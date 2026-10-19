// src/game/SPEditors/SPSubModeMovie.cpp -- migrated from slice(s) s0063d9e0, s0063caf0, s0063ba50, s0063aa90 by tools/migrate/rewrite.py
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
#include "EA/Messaging/AutoHandler.h"
#include "EA/Messaging/IHandler.h"
#include "SP/cEditorYouTubeAuthenticationMessage.h"
#include "SP/cEditorYouTubeVideoUploadMessage.h"
#include "cSPVector4.h"
#include <string.h>
#include <stdio.h>
#include "SP/cSPEditorNaming.h"
#include "SP/cSPEditorUI.h"
#include "EA/DateTime/DateTime.h"
#include "SP/cIMovieSystem.h"
#include "SP/cSPPlayModeSubModePhoto.h"
#include "SP/cPropertyList.h"

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
extern char gDialogText[];   // 0x013EC468
extern const float gRotationSpeed;   // 0x013FA9C8 (-4.18879f)
extern const char* const gFmtMsg;      // 0x01524438
extern const char* const gFmtMsgNoArg; // 0x0152443C
extern const wchar_t* const gYTPropName;   // 0x01524440
extern char gMsgA[], gMsgB[];   // 0x0152481C, 0x015247A4
extern const wchar_t gFmtW[];    // 0x013F5C04
extern const char gFmtS[];       // 0x013F5B98
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
void* operator new(size_t size, int align, const char* name, void* alloc);   // 0x009512D0
inline void* operator new(size_t, void* p) { return p; }
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
struct cSPUILayout_s0063_ba50 {   // 0x18 bytes (retail)
    uint32_t pad[6];
    IWindow_s0063_ba50* FindWindowByID(uint32_t id, bool recurse);   // 0x008105B0
    void Shutdown(bool b);                                // 0x00811AD0
    cSPUILayout_s0063_ba50();                                        // 0x00810000
};
struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void PostMessage(uint32_t id, void* data, int flags);   // +0x14
};
IMessageServer* GetMessageServer();   // 0x0067DCC0
struct cSPVector4_s0063_ba50 { float x, y, z, w; cSPVector4_s0063_ba50(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };
float GetElapsedSeconds();                          // 0x00805080
void  BeginModal(IWindow_s0063_ba50* w, int a, int b);         // 0x008099A0 (cdecl)
void  EndModal(IWindow_s0063_ba50* w, int a, int b);           // 0x00809C50 (cdecl)
struct IWinProc {
    virtual int AddRef(); virtual int Release();
    virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06();
    virtual void s07(); virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
};
struct ISerializable { virtual int s0(); virtual int s1(); };
struct CustomWinProc : IWinProc, ISerializable {
    int mRefCount;
    CustomWinProc() : mRefCount(0) {}
};
struct cConnectingDialog_s0063_ba50 : CustomWinProc {   // 0x38 bytes
    AutoRef<IWindow_s0063_ba50> mpWindow;   // +0xC
    float mStartTime;            // +0x10
    float mTimeout;              // +0x14
    bool mEndConnecting;         // +0x18
    bool mEndConnected;          // +0x19
    cSPVector4_s0063_ba50 mRotation;        // +0x1C
    cSPUILayout_s0063_ba50 mLayout;         // +0x2C

    void SetDialogText(int a);   // 0x0063B640
    void Show(int a);
    bool SetWindow(IWindow_s0063_ba50* w);
    void HandleResults(bool b);
    void End(bool b);
    bool Update(void* p);
    bool Init();   // 0x0063B5C0
    cConnectingDialog_s0063_ba50() : mTimeout(2.5f), mEndConnecting(false), mEndConnected(false), mRotation(0.0f, 0.0f, 1.0f, 0.0f) { }
    bool HandleUIMessage(void* a, void* msg);
    virtual bool Slot32(void* a);
};
void  SetAnimProps(IWindow_s0063_ba50* w, cSPVector4_s0063_ba50* rot);   // 0x00808230 (cdecl)
struct cUIMessage { IWindow_s0063_ba50* mpSource; uint32_t pad; uint32_t mType; };
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
struct IConfigManager {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual void SetBool(uint32_t id, bool v);      // +0x2C
    virtual int GetBool(uint32_t id);              // +0x30
};
IConfigManager* GetConfigManager_s0063_ba50();                 // 0x0067DD30
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
                 virtual const eastl::string16_s0063_ba50& GetLanguage(); };   // +0x14
ILocale* GetLocale();                                // 0x0067DE40
bool StrEq(const eastl::string16_s0063_ba50& a, const wchar_t* b);   // 0x006AB760 (cdecl)
void* GetAllocator();   // 0x009512C0
extern AutoRef<cConnectingDialog_s0063_ba50> gConnectingDialog;   // 0x015F8A70
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

    cSPPlayModeSubModeMovie_s0063_ba50();
    virtual ~cSPPlayModeSubModeMovie_s0063_ba50();
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
int Sprintf16(wchar_t* dst, const wchar_t* fmt, ...);                                    // 0x009399C0 (cdecl)
void StrncpyUTF8ToUTF16(char* dst, int dstSize, const wchar_t* src, int srcLen);         // 0x0093CF10 (cdecl)
struct ISaveArea { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
                   virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
                   virtual const wchar_t* GetPath(); };   // +0x28
ISaveArea* GetSaveArea_s0063_ba50(uint32_t id);                                                     // 0x006B1F90 (cdecl)
struct IMovieSystem { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
                      virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
                      virtual void s10(); virtual void s11(); virtual void s12();
                      virtual int GetMovieName(); };  // +0x34
// ---- items of slice s0063ba50 end

