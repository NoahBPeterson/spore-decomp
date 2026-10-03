#!/usr/bin/env python3
"""Differential tests: original SporeApp.exe resource functions vs our C++.

usage: test_resource.py <analysis image> <libspore_resource_c> [<Spore/Data dir>] [--samples N]
"""
import argparse, ctypes, os, random, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from emu import Emulator, install_crt

ORIG_HASH_NAME = 0x0068C680          # uint32 __cdecl (const char*, int len)
ORIG_REFPACK_DECOMPRESS = 0x0092CA60  # int __cdecl (src, srcSize, dst, dstSize, flag)
ORIG_VERIFY_HEADER = 0x008D8D90       # bool __thiscall DatabasePackedFile::VerifyHeaderRecordIntegrity(hdr)

failures = 0
def check(cond, msg):
    global failures
    if not cond:
        failures += 1
        if failures <= 20:
            print("  MISMATCH:", msg)

def test_hash(emu, lib, rng):
    print("hash: 0x68C680 vs spore_hash_name")
    alphabet = list(range(0x20, 0x7F)) + list(range(0x80, 0x100))
    cases = [b"", b"a", b"Prop", b"CreatureEditor", "Café".encode("latin-1"), b"\xff\x80\x7f"]
    cases += [bytes(rng.choice(alphabet) for _ in range(rng.randint(0, 40))) for _ in range(3000)]
    n = 0
    for s in cases:
        emu.reset_heap()
        p = emu.alloc(len(s) + 1, s + b"\0")
        a = emu.call(ORIG_HASH_NAME, p, len(s))
        b = lib.spore_hash_name(s, len(s))
        check(a == b, "%r: orig %08x ours %08x" % (s, a, b))
        n += 1
    print("  %d cases" % n)

def iter_package_entries(path):
    with open(path, "rb") as f:
        h = f.read(0x60)
        count, isize, ioff = struct.unpack_from("<I", h, 0x24)[0], struct.unpack_from("<I", h, 0x2C)[0], struct.unpack_from("<I", h, 0x40)[0]
        f.seek(ioff)
        idx = f.read(isize)
    flags = struct.unpack_from("<I", idx, 0)[0]
    p = 4 + 4 * bin(flags & 7).count("1")
    for _ in range(count):
        p += 4 * (3 - bin(flags & 3).count("1") - 1) + 4  # non-constant type/group + instance
        off, size, mem = struct.unpack_from("<III", idx, p)
        p += 12
        comp = 0
        if size & 0x80000000:
            comp = struct.unpack_from("<H", idx, p)[0]; p += 4; size &= 0x7FFFFFFF
        else:
            comp = 0 if size == mem else 0xFFFF
        yield off, size, mem, comp

def test_refpack(emu, lib, data_dir, rng, samples):
    print("refpack: 0x92CA60 vs spore_refpack_decompress on corpus samples")
    pool = []
    for name in sorted(os.listdir(data_dir)):
        if name.endswith(".package"):
            path = os.path.join(data_dir, name)
            pool += [(path, e) for e in iter_package_entries(path) if e[3] and e[2] <= 512 * 1024]
    picked = rng.sample(pool, min(samples, len(pool)))
    for path, (off, size, mem, comp) in picked:
        with open(path, "rb") as f:
            f.seek(off); src = f.read(size)
        emu.reset_heap()
        s = emu.alloc(len(src), src)
        d = emu.alloc(mem)
        r = emu.call(ORIG_REFPACK_DECOMPRESS, s, len(src), d, mem, 1)
        orig = emu.read(d, mem) if r == mem else None
        buf = ctypes.create_string_buffer(mem)
        n = lib.spore_refpack_decompress(src, len(src), buf, mem)
        ours = buf.raw[:n] if n == mem else None
        check(orig is not None and orig == ours,
              "%s @%x: orig ret %d ours ret %d equal=%s" % (os.path.basename(path), off, r, n, orig == ours))
    # malformed headers: validity decisions must agree
    for b0 in range(256):
        hdr = bytes([b0, 0xFB, 0, 0, 0, 0, 0xFC, 0, 0, 0])
        emu.reset_heap()
        s = emu.alloc(len(hdr), hdr)
        a = emu.call(ORIG_REFPACK_DECOMPRESS, s, len(hdr), 0, 0, 1)
        b = lib.spore_refpack_decompress(hdr, len(hdr), None, 0)
        check((a == 0xFFFFFFFF) == (b == -1), "header byte %02x: orig %x ours %d" % (b0, a, b))
    print("  %d corpus entries + 256 header variants" % len(picked))

def test_verify_header(emu, lib, rng):
    print("header verify: 0x8D8D90 vs spore_verify_header (mutation fuzz)")
    base = bytearray(0x60)
    base[0:4] = b"DBPF"
    struct.pack_into("<I", base, 0x04, 3); struct.pack_into("<I", base, 0x24, 5)
    struct.pack_into("<I", base, 0x2C, 0x100); struct.pack_into("<I", base, 0x3C, 3)
    struct.pack_into("<I", base, 0x40, 0x1000)
    interesting = [0, 1, 2, 3, 4, 0x7FFFFFE, 0x7FFFFFF, 0xFFF, 0x1000, 0x1100, 0x1200, 0xFFFFFFFF, 0x80000000]
    n = 0
    for _ in range(4000):
        h = bytearray(base)
        for _ in range(rng.randint(1, 3)):
            field = rng.choice([0x00, 0x04, 0x24, 0x28, 0x2C, 0x3C, 0x40, 0x44])
            struct.pack_into("<I", h, field, rng.choice(interesting) if rng.random() < 0.8 else rng.getrandbits(32))
        size = rng.choice([0x1000, 0x1100, 0x1101, 0x2000, 0x10, 0xFFFFFFFF])
        emu.reset_heap()
        hp = emu.alloc(0x60, h)
        this = emu.alloc(0x400, b"\0" * 0x400)
        emu.write(this + 0x264, struct.pack("<I", 0x1))   # "memory-backed" -> use cached size
        emu.write(this + 0x268, struct.pack("<I", size & 0xFFFFFFFF))
        a = emu.call(ORIG_VERIFY_HEADER, hp, this=this) & 0xFF
        b = lib.spore_verify_header(bytes(h), size)
        check(bool(a) == bool(b), "size=%x hdr=%s: orig %d ours %d" % (size, bytes(h).hex(), a, b))
        n += 1
    print("  %d cases" % n)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("image"); ap.add_argument("lib"); ap.add_argument("data", nargs="?")
    ap.add_argument("--samples", type=int, default=300); ap.add_argument("--seed", type=int, default=1)
    a = ap.parse_args()
    lib = ctypes.CDLL(a.lib)
    lib.spore_hash_name.restype = ctypes.c_uint32
    lib.spore_hash_name.argtypes = [ctypes.c_char_p, ctypes.c_size_t]
    lib.spore_refpack_decompress.restype = ctypes.c_int64
    lib.spore_refpack_decompress.argtypes = [ctypes.c_char_p, ctypes.c_size_t, ctypes.c_void_p, ctypes.c_size_t]
    lib.spore_verify_header.restype = ctypes.c_int
    lib.spore_verify_header.argtypes = [ctypes.c_char_p, ctypes.c_uint64]
    emu = Emulator(a.image); install_crt(emu)
    rng = random.Random(a.seed)
    test_hash(emu, lib, rng)
    test_verify_header(emu, lib, rng)
    if a.data:
        test_refpack(emu, lib, a.data, rng, a.samples)
    print("FAILED (%d)" % failures if failures else "OK")
    sys.exit(1 if failures else 0)

if __name__ == "__main__":
    main()
