# EASTL-style vector::insert(pos, const T&): fast path constructs in place at end, else DoInsertValue.
import re
PATTERN = 'mov eax, dword ptr [esp + N] ; push esi ; push edi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; mov edi, eax ; sub edi, dword ptr [esi] ; sar edi, N ; cmp eax, ecx ; jne +N ; cmp ecx, dword ptr [esi + N] ; je +N ; lea eax, [ecx + N] ; mov dword ptr [esi + N], eax ; test ecx, ecx ; je +N ; mov edx, dword ptr [esp + N] ; push edx ; call EXT ; mov eax, edi ; shl eax, N ; add eax, dword ptr [esi] ; pop edi ; pop esi ; ret N ; mov ecx, dword ptr [esp + N] ; push ecx ; push eax ; mov ecx, esi ; call EXT ; mov eax, edi ; shl eax, N ; add eax, dword ptr [esi] ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/GS-", "/TP"]
PRELUDE = "#include <new>\n"
def emit(va, A, N):
    sz = 1 << N[2]
    s = """struct E_@ { char d[SZ]; E_@(const E_@&); };
struct V_@ { E_@ *b, *e, *c;
  void ins(E_@*, const E_@&);
  E_@* insert(E_@* p, const E_@& v); };
E_@* V_@::insert(E_@* p, const E_@& v) {
  const int n = p - b;
  if (p == e && e != c) { ::new((void*)e++) E_@(v); }
  else ins(p, v);
  return b + n;
}""".replace("SZ", str(sz)).replace("@", "%08x" % va)
    return s, "?insert@V_%08x@@QAEPAUE_%08x@@PAU2@ABU2@@Z" % (va, va)
