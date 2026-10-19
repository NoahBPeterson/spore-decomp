// src/game/SPEditors/SPPlayModeUI.cpp -- migrated from slice(s) s00634490, s00637f80, s006373e0, s00636560, s00636320, s006354c0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPlayModeUI.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Stopwatch.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cSPEditorUI.h"
#include "SP/cSPPlayModeUI.h"
#include "cSPUILayout.h"
#include "SP/cSPEditorNaming.h"
#include "SP/cSPPlayModeSubModePhoto.h"
#include "eastl/allocator.h"
#include "eastl/string.h"
#include "SP/cAnimatingCreature.h"
#include "SP/cSPEditorAnimatedCreatureManager.h"
#include "SP/cSPPlayMode.h"
#include "SP/cSPPlayModeAnimation.h"
#include "SP/cSPPlayModeSubModeAction.h"
#include "SP/cString.h"
#include "EA/Swarm/cIVisualEffect.h"
#include "SP/cSPPlayModePhotoBrowser.h"
#include "SP/cPropertyList.h"
#include "SP/cJob.h"
#include "SP/cPlayModeTokenTranslator.h"
#include "cSPUITooltipWinProc.h"
#include "SP/cStringTokenTranslator.h"

// ---- items of slice s006354c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class IWindow {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual IWindow* Cast(uint32_t type);
    virtual IWindow* GetParent();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual uint32_t GetFlags();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual float* GetRealArea();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void SetShadeColor(uint32_t c);
    virtual void v24();
    virtual void SetLocation(float x, float y);
    virtual void v26();
    virtual void v27();
    virtual void SetLayoutLocation(float x, float y);
    virtual void v29();
    virtual void v30();
    virtual void SetFlag(int flag, bool v);
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual int Invalidate();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void AddWindow(IWindow* w);
    virtual void RemoveWindow(IWindow* w);
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void AddWinProc(void* p);
};
class IButton {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual uint8_t GetButtonStateFlags();      // +0x20
    virtual void v9();
    virtual void SetStateFlag(int flag, bool v);    // +0x28
};
class cSPUILayout_s0063_54c0 {
public:
    ~cSPUILayout_s0063_54c0();                                                                        // 0x00811FE0
    bool Init(const wchar_t* name, uint32_t a, bool b, uint32_t c);                        // 0x00812160
    void SetParentWin(IWindow* pWin, bool b, uint32_t c);                                  // 0x008121B0
    IWindow* FindWindowByID(uint32_t id, bool recursive);                                  // 0x008105B0
    uint32_t pad[6];                                                                       // 0x18 bytes
};
namespace SP {
class cSPEditorUI_s0063_54c0 {
public:
    IWindow* FindWindowByID(uint32_t id);                                                  // 0x005DC310
};
}
namespace SP {
class cAppModeEditorBase_s0063_54c0 {
public:
    char pad[0x78];
    cSPEditorUI_s0063_54c0* mpEditorUI;                                                               // +0x78
};
}
namespace SP {
class cSPPlayMode_s0063_54c0;
}
namespace EA {
struct Stopwatch_s0063_54c0 {
    uint32_t mStart[4];
    void Reset() { mStart[0] = 0; mStart[1] = 0; mStart[2] = 0; mStart[3] = 0; }
    void Restart();                                                                        // 0x00571E80
    uint32_t pad[2];
};
}
namespace SPUIHelpers {
void UpdateMouseFocus(bool b);                                                             // 0x00804F50
}
namespace SPUIHelpers {
void AutoSizeWindowForText(IWindow* w, bool a, bool b);                                    // 0x00806E40
}
namespace SPUIHelpers {
void BeginModal(IWindow* w, int a, int b);                                                 // 0x008099A0
}
namespace SPUIHelpers {
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
class cSPPlayModeUI_s0063_54c0 : public IWinProcBase, public RefCountVBase {
public:
    cSPPlayModeUI_s0063_54c0();
    virtual __forceinline ~cSPPlayModeUI_s0063_54c0() {}
    IWindow* FindPlayModeUIWindow(uint32_t id);                                            // 0x00634DC0
    void AddToolTip(uint32_t id, uint32_t strId, const wchar_t* text, int a, int b);       // 0x00635040
    void AddEditorUIToolTip(uint32_t id, uint32_t strId, const wchar_t* text, int a, int b);// 0x00635160
    void SetUpSendEmailWindow();  // 0x006354c0 (SP::cSPPlayModeUI::SetUpSendEmailWindow)
    void ResetSendEmailWindow();
    void SetEnableNewCreatureButton(bool b);  // 0x00635580 (SP::cSPPlayModeUI::SetEnableNewCreatureButton)
    void SetEnableTakePictureButton(bool b);  // 0x00635600 (SP::cSPPlayModeUI::SetEnableTakePictureButton)
    void SetEnableRecordMovieButton(bool b);  // 0x00635680 (SP::cSPPlayModeUI::SetEnableRecordMovieButton)
    void SetUIGroupVisible(uint32_t id, bool b);  // 0x00635760 (SP::cSPPlayModeUI::SetUIGroupVisible)
    void SetEditorUIGroupVisible(uint32_t id, bool b);  // 0x00635790 (SP::cSPPlayModeUI::SetEditorUIGroupVisible)
    void ToggleUIGroup(uint32_t id, bool b);  // 0x006357c0 (SP::cSPPlayModeUI::ToggleUIGroup)
    void SetCheckButtonSelected(uint32_t id, bool b);
    bool IsCheckButtonSelected(uint32_t id);  // 0x00635850 (SP::cSPPlayModeUI::IsCheckButtonSelected)
    bool IsUIGroupEnabled(uint32_t id);  // 0x00635890 (SP::cSPPlayModeUI::IsUIGroupEnabled)
    bool Init(cAppModeEditorBase_s0063_54c0* app, cSPPlayMode_s0063_54c0* pm);  // 0x006358c0 (SP::cSPPlayModeUI::Init)
    void SetTabIndentOff(uint32_t id);  // 0x00635dc0 (SP::cSPPlayModeUI::SetTabIndentOff)
    void SetTabIndentOn();  // 0x00635e80 (SP::cSPPlayModeUI::SetTabIndentOn)
    void SetAnimButtonsEnabled(bool b);  // 0x00635f00 (SP::cSPPlayModeUI::SetAnimButtonsEnabled)
    void SetExpansionAnimButtonsEnabled(bool b);  // 0x00635ff0 (SP::cSPPlayModeUI::SetExpansionAnimButtonsEnabled)
    void ShowYouTubeLoginDialog();
    void HideYouTubeLoginDialog();
    void FUN_00634b10();

    cAppModeEditorBase_s0063_54c0* mApp;                                                              // +0xc
    cSPPlayMode_s0063_54c0* mPlayMode;                                                                // +0x10
    cSPUILayout_s0063_54c0 mLayout;                                                                   // +0x14
    cSPUILayout_s0063_54c0 mCameraControlsLayout;                                                     // +0x2c
    bool mbLayoutInit;                                                                     // +0x44
    char pad45[3];
    EA::Stopwatch_s0063_54c0 mUI_Init_Timer;                                                          // +0x48
    bool mbWaitForUI_Init_Timer;                                                           // +0x60
    char pad61[3];
    WinRef mpField64;                                                                    // +0x64
    WinRef mpYouTubeDlg;                                                                 // +0x68
};
}
#define SET_ENABLE_BODY(ID, EXTRA) \
    IWindow* w = mApp->mpEditorUI->FindWindowByID(ID); \
    if (w) { \
        w->SetFlag(2, b); \
        w->SetFlag(0x10, !b); \
        if (b) { w->SetShadeColor(0xffffffff); EXTRA w->Invalidate(); } \
        else { w->SetShadeColor(0xa0a0a0a0); w->Invalidate(); } \
    }
// ---- items of slice s006354c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cAppPropsHolder* sAppProperties;                                                    // 0x015FD918

