#!/usr/bin/env python3
"""Recover addresses for the 'unresolved reference' blockers of the equivalence checker.

The checker (tools/difftest/equiv.py) refuses to test a rebuilt function when an outside symbol
it references has no known address in the original image.  Most leftovers after the exact-name
pass are names the decompiling agent invented (Callee::f, g_vtblA, CPlayerInventory::f5cae30,
EAVec<I>::DoInsertValue ...), so no symbol database can ever name them.  What does identify them
is the *original function itself*: its sequence of call/data references, aligned against ours.

    harvest   compile + resolve every blocked function (equiv.prepare), record the unresolved
              symbols and both reference sequences          -> DIR/harvest.json
    propose   score candidate addresses per symbol           -> DIR/proposals.json, propose.md
    apply     write '// 0x<VA>' annotations into the slice sources for accepted proposals,
              re-verify byte-exactness (run_all, auto-revert) and re-run the resolver
                                                             -> DIR/apply.json, apply.md
    report    final per-symbol / per-function verdict table  -> DIR/report.md

Evidence per candidate address (a candidate comes from aligning the two reference sequences,
or from a 6-8 digit hex address in the name that the original function references):
    hex-name         the name carries the candidate's address (f5cae30, Fn_ef30, Fun0066_0ad0)
    align-1gap       the resolver's own alignment (gap of one reference between anchors)
    align-weak       gap of equal length and agreeing mnemonics (89% right for 2-gaps, less beyond)
    gap:N            length of that gap
    positional       same number of references of that kind on both sides, mnemonics agree
    arity-ok / arity-MISMATCH   the original callee's 'ret N' vs the stack bytes our declaration
                     implies (a mismatch vetoes the candidate)
    db-name          the candidate's name in symbols/ shares the identifier
    db-name-unique   nothing aligned, but exactly one original reference of that kind is named
                     (in symbols/) with our identifier; accepted only with arity-ok (calls)
    sibling-ann      another slice already annotates this identifier+scope with the candidate
    slice-consensus  other blocked functions of the same slice align the symbol to the same VA

Tiers: 1 hex-name+aligned; 2 aligned+corroborated; 3 aligned, gap<=2, arity agrees (data: gap 1);
4 aligned only (reported, not applied by default).  `__except_list` is not a symbol at all (the
SEH chain head, fs:[0]); the resolver now maps it to 0 like the CRT does, so it never appears.

usage: resolve_leftover.py harvest [--worklist JSON] [--jobs N] [--dir DIR]
       resolve_leftover.py propose [--dir DIR]
       resolve_leftover.py apply [--dir DIR] [--max-tier 3] [--dry-run] [--only SLICE ...]
       resolve_leftover.py report [--dir DIR]
"""
import argparse, collections, glob, json, os, re, subprocess, sys, traceback

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(ROOT, "tools", "difftest"))
sys.path.insert(0, HERE)

DEFAULT_DIR = os.path.join(ROOT, "work", "claude", "resolve_leftover")
EH_OURS = ("__ehhandler$", "__except_list", "__unwindfunclet$", "__security_cookie", "@__security_check_cookie@4",
           "___security_cookie")
HEXRUN = re.compile(r"[0-9A-Fa-f]{3,8}")
CANON_DECL = {   # free operators the compiler declares implicitly: nothing in the source to annotate
    "??_V@YAXPAX@Z": "void operator delete[](void*);",
    "??3@YAXPAX@Z": "void operator delete(void*);",
    "??_U@YAPAXIPBDHI0H@Z": "void* operator new[](unsigned int, const char*, int, unsigned int, const char*, int);",
    "??2@YAPAXIPBDHI0H@Z": "void* operator new(unsigned int, const char*, int, unsigned int, const char*, int);",
    "??2@YAPAXIPBDHHHH@Z": "void* operator new(unsigned int, const char*, int, int, int, int);",
    "??2@YAPAXI@Z": "void* operator new(unsigned int);",
    "??_U@YAPAXI@Z": "void* operator new[](unsigned int);",
}


def _lazy():
    import equiv, resolve as R, slice as S, sig as SIG  # noqa: F401
    return equiv, R, S, SIG


# ====================================================================== harvest

def _worker(item):
    sid, vas = item
    return [_harvest_one(sid, int(v, 16)) for v in vas]


_rev = None


def _rev_names(equiv):
    global _rev
    if _rev is None:
        ctx = equiv.context()
        rev = collections.defaultdict(set)
        for nm, vas in ctx["db"].mangled.items():
            for v in vas:
                rev[v].add(nm)
        for nm, vas in ctx["db"].qual.items():
            for v in vas:
                rev[v].add(nm)
        for v, nm in ctx["img"].names.items():
            rev[v].add(nm)
        _rev = rev
    return _rev


def _harvest_one(sid, va):
    equiv, R, S, SIG = _lazy()
    from coff import REL_REL32
    rec = {"slice": sid, "va": "%08x" % va}
    try:
        t = equiv.prepare(sid, va, log=lambda *a: None)
    except Exception:
        rec["error"] = traceback.format_exc()[-800:]
        return rec
    rec.update(verdict=t.verdict, reason=getattr(t, "reason", None), flags=getattr(t, "flags", None),
               sym=getattr(t, "sym", None))
    res = getattr(t, "res", None)
    if res is None:
        return rec
    coff, ctx = t.coff, equiv.context()
    rs = ctx["res"]
    rev = _rev_names(equiv)
    usage = collections.defaultdict(set)
    for sec in coff.sections:
        for (off, si, typ) in sec.relocs:
            if typ == REL_REL32 and off >= 1 and sec.data[off - 1] in (0xE8, 0xE9):
                usage[si].add("call")
            else:
                usage[si].add("data")
    o_all, _i, _t, bounds = rs.orig_refs(va)
    u_all = rs.our_refs(coff, t.fsym, res)
    known = dict(res.addr)
    cands, weak = rs._align_round(o_all, u_all, known)
    names = {s.name: s for s in coff.syms.values()}
    unres = []
    for u in res.unresolved:
        nm = u.split(" [")[0]
        d = {"name": nm, "note": u[len(nm) + 2:-1] if " [" in u else ""}
        s = names.get(nm)
        if s is not None:
            d.update(is_func=bool(s.is_func), usage=sorted(usage[s.index]),
                     cands=["%08x" % v for v in sorted(cands.get(s.index, ()))],
                     weak=["%08x" % v for v in sorted(weak.get(s.index, ()))])
        unres.append(d)
    rec["unresolved"] = unres
    rec["eh_unresolved"] = res.eh_unresolved
    rec["orig_refs"] = [(k, m, "%08x" % v, sorted(rev.get(v, ()))[:3]) for k, m, v in o_all]
    rec["our_refs"] = [(k, m, coff.syms[si].name, ("%08x" % known[si]) if si in known else None) for k, m, si in u_all]
    rec["orig_bounds"] = ["%08x" % bounds[0], "%08x" % bounds[1]]
    return rec


