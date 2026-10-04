// slice s0063ba50: cConnectingDialog (UI popup) and cSPPlayModeSubModeMovie (YouTube upload / movie recording).
// Module flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "s0063ba50.h"

extern char gDialogText[];   // 0x013EC468

extern const float gRotationSpeed;   // 0x013FA9C8 (-4.18879f)

struct cConnectingDialog : CustomWinProc {   // 0x38 bytes
    AutoRef<IWindow> mpWindow;   // +0xC
    float mStartTime;            // +0x10
    float mTimeout;              // +0x14
    bool mEndConnecting;         // +0x18
    bool mEndConnected;          // +0x19
    cSPVector4 mRotation;        // +0x1C
    cSPUILayout mLayout;         // +0x2C

    void SetDialogText(int a);   // 0x0063B640
    void Show(int a);
    bool SetWindow(IWindow* w);
    void HandleResults(bool b);
    void End(bool b);
    bool Update(void* p);
    bool Init();   // 0x0063B5C0
    cConnectingDialog() : mTimeout(2.5f), mEndConnecting(false), mEndConnected(false), mRotation(0.0f, 0.0f, 1.0f, 0.0f) { }
    bool HandleUIMessage(void* a, void* msg);
    virtual bool Slot32(void* a);
};

// @ 0x0063ba50
void cConnectingDialog::Show(int a)
{
    SetDialogText(a);
    IWindow* w = mLayout.FindWindowByID(0x42e2e38, true);
    if (w)
        w->SetCaption((const wchar_t*)gDialogText);
    w = mLayout.FindWindowByID(0x431e538, true);
    if (w)
        BeginModal(w, 0, 1);
}

// @ 0x0063bab0
bool cConnectingDialog::SetWindow(IWindow* w)
{
    mpWindow = w;
    mStartTime = GetElapsedSeconds();
    return true;
}

// @ 0x0063baf0
void cConnectingDialog::HandleResults(bool b)
{
    EndModal(mpWindow.mpObject, 0, 1);
    mpWindow.mpObject->RemoveWinProc(this);
    mpWindow = 0;
    mLayout.Shutdown(true);
}

// @ 0x0063bf20
void cConnectingDialog::End(bool b)
{
    if (b) {
        mEndConnecting = true;
        return;
    }
    EndModal(mpWindow.mpObject, 0, 1);
    mpWindow.mpObject->RemoveWinProc(this);
    mpWindow = 0;
    mLayout.Shutdown(true);
}

void  SetAnimProps(IWindow* w, cSPVector4* rot);   // 0x00808230 (cdecl)

// @ 0x0063bf80
bool cConnectingDialog::Update(void* p)
{
    if (mEndConnecting && GetElapsedSeconds() - mStartTime > mTimeout) {
        if (!mEndConnected) {
            mEndConnected = true;
            mStartTime = GetElapsedSeconds();
            mTimeout = 0.0f;
            mRotation.w = 0.0f;
            SetAnimProps(mpWindow.mpObject->FindWindowByID(0x43322c0, true), &mRotation);
            GetMessageServer()->PostMessage(0x56bbd7f, 0, 0);
            return true;
        }
        HandleResults(true);
        return true;
    }
    if (!mEndConnected) {
        mRotation.w = (GetElapsedSeconds() - mStartTime) * gRotationSpeed;
        SetAnimProps(mpWindow.mpObject->FindWindowByID(0x43322c0, true), &mRotation);
        GetMessageServer()->PostMessage(0x56bbd7f, &mRotation, 0);
    }
    return true;
}

struct cUIMessage { IWindow* mpSource; uint32_t pad; uint32_t mType; };

