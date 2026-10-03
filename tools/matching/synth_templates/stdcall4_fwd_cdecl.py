# void __stdcall f(a,b,c,d) { cdecl_callee(a,b,c,d); } -- stdcall wrapper (ret 0x10) around a cdecl callee.
# Callee decoded from the call at +0x14.
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 0x15 - _base, 4))[0]
    return va + 0x19 + rel

PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push eax ; mov eax, dword ptr [esp + N] ; push ecx ; push edx ; push eax ; call EXT ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tgt = _callee(va)
    src = ("void __cdecl FUN_%08x(int, int, int, int);\n"
           "void __stdcall FUN_%08x(int a, int b, int c, int d) { FUN_%08x(a, b, c, d); }" % (tgt, va, tgt))
    return src, "?FUN_%08x@@YGXHHHH@Z" % va