// ---- items of slice s00636320 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IWindow_s0063_6320;
struct IOther;
struct IControl;
struct cSPEditorUI;
void operator delete(void* p);   // 0x00F47380
namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
}
namespace eastl {
extern char    gEmptyString8[1];
}
namespace eastl {
template <typename T> struct EmptyStr;
}
namespace eastl {
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
}
namespace eastl {
template <> struct EmptyStr<char>    { static char*    Get() { return gEmptyString8; } };
}
namespace eastl {
template <typename T>
struct allocator_s0063_6320 {
    void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
template <typename T, typename Allocator = allocator_s0063_6320<T> >
class basic_string_s0063_6320 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    basic_string_s0063_6320() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    ~basic_string_s0063_6320() { DeallocateSelf(); }
    const T* c_str() const { return mpBegin; }
    int sprintf(const char* fmt, ...);   // 0x00472FE0
    int append_sprintf(const char* fmt, ...);   // 0x005F9450
    void clear() { if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; } }
    void DeallocateSelf() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin); }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
};
}
namespace eastl {
typedef basic_string_s0063_6320<char> string;
}
struct cAppModeEditorBase {
    char pad78[0x78];
    cSPEditorUI* mpEditorUI;        // +0x78
    char pad7c[0x358 - 0x7c];
    void* mPaintPaletteObject;      // +0x358
};
struct cSPEditorUI {
    char pad[0x14];
    void EnableUIButton(uint32_t id, bool b);     // 0x005DC610
    IWindow_s0063_6320* FindWindowByID(uint32_t id);         // 0x005DC310
};
struct cSPUILayout_s0063_6320 {
    char pad[0x18];
    bool IsVisible();                                         // 0x00810070
    IWindow_s0063_6320* FindWindowByID(uint32_t id, bool recurse);       // 0x008105B0
    void Shutdown(bool b);                                    // 0x00811AD0
};
struct IOther {
    virtual void o00(); virtual void o01(); virtual void o02(); virtual void o03(); virtual void o04();
    virtual void o05(); virtual void o06(); virtual void o07(); virtual void o08(); virtual void o09();
    virtual void o10(); virtual void o11(); virtual void o12(); virtual void o13(); virtual void o14();
    virtual void o15(); virtual void o16(); virtual void o17(); virtual void o18(); virtual void o19();
    virtual void o20(); virtual void o21(); virtual void o22(); virtual void o23(); virtual void o24();
    virtual void o25(); virtual void o26(); virtual void o27(); virtual void o28(); virtual void o29();
    virtual void o30(); virtual void o31(); virtual void o32(); virtual void o33(); virtual void o34();
    virtual void o35(); virtual void o36(); virtual void o37(); virtual void o38(); virtual void o39();
    virtual void o40(); virtual void o41(); virtual void o42(); virtual void o43(); virtual void o44();
    virtual void o45(); virtual void o46(); virtual void o47(); virtual void o48(); virtual void o49();
    virtual void o50(); virtual void o51(); virtual void o52(); virtual void o53(); virtual void o54();
    virtual void Attach(IWindow_s0063_6320* p);              // +0xDC
};
struct IWindow_s0063_6320 {
    virtual void v00();
    virtual int Release();                                    // +0x04
    virtual void v02();
    virtual IControl* v03(uint32_t id);                       // +0x0C
    virtual IOther* GetOther();                               // +0x10
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual uint8_t v10();                                    // +0x28
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual const wchar_t* GetText();                         // +0x3C
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void SetFlag(int flag, int on);                   // +0x7C
    virtual void SetCaption(const wchar_t* text);             // +0x80
    virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
    virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42();
    virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52();
    virtual void v53(); virtual void v54(IWindow_s0063_6320* p);         // +0xD8
    virtual void v55(IWindow_s0063_6320* p);                             // +0xDC
};
struct IControl {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03(); virtual void c04();
    virtual void c05(); virtual void c06(); virtual void c07(); virtual void c08(); virtual void c09();
    virtual void SetMode(int a, int b);                       // +0x28
};
struct cProfScope { void End(); };                            // 0x0067C420
cProfScope* __stdcall BeginProfScope(int a, int b);           // 0x0067CAC0
void EndModal(IWindow_s0063_6320* w, int a, int b);                      // 0x00809C50 (cdecl)
struct cSPPlayModeUI {
    char pad0[0xC];
    cAppModeEditorBase* mpEditor;       // +0x0C
    void* mpPlayMode;                   // +0x10
    cSPUILayout_s0063_6320 mLayout;                // +0x14
    cSPUILayout_s0063_6320 mCameraControlsLayout;  // +0x2C
    bool mbLayoutInit;                  // +0x44
    char pad45[0x64 - 0x45];
    IWindow_s0063_6320* mpMovieSavedDialog;        // +0x64

    IWindow_s0063_6320* FindPlayModeUIWindow(uint32_t id);               // 0x00634DC0
    void SetUIGroupVisible(uint32_t id, bool on);             // 0x00635760
    void EnablePhotoViewerButton(bool b);                     // 0x00636320
    void HideMovieSavedDialogCustom();                        // 0x006364A0
    bool DoMessageInternal(uint32_t a, void* msg);            // 0x00636560
    bool Shutdown();                                          // 0x006373E0
    void SetYTUsername(const eastl::string& s);               // 0x006374B0
    void SetYTPassword(const eastl::string& s);               // 0x00637510
    void GetEditorText(uint32_t id, eastl::string* out);      // 0x006377D0
    void GetYTUsername(eastl::string* out);                   // 0x00637800
    void GetYTPassword(eastl::string* out);                   // 0x00637830
    void ShowSendEmailDialog();                               // 0x00637860
    void SendVideoURLInfoToServer();                          // 0x00637C90
    void ResetSendEmailWindow();                              // 0x00635520
    void HideYouTubeLoginDialog();                            // 0x00636260
};
// ---- items of slice s00636320 end

// ---- items of slice s00636560 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IWindow_s0063_6560 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual uint32_t GetFlags();                              // +0x28
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void SetFlag(int flag, bool on);                  // +0x7C
};
static __forceinline void ToggleVisible(IWindow_s0063_6560* w, bool allowShow)
{
    if (w) {
        if (!(w->GetFlags() & 2))
            w->SetFlag(2, allowShow);
        else
            w->SetFlag(2, false);
    }
}
#define ToggleWindowVisible(w) ToggleVisible(w, true)
static __forceinline void HideWindow(IWindow_s0063_6560* w)
{
    if (w) {
        w->GetFlags();
        w->SetFlag(2, false);
    }
}
static __forceinline void EnableWindow(IWindow_s0063_6560* w, bool on)
{
    if (w) w->SetFlag(1, on);
}
struct IAudioSystem {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03(); virtual void a04();
    virtual void a05(); virtual void a06(); virtual void a07();
    virtual int GetState();                                   // +0x20
};
namespace EA {
namespace Audio {
 IAudioSystem* GetSystemAT();   // 0x00A206F0
}
}
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
namespace SP {
 IMessageServer* MessageServer();   // 0x0067DCC0
}
struct IPaletteObject {
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03(); virtual void p04();
    virtual void p05(); virtual void p06();
    virtual void SetVisible(bool b);                          // +0x1C
};
struct cSPEditorUI_s0063_6560 {
    IWindow_s0063_6560* FindWindowByID(uint32_t id);                     // 0x005DC310
    void DoSaveAndExit();                                     // 0x005DFB40
    void SetMode103();                                        // 0x005DF8D0
};
struct cAppModeEditorBase_s0063_6560 {
    uint32_t pad00[0x78 / 4];
    cSPEditorUI_s0063_6560* mpEditorUI;                                  // +0x78
    uint32_t pad7c[(0x358 - 0x7c) / 4];
    IPaletteObject* mpPaintPalette;                           // +0x358
    void ShowTutorial();                                      // 0x00572260
};
struct cPhotoQueue { uint32_t Count(); };                     // 0x00CEE370
struct cSPPlayModeSubModePhoto_s0063_6560 {
    uint32_t pad00[0x50 / 4];
    cPhotoQueue mQueue;                                       // +0x50
    cPhotoQueue* GetQueue() { return &mQueue; }
    bool IsPhotosWriting(bool b);                             // 0x0063EB90
    void FUN_0063ece0(int a);                                 // 0x0063ECE0
};
struct cSPPlayMode_s0063_6560 {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08();
    virtual void HandleCommand(uint32_t id);                  // +0x24
    uint32_t pad04[(0x1e8 - 4) / 4];
    cSPPlayModeSubModePhoto_s0063_6560 mPhotoMode;                       // +0x1E8
    cSPPlayModeSubModePhoto_s0063_6560* GetPhotoMode() { return &mPhotoMode; }

