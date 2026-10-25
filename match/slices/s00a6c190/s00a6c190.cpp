// Slice s00a6c190 -- EA::Swarm effects manager / global params helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
// (cGlobalParams ctor uses SSE1 scalar moves; /arch:SSE is required for that unit.)
#include "types.h"
#include <string.h>
#include <intrin.h>

// ---------------------------------------------------------------------------
// external helpers / globals
extern "C" void  operator_delete__(void* p);
extern "C" void* operator_new(int size, const char* tag, int a, int b, const char* file, int line);
extern "C" bool  FUN_00a72f70(int x);
extern "C" void  FUN_00a84da0(void* stream, int version, void* rec);  // 0x00a84da0
extern "C" void  IO_ReadInt32(void* s, void* buf, int n, int pad);    // 0x0093a780
extern "C" void  FUN_0093a700(void* s, void* buf, int n, int pad);    // 0x0093a700
extern "C" void  FUN_0093a800(void* s, void* buf, int n, int pad);    // 0x0093a800
extern "C" void  FUN_005302b0(void* s, void* vec);                    // 0x005302b0
extern "C" char  g_01667bac[];                                        // 0x01667bac eastl empty-string data

// dispatch tables: 0x01675ebc stride 0x20 (8 ints), 0x01675a08 stride 0x24 (9 ints)
extern int gTblB[];
extern int gTblA[];

// mutable parameter globals used by cGlobalParams
extern float gEC;     // 0x016768ec
extern float gF0;     // 0x016768f0
extern float gF4;     // 0x016768f4
extern float gC4;     // 0x016768c4
extern float gC8;     // 0x016768c8
extern float gCC;     // 0x016768cc

// read-only constants (constant pools)
extern const char kFXIdentity4[];   // 0x01676930
extern const char kCameraInstr[];   // 0x01676998
extern const float kMilli;          // 0x013f9428 = 0.001f

// ---------------------------------------------------------------------------
// interfaces

struct IStream {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09();
    virtual void Skip(int value, int count);          // 0x28
};

struct ICollBase {
    virtual void r00();
    virtual void r04();
    virtual ICollBase* r08();
    virtual void r0c();
};

struct IComp {
    virtual void q00();
    virtual void q04();
    virtual void q08(int a, int b, int c);
    virtual void q0c();
    virtual void q10();
    virtual void q14(float f, int i);
    virtual void q18(); virtual void q1c(); virtual void q20(); virtual void q24();
    virtual void q28(); virtual void q2c(); virtual void q30(); virtual void q34();
    virtual void q38(); virtual void q3c();
    virtual void q40();
};

struct IColl7 {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s10(int a, int b, int c, int d);
    virtual void s14(int a, int b, int c);
    virtual void s18();
    virtual long long s1c(int t);
};

struct IDecal {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09();
    virtual void d28(int a, int b);
    virtual void d2c(int a, int b);
    virtual void d30(int a, int b, int c);
    virtual void d34(int a, int b, int c);
};

struct Matrix44 { char m[0x40]; void Ctor(const void* src); };
struct Matrix33 { char m[0x24]; void Assign(const void* src); };

struct FXParams {
    float f0;
    float f4;
    float f8;
    float fc;
    float f10;
    char  b14;
    char  pad15[3];
    float f18;
    int   i1c;
};

struct EString { char* begin; char* end; char* cap; };   // 12-byte SSO string

