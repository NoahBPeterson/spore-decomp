# cdecl wrapper forwarding its 3 args plus the address of a global/string to an external cdecl fn:
#   mov eax,[esp+c]; mov ecx,[esp+8]; mov edx,[esp+4]; push A; push eax; push ecx; push edx; call f; add esp,10h; ret
# Source: void f(int a,int b,int c){ ext(a,b,c,&g); } under plain /O2.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push A ; push eax ; push ecx ; push edx ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    rel = struct.unpack("<i", _pe.get_data(va + 0x15 - _base, 4))[0]
    tgt = (va + 0x19 + rel) & 0xffffffff
    src = ("extern char g_%08x;\nint __cdecl FUN_%08x(int,int,int,void*);\n"
           "void FUN_%08x(int a,int b,int c){ FUN_%08x(a,b,c,&g_%08x); }" % (A[0], tgt, va, tgt, A[0]))
    return src, "?FUN_%08x@@YAXHHH@Z" % va
