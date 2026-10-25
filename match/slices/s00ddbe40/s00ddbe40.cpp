// Swarm::SpawnOne: pick the next effect key from the resource manager's key tree
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
extern StrRange g_effectName;                                          // 0x016a109c

// ---- name-vector globals used by the boid's behaviour tail call -----------------------
struct ObjVec { void** mpBegin; void** mpEnd; void** mpCapacity; };
extern ObjVec gNames0bb0;                                              // 0x016a0bb0
extern ObjVec gNames0bd8;                                              // 0x016a0bd8
inline void* VFn(void* p, int off) { return *(void**)(*(char**)p + off); }

// ---- audio system (EA::Audio::GetSystemAT) --------------------------------------------
struct IAudioSystem
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void* v20();                                               // +0x20
};
IAudioSystem* GetSystemAT();                                           // 0x00a206f0

// ---- misc callees ---------------------------------------------------------------------
void* FUN_00ddaf70(Key* out, int id);                                  // 0x00ddaf70 (cdecl)
// Internal static helper: ecx = up, eax = dir, esi = out (results returned in eax).
Quat* FUN_00dd91b0(const Vec3* up, const Vec3* dir, Quat* out);        // 0x00dd91b0
extern "C" int __stdcall QueryPerformanceCounter(long long* ctr);      // import 0x13cc2b8
extern "C" unsigned __int64 __cdecl __rdtsc();
#pragma intrinsic(__rdtsc)

struct Stopwatch                                                       // 0x18 bytes
{
    void SetUnits(int u);                                              // 0x0093a1a0 (ret 4)
    uint32_t mStartLo;          // +0x00
    uint32_t mStartHi;          // +0x04
    uint32_t pad08;             // +0x08
    uint32_t pad0c;             // +0x0c
    int      mUnits;            // +0x10 (1 = rdtsc, otherwise QueryPerformanceCounter)
    float    mScale;            // +0x14
};

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
    Vec3      mV30;             // +0x30
    Vec3      mStartPos;        // +0x3c
    Quat      mRot;             // +0x48
    uint32_t  pad58[8];         // +0x58
    Quat      mV78;             // +0x78
    Quat      mV88;             // +0x88
    float     m98;              // +0x98
    uint32_t  pad9c[3];         // +0x9c
    float     mA8;              // +0xa8
    uint32_t  padac;            // +0xac
    Stopwatch mWatch;           // +0xb0
    int       mC8;              // +0xc8
    int       mCC;              // +0xcc
    int       mD0;              // +0xd0
    char      mD4;              // +0xd4
    char      mD5;              // +0xd5
    char      mD6;              // +0xd6
    char      mD7;              // +0xd7
    char      padd8[4];         // +0xd8
    float     mDC;              // +0xdc
    float     mE0;              // +0xe0
    uint32_t  pade4;            // +0xe4
    Vec3      mAxis;            // +0xe8
    uint32_t  padf4;            // +0xf4
    void*     mpF8;             // +0xf8
    int       mFC;              // +0xfc
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

struct ITimer;                                                         // defined with the gold7 block below

struct Swarm : PtrVec<Boid*>
{
    uint32_t pad[2];
    MapMgr*  mpMgr;                                                    // +0x14
    MapMgr*  mpMgr2;                                                   // +0x18 (second resource manager; slot 0x0c = Create)
    uint32_t pad1c[(0x70 - 0x1c) / 4];
    ITimer*  mpTimer;                                                  // +0x70 (slot 0x24 takes the step + a flag)
    float    FindNearest(const Vec3* p, int group);                    // 0x00dda160 (ret 8)
    void     SpawnOne();                                               // 0x00ddbe40
    void     FUN_00ddb600(Boid* b);                                    // 0x00ddb600 (ret 4)
    bool     FUN_00ddb0d0(Boid* b, uint32_t ticks);                    // 0x00ddb0d0 (ret 8)
    Boid*    FUN_00ddc4a0();                                           // 0x00ddc4a0 (ret 0)
    void     FUN_00ddc820(uint32_t key);                               // 0x00ddc820 (ret 4)
    void     FUN_00ddc6d0(uint32_t ticks);                             // 0x00ddc6d0 (ret 4)
    void     FUN_00ddc910(const Vec3* pos, const Vec3* dir, unsigned char a, unsigned char b);  // 0x00ddc910 (ret 0x10)
    void     FUN_00ddcad0(const Vec3* pos, const Vec3* dir);           // 0x00ddcad0 (ret 8)
};

// @ 0x00ddbe40
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


