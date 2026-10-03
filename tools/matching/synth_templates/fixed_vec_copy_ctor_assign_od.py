# /Od /Ob1 fixed_vector copy ctor: same layout as fixed_vec_ctor_temp_alloc_od (buf at this+0x18,
# begin=end=buf, cap=buf+size), then this->assign(other.begin, other.end, uninit-tag) via external call.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; add eax, N ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ecx], N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx + N], N ; mov eax, dword ptr [ebp - N] ; mov dword ptr [eax + N], N ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [ebp - N] ; mov dword ptr [edx + N], eax ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx + N], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax], edx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax] ; add ecx, N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx + N], ecx ; mov eax, dword ptr [ebp + N] ; mov ecx, dword ptr [eax + N] ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp + N] ; mov eax, dword ptr [edx] ; mov dword ptr [ebp - N], eax ; movzx ecx, byte ptr [ebp - N] ; push ecx ; mov edx, dword ptr [ebp - N] ; push edx ; mov eax, dword ptr [ebp - N] ; push eax ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct false_type {};\ntemplate <class T> struct is_integral : public false_type {};\n"
def emit(va, A, N):
    size = N[27]
    c = "FV_%08x" % va
    src = ("struct Al_%(v)08x { int nm; void* pool; Al_%(v)08x(void* p) { pool = p; } Al_%(v)08x(const Al_%(v)08x& o) { pool = o.pool; } };\n"
           "struct VB_%(v)08x { int* b; int* e; int* c; Al_%(v)08x al; int pad; VB_%(v)08x(const Al_%(v)08x& a) : b(0), e(0), c(0), al(a) {}\n"
           "  int* begin() const { return b; } int* end() const { return e; }\n"
           "  void DoAssign(int* f, int* l, false_type);\n"
           "  void assign(int* f, int* l) { false_type unused; DoAssign(f, l, is_integral<int*>()); } };\n"
           "struct %(c)s : VB_%(v)08x { char buf[%(s)d]; %(c)s(const %(c)s& o); };\n"
           "%(c)s::%(c)s(const %(c)s& o) : VB_%(v)08x(Al_%(v)08x(buf)) { e = (int*)buf; b = e; c = (int*)((char*)b + %(s)d);\n"
           "  assign(o.begin(), o.end()); }\n"
           ) % dict(v=va, c=c, s=size)
    return src, "??0%s@@QAE@ABU0@@Z" % c
