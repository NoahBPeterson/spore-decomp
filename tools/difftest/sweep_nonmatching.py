#!/usr/bin/env python3
"""sweep_nonmatching.py: re-run equiv on every nonmatching row (match/slices/*/nonmatching.txt and
src/**/*.nonmatching.txt) and tally every mismatch, not just the first (equiv's mismatch_sigs).

usage: sweep_nonmatching.py [--out DIR=work/sweep] [--workers N=6] [--filter substr] [--tally] [--extra "..."]
Each row runs `equiv.py <id> <va> [--src <module.cpp>] --fp-tol --max-mismatch 200 --json <out>/<id>_<va>.json`;
rows whose JSON exists are skipped (restartable). One row per VA: a VA listed both in a src module and in its
old slice runs from the module (and a VA two slices both claim runs from the one whose source/symbol table
records it); every dropped claim is named once on stderr. A slice claim for a VA a src module's manifest binds (the
slice was migrated into the module and left in place) is no row: the slice's source is no longer built. --tally prints verdict counts and writes
<out>/tally.json: every row with its recorded reason, the new verdict and the mismatch signatures."""
import argparse, collections, glob, json, os, re, subprocess, sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
PY = os.path.join(ROOT, ".venv", "bin", "python")
EQ = os.path.join(ROOT, "tools", "difftest", "equiv.py")
ROW = re.compile(r"^([0-9a-fA-F]{8})\s+\S+\s+(.*)$")
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import slice as SL                                # noqa: E402  (VA->symbol tables, manifests, source markers)



# Spore keeps a migrated module's bookkeeping in a directory (src/game/<dir>/<obj>/{manifest,nonmatching}.txt next to
# src/game/<dir>/<obj>.cpp); Mount & Blade's are src/**/<stem>.{manifest,nonmatching}.txt. A Spore module row runs
# under the id of the slice the function came from (rewrite.py lands slices verbatim, so the slice's symbol table
# and flags still describe it) with --src the module TU.
def module_files(kind):
    """[(bookkeeping file, module TU, equiv id)] for kind 'manifest' or 'nonmatching', both layouts. A Spore module
    id is its object's stem, or '<dir>/<obj>' when two directories have the same stem (slice.module_dir)."""
    out = []
    for p in sorted(glob.glob(os.path.join(ROOT, "src", "**", "*.%s.txt" % kind), recursive=True)):
        out.append((p, p[:-len(".%s.txt" % kind)] + ".cpp", os.path.basename(p)[:-len(".%s.txt" % kind)]))
    for p in sorted(glob.glob(os.path.join(ROOT, "src", "game", "*", "*", "%s.txt" % kind))):
        d = os.path.dirname(p)
        if os.path.exists(d + ".cpp"):
            stem = os.path.basename(d)
            out.append((p, d + ".cpp", stem if SL.module_dir(stem) else
                        os.path.relpath(d, os.path.join(ROOT, "src", "game")).replace(os.sep, "/")))
    return out


def result_name(r):
    """<out>/<this>.json for a row (a '<dir>/<obj>' id has its slash replaced)."""
    return "%s_%s.json" % (r["id"].replace("/", "__"), r["va"])


_VA_COMMENT = re.compile(r"//.*@\s*0x0*([0-9a-fA-F]{3,8})\b")
_TABLES, _MANIFESTS, _COMMENTS = {}, {}, {}


def _table_vas(sid):
    """VAs `symbols/slices/<sid>.txt` names a mangled symbol for (written from the compiled TU)."""
    if sid not in _TABLES:
        out, p = set(), os.path.join(ROOT, "symbols", "slices", sid + ".txt")
        try:
            for line in open(p, encoding="utf-8", errors="replace"):
                q = line.split("#", 1)[0].split(None, 1)
                try:
                    out.add(int(q[0], 16))
                except (IndexError, ValueError):
                    pass
        except OSError:
            pass
        _TABLES[sid] = out
    return _TABLES[sid]


