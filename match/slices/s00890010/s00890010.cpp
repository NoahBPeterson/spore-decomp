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

struct TextStyle {                // 0x278 bytes (only ever constructed elsewhere)
    uint32_t mData[0x9e];
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

struct Layout {                   // 0x37c bytes
    LayoutSettings mLayoutSettings;
    Layout();
    float GetMaxBaseline(const TextStyle* pStyle);           // 0x00890d20
    float GetMinDescent(const TextStyle* pStyle);            // 0x00890e20
};

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
