// w1g1 slice s004f85b0 -- Skinner aligned-allocator helpers and creature
// ability destructors.  Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
void* Alloc(uint32_t size, const char* name, int, int, int, int);
void  Dealloc(void* p);

// ===========================================================================
// @ 0x004f8750  (MATCH)
// Aligned allocation wrapper: 16-byte-aligns the block and stamps a header.
// ===========================================================================
void* FUN_004f8750(int size, int param2)
{
    int v33, n40, len;
    v33 = (int)Alloc((uint32_t)(size + 0x1f), "Skinner/AlignedAlloc", 0, 0, 0, 0);
    len = (v33 + 0xf) & 0xfffffff0;
    n40 = len;
    *(int*)(n40) = 0xd6d6d6d6;
    *(int*)(n40 + 4) = v33;
    *(int*)(n40 + 8) = param2;
    *(int*)(n40 + 0xc) = 0x29292929;
    n40 += 0x10;
    return (void*)n40;
}

// ===========================================================================
// @ 0x004f87f0  (complete; not byte-exact)  creature-ability destructor tail.
// ===========================================================================
void FUN_004fc320(void* p, int);
void FUN_004f80b0(void* p);
void FUN_004c0b80(void* p);
extern int g_vtbl_13f1140;
extern int g_vtbl_13ef094;

void __fastcall FUN_004f87f0(int* self)
{
    self[0] = (int)&g_vtbl_13f1140;
    FUN_004fc320(self, 1);
    Dealloc((void*)self[0x15]);
    FUN_004f80b0((void*)self[0x12]);
    FUN_004f80b0((void*)self[7]);
    for (uint32_t i = (uint32_t)self[0x16]; i < (uint32_t)self[0x17]; i += 4) {
    }
    FUN_004c0b80(&self[0x16]);
    self[0] = (int)&g_vtbl_13ef094;
}

// ===========================================================================
// Shared types for the ability object at 0x4f8880..0x4f8d80.
// The retail functions are __thiscall (ecx = this, callee pops the stack args).
// ===========================================================================
struct SPMemPool {                                    // the global pool at 0x016c8b44
    void  FUN_009276c0(void* p);                      // 0x009276c0  free (ret 4)
    void* FUN_00928a30(uint32_t size, uint32_t align,
                       int a, int b, int c, int d, int e, int f);  // 0x00928a30 (ret 0x20)
};
extern SPMemPool* g_pSPMemPool;                       // 0x016c8b44

struct SimpleVectorU32 {                              // begin/end/capacity at +0/+4/+8
    void** mpBegin;                                   // +0
    void** mpEnd;                                     // +4
    void** mpCapacity;                                // +8
    void   FUN_004fc610(void** value);                // 0x004fc610  push_back(&value) (ret 4)
    void** erase(void** first, void** last);          // 0x004769b0  (ret 8)
};

struct AbilityEntry {                                 // 0x80-byte entry of the table
    float FUN_004f8e20(int arg1);                     // 0x004f8e20  (ret 4)
};

struct SkinnerAbility {
    char            mPad0[0xc];
    float           mfCost;                           // +0x0c  negated as the sum seed
    char            mPad10[0x58 - 0x10];
    SimpleVectorU32 mChunks;                          // +0x58  allocated pool chunks
    char            mPad64[0xf0 - 0x64];
    char*           mpBump;                           // +0xf0  bump pointer in the current chunk
    unsigned int    mnRemaining;                      // +0xf4  bytes left in the current chunk

    void* FUN_004f8880(int size, int param3);         // 0x004f8880
    void  FUN_004f89a0();                             // 0x004f89a0
    void* FUN_004f8f70(int arg1);                     // 0x004f8f70  (ret 4)
    void  FUN_004f8d80(int arg1, float* out);         // 0x004f8d80
};

// ===========================================================================
// @ 0x004f8880  (complete; not byte-exact)  aligned pool allocator.
// ===========================================================================
void* SkinnerAbility::FUN_004f8880(int size, int param3)
{
    size = (size + 0x10 + 0xf) & 0xfffffff0;
    char* base = mpBump;
    if ((uint32_t)size > mnRemaining) {
        uint32_t chunk = (uint32_t)size > 0x8000 ? (uint32_t)size : 0x8000;
        base = (char*)g_pSPMemPool->FUN_00928a30(chunk, 0x10, 0, 0, 0, 0, 0, 0);
        mChunks.FUN_004fc610((void**)&base);
        mpBump = base;
        mnRemaining = chunk;
    }
    mpBump += size;
    mnRemaining -= size;
    uint32_t* p = (uint32_t*)((uint32_t)(base + 0xf) & 0xfffffff0);
    p[0] = 0xd6d6d6d6;
    p[1] = (uint32_t)base;
    p[2] = (uint32_t)param3;
    p[3] = 0x29292929;
    return p + 4;
}

// ===========================================================================
// @ 0x004f89a0  (complete; not byte-exact)  local-light vector destructor.
// ===========================================================================
void SkinnerAbility::FUN_004f89a0()
{
    int count = (int)(mChunks.mpEnd - mChunks.mpBegin);
    for (int i = 0; i < count; i++)
        g_pSPMemPool->FUN_009276c0(mChunks.mpBegin[i]);
    mChunks.erase(mChunks.mpBegin, mChunks.mpEnd);
    mpBump = 0;
    mnRemaining = 0;
}

// ===========================================================================
// @ 0x004f8d80  (complete; not byte-exact)  weighted distance sum.
// ===========================================================================
void SkinnerAbility::FUN_004f8d80(int arg1, float* out)
{
    float sum = -mfCost;
    void* table = FUN_004f8f70(arg1);
    if (table != 0) {
        uint32_t n = *(uint32_t*)((char*)table - 8);
        for (uint32_t i = 0; i < n; i++)
            sum += ((AbilityEntry*)((char*)table + (i << 7)))->FUN_004f8e20(arg1);
    }
    *out = sum;
}

// ===========================================================================
// @ 0x004f85b0  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f85b0(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// ===========================================================================
// @ 0x004f8e20  (INCOMPLETE skeleton)
// ===========================================================================
float FUN_004f8e20(int a, void* b)
{
    (void)a; (void)b;
    return 0.0f;
}

// ===========================================================================
// @ 0x004f8f70  (INCOMPLETE skeleton)
// ===========================================================================
void* FUN_004f8f70(int a, int b)
{
    (void)a; (void)b;
    return 0;
}

// ===========================================================================
// @ 0x004f90a0  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f90a0(int a, int b)
{
    (void)a; (void)b;
}

// ===========================================================================
// @ 0x004f9180  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f9180(int a, int b, void* c)
{
    (void)a; (void)b; (void)c;
}

// ===========================================================================
// @ 0x004f9250  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f9250(int a, int b)
{
    (void)a; (void)b;
}

// ===========================================================================
// @ 0x004f9360  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f9360(int a, int b, void* c)
{
    (void)a; (void)b; (void)c;
}