def _manifest_vas(sid):
    """VAs the slice/module manifest binds to a symbol."""
    if sid not in _MANIFESTS:
        _MANIFESTS[sid] = {r[2] for r in SL.manifest_rows(sid)}
    return _MANIFESTS[sid]


def _comment_vas(src):
    """VAs src marks with a '// ... @ 0x<va>' comment: find_symbol's marker binding."""
    if src not in _COMMENTS:
        out = set()
        try:
            out = {int(m[1], 16) for m in _VA_COMMENT.finditer(open(src, encoding="utf-8", errors="replace").read())}
        except OSError:
            pass
        _COMMENTS[src] = out
    return _COMMENTS[src]


def _defines(c, va):
    """2 if the module's own symbol table/manifest binds va, 1 if its source carries the VA marker, else 0."""
    v = int(va, 16)
    if v in _table_vas(c["id"]) or v in _manifest_vas(c["id"]):
        return 2
    src = os.path.join(ROOT, c["src"]) if c["src"] else SL.source_path(c["id"])
    return 1 if v in _comment_vas(src) else 0


def _claims():
    out = []
    for p in sorted(glob.glob(os.path.join(ROOT, "match", "slices", "*", "nonmatching.txt"))):
        sid = os.path.basename(os.path.dirname(p))
        for line in open(p, encoding="utf-8", errors="replace"):
            m = ROW.match(line.strip())
            if m:
                out.append({"id": sid, "va": m[1].lower(), "src": None, "reason": m[2][:2000],
                            "file": os.path.relpath(p, ROOT)})
    for p, src, stem in module_files("nonmatching"):
        for line in open(p, encoding="utf-8", errors="replace"):
            m = ROW.match(line.strip())
            if m:
                out.append({"id": stem, "va": m[1].lower(),
                            "src": os.path.relpath(src, ROOT), "reason": m[2][:2000], "file": os.path.relpath(p, ROOT)})
    return out


def _module_manifest_vas():
    """VA -> (module, module source) for every function a src module's manifest binds (its compiled object)."""
    out = {}
    for p, src, stem in module_files("manifest"):
        src = os.path.relpath(src, ROOT)
        for line in open(p, encoding="utf-8", errors="replace"):
            q = line.split("#", 1)[0].split()
            if len(q) > 2:
                try:
                    va = int(q[2], 16)
                except ValueError:
                    continue
                out.setdefault(va, (stem, src))
    return out


def rows():
    """One row per VA, from the module whose compiled object defines it: a src module beats its old slice,
    and within a kind the module whose manifest/symbol table/VA marker binds the VA wins; remaining ties go
    to the lowest module name. Dropped duplicate claims are named on stderr."""
    by_va = collections.defaultdict(list)
    live = _module_manifest_vas()
    for c in _claims():
        if not c["src"] and int(c["va"], 16) in live:
            # a slice claim for a function a module now compiles (the slices stay in place after a migration,
            # src/rgl/mesh2/MIGRATION.md) and does not list as nonmatching: the slice's source is dead code and
            # the module's function is exact, so there is no row (verdicts.py counts module rows only)
            continue
        by_va[c["va"]].append(c)
    out, dropped = [], []
    for va, cs in by_va.items():
        # (module before slice, strongest definition evidence, lowest name) -- total and deterministic
        ranked = sorted(cs, key=lambda c: (0 if c["src"] else 1, -_defines(c, va), c["id"], c["file"]))
        out.append(ranked[0])
        dropped += ["%s:%s" % (va, c["id"]) for c in ranked[1:]]
    if dropped:
        dropped.sort()
        print("sweep: kept one row per VA (%d rows); dropped %d duplicate claim(s): %s"
              % (len(out), len(dropped), ", ".join(dropped)), file=sys.stderr)
    return sorted(out, key=lambda r: r["va"])


_ROW_OPTS = None


