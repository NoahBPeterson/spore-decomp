# Hash table Init(n,a,b): free old buckets, cnt = log2-ish(n*4/3)+1 (min 3), special-case cnt*4==K, alloc buckets via vtable
PATTERN = 'sub esp, N ; push ebx ; push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; xor ebx, ebx ; push edi ; cmp eax, ebx ; je +N ; mov edx, dword ptr [esi] ; push eax ; mov eax, dword ptr [edx + N] ; call eax ; mov dword ptr [esi + N], ebx ; mov edi, dword ptr [esp + N] ; mov ecx, edi ; mov dword ptr [esp + N], ecx ; fild dword ptr [esp + N] ; test ecx, ecx ; jge +N ; fadd dword ptr [A] ; fmul dword ptr [A] ; fnstcw word ptr [esp + N] ; movzx eax, word ptr [esp + N] ; or eax, N ; mov dword ptr [esp + N], eax ; fldcw word ptr [esp + N] ; fistp qword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; mov dword ptr [esi + N], eax ; fldcw word ptr [esp + N] ; cmp eax, N ; jae +N ; mov dword ptr [esi + N], N ; jmp +N ; push eax ; call EXT ; add esp, N ; inc eax ; mov dword ptr [esi + N], eax ; mov edx, dword ptr [esi + N] ; add edx, edx ; add edx, edx ; cmp edx, N ; jne +N ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; push eax ; push ecx ; inc edi ; push edi ; push edx ; mov ecx, esi ; call EXT ; pop edi ; pop esi ; pop ebx ; add esp, N ; ret N ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; push edx ; push eax ; push edi ; push N ; mov ecx, esi ; call EXT ; test al, al ; je +N ; mov eax, dword ptr [esi + N] ; mov edx, dword ptr [esi] ; mov edx, dword ptr [edx + N] ; add eax, eax ; add eax, eax ; push eax ; mov ecx, esi ; call edx ; pop edi ; mov dword ptr [esi + N], eax ; cmp eax, ebx ; pop esi ; setne al ; pop ebx ; add esp, N ; ret N ; pop edi ; pop esi ; mov al, bl ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = '#include "types.h"\n'
def emit(va, A, N):
    K = N[22]
    s = """
struct HT_%(v)08x {
  virtual void v0(); virtual void v1();
  virtual void* Alloc(unsigned sz);
  virtual void Free(void* p);
  uint32_t pad[11];
  unsigned cnt; void* buckets;
  bool Sub(unsigned a, unsigned b, unsigned c, unsigned d);
  bool Init(unsigned n, unsigned a, unsigned b);
};
extern const float g_%(v)08x;
unsigned __cdecl lg_%(v)08x(unsigned);
bool HT_%(v)08x::Init(unsigned n, unsigned a, unsigned b) {
  bool ok = false;
  if (buckets != 0) { Free(buckets); buckets = 0; }
  unsigned c = (unsigned)(n * g_%(v)08x);
  cnt = c;
  if (c < 3) cnt = 3; else cnt = lg_%(v)08x(c) + 1;
  if (cnt * 4 == %(k)d) return Sub(cnt * 4, n + 1, a, b);
  if (Sub(%(k)d, n, a, b)) { buckets = Alloc(cnt * 4); ok = buckets != 0; }
  return ok;
}
""" % dict(v=va, k=K)
    return s, "?Init@HT_%08x@@QAE_NIII@Z" % va