// ===========================================================================
//  gold7 slice functions (0x00ddc4a0 .. 0x00ddcad0) -- members of the same
//  swarm manager that owns SpawnOne above.  Toolchain: VC9 SP1 (/O2 /MD /Gy
//  /EHsc /TP /arch:SSE /fp:fast).
// ===========================================================================

#define VS1(p)  virtual void p##_a();
#define VS2(p)  VS1(p##0) VS1(p##1)
#define VS4(p)  VS2(p##0) VS2(p##1)
#define VS8(p)  VS4(p##0) VS4(p##1)
#define VS16(p) VS8(p##0) VS8(p##1)
#define VS32(p) VS16(p##0) VS16(p##1)

// The object held at Swarm+0x70; only slot 0x24 (the step/flag setter) is resolved here.
struct ITimer
{
    VS8(v0)                                              // +0x00 (slots 0x00..0x1c)
    VS1(v1)                                              // +0x20
    virtual void SetStep(float dt, int flag);            // +0x24 (ret 8)
};

// 4-byte-element SPVector used by the swarm's scratch lists.  Its out-of-line
// inserter is the one shared with the game's SPVector<unsigned int> instances.
template <class T> struct SPVec4
{
    T* mpBegin;                                          // +0x00
    T* mpEnd;                                            // +0x04
    T* mpCapacity;                                       // +0x08
    void DoInsertKey4(T* pos, const T& v);               // 0x00b96600 (ret 8)
    void push_back(const T& v)                           // SPVector 4-byte push shape
    {
        if (mpEnd < mpCapacity)
        {
            T* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot != 0)
                *slot = v;
        }
        else
        {
            DoInsertKey4(mpEnd, v);
        }
    }
};

extern SPVec4<Boid*> g_scanList;                         // 0x016a0c64 (scratch list rebuilt each step)
extern uint32_t      g_scanInit;                         // 0x016a0c78 (bit 0 = scratch list initialised)
extern "C" int   atexit(void (*fn)(void));               // 0x011e07ef (lib_crt)
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);   // 0x011e0744 (lib_crt)
void FUN_013c5f50();                                     // 0x013c5f50 (scratch-list teardown)

// The singleton reset by 0x00ddc8d0; its callee's mangled name gives the class name.
struct ObjA
{
    void FUN_00ddb790();                                 // 0x00ddb790 (ret 0)
    void FUN_00dda9a0();                                 // 0x00dda9a0 (ret 0)
};
extern ObjA* g_objA;                                     // [0x016a0b08]

// ------------------------------------------------------------------ 0x00ddc4a0
// Random-boid factory.  Retries the resource lookup (FUN_00ddaf70 + the manager
// at this+0x18's slot 0x0c) up to 100 times, bumps the resource's refcount
// (+0x40), resolves the caller's effect name through the EffectsManager (slots
// 0x2c/0x00/0x08), builds the 0x100-byte boid (tagged operator new 0x00f473a0 +
// ctor 0x00dd9510) and wires it up: +0x00 resource, +0x08 effect, +0x18/+0x24/
// +0x30/+0x0c = the global origin vector, +0x98 = 5.0f, +0xd0 = the audio
// system's slot 0x20 and the +0xb0 stopwatch (SetUnits(5); rdtsc /
// QueryPerformanceCounter).  It then clears +0x04/+0xc8/+0xcc/+0xd4/+0xd5/+0xf8
// and appends the boid to this+0.
// @ 0x00ddc4a0
Boid* Swarm::FUN_00ddc4a0()
{
    uint32_t i;
    Resource* res;
    for (i = 0; i < 100; ++i)
    {
        Key key;
        FUN_00ddaf70(&key, 0x98e03c0d);
        res = mpMgr2->Create(key.a, key.c, 0);
        if (res != 0)
            break;
    }
    if (i == 100)
        return 0;

    res->mRef++;

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

    Boid* boid = new("Simulator", 0, 0, 0, 0) Boid();
    boid->mWatch.SetUnits(5);
    if ((boid->mWatch.mStartLo | boid->mWatch.mStartHi) == 0)
    {
        if (boid->mWatch.mUnits == 1)
        {
            unsigned __int64 t = __rdtsc();
            boid->mWatch.mStartLo = (uint32_t)t;
            boid->mWatch.mStartHi = (uint32_t)(t >> 32);
        }
        else
        {
            long long ctr;
            QueryPerformanceCounter(&ctr);
            boid->mWatch.mStartLo = (uint32_t)ctr;
            boid->mWatch.mStartHi = (uint32_t)(ctr >> 32);
        }
    }

    boid->mC8 = 0;
    boid->mD5 = 0;
    boid->mResB = 0;
    boid->mCC = 0;
    boid->mpF8 = 0;
    boid->mEffect = eff;

    IAudioSystem* audio = GetSystemAT();
    boid->mD0 = audio ? (int)audio->v20() : 0;

    boid->mV18 = g_v0b0c;
    boid->mV24 = g_v0b0c;
    boid->mV30 = g_v0b0c;
    boid->mPos = g_v0b0c;

    boid->m98 = 5.0f;
    boid->mD4 = 0;
    boid->mResA = res;

    push_back(boid);
    return boid;
}

