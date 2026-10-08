// Slice s00e29c80: SP::cSPUINewProgressBar::Update (SPUIProgressBar.cpp), the per-frame update that
// refreshes the money/progress caption (currency string, pop/colour animation sequence) when the integer
// value changes and slides/scales the level marker, fill and sound when the float progress changes.
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no EH frame, no 64-byte frame alignment).
#include "types.h"

// ---------------------------------------------------------------------------
// shared UI scaffolding (same declarations as slice s00e28f40)
// ---------------------------------------------------------------------------
struct IRefCount {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

struct cAnimationTimer {                            // cSPUIAnimator::cAnimationTimer, 8 bytes
    virtual void TimerSlot0();
    IRefCount* mpTimeFunction;                      // AutoRefCount<cISPUIBehaviorTimeFunction>
    ~cAnimationTimer() { if (mpTimeFunction) mpTimeFunction->Release(); }
};

struct cAnimation {                                 // cSPUIAnimator::cAnimation, 0x80 bytes
    virtual void AnimSlot0();
    void* mActionFunc;                              // +0x4
    cAnimationTimer mTimer;                         // +0x8
    uint32_t mData[28];                             // +0x10
    ~cAnimation() {}
    cAnimation& operator=(const cAnimation& o);     // 0x007f6ff0
};

struct cSPUIAnimationSequence {
    void AppendAnimation(cAnimation& anim, IRefCount* obj, unsigned int type);   // 0x007f8fd0
};

struct IWindow;
struct cSPUIAnimator {
    void Update();                                                             // 0x007f63b0
    void AddAnimation(cAnimation& anim, IWindow* obj, unsigned int type);      // 0x007f8d10
    void RemoveAnimation(IWindow* obj, unsigned int type);                     // 0x007f6210
};

cAnimation SPUICreateAnimationSequence(cSPUIAnimationSequence** ppSequence);   // 0x007f9340
cAnimation SPUICreateWindowAnimationTargetScale(IWindow* w, float to, float start, float duration, int flags);   // 0x007f81d0
cAnimation SPUICreateWindowAnimationTargetShade(IWindow* w, uint32_t color, float start, float duration, int flags);   // 0x007f82f0
cAnimation SPUICreateWindowAnimationTargetPosition(IWindow* w, float x, float y, float start, float duration, int flags);   // 0x007f80d0
cAnimation SPUICreateWindowAnimationTargetOscillatingFill(IWindow* w, int color, float amplitude, float start, float duration);   // 0x007f7670

struct IWindow : IRefCount {
    virtual void P02();
    virtual IWindow* FindChildByID(uint32_t id);                  // +0x0c (ret 4)
    virtual void P04();
    virtual void SetFlag(int v);                                  // +0x14
    virtual void P06();
    virtual void P07();
    virtual void P08();
    virtual void P09();
    virtual void P0a();
    virtual void P0b();
    virtual void P0c();
    virtual void P0d();
    virtual const float* GetArea();                               // +0x38 (left, top, right, bottom)
    virtual void P0f();
    virtual void P10();
    virtual void P11();
    virtual void P12();
    virtual void P13();
    virtual void P14();
    virtual void P15();
    virtual void P16();
    virtual void SetShadeColor(uint32_t color);                   // +0x5c
    virtual void P18();
    virtual void P19();
    virtual void SetSize(float width, float height);              // +0x68
    virtual void P1b();
    virtual void P1c();
    virtual void P1d();
    virtual void P1e();
    virtual void P1f();
    virtual void SetCaption(const wchar_t* text);                 // +0x80
};

struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t id, bool recursive);          // 0x008105b0
};

namespace SPUIHelpers {
    float GetElapsedSeconds();                                     // 0x00805080
}

// eastl::basic_string<wchar_t> (16 bytes incl. allocator)
extern wchar_t gEmptyWString[2];                                   // 0x01667bac
void __cdecl EASTLFreeArray(void* p);                              // 0x00f47380 (operator delete[])
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    WString() : mpBegin(gEmptyWString), mpEnd(gEmptyWString), mpCapacity(gEmptyWString + 1) {}
    ~WString() { if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTLFreeArray(mpBegin); }
    void assign(const wchar_t* first, const wchar_t* last);         // 0x00423650 (ret 8)
    const wchar_t* c_str() const { return mpBegin; }
};