struct cEffectsManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(float a, float b);          // 0x40
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual IColl7* v21(int t);                  // 0x54

    char _pad04[0x44 - 0x04];
    ICollBase* m44;                              // 0x44
    ICollBase* m48;                              // 0x48
    int   m4c;                                   // 0x4c
    float m50;                                   // 0x50
    int   m54;                                   // 0x54
    float m58;                                   // 0x58
    float m5c;                                   // 0x5c
    float m60;                                   // 0x60
    float m64;                                   // 0x64
    unsigned m68;                                // 0x68
    char _pad6c[0xd0 - 0x6c];
    float md0;                                   // 0xd0
    float md4;                                   // 0xd4
    char _padD8[0x1f0 - 0xd8];
    void* m1f0;                                  // 0x1f0
    ICollBase* m1f4[20];                         // 0x1f4
    IComp* m244;                                 // 0x244

    void  DoUpdate(unsigned a, unsigned b);      // 0x00a6c8f0
    void  SetFlag(int index, char value);        // 0x00a6c940
    bool  GetFlag(int index);                    // 0x00a6c970
    void  SetParams(const FXParams* p);          // 0x00a6c9b0
    void  SetResources(ICollBase* p);            // 0x00a6ca10
    void  SetComponent(ICollBase* p, int type); // 0x00a6ca90
    void* GetComponent(int type);                // 0x00a6cb10
    void  Comp8(int a, int b, int c);            // 0x00a6cb30
    void  Comp14(float f, int i);                // 0x00a6cb70
    void  ResetState();                          // 0x00a6cba0
    void  SetComponent244(IComp* p);             // 0x00a6cbc0
    void* LookupA(int a, int idx, int type);     // 0x00a6cc20
    void* LookupB(int a, int idx, int type);     // 0x00a6cc50
    void  Decal30(int a, int b, int c);          // 0x00a6cc80
    void  Decal28(int a, int b);                 // 0x00a6cca0
    void  Coll10(int a, int b, int c, int d);    // 0x00a6ccc0
    void  Decal34(int a, int b, int c);          // 0x00a6cd10
    void  Decal2c(int a, int b);                 // 0x00a6cd30
    void  Coll14(int a, int b, int c);           // 0x00a6cd50
    long long GetS1c(int t);                     // 0x00a6cd70
};

struct cGlobalParams {
    float mParticleDensity;          // 0x00
    float mParticleScale;            // 0x04
    int   mParticleMultThreshold;    // 0x08
    float mMaxParticleSize;          // 0x0c
    int   mMaxParticles;             // 0x10
    int   mMaxEffects;               // 0x14
    int   mMaxDistributeSamples;     // 0x18
    Matrix44 mProjectionMatrix;      // 0x1c
    Matrix33 mCameraOrientation;     // 0x5c
    float mCameraTranslation[3];     // 0x80
    float mLODPosition[3];           // 0x8c
    float mCursorRayPoint[3];        // 0x98
    float mCursorRayDirection[3];    // 0xa4
    char  mCursorRayAvailable;       // 0xb0
    char  _padB1[3];
    int   mButtonFlags;              // 0xb4
    int   mButtonChangedFlags;       // 0xb8
    float mWindDirection[3];         // 0xbc
    float mWindPointStrength;        // 0xc8
    float mWindPoint[3];             // 0xcc
    float mGravityDirection[3];      // 0xd8
    float mGravityPointStrength;     // 0xe4
    float mGravityPoint[3];          // 0xe8
    float mSunDirection[3];          // 0xf4
    float mSunPointStrength;         // 0x100
    float mSunPoint[3];              // 0x104
    char  mShowBoundingBoxes;        // 0x110
    char  mShowSurfaces;             // 0x111
    char  mShowEffects;              // 0x112
    char  _pad113;
    float mShowEffectsScale;         // 0x114
    char  mDisableParticleAlpha;     // 0x118
    char  mDrawParticles;            // 0x119
    char  mDrawMeshes;               // 0x11a
    char  mDrawModels;               // 0x11b
    char  mDrawDecals;               // 0x11c

    cGlobalParams();
};

// ===========================================================================
// @ 0x00a6c750
extern "C" void FUN_00ab2910();
extern "C" void FUN_00aa1bb0();
extern "C" void FUN_00a97f10();
extern "C" void FUN_00aa2fa0();
extern "C" void FUN_00a871b0();
extern "C" void FUN_00abd940();
extern "C" void FUN_00a859f0();
extern "C" void FUN_00abe370();
extern "C" void FUN_00abcdf0();
extern "C" void FUN_00abe7d0();
extern "C" void FUN_00a984f0();
extern "C" void FUN_00a938d0();
extern "C" void FUN_00abb5b0();
extern "C" void FUN_00a78c10();
extern "C" void FUN_00a78560();

void __cdecl InitEffectsSubsystem()
{
    FUN_00ab2910();
    FUN_00aa1bb0();
    FUN_00a97f10();
    FUN_00aa2fa0();
    FUN_00a871b0();
    FUN_00abd940();
    FUN_00a859f0();
    FUN_00abe370();
    FUN_00abcdf0();
    FUN_00abe7d0();
    FUN_00a984f0();
    FUN_00a938d0();
    FUN_00abb5b0();
    FUN_00a78c10();
    FUN_00a78560();
}

