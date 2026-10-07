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
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void SetVisible(bool b);                       // 0x30
    virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetFlag(int flag, bool value);            // 0x7c
};

struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0
    uint32_t pad[3];
};

struct cSPUIGlobalUI {
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
    uint32_t pad2[8];
    bool mbSaved;                                          // +0xac
    bool mbVisibleInGalaxy;                                // +0xad
    uint32_t pad3[2];
    cGameUIData* mpUIData;                                 // +0xb8
};

struct cGGECamera {
    void GetTransform(Transform& t);                       // 0x00dde590
    Transform GetTransform() { Transform t; GetTransform(t); return t; }
    void SetMouseActive(bool b);                           // 0x00dde5b0
};

struct cGalaxyGameEntryUI {                                // global at 0x016a1344
    uint32_t pad0[0x3e];
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
