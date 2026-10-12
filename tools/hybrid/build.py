#!/usr/bin/env python3
"""Build a runnable hybrid SporeApp.exe: the decrypted original with our compiled functions spliced in.

usage: build.py [--out work/hybrid/SporeApp.hybrid.exe] [--no-patches]
                [--hook pass|none|FILE] [--limit N] [--verify-exact N] [-v]

Stage 1: make the analysis image runnable. Entry point back on the real OEP, the (now invalid)
Authenticode directory dropped, DYNAMIC_BASE cleared (our code uses absolute addresses without
base-relocation entries), checksum refreshed, runtime PATCHES applied. Boots to the main menu
under CrossOver/Wine with the Steam client running (docs/hybrid.md).

Stage 2 (--hook): for every selected function, compile its slice (cached by the difftest harness),
resolve the object's relocations against the original image exactly as the equivalence harness
does, copy the sections it needs into two new PE sections (.hybx code+rodata, .hybd writable),
and overwrite the first five bytes of the original function with `jmp ours`. Byte-exact
functions need no splice (same bytes); --verify-exact lays N of them out and diffs them against
the original to prove the relocation arithmetic.

--hook pass selects every function whose latest strict equivalence verdict is PASS
(work/difftest/*_shard*.json); a FILE holds one "<slice> <va>" per line.
"""
import argparse, glob, json, os, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "difftest"))
import pefile                                   # noqa: E402
from coff import REL_DIR32, REL_DIR32NB, REL_REL32   # noqa: E402

IMAGE = os.path.join(ROOT, "work", "SporeApp.analysis.bin")
BASE = 0x400000
OEP = 0x011E11A0
DYNAMIC_BASE = 0x40
JMP = 0xE9

# Runtime patches: (va, expected original bytes, replacement, why). Each is checked against the
# image before it is applied so a wrong image or a stale patch fails loudly.
PATCHES = [
    # Registry strings read through FUN_006ab840 (SetupDirectories' DataDir, Locale, PlayerDir, ...)
    # are built with wstring::assign(buf, cbData - 1): a byte count used as a character count, so
    # the string carries ~len uninitialised stack wchars after its terminator. SetupDirectories then
    # does find(L'"', 1) to strip quotes and, when the garbage holds a quote, drops the drive letter
    # ("C:\...\Data" -> ":\...\Data" -> "//.../Data/"): "Could not find the Data directory [1004]".
    # Windows happens to leave benign garbage there; under Wine it fails on most launches.
    # Fix: length = cbData / 2 - 1. The 6-byte site becomes a jmp to a 13-byte detour in the int3
    # padding after the function (0x6ab942..0x6ab94f).
    (0x006AB908, bytes.fromhex("8b4424104850"),
     bytes([JMP]) + struct.pack("<i", 0x6AB942 - (0x6AB908 + 5)) + b"\x90",
     "registry string length: jump to detour"),
    (0x006AB942, b"\xcc" * 13,
     bytes.fromhex("8b442410" "d1e8" "48" "50") + bytes([JMP]) + struct.pack("<i", 0x6AB90E - (0x6AB942 + 13)),
     "registry string length detour: mov eax,[esp+10h]; shr eax,1; dec eax; push eax; jmp back"),
]


def align(x, a):
    return (x + a - 1) & ~(a - 1)


# ---------------------------------------------------------------- stage 1

def make_runnable(pe, patches=True):
    pe.OPTIONAL_HEADER.AddressOfEntryPoint = OEP - BASE
    cert = pe.OPTIONAL_HEADER.DATA_DIRECTORY[4]
    cert.VirtualAddress = 0
    cert.Size = 0
    pe.OPTIONAL_HEADER.DllCharacteristics &= ~DYNAMIC_BASE
    if patches:
        for va, old, new, why in PATCHES:
            off = pe.get_offset_from_rva(va - BASE)
            have = bytes(pe.__data__[off:off + len(old)])
            if have != old:
                raise SystemExit("patch %08x (%s): image has %s, expected %s" % (va, why, have.hex(), old.hex()))
            assert len(new) == len(old), (hex(va), len(old), len(new))
            pe.set_bytes_at_offset(off, new)


# ---------------------------------------------------------------- stage 2

