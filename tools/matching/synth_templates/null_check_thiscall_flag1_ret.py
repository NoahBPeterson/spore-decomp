# if (p) p->f(1) with eax=1 hoisted: closest known shape is `int r=1; if(p) r=p->f(r); return r;`
# which differs only in instruction order (mov eax,1 before test instead of after).
PATTERN = 'mov ecx, dword ptr [esp + N] ; test ecx, ecx ; mov eax, N ; je +N ; push eax ; call EXT ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    return ("struct S_%08x { int f(int); };\n"
            "int FUN_%08x(S_%08x* p) { int r = 1; if (p) r = p->f(r); return r; }" % (va, va, va),
            "?FUN_%08x@@YAHPAUS_%08x@@@Z" % (va, va))
