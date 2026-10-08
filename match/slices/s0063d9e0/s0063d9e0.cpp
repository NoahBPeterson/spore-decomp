// slice s0063d9e0: cSPPlayModeSubModePhoto activation/shutdown + movie/photo helpers.
#include <stdio.h>
#include "../s00636320/s00636320.h"

struct cAutoHandler { uint32_t a, b, c, d, e; };
void RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);   // 0x00571DB0
struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void PostMessage(uint32_t id, void* data, int flags);   // +0x14
};
IMessageServer* GetMessageServer();                                               // 0x0067DCC0

struct IHandlerServer {
    virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3(); virtual void h4();
    virtual void h5(); virtual void h6(); virtual void h7(); virtual void h8();
    virtual void AddHandler(void* handler, uint32_t id);   // +0x24
};
struct IPhotoBrowser { void HandleMessage(); void Deactivate(); };   // 0x006340C0 / 0x00632FE0
struct IAnimObj {
    virtual void a0(); virtual void a1(); virtual void a2();
    virtual float v3(uint32_t a, uint32_t b, int c, int d, int e);   // +0x0C
};

struct cSPPlayModeSubModePhoto {
    void* mVptr;                   // +0x00
    void* mObj4;                   // +0x04
    IAnimObj* mAnim;               // +0x08
    char pad0c[0x14 - 0x0c];
    char mHandlerSub[0x50 - 0x14]; // +0x14 (IHandler subobject)
    IPhotoBrowser mBrowser;        // +0x50
    char padF30[0xf30 - 0x51];
    bool mbF30;                    // +0xF30
    bool mbF31;                    // +0xF31
    char padF32[0xf58 - 0xf32];
    bool mbF58;                    // +0xF58
    char padF59[0xf78 - 0xf59];
    bool mbF78;                    // +0xF78
    char padF79[0xf9c - 0xf79];
    bool mbF9C;                    // +0xF9C
    bool mbF9D;                    // +0xF9D
    char padF9E[0xfa0 - 0xf9e];
    cAutoHandler mAutoMsgHandler;  // +0xFA0

    bool Activate();               // 0x0063E770
    void Shutdown();               // 0x0063E810
    void FUN_0063d9e0();
    void FUN_0063dc40();
    void FUN_0063de20();
};



// @ 0x0063E770
bool cSPPlayModeSubModePhoto::Activate()
{
    mBrowser.HandleMessage();
    mbF30 = false;
    mbF31 = false;
    mbF58 = false;
    mbF78 = false;
    mbF9C = false;
    mbF9D = false;

    IHandlerServer* ms = (IHandlerServer*)GetMessageServer();
    if (ms) {
        void* handler = (void*)((char*)this + 0x14);
        mAutoMsgHandler.a = (uint32_t)ms;
        mAutoMsgHandler.b = (uint32_t)handler;
        mAutoMsgHandler.c = 0x13ff4d4;
        mAutoMsgHandler.d = 0xd;
        mAutoMsgHandler.e = 0;
        if (handler) {
            for (uint32_t i = 0; i < 0x34; i += 4)
                ms->AddHandler(handler, *(uint32_t*)(0x13ff4d4 + i));
        }
    }
    return true;
}

// @ 0x0063E810
void cSPPlayModeSubModePhoto::Shutdown()
{
    if (mAutoMsgHandler.a) {
        uint32_t a = mAutoMsgHandler.a, b = mAutoMsgHandler.b, c = mAutoMsgHandler.c;
        uint32_t d = mAutoMsgHandler.d, e = mAutoMsgHandler.e;
        mAutoMsgHandler.a = 0;
        RemoveHandler(a, b, c, d, e);
    }
    mBrowser.Deactivate();
    mAnim->v3(*(uint32_t*)((char*)mObj4 + 0x364), 0x4330667, 1, 1, 0);
}

// @ 0x0063D9E0  PARTIAL
void cSPPlayModeSubModePhoto::FUN_0063d9e0() {}
// @ 0x0063DC40  PARTIAL
void cSPPlayModeSubModePhoto::FUN_0063dc40() {}
// @ 0x0063DE20  PARTIAL
void cSPPlayModeSubModePhoto::FUN_0063de20() {}

