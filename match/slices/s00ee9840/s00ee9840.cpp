// Slice s00ee9840: one Spore UI control object -- a draggable "control point"
// (Entry) of a color-gradient editor, plus the message handler that drives the
// gradient-editing flow. The Entry owns a small layout with a slider window and
// a set of child windows, keeps a normalized position and an RGB color, and
// notifies the rest of the UI through the message server. (0xee9840-0xeea7b7)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <intrin.h>

struct Entry;
struct IWindow;
class cSPUILayout;

// ---------------------------------------------------------------- interfaces
// UTFWin::IWindow -- only the slots this slice reaches are named; dummy slots
// keep the offsets right. 0x0c AsInterface, 0x38 GetBox, 0x5c SetColor,
// 0x70 two-float position, 0x78 SetTextId, 0x7c two-int command,
// 0x104 Show, 0x108 Hide.
struct IHost;

struct IWindow {
    virtual void  AddRef() {}
    virtual void  Release() {}
    virtual void  Shutdown() {}
    virtual void* AsInterface(uint32_t id) { return 0; }       // 0x0c
    virtual IHost* GetHost() { return 0; }                     // 0x10
    virtual void  V5()  {} virtual void V6()  {} virtual void V7()  {} virtual void V8()  {}
    virtual void  V9()  {} virtual void V10() {} virtual void V11() {} virtual void V12() {}
    virtual void  V13() {}
    virtual float* GetBox() { return 0; }                      // 0x38
    virtual void  V15() {} virtual void V16() {} virtual void V17() {} virtual void V18() {}
    virtual void  V19() {} virtual void V20() {} virtual void V21() {} virtual void V22() {}
    virtual void  SetColor(uint32_t) {}                        // 0x5c
    virtual void  V24() {} virtual void V25() {} virtual void V26() {} virtual void V27() {}
    virtual void  SetPos2(float, float) {}                     // 0x70
    virtual void  V29() {}
    virtual void  SetTextId(uint32_t) {}                       // 0x78
    virtual void  Cmd2(int, int) {}                            // 0x7c
    virtual void  V32() {} virtual void V33() {} virtual void V34() {} virtual void V35() {}
    virtual void  V36() {} virtual void V37() {} virtual void V38() {} virtual void V39() {}
    virtual void  V40() {} virtual void V41() {} virtual void V42() {} virtual void V43() {}
    virtual void  V44() {} virtual void V45() {} virtual void V46() {} virtual void V47() {}
    virtual void  V48() {} virtual void V49() {} virtual void V50() {} virtual void V51() {}
    virtual void  V52() {} virtual void V53() {} virtual void V54() {} virtual void V55() {}
    virtual void  V56() {} virtual void V57() {} virtual void V58() {} virtual void V59() {}
    virtual void  V60() {} virtual void V61() {} virtual void V62() {} virtual void V63() {}
    virtual void  V64() {}
    virtual void  Show(void*) {}                               // 0x104
    virtual void  Hide(void*) {}                               // 0x108
};

// The object behind IWindow::GetHost (0xe8 slot takes the owning window).
struct IHost {
    void SetOwner(void* p);
};

// IWinButton: 0x20 returns the button state bitfield.
struct IWinButton {
    virtual void V00() {} virtual void V04() {} virtual void V08() {} virtual void V0c() {}
    virtual void V10() {} virtual void V14() {} virtual void V18() {} virtual void V1c() {}
    virtual uint32_t GetState() { return 0; }                  // 0x20
};

// cSPUILayout: 0x04 AddRef, 0x08 Release, then the plain member functions.
class cSPUILayout { public:
    virtual void V0() {}
    virtual void AddRef() {}                                   // 0x04
    virtual void Release() {}                                  // 0x08
    cSPUILayout* Ctor();                                       // 0x810000
    uint8_t  Init(const void* pKey, uint8_t a, uint32_t id);   // 0x8120d0
    uint8_t  SetParentWin(IWindow* pWin, uint8_t a, uint32_t id); // 0x8121b0
    IWindow* FindWindowByID(uint32_t id, uint8_t recurse);     // 0x8105b0
    void     Shutdown(uint32_t a);                             // 0x811ad0
};