def pass_targets():
    """(slice, va) of every function whose latest strict verdict is PASS."""
    latest = {}
    files = sorted(glob.glob(os.path.join(ROOT, "work", "difftest", "backlog_shard*.json")))
    files += sorted(glob.glob(os.path.join(ROOT, "work", "difftest", "refix_shard*.json")))  # newer: wins
    for f in files:
        rows = json.load(open(f))
        rows = rows if isinstance(rows, list) else list(rows.values())
        for r in rows:
            if isinstance(r, dict) and "verdict" in r:
                latest[(r["slice"], r["va"].lower())] = r["verdict"]
    return sorted(k for k, v in latest.items() if v == "PASS")


def file_targets(path):
    out = []
    for line in open(path):
        line = line.split("#")[0].split()
        if len(line) >= 2:
            out.append((line[0], line[1].lower().replace("0x", "")))
    return out


class Splicer:
    """Collects relocated sections for the two new PE sections and the jmp hooks."""

    def __init__(self, img, x_rva, log):
        self.img = img
        self.x = bytearray()        # .hybx: code + read-only data
        self.d = bytearray()        # .hybd: writable data (placed after .hybx, address fixed at the end)
        self.x_va = BASE + x_rva
        self.hooks = []             # (va, entry, sid, nbytes)
        self.pending_d = []         # (x_offset_of_reloc, d_offset, kind) fixups once .hybd's address is known
        self.log = log
        self.skipped = {}
        import capstone
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.md.detail = True   # for instruction prefixes
        # The resolver sends CRT functions the image lacks (fabs, sqrt, sin, cos) to emulator-only
        # helper addresses (machine.BUILTIN_ADDR). Carry the same seven-byte x87 stubs in .hybx and
        # redirect those addresses there; without this a hook calling fabs jumps to 0x7f8e0020.
        import machine as M
        self.builtin = {}
        for name, addr in sorted(M.BUILTIN_ADDR.items()):
            self.x += b"\xcc" * (-len(self.x) % 16)
            self.builtin[addr] = self.x_va + len(self.x)
            self.x += M.BUILTINS[name]

    def skip(self, why, sid, va):
        self.skipped.setdefault(why, []).append("%s:%s" % (sid, va))

    def orig_returns_eax(self, lo, hi):
        """True if every `ret` of the original is preceded (ignoring pops / esp adds) by an
        instruction that writes eax other than a call: the function returns a value."""
        import capstone
        EAX = {capstone.x86.X86_REG_EAX, capstone.x86.X86_REG_AX, capstone.x86.X86_REG_AL, capstone.x86.X86_REG_AH}
        ins = list(self.md.disasm(self.img.read(lo, hi - lo), lo))
        rets = [k for k, i in enumerate(ins) if i.mnemonic == "ret"]
        if not rets:
            return False
        # (d) a call-free function whose first write to eax loads an argument (stack or ecx) returns
        # a pointer derived from it (lower_bound -> position, copy -> destination end, init ->
        # this). All four instances found in the hybrid had this shape.
        if not any(i.mnemonic == "call" for i in ins):
            writers = []
            for k, i in enumerate(ins):
                try:
                    _r, w = i.regs_access()
                except Exception:
                    return False
                if any(r in EAX for r in w) and i.mnemonic not in ("push", "pop"):
                    writers.append(k)
            if writers:
                first = ins[writers[0]]
                loads = first.mnemonic == "mov" and first.op_str.startswith("eax, dword ptr [")
                # the first eax value is an argument or a load, and nothing rewrites eax afterwards:
                # the function hands that value back (pop-front leaf 0x1141200 returned the node)
                if (loads or first.op_str == "eax, ecx") and len(writers) == 1:
                    return True
                if first.mnemonic == "mov" and (first.op_str.startswith(("eax, dword ptr [esp", "eax, dword ptr [ebp"))
                                                or first.op_str == "eax, ecx"):
                    return True
        for k in rets:
            # Walk back from the ret to the last instruction that writes eax (linear order: an
            # approximation of the path). A call means eax is a callee's leftover: not a return
            # value. Then accept only the patterns seen to bite, to keep false positives down:
            #   (a) the writer sits right before the ret (ignoring pops / add esp): explicit result;
            #   (b) `mov eax, [esp+N]` followed by a store through [eax]: hidden return pointer;
            #   (c) `mov eax, ecx` (this) kept to the ret: `return *this`-style.
            j = k - 1
            writer = None
            while j >= 0:
                i = ins[j]
                if i.mnemonic == "call":
                    break
                try:
                    _r, w = i.regs_access()
                except Exception:
                    break
                if any(r in EAX for r in w) and i.mnemonic not in ("push", "pop"):
                    writer = j
                    break
                j -= 1
            if writer is None:
                return False
            between = ins[writer + 1:k]
            trailing = all(x.mnemonic in ("pop", "leave") or (x.mnemonic == "add" and x.op_str.startswith("esp"))
                           for x in between)
            w = ins[writer]
            retptr = w.mnemonic == "mov" and w.op_str.startswith("eax, dword ptr [esp") and \
                any(x.op_str.startswith("dword ptr [eax") for x in between if x.mnemonic == "mov")
            this_ret = w.mnemonic == "mov" and w.op_str == "eax, ecx"
            if not (trailing or retptr or this_ret):
                return False
        return True

    def rets(self, code, va):
        """The set of `ret N` immediates in a code blob (0 for a plain ret)."""
        return {int(i.op_str, 16) if i.op_str else 0 for i in self.md.disasm(code, va) if i.mnemonic == "ret"}

    def has_call(self, code):
        return any(i.mnemonic == "call" for i in self.md.disasm(code, 0x10000000))

    def writes_eax_after_last_call(self, code, va):
        """True if an instruction after the last call (other than push/pop) writes eax."""
        import capstone
        EAX = {capstone.x86.X86_REG_EAX, capstone.x86.X86_REG_AX, capstone.x86.X86_REG_AL, capstone.x86.X86_REG_AH}
        ins = list(self.md.disasm(code, va))
        last = max((k for k, i in enumerate(ins) if i.mnemonic == "call"), default=None)
        if last is None:
            return False
        for i in ins[last + 1:]:
            if i.mnemonic in ("push", "pop"):
                continue
            try:
                _r, w = i.regs_access()
            except Exception:
                continue
            if any(r in EAX for r in w):
                return True
        return False

    def atomics(self, code, va):
        """Number of implicitly or explicitly locked memory operations in a code blob."""
        n = 0
        for i in self.md.disasm(code, va):
            if (i.prefix and 0xF0 in i.prefix) or (i.mnemonic == "xchg" and "[" in i.op_str):
                n += 1
        return n

    def add(self, t):
        """Lay out t.res.local_sections, apply relocations, record the hook."""
        coff, res, fsym = t.coff, t.res, t.fsym
        if res.unresolved:
            return self.skip("unresolved", t.sid, "%08x" % t.va)
        if t.orig_hi - t.orig_lo < 5:
            return self.skip("original shorter than a jmp", t.sid, "%08x" % t.va)
        fsec, f_lo, f_hi = coff.func_extent(fsym)
        # Calling convention: every `ret N` of ours must be one the original uses. `ret 4` against
        # the original's `ret` leaves the caller's stack 4 bytes off at every call (UTFWin crashes
        # at 0x959bd7 / 0x958a09, 2026-10-12). The original's extent may hold two ret forms when the
        # function table merges a neighbour, hence subset rather than equality.
        r_orig = self.rets(self.img.read(t.orig_lo, t.orig_hi - t.orig_lo), t.orig_lo)
        r_ours = self.rets(fsec.data[f_lo:f_hi], 0x10000000)
        if r_orig and r_ours and not r_ours <= r_orig:
            return self.skip("calling convention: ret N differs from the original", t.sid,
                             "%08x(orig %s ours %s)" % (t.va, sorted(r_orig), sorted(r_ours)))
        # The equivalence harness is single-threaded and cannot see atomicity: a `++refcount` where
        # the original has `lock xadd` passes it and then races in the game. Refuse such hooks.
        a_orig = self.atomics(self.img.read(t.orig_lo, t.orig_hi - t.orig_lo), t.orig_lo)
        a_ours = self.atomics(fsec.data[f_lo:f_hi], 0x10000000)
        if a_orig != a_ours:
            return self.skip("atomicity mismatch (locked ops original vs ours)", t.sid, "%08x(%d/%d)" % (t.va, a_orig, a_ours))
        # A function declared void whose original writes eax right before every ret returns a value
        # we do not (hidden return pointer, `return *this`, ...): callers read garbage from eax.
        # Constructors are exempt (thiscall ctors return `this` in eax on both sides). Two hybrid
        # crashes came from this (uninitialized_copy 0x99efa0, rbtree::find 0xe5c780).
        sig = getattr(t, "sig", None)
        if sig is not None and sig.ret == "void" and not fsym.name.startswith("??0"):
            if self.orig_returns_eax(t.orig_lo, t.orig_hi):
                return self.skip("declared void but the original returns a value in eax", t.sid, "%08x" % t.va)
            # A void wrapper whose original keeps its last callee's eax untouched to the ret returns
            # that result (an allocation callback, Pool_AllocGlobal 0x928ad0); ours must not write
            # eax after its last call then.
            orig_code = self.img.read(t.orig_lo, t.orig_hi - t.orig_lo)
            if self.has_call(orig_code) and not self.writes_eax_after_last_call(orig_code, t.orig_lo) \
                    and self.writes_eax_after_last_call(fsec.data[f_lo:f_hi], 0x10000000):
                return self.skip("declared void but ours clobbers the last callee's eax that the original returns",
                                 t.sid, "%08x" % t.va)
        secs = sorted(res.local_sections)
        if (fsym.secno - 1) not in secs:
            secs.append(fsym.secno - 1)
        # placement: x-group at known addresses now; d-group at offsets, addresses fixed later
        place = {}
        xs, ds = [], []
        for i in secs:
            s = coff.sections[i]
            (ds if s.writable else xs).append(i)
        x_off = len(self.x)
        for i in xs:
            s = coff.sections[i]
            x_off = align(x_off, max(s.align, 4))
            place[i] = ("x", x_off)
            x_off += max(len(s.data), 1)
        d_off = len(self.d)
        for i in ds:
            s = coff.sections[i]
            d_off = align(d_off, max(s.align, 4))
            place[i] = ("d", d_off)
            d_off += max(len(s.data), 1)

        def sym_addr(si):
            """(absolute address or None, d_offset or None)"""
            if si in res.addr:
                a = res.addr[si]
                return self.builtin.get(a, a), None
            s = coff.syms[si]
            if s.defined and (s.secno - 1) in place:
                g, off = place[s.secno - 1]
                if g == "x":
                    return self.x_va + off + s.value, None
                return None, off + s.value
            return None, None

        # relocate into local buffers first; commit only if every reloc resolves
        xbuf = bytearray(x_off - len(self.x))
        dbuf = bytearray(d_off - len(self.d))
        fixups = []
        for i in secs:
            s = coff.sections[i]
            g, off = place[i]
            buf, base_off = (xbuf, len(self.x)) if g == "x" else (dbuf, len(self.d))
            data = bytearray(s.data)
            for (roff, si, typ) in s.relocs:
                tgt, dref = sym_addr(si)
                if tgt is None and dref is None:
                    return self.skip("symbol not placed: " + coff.syms[si].name[:40], t.sid, "%08x" % t.va)
                p = (self.x_va + off + roff) if g == "x" else None   # own address, known only for x
                if typ == REL_DIR32:
                    if dref is not None:
                        fixups.append((g, off + roff, dref, "abs"))
                        continue
                    v = (struct.unpack_from("<I", data, roff)[0] + tgt) & 0xFFFFFFFF
                elif typ == REL_REL32:
                    if g == "d" or dref is not None:
                        fixups.append((g, off + roff, dref if dref is not None else tgt, "rel" if dref is not None else "rel-abs"))
                        continue
                    v = (struct.unpack_from("<i", data, roff)[0] + tgt - (p + 4)) & 0xFFFFFFFF
                elif typ == REL_DIR32NB:
                    if dref is not None:
                        fixups.append((g, off + roff, dref, "rva"))
                        continue
                    v = (struct.unpack_from("<I", data, roff)[0] + tgt - BASE) & 0xFFFFFFFF
                else:
                    continue
                struct.pack_into("<I", data, roff, v)
            buf[off - base_off: off - base_off + len(data)] = data
        self.x += xbuf
        self.d += dbuf
        self.pending_d += fixups
        g, off = place[fsym.secno - 1]
        entry = self.x_va + off + fsym.value
        self.hooks.append((t.va, entry, t.sid, t.orig_hi - t.orig_lo))
        return True

    def finish(self, d_rva):
        """Resolve fixups that needed .hybd's address; return (x_bytes, d_bytes)."""
        d_va = BASE + d_rva
        for g, off, ref, kind in self.pending_d:
            buf = self.x if g == "x" else self.d
            own = (self.x_va if g == "x" else d_va) + off
            cur = struct.unpack_from("<I", buf, off)[0]
            if kind == "abs":
                v = cur + d_va + ref
            elif kind == "rva":
                v = cur + d_rva + ref
            elif kind == "rel":
                v = (struct.unpack_from("<i", buf, off)[0] + d_va + ref - (own + 4))
            else:  # rel-abs: REL32 from writable data to an absolute target
                v = (struct.unpack_from("<i", buf, off)[0] + ref - (own + 4))
            struct.pack_into("<I", buf, off, v & 0xFFFFFFFF)
        return bytes(self.x), bytes(self.d)