// ===========================================================================
// @ 0x00a6c7a0
void __cdecl EmitRanges(unsigned* r, char flag, int* count, unsigned** out, int* remain)
{
    if (flag != 0) {
        unsigned lo = r[0];
        unsigned hi = r[1];
        if ((lo & hi) != 0xffffffff) {
            ++*count;
            if (*remain > 0) {
                unsigned* p = *out;
                p[0] = lo;
                p[1] = hi;
                *(unsigned*)(p + 2) = 2;
                *out = (unsigned*)((char*)*out + 0x10);
                --*remain;
            }
        }
        unsigned l6 = r[6];
        unsigned h6 = r[7];
        if (*((char*)r + 9) == 0x0f) {
            if ((l6 & h6) == 0xffffffff)
                return;
            ++*count;
            if (*remain <= 0)
                return;
            unsigned* p = *out;
            p[0] = l6;
            p[1] = h6;
            *(unsigned*)(p + 2) = 1;
            *out = (unsigned*)((char*)*out + 0x10);
            --*remain;
            return;
        }
        if ((l6 & h6) == 0xffffffff)
            return;
        ++*count;
        if (*remain <= 0)
            return;
        unsigned* p = *out;
        p[0] = l6;
        p[1] = h6;
        *(unsigned*)(p + 2) = 0;
        *out = (unsigned*)((char*)*out + 0x10);
        --*remain;
        return;
    }

    unsigned lo = r[0];
    unsigned hi = r[1];
    if (*((char*)r + 9) == 0x0f) {
        if ((lo & hi) == 0xffffffff)
            goto Lb6;
        ++*count;
        if (*remain <= 0)
            goto Lb6;
        {
            unsigned* p = *out;
            p[0] = lo;
            p[1] = hi;
            *(unsigned*)(p + 2) = 1;
        }
    }
    else {
        if ((lo & hi) == 0xffffffff)
            goto Lb6;
        ++*count;
        if (*remain <= 0)
            goto Lb6;
        {
            unsigned* p = *out;
            p[0] = lo;
            p[1] = hi;
            *(unsigned*)(p + 2) = 0;
        }
    }
    *out = (unsigned*)((char*)*out + 0x10);
    --*remain;
Lb6:
    {
        unsigned l6 = r[6];
        unsigned h6 = r[7];
        if ((l6 & h6) != 0xffffffff) {
            ++*count;
            if (*remain > 0) {
                unsigned* p = *out;
                p[0] = l6;
                p[1] = h6;
                *(unsigned*)(p + 2) = 0;
                *out = (unsigned*)((char*)*out + 0x10);
                --*remain;
            }
        }
    }
}

// ===========================================================================
// @ 0x00a6c8f0
void cEffectsManager::DoUpdate(unsigned a, unsigned b)
{
    v16((float)a * kMilli, (float)b * kMilli);
}

// ===========================================================================
// @ 0x00a6c940
void cEffectsManager::SetFlag(int index, char value)
{
    if (index < 0x20) {
        unsigned mask = 1u << index;
        if (value)
            m68 |= mask;
        else
            m68 &= ~mask;
    }
}

// ===========================================================================
// @ 0x00a6c970
bool cEffectsManager::GetFlag(int index)
{
    if (index < 0x20)
        return (m68 & (1u << index)) != 0;
    return false;
}

// ===========================================================================
// @ 0x00a6c9b0
void cEffectsManager::SetParams(const FXParams* p)
{
    m58 = p->f0;
    m5c = p->f8;
    md4 = p->f4;
    m60 = p->fc;
    m64 = p->f10;
    m4c = (p->b14 == 0);
    m50 = p->f18;
    m54 = p->i1c;
}

// ===========================================================================
// @ 0x00a6ca10
void cEffectsManager::SetResources(ICollBase* p)
{
    ICollBase* c6 = m44;
    if (p != c6) {
        if (p)
            p->r00();
        m44 = p;
        if (c6)
            c6->r04();
    }
    if (p != 0) {
        ICollBase* q = p->r08();
        ICollBase* c7 = m48;
        if (q != c7) {
            if (q)
                q->r00();
            m48 = q;
            if (c7)
                c7->r04();
        }
    }
    else {
        ICollBase* c7 = m48;
        if (c7) {
            m48 = 0;
            c7->r04();
        }
    }
}

