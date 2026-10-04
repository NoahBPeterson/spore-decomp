// Slice s00637f80: SP::cSPPlayModeUI YouTube/movie-saved button layout + SP::cSPPlayModeSubModeAction (mouse/key/idle helpers).
#include "s00637f80.h"

// ---------------------------------------------------------------------------------------------
// cString (SP::cString) and a minimal wide string with the EASTL layout used by the original
struct cString {
    cString();                                                          // 0x006B5060
    void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* fallback);   // 0x006B54B0
    const wchar_t* c_str();                                             // 0x006B55C0
    ~cString();                                                         // 0x006B5240
    uint32_t pad[5];
};
void WString_Assign(void* s, const wchar_t* b, const wchar_t* e);       // 0x00423650 (thiscall, s in ecx)
struct WStr {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;
    void assign(const wchar_t* b, const wchar_t* e);                    // 0x00423650
    void RangeInitialize(const wchar_t* s);                             // 0x00579A90
    int find(const WStr& needle, int pos);                              // 0x00608340
    void erase(int pos, int n);                                         // 0x004228E0
    int size() const { return (int)(mpEnd - mpBegin); }
};
void EASTL_deallocate(void* p);                                         // 0x00F47380
namespace SPUIHelpers {
void AutoSizeWindowForText(IWindow* w, bool a, bool b);                 // 0x00806E40
void BeginModal(IWindow* w, int a, int b);                              // 0x008099A0
}

struct Rect4 { float l, t, r, b; };

struct cPaletteStub { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void SetEnabled(int a); };
namespace SP {
class cSPEditorUI { public: IWindow* FindWindowByID(uint32_t id); };    // 0x005DC310
class cAppModeEditorBase {
public:
    char pad0[0x78]; cSPEditorUI* mpEditorUI;                           // +0x78
    char pad1[0x358 - 0x7c]; cPaletteStub* mpPaletteData;                    // +0x358
};
class cSPPlayMode;
}
struct cYTMgr { void SetMode(bool a, bool b); };                        // 0x0067C420
cYTMgr* GetYTMgr();                                                     // 0x0067CAC0
struct IWinMgrLike { virtual void v0(); virtual void* GetCurrent(); };
IWinMgrLike* GetWindowManager();                                        // 0x0067CAA0
struct cWinOwnerSub { void Func(bool b); };                             // 0x00802A30
struct cWinOwnerBase0 { virtual void f0(); };
struct cWinOwnerBase1 { virtual void f1(); };
struct cWinOwner : cWinOwnerBase0, cWinOwnerBase1 {
    char pad[0x2d8 - 8]; cWinOwnerSub* mpSub;                           // +0x2d8
};
struct Rect4Union { float v[4]; void FUN_00634b60(const float* a, const float* b); };    // 0x00634B60 (thiscall on out)

namespace SP {
class cSPPlayModeUI {
public:
    IWindow* FindPlayModeUIWindow(uint32_t id);                         // 0x00634DC0
    void LayoutYouTubeUploadButton();                                   // 0x00637F80
    void ShowMovieSavedDialogCustom();                                  // 0x00638430
    char pad0[0xc]; cAppModeEditorBase* mApp;                           // +0xc
    char pad1[0x64 - 0x10]; IWindow* mpDialog;                          // +0x64
};
}
using namespace SP;

