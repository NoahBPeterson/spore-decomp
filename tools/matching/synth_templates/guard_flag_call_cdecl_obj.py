# if (!g_flag) { g_flag = 1; callee(&obj); }  -> cmp byte [flag],0; jne; push obj; mov byte [flag],1; call; pop ecx; ret
# Lazy one-time init guards (cdecl callee taking the address of a global).
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 0x16 - _base, 4))[0]
    return va + 0x1a + rel

PATTERN = 'cmp byte ptr [A], N ; jne +N ; push A ; mov byte ptr [A], N ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    flag, obj = A[0], A[1]
    tgt = _callee(va)
    src = ("extern bool g_%08x;\nextern char g_%08x;\nvoid __cdecl FUN_%08x(void*);\n"
           "void FUN_%08x() { if (!g_%08x) { g_%08x = true; FUN_%08x(&g_%08x); } }"
           % (flag, obj, tgt, va, flag, flag, tgt, obj))
    return src, "?FUN_%08x@@YAXXZ" % va
