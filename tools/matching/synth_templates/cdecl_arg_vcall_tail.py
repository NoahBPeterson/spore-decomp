# cdecl wrapper tail-calling a virtual method of its pointer arg:
#   mov ecx,[esp+4]; mov eax,[ecx]; mov edx,[eax+slot]; jmp edx   (void f(I* p) { p->vN(); })
PATTERN = 'mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; jmp edx'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    k = N[1] // 4
    virts = " ".join("virtual void v%d();" % i for i in range(k + 1))
    src = ("struct I_%08x { %s };\nvoid FUN_%08x(I_%08x* p) { p->v%d(); }" % (va, virts, va, va, k))
    return src, "?FUN_%08x@@YAXPAUI_%08x@@@Z" % (va, va)
