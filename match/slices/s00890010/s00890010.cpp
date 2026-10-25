// Slice s00890010: EA::Text::Layout font-selection helpers and Layout ctor.
// Built /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast   (no /EHsc: no unwind tables in this module)
#include "types.h"

namespace EA { namespace Text {

struct FontMetrics {              // 0x44 bytes
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

enum Orientation { kOrientationHorizontal = 0, kOrientationVertical, kOrientationDefault = kOrientationHorizontal };
enum HAlignment  { kHALeft = 0, kHACenter, kHARight, kHAJustify };
enum VAlignment  { kVATop = 0, kVACenter, kVABottom };
enum TextWrap    { kTWNone = 0, kTWWrap, kTWSoft, kTWHard, kTWEmergency };

struct TextStyle {                // 0x278 bytes (only ever constructed elsewhere)
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

struct Font;

struct FontNode {                 // eastl rbtree node, 20 bytes
    FontNode* mpNodeRight;        // +0x00
    FontNode* mpNodeLeft;         // +0x04
    FontNode* mpNodeParent;       // +0x08
    bool      mbColor;            // +0x0c (padded to 4)
    Font*     mpFont;             // +0x10 (EA::AutoRefCount<Font>)
};

// rbtree header node reused as the end() sentinel: its value slot overlaps mnSize.
struct FontTreeAnchor {           // 16 bytes
    FontNode* mpNodeRight;        // +0x00
    FontNode* mpNodeLeft;         // +0x04
    FontNode* mpNodeParent;       // +0x08
    bool      mbColor;            // +0x0c (padded to 4)
};

// eastl::fixed_set<EA::AutoRefCount<Font>, 8, 1>: header + 8 nodes * 20 bytes
struct FontSelection {
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
    ~FontSelection() { DoNukeSubtree((FontNode*)mAnchor.mpNodeParent); }
};

struct FontServer {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual int GetFonts(const TextStyle* pStyle, FontSelection* pOut,
                         int32_t script, int32_t a, int32_t b, int32_t c);   // +0x18
};

struct Font {
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
    virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7();
    virtual void f8(); virtual void f9(); virtual void f10(); virtual void f11();
    virtual bool GetFontMetrics(FontMetrics* pOut);          // +0x30
};

FontNode* RBTreeIncrement(FontNode* pNode);                  // 0x00921580
FontServer* GetFontServer(bool bCreate);                     // 0x00885a60

struct LayoutSettings {           // 0x37c bytes
    wchar_t mLocale[6];           // +0x000
    int32_t mScript;              // +0x00c
    int32_t mDirection;           // +0x010
    FontSelection mFontSelection; // +0x014
    bool mbDynamicFontSelection;  // +0x0f4
    TextStyle mTextStyleDefault;  // +0x0f8
    bool mbEnableAutoHyphenation; // +0x370
    bool mbCellTopPosition;       // +0x371
    float mfYScale;               // +0x374
    bool mbEnableLigatures;       // +0x378
    bool mbHideControlCharacters; // +0x379
    bool mbDisplayZWG;            // +0x37a

