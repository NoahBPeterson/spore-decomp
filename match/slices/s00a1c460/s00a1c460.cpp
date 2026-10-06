// Slice s00a1c460 - EA::Audio::Sound primitive configuration / ticking.
// Retail Sound layout differs from the 2008 PDB (fields shifted), so members are placed by
// offset recovered from the asm. Virtual slots are named by role where known.
#include "types.h"
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

template<int N> inline void ScratchSlots() { u32 s[N]; }

struct SystemAT;
void* operator_new(void* alloc, const char* name, int flags, int align, const char* file, int line);
void  FUN_00a1aad0(void* self, void* arg, int zero);

struct BasicString {
    void assign(void* v);
};

inline const float& FMin(const float& a, const float& b) { return (b < a) ? b : a; }
inline const float& FMax(const float& a, const float& b) { return (a < b) ? b : a; }

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3 operator-(const Vec3& o) const { return Vec3(x - o.x, y - o.y, z - o.z); }
    float LengthSq() const { return x * x + y * y + z * z; }
};

// Primitive (refcounted; AddRef/Release in slots 0/1).
struct IPrim {
    virtual void AddRef();                    // +0x00
    virtual void Release();                   // +0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual float GetValue(int);              // +0x1c
    virtual bool v20(int);                    // +0x20
    virtual void v24();
    virtual void SetValue(float, int);        // +0x28
    virtual void SetEnabled(bool);            // +0x2c
};

template <class T> struct ARC {
    T* p;
    ARC() : p(0) {}
    ~ARC() { if (p) p->Release(); }
    void Reset() { if (p) { T* o = p; p = 0; o->Release(); } }
    ARC& operator=(T* o) {
        if (o != p) {
            T* old = p;
            if (o) o->AddRef();
            p = o;
            if (old) old->Release();
        }
        return *this;
    }
};

// Sound emitter interface (slots used by Sound).
struct IEmitter {
    virtual void e00(); virtual void e04(); virtual void e08(); virtual void e0c();
    virtual void e10(); virtual void e14(); virtual void e18();
    virtual void SetFlag(int);                              // +0x1c
    virtual bool e20(int);                                  // +0x20
    virtual void e24(); virtual void e28();
    virtual void SetProperty(u32 key, float v, int one);    // +0x2c
    virtual bool GetProperty(u32 key, float* out);          // +0x30
    virtual void SetData(u32 key, void* data, u32 size);    // +0x34
};

// Hash map nodes (eastl::hashtable: bucket array + sentinel at buckets[count]).
struct PropNode { u32 key; float value; PropNode* next; };
struct PrimNode { u32 key; IPrim* prim; PrimNode* next; };

template <class N> struct HMap {
    N** mpBuckets;
    u32 mBucketCount;
    struct Iter {
        N* mpNode;
        N** mpBucket;
        void inc() {
            mpNode = mpNode->next;
            while (!mpNode)
                mpNode = *++mpBucket;
        }
    };
    Iter begin() {
        Iter it;
        it.mpBucket = mpBuckets;
        it.mpNode = *mpBuckets;
        if (!it.mpNode) {
            ++it.mpBucket;
            while (*it.mpBucket == 0)
                ++it.mpBucket;
            it.mpNode = *it.mpBucket;
        }
        return it;
    }
    N* end() { return mpBuckets[mBucketCount]; }
};

// Embedded configuration object at Sound+0xe4.
struct ConfigObj {
    virtual void c00(); virtual void c04(); virtual void c08(); virtual void c0c();
    virtual void c10(); virtual void c14(); virtual void c18(); virtual void c1c();
    virtual void c20(); virtual void c24(); virtual void c28(); virtual void c2c();
    virtual void c30(); virtual void c34(); virtual void c38(); virtual void c3c();
    virtual void c40();
    virtual bool GetData(u32 key, int* size, void** data);       // +0x44
    virtual bool GetArray(u32 key, u32* count, u32** arr);       // +0x48
    u8 pad[0x10];
};

struct ISoundMix {                                       // second base at +4
    virtual void m00(); virtual void m04(); virtual void m08();
    virtual void SetProp(u32 key, float v, int one);     // +0x0c
    virtual bool GetProp(u32 key, float* out);           // +0x10
    virtual void m14();
    virtual bool AddPrimitive(u32 key, IPrim* p);        // +0x18
};

struct RCurve {
    u8 mData[0x364];
    float GetOutputValue(float in);                      // 0xa1a110
};

struct LerpF { float Get(); };                           // 0xa1b020 (thiscall, returns float)

