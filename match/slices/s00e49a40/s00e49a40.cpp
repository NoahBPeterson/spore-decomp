// Slice s00e49a40 -- mission panel update: a window slides/rotates in and out through an 8-state machine.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- data types
struct Key12 { uint32_t a, b, c; };
struct Vec4 {
    float x, y, z, w;
    Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
    Vec4(const Vec4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};

// ---------------------------------------------------------------- globals
extern float g_15a5b54;                // 0x015a5b54: rotation angle
extern float g_15a5b58;                // 0x015a5b58: extra rotation offset

// ---------------------------------------------------------------- external objects
struct IWindow {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4();
    virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9();
    virtual void w10(); virtual void w11(); virtual void w12();
    virtual const float* GetOffset();                   // +0x34 (two floats)
    virtual void w14(); virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18();
    virtual void w19(); virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
    virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27();
    virtual void SetAnchor(float x, float y);           // +0x70
    virtual void w29(); virtual void w30();
    virtual void SetFlag(int flag, bool value);         // +0x7c
};
struct IReleasable { virtual void w0(); virtual void Release(); };   // Release at +4

struct cModel {                                         // result of cMission::GetModel
    virtual void w0();  virtual void w1();  virtual void w2();  virtual void w3();  virtual void w4();
    virtual void w5();  virtual void w6();  virtual void w7();  virtual void w8();  virtual void w9();
    virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14();
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
    virtual int GetKind();                              // +0x60
};
struct cMission {
    cModel*  GetModel();                                // 0x00c45ce0
    IWindow* GetPanelWindow();                          // 0x00ff35d0
};
struct cModelPanel {                                    // FUN_00e19cf0(model)
    virtual void w0();  virtual void w1();  virtual void w2();  virtual void w3();  virtual void w4();
    virtual void w5();  virtual void w6();  virtual void w7();  virtual void w8();  virtual void w9();
    virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14();
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24();
    virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29();
    virtual void Notify();                              // +0x78
};
cModelPanel* __cdecl FUN_00e19cf0(cModel* model);       // 0x00e19cf0

struct cSink {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4();
    virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9();
    virtual void SetActive(int on);                     // +0x28
};
extern cSink* g_169e230;                                // 0x0169e230

struct cImage { uint32_t pad0; uint8_t flags; };        // flags at +4, bit 0 = loaded
struct cResourceManager {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4();
    virtual void w5(); virtual void w6();
    virtual cImage* GetImage(Key12 key, int flags);     // +0x1c
};
cResourceManager* __cdecl FUN_0067dd60();               // 0x0067dd60
int __cdecl GetCurrentGameMode();                       // 0x00b5b800

struct cImageRef {
    cImage* p;
    void Set(cImage* img);                              // 0x00576650
};

struct AnimBuf {
    uint32_t d[0x80 / 4];
    void Destroy();                                     // 0x0059a1e0: ~cSPUIWindowAnimation
};
struct cAnimator {
    void RemoveAnimation(IWindow* win, int channel);    // 0x007f6210
    void AddAnimation(AnimBuf* anim, IWindow* win, int flags);   // 0x007f8d10
    void Update();                                      // 0x007f63b0
};
AnimBuf* __cdecl SPUICreateWindowAnimationRotation(AnimBuf* out, IWindow* win, Vec4 rot,
                                                   float duration, float from, int type);   // 0x007f8140
float __cdecl GetElapsedSeconds();                      // 0x00805080
struct Quat { float x, y, z, w; };
void __cdecl SetWindowRotation(IWindow* win, const Quat* quat);   // 0x00808230

struct cSubPanel { void FUN_00e49db0(); };              // 0x00e49db0

// ---------------------------------------------------------------- the panel
struct cMissionPanel {
    char       pad0[0xc];
    char       mbFlag;            // +0x0c
    char       pad1[0x18 - 0xd];
    cMission*  mpMission;         // +0x18
    cImageRef  mImage;            // +0x1c
    IWindow*   mpWindow;          // +0x20
    char       pad2[0x38 - 0x24];
    cSubPanel  mSub;              // +0x38
    char       pad3[0x40 - 0x39];
    Key12*     mpTarget;          // +0x40
    char       pad4[0x50 - 0x44];
    Key12*     mpShown;           // +0x50
    char       pad5[0x88 - 0x54];
    int        mState;            // +0x88
    float      mTimer;            // +0x8c
    cAnimator* mpAnimator;        // +0x90
    float      mDuration;         // +0x94
    float      mDuration2;        // +0x98
    float      mDuration3;        // +0x9c

