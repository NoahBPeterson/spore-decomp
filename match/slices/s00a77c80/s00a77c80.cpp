// s00a77c80: Swarm map-info / material-description helpers (cl1_new slice 89).
// Names are Claude-coined from usage unless marked (PDB/vtable names: Swarm::MapInfo, Swarm::MapDescription).
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>
#include <intrin.h>

void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
void* operator new[](size_t size, const char* pName, int a, int b, const char* file, int line);
void operator_delete__(void* p);   // 0xf47380 (operator delete[]-style, plain cdecl)
extern const char kEastlAllocFile[];  // ".../EASTL/allocator.h"

// ------------------------------------------------------------------ stream helpers (cdecl)
struct IStream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual int Read(void* dst, uint32_t size);   // +0x30
};
bool ReadUInt64(void* s, void* p, unsigned n, int endian);   // 0x93a800
bool ReadUInt16(void* s, void* p, unsigned n, int endian);   // 0x93a700
bool ReadInt32(void* s, void* p, unsigned n, int endian);    // 0x93a780
bool ReadBytes(void* s, void* p, unsigned n);                // 0x93a6c0

// ------------------------------------------------------------------ small float helpers
extern const float kRadScale;   // 0x015549dc

// @ 0x00a77c80
float __stdcall WaveSum(const float* v)
{
    float a = sinf(v[0] * kRadScale);
    float b = sinf(kRadScale * v[1] * 0.5f);
    return (b + 1.0f) * 0.1f + (a + 1.0f) * 0.3f;
}

