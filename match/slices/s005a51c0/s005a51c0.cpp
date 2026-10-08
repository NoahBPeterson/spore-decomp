// slice s005a51c0 — SP::cSPColorSwatch::Init and the cSPColorSwatch message/selection
// helpers plus a small cEditorResource-derived class ctor/dtor.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <math.h>
#include <intrin.h>
#include "types.h"

#define PV(n) virtual void pv##n();

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }

struct Property {
    char pad[0x10];
    uint32_t mFlags;             // +0x10
    unsigned short mType;        // +0x12
    int* GetInt();               // 0x0041e990
    uint32_t* GetUInt();         // 0x0041ea00
    float* GetFloat();           // 0x0041ea70
    bool* GetBool();             // 0x0041e920
};

union LARGE_INTEGER_ { struct { unsigned long LowPart; long HighPart; }; __int64 QuadPart; };
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER_*);
struct IDrawable;

namespace EA {
template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
    T*& AsOutParam() {
        if (mpObject) { T* const p = mpObject; mpObject = 0; p->Release(); }
        return mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// operator=(T*) is called out of line (0x00b5f950, COMDAT-folded with AutoRefCount<IWinText>)
template <typename T>
class AutoRefCountOOL : public AutoRefCount<T> {
public:
    __declspec(noinline) AutoRefCountOOL& operator=(T* pObject);
};

template <typename T>
class RefCountVTemplate {
public:
    RefCountVTemplate() : mnRefCount(0) {}
    virtual ~RefCountVTemplate() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release() {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) { mnRefCount = 1; delete this; return 0; }
        return mnRefCount;
    }
    T mnRefCount;
};

namespace COM {
class IUnknown32 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
struct RectT {
    float left, top, right, bottom;
    RectT() {}
    RectT(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b) {}
    float Width() const { return right - left; }
    float Height() const { return bottom - top; }
};
struct Point { float x, y; };
class Stopwatch {
public:
    Stopwatch(int, int);
    uint32_t GetElapsedTime();
    void Start() {
        if (mStartTime == 0) {
            if (mUnits == 1) {
                mStartTime = __rdtsc();
            } else {
                LARGE_INTEGER_ t;
                QueryPerformanceCounter(&t);
                mStartTime = t.QuadPart;
            }
        }
    }
    unsigned __int64 mStartTime;   // +0x00
    uint32_t pad8[2];
    uint32_t mUnits;               // +0x10
    uint32_t pad14;
};
}

namespace EA { namespace UTFWin {
class IWindow {
public:
    virtual int AddRef();                         // +0x00
    virtual int Release();                        // +0x04
    PV(2) PV(3)
    virtual IWindow* GetParent();                 // +0x10
    PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual uint32_t GetFlags();                  // +0x28
    PV(11) PV(12)
    virtual const EA::RectT& GetRealArea();       // +0x34
    virtual const EA::RectT& GetArea();           // +0x38
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    virtual void pv23(uint32_t color);            // +0x5c
    virtual void SetArea(EA::RectT area);         // +0x60
    PV(25) PV(26)
    virtual void pv27(const EA::RectT* area);     // +0x6c
    PV(28) PV(29) PV(30)
    virtual void SetFlag(int flag, bool value);   // +0x7c
    PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41)
    virtual ::IDrawable* GetDrawable();           // +0xa8
    virtual void SetFillColor(uint32_t color);    // +0xac
    PV(44) PV(45) PV(46) PV(47)
    virtual EA::Point ToClient(float, float);     // +0xc0
    virtual EA::Point ToScreen(float, float);     // +0xc4
    PV(50) PV(51) PV(52) PV(53)
    virtual void AddWindow(IWindow*);             // +0xd8
    PV(55) PV(56) PV(57)
    virtual void pv58(void*);                     // +0xe8
    PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
    virtual void AddWinProc(struct IWinProc*);    // +0x104
    virtual void pv66(void*);                     // +0x108
};
class IWinProc : public EA::COM::IUnknown32 {
public:
    virtual ~IWinProc() {}
};
}}

using EA::UTFWin::IWindow;
using EA::UTFWin::IWinProc;

