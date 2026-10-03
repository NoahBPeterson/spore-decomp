# Variant-like setter: release if flag 4, else re-type via member call when flag 2 and type mismatch.
PATTERN = 'push esi ; mov esi, ecx ; test byte ptr [esi + N], N ; je +N ; push N ; call EXT ; mov ax, word ptr [esi + N] ; and ax, N ; je +N ; cmp word ptr [esi + N], N ; je +N ; mov eax, dword ptr [esp + N] ; push N ; push N ; push eax ; push N ; push N ; mov ecx, esi ; call EXT ; mov eax, esi ; pop esi ; ret N ; mov edx, dword ptr [esp + N] ; or eax, N ; mov ecx, N ; mov word ptr [esi + N], ax ; mov word ptr [esi + N], cx ; mov dword ptr [esi], edx ; mov dword ptr [esi + N], N ; mov dword ptr [esi + N], N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """typedef unsigned int u32; typedef unsigned short u16;
void __stdcall Release(int);
"""
def emit(va, A, N):
    t, sz = N[6], N[9]
    n = "V_%08x" % va
    src = """struct %s {
  u32 a, b, c, d; u16 flags, type;
  void Retype(int, int, u32, int, int);
  %s* Set(u32 x);
};
%s* %s::Set(u32 x) {
  if (flags & 4) Release(1);
  if ((flags & 2) && type != %d) { Retype(%d, 0x20, x, %d, 1); return this; }
  type = %d; flags = (flags & 2) | 0x20; a = x; b = %d; c = 1;
  return this;
}""" % (n, n, n, n, t, t, sz, t, sz)
    return src, "?Set@%s@@QAEPAU1@I@Z" % n
