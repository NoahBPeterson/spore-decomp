#!/usr/bin/env python3
"""vtable signal for modmap.py (design signal 3, class membership): place the virtual methods of
a class in the object file that owns the class.

Rule.  Retail has no RTTI (built /GR-), so vtables come from work/xmatch/tables.json `ret_vt`
(4,731 runs of code pointers stored from code, with their slot functions) and the functions that
store each vtable address (a scan of .text for the vtable VA, cached in
work/migrate/vtable_cache.json, regenerated with .venv/bin/python when missing).
  1. Vtable -> class: the mangled `??_7Class@NS@@6B@` name in symbols/pdb_vtables.json (319
     vtables), else the class of an anchored constructor/destructor (`A::B::B`, `A::B::~B`) that
     stores the vtable address, provided they all agree (530).  symbols/vtable_names.txt uses
     ModAPI namespaces (Simulator::, UI::) that do not match the PDB names, so it is not used.
  2. Class -> module: a class is OWNED by M when it has >= 2 unique anchored methods (not comdat,
     not sandwiched; name minus the last `::` component, templates and `anonymous namespace'
     handled by a bracket-aware split) and >= 90% of them are in M.  A class with exactly one
     unique anchored method is a WEAK owner (the `class1` tiers).
  3. Slot function f gets a candidate from each kind of evidence: `class` (every vtable holding f
     has an owned class, all with one module), `class1` (same with weak owners), `ref` (f's
     vtables are stored by confidently placed functions, conf >= 0.9, of one module), and `vote`
     (the other slots that sit in a single vtable and are placed at conf >= 0.9 are all in one
     module).  Slots of size <= 6 are skipped.  A function that sits in a vtable of unknown
     class and has no unanimous vote gets nothing, which is what excludes inherited slots, pure
     stubs and shared implementations.  A class candidate is vetoed when >= 3 votes say another
     module.
  4. Only unassigned functions are set (ctx.set may override a lower-confidence assignment).

Tiers (internal hold-out = every hidden anchor that is a slot function, whether or not interp
had already placed it; three seeds 1/2/3 of --holdout 0.2; right/wrong summed):
  vtable             0.8  class evidence                      953 right 10 wrong = 98.9%
  vtable-refvote     0.8  ref and vote agree                   64 right  2 wrong = 97.0%
  vtable-class1vote  0.5  weak owner and vote agree            45 right  3 wrong = 93.8%
  vtable-class1      0.5  weak owner only                      10 right  1 wrong = 90.9%
  vtable-vote        0.5  vote with >= 2 voters               173 right 13 wrong = 93.0%
  vtable-vote1       0.4  vote with one voter                  77 right  8 wrong = 90.6%
  (ref alone, 18/26 = 69%, is not used.)
Full run (anchor,interp,vtable,inst; interp as of this writing): vtable 961 fn / 178 KB,
refvote 223 / 45, class1vote 17 / 7, class1 55 / 9, vote 1,740 / 142, vote1 1,395 / 120; total
+4,391 functions (+4.8 points by count, +3.0 by size: 27.8% / 42.4% -> 32.6% / 45.4%).  The
modmap --holdout per-how lines only see hidden anchors interp missed, so they are small samples
(`vtable` 205/208 over the three seeds).  Runs in about 5 s.
Main failure modes of `vtable`: `scalar deleting destructor` slots (the retail linker kept
another TU's COMDAT copy) and slots inherited from an abstract base whose own vtable was
optimised away.
"""
import bisect, collections, json, os, re, struct, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)
CACHE = W("work/migrate/vtable_cache.json")

MAIN_CONF = 0.8
WEAK_CONF = 0.5
MIN_SLOT_SIZE = 7          # size <= 6 is a thunk / stub
OWN_MIN_N = 2              # unique anchored methods needed to call a class owned
OWN_MIN_SHARE = 0.9


# ---- vtable cache (retail vtables: slots + the functions that store the vtable address) --------
def make_cache():
    import pefile
    pe = pefile.PE(W("work/SporeApp.analysis.bin"), fast_load=True)
    base = pe.OPTIONAL_HEADER.ImageBase
    img = pe.get_memory_mapped_image()
    secs = {s.Name.rstrip(b"\0").decode(): (base + s.VirtualAddress, base + s.VirtualAddress + s.Misc_VirtualSize)
            for s in pe.sections}
    vt = json.load(open(W("work/xmatch/tables.json")))["ret_vt"]
    ret = json.load(open(W("work/xmatch/retail.json")))
    order = sorted(int(k, 16) for k in ret)
    tlo, thi = secs[".text"]
    text = bytes(img[tlo - base:thi - base])
    want = {struct.pack("<I", int(v, 16)): v for v in vt}
    refs = {v: set() for v in vt}
    for i in range(len(text) - 3):
        v = want.get(text[i:i + 4])
        if v:
            va = tlo + i
            j = bisect.bisect_right(order, va) - 1
            if j >= 0 and va < order[j] + ret["%08x" % order[j]]["size"]:
                refs[v].add(order[j])
    out = {v: {"slots": vt[v], "refs": ["%08x" % x for x in sorted(refs[v])]} for v in vt}
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    from headers import dump_json_atomic
    dump_json_atomic(out, CACHE)


