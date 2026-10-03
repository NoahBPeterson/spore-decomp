# vector<16-byte POD>::resize(n): if (n > size) Fill(end, n-size, T()) member thiscall; else Move(end,end,begin+n) cdecl then end -= count*16.
PATTERN = 'mov eax, dword ptr [esp + N] ; sub esp, N ; push esi ; push edi ; mov edi, ecx ; mov esi, dword ptr [edi + N] ; mov edx, dword ptr [edi] ; mov ecx, esi ; sub ecx, edx ; sar ecx, N ; cmp eax, ecx ; jbe +N ; xor edx, edx ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], edx ; lea edx, [esp + N] ; push edx ; sub eax, ecx ; push eax ; push esi ; mov ecx, edi ; call EXT ; pop edi ; pop esi ; add esp, N ; ret N ; shl eax, N ; push ebx ; add eax, edx ; mov ebx, eax ; push ebx ; push esi ; push esi ; call EXT ; sub esi, ebx ; sar esi, N ; add esp, N ; neg esi ; shl esi, N ; add dword ptr [edi + N], esi ; pop ebx ; pop edi ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-", "/GS-"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    src = """struct T_@ { unsigned a, b, c, d; T_@() { a = 0; b = 0; c = 0; d = 0; } };
void __cdecl M_@(T_@* f, T_@* l, T_@* d);
struct V_@ { T_@* b; T_@* e; T_@* c; void FUN_@(unsigned n);
  void Fill(T_@* pos, unsigned n, const T_@& v); };
void V_@::FUN_@(unsigned n) {
  unsigned sz = (unsigned)(e - b);
  if (n > sz) { T_@ v; Fill(e, n - sz, v); }
  else { T_@* p = b + n; T_@* en = e; M_@(en, en, p); e -= (en - p); }
}""".replace("@", t)
    return src, "?FUN_%s@V_%s@@QAEXI@Z" % (t, t)
