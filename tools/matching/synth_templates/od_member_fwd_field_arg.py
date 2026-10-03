# Unoptimized (/Od /Ob1) member that forwards a field to another member: this->m(this->f)
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax + N] ; push ecx ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    off = _pe.get_data(va - _base + 12, 1)[0]
    rel = struct.unpack("<i", _pe.get_data(va + 18 - _base, 4))[0]
    tgt = "%08x" % ((va + 22 + rel) & 0xffffffff)
    cls = "C_%s" % t
    pad = ""
    if off > 0:
        pad = "char pad[%d]; " % off
    src = ("struct %s { %sint f; void FUN_%s(int); void FUN_%s(); };\n"
           "void %s::FUN_%s() { FUN_%s(f); }") % (cls, pad, tgt, t, cls, t, tgt)
    return src, "?FUN_%s@C_%s@@QAEXXZ" % (t, t)
