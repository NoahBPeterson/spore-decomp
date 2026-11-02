// src/game/UTFSpore_Win32/EATextLayout.cpp -- migrated from slice(s) s00890010, s0088f1b0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EATextLayout.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/AnalysisInfo.h"
#include "EA/Text/Font.h"
#include "EA/Text/FontServer.h"
#include "EA/Text/LayoutSettings.h"
#include "EA/Text/TextStyle.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  FreeRawBlock(void* p);                                   // 0x00f47380

// ---- items of slice s0088f1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FreeRawBlock(void* p);                                   // 0x00f47380
namespace EA {
namespace Text {
typedef uint16_t Char;
}
}
namespace EA {
namespace Text {
struct TextRun {
    wchar_t* mpText;          // +0x00
    unsigned int mnTextSize;  // +0x04
};
}
}
namespace EA {
namespace Text {
class TextRunIterator {
public:
    TextRun* mpArray;             // +0x00
    TextRun* mpArrayEnd;          // +0x04
    TextRun* mpArrayCurrent;      // +0x08
    wchar_t* mpCharCurrent;       // +0x0c
    unsigned int mnStartPosition; // +0x10
    unsigned int mnEndPosition;   // +0x14
    unsigned int mnPosition;      // +0x18

    TextRunIterator& Decrement();
    TextRunIterator& operator++();      // 0x00888160
    Char operator*() const;             // 0x008880c0
    void SetTextRunArray(const TextRun* pTextRunArray, unsigned int nTextRunCount,
                         unsigned int nTextLen, unsigned int mnStartArg,
                         unsigned int mnEndArg);                       // 0x0088f790
};
}
}
namespace EA {
namespace Text {
struct FontMetrics
{
    float mfSize;                    // +0x00
    int   mPitch;                    // +0x04
    float mfHAdvanceXMax;            // +0x08
    float mfVAdvanceYMax;            // +0x0c
    float mfAscent;                  // +0x10
    float mfDescent;                 // +0x14
    float mfLeading;                 // +0x18
    float mfBaseline;                // +0x1c
    float mfLineHeight;              // +0x20
    float mfXHeight;                 // +0x24
    float mfCapsHeight;              // +0x28
    float mfUnderlinePosition;       // +0x2c
    float mfUnderlineThickness;      // +0x30
    float mfLinethroughPosition;     // +0x34
    float mfLinethroughThickness;    // +0x38
    float mfOverlinePosition;        // +0x3c
    float mfOverlineThickness;       // +0x40
};
}
}
namespace EA {
namespace Text {
struct GlyphMetrics_s0088_f1b0
{
    float mfSizeX;      // +0x00
    float mfSizeY;      // +0x04
    float mfHBearingX;  // +0x08
    float mfHBearingY;  // +0x0c
    float mfHAdvanceX;  // +0x10
};
}
}
namespace EA {
namespace Text {
struct GlyphLayoutAttributes
{
    uint32_t mValue;    // +0x00  mGJC:4, mClusterPosition:3, mClusterSize:3, mbDiacritic:1,
                        //        mbInvisible:1, mbZeroWidth:1, plus the cluster fields above
};  // 4 bytes (the glyph id follows at +0x24)
}
}
namespace EA {
namespace Text {
struct Font_s0088_f1b0;
}
}
namespace EA {
namespace Text {
class FontSelection;
}
}
namespace EA {
namespace Text {
struct GlyphAttributes
{
    Font_s0088_f1b0*                 mpFont;      // +0x00
    float                 mfPenX;      // +0x04
    float                 mfPenY;      // +0x08
    float                 mfX1;        // +0x0c
    float                 mfY1;        // +0x10
    float                 mfX2;        // +0x14
    float                 mfY2;        // +0x18
    float                 mfAdvance;   // +0x1c
    GlyphLayoutAttributes mGLA;        // +0x20
    uint16_t              mGlyphId;    // +0x24
    uint16_t              mPad26;      // +0x26
};  // 0x28
}
}
namespace EA {
namespace Text {
struct LayoutMetrics
{
    uint32_t mnSize;          // +0x00
    float    mfSpace;         // +0x04
    uint32_t mnVisibleSize;   // +0x08
    float    mfVisibleSpace;  // +0x0c
    float    mfBaseline;      // +0x10
    float    mfDescent;       // +0x14
    uint32_t mnLineCount;     // +0x18
};
}
}
namespace EA {
namespace Text {
struct GlyphRunInfo
{
    uint32_t mnCharBegin;   // +0x00
    uint32_t mnCharEnd;     // +0x04
};
}
}
namespace EA {
namespace Text {
class Font_s0088_f1b0
{
public:
    virtual ~Font_s0088_f1b0();                                                     // +0x00
    virtual void Slot04();                                               // +0x04
    virtual void Slot08();                                               // +0x08
    virtual void Release();                                              // +0x0c 0x0088b580
    virtual void Slot10();                                               // +0x10
    virtual void Slot14();                                               // +0x14
    virtual void Slot18();                                               // +0x18
    virtual void Slot1c();                                               // +0x1c
    virtual void Slot20();                                               // +0x20
    virtual void Slot24();                                               // +0x24
    virtual void Slot28();                                               // +0x28
    virtual void Slot2c();                                               // +0x2c
    virtual bool GetFontMetrics(FontMetrics& fontMetrics) const;         // +0x30
    virtual bool GetGlyphMetrics(uint16_t glyphId, GlyphMetrics_s0088_f1b0& glyphMetrics) const;  // +0x34
    virtual bool GetGlyphs(const Char* pText, uint32_t nTextLen, uint16_t* pGlyphIdArray,
                           uint32_t nGlyphCount, uint32_t nGlyphStride); // +0x38
    virtual void Slot3c();                                               // +0x3c
    virtual bool GetGlyphProperties(uint16_t glyphId1, uint16_t glyphId2, float* pAdjustment,
                                    bool bAdjustAllowed, bool bAdvance) const;  // +0x40
};
}
}
namespace EA {
namespace Text {
class FontSelection
{
public:
    struct Node
    {
        Node* mpNodeRight;   // +0x00
        Node* mpNodeLeft;    // +0x04
        Node* mpNodeParent;  // +0x08
        char  mColor;        // +0x0c
        char  mPad0d[3];     // +0x0d
        Font_s0088_f1b0* mpFont;        // +0x10  AutoRefCount<Font> (a reference-counted Font*)
    };

    uint8_t  mCompare;       // +0x00  eastl::less<AutoRefCount<Font> >
    char     mPad01[3];      // +0x01
    Node*    mpNodeRight;    // +0x04  mAnchor.mpNodeRight
    Node*    mpNodeLeft;     // +0x08  mAnchor.mpNodeLeft (== begin())
    Node*    mpNodeParent;   // +0x0c  mAnchor.mpNodeParent (root)
    char     mColor;         // +0x10  mAnchor.mColor
    char     mPad11[3];      // +0x11
    uint32_t mnSize;         // +0x14
    Node*    mpFreeList;     // +0x18  mAllocator.mpHead
    void*    mpNext;         // +0x1c  mAllocator.mpNext
    Node*    mpPoolBegin;    // +0x20  mAllocator.mpBegin
    Node*    mpPoolEnd;      // +0x24  mAllocator.mpEnd
    uint32_t mPoolPad;       // +0x28
    char     mPool[0xe4 - 0x2c];  // fixed_node_pool node buffer

