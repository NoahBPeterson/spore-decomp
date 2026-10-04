// Slice s0063aa90: SP::cSPPlayModeSubModeAction::HandleButton, cSPPlayModeSubModeBase/Dance/Movie helpers,
// cConnectingDialog::SetDialogText.
#include "s0063aa90.h"

struct cString {
    cString();                                                          // 0x006B5060
    void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* fallback);   // 0x006B54B0
    const wchar_t* c_str();                                             // 0x006B55C0
    ~cString();                                                         // 0x006B5240
    uint32_t pad[5];
};
class cSPUILayout {
public:
    ~cSPUILayout();                                                     // 0x00811FE0
    bool Init(const uint32_t* key, bool a, uint32_t b);                 // 0x008120D0
    IWindow* FindWindowByID(uint32_t id, bool recursive);               // 0x008105B0
    void Shutdown(bool b);                                              // 0x00811AD0
    uint32_t pad[6];
};
struct cYTMgr { void SetMode(bool a, bool b); };                        // 0x0067C420
cYTMgr* GetYTMgr();                                                     // 0x0067CAC0
struct Stopwatch {
    Stopwatch(int units, int b);                                        // 0x0093A560
    float GetElapsedTimeFloat();                                        // 0x005FF1A0
    void StartIfUnset();                                                // 0x00435480
    uint32_t mField[4];
    uint32_t pad[2];
};
void KillSetiEffects(uint32_t id, int v);                               // 0x00435ED0 (cdecl)
int GetRecorderState();                                                 // 0x00435E90
struct cAudioSys { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual int GetState(); };    // +0x20
cAudioSys* GetSystemAT();                                               // 0x00A206F0
struct cRandom { int RandomUint32Uniform(int n); };                     // 0x00A68FB0
extern cRandom sMathRandom;                                             // 0x01601760
struct cEditorFn { void FUN_00574110(uint32_t id, int a, float b, float c); void OnLayout(int a, int b);  // 0x00574110 / 0x00B267F0
    char pad[0x364]; int mAnimMgr; };
class cEditorMode2 {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual char* GetSaveInfo();   // +0x40
    void SaveModel(char* p, bool b);                                    // 0x0057F6C0
    void FUN_00574110(uint32_t id, int a, float b, float c);            // 0x00574110
    void OnLayout(int a, int b);                                        // 0x00B267F0
};
class cPlayModeUI2 { public: void SetEnabled(uint32_t id, bool b); };   // 0x00634EF0
struct cPlayModeUIOwner { char pad[0xc]; cPlayModeUI2* mpUI; };
class cSPPlayMode {
public:
    void WakeupCreature();                                              // 0x0062A760
    void FUN_00628810();                                                // 0x00628810
    void SetAllBabySitUp();                                             // 0x00629220
    char pad0[0xc]; cPlayModeUI2* mpUI;                                 // +0xc
    char pad1[0x1d - 0x10]; uint8_t mB1d, mB1e;                         // +0x1d, +0x1e
    char pad2[0x28 - 0x1f]; float mF28, mF2c, mF30;                     // +0x28..
};
class cSPPlayModeAnimation2 {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual float PlayAnimation(uint32_t creatureID, uint32_t animID, int a, int b, void* c);  // +0xc
};

class cSPPlayModeSubModeBase {
public:
    virtual void v0();
    void Init(void* params);                                            // 0x0063B270 (called out of line from other TUs; body below as InitCopy)
    void InitCopy(void* params);
    cEditorMode2* mEditorBaseMode;                                      // +0x4
    cSPPlayModeAnimation2* mAnim;                                       // +0x8
    void* mSubModeParams;                                               // +0xc
    cSPPlayMode* mPlayMode;                                             // +0x10
};

// @ 0x0063B270
void cSPPlayModeSubModeBase::InitCopy(void* params)
{
    mSubModeParams = params;
    mPlayMode = *(cSPPlayMode**)((char*)params + 0x24);
}

