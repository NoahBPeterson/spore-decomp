// src/game/SPEditors/SPSubModePhoto.cpp -- migrated from slice(s) s006404f0, s0063f740, s0063e880, s0063d9e0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPSubModePhoto.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPlayModeSubModePhoto.h"
#include "EA/DateTime/DateTime.h"
#include "SP/cIMovieSystem.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cSPEditorNaming.h"
#include "SP/cSPEditorUI.h"
#include "SP/cSPPlayModeSubModeMovie.h"
#include "SP/cSPPlayModeUI.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include <stdio.h>
#include "EA/Stopwatch.h"
#include "SP/cSPPlayModePhotoBrowser.h"
#include "cSPVector4.h"
#include <string.h>
#include <stdlib.h>
#include "SP/cSPPlayMode.h"
#include "SP/cSPPlayModeAnimation.h"
#include "SP/cSPPlayModeSubModeBase.h"

// ---- items of slice s0063d9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
// ---- items of slice s0063d9e0 end

// ---- items of slice s0063e880 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);
extern "C" unsigned __int64 __rdtsc();
extern char gMsgA[];   // 0x01524C60
extern char gMsgB[], gMsgC[], gMsgD[];   // 0x01524C24, 0x01524C30, 0x01524C3C
extern uint32_t gPhotoGlobal;          // 0x01524A10
extern const wchar_t gFmtW[];          // 0x013F5C04
extern "C" long _InterlockedExchangeAdd(long volatile*, long);
#pragma intrinsic(__rdtsc)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
void* operator new(size_t size, int align, const char* name, void* alloc);   // 0x009512D0
void* operator new(size_t size, const char* name, int a, int b, int c, int d);   // 0x00F473A0 (EASTL allocator_allocate)
void operator delete(void* p);                                                  // 0x00F47380
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
struct allocator_s0063_e880 {
    void deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
template <typename T, typename Allocator = allocator_s0063_e880>
class basic_string_s0063_e880 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    basic_string_s0063_e880() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    ~basic_string_s0063_e880() { DeallocateSelf(); }
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
typedef basic_string_s0063_e880<char> string;
}
namespace eastl {
typedef basic_string_s0063_e880<wchar_t> string16_s0063_e880;
}
struct IRefCounted { virtual int AddRef(); virtual int Release(); virtual void s2(); virtual void Stop(int a); };
struct IRangeTarget { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
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
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
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
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
virtual void s51();
virtual void s52();
virtual void s53();
virtual void s54();
virtual void s55();
virtual void s56();
virtual void s57();
virtual void s58();
virtual void s59();
virtual void s60();
virtual void s61();
virtual void s62();
virtual void s63();
virtual void s64();
virtual void s65();
virtual void s66();
virtual void s67();
virtual void s68();
virtual void s69();
virtual void s70();
    virtual void SetRange(const uint64_t* a, const uint64_t* b, int mode);   // +0x11C
};
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
struct IWindow {   // UTFWin window (slots used by this module)
    virtual int AddRef();
    virtual int Release();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
    virtual uint32_t GetControlID();   // +0x1C
virtual void s08();
virtual void s09();
virtual uint32_t GetFlags();
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
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
    virtual void SetFlag(int flag, int on);                    // +0x7C
    virtual void SetCaption(const wchar_t* text);              // +0x80
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
virtual void s51();
virtual void s52();
virtual void s53();
virtual void s54();
virtual void s55();
virtual void s56();
virtual void s57();
virtual void s58();
virtual void s59();
    virtual IWindow* FindWindowByID(uint32_t id, bool recurse);   // +0xF0
virtual void s61();
virtual void s62();
virtual void s63();
virtual void s64();
virtual void s65();
    virtual void RemoveWinProc(void* proc);                       // +0x108
};
void  EndModal(IWindow* w, int a, int b);           // 0x00809C50 (cdecl)
struct Stopwatch {
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfCoeff;
    Stopwatch(int units, bool start);                 // 0x0093A560 (out of line)
    uint64_t GetElapsedTime() const;                  // 0x0093A3A0
    float GetElapsedTimeFloat() const { return (float)(int64_t)GetElapsedTime() * mfCoeff; }
    void Stop();                                      // 0x0093A2E0
    void Restart();                                   // 0x00571E80
    void Reset() { mnStartTime = 0; mnTotalElapsedTime = 0; }
    void Start()
    {
        if (!mnStartTime) {
            if (mnUnits == 1)
                mnStartTime = __rdtsc();
            else {
                int64_t t;
                QueryPerformanceCounter(&t);
                mnStartTime = t;
            }
        }
    }
};
struct cProfScope { void End(); };                       // 0x0067C420
cProfScope* __stdcall BeginProfScope(int a, int b);      // 0x0067CAC0
struct cString {   // 0x14 bytes (retail)
    uint32_t pad[5];
    cString();                                                       // 0x006B5060
    ~cString();                                                      // 0x006B5240
};
struct cSPPlayModeUI {   // retail layout (partial)
    uint32_t pad0[0x44 / 4];
    bool mbLayoutInit;                              // +0x44
    void FUN_00635350(int a, int b);                // 0x00635350
    IWindow* FindEditorUIWindow(uint32_t id);       // 0x00634E40
    bool GetItemVisible(uint32_t id);               // 0x00634E60
    bool IsCheckButtonSelected(uint32_t id);        // 0x00635850
    void SetSelected(uint32_t id, bool b);          // 0x00634EC0
    bool IsUIGroupEnabled(uint32_t id);             // 0x00635890
    void SetUIGroupVisible(uint32_t id, bool on);   // 0x00635760
    void SetEditorUIGroupVisible(uint32_t id, bool on);   // 0x00635790
    void SetEnableTakePictureButton(bool b);        // 0x00635600
    void SetEnableRecordMovieButton(bool b);        // 0x00635680
    void SetEnableNewCreatureButton(bool b);        // 0x00635580
    const wchar_t* GetPhotoName(wchar_t* buf, int n);   // 0x00634E50 (original: caller cleans the 2 args)
};
struct IMovieSystemObj { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
    virtual void s11(); virtual bool IsRecording(); };    // +0x30