// @ 0x00637F80
void cSPPlayModeUI::LayoutYouTubeUploadButton()
{
    cString title;
    title.Load(0x7518573e, 0x5e501eb, L"YouTube Upload (PLACEHOLDER)");
    WStr text = {0, 0, 0};
    bool iconFirst = true;
    const wchar_t* t = title.c_str();
    const wchar_t* te = t;
    while (*te) te++;
    text.assign(t, t + (te - t));
    IWindow* wa = mApp->mpEditorUI->FindWindowByID(0x5e51108);
    IWindow* wb = mApp->mpEditorUI->FindWindowByID(0x5daa660);
    WStr marker = {0, 0, 0};
    marker.RangeInitialize(L"<youtubeicon>");
    WStr before = {0, 0, 0};
    WStr after = {0, 0, 0};
    int pos = text.find(marker, 0);
    if (pos != -1) {
        before.assign(text.mpBegin, text.mpEnd);
        text.erase(pos, before.size());
        after.assign(before.mpBegin, before.mpEnd);
        // text now holds the part before the marker, 'before' the full string
        before.erase(0, pos + marker.size());
        if (((text.mpEnd - text.mpBegin) & ~1) == 0) {
            after.assign(before.mpBegin, before.mpEnd);
        } else {
            after.assign(text.mpBegin, text.mpEnd);
            iconFirst = false;
        }
    }
    if (wb) {
        wb->SetCaption(after.mpBegin);
        SPUIHelpers::AutoSizeWindowForText(wb, false, false);
    }
    float* ra = wa->GetRealArea();
    float baseX = ra[0];
    IWindow* spanWin;
    if (!iconFirst) {
        Rect4 aR = {ra[0], ra[1], ra[2], ra[3]};
        float* rb = wb->GetRealArea();
        Rect4 bR = {rb[0], rb[1], rb[2], rb[3]};
        Rect4 nb = {aR.l, bR.t, (bR.r - bR.l) + aR.l, (bR.b - bR.t) + bR.t};
        wb->SetLayoutArea(&nb.l);
        float right = wb->GetRealArea()[2] + 3.0f;
        Rect4 na = {right, aR.t, (aR.r - aR.l) + right, (aR.b - aR.t) + aR.t};
        wa->SetLayoutArea(&na.l);
        baseX = wb->GetRealArea()[0];
        spanWin = wa;
    } else {
        spanWin = wb;
    }
    float spanRight = spanWin->GetRealArea()[2];
    IWindow* container = mApp->mpEditorUI->FindWindowByID(0x5b5ef50);
    float* rc = container->GetRealArea();
    float shift = (spanRight + baseX) * 0.5f - (rc[2] - rc[0]) * 0.5f;
    float* r1 = wa->GetRealArea();
    Rect4 ra2 = {r1[0], r1[1], r1[2], r1[3]};
    float* r2 = wb->GetRealArea();
    Rect4 rb2 = {r2[0], r2[1], r2[2], r2[3]};
    Rect4 sa = {ra2.l - shift, ra2.t, (ra2.r - ra2.l) + (ra2.l - shift), (ra2.b - ra2.t) + ra2.t};
    wa->SetLayoutArea(&sa.l);
    Rect4 sb = {rb2.l - shift, rb2.t, (rb2.r - rb2.l) + (rb2.l - shift), (rb2.b - rb2.t) + rb2.t};
    wb->SetLayoutArea(&sb.l);
    if (((text.mpCapacity - text.mpBegin) & ~1) > 2 && text.mpBegin) EASTL_deallocate(text.mpBegin);
    (void)marker; (void)before;
}

// @ 0x00638430
void cSPPlayModeUI::ShowMovieSavedDialogCustom()
{
    mApp->mpPaletteData->SetEnabled(0);   // vcall +0x1c
    IWindow* w = mApp->mpEditorUI->FindWindowByID(0x5a73030);
    if (w) { w->GetFlags(); w->SetFlag(2, false); }
    GetYTMgr()->SetMode(false, true);
    cString str;
    str.Load(0x7518573e, 0x54c1e63, L"*Movie Saved*");
    IWindow* c = FindPlayModeUIWindow(0x5b5f5c8);
    c->SetCaption(str.c_str());
    str.Load(0x7518573e, 0x5b5fd1e, L"*Upload to YouTube*");
    c = FindPlayModeUIWindow(0x5b5f608);
    c->SetCaption(str.c_str());
    w = FindPlayModeUIWindow(0x5b5ef50);
    if (w) w->SetFlag(1, true);
    w = FindPlayModeUIWindow(0x5b60540);
    if (w) w->SetFlag(1, true);
    float extra = 0.0f;
    IWindow* w1 = FindPlayModeUIWindow(0x5b5ef51);
    if (w1) {
        SPUIHelpers::AutoSizeWindowForText(w1, true, false);
        IWindow* w2 = FindPlayModeUIWindow(0x5b5ef52);
        if (w2) {
            SPUIHelpers::AutoSizeWindowForText(w2, false, false);
            float* r2 = w2->GetRealArea();
            float width2 = r2[2] - r2[0];
            float* r1 = w1->GetRealArea();
            float newX = r1[0] - width2;
            w2->SetLayoutLocation(newX, r2[1]);
            IWindow* w3 = FindPlayModeUIWindow(0x5b5ef53);
            if (w3) {
                SPUIHelpers::AutoSizeWindowForText(w3, false, false);
                Rect4Union u;
                u.FUN_00634b60(w2->GetRealArea(), w3->GetRealArea());
                extra = u.v[0] - width2;   // approximate (see partial.txt)
            }
        }
    }
    LayoutYouTubeUploadButton();
    IWindow* panel = FindPlayModeUIWindow(0x5b5ef50);
    if (panel && extra > 0.0f) {
        float* r = panel->GetRealArea();
        panel->SetLayoutSize((r[2] - r[0]) + extra, r[3] - r[1]);
    }
    if (!mpDialog) {
        IWindow* d = FindPlayModeUIWindow(0x5b5ef50);
        IWindow* old = mpDialog;
        if (d != old) {
            if (d) d->AddRef();
            mpDialog = d;
            if (old) old->Release();
        }
        mpDialog->GetParent()->RemoveWindow(mpDialog);
    }
    SPUIHelpers::BeginModal(mpDialog, 0, 0);
    void* m = GetWindowManager()->GetCurrent();
    cWinOwner* o = m ? (cWinOwner*)((char*)m - 4) : 0;
    o->mpSub->Func(false);
}

