// src/game/UTFSpore_Win32/EATextShapeArabic.cpp -- migrated from slice(s) s008a2a00, s008a1a10, s008a0b50 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EATextShapeArabic.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <stdlib.h>
#include <new>
#include "EA/Text/Typesetter.h"
#include "EA/Text/GlyphInfo.h"
#include "EA/Text/LineLayout.h"
#include "EA/Text/AnalysisInfo.h"
#include "EA/Text/Font.h"
#include "EA/Text/GlyphLayoutInfo.h"
#include "EA/Text/GlyphMetrics.h"
#include "EA/Text/LayoutSettings.h"
#include "EA/Text/TextStyle.h"

// ---- items of slice s008a0b50 begin (TODO(rewrite): local stubs, replace by canonical classes)
class IVectorAllocator {
 public:
  virtual void vf00();
  virtual void vf04();
  virtual void* Allocate(uint32_t nBytes, int nFlags, void* pName);   // +0x08
  virtual void Deallocate(void* pBlock, uint32_t nBytes);             // +0x0c
};
inline uint16_t* CopyBackwardTrivial(const uint16_t* first, const uint16_t* last, uint16_t* result)
{
  return (uint16_t*)memmove(result - (last - first), first,
                            (size_t)((uintptr_t)last - (uintptr_t)first));
}
inline uint16_t* UninitializedCopyTrivial(const uint16_t* first, const uint16_t* last, uint16_t* result)
{
  return (uint16_t*)memcpy(result, first, (size_t)((uintptr_t)last - (uintptr_t)first))
         + (last - first);
}
class CWordVector {
 public:
  uint16_t* mpBegin;             // +0x00
  uint16_t* mpEnd;               // +0x04
  uint16_t* mpCapacity;          // +0x08
  IVectorAllocator* mpAllocator; // +0x0c
  void* mpAllocatorName;         // +0x10

  void Insert(uint16_t* position, const uint16_t& value);   // 0x008a1900
};
// ---- items of slice s008a0b50 end

// ---- items of slice s008a1a10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __cdecl memcpy(void* pDest, const void* pSrc, uint32_t nBytes);
namespace SP {
void* CopyEntriesRaw(void* pFirst, void* pLast, void* pDest);      // 0x0099efa0
}
namespace SP {
struct CVectorEntry {
  uint32_t mFlags;         // +0x00
  uint8_t  mnPad04;        // +0x04
  uint8_t  mnGlyphClass;   // +0x05
  uint16_t mnPad06;        // +0x06
};
}
namespace SP {
class IVectorAllocator_s008a_1a10 {
 public:
  virtual void vf00();
  virtual void vf04();
  virtual void* Allocate(uint32_t nBytes, int nFlags, void* pName);   // +0x08
  virtual void Deallocate(void* pBlock, uint32_t nBytes);             // +0x0c
};
}
namespace SP {
class CVectorEntryArray {
 public:
  CVectorEntry* mpBegin;         // +0x00
  CVectorEntry* mpEnd;           // +0x04
  CVectorEntry* mpCap;           // +0x08
  IVectorAllocator_s008a_1a10* mpAlloc;     // +0x0c
  void* mpAllocName;             // +0x10

  void Insert(CVectorEntry* pPos, const CVectorEntry& value);   // 0x008a1a10
};
}
namespace EA {
namespace Text {
class OTFClassDef;
}
}
namespace EA {
namespace Text {
class OTFClassDef {
 public:
  uint16_t GetGlyphClass(uint16_t glyphId) const;   // 0x0089ef10
};
}
}
namespace EA {
namespace Text {
class OTF {
 public:
  char mPad00[0xac];
  OTFClassDef mClassDef;     // +0xac
};
}
}
namespace EA {
namespace Text {
struct LineLayout_s008a_1a10 {
  char mPad00[0x2c];
  uint16_t* mpCodes;                     // +0x2c
  uint16_t* mpCodesEnd;                  // +0x30
  char mPad34[0x40 - 0x34];
  SP::CVectorEntryArray mShapedGlyphs;   // +0x40
};
}
}
namespace EA {
namespace Text {
void EraseShapedGlyphs(LineLayout_s008a_1a10* pLineLayout, SP::CVectorEntry* pFirst,
                       SP::CVectorEntry* pLast);                      // 0x00d018d0
}
}
namespace EA {
namespace Text {
struct CharVector {
  uint16_t* mpBegin;      // +0x00
  uint16_t* mpEnd;        // +0x04
  uint16_t* mpCapacity;   // +0x08

