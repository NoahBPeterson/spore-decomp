# Scalar deleting destructor (??_G) of a class with a class-specific operator delete that returns the
# block to a global pool/allocator object: alloc->Free(p, p->mSize16, TAG) (virtual, thiscall, 3 args).
#   push esi; mov esi,ecx; call ~T; test [esp+8],1; je; movzx edx,word [esi+off]; mov ecx,[g_alloc];
#   mov eax,[ecx]; push TAG; push edx; push esi; call [eax+slot]; mov eax,esi; pop esi; ret 4
# Needs /O1 (size): under /O2 the vcall becomes "mov eax,[eax+slot]; call eax". /O1 then refuses to
# inline operator delete, so it is __forceinline. Functions are 40 bytes with no int3 padding,
# consistent with an /O1 module.
PATTERN = 'push esi ; mov esi, ecx ; call EXT ; test byte ptr [esp + N], N ; je +N ; movzx edx, word ptr [esi + N] ; mov ecx, dword ptr [A] ; mov eax, dword ptr [ecx] ; push N ; push edx ; push esi ; call dword ptr [eax + N] ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct PoolAlloc {\n" +
           "".join("    virtual void v%d(void* p, unsigned int size, int tag);\n" % i for i in range(64)) +
           "};\n")

def emit(va, A, N):
    # N = [8, 1, off, TAG, 4]; the vcall slot is a call operand (not in N): 0x14 in all 58 instances.
    off, tag, slot = N[2], N[3], 5
    c = "C_%08x" % va
    pad = "    char pad[%d];\n" % (off - 4) if off > 4 else ""
    src = ("extern PoolAlloc* g_%08x;\n"
           "struct %s {\n    %s();\n    virtual ~%s();\n%s    unsigned short mSize;\n"
           "    static __forceinline void operator delete(void* p) {\n"
           "        g_%08x->v%d(p, ((%s*)p)->mSize, 0x%x);\n    }\n};\n"
           "%s::%s() {}") % (A[0], c, c, c, pad, A[0], slot, c, tag, c, c)
    return src, "??_G%s@@UAEPAXI@Z" % c
