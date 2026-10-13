// src/game/SPEditors/SPSubModeMovie.cpp -- migrated from slice(s) s0063ba50, s0063aa90 by tools/migrate/rewrite.py
// Object file: SPEditors/SPSubModeMovie.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPlayModeSubModeMovie.h"
#include "EA/Stopwatch.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cSPPlayMode.h"
#include "SP/cSPPlayModeSubModeAction.h"
#include "SP/cSPPlayModeSubModeBase.h"
#include "SP/cSPPlayModeSubModeDance.h"
#include "SP/cSPPlayModeUI.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "SP/cEditorYouTubeAuthenticationMessage.h"
#include "SP/cEditorYouTubeVideoUploadMessage.h"
#include "cSPVector4.h"
#include <string.h>
#include <stdio.h>

// unnamed retail callees and globals (address in the comment)
extern char g15247b0[], g15247bc[], g15247c8[], g15247d4[], g15247f8[], g1524804[], g152481c[];
extern char gDefaultSaveData[];                                         // 0x013EC468

// ---- items of slice s0063aa90 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct cString {
    cString();                                                          // 0x006B5060
    void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* fallback);   // 0x006B54B0
    const wchar_t* c_str();                                             // 0x006B55C0
    ~cString();                                                         // 0x006B5240
    uint32_t pad[5];
};
class cSPUILayout_s0063_aa90 {
public:
    ~cSPUILayout_s0063_aa90();                                                     // 0x00811FE0
    bool Init(const uint32_t* key, bool a, uint32_t b);                 // 0x008120D0
    IWindow* FindWindowByID(uint32_t id, bool recursive);               // 0x008105B0
    void Shutdown(bool b);                                              // 0x00811AD0
    uint32_t pad[6];
};
struct cYTMgr { void SetMode(bool a, bool b); };                        // 0x0067C420
cYTMgr* GetYTMgr();                                                     // 0x0067CAC0
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
namespace {
struct cConnectingDialog {
    void SetDialogText(int state);
    char pad[0x2c];
    cSPUILayout_s0063_aa90 mLayout;                                                // +0x2c
};
}
// ---- items of slice s0063aa90 end

// ---- items of slice s0063ba50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gMsgA[], gMsgB[];   // 0x0152481C, 0x015247A4
void  operator delete[](void* p);
namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
}
namespace eastl {
template <typename T> struct EmptyStr;
}
namespace eastl {
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
}
namespace eastl {
template <> struct EmptyStr<char>    { static char*    Get() { return (char*)gEmptyString16; } };
}
namespace eastl {
struct allocator_s0063_ba50 {
    void deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
template <typename T, typename Allocator = allocator_s0063_ba50>
class basic_string_s0063_ba50 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    basic_string_s0063_ba50() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    ~basic_string_s0063_ba50() { DeallocateSelf(); }
    const T* c_str() const { return mpBegin; }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
};
}
namespace eastl {
typedef basic_string_s0063_ba50<char> string;
}
namespace eastl {
typedef basic_string_s0063_ba50<wchar_t> string16_s0063_ba50;
}
namespace EA {
 eastl::string16_s0063_ba50 ConvertToString16(const char* p, int length = -1);   // 0x0093C5A0
}
struct IRefCounted { virtual int AddRef(); virtual int Release(); };
template <class T>
struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    AutoRef& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
struct IWindow_s0063_ba50 {   // UTFWin window (slots used by this module)
    virtual int AddRef();
    virtual int Release();
    virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06();
    virtual uint32_t GetControlID();   // +0x1C
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30();
    virtual void SetFlag(int flag, int on);                    // +0x7C
    virtual void SetCaption(const wchar_t* text);              // +0x80
    virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42();
    virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52();
    virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
    virtual void s58(); virtual void s59();
    virtual IWindow_s0063_ba50* FindWindowByID(uint32_t id, bool recurse);   // +0xF0
    virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65();
    virtual void RemoveWinProc(void* proc);                       // +0x108
};
struct cProfScope { void End(); };                       // 0x0067C420
cProfScope* __stdcall BeginProfScope(int a, int b);       // 0x0067CAC0
struct cString_s0063_ba50 {   // 0x14 bytes (retail)
    uint32_t pad[5];
    cString_s0063_ba50();                                                       // 0x006B5060
    ~cString_s0063_ba50();                                                      // 0x006B5240
    void Load(uint32_t tableId, uint32_t instanceId, const wchar_t* fallback);   // 0x006B54B0
    const wchar_t* Get();                                            // 0x006B55C0
};
struct cGlobalText { uint32_t pad0[6]; const wchar_t* mpTitle; const wchar_t* mpBody; uint32_t pad1[5]; const wchar_t* mpError; };
extern cGlobalText* gpGlobalText;    // 0x015F7CF4
struct cSPPlayModeUI_s0063_ba50 {
    void FUN_00635350(int a, int b);                // 0x00635350
    void FUN_00636320(int a);                       // 0x00636320
    void FUN_006353e0(int a);                       // 0x006353e0
    void FUN_00635380();                            // 0x00635380
    void SetEnabled(uint32_t id, bool on);          // 0x00634EF0
    IWindow_s0063_ba50* FindPlayModeUIWindow(uint32_t id);     // 0x00634DC0
    void ShowYouTubeLoginDialog();                  // 0x006360E0
    void SetYTPrompt(bool b);                       // 0x00635310
    void SetUIGroupVisible(uint32_t id, bool on);   // 0x00635760
};
void RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);   // 0x00571DB0 (cdecl)
struct ILocale { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
                 virtual const eastl::string16_s0063_ba50& GetLanguage(); };   // +0x14
