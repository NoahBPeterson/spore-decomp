// Slice s006354c0: SP::cSPPlayModeUI (play-mode UI: window lookup helpers, button enables, Init, YouTube dialog).
#include "s006354c0.h"

class cSPUILayout {
public:
    ~cSPUILayout();                                                                        // 0x00811FE0
    bool Init(const wchar_t* name, uint32_t a, bool b, uint32_t c);                        // 0x00812160
    void SetParentWin(IWindow* pWin, bool b, uint32_t c);                                  // 0x008121B0
    IWindow* FindWindowByID(uint32_t id, bool recursive);                                  // 0x008105B0
    uint32_t pad[6];                                                                       // 0x18 bytes
};

namespace SP {
class cSPEditorUI {
public:
    IWindow* FindWindowByID(uint32_t id);                                                  // 0x005DC310
};
class cAppModeEditorBase {
public:
    char pad[0x78];
    cSPEditorUI* mpEditorUI;                                                               // +0x78
};
class cSPPlayMode;
}
namespace EA {
struct Stopwatch {
    uint32_t mStart[4];
    void Reset() { mStart[0] = 0; mStart[1] = 0; mStart[2] = 0; mStart[3] = 0; }
    void Restart();                                                                        // 0x00571E80
    uint32_t pad[2];
};
}
namespace SPUIHelpers {
void UpdateMouseFocus(bool b);                                                             // 0x00804F50
void AutoSizeWindowForText(IWindow* w, bool a, bool b);                                    // 0x00806E40
void BeginModal(IWindow* w, int a, int b);                                                 // 0x008099A0
void EndModal(IWindow* w, int a, int b);                                                   // 0x00809C50
}
struct cAppProps { char pad[0x118]; int mFlag; };
struct cAppPropsHolder { char pad[0x3c]; cAppProps* mpProps; };
extern cAppPropsHolder* sAppProperties;                                                    // 0x015FD918

struct cYTMgr { void SetMode(bool a, bool b); };                                           // 0x0067C420
cYTMgr* GetYTMgr();                                                                        // 0x0067CAC0

struct IWinMgrLike { virtual void v0(); virtual void* GetCurrent(); };                     // slot 1
IWinMgrLike* GetWindowManager();                                                           // 0x0067CAA0
struct cWinOwnerSub { void Func(bool b); };                                                // 0x00802A30
struct cWinOwnerBase0 { virtual void f0(); };
struct cWinOwnerBase1 { virtual void f1(); };
struct cWinOwner : cWinOwnerBase0, cWinOwnerBase1 {
    char pad[0x2d8 - 8];
    cWinOwnerSub* mpSub;                                                                    // +0x2d8
};

struct WinRef {
    IWindow* p;
    ~WinRef() { if (p) p->Release(); }
    operator IWindow*() const { return p; }
    IWindow* operator->() const { return p; }
    WinRef& operator=(IWindow* q) { p = q; return *this; }
};
struct IWinProcBase {                     // EA::UTFWin::IWinProc, +0x0
    virtual int AddRef(); virtual int Release(); virtual void* Cast(uint32_t t);
    virtual ~IWinProcBase() {}
};
struct RefCountVBase {                    // EA::RefCountVTemplate<int>, +0x4
    virtual int AddRef(); virtual int Release();
    virtual ~RefCountVBase() {}
    int mnRefCount;
};

namespace SP {
class cSPPlayModeUI : public IWinProcBase, public RefCountVBase {
public:
    cSPPlayModeUI();
    virtual __forceinline ~cSPPlayModeUI() {}
    IWindow* FindPlayModeUIWindow(uint32_t id);                                            // 0x00634DC0
    void AddToolTip(uint32_t id, uint32_t strId, const wchar_t* text, int a, int b);       // 0x00635040
    void AddEditorUIToolTip(uint32_t id, uint32_t strId, const wchar_t* text, int a, int b);// 0x00635160
    void SetUpSendEmailWindow();
    void ResetSendEmailWindow();
    void SetEnableNewCreatureButton(bool b);
    void SetEnableTakePictureButton(bool b);
    void SetEnableRecordMovieButton(bool b);
    void SetUIGroupVisible(uint32_t id, bool b);
    void SetEditorUIGroupVisible(uint32_t id, bool b);
    void ToggleUIGroup(uint32_t id, bool b);
    void SetCheckButtonSelected(uint32_t id, bool b);
    bool IsCheckButtonSelected(uint32_t id);
    bool IsUIGroupEnabled(uint32_t id);
    bool Init(cAppModeEditorBase* app, cSPPlayMode* pm);
    void SetTabIndentOff(uint32_t id);
    void SetTabIndentOn();
    void SetAnimButtonsEnabled(bool b);
    void SetExpansionAnimButtonsEnabled(bool b);
    void ShowYouTubeLoginDialog();
    void HideYouTubeLoginDialog();
    void FUN_00634b10();