struct IDrawableCast {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual void SetMode(int mode);               // +0x28
};
struct IDrawable {
    virtual int AddRef();
    virtual int Release();
    PV(2)
    virtual IDrawableCast* Cast(uint32_t id);     // +0x0c
};
struct Key3 {
    uint32_t mInstance, mType, mGroup;
    Key3() {}
    Key3(uint32_t instance, uint32_t type, uint32_t group) { mType = type; mGroup = group; mInstance = instance; }
};
struct Pt2 { float x, y; Pt2(float a, float b) : x(a), y(b) {} };
namespace SPUIHelpers {
IWindow* CreateImageWindow(const Key3& image, Pt2 pos, IWindow* parent);   // 0x00807880 (cdecl)
}
struct cPropertyList;
bool GetPropertyAsKeyInstance(const cPropertyList* list, uint32_t id, uint32_t* out);   // 0x006a12a0 (cdecl)
void* __cdecl FUN_009512c0();
void* __cdecl FUN_009512d0(unsigned size, unsigned align, const char* name, void* alloc);
struct WindowRaw { WindowRaw* Ctor(); };            // 0x00962a10 EA::UTFWin::Window::Window
struct LayoutMgr { IWindow* GetWorldMainWindow(); };   // 0x00810620
LayoutMgr* __stdcall GetLayoutManager(unsigned id);   // 0x00805070
struct EffectSub {
    PV(0) PV(1) PV(2) PV(3)
    virtual IWinProc* GetWinProc();               // +0x10
    PV(5)
    virtual void SetDuration(float);              // +0x18
    PV(7)
    virtual void SetFlagA(bool);                  // +0x20
    PV(9)
    virtual void SetRange(float, float);          // +0x28
    PV(11)
    virtual void SetFlagB(bool);                  // +0x30
};
struct InflateEffect {
    virtual int AddRef();
    virtual int Release();
    uint32_t pad[1];
    EffectSub mCtl;                               // +0x0c
    uint32_t pad2[(0x60 - 0x10) / 4];
    EffectSub mCtl2;                              // +0x60
    InflateEffect* Ctor();                        // 0x0097e690
};
struct FadeEffect {
    virtual int AddRef();
    virtual int Release();
    uint32_t pad[1];
    EffectSub mCtl;                               // +0x0c
    FadeEffect* Ctor();                           // 0x0096f060
};
struct UnkCast { virtual int AddRef(); virtual int Release(); PV(2) virtual void* Cast(uint32_t id); };

namespace eastl {
struct sp_vector_allocator {
    uint32_t mData[2];
    sp_vector_allocator() {}
    void deallocate(void* p, size_t) { if (((uint32_t*)p)[-1]) operator delete[]((char*)p); }
};
template <typename T>
class sp_vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector();
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T& operator[](unsigned int i) { return mpBegin[i]; }
};
template <typename T>
__declspec(noinline) sp_vector<T>::~sp_vector() {
    if (mpBegin) mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
}
}

struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(uint32_t id, Property*& result);  // +0x24
};

namespace SP {
struct cSPColorRGB {
    float r, g, b;
    cSPColorRGB() {}
    cSPColorRGB(const cSPColorRGB& c) : r(c.r), g(c.g), b(c.b) {}
    bool operator!=(const cSPColorRGB& c) const { return r != c.r || g != c.g || b != c.b; }
};
extern cSPColorRGB gDefaultPaintColor;  // 0x0150f470
class cString {
public:
    cString();
    ~cString();
    void Load(uint32_t id, uint32_t arg, const wchar_t* text);
    const wchar_t* c_str();
    char pad[0x14];
};
}

using SP::cSPColorRGB;

struct ColorPOD { float r, g, b; };
uint32_t ColorRGBToU32(const cSPColorRGB* c);  // 0x00458a40

