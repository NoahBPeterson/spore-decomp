# vector<intrusive_ptr<T>>::push_back with old-style EH prolog (/GS-): placement new + matching delete.
PATTERN = 'mov eax, dword ptr fs:[N] ; push -N ; push A ; push eax ; mov dword ptr fs:[N], esp ; mov eax, dword ptr [ecx + N] ; sub esp, N ; cmp eax, dword ptr [ecx + N] ; jae +N ; lea edx, [eax + N] ; mov dword ptr [esp], eax ; mov dword ptr [ecx + N], edx ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], N ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov ecx, dword ptr [ecx] ; mov dword ptr [eax], ecx ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx] ; call eax ; mov ecx, dword ptr [esp + N] ; mov dword ptr fs:[N], ecx ; add esp, N ; ret N ; mov edx, dword ptr [esp + N] ; push edx ; push eax ; call EXT ; mov ecx, dword ptr [esp + N] ; mov dword ptr fs:[N], ecx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = """
inline void* operator new(unsigned, void* p) { return p; }
inline void operator delete(void*, void*) {}
struct RC { virtual void AddRef(); };
struct P { RC* p; P(const P& o) : p(o.p) { if (p) p->AddRef(); } };
"""
def emit(va, A, N):
    n = "W%08x" % va
    src = ("struct %s { int pad; P* b; P* e;\n  void Ins(P* pos, const P& v);\n"
           "  void FUN_%08x(const P& v);\n};\n"
           "void %s::FUN_%08x(const P& v) { if (b < e) { new (b++) P(v); } else Ins(b, v); }\n") % (n, va, n, va)
    return src, "?FUN_%08x@%s@@QAEXABUP@@@Z" % (va, n)