    LayoutSettings();                                        // 0x0089b010
};

// --- text-layout analysis / shaping state ---------------------------------
// (layouts taken from the EA Text headers vendored under work/ext and from the
//  retail instruction stream; the retail TextStyle above is 0xc smaller than
//  the vendored one, so the trailing enum fields sit at the offsets the code uses.)

struct TextState {                        // one 32-bit word, 7 live bits
    int mnLevel                 : 4;      // +0x00
    int mbForcedDirection       : 1;
    int mbSwapInhibited         : 1;
    int mbDisableNationalDigits : 1;
};

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

struct AnalysisInfo {                     // 8 bytes
    const TextStyle* mpTextStyle;         // +0x00
    Font*            mpFont;              // +0x04
};

struct RunInfo {                          // 16 bytes
    int32_t mScript;                      // +0x00
    int32_t mnBidiLevel;                  // +0x04
    int32_t mnCharBegin;                  // +0x08
    int32_t mnCharEnd;                    // +0x0c
};

struct RunInfoArray {                     // eastl::vector<RunInfo>, 24 bytes
    RunInfo*    mpBegin;                  // +0x00
    RunInfo*    mpEnd;                    // +0x04
    RunInfo*    mpCapacity;               // +0x08
    const char* mpName;                   // +0x0c
    int32_t     mFlags;                   // +0x10
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    void clear() { mpEnd = mpBegin; }
};

RunInfo* RunInfoCopyRange(RunInfo* pDest, RunInfo* pFirst, RunInfo* pLast);  // 0x00705250

// A paragraph is described by a run of 16-byte [start, count, x, y] cluster records.
struct Cluster {                          // 16 bytes
    uint32_t mnCharBegin;                 // +0x00
    uint32_t mnCharCount;                 // +0x04
    uint32_t mnX;                         // +0x08
    uint32_t mnY;                         // +0x0c
};

struct ClusterArray {                     // eastl::vector<Cluster>, 24 bytes
    Cluster*    mpBegin;                  // +0x00
    Cluster*    mpEnd;                    // +0x04
    Cluster*    mpCapacity;               // +0x08
    const char* mpName;                   // +0x0c
    int32_t     mFlags;                   // +0x10
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
};

struct TextRun {                          // 8 bytes
    wchar_t*     mpText;                  // +0x00
    unsigned int mnTextSize;              // +0x04
};

class TextRunIterator {
public:
    TextRun*     mpArray;                 // +0x00
    TextRun*     mpArrayEnd;              // +0x04
    TextRun*     mpArrayCurrent;          // +0x08
    wchar_t*     mpCharCurrent;           // +0x0c
    unsigned int mnStartPosition;         // +0x10
    unsigned int mnEndPosition;           // +0x14
    unsigned int mnPosition;              // +0x18