// ---------------------------------------------------------------------------
// game-side helpers used by Update
// ---------------------------------------------------------------------------
uint32_t __cdecl GetCurrentGameMode();                             // 0x00b5b800 (SP::GetCurrentGameMode)
struct cTribe {
    uint16_t GetCurrencySymbol();                                  // 0x00c8e9f0
};
struct cGameNounManager {
    cTribe* GetPlayerTribe();                                      // 0x00bfc5f0
};
cGameNounManager* __cdecl NounManager();                           // 0x00b3d300 (SP::NounManager)
void __cdecl SetMoneyString(double amount, wchar_t* out, int capacity, const wchar_t* fmt,
                            const wchar_t* symbol);                // 0x008822e0 (EA::Locale::SetMoneyString)

struct IAudioSystem {
    virtual void A0(); virtual void A1(); virtual void A2(); virtual void A3();
    virtual void A4(); virtual void A5(); virtual void A6(); virtual void A7();
    virtual int Slot20();                                          // +0x20
};
IAudioSystem* __cdecl GetSystemAT();                               // 0x00a206f0 (EA::Audio::GetSystemAT)
void __cdecl KillSetiEffects(uint32_t id, int arg);                // 0x00435ed0 (callee-scored PDB name)

// Computes the bar level, the frame inside it and the fraction inside the frame from the progress.
void __cdecl GetLevelAndFrame(float progress, const unsigned int* framesPerLevel, unsigned int* outLevel,
                              unsigned int* outFrame, float* outFraction);   // 0x00e28920

// Progress-bar tuning (SPUIProgressBar.cpp file-scope tuning globals).
struct TunedShade { uint32_t mPad[3]; uint32_t mValue; };
struct SoundSet { uint32_t mId; uint32_t mB; uint32_t mC; };
extern TunedShade gShadeIncrease;        // 0x016ac428
extern TunedShade gShadeDecrease;        // 0x016ac438
extern float gCaptionScaleFrom;          // 0x016ac424
extern float gCaptionScaleDuration;      // 0x016ac3f4
extern float gCaptionSettleDelay;        // 0x016ac404
extern float gCaptionSettleDuration;     // 0x016ac414
extern float gCaptionShadeDuration;      // 0x016ac454
extern float gCaptionShadeFadeDelay;     // 0x016ac464
extern float gCaptionShadeFadeDuration;  // 0x016ac474
extern float gMarkerMoveDuration;        // 0x016ac354
extern float gMarkerScaleDuration;       // 0x016ac364
extern float gMarkerScaleFrom;           // 0x016ac394
extern float gMarkerSettleDelay;         // 0x016ac374
extern float gMarkerSettleDuration;      // 0x016ac384
extern uint32_t gFillShade;              // 0x016ac3e4
extern float gFillOscDuration;           // 0x016ac3c4
extern float gFillOscAmplitude;          // 0x016ac3d4
extern SoundSet gSoundForward;           // 0x016ac324
extern SoundSet gSoundBackward;          // 0x016ac33c

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

    void UpdateLevelWindows(IWindow* window, float progress, float offset, float width, bool instant);   // 0x00e28f40
    void Update(float progress, int amount);        // 0x00e29da0
};

