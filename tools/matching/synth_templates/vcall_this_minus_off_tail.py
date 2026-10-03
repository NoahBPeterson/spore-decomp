# Tail-call of a virtual method on the object at this-N: mov eax,[ecx-N]; mov edx,[eax+slot]; add ecx,-N; jmp edx
# Plain C++ under /O2: ((V*)(p - N))->m() with m at vtable slot S, __fastcall wrapper.
PATTERN = 'mov eax, dword ptr [ecx - N] ; mov edx, dword ptr [eax + N] ; add ecx, A ; jmp edx'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    off, slot = N[0], N[1] // 4
    pads = "".join("virtual void p%d(); " % i for i in range(slot))
    src = ("struct V_%s { %svirtual void m(); };\n"
           "void __fastcall FUN_%s(char* p) { ((V_%s*)(p - %d))->m(); }") % (t, pads, t, t, off)
    return src, "?FUN_%s@@YIXPAD@Z" % t
