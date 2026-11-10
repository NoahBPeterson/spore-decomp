// EA::Text::GetMaxFontMetrics — walks a set of fonts, querying each font's
// metrics and accumulating the highest baseline and the lowest descent.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

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

// vtable view of EA::Text::Font: slot 12 (+0x30) is GetFontMetrics.
struct FontObj
{
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual bool GetFontMetrics(FontMetrics& metrics);   // +0x30
};

// eastl::rbtree node holding a Font* value at +0x10.
struct FontNode
{
    FontNode* mpRight;           // +0x00
    FontNode* mpLeft;            // +0x04
    FontNode* mpParent;          // +0x08
    int       mColor;            // +0x0c
    FontObj*  mpFont;            // +0x10
};

struct FontSet
{
    int      mPad00;             // +0x00
    FontNode mSentinel;          // +0x04
};

void* __cdecl RBTreeIncrement(void* node);   // 0x00921580

template <typename T> __forceinline T& Max(T& a, T& b) { return a < b ? b : a; }
template <typename T> __forceinline T& Min(T& a, T& b) { return b < a ? b : a; }

// @ 0x008985b0
void GetMaxFontMetrics(FontSet* fonts, float* a, float* b)
{
    FontMetrics metrics;
    *(int*)&metrics.mfSize = 0;   // original stores a zero dword, not movss

    FontNode* node = fonts->mSentinel.mpLeft;
    FontNode* end  = &fonts->mSentinel;
    if (node != end)
    {
        do
        {
            node->mpFont->GetFontMetrics(metrics);
            *a = Max(*a, metrics.mfBaseline);
            *b = Min(*b, metrics.mfDescent);
            node = (FontNode*)RBTreeIncrement(node);
        } while (node != end);
    }
}
