// src/game/SPEditors/SPSubModeMovie.cpp -- migrated from slice(s) s00f06d40, s00f05ee0, s00f05110, s00f04140, s00df5670, s00df47b0, s0063d9e0, s0063caf0, s0063ba50, s0063aa90 by tools/migrate/rewrite.py
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
#include "cSPVector3.h"
#include "SP/cGameInfo.h"
#include "SP/cStarManager.h"
#include "SP/cStarRecord.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include <math.h>
#include "SP/cPlayModeTokenTranslator.h"
#include "EA/LimitStopwatch.h"
#include <xmmintrin.h>
#include <intrin.h>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

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
void FUN_00809db0(const void* a, const void* b);                        // 0x00809DB0 (cdecl)
struct cConfigMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual int GetValue(uint32_t id); };   // +0x30
cConfigMgr* GetConfigManager();                                         // 0x0067DD30
struct cSaveArea { virtual void v0(); virtual void v1(); virtual void v2(); virtual int GetType();   // +0xc
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void* GetData(); };                                         // +0x28
cSaveArea* GetSaveArea(uint32_t id);                                    // 0x006B1F90
void FUN_009322b0(const void* p);                                       // 0x009322B0 (cdecl)
void FUN_00932960(const void* p);                                       // 0x00932960 (cdecl)
class cSPPlayModeSubModeMovie {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
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
struct cDialog2 {
    bool Init();
    char pad[0x2c];
    cSPUILayout_s0063_aa90 mLayout;                                                // +0x2c
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
extern const uint32_t gMsgTable[12];   // 0x013FF09C
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
IMovieSystem_s0063_caf0* MovieSystem();   // 0x0067CB10
struct IConfigMgr_s0063_caf0 {
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
virtual void c11();
    virtual int GetValue(uint32_t id);                               // +0x30
};
IConfigMgr_s0063_caf0* GetConfigManager_s0063_caf0();   // 0x0067DD30
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
static __forceinline bool GetTyped(IPropList_s0063_caf0* pl, uint32_t id, short type, void** out)
{
    return pl->GetProp(id, out) && ((cProp*)*out)->mType == type;
}
#define CLOSE_DIALOG do { mState = 0; BeginProfScope(1, 1)->End(); return true; } while (0)
// ---- items of slice s0063caf0 end

// ---- items of slice s0063d9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_1524440;   // 0x01524440
extern void* g_1524444;   // 0x01524444
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
class allocator_s0063_d9e0 { public:
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
class cSPUILayout_s0063_d9e0 { public:
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
class DateTime_s0063_d9e0 { public:
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
    char pad22e8[0x22ec - 0x22e8];
    eastl::string_s0063_d9e0 mYTAuthToken;     // +0x22EC
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
    __declspec(nothrow) void FUN_0063dc40();
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
struct NoThrowStr {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    NoThrowStr() : mpBegin((void*)eastl::gEmptyString16), mpEnd((void*)eastl::gEmptyString16),
                   mpCapacity((char*)eastl::gEmptyString16 + 1) {}
    __declspec(nothrow) ~NoThrowStr() {
        if (((char*)mpCapacity - (char*)mpBegin) > 1 && mpBegin)
            operator delete(mpBegin);
    }
};
struct cEditorYouTubeVideoUploadMessage_s0063_d9e0 {
    NoThrowStr mUsername;               // +0x00
    NoThrowStr mClientID;               // +0x10
    NoThrowStr mAuthenticationToken;    // +0x20
    NoThrowStr mDeveloperKey;           // +0x30
    NoThrowStr mVideoFilename;          // +0x40
    uint32_t   mVideoKey[3];            // +0x50
    NoThrowStr mXMLRequest;             // +0x5C
    ~cEditorYouTubeVideoUploadMessage_s0063_d9e0();          // 0x63c750
};
void ConstructYouTubeVideoUploadXMLRequest(eastl::string16_s0063_d9e0* out);            // 0x63d050 (this in ecx)
void __cdecl CString_Sprintf(eastl::string_s0063_d9e0* str, const char* fmt, ...);      // 0x472fe0
int  __cdecl FNV1_String16A(uint32_t seed, const void* s, int n);            // 0x932f30
void* __cdecl GetPropertyManager_s0063_d9e0();                                          // 0x67de30
void __cdecl SaveNamedResource(eastl::string_s0063_d9e0* dst, void* a, void* b);        // 0x6b4010
void* __cdecl operator_new_ea(unsigned int size, const char* tag, int, int, int, int);  // 0x0F473A0
struct IReleasable { virtual void r0(); virtual void Release(); virtual void r2(); };
void* __fastcall PropertyList_Ctor(void* self, int edx);
struct IPropertyList_s0063_d9e0 {
virtual void p0();
virtual void p1();
virtual uint32_t p2();
virtual void p3();
virtual void p4();
virtual uint32_t v14(uint32_t id, void* variant);
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
    virtual void* v2c(uint32_t key, uint32_t id, void* out);   // +0x2c
};
struct Variant_s0063_d9e0 { uint32_t w[4]; uint32_t flags; uint32_t pad[2]; };
void __fastcall Variant_FromString16(Variant_s0063_d9e0* self, int edx, const void* src, int a, int b, int c,
                                     int d);                                       // 0x93dd80
void __cdecl Variant_Destruct(Variant_s0063_d9e0* v, int a);                                  // 0x93db80
void __cdecl Encrypt(void* dst, const void* src);                                  // 0x60bcf0
void CreateConnectingDialog();                       // 0x0063BC70
void __cdecl DestroyConnectingDialog(bool b);        // 0x0063C060
struct cSPPlayModeUIExt {
    void FUN_00635350(uint32_t a, uint32_t b);       // 0x00635350
    void SetTagField(uint32_t v);                    // 0x006353E0
    void SetEnabled(uint32_t id, bool on);           // 0x00634EF0
    void ShowEditor();                               // 0x00635380
};
// ---- items of slice s0063d9e0 end

// ---- items of slice s00df47b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __int64 __rdtsc(void);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* pCount);
#pragma intrinsic(__rdtsc)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
namespace eastl {
class allocator_s00df_47b0 { public:
    allocator_s00df_47b0() {}
};
}
namespace eastl {
template <typename T> struct basic_string_s00df_47b0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s00df_47b0 mAllocator;

    basic_string_s00df_47b0(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string_s00df_47b0() { DeallocateSelf(); }

    void RangeInitialize(const T* pBegin);   // 0x00579a90
    void DoFree(T* p, size_t n)
    {
        if (p)
            delete[] (char*)p;
    }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void clear()
    {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};
}
namespace eastl {
typedef basic_string_s00df_47b0<wchar_t> string16_s00df_47b0;
}
namespace eastl {
template <typename T> class vector_s00df_47b0 { public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s00df_47b0 mAllocator;

    void DoInsertValue(T* position, const T& value);   // 0x00b96600
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
    }
};
}
using eastl::string16_s00df_47b0;
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
struct Rect {
    float left, top, right, bottom;
    Rect(const Rect& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
};
struct IWindow_s00df_47b0 {
    PV2 PV
    virtual IWindow_s00df_47b0* FindWindowByID(uint32_t id);   // +0x0c
    PV8 PV2
    virtual const Rect& GetArea();                  // +0x38
    PV8 PV2
    virtual void SetLocation(float x, float y);     // +0x64
    PV4 PV
    virtual void SetFlag(int flag, bool value);     // +0x7c
    virtual void SetText(const wchar_t* text);      // +0x80
};
class cSPUILayout_s00df_47b0 { public:
    uint32_t pad[3];
    IWindow_s00df_47b0* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
};
struct cStarRecord {
    uint32_t pad[0x16];
    uint32_t m58;
    uint32_t Get58();                  // 0x00989360 (returns m58)
    void Reset(int flags);             // 0x00bbaa80
};
struct cGameInfo {
    uint32_t pad00[8];
    string16_s00df_47b0 mName;          // +0x20
    uint32_t pad30[7];
    ResourceKey mKey4C;      // +0x4c
    uint32_t pad58[3];
    ResourceKey mKey64;      // +0x64
    ResourceKey mKey70;      // +0x70
    uint32_t mStarID;        // +0x7c
    uint32_t pad80[5];
    ResourceKey mKey94;      // +0x94
    int mA0;                 // +0xa0
    int mA4;                 // +0xa4
    int mA8;                 // +0xa8
    uint32_t padac;
    int mB0;                 // +0xb0
    cStarRecord* GetStarRecord();   // 0x00de4610
};
struct Stopwatch {
    uint64_t mnStartTime;      // +0x00
    uint64_t mnTotalElapsed;   // +0x08
    int mnUnits;               // +0x10 (1 = CPU cycles)
    float mfCyclesToUnits;     // +0x14
    uint64_t GetStopwatchCycle()
    {
        if (mnUnits == 1)
            return __rdtsc();
        int64_t t;
        QueryPerformanceCounter(&t);
        return (uint64_t)t;
    }
    void Restart()
    {
        mnStartTime = GetStopwatchCycle();
        mnTotalElapsed = 0;
    }
};
struct cGalaxyGameEntryUIStateMachine {
    uint32_t pad00[0xa];
    cSPUILayout_s00df_47b0 mLayout;                       // +0x28
    uint32_t pad34[0xa];
    eastl::vector_s00df_47b0<uint32_t> mNewGameFlow;      // +0x5c
    uint32_t pad6c;
    bool mb70;                                 // +0x70
    uint8_t pad71[0x4a3];
    ResourceKey mKey514;                       // +0x514
    uint32_t pad520[0x34];
    Stopwatch mZoomTimer;                      // +0x5f0
    uint32_t pad608[8];
    cGameInfo* mpGameInfo;                     // +0x628

    void ResetGameUI();                                  // 0x00dec460
    void MakeRandomName();                               // 0x00defc80
    void SetupPanelA(uint32_t id);                       // 0x00df2920
    void SetupPanelB(uint32_t id);                       // 0x00df2770
    void SetCurrentState(int state);                     // 0x00df0670
    void RefreshUI();                                    // 0x00ded7d0
    void FillStarterWorldCombo(IWindow_s00df_47b0* combo);          // 0x00df1ba0
    void SelectStarterWorld(IWindow_s00df_47b0* combo, uint32_t v); // 0x00decf20
    void UpdateNavigationControls();                     // 0x00def8c0

    void SetupForGame(cGameInfo* gameInfo);

