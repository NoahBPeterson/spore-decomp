// slice s005a5ec0 — SP::cSPEditorColorPicker (Init/Update/Clear) and cSPColorSwatch::Update.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <string.h>
#include <math.h>
#pragma intrinsic(sqrt)
#include "types.h"

#define PV(n) virtual void pv##n();

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t, void* p) { return p; }

struct Property {
    char pad[0x12];
    unsigned short mType;      // +0x12: 1 = bool, 9 = int, 0xd = float
    int* GetInt();             // 0x0041E990
    uint32_t* GetUInt();
    float* GetFloat();         // 0x0041EA70
    bool* GetBool();           // 0x0041E920
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
    AutoRefCount& operator=(T* p) { if (p != mpObject) { T* t = mpObject; if (p) p->AddRef(); mpObject = p; if (t) t->Release(); } return *this; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template <typename T>
class RefCountVTemplate {
public:
    RefCountVTemplate() : mnRefCount(0) {}
    virtual ~RefCountVTemplate() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release() { int n = (*(volatile int*)&mnRefCount += -1); if (n == 0) { mnRefCount = 1; delete this; return 0; } return mnRefCount; }
    T mnRefCount;
};
namespace COM {
class IUnknown32 { public: virtual int AddRef() = 0; virtual int Release() = 0; };
}
struct RectT { float left, top, right, bottom; RectT() {} float Width() const { return right - left; } float Height() const { return bottom - top; } };
}

struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(uint32_t id, Property*& result);
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
    T* erase(T* first, T* last);
    void DoInsertSlow(T* pos, void* value);   // 0x006650C0 / 0x00Exxxx (out of line)
};
template <typename T>
__declspec(noinline) sp_vector<T>::~sp_vector() {
    if (mpBegin) mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
}
template <typename T>
__declspec(noinline) T* sp_vector<T>::erase(T* first, T* last) {
    memmove(first, last, (char*)mpEnd - (char*)last);
    mpEnd -= (last - first);
    return first;
}
}

struct cSPColorRGB { float r, g, b; cSPColorRGB() {} cSPColorRGB(const cSPColorRGB& c) : r(c.r), g(c.g), b(c.b) {} };

struct IWindow {
    virtual int AddRef();   // slot 0 (+0x0)
    virtual int Release();   // slot 1 (+0x4)
    virtual void v2();   // slot 2 (+0x8)
    virtual void v3();   // slot 3 (+0xc)
    virtual IWindow* GetParent();   // slot 4 (+0x10)
    virtual void v5();   // slot 5 (+0x14)
    virtual void v6();   // slot 6 (+0x18)
    virtual void v7();   // slot 7 (+0x1c)
    virtual void v8();   // slot 8 (+0x20)
    virtual void v9();   // slot 9 (+0x24)
    virtual void v10();   // slot 10 (+0x28)
    virtual void v11();   // slot 11 (+0x2c)
    virtual void v12();   // slot 12 (+0x30)
    virtual const EA::RectT* GetArea();   // slot 13 (+0x34)
    virtual const EA::RectT* GetRealArea();   // slot 14 (+0x38)
    virtual void v15();   // slot 15 (+0x3c)
    virtual void v16();   // slot 16 (+0x40)
    virtual void v17();   // slot 17 (+0x44)
    virtual void v18();   // slot 18 (+0x48)
    virtual void v19();   // slot 19 (+0x4c)
    virtual void v20();   // slot 20 (+0x50)
    virtual void v21();   // slot 21 (+0x54)
    virtual void v22();   // slot 22 (+0x58)
    virtual void SetFillColor(uint32_t c);   // slot 23 (+0x5c)
    virtual void v24();   // slot 24 (+0x60)
    virtual void v25();   // slot 25 (+0x64)
    virtual void v26();   // slot 26 (+0x68)
    virtual void v27();   // slot 27 (+0x6c)
    virtual void v28();   // slot 28 (+0x70)
    virtual void v29();   // slot 29 (+0x74)
    virtual void v30();   // slot 30 (+0x78)
    virtual void SetFlag(int flag, int enable);   // slot 31 (+0x7c)
    virtual void v32();   // slot 32 (+0x80)
    virtual void v33();   // slot 33 (+0x84)
    virtual void v34();   // slot 34 (+0x88)
    virtual void v35();   // slot 35 (+0x8c)
    virtual void v36();   // slot 36 (+0x90)
    virtual void v37();   // slot 37 (+0x94)
    virtual void v38();   // slot 38 (+0x98)
    virtual void v39();   // slot 39 (+0x9c)
    virtual void v40();   // slot 40 (+0xa0)
    virtual void v41();   // slot 41 (+0xa4)
    virtual void v42();   // slot 42 (+0xa8)
    virtual void SetShadeColor(uint32_t c);   // slot 43 (+0xac)
    virtual void v44();   // slot 44 (+0xb0)
    virtual void v45();   // slot 45 (+0xb4)
    virtual void v46();   // slot 46 (+0xb8)
    virtual void v47();   // slot 47 (+0xbc)
    virtual void v48();   // slot 48 (+0xc0)
    virtual void v49();   // slot 49 (+0xc4)
    virtual void v50();   // slot 50 (+0xc8)
    virtual void v51();   // slot 51 (+0xcc)
    virtual void v52();   // slot 52 (+0xd0)
    virtual void v53();   // slot 53 (+0xd4)
    virtual void v54();   // slot 54 (+0xd8)
    virtual void v55();   // slot 55 (+0xdc)
    virtual void v56();   // slot 56 (+0xe0)
    virtual void v57();   // slot 57 (+0xe4)
    virtual void AddWindow(IWindow* w);   // slot 58 (+0xe8)
    virtual void v59();   // slot 59 (+0xec)
    virtual void v60();   // slot 60 (+0xf0)
    virtual void v61();   // slot 61 (+0xf4)
    virtual void v62();   // slot 62 (+0xf8)
    virtual void v63();   // slot 63 (+0xfc)
    virtual void v64();   // slot 64 (+0x100)
    virtual void AddWinProc(void* proc);   // slot 65 (+0x104)
};