def row_opts(r):
    """Extra equiv.py arguments for one row from tools/difftest/row_opts.json ("<id> <va>": {"args": [...], "why":
    "..."}): facts about a row the harness cannot infer, such as image functions one build inlines and the other
    calls (--transparent), each with its reason."""
    global _ROW_OPTS
    if _ROW_OPTS is None:
        try:
            _ROW_OPTS = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "row_opts.json")))
        except (OSError, ValueError):
            _ROW_OPTS = {}
    return list((_ROW_OPTS.get("%s %s" % (r["id"], r["va"])) or {}).get("args", []))


def equivalent_vas():
    """VAs tools/status.py counts as equivalent (compilable, not byte-exact), or None when it is not available."""
    st = os.path.join(ROOT, "tools", "status.py")
    if not os.path.exists(st):
        return None
    import contextlib, io, runpy
    with contextlib.redirect_stdout(io.StringIO()):
        return set(runpy.run_path(st)["equiv"])


def run(r, out, extra):
    js = os.path.join(out, result_name(r))
    if os.path.exists(js):
        return
    cmd = [PY, EQ, r["id"], r["va"], "--fp-tol", "--max-mismatch", "200", "--json", js + ".part"] + extra + row_opts(r)
    if r["src"]:
        cmd += ["--src", os.path.join(ROOT, r["src"])]
    try:
        subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=900)
    except subprocess.TimeoutExpired:
        json.dump([{"verdict": "TIMEOUT"}], open(js + ".part", "w"))
    if os.path.exists(js + ".part"):
        os.replace(js + ".part", js)
    else:
        json.dump([{"verdict": "CRASH"}], open(js, "w"))


def tally(rs, out):
    res, c = [], collections.Counter()
    for r in rs:
        js = os.path.join(out, result_name(r))
        if not os.path.exists(js):
            continue
        d = json.load(open(js))
        d = d[0] if isinstance(d, list) and d else d
        v = d.get("verdict", "?")
        c[v] += 1
        res.append(dict(r, verdict=v, why=d.get("reason", "")[:300], sigs=d.get("mismatch_sigs", {}),
                        fp_tol=d.get("fp_tol")))
    json.dump(res, open(os.path.join(out, "tally.json"), "w"), indent=1)
    print("%d rows run of %d: %s" % (len(res), len(rs), dict(c.most_common())))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=os.path.join(ROOT, "work", "sweep"))
    ap.add_argument("--workers", type=int, default=6)
    ap.add_argument("--filter")
    ap.add_argument("--tally", action="store_true")
    ap.add_argument("--extra", default="")
    ap.add_argument("--all-rows", action="store_true", help="also rows tools/status.py does not count as equivalent")
    ap.add_argument("--rows", help="only these rows: a file of '<id> <va>' or '<va>' lines")
    a = ap.parse_args()
    os.makedirs(a.out, exist_ok=True)
    rs = [r for r in rows() if not a.filter or a.filter in r["id"] or a.filter in r["va"]]
    if not a.all_rows:
        keep = equivalent_vas()
        if keep is not None:
            print("sweep: %d of %d rows are equivalent functions (tools/status.py); the rest (partial, byte-exact "
                  "elsewhere, library) are skipped (--all-rows: keep them)" % (sum(int(r["va"], 16) in keep for r in rs),
                                                                          len(rs)), file=sys.stderr)
            rs = [r for r in rs if int(r["va"], 16) in keep]
    if a.rows:
        want = {tuple(l.split()[:2]) for l in open(a.rows) if l.strip() and not l.startswith("#")}
        rs = [r for r in rs if (r["id"], r["va"]) in want or ("", r["va"]) in want or (r["va"],) in want]
    if not a.tally:
        with ThreadPoolExecutor(a.workers) as ex:
            list(ex.map(lambda r: run(r, a.out, a.extra.split()), rs))
    tally(rs, a.out)


if __name__ == "__main__":
    sys.exit(main())
