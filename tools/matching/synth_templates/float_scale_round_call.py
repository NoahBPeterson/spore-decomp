# cdecl(a, b): callee(b->u32 at off2, (int)round(a->float at off1 * kConst)); return 0.
# cvtss2si from a stack spill: /arch:SSE with _mm_cvtss_si32. Constant is an extern const float.
PATTERN = "mov eax, dword ptr [esp + N] ; movss xmm0, dword ptr [eax + N] ; mulss xmm0, dword ptr [A] ; movss dword ptr [esp + N], xmm0 ; cvtss2si eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx + N] ; push eax ; push edx ; call EXT ; add esp, N ; xor eax, eax ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE", "/fp:fast"]
PRELUDE = "#include <xmmintrin.h>\nextern const float kScale;\nvoid __cdecl ext_fn(unsigned, int);\n__forceinline int RoundF(float x) { __asm { cvtss2si eax, x } }\n"

def emit(va, A, N):
    o1, o2 = N[1], N[5]
    src = ("struct S1_%08x { char p[%d]; float f; };\nstruct S2_%08x { char p[%d]; unsigned v; };\n"
           "int FUN_%08x(S1_%08x* a, S2_%08x* b) { ext_fn(b->v, RoundF(a->f * kScale)); return 0; }"
           % (va, o1, va, o2, va, va, va))
    return src, "?FUN_%08x@@YAHPAUS1_%08x@@PAUS2_%08x@@@Z" % (va, va, va)