struct OwnerObject {                         // swatch owner (AutoRefCount<IUnknown32>)
    virtual int AddRef();
    virtual int Release();
    virtual void* v2();
    virtual void* Cast(uint32_t typeId);     // slot 3 (+0xC)
};

struct cSPColorRGBA { float r, g, b, a; };
extern cSPColorRGB gWhiteColor;               // 0x0150F470 {1,1,1}
uint32_t __cdecl ColorRGBAToU32(const cSPColorRGBA* c);   // 0x004580C0
cSPColorRGB* __cdecl HSLToRGB(cSPColorRGB* out, float h, float s, float l);   // 0x0067FE30
void __cdecl FUN_004a88d0(uint32_t id);                   // 0x004A88D0
struct BoundingBoxLite {
    void Renderer();   // 0x0080D710
};
BoundingBoxLite* __cdecl AddBoundingBox(IWindow* win, int a, int b);   // 0x0067CAD0
bool __cdecl GetPropertyArray(cPropertyList* list, uint32_t id, int* pCount, cSPColorRGB** pData); // 0x006A0A70

struct PropertyManager {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void p10();
    virtual bool GetPropertyList(uint32_t id, uint32_t group, cPropertyList** out);  // slot 11 (+0x2C)
};
PropertyManager* __cdecl GetPropertyManager();             // 0x0067DE30

class cSPColorSwatch;
typedef eastl::sp_vector<cSPColorRGB> ColorVector;

struct SwatchRefVector {                       // vector<AutoRefCount<cSPColorSwatch>, sp_vector_allocator>
    cSPColorSwatch** mpBegin;
    cSPColorSwatch** mpEnd;
    cSPColorSwatch** mpCapacity;
    eastl::sp_vector_allocator mAllocator;
    void erase(cSPColorSwatch** first, cSPColorSwatch** last); // 0x00E25BD0
    void DoInsertSlow(cSPColorSwatch** pos, void* value);                       // 0x006650C0
};

class cSPEditorColorPicker;

