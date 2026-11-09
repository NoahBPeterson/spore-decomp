#!/usr/bin/env python3
"""make_image: build work/SporeApp.analysis.bin from YOUR OWN copy of Spore, for instruction diffs (tools/contrib/check.py).

  .venv/bin/python tools/contrib/make_image.py "<Spore>/SporeBin/SporeApp.exe"

The Steam SporeApp.exe is protected with SteamStub v3.1; tools/steamstub_analysis_image.py decrypts its code section
into a non-runnable image.  The result is checked against the retail fingerprints (tools/ci/fingerprints.jsonl.gz).
Known good: Steam SporeApp.exe, 20,626,168 bytes, SHA-256 f9716458cdc232a507686dcb490e75680c514e31a5b1f33601b0dfcd05baf75d.
Other editions are untested: the probe says how many functions match.

The image is game code: it stays in work/ (git-ignored).  Never commit, upload or share it.
"""
import gzip, hashlib, json, os, random, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.join(ROOT, "tools", "matching"), os.path.join(ROOT, "tools", "ci")]
STEAM_SHA256 = "f9716458cdc232a507686dcb490e75680c514e31a5b1f33601b0dfcd05baf75d"
OUT = os.path.join(ROOT, "work", "SporeApp.analysis.bin")


def probe(n=400):
    import run_all as R, fingerprint as F
    R.IMAGE = OUT
    orig = R.Original()
    fps = [json.loads(l) for l in gzip.open(os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl.gz"), "rt")]
    random.seed(1)
    ok = 0
    for fp in random.sample(fps, n):
        data, _m = orig.bytes_and_mask(int(fp["va"], 16), fp["size"])
        ok += F.mhash(data, F.unpack_mask(fp["mask"])) == fp["sha256"]
    return ok, n


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    exe = sys.argv[1]
    sha = hashlib.sha256(open(exe, "rb").read()).hexdigest()
    print("%s: %d bytes, SHA-256 %s%s" % (exe, os.path.getsize(exe), sha,
                                         "  (Steam, known good)" if sha == STEAM_SHA256 else "  (not the known Steam file)"))
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "steamstub_analysis_image.py"), exe, OUT,
                        os.path.splitext(OUT)[0] + ".json"])
    if r.returncode:
        sys.exit("could not build the image (is this the SteamStub-protected Steam SporeApp.exe?)")
    ok, n = probe()
    print("probe: %d of %d random retail functions match their fingerprints" % (ok, n))
    print("IMAGE OK" if ok == n else "IMAGE DIFFERS: diffs against it will not be meaningful; the pull-request check is unaffected")
    return 0 if ok == n else 3


if __name__ == "__main__":
    sys.exit(main())
