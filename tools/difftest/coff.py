"""Full x86 COFF object reader (sections, every symbol incl. undefined, relocations).

tools/matching/cmpobj.parse_coff only returns defined function symbols; the equivalence harness
also needs undefined externals, data symbols, static labels and section symbols to load and
relocate an object into the emulator.
"""
import struct

REL_DIR32, REL_DIR32NB, REL_SECTION, REL_SECREL, REL_REL32 = 0x06, 0x07, 0x0A, 0x0B, 0x14

SCN_CNT_CODE = 0x20
SCN_CNT_UNINIT = 0x80
SCN_LNK_INFO = 0x200
SCN_LNK_REMOVE = 0x800
SCN_LNK_COMDAT = 0x1000
SCN_MEM_EXECUTE = 0x20000000
SCN_MEM_WRITE = 0x80000000


class Sym:
    __slots__ = ("index", "name", "value", "secno", "type", "cls", "naux", "aux")

    def __init__(self, **kw):
        for k, v in kw.items():
            setattr(self, k, v)

    @property
    def defined(self):
        return self.secno > 0

    @property
    def is_func(self):
        return (self.type >> 4) == 2

    def __repr__(self):
        return "Sym(%r sec=%d val=%#x cls=%d)" % (self.name, self.secno, self.value, self.cls)


class Section:
    __slots__ = ("index", "name", "data", "flags", "relocs", "size", "align", "comdat_sel")

    @property
    def is_code(self):
        return bool(self.flags & (SCN_CNT_CODE | SCN_MEM_EXECUTE))

    @property
    def writable(self):
        return bool(self.flags & SCN_MEM_WRITE)

    @property
    def discard(self):
        return bool(self.flags & (SCN_LNK_REMOVE | SCN_LNK_INFO)) or self.name.startswith((".debug", ".drectve"))


class Coff:
    def __init__(self, path):
        d = open(path, "rb").read()
        machine, nsec, _, symptr, nsym, optsz, _ = struct.unpack_from("<HHIIIHH", d, 0)
        if machine != 0x14C:
            raise ValueError("%s: not an x86 COFF object" % path)
        strtab = symptr + nsym * 18

        def sname(raw):
            if raw[:4] == b"\0\0\0\0":
                off = struct.unpack_from("<I", raw, 4)[0]
                return d[strtab + off: d.index(b"\0", strtab + off)].decode("latin-1")
            return raw.split(b"\0")[0].decode("latin-1")

        self.sections = []
        for i in range(nsec):
            o = 20 + optsz + 40 * i
            raw = d[o:o + 8]
            nm = raw.split(b"\0")[0].decode("latin-1")
            if nm.startswith("/"):
                off = int(nm[1:])
                nm = d[strtab + off: d.index(b"\0", strtab + off)].decode("latin-1")
            size, ptr, relptr, _, nrel = struct.unpack_from("<IIIIH", d, o + 16)
            flags = struct.unpack_from("<I", d, o + 36)[0]
            s = Section()
            s.index, s.name, s.flags, s.size = i, nm, flags, size
            s.data = bytes(d[ptr:ptr + size]) if (ptr and not flags & SCN_CNT_UNINIT) else b"\0" * size
            s.relocs = [struct.unpack_from("<IIH", d, relptr + 10 * k) for k in range(nrel)]
            al = (flags >> 20) & 0xF
            s.align = 1 << (al - 1) if al else 16
            s.comdat_sel = 0
            self.sections.append(s)

        self.syms = {}      # symbol-table index -> Sym
        self.by_name = {}   # name -> Sym (first definition wins; externals keep their single entry)
        i = 0
        while i < nsym:
            o = symptr + 18 * i
            value, secno, typ, cls, naux = struct.unpack_from("<IHHBB", d, o + 8)
            secno = secno if secno < 0xFF00 else secno - 0x10000
            nm = sname(d[o:o + 8])
            aux = d[o + 18:o + 18 + 18 * naux]
            s = Sym(index=i, name=nm, value=value, secno=secno, type=typ, cls=cls, naux=naux, aux=aux)
            self.syms[i] = s
            if cls == 3 and value == 0 and naux and 0 < secno <= nsec:  # section definition symbol
                sel = aux[14] if len(aux) > 14 else 0
                self.sections[secno - 1].comdat_sel = sel
            prev = self.by_name.get(nm)
            if prev is None or (not prev.defined and s.defined):
                self.by_name[nm] = s
            i += 1 + naux

    def functions(self):
        """Defined function symbols: name -> Sym (external or static)."""
        return {s.name: s for s in self.syms.values()
                if s.defined and s.is_func and s.cls in (2, 3)}

    def section_of(self, sym):
        return self.sections[sym.secno - 1]

    def func_extent(self, sym):
        """(section, start, end) of a function symbol: up to the next symbol in its section."""
        sec = self.section_of(sym)
        starts = sorted({s.value for s in self.syms.values()
                         if s.secno == sym.secno and s.cls in (2, 3) and s.is_func and s.value > sym.value})
        end = starts[0] if starts else len(sec.data)
        data = sec.data[sym.value:end]
        if starts:
            data = data.rstrip(b"\xcc")
        return sec, sym.value, sym.value + len(data)