  void DoInsertValue(uint16_t* pPos, const uint16_t& value);   // 0x008a1900
};
}
}
namespace EA {
namespace Text {
struct ArabicLayout {
  char mPad0000[0x444];
  CharVector mAnalysisGlyphs;            // +0x444
  char mPad0450[0x458 - 0x450];
  SP::CVectorEntryArray mShapedGlyphs;   // +0x458

  void AppendArabicGlyphCluster(uint32_t nUnused1, uint32_t nForm, const uint16_t* pJointType,
                                uint32_t nUnused2, const uint16_t* pCharCodes, uint32_t nCount,
                                uint32_t nJointFlags, OTF* pOTF);   // 0x008a1c60
};
}
}
// ---- items of slice s008a1a10 end

// ---- items of slice s008a2a00 begin (TODO(rewrite): local stubs, replace by canonical classes)
void FreeRawBlock(void* p);                                  // 0x00f47380 (EASTL operator delete)
namespace EA {
namespace Text {
typedef unsigned short GlyphId;
}
}
namespace EA {
namespace Text {
typedef wchar_t Char;
}
}
namespace EA {
namespace Text {
struct TextStyle_s008a_2a00 {
    unsigned char mPad00[0x264];
    int mPasswordMode;                      // +0x264 (LayoutSettings mTextStyleDefault)
    unsigned char mPad01[0x26c - 0x268];
    float mfLetterSpacing;                  // +0x26c
    unsigned char mPad02[0x278 - 0x270];
};
}
}
namespace EA {
namespace Text {
struct LayoutSettings_s008a_2a00 {
    unsigned char mPad00[0xf8];
    TextStyle_s008a_2a00 mTextStyleDefault;            // +0xf8
    bool mbEnableAutoHyphenation;           // +0x370
    bool mbCellTopPosition;                 // +0x371
    unsigned char mPad01[2];
    float mfYScale;                         // +0x374
    bool mbEnableLigatures;                 // +0x378
    bool mbHideControlCharacters;           // +0x379
    bool mbDisplayZWG;                      // +0x37a
    unsigned char mPad02[1];
};
}
}
namespace EA {
namespace Text {
struct GlyphMetrics_s008a_2a00 {
    float mfSizeX;                          // +0x00
    float mfSizeY;                          // +0x04
    float mfHBearingX;                      // +0x08
    float mfHBearingY;                      // +0x0c
    float mfHAdvanceX;                      // +0x10
};
}
}
namespace EA {
namespace Text {
struct Kerning {
    float mfX;                              // +0x00
    float mfY;                              // +0x04
};
}
}
namespace EA {
namespace Text {
struct GlyphInfo_s008a_2a00 {
    union {
        uint32_t mBits;                     // +0x00
        struct {
            uint32_t mGJC : 4;
            uint32_t mbGlyphIsObject : 1;
            uint32_t mClusterPosition : 3;
            uint32_t mClusterSize : 3;
            uint32_t mClusterBreakable : 1;
            uint32_t mCharCount : 2;
            uint32_t mDirection : 1;
        };
    };
    uint8_t  mScriptFlags;                  // +0x04
    uint8_t  mOpenTypeLookupFlags;          // +0x05
    uint16_t mPad06;                        // +0x06
};
}
}
namespace EA {
namespace Text {
struct GlyphLayoutInfo_s008a_2a00 {
    union {
        struct Font_s008a_2a00* mpFont;                // +0x00
        void* mpObject;
    };
    float mfPenX;                           // +0x04
    float mfPenY;                           // +0x08
    float mfAdvance;                        // +0x0c
    float mfX1;                             // +0x10
    float mfY1;                             // +0x14
    float mfX2;                             // +0x18
    float mfY2;                             // +0x1c
};
}
}
namespace EA {
namespace Text {
struct AnalysisInfo_s008a_2a00 {
    TextStyle_s008a_2a00* mpTextStyle;                 // +0x00
    struct Font_s008a_2a00* mpFont;                    // +0x04
    uint32_t mScript : 7;                   // +0x08
    uint32_t mBidiClass : 5;
    int      mnBidiLevel : 4;
    uint32_t mbJoinBefore : 1;
    uint32_t mbJoinAfter : 1;
};
}
}
namespace EA {
namespace Text {
struct OTFGsubGpos;
}
}
namespace EA {
namespace Text {
class Font_s008a_2a00 {
public:
    virtual void v00();                     // slot 0
    virtual void v01();                     // slot 1
    virtual void v02();                     // slot 2
    virtual void v03();                     // slot 3
    virtual void v04();                     // slot 4
    virtual void v05();                     // slot 5
    virtual void v06();                     // slot 6
    virtual void v07();                     // slot 7
    virtual void v08();                     // slot 8
    virtual void v09();                     // slot 9
    virtual void v10();                     // slot 10
    virtual void v11();                     // slot 11
    virtual void v12();                     // slot 12
    virtual bool GetGlyphMetrics(GlyphId glyph, GlyphMetrics_s008a_2a00& metrics);   // +0x34, slot 13
    virtual void v14();                     // slot 14
    virtual void v15();                     // slot 15
    virtual bool GetKerning(GlyphId prev, GlyphId cur, Kerning& kerning, int direction, bool flag); // +0x40, slot 16
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual struct OTF_s008a_2a00* GetOTF();           // +0x58, slot 22
};
}
}
namespace EA {
namespace Text {
class ICoreAllocator {
public:
    virtual void v00();
    virtual void v01();
    virtual void* Allocate(size_t n, int flags, unsigned debugFlags);   // vtable +0x08
    virtual void Deallocate(void* p, size_t n);                         // vtable +0x0c
};
}
}
namespace EA {
namespace Text {
template <class Derived, class T>
struct VectorBase {
    T* mpBegin;                             // +0x00
    T* mpEnd;                               // +0x04
    T* mpCapacity;                          // +0x08
    ICoreAllocator* mpAllocator;            // +0x0c
    uint32_t mFlags;                        // +0x10

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    const T& operator[](uint32_t i) const { return mpBegin[i]; }
    T& back() { return mpEnd[-1]; }

    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) T(value);
        else
            static_cast<Derived*>(this)->DoInsertValue(mpEnd, value);
    }

