// Slice s008991f0: insert a range of 0x20-byte records into a vector, growing it when needed.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int u32;

struct cRecord20 {
    u32 mField00;                               // +0x00
    u32 mField04;                               // +0x04
    u32 mField08;                               // +0x08
    u32 mField0c;                               // +0x0c
    u32 mField10;                               // +0x10
    u32 mField14;                               // +0x14
    u32 mField18;                               // +0x18
    u32 mField1c;                               // +0x1c
};
typedef char cRecord20_size_check[(sizeof(cRecord20) == 0x20) ? 1 : -1];

// The allocator interface reached through the vector's +0x0c member.
struct cRecordAllocator {
    void* m_vtbl;                               // +0x00
    void* mField04;                             // +0x04
    void* mField08;                             // +0x08
    void* mField0c;                             // +0x0c
    void* mField10;                             // +0x10
};

struct cRecordVector {
    cRecord20*      mBegin;                     // +0x00
    cRecord20*      mEnd;                       // +0x04
    cRecord20*      mCapacity;                  // +0x08
    cRecordAllocator* mpAllocator;              // +0x0c
    u32             mField10;                   // +0x10

    cRecordVector* Grow(u32 nCount, cRecord20* pFirst, cRecord20* pLast);  // 0x00898e10
};

void __cdecl FUN_00c06600(cRecord20* pDst, cRecord20* pFirst, cRecord20* pLast);     // 0x00c06600
void* __cdecl FUN_00c04920(cRecord20* pDst, cRecord20* pFirst, cRecord20* pLast, cRecord20* pDstEnd);  // 0x00c04920

// @ 0x008991f0
cRecordVector* __fastcall FUN_008991f0(cRecordVector* pThis, void* edxUnused, const cRecordVector* pOther)
{
    (void)edxUnused;
    if (pThis == pOther)
        return pThis;

    u32 nOther = (u32)(pOther->mEnd - pOther->mBegin);
    if (nOther > (u32)(pThis->mEnd - pThis->mBegin)) {
        // the new range does not fit: allocate a new buffer, release the old one and swap it in
        u32 nGrown = (u32)pThis->Grow(nOther, pOther->mBegin, pOther->mEnd);
        if (pThis->mBegin != 0) {
            u32 nUsed = (u32)(pThis->mEnd - pThis->mBegin);
            void** vtbl = *(void***)pThis->mpAllocator;
            ((void (__thiscall*)(cRecordAllocator*, cRecord20*, u32))vtbl[0x0c / 4])(
                pThis->mpAllocator, pThis->mBegin, nUsed * 0x20);
        }
        u32 nNewEnd = nGrown + nOther * 0x20;
        u32 nNewCap = nGrown + nOther * 0x20;
        pThis->mBegin = (cRecord20*)nGrown;
        pThis->mCapacity = (cRecord20*)nNewCap;
        pThis->mEnd = (cRecord20*)nNewEnd;
        return pThis;
    }

    u32 nFree = (u32)(pThis->mCapacity - pThis->mEnd);
    if (nOther > nFree) {
        // the room after the end is too small: shift the tail up by the shortfall, then append
        u32 nShift = nOther - nFree;
        FUN_00c06600(pThis->mEnd, pThis->mBegin, pOther->mEnd);
        FUN_00c04920(pThis->mEnd, pThis->mBegin, pOther->mEnd, pThis->mBegin + nShift);
    } else {
        FUN_00c04920(pThis->mEnd, pThis->mBegin, pOther->mEnd, pThis->mEnd);
    }
    pThis->mEnd = pThis->mBegin + (u32)(pThis->mEnd - pThis->mBegin) + nOther;
    return pThis;
}
