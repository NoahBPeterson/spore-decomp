# vector<T>::erase(first,last) with element dtor loop: p=h1(last,end(),first); destroy(p,end()) (inline loop, end() getter); end -= last-first; return first
PATTERN = 'push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esi + N] ; push edi ; push ecx ; push eax ; push ebp ; call EXT ; mov ebx, dword ptr [esi + N] ; add esp, N ; mov edi, eax ; cmp eax, ebx ; jae +N ; mov ecx, edi ; call EXT ; add edi, N ; cmp edi, ebx ; jb +N ; mov ecx, dword ptr [esp + N] ; sub ebp, ecx ; mov eax, A ; imul ebp ; sub edx, ebp ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; imul eax, eax, N ; add dword ptr [esi + N], eax ; pop edi ; pop esi ; pop ebp ; mov eax, ecx ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    stride = [n for n in N if n > 0x20][-1]
    s = "S_%08x" % va
    t = "T_%08x" % va
    src = ("struct %s { char b[%d]; void D(); };\n"
           "%s* H1_%08x(%s*, %s*, %s*);\n"
           "inline void destroy_%08x(%s* a, %s* b) { for (; a < b; ++a) a->D(); }\n"
           "struct %s { char pad[4]; %s* e; %s* FUN_%08x(%s* f, %s* l); %s* end() { return e; } };\n"
           "%s* %s::FUN_%08x(%s* f, %s* l) { %s* p = H1_%08x(l, end(), f); destroy_%08x(p, end());\n"
           "  e -= (l - f); return f; }"
           ) % (t, stride, t, va, t, t, t, va, t, t, s, t, t, va, t, t, t, t, s, va, t, t, t, va, va)
    return src, "?FUN_%08x@%s@@QAEPAU%s@@PAU2@0@Z" % (va, s, t)
