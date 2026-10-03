# Free cdecl wrapper: bool f(int a, C* p) { p->m(a); return true; }
#   mov eax,[esp+4] ; mov ecx,[esp+8] ; push eax ; call C::m ; mov al,1 ; ret
# Plain /O2, callee external thiscall member; call target decoded from rel32 at +10.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; push eax ; call EXT ; mov al, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    rel = struct.unpack("<i", _pe.get_data(va + 10 - _base, 4))[0]
    tgt = "%08x" % ((va + 14 + rel) & 0xffffffff)
    cls = "C_%s_%s" % (t, tgt)
    src = ("struct %s { void FUN_%s(int); };\n"
           "bool FUN_%s(int a, %s* p) { p->FUN_%s(a); return true; }") % (cls, tgt, t, cls, tgt)
    return src, "?FUN_%s@@YA_NHPAU%s@@@Z" % (t, cls)