// Ref-counted side object owned by an Entry (-0x3c/+0x40 hold an int vector).
struct IRefObj {
    virtual void V0() {}
    virtual void V4() {}
    virtual void AddRef() {}                                   // 0x08
    virtual void Release() {}                                  // 0x0c
    uint8_t pad0[0x38];
    void*   mBegin;                                            // +0x3c
    void*   mEnd;                                              // +0x40
};

// Message payload handed to the handlers.
struct Msg {
    void*    mObj;      // +0x00
    uint32_t mUnk04;    // +0x04
    uint32_t mType;     // +0x08
    uint32_t mId;       // +0x0c
    uint32_t mUnk10;    // +0x10
    uint32_t mUnk14;    // +0x14
};

// A UTFWin rect (only the two fields this slice reads are named).
struct RectF {
    uint8_t pad[0xc];
    float   mX;         // +0x0c
    float   mY;         // +0x10
};

struct Vec4 { float x, y, z, w; };

// A three-float color, passed by value to SetColor (12 bytes on the stack).
struct ColorRGB { float r, g, b; };

// -------------------------------------------------------------- audio system
struct IAudioSystem {
    virtual void V00() {} virtual void V04() {} virtual void V08() {} virtual void V0c() {}
    virtual void V10() {} virtual void V14() {} virtual void V18() {} virtual void V1c() {}
    virtual uint32_t GetCounter() { return 0; }                // 0x20
    virtual void V24() {} virtual void V28() {} virtual void V2c() {}
    virtual void V30() {} virtual void V34() {}
    virtual void F38(uint32_t) {}                              // 0x38
    virtual void V3c() {}
    virtual void F40(uint32_t, uint32_t) {}                    // 0x40
    virtual void V44() {} virtual void V48() {} virtual void V4c() {}
    virtual void V50() {} virtual void V54() {}
    virtual void F58() {}                                      // 0x58
};

// ---------------------------------------------------------------- callees
void*  GetActivePlanet();                    // 0x1021260
void*  GetActivePlanetRecord();              // 0x10212a0
void*  FUN_00b3d3b0();                       // 0xb3d3b0
void*  FUN_00ee7850(void* p);                // 0xee7850
void   FUN_00ee7cb0(void* a, void* b, uint32_t c); // 0xee7cb0
uint32_t FUN_00ee7810(Msg* msg);             // 0xee7810
void   FUN_00b9a5b0(void* pThis, int a);     // 0xb9a5b0
void   FUN_007a41a0(void* pThis);            // 0x7a41a0
uint8_t FUN_00c70c00(void* pThis);            // 0xc70c00
void*  FUN_008414c0(void* pThis);            // 0x8414c0
void   FUN_00c82f80(void* pThis);            // 0xc82f80
void   FUN_00b2bbe0(void* pThis);            // 0xb2bbe0
void*  GetRecorderState();                   // 0x435e90
void   KillSetiEffects(uint32_t id, void* sys); // 0x435ed0
void   SetGlobalProperty(uint32_t id, float v); // 0x5ca880
IAudioSystem* GetSystemAT();                 // 0xa206f0
void*  MessageServer();                      // 0x67dcc0
// MessageBasicRC<5>::SetIRefCount -- method of the allocated message object.
struct RefMsg {
    void SetIRefCount(int a, void* p);       // 0x5726e0
};
void   FUN_00efbbe0(int a, int b);             // 0xefbbe0
// Tutorials-check UI reached through the global UI manager; ToggleHint is the
// 0xefbbe0 thiscall tail called by SetColor.
struct TutorialsUI {
    void ToggleHint(int a, int b);              // 0xefbbe0
};
void*  EAAllocate(uint32_t size, const char* pTag, int a, int b, int c, int d); // 0xf473a0
uint32_t ColorRGBToU32(const float* pColor); // 0x458a40
Vec4*  FUN_00805fe0(Vec4* pOut, IWindow* pWin); // 0x805fe0
void   FUN_00804ed0(Vec4* a, Vec4* b);       // 0x804ed0
IWinButton* InterfaceCast_IWinButton(IWindow* p); // 0x5ca960
void*  GetSpeciesManager();                  // 0x401090

