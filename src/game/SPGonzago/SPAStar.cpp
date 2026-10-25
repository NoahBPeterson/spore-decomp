// src/game/SPGonzago/SPAStar.cpp -- migrated from slice(s) s006755c0, s005718f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAStar.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Stopwatch.h"
#include "EA/Variant.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);
#include <new>
#include <string.h>
#include <math.h>
#include <intrin.h>

// ---- items of slice s005718f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);
namespace EA {
class Stopwatch_s0057_18f0 {
public:
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    void Restart();  // 0x00571e80 (EA::Stopwatch::Restart)
};
}
namespace EA {
static inline uint64_t GetStopwatchCycleInline()
{
    int64_t t;
    QueryPerformanceCounter(&t);
    return (uint64_t)t;
}
}
// ---- items of slice s005718f0 end

// ---- items of slice s006755c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gpEmptyBucketArray[2];   // 0x0154DF28
extern wchar_t gEmptyString16[];       // 0x01667BAC  eastl::gEmptyString16
extern char    g_bWriteTypeAttribute;  // 0x015D8B51
void EAFree(void* p);                                                            // 0x00F47380
void* EAAllocate(unsigned int n, const char* name, int a, int b, const char* file, int line); // 0x00F473A0
static const char* const kpEditorAllocName = (const char*)0x013EB430;   // ?kEditorAllocName@@3QBDB
static const char* const kpEastlAllocatorFile = (const char*)0x013EBB38; // ".../EASTL/allocator.h"
struct HashInsertResult {
    void* mpNode;     // +0x00
    void* mpBucket;   // +0x04
    char  mbInserted; // +0x08
};
struct RehashResult {
    char     mbNeedsRehash;  // +0x00
    uint32_t mnNewCount;     // +0x04
};
struct PrimeRehashPolicy {
    // (out, nBucketCount, nElementCount, nMinBuckets) - out is the first stack slot.
    void GetNextBucketCount(RehashResult* pOut, uint32_t nBucketCount, uint32_t nElemCount,
                            int nMinBuckets);           // 0x00921440
};
struct UIntHashTable {
    char     mPad00[4];       // +0x00  use_first/equal_to/hash/mod_range_hashing
    void**   mpBucketArray;   // +0x04
    uint32_t mnBucketCount;   // +0x08
    uint32_t mnElementCount;  // +0x0c
    float    mfMaxLoadFactor; // +0x10
    float    mfGrowthFactor;  // +0x14
    uint32_t mnNextResize;    // +0x18
    char     mAllocator[4];   // +0x1c

    void DoFreeNodes(void** pNodeArray, uint32_t n);   // 0x006B6570
    void rehash(uint32_t nNewBucketCount);             // 0x00675650
    // Returns pResult (the original leaves it in eax) - 0x006758A0
    HashInsertResult* DoInsertValue(HashInsertResult* pResult, const uint32_t* pKey, bool bHint);

    // eastl::hashtable default construction (the allocator member is left as-is).
    void init()
    {
        mfMaxLoadFactor = 1.0f;
        mfGrowthFactor  = 2.0f;
        mnElementCount  = 0;
        mnNextResize    = 0;
        mnBucketCount   = 1;
        mpBucketArray   = &gpEmptyBucketArray[0];
    }