    void push_back() {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) T();
        else {
            T value = T();
            static_cast<Derived*>(this)->DoInsertValue(mpEnd, value);
        }
    }
};
}
}
namespace EA {
namespace Text {
struct AnalysisInfoVector : VectorBase<AnalysisInfoVector, AnalysisInfo_s008a_2a00> {
};
}
}
namespace EA {
namespace Text {
struct GlyphIdVector : VectorBase<GlyphIdVector, GlyphId> {
    void DoInsertValue(GlyphId* position, const GlyphId& value);        // 0x008a1900
};
}
}
namespace EA {
namespace Text {
struct GlyphInfoVector : VectorBase<GlyphInfoVector, GlyphInfo_s008a_2a00> {
    void DoInsertValue(GlyphInfo_s008a_2a00* position, const GlyphInfo_s008a_2a00& value);    // 0x008a1a10
};
}
}
namespace EA {
namespace Text {
struct GlyphLayoutVector : VectorBase<GlyphLayoutVector, GlyphLayoutInfo_s008a_2a00> {
    uint32_t GetNewCapacity(uint32_t currentCapacity) {
        return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
    }
    GlyphLayoutInfo_s008a_2a00* DoAllocate(uint32_t n) {
        return n ? (GlyphLayoutInfo_s008a_2a00*)mpAllocator->Allocate(n * sizeof(GlyphLayoutInfo_s008a_2a00), 0, mFlags) : 0;
    }
    void DoFree(GlyphLayoutInfo_s008a_2a00* p, uint32_t n) {
        if (p)
            mpAllocator->Deallocate(p, n * sizeof(GlyphLayoutInfo_s008a_2a00));
    }
    void DoInsertValue(GlyphLayoutInfo_s008a_2a00* position, const GlyphLayoutInfo_s008a_2a00& value); // @ 0x008a2fe0
};
}
}
namespace EA {
namespace Text {
struct UIntVector : VectorBase<UIntVector, uint32_t> {
    void DoInsertValue(uint32_t* position, const uint32_t& value);      // 0x008891f0
};
}
}
namespace EA {
namespace Text {
struct WString {
    wchar_t* mpBegin;                       // +0x00
    wchar_t* mpEnd;                         // +0x04
    wchar_t* mpCapacity;                    // +0x08
    void* mpAllocator;                      // +0x0c
    uint32_t mFlags;                        // +0x10

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    Char& operator[](uint32_t i) { return mpBegin[i]; }
    const Char& operator[](uint32_t i) const { return mpBegin[i]; }
};
}
}
namespace EA {
namespace Text {
class LineLayout_s008a_2a00 {
public:
    void GetGlyphRangeFromCharRange(unsigned a, unsigned b, unsigned& g0, unsigned& g1) const;   // 0x00897ae0
    unsigned GetGlyphIndexFromCharIndex(unsigned charIndex) const;                              // 0x00897ab0