// The gradient-editor flow object the message handler belongs to (only the
// helpers it delegates to are named).
struct SpeciesMgr;
struct ProfileVector {
    void* mBegin;   // +0x00
    void* mEnd;     // +0x04
    void* mCap;     // +0x08
    void  Ctor(int a);                          // 0xb9a5b0
    void  Dtor();                               // 0x7a41a0
};
struct SpeciesMgr {
    int GetMatchingPlantProfiles(ProfileVector* v, int a, uint32_t b); // 0x4dfd50
};

// The current cSPUISpace-ish object reached through the global space manager.
struct Space {
    void F33BF0();                              // 0xf33bf0
    void F32410();                              // 0xf32410
    void F34560();                              // 0xf34560
};

// Sibling helpers of the message handler; the handler object sits at offset +8.
struct Host {
    void Fn8240(int a);                         // 0xee8240
    void Fn82C0(uint32_t a);                    // 0xee82c0
    void Fn83A0(void* p);                       // 0xee83a0
    void Fn8460(void* p);                       // 0xee8460
    void Fn95A0(void* p);                       // 0xee95a0
    void Fn9690(void* a, void* b);              // 0xee9690
};

// Message server: 0x14 is Send(id, msg, extra).
struct IMsgServer {
    virtual void V00() {} virtual void V04() {} virtual void V08() {} virtual void V0c() {}
    virtual void V10() {}
    virtual void Send(uint32_t id, void* msg, void* extra) {}  // 0x14
};

// --------------------------------------------------------------- vtable glue
struct Obj { void* mpVtbl; };

template <class T, int Off>
static inline void vcallv(T* p) {
    typedef void (T::*PMF)();
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; (p->*f)();
}
template <class T, int Off, class A>
static inline void vcallA(T* p, A a) {
    typedef void (T::*PMF)(A);
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; (p->*f)(a);
}
template <class T, int Off, class A, class B>
static inline void vcallAB(T* p, A a, B b) {
    typedef void (T::*PMF)(A, B);
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; (p->*f)(a, b);
}
template <class T, int Off, class A, class B, class C>
static inline void vcallABC(T* p, A a, B b, C c) {
    typedef void (T::*PMF)(A, B, C);
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; (p->*f)(a, b, c);
}
template <class R, class T, int Off, class A>
static inline R vcallRA(T* p, A a) {
    typedef R (T::*PMF)(A);
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; return (p->*f)(a);
}
template <class R, class T, int Off>
static inline R vcallR(T* p) {
    typedef R (T::*PMF)();
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; return (p->*f)();
}
// Same as vcallv, but the vtable pointer load is volatile so the compiler cannot
// forward a just-stored vtable constant into the call.
template <class T, int Off>
static inline void vcallv_vol(T* p) {
    typedef void (T::*PMF)();
    void* fn = ((void**)*(void* volatile**)p)[Off / 4];
    PMF f; *(void**)&f = fn; (p->*f)();
}

// The object embedded at offset +4 of an Entry (its RefCountVTemplate<int>
// half): 0x00 vtable, 0x04 refcount.
struct RefCountPart {
    void*  mpVtbl;      // +0x00
    int    mRefCount;   // +0x04
    void*  QueryInterface(uint32_t id);         // 0xeea780
};

// ---------------------------------------------------------------- Entry
// One control point of the gradient editor: primary vtable 0x148acb8,
// secondary (RefCountVTemplate<int>) 0x148aca8.
struct Entry {
    void**   mpVtbl;      // +0x00 -> 0x148acb8
    void*    mRefVtbl;    // +0x04 -> 0x148aca8
    int      mRefCount;   // +0x08
    IWindow* mOwner;      // +0x0c  (parent window passed to Init)
    IWindow* mWin0;       // +0x10
    IWindow* mWinA;       // +0x14
    IWindow* mWinB;       // +0x18
    IWindow* mWinSlider;  // +0x1c  (gradient handle)
    IWindow* mWinHandle;  // +0x20
    cSPUILayout* mLayout; // +0x24
    IRefObj* mPoints;     // +0x28
    uint8_t  mPressed;    // +0x2c
    float    mPos;        // +0x30  (normalized 0..1)
    ColorRGB mColor;      // +0x34
    uint8_t  mUnk40;      // +0x40
    uint8_t  mUnk41;      // +0x41
    float    mGrabX;      // +0x44
    float    mGrabY;      // +0x48
    float    mAnchorX;    // +0x4c
    uint8_t  mDragging;   // +0x50

