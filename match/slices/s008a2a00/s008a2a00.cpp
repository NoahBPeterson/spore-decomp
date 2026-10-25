// Slice s008a2a00: EA::Text::Typesetter Arabic/Hangul/general shaping.
// Layouts: EA/Text reference headers (LineLayout +0x418, mfPenX +0x528); retail vector
// layout is begin/end/capacity + an 8-byte allocator slot + the inline fixed buffer.
#include "types.h"
#include <string.h>

inline void* operator new(size_t, void* p) { return p; }

void FreeRawBlock(void* p);                                  // 0x00f47380 (EASTL operator delete)
void* UninitializedCopyPtr(const void* first, const void* last, void* dest); // 0x00c033a0

namespace EA { namespace Text {

typedef unsigned short GlyphId;
typedef wchar_t Char;

enum {
    kCharNBSP    = 0x00A0,
    kCharSpace   = 0x0020,
    kCharLF      = 0x000A,
    kCharCR      = 0x000D,
    kCharNEL     = 0x0085,
    kCharZWSP    = 0x200B,
    kCharLSEP    = 0x2028,
    kCharPSEP    = 0x2029,
    kCharZWNBSP  = 0xFEFF,
    kCharOBJ     = 0xFFFC,
    kPMPassword  = 1,
    kCCFlagControlChar = 2,
};

enum GlyphJustificationClass { kGJCNone = 0 };

enum HangulClusterType {
    kHangulClusterTypeNone,
    kHangulClusterTypeJamo,
    kHangulClusterTypeTone,
    kHangulClusterTypeUnicode,
};

const unsigned kJamoLFiller = 0x115F;
const unsigned kJamoVFiller = 0x1160;
const unsigned kHangulTone1  = 0x302E;

#define IsS(s)                  (((unsigned)(s) - 0xAC00u) < (0xD7A4u - 0xAC00u))
#define IsJ(j)                  (((unsigned)(j) - 0x1100u) < (0x1200u - 0x1100u))
#define IsL(j)                  (((unsigned)(j) - 0x1100u) < (0x1160u - 0x1100u))
#define IsV(j)                  (((unsigned)(j) - 0x1160u) < (0x11A8u - 0x1160u))
#define IsT(j)                  (((unsigned)(j) - 0x11A8u) < (0x1200u - 0x11A8u))
#define IsTone(c)               (((unsigned)(c) - 0x302Eu) < (0x3030u - 0x302Eu))
#define IsLSyllable(j)          (((unsigned)(j) - 0x1100u) < (0x1113u - 0x1100u))
#define IsVSyllable(j)          (((unsigned)(j) - 0x1161u) < (0x1176u - 0x1161u))
#define IsTSyllable(j)          (((unsigned)(j) - 0x11A8u) < (0x11C3u - 0x11A8u))
#define HasT(s)                 (((s) - 0xAC00u) % 28)
#define GetSyllableLVT(l, v, t) (0xAC00 + (((l) - 0x1100) * 21 + ((v) - 0x1161)) * 28 + ((t) - 0x11A7))
#define GetSyllableLV(l, v)     (0xAC00 + (((l) - 0x1100) * 21 + ((v) - 0x1161)) * 28)

struct TextStyle {
    unsigned char mPad00[0x264];
    int mPasswordMode;                      // +0x264 (LayoutSettings mTextStyleDefault)
    unsigned char mPad01[0x26c - 0x268];
    float mfLetterSpacing;                  // +0x26c
    unsigned char mPad02[0x278 - 0x270];
};

struct LayoutSettings {
    unsigned char mPad00[0xf8];
    TextStyle mTextStyleDefault;            // +0xf8
    bool mbEnableAutoHyphenation;           // +0x370
    bool mbCellTopPosition;                 // +0x371
    unsigned char mPad01[2];
    float mfYScale;                         // +0x374
    bool mbEnableLigatures;                 // +0x378
    bool mbHideControlCharacters;           // +0x379
    bool mbDisplayZWG;                      // +0x37a
    unsigned char mPad02[1];
};

struct GlyphMetrics {
    float mfSizeX;                          // +0x00
    float mfSizeY;                          // +0x04
    float mfHBearingX;                      // +0x08
    float mfHBearingY;                      // +0x0c
    float mfHAdvanceX;                      // +0x10
};

struct Kerning {
    float mfX;                              // +0x00
    float mfY;                              // +0x04
};

// First dword packs GJC:4, mbGlyphIsObject:1, mClusterPosition:3, mClusterSize:3,
// mClusterBreakable:1, mCharCount:2, mDirection:1.
struct GlyphInfo {
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

struct GlyphLayoutInfo {
    union {
        struct Font* mpFont;                // +0x00
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

struct AnalysisInfo {
    TextStyle* mpTextStyle;                 // +0x00
    struct Font* mpFont;                    // +0x04
    uint32_t mScript : 7;                   // +0x08
    uint32_t mBidiClass : 5;
    int      mnBidiLevel : 4;
    uint32_t mbJoinBefore : 1;
    uint32_t mbJoinAfter : 1;
};

struct OTFGsubGpos;

class Font {
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
    virtual bool GetGlyphMetrics(GlyphId glyph, GlyphMetrics& metrics);   // +0x34, slot 13
    virtual void v14();                     // slot 14
    virtual void v15();                     // slot 15
    virtual bool GetKerning(GlyphId prev, GlyphId cur, Kerning& kerning, int direction, bool flag); // +0x40, slot 16
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual struct OTF* GetOTF();           // +0x58, slot 22
};

// ---------------------------------------------------------------------------
// Retail EASTL containers (all vectors are 0x14 bytes: begin/end/capacity plus
// an 8-byte allocator slot; the fixed vector keeps its inline buffer after the
// header, at +0x18).
// ---------------------------------------------------------------------------
class ICoreAllocator {
public:
    virtual void v00();
    virtual void v01();
    virtual void* Allocate(size_t n, int flags, unsigned debugFlags);   // vtable +0x08
    virtual void Deallocate(void* p, size_t n);                         // vtable +0x0c
};

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

struct AnalysisInfoVector : VectorBase<AnalysisInfoVector, AnalysisInfo> {
};

struct GlyphIdVector : VectorBase<GlyphIdVector, GlyphId> {
    void DoInsertValue(GlyphId* position, const GlyphId& value);        // 0x008a1900
};

struct GlyphInfoVector : VectorBase<GlyphInfoVector, GlyphInfo> {
    void DoInsertValue(GlyphInfo* position, const GlyphInfo& value);    // 0x008a1a10
};

struct GlyphLayoutVector : VectorBase<GlyphLayoutVector, GlyphLayoutInfo> {
    uint32_t GetNewCapacity(uint32_t currentCapacity) {
        return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
    }
    GlyphLayoutInfo* DoAllocate(uint32_t n) {
        return n ? (GlyphLayoutInfo*)mpAllocator->Allocate(n * sizeof(GlyphLayoutInfo), 0, mFlags) : 0;
    }
    void DoFree(GlyphLayoutInfo* p, uint32_t n) {
        if (p)
            mpAllocator->Deallocate(p, n * sizeof(GlyphLayoutInfo));
    }
    void DoInsertValue(GlyphLayoutInfo* position, const GlyphLayoutInfo& value); // @ 0x008a2fe0
};

struct UIntVector : VectorBase<UIntVector, uint32_t> {
    void DoInsertValue(uint32_t* position, const uint32_t& value);      // 0x008891f0
};

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

class LineLayout {
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

// ---------------------------------------------------------------------------
// OpenType feature lookup (retail FeatureLookup stride is 0x60).
// ---------------------------------------------------------------------------
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

struct FeatureLookup {
    uint32_t mFeatureTag;                   // +0x00
    uint32_t mGlyphFlags;                   // +0x04
    unsigned char mLookupPtrArray[0x58];    // +0x08 (retail OTFLookupPtrArray16)
};

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

struct OTFTagStruct {
    uint32_t mOTFTag;                       // +0x00
    OTFTagStruct(uint32_t tag = 0) : mOTFTag(tag) {}
};

struct OTFGsubGpos {
    void BuildFeatureLookup(const OTFTagStruct& script, const OTFTagStruct& language,
                            FeatureLookupArray& array) const;    // 0x008a11c0
};

struct OTF {
    unsigned char mPad00[0xe8];
    OTFGsubGpos mGsub;                      // +0xe8
    bool IsScriptSupported(const char* pScript, const char* pLanguage) const; // 0x0089f400
};

struct Item {
    int mType;                              // +0x00
    unsigned mIndex;                        // +0x04
    unsigned mCount;                        // +0x08
    TextStyle* mpStyle;                     // +0x0c
    union {
        struct {
            void* mpObjectPtr;              // +0x10
            GlyphMetrics mGlyphMetrics;     // +0x14
            bool mbBindPrev;                // +0x28
            bool mbBindNext;                // +0x29
        } mObject;
    };
};

// ---------------------------------------------------------------------------
// Free functions and helpers implemented in other retail objects.
// ---------------------------------------------------------------------------
bool IsCharZeroWidth(Char c);                                       // 0x00885c20
bool IsCharCategory(Char c, int nCharCategoryFlags);                // 0x00888090
Char GetMirrorChar(Char c);                                         // 0x0089e110
void AssignArabicCharProperties(const Char* pText, unsigned nTextLength,
                                GlyphInfo* pGlyphInfo);             // 0x008a1680
void DoGlyphSubstitution(LineLayout& lineLayout, unsigned iGlyphBegin,
                         const FeatureLookupArray& featureLookupArray,
                         const OTF* pOTF);                          // 0x008a2120

class Typesetter {
public:
    void PlaceGeneralGlyphCluster(unsigned charIndex, unsigned charCount);
    void SetGlyphLayoutInfo(GlyphLayoutInfo& info, float x, const GlyphMetrics& metrics);   // 0x00897830
    void GetObjectMetrics(unsigned index, GlyphMetrics& metrics);                          // 0x00898300
    unsigned GetGlyphsForChar(const Char* pChar, unsigned count, const AnalysisInfo* pAnalysisInfo,
                              GlyphId* pGlyphIdArray, unsigned& glyphIdCount,
                              const Char* pFallbackOptions, unsigned fallbackOptionCount);  // 0x00897790
    Item* GetScheduleItemFromCharIndex(unsigned charIndex, bool lineRelative);             // 0x008982c0
    void ShapeGeneral(unsigned iCharBegin, unsigned iCharEnd);                             // 0x008a3430
    void AppendArabicGlyphCluster(unsigned iCharBegin, unsigned charCount,
                                  const Char* pCharCluster, unsigned charClusterSize,
                                  const GlyphId* pGlyphCluster, unsigned glyphClusterSize,
                                  int embeddingLevel, const OTF* pOTF);                     // 0x008a1c60
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
    LayoutSettings mLayoutSettings;         // +0x004
    unsigned char mPad00[0x3cc - 0x380];
    bool mbEllipsize;                       // +0x3cc
    unsigned char mPad01[1];
    Char mPasswordChar;                     // +0x3ce
    unsigned char mPad02[0x418 - 0x3d0];
    LineLayout mLineLayout;                 // +0x418
    unsigned char mPad03[0x528 - 0x418 - 0xb0];
    float mfPenX;                           // +0x528
    float mfPenXMax;                        // +0x52c
};

// ---------------------------------------------------------------------------
// SetupArabicGsubLookup
// ---------------------------------------------------------------------------
// @ 0x008a2a00
void SetupArabicGsubLookup(FeatureLookupArray& featureLookupArray, const OTF* pOTF)
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

// ---------------------------------------------------------------------------
// ShapeArabic
// ---------------------------------------------------------------------------
// @ 0x008a2b10
void Typesetter::ShapeArabic(unsigned iCharBegin, unsigned iCharEnd)
{
    const OTF* const pOTF = mLineLayout.mAnalysisInfoArray[0].mpFont->GetOTF();

    if (pOTF && pOTF->IsScriptSupported("arab", 0)) {
        const unsigned iGlyphBegin = mLineLayout.GetGlyphIndexFromCharIndex(iCharBegin);

        for (unsigned i = iCharBegin, charCount = 0; i < iCharEnd; i += charCount) {
            const AnalysisInfo* const pAnalysisInfo = &mLineLayout.mAnalysisInfoArray[i];

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

// ---------------------------------------------------------------------------
// GetGeneralCharCluster
// ---------------------------------------------------------------------------
// @ 0x008a2ee0
unsigned Typesetter::GetGeneralCharCluster(unsigned iCharBegin, unsigned iCharEnd,
                                           Char* pCharCluster, unsigned& clusterSize)
{
    (void)iCharEnd;

    Char c = mLineLayout.mCharArray[iCharBegin];
    const bool bZW = IsCharZeroWidth(c);

    if (mLayoutSettings.mTextStyleDefault.mPasswordMode == kPMPassword) {
        c = mPasswordChar;
    } else if (c == kCharNBSP) {
        c = kCharSpace;
    } else if (bZW && mLayoutSettings.mbDisplayZWG) {
        c = '_';
    } else if ((c == kCharLF) || (c == kCharCR) || (c == kCharPSEP) ||
               (c == kCharNEL) || (c == kCharLSEP)) {
        c = kCharZWSP;
    } else if (mLayoutSettings.mbHideControlCharacters && IsCharCategory(c, kCCFlagControlChar)) {
        c = kCharZWNBSP;
    } else if (mLineLayout.mAnalysisInfoArray[iCharBegin].mnBidiLevel % 2) {
        c = GetMirrorChar(c);
    }

    clusterSize = 1;
    pCharCluster[0] = c;
    return 1;
}

// ---------------------------------------------------------------------------
// GlyphLayoutVector::DoInsertValue -- retail eastl::vector<GlyphLayoutInfo>
// insertion helper (0x20-byte elements).
// ---------------------------------------------------------------------------
// @ 0x008a2fe0
void GlyphLayoutVector::DoInsertValue(GlyphLayoutInfo* position, const GlyphLayoutInfo& value)
{
    if (mpEnd != mpCapacity) {
        const GlyphLayoutInfo* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;

        ::new((void*)mpEnd) GlyphLayoutInfo(*(mpEnd - 1));

        GlyphLayoutInfo* pDst = mpEnd;
        GlyphLayoutInfo* pSrc = pDst - 1;
        while (pSrc != position) {
            --pSrc;
            --pDst;
            *pDst = *pSrc;
        }

        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize  = GetNewCapacity(nPrevSize);
        GlyphLayoutInfo* const pNewData = DoAllocate(nNewSize);

        GlyphLayoutInfo* pNewEnd =
            (GlyphLayoutInfo*)UninitializedCopyPtr(mpBegin, position, pNewData);
        ::new((void*)pNewEnd) GlyphLayoutInfo(value);
        pNewEnd = (GlyphLayoutInfo*)UninitializedCopyPtr(position, mpEnd, ++pNewEnd);

        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));

        mpBegin    = pNewData;
        mpEnd      = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------
// AppendGeneralGlyphCluster
// ---------------------------------------------------------------------------
// @ 0x008a3110
void Typesetter::AppendGeneralGlyphCluster(unsigned iCharBegin, unsigned charCount,
                                           const Char* pCharCluster, unsigned charClusterSize,
                                           const GlyphId* pGlyphCluster, unsigned glyphClusterSize,
                                           int embeddingLevel)
{
    (void)charClusterSize;

    const unsigned glyphArrayIndexEnd = mLineLayout.mGlyphArray.size();

    while (mLineLayout.mGlyphIndexArray.size() < (iCharBegin + charCount))
        mLineLayout.mGlyphIndexArray.push_back(glyphArrayIndexEnd);

    for (unsigned g = 0; g < glyphClusterSize; ++g) {
        const GlyphId glyphId = pGlyphCluster[g];
        Font* const pFont = mLineLayout.mAnalysisInfoArray[iCharBegin].mpFont;

        mLineLayout.mGlyphArray.push_back(glyphId);

        mLineLayout.mGlyphInfoArray.push_back();
        GlyphInfo& gi = mLineLayout.mGlyphInfoArray.back();

        mLineLayout.mGlyphLayoutInfoArray.push_back();
        GlyphLayoutInfo& gli = mLineLayout.mGlyphLayoutInfoArray.back();

        gi.mGJC = kGJCNone;
        gi.mClusterPosition = g;
        gi.mClusterSize = glyphClusterSize;
        gi.mClusterBreakable = 0;
        gi.mCharCount = charCount;
        gi.mDirection = embeddingLevel;

        if (*pCharCluster != kCharOBJ) {
            gli.mpFont = pFont;
            gi.mbGlyphIsObject = 0;
        } else {
            const Item* const pItem = GetScheduleItemFromCharIndex(iCharBegin, true);
            gli.mpObject = pItem->mObject.mpObjectPtr;
            gi.mbGlyphIsObject = 1;
        }

        mLineLayout.mCharIndexArray.push_back(iCharBegin);
    }
}

// ---------------------------------------------------------------------------
// AppendHangulCharCluster
// ---------------------------------------------------------------------------
// @ 0x008a3480
unsigned Typesetter::AppendHangulCharCluster(unsigned iCharBegin, unsigned charCount,
                                             const Char* pCharCluster, unsigned clusterSize,
                                             int clusterType)
{
    const AnalysisInfo* const pAnalysisInfo = &mLineLayout.mAnalysisInfoArray[iCharBegin];
    GlyphId pGlyphIdArray[32];
    unsigned glyphCount = 0;
    unsigned charsEaten = 0;

    if (mLayoutSettings.mTextStyleDefault.mPasswordMode == kPMPassword) {
        GetGlyphsForChar(&mPasswordChar, 1, pAnalysisInfo, pGlyphIdArray, glyphCount, 0, 0);
        charsEaten = clusterSize;
    } else {
        switch (clusterType) {
            case kHangulClusterTypeJamo: {
                const Char cTone = pCharCluster[clusterSize - 1];
                const bool bAppendTone = IsTone(cTone);
                unsigned syllableLength;
                Char c;

                if (bAppendTone)
                    --clusterSize;

                if ((clusterSize >= 3) && IsLSyllable(pCharCluster[0]) &&
                    IsVSyllable(pCharCluster[1]) && IsTSyllable(pCharCluster[2]))
                    syllableLength = 3;
                else if ((clusterSize >= 2) && IsLSyllable(pCharCluster[0]) &&
                         IsVSyllable(pCharCluster[1]))
                    syllableLength = 2;
                else
                    syllableLength = 0;

                if (syllableLength) {
                    if (syllableLength == 3)
                        c = GetSyllableLVT(pCharCluster[0], pCharCluster[1], pCharCluster[2]);
                    else
                        c = GetSyllableLV(pCharCluster[0], pCharCluster[1]);

                    GetGlyphsForChar(&c, 1, pAnalysisInfo, pGlyphIdArray + glyphCount,
                                     glyphCount, 0, 0);
                    charsEaten += syllableLength;
                }

                for (unsigned i = charsEaten; i < clusterSize; i += charsEaten) {
                    if ((pCharCluster[i] != kJamoLFiller) && (pCharCluster[i] != kJamoVFiller)) {
                        charsEaten += GetGlyphsForChar(pCharCluster + i, clusterSize - i, pAnalysisInfo,
                                                       pGlyphIdArray + glyphCount, glyphCount, 0, 0);
                    } else {
                        ++charsEaten;
                    }
                }

                if (glyphCount == 0) {
                    const Char cHangulFiller = 0x3164;
                    charsEaten += GetGlyphsForChar(&cHangulFiller, 1, pAnalysisInfo,
                                                   pGlyphIdArray + glyphCount, glyphCount,
                                                   L"\x25CB _o", 4);
                }

                if (bAppendTone) {
                    charsEaten += GetGlyphsForChar(&cTone, 1, pAnalysisInfo,
                                                   pGlyphIdArray + glyphCount, glyphCount,
                                                   (cTone == kHangulTone1) ? L"\x00b7" : L":", 1);
                }
                break;
            }

            case kHangulClusterTypeTone: {
                const Char cDottedCircle = 0x25CC;

                for (unsigned i = charsEaten; i < clusterSize; i += charsEaten) {
                    charsEaten += GetGlyphsForChar(pCharCluster + i, clusterSize - i, pAnalysisInfo,
                                                   pGlyphIdArray + glyphCount, glyphCount,
                                                   (pCharCluster[i] == kHangulTone1) ? L"\x00b7" : L":", 1);
                    GetGlyphsForChar(&cDottedCircle, 1, pAnalysisInfo,
                                     pGlyphIdArray + glyphCount, glyphCount, L"\x25CB _o", 4);
                }
                break;
            }

            case kHangulClusterTypeUnicode: {
                for (unsigned i = charsEaten; i < clusterSize; i += charsEaten) {
                    charsEaten += GetGlyphsForChar(pCharCluster + i, clusterSize - i, pAnalysisInfo,
                                                   pGlyphIdArray + glyphCount, glyphCount, 0, 0);
                }
                break;
            }
        }
    }

    AppendGeneralGlyphCluster(iCharBegin, charCount, pCharCluster, charsEaten,
                              pGlyphIdArray, glyphCount, pAnalysisInfo->mnBidiLevel);
    PlaceGeneralGlyphCluster(iCharBegin, charsEaten);
    return glyphCount;
}

// ---------------------------------------------------------------------------
// PlaceGeneralGlyphCluster (already matched; kept in retail order/fields).
// ---------------------------------------------------------------------------
// @ 0x008a2d60
void Typesetter::PlaceGeneralGlyphCluster(unsigned charIndex, unsigned charCount)
{
    TextStyle* pStyle = mLineLayout.mAnalysisInfoArray.mpBegin[charIndex].mpTextStyle;
    float fLetterSpacing = pStyle ? pStyle->mfLetterSpacing : 0.0f;

    unsigned glyphEnd;
    mLineLayout.GetGlyphRangeFromCharRange(charIndex, charIndex + charCount, charCount, glyphEnd);

    unsigned prevGlyph = 0;
    for (unsigned glyphIndex = charCount; glyphIndex < glyphEnd; ++glyphIndex) {
        GlyphId glyphId = mLineLayout.mGlyphArray.mpBegin[glyphIndex];
        GlyphInfo& glyphInfo = mLineLayout.mGlyphInfoArray.mpBegin[glyphIndex];
        GlyphLayoutInfo& layoutInfo = mLineLayout.mGlyphLayoutInfoArray.mpBegin[glyphIndex];

        if (glyphIndex != charCount && (glyphInfo.mBits & 0x10) == 0) {
            Kerning kerning;
            if (layoutInfo.mpFont->GetKerning(prevGlyph, glyphId, kerning,
                                              (int)((glyphInfo.mBits >> 14) & 1), true))
                mfPenX = mfPenX + kerning.mfX;
        }

        GlyphMetrics metrics;
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
