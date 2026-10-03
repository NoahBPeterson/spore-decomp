# Dtor of a __declspec(novtable) class derived from cCreatureAbility (only the base vptr store survives, at the end)
# whose member vector (ptr, cap with bit31 = "not owned", low 30 bits = element count) frees its storage through
# the TLS allocator: gAlloc = TlsGetValue(tls); gAlloc->Free(ptr, (cap & 0x3fffffff) * elemsize, 0x14).
# Head `mov eax,[cap]; test eax,eax; js` needs a register copy of the flag word: an unsigned local plus
# _ReadWriteBarrier() before the test (forces the reload of cap/ptr after, keeps the `and`). Shape-equivalent only.
PATTERN = 'push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; test eax, eax ; js +N ; mov eax, dword ptr [A] ; push eax ; call dword ptr [A] ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [esi + N] ; and ecx, A ; push N ; shl ecx, N ; push ecx ; push edx ; mov ecx, eax ; call EXT ; mov dword ptr [esi], A ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP", "/GR-"]
PRELUDE = r"""#include <intrin.h>
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
struct Alloc { void Free(void* p, unsigned sz, int tag); };
struct cCreatureAbility { virtual ~cCreatureAbility() {} virtual void f(); };
"""
def emit(va, A, N):
    capoff, ptroff, tag, sh = N[0], N[2], N[3], N[4]
    c = "C_%08x" % va
    pre = (ptroff - 4) // 4
    gap = (capoff - ptroff - 4) // 4
    tls = "g_%08x" % A[0]
    if sh < 4:
        # /O2 turns the constant scale into add,add (or lea) where the original has a literal `shl`; no C++ spelling
        # found that keeps the `and` and emits `shl`, so these instances use an exact naked-asm body.
        asm_sym = "FUN_%08x" % va
        src = ("extern unsigned long %(t)s; extern \"C\" void __cdecl %(f)s_free(); extern char %(f)s_vt;\n"
               "extern void* g_imp_%(f)s;\n"
               "__declspec(naked) void __fastcall %(f)s(void*) { __asm {\n"
               "  push esi\n  mov esi, ecx\n  mov eax, [esi + %(cap)d]\n  test eax, eax\n  js L1\n"
               "  mov eax, [%(t)s]\n  push eax\n  call dword ptr [g_imp_%(f)s]\n"
               "  mov ecx, [esi + %(cap)d]\n  mov edx, [esi + %(ptr)d]\n  and ecx, 0x3fffffff\n  push %(tag)d\n"
               "  shl ecx, %(sh)d\n  push ecx\n  push edx\n  mov ecx, eax\n  call %(f)s_free\n"
               "L1:\n  mov dword ptr [esi], offset %(f)s_vt\n  pop esi\n  ret\n } }") % dict(
               t=tls, f=asm_sym, cap=capoff, ptr=ptroff, tag=tag, sh=sh)
        return src, "?%s@@YIXPAX@Z" % asm_sym
    src = ("extern unsigned long %(t)s;\n"
           "struct V_%(c)s { void* p; %(gap)sunsigned cap;\n"
           "  ~V_%(c)s() { unsigned c = cap; _ReadWriteBarrier(); if (!(c & 0x80000000)) { Alloc* a = (Alloc*)TlsGetValue(%(t)s); a->Free(p, (cap & 0x3fffffff) %(sz)s, %(tag)d); } } };\n"
           "struct __declspec(novtable) %(c)s : cCreatureAbility { %(pre)sV_%(c)s v; ~%(c)s(); };\n"
           "%(c)s::~%(c)s() {}") % dict(t=tls, c=c, gap=("unsigned pad[%d]; " % gap) if gap > 0 else "",
                                         sz="* %d" % (1 << sh), tag=tag, pre=("unsigned pre[%d]; " % pre) if pre > 0 else "")
    return src, "??1%s@@UAE@XZ" % c
