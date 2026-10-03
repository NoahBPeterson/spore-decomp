# void f(){ char* p=(char*)alloc(imm); *(void**)(p+o1)=fnA; *(void**)(p+o2)=fnB; } cdecl alloc, result unused.
# Callee decoded from the call at +5. N order assumed: push imm, add esp, off1, off2.
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 6 - _base, 4))[0]
    return va + 10 + rel

PATTERN = 'push N ; call EXT ; add esp, N ; mov dword ptr [eax + N], A ; mov dword ptr [eax + N], A ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tgt = _callee(va)
    o1, o2 = N[-2], N[-1]
    src = ("void* __cdecl FUN_%08x(unsigned);\n"
           "void FUN_%08x() { char* p = (char*)FUN_%08x(0x%xu);\n"
           " *(void**)(p + %d) = (void*)0x%08xu; *(void**)(p + %d) = (void*)0x%08xu; }"
           % (tgt, va, tgt, N[0], o1, A[0], o2, A[1]))
    return src, "?FUN_%08x@@YAXXZ" % va
