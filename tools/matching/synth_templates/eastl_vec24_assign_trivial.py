# eastl::vector<T>::operator=(const vector&) for trivially destructible 24-byte T: realloc / shrink-copy / grow-copy.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; cmp ebx, esi ; je +N ; mov edx, dword ptr [ebx + N] ; mov ecx, dword ptr [ebx] ; sub edx, ecx ; mov eax, A ; imul edx ; sar edx, N ; push ebp ; mov ebp, dword ptr [esi] ; push edi ; mov edi, edx ; shr edi, N ; add edi, edx ; mov edx, dword ptr [esi + N] ; sub edx, ebp ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp edi, eax ; jbe +N ; mov edx, dword ptr [ebx + N] ; push edx ; push ecx ; push edi ; mov ecx, esi ; call EXT ; mov ebx, eax ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; lea eax, [edi + edi*N] ; lea ecx, [ebx + eax*N] ; mov dword ptr [esi + N], ecx ; lea eax, [edi + edi*N] ; mov ecx, ebx ; pop edi ; lea edx, [ecx + eax*N] ; pop ebp ; mov dword ptr [esi], ebx ; mov dword ptr [esi + N], edx ; mov eax, esi ; pop esi ; pop ebx ; ret N ; mov edx, dword ptr [esi + N] ; sub edx, ebp ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; push ebp ; cmp edi, eax ; jbe +N ; lea edx, [eax + eax*N] ; lea eax, [ecx + edx*N] ; push eax ; push ecx ; call EXT ; mov ecx, dword ptr [ebx + N] ; mov ebp, dword ptr [esi + N] ; mov dword ptr [esp + N], ecx ; mov ecx, ebp ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; mov ecx, dword ptr [esp + N] ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; lea edx, [eax + eax*N] ; mov eax, dword ptr [ebx] ; push ecx ; lea eax, [eax + edx*N] ; mov edx, dword ptr [esp + N] ; push ebp ; push edx ; push eax ; lea eax, [esp + N] ; push eax ; call EXT ; mov ecx, dword ptr [esi] ; add esp, N ; lea eax, [edi + edi*N] ; pop edi ; lea edx, [ecx + eax*N] ; pop ebp ; mov dword ptr [esi + N], edx ; mov eax, esi ; pop esi ; pop ebx ; ret N ; mov edx, dword ptr [ebx + N] ; push edx ; push ecx ; call EXT ; mov ecx, dword ptr [esi] ; add esp, N ; lea eax, [edi + edi*N] ; lea edx, [ecx + eax*N] ; pop edi ; mov dword ptr [esi + N], edx ; pop ebp ; mov eax, esi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    t = "%08x" % va
    src = """struct T_@ { char d[24]; ~T_@() {} };
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
      b = p; e = p + n; c = p + n;
    } else if (n > (unsigned)(e - b)) {
      Cp_@(x.b, x.b + (e - b), b);
      R_@ r; Uc_@(&r, x.b + (e - b), x.e, e, x.e);
      e = b + n;
    } else {
      T_@* d = Cp_@(x.b, x.e, b);
      for (T_@* q = d; q != e; ++q) q->~T_@();
      e = b + n;
    }
  }
  return *this;
}""".replace("@", t)
    return src, "?FUN_%s@V_%s@@QAEAAU1@ABU1@@Z" % (t, t)
