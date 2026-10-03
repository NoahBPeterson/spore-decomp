# cdecl FUN(a, v): n = query(a, &n, 1, 0); v->resize(n) (thiscall); for i<n: construct(a, v->p + i*size); return a.
# Pointer v->p is reloaded each iteration (callee may modify), offset strength-reduced to edi += size.
import os
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push ebp ; push esi ; push N ; push N ; lea eax, [esp + N] ; push eax ; push ebx ; call EXT ; mov ecx, dword ptr [esp + N] ; mov ebp, dword ptr [esp + N] ; add esp, N ; push ecx ; mov ecx, ebp ; call EXT ; xor esi, esi ; cmp dword ptr [esp + N], esi ; jbe +N ; push edi ; xor edi, edi ; mov edx, dword ptr [ebp] ; add edx, edi ; push edx ; push ebx ; call EXT ; inc esi ; add esp, N ; add edi, N ; cmp esi, dword ptr [esp + N] ; jb +N ; pop edi ; pop esi ; pop ebp ; mov eax, ebx ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    code = _pe.get_data(va - _base, 100)
    j = code.index(b"\x46", 40)  # inc esi
    k = j + 4
    size = code[k + 2] if code[k + 1] == 0xc7 and code[k] == 0x83 else int.from_bytes(code[k + 2:k + 6], "little")
    t = "%08x" % va
    src = ("struct A_%(t)s;\n"
           "struct V_%(t)s { char* p; void __thiscall R(unsigned n); };\n"
           "void Q_%(t)s(A_%(t)s* a, unsigned* n, int x, int y);\n"
           "void C_%(t)s(A_%(t)s* a, char* e);\n"
           "A_%(t)s* FUN_%(t)s(A_%(t)s* a, V_%(t)s* v) {\n"
           "  unsigned n; Q_%(t)s(a, &n, 1, 0); v->R(n);\n"
           "  for (unsigned i = 0; i < n; ++i) C_%(t)s(a, v->p + i * %(sz)d);\n"
           "  return a;\n}\n") % dict(t=t, sz=size)
    return src, "?FUN_%s@@YAPAUA_%s@@PAU1@PAUV_%s@@@Z" % (t, t, t)
