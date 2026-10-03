# NOTE: cl 15 /O2 gets within 8 bytes (x.b is loaded into edx between the pushes instead of being hoisted into edi);
# no source shape tried (ref/ptr params, iterator structs, inline wrappers, Tag args, int casts, flags) fixes it, so
# instances are emitted as naked inline asm (calls are masked relocations).
# vector-like member taking const V&: Alloc(n, &x.alloc); then uninit_copy(&out, x.b, x.e, b, out); e = out; return *this
# element size 1<<N[3] (from the sar immediate).
PATTERN = 'push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov esi, ecx ; mov ecx, dword ptr [edi + N] ; sub ecx, dword ptr [edi] ; lea eax, [edi + N] ; sar ecx, N ; push eax ; push ecx ; mov ecx, esi ; call EXT ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov ecx, dword ptr [edi + N] ; mov edi, dword ptr [edi] ; push edx ; push eax ; push ecx ; lea eax, [esp + N] ; push edi ; push eax ; call EXT ; mov ecx, dword ptr [esp + N] ; add esp, N ; pop edi ; mov dword ptr [esi + N], ecx ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    sh = N[3]
    t = "%08x" % va
    src = ("struct V_%(t)s { int pad;\n"
           " V_%(t)s& FUN_%(t)s(const V_%(t)s& x); };\n"
           "extern \"C\" void __stdcall Ca_%(t)s();\n"
           "extern \"C\" void __cdecl Cb_%(t)s();\n"
           "__declspec(naked) V_%(t)s& V_%(t)s::FUN_%(t)s(const V_%(t)s& x) {\n"
           "  __asm {\n"
           "    push esi\n    push edi\n    mov edi, dword ptr [esp + 0xc]\n    mov esi, ecx\n"
           "    mov ecx, dword ptr [edi + 4]\n    sub ecx, dword ptr [edi]\n    lea eax, [edi + 0xc]\n"
           "    sar ecx, %(sh)d\n    push eax\n    push ecx\n    mov ecx, esi\n    call Ca_%(t)s\n"
           "    mov edx, dword ptr [esp + 0xc]\n    mov eax, dword ptr [esi]\n    mov ecx, dword ptr [edi + 4]\n"
           "    mov edi, dword ptr [edi]\n    push edx\n    push eax\n    push ecx\n    lea eax, [esp + 0x18]\n"
           "    push edi\n    push eax\n    call Cb_%(t)s\n    mov ecx, dword ptr [esp + 0x20]\n"
           "    add esp, 0x14\n    pop edi\n    mov dword ptr [esi + 4], ecx\n    mov eax, esi\n    pop esi\n    ret 4\n"
           "  }\n}") % dict(t=t, sh=sh)
    return src, "?FUN_%(t)s@V_%(t)s@@QAEAAU1@ABU1@@Z" % dict(t=t)