def add_section(pe, name, rva, data, flags):
    last = pe.sections[-1]
    fa = pe.OPTIONAL_HEADER.FileAlignment
    raw_ptr = align(len(pe.__data__), fa)
    raw = data.ljust(align(max(len(data), 1), fa), b"\0")
    sec = pefile.SectionStructure(pe.__IMAGE_SECTION_HEADER_format__, pe=pe)
    sec.__unpack__(bytearray(sec.sizeof()))
    sec.set_file_offset(last.get_file_offset() + last.sizeof())
    sec.Name = name.encode().ljust(8, b"\0")
    sec.Misc_VirtualSize = max(len(data), 1)
    sec.VirtualAddress = rva
    sec.SizeOfRawData = len(raw)
    sec.PointerToRawData = raw_ptr
    sec.PointerToRelocations = sec.PointerToLinenumbers = 0
    sec.NumberOfRelocations = sec.NumberOfLinenumbers = 0
    sec.Characteristics = flags
    pe.__data__ = bytearray(pe.__data__).ljust(raw_ptr, b"\0") + raw
    pe.sections.append(sec)
    pe.__structures__.append(sec)
    pe.FILE_HEADER.NumberOfSections += 1
    pe.OPTIONAL_HEADER.SizeOfImage = align(rva + sec.Misc_VirtualSize, pe.OPTIONAL_HEADER.SectionAlignment)
    return sec