ILocale* GetLocale();                                // 0x0067DE40
bool StrEq(const eastl::string16_s0063_ba50& a, const wchar_t* b);   // 0x006AB760 (cdecl)
struct cSPPlayModeSubModeBase { virtual ~cSPPlayModeSubModeBase() {} virtual void b1(); uint32_t pad[4]; };
struct IHandler { virtual ~IHandler() {} virtual int h1(); };
struct cRecordInfo { uint32_t mWidth, mHeight; float mFPS, mTime, mQuality; bool mAudio, mExcludeUI, mb32;
    cRecordInfo() : mWidth(320), mHeight(240), mFPS(15.0f), mTime(0.0f), mQuality(0.8f), mAudio(true), mExcludeUI(false), mb32(true) {} };
struct cAutoHandler {
    uint32_t a, b, c, d, e;
    cAutoHandler() : a(0), b(0), c(0), d(0), e(0) {}
    ~cAutoHandler()
    {
        if (a) {
            uint32_t ta = a, tb = b, tc = c, td = d, te = e;
            a = 0;
            RemoveHandler(ta, tb, tc, td, te);
        }
    }
};
struct cSPPlayModeSubModeMovie_s0063_ba50 : cSPPlayModeSubModeBase, IHandler {
    uint32_t mpMovieSystem;                  // +0x18
    cRecordInfo mRecordInfo;                 // +0x1C
    cSPPlayModeUI_s0063_ba50* mUI;                      // +0x34
    char mCurrFilename[260];                 // +0x38
    char mCurrPathname[260];                 // +0x13C
    eastl::string16_s0063_ba50 mTableA[260];            // +0x240
    eastl::string16_s0063_ba50 mTableB[260];            // +0x1280
    bool mRecording;                         // +0x22C0
    bool mRecordingIndicator;                // +0x22C1
    uint32_t mIndicatorTimer;                // +0x22C4
    uint32_t pad22c8[2];
    cAutoHandler mAutoMessages;              // +0x22D0
    int mDialogInProgress;                   // +0x22E4
    AutoRef<IRefCounted> pmb;                // +0x22E8
    eastl::string mYTAuthToken;              // +0x22EC
    eastl::string mYTUsername;               // +0x22FC
    eastl::string16_s0063_ba50 mYTVideoURL;             // +0x230C
    bool mRegisterSuccess, mRegisterCheckComplete, mDoRegisterCheck, mLoginSuccess, mLoginCheckComplete;   // +0x231C
    bool mDoLoginCheck, mVideoUploadSuccess, mDoVideoUpload, mVideoUploadComplete, mEnableYouTubeVideoUpload;
    uint32_t mYTStatusCode;                  // +0x2328
    eastl::string mYTStatusMessage;          // +0x232C
    eastl::string16_s0063_ba50 mYTErrorMessage;         // +0x233C
    eastl::string mYTPassword;               // +0x234C
    bool mbYTPrompt;                         // +0x235C
    bool mb235d, mb235e;

