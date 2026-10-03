# cdecl(a, b, c): for each slot copy-assign IObj* obtained via vcall Cast(id) into a ref-counted pointer array.
PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [eax + N] ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; push ebp ; push esi ; mov esi, dword ptr [edx + N] ; add esi, dword ptr [eax + N] ; xor ebp, ebp ; mov dword ptr [esp + N], ecx ; cmp dword ptr [eax + N], ebp ; jbe +N ; push ebx ; push edi ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [eax] ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; push A ; call eax ; mov ebx, dword ptr [esi] ; mov edi, eax ; cmp edi, ebx ; je +N ; test edi, edi ; je +N ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx] ; mov ecx, edi ; call eax ; mov dword ptr [esi], edi ; test ebx, ebx ; je +N ; mov edx, dword ptr [ebx] ; mov ecx, ebx ; jmp +N ; mov ecx, dword ptr [esi] ; test ecx, ecx ; je +N ; mov dword ptr [esi], N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; call eax ; mov ecx, dword ptr [esp + N] ; add dword ptr [esp + N], N ; inc ebp ; add esi, N ; cmp ebp, dword ptr [ecx + N] ; jb +N ; pop edi ; pop ebx ; pop esi ; mov al, N ; pop ebp ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct IObj { virtual void AddRef(); virtual void Release(); virtual void p2(); virtual IObj* Cast(unsigned id); };
struct C { int a[4]; int off; unsigned count; };
"""
def emit(va, A, N):
    id_ = A[0] if A else 0
    return ("""bool __cdecl FUN_%08x(char* d, IObj** s, C* c) {
  s = *(IObj***)((char*)s+4);
  IObj** dst = (IObj**)(*(char**)(d+4) + c->off);
  for (unsigned i = 0; i < c->count; i++, s++, dst++) {
    if (*s) {
      IObj* p = (*s)->Cast(0x%x);
      IObj* o = *dst;
      if (p != o) { if (p) p->AddRef(); *dst = p; if (o) o->Release(); }
    } else { IObj* o = *dst; if (o) { *dst = 0; o->Release(); } }
  }
  return true;
}""" % (va, id_)), "?FUN_%08x@@YA_NPADPAPAUIObj@@PAUC@@@Z" % va
