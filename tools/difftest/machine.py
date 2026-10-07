"""Unicorn machine for the equivalence harness.

Maps the analysis image at its preferred base with per-section protections (code R-X, .rdata R,
.data RW), routes every IAT slot to a stub (Python handler or a few bytes of native x87 code),
gives FS a TEB, and loads OUR object's sections (relocated to original addresses) next to it.
Every byte a run can write is put back before the next run, so the two sides of a test (and
successive inputs) never see each other's leftovers:
- image .data/.bss/.tls and our object's writable data: compared to a baseline and restored;
- the DYN heap (malloc) and the MISC region (TEB, TLS, scratch): a write hook and `write()` record
  the dirty pages, which are compared and restored after the run (`take_dirty`), including pages
  beyond `dyn_next` reached through garbage indices;
- the stack: refilled before every run; pool objects: unmapped after every run;
- code, .rdata, import stubs, the sentinel page and the GDT are not writable at all: emulated
  writes fault, and `write()` (used by import handlers such as memcpy) raises a write-protection
  fault instead of silently patching code.
"""
import ctypes, math, struct

from unicorn import (Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_BLOCK,
                     UC_HOOK_MEM_UNMAPPED, UC_HOOK_MEM_PROT, UC_HOOK_INSN, UC_HOOK_MEM_WRITE,
                     UC_ERR_WRITE_PROT,
                     UC_PROT_READ, UC_PROT_WRITE, UC_PROT_EXEC, UC_PROT_ALL)
from unicorn import unicorn_const as UCC
from unicorn.unicorn_py3.arch import intel
from unicorn.unicorn_py3.unicorn import uccallback
from unicorn.x86_const import *  # noqa: F401,F403

from coff import REL_DIR32, REL_DIR32NB, REL_REL32

OBJ_BASE = 0x30000000
POOL_BASE, POOL_SIZE = 0x40000000, 0x10000000     # lazily materialised input objects (64 KB slots)
SLOT = 0x10000
# Pool objects (64 KB slots) one run may materialise: 4 MB. Each is one Unicorn mem_map, whose cost
# grows steeply with the number of mapped regions (31 us each at 100 regions, 5.6 ms at 2000), so
# slots are mapped whole rather than per 4 KB page, and runaway loops on random inputs stop here.
MAX_POOL_SLOTS = 64
DYN_BASE, DYN_SIZE = 0x50000000, 0x04000000
STACK_TOP, STACK_SIZE = 0x7E000000, 0x00200000
SENTINEL = 0x7EFFF000
STUB_BASE = 0x7F000000
STUB_SLOT = 32
MISC_BASE, MISC_SIZE = 0x7F800000, 0x00100000   # TEB, TLS blocks, scratch
TRAP_BASE = 0x7C000000                          # unresolved (non-required) symbols: never mapped
GDT_BASE = 0x7FF00000
INIT_CODE = MISC_BASE + 0xF0000

BUILTIN_BASE = MISC_BASE + 0xE0000              # native helpers for CRT functions the image lacks
BUILTINS = {   # symbol -> code (cdecl double arg at [esp+4], result in st0)
    "_fabs": b"\xdd\x44\x24\x04\xd9\xe1\xc3",
    "_sqrt": b"\xdd\x44\x24\x04\xd9\xfa\xc3",
    "_sin": b"\xdd\x44\x24\x04\xd9\xfe\xc3",
    "_cos": b"\xdd\x44\x24\x04\xd9\xff\xc3",
}
BUILTIN_ADDR = {n: BUILTIN_BASE + 0x20 * i for i, n in enumerate(sorted(BUILTINS))}

FLD_RET_STUB = BUILTIN_BASE + 0x800          # fld dword [SCRATCH+8]; ret  (fake float-returning method)

TEB = MISC_BASE
TLS_ARRAY = MISC_BASE + 0x1000
TLS_BLOCKS = MISC_BASE + 0x2000          # 64 x 0x1000 (TlsGetValue slots + static TLS)
ERRNO_CELL = MISC_BASE + 0x80000
SCRATCH = MISC_BASE + 0x80100            # double result of python float handlers

CALLEE_SAVED = (("ebx", UC_X86_REG_EBX), ("esi", UC_X86_REG_ESI), ("edi", UC_X86_REG_EDI), ("ebp", UC_X86_REG_EBP))


class Stop(Exception):
    pass


def _page(n):
    return (n + 0xFFF) & ~0xFFF


