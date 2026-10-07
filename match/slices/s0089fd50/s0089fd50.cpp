// Slice s0089fd50: EA::Text::OTF::ReadGsubArrayEntry (0x0089fd50, 3572 bytes).
// EAText OpenType GSUB sub-table reader. Written after the EAText source vendored in
// work/ext/EAWebKitSupportPackages (EATextOpenType.cpp); the retail (2008) version differs
// in that create_array stores the element count without a NULL check.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- (as the other EAText slices, e.g. s0089d3b0).
#include "types.h"
#include <string.h>
#pragma intrinsic(memset)

inline void* operator new(unsigned int, void* p) throw() { return p; }

namespace EA {

namespace IO {
typedef uint32_t size_type;
typedef int32_t off_type;
enum Endian { kEndianBig = 0, kEndianLittle = 1 };
enum PositionType { kPositionTypeBegin = 0, kPositionTypeCurrent = 1, kPositionTypeEnd = 2 };

class IStream {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual bool SetPosition(off_type position, PositionType positionType);   // +0x28
};

bool ReadInt16(IStream* pIS, int16_t& value, Endian endianSource);                     // 0x00692720
bool ReadUint16(IStream* pIS, uint16_t* value, size_type count, Endian endianSource);  // 0x0093a700
}  // namespace IO

namespace Allocator {
class StackAllocator {
public:
    void* Malloc(size_t nSize, bool bBoundsCheck = true);
    bool AllocateNewBlock(size_t nExtraSize);   // 0x00928ba0

    struct Block;
    size_t mnDefaultBlockSize;
    Block* mpCurrentBlock;
    char*  mpCurrentBlockEnd;
    char*  mpCurrentObjectBegin;
    char*  mpCurrentObjectEnd;
};

inline void* StackAllocator::Malloc(size_t nSize, bool bBoundsCheck)
{
    nSize = (nSize + 7) & ~7u;
    if (bBoundsCheck && (((intptr_t)mpCurrentBlockEnd - ((intptr_t)mpCurrentObjectBegin + (intptr_t)nSize)) < 0)) {
        if (!AllocateNewBlock(nSize))
            return 0;
    }
    void* const pReturnValue = mpCurrentObjectBegin;
    mpCurrentObjectBegin += nSize;
    mpCurrentObjectEnd = mpCurrentObjectBegin;
    return pReturnValue;
}
}  // namespace Allocator

namespace Text {

template <typename T>
inline T* create_array(Allocator::StackAllocator* pAllocator, size_t count)
{
    uint32_t* p = (uint32_t*)pAllocator->Malloc(sizeof(uint32_t) + (sizeof(T) * count));
    *p++ = (uint32_t)count;
    for (T* pObject = (T*)(void*)p, *pObjectEnd = pObject + count; pObject != pObjectEnd; ++pObject)
        new (pObject) T;
    return (T*)(void*)p;
}
#define EATEXT_SA_NEW_ARRAY(Class, pAllocator, nCount) EA::Text::create_array<Class>(pAllocator, nCount)

typedef uint16_t OTFGlyphId;
typedef uint16_t OTFOffset;

struct OTFLookupRecord { uint16_t mSequenceIndex; uint16_t mLookupListIndex; };

struct OTFClassDef {
    uint16_t mClassFormat;
    uint16_t mStartGlyph;
    uint16_t mCount;
    uint16_t* mpArray;
};

struct OTFSequence {
    OTFOffset   mOffset;
    uint16_t    mSubstitutionCount;
    OTFGlyphId* mpSubstitutionArray;
};
struct OTFLigature {
    OTFOffset   mOffset;
    OTFGlyphId  mGlyph;
    uint16_t    mComponentCount;
    OTFGlyphId* mpComponentArray;
};
struct OTFLigatureSet {
    OTFOffset    mOffset;
    uint16_t     mLigatureCount;
    OTFLigature* mpLigatureArray;
};
struct OTFClassRule {
    OTFOffset        mOffset;
    uint16_t         mGlyphCount;
    uint16_t*        mpClassArray;
    uint16_t         mSubstCount;
    OTFLookupRecord* mpLookupRecordArray;
};
struct OTFClassSet {
    OTFOffset     mOffset;
    uint16_t      mClassRuleCount;
    OTFClassRule* mpClassRuleArray;
};
struct OTFChainClassRule {
    OTFOffset        mOffset;
    uint16_t         mBacktrackGlyphCount;
    uint16_t*        mpBacktrackGlyphArray;
    uint16_t         mInputGlyphCount;
    uint16_t*        mpInputGlyphArray;
    uint16_t         mLookaheadGlyphCount;
    uint16_t*        mpLookaheadGlyphArray;
    uint16_t         mSubstCount;
    OTFLookupRecord* mpLookupRecordArray;
};
struct OTFChainClassSet {
    OTFOffset          mOffset;
    uint16_t           mChainClassRuleCount;
    OTFChainClassRule* mpChainClassRuleArray;
};

struct OTFSingleSubst1   { int16_t mDeltaGlyphId; };
struct OTFSingleSubst2   { uint16_t mSubstitutionCount; OTFGlyphId* mpSubstitutionArray; };
struct OTFMultipleSubst1 { uint16_t mSequenceCount; OTFSequence* mpSequenceArray; };
struct OTFAlternateSubst1 { uint16_t mAlternateSetCount; void* mpAlternateSetArray; };
struct OTFLigatureSubst1 { uint16_t mLigatureSetCount; OTFLigatureSet* mpLigatureSetArray; };
struct OTFContextSubst1  { uint16_t mRuleSetCount; void* mpRuleSetArray; };
struct OTFContextSubst2  { OTFClassDef mClassDef; uint16_t mClassSetCount; OTFClassSet* mpClassSetArray; };
struct OTFContextSubst3  { uint16_t mGlyphCount; uint16_t mSubstCount; void* mpCoverageArray; void* mpLookupRecordArray; uint32_t mReserved; };
struct OTFChainContextSubst1 { uint16_t mChainRuleSetCount; void* mpChainRuleSetArray; };
struct OTFChainContextSubst2 {
    OTFClassDef mBacktrackClassDef;
    OTFClassDef mInputClassDef;
    OTFClassDef mLookaheadClassDef;
    uint16_t    mChainClassSetCount;
    OTFChainClassSet* mpChainClassSetArray;
};
struct OTFChainContextSubst3 { uint32_t mData[8]; };
struct OTFExtensionSubst1   { uint16_t mFormat; uint16_t mType; uint32_t mOffset; uint32_t mReserved; };
struct OTFReverseChainSubst1 { uint32_t mData[6]; };

struct OTFLookupSubTableGsub {
    uint32_t mHeader[3];
    union {
        OTFSingleSubst1       mSingle1;
        OTFSingleSubst2       mSingle2;
        OTFMultipleSubst1     mMultiple1;
        OTFAlternateSubst1    mAlternate1;
        OTFLigatureSubst1     mLigature1;
        OTFContextSubst1      mContext1;
        OTFContextSubst2      mContext2;
        OTFContextSubst3      mContext3;
        OTFChainContextSubst1 mChainContext1;
        OTFChainContextSubst2 mChainContext2;
        OTFChainContextSubst3 mChainContext3;
        OTFExtensionSubst1    mExtension1;
        OTFReverseChainSubst1 mReverseChain1;
    } mLookup;
};

class OTF {
public:
    uint8_t mPad[0x134];
    IO::IStream* mpFontStream;                    // +0x134
    Allocator::StackAllocator mStackAlloctor;     // +0x138