    cSPPlayModeSubModeMovie_s0063_ba50();  // 0x0063c200 (cSPPlayModeSubModeMovie::cSPPlayModeSubModeMovie_s0063_ba50)
    virtual ~cSPPlayModeSubModeMovie_s0063_ba50();  // 0x0063c200 (cSPPlayModeSubModeMovie::cSPPlayModeSubModeMovie_s0063_ba50)
    void Shutdown();  // 0x0063bb90 (cSPPlayModeSubModeMovie::Shutdown)
    static void SetUpYouTubeErrorMessage(int kind);  // 0x0063bc10 (cSPPlayModeSubModeMovie::SetUpYouTubeErrorMessage)
    static void ShowLoginToYouTubeDialog();  // 0x0063bd50 (cSPPlayModeSubModeMovie::ShowLoginToYouTubeDialog)
    static void ShowYouTubeUploadVideoDialog();  // 0x0063be00 (cSPPlayModeSubModeMovie::ShowYouTubeUploadVideoDialog)
    void ShowYouTubeLoginDialog();
    static bool IsLocaleEnglish();  // 0x0063c0a0 (cSPPlayModeSubModeMovie::IsLocaleEnglish)
    void SetStatusText(bool withArg, int arg);
    void ShowMovieSavedDialog();  // 0x0063c640 (cSPPlayModeSubModeMovie::ShowMovieSavedDialog)
    void LoadYouTubeCredentials();
    void OnMovieRecorded();
};
void ShowMessageBoxEx(const void* a, const void* b);   // 0x00809DB0 (cdecl)
struct cEditorYouTubeAuthenticationMessage {   // 0x34
    eastl::string mUsername;
    eastl::string mPassword;
    eastl::string mSource;
    bool mCheckRegistration;
    ~cEditorYouTubeAuthenticationMessage();
};
struct cEditorYouTubeVideoUploadMessage {   // 0x6c
    eastl::string mUsername;
    eastl::string mClienID;
    eastl::string mAuthenticationToken;
    eastl::string mDeveloperKey;
    eastl::string mVideoFilename;
    uint32_t mVideoKey[3];
    eastl::string mXMLRequest;
    ~cEditorYouTubeVideoUploadMessage();
};
// ---- items of slice s0063ba50 end

// @ 0x0063b640
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



// @ 0x0063b730
bool cSPPlayModeSubModeMovie::OnKeyDown(int key, int mods)
{
    if (key == 0xd && mState == 3) {
        v11(0x5652348);
        return true;
    }
    return false;
}



// @ 0x0063b760
void cSPPlayModeSubModeMovie::FUN_0063b760()
{
    bool b = !mFlag22c1;
    mUI->SetUIGroupVisible(0x3f434ac, b);
    mUI->SetUIGroupVisible(0x3fc1740, !b);
    mFlag22c1 ^= 1;
}



// @ 0x0063b7b0
void cSPPlayModeSubModeMovie::SetState2()
{
    GetYTMgr()->SetMode(false, true);
    FUN_00809db0(g152481c, g15247b0);
    mState = 2;
}



// @ 0x0063b7f0
void cSPPlayModeSubModeMovie::SetState4()
{
    GetYTMgr()->SetMode(false, true);
    FUN_00809db0(0, g15247bc);
    mState = 4;
}



// @ 0x0063b820
void cSPPlayModeSubModeMovie::SetState5()
{
    GetYTMgr()->SetMode(false, true);
    FUN_00809db0(g152481c, g15247d4);
    mState = 5;
}



// @ 0x0063b860
void cSPPlayModeSubModeMovie::SetState6()
{
    GetYTMgr()->SetMode(false, true);
    FUN_00809db0(0, g15247c8);
    mState = 6;
}



// @ 0x0063b890
bool SP::cSPPlayModeSubModeMovie::GetYTPrompt()
{
    return GetConfigManager()->GetValue(0x5664a8b) == 0;
}



// @ 0x0063b8b0
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



// @ 0x0063b910
void cSPPlayModeSubModeMovie::SetStateB()
{
    GetYTMgr()->SetMode(false, true);
    FUN_00809db0(g152481c, g1524804);
    mState = 0xb;
}



