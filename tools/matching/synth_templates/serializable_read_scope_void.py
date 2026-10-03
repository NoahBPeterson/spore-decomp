# ISimulatorSerializable::Read-style void member: s->vfunc8()->vfunc6(), ScopeInit(o,&local,1,0), then stack reader R(this,&desc,name); r.Read(s). No base call, void return.
PATTERN = 'sub esp, N ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push edi ; mov edi, ecx ; mov ecx, esi ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; add esp, N ; push A ; push A ; push edi ; lea ecx, [esp + N] ; call EXT ; push esi ; lea ecx, [esp + N] ; call EXT ; pop edi ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct Obj2 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();"
           " virtual void v4(); virtual void v5(); virtual void* v6(); };\n"
           "struct Strm { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();"
           " virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual Obj2* v8(); };\n"
           "void __cdecl ScopeInit(void* o, void* local, int a, int b);\n")

def emit(va, A, N):
    s, d = "g_%08x" % A[0], "g_%08x" % A[1]
    size = N[0]
    src = ("extern const wchar_t %s[];\nextern const char %s;\n"
           "struct R_%08x { R_%08x(void* o, const void* d, const wchar_t* n); bool Read(void* x);"
           " unsigned int pad[%d]; };\n"
           "struct C_%08x { void Read(Strm* x); };\n"
           "void C_%08x::Read(Strm* x) { unsigned int l; void* o = x->v8()->v6(); ScopeInit(o, &l, 1, 0);"
           " R_%08x r(this, &%s, %s);"
           " r.Read(x); }"
           % (s, d, va, va, (size - 4) // 4, va, va, va, d, s))
    return src, "?Read@C_%08x@@QAEXPAUStrm@@@Z" % va