// ---- items of slice s0063caf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IPropList {
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
    virtual bool GetProp(uint32_t id, void** out);   // +0x24
};
extern IPropList* gAppProperties;   // 0x015FD918
extern const wchar_t gDfltText[];   // 0x013EC468
extern const wchar_t gDflt13fe144[];   // 0x013FE144
extern const wchar_t gFmt13fe12c[];    // 0x013FE12C
extern void* gCalloutWhere;                                          // 0x0152481C
extern const wchar_t gUrlDelims[];   // 0x013FA030
extern char* gRecordingStopped;                       // 0x0152443C
struct IWindow_s0063_caf0;
struct IOther;
struct IControl;
struct cSPEditorUI_s0063_caf0;
void operator delete(void* p);   // 0x00F47380
namespace eastl {
extern char    gEmptyString8[1];
}
namespace eastl {
template <typename T> struct EmptyStr_s0063_caf0;
}
namespace eastl {
template <> struct EmptyStr_s0063_caf0<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
}
namespace eastl {
template <> struct EmptyStr_s0063_caf0<char>    { static char*    Get() { return gEmptyString8; } };
}
namespace eastl {
template <typename T>
struct allocator_s0063_caf0 {
    void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
template <typename T, typename Allocator = allocator_s0063_caf0<T> >
class basic_string_s0063_caf0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    basic_string_s0063_caf0() : mpBegin(EmptyStr_s0063_caf0<T>::Get()), mpEnd(EmptyStr_s0063_caf0<T>::Get()), mpCapacity(EmptyStr_s0063_caf0<T>::Get() + 1) {}
    ~basic_string_s0063_caf0() { DeallocateSelf(); }
    const T* c_str() const { return mpBegin; }
    int sprintf(const char* fmt, ...);   // 0x00472FE0
    int append_sprintf(const char* fmt, ...);   // 0x005F9450
    void clear() { if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; } }
    void DeallocateSelf() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin); }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
};
}
namespace eastl {
typedef basic_string_s0063_caf0<char> string_s0063_caf0;
}
namespace eastl {
typedef basic_string_s0063_caf0<wchar_t> string16_s0063_caf0;
}
namespace EA {
eastl::string16_s0063_caf0 ConvertToString16_s0063_caf0(const char* p, int length = -1);   // 0x0093C5A0
}
namespace EA {
eastl::string16_s0063_caf0 ConvertToString16_s0063_caf0(const eastl::string_s0063_caf0& s);           // 0x0093C6D0
}
struct cAppModeEditorBase_s0063_caf0 {
    char pad78[0x78];
    cSPEditorUI_s0063_caf0* mpEditorUI;        // +0x78
    char pad7c[0x358 - 0x7c];
    void* mPaintPaletteObject;      // +0x358
};
struct cSPEditorUI_s0063_caf0 {
    char pad[0x14];
    void EnableUIButton(uint32_t id, bool b);     // 0x005DC610
    IWindow_s0063_caf0* FindWindowByID(uint32_t id);         // 0x005DC310
};
struct cSPUILayout_s0063_caf0 {
    char pad[0x18];
    bool IsVisible();                                         // 0x00810070
    IWindow_s0063_caf0* FindWindowByID(uint32_t id, bool recurse);       // 0x008105B0
    void Shutdown(bool b);                                    // 0x00811AD0
};
struct IOther {
virtual void o00();
virtual void o01();
virtual void o02();
virtual void o03();
virtual void o04();
virtual void o05();
virtual void o06();
virtual void o07();
virtual void o08();
virtual void o09();
virtual void o10();
virtual void o11();
virtual void o12();
virtual void o13();
virtual void o14();
virtual void o15();
virtual void o16();
virtual void o17();
virtual void o18();
virtual void o19();
virtual void o20();
virtual void o21();
virtual void o22();
virtual void o23();
virtual void o24();
virtual void o25();
virtual void o26();
virtual void o27();
virtual void o28();
virtual void o29();
virtual void o30();
virtual void o31();
virtual void o32();
virtual void o33();
virtual void o34();
virtual void o35();
virtual void o36();
virtual void o37();
virtual void o38();
virtual void o39();
virtual void o40();
virtual void o41();
virtual void o42();
virtual void o43();
virtual void o44();
virtual void o45();
virtual void o46();
virtual void o47();
virtual void o48();
virtual void o49();
virtual void o50();
virtual void o51();
virtual void o52();
virtual void o53();
virtual void o54();
    virtual void Attach(IWindow_s0063_caf0* p);              // +0xDC
};
struct IWindow_s0063_caf0 {
    virtual void v00();
    virtual int Release();                                    // +0x04
    virtual void v02();
    virtual IControl* v03(uint32_t id);                       // +0x0C
    virtual IOther* GetOther();                               // +0x10
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
    virtual uint8_t v10();                                    // +0x28
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
    virtual const wchar_t* GetText();                         // +0x3C
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
    virtual void SetFlag(int flag, int on);                   // +0x7C
    virtual void SetCaption(const wchar_t* text);             // +0x80
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
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
virtual void v54(IWindow_s0063_caf0* p);
    virtual void v55(IWindow_s0063_caf0* p);                             // +0xDC
};
struct IControl {
virtual void c00();
virtual void c01();
virtual void c02();
virtual void c03();
virtual void c04();
virtual void c05();
virtual void c06();
virtual void c07();
virtual void c08();
virtual void c09();
    virtual void SetMode(int a, int b);                       // +0x28
};
struct cSPPlayModeUI_s0063_caf0 {
    char pad0[0xC];
    cAppModeEditorBase_s0063_caf0* mpEditor;       // +0x0C
    void* mpPlayMode;                   // +0x10
    cSPUILayout_s0063_caf0 mLayout;                // +0x14
    cSPUILayout_s0063_caf0 mCameraControlsLayout;  // +0x2C
    bool mbLayoutInit;                  // +0x44
    char pad45[0x64 - 0x45];
    IWindow_s0063_caf0* mpMovieSavedDialog;        // +0x64

    IWindow_s0063_caf0* FindPlayModeUIWindow(uint32_t id);               // 0x00634DC0
    void SetUIGroupVisible(uint32_t id, bool on);             // 0x00635760
    void EnablePhotoViewerButton(bool b);                     // 0x00636320
    void HideMovieSavedDialogCustom();                        // 0x006364A0
    bool DoMessageInternal(uint32_t a, void* msg);            // 0x00636560
    bool Shutdown();                                          // 0x006373E0
    void SetYTUsername(const eastl::string_s0063_caf0& s);               // 0x006374B0
    void SetYTPassword(const eastl::string_s0063_caf0& s);               // 0x00637510
    void GetEditorText(uint32_t id, eastl::string_s0063_caf0* out);      // 0x006377D0
    void GetYTUsername(eastl::string_s0063_caf0* out);                   // 0x00637800
    void GetYTPassword(eastl::string_s0063_caf0* out);                   // 0x00637830
    void ShowSendEmailDialog();                               // 0x00637860
    void SendVideoURLInfoToServer();                          // 0x00637C90
    void ResetSendEmailWindow();                              // 0x00635520
    void HideYouTubeLoginDialog();                            // 0x00636260
};
struct cEditorYouTubeAuthenticationMessage_s0063_caf0 {   // 0x34
    eastl::string_s0063_caf0 mUsername;
    eastl::string_s0063_caf0 mPassword;
    eastl::string_s0063_caf0 mSource;
    bool mCheckRegistration;
    ~cEditorYouTubeAuthenticationMessage_s0063_caf0();
};
struct IMessageServer_s0063_caf0 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
    virtual void PostMessage(uint32_t id, void* data, int flags);   // +0x14
