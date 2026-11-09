#!/usr/bin/env python3
"""variants: compile many spellings of one function and say which reproduce the retail bytes.

  .venv/bin/python tools/contrib/variants.py work/scratch_0x00529690.cpp 0x00529690 \
      --flags "/O2 /MD /Gy /EHsc /TP /Isrc/game/include"

Why this exists: the per-function loop in AGENTS.md edits one source file and calls check.py, which is one wine
compile per spelling (~5 s here, and an edited shared TU on top).  A scratch file with 20-30 renamed copies compiles
once (~2 s), so a source-shape search costs one compile instead of thirty.  check.py is still the tool that records a
match in the real source tree.

Comparison resolution: a fingerprint has the retail size, the offsets that hold addresses, and a hash of the rest --
no code and no per-byte diff (see tools/ci/fingerprint.py).  So this tool states, per spelling:

  * MATCH                  every compared byte is the retail byte;
  * size N, retail M       wrong length, ruled out;
  * relocation at offset.. the right size, but a call/global/address sits at a different offset, i.e. a different
                           instruction schedule (this is the strongest signal without a retail copy);
  * bytes differ           same size and same address positions: no way to tell which spelling is closer.

With a retail image (work/SporeApp.analysis.bin, from your own game) use tools/matching/try_variants.py instead: it
ranks by differing-byte count.  Without one, this is a search over codegen families, not a hill climb: spellings in
one family are indistinguishable, and a one-byte difference away from every address cannot be steered at all.

Rules for the scratch file: one function per spelling with a distinct symbol (`v01`, `v02`, ...), no `// @ 0x` markers,
plain C++ only (the check rejects assembly transcriptions, here as in check.py), and keep it under work/ so it is
never committed.  Do not use this to guess at a near-miss you cannot explain -- a spelling that passes the
fingerprint check is the same evidence check.py would give, so put the winner in the real source and run check.py.
"""
import argparse
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.join(ROOT, "tools", "ci"), os.path.join(ROOT, "tools", "matching"),
                os.path.join(ROOT, "tools", "contrib"), os.path.join(ROOT, "tools", "difftest")]

import fingerprint as F  # noqa: E402
from cmpobj import parse_coff  # noqa: E402
import task as T  # noqa: E402

DEFAULT_FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
SKIP = ("__ehhandler", "__unwindfunclet", "__catch", "__tryend", "$")


def winpath(p):
    return "Z:" + os.path.abspath(p).replace("/", "\\")


def compile_obj(src, flags, obj):
    cmd = [os.path.join(ROOT, "tools/matching/cl.sh"), "/nologo", "/c", *flags,
           "/I" + winpath(os.path.join(ROOT, "src", "game", "include")),
           "/I" + winpath(os.path.join(ROOT, "match", "include")),
           "/Fo" + winpath(obj), winpath(src)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode:
        sys.exit((r.stdout + r.stderr).strip()[-4000:])


def family(verdict):
    """a label that groups spellings with the same observable shape"""
    if verdict == "PASS":
        return "MATCH"
    if verdict.startswith("size "):
        return verdict
    if verdict.startswith("relocation at"):
        offs = verdict.split("offset ")[1].split(" where")[0]
        return "same size; an address sits at the wrong offset (%s)" % offs
    return verdict


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("file", help="scratch .cpp holding the candidate spellings")
    ap.add_argument("va", help="retail address the spellings must reproduce, e.g. 0x00529690")
    ap.add_argument("--flags", help="cl flags (space-separated); default: /O2 /MD /Gy /TP plus the repo includes")
    ap.add_argument("-q", "--quiet", help="family summary only", action="store_true")
    a = ap.parse_args()

    va = int(a.va, 16)
    fp = T.fingerprints().get(va)
    if not fp:
        sys.exit("0x%08x has no fingerprint: not a known function start" % va)
    flags = a.flags.split() if a.flags else list(DEFAULT_FLAGS)

    obj = os.path.join(ROOT, "work", "match", "variants",
                       os.path.basename(a.file) + ".obj")
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    compile_obj(a.file, flags, obj)

    secs, syms = parse_coff(obj)
    rows = []
    for name, (si, off) in syms.items():
        if name.startswith(SKIP):
            continue
        data, rel = F.extract(secs, syms, name)
        verdict = F.check(fp, data, rel)
        rows.append((len(data), name, verdict))
    if not rows:
        sys.exit("no functions in the object: give each spelling a distinct definition")
    rows.sort(key=lambda r: (r[2] != "PASS", family(r[2]), r[0], r[1]))

    if not a.quiet:
        for n, name, verdict in rows:
            print("%-40s %4d  %s" % (name, n, "MATCH" if verdict == "PASS" else verdict))
        print()

    fams = {}
    for _n, name, verdict in rows:
        short = name.split("@")[0].lstrip("?")
        fams.setdefault(family(verdict), []).append(short)
    print("%d spelling(s), %d codegen famil%s (retail 0x%08x, %d bytes):"
          % (len(rows), len(fams), "y" if len(fams) == 1 else "ies", va, fp["size"]))
    for key in sorted(fams, key=lambda k: (k != "MATCH", k)):
        print("  %-52s %2d  %s" % (key, len(fams[key]), " ".join(sorted(fams[key]))))

    winners = fams.get("MATCH", [])
    if winners:
        print("\nMATCH: %s" % " ".join(sorted(winners)))
        print("put the winning spelling in the real source and run tools/contrib/check.py 0x%08x" % va)
        return 0
    if len(fams) == 1 and next(iter(fams)).startswith("size "):
        print("\nno spelling has the retail size: these are candidates for another function, or the flags differ")
    else:
        print("\nno spelling matches; with a retail image try tools/matching/try_variants.py for a byte-ranking")
    return 1


if __name__ == "__main__":
    sys.exit(main())