class Machine:
    def __init__(self, image):
        self.img = image
        uc = self.uc = Uc(UC_ARCH_X86, UC_MODE_32)
        base = image.base
        uc.mem_map(base, image.size, UC_PROT_ALL)
        pe = image.pe
        uc.mem_write(base, pe.header[:0x1000])
        for s in pe.sections:
            data = s.get_data()
            vs = max(s.Misc_VirtualSize, len(data))
            uc.mem_write(base + s.VirtualAddress, data[:vs])
        self.stub_names, self.handlers = {}, {}
        self._install_stubs()
        # protections after the IAT is patched
        uc.mem_protect(base, 0x1000, UC_PROT_READ)
        self.writable = []
        self.readonly = [(base, base + 0x1000)]     # ranges write() refuses (code, constants, stubs)
        for nm, va, size, ch in image.sections:
            lo, hi = va, va + _page(size)
            prot = UC_PROT_READ
            if ch & 0x20000000:
                prot |= UC_PROT_EXEC
            if ch & 0x80000000:
                prot |= UC_PROT_WRITE
                self.writable.append((nm, lo, hi))
            else:
                self.readonly.append((lo, hi))
            uc.mem_protect(lo, hi - lo, prot)
        uc.mem_map(DYN_BASE, DYN_SIZE, UC_PROT_READ | UC_PROT_WRITE)
        uc.mem_map(STACK_TOP - STACK_SIZE, STACK_SIZE + 0x1000, UC_PROT_READ | UC_PROT_WRITE)
        uc.mem_map(SENTINEL, 0x1000, UC_PROT_READ | UC_PROT_EXEC)
        uc.mem_map(MISC_BASE, MISC_SIZE, UC_PROT_ALL)
        self._setup_cpu()
        uc.mem_protect(STUB_BASE, _page(self.stub_end - STUB_BASE), UC_PROT_READ | UC_PROT_EXEC)
        uc.mem_protect(GDT_BASE, 0x1000, UC_PROT_READ)
        self.readonly += [(STUB_BASE, _page(self.stub_end)), (SENTINEL, SENTINEL + 0x1000),
                          (GDT_BASE, GDT_BASE + 0x1000)]
        # rdtsc is not deterministic under Unicorn: one instruction hook returns a per-run counter
        # instead. (A code hook per 0F 31 byte pair in .text, 674 of them, made every translation
        # scan them all and halved the harness's speed.)
        self.tsc = 0
        self._rdtsc_cb = uccallback(uc, intel.HOOK_INSN_CPUID_CFUNC)(self._on_rdtsc)
        # The Python binding only maps in/out/syscall/cpuid; rdtsc hooks share cpuid's C signature.
        uc._Uc__do_hook_add(UC_HOOK_INSN, self._rdtsc_cb, 1, 0, ctypes.c_int(UC_X86_INS_RDTSC))
        self.image_baseline = {nm: bytes(uc.mem_read(lo, hi - lo)) for nm, lo, hi in self.writable}
        self.misc_baseline = bytes(uc.mem_read(MISC_BASE, MISC_SIZE))
        # Dirty-page tracking for DYN and MISC: emulated writes through a hook, handler writes in
        # write(). Both sides start from the baseline (zeros / misc_baseline) on every run.
        self.dirty = set()
        self._dirty_hooks = [uc.hook_add(UC_HOOK_MEM_WRITE, self._on_tracked_write, begin=lo, end=hi - 1)
                             for lo, hi in ((DYN_BASE, DYN_BASE + DYN_SIZE), (MISC_BASE, MISC_BASE + MISC_SIZE))]
        self.obj = None
        self.dyn_next = DYN_BASE
        self.dyn_sizes = {}
        self.rand_state = 1
        self.trace_imports = []
        self.stop_reason = None
        self.hooks = []
        self.last_fault = None
        self.lazy = None            # callable(page) -> bytes for pool pages, set by the runner
        self.pool_pages = {}        # page -> initial bytes of every page mapped during this run
        self.pool_slots = []        # slots mapped during this run
        self.pool_entry = set()     # page of the first access to each slot (for mutation)
        uc.hook_add(UC_HOOK_MEM_UNMAPPED | UC_HOOK_MEM_PROT, self._on_bad_mem)

    def _on_tracked_write(self, uc, access, address, size, value, _):
        self.dirty.add(address & ~0xFFF)
        if (address + size - 1) & ~0xFFF != address & ~0xFFF:
            self.dirty.add((address + size - 1) & ~0xFFF)

    @staticmethod
    def tracked(a):
        return DYN_BASE <= a < DYN_BASE + DYN_SIZE or MISC_BASE <= a < MISC_BASE + MISC_SIZE

    def take_dirty(self):
        """-> ({DYN page: bytes}, {MISC page: bytes}) for pages written since the last call that
        differ from the baseline; restores every dirty page."""
        dyn, misc = {}, {}
        zero = b"\0" * 0x1000
        for p in sorted(self.dirty):
            cur = bytes(self.uc.mem_read(p, 0x1000))
            if DYN_BASE <= p < DYN_BASE + DYN_SIZE:
                base, out = zero, dyn
            else:
                base, out = self.misc_base_page(p), misc
            if cur != base:
                out[p] = cur
                self.uc.mem_write(p, base)
        self.dirty = set()
        return dyn, misc

    def misc_base_page(self, p):
        return self.misc_baseline[p - MISC_BASE:p - MISC_BASE + 0x1000]

    def _on_rdtsc(self, uc, _key):
        self.tsc += 100000
        uc.reg_write(UC_X86_REG_EAX, self.tsc & 0xFFFFFFFF)
        uc.reg_write(UC_X86_REG_EDX, 0)
        return 1                    # skip the real rdtsc

    def _on_bad_mem(self, uc, access, address, size, value, _):
        if (access in (UCC.UC_MEM_READ_UNMAPPED, UCC.UC_MEM_WRITE_UNMAPPED) and self.lazy is not None
                and POOL_BASE <= address < POOL_BASE + POOL_SIZE):
            slot = address & ~(SLOT - 1)
            if slot not in self.pool_slots and len(self.pool_slots) < MAX_POOL_SLOTS:
                pages = [self.lazy(slot + k) for k in range(0, SLOT, 0x1000)]
                uc.mem_map(slot, SLOT, UC_PROT_READ | UC_PROT_WRITE)
                uc.mem_write(slot, b"".join(pages))
                for k, data in enumerate(pages):
                    self.pool_pages[slot + k * 0x1000] = data
                self.pool_slots.append(slot)
                self.pool_entry.add(address & ~0xFFF)
                return True
            if slot not in self.pool_slots:
                # Out of pool objects: a runaway walk through memory, not a repairable bad pointer.
                self.last_fault = ("pool-limit", address, size)
                return False
        kind = {UCC.UC_MEM_READ_UNMAPPED: "read", UCC.UC_MEM_WRITE_UNMAPPED: "write",
                UCC.UC_MEM_FETCH_UNMAPPED: "fetch", UCC.UC_MEM_READ_PROT: "read-prot",
                UCC.UC_MEM_WRITE_PROT: "write-prot", UCC.UC_MEM_FETCH_PROT: "fetch-prot"}.get(access, "?")
        self.last_fault = (kind, address, size)
        return False

    # ------------------------------------------------------------------ CPU / segments
    def _setup_cpu(self):
        uc = self.uc
        cr0 = uc.reg_read(UC_X86_REG_CR0)
        uc.reg_write(UC_X86_REG_CR0, (cr0 & ~4) | 2)
        uc.reg_write(UC_X86_REG_CR4, uc.reg_read(UC_X86_REG_CR4) | 0x600)
        uc.mem_map(GDT_BASE, 0x1000, UC_PROT_READ | UC_PROT_WRITE)

        def desc(base, limit, access, flags):
            d = limit & 0xFFFF
            d |= (base & 0xFFFFFF) << 16
            d |= (access & 0xFF) << 40
            d |= ((limit >> 16) & 0xF) << 48
            d |= (flags & 0xF) << 52
            d |= ((base >> 24) & 0xFF) << 56
            return struct.pack("<Q", d)
        gdt = (b"\0" * 8 + desc(0, 0xFFFFF, 0x9A, 0xC) + desc(0, 0xFFFFF, 0x92, 0xC)   # 1 code, 2 data (flat)
               + desc(TEB, 0xFFF, 0x92, 0x4))                                        # 3 FS -> TEB
        uc.mem_write(GDT_BASE, gdt)
        uc.reg_write(UC_X86_REG_GDTR, (0, GDT_BASE, len(gdt) - 1, 0))
        uc.reg_write(UC_X86_REG_CS, 1 << 3)
        for r in (UC_X86_REG_SS, UC_X86_REG_DS, UC_X86_REG_ES, UC_X86_REG_GS):
            uc.reg_write(r, 2 << 3)
        uc.reg_write(UC_X86_REG_FS, 3 << 3)
        # Clean control state, restored before every run: a garbage input can make the emulated
        # code load a bogus CS or set EFLAGS.VM (iret/retf/popfd), which broke every later run.
        # Setting a segment register one at a time fails once the CPL has changed, so the whole CPU
        # context (incl. hidden segment state) is snapshotted here and restored in reset_cpu.
        self.gdt_bytes = gdt
        uc.reg_write(UC_X86_REG_EFLAGS, 0x202)
        self.cpu_ctx = uc.context_save()
        teb = bytearray(0x1000)
        struct.pack_into("<IIII", teb, 0, 0xFFFFFFFF, STACK_TOP, STACK_TOP - STACK_SIZE, 0)
        struct.pack_into("<I", teb, 0x18, TEB)
        struct.pack_into("<I", teb, 0x2C, TLS_ARRAY)
        uc.mem_write(TEB, bytes(teb))
        tls_tmpl = self.img.section(".tls")
        tmpl = self.img.read(tls_tmpl[0], tls_tmpl[1]) if tls_tmpl else b""
        arr = b"".join(struct.pack("<I", TLS_BLOCKS + 0x1000 * i) for i in range(64))
        uc.mem_write(TLS_ARRAY, arr)
        for i in range(64):
            uc.mem_write(TLS_BLOCKS + 0x1000 * i, tmpl[:0x1000])
        cw = INIT_CODE + 0x40
        uc.mem_write(cw, struct.pack("<HI", 0x027F, 0x1F80))
        code = b"\xdb\xe3" + b"\xd9\x2d" + struct.pack("<I", cw) + b"\x0f\xae\x15" + struct.pack("<I", cw + 2)
        uc.mem_write(INIT_CODE, code)
        for n, a in BUILTIN_ADDR.items():
            uc.mem_write(a, BUILTINS[n])
        uc.mem_write(FLD_RET_STUB, b"\xd9\x05" + struct.pack("<I", SCRATCH + 8) + b"\xc3")
        self.init_end = INIT_CODE + len(code)

    def reset_cpu(self, regs, xmm):
        uc = self.uc
        uc.mem_write(GDT_BASE, self.gdt_bytes)
        uc.context_restore(self.cpu_ctx)
        uc.reg_write(UC_X86_REG_ESP, STACK_TOP - 0x100)
        uc.emu_start(INIT_CODE, self.init_end)
        for k in range(8):          # no stale x87 register contents from the previous run
            uc.reg_write(UC_X86_REG_FP0 + k, (0, 0))
        for r, v in regs.items():
            uc.reg_write(r, v & 0xFFFFFFFF)
        for k, v in enumerate(xmm):
            uc.reg_write(UC_X86_REG_XMM0 + k, v)
        uc.reg_write(UC_X86_REG_EFLAGS, 0x202)

    # ------------------------------------------------------------------ imports
    def _install_stubs(self):
        uc = self.uc
        n = len(self.img.imports)
        uc.mem_map(STUB_BASE, _page(n * STUB_SLOT), UC_PROT_READ | UC_PROT_EXEC | UC_PROT_WRITE)
        install_crt(self)
        for i, (iat, full) in enumerate(sorted(self.img.imports.items())):
            name = full.split("!", 1)[1]
            stub = STUB_BASE + STUB_SLOT * i
            h = self.handlers.get(name)
            code = b"\xc3"
            if h is not None:
                code = h["code"]
            uc.mem_write(stub, code.ljust(STUB_SLOT, b"\xcc"))
            uc.mem_write(iat, struct.pack("<I", stub))
            self.stub_names[stub] = name
        self.stub_end = STUB_BASE + STUB_SLOT * n
        uc.hook_add(UC_HOOK_CODE, self._on_stub, begin=STUB_BASE, end=self.stub_end - 1)

    def handle(self, name, fn=None, nargs=0, pops=0, code=None, fresult=False):
        """fn(machine, args) -> eax (or float when fresult; then the stub does fld [SCRATCH])."""
        if code is None:
            if fresult:
                code = b"\xdd\x05" + struct.pack("<I", SCRATCH)
            else:
                code = b""
            code += (b"\xc2" + struct.pack("<H", pops * 4)) if pops else b"\xc3"
        self.handlers[name] = {"fn": fn, "nargs": nargs, "pops": pops, "code": code, "fresult": fresult}

    def _on_stub(self, uc, address, size, _):
        if (address - STUB_BASE) % STUB_SLOT:
            return
        name = self.stub_names.get(address)
        h = self.handlers.get(name)
        esp = uc.reg_read(UC_X86_REG_ESP)
        if h is None:
            self.stop_reason = ("import", name)
            uc.emu_stop()
            return
        args = [self.u32(esp + 4 + 4 * k) for k in range(h["nargs"])]
        self.trace_imports.append((name, tuple(args)))
        if h["fn"] is None:
            return
        try:
            res = h["fn"](self, args, esp)
        except Stop as e:
            self.stop_reason = ("import", "%s: %s" % (name, e))
            uc.emu_stop()
            return
        except UcError as e:
            self.stop_reason = ("fault", "%s in import %s" % (e, name))
            uc.emu_stop()
            return
        if h["fresult"]:
            self.write(SCRATCH, struct.pack("<d", res))
        elif isinstance(res, tuple):
            uc.reg_write(UC_X86_REG_EAX, res[0] & 0xFFFFFFFF)
            uc.reg_write(UC_X86_REG_EDX, res[1] & 0xFFFFFFFF)
        elif res is not None:
            uc.reg_write(UC_X86_REG_EAX, res & 0xFFFFFFFF)

    # ------------------------------------------------------------------ memory helpers
    def u32(self, a):
        return struct.unpack("<I", self.uc.mem_read(a, 4))[0]

    def read(self, a, n):
        return bytes(self.uc.mem_read(a, n))

    def write(self, a, data):
        """Write on behalf of the emulated program (import handlers, input setup): refuses read-only
        memory (a write-protection fault, as the CPU would raise) and records dirty pages."""
        n = len(data)
        if n:
            e = a + n
            for lo, hi in self.readonly:
                if a < hi and e > lo:
                    raise UcError(UC_ERR_WRITE_PROT)
            if self.tracked(a) or self.tracked(e - 1):
                for p in range(a & ~0xFFF, e, 0x1000):
                    if self.tracked(p):
                        self.dirty.add(p)
        self.uc.mem_write(a, bytes(data))

    def cstr(self, a, wide=False, limit=1 << 16):
        out = bytearray()
        step = 2 if wide else 1
        while len(out) < limit:
            ch = self.read(a + len(out), step)
            if ch == b"\0" * step:
                break
            out += ch
        return bytes(out)

    def unmap_pool(self):
        """-> {page: bytes after the run}; unmaps every materialised pool slot."""
        out = {}
        for slot in self.pool_slots:
            data = bytes(self.uc.mem_read(slot, SLOT))
            for k in range(0, SLOT, 0x1000):
                out[slot + k] = data[k:k + 0x1000]
            self.uc.mem_unmap(slot, SLOT)
        self.pool_pages = {}
        self.pool_slots = []
        return out

    def dyn_alloc(self, n, align=16):
        a = (self.dyn_next + align - 1) & ~(align - 1)
        if a + n > DYN_BASE + DYN_SIZE or n > DYN_SIZE:
            raise Stop("emulated heap exhausted (%d bytes)" % n)
        self.dyn_next = a + n
        self.dyn_sizes[a] = n
        return a

    # ------------------------------------------------------------------ our object
    def load_object(self, coff, res, func_sym):
        """Map the sections of `coff` listed in res.local_sections at OBJ_BASE, relocated.
        Returns {"entry", "code": [(lo, hi)], "data_rw": [(lo, hi)], "symaddr": {index: addr}}."""
        uc = self.uc
        if self.obj is not None:
            uc.mem_unmap(self.obj["map_lo"], self.obj["map_hi"] - self.obj["map_lo"])
        secs = sorted(res.local_sections)
        groups = {"x": [], "r": [], "w": []}
        for i in secs:
            s = coff.sections[i]
            groups["x" if s.is_code else ("w" if s.writable else "r")].append(i)
        addr = {}
        cur = OBJ_BASE
        spans = {}
        for g in ("x", "r", "w"):
            cur = _page(cur)
            lo = cur
            for i in groups[g]:
                s = coff.sections[i]
                al = max(s.align, 4)
                cur = (cur + al - 1) & ~(al - 1)
                addr[i] = cur
                cur += max(len(s.data), 1)
            spans[g] = (lo, _page(cur) if cur > lo else lo)
            cur = _page(cur)
        map_lo, map_hi = OBJ_BASE, max(_page(cur), OBJ_BASE + 0x1000)
        uc.mem_map(map_lo, map_hi - map_lo, UC_PROT_ALL)
        trap = {}

        def sym_addr(si):
            if si in res.addr:
                return res.addr[si]
            s = coff.syms[si]
            if s.defined and (s.secno - 1) in addr:
                return addr[s.secno - 1] + s.value
            if si not in trap:
                trap[si] = TRAP_BASE + 0x10 * len(trap)
            return trap[si]
        for i in secs:
            s = coff.sections[i]
            data = bytearray(s.data)
            for (off, si, typ) in s.relocs:
                tgt = sym_addr(si)
                p = addr[i] + off
                if typ == REL_DIR32:
                    v = (struct.unpack_from("<I", data, off)[0] + tgt) & 0xFFFFFFFF
                elif typ == REL_REL32:
                    v = (struct.unpack_from("<i", data, off)[0] + tgt - (p + 4)) & 0xFFFFFFFF
                elif typ == REL_DIR32NB:
                    v = (struct.unpack_from("<I", data, off)[0] + tgt - self.img.base) & 0xFFFFFFFF
                else:
                    continue
                struct.pack_into("<I", data, off, v)
            uc.mem_write(addr[i], bytes(data))
        self.readonly = [r for r in self.readonly if not (OBJ_BASE <= r[0] < POOL_BASE)]
        for g, prot in (("x", UC_PROT_READ | UC_PROT_EXEC), ("r", UC_PROT_READ), ("w", UC_PROT_READ | UC_PROT_WRITE)):
            lo, hi = spans[g]
            if hi > lo:
                uc.mem_protect(lo, hi - lo, prot)
                if g != "w":
                    self.readonly.append((lo, hi))
        if map_hi > spans["w"][1] and spans["w"][1] >= map_lo:
            pass
        self.obj = {
            "map_lo": map_lo, "map_hi": map_hi,
            "entry": addr[func_sym.secno - 1] + func_sym.value,
            "code": [(addr[i], addr[i] + len(coff.sections[i].data)) for i in groups["x"]],
            "func_range": (addr[func_sym.secno - 1], addr[func_sym.secno - 1] + len(coff.sections[func_sym.secno - 1].data)),
            "data_rw": [spans["w"]] if spans["w"][1] > spans["w"][0] else [],
            "sec_addr": addr,
            "trap": {v: coff.syms[k].name for k, v in trap.items()},
        }
        self.obj["rw_baseline"] = [self.read(lo, hi - lo) for lo, hi in self.obj["data_rw"]]
        return self.obj

    # ------------------------------------------------------------------ run
    def run(self, entry, ret_esp_frame, budget, seconds=0):
        """Start at entry with the stack frame already written (esp set by caller).
        A fetch fault at a non-code address is offered to self.fake_handler (a call through a
        generated function pointer): it may emulate a do-nothing method and the run resumes."""
        import time as _time
        uc = self.uc
        self.stop_reason = None
        self.fake_calls = 0
        self.tsc = 0x1000000
        start = entry
        t_end = _time.time() + seconds if seconds else None
        while True:
            self.last_fault = None
            err = None
            left = max(1, int((t_end - _time.time()) * 1e6)) if t_end else 0
            try:
                uc.emu_start(start, SENTINEL, timeout=left, count=budget)
            except UcError as e:
                err = e
            eip = uc.reg_read(UC_X86_REG_EIP)
            if self.stop_reason:
                return self.stop_reason
            if err is None:
                break
            if TRAP_BASE <= eip < TRAP_BASE + 0x100000 and self.obj and eip in self.obj["trap"]:
                return ("trap", self.obj["trap"][eip])
            lf = self.last_fault
            if (lf and lf[0] in ("fetch", "fetch-prot") and getattr(self, "fake_handler", None)
                    and self.fake_calls < 5000):
                r = self.fake_handler(eip)
                if r is True:
                    self.fake_calls += 1
                    start = uc.reg_read(UC_X86_REG_EIP)
                    continue
                if isinstance(r, tuple):
                    return r
            return ("fault", "%s at eip=%08x" % (err, eip))
        if eip != SENTINEL:
            return ("budget", "instruction budget %d or %ss exhausted at eip=%08x" % (budget, seconds, eip))
        return ("ok", None)


