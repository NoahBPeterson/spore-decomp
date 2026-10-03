# Member (thiscall) of a fixed-vector-like object: h(p, n); mCount=0; if n>1 && p != inline buf: push on pool freelist if in pool range else EASTL deallocate (cdecl).
PATTERN = 'push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esi + N] ; push eax ; push ecx ; mov ecx, esi ; call EXT ; cmp dword ptr [esi + N], N ; mov eax, dword ptr [esi + N] ; mov dword ptr [esi + N], N ; jbe +N ; cmp eax, dword ptr [esi + N] ; je +N ; cmp eax, dword ptr [esi + N] ; jb +N ; cmp eax, dword ptr [esi + N] ; jae +N ; mov edx, dword ptr [esi + N] ; mov dword ptr [eax], edx ; mov dword ptr [esi + N], eax ; pop esi ; ret  ; push eax ; call EXT ; add esp, N ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = '''extern "C" void __cdecl EASTL_allocator_deallocate(void*);
'''
def emit(va, A, N):
    c = "C_%08x" % va
    src = ("struct %(c)s {\n"
           "  void h(unsigned* p, unsigned n);\n"
           "  void FUN_%(va)08x();\n"
           "  unsigned p0; unsigned* p; unsigned n; unsigned z;\n"
           "  unsigned pad1[3]; unsigned* head; unsigned pad2; unsigned* lo; unsigned* hi; unsigned pad3; unsigned* inl;\n};\n"
           "void %(c)s::FUN_%(va)08x() {\n"
           "  h(p, n);\n  unsigned* q = p;\n  z = 0;\n"
           "  if (n > 1 && q != inl) {\n"
           "    if (q >= lo && q < hi) { *(unsigned**)q = head; head = q; return; }\n"
           "    EASTL_allocator_deallocate(q);\n  }\n}") % dict(c=c, va=va)
    return src, "?FUN_%08x@%s@@QAEXXZ" % (va, c)
