# Release() on a sub-object at this+M (vptr at +0, refcount at +4): load rc, rc-1, store, return it if
# nonzero, else rc=1 and virtual-delete the sub-object (scalar deleting dtor, slot 0).
# 'rc-1' must be spelled as three uses of n-1 to get "add eax,-1" instead of "sub eax,1"/mem-form add.
PATTERN = 'mov eax, dword ptr [ecx + N] ; add ecx, N ; add eax, -N ; mov dword ptr [ecx + N], eax ; jne +N ; mov dword ptr [ecx + N], N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax] ; push N ; call edx ; xor eax, eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct SubObj { virtual ~SubObj() {} int rc; };\n"

def emit(va, A, N):
    m = N[1]
    src = ("struct Own_%08x { char pad[%d]; SubObj b; int Release(); };\n"
           "int Own_%08x::Release() { SubObj* p = &b; int n = p->rc; p->rc = n - 1; "
           "if (n - 1 != 0) return n - 1; p->rc = 1; delete p; return 0; }"
           % (va, m, va))
    return src, "?Release@Own_%08x@@QAEHXZ" % va
