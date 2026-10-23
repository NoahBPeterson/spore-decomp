// slice s00f04140 — Simulator::cScenarioYouTube, the YouTube "tell a friend" e-mail dialog.
// Reconstructed from the retail image (SporeApp.exe, 2017 build).
// flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"

// --------------------------------------------------------------------------- externals
void operator delete(void* p);                                            // 0x00F47380
void* __cdecl EAAllocate(uint32_t size, const char* tag, int a, int b, int c, int d);  // 0x00F473A0

extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedDecrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// --------------------------------------------------------------------------- eastl strings
namespace eastl {
extern wchar_t gEmptyString16[2];                          // 0x01667BAC ("" for char too)
template <typename T> struct EmptyStr;
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
template <> struct EmptyStr<char>    { static char*    Get() { return (char*)gEmptyString16; } };

template <typename T>
struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mPad;                                            // sizeof == 0x10
    basic_string() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()),
                     mpCapacity(EmptyStr<T>::Get() + 1) {}
    basic_string& operator=(const basic_string& o) {
        mpBegin = o.mpBegin; mpEnd = o.mpEnd; mpCapacity = o.mpCapacity;
        return *this;
    }
    ~basic_string() { DeallocateSelf(); }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin) operator delete(mpBegin);
        }
    }
    const T* c_str() const { return mpBegin; }
    basic_string& Assign(const T* pBegin, const T* pEnd);   // wchar: 0x00423650
};
typedef basic_string<char> string;
typedef basic_string<wchar_t> string16;

// The same 0x10-byte layout with a destructor but no constructor, for locals that the
// callee constructs in place (the retail codegen leaves them uninitialised).
struct string16_raw {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mPad;
    ~string16_raw() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin) operator delete(mpBegin);
        }
    }
};

template <typename T>
inline unsigned int CharStrlen(const T* p) {
    const T* pCurrent = p;
    while (*pCurrent) ++pCurrent;
    return (unsigned int)(pCurrent - p);
}
}

namespace EA {
namespace ResourceMan { struct Key { uint32_t mType, mName, mInstance; }; }
eastl::string16* ConvertToString16(eastl::string16* dst, const eastl::string* src);  // 0x0093C6D0
void ConvertToString16Impl(eastl::string16* dst, const char* src, uint32_t len);     // 0x0093C5A0
namespace Hash { uint32_t FNV1_String16(const wchar_t*, uint32_t, int); }            // 0x00932F30
}

// --------------------------------------------------------------------------- refcount layouts
// Layout A: slot +0x04 = Release, slot +0x08 = a second method.
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

// Layout B: slot +0x04 = AddRef, slot +0x08 = Release (cSPUILayout / token translator).
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

// Non-virtual atomic refcount stored at +0x08 (EA refcounted resource).
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

// --------------------------------------------------------------------------- auto refcount
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

// --------------------------------------------------------------------------- UTFWin
struct IWindow;
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
struct IWindow {
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
struct IControl {
    IControlVtbl* mpVtbl;
    void SetFlag(int a, bool b) { mpVtbl->SetFlag(this, a, b); }
};

struct cSPUILayout {
    RefBVtbl* mpVtbl;                                           // +0x00
    void AddRef() { mpVtbl->AddRef(this); }
    void Release() { mpVtbl->Release(this); }
    IWindow* FindWindowByID(uint32_t id, bool recurse);                        // 0x008105B0
    void     Shutdown(uint32_t a);                                            // 0x00811AD0
    bool     Init(const EA::ResourceMan::Key& key, bool b, uint32_t c);       // 0x008120D0
    bool     SetParentWin(IWindow* w, bool b, uint32_t c);                    // 0x008121B0
};

// --------------------------------------------------------------------------- EA property types
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

// --------------------------------------------------------------------------- manager interfaces
struct IPropertyManagerVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24; void* f28;
    void (__thiscall* GetProperty)(void*, uint32_t, uint32_t, Property*&);   // +0x2c
};
struct IPropertyManager {
    IPropertyManagerVtbl* mpVtbl;
    void GetProperty(uint32_t k1, uint32_t k2, Property*& out) {
        mpVtbl->GetProperty(this, k1, k2, out);
    }
};

