#include "types.h"
#include <math.h>

// Slice s005e16c0: SP::cSPEditorVerbIcon (UI::TimelineEventEditorVerbIcon) and SP::cSPVerbTrayCollection.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (the float compares need /fp:fast).

#define PV(n) virtual void _pv##n();

// ---------------------------------------------------------------------------------------------
// Shared resource key (0x0c bytes, passed by value).
namespace EA {
namespace ResourceMan {
struct Key {
    unsigned int mType;
    unsigned int mGroup;
    unsigned int mInstance;
};
}
}

extern const char kEditorAllocName[];   // "Editor" @ 0x013eb430
extern float g_015f0090;                // cos frequency constant

// ---------------------------------------------------------------------------------------------
// UI window (only the vtable slots this slice uses are named).
namespace EA {
namespace UTFWin {
class IWindow {
 public:
    virtual int AddRef();                       // +0x00
    virtual int Release();                      // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual void SetPage(IWindow* page, int b); // +0x28
    PV(11) PV(12) PV(13)
    virtual const float* GetArea();             // +0x38
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    virtual void SetArea(const float* r);       // +0x6c
    PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51)
    PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
    virtual IWindow* FindChild(unsigned int id, int b);   // +0xf0
};
// A ref-counted object whose Release lives at vtable slot 2 (used by the +0x0c member).
class IRefCounted2 {
 public:
    virtual int AddRef();                       // +0x00
    virtual void _s1();                         // +0x04
    virtual int Release();                      // +0x08
};
}
}

// Reference-counted smart pointer, exactly as the original inlines it.
template <typename T>
class AutoRefCount {
 public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};

// ---------------------------------------------------------------------------------------------
// Interpolation values.
namespace SP {

struct cVerbIconInterpolationValue {          // 0x1c bytes
    float mTargetValue;      // +0x00
    float mCurrentValue;     // +0x04
    float mElapsedTime;      // +0x08
    float mInitialValue;     // +0x0c
    float mDuration;         // +0x10
    float mOverShoot;        // +0x14
    float mDampenPercent;    // +0x18
    void Init(float a, float b, float c, float d, float e);
    int IsAtTarget();
    void Update(float dt);                   // @ 0x005e1d00
};

struct cVerbIconMiddleInterpolationValue {    // 0x20 bytes
    float mEndValue;         // +0x00
    float mMiddleValue;      // +0x04
    float mCurrentValue;     // +0x08
    float mElapsedTime;      // +0x0c
    float mInitialValue;     // +0x10
    float mMiddleStart;      // +0x14
    float mMiddleEnd;        // +0x18
    float mDuration;         // +0x1c
    void Update(float dt);                   // @ 0x005e1e90
};

struct cVerbIconLinearInterpolationValue {    // 0x14 bytes
    float mTargetValue;      // +0x00
    float mCurrentValue;     // +0x04
    float mElapsedTime;      // +0x08
    float mInitialValue;     // +0x0c
    float mDuration;         // +0x10
};

struct cVerbIconOscillatingAlpha {            // 0x18 bytes
    float mTargetValue;      // +0x00
    float mCurrentValue;     // +0x04
    float mElapsedTime;      // +0x08
    float mDuration;         // +0x0c
    float mSpeed;            // +0x10
    unsigned int mColor;     // +0x14
};
}
using SP::cVerbIconInterpolationValue;
using SP::cVerbIconMiddleInterpolationValue;

// @ 0x005e1c80
void cVerbIconInterpolationValue::Init(float a, float b, float c, float d, float e)
{
    mInitialValue = a;
    mCurrentValue = a;
    mTargetValue = b;
    mDuration = c;
    mOverShoot = e;
    mDampenPercent = d;
    mElapsedTime = 0.0f;
}

// @ 0x005e1cd0
int cVerbIconInterpolationValue::IsAtTarget()
{
    if (mCurrentValue == mTargetValue && mElapsedTime >= mDuration)
        return 1;
    return 0;
}

