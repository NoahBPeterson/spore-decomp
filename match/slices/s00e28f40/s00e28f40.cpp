// Slice s00e28f40: SP::cSPUINewProgressBar::UpdateLevelWindows (SPUIProgressBar.cpp).
// UI module (SSE scalar math, no EH frame): /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// EA::COM::IRefCount (AddRef slot 0, Release slot 1)
// ---------------------------------------------------------------------------
struct IRefCount {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

// ---------------------------------------------------------------------------
// EA::Variant (size 0x14, flags +0x10, type id +0x12)
// ---------------------------------------------------------------------------
struct Variant {
    uint32_t mValue[4];
    uint16_t mFlags;
    uint16_t mTypeId;

    Variant() : mFlags(0), mTypeId(0) {}
    ~Variant() { if (mFlags & 4) Destruct(0); }
    void Destruct(int full);                        // 0x0093db80
    Variant& operator=(const unsigned int& v);      // 0x00427fd0 (operator=<unsigned int>)
    Variant& operator=(const float& v);             // 0x00428060 (operator=<float>)
};

// ---------------------------------------------------------------------------
// cSPUIAnimator and its value types (vtables 0x013f6400 / 0x013f63fc).
// ---------------------------------------------------------------------------
struct cAnimationTimer {                            // cSPUIAnimator::cAnimationTimer, 8 bytes
    virtual void TimerSlot0();
    IRefCount* mpTimeFunction;                      // AutoRefCount<cISPUIBehaviorTimeFunction>
    ~cAnimationTimer() { if (mpTimeFunction) mpTimeFunction->Release(); }
};

struct __declspec(align(64)) cAnimation {           // cSPUIAnimator::cAnimation, 0x80 bytes
    virtual void AnimSlot0();
    void* mActionFunc;                              // +0x4
    cAnimationTimer mTimer;                         // +0x8
    uint32_t mData[28];                             // +0x10
    ~cAnimation() {}
};

struct cSPUIAnimationSequence {
    void AppendAnimation(cAnimation& anim, IRefCount* obj, unsigned int type);   // 0x007f8fd0
};

struct cSPUIAnimator {
    void AddAnimation(cAnimation& anim, IRefCount* obj, unsigned int type);   // 0x007f8d10
    void RemoveAnimation(IRefCount* obj, unsigned int type);                  // 0x007f6210
};

enum eInterpolationType { kInterpolationLinear = 0 };

typedef void (*AnimSetterFn)(IRefCount*, Variant&, const Variant&, const Variant&, float);
typedef void (*AnimGetterFn)(IRefCount*, Variant&, Variant&);
typedef bool (*AnimEventFn)(IRefCount*, Variant&, int);

cAnimationTimer SPUICreateAnimationTimerInterpolation(float start, float duration, eInterpolationType type); // 0x007f7eb0
cAnimationTimer SPUICreateAnimationTimerRamp(float a, float b, float c);                                   // 0x007f6040
cAnimation SPUICreateObjectAnimation(IRefCount* obj, const Variant& a, AnimSetterFn setter, AnimGetterFn getter,
                                     const cAnimationTimer& timer, const Variant& b, const Variant& c,
                                     AnimEventFn event);                                                    // 0x007f7740
cAnimation SPUICreateAnimationSequence(cSPUIAnimationSequence** ppSequence);                               // 0x007f9340

// Same-TU static callbacks of SPUIProgressBar.cpp (addresses are relocations only).
void ProgressBar_SetColorParam(IRefCount*, Variant&, const Variant&, const Variant&, float);   // 0x00e28c40
void ProgressBar_GetColorParam(IRefCount*, Variant&, Variant&);                               // 0x00e28d60
void ProgressBar_SetFloatParam(IRefCount*, Variant&, const Variant&, const Variant&, float);   // 0x00e28b20
void ProgressBar_GetFloatParam(IRefCount*, Variant&, Variant&);                               // 0x00e28be0

// ---------------------------------------------------------------------------
// UI types
// ---------------------------------------------------------------------------
struct Rectangle { float x1, y1, x2, y2; };
struct ColorRGB { float r, g, b; };

// The SP material win-proc found through IWindow slot 0x4c -> Cast(0x5234b49).
// Shader parameters live at +0x188 (16 floats).
struct cSPUIMaterialWinProc : IRefCount {
    bool FindParameter(uint32_t id, unsigned int* pIndex, unsigned int* pType, unsigned int* pCount); // 0x0082f5c0
    void SetParameters(const float* values, unsigned int index, unsigned int count);                  // 0x0082e380
    void SetParameter(float value, unsigned int index);                                               // 0x0082e340
};

struct IWinProcContainer {
    virtual void S0();
    virtual void S1();
    virtual void S2();
    virtual cSPUIMaterialWinProc* Cast(uint32_t id);                // +0x0c
};

struct IWindow {
    virtual void S00(); virtual void S01(); virtual void S02(); virtual void S03();
    virtual void S04(); virtual void S05(); virtual void S06(); virtual void S07();
    virtual void S08(); virtual void S09(); virtual void S0a(); virtual void S0b();
    virtual void S0c(); virtual void S0d(); virtual void S0e(); virtual void S0f();
    virtual void S10(); virtual void S11(); virtual void S12();
    virtual IWinProcContainer* GetWinProcContainer();             // +0x4c
};

struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t id, bool recursive);           // 0x008105b0
};