struct IConfigManagerVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24; void* f28;
    void (__thiscall* SetBool)(void*, uint32_t, int);                        // +0x2c
};
struct IConfigManager {
    IConfigManagerVtbl* mpVtbl;
    void SetBool(uint32_t id, int v) { mpVtbl->SetBool(this, id, v); }
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

struct IAuthManagerVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24; void* f28; void* f2c;
    const eastl::string& (__thiscall* GetUser)(void*);                       // +0x30
};
struct IAuthManager {
    IAuthManagerVtbl* mpVtbl;
    const eastl::string& GetUser() { return mpVtbl->GetUser(this); }
};

struct IWindowManagerVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24; void* f28; void* f2c; void* f30; void* f34; void* f38; void* f3c;
    void* f40; void* f44; void* f48; void* f4c; void* f50; void* f54; void* f58; void* f5c;
    void* f60; void* f64; void* f68; void* f6c; void* f70; void* f74; void* f78; void* f7c;
    char  (__thiscall* IsVisible)(void*, IWindow*);                          // +0x80
};
struct IWindowManager {
    IWindowManagerVtbl* mpVtbl;
    char IsVisible(IWindow* w) { return mpVtbl->IsVisible(this, w); }
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

struct IMgrAVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24; void* f28; void* f2c; void* f30; void* f34; void* f38; void* f3c;
    void* f40; void* f44; void* f48; void* f4c; void* f50; void* f54; void* f58; void* f5c;
    void* f60; void* f64;
    int   (__thiscall* Count)(void*);                                        // +0x68
    void* f6c;
    void* (__thiscall* Get)(void*, int);                                     // +0x70
};
struct IMgrA {
    IMgrAVtbl* mpVtbl;
    int Count() { return mpVtbl->Count(this); }
    void* Get(int i) { return mpVtbl->Get(this, i); }
};

struct IMgrBVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24; void* f28; void* f2c; void* f30; void* f34; void* f38; void* f3c;
    void* (__thiscall* Make)(void*, int, int, int, int, int, int);           // +0x40
};
struct IMgrB {
    IMgrBVtbl* mpVtbl;
    void* Make(int a, int b, int c, int d, int e, int f) {
        return mpVtbl->Make(this, a, b, c, d, e, f);
    }
};

struct IMgrCVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24; void* f28;
    void (__thiscall* Set)(void*, void*);                                    // +0x2c
};
struct IMgrC {
    IMgrCVtbl* mpVtbl;
    void Set(void* p) { mpVtbl->Set(this, p); }
};

struct IMovieSystemVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24; void* f28; void* f2c;
    bool (__thiscall* IsPlaying)(void*);                                     // +0x30
    const wchar_t* (__thiscall* GetTitle)(void*);                            // +0x34
};
struct IMovieSystem {
    IMovieSystemVtbl* mpVtbl;
    bool IsPlaying() { return mpVtbl->IsPlaying(this); }
    const wchar_t* GetTitle() { return mpVtbl->GetTitle(this); }
};