    cAppModeEditorBase* mApp;                                                              // +0xc
    cSPPlayMode* mPlayMode;                                                                // +0x10
    cSPUILayout mLayout;                                                                   // +0x14
    cSPUILayout mCameraControlsLayout;                                                     // +0x2c
    bool mbLayoutInit;                                                                     // +0x44
    char pad45[3];
    EA::Stopwatch mUI_Init_Timer;                                                          // +0x48
    bool mbWaitForUI_Init_Timer;                                                           // +0x60
    char pad61[3];
    WinRef mpField64;                                                                    // +0x64
    WinRef mpYouTubeDlg;                                                                 // +0x68
};
}

using namespace SP;

// @ 0x006354C0
void cSPPlayModeUI::SetUpSendEmailWindow()
{
    IWindow* w = FindPlayModeUIWindow(0x3f67620);
    if (w) w->AddRef();
    w->GetParent()->RemoveWindow(w);
    mApp->mpEditorUI->FindWindowByID(-1)->AddWindow(w);
    w->Release();
}

// @ 0x00635520
void cSPPlayModeUI::ResetSendEmailWindow()
{
    IWindow* w = mApp->mpEditorUI->FindWindowByID(0x3f67620);
    if (w) w->AddRef();
    w->GetParent()->RemoveWindow(w);
    FindPlayModeUIWindow(-1)->AddWindow(w);
    w->Release();
}

#define SET_ENABLE_BODY(ID, EXTRA) \
    IWindow* w = mApp->mpEditorUI->FindWindowByID(ID); \
    if (w) { \
        w->SetFlag(2, b); \
        w->SetFlag(0x10, !b); \
        if (b) { w->SetShadeColor(0xffffffff); EXTRA w->Invalidate(); } \
        else { w->SetShadeColor(0xa0a0a0a0); w->Invalidate(); } \
    }

// @ 0x00635580
void cSPPlayModeUI::SetEnableNewCreatureButton(bool b)
{
    SET_ENABLE_BODY(0x4766ff0, )
}

// @ 0x00635600
void cSPPlayModeUI::SetEnableTakePictureButton(bool b)
{
    SET_ENABLE_BODY(0x3a8ede4, SPUIHelpers::UpdateMouseFocus(true);)
}

// @ 0x00635680
void cSPPlayModeUI::SetEnableRecordMovieButton(bool b)
{
    SET_ENABLE_BODY(0x3fc1740, )
}

// @ 0x00635700  (scalar deleting destructor)
cSPPlayModeUI::cSPPlayModeUI() {}   // out-of-line ctor only to force the vtable and ??_G emission

// @ 0x00635760
void cSPPlayModeUI::SetUIGroupVisible(uint32_t id, bool b)
{
    IWindow* w = FindPlayModeUIWindow(id);
    if (w) w->SetFlag(1, b);
}

// @ 0x00635790
void cSPPlayModeUI::SetEditorUIGroupVisible(uint32_t id, bool b)
{
    cSPEditorUI* ui = mApp->mpEditorUI;
    IWindow* w = ui->FindWindowByID(id);
    if (w) w->SetFlag(1, b);
}

// @ 0x006357C0
void cSPPlayModeUI::ToggleUIGroup(uint32_t id, bool b)
{
    IWindow* w = FindPlayModeUIWindow(id);
    if (w) {
        if (!(w->GetFlags() & 2) && !b)
            w->SetFlag(2, true);
        else
            w->SetFlag(2, false);
    }
}

