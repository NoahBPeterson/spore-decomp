// slice s00708f40: cLightingWorld global-state evaluation + cLightingManager ctor.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include <new>
#include <xmmintrin.h>
#include "types.h"

extern int g_lm_vtbl0;
extern int g_lm_vtbl1;
extern int g_lm_vtbl2;
extern int g_lm_vtbl3;
extern int g_lm_vtbl4;
extern float g_lm_f0;   // 0x1535980
extern float g_lm_f1;   // 0x1535984
extern float g_lm_f2;   // 0x1535988

struct LightingManager {
    void Init();
};

// @ 0x00709c40
void LightingManager::Init()
{
    char* p = (char*)this;
    int z = 0;
    *(void**)(p + 4) = &g_lm_vtbl0;
    *(void**)(p + 8) = &g_lm_vtbl1;
    *(int*)(p + 0xc) = z;
    *(void**)(p) = &g_lm_vtbl2;
    *(void**)(p + 4) = &g_lm_vtbl3;
    *(void**)(p + 8) = &g_lm_vtbl4;
    *(int*)(p + 0x10) = 4;
    *(int*)(p + 0x14) = 0x10;
    *(int*)(p + 0x18) = z;
    *(int*)(p + 0x1c) = z;
    *(int*)(p + 0x20) = z;
    *(int*)(p + 0x34) = z;
    *(int*)(p + 0x38) = z;
    *(int*)(p + 0x3c) = z;
    void** q = (void**)(p + 0x30);
    *q = q;
    *(void**)(p + 0x34) = q;
    *(int*)(p + 0x38) = z;
    *(char*)(p + 0x3c) = (char)z;
    *(int*)(p + 0x40) = z;
    *(float*)(p + 0x48) = g_lm_f0;
    *(float*)(p + 0x4c) = g_lm_f1;
    *(float*)(p + 0x50) = g_lm_f2;
    *(int*)(p + 0x54) = z;
}

// ===========================================================================
// cLightingWorld: 0x00708f40 (not reconstructed) and 0x007094c0 ApplyConfig
// ===========================================================================
struct IEffect {                                                // ref-counted effect object
    virtual void AddRef();
    virtual void Release();
    virtual void Lock();                                        // +0x08
    virtual void Unlock();                                      // +0x0c
    virtual int GetValue();                                     // +0x10
};
#define PV(n) virtual void pv##n();
struct IEffectsManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual IEffect* GetEffect(uint32_t id, int arg);           // +0x8c
};
struct IMessageServer {
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void Post(uint32_t id, int a, int b);               // +0x14
};
namespace SP {
IEffectsManager* EffectsManager();                              // 0x0067ddd0
IMessageServer* MessageServer();                                // 0x0067dcc0
}

struct Vec3 {
    float x, y, z;
    Vec3(float a, float b, float c) { x = a; y = b; z = c; }
    Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
};
uint32_t __cdecl PackDirLight(Vec3 a, Vec3 b);                  // 0x007623f0
uint32_t __cdecl PackSunLight(Vec3 pos, Vec3 axis, float w);    // 0x007624c0

__declspec(align(16)) struct Vector4 {
    union {
        __m128 m;
        struct { float x, y, z, w; };
    };
    Vector4() {}
    Vector4(float a, float b, float c, float d) : m(_mm_set_ps(d, c, b, a)) {}
    Vector4(__m128 v) : m(v) {}
    Vector4(const Vector4& o) : m(o.m) {}
    Vector4& operator=(const Vector4& o) { m = o.m; return *this; }
};

static inline bool Bit(unsigned v, int n) { return (v >> n) & 1; }
static inline bool FlagSet(unsigned v, unsigned m) { return (v & m) != 0; }

struct U32Vec {                                                 // eastl::vector<uint32_t>
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    void DoInsertValue(uint32_t* pos, const uint32_t& v);       // 0x006ec4a0 (thiscall, ret 8)
    void push_back(uint32_t v)
    {
        if (mpEnd < mpCap)
            ::new (mpEnd++) uint32_t(v);
        else
            DoInsertValue(mpEnd, v);
    }
};