    void* mpCoreAllocator;                  // +0x00
    WString mCharArray;                     // +0x04 (Typesetter +0x41c)
    AnalysisInfoVector mAnalysisInfoArray;  // +0x18 (Typesetter +0x430)
    GlyphIdVector mGlyphArray;              // +0x2c (Typesetter +0x444)
    GlyphInfoVector mGlyphInfoArray;        // +0x40 (Typesetter +0x458)
    GlyphLayoutVector mGlyphLayoutInfoArray; // +0x54 (Typesetter +0x46c)
    UIntVector mGlyphIndexArray;            // +0x68 (Typesetter +0x480)
    UIntVector mCharIndexArray;             // +0x7c (Typesetter +0x494)
    unsigned char mPad00[0xb0 - 0x90];
};
}
}
namespace EA {
namespace Text {
enum {
    kOTFTag_ccmp = 0x63636d70,
    kOTFTag_isol = 0x69736f6c,
    kOTFTag_fina = 0x66696e61,
    kOTFTag_medi = 0x6d656469,
    kOTFTag_init = 0x696e6974,
    kOTFTag_rlig = 0x726c6967,
    kOTFTag_calt = 0x63616c74,
    kOTFTag_liga = 0x6c696761,
    kOTFTag_cswh = 0x63737768,
    kOTFTag_mset = 0x6d736574,
    kOTFTag_arab = 0x61726162,
};
}
}
namespace EA {
namespace Text {
struct FeatureLookup {
    uint32_t mFeatureTag;                   // +0x00
    uint32_t mGlyphFlags;                   // +0x04
    unsigned char mLookupPtrArray[0x58];    // +0x08 (retail OTFLookupPtrArray16)
};
}
}
namespace EA {
namespace Text {
struct FeatureLookupArray {
    FeatureLookup* mpBegin;                 // +0x00
    FeatureLookup* mpEnd;                   // +0x04
    FeatureLookup* mpCapacity;              // +0x08
    uint32_t mAllocator;                    // +0x0c
    FeatureLookup* mpFixedBuffer;           // +0x10
    uint32_t mPad14;                        // +0x14
    FeatureLookup mBuffer[10];              // +0x18

    FeatureLookupArray() {
        mpEnd = mBuffer;
        mpFixedBuffer = mBuffer;
        mpBegin = mBuffer;
        mpCapacity = mBuffer + 10;
    }
    ~FeatureLookupArray() {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin && (mpBegin != mpFixedBuffer))
            FreeRawBlock(mpBegin);
    }

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    FeatureLookup& operator[](uint32_t i) { return mpBegin[i]; }