    void  Ctor();                                        // 0xee9be0
    void  Dtor();                                        // 0xee9c70
    void  SetVisible(uint8_t visible);                   // 0xee9d00
    void  Update(void* a);                               // 0xee9de0
    void  Shutdown();                                    // 0xee9e50
    void  SetRect(int a, RectF* pRect, uint8_t flag);    // 0xee9e90
    void  TrackPoint(void* pWin, RectF* pPoint);         // 0xee9f10
    void  SetColor(ColorRGB color);                     // 0xeea190
    void  NotifyChanged();                               // 0xeea260
    void  OnClick(int a, int b);                         // 0xeea2f0
    uint8_t Init(IWindow* pOwner, float pos, float r, float g, float b,
                 IRefObj* pPoints);                      // 0xeea3c0
    uint8_t DoMessage(uint32_t msgId, Msg* msg);         // 0xeea6d0
};

int Entry_PosGreater(Entry* a, Entry* b);                // 0xeea760

// The message handler object (lives at offset +8 of the Host object).
struct MsgHandler {
    uint8_t Handle(IWindow* sender, Msg* msg);           // 0xee9840
};

// ================================================================= functions

// @ 0x00ee9840
uint8_t MsgHandler::Handle(IWindow* sender, Msg* msg)
{
    void* planet = GetActivePlanet();
    void* record = GetActivePlanetRecord();
    void* ctx = FUN_00b3d3b0();
    Space* space = *(Space**)(*(int*)0x16c7aa4 + 0x18);
    uint32_t type = msg->mType;
    uint8_t result = 0;

    switch (type) {
    case 0x1b:
    case 0x1c: {
        void* p = FUN_00ee7850(msg->mObj);
        if (p != 0) {
            ((Host*)((uint8_t*)this - 8))->Fn8460(p);
            return result;
        }
        break;
    }
    case 0x7a44749:
        if (msg->mId == 0x72bfdfd) {
            if (msg->mUnk14 != msg->mUnk10) {
                space->F34560();
                return 1;
            }
            space->F32410();
            return 1;
        }
        break;
    case 0x7a4489c:
        if (msg->mId == 0x72bfdfd) {
            space->F33BF0();
            return 1;
        }
        break;
    case 0x287259f6:
        switch (msg->mId) {
        case 0x73d54a0:
        case 0x4a1cb6d: {
            void* p = FUN_00ee7850(msg->mObj);
            ((Host*)((uint8_t*)this - 8))->Fn83A0(p);
            return result;
        }
        case 0x73272b0: {
            KillSetiEffects(0x13bed0aa, GetRecorderState());
            void* p = FUN_00ee7850(msg->mObj);
            ProfileVector vec;
            vec.Ctor(1);
            uint32_t a, b;
            uint32_t r = vcallRA<uint32_t, Obj, 0x1c>((Obj*)p, &b);
            (void)a;
            FUN_00ee7cb0(&a, &b, r);
            int n = ((SpeciesMgr*)GetSpeciesManager())
                        ->GetMatchingPlantProfiles(&vec, 1, FUN_00ee7810(msg));
            if (n == 1) {
                ((Host*)((uint8_t*)this - 8))->Fn9690(p, (char*)vec.mBegin + 0x504);
            }
            vec.Dtor();
            return result;
        }
        case 0x7b6b2cd: {
            IAudioSystem* at = GetSystemAT();
            uint32_t v = at ? at->GetCounter() : 0;
            KillSetiEffects(0x956eae88, (void*)v);
            void* p = FUN_00ee7850(msg->mObj);
            ((Host*)((uint8_t*)this - 8))->Fn95A0(p);
            return result;
        }
        case 0x16b1858d: {
            IWinButton* btn = InterfaceCast_IWinButton(sender);
            if (btn != 0) {
                KillSetiEffects(0xe76c9b4f, GetRecorderState());
                uint32_t v = btn->GetState();
                ((Host*)((uint8_t*)this - 8))->Fn8240((v >> 2) & 1);
            }
            break;
        }
        default:
            break;
        }
        {
            IAudioSystem* at = GetSystemAT();
            uint32_t v = at ? at->GetCounter() : 0;
            KillSetiEffects(0xe76c9b4f, (void*)v);
            ((Host*)((uint8_t*)this - 8))->Fn82C0(msg->mId);
            return result;
        }
    case 0xef00a884:
        if (msg->mId != 0x72bfdfd) break;
        if (msg->mObj != 0) {
            void* q = vcallRA<void*, Obj, 0x0c>((Obj*)msg->mObj, 0xf00a8a0);
            if (q != 0) {
                uint32_t n1 = vcallR<uint32_t, Obj, 0x20>((Obj*)q);
                uint32_t n2 = vcallR<uint32_t, Obj, 0x30>((Obj*)q);
                float f = (float)n1 / (float)n2;
                *(float*)((uint8_t*)record + 0x10c) = f;
                SetGlobalProperty(0xf04ff0cd, f);
                if ((uint8_t)FUN_00c70c00(planet)) {
                    void* x = FUN_008414c0(planet);
                    FUN_00c82f80(x);
                    FUN_00b2bbe0(ctx);
                }
            }
        }
        return 1;
    default:
        break;
    }
    return result;
}