struct DirLight {                                               // 0x1c bytes at Config+8
    float px, py, pz;       // +0x00
    float k;                // +0x0c
    float dx, dy, dz;       // +0x10
};
struct Config {                                                 // object at cLightingWorld+0x10
    char pad00[4];
    uint32_t mFlags;        // +0x04 (bits 0-3: DirLight present, 4: ambient override, 5: sun)
    DirLight mLights[4];    // +0x08
    float m78, m7c, m80;    // +0x78
    float m84;              // +0x84 (sun scale)
    float m88;              // +0x88
    float vx, vy, vz;       // +0x8c
    uint32_t mAmbient[3];   // +0x98
    char padA4[0x18];
    Vector4* mAddBegin;     // +0xbc
    Vector4* mAddEnd;       // +0xc0
    char padC4[0xc];
    float mScale;           // +0xd0
    char padD4[8];
    float mEffectA;         // +0xdc
    float mEffectB;         // +0xe0
    char padE4[0x40];
    float mIntensity;       // +0x124
    bool HasLight(int mask) const { return (mFlags & mask) != 0; }
};

template <int STRIDE>
struct SlotDeque {                                              // spstl::slot_deque
    char** mpBegin;         // +0x00
    char** mpEnd;           // +0x04
    char pad08[0xc];
    int mLast;              // +0x14
    int mFirst;             // +0x18
    int Capacity() const { int n = (int)(mpEnd - mpBegin); return n * 128 + mLast - 0x7f; }
    char* Entry(unsigned idx) const { return mpBegin[idx >> 7] + (idx & 0x7f) * STRIDE; }
};

struct LightingInfo {                                           // at cLightingWorld+0x260
    char pad00;
    unsigned char mNumBands;    // +0x01
    char pad02[0xe];
    float mIntensity;           // +0x10
    char pad14[0x1c];
    Vector4 mCoeffs[25];        // +0x30
};

template <class T> static inline const T& MinRef(const T& a, const T& b) { return (a < b) ? a : b; }

extern float g_defAmbient[3];                                   // 0x015359f8
extern uint32_t g_cfgAmbient[3];                                // 0x01629884

struct cLightingWorld {
    char pad00[0x10];
    Config* mCfg;                   // +0x10
    char pad14[4];
    int mField18;                   // +0x18
    char pad1c[0x24];
    float mAmbient[3];              // +0x40
    U32Vec mDirLights;              // +0x4c
    char pad58[8];
    uint32_t mSunLight;             // +0x60
    uint8_t mFlags;                 // +0x64
    char pad65[3];
    float mPos[3];                  // +0x68
    float mScale;                   // +0x74
    float m[9];                     // +0x78
    char pad9c[0x44];
    bool mDirty;                    // +0xe0
    char pade1[0x16b];
    IEffect* mEffect;               // +0x24c
    int mEffectValue;               // +0x250
    char pad254[0xc];
    LightingInfo mInfo;             // +0x260
    char pad_[0x424 - 0x260 - sizeof(LightingInfo)];
    bool mEnabled;                  // +0x424
    char pad425[0x16b];
    bool mEnvFlag;                  // +0x590
    char pad591[3];
    SlotDeque<0x1f0> mEnvCache;     // +0x594
    char pad5b0[0x58];
    SlotDeque<0x1e0> mLocalCache;   // +0x608

    void PreUpdate();                                           // 0x007087a0
    void UpdateEnvLightSample(void* sample);                    // 0x00706170
    void UpdateLocalLightSample(int handle);                    // 0x00707370
    void ApplyGlobalState(int* state);
    void ApplyConfig();
};

// @ 0x00708f40
void cLightingWorld::ApplyGlobalState(int* state)
{
    (void)state;
}

