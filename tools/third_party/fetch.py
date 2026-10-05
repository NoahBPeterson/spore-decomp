#!/usr/bin/env python3
"""Fetch, verify (SHA-256) and extract the pinned third-party tarballs listed in third_party/manifest.json.

usage: fetch.py [lib ...] [--src DIR] [--offline] [--seed DIR]
Default DIR is work/third_party/src. Tarballs already present (in DIR or in --seed, default work/oss) are
used without network access; a present file with a wrong hash is an error (never silently replaced).
Extraction goes to DIR/<extract_dir>; it is skipped if that directory already exists.
"""
import argparse, hashlib, json, os, shutil, sys, tarfile, urllib.request

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))

def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()

def load_manifest():
    return json.load(open(os.path.join(ROOT, "third_party", "manifest.json")))

def fetch_one(name, lib, src, seed, offline):
    tb = lib["tarball"]
    dst = os.path.join(src, tb)
    want = lib["sha256"]
    if not os.path.exists(dst):
        seeded = os.path.join(seed, tb) if seed else None
        if seeded and os.path.exists(seeded):
            shutil.copy(seeded, dst)
            print("%s: copied %s from %s" % (name, tb, seed))
        elif offline:
            sys.exit("%s: %s missing and --offline given" % (name, tb))
        else:
            for url in lib["urls"]:
                try:
                    print("%s: downloading %s" % (name, url))
                    req = urllib.request.Request(url, headers={"User-Agent": "spore-decomp-fetch"})
                    with urllib.request.urlopen(req, timeout=120) as r, open(dst + ".part", "wb") as f:
                        shutil.copyfileobj(r, f)
                    if sha256(dst + ".part") != want:
                        print("%s: hash mismatch from %s, trying next" % (name, url))
                        os.remove(dst + ".part")
                        continue
                    os.rename(dst + ".part", dst)
                    break
                except Exception as e:
                    print("%s: %s failed: %s" % (name, url, e))
            else:
                sys.exit("%s: all sources failed" % name)
    got = sha256(dst)
    if got != want:
        sys.exit("%s: SHA-256 mismatch for %s\n  expected %s\n  got      %s" % (name, dst, want, got))
    out = os.path.join(src, lib["extract_dir"])
    if not os.path.isdir(out):
        with tarfile.open(dst) as t:
            for m in t.getmembers():  # refuse path escapes
                if os.path.isabs(m.name) or ".." in m.name.split("/"):
                    sys.exit("unsafe path in tarball: " + m.name)
            t.extractall(src)
        if not os.path.isdir(out):
            sys.exit("%s: expected %s after extraction" % (name, out))
        print("%s: extracted to %s" % (name, out))
    else:
        print("%s: ok (%s verified, %s present)" % (name, tb, lib["extract_dir"]))

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("libs", nargs="*")
    ap.add_argument("--src", default=os.path.join(ROOT, "work", "third_party", "src"))
    ap.add_argument("--seed", default=os.path.join(ROOT, "work", "oss"))
    ap.add_argument("--offline", action="store_true")
    a = ap.parse_args()
    m = load_manifest()
    os.makedirs(a.src, exist_ok=True)
    for name, lib in m["libraries"].items():
        if a.libs and name not in a.libs:
            continue
        fetch_one(name, lib, a.src, a.seed, a.offline)

if __name__ == "__main__":
    main()
