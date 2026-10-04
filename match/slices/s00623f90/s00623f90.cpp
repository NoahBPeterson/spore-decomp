// slice s00623f90: Pollen XHTML window bits, camera random helpers, cCreatureCameraBase
#include <new>
#include <string.h>
#include <math.h>
#include <float.h>
#include <wchar.h>
#include "types.h"

namespace EA {
namespace Random {
class RandomLinearCongruential {
public:
    uint32_t mnSeed;
    void SetSeed(uint32_t seed);
    double RandomDoubleUniform();
};
}
}
extern EA::Random::RandomLinearCongruential sMathRandomA;   // 0x1601760
extern EA::Random::RandomLinearCongruential sMathRandomB;   // 0x15f6470

__forceinline float RandomRangeClampedA(float a, float b)
{
    const double lo = a;
    const double hi = b;
    double d = lo + (hi - lo) * sMathRandomA.RandomDoubleUniform();
    if (d >= hi)
        return (float)hi;
    if (d < lo)
        return (float)lo;
    return (float)d;
}
__forceinline float RandomMaxA(float b)
{
    const double hi = b;
    double d = sMathRandomA.RandomDoubleUniform() * hi;
    if (d >= hi)
        d = hi;
    else if (d < 0)
        d = 0;
    return (float)d;
}
__forceinline float RandomRangeClampedB(float a, float b)
{
    const double lo = a;
    const double hi = b;
    double d = lo + (hi - lo) * sMathRandomB.RandomDoubleUniform();
    if (d >= hi)
        return (float)hi;
    if (d < lo)
        return (float)lo;
    return (float)d;
}
__forceinline float RandomMaxB(float b)
{
    const double hi = b;
    double d = sMathRandomB.RandomDoubleUniform() * hi;
    if (d >= hi)
        d = hi;
    else if (d < 0)
        d = 0;
    return (float)d;
}

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct Vector3 { float x, y, z; Vector3() {} Vector3(float a, float b, float c) : x(a), y(b), z(c) {} };
static inline Vector3 operator*(const Vector3& v, float s) { return Vector3(v.x * s, v.y * s, v.z * s); }
struct Quaternion { float x, y, z, w; };

// @ 0x006249b0
struct RandomOwner {
    virtual void v0();
    RandomOwner();
};
RandomOwner::RandomOwner()
{
    sMathRandomB.SetSeed(0);
}

Vector3* __cdecl FUN_00699600(Vector3* out, const Vector3* a, const Vector3* b, float t);
void __cdecl FUN_0069b840(float a, float b, float c);
void __cdecl FUN_0069b760(int a, int b, int c);
void __cdecl FUN_00699730(float a, float b);
Quaternion* __cdecl QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing, const Vector3* up);
Quaternion* __cdecl FUN_005b2500(Quaternion* tmp, const Vector3* axis, const Vector3* b, float f);

// @ 0x006249d0
Quaternion* __stdcall w_6249d0(Quaternion* out, const Vector3* facing, const Vector3* up)
{
    QuaternionFromFacingAndUp(out, facing, up);
    return out;
}

struct T9f0 { void FUN_006b9440(void* p); };
// @ 0x006249f0
void* __stdcall w_6249f0(void* out, T9f0* self)
{
    self->FUN_006b9440(out);
    return out;
}

// @ 0x00624a10
Vector3* __stdcall w_624a10(Vector3* out, const Vector3* a, const Vector3* b, float t)
{
    FUN_00699600(out, a, b, t);
    return out;
}

// @ 0x00624a40
void __stdcall w_624a40(float a, float b, float c)
{
    FUN_0069b840(a, b, c);
}

// @ 0x00624a70
void __stdcall w_624a70(int a, int b, int c)
{
    FUN_0069b760(a, b, c);
}

// @ 0x00624ab0
void __stdcall w_624ab0(float a, float b)
{
    FUN_00699730(a, b);
}