    void resize(uint32_t n);                                    // 0x008a2950
    void DoDestroyValues(FeatureLookup* begin, FeatureLookup* end); // 0x008a1c20
};
}
}
namespace EA {
namespace Text {
struct OTFTagStruct {
    uint32_t mOTFTag;                       // +0x00
    OTFTagStruct(uint32_t tag = 0) : mOTFTag(tag) {}
};
}
}
namespace EA {
namespace Text {
struct OTFGsubGpos {
    void BuildFeatureLookup(const OTFTagStruct& script, const OTFTagStruct& language,
                            FeatureLookupArray& array) const;    // 0x008a11c0
};
}
}
namespace EA {
namespace Text {
struct OTF_s008a_2a00 {
    unsigned char mPad00[0xe8];
    OTFGsubGpos mGsub;                      // +0xe8
    bool IsScriptSupported(const char* pScript, const char* pLanguage) const; // 0x0089f400
};
}
}
namespace EA {
namespace Text {
struct Item_s008a_2a00 {
    int mType;                              // +0x00
    unsigned mIndex;                        // +0x04
    unsigned mCount;                        // +0x08
    TextStyle_s008a_2a00* mpStyle;                     // +0x0c
    union {
        struct {
            void* mpObjectPtr;              // +0x10
            GlyphMetrics_s008a_2a00 mGlyphMetrics;     // +0x14
            bool mbBindPrev;                // +0x28
            bool mbBindNext;                // +0x29
        } mObject;
    };
};
}
}
namespace EA {
namespace Text {
void AssignArabicCharProperties(const Char* pText, unsigned nTextLength,
                                GlyphInfo_s008a_2a00* pGlyphInfo);             // 0x008a1680
}
}
namespace EA {
namespace Text {
void DoGlyphSubstitution(LineLayout_s008a_2a00& lineLayout, unsigned iGlyphBegin,
                         const FeatureLookupArray& featureLookupArray,
                         const OTF_s008a_2a00* pOTF);                          // 0x008a2120
}
}
namespace EA {
namespace Text {
class Typesetter_s008a_2a00 {
public:
    void PlaceGeneralGlyphCluster(unsigned charIndex, unsigned charCount);
    void SetGlyphLayoutInfo(GlyphLayoutInfo_s008a_2a00& info, float x, const GlyphMetrics_s008a_2a00& metrics);   // 0x00897830
    void GetObjectMetrics(unsigned index, GlyphMetrics_s008a_2a00& metrics);                          // 0x00898300
    unsigned GetGlyphsForChar(const Char* pChar, unsigned count, const AnalysisInfo_s008a_2a00* pAnalysisInfo,
                              GlyphId* pGlyphIdArray, unsigned& glyphIdCount,
                              const Char* pFallbackOptions, unsigned fallbackOptionCount);  // 0x00897790
    Item_s008a_2a00* GetScheduleItemFromCharIndex(unsigned charIndex, bool lineRelative);             // 0x008982c0
    void ShapeGeneral(unsigned iCharBegin, unsigned iCharEnd);                             // 0x008a3430
    void AppendArabicGlyphCluster(unsigned iCharBegin, unsigned charCount,
                                  const Char* pCharCluster, unsigned charClusterSize,
                                  const GlyphId* pGlyphCluster, unsigned glyphClusterSize,
                                  int embeddingLevel, const OTF_s008a_2a00* pOTF);                     // 0x008a1c60
    void CompleteLineLayoutArrays(unsigned iCharBegin, unsigned iCharEnd,
                                  unsigned iGlyphBegin);                                   // 0x008a21e0
    void ShapeArabic(unsigned iCharBegin, unsigned iCharEnd);                             // 0x008a2b10
    unsigned GetGeneralCharCluster(unsigned iCharBegin, unsigned iCharEnd,
                                   Char* pCharCluster, unsigned& clusterSize);             // 0x008a2ee0
    void AppendGeneralGlyphCluster(unsigned iCharBegin, unsigned charCount,
                                   const Char* pCharCluster, unsigned charClusterSize,
                                   const GlyphId* pGlyphCluster, unsigned glyphClusterSize,
                                   int embeddingLevel);                                    // 0x008a3110
    unsigned AppendHangulCharCluster(unsigned iCharBegin, unsigned charCount,
                                     const Char* pCharCluster, unsigned clusterSize,
                                     int clusterType);                                     // 0x008a3480

    void* mpCoreAllocator;                  // +0x000
    LayoutSettings_s008a_2a00 mLayoutSettings;         // +0x004
    unsigned char mPad00[0x3cc - 0x380];
    bool mbEllipsize;                       // +0x3cc
    unsigned char mPad01[1];
    Char mPasswordChar;                     // +0x3ce
    unsigned char mPad02[0x418 - 0x3d0];
    LineLayout_s008a_2a00 mLineLayout;                 // +0x418
    unsigned char mPad03[0x528 - 0x418 - 0xb0];
    float mfPenX;                           // +0x528
    float mfPenXMax;                        // +0x52c
};
}
}
// ---- items of slice s008a2a00 end

// @ 0x008a1900
void CWordVector::Insert(uint16_t* position, const uint16_t& value)
{
  if (mpEnd != mpCapacity) {
    const uint16_t* pValue = &value;
    // A value that already lives at or after the insertion point moves up with the tail.
    if ((pValue >= position) && (pValue < mpEnd))
      ++pValue;
    // The shift is a move_backward with its first copy peeled off.
    ::new (mpEnd) uint16_t(*(mpEnd - 1));
    CopyBackwardTrivial(position, mpEnd - 1, mpEnd);
    *position = *pValue;
    ++mpEnd;
    return;
  }

  const size_t nPosSize = (size_t)(position - mpBegin);
  const size_t nPrevSize = (size_t)(mpEnd - mpBegin);
  const size_t nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
  uint16_t* const pNewData =
      nNewSize ? (uint16_t*)mpAllocator->Allocate((uint32_t)(nNewSize * sizeof(uint16_t)), 0,
                                                  mpAllocatorName)
               : 0;
  (void)nPosSize;
  uint16_t* pNewEnd = UninitializedCopyTrivial(mpBegin, position, pNewData);
  ::new (pNewEnd) uint16_t(value);
  pNewEnd = UninitializedCopyTrivial(position, mpEnd, ++pNewEnd);

  if (mpBegin != 0)
    mpAllocator->Deallocate(mpBegin, (uint32_t)((mpCapacity - mpBegin) * sizeof(uint16_t)));

  mpBegin = pNewData;
  mpEnd = pNewEnd;
  mpCapacity = pNewData + nNewSize;
}