// ===========================================================================
// @ 0x00a6ca90
void cEffectsManager::SetComponent(ICollBase* p, int type)
{
    if (type >= 0) {
        ICollBase* old = m1f4[type];
        if (p != old) {
            if (p)
                p->r08();
            m1f4[type] = p;
            if (old)
                old->r0c();
        }
    }
    else {
        ICollBase* old = (ICollBase*)m1f0;
        if (p != old) {
            if (p)
                p->r08();
            m1f0 = p;
            if (old)
                old->r0c();
        }
    }
}

// ===========================================================================
// @ 0x00a6cb10
void* cEffectsManager::GetComponent(int type)
{
    if (type >= 0) {
        void* r = m1f4[type];
        if (r)
            return r;
    }
    return m1f0;
}

// ===========================================================================
// @ 0x00a6cb30
void cEffectsManager::Comp8(int a, int b, int c)
{
    m244->q08(a, b, c);
    _ReadWriteBarrier();
}

// ===========================================================================
// @ 0x00a6cb70
void cEffectsManager::Comp14(float f, int i)
{
    m244->q14(f, i);
}

// ===========================================================================
// @ 0x00a6cba0
void cEffectsManager::ResetState()
{
    md0 = m58;
    m244->q40();
}

// ===========================================================================
// @ 0x00a6cbc0
void cEffectsManager::SetComponent244(IComp* p)
{
    IComp* old;
    if (p != 0) {
        old = m244;
        if (p == old)
            return;
    }
    else {
        p = (IComp*)v21(0);
        old = m244;
        if (p == old)
            return;
        if (p == 0)
            goto done;
    }
    p->q00();
done:
    m244 = p;
    if (old)
        old->q04();
}

// ===========================================================================
// @ 0x00a6cc20
void* cEffectsManager::LookupA(int a, int idx, int type)
{
    int* table = *(int**)((char*)this + 0x2c);
    int  obj = *(int*)((char*)table + type * 4);
    int  arr = *(int*)((char*)obj + 0xc);
    int* e = (int*)(arr + a * 0x14);
    if (e[0] == e[1])
        return 0;
    return *(void**)(e[0] + idx * 4);
}

// ===========================================================================
// @ 0x00a6cc50
void* cEffectsManager::LookupB(int a, int idx, int type)
{
    int* table = *(int**)((char*)this + 0x2c);
    int  obj = *(int*)((char*)table + type * 4);
    int  arr = *(int*)((char*)obj + 0x20);
    int* e = (int*)(arr + a * 0x14);
    if (e[0] == e[1])
        return 0;
    return *(void**)(e[0] + idx * 4);
}

// ===========================================================================
// @ 0x00a6cc80
void cEffectsManager::Decal30(int a, int b, int c)
{
    ((IDecal*)m44)->d30(a, b, c);
    _ReadWriteBarrier();
}

// ===========================================================================
// @ 0x00a6cca0
void cEffectsManager::Decal28(int a, int b)
{
    ((IDecal*)m44)->d28(a, b);
    _ReadWriteBarrier();
}

// ===========================================================================
// @ 0x00a6ccc0
void cEffectsManager::Coll10(int a, int b, int c, int d)
{
    IColl7* p = (IColl7*)m48;
    if (p) {
        p->s10(a, b, c, d);
        _ReadWriteBarrier();
    }
}

// ===========================================================================
// @ 0x00a6cd10
void cEffectsManager::Decal34(int a, int b, int c)
{
    ((IDecal*)m44)->d34(a, b, c);
    _ReadWriteBarrier();
}

// ===========================================================================
// @ 0x00a6cd30
void cEffectsManager::Decal2c(int a, int b)
{
    ((IDecal*)m44)->d2c(a, b);
    _ReadWriteBarrier();
}

// ===========================================================================
// @ 0x00a6cd50
void cEffectsManager::Coll14(int a, int b, int c)
{
    IColl7* p = (IColl7*)m48;
    if (p) {
        p->s14(a, b, c);
        _ReadWriteBarrier();
    }
}

