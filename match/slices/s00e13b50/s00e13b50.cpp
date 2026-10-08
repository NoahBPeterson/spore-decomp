// Slice s00e13b50 -- SP::cUICard layout pass (the PDB-derived name "interface_cast<cSPMission*>" is a
// mislabel): after the card text changed, resize the description/background windows to fit, either
// instantly (SetSize) or through cSPUIAnimator size animations, then tell the "0x5397388" button child
// to switch state.  Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Rect {
    float x1, y1, x2, y2;
    Rect() {}
    Rect(float a, float b, float c, float d) : x1(a), y1(b), x2(c), y2(d) {}
};

struct IWinText {                                       // result of Cast(0xf15f4bd) on a text window
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4();
    virtual void SetFlagOn(int v);                      // +0x14
};
struct IWinButton {                                     // result of Cast(0x8ed27e7a)
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4();
    virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9();
    virtual void SetButtonState(int state, int arg);    // +0x28
};
struct IWindow {
    virtual void w0(); virtual void Release(); virtual void w2();
    virtual void* Cast(uint32_t id);                    // +0x0c
    virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8();
    virtual void w9(); virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13();
    virtual const Rect& GetArea();                      // +0x38
    virtual const char* GetCaption();                   // +0x3c
    virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19(); virtual void w20();
    virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24(); virtual void w25();
    virtual void SetSize(float w, float h);             // +0x68
    virtual void w27();
    virtual void SetLocation(float x, float y);         // +0x70
    virtual void w29(); virtual void w30(); virtual void w31(); virtual void w32(); virtual void w33(); virtual void w34();
    virtual void w35(); virtual void w36(); virtual void w37(); virtual void w38(); virtual void w39();
    virtual void w40(); virtual void w41(); virtual void w42(); virtual void w43(); virtual void w44();
    virtual void w45(); virtual void w46(); virtual void w47(); virtual void w48(); virtual void w49();
    virtual void w50(); virtual void w51(); virtual void w52(); virtual void w53(); virtual void w54();
    virtual void w55(); virtual void w56(); virtual void w57(); virtual void w58(); virtual void w59();
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);   // +0xf0
};
// FUN_00e12f80 etc: if (w) w->vslot7c(1, v)
void __cdecl SetWindowFlag1(IWindow* w, bool v);                    // 0x00e12f80
IWinText* __cdecl CastToText(IWindow** pw);                        // 0x005e1fd0 (*pw)->Cast(0xf15f4bd)
IWinButton* __cdecl CastToButton(IWindow* w);                      // 0x005ca960 w->Cast(0x8ed27e7a)
float __cdecl GetElapsedSeconds();                                 // 0x00805080
void __cdecl AutoSizeWindowForText(IWindow* w, int a, int b);      // 0x00806e40
int __cdecl GetCurrentGameMode();                                  // 0x00b5b800

struct AnimBuf {
    uint32_t d[0x80 / 4];
    void Destroy();                                     // 0x0059a1e0
};
struct cAnimator {
    void AddAnimation(AnimBuf* anim, IWindow* win, int flags);     // 0x007f8d10
    void Clear();                                                  // 0x007f8f00
};
AnimBuf* __cdecl SPUICreateWindowAnimationTargetSize(AnimBuf* out, IWindow* win, const float* size,
                                                     float now, float duration, int type);   // 0x007f8230

static const int kModeX = 0x1654c10;

struct cUICard {
    void*      vtbl0;
    void*      vtbl4;
    char       pad08[0x24 - 0x08];
    IWindow*   mpMainWin;       // +0x24
    cAnimator* mpAnimator;      // +0x28
    IWindow*   mpDescWin;       // +0x2c
    IWindow*   mpTextWin;       // +0x30
    IWindow*   pad34;
    IWindow*   mpWinA;          // +0x38
    IWindow*   mpWinB;          // +0x3c
    IWindow*   pad40;
    IWindow*   mpWinC;          // +0x44
    uint32_t   pad48[(0x68 - 0x48) / 4];
    Rect       mAreaA;          // +0x68 initial area of mpWinA
    Rect       mAreaB;          // +0x78 initial area of mpWinB
    Rect       mAreaC;          // +0x88 initial area of mpWinC

    IWindow* FindWindowByID(uint32_t id);               // 0x00e13390
    void ResizeToContent(bool animate, int style);      // @ 0x00e13b50
};

