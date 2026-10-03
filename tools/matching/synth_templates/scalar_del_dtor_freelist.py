# Scalar deleting destructor shape: call out-of-line dtor, then if (flags&1) class operator delete
# pushes the block onto a global intrusive free list. Callee decoded from call at +3.
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 4 - _base, 4))[0]
    return va + 8 + rel

PATTERN = 'push esi ; mov esi, ecx ; call EXT ; test byte ptr [esp + N], N ; je +N ; test esi, esi ; je +N ; mov eax, dword ptr [A] ; mov dword ptr [esi], eax ; mov dword ptr [A], esi ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tgt = _callee(va)
    src = ("struct S_%08x { void D_%08x(); static void* g_%08x;\n"
           " S_%08x* FUN_%08x(unsigned f); };\n"
           "void* S_%08x::g_%08x;\n"
           "S_%08x* S_%08x::FUN_%08x(unsigned f) { D_%08x(); if ((f & 1) && this) { *(void**)this = g_%08x; g_%08x = this; } return this; }\n"
           % ((va,) * 13))
    return src, "?FUN_%08x@S_%08x@@QAEPAU1@I@Z" % (va, va)
