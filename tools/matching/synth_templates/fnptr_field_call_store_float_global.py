# p->fn(p) returns float*; *result = global float (cdecl fn ptr field in struct, /arch:SSE)
PATTERN = 'mov eax, dword ptr [esp + N] ; push eax ; mov eax, dword ptr [eax + N] ; call eax ; movss xmm0, dword ptr [A] ; add esp, N ; movss dword ptr [eax], xmm0 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""
def emit(va, A, N):
    off = N[1]
    h = "%08x" % va
    pad = "char p[%d];" % off if off else ""
    src = ("struct S_%s { %s float* (__cdecl *fn)(S_%s*); };\n"
           "extern float g_%08x;\n"
           "void FUN_%s(S_%s* s) { *s->fn(s) = g_%08x; }\n"
           % (h, pad.replace("char", "unsigned int").replace("[%d]" % off, "[%d]" % (off // 4)) if off else "", h, A[0], h, h, A[0]))
    return src, "?FUN_%s@@YAXPAUS_%s@@@Z" % (h, h)