// @ 0x00a77cc0
void __stdcall InvLengthSqScale(float* out, const float* v)
{
    float s = 1.0f / (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    out[0] = v[0] * s;
    out[1] = v[1] * s;
    out[2] = v[2] * s;
}

// @ 0x00a77d30
void __stdcall WaveVec4(float* out, const float* v)
{
    float a = v[0] * kRadScale;
    float b = kRadScale * v[1] * 0.5f;
    out[2] = 1.0f;
    float x = (sinf(a) + 1.0f) * 0.3f + (sinf(b) + 1.0f) * 0.1f;
    float y = (cosf(b) + 1.0f) * 0.1f + (cosf(a) + 1.0f) * 0.3f;
    out[0] = x;
    out[1] = y;
    out[3] = y * x;
}

// @ 0x00a77da0
void __stdcall WaveNormal(float* out, const float* v)
{
    float x = cosf(v[0] * kRadScale) * kRadScale * -0.3f;
    float y = cosf(kRadScale * v[1] * 0.5f) * kRadScale * -0.05f;
    float inv = 1.0f / sqrtf(x * x + y * y + 1.0f);
    out[0] = x * inv;
    out[1] = y * inv;
    out[2] = inv;
}

// ------------------------------------------------------------------ MapInfo object family
struct IRefObj { virtual void AddRef(); virtual void Release(); };   // slots 0 (AddRef), 1 (Release)

struct B4 {                      // second base at +4: vptr + counter
    virtual ~B4() {}
    int mRef;
    B4() { mRef = 0; }
};

struct MapInfoBase : IRefObj, B4 {   // 0xc bytes (Swarm::MapInfo, 0x00a77e00)
    MapInfoBase();
    virtual void Release();
    virtual ~MapInfoBase() {}
};

struct IItem { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
               virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(uint32_t a); };

struct MapInfoMid : IRefObj, B4 {    // 0x40 bytes
    uint32_t mUnk0c[4];
    bool     mB1c;
    int      mI20, mI24;
    float    mF28, mF2c;
    int      mI30;
    bool     mOwnsItem;
    IItem*   mpItem;
    bool     mB3c;
    MapInfoMid() { mB1c = false; mI20 = 0; mI24 = 0; mF28 = 1.0f; mF2c = 1.0f; mI30 = 0;
                   mOwnsItem = false; mpItem = 0; mB3c = false; }
    virtual void Apply();
    // @ 0x00a77f50  (deleting dtor of MapInfoMid)
    virtual ~MapInfoMid() { if (mpItem && mOwnsItem) mpItem->v7(mI30); }
};

// @ 0x00a77e00
MapInfoBase::MapInfoBase() {}

// Derived map-info objects (each has its own vtable): their constructors only zero the extra fields.
// MapInfoD1 is 0x50 bytes (ctor shape 0x00a77ef0); unused by Add.
struct MapInfoD1 : MapInfoMid {
    uint32_t x[4];
    MapInfoD1();
    void Init76420(void*, int, int, bool, void*, bool);
    virtual void Apply(); };
struct MapInfoD2 : MapInfoMid {  // 0x44 bytes
    uint32_t x[1];
    MapInfoD2();                                         // 0x00a77fa0
    void Init76070(void*, int, int, bool, void*, bool);  // 0x00a76070
    virtual void Apply(); };
struct MapInfoD3 : MapInfoMid {  // 0x48 bytes
    uint32_t x[2];
    MapInfoD3();                                         // 0x00a78000
    void Init76420(void*, int, int, bool, void*, bool);  // 0x00a76420
    virtual void Apply(); };
struct MapInfoD4 : MapInfoMid {  // 0x48 bytes
    uint32_t x[2];
    MapInfoD4();                                         // 0x00a78050
    void Init769b0(void*, int, int, bool, void*);        // 0x00a769b0
    virtual void Apply(); };
struct MapInfoD5 : MapInfoMid {  // 0x50 bytes
    uint32_t x[4];
    MapInfoD5();                                         // 0x00a780a0
    void Init76b80(void*, int, int, bool, void*);        // 0x00a76b80
    virtual void Apply(); };
struct MapInfoMid2 : MapInfoMid { uint32_t x40; MapInfoMid2() { x40 = 0; } };
struct MapInfoD6 : MapInfoMid2 {  // 0x48 bytes
    uint32_t x44;
    MapInfoD6();                                         // 0x00a781a0
    void Init76070(void*, int, int, bool, void*, bool);  // 0x00a76070
    virtual void Apply(); };
struct MapInfoD0 : MapInfoMid {  // 0x50 bytes; used for kinds 2/3
    uint32_t x[4];
    MapInfoD0();                                         // 0x00a77ef0
    void Init75810(void*, int, int, bool, void*, bool);  // 0x00a75810
    void Init758b0(void*, int, int, bool, void*, int, bool);   // 0x00a758b0
    virtual void Apply(); };
struct MapInfoD7 : MapInfoMid {  // 0x80 bytes
    uint32_t x[0x10];
    MapInfoD7();                                         // 0x00a76cf0 (other slice)
    void Init77b70(int, void*, void*);                   // 0x00a77b70
    void Init75340(int, uint32_t, uint32_t);             // 0x00a75340
    void Init752d0(int, void*);                          // 0x00a752d0
    virtual void Apply(); };

// @ 0x00a77ef0
MapInfoD0::MapInfoD0() { x[0] = 0; x[1] = 0; x[2] = 0; x[3] = 0; }
// @ 0x00a77fa0
MapInfoD2::MapInfoD2() { x[0] = 0; }
// @ 0x00a78000
MapInfoD3::MapInfoD3() { x[0] = 0; x[1] = 0; }
// @ 0x00a78050
MapInfoD4::MapInfoD4() { x[0] = 0; x[1] = 0; }
// @ 0x00a780a0
MapInfoD5::MapInfoD5() { x[0] = 0; x[1] = 0; x[2] = 0; x[3] = 0; }
// @ 0x00a781a0
MapInfoD6::MapInfoD6() { x44 = 0; }

// @ 0x00a780f0  (deleting dtor of an object holding four ref-counted pointers at +0x70..+0x7c)
struct AutoRef {
    IRefObj* p;
    __forceinline ~AutoRef() { if (p) p->Release(); }
};
struct MapInfoHolder : IRefObj, B4 {
    uint32_t pad[0x19];
    AutoRef mRef70, mRef74, mRef78, mRef7c;
    MapInfoHolder();
};
MapInfoHolder::MapInfoHolder() {}

// ------------------------------------------------------------------ Swarm::MapDescription
struct MapDescription {
    virtual void d0();
    uint32_t mField4;          // +4
    uint32_t mA8, mAC;         // +8, +0xc  (read as one 64-bit id)
    uint32_t mFlags;           // +0x10
    uint32_t mKind;            // +0x14
    int      mI18, mI1c;       // +0x18, +0x1c
    float    mV20[4];          // +0x20 (16 bytes read raw)
    int8_t   mType30;          // +0x30
    int8_t   mFlag31;          // +0x31
    uint32_t mPad32;
    uint32_t mPairs[8];        // +0x38: 4 x 64-bit
    float    mVecs[16];        // +0x58: 4 x 16 bytes
    MapDescription();
};

// @ 0x00a78590
MapDescription::MapDescription()
{
    mField4 = 0;
    mFlags = 0; mKind = 0;
    mI18 = -1; mI1c = -1;
    mV20[0] = -1.0f; mV20[1] = -1.0f; mV20[2] = 1.0f; mV20[3] = 1.0f;
    mType30 = 4;
    mFlag31 = 0;
}

// @ 0x00a77e20  (read a MapDescription from a stream)
void ReadMapDescription(IStream* s, int unused, MapDescription* d)
{
    ReadUInt64(s, &d->mA8, 1, 0);
    int32_t v;
    ReadInt32(s, &v, 1, 0);
    d->mFlags = v & 0x3ff;
    uint8_t b;
    ReadBytes(s, &b, 1);
    d->mKind = b;
    ReadUInt64(s, &d->mI18, 1, 0);
    s->Read(d->mV20, 0x10);
    ReadBytes(s, &d->mType30, 1);
    ReadBytes(s, &d->mFlag31, 1);
    for (int i = 0; i < 4; ++i) ReadUInt64(s, &d->mPairs[i * 2], 1, 0);
    for (int i = 0; i < 4; ++i) s->Read(&d->mVecs[i * 4], 0x10);
}

// ------------------------------------------------------------------ Add (anonymous namespace)
struct IContext {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void* GetSink();                                   // +0x14
    virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10();
    virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
    virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19(); virtual void c20();
    virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24(); virtual void c25();
    virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29(); virtual void c30();
    virtual void c31(); virtual void c32(); virtual void c33();
    virtual void AddEntry(uint32_t a, uint32_t b, IRefObj* o);  // +0x88
};

struct RefHolder {
    IRefObj* p;
    RefHolder& operator=(IRefObj* o);   // 0x00b5f950 (out of line)
    ~RefHolder() { if (p) p->Release(); }
};

static inline bool BitAt(uint32_t v, int n) { return ((v >> n) & 1) != 0; }

// @ 0x00a781f0
void Add(MapDescription* d, IContext* ctx)
{
    void* sink = ctx->GetSink();
    RefHolder result;
    result.p = 0;
    switch (d->mKind) {
    case 3:
        if (d->mType30 != 4) {
            MapInfoD0* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD0();
            uint32_t f = d->mFlags;
            o->Init758b0(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, d->mType30, BitAt(f, 1));
            result = o;
        } else {
            MapInfoD2* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD2();
            uint32_t f = d->mFlags;
            o->Init76070(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, BitAt(f, 1));
            result = o;
        }
        break;
    case 4:
    case 5: {
        MapInfoD6* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD6();
        uint32_t f = d->mFlags;
        o->Init76070(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, BitAt(f, 1));
        result = o;
        break; }
    case 2: {
        MapInfoD0* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD0();
        uint32_t f = d->mFlags;
        o->Init75810(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, BitAt(f, 1));
        result = o;
        break; }
    case 1: {
        MapInfoD3* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD3();
        uint32_t f = d->mFlags;
        o->Init76420(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, BitAt(f, 1));
        result = o;
        break; }
    case 6: {
        MapInfoD7* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD7();
        o->Init77b70(d->mFlag31, d->mV20, sink);
        for (int i = 0; i < 4; ++i) {
            uint32_t m = 1u << i;
            if ((unsigned)(i + 2) < 10 && (d->mFlags & _rotl(m, 2)) != 0)
                o->Init75340(i, d->mPairs[i * 2], d->mPairs[i * 2 + 1]);
            else if ((unsigned)(i + 6) < 10 && (d->mFlags & _rotl(m, 6)) != 0)
                o->Init752d0(i, &d->mVecs[i * 4]);
        }
        if (!o) return;
        o->AddRef();
        result.p = o;
        break; }
    case 7: {
        MapInfoD4* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD4();
        o->Init769b0(d->mV20, d->mI18, d->mI1c, BitAt(d->mFlags, 0), sink);
        result = o;
        break; }
    case 8: {
        MapInfoD5* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD5();
        o->Init76b80(d->mV20, d->mI18, d->mI1c, BitAt(d->mFlags, 0), sink);
        result = o;
        break; }

    case 0:
        result = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoBase();
        break;
    default:
        return;
    }
    if (result.p) ctx->AddEntry(d->mA8, d->mAC, result.p);
}

// @ 0x00a78560  (registers Add/Read callbacks in a dispatch table)
extern void* g_MapInfoFns[8];   // 0x01675a00
void AddFunc();                  // 0x00a75390
void ReadFunc();                 // 0x00a78150
void InitMapInfoTable()
{
    g_MapInfoFns[0] = (void*)&Add;
    g_MapInfoFns[1] = (void*)&AddFunc;
    g_MapInfoFns[2] = (void*)&ReadFunc;
    g_MapInfoFns[5] = 0;
    g_MapInfoFns[6] = 0;
}

// @ 0x00a785e0
struct IEntries { virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
                  virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
                  virtual void Add(uint32_t a, uint32_t b, void* d); };
void AddMapDescription(MapDescription* d, IContext* ctx)
{
    IEntries* e = (IEntries*)ctx->GetSink();
    e->Add(d->mA8, d->mAC, d);
}

// ------------------------------------------------------------------ material parameters
struct MaterialParam {          // 0x18 bytes
    uint32_t mIdLo, mIdHi;      // +0
    union { int32_t i; float f; void* p; uint8_t b; uint32_t u32[2]; } mValue;   // +8
    int16_t  mCount;            // +0x10
    int8_t   mType;             // +0x12
    uint8_t  mPad13;
    uint32_t mPad14;
};

// @ 0x00a78610  (read one MaterialParam)
void ReadMaterialParam(IStream* s, MaterialParam* o)
{
    ReadUInt64(s, o, 1, 0);
    ReadBytes(s, &o->mType, 1);
    switch (o->mType) {
    case 0:
    case 1:
        ReadInt32(s, &o->mValue.i, 1, 0);
        return;
    case 2:
        ReadBytes(s, &o->mValue.b, 1);
        return;
    case 3: {
        int16_t n;
        ReadUInt16(s, &n, 1, 0);
        o->mCount = n;
        o->mValue.p = new("Swarm/MaterialParams", 0, 0, 0, 0) int32_t[n];
        for (int i = 0; i < n; ++i)
            ReadInt32(s, (int32_t*)o->mValue.p + i, 1, 0);
        return; }
    case 4: {
        int16_t n;
        ReadUInt16(s, &n, 1, 0);
        o->mCount = n;
        o->mValue.p = new("Swarm/MaterialParams", 0, 0, 0, 0) int32_t[n];
        for (int i = 0; i < n; ++i)
            ReadInt32(s, (int32_t*)o->mValue.p + i, 1, 0);
        return; }
    case 5: {
        int16_t n;
        ReadUInt16(s, &n, 1, 0);
        o->mCount = n;
        o->mValue.p = new("Swarm/MaterialParams", 0, 0, 0, 0) char[n];
        for (int i = 0; i < n; ++i)
            ReadBytes(s, (char*)o->mValue.p + i, 1);
        return; }
    case 6:
        ReadUInt64(s, &o->mValue, 1, 0);
        return;
    }
}

// ---- eastl::vector<MaterialParam> (EASTL 0xd1 allocator line), helpers resolved to the shared lib copies
struct DefaultCopyTag {};
struct GenIter { MaterialParam* p; };
MaterialParam* UninitCopy(MaterialParam* first, MaterialParam* last, MaterialParam* dest);      // 0x00720200
GenIter*       UninitCopyGen(GenIter* out, MaterialParam* first, MaterialParam* last, MaterialParam* dest); // 0x00720d70
MaterialParam* CopyBackward(MaterialParam* first, MaterialParam* last, MaterialParam* destEnd); // 0x00cc8b50
void           FillRange(MaterialParam* first, MaterialParam* last, const MaterialParam* v);    // 0x007144b0
void           UninitFillN(MaterialParam* dest, uint32_t n, const MaterialParam* v);            // 0x00714910
void           UninitFillN(MaterialParam* dest, uint32_t n, const MaterialParam* v, DefaultCopyTag t);
MaterialParam* CopyPtr(MaterialParam* first, MaterialParam* last, MaterialParam* dest);         // 0x00720250

struct ParamVec {
    MaterialParam* mpBegin;
    MaterialParam* mpEnd;
    MaterialParam* mpCapacity;
    __forceinline ~ParamVec() { if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin); }
    void erase(MaterialParam* first, MaterialParam* last) {
        MaterialParam* dst = first;
        for (MaterialParam* src = last; src != mpEnd; ++src, ++dst) *dst = *src;
        mpEnd -= (last - first);
    }
    void insert(MaterialParam* position, uint32_t n, const MaterialParam& value);   // 0x00a787f0
    void resize(uint32_t n);                                                       // 0x00a789e0
};

