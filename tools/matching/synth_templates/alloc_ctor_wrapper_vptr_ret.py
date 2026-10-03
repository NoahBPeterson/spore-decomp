# Factory: p = g_alloc->vfunc4(size, 0x1c); p->s=size; p->init(a,b,c,d); p->vptr=vt; return p
PATTERN = 'mov ecx, dword ptr [A] ; mov eax, dword ptr [ecx] ; push esi ; push N ; push N ; call dword ptr [eax + N] ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push ecx ; mov ecx, dword ptr [esp + N] ; mov esi, eax ; mov eax, dword ptr [esp + N] ; push edx ; push eax ; push ecx ; mov ecx, esi ; mov word ptr [esi + N], N ; call EXT ; mov dword ptr [esi], A ; mov eax, esi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Alc { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void* alloc(int,int); };
extern Alc* g_016e4178;
"""
def emit(va, A, N):
    size = N[1]
    return ("""extern char vt_%08x[];
struct Obj%08x { void* vp; short s; void init(int,int,int,int); };
Obj%08x* FUN_%08x(int a,int b,int c,int d) {
    Obj%08x* p = (Obj%08x*)g_016e4178->alloc(%d, %d);
    p->s = %d;
    p->init(a,b,c,d);
    p->vp = vt_%08x;
    return p;
}""" % (va, va, va, va, va, va, size, N[0], size, va)), "?FUN_%08x@@YAPAUObj%08x@@HHHH@Z" % (va, va)