def cmd_harvest(a):
    from multiprocessing import Pool
    os.makedirs(a.dir, exist_ok=True)
    if a.worklist:
        wl = json.load(open(a.worklist))
        items = collections.defaultdict(list)
        for w in wl:
            items[w["slice"]].append(w["va"] if isinstance(w["va"], str) else "%08x" % w["va"])
    else:
        _e, _R, S, _S = _lazy()
        items = collections.defaultdict(list)
        for sid in a.slices:
            for va, _d, _r in S.read_rows(os.path.join(S.slice_dir(sid), "nonmatching.txt")):
                items[sid].append("%08x" % va)
    out = []
    items = sorted(items.items())
    with Pool(a.jobs) as p:
        for i, recs in enumerate(p.imap_unordered(_worker, items)):
            out.extend(recs)
            print("harvest %d/%d slices (%d functions)" % (i + 1, len(items), len(out)), flush=True)
    json.dump(out, open(os.path.join(a.dir, "harvest.json"), "w"), indent=1)
    blocked = [r for r in out if "unresolved reference" in (r.get("reason") or "")]
    print("wrote %s: %d functions, %d blocked by unresolved references" % (
        os.path.join(a.dir, "harvest.json"), len(out), len(blocked)))


# ====================================================================== propose

def ident_and_scopes(name):
    _e, R, S, _S = _lazy()
    op = R.operator_of(name) if name.startswith("??") and not name.startswith(("??0", "??1")) else None
    if op:
        return op[0], op[1]
    ident = S.base_ident(name)
    scopes = R.mangled_scopes(name)
    if name.startswith("??1"):
        ident = "~" + ident
    if name.startswith(("??0", "??1")):
        scopes = scopes + [S.base_ident(name)]
    return ident, scopes


def class_of(sym):
    """Name of the innermost class a member symbol belongs to (for a dummy-struct annotation)."""
    _e, _R, S, _S2 = _lazy()
    if sym.startswith(("??0", "??1")):
        return S.base_ident(sym)
    body = sym[3:] if sym.startswith("??$") else sym[1:]
    end = body.find("@@")
    frags = body[:end if end >= 0 else len(body)].split("@")[1:]
    frags = [f for f in frags if f and not f[0].isdigit()]
    if sym.startswith("??$"):
        tm = [f for f in frags if f.startswith("?$")]
        return (tm[0] if tm else frags[-1]).lstrip("?$") if frags else None
    return frags[0].lstrip("?$") if frags else None


def hex_in_name(name):
    """Hex runs (>= 3 digits, containing a decimal digit) in the identifier and its scopes."""
    ident, scopes = ident_and_scopes(name)
    text = ident + "".join("_" + s for s in scopes)
    return [m.group(0).lower() for m in HEXRUN.finditer(text) if re.search(r"\d", m.group(0))]


def hex_matches(name, va):
    h8 = "%08x" % va
    for h in hex_in_name(name):
        if len(h) >= 6 and int(h, 16) == va:
            return True
        if len(h) >= 4 and (h8.endswith(h) or h8.lstrip("0").endswith(h)):
            return True
    return False


def hex_full_addrs(name):
    out = set()
    for h in hex_in_name(name):
        if len(h) >= 6:
            v = int(h, 16)
            if 0x401000 <= v < 0x1900000:
                out.add(v)
    return out


_ret_cache = {}


def callee_ret(va):
    """{'ret N' values} of the original function at va; None for thunks / unknown."""
    equiv, _R, _S, _SIG = _lazy()
    from capstone import x86_const as X
    if va in _ret_cache:
        return _ret_cache[va]
    ctx = equiv.context()
    img, rs = ctx["img"], ctx["res"]
    r = None
    if img.in_text(va) and va in img.start_set:
        b = img.read(va, 6)
        if b[:2] != b"\xff\x25" and b[:1] != b"\xe9":
            try:
                _refs, insns, _t, _b = rs.orig_refs(va)
                vals = {(ins.operands[0].imm if ins.operands else 0) for ins in insns.values() if ins.id == X.X86_INS_RET}
                r = vals or None
            except Exception:
                r = None
    _ret_cache[va] = r
    return r


def expected_ret(name):
    """Stack bytes our declaration says the callee pops ('ret N'), or None if unknown."""
    _e, _R, _S, SIG = _lazy()
    if not name.startswith("?"):
        m = re.match(r"^_\w+@(\d+)$", name)
        if m:
            return int(m.group(1))
        return 0 if name.startswith("_") and "@" not in name else None
    try:
        sg = SIG.parse(name)
    except Exception:
        return None
    if sg.params is None or any(d is None for _k, d in sg.params):
        return None
    if sg.conv == "cdecl" or sg.variadic:
        return 0
    n = sum(d for _k, d in sg.params) + (1 if sg.ret == "hidden" else 0)
    if sg.conv == "fastcall":
        n = max(0, n - 2)
    return 4 * n


