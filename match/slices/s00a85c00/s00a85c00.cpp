// slice s00a85c00 -- EA::Swarm distribute emitter helper ("cDistributeEffectSimulator",
// name guessed).  0x00a85c00..0x00a86114 are the methods of one GmeIComponent-derived
// class (its two vtables are 0x1458130 / 0x145812c); 0x00a86120.. onwards belongs to the
// sibling distribution-simulator class that shares the same vtable pair.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <new>

typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t  uint8;

// ---------------------------------------------------------------- math
struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };

// rw::math::fpu::Matrix33Template<float,0> (0x24 bytes, out-of-line copy at 0x0041cb40).
struct Matrix3 {
    float m[9];
    Matrix3(const Matrix3& o);            // 0x0041cb40
    Matrix3& operator=(const Matrix3& o);
};

// 2008 PDB layout of the distribution description (only the parts this slice reads).
struct cDistributeDescription {
    uint32 pad00[2];
    uint32 mMask;                         // +0x08  bit0: emitter mode, bit1: emit map used
    uint32 pad0c[3];
    uint8  mSourceType;                   // +0x1c
    uint8  pad1d[3];
    float  mScale;                        // +0x20
    uint32 pad24[3];
    float  mSizeScale;                    // +0x30
    uint32 pad34[(0x98 - 0x34) / 4];
    float  mParam98;                      // +0x98
    float  mParam9c;                      // +0x9c
    float  mParamA0;                      // +0xa0
    uint32 padA4[4];
    uint32 mHandleB0;                     // +0xb0
    uint32 mHandleB4;                     // +0xb4
};

// The 0x38-byte curve vector used by the description IO (sp_vector<float>, header at [-1]).
struct FloatCurve {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32 mAllocator[2];
};
typedef FloatCurve FloatVec;

// Vtable-only interface used through the emitter/streamer slots.
struct cIRefObj {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void SetHandle(uint32 h);
};

// ===========================================================================
// The component implementing 0x00a85c00..0x00a860e0.
// ===========================================================================
struct cDistributeDescInit;
struct cSimulatorWorld;
struct cDistributeSimulator {
    volatile uint32 mVtbl00;              // +0x000 (GmeIComponent / simulator)
    volatile uint32 mVtbl04;              // +0x004 (GmeRefCount)
    uint32 pad08;
    cDistributeDescInit* mDesc;           // +0x00c
    uint8  mActive;                       // +0x010
    uint8  pad11[3];
    uint16 mFlags14;                      // +0x014
    uint16 mModCount16;                   // +0x016
    float  mCenterX;                      // +0x018
    float  mCenterY;                      // +0x01c
    float  mCenterZ;                      // +0x020
    float  mRadius;                       // +0x024
    char   pad28[0x38 - 0x28];
    uint32 pad38[(0x4c - 0x38) / 4];
    float  mParam4c;                      // +0x04c
    float  mParam50;                      // +0x050
    float  mParam54;                      // +0x054
    float  mParam58;                      // +0x058
    float  mParam5c;                      // +0x05c
    float  mParam60;                      // +0x060
    float  mParam64;                      // +0x064
    float  mParam68;                      // +0x068
    float  mParam6c;                      // +0x06c
    float  mParam70;                      // +0x070
    float  mParam74;                      // +0x074
    float  mParam78;                      // +0x078
    uint8  mParam7c;                      // +0x07c
    char   pad7d[0x84 - 0x7d];
    float  mParam84;                      // +0x084
    cIRefObj* mpRef88;                    // +0x088
    cIRefObj* mpRef8c;                    // +0x08c
    void*  mHandle90;                     // +0x090
    char   pad94[0x98 - 0x94];
    long long mValueL;                    // +0x098 (int pair: lo = mParam98, hi = mParam9c)
    char   padA0[0xb0 - 0xa0];
    uint32 mHandleB0;                     // +0x0b0
    uint32 mHandleB4;                     // +0x0b4

    cDistributeSimulator(uint32 desc);                    // 0x00a86120
    void* Destroy(uint32 flags);                          // 0x00a86210
    void Initialize(int a, cSimulatorWorld* world, int c); // 0x00a86270
    void Update(float dt);                                // 0x00a86590

