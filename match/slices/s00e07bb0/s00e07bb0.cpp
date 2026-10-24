// s00e07bb0 -- SP::cSPUIMineralBar::UpdateMeter
//
// Refreshes the civilization mineral bar: the phase meter, the mineral name /
// colour, the per-turn extraction amount and the phase text.  Layout stubs for
// the UI and noun classes follow the retail layouts recovered from the code.
#include "types.h"

namespace SP {

class cSPUILayout;
class cCommunity;
class cNoun;

// ---------------------------------------------------------------- strings
// eastl::basic_string<wchar_t>: begin / end / capacity / allocator.
struct WStr {
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    uint32_t mAllocator;    // +0x0c

    WStr() : mpBegin(0), mpEnd(0), mpCapacity(0) {}

    ~WStr()
    {
        if ((((int)((char*)mpCapacity - (char*)mpBegin) & 0xfffffffe) > 2) && mpBegin)
            operator delete(mpBegin);
    }

    void RangeInitialize(const wchar_t* p);     // 0x00579a90
    void append(const wchar_t* p);              // 0x005c3d90
};

// The phase scratch and the mineral-name string share one stack object so the
// name begins four bytes after the phase slot (the retail frame layout).
struct NameSlot {
    union {
        uint32_t mPad;
        float    mPhase;
        int      mPhaseInt;
    };
    WStr mName;
};

void __cdecl operator delete(void* p);          // 0x00f47380

// The localization helper returns a temporary 0x14-byte cString.
struct cString {
    char mData[0x14];

    cString(uint32_t a, uint32_t b, int c);     // 0x006b5770
    ~cString();                                 // 0x006b5240
    const wchar_t* GetText();                   // 0x006b55c0
};

// ---------------------------------------------------------------- UI
class IWindow {
public:
    virtual void v00();                          // +0x00
    virtual void SetProgress(float value);       // +0x04
    virtual void v08();                          // +0x08
    virtual IWindow* GetSubWindow(uint32_t id);  // +0x0c
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void SetColor(uint32_t color);       // +0x5c
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void SetVisible(int a, int b);       // +0x7c
    virtual void SetText(const wchar_t* text);   // +0x80
};

class cSPUILayout {
public:
    IWindow* FindWindowByID(uint32_t id, int deep);   // 0x008105b0
};

// ---------------------------------------------------------------- nouns
class cNounName {
public:
    virtual void v00();                          // +0x00
    virtual const wchar_t* GetText();            // +0x04
    uint32_t mPad;                               // +0x08
};

class cNounColor {
public:
    uint32_t mValue;                             // +0x00
    uint32_t GetPacked();                        // 0x00b6f310
};

class cNoun {
public:
    uint32_t pad00[0x0d];                        // +0x00 .. +0x33
    cNounName mName;                             // +0x34
    cNounColor mColor;                           // +0x3c
    uint32_t pad40[0x12];                        // +0x40 .. +0x87
    uint8_t pad88;                               // +0x88
    uint8_t mFlag89;                             // +0x89
};

class cCommunity {
public:
    float GetPhaseRatio();                       // 0x00bfdea0
    float ReadPhase(int phase);                  // 0x00bfde50
    cNoun* GetNoun();                            // 0x00bfdf80
};

float __cdecl FUN_00bd80d0(cNoun* pNoun);        // 0x00bd80d0
void __cdecl FUN_00881ea0(double value, void* buffer, int maxLen, int flags);   // 0x00881ea0

extern wchar_t DAT_013ec468[];                   // 0x013ec468

// The mineral bar subclasses the meter; only the fields used here are named.
class cSPUIMineralBar {
public:
    void* mVtbl0;                                // +0x00
    void* mVtbl1;                                // +0x04
    uint32_t m_nFlags08;                         // +0x08
    uint8_t m_bRangeType;                        // +0x0c
    uint8_t m_pad0d[3];                          // +0x0d
    cSPUILayout* mLayout;                        // +0x10
    void* m_pSource;                             // +0x14
    uint32_t m_nRootID;                          // +0x18
    uint32_t m_nWindowID;                        // +0x1c
    uint32_t m_nStart;                           // +0x20
    uint32_t m_nNext;                            // +0x24
    cCommunity* mpCommunity;                     // +0x28
    int32_t m_nModelExtra;                       // +0x2c
    void* m_pTracked;                            // +0x30
    void* m_pLinkA;                              // +0x34
    void* m_pLinkB;                              // +0x38

    void UpdateMeter();                          // 0x00e07bb0
};

// @ 0x00e07bb0
void cSPUIMineralBar::UpdateMeter()
{
    if (mLayout == 0)
        return;
    if (mpCommunity == 0)
        return;

    float value = mpCommunity->GetPhaseRatio() * 100.0f;

    IWindow* pMeter = mLayout->FindWindowByID(m_nWindowID, 1);
    IWindow* pSub = pMeter->GetSubWindow(0x10edf11);
    if (pSub != 0) {
        float clamped = value;
        if (clamped < 0.0f)
            clamped = 0.0f;
        if (clamped > 100.0f)
            clamped = 100.0f;
        pSub->SetProgress(clamped);
    }

    cNoun* pNoun = mpCommunity->GetNoun();
    uint32_t color = 0x8c79898d;
    NameSlot nameSlot;
    nameSlot.mName.RangeInitialize(DAT_013ec468);

    if (pNoun != 0) {
        color = pNoun->mColor.GetPacked();
        nameSlot.mName.append(pNoun->mName.GetText());
    }
    else {
        nameSlot.mName.append(cString(0x2db6dad3, 0x63c3d96, 0).GetText());
    }

    IWindow* pWindow = mLayout->FindWindowByID(0x62478b8, 1);
    if (pWindow != 0)
        pWindow->SetColor(color);

    pWindow = mLayout->FindWindowByID(0x6245a18, 1);
    if (pWindow != 0)
        pWindow->SetText(nameSlot.mName.mpBegin);

    pWindow = mLayout->FindWindowByID(0x46adf86, 1);
    pSub = pWindow->GetSubWindow(0x10edf11);
    if (pSub != 0) {
        pWindow->SetVisible(1, (pNoun != 0 && pNoun->mFlag89 == 0)
                                 ? (pSub->SetProgress(FUN_00bd80d0(pNoun)), 1)
                                 : 0);
    }

    nameSlot.mPhase = mpCommunity->ReadPhase(0);
    nameSlot.mPhaseInt = (int)nameSlot.mPhase;
    wchar_t buffer[40];
    buffer[0] = 0;
    FUN_00881ea0((double)nameSlot.mPhaseInt, buffer, 0x28, 0);

    WStr phaseText;
    phaseText.RangeInitialize(buffer);

    pWindow = mLayout->FindWindowByID(0x55155f9, 1);
    if (pWindow != 0) {
        pSub = pWindow->GetSubWindow(0xeeee8218);
        if (pSub != 0)
            pSub->SetText(phaseText.mpBegin);
    }
}

} // namespace SP
