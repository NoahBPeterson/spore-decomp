#!/usr/bin/env python3
"""Minimal MSF 7.00 (PDB) stream reader that supports multi-block directory maps
(old 1 KiB-page PDBs that llvm-pdbutil rejects with "Too many directory blocks")."""
import struct, sys

class MSF:
    def __init__(self, path):
        self.f = open(path, "rb")
        h = self.f.read(64)
        assert h[:32].startswith(b"Microsoft C/C++ MSF 7.00"), "not MSF 7.00"
        self.bs, self.fpm, self.nblocks, self.dirsize, _ = struct.unpack_from("<IIIII", h, 32)
        nb = (self.dirsize + self.bs - 1) // self.bs           # directory blocks
        nmap = (nb * 4 + self.bs - 1) // self.bs               # block-map blocks (array at offset 52)
        self.f.seek(52); mapblocks = struct.unpack("<%dI" % nmap, self.f.read(4 * nmap))
        dirblocks = struct.unpack_from("<%dI" % nb, b"".join(self.block(b) for b in mapblocks))
        d = b"".join(self.block(b) for b in dirblocks)[:self.dirsize]
        n = struct.unpack_from("<I", d, 0)[0]
        self.sizes = list(struct.unpack_from("<%dI" % n, d, 4))
        o = 4 + 4 * n; self.blocks = []
        for sz in self.sizes:
            k = 0 if sz == 0xFFFFFFFF else (sz + self.bs - 1) // self.bs
            self.blocks.append(struct.unpack_from("<%dI" % k, d, o)); o += 4 * k

    def block(self, i):
        self.f.seek(i * self.bs); return self.f.read(self.bs)

    def stream(self, i):
        sz = self.sizes[i]
        if sz == 0xFFFFFFFF: return b""
        return b"".join(self.block(b) for b in self.blocks[i])[:sz]

if __name__ == "__main__":
    m = MSF(sys.argv[1])
    s1 = m.stream(1)
    ver, sig, age = struct.unpack_from("<III", s1, 0)
    print("streams %d, page %d; PDB info: version %d age %d guid %s" % (len(m.sizes), m.bs, ver, age, s1[12:28].hex()))