struct ISlot54 {
    PV16 PV4 PV
    virtual void SetRange(float lo, float hi);   // +0x54
    // @ 0x00624b00
    void W624b00(float v) { SetRange(-v, v); }
    // @ 0x00624b30
    void W624b30(float c, float r) { SetRange(c - r, c + r); }
};
void ForceW1(ISlot54* s) { s->W624b00(1.0f); s->W624b30(1.0f, 2.0f); }

// @ 0x00624b80
float __stdcall w_624b80(float m) { return RandomMaxA(m); }
// @ 0x00624bc0
float __stdcall w_624bc0(float a, float b) { return RandomRangeClampedA(a, b); }
// @ 0x00624c10
float __stdcall w_624c10(const float* r) { return RandomRangeClampedA(r[0], r[1]); }
// @ 0x00624c60
float __stdcall w_624c60(float m) { return RandomRangeClampedA(-m, m); }
// @ 0x00624cb0
float __stdcall w_624cb0(float c, float r) { return RandomRangeClampedA(c - r, c + r); }
// @ 0x00624d10
float __stdcall w_624d10(float m) { return RandomMaxB(m); }
// @ 0x00624d50
float __stdcall w_624d50(float a, float b) { return RandomRangeClampedB(a, b); }
// @ 0x00624da0
float __stdcall w_624da0(const float* r) { return RandomRangeClampedB(r[0], r[1]); }

// @ 0x00624df0
Quaternion* __stdcall w_624df0(Quaternion* out, const Vector3* axis, float angle)
{
    float s = sinf(angle * 0.5f);
    float c = cosf(angle * 0.5f);
    Vector3 v = *axis * s;
    out->x = v.x;
    out->y = v.y;
    out->z = v.z;
    out->w = c;
    return out;
}

// @ 0x00624e40
Quaternion* __stdcall w_624e40(Quaternion* out, const Vector3* a, const Vector3* b, float f)
{
    Quaternion tmp;
    Quaternion* p = FUN_005b2500(&tmp, a, b, f);
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    out->w = p->w;
    return out;
}

// ---- cCreatureCameraBase ----
namespace EA { namespace Messaging {
class Server;
void __cdecl RemoveHandler(Server* srv, void* handler, void* ids, int count, int prio);
struct AutoHandler {
    Server* mpServer;
    void* mpHandler;
    void* mpIdArray;
    int mnIdArrayCount;
    int mnPriority;
};
} }

struct IWinMgr {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4();
    virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9();
    virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14();
    virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24();
    virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29();
    virtual void p30(); virtual void p31(); virtual void p32();
    virtual void* GetInputCapture();   // +0x84
};
struct AssetBrowserT { char pad[0x1c]; bool mbBusy; };
IWinMgr* __cdecl WindowManager();
AssetBrowserT* __cdecl AssetBrowser();

namespace SP {
class cCreatureCameraDepends {
public:
    char pad[0x78];
    bool OnKeyDown(int a, int b);
    bool OnKeyUp_SendMessage(int a, int b);
};

class cICameraController { public: virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); };
class IRef2 { public: virtual void r0(); virtual void r1(); };

class cCreatureCameraBase : public cICameraController, public IRef2 {
public:
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void Dispose();   // +0x1c
    int padA[2];
    cCreatureCameraDepends mDepends;  // +0x10
    int mCameraInputState;            // +0x88
    char pad2[0x1d0 - 0x8c];
    EA::Messaging::AutoHandler mMessageRegistration;  // +0x1d0
    char pad3[0x1ec - 0x1e4];
    volatile bool mMouseLeftButton;
    volatile bool mMouseMiddleButton;
    volatile bool mMouseRightButton;
    bool mbActive;
    bool mbEnabled;
    bool Shutdown();
    void Deactivate();
    bool OnKeyDown(int a, int b);
    bool OnKeyUp(int a, int b);
    void W624f90(bool v);
};

// @ 0x00624eb0
bool cCreatureCameraBase::Shutdown()
{
    Dispose();
    return true;
}

