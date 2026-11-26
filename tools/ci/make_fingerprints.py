#!/usr/bin/env python3
"""Write fingerprints (tools/ci/fingerprint.py) of retail functions.  Maintainers only: needs the retail image
(work/SporeApp.analysis.bin), the function lists in work/ and the manifests.

usage: make_fingerprints.py [--vas FILE] [--out tools/ci/fingerprints.jsonl]
       --vas: one hex VA per line (default: every known function start)
       make_fingerprints.py --add-masked tools/ci/fingerprints.jsonl [--out tools/ci/fingerprints.jsonl]
       --add-masked: add the "masked" field to existing fingerprints, leaving size, mask and hash as they are
       make_fingerprints.py --add-fixups tools/ci/fingerprints.jsonl [--out tools/ci/fingerprints.jsonl]
       --add-fixups: add the "fixups" field (retail .reloc offsets) the same way
"""
import argparse, csv, glob, json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "matching"))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import run_all as R             # noqa: E402
import fingerprint as F         # noqa: E402


def starts():
    """every function start we know: the Ghidra index, the module map, and every manifest/nonmatching row (the index
    alone misses some: 652 byte-exact rows ran into the next function)"""
    s = set()
    for f in glob.glob(os.path.join(ROOT, "work", "decomp_all", "index_*.csv")):
        for row in csv.reader(open(f)):
            if len(row) >= 3 and row[2].isdigit():
                s.add(int(row[0], 16))
    mm = os.path.join(ROOT, "work", "migrate", "modmap.json")
    if os.path.exists(mm):
        s |= {int(v, 16) for v in json.load(open(mm))["functions"]}
    # every start an earlier run knew: the fingerprints themselves (enough to re-size a few rows when the Ghidra index
    # or the module map is not on this machine)
    fps = os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl")
    if os.path.exists(fps):
        s |= {int(json.loads(l)["va"], 16) for l in open(fps) if l.strip()}
    # starts that none of the lists above has, found by hand: a fingerprint otherwise runs into the next function
    # (#588: 0x00fc9210 absorbed 0x00fc9220, 0x00fcdb20 absorbed 0x00fcdc10)
    extra = os.path.join(ROOT, "tools", "ci", "extra_starts.txt")
    if os.path.exists(extra):
        for line in open(extra):
            tok = line.split("#", 1)[0].strip()
            if tok:
                s.add(int(tok, 16))
    for f in [g for d in ("match", os.path.join("src", "game")) for n in ("manifest.txt", "nonmatching.txt", "partial.txt")
              for g in glob.glob(os.path.join(ROOT, d, "**", n), recursive=True)]:
        for line in open(f, errors="replace"):
            for tok in line.split("#", 1)[0].split()[:3]:
                if len(tok) == 8:
                    try:
                        s.add(int(tok, 16))
                    except ValueError:
                        pass
    return sorted(s)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--vas")
    ap.add_argument("--out", default=os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl"))
    ap.add_argument("--add-masked")
    ap.add_argument("--add-fixups")
    a = ap.parse_args()
    orig = R.Original()
    if a.add_fixups:
        n = 0
        with open(a.add_fixups, "rt") as src, open(a.out, "w") as f:
            for line in src:
                fp = json.loads(line)
                va = int(fp["va"], 16)
                fx = F.fixups(orig, va, fp["size"])
                mask = F.unpack_mask(fp["mask"])
                if not all(o + k in mask for o in fx for k in range(4)):
                    sys.exit("%s: a .reloc fixup outside the fingerprint's mask" % fp["va"])
                fp["fixups"] = fx
                f.write(json.dumps(fp, separators=(",", ":")) + "\n")
                n += 1
        print("added fixups to %d fingerprints -> %s" % (n, os.path.relpath(a.out, ROOT)))
        return
    if a.add_masked:
        n = 0
        with open(a.add_masked, "rt") as src, open(a.out, "w") as f:
            for line in src:
                fp = json.loads(line)
                va = int(fp["va"], 16)
                data, _m = orig.bytes_and_mask(va, fp["size"])
                mask = set(F.unpack_mask(fp["mask"]))
                if F.mhash(data, mask) != fp["sha256"]:
                    sys.exit("%s: the image no longer gives this fingerprint's hash" % fp["va"])
                fp["masked"] = F.masked_hex(data, mask)
                f.write(json.dumps(fp, separators=(",", ":")) + "\n")
                n += 1
        print("added masked bytes to %d fingerprints -> %s" % (n, os.path.relpath(a.out, ROOT)))
        return
    st = starts()
    sizes = F.retail_sizes(orig, st)
    want = [int(l.split()[0], 16) for l in open(a.vas) if l.strip()] if a.vas else st
    md, rng = F._disasm(), F.image_range(orig)
    n = 0
    with open(a.out, "w") as f:
        for va in sorted(set(want)):
            if va in sizes:
                f.write(json.dumps(F.make(orig, va, sizes[va], md, rng), separators=(",", ":")) + "\n")
                n += 1
    print("%d fingerprints -> %s (%d VAs had no size)" % (n, os.path.relpath(a.out, ROOT), len(set(want)) - n))


if __name__ == "__main__":
    main()
