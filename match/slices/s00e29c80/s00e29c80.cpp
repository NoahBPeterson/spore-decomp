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
class cSPUIAnimator { public:
    cSPUIAnimator();                                                           // 0x007f83e0 (ctor)
    void Construct();                                                          // 0x007f83e0 (ctor)
    void Update();                                                             // 0x007f63b0
    void AddAnimation(cAnimation& anim, IWindow* obj, unsigned int type);      // 0x007f8d10
    void RemoveAnimation(IWindow* obj, unsigned int type);                     // 0x007f6210
    uint8_t mData[0x20];                                                       // sizeof == 0x20
};

cAnimation SPUICreateAnimationSequence(cSPUIAnimationSequence** ppSequence);   // 0x007f9340
cAnimation SPUICreateWindowAnimationTargetScale(IWindow* w, float to, float start, float duration, int flags);   // 0x007f81d0
cAnimation SPUICreateWindowAnimationTargetShade(IWindow* w, uint32_t color, float start, float duration, int flags);   // 0x007f82f0
cAnimation SPUICreateWindowAnimationTargetPosition(IWindow* w, float x, float y, float start, float duration, int flags);   // 0x007f80d0
cAnimation SPUICreateWindowAnimationTargetOscillatingFill(IWindow* w, int color, float amplitude, float start, float duration);   // 0x007f7670

// Every engine interface slot is entered with `this` in ecx and pops its own stack arguments
// (plain __thiscall members: cl emits `ret N`, so the callers never emit an `add esp`).
struct IWindow : IRefCount {
    virtual void  P02();
    virtual IWindow*  FindChildByID(uint32_t id);        // +0x0c
    virtual IWindow*  GetParent();                       // +0x10
    virtual void  SetFlag(int v);                        // +0x14
    virtual void  P06();
    virtual void  P07();
    virtual void  P08();
    virtual void  P09();
    virtual void  P0a();
    virtual void  P0b();
    virtual void  P0c();
    virtual const float*  GetAreaRaw();                  // +0x34
    virtual const float*  GetArea();                     // +0x38 (left, top, right, bottom)
    virtual void  P0f();
    virtual void  P10();
    virtual void  P11();
    virtual void  P12();
    virtual void  P13();
    virtual void  P14();
    virtual void  P15();
    virtual void  P16();
    virtual void  SetShadeColor(uint32_t color);         // +0x5c
    virtual void  SetAreaA(const float* area);            // +0x60
    virtual void  SetPosition(float x, float y);          // +0x64
    virtual void  SetSize(float width, float height);     // +0x68
    virtual void  SetAreaB(const float* area);            // +0x6c
    virtual void  P1c();
    virtual void  P1d();
    virtual void  P1e();
    virtual void  SetVisible(int what, uint8_t on);       // +0x7c (the flag is passed zero-extended)
    virtual void  SetCaption(const wchar_t* text);        // +0x80
    virtual void  P20();  virtual void  P21();   // +0x84, +0x88
    virtual void  P22();  virtual void  P23();
    virtual void  P24();  virtual void  P25();
    virtual void  P26();  virtual void  P27();
    virtual void  P28();  virtual void  P29();
    virtual void  P2a();  virtual void  P2b();
    virtual void  P2c();  virtual void  P2d();
    virtual void  P2e();  virtual void  P2f();   // +0xbc
    virtual void  P30();  virtual void  P31();
    virtual void  P32();  virtual void  P33();
    virtual void  P34();                                  // +0xd4
    virtual void  AddChild(IWindow* child);               // +0xd8
    virtual void  RemoveChild(IWindow* child);            // +0xdc
    virtual void  P38();  virtual void  P39();
    virtual void  P3a();  virtual void  P3b();
    virtual IWindow*  FindWindowByID2(uint32_t id, bool recursive);   // +0xf0
};