    __declspec(noinline) void DoNukeSubtree(Node* pNode);   // 0x0088fda0
    void reset();
};
}
}
namespace EA {
namespace Text {
inline void FontSelection::reset()
{
    mpNodeRight  = (Node*)(void*)&mpNodeRight;
    mpNodeLeft   = (Node*)(void*)&mpNodeRight;
    mpNodeParent = 0;
    mColor       = 0;
    mnSize       = 0;
}
}
}
namespace EA {
namespace Text {
struct TextStyle_s0088_f1b0
{
    char mPad000[0x264];     // +0x000
    int  mPasswordMode;      // +0x264 (kPMDefault = 0, kPMPassword = 1)
    char mPad268[0x278 - 0x268];
};
}
}
namespace EA {
namespace Text {
struct LayoutSettings_s0088_f1b0
{
    Char          mLocale[6];              // +0x000
    int           mScript;                 // +0x00c
    int           mDirection;              // +0x010
    FontSelection mFontSelection;          // +0x014
    TextStyle_s0088_f1b0     mTextStyleDefault;       // +0x0f8
    bool          mbEnableAutoHyphenation; // +0x370
    bool          mbCellTopPosition;       // +0x371
    char          mPad372[2];              // +0x372
    float         mfYScale;                // +0x374
    bool          mbEnableLigatures;       // +0x378
    bool          mbHideControlCharacters; // +0x379
    bool          mbDisplayZWG;            // +0x37a
    char          mPad37b;                 // +0x37b
};  // 0x37c
}
}
namespace EA {
namespace Text {
class FontDescription_s0088_f1b0
{
public:
    uint32_t mPad00[2];         // +0x00
    Char     mpFamilyName[0x20];// +0x08  inline family name, NUL terminated
};
}
}
namespace EA {
namespace Text {
class FaceSource_s0088_f1b0
{
public:
    FaceSource_s0088_f1b0*     mpNext;           // +0x00
    FaceSource_s0088_f1b0*     mpPrev;           // +0x04
    FontDescription_s0088_f1b0 mFontDescription; // +0x08  (family name at +0x10)
};
}
}
namespace EA {
namespace Text {
class Face_s0088_f1b0
{
public:
    char        mPad000[0x50];     // +0x000
    FaceSource_s0088_f1b0  mSourceListHead;   // +0x050  fixed_list<FaceSource> sentinel
};
}
}
namespace EA {
namespace Text {
class FaceMap
{
public:
    uint32_t mPad00;          // +0x00
    void*    mpBucketArray;   // +0x04
    uint32_t mnBucketCount;   // +0x08
    char     mBuffer[0x100];  // +0x0c  fixed bucket buffer / prime rehash policy

    Face_s0088_f1b0* FindFace(const Char* pFamilyName);   // 0x0088c600  find_as<wchar_t const*>
    Face_s0088_f1b0* InsertFace(const Char* pFamilyName); // 0x0088f000  DoInsertValue
};
}
}
namespace EA {
namespace Text {
struct CriticalSection
{
    uint32_t mData[6];
};
}
}
namespace EA {
namespace Text {
class FontServer_s0088_f1b0
{
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual bool GetFont(const TextStyle_s0088_f1b0* pTextStyle, FontSelection& fontSelection,
                         uint32_t maxCount, uint32_t a4, uint32_t a5, uint32_t a6);  // +0x18

    char          mPad000[0x288];   // +0x000
    FaceMap       mFaceMap;         // +0x288
    char          mPad288[0x2fb0 - 0x288 - sizeof(FaceMap)];
    CriticalSection mMutex;         // +0x2fb0

    bool AddFaceSource(const FontDescription_s0088_f1b0* pFontDescription);   // 0x0088f1b0
};
}
}
extern "C" void* EA_Text_GetFontServer(int bSomething);                                // 0x00885a60
namespace EA {
namespace Text {
struct ScriptProperties
{
    uint32_t mData[2];   // 8 bytes, written by GetScriptProperties
};
}
}
namespace EA {
namespace Text {
bool GetScriptProperties(int script, ScriptProperties* pScriptProperties, bool bSomething);  // 0x00893ed0
}
}
namespace EA {
namespace Text {
class Layout
{
public:
    LayoutSettings_s0088_f1b0 mLayoutSettings;   // +0x000 (the only member; Layout is 0x37c bytes)

    static void GetLayoutMetrics(const GlyphAttributes* pGlyphAttributes, uint32_t nGlyphCount,
                                 LayoutMetrics* pLayoutMetrics);                    // 0x0088f4e0
    static uint32_t __stdcall PlaceGlyphs(const GlyphRunInfo* pGlyphRuns, uint32_t nGlyphRunCount,
                                const uint32_t* pGlyphIndexArray, const GlyphAttributes* pGlyphAttributes,
                                uint32_t nUnused, float penX, float penY,
                                GlyphAttributes* pGlyphAttributesOut);              // 0x0088f6a0
    uint32_t GetGlyphs(const Char* pText, uint32_t nTextLen, float penX, float penY,
                       Font_s0088_f1b0* pFont, GlyphAttributes* pGlyphAttributes);             // 0x0088f860
    uint32_t ShapeGlyphs(uint32_t* pGlyphCountOut, uint32_t nTextRunCount,
                         uint32_t* pGlyphIndexArray, const TextRun* pTextRunArray,
                         uint32_t nGlyphCapacity, GlyphAttributes* pGlyphAttributes,
                         uint32_t nGlyphCount, uint32_t* pGlyphIndexArray2);        // 0x0088f9b0
    void DistributeWhitespace(const TextRun* pTextRunArray, uint32_t nTextRunCount,
                              uint32_t nCharBegin, uint32_t nCharCount,
                              const uint32_t* pGlyphIndexArray, GlyphAttributes* pGlyphAttributes,
                              uint32_t nUnused1, uint32_t nUnused2, float fSpace,
                              bool bAdjustLastLine);                                 // 0x0088fbc0
    void UpdateFontSelection(const TextStyle_s0088_f1b0* pTextStyle, Layout* pLayout,
                             FontServer_s0088_f1b0* pFontServer);                              // 0x0088ffa0
};
}
}
namespace EA {
namespace Text {
int MeasureNextSegment(TextRunIterator* pIterator, Char* pLastChar);                // 0x0088f570
}
}
// ---- items of slice s0088f1b0 end

// ---- items of slice s00890010 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl iat_floor(double);                  // 0x011e0906
namespace EA {
namespace Text {
struct FontMetrics_s0089_0010 {              // 0x44 bytes
    float mfSize;                 // +0x00
    int32_t mPitch;               // +0x04
    float mfHAdvanceXMax;         // +0x08
    float mfVAdvanceYMax;         // +0x0c
    float mfAscent;               // +0x10
    float mfDescent;              // +0x14
    float mfLeading;              // +0x18
    float mfBaseline;             // +0x1c
    uint32_t mPad20[9];           // +0x20
};
}
}
namespace EA {
namespace Text {
enum Orientation_s0089_0010 { kOrientationHorizontal_s0089_0010 = 0, kOrientationVertical_s0089_0010, kOrientationDefault_s0089_0010 = kOrientationHorizontal_s0089_0010 };
}
}
namespace EA {
namespace Text {
enum HAlignment_s0089_0010  { kHALeft_s0089_0010 = 0, kHACenter_s0089_0010, kHARight_s0089_0010, kHAJustify_s0089_0010 };
}
}
namespace EA {
namespace Text {
enum VAlignment_s0089_0010  { kVATop_s0089_0010 = 0, kVACenter_s0089_0010, kVABottom_s0089_0010 };
}
}
namespace EA {
namespace Text {
struct TextStyle_s0089_0010 {                // 0x278 bytes (only ever constructed elsewhere)
    uint32_t mData[0x8f];         // +0x000 .. FontStyle + colours + decoration flags
    int32_t  mDirection;          // +0x23c
    int32_t  mOrientation;        // +0x240
    int32_t  mHAlignment;         // +0x244
    int32_t  mVAlignment;         // +0x248
    int32_t  mJustify;            // +0x24c
    int32_t  mTextWrap;           // +0x250
    int32_t  mTextOverflow;       // +0x254
    int32_t  mEmphasisStyle;      // +0x258
    int32_t  mEmphasisPosition;   // +0x25c
    int32_t  mDigitSubstitution;  // +0x260
    int32_t  mPasswordMode;       // +0x264
    float    mfStretch;           // +0x268
    float    mfLetterSpacing;     // +0x26c
    float    mfWordSpacing;       // +0x270
    float    mfLineSpace;         // +0x274
};
}
}
namespace EA {
namespace Text {
struct Font_s0089_0010;
}
}
namespace EA {
namespace Text {
struct FontNode {                 // eastl rbtree node, 20 bytes
    FontNode* mpNodeRight;        // +0x00
    FontNode* mpNodeLeft;         // +0x04
    FontNode* mpNodeParent;       // +0x08
    bool      mbColor;            // +0x0c (padded to 4)
    Font_s0089_0010*     mpFont;             // +0x10 (EA::AutoRefCount<Font>)
};
}
}
namespace EA {
namespace Text {
struct FontTreeAnchor {           // 16 bytes
    FontNode* mpNodeRight;        // +0x00
    FontNode* mpNodeLeft;         // +0x04
    FontNode* mpNodeParent;       // +0x08
    bool      mbColor;            // +0x0c (padded to 4)
};
}
}
namespace EA {
namespace Text {
struct FontSelection_s0089_0010 {
    uint32_t       mCompare;      // +0x00
    FontTreeAnchor mAnchor;       // +0x04
    uint32_t       mnSize;        // +0x14
    void*          mpPoolHead;    // +0x18
    void*          mpPoolNext;    // +0x1c
    void*          mpPoolBegin;   // +0x20
    void*          mpPoolEnd;     // +0x24
    uint32_t       mnNodeSize;    // +0x28
    uint32_t       mBuffer[0x2d]; // +0x2c (9 * 20 bytes)

