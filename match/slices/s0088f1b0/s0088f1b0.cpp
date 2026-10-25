// Slice s0088f1b0: EA::Text (EAText) textsetter / layout helpers as linked into SporeApp.exe.
//
//  0088f1b0  EA::Text::FontServer::AddFaceSource
//  0088f4e0  EA::Text::Layout::GetLayoutMetrics   (baseline/descent over a GlyphAttributes array)
//  0088f570  EA::Text::MeasureNextSegment         (word-segment length + last Char)
//  0088f6a0  EA::Text::Layout::PlaceGlyphs
//  0088f860  EA::Text::Layout::GetGlyphs          (shape one Char per GlyphAttributes slot)
//  0088f9b0  EA::Text::Layout::ShapeGlyphs
//  0088fbc0  EA::Text::Layout::DistributeWhitespace
//  0088fda0  eastl::rbtree<EA::AutoRefCount<EA::Text::Font>,...>::DoNukeSubtree
//  0088fe00  eastl::vector<Typesetter::RunInfo>::DoInsertValues
//  0088ffa0  EA::Text::Layout::UpdateFontSelection
//
// The retail EAText is the 2009/2010 layout-settings build: EA::Text::Layout has no vtable and
// its only member is mLayoutSettings (size 0x37c), whose FontSelection (eastl::fixed_set<FontARC,8>)
// starts at +0x14, followed by mTextStyleDefault at +0xf8, mbCellTopPosition at +0x371 and
// mfYScale at +0x374. GlyphAttributes is 0x28 bytes (mpFont +0x00 .. mGLA +0x20, mGlyphId +0x24).
#include "types.h"

extern "C" {
void __stdcall EnterCriticalSection(void* pCriticalSection);   // kernel32!EnterCriticalSection
void __stdcall LeaveCriticalSection(void* pCriticalSection);   // kernel32!LeaveCriticalSection
void* __cdecl operator new[](unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                             const char* file, int line);      // 0x00f473a0
void  __cdecl operator delete[](void* p);
void  FreeRawBlock(void* p);                                   // 0x00f47380
}

namespace EA { namespace Text {

typedef uint16_t Char;

struct TextRun {
    wchar_t* mpText;          // +0x00
    unsigned int mnTextSize;  // +0x04
};

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

}}

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

