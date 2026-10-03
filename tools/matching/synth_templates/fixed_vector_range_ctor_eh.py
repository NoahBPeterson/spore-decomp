# EASTL fixed_vector-style range constructor with EH frame (/GS-):
#   begin=end=allocator-ptr=buf; capacity=buf+n; (state 0) DoAssign(r->first, r->last, tag)
# Class: 6 header dwords, inline buffer of n dwords at +0x18, a member with a dtor (EH state),
# an empty tag local passed by const reference. n = N[?] / 4 derived from the 'add eax, N' immediate.
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; push ecx ; push esi ; mov esi, ecx ; lea eax, [esi + N] ; mov dword ptr [esp + N], esi ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], eax ; mov dword ptr [esi], eax ; add eax, N ; mov dword ptr [esi + N], eax ; mov eax, dword ptr [esp + N] ; push eax ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [eax + N] ; mov edx, dword ptr [eax] ; push ecx ; push edx ; mov ecx, esi ; mov dword ptr [esp + N], N ; call EXT ; mov ecx, dword ptr [esp + N] ; mov eax, esi ; pop esi ; mov dword ptr fs:[N], ecx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "struct K { unsigned *a, *b; };\n"
# STATUS: NOT byte-exact. Everything matches (EH prolog with /GS-, this-slot store after the lea, store order,
# add eax,size) except one scheduling detail: the original pushes the ref arg first and then RELOADS the param
# (push eax; mov eax,[esp+0x1c]; mov ecx,[eax+4]; mov edx,[eax]; push ecx; push edx); cl CSEs the load.
# The callee is eastl vector DoAssign(first,last,tag) (ret 0xc), 3rd arg is the param pointer itself.

def emit(va, A, N):
    n = N[7] // 4  # 'add eax, size_bytes' immediate
    name = "C_%08x" % va
    src = ("struct %sB { unsigned *p0,*p1,*p2; unsigned x; unsigned *p4; unsigned y; %sB(unsigned*b){p0=p1=p4=b;} ~%sB(); };\n"
           "struct %s : %sB { unsigned buf[%d]; void init(unsigned*,unsigned*,const K*); %s(const K* k); };\n"
           "%s::%s(const K* k) : %sB(buf) { p2 = p0 + %d; init(k->a, k->b, k); }"
           % (name, name, name, name, name, n, name, name, name, name, n))
    return src, "??0%s@@QAE@PBUK@@@Z" % name
