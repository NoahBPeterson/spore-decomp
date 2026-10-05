// slice s005a51c0 — SP::cSPColorSwatch::Init and the cSPColorSwatch message/selection
// helpers plus a small cEditorResource-derived class ctor/dtor.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <math.h>
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
    char pad[0x18];
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
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
    virtual EA::Point ToClient(float, float);     // +0xc0
    virtual EA::Point ToScreen(float, float);     // +0xc4
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57)
    virtual void pv58(void*);                     // +0xe8
    PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
    virtual void pv65(void*);                     // +0x104
    virtual void pv66(void*);                     // +0x108
};
class IWinProc : public EA::COM::IUnknown32 {
public:
    virtual ~IWinProc() {}
};
}}

using EA::UTFWin::IWindow;

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
    cSPColorRGB mBaseColor;     // +0x24
    cSPColorRGB mDisplayColor;  // +0x30
    EA::RectT mOriginalArea;    // +0x3c
    EA::AutoRefCount<IWindow> mWinFrame;      // +0x4c
    EA::AutoRefCount<IWindow> mWinFrameGlow;  // +0x50
    EA::AutoRefCount<IWindow> mWinShine;      // +0x54
    EA::AutoRefCount<IWindow> mWinColor;      // +0x58
    EA::AutoRefCount<IWindow> mWinRoot;       // +0x5c
    EA::AutoRefCount<IWindow> mWinExpansion;  // +0x60
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

    void SetColor(const cSPColorRGB& color);        // 0x005a45d0
    void CollapseExpansion();                       // 0x005a4630
    void SetExpansionArea(bool b);                  // 0x005a4990
    void SetSelectedColor(void* param);             // 0x005a4b80
    __declspec(noinline) void MainColorSelected();  // 0x005a5960
    void SetFromSwatch(cSPColorSwatch* other);      // 0x005a5ae0
    int  DoMessage(uint32_t wParam, void* message); // 0x005a5b70
    void Cleanup();                                 // 0x005a5db0
    void Init(cPropertyList* config, float r, float g, float b,
              float l, float t, float rr, float bb, uint32_t index,
              void* owner, EA::COM::IUnknown32* param11);
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
// @ 0x005a51c0  SP::cSPColorSwatch::Init  (abridged: window construction path)
void cSPColorSwatch::Init(cPropertyList* config, float r, float g, float b,
                          float l, float t, float rr, float bb, uint32_t index,
                          void* owner, EA::COM::IUnknown32* param11) {
    mOriginalArea.left = l; mOriginalArea.top = t; mOriginalArea.right = rr; mOriginalArea.bottom = bb;
    mBaseColor.r = r; mDisplayColor.r = r;
    mBaseColor.g = g; mDisplayColor.g = g;
    mBaseColor.b = b; mDisplayColor.b = b;
    mOwner = (EA::COM::IUnknown32*)param11;
    mColorPickerConfig = config;
    mSwatchIndex = 0xffffffff;
    mExpansionIndex = 0xffffffff;
    (void)index; (void)owner;
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