// @ 0x005e1d00
void cVerbIconInterpolationValue::Update(float dt)
{
    if (mCurrentValue == mTargetValue && mElapsedTime >= mDuration)
        return;
    float elapsed = mElapsedTime + dt;
    float duration = mDuration;
    mElapsedTime = elapsed;
    if (duration <= elapsed) {
        mCurrentValue = mTargetValue;
        mElapsedTime = duration;
        return;
    }
    float t = elapsed / duration;
    float dampen = mDampenPercent;
    float knee = 1.0f - dampen;
    float over = mOverShoot + 1.0f;
    float k = over;
    if (0.1f <= knee)
        k = sqrtf((1.0f / knee) * t) * over;
    if (knee < t) {
        float g = (t - knee) / (dampen * 0.25f);
        if (g < 0.0f) g = 0.0f;
        if (g > 1.0f) g = 1.0f;
        k = (over - k) * g + k;
    }
    float h = (t - knee) / dampen;
    if (h < 0.0f) h = 0.0f;
    if (h > 1.0f) h = 1.0f;
    mCurrentValue = (mTargetValue - mInitialValue) *
        (((1.0f - h) * cosf(g_015f0090 * h * 1.5f) * mOverShoot - mOverShoot) + k)
        + mInitialValue;
}

// @ 0x005e1e90
void cVerbIconMiddleInterpolationValue::Update(float dt)
{
    if (mCurrentValue == mEndValue && mElapsedTime >= mDuration)
        return;
    float elapsed = mElapsedTime + dt;
    float duration = mDuration;
    mElapsedTime = elapsed;
    if (duration <= elapsed) {
        mCurrentValue = mEndValue;
        mElapsedTime = duration;
        return;
    }
    float t = elapsed / duration;
    if (t < mMiddleStart) {
        mCurrentValue = (mMiddleValue - mInitialValue) * (t / mMiddleStart) + mInitialValue;
        return;
    }
    if (t > mMiddleEnd) {
        mCurrentValue = ((t - mMiddleEnd) / (1.0f - mMiddleEnd)) * (mEndValue - mMiddleValue)
                        + mMiddleValue;
        return;
    }
    mCurrentValue = mMiddleValue;
}

// ---------------------------------------------------------------------------------------------
// Base subobjects of the verb icon (two vtables: +0x00 and +0x04).
namespace EA {
namespace Trace {
class ITracerBase {
 public:
    ~ITracerBase() {}
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
};
}
}
namespace Simulator {
class cContentValidationSummarizer {
 public:
    ~cContentValidationSummarizer() {}
    virtual void v0();
    virtual void v1();
    int mRefCount;          // +0x08
};
}

