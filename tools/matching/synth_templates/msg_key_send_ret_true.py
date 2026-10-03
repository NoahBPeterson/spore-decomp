# bool f(int, unsigned p) { Msg m(Key(p, K, g)); Send(&m); return true; }   (cdecl, 0x48-byte local)
# Msg : Mid : Base. Base has out-of-line ctor/dtor (no EH: throw()); Mid's inline ctor stores the message id
# FIRST; Msg's inline ctor copy-inits a 12-byte Key member, so the three args are hoisted into ebx/esi/edi
# before the base ctor call. First (unused) argument shifts p to [esp+4]; Send is cdecl taking &m.
PATTERN = 'sub esp, N ; push ebx ; mov ebx, dword ptr [A] ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; lea ecx, [esp + N] ; mov edi, A ; call EXT ; lea eax, [esp + N] ; push eax ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], ebx ; call EXT ; add esp, N ; lea ecx, [esp + N] ; call EXT ; pop edi ; pop esi ; mov al, N ; pop ebx ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Key { unsigned a,b,c; Key(unsigned x, unsigned y, unsigned z):a(x),b(y),c(z){} };
struct Base { unsigned id; unsigned pad[5]; Base() throw(); ~Base() throw(); };
struct Mid : Base { Mid(unsigned i) { id = i; } };
struct Msg : Mid { Key k; unsigned pad2[9]; Msg(unsigned i, const Key& x) : Mid(i), k(x) { } };
void __cdecl Send(Msg*) throw();
"""
def emit(va, A, N):
    gl, k, mid = A[0], A[1], A[2]
    src = ("extern unsigned g_%08x;\nbool FUN_%08x(int, unsigned p) {\n"
           "  Msg m(0x%xu, Key(p, 0x%xu, g_%08x)); Send(&m); return true;\n}") % (gl, va, mid, k, gl)
    return src, "?FUN_%08x@@YA_NHI@Z" % va