def db_ident_equal(name, va, rev):
    """A symbols/ name at va whose last identifier equals ours (case-insensitive; 'g_'/'vtbl_'/'_'
    prefixes ignored) -> that name, else None.  Stricter than db_ident_match: used on its own."""
    _e, _R, S, _S = _lazy()
    ident, _scopes = ident_and_scopes(name)
    norm = lambda x: re.sub(r"^(g_|vtbl_|s_|k)?_*", "", x.lower())
    il = norm(ident)
    if len(il) < 4:
        return None
    for nm in rev.get(va, ()):
        q = S.demangle_qual(nm) or nm
        if norm(q.split("::")[-1].split("(")[0]) == il:
            return nm
    return None


def db_ident_match(name, va, rev):
    _e, _R, S, _S = _lazy()
    ident, _scopes = ident_and_scopes(name)
    il = ident.lower().lstrip("_")
    for nm in rev.get(va, ()):
        q = S.demangle_qual(nm) or nm
        last = q.split("::")[-1].lower().lstrip("_")
        if last == il or (len(il) >= 5 and (il in last or last in il)):
            return nm
    return None


def local_align(orig_refs, our_refs):
    """Re-align both reference sequences (like Resolver._align_round) but report the gap length
    of every pairing and a positional pairing when a whole kind-sequence lines up.
    -> {our symbol name: {va: {'gap': n} | {'positional': True}}}"""
    import difflib
    out = collections.defaultdict(lambda: collections.defaultdict(dict))
    for kind in ("call", "data"):
        O = [x for x in orig_refs if x[0] == kind]
        U = [x for x in our_refs if x[0] == kind and not x[2].startswith(EH_OURS)]
        ko = [("v", int(x[2], 16)) for x in O]
        ku = [("v", int(x[3], 16)) if x[3] else ("u", x[2], j) for j, x in enumerate(U)]
        sm = difflib.SequenceMatcher(None, ko, ku, autojunk=False)
        prev_o, prev_u = 0, 0
        for (bo, bu, n) in sm.get_matching_blocks():
            go, gu = O[prev_o:bo], U[prev_u:bu]
            if go and len(go) == len(gu) and all(x[1] == y[1] for x, y in zip(go, gu)):
                for x, y in zip(go, gu):
                    if y[3] is None:
                        out[y[2]][int(x[2], 16)]["gap"] = len(go)
            prev_o, prev_u = bo + n, bu + n
        if O and len(O) == len(U) and all(x[1] == y[1] for x, y in zip(O, U)):
            for x, y in zip(O, U):
                if y[3] is None:
                    out[y[2]][int(x[2], 16)]["positional"] = True
    return out


def sibling_annotations():
    """(ident, last real scope) -> Counter(va) over every slice source."""
    _e, R, _S, _S2 = _lazy()
    sib = collections.defaultdict(collections.Counter)
    for d in sorted(glob.glob(os.path.join(ROOT, "match", "slices", "*"))):
        paths = glob.glob(os.path.join(d, "*.cpp")) + glob.glob(os.path.join(d, "*.h"))
        for ident, scopes, va, _loc, _pt in R.source_annotations(paths):
            real = [x for x in scopes if x != "<anon>"]
            sib[(ident, real[-1] if real else "")][va] += 1
    return sib


def tier_of(usage, cands):
    """Best (tier, va, evidence) among a symbol's candidates, or None."""
    best = None
    for va, e in cands.items():
        tags = {x.split(":")[0] for x in e}
        if "arity-MISMATCH" in tags:
            continue
        aligned = bool(tags & {"align-1gap", "align-weak", "in-orig-refs", "positional"})
        if "db-name-unique" in tags and not aligned:
            if "arity-ok" in tags or (usage == ["data"] and "arity-MISMATCH" not in tags):
                t = 2 if "arity-ok" in tags else 3
                if best is None or t < best[0]:
                    best = (t, va, e)
            continue
        if not aligned:
            continue
        corro = bool(tags & {"db-name", "sibling-ann", "slice-consensus"})
        gaps = [int(x.split(":")[1]) for x in e if x.startswith("gap:")]
        gap = min(gaps) if gaps else (1 if "align-1gap" in tags else 99)
        if "positional" in tags:
            gap = min(gap, 2)
        if "hex-name" in tags:
            t = 1
        elif corro:
            t = 2
        elif usage == ["data"]:
            t = 3 if gap <= 2 else 4
        elif "arity-ok" in tags and gap <= 2:
            t = 3
        else:
            t = 4
        if best is None or t < best[0]:
            best = (t, va, e)
    return best