// @ 0x0063b950
void FUN_0063b950()
{
    const void* p = gDefaultSaveData;
    cSaveArea* a = GetSaveArea(0x11ac197);
    if (a && a->GetType() == 0x34728492)
        p = a->GetData();
    FUN_009322b0(p);
}



// @ 0x0063b9a0
void FUN_0063b9a0()
{
    const void* p = gDefaultSaveData;
    cSaveArea* a = GetSaveArea(0x11ac197);
    if (a && a->GetType() == 0x34728492)
        p = a->GetData();
    FUN_00932960(p);
}



// @ 0x0063b9f0
void cSPPlayModeSubModeMovie::FUN_0063b9f0(bool v)
{
    mUI->FUN_00635350(v, 0);
    mUI->FUN_00636320(v);
    mUI->FUN_006353e0(v);
    mUI->SetEnabled(0x3a8ede4, v);
    if (v) mUI->FUN_00635380();
}


// @ 0x0063bb90
void cSPPlayModeSubModeMovie_s0063_ba50::Shutdown()
{
    mUI->FUN_00635350(1, 0);
    mUI->FUN_00636320(1);
    mUI->FUN_006353e0(1);
    mUI->SetEnabled(0x3a8ede4, true);
    mUI->FUN_00635380();
    if (mAutoMessages.a) {
        uint32_t a = mAutoMessages.a, b = mAutoMessages.b, c = mAutoMessages.c, d = mAutoMessages.d, e = mAutoMessages.e;
        mAutoMessages.a = 0;
        RemoveHandler(a, b, c, d, e);
    }
}

// @ 0x0063bc10
void cSPPlayModeSubModeMovie_s0063_ba50::SetUpYouTubeErrorMessage(int kind)
{
    cString_s0063_ba50 s;
    switch (kind) {
    case 0:
        s.Load(0x7518573e, 0x5baf944, L"Login Failed (PLACEHOLDER)");
        break;
    case 1:
        s.Load(0x7518573e, 0x5cbdeda, L"Upload Failed (PLACEHOLDER)");
        break;
    }
    cGlobalText* g = gpGlobalText;
    g->mpError = s.Get();
}

// @ 0x0063c0a0
bool SP::cSPPlayModeSubModeMovie::IsLocaleEnglish()
{
    return StrEq(GetLocale()->GetLanguage(), L"en-us") || StrEq(GetLocale()->GetLanguage(), L"en-us")
        || StrEq(GetLocale()->GetLanguage(), L"en-gb");
}

// @ 0x0063c200
cSPPlayModeSubModeMovie_s0063_ba50::cSPPlayModeSubModeMovie_s0063_ba50()
: mpMovieSystem(0), mDialogInProgress(0), mRegisterSuccess(false), mRegisterCheckComplete(false), mDoRegisterCheck(false),
      mLoginSuccess(false), mLoginCheckComplete(false), mDoLoginCheck(false), mVideoUploadSuccess(false),
      mDoVideoUpload(false), mVideoUploadComplete(false), mEnableYouTubeVideoUpload(false), mYTStatusCode(0),
      mbYTPrompt(true), mb235d(false), mb235e(false)
{
}

// @ 0x0063c3f0
cSPPlayModeSubModeMovie_s0063_ba50::~cSPPlayModeSubModeMovie_s0063_ba50()
{
}

// @ 0x0063c640
void cSPPlayModeSubModeMovie_s0063_ba50::ShowMovieSavedDialog()
{
    BeginProfScope(0, 1)->End();
    const eastl::string16_s0063_ba50 name = EA::ConvertToString16(mCurrFilename, -1);
    gpGlobalText->mpTitle = name.c_str();
    const eastl::string16_s0063_ba50 path = EA::ConvertToString16(mCurrPathname, -1);
    gpGlobalText->mpBody = path.c_str();
    ShowMessageBoxEx(gMsgA, gMsgB);
    mDialogInProgress = 1;
}

// @ 0x0063c700
cEditorYouTubeAuthenticationMessage::~cEditorYouTubeAuthenticationMessage()
{}

// @ 0x0063c750
cEditorYouTubeVideoUploadMessage::~cEditorYouTubeVideoUploadMessage()
{}
