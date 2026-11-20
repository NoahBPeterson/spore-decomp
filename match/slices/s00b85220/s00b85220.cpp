// Slice s00b85220 -- vector-style single-element insert (retail 0x00b85220).
//
// Modelled from the retail disassembly: a growable array of 24-byte records keeps
// three pointers (begin +0x00, end +0x04, capacity +0x08). Insert(pWhere, pValue)
// shifts the tail right by one element when the array still has spare capacity and
// otherwise reallocates to twice its size, copying the prefix, the new record and
// the suffix into the fresh block.
//
// The record layout comes from the retail copies: id +0x00, three floats +0x04..+0x0c,
// two bytes +0x10/+0x11 and a dword +0x14 (size 0x18).

#include <new>

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f09b4[];

typedef unsigned int  uint32_t;
typedef unsigned char uint8_t;
typedef int           int32_t;

struct tRecord {
    int32_t mId;        // +0x00
    float   m04;        // +0x04
    float   m08;        // +0x08
    float   m0c;        // +0x0c
    uint8_t m10;        // +0x10
    uint8_t m11;        // +0x11
    uint8_t mPad12[2];  // +0x12
    int32_t m14;        // +0x14
};

// Out-of-line callees (original addresses in the comments).
void*     __cdecl FUN_00f473a0(uint32_t nBytes, const char* pszType, int nFlags,
                               int nExtra, const char* pszFile, int nLine); // 0x00f473a0 allocator
void      __cdecl FUN_00f47380(void* pBlock);                               // 0x00f47380 free
tRecord*  __cdecl FUN_00cc8b50(tRecord* pFirst, tRecord* pLast, tRecord* pDest); // 0x00cc8b50 copy_backward
tRecord*  __cdecl FUN_00b7f630(tRecord* pFirst, tRecord* pLast, tRecord* pDest); // 0x00b7f630 uninitialized copy

class cRecordArray {
public:
    tRecord* mpBegin;       // +0x00
    tRecord* mpEnd;         // +0x04
    tRecord* mpCapacity;    // +0x08

    void Insert(tRecord* pWhere, const tRecord* pValue);
};

// @ 0x00b85220
void cRecordArray::Insert(tRecord* pWhere, const tRecord* pValue)
{
    if (mpEnd != mpCapacity) {
        // The value may live inside the range that is about to be shifted.
        const tRecord* pSrc = pValue;
        if (pSrc >= pWhere && pSrc < mpEnd)
            ++pSrc;

        // Copy the last element into the spare slot, member by member, then shift.
        if (mpEnd != 0) {
            tRecord*       pDst  = mpEnd;
            const tRecord* pLast = mpEnd - 1;
            pDst->mId = pLast->mId;
            pDst->m04 = pLast->m04;
            pDst->m08 = pLast->m08;
            pDst->m0c = pLast->m0c;
            pDst->m10 = pLast->m10;
            pDst->m11 = pLast->m11;
            pDst->m14 = pLast->m14;
        }
        FUN_00cc8b50(pWhere, mpEnd - 1, mpEnd);
        *pWhere = *pSrc;
        ++mpEnd;
        return;
    }

    // Grow to twice the current size (one element when the array is empty).
    uint32_t nNew;
    {
        uint32_t nSize = (uint32_t)(mpEnd - mpBegin);
        if (nSize != 0)
            nNew = nSize * 2;
        else
            nNew = 1;
    }

    tRecord* pNewBlock;
    if (nNew != 0)
        pNewBlock = (tRecord*)FUN_00f473a0(nNew * (uint32_t)sizeof(tRecord),
                                          (const char*)g_013f09b4, 0, 0,
                                          (const char*)g_013ebb38, 0xd1);
    else
        pNewBlock = 0;

    // Copy the elements before pWhere, store the new record, then copy the rest.
    tRecord*       pOldBegin = mpBegin;
    tRecord*       pPos      = FUN_00b7f630(pOldBegin, pWhere, pNewBlock);
    if (pPos != 0) {
        const tRecord* pSrc = pValue;
        pPos->mId = pSrc->mId;
        pPos->m04 = pSrc->m04;
        pPos->m08 = pSrc->m08;
        pPos->m0c = pSrc->m0c;
        pPos->m10 = pSrc->m10;
        pPos->m11 = pSrc->m11;
        pPos->m14 = pSrc->m14;
    }
    tRecord*       pOldEnd = mpEnd;
    tRecord*       pNewEnd = FUN_00b7f630(pWhere, pOldEnd, pPos + 1);

    if (mpBegin != 0 && *(uint32_t*)((char*)mpBegin - 4) != 0)
        FUN_00f47380(mpBegin);

    mpEnd = pNewEnd;
    mpBegin = pNewBlock;
    mpCapacity = pNewBlock + nNew;
}
