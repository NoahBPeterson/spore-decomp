#!/usr/bin/env python3
"""Verify a symbol-less COMDAT fragment (catch funclet, cold tail, continuation label) by
byte-comparing the whole COMDAT that encloses it against the original image.

usage:
  comdat_check.py <va> [<va> ...] [--parent VA] [--table FILE] [--src FILE] [--module ID]
                  [--flags "..."] [--json FILE]
  comdat_check.py --table docs/equiv_verdicts.json --from-results DIR [<va> ...] [--workers N]

For each VA:
  1. parent = the closest function start at or below the VA in work/index/functions.csv
     (fragment starts listed by the index are skipped), or --parent.
  2. the module source named by the verdict row (`<file>.nonmatching.txt` -> `<file>.cpp`) and
     every slice that claims the parent are compiled; `slice.find_symbol` resolves the parent's
     symbol and the length of its COMDAT section.  When the module's own symbol does not have
     the original function's indexed length, the slice source with the matching length wins.
  3. cmpobj runs with --len = the enclosing COMDAT length (the length recorded in the row's
     note, when the note states one and the compiled section is large enough, else the
     section/next-function span), and the row is reported as
         BYTE-EXACT-COMDAT
     or
         COMDAT-DIFFERS(<n> bytes, first at +0x<off>)
     The fragment's own byte range is classified separately.

--table + --from-results checks every `funclet` row of docs/equiv_verdicts.json and writes one
JSON per row (`<module>_<va>.json`) into that directory.  docs/equiv_verdicts.json is never
modified.  Exit status is 0 when every row produced a verdict; ERROR rows make it 1.
"""
import argparse, bisect, collections, glob, json, os, re, subprocess, sys
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(ROOT, "tools", "matching"))
import slice as S                                   # noqa: E402
from coff import Coff                               # noqa: E402

CMPOBJ = os.path.join(ROOT, "tools", "matching", "cmpobj.py")
IMAGE = os.path.join(ROOT, "work", "SporeApp.analysis.bin")
FUNCS = os.path.join(ROOT, "work", "index", "functions.csv")
TABLE = os.path.join(ROOT, "docs", "equiv_verdicts.json")

_STARTS = None
_IMG = None
_TABLE_ROWS = None
_NOTES = None
_SLICE_CLAIMS = None
_FILE_ROWS = {}
_RESOLVE_CACHE = {}


# ---------------------------------------------------------------- index / image

def starts():
    """Sorted .text function starts from work/index/functions.csv."""
    global _STARTS
    if _STARTS is None:
        out = []
        import csv
        with open(FUNCS, newline="") as f:
            for row in csv.DictReader(f):
                if row.get("block") == ".text":
                    out.append(int(row["address"], 16))
        _STARTS = sorted(set(out))
    return _STARTS


class Image:
    """Just enough of the analysis image for function extents."""

    def __init__(self, path):
        import pefile
        self.pe = pefile.PE(path, fast_load=True)
        self.base = self.pe.OPTIONAL_HEADER.ImageBase

    def read(self, va, n):
        return self.pe.get_data(va - self.base, n)


def image():
    global _IMG
    if _IMG is None:
        _IMG = Image(IMAGE)
    return _IMG


def orig_extent(va):
    """(start, end) of the original function at va: up to the next indexed start, trailing
    0xCC padding removed.  The index splits EH handlers off as starts, so this is the
    function's own body (495 for _Insert_n, 113 for _Copy, 421 for insert_n)."""
    st = starts()
    i = bisect.bisect_right(st, va)
    end = st[i] if i < len(st) else va + 0x1000
    data = image().read(va, end - va)
    n = len(data)
    while n and data[n - 1] == 0xCC:
        n -= 1
    return va, va + n


# ---------------------------------------------------------------- verdict table / notes

def table_rows():
    global _TABLE_ROWS
    if _TABLE_ROWS is None:
        _TABLE_ROWS = {}
        try:
            d = json.load(open(TABLE))
            rows = d.get("rows") if isinstance(d, dict) else d
            if isinstance(rows, dict):
                for k, v in rows.items():
                    try:
                        _TABLE_ROWS[int(k, 16)] = dict(v)
                    except ValueError:
                        pass
            elif isinstance(rows, list):
                for v in rows:
                    try:
                        _TABLE_ROWS[int(v["va"], 16)] = dict(v)
                    except (KeyError, ValueError):
                        pass
        except (OSError, ValueError):
            pass
    return _TABLE_ROWS