class cSPColorSwatch : public EA::UTFWin::IWinProc, public EA::RefCountVTemplate<int> {
public:
    bool mRespondToInput;   // +0xc
    bool mRolledOver;       // +0xd
    bool mMouseDown;        // +0xe
    bool mExpanded;         // +0xf
    bool mBecomingOwner;    // +0x10
    bool mCustomColor;      // +0x11
    bool mIsDefaultColor;   // +0x12
    char pad13[1];
    float mRollOverTimer;   // +0x14
    float mFadeTimer;       // +0x18
    float mMouseDownTimer;  // +0x1c
    float mSelectedTimer;   // +0x20
    ColorPOD mBaseColor;     // +0x24
    ColorPOD mDisplayColor;  // +0x30
    EA::RectT mOriginalArea;    // +0x3c
    EA::AutoRefCount<IWindow> mWinFrame;      // +0x4c
    EA::AutoRefCount<IWindow> mWinFrameGlow;  // +0x50
    EA::AutoRefCount<IWindow> mWinShine;      // +0x54
    EA::AutoRefCount<IWindow> mWinColor;      // +0x58
    EA::AutoRefCount<IWindow> mWinRoot;       // +0x5c
    EA::AutoRefCountOOL<IWindow> mWinExpansion;  // +0x60
    EA::AutoRefCount<EA::COM::IUnknown32> mOwner;  // +0x64
    eastl::sp_vector<EA::AutoRefCount<cSPColorSwatch> > mExpansionSwatches;  // +0x68
    EA::AutoRefCount<cPropertyList> mColorPickerConfig;  // +0x7c
    EA::Stopwatch mTimerDoubleClick;  // +0x80
    uint32_t mCurrMouseDownTime;      // +0x98
    uint32_t mLastMouseDownTime;      // +0x9c
    uint32_t mSwatchIndex;            // +0xa0
    uint32_t mExpansionIndex;         // +0xa4

    virtual int AddRef() { return EA::RefCountVTemplate<int>::AddRef(); }
    virtual int Release() { return EA::RefCountVTemplate<int>::Release(); }

    void SetColor(const ColorPOD& color);        // 0x005a45d0
    void CollapseExpansion();                       // 0x005a4630
    void SetExpansionArea(bool b);                  // 0x005a4990
    void SetSelectedColor(void* param);             // 0x005a4b80
    __declspec(noinline) void MainColorSelected();  // 0x005a5960
    void SetFromSwatch(cSPColorSwatch* other);      // 0x005a5ae0
    int  DoMessage(uint32_t wParam, void* message); // 0x005a5b70
    void Cleanup();                                 // 0x005a5db0
    void SetArea(EA::RectT area, bool b);          // 0x005a4500
    void Init(cPropertyList* config, ColorPOD color,
              float l, float t, float rr, float bb,
              IWindow* parent, EA::COM::IUnknown32* owner);
};

// class cX: the cEditorResource/ContentValidationSummarizer-derived class at 0x5a5a50.
namespace SP {
class cContentValidationSummarizer {
public:
    virtual int v0();
    virtual int v1();
};
class cEditorResource : public cContentValidationSummarizer {
public:
    cEditorResource() : mField4(0) {}
    virtual int v0();
    virtual int v1();
    int mField4;   // +0x4
};
}
class cXBase { public: virtual int v0(); };
class cX : public SP::cEditorResource, public cXBase {
public:
    EA::AutoRefCount<EA::COM::IUnknown32> mPtrC;  // +0xc
    void* mPtr10;     // +0x10
    float mFloat14;   // +0x14
    float mFloat18;   // +0x18
    cSPColorRGB mColor1c;  // +0x1c
    uint32_t mInt28;  // +0x28
    uint32_t mInt2c;  // +0x2c
    eastl::sp_vector<void*> mVec30;  // +0x30
    void* mPtr44;     // +0x44
    EA::AutoRefCount<EA::COM::IUnknown32> mPtr48;  // +0x48
    void* mPtr4c;     // +0x4c
    cX();
    virtual ~cX();
};