virtual void s6();
virtual void s7();
virtual void s8();
    virtual void AddHandler(void* handler, uint32_t id);            // +0x24
};
IMessageServer_s0063_caf0* GetMessageServer_s0063_caf0();   // 0x0067DCC0
struct cProp {
    char pad12[0x12]; short mType;
    char* GetBool();        // 0x0041E920
    uint32_t* GetUInt();    // 0x0041EA00
    float* GetFloat();      // 0x0041EA70
};
struct IPropList_s0063_caf0 {
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
    virtual bool GetProp(uint32_t id, void** out);   // +0x24
    bool GetDescription(uint32_t id);                // 0x006A25A0 (non-virtual, ret 4)
};
extern IPropList_s0063_caf0* gAppProperties_s0063_caf0;   // 0x015FD918
struct IMovieSystem_s0063_caf0 {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
virtual void m10();
virtual void m11();
    virtual bool IsRecording();                                      // +0x30
};
struct IAuthManager_s0063_caf0 {
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
    virtual bool v24();                                              // +0x24
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
    virtual void v44();                                              // +0x44
virtual void a18();
virtual void a19();
virtual void a20();
virtual void a21();
    virtual bool v58();                                              // +0x58
};
IAuthManager_s0063_caf0* GetAuthManager_s0063_caf0();   // 0x00607A60
struct IApp15e4ef0 {
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
virtual void a19();
virtual void a20();
virtual void a21();
    virtual void v58();                                              // +0x58
};
extern IApp15e4ef0* gApp15e4ef0;   // 0x015E4EF0
struct cMovieUI : cSPPlayModeUI_s0063_caf0 {
    void SetYTPrompt(bool b);                  // 0x00635310
    void ShowMovieSavedDialogCustom();         // 0x00638430
    bool FUN_00634b00();                       // 0x00634B00
    void ShowSendEmail(void* p);               // 0x00637860 (ret 4)
};
struct cTextTable {   // *0x015F7CF4
    char pad0[0x18];
    const wchar_t* m18;
    const wchar_t* m1c;
    char pad20[0x30 - 0x20];
    const wchar_t* m30;
    char pad34[0x58 - 0x34];
    const wchar_t* m58;
};
extern cTextTable* gTextTable;   // 0x015F7CF4
namespace SP {
class cString_s0063_caf0 {
public:
    cString_s0063_caf0();                                                       // 0x006B5060
    ~cString_s0063_caf0();                                                      // 0x006B5240
    void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* dflt);   // 0x006B54B0
    const wchar_t* GetText();                                        // 0x006B55C0
    char pad[0x14];
};
}
void __cdecl WStr_Format(void* str, const wchar_t* fmt, ...);        // 0x0041E050
struct SubModeParams { char pad[0x1c]; cMovieUI* mUI; };
struct cMsg;
struct cSPPlayModeSubModeMovie_s0063_caf0;
struct cSubModeBase {
    char pad[0x18];
    void Init(SubModeParams* p);   // 0x0063B270 (non-virtual call, ret 4)
};
struct cSPPlayModeSubModeMovie_s0063_caf0 : cSubModeBase {
    IMovieSystem_s0063_caf0* mMovieSystem;     // +0x18
    uint32_t mWidth;                // +0x1C
    uint32_t mHeight;               // +0x20
    float mFPS;                     // +0x24
    float mTime;                    // +0x28
    float mQuality;                 // +0x2C
    bool mAudio;                    // +0x30
    char pad31[3];
    cMovieUI* mUI;                  // +0x34
    char mCurrFilename[260];        // +0x38
    char mCurrPathname[260];        // +0x13C
    eastl::string16_s0063_caf0 mTableA[260];   // +0x240
    eastl::string16_s0063_caf0 mTableB[260];   // +0x1280
    bool mb22c0;                    // +0x22C0
    bool mb22c1;                    // +0x22C1
    char pad22c2[0x22c8 - 0x22c2];
    uint32_t mField22c8;            // +0x22C8
    uint32_t mField22cc;            // +0x22CC
    IMessageServer_s0063_caf0* mAutoServer;    // +0x22D0
    void* mAutoHandler;             // +0x22D4
    const uint32_t* mAutoTable;     // +0x22D8
    uint32_t mAutoCount;            // +0x22DC
    uint32_t mAutoE;                // +0x22E0
    int mDialogInProgress;          // +0x22E4
    char pad22e8[0x22fc - 0x22e8];
    uint32_t mField22fc;            // +0x22FC
    char pad2300[0x231c - 0x2300];
    bool mb231c;                    // +0x231C
    bool mb231d;                    // +0x231D
    bool mb231e;                    // +0x231E
    bool mb231f;                    // +0x231F
    bool mb2320;                    // +0x2320
    bool mb2321;                    // +0x2321
    char pad2322[0x234c - 0x2322];
    uint32_t mField234c;            // +0x234C
    char pad2350[0x235d - 0x2350];
    bool mb235d;
    bool mb235e;

    void CheckYouTubeRegistration();   // 0x0063CED0
    void FUN_0063cf90();               // 0x0063CF90
    void FUN_0063caf0(SubModeParams* p);
    __declspec(noinline) void FUN_0063cd30();
    void ConstructYouTubeVideoUploadXMLRequest(eastl::string_s0063_caf0* out);   // 0x0063D050
    static bool ConstructVideoURL(eastl::string16_s0063_caf0* in, eastl::string16_s0063_caf0* out);   // 0x0063D170
    void FUN_0063d2f0();
    void FUN_0063b760();  // 0x0063b760 (cSPPlayModeSubModeMovie::FUN_0063b760)
    void ToggleRecordingIndicator(char b);          // 0x0063D910
    void LoadYouTubeCredentials();     // 0x0063C7F0
    void OnMovieRecorded();            // 0x0063C8F0
    void ShowMovieSavedDialog();       // 0x0063C640
    void ShowYouTubeLoginDialog();     // 0x0063BEC0
    void SetStateB();                  // 0x0063B910
    static bool GetYTPrompt();         // 0x0063B890
};
struct cStrObj { char pad[0xc]; const char* mStr; };
struct cMsg { uint32_t f00, f04, f08, f0c, f10, f14, f18, f1c, f20; };
extern char gKey15247e0_s0063_caf0[12], gKey15247ec_s0063_caf0[12];
void __cdecl CalloutMessageBox(void* where, const void* key);        // 0x00809DB0
void __cdecl OpenBrowser(const wchar_t* url, int flag);              // 0x00935FB0
struct CAch { void AutoTest(); };                                    // 0x00676E90
CAch* __stdcall AchievementsController(uint32_t a, int b);           // 0x00675250
struct cAppPropsX { char pad[0x3c]; struct { char pad[0x118]; int f118; }* p3c; };
struct WStr16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
    WStr16() : mpBegin(eastl::gEmptyString16), mpEnd(eastl::gEmptyString16), mpCapacity(eastl::gEmptyString16 + 1) {}
    ~WStr16() { if ((mpCapacity - mpBegin) > 1 && mpBegin) operator delete(mpBegin); }
    WStr16 substr(uint32_t pos, uint32_t n) const;                 // 0x00453D20 (thiscall, hidden return, ret 12)
    void assign(const wchar_t* b, const wchar_t* e);               // 0x00423650 (thiscall, ret 8)
    WStr16& operator=(const WStr16& o) { if (&o != this) assign(o.mpBegin, o.mpEnd); return *this; }
};
const wchar_t* FindLastOf16(const wchar_t* first, const wchar_t* last, const wchar_t* sb, const wchar_t* se);   // 0x005728F0 (cdecl)
static inline uint32_t StrLenB16(const wchar_t* p) { const wchar_t* p1 = p + 1; const wchar_t* q = p; while (*q++) {} return (uint32_t)(q - p1); }
static inline const uint32_t& MinRef(const uint32_t& a, const uint32_t& b) { return (b > a) ? a : b; }
struct cMovieHandler {   // IHandler subobject at movie+0x14: offsets are movie offsets minus 0x14
    void* mVptr;
    char pad04[0x20 - 4];
    cMovieUI* mUI;                  // +0x20
    char pad24[0x22d0 - 0x24];
    int mState;                     // +0x22D0
    char pad22d4[0x22d8 - 0x22d4];
    eastl::string_s0063_caf0 mAuthToken;       // +0x22D8
    eastl::string_s0063_caf0 mUsername;        // +0x22E8
    WStr16 mURL;                    // +0x22F8
    bool mb2308, mb2309, mb230a, mb230b, mb230c, mb230d, mb230e, mb230f, mb2310;
    char pad2311[3];
    uint32_t mStatusCode;           // +0x2314
    eastl::string_s0063_caf0 mStatusMsg;       // +0x2318
    char pad2328[0x2349 - 0x2328];
    bool mb2349, mb234a;

