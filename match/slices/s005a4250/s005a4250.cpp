// slice s005a4250 — SP::cSPColorSwatch and SP::cSPEditorColorPicker helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <math.h>
#include "types.h"

#define PV(n) virtual void pv##n();

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t, void* p) { return p; }

struct Property {
    char pad[0x12];
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

class RectT { public:
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
    virtual void SetArea(const EA::RectT& area);  // +0x60 (a pointer is pushed)
    PV(25) PV(26)
    virtual void pv27(const EA::RectT* area);     // +0x6c
    PV(28) PV(29) PV(30)
    virtual void SetFlag(int flag, bool value);   // +0x7c
    PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
    virtual EA::Point ToClient(float, float);     // +0xc0
    virtual EA::Point ToScreen(float, float);     // +0xc4
    PV(50) PV(51) PV(52) PV(53)
    virtual void SelectChild(IWindow* child);     // +0xd8
    virtual void DeselectChild(IWindow* child);   // +0xdc
    PV(56) PV(57) PV(58) PV(59)
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

class cSPColorSwatch;

// What an owning color picker exposes: slot +0xc maps an id to the swatch it
// created for it.
class IColorSwatchHost : public EA::COM::IUnknown32 {
public:
    PV(2)
    virtual cSPColorSwatch* GetSwatch(uint32_t id);   // +0x0c
};

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
    const wchar_t* GetText();                                   // 0x6b55c0
    const wchar_t* c_str();                                     // 0x6b5240
    // Opaque storage; spelled as words (not an array) so a local cString whose
    // address is taken does not pull in a /GS cookie.
    uint32_t mField00;
    uint32_t mField04;
    uint32_t mField08;
    uint32_t mField0c;
    uint32_t mField10;
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

// The window manager singleton; only its main-window getter is used here.
class cWindowManager {
public:
    virtual int AddRef();                  // +0x00
    virtual IWindow* GetMainWindow();      // +0x04
};
cWindowManager* WindowManager();           // 0x67caa0

void RgbToHsl(uint8_t r, uint8_t g, uint8_t b,
              float* pHue, float* pLight, float* pSat);      // 0x918090
cSPColorRGB* HSLToRGB(cSPColorRGB* out, float h, float s, float l);  // 0x67fe30

}  // namespace SP

// Heap allocation behind the tooltip: FUN_009512c0 fetches the owning heap,
// FUN_009512d0 allocates a block from it (size, flags, name, heap).
void* FUN_009512c0();                                                    // 0x9512c0
void* FUN_009512d0(size_t size, int flags, const char* pName, void* pHeap);  // 0x9512d0

// Tooltip window procedure created for the swatch (definition lives in the
// tooltip slice; only AddRef/Release and the constructor are used here).
class cSPUITooltipWinProc {
public:
    virtual int AddRef();    // +0x00
    virtual int Release();   // +0x04
    cSPUITooltipWinProc(const wchar_t* pName, uint32_t id, const wchar_t* pText,
                        const EA::Point* pOffset, uint32_t arg, const wchar_t* pClass,
                        uint32_t flags);                     // 0x835e30
    char mData[0x64];
};

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
// @ 0x005a4250
void cSPColorSwatch::GetExpansionColor(float* out, float a, float b, float c, int d, int e) {
    // Grey swatches are spread over the expansion row, colored ones go through
    // HSV: sat = satBase ^ (satExp * (1 - d/steps)) and likewise for the value.
    Property* pProp;
    int steps = 5;
    float satExp = 1.0f;    // 0xb2fa6d7b
    float satBase = 1.0f;   // 0xd29675ed
    float lightExp = 1.0f;  // 0x92fa6b4b
    float lightBase = 1.0f; // 0xd29675ee

    if (mColorPickerConfig && mColorPickerConfig->GetProperty(0xd29675eb, pProp) && pProp->mType == 9)
        steps = *pProp->GetInt();
    if (mColorPickerConfig && mColorPickerConfig->GetProperty(0x92fa6b4b, pProp) && pProp->mType == 0xd)
        lightExp = *pProp->GetFloat();
    if (mColorPickerConfig && mColorPickerConfig->GetProperty(0xd29675ee, pProp) && pProp->mType == 0xd)
        lightBase = *pProp->GetFloat();
    if (mColorPickerConfig && mColorPickerConfig->GetProperty(0xb2fa6d7b, pProp) && pProp->mType == 0xd)
        satExp = *pProp->GetFloat();
    if (mColorPickerConfig && mColorPickerConfig->GetProperty(0xd29675ed, pProp) && pProp->mType == 0xd)
        satBase = *pProp->GetFloat();

    if (a == b && a == c && b == c) {
        float grey = (float)(steps * d + e) / (float)(steps * steps - 1);
        out[0] = grey;
        out[1] = grey;
        out[2] = grey;
        return;
    }

    float light;
    float sat;
    float hue;
    SP::RgbToHsl((uint8_t)(int)(mBaseColor.r * 255.0f),
                 (uint8_t)(int)(mBaseColor.g * 255.0f),
                 (uint8_t)(int)(mBaseColor.b * 255.0f),
                 &hue, &light, &sat);
    cSPColorRGB color;
    SP::HSLToRGB(&color, hue * 60.0f,
                 (float)pow((double)satBase, (double)satExp * (1.0 - (double)d / (double)steps)),
                 (float)pow((double)lightBase, (double)lightExp * (1.0 - (double)e / (double)steps)));
    out[0] = color.r;
    out[1] = color.g;
    out[2] = color.b;
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
    IWindow* pRoot = mWinRoot;
    EA::Point offset;       // where the tooltip pops up, relative to the swatch
    offset.x = 5.0f;
    offset.y = -9.0f;
    if (!pRoot)
        return;

    SP::cString text;
    text.Load(0x496bfb26, id, L"Color swatch Placeholder");

    cSPUITooltipWinProc* pTooltip = 0;
    void* pMemory = FUN_009512d0(0x68, 4, "UI/Tooltip", FUN_009512c0());
    if (pMemory != 0) {
        cSPUITooltipWinProc* pProc = new (pMemory) cSPUITooltipWinProc(
            L"Tooltips", 0x3754e6c, text.GetText(), &offset, 0, L"Tooltip", 0);
        if (pProc != 0) {
            pProc->AddRef();
            pTooltip = pProc;
        }
    }
    pRoot->pv65(pTooltip);
    if (pTooltip)
        pTooltip->Release();
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
    EA::RectT* area = (EA::RectT*)out;
    float step = (mRootWidth / (float)mNumColors) * scale;
    float remaining = mRootWidth - (float)(mNumColors - 1) * step;
    area->bottom = mRootHeight;
    float w = remaining / (float)mNumColors;
    float x = (float)index * (w + step);
    area->left = x;
    area->right = x + w;
    area->top = 0.0f;
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
void cSPColorSwatch::SetExpansionArea(bool bKeepInside) {
    Property* pProp;
    float scale = 0.0f;
    if (mColorPickerConfig && mColorPickerConfig->GetProperty(0xd29675ea, pProp) && pProp->mType == 0xd)
        scale = *pProp->GetFloat();

    // The expansion square is centred on the swatch and sized from the world
    // area of the root window.
    const EA::RectT& world = SP::WindowManager()->GetMainWindow()->GetRealArea();
    float span = (world.right - world.left) * 0.00125f;
    const EA::RectT& screen = SP::WindowManager()->GetMainWindow()->GetArea();
    const EA::RectT& root = mWinRoot->GetArea();
    float centerY = (root.bottom + root.top) * 0.5f;
    float centerX = (root.right + root.left) * 0.5f;
    IWindow* pParent = mWinRoot->GetParent();
    EA::Point client = pParent->ToClient(centerX, centerY);
    EA::Point pos = SP::WindowManager()->GetMainWindow()->ToScreen(client.x, client.y);

    float half = span * scale * 0.5f;
    float x = pos.x;
    if (bKeepInside && x + half > screen.right)
        x = (screen.right - half) - 1.0f;
    mWinExpansion->SetFlag(1, false);
    mWinExpansion->SetArea(EA::RectT(x - half, pos.y - half, x + half, pos.y + half));
}

// @ 0x005a4b80
void cSPColorSwatch::SetSelectedColor(EA::COM::IUnknown32* pOwner) {
    // Become the owner's current swatch: hand the parent window's selection
    // over and move this swatch onto the owner's square.
    mBecomingOwner = true;
    if (!mOwner)
        return;
    cSPColorSwatch* pOwnerSwatch =
        (cSPColorSwatch*)((IColorSwatchHost*)mOwner.mpObject)->GetSwatch(0x3b26ca5);
    if (!pOwnerSwatch)
        return;
    if (!pOwnerSwatch->mWinRoot)
        return;
    if (!pOwnerSwatch->mWinRoot->GetParent())
        return;
    if (!mWinRoot->GetParent())
        return;

    EA::RectT area = mWinRoot->GetRealArea();
    float x0 = mWinRoot->ToClient(area.left, area.top).x;
    float y0 = mWinRoot->ToClient(area.left, area.top).y;
    float x1 = mWinRoot->ToClient(area.right, area.bottom).x;
    float y1 = mWinRoot->ToClient(area.right, area.bottom).y;

    mWinRoot->GetParent()->DeselectChild(mWinRoot);
    pOwnerSwatch->mWinRoot->GetParent()->SelectChild(mWinRoot);

    SetArea(EA::RectT(mWinRoot->ToScreen(x0, y0).x,
                      mWinRoot->ToScreen(x0, y0).y,
                      mWinRoot->ToScreen(x1, y1).x,
                      mWinRoot->ToScreen(x1, y1).y),
            false);
    (void)pOwner;
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
