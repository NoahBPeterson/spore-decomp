// @ 0x00ddbe40  Swarm::SpawnOne: pick the next effect key from the resource manager's key tree
// (round-robin through g_nextKey), create two resources for it, wrap the first in a transform
// description + holder, give the new boid a random orientation and a rejection-sampled start
// position, and append it to the swarm's boid vector (this+0). Names are Claude-coined from usage.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc).

#include "types.h"
#include <math.h>

typedef unsigned int uint;

inline void* operator new(unsigned, void* p) { return p; }
void* operator new(unsigned size, const char* tag, int a, int b, int c, int d);   // 0x00f473a0
void operator delete[](void* p);                                                  // 0x00f47380

struct Key { uint a, b, c; };

// vector<Key> (12-byte elements) with the sp_vector_allocator header check on free
struct KeyVec
{
    Key* mpBegin; Key* mpEnd; Key* mpCapacity;
    ~KeyVec() { if (mpBegin && ((uint*)mpBegin)[-1]) operator delete[](mpBegin); }
};

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
static __forceinline Vec4 MakeV4(float x, float y, float z, float w)
{
    Vec4 v; v.x = x; v.y = y; v.z = z; v.w = w; return v;
}
struct Quat
{
    float x, y, z, w;
    void Assign(const Quat* o) { x = o->x; y = o->y; z = o->z; w = o->w; }
};
static __forceinline Quat MakeQuat(float x, float y, float z, float w)
{
    Quat q; q.x = x; q.y = y; q.z = z; q.w = w; return q;
}
Quat* QuatMul(Quat* out, const Quat* a, const Quat* b);                // 0x007dcb00 (cdecl)

struct RandomLinearCongruential
{
    double RandomDoubleUniform();                                      // 0x009360d0
};
extern RandomLinearCongruential g_Random;                              // 0x01601760
float RandomFloatRange(float lo, float hi);                            // 0x00572a10 (cdecl)

// inlined copy of RandomFloatRange
static __forceinline float RandInline(float lo, float hi)
{
    double dlo = lo;
    double dhi = hi;
    double u = g_Random.RandomDoubleUniform();
    double r = u * (dhi - dlo) + dlo;
    if (r < dhi)
        return (float)(dlo > r ? dlo : r);
    return (float)dhi;
}

// ---- key helpers ----------------------------------------------------------------------
struct KeyUtil
{
    bool IsValid(const Key* k);                                        // 0x00b7d4f0 (ret 4)
    void MakeVariants(Key k, Key* p4, Key* p5, Key* p6, void* p7, Key* p8, Key* p9);   // 0x00b7d440 (ret 0x24)
};
KeyUtil* GetKeyUtil();                                                 // 0x00b3d360 (returns [0x167eafc])

struct KeyTree
{
    void GetKeys(KeyVec* out);                                         // 0x00de7530 (ret 4)
    void Remove(Key* k);                                               // 0x00de74c0 (ret 4)
};
struct ResMgr { uint32_t pad[0x3c / 4]; KeyTree tree; };
extern ResMgr* g_resMgr;                                               // [0x016a1344]
extern uint g_nextKey;                                                 // [0x016a0c60]

// 0x00dd9130: static helper (outputs in edi/esi): splits a key into the two resource keys
static __declspec(noinline) void SplitKey(const Key* k, Key* a, Key* b)
{
    if (GetKeyUtil()->IsValid(k))
    {
        Key kk = *k;
        GetKeyUtil()->MakeVariants(kk, 0, 0, 0, 0, a, b);
    }
    else
    {
        a->a = 0; a->b = 0; a->c = 0;
        b->a = 0; b->b = 0; b->c = 0;
    }
}

// ---- effects --------------------------------------------------------------------------
struct IEff
{
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2(int a);
};
struct EffectsMgr
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual void Find(uint hash, int zero, IEff** out);                // +0x2c (ret 0xc)
};
EffectsMgr* EffectsManager();                                          // 0x0067ddd0
uint FNV1_String16(const wchar_t* s, uint seed, int mode);             // 0x00932f30 (cdecl)

struct StrRange { const wchar_t* mpBegin; const wchar_t* mpEnd; };
extern StrRange g_effectName;                                          // [0x016a10ac]/[0x016a10b0]