    cSPPlayModeSubModeMovie_s0063_caf0* Movie() { return (cSPPlayModeSubModeMovie_s0063_caf0*)((char*)this - 0x14); }
    bool HandleMessage(uint32_t id, cMsg* msg);   // 0x0063D2F0
};
void KillSetiEffects(uint32_t id, uint32_t state);   // 0x00435ED0 (cdecl)
struct IAudioSystem {
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
    virtual uint32_t v8();                            // +0x20
};
IAudioSystem* GetSystemAT();                          // 0x00A206F0
#define CLOSE_DIALOG do { mState = 0; BeginProfScope(1, 1)->End(); return true; } while (0)
// ---- items of slice s0063caf0 end

// ---- items of slice s0063d9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)

struct IWindow_s0063_d9e0;
struct IOther_s0063_d9e0;
struct cSPEditorUI_s0063_d9e0;
namespace eastl {
template <typename T> struct EmptyStr_s0063_d9e0;
}
namespace eastl {
template <> struct EmptyStr_s0063_d9e0<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
}
namespace eastl {
template <> struct EmptyStr_s0063_d9e0<char>    { static char*    Get() { return gEmptyString8; } };
}
namespace eastl {
template <typename T>
struct allocator_s0063_d9e0 {
    void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
template <typename T, typename Allocator = allocator_s0063_d9e0<T> >
class basic_string_s0063_d9e0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    basic_string_s0063_d9e0() : mpBegin(EmptyStr_s0063_d9e0<T>::Get()), mpEnd(EmptyStr_s0063_d9e0<T>::Get()), mpCapacity(EmptyStr_s0063_d9e0<T>::Get() + 1) {}
    ~basic_string_s0063_d9e0() { DeallocateSelf(); }
    const T* c_str() const { return mpBegin; }
    int sprintf(const char* fmt, ...);   // 0x00472FE0
    int append_sprintf(const char* fmt, ...);   // 0x005F9450
    void clear() { if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; } }
    void DeallocateSelf() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin); }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
};
}
namespace eastl {
typedef basic_string_s0063_d9e0<char> string_s0063_d9e0;
}
namespace eastl {
typedef basic_string_s0063_d9e0<wchar_t> string16_s0063_d9e0;
}
namespace EA {
eastl::string16_s0063_d9e0 ConvertToString16_s0063_d9e0(const char* p, int length = -1);   // 0x0093C5A0
}
namespace EA {
eastl::string16_s0063_d9e0 ConvertToString16_s0063_d9e0(const eastl::string_s0063_d9e0& s);           // 0x0093C6D0
}
struct cAppModeEditorBase_s0063_d9e0 {
    char pad78[0x78];
    cSPEditorUI_s0063_d9e0* mpEditorUI;        // +0x78
    char pad7c[0x358 - 0x7c];
    void* mPaintPaletteObject;      // +0x358
};
struct cSPEditorUI_s0063_d9e0 {
    char pad[0x14];
    void EnableUIButton(uint32_t id, bool b);     // 0x005DC610
    IWindow_s0063_d9e0* FindWindowByID(uint32_t id);         // 0x005DC310
};
struct cSPUILayout_s0063_d9e0 {
    char pad[0x18];
    bool IsVisible();                                         // 0x00810070
    IWindow_s0063_d9e0* FindWindowByID(uint32_t id, bool recurse);       // 0x008105B0
    void Shutdown(bool b);                                    // 0x00811AD0
};
struct IOther_s0063_d9e0 {
virtual void o00();
virtual void o01();
virtual void o02();
virtual void o03();
virtual void o04();
virtual void o05();
virtual void o06();
virtual void o07();
virtual void o08();
virtual void o09();
virtual void o10();
virtual void o11();
virtual void o12();
virtual void o13();
virtual void o14();
virtual void o15();
virtual void o16();
virtual void o17();
virtual void o18();
virtual void o19();
virtual void o20();
virtual void o21();
virtual void o22();
virtual void o23();
virtual void o24();
virtual void o25();
virtual void o26();
virtual void o27();
virtual void o28();
virtual void o29();
virtual void o30();
virtual void o31();
virtual void o32();
virtual void o33();
virtual void o34();
virtual void o35();
virtual void o36();
virtual void o37();
virtual void o38();
virtual void o39();
virtual void o40();
virtual void o41();
virtual void o42();
virtual void o43();
virtual void o44();
virtual void o45();
virtual void o46();
virtual void o47();
virtual void o48();
virtual void o49();
virtual void o50();
virtual void o51();
virtual void o52();
virtual void o53();
virtual void o54();
    virtual void Attach(IWindow_s0063_d9e0* p);              // +0xDC
};
struct IWindow_s0063_d9e0 {
    virtual void v00();
    virtual int Release();                                    // +0x04
    virtual void v02();
    virtual IControl* v03(uint32_t id);                       // +0x0C
    virtual IOther_s0063_d9e0* GetOther();                               // +0x10
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
    virtual uint8_t v10();                                    // +0x28
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
    virtual const wchar_t* GetText();                         // +0x3C
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
    virtual void SetFlag(int flag, int on);                   // +0x7C
    virtual void SetCaption(const wchar_t* text);             // +0x80
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
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
virtual void v54(IWindow_s0063_d9e0* p);
    virtual void v55(IWindow_s0063_d9e0* p);                             // +0xDC
};
struct cSPPlayModeUI_s0063_d9e0 {
    char pad0[0xC];
    cAppModeEditorBase_s0063_d9e0* mpEditor;       // +0x0C
    void* mpPlayMode;                   // +0x10
    cSPUILayout_s0063_d9e0 mLayout;                // +0x14
    cSPUILayout_s0063_d9e0 mCameraControlsLayout;  // +0x2C
    bool mbLayoutInit;                  // +0x44
    char pad45[0x64 - 0x45];
    IWindow_s0063_d9e0* mpMovieSavedDialog;        // +0x64

    IWindow_s0063_d9e0* FindPlayModeUIWindow(uint32_t id);               // 0x00634DC0
    void SetUIGroupVisible(uint32_t id, bool on);             // 0x00635760
    void EnablePhotoViewerButton(bool b);                     // 0x00636320
    void HideMovieSavedDialogCustom();                        // 0x006364A0
    bool DoMessageInternal(uint32_t a, void* msg);            // 0x00636560
    bool Shutdown();                                          // 0x006373E0
    void SetYTUsername(const eastl::string_s0063_d9e0& s);               // 0x006374B0
    void SetYTPassword(const eastl::string_s0063_d9e0& s);               // 0x00637510
    void GetEditorText(uint32_t id, eastl::string_s0063_d9e0* out);      // 0x006377D0
    void GetYTUsername(eastl::string_s0063_d9e0* out);                   // 0x00637800
    void GetYTPassword(eastl::string_s0063_d9e0* out);                   // 0x00637830
    void ShowSendEmailDialog();                               // 0x00637860
    void SendVideoURLInfoToServer();                          // 0x00637C90
    void ResetSendEmailWindow();                              // 0x00635520
    void HideYouTubeLoginDialog();                            // 0x00636260
};
struct Key12 { uint32_t a, b, c; };
struct IMovieSystem_s0063_d9e0 {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
    virtual void m10();
    virtual void StartRecording(const wchar_t* name, void* info);   // +0x2c
    virtual bool IsRecording();                                      // +0x30
    virtual void m13();
    virtual void StopRecording();                                    // +0x38
};
struct IAuthManager {
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
    virtual bool v24();                                              // +0x24
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
virtual void a19();
virtual void a20();
virtual void a21();
    virtual bool v58();                                              // +0x58
};
IAuthManager* GetAuthManager();                                      // 0x00607A60
struct IConfigMgr {
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
virtual void c5();
virtual void c6();
virtual void c7();
virtual void c8();
virtual void c9();
    virtual void c10();
    virtual void SetValue(uint32_t id, int v);                       // +0x2c
    virtual int GetValue(uint32_t id);                               // +0x30
virtual void c13();
virtual void c14();
    virtual void Slot3c();                                           // +0x3c
};
IConfigMgr* GetConfigManager_s0063_d9e0();                                      // 0x0067DD30
struct ISaveArea_s0063_d9e0 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
    virtual const char* GetPath();                                   // +0x28
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
    virtual void SetName(const wchar_t* name, int a, int b);         // +0x54 (index 21)
};
ISaveArea_s0063_d9e0* __cdecl GetSaveArea_s0063_d9e0(uint32_t id);                         // 0x006B1F90

