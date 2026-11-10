// Slice s00899110: assign one 8-byte-record vector into another (alias check, grow
// through 0x00898dc0 with release of the old buffer, then the overlapping move via
// 0x00ac4440 / 0x0076ffd0). Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Unmatched (~14 bytes short). Retail pins the arguments in eax/edx/ecx and the other
// vector in ebp at the very first block and reuses them in both copy blocks below; cl 15
// reloads other->begin/other->end in each block and re-derives the end difference, so
// every copy block's load set and push order differ (including the 0x1c inlined
// 0x76ffd0 argument order). Tried: source ends hoisted into locals before/after the
// grow, in-place vs if/else branch order, u32 arithmetic vs pointer subtraction, and the
// vendored s008997f0 spelling (copy-out then copy-back through UninitCopy8/Copy8/
// SeqCopy8). Growth block still differs in register roles (retail grows on ebx==esi).
#include "types.h"

typedef unsigned int u32;

struct cRecord8 {
    u32 mField00;                               // +0x00
    u32 mField04;                               // +0x04
};
typedef char cRecord8_size_check[(sizeof(cRecord8) == 8) ? 1 : -1];

// The allocator interface reached through the vector's +0x0c member.
struct cRecordAllocator {
    void* m_vtbl;                               // +0x00
};

struct cRecordVector8 {
    cRecord8*         mBegin;                   // +0x00
    cRecord8*         mEnd;                     // +0x04
    cRecord8*         mCapacity;                // +0x08
    cRecordAllocator* mpAllocator;              // +0x0c

    void* Grow(u32 nCount, cRecord8* pFirst, cRecord8* pLast);                        // 0x00898dc0
};

void  __cdecl FUN_00ac4440(void* pResult, const void* pFirst, const void* pLast);  // 0x00ac4440
void  __cdecl FUN_0076ffd0(void* pResult, const void* pFirst, const void* pLast,
                           void* pOutEnd, const void* pValue);                      // 0x0076ffd0

// @ 0x00899110
cRecordVector8* __fastcall FUN_00899110(cRecordVector8* pThis, void* edxUnused, const cRecordVector8* pOther)
{
    (void)edxUnused;
    if (pThis == pOther)
        return pThis;

    cRecord8* pSrcFirst = pOther->mBegin;
    cRecord8* pSrcEnd = pOther->mEnd;
    u32 nOther = (u32)(pSrcEnd - pSrcFirst);
    if (nOther > (u32)(pThis->mEnd - pThis->mBegin)) {
        // the source is longer than what we hold: regrow, release the old buffer, then move
        cRecord8* pNew = (cRecord8*)pThis->Grow(nOther, pSrcFirst, pSrcEnd);
        if (pThis->mBegin != 0) {
            cRecord8* pOldEnd = pThis->mEnd;
            u32 nUsed = (u32)(pOldEnd - pThis->mBegin);
            void** vtbl = *(void***)pThis->mpAllocator;
            ((void (__thiscall*)(cRecordAllocator*, cRecord8*, u32))vtbl[0x0c / 4])(
                pThis->mpAllocator, pThis->mBegin, nUsed * 8);
        }
        pThis->mBegin = pNew;
        pThis->mEnd = pNew + nOther * 8;
        pThis->mCapacity = pNew + nOther * 8;
        return pThis;
    }

    u32 nFree = (u32)(pThis->mCapacity - pThis->mEnd);
    if (nOther > nFree) {
        // the room after the end is too small: move the tail into the new buffer, then fill
        FUN_00ac4440(pSrcFirst, pThis->mBegin, pThis->mBegin + nFree);
        cRecord8* pDst = pThis->mEnd;
        FUN_0076ffd0(0, pThis->mBegin, pThis->mCapacity, pDst + nOther, 0);
    } else {
        FUN_00ac4440(pSrcFirst, pThis->mBegin, pThis->mBegin + nOther);
    }
    pThis->mEnd = pThis->mBegin + (u32)(pThis->mEnd - pThis->mBegin) + nOther;
    return pThis;
}
