// src/game/UTFSpore_Win32/MessageBox.cpp -- migrated from slice(s) s01300280, s0097f390 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/MessageBox.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWinControls/IWinText.h"
#include "EA/UTFWin/IWindow.h"

// unnamed retail callees and globals (address in the comment)
extern const wchar_t g_OK[];        // 0x014439bc
extern const wchar_t g_Yes[];       // 0x014439b4
extern const wchar_t g_No[];        // 0x014439ac
extern const wchar_t g_Cancel[];    // 0x0144399c
#include <intrin.h>

// ---- items of slice s0097f390 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct Rect {
    float x1, y1, x2, y2;
    Rect(float a, float b, float c, float d) : x1(a), y1(b), x2(c), y2(d) {}
};
struct IWindowManager;
struct IWindow;
struct Msg {                    // UTFWin::Message
    IWindow* source;            // +0
    int      type;              // +4
    int      eventType;         // +8
    int      pad0c, pad10;
    float*   out;               // +0x14
};
struct IWindowManager {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual bool SendMsg(IWindow* src, IWindow* dst, const Msg* msg, bool inheritable);   // +0x10
};
struct IWindow {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10();
    virtual IWindowManager* GetWindowManager();            // +0x14
    virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual uint GetFlags();                               // +0x28
    virtual void s2c(); virtual void s30(); virtual void s34();
    virtual const float* GetRealArea();                    // +0x38
    virtual void s3c(); virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
    virtual void SetArea(const Rect* r);                   // +0x60
    virtual void s64(); virtual void s68(); virtual void s6c(); virtual void s70(); virtual void s74();
    virtual void s78();
    virtual void SetFlag(uint flag, bool value);           // +0x7c
    virtual void SetCaption(const wchar_t* text);          // +0x80
    virtual void SetTextFontID(uint style);                // +0x84
    virtual void s88(); virtual void s8c(); virtual void s90(); virtual void s94(); virtual void s98();
    virtual void s9c(); virtual void sa0(); virtual void sa4(); virtual void sa8(); virtual void sac();
    virtual void sb0(); virtual void sb4(); virtual void sb8(); virtual void sbc(); virtual void sc0();
    virtual void sc4(); virtual void sc8(); virtual void scc(); virtual void sd0(); virtual void sd4();
    virtual void AddWindow(IWindow* w);                    // +0xd8
};
struct IWinButton {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual IWindow* GetWindow();                          // +0x10
    virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual void s28(); virtual void s2c(); virtual void s30(); virtual void s34(); virtual void s38();
    virtual void s3c(); virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50();
    virtual void SetBorder(float l, float t, float r, float b);   // +0x54
    virtual void s58(); virtual void s5c();
    virtual void SetDrawable(void* d);                     // +0x60
};
struct IWinText {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual IWindow* GetWindow();                          // +0x10
    virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual void SetTextColor(uint c);                     // +0x28
    virtual void s2c(); virtual void s30(); virtual void s34();
    virtual void SetBorder(float l, float t, float r, float b);   // +0x38
};
struct IMsgBoxSub {                                        // IWinMessageBox sub-object at +0x338
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10();
    virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual void s28(); virtual void s2c(); virtual void s30(); virtual void s34(); virtual void s38();
    virtual void s3c(); virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c(); virtual void s60();
    virtual void s64(); virtual void s68(); virtual void s6c(); virtual void s70(); virtual void s74();
    virtual void s78();
    virtual void AddButton(const wchar_t* text, int id, int a, int b);   // +0x7c
};
struct AutoRefCountText {                                  // EA::AutoRefCount<IWinText>
    IWinText* mpObject;
    void Assign(IWinText* p);                              // @ 0x00b5f950 (operator=)
};
IWinText* WinText_CreateDefault(int a, uint b);            // @ 0x00989130 (cdecl)
extern const wchar_t g_OK[];        // 0x014439bc
extern const wchar_t g_Yes[];       // 0x014439b4
extern const wchar_t g_No[];        // 0x014439ac
extern const wchar_t g_Cancel[];    // 0x0144399c
struct WinMessageBox {
    char     pad0[4];
    char     pad4[0x2d0 - 4];
    float    mClient[4];            // +0x2d0: client-area rectangle (l, t, r, b)
    char     pad2e0[0x338 - 0x2e0];
    IMsgBoxSub mSub;                // +0x338 (vptr only)
    uint     mnType;                // +0x33c
    float    mfGutter;              // +0x340
    float    mfTextBorder[4];       // +0x344
    float    mfButtonBorder[4];     // +0x354
    float    mfButtonMinW;          // +0x364
    float    mfButtonMinH;          // +0x368
    float    mfButtonSpacing;       // +0x36c
    float    mfButtonW;             // +0x370
    float    mfButtonH;             // +0x374
    uint     mnButtonTextStyle;     // +0x378
    uint     mnButtonAlignment;     // +0x37c
    IWinButton** mpButtonsBegin;    // +0x380
    IWinButton** mpButtonsEnd;      // +0x384
    char     pad388[0x3b4 - 0x388];
    wchar_t* mpTextBegin;           // +0x3b4 (msMessageText begin)
    wchar_t* mpTextEnd;             // +0x3b8
    char     pad3bc[0x3c4 - 0x3bc];
    uint     mnMessageTextStyle;    // +0x3c4
    uint     mnMessageTextColor;    // +0x3c8
    AutoRefCountText mpMessageText; // +0x3cc
    void*    mpButtonDrawable;      // +0x3d0

