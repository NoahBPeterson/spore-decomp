// slice s005a4250 — SP::cSPColorSwatch and SP::cSPEditorColorPicker helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <math.h>
#include "types.h"

#define PV(n) virtual void pv##n();

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
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
        if (mpObject) {
            T* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
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
}  // namespace COM

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
    char pad[0x18];
};

}  // namespace EA

namespace EA {
namespace UTFWin {
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
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
    PV(60) PV(61) PV(62) PV(63) PV(64)
    virtual void pv65(void*);                     // +0x104
    virtual void pv66(void*);                     // +0x108
};
class IWinProc : public EA::COM::IUnknown32 {
public:
    virtual ~IWinProc() {}
};
}  // namespace UTFWin
}  // namespace EA

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
    if (mpBegin)
        mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
}
}  // namespace eastl

struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(uint32_t id, Property*& result);  // +0x24
};

namespace SP {
class cString {
public:
    cString();
    ~cString();
    void Load(uint32_t id, uint32_t arg, const wchar_t* text);  // 0x6b54b0
    const wchar_t* c_str();                                     // 0x6b5240
    char pad[0x14];
};

struct cSPColorRGB {
    float r, g, b;
    cSPColorRGB() {}
    cSPColorRGB(const cSPColorRGB& c) : r(c.r), g(c.g), b(c.b) {}
    bool operator!=(const cSPColorRGB& c) const { return r != c.r || g != c.g || b != c.b; }
};

extern cSPColorRGB gDefaultPaintColor;  // 0x0150f470 (12 bytes)

IWindow* WindowManagerView();
int PropertyManagerDummy();

}  // namespace SP

using SP::cSPColorRGB;

// ---- SP::cSPColorSwatch -----------------------------------------------------
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
    cSPColorSwatch();
    ~cSPColorSwatch();

    void SetArea(EA::RectT area, bool bStoreOriginal);   // 0x005a4500
    void SetColor(const cSPColorRGB& color);             // 0x005a45d0
    void CollapseExpansion();                            // 0x005a4630
    void AddTooltip(uint32_t id);                        // 0x005a4680
    void SetExpansionArea(bool b);                       // 0x005a4990
    void Init(cPropertyList* config, float r, float g, float b,
              float l, float t, float rr, float bb, uint32_t index,
              EA::COM::IUnknown32* owner);
    void MainColorSelected();                            // 0x005a5960
    void SetSelectedColor(EA::COM::IUnknown32* param);   // 0x005a4b80 (guessed)
    void GetExpansionColor(float* out, float a, float b, float c, int d, int e);
    void SubSelect(uint32_t param);                      // 0x005a5ae0
};

uint32_t ColorRGBToU32(const cSPColorRGB* c);  // 0x00458a40
void FUN_005a4500(cSPColorSwatch* self, float x, float y, float z, float w, bool b);
void FUN_005a45d0(cSPColorSwatch* self, const cSPColorRGB* c);
void FUN_005a4630(cSPColorSwatch* self);

// ---- SP::cSPEditorColorPicker ----------------------------------------------
class cSPEditorColorPicker : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
public:
    EA::AutoRefCount<cSPColorSwatch> mSelectedSwatch;  // +0xc
    IWindow* mWinRoot;          // +0x10
    float mRootWidth;           // +0x14
    float mRootHeight;          // +0x18
    cSPColorRGB mSelectedColor; // +0x1c
    int mUnknown28;             // +0x28
    int mSelectedIndex;         // +0x2c
    eastl::sp_vector<cSPColorSwatch*> mSwatches;  // +0x30
    int mNumColors;             // +0x44
    EA::AutoRefCount<cPropertyList> mColorPickerConfig;  // +0x48

    void GetSwatchArea(cSPColorRGB* out, int index, int unused);  // 0x005a4750
    void SetArea(EA::RectT area);                                 // 0x005a4800
    void SetPaletteColor(const cSPColorRGB& color);               // 0x005a4920
    void SetColor(const cSPColorRGB& color);                      // 0x005a4e20
    void SetDefault();                                            // 0x005a4fb0
    void SetSwatchIndex(int index);                               // 0x005a4fb0 alt
};

void FUN_005a4e20(cSPEditorColorPicker* self, const cSPColorRGB* c);
void FUN_005a4fb0(cSPEditorColorPicker* self);