// @ 0x007094c0
void cLightingWorld::ApplyConfig()
{
    PreUpdate();
    Config* cfg = mCfg;
    if (!cfg) {
        mAmbient[0] = g_defAmbient[0] * 0.1f;
        mAmbient[1] = g_defAmbient[1] * 0.1f;
        mAmbient[2] = g_defAmbient[2] * 0.1f;
        mDirLights.push_back(PackDirLight(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 0.7f, 1.0f)));
        mDirLights.push_back(PackDirLight(Vec3(-1.0f, -1.0f, -1.0f), Vec3(0.7f, 1.0f, 1.0f)));
    } else {
        ((uint32_t*)mAmbient)[0] = g_cfgAmbient[0];
        ((uint32_t*)mAmbient)[1] = g_cfgAmbient[1];
        ((uint32_t*)mAmbient)[2] = g_cfgAmbient[2];
        if (Bit(cfg->mFlags, 4)) {
            ((uint32_t*)mAmbient)[0] = cfg->mAmbient[0];
            ((uint32_t*)mAmbient)[1] = cfg->mAmbient[1];
            ((uint32_t*)mAmbient)[2] = cfg->mAmbient[2];
        }
        if (Bit(cfg->mFlags, 5)) {
            float a = cfg->m84;
            float vx = cfg->vx, vy = cfg->vy, vz = cfg->vz;
            float p = cfg->m7c * a;
            float q = a * cfg->m80;
            float last = cfg->m88;
            float r = a * cfg->m78;
            if (mFlags & 2) {
                float nx = (m[3] * vy + m[6] * vz) + m[0] * vx;
                float ny = (m[1] * vx + m[4] * vy) + m[7] * vz;
                float nz = (m[2] * vx + m[5] * vy) + m[8] * vz;
                vx = nx;
                vy = ny;
                vz = nz;
            }
            float s = mScale;
            mSunLight = PackSunLight(Vec3(s * vx + mPos[0], mPos[1] + vy * s, mPos[2] + s * vz), Vec3(r, p, q), last);
        }
        {
            unsigned i = 0;
            unsigned mask = 1;
            for (int off = 0; off < 0x70; off += 0x1c, i++, mask = (mask << 1) | (mask >> 31)) {
                if (i < 7 && FlagSet(mCfg->mFlags, mask)) {
                    Config* c = mCfg;
                    float n1 = -*(float*)((char*)c + off + 0x18);
                    float n2 = -*(float*)((char*)c + off + 0x1c);
                    float n3 = -*(float*)((char*)c + off + 0x20);
                    float d1 = *(float*)((char*)c + off + 0xc) - mAmbient[1];
                    float d2 = *(float*)((char*)c + off + 0x10) - mAmbient[2];
                    float d0 = *(float*)((char*)c + off + 8) - mAmbient[0];
                    float k = *(float*)((char*)c + off + 0x14);
                    float t = k * d1;
                    float u = k * d0;
                    float v = k * d2;
                    float ox = n1, oy = n2, oz = n3;
                    if (mFlags & 2) {
                        ox = (m[3] * n2 + m[6] * n3) + n1 * m[0];
                        oy = (m[1] * n1 + m[4] * n2) + m[7] * n3;
                        oz = (m[2] * n1 + m[5] * n2) + m[8] * n3;
                    }
                    mDirLights.push_back(PackDirLight(Vec3(ox, oy, oz), Vec3(u, t, v)));
                }
            }
        }
        cfg = mCfg;
        mDirty = mEnabled;
        mEnabled = cfg->mScale > 0.0f;
        cfg = mCfg;
        if (cfg->mAddBegin == cfg->mAddEnd) {
            mInfo.mNumBands = 0;
        } else {
            int count = (int)(cfg->mAddEnd - cfg->mAddBegin);
            int limit = 25;
            const int& n = MinRef(count, limit);
            mInfo.mNumBands = (unsigned char)n;
            for (int i = 0; i < mInfo.mNumBands; i++)
                mInfo.mCoeffs[i] = mCfg->mAddBegin[i];
        }
        {
            Vector4 zero(0.0f, 0.0f, 0.0f, 0.0f);
            for (int i = mInfo.mNumBands; i < 25; i++)
                mInfo.mCoeffs[i] = zero;
        }
        mInfo.mIntensity = mCfg->mIntensity;
    }

    cfg = mCfg;
    if (cfg && mEnabled && (cfg->mEffectA > 0.0f || cfg->mEffectB > 0.0f)) {
        IEffect* effect = SP::EffectsManager()->GetEffect(0x16f280b, 0);
        IEffect* old = mEffect;
        if (effect != old) {
            if (effect)
                effect->AddRef();
            mEffect = effect;
            if (old)
                old->Release();
        }
        if (mEffect)
            mEffectValue = mEffect->GetValue();
    } else {
        IEffect* old = mEffect;
        if (old) {
            mEffect = 0;
            old->Release();
        }
    }
    if (mEnabled) {
        mEnvFlag = true;
        mField18 = 2;
    }
    {
        int limit = mEnvCache.Capacity();
        for (int i = 0; i < limit; i++) {
            if ((unsigned)i < (unsigned)mEnvCache.Capacity()) {
                if (!Bit(*(unsigned*)mEnvCache.Entry(i), 31))
                    UpdateEnvLightSample(mEnvCache.Entry(i) + 0x10);
            }
        }
    }
    {
        int limit = mLocalCache.Capacity();
        for (int i = 0; i < limit; i++) {
            if ((unsigned)i < (unsigned)mLocalCache.Capacity()) {
                if (!Bit(*(unsigned*)mLocalCache.Entry(i), 31))
                    UpdateLocalLightSample(*(int*)(mLocalCache.Entry(i) + 0x1d0));
            }
        }
    }
    if (mEnvFlag)
        SP::MessageServer()->Post(0x2495f34, 0, 0);
}