// @ 0x00624ec0
void cCreatureCameraBase::Deactivate()
{
    if (mbActive) {
        mMouseLeftButton = false;
        mMouseMiddleButton = false;
        mMouseRightButton = false;
        EA::Messaging::Server* pServer = mMessageRegistration.mpServer;
        if (pServer) {
            mMessageRegistration.mpServer = 0;
            EA::Messaging::RemoveHandler(pServer, mMessageRegistration.mpHandler, mMessageRegistration.mpIdArray,
                                         mMessageRegistration.mnIdArrayCount, mMessageRegistration.mnPriority);
        }
        mbActive = false;
    }
}

// @ 0x00624f20
bool cCreatureCameraBase::OnKeyDown(int a, int b)
{
    if (mbEnabled) {
        void* r = WindowManager()->GetInputCapture();
        AssetBrowserT* ab = AssetBrowser();
        if (!r && !ab->mbBusy)
            mDepends.OnKeyDown(a, b);
    }
    return false;
}

// @ 0x00624f70
bool cCreatureCameraBase::OnKeyUp(int a, int b)
{
    if (mbEnabled)
        mDepends.OnKeyUp_SendMessage(a, b);
    return false;
}
}

namespace SP {
// @ 0x00624f90
void cCreatureCameraBase::W624f90(bool v)
{
    if (!v)
        mCameraInputState = 0;
}
}


// ===========================================================================
// Pollen XHTML window pieces
// ===========================================================================
struct WString { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; };   // eastl::basic_string<wchar_t>
struct LinkNode { LinkNode* mpNext; LinkNode* mpPrev; };
extern wchar_t gEmptyWString[];   // shared empty-string storage (0x1667bac)

struct WStringLocal {   // eastl::basic_string<wchar_t> local with an inline default ctor
    const wchar_t* mpBegin;
    const wchar_t* mpEnd;
    const wchar_t* mpCapacity;
    WStringLocal() : mpBegin(gEmptyWString), mpEnd(gEmptyWString), mpCapacity(gEmptyWString + 1) {}
    ~WStringLocal();   // 0x933960 (SP::QualifyNameWithGroup in the name table: really the string dtor)
};

float __cdecl GetElapsedSeconds();   // SPUIHelpers::GetElapsedSeconds
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);
void* __cdecl FUN_009512c0();
void* __cdecl FUN_009512d0(unsigned size, unsigned align, const char* name, void* alloc);

struct IQuery {
    virtual void q0();
    virtual void q1();
    virtual void q2();
    virtual void* Query(unsigned id);   // +0x0c
};

struct DomNode {
    virtual void d0();
    virtual void d1();
    virtual void GetText(WString* out);   // +0x08
    LinkNode link;                        // +4 (mpNext, mpPrev)
    int Type();                           // EA::XHTML::DOM::Node::Type (0xfc7e50)
};
struct Element : DomNode {
    char padE[0x18 - 0x0c];
    LinkNode mChildren;                   // +0x18 circular anchor
    char padE2[0x28 - 0x20];
    int mType;                            // +0x28
    char padE3[0x44 - 0x2c];
    IQuery* mpControl;                    // +0x44
    const wchar_t* GetAttrValue(const wchar_t* name);   // 0x8e45b0
};
struct FormControl : Element {
    void SetControl(void* pWindow);       // 0x8e4b60
};

