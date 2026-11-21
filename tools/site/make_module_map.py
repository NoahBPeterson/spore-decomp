#!/usr/bin/env python3
"""Write tools/site/modules.json: which top-level module (EA's own top directory, e.g. SPGonzago) each retail function
belongs to, for the per-module bars on the public progress site.

Maintainer tool: it reads work/migrate/modmap.json (made from the development build's debug database) and
work/kinds.json (tools/status.py's function kinds), which are not in the repository.  A function modmap does not
assign falls back, in order, to:
  - its open-source library (symbols/lib_names.txt): "Open-source libraries";
  - compiler-generated code: an entry of the C runtime's dynamic-initializer table, a global's atexit destructor or a
    jump thunk (status.py kind "global"), and anything else unassigned in the block the linker put after the
    initializers (atexit destructors, exception-handling funclets): "Compiler-generated code";
  - an unassigned run of the module map with the same object, or the same top directory, on both sides: that
    directory (retail .text keeps each object's functions together);
  - then, repeated until nothing changes: runs with one directory on both sides take it; a function's named
    evidence (Spore-ModAPI's class for it, mapped onto this build by modapi_addr.py, and namespace strings such as
    "Simulator/cScenarioResource", each calibrated on attributed code) or, without any, its call graph (every
    attributed caller and callee in one directory, at least two) gives its directory (see decide());
  - else "Not yet attributed". The output holds only address runs and directory-level module names, which are already public as the
folders under src/game/: no function names, no code.

  .venv/bin/python tools/site/make_module_map.py
"""
import bisect, collections, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SOUND_DIRS = ("cmn", "plugins", "mix", "decoders", "ealayer30", "ealayer31")   # EA's sound library: one module
OTHER = "Not yet attributed"
LIBS = "Open-source libraries"
STARTUP = "Compiler-generated code"
GLUE_RUN = 1000          # the initializer block: the first run of this many consecutive "global"-kind functions