// @ 0x00a787f0
void ParamVec::insert(MaterialParam* position, uint32_t n, const MaterialParam& value)
{
    if (n > (uint32_t)(mpCapacity - mpEnd)) {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        uint32_t nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
        uint32_t nNewSize = nPrevSize + n;
        if (nGrowSize > nNewSize) nNewSize = nGrowSize;
        MaterialParam* pNewData = 0;
        if (nNewSize)
            pNewData = (MaterialParam*)operator new(nNewSize * sizeof(MaterialParam), "EASTL", 0, 0, kEastlAllocFile, 0xd1);
        MaterialParam* pNewEnd = UninitCopy(mpBegin, position, pNewData);
        UninitFillN(pNewEnd, n, &value, DefaultCopyTag());
        pNewEnd = UninitCopy(position, mpEnd, pNewEnd + n);
        if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    } else if (n != 0) {
        const MaterialParam temp = value;
        MaterialParam* const pOldEnd = mpEnd;
        const uint32_t nExtra = (uint32_t)(pOldEnd - position);
        if (n < nExtra) {
            GenIter tmp;
            UninitCopyGen(&tmp, pOldEnd - n, pOldEnd, pOldEnd);
            mpEnd += n;
            CopyBackward(position, pOldEnd - n, pOldEnd);
            FillRange(position, position + n, &temp);
        } else {
            UninitFillN(pOldEnd, n - nExtra, &temp);
            mpEnd += n - nExtra;
            GenIter tmp;
            UninitCopyGen(&tmp, position, pOldEnd, mpEnd);
            mpEnd += nExtra;
            FillRange(position, pOldEnd, &temp);
        }
    }
}