struct ISaveAreaVtbl {
    void* f00; void* f04; void* f08; void* f0c; void* f10; void* f14; void* f18; void* f1c;
    void* f20; void* f24;
    const wchar_t* (__thiscall* GetName)(void*);                             // +0x28
};
struct ISaveArea {
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
struct IAudioSystem {
    IAudioSystemVtbl* mpVtbl;
    void* v20() { return mpVtbl->v20(this); }
    void v38(uint32_t a) { mpVtbl->v38(this, a); }
    void v40(uint32_t a, uint32_t b) { mpVtbl->v40(this, a, b); }
    void v58() { mpVtbl->v58(this); }
};

// --------------------------------------------------------------------------- globals / free funcs
extern const wchar_t* g_pYtLogin;                 // 0x015AD36C
extern IAppProps*     gAppProps;                  // 0x015FD918
extern uint32_t*      gField_016c7aa4;            // 0x016C7AA4
extern AutoRefCount<RefB> gTokenTranslator;       // 0x015F7CF4

IAuthManager*          AuthManager();             // 0x00607A60
IPropertyManager*      PropertyManager();         // 0x0067DE30
IConfigManager*        ConfigManager();           // 0x0067DD30
IWindowManager*        WindowManager();           // 0x0067CAA0
IUISystem*             UISystem();                // 0x0067DE40
IMgrA*                 MgrA();                    // 0x0067DD50
IMgrB*                 MgrB();                    // 0x0067DD60
IMgrC*                 MgrC();                    // 0x0067DDB0
IMovieSystem*          MovieSystem();             // 0x0067CB10
ISaveArea*             GetSaveArea(uint32_t id);  // 0x006B1F90
IAudioSystem*          AudioGetSystemAT();        // 0x00A206F0
bool                   GetYTPrompt();             // 0x0063B890

bool GetPropertyAsString8(Property* prop, uint32_t key, eastl::string* out);   // 0x006A13B0
void Decrypt(const eastl::string& in, eastl::string& out);                     // 0x0060BF00
void SP_SetWindowImage(void* win, void* rect, int a);                          // 0x00807BB0
void SP_UpdateMouseFocus(int a);                                               // 0x00804F50
struct CEdObj { void Method(bool a); };                                        // 0x00ED4F00
void FUN_00F040E0(eastl::string* s);                                           // 0x00F040E0

struct cProfScope { void End(); };                                             // 0x0067C420
cProfScope* __stdcall BeginProfScope(int a, int b);                            // 0x0067CAC0
void EndModal(IWindow* w, int a, int b);                                       // 0x00809C50 (cdecl)

struct CGameTimeManager { void DecPauseGate(void* gate); };                    // 0x00B32250
CGameTimeManager* GameTimeManager();                                           // 0x00B3D380

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

struct C760C00 { IWindow* Init(); };                               // 0x00760C00
struct C760FD0 { void Method(void* a, uint32_t b, void* c); };     // 0x00760FD0

namespace EA {
struct Stopwatch { void Init(int a, bool b); };                    // 0x0093A560
struct LimitStopwatch { void SetTimeLimit(uint32_t a, bool b); };  // 0x0093A480
}

namespace SP {
struct cString {
    eastl::string16 mpText;                                        // +0x00
    uint32_t mKey;                                                 // +0x10
    uint32_t mTable;                                               // +0x14
    cString();                                                     // 0x006B5060
    cString(uint32_t table, uint32_t key, const wchar_t* text);    // 0x006B5770
    ~cString();                                                    // 0x006B5240
    bool Load(uint32_t table, uint32_t key, const wchar_t* text);  // 0x006B54B0
    const wchar_t* GetText();                                      // 0x006B55C0
};
}

// --------------------------------------------------------------------------- the class
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
    cSPUILayout* mLayout;      // +0x2c
    IWindow* mpWin30;          // +0x30
    IWindow* mpWin34;          // +0x34
    IWindow* mpWin38;          // +0x38
    uint32_t mWidth;           // +0x3c
    uint32_t mHeight;          // +0x40
    float mFloat44;            // +0x44
    float mFloat48;            // +0x48
    float mFloat4c;            // +0x4c
    bool mBool50;              // +0x50
    bool mBool51;              // +0x51
    bool mBool52;              // +0x52
    char mPad53;
    eastl::string16 mStr54;    // +0x54
    eastl::string16 mStr64;    // +0x64
    uint32_t mField74;         // +0x74
    bool mBool78;              // +0x78
    bool mBool79;              // +0x79
    char mPad7a[2];
    eastl::string mStr7c;      // +0x7c
    eastl::string mStr8c;      // +0x8c
    eastl::string mStr9c;      // +0x9c
    eastl::string16 mStrAc;    // +0xac
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