    void FUN_00e493c0(Key12 key);                       // 0x00e493c0
    void Update(float dt);                              // 0x00e49f80
};

// @ 0x00e49f80
void cMissionPanel::Update(float dt)
{
    AnimBuf animA, animB, animC, animD, animE;
    Key12 key;
    Quat qB, qC;
    IWindow* panelWin = 0;
    mpWindow->SetAnchor(4.0f, 10.0f);
    if (mpMission != 0) {
        panelWin = mpMission->GetPanelWindow();
        if (panelWin != 0) {
            const float* off = panelWin->GetOffset();
            mpWindow->SetAnchor(off[0], off[1]);
        }
    }
    mTimer = dt + mTimer;

    switch (mState)
    {
    case 0:
        if (panelWin) panelWin->SetFlag(1, true);
        if (mbFlag) {
            cMission* m = mpMission;
            if (m != 0) {
                mpMission = 0;
                ((IReleasable*)m)->Release();
            }
            mbFlag = 1;
        }
        if (mpTarget != mpShown) {
            if (mbFlag != 1) {
                if (mpMission->GetModel()->GetKind() == 5) break;
            }
            key = *mpTarget;
            key.b = 0x2f7d0004;
            key.c = (GetCurrentGameMode() != 0x1654c00) ? 0x02231c8b : 0xb1b0f42e;
            mImage.Set(FUN_0067dd60()->GetImage(key, 0));
            if (mImage.p != 0) mState = 1;
            else               mSub.FUN_00e49db0();
        }
        break;

    case 1:
        if (panelWin) panelWin->SetFlag(1, true);
        if (!(mImage.p->flags & 1)) break;
        if (mbFlag != 0) {
            FUN_00e493c0(*mpTarget);
            mSub.FUN_00e49db0();
            mpAnimator->RemoveAnimation(mpWindow, -1);
            qB.x = 0.0f; qB.y = 1.0f; qB.z = 0.0f; qB.w = g_15a5b54 + g_15a5b58;
            SetWindowRotation(mpWindow, &qB);
            mpWindow->SetFlag(1, true);
            mpAnimator->AddAnimation(
                SPUICreateWindowAnimationRotation(&animB, mpWindow, Vec4(0.0f, 1.0f, 0.0f, g_15a5b54),
                                                  GetElapsedSeconds(), mDuration, 2),
                mpWindow, 0);
            animB.Destroy();
            mTimer = 0.0f;
            mState = 3;
        } else {
            mpAnimator->RemoveAnimation(panelWin, -1);
            mpAnimator->AddAnimation(
                SPUICreateWindowAnimationRotation(&animA, panelWin, Vec4(0.0f, 1.0f, 0.0f, g_15a5b54),
                                                  GetElapsedSeconds(), mDuration, 1),
                panelWin, 0);
            animA.Destroy();
            mTimer = 0.0f;
            mState = 2;
        }
        break;

    case 2:
        if (panelWin) panelWin->SetFlag(1, true);
        if (mTimer > mDuration) {
            FUN_00e493c0(*mpTarget);
            mSub.FUN_00e49db0();
            mpAnimator->RemoveAnimation(mpWindow, -1);
            qC.x = 0.0f; qC.y = 1.0f; qC.z = 0.0f; qC.w = g_15a5b54 + g_15a5b58;
            SetWindowRotation(mpWindow, &qC);
            mpWindow->SetFlag(1, true);
            mpAnimator->AddAnimation(
                SPUICreateWindowAnimationRotation(&animC, mpWindow, Vec4(0.0f, 1.0f, 0.0f, g_15a5b54),
                                                  GetElapsedSeconds(), mDuration, 2),
                mpWindow, 0);
            animC.Destroy();
            mTimer = 0.0f;
            mState = 3;
        }
        break;

    case 3:
        if (panelWin) panelWin->SetFlag(1, false);
        if (mTimer > mDuration) {
            mTimer = 0.0f;
            mState = 4;
        }
        break;

    case 4:
        if (panelWin) panelWin->SetFlag(1, false);
        if (mTimer > mDuration2) {
            mpAnimator->RemoveAnimation(mpWindow, -1);
            mpAnimator->AddAnimation(
                SPUICreateWindowAnimationRotation(&animD, mpWindow, Vec4(0.0f, 1.0f, 0.0f, -g_15a5b54),
                                                  GetElapsedSeconds(), mDuration, 1),
                mpWindow, 0);
            animD.Destroy();
            mTimer = 0.0f;
            mState = 5;
        }
        break;

    case 5:
        if (panelWin) panelWin->SetFlag(1, false);
        if (mTimer > mDuration) {
            if (mbFlag == 0) {
                mpWindow->SetFlag(1, false);
                mpAnimator->RemoveAnimation(panelWin, -1);
                mpAnimator->AddAnimation(
                    SPUICreateWindowAnimationRotation(&animE, panelWin, Vec4(0.0f, 1.0f, 0.0f, -g_15a5b54),
                                                      GetElapsedSeconds(), mDuration, 2),
                    panelWin, 0);
                animE.Destroy();
                mTimer = 0.0f;
                mState = 6;
            } else {
                mState = 0;
            }
        }
        break;

    case 6:
        if (panelWin) panelWin->SetFlag(1, true);
        if (mTimer > mDuration) {
            mTimer = 0.0f;
            mState = 7;
            cModel* model = mpMission->GetModel();
            if (model->GetKind() == 4) {
                cModelPanel* panel = FUN_00e19cf0(model);
                if (panel != 0) {
                    panel->Notify();
                    if (GetCurrentGameMode() == 0x1654c01)
                        g_169e230->SetActive(0);
                }
            }
        }
        break;

    case 7:
        if (panelWin) panelWin->SetFlag(1, true);
        if (mTimer > mDuration3) {
            mTimer = 0.0f;
            mState = 0;
            mImage.Set(0);
        }
        break;
    }
    mpAnimator->Update();
}