    TextRunIterator& operator++();                                        // 0x0088f570
    TextRun&         operator*();                                         // 0x0088f480
    void Restore(const TextRunIterator& src) {
        mpArray = src.mpArray; mpArrayEnd = src.mpArrayEnd; mpArrayCurrent = src.mpArrayCurrent;
        mpCharCurrent = src.mpCharCurrent; mnStartPosition = src.mnStartPosition;
        mnEndPosition = src.mnEndPosition; mnPosition = src.mnPosition;
    }
    void SetTextRunArray(const TextRun* pRuns, unsigned int nCount,
                         unsigned int nStart, unsigned int nPos,
                         unsigned int nMax, unsigned int nEnd);           // 0x0088f790
};

struct GlyphAttributes {                  // 40 bytes in this build
    Font*    mpFont;                      // +0x00
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

// A 0x28-byte slot whose first float is a per-glyph advance delta.
struct GlyphAdvanceSlot {                 // 40 bytes
    float    mfValue;                     // +0x00
    uint32_t mPad[9];                     // +0x04
};

struct LayoutMetrics {                    // 28 bytes
    uint32_t mnSize;                      // +0x00
    float    mfSpace;                     // +0x04
    uint32_t mnVisibleSize;               // +0x08
    float    mfVisibleSpace;              // +0x0c
    float    mfBaseline;                  // +0x10
    float    mfDescent;                   // +0x14
    uint32_t mnLineCount;                 // +0x18
};

struct OutlineFont {
    uint8_t mData[0x164];                 // +0x000
    bool    mbOption1;                    // +0x164
    void SetOption(int option, int value);   // 0x00890fa0
};

// --- layout scratch globals ------------------------------------------------
struct TextStyleMetrics { char mData[0x278]; };
extern int32_t           g_glyphIndex[];      // 0x016519cc (char -> glyph id, -1 = none)
extern GlyphAttributes   g_glyphAttributes[]; // 0x016539d0 (shaped glyphs, stride 0x28)
extern GlyphAdvanceSlot  g_glyphAdvance[];    // 0x016539c4 (per-glyph advance, stride 0x28)
extern int32_t           g_glyphClusters[];   // 0x016529d0 (glyph -> cluster end, stride 4)
extern RunInfoArray      g_runInfoLine;       // 0x01667a18 (line run list)
extern ClusterArray      g_runInfoPara;       // 0x01667a04 (paragraph cluster list)
extern TextStyle         g_textStyleScratch;  // 0x0165d9d0 (scratch style / glyph out buffer)
extern uint8_t           g_csText[];          // 0x016679d0 (CRITICAL_SECTION)

__declspec(dllimport) void __stdcall EnterCriticalSection(void*);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void*);

const int kScriptDefault = 0x1e;

typedef wchar_t wchar16;

struct Layout;                            // 0x37c bytes
struct Layout {
    LayoutSettings mLayoutSettings;
    Layout();
    float GetMaxBaseline(const TextStyle* pStyle);           // 0x00890d20
    float GetMinDescent(const TextStyle* pStyle);            // 0x00890e20
    int   AnalyzeText(const AnalysisInfo* pInfo, int nCount,
                      AnalysisArray* pOut, int unused);      // 0x00890500
    int   LayoutTextLine(int a1, int a2, float fX, float fY,
                         const TextStyle* pStyle, GlyphAttributes* pGlyphs,
                         unsigned int nMaxGlyphs, LayoutMetrics* pMetrics);  // 0x00890570
    unsigned int LayoutText(const TextRun* pRuns, int nRuns, unsigned int nStart,
                            unsigned int nEnd, const int32_t* pGlyphIndex,
                            ClusterArray* pClusters, GlyphAdvanceSlot* pAdvances,
                            int32_t* pGlyphClusters, float fLineWidth,
                            unsigned int* pLineEnds, unsigned int nMaxLines,
                            float* pLineWidths);                 // 0x00890010
    int   LayoutTextParagraph(int a2, int a3, float fX1, float fY1, float fX2,
                              float fY2, const TextStyle* pStyle, int a9,
                              unsigned int nMaxGlyphs, LayoutMetrics* pOut);  // 0x00890830
    float GetTextLayoutMetrics(int a1, int a2, const TextStyle* pStyle,
                               LayoutMetrics* pOut);             // 0x00890cc0
};

// Callees in the EA::Text layout module (defined in their own slices).
unsigned int ShapeGlyphs(Layout* pLayout, const AnalysisInfo* pInfo, int nInfo,
                         const int32_t* pGlyphIndex, RunInfo* pRuns, unsigned int nRuns,
                         GlyphAttributes* pGlyphs, unsigned int nMaxGlyphs,
                         int32_t* pGlyphClusters);                       // 0x0088f9b0
unsigned int PlaceGlyphs(RunInfo* pRuns, unsigned int nRuns,
                         const int32_t* pGlyphIndex, GlyphAttributes* pGlyphs,
                         unsigned int nMaxGlyphs, float fPenX, float fPenY,
                         int nGlyphBase);                                // 0x0088f6a0
void GlyphMetrics(GlyphAttributes* pGlyphs, unsigned int nGlyphCount, void* pOut);  // 0x0088f4e0
void JustifyGlyphs(const AnalysisInfo* pInfo, int nInfo, int a3, int a4,
                   const int32_t* pGlyphIndex, GlyphAttributes* pGlyphs,
                   unsigned int nMaxGlyphs, int32_t* pGlyphClusters, float fAmount,
                   int a10);                                             // 0x0088fbc0
bool IsSpace(wchar16 c, unsigned int a2, bool a3);                       // 0x0089e0e0

template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template <class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

// Comparison callback registered with a container (context + 2 keys + value).
struct IFontCompareTarget {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual bool HasFont(int32_t a, int32_t b);              // +0x28
    virtual void v11();
    virtual int32_t FindFont(int32_t a, int32_t b);          // +0x30
};

}}  // namespace EA::Text

using namespace EA::Text;

extern "C" double __cdecl iat_floor(double);                  // 0x011e0906

// @ 0x00890d20
float Layout::GetMaxBaseline(const TextStyle* pStyle)
{
    float fMax = 0.0f;
    FontMetrics metrics;
    LayoutSettings settings;
    LayoutSettings* pCur = &mLayoutSettings;

    if (pStyle)
    {
        FontServer* pServer = GetFontServer(true);
        settings.mFontSelection.clear();
        pServer->GetFonts(pStyle, &settings.mFontSelection, 0x1e, 1, -1, 1);
        pCur = &settings;
    }

    for (FontNode* p = pCur->mFontSelection.begin(); p != pCur->mFontSelection.end();
         p = RBTreeIncrement(p))
    {
        Font* pFont = p->mpFont;
        if (pFont)
        {
            metrics.mfSize = 0.0f;
            pFont->GetFontMetrics(&metrics);
            fMax = Max(fMax, metrics.mfBaseline);
        }
    }
    return fMax;
}

// @ 0x00890e20
float Layout::GetMinDescent(const TextStyle* pStyle)
{
    float fMin = 0.0f;
    FontMetrics metrics;
    LayoutSettings settings;
    LayoutSettings* pCur = &mLayoutSettings;

    if (pStyle)
    {
        FontServer* pServer = GetFontServer(true);
        settings.mFontSelection.clear();
        pServer->GetFonts(pStyle, &settings.mFontSelection, 0x1e, 1, -1, 1);
        pCur = &settings;
    }

    for (FontNode* p = pCur->mFontSelection.begin(); p != pCur->mFontSelection.end();
         p = RBTreeIncrement(p))
    {
        Font* pFont = p->mpFont;
        if (pFont)
        {
            metrics.mfSize = 0.0f;
            pFont->GetFontMetrics(&metrics);
            fMin = Min(fMin, (float)iat_floor((double)metrics.mfDescent));
        }
    }
    return fMin;
}

// @ 0x00890f50
Layout::Layout()
{
}

// @ 0x00890500
int Layout::AnalyzeText(const AnalysisInfo* pInfo, int nCount, AnalysisArray* pOut, int)
{
    pOut->resize(pOut->size() + 1);
    Analysis* pAnalysis = &pOut->back();

    const AnalysisInfo* pEnd = pInfo + nCount;
    const AnalysisInfo* p = pInfo;
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
    pAnalysis->mScript = kScriptDefault;
    pAnalysis->mnParity = 0;
    pAnalysis->mnParentParity = 0;
    pAnalysis->mbJoinBefore = 0;
    pAnalysis->mbJoinAfter = 0;
    return 1;
}

// @ 0x00890570
int Layout::LayoutTextLine(int a1, int a2, float fX, float fY, const TextStyle* pStyle,
                           GlyphAttributes* pGlyphs, unsigned int nMaxGlyphs,
                           LayoutMetrics* pMetrics)
{
    int nGlyphCount = 0;
    float fSpace = 1.0f;
    float fVisibleSpace = 0.0f;
    const TextStyle* pCurStyle = pStyle;

    EnterCriticalSection(g_csText);

    if (pCurStyle == 0)
        pCurStyle = &mLayoutSettings.mTextStyleDefault;

    if (a2 != 0)
    {
        if (mLayoutSettings.mFontSelection.mnSize == 0)
        {
            FontServer* pServer = GetFontServer(true);
            mLayoutSettings.mFontSelection.clear();
            pServer->GetFonts(pCurStyle, &mLayoutSettings.mFontSelection, kScriptDefault, 1, -1, 1);
        }

        AnalysisInfo info;
        info.mpTextStyle = (const TextStyle*)a1;
        info.mpFont = (Font*)a2;

        RunInfoArray* pRuns = (RunInfoArray*)&g_runInfoLine;
        pRuns->clear();
        AnalyzeText(&info, 1, (AnalysisArray*)&g_runInfoPara, 0);

        if (nMaxGlyphs > 0x400)
            nMaxGlyphs = 0x400;

        unsigned int nShaped = ShapeGlyphs(this, &info, 1, &g_glyphIndex[1],
                                           (RunInfo*)&g_runInfoPara,
                                           ((RunInfoArray*)&g_runInfoPara)->size(),
                                           &g_glyphAttributes[0], nMaxGlyphs, g_glyphClusters);
        GlyphAttributes aMetrics[4];
        GlyphMetrics(&g_glyphAttributes[0], nShaped, aMetrics);

        if (nShaped <= nMaxGlyphs)
        {
            if (mLayoutSettings.mbCellTopPosition)
                fY = mLayoutSettings.mfYScale * fSpace + fY;

            nGlyphCount = PlaceGlyphs((RunInfo*)&g_runInfoPara,
                                      ((RunInfoArray*)&g_runInfoPara)->size(),
                                      &g_glyphIndex[1], &g_glyphAttributes[0],
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
            fWidth = (g_glyphAttributes[nGlyphCount - 1].mfAdvance
                      + g_glyphAdvance[nGlyphCount - 1].mfValue) - fX;
        pMetrics->mfSpace = fWidth;
        while (nGlyphCount != 0)
        {
            if (!IsSpace((wchar16)g_glyphAttributes[nGlyphCount - 1].mGlyphId, 0xff, 0))
                break;
            --nGlyphCount;
        }
        pMetrics->mnVisibleSize = (uint32_t)nGlyphCount;
        pMetrics->mfVisibleSpace = 0.0f;
    }

    LeaveCriticalSection(g_csText);
    return nGlyphCount;
}

// @ 0x00890010
unsigned int Layout::LayoutText(const TextRun* pRuns, int nRuns, unsigned int nStart,
                                unsigned int nEnd, const int32_t* pGlyphIndex,
                                ClusterArray* pClusters, GlyphAdvanceSlot* pAdvances,
                                int32_t* pGlyphClusters, float fLineWidth,
                                unsigned int* pLineEnds, unsigned int nMaxLines,
                                float* pLineWidths)
{
    TextRunIterator it;
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

                TextRun& run = *it.mpArrayCurrent;
                unsigned int nRunEnd = run.mnTextSize;
                it.operator++();
                nPos = nChar + 1;

                unsigned int nGlyph = (unsigned int)pGlyphIndex[nPos];
                unsigned int nGlyphFirst = (unsigned int)pGlyphIndex[nChar];
                if (nGlyphFirst < nGlyph)
                {
                    GlyphAdvanceSlot* pAdv = &pAdvances[nGlyphFirst];
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
            if (mLayoutSettings.mTextStyleDefault.mOrientation == kOrientationVertical - 4)
            {
                int nGlyph = pGlyphIndex[nLineBegin];
                fLinePos = 0.0f;
                if (nLineBegin < nLimit)
                {
                    int32_t* pCluster = &pGlyphClusters[nGlyph];
                    GlyphAdvanceSlot* pAdv = &pAdvances[nGlyph];
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

// @ 0x00890830
int Layout::LayoutTextParagraph(int a2, int a3, float fX1, float fY1, float fX2,
                                float fY2, const TextStyle* pStyle, int a9,
                                unsigned int nMaxGlyphs, LayoutMetrics* pOut)
{
    int nTotal = 0;
    float fSpace = 1.0f;
    unsigned int nLines = 0;
    float fVisibleSpace = 0.0f;
    const TextStyle* pCurStyle = pStyle;
    unsigned int aLineEnds[256];
    float aLineWidths[256];
    GlyphAttributes aGlyphDummy[4];

    EnterCriticalSection(g_csText);

    if (pCurStyle == 0)
        pCurStyle = &mLayoutSettings.mTextStyleDefault;

    if (a3 != 0)
    {
        if (mLayoutSettings.mFontSelection.mnSize == 0)
        {
            FontServer* pServer = GetFontServer(true);
            mLayoutSettings.mFontSelection.clear();
            pServer->GetFonts(pCurStyle, &mLayoutSettings.mFontSelection, kScriptDefault, 1, -1, 1);
        }

        AnalysisInfo info;
        info.mpTextStyle = (const TextStyle*)a2;
        info.mpFont = (Font*)a3;

        ((RunInfoArray*)&g_runInfoPara)->clear();
        AnalyzeText(&info, 1, (AnalysisArray*)&g_runInfoPara, 0);

        if (nMaxGlyphs > 0x400)
            nMaxGlyphs = 0x400;

        unsigned int nShaped = ShapeGlyphs(this, &info, 1, &g_glyphIndex[1],
                                           (RunInfo*)&g_runInfoPara,
                                           ((RunInfoArray*)&g_runInfoPara)->size(),
                                           g_glyphAttributes, nMaxGlyphs, g_glyphClusters);
        GlyphMetrics(g_glyphAttributes, nShaped, aGlyphDummy);

        if (nShaped <= nMaxGlyphs)
        {
            float fLineAdvance = fSpace - fVisibleSpace;
            float fScaled = fLineAdvance * mLayoutSettings.mfYScale;
            nLines = LayoutText((const TextRun*)&info, 1, 0, (unsigned int)a3,
                                &g_glyphIndex[1], (ClusterArray*)&g_runInfoPara,
                                g_glyphAdvance, g_glyphClusters, fX2 - fX1,
                                aLineEnds, 0x100, aLineWidths);

            if (pCurStyle->mVAlignment == kVACenter)
                fY1 = (((fY2 - fY1) - (float)nLines * fLineAdvance) * 0.5f) * mLayoutSettings.mfYScale + fY1;
            else if (pCurStyle->mVAlignment == kVABottom)
                fY1 = fY2 - ((float)nLines * fLineAdvance) * mLayoutSettings.mfYScale;

            unsigned int nRuns = ((RunInfoArray*)&g_runInfoPara)->size();
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
                        RunInfo* pRun = (RunInfo*)&g_runInfoPara + nRun;
                        do
                        {
                            if (aLineEnds[nShaped] < (unsigned int)(pRun->mnCharBegin + pRun->mnCharEnd))
                                break;
                            ++nRunEnd;
                            pRun += 1;
                        } while (nRunEnd < nRuns);
                    }

                    float fLineX;
                    if (pCurStyle->mHAlignment == kHACenter)
                        fLineX = (fPenY - aLineWidths[nShaped]) * 0.5f + fPenX;
                    else
                    {
                        fLineX = fPenX;
                        if (pCurStyle->mHAlignment == kHARight)
                            fLineX = fX2 - aLineWidths[nShaped];
                    }

                    if (pCurStyle->mHAlignment == kHAJustify)
                    {
                        int nRunBegin = ((RunInfo*)&g_runInfoPara)[nRun].mnCharBegin;
                        RunInfo* pRunLast = (RunInfo*)&g_runInfoPara + nRunEnd;
                        JustifyGlyphs(&info, 1, nRunBegin,
                                      (pRunLast[-1].mnCharBegin + pRunLast[-1].mnCharEnd) - nRunBegin,
                                      &g_glyphIndex[1], g_glyphAttributes, nMaxGlyphs,
                                      g_glyphClusters, fPenY - aLineWidths[nShaped], 0);
                        fPenY = fLineAdvance;
                        fPenX = fX1;
                    }

                    int nPlaced = PlaceGlyphs((RunInfo*)&g_runInfoPara + nRun, nRunEnd - nRun,
                                              &g_glyphIndex[1], &g_glyphAttributes[0],
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

    LeaveCriticalSection(g_csText);
    return nTotal;
}

// @ 0x00890cc0
float Layout::GetTextLayoutMetrics(int a1, int a2, const TextStyle* pStyle, LayoutMetrics* pOut)
{
    EnterCriticalSection(g_csText);
    LayoutTextLine(a1, a2, 0.0f, 0.0f, pStyle, (GlyphAttributes*)&g_textStyleScratch, 0x400, pOut);
    float fResult = pOut->mfSpace;
    LeaveCriticalSection(g_csText);
    return fResult;
}

// @ 0x00890fa0
void OutlineFont::SetOption(int option, int value)
{
    if (option == 1)
        mbOption1 = (value != 0);
}

// @ 0x00890f60
int __cdecl CompareFontCallback(IFontCompareTarget* pTarget, int32_t a2, int32_t a3, int32_t a4)
{
    if (pTarget->HasFont(a3, 0))
    {
        if (pTarget->FindFont(a2, a4) == a4)
            return 0;
    }
    return -1;
}