// ===========================================================================
// @ 0x00a6cd70
long long cEffectsManager::GetS1c(int t)
{
    IColl7* p = (IColl7*)m48;
    if (p)
        return p->s1c(t);
    return 0xFFFFFFFFFFFFFFFFull;
}

// ===========================================================================
// @ 0x00a6cd90
bool __stdcall RangeNotEmpty(void* p)
{
    int a = *(int*)((char*)p + 0x10);
    if (a != *(int*)((char*)p + 0x14))
        return FUN_00a72f70(a);
    return false;
}

// ===========================================================================
// @ 0x00a6cdb0
cGlobalParams::cGlobalParams()
{
    mParticleDensity = 1.0f;
    mParticleScale = 1.0f;
    mParticleMultThreshold = 0x14;
    mMaxParticleSize = 1000.0f;
    mMaxParticles = 0;
    mMaxEffects = 0;
    mMaxDistributeSamples = 0;
    mProjectionMatrix.Ctor(&kFXIdentity4);
    mCameraOrientation.Assign(&kCameraInstr);
    mCameraTranslation[0] = 0.0f;
    mCameraTranslation[1] = 0.0f;
    mCameraTranslation[2] = 0.0f;
    mLODPosition[0] = 0.0f;
    mLODPosition[1] = 0.0f;
    mLODPosition[2] = 0.0f;
    mCursorRayPoint[0] = 0.0f;
    mCursorRayPoint[1] = 0.0f;
    mCursorRayPoint[2] = 0.0f;
    mCursorRayDirection[0] = 0.0f;
    mCursorRayDirection[1] = 0.0f;
    mCursorRayDirection[2] = 1.0f;
    mCursorRayAvailable = 0;
    mButtonFlags = 0;
    mButtonChangedFlags = 0;
    mWindDirection[0] = gEC;
    mWindDirection[1] = gF0;
    mWindDirection[2] = gF4;
    mWindPointStrength = 0.0f;
    mWindPoint[0] = gEC;
    mWindPoint[1] = gF0;
    mWindPoint[2] = gF4;
    mGravityDirection[0] = 0.0f;
    mGravityDirection[1] = 0.0f;
    mGravityDirection[2] = -1.0f;
    mGravityPointStrength = 0.0f;
    mGravityPoint[0] = gEC;
    mGravityPoint[1] = gF0;
    mGravityPoint[2] = gF4;
    mSunDirection[0] = gC4;
    mSunDirection[1] = gC8;
    mSunDirection[2] = gCC;
    mSunPointStrength = 0.0f;
    mSunPoint[0] = gC4;
    mSunPoint[1] = gC8;
    mSunPoint[2] = gCC;
    mShowBoundingBoxes = 0;
    mShowSurfaces = 0;
    mShowEffects = 0;
    mShowEffectsScale = 0.1f;
    mDisableParticleAlpha = 0;
    mDrawParticles = 1;
    mDrawMeshes = 1;
    mDrawModels = 1;
    mDrawDecals = 1;
}

// ===========================================================================
// @ 0x00a6d000
struct GmeRefCount {
    int ScalarDeletingDestructor(unsigned flags);
};
int GmeRefCount::ScalarDeletingDestructor(unsigned flags)
{
    *(void**)((char*)this + 4) = (void*)0x013ef094;
    if (flags & 1)
        operator_delete__(this);
    return (int)this;
}

// ===========================================================================
// ---------------------------------------------------------------------------
// containers walked by the Ctx2 stream reader below

struct IRefCounted {                    // vptr @ 0, reference count @ +4
    virtual void Destroy(int flags);
    int mnRefCount;
};

struct RefVec {                         // 0x14-byte slot vector (this+0x0c / +0x20)
    IRefCounted** mpBegin;              // 0x00
    IRefCounted** mpEnd;                // 0x04
    IRefCounted** mpCap;                // 0x08
    int mPad0c[2];
    void resize(unsigned count);                        // 0x00a6ae70
};

struct Rec58 { char mBytes[0x58]; };    // one 0x58-byte effect record

