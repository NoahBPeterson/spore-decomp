// slice s006404f0: cSPPlayModeSubModePhoto helpers + small content-validation wrappers.
#include "../s00636320/s00636320.h"

int FUN_00552300(void* p);   // 0x00552300

struct cVBase {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
    virtual uint32_t GetType();               // +0x24 (index 9)
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35();
    virtual bool v36(uint32_t* out);          // +0x90 (index 36)
    virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(uint32_t a, int b);      // +0xA0 (index 40)
    virtual void v41(uint32_t a);             // +0xA4 (index 41)
    virtual void v42();                       // +0xA8 (index 42)
    virtual void v43(uint32_t a);             // +0xAC (index 43)
};

struct cXX : cVBase {
    uint32_t f4;   // +0x04
    uint32_t f8;   // +0x08
    uint32_t fc;   // +0x0C
    char pad10[0x26 - 0x10];
    uint8_t f26;   // +0x26

    void FUN_006412a0();
    void FUN_006412c0(uint32_t* src);
    void FUN_00641340(uint32_t a);
    void FUN_00641360(uint32_t a);
    void FUN_00641380(uint32_t* src, uint32_t a);
    void FUN_006413d0();
    char FUN_00641410();
    char FUN_00641470();
    char FUN_00641490();
    void FUN_00640ee0();
    void FUN_00640fa0();
    void FUN_006411b0();
};

// @ 0x006412C0
void cXX::FUN_006412c0(uint32_t* src)
{
    if (src[3] != 0) {
        f8 = ((uint32_t*)((uint32_t*)src[3])[3])[1];
        f4 = ((uint32_t*)((uint32_t*)src[3])[3])[2];
        fc = ((uint32_t*)((uint32_t*)src[3])[3])[3];
    } else {
        f4 = src[0];
        f8 = src[1];
        fc = src[2];
    }
}

// @ 0x00641340
void cXX::FUN_00641340(uint32_t a) { v40(a, 0); }

// @ 0x00641360
void cXX::FUN_00641360(uint32_t a) { v40(a, 1); }

// @ 0x00641380
void cXX::FUN_00641380(uint32_t* src, uint32_t a)
{
    f4 = src[0];
    f8 = src[1];
    fc = src[2];
    v41(a);
    v42();
    v43(a);
}

// @ 0x006413D0
void cXX::FUN_006413d0()
{
    v41(0);
    v42();
    v43(0);
}

// @ 0x00641410
char cXX::FUN_00641410()
{
    if (GetType() == 0xbcd73e89 || GetType() == 0xb8669ec9 ||
        GetType() == 0x37148141 || GetType() == 0x04f684a4)
        return 0;
    return f26;
}

// @ 0x00641470
char cXX::FUN_00641470()
{
    return FUN_00552300((char*)this + 4) != 0;
}

// @ 0x00641490
char cXX::FUN_00641490()
{
    if (FUN_00552300((char*)this + 4) == 2) {
        uint32_t local[2];
        if (v36(local) && (local[1] & local[0]) != 0xffffffff)
            return 1;
    }
    return 0;
}

// @ 0x006412A0  PARTIAL
void cXX::FUN_006412a0() {}
// @ 0x00640EE0  PARTIAL
void cXX::FUN_00640ee0() {}
// @ 0x00640FA0  PARTIAL
void cXX::FUN_00640fa0() {}
// @ 0x006411B0  PARTIAL
void cXX::FUN_006411b0() {}