    FontNode* begin() const { return (FontNode*)mAnchor.mpNodeLeft; }
    FontNode* end() const { return (FontNode*)&mAnchor; }
    void DoNukeSubtree(FontNode* pNode);                     // 0x0088fda0
    void clear()
    {
        DoNukeSubtree((FontNode*)mAnchor.mpNodeParent);
        mAnchor.mpNodeRight = (FontNode*)&mAnchor;
        mAnchor.mpNodeLeft = (FontNode*)&mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mbColor = 0;
        mnSize = 0;
    }
    ~FontSelection_s0089_0010() { DoNukeSubtree((FontNode*)mAnchor.mpNodeParent); }
};
}
}
namespace EA {
namespace Text {
struct FontServer_s0089_0010 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
    virtual int GetFonts(const TextStyle_s0089_0010* pStyle, FontSelection_s0089_0010* pOut,
                         int32_t script, int32_t a, int32_t b, int32_t c);   // +0x18
};
}
}
namespace EA {
namespace Text {
struct Font_s0089_0010 {
virtual void f0();
virtual void f1();
virtual void f2();
virtual void f3();
virtual void f4();
virtual void f5();
virtual void f6();
virtual void f7();
virtual void f8();
virtual void f9();
virtual void f10();
virtual void f11();
    virtual bool GetFontMetrics(FontMetrics_s0089_0010* pOut);          // +0x30
};
}
}
namespace EA {
namespace Text {
FontNode* RBTreeIncrement(FontNode* pNode);                  // 0x00921580
}
}
namespace EA {
namespace Text {
FontServer_s0089_0010* GetFontServer(bool bCreate);                     // 0x00885a60
}
}
namespace EA {
namespace Text {
struct LayoutSettings_s0089_0010 {           // 0x37c bytes
    wchar_t mLocale[6];           // +0x000
    int32_t mScript;              // +0x00c
    int32_t mDirection;           // +0x010
    FontSelection_s0089_0010 mFontSelection; // +0x014
    bool mbDynamicFontSelection;  // +0x0f4
    TextStyle_s0089_0010 mTextStyleDefault;  // +0x0f8
    bool mbEnableAutoHyphenation; // +0x370
    bool mbCellTopPosition;       // +0x371
    float mfYScale;               // +0x374
    bool mbEnableLigatures;       // +0x378
    bool mbHideControlCharacters; // +0x379
    bool mbDisplayZWG;            // +0x37a

    LayoutSettings_s0089_0010();                                        // 0x0089b010
};
}
}
namespace EA {
namespace Text {
struct TextState {                        // one 32-bit word, 7 live bits
    int mnLevel                 : 4;      // +0x00
    int mbForcedDirection       : 1;
    int mbSwapInhibited         : 1;
    int mbDisableNationalDigits : 1;
};
}
}
namespace EA {
namespace Text {
struct Analysis {                         // 16 bytes
    uint32_t  mnPosition;                 // +0x00
    uint32_t  mnLength;                   // +0x04
    TextState mTextState;                 // +0x08
    uint32_t  mScript        : 7;         // +0x0c
    uint32_t  mnParity       : 1;
    uint32_t  mnParentParity : 1;
    uint32_t  mbJoinBefore   : 1;
    uint32_t  mbJoinAfter    : 1;
};
}
}
namespace EA {
namespace Text {
struct AnalysisArray {                    // eastl::vector<Analysis>, 24 bytes
    Analysis*   mpBegin;                  // +0x00
    Analysis*   mpEnd;                    // +0x04
    Analysis*   mpCapacity;               // +0x08
    const char* mpName;                   // +0x0c
    int32_t     mFlags;                   // +0x10
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    Analysis&    back() { return mpEnd[-1]; }
    void         resize(unsigned int nNewSize);   // 0x00890490
};
}
}
namespace EA {
namespace Text {
struct AnalysisInfo_s0089_0010 {                     // 8 bytes
    const TextStyle_s0089_0010* mpTextStyle;         // +0x00
    Font_s0089_0010*            mpFont;              // +0x04
};
}
}
namespace EA {
namespace Text {
struct RunInfo_s0089_0010 {                          // 16 bytes
    int32_t mScript;                      // +0x00
    int32_t mnBidiLevel;                  // +0x04
    int32_t mnCharBegin;                  // +0x08
    int32_t mnCharEnd;                    // +0x0c
};
}
}
namespace EA {
namespace Text {
struct RunInfoArray {                     // eastl::vector<RunInfo>, 24 bytes
    RunInfo_s0089_0010*    mpBegin;                  // +0x00
    RunInfo_s0089_0010*    mpEnd;                    // +0x04
    RunInfo_s0089_0010*    mpCapacity;               // +0x08
    const char* mpName;                   // +0x0c
    int32_t     mFlags;                   // +0x10
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    void clear() { mpEnd = mpBegin; }
};
}
}
namespace EA {
namespace Text {
struct Cluster {                          // 16 bytes
    uint32_t mnCharBegin;                 // +0x00
    uint32_t mnCharCount;                 // +0x04
    uint32_t mnX;                         // +0x08
    uint32_t mnY;                         // +0x0c
};
}
}
namespace EA {
namespace Text {
struct ClusterArray {                     // eastl::vector<Cluster>, 24 bytes
    Cluster*    mpBegin;                  // +0x00
    Cluster*    mpEnd;                    // +0x04
    Cluster*    mpCapacity;               // +0x08
    const char* mpName;                   // +0x0c
    int32_t     mFlags;                   // +0x10
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
};
}
}
namespace EA {
namespace Text {
class TextRunIterator_s0089_0010 {
public:
    TextRun*     mpArray;                 // +0x00
    TextRun*     mpArrayEnd;              // +0x04
    TextRun*     mpArrayCurrent;          // +0x08
    wchar_t*     mpCharCurrent;           // +0x0c
    unsigned int mnStartPosition;         // +0x10
    unsigned int mnEndPosition;           // +0x14
    unsigned int mnPosition;              // +0x18