// @ 0x00ee9be0
void Entry::Ctor()
{
    *(void* volatile*)((uint8_t*)this + 4) = (void*)0x13ec458;
    this->mRefCount = 0;
    this->mpVtbl = (void**)0x148acb8;
    this->mRefVtbl = (void*)0x148aca8;
    this->mOwner = 0;
    this->mWin0 = 0;
    this->mWinA = 0;
    this->mWinB = 0;
    this->mWinSlider = 0;
    this->mWinHandle = 0;
    this->mLayout = 0;
    this->mPoints = 0;
    this->mPressed = 0;
    this->mPos = 0.0f;
    _mm_store_ss(&this->mColor.r, _mm_load_ss((const float*)0x15ac834));
    _mm_store_ss(&this->mColor.g, _mm_load_ss((const float*)0x15ac838));
    _mm_store_ss(&this->mColor.b, _mm_load_ss((const float*)0x15ac83c));
    this->mUnk40 = 0;
    this->mUnk41 = 0;
    this->mAnchorX = 0.0f;
    this->mDragging = 0;
}

// @ 0x00ee9c70
void Entry::Dtor()
{
    *(void* volatile*)this = (void*)0x148acb8;
    *(void* volatile*)((uint8_t*)this + 4) = (void*)0x148aca8;
    IRefObj* pts = *(IRefObj* volatile*)&this->mPoints;
    if (pts != 0)  pts->Release();
    if (this->mLayout != 0)  ((cSPUILayout*)this->mLayout)->Release();
    if (this->mWinHandle != 0) ((IWindow*)this->mWinHandle)->Release();
    if (this->mWinSlider != 0) ((IWindow*)this->mWinSlider)->Release();
    if (this->mWinB != 0)      ((IWindow*)this->mWinB)->Release();
    if (this->mWinA != 0)      ((IWindow*)this->mWinA)->Release();
    if (this->mWin0 != 0)      ((IWindow*)this->mWin0)->Release();
    if (this->mOwner != 0)     ((IWindow*)this->mOwner)->Release();
    *(void* volatile*)this = (void*)0x13eb938;
    *(void* volatile*)((uint8_t*)this + 4) = (void*)0x13ec458;
}

// @ 0x00ee9d00
void Entry::SetVisible(uint8_t visible)
{
    if (this->mLayout == 0) return;
    IWindow* w0 = this->mWin0;
    if (w0 != 0) {
        if (visible) w0->Show(this);
        else         w0->Hide(this);
    }
    IWindow* wa = this->mWinA;
    if (wa != 0) {
        if (visible) {
            wa->Show(this);
            this->mWinA->Show(this->mPoints ? (uint8_t*)this->mPoints + 4 : 0);
        } else {
            wa->Hide(this);
            this->mWinA->Hide(this->mPoints ? (uint8_t*)this->mPoints + 4 : 0);
        }
    }
    IWindow* wb = this->mWinB;
    if (wb != 0) {
        if (visible) wb->Show(this->mPoints ? (uint8_t*)this->mPoints + 4 : 0);
        else         wb->Hide(this->mPoints ? (uint8_t*)this->mPoints + 4 : 0);
    }
}

