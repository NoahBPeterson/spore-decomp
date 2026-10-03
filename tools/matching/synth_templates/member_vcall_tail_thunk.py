# Thunk forwarding to a virtual method of a member object:
#   mov ecx,[ecx+off] ; mov eax,[ecx] ; mov eax,[eax+slot] ; jmp eax
# Plain "p->o->m()" under /O2 picks "mov edx,[eax+slot]; jmp edx". The original reuses eax,
# which is what MSVC does when EDX is live: the wrapper is __fastcall (S* p, int a) forwarding
# to a __fastcall virtual m(int a) (EDX passes through untouched).
PATTERN = "mov ecx, dword ptr [ecx + N] ; mov eax, dword ptr [ecx] ; mov eax, dword ptr [eax + N] ; jmp eax"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    off, slot = N[0], N[1] // 4
    pads = "".join("virtual void p%d(); " % i for i in range(slot))
    src = ("struct I_%s { %svirtual void __fastcall m(int); };\n"
           "struct S_%s { char pad[%d]; I_%s* o; };\n"
           "void __fastcall FUN_%s(S_%s* p, int a) { p->o->m(a); }") % (t, pads, t, off, t, t, t)
    return src, "?FUN_%s@@YIXPAUS_%s@@H@Z" % (t, t)