// Generic UTFWin window object (vtable slots used by the form-control builders).
struct IWinObj {
    virtual void AddRef();
    virtual void Release();
    virtual void w2();
    virtual void w3();
    virtual void w4();
    virtual void w5();
    virtual void w6();
    virtual void w7();
    virtual void w8();
    virtual void w9();
    virtual void w10();
    virtual void w11();
    virtual void w12();
    virtual void w13();
    virtual void w14();
    virtual void w15();
    virtual void w16();
    virtual void w17();
    virtual void w18();
    virtual void w19();
    virtual void w20();
    virtual void SetCommand(unsigned id);
    virtual void w22();
    virtual void w23();
    virtual void w24();
    virtual void w25();
    virtual void w26();
    virtual void w27();
    virtual void w28();
    virtual void w29();
    virtual void w30();
    virtual void SetFlag(int flag, int value);
    virtual void SetCaption(const wchar_t* text);
    virtual void w33();
    virtual void w34();
    virtual void w35();
    virtual void w36();
    virtual void w37();
    virtual void w38();
    virtual void w39();
    virtual void w40();
    virtual void w41();
    virtual void w42();
    virtual void SetColorA(unsigned c);
    virtual void SetColorB(unsigned c);
    virtual void w45();
    virtual void SetProperty(unsigned id, void* pRef);
};
// Text-edit control interface (second base of WinTextEdit at +0x20c).
struct ITextCtl {
    virtual void t0();
    virtual void Release();
    virtual void t2();
    virtual void t3();
    virtual IWinObj* GetWindow();
    virtual void t5();
    virtual void t6();
    virtual void t7();
    virtual void t8();
    virtual void t9();
    virtual void SetMargins(const float* rect);
    virtual void t11();
    virtual void t12();
    virtual void t13();
    virtual void t14();
    virtual void t15();
    virtual void SetAlign(int a);
    virtual void SetFlags(int a, int b);
    virtual void t18();
    virtual void t19();
    virtual void t20();
    virtual void t21();
    virtual void t22();
    virtual void t23();
    virtual void t24();
    virtual void t25();
    virtual void SetMaxLength(int n);
    virtual void t27();
    virtual void t28();
    virtual void t29();
    virtual void t30();
    virtual void t31();
    virtual void t32();
    virtual void t33();
    virtual void t34();
    virtual void t35();
    virtual void t36();
    virtual void t37();
    virtual void t38();
    virtual void t39();
    virtual void t40();
    virtual void t41();
    virtual void t42();
    virtual void t43();
    virtual void t44();
    virtual void t45();
    virtual void t46();
    virtual void t47();
    virtual void t48();
    virtual void t49();
    virtual void t50();
    virtual void t51();
    virtual void t52();
    virtual void t53();
    virtual void t54();
    virtual void t55();
    virtual void t56();
    virtual void t57();
    virtual void SetFont(int a, void* font);
};
// Window container (this+0xa67c).
struct IWinContainer {
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
    virtual void c12();
    virtual void c13();
    virtual void c14();
    virtual void c15();
    virtual void c16();
    virtual void c17();
    virtual void c18();
    virtual void c19();
    virtual void c20();
    virtual void c21();
    virtual void c22();
    virtual void c23();
    virtual void c24();
    virtual void c25();
    virtual void c26();
    virtual void c27();
    virtual void c28();
    virtual void c29();
    virtual void c30();
    virtual void c31();
    virtual void c32();
    virtual void c33();
    virtual void c34();
    virtual void c35();
    virtual void c36();
    virtual void c37();
    virtual void c38();
    virtual void c39();
    virtual void c40();
    virtual void c41();
    virtual void c42();
    virtual void c43();
    virtual void c44();
    virtual void c45();
    virtual void c46();
    virtual void c47();
    virtual void c48();
    virtual void c49();
    virtual void c50();
    virtual void c51();
    virtual void c52();
    virtual void c53();
    virtual void AddWindow(IWinObj* w);
};
// Popup-menu window (cSPUIPopupMenuWin).
struct cSPUIPopupMenuWin {
    virtual void AddRef();
    virtual void Release();
    char pad[0x8c8 - 4];
    unsigned mField8c8;
    void* AddMenuItem(const unsigned* key, int a, int b, int c);   // 0x81b6a0
};
struct cSPUILayout {   // 0x810000 ctor ... (24 bytes of state)
    unsigned pad[6];
    cSPUILayout();
    ~cSPUILayout();
    bool Init(const unsigned* key, int a, int b);                  // 0x8120d0
    IWinObj* FindWindowByID(int id, int recurse);                  // 0x8105b0
    void Shutdown(bool b);                                         // 0x811ad0
};
template <class T> struct AutoRef {   // EA::AutoRefCount<T> (AsPPTypeParam is not inlined in this build)
    T* mp;
    AutoRef() : mp(0) {}
    ~AutoRef() { if (mp) mp->Release(); }
    T** AsPPTypeParam();
    void Assign(T* p);   // operator=(T*): AddRef new, Release old (0xb5f950)
};
bool __cdecl CreateXHTMLButton(IWinObj** pOut);    // SP::Pollen::CreateXHTMLButton (0x6230b0)
cSPUIPopupMenuWin* __cdecl InterfaceCastPopup(AutoRef<IWinObj>* p);   // 0x623090
struct WinXHTMLBase {
    bool ShouldCreate(FormControl* pCtl);          // 0x623000
    void CreateFormControlBase(FormControl* pCtl); // 0x994c80  EA::UTFWinExtras::WinXHTML::CreateFormControl
};
struct WinTextEditObj {
    char pad4[4];
    IWinObj mWin;                                  // +4 (subobject; only its vtable is used)
    char pad5[0x20c - 8];
    ITextCtl mText;                                // +0x20c
    WinTextEditObj();                              // 0x98c110
    void SetMode(int mode);                        // 0x9896c0
};
extern const wchar_t* gAttrType;       // 0x1521294  L"type"
extern const wchar_t* gAttrValue;      // 0x1521298  L"value"
extern const wchar_t* gAttrLabel;      // 0x152129c  L"label"
extern const wchar_t* gAttrDisabled;   // 0x15212a0  L"disabled"
extern const wchar_t* gAttrReadonly;   // 0x15212a4  L"readonly"
extern const wchar_t* gAttrSize;       // 0x15212a8  L"size"
extern const wchar_t* gAttrMultiple;   // 0x15212ac  L"multiple"
extern const wchar_t* gValButton;      // 0x15212b4  L"button"
extern const wchar_t* gValSubmit;      // 0x15212b8  L"submit"
extern const wchar_t* gValReset;       // 0x15212bc  L"reset"
extern const wchar_t* gValText;        // 0x15212c4  L"text"
extern const float gTextMarginUnit;    // 0x14853e0

