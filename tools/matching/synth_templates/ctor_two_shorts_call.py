# Member fn: sets two shorts at +0x10/+0x12, calls non-inline member with *p, returns *this.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase
PATTERN = 'mov edx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov eax, N ; mov ecx, N ; mov word ptr [esi + N], cx ; mov word ptr [esi + N], ax ; mov eax, dword ptr [edx] ; push eax ; mov ecx, esi ; call EXT ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    rel = struct.unpack("<i", _pe.get_data(va + 0x1e + 1 - _base, 4))[0]
    tgt = "%08x" % ((va + 0x1e + 5 + rel) & 0xffffffff)
    cls = "C_%s" % t
    src = ("struct %s { char pad[0x10]; short a; short b; void FUN_%s(unsigned);\n"
           "  %s& FUN_%s(const unsigned* p) { a = %d; b = %d; FUN_%s(*p); return *this; } };\n"
           "template class %s;\n"
           "%s& %s::FUN_%s(const unsigned* p);\n") % (cls, tgt, cls, t, N[2], N[1], tgt, cls, cls, cls, t)
    src = ("struct %s { char pad[0x10]; short a; short b; void FUN_%s(unsigned);\n"
           "  %s& FUN_%s(const unsigned* p); };\n"
           "%s& %s::FUN_%s(const unsigned* p) { b = %d; a = %d; FUN_%s(*p); return *this; }\n"
           ) % (cls, tgt, cls, t, cls, cls, t, N[1], N[2], tgt)
    return src, "?FUN_%s@%s@@QAEAAU1@PBI@Z" % (t, cls)
