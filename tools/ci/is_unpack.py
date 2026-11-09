#!/usr/bin/env python3
"""Unpack the files of an InstallShield 7 setup launcher (VCToolkitSetup.exe) without running it.

The launcher's overlay (after the last PE section) is "InstallShield\\0", a file count, then per file a 312-byte header
(name: 260 bytes, flags u32, u32, length u32, ...) and the file's bytes.  With flag 2 the bytes are obfuscated:
key = name XOR 13 35 86 07 (repeating), byte = NOT(key[i] XOR nibble-swap(byte)), over the whole file (--chunk N
restarts the key every N bytes, as later InstallShield versions do; with it the toolkit's MSI comes out wrong after byte
1024).  Checked: the unpacked MSI is byte-identical to the one msiexec cached when the launcher ran under wine on the Mac
(SHA-1 905dd04ff53f7994f583afc232760683e7383ff8).  The CI runner's wine could not run the launcher (exit 109 before msiexec started, run 42658111691), so
setup_toolchain.sh unpacks the toolkit's MSI with this and extracts it with msiextract, like VC9.

usage: is_unpack.py SETUP.EXE OUTDIR [--chunk N]     prints each file written
"""
import argparse, os, struct

MAGIC = bytes([0x13, 0x35, 0x86, 0x07])


def overlay(d):
    pe = struct.unpack_from("<I", d, 0x3c)[0]
    ns, opt = struct.unpack_from("<H", d, pe + 6)[0], struct.unpack_from("<H", d, pe + 20)[0]
    end = 0
    for k in range(ns):
        sz, ptr = struct.unpack_from("<II", d, pe + 24 + opt + 40 * k + 16)
        end = max(end, ptr + sz)
    return end


def decode(buf, name, chunk):
    key = bytes(c ^ MAGIC[i % 4] for i, c in enumerate(name))
    # per key position, a 256-entry table: decode is a byte map, so translate() runs it at C speed
    tables = [bytes((~(k ^ (((b << 4) & 0xf0) | (b >> 4)))) & 0xff for b in range(256)) for k in key]
    out = bytearray(len(buf))
    period = chunk or len(buf)
    n = len(key)
    for start in range(0, len(buf), period):
        block = buf[start:start + period]
        for j in range(n):
            out[start + j:start + len(block):n] = block[j::n].translate(tables[j])
    return bytes(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("setup")
    ap.add_argument("outdir")
    ap.add_argument("--chunk", type=int, default=0)
    a = ap.parse_args()
    d = open(a.setup, "rb").read()
    o = overlay(d)
    if d[o:o + 14] != b"InstallShield\0":
        raise SystemExit("%s: no InstallShield 7 overlay at %#x" % (a.setup, o))
    count = struct.unpack_from("<H", d, o + 14)[0]
    p = o + 0x2e
    os.makedirs(a.outdir, exist_ok=True)
    for _ in range(count):
        name = d[p:p + 260].split(b"\0")[0]
        flags, _u, length = struct.unpack_from("<III", d, p + 260)
        data = d[p + 312:p + 312 + length]
        if flags & 2:
            data = decode(data, name, a.chunk)
        path = os.path.join(a.outdir, name.decode("latin-1"))
        open(path, "wb").write(data)
        print("%10d  %s" % (length, path))
        p += 312 + length


if __name__ == "__main__":
    main()