// @ 0x00ee9de0
void Entry::Update(void* a)
{
    (void)a;
    IRefObj* pts = this->mPoints;
    if (pts != 0) {
        IWindow* win0 = this->mWin0;
        if (win0 != 0) {
            int n = (int)((uint8_t*)pts->mEnd - (uint8_t*)pts->mBegin) & ~3;
            vcallAB<IWindow, 0x7c>(win0, 1, n > 4);
        }
    }
    IWindow* slider = this->mWinSlider;
    if (slider != 0) {
        slider->SetColor(this->mDragging ? 0x99ffffffu : 0xffffffffu);
    }
    IWindow* handle = this->mWinHandle;
    if (handle != 0) {
        vcallAB<IWindow, 0x7c>(handle, 1, this->mDragging == 0);
    }
}

// @ 0x00ee9e50
void Entry::Shutdown()
{
    vcallA<Entry, 0x28>(this, 0);
    if (this->mOwner != 0) {
        IWindow* p = this->mOwner;
        this->mOwner = 0;
        p->Release();
    }
    if (this->mLayout != 0) this->mLayout->Shutdown(1u);
}

// @ 0x00ee9e90
void Entry::SetRect(int a, RectF* pRect, uint8_t flag)
{
    (void)a;
    this->mGrabX = 0.0f;
    this->mGrabY = 0.0f;
    if (flag) {
        this->mGrabX = pRect->mX;
        this->mGrabY = pRect->mY;
    }
    if (this->mWinB != 0) this->mWinB->SetTextId(0x747d67c);
    if (this->mWinA != 0) this->mWinA->SetTextId(0x747d67c);
    if (this->mWinSlider != 0) {
        if (this->mWinSlider->GetHost() != 0) {
            IHost* h = this->mWinSlider->GetHost();
            vcallA<IHost, 0xe8>(h, this->mWinSlider);
        }
    }
}

// @ 0x00ee9f10
void Entry::TrackPoint(void* pWin, RectF* pPoint)
{
    (void)pWin;
    if (this->mOwner == 0) return;

    float* boxOwner = this->mOwner->GetBox();
    float fTop = boxOwner[1];
    float fBottom = boxOwner[3];
    float fLeft = this->mWinSlider->GetBox()[0];
    float fTop2 = this->mWinSlider->GetBox()[1];

    float y = pPoint->mY - this->mGrabY + fTop2;
    if (0.0f > y) {
        y = 0.0f;
    } else {
        float* sb = this->mWinSlider->GetBox();
        float span = (fBottom - fTop) - (sb[3] - sb[1]);
        if (y > span) y = span;
    }

    Vec4 r;
    FUN_00805fe0(&r, this->mOwner);
    r.x = r.x - 10.0f;
    r.y = r.y - 30.0f;
    r.z = r.z + 10.0f;
    r.w = r.w + 30.0f;
    Vec4 pt;
    FUN_00804ed0(&pt, &r);

    bool outside = false;
    if (((int)((uint8_t*)((IRefObj*)this->mPoints)->mEnd -
               (uint8_t*)((IRefObj*)this->mPoints)->mBegin) & ~3) > 4) {
        bool inside = !(pt.x < r.x || pt.y < r.y || r.z <= pt.x || r.w <= pt.y);
        outside = !inside;
    }
    if (outside != (this->mDragging != 0)) {
        IAudioSystem* at = GetSystemAT();
        uint32_t v = at ? at->GetCounter() : 0;
        KillSetiEffects(0x9a810c9c, (void*)v);
        this->mDragging = outside ? 1 : 0;
    }
    if (this->mDragging != 0) {
        float x = pPoint->mX - this->mGrabX + fLeft;
        float yy = pPoint->mY - this->mGrabY + fTop2;
        this->mWinSlider->SetPos2(x, yy);
    } else {
        this->mWinSlider->SetPos2(this->mAnchorX, y);
    }
    float* sb2 = this->mWinSlider->GetBox();
    float newPos = y / ((fBottom - fTop) - (sb2[3] - sb2[1]));
    if (newPos != this->mPos) {
        this->mPos = newPos;
        SetGlobalProperty(0x272d708, pPoint->mY);
    }
}