class cSPColorSwatch {
public:
    virtual int AddRef();                      // slot 0
    virtual int Release();                     // slot 1
    uint32_t pad4;
    int mnRefCount;                            // +8
    bool mRespondToInput;                      // +0xc
    bool mRolledOver;                          // +0xd
    bool mMouseDown;                           // +0xe
    bool mExpanded;                            // +0xf
    bool mBecomingOwner;                       // +0x10
    bool mCustomColor;                         // +0x11
    bool mIsDefaultColor;                      // +0x12
    char pad13;
    float mRollOverTimer;                      // +0x14
    float mFadeTimer;                          // +0x18
    float mMouseDownTimer;                     // +0x1c
    float mSelectedTimer;                      // +0x20
    cSPColorRGB mBaseColor;                    // +0x24
    cSPColorRGB mDisplayColor;                 // +0x30
    EA::RectT mOriginalArea;                   // +0x3c
    EA::AutoRefCount<IWindow> mWinFrame;       // +0x4c
    EA::AutoRefCount<IWindow> mWinFrameGlow;   // +0x50
    EA::AutoRefCount<IWindow> mWinShine;       // +0x54
    EA::AutoRefCount<IWindow> mWinColor;       // +0x58
    EA::AutoRefCount<IWindow> mWinRoot;        // +0x5c
    EA::AutoRefCount<IWindow> mWinExpansion;   // +0x60
    EA::AutoRefCount<OwnerObject> mOwner;      // +0x64
    SwatchRefVector mExpansionSwatches;        // +0x68
    EA::AutoRefCount<cPropertyList> mColorPickerConfig;  // +0x7c
    char mTimerDoubleClick[0x18];              // +0x80
    unsigned int mCurrMouseDownTime;           // +0x98
    unsigned int mLastMouseDownTime;           // +0x9c
    unsigned int mSwatchIndex;                 // +0xa0
    unsigned int mExpansionIndex;              // +0xa4

    cSPColorSwatch();                          // 0x005a5000
    void Cleanup();                            // 0x005a5db0
    void Init(cPropertyList* config, cSPColorRGB color, EA::RectT area, IWindow* root,
              void* owner);     // 0x005a51c0
    void SetArea(EA::RectT area, int flag);    // 0x005a4500
    void SetExpansionArea(int flag);           // 0x005a4990
    void AddTooltip(uint32_t id);              // 0x005a4680
    cSPColorRGB GetExpansionColor(cSPColorRGB base, int i, int j);   // 0x005a4250
    void Update(int deltaTime, bool selected); // 0x005a63d0
};

class cSPEditorColorPicker : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
public:
    EA::AutoRefCount<cSPColorSwatch> mSelectedSwatch;  // +0xc
    IWindow* mWinRoot;          // +0x10
    float mRootWidth;           // +0x14
    float mRootHeight;          // +0x18
    cSPColorRGB mSelectedColor; // +0x1c
    int mCustomSwatchIndex;     // +0x28
    int mDefaultSwatchIndex;    // +0x2c
    eastl::sp_vector<cSPColorSwatch*> mSwatches;  // +0x30
    int mNumColors;             // +0x44
    EA::AutoRefCount<cPropertyList> mColorPickerConfig;  // +0x48
    int mUserData;              // +0x4c

    bool Init(IWindow* winRoot, uint32_t configId, int userData, const ColorVector* colors); // 0x005a5ec0
    void Clear();                      // 0x005a6390
    void Update(int deltaTime);        // 0x005a6db0
    EA::RectT GetSwatchArea(int index, int flag);   // 0x005a4750
};

// ============================================================================
static inline void PushSwatch(eastl::sp_vector<cSPColorSwatch*>& v, cSPColorSwatch* sw,
                              EA::AutoRefCount<cSPColorSwatch>& ref)
{
    cSPColorSwatch** pos = v.mpEnd;
    if (pos < v.mpCapacity) {
        v.mpEnd = pos + 1;
        if (pos) {
            *pos = sw;
            sw->AddRef();
        }
    } else {
        v.DoInsertSlow(pos, &ref);
    }
}

