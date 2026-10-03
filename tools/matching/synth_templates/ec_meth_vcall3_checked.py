# OpenSSL EC_* wrapper: meth fn slot null check, group/point meth equality check, tail call with 3 args
PATTERN = 'mov edx, dword ptr [esp + N] ; mov eax, dword ptr [edx] ; mov ecx, dword ptr [eax + N] ; test ecx, ecx ; jne +N ; push ecx ; push ecx ; push N ; push N ; push N ; call EXT ; add esp, N ; xor eax, eax ; ret  ; push esi ; mov esi, dword ptr [esp + N] ; cmp eax, dword ptr [esi] ; je +N ; push N ; push N ; push N ; push N ; push N ; call EXT ; add esp, N ; xor eax, eax ; pop esi ; ret  ; mov eax, dword ptr [esp + N] ; push eax ; mov eax, dword ptr [esp + N] ; push eax ; mov eax, dword ptr [esp + N] ; push eax ; push esi ; push edx ; call ecx ; add esp, N ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct M { int pad[%d]; };
""" 
PRELUDE = """struct Meth;
struct Obj { Meth* meth; };
typedef int (__cdecl *Fn)(Obj*, Obj*, void*, void*, void*);
extern "C" void ERR_put_error_x(int, int, int, const char*, int);
void __cdecl ERR_put_error(int, int, int, const char*, int);
"""
def emit(va, A, N):
    print_N = N
    off = N[1]; func = N[3]
    src = """struct Meth_%08x { Fn slots[64]; };
int __cdecl FUN_%08x(Obj* a, Obj* b, void* c, void* d, void* e) {
    Fn f = ((Meth_%08x*)a->meth)->slots[%d];
    if (!f) { ERR_put_error(16, %d, 66, 0, 0); return 0; }
    if (a->meth != b->meth) { ERR_put_error(16, %d, 101, 0, 0); return 0; }
    return f(a, b, c, d, e);
}""" % (va, va, va, off // 4, func, func)
    return src, "?FUN_%08x@@YAHPAUObj@@0PAX11@Z" % va
