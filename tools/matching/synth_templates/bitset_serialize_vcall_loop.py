# Serialize a bitset<N>: write count N via self->v8()->v6() cdecl(ext, &v,1,0), then per bit write bool (via int-taking helper).
PATTERN = 'push ebx ; push ebp ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax + N] ; mov ecx, edi ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; mov dword ptr [esp + N], N ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; xor ebp, ebp ; add esp, N ; lea esi, [ebp + N] ; cmp ebp, N ; jae +N ; mov edx, dword ptr [esp + N] ; test dword ptr [edx], esi ; setne bl ; jmp +N ; xor bl, bl ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax + N] ; mov ecx, edi ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; push N ; lea edx, [esp + N] ; test bl, bl ; push edx ; setne cl ; push eax ; mov byte ptr [esp + N], cl ; call EXT ; add esp, N ; inc ebp ; rol esi, N ; cmp ebp, N ; jl +N ; mov eax, edi ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    cnt = N[4]
    o1, o2 = N[1] // 4, N[2] // 4
    pad1 = "".join("virtual void a%d(); " % i for i in range(o1))
    pad2 = "".join("virtual void b%d(); " % i for i in range(o2))
    src = f"""
typedef unsigned int u32;
struct B_{t} {{ virtual void p0(); }};
struct C_{t} {{ {pad2}virtual B_{t}* q(); }};
struct S_{t} {{ {pad1}virtual C_{t}* c(); }};
void ext1_{t}(B_{t}*, void*, int, int);
void ext2_{t}(B_{t}*, void*, int);
struct Bits_{t} {{ u32 v; bool test(u32 i) const {{ return i < {cnt} ? (v & (1u << i)) != 0 : false; }} }};
inline void w1_{t}(B_{t}* o, u32 v) {{ ext1_{t}(o, &v, 1, 0); }}
inline void w3_{t}(B_{t}* o, int v) {{ bool b = v != 0; ext2_{t}(o, &b, 1); }}
S_{t}* FUN_{t}(S_{t}* s, const Bits_{t}* m) {{
  w1_{t}(s->c()->q(), {cnt});
  for (int i = 0; i < {cnt}; ++i) {{
    bool v = m->test(i);
    w3_{t}(s->c()->q(), v);
  }}
  return s;
}}
"""
    return src, "?FUN_%s@@YAPAUS_%s@@PAU1@PBUBits_%s@@@Z" % (t, t, t)
