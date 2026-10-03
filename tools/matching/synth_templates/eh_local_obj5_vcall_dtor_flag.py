# EH cdecl fn(obj, a, b, c): local S s(N5, 0x98, c, N2, b); obj->vf5(a, &s); ~S() frees if (flags & 4).
# S is 0x14 bytes: 16 pad bytes then u16 flags, u16 x (both zeroed by the inline ctor).
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; sub esp, N ; mov edx, dword ptr [esp + N] ; push edx ; xor eax, eax ; push N ; mov word ptr [esp + N], ax ; mov eax, dword ptr [esp + N] ; push eax ; xor ecx, ecx ; push N ; mov word ptr [esp + N], cx ; push N ; lea ecx, [esp + N] ; call EXT ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; mov edx, dword ptr [edx + N] ; lea eax, [esp] ; push eax ; mov eax, dword ptr [esp + N] ; push eax ; mov dword ptr [esp + N], N ; call edx ; test byte ptr [esp + N], N ; mov dword ptr [esp + N], A ; je +N ; push N ; lea ecx, [esp + N] ; call EXT ; mov ecx, dword ptr [esp + N] ; mov dword ptr fs:[N], ecx ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    nums = [n for n in N]
    # N order: -1(push), ... find by value: first ctor arg is last push-before-call imm
    src = ("struct S_%s { unsigned pad[4]; unsigned short fl, x;\n"
           "  void Init(unsigned, unsigned, unsigned, unsigned, unsigned);\n"
           "  void Free(int);\n"
           "  S_%s(unsigned a, unsigned b, unsigned c, unsigned d, unsigned e) : fl(0), x(0) { Init(a,b,c,d,e); }\n"
           "  ~S_%s() { if (fl & 4) Free(0); } };\n"
           "struct O_%s { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();\n"
           "  virtual void v5(unsigned, S_%s*); };\n"
           "void FUN_%s(O_%s* o, unsigned a, unsigned b, unsigned c) {\n"
           "  S_%s s(%d, 0x98, c, %d, b); o->v5(a, &s); }\n") % (t,t,t,t,t,t,t,t,N[10],N[5])
    return src, "?FUN_%s@@YAXPAUO_%s@@III@Z" % (t, t)
