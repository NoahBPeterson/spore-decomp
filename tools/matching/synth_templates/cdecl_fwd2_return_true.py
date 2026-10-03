# cdecl bool wrapper: bool f(int a, int b) { callee(a, b); return true; }
# -> mov eax,[esp+8]; mov ecx,[esp+4]; push eax; push ecx; call; add esp,8; mov al,1; ret. Plain /O2.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = "mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; push eax ; push ecx ; call EXT ; add esp, N ; mov al, N ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    rel = struct.unpack("<i", _pe.get_data(va + 11 - _base, 4))[0]
    tgt = (va + 15 + rel) & 0xffffffff
    nb = (N[0] - 4) // 4 + 1  # param index of the second forwarded arg (loaded first)
    ia = (N[1] - 4) // 4
    ib = (N[0] - 4) // 4
    params = ", ".join("int p%d" % k for k in range(nb))
    src = ("void __cdecl FUN_%08x(int, int);\n"
           "bool FUN_%08x(%s) { FUN_%08x(p%d, p%d); return true; }" % (tgt, va, params, tgt, ia, ib))
    return src, "?FUN_%08x@@YA_N" % va + "H" * nb + "@Z"