    TextRunIterator_s0089_0010& operator++();                                        // 0x0088f570
    TextRun&         operator*();                                         // 0x0088f480
    void Restore(const TextRunIterator_s0089_0010& src) {
        mpArray = src.mpArray; mpArrayEnd = src.mpArrayEnd; mpArrayCurrent = src.mpArrayCurrent;
        mpCharCurrent = src.mpCharCurrent; mnStartPosition = src.mnStartPosition;
        mnEndPosition = src.mnEndPosition; mnPosition = src.mnPosition;
    }
    void SetTextRunArray(const TextRun* pRuns, unsigned int nCount,
                         unsigned int nStart, unsigned int nPos,
                         unsigned int nMax, unsigned int nEnd);           // 0x0088f790
};
}
}
namespace EA {
namespace Text {
struct GlyphAttributes_s0089_0010 {                  // 40 bytes in this build
    Font_s0089_0010*    mpFont;                      // +0x00
    float    mfPenX;                      // +0x04
    float    mfPenY;                      // +0x08
    float    mfX1;                        // +0x0c
    float    mfY1;                        // +0x10
    float    mfX2;                        // +0x14
    float    mfY2;                        // +0x18
    float    mfAdvance;                   // +0x1c
    uint16_t mGLA;                        // +0x20
    uint16_t mPad22;                      // +0x22
    uint32_t mGlyphId;                    // +0x24
};
}
}
namespace EA {
namespace Text {
struct GlyphAdvanceSlot {                 // 40 bytes
    float    mfValue;                     // +0x00
    uint32_t mPad[9];                     // +0x04
};
}
}
namespace EA {
namespace Text {
extern int32_t           g_glyphIndex[];      // 0x016519cc (char -> glyph id, -1 = none)
}
}
namespace EA {
namespace Text {
extern GlyphAttributes_s0089_0010   g_glyphAttributes[]; // 0x016539d0 (shaped glyphs, stride 0x28)
}
}
namespace EA {
namespace Text {
extern GlyphAdvanceSlot  g_glyphAdvance[];    // 0x016539c4 (per-glyph advance, stride 0x28)
}
}
namespace EA {
namespace Text {
extern int32_t           g_glyphClusters[];   // 0x016529d0 (glyph -> cluster end, stride 4)
}
}
namespace EA {
namespace Text {
extern RunInfoArray      g_runInfoLine;       // 0x01667a18 (line run list)
}
}
namespace EA {
namespace Text {
extern ClusterArray      g_runInfoPara;       // 0x01667a04 (paragraph cluster list)
}
}
namespace EA {
namespace Text {
extern TextStyle_s0089_0010         g_textStyleScratch;  // 0x0165d9d0 (scratch style / glyph out buffer)
}
}
namespace EA {
namespace Text {
extern uint8_t           g_csText[];          // 0x016679d0 (CRITICAL_SECTION)
}
}
namespace EA {
namespace Text {
__declspec(dllimport) void __stdcall EnterCriticalSection(void*);
}
}
namespace EA {
namespace Text {
__declspec(dllimport) void __stdcall LeaveCriticalSection(void*);
}
}
namespace EA {
namespace Text {
const int kScriptDefault = 0x1e;
}
}
namespace EA {
namespace Text {
typedef wchar_t wchar16;
}
}
namespace EA {
namespace Text {
struct Layout_s0089_0010;                            // 0x37c bytes
}
}
namespace EA {
namespace Text {
struct Layout_s0089_0010 {
    LayoutSettings_s0089_0010 mLayoutSettings;
    Layout_s0089_0010();
    float GetMaxBaseline(const TextStyle_s0089_0010* pStyle);           // 0x00890d20
    float GetMinDescent(const TextStyle_s0089_0010* pStyle);            // 0x00890e20
    int   AnalyzeText(const AnalysisInfo_s0089_0010* pInfo, int nCount,
                      AnalysisArray* pOut, int unused);      // 0x00890500
    int   LayoutTextLine(int a1, int a2, float fX, float fY,
                         const TextStyle_s0089_0010* pStyle, GlyphAttributes_s0089_0010* pGlyphs,
                         unsigned int nMaxGlyphs, LayoutMetrics* pMetrics);  // 0x00890570
    unsigned int LayoutText(const TextRun* pRuns, int nRuns, unsigned int nStart,
                            unsigned int nEnd, const int32_t* pGlyphIndex,
                            ClusterArray* pClusters, GlyphAdvanceSlot* pAdvances,
                            int32_t* pGlyphClusters, float fLineWidth,
                            unsigned int* pLineEnds, unsigned int nMaxLines,
                            float* pLineWidths);                 // 0x00890010
    int   LayoutTextParagraph(int a2, int a3, float fX1, float fY1, float fX2,
                              float fY2, const TextStyle_s0089_0010* pStyle, int a9,
                              unsigned int nMaxGlyphs, LayoutMetrics* pOut);  // 0x00890830
    float GetTextLayoutMetrics(int a1, int a2, const TextStyle_s0089_0010* pStyle,
                               LayoutMetrics* pOut);             // 0x00890cc0
};
}
}
namespace EA {
namespace Text {
unsigned int ShapeGlyphs(Layout_s0089_0010* pLayout, const AnalysisInfo_s0089_0010* pInfo, int nInfo,
                         const int32_t* pGlyphIndex, RunInfo_s0089_0010* pRuns, unsigned int nRuns,
                         GlyphAttributes_s0089_0010* pGlyphs, unsigned int nMaxGlyphs,
                         int32_t* pGlyphClusters);                       // 0x0088f9b0
}
}
namespace EA {
namespace Text {
unsigned int PlaceGlyphs(RunInfo_s0089_0010* pRuns, unsigned int nRuns,
                         const int32_t* pGlyphIndex, GlyphAttributes_s0089_0010* pGlyphs,
                         unsigned int nMaxGlyphs, float fPenX, float fPenY,
                         int nGlyphBase);                                // 0x0088f6a0
}
}
namespace EA {
namespace Text {
void GlyphMetrics(GlyphAttributes_s0089_0010* pGlyphs, unsigned int nGlyphCount, void* pOut);  // 0x0088f4e0
}
}
namespace EA {
namespace Text {
void JustifyGlyphs(const AnalysisInfo_s0089_0010* pInfo, int nInfo, int a3, int a4,
                   const int32_t* pGlyphIndex, GlyphAttributes_s0089_0010* pGlyphs,
                   unsigned int nMaxGlyphs, int32_t* pGlyphClusters, float fAmount,
                   int a10);                                             // 0x0088fbc0
}
}
namespace EA {
namespace Text {
bool IsSpace(wchar16 c, unsigned int a2, bool a3);                       // 0x0089e0e0
}
}
namespace EA {
namespace Text {
template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
}
}
namespace EA {
namespace Text {
template <class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
}
}
// ---- items of slice s00890010 end

// @ 0x0088f420
EA::Text::TextRunIterator& EA::Text::TextRunIterator::Decrement()
{
    if (mnPosition > mnStartPosition)
    {
        --mpCharCurrent;
        if (mpCharCurrent < mpArrayCurrent->mpText)
        {
            --mpArrayCurrent;
            while (mpArrayCurrent >= mpArray && mpArrayCurrent->mnTextSize == 0)
                --mpArrayCurrent;
            if (mpArrayCurrent >= mpArray)
            {
                mpCharCurrent = mpArrayCurrent->mpText + (mpArrayCurrent->mnTextSize - 1);
            }
            else
            {
                mpArrayCurrent = mpArray;
                mpCharCurrent = mpArray->mpText - 1;
                mnPosition = 0;
                return *this;
            }
        }
        --mnPosition;
    }
    return *this;
}

// @ 0x0088f4e0
namespace EA { namespace Text {
void EA::Text::Layout::GetLayoutMetrics(const GlyphAttributes* pGlyphAttributes, uint32_t nGlyphCount, LayoutMetrics* pLayoutMetrics)
{
    FontMetrics fontMetrics;
    const Font_s0088_f1b0* pFontLast = 0;
    const GlyphAttributes* const pGlyphAttributesEnd = pGlyphAttributes + nGlyphCount;

    fontMetrics.mfSize = 0.0f;
    pLayoutMetrics->mfBaseline = 0.f;
    pLayoutMetrics->mfDescent  = 0.f;

    while (pGlyphAttributes < pGlyphAttributesEnd)
    {
        const Font_s0088_f1b0* const pFont = pGlyphAttributes->mpFont;

        if (pFontLast != pFont)
        {
            pFontLast = pFont;
            pFont->GetFontMetrics(fontMetrics);
        }

        if (fontMetrics.mfBaseline > pLayoutMetrics->mfBaseline)
            pLayoutMetrics->mfBaseline = fontMetrics.mfBaseline;

        if (pLayoutMetrics->mfDescent > fontMetrics.mfDescent)
            pLayoutMetrics->mfDescent = fontMetrics.mfDescent;

        ++pGlyphAttributes;
    }
}
}}  // namespace EA::Text