// @ 0x008a1a10
namespace SP {
void CVectorEntryArray::Insert(CVectorEntry* pPos, const CVectorEntry& value)
{
  if (mpEnd != mpCap) {
    const CVectorEntry* pValue = &value;
    // An entry that already lives at or after the insertion point moves up with the tail.
    if (pValue >= pPos && pValue < mpEnd)
      ++pValue;
    // The shift is a move_backward with its first copy peeled off.
    if (mpEnd != 0)
      *mpEnd = mpEnd[-1];
    CVectorEntry* pSrc = mpEnd - 1;
    CVectorEntry* pDst = mpEnd;
    while (pSrc != pPos) {
      --pSrc;
      --pDst;
      *pDst = *pSrc;
    }
    *pPos = *pValue;
    ++mpEnd;
    return;
  }

  int nDiff = (int)(mpEnd - mpBegin);
  unsigned nCount = (unsigned)nDiff;
  int nNewCap = (nCount > 0u) ? (int)(nCount * 2) : 1;
  CVectorEntry* pNew;
  if (nNewCap != 0)
    pNew = (CVectorEntry*)mpAlloc->Allocate((uint32_t)(nNewCap * (int)sizeof(CVectorEntry)), 0,
                                            mpAllocName);
  else
    pNew = 0;

  void* pNewEnd = CopyEntriesRaw(mpBegin, pPos, pNew);
  if (pNewEnd != 0)
    *(CVectorEntry*)pNewEnd = value;
  pNewEnd = CopyEntriesRaw(pPos, mpEnd, (char*)pNewEnd + sizeof(CVectorEntry));

  if (mpBegin != 0) {
    int nOldCap = (int)(mpCap - mpBegin);
    mpAlloc->Deallocate(mpBegin, (uint32_t)(nOldCap * (int)sizeof(CVectorEntry)));
  }
  mpBegin = pNew;
  mpEnd = (CVectorEntry*)pNewEnd;
  mpCap = pNew + nNewCap;
}
}  // namespace SP

// @ 0x008a1b70
namespace EA { namespace Text {
void SubstituteGlyphs2(LineLayout_s008a_1a10* pLineLayout, uint32_t nPosition, uint32_t nCount, uint16_t glyph)
{
  uint16_t* const pCodes = pLineLayout->mpCodes;
  uint16_t* const pSrc = pCodes + nPosition + nCount;
  uint16_t* const pDst = pCodes + nPosition + 1;

  memcpy(pDst, pSrc, (uint32_t)(pLineLayout->mpCodesEnd - pSrc) * sizeof(uint16_t));
  pLineLayout->mpCodesEnd = pDst + (pLineLayout->mpCodesEnd - pSrc);

  EraseShapedGlyphs(pLineLayout, pLineLayout->mShapedGlyphs.mpBegin + nPosition + 1,
                    pLineLayout->mShapedGlyphs.mpBegin + nPosition + nCount);

  pCodes[nPosition] = glyph;

  SP::CVectorEntry* const pAttributes = pLineLayout->mShapedGlyphs.mpBegin + nPosition;
  pAttributes->mFlags = (pAttributes->mFlags & 0xfffff9ff) | 0x100;
  pAttributes->mFlags &= 0xffffff1f;
  pAttributes->mFlags ^= (nCount << 12 ^ pAttributes->mFlags) & 0x3000;
  pAttributes->mFlags |= 0x800;
}
}}  // namespace EA::Text