struct ScreenInfo {                                                 // 32 bytes, copied by value
    int mField0;
    int mField4;
    int mField8;
    int mWidth;                                                     // +0x0c
    int mField10[4];
};

struct IRenderInfo {
    virtual void S0(); virtual void S1(); virtual void S2(); virtual void S3();
    virtual void S4(); virtual void S5(); virtual void S6();
    virtual const ScreenInfo& GetScreenInfo();                      // +0x1c
};
IRenderInfo* GetRenderInfo();                                       // 0x0067dd50

namespace SPUIHelpers {
    Rectangle GetBoundingScreenRect(IWindow* window, bool b);                             // 0x00808d20
    void SetWindowSPMaterial(IWindow* window, const wchar_t* material, bool b);           // 0x00808ad0
    float GetElapsedSeconds();                                                            // 0x00805080
}
uint32_t ColorRGBToU32(const ColorRGB& c);                                                // 0x00458a40

// eastl::basic_string<wchar_t> (16 bytes incl. allocator)
extern wchar_t gEmptyWString[2];                                    // 0x01667bac
void __cdecl EASTLFreeArray(void* p);                               // 0x00f47380 (operator delete[])
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    WString() : mpBegin(gEmptyWString), mpEnd(gEmptyWString), mpCapacity(gEmptyWString + 1) {}
    ~WString() { if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTLFreeArray(mpBegin); }
    const wchar_t* c_str() const { return mpBegin; }
};
void __cdecl WString_sprintf(WString* s, const wchar_t* fmt, ...);   // 0x0041e050

// Progress-bar tuning (SPUIProgressBar.cpp file-scope tuning globals).
struct TunedColor { ColorRGB mValue; uint32_t mPad[3]; };           // 0x18 stride
extern TunedColor gLevelShades[6];                                  // 0x016ac484
extern bool  gMaterialFlag;                                         // 0x016ac514
extern float gShadeFadeDuration;                                    // 0x016ac524
extern float gShadeSecondDelay;                                     // 0x016ac534
extern float gShadeSecondDuration;                                  // 0x016ac544
extern float gBoundaryRampDuration;                                 // 0x016ac354

template<class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

inline float ClampUnit(float v) {
    float lo = -1.0f;
    float hi = 1.0f;
    v = (v > lo) ? v : lo;        // maxss
    v = (v < hi) ? v : hi;        // minss
    return v;
}

namespace SP {

class cSPUINewProgressBar {
public:
    void* vftable;
    int mnRefCount;
    cSPUILayout* mGlobalUILayout;                   // +0x08 AutoRefCount<cSPUILayout>
    IRefCount* mTuningProps;                        // +0x0c
    cSPUIAnimator* mpAnimator;                      // +0x10
    unsigned int mNumFramesPerLevel[5];             // +0x14
    float mfCachedProgress;                         // +0x28
    unsigned int mCachedLevel;                      // +0x2c
    unsigned int mCachedFrame;                      // +0x30
    int mCachedIntProgress;                         // +0x34

