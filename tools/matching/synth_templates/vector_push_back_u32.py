# EASTL-style vector<T*>::push_back(const T&): placement-new at end if room else out-of-line DoInsertValue.
# Near-match only: the original loads the arg into edx (not ecx) in the grow path; best source differs by 2 bytes.
PATTERN = 'mov eax, dword ptr [ecx + N] ; cmp eax, dword ptr [ecx + N] ; jae +N ; lea edx, [eax + N] ; mov dword ptr [ecx + N], edx ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; mov dword ptr [eax], edx ; ret N ; mov edx, dword ptr [esp + N] ; push edx ; push eax ; call EXT ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """inline void* operator new(unsigned, void*  p) { return p; }
inline void operator delete(void*, void*) {}
"""
def emit(va, A, N):
    src = ("void __stdcall Ext_%08x(unsigned*, const unsigned&);\n"
           "struct V_%08x { unsigned pad; unsigned* e; unsigned* c; void push(const unsigned& v); };\n"
           "void V_%08x::push(const unsigned& v) { if (e < c) { ::new((void*)e++) unsigned(v); } else Ext_%08x(e, v); }"
           % (va, va, va, va))
    return src, "?push@V_%08x@@QAEXABI@Z" % va
