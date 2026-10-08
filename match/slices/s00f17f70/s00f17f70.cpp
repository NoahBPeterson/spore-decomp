// Slice s00f17f70: per-frame Update of a level-progress UI panel (0x00f17f70, 1773 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (scalar SSE compares, x87 float copies through references).
//
// The panel animates a value (mCur) towards a target (mEnd): a count-down delay, the palette
// and updater ticks, enabling/disabling child windows by state, then in state 8 starts the
// animation, and in state 3 advances it (timer, easing ratio, rect interpolation, number
// strings) and, when a new level is reached, swaps in the level image and plays the level-up.
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

typedef unsigned int uint;

// ----------------------------------------------------------------------------- UI stubs
struct IWin {
    PV8 PV4 PV2
    virtual float* GetRect();                        // +0x38
    PV8 PV4
    virtual void SetRect(const float* rect);         // +0x6c
    PV2 PV
    virtual void SetVisible(int a, bool b);          // +0x7c
    virtual void SetText(const wchar_t* text);       // +0x80
};
struct IWinContainer {
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV4
    virtual IWin* FindChild(uint id, int recurse);   // +0xf0
};
struct Layout {
    IWin* FindWindowByID(uint id, int recurse);      // 0x008105b0
};

struct IAudioSystem {
    PV8
    virtual int Query();                             // +0x20
};

struct GlobalState {
    uint pad00[0x74 / 4];
    void* mpSub74;                                   // +0x74
    uint pad78[(0xd0 - 0x78) / 4];
    int mLevel;                                      // +0xd0
};
extern GlobalState* g_16c7aa4;                       // 0x016c7aa4

struct PaletteHolder {
    void Update(uint deltaMS);                       // 0x005c28b0 (cSPPaletteCategoryUI::Update)
};
struct Updater490 { void Update490(uint deltaMS); }; // 0x00ae8510
Updater490* GetUpdater490();                         // 0x00b3d490

void SetGlobalProperty(uint id, float value);                        // 0x005ca880 (cdecl)
void SetNumberString(int64_t value, wchar_t* buf, int cap);          // 0x00881ae0 (cdecl)
void SetImageFromLayout(IWin* win, Layout* layout, int id, int a);   // 0x00806a60 (cdecl)
IAudioSystem* GetSystemAT();                                         // 0x00a206f0
void KillSetiEffects(uint id, int audio);                            // 0x00435ed0 (cdecl)
int LevelFromValue(int v);                                           // 0x00eec580 (cdecl)
float LevelBaseValue();                                              // 0x00eec5b0
int FindFirstGE(int v);                                              // 0x00eec540 (cdecl)
void SpawnEffect(uint id, int a, uint* pos, uint* dir, int b, int level, uint* arr, int c);  // 0x00e39ab0 (cdecl)

struct SubA {
    uint pad00[0x18 / 4];
    PaletteHolder* mpPalette;                        // +0x18
    uint pad1c;
    void* mpField20;                                 // +0x20
    int  GetLevelData();                             // 0x00f12690
};
struct LevelData { int GetMaxLevel(); };             // 0x005943b0
struct SubB { int GetEffectContext(); };             // 0x00f3bcb0

struct Rect4 { float x, y, z, w; };

// eastl::min / max on references to float (b < a ? b : a)
inline const float& FMin(const float& a, const float& b) { return (b < a) ? b : a; }
inline const float& FMax(const float& a, const float& b) { return (a < b) ? b : a; }

class cSPUIProgress {
public:
    uint pad00[0x18 / 4];
    Layout* mpLayout;                                // +0x18
    uint pad1c[2];
    SubA* mpSubA;                                    // +0x24
    uint pad28[(0xbc - 0x28) / 4];
    float mTimer;                                    // +0xbc
    float mCur;                                      // +0xc0
    float mStart;                                    // +0xc4
    float mEnd;                                      // +0xc8
    float mNext;                                     // +0xcc
    int   mLevel;                                    // +0xd0
    int   mState;                                    // +0xd4
    uint  mDelay;                                    // +0xd8
    IWinContainer* mpWinA;                           // +0xdc
    IWinContainer* mpWinB;                           // +0xe0

    void StartNextAnimation();                       // 0x00f17870
    bool CheckFlag(int a);                           // 0x00f135b0

    void Update(uint deltaMS);
};