struct Stopwatch { void SetUnits(int u); };                            // 0x0093a1a0 (ret 4)

// ---- the map manager at this+0x14 -----------------------------------------------------
struct Resource { uint32_t pad0; uint32_t mFlags; uint32_t pad[(0x40 - 8) / 4]; int mRef; };
struct HolderObj;
struct MapMgr
{
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual Resource* Create(uint a, uint b, uint c);                  // +0x0c (ret 0xc)
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70();
    virtual void v74(); virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94(); virtual void v98();
    virtual void v9c(); virtual void va0();
    virtual void Attach(Resource* r, HolderObj* h, int idx);           // +0xa4 (ret 0xc)
};

template <class T> struct PtrVec
{
    T* mpBegin; T* mpEnd; T* mpCapacity;
    void DoInsertValue(T* pos, const T& v);
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(v);
        else
            DoInsertValue(mpEnd, v);
    }
};

struct TransformDesc                                                   // vtable 0x01453948
{
    virtual void d0();
    uint16_t mKind;             // +4
    uint16_t mCount;            // +6
    float*   mpMatrix;          // +8
    Vec4     mRow[4];           // +0xc  (4x4 identity)
    uint32_t pad[(0x10c - 0x4c) / 4];
    TransformDesc() : mKind(0x206), mCount(0x100), mpMatrix(&mRow[0].x) {}
};

struct HolderObj
{
    void* vtbl;
    int   mRef;
    PtrVec<TransformDesc*> mVec;                                       // +8   DoInsertValue 0x004558a0
    HolderObj();                                                       // 0x0077d1d0 (fastcall ctor)
};

struct Boid                                                            // 0x100 bytes
{
    Resource* mResA;            // +0x00
    Resource* mResB;            // +0x04
    IEff*     mEffect;          // +0x08
    Vec3      mPos;             // +0x0c
    Vec3      mV18;
    Vec3      mV24;
    Vec3      mV30;
    uint32_t  pad3c[3];
    Quat      mRot;             // +0x48
    uint32_t  pad58[16];
    float     m98;              // +0x98
    uint32_t  pad9c[3];
    float     mA8;              // +0xa8
    uint32_t  padac;
    Stopwatch mWatch;           // +0xb0
    uint32_t  padb1[(0xc8 - 0xb1) / 4 + 0];
    int       mC8;
    int       mCC;
    int       mD0;
    char      mD4;
    char      mD5;
    char      padd6[6];
    float     mDC;
    float     mE0;
    uint32_t  pade4;
    Vec3      mAxis;            // +0xe8
    uint32_t  padf4;
    void*     mpF8;             // +0xf8
    int       mFC;
    Boid();                                                            // 0x00dd9510 (fastcall ctor)
};

extern Vec3 g_v0b0c;                                                   // 0x016a0b0c
extern Vec3 g_v0ba4;                                                   // 0x016a0ba4
extern Vec3 g_axis;                                                    // 0x016a0c3c
extern float g_angle;                                                  // 0x015a2d00
extern float g_maxAngle;                                               // 0x016a0b58
extern float g_scaleLo, g_scaleHi;                                     // 0x016a0fd8 / 0x016a0fe8
extern float g_dHi, g_dLo;                                             // 0x016a1018 / 0x016a1028
extern float g_z;                                                      // 0x016a1038
extern float g_maxE0;                                                  // 0x013eecd8
extern char  g_boidGlobal;                                             // 0x016a0c00

// 0x00dd93d0: static helper (output pointer in esi): random start offset in the xy plane
extern const float k_range50;                                          // 0x0147d244
extern const float k_min35;                                            // 0x0147d240
static __declspec(noinline) Vec3* RandomOffset(Vec3* out)
{
    static float range = k_range50;
    static float minLen = k_min35;
    int i = 0;
    do
    {
        out->x = RandInline(-range, range);
        out->y = RandInline(-range, range);
        out->z = 0.0f;
        float len = sqrtf((out->x * out->x + out->y * out->y) + out->z * out->z);
        if (!(len < minLen && len > range))
            break;
    } while (i++ < 1000);
    return out;
}

struct Swarm : PtrVec<Boid*>
{
    uint32_t pad[2];
    MapMgr*  mpMgr;                                                    // +0x14
    float    FindNearest(const Vec3* p, int group);                    // 0x00dda160 (ret 8)
    void     SpawnOne();                                               // 0x00ddbe40
};