void __cdecl Utf16ToUtf8(char* dst, unsigned n, const wchar_t* src, int len);   // 0x0093CF10
struct IPropList;
bool __cdecl TryGetUIntProperty(IPropList* pl, uint32_t id, uint32_t* out);   // 0x00410370
bool __cdecl GetBoolProperty(IPropList* pl, uint32_t id, bool* out);          // 0x00407190
void __cdecl CalloutMessageBox(void* where, const Key12* key);       // 0x00809DB0

extern Key12 gKey15247e0, gKey15247ec, gKey1524810;
namespace EA {
namespace DateTime {
struct DateTime_s0063_d9e0 {
    int64_t mnSeconds;
    DateTime_s0063_d9e0(int timeFrame);                                         // 0x0092E3D0
    uint32_t GetParameter(int which);                                // 0x0092DF80
};
}
}
namespace SP {
class cString_s0063_d9e0 {
public:
    cString_s0063_d9e0();                                                       // 0x006B5060
    ~cString_s0063_d9e0();                                                      // 0x006B5240
    void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* dflt);   // 0x006B54B0
    const wchar_t* GetText();                                        // 0x006B55C0
    char pad[0x14];
};
}
struct cDateStrings {
    char pad0[0x34];
    const wchar_t* mMessage;   // +0x34
    char pad38[0x44 - 0x38];
    const wchar_t* mYear;   // +0x44
    const wchar_t* mMonth;  // +0x48
    const wchar_t* mDay;    // +0x4C
    const wchar_t* mTime;   // +0x50
    const wchar_t* mPrefix; // +0x54
};
extern cDateStrings* gDateStrings;                                   // 0x015F7CF4
struct cSPPlayModeSubModeMovie_s0063_d9e0 {
    char pad00[0x18];
    IMovieSystem_s0063_d9e0* mMovieSystem;     // +0x18
    uint32_t mWidth;                // +0x1C
    uint32_t mHeight;               // +0x20
    char pad24[4];
    float mTime;                    // +0x28
    char pad2c[5];
    bool mExcludeUI;                // +0x31
    char pad32[2];
    cSPPlayModeUI_s0063_d9e0* mUI;             // +0x34
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
    eastl::string_s0063_d9e0 mYTUsername;      // +0x22FC
    char pad230c[0x231c - 0x230c];
    bool mRegisterSuccess;          // +0x231C
    bool mRegisterCheckComplete;    // +0x231D
    bool mDoRegisterCheck;          // +0x231E
    bool mLoginSuccess;             // +0x231F
    bool mLoginCheckComplete;       // +0x2320
    bool mDoLoginCheck;             // +0x2321
    bool mVideoUploadSuccess;       // +0x2322
    bool mDoVideoUpload;            // +0x2323
    bool mVideoUploadComplete;      // +0x2324
    bool mEnableYouTubeVideoUpload; // +0x2325
    char pad2326[2];
    uint32_t mYTStatusCode;         // +0x2328
    char pad232c[0x234c - 0x232c];
    eastl::string_s0063_d9e0 mYTPassword;      // +0x234C

