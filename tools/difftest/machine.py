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
import ctypes, math, os, re, struct

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
MODEL_BASE, MODEL_SIZE = 0x60000000, 0x00400000   # zeroed blocks for symbols only a model can bind
MODEL_SLOT = 0x1000                               # one modelled object per page
MODEL_STUB_SLOTS = 128                            # spare import-thunk slots Machine.model_stub hands out
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
CRT_LOCKS = MISC_BASE + 0x90000          # the CRITICAL_SECTIONs _mtinitlocks hands the preallocated CRT locks

CALLEE_SAVED = (("ebx", UC_X86_REG_EBX), ("esi", UC_X86_REG_ESI), ("edi", UC_X86_REG_EDI), ("ebp", UC_X86_REG_EBP))


# Pure CRT math our object calls by name (a modelled stub) where the original runs its statically linked copy in
# the image (floor 0x536b10): the original's call is never an import, so recording ours as one made every such row
# an "import call" FAIL (world_data 0x494b60). The result is still compared through registers and memory.
UNTRACED_PURE = frozenset(("floor", "ceil", "ldexp"))

class Stop(Exception):
    pass


class Exit(Stop):
    """The program terminated: the CRT's exit/_exit/abort (the game's fatal-error path, mb_error 0x42cc80 ->
    exit(-1)) or, past them, the exit path's SetUnhandledExceptionFilter. The run ENDS there with status
    ("exit", "<name>: <detail>") -- a completed run whose memory and call traces are compared like a return's,
    not a discarded input (the frames below never return, so registers and esp are not)."""


# An import handler that runs the emulated heap out of address space (malloc/new). equiv.py needs to tell this
# apart from an input-dependent handler stop that *is* measured (a huge memcpy/memset): the run no longer has a
# comparable end state, so the input is discarded instead of compared.
HEAP_EXHAUSTED = "emulated heap exhausted"


def is_heap_exhausted(why):
    return HEAP_EXHAUSTED in str(why)


def is_huge_block(why):
    """A memcpy/memmove/memset stopped because its length (from the input) is beyond any real block."""
    return re.search(r"\bhuge mem(cpy|set|move) 0x", str(why)) is not None


def _page(n):
    return (n + 0xFFF) & ~0xFFF


FPCW = 0x007F   # x87 control word both sides run under; see _setup_cpu



def static_crt_functions(handlers):
    """[(va, handler name)] for statically linked CRT functions in the image. mountandblade-decomp (/MT) reads them
    from its CRT match list; SporeApp.exe links msvcr90 dynamically (/MD), so there are none and the static-CRT
    startup model (_init_crt_state) finds nothing to set up."""
    return []