def cmd_propose(a):
    equiv, R, S, SIG = _lazy()
    H = json.load(open(os.path.join(a.dir, "harvest.json")))
    ctx = equiv.context()
    img, rs = ctx["img"], ctx["res"]
    rev = _rev_names(equiv)
    sib = sibling_annotations()
    props = []
    by_slice_sym = collections.defaultdict(list)
    for r in H:
        if "unresolved reference" not in (r.get("reason") or ""):
            continue
        orig_vas = {int(x[2], 16) for x in r["orig_refs"]}
        la = local_align(r["orig_refs"], r["our_refs"])
        for u in r["unresolved"]:
            nm = u["name"]
            usage = u.get("usage") or []
            want_func = usage == ["call"] or bool(u.get("is_func"))
            strong = {int(x, 16) for x in u.get("cands", [])}
            weak = {int(x, 16) for x in u.get("weak", [])}
            pool = strong | weak | set(la.get(nm, {})) | (hex_full_addrs(nm) & orig_vas)
            name_unique = None
            if not pool:
                # no alignment at all: the one original reference of this kind whose name is ours
                kind = "call" if want_func else "data"
                eq = {int(x[2], 16): db_ident_equal(nm, int(x[2], 16), rev) for x in r["orig_refs"] if x[0] == kind}
                eq = {v: n_ for v, n_ in eq.items() if n_}
                if len(eq) == 1:
                    name_unique = next(iter(eq))
                    pool = {name_unique}
            cands = {}
            for v in sorted(pool):
                if not rs.plausible(v, want_func) and not (usage == ["data"] and img.in_image(v)):
                    continue
                e = []
                if hex_matches(nm, v):
                    e.append("hex-name")
                if v in strong:
                    e.append("align-1gap")
                if v in weak:
                    e.append("align-weak")
                if v in la.get(nm, {}):
                    g = la[nm][v]
                    if "gap" in g:
                        e.append("gap:%d" % g["gap"])
                        if v not in strong | weak:
                            e.append("align-weak")
                    if g.get("positional"):
                        e.append("positional")
                if v == name_unique:
                    e.append("db-name-unique:" + db_ident_equal(nm, v, rev)[:60])
                elif v in orig_vas and not (v in strong or v in weak or v in la.get(nm, {})):
                    e.append("in-orig-refs")
                m = db_ident_match(nm, v, rev)
                if m:
                    e.append("db-name:" + m[:60])
                ident, scopes = ident_and_scopes(nm)
                key = (ident, scopes[-1] if scopes else "")
                if sib[key].get(v):
                    e.append("sibling-ann:%d" % sib[key][v])
                if want_func:
                    exp, got = expected_ret(nm), callee_ret(v)
                    if exp is not None and got is not None:
                        if got == {exp}:
                            e.append("arity-ok:%d" % exp)
                        elif exp not in got:
                            e.append("arity-MISMATCH:exp%d got%s" % (exp, sorted(got)))
                cands["%08x" % v] = e
            p = {"slice": r["slice"], "va": r["va"], "sym": nm, "usage": usage, "note": u.get("note", ""),
                 "cands": cands, "hex_unreferenced": sorted("%08x" % v for v in hex_full_addrs(nm) - orig_vas)}
            props.append(p)
            by_slice_sym[(r["slice"], nm)].append(p)
    for _key, lst in by_slice_sym.items():
        cnt = collections.Counter(v for p in lst for v in p["cands"])
        for p in lst:
            for v, e in p["cands"].items():
                if cnt[v] >= 2:
                    e.append("slice-consensus:%d/%d" % (cnt[v], len(lst)))
    for p in props:
        p["decision"] = tier_of(p["usage"], p["cands"])
    # one address per (slice, symbol): the annotation is slice-wide
    choice = {}
    for key, lst in by_slice_sym.items():
        votes = collections.Counter()
        for p in lst:
            if p["decision"]:
                votes[p["decision"][1]] += 1
        if not votes:
            choice[key] = {"status": "none"}
            continue
        top = votes.most_common()
        if len(top) > 1 and top[0][1] == top[1][1]:
            choice[key] = {"status": "conflict", "votes": dict(votes)}
            continue
        va = top[0][0]
        tiers = [p["decision"][0] for p in lst if p["decision"] and p["decision"][1] == va]
        ev = sorted({x for p in lst if p["decision"] and p["decision"][1] == va for x in p["decision"][2]})
        choice[key] = {"status": "ok", "va": va, "tier": min(tiers), "evidence": ev,
                       "dissent": [p["va"] for p in lst if p["decision"] and p["decision"][1] != va],
                       "votes": dict(votes)}
    out = {"proposals": props, "choice": {"%s %s" % k: v for k, v in choice.items()}}
    json.dump(out, open(os.path.join(a.dir, "proposals.json"), "w"), indent=1)
    cnt = collections.Counter(v["status"] if v["status"] != "ok" else "tier%d" % v["tier"] for v in choice.values())
    lines = ["# resolve_leftover: proposals", "", "slice-symbol pairs: %s" % dict(sorted(cnt.items())), "",
             "| slice | symbol | usage | VA | tier | evidence |", "|---|---|---|---|---|---|"]
    for key in sorted(choice, key=lambda k: (choice[k].get("tier", 9), k)):
        v = choice[key]
        if v["status"] == "ok":
            lines.append("| %s | `%s` | %s | %s | %d | %s |" % (key[0], key[1][:70], "/".join(by_slice_sym[key][0]["usage"]),
                                                             v["va"], v["tier"], ", ".join(v["evidence"])[:140]))
    open(os.path.join(a.dir, "propose.md"), "w").write("\n".join(lines) + "\n")
    print("proposals: %s -> %s" % (dict(sorted(cnt.items())), os.path.join(a.dir, "proposals.json")))


# ====================================================================== apply

