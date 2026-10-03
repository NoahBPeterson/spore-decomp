# vector<T>::resize(n) for POD T of size S: if (n > size) Fill(end, n-size, uninit local T) else Erase(begin+n, end); thiscall members (ecx stays live).
PATTERN = 'sub esp, N ; push ebx ; mov ebx, dword ptr [ecx + N] ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [ecx] ; mov edx, ebx ; sub edx, edi ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp esi, eax ; jbe +N ; lea edx, [esp + N] ; push edx ; mov edx, ebx ; sub edx, edi ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; sub esi, eax ; push esi ; push ebx ; call EXT ; pop edi ; pop esi ; pop ebx ; add esp, N ; ret N ; lea edx, [esi + esi*N] ; push ebx ; lea eax, [edi + edx*N] ; push eax ; call EXT ; pop edi ; pop esi ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-", "/GS-"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    src = """struct T_@ { char d[#]; };
struct V_@ { T_@* b; T_@* e; T_@* c; void FUN_@(unsigned n);
  void Fill(T_@* pos, unsigned n, const T_@& v); void Erase(T_@* f, T_@* l); };
void V_@::FUN_@(unsigned n) {
  if (n > (unsigned)(e - b)) { T_@ v; Fill(e, n - (unsigned)(e - b), v); }
  else Erase(b + n, e);
}""".replace("@", t).replace("#", str(N[0]))
    return src, "?FUN_%s@V_%s@@QAEXI@Z" % (t, t)