namespace SP {

class cSPUILayout {
 public:
    virtual int AddRef();
    virtual int Release();
    bool Init(const EA::ResourceMan::Key& key, bool b, unsigned int n);   // 0x008120d0
    bool SetParentWin(EA::UTFWin::IWindow* p, bool b, unsigned int n);    // 0x008121b0
    EA::UTFWin::IWindow* FindWindowByID(unsigned int id, bool b);         // 0x008105b0
};

class cSPEditorVerbIconTray : public EA::UTFWin::IWindow {
 public:
    float GetHeight();                                                    // 0x005e6390
};

class cSPEditorVerbIcon
    : public EA::Trace::ITracerBase, public Simulator::cContentValidationSummarizer {
 public:
    // ---- virtuals (slot 9 == +0x24, slot 18 == +0x48) ----
    virtual void LayoutInit(EA::ResourceMan::Key key, int a, int b);      // +0x24
    virtual void Slot10();                                                // +0x28
    virtual void Slot11();
    virtual void Slot12();
    virtual void SetLevel(float level);                                   // +0x34
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void SetVerbID(unsigned int id);                              // +0x48

    // ---- members ----
    AutoRefCount<EA::UTFWin::IRefCounted2> mWin0c;    // +0x0c
    AutoRefCount<EA::UTFWin::IWindow> mWinRoot;  // +0x10
    AutoRefCount<EA::UTFWin::IWindow> mWinIcon;  // +0x14
    AutoRefCount<EA::UTFWin::IWindow> mWinLevel; // +0x18
    AutoRefCount<EA::UTFWin::IWindow> mWinHighlight;      // +0x1c
    AutoRefCount<EA::UTFWin::IWindow> mWinShortcutText;   // +0x20
    AutoRefCount<EA::UTFWin::IWindow> mWin24;             // +0x24
    AutoRefCount<EA::UTFWin::IWindow> mWinFlashingGlow;   // +0x28
    AutoRefCount<EA::UTFWin::IWindow> mWinChargeDial;     // +0x2c
    AutoRefCount<EA::UTFWin::IWindow> mWinLevelPips[5];   // +0x30 .. +0x44
    AutoRefCount<EA::UTFWin::IWindow> mWin44;             // +0x44
    unsigned int mPad48[3];                      // +0x48
    unsigned int mPad54[3];                      // +0x54
    unsigned int mUnk60;                         // +0x60
    int mState;                                  // +0x64
    unsigned char mB68;                          // +0x68
    unsigned char mB69;
    unsigned char mB6a;
    unsigned char mB6b;
    unsigned char mB6c;
    unsigned char mB6d;
    unsigned char mB6e;
    unsigned char mB6f;
    unsigned char mB70;
    unsigned char mB71;
    unsigned char mB72;
    unsigned char mB73;
    unsigned char mPad74[0x1c];                  // +0x74 .. +0x8f
    float mF90;                                  // +0x90
    float mF94;                                  // +0x94
    cVerbIconLinearInterpolationValue mCharge;   // +0x98
    cVerbIconInterpolationValue mScaleX;         // +0xac
    cVerbIconInterpolationValue mScaleY;         // +0xc8
    cVerbIconLinearInterpolationValue mLevel;    // +0xe4
    cVerbIconInterpolationValue mUpgradeScale;   // +0xf8
    cVerbIconMiddleInterpolationValue mUpgradeHighlightFade;   // +0x114
    cVerbIconMiddleInterpolationValue mIconAlpha;              // +0x134
    float mF154;                                 // +0x154
    cVerbIconOscillatingAlpha mFlashAlpha;       // +0x158
    AutoRefCount<EA::UTFWin::IWindow> mIconData; // +0x170
    AutoRefCount<EA::UTFWin::IWindow> mRollover; // +0x174
    unsigned int mBaseTextColor;                 // +0x178
    AutoRefCount<EA::UTFWin::IWindow> mCollectionID;   // +0x17c
    float mAspectRatio;                          // +0x180

    cSPEditorVerbIcon();
    ~cSPEditorVerbIcon();
    void SetFlag(char b);                        // @ 0x005e1fa0
    void Reset(int verbId, char b, char c);      // @ 0x005e23b0
    void SetIcon(EA::UTFWin::IWindow* p, EA::ResourceMan::Key key, int a, int b);  // @ 0x005e1b70
};

// @ 0x005e1fa0
void SP::cSPEditorVerbIcon::SetFlag(char b)
{
    mB6b = 1;
    mB6a = b;
}

// @ 0x005e23b0
void SP::cSPEditorVerbIcon::Reset(int verbId, char b, char c)
{
    mWinRoot = 0;
    mWinIcon = 0;
    mWinHighlight = 0;
    mWinShortcutText = 0;
    mWin24 = 0;
    mWinChargeDial = 0;
    mB69 = 0;
    mB6d = 0;
    mB6e = 0;
    mB72 = 0;
    mB73 = 0;
    mB68 = c;
    mB6c = b;
    for (int i = 0; i < 5; ++i)
        mWinLevelPips[i] = 0;
    SetVerbID((unsigned int)verbId);
}

// @ 0x005e2280
SP::cSPEditorVerbIcon::~cSPEditorVerbIcon()
{
}

// @ 0x005e2000
SP::cSPEditorVerbIcon::cSPEditorVerbIcon()
{
    mState = 6;
    mB6b = 0; mB6c = 0; mB6f = 0; mB71 = 0; mB72 = 0; mB73 = 0;
    mB68 = 1; mB69 = 1; mB6a = 1; mB6d = 1; mB6e = 1; mB70 = 1;
    mCharge.mTargetValue = 1.0f; mCharge.mCurrentValue = 1.0f; mCharge.mElapsedTime = 0.0f;
    mCharge.mInitialValue = 1.0f; mCharge.mDuration = 0.0f;
    mScaleX.mTargetValue = 1.0f; mScaleX.mCurrentValue = 1.0f; mScaleX.mElapsedTime = 0.0f;
    mScaleX.mInitialValue = 1.0f; mScaleX.mDuration = 0.0f;
    mScaleX.mOverShoot = 0.0f; mScaleX.mDampenPercent = 0.0f;
    mScaleY.mTargetValue = 1.0f; mScaleY.mCurrentValue = 1.0f; mScaleY.mElapsedTime = 0.0f;
    mScaleY.mInitialValue = 1.0f; mScaleY.mDuration = 0.0f;
    mScaleY.mOverShoot = 0.0f; mScaleY.mDampenPercent = 0.0f;
    mLevel.mTargetValue = 1.0f; mLevel.mCurrentValue = 1.0f; mLevel.mElapsedTime = 0.0f;
    mLevel.mInitialValue = 1.0f; mLevel.mDuration = 0.0f;
    mUpgradeScale.mTargetValue = 1.0f; mUpgradeScale.mCurrentValue = 1.0f;
    mUpgradeScale.mElapsedTime = 0.0f; mUpgradeScale.mInitialValue = 1.0f;
    mUpgradeScale.mDuration = 0.0f; mUpgradeScale.mOverShoot = 0.0f;
    mUpgradeScale.mDampenPercent = 0.0f;
    mUpgradeHighlightFade.mEndValue = 1.0f; mUpgradeHighlightFade.mMiddleValue = 1.0f;
    mUpgradeHighlightFade.mCurrentValue = 1.0f; mUpgradeHighlightFade.mElapsedTime = 0.0f;
    mUpgradeHighlightFade.mInitialValue = 1.0f; mUpgradeHighlightFade.mMiddleStart = 0.05f;
    mUpgradeHighlightFade.mMiddleEnd = 0.05f; mUpgradeHighlightFade.mDuration = 0.0f;
    mIconAlpha.mEndValue = 1.0f; mIconAlpha.mMiddleValue = 1.0f;
    mIconAlpha.mCurrentValue = 1.0f; mIconAlpha.mElapsedTime = 0.0f;
    mIconAlpha.mInitialValue = 1.0f; mIconAlpha.mMiddleStart = 0.05f;
    mIconAlpha.mMiddleEnd = 0.05f; mIconAlpha.mDuration = 0.0f;
    mF154 = 0.0f;
    mFlashAlpha.mTargetValue = 0.0f; mFlashAlpha.mCurrentValue = 0.0f;
    mFlashAlpha.mElapsedTime = 0.0f; mFlashAlpha.mDuration = 0.0f;
    mFlashAlpha.mSpeed = 0.0f;
    mIconData = 0;
    mRollover = 0;
    mCollectionID = 0;
    mAspectRatio = 1.0f;
}

// @ 0x005e1b70
void SP::cSPEditorVerbIcon::SetIcon(EA::UTFWin::IWindow* p, EA::ResourceMan::Key key, int a, int b)
{
    mWinShortcutText = p;
    if (mWin24.mpObject == 0) {
        mWin24 = mWinShortcutText->FindChild(0x3ed7919, 1);
        if (mWin24.mpObject == 0)
            mWin24 = mWinShortcutText.mpObject;
    }
    mCharge.mCurrentValue = 0.0f;
    mF90 = 0.0f;
    mCharge.mElapsedTime = 0.0f;
    mF94 = 0.0f;
    mCharge.mInitialValue = 0.0f;
    mCharge.mTargetValue = 0.0f;
    LayoutInit(key, a, b);
    Slot10();
}

}  // namespace SP

