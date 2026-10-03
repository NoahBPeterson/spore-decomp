# cdecl wrapper forwarding its pointer arg as `this` to a thiscall member and tail-jumping:
#   mov ecx,[esp+4]; jmp Obj::Method   (void f(Obj* p) { p->Method(); })
# Callee is the jmp target (relocation masked), so any extern member works.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov ecx, dword ptr [esp + N] ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct Obj { void Method(); };\n"

def emit(va, A, N):
    return "void FUN_%08x(Obj* p) { p->Method(); }" % va, "?FUN_%08x@@YAXPAUObj@@@Z" % va