    void FUN_00df5330();
    void FUN_00df53d0(bool show);
    void FUN_00df5430(int mode);
    long double FUN_00df54f0(float offset);
    void FUN_00df5540();
    void FUN_00df55b0(int mode);
    void FUN_00df5610(float t);
};
#define VTFN(obj, slot) (*(void***)(obj))[slot]
struct GalaxyLayoutState
{
    void SetLayout(const wchar_t* layout);      // 0x00dedda0
};
struct GalaxyView
{
    uint8_t       m_pad0[8];                    // +0x00
    GalaxyLayoutState* m_state8;                // +0x08
    cGameInfo*    m_game0c;                     // +0x0c
    uint8_t       m_pad10[0x20];                // +0x10
    void*         m_effect30;                   // +0x30
    float         m_x34;                        // +0x34
    float         m_y38;                        // +0x38
    float         m_z3c;                        // +0x3c
    float         m_w40;                        // +0x40
    uint8_t       m_pad44[8];                   // +0x44
    uint32_t      m_count4c;                    // +0x4c
    uint32_t      m_value50;                    // +0x50
    cSPUILayout_s00df_47b0   mLayout54;                    // +0x54
};
struct GalaxyView0c
{
    uint8_t     m_pad0[0xc];                   // +0x00
    cSPUILayout_s00df_47b0 mLayout0c;                     // +0x0c
};
class cMessageServer
{
public:
    PV4 PV
    virtual void post(uint32_t message, uint32_t param, int flags);   // +0x14
};
cMessageServer* MessageServer();                // 0x0067dcc0
void __cdecl FUN_008099a0(IWindow_s00df_47b0* window, int a, int b);   // BeginModal
class cString_s00df_47b0
{
public:
    uint32_t m_data[5];
    cString_s00df_47b0();                                  // 0x006b5060
    ~cString_s00df_47b0();                                 // 0x006b5240
    void Load(uint32_t id, uint32_t group, const wchar_t* text);   // 0x006b54b0
    const wchar_t* GetText();                   // 0x006b55c0
};
struct Effect
{
    PV8 PV8 PV8
    virtual void SetValue(const float* value);  // +0x60
};
// ---- items of slice s00df47b0 end

// ---- items of slice s00df5670 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct Vec4 { float x, y, z, w; };
struct Obj;
struct cSPUILayout_s00df_5670;
struct cSPUILayout_s00df_5670 {
    void* FindWindowByID(uint id, int b);              // 0x008105b0 (ret 8) -> IWinNode*
    void* FindWindowByIDB(uint id, int b);             // 0x008105b0 (ret 8)
    bool  Init(const void* key, bool b, uint id);      // 0x008120d0 (ret 0xc)
    void  Shutdown(uint b);                            // 0x00811ad0 (ret 4)
    void  dtor();                                      // 0x00811fe0
    void  ctor();                                      // 0x00810000
};
struct IRefCount { virtual void r00(); virtual void r04(); };
struct IWinNode : IRefCount {
virtual void  v08();
virtual void  v0c(int b);
virtual void  v10();
virtual void  v14();
virtual void  v18();
virtual int   v1c();
virtual void  v20();
virtual void  v24();
virtual void  v28();
virtual void  v2c();
virtual void  v30();
virtual Vec4* v34();
    virtual Vec4* v38();
virtual void  v3c();
virtual void  v40();
virtual void  v44();
virtual void  v48();
virtual void  v4c();
virtual void  v50();
    virtual void  v54();
    virtual void* v58();
    virtual void  v5c(void* p);
    virtual void  v60(const float* rect);
    virtual void  v64(float a, float b);
virtual void  v68();
virtual void  v6c();
virtual void  v70();
virtual void  v74();
    virtual void  v78();
    virtual void  v7c(int a, int b);
virtual bool  v80(const wchar_t* s);
virtual void  v84();
virtual void  v88();
virtual void  v8c();
virtual void  v90();
virtual void  v94();
virtual void  v98();
virtual void  v9c();
virtual void  va0();
virtual void  va4();
virtual void  va8();
virtual void  vac();
virtual void  vb0();
virtual void  vb4();
virtual void  vb8();
virtual void  vbc();
virtual void  vc0();
virtual void  vc4();
virtual void  vc8();
virtual void  vcc();
virtual void  vd0();
virtual void  vd4();
virtual void  vd8();
virtual void  vdc();
virtual void  ve0();
virtual void  ve4();
virtual void  ve8();
    virtual void  vec();
    virtual void* vf0(int a, int b, float* p);
virtual void  vf4();
virtual void  vf8();
    virtual void  vfc();
    virtual void  v100();
    virtual void  v104(void* p);
    virtual void  v108(void* p);
};
struct cString_s00df_5670 {
    char  m_storage[0x0c];
    cString_s00df_5670();                                          // 0x006b5060
    ~cString_s00df_5670();                                         // 0x006b5240
    bool Load(uint a, uint b, const wchar_t* s);        // 0x006b54b0 (ret 0xc)
    const wchar_t* GetText();                           // 0x006b55c0
};
void  __cdecl FUN_00df5430(int b);                                      // 0x00df5430 (ret 4)
struct cDownloadDialog;
struct cDownloadDialog {
    void* mpVtbl_00;        // +0x00
    void* mpVtbl_04;        // +0x04  Resource::Async
    void* mpVal_08;         // +0x08  (vector begin for the +0x08/+0x0c vector view)
    union { void* mpNode_0c; void* m_entryEnd; cSPUILayout_s00df_5670* mpLayout_0c; }; // +0x0c
    float m_timerBase;      // +0x10
    float m_timerPeriod;    // +0x14
    char  m_active;         // +0x18
    char  m_latch;          // +0x19
    char pad1[0x1c - 0x1a];
    float m_p1c;            // +0x1c
    float m_p20;            // +0x20
    union { float m_p24; void* mpNode_24; }; // +0x24
    float m_p28;            // +0x28
    char  m_paused;         // +0x2c
    char pad2[0x30 - 0x2d];
    void* m_label;          // +0x30 AutoRefCount<IWinText>
    float m_r34;            // +0x34
    float m_r38;            // +0x38
    float m_r3c;            // +0x3c
    float m_r40;            // +0x40
    float m_progress;       // +0x44
    void* m_entry;          // +0x48
    int   m_count;          // +0x4c
    int   m_index;          // +0x50
    char  m_layout[0x08];   // +0x54 cSPUILayout

    cSPUILayout_s00df_5670* Layout() { return (cSPUILayout_s00df_5670*)((char*)this + 0x54); }
    cSPUILayout_s00df_5670* LayoutB() { return (cSPUILayout_s00df_5670*)((char*)this + 0x0c); }

    void   FUN_00df5670(char b);        // 0x00df5670 (ret 4)
    void   FUN_00df57d0(int b);         // 0x00df57d0 (ret 4)
    bool   FUN_00df5830(void* retaddr); // 0x00df5830 (ret 4)
    void   FUN_00df58f0();              // 0x00df58f0
    bool   FUN_00df59c0(void* p);       // 0x00df59c0 (ret 4)
    void   FUN_00df5aa0(char b);        // 0x00df5aa0 (ret 4)
    bool   FUN_00df5ac0(int b);         // 0x00df5ac0 (ret 4)
    void   FUN_00df5cd0();              // 0x00df5cd0
    void*  FUN_00df5d30(int b);         // 0x00df5d30 (ret 4)
    bool   FUN_00df5d90(void* a, void* b); // 0x00df5d90 (ret 8)
    void   FUN_00df6040();              // 0x00df6040
    bool   FUN_00df6140(Obj* a, float x, float y); // 0x00df6140 (ret 0xc)
    void   FUN_00df6330(uint id, void* p, uint b); // 0x00df6330 (ret 8)
    int    FUN_00df64c0(float a, float b, float c); // 0x00df64c0 (ret 0xc)
    void   FUN_00df65e0(void* a, void* b, float c); // 0x00df65e0 (ret 0xc)
};
// ---- items of slice s00df5670 end

// ---- items of slice s00f04140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" void _ReadWriteBarrier(void);
extern uint32_t*      gField_016c7aa4;            // 0x016C7AA4
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)
#pragma intrinsic(_ReadWriteBarrier)
void* __cdecl EAAllocate(uint32_t size, const char* tag, int a, int b, int c, int d);  // 0x00F473A0
namespace eastl {
template <typename T> struct EmptyStr_s00f0_4140;
}
namespace eastl {
template <> struct EmptyStr_s00f0_4140<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
}
namespace eastl {
template <> struct EmptyStr_s00f0_4140<char>    { static char*    Get() { return (char*)gEmptyString16; } };
}
namespace eastl {
template <typename T>
struct basic_string_s00f0_4140 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mPad;                                            // sizeof == 0x10
    basic_string_s00f0_4140() : mpBegin(EmptyStr_s00f0_4140<T>::Get()), mpEnd(EmptyStr_s00f0_4140<T>::Get()),
                     mpCapacity(EmptyStr_s00f0_4140<T>::Get() + 1) {}
    basic_string_s00f0_4140& operator=(const basic_string_s00f0_4140& o) {
        mpBegin = o.mpBegin; mpEnd = o.mpEnd; mpCapacity = o.mpCapacity;
        return *this;
    }
    ~basic_string_s00f0_4140() { DeallocateSelf(); }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin) operator delete(mpBegin);
        }
    }
    const T* c_str() const { return mpBegin; }
    basic_string_s00f0_4140& Assign(const T* pBegin, const T* pEnd);   // wchar: 0x00423650
};
}
namespace eastl {
typedef basic_string_s00f0_4140<char> string_s00f0_4140;
}
namespace eastl {
typedef basic_string_s00f0_4140<wchar_t> string16_s00f0_4140;
}
namespace eastl {
template <typename T>
inline unsigned int CharStrlen(const T* p) {
    const T* pCurrent = p;
    while (*pCurrent) ++pCurrent;
    return (unsigned int)(pCurrent - p);
}
}
namespace EA {
namespace ResourceMan {
 struct Key_s00f0_4140 { uint32_t mType, mName, mInstance; }; 
}
}
struct RefAVtbl {
    void* f00;
    void (__thiscall* Release)(void*);                          // +0x04
    void (__thiscall* v08)(void*);                              // +0x08
};
struct RefA {
    RefAVtbl* mpVtbl;
    void Release() { mpVtbl->Release(this); }
    void v08() { mpVtbl->v08(this); }
};
struct RefBVtbl {
    void* f00;
    void (__thiscall* AddRef)(void*);                           // +0x04
    void (__thiscall* Release)(void*);                          // +0x08
};
struct RefB {
    RefBVtbl* mpVtbl;
    void AddRef() { mpVtbl->AddRef(this); }
    void Release() { mpVtbl->Release(this); }
};
struct AtomicRefCounted {
    void* mpVtbl;
    uint32_t mField4;
    volatile long mnRefCount;                                   // +0x08
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release() {
        _InterlockedDecrement(&mnRefCount);
        if (_InterlockedExchangeAdd(&mnRefCount, 0) < 1)
            _InterlockedIncrement(&mnRefCount);
        else
            _InterlockedExchangeAdd(&mnRefCount, 0);
    }
};
template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pOld = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    T*& AsOutParam() {
        if (mpObject) {
            T* const pObject = mpObject;
            mpObject = 0;
            pObject->Release();
        }
        return mpObject;
    }
    operator T*() const { return mpObject; }
};
struct IWindow_s00f0_4140;
struct IWindowVtbl {
    void  (__thiscall* AddRef)(void*);                          // +0x00
    void  (__thiscall* Release)(void*);                         // +0x04
    void* f08;
    void* (__thiscall* GetControl)(void*, uint32_t);            // +0x0c
    void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24; void* f28; void* f2c;
    void* f30; void* f34; void* f38; void* f3c;
    void* f40; void* f44; void* f48; void* f4c;
    void* f50; void* f54; void* f58; void* f5c;
    void* f60; void* f64; void* f68; void* f6c;
    void* f70; void* f74; void* f78;
    void  (__thiscall* SetFlag)(void*, int, bool);              // +0x7c
    void  (__thiscall* SetCaption)(void*, const wchar_t*);      // +0x80
    void* f84; void* f88; void* f8c; void* f90; void* f94; void* f98; void* f9c;
    void* fa0; void* fa4; void* fa8; void* fac; void* fb0; void* fb4; void* fb8;
    void* fbc; void* fc0; void* fc4; void* fc8; void* fcc; void* fd0; void* fd4;
    void* fd8; void* fdc; void* fe0; void* fe4; void* fe8; void* fec;
    void* (__thiscall* FindChild)(void*, uint32_t, int);        // +0xf0
    void* f_f4; void* f_f8; void* f_fc; void* f_100;
    void  (__thiscall* AddProc)(void*, void*);                  // +0x104
    void  (__thiscall* RemoveProc)(void*, void*);               // +0x108
};
struct IWindow_s00f0_4140 {
    IWindowVtbl* mpVtbl;
    void AddRef() { mpVtbl->AddRef(this); }
    void Release() { mpVtbl->Release(this); }
    void* GetControl(uint32_t id) { return mpVtbl->GetControl(this, id); }
    void SetFlag(int a, bool b) { mpVtbl->SetFlag(this, a, b); }
    void SetCaption(const wchar_t* p) { mpVtbl->SetCaption(this, p); }
    void* FindChild(uint32_t id, int b) { return mpVtbl->FindChild(this, id, b); }
    void AddProc(void* p) { mpVtbl->AddProc(this, p); }
    void RemoveProc(void* p) { mpVtbl->RemoveProc(this, p); }
};
struct IControlVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24; void* f28; void* f2c; void* f30;
    void  (__thiscall* SetFlag)(void*, int, bool);               // +0x34
};
struct IControl_s00f0_4140 {
    IControlVtbl* mpVtbl;
    void SetFlag(int a, bool b) { mpVtbl->SetFlag(this, a, b); }
};
struct cSPUILayout_s00f0_4140 {
    RefBVtbl* mpVtbl;                                           // +0x00
    void AddRef() { mpVtbl->AddRef(this); }
    void Release() { mpVtbl->Release(this); }
    IWindow_s00f0_4140* FindWindowByID(uint32_t id, bool recurse);                        // 0x008105B0
    void     Shutdown(uint32_t a);                                            // 0x00811AD0
    bool     Init(const EA::ResourceMan::Key_s00f0_4140& key, bool b, uint32_t c);       // 0x008120D0
    bool     SetParentWin(IWindow_s00f0_4140* w, bool b, uint32_t c);                    // 0x008121B0
};
struct Property;
struct PropertyVtbl {
    void* f00;
    void (__thiscall* Release)(void*);                          // +0x04
};
struct Property {
    PropertyVtbl* mpVtbl;                                       // +0x00
    uint32_t mData[3];
    uint16_t mnFlags;                                           // +0x10
    uint16_t mnType;                                            // +0x12
    void AddRef() {}
    void Release() { mpVtbl->Release(this); }
    const float*    GetValueFloat();                            // 0x0041EA70
    const uint32_t* GetValueUInt();                             // 0x0041EA00
    const bool*     GetValueBool();                             // 0x0041E920
};
struct IAppPropsVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20;
    bool (__thiscall* GetProperty)(void*, uint32_t, Property**);             // +0x24
};
struct IAppProps {
    IAppPropsVtbl* mpVtbl;
    bool GetProperty(uint32_t id, Property** out) { return mpVtbl->GetProperty(this, id, out); }
};
struct IUISubVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18;
    void (__thiscall* v1c)(void*, void*);                                    // +0x1c
    void (__thiscall* v20)(void*, void*);                                    // +0x20
};
struct IUISub {
    IUISubVtbl* mpVtbl;
    void v1c(void* p) { mpVtbl->v1c(this, p); }
    void v20(void* p) { mpVtbl->v20(this, p); }
};
struct IUISystemVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    IUISub* (__thiscall* GetSub)(void*);                                     // +0x20
};
struct IUISystem {
    IUISystemVtbl* mpVtbl;
    IUISub* GetSub() { return mpVtbl->GetSub(this); }
};
struct IMovieSystemVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24; void* f28; void* f2c;
    bool (__thiscall* IsPlaying)(void*);                                     // +0x30
    const wchar_t* (__thiscall* GetTitle)(void*);                            // +0x34
};
struct IMovieSystem_s00f0_4140 {
    IMovieSystemVtbl* mpVtbl;
    bool IsPlaying() { return mpVtbl->IsPlaying(this); }
    const wchar_t* GetTitle() { return mpVtbl->GetTitle(this); }
};
struct ISaveAreaVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24;
    const wchar_t* (__thiscall* GetName)(void*);                             // +0x28
};
struct ISaveArea_s00f0_4140 {
    ISaveAreaVtbl* mpVtbl;
    const wchar_t* GetName() { return mpVtbl->GetName(this); }
};
struct IAudioSystemVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* (__thiscall* v20)(void*);                                          // +0x20
    void* f24; void* f28; void* f2c; void* f30; void* f34;
    void  (__thiscall* v38)(void*, uint32_t);                                // +0x38
    void* f3c;
    void  (__thiscall* v40)(void*, uint32_t, uint32_t);                      // +0x40
    void* f44; void* f48; void* f4c; void* f50; void* f54;
    void  (__thiscall* v58)(void*);                                          // +0x58
};
struct IAudioSystem_s00f0_4140 {
    IAudioSystemVtbl* mpVtbl;
    void* v20() { return mpVtbl->v20(this); }
    void v38(uint32_t a) { mpVtbl->v38(this, a); }
    void v40(uint32_t a, uint32_t b) { mpVtbl->v40(this, a, b); }
    void v58() { mpVtbl->v58(this); }
};
extern IAppProps*     gAppProps;                  // 0x015FD918
extern AutoRefCount<RefB> gTokenTranslator;       // 0x015F7CF4
IUISystem*             UISystem();                // 0x0067DE40
IMovieSystem_s00f0_4140*          MovieSystem_s00f0_4140();             // 0x0067CB10
ISaveArea_s00f0_4140*             GetSaveArea_s00f0_4140(uint32_t id);  // 0x006B1F90
IAudioSystem_s00f0_4140*          AudioGetSystemAT();        // 0x00A206F0
bool                   GetYTPrompt();             // 0x0063B890
void SP_UpdateMouseFocus(int a);                                               // 0x00804F50
struct CEdObj { void Method(bool a); };                                        // 0x00ED4F00
void FUN_00F040E0(eastl::string_s00f0_4140* s);                                           // 0x00F040E0
struct cPlayModeTokenTranslator { cPlayModeTokenTranslator* ctor(); };         // 0x006345B0
struct CSPUILayoutCtor { CSPUILayoutCtor* ctor(); };                           // 0x00810000
struct Vec20 {
    uint32_t* mpBegin;                                              // +0x00
    uint32_t* mpEnd;                                                // +0x04
    uint32_t* mpCap;                                                // +0x08
    uint32_t  mPad[2];
    void DestroyRange(void* pBegin, void* pEnd);                    // 0x0070F520
};
void RemoveHandler(void* h, void* a, void* b, void* c, void* d);   // 0x00571DB0
namespace Simulator {
struct cScenarioYouTube {
    void* mpVtbl0;             // +0x00
    void* mpVtbl4;             // +0x04
    void* mpVtbl8;             // +0x08
    void* mpVtblc;             // +0x0c
    RefA* mpRef10;             // +0x10
    AtomicRefCounted* mpMsgHandler;  // +0x14
    void* mpMsgA;              // +0x18
    void* mpMsgB;              // +0x1c
    void* mpMsgC;              // +0x20
    void* mpMsgD;              // +0x24
    uint32_t mField28;         // +0x28
    cSPUILayout_s00f0_4140* mLayout;      // +0x2c
    IWindow_s00f0_4140* mpWin30;          // +0x30
    IWindow_s00f0_4140* mpWin34;          // +0x34
    IWindow_s00f0_4140* mpWin38;          // +0x38
    uint32_t mWidth;           // +0x3c
    uint32_t mHeight;          // +0x40
    float mFloat44;            // +0x44
    float mFloat48;            // +0x48
    float mFloat4c;            // +0x4c
    bool mBool50;              // +0x50
    bool mBool51;              // +0x51
    bool mBool52;              // +0x52
    char mPad53;
    eastl::string16_s00f0_4140 mStr54;    // +0x54
    eastl::string16_s00f0_4140 mStr64;    // +0x64
    uint32_t mField74;         // +0x74
    bool mBool78;              // +0x78
    bool mBool79;              // +0x79
    char mPad7a[2];
    eastl::string_s00f0_4140 mStr7c;      // +0x7c
    eastl::string_s00f0_4140 mStr8c;      // +0x8c
    eastl::string_s00f0_4140 mStr9c;      // +0x9c
    eastl::string16_s00f0_4140 mStrAc;    // +0xac
    bool mBoolBc; bool mBoolBd; bool mBoolBe; bool mBoolBf;
    bool mBoolC0; bool mBoolC1; bool mBoolC2; bool mBoolC3;
    bool mBoolC4; bool mBoolC5; bool mBoolC6;
    char mPadC7;
    uint32_t mFieldC8;         // +0xc8
    RefA* mpRefCc;             // +0xcc
    Vec20 mVec0;               // +0xd0
    Vec20 mVec1;               // +0xe4
    bool mBoolF8;              // +0xf8
    bool mBoolF9;              // +0xf9
    char mPadFa[6];
    char mStopwatch[0x28];     // +0x100 EA::LimitStopwatch