// @ 0x00635810
void cSPPlayModeUI::SetCheckButtonSelected(uint32_t id, bool b)
{
    IWindow* w = FindPlayModeUIWindow(id);
    IButton* btn = w ? (IButton*)w->Cast(0x8ed27e7a) : 0;
    btn->SetStateFlag(4, b);
}

// @ 0x00635850
bool cSPPlayModeUI::IsCheckButtonSelected(uint32_t id)
{
    IWindow* w = FindPlayModeUIWindow(id);
    IButton* btn = w ? (IButton*)w->Cast(0x8ed27e7a) : 0;
    uint8_t f = btn->GetButtonStateFlags();
    f >>= 2;
    f &= 1;
    return f;
}

// @ 0x00635890
bool cSPPlayModeUI::IsUIGroupEnabled(uint32_t id)
{
    IWindow* w = FindPlayModeUIWindow(id);
    if (w && (w->GetFlags() & 2))
        return true;
    return false;
}

// @ 0x006358C0
bool cSPPlayModeUI::Init(cAppModeEditorBase* app, cSPPlayMode* pm)
{
    IWindow* root;
    IWindow* w;
    IWindow* cam;
    mApp = app;
    mPlayMode = pm;
    if (app == 0) return false;
    if (pm == 0) return false;
    bool ok = mLayout.Init(L"PlayMode", 0x40464100, false, 0x5b598fa);
    if (!ok) return ok;
    {
    {
    mbLayoutInit = true;
    mUI_Init_Timer.Reset();
    mUI_Init_Timer.Restart();
    mbWaitForUI_Init_Timer = true;
    root = mLayout.FindWindowByID(-1, true);
    if (root) {
        root->AddWinProc(this);
        root->SetLocation(0.0f, 0.0f);
        root->SetFlag(1, true);
        w = mApp->mpEditorUI->FindWindowByID(0x4816f20);
        w->AddWindow(root);
        SetUpSendEmailWindow();
        FUN_00634b10();
        cam = mApp->mpEditorUI->FindWindowByID(0x4fcc582);
        if (cam) {
            cSPUILayout* cl = &mCameraControlsLayout;
            cl->Init(L"CameraControls", 0x40464100, true, 0x5b598fa);
            cl->SetParentWin(cam, true, 0x5b598fa);
        }
    }
    AddEditorUIToolTip(0x3f67720, 0x4598e97, L"*Send Mail*", 0, 0);
    AddEditorUIToolTip(0x56be960, 0x4598e97, L"*Send Mail*", 0, 0);
    AddToolTip(0x3f43834, 0x46287d6, L"*Animate*", 0, 0);
    AddToolTip(0x44593d0, 0x46287d8, L"*Backdrops*", 0, 0);
    AddToolTip(0x445a418, 0x46287da, L"*Babies*", 0, 0);
    AddToolTip(0x445ea50, 0x46287a4, L"*PictureViewer*", 0, 0);
    AddToolTip(0x3a8ede4, 0x46287a5, L"*ShootPictures*", 0, 0);
    AddToolTip(0x3fc1740, 0x46287a6, L"*RecordVideo*", 0, 0);
    AddToolTip(0x4463e78, 0x473f903, L"*ManagePhotos*", 0, 0);
    AddToolTip(0x44782a8, 0x46287ed, L"*Save*", 0, 0);
    AddToolTip(0x44dcbc8, 0x4583afb, L"*Cancel*", 0, 0);
    AddToolTip(0x4615580, 0x462932d, L"*Help*", 0, 0);
    AddToolTip(0x3fc4334, 0x4628719, L"*Tadah*", 0, 0);
    AddToolTip(0x3fc433c, 0x4628726, L"*Hey*", 0, 0);
    AddToolTip(0x3fc4344, 0x4628722, L"*Cutie*", 0, 0);
    AddToolTip(0x3fc4350, 0x4628729, L"*Flex*", 0, 0);
    AddToolTip(0x3fc4358, 0x4628724, L"*Sumo*", 0, 0);
    AddToolTip(0x3fc435c, 0x4628733, L"*HeyBaby*", 0, 0);
    AddToolTip(0x3e830f4, 0x4628737, L"*ThePoint*", 0, 0);
    AddToolTip(0x3e830fc, 0x4628745, L"*HippityHop*", 0, 0);
    AddToolTip(0x3e83104, 0x4628739, L"*WalkNPlace*", 0, 0);
    AddToolTip(0x3e8313c, 0x4628749, L"*TheStomp*", 0, 0);
    AddToolTip(0x3e83154, 0x462873f, L"*HotFoot*", 0, 0);
    AddToolTip(0x3e83170, 0x462874e, L"*RaverPunch*", 0, 0);
    AddToolTip(0x3fc42e4, 0x4628798, L"*Happy*", 0, 0);
    AddToolTip(0x3fc4300, 0x46287a1, L"*Angry*", 0, 0);
    AddToolTip(0x3fc4304, 0x462879c, L"*Sad*", 0, 0);
    AddToolTip(0x3fc4310, 0x46287a2, L"*Laugh*", 0, 0);
    AddToolTip(0x3fc4314, 0x46287a0, L"*Scared*", 0, 0);
    AddToolTip(0x3fc431c, 0x46287a3, L"*Swoon*", 0, 0);
    AddToolTip(0x3e99d88, 0x46286e7, L"*Spin*", 0, 0);
    AddToolTip(0x3e99d8c, 0x46286f8, L"*Roar*", 0, 0);
    AddToolTip(0x3e99d90, 0x4628717, L"*Bite*", 0, 0);
    AddToolTip(0x3e99de4, 0x4628713, L"*Call*", 0, 0);
    AddToolTip(0x3e99d94, 0x46286f2, L"*Backflip*", 0, 0);
    AddToolTip(0x3e99e98, 0x46286f4, L"*Sit*", 0, 0);
    AddEditorUIToolTip(0x447c040, 0x474e80d, L"*DeleteImage*", 0, 0);
    AddEditorUIToolTip(0x447c4e8, 0x474e80e, L"*ArchiveImage*", 0, 0);
    w = FindPlayModeUIWindow(0x477ae30);
    if (w) w->SetFlag(1, true);
    if (sAppProperties->mpProps->mFlag) {
        w = FindPlayModeUIWindow(0x4615580);
        if (w) w->SetFlag(1, true);
    }
    return root != 0;
    }
    }
}

