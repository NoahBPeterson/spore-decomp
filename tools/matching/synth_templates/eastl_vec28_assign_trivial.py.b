# eastl::vector<28-byte trivial T>::operator=(const vector&)
PATTERN = 'push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov esi, ecx ; cmp ebp, esi ; je +N ; mov ecx, dword ptr [ebp + N] ; push ebx ; mov ebx, dword ptr [ebp] ; sub ecx, ebx ; mov eax, A ; imul ecx ; mov eax, dword ptr [esi] ; add edx, ecx ; mov ecx, dword ptr [esi + N] ; sar edx, N ; sub ecx, eax ; push edi ; mov edi, edx ; shr edi, N ; add edi, edx ; mov eax, A ; imul ecx ; add edx, ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp edi, eax ; jbe +N ; mov ecx, dword ptr [ebp + N] ; push ecx ; push ebx ; push edi ; mov ecx, esi ; call EXT ; mov ebx, eax ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; lea edx, [edi*N] ; sub edx, edi ; lea eax, [ebx + edx*N] ; mov dword ptr [esi], ebx ; mov dword ptr [esi + N], eax ; jmp +N ; mov ecx, dword ptr [esi + N] ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; add edx, ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp edi, eax ; jbe +N ; mov ecx, dword ptr [esi] ; push ecx ; lea ecx, [eax*N] ; sub ecx, eax ; lea edx, [ebx + ecx*N] ; push edx ; push ebx ; call EXT ; mov ebx, dword ptr [esi + N] ; mov eax, dword ptr [ebp + N] ; mov dword ptr [esp + N], eax ; mov ecx, ebx ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; add edx, ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; mov edx, dword ptr [ebp] ; lea ecx, [eax*N] ; sub ecx, eax ; lea eax, [edx + ecx*N] ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push ecx ; push ebx ; push edx ; push eax ; lea eax, [esp + N] ; push eax ; call EXT ; add esp, N ; jmp +N ; mov eax, dword ptr [esi] ; mov ecx, dword ptr [ebp + N] ; push eax ; push ecx ; push ebx ; call EXT ; add esp, N ; mov eax, dword ptr [esi] ; lea edx, [edi*N] ; sub edx, edi ; lea ecx, [eax + edx*N] ; pop edi ; mov dword ptr [esi + N], ecx ; pop ebx ; mov eax, esi ; pop esi ; pop ebp ; ret N'
FLAGS = ["/O2","/arch:SSE", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    t = "%08x" % va
    src = """struct T_@ { char d[28]; ~T_@() {} };
struct R_@ { T_@* p; };
struct V_@ { T_@* b; T_@* e; T_@* c;
 T_@* Alloc(unsigned n, T_@* f, T_@* l);
 V_@& FUN_@(const V_@& x); };
T_@* Cp_@(T_@* f, T_@* l, T_@* d);
R_@* Uc_@(R_@* o, T_@* f, T_@* l, T_@* d, T_@* e);
V_@& V_@::FUN_@(const V_@& x) {
  if (&x != this) {
    unsigned n = x.e - x.b;
    if (n > (unsigned)(c - b)) {
      T_@* p = Alloc(n, x.b, x.e);
      for (T_@* q = b; q != e; ++q) q->~T_@();
      if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
      b = p; c = p + n;
    } else if (n > (unsigned)(e - b)) {
      Cp_@(x.b, x.b + (e - b), b);
      R_@ r; Uc_@(&r, x.b + (e - b), x.e, e, x.e);
    } else {
      T_@* d = Cp_@(x.b, x.e, b);
      for (T_@* q = d; q != e; ++q) q->~T_@();
    }
    e = b + n;
  }
  return *this;
}""".replace("@", t)
    return src, "?FUN_%s@V_%s@@QAEAAU1@ABU1@@Z" % (t, t)