    void  FUN_00f04140(const eastl::string_s00f0_4140* s);
    void  FUN_00f041a0();
    void  FUN_00f043d0();
    void  FUN_00f044d0();
    void* FUN_00f046e0(unsigned flags);
    void* FUN_00f04740();
    void  FUN_00f04910();
    void  FUN_00f04ad0();
    void  FUN_00f04bd0();
    void  FUN_00f04d10(int arg);
};
}
using Simulator::cScenarioYouTube;
// ---- items of slice s00f04140 end

// ---- items of slice s00f05110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const char gEmptyString16[];              // 0x1667bac
extern "C" void __cdecl operator_delete(void* p);    // 0xf47380
extern "C" void* __cdecl Audio_GetSystemAT();                      // 0xa206f0
extern "C" void __cdecl ScenarioTutorials_CloseWindow();           // 0xefcae0
extern "C" void* __cdecl GetTriggerMgr();                          // 0xb3d4d0
extern "C" void __cdecl UpdateMouseFocus(int on);                  // 0x804f50
extern "C" void* __cdecl SP_GetSaveArea(int id);                   // 0x6b1f90
extern "C" void* __cdecl UIHints_Get();                // 0x67cac0
extern "C" void* __cdecl WindowManager();              // 0x67caa0
extern "C" void* __cdecl GameTimeManager();            // 0xb3d380
extern "C" void __cdecl SPUIHelpers_BeginModal(void*, int, int);      // 0x8099a0
extern "C" void __cdecl AutoSizeWindowForText(void* win, int a, int b); // 0x806e40
extern "C" void* __cdecl PropertyManager();                       // 0x67de30
extern "C" void* g_ytLoginKey;                                     // 0x15ad36c
typedef unsigned char  uchar;
typedef unsigned short ushort;
template<class T> inline T& at(void* p, int off) { return *(T*)((char*)p + off); }
template<class T> inline T& at(int p, int off) { return *(T*)((char*)(long)p + off); }
struct EaStr
{
    char* mpBegin;      // 0x00
    char* mpEnd;        // 0x04
    char* mpCap;        // 0x08
    char* mpSpare;      // 0x0c
    EaStr();
    int    sprintf(const char* fmt, ...);            // 0x472fe0
    EaStr& append_sprintf(const char* fmt, ...);     // 0x5f9450
};
inline EaStr::EaStr()
{
    mpBegin = (char*)gEmptyString16;
    mpEnd   = (char*)gEmptyString16;
    mpCap   = (char*)gEmptyString16 + 1;
}
struct YtAuthMsg
{
    EaStr mToken;       // 0x00
    EaStr mUser;        // 0x10
    EaStr mExtra;       // 0x20
    uchar mPrivate;     // 0x30
    ~YtAuthMsg();       // ??1cEditorYouTubeAuthenticationMessage@@QAE@XZ
};
struct Movie
{
    void SendPublicAuth();      // 00f05c40
    void LoginToYouTube();      // 00f05d00
    void CloseUpload();         // 00f05b00
    void RefreshPanel();        // 00f05790
    void LayoutYouTube();       // 00f05110
    void SaveUploadSettings();  // 00f055c0
};
extern "C" void* gAppProperties_s00f0_5110;                     // 0x15fd918
struct Prop { uchar* GetBool(); };                   // 0x41e920
struct PropList { uchar GetDescription(uint id); };   // 0x6a25a0
struct EaStr16
{
    char* mpBegin;      // 0x00
    char* mpEnd;        // 0x04
    char* mpCap;        // 0x08
    int   mSpare;       // 0x0c
    EaStr16();
    EaStr16(const wchar_t* text);
    ~EaStr16();
    void Format(const char* fmt, ...);                  // 0x41e050
    void assign(const wchar_t* first, const wchar_t* last);   // 0x423650
    void RangeInitialize(const wchar_t* text);          // 0x579a90
    int  find(const wchar_t* needle, int pos);          // 0x608340
    void erase(int pos, int count);                     // 0x4228e0
};
inline EaStr16::EaStr16(const wchar_t* text)
{
    mpBegin = 0;
    mpEnd   = 0;
    mpCap   = 0;
    RangeInitialize(text);
}
inline EaStr16::EaStr16()
{
    mpBegin = (char*)gEmptyString16;
    mpEnd   = (char*)gEmptyString16;
    mpCap   = (char*)gEmptyString16 + 2;
}
inline EaStr16::~EaStr16()
{
    if (((int)(mpCap - mpBegin) & ~1) > 2 && mpBegin != 0)
        operator_delete(mpBegin);
}
struct RectF
{
    float left, top, right, bottom;
    uchar Intersect(const RectF& a, const RectF& b);   // 0x634b60
};
struct cString_s00f0_5110
{
    char pad[0x10];
    cString_s00f0_5110(uint id, uint key, const void* text);      // 0x6b5770
    ~cString_s00f0_5110();                                        // 0x6b5240
    const void* GetText();                             // 0x6b55c0
};
struct UIHints { int SetFlag(char flag, int value); }; // 0x67c420
struct SpGameTime { void IncPauseGate(int tag); };     // 0xb32220
struct Layout
{
    void* FindWindowByID(uint id, char recurse);       // 0x8105b0
};
extern "C" uchar __cdecl SP_SaveNamedResource(void* key, const void* name, void* area); // 0x6b4010
struct Variant
{
    int mFlags;             // type flags (bit 2 = destructible)
    int mPad[0x0b];
    void Construct(int type, int sub, const void* data, int size, int count);  // 0x93dd80
    void Destruct(bool free);                                                  // 0x93db80
};
struct CPropList { CPropList* init(); };      // 0x6a1c40
// ---- items of slice s00f05110 end