def load_vtables():
    if not os.path.exists(CACHE):
        try:
            make_cache()
        except ImportError:
            py = W(".venv/bin/python")
            subprocess.check_call([py, os.path.abspath(__file__), "--make-cache"])
    return json.load(open(CACHE))


# ---- names -----------------------------------------------------------------------------------
def split_top(name):
    """Split a demangled name on top-level '::' (not inside <> or () or `...')."""
    parts, cur, depth, i = [], "", 0, 0
    while i < len(name):
        c = name[i]
        if c == "`" and depth == 0:
            j = name.find("'", i)
            j = len(name) - 1 if j < 0 else j
            cur += name[i:j + 1]
            i = j + 1
            continue
        if c in "<(":
            depth += 1
        elif c in ">)":
            depth -= 1
        if depth == 0 and name.startswith("::", i):
            parts.append(cur)
            cur = ""
            i += 2
            continue
        cur += c
        i += 1
    parts.append(cur)
    return parts


def class_of(name):
    """Class path of a method name ('A::B::f' -> 'A::B'), or None for free functions / odd names."""
    if not name or name.startswith("$") or name.startswith("`vector") or name.startswith("`dynamic"):
        return None
    p = split_top(name)
    if len(p) < 2:
        return None
    return "::".join(p[:-1])


def method_of(name):
    return split_top(name)[-1]


def unmangle_vtable(m):
    """??_7WinGrid@UTFWinControls@EA@@6B@ -> 'EA::UTFWinControls::WinGrid' (None for templates)."""
    if not m.startswith("??_7") or m.startswith("??_7?$"):
        return None
    body = m[4:].split("@@", 1)[0]
    parts = body.split("@")
    if not parts or any((not p) or p.startswith("?") for p in parts):
        return None
    return "::".join(reversed(parts))


def ctor_class(name):
    """Class named by a constructor / destructor anchor: 'A::B::B' / 'A::B::~B' -> 'A::B'."""
    p = split_top(name or "")
    if len(p) < 2:
        return None
    last = p[-1]
    base = p[-2]
    # template classes: compare the name up to '<'
    b0 = base.split("<", 1)[0]
    l0 = last.lstrip("~").split("<", 1)[0]
    if last.startswith("`"):
        return None
    if b0 and b0 == l0:
        return "::".join(p[:-1])
    return None


# ---- class ownership ---------------------------------------------------------------------------
def class_owners(ctx):
    """{class: dict(module, n, total, dissent)} for classes owned by one module (>=2 unique anchored
    methods, >=90% in one module)."""
    cnt = collections.defaultdict(collections.Counter)
    for va, a in ctx.anchors.items():
        if a["comdat"] or a.get("sandwiched"):
            continue
        c = class_of(a["name"])
        if c:
            cnt[c][a["module"]] += 1
    owners = {}
    for c, mods in cnt.items():
        total = sum(mods.values())
        m, n = mods.most_common(1)[0]
        if total >= OWN_MIN_N and n >= OWN_MIN_SHARE * total:
            owners[c] = dict(module=m, n=n, total=total, dissent=total - n)
    ctx._vt_class_counts = cnt
    ctx._vt_weak_owners = {c: next(iter(m)) for c, m in cnt.items() if sum(m.values()) == 1}
    return owners


# ---- vtable -> class -----------------------------------------------------------------------------
def vtable_classes(ctx, vts):
    """{vtable va hex: (class, source)} from pdb_vtables mangled names, then constructor/destructor
    references (anchored ctors storing the vtable address)."""
    out = {}
    pv = json.load(open(W("symbols/pdb_vtables.json")))
    for va, e in pv.items():
        if va in vts:
            c = unmangle_vtable(e["name"])
            if c:
                out[va] = (c, "pdb")
    for va, v in vts.items():
        if va in out:
            continue
        votes = collections.Counter()
        for r in v["refs"]:
            a = ctx.anchors.get(int(r, 16))
            if a:
                c = ctor_class(a["name"])
                if c:
                    votes[c] += 1
        if len(votes) == 1:
            out[va] = (next(iter(votes)), "ctor")
    return out


