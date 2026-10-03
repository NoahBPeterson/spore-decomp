# eastl::vector<T>::set_capacity-style grow (sizeof(T) = 0x18 / 0x28): __thiscall, ret 4.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp ebx, eax ; jbe +N ; push edi ; test ebx, ebx ; je +N ; push N ; push A ; push N ; lea ecx, [ebx + ebx*N] ; add ecx, ecx ; push N ; add ecx, ecx ; add ecx, ecx ; push A ; push ecx ; call EXT ; add esp, N ; mov edi, eax ; jmp +N ; xor edi, edi ; mov eax, dword ptr [esi] ; push ebp ; mov ebp, dword ptr [esi + N] ; push edi ; push ebp ; push eax ; mov dword ptr [esp + N], eax ; call EXT ; mov edx, dword ptr [esp + N] ; push edi ; push ebp ; push edx ; call EXT ; mov eax, dword ptr [esi] ; add esp, N ; pop ebp ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov ecx, dword ptr [esi + N] ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; lea eax, [eax + eax*N] ; lea ecx, [edi + eax*N] ; lea edx, [ebx + ebx*N] ; lea eax, [edi + edx*N] ; mov dword ptr [esi], edi ; mov dword ptr [esi + N], ecx ; mov dword ptr [esi + N], eax ; pop edi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = '''
extern "C" void *alloc_(unsigned, const char*, int, int, const char*, int);
extern "C" void free_(void*);
'''
MAGIC = {0x2aaaaaab: 0x18, 0x66666667: 0x28}
def emit(va, A, N):
    S = MAGIC[A[0]]
    t = "T%08x" % va
    src = '''struct %(t)s { char p[%(S)d]; };
extern "C" void c1_%(v)08x(%(t)s*, %(t)s*, %(t)s*);
extern "C" void c2_%(v)08x(%(t)s*, %(t)s*, %(t)s*);
extern "C" void *alloc_%(v)08x(unsigned, const char*, int, int, const char*, int);
extern "C" void free_%(v)08x(void*);
struct V%(v)08x {
  %(t)s *b, *e, *c;
  void FUN_%(v)08x(unsigned n);
};
void V%(v)08x::FUN_%(v)08x(unsigned n) {
  if (n > (unsigned)(c - b)) {
    %(t)s *p = n ? (%(t)s*)alloc_%(v)08x(n * sizeof(%(t)s), "Simulator", 0, 0, "%(f)s", 0xd1) : 0;
    %(t)s *se = e, *sb = b;
    c1_%(v)08x(sb, se, p);
    c2_%(v)08x(sb, se, p);
    if (b && ((int*)b)[-1]) free_%(v)08x(b);
    e = p + (e - b);
    c = p + n;
    b = p;
  }
}''' % dict(t=t, S=S, v=va, f='x.h')
    return src, "?FUN_%08x@V%08x@@QAEXI@Z" % (va, va)