class cSPUILayout { public:
    IWindow*  FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0
    uint8_t mData[0x28];                                            // sizeof == 0x28 (never read here)
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
    void Init();                                    // 0x00e29c80
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

// ==================================================================================================
// SPUI rollover / property layouts (cSPUIPropertyLayout family, 0x00e29c80-0x00e2acc0).
// ==================================================================================================

struct AutoRefCount;
struct cProperty;

// SP::IPropertyManager (virtual only).
struct IPropertyManager {
    virtual void  M00(); virtual void  M04();
    virtual void  M08(); virtual void  M0c();
    virtual void  M10(); virtual void  M14();
    virtual void  M18(); virtual void  M1c();
    virtual void  M20(); virtual void  M24();
    virtual void  M28();
    virtual void  AddProperty(const void* owner, uint32_t id, IRefCount** out);   // +0x2c
    virtual bool  GetPropertyList(uint32_t id, IRefCount** out);                  // +0x30
};
IPropertyManager* PropertyManager();                                   // 0x67de30

// UTFWin property value; +0x12 is the value-type tag (9 = int).
struct cProperty {
    uint8_t  mPad00[0x12];                                             // +0x00
    uint16_t mType;                                                    // +0x12
    int* GetInt();                                                     // 0x41e990
};

// UTFWin property list: vtable slots 0x00/0x04 come from IRefCount.
struct cPropertyList : IRefCount {
    virtual void  L08(); virtual void  L0c();
    virtual void  L10(); virtual void  L14();
    virtual void  L18(); virtual void  L1c();
    virtual void  L20();
    virtual bool  GetProperty(uint32_t id, cProperty** out);  // +0x24
};

// 4-byte owning pointer: the reset/dtor store zero before releasing.
struct AutoRefCount {
    IRefCount* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    void Reset() { if (mpObject) { IRefCount* p = mpObject; mpObject = 0; p->Release(); } }
};

// eastl copy helper reached through the static object at 0x15a55e8.
struct cPropertyListCopier {
    void  do_copy(IRefCount* src);                            // 0x6237d0
};
extern cPropertyListCopier gPropertyListCopier;                        // 0x15a55e8

extern const float gSPUIRowPad;                                        // 0x1481654 (2.0f)
extern const float gSPUIRowHeight;                                     // 0x14816ec (88.0f)

struct cSPUILayoutManager {
    IWindow* GetWorldMainWindow();                                     // 0x810620
};

namespace SPUIHelpers {
    cSPUILayoutManager* __stdcall GetLayoutManager(uint32_t arg);      // 0x805070
}

// eastl::rbtree header embedded in the layout object at +0x78.
struct RBNode {
    uint8_t  mPad00[0x1c];                                             // +0x00
    uint32_t mField1c;                                                 // +0x1c
    uint32_t mField20;                                                 // +0x20
};
RBNode* __cdecl RBTreeIncrement(RBNode* node);                         // 0x921580

struct RBTree {
    void*   mHeader;                                                   // +0x78
    RBNode* mEndNode;                                                  // +0x7c
    RBNode* mRoot;                                                     // +0x80
    void  find(RBNode** out, const uint32_t* key);            // 0xe5c780
};

// Base of every rollover / property layout widget.
class cSPUIPropertyLayout {
public:
    virtual void  P00();                                      // +0x00 (dtor)
    virtual void  P04();
    virtual void  P08();
    virtual void  V0c();
    virtual void  V10();
    virtual void  V14();
    virtual void  V18();
    virtual void  V1c();
    virtual void  V20();
    virtual void  HideRollover();                             // +0x24

    bool Init();                                                       // 0x828250
    IWindow* GetRootWindow();                                          // 0x828100
    uint32_t GetEventMask();                                           // 0x828070
    bool func24h();                                                    // 0x828be0