IMovieSystemObj* GetMovieSystem();                         // 0x0067CB10
void ShowMessageBoxEx(const void* a, const void* b);       // 0x00809DB0 (cdecl)
struct cAutoHandler_s0063_e880 {
    uint32_t a, b, c, d, e;
    cAutoHandler_s0063_e880() : a(0), b(0), c(0), d(0), e(0) {}
    ~cAutoHandler_s0063_e880()
    {
        if (a) {
            uint32_t ta = a, tb = b, tc = c, td = d, te = e;
            a = 0;
            RemoveHandler(ta, tb, tc, td, te);
        }
    }
};
struct cSPPlayModeSubModeBase { virtual ~cSPPlayModeSubModeBase() {} virtual void b1(); uint32_t pad[4];
    void Init(void* arg);   // 0x0063B270
};
struct IHandler { virtual ~IHandler() {} virtual int h1(); };
struct cSPPlayModePhotoBrowser {   // 0xEC0 bytes
    uint32_t pad[0xec0 / 4];
    cSPPlayModePhotoBrowser();            // 0x00630A50
    ~cSPPlayModePhotoBrowser();           // 0x00630930
    void Init(cSPPlayModeUI* ui);         // 0x006339E0
    void Shutdown();                      // 0x00632F30
    void ShowImageThumbnail();            // 0x00633CC0
    void UpdatePhotoCountText();          // 0x00630D10
    void FUN_00630580(uint32_t dt);          // 0x00630580
    bool FUN_006304e0();                  // 0x006304E0
    void FUN_006303a0();                  // 0x006303A0
    void FUN_00631df0(void* p);           // 0x00631DF0
};
struct cPhotoMsg;
struct cPhotoAssetManager;
void* GetPhotoAssets();   // 0x0067DD60
struct cSPPlayModeSubModePhoto_s0063_e880 : cSPPlayModeSubModeBase, IHandler {
    uint32_t mPoseAnimIDs[6];                 // +0x18
    uint32_t mCurrPoseNum;                    // +0x30
    uint32_t mBabyEventIDs[6];                // +0x34
    cSPPlayModeUI* mUI;                       // +0x4C
    cSPPlayModePhotoBrowser mPhotoBrowser;    // +0x50
    Stopwatch mTimerA;                        // +0xF10
    uint32_t mCurrentPhotoID;                 // +0xF28
    AutoRef<IRefCounted> mFlashEffect;        // +0xF2C
    bool mbFlashA;                            // +0xF30
    bool mbFlashB;                            // +0xF31
    uint32_t pad0f34;
    Stopwatch mTimerB;                        // +0xF38
    uint32_t mUnusedF50;                      // +0xF50
    uint32_t mWriteJobCount;                  // +0xF54
    bool mbFlashC;                            // +0xF58
    uint32_t pad0f5c;
    Stopwatch mTimerC;                        // +0xF60
    bool mbFlashD;                            // +0xF78
    uint32_t pad0f7c;
    Stopwatch mTimerD;                        // +0xF80
    int mDialogInProgress;                    // +0xF98
    bool mb0f9c, mb0f9d;
    cAutoHandler_s0063_e880 mAutoMsgHandler;             // +0xFA0
    eastl::string16_s0063_e880 mString;                  // +0xFB4

