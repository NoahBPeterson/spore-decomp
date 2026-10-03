# vector<8-byte POD>::insert(pos, val): fast path when pos==end and capacity left, else out-of-line insert_aux.
PATTERN = 'push esi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esi + N] ; push edi ; mov edi, ecx ; sub edi, dword ptr [esi] ; sar edi, N ; cmp ecx, eax ; jne +N ; cmp eax, dword ptr [esi + N] ; je +N ; lea ecx, [eax + N] ; mov dword ptr [esi + N], ecx ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; mov dword ptr [eax], edx ; mov ecx, dword ptr [ecx + N] ; mov dword ptr [eax + N], ecx ; mov eax, dword ptr [esi] ; lea eax, [eax + edi*N] ; pop edi ; pop esi ; ret N ; mov edx, dword ptr [esp + N] ; push edx ; push ecx ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esi] ; lea eax, [eax + edi*N] ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "inline void* operator new(unsigned, void* p) { return p; }\ninline void operator delete(void*, void*) {}\n"
TPL = """struct E_@ { unsigned a, b; };
struct V_@ {
  E_@ *f_, *l_, *c_;
  void aux(E_@* pos, const E_@& v);
  E_@* ins(E_@* pos, const E_@& v);
};
E_@* V_@::ins(E_@* pos, const E_@& v) {
  int off = pos - f_;
  if (pos == l_ && l_ != c_) { E_@* p = l_; l_ = p + 1; ::new((void*)p) E_@(v); }
  else aux(pos, v);
  return f_ + off;
}
"""
def emit(va, A, N):
    return TPL.replace("@", "%08x" % va), "?ins@V_%08x@@QAEPAUE_%08x@@PAU2@ABU2@@Z" % (va, va)