// @ 0x00eea190
void Entry::SetColor(ColorRGB color)
{
    ColorRGB* mc = &this->mColor;
    if (color.r != mc->r || color.g != mc->g || color.b != mc->b) {
        *mc = color;
        IMsgServer* ms = (IMsgServer*)MessageServer();
        ms->Send(0xd69290d7, 0, 0);
    }
    TutorialsUI* ui = *(TutorialsUI**)(*(int*)0x16c7aa4 + 0xd4);
    ui->ToggleHint(0x96, 0x97);
    cSPUILayout* lay = this->mLayout;
    uint32_t c = ColorRGBToU32(&this->mColor.r);
    IWindow* w = lay->FindWindowByID(0x7e099a4, 1);
    if (w != 0) w->SetColor(c);
}

// @ 0x00eea260
void Entry::NotifyChanged()
{
    if (this->mWinA == 0) return;
    void* p = EAAllocate(0x40, (const char*)0x13f6b3c, 0, 0, 0, 0);
    if (p == 0) return;
    void* msg = p;
    *(int*)((uint8_t*)msg + 0x30) = 0;
    *(void**)msg = (void*)0x13eb90c;
    _InterlockedExchange((volatile long*)((uint8_t*)msg + 4), 0);
    *(void* volatile*)msg = (void*)0x13eb844;
    *(int* volatile*)((uint8_t*)msg + 0x38) = 0;
    _ReadWriteBarrier();
    vcallv_vol<Obj, 4>((Obj*)msg);
    *(int*)((uint8_t*)msg + 0x30) = 0x7e19b84;
    ((RefMsg*)msg)->SetIRefCount(0, this->mWinA);
    IMsgServer* ms = (IMsgServer*)MessageServer();
    ms->Send((uint32_t)*(int*)((uint8_t*)msg + 0x30), msg, 0);
    vcallv_vol<Obj, 8>((Obj*)msg);
}

// @ 0x00eea2f0
void Entry::OnClick(int a, int b)
{
    (void)a; (void)b;
    if (this->mWinB != 0) this->mWinB->SetTextId(0x747d67b);
    if (this->mWinA != 0) this->mWinA->SetTextId(0x747d67b);
    if (this->mDragging != 0) {
        this->mPressed = 1;
    } else {
        NotifyChanged();
        if (this->mWinA != 0) {
            void* q = this->mWinA->AsInterface(0x8ed27e7a);
            if (q != 0) vcallAB<Obj, 0x28>((Obj*)q, 4, 1);
        }
    }
    IAudioSystem* at = GetSystemAT();
    uint32_t v = at ? at->GetCounter() : 0;
    IAudioSystem* at2 = GetSystemAT();
    if (at2 != 0) {
        at2->F38(0x3475365);
        at2->F40(0x3475381, 0xe76c9b4f);
        at2->F40(0x3475385, v);
        at2->F58();
    }
}

