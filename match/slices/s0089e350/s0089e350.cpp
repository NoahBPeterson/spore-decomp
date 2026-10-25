#include "types.h"
#include <string.h>

// EA::Text::GetCharCategory -- EATextUnicode.cpp (EA EAText / EAIO)
namespace EA { namespace Text {

typedef wchar_t Char;

enum CharCategory { };

struct CharCategoryInfo
{
    uint16_t mCode;         // starting code of the range
    uint8_t  mCharClass0;   // character class for 0 bits
    uint8_t  mCharClass1;   // character class for 1 bits
    uint8_t* mpBitMask;     // bitmask (can be NULL)
};

struct CharCategoryLess
{
    bool operator()(const CharCategoryInfo& a, const CharCategoryInfo& b) const
        { return a.mCode < b.mCode; }
};

extern CharCategoryInfo gCharCategoryTable[779];   // 0x0154a1a0 .. 0x0154b9f8

template <typename RandomAccessIterator, typename T, typename Compare>
RandomAccessIterator upper_bound(RandomAccessIterator first, RandomAccessIterator last,
                                 const T& value, Compare compare);   // 0x0089e5a0

// @ 0x0089e5e0
CharCategory GetCharCategory(Char nChar)
{
    const size_t           kCCTableSize = sizeof(gCharCategoryTable) / sizeof(gCharCategoryTable[0]);
    const CharCategoryInfo cciTemp      = { nChar, 0, 0, 0 };

    const CharCategoryInfo* const pCC = (EA::Text::upper_bound(gCharCategoryTable, gCharCategoryTable + kCCTableSize, cciTemp, CharCategoryLess()) - 1);

    if(pCC->mpBitMask == 0)
        return (CharCategory)pCC->mCharClass0;

    const int nBitIndex = nChar - pCC->mCode;
    return (CharCategory)((pCC->mpBitMask[nBitIndex >> 3] & (1 << (nBitIndex & 7))) ? pCC->mCharClass1 : pCC->mCharClass0);
}

}} // namespace EA::Text

// ---------------------------------------------------------------------------
// EA::Text::OTF foothold types (OpenType table reader, EATextOpenType.cpp)
// ---------------------------------------------------------------------------

namespace EA { namespace IO {

typedef uint32_t size_type;
enum Endian { kEndianBig = 0, kEndianLittle = 1 };

class IStream;

// @ 0x0093a700
bool ReadUint16(IStream* pIS, uint16_t* pValue, size_type nCount, Endian endianSource);

}}

namespace EA { namespace Text {

// 0x0154... OpenType structures touched by OTFScriptList::GetLangSys.
struct OTFLangSys
{
    uint16_t mLookupOrder;          // +0x00
    uint16_t mRequiredFeatureIndex; // +0x02
    uint16_t mFeatureIndexCount;    // +0x04
};

// 0x14-byte entry of a script's language-system record array.
struct OTFLangSysEntry
{
    uint32_t   mLangSysTag;         // +0x00
    uint32_t   mPad04;              // +0x04
    OTFLangSys mLangSys;            // +0x08
    uint8_t    mPad0e[6];           // +0x0e
};

// 0x1c-byte script entry.
struct OTFScript
{
    uint32_t            mScriptTag;             // +0x00
    uint32_t            mPad04;                 // +0x04
    OTFLangSys          mDefaultLangSys;        // +0x08
    uint32_t            mPad10;                 // +0x10
    uint16_t            mLangSysRecordCount;    // +0x14
    uint16_t            mPad16;                 // +0x16
    OTFLangSysEntry*    mpLangSysRecordArray;   // +0x18
};

struct OTFScriptList
{
    uint16_t    mPad00;             // +0x00
    uint16_t    mScriptCount;       // +0x02
    OTFScript*  mpScriptArray;      // +0x04

    // GetLangSys (definition below)
    OTFLangSys* GetLangSys(uint32_t* pScriptTag, uint32_t* pLangSysTag, bool bDefault);
};

}} // namespace EA::Text

// ---------------------------------------------------------------------------
// EA::Allocator::StackAllocator -- bump allocator the OTF readers carve from.
// ---------------------------------------------------------------------------

