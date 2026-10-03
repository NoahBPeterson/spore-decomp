# void S::f() { ext(); this->vN(imm); }  ext = external non-virtual thiscall member, vN virtual taking one imm arg
PATTERN = 'push esi ; mov esi, ecx ; call EXT ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push A ; mov ecx, esi ; call edx ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0]
    imm = A[0] if A else N[1]
    k = off // 4
    virts = " ".join("virtual void v%d(int);" % i for i in range(k + 1))
    src = ("struct S_%08x { void ext(); %s void FUN_%08x(); };\n"
           "void S_%08x::FUN_%08x() { ext(); v%d(0x%x); }" % (va, virts, va, va, va, k, imm))
    return src, "?FUN_%08x@S_%08x@@QAEXXZ" % (va, va)