def funclet_set():
    return {va for va, r in table_rows().items() if r.get("category") == "funclet"}


def is_fragment_reason(reason):
    low = (reason or "").lower()
    return ("funclet" in low or "cold tail" in low or "not a function" in low
            or "continuation label" in low or "symbol-less" in low or "eh tail" in low
            or "handler body" in low
            or ("interior of the" in low and "comdat" in low))


def notes():
    """va -> (module id, repo-relative note file, reason).  src/ modules beat old slices."""
    global _NOTES
    if _NOTES is None:
        _NOTES = {}
        for p in sorted(glob.glob(os.path.join(ROOT, "src", "**", "*.nonmatching.txt"), recursive=True)):
            mod = os.path.basename(p)[:-len(".nonmatching.txt")]
            rel = os.path.relpath(p, ROOT)
            for va, _diff, reason in S.read_rows(p):
                _NOTES[va] = (mod, rel, reason)
        for p in sorted(glob.glob(os.path.join(ROOT, "match", "slices", "*", "nonmatching.txt"))):
            sid = os.path.basename(os.path.dirname(p))
            rel = os.path.relpath(p, ROOT)
            for va, _diff, reason in S.read_rows(p):
                _NOTES.setdefault(va, (sid, rel, reason))
    return _NOTES


def row_for(va):
    """Metadata for a VA: the verdict table first, then the note files."""
    r = table_rows().get(va)
    if r is not None:
        return dict(r)
    n = notes().get(va)
    if n is not None:
        mod, rel, reason = n
        return {"module": mod, "file": rel, "reason": reason,
                "category": "funclet" if is_fragment_reason(reason) else "func"}
    return None


def file_rows(rel):
    if rel not in _FILE_ROWS:
        _FILE_ROWS[rel] = {va: reason for va, _d, reason in S.read_rows(os.path.join(ROOT, rel))}
    return _FILE_ROWS[rel]


# ---------------------------------------------------------------- sources / symbols

def module_source(row, override=None):
    if override:
        return os.path.abspath(override)
    f = row.get("file") or ""
    if f.endswith(".nonmatching.txt"):
        p = os.path.join(ROOT, f[:-len(".nonmatching.txt")] + ".cpp")
        if os.path.exists(p):
            return p
    if f.endswith(".cpp"):
        p = os.path.join(ROOT, f)
        if os.path.exists(p):
            return p
    mod = row.get("module")
    if mod:
        p = S.source_path(mod)
        if os.path.exists(p):
            return p
        hits = glob.glob(os.path.join(ROOT, "src", "**", mod + ".cpp"), recursive=True)
        if len(hits) == 1:
            return hits[0]
    return None


def slice_claims():
    """parent VA -> [slice ids] whose nonmatching rows or manifests bind that VA."""
    global _SLICE_CLAIMS
    if _SLICE_CLAIMS is None:
        d = collections.defaultdict(list)
        for p in sorted(glob.glob(os.path.join(ROOT, "match", "slices", "*", "nonmatching.txt"))):
            sid = os.path.basename(os.path.dirname(p))
            for va, _diff, _reason in S.read_rows(p):
                if sid not in d[va]:
                    d[va].append(sid)
        for p in sorted(glob.glob(os.path.join(ROOT, "match", "slices", "*", "manifest.txt"))):
            sid = os.path.basename(os.path.dirname(p))
            for src, sym, va, _flags in S.manifest_rows(sid):
                if sid not in d[va]:
                    d[va].append(sid)
        _SLICE_CLAIMS = dict(d)
    return _SLICE_CLAIMS


def flags_for(sid, va, src, override):
    if override:
        return override.split()
    flags, how = S.choose_flags(sid, va)
    flags = list(flags)
    # a module TU (src/game/...) includes game/types.h and the canonical headers
    if os.path.abspath(src).startswith(os.path.join(ROOT, "src", "game") + os.sep):
        if not any(f.replace("\\", "/").rstrip("/").endswith("src/game/include")
                   for f in flags if f.startswith("/I")):
            flags.append("/Isrc/game/include")
    return flags