void Swarm::SpawnOne()
{
    KeyVec keys = { 0, 0, 0 };
    g_resMgr->tree.GetKeys(&keys);
    if (keys.mpBegin != keys.mpEnd)
    {
        uint n = (uint)(keys.mpEnd - keys.mpBegin);
        if (g_nextKey >= n)
            g_nextKey = 0;
        Key kB = { 0, 0, 0 };
        Key kA = { 0, 0, 0 };
        SplitKey(keys.mpBegin + g_nextKey, &kA, &kB);
        Resource* resA = mpMgr->Create(kA.a, kA.c, 0);
        if (resA)
        {
            resA->mRef++;
            resA->mFlags |= 0x12;

            TransformDesc* td = new("Simulator", 0, 0, 0, 0) TransformDesc();
            td->mRow[0] = MakeV4(1.0f, 0.0f, 0.0f, 0.0f);
            td->mRow[1] = MakeV4(0.0f, 1.0f, 0.0f, 0.0f);
            td->mRow[2] = MakeV4(0.0f, 0.0f, 1.0f, 0.0f);
            td->mRow[3] = MakeV4(0.0f, 0.0f, 0.0f, 1.0f);

            HolderObj* holder = new("Simulator", 0, 0, 0, 0) HolderObj();
            TransformDesc* pTd = td;
            holder->mVec.push_back(pTd);
            mpMgr->Attach(resA, holder, -1);

            Boid* boid = new("Simulator", 0, 0, 0, 0) Boid();
            Boid* pBoid = boid;
            boid->mResA = resA;
            boid->mFC = 0;
            boid->mResB = mpMgr->Create(kB.a, kB.c, 0);
            boid->mResB->mRef++;
            boid->mWatch.SetUnits(5);
            boid->mC8 = 0;
            boid->mD5 = 0;
            boid->mCC = 0;
            boid->mpF8 = &g_boidGlobal;
            boid->mAxis = g_v0ba4;
            boid->mD0 = 0;
            boid->mV18 = g_v0b0c;
            boid->mV24 = g_v0b0c;
            boid->mV30 = g_v0b0c;

            IEff* eff = 0;
            if (g_effectName.mpBegin != g_effectName.mpEnd)
            {
                EffectsMgr* em = EffectsManager();
                em->Find(FNV1_String16(g_effectName.mpBegin, 0x811c9dc5, 1), 0, &eff);
                if (eff)
                {
                    eff->Slot0();
                    eff->Slot2(0);
                }
            }
            boid->mEffect = eff;

            float half = g_angle * 0.5f;
            float s = sinf(half);
            float c = cosf(half);
            boid->mRot = MakeQuat(s * g_axis.x, s * g_axis.y, s * g_axis.z, c);

            float half2 = RandomFloatRange(0.0f, g_maxAngle) * 0.5f;
            float s2 = sinf(half2);
            float c2 = cosf(half2);
            Quat q2 = MakeQuat(boid->mAxis.x * s2, boid->mAxis.y * s2, boid->mAxis.z * s2, c2);
            Quat tmp;
            boid->mRot.Assign(QuatMul(&tmp, &boid->mRot, &q2));

            int cnt = 0;
            Vec3 off;
            float len;
            do
            {
                boid->mPos = *RandomOffset(&off);
                len = sqrtf((boid->mPos.x * boid->mPos.x + boid->mPos.y * boid->mPos.y) + boid->mPos.z * boid->mPos.z);
                boid->mPos.z = RandInline(-600.0f, boid->mE0);
            } while (len < k_min35 && FindNearest(&boid->mPos, 0) < 30.0f && cnt++ < 1000);

            boid->mE0 = RandomFloatRange(0.0f, g_maxE0);
            float r = RandomFloatRange(g_scaleLo, g_scaleHi);
            boid->mA8 = r;
            boid->m98 = r;
            boid->mD4 = 0;
            boid->mDC = RandomFloatRange(g_dLo, g_dHi);
            boid->mV18.x = 0.0f; boid->mV18.y = 0.0f; boid->mV18.z = g_z;
            push_back(pBoid);
        }
        else
        {
            g_resMgr->tree.Remove(keys.mpBegin + g_nextKey);
        }
        g_nextKey++;
    }
}
