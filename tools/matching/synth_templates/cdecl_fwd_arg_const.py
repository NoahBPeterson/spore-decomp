# cdecl wrapper: f(p) { callee(p, CONST); } -> mov eax,[esp+4]; push imm; push eax; call; add esp,8; ret
# (e.g. ASN1_item_free(p, &item_template)). Callee address is decoded from the call at +0xA.
# Plain /O2; callee and imm are masked, so any extern void __cdecl(void*, unsigned) works.
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 11 - _base, 4))[0]
    return va + 15 + rel

PATTERN = "mov eax, dword ptr [esp + N] ; push A ; push eax ; call EXT ; add esp, N ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tgt = _callee(va)
    src = ("void __cdecl FUN_%08x(void*, unsigned);\n"
           "void FUN_%08x(void* p) { FUN_%08x(p, 0x%x); }" % (tgt, va, tgt, A[0] if A else N[1]))
    return src, "?FUN_%08x@@YAXPAX@Z" % va