    void FUN_006284b0(int mode);                              // 0x006284B0
    void ToggleBaby(int which);                               // 0x0062C990
    void RunSkinPaintOnEditorModel(int a, int b);             // 0x0062C7E0
    void FUN_0062ba10(int a);                                 // 0x0062BA10
    void FUN_006288f0();                                      // 0x006288F0
    void FUN_006288d0(int a);                                 // 0x006288D0
};
struct cSPUILayout_s0063_6560 {
    uint32_t pad[0x18 / 4];
    bool IsVisible();                                         // 0x00810070
};
struct UIMessage {
    uint32_t pad00[2];
    uint32_t mType;                                           // +0x08
    int mCommandID;                                           // +0x0C
};
struct cSPPlayModeUI_s0063_6560 {
    uint32_t pad00[3];
    cAppModeEditorBase_s0063_6560* mpEditor;       // +0x0C
    cSPPlayMode_s0063_6560* mpPlayMode;            // +0x10
    cSPUILayout_s0063_6560 mLayout;                // +0x14
    cSPUILayout_s0063_6560 mCameraControlsLayout;  // +0x2C
    uint32_t pad44[(0x60 - 0x44) / 4];
    bool mbField60;                     // +0x60

    IWindow_s0063_6560* FindPlayModeUIWindow(uint32_t id);               // 0x00634DC0
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
// ---- items of slice s00636560 end

// ---- items of slice s006373e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IWindow_s0063_73e0;
struct IOther_s0063_73e0;
struct cSPEditorUI_s0063_73e0;
namespace eastl {
template <typename T> struct EmptyStr_s0063_73e0;
}
namespace eastl {
template <> struct EmptyStr_s0063_73e0<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
}
namespace eastl {
template <> struct EmptyStr_s0063_73e0<char>    { static char*    Get() { return gEmptyString8; } };
}
namespace eastl {
template <typename T>
struct allocator_s0063_73e0 {
    void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
template <typename T, typename Allocator = allocator_s0063_73e0<T> >
class basic_string_s0063_73e0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    basic_string_s0063_73e0() : mpBegin(EmptyStr_s0063_73e0<T>::Get()), mpEnd(EmptyStr_s0063_73e0<T>::Get()), mpCapacity(EmptyStr_s0063_73e0<T>::Get() + 1) {}
    ~basic_string_s0063_73e0() { DeallocateSelf(); }
    const T* c_str() const { return mpBegin; }
    int sprintf(const char* fmt, ...);   // 0x00472FE0
    int append_sprintf(const char* fmt, ...);   // 0x005F9450
    void clear() { if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; } }
    void DeallocateSelf() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin); }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
};
}
namespace eastl {
typedef basic_string_s0063_73e0<char> string_s0063_73e0;
}
namespace eastl {
typedef basic_string_s0063_73e0<wchar_t> string16_s0063_73e0;
}
namespace EA {
eastl::string16_s0063_73e0 ConvertToString16(const char* p, int length = -1);   // 0x0093C5A0
}
namespace EA {
eastl::string16_s0063_73e0 ConvertToString16(const eastl::string_s0063_73e0& s);           // 0x0093C6D0
}
struct cAppModeEditorBase_s0063_73e0 {
    char pad78[0x78];
    cSPEditorUI_s0063_73e0* mpEditorUI;        // +0x78
    char pad7c[0x358 - 0x7c];
    void* mPaintPaletteObject;      // +0x358
};
struct cSPEditorUI_s0063_73e0 {
    char pad[0x14];
    void EnableUIButton(uint32_t id, bool b);     // 0x005DC610
    IWindow_s0063_73e0* FindWindowByID(uint32_t id);         // 0x005DC310
};
struct cSPUILayout_s0063_73e0 {
    char pad[0x18];
    bool IsVisible();                                         // 0x00810070
    IWindow_s0063_73e0* FindWindowByID(uint32_t id, bool recurse);       // 0x008105B0
    void Shutdown(bool b);                                    // 0x00811AD0
};
struct cSPEditorNaming { void ResetParentWin(); };            // 0x005BFB70
struct IOther_s0063_73e0 {
    virtual void o00(); virtual void o01(); virtual void o02(); virtual void o03(); virtual void o04();
    virtual void o05(); virtual void o06(); virtual void o07(); virtual void o08(); virtual void o09();
    virtual void o10(); virtual void o11(); virtual void o12(); virtual void o13(); virtual void o14();
    virtual void o15(); virtual void o16(); virtual void o17(); virtual void o18(); virtual void o19();
    virtual void o20(); virtual void o21(); virtual void o22(); virtual void o23(); virtual void o24();
    virtual void o25(); virtual void o26(); virtual void o27(); virtual void o28(); virtual void o29();
    virtual void o30(); virtual void o31(); virtual void o32(); virtual void o33(); virtual void o34();
    virtual void o35(); virtual void o36(); virtual void o37(); virtual void o38(); virtual void o39();
    virtual void o40(); virtual void o41(); virtual void o42(); virtual void o43(); virtual void o44();
    virtual void o45(); virtual void o46(); virtual void o47(); virtual void o48(); virtual void o49();
    virtual void o50(); virtual void o51(); virtual void o52(); virtual void o53(); virtual void o54();
    virtual void Attach(IWindow_s0063_73e0* p);              // +0xDC
};
struct IWindow_s0063_73e0 {
    virtual void v00();
    virtual int Release();                                    // +0x04
    virtual void v02();
    virtual IControl* v03(uint32_t id);                       // +0x0C
    virtual IOther_s0063_73e0* GetOther();                               // +0x10
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual uint8_t v10();                                    // +0x28
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual const wchar_t* GetText();                         // +0x3C
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void SetFlag(int flag, int on);                   // +0x7C
    virtual void SetCaption(const wchar_t* text);             // +0x80
    virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
    virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42();
    virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52();
    virtual void v53(); virtual void v54(IWindow_s0063_73e0* p);         // +0xD8
    virtual void v55(IWindow_s0063_73e0* p);                             // +0xDC
};
void EndModal(IWindow_s0063_73e0* w, int a, int b);                      // 0x00809C50 (cdecl)
struct cSPPlayModeUI_s0063_73e0 {
    char pad0[0xC];
    cAppModeEditorBase_s0063_73e0* mpEditor;       // +0x0C
    void* mpPlayMode;                   // +0x10
    cSPUILayout_s0063_73e0 mLayout;                // +0x14
    cSPUILayout_s0063_73e0 mCameraControlsLayout;  // +0x2C
    bool mbLayoutInit;                  // +0x44
    char pad45[0x64 - 0x45];
    IWindow_s0063_73e0* mpMovieSavedDialog;        // +0x64

    IWindow_s0063_73e0* FindPlayModeUIWindow(uint32_t id);               // 0x00634DC0
    void SetUIGroupVisible(uint32_t id, bool on);             // 0x00635760
    void EnablePhotoViewerButton(bool b);                     // 0x00636320
    void HideMovieSavedDialogCustom();                        // 0x006364A0
    bool DoMessageInternal(uint32_t a, void* msg);            // 0x00636560
    bool Shutdown();                                          // 0x006373E0
    void SetYTUsername(const eastl::string_s0063_73e0& s);               // 0x006374B0
    void SetYTPassword(const eastl::string_s0063_73e0& s);               // 0x00637510
    void GetEditorText(uint32_t id, eastl::string_s0063_73e0* out);      // 0x006377D0
    void GetYTUsername(eastl::string_s0063_73e0* out);                   // 0x00637800
    void GetYTPassword(eastl::string_s0063_73e0* out);                   // 0x00637830
    void ShowSendEmailDialog();                               // 0x00637860
    void SendVideoURLInfoToServer();                          // 0x00637C90
    void ResetSendEmailWindow();                              // 0x00635520
    void HideYouTubeLoginDialog();                            // 0x00636260
};
// ---- items of slice s006373e0 end