def template_tokens(src, va):
    """Identifiers inside the template argument list of the definition marked for va
    (std::vector<E56>::_Insert_n -> E56), so an overload set resolves to the right instance."""
    try:
        lines = open(src, encoding="utf-8", errors="replace").read().split("\n")
    except OSError:
        return []
    mark = re.compile(r"@\s*0x0*%x\b" % va, re.I)
    out = []
    for i, line in enumerate(lines):
        if not mark.search(line):
            continue
        for j in range(i + 1, min(i + 14, len(lines))):
            code = lines[j].split("//", 1)[0]
            for grp in re.findall(r"<([^<>]*)>", code):
                for tok in re.findall(r"[A-Za-z_]\w+", grp):
                    if len(tok) > 1 and tok not in ("std", "vector", "allocator", "char_traits", "basic_string"):
                        if tok not in out:
                            out.append(tok)
            if "{" in code or ";" in code:
                break
    return out


def pick_symbol(coff, cands, orig_len, tokens):
    """Best candidate: same template argument first, then closest function length."""
    best = None
    for n in cands:
        f = coff.by_name.get(n)
        if f is None:
            continue
        _sec, a, b = coff.func_extent(f)
        tok = 0 if any(t in n for t in tokens) else 1
        score = (tok, abs((b - a) - orig_len) if orig_len else 0)
        if best is None or score < best[0]:
            best = (score, n)
    return best[1] if best else None


def candidate(src, sid, parent_va, orig_len, override):
    """Compile src, resolve the parent symbol, and return its COMDAT facts (or None)."""
    if not src or not os.path.exists(src):
        return None
    flags = flags_for(sid, parent_va, src, override)
    key = (os.path.abspath(src), parent_va, tuple(flags), orig_len)
    if key in _RESOLVE_CACHE:
        return _RESOLVE_CACHE[key]
    obj, log = S.compile_obj(src, flags)
    if obj is None:
        _RESOLVE_CACHE[key] = None
        return None
    try:
        coff = Coff(obj)
        sym, how = S.find_symbol(coff, sid, parent_va, src, orig_len or None)
        if isinstance(sym, list):
            sym = pick_symbol(coff, sym, orig_len, template_tokens(src, parent_va))
        if not sym or sym not in coff.by_name:
            _RESOLVE_CACHE[key] = None
            return None
        fs = coff.by_name[sym]
        if not fs.defined:
            _RESOLVE_CACHE[key] = None
            return None
        sec = coff.section_of(fs)
        _s, a, b = coff.func_extent(fs)
        info = {
            "src": src, "sid": sid, "flags": " ".join(flags), "obj": obj,
            "coff": coff, "symbol": sym, "symbol_from": how,
            "section_len": len(sec.data) - fs.value,
            "value": fs.value, "extent_len": b - a,
            "dist": abs((b - a) - orig_len) if orig_len else 0,
        }
    except Exception:
        info = None
    _RESOLVE_CACHE[key] = info
    return info


def resolve_parent(parent_va, row, override_src, flags_override):
    """Compile the module source and any slice claiming the parent; pick the candidate whose
    function length matches the original's indexed extent (module wins ties)."""
    mod_src = module_source(row, override_src)
    mod_id = row.get("module") or (os.path.basename(mod_src).rsplit(".", 1)[0] if mod_src else "?")
    ck = (mod_src, mod_id, parent_va, flags_override or "")
    if ck in _RESOLVE_CACHE:
        return _RESOLVE_CACHE[ck]
    lo, hi = orig_extent(parent_va)
    orig_len = hi - lo
    best = candidate(mod_src, mod_id, parent_va, orig_len, flags_override)
    if best is None or best["dist"] > 0:
        for sid in slice_claims().get(parent_va, [])[:4]:
            info = candidate(S.source_path(sid), sid, parent_va, orig_len, flags_override)
            if info is not None and (best is None or info["dist"] < best["dist"]):
                best = info
                if best["dist"] == 0:
                    break
    _RESOLVE_CACHE[ck] = best
    return best


def covers(info, parent_va, va):
    return info is not None and info["value"] + (va - parent_va) < info["value"] + info["section_len"]