def find_decls(paths):
    """Every annotatable declaration in the slice sources (file, namespace and class scope, plus
    'extern' declarations inside function bodies):
    [(ident, scopes, path, last physical line (1-based), logical code, params text,
      existing annotation VA or None, pieces)]  where pieces is None for a single declaration or
    [(ident, text-without-';')] when the line holds several declarators/statements."""
    _e, R, _S, _S2 = _lazy()
    out = []
    for path in paths:
        if not os.path.exists(path):
            continue
        lines = open(path, encoding="utf-8", errors="replace").read().split("\n")
        scopes, depth, pending, in_block, buf, logical = [], 0, None, False, None, []
        for ln, raw in enumerate(lines, 1):
            line = raw
            if in_block:
                if "*/" in line:
                    line = line[line.index("*/") + 2:]
                    in_block = False
                else:
                    continue
            code, _, comment = line.partition("//")
            code = re.sub(r"/\*.*?\*/", "", code)
            if "/*" in code:
                code = code[:code.index("/*")]
                in_block = True
            code = re.sub(r'"(\\.|[^"\\])*"', '""', code)
            if buf is not None:
                buf = (buf[0], buf[1] + " " + code.strip(), buf[2] + " " + comment, ln)
            else:
                buf = (ln, code, comment, ln)
            if buf[1].count("(") > buf[1].count(")") and ln - buf[0] < 12:
                continue
            logical.append(buf)
            buf = None
        if buf is not None:
            logical.append(buf)
        prev_code = ""
        for ln, code, comment, last in logical:
            va = None
            for m in R.ADDR_IN_COMMENT.finditer(comment):
                v = int(m.group(1) or m.group(2), 16)
                if 0x401000 <= v < 0x1900000:
                    va = v
                    break
            cm = re.search(r"\b(class|struct|union|namespace)\s+(?:__declspec\([^)]*\)\s*)?([A-Za-z_]\w*)?[^;()]*$", code)
            if cm and "(" not in code.split(cm.group(0))[0][-1:]:
                pending = cm.group(2) or "<anon>"
            elif re.search(r'extern\s*""\s*\{', code) and not pending:
                pending = "<anon>"                       # extern "C" { ... }: no scope
            c = code.strip()
            in_body = depth > (scopes[-1][1] if scopes else 0)     # braces that are not a class/namespace
            is_decl = c and ";" in c and "{" not in c and "}" not in c and (not in_body or c.startswith("extern")) and \
                not c.startswith(("#", "typedef", "using", "return", "friend"))
            if is_decl and ("(" in c or re.match(r"(extern|static)\b", c) or scopes):
                cls = [sc for sc, _d in scopes]
                stmts = [x.strip() for x in c.split(";") if x.strip()]
                if len(stmts) > 1 and "(" not in c:               # 'extern int a; extern int b;'
                    pieces = []
                    for st in stmts:
                        m = re.search(r"([A-Za-z_]\w*)\s*(\[[^\]]*\]\s*)*$", st)
                        if m:
                            pieces.append((m.group(1), st))
                    for ident, _t in pieces:
                        out.append((ident, tuple(cls), path, last, code, None, va, pieces))
                    continue
                sp = _split_declarators(c) if "(" not in c else None
                if sp and len(sp[1]) > 1:                          # 'extern char a[], b[];'
                    pieces = []
                    for dcl in sp[1]:
                        m = re.search(r"([A-Za-z_]\w*)\s*(\[[^\]]*\]\s*)*$", dcl)
                        if m:
                            pieces.append((m.group(1), "%s %s" % (sp[0], dcl)))
                    for ident, _t in pieces:
                        out.append((ident, tuple(cls), path, last, code, None, va, pieces))
                    continue
                head = c[:c.index("(")] if "(" in c else c
                pc = prev_code.strip()        # 'static NAMED *' on its own line: a split prototype
                split_proto = pc and "(" not in pc and not pc.endswith((";", "{", "}", ")", ",")) and not pc.startswith("#")
                stmt = "(" in c and (re.search(r"[=.]|->", head) or
                                     (len(re.findall(r"[A-Za-z_]\w*", head)) < 2 and not scopes and "operator" not in head
                                      and not split_proto))
                ident = R._decl_ident(code) if not stmt else None
                if ident and not re.match(r"(if|for|while|switch|sizeof|return)$", ident):
                    if "::" in ident:
                        parts = ident.split("::")
                        cls, ident = cls + parts[:-1], parts[-1]
                    out.append((ident, tuple(cls), path, last, code, R._decl_params(code), va, None))
            for ch in code:
                if ch == "{":
                    depth += 1
                    if pending:
                        scopes.append((pending, depth))
                        pending = None
                elif ch == "}":
                    if scopes and scopes[-1][1] == depth:
                        scopes.pop()
                    depth -= 1
            if ";" in code and pending and "{" not in code:
                pending = None
            prev_code = code
    return out


def _split_declarators(code):
    """'extern char a[], *b, c;' -> ('extern char', ['a[]', '*b', 'c']) or None."""
    c = code.strip().rstrip(";").strip()
    if "(" in c or "=" in c or "{" in c:
        return None
    parts, d, cur = [], 0, ""
    for ch in c:
        if ch in "<[":
            d += 1
        elif ch in ">]":
            d -= 1
        if ch == "," and d == 0:
            parts.append(cur.strip())
            cur = ""
        else:
            cur += ch
    parts.append(cur.strip())
    first = parts[0]
    m = re.search(r"([A-Za-z_]\w*)\s*(\[[^\]]*\]\s*)*$", first)
    if not m:
        return None
    i = m.start(1)
    while i > 0 and first[i - 1] in "*& \t":
        i -= 1
    base = first[:i].strip()
    if not base:
        return None
    return base, [first[i:].strip()] + parts[1:]


def _scope_ok(decl_scopes, sym_scopes):
    real = [x for x in decl_scopes if x != "<anon>"]
    if real:
        return real[-1] in sym_scopes
    return not sym_scopes


def dummy_scope(sym, siblings=()):
    """Scope name for a dummy-struct annotation of a member symbol.  The resolver accepts any
    scope fragment of the mangled name, so for a template instantiation a template-argument
    fragment distinguishes it from the other instantiations: prefer the first identifier-like
    fragment after the class name that no sibling symbol (same identifier) shares, else the class."""
    _e, R, _S, _S2 = _lazy()
    cls = class_of(sym)
    frags = R.mangled_scopes(sym)
    others = [set(R.mangled_scopes(o)) for o in siblings if o != sym]
    if "?$" in sym and cls in frags:
        i = frags.index(cls)
        cands = [f for f in frags[i + 1:] if re.match(r"[A-Za-z_]\w*$", f) and f != cls]
        for f in cands:
            if not any(f in o for o in others):
                return f
        if cands:
            return cands[0]
    return cls if cls and re.match(r"[A-Za-z_]\w*$", cls) else None