// ---------------------------------------------------------------- cSPPlayModeSubModeMovie::HandleButton
struct Key12 { uint32_t a, b, c; };
struct IMovieSystem {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9();
    virtual void m10();
    virtual void StartRecording(const wchar_t* name, void* info);   // +0x2c
    virtual bool IsRecording();                                      // +0x30
    virtual void m13();
    virtual void StopRecording();                                    // +0x38
};
struct IAuthManager {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8();
    virtual bool v24();                                              // +0x24
    virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14();
    virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual void a20(); virtual void a21();
    virtual bool v58();                                              // +0x58
};
IAuthManager* GetAuthManager();                                      // 0x00607A60
struct IConfigMgr {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9();
    virtual void c10();
    virtual void SetValue(uint32_t id, int v);                       // +0x2c
    virtual int GetValue(uint32_t id);                               // +0x30
};
IConfigMgr* GetConfigManager();                                      // 0x0067DD30
struct ISaveArea {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual const char* GetPath();                                   // +0x28
    virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual void SetName(const wchar_t* name, int a, int b);         // +0x54 (index 21)
};
ISaveArea* __cdecl GetSaveArea(uint32_t id);                         // 0x006B1F90
void __cdecl WStr_Format(void* str, const wchar_t* fmt, ...);        // 0x0041E050
int __cdecl Sprintf16(wchar_t* buf, const wchar_t* fmt, ...);        // 0x009399C0
void __cdecl Utf16ToUtf8(char* dst, unsigned n, const wchar_t* src, int len);   // 0x0093CF10
struct IPropList;
extern IPropList* gAppProperties;                                    // 0x015FD918
bool __cdecl TryGetUIntProperty(IPropList* pl, uint32_t id, uint32_t* out);   // 0x00410370
bool __cdecl GetBoolProperty(IPropList* pl, uint32_t id, bool* out);          // 0x00407190
void __cdecl CalloutMessageBox(void* where, const Key12* key);       // 0x00809DB0
void __cdecl OpenBrowser(const wchar_t* url, int flag);              // 0x00935FB0
extern Key12 gKey15247e0, gKey15247ec, gKey1524810;
extern void* gCalloutWhere;                                          // 0x0152481C

namespace EA { namespace DateTime {
struct DateTime {
    int64_t mnSeconds;
    DateTime(int timeFrame);                                         // 0x0092E3D0
    uint32_t GetParameter(int which);                                // 0x0092DF80
};
} }

namespace SP {
class cString {
public:
    cString();                                                       // 0x006B5060
    ~cString();                                                      // 0x006B5240
    void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* dflt);   // 0x006B54B0
    const wchar_t* GetText();                                        // 0x006B55C0
    char pad[0x14];
};
}

struct cDateStrings {
    char pad0[0x44];
    const wchar_t* mYear;   // +0x44
    const wchar_t* mMonth;  // +0x48
    const wchar_t* mDay;    // +0x4C
    const wchar_t* mTime;   // +0x50
    const wchar_t* mPrefix; // +0x54
};
extern cDateStrings* gDateStrings;                                   // 0x015F7CF4

struct cSPPlayModeSubModeMovie {
    char pad00[0x18];
    IMovieSystem* mMovieSystem;     // +0x18
    uint32_t mWidth;                // +0x1C
    uint32_t mHeight;               // +0x20
    char pad24[4];
    float mTime;                    // +0x28
    char pad2c[5];
    bool mExcludeUI;                // +0x31
    char pad32[2];
    cSPPlayModeUI* mUI;             // +0x34
    char mCurrFilename[260];        // +0x38
    char mCurrPathname[260];        // +0x13C
    char pad240[0x22c0 - 0x240];
    bool mRecording;                // +0x22C0
    bool mIndicator;                // +0x22C1
    char pad22c2[2];
    int mIndicatorTimer;            // +0x22C4
    char pad22c8[0x22e4 - 0x22c8];
    int mDialogInProgress;          // +0x22E4
    char pad22e8[0x22fc - 0x22e8];
    eastl::string mYTUsername;      // +0x22FC
    char pad230c[0x234c - 0x230c];
    eastl::string mYTPassword;      // +0x234C

    bool HandleButton(int id);                       // 0x0063E100
    void ToggleRecordingIndicator(char b);           // 0x0063D910
    void CheckYouTubeRegistration();                 // 0x0063CED0
    void FUN_0063cd30();
    void FUN_0063b760();
    bool FUN_0063b950();
    bool FUN_0063b9a0();
    void FUN_0063b9f0(bool v);
    void FUN_0063b8b0();
    void FUN_0063bec0();
    void SetStatusText(bool withArg, const char* arg);   // 0x0063C590
    static bool GetYTPrompt();                       // 0x0063B890
    static bool IsLocaleEnglish();                   // 0x0063C0A0
};
void CreateConnectingDialog();                       // 0x0063BC70