// ============================================================================
// @ 0x005a51c0  SP::cSPColorSwatch::Init
void cSPColorSwatch::Init(cPropertyList* config, ColorPOD color,
                          float l, float t, float rr, float bb,
                          IWindow* parent, EA::COM::IUnknown32* owner) {
    mTimerDoubleClick.Start();
    mOriginalArea.left = l; mOriginalArea.top = t; mOriginalArea.right = rr; mOriginalArea.bottom = bb;
    mBaseColor = color;
    mDisplayColor = color;
    mOwner = owner;
    mColorPickerConfig = config;
    mSwatchIndex = 0xffffffff;
    mExpansionIndex = 0xffffffff;

    uint32_t keyGroup = 0, key1 = 0, key2 = 0, key3 = 0, key4 = 0, key5 = 0;
    bool hasExpansion = true;
    GetPropertyAsKeyInstance(mColorPickerConfig, 0xd29675e0, &keyGroup);
    GetPropertyAsKeyInstance(mColorPickerConfig, 0xd29675e1, &key1);
    GetPropertyAsKeyInstance(mColorPickerConfig, 0xd29675e2, &key2);
    GetPropertyAsKeyInstance(mColorPickerConfig, 0xd29675e3, &key3);
    GetPropertyAsKeyInstance(mColorPickerConfig, 0xd29675e4, &key4);
    GetPropertyAsKeyInstance(mColorPickerConfig, 0xd29675e5, &key5);
    if (mIsDefaultColor) {
        GetPropertyAsKeyInstance(mColorPickerConfig, 0x5adcd71, &key1);
        GetPropertyAsKeyInstance(mColorPickerConfig, 0x5adcd72, &key2);
        GetPropertyAsKeyInstance(mColorPickerConfig, 0x5adcd73, &key3);
        GetPropertyAsKeyInstance(mColorPickerConfig, 0x5adcd6f, &key5);
    }
    {
        Property* prop;
        if (mColorPickerConfig && mColorPickerConfig->GetProperty(0x55aa173, prop) && prop->mType == 1)
            hasExpansion = *prop->GetBool();
    }

    WindowRaw* wr = 0;
    void* mem = FUN_009512d0(0x20c, 4, "UI/Window", FUN_009512c0());
    IWindow* root = 0;
    if (mem) {
        wr = ((WindowRaw*)mem)->Ctor();
        if (wr) root = (IWindow*)((char*)wr + 4);
    }
    mWinRoot = root;
    if (mWinRoot) {
        parent->AddWindow(mWinRoot);
        parent->pv58(mWinRoot);
        mWinRoot->pv23(0xffffffff);
        mWinRoot->SetFillColor(0xffffff);
        mWinRoot->AddWinProc(this);

        mWinColor = SPUIHelpers::CreateImageWindow(Key3(key5, 0x2f7d0004, keyGroup), Pt2(0.0f, 0.0f), mWinRoot);
        if (mWinColor) {
            mWinColor->pv23(ColorRGBToU32((const cSPColorRGB*)&mBaseColor));
            IDrawableCast* d = mWinColor->GetDrawable()->Cast(0xef3c47cf);
            if (d) d->SetMode(2);
            mWinColor->SetFlag(2, false);
            mWinColor->SetFlag(0x10, true);
        }
        mWinFrame = SPUIHelpers::CreateImageWindow(Key3(key1, 0x2f7d0004, keyGroup), Pt2(0.0f, 0.0f), mWinRoot);
        if (mWinFrame) {
            IDrawableCast* d = mWinFrame->GetDrawable()->Cast(0xef3c47cf);
            if (d) d->SetMode(2);
            mWinFrame->SetFlag(2, false);
            mWinFrame->SetFlag(0x10, true);
        }
        mWinFrameGlow = SPUIHelpers::CreateImageWindow(Key3(key2, 0x2f7d0004, keyGroup), Pt2(0.0f, 0.0f), mWinRoot);
        if (mWinFrameGlow) {
            IDrawableCast* d = mWinFrameGlow->GetDrawable()->Cast(0xef3c47cf);
            if (d) d->SetMode(2);
            mWinFrameGlow->pv23(0);
            mWinFrameGlow->SetFlag(2, false);
            mWinFrameGlow->SetFlag(0x10, true);
        }
        mWinShine = SPUIHelpers::CreateImageWindow(Key3(key3, 0x2f7d0004, keyGroup), Pt2(0.0f, 0.0f), mWinRoot);
        if (mWinShine) {
            mWinShine->SetFlag(2, false);
            mWinShine->SetFlag(0x10, true);
        }
        SetArea(mOriginalArea, false);

        if (hasExpansion && mOwner && ((UnkCast*)(EA::COM::IUnknown32*)mOwner)->Cast(0xd0d22119)) {
            IWindow* world = GetLayoutManager(0x5b598fa)->GetWorldMainWindow();
            mWinExpansion = SPUIHelpers::CreateImageWindow(Key3(key4, 0x2f7d0004, keyGroup), Pt2(0.0f, 0.0f), world);
            if (mWinExpansion) {
                SetExpansionArea(false);
                InflateEffect* inflate = 0;
                {
                    void* m = FUN_009512d0(0xb8, 8, "UI/InflateEffect", FUN_009512c0());
                    if (m) inflate = ((InflateEffect*)m)->Ctor();
                }
                if (inflate) {
                    inflate->AddRef();
                    inflate->mCtl.SetDuration(0.3f);
                    inflate->mCtl.SetRange(0.5f, 0.5f);
                    inflate->mCtl.SetFlagB(true);
                    inflate->mCtl.SetFlagA(true);
                    inflate->mCtl2.SetDuration(0.0001f);
                    mWinExpansion->AddWinProc(inflate->mCtl.GetWinProc());
                }
                FadeEffect* fade = 0;
                {
                    void* m = FUN_009512d0(0x60, 8, "UI/FadeEffect", FUN_009512c0());
                    if (m) fade = ((FadeEffect*)m)->Ctor();
                }
                if (fade) {
                    fade->AddRef();
                    fade->mCtl.SetDuration(0.3f);
                    fade->mCtl.SetRange(0.0f, 0.0f);
                    fade->mCtl.SetFlagB(false);
                    fade->mCtl.SetFlagA(true);
                    mWinExpansion->AddWinProc(fade->mCtl.GetWinProc());
                    fade->Release();
                }
                if (inflate) inflate->Release();
            }
        }
    }
    mRespondToInput = true;
}