def plan_edits(sid, targets, decls, existing_annots):
    """targets: {symbol: (va, tier)} -> (edits [(path, line, kind, payload)], notes {symbol: note}).
    kind: 'append' (comment on that line), 'split' (rewrite a multi-declaration line, payload
    [(ident, text)], {ident: tag}), 'block' (dummy structs / canonical declarations appended)."""
    _e, R, _S, SIG = _lazy()
    ctx = _lazy()[0].context()
    rs = ctx["res"]
    edits, notes, blocks, members, splits, planned = [], {}, [], {}, {}, []
    cpp = os.path.join(ROOT, "match", "slices", sid, sid + ".cpp")
    src = open(cpp, encoding="utf-8", errors="replace").read() if os.path.exists(cpp) else ""
    n = 1
    while "__equiv_ann%d" % n in src:
        n += 1
    ns = "__equiv_ann%d" % n
    sibs = collections.defaultdict(list)
    for sym in targets:
        sibs[ident_and_scopes(sym)[0]].append(sym)
    for sym, (va, tier) in sorted(targets.items()):
        ident, scopes = ident_and_scopes(sym)
        cands = [d for d in decls if d[0] == ident and (_scope_ok(d[1], scopes) or not sym.startswith("?"))]
        if "?$" in sym and sym.startswith("?") and scopes:
            cands = []          # a template's declaration can hold one address: use a dummy scope per instantiation
        if len({(d[2], d[3]) for d in cands}) > 1:
            try:
                mt = SIG.parse(sym).ptypes
            except Exception:
                mt = None
            sel = [d for d in cands if R.params_match(mt, R.norm_text_params(d[5]))]
            if sel:
                cands = sel
        cands = list({(d[2], d[3]): d for d in cands}.values())
        tag = "// 0x%08x (equiv t%d)" % (va, tier)
        if not cands:
            if sym in CANON_DECL:
                blocks.append("%s   %s" % (CANON_DECL[sym], tag))
                planned.append((sym, ident, (), va, "block", R._decl_params(CANON_DECL[sym])))
            elif sym.startswith(("??0", "??1")) and class_of(sym) and re.match(r"[A-Za-z_]\w*$", class_of(sym)):
                sc = class_of(sym)                     # a ctor/dtor can only be declared under its own class name
                ident = ident.lstrip("?$") if not ident.startswith("~") else "~" + ident[1:].lstrip("?$")
                members.setdefault(sc, {}).setdefault((ident, va), "    %s();   %s" % (ident, tag))
                planned.append((sym, ident, (ns, sc), va, "block", ""))
            elif sym.startswith("?") and scopes and dummy_scope(sym, sibs[ident]) and re.match(r"[A-Za-z_]\w*$", ident):
                sc = dummy_scope(sym, sibs[ident])
                members.setdefault(sc, {}).setdefault((ident, va), "    void %s();   %s" % (ident, tag))
                planned.append((sym, ident, (ns, sc), va, "block", ""))
            elif sym.startswith("??") and scopes and ident in ("operator=", "operator==", "operator!=", "operator[]", "operator+", "operator-", "operator*") \
                    and re.match(r"[A-Za-z_]\w*$", scopes[-1]):
                sc = scopes[-1]
                members.setdefault(sc, {}).setdefault((ident, va), "    void %s(int);   %s" % (ident, tag))
                planned.append((sym, ident, (ns, sc), va, "block", "int"))
            else:
                notes[sym] = "no declaration of %s found in the slice sources" % ident
            continue
        other = [d for d in cands if d[6] is not None and d[6] != va]
        todo = [d for d in cands if d[6] is None]
        if other and not todo:
            notes[sym] = "declaration already annotated with a different address (%s)" % ", ".join("%08x" % d[6] for d in other)
            continue
        if not todo:
            notes[sym] = "already annotated"
            continue
        if len(todo) > 1 and len({d[5] for d in todo}) > 1:
            notes[sym] = "ambiguous: %d overload declarations match" % len(todo)
            continue
        for d in todo:
            if d[7]:
                splits.setdefault((d[2], d[3]), (d[7], {}))[1][ident] = tag
            else:
                edits.append((d[2], d[3], "append", tag))
            planned.append((sym, ident, d[1], va, "%s:%d" % (os.path.basename(d[2]), d[3]), d[5]))
    # simulate the resolver on existing + planned annotations; drop what it would not accept
    annots = list(existing_annots) + [(i, sc, v, loc, pt) for (_s, i, sc, v, loc, pt) in planned]
    bad = set()
    for sym, ident, sc, va, loc, pt in planned:
        got, how = rs.by_annotation(sym, annots, True)
        if got is None:
            got, how = rs.by_annotation(sym, annots, False)
        if got != va:
            bad.add(sym)
            notes[sym] = "resolver would not pick %08x from the annotations (%s)" % (va, how)
    if bad:
        keep = {(i, sc[-1] if sc else None, v) for (s2, i, sc, v, _l, _p) in planned if s2 not in bad}
        edits = [e for e in edits if e[2] != "append" or any(e[3].startswith("// 0x%08x" % v) for (_i, _s, v) in keep)]
        for sc, ds in list(members.items()):
            for (i, v) in list(ds):
                if (i, sc, v) not in keep:
                    del ds[(i, v)]
            if not ds:
                del members[sc]
        for key, (pieces, tags) in list(splits.items()):
            for i in list(tags):
                if not any(tags[i].startswith("// 0x%08x" % v) for (_i, _s, v) in keep):
                    del tags[i]
            if not tags:
                del splits[key]
    for (path, ln), payload in splits.items():
        edits.append((path, ln, "split", payload))
    if blocks or members:
        text = []
        if members:
            text.append("namespace %s {   // address annotations for the equivalence checker; never referenced" % ns)
            for sc, ds in sorted(members.items()):
                text += ["struct %s {" % sc] + list(ds.values()) + ["};"]
            text.append("}")
        text += blocks
        edits.append((cpp, None, "block", "\n".join(text)))
    return edits, notes


def apply_edits(edits):
    by_path = collections.defaultdict(list)
    for e in edits:
        by_path[e[0]].append(e)
    originals = {}
    for path, es in by_path.items():
        text = open(path, encoding="utf-8", errors="replace").read()
        originals[path] = text
        lines = text.split("\n")
        for _p, ln, kind, payload in sorted(es, key=lambda e: -(e[1] or 10 ** 9)):
            if kind == "append":
                lines[ln - 1] = lines[ln - 1].rstrip() + "   " + payload
            elif kind == "split":
                pieces, tags = payload
                indent = re.match(r"\s*", lines[ln - 1]).group(0)
                new = []
                for ident, text in pieces:
                    l = "%s%s;" % (indent, text)
                    if ident in tags:
                        l += "   " + tags[ident]
                    new.append(l)
                old_comment = lines[ln - 1].partition("//")[2]
                if old_comment.strip():
                    new[0] += "   //" + old_comment
                lines[ln - 1:ln] = new
            elif kind == "block":
                if lines and lines[-1] == "":
                    lines.insert(len(lines) - 1, "\n" + payload)
                else:
                    lines.append("\n" + payload)
        open(path, "w", encoding="utf-8").write("\n".join(lines))
    return originals


