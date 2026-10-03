# Pooled operator delete(void*, size): push onto a global freelist if size matches, else EASTL deallocate.
PATTERN = 'mov eax, dword ptr [esp + N] ; test eax, eax ; je +N ; cmp dword ptr [esp + N], N ; jne +N ; mov ecx, dword ptr [A] ; mov dword ptr [eax], ecx ; mov dword ptr [A], eax ; ret  ; push eax ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" void __cdecl EASTL_allocator_deallocate(void*);
"""
def emit(va, A, N):
    g = "g_%08x" % A[0]
    s = ("void* %s;\nvoid FUN_%08x(void* p, int n) {\n  if (p) {\n    if (n == %d) { *(void**)p = %s; %s = p; return; }\n"
         "    EASTL_allocator_deallocate(p);\n  }\n}" % (g, va, N[2], g, g))
    return s, "?FUN_%08x@@YAXPAXH@Z" % va