// ---- items of slice s00637f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
class IWindow_s0063_7f80 {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual IWindow_s0063_7f80* Cast(uint32_t type);
    virtual IWindow_s0063_7f80* GetParent();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual uint32_t GetFlags();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual float* GetRealArea();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void SetShadeColor(uint32_t c);
    virtual void v24();
    virtual void SetLocation(float x, float y);
    virtual void v26();
    virtual void SetLayoutArea(const float* rect);
    virtual void SetLayoutLocation(float x, float y);
    virtual void SetLayoutSize(float w, float hgt);
    virtual void v30();
    virtual void SetFlag(int flag, bool v);
    virtual void SetCaption(const wchar_t* s);
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual int Invalidate();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void AddWindow(IWindow_s0063_7f80* w);
    virtual void RemoveWindow(IWindow_s0063_7f80* w);
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual IWindow_s0063_7f80* FindWindowByID(uint32_t id, bool recursive);
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void AddWinProc(void* p);
};
struct cString_s0063_7f80 {
    cString_s0063_7f80();                                                          // 0x006B5060
    void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* fallback);   // 0x006B54B0
    const wchar_t* c_str();                                             // 0x006B55C0
    ~cString_s0063_7f80();                                                         // 0x006B5240
    uint32_t pad[5];
};
namespace SPUIHelpers {
void AutoSizeWindowForText(IWindow_s0063_7f80* w, bool a, bool b);                 // 0x00806E40
}
namespace SPUIHelpers {
void BeginModal(IWindow_s0063_7f80* w, int a, int b);                              // 0x008099A0
}
struct cPaletteStub { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void SetEnabled(int a); };
namespace SP {
class cSPEditorUI_s0063_7f80 { public: IWindow_s0063_7f80* FindWindowByID(uint32_t id); };    // 0x005DC310
}
namespace SP {
class cAppModeEditorBase_s0063_7f80 {
public:
    char pad0[0x78]; cSPEditorUI_s0063_7f80* mpEditorUI;                           // +0x78
    char pad1[0x358 - 0x7c]; cPaletteStub* mpPaletteData;                    // +0x358
};
}
struct Rect4Union { float v[4]; void FUN_00634b60(const float* a, const float* b); };    // 0x00634B60 (thiscall on out)
namespace SP {
class cSPPlayModeUI_s0063_7f80 {
public:
    IWindow_s0063_7f80* FindPlayModeUIWindow(uint32_t id);                         // 0x00634DC0
    void LayoutYouTubeUploadButton();                                   // 0x00637F80
    void ShowMovieSavedDialogCustom();                                  // 0x00638430
    char pad0[0xc]; cAppModeEditorBase_s0063_7f80* mApp;                           // +0xc
    char pad1[0x64 - 0x10]; IWindow_s0063_7f80* mpDialog;                          // +0x64
};
}
// ---- items of slice s00637f80 end

// ---- items of slice s00634490 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gBtnFx0, gBtnFx1, gBtnFx2, gBtnFx3;     // 0x013f9328, 0x013f9324, 0x013ef53c, 0x013fe744
struct IRefCountU {
    virtual int AddRef();
    virtual int Release();
};
struct UIProc;
struct UIWin {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual struct UIProc* QueryProc(uint32_t id);
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual uint32_t GetID();
    virtual void s08();
    virtual void s09();
    virtual uint8_t GetFlags();
    virtual void s0b();
    virtual void s0c();
    virtual void s0d();
    virtual void s0e();
    virtual void s0f();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s1a();
    virtual void s1b();
    virtual void s1c();
    virtual void s1d();
    virtual void s1e();
    virtual void SetFlag(int flag, bool v);
    virtual void SetText(const wchar_t* text);
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s2a();
    virtual void s2b();
    virtual void s2c();
    virtual void s2d();
    virtual void s2e();
    virtual void s2f();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s3a();
    virtual void s3b();
    virtual UIWin* FindChild(uint32_t id, bool recurse);
    virtual void s3d();
    virtual void s3e();
    virtual void s3f();
    virtual void s40();
    virtual void SetTooltip(void* tip);
    virtual void RemoveTooltip(void* tip);
};
struct UIProc {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual UIWin* GetParent();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual uint32_t GetState();
    virtual void s09();
    virtual void SetFlags(uint32_t flags, bool v);
    virtual void s0b();
    virtual void s0c();
    virtual void SetState13(int a, int b);
};
struct UIObjVec {
    UIWin** mpBegin;
    UIWin** mpEnd;
};
struct cSPUILayout_s0063_4490 {
    uint32_t pad[6];
    cSPUILayout_s0063_4490();                                   // 0x00810000
    UIWin* FindWindowByID(uint32_t id, bool recurse);   // 0x008105b0
    UIObjVec* GetObjects();                          // 0x008100c0
};
struct cSPEditorNaming_s0063_4490 {
    void SetTagField(uint32_t v);                    // 0x005bfc90
};
struct cSPEditorUI_s0063_4490 {
    UIWin* FindWindowByID(uint32_t id);              // 0x005dc310
    void DoCommand(uint32_t cmd);                    // 0x005dfd00
    void EnableUIButton(uint32_t id, uint32_t v);    // 0x005dc610
    void Show();                                     // 0x005dd070
    void FUN_005de690(uint32_t a, uint32_t b);       // 0x005de690
};
struct FxController;
struct cAppMode {
    FxController* FUN_00572400();                    // 0x00572400
    uint32_t pad0[0x78 / 4];
    cSPEditorUI_s0063_4490* mEditorUI;                          // +0x78
    uint32_t pad1[(0x98 - 0x7c) / 4];
    IRefCountU* mObj98;                              // +0x98
    uint32_t pad2[(0x358 - 0x9c) / 4];
    cSPEditorNaming_s0063_4490* mNaming;                        // +0x358
};
struct StopwatchU {
    uint32_t pad[7];
    StopwatchU(int units, int start);                // 0x0093a560
};
struct IWinProcU {
    virtual void w0();
    virtual void w1();
};
struct RefCountBaseU {
    virtual void r0();
    int mRefCount;
    RefCountBaseU() : mRefCount(0) {}
};
struct cSPPlayModeUI_s0063_4490 : IWinProcU, RefCountBaseU {
    cAppMode* mApp;            // +0x0c
    void* mPlayMode;           // +0x10
    cSPUILayout_s0063_4490 mLayout;       // +0x14
    cSPUILayout_s0063_4490 mLayout2;      // +0x2c
    uint8_t mFlag44;           // +0x44
    uint8_t mFlag45;           // +0x45
    StopwatchU mTimer;         // +0x48
    uint32_t mField64;         // +0x64
    UIWin* mField68;           // +0x68

