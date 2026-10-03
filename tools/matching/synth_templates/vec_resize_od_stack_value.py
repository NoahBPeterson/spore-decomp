# vector<T>::resize(n) for POD T of size S in an unoptimized (/Od /Ob1) module: if (n > size) Fill(end, n-size, local T) else Erase(begin+n, end).
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [ebp - N] ; mov eax, dword ptr [eax + N] ; sub eax, dword ptr [ecx] ; cdq  ; mov ecx, N ; idiv ecx ; cmp dword ptr [ebp + N], eax ; jbe +N ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [edx + N] ; sub ecx, dword ptr [eax] ; mov eax, ecx ; cdq  ; mov ecx, N ; idiv ecx ; mov edx, dword ptr [ebp + N] ; sub edx, eax ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax + N] ; mov dword ptr [ebp - N], ecx ; lea edx, [ebp - N] ; push edx ; mov eax, dword ptr [ebp - N] ; push eax ; mov ecx, dword ptr [ebp - N] ; push ecx ; mov ecx, dword ptr [ebp - N] ; call EXT ; jmp +N ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [edx + N] ; push eax ; mov ecx, dword ptr [ebp + N] ; imul ecx, ecx, N ; mov edx, dword ptr [ebp - N] ; add ecx, dword ptr [edx] ; push ecx ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""
# The unused local area (frame - this - count/pos - value) is derived from the frame size N[0]; it is 24 bytes except 16 for 28-byte elements.
def emit(va, A, N):
    t = "%08x" % va
    src = """struct T_@ { unsigned d[#]; };
struct V_@ { T_@* b; T_@* e; T_@* c; void FUN_@(unsigned n);
  void Fill(T_@* pos, unsigned n, const T_@& v); void Erase(T_@* f, T_@* l);
  void ins(T_@* pos, unsigned n, const T_@& v) { Fill(pos, n, v); }
  void er(unsigned n) { unsigned u[%];  Erase(b + n, e); }
};
void V_@::FUN_@(unsigned n) {
  if (n > (unsigned)(e - b)) { T_@ v; ins(e, n - (unsigned)(e - b), v); }
  else er(n);
}""".replace("@", t).replace("#", str(N[5] // 4)).replace("%", str((N[0] - 12 - N[5]) // 4))
    return src, "?FUN_%s@V_%s@@QAEXI@Z" % (t, t)
