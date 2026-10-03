# stdcall(a,b,c,d): builds {vptr,0,d} on stack (assigned v,b,vptr order), calls ext(b,a,c,&obj)
PATTERN = 'sub esp, N ; mov eax, dword ptr [esp + N] ; mov dword ptr [esp + N], eax ; mov eax, dword ptr [esp + N] ; lea edx, [esp] ; push edx ; mov edx, dword ptr [esp + N] ; push eax ; mov eax, dword ptr [esp + N] ; push edx ; push eax ; mov byte ptr [esp + N], N ; mov dword ptr [esp + N], A ; call EXT ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Obj { void* vt; char b; int v; };
"""
def emit(va, A, N):
    return ("void __stdcall ext_%08x(int,int,int,Obj*);\n"
            "extern char vt_%08x[];\n"
            "void __stdcall FUN_%08x(int a,int b,int c,int d){ Obj o; o.v=d; o.b=0; o.vt=vt_%08x; ext_%08x(b,a,c,&o); }" % (va, va, va, va, va),
            "?FUN_%08x@@YGXHHHH@Z" % va)