    cSPPlayModeUI_s0063_4490();
    void AttachWinProc();
    UIWin* FindPlayModeUIWindow(uint32_t id);  // 0x00634dc0 (cSPPlayModeUI::FindPlayModeUIWindow)
    UIWin* FindEditorUIWindow(uint32_t id);  // 0x00634e40 (cSPPlayModeUI::FindEditorUIWindow)
    int FUN_00634e50();
    uint8_t IsItemVisible(uint32_t id);
    void SetHighlight(uint32_t id, bool v);  // 0x00634e90 (cSPPlayModeUI::SetHighlight)
    void SetSelected(uint32_t id, bool v);  // 0x00634ec0 (cSPPlayModeUI::SetSelected)
    void SetEnabled(uint32_t id, bool v);  // 0x00634ef0 (cSPPlayModeUI::SetEnabled)
    void SetEditorUIEnabled(uint32_t id, bool v);  // 0x00634f20 (cSPPlayModeUI::SetEditorUIEnabled)
    void SetHideOut(uint32_t id, bool v);
    void SetEditorText(uint32_t id, const wchar_t** text);  // 0x00635010 (cSPPlayModeUI::SetEditorText)
    void ShowToolTip(uint32_t id, uint32_t a, uint32_t b, struct cSPUITooltipWinProc_s0063_4490* existing, float* pos);
    void ShowEditorUIToolTip(uint32_t id, uint32_t a, uint32_t b, struct cSPUITooltipWinProc_s0063_4490* existing, float* pos);
    void RemoveTooltip(uint32_t id, void* tip);  // 0x00635290 (cSPPlayModeUI::RemoveTooltip)
    void DoCommand103();
    void DoCommand102();
    void SetPrompt(uint32_t v);
    void FUN_00635350(uint32_t a, uint32_t b);
    void ShowEditor();
    void ToggleNameAndDescribe(bool v);  // 0x00635390 (cSPPlayModeUI::ToggleNameAndDescribe)
    void SetTagField(uint32_t v);
    void SetSendEmailDialogVisibility(bool v);  // 0x00635400 (cSPPlayModeUI::SetSendEmailDialogVisibility)
    void UpdateButtonEffects(int unused);
};
struct FxController {
    void SetScaleA(float v);    // 0x00625270
    void SetScaleB(float v);    // 0x006252a0
};
struct UIHelperObj { void FUN_0067c420(); };
UIHelperObj* __stdcall FUN_0067cac0(int a, int b);
struct WinMgrHandler { void FUN_00802a30(int v); };
struct WinMgrOwner { uint32_t pad[0x2d8 / 4]; WinMgrHandler* mHandler; };
struct WinMgr { virtual void w0(); virtual void* GetCurrent(); };
WinMgr* WindowManager();
void BeginModal(UIWin* w, int a, int b);
void EndModal(UIWin* w, int a, int b);
struct cSPUITooltipWinProc_s0063_4490 : IRefCountU {
    uint32_t pad[0x68 / 4 - 1];
    cSPUITooltipWinProc_s0063_4490(const wchar_t* cls, uint32_t id, const wchar_t* text);   // 0x00835e30
    void SetText(const wchar_t* t);                              // 0x00835ed0
};
// ---- items of slice s00634490 end

// ---- items of slice s00634490b begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gTipDefault0, gTipDefault1;             // 0x01486110, 0x013f6ad8
void* operator new(size_t, const char*, int, int, int, int);
inline void* operator new(size_t, void* p) { return p; }
struct cSPUILayout_s0063_4490_b {
    uint32_t pad[6];
    cSPUILayout_s0063_4490_b();                                   // 0x00810000
    UIWin* FindWindowByID(uint32_t id, bool recurse);   // 0x008105b0
    UIObjVec* GetObjects();                          // 0x008100c0
};
struct cSPEditorNaming_s0063_4490_b {
    void SetTagField(uint32_t v);                    // 0x005bfc90
};
struct cSPEditorUI_s0063_4490_b {
    UIWin* FindWindowByID(uint32_t id);              // 0x005dc310
    void DoCommand(uint32_t cmd);                    // 0x005dfd00
    void EnableUIButton(uint32_t id, uint32_t v);    // 0x005dc610
    void Show();                                     // 0x005dd070
    void FUN_005de690(uint32_t a, uint32_t b);       // 0x005de690
};
struct cAppMode_s0063_4490_b {
    FxController* FUN_00572400();                    // 0x00572400
    uint32_t pad0[0x78 / 4];
    cSPEditorUI_s0063_4490_b* mEditorUI;                          // +0x78
    uint32_t pad1[(0x98 - 0x7c) / 4];
    IRefCountU* mObj98;                              // +0x98
    uint32_t pad2[(0x358 - 0x9c) / 4];
    cSPEditorNaming_s0063_4490_b* mNaming;                        // +0x358
};
struct cSPPlayModeUI_s0063_4490_b : IWinProcU, RefCountBaseU {
    cAppMode_s0063_4490_b* mApp;            // +0x0c
    void* mPlayMode;           // +0x10
    cSPUILayout_s0063_4490_b mLayout;       // +0x14
    cSPUILayout_s0063_4490_b mLayout2;      // +0x2c
    uint8_t mFlag44;           // +0x44
    uint8_t mFlag45;           // +0x45
    StopwatchU mTimer;         // +0x48
    uint32_t mField64;         // +0x64
    UIWin* mField68;           // +0x68

    cSPPlayModeUI_s0063_4490_b();
    void AttachWinProc();  // 0x00634b10 (cSPPlayModeUI::AttachWinProc)
    UIWin* FindPlayModeUIWindow(uint32_t id);  // 0x00634dc0 (cSPPlayModeUI::FindPlayModeUIWindow)
    UIWin* FindEditorUIWindow(uint32_t id);  // 0x00634e40 (cSPPlayModeUI::FindEditorUIWindow)
    int FUN_00634e50();  // 0x00634e50 (cSPPlayModeUI::FUN_00634e50)
    uint8_t IsItemVisible(uint32_t id);  // 0x00634e60 (cSPPlayModeUI::IsItemVisible)
    void SetHighlight(uint32_t id, bool v);  // 0x00634e90 (cSPPlayModeUI::SetHighlight)
    void SetSelected(uint32_t id, bool v);  // 0x00634ec0 (cSPPlayModeUI::SetSelected)
    void SetEnabled(uint32_t id, bool v);  // 0x00634ef0 (cSPPlayModeUI::SetEnabled)
    void SetEditorUIEnabled(uint32_t id, bool v);  // 0x00634f20 (cSPPlayModeUI::SetEditorUIEnabled)
    void SetHideOut(uint32_t id, bool v);  // 0x00634f50 (cSPPlayModeUI::SetHideOut)
    void SetEditorText(uint32_t id, const wchar_t** text);  // 0x00635010 (cSPPlayModeUI::SetEditorText)
    void ShowToolTip(uint32_t id, uint32_t a, uint32_t b, struct cSPUITooltipWinProc_s0063_4490_b* existing, float* pos);
    void ShowEditorUIToolTip(uint32_t id, uint32_t a, uint32_t b, struct cSPUITooltipWinProc_s0063_4490_b* existing, float* pos);
    void RemoveTooltip(uint32_t id, void* tip);  // 0x00635290 (cSPPlayModeUI::RemoveTooltip)
    void DoCommand103();  // 0x006352d0 (cSPPlayModeUI::DoCommand103)
    void DoCommand102();  // 0x006352f0 (cSPPlayModeUI::DoCommand102)
    void SetPrompt(uint32_t v);  // 0x00635310 (cSPPlayModeUI::SetPrompt)
    void FUN_00635350(uint32_t a, uint32_t b);  // 0x00635350 (cSPPlayModeUI::FUN_00635350)
    void ShowEditor();  // 0x00635380 (cSPPlayModeUI::ShowEditor)
    void ToggleNameAndDescribe(bool v);  // 0x00635390 (cSPPlayModeUI::ToggleNameAndDescribe)
    void SetTagField(uint32_t v);  // 0x006353e0 (cSPPlayModeUI::SetTagField)
    void SetSendEmailDialogVisibility(bool v);  // 0x00635400 (cSPPlayModeUI::SetSendEmailDialogVisibility)
    void UpdateButtonEffects(int unused);  // 0x00634c80 (cSPPlayModeUI::UpdateButtonEffects)
};
struct cString {
    uint32_t pad[5];
    cString();                                                   // 0x006b5060
    ~cString();                                                  // 0x006b5240
    void Load(uint32_t id, uint32_t a, uint32_t b);              // 0x006b54b0
    const wchar_t* Format(float* pos, int a, const wchar_t* fmt, int b);   // 0x006b55c0
    const wchar_t* Format2(int len, int flag);                   // 0x006b55c0
};
struct cSPUITooltipWinProc_s0063_4490_b : IRefCountU {
    uint32_t pad[0x68 / 4 - 1];
    cSPUITooltipWinProc_s0063_4490_b(const wchar_t* cls, uint32_t id, const wchar_t* text);   // 0x00835e30
    void SetText(const wchar_t* t);                              // 0x00835ed0
};
void* FUN_009512c0();
void* FUN_009512d0(size_t size, int align, const char* name, void* alloc);
struct RectF {
    float x0, y0, x1, y1;
    bool Intersect(const RectF& a, const RectF& b);
};
// ---- items of slice s00634490b end

// @ 0x00634b10
void cSPPlayModeUI_s0063_4490::AttachWinProc()
{
    UIWin* w = mLayout.FindWindowByID(0x5b5ef50, true);
    if (w)
        w->SetTooltip(this);
    w = mLayout.FindWindowByID(0x5650568, true);
    if (w)
        w->SetTooltip(this);
}