// ------------------------------------------------------------------ 0x00ddc820
// Calls FUN_00ddb600 on every boid whose key field (+0xfc) equals the argument,
// walking the matches in reverse order.  The matches are collected in a local
// scratch list first.
// @ 0x00ddc820
void Swarm::FUN_00ddc820(uint32_t key)
{
    unsigned count = (unsigned)(mpEnd - mpBegin);
    SPVec4<Boid*> hits = { 0, 0, 0 };
    for (unsigned i = 0; i < count; ++i)
    {
        if (mpBegin[i]->mFC == key)
            hits.push_back(mpBegin[i]);
    }
    for (Boid** it = hits.mpEnd; it != hits.mpBegin; )
    {
        --it;
        FUN_00ddb600(*it);
    }
    if (hits.mpBegin != 0 && hits.mpBegin[-1] != 0)
        operator delete[](hits.mpBegin);
}

// ------------------------------------------------------------------ 0x00ddc6d0
// Advances the swarm one step: converts the caller's millisecond count to
// seconds, clamps it to 0.2 s and pushes it into the timer at +0x70, then
// re-spawns every boid of this+0 whose FUN_00ddb0d0 fails into the global
// scratch list, updates each collected boid (FUN_00ddb600) and empties the list.
// @ 0x00ddc6d0
void Swarm::FUN_00ddc6d0(uint32_t ticks)
{
    float cap = 0.2f;
    float secs = ticks * 0.001;
    float& step = (secs <= cap) ? secs : cap;      // min(secs, cap), taken by reference
    mpTimer->SetStep(step, 0);

    if ((g_scanInit & 1) == 0)
    {
        g_scanInit |= 1;
        g_scanList.mpBegin = 0;
        g_scanList.mpEnd = 0;
        g_scanList.mpCapacity = 0;
        atexit(FUN_013c5f50);
    }

    unsigned count = (unsigned)(mpEnd - mpBegin);
    for (unsigned i = 0; i < count; ++i)
    {
        Boid* b = mpBegin[i];
        if (!FUN_00ddb0d0(b, ticks))
            g_scanList.push_back(b);
    }

    count = (unsigned)(g_scanList.mpEnd - g_scanList.mpBegin);
    for (unsigned i = 0; i < count; ++i)
        FUN_00ddb600(g_scanList.mpBegin[i]);

    // the scratch list's own erase(mpBegin, mpEnd): nothing shifts, only mpEnd moves back
    Boid** first = g_scanList.mpBegin;
    Boid** last  = g_scanList.mpEnd;
    memcpy(first, last, 0);
    g_scanList.mpEnd = g_scanList.mpEnd - (last - first);
}

// ------------------------------------------------------------------ 0x00ddc8d0
// Releases the global singleton: 0x00ddb790 first, then 0x00dda9a0 (or
// operator delete[] when the pointer is still set), then clears the global.
// @ 0x00ddc8d0
void FUN_00ddc8d0()
{
    if (g_objA != 0)
    {
        g_objA->FUN_00ddb790();
        if (g_objA != 0)
        {
            ObjA* p = g_objA;
            g_objA->FUN_00dda9a0();
            operator delete[](p);
        }
        g_objA = 0;
    }
}

