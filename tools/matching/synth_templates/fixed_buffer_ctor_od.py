# Inline fixed-capacity buffer ctor in an unoptimized (/Od /Ob1) module: zero count at +0x14,
# begin=this+0x18 (inline storage), cur=begin, end=begin+size.
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov dword ptr [eax + N], N ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ecx] ; mov dword ptr [eax + N], edx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax] ; add ecx, N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx + N], ecx ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size = N[11]
    return ("struct B_%08x { char* b; char* c; char* e; int p[2]; int n; char buf[%d];\n"
            "  void FUN_%08x(); };\n"
            "void B_%08x::FUN_%08x() { n = 0; b = buf; c = b; e = b + %d; }") % (va, size, va, va, va, size), "?FUN_%08x@B_%08x@@QAEXXZ" % (va, va)