// @ 0x005a5ec0  SP::cSPEditorColorPicker::Init
bool cSPEditorColorPicker::Init(IWindow* winRoot, uint32_t configId, int userData,
                                const ColorVector* colors) {
    mUserData = userData;
    mWinRoot = winRoot;
    mSelectedSwatch = 0;
    PropertyManager* pm = GetPropertyManager();
    mColorPickerConfig = 0;
    pm->GetPropertyList(configId, 0x97097e36, &mColorPickerConfig.mpObject);

    if (mWinRoot && mColorPickerConfig) {
        mWinRoot->SetFillColor(0xffffffff);
        mWinRoot->SetShadeColor(0xffffff);
        mWinRoot->SetFlag(1, 0);
        const EA::RectT* area = mWinRoot->GetRealArea();
        mRootWidth = area->right - area->left;
        mRootHeight = area->bottom - area->top;

        mNumColors = 10;
        cSPColorRGB* colorData = 0;
        if (colors) {
            mNumColors = colors->size();
            colorData = colors->mpBegin;
        } else {
            GetPropertyArray(mColorPickerConfig, 0xd29675ec, &mNumColors, &colorData);
        }

        bool hasCustom = true;
        bool hasDefault = true;
        Property* prop;
        if (mColorPickerConfig && mColorPickerConfig->GetProperty(0x55a847e, prop) && prop->mType == 1)
            hasCustom = *prop->GetBool();
        if (mColorPickerConfig && mColorPickerConfig->GetProperty(0x55a847f, prop) && prop->mType == 1)
            hasDefault = *prop->GetBool();

        int n = mNumColors;
        if (hasCustom) {
            mCustomSwatchIndex = mNumColors;
            mNumColors++;
        }
        if (hasDefault) {
            mDefaultSwatchIndex = mNumColors;
            mNumColors++;
        }

        for (int i = 0; i < n; i++) {
            cSPColorSwatch* sw = new("UI", 0, 0, 0, 0) cSPColorSwatch();
            EA::AutoRefCount<cSPColorSwatch> ref(sw);
            if (sw) {
                const cSPColorRGB* c;
                cSPColorRGB tmp;
                if (colorData)
                    c = &colorData[i];
                else if (i == 0)
                    c = &gWhiteColor;
                else
                    c = HSLToRGB(&tmp, (float)i / (float)(mNumColors - 1) * 360.0f, 1.0f, 1.0f);
                cSPColorRGB color = *c;
                sw->Init(mColorPickerConfig, color, GetSwatchArea(i, 0), mWinRoot,
                         (EA::COM::IUnknown32*)this);
                sw->mSwatchIndex = i;
                sw->AddTooltip(0x5bf125f);
                PushSwatch(mSwatches, sw, ref);
            }
        }

        if (hasCustom) {
            cSPColorSwatch* sw = new("UI", 0, 0, 0, 0) cSPColorSwatch();
            EA::AutoRefCount<cSPColorSwatch> ref(sw);
            if (sw) {
                sw->mCustomColor = true;
                cSPColorRGB color;
                color.r = 0.5f;
                color.g = 0.5f;
                color.b = 0.5f;
                sw->Init(mColorPickerConfig, color, GetSwatchArea(mCustomSwatchIndex, 0), mWinRoot,
                         (EA::COM::IUnknown32*)this);
                sw->mSwatchIndex = mCustomSwatchIndex;
                sw->AddTooltip(0x5bf125f);
                PushSwatch(mSwatches, sw, ref);
            }
        }

        if (hasDefault) {
            cSPColorSwatch* sw = new("UI", 0, 0, 0, 0) cSPColorSwatch();
            EA::AutoRefCount<cSPColorSwatch> ref(sw);
            if (sw) {
                sw->mIsDefaultColor = true;
                cSPColorRGB color;
                color.r = 1.0f;
                color.g = 0.94f;
                color.b = 0.83f;
                sw->Init(mColorPickerConfig, color, GetSwatchArea(mDefaultSwatchIndex, 1), mWinRoot,
                         (EA::COM::IUnknown32*)this);
                sw->mSwatchIndex = mDefaultSwatchIndex;
                PushSwatch(mSwatches, sw, ref);
            }
        }
    }
    return true;
}

// @ 0x005a6390  SP::cSPEditorColorPicker::Clear
void cSPEditorColorPicker::Clear() {
    eastl::sp_vector<cSPColorSwatch*>& v = mSwatches;
    int n = (int)(v.mpEnd - v.mpBegin);
    for (int i = 0; i < n; i++)
        v.mpBegin[i]->Cleanup();
    v.erase(v.mpBegin, v.mpEnd);
}


inline float Maxf(float a, float b) { return a > b ? a : b; }
inline float Minf(float a, float b) { return a < b ? a : b; }

// Reads one typed property of the swatch's config list into `out` when present.
#define SWATCH_PROP_INT(id, out) \
    if (mColorPickerConfig) { \
        Property* p; \
        if (mColorPickerConfig->GetProperty(id, p) && p->mType == 9) out = *p->GetInt(); \
    }