// ============================================================================
// @ 0x005a4250  SP::cSPColorSwatch::GetExpansionColor
void cSPColorSwatch::GetExpansionColor(float* out, float a, float b, float c, int d, int e) {
    int num = 5;
    if (mColorPickerConfig) {
        Property* prop;
        if (mColorPickerConfig->GetProperty(0xd29675eb, prop) && prop->mType == 9) {
            int* p = prop->GetInt();
            num = *p;
        }
    }
    float col2 = 0.0f, col3 = 0.0f, col4 = 0.0f;
    if (mColorPickerConfig) {
        Property* prop;
        if (mColorPickerConfig->GetProperty(0x92fa6b4b, prop) && prop->mType == 0xd) {
            float* p = prop->GetFloat();
            col2 = *p;
        }
    }
    if (mColorPickerConfig) {
        Property* prop;
        if (mColorPickerConfig->GetProperty(0xd29675ee, prop) && prop->mType == 0xd) {
            float* p = prop->GetFloat();
            col3 = *p;
        }
    }
    if (mColorPickerConfig) {
        Property* prop;
        if (mColorPickerConfig->GetProperty(0xb2fa6d7b, prop) && prop->mType == 0xd) {
            float* p = prop->GetFloat();
            col4 = *p;
        }
    }
    if (mColorPickerConfig) {
        Property* prop;
        if (mColorPickerConfig->GetProperty(0xd29675ed, prop) && prop->mType == 0xd) {
            float* p = prop->GetFloat();
            /* stored to 0x1c slot; unused below */
            (void)p;
        }
    }
    if (a == b && a == c && b == c) {
        float t = (float)(num * d + e) / (float)(num * num - 1);
        out[0] = t;
        out[1] = t;
        out[2] = t;
        return;
    }
    (void)col2; (void)col3; (void)col4;
    out[0] = 0.0f; out[1] = 0.0f; out[2] = 0.0f;
}

// @ 0x005a4500
void cSPColorSwatch::SetArea(EA::RectT area, bool bStoreOriginal) {
    if (!mWinRoot)
        return;
    if (bStoreOriginal)
        mOriginalArea = area;
    EA::RectT child;
    child.left = 0.0f;
    child.top = 0.0f;
    child.right = area.Width();
    child.bottom = area.Height();
    mWinRoot->SetArea(area);
    if (mWinColor)
        mWinColor->SetArea(child);
    if (mWinFrame)
        mWinFrame->SetArea(child);
    if (mWinFrameGlow)
        mWinFrameGlow->SetArea(child);
    if (mWinShine)
        mWinShine->SetArea(child);
}

// @ 0x005a45d0
void cSPColorSwatch::SetColor(const cSPColorRGB& color) {
    mDisplayColor = color;
    if (mCustomColor)
        mBaseColor = color;
    if (mWinColor)
        mWinColor->pv23(ColorRGBToU32(&mDisplayColor));
}

// @ 0x005a4630
void cSPColorSwatch::CollapseExpansion() {
    int n = (int)(mExpansionSwatches.mpEnd - mExpansionSwatches.mpBegin);
    for (int i = 0; i < n; i++)
        mExpansionSwatches.mpBegin[i]->mRespondToInput = false;
    if (mWinExpansion)
        mWinExpansion->pv66((void*)this);
    if (mWinExpansion)
        mWinExpansion->SetFlag(1, false);
    mExpanded = false;
}

// @ 0x005a4680
void cSPColorSwatch::AddTooltip(uint32_t id) {
    IWindow* w = mWinRoot;
    if (!w)
        return;
    SP::cString str;
    str.Load(0x496bfb26, id, L"Color swatch Placeholder");
    /* Tooltip creation path elided for reading; behaviour: attach tooltip window. */
    (void)str;
}

// @ 0x005a4750
void cSPEditorColorPicker::GetSwatchArea(cSPColorRGB* out, int index, int) {
    float scale = 0.1f;
    if (mColorPickerConfig) {
        Property* prop;
        if (mColorPickerConfig->GetProperty(0x4120847, prop) && prop->mType == 0xd) {
            float* p = prop->GetFloat();
            scale = *p;
        }
    }
    float n = (float)mNumColors;
    float step = (mRootWidth / n) * scale;
    float w = (mRootWidth - (float)(mNumColors - 1) * step) / n;
    float x = (float)index * (w + step);
    out->r = x;
    out->g = 0.0f;
    out->b = x + w;
    /* 4th float written by caller convention: mRootHeight */
}