    bool OnMessage(int msg, int* pValue, int a3);         // 0x00a85ed0
    bool SetParams(int msg, float* p, int a3);            // 0x00a86050
    void SetEmitterFlags(bool on);                        // 0x00a860e0
    void Deactivate(int unused);                          // 0x00a86010
    void ReleaseEmitter();                                // 0x00a85fb0
};

// Interface used by the Initialize method through its second argument.
struct cSimulatorWorld {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual cIRefObj* GetObjByIdx(uint8 idx);             // +0x24
    virtual void SlotA();
    virtual void SlotB();
    virtual void SlotC();
    virtual void SlotD();
    virtual void SlotE();
    virtual void SlotF();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot1a();
    virtual void Slot1b();
    virtual void Slot1c();
    virtual void Slot1d();
    virtual void Slot1e();
    virtual void Slot1f();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual cIRefObj* GetObjById(uint32 idLo, uint32 idHi); // +0x8c
};

// ===========================================================================
// externals
// ===========================================================================
extern const float DAT_01485720;          // 1.0f
extern const float DAT_01471064;          // 0.5f
extern const float DAT_01485378;          // 0.0f
extern const float DAT_013ebca0;          // 0.0001f
extern const float DAT_01564f38;
extern const float DAT_01677fbc;
extern const float DAT_01677fc0;
extern const float DAT_01677fc4;
extern const float DAT_01678068[];        // 3x3 identity
extern const float DAT_013eb8b0[];        // {-0.0f x4}