struct ISystem {
    virtual void s00();
    virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10(); virtual void s14();
    virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24(); virtual void s28();
    virtual void s2c(); virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c(); virtual void s50();
    virtual void s54(); virtual void s58(); virtual void s5c(); virtual void s60(); virtual void s64();
    virtual void s68(); virtual void s6c(); virtual void s70(); virtual void s74(); virtual void s78();
    virtual Vec3* GetPosition(u32 handle);               // +0x7c
    virtual void s80(); virtual void s84(); virtual void s88(); virtual void s8c(); virtual void s90();
    virtual void s94(); virtual void s98(); virtual void s9c(); virtual void sa0(); virtual void sa4();
    virtual void sa8(); virtual void sac(); virtual void sb0(); virtual void sb4(); virtual void sb8();
    virtual void sbc(); virtual void sc0(); virtual void sc4(); virtual void sc8(); virtual void scc();
    virtual void sd0(); virtual void sd4(); virtual void sd8(); virtual void sdc(); virtual void se0();
    virtual bool GetPrimitive(u32 key, void* outArc);    // +0xe4
    virtual void se8(); virtual void sec(); virtual void sf0(); virtual void sf4(); virtual void sf8();
    virtual void sfc(); virtual void s100(); virtual void s104(); virtual void s108(); virtual void s10c();
    virtual void s110(); virtual void s114(); virtual void s118(); virtual void s11c(); virtual void s120();
    virtual void s124(); virtual void s128(); virtual void s12c(); virtual void s130(); virtual void s134();
    virtual void s138(); virtual void s13c(); virtual void s140(); virtual void s144(); virtual void s148();
    virtual void s14c(); virtual void s150(); virtual void s154(); virtual void s158(); virtual void s15c();
    virtual void s160(); virtual void s164(); virtual void s168(); virtual void s16c(); virtual void s170();
    virtual void s174(); virtual void s178(); virtual void s17c(); virtual void s180(); virtual void s184();
    virtual void s188(); virtual void s18c(); virtual void s190(); virtual void s194(); virtual void s198();
    virtual void s19c(); virtual void s1a0(); virtual void s1a4();
    virtual float GetSpeed(Vec3* pos);                   // +0x1a8
};

ISystem* GetSystemAT();                                  // EA::Audio::GetSystemAT

// Newly allocated response-curve primitive (PResp, 0x38c bytes; ctor at 0xa173f0).
struct PRespObj : IPrim {
    PRespObj(void* owner);
    void SetCurveData(void* data, int n);                // 0xa171c0 -> SetResponseCurveData(+0xc)
    void SetModSource(IPrim* src);                       // 0xa37080
    static void* operator new(size_t);                   // 0xa171e0 (fixed pool alloc)
    static void  operator delete(void*);
    u8 pad[0x38c - 4];
};

// Virtual interface of Sound (primary vtable).
struct SoundV {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void Stop(int, int, float, int);
    virtual bool Query(int, int);
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c(float);
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78(bool);
    virtual void v7c();
    virtual void v80(int, int);
    virtual void v84();
    virtual bool v88(float);
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void SetPropValue(u32 key, float v);
    virtual void v9c();
    virtual void va0(void*);
    virtual void va4(void*);
    virtual void va8();
    virtual void vac();
    virtual void vb0();
    virtual void vb4(u32, u32, IPrim*);
};

