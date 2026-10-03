# Wrapper building a stack object {tbl_ptr, byte=0, p4} and calling f(p2,p1,p3,&obj) (cdecl).
PATTERN = 'sub esp, N ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; lea ecx, [esp] ; push ecx ; mov ecx, dword ptr [esp + N] ; mov dword ptr [esp + N], eax ; mov eax, dword ptr [esp + N] ; push edx ; push eax ; push ecx ; mov byte ptr [esp + N], N ; mov dword ptr [esp + N], A ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "struct Obj { void** p; unsigned char flag; unsigned p4; };\n"
def emit(va, A, N):
    return ("extern void* g_%08x[];\nvoid T_%08x(unsigned,unsigned,unsigned,Obj*);\n"
            "void FUN_%08x(unsigned p1,unsigned p2,unsigned p3,unsigned p4){ Obj o; o.p4=p4; o.flag=0; o.p=g_%08x; T_%08x(p2,p1,p3,&o); }"
            % (A[0], va, va, A[0], va),
            "?FUN_%08x@@YAXIIII@Z" % va)
