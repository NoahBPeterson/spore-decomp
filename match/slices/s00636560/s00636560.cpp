// slice s00636560: cSPPlayModeUI::DoMessageInternal (3702 bytes), the play-mode UI command handler.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /GS- (same module as s00636320).
// Self-contained declarations (retail layout); callees are masked relocations.
#include "types.h"

// ---------------------------------------------------------------- windows / helpers
struct IWindow {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual uint32_t GetFlags();                              // +0x28
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void SetFlag(int flag, bool on);                  // +0x7C
};

// flag 2 = visible, flag 1 = enabled
static __forceinline void ToggleVisible(IWindow* w, bool allowShow)
{
    if (w) {
        if (!(w->GetFlags() & 2))
            w->SetFlag(2, allowShow);
        else
            w->SetFlag(2, false);
    }
}
#define ToggleWindowVisible(w) ToggleVisible(w, true)
static __forceinline void HideWindow(IWindow* w)
{
    if (w) {
        w->GetFlags();
        w->SetFlag(2, false);
    }
}
static __forceinline void EnableWindow(IWindow* w, bool on)
{
    if (w) w->SetFlag(1, on);
}

struct IAudioSystem {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03(); virtual void a04();
    virtual void a05(); virtual void a06(); virtual void a07();
    virtual int GetState();                                   // +0x20
};
namespace EA { namespace Audio { IAudioSystem* GetSystemAT(); } }    // 0x00A206F0
int GetRecorderState();                                       // 0x00435E90 (out-of-line copy of the inline below)
void PlayUISound(uint32_t soundID, int state);                // 0x00435ED0 (cdecl)

static inline int GetAudioState()
{
    IAudioSystem* sys = EA::Audio::GetSystemAT();
    return sys ? sys->GetState() : 0;
}

struct IMessageServer {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03(); virtual void m04();
    virtual void PostMSG(uint32_t a, uint32_t b, uint32_t c); // +0x14
};
namespace SP { IMessageServer* MessageServer(); }             // 0x0067DCC0

// ---------------------------------------------------------------- editor / play mode
struct IPaletteObject {
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03(); virtual void p04();
    virtual void p05(); virtual void p06();
    virtual void SetVisible(bool b);                          // +0x1C
};

struct cSPEditorUI {
    IWindow* FindWindowByID(uint32_t id);                     // 0x005DC310
    void DoSaveAndExit();                                     // 0x005DFB40
    void SetMode103();                                        // 0x005DF8D0
};

struct cAppModeEditorBase {
    uint32_t pad00[0x78 / 4];
    cSPEditorUI* mpEditorUI;                                  // +0x78
    uint32_t pad7c[(0x358 - 0x7c) / 4];
    IPaletteObject* mpPaintPalette;                           // +0x358
    void ShowTutorial();                                      // 0x00572260
};

struct cPhotoQueue { uint32_t Count(); };                     // 0x00CEE370
struct cSPPlayModeSubModePhoto {
    uint32_t pad00[0x50 / 4];
    cPhotoQueue mQueue;                                       // +0x50
    cPhotoQueue* GetQueue() { return &mQueue; }
    bool IsPhotosWriting(bool b);                             // 0x0063EB90
    void FUN_0063ece0(int a);                                 // 0x0063ECE0
};

struct cSPPlayMode {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08();
    virtual void HandleCommand(uint32_t id);                  // +0x24
    uint32_t pad04[(0x1e8 - 4) / 4];
    cSPPlayModeSubModePhoto mPhotoMode;                       // +0x1E8
    cSPPlayModeSubModePhoto* GetPhotoMode() { return &mPhotoMode; }

    void FUN_006284b0(int mode);                              // 0x006284B0
    void ToggleBaby(int which);                               // 0x0062C990
    void RunSkinPaintOnEditorModel(int a, int b);             // 0x0062C7E0
    void FUN_0062ba10(int a);                                 // 0x0062BA10
    void FUN_006288f0();                                      // 0x006288F0
    void FUN_006288d0(int a);                                 // 0x006288D0
};

struct cSPUILayout {
    uint32_t pad[0x18 / 4];
    bool IsVisible();                                         // 0x00810070
};

