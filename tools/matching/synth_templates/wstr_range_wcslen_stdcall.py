# thiscall member F(const wchar_t* s) { this->G(s, s + (end - s)); } with a hand-written NUL-scan
# loop (not the wcslen intrinsic). ecx (this) stays live to the call, which forces edx for s.
PATTERN = 'mov edx, dword ptr [esp + N] ; cmp word ptr [edx], N ; mov eax, edx ; je +N ; lea esp, [esp] ; add eax, N ; cmp word ptr [eax], N ; jne +N ; sub eax, edx ; sar eax, N ; lea eax, [edx + eax*N] ; push eax ; push edx ; call EXT ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    src = ("struct C_%08x { void F(const wchar_t* s); void G(const wchar_t*, const wchar_t*); };\n"
           "void C_%08x::F(const wchar_t* s) {\n"
           "  const wchar_t* e = s; while (*e) ++e;\n"
           "  G(s, s + (e - s)); }" % (va, va))
    return src, "?F@C_%08x@@QAEXPB_W@Z" % va