// ---------------------------------------------------------------------------------------------
// SP::cSPVerbTrayCollection : the palette category that owns the verb-icon trays.
namespace SP {

class cSPPalettePage : public cSPEditorVerbIconTray {
 public:
    void SetParent(EA::UTFWin::IWindow* w, int b);      // +0x28 (slot 10)
};

// Plain layout class: the original places its own members at the offsets below.
class cSPVerbTrayCollection {
 public:
    void InitTraysBase(EA::ResourceMan::Key key, const void* p, int n);   // 0x00605f90
    cSPPalettePage* GetPage(int index);                                   // 0x005c1ce0
    void InitTrays(EA::ResourceMan::Key key, const void* p, int n);       // @ 0x005e16c0

    unsigned char mPad00[0x20];                 // +0x00 .. +0x1f
    AutoRefCount<EA::UTFWin::IWindow> mWin20;   // +0x20
    unsigned char mPad24[0x30];                 // +0x24 .. +0x53
    AutoRefCount<cSPUILayout> mLayout;          // +0x54
    AutoRefCount<EA::UTFWin::IWindow> mWin58;   // +0x58
    AutoRefCount<EA::UTFWin::IWindow> mWin5c;   // +0x5c
    AutoRefCount<EA::UTFWin::IWindow> mWin60;   // +0x60
    AutoRefCount<EA::UTFWin::IWindow> mWin64;   // +0x64
    AutoRefCount<EA::UTFWin::IWindow> mWin68;   // +0x68
    AutoRefCount<EA::UTFWin::IWindow> mWin6c;   // +0x6c
    AutoRefCount<EA::UTFWin::IWindow> mWin70;   // +0x70
    AutoRefCount<EA::UTFWin::IWindow> mWin74;   // +0x74
    AutoRefCount<EA::UTFWin::IWindow> mWin78;   // +0x78
    AutoRefCount<EA::UTFWin::IWindow> mWin7c;   // +0x7c
    AutoRefCount<EA::UTFWin::IWindow> mWin80;   // +0x80
    AutoRefCount<cSPPalettePage> mPage84;       // +0x84
    AutoRefCount<cSPPalettePage> mPage88;       // +0x88
    AutoRefCount<cSPPalettePage> mPage8c;       // +0x8c
    unsigned char mPad90[0x18];                 // +0x90 .. +0xa7
    float mHeight;                              // +0xa8
    float mArea[4];                             // +0xac .. +0xb8
};

// helper shims used by the Init below
class cPropertyManager {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual void GetProperty(int a, int b, void* out);      // +0x2c
};
cPropertyManager* PropertyManager();            // 0x0067de30
void GetPropertyAsKey(void* property, unsigned int id, EA::ResourceMan::Key* out);   // 0x006a1250
void* operator_new(unsigned int size, const char* name, int a, int b, int c, int d); // 0x00f473a0
cSPUILayout* cConnectionDialog_ctor(void* mem);                                        // 0x00810000

}