// @ 0x00a789e0
void ParamVec::resize(uint32_t n)
{
    MaterialParam* pEnd = mpEnd;
    uint32_t size = (uint32_t)(pEnd - mpBegin);
    if (n > size) {
        MaterialParam v;
        v.mIdLo = 0xffffffff; v.mIdHi = 0xffffffff;
        v.mCount = 0; v.mType = 7; v.mPad13 = 0;
        insert(pEnd, n - size, v);
    } else {
        MaterialParam* newEnd = mpBegin + n;
        CopyPtr(pEnd, pEnd, newEnd);
        mpEnd -= (pEnd - newEnd);
    }
}

// ------------------------------------------------------------------ MaterialDescription
struct MaterialDescription : B4 {
    virtual ~MaterialDescription();
    uint32_t mIdA[2];          // +8
    uint32_t mIdB[2];          // +0x10
    ParamVec mParams;          // +0x18
    uint32_t mPad24[3];
    MaterialDescription() {
        mIdA[0] = 0xffffffff; mIdA[1] = 0xffffffff; mIdB[0] = 0xffffffff; mIdB[1] = 0xffffffff;
        mParams.mpBegin = 0; mParams.mpEnd = 0; mParams.mpCapacity = 0;
    }
    void Clear();              // 0x00a78a80
};

