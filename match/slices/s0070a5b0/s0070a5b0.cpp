// slice s0070a5b0: cLightingManager tree iteration / removal and cLightingWorld::Update.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include <new>
#include <xmmintrin.h>
#include "types.h"

void __cdecl EastlFree(void* p);                       // 0x00F47380
void* __cdecl RBTreeIncrement(void* node);             // 0x00921580
void  __cdecl RBTreeErase(void* node, void* anchor);   // 0x00921880

#define PV(n) virtual void pv##n();

// ---------------------------------------------------------------- property lists
struct Property {
    char pad00[0x10];
    unsigned short mFlags;   // +0x10
    unsigned short mType;    // +0x12
    int* GetInt();           // Property::GetInt (0x0041e990)
};
static inline float PropertyFloat(Property* p)
{
    float* data = (float*)p;
    if (p->mFlags & 0x30)
        data = *(float**)p;
    return *data;
}
class PropertyList {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(uint32_t id, Property*& result);   // +0x24
};
extern PropertyList* sAppProperties;                            // 0x015fd918

// ---------------------------------------------------------------- misc stubs
struct IEffect {                                                // ref-counted effect object
    virtual void AddRef();
    virtual void Release();
    virtual void Lock();                                        // +0x08
    virtual void Unlock();                                      // +0x0c
    virtual int GetValue();                                     // +0x10
};
struct IEffectsManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual IEffect* GetEffect(uint32_t id, int arg);           // +0x8c
};
namespace SP { IEffectsManager* EffectsManager(); }             // 0x0067ddd0

struct EffectRef {
    IEffect* mp;
    EffectRef& operator=(IEffect* p);                           // AutoRefCount::operator= (0x00b5f950)
};

struct Vec3 {
    float x, y, z;
    Vec3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
};
struct Vec4u : Vec3 { float w; };                               // unaligned 16-byte vector
__declspec(align(16)) struct Vector4 {
    union {
        __m128 m;
        struct { float x, y, z, w; };
    };
    Vector4() {}
    Vector4(__m128 v) : m(v) {}
    Vector4(const Vector4& o) : m(o.m) {}
    Vector4& operator=(const Vector4& o) { m = o.m; return *this; }
    bool operator==(const Vector4& o) const
    {
        bool r = _mm_movemask_ps(_mm_cmpeq_ps(m, o.m)) == 0xf;
        return r;
    }
};

void __cdecl CalcAtmosphereZH(int count, Vec4u* dirs, int numBands, Vector4* out);        // 0x00796420
void __cdecl SHAccumulate(const float* dir, int numBands, const Vector4* coeffs, Vector4* out); // 0x00794e60
void __cdecl ApplyNormalizationConstants(int numBands, Vector4* coeffs);                   // 0x00783590

// eastl::fixed_vector<Vec4u, 8> with overflow
struct FixedVec4 {
    Vec4u* mpBegin;
    Vec4u* mpEnd;
    Vec4u* mpCapacity;
    char pad0c[4];
    void* mpPool;
    char pad14[4];
    Vec4u mStorage[8];
    FixedVec4(int n);                                           // 0x0070a0d0
    ~FixedVec4() { if (mpBegin && mpBegin != mpPool) EastlFree(mpBegin); }
    Vec4u& operator[](int i) { return mpBegin[i]; }
};

static inline bool Bit(unsigned v, int n) { return (v >> n) & 1; }

static inline Vector4 Desaturate(const Vector4& v, float t)
{
    Vector4 c = v;
    float lum = v.y * 0.587f + v.x * 0.299f + v.z * 0.114f;
    Vector4 gray(_mm_set_ps(c.w, lum, lum, lum));
    return Vector4(_mm_add_ps(_mm_mul_ps(_mm_sub_ps(v.m, gray.m), _mm_set1_ps(t)), gray.m));
}