    cSPPlayModeSubModePhoto_s0063_e880();
    virtual ~cSPPlayModeSubModePhoto_s0063_e880();
    void FUN_0063f060();  // 0x0063f060 (cSPPlayModeSubModePhoto::FUN_0063f060)
    void SavePhoto(uint16_t a);  // 0x0063f420 (cSPPlayModeSubModePhoto::SavePhoto)
    void SavePhotoSimple();
    void Update(uint32_t dt);  // 0x0063e880 (cSPPlayModeSubModePhoto::Update)
    void ShowErrorDialog(uint32_t id, int unused);  // 0x0063eb30 (cSPPlayModeSubModePhoto::ShowErrorDialog)
    bool IsPhotosWriting(bool arg);  // 0x0063eb90 (cSPPlayModeSubModePhoto::IsPhotosWriting)
    void CloseSendPhotoWindow();  // 0x0063ec10 (cSPPlayModeSubModePhoto::CloseSendPhotoWindow)
    bool IsFlashAIdle();
    static void DefaultPathA();
    static void DefaultPathB();
    void Init(void* arg);  // 0x0063ee30 (cSPPlayModeSubModePhoto::Init)
    void Shutdown();  // 0x0063eef0 (cSPPlayModeSubModePhoto::Shutdown)
    bool HandleKey(uint32_t id, int unused);  // 0x0063ef30 (cSPPlayModeSubModePhoto::HandleKey)
    void StartCameraFlash();  // 0x0063ef70 (cSPPlayModeSubModePhoto::StartCameraFlash)
};
struct IAudioSystemAT {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual int GetValue();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
    virtual void SetMode(uint32_t id);                                                   // +0x38
    virtual void s15();
    virtual void SetParam(uint32_t id, int v);                                           // +0x40
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
    virtual void Commit();                                                               // +0x58
};
IAudioSystemAT* GetSystemAT();   // 0x00A206F0
namespace eastl {
template <typename ForwardIterator, typename T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
{
    for (; first != last; ++first) {
        if (*first == old_value)
            *first = new_value;
    }
}
}
namespace eastl {
template void replace<wchar_t*, wchar_t>(wchar_t*, wchar_t*, const wchar_t&, const wchar_t&);   // 0x0063eda0
}
IRefCounted* __stdcall FUN_00401050(uint32_t id, int a);   // 0x00401050
struct cEffectFactory { IRefCounted* Create(); };          // 0x0045AE10
struct cFourStrings {
    uint32_t pad[3];
    eastl::string s0, s1, s2, s3;
    ~cFourStrings();
};
struct cMsgBaseA { virtual ~cMsgBaseA() {} virtual int AddRef(); virtual int Release(); int mRefCount; cMsgBaseA() : mRefCount(0) {} };
struct cPhotoMsg : cMsgBaseA {
    uint32_t mId;            // +8
    uint32_t mWidth;         // +0xC
    uint32_t mType;          // +0x10
    uint32_t mField14;       // +0x14
    uint32_t mPhotoID;       // +0x18
    uint32_t mKey1;          // +0x1C
    uint32_t mGlobal;        // +0x20
    uint32_t mPhotoID2;      // +0x24
    eastl::string16_s0063_e880 mName;   // +0x28
    cPhotoMsg() {}
};
struct cIDGenerator {
    virtual void s0();
    virtual void Generate(uint32_t* out, uint32_t type, int a, int b, int c, int d);   // +4
};
cIDGenerator* GetIDGenerator();     // 0x0067DE60
struct cMsgDispatcher {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
    virtual void Dispatch(uint32_t a, uint32_t b, uint32_t c, cPhotoMsg* msg);   // +0x24
};
cMsgDispatcher* GetMsgDispatcher();   // 0x0067DDB0
int WStr_Format(eastl::string16_s0063_e880* dst, const wchar_t* fmt, ...);   // 0x0041E050 (cdecl)
void MakeFileNameValid(const wchar_t* p);                          // 0x00931250 (cdecl)
struct cPhotoOwner { char pad[0x8c]; uint32_t f8c; char pad2[0x360 - 0x90]; struct { char pad[0x38]; uint32_t f38; }* p360; };
struct cPhotoCheck { bool FUN_00628940(); };   // 0x00628940
struct cSimpleMsg : cMsgBaseA {
    uint32_t mGlobal;        // +8
    uint32_t mPhotoID;       // +0xC
    uint32_t mField10, mField14, mField18;
    uint32_t mPhotoID2;      // +0x1C
    eastl::string16_s0063_e880 mName;   // +0x20
    uint32_t mField30, mField34;
    bool mb38, mb39;
    cSimpleMsg() : mField10(0), mField14(0), mField18(0), mField30(0), mField34(0) {}
};
struct cRefCountedAsset { uint32_t pad[2]; volatile long mRefCount; };
struct cPhotoAssetManager {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
    virtual cRefCountedAsset* Lookup(uint32_t a, uint32_t b, uint32_t c);   // +0x20
virtual void s9();
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
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
    virtual void Register(cRefCountedAsset* a);   // +0x68
};
// ---- items of slice s0063e880 end