// @ 0x0063c190
bool cConnectingDialog::HandleUIMessage(void* a, void* m)
{
    cUIMessage* msg = (cUIMessage*)m;
    uint32_t type = msg->mType;
    if (type == 0x287259f6) {
        if (msg->mpSource->GetControlID() == 0x5d2bdf8) {
            GetMessageServer()->PostMessage(0x5d2c5c0, 0, 0);
            return true;
        }
    } else if (type == 0xc) {
        return Update(a);
    } else if (type == 0x11) {
        return Slot32(a);
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// misc services
struct cProfScope { void End(); };                       // 0x0067C420
cProfScope* __stdcall BeginProfScope(int a, int b);       // 0x0067CAC0

struct cString {   // 0x14 bytes (retail)
    uint32_t pad[5];
    cString();                                                       // 0x006B5060
    ~cString();                                                      // 0x006B5240
    void Load(uint32_t tableId, uint32_t instanceId, const wchar_t* fallback);   // 0x006B54B0
    const wchar_t* Get();                                            // 0x006B55C0
};

struct cGlobalText { uint32_t pad0[6]; const wchar_t* mpTitle; const wchar_t* mpBody; uint32_t pad1[5]; const wchar_t* mpError; };
extern cGlobalText* gpGlobalText;    // 0x015F7CF4

struct IConfigManager {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual void SetBool(uint32_t id, bool v);      // +0x2C
    virtual int GetBool(uint32_t id);              // +0x30
};
IConfigManager* GetConfigManager();                 // 0x0067DD30

struct cSPPlayModeUI {
    void FUN_00635350(int a, int b);                // 0x00635350
    void FUN_00636320(int a);                       // 0x00636320
    void FUN_006353e0(int a);                       // 0x006353e0
    void FUN_00635380();                            // 0x00635380
    void SetEnabled(uint32_t id, bool on);          // 0x00634EF0
    IWindow* FindPlayModeUIWindow(uint32_t id);     // 0x00634DC0
    void ShowYouTubeLoginDialog();                  // 0x006360E0
    void SetYTPrompt(bool b);                       // 0x00635310
    void SetUIGroupVisible(uint32_t id, bool on);   // 0x00635760
};

struct AutoHandler { uint32_t a, b, c, d, e; };
void RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);   // 0x00571DB0 (cdecl)

struct IPropertyList : IRefCounted {};
struct IPropertyManager {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual bool GetPropertyList(uint32_t instanceId, uint32_t groupId, IPropertyList** out);   // +0x2C
};
IPropertyManager* GetPropertyManager();             // 0x0067DE30
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int a);   // 0x00932F30 (cdecl)
bool GetPropertyAsString8(IPropertyList* l, uint32_t id, eastl::string* out);   // 0x006A13B0 (cdecl)
void Decrypt(eastl::string* src, eastl::string* dst);    // 0x0060BF00 (cdecl)

struct ILocale { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
                 virtual const eastl::string16& GetLanguage(); };   // +0x14
ILocale* GetLocale();                                // 0x0067DE40
bool StrEq(const eastl::string16& a, const wchar_t* b);   // 0x006AB760 (cdecl)

extern const char* const gFmtMsg;      // 0x01524438
extern const char* const gFmtMsgNoArg; // 0x0152443C
extern const wchar_t* const gYTPropName;   // 0x01524440
void* GetAllocator();   // 0x009512C0
#include <stdio.h>

// ---------------------------------------------------------------------------------------------
extern AutoRef<cConnectingDialog> gConnectingDialog;   // 0x015F8A70
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

struct cStr5 { eastl::string16 s[5]; };

struct cSPPlayModeSubModeMovie : cSPPlayModeSubModeBase, IHandler {
    uint32_t mpMovieSystem;                  // +0x18
    cRecordInfo mRecordInfo;                 // +0x1C
    cSPPlayModeUI* mUI;                      // +0x34
    char mCurrFilename[260];                 // +0x38
    char mCurrPathname[260];                 // +0x13C
    eastl::string16 mTableA[260];            // +0x240
    eastl::string16 mTableB[260];            // +0x1280
    bool mRecording;                         // +0x22C0
    bool mRecordingIndicator;                // +0x22C1
    uint32_t mIndicatorTimer;                // +0x22C4
    uint32_t pad22c8[2];
    cAutoHandler mAutoMessages;              // +0x22D0
    int mDialogInProgress;                   // +0x22E4
    AutoRef<IRefCounted> pmb;                // +0x22E8
    eastl::string mYTAuthToken;              // +0x22EC
    eastl::string mYTUsername;               // +0x22FC
    eastl::string16 mYTVideoURL;             // +0x230C
    bool mRegisterSuccess, mRegisterCheckComplete, mDoRegisterCheck, mLoginSuccess, mLoginCheckComplete;   // +0x231C
    bool mDoLoginCheck, mVideoUploadSuccess, mDoVideoUpload, mVideoUploadComplete, mEnableYouTubeVideoUpload;
    uint32_t mYTStatusCode;                  // +0x2328
    eastl::string mYTStatusMessage;          // +0x232C
    eastl::string16 mYTErrorMessage;         // +0x233C
    eastl::string mYTPassword;               // +0x234C
    bool mbYTPrompt;                         // +0x235C
    bool mb235d, mb235e;

    cSPPlayModeSubModeMovie();
    virtual ~cSPPlayModeSubModeMovie();
    void Shutdown();
    static void SetUpYouTubeErrorMessage(int kind);
    static void ShowLoginToYouTubeDialog();
    static void ShowYouTubeUploadVideoDialog();
    void ShowYouTubeLoginDialog();
    static bool IsLocaleEnglish();
    void SetStatusText(bool withArg, int arg);
    void ShowMovieSavedDialog();
    void LoadYouTubeCredentials();
    void OnMovieRecorded();
};