def run_all(sid):
    """-> (ok, text, {va: status}) for the slice manifest."""
    man = os.path.join(ROOT, "match", "slices", sid, "manifest.txt")
    if not os.path.exists(man):
        return True, "no manifest", {}
    import time
    for _try in range(120):
        r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "matching", "run_all.py"), "--manifest", man],
                           capture_output=True, text=True)
        txt = r.stdout + r.stderr
        if "already running" not in txt:
            break
        time.sleep(5)                 # another run_all holds work/run_all.lock: wait for it
    res = {}
    try:
        res = {k: v["status"] for k, v in json.load(open(os.path.join(ROOT, "work", "verify_results.json"))).items()}
    except Exception:
        pass
    m = re.search(r"(\d+) / (\d+) functions byte-exact", txt)
    ok = bool(m) and m.group(1) == m.group(2)
    return ok, txt[-1500:], res


def affected_slices(sid, paths):
    """The slice plus every slice whose source includes one of the edited headers."""
    out = {sid}
    for p in paths:
        if not p.endswith(".h"):
            continue
        base = os.path.basename(p)
        for cpp in glob.glob(os.path.join(ROOT, "match", "slices", "*", "*.cpp")):
            try:
                if re.search(r'#\s*include\s+"[^"]*%s"' % re.escape(base), open(cpp, encoding="utf-8", errors="replace").read()):
                    out.add(os.path.basename(os.path.dirname(cpp)))
            except OSError:
                pass
    return sorted(out)


def run_all_many(sids):
    oks, txts, res = [], [], {}
    for s2 in sids:
        ok, txt, r = run_all(s2)
        oks.append(ok)
        txts.append("%s: %s" % (s2, txt.strip().splitlines()[-1] if txt.strip() else ""))
        res.update(r)
    return all(oks), "\n".join(txts), res


def cmd_apply(a):
    equiv, R, S, SIG = _lazy()
    P = json.load(open(os.path.join(a.dir, "proposals.json")))
    H = {(r["slice"], r["va"]): r for r in json.load(open(os.path.join(a.dir, "harvest.json")))}
    per_slice = collections.defaultdict(dict)
    for key, v in P["choice"].items():
        sid, sym = key.split(" ", 1)
        if v["status"] == "ok" and v["tier"] <= a.max_tier and (not a.only or sid in a.only):
            per_slice[sid][sym] = (int(v["va"], 16), v["tier"])
    report = {}
    for sid in sorted(per_slice):
        d = os.path.join(ROOT, "match", "slices", sid)
        paths = glob.glob(os.path.join(d, "*.cpp")) + glob.glob(os.path.join(d, "*.h")) + S.sibling_headers(S.source_path(sid))
        decls = find_decls(paths)
        edits, notes = plan_edits(sid, per_slice[sid], decls, R.source_annotations(paths))
        rec = {"planned": len(edits), "notes": notes, "edits": [(os.path.relpath(e[0], ROOT), e[1], e[2], e[3] if e[2] != "split" else e[3][1]) for e in edits]}
        report[sid] = rec
        print("%s: %d edits, %d skipped" % (sid, len(edits), len(notes)), flush=True)
        if a.dry_run or not edits:
            continue
        originals = apply_edits(edits)
        touched = affected_slices(sid, [e[0] for e in edits])
        ok, txt, after = run_all_many(touched)
        if not ok:
            for p, t in originals.items():
                open(p, "w", encoding="utf-8").write(t)
            ok0, txt0, before = run_all_many(touched)
            if ok0:
                rec["verify"] = "REVERTED: byte-exact check failed after the edit\n" + txt
                print("  REVERTED (%s)" % txt.strip().splitlines()[-1], flush=True)
                continue
            bad_before = {k for k, v in before.items() if v != "MATCH"}
            bad_after = {k for k, v in after.items() if v != "MATCH"}
            if bad_after <= bad_before:
                apply_edits(edits)
                rec["verify"] = "applied; pre-existing non-matches unchanged: %s" % sorted(bad_before)
            else:
                rec["verify"] = "REVERTED: new non-matches %s" % sorted(bad_after - bad_before)
                print("  REVERTED (new non-matches)", flush=True)
                continue
        else:
            rec["verify"] = "byte-exact unchanged (%s)" % txt.strip().splitlines()[-1]
        # re-run the resolver for this slice's blocked functions
        after = {}
        for (s2, va), r in H.items():
            if s2 != sid or "unresolved reference" not in (r.get("reason") or ""):
                continue
            try:
                t = equiv.prepare(sid, int(va, 16), log=lambda *x: None)
                after[va] = {"verdict": t.verdict, "reason": getattr(t, "reason", None),
                             "unresolved": [u.split(" [")[0] for u in getattr(t, "unresolved", [])]}
            except Exception as e:
                after[va] = {"verdict": "ERROR", "reason": str(e)[:200]}
        rec["after"] = after
        freed = sum(1 for v in after.values() if "unresolved reference" not in (v.get("reason") or ""))
        print("  verified; %d/%d functions no longer blocked by unresolved references" % (freed, len(after)), flush=True)
    json.dump(report, open(os.path.join(a.dir, "apply.json"), "w"), indent=1)
    print("wrote", os.path.join(a.dir, "apply.json"))


# ====================================================================== report

STRUCTURAL = {
    "___rdtsc": "intrinsic: the original executes `rdtsc` inline; our source calls a helper (add #pragma intrinsic(__rdtsc))",
    "_isspace": "the original inlines the CRT ctype-table lookup; there is no call to point at",
    "_gensym": "parser noise",
}


