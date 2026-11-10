#!/usr/bin/env python3
"""Write tools/site/modules.json: which top-level module (EA's own top directory, e.g. SPGonzago) each retail function
belongs to, for the per-module bars on the public progress site.

Maintainer tool: it reads work/migrate/modmap.json (made from the development build's debug database), which is not in
the repository. The output holds only address runs and directory-level module names, which are already public as the
folders under src/game/: no function names, no code.

  .venv/bin/python tools/site/make_module_map.py
"""
import gzip, json, os

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SOUND_DIRS = ("cmn", "plugins", "mix", "decoders", "ealayer30", "ealayer31")   # EA's sound library: one module
OTHER = "Not yet attributed"


def main():
    M = json.load(open(os.path.join(ROOT, "work", "migrate", "modmap.json")))["functions"]
    vas = sorted(int(d["va"], 16) for d in map(json.loads, gzip.open(os.path.join(ROOT, "tools", "ci",
                                                                                   "fingerprints.jsonl.gz"), "rt")))
    def module(va):
        m = (M.get("%08x" % va) or {}).get("module") or ""
        top = m.split("/")[0] if "/" in m else ""
        return "EA sound library" if top in SOUND_DIRS else (top or OTHER)
    names, runs, last = [], [], None
    for va in vas:
        m = module(va)
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


if __name__ == "__main__":
    main()