// @ 0x0088f570
namespace EA { namespace Text {
int EA::Text::MeasureNextSegment(TextRunIterator* pIterator, Char* pLastChar)
{
    int nLength = 0;

    if (pIterator->mnPosition != pIterator->mnEndPosition)
    {
        Char c = (pIterator->mnPosition < pIterator->mnEndPosition) ? *pIterator->mpCharCurrent : (Char)0xffff;
        ++(*pIterator);
        nLength = 1;

        bool bLineBreak = (c == '\n') || (c == 0x2029);
        bool bSpace     = (c == ' ')  || (c == '-');
        Char cCurrent   = c;

        if (pIterator->mnPosition != pIterator->mnEndPosition)
        {
            while (cCurrent != 0x0e46)   // Thai: not a segment break point
            {
                c = **pIterator;
                ++(*pIterator);

                const bool bLineBreakNext = (c == '\n') || (c == 0x2029);
                const bool bSpaceNext     = (c == ' ')  || (c == '-');

                if (bLineBreak || bLineBreakNext)
                {
                    ++nLength;
                    cCurrent = c;
                    break;
                }

                if (bSpace && !bSpaceNext)
                {
                    pIterator->Decrement();
                    *pLastChar = cCurrent;
                    return nLength;
                }

                ++nLength;
                bLineBreak = false;
                cCurrent   = c;
                bSpace     = bSpaceNext;

                if (pIterator->mnPosition == pIterator->mnEndPosition)
                {
                    *pLastChar = cCurrent;
                    return nLength;
                }
            }
        }

        *pLastChar = cCurrent;
    }

    return nLength;
}
}}  // namespace EA::Text

// @ 0x0088f860
namespace EA { namespace Text {
uint32_t EA::Text::Layout::GetGlyphs(const Char* pText, uint32_t nTextLen, float penX, float penY, Font_s0088_f1b0* pFont, GlyphAttributes* pGlyphAttributes)
{
    if (!pFont && mLayoutSettings.mFontSelection.mnSize)
        pFont = mLayoutSettings.mFontSelection.mpNodeLeft->mpFont;

    const float fYScale = mLayoutSettings.mfYScale;

    if (mLayoutSettings.mbCellTopPosition)
    {
        FontMetrics fontMetrics;
        fontMetrics.mfSize = 0.f;
        pFont->GetFontMetrics(fontMetrics);
        penY += fYScale * fontMetrics.mfBaseline;
    }

    pFont->GetGlyphs(pText, nTextLen, &pGlyphAttributes->mGlyphId, 1, (uint32_t)sizeof(GlyphAttributes));

    uint32_t nGlyphCount = nTextLen;

    if (pText < pText + nTextLen)
    {
        uint32_t nCount = ((uint32_t)((pText + nTextLen) - pText) - 1) / 2 + 1;

        do
        {
            GlyphMetrics_s0088_f1b0 glyphMetrics;

            pGlyphAttributes->mpFont = pFont;
            pFont->GetGlyphMetrics(pGlyphAttributes->mGlyphId, glyphMetrics);

            pGlyphAttributes->mfX1 = glyphMetrics.mfHBearingX + penX;
            pGlyphAttributes->mfX2 = pGlyphAttributes->mfX1 + glyphMetrics.mfSizeX;
            pGlyphAttributes->mfPenY = penY;
            pGlyphAttributes->mfPenX = penX;
            pGlyphAttributes->mfY1 = penY - glyphMetrics.mfHBearingY * fYScale;
            pGlyphAttributes->mfY2 = pGlyphAttributes->mfY1 + glyphMetrics.mfSizeY * fYScale;
            pGlyphAttributes->mfAdvance = glyphMetrics.mfHAdvanceX;
            pGlyphAttributes->mGLA.mValue = 0;

            ++pGlyphAttributes;
            penX += glyphMetrics.mfHAdvanceX;
        } while (--nCount);
    }

    return nGlyphCount;
}
}}  // namespace EA::Text

// @ 0x0088f9b0
namespace EA { namespace Text {
uint32_t EA::Text::Layout::ShapeGlyphs(uint32_t* pGlyphCountOut, uint32_t nTextRunCount, uint32_t* pGlyphIndexArray, const TextRun* pTextRunArray, uint32_t nGlyphCapacity, GlyphAttributes* pGlyphAttributes, uint32_t nGlyphCount, uint32_t* pGlyphIndexArray2)
{
    uint32_t nGlyph = 0;

    TextRunIterator iterator;
    iterator.SetTextRunArray(pTextRunArray, nTextRunCount, 0, 0, 0xffffffff);

    if (iterator.mnPosition != iterator.mnEndPosition)
    {
        Font_s0088_f1b0* const pFont = mLayoutSettings.mFontSelection.mpNodeLeft->mpFont;
        GlyphAttributes* pGlyph = pGlyphAttributes;

        for (;;)
        {
            Char c = (iterator.mnPosition < iterator.mnEndPosition) ? *iterator.mpCharCurrent : (Char)0xffff;

            if (nGlyph < nGlyphCount)
            {
                if (mLayoutSettings.mTextStyleDefault.mPasswordMode == 1)
                    c = 0x25cf;   // BULLET

                pFont->GetGlyphs(&c, 1, &pGlyph->mGlyphId, 1, 2);

                GlyphMetrics_s0088_f1b0 glyphMetrics;
                pFont->GetGlyphMetrics(pGlyph->mGlyphId, glyphMetrics);

                pGlyph->mpFont = pFont;
                pGlyph->mfPenX = 0.f;
                pGlyph->mfPenY = 0.f;
                pGlyph->mfX1 = glyphMetrics.mfHBearingX;
                pGlyph->mfY1 = -(mLayoutSettings.mfYScale * glyphMetrics.mfHBearingY);
                pGlyph->mfX2 = glyphMetrics.mfHBearingX + glyphMetrics.mfSizeX;
                pGlyph->mfY2 = -((glyphMetrics.mfHBearingY - glyphMetrics.mfSizeY) * mLayoutSettings.mfYScale);
                pGlyph->mfAdvance = glyphMetrics.mfHAdvanceX;
                pGlyph->mGLA.mValue = (pGlyph->mGLA.mValue & 0xfffff880u) | 0x80u;
                pGlyph->mGLA.mValue = (pGlyph->mGLA.mValue & 0xffffe7ffu) |
                                      ((c == ' ') ? 0x0800u : 0u);

                *pGlyphIndexArray = nGlyph;
                ++pGlyphIndexArray;

                if (pGlyphIndexArray2)
                {
                    *pGlyphIndexArray2 = nGlyph;
                    ++pGlyphIndexArray2;
                }
            }

            ++nGlyph;
            ++pGlyph;
            ++iterator;

            if ((iterator.mnPosition < iterator.mnEndPosition) && (*iterator.mpCharCurrent != 0xffff))
                continue;

            break;
        }

        uint32_t nAdjustCount = (nGlyph <= nGlyphCount) ? nGlyph : nGlyphCount;
        --nAdjustCount;

        if (nAdjustCount)
        {
            GlyphAttributes* pAdjust = pGlyphAttributes;

            do
            {
                float fAdjustment;

                if (pFont->GetGlyphProperties(pAdjust[1].mGlyphId, pAdjust[0].mGlyphId, &fAdjustment, 0, 1))
                    pAdjust->mfAdvance += fAdjustment;

                ++pAdjust;
            } while (--nAdjustCount);
        }
    }

    *pGlyphCountOut = nGlyph;

    if (pGlyphIndexArray2 && nGlyph < nGlyphCapacity)
        *pGlyphIndexArray2 = nGlyph;

    return nGlyph;
}
}}  // namespace EA::Text