    __forceinline uint ButtonCount() const { return (uint)(mpButtonsEnd - mpButtonsBegin); }
    bool WinDialogRefresh();        // @ 0x0096c6f0
    bool Refresh();                 // @ 0x0097f390
};
// ---- items of slice s0097f390 end

// @ 0x0097f390
bool WinMessageBox::Refresh()
{
    if (WinDialogRefresh()) {
    if (mpButtonsBegin == mpButtonsEnd) {
        switch (mnType) {
        case 1:
            mSub.AddButton(g_OK, 0, 0, 1);
            break;
        case 2:
            mSub.AddButton(g_OK, 0, 0, 1);
            mSub.AddButton(g_Cancel, 3, 0, 0);
            break;
        case 3:
            mSub.AddButton(g_Yes, 1, 0, 1);
            mSub.AddButton(g_No, 2, 0, 0);
            break;
        case 4:
            mSub.AddButton(g_Yes, 1, 0, 1);
            mSub.AddButton(g_No, 2, 0, 0);
            mSub.AddButton(g_Cancel, 3, 0, 0);
            break;
        }
    }

    if (mpTextBegin == mpTextEnd || mnMessageTextStyle == 0) {
        if (mpMessageText.mpObject)
            mpMessageText.mpObject->GetWindow()->SetFlag(1, false);
    } else {
        if (!mpMessageText.mpObject) {
            mpMessageText.Assign(WinText_CreateDefault(-1, 0xf170dc1));
            if (mpMessageText.mpObject)
                ((IWindow*)((char*)this + 4))->AddWindow(mpMessageText.mpObject->GetWindow());
        }
        if (mpMessageText.mpObject) {
            mpMessageText.mpObject->GetWindow()->SetCaption(mpTextBegin);
            mpMessageText.mpObject->GetWindow()->SetTextFontID(mnMessageTextStyle);
            mpMessageText.mpObject->GetWindow()->SetFlag(1, true);
            mpMessageText.mpObject->GetWindow()->SetFlag(0x200, true);
            mpMessageText.mpObject->GetWindow()->SetFlag(0x10, true);
            mpMessageText.mpObject->SetTextColor(mnMessageTextColor);
            mpMessageText.mpObject->SetBorder(mfTextBorder[0], mfTextBorder[1], mfTextBorder[2], mfTextBorder[3]);
        }
    }

    mfButtonH = 0.0f;
    mfButtonW = 0.0f;
    _ReadWriteBarrier();

    if (mpButtonsBegin != mpButtonsEnd) {
        _ReadWriteBarrier();
        IWinButton** it = mpButtonsBegin;
        mfButtonH = mfButtonMinH;
        mfButtonW = mfButtonMinW;
        for (; it != mpButtonsEnd; ++it) {
            IWinButton* btn = *it;
            if (btn) {
                btn->SetBorder(mfButtonBorder[0], mfButtonBorder[1], mfButtonBorder[2], mfButtonBorder[3]);
                btn->GetWindow()->SetTextFontID(mnButtonTextStyle);
                if (mpButtonDrawable)
                    btn->SetDrawable(mpButtonDrawable);
                const float* r = btn->GetWindow()->GetRealArea();
                float w = r[2] - r[0];
                r = btn->GetWindow()->GetRealArea();
                float h = r[3] - r[1];
                IWindow* win = btn->GetWindow();
                if (win) {
                    float out[2];
                    Msg m;
                    m.out = out;
                    m.type = 0x16;
                    m.eventType = 0;
                    if (win->GetWindowManager()) {
                        if (win->GetWindowManager()->SendMsg(win, win, &m, false))
                            w = out[1];
                    }
                }
                if (w > mfButtonW)
                    mfButtonW = w;
                if (h > mfButtonH)
                    mfButtonH = h;
                IWindow* bw = btn->GetWindow();
                Rect rc(0.0f, 0.0f, mfButtonW, mfButtonH);
                bw->SetArea(&rc);
            }
        }
        for (IWinButton** it = mpButtonsBegin; it != mpButtonsEnd; ++it) {
            if (*it) {
                IWindow* w = (*it)->GetWindow();
                Rect rc(0.0f, 0.0f, mfButtonW, mfButtonH);
                w->SetArea(&rc);
            }
        }
        float a = (float)(ButtonCount() - 1) * mfButtonSpacing;
        _ReadWriteBarrier();
        mfButtonW = a + (float)ButtonCount() * mfButtonW;
    }

    if (mpMessageText.mpObject) {
        if (mpMessageText.mpObject->GetWindow()->GetFlags() & 1) {
            float g = mfGutter;
            Rect rc(mClient[0] + g, mClient[1] + g, mClient[2] - g, (mClient[3] - mfButtonH) - g * 2.0f);
            mpMessageText.mpObject->GetWindow()->SetArea(&rc);
        }
    }

    if (mpButtonsBegin != mpButtonsEnd) {
        float y = mClient[1] + mfGutter;
        if (mpMessageText.mpObject) {
            if (mpMessageText.mpObject->GetWindow()->GetFlags() & 1)
                y = mpMessageText.mpObject->GetWindow()->GetRealArea()[3] + mfGutter;
        }
        float g = mfGutter;
        y = ((((mClient[3] - y) - mfButtonH) - g) * 0.5f) + y;
        float x = mClient[0];
        switch (mnButtonAlignment) {
        case 1:
            x = x + g;
            break;
        case 2:
            x = (mClient[2] - mfButtonW) - g;
            break;
        case 3:
            x = ((((mClient[2] - x) - mfButtonW) - g * 2.0f) * 0.5f + x) + g;
            break;
        }
        for (IWinButton** it = mpButtonsBegin; it != mpButtonsEnd; ++it) {
            IWindow* win = (*it)->GetWindow();
            if (win) {
                const float* r = win->GetRealArea();
                float bottom = (r[3] - r[1]) + y;
                r = win->GetRealArea();
                Rect rc(x, y, (r[2] - r[0]) + x, bottom);
                win->SetArea(&rc);
            }
            const float* r2 = win->GetRealArea();
            x = ((r2[2] - r2[0]) + mfButtonSpacing) + x;
        }
    }
    return true;
    }
    return false;
}

// @ 0x01300b20
void init_154f94c()
{
    *(int*)0x154f94c = 1;
    *(int*)0x154f950 = 0;
    *(int*)0x154f954 = 0;
    *(int*)0x154f958 = 0xeec2c011;
    *(short*)0x154f95c = 0xb;
    *(int*)0x154f960 = 0x340;
    *(int*)0x154f964 = 1;
}
