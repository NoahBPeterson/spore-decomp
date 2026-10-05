// slice s00639bd0: cSPPlayModeSubModeAction key handling.
#include "../s00636320/s00636320.h"

struct cAssetBrowser { char pad[0x1c]; bool mActive; };        // +0x1C
cAssetBrowser* GetAssetBrowser();                              // 0x00401030

struct IWindowManager {
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03(); virtual void w04();
    virtual void w05(); virtual void w06(); virtual void w07(); virtual void w08(); virtual void w09();
    virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14();
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24();
    virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29();
    virtual void w30(); virtual void w31(); virtual void w32();
    virtual int  v33();                                        // +0x84
};
IWindowManager* GetWindowManager();                            // 0x0067CAA0

struct IAnimCreature {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual float SetAnim(uint32_t id, uint32_t anim, int a, int b, int c);   // +0x0C
};
struct cCreatureAnimMgr {
    bool IsAnimationPlaying(uint32_t creatureID, uint32_t animID);   // 0x0059CC40
};
struct cSPPlayMode {
    char pad[0x40];
    void WakeupCreature();                                     // 0x0062A760
};
struct cEditorBase {
    uint32_t EmitEmotion(uint32_t event, int a, float b, float c);   // 0x00574110
};

struct cSPPlayModeSubModeAction {
    char pad04[0x4];
    cEditorBase*   mEditorBase;        // +0x04
    IAnimCreature* mAnim;              // +0x08
    char pad0c[0x4];
    cSPPlayMode*   mPlayMode;          // +0x10
    char pad14[0x48 - 0x14];
    cCreatureAnimMgr* mAnimCreatureMgr; // +0x48
    uint32_t mCreatureID;              // +0x4C
    char pad50[0x68 - 0x50];
    int  mCurrIdleAnimState;           // +0x68
    char pad6c[0x7c - 0x6c];
    bool mMouthBidx;                   // +0x7C
    char pad7d[0xb8 - 0x7d];
    uint32_t mBabyEmotionEventIDS[1];  // +0xB8

    void Init();
    bool OnKeyDown(int keyCode, int arg2);
    void Update();
    void MarkKeyInputKeyDown(int idx);   // 0x006398F0
    void CaptureGIF();                   // 0x00639A10
};

// @ 0x00639EC0
bool cSPPlayModeSubModeAction::OnKeyDown(int keyCode, int arg2)
{
    if (GetAssetBrowser()->mActive)
        return false;
    if (GetWindowManager()->v33())
        return false;

    switch (keyCode) {
    case ' ':
        if (mAnimCreatureMgr && mAnimCreatureMgr->IsAnimationPlaying(mCreatureID, 0x44859f9))
            break;
        mPlayMode->WakeupCreature();
        if (mCurrIdleAnimState != 0)
            mMouthBidx = true;
        mAnim->SetAnim(mCreatureID, 0x44859f9, 0, 1, 0);
        mAnim->SetAnim(mCreatureID, 0x4330667, 1, 0, 0);
        mEditorBase->EmitEmotion(mBabyEmotionEventIDS[0], -1, 1.0f, 0.0f);
        return false;

    case '&': case 'W': case 'h':
        if (arg2 == 0) { MarkKeyInputKeyDown(0); return false; }
        break;
    case '(': case 'S': case 'b':
        if (arg2 == 0) { MarkKeyInputKeyDown(2); return false; }
        break;
    case 'Q': case 'g':
        if (arg2 == 0) { MarkKeyInputKeyDown(4); return false; }
        break;
    case 'E': case 'i':
        if (arg2 == 0) { MarkKeyInputKeyDown(5); return false; }
        break;
    case '%': case 'A': case 'd':
        if (arg2 == 0) { MarkKeyInputKeyDown(1); return false; }
        break;
    case '\'': case 'D': case 'f':
        if (arg2 == 0) { MarkKeyInputKeyDown(3); return false; }
        break;
    case 'J':
        if (arg2 == 6)
            CaptureGIF();
        break;
    }
    return false;
}

// @ 0x00639BD0  PARTIAL
void cSPPlayModeSubModeAction::Init() {}
// @ 0x0063A0A0  PARTIAL
void cSPPlayModeSubModeAction::Update() {}
// MarkKeyInputKeyDown (0x006398F0) and CaptureGIF (0x00639A10) are called
// out-of-line by the original; leave them undefined here for byte codegen.