// @ 0x0088fbc0
namespace EA { namespace Text {
void EA::Text::Layout::DistributeWhitespace(const TextRun* pTextRunArray, uint32_t nTextRunCount, uint32_t nCharBegin, uint32_t nCharCount, const uint32_t* pGlyphIndexArray, GlyphAttributes* pGlyphAttributes, uint32_t, uint32_t, float fSpace, bool bAdjustLastLine)
{
    ScriptProperties scriptProperties;
    GetScriptProperties(mLayoutSettings.mScript, &scriptProperties, true);

    TextRunIterator iterator;
    iterator.SetTextRunArray(pTextRunArray, nTextRunCount, nCharBegin, 0, 0xffffffff);

    uint32_t pSpaceIndexArray[256];
    uint32_t nSpaceCount = 0;

    for (uint32_t i = nCharBegin; i < nCharBegin + nCharCount; ++i)
    {
        const Char c = (iterator.mnPosition < iterator.mnEndPosition) ? *iterator.mpCharCurrent : (Char)0xffff;
        ++iterator;

        if (c == ' ' && nSpaceCount < 256)
            pSpaceIndexArray[nSpaceCount++] = i;
    }

    if (bAdjustLastLine)
    {
        uint32_t iGlyph = pGlyphIndexArray[nCharBegin];
        const uint32_t iGlyphEnd = pGlyphIndexArray[nCharBegin + nCharCount - 1] + 1;

        if (iGlyph < iGlyphEnd)
        {
            float fAdvanceSum = 0.f;

            for (; iGlyph < iGlyphEnd; ++iGlyph)
            {
                const float fAdvance = pGlyphAttributes[iGlyph].mfAdvance;

                if (fAdvance > 0.f)
                    fAdvanceSum += fAdvance;
            }

            (void)fAdvanceSum;
        }

        fSpace *= 0.f;
    }

    const float fSpaceExtra = fSpace / (float)nSpaceCount;

    for (uint32_t i = 0; i < nSpaceCount; ++i)
        pGlyphAttributes[pGlyphIndexArray[pSpaceIndexArray[i]]].mfAdvance += fSpaceExtra;
}
}}  // namespace EA::Text

// @ 0x0088fda0
namespace EA { namespace Text {
void EA::Text::FontSelection::DoNukeSubtree(Node* pNode)
{
    while (pNode)
    {
        DoNukeSubtree(pNode->mpNodeRight);

        Node* const pNodeLeft = pNode->mpNodeLeft;

        if (pNode->mpFont)
            pNode->mpFont->Release();

        if ((pNode < mpPoolBegin) || (pNode >= mpPoolEnd))
        {
            FreeRawBlock(pNode);
        }
        else
        {
            pNode->mpNodeRight = mpFreeList;
            mpFreeList = pNode;
        }

        pNode = pNodeLeft;
    }
}
}}  // namespace EA::Text

// @ 0x0088ffa0
namespace EA { namespace Text {
void EA::Text::Layout::UpdateFontSelection(const TextStyle_s0088_f1b0* pTextStyle, Layout* pLayout, FontServer_s0088_f1b0* pFontServer)
{
    if (!pLayout)
        pLayout = this;

    if (!pTextStyle)
        pTextStyle = &pLayout->mLayoutSettings.mTextStyleDefault;

    if (!pFontServer)
        pFontServer = (FontServer_s0088_f1b0*)EA_Text_GetFontServer(1);

    FontSelection& fontSelection = pLayout->mLayoutSettings.mFontSelection;

    fontSelection.DoNukeSubtree(fontSelection.mpNodeParent);
    fontSelection.reset();

    pFontServer->GetFont(pTextStyle, fontSelection, 0x1e, 1, 0xffffffff, 1);
}
}}  // namespace EA::Text

// @ 0x00890010
unsigned int EA::Text::Layout_s0089_0010::LayoutText(const EA::Text::TextRun* pRuns, int nRuns, unsigned int nStart, unsigned int nEnd, const int32_t* pGlyphIndex, EA::Text::ClusterArray* pClusters, EA::Text::GlyphAdvanceSlot* pAdvances, int32_t* pGlyphClusters, float fLineWidth, unsigned int* pLineEnds, unsigned int nMaxLines, float* pLineWidths)
{
    EA::Text::TextRunIterator_s0089_0010 it;
    unsigned int nLine = 0;
    unsigned int nLineBegin = nStart;
    unsigned int nCurEnd = nEnd;
    float fLineWidthMax = fLineWidth;

    it.SetTextRunArray(pRuns, (unsigned int)nRuns, nStart, nStart, 0xffffffff, nEnd);

    if (fLineWidth < 0.1f)
        fLineWidth = 0.1f;

    unsigned int nLimit = nStart + nEnd;
    if (nLimit <= nStart)
        return 0;

    float fLineHeight = 0.0f;

    for (;;)
    {
        if (nLine >= nMaxLines)
            return nLine;

        unsigned int nChar = nLineBegin;
        float fLinePos = 0.0f;
        float fLineFirst = 0.0f;
        int bBreakChar = 0;
        unsigned int nPos = nChar;

        if (nChar < nLimit)
        {
            do
            {
                if (fLineWidth < fLineFirst || bBreakChar != 0)
                    break;

                EA::Text::TextRun& run = *it.mpArrayCurrent;
                unsigned int nRunEnd = run.mnTextSize;
                it.operator++();
                nPos = nChar + 1;

                unsigned int nGlyph = (unsigned int)pGlyphIndex[nPos];
                unsigned int nGlyphFirst = (unsigned int)pGlyphIndex[nChar];
                if (nGlyphFirst < nGlyph)
                {
                    EA::Text::GlyphAdvanceSlot* pAdv = &pAdvances[nGlyphFirst];
                    do
                    {
                        fLineFirst = fLinePos;
                        if (pAdv->mfValue > 0.0f)
                        {
                            fLinePos += pAdv->mfValue;
                            if (fLineWidth < fLinePos)
                                goto BreakOut;
                        }
                        ++pAdv;
                        ++nGlyphFirst;
                    } while (nGlyphFirst < nGlyph);
                }
                nLineBegin = nPos;
                fLinePos = fLineFirst;
            } while (nPos < nLimit);
        }

    BreakOut:
        fLineHeight = 0.0f;
        if (nLineBegin == nCurEnd)
        {
            if (mLayoutSettings.mTextStyleDefault.mOrientation == EA::Text::kOrientationVertical_s0089_0010 - 4)
            {
                int nGlyph = pGlyphIndex[nLineBegin];
                fLinePos = 0.0f;
                if (nLineBegin < nLimit)
                {
                    int32_t* pCluster = &pGlyphClusters[nGlyph];
                    EA::Text::GlyphAdvanceSlot* pAdv = &pAdvances[nGlyph];
                    do
                    {
                        if (fLineWidth <= fLineHeight)
                            break;
                        if (pAdv->mfValue > 0.0f)
                        {
                            fLinePos += pAdv->mfValue;
                            fLineHeight = fLinePos;
                            if (fLinePos < fLineWidth && nLineBegin <= (unsigned int)*pCluster)
                            {
                                unsigned int nSkip = (unsigned int)(*pCluster - nLineBegin) + 1;
                                nLineBegin += nSkip;
                                do
                                {
                                    it.operator++();
                                } while (--nSkip != 0);
                            }
                        }
                        ++pAdv;
                        ++pCluster;
                    } while (nLineBegin < nLimit);
                }
            }
            else
            {
                fLinePos += fLinePos;
                nLineBegin = nChar;
                fLineHeight = fLinePos;
            }
        }
        else if (nLineBegin < nLimit)
        {
            if (fLineWidth < fLineWidthMax || (bBreakChar == 0 && fLinePos == 0.0f))
                it.Restore(it);
        }

        if (it.mnPosition < it.mnEndPosition && *it.mpCharCurrent == L' ')
        {
            if (bBreakChar != L' ' && nLineBegin < nLimit)
            {
                it.operator++();
                ++nLineBegin;
                fLineHeight = fLinePos;
            }
        }

        if (fLineHeight < 0.1f)
            fLineHeight = 0.1f;

        if (nLineBegin <= nCurEnd)
            return nLine;

        if (pLineWidths != 0)
            pLineWidths[nLine] = fLineHeight;

        ++nLine;
        *pLineEnds = nLineBegin;
        ++pLineEnds;
        nCurEnd = nLineBegin;
    }
}

