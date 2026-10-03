# for (; n; --n) { new(p) T(a); ++p; } as cdecl free function: placement new null-check + external thiscall ctor(1 arg).
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; test edi, edi ; jbe +N ; push ebx ; mov ebx, dword ptr [esp + N] ; test esi, esi ; je +N ; push ebx ; mov ecx, esi ; call EXT ; dec edi ; add esi, N ; test edi, edi ; ja +N ; pop ebx ; pop edi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "inline void* operator new(unsigned, void* p) { return p; }\n"

def emit(va, A, N):
    t = "%08x" % va
    code = _pe.get_data(va - _base, 64)
    i = code.index(b"\xe8", 20)
    rel = struct.unpack("<i", code[i + 1:i + 5])[0]
    tgt = "%08x" % ((va + i + 5 + rel) & 0xffffffff)
    j = code.index(b"\x4f", i)  # dec edi
    size = struct.unpack("<b", code[j + 3:j + 4])[0] if code[j + 1] == 0x83 else struct.unpack("<i", code[j + 3:j + 7])[0]
    cls = "C_%s" % t
    src = ("struct %s { char d[%d]; %s(const %s&); };\n"
           "void FUN_%s(%s* p, unsigned n, const %s& a) { %s* f = p; for (; n > 0; --n, ++f) { new (f) %s(a); } }"
           % (cls, size, cls, cls, t, cls, cls, cls, cls))
    return src, "?FUN_%s@@YAXPAU%s@@IABU1@@Z" % (t, cls)