// @ 0x00634b60
bool RectF::Intersect(const RectF& a, const RectF& b)
{
    if (b.x0 >= a.x1 || a.x0 >= b.x1 || b.y0 >= a.y1 || a.y0 >= b.y1) {
        y0 = 0.0f;
        x1 = 0.0f;
        x0 = 0.0f;
        y1 = 0.0f;
        return false;
    }
    x0 = (a.x0 > b.x0) ? a.x0 : b.x0;
    y0 = (a.y0 > b.y0) ? a.y0 : b.y0;
    x1 = (a.x1 < b.x1) ? a.x1 : b.x1;
    y1 = (a.y1 < b.y1) ? a.y1 : b.y1;
    return true;
}

// @ 0x00634c10
cSPPlayModeUI_s0063_4490::cSPPlayModeUI_s0063_4490()
: mLayout(), mLayout2(), mFlag44(0), mFlag45(0), mTimer(5, 0)
{
    mField64 = 0;
    mField68 = 0;
}


// @ 0x00634c80
void cSPPlayModeUI_s0063_4490::UpdateButtonEffects(int unused)
{
    UIWin* w = mLayout2.FindWindowByID(0x4cab570, true);
    if (w) {
        UIProc* p = w->QueryProc(0x8ed27e7a);
        if (p->GetState() & 2) {
            FxController* fx = mApp->FUN_00572400();
            if (fx)
                fx->SetScaleA(gBtnFx0);
        }
    }
    w = mLayout2.FindWindowByID(0x4cab571, true);
    if (w) {
        UIProc* p = w->QueryProc(0x8ed27e7a);
        if (p->GetState() & 2) {
            FxController* fx = mApp->FUN_00572400();
            if (fx)
                fx->SetScaleA(gBtnFx1);
        }
    }
    w = mLayout2.FindWindowByID(0x4cab56f, true);
    if (w) {
        UIProc* p = w->QueryProc(0x8ed27e7a);
        if (p->GetState() & 2) {
            FxController* fx = mApp->FUN_00572400();
            if (fx)
                fx->SetScaleB(gBtnFx2);
        }
    }
    w = mLayout2.FindWindowByID(0x4cab56e, true);
    if (w) {
        UIProc* p = w->QueryProc(0x8ed27e7a);
        if (p->GetState() & 2) {
            FxController* fx = mApp->FUN_00572400();
            if (fx)
                fx->SetScaleB(gBtnFx3);
        }
    }
}


// @ 0x00634dc0
UIWin* cSPPlayModeUI_s0063_4490::FindPlayModeUIWindow(uint32_t id)
{
    UIObjVec* objs = mLayout.GetObjects();
    int n = (int)(objs->mpEnd - objs->mpBegin);
    for (int i = 0; i < n; ++i) {
        UIWin* obj = objs->mpBegin[i];
        if (obj) {
            UIWin* win = (UIWin*)obj->QueryProc(0xeeee8218);
            if (win) {
                if (win->GetID() == id)
                    return win;
                UIWin* r = win->FindChild(id, true);
                if (r)
                    return r;
            }
        }
    }
    return 0;
}


// @ 0x00634e40
UIWin* cSPPlayModeUI_s0063_4490::FindEditorUIWindow(uint32_t id)
{
    cSPEditorUI_s0063_4490* ed = mApp->mEditorUI;
    return ed->FindWindowByID(id);
}


// @ 0x00634e50
int cSPPlayModeUI_s0063_4490::FUN_00634e50()
{
    return mApp->mObj98->Release();
}


// @ 0x00634e60
uint8_t cSPPlayModeUI_s0063_4490::IsItemVisible(uint32_t id)
{
    uint8_t result = 0;
    UIWin* w = FindPlayModeUIWindow(id);
    if (w) {
        result = w->GetFlags();
        result &= 1;
    }
    return result;
}


// @ 0x00634e90
void cSPPlayModeUI_s0063_4490::SetHighlight(uint32_t id, bool v)
{
    UIWin* w = FindPlayModeUIWindow(id);
    if (w)
        w->QueryProc(0x8ed27e7a)->SetFlags(8, v);
}


// @ 0x00634ec0
void cSPPlayModeUI_s0063_4490::SetSelected(uint32_t id, bool v)
{
    UIWin* w = FindPlayModeUIWindow(id);
    if (w)
        w->QueryProc(0x8ed27e7a)->SetFlags(4, v);
}


// @ 0x00634ef0
void cSPPlayModeUI_s0063_4490::SetEnabled(uint32_t id, bool v)
{
    UIWin* w = FindPlayModeUIWindow(id);
    if (w)
        w->SetFlag(2, v);
}


// @ 0x00634f20
void cSPPlayModeUI_s0063_4490::SetEditorUIEnabled(uint32_t id, bool v)
{
    cSPEditorUI_s0063_4490* ed = mApp->mEditorUI;
    UIWin* w = ed->FindWindowByID(id);
    if (w)
        w->SetFlag(2, v);
}


// @ 0x00634f50
void cSPPlayModeUI_s0063_4490::SetHideOut(uint32_t id, bool v)
{
    UIWin* w;
    switch (id) {
    case 0x44594d8:
        w = FindPlayModeUIWindow(0x5ac71d9);
        if (w)
            w->SetFlag(1, v);
        break;
    case 0x3e831e4:
        w = FindPlayModeUIWindow(0x5ac71d8);
        if (w)
            w->SetFlag(1, v);
        break;
    case 0x445a468:
        w = FindPlayModeUIWindow(0x5ac71da);
        if (w)
            w->SetFlag(1, v);
        break;
    case 0x445ea18:
        w = FindPlayModeUIWindow(0x5ac71db);
        if (w)
            w->SetFlag(2, !v);
        break;
    }
}


// @ 0x00635010
void cSPPlayModeUI_s0063_4490::SetEditorText(uint32_t id, const wchar_t** text)
{
    cSPEditorUI_s0063_4490* ed = mApp->mEditorUI;
    UIWin* w = ed->FindWindowByID(id);
    w->SetText(*text);
}


// @ 0x00635040
void cSPPlayModeUI_s0063_4490_b::ShowToolTip(uint32_t id, uint32_t a2, uint32_t a3, cSPUITooltipWinProc_s0063_4490_b* existing, float* pos)
{
    float defaults[2];
    defaults[0] = gTipDefault0;
    defaults[1] = gTipDefault1;
    UIWin* win = FindPlayModeUIWindow(id);
    if (win) {
        cString str;
        str.Load(0x7518573e, a2, a3);
        UIProc* proc = win->QueryProc(0x8ed27e7a);
        if (!pos)
            pos = defaults;
        cSPUITooltipWinProc_s0063_4490_b* tip = existing;
        cSPUITooltipWinProc_s0063_4490_b* result = 0;
        if (!tip) {
            void* mem = FUN_009512d0(0x68, 4, "UI/Tooltip", FUN_009512c0());
            if (mem) {
                tip = new (mem) cSPUITooltipWinProc_s0063_4490_b(L"Tooltips", 0x3754e6c, str.Format(pos, 0, (const wchar_t*)0x13fe714, 0));
                if (tip) {
                    tip->AddRef();
                    result = tip;
                }
            }
        } else {
            tip->SetText(str.Format2(-1, 1));
            tip->AddRef();
            result = tip;
        }
        proc->GetParent()->SetTooltip(result);
        if (result)
            result->Release();
    }
}

// @ 0x00635160
void cSPPlayModeUI_s0063_4490_b::ShowEditorUIToolTip(uint32_t id, uint32_t a2, uint32_t a3, cSPUITooltipWinProc_s0063_4490_b* existing, float* pos)
{
    float defaults[2];
    defaults[0] = gTipDefault0;
    defaults[1] = gTipDefault1;
    cSPEditorUI_s0063_4490_b* ed = mApp->mEditorUI;
    UIWin* win = ed->FindWindowByID(id);
    if (win) {
        cString str;
        str.Load(0x7518573e, a2, a3);
        UIProc* proc = win->QueryProc(0x8ed27e7a);
        if (!pos)
            pos = defaults;
        cSPUITooltipWinProc_s0063_4490_b* tip = existing;
        cSPUITooltipWinProc_s0063_4490_b* result = 0;
        if (!tip) {
            void* mem = FUN_009512d0(0x68, 4, "UI/Tooltip", FUN_009512c0());
            if (mem) {
                tip = new (mem) cSPUITooltipWinProc_s0063_4490_b(L"Tooltips", 0x3754e6c, str.Format(pos, 0, (const wchar_t*)0x13fe714, 0));
                if (tip) {
                    tip->AddRef();
                    result = tip;
                }
            }
        } else {
            tip->SetText(str.Format2(-1, 1));
            tip->AddRef();
            result = tip;
        }
        proc->GetParent()->SetTooltip(result);
        if (result)
            result->Release();
    }
}

