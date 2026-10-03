# EASTL basic_string<char16>::append_sprintf_va_list(fmt, va_list) with out-of-line reserve and retry-doubling loop.
PATTERN = 'sub esp, N ; push ebx ; push ebp ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; mov eax, dword ptr [esi] ; mov ebp, ecx ; sub ebp, eax ; sar ebp, N ; push edi ; cmp eax, A ; jne +N ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push eax ; push edx ; push N ; jmp +N ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esi + N] ; push edx ; mov edx, dword ptr [esp + N] ; sub eax, ecx ; sar eax, N ; push edx ; push eax ; push ecx ; call EXT ; mov ecx, dword ptr [esi + N] ; mov ebx, eax ; mov eax, dword ptr [esi + N] ; sub ecx, eax ; sar ecx, N ; add esp, N ; cmp ebx, ecx ; jl +N ; lea edx, [ebx + ebp] ; push edx ; mov ecx, esi ; call EXT ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; push ecx ; push edx ; inc ebx ; lea eax, [eax + ebp*N] ; push ebx ; push eax ; call EXT ; add esp, N ; mov ebx, eax ; test ebx, ebx ; jl +N ; mov edx, dword ptr [esi] ; add ebx, ebp ; lea eax, [edx + ebx*N] ; mov dword ptr [esi + N], eax ; pop edi ; mov eax, esi ; pop esi ; pop ebp ; pop ebx ; add esp, N ; ret N ; test ebx, ebx ; jge +N ; sub eax, dword ptr [esi] ; mov dword ptr [esp + N], N ; sar eax, N ; add eax, eax ; mov dword ptr [esp + N], eax ; cmp eax, N ; lea eax, [esp + N] ; ja +N ; lea eax, [esp + N] ; mov edi, dword ptr [eax] ; lea ebx, [ebx] ; cmp edi, N ; jae +N ; push edi ; mov ecx, esi ; call EXT ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; push ecx ; mov ecx, edi ; sub ecx, ebp ; push edx ; inc ecx ; lea eax, [eax + ebp*N] ; push ecx ; push eax ; call EXT ; mov ebx, eax ; add esp, N ; add edi, edi ; test ebx, ebx ; jl +N ; jmp +N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "template<class T> inline const T& mx(const T& a, const T& b){ return (a<b)?b:a; }\n"
TPL = """extern unsigned short E_@[];
int __cdecl V_@(unsigned short*, unsigned, const unsigned short*, void*);
struct S_@ {
  unsigned short *b, *e, *c;
  void __thiscall rs(unsigned n);
  S_@& __thiscall f(const unsigned short* fmt, void* va);
};
S_@& S_@::f(const unsigned short* fmt, void* va) {
  const int init = (int)(e - b);
  int n;
  if (b == E_@) n = V_@(e, 0, fmt, va);
  else { unsigned r = (unsigned)(c - e); n = V_@(e, r, fmt, va); }
  if (n >= (int)(c - e)) {
    rs(n + init);
    unsigned short* p = b + init;
    n = V_@(p, n + 1, fmt, va);
  } else if (n < 0) {
    const unsigned sz2 = (unsigned)(e - b) * 2; const unsigned sev = 7;
    unsigned w = mx(sev, sz2);
    do {
      if (w >= 1000000u) break;
      rs(w);
      unsigned short* p = b + init;
      n = V_@(p, w - init + 1, fmt, va);
      w *= 2;
    } while (n < 0);
  }
  if (n >= 0) e = b + (n + init);
  return *this;
}
"""
def emit(va, A, N):
    t = "%08x" % va
    return TPL.replace("E_@", "g_%08x" % A[0]).replace("@", t), "?f@S_%s@@QAEAAU1@PBGPAX@Z" % t
