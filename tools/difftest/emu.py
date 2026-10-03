"""Run original SporeApp.exe functions under Unicorn for differential testing.

Maps the (non-runnable) analysis image at its preferred base, points every IAT
slot at a stub that dispatches to a Python implementation, and calls functions
by address with cdecl / stdcall / thiscall conventions.

Only the handful of imports a tested function actually reaches need a handler;
an unhandled import raises so a test can never silently pass through one.
"""
import struct
import pefile
from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_PROT_ALL
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX,
                               UC_X86_REG_ESP, UC_X86_REG_EIP)

STUB_BASE = 0x7F000000   # one 16-byte slot per import
STACK_TOP = 0x7E000000
STACK_SIZE = 0x100000
HEAP_BASE = 0x60000000
HEAP_SIZE = 0x10000000
RETURN_SENTINEL = 0x7EFFF000


class Emulator:
    def __init__(self, image_path):
        self.pe = pefile.PE(image_path)
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.uc = Uc(UC_ARCH_X86, UC_MODE_32)
        size = (self.pe.OPTIONAL_HEADER.SizeOfImage + 0xFFF) & ~0xFFF
        self.uc.mem_map(self.base, size, UC_PROT_ALL)
        self.uc.mem_write(self.base, self.pe.header[:0x1000])
        for s in self.pe.sections:
            data = s.get_data()[: max(s.Misc_VirtualSize, 0) or len(s.get_data())]
            self.uc.mem_write(self.base + s.VirtualAddress, data)
        self.uc.mem_map(STACK_TOP - STACK_SIZE, STACK_SIZE + 0x1000, UC_PROT_ALL)
        self.uc.mem_map(HEAP_BASE, HEAP_SIZE, UC_PROT_ALL)
        self.uc.mem_map(RETURN_SENTINEL & ~0xFFF, 0x1000, UC_PROT_ALL)
        self.heap_next = HEAP_BASE
        self.handlers = {}
        self.stub_names = {}
        self._patch_iat()
        self.uc.hook_add(UC_HOOK_CODE, self._on_stub, begin=STUB_BASE, end=STUB_BASE + 0xFFFFF)

    # ---- imports ----
    def _patch_iat(self):
        n_imports = sum(len(e.imports) for e in self.pe.DIRECTORY_ENTRY_IMPORT)
        self.uc.mem_map(STUB_BASE, (n_imports * 16 + 0xFFF) & ~0xFFF, UC_PROT_ALL)
        i = 0
        for entry in self.pe.DIRECTORY_ENTRY_IMPORT:
            dll = entry.dll.decode().lower()
            for imp in entry.imports:
                name = imp.name.decode() if imp.name else "ord%d" % imp.ordinal
                stub = STUB_BASE + 16 * i
                self.uc.mem_write(stub, b"\xC3" + b"\x90" * 15)  # never executed past the hook
                self.uc.mem_write(imp.address, struct.pack("<I", stub))
                self.stub_names[stub] = (dll, name)
                i += 1

    def handle(self, name, fn, stdcall_args=0):
        """fn(emu, args_reader) -> return value (eax). stdcall_args = number of dwords callee pops."""
        self.handlers[name] = (fn, stdcall_args)

    def _on_stub(self, uc, address, size, _):
        dll, name = self.stub_names[address]
        if name not in self.handlers:
            uc.emu_stop()
            raise RuntimeError("unhandled import %s!%s" % (dll, name))
        fn, pops = self.handlers[name]
        esp = uc.reg_read(UC_X86_REG_ESP)
        ret = self.u32(esp)
        result = fn(self, lambda k: self.u32(esp + 4 + 4 * k))
        uc.reg_write(UC_X86_REG_EAX, (result or 0) & 0xFFFFFFFF)
        uc.reg_write(UC_X86_REG_ESP, esp + 4 + 4 * pops)
        uc.reg_write(UC_X86_REG_EIP, ret)

    # ---- memory helpers ----
    def u32(self, a):
        return struct.unpack("<I", self.uc.mem_read(a, 4))[0]

    def read(self, a, n):
        return bytes(self.uc.mem_read(a, n))

    def write(self, a, data):
        self.uc.mem_write(a, bytes(data))

    def alloc(self, n, data=None):
        a = self.heap_next
        self.heap_next = (a + n + 0xF) & ~0xF
        if self.heap_next > HEAP_BASE + HEAP_SIZE:
            raise MemoryError("emulator heap exhausted")
        if data is not None:
            self.write(a, data)
        return a

    def reset_heap(self):
        self.heap_next = HEAP_BASE

    # ---- calls ----
    def call(self, addr, *args, this=None, edx=None, max_insns=200_000_000):
        sp = STACK_TOP - 0x100
        frame = struct.pack("<I", RETURN_SENTINEL) + b"".join(struct.pack("<I", a & 0xFFFFFFFF) for a in args)
        sp -= len(frame)
        self.uc.mem_write(sp, frame)
        self.uc.reg_write(UC_X86_REG_ESP, sp)
        if this is not None:
            self.uc.reg_write(UC_X86_REG_ECX, this)
        if edx is not None:
            self.uc.reg_write(UC_X86_REG_EDX, edx)
        try:
            self.uc.emu_start(addr, RETURN_SENTINEL, count=max_insns)
        except UcError as e:
            eip = self.uc.reg_read(UC_X86_REG_EIP)
            raise RuntimeError("emulation fault %s at eip=%08x" % (e, eip)) from None
        if self.uc.reg_read(UC_X86_REG_EIP) != RETURN_SENTINEL:
            raise RuntimeError("function did not return (eip=%08x)" % self.uc.reg_read(UC_X86_REG_EIP))
        return self.uc.reg_read(UC_X86_REG_EAX)


def install_crt(emu):
    """Minimal msvcr90 semantics used by leaf functions (cdecl, "C" locale)."""
    def towlower(e, a):
        c = a(0) & 0xFFFF
        return c + 32 if 0x41 <= c <= 0x5A else c
    def tolower(e, a):
        c = a(0)
        return c + 32 if 0x41 <= c <= 0x5A else c
    def memcpy(e, a):
        e.write(a(0), e.read(a(1), a(2))); return a(0)
    def memset(e, a):
        e.write(a(0), bytes([a(1) & 0xFF]) * a(2)); return a(0)
    def memmove(e, a):
        e.write(a(0), e.read(a(1), a(2))); return a(0)
    for name, fn in (("towlower", towlower), ("tolower", tolower), ("memcpy", memcpy),
                     ("memset", memset), ("memmove", memmove)):
        emu.handle(name, fn)
