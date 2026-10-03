# ISimulatorSerializable::Read-style member: __thiscall(this, Stream* s). Gets an object via
# s->vfunc8() then ->vfunc6(), passes it to a cdecl helper with (obj, &local4, 1, 0), then runs
# Base(s) (kept in bl), builds a large stack reader R(this, &desc, name), and returns
# `b && r.Read(s)` as bool (mov al,1 / xor al,al). Frame = sub esp immediate (a 4-byte local + reader).
PATTERN = 'sub esp, N ; push ebx ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push edi ; mov edi, ecx ; mov ecx, esi ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; add esp, N ; push esi ; mov ecx, edi ; call EXT ; push A ; push A ; push edi ; lea ecx, [esp + N] ; mov bl, al ; call EXT ; test bl, bl ; je +N ; push esi ; lea ecx, [esp + N] ; call EXT ; test al, al ; je +N ; pop edi ; pop esi ; mov al, N ; pop ebx ; add esp, N ; ret N ; pop edi ; pop esi ; xor al, al ; pop ebx ; add esp, N ; ret N'
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
           "struct C_%08x { bool Base(void* x); bool Read(Strm* x); };\n"
           "bool C_%08x::Read(Strm* x) { unsigned int l; void* o = x->v8()->v6(); ScopeInit(o, &l, 1, 0);"
           " bool b = Base(x); R_%08x r(this, &%s, %s);"
           " if (b && r.Read(x)) return true; return false; }"
           % (s, d, va, va, (size - 4) // 4, va, va, va, d, s))
    return src, "?Read@C_%08x@@QAE_NPAUStrm@@@Z" % va