// ---- items of slice s00f05ee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable: 4100)
typedef unsigned int   u32;
typedef unsigned char  u8;
struct MovieHandler { void* mVtbl; u32 mSrv;                   // IHandler subobject at +0x04
    void HandleMessage(u32 unused, u32 msgId);                 // 0x00f063c0
};
struct VtblPart { void* mVtbl0; };                            // primary vtable at +0x00
void  __cdecl FUN_00809db0(MovieHandler* obj, u32 msg);       // 0x00809db0 UI::CalloutMessageBox
void* __cdecl FUN_00607a60();                                 // 0x00607a60 AuthManager
void  __cdecl FUN_0063bc70();                                 // 0x0063bc70 CreateConnectingDialog
u8    __cdecl OpenBrowser_s00f0_5ee0(const wchar_t* url, int flag);      // 0x00935fb0
static inline void* VT(void* o, int off) { return ((void**) (*(void**) o))[off / 4]; }
typedef void  (__thiscall *FnU0)(void*);
typedef char  (__thiscall *FnC0)(void*);
namespace SP {
struct RefVec {
    void** mpBegin;   // +0
    void** mpEnd;     // +4
    void** mpCap;     // +8
    void  Release(void* elem);                     // 0x00760c40
    void  DoInsertValue(void* where, void* val);   // 0x00425a80
    void  DestroyRange(void* a, void* b);          // 0x0070f520
};
}
namespace SP {
class cDirectPropertyList_s00f0_5ee0 { public: char m[0x18];           // +0x100
    void SetBoolProperty();                          // 0x0093a2e0
};
}
namespace SP {
class cSPPlayModeSubModeMovie_s00f0_5ee0 : public VtblPart, public MovieHandler { public:
    char   m08[8];        // +0x0c
    void*  mServer;       // +0x14
    void*  mHandlerObj;   // +0x18
    void*  mMsgTable;     // +0x1c
    u32    mMsgCount;     // +0x20
    u32    m24;           // +0x24
    u32    mDialog;       // +0x28
    void*  mUI;           // +0x2c  cSPUILayout*
    char   m30[8];        // +0x30
    void*  m38;           // +0x38
    char   m3c[0x18];     // +0x3c
    void*  m54;           // +0x54  wchar_t*
    char   m58[0x1c];     // +0x58
    u32    m74;           // +0x74
    bool   m78;           // +0x78
    char   m79[3];        // +0x79
    void*  m7c;           // +0x7c  char*
    char   m80[0x0c];     // +0x80
    void*  m8c;           // +0x8c  char*
    char   m90[0x0c];     // +0x90
    void*  m9c;           // +0x9c  char*
    char   ma0[0x1c];     // +0xa0
    bool   mbc;           // +0xbc
    bool   mbd;           // +0xbd
    bool   mbe;           // +0xbe
    bool   mbf;           // +0xbf
    bool   mc0;           // +0xc0
    bool   mc1;           // +0xc1
    bool   mc2;           // +0xc2
    bool   mc3;           // +0xc3
    bool   mc4;           // +0xc4
    char   mc5[3];        // +0xc5
    u32    mc8;           // +0xc8
    char   mcc[4];        // +0xcc
    RefVec mVecA;         // +0xd0
    char   mdc[8];        // +0xdc
    RefVec mVecB;         // +0xe4
    char   mf0[8];        // +0xf0
    bool   mf8;           // +0xf8
    bool   mf9;           // +0xf9
    char   mfa[6];        // +0xfa
    cDirectPropertyList_s00f0_5ee0 mPropList;  // +0x100
    long long mDeadline;  // +0x118

    void  PostRecordingDone();                        // 0x00f05ee0
    bool  CheckRecordingPreconditions();              // 0x00f06150
    void  ShowUploadProgressDialog();                 // 0x00f065d0
    void  ShowSendVideoURLDialog();                   // 0x00f06660
    bool  SelectRecording(int* pIndex, void* pOut);   // 0x00f066c0
    void  Update(u32 dt);                             // 0x00f067b0
    bool  BeginRecording(u8 flag);                    // 0x00f069a0
    void  ClearIndicatorTextures();                   // 0x00f06ac0
    void  RegisterMessageHandlers();                  // 0x00f06ce0

    // callees in this module (declared only)
    void FUN_00f05c40();                              // 0x00f05c40
    void FUN_00f05dc0(void* msg);                     // 0x00f05dc0
    void FUN_00f05d00();                              // 0x00f05d00 LoginToYouTube
    void FUN_00f055c0();                              // 0x00f055c0
    void FUN_00f05790();                              // 0x00f05790
    void FUN_00f03de0();                              // 0x00f03de0
    void FUN_00f03e40();                              // 0x00f03e40
    void FUN_00f03e90();                              // 0x00f03e90
    void FUN_00f03d20();                              // 0x00f03d20
    void FUN_00f03d50();                              // 0x00f03d50
    void FUN_00f041a0();                              // 0x00f041a0
    void FUN_00f044d0();                              // 0x00f044d0
    void FUN_00f03fc0(int);                           // 0x00f03fc0
    void FUN_00f04070(int);                           // 0x00f04070

    MovieHandler* GetHandlerSub() { return static_cast<MovieHandler*>(this); }
};
}
// ---- items of slice s00f05ee0 end

// ---- items of slice s00f06d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*        F_0067dd30();               // 0x0067dd30 ConfigManager
extern void*        F_00607a60();               // 0x00607a60 Pollen::AuthManager
extern int          F_00435e90();               // 0x00435e90 GetRecorderState
extern void         F_00435ed0(unsigned int id, unsigned int state); // 0x00435ed0 RecordEvent2
extern void         F_00809db0(void* ctx, const wchar_t* text);      // 0x00809db0 CalloutMessageBox
extern unsigned char F_0063b890();              // 0x0063b890 GetYTPrompt
extern unsigned char F_0063c0a0();              // 0x0063c0a0 IsLocaleEnglish
extern void         F_0063bc70();               // 0x0063bc70 CreateConnectingDialog
extern void         F_0063c060(bool b);         // 0x0063c060 DestroyConnectingDialog
extern void*        F_00a206f0();               // 0x00a206f0 EA::Audio::GetSystemAT
extern void*        F_0067cb10();               // 0x0067cb10 MovieSystem
extern void*        F_006b1f90(int area);       // 0x006b1f90 SP_GetSaveArea
extern void         F_004af210(void* props, int key, unsigned int* out); // 0x004af210
extern void         F_00935fb0(const wchar_t* url, bool b);          // 0x00935fb0 OpenBrowser
extern void         F_00472fe0(void* dest, const char* fmt, ...);    // 0x00472fe0 string::sprintf
extern void*        F_00f04530(bool b);         // 0x00f04530
extern void*        F_0067ddd0();               // 0x0067ddd0 EffectsManager
extern void*        F_0067caa0();               // 0x0067caa0 WindowManager
extern void*        F_0067dcc0();               // 0x0067dcc0 MessageServer
extern void*        F_00b3d380();               // 0x00b3d380 GameTimeManager
extern const wchar_t g_01667bac[];              // 0x01667bac eastl::gEmptyString16
extern void*         g_015fd918;                // 0x015fd918 app properties
struct Msg;
union PtrInt {
    void* p;
    int   i;
};
struct Msg {                    // message handed to the dispatchers
    char   m00[8];
    int    m08;                 // +0x08 message kind (1 / 0x287259f6)
    int    m0c;                 // +0x0c message id
    PtrInt m10;                 // +0x10 payload
    void*  m14;                 // +0x14
    void*  m18;                 // +0x18 payload
    void*  m1c;                 // +0x1c
    void*  m20;                 // +0x20 payload
};
struct SubMsg {                 // object pointed at by Msg::m18 / Msg::m20
    char m00[0x0c];
    int  m0c;                   // +0x0c
};
struct WStr {                   // SP::WString, 16 bytes (eastl string + allocator tag)
    const wchar_t* mBegin;      // +0x00
    const wchar_t* mEnd;        // +0x04
    const wchar_t* mCap;        // +0x08
    unsigned int   mAllocator;  // +0x0c
    void append(const wchar_t* s);              // 0x005c3d90
    void DeallocateSelf();                      // 0x00933960
    void F_0057cb60(const WStr& src);           // 0x0057cb60  operator=
};
struct CharStr {                // eastl::basic_string<char>, 12 bytes
    char* mBegin;
    char* mEnd;
    char* mCap;
};
struct DateTime_s00f0_6d40 {               // 8 bytes on the original frame
    int mData[2];
    void Set(int param);                        // 0x0092e3d0
    int  GetParameter(int param);               // 0x0092df80
};
struct CStringStub {            // SP::cString
    char mData[0x14];
    void Ctor(unsigned int a, unsigned int b, const wchar_t* c);  // 0x006b5770
    const wchar_t* GetText();                                     // 0x006b55c0
    void Dtor();                                                  // 0x006b5240
};
struct TextSlots {              // pointed at by g_015f7cf4
    char           m00[0x30];
    const wchar_t* m30;         // +0x30
    char           m34[0x10];
    const wchar_t* m44;         // +0x44
    const wchar_t* m48;         // +0x48
    const wchar_t* m4c;         // +0x4c
    const wchar_t* m50;         // +0x50
    const wchar_t* m54;         // +0x54
};
struct PtrVector {              // vector of smart pointers
    void* mBegin;
    void* mEnd;
    void* mCap;
    void F_00420660(void** value);              // 0x00420660
};
struct TempRef {                // smart-pointer wrapper (one pointer)
    void* mPtr;
    void F_00576620();                          // 0x00576620
};
struct AutoRef_s00f0_6d40 {                // wrapper around PhotoHandler::m_c4
    void* F_00a16f40();                         // 0x00a16f40
};
struct LimitStopwatch {
    char mData[0x10];
    void F_0093a480(unsigned int ms, bool b);   // 0x0093a480
};
struct Layout_s00f0_6d40 {
    void* F_008105b0(int id, int flag);         // 0x008105b0
};
struct GameTime {
    void F_00b32250(unsigned int id);           // 0x00b32250
};
struct MainWin {
    void F_008143a0();                          // 0x008143a0
};
struct Movie_s00f0_6d40 {                  // SP::cSPPlayModeSubModeMovie
    char      m00[0x04];
    char      m04[0x24];        // +0x04 callout-message-box context
    int       m28;              // +0x28 dialog state
    Layout_s00f0_6d40*   m2c;              // +0x2c UI layout
    char      m30[0x0c];
    uint32_t  m3c;              // +0x3c
    uint32_t  m40;              // +0x40
    char      m44[0x10];
    WStr      m54;              // +0x54
    WStr      m64;              // +0x64
    int       m74;              // +0x74
    bool      m78;              // +0x78
    bool      m79;              // +0x79

    void F_00f065d0();                          // 0x00f065d0 ShowUploadProgressDialog
    void F_00f06660();                          // 0x00f06660 ShowSendVideoURLDialog
    void F_00f069a0(int a);                     // 0x00f069a0 BeginRecording
    void F_00f06ac0();                          // 0x00f06ac0 ClearIndicatorTextures
    void F_00f03fc0(int a);                     // 0x00f03fc0
    void F_00f044d0();                          // 0x00f044d0
    void F_00f03e20();                          // 0x00f03e20
    void F_00f03e40();                          // 0x00f03e40
    void F_00f03e90();                          // 0x00f03e90
    void F_00f03fa0();                          // 0x00f03fa0
    void F_00f05790();                          // 0x00f05790
    void F_00f05c40();                          // 0x00f05c40 SendPublicAuth
    void F_00f04bd0();                          // 0x00f04bd0
    void F_00f05b00();                          // 0x00f05b00 CloseUpload
    void F_00f04070(int a);                     // 0x00f04070
    bool F_00f06d40(int msgId, Msg* msg);       // 0x00f06d40
};
struct PhotoHandler {           // handler subobject embedded at Movie+8
    char      m00[0x20];
    int       m20;              // +0x20 = Movie+0x28 dialog state
    Layout_s00f0_6d40*   m24;              // +0x24 = Movie+0x2c UI layout
    char      m28[0x4c];
    CharStr   m74;              // +0x74
    char      m80[0x04];
    CharStr   m84;              // +0x84
    char      m90[0x14];
    WStr      m_a4;             // +0xa4
    bool      m_b4;             // +0xb4
    bool      m_b5;             // +0xb5
    char      m_b6[0x01];
    bool      m_b7;             // +0xb7
    bool      m_b8;             // +0xb8
    char      m_b9[0x01];
    bool      m_ba;             // +0xba
    char      m_bb[0x01];
    bool      m_bc;             // +0xbc
    bool      m_bd;             // +0xbd
    bool      m_be;             // +0xbe
    char      m_bf[0x01];
    uint32_t  m_c0;             // +0xc0
    void*     m_c4;             // +0xc4
    char      m_c8[0x14];
    PtrVector m_dc;             // +0xdc
    char      m_e8[0x08];
    bool      m_f0;             // +0xf0
    bool      m_f1;             // +0xf1
    char      m_f2[0x06];
    LimitStopwatch m_f8;        // +0xf8