struct FormControlRef {   // 12-byte ref object stored as a window property
    void* vtbl;
    int mnRefCount;
    FormControl* mpControl;
    FormControlRef(FormControl* p) : mnRefCount(0), mpControl(p) {}
    virtual void vf0();
};

// --- 0x00623f90 : popup tooltip timer message handler ---
struct SMessage { char pad[8]; int mId; char pad2[0x18 - 0x0c]; const wchar_t* mpData; };
struct IPopWin {
    virtual void pw0();
    virtual void pw1();
    virtual void pw2();
    virtual void pw3();
    virtual void pw4();
    virtual void pw5();
    virtual void pw6();
    virtual void pw7();
    virtual void pw8();
    virtual void pw9();
    virtual unsigned IsShown();
    virtual void pw11();
    virtual void pw12();
    virtual void pw13();
    virtual void pw14();
    virtual void pw15();
    virtual void pw16();
    virtual void pw17();
    virtual void pw18();
    virtual void pw19();
    virtual void pw20();
    virtual void pw21();
    virtual void pw22();
    virtual void pw23();
    virtual void pw24();
    virtual void pw25();
    virtual void pw26();
    virtual void pw27();
    virtual void pw28();
    virtual void pw29();
    virtual void pw30();
    virtual void SetFlag(int flag, int value);
};
struct WStrMember {   // eastl::basic_string<wchar_t> member (12 bytes)
    wchar_t* a; wchar_t* b; wchar_t* c;
    WStrMember& operator=(const wchar_t* p);   // 0x5c3d90
};
struct cPopupTimer {
    char pad0[0x10];
    int mField10;
    IPopWin* mpWin;
    float mNextTime;
    WStrMember mText;     // +0x1c
    bool OnMessage(void* unused, SMessage* m);   // @ 0x00623f90
    void Refresh();       // 0x623830
    void Create();        // 0x6239c0
};
extern const float kDelayShort; // 0x15f6154
extern const float kDelayLong;  // 0x15f627c