// ---------------------------------------------------------------------------------------------
struct PtrZ { void* p; PtrZ() : p(0) {} };
struct Vec3Z { uint32_t a, b, c; Vec3Z() : a(0), b(0), c(0) {} };
class cSPPlayModeSubModeAction : public cSPPlayModeSubModeBase {
public:
    cSPPlayModeSubModeAction();
    bool HandleButton(int id);
    void HandleExpansionAnim(uint32_t id);                              // 0x00638A00
    void CaptureGIF();                                                  // 0x00639A10

    char pad14[0x16 - 0x14];
    bool mIsPickingUp;                                                  // +0x16
    char pad17[0x38 - 0x17];
    PtrZ mCursorEffect;                                                // +0x38
    char pad3c[0x44 - 0x3c];
    PtrZ mHitEffect;                                                   // +0x44
    char pad48[0x4c - 0x48];
    uint32_t mCreatureID;                                               // +0x4c
    char pad50[0x54 - 0x50];
    Vec3Z mGrasperList;                                           // +0x54
    char pad60[0x68 - 0x60];
    uint32_t mCurrIdleAnimState;                                        // +0x68
    char pad6c[0x7c - 0x6c];
    uint8_t mMouthBidx;                                                 // +0x7c
    char pad7d[0x80 - 0x7d];
    uint32_t mSocCallEffectID;                                          // +0x80
    char pad84[0x9c - 0x84];
    uint32_t mBabyActionEventIDs[7];                                    // +0x9c
    uint32_t mBabyEmotionEventIDs[9];                                   // +0xb8
    char padDC[0xe8 - 0xdc];
    Stopwatch mFaceUserTimer;                                           // +0xe8
    char pad100[0x104 - 0x100];
    void* mField104; void* mField108; void* mField10c;                  // +0x104
};

// @ 0x0063B210
cSPPlayModeSubModeAction::cSPPlayModeSubModeAction() : mFaceUserTimer(5, 0)
{
    mField104 = 0;
    mField108 = 0;
    mField10c = 0;
}

#define KILL_SETI_REC() KillSetiEffects(0xa03e74b2, GetRecorderState())
#define KILL_SETI_AT() { cAudioSys* at = GetSystemAT(); KillSetiEffects(0xa03e74b2, at ? at->GetState() : 0); }