    bool F_00f072b0(int msgId, Msg* msg);       // 0x00f072b0
};
extern WStr*        F_0041e050(WStr* dest, const wchar_t* fmt, ...); // 0x0041e050 WStr_Format
extern unsigned char F_0063d170(WStr* a, WStr* b); // 0x0063d170 ConstructVideoURL
extern TextSlots*    g_015f7cf4;                // 0x015f7cf4
// ---- items of slice s00f06d40 end

// @ 0x0063b5c0
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

// @ 0x0063caf0
void cSPPlayModeSubModeMovie_s0063_caf0::FUN_0063caf0(SubModeParams* p)
{
    Init(p);
    mUI = p->mUI;
    mMovieSystem = MovieSystem();
    mb22c0 = false;
    mb22c1 = false;
    mCurrFilename[0] = 0;
    mCurrPathname[0] = 0;
    mb235d = false;
    mb235e = false;
    IPropList_s0063_caf0* pl = gAppProperties_s0063_caf0;
    if (pl) {
        void* pr;
        if (GetTyped(pl, 0x456f974, 0xd, &pr))
            mTime = *((cProp*)pr)->GetFloat();
        if (GetTyped(pl, 0x456f975, 10, &pr))
            mWidth = *((cProp*)pr)->GetUInt();
        if (GetTyped(pl, 0x456f976, 10, &pr))
            mHeight = *((cProp*)pr)->GetUInt();
        if (GetTyped(pl, 0x456f977, 0xd, &pr))
            mFPS = *((cProp*)pr)->GetFloat();
        if (GetTyped(pl, 0x456f978, 0xd, &pr))
            mQuality = *((cProp*)pr)->GetFloat();
        if (GetTyped(pl, 0x456f979, 1, &pr))
            mAudio = *((cProp*)pr)->GetBool();
    }
    mField22c8 = mWidth;
    mField22cc = mHeight;
    LoadYouTubeCredentials();
    mUI->SetYTUsername(*(eastl::string_s0063_caf0*)&mField22fc);
    mUI->SetYTPassword(*(eastl::string_s0063_caf0*)&mField234c);
    mUI->SetYTPrompt(GetConfigManager_s0063_caf0()->GetValue(0x5664a8b) != 0);
    IMessageServer_s0063_caf0* ms = (IMessageServer_s0063_caf0*)GetMessageServer_s0063_caf0();
    void* h = (char*)this + 0x14;
    mAutoServer = ms;
    mAutoHandler = h;
    mAutoTable = gMsgTable;
    mAutoCount = 0xc;
    mAutoE = 0;
    if (ms && h) {
        for (uint32_t i = 0; i < 12; ++i)
            ms->AddHandler(h, gMsgTable[i]);
    }
    if (mMovieSystem->IsRecording())
        OnMovieRecorded();
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

// @ 0x0063d9e0
void cSPPlayModeSubModeMovie_s0063_d9e0::FUN_0063d9e0()
{
    mDoVideoUpload = true;
    mVideoUploadComplete = false;
    mVideoUploadSuccess = false;

    eastl::string16_s0063_d9e0 req;                       // constructed by 0x63d050, then reformatted
    ConstructYouTubeVideoUploadXMLRequest(&req);              // 0x63d050

    // Convert the current filename to UTF-16 and format it (e.g. "name.avi") into req.
    eastl::string16_s0063_d9e0 fnW = EA::ConvertToString16_s0063_d9e0(mCurrFilename, -1);   // 0x93c5a0
    WStr_Format(&req, L"%s.avi", fnW.c_str());                // 0x41e050

    // Ask the save area for a suitable resource name/slot.
    ISaveArea_s0063_d9e0* sa = GetSaveArea_s0063_d9e0(0x11ac197);                   // 0x6b1f90
    eastl::string16_s0063_d9e0 extra;
    sa->SetName(extra.mpBegin, 0, 2);                         // vtbl[0x68] (arg plumbing)

    // Build the upload payload (five char strings + a 3-dword key + the XML request).
    cEditorYouTubeVideoUploadMessage_s0063_d9e0 msg;
    CString_Sprintf((eastl::string_s0063_d9e0*)&msg.mUsername, "%s", mYTUsername.mpBegin);   // 0x472fe0
    CString_Sprintf((eastl::string_s0063_d9e0*)&msg.mClientID, "%s", mYTAuthToken.mpBegin);
    CString_Sprintf((eastl::string_s0063_d9e0*)&msg.mAuthenticationToken, "%s", (const char*)g_1524444);
    CString_Sprintf((eastl::string_s0063_d9e0*)&msg.mDeveloperKey, "%s", fnW.mpBegin);
    CString_Sprintf((eastl::string_s0063_d9e0*)&msg.mVideoFilename, "%s", mYTUsername.mpBegin);
    CString_Sprintf((eastl::string_s0063_d9e0*)&msg.mXMLRequest, "%s", req.mpBegin);

    IMessageServer* ms = GetMessageServer();                  // 0x67dcc0
    ms->PostMessage(0x55e8bc8, &msg, 0);                      // vtbl[0x14]

    msg.~cEditorYouTubeVideoUploadMessage_s0063_d9e0();                  // 0x63c750
    (void)extra;
}

// @ 0x0063dc40
void cSPPlayModeSubModeMovie_s0063_d9e0::FUN_0063dc40()
{
    // 1. Look up / create the property list that carries the YouTube credentials.
    uint32_t key = FNV1_String16A(0x811c9dc5, g_1524440, 1);  // 0x932f30
    IPropertyList_s0063_d9e0* pm = (IPropertyList_s0063_d9e0*)GetPropertyManager_s0063_d9e0(); // 0x67de30

    void* pl = 0;                                             // [esp+0x10]
    if (pl)
        ((IReleasable*)pl)->Release();                        // stale-slot release
    pm->v2c(key, 0x11ac192, &pl);                             // vtbl[0x2c] GetProperty

    if (!pl) {
        void* p = operator_new_ea(0x38, (const char*)0x13eb430, 0, 0, 0, 0);  // 0x0F473A0
        if (p)
            p = PropertyList_Ctor(p, 0);                      // 0x6a1c40 (this in ecx)
        else
            p = 0;
        if (p != pl) {
            void* old = pl;
            if (p)
                ((IReleasable*)p)->r0();                      // vtbl[0]
            pl = p;
            if (old)
                ((IReleasable*)old)->Release();               // vtbl[4]
        }
        char* q = (char*)pl + 8;
        *(uint32_t*)(q + 0) = key;                            // +8
        *(uint32_t*)(q + 4) = 0xb1b104;                       // +0xc
        *(uint32_t*)(q + 8) = 0x11ac192;                      // +0x10
    }

    // 2. Publish the username as a property (0x93dd80 builds the Variant from a string16).
    Variant_s0063_d9e0 v1;
    Variant_FromString16(&v1, 0, &mYTUsername, 1, 0x10, 9, 0x12);   // 0x93dd80
    ((IPropertyList_s0063_d9e0*)pl)->v14(0x5664bf5, &v1);                   // vtbl[0x14]
    if (v1.flags & 4)
        Variant_Destruct(&v1, 0);                                // 0x93db80

    // 3. Encrypt the password, then publish it as a property.
    NoThrowStr enc;                                              // [esp+0x14] (wstring-shaped temp)
    Encrypt(&enc, &mYTPassword);                                 // 0x60bcf0
    Variant_s0063_d9e0 v2;
    Variant_FromString16(&v2, 0, &enc, 1, 0x10, 9, 0x12);        // 0x93dd80
    ((IPropertyList_s0063_d9e0*)pl)->v14(0x5664bf6, &v2);                   // vtbl[0x14]
    if (v2.flags & 4)
        Variant_Destruct(&v2, 0);                                // 0x93db80

    // 4. Save the credentials through the named save area.
    ISaveArea_s0063_d9e0* sa = GetSaveArea_s0063_d9e0(0x11ac192);                      // 0x6b1f90
    if (sa) {
        NoThrowStr name;                                         // [esp]
        SaveNamedResource((eastl::string_s0063_d9e0*)&name, g_1524440, sa); // 0x6b4010
    }

    // 5. Release the property list.
    if (pl)
        ((IReleasable*)pl)->Release();                           // vtbl[4]
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

// @ 0x00df5430
void cGalaxyGameEntryUIStateMachine::FUN_00df5430(int mode)
{
    GalaxyView* view = (GalaxyView*)this;
    IWindow_s00df_47b0* window = view->mLayout54.FindWindowByID(0x5d2bdf8, true);
    window->SetFlag(1, true);
    window->SetFlag(2, true);

    IWindow_s00df_47b0* textWindow = view->mLayout54.FindWindowByID(0x5006000, true);
    if (!textWindow)
        return;

    cString_s00df_47b0 text;
    switch (mode) {
    case 0:
        text.Load(0xd7f9d626, 0x5d65f2c, L"Patch Downloading...(PLACEHOLDER)");
        break;
    case 1:
        text.Load(0xd7f9d626, 0x5ee1440, L"Download Paused (PLACEHOLDER)");
        break;
    }

    textWindow->SetText(text.GetText());
}

// @ 0x00df54f0
long double cGalaxyGameEntryUIStateMachine::FUN_00df54f0(float offset)
{
    GalaxyView* view = (GalaxyView*)this;
    if (view->m_count4c == 0)
        return 0.0f;
    const float count = (float)view->m_count4c;
    const float value = (float)view->m_value50;
    return ((long double)1.0 / (long double)count) *
           ((long double)value + (long double)offset);
}

// @ 0x00df5540
void cGalaxyGameEntryUIStateMachine::FUN_00df5540()
{
    GalaxyView0c* view = (GalaxyView0c*)this;
    IWindow_s00df_47b0* window = view->mLayout0c.FindWindowByID(0x6383590, true);
    if (window)
        FUN_008099a0(window, 0, 1);
}

// @ 0x00df5570
bool __stdcall FUN_00df5570(void* unused, void* event)
{
    (void)unused;
    if (*(uint32_t*)((char*)event + 8) == 0x287259f6) {
        void* object = *(void**)event;
        int result = ((int (__fastcall*)(void*))VTFN(object, 0x1c / 4))(object);
        if (result == 0x6383360) {
            cMessageServer* server = MessageServer();
            server->post(0x6382db7, 0, 0);
            return true;
        }
    }
    return false;
}

// @ 0x00df55b0
void cGalaxyGameEntryUIStateMachine::FUN_00df55b0(int mode)
{
    FUN_00df5430(mode);
    GalaxyView* view = (GalaxyView*)this;

    IWindow_s00df_47b0* window = view->mLayout54.FindWindowByID(0x42e2e38, true);
    if (window)
        window->SetText((const wchar_t*)0x013ec468);

    window = view->mLayout54.FindWindowByID(0x431e538, true);
    if (window)
        FUN_008099a0(window, 0, 1);
}

// @ 0x00df5610
void cGalaxyGameEntryUIStateMachine::FUN_00df5610(float t)
{
    GalaxyView* view = (GalaxyView*)this;
    void* effect = view->m_effect30;
    if (effect == 0)
        return;

    float value[4];
    const float x = view->m_x34;
    const float y = view->m_y38;
    value[1] = y;
    value[0] = x;
    value[3] = view->m_w40;
    value[2] = (view->m_z3c - x) * t + x;
    ((Effect*)effect)->SetValue(value);
}

// @ 0x00df5670
void cDownloadDialog::FUN_00df5670(char b)
{
    m_paused = b;
    find_window:
    if (b != 0) {
        // one cString on every path through this branch -> fold all FindWindowByID calls
        cString_s00df_5670 storage;
        cSPUILayout_s00df_5670* lay = Layout();
        IWinNode* w = (IWinNode*)lay->FindWindowByID(0x5d2bdf8, 1);
        w->v7c(1, 1);
        w->v7c(2, 1);
        IWinNode* w2 = (IWinNode*)lay->FindWindowByID(0x5006000, 1);
        if (w2) {
            storage.Load(0xd7f9d626, 0x5ee1440, L"Download Paused (PLACEHOLDER)");
            w2->v80(storage.GetText());
        }
        IWinNode* w3 = (IWinNode*)lay->FindWindowByID(0x5d66f78, 1);
        if (w3) {
            storage.Load(0xd7f9d626, 0x64bf9e1, L"Resume (PLACEHOLDER)");
            w3->v80(storage.GetText());
        }
        return;
    }
    FUN_00df5430(0);
    {
        cString_s00df_5670 storage;
        IWinNode* w = (IWinNode*)Layout()->FindWindowByID(0x5d66f78, 1);
        if (w) {
            storage.Load(0xd7f9d626, 0x61f1d7f, L"Pause (PLACEHOLDER)");
            w->v80(storage.GetText());
        }
    }
    (void)0;
    goto find_window;
}

// @ 0x00f04910
void Simulator::cScenarioYouTube::FUN_00f04910()
{
    Vec20& v1 = mVec1;
    mpVtbl0 = (void*)0x148b864;
    mpVtbl4 = (void*)0x148b858;
    mpVtbl8 = (void*)0x148b850;
    mpVtblc = (void*)0x148b840;
    _ReadWriteBarrier();

    v1.DestroyRange(v1.mpBegin, v1.mpEnd);
    if (v1.mpBegin && *((int*)v1.mpBegin - 1) != 0)
        operator delete(v1.mpBegin);

    mVec0.DestroyRange(mVec0.mpBegin, mVec0.mpEnd);
    if (mVec0.mpBegin && *((int*)mVec0.mpBegin - 1) != 0)
        operator delete(mVec0.mpBegin);

    if (mpRefCc)
        mpRefCc->Release();

    mStrAc.DeallocateSelf();
    mStr9c.DeallocateSelf();
    mStr8c.DeallocateSelf();
    mStr7c.DeallocateSelf();
    mStr64.DeallocateSelf();
    mStr54.DeallocateSelf();

    if (mpWin38)
        mpWin38->Release();
    if (mpWin34)
        mpWin34->Release();
    if (mpWin30)
        mpWin30->Release();
    if (mLayout)
        mLayout->Release();

    if (mpMsgHandler) {
        void* h = mpMsgHandler;
        mpMsgHandler = 0;
        RemoveHandler(h, mpMsgA, mpMsgB, mpMsgC, mpMsgD);
    }
    mpVtblc = (void*)0x13ec458;
    mpVtbl8 = (void*)0x13eb394;
    mpVtbl0 = (void*)0x13eb938;
}

// @ 0x00f04ad0
void Simulator::cScenarioYouTube::FUN_00f04ad0()
{
    FUN_00f044d0();
    UISystem()->GetSub()->v20(gTokenTranslator.mpObject);
    gTokenTranslator = (RefB*)0;

    mpWin38->RemoveProc(this);
    if (mpWin38) {
        IWindow_s00f0_4140* w = mpWin38;
        mpWin38 = 0;
        w->Release();
    }

    mLayout->FindWindowByID(0xffffffff, true)->RemoveProc(this);
    mLayout->Shutdown(1);
    if (mLayout) {
        cSPUILayout_s00f0_4140* l = mLayout;
        mLayout = 0;
        l->Release();
    }

    bool b = (uint32_t)(mVec0.mpEnd - mVec0.mpBegin) < 0x32;
    if (mpWin38) {
        IWindow_s00f0_4140* child = (IWindow_s00f0_4140*)mpWin38->FindChild(0x78d57d8, 1);
        if (child)
            child->SetFlag(2, b);
    }
    void* h = *(void**)((char*)gField_016c7aa4 + 0x14);
    if (h)
        ((CEdObj*)h)->Method(b);
}

// @ 0x00f04bd0
void Simulator::cScenarioYouTube::FUN_00f04bd0()
{
    IAudioSystem_s00f0_4140* au = AudioGetSystemAT();
    uint32_t u;
    if (au)
        u = (uint32_t)au->v20();
    else
        u = 0;

    au = AudioGetSystemAT();
    if (au) {
        au->v38(0x3475365);
        au->v40(0x3475381, 0x6f89c68e);
        au->v40(0x3475385, u);
        au->v58();
    }

    IMovieSystem_s00f0_4140* ms = MovieSystem_s00f0_4140();
    const wchar_t* p1 = ms->GetTitle();
    mStr54.Assign(p1, p1 + eastl::CharStrlen(p1));

    ISaveArea_s00f0_4140* sa = GetSaveArea_s00f0_4140(0x11ac197);
    const wchar_t* p2 = sa->GetName();
    mStr64.Assign(p2, p2 + eastl::CharStrlen(p2));

    mBool78 = true;
    mBool79 = true;
    mpWin30->SetFlag(1, 1);
    mpWin34->SetFlag(1, 0);
    SP_UpdateMouseFocus(1);
    mField74 = 0;
}

// @ 0x00f04d10
void Simulator::cScenarioYouTube::FUN_00f04d10(int arg)
{
    void* mem = EAAllocate(0x60, "Simulator/cPlayModeTokenTranslator", 0, 0, 0, 0);
    cPlayModeTokenTranslator* tt = mem ? ((cPlayModeTokenTranslator*)mem)->ctor() : 0;

    gTokenTranslator = (RefB*)tt;

    UISystem()->GetSub()->v1c(gTokenTranslator.mpObject);

    void* lmem = EAAllocate(0x18, "UI/cSPUILayout", 0, 0, 0, 0);
    cSPUILayout_s00f0_4140* layout = lmem ? (cSPUILayout_s00f0_4140*)((CSPUILayoutCtor*)lmem)->ctor() : 0;
    cSPUILayout_s00f0_4140* oldLayout = mLayout;
    if (layout != oldLayout) {
        if (layout) layout->AddRef();
        mLayout = layout;
        if (oldLayout) oldLayout->Release();
    }

    EA::ResourceMan::Key_s00f0_4140 key;
    key.mType = 0x784e37b4;
    key.mName = 0x510a95b;
    key.mInstance = 0x40464100;
    mLayout->Init(key, false, 0x5b598fa);

    cSPUILayout_s00f0_4140* lay = layout;
    lay->SetParentWin(lay->FindWindowByID(0xffffffff, true), true, 0x5b598fa);

    IWindow_s00f0_4140* w = lay->FindWindowByID(0x7916468, true);
    IWindow_s00f0_4140* old38 = mpWin38;
    if (w != old38) {
        if (w) w->AddRef();
        mpWin38 = w;
        if (old38) old38->Release();
    }
    mpWin38->AddProc(this);
    mLayout->FindWindowByID(0xffffffff, true)->AddProc(this);

    w = mLayout->FindWindowByID(0x78ec978, true);
    IWindow_s00f0_4140* old30 = mpWin30;
    if (w != old30) {
        if (w) w->AddRef();
        mpWin30 = w;
        if (old30) old30->Release();
    }

    w = mLayout->FindWindowByID(0x78d57d0, true);
    IWindow_s00f0_4140* old34 = mpWin34;
    if (w != old34) {
        if (w) w->AddRef();
        mpWin34 = w;
        if (old34) old34->Release();
    }

    IAppProps* props = gAppProps;
    if (props) {
        Property* prop;
        if (props->GetProperty(0x456f974, &prop) && prop->mnType == 0xd)
            mFloat48 = *prop->GetValueFloat();
        if (props->GetProperty(0x456f975, &prop) && prop->mnType == 10)
            mWidth = *prop->GetValueUInt();
        if (props->GetProperty(0x456f976, &prop) && prop->mnType == 10)
            mHeight = *prop->GetValueUInt();
        if (props->GetProperty(0x456f977, &prop) && prop->mnType == 0xd)
            mFloat44 = *prop->GetValueFloat();
        if (props->GetProperty(0x456f978, &prop) && prop->mnType == 0xd)
            mFloat4c = *prop->GetValueFloat();
        if (props->GetProperty(0x456f979, &prop) && prop->mnType == 1)
            mBool50 = *prop->GetValueBool();
        if (props->GetProperty(0x456f97a, &prop) && prop->mnType == 1)
            mBool51 = *prop->GetValueBool();
    }

    FUN_00f043d0();
    FUN_00F040E0(&mStr8c);
    FUN_00f04140(&mStr9c);

    bool bPrompt = GetYTPrompt();
    IWindow_s00f0_4140* hint = mLayout->FindWindowByID(0x5665f58, true);
    IControl_s00f0_4140* ctl = hint ? (IControl_s00f0_4140*)hint->GetControl(0x8ed27e7a) : 0;
    if (ctl)
        ctl->SetFlag(4, !bPrompt);

    if (MovieSystem_s00f0_4140()->IsPlaying())
        FUN_00f04bd0();

    bool b = (uint32_t)(mVec0.mpEnd - mVec0.mpBegin) < 0x32;
    if (mpWin38) {
        IWindow_s00f0_4140* child = (IWindow_s00f0_4140*)mpWin38->FindChild(0x78d57d8, 1);
        if (child)
            child->SetFlag(2, b);
    }
    void* h = *(void**)((char*)gField_016c7aa4 + 0x14);
    if (h)
        ((CEdObj*)h)->Method(b);
}

// @ 0x00f05110
void Movie::LayoutYouTube()
{
    cString_s00f0_5110 title(0x7518573e, 0x5e501eb, 0);
    EaStr16 text;
    EaStr16 before;
    EaStr16 after;
    bool iconFirst = true;

    const wchar_t* p = (const wchar_t*)title.GetText();
    const wchar_t* e = p;
    while (*e != 0)
        e++;
    text.assign(p, p + (e - p));

    void* icon  = ((Layout*)at<void*>(this, 0x2c))->FindWindowByID(0x5e51108, 1);
    void* label = ((Layout*)at<void*>(this, 0x2c))->FindWindowByID(0x5daa660, 1);

    EaStr16 marker(L"<youtubeicon>");

    int pos = text.find((const wchar_t*)marker.mpBegin, 0);
    if (pos != -1) {
        before.assign((const wchar_t*)text.mpBegin, (const wchar_t*)text.mpEnd);
        text.erase(pos, (int)(before.mpEnd - before.mpBegin) >> 1);
        before.erase(0, pos + ((int)(marker.mpEnd - marker.mpBegin) >> 1));
        if (((int)(text.mpEnd - text.mpBegin) & ~1) == 0) {
            after.assign((const wchar_t*)before.mpBegin, (const wchar_t*)before.mpEnd);
        } else {
            after.assign((const wchar_t*)text.mpBegin, (const wchar_t*)text.mpEnd);
            iconFirst = false;
        }
    }

    if (label != 0) {
        ((void (__thiscall*)(void*, const void*))((void**)*(void**)label)[0x80 / 4])(label, after.mpBegin);
        AutoSizeWindowForText(label, 0, 0);
    }

    float baseX;
    void* spanWin;
    if (!iconFirst) {
        RectF aR = *(RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)icon)[0x38 / 4])(icon);
        RectF* rb = (RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)label)[0x38 / 4])(label);
        RectF nb = *rb;
        nb.left   = aR.left;
        nb.right  = (rb->right - rb->left) + aR.left;
        nb.bottom = (rb->bottom - rb->top) + rb->top;
        ((void (__thiscall*)(void*, const RectF*))((void**)*(void**)label)[0x6c / 4])(label, &nb);

        float right = ((RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)label)[0x38 / 4])(label))->right + 3.0f;
        aR.right  = (aR.right - aR.left) + right;
        aR.left   = right;
        aR.bottom = (aR.bottom - aR.top) + aR.top;
        ((void (__thiscall*)(void*, const RectF*))((void**)*(void**)icon)[0x6c / 4])(icon, &aR);

        baseX = ((RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)label)[0x38 / 4])(label))->left;
        spanWin = icon;
    } else {
        baseX = ((RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)icon)[0x38 / 4])(icon))->left;
        spanWin = label;
    }
    float spanRight = ((RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)spanWin)[0x38 / 4])(spanWin))->right;

    void* panel = ((Layout*)at<void*>(this, 0x2c))->FindWindowByID(0x5b5ef50, 1);
    RectF* pr = (RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)panel)[0x38 / 4])(panel);
    float shift = (spanRight + baseX) * 0.5f - (pr->right - pr->left) * 0.5f;

    RectF ia = *(RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)icon)[0x38 / 4])(icon);
    ia.left   = ia.left - shift;
    ia.right  = (ia.right - (ia.left + shift)) + ia.left;
    ia.bottom = (ia.bottom - ia.top) + ia.top;
    ((void (__thiscall*)(void*, const RectF*))
     ((void**)*(void**)icon)[0x6c / 4])(icon, &ia);

    RectF la = *(RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)label)[0x38 / 4])(label);
    la.left   = la.left - shift;
    la.right  = (la.right - (la.left + shift)) + la.left;
    la.bottom = (la.bottom - la.top) + la.top;
    ((void (__thiscall*)(void*, const RectF*))
     ((void**)*(void**)label)[0x6c / 4])(label, &la);
}