struct World {                                                  // object at cLightingWorld+0x0c
    char pad00[0x48];
    Vec3 mDir;              // +0x48
    int mNumLights;         // +0x54
    Vec4u mLights[1];       // +0x58
};
struct Config {                                                 // object at cLightingWorld+0x10
    PropertyList* mProps;   // +0x00
    char pad04[0xb8];
    Vector4* mAddBegin;     // +0xbc
    Vector4* mAddEnd;       // +0xc0
    char pad0c4[0xc];
    float mScale;           // +0xd0
    float mSunThreshold;    // +0xd4
    float mLightScale;      // +0xd8
    float mEffectA;         // +0xdc
    float mEffectB;         // +0xe0
    Vec4u mColors[3];       // +0xe4
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

struct DequeIter {                                              // eastl::deque iterator, 0x2c-byte elements
    char* mpCur;
    char* mpBegin;
    char* mpEnd;
    char** mpSub;
};
struct DequeWalker {                                            // forward walk over a DequeIter
    char* mpCur;
    char* mpEnd;
    char** mpSub;
    DequeWalker(const DequeIter& it) : mpCur(it.mpCur), mpEnd(it.mpEnd), mpSub(it.mpSub) {}
    void Next()
    {
        mpCur += 0x2c;
        if (mpCur == mpEnd) {
            ++mpSub;
            mpCur = *mpSub;
            mpEnd = mpCur + 0xb0;
        }
    }
};

struct LightingInfo {                                           // at cLightingWorld+0x260
    char pad00;
    unsigned char mNumBands;    // +0x01
    char pad02[2];
    Vec3 mDir;                  // +0x04
    char pad10[0x10];
    Vector4 mAmbient;           // +0x20
    Vector4 mCoeffs[25];        // +0x30
};

struct cLightingWorld {
    char pad00[0xc];
    World* mWorld;                  // +0x0c
    Config* mCfg;                   // +0x10
    char pad14[0x20];
    int mNumBands;                  // +0x34
    int mNumCoeffs;                 // +0x38
    int mBudget;                    // +0x3c
    char pad40[0xa0];
    bool mDirty;                    // +0xe0
    char pade1[0xf];
    Vector4 mZH[3][7];              // +0xf0
    Vec3 mSun;                      // +0x240
    EffectRef mEffect;              // +0x24c
    int mEffectValue;               // +0x250
    char pad254[0xc];
    LightingInfo mInfo;             // +0x260
    LightingInfo* mActive;          // +0x420
    bool mEnabled;                  // +0x424
    char pad425[0x2f];
    DequeIter mFirst;               // +0x454
    DequeIter mLast;                // +0x464
    char pad474[0x120];
    SlotDeque<0x1f0> mEnvCache;     // +0x594
    char pad5b0[0x18];
    int mEnvIdx;                    // +0x5c8
    bool mEnvRescan;                // +0x5cc
    int mLocalCount;                // +0x5d0
    char pad5d4[0x34];
    SlotDeque<0x1e0> mLocalCache;   // +0x608
    char pad624[0x38];
    int mLocalIdx;                  // +0x65c
    bool mLocalRescan;              // +0x660