namespace EA { namespace Text {

// ---------------------------------------------------------------------------------------------
// Retail EAText data layouts
// ---------------------------------------------------------------------------------------------

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

struct GlyphMetrics
{
    float mfSizeX;      // +0x00
    float mfSizeY;      // +0x04
    float mfHBearingX;  // +0x08
    float mfHBearingY;  // +0x0c
    float mfHAdvanceX;  // +0x10
};

struct GlyphLayoutAttributes
{
    uint32_t mValue;    // +0x00  mGJC:4, mClusterPosition:3, mClusterSize:3, mbDiacritic:1,
                        //        mbInvisible:1, mbZeroWidth:1, plus the cluster fields above
};  // 4 bytes (the glyph id follows at +0x24)

struct Font;
class FontSelection;

struct GlyphAttributes
{
    Font*                 mpFont;      // +0x00
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

// Typesetter run info (0x10 bytes); the retail vector of these lives in the Typesetter.
struct RunInfo
{
    uint32_t mScript;       // +0x00
    int      mnBidiLevel;   // +0x04
    uint32_t mnCharBegin;   // +0x08
    uint32_t mnCharEnd;     // +0x0c
};

// Glyph-run pair consumed by Layout::PlaceGlyphs: two character/glyph indices at +0x00/+0x04.
struct GlyphRunInfo
{
    uint32_t mnCharBegin;   // +0x00
    uint32_t mnCharEnd;     // +0x04
};

class Font
{
public:
    virtual ~Font();                                                     // +0x00
    virtual void Slot04();                                               // +0x04
    virtual void Slot08();                                               // +0x08
    virtual void Release();                                              // +0x0c
    virtual void Slot10();                                               // +0x10
    virtual void Slot14();                                               // +0x14
    virtual void Slot18();                                               // +0x18
    virtual void Slot1c();                                               // +0x1c
    virtual void Slot20();                                               // +0x20
    virtual void Slot24();                                               // +0x24
    virtual void Slot28();                                               // +0x28
    virtual void Slot2c();                                               // +0x2c
    virtual bool GetFontMetrics(FontMetrics& fontMetrics) const;         // +0x30
    virtual bool GetGlyphMetrics(uint16_t glyphId, GlyphMetrics& glyphMetrics) const;  // +0x34
    virtual bool GetGlyphs(const Char* pText, uint32_t nTextLen, uint16_t* pGlyphIdArray,
                           uint32_t nGlyphCount, uint32_t nGlyphStride); // +0x38
    virtual void Slot3c();                                               // +0x3c
    virtual bool GetGlyphProperties(uint16_t glyphId1, uint16_t glyphId2, float* pAdjustment,
                                    bool bAdjustAllowed, bool bAdvance) const;  // +0x40
};

// eastl::fixed_set<EA::AutoRefCount<EA::Text::Font>, 8> == rbtree over a
// fixed_node_pool<20,8,4,0,1>. The allocator is embedded at +0x18.
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
        Font* mpFont;        // +0x10  AutoRefCount<Font> (a reference-counted Font*)
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

inline void FontSelection::reset()
{
    mpNodeRight  = (Node*)(void*)&mpNodeRight;
    mpNodeLeft   = (Node*)(void*)&mpNodeRight;
    mpNodeParent = 0;
    mColor       = 0;
    mnSize       = 0;
}

struct TextStyle
{
    char mPad000[0x264];     // +0x000
    int  mPasswordMode;      // +0x264 (kPMDefault = 0, kPMPassword = 1)
    char mPad268[0x278 - 0x268];
};

struct LayoutSettings
{
    Char          mLocale[6];              // +0x000
    int           mScript;                 // +0x00c
    int           mDirection;              // +0x010
    FontSelection mFontSelection;          // +0x014
    TextStyle     mTextStyleDefault;       // +0x0f8
    bool          mbEnableAutoHyphenation; // +0x370
    bool          mbCellTopPosition;       // +0x371
    char          mPad372[2];              // +0x372
    float         mfYScale;                // +0x374
    bool          mbEnableLigatures;       // +0x378
    bool          mbHideControlCharacters; // +0x379
    bool          mbDisplayZWG;            // +0x37a
    char          mPad37b;                 // +0x37b
};  // 0x37c

// ---------------------------------------------------------------------------------------------
// Font description / server / face (retail layout)
// ---------------------------------------------------------------------------------------------

class FontDescription
{
public:
    uint32_t mPad00[2];         // +0x00
    Char     mpFamilyName[0x20];// +0x08  inline family name, NUL terminated
};

class FaceSource
{
public:
    FaceSource*     mpNext;           // +0x00
    FaceSource*     mpPrev;           // +0x04
    FontDescription mFontDescription; // +0x08  (family name at +0x10)
};

class Face
{
public:
    char        mPad000[0x50];     // +0x000
    FaceSource  mSourceListHead;   // +0x050  fixed_list<FaceSource> sentinel
};

// eastl::hashtable<string16, pair<const string16, Face>, fixed_hashtable_allocator<10,1232,8,4,0,1>>
class FaceMap
{
public:
    uint32_t mPad00;          // +0x00
    void*    mpBucketArray;   // +0x04
    uint32_t mnBucketCount;   // +0x08
    char     mBuffer[0x100];  // +0x0c  fixed bucket buffer / prime rehash policy