// @ 0x00f055c0
void Movie::SaveUploadSettings()
{
    void* pm = PropertyManager();
    void* pl = 0;
    ((void (__thiscall*)(void*, int, int, void**))
     ((void**)*(void**)pm)[0x2c / 4])(pm, 0x3a39cb0d, 0x11ac192, &pl);

    if (pl == 0) {
        void* mem = EAAllocate(0x38, (const char*)0x148b8a4, 0, 0, 0, 0);
        pl = mem != 0 ? ((CPropList*)mem)->init() : 0;
        at<int>(pl, 8)  = 0x3a39cb0d;
        at<int>(pl, 0xc) = 0xb1b104;
        at<int>(pl, 0x10) = 0x11ac192;
    }

    Variant v;
    v.Construct(0x12, 9, (char*)this + 0x8c, 0x10, 1);
    ((void (__thiscall*)(void*, int, Variant*))
     ((void**)*(void**)pl)[0x14 / 4])(pl, 0x5664bf5, &v);
    if (v.mFlags & 4)
        v.Destruct(0);

    EaStr enc;
    Encrypt(&enc, (char*)this + 0x9c);

    Variant v2;
    v2.Construct(0x12, 9, &enc, 0x10, 1);
    ((void (__thiscall*)(void*, int, Variant*))
     ((void**)*(void**)pl)[0x14 / 4])(pl, 0x5664bf6, &v2);
    if (v2.mFlags & 4)
        v2.Destruct(0);

    void* area = SP_GetSaveArea(0x11ac192);
    if (area != 0)
        SP_SaveNamedResource(g_ytLoginKey, enc.mpBegin, area);
}