    void  FUN_00f04140(const eastl::string* s);
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
int FUN_00f04530(char flag);

using Simulator::cScenarioYouTube;

// object allocated by FUN_00f04530 (vtbl 0x148B834, Release at +0x04)
struct TokenObjVtbl {
    void* f00;
    void (__thiscall* Release)(void*);                          // +0x04
    void (__thiscall* v08)(void*);                              // +0x08
};
struct TokenObj {
    TokenObjVtbl* volatile mpVtbl;           // +0x00
    uint32_t mField4;                        // +0x04
    uint32_t mField8;                        // +0x08
    uint32_t mFieldC;                        // +0x0c
    AutoRefCount<IWindow> mPtr10;            // +0x10
    AutoRefCount<AtomicRefCounted> mRef14;   // +0x14
    uint32_t mField18;                       // +0x18
    uint32_t mField1c;                       // +0x1c
};

// =========================================================================== 0x00F04140
// @ 0x00F04140
void cScenarioYouTube::FUN_00f04140(const eastl::string* s)
{
    IWindow* pWin = mLayout->FindWindowByID(0x5650500, true);
    eastl::string16_raw t;
    eastl::string16* pt = EA::ConvertToString16((eastl::string16*)&t, s);
    pWin->SetCaption(pt->mpBegin);
}

// =========================================================================== 0x00F041A0
// @ 0x00F041A0
void cScenarioYouTube::FUN_00f041a0()
{
    eastl::string16_raw caption;
    EA::ConvertToString16Impl((eastl::string16*)&caption, AuthManager()->GetUser().c_str(), (uint32_t)-1);
    IWindow* wc = mLayout->FindWindowByID(0x4581d50, true);
    wc->SetCaption((const wchar_t*)caption.mpBegin);

    SP::cString text;
    IWindow* w = mLayout->FindWindowByID(0x45adfc8, true);
    if (w) {
        text.Load(0x7518573e, 0x5b5b8c4, L"*Tell a friend about your video*");
        IWindowVtbl* vt = w->mpVtbl;
        const wchar_t* t = text.GetText();
        vt->SetCaption(w, t);
    }
    w = mLayout->FindWindowByID(0x45ae078, true);
    if (w) {
        text.Load(0x7518573e, 0x45ad62f, L"*Your Email*");
        IWindowVtbl* vt = w->mpVtbl;
        const wchar_t* t = text.GetText();
        vt->SetCaption(w, t);
    }
    w = mLayout->FindWindowByID(0x45ae090, true);
    if (w) {
        text.Load(0x7518573e, 0x45ad634, L"*Recipient's Email*");
        IWindowVtbl* vt = w->mpVtbl;
        const wchar_t* t = text.GetText();
        vt->SetCaption(w, t);
    }
    w = mLayout->FindWindowByID(0x45ae0c0, true);
    if (w) {
        text.Load(0x7518573e, 0x45ad63a, L"*Your Message*");
        IWindowVtbl* vt = w->mpVtbl;
        const wchar_t* t = text.GetText();
        vt->SetCaption(w, t);
    }

    SP::cString msg(0x7518573e, 0x56bcdca, L"*Check out my video!*");
    IWindow* wm = mLayout->FindWindowByID(0x4581d90, true);
    IWindowVtbl* vm = wm->mpVtbl;
    const wchar_t* m = msg.GetText();
    vm->SetCaption(wm, m);

    w = mLayout->FindWindowByID(0x3ffb8cc, true);
    if (w) {
        uint32_t rect[3];
        rect[0] = 0xb563455a;
        rect[1] = 0x2f7d0004;
        rect[2] = 0x40607300;
        SP_SetWindowImage(w, rect, 0);
    }

    mLayout->FindWindowByID(0x3f67620, true)->SetFlag(1, 1);
}

// =========================================================================== 0x00F043D0
// @ 0x00F043D0
void cScenarioYouTube::FUN_00f043d0()
{
    AutoRefCount<Property> prop;
    IPropertyManager* pm = PropertyManager();
    Property*& pOut = prop.AsOutParam();
    pm->GetProperty(EA::Hash::FNV1_String16(g_pYtLogin, 0x811c9dc5, 1), 0x11ac192, pOut);
    if (prop) {
        GetPropertyAsString8(prop, 0x5664bf5, &mStr8c);
        eastl::string tmp;
        if (GetPropertyAsString8(prop, 0x5664bf6, &tmp))
            Decrypt(tmp, mStr9c);
    } else {
        ConfigManager()->SetBool(0x5664a8b, 0);
    }
}

// =========================================================================== 0x00F044D0
// @ 0x00F044D0
void cScenarioYouTube::FUN_00f044d0()
{
    IWindow* w = mLayout->FindWindowByID(0xffffffff, true);
    if (WindowManager()->IsVisible(w)) {
        EndModal(w, 0, 0);
        CGameTimeManager* gtm = GameTimeManager();
        gtm->DecPauseGate((void*)0x4bf38a4);
    }
    BeginProfScope(1, 1)->End();
    mField28 = 0;
}

// =========================================================================== 0x00F04530
// @ 0x00F04530
int FUN_00f04530(char flag)
{
    uint32_t id = 0x7c651b0 + (uint32_t)(flag != 0);
    uint32_t sz = ((unsigned char)flag != 0) ? 0x100 : 0x80;

    TokenObj* pTok = (TokenObj*)EAAllocate(0x1c, "Simulator", 0, 0, 0, 0);
    if (pTok) {
        pTok->mField4 = 0;
        pTok->mpVtbl = (TokenObjVtbl*)0x148b834;
        pTok->mPtr10.mpObject = 0;
        pTok->mRef14.mpObject = 0;
        pTok->mpVtbl->Release(pTok);
    }

    IWindow* pOther = 0;
    void* mem = EAAllocate(0x20, "Simulator", 0, 0, 0, 0);
    if (mem) {
        pOther = ((C760C00*)mem)->Init();
        if (pOther) pOther->AddRef();
    }

    int n = MgrA()->Count();
    for (int i = 0; i < n; ++i) {
        uint32_t* e = (uint32_t*)MgrA()->Get(i);
        if (e[1] < 0x1a)
            ((C760FD0*)pOther)->Method((void*)e[0], e[1], (void*)e[2]);
    }

    void* created = MgrB()->Make(sz, sz, 1, 0x208, 0x15, 8);

    pTok->mField8 = 0;
    pTok->mFieldC = sz;
    pTok->mField18 = id;
    pTok->mPtr10 = pOther;
    pTok->mRef14 = (AtomicRefCounted*)created;

    MgrC()->Set(pTok);
    if (pOther) pOther->Release();
    pTok->mpVtbl->v08(pTok);
    return (int)created;
}

// =========================================================================== 0x00F046E0
// @ 0x00F046E0
void* cScenarioYouTube::FUN_00f046e0(unsigned flags)
{
    if (mpMsgHandler)
        mpMsgHandler->Release();
    if (mpRef10)
        mpRef10->Release();
    mpVtbl0 = (void*)0x13ef094;
    if (flags & 1)
        operator delete(this);
    return this;
}

// =========================================================================== 0x00F04740
// @ 0x00F04740
void* cScenarioYouTube::FUN_00f04740()
{
    // The two interface base sub-objects publish their own vtable first; both stores are
    // overwritten by the cScalarObject vtables below, so they must be volatile to survive
    // MSVC's dead-store elimination.
    *(void* volatile*)((char*)this + 8) = (void*)0x13eb394;
    *(void* volatile*)((char*)this + 0xc) = (void*)0x13ec458;
    mpRef10 = 0;
    mpVtbl0 = (void*)0x148b864;
    mpVtbl4 = (void*)0x148b858;
    mpVtbl8 = (void*)0x148b850;
    mpVtblc = (void*)0x148b840;
    mpMsgHandler = 0;
    mpMsgA = 0;
    mpMsgB = 0;
    mpMsgC = 0;
    mpMsgD = 0;
    mField28 = 0;
    mLayout = 0;
    mpWin30 = 0;
    mpWin34 = 0;
    mpWin38 = 0;
    // MSVC's scheduler otherwise hoists this whole float group up into the vtable stores;
    // the volatile qualifiers pin the stores to their source position (the original keeps
    // only the 15.0f constant load hoisted to the very top of the function).
    *(float volatile*)&mFloat44 = 15.0f;
    mWidth = 0x140;
    mHeight = 0xf0;
    mBool51 = false;
    *(float volatile*)&mFloat48 = 0.0f;
    *(float volatile*)&mFloat4c = 0.8f;
    mBool50 = true;
    mBool52 = true;
    mStr54 = eastl::string16();
    mStr64 = eastl::string16();
    mField74 = 0;
    mBool78 = false;
    mBool79 = false;
    mStr7c = eastl::string();
    mStr8c = eastl::string();
    mStr9c = eastl::string();
    mStrAc = eastl::string16();
    mBoolBc = false; mBoolBd = false; mBoolBe = false; mBoolBf = false;
    mBoolC0 = false; mBoolC1 = false; mBoolC2 = false; mBoolC3 = false;
    mBoolC4 = false; mBoolC5 = false; mBoolC6 = false;
    mFieldC8 = 0;
    mpRefCc = 0;
    mVec0.mpBegin = 0; mVec0.mpEnd = 0; mVec0.mpCap = 0;
    mVec1.mpBegin = 0; mVec1.mpEnd = 0; mVec1.mpCap = 0;
    mBoolF8 = false;
    mBoolF9 = true;
    ((EA::Stopwatch*)mStopwatch)->Init(4, false);
    ((EA::LimitStopwatch*)mStopwatch)->SetTimeLimit(0, false);
    return this;
}

// =========================================================================== 0x00F04910
// @ 0x00F04910
void cScenarioYouTube::FUN_00f04910()
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

// =========================================================================== 0x00F04AD0
// @ 0x00F04AD0
void cScenarioYouTube::FUN_00f04ad0()
{
    FUN_00f044d0();
    UISystem()->GetSub()->v20(gTokenTranslator.mpObject);
    gTokenTranslator = (RefB*)0;

    mpWin38->RemoveProc(this);
    if (mpWin38) {
        IWindow* w = mpWin38;
        mpWin38 = 0;
        w->Release();
    }

    mLayout->FindWindowByID(0xffffffff, true)->RemoveProc(this);
    mLayout->Shutdown(1);
    if (mLayout) {
        cSPUILayout* l = mLayout;
        mLayout = 0;
        l->Release();
    }

    bool b = (uint32_t)(mVec0.mpEnd - mVec0.mpBegin) < 0x32;
    if (mpWin38) {
        IWindow* child = (IWindow*)mpWin38->FindChild(0x78d57d8, 1);
        if (child)
            child->SetFlag(2, b);
    }
    void* h = *(void**)((char*)gField_016c7aa4 + 0x14);
    if (h)
        ((CEdObj*)h)->Method(b);
}

// =========================================================================== 0x00F04BD0
// @ 0x00F04BD0
void cScenarioYouTube::FUN_00f04bd0()
{
    IAudioSystem* au = AudioGetSystemAT();
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

    IMovieSystem* ms = MovieSystem();
    const wchar_t* p1 = ms->GetTitle();
    mStr54.Assign(p1, p1 + eastl::CharStrlen(p1));

    ISaveArea* sa = GetSaveArea(0x11ac197);
    const wchar_t* p2 = sa->GetName();
    mStr64.Assign(p2, p2 + eastl::CharStrlen(p2));

    mBool78 = true;
    mBool79 = true;
    mpWin30->SetFlag(1, 1);
    mpWin34->SetFlag(1, 0);
    SP_UpdateMouseFocus(1);
    mField74 = 0;
}

// =========================================================================== 0x00F04D10
// @ 0x00F04D10
void cScenarioYouTube::FUN_00f04d10(int arg)
{
    void* mem = EAAllocate(0x60, "Simulator/cPlayModeTokenTranslator", 0, 0, 0, 0);
    cPlayModeTokenTranslator* tt = mem ? ((cPlayModeTokenTranslator*)mem)->ctor() : 0;

    gTokenTranslator = (RefB*)tt;

    UISystem()->GetSub()->v1c(gTokenTranslator.mpObject);

    void* lmem = EAAllocate(0x18, "UI/cSPUILayout", 0, 0, 0, 0);
    cSPUILayout* layout = lmem ? (cSPUILayout*)((CSPUILayoutCtor*)lmem)->ctor() : 0;
    cSPUILayout* oldLayout = mLayout;
    if (layout != oldLayout) {
        if (layout) layout->AddRef();
        mLayout = layout;
        if (oldLayout) oldLayout->Release();
    }

    EA::ResourceMan::Key key;
    key.mType = 0x784e37b4;
    key.mName = 0x510a95b;
    key.mInstance = 0x40464100;
    mLayout->Init(key, false, 0x5b598fa);

    cSPUILayout* lay = layout;
    lay->SetParentWin(lay->FindWindowByID(0xffffffff, true), true, 0x5b598fa);

    IWindow* w = lay->FindWindowByID(0x7916468, true);
    IWindow* old38 = mpWin38;
    if (w != old38) {
        if (w) w->AddRef();
        mpWin38 = w;
        if (old38) old38->Release();
    }
    mpWin38->AddProc(this);
    mLayout->FindWindowByID(0xffffffff, true)->AddProc(this);

    w = mLayout->FindWindowByID(0x78ec978, true);
    IWindow* old30 = mpWin30;
    if (w != old30) {
        if (w) w->AddRef();
        mpWin30 = w;
        if (old30) old30->Release();
    }

    w = mLayout->FindWindowByID(0x78d57d0, true);
    IWindow* old34 = mpWin34;
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
    IWindow* hint = mLayout->FindWindowByID(0x5665f58, true);
    IControl* ctl = hint ? (IControl*)hint->GetControl(0x8ed27e7a) : 0;
    if (ctl)
        ctl->SetFlag(4, !bPrompt);

    if (MovieSystem()->IsPlaying())
        FUN_00f04bd0();

    bool b = (uint32_t)(mVec0.mpEnd - mVec0.mpBegin) < 0x32;
    if (mpWin38) {
        IWindow* child = (IWindow*)mpWin38->FindChild(0x78d57d8, 1);
        if (child)
            child->SetFlag(2, b);
    }
    void* h = *(void**)((char*)gField_016c7aa4 + 0x14);
    if (h)
        ((CEdObj*)h)->Method(b);
}