// ---------------------------------------------------------------------------------------------
// cSPPlayModeSubModeAction (retail layout; PDB offsets differ past +0xd8)
namespace SP {
class cSPPlayMode {
public:
    void SetBabySpawned(int idx, bool spawned);                         // 0x00629380
    char pad0[0x1c];
    bool mSleepB1c, mSleepB1d, mSleepB1e, mSleepB1f, mSleepB20;         // +0x1c..+0x20
    char pad1[0x3c - 0x21];
    float mMomCrouchChangeTime;                                         // +0x3c
    float mBabyCelebratingChangeTime[3];                                // +0x40
    char pad2[0x51 - 0x4c];
    bool mBabyPhotoMode;                                                // +0x51
};
}
struct cEditorBaseStub { char pad[0x84]; void* mpModelWorld; };
struct cAnimInfoStub { char pad[8]; uint32_t mCurrAnimID; };

class cVisualEffect {
public:
    virtual int AddRef(); virtual int Release(); virtual void v2();
    virtual void Stop(int a);                                           // +0xc
};
class cSPPlayModeAnimation {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual float PlayAnimation(uint32_t creatureID, uint32_t animID, int a, int b, void* c);  // +0xc
    bool GetExpansionAnimInfo(uint32_t id, int* animID, int* a, float* b, float* c);    // 0x0062E4F0
    char pad[4]; uint32_t mCurrAnimID;
};
struct cCreatureStructure {
    char pad[0x48]; float f48; char pad2[4]; float f50;
    void FUN_0059b2f0(float v, int b);                                  // 0x0059B2F0
};
class cSPEditorAnimatedCreatureManager {
public:
    cCreatureStructure* GetCreatureStructure(uint32_t id);              // 0x0059CAC0
    void SetCreatureSpeeds(uint32_t id, float a, float b);              // 0x0059D0B0
    void SetCreatureIsTurning(uint32_t id, bool turning);               // 0x0059D010
};
struct cAnimatingCreatureSub { void FUN_00a006f0(int v); };             // 0x00A006F0
class cAnimatingCreature {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void GetAnimInfo(int* out, int a, int b, int c);            // +0x58
    char pad[0x154 - 4]; int mState;                   // +0x154
    char pad2[0x184 - 0x158]; cAnimatingCreatureSub* mpSub;             // +0x184
    void FUN_00a04ad0(uint32_t state);                                  // 0x00A04AD0
};
struct cIdleObj { char pad[0x8c]; cVisualEffect* mpEffect; };
struct cIdleObjMgr { cIdleObj* FUN_009cab60(uint32_t id); void FUN_009cb460(cIdleObj* o); };  // 0x009CAB60 / 0x009CB460
struct cEffectsMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual int GetEffectsWorldHandle();             // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void RemoveEffect(uint32_t id);                             // +0x50
};
cEffectsMgr* GetEffectsManager();                                       // 0x0067DDD0
struct cWorldObj { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void SetEffectsHandle(int h); };         // +0x1c
struct cStopObj {
    virtual int AddRef(); virtual int Release(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void Flush();                           // +0x7c
};
struct cPlayModeFlagStub { void FUN_0062ab80(); };                      // 0x0062AB80
struct AssetBrowserStub { char pad[0x1c]; bool mFlag1c; };
AssetBrowserStub* GetAssetBrowser();                                    // 0x00401030
float FUN_0069b840(float a, float b, float c);                          // 0x0069B840
struct cEditorStub2 { void FUN_00574110(uint32_t id, int a, float b, float c); };                         // 0x00574110
struct cAnimCreatureHelper { bool FUN_00a02b20(int a); };               // 0x00A02B20
bool FUN_0062ab80helper();

extern float gDefaultSpeedB;                                            // 0x015F81B4

namespace SP {
class cSPPlayModeSubModeAction {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    bool OnMouseUp(int btn, float x, float y, int flags);
    bool OnMouseMove(float x, float y, int flags);
    void UpdateBabyCelebrationTimes(uint32_t dtMs);
    bool ReachedMomTargetAngle(uint32_t dtMs);
    bool IsLookAroundIdle(uint32_t animID);
    void SetWalkAnimation(cAnimatingCreature* creature, uint32_t id);
    bool AnyKeyDown();
    void HandleExpansionAnim(uint32_t id);
    void Shutdown();
    bool OnMouseDown(int btn, float x, float y, int flags);
    bool OnKeyUp(uint32_t key, uint32_t mods);
    bool IsIdle();

