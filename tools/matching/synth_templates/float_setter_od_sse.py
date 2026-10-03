# Member float setter at /Od /arch:SSE: ecx spilled, movss xmm0,[ebp+8]; movss [eax+off],xmm0; ret 4
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; movss xmm0, dword ptr [ebp + N] ; movss dword ptr [eax + N], xmm0 ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""
def emit(va, A, N):
    off = N[3]
    c = "C_%08x" % va
    pad = "char pad[%d]; " % off if off else ""
    src = ("struct %s { %sfloat f; void FUN_%08x(float v); };\n"
           "void %s::FUN_%08x(float v) { f = v; }\n") % (c, pad, va, c, va)
    return src, "?FUN_%08x@%s@@QAEXM@Z" % (va, c)
