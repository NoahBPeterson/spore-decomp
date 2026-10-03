# void C::set(int v) { if (f != v) { f = v; m.g(v*v*6); } }  (m sub-object at +N, g non-inline thiscall member)
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov eax, dword ptr [esp + N] ; cmp dword ptr [ecx + N], eax ; je +N ; mov dword ptr [ecx + N], eax ; imul eax, eax ; lea eax, [eax + eax*N] ; add eax, eax ; mov dword ptr [esp + N], eax ; add ecx, N ; jmp EXT ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""

def emit(va, A, N):
    foff, soff = N[1], N[-2]
    t = "%08x" % va
    # add ecx at va+0x11 (imm8), jmp at +0x14
    b = _pe.get_data(va - _base + 0x14, 5)
    tgt = ("%08x" % ((va + 0x14 + 5 + struct.unpack("<i", b[1:5])[0]) & 0xffffffff)) if b[0] == 0xE9 else t + "_tgt"
    pad1 = " char p1[%d];" % foff if foff else ""
    pad2 = " char p2[%d];" % (soff - foff - 4) if soff - foff - 4 else ""
    src = ("struct M_%s_%s { void FUN_%s(int); };\n"
           "struct C_%s {%s int f;%s M_%s_%s m; void FUN_%s(int); };\n"
           "void C_%s::FUN_%s(int v) { if (f != v) { f = v; m.FUN_%s(v * v * 6); } }") % (
           t, tgt, tgt, t, pad1, pad2, t, tgt, t, t, t, tgt)
    return src, "?FUN_%s@C_%s@@QAEXH@Z" % (t, t)