// @ 0x0063AA90
bool cSPPlayModeSubModeAction::HandleButton(int id)
{
    cSPPlayMode* pm = mPlayMode;
    uint8_t btn = 0xff;
    uint32_t ev = 0xffffffff;
    mIsPickingUp = false;
    bool wasSleeping = false;
    if (pm->mB1d == 3) wasSleeping = true;
    pm->WakeupCreature();
    mPlayMode->FUN_00628810();
    if (id <= 0x3fc431c) {
        if (id == 0x3fc431c) {
            mEditorBaseMode->OnLayout(3, 5);
            KILL_SETI_AT();
            ev = mBabyEmotionEventIDs[8 - 0];   // +0xd8
            btn = 0xf;
        } else if (id <= 0x3e99e98) {
            if (id == 0x3e99e98) {
                KILL_SETI_AT();
                ev = mBabyActionEventIDs[3];
                btn = 2;
                mEditorBaseMode->OnLayout(0, 2);
            } else {
                switch (id) {
                case 0x3e99d88:
                    KILL_SETI_REC();
                    ev = mBabyActionEventIDs[1]; btn = 0;
                    mEditorBaseMode->OnLayout(0, 0);
                    break;
                case 0x3e99d8c:
                    KILL_SETI_REC();
                    ev = mBabyActionEventIDs[4]; btn = 3;
                    mEditorBaseMode->OnLayout(0, 3);
                    break;
                case 0x3e99d90:
                    KILL_SETI_REC();
                    ev = mBabyActionEventIDs[6]; btn = 5;
                    mEditorBaseMode->OnLayout(0, 5);
                    break;
                case 0x3e99d94:
                    KILL_SETI_REC();
                    ev = mBabyActionEventIDs[2]; btn = 1;
                    mEditorBaseMode->OnLayout(0, 1);
                    break;
                case 0x3e99de4:
                    KILL_SETI_REC();
                    ev = mBabyActionEventIDs[5]; btn = 4;
                    mEditorBaseMode->OnLayout(0, 4);
                    break;
                }
            }
        } else {
            switch (id) {
            case 0x3fc42e4:
                mEditorBaseMode->OnLayout(3, 0);
                KILL_SETI_REC();
                ev = mBabyEmotionEventIDs[3]; btn = 10;
                break;
            case 0x3fc4300:
                mEditorBaseMode->OnLayout(3, 1);
                KILL_SETI_REC();
                ev = mBabyEmotionEventIDs[4]; btn = 0xb;
                break;
            case 0x3fc4304:
                mEditorBaseMode->OnLayout(3, 2);
                KILL_SETI_REC();
                ev = mBabyEmotionEventIDs[5]; btn = 0xc;
                break;
            case 0x3fc4310:
                mEditorBaseMode->OnLayout(3, 3);
                KILL_SETI_REC();
                ev = mBabyEmotionEventIDs[6]; btn = 0xd;
                break;
            case 0x3fc4314:
                mEditorBaseMode->OnLayout(3, 4);
                KILL_SETI_REC();
                ev = mBabyEmotionEventIDs[7]; btn = 0xe;
                break;
            }
        }
    } else if (id <= 0x4866b6d) {
        if (id >= 0x4866b68) {
            HandleExpansionAnim(id);
            return true;
        }
        if (id <= 0x48669cc) {
            if (id >= 0x48669c8) {
                HandleExpansionAnim(id);
                return true;
            }
            if (id == 0x44eec00) {
                KILL_SETI_REC();
                if (mFaceUserTimer.GetElapsedTimeFloat() > 0.0f)
                    return true;
                mFaceUserTimer.mField[0] = 0;
                mFaceUserTimer.mField[1] = 0;
                mFaceUserTimer.mField[2] = 0;
                mFaceUserTimer.mField[3] = 0;
                mFaceUserTimer.StartIfUnset();
                return true;
            }
            if (id == 0x48669a8) {
                HandleExpansionAnim(id);
                return true;
            }
        } else {
            switch (id) {
            case 0x4866a98: case 0x4866a99: case 0x4866a9a: case 0x4866a9b: case 0x4866a9c: case 0x4866a9d:
            case 0x4866b10: case 0x4866b11: case 0x4866b12: case 0x4866b13: case 0x4866b14: case 0x4866b15:
                HandleExpansionAnim(id);
                return true;
            }
        }
    } else if (id <= 0x7034070) {
        if (id == 0x7034070) {
            KILL_SETI_AT();
            ev = mBabyEmotionEventIDs[2]; btn = 0x11;
        } else if (id == 0x58b74e8) {
            mPlayMode->mpUI->SetEnabled(0x58b74e8, false);
            CaptureGIF();
        } else if (id == 0x5b02188) {
            mPlayMode->mpUI->SetEnabled(0x5b02188, false);
            char* info = mEditorBaseMode->GetSaveInfo();
            mEditorBaseMode->SaveModel(info + 0xc, true);
        }
    } else if (id == 0x7034071) {
        KILL_SETI_AT();
        ev = mBabyEmotionEventIDs[1]; btn = 0x10;
    }
    uint32_t animID;
    switch (btn) {
    case 0: animID = 0x42dd0e8; break;
    case 1: animID = 0x42dd0e2; break;
    case 2:
        if (wasSleeping) return true;
        if (mPlayMode->mB1d == 0) {
            float len = mAnim->PlayAnimation(mCreatureID, 0x4079846, 0, 1, 0);
            mPlayMode->mF28 = len * 0.5f;
            mPlayMode->mB1d = 1;
            goto sendEvent;
        }
        mAnim->PlayAnimation(mCreatureID, 0x4079859, 0, 1, 0);
        mPlayMode->mF28 = 0.0f;
        mPlayMode->mB1d = 0;
        mPlayMode->SetAllBabySitUp();
        return true;
    case 3: {
        int r = sMathRandom.RandomUint32Uniform(3);
        if (r == 0) animID = 0x4330328;
        else if (r == 1) animID = 0x42dd0ee;
        else if (r == 2) animID = 0x4373686;
        else return true;
        break;
    }
    case 4:
        if (mPlayMode->mB1e != 0) return true;
        mPlayMode->mF2c = mAnim->PlayAnimation(mCreatureID, 0x42dd0f4, 0, 1, 0);
        if (mSocCallEffectID != (uint32_t)-1) {
            mPlayMode->mF30 = 0.5f;
            mPlayMode->mB1e = 1;
        } else {
            mPlayMode->mB1e = 2;
        }
        goto sendEvent;
    case 5: animID = 0x42dd0d5; break;
    case 10: animID = 0x42dd196; break;
    case 0xb: animID = 0x42dd19c; break;
    case 0xc: animID = 0x42dd1a9; break;
    case 0xd: animID = 0x42dd1ae; break;
    case 0xe: animID = 0x42dd1b3; break;
    case 0xf: animID = 0x42dd1b8; break;
    case 0x10: animID = 0x6f8a609; break;
    case 0x11: animID = 0x6f8a61b; break;
    default:
        return true;
    }
    if (mCurrIdleAnimState != 0) mMouthBidx = 1;
    mAnim->PlayAnimation(mCreatureID, animID, 0, 1, 0);
    mAnim->PlayAnimation(mCreatureID, 0x4330667, 1, 0, 0);
    if (ev != (uint32_t)-1) {
sendEvent:
        mEditorBaseMode->FUN_00574110(ev, -1, 1.0f, 0.0f);
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// cSPPlayModeSubModeDance
class cSPPlayModeSubModeDance : public cSPPlayModeSubModeBase {
public:
    cSPPlayModeSubModeDance();
    void Init(void* params);
    bool IsDancingAnim(uint32_t animID, bool baby);
    bool HandleButton(uint32_t id);

    char pad14[0x28 - 0x14];
    uint32_t mField28;                                                  // +0x28
    uint32_t mDanceMovesGUID[6];                                        // +0x2c
    uint32_t mBabyDanceMovesGUID[6];                                    // +0x44
    uint8_t mField5c;                                                   // +0x5c (inside event array slot)
    char pad5d[3];
    uint32_t mDanceEventIDs[6];                                         // +0x60
};

// @ 0x0063B5A0
cSPPlayModeSubModeDance::cSPPlayModeSubModeDance()
{
    char* p = (char*)this;
    *(uint32_t*)(p + 0x14) = 0;
    *(uint32_t*)(p + 0x18) = 0;
    *(uint32_t*)(p + 0x1c) = 0;
    *(uint32_t*)(p + 0x20) = 0;
}

// @ 0x0063B290
void cSPPlayModeSubModeDance::Init(void* params)
{
    cSPPlayModeSubModeBase::Init(params);
    mDanceMovesGUID[0] = 0x3fbce75;
    mDanceMovesGUID[1] = 0x3fbce97;
    mDanceMovesGUID[2] = 0x3fbcea4;
    mDanceMovesGUID[3] = 0x3fbceb5;
    mDanceMovesGUID[4] = 0x4114b22;
    mDanceMovesGUID[5] = 0x4114b5e;
    mBabyDanceMovesGUID[0] = 0x44f475b;
    mBabyDanceMovesGUID[1] = 0x44f4767;
    mBabyDanceMovesGUID[2] = 0x44f476c;
    mBabyDanceMovesGUID[3] = 0x44f4771;
    mBabyDanceMovesGUID[4] = 0x44f4776;
    mBabyDanceMovesGUID[5] = 0x44f477a;
    mDanceEventIDs[0] = 0xe5025cd9;
    mDanceEventIDs[1] = 0xed65cbf6;
    mDanceEventIDs[2] = 0xe12a2ae7;
    mDanceEventIDs[3] = 0xbd989484;
    mDanceEventIDs[4] = 0x6df196fd;
    mDanceEventIDs[5] = 0x3088ceca;
    mField28 = 0;
    mAnim = *(cSPPlayModeAnimation2**)((char*)params + 0x20);
    mField5c = 0;
}

// @ 0x0063B570
bool cSPPlayModeSubModeDance::IsDancingAnim(uint32_t animID, bool baby)
{
    const uint32_t* arr;
    if (baby) arr = mBabyDanceMovesGUID;
    else arr = mDanceMovesGUID;
    uint32_t i = 0;
    do {
        if (animID == arr[i]) return true;
        i++;
    } while (i < 6);
    return false;
}

#define DANCE_CASE(ID, N) \
    case ID: KILL_SETI_AT(); guid = mDanceMovesGUID[N]; evt = mDanceEventIDs[N]; idx = N; break;

// @ 0x0063B330
bool cSPPlayModeSubModeDance::HandleButton(uint32_t id)
{
    uint32_t guid, evt;
    int idx;
    switch (id) {
    DANCE_CASE(0x3e830f4, 0)
    DANCE_CASE(0x3e830fc, 1)
    DANCE_CASE(0x3e83104, 2)
    DANCE_CASE(0x3e8313c, 3)
    DANCE_CASE(0x3e83154, 4)
    DANCE_CASE(0x3e83170, 5)
    default:
        return true;
    }
    mEditorBaseMode->OnLayout(1, idx);
    if (guid != (uint32_t)-1) {
        mPlayMode->WakeupCreature();
        mPlayMode->FUN_00628810();
        mAnim->PlayAnimation(*(uint32_t*)((char*)mEditorBaseMode + 0x364), guid, 1, 1, 0);
        if (evt != (uint32_t)-1)
            mEditorBaseMode->FUN_00574110(evt, -1, 1.0f, 0.0f);
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// cSPPlayModeUI helpers called from the movie sub-mode
class cSPPlayModeUI {
public:
    void SetUIGroupVisible(uint32_t id, bool visible);                  // 0x00635760
    void SetEnabled(uint32_t id, bool enabled);                         // 0x00634EF0
    bool SendVideoURLInfoToServer();                                    // 0x00637C90
    void FUN_00634af0();                                                // 0x00634AF0
    void FUN_00635350(bool v, int a);                                   // 0x00635350
    void FUN_00636320(bool v);                                          // 0x00636320
    void FUN_006353e0(bool v);                                          // 0x006353E0
    void FUN_00635380();                                                // 0x00635380
};
extern char g15247b0[], g15247bc[], g15247c8[], g15247d4[], g15247f8[], g1524804[], g152481c[];
void FUN_00809db0(const void* a, const void* b);                        // 0x00809DB0 (cdecl)
struct cConfigMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual int GetValue(uint32_t id); };   // +0x30
cConfigMgr* GetConfigManager();                                         // 0x0067DD30
struct cSaveArea { virtual void v0(); virtual void v1(); virtual void v2(); virtual int GetType();   // +0xc
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void* GetData(); };                                         // +0x28
cSaveArea* GetSaveArea(uint32_t id);                                    // 0x006B1F90
extern char gDefaultSaveData[];                                         // 0x013EC468
void FUN_009322b0(const void* p);                                       // 0x009322B0 (cdecl)
void FUN_00932960(const void* p);                                       // 0x00932960 (cdecl)

class cSPPlayModeSubModeMovie {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(uint32_t id);                                      // +0x2c
    bool OnKeyDown(int key, int mods);
    void FUN_0063b760();
    void SetState2();
    void SetState4();
    void SetState5();
    void SetState6();
    int GetYTPrompt();
    void CheckServer();
    void SetStateB();
    void FUN_0063b9f0(bool v);

    char pad04[0x34 - 4];
    cSPPlayModeUI* mUI;                                                 // +0x34
    char pad38[0x22c1 - 0x38];
    bool mFlag22c1;                                                     // +0x22c1
    char pad22c2[0x22e4 - 0x22c2];
    int mState;                                                         // +0x22e4
};

// @ 0x0063B730
bool cSPPlayModeSubModeMovie::OnKeyDown(int key, int mods)
{
    if (key == 0xd && mState == 3) {
        v11(0x5652348);
        return true;
    }
    return false;
}

// @ 0x0063B760
void cSPPlayModeSubModeMovie::FUN_0063b760()
{
    bool b = !mFlag22c1;
    mUI->SetUIGroupVisible(0x3f434ac, b);
    mUI->SetUIGroupVisible(0x3fc1740, !b);
    mFlag22c1 ^= 1;
}

// @ 0x0063B7B0
void cSPPlayModeSubModeMovie::SetState2()
{
    GetYTMgr()->SetMode(false, true);
    FUN_00809db0(g152481c, g15247b0);
    mState = 2;
}

// @ 0x0063B7F0
void cSPPlayModeSubModeMovie::SetState4()
{
    GetYTMgr()->SetMode(false, true);
    FUN_00809db0(0, g15247bc);
    mState = 4;
}

// @ 0x0063B820
void cSPPlayModeSubModeMovie::SetState5()
{
    GetYTMgr()->SetMode(false, true);
    FUN_00809db0(g152481c, g15247d4);
    mState = 5;
}

// @ 0x0063B860
void cSPPlayModeSubModeMovie::SetState6()
{
    GetYTMgr()->SetMode(false, true);
    FUN_00809db0(0, g15247c8);
    mState = 6;
}

// @ 0x0063B890
int cSPPlayModeSubModeMovie::GetYTPrompt()
{
    return GetConfigManager()->GetValue(0x5664a8b) == 0;
}

// @ 0x0063B8B0
void cSPPlayModeSubModeMovie::CheckServer()
{
    cString s;
    if (!mUI->SendVideoURLInfoToServer()) {
        mUI->FUN_00634af0();
        GetYTMgr()->SetMode(false, true);
        FUN_00809db0(g152481c, g15247f8);
        mState = 0xa;
    }
}

// @ 0x0063B910
void cSPPlayModeSubModeMovie::SetStateB()
{
    GetYTMgr()->SetMode(false, true);
    FUN_00809db0(g152481c, g1524804);
    mState = 0xb;
}

// @ 0x0063B950
void FUN_0063b950()
{
    const void* p = gDefaultSaveData;
    cSaveArea* a = GetSaveArea(0x11ac197);
    if (a && a->GetType() == 0x34728492)
        p = a->GetData();
    FUN_009322b0(p);
}

// @ 0x0063B9A0
void FUN_0063b9a0()
{
    const void* p = gDefaultSaveData;
    cSaveArea* a = GetSaveArea(0x11ac197);
    if (a && a->GetType() == 0x34728492)
        p = a->GetData();
    FUN_00932960(p);
}

// @ 0x0063B9F0
void cSPPlayModeSubModeMovie::FUN_0063b9f0(bool v)
{
    mUI->FUN_00635350(v, 0);
    mUI->FUN_00636320(v);
    mUI->FUN_006353e0(v);
    mUI->SetEnabled(0x3a8ede4, v);
    if (v) mUI->FUN_00635380();
}

// ---------------------------------------------------------------------------------------------
// FUN_0063b5c0: layout init of a small dialog class (layout at +0x2c)
struct cDialog2 {
    bool Init();
    char pad[0x2c];
    cSPUILayout mLayout;                                                // +0x2c
};

// @ 0x0063B5C0
bool cDialog2::Init()
{
    uint32_t key[3];
    key[0] = 0x834b03af;
    key[1] = 0x510a95b;
    key[2] = 0x40464100;
    if (mLayout.Init(key, true, 0x5b598fa)) {
        IWindow* w = mLayout.FindWindowByID(0x431e538, true);
        if (w) {
            w->AddWinProc(this);
            return true;
        }
        mLayout.Shutdown(true);
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
namespace {
struct cConnectingDialog {
    void SetDialogText(int state);
    char pad[0x2c];
    cSPUILayout mLayout;                                                // +0x2c
};
}

// @ 0x0063B640
void cConnectingDialog::SetDialogText(int state)
{
    IWindow* a = mLayout.FindWindowByID(0x5d2bdf8, true);
    a->SetFlag(1, false);
    a->SetFlag(2, false);
    IWindow* t = mLayout.FindWindowByID(0x5006000, true);
    if (t) {
        cString s;
        switch (state) {
        case 0:
            s.Load(0x7518573e, 0x56691b0, L"*Check Registration...*");
            break;
        case 1:
            s.Load(0x7518573e, 0x5496b24, L"*Log In...*");
            break;
        case 2:
            s.Load(0x7518573e, 0x55aa305, L"*Upload Video...*");
            a->SetFlag(1, true);
            a->SetFlag(2, true);
            break;
        }
        t->SetCaption(s.c_str());
    }
}