namespace EA { namespace Allocator {

class StackAllocator
{
public:
    size_t  mnDefaultBlockSize;     // +0x00
    void*   mpCurrentBlock;         // +0x04
    char*   mpCurrentBlockEnd;      // +0x08
    char*   mpCurrentObjectBegin;   // +0x0c
    char*   mpCurrentObjectEnd;     // +0x10

    // AllocateNewBlock @ 0x00928ba0
    bool AllocateNewBlock(size_t nSize);
};

// StackAllocator::Malloc -- bump-allocates nSize bytes (already rounded) and
// returns the block, or NULL when the block request fails.
inline uint32_t* MallocBlock(StackAllocator* pAllocator, size_t nSize)
{
    if ((intptr_t)pAllocator->mpCurrentBlockEnd
        - ((intptr_t)pAllocator->mpCurrentObjectBegin + (intptr_t)nSize) < 0)
    {
        if (!pAllocator->AllocateNewBlock(nSize))
            return (uint32_t*)0;
    }

    uint32_t* p = (uint32_t*)pAllocator->mpCurrentObjectBegin;
    pAllocator->mpCurrentObjectBegin = (char*)p + nSize;
    pAllocator->mpCurrentObjectEnd   = pAllocator->mpCurrentObjectBegin;
    return p;
}

// @ 0x0089f0d0 .. 0x0089f2a0
// EA::Allocator::create_array<T>: free cdecl function.  Reserves
// sizeof(uint32_t) + sizeof(T)*count bytes (rounded up to 8) from the bump
// allocator, stores the element count in the leading word and returns the
// element block.  Element constructors are NOT run.
template <typename T>
inline T* create_array(StackAllocator* pAllocator, uint32_t nCount)
{
    const size_t nSize = (sizeof(uint32_t) + sizeof(T) * nCount + 7) & ~(size_t)7;

    uint32_t* const p = MallocBlock(pAllocator, nSize);
    *p = nCount;
    return (T*)(p + 1);
}

}} // namespace EA::Allocator

// Storage-only tag types for the create_array instantiations; only sizeof()
// participates in the generated code.
namespace EA { namespace Text {

struct OTFLangSysRecord      { uint16_t mValue; };                                          // 2
struct OTFLookup             { uint16_t mLookupType; uint16_t mLookupFlag; uint16_t mSubTableCount; }; // 6
struct OTFLookupSubTableGsub { uint8_t  mData[0x1c]; };                                     // 28
struct OTFLigature           { uint16_t mLigGlyph; uint16_t mComponentCount; uint16_t mComponents[2]; }; // 8
struct OTFClassRule          { uint8_t  mData[0x10]; };                                     // 16
struct OTFChainClassRule     { uint8_t  mData[0x20]; };                                     // 32

}} // namespace EA::Text

namespace EA { namespace Allocator {

template EA::Text::OTFLangSysRecord*      create_array<EA::Text::OTFLangSysRecord>(StackAllocator*, uint32_t);      // @ 0x0089f0d0
template EA::Text::OTFLookup*             create_array<EA::Text::OTFLookup>(StackAllocator*, uint32_t);             // @ 0x0089f120
template EA::Text::OTFLookupSubTableGsub* create_array<EA::Text::OTFLookupSubTableGsub>(StackAllocator*, uint32_t); // @ 0x0089f170
template EA::Text::OTFLigature*           create_array<EA::Text::OTFLigature>(StackAllocator*, uint32_t);           // @ 0x0089f1d0
template EA::Text::OTFClassRule*          create_array<EA::Text::OTFClassRule>(StackAllocator*, uint32_t);          // @ 0x0089f220
template EA::Text::OTFChainClassRule*     create_array<EA::Text::OTFChainClassRule>(StackAllocator*, uint32_t);     // @ 0x0089f270

}} // namespace EA::Allocator

namespace EA { namespace Text {

// (no PDB name; member of EA::Text::OTF -- neighbours SetAllocator/ReadTableDirectory)
class OTF
{
public:
    uint8_t         mPad000[0x134];
    EA::IO::IStream* mpStream;      // +0x134