// @ 0x00e13b50
void cUICard::ResizeToContent(bool animate, int style) {
    if (!mpTextWin) return;
    if (!mpWinA) return;
    if (!mpWinB) return;
    if (!mpWinC) return;

    float now = GetElapsedSeconds();
    mpAnimator->Clear();
    const Rect* areaA = &mpWinA->GetArea();
    const Rect* areaB = &mpWinB->GetArea();
    const Rect* areaC = &mpWinC->GetArea();
    AutoSizeWindowForText(mpTextWin, 0, 1);
    const Rect* r = &mpTextWin->GetArea();
    float top = r->y1;
    float bottom = r->y2;

    if (GetCurrentGameMode() == kModeX) {
        IWindow* c1 = FindWindowByID(0x7f453b8);
        IWindow* c2 = FindWindowByID(0x7f5abd0);
        c2->GetArea();
        const Rect* t = &mpTextWin->GetArea();
        float textH = t->y2 - t->y1;
        const Rect* ca = &c1->GetArea();
        bool bigger = textH > (ca->y2 - ca->y1);
        SetWindowFlag1(c1, bigger);
        SetWindowFlag1(mpTextWin, !bigger);
        if (bigger) {
            const Rect* ra = &c1->GetArea();
            top = ra->y1;
            bottom = ra->y2;
        }
    }

    float y = (bottom - top) + top;
    IWindow* d0 = mpDescWin;
    if (d0 && d0->GetCaption()) {
        IWindow* d = mpDescWin;
        const Rect* da = &d->GetArea();
        d->SetLocation(da->x1, y);
        CastToText(&mpDescWin)->SetFlagOn(1);
        const Rect* da2 = &mpDescWin->GetArea();
        y = (da2->y2 - da2->y1) + y;
    }

    uint32_t extraId = 0;
    switch (style) {
    case 1: extraId = 0x574efda; break;
    case 2: extraId = 0xf5a74bec; break;
    default: break;
    }
    IWindow* extra = extraId ? FindWindowByID(extraId) : 0;
    if (extra) {
        const Rect* ea = &extra->GetArea();
        float eh = ea->y2 - ea->y1;
        if (eh > (y - top))
            y = (eh - (y - top)) + y;
        extra->SetLocation(ea->x1, ((y - top) * 0.5f + top) - eh * 0.5f);
    }

    Rect rA(mAreaA.x1, mAreaA.y1, (mAreaA.x2 - mAreaA.x1) + mAreaA.x1,
            (float)fabs((y + 8.0f) - mAreaA.y1) + mAreaA.y1);
    Rect rC(mAreaC.x1, mAreaC.y1, (mAreaC.x2 - mAreaC.x1) + mAreaC.x1,
            ((rA.y2 - mAreaA.y2) + (mAreaC.y2 - mAreaC.y1)) + mAreaC.y1);

    IWindow* child = mpMainWin->FindWindowByID(0x35b08191, true);
    bool notX = GetCurrentGameMode() != kModeX;
    float hA = rA.y2 - rA.y1;

    if (animate) {
        AnimBuf anim;
        float size[2];
        size[0] = rA.x2 - rA.x1;
        size[1] = hA;
        mpAnimator->AddAnimation(SPUICreateWindowAnimationTargetSize(&anim, mpWinA, size, now,
                                     (float)fabs(hA - (areaA->y2 - areaA->y1)) * 0.002f, 1), mpWinA, 0);
        anim.Destroy();
        if (notX) {
            size[0] = mAreaB.x2 - mAreaB.x1;
            float hB = mAreaB.y2 - mAreaB.y1;
            size[1] = hB;
            mpAnimator->AddAnimation(SPUICreateWindowAnimationTargetSize(&anim, mpWinB, size, now,
                                         (float)fabs(hB - (areaB->y2 - areaB->y1)) * 0.002f, 1), mpWinB, 0);
            anim.Destroy();
        }
        float hC = rC.y2 - rC.y1;
        float wC = rC.x2 - rC.x1;
        size[0] = wC;
        size[1] = hC;
        mpAnimator->AddAnimation(SPUICreateWindowAnimationTargetSize(&anim, mpWinC, size, now,
                                     (float)fabs(hC - (areaC->y2 - areaC->y1)) * 0.002f, 1), mpWinC, 0);
        anim.Destroy();
        if (child) {
            size[0] = wC;
            size[1] = hC;
            mpAnimator->AddAnimation(SPUICreateWindowAnimationTargetSize(&anim, child, size, now,
                                         (float)fabs(hC - (areaC->y2 - areaC->y1)) * 0.002f, 1), child, 0);
            anim.Destroy();
        }
    } else {
        mpWinA->SetSize(rA.x2 - rA.x1, hA);
        if (notX)
            mpWinB->SetSize(mAreaB.x2 - mAreaB.x1, mAreaB.y2 - mAreaB.y1);
        float hC = rC.y2 - rC.y1;
        float wC = rC.x2 - rC.x1;
        mpWinC->SetSize(wC, hC);
        if (child)
            child->SetSize(wC, hC);
    }

    IWindow* btnWin = mpMainWin->FindWindowByID(0x5397388, true);
    if (btnWin) {
        IWinButton* btn = CastToButton(btnWin);
        if (btn)
            btn->SetButtonState(4, 0);
    }
}
