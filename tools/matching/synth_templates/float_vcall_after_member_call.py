# this->ext(float a, int b); this->vslot(this->field);  (thiscall, field is float, vcall passes float)
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov eax, dword ptr [esp + N] ; fld dword ptr [esp + N] ; push esi ; push eax ; push ecx ; fstp dword ptr [esp] ; mov esi, ecx ; call EXT ; fld dword ptr [esi + N] ; mov edx, dword ptr [esi] ; mov eax, dword ptr [edx + N] ; push ecx ; mov ecx, esi ; fstp dword ptr [esp] ; call eax ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    d = _pe.get_data(va - _base, 0x20)
    rel = struct.unpack("<i", d[0x11:0x15])[0]
    tgt = "%08x" % ((va + 0x15 + rel) & 0xffffffff)
    fo = d[0x17]; vo = d[0x1c]
    cls = "C_%s" % t
    pad = fo - 4
    members = "".join("  float p%d;\n" % i for i in range(1, 1)) 
    virts = "".join("  virtual void v%d();\n" % i for i in range(vo // 4)) + "  virtual void vs(float);\n"
    src = ("struct %s {\n%s  char pad[%d];\n  float f;\n  void FUN_%s(float, int);\n  void FUN_%s(float a, int b);\n};\n"
           "void %s::FUN_%s(float a, int b) { FUN_%s(a, b); vs(f); }") % (cls, virts, pad, tgt, t, cls, t, tgt)
    src = src.replace("  void FUN_%s(float a, int b);\n" % t, "  void FUN_%s(float a, int b);\n" % t)
    return src, "?FUN_%s@%s@@QAEXMH@Z" % (t, cls)