// @ 0x00635DC0
void cSPPlayModeUI::SetTabIndentOff(uint32_t id)
{
    IWindow* w = FindPlayModeUIWindow(id);
    if (w) w->SetFlag(1, true);
    w = FindPlayModeUIWindow(0x46db858);
    if (w) w->SetFlag(1, false);
    IWindow* h;
    switch (id) {
    case 0x46db770:
        h = FindPlayModeUIWindow(0x46db958); if (h) h->SetFlag(1, false);
        h = FindPlayModeUIWindow(0x46db980); if (h) h->SetFlag(1, false);
        break;
    case 0x46db958:
        h = FindPlayModeUIWindow(0x46db770); if (h) h->SetFlag(1, false);
        h = FindPlayModeUIWindow(0x46db980); if (h) h->SetFlag(1, false);
        break;
    case 0x46db980:
        h = FindPlayModeUIWindow(0x46db770); if (h) h->SetFlag(1, false);
        h = FindPlayModeUIWindow(0x46db958); if (h) h->SetFlag(1, false);
        break;
    }
}

// @ 0x00635E80
void cSPPlayModeUI::SetTabIndentOn()
{
    IWindow* w = FindPlayModeUIWindow(0x46db858);
    if (w) w->SetFlag(1, true);
    w = FindPlayModeUIWindow(0x46db770);
    if (w) w->SetFlag(1, false);
    w = FindPlayModeUIWindow(0x46db958);
    if (w) w->SetFlag(1, false);
    w = FindPlayModeUIWindow(0x46db980);
    if (w) w->SetFlag(1, false);
}