def main():
    MM = json.load(open(os.path.join(ROOT, "work", "migrate", "modmap.json")))
    M = MM["functions"]
    gaps = sorted((int(g["lo"], 16), int(g["hi"], 16), g.get("before") or "", g.get("after") or "") for g in MM.get("gaps", []))
    los = [g[0] for g in gaps]
    libs = set()
    for line in open(os.path.join(ROOT, "symbols", "lib_names.txt")):
        p = line.split("#", 1)[0].split()
        if len(p) >= 2:
            libs.add(int(p[0], 16))
    try:
        kinds = json.load(open(os.path.join(ROOT, "work", "kinds.json")))
    except OSError:
        kinds = {}
        print("work/kinds.json missing (run tools/status.py once): startup code stays unattributed")
    vas = sorted(int(d["va"], 16) for d in map(json.loads, open(os.path.join(ROOT, "tools", "ci",
                                                                                   "fingerprints.jsonl"), "rt")))
    def topdir(m):
        top = m.split("/")[0] if "/" in m else ""
        return "EA sound library" if top in SOUND_DIRS else top

    def module(va):
        top = topdir((M.get("%08x" % va) or {}).get("module") or "")
        if top:
            return top
        if va in libs:
            return LIBS
        if kinds.get("%08x" % va) == "global":
            return STARTUP
        i = bisect.bisect_right(los, va) - 1
        if i >= 0 and gaps[i][0] <= va <= gaps[i][1]:
            b, a = topdir(gaps[i][2]), topdir(gaps[i][3])
            if b and b == a:
                return b
        return OTHER
    # the initializer block and what the linker put after it
    glue_lo, k = None, 0
    for va in vas:
        k = k + 1 if kinds.get("%08x" % va) == "global" else 0
        if k == GLUE_RUN:
            glue_lo = vas[vas.index(va) - GLUE_RUN + 1]
            break
    lab = {}
    for va in vas:
        m = module(va)
        lab[va] = STARTUP if m == OTHER and glue_lo is not None and va >= glue_lo else m
    # call-graph vote, directory level
    feat = json.load(open(os.path.join(ROOT, "work", "xmatch", "retail.json")))
    calls = {int(a, 16): [int(c, 16) for c in v["calls"]] for a, v in feat.items()}
    callers = collections.defaultdict(list)
    for f, cs in calls.items():
        for c in cs:
            callers[c].append(f)
    skip = {OTHER, STARTUP, LIBS}
    # named evidence: ModAPI's class / file category for a function placed on this build (modapi_addr.py), and
    # namespace-like strings it references ("Simulator", "Simulator/cScenarioResource", "Graphics", "Anim", ...).  Each
    # key is calibrated on already-attributed functions: kept when one directory holds at least 90% of them (and 5+).
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import modapi_addr
    mapi = modapi_addr.mapping(set(vas))
    keys = collections.defaultdict(list)
    for va, (cat, cls) in mapi.items():
        keys[va] += [("modapi-class", cls), ("modapi-file", cat)]
    for a, v in feat.items():
        for st in v["strs"]:
            m = re.match(r"^([A-Z][A-Za-z]+)(?:/|$)", st)
            if m and len(st) < 80:
                keys[int(a, 16)].append(("string", m.group(1)))
    tally = collections.defaultdict(collections.Counter)
    for va, ks in keys.items():
        if lab[va] not in skip:
            for k in set(ks):
                tally[k][lab[va]] += 1
    calib = {k: c.most_common(1)[0][0] for k, c in tally.items()
             if c.most_common(1)[0][1] >= 5 and c.most_common(1)[0][1] >= 0.9 * sum(c.values())}

    def decide(va):
        """Directory for an unattributed function, or None.  Named evidence first (all of it must agree, and the
        call graph must not be all elsewhere); else the call graph alone (every attributed neighbour in one directory,
        at least two).  Holdout 2026-11-14: named 1,277 right / 68 wrong (95%), call graph 94%."""
        ev = {calib[k] for k in keys.get(va, ()) if k in calib}
        cg = collections.Counter(lab[g] for g in calls.get(va, []) + callers.get(va, []) if lab.get(g) and lab[g] not in skip)
        if len(ev) == 1:
            d = next(iter(ev))
            return d if not cg or cg[d] else None
        if not ev and len(cg) == 1 and sum(cg.values()) >= 2:
            return next(iter(cg))
        return None

    def fill():
        """An unattributed run with the same directory on both sides takes it (holdout: 29,180 right, 51 wrong)."""
        add, i = {}, 0
        while i < len(vas):
            if lab[vas[i]] != OTHER:
                i += 1
                continue
            j = i
            while j < len(vas) and lab[vas[j]] == OTHER:
                j += 1
            b4, af = (lab[vas[i - 1]] if i else None), (lab[vas[j]] if j < len(vas) else None)
            if b4 and b4 == af and b4 not in skip:
                add.update((vas[k], b4) for k in range(i, j))
            i = j
        return add

    while True:
        new = fill()
        lab.update(new)
        votes = {va: d for va in vas if lab[va] == OTHER for d in [decide(va)] if d}
        lab.update(votes)
        if not new and not votes:
            break
    names, runs, last = [], [], None
    for va in vas:
        m = lab[va]
        if m not in names:
            names.append(m)
        i = names.index(m)
        if i != last:
            runs.append(["%08x" % va, i])
            last = i
    out = {"_comment": "Runs over the retail function addresses (tools/ci/fingerprints.jsonl): from each address on, "
                       "functions belong to modules[index] until the next run. Made by tools/site/make_module_map.py.",
           "modules": names, "runs": runs}
    path = os.path.join(ROOT, "tools", "site", "modules.json")
    json.dump(out, open(path, "w"), separators=(",", ":"))
    print("%s: %d modules, %d runs, %d bytes" % (os.path.relpath(path, ROOT), len(names), len(runs), os.path.getsize(path)))
    size = {int(d["va"], 16): d["size"] for d in map(json.loads, open(os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl"), "rt"))}
    by = collections.Counter()
    for va in vas:
        by[lab[va]] += size[va]
    tot = sum(by.values())
    for m, b in by.most_common():
        print("  %-28s %6.2f MB  %5.1f%%" % (m, b / 2**20, 100.0 * b / tot))


if __name__ == "__main__":
    main()