    Face* FindFace(const Char* pFamilyName);   // 0x0088c600  find_as<wchar_t const*>
    Face* InsertFace(const Char* pFamilyName); // 0x0088f000  DoInsertValue
};

class WString
{
public:
    Char*    mpBegin;     // +0x00
    Char*    mpEnd;       // +0x04
    Char*    mpCapacity;  // +0x08
    uint32_t mPad0c;      // +0x0c
    Char     mBuffer[8];  // +0x10  SSO buffer

    void Assign(const Char* pBegin, const Char* pEnd);  // 0x0088c3d0
    void MakeLower();                                   // 0x005e8e80
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    const Char* c_str() const { return mpBegin; }
};

struct CriticalSection
{
    uint32_t mData[6];
};

class FontServer
{
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual bool GetFont(const TextStyle* pTextStyle, FontSelection& fontSelection,
                         uint32_t maxCount, uint32_t a4, uint32_t a5, uint32_t a6);  // +0x18

    char          mPad000[0x288];   // +0x000
    FaceMap       mFaceMap;         // +0x288
    char          mPad288[0x2fb0 - 0x288 - sizeof(FaceMap)];
    CriticalSection mMutex;         // +0x2fb0

    bool AddFaceSource(const FontDescription* pFontDescription);   // 0x0088f1b0
};

extern "C" {
bool IsSameFamilyName(const Char* pFamilyName1, const Char* pFamilyName2);  // 0x0088b500
FaceSource* CreateFaceSource(const FontDescription* pFontDescription);      // 0x0088e5a0
void* EA_Text_GetFontServer(int bSomething);                                // 0x00885a60
}

struct ScriptProperties
{
    uint32_t mData[2];   // 8 bytes, written by GetScriptProperties
};
bool GetScriptProperties(int script, ScriptProperties* pScriptProperties, bool bSomething);  // 0x00893ed0

// ---------------------------------------------------------------------------------------------
// Layout
// ---------------------------------------------------------------------------------------------

class Layout
{
public:
    LayoutSettings mLayoutSettings;   // +0x000 (the only member; Layout is 0x37c bytes)

    static void GetLayoutMetrics(const GlyphAttributes* pGlyphAttributes, uint32_t nGlyphCount,
                                 LayoutMetrics* pLayoutMetrics);                    // 0x0088f4e0
    static uint32_t __stdcall PlaceGlyphs(const GlyphRunInfo* pGlyphRuns, uint32_t nGlyphRunCount,
                                const uint32_t* pGlyphIndexArray, const GlyphAttributes* pGlyphAttributes,
                                uint32_t nUnused, float penX, float penY,
                                GlyphAttributes* pGlyphAttributesOut);              // 0x0088f6a0
    uint32_t GetGlyphs(const Char* pText, uint32_t nTextLen, float penX, float penY,
                       Font* pFont, GlyphAttributes* pGlyphAttributes);             // 0x0088f860
    uint32_t ShapeGlyphs(uint32_t* pGlyphCountOut, uint32_t nTextRunCount,
                         uint32_t* pGlyphIndexArray, const TextRun* pTextRunArray,
                         uint32_t nGlyphCapacity, GlyphAttributes* pGlyphAttributes,
                         uint32_t nGlyphCount, uint32_t* pGlyphIndexArray2);        // 0x0088f9b0
    void DistributeWhitespace(const TextRun* pTextRunArray, uint32_t nTextRunCount,
                              uint32_t nCharBegin, uint32_t nCharCount,
                              const uint32_t* pGlyphIndexArray, GlyphAttributes* pGlyphAttributes,
                              uint32_t nUnused1, uint32_t nUnused2, float fSpace,
                              bool bAdjustLastLine);                                 // 0x0088fbc0
    void UpdateFontSelection(const TextStyle* pTextStyle, Layout* pLayout,
                             FontServer* pFontServer);                              // 0x0088ffa0
};

int MeasureNextSegment(TextRunIterator* pIterator, Char* pLastChar);                // 0x0088f570

// eastl::vector<RunInfo> (retail eastl_size_t based vector of 0x10-byte elements)
class RunInfoVector
{
public:
    RunInfo* mpBegin;      // +0x00
    RunInfo* mpEnd;        // +0x04
    RunInfo* mpCapacity;   // +0x08