# ---------------------------------------------------------------------- CRT and Win32 imports

def install_crt(m):
    def d(args, k):
        return struct.unpack("<d", struct.pack("<II", args[k], args[k + 1]))[0]

    def memcpy(m, a, esp):
        if a[2] > 0x4000000:
            raise Stop("huge memcpy %#x" % a[2])
        m.write(a[0], m.read(a[1], a[2]))
        return a[0]

    def memset(m, a, esp):
        if a[2] > 0x4000000:
            raise Stop("huge memset %#x" % a[2])
        m.write(a[0], bytes([a[1] & 0xFF]) * a[2])
        return a[0]

    def memcmp(m, a, esp):
        x, y = m.read(a[0], a[2]), m.read(a[1], a[2])
        return 0 if x == y else (-1 if x < y else 1)

    def memchr(m, a, esp):
        buf = m.read(a[0], a[2])
        i = buf.find(bytes([a[1] & 0xFF]))
        return 0 if i < 0 else a[0] + i

    def strlen(m, a, esp):
        return len(m.cstr(a[0]))

    def cmp(x, y):
        return 0 if x == y else (-1 if x < y else 1)

    def strcmp(m, a, esp):
        return cmp(m.cstr(a[0]), m.cstr(a[1]))

    def strncmp(m, a, esp):
        return cmp(m.cstr(a[0])[:a[2]], m.cstr(a[1])[:a[2]])

    def stricmp(m, a, esp):
        return cmp(m.cstr(a[0]).lower(), m.cstr(a[1]).lower())

    def strnicmp(m, a, esp):
        return cmp(m.cstr(a[0])[:a[2]].lower(), m.cstr(a[1])[:a[2]].lower())

    def w(m, p):
        return m.cstr(p, wide=True).decode("utf-16le", "replace")

    def wcsicmp(m, a, esp):
        return cmp(w(m, a[0]).lower(), w(m, a[1]).lower())

    def wcsnicmp(m, a, esp):
        return cmp(w(m, a[0])[:a[2]].lower(), w(m, a[1])[:a[2]].lower())

    def wcsncmp(m, a, esp):
        return cmp(w(m, a[0])[:a[2]], w(m, a[1])[:a[2]])

    def strchr(m, a, esp):
        s = m.cstr(a[0])
        c = a[1] & 0xFF
        if c == 0:
            return a[0] + len(s)
        i = s.find(bytes([c]))
        return 0 if i < 0 else a[0] + i

    def strrchr(m, a, esp):
        s = m.cstr(a[0])
        c = a[1] & 0xFF
        if c == 0:
            return a[0] + len(s)
        i = s.rfind(bytes([c]))
        return 0 if i < 0 else a[0] + i

    def strstr(m, a, esp):
        i = m.cstr(a[0]).find(m.cstr(a[1]))
        return 0 if i < 0 else a[0] + i

    def wcschr(m, a, esp):
        s = w(m, a[0])
        c = chr(a[1] & 0xFFFF)
        if c == "\0":
            return a[0] + 2 * len(s)
        i = s.find(c)
        return 0 if i < 0 else a[0] + 2 * i

    def wcsrchr(m, a, esp):
        s = w(m, a[0])
        c = chr(a[1] & 0xFFFF)
        if c == "\0":
            return a[0] + 2 * len(s)
        i = s.rfind(c)
        return 0 if i < 0 else a[0] + 2 * i

    def wcsstr(m, a, esp):
        i = w(m, a[0]).find(w(m, a[1]))
        return 0 if i < 0 else a[0] + 2 * i

    def strncpy(m, a, esp):
        s = m.cstr(a[1])[:a[2]]
        m.write(a[0], s + b"\0" * (a[2] - len(s)))
        return a[0]

    def wcsncpy(m, a, esp):
        s = m.cstr(a[1], wide=True)[:2 * a[2]]
        m.write(a[0], s + b"\0" * (2 * a[2] - len(s)))
        return a[0]

    def ctype(pred):
        return lambda m, a, esp: 1 if (a[0] & 0xFFFFFFFF) < 256 and pred(chr(a[0])) else 0

    def malloc(m, a, esp):
        return m.dyn_alloc(max(a[0], 1))

    def aligned_malloc(m, a, esp):
        al = a[1] if a[1] and a[1] & (a[1] - 1) == 0 else 16
        return m.dyn_alloc(max(a[0], 1), max(al, 16))

    def free(m, a, esp):
        return 0

    def realloc(m, a, esp, align=16):
        p, n = a[0], a[1]
        q = m.dyn_alloc(max(n, 1), align)
        if p:
            old = m.dyn_sizes.get(p, 0)
            m.write(q, m.read(p, min(old, n)))
        return q

    def aligned_realloc(m, a, esp):
        return realloc(m, a, esp, max(a[2], 16))

    def rand(m, a, esp):
        m.rand_state = (m.rand_state * 214013 + 2531011) & 0xFFFFFFFF
        return (m.rand_state >> 16) & 0x7FFF

    def srand(m, a, esp):
        m.rand_state = a[0]

    def errno(m, a, esp):
        return ERRNO_CELL

    def atoi(m, a, esp):
        s = m.cstr(a[0]).strip()
        k = 0
        sign = 1
        if s[:1] in (b"-", b"+"):
            sign = -1 if s[:1] == b"-" else 1
            s = s[1:]
        for ch in s:
            if 48 <= ch <= 57:
                k = k * 10 + ch - 48
            else:
                break
        return sign * k

    def isnan(m, a, esp):
        return 1 if math.isnan(d(a, 0)) else 0

    def finite(m, a, esp):
        return 1 if math.isfinite(d(a, 0)) else 0

    def floor(m, a, esp):
        x = d(a, 0)
        return x if not math.isfinite(x) else float(math.floor(x))

    def ceil(m, a, esp):
        x = d(a, 0)
        return x if not math.isfinite(x) else float(math.ceil(x))

    def ldexp(m, a, esp):
        n = struct.unpack("<i", struct.pack("<I", a[2]))[0]
        try:
            return math.ldexp(d(a, 0), n)
        except OverflowError:
            return math.copysign(math.inf, d(a, 0))

    def modf(m, a, esp):
        x = d(a, 0)
        f, i = math.modf(x) if math.isfinite(x) else (0.0, x)
        m.write(a[2], struct.pack("<d", i))
        return f

    def atof(m, a, esp):
        try:
            return float(m.cstr(a[0]).split()[0])
        except (ValueError, IndexError):
            return 0.0

    def purecall(m, a, esp):
        raise Stop("_purecall")

    def throw(m, a, esp):
        raise Stop("C++ exception thrown (_CxxThrowException)")

    def tls_get(m, a, esp):
        return TLS_BLOCKS + 0x1000 * (a[0] % 64)

    def tls_set(m, a, esp):
        m.write(TLS_ARRAY + 4 * (a[0] % 64), struct.pack("<I", a[1]))
        return 1

    def interlocked(op):
        def f(m, a, esp):
            old = struct.unpack("<I", m.read(a[0], 4))[0]
            new, ret = op(old, a)
            m.write(a[0], struct.pack("<I", new & 0xFFFFFFFF))
            return ret & 0xFFFFFFFF
        return f

    def ret0(m, a, esp):
        return 0

    def ret1(m, a, esp):
        return 1

    def qpc(m, a, esp):
        m.write(a[0], struct.pack("<Q", 123456789))
        return 1

    def qpf(m, a, esp):
        m.write(a[0], struct.pack("<Q", 3579545))
        return 1

    cdecl = {
        "memcpy": (memcpy, 3), "memmove": (memcpy, 3), "memset": (memset, 3), "memcmp": (memcmp, 3),
        "memchr": (memchr, 3), "strlen": (strlen, 1), "strcmp": (strcmp, 2), "strncmp": (strncmp, 3),
        "_stricmp": (stricmp, 2), "_strnicmp": (strnicmp, 3), "_wcsicmp": (wcsicmp, 2),
        "_wcsnicmp": (wcsnicmp, 3), "wcsncmp": (wcsncmp, 3), "strchr": (strchr, 2), "strrchr": (strrchr, 2),
        "strstr": (strstr, 2), "wcschr": (wcschr, 2), "wcsrchr": (wcsrchr, 2), "wcsstr": (wcsstr, 2),
        "strncpy": (strncpy, 3), "wcsncpy": (wcsncpy, 3),
        "tolower": (lambda m, a, e: a[0] + 32 if 65 <= a[0] <= 90 else a[0], 1),
        "toupper": (lambda m, a, e: a[0] - 32 if 97 <= a[0] <= 122 else a[0], 1),
        "towlower": (lambda m, a, e: (a[0] & 0xFFFF) + 32 if 65 <= (a[0] & 0xFFFF) <= 90 else a[0] & 0xFFFF, 1),
        "towupper": (lambda m, a, e: (a[0] & 0xFFFF) - 32 if 97 <= (a[0] & 0xFFFF) <= 122 else a[0] & 0xFFFF, 1),
        "isalpha": (ctype(str.isalpha), 1), "isdigit": (ctype(str.isdigit), 1), "isspace": (ctype(str.isspace), 1),
        "isalnum": (ctype(str.isalnum), 1), "isupper": (ctype(str.isupper), 1),
        "isxdigit": (ctype(lambda c: c in "0123456789abcdefABCDEF"), 1), "isprint": (ctype(str.isprintable), 1),
        "malloc": (malloc, 1), "free": (free, 1), "realloc": (realloc, 2),
        "_aligned_malloc": (aligned_malloc, 2), "_aligned_free": (free, 1), "_aligned_realloc": (aligned_realloc, 3),
        "rand": (rand, 0), "srand": (srand, 1), "_errno": (errno, 0), "atoi": (atoi, 1), "atol": (atoi, 1),
        "_isnan": (isnan, 2), "_finite": (finite, 2), "_purecall": (purecall, 0),
        "_CxxThrowException": (throw, 2),
    }
    for name, (fn, n) in cdecl.items():
        m.handle(name, fn, nargs=n)
    for name, (fn, n) in {"floor": (floor, 2), "ceil": (ceil, 2), "ldexp": (ldexp, 3), "modf": (modf, 3),
                          "atof": (atof, 1)}.items():
        m.handle(name, fn, nargs=n, fresult=True)
    stdcall = {
        "TlsGetValue": (tls_get, 1), "TlsSetValue": (tls_set, 2), "GetTickCount": (lambda m, a, e: 100000, 0),
        "timeGetTime": (lambda m, a, e: 100000, 0),
        "QueryPerformanceCounter": (qpc, 1), "QueryPerformanceFrequency": (qpf, 1),
        "GetCurrentThreadId": (lambda m, a, e: 0x1234, 0), "GetCurrentProcessId": (lambda m, a, e: 0x4321, 0),
        "InterlockedIncrement": (interlocked(lambda o, a: (o + 1, o + 1)), 1),
        "InterlockedDecrement": (interlocked(lambda o, a: (o - 1, o - 1)), 1),
        "InterlockedExchange": (interlocked(lambda o, a: (a[1], o)), 2),
        "InterlockedExchangeAdd": (interlocked(lambda o, a: (o + a[1], o)), 2),
        "InterlockedCompareExchange": (interlocked(lambda o, a: ((a[1] if (o & 0xFFFFFFFF) == a[2] else o), o)), 3),
        "EnterCriticalSection": (ret0, 1), "LeaveCriticalSection": (ret0, 1),
        "TryEnterCriticalSection": (ret1, 1), "InitializeCriticalSection": (ret0, 1),
        "DeleteCriticalSection": (ret0, 1), "Sleep": (ret0, 1), "OutputDebugStringA": (ret0, 1),
        "OutputDebugStringW": (ret0, 1), "GetLastError": (ret0, 0), "SetLastError": (ret0, 1),
    }
    for name, (fn, n) in stdcall.items():
        m.handle(name, fn, nargs=n, pops=n)
    # x87 helpers: argument(s) and result on the FPU stack, run as native code
    native = {
        "_CIsqrt": b"\xd9\xfa\xc3",
        "_CIsin": b"\xd9\xfe\xc3",
        "_CIcos": b"\xd9\xff\xc3",
        "_CIlog": b"\xd9\xed\xd9\xc9\xd9\xf1\xc3",
        "_CIfmod": b"\xd9\xc9\xd9\xf8\xdf\xe0\x9e\x7a\xf9\xdd\xd9\xc3",
        "_CIpow": b"\xd9\xc9\xd9\xf1\xd9\xc0\xd9\xfc\xdc\xe9\xd9\xc9\xd9\xf0\xd9\xe8\xde\xc1\xd9\xfd\xdd\xd9\xc3",
        "_CIasin": b"\xd9\xc0\xd8\xc8\xd9\xe8\xde\xe1\xd9\xfa\xd9\xf3\xc3",
        "_CIacos": b"\xd9\xc0\xd8\xc8\xd9\xe8\xde\xe1\xd9\xfa\xd9\xc9\xd9\xf3\xc3",
    }
    for name, code in native.items():
        m.handle(name, None, code=code)
