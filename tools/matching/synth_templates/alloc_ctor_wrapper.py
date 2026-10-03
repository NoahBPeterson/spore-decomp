# Factory: p = g_alloc->vfunc4(size, 0x1c); *(short*)(p+4)=size; p->init(a,b,c,d)
PATTERN = 'mov ecx, dword ptr [A] ; mov eax, dword ptr [ecx] ; push N ; push N ; call dword ptr [eax + N] ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push ecx ; mov ecx, dword ptr [esp + N] ; push edx ; mov edx, dword ptr [esp + N] ; push ecx ; push edx ; mov ecx, eax ; mov word ptr [eax + N], N ; call EXT ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Alc { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void* alloc(int,int); };
extern Alc* g_016e4178;
"""
def emit(va, A, N):
    size = N[1]
    return ("""struct Obj%08x { int a; short s; void init(int,int,int,int); };
void FUN_%08x(int a,int b,int c,int d) {
    Obj%08x* p = (Obj%08x*)g_016e4178->alloc(%d, %d);
    p->s = %d;
    p->init(a,b,c,d);
}""" % (va, va, va, va, size, N[0], size)), "?FUN_%08x@@YAXHHHH@Z" % va