// @ 0x0063bb90
void cSPPlayModeSubModeMovie::Shutdown()
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
void cSPPlayModeSubModeMovie::SetUpYouTubeErrorMessage(int kind)
{
    cString s;
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

// @ 0x0063bd50
void cSPPlayModeSubModeMovie::ShowLoginToYouTubeDialog()
{
    BeginProfScope(0, 1)->End();
    cSPUILayout* layout = &gConnectingDialog.mpObject->mLayout;
    IWindow* w = layout->FindWindowByID(0x5d2bdf8, true);
    w->SetFlag(1, 0);
    w->SetFlag(2, 0);
    IWindow* t = layout->FindWindowByID(0x5006000, true);
    if (t) {
        cString s;
        s.Load(0x7518573e, 0x5496b24, L"*Log In...*");
        t->SetCaption(s.Get());
    }
}

// @ 0x0063be00
void cSPPlayModeSubModeMovie::ShowYouTubeUploadVideoDialog()
{
    BeginProfScope(0, 1)->End();
    cSPUILayout* layout = &gConnectingDialog.mpObject->mLayout;
    IWindow* w = layout->FindWindowByID(0x5d2bdf8, true);
    w->SetFlag(1, 0);
    w->SetFlag(2, 0);
    IWindow* t = layout->FindWindowByID(0x5006000, true);
    if (t) {
        cString s;
        s.Load(0x7518573e, 0x55aa305, L"*Upload Video...*");
        w->SetFlag(1, 1);
        w->SetFlag(2, 1);
        t->SetCaption(s.Get());
    }
}

// @ 0x0063bec0
void cSPPlayModeSubModeMovie::ShowYouTubeLoginDialog()
{
    BeginProfScope(0, 1)->End();
    mUI->ShowYouTubeLoginDialog();
    if (GetConfigManager()->GetBool(0x5664a8b)) {
        mUI->SetYTPrompt(true);
        mDialogInProgress = 3;
    } else {
        mUI->SetYTPrompt(false);
        mDialogInProgress = 3;
    }
}

// @ 0x0063bc70
void CreateConnectingDialog()
{
    BeginProfScope(0, 1)->End();
    cConnectingDialog* d = new (4, "UI/cConnectionDialog", GetAllocator()) cConnectingDialog();
    gConnectingDialog = d;
    if (gConnectingDialog.mpObject->Init())
        gConnectingDialog.mpObject->Show(0);
}

// @ 0x0063c060
void DestroyConnectingDialog(bool b)
{
    BeginProfScope(1, 1)->End();
    if (gConnectingDialog.mpObject) {
        gConnectingDialog.mpObject->End(b);
        gConnectingDialog = 0;
    }
}

// @ 0x0063c0a0
bool cSPPlayModeSubModeMovie::IsLocaleEnglish()
{
    return StrEq(GetLocale()->GetLanguage(), L"en-us") || StrEq(GetLocale()->GetLanguage(), L"en-us")
        || StrEq(GetLocale()->GetLanguage(), L"en-gb");
}

static __forceinline eastl::string16 FormatStatus(bool withArg, int arg)
{
    char buf[0x100];
    if (withArg) {
        sprintf(buf, gFmtMsg, arg);
        return EA::ConvertToString16(buf, -1);
    }
    return EA::ConvertToString16(gFmtMsgNoArg, -1);
}

// @ 0x0063c590
void cSPPlayModeSubModeMovie::SetStatusText(bool withArg, int arg)
{
    IWindow* w = mUI->FindPlayModeUIWindow(0x42cadb8);
    if (w) {
        if (withArg) {
            char buf[0x100];
            sprintf(buf, gFmtMsg, arg);
            w->SetCaption(EA::ConvertToString16(buf, -1).c_str());
        } else {
            w->SetCaption(EA::ConvertToString16(gFmtMsgNoArg, -1).c_str());
        }
    }
}

void ShowMessageBoxEx(const void* a, const void* b);   // 0x00809DB0 (cdecl)
extern char gMsgA[], gMsgB[];   // 0x0152481C, 0x015247A4

// @ 0x0063c640
void cSPPlayModeSubModeMovie::ShowMovieSavedDialog()
{
    BeginProfScope(0, 1)->End();
    const eastl::string16 name = EA::ConvertToString16(mCurrFilename, -1);
    gpGlobalText->mpTitle = name.c_str();
    const eastl::string16 path = EA::ConvertToString16(mCurrPathname, -1);
    gpGlobalText->mpBody = path.c_str();
    ShowMessageBoxEx(gMsgA, gMsgB);
    mDialogInProgress = 1;
}

struct cEditorYouTubeAuthenticationMessage {   // 0x34
    eastl::string mUsername;
    eastl::string mPassword;
    eastl::string mSource;
    bool mCheckRegistration;
    ~cEditorYouTubeAuthenticationMessage();
};

// @ 0x0063c700
cEditorYouTubeAuthenticationMessage::~cEditorYouTubeAuthenticationMessage() {}

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

// @ 0x0063c750
cEditorYouTubeVideoUploadMessage::~cEditorYouTubeVideoUploadMessage() {}

// @ 0x0063c7f0
void cSPPlayModeSubModeMovie::LoadYouTubeCredentials()
{
    AutoRef<IPropertyList> list;
    IPropertyManager* pm = GetPropertyManager();
    list = 0;
    uint32_t id = FNV1_String16(gYTPropName, 0x811c9dc5, 1);
    pm->GetPropertyList(id, 0x11ac192, &list.mpObject);
    if (list.mpObject) {
        GetPropertyAsString8(list.mpObject, 0x5664bf5, &mYTUsername);
        eastl::string tmp;
        if (GetPropertyAsString8(list.mpObject, 0x5664bf6, &tmp))
            Decrypt(&tmp, &mYTPassword);
    } else {
        GetConfigManager()->SetBool(0x5664a8b, false);
    }
}

// string / save-area helpers
int Sprintf16(wchar_t* dst, const wchar_t* fmt, ...);                                    // 0x009399C0 (cdecl)
void StrncpyUTF8ToUTF16(char* dst, int dstSize, const wchar_t* src, int srcLen);         // 0x0093CF10 (cdecl)
struct ISaveArea { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
                   virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
                   virtual const wchar_t* GetPath(); };   // +0x28
ISaveArea* GetSaveArea(uint32_t id);                                                     // 0x006B1F90 (cdecl)
struct IMovieSystem { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
                      virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
                      virtual void s10(); virtual void s11(); virtual void s12();
                      virtual int GetMovieName(); };  // +0x34
extern const wchar_t gFmtW[];    // 0x013F5C04
extern const char gFmtS[];       // 0x013F5B98

// @ 0x0063c8f0
void cSPPlayModeSubModeMovie::OnMovieRecorded()
{
    mUI->FUN_00635350(0, 0);
    mUI->FUN_00636320(0);
    mUI->FUN_006353e0(0);
    mUI->SetEnabled(0x3a8ede4, false);
    wchar_t wbuf[0x104];
    char cbuf[0x104];
    Sprintf16(wbuf, gFmtW, ((IMovieSystem*)(void*)mpMovieSystem)->GetMovieName());
    StrncpyUTF8ToUTF16(cbuf, 0x104, wbuf, -1);
    sprintf(mCurrFilename, gFmtS, cbuf);
    Sprintf16(wbuf, gFmtW, GetSaveArea(0x11ac197)->GetPath());
    StrncpyUTF8ToUTF16(cbuf, 0x104, wbuf, -1);
    sprintf(mCurrPathname, gFmtS, cbuf);
    IWindow* w = mUI->FindPlayModeUIWindow(0x42cadb8);
    if (w) {
        char buf[0x100];
        sprintf(buf, gFmtMsg, mCurrFilename);
        w->SetCaption(EA::ConvertToString16(buf, -1).c_str());
    }
    mRecording = true;
    mRecordingIndicator = false;
    mUI->SetUIGroupVisible(0x3f434ac, true);
    mUI->SetUIGroupVisible(0x3fc1740, false);
    bool vis = !mRecordingIndicator;
    mUI->SetUIGroupVisible(0x3f434ac, vis);
    mUI->SetUIGroupVisible(0x3fc1740, !vis);
    mRecordingIndicator ^= true;
    mIndicatorTimer = 0;
    GetMessageServer()->PostMessage(0x52f180, (void*)0x21, 0);
}

// @ 0x0063c200
cSPPlayModeSubModeMovie::cSPPlayModeSubModeMovie()
    : mpMovieSystem(0), mDialogInProgress(0), mRegisterSuccess(false), mRegisterCheckComplete(false), mDoRegisterCheck(false),
      mLoginSuccess(false), mLoginCheckComplete(false), mDoLoginCheck(false), mVideoUploadSuccess(false),
      mDoVideoUpload(false), mVideoUploadComplete(false), mEnableYouTubeVideoUpload(false), mYTStatusCode(0),
      mbYTPrompt(true), mb235d(false), mb235e(false)
{
}

// @ 0x0063c3f0
cSPPlayModeSubModeMovie::~cSPPlayModeSubModeMovie()
{
}