// @ 0x00890500
int EA::Text::Layout_s0089_0010::AnalyzeText(const EA::Text::AnalysisInfo_s0089_0010* pInfo, int nCount, EA::Text::AnalysisArray* pOut, int)
{
    pOut->resize(pOut->size() + 1);
    EA::Text::Analysis* pAnalysis = &pOut->back();

    const EA::Text::AnalysisInfo_s0089_0010* pEnd = pInfo + nCount;
    const EA::Text::AnalysisInfo_s0089_0010* p = pInfo;
    while (p < pEnd)
    {
        pAnalysis->mnLength += (uint32_t)pInfo->mpFont;
        ++p;
    }

    pAnalysis->mTextState.mnLevel = 0;
    pAnalysis->mTextState.mbForcedDirection = 0;
    pAnalysis->mTextState.mbSwapInhibited = 0;
    pAnalysis->mTextState.mbDisableNationalDigits = 0;
    pAnalysis->mnPosition = 0;
    pAnalysis->mScript = EA::Text::kScriptDefault;
    pAnalysis->mnParity = 0;
    pAnalysis->mnParentParity = 0;
    pAnalysis->mbJoinBefore = 0;
    pAnalysis->mbJoinAfter = 0;
    return 1;
}

// @ 0x00890570
int EA::Text::Layout_s0089_0010::LayoutTextLine(int a1, int a2, float fX, float fY, const EA::Text::TextStyle_s0089_0010* pStyle, EA::Text::GlyphAttributes_s0089_0010* pGlyphs, unsigned int nMaxGlyphs, EA::Text::LayoutMetrics* pMetrics)
{
    int nGlyphCount = 0;
    float fSpace = 1.0f;
    float fVisibleSpace = 0.0f;
    const EA::Text::TextStyle_s0089_0010* pCurStyle = pStyle;

    EA::Text::EnterCriticalSection(EA::Text::g_csText);

    if (pCurStyle == 0)
        pCurStyle = &mLayoutSettings.mTextStyleDefault;

    if (a2 != 0)
    {
        if (mLayoutSettings.mFontSelection.mnSize == 0)
        {
            EA::Text::FontServer_s0089_0010* pServer = EA::Text::GetFontServer(true);
            mLayoutSettings.mFontSelection.clear();
            pServer->GetFonts(pCurStyle, &mLayoutSettings.mFontSelection, EA::Text::kScriptDefault, 1, -1, 1);
        }

        EA::Text::AnalysisInfo_s0089_0010 info;
        info.mpTextStyle = (const EA::Text::TextStyle_s0089_0010*)a1;
        info.mpFont = (EA::Text::Font_s0089_0010*)a2;

        EA::Text::RunInfoArray* pRuns = (EA::Text::RunInfoArray*)&EA::Text::g_runInfoLine;
        pRuns->clear();
        AnalyzeText(&info, 1, (EA::Text::AnalysisArray*)&EA::Text::g_runInfoPara, 0);

        if (nMaxGlyphs > 0x400)
            nMaxGlyphs = 0x400;

        unsigned int nShaped = EA::Text::ShapeGlyphs(this, &info, 1, &EA::Text::g_glyphIndex[1],
                                           (EA::Text::RunInfo_s0089_0010*)&EA::Text::g_runInfoPara,
                                           ((EA::Text::RunInfoArray*)&EA::Text::g_runInfoPara)->size(),
                                           &EA::Text::g_glyphAttributes[0], nMaxGlyphs, EA::Text::g_glyphClusters);
        EA::Text::GlyphAttributes_s0089_0010 aMetrics[4];
        EA::Text::GlyphMetrics(&EA::Text::g_glyphAttributes[0], nShaped, aMetrics);

        if (nShaped <= nMaxGlyphs)
        {
            if (mLayoutSettings.mbCellTopPosition)
                fY = mLayoutSettings.mfYScale * fSpace + fY;

            nGlyphCount = EA::Text::PlaceGlyphs((EA::Text::RunInfo_s0089_0010*)&EA::Text::g_runInfoPara,
                                      ((EA::Text::RunInfoArray*)&EA::Text::g_runInfoPara)->size(),
                                      &EA::Text::g_glyphIndex[1], &EA::Text::g_glyphAttributes[0],
                                      0x400, fX, fY, (int)pGlyphs);
        }
    }

    if (pMetrics != 0)
    {
        pMetrics->mfBaseline = fSpace;
        pMetrics->mfDescent = fVisibleSpace;
        pMetrics->mnSize = (uint32_t)a2;
        pMetrics->mnLineCount = 1;
        float fWidth = 0.0f;
        if (nGlyphCount != 0)
            fWidth = (EA::Text::g_glyphAttributes[nGlyphCount - 1].mfAdvance
                      + EA::Text::g_glyphAdvance[nGlyphCount - 1].mfValue) - fX;
        pMetrics->mfSpace = fWidth;
        while (nGlyphCount != 0)
        {
            if (!EA::Text::IsSpace((EA::Text::wchar16)EA::Text::g_glyphAttributes[nGlyphCount - 1].mGlyphId, 0xff, 0))
                break;
            --nGlyphCount;
        }
        pMetrics->mnVisibleSize = (uint32_t)nGlyphCount;
        pMetrics->mfVisibleSpace = 0.0f;
    }

    EA::Text::LeaveCriticalSection(EA::Text::g_csText);
    return nGlyphCount;
}

