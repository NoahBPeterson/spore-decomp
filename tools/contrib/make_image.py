#!/usr/bin/env python3
"""make_image: build work/SporeApp.analysis.bin from YOUR OWN copy of Spore, for instruction diffs (tools/contrib/check.py).

  .venv/bin/python tools/contrib/make_image.py "<Spore>/SporeBin/SporeApp.exe" [out]

Steam or GOG. The Steam SporeApp.exe is protected with SteamStub v3.1; tools/steamstub_analysis_image.py decrypts its
code section into a non-runnable image. The GOG one is not protected and is used as it is: apart from Steam's DRM
section the two are identical. The result is checked against the retail fingerprints (tools/ci/fingerprints.jsonl.gz).
Known good (SporeBin/SporeApp.exe):
  Steam, 20,626,168 bytes, SHA-256 f9716458cdc232a507686dcb490e75680c514e31a5b1f33601b0dfcd05baf75d
  GOG,   20,454,960 bytes, SHA-256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
Galactic Adventures (SporebinEP1/SporeApp.exe) shares 99.75% of its functions with it byte for byte, at other
addresses; the fingerprints are for SporeBin's, so use that one.

The image is game code: it stays in work/ (git-ignored).  Never commit, upload or share it.
"""
import gzip, hashlib, json, os, random, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.join(ROOT, "tools", "matching"), os.path.join(ROOT, "tools", "ci")]
STEAM_SHA256 = "f9716458cdc232a507686dcb490e75680c514e31a5b1f33601b0dfcd05baf75d"
GOG_SHA256 = "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e"
OUT = os.path.join(ROOT, "work", "SporeApp.analysis.bin")


def probe(n=400, out=OUT):
    import run_all as R, fingerprint as F
    R.IMAGE = out
    orig = R.Original()
    fps = [json.loads(l) for l in gzip.open(os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl.gz"), "rt")]
    random.seed(1)
    ok = 0
    for fp in random.sample(fps, n):
        data, _m = orig.bytes_and_mask(int(fp["va"], 16), fp["size"])
        ok += F.mhash(data, F.unpack_mask(fp["mask"])) == fp["sha256"]
    return ok, n


def main():
    if len(sys.argv) not in (2, 3):
        sys.exit(__doc__)
    exe = sys.argv[1]
    out = os.path.abspath(sys.argv[2]) if len(sys.argv) == 3 else OUT
    sha = hashlib.sha256(open(exe, "rb").read()).hexdigest()
    known = {STEAM_SHA256: "Steam, known good", GOG_SHA256: "GOG, known good"}.get(sha, "not a known file")
    print("%s: %d bytes, SHA-256 %s  (%s)" % (exe, os.path.getsize(exe), sha, known))
    os.makedirs(os.path.dirname(out), exist_ok=True)
    import pefile
    protected = any(s.Name.rstrip(b"\0") == b".bind" for s in pefile.PE(exe, fast_load=True).sections)
    if protected:            # Steam: SteamStub-encrypted code section
        r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "steamstub_analysis_image.py"), exe, out,
                            os.path.splitext(out)[0] + ".json"])
        if r.returncode:
            sys.exit("could not build the image (is this the SteamStub-protected Steam SporeApp.exe?)")
    else:                    # GOG: not protected, the file is the image
        import shutil
        shutil.copyfile(exe, out)
    ok, n = probe(out=out)
    print("probe: %d of %d random retail functions match their fingerprints" % (ok, n))
    print("IMAGE OK" if ok == n else "IMAGE DIFFERS: diffs against it will not be meaningful; the pull-request check is unaffected")
    return 0 if ok == n else 3


if __name__ == "__main__":
    sys.exit(main())
