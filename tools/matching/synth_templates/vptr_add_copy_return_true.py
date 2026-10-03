# bool f(Out* o, const In* a, const In2* b): o->vptr = A; o->x = a->x + b->y; o->z = b->z; return true
PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov dword ptr [eax], A ; mov edx, dword ptr [ecx + N] ; mov ecx, dword ptr [esp + N] ; add edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [ecx + N] ; mov dword ptr [eax + N], ecx ; mov al, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct In { int p0; int x; int p2; int p3; };
struct In2 { int p[4]; int y; int z; };
struct Out { void* vptr; int x; int z; };
"""
def emit(va, A, N):
    return ("bool FUN_%08x(Out* o, In* a, In2* b) { o->vptr = (void*)0x%x; o->x = a->x + b->y; o->z = b->z; return true; }"
            % (va, A[0])), "?FUN_%08x@@YA_NPAUOut@@PAUIn@@PAUIn2@@@Z" % va