// ============================================================================
// @ 0x006404F0  SP::cSPPlayModeSubModePhoto::HandleButton
// ============================================================================
namespace SP {

class cString {
public:
    cString();     // 0x006B5060
    ~cString();    // 0x006B5240
    uint32_t mData[5];
};

struct cSPPlayMode {
    void WakeupCreature();      // 0x0062A760
    void FUN_00628810();        // 0x00628810
};

struct cSPPlayModeAnimation {
    virtual void a0(); virtual void a1(); virtual void a2();
    virtual float PlayPose(void* shadowViewer, uint32_t animID, int a, int b, int c);   // +0x0C
};

struct cAppModeEditorBasePhoto {
    char pad0[0x364];
    void* mShadowViewer;                                        // +0x364
    void FUN_00b267f0(int a, int pose);                         // 0x00B267F0
    void FUN_00574110(uint32_t id, int a, float b, float c);    // 0x00574110
};

struct cSPPlayModeUIPhoto {
    char pad0[0x44];
    bool mbLayoutInit;                                  // +0x44
    void SetHighlight(uint32_t id, bool on);            // 0x00634E90
    void FUN_00635350(int a, int b);                    // 0x00635350
    void SetSendEmailDialogVisibility(bool on);         // 0x00635400
    void SetEnableNewCreatureButton(bool on);           // 0x00635580
    void SetEnableTakePictureButton(bool on);           // 0x00635600
    void SetEnableRecordMovieButton(bool on);           // 0x00635680
};

struct cSPPlayModePhotoBrowser {
    void EnterMoveMode();               // 0x0062FDA0
    void EnterDeleteMode();             // 0x0062FE40
    void FUN_0062ff80(int mode);        // 0x0062FF80
    void SelectAll(bool on);            // 0x00630090
    void ExitDeleteMode();              // 0x006301A0
    void ExitMoveMode();                // 0x00630280
    void DeleteSelected();              // 0x00632660
    void MoveSelected();                // 0x006326F0
    bool FUN_00632e40();                // 0x00632E40
    bool FUN_00633430();                // 0x00633430
    void ClearPhotoList();              // 0x00634030
    void SendPhoto(int index);          // 0x00634380
    void NextPage();                    // 0x006343F0
    void PrevPage();                    // 0x00634490
    void FUN_00634520();                // 0x00634520
    void FUN_00634570();                // 0x00634570
    int  FUN_006c0200();                // 0x006C0200
    uint32_t FUN_00cee370();            // 0x00CEE370
};

namespace Pollen {
struct cAuthManager {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03(); virtual void m04();
    virtual void m05(); virtual void m06(); virtual void m07(); virtual void m08();
    virtual bool IsRegistrationNeeded();    // +0x24
    virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual void m14();
    virtual void m15(); virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21();
    virtual bool IsLoggedIn();              // +0x58
};
cAuthManager* AuthManager();                // 0x00607A60
}

struct IMessageServer {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void PostMSG(uint32_t id, int a, int b);    // +0x14
};
IMessageServer* MessageServer();                        // 0x0067DCC0

struct cSPPlayModeSubModeBase {
    virtual void b00();
    cAppModeEditorBasePhoto* mEditorBaseMode;   // +0x04
    cSPPlayModeAnimation* mAnim;                // +0x08
    void* mSubModeParams;                       // +0x0C
    cSPPlayMode* mPlayMode;                     // +0x10
};

struct IHandlerPhoto { virtual bool HandleMessage(uint32_t id, void* msg); };

class cSPPlayModeSubModePhoto : public cSPPlayModeSubModeBase, public IHandlerPhoto {
public:
    uint32_t mPoseAnimIDs[6];                   // +0x18
    uint32_t mCurrPoseNum;                      // +0x30
    uint32_t mBabyEventIDs[6];                  // +0x34
    cSPPlayModeUIPhoto* mUI;                    // +0x4C
    cSPPlayModePhotoBrowser mPhotoBrowser;      // +0x50
    char padBrowser[0xF30 - 0x51];
    bool mbF30;                                 // +0xF30
    char padF31[0xF98 - 0xF31];
    int mDialogInProgress;                      // +0xF98

    bool HandleButton(int id);
    bool FUN_0063ed00();                        // 0x0063ED00
    bool FUN_0063ed50();                        // 0x0063ED50
    void CloseSendPhotoWindow();                // 0x0063EC10
    void FUN_0063f060();                        // 0x0063F060
    void SavePhoto(uint32_t a);                 // 0x0063F420
    void SendPhoto();                           // 0x0063FD20
};

} // namespace SP