// @ 0x00a78a80
void MaterialDescription::Clear()
{
    int count = (int)(mParams.mpEnd - mParams.mpBegin);
    for (int i = 0; i < count; ++i) {
        MaterialParam* p = mParams.mpBegin + i;
        if (p->mCount != 0) operator_delete__(p->mValue.p);
    }
    mIdB[0] = 0xffffffff; mIdB[1] = 0xffffffff;
    mParams.erase(mParams.mpBegin, mParams.mpEnd);
}

// @ 0x00a78b30 is in another slice
void ReadParams(IStream* s, ParamVec* v);

// @ 0x00a78b90
MaterialDescription* ReadMaterialDescription(IStream* s)
{
    MaterialDescription* d = new("Swarm/MaterialDescription", 0, 0, 0, 0) MaterialDescription();
    ReadUInt64(s, &d->mIdA, 1, 0);
    ReadUInt64(s, &d->mIdB, 1, 0);
    ReadParams(s, &d->mParams);
    return d;
}

// @ 0x00a78c10
extern void* g_MaterialFns[8];   // 0x01675a24
void SetSerializer();            // 0x00c2e4e0
void InitMaterialTable()
{
    g_MaterialFns[0] = (void*)&AddMapDescription;
    g_MaterialFns[1] = (void*)&SetSerializer;
    g_MaterialFns[2] = (void*)&ReadMaterialDescription;
    g_MaterialFns[5] = 0;
    g_MaterialFns[6] = 0;
}

// @ 0x00a78c40  (deleting dtor)
MaterialDescription::~MaterialDescription()
{
    Clear();
}

// @ 0x00a78c80  (table-driven sine approximation)
extern const float kSineScale;       // 0x016770d8
extern const float kSineStep;        // 0x01677160
extern const float kSineTable[];     // 0x01677840
float FastSine(float x)
{
    float t = kSineScale * x + 12582912.0f;
    uint32_t bits = *(uint32_t*)&t;
    uint32_t idx = (bits & 0xf) * 2;
    int k = (int)(bits - 0x4b400000);
    float r = x - (float)k * kSineStep;
    float a = kSineTable[idx], b = kSineTable[idx + 1];
    return a + (b - a * r * 0.5f) * r;
}