// @ 0x005e16c0
void SP::cSPVerbTrayCollection::InitTrays(EA::ResourceMan::Key key, const void* p, int n)
{
    InitTraysBase(key, p, n);

    void* temp = 0;
    cPropertyManager* pm = PropertyManager();
    pm->GetProperty(key.mType, key.mInstance, &temp);

    EA::ResourceMan::Key layoutKey;
    GetPropertyAsKey(temp, 0x6309cac, &layoutKey);
    layoutKey.mGroup = 0x510a95b;
    layoutKey.mInstance = 0x40464100;

    void* mem = operator_new(0x18, kEditorAllocName, 0, 0, 0, 0);
    if (mem != 0)
        mLayout = cConnectionDialog_ctor(mem);
    else
        mLayout = 0;

    mLayout->Init(layoutKey, true, 0x5b598fa);
    mLayout->SetParentWin(mWin20.mpObject, true, 0x5b598fa);

    mWin58 = mLayout->FindWindowByID(0x6309146, true);
    mWin5c = mLayout->FindWindowByID(0x6309b56, true);
    mWin60 = mLayout->FindWindowByID(0x63090b9, true);
    mWin64 = mLayout->FindWindowByID(0x63090db, true);
    mWin68 = mLayout->FindWindowByID(0x63090ef, true);
    mWin6c = mLayout->FindWindowByID(0x6381b56, true);
    mWin70 = mLayout->FindWindowByID(0x6381b57, true);
    mWin74 = mLayout->FindWindowByID(0x6381b58, true);
    mWin78 = mLayout->FindWindowByID(0x6381d5d, true);
    mWin7c = mLayout->FindWindowByID(0x6381d5e, true);
    mWin80 = mLayout->FindWindowByID(0x6381d5f, true);

    const float* area = mWin60.mpObject->GetArea();
    mArea[0] = area[0];
    mArea[1] = area[1];
    mArea[2] = area[2];
    mArea[3] = area[3];

    const float* a20 = mWin20.mpObject->GetArea();
    float x20 = a20[0];
    float x2_20 = a20[2];
    const float* a58 = mWin58.mpObject->GetArea();
    float r[4];
    r[0] = a58[2] - a58[0];
    r[1] = 0.0f;
    r[2] = x2_20 - x20;
    r[3] = a58[3] - a58[1];
    r[0] = r[2] - r[0];
    mWin58.mpObject->SetArea(r);

    mPage84 = (cSPPalettePage*)0;
    cSPPalettePage* page0 = GetPage(0);
    mWin5c.mpObject->SetPage(page0, 0);
    mPage84 = GetPage(1);
    mWin58.mpObject->SetPage(mPage84.mpObject, 0);
    mPage88 = GetPage(2);
    mWin58.mpObject->SetPage(mPage88.mpObject, 0);
    mPage8c = GetPage(3);
    mWin58.mpObject->SetPage(mPage8c.mpObject, 0);

    mHeight = mPage84.mpObject->GetHeight() - 10.0f;

    if (temp != 0)
        ((EA::UTFWin::IWindow*)temp)->Release();
}