// @ 0x00635F00
void cSPPlayModeUI::SetAnimButtonsEnabled(bool b)
{
    IWindow* w;
    w = FindPlayModeUIWindow(0x480e060); if (w) w->SetFlag(2, b);
    w = FindPlayModeUIWindow(0x480e150); if (w) w->SetFlag(2, b);
    w = FindPlayModeUIWindow(0x480e160); if (w) w->SetFlag(2, b);
    w = FindPlayModeUIWindow(0x480e170); if (w) w->SetFlag(2, b);
    w = FindPlayModeUIWindow(0x480e060); if (w) w->SetFlag(1, b);
    w = FindPlayModeUIWindow(0x480e150); if (w) w->SetFlag(1, b);
    w = FindPlayModeUIWindow(0x480e160); if (w) w->SetFlag(1, b);
    w = FindPlayModeUIWindow(0x480e170); if (w) w->SetFlag(1, b);
}

// @ 0x00635FF0
void cSPPlayModeUI::SetExpansionAnimButtonsEnabled(bool b)
{
    IWindow* w;
    w = FindPlayModeUIWindow(0x48666b8); if (w) w->SetFlag(2, b);
    w = FindPlayModeUIWindow(0x48667a8); if (w) w->SetFlag(2, b);
    w = FindPlayModeUIWindow(0x48667c8); if (w) w->SetFlag(2, b);
    w = FindPlayModeUIWindow(0x48667e0); if (w) w->SetFlag(2, b);
    w = FindPlayModeUIWindow(0x48666b8); if (w) w->SetFlag(1, b);
    w = FindPlayModeUIWindow(0x48667a8); if (w) w->SetFlag(1, b);
    w = FindPlayModeUIWindow(0x48667c8); if (w) w->SetFlag(1, b);
    w = FindPlayModeUIWindow(0x48667e0); if (w) w->SetFlag(1, b);
}

// @ 0x006360E0
void cSPPlayModeUI::ShowYouTubeLoginDialog()
{
    GetYTMgr()->SetMode(false, true);
    IWindow* w = FindPlayModeUIWindow(0x5650630);
    if (w) w->SetFlag(1, true);
    w = FindPlayModeUIWindow(0x5650568);
    if (w) w->SetFlag(1, true);
    IWindow* t = FindPlayModeUIWindow(0x5baefc8);
    SPUIHelpers::AutoSizeWindowForText(t, false, false);
    IWindow* a = FindPlayModeUIWindow(0x5652348);
    SPUIHelpers::AutoSizeWindowForText(a, true, false);
    IWindow* c = FindPlayModeUIWindow(0x5b5bd80);
    SPUIHelpers::AutoSizeWindowForText(c, true, false);
    if (a && c) {
        float* ra = a->GetRealArea();
        float* rc = c->GetRealArea();
        c->SetLayoutLocation(ra[0] - (rc[2] - rc[0]), rc[1]);
    }
    if (!mpYouTubeDlg) {
        IWindow* d = FindPlayModeUIWindow(0x5650568);
        IWindow* old = mpYouTubeDlg;
        if (d != old) {
            if (d) d->AddRef();
            mpYouTubeDlg = d;
            if (old) old->Release();
        }
        mpYouTubeDlg->GetParent()->RemoveWindow(mpYouTubeDlg);
    }
    SPUIHelpers::BeginModal(mpYouTubeDlg, 0, 0);
    void* m = GetWindowManager()->GetCurrent();
    cWinOwner* o = m ? (cWinOwner*)((char*)m - 4) : 0;
    o->mpSub->Func(false);
}

// @ 0x00636260
void cSPPlayModeUI::HideYouTubeLoginDialog()
{
    GetYTMgr()->SetMode(true, true);
    if (mpYouTubeDlg)
        SPUIHelpers::EndModal(mpYouTubeDlg, 0, 0);
    IWindow* w = FindPlayModeUIWindow(0x5650630);
    if (w && mpYouTubeDlg) {
        mpYouTubeDlg->GetParent()->RemoveWindow(mpYouTubeDlg);
        w->AddWindow(mpYouTubeDlg);
    }
    IWindow* d = mpYouTubeDlg;
    if (d) {
        mpYouTubeDlg = 0;
        d->Release();
    }
    w = FindPlayModeUIWindow(0x5650630);
    if (w) w->SetFlag(1, false);
    w = FindPlayModeUIWindow(0x5650568);
    if (w) w->SetFlag(1, false);
}