class Machine:
    def __init__(self, image, fpcw=FPCW):
        self.img = image
        self.fpcw = fpcw
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
        # Modelled data symbols (Machine.model_data): its own region, so no hook and no diffed section
        # ever sees it -- the same exclusion imports and pool objects get.
        uc.mem_map(MODEL_BASE, MODEL_SIZE, UC_PROT_READ | UC_PROT_WRITE)
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
        self.image_extra_base = {}
        self._init_crt_state()
        # Baseline of each writable section up to its last nonzero page; pages beyond are zero
        # (mount&blade.exe: 188 KB initialized of a 144 MB .data). Read through image_base_page().
        self.image_baseline = {}
        for nm, lo, hi in self.writable:
            raw = next((s.get_data() for s in pe.sections if base + s.VirtualAddress == lo), b"")
            n = min(hi - lo, _page(len(raw.rstrip(b"\0"))))
            self.image_baseline[nm] = bytes(uc.mem_read(lo, n))
        self.misc_baseline = bytes(uc.mem_read(MISC_BASE, MISC_SIZE))
        # Dirty-page tracking for DYN and MISC: emulated writes through a hook, handler writes in
        # write(). Both sides start from the baseline (zeros / misc_baseline) on every run.
        self.dirty = set()
        self._dirty_hooks = [uc.hook_add(UC_HOOK_MEM_WRITE, self._on_tracked_write, begin=lo, end=hi - 1)
                             for lo, hi in ((DYN_BASE, DYN_BASE + DYN_SIZE), (MISC_BASE, MISC_BASE + MISC_SIZE))]
        # Same for the image's writable sections. mount&blade.exe's .data is 144 MB (mostly .bss): reading
        # and comparing whole sections after every run allocated 144 MB per run (~5 GB peak per process).
        self.img_dirty = set()
        self._dirty_hooks += [uc.hook_add(UC_HOOK_MEM_WRITE, self._on_image_write, begin=lo, end=hi - 1)
                              for _nm, lo, hi in self.writable]
        self.obj = None
        self.dyn_next = DYN_BASE
        self.dyn_sizes = {}
        self.rand_state = 1
        self.ui_seed, self.ui_calls = 0, 0
        self.find_patterns, self.find_counts = {}, {}     # FindFirstFileA search state (reset per run)
        self.trace_imports = []
        self.stop_reason = None
        self.hooks = []
        self.last_fault = None
        self.lazy = None            # callable(page) -> bytes for pool pages, set by the runner
        self.pool_pages = {}        # page -> initial bytes of every page mapped during this run
        self.pool_slots = []        # slots mapped during this run
        self.pool_entry = set()     # page of the first access to each slot (for mutation)
        self.model_next = MODEL_BASE    # bump allocator for Machine.model_data
        self.model_blocks = {}      # symbol name -> (address, size) of its zeroed block
        uc.hook_add(UC_HOOK_MEM_UNMAPPED | UC_HOOK_MEM_PROT, self._on_bad_mem)

    def _on_tracked_write(self, uc, access, address, size, value, _):
        self.dirty.add(address & ~0xFFF)
        if (address + size - 1) & ~0xFFF != address & ~0xFFF:
            self.dirty.add((address + size - 1) & ~0xFFF)

    def _on_image_write(self, uc, access, address, size, value, _):
        self.img_dirty.add(address & ~0xFFF)
        if (address + size - 1) & ~0xFFF != address & ~0xFFF:
            self.img_dirty.add((address + size - 1) & ~0xFFF)

    def image_base_page(self, nm, p):
        lo = next(l for n, l, _h in self.writable if n == nm)
        if p in self.image_extra_base:
            return self.image_extra_base[p]
        b = self.image_baseline[nm][p - lo:p - lo + 0x1000]
        return b + b"\0" * (0x1000 - len(b))

    def in_image_writable(self, a):
        return any(lo <= a < hi for _nm, lo, hi in self.writable)

    def take_image_dirty(self):
        """-> {section name: {page: bytes}} for image pages written since the last call that differ from
        the baseline (sections with no such page are absent); restores every dirty page."""
        out = {}
        for p in sorted(self.img_dirty):
            for nm, lo, hi in self.writable:
                if lo <= p < hi:
                    base = self.image_base_page(nm, p)
                    cur = bytes(self.uc.mem_read(p, len(base)))
                    if cur != base:
                        out.setdefault(nm, {})[p] = cur
                        self.uc.mem_write(p, base)
                    break
        self.img_dirty = set()
        return out

    @staticmethod
    def tracked(a):
        return DYN_BASE <= a < DYN_BASE + DYN_SIZE or MISC_BASE <= a < MISC_BASE + MISC_SIZE

    def take_dirty(self, written=None):
        """-> ({DYN page: bytes}, {MISC page: bytes}) for pages written since the last call that
        differ from the baseline; restores every dirty page. `written`, when given, collects the address
        of every written dword (the caller's per-run write set: the comparison needs to know which dwords
        of a dirty page a build actually wrote, and only an emulated store reaches this hook)."""
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
                if written is not None:
                    for k in range(0, 0x1000, 4):
                        if cur[k:k + 4] != base[k:k + 4]:
                            written.add(p + k)
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
        cw = self.cw_addr = INIT_CODE + 0x40
        # x87 control word for both sides, loaded by the session-init stub before every run. The default
        # FPCW (0x007F: 24-bit single precision, round-to-nearest, exceptions masked) is the state of the
        # thread that created the D3D device, where the game's simulation and rendering code runs
        # (docs/floating_point.md "FPU precision at runtime"); the CRT value 0x027F (53-bit) is what worker
        # threads keep. Until 2026-10-14 this was 0x027F (docs/tickets.md P3): both sides agreed with each
        # other while rounding differently from the game. Override per run with equiv.py --fpcw.
        uc.mem_write(cw, struct.pack("<HI", self.fpcw, 0x1F80))
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

    def set_fpcw(self, fpcw):
        """Change the control word the init stub loads before every run (equiv.py --fpcw)."""
        self.fpcw = fpcw & 0xFFFF
        self.uc.mem_write(self.cw_addr, struct.pack("<H", self.fpcw))

    def _init_crt_state(self):
        """The static CRT's per-process state as the game's startup (_mtinit, before main) leaves it, which
        no test runs: left as the image has it, the first CRT function that takes a lock or reads per-thread
        data (errno, locale, mbcinfo) recursed or ended the input (quest_log 0x4ee910: _lock -> _mtinitlocknum
        -> _lock(_LOCKTAB_LOCK) until the stack ran out; then _getptd -> _amsg_exit -> MessageBoxA).
        - _mtinitlocks: each preallocated lock of _locktable ({CRITICAL_SECTION*, kind} x 36, mlock.c) gets a
          critical section; the table is found through _lock's `lea esi,[eax*8+table]; cmp dword [esi],0`.
        - _mtinit's no-FLS path (kernel32 without FlsAlloc): the four gpFls* pointers are the Tls* imports,
          __tlsindex a TLS slot, and that slot's block the main thread's _tiddata (tid, _thandle -1,
          _ownlocale 1, ptmbcinfo = &__initialmbcinfo). Addresses are read from _mtinit's own stores.
        Pages of .bss this writes are kept as baseline (image_extra_base), so every run starts from them."""
        uc = self.uc
        rd = lambda a, n: bytes(uc.mem_read(a, n))
        text = next((s for s in self.img.sections if s[0] == ".text"), None)
        if text is None:
            return
        code = rd(text[1], text[2])
        touched = set()

        def put(a, v):
            uc.mem_write(a, struct.pack("<I", v & 0xFFFFFFFF))
            touched.add(a & ~0xFFF)

        k = code.find(b"\x55\x8b\xec\x8b\x45\x08\x56\x8d\x34\xc5")
        if k >= 0 and code[k + 14:k + 17] == b"\x83\x3e\x00":
            table = struct.unpack_from("<I", code, k + 10)[0]
            ents = struct.unpack("<72I", rd(table, 72 * 4))
            for i in range(36):
                if ents[2 * i] == 0 and ents[2 * i + 1] == 1:
                    put(table + 8 * i, CRT_LOCKS + 0x18 * i)
        mt = next((va for va, nm in static_crt_functions({"_mtinit": {"fn": True}})), None)
        b = rd(mt, 0xF0) if mt else b""
        want = ((0x38, b"\xa3"), (0x45, b"\xa3"), (0x52, b"\xa3"), (0x60, b"\xa3"), (0x67, b"\xa1"),
                (0x71, b"\xa1"), (0x7B, b"\xa1"), (0x80, b"\xc7\x05"), (0x9D, b"\xa3"), (0xCB, b"\xc7\x46\x54"))
        if b and all(b[o:o + len(op)] == op for o, op in want):
            u = lambda o: struct.unpack_from("<I", b, o)[0]
            fls_alloc, fls_get, fls_set, fls_free = u(0x39), u(0x46), u(0x53), u(0x61)
            put(fls_get, struct.unpack("<I", rd(u(0x68), 4))[0])      # = TlsGetValue's IAT entry
            put(fls_set, struct.unpack("<I", rd(u(0x72), 4))[0])      # TlsSetValue
            put(fls_free, struct.unpack("<I", rd(u(0x7C), 4))[0])     # TlsFree
            put(fls_alloc, u(0x86))                                    # _mtinit's TlsAlloc wrapper
            slot = 63
            put(u(0x9E), slot)                                         # __tlsindex
            ptd = TLS_BLOCKS + 0x1000 * slot
            uc.mem_write(ptd, b"\0" * 0x8C)
            uc.mem_write(ptd, struct.pack("<Ii", 0x1234, -1))         # _tid (GetCurrentThreadId), _thandle
            uc.mem_write(ptd + 0x14, struct.pack("<I", 1))            # _ownlocale
            uc.mem_write(ptd + 0x54, struct.pack("<I", u(0xCE)))      # ptmbcinfo = &__initialmbcinfo
            uc.mem_write(TLS_ARRAY + 4 * slot, struct.pack("<I", ptd))
        for p in touched:
            self.image_extra_base[p] = rd(p, 0x1000)

    # ------------------------------------------------------------------ imports
    def _install_stubs(self):
        uc = self.uc
        install_crt(self)
        install_import_models(self)
        # SporeApp.exe links the CRT dynamically (/MD): malloc, memcpy, ... are msvcr90 imports with their own
        # stubs. (mountandblade-decomp routes its static-CRT image functions to handler stubs here.)
        crt = []
        n = len(self.img.imports) + len(crt)
        # The tail of the stub table is never used by an import: Machine.model_stub hands those slots out
        # to symbols no source maps, through this same table and Python handler dispatch.
        slots = n + MODEL_STUB_SLOTS
        uc.mem_map(STUB_BASE, _page(slots * STUB_SLOT), UC_PROT_READ | UC_PROT_EXEC | UC_PROT_WRITE)
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
        for j, (va, name) in enumerate(crt):
            stub = STUB_BASE + STUB_SLOT * (len(self.img.imports) + j)
            uc.mem_write(stub, self.handlers[name]["code"].ljust(STUB_SLOT, b"\xcc"))
            uc.mem_write(va, b"\xe9" + struct.pack("<i", stub - (va + 5)))
            self.stub_names[stub] = name
        self.stub_end = STUB_BASE + STUB_SLOT * slots
        self.model_stub_next, self.model_stub_limit = n, slots
        self.model_stubs = {}       # symbol name -> stub address
        uc.hook_add(UC_HOOK_CODE, self._on_stub, begin=STUB_BASE, end=self.stub_end - 1)

    def handle(self, name, fn=None, nargs=0, pops=0, code=None, fresult=False, span=None):
        """fn(machine, args) -> eax (or float when fresult; then the stub does fld [SCRATCH]).
        `span`, when given, is the byte length of the handler's buffer argument(s): equiv.py's
        stub-scratch rule uses it to scope which addresses a do-nothing stub (fn None) can excuse."""
        if code is None:
            if fresult:
                code = b"\xdd\x05" + struct.pack("<I", SCRATCH)
            else:
                code = b""
            code += (b"\xc2" + struct.pack("<H", pops * 4)) if pops else b"\xc3"
        self.handlers[name] = {"fn": fn, "nargs": nargs, "pops": pops, "code": code, "fresult": fresult,
                               "span": span}

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
        if name not in UNTRACED_PURE:
            self.trace_imports.append((name, tuple(args)))
        if h["fn"] is None:
            return
        try:
            res = h["fn"](self, args, esp)
        except Exit as e:
            self.stop_reason = ("exit", "%s: %s" % (name, e))
            uc.emu_stop()
            return
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
        cb = getattr(self, "mark_written", None)
        if cb is not None and n:            # --uninit-mem: a handler/setup write is a write by this run
            try:
                cb(a, n, True)              # via_import: not a store the code made (see MemWrites.mark)
            except Exception:               # noqa: BLE001  bookkeeping must never break a run
                pass
        if n:
            e = a + n
            for lo, hi in self.readonly:
                if a < hi and e > lo:
                    raise UcError(UC_ERR_WRITE_PROT)
            if self.tracked(a) or self.tracked(e - 1):
                for p in range(a & ~0xFFF, e, 0x1000):
                    if self.tracked(p):
                        self.dirty.add(p)
            # the pages of [a, e) inside each writable section, by range intersection (a fill of the stack or
            # a big setup buffer spans hundreds of pages; testing each one was most of a run's write cost)
            first = a & ~0xFFF
            for _nm, lo, hi in self.writable:
                # the pages p of range(first, e, 0x1000) with lo <= p < hi
                start = first if first >= lo else first + -(-(lo - first) // 0x1000) * 0x1000
                stop = min(e, hi)
                if start < stop:
                    self.img_dirty.update(range(start, stop, 0x1000))
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
            raise Stop("%s (%d bytes)" % (HEAP_EXHAUSTED, n))
        self.dyn_next = a + n
        self.dyn_sizes[a] = n
        return a

    # ------------------------------------------------------------------ models
    # A symbol our object references but no name source identifies has no original address to bind to.
    # Narrowing the row to "unresolved reference" makes it unmeasurable, so the resolver (resolve.py) may
    # bind it to one of these two models instead. A model is evidence of testability, never of equivalence:
    # resolve.py records it in r.models and equiv.py caps such a run at WEAK and says how many there were.
    # Neither model can hide a difference the harness compares: model stubs live in the read-only stub
    # table and model data in its own untracked region, so neither shows up as written memory.
    def model_stub(self, name):
        """Address of an executable stub for an unmapped function symbol: a `call` returns 0 (xor eax,eax;
        ret) and touches nothing but the return address. Routed through the import stub table and the same
        Python handler dispatch (_on_stub), so it costs one traced import entry and nothing else.
        Idempotent per name."""
        a = self.model_stubs.get(name)
        if a is not None:
            return a
        slot = self.model_stub_next
        if slot >= self.model_stub_limit:
            raise Stop("model stub slots exhausted (%s)" % name)
        stub = STUB_BASE + STUB_SLOT * slot
        key = "model:" + name        # never collides with an import handler of the same name
        code = b"\x31\xc0\xc3"       # xor eax,eax; ret
        self.handlers[key] = {"fn": lambda m, args, esp: 0, "nargs": 0, "pops": 0, "code": code,
                              "fresult": False}
        page = stub & ~0xFFF
        self.uc.mem_protect(page, 0x1000, UC_PROT_READ | UC_PROT_WRITE | UC_PROT_EXEC)
        self.uc.mem_write(stub, code.ljust(STUB_SLOT, b"\xcc"))
        self.uc.mem_protect(page, 0x1000, UC_PROT_READ | UC_PROT_EXEC)
        self.stub_names[stub] = key
        self.model_stub_next = slot + 1
        self.model_stubs[name] = stub
        return stub

    def model_data(self, name, size):
        """Address of a zeroed, readable+writable block of at least `size` bytes for a data symbol no source
        maps. Idempotent per name for the same or a smaller size; a later, larger request gets a fresh block
        (the first address may already be reachable from the code being tested). Both sides start every run
        from zeros (see run()), and the block lies in MODEL_BASE, which no write hook or diffed region
        covers -- the exclusion imports and pool objects get."""
        n = max(int(size), 1)
        blk = self.model_blocks.get(name)
        if blk is not None and blk[1] >= n:
            return blk[0]
        span = (n + MODEL_SLOT - 1) // MODEL_SLOT * MODEL_SLOT
        a = self.model_next
        if a + span > MODEL_BASE + MODEL_SIZE:
            raise Stop("model data exhausted (%d bytes for %s)" % (span, name))
        self.model_next = a + span
        self.model_blocks[name] = (a, n)
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
        for a, n in self.model_blocks.values():     # both sides start from the same model memory
            uc.mem_write(a, b"\0" * n)
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
            if t_end is not None and _time.time() >= t_end:
                # the WALL clock stopped it, not the instruction budget: this outcome depends on machine load, so
                # the caller must not turn it into a verdict (equiv invalidates the row instead)
                return ("wall", "%ss wall-clock cap exhausted at eip=%08x" % (seconds, eip))
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

    def exit_(m, a, esp):
        code = a[0] - (1 << 32) if a[0] & 0x80000000 else a[0]
        raise Exit("code %d" % code)

    def abort(m, a, esp):
        raise Exit("abort")

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
        # msvcr80/90 pointer obfuscation: the real ones XOR with a per-process cookie; one value for both builds
        # (identity) keeps a decode of an encoded global symmetric and lets the caller go on
        "_encode_pointer": (lambda m, a, e: a[0], 1), "_decode_pointer": (lambda m, a, e: a[0], 1),
        # msvcr90's CRT locks (_lock(n) / _unlock(n)): one emulated thread, so taking a lock always succeeds at once
        "_lock": (lambda m, a, e: 0, 1), "_unlock": (lambda m, a, e: 0, 1),
        # atexit registration (a global's static initializer registers its destructor): success, the function is
        # never run at exit; both builds register through the same import, so the call trace still compares them
        "__dllonexit": (lambda m, a, e: a[0], 3), "_onexit": (lambda m, a, e: a[0], 1), "atexit": (lambda m, a, e: 0, 1),
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
        "exit": (exit_, 1), "_exit": (exit_, 1), "abort": (abort, 0),     # image CRT code (static_crt_functions)
        # _mtinitlocknum's critical section for a lock first taken at run time: initialized (TRUE), without
        # the LoadLibraryA("kernel32")/GetProcAddress lookup that otherwise ends the input at an import
        "__crtInitCritSecAndSpinCount": (lambda m, a, e: 1, 2),
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


# ---------------------------------------------------------------------- import models

def install_import_models(m):
    """Models for imports that stop the run where they are called: an unmodelled thunk ends the input, so
    a function that reaches one is never measurable (rows "only 0/N inputs valid (discards:
    import:CreateDirectoryA=400)"). Each model is what the API documents for the state the original can
    reach with a generated input -- a handle, S_OK, a zeroed allocation, the documented D3DX matrix -- and
    never a pointer the real call could not have produced. Like install_crt's handlers these change the
    emulator identically on both sides, so a row they keep alive is still re-run and compared in full;
    unlike a symbol model they are not part of equiv.py's "N modelled symbol(s)" count."""
    def fl(x):
        """A FLOAT argument: the dword on the stack reinterpreted, as the callee's own code would read it."""
        return struct.unpack("<f", struct.pack("<I", x & 0xFFFFFFFF))[0]

    def raise_exception(m_, a, esp):
        # The harness has no SEH unwinder, so a raise that reached the CRT's C++ throw (0xE06D7363) can only
        # either stop the input -- indistinguishable from the unmodelled thunk it replaces, which is what
        # left these rows untestable -- or be modelled as ignored, the documented behaviour when no handler
        # takes the exception. Ignored, execution resumes after the raise; a dead frame that faults does so
        # at the barrier (address 0 / 0xCCCCCCCC) and is discarded as a fault, never counted as valid.
        return 0

    def unhandled_filter(m_, a, esp):
        # Reached only on the CRT's exit path (0x53cd8d: the terminator doexit runs to restore the filter; the
        # startup call that installs it never runs here). The process is terminating.
        raise Exit("CRT exit path")

    def heap_alloc(m_, a, esp):
        # A block from the emulated heap, as kernel32!HeapAlloc hands one out. DYN memory is zero on a fresh
        # run and restored to zero between runs, so an overflowing size stops the run like malloc does.
        return m_.dyn_alloc(max(a[2], 1))

    def create_directory(m_, a, esp):
        # BOOL: nonzero when the directory now exists. A generated path is not a real path, so "created" is
        # the answer that lets the caller's success branch run.
        return 1

    def create_compatible_dc(m_, a, esp):
        return 0x00010001           # HDC: a handle, not an address the caller dereferences

    def create_dib_section(m_, a, esp):
        # HBITMAP, and the BITS pointer the API writes through ppvBits: a zeroed block to draw into.
        m_.write(a[3], struct.pack("<I", m_.model_data("CreateDIBSection.bits", 0x1000)))
        return 0x00020001

    def d3dx_create_texture(m_, a, esp):
        # S_OK plus a non-null texture at ppTexture: the caller checks the HRESULT and then uses *ppTexture,
        # so returning 0 alone would hand it a NULL engine object.
        m_.write(a[7], struct.pack("<I", m_.model_data("D3DXCreateTexture.texture", 0x100)))
        return 0

    def fsound_listener(m_, a, esp):
        # FSOUND_BOOL: the attributes were accepted. The call only hands the listener position/velocity
        # vectors to the sound driver, which nothing the harness compares reads back.
        return 1

    def message_box(m_, a, esp):
        # int: a modal dialog. A generated caption/text is not a real prompt, so the answer is the one
        # the original's continuation expects: the user pressed OK (IDOK). The API writes nothing.
        return 1

    def open_clipboard(m_, a, esp):
        # BOOL: the clipboard is now owned by the caller (the function it is called from only reads or
        # writes through the other clipboard APIs, which this harness never reaches).
        return 1

    def get_module_file_name(m_, a, esp):
        # DWORD: the module's path written to lpFilename. A generated buffer is not the process's real
        # one, so the documented "path truncated to nSize-1, NUL terminated" answer is written instead
        # of faulting; a buffer the emulator cannot write (generated garbage pointer) keeps the count.
        path = b"C:\\Program Files (x86)\\Steam\\steamapps\\common\\Spore\\SporeBin\\SporeApp.exe"
        n = a[2] & 0xFFFFFFFF
        if not n:
            return 0
        copy = path[:max(n - 1, 0)]
        try:
            m_.write(a[1], copy + b"\0")
        except UcError:
            pass
        return n if len(copy) < len(path) else len(path)

    def get_full_path_name(m_, a, esp):
        # DWORD GetFullPathNameA(name, nBufferLength, lpBuffer, lpFilePart): the name made absolute against a fixed
        # current directory, written NUL-terminated when it fits (returns its length), else the size needed. A name
        # the emulator cannot read is the documented failure (0).
        try:
            name = m_.cstr(a[0], limit=1024).replace(b"/", b"\\")
        except UcError:
            return 0
        full = name if (name[1:2] == b":" or name.startswith(b"\\")) else b"C:\\Spore\\" + name
        if (a[1] & 0xFFFFFFFF) <= len(full):
            return len(full) + 1
        try:
            m_.write(a[2], full + b"\0")
            if a[3]:
                m_.write(a[3], struct.pack("<I", (a[2] + full.rfind(b"\\") + 1) & 0xFFFFFFFF))
        except UcError:
            return 0
        return len(full)

    def matrix(m_, a, rows):
        m_.write(a[0], struct.pack("<16f", *rows))      # D3DXMATRIX: row-major, translation in row 4
        return a[0]                                     # pOut, as the API returns it

    def matrix_read(m_, addr):
        return struct.unpack("<16f", m_.read(addr, 64))

    def matrix_multiply(m_, a, esp):
        p, q = matrix_read(m_, a[1]), matrix_read(m_, a[2])
        return matrix(m_, a, tuple(_f32(_f32(p[i * 4] * q[j]) + _f32(p[i * 4 + 1] * q[4 + j])
                                        + _f32(p[i * 4 + 2] * q[8 + j]) + _f32(p[i * 4 + 3] * q[12 + j]))
                                 for i in range(4) for j in range(4)))

    def matrix_transpose(m_, a, esp):
        p = matrix_read(m_, a[1])
        return matrix(m_, a, tuple(p[j * 4 + i] for i in range(4) for j in range(4)))

    # ---- user32 dialog / window calls (the map editor's and the options' dialogs). No window exists in the
    # emulator, so each call gets a fixed, documented answer: a control handle is a token the game only passes back
    # to user32 (never dereferenced), queries answer "nothing selected / empty / unchecked", and the out-buffers are
    # written as the API would. Writes through a generated pointer the emulator cannot write are skipped.
    def put(m_, addr, data):
        try:
            m_.write(addr, data)
        except UcError:
            pass

    def get_dlg_item(m_, a, esp):
        # HWND of control a[1] in dialog a[0]: NULL for a NULL dialog (the API fails), else a stable token
        return 0 if not a[0] & 0xFFFFFFFF else 0x00030000 | (a[1] & 0xFFFF)

    def ui_answer(m_, choices):
        # One of `choices` for the n-th user32 query of this run, a pure function of (input seed, n): both builds
        # get the same answers as long as they ask the same questions in the same order (a reordered call is a
        # mismatch of the import trace anyway), and different inputs see different selections / checks / item
        # data, so the dialog code's branches on them are reachable.
        m_.ui_calls += 1
        h = (m_.ui_seed * 0x9E3779B1 + m_.ui_calls * 0x85EBCA77) & 0xFFFFFFFF
        h ^= h >> 16                    # murmur3 fmix32: neighbouring seeds / ordinals give unrelated answers
        h = (h * 0x85EBCA6B) & 0xFFFFFFFF
        h ^= h >> 13
        h = (h * 0xC2B2AE35) & 0xFFFFFFFF
        h ^= h >> 16
        return choices[h % len(choices)]

    UI_QUERIES = {0x146, 0x147, 0x150, 0x188, 0x18b, 0x199}   # CB_GETCOUNT/GETCURSEL/GETITEMDATA, LB_GETCURSEL/GETCOUNT/GETITEMDATA

    # messages that write into lParam: the text getters (WM_GETTEXT, CB_GETLBTEXT, LB_GETTEXT, the rich edit's
    # EM_GETSELTEXT / EM_GETTEXTRANGE) return an empty string; EM_EXGETSEL fills a CHARRANGE with an empty selection
    UI_TEXT_OUT = {0x0d, 0x148, 0x189, 0x43e, 0x44b}
    EM_EXGETSEL = 0x434

    def send_message(m_, a, esp):
        # LRESULT. Queries (the selection, a count, an item's data) and the application's own messages (>= WM_USER,
        # the editor's 0x40x list-type queries) answer -1 ("none", CB_ERR / LB_ERR) or a small number; every other
        # message (adding strings, setting the selection, WM_SETTEXT, ...) answers 0
        msg = a[1] & 0xFFFF
        if msg in UI_TEXT_OUT:
            if a[3] & 0xFFFFFFFF:
                put(m_, a[3], b"\0")
            return 0
        if msg == EM_EXGETSEL:
            if a[3] & 0xFFFFFFFF:
                put(m_, a[3], struct.pack("<2i", 0, 0))
            return 0
        if msg in UI_QUERIES or msg >= 0x400:
            return ui_answer(m_, (0xFFFFFFFF, 0, 1, 2, 3, 4, 5, 7))
        return 0

    def get_text(buf_arg):
        def f(m_, a, esp):
            # int: the control's text: empty, NUL-terminated when the buffer has room
            if a[buf_arg + 1] & 0xFFFFFFFF:
                put(m_, a[buf_arg], b"\0")
            return 0
        return f

    def get_dlg_item_int(m_, a, esp):
        # UINT: no number in an empty control: 0, *lpTranslated = FALSE
        if a[2] & 0xFFFFFFFF:
            put(m_, a[2], struct.pack("<I", 0))
        return 0

    def get_rect(m_, a, esp):
        # BOOL: an 800 x 600 window at the origin (the game's default resolution)
        put(m_, a[1], struct.pack("<4i", 0, 0, 800, 600))
        return 1

    def get_cursor_pos(m_, a, esp):
        # BOOL: the cursor at the centre of that window
        put(m_, a[0], struct.pack("<2i", 400, 300))
        return 1

    def ortho_off_center(rh):
        def f(m_, a, esp):
            l, r, b, t, zn, zf = (fl(x) for x in a[1:7])
            z = _fdiv(1.0, zn - zf) if rh else _fdiv(1.0, zf - zn)
            return matrix(m_, a, (_fdiv(2.0, r - l), 0.0, 0.0, 0.0,
                                  0.0, _fdiv(2.0, t - b), 0.0, 0.0,
                                  0.0, 0.0, z, 0.0,
                                  _fdiv(l + r, l - r), _fdiv(t + b, b - t), _fdiv(zn, zn - zf), 1.0))
        return f

    def persp_off_center(rh):
        def f(m_, a, esp):
            l, r, b, t, zn, zf = (fl(x) for x in a[1:7])
            two_zn = _f32(2.0 * zn)
            far = _fdiv(zf, zn - zf) if rh else _fdiv(zf, zf - zn)
            w = _fdiv(zn * zf, zn - zf) if rh else _fdiv(-zn * zf, zf - zn)
            return matrix(m_, a, (_fdiv(two_zn, r - l), 0.0, 0.0, 0.0,
                                  0.0, _fdiv(two_zn, t - b), 0.0, 0.0,
                                  _fdiv(l + r, l - r), _fdiv(t + b, b - t), far, -1.0 if rh else 1.0,
                                  0.0, 0.0, w, 0.0))
        return f

    stdcall = {
        "RaiseException": (raise_exception, 4),
        "SetUnhandledExceptionFilter": (unhandled_filter, 1),
        "HeapAlloc": (heap_alloc, 3),
        "CreateDirectoryA": (create_directory, 2),
        "CreateCompatibleDC": (create_compatible_dc, 1),
        "CreateDIBSection": (create_dib_section, 6),
        "D3DXCreateTexture": (d3dx_create_texture, 8),
        "D3DXMatrixMultiply": (matrix_multiply, 3),
        "D3DXMatrixTranspose": (matrix_transpose, 2),
        "D3DXMatrixOrthoOffCenterRH": (ortho_off_center(True), 7),
        "D3DXMatrixOrthoOffCenterLH": (ortho_off_center(False), 7),
        "D3DXMatrixPerspectiveOffCenterRH": (persp_off_center(True), 7),
        "D3DXMatrixPerspectiveOffCenterLH": (persp_off_center(False), 7),
        "_FSOUND_3D_Listener_SetAttributes@32": (fsound_listener, 8),
        "MessageBoxA": (message_box, 4),
        "OpenClipboard": (open_clipboard, 1),
        "GetModuleFileNameA": (get_module_file_name, 3),
        "GetFullPathNameA": (get_full_path_name, 4),
        "CloseHandle": (lambda m_, a, esp: 1, 1),                 # BOOL: closed
        "GetCurrentThread": (lambda m_, a, esp: 0xFFFFFFFE, 0),   # the documented pseudo-handle, (HANDLE)-2
        "GetThreadPriority": (lambda m_, a, esp: 0, 1),           # THREAD_PRIORITY_NORMAL
        "GetCurrentProcess": (lambda m_, a, esp: 0xFFFFFFFF, 0),  # the documented pseudo-handle, (HANDLE)-1
        "EncodePointer": (lambda m_, a, esp: a[0], 1), "DecodePointer": (lambda m_, a, esp: a[0], 1),
        "SetThreadPriority": (lambda m_, a, esp: 1, 2),           # BOOL: done
        "GetDlgItem": (get_dlg_item, 2),
        "SendMessageA": (send_message, 4),
        "GetDlgItemTextA": (get_text(2), 4),
        "GetWindowTextA": (get_text(1), 3),
        "GetDlgItemInt": (get_dlg_item_int, 4),
        "IsDlgButtonChecked": (lambda m_, a, esp: ui_answer(m_, (0, 1)), 2),   # BST_UNCHECKED / BST_CHECKED
        "SetDlgItemTextA": (lambda m_, a, esp: 1, 3),             # BOOL: done
        "SetDlgItemInt": (lambda m_, a, esp: 1, 4),
        "SetWindowTextA": (lambda m_, a, esp: 1, 2),
        "CheckRadioButton": (lambda m_, a, esp: 1, 4),
        "EnableWindow": (lambda m_, a, esp: 0, 2),                # BOOL: the window was not disabled before
        "ShowWindow": (lambda m_, a, esp: 0, 2),                  # BOOL: it was hidden before
        "UpdateWindow": (lambda m_, a, esp: 1, 1),
        "RedrawWindow": (lambda m_, a, esp: 1, 4),
        "SetWindowPos": (lambda m_, a, esp: 1, 7),
        "SetFocus": (lambda m_, a, esp: 0, 1),                    # HWND: no window had the focus
        "PostMessageA": (lambda m_, a, esp: 1, 4),
        "EndDialog": (lambda m_, a, esp: 1, 2),
        "DefWindowProcA": (lambda m_, a, esp: 0, 4),
        "GetWindowRect": (get_rect, 2),
        "GetClientRect": (get_rect, 2),
        "GetCursorPos": (get_cursor_pos, 1),
    }
    for name, (fn, n) in stdcall.items():
        m.handle(name, fn, nargs=n, pops=n)
    install_system_models(m, ui_answer, put)


# Opaque handles the models hand out: values the game only passes back to the API (never dereferenced), each kind in
# its own range so a trace shows which call produced it. Pointers the game DOES read through (an FMOD stream or
# sample, a Newton object) come from model_data instead.
H_FIND, H_FILE, H_KEY, H_MODULE, H_EVENT, H_PROCESS, H_THREAD = (0x00040001, 0x00041001, 0x00042001, 0x6F000000,
                                                                0x00043001, 0x00044001, 0x00045001)
H_GDI, H_FONT, H_PAINT_DC, H_CURSOR, H_MENU = 0x00060001, 0x00070001, 0x00010002, 0x00090001, 0x000A0001
INVALID_HANDLE = 0xFFFFFFFF
MODULE_DIR = b"C:\\Program Files\\Mount&Blade"
# SHGetFolderPathA's answers per CSIDL (low byte; CSIDL_FLAG_CREATE and friends are ORed into the high bits)
FOLDER_PATHS = {0x05: b"C:\\Documents and Settings\\User\\My Documents",        # CSIDL_PERSONAL
                0x1A: b"C:\\Documents and Settings\\User\\Application Data",    # CSIDL_APPDATA
                0x1C: b"C:\\Documents and Settings\\User\\Local Settings\\Application Data",
                0x23: b"C:\\Documents and Settings\\All Users\\Application Data",
                0x26: b"C:\\Program Files"}


def install_system_models(m, ui_answer, put):
    """kernel32 / shell / registry / GDI / FMOD / Newton imports the game's own code calls. As with the dialog
    models above, every answer to a query or to a call that can fail -- a file found or not, a folder lookup,
    a sound channel, a physics body's matrix, the installed memory -- is ui_answer(): a pure function of
    (input seed, call ordinal), identical for both builds as long as they make the same calls in the same
    order, and different across inputs so the branches on it are explored. Out-parameters are written the way
    the API documents (skipped when the generated pointer is not writable)."""
    def fl(x):
        return struct.unpack("<f", struct.pack("<I", x & 0xFFFFFFFF))[0]

    def cstr(m_, p, limit=0x400):
        try:
            return m_.cstr(p, limit=limit) if p & 0xFFFFFFFF else b""
        except UcError:
            return b""

    # ---- shfolder
    def sh_get_folder_path(m_, a, esp):
        # HRESULT. S_OK with the folder's path in pszPath (MAX_PATH chars), or E_FAIL; a failed call leaves an
        # empty string (callers test path[0])
        csidl = a[1] & 0xFF
        if ui_answer(m_, (0, 0, 0, 0x80004005)):
            put(m_, a[4], b"\0")
            return 0x80004005
        put(m_, a[4], FOLDER_PATHS.get(csidl, b"C:\\Documents and Settings\\User") + b"\0")
        return 0

    # ---- kernel32: find, files, handles
    def find_name(pattern, k):
        base = re.split(rb"[\\/]", pattern)[-1] or b"a"
        nm = base.replace(b"*", b"a%d" % k if k else b"a").replace(b"?", b"a")
        return nm[:259]

    def fill_find_data(m_, p, name):
        # WIN32_FIND_DATAA (320 bytes): attributes, three FILETIMEs, size high/low, reserved, cFileName[260],
        # cAlternateFileName[14]. A name without an extension is a directory, anything else a 1 KB archive file.
        attr = 0x20 if b"." in name.strip(b".") else 0x10
        ft = struct.pack("<II", 0xD53E8000, 0x01C8D2A4)                     # 2008-06-01 00:00 UTC
        rec = struct.pack("<I", attr) + ft * 3 + struct.pack("<IIII", 0, 0 if attr == 0x10 else 1024, 0, 0)
        rec += name.ljust(260, b"\0")[:260] + b"\0" * 16
        put(m_, p, rec)

    def find_first_file(m_, a, esp):
        # HANDLE: a search handle and the first match in *lpFindFileData, or INVALID_HANDLE_VALUE (no match)
        if not ui_answer(m_, (0, 1)):
            return INVALID_HANDLE
        pat = cstr(m_, a[0])
        m_.find_patterns[H_FIND] = pat
        fill_find_data(m_, a[1], find_name(pat, 0))
        return H_FIND

    def find_next_file(m_, a, esp):
        # BOOL: the next match, or FALSE (ERROR_NO_MORE_FILES). Each call ends the listing with probability 2/3,
        # so a directory loop terminates.
        if not ui_answer(m_, (0, 0, 1)):
            return 0
        n = m_.find_counts.get(a[0], 0) + 1
        m_.find_counts[a[0]] = n
        fill_find_data(m_, a[1], find_name(m_.find_patterns.get(a[0], b"*.txt"), n))
        return 1

    def create_file(m_, a, esp):
        # HANDLE or INVALID_HANDLE_VALUE (not found / no access)
        return ui_answer(m_, (INVALID_HANDLE, H_FILE))

    def write_file(m_, a, esp):
        # BOOL: everything written; *lpNumberOfBytesWritten = nNumberOfBytesToWrite
        if a[3] & 0xFFFFFFFF:
            put(m_, a[3], struct.pack("<I", a[2]))
        return 1

    def read_file(m_, a, esp):
        # BOOL TRUE with *lpNumberOfBytesRead = 0: end of file (an opened file is empty; no content exists to read)
        if a[3] & 0xFFFFFFFF:
            put(m_, a[3], struct.pack("<I", 0))
        return 1

    def file_time_to_local(m_, a, esp):
        # BOOL; the machine's time zone is UTC, so the local time is the same FILETIME
        put(m_, a[1], m_.read(a[0], 8))
        return 1

    def file_time_to_system(m_, a, esp):
        # BOOL; SYSTEMTIME {year, month, weekday, day, hour, minute, second, ms} of the FILETIME (UTC)
        import datetime
        ft = struct.unpack("<Q", m_.read(a[0], 8))[0]
        if ft >= 0x8000000000000000:
            return 0
        t = datetime.datetime(1601, 1, 1) + datetime.timedelta(microseconds=ft // 10)
        put(m_, a[1], struct.pack("<8H", t.year, t.month, (t.weekday() + 1) % 7, t.day, t.hour, t.minute,
                                  t.second, t.microsecond // 1000))
        return 1

    def global_memory_status(m_, a, esp):
        # void: MEMORYSTATUS (32 bytes). The installed RAM is a query answer: 256 MB .. 2 GB, half of it free
        total = ui_answer(m_, (256, 512, 1024, 2047)) << 20
        put(m_, a[0], struct.pack("<8I", 32, 50, total, total // 2, 2 * total, total, 0x7FFE0000, 0x7F000000))
        return 0

    def get_current_directory(m_, a, esp):
        # DWORD: chars written without the NUL, or the size needed when the buffer is too small
        n = a[0] & 0xFFFFFFFF
        if n <= len(MODULE_DIR):
            return len(MODULE_DIR) + 1
        put(m_, a[1], MODULE_DIR + b"\0")
        return len(MODULE_DIR)

    def heap_size(m_, a, esp):
        return m_.dyn_sizes.get(a[2], 0xFFFFFFFF)       # SIZE_T, (SIZE_T)-1 for a block the heap did not hand out

    def heap_realloc(m_, a, esp):
        p, n = a[2], max(a[3], 1)
        q = m_.dyn_alloc(n)
        if p:
            m_.write(q, m_.read(p, min(m_.dyn_sizes.get(p, 0), n)))
        return q

    def global_alloc(m_, a, esp):
        # HGLOBAL; the block itself (GlobalLock returns it unchanged), zeroed as GMEM_ZEROINIT would
        return m_.dyn_alloc(max(a[1], 1))

    def create_process(m_, a, esp):
        # BOOL; on success PROCESS_INFORMATION {hProcess, hThread, pid, tid} at lpProcessInformation (arg 10)
        if not ui_answer(m_, (0, 1)):
            return 0
        put(m_, a[9], struct.pack("<4I", H_PROCESS, H_THREAD, 0x5678, 0x9ABC))
        return 1

    def process_affinity(m_, a, esp):
        put(m_, a[1], struct.pack("<I", 1))
        put(m_, a[2], struct.pack("<I", 1))
        return 1

    def mul_div(m_, a, esp):
        # int: a*b/c rounded to nearest (halves away from zero), -1 on c == 0 or overflow
        s = lambda v: v - (1 << 32) if v & 0x80000000 else v
        x, y, z = s(a[0]), s(a[1]), s(a[2])
        if z == 0:
            return 0xFFFFFFFF
        p = x * y
        q = (abs(p) + abs(z) // 2) // abs(z)
        q = q if (p >= 0) == (z > 0) else -q
        return 0xFFFFFFFF if not -(1 << 31) <= q < (1 << 31) else q & 0xFFFFFFFF

    def lstrcpy(m_, a, esp):
        m_.write(a[0], m_.cstr(a[1]) + b"\0")
        return a[0]

    def lstrcpyn(m_, a, esp):
        n = a[2] & 0xFFFFFFFF
        if n:
            m_.write(a[0], m_.cstr(a[1])[:n - 1] + b"\0")
        return a[0]

    def lstrcat(m_, a, esp):
        d = m_.cstr(a[0])
        m_.write(a[0] + len(d), m_.cstr(a[1]) + b"\0")
        return a[0]

    def lstrcmp(m_, a, esp):
        x, y = m_.cstr(a[0]), m_.cstr(a[1])
        return 0 if x == y else (0xFFFFFFFF if x < y else 1)

    # ---- advapi32
    def reg_create_key(m_, a, esp):
        # LONG ERROR_SUCCESS; *phkResult = a key handle, *lpdwDisposition = REG_CREATED_NEW_KEY (1) or
        # REG_OPENED_EXISTING_KEY (2) -- the query the game branches on (it logs a newly created key)
        put(m_, a[7], struct.pack("<I", H_KEY))
        if a[8] & 0xFFFFFFFF:
            put(m_, a[8], struct.pack("<I", ui_answer(m_, (1, 2))))
        return 0

    def reg_query_value(m_, a, esp):
        # LONG: ERROR_FILE_NOT_FOUND (no such value) or ERROR_SUCCESS with the value: a REG_DWORD 0/1 when the
        # caller's buffer is 4 bytes, else an empty REG_SZ; a too-small buffer gets ERROR_MORE_DATA
        if not ui_answer(m_, (0, 1)):
            return 2
        cb = struct.unpack("<I", m_.read(a[5], 4))[0] if a[5] & 0xFFFFFFFF else 0
        if cb == 4:
            typ, data = 4, struct.pack("<I", ui_answer(m_, (0, 1)))
        else:
            typ, data = 1, b"\0"
        if a[3] & 0xFFFFFFFF:
            put(m_, a[3], struct.pack("<I", typ))
        if a[5] & 0xFFFFFFFF:
            put(m_, a[5], struct.pack("<I", len(data)))
        if a[4] & 0xFFFFFFFF:
            if cb < len(data):
                return 234
            put(m_, a[4], data)
        return 0

    # ---- user32 / gdi32 (painting, metrics)
    def begin_paint(m_, a, esp):
        # HDC; PAINTSTRUCT {hdc, fErase, rcPaint = the 800 x 600 client area, ...} at lpPaint
        put(m_, a[1], struct.pack("<II4i", H_PAINT_DC, 0, 0, 0, 800, 600) + b"\0" * 40)
        return H_PAINT_DC

    DEVICE_CAPS = {8: 800, 10: 600, 12: 32, 14: 1, 88: 96, 90: 96}   # HORZRES VERTRES BITSPIXEL PLANES LOGPIXELSX/Y

    def text_extent(m_, a, esp):
        # BOOL; SIZE {8 px per char, 16 px}: a fixed-pitch stand-in for the selected font
        put(m_, a[3], struct.pack("<2i", 8 * (a[2] & 0xFFFF), 16))
        return 1

    def get_object(m_, a, esp):
        # int bytes written: a 64 x 64 32-bpp BITMAP (the only object type the game asks about)
        n = a[1] & 0xFFFFFFFF
        bm = struct.pack("<iiiiHHI", 0, 64, 64, 256, 1, 32, 0)
        if a[2] & 0xFFFFFFFF and n:
            put(m_, a[2], (bm + b"\0" * n)[:min(n, 24)])
            return min(n, 24)
        return 24

    SYS_METRICS = {0: 1024, 1: 768, 4: 19, 5: 1, 6: 1, 7: 3, 8: 3, 15: 19, 32: 4, 33: 4}

    def window_long(m_, a, esp):
        idx = a[1] - (1 << 32) if a[1] & 0x80000000 else a[1]
        return {-16: 0x16CF0000, -20: 0x00000100}.get(idx, 0)  # GWL_STYLE (overlapped, visible), GWL_EXSTYLE

    def set_rect(m_, a, esp):
        put(m_, a[0], struct.pack("<4I", a[1], a[2], a[3], a[4]))
        return 1

    def variant_init(m_, a, esp):
        put(m_, a[0], b"\0" * 16)
        return 0

    def co_create_instance(m_, a, esp):
        # HRESULT REGDB_E_CLASSNOTREG, *ppv = NULL: no COM server exists in the emulator (a fake object would
        # need a vtable the harness cannot know); the failure branch is the one a real machine without it takes
        put(m_, a[4], struct.pack("<I", 0))
        return 0x80040154

    stdcall = {
        "SHGetFolderPathA": (sh_get_folder_path, 5),
        "FindFirstFileA": (find_first_file, 2),
        "FindNextFileA": (find_next_file, 2),
        "FindClose": (lambda m_, a, esp: 1, 1),
        "CreateFileA": (create_file, 7),
        "WriteFile": (write_file, 5),
        "SetFilePointer": (lambda m_, a, esp: 0, 4),
        "ReadFile": (read_file, 5),
        "GetFileType": (lambda m_, a, esp: 1, 1),                 # FILE_TYPE_DISK
        "SetEndOfFile": (lambda m_, a, esp: 1, 1),
        "FileTimeToLocalFileTime": (file_time_to_local, 2),
        "FileTimeToSystemTime": (file_time_to_system, 2),
        "LoadImageA": (lambda m_, a, esp: ui_answer(m_, (0, H_GDI + 0x200)), 6),   # HANDLE, NULL = not found
        "FlushFileBuffers": (lambda m_, a, esp: 1, 1),
        "CloseHandle": (lambda m_, a, esp: 1, 1),
        "DeleteFileA": (lambda m_, a, esp: 1, 1),
        "MoveFileA": (lambda m_, a, esp: 1, 2),
        "GetDriveTypeA": (lambda m_, a, esp: 3, 1),               # DRIVE_FIXED
        "GetCurrentDirectoryA": (get_current_directory, 2),
        "GlobalMemoryStatus": (global_memory_status, 1),
        "LoadLibraryA": (lambda m_, a, esp: H_MODULE, 1),         # HMODULE (the game ignores it)
        "GetModuleHandleA": (lambda m_, a, esp: m_.img.base if not a[0] & 0xFFFFFFFF else H_MODULE, 1),
        "GetProcAddress": (lambda m_, a, esp: 0, 2),              # FARPROC NULL: no such export (never callable)
        "WaitForSingleObject": (lambda m_, a, esp: 0, 2),         # WAIT_OBJECT_0
        "CreateEventA": (lambda m_, a, esp: H_EVENT, 4),
        "SetEvent": (lambda m_, a, esp: 1, 1),
        "CreateProcessA": (create_process, 10),
        "GetCurrentProcess": (lambda m_, a, esp: 0xFFFFFFFF, 0),  # the pseudo handle
        "GetProcessAffinityMask": (process_affinity, 3),
        "HeapSize": (heap_size, 3),
        "HeapFree": (lambda m_, a, esp: 1, 3),
        "HeapReAlloc": (heap_realloc, 4),
        "GlobalAlloc": (global_alloc, 2),
        "GlobalLock": (lambda m_, a, esp: a[0], 1),
        "GlobalUnlock": (lambda m_, a, esp: 0, 1),
        "MulDiv": (mul_div, 3),
        "lstrcpyA": (lstrcpy, 2),
        "lstrcpynA": (lstrcpyn, 3),
        "lstrcatA": (lstrcat, 2),
        "lstrlenA": (lambda m_, a, esp: len(m_.cstr(a[0])) if a[0] & 0xFFFFFFFF else 0, 1),
        "lstrcmpA": (lstrcmp, 2),
        "RegCreateKeyExA": (reg_create_key, 9),
        "RegCloseKey": (lambda m_, a, esp: 0, 1),
        "RegSetValueExA": (lambda m_, a, esp: 0, 6),
        "RegQueryValueExA": (reg_query_value, 6),
        "ShellExecuteA": (lambda m_, a, esp: 42, 6),              # HINSTANCE > 32: started
        "VariantInit": (variant_init, 1),
        "VariantClear": (variant_init, 1),                        # HRESULT S_OK, the VARIANT now VT_EMPTY
        "CoInitialize": (lambda m_, a, esp: 0, 1),
        "CoCreateInstance": (co_create_instance, 5),
        "BeginPaint": (begin_paint, 2),
        "EndPaint": (lambda m_, a, esp: 1, 2),
        "GetClassLongA": (lambda m_, a, esp: H_CURSOR, 2),
        "GetSystemMetrics": (lambda m_, a, esp: SYS_METRICS.get(a[0], 0), 1),
        "GetWindowLongA": (window_long, 2),
        "SetWindowLongA": (lambda m_, a, esp: 0, 3),              # LONG: the previous value
        "GetMenu": (lambda m_, a, esp: H_MENU, 1),
        "SetMenu": (lambda m_, a, esp: 1, 2),
        "DestroyMenu": (lambda m_, a, esp: 1, 1),
        "SetRect": (set_rect, 5),
        "AdjustWindowRect": (lambda m_, a, esp: 1, 3),            # BOOL: the rect left as is (no frame)
        "ScreenToClient": (lambda m_, a, esp: 1, 2),              # BOOL: the window sits at the origin
        "ClipCursor": (lambda m_, a, esp: 1, 1),
        "SetCursorPos": (lambda m_, a, esp: 1, 2),
        "SetCursor": (lambda m_, a, esp: 0, 1),
        "LoadCursorA": (lambda m_, a, esp: H_CURSOR, 2),
        "LoadIconA": (lambda m_, a, esp: H_CURSOR + 1, 2),
        "IsClipboardFormatAvailable": (lambda m_, a, esp: ui_answer(m_, (0, 1)), 1),
        "GetClipboardData": (lambda m_, a, esp: 0, 1),            # HANDLE NULL: no data in that format
        "CloseClipboard": (lambda m_, a, esp: 1, 0),
        "EmptyClipboard": (lambda m_, a, esp: 1, 0),
        "SetClipboardData": (lambda m_, a, esp: a[1], 2),
        "SetMapMode": (lambda m_, a, esp: 1, 2),                  # int: the previous mode, MM_TEXT
        "SelectObject": (lambda m_, a, esp: H_GDI, 2),            # HGDIOBJ: the previously selected object
        "DeleteObject": (lambda m_, a, esp: 1, 1),
        "DeleteDC": (lambda m_, a, esp: 1, 1),
        "GetStockObject": (lambda m_, a, esp: H_GDI + 0x100 + (a[0] & 0xFF), 1),
        "BitBlt": (lambda m_, a, esp: 1, 9),
        "SetTextColor": (lambda m_, a, esp: 0, 2),                # COLORREF: the previous colour (black)
        "SetBkColor": (lambda m_, a, esp: 0xFFFFFF, 2),           # (white)
        "SetTextAlign": (lambda m_, a, esp: 0, 2),                # UINT: TA_TOP | TA_LEFT before
        "GetDeviceCaps": (lambda m_, a, esp: DEVICE_CAPS.get(a[1], 0), 2),
        "CreateFontA": (lambda m_, a, esp: ui_answer(m_, (H_FONT, H_FONT, H_FONT, 0)), 14),
        "GetTextExtentPoint32A": (text_extent, 4),
        "ExtTextOutA": (lambda m_, a, esp: 1, 8),
        "GetObjectA": (get_object, 3),
    }
    for name, (fn, n) in stdcall.items():
        m.handle(name, fn, nargs=n, pops=n)

    # ---- FMOD 3.x (fmod.dll, __stdcall: the decorated @N is the argument bytes). FSOUND_BOOL is a signed char.
    # Creating a sample/stream and starting a channel can fail (NULL / -1) and the lengths / states are queries,
    # so those are ui_answer; samples and streams are zeroed model blocks (the game passes them back to FMOD).
    def fs_sample_load(m_, a, esp):
        return ui_answer(m_, (0, m_.model_data("FSOUND_SAMPLE", 0x100), m_.model_data("FSOUND_SAMPLE", 0x100)))

    def fs_stream_open(m_, a, esp):
        return ui_answer(m_, (0, m_.model_data("FSOUND_STREAM", 0x100), m_.model_data("FSOUND_STREAM", 0x100)))

    def fs_sample_get_defaults(m_, a, esp):
        for p, v in zip(a[1:5], (44100, 255, 128, 128)):          # deffreq, defvol, defpan, defpri
            if p & 0xFFFFFFFF:
                put(m_, p, struct.pack("<i", v))
        return 1

    fsound = {
        "Update": (lambda m_, a, esp: 0), "Close": (lambda m_, a, esp: 0),
        "Init": (lambda m_, a, esp: 1), "SetMaxHardwareChannels": (lambda m_, a, esp: 1),
        "SetSFXMasterVolume": (lambda m_, a, esp: 0), "3D_SetRolloffFactor": (lambda m_, a, esp: 0),
        "Sample_Load": fs_sample_load, "Sample_SetDefaults": (lambda m_, a, esp: 1),
        "Sample_GetLength": (lambda m_, a, esp: ui_answer(m_, (0, 22050, 44100, 441000))),
        "Sample_GetDefaults": fs_sample_get_defaults,
        "Stream_Open": fs_stream_open, "Stream_Close": (lambda m_, a, esp: 1),
        # 0 ready, -2 still opening, -3 failed to open
        "Stream_GetOpenState": (lambda m_, a, esp: ui_answer(m_, (0, 0, 0xFFFFFFFE, 0xFFFFFFFD))),
        "Stream_Play": (lambda m_, a, esp: ui_answer(m_, (0xFFFFFFFF, 0, 1, 7))),
        "Stream_GetLengthMs": (lambda m_, a, esp: ui_answer(m_, (0, 1000, 30000, 180000))),
        "Stream_GetTime": (lambda m_, a, esp: ui_answer(m_, (0, 500, 29000, 179999))),
        "PlaySoundEx": (lambda m_, a, esp: ui_answer(m_, (0xFFFFFFFF, 0, 3, 7))),     # channel, -1 = none free
        "3D_SetAttributes": (lambda m_, a, esp: 1), "SetVolume": (lambda m_, a, esp: 1),
        "SetLoopMode": (lambda m_, a, esp: 1), "SetCurrentPosition": (lambda m_, a, esp: 1),
        "SetFrequency": (lambda m_, a, esp: 1), "SetPriority": (lambda m_, a, esp: 1),
        "SetPaused": (lambda m_, a, esp: 1), "StopSound": (lambda m_, a, esp: 1),
    }
    for full in set(nm.split("!", 1)[1] for nm in m.img.imports.values()):
        mt = re.match(r"_FSOUND_(\w+)@(\d+)$", full)
        if mt and mt.group(1) in fsound and full not in m.handlers:
            n = int(mt.group(2)) // 4
            m.handle(full, fsound[mt.group(1)], nargs=n, pops=n)

    # ---- Newton Game Dynamics 1.5 (newton.dll, __cdecl). Worlds, bodies, collisions and rag dolls are zeroed
    # model blocks; the getters fill their out-arrays. A body's matrix is a rotation-free transform whose
    # translation is a query answer per call, so code comparing two bodies' positions sees both orders.
    def nw(kind):
        return lambda m_, a, esp: m_.model_data("Newton" + kind, 0x100)

    COORDS = (0.0, 1.0, -1.0, 2.5)

    def nw_matrix(m_, a, esp):
        t = [ui_answer(m_, COORDS) for _ in range(3)]
        put(m_, a[1], struct.pack("<16f", 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, t[0], t[1], t[2], 1))
        return 0

    def nw_vec3(m_, a, esp):
        put(m_, a[1], struct.pack("<3f", *(ui_answer(m_, COORDS) for _ in range(3))))
        return 0

    def nw_mass(m_, a, esp):
        for p, v in zip(a[1:5], (ui_answer(m_, (0.0, 1.0, 80.0)), 1.0, 1.0, 1.0)):   # mass 0 = static body
            if p & 0xFFFFFFFF:
                put(m_, p, struct.pack("<f", v))
        return 0

    def nw_inertia(m_, a, esp):
        put(m_, a[1], struct.pack("<3f", 1.0, 1.0, 1.0))
        put(m_, a[2], struct.pack("<3f", 0.0, 0.0, 0.0))
        return 0

    void0 = lambda m_, a, esp: 0
    newton = {
        "NewtonCreate": (nw("World"), 2), "NewtonDestroy": (void0, 1), "NewtonUpdate": (void0, 2),
        "NewtonSetSolverModel": (void0, 2), "NewtonSetWorldSize": (void0, 3),
        "NewtonMaterialGetDefaultGroupID": (void0, 1), "NewtonMaterialSetDefaultSoftness": (void0, 4),
        "NewtonMaterialSetDefaultElasticity": (void0, 4), "NewtonMaterialSetDefaultFriction": (void0, 5),
        "NewtonCreateBody": (nw("Body"), 2), "NewtonDestroyBody": (void0, 2),
        "NewtonCreateTreeCollision": (nw("Collision"), 2), "NewtonCreateCapsule": (nw("Collision"), 4),
        "NewtonTreeCollisionBeginBuild": (void0, 1), "NewtonTreeCollisionAddFace": (void0, 5),
        "NewtonTreeCollisionEndBuild": (void0, 2), "NewtonReleaseCollision": (void0, 2),
        "NewtonConvexCollisionCalculateInertialMatrix": (nw_inertia, 3),
        "NewtonBodyGetMatrix": (nw_matrix, 2), "NewtonBodySetMatrix": (void0, 2),
        "NewtonBodyGetVelocity": (nw_vec3, 2), "NewtonBodySetVelocity": (void0, 2),
        "NewtonBodyGetOmega": (nw_vec3, 2), "NewtonBodySetOmega": (void0, 2),
        "NewtonBodyGetMassMatrix": (nw_mass, 5), "NewtonBodySetMassMatrix": (void0, 5),
        "NewtonBodySetCentreOfMass": (void0, 2), "NewtonBodySetMaterialGroupID": (void0, 2),
        "NewtonBodySetAngularDamping": (void0, 2), "NewtonBodySetFreezeTreshold": (void0, 4),
        "NewtonBodyGetSleepingState": (lambda m_, a, esp: ui_answer(m_, (0, 1)), 1),
        "NewtonBodyAddForce": (void0, 2), "NewtonBodyAddTorque": (void0, 2),
        "NewtonCreateRagDoll": (nw("RagDoll"), 1), "NewtonRagDollBegin": (void0, 1), "NewtonRagDollEnd": (void0, 1),
        "NewtonRagDollAddBone": (nw("RagDollBone"), 7), "NewtonRagDollBoneSetLimits": (void0, 8),
        "NewtonRagDollBoneGetBody": (nw("Body"), 1), "NewtonRagDollBoneGetGlobalMatrix": (nw_matrix, 2),
        "NewtonRagDollSetForceAndTorqueCallback": (void0, 2),
    }
    for name, (fn, n) in newton.items():
        m.handle(name, fn, nargs=n)


def _f32(x):
    """x rounded to single precision, the width the original's D3DX call computes in."""
    try:
        return struct.unpack("<f", struct.pack("<f", x))[0]
    except OverflowError:
        return math.copysign(math.inf, x)


def _fdiv(a, b):
    """IEEE division: a degenerate projection (l == r, zn == zf) yields inf/NaN like the real call, where
    Python would raise ZeroDivisionError."""
    if b:
        return _f32(a / b)
    if a == 0.0 or a != a:
        return float("nan")
    return math.copysign(float("inf"), a) * math.copysign(1.0, b)
