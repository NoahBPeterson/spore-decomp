# EASTL vector<T*>::DoAssignFromIterator(first,last,forward_iterator_tag), 4-byte elements.
# NOT byte-exact: original keeps `first` in eax (loaded before saves); every variant tried put it in ecx (190 bytes, ~51 diff).
PATTERN = 'mov eax, dword ptr [esp + N] ; push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov edx, dword ptr [esi] ; mov ecx, dword ptr [esi + N] ; push edi ; mov edi, ebx ; sub edi, eax ; sub ecx, edx ; sar edi, N ; sar ecx, N ; cmp edi, ecx ; jbe +N ; push ebx ; push eax ; push edi ; mov ecx, esi ; call EXT ; mov edx, dword ptr [esi + N] ; mov ebx, eax ; mov eax, dword ptr [esi] ; push edx ; push eax ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; cmp eax, dword ptr [esi + N] ; je +N ; push eax ; call EXT ; add esp, N ; lea eax, [ebx + edi*N] ; pop edi ; mov dword ptr [esi], ebx ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], eax ; pop esi ; pop ebx ; ret N ; mov ecx, dword ptr [esi + N] ; sub ecx, edx ; sar ecx, N ; push edx ; cmp edi, ecx ; ja +N ; push ebx ; push eax ; call EXT ; mov ecx, dword ptr [esi + N] ; add esp, N ; push ecx ; mov edi, eax ; push edi ; mov ecx, esi ; call EXT ; mov dword ptr [esi + N], edi ; pop edi ; pop esi ; pop ebx ; ret N ; lea edi, [eax + ecx*N] ; push edi ; push eax ; call EXT ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esi + N] ; push edx ; push eax ; push ebx ; lea eax, [esp + N] ; push edi ; push eax ; call EXT ; mov ecx, dword ptr [esp + N] ; add esp, N ; pop edi ; mov dword ptr [esi + N], ecx ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct Tag {};\nvoid Dealloc(void*);\n"
SRC = """struct V%(s)s {
  int* b; int* e; int* c; int pad; int* fixed;
  int* A(unsigned n, const int* f, const int* l);
  void D(int* f, int* l);
  void FUN_%(s)s(const int* first, const int* last, const Tag&);
};
int* Copy%(s)s(const int* f, const int* l, int* d);
int* Copy2%(s)s(int*& out, const int* f, const int* l, int* d, int* o);
void V%(s)s::FUN_%(s)s(const int* first, const int* last, const Tag&) {
  const unsigned n = (unsigned)(last - first);
  if (n > (unsigned)(c - b)) {
    int* p = A(n, first, last);
    D(b, e);
    if (b && b != fixed) Dealloc(b);
    c = e = p + n;
    b = p;
  } else {
    const unsigned sz = (unsigned)(e - b);
    if (n <= sz) {
      int* p = Copy%(s)s(first, last, b);
      D(p, e);
      e = p;
    } else {
      const int* mid = first + sz;
      Copy%(s)s(first, mid, b);
      Copy2%(s)s(*(int**)&last, mid, last, e, (int*)last);
      e = (int*)last;
    }
  }
}"""
def emit(va, A, N):
    s = "%08x" % va
    return SRC % {"s": s}, "?FUN_%s@V%s@@QAEXPBH0ABUTag@@@Z" % (s, s)
