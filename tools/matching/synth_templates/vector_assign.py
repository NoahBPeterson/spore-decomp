# eastl::vector<T>::operator=(const vector&) for sizeof(T) = 16/32/128 (shift taken from N[3]).
# Helpers are per-instance out-of-line callees (masked relocations). Shape-equivalent source.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; cmp ebx, esi ; je +N ; mov ecx, dword ptr [ebx] ; mov edx, dword ptr [esi] ; mov eax, dword ptr [esi + N] ; push ebp ; mov ebp, dword ptr [ebx + N] ; push edi ; mov edi, ebp ; sub edi, ecx ; sub eax, edx ; sar edi, N ; sar eax, N ; cmp edi, eax ; jbe +N ; push ebp ; push ecx ; push edi ; mov ecx, esi ; call EXT ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [esi] ; push ecx ; push edx ; mov ecx, esi ; mov ebx, eax ; call EXT ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov eax, edi ; shl eax, N ; add eax, ebx ; shl edi, N ; add edi, ebx ; mov dword ptr [esi + N], edi ; pop edi ; mov dword ptr [esi + N], eax ; pop ebp ; mov dword ptr [esi], ebx ; mov eax, esi ; pop esi ; pop ebx ; ret N ; mov eax, dword ptr [esi + N] ; sub eax, edx ; sar eax, N ; push edx ; cmp edi, eax ; jbe +N ; shl eax, N ; add eax, ecx ; push eax ; push ecx ; call EXT ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [ebx + N] ; mov eax, ecx ; sub eax, dword ptr [esi] ; sar eax, N ; shl eax, N ; add eax, dword ptr [ebx] ; mov ebx, dword ptr [esp + N] ; push ebx ; push ecx ; push edx ; push eax ; lea ecx, [esp + N] ; push ecx ; call EXT ; add esp, N ; shl edi, N ; add edi, dword ptr [esi] ; mov eax, esi ; mov dword ptr [esi + N], edi ; pop edi ; pop ebp ; pop esi ; pop ebx ; ret N ; push ebp ; push ecx ; call EXT ; mov edx, dword ptr [esi + N] ; add esp, N ; push edx ; push eax ; mov ecx, esi ; call EXT ; shl edi, N ; add edi, dword ptr [esi] ; mov dword ptr [esi + N], edi ; pop edi ; pop ebp ; mov eax, esi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "void __cdecl eastl_dealloc(void*);\n"
T = """
struct @n;
struct E@x { unsigned int d[@w]; };
struct @n {
  E@x *b, *e, *c;
  E@x* a(unsigned n, E@x* f, E@x* l);
  void d(E@x* f, E@x* l);
  static E@x* __cdecl mv(E@x* f, E@x* l, E@x* o);
  static void __cdecl uc(const @n& r, E@x* f, E@x* l, E@x* o, const @n& t);
  @n& FUN_@x(const @n& x);
};
@n& @n::FUN_@x(const @n& x) {
    if (&x != this) {
      unsigned n = (unsigned)(x.e - x.b);
      if (n > (unsigned)(c - b)) {
        E@x* p = a(n, x.b, x.e);
        d(b, e);
        if (b && ((int*)b)[-1]) eastl_dealloc(b);
        b = p; e = p + n; c = p + n;
      } else if (n > (unsigned)(e - b)) {
        unsigned m = (unsigned)(e - b);
        mv(x.b, x.b + m, b);
        uc(x, x.b + m, x.e, e, x);
        e = b + n;
      } else {
        E@x* q = mv(x.b, x.e, b);
        d(q, e);
        e = b + n;
      }
    }
    return *this;
}
"""
def emit(va, A, N):
    s = 1 << N[3]
    n = "V%08x" % va
    src = T.replace("@x", "%08x" % va).replace("@n", n).replace("@w", str(s // 4))
    return src, "?FUN_%08x@%s@@QAEAAU1@ABU1@@Z" % (va, n)