// @ 0x00f17f70
void cSPUIProgress::Update(uint deltaMS)
{
    if (mDelay > 0) {
        mDelay--;
        if (mDelay == 0)
            StartNextAnimation();
        return;
    }

    if (mpSubA->mpPalette)
        mpSubA->mpPalette->Update(deltaMS);
    GetUpdater490()->Update490(deltaMS);

    if (mpWinA) {
        bool active = (mState == 0 || mState == 9);
        bool levelUp = (g_16c7aa4->mLevel != 0);
        IWin* w = mpWinA->FindChild(0x7c79948, 1);
        if (w) w->SetVisible(1, active);
        w = mpWinA->FindChild(0x7c79940, 1);
        if (w) w->SetVisible(1, active);
        bool v = active && levelUp;
        w = mpWinA->FindChild(0x7c79c50, 1);
        if (w) w->SetVisible(1, v);
        w = mpWinB->FindChild(0x7c79c78, 1);
        if (w) w->SetVisible(1, active);
        v = active && CheckFlag(0);
        w = mpWinB->FindChild(0x7e20437, 1);
        if (w) w->SetVisible(1, v);
    }

    wchar_t text[0x20];

    if (mState == 8 && mpSubA->mpField20) {
        IWin* w = mpLayout->FindWindowByID(0x7c66c00, 1);
        if (w) w->SetVisible(1, false);
        if (mCur != mEnd) {
            mStart = mNext;
            float next = (float)LevelFromValue(mLevel + 1);
            mNext = next;
            float limit = next - 1.0f;
            mStart = FMin(mStart, limit);
            mTimer = LevelBaseValue();
            SetNumberString((int64_t)mNext, text, 0x20);
            w = mpLayout->FindWindowByID(0x7c7a088, 1);
            if (w) w->SetText(text);
            IWin* bar = mpLayout->FindWindowByID(0x7c7a310, 1);
            float* r = bar->GetRect();
            float rectCopy[4];
            rectCopy[0] = r[0];
            rectCopy[1] = r[1];
            rectCopy[2] = r[2];
            rectCopy[3] = r[3];
            rectCopy[1] = rectCopy[3];
            bar->SetRect(rectCopy);
            mState = 3;
        } else {
            mState = 0;
        }
    }

    if (mState != 3)
        return;

    if (!(0.0f < mTimer)) {
        mState = 0;
        return;
    }

    float one;
    float t;
    float v1;
    float q;
    float r2[4];
    float a[3];
    float dt = (float)deltaMS * 0.001f;
    one = 1.0f;
    float ratio = dt / mTimer;
    t = FMin(ratio, one);
    mTimer = mTimer - dt;
    SetGlobalProperty(0xf1472886, (mCur - mStart) / (mEnd - mStart));

    v1 = FMin(mEnd, mNext);
    IWin* ref = mpLayout->FindWindowByID(0x7c7a318, 1);
    float* ra = ref->GetRect();
    a[0] = ra[1];
    a[2] = ra[3];
    IWin* bar = mpLayout->FindWindowByID(0x7c7a310, 1);
    float* rb = bar->GetRect();
    r2[0] = rb[0];
    r2[1] = rb[1];
    r2[2] = rb[2];
    r2[3] = rb[3];
    q = 1.0f - (v1 - mStart) / (mNext - mStart);
    float zero = 0.0f;
    float p = FMax(q, zero);
    r2[1] = (((a[2] - a[0]) * p + a[0]) - r2[1]) * t + r2[1];
    bar->SetRect(r2);
    bool moved = (r2[1] != a[0]);
    IWin* w = mpLayout->FindWindowByID(0x7c7a088, 1);
    if (w) w->SetVisible(1, moved);

    float cur = (v1 - mCur) * t + mCur;
    mCur = cur;
    SetNumberString((int64_t)cur, text, 0x20);
    w = mpLayout->FindWindowByID(0x7c79fd8, 1);
    if (w) w->SetText(text);
    SetNumberString((int64_t)(mEnd - mCur), text, 0x20);
    w = mpWinA->FindChild(0x7c79d78, 1);
    if (w) w->SetText(text);

    int level = FindFirstGE((int)mCur);
    mLevel = level;
    if (level > ((LevelData*)mpSubA->GetLevelData())->GetMaxLevel()) {
        SetImageFromLayout(mpLayout->FindWindowByID(0x7eb2740, 1), mpLayout, level + 0x7f24ce0, -1);
        w = mpLayout->FindWindowByID(0x7db8991, 1);
        if (w) w->SetVisible(1, true);
        w = mpLayout->FindWindowByID(0x7c62860, 1);
        if (w) w->SetVisible(2, true);
        mState = 4;
        IAudioSystem* audio = GetSystemAT();
        KillSetiEffects(0x366f725d, audio ? audio->Query() : 0);
        if (g_16c7aa4->mLevel == 2) {
            SubB* sub = (SubB*)g_16c7aa4->mpSub74;
            uint arr[6] = {0, 0, 0, 0, 0, 0};
            uint v3[3] = {0, 0, 0};
            SpawnEffect(0xbbc2a4ef, 0, v3, &arr[3], 0, mLevel, arr, sub->GetEffectContext());
        }
    }
}