    int mRefCount;                                                     // +0x04
    int mField08;                                                      // +0x08
    cSPUILayout mLayout;                                               // +0x0c (0x28 bytes)
    uint8_t mPad34[0x10];                                              // +0x34
    bool mFlag44;                                                      // +0x44
    uint8_t mPad45[0x33];                                              // +0x45
    RBTree mTree;                                                      // +0x78
    uint8_t mPad84[0x10];                                              // +0x84
    uint32_t mCounter94;                                               // +0x94
    uint32_t mValue98;                                                 // +0x98
    uint32_t mKey9c;                                                   // +0x9c
    uint32_t mValueA0;                                                 // +0xa0
    uint8_t mFlagA4;                                                   // +0xa4
    uint8_t mPadA5;                                                    // +0xa5
    uint8_t mFlagA6;                                                   // +0xa6
    uint8_t mPadA7;                                                    // +0xa7
    uint32_t mFieldA8;                                                 // +0xa8
};

// Concrete widgets (no extra members, only distinct method sets).
struct cSPUIRolloverCivCityVehicle : cSPUIPropertyLayout {
    bool Init(uint32_t arg);                                           // 0x00e2a550
};
struct cSPUICursorLayoutWidget : cSPUIPropertyLayout {
    void SetShown(bool shown);                                         // 0x00e2a600
};
struct cSPUIRolloverRelationship : cSPUIPropertyLayout {
    void HideRelationshipRollover();                                   // 0x00e2a6c0
};
struct cSPUIRolloverVehicleFlags : cSPUIPropertyLayout {
    uint32_t GetEventFlags();                                          // 0x00e2a690
};
struct cSPUIRolloverCityFlags : cSPUIPropertyLayout {
    uint32_t GetEventFlags();                                          // 0x00e2a6a0
};
struct cSPUIRolloverPropertyFlags : cSPUIPropertyLayout {
    uint32_t GetEventFlags();                                          // 0x00e2a5f0
};
struct cSPUIRolloverCivCityHall : cSPUIPropertyLayout {
    void SetSpecialtyIcon(uint32_t icon);                              // 0x00e2a7b0
    void calculate_layout();                                           // 0x00e2a920
    bool SetPrimaryPopulationGroupId(uint32_t id);                     // 0x00e2ab10
    void UpdatePlacement();                                            // 0x00e2abc0
    void read_properties();                                            // 0x00e2acc0
};

namespace UI {
class CursorAttachment : public cSPUIPropertyLayout {
public:
    void Dispose();                                                    // 0x00e2a5b0
};
}  // namespace UI

// Concrete layout as seen by the CursorAttachment constructor: three vftables are stored by hand.
struct cSPUIRolloverCivCityVehicleCtor {
    void* mpVftable00;                                                 // +0x00
    void* mpVftable04;                                                 // +0x04
    uint8_t mPad08[0x70];                                              // +0x08
    void* mpVftable78;                                                 // +0x78