// @ 0x005a4800
void cSPEditorColorPicker::SetArea(EA::RectT area) {
    if (!mWinRoot)
        return;
    mWinRoot->pv27(&area);
    mRootWidth = area.Width();
    mRootHeight = area.Height();
    int n = (int)(mSwatches.mpEnd - mSwatches.mpBegin);
    for (int i = 0; i < n; i++) {
        float scale = 0.1f;
        bool flag = true;
        if (mColorPickerConfig) {
            Property* prop;
            if (mColorPickerConfig->GetProperty(0x4120847, prop) && prop->mType == 0xd) {
                float* p = prop->GetFloat();
                scale = *p;
            }
        }
        float fn = (float)mNumColors;
        float w = (mRootWidth / fn) * scale;
        float h = (mRootWidth - (float)(mNumColors - 1) * w) / fn;
        float x = (float)i * (h + w);
        mSwatches.mpBegin[i]->SetArea(EA::RectT(x, 0.0f, x + h, mRootHeight), flag);
    }
}

// @ 0x005a4920
void cSPEditorColorPicker::SetPaletteColor(const cSPColorRGB& color) {
    int i = mSelectedIndex;
    if (i > 0) {
        if (i < (int)mSwatches.size())
            mSwatches[i]->SetColor(color);
    }
}

// @ 0x005a4990
void cSPColorSwatch::SetExpansionArea(bool b) {
    float scale = 0.0f;
    if (mColorPickerConfig) {
        Property* prop;
        if (mColorPickerConfig->GetProperty(0xd29675ea, prop) && prop->mType == 0xd) {
            float* p = prop->GetFloat();
            scale = *p;
        }
    }
    (void)b; (void)scale;
}

// @ 0x005a4b80
void cSPColorSwatch::SetSelectedColor(EA::COM::IUnknown32*) {
    mBecomingOwner = true;
}

// @ 0x005a4e20
void cSPEditorColorPicker::SetColor(const cSPColorRGB& color) {
    mSelectedColor = color;
    if (mColorPickerConfig) {
        Property* prop;
        mColorPickerConfig->GetProperty(0xd29675eb, prop);
    }
    int n = (int)(mSwatches.mpEnd - mSwatches.mpBegin);
    for (int i = 0; i < n; i++) {
        cSPColorSwatch* s = mSwatches.mpBegin[i];
        float dz = s->mDisplayColor.b - color.b;
        float dy = s->mDisplayColor.g - color.g;
        float dx = s->mDisplayColor.r - color.r;
        if (sqrtf(dx * dx + (dy * dy + dz * dz)) < 0.01f) {
            mSelectedSwatch = s;
            return;
        }
    }
    int i = mUnknown28;
    if (i > 0 && i < n) {
        mSelectedSwatch = mSwatches.mpBegin[i];
        cSPColorSwatch* s = mSelectedSwatch;
        s->mDisplayColor = mSelectedColor;
        if (s->mCustomColor)
            s->mBaseColor = mSelectedColor;
        if (s->mWinColor)
            s->mWinColor->pv23(ColorRGBToU32(&s->mDisplayColor));
    }
}

// @ 0x005a4fb0
void cSPEditorColorPicker::SetDefault() {
    int i = mSelectedIndex;
    if (i > 0) {
        if (i < (int)mSwatches.size())
            mSelectedSwatch = mSwatches[i];
    }
}

// @ 0x005a5000
cSPColorSwatch::cSPColorSwatch()
    : mRespondToInput(false), mRolledOver(false), mMouseDown(false), mExpanded(false),
      mBecomingOwner(false), mCustomColor(false), mIsDefaultColor(false),
      mRollOverTimer(0.0f), mFadeTimer(0.0f), mMouseDownTimer(0.0f), mSelectedTimer(0.0f),
      mBaseColor(SP::gDefaultPaintColor), mDisplayColor(SP::gDefaultPaintColor),
      mTimerDoubleClick(4, 0),
      mCurrMouseDownTime(0), mLastMouseDownTime(0), mSwatchIndex(0xffffffff) {
}

// @ 0x005a5100
cSPColorSwatch::~cSPColorSwatch() {
}

// @ 0x005a51c0 (slice 39 starts) - placeholder to keep symbols local
