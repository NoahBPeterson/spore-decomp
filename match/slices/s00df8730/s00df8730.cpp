// Slice s00df8730: galaxy game-entry screen per-frame update (vtable 0x0147f000 slot 5).
// /O2 /arch:SSE module (movss float copies, x87 compares).
#include "types.h"

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(void* pCount);
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);
#pragma intrinsic(sqrt)
extern "C" double __cdecl sqrt(double);

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
    Vector3 operator+(const Vector3& o) const
    {
        Vector3 r(*this);
        r.x += o.x;
        r.y += o.y;
        r.z += o.z;
        return r;
    }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
};

struct BoundingBox {
    Vector3 lower;
    Vector3 upper;
    BoundingBox(const Vector3& lo, const Vector3& hi) : lower(lo), upper(hi) {}
};

struct Matrix3 {
    float m[3][3];
    Vector3 operator*(const Vector3& v) const
    {
        return Vector3(v.z * m[2][0] + v.y * m[1][0] + v.x * m[0][0],
                       v.z * m[2][1] + v.y * m[1][1] + v.x * m[0][1],
                       v.z * m[2][2] + v.y * m[1][2] + v.x * m[0][2]);
    }
};

struct Transform {
    uint16_t mFlags;
    uint16_t mRefCount;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;
    Transform();                                           // 0x00409930
    Transform(const Vector3& offset, const Matrix3& rot)
        : mFlags(4), mRefCount(1), mOffset(offset), mfScale(1.0f), mRotation(rot) {}
};

namespace SP {
    Vector3 normalized_safe(const Vector3& v);            // 0x00449c20
    struct cSporeGuide { uint32_t pad[7]; bool mbActive; };  // +0x1c
    cSporeGuide* SporeGuide();                             // 0x00401040
}
Vector3 RandomPointInBox(const BoundingBox& box);          // 0x00df5f50
void GetScaledMouse(float* x, float* y);                   // 0x00804ed0

struct RandomLinearCongruential {
    uint32_t RandomUint32Uniform(uint32_t nLimit);         // 0x00a68fb0
    double RandomDoubleUniform();                          // 0x009360d0
    double RandomDoubleUniform(double limit)
    {
        double r = RandomDoubleUniform() * limit;
        if (r >= limit)
            return limit;
        if (r < 0.0)
            return 0.0;
        return r;
    }
};
extern RandomLinearCongruential g_SPRandom;                // 0x01601760

struct Stopwatch {
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    void Stop();                                           // 0x0093a2e0
    uint64_t GetElapsedTime() const;                       // 0x0093a3a0
    bool IsRunning() const { return mnStartTime != 0; }
    void Reset() { mnStartTime = 0; mnTotalElapsedTime = 0; }
    float GetElapsedTimeFloat() const
    {
        return (float)(int64_t)GetElapsedTime() * mfStopwatchCyclesToUnitsCoefficient;
    }
};

struct LimitStopwatch : Stopwatch {
    uint64_t mnEndTime;
    void SetTimeLimit(uint32_t nLimit, bool bStartImmediately);   // 0x0093a480
    bool IsTimeUp() const
    {
        uint64_t t;
        QueryPerformanceCounter(&t);
        return (int64_t)(mnEndTime - t) < 0;
    }
};

struct cIVisualEffect {
    virtual int AddRef();
    virtual int Release();
    virtual bool Start(int flags);                 // 0x08
    virtual bool Stop(int flags);                  // 0x0c
    virtual bool IsRunning();                      // 0x10
    virtual void v14();
    virtual void SetTransform(const Transform& t); // 0x18
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void SetVisible(bool b);               // 0x30
};

template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
typedef AutoRefCount<cIVisualEffect> EffectRef;

struct cIEffectsWorld {
    virtual void v00();
    virtual void v04();
    virtual bool CreateVisualEffect(uint32_t instanceId, int flags, EffectRef& out);   // 0x08
};

// out-of-line EASTL helpers
EffectRef* copy(EffectRef* first, EffectRef* last, EffectRef* result);   // 0x0042f530

inline void* operator new(unsigned int, void* p) { return p; }

