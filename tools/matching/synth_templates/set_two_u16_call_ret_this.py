# this->w10=a; this->w12=b; callee(arg) on this; return this  (__thiscall, ret 4)
PATTERN = 'mov edx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov ecx, N ; mov eax, N ; mov word ptr [esi + N], cx ; push edx ; mov ecx, esi ; mov word ptr [esi + N], ax ; call EXT ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct S { char pad[16]; unsigned short a, b; S* f(void*); };\n"
def emit(va, A, N):
    # N order: [esp+4]->4, ecx imm, eax imm, 0x10, 0x12, ret 4
    return ("struct S%08x { char pad[16]; unsigned short a, b; void callee(void*); S%08x* f(void* p); };\n"
            "S%08x* S%08x::f(void* p) { b = %d; a = %d; callee(p); return this; }" % (va, va, va, va, N[2], N[1])), \
           "?f@S%08x@@QAEPAU1@PAX@Z" % va