struct Rec58Vec {
    Rec58* mpBegin;                     // 0x00
    Rec58* mpEnd;                       // 0x04
    Rec58* mpCap;                       // 0x08
    int mPad0c[2];
    void resize(unsigned count);                        // 0x00a6c030
};

struct T8 { int m0; int m4; };          // one 8-byte vector element

struct Vec8 {
    T8* mpBegin;                        // 0x00
    T8* mpEnd;                          // 0x04
    T8* mpCap;                          // 0x08
    int mPad0c[2];
    void insert_n(T8* pos, unsigned n, const T8* elem);  // 0x00a6aaa0
};

struct HNode;
struct HTInsertOut { int mWords[3]; };  // thin insert-return scratch

struct HashTable {                      // node table (this+0x48 and this+0x68)
    unsigned mx00;                      // 0x00
    HNode** mpBuckets;                  // 0x04
    unsigned mBucketCount;              // 0x08
    unsigned mSize;                     // 0x0c
    HashTable* insert_node(HTInsertOut* out, const EString* key, unsigned flag); // 0x00a6a810
};

struct Key { int m0; int m4; };         // 8-byte resource key
struct KeyPair { Key mKey; int mValue; };

struct Ctx2 {
    char _pad00[0xc];
    RefVec* mpSlotsB;                   // 0x0c
    char _pad10[0x10];
    RefVec* mpSlotsA;                   // 0x20
    char _pad24[0x10];
    Rec58Vec mRecs;                     // 0x34
    HashTable mStrMap;                  // 0x48
    char _pad58[0x10];
    HashTable mKeyMap;                  // 0x68
    char _pad78[0x10];
    Vec8 mVec8;                         // 0x88

    bool Read(void* stream);
};