def cmd_report(a):
    """Final table: status per function from --final (a harvest taken after apply), reasons per
    still-blocking symbol from the proposals/apply logs of every round in --rounds (default: DIR)."""
    H0 = json.load(open(os.path.join(a.dir, "harvest.json")))
    HF = json.load(open(a.final)) if a.final else H0
    rounds = a.rounds or [a.dir]
    choice, notes, props = {}, {}, {}
    for d in rounds:
        try:
            P = json.load(open(os.path.join(d, "proposals.json")))
        except OSError:
            continue
        choice.update(P["choice"])
        for p in P["proposals"]:
            props.setdefault((p["slice"], p["va"], p["sym"]), p)
        try:
            A = json.load(open(os.path.join(d, "apply.json")))
            for sid, rec in A.items():
                for sym, n in rec.get("notes", {}).items():
                    notes[(sid, sym)] = n
        except OSError:
            pass
    initial = {(r["slice"], r["va"]): r for r in H0 if "unresolved reference" in (r.get("reason") or "")}
    final = {(r["slice"], r["va"]): r for r in HF}
    fn_rows, outcome, sym_bucket = [], collections.Counter(), collections.Counter()
    seen_syms = set()
    for key in sorted(initial):
        r = final.get(key, initial[key])
        reason = r.get("reason") or ""
        if "unresolved reference" not in reason:
            st = "unblocked" + ("" if r.get("verdict") is None else " (now: %s)" % reason[:50])
            outcome["unblocked" if r.get("verdict") is None else "unblocked, other UNSUPPORTED"] += 1
            fn_rows.append((key[0], key[1], st, []))
            continue
        left = [u["name"] for u in r["unresolved"]]
        why = []
        for sname in left:
            c = choice.get("%s %s" % (key[0], sname), {"status": "none"})
            p = props.get((key[0], key[1], sname))
            n = notes.get((key[0], sname))
            if sname in STRUCTURAL:
                b, txt = "E", STRUCTURAL[sname]
            elif c["status"] == "conflict":
                b, txt = "C", "functions of this slice align it to different originals %s" % c.get("votes")
            elif n and ("would not pick" in n or "no declaration" in n or "already annotated" in n or "ambiguous" in n):
                b, txt = "S", n
            elif c["status"] == "ok" and c["tier"] >= 4:
                b, txt = "P", "plausible only: %s (%s)" % (c["va"], ", ".join(c["evidence"])[:70])
            elif p and any(any(x.startswith("arity-MISMATCH") for x in e) for e in p["cands"].values()):
                v = [(vv, [x for x in e if x.startswith("arity-MISMATCH")][0]) for vv, e in p["cands"].items() if any(x.startswith("arity-MISMATCH") for x in e)]
                b, txt = "M", "aligned to %s but our declaration's convention/args disagree (%s)" % (v[0][0], v[0][1])
            elif p and p.get("hex_unreferenced"):
                b, txt = "H", "name says %s but the original never references it" % ",".join(p["hex_unreferenced"])
            elif c["status"] == "ok":
                b, txt = "S", "applied/accepted but still unresolved (%s)" % (n or "see apply.json")
            else:
                oc = sum(1 for x in r["orig_refs"] if x[0] == "call"); uc = sum(1 for x in r["our_refs"] if x[0] == "call")
                b, txt = "D", "no candidate: reference sequences do not pair (orig %d calls, ours %d)" % (oc, uc)
            why.append("%s: [%s] %s" % (sname[:50], b, txt[:90]))
            if (key[0], sname) not in seen_syms:
                seen_syms.add((key[0], sname))
                sym_bucket[b] += 1
        outcome["blocked"] += 1
        fn_rows.append((key[0], key[1], "blocked (%d left)" % len(left), why))
    legend = {"E": "structural (intrinsic / inlined CRT / not a symbol)", "C": "slice-level conflict between functions",
              "S": "source/annotation mechanism limit (see note)", "P": "plausible candidate only, not applied",
              "M": "declaration convention/arg count disagrees with the aligned original callee",
              "H": "hex address in name not referenced by the original", "D": "no alignment candidate at all"}
    lines = ["# resolve_leftover report", "", "Initially blocked functions: %d" % len(initial), "",
             "| outcome | functions |", "|---|---:|"] + ["| %s | %d |" % kv for kv in sorted(outcome.items())]
    lines += ["", "## still-blocking symbols by bucket (distinct per slice)", "", "| bucket | meaning | symbols |", "|---|---|---:|"]
    lines += ["| %s | %s | %d |" % (b, legend[b], n) for b, n in sorted(sym_bucket.items())]
    lines += ["", "## per function", "", "| slice | va | status | why |", "|---|---|---|---|"]
    for sid, va, st, why in fn_rows:
        lines.append("| %s | %s | %s | %s |" % (sid, va, st, "<br>".join(why)))
    open(os.path.join(a.dir, "report.md"), "w").write("\n".join(lines) + "\n")
    print("\n".join(lines[:16]))
    print("wrote", os.path.join(a.dir, "report.md"))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    h = sub.add_parser("harvest"); h.add_argument("--worklist"); h.add_argument("slices", nargs="*")
    h.add_argument("--jobs", type=int, default=6); h.add_argument("--dir", default=DEFAULT_DIR)
    p = sub.add_parser("propose"); p.add_argument("--dir", default=DEFAULT_DIR)
    ap_ = sub.add_parser("apply"); ap_.add_argument("--dir", default=DEFAULT_DIR); ap_.add_argument("--max-tier", type=int, default=3)
    ap_.add_argument("--dry-run", action="store_true"); ap_.add_argument("--only", nargs="*")
    r = sub.add_parser("report"); r.add_argument("--dir", default=DEFAULT_DIR)
    r.add_argument("--final", help="harvest.json taken after the apply rounds"); r.add_argument("--rounds", nargs="*")
    a = ap.parse_args(argv)
    return {"harvest": cmd_harvest, "propose": cmd_propose, "apply": cmd_apply, "report": cmd_report}[a.cmd](a)


if __name__ == "__main__":
    sys.exit(main())
