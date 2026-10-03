# Global vector dtor: g.DoDestroy(g.begin, g.end); if (begin && ((int*)begin)[-1]) deallocate(begin)
PATTERN = 'mov eax, dword ptr [A] ; mov ecx, dword ptr [A] ; push eax ; push ecx ; mov ecx, A ; call EXT ; mov eax, dword ptr [A] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ("void EASTL_allocator_deallocate(void* p);\n"
           "struct V { void* b; void* e; void Destroy(void* b, void* e); };\n")
def emit(va, A, N):
    g = A[0]
    return ("extern V g_%08x;\n"
            "void FUN_%08x() { g_%08x.Destroy(g_%08x.b, g_%08x.e);"
            " if (g_%08x.b && ((int*)g_%08x.b)[-1]) EASTL_allocator_deallocate(g_%08x.b); }"
            % (g, va, g, g, g, g, g, g)), "?FUN_%08x@@YAXXZ" % va