def resolve_fragment(va, row, parent_override, override_src, flags_override):
    """Parent + compiled COMDAT facts for a fragment/VA."""
    parent = int(parent_override, 16) if isinstance(parent_override, str) else parent_override
    if parent is not None:
        info = resolve_parent(parent, row, override_src, flags_override)
        if info is None or not covers(info, parent, va):
            return parent, None
        return parent, info

    # A few table rows are marked `funclet` but their note describes a complete function
    # (warn_sound, check_*): those are ordinary VAs and must be checked as themselves.  A slice
    # may supply the symbol only when the note describes a real function (a slice marker can
    # bind a symbol-less fragment to an unrelated function), and the length must match the
    # indexed function extent.
    reason = row.get("reason") or ""
    allow_self = (not is_fragment_reason(reason)
                  and (bool(reason) or row.get("category") != "funclet"))
    if parent_override is None and allow_self:
        lo, hi = orig_extent(va)
        orig_len = hi - lo
        tol = max(8, orig_len // 10)
        mod_src = module_source(row, override_src)
        mod_id = row.get("module") or (os.path.basename(mod_src).rsplit(".", 1)[0] if mod_src else "?")
        best = candidate(mod_src, mod_id, va, orig_len, flags_override)
        # the module's marker scan can break on a `__declspec` line (script_interpreter's
        # check_* / warn_* functions); a slice that claims the VA has the exact symbol table.
        # Only trust it when the note describes a real function, not a fragment.
        if row.get("reason") and (best is None or best["dist"] > tol):
            for sid in slice_claims().get(va, [])[:4]:
                info = candidate(S.source_path(sid), sid, va, orig_len, flags_override)
                if info is not None and (best is None or info["dist"] < best["dist"]):
                    best = info
                    if best["dist"] == 0:
                        break
        if best is not None and covers(best, va, va) and best["dist"] <= tol:
            return va, best

    st = starts()
    fs = funclet_set()
    is_frag = row.get("category") == "funclet" or va in fs or is_fragment_reason(row.get("reason", ""))
    i = bisect.bisect_right(st, va) - 1
    if i >= 0 and st[i] == va and is_frag:
        i -= 1
    tried = 0
    while i >= 0 and tried < 8:
        p = st[i]
        i -= 1
        if p in fs:
            continue
        tried += 1
        info = resolve_parent(p, row, override_src, flags_override)
        if info is not None and covers(info, p, va):
            return p, info
    return None, None


# ---------------------------------------------------------------- COMDAT length

def note_length(row, parent_va, va, span, object_len, orig_len):
    """COMDAT size stated by the row/parent/fragment notes, if it is a usable --len."""
    rel = row.get("file")
    if not rel:
        return None
    try:
        rows = file_rows(rel)
    except OSError:
        return None
    texts = []
    for addr, reason in rows.items():
        if addr == parent_va or addr == va:
            texts.append(reason)
        elif parent_va <= addr < parent_va + span and is_fragment_reason(reason):
            texts.append(reason)
    text = " ".join(texts)
    cands = []
    for m in re.finditer(r"0x([0-9a-fA-F]+)-byte\s+COMDAT", text):
        cands.append(int(m.group(1), 16))
    for m in re.finditer(r"(\d+)-byte\s+COMDAT", text):
        cands.append(int(m.group(1)))
    for m in re.finditer(r"COMDAT\s*\((\d+)\s*bytes?\)", text):
        cands.append(int(m.group(1)))
    for m in re.finditer(r"--len\s+(\d+)", text):
        cands.append(int(m.group(1)))
    valid = [c for c in cands if orig_len <= c <= object_len]
    return min(valid) if valid else None


def group_span(parent_va):
    """Distance from the parent to the next indexed start that is not a known fragment."""
    st = starts()
    fs = funclet_set()
    i = bisect.bisect_right(st, parent_va)
    while i < len(st) and st[i] in fs:
        i += 1
    if i < len(st):
        return st[i] - parent_va
    return None


# ---------------------------------------------------------------- prepare / run

def prepare_row(row, va, parent_override=None, override_src=None, flags_override=None):
    out = {"va": va, "module": row.get("module") or "?", "file": row.get("file"),
           "fragment_size": row.get("size") or 0, "error": None}
    # verdict-table rows carry no prose: read the row's note so a complete function that the
    # table categorised as `funclet` is not mistaken for a symbol-less fragment.
    if not row.get("reason") and row.get("file"):
        try:
            row = dict(row)
            row["reason"] = file_rows(row["file"]).get(va, "")
        except OSError:
            pass
    try:
        parent, info = resolve_fragment(va, row, parent_override, override_src, flags_override)
        if parent is None or info is None:
            out["error"] = "no symbol-bearing parent COMDAT for 0x%08x" % va
            return out
        lo, hi = orig_extent(parent)
        orig_len = hi - lo
        span = group_span(parent)
        object_len = info["section_len"]
        length = note_length(row, parent, va, span or object_len, object_len, orig_len)
        if length is None:
            length = min(object_len, span) if span else object_len
        out.update(parent=parent, info=info, length=length, object_len=object_len,
                   orig_len=orig_len, span=span, note_len=length if length != object_len else None)
        if not row.get("size") and info and out["fragment_size"] == 0:
            # the index's extent for this fragment (next indexed start)
            i = bisect.bisect_right(starts(), va)
            if i < len(starts()):
                out["fragment_size"] = starts()[i] - va
    except Exception as e:                      # noqa: BLE001 - one row must not kill the table run
        out["error"] = "%s: %s" % (type(e).__name__, str(e)[:200])
    return out


def run_cmpobj(info, parent, length):
    cmd = [sys.executable, CMPOBJ, IMAGE, info["obj"], info["symbol"],
           "0x%08x" % parent, "--len", str(length)]
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    return r.returncode, r.stdout + r.stderr


_SUMMARY = re.compile(r"len\s+(\d+):\s+(MATCH|DIFF)\s+\((\d+) diff bytes, (\d+) masked\)")
_DIFFAT = re.compile(r"diff@\s*\[([^\]]*)\]")


def execute(prep):
    """Run cmpobj and classify both the COMDAT and the fragment's own bytes."""
    res = dict(prep)
    if prep.get("error"):
        res.update(verdict="ERROR", reason=prep["error"], fragment_verdict="ERROR")
        return res
    info, parent, length = prep["info"], prep["parent"], prep["length"]
    rc, out = run_cmpobj(info, parent, length)
    m = _SUMMARY.search(out)
    if not m:
        last = out.strip().splitlines()[-1] if out.strip() else "cmpobj produced no summary"
        res.update(verdict="ERROR", reason="cmpobj failed: " + last[:300], fragment_verdict="ERROR")
        return res
    n = int(m.group(3))
    first = None
    dm = _DIFFAT.search(out)
    offs = []
    if dm and dm.group(1).strip():
        offs = [int(x) for x in re.findall(r"\d+", dm.group(1))]
        if offs:
            first = offs[0]
    frag_off = prep["va"] - parent
    frag_len = prep.get("fragment_size") or 0
    if m.group(2) == "MATCH":
        verdict = "BYTE-EXACT-COMDAT"
        frag_verdict = "BYTE-EXACT-FRAGMENT"
        detail = "byte-exact"
    else:
        verdict = "COMDAT-DIFFERS"
        if n == 0 and len(out):
            # length mismatch only (cmpobj's `ok` also requires len(mine) == length)
            detail = "0 differing bytes but a length mismatch"
            first = length
        elif first is None:
            detail = "%d differing bytes" % n
        else:
            detail = "%d differing bytes, first at +0x%x" % (n, first)
        if n == 0:
            verdict = "COMDAT-DIFFERS(0 bytes, length mismatch)"
        elif first is not None:
            verdict = "COMDAT-DIFFERS(%d bytes, first at +0x%x)" % (n, first)
        else:
            verdict = "COMDAT-DIFFERS(%d bytes)" % n
        # classify the fragment's own range; the full offset list is printed only when <= 32
        if n == 0:
            frag_verdict = "FRAGMENT-LENGTH-MISMATCH"
        elif frag_len and len(offs) == n:
            inside = [o for o in offs if frag_off <= o < frag_off + frag_len]
            frag_verdict = ("FRAGMENT-DIFFERS(%d bytes)" % len(inside)) if inside else "BYTE-EXACT-FRAGMENT"
        elif frag_len and first is not None and first >= frag_off + frag_len:
            frag_verdict = "BYTE-EXACT-FRAGMENT(no diff before +0x%x)" % (frag_off + frag_len)
        else:
            frag_verdict = "UNCLASSIFIED"
    reason_bits = [
        "parent 0x%08x (%s)" % (parent, info["symbol"]),
        "source %s" % os.path.relpath(info["src"], ROOT),
        "COMDAT %d bytes" % length,
    ]
    if prep.get("note_len") is not None:
        reason_bits.append("object COMDAT %d bytes" % prep["object_len"])
    reason = "; ".join(reason_bits) + "; " + detail
    if frag_len:
        reason += "; fragment 0x%08x (%d bytes): %s" % (prep["va"], frag_len, frag_verdict)
    res.update(verdict=verdict, reason=reason, fragment_verdict=frag_verdict,
               diff_bytes=n, first_diff=first, comdat_parent=parent, comdat_len=length,
               comdat_symbol=info["symbol"], source=os.path.relpath(info["src"], ROOT),
               flags=info["flags"])
    return res


# ---------------------------------------------------------------- modes

def result_json(r):
    return {
        "va": "%08x" % r["va"],
        "module": r.get("module"),
        "verdict": r.get("verdict"),
        "reason": r.get("reason"),
        "comdat_parent": ("%08x" % r["comdat_parent"]) if r.get("comdat_parent") is not None else None,
        "comdat_len": r.get("comdat_len"),
        "fragment_verdict": r.get("fragment_verdict"),
        "comdat_symbol": r.get("comdat_symbol"),
        "source": r.get("source"),
        "flags": r.get("flags"),
        "diff_bytes": r.get("diff_bytes"),
        "first_diff": r.get("first_diff"),
    }


def print_one(r):
    if r.get("verdict") == "ERROR":
        print("0x%08x %s: ERROR %s" % (r["va"], r.get("module", "?"), r.get("reason", "")))
        return
    print("0x%08x %s parent 0x%08x len %d: %s" % (
        r["va"], r.get("module", "?"), r["comdat_parent"], r["comdat_len"], r["verdict"]))
    print("    %s" % r["reason"])
    if r.get("fragment_verdict"):
        print("    fragment: %s%s" % (r["fragment_verdict"],
                                      (" (%d bytes)" % r["fragment_size"]) if r.get("fragment_size") else ""))


def tally(results):
    c = collections.Counter()
    for r in results:
        v = r.get("verdict") or "ERROR"
        c[v.split("(", 1)[0]] += 1
    print("tally: %d rows: %s" % (len(results), dict(c.most_common())))
    return c


def table_mode(args):
    d = json.load(open(args.table))
    rows = d.get("rows") if isinstance(d, dict) else d
    items = []
    if isinstance(rows, dict):
        for k, v in rows.items():
            if v.get("category") == "funclet":
                try:
                    items.append((int(k, 16), v))
                except ValueError:
                    pass
    else:
        for v in rows:
            if v.get("category") == "funclet":
                items.append((int(v["va"], 16), v))
    items.sort()
    if args.vas:
        want = {int(v, 16) for v in args.vas}
        items = [it for it in items if it[0] in want]
    outdir = os.path.abspath(args.from_results) if args.from_results else None
    if outdir:
        os.makedirs(outdir, exist_ok=True)
    preps = [prepare_row(row, va, args.parent, args.src, args.flags) for va, row in items]
    with ThreadPoolExecutor(max_workers=max(1, args.workers)) as ex:
        results = list(ex.map(execute, preps))
    for r in results:
        print_one(r)
        if outdir:
            path = os.path.join(outdir, "%s_%08x.json" % (r.get("module") or "?", r["va"]))
            json.dump(result_json(r), open(path, "w"), indent=1)
    tally(results)
    return 0 if all(r.get("verdict") != "ERROR" for r in results) else 1


def direct_mode(args):
    results = []
    for v in args.vas:
        va = int(v, 16)
        row = row_for(va) or {}
        if args.src and not row:
            row = {"module": args.module or os.path.basename(args.src).rsplit(".", 1)[0]}
        prep = prepare_row(row, va, args.parent, args.src, args.flags)
        results.append(execute(prep))
    for r in results:
        print_one(r)
    if args.json:
        json.dump([result_json(r) for r in results], open(args.json, "w"), indent=1)
    if len(results) > 1:
        tally(results)
    return 0 if all(r.get("verdict") != "ERROR" for r in results) else 1


def main(argv=None):
    global TABLE
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("vas", nargs="*", help="fragment/function virtual address(es)")
    ap.add_argument("--parent", help="enclosing function start VA (default: from functions.csv)")
    ap.add_argument("--table", default=None, help="verdict table (default docs/equiv_verdicts.json)")
    ap.add_argument("--from-results", help="write one <module>_<va>.json per table row into this dir")
    ap.add_argument("--module", help="module id when the VA is not in the table")
    ap.add_argument("--src", help="module source to compile instead of the row's file")
    ap.add_argument("--flags", help="compiler flags (default: slice.choose_flags)")
    ap.add_argument("--json", help="write the direct-mode results here")
    ap.add_argument("--workers", type=int, default=8)
    args = ap.parse_args(argv)

    if args.table:
        TABLE = os.path.abspath(args.table)
    args.table = TABLE
    if args.from_results or (not args.vas and args.table):
        if not args.from_results:
            ap.error("--from-results DIR is required when checking the whole table")
        return table_mode(args)
    if not args.vas:
        ap.error("give at least one VA, or --table ... --from-results DIR")
    return direct_mode(args)


if __name__ == "__main__":
    sys.exit(main())