struct UIMessage {
    uint32_t pad00[2];
    uint32_t mType;                                           // +0x08
    int mCommandID;                                           // +0x0C
};

// ---------------------------------------------------------------- cSPPlayModeUI
struct cSPPlayModeUI {
    uint32_t pad00[3];
    cAppModeEditorBase* mpEditor;       // +0x0C
    cSPPlayMode* mpPlayMode;            // +0x10
    cSPUILayout mLayout;                // +0x14
    cSPUILayout mCameraControlsLayout;  // +0x2C
    uint32_t pad44[(0x60 - 0x44) / 4];
    bool mbField60;                     // +0x60

    IWindow* FindPlayModeUIWindow(uint32_t id);               // 0x00634DC0
    void SetSelected(uint32_t id, bool b);                    // 0x00634EC0
    void ToggleNameAndDescribe(bool b);                       // 0x00635390
    void SetUIGroupVisible(uint32_t id, bool on);             // 0x00635760
    void SetEditorUIGroupVisible(uint32_t id, bool on);       // 0x00635790
    bool IsUIGroupEnabled(uint32_t id);                       // 0x00635890
    void SetTabIndentOff(uint32_t id);                        // 0x00635DC0
    void SetTabIndentOn();                                    // 0x00635E80
    void SetAnimButtonsEnabled(bool b);                       // 0x00635F00
    void SetExpansionAnimButtonsEnabled(bool b);              // 0x00635FF0
    bool DoMessageInternal(uint32_t a, UIMessage* msg);       // 0x00636560
};