def splice(pe, targets, verbose, limit=None):
    import equiv as E
    ctx = E.context()
    img = ctx["img"]
    sa = pe.OPTIONAL_HEADER.SectionAlignment
    x_rva = align(pe.OPTIONAL_HEADER.SizeOfImage, sa)
    sp = Splicer(img, x_rva, print)
    quiet = lambda *a, **k: None
    n = 0
    for sid, va in targets[:limit] if limit else targets:
        vai = int(va, 16)
        try:
            t = E.prepare(sid, vai, log=quiet)
        except Exception as e:  # a slice the harness cannot handle must not stop the build
            sp.skip("prepare raised " + type(e).__name__, sid, va)
            continue
        if t.verdict is not None:
            sp.skip("unsupported: " + (getattr(t, "reason", "") or "").split(":")[0][:50], sid, va)
            continue
        if sp.add(t) is True:
            n += 1
            if verbose:
                print("hook %08x -> %08x  %s  (%d local bytes)" % (vai, sp.hooks[-1][1], sid, len(sp.x)))
    d_rva = align(x_rva + max(len(sp.x), 1), sa)
    xb, db = sp.finish(d_rva)
    add_section(pe, ".hybx", x_rva, xb, 0x60000020)      # code | execute | read
    add_section(pe, ".hybd", d_rva, db, 0xC0000040)      # idata | read | write
    for va, entry, sid, _n in sp.hooks:
        off = pe.get_offset_from_rva(va - BASE)
        pe.set_bytes_at_offset(off, bytes([JMP]) + struct.pack("<i", entry - (va + 5)))
    print("hooked %d functions; .hybx %d bytes, .hybd %d bytes" % (n, len(xb), len(db)))
    for why, lst in sorted(sp.skipped.items(), key=lambda kv: -len(kv[1])):
        print("  skipped %4d  %s%s" % (len(lst), why, ("  e.g. " + " ".join(lst[:3])) if verbose else ""))
    return sp


