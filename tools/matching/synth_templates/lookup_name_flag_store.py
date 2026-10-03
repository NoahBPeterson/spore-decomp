# thiscall(arg): flag = Lookup(*Get(arg,1), &name); this->p->byte[off] = flag
PATTERN = 'push esi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; push N ; call EXT ; mov eax, dword ptr [eax] ; push A ; push eax ; call EXT ; mov ecx, dword ptr [esi + N] ; add esp, N ; mov byte ptr [ecx + N], al ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Ctx { int* v; };
struct Holder { int a, b, c; char* p; };
struct Arg { int** __thiscall Get(int n); };
bool __cdecl Lookup(int* key, const void* name);
int** __thiscall GetCtx(Arg* a, int n);
"""
PRELUDE = """struct Ctx;
struct Arg { int** Get(int n); };
struct Holder { int a, b, c; char* p; void Run(Arg* a); };
bool Lookup(int* key, const void* name);
"""
def emit(va, A, N):
    g = "g_%08x" % A[0]
    off = N[4]
    src = ("extern char %s[];\nstruct H_%08x : Holder { void __thiscall Run_%08x(Arg* a); };\n"
           "void H_%08x::Run_%08x(Arg* a) { p[0x%x] = Lookup(*a->Get(1), %s); }") % (g, va, va, va, va, off, g)
    return src, "?Run_%08x@H_%08x@@QAEXPAUArg@@@Z" % (va, va)