struct Sound : SoundV, ISoundMix {
    u8   pad0[0x44 - 8];
    IEmitter* mpEmitter;      // +0x44
    float mDist;              // +0x48
    u8   pad1[0x54 - 0x4c];
    float mMaxDistance;       // +0x54
    float mGain;              // +0x58
    u8   pad2[0x60 - 0x5c];
    float mMaxGainChange;     // +0x60
    float mAttenGain;         // +0x64
    float mLastGain;          // +0x68
    u8   pad3[0x74 - 0x6c];
    float mLowPass;           // +0x74
    float mHighPass;          // +0x78
    float mDopplerPitch;      // +0x7c
    float mRandomPitch;       // +0x80
    float mPitch;             // +0x84
    float mSpeed;             // +0x88
    float mSmoothSpeed;       // +0x8c
    float mLastPitch;         // +0x90
    u8   pad4[0x9d - 0x94];
    u8   mb9d;                // +0x9d
    u8   mb9e;                // +0x9e
    u8   pad5;
    u8   mbDirect;            // +0xa0
    u8   pad6[3];
    u32  mPosHandle;          // +0xa4
    Vec3 mPos;                // +0xa8
    Vec3 mVelDelta;           // +0xb4
    u8   mMode;               // +0xc0
    u8   pad7[3];
    Vec3 mDirectPos;          // +0xc4
    u8   pad8[0xd8 - 0xd0];
    float mWetLevel;          // +0xd8
    u8   pad9[0xe4 - 0xdc];
    ConfigObj mConfig;        // +0xe4
    u8   pad10[0xfc - 0xe4 - sizeof(ConfigObj)];
    HMap<PropNode> mProps;    // +0xfc
    u8   pad11[0x320 - 0x104];
    u32  mSoundId;            // +0x320
    float mStartDelay;        // +0x324
    u8   pad12[0x32c - 0x328];
    float mElapsed;           // +0x32c
    u8   pad13[0x33c - 0x330];
    HMap<PrimNode> mPrims;    // +0x33c
    u8   pad14[0xc94 - 0x344];
    LerpF mFader;             // +0xc94
    u8   pad15[0xcd0 - 0xc95];
    float mFinishTime;        // +0xcd0
    u8   mbHasFinish;         // +0xcd4
    u8   pad16[0xce4 - 0xcd5];
    u32  mFlags;              // +0xce4
    u8   pad17[0xcec - 0xce8];
    RCurve mCurveA;           // +0xcec
    RCurve mCurveB;           // +0x1050
    RCurve mCurveC;           // +0x13b4
    RCurve mCurveD;           // +0x1718
    RCurve mCurveE;           // +0x1a7c
    u8   padF[0x1df0 - 0x1de0];
    float mFadeTo;            // +0x1df0
    float mFadeCur;           // +0x1df4
    float mFadeRate;          // +0x1df8
    char* mStrBegin;          // +0x1dfc
    char* mStrEnd;            // +0x1e00
    u8   pad18[0x1e0c - 0x1e04];
    int  mCount;              // +0x1e0c

    bool StrEmpty() { return mStrBegin == mStrEnd; }
    char* StrData() { return mStrBegin; }
    u32 StrSize() { return mStrEnd - mStrBegin; }
    void UpdatePropertiesFromPrimitives(bool all);   // 00a1cf60
    void CommitAllProperties();                      // 00a1d080
    void SetData(u32 id, void* arg, u32 arg4);       // 00a1d310
    int  TickInternal(int unused, float dt, bool force); // 00a1c710
    bool ConfigurePrimitives();                      // 00a1c460
};

// ---------------------------------------------------------------------------
// 00a1cf10 - hash node free-list allocation (eastl fixed_pool insert)
// ---------------------------------------------------------------------------
struct NodePool {
    u8     pad0[0x1c];
    void*  mpFree;      // +0x1c
    u8     pad1[0xc];   // +0x20
    void*  mpAlloc;     // +0x2c

    void Insert(void* v);
};

// @ 0x00a1cf10
void NodePool::Insert(void* v)
{
    void* p = mpFree;
    if (p != 0) {
        mpFree = *(void**)p;
    } else {
        p = operator_new(mpAlloc, "EASTL", 0, 0, "EASTL/allocator.h", 0xd1);
    }
    if (p != 0) {
        *(u32*)p = *(const u32*)v;
        *(u32*)((char*)p + 4) = *(const u32*)((char*)(v) + 4);
    }
    *(u32*)((char*)p + 8) = 0;
}


// @ 0x00a1cf60
void Sound::UpdatePropertiesFromPrimitives(bool all)
{
    ScratchSlots<1>();
    if (all) {
        HMap<PrimNode>::Iter it = mPrims.begin();
        PrimNode* end = mPrims.end();
        while (it.mpNode != end) {
            it.mpNode->prim->SetValue(0.0f, 0);
            it.inc();
        }
    }
    HMap<PrimNode>::Iter it = mPrims.begin();
    PrimNode* end = mPrims.end();
    while (it.mpNode != end) {
        u32 key = it.mpNode->key;
        IPrim* prim = it.mpNode->prim;
        if (all || prim->v20(0))
            SetPropValue(key, prim->GetValue(1));
        it.inc();
    }
}