    void reset()
    {
        mnBucketCount  = 1;
        mpBucketArray  = &gpEmptyBucketArray[0];
        mnElementCount = 0;
        mnNextResize   = 0;
    }
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    ~UIntHashTable()
    {
        clear();
        if (mnBucketCount > 1)
            EAFree(mpBucketArray);
    }
};
struct IPropStream {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
    virtual void* GetStream();                                 // +0x18
};
struct IPropWriter {
    virtual bool Begin(const wchar_t* pName);                  // +0x00
    virtual bool End(const wchar_t* pName);                    // +0x04
    virtual bool Attr(const wchar_t* pName, const wchar_t* pValue);  // +0x08
    virtual bool Text(const wchar_t* pText);                   // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void NextEntry();                                  // +0x1c
    virtual IPropStream* GetWriter();                          // +0x20
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual bool ReadProp(void* pData, int nSize);             // +0x38
};
struct Elem16;
Elem16*   __cdecl UninitialisedCopy16(Elem16* pFirst, Elem16* pLast, Elem16* pDest);             // 0x00C7EA30
void      __cdecl CopyBackward16(Elem16* pFirst, Elem16* pLast, Elem16* pDest);                  // 0x00EDBA80
struct Elem16 {
    uint32_t m0;   // +0x00
    uint32_t m4;   // +0x04
    uint32_t m8;   // +0x08
    uint32_t mC;   // +0x0c
};
struct Elem16Vec {
    Elem16* mpBegin;   // +0x00
    Elem16* mpEnd;     // +0x04
    Elem16* mpCap;     // +0x08
    Elem16* insert(Elem16* pPos, const Elem16* pValue);            // 0x00676370
    void    DoInsertValue(Elem16* pPos, const Elem16* pValue);     // 0x00675B90
};
struct TWString {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08
    int      mAlloc;    // +0x0c
    TWString* Clone(const TWString* pOther);          // 0x0056E2D0 (copy ctor)
    void      RangeInitialize(const wchar_t* pFirst); // 0x00579A90
    // eastl::basic_string destructor: release everything but the shared empty buffer.
    void Release()
    {
        if ((unsigned)((char*)mpCap - (char*)mpBegin) > 2 && mpBegin != 0)
            EAFree(mpBegin);
    }
};
TWString* __cdecl ConvertToString16W(TWString* pOut, const char* pSrc, int nLen);          // 0x0093C5A0
TWString* __cdecl ConvertToString16FromW(TWString* pOut, const TWString* pSrc);             // 0x0093C6D0
void      __cdecl TypedValueToString16(TWString* pOut, const void* pValue);                 // 0x00694F00
bool __cdecl FUN_00675990(IPropWriter* pWriter, const char* pText, const void* pValue,
                          const wchar_t* pType);
// ---- items of slice s006755c0 end

// @ 0x00571e80
namespace EA {
void Stopwatch_s0057_18f0::Restart()
{
    if (mnUnits == 1)
        mnStartTime = __rdtsc();
    else
        mnStartTime = GetStopwatchCycleInline();
    mnTotalElapsedTime = 0;
}
}  // namespace EA

// @ 0x006758a0
HashInsertResult* UIntHashTable::DoInsertValue(HashInsertResult* pResult, const uint32_t* pKey, bool)
{
    uint32_t nKey         = *pKey;
    uint32_t nBucketCount = mnBucketCount;
    uint32_t nIndex       = nKey % nBucketCount;
    uint32_t** ppBucket   = (uint32_t**)mpBucketArray + nIndex;
    uint32_t* pNode       = *ppBucket;
    while (pNode != 0) {
        if (pNode[0] == nKey) {
            pResult->mpNode     = pNode;
            pResult->mpBucket   = ppBucket;
            pResult->mbInserted = 0;
            return pResult;    // the original leaves the insert result in eax
        }
        pNode = (uint32_t*)pNode[1];
    }

    RehashResult rehashResult;
    ((PrimeRehashPolicy*)(void*)((char*)this + 0x10))->GetNextBucketCount(&rehashResult, nBucketCount, mnElementCount, 1);

    uint32_t* pNew = (uint32_t*)EAAllocate(8, kpEditorAllocName, 0, 0, kpEastlAllocatorFile, 0xd1);
    if (pNew != 0)
        pNew[0] = nKey;
    pNew[1] = 0;

    if (rehashResult.mbNeedsRehash != 0) {
        nIndex = nKey % rehashResult.mnNewCount;
        rehash(rehashResult.mnNewCount);
    }

    uint32_t** ppBase = (uint32_t**)mpBucketArray;
    pNew[1]           = (uint32_t)ppBase[nIndex];
    ppBase[nIndex]    = pNew;
    ++mnElementCount;

    pResult->mpNode     = pNew;
    pResult->mpBucket   = &ppBase[nIndex];
    pResult->mbInserted = 1;
    return pResult;
}