template<class T> struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    void* mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    T& back() { return *(mpEnd - 1); }
    bool empty() const { return mpBegin == mpEnd; }
    void DoInsertValue(T* position, const T& value);
    void DestroyRange(T* first, T* last);                  // 0x00de5ee0
    void Resize(int n);                                    // 0x00de9e20
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    T* erase(T* first, T* last)
    {
        memmove(first, last, (unsigned int)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    T* erase(T* position)
    {
        if ((position + 1) < mpEnd)
            copy(position + 1, mpEnd, position);
        --mpEnd;
        mpEnd->~T();
        return position;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

struct IWindow {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* v0c(uint32_t id);                        // 0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void SetVisible(bool b);                       // 0x30
    virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetFlag(int flag, bool value);            // 0x7c
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4();
    virtual void SetSomething(int a, int b);               // 0xb8
};

class cSPUILayout { public:
    IWindow* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0
    void Shutdown(uint32_t flags);                         // 0x00811ad0
    uint32_t pad[3];
};

class cSPUIGlobalUI { public:
    void SetVisibility(bool visible);                      // 0x00e01350
};

struct cGameUIData {
    uint32_t pad[8];
    struct Anim { void Update(uint32_t ms); } mAnim;  // 0x00e21040 (member at +0x20)
    uint32_t pad2[4];
    IWindow* mpWindow;                                     // +0x34
};

struct cGameInfo {                                         // size 0xbc (retail)
    uint32_t pad[0x20];
    Vector3 mStarLocationAbsolute;                         // +0x80
    int mField8c;                                          // +0x8c
    uint32_t pad90[6];
    int mType;                                             // +0xa8
    bool mbSaved;                                          // +0xac
    bool mbVisibleInGalaxy;                                // +0xad
    uint16_t pad_ae;                                       // +0xae
    uint32_t mFieldb0;                                     // +0xb0
    uint32_t mFieldb4;                                     // +0xb4
    cGameUIData* mpUIData;                                 // +0xb8
};

struct cGGECamera {
    void GetTransform(Transform& t);                       // 0x00dde590
    Transform GetTransform() { Transform t; GetTransform(t); return t; }
    void SetMouseActive(bool b);                           // 0x00dde5b0
};

struct cGalaxyGameEntryUI {                                // global at 0x016a1344
    uint32_t m04;                                          // +0x04 (passed to FUN_00df76c0)
    uint32_t pad0[0x3d];
    int mf8;                                               // +0xf8
    int mfc;                                               // +0xfc
    uint32_t pad1[0x11];
    cSPUILayout mLayout;                                   // +0x144
    uint32_t pad2[3];
    cIEffectsWorld* mpEffectsWorld;                        // +0x15c
    uint32_t pad3[9];
    cSPUIGlobalUI* mpGlobalUI;                             // +0x184
    uint32_t pad4[4];
    cGGECamera* mpCamera;                                  // +0x198
    uint32_t pad5[0xf];
    sp_vector<IWindow*> mWindows;                          // +0x1d8
    uint32_t pad6[2];
    bool mb1f0;                                            // +0x1f0
    char pad7[0x80];
    bool mb271;                                            // +0x271
    void Refresh();                                        // 0x00de5260
    void ShowPanel(int which);                             // 0x00de53d0
};
extern cGalaxyGameEntryUI* g_pGalaxyGameEntryUI;           // 0x016a1344

struct cGalaxyStarLinks {
    uint32_t GetLinkCount(int kind);                       // 0x00dda060
    uint32_t GetPulseCount();                              // 0x00dda380
    void AddLongLink(Vector3* a, Vector3* b);              // 0x00ddcad0
    void AddLink(Vector3* a, Vector3* b, bool c, bool d);  // 0x00ddc910
    void AddPulse();                                       // 0x00ddcdc0
};
cGalaxyStarLinks* GalaxyStarLinks();                       // 0x00dd9190

extern float g_fLinkChance;                                // 0x015a41e0
extern float g_fNoticeTime;                                // 0x016a0ef8
extern Matrix3 g_galaxyRotation;                           // 0x016a1674
extern Vector3 g_galaxyOffset;                             // 0x016a1698

class cGalaxyGameEntryScreen {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void Update(float dt);                         // 0x14
    virtual void v18(); virtual void v1c();
    virtual void OnMouseMove(float x, float y, int flags); // 0x20
    virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64();
    virtual void UpdateRollover();                         // 0x68

    void ClearGames();                                     // 0x00df9510
    void BuildGames();                                     // 0x00df9230
    void ResetGames();                                     // 0x00df95d0
    void LoadGameRange(cGameInfo* first, int count);        // 0x00df7ce0
    void LoadSavedGames(cGameInfo* first, int count);       // 0x00df7f60
    void SetupRolloverStarEffects();                        // 0x00df8330

    sp_vector<cGameInfo> mGames;                           // +0x08
    uint32_t pad18[2];
    Stopwatch mNoticeTimer;                                // +0x20
    Stopwatch mHintTimer;                                  // +0x38
    bool mbWaitForGuide;                                   // +0x50
    sp_vector<uint32_t> mCandidates;                       // +0x54
    uint32_t pad64;
    int mHighlightIndex;                                   // +0x68
    uint32_t pad6c;
    LimitStopwatch mHighlightTimer;                        // +0x70
    sp_vector<EffectRef> mHighlightEffects;                // +0x90
};

inline void UpdateMouse(cGalaxyGameEntryScreen* self)
{
    float x, y;
    GetScaledMouse(&x, &y);
    self->OnMouseMove(x, y, 0);
}

// @ 0x00df8730
void cGalaxyGameEntryScreen::Update(float dt)
{
    if (GalaxyStarLinks()->GetLinkCount(1) < 5
        && g_SPRandom.RandomDoubleUniform(g_fLinkChance) <= 1.0)
    {
        if (g_SPRandom.RandomUint32Uniform(5) < 3) {
            uint32_t a = g_SPRandom.RandomUint32Uniform(mGames.size());
            uint32_t b;
            do {
                b = g_SPRandom.RandomUint32Uniform(mGames.size());
            } while (b == a);
            Vector3 posA(mGames[a].mStarLocationAbsolute);
            Vector3 posB(mGames[b].mStarLocationAbsolute);
            if ((posA - posB).Length() > 200.0f)
                GalaxyStarLinks()->AddLongLink(&posA, &posB);
            else
                GalaxyStarLinks()->AddLink(&posA, &posB, true, true);
        } else {
            Vector3 far = (g_SPRandom.RandomUint32Uniform(2) == 0
                ? SP::normalized_safe(g_pGalaxyGameEntryUI->mpCamera->GetTransform().mOffset)
                : SP::normalized_safe(RandomPointInBox(
                      BoundingBox(Vector3(-1.0f, -1.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f))))) * 1500.0f;
            uint32_t i = g_SPRandom.RandomUint32Uniform(mGames.size());
            Vector3 pos(mGames[i].mStarLocationAbsolute);
            if (g_SPRandom.RandomUint32Uniform(2) == 0)
                GalaxyStarLinks()->AddLink(&far, &pos, false, true);
            else
                GalaxyStarLinks()->AddLink(&pos, &far, true, false);
        }
    }

    if (g_pGalaxyGameEntryUI->mb1f0 && GalaxyStarLinks()->GetPulseCount() < 15)
        GalaxyStarLinks()->AddPulse();

    IWindow* w = g_pGalaxyGameEntryUI->mLayout.FindWindowByID(0x615a5ff, true);
    if (w)
        w->SetFlag(1, g_pGalaxyGameEntryUI->mfc == 0);
    g_pGalaxyGameEntryUI->mpGlobalUI->SetVisibility(g_pGalaxyGameEntryUI->mfc == 0);
    g_pGalaxyGameEntryUI->Refresh();

    if (g_pGalaxyGameEntryUI->mf8)
        UpdateMouse(this);

    for (uint32_t i = 0; i < mGames.size(); ++i) {
        if (mGames[i].mpUIData)
            mGames[i].mpUIData->mAnim.Update((uint32_t)(dt * 1000.0f));
    }

    if (g_pGalaxyGameEntryUI->mf8) {
        UpdateMouse(this);
        g_pGalaxyGameEntryUI->mpCamera->SetMouseActive(true);
    } else
        g_pGalaxyGameEntryUI->mpCamera->SetMouseActive(false);
    if (g_pGalaxyGameEntryUI->mf8)
        UpdateRollover();

    if (g_pGalaxyGameEntryUI->mfc) {
        UpdateRollover();
        g_pGalaxyGameEntryUI->mpGlobalUI->SetVisibility(false);
    } else if (!g_pGalaxyGameEntryUI->mb1f0) {
        g_pGalaxyGameEntryUI->mpGlobalUI->SetVisibility(true);
    }

    if (mNoticeTimer.IsRunning() && mNoticeTimer.GetElapsedTimeFloat() > g_fNoticeTime) {
        mNoticeTimer.Stop();
        mNoticeTimer.Reset();
    }

    if (g_pGalaxyGameEntryUI->mb271) {
        if (!mHighlightTimer.IsRunning() || mHighlightTimer.IsTimeUp()) {
            if (!mHighlightEffects.empty())
                mHighlightEffects.back()->Stop(0);

            for (int i = 0; i < mGames.size(); ++i) {
                if (i != mHighlightIndex && !mGames[i].mbSaved && mGames[i].mbVisibleInGalaxy)
                    mCandidates.push_back(i);
            }

            uint32_t n = mCandidates.size();
            if (n > 0) {
                mHighlightIndex = mCandidates[g_SPRandom.RandomUint32Uniform(n)];
                cGameInfo& game = mGames[mHighlightIndex];
                EffectRef effect;
                if (g_pGalaxyGameEntryUI->mpEffectsWorld->CreateVisualEffect(0xdaae81f8, 0, effect)) {
                    Transform t(g_galaxyOffset + g_galaxyRotation * game.mStarLocationAbsolute,
                                g_galaxyRotation);
                    effect->SetTransform(t);
                    effect->Start(0);
                    mHighlightEffects.push_back(effect);
                    mHighlightTimer.SetTimeLimit(3000, true);
                }
            } else {
                mHighlightIndex = -1;
            }
            mCandidates.clear();
        }
    }

    bool noticeShowing = mNoticeTimer.IsRunning();
    bool panelOpen = g_pGalaxyGameEntryUI->mfc != 0;
    IWindow* highlighted;
    if (mHighlightIndex > 0)
        highlighted = mGames[mHighlightIndex].mpUIData->mpWindow;
    else
        highlighted = 0;

    for (uint32_t i = 0; i < g_pGalaxyGameEntryUI->mWindows.size(); ++i) {
        IWindow* win = g_pGalaxyGameEntryUI->mWindows[i];
        win->SetVisible(noticeShowing || panelOpen || win == highlighted);
    }

    for (uint32_t i = 0; i < mHighlightEffects.size(); ) {
        cIVisualEffect* e = mHighlightEffects[i];
        if (e->IsRunning()) {
            e->SetVisible(noticeShowing || panelOpen);
            ++i;
        } else {
            mHighlightEffects.erase(mHighlightEffects.mpBegin + i);
        }
    }

    if (mbWaitForGuide && !SP::SporeGuide()->mbActive) {
        mbWaitForGuide = false;
        if (g_pGalaxyGameEntryUI->mfc) {
            g_pGalaxyGameEntryUI->ShowPanel(0);
            g_pGalaxyGameEntryUI->ShowPanel(1);
        }
    }

    if (mHintTimer.IsRunning() && mHintTimer.GetElapsedTimeFloat() > 1000.0f) {
        IWindow* hint = g_pGalaxyGameEntryUI->mLayout.FindWindowByID(0x806aa00, true);
        if (hint)
            hint->SetFlag(1, true);
        mHintTimer.Stop();
        mHintTimer.Reset();
    }
}

// ---------------------------------------------------------------------------
// Game list rebuild (this+0x08 cGameInfo vector) and per-game UI data block.
// ---------------------------------------------------------------------------

extern char g_vtblGGEUIData[];                             // 0x0147eb60
extern void* g_pGameRolloverLayout;                        // 0x016a0d08
extern bool g_bGGEUIDataReady;                             // 0x016a0f88

struct cBaseCtor { void Construct(); };                    // 0x00810000

void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void GameFree(void* p);                                    // 0x00f47380

namespace SP {
struct cString {
    uint32_t mData[5];                                          // 0x14 bytes (retail)
    cString(uint32_t id, uint32_t name, const wchar_t* text);   // 0x006b5770
    ~cString();                                                 // 0x006b5240
    const void* GetText(int start, ...);                        // 0x006b55c0
};
}
void SetTooltipText(IWindow* window, const void* text);     // 0x00806de0

struct cGGEWindowSub {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10();
    virtual void SetValue(int value);                      // +0x14
};

struct cGGEWindowEx {
    uint32_t pad[0x83];                                    // 0x000 .. 0x20b
    cGGEWindowSub mSub;                                    // +0x20c
};

struct cGameUIDataBlock;

struct cGGEGameUIDataChild {
    virtual void v00();
    virtual void v04();                                    // destroy
    virtual void v08(int value);
    virtual void v0c(int value);
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44();
    virtual void Setup(int kind, cGameInfo** ppOwner, int flags);   // +0x48
};

struct cGameUIDataBlock {                                  // 0x90 (retail)
    uint32_t pad00[6];                                     // +0x00
    void* mpVtbl2;                                         // +0x18
    int m1c;                                               // +0x1c
    uint32_t m20;                                          // +0x20
    uint32_t m24;                                          // +0x24
    uint32_t m28;                                          // +0x28
    uint32_t m2c;                                          // +0x2c
    cGameInfo* mpGameInfo;                                 // +0x30
    cGGEGameUIDataChild* mpChild;                          // +0x34
    uint16_t* mpVecBegin;                                  // +0x38
    uint16_t* mpVecEnd;                                    // +0x3c
    uint16_t* mpVecCapacity;                               // +0x40
    void* mpVecAllocator;                                  // +0x44
    uint16_t* mpInlineBegin;                               // +0x48
    uint16_t mInline[0x20];                                // +0x4c
    uint32_t m8c;                                          // +0x8c

    cGameUIDataBlock(cGameInfo* info)
    {
        ((cBaseCtor*)this)->Construct();
        mpVtbl2 = g_vtblGGEUIData;
        m20 = 0;
        m24 = 0;
        m28 = 0;
        m2c = 0;
        mpGameInfo = info;
        mpChild = 0;
        mpInlineBegin = mInline;
        mpVecCapacity = mpInlineBegin + 0x20;
        mpVecEnd = mInline;
        mpVecBegin = mInline;
        mInline[0] = 0;
        m8c = 0;
        m1c = (int)info;
    }
};

struct cGameUIDataBlockOps {
    void InitRollover(void* layout, void* owner);          // 0x00df76c0
    void Destroy();                                        // 0x00df82d0
};

// @ 0x00df9190
void FUN_00df9190(cGameUIDataBlock* self)
{
    if (self->mpChild)
        self->mpChild->v0c(1);
    cGGEGameUIDataChild* child = self->mpChild;
    if (child) {
        self->mpChild = 0;
        child->v04();
    }
    if (self->mpChild) {
        self->mpChild->v08(0);
        cGameInfo* owner = self->mpGameInfo;
        self->mpChild->Setup(9, &owner, 1);
    }
    self->m2c = 0;
    IWindow* w = ((cSPUILayout*)self)->FindWindowByID(0x46ea4b6, true);
    if (w)
        w->SetSomething(0x37ac490, 0);
    ((cSPUILayout*)self)->Shutdown(1);
    ((cGameUIDataBlockOps*)self)->Destroy();
    GameFree(self);
}

// @ 0x00df9510
void cGalaxyGameEntryScreen::ClearGames()
{
    sp_vector<cGameInfo>& games = mGames;
    uint32_t count = games.size();
    for (uint32_t i = 0; i < count; ++i) {
        if (games[i].mpUIData)
            FUN_00df9190((cGameUIDataBlock*)games[i].mpUIData);
        games[i].mFieldb4 = 0;
        games[i].mpUIData = 0;
    }
    cGameInfo* first = games.mpBegin;
    cGameInfo* last = games.mpEnd;
    cGameInfo* dst = first;
    for (cGameInfo* p = last; p != games.mpEnd; ++p, ++dst)
        *dst = *p;
    games.DestroyRange(dst, games.mpEnd);
    games.mpEnd -= (last - first);
}

// @ 0x00df9230
void cGalaxyGameEntryScreen::BuildGames()
{
    uint32_t count = mGames.size();
    if (count != 0) {
        for (uint32_t i = 0; i != count; ++i) {
            if (mGames[i].mpUIData)
                FUN_00df9190((cGameUIDataBlock*)mGames[i].mpUIData);
            cGameInfo* g = &mGames[i];
            mGames[i].mpUIData = (cGameUIData*)new ("UI/GGE_game_ui_data", 0, 0, 0, 0)
                cGameUIDataBlock(g);
            ((cGameUIDataBlockOps*)mGames[i].mpUIData)->InitRollover(
                g_pGameRolloverLayout,
                g_pGalaxyGameEntryUI ? (void*)((int)g_pGalaxyGameEntryUI + 4) : 0);
            if (mGames[i].mbSaved) {
                int n = 0;
                const wchar_t* text = (const wchar_t*)0x67735d4;
                switch (mGames[i].mType) {
                case 1:
                    n = 1;
                    break;
                case 2:
                    n = 2;
                    break;
                case 4:
                    n = 3;
                    break;
                case 5:
                    text = (const wchar_t*)0x67735d5;
                    n = 4;
                    break;
                }
                IWindow* win = ((cSPUILayout*)mGames[i].mpUIData)->FindWindowByID(0x26e0001, true);
                if (win) {
                    void* sub = win->v0c(0x106f146);
                    if (sub)
                        ((cGGEWindowEx*)sub)->mSub.SetValue(n);
                }
                win = ((cSPUILayout*)mGames[i].mpUIData)->FindWindowByID(0x26e0002, true);
                if (win) {
                    void* sub = win->v0c(0x106f146);
                    if (sub)
                        ((cGGEWindowEx*)sub)->mSub.SetValue(n);
                }
                if (!g_bGGEUIDataReady) {
                    win = ((cSPUILayout*)mGames[i].mpUIData)->FindWindowByID(0x3c4925e, true);
                    if (win) {
                        SP::cString text2(0x2b7a0311, (uint32_t)text, 0);
                        SetTooltipText(win, text2.GetText(-1, true));
                    }
                }
            }
            if (mGames[i].mField8c == 3) {
                IWindow* win = ((cSPUILayout*)mGames[i].mpUIData)->FindWindowByID(0x60a1102, true);
                if (win)
                    win->SetFlag(1, true);
                win = ((cSPUILayout*)mGames[i].mpUIData)->FindWindowByID(0x60a1103, true);
                if (win)
                    win->SetFlag(1, true);
                win = ((cSPUILayout*)mGames[i].mpUIData)->FindWindowByID(0x375408c, true);
                if (win)
                    win->SetFlag(2, false);
                win = ((cSPUILayout*)mGames[i].mpUIData)->FindWindowByID(0x5944088, true);
                win->SetFlag(1, false);
            }
        }
    }
}

struct cStarManagerList {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cStarManager {
    uint32_t pad[0x3c];
    cStarManagerList mList;                                // +0xf0
    cStarManagerList* QueryList();                         // 0x00ba6300
};

cStarManager* StarManager();                               // 0x00b3d2a0

// @ 0x00df95d0
void cGalaxyGameEntryScreen::ResetGames()
{
    ClearGames();
    int saved = StarManager()->mList.size();
    cStarManagerList* q = StarManager()->QueryList();
    int added = (int)(q->mpEnd - q->mpBegin);
    int total = saved + added;
    mGames.Resize(total);
    LoadGameRange(mGames.mpBegin + saved, total - saved);
    LoadSavedGames(mGames.mpBegin, saved);
    BuildGames();
    SetupRolloverStarEffects();
}
