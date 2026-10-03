# EASTL deque<T> destructor, trivial T: empty element-dtor iterate loop, free subarrays, free ptr map.
PATTERN = 'push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; mov edx, dword ptr [esi + N] ; mov ecx, dword ptr [esi + N] ; push edi ; mov edi, dword ptr [esi + N] ; cmp eax, edi ; je +N ; add eax, N ; cmp eax, edx ; jne +N ; mov eax, dword ptr [ecx + N] ; add ecx, N ; lea edx, [eax + N] ; cmp eax, edi ; jne +N ; cmp dword ptr [esi], N ; je +N ; mov edi, dword ptr [esi + N] ; push ebx ; mov ebx, dword ptr [esi + N] ; add ebx, N ; cmp edi, ebx ; jae +N ; mov edi, edi ; mov eax, dword ptr [edi] ; test eax, eax ; je +N ; push eax ; call EXT ; add esp, N ; add edi, N ; cmp edi, ebx ; jb +N ; mov esi, dword ptr [esi] ; pop ebx ; test esi, esi ; je +N ; push esi ; call EXT ; add esp, N ; pop edi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" void __cdecl EASTL_allocator_deallocate(void*);
"""
TPL = """struct E_@ { char d[ESZ]; };
struct It4_@ { E_@* c; E_@* b; E_@* e; E_@** ap; };
struct It_@ { E_@* c; E_@* e; E_@** ap;
  It_@(const It4_@& o) : c(o.c), e(o.e), ap(o.ap) {}
  It_@& operator++() { ++c; if (c == e) { ++ap; E_@* t = *ap; e = t + SUB; c = t; } return *this; }
  bool operator!=(const It4_@& o) const { return c != o.c; } };
inline void fs_@(E_@** b, E_@** e) { for (; b < e; ++b) if (*b) EASTL_allocator_deallocate(*b); }
struct D_@ { E_@** pa; unsigned n; It4_@ bg; It4_@ en; void f(); };
void D_@::f() {
  for (It_@ i = bg; i != en; ++i) {}
  if (pa) { fs_@(bg.ap, en.ap + 1); if (pa) EASTL_allocator_deallocate(pa); }
}
"""
def emit(va, A, N):
    s = TPL.replace("ESZ", str(N[4])).replace("SUB", str(N[7] // N[4])).replace("@", "%08x" % va)
    return s, "?f@D_%08x@@QAEXXZ" % va