def verify_exact(n, verbose):
    """Lay out n byte-exact functions through the same path and diff them against the original.
    Bytes under a relocation that resolved to one of our own local sections are expected to differ."""
    import random
    import equiv as E
    import slice as S
    ctx = E.context()
    img = ctx["img"]
    rows = []
    for m in glob.glob(os.path.join(ROOT, "match", "slices", "*", "manifest.txt")):
        sid = os.path.basename(os.path.dirname(m))
        for line in open(m):
            p = line.split("#", 1)[0].split()   # source  symbol  VA  [flags]
            if len(p) >= 3 and len(p[2]) == 8:
                rows.append((sid, p[2]))
    random.seed(1)
    random.shuffle(rows)
    ok = bad = unsup = 0
    quiet = lambda *a, **k: None
    for sid, va in rows[:n]:
        vai = int(va, 16)
        try:
            t = E.prepare(sid, vai, log=quiet)
        except Exception as e:
            unsup += 1
            if verbose:
                print("  %s %s: prepare raised %s" % (sid, va, e))
            continue
        if t.verdict is not None or t.res.unresolved:
            unsup += 1
            continue
        # place the function at its original address (rel32 displacements only match from there):
        # a dry run gives the entry offset, the real run shifts the base by the difference
        sp = Splicer(img, 0x2000000, print)
        if sp.add(t) is not True:
            unsup += 1
            continue
        shift = vai - sp.hooks[0][1]
        sp = Splicer(img, 0x2000000 + shift, print)
        sp.add(t)
        xb, _db = sp.finish(0x2100000 + shift)
        _va, entry, _sid, size = sp.hooks[0]
        assert entry == vai
        mine = xb[entry - sp.x_va: entry - sp.x_va + size]
        theirs = img.read(vai, size)
        # classify differing bytes by the relocation covering them: a reference to one of our own
        # local sections (string/float literal, static) is expected to differ; a reference resolved
        # to a different original address, or a byte outside any relocation, is a real difference
        sec, f0 = t.coff.section_of(t.fsym), t.fsym.value
        relocs = {}
        for off, si, typ in sec.relocs:
            if f0 <= off < f0 + size:
                for k in range(4):
                    relocs[off - f0 + k] = (off - f0, si)
        local, other, raw = set(), {}, []
        for i in range(min(len(mine), len(theirs))):
            if mine[i] == theirs[i]:
                continue
            if i in relocs:
                o, si = relocs[i]
                s = t.coff.syms[si]
                if si in t.res.addr:
                    other[o] = "%s(%s)" % (s.name[:40], t.res.method.get(s.name, "?"))
                else:
                    local.add(o)
            else:
                raw.append(i)
        if other or raw:
            bad += 1
            if verbose:
                print("  DIFF %s %s: %d raw bytes, %d local refs, other resolution: %s"
                      % (sid, va, len(raw), len(local), ", ".join(sorted(set(other.values()))[:4]) or "-"))
        else:
            ok += 1
    print("verify-exact: %d identical, %d differ, %d not laid out (of %d sampled)" % (ok, bad, unsup, n))
    return bad == 0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=os.path.join(ROOT, "work", "hybrid", "SporeApp.hybrid.exe"))
    ap.add_argument("--no-patches", action="store_true")
    ap.add_argument("--hook", default="none", help="pass | none | FILE of '<slice> <va>' lines")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--exclude", default="", help="comma-separated slice ids / VAs, or @FILE with one per line")
    ap.add_argument("--verify-exact", type=int, metavar="N")
    ap.add_argument("-v", action="store_true")
    a = ap.parse_args()
    if a.verify_exact:
        sys.exit(0 if verify_exact(a.verify_exact, a.v) else 1)
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    pe = pefile.PE(IMAGE)
    pe.__data__ = bytearray(pe.__data__)
    make_runnable(pe, patches=not a.no_patches)
    sp = None
    if a.hook != "none":
        targets = pass_targets() if a.hook == "pass" else file_targets(a.hook)
        # tools/hybrid/known_bad.txt: hooks the hybrid disproved whose fix is not in the source yet
        ex = {v for _s, v in file_targets(os.path.join(os.path.dirname(os.path.abspath(__file__)), "known_bad.txt"))}
        if a.exclude:
            more = open(a.exclude[1:]).read().split() if a.exclude.startswith("@") else a.exclude.split(",")
            ex |= {e.strip().lower().replace("0x", "") for e in more if e.strip()}
        before = len(targets)
        targets = [(s, v) for s, v in targets if s not in ex and v not in ex]
        if before != len(targets):
            print("excluded %d (known_bad.txt / --exclude)" % (before - len(targets)))
        print("%d candidate functions" % len(targets))
        sp = splice(pe, targets, a.v, a.limit)
    pe.OPTIONAL_HEADER.CheckSum = pe.generate_checksum()
    pe.write(a.out)
    if sp is not None:
        json.dump({"hooks": [{"va": "%08x" % va, "entry": "%08x" % e, "slice": s, "orig_size": n} for va, e, s, n in sp.hooks],
                   "skipped": sp.skipped}, open(a.out + ".hooks.json", "w"), indent=1)
    print("wrote", a.out)


if __name__ == "__main__":
    main()