// @ 0x00623f90
bool cPopupTimer::OnMessage(void* unused, SMessage* m)
{
    if (m->mId == 0xc) {
        float now = GetElapsedSeconds();
        if (mNextTime <= now) {
            if (mpWin->IsShown() & 1) {
                mpWin->SetFlag(1, 0);
                mNextTime = FLT_MAX;
            } else {
                Refresh();
                mNextTime = GetElapsedSeconds() + kDelayShort;
            }
        }
        return false;
    }
    if (m->mId == 0x51a1a2e) {
        if (m->mpData) {
            if (mField10 == 0)
                Create();
            if (mpWin) {
                if (mpWin->IsShown() & 1)
                    mpWin->SetFlag(1, 0);
                mText = m->mpData;
                mNextTime = GetElapsedSeconds() + kDelayLong;
            }
            return true;
        }
        if (mpWin) {
            mpWin->SetFlag(1, 0);
            mNextTime = FLT_MAX;
        }
        return true;
    }
    return false;
}

void __fastcall FUN_00995ea0(void* self, void* pOut);   // base-class GetFormControlValue (ecx=this, edx=out)
void __fastcall WString_Assign(WString* self, const wchar_t* b, const wchar_t* e);   // eastl::basic_string::assign (0x423650)

struct IFontRef { virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3(); virtual void* GetFont(); };
struct IBaseObj { virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual unsigned GetHandle(); };
struct TabStopNode { TabStopNode* mpNext; TabStopNode* mpPrev; FormControl* mpValue; };
struct cXHTMLWin {   // the WinXHTML sub-object at +0x20c of the real window; offsets are from `this` here
    char pad0[0xa65c];
    unsigned mColorText;          // +0xa65c
    char pad1[0xa67c - 0xa660];
    IWinContainer* mpContainer;   // +0xa67c
    char pad2[0xa684 - 0xa680];
    IFontRef* mpFontBody;         // +0xa684
    char pad3[0xa698 - 0xa688];
    IFontRef* mpFontEdit;         // +0xa698
    char pad4[0xa6dc - 0xa69c];
    TabStopNode mTabStops;        // +0xa6dc list anchor (value unused)
    void CreateFormControl(FormControl* pCtl);                       // 0x00624080
    void GetFormControlValue(FormControl* pCtl, WString* pOut);      // 0x006248d0
};

// @ 0x006248d0
void cXHTMLWin::GetFormControlValue(FormControl* pCtl, WString* pOut)
{
    IQuery* q = pCtl->mpControl;
    char* pSel;
    if (!q || !(pSel = (char*)q->Query(0x4c058d5))) {
        FUN_00995ea0(this, pOut);
        return;
    }
    int idx = 0;
    LinkNode* pAnchor = &pCtl->mChildren;
    Element* pNode = pAnchor->mpNext ? (Element*)((char*)pAnchor->mpNext - 4) : 0;
    for (;;) {
        Element* pEnd = pAnchor ? (Element*)((char*)pAnchor - 4) : 0;
        if (pNode == pEnd)
            return;
        if (pNode->Type() == 1) {
            int cur = idx++;
            if (*(int*)(pSel + 0x8ac) == cur) {
                const wchar_t* v = pNode->GetAttrValue(gAttrValue);
                if (!v) {
                    pNode->GetText(pOut);
                    return;
                }
                const wchar_t* e = v;
                while (*e)
                    ++e;
                WString_Assign(pOut, v, v + (e - v));
                return;
            }
        }
        LinkNode* n = pNode->link.mpNext;
        pNode = n ? (Element*)((char*)n - 4) : 0;
    }
}

void __fastcall LinkListBegin(LinkNode* anchor, LinkNode** pOut);   // FUN_00623260 (thiscall in orig; helper)
extern const wchar_t gEmptyCaption[];   // L"" (0x13ec468)