// ---- items of slice s0063f740 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gAppProperties2;                                // 0x015FD918
extern void gPartialCall();
struct cString_s0063_f740 {  // 0x006B5060 / 0x006B5240
    char pad[0x14];
    cString_s0063_f740();
    ~cString_s0063_f740();
};
void FUN_00809db0(void* a, void* b);                         // 0x00809DB0 (cdecl)
struct CAchievementController { void AutoTest(uint32_t a, int b); };   // 0x00676E90
CAchievementController* FUN_00675250();                      // 0x00675250
struct cSPPlayModeSubModePhoto_s0063_f740 {
    char pad0[0xf98];
    int  mDialogInProgress;        // +0xF98

    void WritePhotoWithComment();  // 0x0063f740 (cSPPlayModeSubModePhoto::WritePhotoWithComment)
    bool FUN_0063fa40();
    void SendPhoto();
    void FUN_0063fda0();
    void CloseSendPhotoWindow();   // 0x0063EC10 (external)
};
// ---- items of slice s0063f740 end

// ---- items of slice s006404f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_PhotoPropList;                                             // 0x015FD918
extern char g_CalloutConfig[];      // 0x01524C60
extern char g_CalloutTakeFull[];    // 0x01524BD0
extern char g_CalloutLogin[];       // 0x01524C54
extern char g_CalloutRegister[];    // 0x01524C48
extern char g_CalloutActions[];     // 0x01524BF4
extern char g_CalloutDeleteAll[];   // 0x01524BDC
extern char g_CalloutDelete[];      // 0x01524BE8
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
namespace SP {
class cString_s0064_04f0 {
public:
    cString_s0064_04f0();     // 0x006B5060
    ~cString_s0064_04f0();    // 0x006B5240
    uint32_t mData[5];
};
}
namespace SP {
struct cSPPlayMode_s0064_04f0 {
    void WakeupCreature();      // 0x0062A760
    void FUN_00628810();        // 0x00628810
};
}
namespace SP {
struct cSPPlayModeAnimation_s0064_04f0 {
    virtual void a0(); virtual void a1(); virtual void a2();
    virtual float PlayPose(void* shadowViewer, uint32_t animID, int a, int b, int c);   // +0x0C
};
}
namespace SP {
struct cAppModeEditorBasePhoto {
    char pad0[0x364];
    void* mShadowViewer;                                        // +0x364
    void FUN_00b267f0(int a, int pose);                         // 0x00B267F0
    void FUN_00574110(uint32_t id, int a, float b, float c);    // 0x00574110
};
}
namespace SP {
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
}
namespace SP {
struct cSPPlayModePhotoBrowser_s0064_04f0 {
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
}
namespace SP {
namespace Pollen {
struct cAuthManager_s0064_04f0 {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03(); virtual void m04();
    virtual void m05(); virtual void m06(); virtual void m07(); virtual void m08();
    virtual bool IsRegistrationNeeded();    // +0x24
    virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual void m14();
    virtual void m15(); virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21();
    virtual bool IsLoggedIn();              // +0x58
};
}
}
namespace SP {
namespace Pollen {
cAuthManager_s0064_04f0* AuthManager();                // 0x00607A60
}
}
namespace SP {
struct IMessageServer_s0064_04f0 {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void PostMSG(uint32_t id, int a, int b);    // +0x14
};
}
namespace SP {
IMessageServer_s0064_04f0* MessageServer();                        // 0x0067DCC0
}
namespace SP {
struct cSPPlayModeSubModeBase_s0064_04f0 {
    virtual void b00();
    cAppModeEditorBasePhoto* mEditorBaseMode;   // +0x04
    cSPPlayModeAnimation_s0064_04f0* mAnim;                // +0x08
    void* mSubModeParams;                       // +0x0C
    cSPPlayMode_s0064_04f0* mPlayMode;                     // +0x10
};
}
namespace SP {
struct IHandlerPhoto { virtual bool HandleMessage(uint32_t id, void* msg); };
}
namespace SP {
class cSPPlayModeSubModePhoto_s0064_04f0 : public cSPPlayModeSubModeBase_s0064_04f0, public IHandlerPhoto {
public:
    uint32_t mPoseAnimIDs[6];                   // +0x18
    uint32_t mCurrPoseNum;                      // +0x30
    uint32_t mBabyEventIDs[6];                  // +0x34
    cSPPlayModeUIPhoto* mUI;                    // +0x4C
    cSPPlayModePhotoBrowser_s0064_04f0 mPhotoBrowser;      // +0x50
    char padBrowser[0xF30 - 0x51];
    bool mbF30;                                 // +0xF30
    char padF31[0xF98 - 0xF31];
    int mDialogInProgress;                      // +0xF98

