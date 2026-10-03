# NEAR-MATCH only (25 diff bytes of 81: orig keeps this in esi and reuses edi for the final end compare; mine reloads [this+0x11dc] and uses edx for lea).
# bool C::Get(unsigned key): it = lower_bound_ext(begin,end,&key,flag); if (it==end||key<it->k||it==it+1) it=end;
# return it!=end && (it->v>>n)&1.   Sorted vector of {key,value} pairs (stride 8).
PATTERN = 'push esi ; mov esi, ecx ; movzx eax, byte ptr [esi + N] ; mov edx, dword ptr [esi + N] ; push edi ; mov edi, dword ptr [esi + N] ; push eax ; lea ecx, [esp + N] ; push ecx ; push edi ; push edx ; call EXT ; add esp, N ; cmp eax, edi ; je +N ; mov ecx, dword ptr [esp + N] ; cmp ecx, dword ptr [eax] ; jb +N ; lea ecx, [eax + N] ; cmp eax, ecx ; jne +N ; mov eax, edi ; cmp eax, edi ; pop edi ; pop esi ; jne +N ; xor al, al ; ret N ; mov eax, dword ptr [eax + N] ; shr eax, N ; and al, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = r'''
struct KV { unsigned k; unsigned v; };
KV* __cdecl lower_bound_ext(KV* first, KV* last, const unsigned& key, bool flag);
'''
def emit(va, A, N):
    t = "C_%08x" % va
    # N order: 0x11ec, 0x11d8, 0x11dc, 0x10(lea), 0xc, 8, 4(+4 field), shift, 1, ret 4
    offs = sorted(set(n for n in N if n >= 0x100))
    src = ("struct %s { char p[%d]; KV* b; KV* e; char q[%d]; bool flag; bool Get(unsigned key); };\n"
           "bool %s::Get(unsigned key) {\n"
           "  KV* last = e;\n  KV* it = lower_bound_ext(b, last, key, flag);\n"
           "  if (it == last || key < it->k || it == it + 1) it = last;\n"
           "  if (it == e) return false;\n"
           "  unsigned char r = (it->v >> %d) & 1; return r; }\n") % (t, 0x11d8, 0x11ec - 0x11e0, t, [n for n in N if 0 < n < 32 and n not in (4,8,0xc,0x10)][0] if any(0 < n < 32 and n not in (4,8,0xc,0x10) for n in N) else 1)
    return src, "?Get@%s@@QAE_NI@Z" % t