namespace EA { namespace Audio {
struct IAudioSystem {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7();
    virtual uint32_t GetState();    // +0x20
};
IAudioSystem* GetSystemAT();        // 0x00A206F0
} }

// 0x00435E90 (an out-of-line /Od copy is what the linker kept)
inline uint32_t GetRecorderState()
{
    EA::Audio::IAudioSystem* s = EA::Audio::GetSystemAT();
    return s ? s->GetState() : 0;
}
void PlayAudio(uint32_t soundID, uint32_t state);                         // 0x00435ED0 (cdecl)
bool TryGetUIntProperty(void* propList, uint32_t id, uint32_t* out);      // 0x00410370 (cdecl)
extern void* g_PhotoPropList;                                             // 0x015FD918

struct cUIHints { void SetEnabled(bool on, bool b); };                    // 0x0067C420
cUIHints* UIHints();                                                      // 0x0067CAC0
namespace UI { void CalloutMessageBox(void* config, void* text); }        // 0x00809DB0
extern char g_CalloutConfig[];      // 0x01524C60
extern char g_CalloutTakeFull[];    // 0x01524BD0
extern char g_CalloutLogin[];       // 0x01524C54
extern char g_CalloutRegister[];    // 0x01524C48
extern char g_CalloutActions[];     // 0x01524BF4
extern char g_CalloutDeleteAll[];   // 0x01524BDC
extern char g_CalloutDelete[];      // 0x01524BE8