// allocator (EAAllocate(size, tag, align, flags, ?, file, line))
void* EAAllocate(uint32 size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
void  operator_delete__(void* p);         // 0x00f47380

struct RandomLCG { double RandomDoubleUniform(); };
extern RandomLCG sRandom_Swarm;           // 0x016778dc

// IO helpers (cdecl): read/write little-endian scalars.
extern "C" void FUN_0093a780(void* s, void* dst, int count, int endian);   // int32 reader
extern "C" void FUN_0093a800(void* s, void* dst, int count, int endian);   // int32 writer
extern "C" void FUN_0093a6c0(void* s, void* dst, int count);               // uint16 reader
extern "C" void FUN_0093a700(void* s, void* dst, int count, int endian);   // uint16 writer
extern "C" void FUN_007d27d0(void* s, void* dst);                          // float-curve reader
extern "C" void FUN_007ed920(void* s, void* dst);                          // embed-reader
extern "C" void FUN_00a85b00(void* s, void* dst);                          // float-curve reader 2
extern "C" void FUN_00a6c7a0(int owner, int index, int* outCount, uint32** outPtr, int** outCount2);
extern "C" float FUN_00a78f80(float x);                                    // exp/curve helper
extern "C" void FUN_00a85ed0(void);
extern "C" void FUN_00a86010(void);

// ===========================================================================
// 0x00a85c00 -- constructor-initializer of the description side objects.  Fills a
// 0xb8-byte block with the default description values and allocates the curve blocks.
// It is *not* the simulator ctor; it takes an explicit destination only through ecx.
// ===========================================================================
struct cDistributeDescInit {
    volatile uint32 mVtbl00;              // +0x000
    volatile uint32 mVtbl04;              // +0x004
    uint32 mMask;                         // +0x008 (bitset; bit0 mode, bit1 map)
    uint8  mParam0c;                      // +0x00c
    uint8  mParam0d;                      // +0x00d
    uint16 mParam0e;                      // +0x00e
    uint32 mParam10;                      // +0x010
    uint32 mParam14;                      // +0x014
    uint8  mParam18;                      // +0x018
    uint8  mParam19;                      // +0x019
    uint8  mParam1a;                      // +0x01a
    uint8  mParam1b;                      // +0x01b
    uint16 mParam1c;                      // +0x01c
    uint16 pad1e;                         // +0x01e
    float  mParam20;                      // +0x020
    uint32 pad24[(0x28 - 0x24) / 4];
    uint32 mParam28;                      // +0x028
    uint32 mParam2c;                      // +0x02c
    float  mParam30;                      // +0x030
    FloatCurve mCurve34;                  // +0x034
    FloatCurve mCurve48;                  // +0x048
    FloatCurve mCurve5c;                  // +0x05c
    FloatCurve mCurve70;                  // +0x070
    FloatCurve mCurve84;                  // +0x084
    float  mParam98;                      // +0x098
    float  mParam9c;                      // +0x09c
    float  mParamA0;                      // +0x0a0
    float  mParamA4;                      // +0x0a4
    float  mParamA8;                      // +0x0a8
    float  mParamAC;                      // +0x0ac
    uint32 mParamB0;                      // +0x0b0
    uint32 mParamB4;                      // +0x0b4

    cDistributeDescInit();
};

static inline float* AllocFloats(int count) {
    float* p = (float*)EAAllocate(count * 4, "EASTL", 0, 0, "EASTL/allocator.h", 0xd1);
    return p;
}

extern const float DAT_01486110;

// @ 0x00a85c00
cDistributeDescInit::cDistributeDescInit()
{
    mVtbl04 = 0;
    mVtbl00 = 0x014580ec;
    mMask = 0;
    mParam0c = 0;
    mParam0d = 0;
    mParam0e = 0;
    mParam10 = 0xffffffff;
    mParam14 = 0xffffffff;
    mParam18 = 0;
    mParam19 = 0;
    mParam1a = 0;
    mParam1b = 0;
    mParam1c = 0;
    mParam20 = 0.0f;
    mParam28 = 0xffffffff;
    mParam2c = 0xffffffff;
    mParam30 = DAT_01486110;

    mCurve34.mpBegin = AllocFloats(1);
    mCurve34.mpCapacity = mCurve34.mpBegin + 1;
    mCurve34.mpBegin[0] = 0.0f;
    mCurve34.mpEnd = mCurve34.mpBegin + 1;

    mCurve48.mpBegin = AllocFloats(1);
    mCurve48.mpCapacity = mCurve48.mpBegin + 1;
    mCurve48.mpBegin[0] = DAT_01485720;
    mCurve48.mpEnd = mCurve48.mpBegin + 1;

    mCurve5c.mpBegin = AllocFloats(1);
    mCurve5c.mpCapacity = mCurve5c.mpBegin + 1;
    mCurve5c.mpBegin[0] = DAT_01485720;
    mCurve5c.mpEnd = mCurve5c.mpBegin + 1;

    mCurve70.mpBegin = AllocFloats(3);
    mCurve70.mpEnd = mCurve70.mpBegin;
    mCurve70.mpCapacity = mCurve70.mpBegin + 3;
    if (mCurve70.mpBegin != 0) {
        mCurve70.mpBegin[0] = DAT_01485720;
        mCurve70.mpBegin[1] = DAT_01485720;
        mCurve70.mpBegin[2] = DAT_01485720;
    }
    mCurve70.mpEnd = mCurve70.mpBegin + 3;

    mCurve84.mpBegin = AllocFloats(1);
    mCurve84.mpCapacity = mCurve84.mpBegin + 1;
    mCurve84.mpBegin[0] = DAT_01485720;
    mCurve84.mpEnd = mCurve84.mpBegin + 1;

    mParam98 = 0;
    mParam9c = 0;
    mParamA0 = 0;
    mParamA4 = 0x3f800000;
    mParamA8 = 0;
    mParamAC = 0;
    mParamB0 = 0xffffffff;
    mParamB4 = 0xffffffff;
}

// ===========================================================================
// 0x00a85dd0 -- description IO reader.  cdecl(stream, void* dst); the second
// argument is the destination block (reached as this-8 by its caller).
// ===========================================================================
struct cDescIO {
    uint32 pad00[2];
    uint32 mMask;                         // +0x08 (low 3 bits kept)
    uint8  mParam0c;                      // +0x0c
    uint8  mParam0d;                      // +0x0d
    uint16 pad0e;                         // +0x0e
    FloatCurve mCurve10;                  // +0x10
    uint32 pad24[(0x30 - 0x24) / 4];
    uint32 mParam30;                      // +0x30
    FloatCurve mCurve34;                  // +0x34
    FloatCurve mCurve48;                  // +0x48
    FloatCurve mCurve5c;                  // +0x5c
    FloatCurve mCurve70;                  // +0x70
    FloatCurve mCurve84;                  // +0x84
    uint32 mParam98;                      // +0x98
    uint32 mParam9c;                      // +0x9c
    uint32 mParamA0;                      // +0xa0
    uint32 mParamA4;                      // +0xa4
    uint32 mParamA8;                      // +0xa8
    uint32 mParamAC;                      // +0xac
};

// @ 0x00a85dd0
void ReadDesc(void* stream, void* dst)
{
    cDescIO* d = (cDescIO*)dst;
    uint32 tmp = 0;
    FUN_0093a780(stream, &tmp, 1, 0);
    d->mMask = tmp & 7;
    FUN_0093a6c0(stream, &d->mParam0c, 1);
    FUN_0093a6c0(stream, &d->mParam0d, 1);
    FUN_00a85b00(stream, &d->mCurve10);
    FUN_0093a780(stream, &d->mParam30, 1, 0);
    FUN_007d27d0(stream, &d->mCurve34);
    FUN_007d27d0(stream, &d->mCurve48);
    FUN_007d27d0(stream, &d->mCurve5c);
    FUN_007ed920(stream, &d->mCurve70);
    FUN_007d27d0(stream, &d->mCurve84);
    FUN_0093a780(stream, &d->mParam98, 1, 0);
    FUN_0093a780(stream, &d->mParam9c, 1, 0);
    FUN_0093a780(stream, &d->mParamA0, 1, 0);
    FUN_0093a780(stream, &d->mParamA4, 1, 0);
    // d->mParamA8: 8 raw bytes read through the stream vtable slot +0x30.
    (*(void(__thiscall**)(void*, void*, int))(*(uint32*)stream + 0x30))(stream, (char*)dst + 0xa8, 8);
    FUN_0093a800(stream, (char*)dst + 0xb0, 1, 0);
}

// ===========================================================================
// 0x00a85ed0 -- message handler: on message 1 set the 64-bit param field at +0x98.
// ===========================================================================
// @ 0x00a85ed0
bool cDistributeSimulator::OnMessage(int msg, int* pValue, int a3)
{
    switch (msg) {
    case 1: {
        long long v = *pValue;
        if (mValueL != v) {
            mValueL = v;
            if (mActive) {
                (*(void(__thiscall**)(cDistributeSimulator*, int))(mVtbl00 + 0xc))(this, 1);
                (*(void(__thiscall**)(cDistributeSimulator*, int))(mVtbl00 + 8))(this, 0);
            }
        }
        return true;
    }
    default:
        return false;
    }
}

// ===========================================================================
// 0x00a86050 -- message handler for a few message ids.
// ===========================================================================
// @ 0x00a86050
bool cDistributeSimulator::SetParams(int msg, float* p, int a3)
{
    switch (msg) {
    case 4:
        mParam78 = p[0];
        return true;
    case 0xc: {
        float num = p[4] - p[1];
        float denom = p[3] - p[0];
        mParam74 = num / denom;
        mParam50 = 0.0f;
        if ((mDesc->mMask & 1) != 0)
            mParam70 = denom;
        mParam7c = 1;
        return true;
    }
    case 0x101:
        mParam54 = p[1];
        mParam5c = p[2];
        mParam58 = p[4];
        mParam60 = p[5];
        return true;
    default:
        return false;
    }
}

// ===========================================================================
// 0x00a860e0 -- enable/disable the emitter flags object.
// ===========================================================================
// @ 0x00a860e0
void cDistributeSimulator::SetEmitterFlags(bool on)
{
    void* h = mHandle90;
    if (h == 0)
        return;
    if (on)
        *(uint32*)((char*)h + 0x64) |= 1;
    else
        *(uint32*)((char*)h + 0x64) &= 0xfffffffe;
    mpRef8c->SetHandle((uint32)mHandle90);
}

// ===========================================================================
// 0x00a86010 -- deactivate and release the handle.
// ===========================================================================
// @ 0x00a86010
void cDistributeSimulator::Deactivate(int unused)
{
    if (mActive) {
        mActive = 0;
        if (mHandle90 != 0) {
            (*(void(__thiscall**)(cIRefObj*, void*))(*(uint32*)mpRef8c + 0x18))(mpRef8c, mHandle90);
            mHandle90 = 0;
        }
    }
}

// ===========================================================================
// 0x00a85fb0 -- release the two interface pointers.
// ===========================================================================
// @ 0x00a85fb0
void cDistributeSimulator::ReleaseEmitter()
{
    if (mActive)
        (*(void(__thiscall**)(cDistributeSimulator*, int))(mVtbl00 + 0xc))(this, 1);
    if (mpRef88 != 0) {
        (*(void(__thiscall**)(cIRefObj*))(*(uint32*)mpRef88 + 0xc))(mpRef88);
        cIRefObj* p = mpRef88;
        if (p != 0) {
            mpRef88 = 0;
            (*(void(__thiscall**)(cIRefObj*))(*(uint32*)p + 4))(p);
        }
    }
    cIRefObj* q = mpRef8c;
    if (q != 0) {
        mpRef8c = 0;
        (*(void(__thiscall**)(cIRefObj*))(*(uint32*)q + 0xc))(q);
    }
}

extern "C" void FUN_00a6c7a0(int owner, int index, int* outCount, uint32** outPtr, int** outCount2);

// @ 0x00a85f30
int EnumGroupOverrides(char* obj, uint32* out, int limit)
{
    int count = 0;
    FUN_00a6c7a0((int)(obj + 0x10), 0, &count, (uint32**)&out, (int**)&limit);
    uint32 a = *(uint32*)(obj + 0xb0);
    uint32 b = *(uint32*)(obj + 0xb4);
    if (((b & a) != 0xffffffff) && (++count, limit > 0)) {
        out[0] = a;
        out[1] = b;
        out[2] = 5;
    }
    return count;
}

// ===========================================================================
// 0x00a86120 -- constructor of the distribution simulator.
// ===========================================================================

// @ 0x00a86120
cDistributeSimulator::cDistributeSimulator(uint32 desc)
{
    mVtbl04 = 0x13ef094;
    pad08 = 0;
    mVtbl00 = 0x1458130;
    mVtbl04 = 0x145812c;
    mDesc = (cDistributeDescInit*)desc;
    mActive = 0;
    mFlags14 = 0;
    mModCount16 = 0;
    mCenterX = DAT_01677fbc;
    mCenterY = DAT_01677fc0;
    mCenterZ = DAT_01677fc4;
    mRadius = DAT_01485720;
    *(Matrix3*)((char*)this + 0x28) = *(const Matrix3*)&DAT_01678068;
    float one = DAT_01485720;
    mParam54 = one;
    mParam58 = one;
    mParam5c = one;
    mParam60 = one;
    mParam7c = 0;
    mParam64 = one;
    mParam68 = one;
    mParam6c = one;
    mParam70 = one;
    mParam74 = one;
    mParam78 = one;
    mParam84 = one;
    mpRef88 = 0;
    mpRef8c = 0;
    mValueL = 0xffffffffffffffffLL;
    mHandle90 = 0;
}

// ===========================================================================
// 0x00a86210 -- deleting destructor.
// ===========================================================================
// @ 0x00a86210
void* cDistributeSimulator::Destroy(uint32 flags)
{
    mVtbl00 = 0x1458130;
    mVtbl04 = 0x145812c;
    if (mpRef8c) {
        cIRefObj* r = mpRef8c;
        (*(void(__thiscall**)(cIRefObj*))(*(uint32*)r + 0xc))(r);
    }
    if (mpRef88 != 0)
        (*(void(__thiscall**)(cIRefObj*))(*(uint32*)mpRef88 + 4))(mpRef88);
    mVtbl00 = 0x13f21d4;
    mVtbl04 = 0x13ef094;
    if (flags & 1)
        operator_delete__(this);
    return this;
}

// ===========================================================================
// 0x00a86270 -- initialise the simulator against a world (1 arg used of 3).
// ===========================================================================
// @ 0x00a86270
void cDistributeSimulator::Initialize(int a, cSimulatorWorld* world, int c)
{
    cDistributeDescInit* d = mDesc;
    float minSize = DAT_013ebca0;
    const float* src = &d->mParam30;
    if (!(d->mParam30 > DAT_013ebca0))
        src = &minSize;
    mParam84 = DAT_01485720 / *src;

    // Randomised size-vary around 1.0, clamped to [1-vary, 1+vary].
    {
        double lo = 1.0 - d->mParam98;
        double hi = 1.0 + d->mParam98;
        double r = sRandom_Swarm.RandomDoubleUniform();
        double v = r * (hi - lo) + lo;
        if (v < hi) {
            if (v < lo) v = lo;
        } else {
            v = hi;
        }
        mParam64 = (float)v;
    }
    {
        double lo = 1.0 - d->mParam9c;
        double hi = 1.0 + d->mParam9c;
        double r = sRandom_Swarm.RandomDoubleUniform();
        double v = r * (hi - lo) + lo;
        if (v < hi) {
            if (v < lo) v = lo;
        } else {
            v = hi;
        }
        mParam68 = (float)v;
    }
    if (d->mParamA0 > DAT_01485378)
        mParam6c = FUN_00a78f80(d->mParamA0);
    else
        mParam6c = DAT_01485720;

    mParam4c = mParam68;

    cIRefObj* obj = world->GetObjByIdx(d->mParam0c);
    cIRefObj* old = mpRef8c;
    if (obj != old) {
        if (obj != 0)
            (*(void(__thiscall**)(cIRefObj*))(*(uint32*)obj + 8))(obj);
        mpRef8c = obj;
        if (old != 0)
            (*(void(__thiscall**)(cIRefObj*))(*(uint32*)old + 0xc))(old);
    }

    if ((d->mMask >> 1) & 1) {
        mParam7c = 1;
        cIRefObj* m = world->GetObjById(d->mParamB0, d->mParamB4);
        if (m != 0) {
            float v = DAT_01564f38;
            float pt[6];
            pt[0] = v;
            pt[1] = -v;
            pt[2] = v;
            pt[3] = v;
            pt[4] = -v;
            pt[5] = -v;
            (*(void(__thiscall**)(cIRefObj*, float*))(*(uint32*)m + 0x14))(m, &pt[1]);
            mFlags14 |= 4;
            mModCount16 += 1;
            float cx = (pt[2] + pt[0]) * 0.5f;
            float cy = (pt[3] + pt[1]) * 0.5f;
            float cz = (pt[4] + pt[0]) * 0.5f;
            mCenterX = cx;
            mCenterY = cy;
            mCenterZ = cz;
            float dx = pt[1] - pt[0];
            float dy = pt[3] - pt[1];
            mModCount16 += 1;
            mRadius = (dx <= dy) ? dx : dy;
        }
    }

    uint32 idLo = d->mParamB0;
    uint32 idHi = d->mParamB4;
    if ((idLo & idHi) != 0xffffffff) {
        cIRefObj* r = world->GetObjById(idLo, idHi);
        cIRefObj* old2 = mpRef88;
        if (r != old2) {
            if (r != 0)
                (*(void(__thiscall**)(cIRefObj*))(*(uint32*)r))(r);
            mpRef88 = r;
            if (old2 != 0)
                (*(void(__thiscall**)(cIRefObj*))(*(uint32*)old2 + 4))(old2);
        }
    }
    if (mpRef88 != 0)
        (*(void(__thiscall**)(cIRefObj*))(*(uint32*)mpRef88 + 8))(mpRef88);
}

// ===========================================================================
// 0x00a86590 -- per-frame update: samples the description curves and pushes a
// render transform to the streamer.
// ===========================================================================
struct cSPTransform {
    float f[0x38 / 4];
    cSPTransform(const void* src);            // 0x538000
    void* Assign(const void* src);            // 0x537dc0
};
struct cSPTransformOps { void* Assign(const void* src); };

extern "C" void FUN_00705290(float* out, const float* in);   // Vector3 multiply
extern const float DAT_01471064;   // 0.5f
extern const float DAT_01564f38;
extern const float DAT_013f4fd0;   // 4294967296.0f (unsigned int -> float)
extern const float DAT_013eb8b0[];

// Samples a float curve (lerp) at t in [0,1].
static inline float SampleCurve(const FloatCurve& c, float t)
{
    unsigned n = (unsigned)(c.mpEnd - c.mpBegin) - 1;
    if (n == 0)
        return c.mpBegin[0];
    float f = (float)n;
    unsigned idx = (unsigned)(f * t);
    float frac = f * t - (float)idx;
    if (frac <= DAT_01485378)
        return c.mpBegin[idx];
    return (c.mpBegin[idx + 1] - c.mpBegin[idx]) * frac + c.mpBegin[idx];
}

// Samples a Vector3 curve (lerp) at t in [0,1].
static inline void SampleCurve3(const FloatVec& cv, float t, float* out)
{
    const Vector3* b = (const Vector3*)cv.mpBegin;
    const Vector3* e = (const Vector3*)cv.mpEnd;
    if (b == e) {
        out[0] = 1.0f; out[1] = 1.0f; out[2] = 1.0f;
        return;
    }
    unsigned n = (unsigned)(e - b) - 1;
    if (n == 0) {
        out[0] = b[0].x; out[1] = b[0].y; out[2] = b[0].z;
        return;
    }
    float f = (float)n;
    unsigned idx = (unsigned)(f * t);
    float frac = f * t - (float)idx;
    if (frac <= DAT_01485378) {
        out[0] = b[idx].x; out[1] = b[idx].y; out[2] = b[idx].z;
    } else {
        out[0] = b[idx].x + (b[idx + 1].x - b[idx].x) * frac;
        out[1] = b[idx].y + (b[idx + 1].y - b[idx].y) * frac;
        out[2] = b[idx].z + (b[idx + 1].z - b[idx].z) * frac;
    }
}

// @ 0x00a86590
void cDistributeSimulator::Update(float dt)
{
    if (mpRef8c == 0 || mActive != 0)
        return;

    float t = 0.0f;
    if (dt != 0.0f) {
        uint8 srcType = mDesc->mParam0d;
        if (srcType == 1)
            return;
        if (srcType == 2)
            t = 1.0f;
    }

    uint8 fmt = mDesc->mParam0c;

    cSPTransform xf(&mFlags14);
    float sz = SampleCurve(*(FloatCurve*)((char*)mDesc + 0x48), t);
    xf.f[1] = mParam68 * sz * xf.f[1];
    mFlags14 |= 1;
    mModCount16 += 1;

    float pitch = SampleCurve(*(FloatCurve*)((char*)mDesc + 0x34), t);
    pitch = mParam6c * pitch;

    void* handle = (*(void*(__thiscall**)(cIRefObj*, uint32, void*, cSPTransform*, void*))(*(uint32*)mpRef8c + 0x10))
        (mpRef8c, fmt, (char*)mDesc + 0x10, &xf, this);
    mHandle90 = handle;
    if (handle == 0)
        return;

    ((cSPTransformOps*)handle)->Assign(&xf);
    *(float*)((char*)handle + 0x48) = pitch;

    float roll = SampleCurve(*(FloatCurve*)((char*)mDesc + 0x84), t);
    *(float*)((char*)handle + 0x4c) = mParam74 * roll;

    if ((mDesc->mMask & 1) != 0) {
        *(float*)((char*)handle + 0x50) = mDesc->mParamA4 * mParam70;
        *(float*)((char*)handle + 0x54) = *(float*)((char*)handle + 0x50) * *(float*)((char*)handle + 0x4c);
    } else {
        *(float*)((char*)handle + 0x50) = 1.0f;
        *(float*)((char*)handle + 0x54) = 1.0f;
    }
    *(float*)((char*)handle + 0x58) = mDesc->mParamA8;
    *(float*)((char*)handle + 0x5c) = mDesc->mParamAC;

    float heading = SampleCurve(*(FloatCurve*)((char*)mDesc + 0x5c), t);
    float colorScale = mParam78 * mParam64 * heading;

    float col[3];
    SampleCurve3(*(FloatVec*)((char*)mDesc + 0x70), t, col);

    if (mpRef88 != 0) {
        float pt[3];
        pt[0] = mCenterX; pt[1] = mCenterY; pt[2] = mCenterZ;
        if ((*(bool(__thiscall**)(cIRefObj*, float*))(*(uint32*)mpRef88 + 0x18))(mpRef88, pt)) {
            float out[3];
            (*(void(__thiscall**)(cIRefObj*, float*, float*))(*(uint32*)mpRef88 + 0x2c))(mpRef88, out, pt);
            colorScale = out[2] * colorScale;
            for (int i = 0; i < 3; ++i)
                col[i] = out[i] * col[i];
        }
    }

    *(float*)((char*)handle + 0x44) = colorScale;
    *(float*)((char*)handle + 0x38) = col[0];
    *(float*)((char*)handle + 0x3c) = col[1];
    *(float*)((char*)handle + 0x40) = col[2];

    (*(void(__thiscall**)(cIRefObj*, void*))(*(uint32*)mpRef8c + 0x14))(mpRef8c, handle);
    *(float*)((char*)this + 0x80) = t;

    if (mDesc->mParam0c == 3) {
        mHandle90 = 0;
        mActive = 0;
        return;
    }
    mActive = 1;
}