    void Update(uint32_t param);
    void Shutdown();
    void UpdateEnvLightSample(void* sample);                    // 0x00706170
    void UpdateLocalLightSample(int handle);                    // 0x00707370
};

struct RBTree {
    void Find(void* out, const void* key);   // 0xE5C780
};

struct cLightingManager {
    char pad[0x100];
    void UpdateAll(uint32_t param);
    void RemoveLightingWorld(uint32_t key);
};

// @ 0x0070ae40
void cLightingManager::UpdateAll(uint32_t param)
{
    for (char* it = *(char**)((char*)this + 0x34); it != (char*)this + 0x30;
         it = (char*)RBTreeIncrement(it)) {
        (*(cLightingWorld**)(it + 0x14))->Update(param);
    }
}

// @ 0x0070ae70
void cLightingManager::RemoveLightingWorld(uint32_t key)
{
    char* it;
    ((RBTree*)((char*)this + 0x2c))->Find(&it, &key);
    if (it != (char*)this + 0x30) {
        (*(cLightingWorld**)(it + 0x14))->Shutdown();
        --*(int*)((char*)this + 0x40);
        RBTreeIncrement(it);
        RBTreeErase(it, (char*)this + 0x30);
        cLightingWorld* w = *(cLightingWorld**)(it + 0x14);
        if (w)
            ((void(__thiscall*)(cLightingWorld*))(*(void***)w)[1])(w);
        EastlFree(it);
    }
}

// @ 0x0070a5b0
void cLightingWorld::Update(uint32_t param)
{
    if (!mCfg)
        return;

    PropertyList* props = sAppProperties;
    if (props) {
        Property* prop;
        if (props->GetProperty(0x641a468, prop) && prop->mType == 9) {
            int bands = *prop->GetInt();
            mNumBands = bands;
            mNumCoeffs = bands * bands;
        }
        if (props->GetProperty(0x641a467, prop) && prop->mType == 9)
            mBudget = *prop->GetInt();
    }

    Config* cfg = mCfg;
    if (cfg) {
        if (mEnabled) {
            IEffect* effect = 0;
            int effectValue = 0;
            if (cfg->mEffectA > 0.0f || cfg->mEffectB > 0.0f) {
                effect = SP::EffectsManager()->GetEffect(0x16f280b, 0);
                if (effect)
                    effectValue = effect->GetValue();
            }
            if (mEffect.mp != effect || mEffectValue != effectValue) {
                mEffect = effect;
                mEffectValue = effectValue;
                mEnvRescan = true;
            }
        }
    }

    if (mEnabled) {
        FixedVec4 dirs(mWorld->mNumLights + 1);
        for (int i = 0; i < mWorld->mNumLights; i++) {
            dirs[i] = mWorld->mLights[i];
            dirs[i] *= mCfg->mLightScale;
        }

        Vector4 work[56];
        Vector4* zh = work;
        Vector4* sh = work + 7;
        for (int j = 0; j < 3; j++) {
            dirs[mWorld->mNumLights] = mCfg->mColors[j];
            CalcAtmosphereZH(mWorld->mNumLights + 1, &dirs[0], mNumBands, zh);

            PropertyList* pl = mCfg->mProps;
            if (pl) {
                Property* prop;
                if (pl->GetProperty(0x2478ee3, prop) && prop->mType == 0xd) {
                    float sat = PropertyFloat(prop);
                    for (int k = 0; k < mNumBands; k++) {
                        zh[k] = Desaturate(zh[k], sat);
                    }
                }
            }
            for (int k = 0; k < mNumBands; k++) {
                __m128 scale = _mm_set1_ps(mCfg->mScale);
                zh[k].m = _mm_mul_ps(scale, zh[k].m);
            }

            bool changed = false;
            for (int k = 0; k < mNumBands; k++) {
                if (!(mZH[j][k] == zh[k])) {
                    mDirty = true;
                    break;
                }
            }
            if (mDirty) {
                for (int k = 0; k < mNumBands; k++)
                    mZH[j][k] = zh[k];
            }
        }

        World* world = mWorld;
        Vec3& sun = mSun;
        float d = sun.z * world->mDir.z + sun.y * world->mDir.y + world->mDir.x * sun.x;
        if (mCfg->mSunThreshold > d) {
            mDirty = true;
            sun = world->mDir;
        }

        cfg = mCfg;
        if (cfg->mEffectA > 0.0f || cfg->mEffectB > 0.0f) {
            IEffect* effect = SP::EffectsManager()->GetEffect(0x16f280b, 0);
            if (mEffect.mp != effect) {
                IEffect* old = mEffect.mp;
                if (effect != old) {
                    if (effect)
                        effect->AddRef();
                    mEffect.mp = effect;
                    if (old)
                        old->Release();
                }
                mDirty = true;
            }
        }

        SHAccumulate(&sun.x, mNumBands, &mZH[0][0], sh);
        ApplyNormalizationConstants(mNumBands, sh + 1);
        mInfo.mNumBands = (unsigned char)mNumCoeffs;
        for (int i = 0; i < mNumCoeffs; i++)
            mInfo.mCoeffs[i] = sh[i];

        cfg = mCfg;
        if (cfg->mAddBegin != cfg->mAddEnd) {
            int count = (int)(cfg->mAddEnd - cfg->mAddBegin);
            int limit = 25;
            const int& n = (limit < count) ? limit : count;
            for (int i = 0; i < n; i++)
                mInfo.mCoeffs[i].m = _mm_add_ps(mCfg->mAddBegin[i].m, mInfo.mCoeffs[i].m);
        }
        mInfo.mDir = sun;
        mInfo.mAmbient = mInfo.mCoeffs[0];
        mActive = &mInfo;
    } else {
        if (mInfo.mNumBands > 0)
            mActive = &mInfo;
        else
            mActive = 0;
    }

    if (mDirty) {
        if (mEnabled) {
            mEnvRescan = true;
        } else {
            for (DequeWalker it(mFirst); it.mpCur != mLast.mpCur; it.Next())
                *(LightingInfo**)it.mpCur = &mInfo;
            mEnvIdx = -1;
        }
        mDirty = false;
    }

    if (mEnvIdx < 0) {
        if (mEnvRescan) {
            if (mEnvCache.mFirst != 0x3fffffff)
                mEnvIdx = mEnvCache.mFirst;
            mEnvRescan = false;
        }
        if (mEnvIdx < 0)
            goto localPass;
    }
    if (mEffect.mp)
        mEffect.mp->Lock();
    {
        int limit = mEnvCache.Capacity();
        int budget = mBudget;
        if (mEnvIdx < limit) {
            while (mEnvIdx < limit && budget > 0) {
                if ((unsigned)mEnvIdx < (unsigned)mEnvCache.Capacity()) {
                    if (!Bit(*(unsigned*)mEnvCache.Entry(mEnvIdx), 31)) {
                        UpdateEnvLightSample(mEnvCache.Entry(mEnvIdx) + 0x10);
                        budget--;
                    }
                }
                mEnvIdx++;
            }
        }
        if (mEnvIdx >= limit) {
            mEnvIdx = -1;
            if (mLocalCount > 0)
                mLocalRescan = true;
        }
    }
    if (mEffect.mp)
        mEffect.mp->Unlock();

localPass:
    if (mLocalIdx < 0 && mLocalRescan) {
        if (mLocalCache.mFirst != 0x3fffffff)
            mLocalIdx = mLocalCache.mFirst;
        mLocalRescan = false;
    }
    if (mLocalIdx >= 0) {
        int limit = mLocalCache.Capacity();
        int budget = mBudget;
        if (mLocalIdx < limit) {
            while (mLocalIdx < limit && budget > 0) {
                if ((unsigned)mLocalIdx < (unsigned)mLocalCache.Capacity()) {
                    if (!Bit(*(unsigned*)mLocalCache.Entry(mLocalIdx), 31)) {
                        UpdateLocalLightSample(*(int*)(mLocalCache.Entry(mLocalIdx) + 0x1d0));
                        budget--;
                    }
                }
                mLocalIdx++;
            }
        }
        if (mLocalIdx >= limit)
            mLocalIdx = -1;
    }
}