// @ 0x00635290
void cSPPlayModeUI_s0063_4490::RemoveTooltip(uint32_t id, void* tip)
{
    if (tip) {
        UIWin* w = FindPlayModeUIWindow(id);
        if (w)
            w->QueryProc(0x8ed27e7a)->GetParent()->RemoveTooltip(tip);
    }
}


// @ 0x006352d0
void cSPPlayModeUI_s0063_4490::DoCommand103()
{
    mApp->mEditorUI->DoCommand(0x103);
}


// @ 0x006352f0
void cSPPlayModeUI_s0063_4490::DoCommand102()
{
    mApp->mEditorUI->DoCommand(0x102);
}


// @ 0x00635310
void cSPPlayModeUI_s0063_4490::SetPrompt(uint32_t v)
{
    UIWin* w = FindPlayModeUIWindow(0x5665f58);
    if (!w)
        w = mField68;
    if (w) {
        UIProc* p = w->QueryProc(0x8ed27e7a);
        if (p)
            p->SetState13(4, v);
    }
}


// @ 0x00635350
void cSPPlayModeUI_s0063_4490::FUN_00635350(uint32_t a, uint32_t b)
{
    mApp->mEditorUI->FUN_005de690(a, b);
    mApp->mEditorUI->EnableUIButton(0x58b74e8, a);
}


// @ 0x00635380
void cSPPlayModeUI_s0063_4490::ShowEditor()
{
    mApp->mEditorUI->Show();
}


// @ 0x00635390
void cSPPlayModeUI_s0063_4490::ToggleNameAndDescribe(bool v)
{
    UIWin* w = mApp->mEditorUI->FindWindowByID(0x5a73030);
    if (w) {
        if (!(w->GetFlags() & 2) && !v)
            w->SetFlag(2, true);
        else
            w->SetFlag(2, false);
    }
}


// @ 0x006353e0
void cSPPlayModeUI_s0063_4490::SetTagField(uint32_t v)
{
    cSPEditorNaming_s0063_4490* n = mApp->mNaming;
    if (n)
        n->SetTagField(v);
}


// @ 0x00635400
void cSPPlayModeUI_s0063_4490::SetSendEmailDialogVisibility(bool v)
{
    cSPEditorUI_s0063_4490* ed = mApp->mEditorUI;
    ed->FindWindowByID(0x5b9cdb0)->SetFlag(1, v);
    UIWin* w = mApp->mEditorUI->FindWindowByID(0x3f67620);
    if (v) {
        FUN_0067cac0(0, 1)->FUN_0067c420();
        BeginModal(w, 0, 0);
        void* p = WindowManager()->GetCurrent();
        WinMgrOwner* o = p ? (WinMgrOwner*)((char*)p - 4) : 0;
        o->mHandler->FUN_00802a30(0);
    } else {
        FUN_0067cac0(1, 1)->FUN_0067c420();
        EndModal(w, 0, 0);
    }
}


// @ 0x006354c0
void SP::cSPPlayModeUI_s0063_54c0::SetUpSendEmailWindow()
{
    IWindow* w = FindPlayModeUIWindow(0x3f67620);
    if (w) w->AddRef();
    w->GetParent()->RemoveWindow(w);
    mApp->mpEditorUI->FindWindowByID(-1)->AddWindow(w);
    w->Release();
}








// @ 0x00635520
void SP::cSPPlayModeUI_s0063_54c0::ResetSendEmailWindow()
{
    IWindow* w = mApp->mpEditorUI->FindWindowByID(0x3f67620);
    if (w) w->AddRef();
    w->GetParent()->RemoveWindow(w);
    FindPlayModeUIWindow(-1)->AddWindow(w);
    w->Release();
}








// @ 0x00635580
void SP::cSPPlayModeUI_s0063_54c0::SetEnableNewCreatureButton(bool b)
{
    SET_ENABLE_BODY(0x4766ff0, )
}








// @ 0x00635600
void SP::cSPPlayModeUI_s0063_54c0::SetEnableTakePictureButton(bool b)
{
    SET_ENABLE_BODY(0x3a8ede4, SPUIHelpers::UpdateMouseFocus(true);)
}








// @ 0x00635680
void SP::cSPPlayModeUI_s0063_54c0::SetEnableRecordMovieButton(bool b)
{
    SET_ENABLE_BODY(0x3fc1740, )
}








// @ 0x00635760
void SP::cSPPlayModeUI_s0063_54c0::SetUIGroupVisible(uint32_t id, bool b)
{
    IWindow* w = FindPlayModeUIWindow(id);
    if (w) w->SetFlag(1, b);
}








// @ 0x00635790
void SP::cSPPlayModeUI_s0063_54c0::SetEditorUIGroupVisible(uint32_t id, bool b)
{
    SP::cSPEditorUI_s0063_54c0* ui = mApp->mpEditorUI;
    IWindow* w = ui->FindWindowByID(id);
    if (w) w->SetFlag(1, b);
}








// @ 0x006357c0
void SP::cSPPlayModeUI_s0063_54c0::ToggleUIGroup(uint32_t id, bool b)
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
void SP::cSPPlayModeUI_s0063_54c0::SetCheckButtonSelected(uint32_t id, bool b)
{
    IWindow* w = FindPlayModeUIWindow(id);
    IButton* btn = w ? (IButton*)w->Cast(0x8ed27e7a) : 0;
    btn->SetStateFlag(4, b);
}








// @ 0x00635850
bool SP::cSPPlayModeUI_s0063_54c0::IsCheckButtonSelected(uint32_t id)
{
    IWindow* w = FindPlayModeUIWindow(id);
    IButton* btn = w ? (IButton*)w->Cast(0x8ed27e7a) : 0;
    uint8_t f = btn->GetButtonStateFlags();
    f >>= 2;
    f &= 1;
    return f;
}








// @ 0x00635890
bool SP::cSPPlayModeUI_s0063_54c0::IsUIGroupEnabled(uint32_t id)
{
    IWindow* w = FindPlayModeUIWindow(id);
    if (w && (w->GetFlags() & 2))
        return true;
    return false;
}








// @ 0x006358c0
bool SP::cSPPlayModeUI_s0063_54c0::Init(cAppModeEditorBase_s0063_54c0* app, cSPPlayMode_s0063_54c0* pm)
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
            cSPUILayout_s0063_54c0* cl = &mCameraControlsLayout;
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








// @ 0x00635dc0
void SP::cSPPlayModeUI_s0063_54c0::SetTabIndentOff(uint32_t id)
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








// @ 0x00635e80
void SP::cSPPlayModeUI_s0063_54c0::SetTabIndentOn()
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








// @ 0x00635f00
void SP::cSPPlayModeUI_s0063_54c0::SetAnimButtonsEnabled(bool b)
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








// @ 0x00635ff0
void SP::cSPPlayModeUI_s0063_54c0::SetExpansionAnimButtonsEnabled(bool b)
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








// @ 0x006360e0
void SP::cSPPlayModeUI_s0063_54c0::ShowYouTubeLoginDialog()
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
void SP::cSPPlayModeUI_s0063_54c0::HideYouTubeLoginDialog()
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







