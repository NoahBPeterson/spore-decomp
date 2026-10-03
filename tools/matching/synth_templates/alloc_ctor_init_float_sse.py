# Factory: p = alloc(g_a); if (p) { ctor(p, g_c4, g_c8); init(p, &p->f2c); p->f28 = 0; p->f2c = arg; } return p;
# /arch:SSE module (xorps/movss for the float stores); callees are cdecl externs (relocations, masked).
PATTERN = 'mov eax, dword ptr [A] ; push esi ; push eax ; call EXT ; mov esi, eax ; add esp, N ; test esi, esi ; je +N ; mov ecx, dword ptr [A] ; mov edx, dword ptr [A] ; push edi ; push ecx ; push edx ; push esi ; call EXT ; lea edi, [esi + N] ; push edi ; push esi ; call EXT ; xorps xmm0, xmm0 ; movss dword ptr [esi + N], xmm0 ; movss xmm0, dword ptr [esp + N] ; add esp, N ; movss dword ptr [edi], xmm0 ; mov eax, esi ; pop edi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ("struct T { unsigned pad[10]; float a; float b; };\n"
           "extern \"C\" { void* alloc_(int); void ctor_(void*, int, int); void init_(void*, float*); }\n")

def emit(va, A, N):
    s = "".join("extern int g_%08x;\n" % a for a in sorted(set(A)))
    s += ("T* FUN_%08x(float p) { T* t = (T*)alloc_(g_%08x); if (t) { ctor_(t, g_%08x, g_%08x); init_(t, &t->b); t->a = 0.0f; t->b = p; } return t; }"
          % (va, A[0], A[2], A[1]))
    return s, "?FUN_%08x@@YAPAUT@@M@Z" % va