// @ 0x0063E100
bool cSPPlayModeSubModeMovie::HandleButton(int id)
{
    IAuthManager* auth = GetAuthManager();
    switch (id) {
    case 0x3f434ac:
    case 0x3fc1740:
        if (mMovieSystem->IsRecording()) {
            mMovieSystem->StopRecording();
            ToggleRecordingIndicator(0);
            ISaveArea* sa = GetSaveArea(0x11ac197);
            eastl::string16 name;
            WStr_Format(&name, L"%s.avi", EA::ConvertToString16(mCurrFilename, -1).c_str());
            sa->SetName(name.c_str(), 0, 2);
            FUN_0063b9f0(true);
            return true;
        }
        if (!FUN_0063b950() && !FUN_0063b9a0())
            return true;
        FUN_0063b9f0(false);
        {
            eastl::string16 year;
            eastl::string16 month;
            eastl::string16 day;
            eastl::string16 time;
            eastl::string16 prefix;
            wchar_t wide[0x104];
            char narrow[0x104];

            WStr_Format(&prefix, L"%s", L"Spore_");
            gDateStrings->mPrefix = prefix.c_str();
            EA::DateTime::DateTime now(2);
            WStr_Format(&year, L"%04u", now.GetParameter(1));
            gDateStrings->mYear = year.c_str();
            WStr_Format(&month, L"%02u", now.GetParameter(2));
            gDateStrings->mMonth = month.c_str();
            WStr_Format(&day, L"%02u", now.GetParameter(6));
            gDateStrings->mDay = day.c_str();
            WStr_Format(&time, L"%02u-%02u-%02u", now.GetParameter(8), now.GetParameter(9), now.GetParameter(10));
            gDateStrings->mTime = time.c_str();

            SP::cString title;
            title.Load(0x7518573e, 0x5dbc9ee, L"Movie Name (PLACEHOLDER)");
            Sprintf16(wide, L"%s", title.GetText());
            Utf16ToUtf8(narrow, 0x104, wide, -1);
            sprintf(mCurrFilename, "%s", narrow);

            Sprintf16(wide, L"%s", GetSaveArea(0x11ac197)->GetPath());
            Utf16ToUtf8(narrow, 0x104, wide, -1);
            sprintf(mCurrPathname, "%s", narrow);

            uint32_t width, height;
            TryGetUIntProperty(gAppProperties, 0x456f975, &width);
            TryGetUIntProperty(gAppProperties, 0x456f976, &height);
            mWidth = width;
            mHeight = height;
            mTime = 120.0f;
            GetBoolProperty(gAppProperties, 0x456f97a, &mExcludeUI);
            mMovieSystem->StartRecording(EA::ConvertToString16(mCurrFilename, -1).c_str(), &mWidth);
            SetStatusText(true, mCurrFilename);
            mRecording = true;
            mIndicator = false;
            mUI->SetUIGroupVisible(0x3f434ac, true);
            mUI->SetUIGroupVisible(0x3fc1740, false);
            FUN_0063b760();
            mIndicatorTimer = 0;
            GetMessageServer()->PostMessage(0x52f180, (void*)0x21, 0);
        }
        return true;
    case 0x5652348:
        mUI->HideYouTubeLoginDialog();
        mDialogInProgress = 0;
        mUI->GetYTUsername(&mYTUsername);
        mUI->GetYTPassword(&mYTPassword);
        CreateConnectingDialog();
        CheckYouTubeRegistration();
        return true;
    case 0x5665f58: {
        bool on = GetConfigManager()->GetValue(0x5664a8b) != 0;
        GetConfigManager()->SetValue(0x5664a8b, !on);
        return true;
    }
    case 0x56be960:
        FUN_0063b8b0();
        return true;
    case 0x5b5bd80:
        mUI->HideYouTubeLoginDialog();
        mDialogInProgress = 0;
        FUN_0063cd30();
        return true;
    case 0x5b5ef51:
        mUI->HideMovieSavedDialogCustom();
        if (!auth->v58()) {
            mDialogInProgress = 8;
            CalloutMessageBox(&gCalloutWhere, &gKey15247ec);
        } else if (auth->v24()) {
            mDialogInProgress = 7;
            CalloutMessageBox(&gCalloutWhere, &gKey15247e0);
        } else if (GetYTPrompt()) {
            FUN_0063bec0();
            return true;
        } else {
            CreateConnectingDialog();
            CheckYouTubeRegistration();
            return true;
        }
        goto callout;
    case 0x5b5ef52:
        mUI->HideMovieSavedDialogCustom();
        return true;
    case 0x5b5ef53:
        if (!IsLocaleEnglish()) {
            mUI->HideMovieSavedDialogCustom();
            mDialogInProgress = 0xd;
            CalloutMessageBox(&gCalloutWhere, &gKey1524810);
            goto callout;
        }
        OpenBrowser(L"http://youtube.com/t/terms", 1);
        break;
    case 0x5baefc8:
        if (!IsLocaleEnglish()) {
            mUI->HideYouTubeLoginDialog();
            mDialogInProgress = 0xc;
            CalloutMessageBox(&gCalloutWhere, &gKey1524810);
            goto callout;
        }
        OpenBrowser(L"http://www.youtube.com/signup", 1);
        break;
    }
    return true;
callout:
    BeginProfScope(0, 1)->End();
    return true;
}
