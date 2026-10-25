// Slice s00b84270 (gold7): Simulator-side eastl vector helpers and the
// cModelTestCheat terrain-box rebuild.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc).
#include <new>
#include "types.h"

#define ALLOC_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

void* __cdecl operator_new_eastl(unsigned int size, const char* name, int flags, int align,
                                 const char* file, int line);   // 0x00f473a0
void __cdecl operator_delete_eastl(void* p);                    // 0x00f47380
void* __cdecl MemCpy(void* dst, const void* src, unsigned int n);  // 0x011e0744

// ---------------------------------------------------------------------------
// eastl::vector<uint16_t> -- three pointers followed by the allocator pair.
// ---------------------------------------------------------------------------
struct U16Vec {
    uint16_t* mpBegin;      // +0x00
    uint16_t* mpEnd;        // +0x04
    uint16_t* mpCapacity;   // +0x08
    int mAllocator[2];      // +0x0c

    void Reserve(unsigned int n);
};

// ---------------------------------------------------------------------------
// @ 0x00b849e0  U16Vec::Reserve
// ---------------------------------------------------------------------------
void U16Vec::Reserve(unsigned int n)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        uint16_t* pNew = n
            ? (uint16_t*)operator_new_eastl(n * 2, "Simulator", 0, 0, ALLOC_FILE, 0xd1)
            : 0;
        MemCpy(pNew, mpBegin, (uint32_t)((char*)mpEnd - (char*)mpBegin));
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
            operator_delete_eastl(mpBegin);
        uint16_t* pNewEnd = pNew + (mpEnd - mpBegin);
        uint16_t* pNewCap = pNew + n;
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNewCap;
    }
}

// ---------------------------------------------------------------------------
// 0x1c-byte records produced by the boundary-vector initialisation helpers.
// ---------------------------------------------------------------------------
struct Vec14 {
    void* mpBegin;     // +0x00
    void* mpEnd;       // +0x04
    void* mpCapacity;  // +0x08
    int   mAllocator[2];

    void Copy(const Vec14& other);   // 0x00473460
};

struct Elem1C {
    uint32_t mA;    // +0x00
    uint32_t mB;    // +0x04
    Vec14    mVec;  // +0x08
};

// ---------------------------------------------------------------------------
// @ 0x00b850c0  uninitialised copy of 0x1c-byte records
// ---------------------------------------------------------------------------
Elem1C* UninitCopy1C(const Elem1C* first, const Elem1C* last, Elem1C* dst)
{
    while (first != last) {
        if (dst) {
            dst->mA = first->mA;
            dst->mB = first->mB;
            dst->mVec.Copy(first->mVec);
        }
        first += 1;
        dst += 1;
    }
    return dst;
}

// ---------------------------------------------------------------------------
// ScalarList: the cModelTestCheat helper owning two vector<vector<int>> members
// (+0x0c, +0x20) and a vector<int> (+0x34), plus an owned object at +0x08.
// ---------------------------------------------------------------------------
struct IntVector {
    uint32_t* mpBegin;      // +0x00
    uint32_t* mpEnd;        // +0x04
    uint32_t* mpCapacity;   // +0x08
    int mAllocator[2];      // +0x0c

    void Free()
    {
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
            operator_delete_eastl(mpBegin);
    }

    ~IntVector() { Free(); }
};

struct IntVectorVec {
    IntVector* mpBegin;      // +0x00
    IntVector* mpEnd;        // +0x04
    IntVector* mpCapacity;   // +0x08
    int mAllocator[2];       // +0x0c

    void DestroyRange(void* first, void* last);   // 0x01023030

    ~IntVectorVec()
    {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
            operator_delete_eastl(mpBegin);
    }
};

struct EventModifier {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};

extern char kEventModifierVtbl;   // 0x013ef094

struct ScalarList {
    void* mpVtbl;            // +0x00
    int   m04;               // +0x04
    EventModifier* mp08;     // +0x08
    IntVectorVec mVec0c;     // +0x0c
    IntVectorVec mVec20;     // +0x20
    IntVector mVec34;        // +0x34

    void Dtor();
};

// ---------------------------------------------------------------------------
// @ 0x00b85110  ScalarList::Dtor
// ---------------------------------------------------------------------------
void ScalarList::Dtor()
{
    mVec34.~IntVector();
    mVec20.~IntVectorVec();
    mVec0c.~IntVectorVec();
    if (mp08)
        mp08->s2();
    mpVtbl = &kEventModifierVtbl;
}