namespace SP {

bool cSPPlayModeSubModePhoto::HandleButton(int id)
{
    cString unused;
    if (mPlayMode) {
        mPlayMode->WakeupCreature();
        mPlayMode->FUN_00628810();
    }

    switch (id) {
    case 0x3a8ede4:     // BtnTakePicture
        if (mbF30)
            break;
        if (!FUN_0063ed00() && !FUN_0063ed50())
            break;
        if (mPhotoBrowser.FUN_00632e40())
            mPhotoBrowser.ClearPhotoList();
        if (mPhotoBrowser.FUN_00cee370() < 0x63) {
            if (mUI) {
                mUI->SetEnableTakePictureButton(false);
                mUI->SetEnableNewCreatureButton(false);
                mUI->SetEnableRecordMovieButton(false);
                mUI->FUN_00635350(0, 1);
            }
            FUN_0063f060();
            uint32_t value;
            TryGetUIntProperty(g_PhotoPropList, 0x473b871, &value);
            SavePhoto(value);
            mUI->SetHighlight(0x445ea50, true);
            MessageServer()->PostMSG(0x52f180, 0x1e, 0);
            return true;
        }
        if (mUI->mbLayoutInit) {
            UIHints()->SetEnabled(false, true);
            UI::CalloutMessageBox(g_CalloutConfig, g_CalloutTakeFull);
            mDialogInProgress = 8;
            return true;
        }
        break;

    case 0x3eab260:
        PlayAudio(0xceaee5e8, GetRecorderState());
        mPhotoBrowser.SendPhoto(mPhotoBrowser.FUN_006c0200());
        return true;
    case 0x3f15ea8:
        PlayAudio(0xceaee5e8, GetRecorderState());
        mPhotoBrowser.SendPhoto(mPhotoBrowser.FUN_006c0200() + 1);
        return true;
    case 0x3f15ef8:
        PlayAudio(0xceaee5e8, GetRecorderState());
        mPhotoBrowser.SendPhoto(mPhotoBrowser.FUN_006c0200() + 2);
        return true;
    case 0x3f6c0e8:
        PlayAudio(0xceaee5e8, GetRecorderState());
        mPhotoBrowser.SendPhoto(mPhotoBrowser.FUN_006c0200() + 3);
        return true;
    case 0x3f6c188:
        PlayAudio(0xceaee5e8, GetRecorderState());
        mPhotoBrowser.SendPhoto(mPhotoBrowser.FUN_006c0200() + 4);
        return true;
    case 0x3f6c1b4:
        PlayAudio(0xceaee5e8, GetRecorderState());
        mPhotoBrowser.SendPhoto(mPhotoBrowser.FUN_006c0200() + 5);
        return true;

    case 0x3f42784:
        PlayAudio(0xa03e74b2, GetRecorderState());
        mPhotoBrowser.NextPage();
        return true;
    case 0x3f42804:
        PlayAudio(0xa03e74b2, GetRecorderState());
        mPhotoBrowser.PrevPage();
        return true;
    case 0x3f692bc:
        PlayAudio(0xa03e74b2, GetRecorderState());
        break;

    case 0x3f67720:
        PlayAudio(0xe00ad270, GetRecorderState());
        if (mPhotoBrowser.FUN_00632e40() || !mPhotoBrowser.FUN_00633430()) {
            mPhotoBrowser.ClearPhotoList();
            CloseSendPhotoWindow();
            return true;
        }
        {
            Pollen::cAuthManager* auth = Pollen::AuthManager();
            if (!auth->IsLoggedIn()) {
                mDialogInProgress = 7;
                UI::CalloutMessageBox(g_CalloutConfig, g_CalloutLogin);
                mUI->SetSendEmailDialogVisibility(false);
            } else if (auth->IsRegistrationNeeded()) {
                mDialogInProgress = 6;
                UI::CalloutMessageBox(g_CalloutConfig, g_CalloutRegister);
                mUI->SetSendEmailDialogVisibility(false);
            } else {
                SendPhoto();
            }
        }
        return true;

    case 0x3fc4334:
        PlayAudio(0xa03e74b2, GetRecorderState());
        {
            uint32_t babyEvent = mBabyEventIDs[0];
            mAnim->PlayPose(mEditorBaseMode->mShadowViewer, mPoseAnimIDs[0], 0, 1, 0);
            mEditorBaseMode->FUN_00b267f0(2, 0);
            if (babyEvent != 0xffffffff)
                mEditorBaseMode->FUN_00574110(babyEvent, -1, 1.0f, 0.0f);
        }
        break;
    default:
        break;
    case 0x3fc433c:
        PlayAudio(0xa03e74b2, GetRecorderState());
        {
            uint32_t babyEvent = mBabyEventIDs[1];
            mAnim->PlayPose(mEditorBaseMode->mShadowViewer, mPoseAnimIDs[1], 0, 1, 0);
            mEditorBaseMode->FUN_00b267f0(2, 1);
            if (babyEvent != 0xffffffff)
                mEditorBaseMode->FUN_00574110(babyEvent, -1, 1.0f, 0.0f);
        }
        break;
    case 0x3fc4344:
        PlayAudio(0xa03e74b2, GetRecorderState());
        {
            uint32_t babyEvent = mBabyEventIDs[2];
            mAnim->PlayPose(mEditorBaseMode->mShadowViewer, mPoseAnimIDs[2], 0, 1, 0);
            mEditorBaseMode->FUN_00b267f0(2, 2);
            if (babyEvent != 0xffffffff)
                mEditorBaseMode->FUN_00574110(babyEvent, -1, 1.0f, 0.0f);
        }
        break;
    case 0x3fc4350:
        PlayAudio(0xa03e74b2, GetRecorderState());
        {
            uint32_t babyEvent = mBabyEventIDs[3];
            mAnim->PlayPose(mEditorBaseMode->mShadowViewer, mPoseAnimIDs[3], 0, 1, 0);
            mEditorBaseMode->FUN_00b267f0(2, 3);
            if (babyEvent != 0xffffffff)
                mEditorBaseMode->FUN_00574110(babyEvent, -1, 1.0f, 0.0f);
        }
        break;
    case 0x3fc4358:
        PlayAudio(0xa03e74b2, GetRecorderState());
        {
            uint32_t babyEvent = mBabyEventIDs[4];
            mAnim->PlayPose(mEditorBaseMode->mShadowViewer, mPoseAnimIDs[4], 0, 1, 0);
            mEditorBaseMode->FUN_00b267f0(2, 4);
            if (babyEvent != 0xffffffff)
                mEditorBaseMode->FUN_00574110(babyEvent, -1, 1.0f, 0.0f);
        }
        break;
    case 0x3fc435c:
        PlayAudio(0xa03e74b2, GetRecorderState());
        {
            uint32_t babyEvent = mBabyEventIDs[5];
            mAnim->PlayPose(mEditorBaseMode->mShadowViewer, mPoseAnimIDs[5], 0, 1, 0);
            mEditorBaseMode->FUN_00b267f0(2, 5);
            if (babyEvent != 0xffffffff)
                mEditorBaseMode->FUN_00574110(babyEvent, -1, 1.0f, 0.0f);
        }
        break;

    case 0x410cf00: mPhotoBrowser.EnterMoveMode(); return true;
    case 0x410d340: mPhotoBrowser.DeleteSelected(); return true;
    case 0x410d358: mPhotoBrowser.SelectAll(true); return true;
    case 0x410d368: mPhotoBrowser.SelectAll(false); return true;
    case 0x410d370: mPhotoBrowser.ExitDeleteMode(); return true;
    case 0x41a30c0: mPhotoBrowser.EnterDeleteMode(); return true;
    case 0x41a3ba8: mPhotoBrowser.SelectAll(false); return true;
    case 0x41a3bb8: mPhotoBrowser.SelectAll(true); return true;
    case 0x41a3bd0: mPhotoBrowser.MoveSelected(); return true;
    case 0x41a3be8: mPhotoBrowser.ExitMoveMode(); return true;

    case 0x4463e78:
        PlayAudio(0xa03e74b2, GetRecorderState());
        UIHints()->SetEnabled(false, true);
        UI::CalloutMessageBox(g_CalloutConfig, g_CalloutActions);
        mDialogInProgress = 3;
        return true;

    case 0x447b968:
        PlayAudio(0xa03e74b2, GetRecorderState());
        if (mPhotoBrowser.FUN_00632e40()) {
            mPhotoBrowser.ClearPhotoList();
            CloseSendPhotoWindow();
            return true;
        }
        mPhotoBrowser.FUN_00634520();
        return true;
    case 0x447b980:
        PlayAudio(0xa03e74b2, GetRecorderState());
        if (mPhotoBrowser.FUN_00632e40()) {
            mPhotoBrowser.ClearPhotoList();
            CloseSendPhotoWindow();
            return true;
        }
        mPhotoBrowser.FUN_00634570();
        return true;
    case 0x447c040:
        PlayAudio(0x5ff7c871, GetRecorderState());
        if (mPhotoBrowser.FUN_00632e40()) {
            mPhotoBrowser.ClearPhotoList();
            CloseSendPhotoWindow();
            return true;
        }
        mPhotoBrowser.FUN_0062ff80(0);
        UIHints()->SetEnabled(false, true);
        mUI->SetSendEmailDialogVisibility(false);
        UI::CalloutMessageBox(g_CalloutConfig, g_CalloutDeleteAll);
        mDialogInProgress = 2;
        return true;
    case 0x447c4e8:
        PlayAudio(0xa03e74b2, GetRecorderState());
        if (mPhotoBrowser.FUN_00632e40()) {
            mPhotoBrowser.ClearPhotoList();
            CloseSendPhotoWindow();
            return true;
        }
        mPhotoBrowser.FUN_0062ff80(2);
        UIHints()->SetEnabled(false, true);
        mUI->SetSendEmailDialogVisibility(false);
        UI::CalloutMessageBox(g_CalloutConfig, g_CalloutDelete);
        mDialogInProgress = 2;
        return true;

    case 0x5adbea8:
        CloseSendPhotoWindow();
        return true;

    }
    return true;
}

} // namespace SP