// @ 0x00a1d080
void Sound::CommitAllProperties()
{
    if (!mpEmitter)
        return;
    HMap<PropNode>::Iter it = mProps.begin();
    PropNode* end = mProps.end();
    while (it.mpNode != end) {
        mpEmitter->SetProperty(it.mpNode->key, it.mpNode->value, 1);
        it.inc();
    }
    if (!(mMode & 8) && mCount >= 2) {
        if (mFlags & 0x8000) mpEmitter->SetProperty(0x647a7836, mHighPass, 1);
        if (mFlags & 0x10000) mpEmitter->SetProperty(0xa26a765f, mDopplerPitch, 1);
        if (mFlags & 0x20000) mpEmitter->SetProperty(0x49eb68db, mLowPass, 1);
    }
    if (mbDirect) {
        if (mMode & 1) mpEmitter->SetProperty(0x50c5d67, mDirectPos.x, 1);
        if (mMode & 2) mpEmitter->SetProperty(0x50c5d66, mDirectPos.y, 1);
        if (mMode & 4) mpEmitter->SetProperty(0x50c5d65, mDirectPos.z, 1);
    } else {
        if (mMode & 1) mpEmitter->SetProperty(0x50c5d67, mPos.x, 1);
        if (mMode & 2) mpEmitter->SetProperty(0x50c5d66, mPos.y, 1);
        if (mMode & 4) mpEmitter->SetProperty(0x50c5d65, mPos.z, 1);
    }
    if (mMode & 8) {
        mpEmitter->SetProperty(0xf616b72, mMaxDistance, 1);
        mpEmitter->SetProperty(0x3593710, mGain, 1);
    }
    mpEmitter->SetProperty(0x12d2a4d4, (mMode & 8) ? 1.0f : 0.0f, 1);
    mpEmitter->SetProperty(0x6df5822d, (float)mCount, 1);
    if (!StrEmpty())
        mpEmitter->SetData(0x2fe09c83, StrData(), StrSize());
}

// @ 0x00a1d310
void Sound::SetData(u32 id, void* arg, u32 arg4)
{
    void* target = 0;
    switch (id) {
    case 0x173c2710: target = &mCurveC; break;
    case 0x8adce22f: target = &mCurveB; break;
    case 0x9b3918c4: target = &mCurveE; break;
    case 0xbdc98ce5: target = &mCurveA; break;
    case 0x2fe09c83: {
        ((BasicString*)&mStrBegin)->assign(arg);
        ISystem* sys = GetSystemAT();
        mSoundId = ((u32 (__thiscall*)(void*, void*))((*(void***)sys)[0xf4 / 4]))(sys, arg);
        break;
    }
    case 0x14043549:
        va4(arg);
        return;
    case 0x7cb81a35:
    case 0xf58ca0be:
        va0(arg);
        return;
    default:
        break;
    }
    if (target != 0)
        FUN_00a1aad0(target, arg, 0);
    IEmitter* em = mpEmitter;
    if (em != 0 && arg != 0)
        em->SetData(id, arg, arg4);
}


// @ 0x00a1c460
bool Sound::ConfigurePrimitives()
{
    u32 count;
    u32* arr;
    if (!mConfig.GetArray(0x3da0a727, &count, &arr))
        return false;
    while (count != 0) {
        if (count < 2)
            return false;
        count -= 2;
        u32 c = 0;
        u32 a = *arr++;
        u32 b = *arr++;
        if (a == 0 || b == 0)
            return false;
        if (count != 0) {
            c = *arr++;
            --count;
            if (count != 0 && *arr == 0) {
                ++arr;
                --count;
            }
        }
        ARC<IPrim> prim;
        if (c != 0) {
            int size;
            void* data;
            if (mConfig.GetData(c, &size, &data)) {
                PRespObj* r = new PRespObj(this);
                if (r) prim = r;
                ((PRespObj*)prim.p)->SetCurveData(data, size / 2);
                prim.p->SetEnabled(true);
            }
        }
        ARC<IPrim> sysPrim;
        ISystem* sys = GetSystemAT();
        sysPrim.Reset();
        if (sys->GetPrimitive(b, &sysPrim)) {
            if (prim.p) {
                ((PRespObj*)prim.p)->SetModSource(sysPrim.p);
                prim.p->v10();
                sysPrim = prim.p;
            }
            if (!((ISoundMix*)this)->AddPrimitive(a, sysPrim.p)) {
                sysPrim.p->SetEnabled(false);
                return false;
            }
        } else {
            vb4(a, b, prim.p);
        }
    }
    return true;
}