// @ 0x00675990
bool __cdecl FUN_00675990(IPropWriter* pWriter, const char* pText, const void* pValue, const wchar_t* pType)
{
    TWString strValue;                                  // formatted value
    strValue.mpBegin = gEmptyString16;                  // the retail empty-string triple: the capacity
    strValue.mpEnd   = gEmptyString16;                  //   sentinel sits one *byte* past the buffer
    strValue.mpCap   = (wchar_t*)((char*)gEmptyString16 + 1);
    strValue.mAlloc  = 0;
    TypedValueToString16(&strValue, pValue);
    if (strValue.mpBegin == strValue.mpEnd) {
        strValue.Release();
        return true;
    }

    // Entry name: widen the caller's text into a temporary, then copy-construct the real string.
    TWString strTemp;
    if (pText != 0) {
        ConvertToString16W(&strTemp, pText, -1);
    } else {
        strTemp.mpBegin = gEmptyString16;
        strTemp.mpEnd   = gEmptyString16;
        strTemp.mpCap   = gEmptyString16 + 1;
        strTemp.mAlloc  = 0;
    }
    TWString strName;
    strName.Clone(&strTemp);
    strTemp.Release();

    TWString strText;                                   // entry text: the formatted value
    ConvertToString16FromW(&strText, &strValue);

    // Every writer call is folded back to 0/1, like the original's explicit setne/xor pairs.
    bool bResult;
    if (strName.mpBegin == strName.mpEnd) {
        bResult = pWriter->Begin(pType) != 0;
    } else {
        bResult = pWriter->Begin(strName.mpBegin) != 0;
        if (bResult && g_bWriteTypeAttribute != 0)
            bResult = pWriter->Attr(L"type", pType) != 0;
    }
    if (bResult)
        bResult = pWriter->Text(strText.mpBegin) != 0;
    if (bResult)
        bResult = pWriter->End((strName.mpBegin == strName.mpEnd) ? pType : strName.mpBegin) != 0;

    strText.Release();
    strName.Release();
    strValue.Release();
    return bResult;
}

// @ 0x00675b90
void Elem16Vec::DoInsertValue(Elem16* pPos, const Elem16* pValue)
{
    if (mpEnd != mpCap) {
        Elem16*       pLast = mpEnd;
        const Elem16* pSrc  = pValue;
        if ((unsigned)pSrc >= (unsigned)pPos && (unsigned)pSrc < (unsigned)mpEnd)
            ++pSrc;
        if (pLast != 0)
            *pLast = *(mpEnd - 1);
        CopyBackward16(pPos, mpEnd - 1, mpEnd);
        *pPos = *pSrc;
        ++mpEnd;
        return;
    }

    unsigned nSize = (unsigned)(mpEnd - mpBegin);
    unsigned nNewSize = (nSize != 0) ? nSize * 2 : 1;
    Elem16*  pNewBegin = 0;
    if (nNewSize != 0)
        pNewBegin = (Elem16*)EAAllocate(nNewSize * 0x10, kpEditorAllocName, 0, 0,
                                        kpEastlAllocatorFile, 0xd1);

    Elem16* pMid = UninitialisedCopy16(mpBegin, pPos, pNewBegin);
    if (pMid != 0)
        *pMid = *pValue;
    Elem16* pNewEnd = UninitialisedCopy16(pPos, mpEnd, pMid + 1);

    if (mpBegin != 0)
        EAFree(mpBegin);
    mpEnd   = pNewEnd;
    mpCap   = pNewBegin + nNewSize;
    mpBegin = pNewBegin;
}
