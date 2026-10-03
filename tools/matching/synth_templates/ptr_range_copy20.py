PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; push ebx ; push eax ; push edi ; call EXT ; mov ecx, dword ptr [esi + N] ; add esp, N ; push ecx ; push eax ; mov ecx, esi ; call EXT ; sub edi, ebx ; mov eax, A ; imul edi ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; lea edx, [eax + eax*N] ; add edx, edx ; add edx, edx ; add dword ptr [esi + N], edx ; pop edi ; pop esi ; mov eax, ebx ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct E { int a[5]; };
E* __cdecl XX(E*, E*, E*);
struct C { int p0; E* end; E* Y(E*, E*); };
"""
def emit(va, A, N):
    return ("struct C%08x : C { E* F(E*, E*); };\nE* C%08x::F(E* f, E* l) { E* r = XX(l, end, f); Y(r, end); end -= (l - f); return f; }\n" % (va, va),
            "?F@C%08x@@QAEPAUE@@PAU2@0@Z" % va)
