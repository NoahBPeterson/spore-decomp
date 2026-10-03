# vector<T*-like intrusive elems, stride 12/20>::erase(first,last): p=h(last,end,first); for(;p<end;p+=stride) if(*p) (*p)->vslot(); end -= (last-first); return first
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push ebp ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esi + N] ; push edi ; push ecx ; push eax ; push ebx ; call EXT ; mov ebp, dword ptr [esi + N] ; add esp, N ; mov edi, eax ; cmp eax, ebp ; jae +N ; mov ecx, dword ptr [edi] ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; call eax ; add edi, N ; cmp edi, ebp ; jb +N ; mov ecx, dword ptr [esp + N] ; sub ebx, ecx ; mov eax, A ; imul ebx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; lea edx, [eax + eax*N] ; add edx, edx ; pop edi ; add edx, edx ; add dword ptr [esi + N], edx ; pop esi ; pop ebp ; mov eax, ecx ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    import sys
    # N: 4(?)... find slot = value after 'lea'-independent: use known positions
    stride = N[6]
    # vslot is the immediate of mov eax,[edx+N]: the first N after the esi+4 loads that is not a stack/small one
    slot = N[5]
    n = slot // 4
    d = dict(va=va, t="T_%08x" % va, s="S_%08x" % va, n=n, pd=stride - 4,
             vs="".join("virtual void v%d(); " % i for i in range(n + 1)))
    src = ("struct I_%(va)08x { %(vs)s};\n"
           "struct %(t)s { I_%(va)08x* p; char pad[%(pd)d]; };\n"
           "%(t)s* H_%(va)08x(%(t)s*, %(t)s*, %(t)s*);\n"
           "inline void destroy_%(va)08x(%(t)s* a, %(t)s* b) { for (; a < b; ++a) if (a->p) a->p->v%(n)d(); }\n"
           "struct %(s)s { int a; %(t)s* e; %(t)s* end() { return e; } %(t)s* FUN_%(va)08x(%(t)s* f, %(t)s* l); };\n"
           "%(t)s* %(s)s::FUN_%(va)08x(%(t)s* f, %(t)s* l) { %(t)s* p = H_%(va)08x(l, end(), f); destroy_%(va)08x(p, end());\n"
           "  e -= (l - f); return f; }") % d
    return src, "?FUN_%08x@%s@@QAEPAU%s@@PAU2@0@Z" % (va, d["s"], d["t"])
