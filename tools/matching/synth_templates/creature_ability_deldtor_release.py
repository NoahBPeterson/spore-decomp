# Scalar deleting dtor of a cCreatureAbility-derived class whose dtor releases a counted member
# (word flag at +4, word refcount at +6, virtual delete slot 0) and whose class operator delete
# calls gAlloc->vslot5(p, *(u16*)(p+4), tag). Base vptr store sits between release and delete test.
PATTERN = 'push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; mov dword ptr [esi], A ; cmp word ptr [ecx + N], N ; je +N ; dec word ptr [ecx + N] ; cmp word ptr [ecx + N], N ; jne +N ; mov eax, dword ptr [ecx] ; push N ; call dword ptr [eax] ; test byte ptr [esp + N], N ; mov dword ptr [esi], A ; je +N ; movzx eax, word ptr [esi + N] ; mov ecx, dword ptr [A] ; mov edx, dword ptr [ecx] ; push N ; push eax ; push esi ; call dword ptr [edx + N] ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O1", "/MD", "/Gy", "/TP", "/GR-"]
PRELUDE = r"""struct IAlloc { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void Free(void*, unsigned, int); };
extern IAlloc* gAlloc;
struct Counted { virtual void Destroy(int) = 0; unsigned short flag; short rc; };
struct cCreatureAbility {
  virtual ~cCreatureAbility() {}
  unsigned short mSize;
};
"""
def emit(va, A, N):
    c = "C_%08x" % va
    off, tag = N[0], N[10]
    pad = (off - 8) // 4
    padf = ("int pad[%d]; " % pad) if pad > 0 else ""
    src = ("struct %(c)s : cCreatureAbility { %(p)sCounted* m; %(c)s(); __forceinline virtual ~%(c)s() { Counted* q = m; if (q->flag) { if (--q->rc == 0) q->Destroy(1); } }\n"
           " static __forceinline void operator delete(void* p) { gAlloc->Free(p, ((cCreatureAbility*)p)->mSize, %(t)d); } };\n"
           "%(c)s::%(c)s() {}") % dict(c=c, p=padf, t=tag)
    return src, "??_G%s@@UAEPAXI@Z" % c