// @ 0x008a1c60
namespace EA { namespace Text {
void ArabicLayout::AppendArabicGlyphCluster(uint32_t nUnused1, uint32_t nForm, const uint16_t* pJointType, uint32_t nUnused2, const uint16_t* pCharCodes, uint32_t nCount, uint32_t nJointFlags, OTF* pOTF)
{
  const uint32_t nFormBits = (nForm & 3) << 12;
  const uint32_t nCountBits = (nCount & 7) << 8;
  const uint32_t nJointBits = (nJointFlags & 1) << 14;
  const OTFClassDef* const pClassDef = &pOTF->mClassDef;

  for (uint32_t i = 0; i < nCount; ++i) {
    const uint16_t glyphCode = pCharCodes[i];

    if (mAnalysisGlyphs.mpEnd < mAnalysisGlyphs.mpCapacity) {
      uint16_t* const pNew = mAnalysisGlyphs.mpEnd;
      mAnalysisGlyphs.mpEnd = pNew + 1;
      if (pNew != 0)
        *pNew = glyphCode;
    } else {
      mAnalysisGlyphs.DoInsertValue(mAnalysisGlyphs.mpEnd, glyphCode);
    }

    SP::CVectorEntry* pAttribute;
    if (mShapedGlyphs.mpEnd < mShapedGlyphs.mpCap) {
      pAttribute = mShapedGlyphs.mpEnd;
      mShapedGlyphs.mpEnd = pAttribute + 1;
      if (pAttribute != 0) {
        pAttribute->mFlags = 0;
        pAttribute->mnPad04 = 0;
        pAttribute->mnPad06 = 0;
      }
    } else {
      SP::CVectorEntry empty;
      empty.mFlags = 0;
      empty.mnPad04 = 0;
      empty.mnPad06 = 0;
      mShapedGlyphs.Insert(mShapedGlyphs.mpEnd, empty);
      pAttribute = mShapedGlyphs.mpEnd - 1;
    }

    uint32_t nFlags = pAttribute->mFlags & 0xfffff810;
    nFlags |= nCountBits;
    nFlags &= 0xffffc7ff;
    nFlags |= nFormBits;
    nFlags &= 0xffffbfff;
    nFlags |= (i & 7) << 5;
    nFlags |= nJointBits;
    nFlags = ((uint32_t)(*pJointType != 0xfffc) << 4 ^ nFlags) & 0x10 ^ nFlags;
    pAttribute->mFlags = nFlags;
    pAttribute->mnGlyphClass = (uint8_t)pClassDef->GetGlyphClass(glyphCode);
  }
}
}}  // namespace EA::Text

// @ 0x008a2a00
namespace EA { namespace Text {
void SetupArabicGsubLookup(FeatureLookupArray& featureLookupArray, const OTF_s008a_2a00* pOTF)
{
    featureLookupArray.resize(10);

    featureLookupArray[0].mFeatureTag = kOTFTag_ccmp;
    featureLookupArray[0].mGlyphFlags = 0xffffffff;

    featureLookupArray[1].mFeatureTag = kOTFTag_isol;
    featureLookupArray[1].mGlyphFlags = 1;

    featureLookupArray[2].mFeatureTag = kOTFTag_fina;
    featureLookupArray[2].mGlyphFlags = 2;

    featureLookupArray[3].mFeatureTag = kOTFTag_medi;
    featureLookupArray[3].mGlyphFlags = 4;

    featureLookupArray[4].mFeatureTag = kOTFTag_init;
    featureLookupArray[4].mGlyphFlags = 8;

    featureLookupArray[5].mFeatureTag = kOTFTag_rlig;
    featureLookupArray[5].mGlyphFlags = 0xffffffff;

    featureLookupArray[6].mFeatureTag = kOTFTag_calt;
    featureLookupArray[6].mGlyphFlags = 0xffffffff;

    featureLookupArray[7].mFeatureTag = kOTFTag_liga;
    featureLookupArray[7].mGlyphFlags = 0xffffffff;

    featureLookupArray[8].mFeatureTag = kOTFTag_cswh;
    featureLookupArray[8].mGlyphFlags = 0xffffffff;

    featureLookupArray[9].mFeatureTag = kOTFTag_mset;
    featureLookupArray[9].mGlyphFlags = 0xffffffff;

    pOTF->mGsub.BuildFeatureLookup(OTFTagStruct(kOTFTag_arab), OTFTagStruct(0), featureLookupArray);
}
}}  // namespace EA::Text