    void BaseConstruct();                                              // 0x801280 (cSPUICursorAttachmentLayout ctor)
    void  SetKey(const wchar_t* key, uint32_t id);            // 0x827fc0
    void  SetRootWindowId(uint32_t id);                       // 0xc87bc0
    cSPUIRolloverCivCityVehicleCtor* Initialize();                     // 0x00e2a640
};

extern char gVftblCursorAttachment00[];                                // 0x01481694
extern char gVftblCursorAttachment04[];                                // 0x01481684
extern char gVftblCursorAttachment78[];                                // 0x01481668

// EA allocator with a debug tag (size, name, file, line, flags, flags).
void* operator new(size_t size, const char* name, int a, int b, int c, int d);   // 0xf473a0

struct cPlanetOwner {
    void** GetObject();                                                // 0xb8dad0
};
struct cActivePlanet {
    uint8_t mPad00[0x13c];                                             // +0x00
    cPlanetOwner* mOwner;                                              // +0x13c
};
void* __cdecl GetActivePlanet();                                       // 0x1021260
void __cdecl GetPropertyAsUint32(IRefCount* list, uint32_t id, uint32_t* out);   // 0x4af210

// --------------------------------------------------------------------------------------------------
// The functions.
// --------------------------------------------------------------------------------------------------

// @ 0x00e29c80
void SP::cSPUINewProgressBar::Init()
{
    IPropertyManager* pm = PropertyManager();

    if (mTuningProps) {
        IRefCount* old = mTuningProps;
        mTuningProps = 0;
        old->Release();
    }
    if (pm->GetPropertyList(0x5c770db7, &mTuningProps))
        gPropertyListCopier.do_copy(mTuningProps);

    mpAnimator = new ("UI/cUINewProgressBar/ProgressCursorAnimator", 0, 0, 0, 0) cSPUIAnimator;

    IWindow* level = mGlobalUILayout->FindWindowByID(0x51b54c0, true);
    if (level) {
        IWindow* marker = mGlobalUILayout->FindWindowByID(0x51b5168, true);
        if (marker) {
            const float* markerArea = marker->GetArea();
            const float* levelArea = level->GetArea();
            marker->SetPosition(levelArea[0], markerArea[1]);
        }
        IWindow* fill = mGlobalUILayout->FindWindowByID(0x51b7e48, true);
        if (fill) {
            const float* fillArea = fill->GetArea();
            float width = fillArea[2] - fillArea[0];
            const float* levelArea2 = level->GetArea();
            UpdateLevelWindows(level, 0.0f, levelArea2[0], width, true);
        }
    }
}

// @ 0x00e2a550
bool cSPUIRolloverCivCityVehicle::Init(uint32_t arg)
{
    mFieldA8 = 0;
    if (cSPUIPropertyLayout::Init()) {
        IWindow* root = GetRootWindow();
        if (!root->GetParent()) {
            cSPUILayoutManager* manager = SPUIHelpers::GetLayoutManager(arg);
            IWindow* main = manager->GetWorldMainWindow();
            main->AddChild(root);
        }
        return true;
    }
    return false;
}

// @ 0x00e2a5b0
void UI::CursorAttachment::Dispose()
{
    if (mFlag44) {
        IWindow* root = GetRootWindow();
        IWindow* parent = root->GetParent();
        IWindow* root2 = GetRootWindow();
        parent->RemoveChild(root2);
    }
    func24h();
}

// @ 0x00e2a5f0
uint32_t cSPUIRolloverPropertyFlags::GetEventFlags()
{
    return GetEventMask() | 0x48c;
}

// @ 0x00e2a600
void cSPUICursorLayoutWidget::SetShown(bool shown)
{
    mFlagA4 = shown;
    IWindow* window = mLayout.FindWindowByID(0x46adf86, true);
    window->SetVisible(1, mFlagA4);
}

// @ 0x00e2a640
cSPUIRolloverCivCityVehicleCtor* cSPUIRolloverCivCityVehicleCtor::Initialize()
{
    BaseConstruct();
    mpVftable00 = gVftblCursorAttachment00;
    mpVftable04 = gVftblCursorAttachment04;
    mpVftable78 = gVftblCursorAttachment78;
    SetKey(L"RolloverCivCityVehicle", 0x40464100);
    SetRootWindowId(0x199a7de);
    return this;
}

// @ 0x00e2a690
uint32_t cSPUIRolloverVehicleFlags::GetEventFlags()
{
    return GetEventMask() | 0x400;
}

// @ 0x00e2a6a0
uint32_t cSPUIRolloverCityFlags::GetEventFlags()
{
    return GetEventMask() | 0x40c;
}

// @ 0x00e2a6c0
void cSPUIRolloverRelationship::HideRelationshipRollover()
{
    if (mFlag44) {
        IWindow* root = GetRootWindow();
        root->SetVisible(1, false);
        HideRollover();
    }
}

// @ 0x00e2a760
int __cdecl CountRolloverRows(cSPUIPropertyLayout* self)
{
    int i = 0;
next:
    {
        IWindow* root = self->GetRootWindow();
        IWindow* row = root->FindWindowByID2((uint32_t)(i + 0x4d18700), true);
        if (!row)
            return i;
        if (!row->FindChildByID(0xf15f4bd))
            return i;
        i++;
    }
    goto next;
}

// @ 0x00e2a7b0
void cSPUIRolloverCivCityHall::SetSpecialtyIcon(uint32_t icon)
{
    float area[4];

    mLayout.FindWindowByID(0x2cf2f30, true)->SetVisible(1, false);
    mLayout.FindWindowByID(0x2cf2f34, true)->SetVisible(1, false);
    mLayout.FindWindowByID(0x2cf2f38, true)->SetVisible(1, false);

    if (icon) {
        IWindow* iconWindow = mLayout.FindWindowByID(icon, true);
        if (iconWindow) {
            iconWindow->SetVisible(1, true);
            IWindow* image = mLayout.FindWindowByID(0x2cf2f44, true);
            if (!image)
                return;
            const float* imageArea = image->GetArea();
            area[0] = imageArea[0];
            area[1] = imageArea[1];
            area[2] = imageArea[2];
            area[3] = imageArea[3];
            const float* iconArea = iconWindow->GetArea();
            area[0] = iconArea[2] + 3.0f;
            image->SetAreaB(area);
            return;
        }
    }

    IWindow* image = mLayout.FindWindowByID(0x2cf2f44, true);
    if (!image)
        return;
    const float* imageArea = image->GetArea();
    area[0] = imageArea[0];
    area[1] = imageArea[1];
    area[2] = imageArea[2];
    area[3] = imageArea[3];
    area[0] = 4.0f;
    image->SetAreaB(area);
}

// @ 0x00e2a920
void cSPUIRolloverCivCityHall::calculate_layout()
{
    float extend = gSPUIRowPad;

    IWindow* header = mLayout.FindWindowByID(0x4b1f8ae, true);
    header->SetVisible(1, mFlagA6);
    if (mFlagA6) {
        const float* headerArea = header->GetAreaRaw();
        extend = (headerArea[3] - headerArea[1]) + gSPUIRowPad + gSPUIRowPad;
    }

    IWindow* bar = mLayout.FindWindowByID(0x4b1f8bd, true);
    const float* barArea = bar->GetAreaRaw();
    float barRect[4];
    barRect[0] = barArea[0];
    barRect[1] = barArea[1];
    barRect[2] = barArea[2];
    barRect[3] = barArea[3];
    barRect[1] = extend;
    bar->SetAreaA(barRect);

    IWindow* root = GetRootWindow();
    const float* rootArea = root->GetArea();
    float rootRect[4];
    rootRect[0] = rootArea[0];
    rootRect[1] = rootArea[1];
    rootRect[2] = rootArea[2];
    rootRect[3] = (extend + gSPUIRowHeight) + gSPUIRowPad + rootArea[1];
    root->SetAreaA(rootRect);
}

// @ 0x00e2ab10
bool cSPUIRolloverCivCityHall::SetPrimaryPopulationGroupId(uint32_t id)
{
    mKey9c = id;
    RBNode* found;
    mTree.find(&found, &mKey9c);
    if (found != mTree.mEndNode) {
        found->mField1c = 0;
        mValue98 = found->mField20;
        for (RBNode* node = mTree.mRoot; node != mTree.mEndNode; ) {
            if (node != found) {
                mCounter94++;
                node->mField1c = mCounter94;
                break;
            }
            node = RBTreeIncrement(node);
        }
    }

    IWindow* window = mLayout.FindWindowByID(0x2cf324c, true);
    if (window) {
        IWindow* child = window->FindChildByID(0xeeee8218);
        if (child)
            child->SetShadeColor(mValue98);
    }
    return true;
}

// @ 0x00e2abc0
void cSPUIRolloverCivCityHall::UpdatePlacement()
{
    if (GetCurrentGameMode() != 0x1654c05)
        return;

    mLayout.FindWindowByID(0x6830fd0, true)->SetVisible(1, false);
    IWindow* window = mLayout.FindWindowByID(0x6830fd8, true);
    uint32_t colour = 0xffffffff;
    if (GetActivePlanet() != 0) {
        AutoRefCount props;
        cActivePlanet* planet = (cActivePlanet*)GetActivePlanet();
        cPlanetOwner* owner = planet->mOwner;
        if (owner) {
            IPropertyManager* pm = PropertyManager();
            props.Reset();
            pm->AddProperty(*owner->GetObject(), 0x34d97fa, &props.mpObject);
            GetPropertyAsUint32(props.mpObject, 0x58cbb75, &colour);
        }
    }
    window->SetShadeColor(colour | 0xff000000);
    window->SetVisible(1, true);
}

// @ 0x00e2acc0
void cSPUIRolloverCivCityHall::read_properties()
{
    AutoRefCount props;
    IPropertyManager* pm = PropertyManager();
    props.Reset();
    if (pm->GetPropertyList(0x5c770db7, &props.mpObject)) {
        if (props.mpObject) {
            cPropertyList* list = (cPropertyList*)props.mpObject;
            cProperty* prop;
            if (list->GetProperty(0x1b53f12, &prop) && prop->mType == 9)
                mValueA0 = (uint32_t)*prop->GetInt();
        }
    }
}