// ------------------------------------------------------------------ 0x00ddc910
// Spawns a boid with position/direction: forwards to FUN_00ddc4a0 (the caller's
// ecx), stores pos -> +0x0c/+0x3c and dir -> +0x30, seeds the stopwatch
// (+0xb0/+0xb4: rdtsc when +0xc0 == 1, else QueryPerformanceCounter), flags
// +0xd6/+0xd7, sets +0xfc = 1, normalises the direction (1/sqrt(d2 + 1e-8)),
// copies the resulting quaternion lanes to +0x78/+0x48/+0x88, points +0xf8 at
// the 0x016a0bb0 name list and tail-calls its first object's slot 0.
// @ 0x00ddc910
void Swarm::FUN_00ddc910(const Vec3* pos, const Vec3* dir, unsigned char a, unsigned char b)
{
    Boid* boid = FUN_00ddc4a0();
    if (boid == 0)
        return;

    boid->mPos = *pos;
    boid->mV30 = *dir;
    boid->mStartPos = *pos;

    if ((boid->mWatch.mStartLo | boid->mWatch.mStartHi) == 0)
    {
        if (boid->mWatch.mUnits == 1)
        {
            unsigned __int64 t = __rdtsc();
            boid->mWatch.mStartLo = (uint32_t)t;
            boid->mWatch.mStartHi = (uint32_t)(t >> 32);
        }
        else
        {
            long long ctr;
            QueryPerformanceCounter(&ctr);
            boid->mWatch.mStartLo = (uint32_t)ctr;
            boid->mWatch.mStartHi = (uint32_t)(ctr >> 32);
        }
    }

    boid->mD6 = a;
    boid->mFC = 1;
    boid->mD7 = b;

    Vec3 d;
    d.x = dir->x - pos->x;
    d.y = dir->y - pos->y;
    d.z = dir->z - pos->z;
    float f = 1.0f / sqrtf((d.x * d.x + d.z * d.z + d.y * d.y) + 1e-8f);
    d.x = f * d.x;
    d.y = f * d.y;
    d.z = f * d.z;

    Quat q;
    FUN_00dd91b0(&g_v0ba4, &d, &q);

    boid->mV78 = q;
    boid->mRot = q;
    boid->mV88 = q;

    boid->mpF8 = &gNames0bb0;
    void* obj = *gNames0bb0.mpBegin;
    ((void (__thiscall *)(void*, void*))VFn(obj, 0))(obj, boid);
}

// ------------------------------------------------------------------ 0x00ddcad0
// Same spawn as 0x00ddc910 but derives the direction from a cross product
// against the global at 0x016a0ba4 and a random angle (RandomDoubleUniform * the
// global angle at 0x016a0b58, sin/cos), storing the result as a quaternion.
// @ 0x00ddcad0
void Swarm::FUN_00ddcad0(const Vec3* pos, const Vec3* dir)
{
    Boid* boid = FUN_00ddc4a0();
    if (boid == 0)
        return;

    boid->mPos = *pos;
    boid->mV30 = *dir;
    boid->mStartPos = *pos;

    if ((boid->mWatch.mStartLo | boid->mWatch.mStartHi) == 0)
    {
        if (boid->mWatch.mUnits == 1)
        {
            unsigned __int64 t = __rdtsc();
            boid->mWatch.mStartLo = (uint32_t)t;
            boid->mWatch.mStartHi = (uint32_t)(t >> 32);
        }
        else
        {
            long long ctr;
            QueryPerformanceCounter(&ctr);
            boid->mWatch.mStartLo = (uint32_t)ctr;
            boid->mWatch.mStartHi = (uint32_t)(ctr >> 32);
        }
    }

    boid->mFC = 1;
    boid->mD6 = 1;
    boid->mD7 = 1;

    Vec3 c;
    c.x = pos->z * g_v0ba4.y - pos->y * g_v0ba4.z;
    c.y = pos->x * g_v0ba4.z - pos->z * g_v0ba4.x;
    c.z = pos->y * g_v0ba4.x - pos->x * g_v0ba4.y;

    float n2 = 1.0f / sqrtf((dir->y * dir->y + dir->x * dir->x) + dir->z * dir->z + 1e-8f);
    float n1 = 1.0f / sqrtf((pos->z * pos->z + (pos->y * pos->y + pos->x * pos->x)) + 1e-8f);
    if ((dir->y * n2) * (pos->x * n1) - (pos->y * n1) * (dir->x * n2) < 0.0f)
    {
        c.x = -c.x;
        c.y = -c.y;
        c.z = -c.z;
    }

    Quat q;
    FUN_00dd91b0(&g_v0ba4, &c, &q);
    boid->mV78 = q;

    double maxa = (double)g_maxAngle;
    double r = g_Random.RandomDoubleUniform() * maxa;
    double v;
    if (r >= maxa)
        v = maxa;
    else
    {
        v = r;
        if (v < 0.0)
            v = 0.0;
    }
    float s = (float)sin(v * 0.5);
    float co = (float)cos(v * 0.5);

    Quat qa;
    qa.x = s * g_v0ba4.x;
    qa.y = s * g_v0ba4.y;
    qa.z = s * g_v0ba4.z;
    qa.w = co;
    boid->mRot = qa;
    boid->mV88 = qa;

    boid->mpF8 = &gNames0bd8;
    void* obj = *gNames0bd8.mpBegin;
    ((void (__thiscall *)(void*, void*))VFn(obj, 0))(obj, boid);
}