// @ 0x00890830
int EA::Text::Layout_s0089_0010::LayoutTextParagraph(int a2, int a3, float fX1, float fY1, float fX2, float fY2, const EA::Text::TextStyle_s0089_0010* pStyle, int a9, unsigned int nMaxGlyphs, EA::Text::LayoutMetrics* pOut)
{
    int nTotal = 0;
    float fSpace = 1.0f;
    unsigned int nLines = 0;
    float fVisibleSpace = 0.0f;
    const EA::Text::TextStyle_s0089_0010* pCurStyle = pStyle;
    unsigned int aLineEnds[256];
    float aLineWidths[256];
    EA::Text::GlyphAttributes_s0089_0010 aGlyphDummy[4];

    EA::Text::EnterCriticalSection(EA::Text::g_csText);

    if (pCurStyle == 0)
        pCurStyle = &mLayoutSettings.mTextStyleDefault;

    if (a3 != 0)
    {
        if (mLayoutSettings.mFontSelection.mnSize == 0)
        {
            EA::Text::FontServer_s0089_0010* pServer = EA::Text::GetFontServer(true);
            mLayoutSettings.mFontSelection.clear();
            pServer->GetFonts(pCurStyle, &mLayoutSettings.mFontSelection, EA::Text::kScriptDefault, 1, -1, 1);
        }

        EA::Text::AnalysisInfo_s0089_0010 info;
        info.mpTextStyle = (const EA::Text::TextStyle_s0089_0010*)a2;
        info.mpFont = (EA::Text::Font_s0089_0010*)a3;

        ((EA::Text::RunInfoArray*)&EA::Text::g_runInfoPara)->clear();
        AnalyzeText(&info, 1, (EA::Text::AnalysisArray*)&EA::Text::g_runInfoPara, 0);

        if (nMaxGlyphs > 0x400)
            nMaxGlyphs = 0x400;

        unsigned int nShaped = EA::Text::ShapeGlyphs(this, &info, 1, &EA::Text::g_glyphIndex[1],
                                           (EA::Text::RunInfo_s0089_0010*)&EA::Text::g_runInfoPara,
                                           ((EA::Text::RunInfoArray*)&EA::Text::g_runInfoPara)->size(),
                                           EA::Text::g_glyphAttributes, nMaxGlyphs, EA::Text::g_glyphClusters);
        EA::Text::GlyphMetrics(EA::Text::g_glyphAttributes, nShaped, aGlyphDummy);

        if (nShaped <= nMaxGlyphs)
        {
            float fLineAdvance = fSpace - fVisibleSpace;
            float fScaled = fLineAdvance * mLayoutSettings.mfYScale;
            nLines = LayoutText((const EA::Text::TextRun*)&info, 1, 0, (unsigned int)a3,
                                &EA::Text::g_glyphIndex[1], (EA::Text::ClusterArray*)&EA::Text::g_runInfoPara,
                                EA::Text::g_glyphAdvance, EA::Text::g_glyphClusters, fX2 - fX1,
                                aLineEnds, 0x100, aLineWidths);

            if (pCurStyle->mVAlignment == EA::Text::kVACenter_s0089_0010)
                fY1 = (((fY2 - fY1) - (float)nLines * fLineAdvance) * 0.5f) * mLayoutSettings.mfYScale + fY1;
            else if (pCurStyle->mVAlignment == EA::Text::kVABottom_s0089_0010)
                fY1 = fY2 - ((float)nLines * fLineAdvance) * mLayoutSettings.mfYScale;

            unsigned int nRuns = ((EA::Text::RunInfoArray*)&EA::Text::g_runInfoPara)->size();
            nShaped = 0;
            fY1 = fSpace * mLayoutSettings.mfYScale + fY1;
            unsigned int nRun = 0;
            float fPenY = fLineAdvance;
            float fPenX = fX1;

            if (nLines != 0)
            {
                do
                {
                    unsigned int nRunEnd = nRun;
                    if (nRun < nRuns)
                    {
                        EA::Text::RunInfo_s0089_0010* pRun = (EA::Text::RunInfo_s0089_0010*)&EA::Text::g_runInfoPara + nRun;
                        do
                        {
                            if (aLineEnds[nShaped] < (unsigned int)(pRun->mnCharBegin + pRun->mnCharEnd))
                                break;
                            ++nRunEnd;
                            pRun += 1;
                        } while (nRunEnd < nRuns);
                    }

                    float fLineX;
                    if (pCurStyle->mHAlignment == EA::Text::kHACenter_s0089_0010)
                        fLineX = (fPenY - aLineWidths[nShaped]) * 0.5f + fPenX;
                    else
                    {
                        fLineX = fPenX;
                        if (pCurStyle->mHAlignment == EA::Text::kHARight_s0089_0010)
                            fLineX = fX2 - aLineWidths[nShaped];
                    }

                    if (pCurStyle->mHAlignment == EA::Text::kHAJustify_s0089_0010)
                    {
                        int nRunBegin = ((EA::Text::RunInfo_s0089_0010*)&EA::Text::g_runInfoPara)[nRun].mnCharBegin;
                        EA::Text::RunInfo_s0089_0010* pRunLast = (EA::Text::RunInfo_s0089_0010*)&EA::Text::g_runInfoPara + nRunEnd;
                        EA::Text::JustifyGlyphs(&info, 1, nRunBegin,
                                      (pRunLast[-1].mnCharBegin + pRunLast[-1].mnCharEnd) - nRunBegin,
                                      &EA::Text::g_glyphIndex[1], EA::Text::g_glyphAttributes, nMaxGlyphs,
                                      EA::Text::g_glyphClusters, fPenY - aLineWidths[nShaped], 0);
                        fPenY = fLineAdvance;
                        fPenX = fX1;
                    }

                    int nPlaced = EA::Text::PlaceGlyphs((EA::Text::RunInfo_s0089_0010*)&EA::Text::g_runInfoPara + nRun, nRunEnd - nRun,
                                              &EA::Text::g_glyphIndex[1], &EA::Text::g_glyphAttributes[0],
                                              nMaxGlyphs, fLineX, fY1, a9);
                    nTotal += nPlaced;                    fY1 += fScaled;
                    ++nShaped;
                    nRun = nRunEnd;
                } while (nShaped < nLines);
            }
        }
    }

    if (pOut != 0)
    {
        float fTotalHeight = (fSpace - fVisibleSpace) * (float)nLines;
        pOut->mnSize = (uint32_t)a3;
        pOut->mfSpace = (float)(int)a3;
        pOut->mnVisibleSize = (uint32_t)a3;
        pOut->mfVisibleSpace = fTotalHeight;
        pOut->mfBaseline = fSpace;
        pOut->mfDescent = fVisibleSpace;
        pOut->mnLineCount = nLines;
    }

    EA::Text::LeaveCriticalSection(EA::Text::g_csText);
    return nTotal;
}

// @ 0x00890cc0
float EA::Text::Layout_s0089_0010::GetTextLayoutMetrics(int a1, int a2, const EA::Text::TextStyle_s0089_0010* pStyle, EA::Text::LayoutMetrics* pOut)
{
    EA::Text::EnterCriticalSection(EA::Text::g_csText);
    LayoutTextLine(a1, a2, 0.0f, 0.0f, pStyle, (EA::Text::GlyphAttributes_s0089_0010*)&EA::Text::g_textStyleScratch, 0x400, pOut);
    float fResult = pOut->mfSpace;
    EA::Text::LeaveCriticalSection(EA::Text::g_csText);
    return fResult;
}

// @ 0x00890d20
float EA::Text::Layout_s0089_0010::GetMaxBaseline(const EA::Text::TextStyle_s0089_0010* pStyle)
{
    float fMax = 0.0f;
    EA::Text::FontMetrics_s0089_0010 metrics;
    EA::Text::LayoutSettings_s0089_0010 settings;
    EA::Text::LayoutSettings_s0089_0010* pCur = &mLayoutSettings;

    if (pStyle)
    {
        EA::Text::FontServer_s0089_0010* pServer = EA::Text::GetFontServer(true);
        settings.mFontSelection.clear();
        pServer->GetFonts(pStyle, &settings.mFontSelection, 0x1e, 1, -1, 1);
        pCur = &settings;
    }

    for (EA::Text::FontNode* p = pCur->mFontSelection.begin(); p != pCur->mFontSelection.end();
         p = EA::Text::RBTreeIncrement(p))
    {
        EA::Text::Font_s0089_0010* pFont = p->mpFont;
        if (pFont)
        {
            metrics.mfSize = 0.0f;
            pFont->GetFontMetrics(&metrics);
            fMax = EA::Text::Max(fMax, metrics.mfBaseline);
        }
    }
    return fMax;
}

// @ 0x00890e20
float EA::Text::Layout_s0089_0010::GetMinDescent(const EA::Text::TextStyle_s0089_0010* pStyle)
{
    float fMin = 0.0f;
    EA::Text::FontMetrics_s0089_0010 metrics;
    EA::Text::LayoutSettings_s0089_0010 settings;
    EA::Text::LayoutSettings_s0089_0010* pCur = &mLayoutSettings;

    if (pStyle)
    {
        EA::Text::FontServer_s0089_0010* pServer = EA::Text::GetFontServer(true);
        settings.mFontSelection.clear();
        pServer->GetFonts(pStyle, &settings.mFontSelection, 0x1e, 1, -1, 1);
        pCur = &settings;
    }

    for (EA::Text::FontNode* p = pCur->mFontSelection.begin(); p != pCur->mFontSelection.end();
         p = EA::Text::RBTreeIncrement(p))
    {
        EA::Text::Font_s0089_0010* pFont = p->mpFont;
        if (pFont)
        {
            metrics.mfSize = 0.0f;
            pFont->GetFontMetrics(&metrics);
            fMin = EA::Text::Min(fMin, (float)iat_floor((double)metrics.mfDescent));
        }
    }
    return fMin;
}
