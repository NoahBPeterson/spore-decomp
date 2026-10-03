# void f(A* a) { if (a->x->y && a->x->y->fn) a->x->y->fn(a); }  (cdecl, tail jmp)
PATTERN = 'mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [ecx] ; mov eax, dword ptr [eax + N] ; test eax, eax ; je +N ; mov eax, dword ptr [eax + N] ; test eax, eax ; je +N ; mov dword ptr [esp + N], ecx ; jmp eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""

def emit(va, A, N):
    o1, o2 = N[1], N[2]
    t = "%08x" % va
    src = ("struct A_%s;\n"
           "typedef void (__cdecl *F_%s)(A_%s*);\n"
           "struct Y_%s { char pad[%d]; F_%s fn; };\n"
           "struct X_%s { char pad[%d]; Y_%s* y; };\n"
           "struct A_%s { X_%s* x; };\n"
           "void FUN_%s(A_%s* a) { if (a->x->y) { F_%s f = a->x->y->fn; if (f) f(a); } }") % (
           t, t, t, t, o2, t, t, o1, t, t, t, t, t, t)
    return src, "?FUN_%s@@YAXPAUA_%s@@@Z" % (t, t)