// @ 0x005a5960  SP::cSPColorSwatch::MainColorSelected  (complex message path: partial, external)

// @ 0x005a5a50
cX::cX() : mPtr10(0), mFloat14(0.0f), mFloat18(0.0f),
           mColor1c(SP::gDefaultPaintColor), mInt28(0xffffffff), mInt2c(0xffffffff),
           mPtr44(0), mPtr4c(0) {}

// @ 0x005a5b10
cX::~cX() {}

// @ 0x005a5ae0  SP::cSPColorSwatch::SetFromSwatch
void cSPColorSwatch::SetFromSwatch(cSPColorSwatch* other) {
    if (other) {
        SetColor(other->mBaseColor);
        CollapseExpansion();
        MainColorSelected();
    }
}

// @ 0x005a5b70  SP::cSPColorSwatch::DoMessage (abridged behaviour)
int cSPColorSwatch::DoMessage(uint32_t, void*) {
    return 0;
}

// @ 0x005a5db0  SP::cSPColorSwatch::Cleanup
void cSPColorSwatch::Cleanup() {
    int n = (int)(mExpansionSwatches.mpEnd - mExpansionSwatches.mpBegin);
    for (int i = 0; i < n; i++)
        mExpansionSwatches.mpBegin[i]->Cleanup();
    if (mWinRoot) {
        mWinRoot->pv58(0);
        IWindow* p = mWinRoot->GetParent();
        if (p) {
            if (mWinExpansion)
                mWinExpansion->GetParent()->pv58(mWinExpansion);
            mWinRoot->GetParent()->pv58(mWinRoot);
        }
    }
    mWinRoot = (IWindow*)0;
    mWinShine = (IWindow*)0;
    mWinFrame = (IWindow*)0;
    mWinFrameGlow = (IWindow*)0;
    mWinExpansion = (IWindow*)0;
    mExpansionSwatches.mpEnd = mExpansionSwatches.mpBegin;
}