// @ 0x00a1c710
int Sound::TickInternal(int unused, float dt, bool force)
{
    float tmp;
    if (!mpEmitter->GetProperty(0x893f8476, &mElapsed))
        mElapsed += dt;
    bool b1 = Query(-1, 1);
    v78(force);
    if (force)
        v5c(dt);
    if ((mFlags & 0x400) && !(mFlags & 0x80) && mStartDelay >= mFinishTime)
        v80(0, 0);
    if (mbHasFinish && !(mFlags & 0x80) && mpEmitter) {
        float a;
        float b;
        if (mpEmitter->GetProperty(0xd24d4aff, &a)) {
            ((ISoundMix*)this)->GetProp(0xe8ab99b9, &b);
            float rem = (a > b) ? a - b : 0.0f;
            if (mElapsed >= rem)
                v80(0, 0);
        }
    }
    if (mFadeCur != mFadeTo) {
        float diff = mFadeTo - mFadeCur;
        float sign = (diff >= 0.0f) ? 1.0f : -1.0f;
        float ad = (float)fabs(diff);
        float step = mFadeRate * dt;
        if (step > ad) step = ad;
        mFadeCur = step * sign + mFadeCur;
    }
    if ((mFlags & 0x800) && mFadeCur == 0.0f && mpEmitter) {
        mFlags &= ~0x800u;
        mpEmitter->SetFlag(1);
    }
    float pf = mFadeCur;
    float g = mAttenGain;
    float v = mFader.Get() * g * pf;
    if (!(mMode & 8) || mMode == 0xf) {
        if (v88(g)) {
            if (mb9d != 0) {
                if (!Query(2, 0))
                    Stop(1, 2, 0.0f, 1);
            } else {
                v80(3, 0);
            }
        } else if (Query(2, 0)) {
            Stop(0, 2, 0.0f, 1);
        }
    }
    if (mpEmitter && !b1) {
        float prev = mLastGain;
        if (v != prev) {
            float lim = mMaxGainChange;
            if (lim > 0.0f && prev >= 0.0f) {
                float d = v - prev;
                float ad = (float)fabs(d);
                if (ad > lim)
                    v = (d / ad) * lim + prev;
            }
            mpEmitter->SetProperty(0x25df0108, v, 1);
        }
        mLastGain = v;
        if (mb9e && mMode == 0xf) {
            ((ISoundMix*)this)->SetProp(0x8c37ecc7, mDist, 1);
            ((ISoundMix*)this)->SetProp(0xdb495023, GetSystemAT()->GetSpeed(&mPos), 1);
            if (mbDirect) {
                mpEmitter->SetProperty(0x50c5d67, mDirectPos.x, 1);
                mpEmitter->SetProperty(0x50c5d66, mDirectPos.y, 1);
                mpEmitter->SetProperty(0x50c5d65, mDirectPos.z, 1);
                mpEmitter->SetProperty(0x26341ede, mWetLevel, 1);
            } else {
                mpEmitter->SetProperty(0x50c5d67, mPos.x, 1);
                mpEmitter->SetProperty(0x50c5d66, mPos.y, 1);
                mpEmitter->SetProperty(0x50c5d65, mPos.z, 1);
            }
            float hp = 96000.0f;
            float dop = 0.0f;
            float lp = 0.0f;
            if (mCount >= 2) {
                float o1 = mCurveA.GetOutputValue(mDist);
                hp = FMin(mHighPass, o1);
                float o2 = mCurveB.GetOutputValue(mDist);
                dop = FMax(mDopplerPitch, o2);
                float o3 = mCurveC.GetOutputValue(mDist);
                lp = FMax(mLowPass, o3);
                if (mFlags & 0x4000) {
                    Vec3* p = GetSystemAT()->GetPosition(mPosHandle);
                    Vec3 d = *p - mPos;
                    Vec3 vv = d - mVelDelta;
                    mVelDelta = d;
                    float sp = (float)sqrt(vv.x * vv.x + vv.z * vv.z + vv.y * vv.y) / dt * 0.1f;
                    mSmoothSpeed = mSmoothSpeed * 0.9f + sp;
                    float sg = (0.0f > mSmoothSpeed) ? -1.0f : 1.0f;
                    mRandomPitch = mCurveD.GetOutputValue((float)fabs(mSmoothSpeed)) * sg + 1.0f;
                }
            }
            mpEmitter->SetProperty(0x647a7836, hp, 1);
            mpEmitter->SetProperty(0xa26a765f, dop, 1);
            mpEmitter->SetProperty(0x49eb68db, lp, 1);
        }
        if (mSpeed != mLastPitch) {
            float x = mPitch * mRandomPitch * mSpeed;
            mpEmitter->SetProperty(0x71bc3009, x, 1);
            mLastPitch = x;
        }
    }
    return 0;
}