    void DoInsertValues(RunInfo* pos, uint32_t n, const RunInfo& value);   // 0x0088fe00
};

extern "C" {
void UninitCopy16(RunInfo** pOut, RunInfo* first, RunInfo* last, RunInfo* result, RunInfo* result2);  // 0x007f1890
RunInfo* CopyRunInfo(RunInfo* first, RunInfo* last, RunInfo* result);        // 0x00c7ea30
void FillRunInfo(RunInfo* first, RunInfo* last, const RunInfo* pValue);      // 0x00898580
void CopyBackwardRunInfo(RunInfo* first, RunInfo* last, RunInfo* result);    // 0x00edba80
void UninitFillNRunInfo(RunInfo* first, uint32_t n, const RunInfo* pValue, RunInfo* pos);  // 0x0088f820
}

// ---------------------------------------------------------------------------------------------
// FontServer::AddFaceSource
// ---------------------------------------------------------------------------------------------
// @ 0x0088f1b0
bool EA::Text::FontServer::AddFaceSource(const FontDescription* pFontDescription)
{
    bool bResult = false;

    EnterCriticalSection(&mMutex);

    const Char* const pFamilyName = pFontDescription->mpFamilyName;
    uint32_t nFamilyNameLength = 0;
    while (pFamilyName[nFamilyNameLength] != 0)
        ++nFamilyNameLength;

    WString familyName;
    familyName.Assign(pFamilyName, pFamilyName + nFamilyNameLength);

    if (familyName.size() < 0x20)   // kFamilyNameCapacity
    {
        familyName.MakeLower();

        Face* pFace = mFaceMap.FindFace(familyName.c_str());

        if (!pFace)
            pFace = mFaceMap.InsertFace(familyName.c_str());

        if (pFace)
        {
            bool bFound = false;

            for (FaceSource* pSource = pFace->mSourceListHead.mpNext;
                 pSource != &pFace->mSourceListHead; pSource = pSource->mpNext)
            {
                if (IsSameFamilyName(pFamilyName, pSource->mFontDescription.mpFamilyName))
                    bFound = true;
            }

            if (!bFound)
            {
                FaceSource* const pNewSource = CreateFaceSource(pFontDescription);
                pNewSource->mpNext = &pFace->mSourceListHead;
                pNewSource->mpPrev = pFace->mSourceListHead.mpPrev;
                pFace->mSourceListHead.mpPrev->mpNext = pNewSource;
                pFace->mSourceListHead.mpPrev = pNewSource;
            }

            bResult = true;
        }
    }

    LeaveCriticalSection(&mMutex);

    return bResult;
}

// ---------------------------------------------------------------------------------------------
// Layout::GetLayoutMetrics
// ---------------------------------------------------------------------------------------------
// @ 0x0088f4e0
void EA::Text::Layout::GetLayoutMetrics(const GlyphAttributes* pGlyphAttributes, uint32_t nGlyphCount,
                                        LayoutMetrics* pLayoutMetrics)
{
    FontMetrics fontMetrics;
    const Font* pFontLast = 0;
    const GlyphAttributes* const pGlyphAttributesEnd = pGlyphAttributes + nGlyphCount;

    fontMetrics.mfSize = 0.0f;
    pLayoutMetrics->mfBaseline = 0.f;
    pLayoutMetrics->mfDescent  = 0.f;

    while (pGlyphAttributes < pGlyphAttributesEnd)
    {
        const Font* const pFont = pGlyphAttributes->mpFont;

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

// ---------------------------------------------------------------------------------------------
// MeasureNextSegment
// ---------------------------------------------------------------------------------------------
// @ 0x0088f570
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

// ---------------------------------------------------------------------------------------------
// Layout::PlaceGlyphs
// ---------------------------------------------------------------------------------------------
// @ 0x0088f6a0
uint32_t __stdcall EA::Text::Layout::PlaceGlyphs(const GlyphRunInfo* pGlyphRuns, uint32_t nGlyphRunCount,
                                       const uint32_t* pGlyphIndexArray, const GlyphAttributes* pGlyphAttributes,
                                       uint32_t, float penX, float penY,
                                       GlyphAttributes* pGlyphAttributesOut)
{
    GlyphAttributes* pOut = pGlyphAttributesOut;
    uint32_t nRuns = nGlyphRunCount;

    if (nRuns)
    {
        float fPenX = penX;

        do
        {
            const uint32_t nCharBegin = pGlyphRuns->mnCharBegin;
            const uint32_t nCharLast = pGlyphRuns->mnCharEnd;

            const GlyphAttributes* pGlyph = pGlyphAttributes + pGlyphIndexArray[nCharBegin];
            const GlyphAttributes* const pGlyphEnd =
                pGlyphAttributes + pGlyphIndexArray[nCharBegin + nCharLast];

            while (pGlyph < pGlyphEnd)
            {
                pOut->mpFont    = pGlyph->mpFont;
                pOut->mfPenX    = fPenX;
                pOut->mfPenY    = penY;
                pOut->mfX1      = pGlyph->mfX1 + fPenX;
                pOut->mfY1      = pGlyph->mfY1 + penY;
                pOut->mfX2      = pGlyph->mfX2 + fPenX;
                pOut->mfY2      = pGlyph->mfY2 + penY;
                pOut->mfAdvance = pGlyph->mfAdvance;
                pOut->mGLA      = pGlyph->mGLA;
                pOut->mGlyphId  = pGlyph->mGlyphId;

                ++pOut;
                fPenX = pGlyph->mfAdvance + fPenX;
                ++pGlyph;
            }

            ++pGlyphRuns;
        } while (--nRuns);
    }

    return (uint32_t)(pOut - pGlyphAttributesOut);
}

// ---------------------------------------------------------------------------------------------
// Layout::GetGlyphs
// ---------------------------------------------------------------------------------------------
// @ 0x0088f860
uint32_t EA::Text::Layout::GetGlyphs(const Char* pText, uint32_t nTextLen, float penX, float penY,
                                     Font* pFont, GlyphAttributes* pGlyphAttributes)
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
            GlyphMetrics glyphMetrics;

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

// ---------------------------------------------------------------------------------------------
// Layout::ShapeGlyphs
// ---------------------------------------------------------------------------------------------
// @ 0x0088f9b0
uint32_t EA::Text::Layout::ShapeGlyphs(uint32_t* pGlyphCountOut, uint32_t nTextRunCount,
                                       uint32_t* pGlyphIndexArray, const TextRun* pTextRunArray,
                                       uint32_t nGlyphCapacity, GlyphAttributes* pGlyphAttributes,
                                       uint32_t nGlyphCount, uint32_t* pGlyphIndexArray2)
{
    uint32_t nGlyph = 0;

    TextRunIterator iterator;
    iterator.SetTextRunArray(pTextRunArray, nTextRunCount, 0, 0, 0xffffffff);

    if (iterator.mnPosition != iterator.mnEndPosition)
    {
        Font* const pFont = mLayoutSettings.mFontSelection.mpNodeLeft->mpFont;
        GlyphAttributes* pGlyph = pGlyphAttributes;

        for (;;)
        {
            Char c = (iterator.mnPosition < iterator.mnEndPosition) ? *iterator.mpCharCurrent : (Char)0xffff;

            if (nGlyph < nGlyphCount)
            {
                if (mLayoutSettings.mTextStyleDefault.mPasswordMode == 1)
                    c = 0x25cf;   // BULLET

                pFont->GetGlyphs(&c, 1, &pGlyph->mGlyphId, 1, 2);

                GlyphMetrics glyphMetrics;
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

// ---------------------------------------------------------------------------------------------
// Layout::DistributeWhitespace
// ---------------------------------------------------------------------------------------------
// @ 0x0088fbc0
void EA::Text::Layout::DistributeWhitespace(const TextRun* pTextRunArray, uint32_t nTextRunCount,
                                            uint32_t nCharBegin, uint32_t nCharCount,
                                            const uint32_t* pGlyphIndexArray, GlyphAttributes* pGlyphAttributes,
                                            uint32_t, uint32_t, float fSpace, bool bAdjustLastLine)
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

// ---------------------------------------------------------------------------------------------
// eastl::rbtree<AutoRefCount<Font>, ...>::DoNukeSubtree
// ---------------------------------------------------------------------------------------------
// @ 0x0088fda0
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

// ---------------------------------------------------------------------------------------------
// eastl::vector<RunInfo>::DoInsertValues
// ---------------------------------------------------------------------------------------------
// @ 0x0088fe00
void EA::Text::RunInfoVector::DoInsertValues(RunInfo* pos, uint32_t n, const RunInfo& value)
{
    if (n > (uint32_t)(mpCapacity - mpEnd))
    {
        const uint32_t nOldSize = (uint32_t)(mpEnd - mpBegin);
        uint32_t nNewCapacity = nOldSize ? nOldSize * 2 : 1;

        if (nNewCapacity < nOldSize + n)
            nNewCapacity = nOldSize + n;

        RunInfo* const pNewBegin = nNewCapacity ?
            (RunInfo*)operator new[](nNewCapacity * sizeof(RunInfo), "EASTL", 0, 0,
                                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;

        RunInfo* pNewEnd = CopyRunInfo(mpBegin, pos, pNewBegin);
        UninitFillNRunInfo(pNewEnd, n, &value, pos);
        pNewEnd = CopyRunInfo(pos, mpEnd, pNewEnd + n);

        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            operator delete[](mpBegin);

        mpBegin    = pNewBegin;
        mpEnd      = pNewEnd;
        mpCapacity = pNewBegin + nNewCapacity;
    }
    else if (n)
    {
        const RunInfo valueCopy = value;
        RunInfo* const pOldEnd = mpEnd;
        const uint32_t nAfterPos = (uint32_t)(mpEnd - pos);

        if (n < nAfterPos)
        {
            UninitCopy16((RunInfo**)&value, pOldEnd - n, pOldEnd, pOldEnd, pos);
            mpEnd += n;
            CopyBackwardRunInfo(pos, pOldEnd - n, pOldEnd);
            FillRunInfo(pos, pos + n, &valueCopy);
        }
        else
        {
            UninitFillNRunInfo(pOldEnd, n - nAfterPos, &valueCopy, pos);
            mpEnd += n - nAfterPos;

            RunInfo* const pPos = pos;
            UninitCopy16((RunInfo**)&pos, pPos, pOldEnd, mpEnd, pPos);
            mpEnd += nAfterPos;
            FillRunInfo(pPos, pOldEnd, &valueCopy);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// Layout::UpdateFontSelection
// ---------------------------------------------------------------------------------------------
// @ 0x0088ffa0
void EA::Text::Layout::UpdateFontSelection(const TextStyle* pTextStyle, Layout* pLayout,
                                           FontServer* pFontServer)
{
    if (!pLayout)
        pLayout = this;

    if (!pTextStyle)
        pTextStyle = &pLayout->mLayoutSettings.mTextStyleDefault;

    if (!pFontServer)
        pFontServer = (FontServer*)EA_Text_GetFontServer(1);

    FontSelection& fontSelection = pLayout->mLayoutSettings.mFontSelection;

    fontSelection.DoNukeSubtree(fontSelection.mpNodeParent);
    fontSelection.reset();

    pFontServer->GetFont(pTextStyle, fontSelection, 0x1e, 1, 0xffffffff, 1);
}

}}