    void UpdateLevelWindows(IWindow* window, float progress, float offset, float width, bool instant);
};

// @ 0x00e28f40
void cSPUINewProgressBar::UpdateLevelWindows(IWindow* window, float progress, float offset, float width, bool instant)
{
    ScreenInfo screen = GetRenderInfo()->GetScreenInfo();
    Rectangle barRect = SPUIHelpers::GetBoundingScreenRect(window, false);
    float invWidth = 1.0f / (float)screen.mWidth;

    float leftBoundary =
        ClampUnit((((barRect.x2 - barRect.x1) * progress + barRect.x1) * invWidth - 0.5f) * 2.0f);

    Rectangle markerRect =
        SPUIHelpers::GetBoundingScreenRect(mGlobalUILayout->FindWindowByID(0x51b5478, true), false);
    float middleBoundary = ClampUnit((((markerRect.x1 + offset) + width) * invWidth - 0.5f) * 2.0f);

    ColorRGB leftShade   = gLevelShades[0].mValue;
    ColorRGB fadeShade   = gLevelShades[1].mValue;
    ColorRGB deltaShade  = gLevelShades[2].mValue;
    ColorRGB deltaShade2 = gLevelShades[3].mValue;
    ColorRGB middleShade = gLevelShades[4].mValue;
    ColorRGB rightShade  = gLevelShades[5].mValue;

    for (unsigned int i = 0; i < 5; ++i) {
        if (mNumFramesPerLevel[i] == 0)
            continue;
        IWindow* levelWindow = mGlobalUILayout->FindWindowByID(0x51b54c0 + i, true);
        if (levelWindow == 0)
            continue;

        IWinProcContainer* procs = levelWindow->GetWinProcContainer();
        cSPUIMaterialWinProc* material;
        if (procs == 0 || (material = procs->Cast(0x5234b49)) == 0) {
            WString cmd;
            WString_sprintf(&cmd,
                L"ui_material_split -leftShade (%f,%f,%f) -deltaShade (%f, %f, %f) -middleShade (%f,%f,%f) "
                L"-rightShade (%f,%f,%f) -leftBoundary %f -deltaBoundary %f -middleBoundary %f",
                (double)leftShade.r, (double)leftShade.g, (double)leftShade.b,
                (double)deltaShade.r, (double)deltaShade.g, (double)deltaShade.b,
                (double)middleShade.r, (double)middleShade.g, (double)middleShade.b,
                (double)rightShade.r, (double)rightShade.g, (double)rightShade.b,
                (double)leftBoundary, (double)leftBoundary, (double)middleBoundary);
            SPUIHelpers::SetWindowSPMaterial(levelWindow, cmd.c_str(), gMaterialFlag);
            continue;
        }

        mpAnimator->RemoveAnimation(material, (unsigned int)-1);

        unsigned int index;
        unsigned int type;
        unsigned int count;

        // shade parameter 0x13ee73cd
        if (material->FindParameter(0x13ee73cd, &index, &type, &count)) {
            if (instant) {
                float values[4] = { leftShade.r, leftShade.g, leftShade.b, 0.0f };
                unsigned int maxCount = 3;
                material->SetParameters(values, index, Min(count, maxCount));
            } else {
                float startTime = SPUIHelpers::GetElapsedSeconds();
                cSPUIAnimationSequence* sequence;
                cAnimation sequenceAnim = SPUICreateAnimationSequence(&sequence);
                {
                    Variant vIndex;
                    vIndex = index;
                    unsigned int color = ColorRGBToU32(fadeShade);
                    Variant vColor;
                    vColor = color;
                    Variant vNone;
                    sequence->AppendAnimation(
                        SPUICreateObjectAnimation(material, vColor, ProgressBar_SetColorParam, ProgressBar_GetColorParam,
                            SPUICreateAnimationTimerInterpolation(startTime, gShadeFadeDuration, kInterpolationLinear),
                            vIndex, vNone, 0),
                        material, 10);
                }
                {
                    Variant vIndex;
                    vIndex = index;
                    unsigned int color = ColorRGBToU32(leftShade);
                    Variant vColor;
                    vColor = color;
                    Variant vNone;
                    sequence->AppendAnimation(
                        SPUICreateObjectAnimation(material, vColor, ProgressBar_SetColorParam, ProgressBar_GetColorParam,
                            SPUICreateAnimationTimerInterpolation(startTime + gShadeSecondDelay, gShadeSecondDuration,
                                                                  kInterpolationLinear),
                            vIndex, vNone, 0),
                        material, 10);
                }
                mpAnimator->AddAnimation(sequenceAnim, material, 11);
            }
        }

        // shade parameter 0xf8cd941c
        if (material->FindParameter(0xf8cd941c, &index, &type, &count)) {
            unsigned int maxCount = 3;
            if (instant) {
                ColorRGB c = deltaShade;
                material->SetParameters(&c.r, index, Min(count, maxCount));
            } else {
                ColorRGB c = deltaShade2;
                material->SetParameters(&c.r, index, Min(count, maxCount));
            }
        }

        // boundary parameter 0xbaf389b4
        if (material->FindParameter(0xbaf389b4, &index, &type, &count)) {
            if (instant) {
                Variant vIndex;
                vIndex = index;
                Variant vValue;
                vValue = leftBoundary;
                Variant vNone;
                mpAnimator->AddAnimation(
                    SPUICreateObjectAnimation(material, vValue, ProgressBar_SetFloatParam, ProgressBar_GetFloatParam,
                        SPUICreateAnimationTimerRamp(gBoundaryRampDuration, 0.0f, 0.0f), vIndex, vNone, 0),
                    material, 8);
            } else {
                material->SetParameter(leftBoundary, index);
            }
        }

        // boundary parameter 0x937d4063
        if (material->FindParameter(0x937d4063, &index, &type, &count)) {
            if (instant) {
                material->SetParameter(leftBoundary, index);
            } else {
                Variant vIndex;
                vIndex = index;
                Variant vValue;
                vValue = leftBoundary;
                Variant vNone;
                mpAnimator->AddAnimation(
                    SPUICreateObjectAnimation(material, vValue, ProgressBar_SetFloatParam, ProgressBar_GetFloatParam,
                        SPUICreateAnimationTimerRamp(gBoundaryRampDuration, 0.0f, 0.0f), vIndex, vNone, 0),
                    material, 8);
            }
        }

        // boundary parameter 0x14757808
        if (material->FindParameter(0x14757808, &index, &type, &count)) {
            Variant vIndex;
            vIndex = index;
            Variant vValue;
            vValue = middleBoundary;
            Variant vNone;
            mpAnimator->AddAnimation(
                SPUICreateObjectAnimation(material, vValue, ProgressBar_SetFloatParam, ProgressBar_GetFloatParam,
                    SPUICreateAnimationTimerRamp(gBoundaryRampDuration, 0.0f, 0.0f), vIndex, vNone, 0),
                material, 9);
        }
    }
}

} // namespace SP