    bool HandleButton(int id);  // 0x006404f0 (SP::cSPPlayModeSubModePhoto::HandleButton)
    bool FUN_0063ed00();                        // 0x0063ED00
    bool FUN_0063ed50();                        // 0x0063ED50
    void CloseSendPhotoWindow();                // 0x0063EC10
    void FUN_0063f060();                        // 0x0063F060
    void SavePhoto(uint32_t a);                 // 0x0063F420
    void SendPhoto();                           // 0x0063FD20
};
}
namespace EA {
namespace Audio {
struct IAudioSystem {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7();
    virtual uint32_t GetState();    // +0x20
};
}
}
namespace EA {
namespace Audio {
IAudioSystem* GetSystemAT_s0064_04f0();        // 0x00A206F0
}
}
inline uint32_t GetRecorderState()
{
    EA::Audio::IAudioSystem* s = EA::Audio::GetSystemAT_s0064_04f0();
    return s ? s->GetState() : 0;
}
void PlayAudio(uint32_t soundID, uint32_t state);                         // 0x00435ED0 (cdecl)
bool TryGetUIntProperty(void* propList, uint32_t id, uint32_t* out);      // 0x00410370 (cdecl)
class cUIHints { public: void SetEnabled(bool on, bool b); };                    // 0x0067C420
cUIHints* UIHints();                                                      // 0x0067CAC0
namespace UI {
 void CalloutMessageBox(void* config, void* text);   // 0x00809DB0
}
// ---- items of slice s006404f0 end

// @ 0x0063e770
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

// @ 0x0063e810
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

// @ 0x0063e880
void cSPPlayModeSubModePhoto_s0063_e880::Update(uint32_t dt)
{
    if (mbFlashA) {
        Stopwatch* sw = &mTimerA;
        if (0.5f > sw->GetElapsedTimeFloat()) {
            if (!mUI->GetItemVisible(0x46530c8))
                mUI->SetUIGroupVisible(0x46530c8, true);
        } else {
            if (mUI->GetItemVisible(0x46530c8))
                mUI->SetUIGroupVisible(0x46530c8, false);
            if (sw->GetElapsedTimeFloat() > 1.0f)
                sw->Restart();
        }
    }
    if (mbFlashB) {
        Stopwatch* sw = &mTimerB;
        if (sw->GetElapsedTimeFloat() > 0.5f) {
            sw->Stop();
            sw->Reset();
            mbFlashB = false;
            if (mUI && mUI->mbLayoutInit) {
                mUI->SetEnableTakePictureButton(true);
                mUI->SetEnableRecordMovieButton(true);
                if (!GetMovieSystem()->IsRecording()) {
                    mUI->SetEnableNewCreatureButton(true);
                    mUI->FUN_00635350(1, 1);
                }
            }
            mUI->SetUIGroupVisible(0x410cf00, true);
            mUI->SetUIGroupVisible(0x41a30c0, true);
            mUI->SetEditorUIGroupVisible(0x447c040, true);
            mUI->SetEditorUIGroupVisible(0x447c4e8, true);
            if (mUI->IsUIGroupEnabled(0x445ea18))
                mUI->SetUIGroupVisible(0x4463e78, true);
            mUI->SetUIGroupVisible(0x46530c8, false);
            mbFlashA = false;
        }
    }
    if (mbFlashC) {
        Stopwatch* sw = &mTimerC;
        if (0.5f > sw->GetElapsedTimeFloat()) {
            if (!mUI->IsCheckButtonSelected(0x445ea50))
                mUI->SetSelected(0x445ea50, true);
        } else {
            if (mUI->IsCheckButtonSelected(0x445ea50))
                mUI->SetSelected(0x445ea50, false);
            if (sw->GetElapsedTimeFloat() > 1.0f)
                sw->Restart();
        }
    }
    if (mbFlashD) {
        Stopwatch* sw = &mTimerD;
        if (sw->GetElapsedTimeFloat() > 0.5f) {
            mbFlashD = false;
            sw->Stop();
            sw->Reset();
            mPhotoBrowser.ShowImageThumbnail();
        }
    }
    mPhotoBrowser.FUN_00630580(dt);
}

// @ 0x0063eb30
void SP::cSPPlayModeSubModePhoto::ShowErrorDialog(unsigned int id, wchar_t const * unused)
{
    switch (id) {
    case 0x4585f1f:
        BeginProfScope(0, 1)->End();
        ShowMessageBoxEx(gMsgA, gMsgB);
        mDialogInProgress = (SP::cSPPlayModeSubModePhoto::ePhotoDialogType)(8);
        break;
    case 0x4585f49:
        BeginProfScope(0, 1)->End();
        ShowMessageBoxEx(gMsgA, gMsgC);
        mDialogInProgress = (SP::cSPPlayModeSubModePhoto::ePhotoDialogType)(8);
        break;
    }
}

// @ 0x0063eb90
bool cSPPlayModeSubModePhoto_s0063_e880::IsPhotosWriting(bool arg)
{
    cString s;
    if (mPhotoBrowser.FUN_006304e0()) {
        BeginProfScope(0, 1)->End();
        ShowMessageBoxEx(gMsgA, gMsgD);
        mDialogInProgress = (arg == false) + 4;
        return true;
    }
    return false;
}

// @ 0x0063ec10
void cSPPlayModeSubModePhoto_s0063_e880::CloseSendPhotoWindow()
{
    IAudioSystemAT* at = GetSystemAT();
    int v = at ? at->GetValue() : 0;
    at = GetSystemAT();
    if (at) {
        at->SetMode(0x3475365);
        at->SetParam(0x3475381, 0x2dd795c);
        at->SetParam(0x3475385, v);
        at->Commit();
    }
    IWindow* w = mUI->FindEditorUIWindow(0x3f67620);
    if (w) {
        w->SetFlag(1, 0);
        EndModal(w, 0, 0);
        BeginProfScope(1, 1)->End();
    }
    mPhotoBrowser.FUN_006303a0();
    mDialogInProgress = 0;
}

// @ 0x0063ee30
void cSPPlayModeSubModePhoto_s0063_e880::Init(void* arg)
{
    cSPPlayModeSubModeBase::Init(arg);
    mFlashEffect = 0;
    cSPPlayModeUI* ui = *(cSPPlayModeUI**)((char*)arg + 0x1c);
    mUI = ui;
    mPoseAnimIDs[0] = 0x3fd1227;
    mPoseAnimIDs[1] = 0x3fd1214;
    mPoseAnimIDs[2] = 0x3fd11fb;
    mPoseAnimIDs[3] = 0x418b841;
    mPoseAnimIDs[4] = 0x3fd120a;
    mPoseAnimIDs[5] = 0x3fd1203;
    mBabyEventIDs[0] = 0x2949954d;
    mBabyEventIDs[1] = 0xd0c86c9a;
    mBabyEventIDs[2] = 0x89d6008b;
    mBabyEventIDs[3] = 0xc4b6e6e0;
    mBabyEventIDs[4] = 0xc1339ba9;
    mBabyEventIDs[5] = 0x7f034f46;
    mCurrPoseNum = 0;
    pad[1] = *(uint32_t*)((char*)arg + 0x20);
    mPhotoBrowser.Init(mUI);
    mUnusedF50 = 0;
    mWriteJobCount = 0;
    mbFlashA = false;
    mbFlashB = false;
}

// @ 0x0063eef0
void cSPPlayModeSubModePhoto_s0063_e880::Shutdown()
{
    mPhotoBrowser.Shutdown();
    IRefCounted* e = mFlashEffect.mpObject;
    if (e) {
        e->Stop(0);
        mFlashEffect = 0;
    }
}

// @ 0x0063ef30
bool cSPPlayModeSubModePhoto_s0063_e880::HandleKey(uint32_t id, int unused)
{
    if (id == 0x1b) {
        IWindow* w = mUI->FindEditorUIWindow(0x3f67620);
        if (w && (w->GetFlags() & 1)) {
            CloseSendPhotoWindow();
            return true;
        }
    }
    return false;
}

// @ 0x0063ef70
void cSPPlayModeSubModePhoto_s0063_e880::StartCameraFlash()
{
    if (mFlashEffect.mpObject) {
        mFlashEffect.mpObject->Stop(0);
        mFlashEffect = 0;
    }
    mFlashEffect = ((cEffectFactory*)FUN_00401050(0x44ed103, 0))->Create();
    mbFlashD = true;
    if (mTimerD.mnUnits == 1)
        mTimerD.mnStartTime = __rdtsc();
    else {
        int64_t t;
        QueryPerformanceCounter(&t);
        mTimerD.mnStartTime = t;
    }
    mTimerD.mnTotalElapsedTime = 0;
}

// @ 0x0063f060
void cSPPlayModeSubModePhoto_s0063_e880::FUN_0063f060()
{
    uint32_t val[2];
    uint32_t zero[2] = {0, 0};
    uint32_t* p = (uint32_t*)pad[2];
    IRangeTarget* t = *(IRangeTarget**)p;
    val[0] = p[5] | p[1];
    val[1] = p[6] | p[2];
    t->SetRange((uint64_t*)val, (uint64_t*)zero, 6);
    p = (uint32_t*)pad[2];
    val[0] = p[5] | p[1];
    val[1] = p[6] | p[2];
    ((IRangeTarget*)(*(void**)(*(char**)&pad[0] + 0x8c)))->SetRange((uint64_t*)val, (uint64_t*)zero, 6);
}

// @ 0x0063f2b0
cSPPlayModeSubModePhoto_s0063_e880::~cSPPlayModeSubModePhoto_s0063_e880()
{
}

// @ 0x0063f350
cFourStrings::~cFourStrings()
{}

// @ 0x0063f420
void cSPPlayModeSubModePhoto_s0063_e880::SavePhoto(uint16_t a)
{
    uint32_t key[3] = {0, 0, 0};
    wchar_t name[0x100];
    if (((cPhotoCheck*)pad[3])->FUN_00628940())
        GetIDGenerator()->Generate(key, 0x46194d0, 1, 0, 0, 0);
    else
        GetIDGenerator()->Generate(key, 0x65ea4ec, 1, 0, 0, 0);
    mCurrentPhotoID = key[0];
    cMsgDispatcher* disp = GetMsgDispatcher();
    cPhotoMsg* msg = new ("Editor", 0, 0, 0, 0) cPhotoMsg();
    if (msg)
        msg->AddRef();
    msg->mId = a;
    msg->mWidth = 0x280;
    msg->mType = 0x3eaed50;
    msg->mField14 = 0;
    msg->mPhotoID = mCurrentPhotoID;
    msg->mKey1 = key[1];
    msg->mGlobal = gPhotoGlobal;
    msg->mPhotoID2 = mCurrentPhotoID;
    MakeFileNameValid(mUI->GetPhotoName(name, 4));
    WStr_Format(&msg->mName, gFmtW, name);
    eastl::replace(msg->mName.mpBegin, msg->mName.mpEnd, L'!', L'_');
    eastl::replace(msg->mName.mpBegin, msg->mName.mpEnd, L'@', L'_');
    cPhotoOwner* owner = (cPhotoOwner*)pad[0];
    disp->Dispatch(**(uint32_t**)&pad[2], owner->f8c, owner->p360->f38, msg);
    ++mWriteJobCount;
    msg->Release();
}

// @ 0x0063f5c0
#pragma intrinsic(_InterlockedExchangeAdd)
void cSPPlayModeSubModePhoto_s0063_e880::SavePhotoSimple()
{
    wchar_t name[0x100];
    cSimpleMsg* msg = new ("Editor", 0, 0, 0, 0) cSimpleMsg();
    cRefCountedAsset* asset = ((cPhotoAssetManager*)GetPhotoAssets())->Lookup(mCurrentPhotoID, gPhotoGlobal, 0);
    _InterlockedExchangeAdd(&asset->mRefCount, 1);
    ((cPhotoAssetManager*)GetPhotoAssets())->Register(asset);
    msg->mPhotoID = mCurrentPhotoID;
    msg->mGlobal = gPhotoGlobal;
    msg->mb39 = true;
    msg->mb38 = false;
    msg->mPhotoID2 = mCurrentPhotoID;
    MakeFileNameValid(mUI->GetPhotoName(name, 4));
    WStr_Format(&msg->mName, gFmtW, name);
    eastl::replace(msg->mName.mpBegin, msg->mName.mpEnd, L'!', L'_');
    eastl::replace(msg->mName.mpBegin, msg->mName.mpEnd, L'@', L'_');
    cSPPlayModePhotoBrowser* b = &mPhotoBrowser;
    b->FUN_00631df0(msg);
    b->UpdatePhotoCountText();
    mUI->SetUIGroupVisible(0x410cf00, true);
    mUI->SetUIGroupVisible(0x41a30c0, true);
    mUI->SetUIGroupVisible(0x4463e78, true);
    mUI->SetEditorUIGroupVisible(0x447c040, true);
    mUI->SetEditorUIGroupVisible(0x447c4e8, true);
}

// @ 0x0063f740
void SP::cSPPlayModeSubModePhoto::WritePhotoWithComment(SP::cWriteJobInfo * a1, SP::ePlayModePhotoType a2, unsigned int a3)
{}

// @ 0x0063fa40
__declspec(noinline) bool cSPPlayModeSubModePhoto_s0063_f740::FUN_0063fa40()
{ gPartialCall(); return false; }

// @ 0x0063fd20
void cSPPlayModeSubModePhoto_s0063_f740::SendPhoto()
{
    cString_s0063_f740 s;
    if (!FUN_0063fa40()) {
        CloseSendPhotoWindow();
        BeginProfScope(0, 1)->End();
        FUN_00809db0((void*)0x1524c60, (void*)0x1524c18);
        mDialogInProgress = 8;
        if (*(int*)(*(int*)((char*)gAppProperties2 + 0x3c) + 0x118) == 0)
            FUN_00675250()->AutoTest(0xb4c2a66b, 1);
    }
}

// @ 0x0063fda0
void cSPPlayModeSubModePhoto_s0063_f740::FUN_0063fda0()
{}

// @ 0x006404f0
namespace SP {
bool cSPPlayModeSubModePhoto_s0064_04f0::HandleButton(int id)
{
    cString_s0064_04f0 unused;
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
            Pollen::cAuthManager_s0064_04f0* auth = Pollen::AuthManager();
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
}  // namespace SP

// @ 0x00640ee0
void cXX::FUN_00640ee0()
{}

// @ 0x00640fa0
void cXX::FUN_00640fa0()
{}

// @ 0x006411b0
void SP::cSPPlayModeSubModePhoto::CaptureImageDone()
{}