// @ 0x00624080
void cXHTMLWin::CreateFormControl(FormControl* pCtl)
{
    WinXHTMLBase* pBase = (WinXHTMLBase*)((char*)this - 0x20c);
    if (pBase->ShouldCreate(pCtl)) {
        TabStopNode* pAnchor = &mTabStops;
        TabStopNode* pNode = new("Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) TabStopNode;
        if (&pNode->mpValue)
            pNode->mpValue = pCtl;
        pNode->mpNext = pAnchor;
        pNode->mpPrev = pAnchor->mpPrev;
        pAnchor->mpPrev->mpNext = pNode;
        pAnchor->mpPrev = pNode;
    }

    AutoRef<IWinObj> win;
    const wchar_t* pType = pCtl->GetAttrValue(gAttrType);
    const wchar_t* pValue = pCtl->GetAttrValue(gAttrValue);
    const wchar_t* pSize = pCtl->GetAttrValue(gAttrSize);
    const wchar_t* pReadonly = pCtl->GetAttrValue(gAttrReadonly);

    switch (pCtl->mType) {
    case 0x17:   // <input>
        if (!pType)
            break;
        if (_wcsicmp(pType, gValButton) == 0) {
            if (CreateXHTMLButton(win.AsPPTypeParam())) {
                if (pValue)
                    win.mp->SetCaption(pValue);
                else
                    win.mp->SetCaption(gEmptyCaption);
            }
            goto finalize;
        }
        if (_wcsicmp(pType, gValSubmit) == 0) {
            if (CreateXHTMLButton(win.AsPPTypeParam())) {
                if (pValue) {
                    win.mp->SetCaption(pValue);
                } else {
                    win.mp->SetCaption(L"Submit");
                    win.mp->SetCommand(0x344a710);
                }
            }
            goto finalize;
        }
        if (_wcsicmp(pType, gValReset) == 0) {
            if (CreateXHTMLButton(win.AsPPTypeParam())) {
                if (pValue) {
                    win.mp->SetCaption(pValue);
                } else {
                    win.mp->SetCaption(L"Reset");
                    win.mp->SetCommand(0x344a711);
                }
            }
            goto finalize;
        }
        if (_wcsicmp(pType, gValText) == 0) {
            void* pMem = FUN_009512d0(0x658, 8, "UTFWin/WinXHTML/WinTextEdit", FUN_009512c0());
            WinTextEditObj* pEdit = pMem ? ::new (pMem) WinTextEditObj() : 0;
            ITextCtl* pText = &pEdit->mText;
            win.Assign(pText->GetWindow());
            float margins[4] = { gTextMarginUnit, gTextMarginUnit, gTextMarginUnit, gTextMarginUnit };
            pText->SetMargins(margins);
            pEdit->SetMode(2);
            if (pValue)
                pEdit->mWin.SetCaption(pValue);
            if (pReadonly)
                pText->SetFlags(1, 1);
            if (pSize) {
                long n = wcstol(pSize, 0, 0);
                if (n)
                    pText->SetMaxLength(n);
            }
            win.mp->SetColorB(mColorText);
            win.mp->SetColorA(0xffccccee);
            goto finalize;
        }
        pBase->CreateFormControlBase(pCtl);
        break;

    case 0x18: {   // <select>
        const wchar_t* pMultiple = pCtl->GetAttrValue(gAttrMultiple);
        int rows = 1;
        if (pSize) {
            int n = (int)wcstol(pSize, 0, 0);
            rows = (n > 1) ? n : 1;
        }
        if (pMultiple || rows != 1) {
            pBase->CreateFormControlBase(pCtl);
            break;
        }
        {
            cSPUILayout layout;
            AutoRef<cSPUIPopupMenuWin> popup;
            unsigned layoutKey[3] = { 0x7b9fba30, 0x510a95b, 0x40464100 };
            if (layout.Init(layoutKey, 0, 0x5b598fa)) {
                win.Assign(layout.FindWindowByID(0, 1));
                if (win.mp)
                    popup.Assign(InterfaceCastPopup(&win));
            }
            layout.Shutdown(true);
            if (popup.mp) {
                popup.mp->mField8c8 = ((IBaseObj*)((char*)this - 0x208))->GetHandle();
                LinkNode* pAnchor = &pCtl->mChildren;
                LinkNode* it = pAnchor;
                LinkListBegin(pAnchor, &it);
                Element* pCur = (Element*)it;
                for (;;) {
                    Element* pEnd = pAnchor->mpNext ? (Element*)((char*)pAnchor->mpNext - 4) : 0;
                    if (pCur == pEnd)
                        break;
                    DomNode* pChild = pCur->link.mpPrev ? (DomNode*)((char*)pCur->link.mpPrev - 4) : 0;
                    if (pChild->Type() == 1) {
                        Element* pElem = pCur->link.mpPrev ? (Element*)((char*)pCur->link.mpPrev - 4) : 0;
                        if (pElem->mType == 0x19) {
                            WStringLocal text;
                            const wchar_t* pLabel = pElem->GetAttrValue(gAttrLabel);
                            if (!pLabel) {
                                pElem->GetText((WString*)&text);
                                pLabel = text.mpBegin;
                            }
                            unsigned itemKey[3] = { 0xa10d844a, 0x510a95b, 0x40464100 };
                            void* pItem = popup.mp->AddMenuItem(itemKey, 0, 0, 0);
                            if (pItem)
                                ((IWinObj*)((char*)pItem + 4))->SetCaption(pLabel);
                        }
                    }
                    pCur = pCur->link.mpPrev ? (Element*)((char*)pCur->link.mpPrev - 4) : 0;
                }
            }
        }
        goto finalize;
    }

    case 0x1a: {   // <textarea>
        const wchar_t* pDisabled = pCtl->GetAttrValue(gAttrDisabled);
        void* pMem = FUN_009512d0(0x658, 8, "UTFWin/WinXHTML/WinTextEdit", FUN_009512c0());
        WinTextEditObj* pEdit = pMem ? ::new (pMem) WinTextEditObj() : 0;
        ITextCtl* pText = &pEdit->mText;
        win.Assign(pText->GetWindow());
        float margins[4] = { gTextMarginUnit, gTextMarginUnit, gTextMarginUnit, gTextMarginUnit };
        pText->SetMargins(margins);
        pText->SetMaxLength(0xff);
        pEdit->SetMode(2);
        pText->SetAlign(2);
        if (pReadonly)
            pText->SetFlags(1, 1);
        win.mp->SetColorB(mColorText);
        win.mp->SetColorA(0xffffffff);
        if (mpFontEdit)
            pText->SetFont(1, mpFontEdit->GetFont());
        if (mpFontBody)
            pText->SetFont(0, mpFontBody->GetFont());
        pCtl->SetControl(win.mp);
        FormControlRef* pRef = new("FormControlRef", 0, 0, 0, 0) FormControlRef(pCtl);
        win.mp->SetProperty(0x344a0b7, pRef);
        if (pDisabled)
            win.mp->SetFlag(2, 0);
        goto finalize;
    }

    case 0x1b:   // <button>
        if (win.mp) {
            IWinObj* old = win.mp;
            win.mp = 0;
            old->Release();
        }
        if (CreateXHTMLButton(win.AsPPTypeParam())) {
            if (pValue) {
                win.mp->SetCaption(pValue);
            } else if (_wcsicmp(pType, gValSubmit) == 0) {
                win.mp->SetCaption(L"Submit");
                win.mp->SetCommand(0x344a710);
            } else if (_wcsicmp(pType, gValReset) == 0) {
                win.mp->SetCaption(L"Reset");
                win.mp->SetCommand(0x344a711);
            }
        }
        goto finalize;

    default:
        pBase->CreateFormControlBase(pCtl);
        break;
    }
    return;

finalize:
    if (win.mp) {
        pCtl->SetControl(win.mp);
        FormControlRef* pRef = new("UI/FormControlRef", 0, 0, 0, 0) FormControlRef(pCtl);
        win.mp->SetProperty(0x344a0b7, pRef);
        if (pCtl->GetAttrValue(gAttrDisabled))
            win.mp->SetFlag(2, 0);
        win.mp->SetFlag(1, 0);
        mpContainer->AddWindow(win.mp);
    }
}
