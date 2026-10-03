# bool f(int a, int b) { Obj o(b, &g, K); o.m(a); return true; }  (0xa14-byte stack object, no dtor)
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov eax, dword ptr [esp + N] ; sub esp, N ; push A ; push A ; push eax ; lea ecx, [esp + N] ; call EXT ; mov ecx, dword ptr [esp + N] ; push ecx ; lea ecx, [esp + N] ; call EXT ; mov al, N ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""

def _tgt(va, off):
    rel = struct.unpack("<i", _pe.get_data(va + off - _base, 4))[0]
    return (va + off + 4 + rel) & 0xffffffff

def emit(va, A, N):
    c1, c2 = _tgt(va, 0x1a), _tgt(va, 0x2b)
    k, g = A[0], A[1]
    src = ("struct O%08x { char b[0xa14]; O%08x(int, const void*, int); void m(int); };\n"
           "extern int g_%08x;\n"
           "bool FUN_%08x(int a, int b) { O%08x o(b, &g_%08x, 0x%x); o.m(a); return true; }"
           % (va, va, g, va, va, g, k))
    return src, "?FUN_%08x@@YA_NHH@Z" % va
