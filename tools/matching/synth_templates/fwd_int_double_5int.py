# Forwarding wrapper f(int, double, int x5) -> g(same args), cdecl, not tail-merged
PATTERN = 'mov eax, dword ptr [esp + N] ; fld qword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push eax ; mov eax, dword ptr [esp + N] ; push ecx ; mov ecx, dword ptr [esp + N] ; push edx ; mov edx, dword ptr [esp + N] ; push eax ; push ecx ; sub esp, N ; fstp qword ptr [esp] ; push edx ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    return ("void FUN_%08x_t(int,double,int,int,int,int,int);\n"
            "void FUN_%08x(int a,double b,int c,int d,int e,int f,int g){ FUN_%08x_t(a,b,c,d,e,f,g); }" % (va, va, va),
            "?FUN_%08x@@YAXHNHHHHH@Z" % va)
