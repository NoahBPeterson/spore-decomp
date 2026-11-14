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
  - the call graph (work/xmatch/retail.json direct calls): when every attributed caller and callee of a function is
    in one directory, and there are at least two, that directory; repeated until nothing changes.  Holdout on 6,000
    attributed functions (2026-11-14): 1,457 right, 89 wrong (94%%) at that threshold;
  - else "Not yet attributed". The output holds only address runs and directory-level module names, which are already public as the
folders under src/game/: no function names, no code.

  .venv/bin/python tools/site/make_module_map.py
"""
import bisect, collections, gzip, json, os

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
    vas = sorted(int(d["va"], 16) for d in map(json.loads, gzip.open(os.path.join(ROOT, "tools", "ci",
                                                                                   "fingerprints.jsonl.gz"), "rt")))
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
    while True:
        new = {}
        for va in vas:
            if lab[va] != OTHER:
                continue
            c = collections.Counter(lab.get(g) for g in calls.get(va, []) + callers.get(va, []) if lab.get(g) not in skip
                                    and lab.get(g) is not None)
            if c and len(c) == 1 and sum(c.values()) >= 2:
                new[va] = next(iter(c))
        if not new:
            break
        lab.update(new)
    names, runs, last = [], [], None
    for va in vas:
        m = lab[va]
        if m not in names:
            names.append(m)
        i = names.index(m)
        if i != last:
            runs.append(["%08x" % va, i])
            last = i
    out = {"_comment": "Runs over the retail function addresses (tools/ci/fingerprints.jsonl.gz): from each address on, "
                       "functions belong to modules[index] until the next run. Made by tools/site/make_module_map.py.",
           "modules": names, "runs": runs}
    path = os.path.join(ROOT, "tools", "site", "modules.json")
    json.dump(out, open(path, "w"), separators=(",", ":"))
    print("%s: %d modules, %d runs, %d bytes" % (os.path.relpath(path, ROOT), len(names), len(runs), os.path.getsize(path)))
    size = {int(d["va"], 16): d["size"] for d in map(json.loads, gzip.open(os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl.gz"), "rt"))}
    by = collections.Counter()
    for va in vas:
        by[lab[va]] += size[va]
    tot = sum(by.values())
    for m, b in by.most_common():
        print("  %-28s %6.2f MB  %5.1f%%" % (m, b / 2**20, 100.0 * b / tot))


if __name__ == "__main__":
    main()
