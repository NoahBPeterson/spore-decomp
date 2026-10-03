# vector<T>::resize(n) where T (12/20/24 bytes) has a ctor zeroing 3 dwords at some offset: if (n > size) Fill(end, n-size, T()) else Erase(begin+n, end); thiscall member.
PATTERN = 'sub esp, N ; push ebx ; mov ebx, dword ptr [ecx + N] ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [ecx] ; mov edx, ebx ; sub edx, edi ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp esi, eax ; jbe +N ; xor eax, eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; lea edx, [esp + N] ; push edx ; mov edx, ebx ; sub edx, edi ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; sub esi, eax ; push esi ; push ebx ; call EXT ; pop edi ; pop esi ; pop ebx ; add esp, N ; ret N ; lea edx, [esi + esi*N] ; push ebx ; lea eax, [edi + edx*N] ; push eax ; call EXT ; pop edi ; pop esi ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-", "/GS-"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    size, off = N[0], N[5] - N[8]
    pre = off // 4
    post = (size - off - 12) // 4
    src = """struct T_@ { %s unsigned a, b, c; %s T_@() { a = 0; b = 0; c = 0; } };
struct V_@ { T_@* b; T_@* e; T_@* c; void FUN_@(unsigned n);
  void Fill(T_@* pos, unsigned n, const T_@& v); void Erase(T_@* f, T_@* l); };
void V_@::FUN_@(unsigned n) {
  if (n > (unsigned)(e - b)) { T_@ v; Fill(e, n - (unsigned)(e - b), v); }
  else Erase(b + n, e);
}""".replace("@", t) % ("unsigned pre[%d];" % pre if pre else "", "unsigned post[%d];" % post if post else "")
    return src, "?FUN_%s@V_%s@@QAEXI@Z" % (t, t)