#define SWATCH_PROP_FLOAT(id, out) \
    if (mColorPickerConfig) { \
        Property* p; \
        if (mColorPickerConfig->GetProperty(id, p) && p->mType == 0xd) out = *p->GetFloat(); \
    }

// @ 0x005a63d0  SP::cSPColorSwatch::Update
void cSPColorSwatch::Update(int deltaTime, bool selected) {
    float mouseDownTime = 0.25f;
    float rollOverTime = 0.25f;
    float selectedTime = 0.25f;
    float rollOverGrow = 12.0f;
    float ownerFadeScale = 3.0f;
    float expansionGap = 0.1f;
    int expansionDim = 5;
    int doubleClickTime = 400;
    float fadeMax = 0.5f;

    float dtMs = (float)(unsigned int)deltaTime;
    float dt = dtMs * 0.001f;

    SWATCH_PROP_INT(0x41c3428, doubleClickTime)
    SWATCH_PROP_INT(0xd29675eb, expansionDim)
    SWATCH_PROP_FLOAT(0xd29675e6, rollOverTime)
    SWATCH_PROP_FLOAT(0xd29675e7, mouseDownTime)
    SWATCH_PROP_FLOAT(0xd297bfc6, selectedTime)
    SWATCH_PROP_FLOAT(0xd29675e8, rollOverGrow)
    SWATCH_PROP_FLOAT(0xd29675ef, ownerFadeScale)
    SWATCH_PROP_FLOAT(0x4120847, expansionGap)

    mSelectedTimer = Minf(Maxf((selected ? 1.0f : -1.0f) * dt + mSelectedTimer, 0.0f), selectedTime);
    mRollOverTimer = Minf(Maxf((mRolledOver ? 1.0f : -1.0f) * dt + mRollOverTimer, 0.0f), rollOverTime);
    mMouseDownTimer = Minf(Maxf((mMouseDown ? 1.0f : -1.0f) * dt + mMouseDownTimer, 0.0f), mouseDownTime);
    mFadeTimer = Minf(Maxf((mExpanded ? 1.0f : -1.0f) * dt + mFadeTimer, 0.0f), fadeMax);

    if (mWinRoot && mRespondToInput) {
        float grow = (rollOverGrow / rollOverTime) * mRollOverTimer;
        EA::RectT r;
        r.left = mOriginalArea.left - grow;
        r.top = mOriginalArea.top - grow;
        r.right = mOriginalArea.right + grow;
        r.bottom = mOriginalArea.bottom + grow;
        SetArea(r, 0);
        cSPColorRGBA c;
        c.r = gWhiteColor.r;
        c.g = gWhiteColor.g;
        c.b = gWhiteColor.b;
        c.a = 1.0f - mFadeTimer * 2.0f;
        mWinRoot->SetFillColor(ColorRGBAToU32(&c));
    }

    if (mWinFrameGlow) {
        cSPColorRGBA c;
        c.r = gWhiteColor.r;
        c.g = gWhiteColor.g;
        c.b = gWhiteColor.b;
        if (mSelectedTimer > 0.0f)
            c.a = mSelectedTimer / selectedTime;
        else
            c.a = mMouseDownTimer / mouseDownTime;
        mWinFrameGlow->SetFillColor(ColorRGBAToU32(&c));
    }

    bool doubleClick = false;
    if (mCurrMouseDownTime != 0 && mLastMouseDownTime != 0)
        doubleClick = (mCurrMouseDownTime - mLastMouseDownTime) < (unsigned int)doubleClickTime;

    if (!mIsDefaultColor && (mMouseDownTimer == mouseDownTime || (doubleClick && !mExpanded))) {
        mMouseDownTimer = 0.0f;
        mMouseDown = false;
        mRolledOver = false;
        mCurrMouseDownTime = 0;
        mLastMouseDownTime = 0;
        if (mWinExpansion) {
            int count = (int)(mExpansionSwatches.mpEnd - mExpansionSwatches.mpBegin);
            for (int k = 0; k < count; k++)
                mExpansionSwatches.mpBegin[k]->Cleanup();
            mExpansionSwatches.erase(mExpansionSwatches.mpBegin, mExpansionSwatches.mpEnd);
            SetExpansionArea(1);
            FUN_004a88d0(0xa9e589e1);
            mWinExpansion->SetFlag(1, 1);
            mWinExpansion->SetFlag(1, 1);
            mWinExpansion->GetParent()->AddWindow(mWinExpansion);

            const EA::RectT* area = mWinExpansion->GetArea();
            float cell = (area->right - area->left) / (float)expansionDim;
            float pad = cell * expansionGap;
            float inner = (1.0f - expansionGap) * cell;

            int base = 0;
            for (int i = 0; i < expansionDim; i++) {
                for (int j = 0; j < expansionDim; j++) {
                    cSPColorSwatch* sw = new("UI", 0, 0, 0, 0) cSPColorSwatch();
                    if (sw) {
                        float x0 = (float)i * cell + pad * 0.5f;
                        float y0 = (float)j * cell + pad * 0.5f;
                        EA::RectT r;
                        r.left = x0;
                        r.top = y0;
                        r.right = x0 + inner;
                        r.bottom = y0 + inner;
                        sw->Init(mColorPickerConfig, GetExpansionColor(mBaseColor, i, j), r,
                                 mWinExpansion, this);
                        sw->mExpansionIndex = base + j;
                        sw->mSwatchIndex = mSwatchIndex;
                        EA::AutoRefCount<cSPColorSwatch> ref(sw);
                        cSPColorSwatch** pos = mExpansionSwatches.mpEnd;
                        if (pos < mExpansionSwatches.mpCapacity) {
                            mExpansionSwatches.mpEnd = pos + 1;
                            if (pos) {
                                *pos = sw;
                                sw->AddRef();
                            }
                        } else {
                            mExpansionSwatches.DoInsertSlow(pos, &ref);
                        }
                    }
                }
                base += expansionDim;
            }

            mExpanded = true;
            if (mOwner) {
                cSPEditorColorPicker* picker = (cSPEditorColorPicker*)mOwner->Cast(0xd0d22119);
                if (picker && picker->mWinRoot) {
                    if (picker->mWinRoot->GetParent())
                        picker->mWinRoot->GetParent()->AddWindow(picker->mWinRoot);
                }
            }
            mWinExpansion->AddWinProc(this);
            AddBoundingBox(mWinExpansion, 2, 1)->Renderer();
        }
    }

    int count2 = (int)(mExpansionSwatches.mpEnd - mExpansionSwatches.mpBegin);
    for (int k = 0; k < count2; k++)
        mExpansionSwatches.mpBegin[k]->Update(deltaTime, false);

    if (mBecomingOwner) {
        float t = dtMs * ownerFadeScale * 0.001f;
        if (t > 1.0f)
            t = 1.0f;
        if (mOwner) {
            cSPColorSwatch* other = (cSPColorSwatch*)mOwner->Cast(0x3b26ca5);
            if (other) {
                EA::RectT a = *other->mWinRoot->GetArea();
                const EA::RectT* b = mWinRoot->GetArea();
                EA::RectT r;
                r.left = (a.left - b->left) * t + b->left;
                r.top = (a.top - b->top) * t + b->top;
                r.right = (a.right - b->right) * t + b->right;
                r.bottom = (a.bottom - b->bottom) * t + b->bottom;
                SetArea(r, 0);
                float dx = a.left - r.left;
                float dy = a.top - r.top;
                if ((float)sqrt((double)(dx * dx + dy * dy)) < 1.0f) {
                    dx = a.right - r.right;
                    dy = a.bottom - r.bottom;
                    if ((float)sqrt((double)(dx * dx + dy * dy)) < 1.0f) {
                        mBecomingOwner = false;
                        mWinRoot->SetFlag(1, 0);
                        other->mWinRoot->SetFlag(1, 1);
                        other->mFadeTimer = 0.0f;
                        return;
                    }
                }
            }
        }
    }
}

// @ 0x005a6db0  SP::cSPEditorColorPicker::Update
void cSPEditorColorPicker::Update(int deltaTime) {
    int n = (int)(mSwatches.mpEnd - mSwatches.mpBegin);
    for (int i = 0; i < n; i++) {
        cSPColorSwatch* sw = mSwatches.mpBegin[i];
        sw->Update(deltaTime, sw == mSelectedSwatch.mpObject);
    }
}

// @ 0x005a6e00
float FUN_005a6e00(float x) {
    return Minf(Maxf(0.0f, x), 1.0f);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct BoundingBoxLite {
    void Renderer(); // 0x0080d710
};
}
