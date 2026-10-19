// slice s00708f40: cLightingWorld global-state evaluation + cLightingManager ctor.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include <new>
#include <xmmintrin.h>
#include <intrin.h>
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

struct IConfigOwner;
struct DirLight {                                               // 0x1c bytes at Config+8
    float px, py, pz;       // +0x00
    float k;                // +0x0c
    float dx, dy, dz;       // +0x10
};
struct Config {                                                 // object at cLightingWorld+0x10
    IConfigOwner* mOwner;   // +0x00
    uint32_t mFlags;        // +0x04 (bits 0-3: DirLight present, 4: ambient override, 5: sun)
    DirLight mLights[4];    // +0x08
    float m78, m7c, m80;    // +0x78
    float m84;              // +0x84 (sun scale)
    float m88;              // +0x88
    float vx, vy, vz;       // +0x8c
    uint32_t mAmbient[3];   // +0x98
    bool mCopyXform;        // +0xa4
    char padA5[0x17];
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


// --------------------------------------------------------------------------- global-state helpers
extern uint32_t g_softDirty;            // 0x016f9528 (GlobalState soft-state dirty bits)
extern float g_gsAmbient[3];            // 0x016f9598
extern void* g_gsLights[8];             // 0x016f9574
extern float g_kOrigin[3];              // 0x01629858
extern float g_kIdentity[9];            // 0x016299ac
void __cdecl SetShaderData(unsigned short id, const void* data, char force);   // 0x00777ae0
void __cdecl EAFreeLw(void* p);                                                 // 0x00f47380
void __cdecl RemoveNormalizationConstants(int n, float* coeffs);               // 0x00783830
void __cdecl ApplyNormalizationConstants(int n, float* coeffs);                // 0x00783590
void __cdecl ConvolveCoefficients(float* a, int n, float* b, float* out);      // 0x00795eb0 (thunk of 0x007864c0)
bool __cdecl Mat33NotEqual(const float* a, const float* b);                    // 0x0041dd90
struct RGB3 { float r, g, b; };
struct LoopState { unsigned off; unsigned i; };

struct Mat33 {                                                  // rw::math::fpu::Matrix33Template<float,0>
    float m[9];
    Mat33(const float* src);                                    // 0x0041cb40 (Matrix3::Assign, ret 4)
};
struct Xform {                                                  // SP::cSPTransform
    uint16_t mFlags;        // +0x00 (bit 1: rotation present, bit 2: position)
    uint16_t mVersion;      // +0x02
    float mPos[3];          // +0x04
    float mScale;           // +0x10
    Mat33 mRot;             // +0x14
    Xform() : mRot(g_kIdentity)
    {
        mVersion = 0;
        mPos[0] = g_kOrigin[0];
        mPos[1] = g_kOrigin[1];
        mFlags = 0;
        mPos[2] = g_kOrigin[2];
        mScale = 1.0f;
    }
    Xform& operator=(const Xform& o);                           // 0x00537dc0 (ret 4)
};
struct XformSource {                                            // owner of the matrix + origin fetched by 0x007c40f0
    void GetTransform(Xform* out);                              // 0x007c40f0 (ret 4)
};
struct Light {
    char pad00[0x20];
    Vector4 mDir;           // +0x20
    Vector4 mPos;           // +0x30
};
struct ScratchCoeffs {                                          // eastl::fixed_vector<float,256> on the stack
    float* mpBegin;
    float* mpEnd;
    float* mpCap;
    uint32_t pad0c;
    float* mpPoolBegin;
    uint32_t pad14[3];
    float mBuf[256];
    ScratchCoeffs(const Vector4* first, const Vector4* last);   // 0x00708df0 (ret 8)
    ~ScratchCoeffs() { if (mpBegin && mpBegin != mpPoolBegin) EAFreeLw(mpBegin); }
};
struct IConfigOwner {                                           // object at Config+0
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void Query(uint32_t id, void* out);                 // +0x24
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
    char pad9c[0x38];
    float mAtmPos[3];               // +0xd4
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
    void ApplyGlobalState(XformSource* src);
    Xform& Cur() { return *(Xform*)&mFlags; }
    Xform& Prev() { return *(Xform*)pad9c; }
    void ApplyConfig();
};

// @ 0x00708f40
void cLightingWorld::ApplyGlobalState(XformSource* src)
{
    LoopState st;                       // doubles as the Query out-parameter at the end
    RGB3 amb;
    amb.r = mAmbient[0];
    amb.g = mAmbient[1];
    amb.b = mAmbient[2];
    g_softDirty |= 0x20;
    *(RGB3*)g_gsAmbient = amb;

    Xform t;
    src->GetTransform(&t);
    mAtmPos[0] = t.mPos[0];
    mAtmPos[1] = t.mPos[1];
    mAtmPos[2] = t.mPos[2];

    Config* cfg = mCfg;
    if (cfg) {
        if (cfg->mCopyXform)
            Cur() = t;
        Xform* xf = &Cur();
        Xform& prev = Prev();
        if (prev.mScale != xf->mScale || prev.mPos[0] != xf->mPos[0] || prev.mPos[1] != xf->mPos[1] ||
            prev.mPos[2] != xf->mPos[2] || Mat33NotEqual(prev.mRot.m, xf->mRot.m)) {
            if (mInfo.mNumBands != 0 && !mEnabled) {
                Config* c = mCfg;
                ScratchCoeffs coeffs(c->mAddBegin, c->mAddBegin + (c->mAddEnd - c->mAddBegin));
                int n = *(int*)((char*)this + 0x34);
                RemoveNormalizationConstants(n, coeffs.mpBegin);
                ConvolveCoefficients(xf->mRot.m, n, coeffs.mpBegin, &mInfo.mCoeffs[0].x);
                ApplyNormalizationConstants(n, &mInfo.mCoeffs[0].x);
            }
            cfg = mCfg;
            if (Bit(cfg->mFlags, 5)) {
                float vx = cfg->vx, vy = cfg->vy, vz = cfg->vz;
                float ox = vx, oy = vy, oz = vz;
                if (xf->mFlags & 2) {
                    ox = (xf->mRot.m[6] * vz + xf->mRot.m[3] * vy) + xf->mRot.m[0] * vx;
                    oy = (xf->mRot.m[1] * vx + xf->mRot.m[7] * vz) + xf->mRot.m[4] * vy;
                    oz = (xf->mRot.m[2] * vx + xf->mRot.m[8] * vz) + xf->mRot.m[5] * vy;
                }
                float s = xf->mScale;
                float px = xf->mPos[0] + ox * s;
                float py = xf->mPos[1] + oy * s;
                float pz = xf->mPos[2] + oz * s;
                ((Light*)mSunLight)->mPos = Vector4(px, py, pz, px);
            }
            {
                st.off = 0;
                st.i = 0;
                unsigned mask = 1;
                for (int off = 0; off < 0x70; off += 0x1c, st.i++, mask = (mask << 1) | (mask >> 31)) {
                    if (st.i < 7 && FlagSet(mCfg->mFlags, mask)) {
                        Config* c = mCfg;
                        float n1 = -*(float*)((char*)c + off + 0x18);
                        float n2 = -*(float*)((char*)c + off + 0x1c);
                        float n3 = -*(float*)((char*)c + off + 0x20);
                        float ox = n1, oy = n2, oz = n3;
                        if (xf->mFlags & 2) {
                            ox = (xf->mRot.m[6] * n3 + xf->mRot.m[3] * n2) + n1 * xf->mRot.m[0];
                            oy = (xf->mRot.m[1] * n1 + xf->mRot.m[7] * n3) + xf->mRot.m[4] * n2;
                            oz = (xf->mRot.m[2] * n1 + xf->mRot.m[8] * n3) + xf->mRot.m[5] * n2;
                        }
                        Light* l = *(Light**)((char*)mDirLights.mpBegin + st.off);
                        st.off += 4;
                        l->mDir = Vector4(ox, oy, oz, ox);
                    }
                }
            }
            Prev() = *xf;
        }
    }

    int count = (int)(mDirLights.mpEnd - mDirLights.mpBegin);
    unsigned mask = 1;
    int n = 0;
    for (int i = 0; i < count; i++) {
        void* l = (void*)mDirLights.mpBegin[i];
        g_softDirty |= _rotl(mask, 6);
        g_gsLights[i] = l;
        mask = _rotl(mask, 1);
        n = count;
    }
    if (mSunLight) {
        g_gsLights[n] = (void*)mSunLight;
        g_softDirty |= 1 << ((n + 6) & 31);
        n++;
    }
    unsigned bit = _rotl(1, n);
    if (n < 8) {
        int rest = 8 - n;
        for (int k = 0; k < rest; k++)
            g_gsLights[n + k] = 0;
        do {
            g_softDirty |= _rotl(bit, 6);
            bit = _rotl(bit, 1);
            rest--;
        } while (rest != 0);
    }

    cfg = mCfg;
    if (!cfg) {
        SetShaderData(0x219, 0, 0);
        SetShaderData(0x224, 0, 0);
        return;
    }
    SetShaderData(0x300, 0, 0);
    if (mInfo.mNumBands != 0)
        SetShaderData(0x219, &mInfo, 1);
    else
        SetShaderData(0x219, 0, 0);
    if (!mEnabled) {
        SetShaderData(0x224, 0, 0);
        return;
    }
    if (cfg->mOwner)
        cfg->mOwner->Query(0x2478ee4, &st);
    SetShaderData(0x224, *(char**)((char*)this + 0xc) + 0xf8, 1);
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
