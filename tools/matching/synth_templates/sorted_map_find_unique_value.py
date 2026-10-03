# thiscall(owner*, out*): if (mKind==3) { key=mKey; r=equal_range(owner, owner+SIZE, key); if (r.first+1==r.second)
# { *out=r.first->value; this->post(); return true; } } return false;  equal_range returns pair by hidden ptr (cdecl).
PATTERN = 'sub esp, N ; push esi ; mov esi, ecx ; cmp dword ptr [esi + N], N ; jne +N ; mov eax, dword ptr [esi + N] ; mov dword ptr [esp + N], eax ; mov eax, dword ptr [esp + N] ; lea ecx, [esp + N] ; push ecx ; lea edx, [eax + N] ; push edx ; push eax ; lea eax, [esp + N] ; push eax ; call EXT ; mov eax, dword ptr [esp + N] ; lea ecx, [eax + N] ; add esp, N ; cmp ecx, dword ptr [esp + N] ; jne +N ; mov edx, dword ptr [eax + N] ; mov eax, dword ptr [esp + N] ; mov ecx, esi ; mov dword ptr [eax], edx ; call EXT ; mov al, N ; pop esi ; add esp, N ; ret N ; xor al, al ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = r'''
struct KV { unsigned k; unsigned v; };
struct RNG { KV* a; KV* b; };
RNG* __cdecl equal_range_ext(RNG* out, KV* first, KV* last, const unsigned& key);
'''
def emit(va, A, N):
    t = "T%08x" % va
    src = ("struct %s { char p0[%d]; unsigned key; char p1[%d]; int kind; void post(); bool FUN_%08x(char* o, unsigned* out); };\n"
           "bool %s::FUN_%08x(char* o, unsigned* out) {\n"
           "  if (kind == %d) { unsigned k = key; RNG r;\n"
           "    equal_range_ext(&r, (KV*)o, (KV*)(o + %d), k);\n"
           "    if (r.a + 1 == r.b) { *out = r.a->v; post(); return true; } }\n"
           "  return false; }\n") % (t, N[3], N[1] - N[3] - 4, va, t, va, N[2], N[7])
    return src, "?FUN_%08x@%s@@QAE_NPADPAI@Z" % (va, t)
