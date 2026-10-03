# vector<intrusive_ptr<T>>::push_back: inline construct at end (AddRef via vslot 0) else call out-of-line insert
PATTERN = 'mov eax, dword ptr [ecx + N] ; cmp eax, dword ptr [ecx + N] ; jae +N ; lea edx, [eax + N] ; mov dword ptr [ecx + N], edx ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov ecx, dword ptr [ecx] ; mov dword ptr [eax], ecx ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx] ; call eax ; ret N ; mov edx, dword ptr [esp + N] ; push edx ; push eax ; call EXT ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """
inline void* operator new(unsigned, void* p) { return p; }
struct RC { virtual void AddRef(); };
struct P { RC* p; P(const P& o) : p(o.p) { if (p) p->AddRef(); } };
"""
def emit(va, A, N):
    n = "W%08x" % va
    src = ("struct %s { int pad; P* b; P* e;\n  void Ins(P* pos, const P& v);\n"
           "  void FUN_%08x(const P& v);\n};\n"
           "void %s::FUN_%08x(const P& v) { if (b < e) { new (b++) P(v); } else Ins(b, v); }\n") % (n, va, n, va)
    return src, "?FUN_%08x@%s@@QAEXABUP@@@Z" % (va, n)