static const char kAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// @ 0x00a6c190
bool Ctx2::Read(void* stream)
{
    typedef IRefCounted* (__cdecl* RefFactory)(void* stream, unsigned version);

    unsigned version = 0;
    unsigned tagB = 0;
    unsigned tagA = 0;
    unsigned skip = 0;
    unsigned count = 0;
    int      id = 0;
    Key      key;
    EString  str;

    FUN_0093a700(stream, &version, 1, 0);
    if ((unsigned short)version != 4)
        return false;

    // ---- dispatch table B (stride 0x20) ------------------------------------
    FUN_0093a700(stream, &tagB, 1, 0);
    while ((unsigned short)tagB != 0xffff) {
        unsigned t = (unsigned short)tagB;
        FUN_0093a700(stream, &version, 1, 0);
        IO_ReadInt32(stream, &skip, 1, 0);
        if (gTblB[t * 8] == 0 ||
            (int)(unsigned short)version < gTblB[t * 8 + 3] ||
            gTblB[t * 8 + 4] < (int)(unsigned short)version) {
            ((IStream*)stream)->Skip((int)skip, 1);
        }
        else {
            IO_ReadInt32(stream, &count, 1, 0);
            mpSlotsB[t].resize(count);
            for (int i = 0; i < (int)count; ++i) {
                IRefCounted** slot = mpSlotsB[t].mpBegin + i;
                RefFactory make = (RefFactory)(void*)(uintptr_t)(unsigned)gTblB[t * 8];
                IRefCounted* created = make(stream, (unsigned short)version);
                IRefCounted* old = *slot;
                if (created != old) {
                    if (created)
                        ++created->mnRefCount;
                    *slot = created;
                    if (old) {
                        --old->mnRefCount;
                        if (old->mnRefCount == 0) {
                            old->mnRefCount = 1;
                            old->Destroy(1);
                        }
                    }
                }
            }
        }
        FUN_0093a700(stream, &tagB, 1, 0);
    }

    // ---- dispatch table A (stride 0x24) ------------------------------------
    FUN_0093a700(stream, &tagA, 1, 0);
    while ((unsigned short)tagA != 0xffff) {
        unsigned t = (unsigned short)tagA;
        FUN_0093a700(stream, &version, 1, 0);
        IO_ReadInt32(stream, &skip, 1, 0);
        if (gTblA[t * 9] == 0 ||
            (int)(unsigned short)version < gTblA[t * 9 + 3] ||
            gTblA[t * 9 + 4] < (int)(unsigned short)version) {
            ((IStream*)stream)->Skip((int)skip, 1);
        }
        else {
            IO_ReadInt32(stream, &count, 1, 0);
            mpSlotsA[t].resize(count);
            for (int i = 0; i < (int)count; ++i) {
                IRefCounted** slot = mpSlotsA[t].mpBegin + i;
                RefFactory make = (RefFactory)(void*)(uintptr_t)(unsigned)gTblA[t * 9];
                IRefCounted* created = make(stream, (unsigned short)version);
                IRefCounted* old = *slot;
                if (created != old) {
                    if (created)
                        ++created->mnRefCount;
                    *slot = created;
                    if (old) {
                        --old->mnRefCount;
                        if (old->mnRefCount == 0) {
                            old->mnRefCount = 1;
                            old->Destroy(1);
                        }
                    }
                }
            }
        }
        FUN_0093a700(stream, &tagA, 1, 0);
    }

    // ---- vector of 0x58-byte records ---------------------------------------
    FUN_0093a700(stream, &version, 1, 0);
    IO_ReadInt32(stream, &count, 1, 0);
    mRecs.resize(count);
    {
        int records = (int)(((char*)mRecs.mpEnd - (char*)mRecs.mpBegin) / 0x58);
        for (int i = 0; i < records; ++i)
            FUN_00a84da0(stream, (unsigned short)version, &mRecs.mpBegin[i]);
    }

    // ---- 8-byte-keyed node table (this+0x68) -------------------------------
    ((void (__thiscall*)(void*, void**, unsigned))0x007611f0)
        (&mKeyMap, (void**)mKeyMap.mpBuckets, mKeyMap.mBucketCount);
    mKeyMap.mSize = 0;
    IO_ReadInt32(stream, &id, 1, 0);
    while (id >= 0) {
        FUN_0093a800(stream, &key, 1, 0);
        KeyPair pair;
        pair.mKey = key;
        pair.mValue = id;
        HTInsertOut out;
        ((void (__thiscall*)(void*, void*, const void*, unsigned))0x00594b60)
            (&mKeyMap, &out, &pair, 0);
        IO_ReadInt32(stream, &id, 1, 0);
    }

    // ---- string-keyed node table (this+0x48) -------------------------------
    ((void (__thiscall*)(void*, void**, unsigned))0x006a85b0)
        (&mStrMap, (void**)mStrMap.mpBuckets, mStrMap.mBucketCount);
    mStrMap.mSize = 0;
    str.begin = g_01667bac;
    str.end = g_01667bac;
    str.cap = g_01667bac + 1;
    IO_ReadInt32(stream, &id, 1, 0);
    while (id >= 0) {
        FUN_005302b0(stream, &str);
        {
            int len = (int)(str.end - str.begin);
            char* dst;
            char* cap;
            if (len + 1 <= 1) {
                dst = g_01667bac;
                cap = g_01667bac + 1;
            }
            else {
                dst = (char*)operator_new(len + 1, "EASTL", 0, 0, kAllocatorFile, 0xd1);
                cap = dst + len + 1;
            }
            memcpy(dst, str.begin, (size_t)len);
            dst[len] = 0;
            EString keyCopy;
            keyCopy.begin = dst;
            keyCopy.end = dst + len;
            keyCopy.cap = cap;
            HTInsertOut out;
            mStrMap.insert_node(&out, &keyCopy, 0);
            if (cap - dst > 1 && dst)
                operator_delete__(dst);
        }
        IO_ReadInt32(stream, &id, 1, 0);
    }

    // ---- vector of 8-byte records (this+0x88) ------------------------------
    IO_ReadInt32(stream, &count, 1, 0);
    {
        unsigned have = (unsigned)(mVec8.mpEnd - mVec8.mpBegin);
        if (have < count) {
            T8 zero;
            zero.m0 = 0;
            zero.m4 = 0;
            mVec8.insert_n(mVec8.mpEnd, count - have, &zero);
        }
        else {
            T8* newEnd = mVec8.mpBegin + count;
            memcpy(newEnd, mVec8.mpEnd, 0);
            mVec8.mpEnd = newEnd;
        }
        for (unsigned i = 0; i < count; ++i)
            FUN_0093a800(stream, &mVec8.mpBegin[i], 1, 0);
    }

    if (str.cap - str.begin > 1 && str.begin)
        operator_delete__(str.begin);
    return true;
}