    bool HandleButton(int id);                       // 0x0063E100
    void ToggleRecordingIndicator(char b);           // 0x0063D910
    void CheckYouTubeRegistration();                 // 0x0063CED0
    void FUN_0063cd30();
    void FUN_0063de20(int dt);                       // 0x0063DE20
    void FUN_0063dc40();
    void FUN_0063d9e0();
    void FUN_0063cf90();  // 0x0063cf90 (cSPPlayModeSubModeMovie::FUN_0063cf90)
    void SetState2();                                // 0x0063B7B0
    void SetState4();                                // 0x0063B7F0
    void SetState5();                                // 0x0063B820
    void SetState6();                                // 0x0063B860
    static void ShowLoginToYouTubeDialog();          // 0x0063BD50
    static void ShowYouTubeUploadVideoDialog();      // 0x0063BE00
    void FUN_0063b760();  // 0x0063b760 (cSPPlayModeSubModeMovie::FUN_0063b760)
    bool FUN_0063b950();
    bool FUN_0063b9a0();
    void FUN_0063b9f0(bool v);  // 0x0063b9f0 (cSPPlayModeSubModeMovie::FUN_0063b9f0)
    void FUN_0063b8b0();
    void FUN_0063bec0();
    void SetStatusText(bool withArg, const char* arg);   // 0x0063C590
    static bool GetYTPrompt();                       // 0x0063B890
    static bool IsLocaleEnglish();                   // 0x0063C0A0
};
void CreateConnectingDialog();                       // 0x0063BC70
void __cdecl DestroyConnectingDialog(bool b);        // 0x0063C060
struct cSPPlayModeUIExt {
    void FUN_00635350(uint32_t a, uint32_t b);       // 0x00635350
    void SetTagField(uint32_t v);                    // 0x006353E0
    void SetEnabled(uint32_t id, bool on);           // 0x00634EF0
    void ShowEditor();                               // 0x00635380
};
// ---- items of slice s0063d9e0 end

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
bool SP::cSPPlayModeSubModeMovie::OnKeyDown(unsigned int key, unsigned int mods)
{
    if (key == 0xd && mDialogInProgress == 3) {
        HandleButton(0x5652348);
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

// @ 0x0063ba50
void cConnectingDialog_s0063_ba50::Show(int a)
{
    SetDialogText(a);
    IWindow_s0063_ba50* w = mLayout.FindWindowByID(0x42e2e38, true);
    if (w)
        w->SetCaption((const wchar_t*)gDialogText);
    w = mLayout.FindWindowByID(0x431e538, true);
    if (w)
        BeginModal(w, 0, 1);
}

// @ 0x0063bab0
bool cConnectingDialog_s0063_ba50::SetWindow(IWindow_s0063_ba50* w)
{
    mpWindow = w;
    mStartTime = GetElapsedSeconds();
    return true;
}

// @ 0x0063baf0
void cConnectingDialog_s0063_ba50::HandleResults(bool b)
{
    EndModal(mpWindow.mpObject, 0, 1);
    mpWindow.mpObject->RemoveWinProc(this);
    mpWindow = 0;
    mLayout.Shutdown(true);
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

// @ 0x0063bc70
void CreateConnectingDialog()
{
    BeginProfScope(0, 1)->End();
    cConnectingDialog_s0063_ba50* d = new (4, "UI/cConnectionDialog", GetAllocator()) cConnectingDialog_s0063_ba50();
    gConnectingDialog = d;
    if (gConnectingDialog.mpObject->Init())
        gConnectingDialog.mpObject->Show(0);
}

// @ 0x0063bd50
void cSPPlayModeSubModeMovie_s0063_ba50::ShowLoginToYouTubeDialog()
{
    BeginProfScope(0, 1)->End();
    cSPUILayout_s0063_ba50* layout = &gConnectingDialog.mpObject->mLayout;
    IWindow_s0063_ba50* w = layout->FindWindowByID(0x5d2bdf8, true);
    w->SetFlag(1, 0);
    w->SetFlag(2, 0);
    IWindow_s0063_ba50* t = layout->FindWindowByID(0x5006000, true);
    if (t) {
        cString_s0063_ba50 s;
        s.Load(0x7518573e, 0x5496b24, L"*Log In...*");
        t->SetCaption(s.Get());
    }
}

// @ 0x0063be00
void cSPPlayModeSubModeMovie_s0063_ba50::ShowYouTubeUploadVideoDialog()
{
    BeginProfScope(0, 1)->End();
    cSPUILayout_s0063_ba50* layout = &gConnectingDialog.mpObject->mLayout;
    IWindow_s0063_ba50* w = layout->FindWindowByID(0x5d2bdf8, true);
    w->SetFlag(1, 0);
    w->SetFlag(2, 0);
    IWindow_s0063_ba50* t = layout->FindWindowByID(0x5006000, true);
    if (t) {
        cString_s0063_ba50 s;
        s.Load(0x7518573e, 0x55aa305, L"*Upload Video...*");
        w->SetFlag(1, 1);
        w->SetFlag(2, 1);
        t->SetCaption(s.Get());
    }
}

// @ 0x0063bec0
void cSPPlayModeSubModeMovie_s0063_ba50::ShowYouTubeLoginDialog()
{
    BeginProfScope(0, 1)->End();
    mUI->ShowYouTubeLoginDialog();
    if (GetConfigManager_s0063_ba50()->GetBool(0x5664a8b)) {
        mUI->SetYTPrompt(true);
        mDialogInProgress = 3;
    } else {
        mUI->SetYTPrompt(false);
        mDialogInProgress = 3;
    }
}

// @ 0x0063bf20
void cConnectingDialog_s0063_ba50::End(bool b)
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

// @ 0x0063bf80
bool cConnectingDialog_s0063_ba50::Update(void* p)
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
bool SP::cSPPlayModeSubModeMovie::IsLocaleEnglish()
{
    return StrEq(GetLocale()->GetLanguage(), L"en-us") || StrEq(GetLocale()->GetLanguage(), L"en-us")
        || StrEq(GetLocale()->GetLanguage(), L"en-gb");
}

// @ 0x0063c190
bool cConnectingDialog_s0063_ba50::HandleUIMessage(void* a, void* m)
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

// @ 0x0063c590
void cSPPlayModeSubModeMovie_s0063_ba50::SetStatusText(bool withArg, int arg)
{
    IWindow_s0063_ba50* w = mUI->FindPlayModeUIWindow(0x42cadb8);
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

// @ 0x0063c7f0
void cSPPlayModeSubModeMovie_s0063_ba50::LoadYouTubeCredentials()
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
        GetConfigManager_s0063_ba50()->SetBool(0x5664a8b, false);
    }
}

// @ 0x0063c8f0
void cSPPlayModeSubModeMovie_s0063_ba50::OnMovieRecorded()
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
    Sprintf16(wbuf, gFmtW, GetSaveArea_s0063_ba50(0x11ac197)->GetPath());
    StrncpyUTF8ToUTF16(cbuf, 0x104, wbuf, -1);
    sprintf(mCurrPathname, gFmtS, cbuf);
    IWindow_s0063_ba50* w = mUI->FindPlayModeUIWindow(0x42cadb8);
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

// @ 0x0063cd30
__declspec(noinline) void cSPPlayModeSubModeMovie_s0063_caf0::FUN_0063cd30()
{
    eastl::string16_s0063_caf0 name = EA::ConvertToString16_s0063_caf0(mCurrFilename, -1);
    gTextTable->m18 = name.c_str();
    eastl::string16_s0063_caf0 path = EA::ConvertToString16_s0063_caf0(mCurrPathname, -1);
    if (gAppProperties_s0063_caf0->GetDescription(0x61b67b6)) {
        SP::cString_s0063_caf0 s1, s2, s3;
        s1.Load(0x19f76d11, 0x5ca8d97, gDflt13fe144);
        s3.Load(0x19f76d11, 0x5ca8d98, gDflt13fe144);
        WStr_Format(&mTableB[0], L" %s%s", s1.GetText(), s3.GetText());
        gTextTable->m1c = mTableB[0].c_str();
        s2.Load(0x19f76d11, 0x61b68c1, gDflt13fe144);
        WStr_Format(&mTableA[0], gFmt13fe12c, s2.GetText());
        gTextTable->m58 = mTableA[0].c_str();
    } else {
        gTextTable->m1c = path.c_str();
        gTextTable->m58 = gDfltText;
    }
    mUI->ShowMovieSavedDialogCustom();
    mDialogInProgress = 1;
}

// @ 0x0063ced0
void cSPPlayModeSubModeMovie_s0063_caf0::CheckYouTubeRegistration()
{
    cEditorYouTubeAuthenticationMessage_s0063_caf0 msg;
    mb231e = true;
    mb231d = false;
    mb231c = false;
    msg.mUsername.sprintf("%s", (const char*)mField22fc);
    msg.mPassword.sprintf("%s", (const char*)mField234c);
    msg.mSource.sprintf("%s", "scc");
    msg.mCheckRegistration = true;
    GetMessageServer_s0063_caf0()->PostMessage(0x55be439, &msg, 0);
}

// @ 0x0063cf90
void cSPPlayModeSubModeMovie_s0063_caf0::FUN_0063cf90()
{
    cEditorYouTubeAuthenticationMessage_s0063_caf0 msg;
    mb2321 = true;
    mb2320 = false;
    mb231f = false;
    msg.mUsername.sprintf("%s", (const char*)mField22fc);
    msg.mPassword.sprintf("%s", (const char*)mField234c);
    msg.mSource.sprintf("%s", "scc");
    msg.mCheckRegistration = false;
    GetMessageServer_s0063_caf0()->PostMessage(0x55be439, &msg, 0);
}

// @ 0x0063d050
void cSPPlayModeSubModeMovie_s0063_caf0::ConstructYouTubeVideoUploadXMLRequest(eastl::string_s0063_caf0* out)
{
    char bPrivate = 0;
    if (gAppProperties_s0063_caf0) {
        void* p;
        if (gAppProperties_s0063_caf0->GetProp(0x8608be4, &p) && ((cProp*)p)->mType == 1)
            bPrivate = *((cProp*)p)->GetBool();
    }

    out->clear();
    out->append_sprintf("%s", "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    out->append_sprintf("%s", "<entry xmlns=\"http://www.w3.org/2005/Atom\"\n");
    out->append_sprintf("%s", "\txmlns:media=\"http://search.yahoo.com/mrss/\"\n");
    out->append_sprintf("%s", "\txmlns:yt=\"http://gdata.youtube.com/schemas/2007\">\n");
    out->append_sprintf("%s", "\t<media:group>\n");
    out->append_sprintf("%s", "\t\t<media:title>Spore Creature Creator Video</media:title>\n");
    out->append_sprintf("%s", "\t\t<media:description>This video was created using the Spore Creature Creator.</media:description>\n");
    out->append_sprintf("%s", "\t\t<media:category scheme=\"http://gdata.youtube.com/schemas/2007/categories.cat\">Entertainment</media:category>\n");
    out->append_sprintf("%s", "\t\t<media:keywords>spore, creature</media:keywords>\n");
    if (bPrivate == 0)
        out->append_sprintf("%s", "\t<yt:private/>\n");
    out->append_sprintf("%s", "\t</media:group>\n");
    out->append_sprintf("%s", "</entry>\n");
}

// @ 0x0063d170
bool cSPPlayModeSubModeMovie_s0063_caf0::ConstructVideoURL(eastl::string16_s0063_caf0* in, eastl::string16_s0063_caf0* out)
{
    WStr16 str;
    bool ok = true;
    const wchar_t* e = gUrlDelims;
    while (*e) e += 1;
    const wchar_t* dEnd = gUrlDelims + (e - gUrlDelims);
    const wchar_t* b = in->mpBegin;
    uint32_t len = (uint32_t)(in->mpEnd - b);
    if (len) {
        uint32_t npos = (uint32_t)-1;
        uint32_t pos = len - 1;
        const wchar_t* r = FindLastOf16(b + MinRef(pos, npos) + 1, b, gUrlDelims, dEnd);
        if (r != b) {
            int idx = (int)((r - 1) - b);
            if (idx != -1) {
                str = ((WStr16*)in)->substr(idx + 1, StrLenB16(b) - idx);
                out->clear();
                WStr_Format(out, L"http://www.youtube.com/watch?v=%s", str);
                goto done;
            }
        }
    }
    ok = false;
done:
    return ok;
}

// @ 0x0063d2f0
bool cMovieHandler::HandleMessage(uint32_t id, cMsg* msg)
{
    IAuthManager_s0063_caf0* auth = GetAuthManager_s0063_caf0();
    switch (id) {
    case 0x5b98f52:
        if (mState != 7 && mState != 8)
            return false;
        Movie()->FUN_0063cd30();
        BeginProfScope(0, 1)->End();
        return false;
    case 0x55e5212: {
        uint32_t f10 = msg->f10;
        uint32_t f8 = msg->f08;
        if (f10 != 0)
            mb2309 = true;
        else
            mb230c = true;
        if (f8 != 0) {
            if (f10 != 0) {
                mb2308 = true;
                return true;
            }
            mAuthToken.sprintf("%s", ((cStrObj*)msg->f18)->mStr);
            mUsername.sprintf("%s", ((cStrObj*)msg->f20)->mStr);
            mb230b = true;
            return true;
        }
        mb2308 = false;
        mb230b = false;
        mStatusCode = msg->f18;
        mStatusMsg.sprintf("%s", ((cStrObj*)msg->f20)->mStr);
        return true;
    }
    case 0x44db12e:
        if (msg == 0)
            return false;
        if (mState != 7 && mState != 8)
            return false;
        if (mb2349) {
            mb234a = true;
            return false;
        }
        if (cSPPlayModeSubModeMovie_s0063_caf0::GetYTPrompt()) {
            Movie()->ShowYouTubeLoginDialog();
            gApp15e4ef0->v58();
            return false;
        }
        CreateConnectingDialog();
        Movie()->CheckYouTubeRegistration();
        gApp15e4ef0->v58();
        return false;
    case 0x5493aeb: {
        uint32_t btn = msg->f08;
        if (btn == 0x1510d07)
            return false;
        switch (mState) {
        case 1:
            switch (btn) {
            case 0x5107b17:
                Movie()->ShowMovieSavedDialog();
                OpenBrowser(L"http://youtube.com/t/terms", 1);
                break;
            case 0x5107b19:
                mState = 0;
                return true;
            case 0x5107b1a:
                if (!auth->v58()) {
                    mState = 8;
                    CalloutMessageBox(&gCalloutWhere, gKey15247ec_s0063_caf0);
                } else if (auth->v24()) {
                    mState = 7;
                    CalloutMessageBox(&gCalloutWhere, gKey15247e0_s0063_caf0);
                } else {
                    if (cSPPlayModeSubModeMovie_s0063_caf0::GetYTPrompt()) {
                        Movie()->ShowYouTubeLoginDialog();
                        return true;
                    }
                    CreateConnectingDialog();
                    Movie()->CheckYouTubeRegistration();
                    return true;
                }
                BeginProfScope(0, 1)->End();
                return true;
            }
            return true;
        case 2:
            switch (btn) {
            case 0x5107b19:
                goto closeDialog;
            case 0x5107b1a:
                Movie()->ShowYouTubeLoginDialog();
                return true;
            default:
                return true;
            }
        case 3:
            mState = 0;
            return true;
        case 7:
        case 8:
            switch (btn) {
            case 0x5107b19:
                goto closeDialog;
            case 0x5107b1a:
                auth->v44();
                return true;
            default:
                return true;
            }
        case 5:
            switch (btn) {
            case 0x5107b19:
                goto closeDialog;
            case 0x5107b1a:
                mUI->ShowSendEmail(&mURL);
                return true;
            default:
                return true;
            }
        case 10:
        case 11:
            if (btn != 0xfffffff1)
                return true;
        case 4:
        case 6:
        closeDialog:
            CLOSE_DIALOG;
        case 12:
            switch (btn) {
            case 0x5107b19:
                Movie()->ShowYouTubeLoginDialog();
                break;
            case 0x5107b1a:
                Movie()->ShowYouTubeLoginDialog();
                OpenBrowser(L"http://www.youtube.com/signup", 1);
                break;
            }
            return true;
        case 13:
            switch (btn) {
            case 0x5107b19:
                Movie()->FUN_0063cd30();
                break;
            case 0x5107b1a:
                Movie()->FUN_0063cd30();
                OpenBrowser(L"http://youtube.com/t/terms", 1);
                break;
            }
            return true;
        default:
            return false;
        }
    }
    case 0x55e8be4: {
        if (msg->f08 != 0)
            mb230e = true;
        if (mb230e) {
            WStr16 tmp;
            WStr_Format(&tmp, L"%s", ((cStrObj*)msg->f10)->mStr);
            if (!cSPPlayModeSubModeMovie_s0063_caf0::ConstructVideoURL((eastl::string16_s0063_caf0*)&tmp, (eastl::string16_s0063_caf0*)&mURL))
                mURL = tmp;
            gTextTable->m30 = mURL.mpBegin;
        } else {
            mStatusCode = msg->f10;
            mStatusMsg.sprintf("%s", ((cStrObj*)msg->f18)->mStr);
        }
        if (((cAppPropsX*)gAppProperties_s0063_caf0)->p3c->f118 == 0)
            AchievementsController(0xb4c2a66b, 1)->AutoTest();
        mb2310 = true;
        return true;
    }
    case 0x5b96086:
        if (mUI->FUN_00634b00())
            return true;
        if (!auth->v58())
            return true;
        CLOSE_DIALOG;
    case 0x5dd52c7:
        mb2349 = false;
        if (mb234a) {
            mb234a = false;
            if (cSPPlayModeSubModeMovie_s0063_caf0::GetYTPrompt()) {
                Movie()->ShowYouTubeLoginDialog();
                gApp15e4ef0->v58();
                return false;
            }
            CreateConnectingDialog();
            Movie()->CheckYouTubeRegistration();
            gApp15e4ef0->v58();
            return false;
        }
        return false;
    case 0x5bd6378:
        mb2349 = true;
        return false;
    case 0x5d2c5c0: {
        DestroyConnectingDialog(false);
        Movie()->SetStateB();
        uint32_t m = 0x55e7aed;
        GetMessageServer_s0063_caf0()->PostMessage(0x5d313c7, &m, 0);
        return true;
    }
    case 0x62ff413:
        Movie()->OnMovieRecorded();
        return false;
    }
    return false;
}

// @ 0x0063d910
void cSPPlayModeSubModeMovie_s0063_caf0::ToggleRecordingIndicator(char b)
{
    if (b == 0) {
        IAudioSystem* s = GetSystemAT();
        KillSetiEffects(0xcb4ad069, s ? s->v8() : 0);
        FUN_0063cd30();
    }
    IWindow_s0063_caf0* w = mUI->FindPlayModeUIWindow(0x42cadb8);
    if (w)
        w->SetCaption(EA::ConvertToString16_s0063_caf0(gRecordingStopped, -1).c_str());
    mb22c0 = false;
    mUI->SetUIGroupVisible(0x3f434ac, false);
    mUI->SetUIGroupVisible(0x3fc1740, true);
    if (mb22c1)
        FUN_0063b760();
}

// @ 0x0063de20
void cSPPlayModeSubModeMovie_s0063_d9e0::FUN_0063de20(int dt)
{
    if (mRecording) {
        mIndicatorTimer += dt;
        if ((uint32_t)mIndicatorTimer > 500) {
            FUN_0063b760();
            mIndicatorTimer = 0;
        }
        if (!mMovieSystem->IsRecording()) {
            ToggleRecordingIndicator(0);
            ISaveArea_s0063_d9e0* sa = GetSaveArea_s0063_d9e0(0x11ac197);
            eastl::string16_s0063_d9e0 name;
            WStr_Format(&name, L"%s.avi", EA::ConvertToString16_s0063_d9e0(mCurrFilename, -1).c_str());
            sa->SetName(name.c_str(), 0, 2);
            ((cSPPlayModeUIExt*)mUI)->FUN_00635350(1, 0);
            mUI->EnablePhotoViewerButton(true);
            ((cSPPlayModeUIExt*)mUI)->SetTagField(1);
            ((cSPPlayModeUIExt*)mUI)->SetEnabled(0x3a8ede4, true);
            ((cSPPlayModeUIExt*)mUI)->ShowEditor();
        }
    }
    if (mDoRegisterCheck && mRegisterCheckComplete) {
        if (mRegisterSuccess) {
            GetConfigManager_s0063_d9e0()->Slot3c();
            FUN_0063dc40();
            ShowLoginToYouTubeDialog();
            FUN_0063cf90();
        } else {
            DestroyConnectingDialog(false);
            {
                SP::cString_s0063_d9e0 msg;
                msg.Load(0x7518573e, 0x5baf944, L"Login Failed (PLACEHOLDER)");
                cDateStrings* ds = gDateStrings;
                ds->mMessage = msg.GetText();
            }
            if (mYTStatusCode == 0x193)
                SetState2();
            else
                SetState4();
        }
        mDoRegisterCheck = false;
    }
    if (mDoLoginCheck && mLoginCheckComplete) {
        if (mLoginSuccess) {
            ShowYouTubeUploadVideoDialog();
            mEnableYouTubeVideoUpload = true;
            FUN_0063d9e0();
        } else {
            DestroyConnectingDialog(false);
            {
                SP::cString_s0063_d9e0 msg;
                msg.Load(0x7518573e, 0x5baf944, L"Login Failed (PLACEHOLDER)");
                cDateStrings* ds = gDateStrings;
                ds->mMessage = msg.GetText();
            }
            SetState4();
        }
        mDoLoginCheck = false;
    }
    if (mDoVideoUpload && mVideoUploadComplete) {
        if (mVideoUploadSuccess) {
            DestroyConnectingDialog(true);
            SetState5();
            mDoVideoUpload = false;
            return;
        }
        DestroyConnectingDialog(false);
        {
            SP::cString_s0063_d9e0 msg;
            msg.Load(0x7518573e, 0x5cbdeda, L"Upload Failed (PLACEHOLDER)");
            cDateStrings* ds = gDateStrings;
            ds->mMessage = msg.GetText();
        }
        SetState6();
        mDoVideoUpload = false;
    }
}

// @ 0x0063e100
bool cSPPlayModeSubModeMovie_s0063_d9e0::HandleButton(int id)
{
    IAuthManager* auth = GetAuthManager();
    switch (id) {
    case 0x3f434ac:
    case 0x3fc1740:
        if (mMovieSystem->IsRecording()) {
            mMovieSystem->StopRecording();
            ToggleRecordingIndicator(0);
            ISaveArea_s0063_d9e0* sa = GetSaveArea_s0063_d9e0(0x11ac197);
            eastl::string16_s0063_d9e0 name;
            WStr_Format(&name, L"%s.avi", EA::ConvertToString16_s0063_d9e0(mCurrFilename, -1).c_str());
            sa->SetName(name.c_str(), 0, 2);
            FUN_0063b9f0(true);
            return true;
        }
        if (!FUN_0063b950() && !FUN_0063b9a0())
            return true;
        FUN_0063b9f0(false);
        {
            eastl::string16_s0063_d9e0 year;
            eastl::string16_s0063_d9e0 month;
            eastl::string16_s0063_d9e0 day;
            eastl::string16_s0063_d9e0 time;
            eastl::string16_s0063_d9e0 prefix;
            wchar_t wide[0x104];
            char narrow[0x104];

            WStr_Format(&prefix, L"%s", L"Spore_");
            gDateStrings->mPrefix = prefix.c_str();
            EA::DateTime::DateTime_s0063_d9e0 now(2);
            WStr_Format(&year, L"%04u", now.GetParameter(1));
            gDateStrings->mYear = year.c_str();
            WStr_Format(&month, L"%02u", now.GetParameter(2));
            gDateStrings->mMonth = month.c_str();
            WStr_Format(&day, L"%02u", now.GetParameter(6));
            gDateStrings->mDay = day.c_str();
            WStr_Format(&time, L"%02u-%02u-%02u", now.GetParameter(8), now.GetParameter(9), now.GetParameter(10));
            gDateStrings->mTime = time.c_str();

            SP::cString_s0063_d9e0 title;
            title.Load(0x7518573e, 0x5dbc9ee, L"Movie Name (PLACEHOLDER)");
            Sprintf16(wide, L"%s", title.GetText());
            Utf16ToUtf8(narrow, 0x104, wide, -1);
            sprintf(mCurrFilename, "%s", narrow);

            Sprintf16(wide, L"%s", GetSaveArea_s0063_d9e0(0x11ac197)->GetPath());
            Utf16ToUtf8(narrow, 0x104, wide, -1);
            sprintf(mCurrPathname, "%s", narrow);

            uint32_t width, height;
            TryGetUIntProperty(gAppProperties, 0x456f975, &width);
            TryGetUIntProperty(gAppProperties, 0x456f976, &height);
            mWidth = width;
            mHeight = height;
            mTime = 120.0f;
            GetBoolProperty(gAppProperties, 0x456f97a, &mExcludeUI);
            mMovieSystem->StartRecording(EA::ConvertToString16_s0063_d9e0(mCurrFilename, -1).c_str(), &mWidth);
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
        bool on = GetConfigManager_s0063_d9e0()->GetValue(0x5664a8b) != 0;
        GetConfigManager_s0063_d9e0()->SetValue(0x5664a8b, !on);
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
