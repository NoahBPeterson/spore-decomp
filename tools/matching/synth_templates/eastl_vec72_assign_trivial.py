# eastl::vector<T>::operator=(const vector&) sizeof(T)=72, out-of-line Destroy. NOT byte-exact yet:
# realloc tail CSEs p+n (orig recomputes e separately via lea) and grow branch keeps x.e in a stack spill.
PATTERN = 'push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov esi, ecx ; cmp ebp, esi ; je +N ; mov edx, dword ptr [ebp + N] ; mov ecx, dword ptr [ebp] ; sub edx, ecx ; mov eax, A ; imul edx ; sar edx, N ; push ebx ; mov ebx, dword ptr [esi] ; push edi ; mov edi, edx ; shr edi, N ; add edi, edx ; mov edx, dword ptr [esi + N] ; sub edx, ebx ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp edi, eax ; jbe +N ; mov edx, dword ptr [ebp + N] ; push edx ; push ecx ; push edi ; mov ecx, esi ; call EXT ; mov ecx, dword ptr [esi] ; mov ebx, eax ; mov eax, dword ptr [esi + N] ; push eax ; push ecx ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; lea edx, [edi + edi*N] ; lea eax, [ebx + edx*N] ; mov dword ptr [esi + N], eax ; mov eax, ebx ; lea edx, [edi + edi*N] ; pop edi ; mov dword ptr [esi], ebx ; lea ecx, [eax + edx*N] ; pop ebx ; mov dword ptr [esi + N], ecx ; mov eax, esi ; pop esi ; pop ebp ; ret N ; mov edx, dword ptr [esi + N] ; sub edx, ebx ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; push ebx ; cmp edi, eax ; jbe +N ; lea edx, [eax + eax*N] ; lea eax, [ecx + edx*N] ; push eax ; push ecx ; call EXT ; mov ecx, dword ptr [ebp + N] ; mov ebx, dword ptr [esi + N] ; mov dword ptr [esp + N], ecx ; mov ecx, ebx ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; mov ecx, dword ptr [esp + N] ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; lea edx, [eax + eax*N] ; mov eax, dword ptr [ebp] ; push ecx ; lea eax, [eax + edx*N] ; mov edx, dword ptr [esp + N] ; push ebx ; push edx ; push eax ; lea eax, [esp + N] ; push eax ; call EXT ; mov eax, dword ptr [esi] ; add esp, N ; lea edx, [edi + edi*N] ; pop edi ; lea ecx, [eax + edx*N] ; pop ebx ; mov dword ptr [esi + N], ecx ; mov eax, esi ; pop esi ; pop ebp ; ret N ; mov edx, dword ptr [ebp + N] ; push edx ; push ecx ; call EXT ; mov ecx, dword ptr [esi + N] ; add esp, N ; push ecx ; push eax ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esi] ; lea edx, [edi + edi*N] ; lea ecx, [eax + edx*N] ; pop edi ; mov dword ptr [esi + N], ecx ; pop ebx ; mov eax, esi ; pop esi ; pop ebp ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    t = "%08x" % va
    src = """struct T_@ { char d[72]; ~T_@() {} };
struct R_@ { T_@* p; };
struct V_@ { T_@* b; T_@* e; T_@* c;
 T_@* Alloc(unsigned n, T_@* f, T_@* l);
 void Destroy(T_@* f, T_@* l);
 V_@& FUN_@(const V_@& x); };
T_@* Cp_@(T_@* f, T_@* l, T_@* d);
R_@* Uc_@(R_@* o, T_@* f, T_@* l, T_@* d, T_@* e);
V_@& V_@::FUN_@(const V_@& x) {
  if (&x != this) {
    unsigned n = x.e - x.b;
    if (n > (unsigned)(c - b)) {
      T_@* p = Alloc(n, x.b, x.e);
      Destroy(b, e);
      if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
      c = p + n; b = p; e = p + n;
    } else if (n > (unsigned)(e - b)) {
      Cp_@(x.b, x.b + (e - b), b);
      R_@ r; Uc_@(&r, x.b + (e - b), x.e, e, x.e);
      e = b + n;
    } else {
      T_@* d = Cp_@(x.b, x.e, b);
      Destroy(d, e);
      e = b + n;
    }
  }
  return *this;
}""".replace("@", t)
    return src, "?FUN_%s@V_%s@@QAEAAU1@ABU1@@Z" % (t, t)