// @ 0x00f05790
void Movie::RefreshPanel()
{
    void* ui = *(void**)0x15f7cf4;
    at<int>(ui, 0x18) = at<int>(this, 0x54);
    if (!((PropList*)gAppProperties_s00f0_5110)->GetDescription(0x61b67b6)) {
        at<int>(*(void**)0x15f7cf4, 0x1c) = at<int>(this, 0x64);
        at<void*>(*(void**)0x15f7cf4, 0x58) = (void*)0x13ec468;
    } else {
        EaStr16 name, desc;
        cString_s00f0_5110 cfg1(0x19f76d11, 0x5ca8d97, 0);
        cString_s00f0_5110 cfg2(0x19f76d11, 0x5ca8d98, 0);
        name.Format((const char*)0x13ff0cc, cfg1.GetText(), cfg2.GetText());
        at<void*>(*(void**)0x15f7cf4, 0x1c) = name.mpBegin;
        cString_s00f0_5110 cfg3(0x19f76d11, 0x61b68c1, 0);
        desc.Format((const char*)0x13fe12c, cfg3.GetText());
        at<void*>(*(void**)0x15f7cf4, 0x58) = desc.mpBegin;
    }

    void* hints = UIHints_Get();
    ((UIHints*)hints)->SetFlag(0, 1);

    cString_s00f0_5110 caption(0x7518573e, 0x54c1e63, (const void*)0x13febb4);
    Layout* lay = (Layout*)at<void*>(this, 0x2c);
    void* win1 = lay->FindWindowByID(0x5b5f5c8, 1);
    ((void (__thiscall*)(void*, const void*))((void**)*(void**)win1)[0x80 / 4])(win1, caption.GetText());

    float h = 0.0f;
    void* win2 = lay->FindWindowByID(0x5b5ef51, 1);
    if (win2 != 0) {
        AutoSizeWindowForText(win2, 1, 0);
        void* win3 = lay->FindWindowByID(0x5b5ef52, 1);
        if (win3 != 0) {
            AutoSizeWindowForText(win3, 0, 0);
            RectF* r3 = ((RectF* (__thiscall*)(void*))((void**)*(void**)win3)[0x38 / 4])(win3);
            float w = r3->right - r3->left;
            RectF* r2 = ((RectF* (__thiscall*)(void*))((void**)*(void**)win2)[0x38 / 4])(win2);
            ((void (__thiscall*)(void*, float, float))
             ((void**)*(void**)win3)[0x70 / 4])(win3, r2->left - w, r3->top);
            void* win4 = lay->FindWindowByID(0x5b5ef53, 1);
            if (win4 != 0) {
                AutoSizeWindowForText(win4, 0, 0);
                RectF* r4 = ((RectF* (__thiscall*)(void*))((void**)*(void**)win4)[0x38 / 4])(win4);
                RectF* r3b = ((RectF* (__thiscall*)(void*))((void**)*(void**)win3)[0x38 / 4])(win3);
                RectF res;
                res.Intersect(*r4, *r3b);
                h = res.right - res.left;
            }
        }
    }

    this->LayoutYouTube();

    void* panel = lay->FindWindowByID(0x5b5ef50, 1);
    ((void (__thiscall*)(void*, int, int))((void**)*(void**)panel)[0x7c / 4])(panel, 1, 1);
    if (h > 0.0f) {
        RectF* rp = ((RectF* (__thiscall*)(void*))((void**)*(void**)panel)[0x38 / 4])(panel);
        ((void (__thiscall*)(void*, float, float))((void**)*(void**)panel)[0x74 / 4])(
            panel, (rp->right - rp->left) + h, rp->bottom - rp->top);
    }

    void* dialog = lay->FindWindowByID(0xffffffff, 1);
    void* wm = WindowManager();
    if (!((uchar (__thiscall*)(void*, void*))((void**)*(void**)wm)[0x80 / 4])(wm, dialog)) {
        SPUIHelpers_BeginModal(dialog, 0, 0);
        void* gt = GameTimeManager();
        ((SpGameTime*)gt)->IncPauseGate(0x4bf38a4);
    }
    at<int>(this, 0x28) = 1;
}

// @ 0x00f05b00
void Movie::CloseUpload()
{
    void* sys = Audio_GetSystemAT();
    int   vol = sys != 0
              ? ((int (__thiscall*)(void*))((void**)*(void**)sys)[0x20 / 4])(sys)
              : 0;

    sys = Audio_GetSystemAT();
    if (sys != 0) {
        ((void (__thiscall*)(void*, int))((void**)*(void**)sys)[0x38 / 4])(sys, 0x3475365);
        ((void (__thiscall*)(void*, int, int))((void**)*(void**)sys)[0x40 / 4])(sys, 0x3475381, 0xcb4ad069);
        ((void (__thiscall*)(void*, int, int))((void**)*(void**)sys)[0x40 / 4])(sys, 0x3475385, vol);
        ((void (__thiscall*)(void*))((void**)*(void**)sys)[0x58 / 4])(sys);
    }

    ScenarioTutorials_CloseWindow();
    void* trig = GetTriggerMgr();
    int   mode = at<int>(trig, 0x2c);
    if (mode != 1 && mode != 2)
        this->RefreshPanel();

    at<uchar>(this, 0x78) = 0;
    void* btn1 = at<void*>(this, 0x30);
    ((void (__thiscall*)(void*, int, int))((void**)*(void**)btn1)[0x7c / 4])(btn1, 1, 0);
    void* btn2 = at<void*>(this, 0x34);
    ((void (__thiscall*)(void*, int, int))((void**)*(void**)btn2)[0x7c / 4])(btn2, 1, 1);

    UpdateMouseFocus(1);
    void* area = SP_GetSaveArea(0x11ac197);
    int   panel = area != 0
                ? ((int (__thiscall*)(void*, int))
                   ((void**)*(void**)((char*)area + 4))[0xc / 4])((char*)area + 4, 0x226a1de)
                : 0;

    EaStr16 name;
    name.Format((const char*)0x13ff3dc, at<int>(this, 0x54));
    ((void (__thiscall*)(void*, char*, int, int))
     ((void**)*(void**)panel)[0x54 / 4])((void*)panel, name.mpBegin, 0, 2);
}

// @ 0x00f05c40
void Movie::SendPublicAuth()
{
    YtAuthMsg msg;

    at<uchar>(this, 0xbe) = 1;
    at<uchar>(this, 0xbd) = 0;
    at<uchar>(this, 0xbc) = 0;
    msg.mToken.sprintf((const char*)0x13f5b98, at<int>(this, 0x8c));
    msg.mUser.sprintf((const char*)0x13f5b98, at<int>(this, 0x9c));
    msg.mExtra.sprintf((const char*)0x13f5b98, (const char*)0x13ff0d8);
    msg.mPrivate = 1;
    void* srv = MessageServer();
    ((void (__thiscall*)(void*, int, YtAuthMsg*, int))
     ((void**)*(void**)srv)[0x14 / 4])(srv, 0x55be439, &msg, 0);
}

// @ 0x00f05d00
void SP::cSPPlayModeSubModeMovie::LoginToYouTube()
{
    YtAuthMsg msg;

    at<uchar>(this, 0xc1) = 1;
    at<uchar>(this, 0xc0) = 0;
    at<uchar>(this, 0xbf) = 0;
    msg.mToken.sprintf((const char*)0x13f5b98, at<int>(this, 0x8c));
    msg.mUser.sprintf((const char*)0x13f5b98, at<int>(this, 0x9c));
    msg.mExtra.sprintf((const char*)0x13f5b98, (const char*)0x13ff0d8);
    msg.mPrivate = 0;
    void* srv = MessageServer();
    ((void (__thiscall*)(void*, int, YtAuthMsg*, int))
     ((void**)*(void**)srv)[0x14 / 4])(srv, 0x55be439, &msg, 0);
}

// @ 0x00f05dc0
void __stdcall BuildYtFeed(EaStr* out)
{
    char priv = 0;

    if (gAppProperties_s00f0_5110 != 0) {
        void* pl = gAppProperties_s00f0_5110;
        int prop;
        if (((uchar (__thiscall*)(void*, int, int*))
             ((void**)*(void**)pl)[0x24 / 4])(pl, 0x8608be4, &prop) &&
            at<ushort>(prop, 0x12) == 1)
            priv = *((Prop*)prop)->GetBool();
    }
    if (out->mpBegin != out->mpEnd) {
        *out->mpBegin = 0;
        out->mpEnd = out->mpBegin;
    }
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff2f0);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff2c4);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff294);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff260);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff250);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x148b964);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x148b900);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff140);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x148b8bc);
    if (!priv)
        out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff0fc);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff0e8);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff0dc);
}

// @ 0x00f063c0
void MovieHandler::HandleMessage(u32 unused, u32 msgId)
{
    SP::cSPPlayModeSubModeMovie_s00f0_5ee0* o = static_cast<SP::cSPPlayModeSubModeMovie_s00f0_5ee0*>(this);
    switch (o->mDialog) {
    case 1:
        if (msgId == 0x5107b17) {
            o->FUN_00f03de0();
            OpenBrowser_s00f0_5ee0(L"http://youtube.com/t/terms", 1);
            return;
        }
        if (msgId == 0x5107b19)
            goto L_5107b19;
        if (msgId == 0x5107b1a) {
            void* am = FUN_00607a60();
            if (!((FnC0) VT(am, 0x58))(am)) {
                o->mDialog = 8;
                FUN_00809db0(this, 0x15ad498);
                return;
            }
            am = FUN_00607a60();
            if (((FnC0) VT(am, 0x24))(am)) {
                o->mDialog = 7;
                FUN_00809db0(this, 0x15ad48c);
                return;
            }
            if (!GetYTPrompt()) {
                FUN_0063bc70();
                o->FUN_00f05c40();
                return;
            }
            goto L_5107b1a;
        }
        break;
    case 2:
        if (msgId == 0x5107b19) goto L_5107b19;
        if (msgId == 0x5107b1a) goto L_5107b1a;
        break;
    case 3:
        o->mDialog = 0;
        return;
    case 4:
    case 6:
    L_5107b19:
        o->FUN_00f044d0();
        return;
    case 5:
        if (msgId == 0x5107b19) goto L_5107b19;
        if (msgId == 0x5107b1a) {
            o->FUN_00f041a0();
            return;
        }
        break;
    case 7:
    case 8:
        if (msgId == 0x5107b19) goto L_5107b19;
        if (msgId == 0x5107b1a) {
            void* am = FUN_00607a60();
            ((FnU0) VT(am, 0x44))(am);
            return;
        }
        break;
    case 10:
    case 0xb:
        if (msgId == (u32) -0xf) goto L_5107b19;
        break;
    case 0xc:
        if (msgId == 0x5107b19) {
        L_5107b1a:
            o->FUN_00f03e90();
            return;
        }
        if (msgId == 0x5107b1a) {
            o->FUN_00f03e90();
            OpenBrowser_s00f0_5ee0(L"http://www.youtube.com/signup", 1);
            return;
        }
        break;
    case 0xd:
        if (msgId == 0x5107b19) {
            o->FUN_00f05790();
            return;
        }
        if (msgId == 0x5107b1a) {
            o->FUN_00f05790();
            OpenBrowser_s00f0_5ee0(L"http://youtube.com/t/terms", 1);
            return;
        }
        break;
    case 0xe:
        if (msgId == (u32) -0xf)
            o->FUN_00f03fc0(1);
        break;
    }
}

