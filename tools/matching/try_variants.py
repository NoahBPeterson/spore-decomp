#!/usr/bin/env python3
"""Compile a scratch file of candidate functions and rank each against an original VA.

usage: try_variants.py <file.cpp> <va-hex> [--flags "..."] [cl flags...]
Every function symbol in the object is compared; prints heuristic distances, best first,
and the independent retail fingerprint verdict. FINGERPRINT_PASS is diagnostic only:
run the contribution gate for source-policy, manifest, and regression checks.
"""
import argparse, gzip, json, os, shutil, subprocess, sys, tempfile
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pefile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "ci"))
import fingerprint as F  # noqa: E402


def score_candidates(secs, syms, fp, retail):
    """Rank by distance; only F.check decides the fingerprint verdict.

    Distance masks addresses on either side and counts missing/excess bytes. It
    deliberately cannot prove relocation validity or the identity of a target.
    """
    if len(retail) != fp["size"]:
        raise ValueError("Retail image did not provide the fingerprint's full function extent")
    retail_mask = F.unpack_mask(fp["mask"])
    rows = []
    for name in syms:
        if name.startswith(F.FUNCLET):
            continue
        mine, rel = F.extract(secs, syms, name)
        mask = retail_mask | rel
        distance = abs(len(mine) - len(retail)) + sum(
            a != b for i, (a, b) in enumerate(zip(mine, retail)) if i not in mask)
        rows.append((distance, len(mine), name, F.check(fp, mine, rel)))
    return sorted(rows)


def _normalize_flags(parser, opt_flags, remainder):
    raw = list(opt_flags)
    it = iter(remainder)
    for token in it:
        if token == "--flags":
            val = next(it, None)
            if val is None:
                parser.error("argument --flags: expected one argument")
            raw.append(val)
        elif token.startswith("--flags="):
            raw.append(token.split("=", 1)[1])
        else:
            raw.append(token)
    return [f for arg in raw for f in arg.split()] or ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source")
    parser.add_argument("address", type=lambda value: int(value, 16))
    parser.add_argument("--flags", dest="opt_flags", action="append", default=[])
    parser.add_argument("flags", nargs=argparse.REMAINDER)
    args = parser.parse_args(argv)
    flags = _normalize_flags(parser, args.opt_flags, args.flags)
    with gzip.open(os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl.gz"), "rt") as stream:
        fp = next((row for row in map(json.loads, stream) if int(row["va"], 16) == args.address), None)
    if fp is None:
        parser.error("No retail fingerprint for 0x%08x" % args.address)
    directory = os.path.join(ROOT, "work", "match", "variants")
    os.makedirs(directory, exist_ok=True)
    # A successful compiler exit need not emit an object (/Zs, for example).
    # A fresh path also prevents concurrent invocations from sharing output.
    invocation = tempfile.mkdtemp(prefix="variant-", dir=directory)
    obj = os.path.join(invocation, "candidate.obj")
    w = lambda p: "Z:" + os.path.abspath(p).replace("/", "\\")
    result = subprocess.run([os.path.join(ROOT, "tools/matching/cl.sh"), "/nologo", "/c", *flags,
                             "/I" + w(os.path.join(ROOT, "match", "include")), "/Fo" + w(obj), w(args.source)],
                            capture_output=True, text=True)
    if result.returncode:
        shutil.rmtree(invocation, ignore_errors=True)
        print(result.stdout + result.stderr, file=sys.stderr)
        return 1
    if not os.path.isfile(obj):
        shutil.rmtree(invocation, ignore_errors=True)
        print("Compiler did not emit the requested object: " + obj, file=sys.stderr)
        return 1
    print("Object: " + obj)
    secs, syms = F.parse_coff(obj)
    pe = pefile.PE(os.path.join(ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
    try:
        retail = pe.get_data(args.address - pe.OPTIONAL_HEADER.ImageBase, fp["size"])
    finally:
        pe.close()
    try:
        rows = score_candidates(secs, syms, fp, retail)
    except ValueError as error:
        parser.error(str(error))
    if not rows:
        parser.error("No function symbols found in the compiled object")
    for distance, size, name, verdict in rows:
        status = "FINGERPRINT_PASS (run contribution gate)" if verdict == "PASS" else verdict
        print("%4d heuristic diff / %3d bytes  %s   %s" % (distance, size, name, status))
    return 0


if __name__ == "__main__":
    sys.exit(main())