// @ 0x00e29da0
void cSPUINewProgressBar::Update(float progress, int amount)
{
    mpAnimator->Update();
    float elapsed = SPUIHelpers::GetElapsedSeconds();

    if (amount != mCachedIntProgress) {
        IWindow* window = mGlobalUILayout->FindWindowByID(0xabcd1001, true);
        if (window) {
            cSPUIAnimationSequence* seq;
            WString text;
            wchar_t buffer[40];
            buffer[0] = 0;
            wchar_t symbol[2];
            symbol[0] = 0x268a;
            symbol[1] = 0;
            switch (GetCurrentGameMode()) {
            case 0x1654c00:
            case 0x1654c01:
                symbol[0] = 0x268b;
                break;
            case 0x1654c02: {
                cTribe* tribe = NounManager()->GetPlayerTribe();
                if (tribe)
                    symbol[0] = tribe->GetCurrencySymbol();
                else
                    symbol[0] = 0x268f;
                break;
            }
            case 0x1654c04:
            case 0x1654c05:
                symbol[0] = 0x268a;
                break;
            }
            SetMoneyString((double)amount, buffer, 0x28, L"%-F%-p", symbol);
            const wchar_t* end = buffer;
            while (*end)
                ++end;
            text.assign(buffer, buffer + (end - buffer));
            window->SetCaption(text.c_str());

            IWindow* child = window->FindChildByID(0xf15f4bd);
            if (child) {
                const float* rect = window->GetArea();
                float height = rect[3] - rect[1];
                child->SetFlag(0);
                window->SetSize(rect[2] - rect[0], height);
            }

            cAnimation anim = SPUICreateAnimationSequence(&seq);
            seq->AppendAnimation(SPUICreateWindowAnimationTargetScale(window, gCaptionScaleFrom, elapsed, gCaptionScaleDuration, 0), window, 2);
            seq->AppendAnimation(SPUICreateWindowAnimationTargetScale(window, 1.0f, gCaptionSettleDelay + elapsed, gCaptionSettleDuration, 0), window, 3);
            mpAnimator->AddAnimation(anim, window, 6);

            const TunedShade& shade = (amount < mCachedIntProgress) ? gShadeDecrease : gShadeIncrease;
            uint32_t color = shade.mValue;
            anim = SPUICreateAnimationSequence(&seq);
            seq->AppendAnimation(SPUICreateWindowAnimationTargetShade(window, color, elapsed, gCaptionShadeDuration, 0), window, 4);
            seq->AppendAnimation(SPUICreateWindowAnimationTargetShade(window, 0xffffffff, gCaptionShadeFadeDelay + elapsed, gCaptionShadeFadeDuration, 0), window, 5);
            mpAnimator->AddAnimation(anim, window, 7);
        }
        mCachedIntProgress = amount;
    }

    if (progress != mfCachedProgress) {
        unsigned int level;
        unsigned int frame;
        float fraction;
        GetLevelAndFrame(progress, mNumFramesPerLevel, &level, &frame, &fraction);

        IWindow* levelWindow = mGlobalUILayout->FindWindowByID(level + 0x51b54c0, true);
        if (levelWindow) {
            const float* levelRect = levelWindow->GetArea();
            IWindow* marker = mGlobalUILayout->FindWindowByID(0x51b5168, true);
            if (marker) {
                const float* markerRect = marker->GetArea();
                float markerX = (levelRect[2] - levelRect[0]) * fraction + levelRect[0];
                float markerY = markerRect[1];
                mpAnimator->RemoveAnimation(marker, (unsigned int)-1);
                mpAnimator->AddAnimation(SPUICreateWindowAnimationTargetPosition(marker, markerX, markerY, elapsed, gMarkerMoveDuration, 0), marker, 1);

                cSPUIAnimationSequence* seq;
                cAnimation anim = SPUICreateAnimationSequence(&seq);
                seq->AppendAnimation(SPUICreateWindowAnimationTargetScale(marker, gMarkerScaleFrom, elapsed, gMarkerScaleDuration, 0), marker, 2);
                seq->AppendAnimation(SPUICreateWindowAnimationTargetScale(marker, 1.0f, gMarkerSettleDelay + elapsed, gMarkerSettleDuration, 0), marker, 3);
                mpAnimator->AddAnimation(anim, marker, 6);
            }
            IWindow* fillWindow = mGlobalUILayout->FindWindowByID(0x51b7e48, true);
            if (fillWindow) {
                const float* fillRect = fillWindow->GetArea();
                float offset = (levelRect[2] - levelRect[0]) * ((float)frame / (float)mNumFramesPerLevel[level]) + levelRect[0];
                if (frame != mCachedFrame) {
                    levelWindow->SetShadeColor(gFillShade);
                    mpAnimator->AddAnimation(SPUICreateWindowAnimationTargetOscillatingFill(levelWindow, -1, gFillOscAmplitude, elapsed, gFillOscDuration), levelWindow, 4);
                    mCachedFrame = frame;
                }
                UpdateLevelWindows(levelWindow, fraction, offset, fillRect[2] - fillRect[0], progress > mfCachedProgress);
            }
        }

        SoundSet sound = (mfCachedProgress > progress) ? gSoundBackward : gSoundForward;
        IAudioSystem* audio = GetSystemAT();
        KillSetiEffects(sound.mId, audio ? audio->Slot20() : 0);
        mfCachedProgress = progress;
        mCachedLevel = level;
    }
}

}  // namespace SP
