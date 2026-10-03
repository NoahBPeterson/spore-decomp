# Owner::push(unsigned v): embedded EASTL vector<unsigned*-ish>; if (e < cap) placement-new *e++ = v else stdcall DoInsertValue(e, &v).
PATTERN = 'mov eax, dword ptr [ecx + N] ; add ecx, N ; cmp eax, dword ptr [ecx + N] ; jae +N ; lea edx, [eax + N] ; mov dword ptr [ecx + N], edx ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov dword ptr [eax], ecx ; ret N ; lea edx, [esp + N] ; push edx ; push eax ; call EXT ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """inline void* operator new(unsigned, void* p) { return p; }
inline void operator delete(void*, void*) {}
"""
def emit(va, A, N):
    off = N[1]
    src = ("struct V_%08x { unsigned* b; unsigned* e; unsigned* c; void ins(unsigned*, const unsigned&);\n"
           "  void push_back(const unsigned& x) { if (e < c) { ::new((void*)e++) unsigned(x); } else ins(e, x); } };\n"
           "struct O_%08x { char pad[%d]; V_%08x v; void push(unsigned x); };\n"
           "void O_%08x::push(unsigned x) { v.push_back(x); }"
           % (va, va, off, va, va))
    return src, "?push@O_%08x@@QAEXI@Z" % va