    bool ReadUint16(uint16_t& value);                              // 0x0089ed70
    bool ReadUint16(uint16_t* pValueArray, IO::size_type count);   // 0x0089ed90
    bool ReadClassDef(OTFClassDef& classDef, uint32_t fileOffset); // 0x0089f4b0
    bool ReadGsubArrayEntry(uint32_t substitutionTableOffset, uint32_t nType, uint32_t nFormat,
                            OTFLookupSubTableGsub& gsubEntry);
};

bool OTF::ReadUint16(uint16_t& value)
{
    return IO::ReadUint16(mpFontStream, &value, 1, IO::kEndianBig);
}

bool OTF::ReadUint16(uint16_t* pValueArray, IO::size_type count)
{
    return IO::ReadUint16(mpFontStream, pValueArray, count, IO::kEndianBig);
}

// @ 0x0089fd50 ?ReadGsubArrayEntry@OTF@Text@EA@@
bool OTF::ReadGsubArrayEntry(uint32_t substitutionTableOffset, uint32_t nType, uint32_t nFormat,
                             OTFLookupSubTableGsub& gsubEntry)
{
    uint32_t i, j;

    switch (nType)
    {
        case 1: // Single Substitution Subtable
        {
            if (nFormat == 1)
                IO::ReadInt16(mpFontStream, gsubEntry.mLookup.mSingle1.mDeltaGlyphId, IO::kEndianBig);
            else
            {
                ReadUint16(gsubEntry.mLookup.mSingle2.mSubstitutionCount);
                gsubEntry.mLookup.mSingle2.mpSubstitutionArray =
                        EATEXT_SA_NEW_ARRAY(OTFGlyphId, &mStackAlloctor, gsubEntry.mLookup.mSingle2.mSubstitutionCount);
                ReadUint16(gsubEntry.mLookup.mSingle2.mpSubstitutionArray,
                           gsubEntry.mLookup.mSingle2.mSubstitutionCount);
            }
            break;
        }

        case 2: // Multiple Substitution Subtable
        {
            ReadUint16(gsubEntry.mLookup.mMultiple1.mSequenceCount);

            gsubEntry.mLookup.mMultiple1.mpSequenceArray =
                    EATEXT_SA_NEW_ARRAY(OTFSequence, &mStackAlloctor, gsubEntry.mLookup.mMultiple1.mSequenceCount);

            for (i = 0; i < gsubEntry.mLookup.mMultiple1.mSequenceCount; i++)
                ReadUint16(gsubEntry.mLookup.mMultiple1.mpSequenceArray[i].mOffset);

            for (i = 0; i < gsubEntry.mLookup.mMultiple1.mSequenceCount; i++)
            {
                mpFontStream->SetPosition(substitutionTableOffset + gsubEntry.mLookup.mMultiple1.mpSequenceArray[i].mOffset, IO::kPositionTypeBegin);

                ReadUint16(gsubEntry.mLookup.mMultiple1.mpSequenceArray[i].mSubstitutionCount);

                gsubEntry.mLookup.mMultiple1.mpSequenceArray[i].mpSubstitutionArray =
                        EATEXT_SA_NEW_ARRAY(OTFGlyphId, &mStackAlloctor, gsubEntry.mLookup.mMultiple1.mpSequenceArray[i].mSubstitutionCount);

                ReadUint16(gsubEntry.mLookup.mMultiple1.mpSequenceArray[i].mpSubstitutionArray,
                           gsubEntry.mLookup.mMultiple1.mpSequenceArray[i].mSubstitutionCount);
            }
            break;
        }

        case 3: // Alternate Substitution Subtable (intentionally not read)
        {
            gsubEntry.mLookup.mAlternate1.mAlternateSetCount = 0;
            gsubEntry.mLookup.mAlternate1.mpAlternateSetArray = 0;
            break;
        }

        case 4: // Ligature Substitution Subtable
        {
            ReadUint16(gsubEntry.mLookup.mLigature1.mLigatureSetCount);

            gsubEntry.mLookup.mLigature1.mpLigatureSetArray =
                    EATEXT_SA_NEW_ARRAY(OTFLigatureSet, &mStackAlloctor, gsubEntry.mLookup.mLigature1.mLigatureSetCount);

            for (i = 0; i < gsubEntry.mLookup.mLigature1.mLigatureSetCount; i++)
                ReadUint16(gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mOffset);

            for (i = 0; i < gsubEntry.mLookup.mLigature1.mLigatureSetCount; i++)
            {
                mpFontStream->SetPosition(substitutionTableOffset + gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mOffset, IO::kPositionTypeBegin);

                ReadUint16(gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mLigatureCount);

                gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mpLigatureArray =
                        EATEXT_SA_NEW_ARRAY(OTFLigature, &mStackAlloctor, gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mLigatureCount);

                for (j = 0; j < gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mLigatureCount; j++)
                    ReadUint16(gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mpLigatureArray[j].mOffset);

                for (j = 0; j < gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mLigatureCount; j++)
                {
                    const uint32_t ligatureOffset = substitutionTableOffset + gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mOffset +
                                                        gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mpLigatureArray[j].mOffset;
                    mpFontStream->SetPosition(ligatureOffset, IO::kPositionTypeBegin);

                    ReadUint16(gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mpLigatureArray[j].mGlyph);
                    ReadUint16(gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mpLigatureArray[j].mComponentCount);

                    const uint32_t arraySize = gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mpLigatureArray[j].mComponentCount - 1;

                    gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mpLigatureArray[j].mpComponentArray =
                            EATEXT_SA_NEW_ARRAY(OTFGlyphId, &mStackAlloctor, arraySize);

                    ReadUint16(gsubEntry.mLookup.mLigature1.mpLigatureSetArray[i].mpLigatureArray[j].mpComponentArray, arraySize);
                }
            }
            break;
        }

        case 5: // Contextual Substitution Subtable
        {
            if (nFormat == 1) // ContextSubstFormat1 (not supported)
                memset(&gsubEntry.mLookup.mContext1, 0, sizeof(gsubEntry.mLookup.mContext1));
            else if (nFormat == 2) // ContextSubstFormat2
            {
                OTFOffset offsetClassDef;
                ReadUint16(offsetClassDef);

                ReadUint16(gsubEntry.mLookup.mContext2.mClassSetCount);

                gsubEntry.mLookup.mContext2.mpClassSetArray =
                        EATEXT_SA_NEW_ARRAY(OTFClassSet, &mStackAlloctor, gsubEntry.mLookup.mContext2.mClassSetCount);

                for (i = 0; i < gsubEntry.mLookup.mContext2.mClassSetCount; i++)
                    ReadUint16(gsubEntry.mLookup.mContext2.mpClassSetArray[i].mOffset);

                for (i = 0; i < gsubEntry.mLookup.mContext2.mClassSetCount; i++)
                {
                    if (gsubEntry.mLookup.mContext2.mpClassSetArray[i].mOffset)
                    {
                        mpFontStream->SetPosition(substitutionTableOffset + gsubEntry.mLookup.mContext2.mpClassSetArray[i].mOffset, IO::kPositionTypeBegin);

                        ReadUint16(gsubEntry.mLookup.mContext2.mpClassSetArray[i].mClassRuleCount);

                        gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray =
                                EATEXT_SA_NEW_ARRAY(OTFClassRule, &mStackAlloctor, gsubEntry.mLookup.mContext2.mpClassSetArray[i].mClassRuleCount);

                        for (j = 0; j < gsubEntry.mLookup.mContext2.mpClassSetArray[i].mClassRuleCount; j++)
                            ReadUint16(gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray[j].mOffset);

                        for (j = 0; j < gsubEntry.mLookup.mContext2.mpClassSetArray[i].mClassRuleCount; j++)
                        {
                            const uint32_t classRuleOffset = substitutionTableOffset + gsubEntry.mLookup.mContext2.mpClassSetArray[i].mOffset +
                                                                gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray[j].mOffset;

                            mpFontStream->SetPosition(classRuleOffset, IO::kPositionTypeBegin);

                            ReadUint16(gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray[j].mGlyphCount);

                            gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray[j].mpClassArray =
                                    EATEXT_SA_NEW_ARRAY(uint16_t, &mStackAlloctor, gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray[j].mGlyphCount - 1);

                            ReadUint16(gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray[j].mSubstCount);

                            gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray[j].mpLookupRecordArray =
                                    EATEXT_SA_NEW_ARRAY(OTFLookupRecord, &mStackAlloctor, gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray[j].mSubstCount);

                            ReadUint16(gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray[j].mpClassArray,
                                       gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray[j].mGlyphCount - 1);

                            ReadUint16((uint16_t*)(void*)&gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray[j].mpLookupRecordArray[0],
                                       gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray[j].mSubstCount * 2);
                        }
                    }
                    else
                    {
                        gsubEntry.mLookup.mContext2.mpClassSetArray[i].mClassRuleCount  = 0;
                        gsubEntry.mLookup.mContext2.mpClassSetArray[i].mpClassRuleArray = 0;
                    }
                }

                ReadClassDef(gsubEntry.mLookup.mContext2.mClassDef, substitutionTableOffset + offsetClassDef);
            }
            else // ContextSubstFormat3 (not supported)
                memset(&gsubEntry.mLookup.mContext3, 0, sizeof(gsubEntry.mLookup.mContext3));
            break;
        }

        case 6: // Chaining Contextual Substitution Subtable
        {
            if (nFormat == 1) // ChainContextSubstFormat1 (not supported)
                memset(&gsubEntry.mLookup.mChainContext1, 0, sizeof(gsubEntry.mLookup.mChainContext1));
            else if (nFormat == 2) // ChainContextSubstFormat2
            {
                OTFOffset offsetBacktrackClassDef;
                ReadUint16(offsetBacktrackClassDef);

                OTFOffset inputClassDef;
                ReadUint16(inputClassDef);

                OTFOffset lookaheadClassDef;
                ReadUint16(lookaheadClassDef);

                ReadUint16(gsubEntry.mLookup.mChainContext2.mChainClassSetCount);

                gsubEntry.mLookup.mChainContext2.mpChainClassSetArray =
                        EATEXT_SA_NEW_ARRAY(OTFChainClassSet, &mStackAlloctor, gsubEntry.mLookup.mChainContext2.mChainClassSetCount);

                for (i = 0; i < gsubEntry.mLookup.mChainContext2.mChainClassSetCount; i++)
                    ReadUint16(gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mOffset);

                for (i = 0; i < gsubEntry.mLookup.mChainContext2.mChainClassSetCount; i++)
                {
                    if (gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mOffset)
                    {
                        mpFontStream->SetPosition(substitutionTableOffset + gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mOffset, IO::kPositionTypeBegin);

                        ReadUint16(gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mChainClassRuleCount);

                        gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray =
                                EATEXT_SA_NEW_ARRAY(OTFChainClassRule, &mStackAlloctor, gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mChainClassRuleCount);

                        for (j = 0; j < gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mChainClassRuleCount; j++)
                            ReadUint16(gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mOffset);

                        for (j = 0; j < gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mChainClassRuleCount; j++)
                        {
                            const uint32_t chainClassRuleOffset = substitutionTableOffset + gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mOffset +
                                                                    gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mOffset;

                            mpFontStream->SetPosition(chainClassRuleOffset, IO::kPositionTypeBegin);

                            // Backtrack glyphs
                            ReadUint16(gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mBacktrackGlyphCount);

                            if (gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mBacktrackGlyphCount)
                            {
                                gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mpBacktrackGlyphArray =
                                        EATEXT_SA_NEW_ARRAY(uint16_t, &mStackAlloctor, gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mBacktrackGlyphCount);

                                ReadUint16(gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mpBacktrackGlyphArray,
                                           gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mBacktrackGlyphCount);
                            }
                            else
                                gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mpBacktrackGlyphArray = 0;

                            // Input glyphs (mInputGlyphCount - 1 are stored)
                            ReadUint16(gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mInputGlyphCount);

                            if (gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mInputGlyphCount > 1)
                            {
                                gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mpInputGlyphArray =
                                        EATEXT_SA_NEW_ARRAY(uint16_t, &mStackAlloctor, gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mInputGlyphCount - 1);

                                ReadUint16(gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mpInputGlyphArray,
                                           gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mInputGlyphCount - 1);
                            }
                            else
                                gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mpInputGlyphArray = 0;

                            // Lookahead glyphs
                            ReadUint16(gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mLookaheadGlyphCount);

                            if (gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mLookaheadGlyphCount)
                            {
                                gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mpLookaheadGlyphArray =
                                        EATEXT_SA_NEW_ARRAY(uint16_t, &mStackAlloctor, gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mLookaheadGlyphCount);

                                ReadUint16(gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mpLookaheadGlyphArray,
                                           gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mLookaheadGlyphCount);
                            }
                            else
                                gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mpLookaheadGlyphArray = 0;

                            // Lookup records
                            ReadUint16(gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mSubstCount);

                            gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mpLookupRecordArray =
                                    EATEXT_SA_NEW_ARRAY(OTFLookupRecord, &mStackAlloctor, gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mSubstCount);

                            ReadUint16((uint16_t*)(void*)&gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mpLookupRecordArray[0],
                                       gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray[j].mSubstCount * 2);
                        }
                    }
                    else
                    {
                        gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mChainClassRuleCount = 0;
                        gsubEntry.mLookup.mChainContext2.mpChainClassSetArray[i].mpChainClassRuleArray = 0;
                    }
                }

                if (offsetBacktrackClassDef)
                    ReadClassDef(gsubEntry.mLookup.mChainContext2.mBacktrackClassDef, substitutionTableOffset + offsetBacktrackClassDef);
                else
                    memset(&gsubEntry.mLookup.mChainContext2.mBacktrackClassDef, 0, sizeof(gsubEntry.mLookup.mChainContext2.mBacktrackClassDef));

                if (inputClassDef)
                    ReadClassDef(gsubEntry.mLookup.mChainContext2.mInputClassDef, substitutionTableOffset + inputClassDef);
                else
                    memset(&gsubEntry.mLookup.mChainContext2.mInputClassDef, 0, sizeof(gsubEntry.mLookup.mChainContext2.mInputClassDef));

                if (lookaheadClassDef)
                    ReadClassDef(gsubEntry.mLookup.mChainContext2.mLookaheadClassDef, substitutionTableOffset + lookaheadClassDef);
                else
                    memset(&gsubEntry.mLookup.mChainContext2.mLookaheadClassDef, 0, sizeof(gsubEntry.mLookup.mChainContext2.mLookaheadClassDef));
            }
            else // ChainContextSubstFormat3 (not supported)
                memset(&gsubEntry.mLookup.mChainContext3, 0, sizeof(gsubEntry.mLookup.mChainContext3));
            break;
        }

        case 7: // Extension Substitution (not supported)
            memset(&gsubEntry.mLookup.mExtension1, 0, sizeof(gsubEntry.mLookup.mExtension1));
            break;

        case 8: // Reverse Chaining Contextual Single Substitution (not supported)
            memset(&gsubEntry.mLookup.mReverseChain1, 0, sizeof(gsubEntry.mLookup.mReverseChain1));
            break;
    }

    return true;
}

}  // namespace Text
}  // namespace EA
