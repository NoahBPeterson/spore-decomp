# Plain function (atexit dtor shape) for a global fixed-vector-like object: call helper(this, p, n); clear; if n>1 and p != inline buf, push to freelist if inside pool range else EASTL deallocate.
PATTERN = 'mov eax, dword ptr [A] ; mov ecx, dword ptr [A] ; push eax ; push ecx ; mov ecx, A ; call EXT ; cmp dword ptr [A], N ; mov eax, dword ptr [A] ; mov dword ptr [A], N ; jbe +N ; cmp eax, dword ptr [A] ; je +N ; cmp eax, dword ptr [A] ; jb +N ; cmp eax, dword ptr [A] ; jae +N ; mov edx, dword ptr [A] ; mov dword ptr [eax], edx ; mov dword ptr [A], eax ; ret  ; push eax ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" void __cdecl EASTL_allocator_deallocate(void*);
struct Obj {
    void h(void* p, unsigned n);
    void* p0; unsigned* p; unsigned n; unsigned z;
    unsigned pad1[3]; unsigned* head; unsigned pad2; unsigned* lo; unsigned* hi; unsigned pad3; unsigned* inl;
};
"""
def emit(va, A, N):
    g = "g_%08x" % A[2]
    s = ("Obj %(g)s;\nvoid FUN_%(va)08x() {\n"
         "  %(g)s.h(%(g)s.p, %(g)s.n);\n  unsigned* q = %(g)s.p;\n  %(g)s.z = 0;\n"
         "  if (%(g)s.n > 1 && q != %(g)s.inl) {\n"
         "    if (q >= %(g)s.lo && q < %(g)s.hi) { *(unsigned**)q = %(g)s.head; %(g)s.head = q; return; }\n"
         "    EASTL_allocator_deallocate(q);\n  }\n}") % dict(g=g, va=va)
    return s, "?FUN_%08x@@YAXXZ" % va
