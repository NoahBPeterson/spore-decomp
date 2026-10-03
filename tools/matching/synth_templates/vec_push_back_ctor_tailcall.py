# Vector push_back(const T&): if (mEnd < mCap) new(mEnd++) T(arg) [tail-called thiscall ctor] else DoInsert(mEnd, arg) stdcall.
PATTERN = 'mov eax, dword ptr [ecx + N] ; cmp eax, dword ptr [ecx + N] ; jae +N ; lea edx, [eax + N] ; mov dword ptr [ecx + N], edx ; test eax, eax ; je +N ; mov ecx, eax ; jmp EXT ; mov edx, dword ptr [esp + N] ; push edx ; push eax ; call EXT ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "inline void* operator new(unsigned int, void* p) { return p; }\ninline void operator delete(void*, void*) {}\n"
def emit(va, A, N):
    d = dict(t="T_%08x" % va, v="V_%08x" % va, size=N[2])
    src = ("struct %(t)s { char d[%(size)d]; %(t)s(const int&) throw(); };\n"
           "void __stdcall ins_%(v)s(%(t)s*, const int&);\n"
           "struct %(v)s { int pad; %(t)s* e; %(t)s* c; void push(const int& a); };\n"
           "void %(v)s::push(const int& a) {\n  if (e < c) { new (e++) %(t)s(a); } else ins_%(v)s(e, a);\n}\n") % d
    return src, "?push@%(v)s@@QAEXABH@Z" % d
