# cdecl bool f(Obj* a, int x): b = a->vslot(N1)(); c = b->vslot(N2)(); ext(c, x, K, 0); return true;
# Callee decoded from the call; vtable slots from the displacement immediates.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; mov ecx, dword ptr [esp + N] ; push N ; push N ; push ecx ; push eax ; call EXT ; add esp, N ; mov al, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 0x1f - _base, 4))[0]
    return va + 0x23 + rel

def _pad(n):
    return "".join("virtual void p%d(); " % i for i in range(n))

def emit(va, A, N):
    s1, s2, k = N[1] // 4, N[2] // 4, N[5]
    tgt = _callee(va)
    src = ("struct C%08x {};\n"
           "struct B%08x { %s virtual C%08x* m(); };\n"
           "struct A%08x { %s virtual B%08x* m(); };\n"
           "void __cdecl FUN_%08x(C%08x*, int, int, int);\n"
           "bool FUN_%08x(A%08x* a, int x) { C%08x* c = a->m()->m(); FUN_%08x(c, x, %d, 0); return true; }"
           % (va, va, _pad(s2), va, va, _pad(s1), va, tgt, va, va, va, va, tgt, k))
    return src, "?FUN_%08x@@YA_NPAUA%08x@@H@Z" % (va, va)