    // ReadUint16 @ 0x0089ed70  (no PDB name)
    bool ReadUint16(uint16_t* pValue);
};

// @ 0x0089ed70
bool OTF::ReadUint16(uint16_t* pValue)
{
    return EA::IO::ReadUint16(mpStream, pValue, 1, EA::IO::kEndianBig);
}

// @ 0x0089f000
OTFLangSys* OTFScriptList::GetLangSys(uint32_t* pScriptTag, uint32_t* pLangSysTag, bool bDefault)
{
    const uint32_t kScriptTagDefault = 0x44464c54;   // 'TLFD' as stored in memory

    uint32_t   i              = 0;
    OTFScript* pDefaultScript = 0;

    for (; i < mScriptCount; ++i)
    {
        OTFScript* const pScript = &mpScriptArray[i];

        if (pScript->mScriptTag == kScriptTagDefault)
            pDefaultScript = pScript;

        if (pScript->mScriptTag != *pScriptTag)
            continue;

        if (*pLangSysTag != 0)
        {
            for (uint32_t j = 0; j < pScript->mLangSysRecordCount; ++j)
            {
                if (pScript->mpLangSysRecordArray[j].mLangSysTag == *pLangSysTag)
                    return &pScript->mpLangSysRecordArray[j].mLangSys;
            }
        }
        return &pScript->mDefaultLangSys;
    }

    if (bDefault)
        return 0;

    if (pDefaultScript == 0)
        pDefaultScript = mpScriptArray;

    if (*pLangSysTag != 0)
    {
        for (i = 0; i < pDefaultScript->mLangSysRecordCount; ++i)
        {
            if (pDefaultScript->mpLangSysRecordArray[i].mLangSysTag == *pLangSysTag)
                return &pDefaultScript->mpLangSysRecordArray[i].mLangSys;
        }
    }
    return &pDefaultScript->mDefaultLangSys;
}

// ---------------------------------------------------------------------------
// Bidirectional algorithm (EATextUnicode.cpp)
// ---------------------------------------------------------------------------

// 0xc-byte bidi run record.  Bits 12..15 of mLevel hold the explicit embedding
// level, bits 7..11 the resolved level.
struct BidiRecord
{
    uint32_t mValue0;   // +0x00
    uint32_t mValue1;   // +0x04
    uint32_t mLevel;    // +0x08
};

// Weak / neutral state-machine tables (read-only .rdata).
extern const uint32_t gWeakStateActionTable[];   // 0x0142f670
extern const uint32_t gWeakStateTable[];         // 0x0142f990
extern const uint32_t gWeakFinalActionTable[];   // 0x0142f994

extern const uint32_t gNeutralStateActionTable[]; // 0x0142fcb0
extern const uint32_t gNeutralStateTable[];       // 0x0142fd28
extern const uint32_t gNeutralFinalActionTable[]; // 0x0142fd2c

// @ 0x0089e740
uint32_t BidiResolveExplicitImpl(uint32_t level, BidiRecord* pRecords, uint32_t count,
                                 int dir, int nesting)
{
    uint32_t i     = 0;
    uint32_t bound = count;

    if (count != 0)
    {
        do
        {
            BidiRecord* const pRecord   = &pRecords[i];
            uint32_t          w         = pRecord->mLevel;
            int               bidiClass = ((int)(w << 20)) >> 27;

            uint32_t newBound = count;              // bound for the next iteration
            uint32_t limit    = count;              // loop limit for the next iteration

            switch (bidiClass)
            {
            case 0xe:
            case 0xf:
                {
                    const uint32_t newLevel = ((level + 1) & ~(uint32_t)1) + 1;
                    ++nesting;
                    if ((int)newLevel > 0xf)
                    {
                        pRecord->mLevel = (w & 0xfffff57f) | 0x500;
                        bidiClass       = 10;
                        break;
                    }
                    pRecord->mLevel = (uint32_t)((newLevel & 0xf) << 12)
                                    | (w & 0xffff057f) | 0x500;
                    i += BidiResolveExplicitImpl(newLevel, pRecord + 1, count - i - 1,
                                                 -(bidiClass != 0xf) & 2, nesting + 1);
                    --nesting;
                    newBound = count;
                }
                break;

            case 0x10:
            case 0x11:
                {
                    const uint32_t newLevel = (level + 2) & ~(uint32_t)1;
                    ++nesting;
                    if ((int)newLevel > 0xf)
                    {
                        pRecord->mLevel = (w & 0xfffff57f) | 0x500;
                        bidiClass       = 10;
                        break;
                    }
                    pRecord->mLevel = (uint32_t)((level + 2 & 0xe) << 12)
                                    | (w & 0xffff057f) | 0x500;
                    i += BidiResolveExplicitImpl(newLevel, pRecord + 1, count - i - 1,
                                                 bidiClass != 0x11, nesting + 1);
                    --nesting;
                    newBound = count;
                }
                break;

            case 0x12:
                pRecord->mLevel = (w & 0xfffff57f) | 0x500;
                bidiClass       = 10;
                if (nesting > 0)
                {
                    newBound = i;
                    limit    = i;
                    if ((int)count > nesting)
                    {
                        --nesting;
                        newBound = bound;
                        limit    = count;
                    }
                }
                break;

            default:
                break;
            }

            count = limit;

            pRecord->mLevel ^= (uint32_t)(level << 12 ^ pRecord->mLevel) & 0xf000;
            {
                const uint32_t lvl = pRecord->mLevel;
                if (dir != 0)
                    bidiClass = dir;
                if ((lvl & 0xf80) != 0x500)
                    pRecord->mLevel = (uint32_t)(bidiClass << 7 ^ lvl) & 0xf80 ^ lvl;
            }

            ++i;
            bound = newBound;
        } while (i < bound);
    }
    return i;
}

// @ 0x0089e8e0
void BidiResolveWeak(uint32_t level, BidiRecord* pRecords, uint32_t count)
{
    int      state    = 2 - (int)((level & 1) != 0);
    int      runLen   = 0;
    uint32_t curLevel = 0;
    uint32_t i        = 0;
    uint32_t uLevel   = level;

    if (count != 0)
    {
        uint32_t* pLevel = &pRecords[0].mLevel;
        do
        {
            uint32_t w         = *pLevel;
            uint32_t prevLevel = uLevel;

            if ((w & 0xf80) == 0x500)
            {
                w = (uint32_t)(uLevel << 12 ^ w) & 0xf000 ^ w;
                *pLevel = w;

                if (runLen + 1 == (int)count && uLevel != level)
                {
                    uint32_t t = uLevel & 0x80000001;
                    if ((int)t < 0)
                        t = (t - 1 | 0xfffffffe) + 1;
                    *pLevel = (uint32_t)(((t + 1) * 0x80) ^ w) & 0xf80 ^ w;
                    state   = (((int)(*pLevel << 20)) >> 27) + state * 10;
                    goto doState;
                }
                if (runLen + 1 < (int)count)
                {
                    prevLevel = (uint32_t)((int)(pLevel[3] << 0x10) >> 0x1c);
                    if (uLevel != prevLevel && (pLevel[3] & 0xf80) != 0x500)
                    {
                        uint32_t hi = prevLevel;
                        if ((int)prevLevel < (int)uLevel)
                            hi = uLevel;
                        uint32_t t = hi & 0x80000001;
                        if ((int)t < 0)
                            t = (t - 1 | 0xfffffffe) + 1;
                        *pLevel = (uint32_t)(((t + 1) & 0x1f) << 7)
                                | (uint32_t)((hi & 0xf) << 12) | (w & 0xffff007f);
                        goto afterState;
                    }
                }
                if (curLevel != 0)
                    ++curLevel;
                goto afterState;
            }

            state = (int)((*pLevel << 0x14) >> 0x1b) + state * 10;

        doState:
            {
                uint32_t action = gWeakStateActionTable[state];
                uint32_t act    = (uint32_t)((int)action >> 4) & 0xf;
                if (act != 0xf)
                {
                    uint32_t* p    = (uint32_t*)((char*)pRecords + (i - curLevel) * 0xc);
                    uint32_t* pEnd = (uint32_t*)((char*)p + curLevel * 0xc);
                    if (p != pEnd)
                    {
                        do
                        {
                            p[2] = p[2] & 0xfffff07f | act << 7;
                            p    = (uint32_t*)((char*)p + 0xc);
                        } while (p != pEnd);
                    }
                    curLevel = 0;
                }
                if ((action & 0xf) != 0xf)
                    *pLevel = *pLevel ^ ((action & 0xf) << 7 ^ *pLevel) & 0xf80;
                if ((action & 0x100) != 0)
                    ++curLevel;
                state  = (int)gWeakStateTable[state];
                uLevel = prevLevel;
            }

        afterState:
            ++i;
            pLevel += 3;
        } while (i < count);
    }

    {
        uint32_t t = uLevel & 0x80000001;
        if ((int)t < 0)
            t = (t - 1 | 0xfffffffe) + 1;
        uint32_t act = (uint32_t)((int)gWeakFinalActionTable[t + state * 10] >> 4) & 0xf;
        if (act != 0xf)
        {
            uint32_t* p    = (uint32_t*)((char*)pRecords + (i - curLevel) * 0xc);
            uint32_t* pEnd = (uint32_t*)((char*)p + curLevel * 0xc);
            if (p != pEnd)
            {
                do
                {
                    p[2] = p[2] & 0xfffff07f | act << 7;
                    p    = (uint32_t*)((char*)p + 0xc);
                } while (p != pEnd);
            }
        }
    }
}

// @ 0x0089eb00
void BidiResolveNeutral(uint32_t level, BidiRecord* pRecords, uint32_t count)
{
    int      runLen = 0;
    uint32_t i      = 0;
    uint32_t dir    = ~level & 1;
    uint32_t uLevel = level;

    if (count != 0)
    {
        uint32_t* pLevel = &pRecords[0].mLevel;
        do
        {
            int cls = ((int)(*pLevel << 0x14)) >> 0x1b;

            if (cls == 10)
            {
                if (runLen != 0)
                    ++runLen;
            }
            else
            {
                int      state  = cls + (int)dir * 5;
                uint32_t action = gNeutralStateActionTable[state];
                uint32_t act    = (uint32_t)((int)action >> 4) & 0xf;

                if (act == 3)
                {
                    uint32_t t = uLevel & 0x80000001;
                    if ((int)t < 0)
                        t = (t - 1 | 0xfffffffe) + 1;
                    act = t + 1;
                }
                if (act != 0)
                {
                    uint32_t* p    = (uint32_t*)((char*)pRecords + (i - runLen) * 0xc);
                    uint32_t* pEnd = (uint32_t*)((char*)p + runLen * 0xc);
                    if (p != pEnd)
                    {
                        do
                        {
                            p[2] = p[2] & 0xfffff07f | (act & 0x1f) << 7;
                            p    = (uint32_t*)((char*)p + 0xc);
                        } while (p != pEnd);
                    }
                    runLen = 0;
                }

                uLevel = action & 0xf;
                if (uLevel != 0x100 && uLevel != 0)
                    *pLevel = *pLevel ^ (uLevel << 7 ^ *pLevel) & 0xf80;
                if ((action & 0x100) != 0)
                    ++runLen;

                dir    = gNeutralStateTable[state];
                uLevel = (uint32_t)((int)(*pLevel << 0x10) >> 0x1c);
            }

            ++i;
            pLevel += 3;
        } while (i < count);
    }

    {
        uint32_t t = uLevel & 0x80000001;
        if ((int)t < 0)
            t = (t - 1 | 0xfffffffe) + 1;
        uint32_t act = (uint32_t)((int)gNeutralFinalActionTable[t + dir * 5] >> 4) & 0xf;
        uint32_t n   = t + 1;
        if (act != 3)
            n = act;
        if (n != 0)
        {
            uint32_t* p    = (uint32_t*)((char*)pRecords + (i - runLen) * 0xc);
            uint32_t* pEnd = (uint32_t*)((char*)p + runLen * 0xc);
            if (p != pEnd)
            {
                do
                {
                    p[2] = p[2] & 0xfffff07f | (n & 0x1f) << 7;
                    p    = (uint32_t*)((char*)p + 0xc);
                } while (p != pEnd);
            }
        }
    }
}

}} // namespace EA::Text
