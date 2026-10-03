# Old-style EH (/GS-) placement-new fill loop: uninitialized_fill_n with an iterator wrapper.
#   for (; n > 0; --n, ++cur) { void* v = &*cur; new (v) C(a); }  with It cur = first;
# Key levers: the first argument is a by-value struct iterator (struct It { C* p; operator++/operator* }) and the loop
# runs over a local copy `cur`; a raw C* (even with a copy, void* temp, or template inlining) hoists/spills differently.
# Placement delete is declared only (the unwind funclet calls the folded empty stub); the ctor is an external 1-arg thiscall.
import os
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; push ecx ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; test edi, edi ; jbe +N ; jmp +N ; lea esp, [esp] ; lea ecx, [ecx] ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], N ; test esi, esi ; je +N ; mov eax, dword ptr [esp + N] ; push eax ; mov ecx, esi ; call EXT ; dec edi ; add esi, N ; mov dword ptr [esp + N], A ; test edi, edi ; ja +N ; mov ecx, dword ptr [esp + N] ; pop edi ; pop esi ; mov dword ptr fs:[N], ecx ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ("inline void* operator new(unsigned, void* p) { return p; }\n"
           "void operator delete(void*, void*);\n")

def emit(va, A, N):
    t = "%08x" % va
    code = _pe.get_data(va - _base, 128)
    j = code.index(b"\x4f\x83\xc6") if b"\x4f\x83\xc6" in code else code.index(b"\x4f\x81\xc6")
    size = code[j + 3] if code[j + 1] == 0x83 else int.from_bytes(code[j + 3:j + 7], "little")
    src = ("struct C_%s { char d[%d]; C_%s(const C_%s&); };\n"
           "struct I_%s { C_%s* p; I_%s& operator++() { ++p; return *this; } C_%s& operator*() const { return *p; } };\n"
           "void FUN_%s(I_%s first, unsigned n, const C_%s& a) { I_%s cur = first; for (; n > 0; --n, ++cur) { void* v = &*cur; new (v) C_%s(a); } }"
           % (t, size, t, t, t, t, t, t, t, t, t, t, t))
    return src, "?FUN_%s@@YAXUI_%s@@IABUC_%s@@@Z" % (t, t, t)