// @ 0x00636560
bool cSPPlayModeUI::DoMessageInternal(uint32_t a, UIMessage* msg)
{
    if (!mLayout.IsVisible())
        return false;
    mbField60 = false;
    if (msg->mType != 0x287259f6)
        return false;

    switch (msg->mCommandID) {
    case 0x3e40428:
        mpPlayMode->FUN_006284b0(1);
        return true;
    case 0x3e40444:
        mpPlayMode->FUN_006284b0(0);
        return true;
    case 0x3e44efc:
        PlayUISound(0xa03e74b2, GetRecorderState());
        mpPlayMode->ToggleBaby(0);
        return true;
    case 0x3e41e20:
        mpPlayMode->FUN_006284b0(2);
        return true;

    case 0x3f43834:
        PlayUISound(0x957c48e7, GetRecorderState());
        ToggleWindowVisible(FindPlayModeUIWindow(0x3e831e4));
        HideWindow(FindPlayModeUIWindow(0x44594d8));
        HideWindow(FindPlayModeUIWindow(0x445a468));
        EnableWindow(FindPlayModeUIWindow(0x5ac71d9), false);
        EnableWindow(FindPlayModeUIWindow(0x5ac71da), false);
        if (IsUIGroupEnabled(0x3e831e4)) {
            EnableWindow(FindPlayModeUIWindow(0x5ac71d8), true);
            SetTabIndentOff(0x46db770);
            ToggleNameAndDescribe(true);
            mpEditor->mpPaintPalette->SetVisible(false);
            SetAnimButtonsEnabled(true);
            SetExpansionAnimButtonsEnabled(false);
            mpPlayMode->FUN_006288f0();
            SP::MessageServer()->PostMSG(0x52f180, 0x1a, 0);
        } else {
            EnableWindow(FindPlayModeUIWindow(0x5ac71d8), false);
            SetTabIndentOn();
            ToggleNameAndDescribe(false);
            SetAnimButtonsEnabled(false);
        }
        SetSelected(0x44593d0, false);
        SetSelected(0x445a418, false);
        return true;

    case 0x3e830f4: case 0x3e830fc: case 0x3e83104: case 0x3e8313c: case 0x3e83154: case 0x3e83170:
    case 0x3e99d88: case 0x3e99d8c: case 0x3e99d90: case 0x3e99d94: case 0x3e99de4: case 0x3e99e98:
    case 0x3fc42e4: case 0x3fc4300: case 0x3fc4304: case 0x3fc4310: case 0x3fc4314: case 0x3fc431c:
    case 0x3fc4334: case 0x3fc433c: case 0x3fc4344: case 0x3fc4350: case 0x3fc4358: case 0x3fc435c:
        PlayUISound(0xa03e74b2, GetRecorderState());
        mpPlayMode->HandleCommand(msg->mCommandID);
        SP::MessageServer()->PostMSG(0x52f180, 0x1b, 0);
        return false;

    case 0x4066678:
        mpPlayMode->RunSkinPaintOnEditorModel(-1, 0);
        return true;
    case 0x40666b8:
        mpPlayMode->FUN_0062ba10(-1);
        return true;

    case 0x44593d0:
        PlayUISound(0x957c48e7, GetRecorderState());
        ToggleWindowVisible(FindPlayModeUIWindow(0x44594d8));
        HideWindow(FindPlayModeUIWindow(0x3e831e4));
        SetAnimButtonsEnabled(false);
        HideWindow(FindPlayModeUIWindow(0x445a468));
        EnableWindow(FindPlayModeUIWindow(0x5ac71d8), false);
        EnableWindow(FindPlayModeUIWindow(0x5ac71da), false);
        if (IsUIGroupEnabled(0x44594d8)) {
            EnableWindow(FindPlayModeUIWindow(0x5ac71d9), true);
            SetTabIndentOff(0x46db958);
            ToggleNameAndDescribe(true);
            mpEditor->mpPaintPalette->SetVisible(false);
        } else {
            EnableWindow(FindPlayModeUIWindow(0x5ac71d9), false);
            SetTabIndentOn();
            ToggleNameAndDescribe(false);
        }
        SetSelected(0x3f43834, false);
        SetSelected(0x445a418, false);
        return true;

    case 0x445a418:
        PlayUISound(0x957c48e7, GetRecorderState());
        ToggleWindowVisible(FindPlayModeUIWindow(0x445a468));
        HideWindow(FindPlayModeUIWindow(0x44594d8));
        HideWindow(FindPlayModeUIWindow(0x3e831e4));
        EnableWindow(FindPlayModeUIWindow(0x5ac71d9), false);
        EnableWindow(FindPlayModeUIWindow(0x5ac71d8), false);
        SetAnimButtonsEnabled(false);
        if (IsUIGroupEnabled(0x445a468)) {
            EnableWindow(FindPlayModeUIWindow(0x5ac71da), true);
            EnableWindow(FindPlayModeUIWindow(0x46db980), true);
            EnableWindow(FindPlayModeUIWindow(0x46db858), false);
            EnableWindow(FindPlayModeUIWindow(0x46db770), false);
            EnableWindow(FindPlayModeUIWindow(0x46db958), false);
            ToggleNameAndDescribe(true);
            mpEditor->mpPaintPalette->SetVisible(false);
        } else {
            EnableWindow(FindPlayModeUIWindow(0x5ac71da), false);
            SetTabIndentOn();
            ToggleNameAndDescribe(false);
        }
        SetSelected(0x3f43834, false);
        SetSelected(0x44593d0, false);
        return true;

    case 0x445d380:
        PlayUISound(0xa03e74b2, GetRecorderState());
        mpPlayMode->ToggleBaby(1);
        return true;

    case 0x445ea50:
        PlayUISound(0x957c48e7, GetRecorderState());
        ToggleWindowVisible(FindPlayModeUIWindow(0x445ea18));
        mpPlayMode->GetPhotoMode()->FUN_0063ece0(0);
        if (IsUIGroupEnabled(0x445ea18)) {
            IWindow* w = FindPlayModeUIWindow(0x5ac71db);
            if (w) w->SetFlag(2, false);
            SetSelected(0x445ea50, true);
            if (mpPlayMode->GetPhotoMode()->GetQueue()->Count() > 0)
                SetUIGroupVisible(0x4463e78, true);
            SetEditorUIGroupVisible(0x447c040, true);
            SetEditorUIGroupVisible(0x447c4e8, true);
            SetUIGroupVisible(0x40eb500, true);
            SetUIGroupVisible(0x40eb518, true);
            SetUIGroupVisible(0x40eb7e8, true);
            SetUIGroupVisible(0x40eb7f8, true);
            SetUIGroupVisible(0x40eb818, true);
            SP::MessageServer()->PostMSG(0x52f180, 0x1f, 0);
        } else {
            IWindow* w = FindPlayModeUIWindow(0x5ac71db);
            if (w) w->SetFlag(2, true);
            SetSelected(0x445ea50, false);
            SetUIGroupVisible(0x4463e78, false);
            SetEditorUIGroupVisible(0x447c040, false);
            SetEditorUIGroupVisible(0x447c4e8, false);
            SetUIGroupVisible(0x40eb500, false);
            SetUIGroupVisible(0x40eb518, false);
            SetUIGroupVisible(0x40eb7e8, false);
            SetUIGroupVisible(0x40eb7f8, false);
            SetUIGroupVisible(0x40eb818, false);
        }
        return true;

    case 0x445d3c0:
        PlayUISound(0xa03e74b2, GetRecorderState());
        mpPlayMode->ToggleBaby(2);
        return true;

    case 0x44782a8:
        if (!(mpEditor->mpEditorUI->FindWindowByID(0x3f67620)->GetFlags() & 1)
            && !mpPlayMode->GetPhotoMode()->IsPhotosWriting(false)) {
            PlayUISound(0xf515d2c3, GetRecorderState());
            mpEditor->mpEditorUI->DoSaveAndExit();
        }
        return true;

    case 0x44dcbc8:
        if (!(mpEditor->mpEditorUI->FindWindowByID(0x3f67620)->GetFlags() & 1)
            && !mpPlayMode->GetPhotoMode()->IsPhotosWriting(true)) {
            PlayUISound(0xa03e74b2, GetRecorderState());
            mpEditor->mpEditorUI->SetMode103();
        }
        return true;

    case 0x4615580:
        PlayUISound(0x9f4d9496, GetRecorderState());
        mpEditor->ShowTutorial();
        return true;

    case 0x4864e80:
    case 0x4869260:
        mpPlayMode->FUN_006288d0(0);
        return true;
    case 0x4864e88:
    case 0x4869298:
        mpPlayMode->FUN_006288d0(1);
        return true;

    case 0x3a8ede4: case 0x3e831c4: case 0x3eab260: case 0x3f15ea8: case 0x3f15ef8: case 0x3f42784:
    case 0x3f42804: case 0x3f434ac: case 0x3f67720: case 0x3f67aec: case 0x3f692bc: case 0x3f6c0e8:
    case 0x3f6c188: case 0x3f6c1b4: case 0x3fc1740: case 0x410cf00: case 0x410d340: case 0x410d358:
    case 0x410d368: case 0x410d370: case 0x41a30c0: case 0x41a3ba8: case 0x41a3bb8: case 0x41a3bd0:
    case 0x41a3be8: case 0x445b018: case 0x445b318: case 0x445b340: case 0x445b388: case 0x4463e78:
    case 0x447b968: case 0x447b980: case 0x447c040: case 0x447c4e8: case 0x47ed5b8: case 0x47ed640:
    case 0x48669a8:
    case 0x48669c8: case 0x48669c9: case 0x48669ca: case 0x48669cb: case 0x48669cc:
    case 0x4866a98: case 0x4866a99: case 0x4866a9a: case 0x4866a9b: case 0x4866a9c: case 0x4866a9d:
    case 0x4866b10: case 0x4866b11: case 0x4866b12: case 0x4866b13: case 0x4866b14: case 0x4866b15:
    case 0x4866b68: case 0x4866b69: case 0x4866b6a: case 0x4866b6b: case 0x4866b6c: case 0x4866b6d:
    case 0x5652348: case 0x5665f58: case 0x56be960: case 0x58b74e8: case 0x5adbea8: case 0x5b02188:
    case 0x5b5bd80: case 0x5b5ef51: case 0x5b5ef52: case 0x5b5ef53: case 0x5baefc8:
    case 0x7034070: case 0x7034071:
        PlayUISound(0xa03e74b2, GetAudioState());
        // fall through
    case 0x44eec00:
        mpPlayMode->HandleCommand(msg->mCommandID);
        return true;
    default:
        return false;
    }
}
