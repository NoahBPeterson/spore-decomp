#!/usr/bin/env python3
"""Extract COFF object members from an MSVC .lib (ar archive). usage: ar_extract.py <lib> <outdir>"""
import os, sys
lib, out = sys.argv[1], sys.argv[2]
os.makedirs(out, exist_ok=True)
d = open(lib, "rb").read()
assert d[:8] == b"!<arch>\n"
p, n, longnames = 8, 0, b""
while p + 60 <= len(d):
    hdr = d[p:p + 60]
    name = hdr[:16].decode(errors="replace").strip()
    size = int(hdr[48:58].decode().strip())
    body = d[p + 60:p + 60 + size]
    if name == "//":
        longnames = body
    elif name not in ("/", "") and body[:2] == b"\x4c\x01":   # i386 COFF object (skip import stubs)
        if name.startswith("/") and name[1:].isdigit():
            off = int(name[1:]); name = longnames[off:longnames.index(b"\0", off) if b"\0" in longnames[off:] else longnames.index(b"\n", off)].decode()
        base = os.path.basename(name.rstrip("/").replace("\\", "/"))
        open(os.path.join(out, "%04d_%s" % (n, base)), "wb").write(body)
        n += 1
    p += 60 + size + (size & 1)
print("extracted", n)