def vtable_modules(ctx, vts, vcls, owners):
    """{vtable va hex: (module, source)}: the module a vtable's own methods live in.
    source 'class' = its class is owned by a module; 'ref' = the (confident) module of the
    functions that store its address."""
    nref = collections.Counter()           # function -> number of distinct vtables it stores
    for v in vts.values():
        for r in v["refs"]:
            nref[r] += 1
    out = {}
    for va, v in vts.items():
        c = vcls.get(va)
        if c and c[0] in owners:
            out[va] = (owners[c[0]]["module"], "class-" + c[1])
            continue
        if c and c[0] in ctx._vt_weak_owners:
            out[va] = (ctx._vt_weak_owners[c[0]], "class1-" + c[1])
            continue
        mods = collections.Counter()
        for r in v["refs"]:
            rv = int(r, 16)
            e = ctx.assign.get(rv)
            if not e or e["confidence"] < 0.9:
                continue
            if nref[r] > REF_MAX_VT or ctx.retail[rv] > REF_MAX_SIZE:
                continue
            mods[e["module"]] += 1
        if len(mods) == 1:
            out[va] = (next(iter(mods)), "ref")
    return out


def slot_users(vts):
    users = collections.defaultdict(list)
    for va, v in vts.items():
        for s in set(v["slots"]):
            users[int(s, 16)].append(va)
    return users


def predict(ctx, vts, vmod):
    """{slot function va: dict(class=module|None, ref=module|None, vote=(module, n)|None)} for every
    slot function that has at least one candidate (assigned or not)."""
    users = slot_users(vts)
    cand = {}
    stats = collections.Counter()
    for f, us in users.items():
        if ctx.retail.get(f, 0) < MIN_SLOT_SIZE:
            stats["small"] += 1
            continue
        c = {}
        # (1) class / ref evidence: every vtable the function sits in has a known module, all equal
        known = [vmod.get(u) for u in us]
        if all(k is not None for k in known):
            mods = {k[0] for k in known}
            if len(mods) == 1:
                if all(k[1].startswith("class-") for k in known):
                    kind = "class"
                elif all(k[1].startswith("class") for k in known):
                    kind = "class1"
                else:
                    kind = "ref"
                c[kind] = next(iter(mods))
            else:
                stats["conflict"] += 1
        # (2) vote: the confident assignments of the other slots of its vtables are unanimous
        votes = collections.Counter()
        for u in us:
            for s in set(vts[u]["slots"]):
                sv_ = int(s, 16)
                if sv_ == f or len(users[sv_]) != 1:
                    continue
                e = ctx.assign.get(sv_)
                if e and e["confidence"] >= 0.9:
                    votes[e["module"]] += 1
        if votes and len(votes) == 1:
            m, n = votes.most_common(1)[0]
            c["vote"] = (m, n)
        if c:
            cand[f] = c
    return cand, stats


def decide(c):
    """Combine the candidates of one function into (module, tier) or None."""
    cl, rf, vo = c.get("class"), c.get("ref"), c.get("vote")
    c1 = c.get("class1")
    if not cl and c1:
        if vo and vo[0] == c1:
            return c1, "vtable-class1vote"
        if rf == c1 or (not vo and not rf):
            return c1, "vtable-class1"
    if cl:
        if vo and vo[1] >= VETO_VOTES and vo[0] != cl:
            return None            # the vtable's other slots say a different module: inherited slot
        return cl, "vtable"
    if rf and vo and vo[0] == rf:
        return rf, "vtable-refvote"
    if vo and vo[1] >= 2:
        return vo[0], "vtable-vote"
    if vo:
        return vo[0], "vtable-vote1"
    return None


TIER_CONF = {"vtable": MAIN_CONF, "vtable-refvote": MAIN_CONF, "vtable-vote": WEAK_CONF,
             "vtable-ref": WEAK_CONF, "vtable-vote1": 0.4,
             "vtable-class1vote": WEAK_CONF, "vtable-class1": WEAK_CONF}
VETO_VOTES = 3
REF_MAX_VT = 3
REF_MAX_SIZE = 600


def apply(ctx):
    vts = load_vtables()
    owners = class_owners(ctx)
    vcls = vtable_classes(ctx, vts)
    vmod = vtable_modules(ctx, vts, vcls, owners)
    cand, stats = predict(ctx, vts, vmod)
    ctx._vt_owners, ctx._vt_classes, ctx._vt_vmod, ctx._vt_cand = owners, vcls, vmod, cand
    pred = {}
    for f, c in cand.items():
        d = decide(c)
        if d:
            pred[f] = d
    ctx._vt_pred = pred
    for f, (m, tier) in pred.items():
        if ctx.set(f, m, tier, TIER_CONF[tier]):
            stats["assigned-" + tier] += 1
    ctx.vtable_stats = dict(stats)
    if ctx.hidden and os.environ.get("VT_EVAL"):
        ev = collections.Counter()
        for f, a in ctx.hidden.items():
            p = pred.get(f)
            if p:
                ev[(p[1], p[0] == a["module"])] += 1
        for (tier, ok), n in sorted(ev.items()):
            print("  [vtable eval, all hidden slot functions] %-16s %s %d" % (tier, "right" if ok else "WRONG", n))


if __name__ == "__main__":
    if "--make-cache" in sys.argv:
        make_cache()