// @ 0x00eea3c0
uint8_t Entry::Init(IWindow* pOwner, float pos, float r, float g, float b,
                    IRefObj* pPoints)
{
    if (pOwner != this->mOwner) {
        if (pOwner != 0) pOwner->AddRef();
        IWindow* old = this->mOwner;
        this->mOwner = pOwner;
        if (old != 0) old->Release();
    }
    if (pPoints != this->mPoints) {
        if (pPoints != 0) pPoints->AddRef();
        IRefObj* oldp = this->mPoints;
        this->mPoints = pPoints;
        if (oldp != 0) oldp->Release();
    }
    this->mColor.r = r;
    this->mColor.g = g;
    this->mPressed = 0;
    this->mPos = pos;
    this->mColor.b = b;

    if (this->mOwner != 0) {
        void* p = EAAllocate(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
        cSPUILayout* lay = p ? ((cSPUILayout*)p)->Ctor() : 0;
        if (lay != this->mLayout) {
            if (lay != 0) lay->AddRef();
            cSPUILayout* oldl = this->mLayout;
            this->mLayout = lay;
            if (oldl != 0) oldl->Release();
        }
        if (!this->mLayout->Init((const void*)0x15ac864, 0, 0x5b598fa)) {
            this->mLayout->Shutdown(1u);
            if (this->mLayout != 0) {
                cSPUILayout* q = this->mLayout;
                this->mLayout = 0;
                q->Release();
            }
            return 0;
        }
        this->mLayout->SetParentWin(this->mOwner, 1, 0x5b598fa);

        IWindow* t;
        t = this->mLayout->FindWindowByID(0x568ed1c3, 1);
        if (t != this->mWinSlider) {
            if (t != 0) t->AddRef();
            IWindow* old = this->mWinSlider;
            this->mWinSlider = t;
            if (old != 0) old->Release();
        }
        t = this->mLayout->FindWindowByID(0xf68ed165, 1);
        if (t != this->mWin0) {
            if (t != 0) t->AddRef();
            IWindow* old = this->mWin0;
            this->mWin0 = t;
            if (old != 0) old->Release();
        }
        t = this->mLayout->FindWindowByID(0x7e099a3, 1);
        if (t != this->mWinA) {
            if (t != 0) t->AddRef();
            IWindow* old = this->mWinA;
            this->mWinA = t;
            if (old != 0) old->Release();
        }
        t = this->mLayout->FindWindowByID(0xf68ed164, 1);
        if (t != this->mWinB) {
            if (t != 0) t->AddRef();
            IWindow* old = this->mWinB;
            this->mWinB = t;
            if (old != 0) old->Release();
        }
        t = this->mLayout->FindWindowByID(0x7e1e057, 1);
        if (t != this->mWinHandle) {
            if (t != 0) t->AddRef();
            IWindow* old = this->mWinHandle;
            this->mWinHandle = t;
            if (old != 0) old->Release();
        }

        if (this->mWinB != 0) this->mWinB->SetTextId(0x747d67b);
        if (this->mWinA != 0) this->mWinA->SetTextId(0x747d67b);

        uint32_t c = ColorRGBToU32(&this->mColor.r);
        IWindow* w = this->mLayout->FindWindowByID(0x7e099a4, 1);
        if (w != 0) w->SetColor(c);
    }

    if (this->mOwner != 0 && this->mWinSlider != 0) {
        float* sb = this->mWinSlider->GetBox();
        float hSlider = sb[3] - sb[1];
        float* ob = this->mOwner->GetBox();
        float hOwner = ob[3] - ob[1];
        float* sb2 = this->mWinSlider->GetBox();
        this->mWinSlider->SetPos2(sb2[0], (hOwner - hSlider) * this->mPos);
        this->mAnchorX = this->mWinSlider->GetBox()[0];
    }
    NotifyChanged();
    return 1;
}

// @ 0x00eea6d0
uint8_t Entry::DoMessage(uint32_t msgId, Msg* msg)
{
    (void)msgId;
    if (msg->mType != 0x287259f6) return 0;
    if (msg->mId == 0xf68ed165) {
        int n = (int)((uint8_t*)((IRefObj*)this->mPoints)->mEnd -
                      (uint8_t*)((IRefObj*)this->mPoints)->mBegin) & ~3;
        if (n > 4) {
            IAudioSystem* at = GetSystemAT();
            uint32_t v = at ? at->GetCounter() : 0;
            KillSetiEffects(0xe76c9b4f, (void*)v);
            IMsgServer* ms = (IMsgServer*)MessageServer();
            ms->Send(0x7e1ea71, 0, 0);
            this->mPressed = 1;
        }
        return 1;
    }
    if (msg->mId == 0x7e099a3) {
        NotifyChanged();
    }
    return 0;
}

// @ 0x00eea760
int Entry_PosGreater(Entry* a, Entry* b)
{
    return b->mPos > a->mPos;
}

// @ 0x00eea780
void* RefCountPart::QueryInterface(uint32_t id)
{
    switch (id) {
    case 0x968dcff4:
        return (uint8_t*)this - 4;
    case 0xee3f516e:
    case 0x2f009dd0:
        return ((uint8_t*)this - 4) != 0 ? (void*)this : 0;
    default:
        return 0;
    }
}
