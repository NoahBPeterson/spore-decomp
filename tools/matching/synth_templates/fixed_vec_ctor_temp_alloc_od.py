# /Od /Ob1 fixed_vector ctor: base(Al(buf)) with allocator temp copy (copies only pool at +4);
# begin=end=buf (this+0x18), capacity=begin+size bytes. Returns this.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; add eax, N ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ecx], N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx + N], N ; mov eax, dword ptr [ebp - N] ; mov dword ptr [eax + N], N ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [ebp - N] ; mov dword ptr [edx + N], eax ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx + N], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax], edx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax] ; add ecx, N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx + N], ecx ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size = N[-4]
    c = "FV_%08x" % va
    src = ("struct Al_%08x { int nm; void* pool; Al_%08x(void* p) { pool = p; } Al_%08x(const Al_%08x& o) { pool = o.pool; } };\n"
           "struct VB_%08x { int* b; int* e; int* c; Al_%08x al; int pad; VB_%08x(const Al_%08x& a) : b(0), e(0), c(0), al(a) {} };\n"
           "struct %s : VB_%08x { char buf[%d]; %s(); };\n"
           "%s::%s() : VB_%08x(Al_%08x(buf)) { e = (int*)buf; b = e; c = (int*)((char*)b + %d); }\n"
           ) % ((va,)*4 + (va,)*4 + (c, va, size, c, c, c, va, va, size))
    return src, "??0%s@@QAE@XZ" % c