// @ 0x00f06d40
bool Movie_s00f0_6d40::F_00f06d40(int msgId, Msg* msg)
{
    (void)msgId;
    switch (msg->m08) {
    case 0x287259f6:
        switch (msg->m0c) {
        case 0x56be960:                                 // ShowSendVideoURLDialog
            F_00f06660();
            return true;
        case 0x5665f58: {                               // toggle a config value
            void* cm = F_0067dd30();
            bool on = ((int (__thiscall*)(void*, int))((*(void***)cm)[0x30 / 4]))(cm, 0x5664a8b) != 0;
            void* cm2 = F_0067dd30();
            ((void (__thiscall*)(void*, int, int))((*(void***)cm2)[0x2c / 4]))(cm2, 0x5664a8b, on ? 0 : 1);
            return true;
        }
        case 0x5652348:                                 // ShowUploadProgressDialog
            F_00f065d0();
            return true;
        case 0x5adbea8:
            F_00f03fc0(0);
            F_00f044d0();
            return true;
        case 0x5b5ef51: {                               // begin the YouTube auth flow
            F_00435ed0(0xe76c9b4f, F_00435e90());
            F_00f03e20();
            void* auth = F_00607a60();
            if (!((unsigned char (__thiscall*)(void*))((*(void***)auth)[0x58 / 4]))(auth)) {
                m28 = 8;                                // YouTube login check
                F_00809db0(m04, (const wchar_t*)0x15ad498);
                return true;
            }
            if (((unsigned char (__thiscall*)(void*))((*(void***)auth)[0x24 / 4]))(auth)) {
                m28 = 7;                                // YouTube register check
                F_00809db0(m04, (const wchar_t*)0x15ad48c);
                return true;
            }
            if (F_0063b890()) {
                F_00f03e90();
                return true;
            }
            F_0063bc70();
            F_00f05c40();
            return true;
        }
        case 0x5b5bd80:
            F_00f03fa0();
            m28 = 0;
            F_00f05790();
            return true;
        case 0x5b5ef52: {                               // reset the auth UI
            void* at = F_00a206f0();
            unsigned int v = 0;
            if (at)
                v = ((unsigned int (__thiscall*)(void*))((*(void***)at)[0x20 / 4]))(at);
            F_00435ed0(0xe76c9b4f, v);
            void* win = m2c->F_008105b0(0x5b5ef50, 1);
            ((void (__thiscall*)(void*, int, int))((*(void***)win)[0x7c / 4]))(win, 1, 0);
            F_00f044d0();
            return true;
        }
        case 0x5baefc8:                                 // open the signup page
            if (!F_0063c0a0()) {
                F_00f03fa0();
                m28 = 0xc;                              // English signup warning
                F_00809db0(m04, (const wchar_t*)0x15ad4bc);
                return true;
            }
            F_00935fb0((const wchar_t*)0x13ff35c, true);
            return true;
        case 0x5b5ef53:                                 // open the terms page
            F_00435ed0(0xe76c9b4f, F_00435e90());
            if (F_0063c0a0()) {
                F_00935fb0((const wchar_t*)0x13ff398, true);
                return true;
            }
            F_00f03e20();
            m28 = 0xd;                                  // English TOS warning
            F_00809db0(m04, (const wchar_t*)0x15ad4bc);
            return true;
        case 0x78d57d0:
        case 0x78ec978: {
            // ---- media capture / YouTube metadata ---------------------------
            void* msys = F_0067cb10();
            if (((unsigned char (__thiscall*)(void*))((*(void***)msys)[0x30 / 4]))(msys)) {
                ((void (__thiscall*)(void*))((*(void***)msys)[0x38 / 4]))(msys);
                return true;
            }

            WStr s1, s2, s3, s4, s5;
            DateTime_s00f0_6d40 dt;
            CStringStub cs;

            s1.mBegin = s1.mEnd = g_01667bac; s1.mCap = g_01667bac + 1;
            s2.mBegin = s2.mEnd = g_01667bac; s2.mCap = g_01667bac + 1;
            s3.mBegin = s3.mEnd = g_01667bac; s3.mCap = g_01667bac + 1;
            s4.mBegin = s4.mEnd = g_01667bac; s4.mCap = g_01667bac + 1;
            s5.mBegin = s5.mEnd = g_01667bac; s5.mCap = g_01667bac + 1;

            F_0041e050(&s1, (const wchar_t*)0x13f5c04, (const wchar_t*)0x13ff420);
            g_015f7cf4->m54 = s1.mBegin;

            dt.Set(2);
            F_0041e050(&s5, (const wchar_t*)0x13f5bf8, dt.GetParameter(1));
            g_015f7cf4->m44 = s5.mBegin;
            F_0041e050(&s4, (const wchar_t*)0x13f5bec, dt.GetParameter(2));
            g_015f7cf4->m48 = s4.mBegin;
            F_0041e050(&s3, (const wchar_t*)0x13f5bec, dt.GetParameter(6));
            g_015f7cf4->m4c = s3.mBegin;
            F_0041e050(&s2, (const wchar_t*)0x13f5bcc,
                       dt.GetParameter(0xa), dt.GetParameter(9), dt.GetParameter(8));
            g_015f7cf4->m50 = s2.mBegin;

            cs.Ctor(0x7518573e, 0x5dbc9ee, 0);
            m54.append(cs.GetText());
            void* area = F_006b1f90(0x11ac197);
            const wchar_t* name =
                (const wchar_t*)((unsigned int (__thiscall*)(void*))((*(void***)area)[0x28 / 4]))(area);
            m64.append(name);

            F_004af210(g_015fd918, 0x456f975, &m3c);
            F_004af210(g_015fd918, 0x456f976, &m40);
            ((void (__thiscall*)(void*, const wchar_t*, uint32_t*))((*(void***)msys)[0x2c / 4]))
                (msys, m54.mBegin, &m3c);

            m78 = true;
            m79 = false;
            F_00f03e40();
            m74 = 0;
            cs.Dtor();
            s1.DeallocateSelf();
            s2.DeallocateSelf();
            s3.DeallocateSelf();
            s4.DeallocateSelf();
            s5.DeallocateSelf();
            return true;
        }
        case 0x78d57d8:
            F_00f069a0(0);                              // BeginRecording
            return true;
        default:
            break;
        }
        return false;
    case 1:
        if (msg->m10.i == 0xd && m28 == 3) {
            F_00f065d0();
            return true;
        }
        break;
    default:
        break;
    }
    return false;
}

// @ 0x00f072b0
bool PhotoHandler::F_00f072b0(int msgId, Msg* msg)
{
    TempRef tmp;

    switch (msgId) {
    case 0x7c651b1: {
        void* gtm = F_00b3d380();
        ((GameTime*)gtm)->F_00b32250(0x4bf38a7);

        void* q = m_c4;
        if (q) {
            ((void (__thiscall*)(void*, int))((*(void***)q)[0x0c / 4]))(q, 0);
            q = m_c4;
            if (q) {
                m_c4 = 0;
                ((void (__thiscall*)(void*))((*(void***)q)[0x04 / 4]))(q);
            }
        }

        if (!m_f1) {
            void* em = F_0067ddd0();
            unsigned char (__thiscall* play)(void*, int, int, void*) =
                (unsigned char (__thiscall*)(void*, int, int, void*))((*(void***)em)[0x2c / 4]);
            void* param = ((AutoRef_s00f0_6d40*)&m_c4)->F_00a16f40();
            unsigned char ok = play(em, 0x44ed103, 0, param);
            if (ok) {
                void* r = m_c4;
                ((void (__thiscall*)(void*, int))((*(void***)r)[0x08 / 4]))(r, 0);
            }
        }

        if (m_f1) {
            void* wm = F_0067caa0();
            void* w = ((void* (__thiscall*)(void*))((*(void***)wm)[0x04 / 4]))(wm);
            if (w)
                ((MainWin*)((char*)w - 4))->F_008143a0();
            else
                ((MainWin*)0)->F_008143a0();
        } else {
            m_f8.F_0093a480(0x1f4, true);
        }
        return false;
    }
    case 0x7c651b0: {
        void* p = F_00f04530(1);
        tmp.mPtr = p;
        if (p)
            _InterlockedIncrement((volatile long*)((char*)p + 8));
        m_dc.F_00420660(&tmp.mPtr);
        tmp.F_00576620();
        return false;
    }
    case 0x7d62123:
        m_f0 = false;
        ((Movie_s00f0_6d40*)((char*)this - 8))->F_00f04070(1);
        return false;
    case 0x7e1e46d: {
        Movie_s00f0_6d40* movie = (Movie_s00f0_6d40*)((char*)this - 8);
        movie->F_00f06ac0();                            // ClearIndicatorTextures
        movie->F_00f04070(1);
        return false;
    }
    }

    if (m24 == 0)
        return false;

    switch (msgId) {
    case 0x55e5212: {
        int a = msg->m10.i;
        int b = msg->m08;
        if (a)
            m_b5 = true;
        else
            m_b8 = true;
        if (b) {
            if (a) {
                m_b4 = true;
                return false;
            }
            F_00472fe0(&m74, (const char*)0x13f5b98, ((SubMsg*)msg->m18)->m0c);
            F_00472fe0(&m84, (const char*)0x13f5b98, ((SubMsg*)msg->m20)->m0c);
            m_b7 = true;
            return false;
        }
        m_b4 = false;
        m_b7 = false;
        m_c0 = (uint32_t)msg->m18;
        return false;
    }
    case 0x44db12e: {
        if (msg == 0)
            return false;
        int st = m20;
        if (st != 7 && st != 8)
            return false;
        if (m_bd) {
            m_be = true;
            return false;
        }
        if (F_0063b890()) {
            ((Movie_s00f0_6d40*)((char*)this - 8))->F_00f03e90();
            return false;
        }
        F_0063bc70();
        ((Movie_s00f0_6d40*)((char*)this - 8))->F_00f05c40();
        return false;
    }
    case 0x55e8be4: {
        if (msg->m08)
            m_ba = true;
        if (!m_ba) {
            m_c0 = (uint32_t)msg->m10.p;
            m_bc = true;
            return false;
        }
        WStr url;
        url.mBegin = url.mEnd = g_01667bac; url.mCap = g_01667bac + 1;
        F_0041e050(&url, (const wchar_t*)0x13f5c04,
                   (const wchar_t*)((SubMsg*)msg->m10.p)->m0c);
        if (!F_0063d170(&url, &m_a4))
            m_a4.F_0057cb60(url);
        g_015f7cf4->m30 = m_a4.mBegin;
        url.DeallocateSelf();
        m_bc = true;
        return false;
    }
    case 0x5b98f52: {
        int st = m20;
        if (st != 7 && st != 8)
            return false;
        ((Movie_s00f0_6d40*)((char*)this - 8))->F_00f05790();
        return false;
    }
    case 0x5b96086: {
        void* auth = F_00607a60();
        if (!((unsigned char (__thiscall*)(void*))((*(void***)auth)[0x58 / 4]))(auth))
            return false;
        ((Movie_s00f0_6d40*)((char*)this - 8))->F_00f044d0();
        return false;
    }
    case 0x5bd6378:
        m_bd = true;
        return false;
    case 0x5dd52c7:
        m_bd = false;
        if (!m_be)
            return false;
        m_be = false;
        if (F_0063b890()) {
            ((Movie_s00f0_6d40*)((char*)this - 8))->F_00f03e90();
            return false;
        }
        F_0063bc70();
        ((Movie_s00f0_6d40*)((char*)this - 8))->F_00f05c40();
        return false;
    case 0x5d2c5c0: {
        F_0063c060(false);
        void* ctx = (void*)((char*)this - 4);
        F_00809db0(ctx, (const wchar_t*)0x15ad4b0);
        m20 = 0xb;
        tmp.mPtr = (void*)0x55e7aed;
        void* ms = F_0067dcc0();
        ((void (__thiscall*)(void*, int, void**, int))((*(void***)ms)[0x14 / 4]))
            (ms, 0x5d313c7, &tmp.mPtr, 0);
        return true;
    }
    case 0x62ff413:
        ((Movie_s00f0_6d40*)((char*)this - 8))->F_00f04bd0();
        return false;
    case 0x62ff414:
    case 0x62ff415:
        ((Movie_s00f0_6d40*)((char*)this - 8))->F_00f05b00();
        return false;
    default:
        break;
    }
    return false;
}
