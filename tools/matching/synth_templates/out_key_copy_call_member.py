# bool f(K* out, C* p) { K t = p->o->s.get(); *out = t; return true; }
# K is 16 bytes (4th field never copied) with a hand-written operator= copying b,c,a in that order;
# get() is a non-inline thiscall member on the sub-object at +4 of the object pointed to by p+4.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov ecx, dword ptr [esp + N] ; mov ecx, dword ptr [ecx + N] ; sub esp, N ; lea eax, [esp] ; push eax ; add ecx, N ; call EXT ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov dword ptr [eax + N], edx ; mov edx, dword ptr [esp] ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax], edx ; mov al, N ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    rel = struct.unpack("<i", _pe.get_data(va + 0x12 - _base, 4))[0]
    tgt = "%08x" % ((va + 0x16 + rel) & 0xffffffff)
    k, s, o, c = ("%s_%s" % (n, t) for n in "KSOC")
    src = ("struct %s { unsigned a,b,c,d; %s& operator=(const %s& r){b=r.b;c=r.c;a=r.a;return *this;} };\n"
           "struct %s { %s FUN_%s(); };\n"
           "struct %s { int pad; %s s; };\n"
           "struct %s { int pad; %s* o; };\n"
           "bool FUN_%s(%s* out, %s* p) { %s t = p->o->s.FUN_%s(); *out = t; return true; }") % (
           k, k, k, s, k, tgt, o, s, c, o, t, k, c, k, tgt)
    sym = "?FUN_%s@@YA_NPAU%s@@PAU%s@@@Z" % (t, k, c)
    return src, sym