// @ 0x008a2b10
namespace EA { namespace Text {
void Typesetter_s008a_2a00::ShapeArabic(unsigned iCharBegin, unsigned iCharEnd)
{
    const OTF_s008a_2a00* const pOTF = mLineLayout.mAnalysisInfoArray[0].mpFont->GetOTF();

    if (pOTF && pOTF->IsScriptSupported("arab", 0)) {
        const unsigned iGlyphBegin = mLineLayout.GetGlyphIndexFromCharIndex(iCharBegin);

        for (unsigned i = iCharBegin, charCount = 0; i < iCharEnd; i += charCount) {
            const AnalysisInfo_s008a_2a00* const pAnalysisInfo = &mLineLayout.mAnalysisInfoArray[i];

            Char pCharCluster[32];
            unsigned charClusterSize = 0;

            charCount = GetGeneralCharCluster(i, iCharEnd, pCharCluster, charClusterSize);

            for (unsigned c = 0, charsEaten = 0, glyphCount = 0, glyphCountPrev = 0;
                 c < charClusterSize; c += charsEaten) {
                GlyphId pGlyphIdArray[32];

                charsEaten = GetGlyphsForChar(pCharCluster + c, charClusterSize - c, pAnalysisInfo,
                                              pGlyphIdArray + glyphCount, glyphCount, 0, 0);

                AppendArabicGlyphCluster(iCharBegin, charCount, pCharCluster + c, charsEaten,
                                         pGlyphIdArray + glyphCountPrev, glyphCount - glyphCountPrev,
                                         pAnalysisInfo->mnBidiLevel, pOTF);

                glyphCountPrev = glyphCount;
            }
        }

        FeatureLookupArray featureLookupArray;

        SetupArabicGsubLookup(featureLookupArray, pOTF);
        AssignArabicCharProperties(&mLineLayout.mCharArray[iCharBegin], iCharEnd - iCharBegin,
                                   &mLineLayout.mGlyphInfoArray[iGlyphBegin]);
        DoGlyphSubstitution(mLineLayout, iGlyphBegin, featureLookupArray, pOTF);
        CompleteLineLayoutArrays(iCharBegin, iCharEnd, iGlyphBegin);
        PlaceGeneralGlyphCluster(iCharBegin, iCharEnd - iCharBegin);
    } else {
        ShapeGeneral(iCharBegin, iCharEnd);
    }
}
}}  // namespace EA::Text

// @ 0x008a2d60
namespace EA { namespace Text {
void Typesetter_s008a_2a00::PlaceGeneralGlyphCluster(unsigned charIndex, unsigned charCount)
{
    TextStyle_s008a_2a00* pStyle = mLineLayout.mAnalysisInfoArray.mpBegin[charIndex].mpTextStyle;
    float fLetterSpacing = pStyle ? pStyle->mfLetterSpacing : 0.0f;

    unsigned glyphEnd;
    mLineLayout.GetGlyphRangeFromCharRange(charIndex, charIndex + charCount, charCount, glyphEnd);

    unsigned prevGlyph = 0;
    for (unsigned glyphIndex = charCount; glyphIndex < glyphEnd; ++glyphIndex) {
        GlyphId glyphId = mLineLayout.mGlyphArray.mpBegin[glyphIndex];
        GlyphInfo_s008a_2a00& glyphInfo = mLineLayout.mGlyphInfoArray.mpBegin[glyphIndex];
        GlyphLayoutInfo_s008a_2a00& layoutInfo = mLineLayout.mGlyphLayoutInfoArray.mpBegin[glyphIndex];

        if (glyphIndex != charCount && (glyphInfo.mBits & 0x10) == 0) {
            Kerning kerning;
            if (layoutInfo.mpFont->GetKerning(prevGlyph, glyphId, kerning,
                                              (int)((glyphInfo.mBits >> 14) & 1), true))
                mfPenX = mfPenX + kerning.mfX;
        }

        GlyphMetrics_s008a_2a00 metrics;
        if ((glyphInfo.mBits & 0x10) == 0)
            layoutInfo.mpFont->GetGlyphMetrics(glyphId, metrics);
        else
            GetObjectMetrics(glyphIndex, metrics);

        SetGlyphLayoutInfo(layoutInfo, mfPenX, metrics);

        if ((glyphInfo.mBits & 0xe0) == 0)
            metrics.mfHAdvanceX = metrics.mfHAdvanceX + fLetterSpacing;
        mfPenX = mfPenX + metrics.mfHAdvanceX;
        if (mfPenX > mfPenXMax)
            mfPenXMax = mfPenX;
        mfPenX = mfPenXMax;
        prevGlyph = glyphId;
    }
}
}}  // namespace EA::Text