    cEditorBaseStub* mEditorBaseMode;                                   // +0x4
    cSPPlayModeAnimation* mAnim;                                        // +0x8
    void* mSubModeParams;                                               // +0xc
    cSPPlayMode* mPlayMode;                                             // +0x10
    bool mIsMouseDown, mIsFirstClick, mIsPickingUp, mIsGoingToPickUp;   // +0x14
    bool mIsThrowing, mHoopsModeOn, mIsWalking, mHoopsMode_state;       // +0x18
    char pad1c[0x30 - 0x1c];
    float mX, mY;                                                       // +0x30
    cVisualEffect* mCursorEffect;                                       // +0x38
    float mClickTime;                                                   // +0x3c
    char pad40[0x48 - 0x40];
    cSPEditorAnimatedCreatureManager* mAnimCreatureMgr;                 // +0x48
    uint32_t mCreatureID;                                               // +0x4c
    cAnimatingCreature* mAnimCreature;                                  // +0x50
    char pad54[0x68 - 0x54];
    uint32_t mCurrIdleAnimState;                                        // +0x68
    char pad6c[0x7c - 0x6c];
    uint8_t mMouthBidx;                                                 // +0x7c
    char pad7d[0x84 - 0x7d];
    uint32_t mLastLookAroundIdleID;                                     // +0x84
    char pad88[0xdc - 0x88];
    bool mKeyInputButtonState[6];                                       // +0xdc
    char pade2[0x104 - 0xe2];
    cWorldObj* mpField104;                                                   // +0x104
    void* mpField108;                                                   // +0x108
    cStopObj* mpField10c;                                                   // +0x10c
};
}

// @ 0x00638750
bool cSPPlayModeSubModeAction::OnMouseUp(int btn, float x, float y, int flags)
{
    if (btn == 1000) {
        mIsMouseDown = false;
        mIsFirstClick = false;
    }
    return false;
}

// @ 0x00638770
bool cSPPlayModeSubModeAction::OnMouseMove(float x, float y, int flags)
{
    mX = x;
    mY = y;
    return false;
}

// @ 0x00638790
void cSPPlayModeSubModeAction::UpdateBabyCelebrationTimes(uint32_t dtMs)
{
    cSPPlayMode* pm = mPlayMode;
    int i = 0;
    uint32_t off = 0x40;
    do {
        if (*(float*)((char*)pm + off) > 0.0f) {
            float* p = (float*)((char*)mPlayMode + off);
            *p -= (float)dtMs * 0.001f;
            if (*p <= 0.0f) {
                pm->SetBabySpawned(i, false);
                pm = mPlayMode;
                *(float*)((char*)pm + off) = 0.0f;
            }
        }
        off += 4;
        i++;
    } while (off < 0x4c);
}

// @ 0x00638810
bool cSPPlayModeSubModeAction::ReachedMomTargetAngle(uint32_t dtMs)
{
    cCreatureStructure* cs = mAnimCreatureMgr->GetCreatureStructure(mCreatureID);
    float a = cs->f48;
    float b = cs->f50;
    float f = FUN_0069b840(a, mPlayMode->mMomCrouchChangeTime, b * ((float)dtMs * 0.001f));
    cs->FUN_0059b2f0(f, 1);
    if (f == mPlayMode->mMomCrouchChangeTime) return true;
    return false;
}

// @ 0x00638890
bool cSPPlayModeSubModeAction::IsLookAroundIdle(uint32_t animID)
{
    if (animID == 0x4112345) return true;
    if (animID == 0x44d7f20) return true;
    if (animID == 0x411238e) return true;
    if (animID == 0x41123a5) return true;
    if (animID == 0x407986c) return true;
    if (animID == 0x4079862) return true;
    if (animID == 0x4079874) return true;
    if (animID == 0x4079879) return true;
    if (animID == 0x4330317) return true;
    return false;
}

// @ 0x006388E0
void cSPPlayModeSubModeAction::SetWalkAnimation(cAnimatingCreature* creature, uint32_t id)
{
    int curAnim;
    creature->GetAnimInfo(&curAnim, 0, 0, 0);
    if (curAnim == 0x4079859)
        mAnim->PlayAnimation(id, 0x452b634, 0, 0, 0);
    else
        mAnim->PlayAnimation(id, 0x452b634, 0, 1, 0);
    creature->mState = 2;
    int tmp = 0;
    mAnim->PlayAnimation(id, 0x452b64a, 1, 0, &tmp);
    if (creature->mpSub) creature->mpSub->FUN_00a006f0(tmp);
    creature->FUN_00a04ad0(mCurrIdleAnimState);
    uint32_t idleAnim = 0x4485a08;
    if (!(mCurrIdleAnimState - 2)) idleAnim = 0x4485a0f;
    mAnim->PlayAnimation(id, idleAnim, 1, 2, 0);
}

// @ 0x006389B0
bool cSPPlayModeSubModeAction::AnyKeyDown()
{
    bool r = false;
    if (mKeyInputButtonState[0]) r = true;
    if (mKeyInputButtonState[1]) r = true;
    if (mKeyInputButtonState[2]) r = true;
    if (mKeyInputButtonState[3]) r = true;
    if (mKeyInputButtonState[4]) r = true;
    if (mKeyInputButtonState[5]) r = true;
    return r;
}

// @ 0x00638A00
void cSPPlayModeSubModeAction::HandleExpansionAnim(uint32_t id)
{
    int animID = 0;
    int a = 0;
    float b = 1.0f, c = 0.0f;
    if (mAnim->GetExpansionAnimInfo(id, &animID, &a, &b, &c) && animID != -1) {
        if (mCurrIdleAnimState != 0) mMouthBidx = 1;
        mAnim->PlayAnimation(mCreatureID, animID, 0, 1, 0);
        mAnim->PlayAnimation(mCreatureID, 0x4330667, 1, 0, 0);
        ((cEditorStub2*)mEditorBaseMode)->FUN_00574110(0x4878ee8, a, b, c);
    }
}

// @ 0x00638AD0
void cSPPlayModeSubModeAction::Shutdown()
{
    if (mLastLookAroundIdleID != (uint32_t)-1) {
        cIdleObjMgr* m = *(cIdleObjMgr**)((char*)mAnimCreature + 0x17c);
        cIdleObj* o = m->FUN_009cab60(mLastLookAroundIdleID);
        if (o) {
            cVisualEffect* e = o->mpEffect;
            if (e) e->Stop(1);
            m = *(cIdleObjMgr**)((char*)mAnimCreature + 0x17c);
            m->FUN_009cb460(o);
        }
        mLastLookAroundIdleID = (uint32_t)-1;
    }
    ((cPlayModeFlagStub*)mPlayMode)->FUN_0062ab80();
    *((uint8_t*)mPlayMode + 0x4c) = 0;
    mpField104->SetEffectsHandle(GetEffectsManager()->GetEffectsWorldHandle());
    mpField10c->Flush();
    cStopObj* p = mpField10c;
    if (p) {
        mpField10c = 0;
        p->Release();
    }
    GetEffectsManager()->RemoveEffect(0x61c8236);
    mpField104 = 0;
    mpField108 = 0;
}

// @ 0x00638BA0
bool cSPPlayModeSubModeAction::OnMouseDown(int btn, float x, float y, int flags)
{
    if (btn == 1000) {
        void* world = mEditorBaseMode->mpModelWorld;
        if (mClickTime > 0.0f && 400.0f > mClickTime) {
            if (world && mAnimCreatureMgr) {
                mAnimCreatureMgr->SetCreatureSpeeds(mCreatureID, 4.0f, gDefaultSpeedB);
                mCurrIdleAnimState = 2;
            }
        } else {
            mClickTime = 0.0f;
            if (world && mAnimCreatureMgr) {
                mAnimCreatureMgr->SetCreatureSpeeds(mCreatureID, 2.5f, gDefaultSpeedB);
                mCurrIdleAnimState = 1;
            }
        }
        mX = x;
        mY = y;
        if (!mIsMouseDown) mIsFirstClick = true;
        mIsMouseDown = true;
    }
    if (mCursorEffect) {
        mCursorEffect->Stop(0);
        cVisualEffect* e = mCursorEffect;
        if (e) {
            mCursorEffect = 0;
            e->Release();
        }
    }
    return false;
}

// @ 0x00638C90
bool cSPPlayModeSubModeAction::OnKeyUp(uint32_t key, uint32_t mods)
{
    if (!GetAssetBrowser()->mFlag1c) {
        switch (key) {
        case 0x26: case 0x57: case 0x68:
            mKeyInputButtonState[0] = false;
            return false;
        case 0x28: case 0x53: case 0x62:
            mKeyInputButtonState[2] = false;
            mMouthBidx = 1;
            return false;
        case 0x51: case 0x67:
            mKeyInputButtonState[4] = false;
            return false;
        case 0x45: case 0x69:
            mKeyInputButtonState[5] = false;
            return false;
        case 0x25: case 0x41: case 100:
            mKeyInputButtonState[1] = false;
            mAnimCreatureMgr->SetCreatureIsTurning(mCreatureID, false);
            return false;
        case 0x27: case 0x44: case 0x66:
            mKeyInputButtonState[3] = false;
            mAnimCreatureMgr->SetCreatureIsTurning(mCreatureID, false);
            break;
        }
    }
    return false;
}

// @ 0x00638D90
bool cSPPlayModeSubModeAction::IsIdle()
{
    cSPPlayMode* p = mPlayMode;
    if (p->mSleepB1c) return false;
    if (p->mSleepB1e) return false;
    if (p->mSleepB1d) return false;
    if (p->mSleepB1f) return false;
    if (p->mSleepB20) return false;
    if (p->mBabyPhotoMode) return false;
    if (mIsMouseDown) return false;
    if (mIsPickingUp) return false;
    if (mIsGoingToPickUp) return false;
    if (mIsThrowing) return false;
    if (mIsWalking) return false;
    if (AnyKeyDown()) return false;
    if (((cAnimCreatureHelper*)mAnimCreature)->FUN_00a02b20(0) || IsLookAroundIdle(mAnim->mCurrAnimID)) return true;
    return false;
}

// @ 0x00638E10
struct Vec3f {
    float x, y, z;
    Vec3f() {}
    Vec3f(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3f operator*(float s) const { return Vec3f(x * s, y * s, z * s); }
    Vec3f operator+(const Vec3f& o) const { return Vec3f(x + o.x, y + o.y, z + o.z); }
};
bool RayPlaneIntersectZ(const Vec3f* origin, const Vec3f* dir, Vec3f* out, float planeZ)
{
    if (dir->z == 0.0f) return false;
    float t = -((origin->z - planeZ) / dir->z);
    Vec3f r = *origin + *dir * t;
    out->x = r.x; out->y = r.y; out->z = r.z;
    return true;
}