// @ 0x00636320
void cSPPlayModeUI::EnablePhotoViewerButton(bool b)
{
    mpEditor->mpEditorUI->EnableUIButton(0x445ea50, b);

    IWindow_s0063_6320* w = FindPlayModeUIWindow(0x445ea18);
    if (w && (w->v10() & 2)) {
        w = FindPlayModeUIWindow(0x5ac71db);
        if (w)
            w->SetFlag(2, 1);

        w = FindPlayModeUIWindow(0x445ea50);
        if (w)
            w->v03(0x8ed27e7a)->SetMode(4, 0);

        w = FindPlayModeUIWindow(0x4463e78);
        if (w)
            w->SetFlag(1, 0);

        w = mpEditor->mpEditorUI->FindWindowByID(0x447c040);
        if (w)
            w->SetFlag(1, 0);

        w = mpEditor->mpEditorUI->FindWindowByID(0x447c4e8);
        if (w)
            w->SetFlag(1, 0);

        w = FindPlayModeUIWindow(0x40eb500);
        if (w)
            w->SetFlag(1, 0);

        w = FindPlayModeUIWindow(0x40eb518);
        if (w)
            w->SetFlag(1, 0);

        w = FindPlayModeUIWindow(0x40eb7e8);
        if (w)
            w->SetFlag(1, 0);

        w = FindPlayModeUIWindow(0x40eb7f8);
        if (w)
            w->SetFlag(1, 0);

        w = FindPlayModeUIWindow(0x40eb818);
        if (w)
            w->SetFlag(1, 0);
    }
}







// @ 0x006364a0
void cSPPlayModeUI::HideMovieSavedDialogCustom()
{
    BeginProfScope(1, 1)->End();

    if (mpMovieSavedDialog)
        EndModal(mpMovieSavedDialog, 0, 0);

    IWindow_s0063_6320* w = FindPlayModeUIWindow(0x5b60540);
    if (w && mpMovieSavedDialog) {
        IOther* o = mpMovieSavedDialog->GetOther();
        o->Attach(mpMovieSavedDialog);
        w->v54(mpMovieSavedDialog);
    }

    if (mpMovieSavedDialog) {
        IWindow_s0063_6320* old = mpMovieSavedDialog;
        mpMovieSavedDialog = 0;
        old->Release();
    }

    w = FindPlayModeUIWindow(0x5b5ef50);
    if (w)
        w->SetFlag(1, 0);

    w = FindPlayModeUIWindow(0x5b60540);
    if (w)
        w->SetFlag(1, 0);
}






// @ 0x00636560
bool cSPPlayModeUI_s0063_6560::DoMessageInternal(uint32_t a, UIMessage* msg)
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
            IWindow_s0063_6560* w = FindPlayModeUIWindow(0x5ac71db);
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
            IWindow_s0063_6560* w = FindPlayModeUIWindow(0x5ac71db);
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




// @ 0x006373e0
bool cSPPlayModeUI_s0063_73e0::Shutdown()
{
    if (mpEditor && mpEditor->mPaintPaletteObject)
        ((cSPEditorNaming*)mpEditor->mPaintPaletteObject)->ResetParentWin();

    mCameraControlsLayout.Shutdown(true);

    IWindow_s0063_73e0* w = mpEditor->mpEditorUI->FindWindowByID(0x4816f20);
    w->v55(mLayout.FindWindowByID(0xffffffff, true));

    w = mpEditor->mpEditorUI->FindWindowByID(0x5b9cdb0);
    w->SetFlag(1, 0);

    w = mpEditor->mpEditorUI->FindWindowByID(0x3f67620);
    BeginProfScope(1, 1)->End();
    EndModal(w, 0, 0);

    ResetSendEmailWindow();
    HideMovieSavedDialogCustom();
    HideYouTubeLoginDialog();

    mLayout.Shutdown(true);
    mbLayoutInit = false;
    return true;
}




// @ 0x006374b0
void cSPPlayModeUI_s0063_73e0::SetYTUsername(const eastl::string_s0063_73e0& s)
{
    eastl::string16_s0063_73e0 w = EA::ConvertToString16(s);
    const wchar_t* p = w.c_str();
    IWindow_s0063_73e0* win = FindPlayModeUIWindow(0x5650498);
    win->SetCaption(p);
}




// @ 0x00637510
void cSPPlayModeUI_s0063_73e0::SetYTPassword(const eastl::string_s0063_73e0& s)
{
    eastl::string16_s0063_73e0 w = EA::ConvertToString16(s);
    const wchar_t* p = w.c_str();
    IWindow_s0063_73e0* win = FindPlayModeUIWindow(0x5650500);
    win->SetCaption(p);
}




// @ 0x006375e0
char FindParentDir2(int a, int b, int c)
{
    (void)a; (void)b; (void)c;
    return 0;
}




// @ 0x006377d0
void cSPPlayModeUI_s0063_73e0::GetEditorText(uint32_t id, eastl::string_s0063_73e0* out)
{
    cSPEditorUI_s0063_73e0* ui = mpEditor->mpEditorUI;
    IWindow_s0063_73e0* w = ui->FindWindowByID(id);
    out->sprintf("%ls", w->GetText());
}




// @ 0x00637800
void cSPPlayModeUI_s0063_73e0::GetYTUsername(eastl::string_s0063_73e0* out)
{
    IWindow_s0063_73e0* w = FindPlayModeUIWindow(0x5650498);
    out->sprintf("%ls", w->GetText());
}




// @ 0x00637830
void cSPPlayModeUI_s0063_73e0::GetYTPassword(eastl::string_s0063_73e0* out)
{
    IWindow_s0063_73e0* w = FindPlayModeUIWindow(0x5650500);
    out->sprintf("%ls", w->GetText());
}




// @ 0x00637860
void SP::cSPPlayModeUI::Show()
{
}




// @ 0x00637c90
void cSPPlayModeUI_s0063_73e0::SendVideoURLInfoToServer()
{
}



// @ 0x00638430
void SP::cSPPlayModeUI_s0063_7f80::ShowMovieSavedDialogCustom()
{
    mApp->mpPaletteData->SetEnabled(0);   // vcall +0x1c
    IWindow_s0063_7f80* w = mApp->mpEditorUI->FindWindowByID(0x5a73030);
    if (w) { w->GetFlags(); w->SetFlag(2, false); }
    GetYTMgr()->SetMode(false, true);
    cString_s0063_7f80 str;
    str.Load(0x7518573e, 0x54c1e63, L"*Movie Saved*");
    IWindow_s0063_7f80* c = FindPlayModeUIWindow(0x5b5f5c8);
    c->SetCaption(str.c_str());
    str.Load(0x7518573e, 0x5b5fd1e, L"*Upload to YouTube*");
    c = FindPlayModeUIWindow(0x5b5f608);
    c->SetCaption(str.c_str());
    w = FindPlayModeUIWindow(0x5b5ef50);
    if (w) w->SetFlag(1, true);
    w = FindPlayModeUIWindow(0x5b60540);
    if (w) w->SetFlag(1, true);
    float extra = 0.0f;
    IWindow_s0063_7f80* w1 = FindPlayModeUIWindow(0x5b5ef51);
    if (w1) {
        SPUIHelpers::AutoSizeWindowForText(w1, true, false);
        IWindow_s0063_7f80* w2 = FindPlayModeUIWindow(0x5b5ef52);
        if (w2) {
            SPUIHelpers::AutoSizeWindowForText(w2, false, false);
            float* r2 = w2->GetRealArea();
            float width2 = r2[2] - r2[0];
            float* r1 = w1->GetRealArea();
            float newX = r1[0] - width2;
            w2->SetLayoutLocation(newX, r2[1]);
            IWindow_s0063_7f80* w3 = FindPlayModeUIWindow(0x5b5ef53);
            if (w3) {
                SPUIHelpers::AutoSizeWindowForText(w3, false, false);
                Rect4Union u;
                u.FUN_00634b60(w2->GetRealArea(), w3->GetRealArea());
                extra = u.v[0] - width2;   // approximate (see partial.txt)
            }
        }
    }
    LayoutYouTubeUploadButton();
    IWindow_s0063_7f80* panel = FindPlayModeUIWindow(0x5b5ef50);
    if (panel && extra > 0.0f) {
        float* r = panel->GetRealArea();
        panel->SetLayoutSize((r[2] - r[0]) + extra, r[3] - r[1]);
    }
    if (!mpDialog) {
        IWindow_s0063_7f80* d = FindPlayModeUIWindow(0x5b5ef50);
        IWindow_s0063_7f80* old = mpDialog;
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
