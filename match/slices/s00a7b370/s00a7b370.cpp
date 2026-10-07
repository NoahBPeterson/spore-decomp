// s00a7b370: Swarm path builder, small readers, hash-map of ref-counted objects and Halton sequences
// (cl1_new slice 90). Names are Claude-coined from usage.
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>
#include <intrin.h>

void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
void  operator_delete__(void* p);                                                               // 0xf47380
extern const char kEastlAllocFile[];   // ".../EASTL/allocator.h"

// ------------------------------------------------------------------ stream helpers
struct IStream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual int Read(void* dst, uint32_t size);   // +0x30
};
bool ReadInt32(void* s, void* p, unsigned n, int endian);    // 0x93a780
bool ReadBytes(void* s, void* p, unsigned n);                // 0x93a6c0
void* ReadIntVector(void* s, void* vec);                     // 0x7d27d0

// ====================================================================== path builder (0x00a7b370)
struct Vec3 { float x, y, z; };

struct FloatVec {          // eastl::vector<float> (begin, end, capacity)
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    void PushSlow(float* pEnd, const float* v);   // 0x00455660 (thiscall)
    void push_back(const float& v) {
        float* p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p) *p = v;
        } else {
            PushSlow(p, &v);
        }
    }
};
struct Vec3Vec { Vec3* mpBegin; Vec3* mpEnd; Vec3* mpCapacity; };
struct Vertex {            // 0x1c bytes: position, direction, parameter
    Vec3 pos;
    Vec3 dir;
    float param;
};
struct VertexVec {
    Vertex* mpBegin;
    Vertex* mpEnd;
    Vertex* mpCapacity;
    void PushSlow(Vertex* pEnd, const Vertex* v);   // 0x00a7a9d0
    Vertex* erase(Vertex* first, Vertex* last);    // 0x00d73090 (thiscall, ret 8)
};
extern const Vec3 kDefaultDir;                      // 0x016770dc

template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template<class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

struct PathBuilder {
    char       pad00[0x38];
    Vec3Vec    mPoints;       // +0x38
    char       pad44[0x4c - 0x44];
    FloatVec   mWidths;       // +0x4c
    char       pad58[0x60 - 0x58];
    Vec3Vec    mTangents;     // +0x60
    char       pad6c[0x74 - 0x6c];
    FloatVec   mParams;       // +0x74
    char       pad80[0x88 - 0x80];
    bool*      mpDone;        // +0x88
    char       pad8c[0x90 - 0x8c];
    VertexVec* mpOut;         // +0x90
    void Build(bool skip);    // 0x00a7b370
};

static inline float SegLen(const Vec3& a, const Vec3& b)
{
    float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

// @ 0x00a7b370
void PathBuilder::Build(bool skip)
{
    if (skip) return;
    int n = (int)(mPoints.mpEnd - mPoints.mpBegin);
    int nTan = (int)(mTangents.mpEnd - mTangents.mpBegin);
    int nWidth = (int)(mWidths.mpEnd - mWidths.mpBegin);
    int nParam = (int)(mParams.mpEnd - mParams.mpBegin);
    bool normalize = false;

    if (nParam == 0) {
        if (nWidth == 1) {
            float total = 0.0f;
            for (int i = 1; i < n; ++i)
                total += SegLen(mPoints.mpBegin[i], mPoints.mpBegin[i - 1]);
            float v = total / mWidths.mpBegin[0];
            mParams.push_back(v);
            normalize = true;
        } else {
            float zero = 0.0f;
            mParams.push_back(zero);
            float acc = 0.0f;
            for (int i = 1; i < n; ++i) {
                Vec3 d;
                d.x = mPoints.mpBegin[i].x - mPoints.mpBegin[i - 1].x;
                d.y = mPoints.mpBegin[i].y - mPoints.mpBegin[i - 1].y;
                d.z = mPoints.mpBegin[i].z - mPoints.mpBegin[i - 1].z;
                float w = (mWidths.mpBegin[i - 1] + mWidths.mpBegin[i]) * 0.5f;
                if (w > 0.0f)
                    acc = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z) / w + acc;
                mParams.push_back(acc);
            }
        }
    } else if (nParam == 1) {
        normalize = true;
    }

    if (normalize && n > 1) {
        float last = mParams.mpEnd[-1];
        float total = 0.0f;
        for (int i = 1; i < n; ++i)
            total += SegLen(mPoints.mpBegin[i], mPoints.mpBegin[i - 1]);
        mParams.mpBegin[0] = 0.0f;
        float acc = 0.0f;
        float inv = 1.0f / total;
        for (int i = 1; i < n; ++i) {
            acc += SegLen(mPoints.mpBegin[i], mPoints.mpBegin[i - 1]);
            float v = inv * acc * last;
            mParams.push_back(v);
        }
    }

    if (nWidth == 0 && nTan == 0) {
        float last = mParams.mpEnd[-1];
        float total = 0.0f;
        for (int i = 1; i < n; ++i)
            total += SegLen(mPoints.mpBegin[i], mPoints.mpBegin[i - 1]);
        float w;
        if (last > 0.0f) w = total / last;
        else w = 0.0f;
        mWidths.push_back(w);
        nWidth = 1;
    }

    mpOut->erase(mpOut->mpBegin, mpOut->mpEnd);
    for (int i = 0; i < n; ++i) {
        Vertex v;
        v.pos = mPoints.mpBegin[i];
        v.param = mParams.mpBegin[i];
        if (nWidth > 0) {
            float w = (nWidth > 1) ? mWidths.mpBegin[i] : mWidths.mpBegin[0];
            int ia = Max(i - 1, 0);
            int ib = Min(i + 1, n - 1);
            Vec3 d;
            d.x = mPoints.mpBegin[ib].x - mPoints.mpBegin[ia].x;
            d.y = mPoints.mpBegin[ib].y - mPoints.mpBegin[ia].y;
            d.z = mPoints.mpBegin[ib].z - mPoints.mpBegin[ia].z;
            float len = sqrtf(d.z * d.z + d.y * d.y + d.x * d.x);
            if (len > 1e-6f) {
                float s = w / len;
                v.dir.x = d.x * s;
                v.dir.y = d.y * s;
                v.dir.z = d.z * s;
            } else {
                v.dir = kDefaultDir;
            }
        } else if (nTan > 0) {
            const Vec3& t = (nTan > 1) ? mTangents.mpBegin[i] : mTangents.mpBegin[0];
            v.dir = t;
        }
        VertexVec* out = mpOut;
        Vertex* p = out->mpEnd;
        if (p < out->mpCapacity) {
            out->mpEnd = p + 1;
            if (p) *p = v;
        } else {
            out->PushSlow(p, &v);
        }
    }
    *mpDone = true;
}

// ====================================================================== readers
// @ 0x00a7b9a0
void ReadRecordA(IStream* s, uint8_t* o)
{
    s->Read(o, 8);
    s->Read(o + 8, 8);
    ReadInt32(s, o + 0x10, 1, 0);
    ReadInt32(s, o + 0x14, 1, 0);
    ReadInt32(s, o + 0x18, 1, 0);
    ReadIntVector(s, o + 0x1c);
    ReadBytes(s, o + 0x30, 1);
}

// @ 0x00a7ba10
void ReadRecordB(IStream* s, uint8_t* o)
{
    ReadIntVector(s, o);
    ReadInt32(s, o + 0x14, 1, 0);
    ReadInt32(s, o + 0x18, 1, 0);
}

// @ 0x00a7ba60  (query-interface style: stores the type id when asked for a non-null slot)
int __stdcall QueryTypeId(uint32_t* out, unsigned n)
{
    if (out) {
        if (n >= 1) {
            *out = 0xea5118b0;
        } else return 0;
    }
    return 1;
}

// ====================================================================== ref-counted objects
struct RcObj {                   // slot 2 = deleting destructor, counter at +4
    virtual void v0();
    virtual void v1();
    virtual ~RcObj();
    long mRef;
    long Release();              // 0x00a7ba90
};

// @ 0x00a7ba90
long RcObj::Release()
{
    long n = _InterlockedDecrement(&mRef);
    if (n == 0) {
        _InterlockedExchange(&mRef, 1);
        delete this;
    }
    return n;
}

struct IFace12 {                  // interface used by the two thunks below
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11();
    virtual bool Op12(void* x);   // +0x30
    virtual bool Op13(void* x);   // +0x34
};
struct ISource {
    virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3();
    virtual void q4(); virtual void q5();
    virtual void* GetItem();       // +0x18
};
struct Forwarder {
    char pad[0x14];
    IFace12* mpTarget;             // +0x14
};

// @ 0x00a7bac0
bool __stdcall ForwardOp12(ISource* src, Forwarder* fw, int unused, uint32_t tag)
{
    bool r = false;
    void* item = src->GetItem();
    if (tag == 0xea5118b0)
        r = fw->mpTarget->Op12(item);
    return r;
}

// @ 0x00a7bb00
bool __stdcall ForwardOp13(Forwarder* fw, ISource* src, int unused, uint32_t tag)
{
    bool r = false;
    void* item = src->GetItem();
    if (tag == 0xea5118b0)
        r = fw->mpTarget->Op13(item);
    return r;
}

// ---- base with an interlocked counter at +4
struct CountedBase {
    virtual ~CountedBase() {}
    long mRef;
    CountedBase() { _InterlockedExchange(&mRef, 0); }
};
struct CountedBase2 {
    virtual void AddRef();
    virtual void Release();
    virtual ~CountedBase2() {}
    long mRef;
    CountedBase2() { _InterlockedExchange(&mRef, 0); }
};

struct RecordReadObj : CountedBase {         // 0x00a7bb80
    RecordReadObj();
    virtual ~RecordReadObj() {}
};
// @ 0x00a7bb80
RecordReadObj::RecordReadObj() {}

struct IRefA { virtual void AddRef(); virtual void Release(); };   // slot 0 AddRef, 1 Release

struct CollectionBase : CountedBase2 {
    uint32_t mVec[3];                         // +8
    CollectionBase() { mVec[0] = 0; mVec[1] = 0; mVec[2] = 0; }
    virtual void AddRef();
    virtual void Release();
};
struct CollectionResource : CollectionBase {  // 0x18 bytes
    IRefA*   mpRes;                           // +0x14
    CollectionResource() { mpRes = 0; }
    virtual void AddRef();
    virtual void Release();
};

struct IVec3Source { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
                     virtual const uint32_t* GetVec(); };   // +0x10
struct ICreator {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
    virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7();
    virtual void c8();
    virtual bool Create(IVec3Source* a, CollectionResource* r, int arg, uint32_t tag);   // +0x24
};
IRefA* GetDefaultResource();   // 0x00a6b970

struct Loader {
    ICreator* creator() { return (ICreator*)this; }
    bool Load(IVec3Source* a, CollectionResource** out, int arg, uint32_t tag);   // 0x00a7bba0
};

// @ 0x00a7bba0
bool Loader::Load(IVec3Source* a, CollectionResource** out, int arg, uint32_t tag)
{
    if (tag == 0xea5118b0) {
        CollectionResource* obj = new("Swarm/CollectionResource", 0, 0, 0, 0) CollectionResource();
        IRefA* res = GetDefaultResource();
        IRefA* old = obj->mpRes;
        if (res != old) {
            if (res) res->AddRef();
            obj->mpRes = res;
            if (old) old->Release();
        }
        if (obj) {
            obj->AddRef();
            if (creator()->Create(a, obj, arg, 0xea5118b0)) {
                *out = obj;
                obj->AddRef();
                const uint32_t* v = a->GetVec();
                (*out)->mVec[0] = v[0];
                (*out)->mVec[1] = v[1];
                (*out)->mVec[2] = v[2];
                obj->Release();
                return true;
            }
            obj->Release();
        }
    }
    return false;
}

struct IFactory {
    virtual void f0(); virtual void f1(); virtual void f2();
    virtual bool Create(void* q, CollectionResource** out, int a, int b, int c, int d);   // +0xc
};
IFactory* GetFactory();   // 0x008de1a0

struct QueryDesc { int mParam; uint32_t mTagA; uint32_t mTagB; };
struct ResultObj {
    virtual void AddRef();
    virtual void Release();
    char pad[0x14 - 4];
    int mField14;
};

// @ 0x00a7bca0
int GetResourceField(int param)
{
    IFactory* f = GetFactory();
    if (f) {
        QueryDesc q;
        q.mParam = param;
        q.mTagA = 0xea5118b0;
        q.mTagB = 0xea5118b1;
        ResultObj* res = 0;
        if (f->Create(&q, (CollectionResource**)&res, 0, 0, 0, 0)) {
            int r = res->mField14;
            res->Release();
            return r;
        }
        if (res) res->Release();
    }
    return 0;
}

// ====================================================================== hash map of ref-counted objects
struct IRefT1 { virtual void Release(); virtual void AddRef(); };   // slot 0 Release, 1 AddRef
struct IRefT2 { virtual void AddRef(); virtual void Release(); };   // slot 0 AddRef, 1 Release

struct HKey { uint32_t a, b; };

// @ 0x00a7bd20 / 0x00a7be20: node allocation (copy of {key, ref-counted value}); node = 0x18 bytes
template<class T> struct HNode {
    HKey key;          // +0
    T*   value;        // +8
    uint32_t pad0c;
    HNode* next;       // +0x10
    uint32_t pad14;
};

struct HIter {
    void*  node;
    void** bucket;
    HIter() {}
    HIter(const HIter& o) { node = o.node; bucket = o.bucket; }
};

struct HTag {};
struct HInsRes {              // eastl::pair<iterator, bool>
    HIter first;
    bool  second;
    HInsRes() {}
    HInsRes(const HInsRes& o) : first(o.first), second(o.second) {}
};

template<class T> struct HPair {
    HKey key;
    T*   value;
};

// @ 0x00a7bd20
HNode<IRefT1>* __stdcall AllocNode1(const HPair<IRefT1>* src)
{
    HNode<IRefT1>* p = (HNode<IRefT1>*)operator new(0x18, "EASTL", 0, 0, kEastlAllocFile, 0xd1);
    if (p) {
        p->key.a = src->key.a;
        p->key.b = src->key.b;
        p->value = src->value;
        if (p->value) p->value->AddRef();
    }
    p->next = 0;
    return p;
}

// @ 0x00a7be20
HNode<IRefT2>* __stdcall AllocNode2(const HPair<IRefT2>* src)
{
    HNode<IRefT2>* p = (HNode<IRefT2>*)operator new(0x18, "EASTL", 0, 0, kEastlAllocFile, 0xd1);
    if (p) {
        p->key.a = src->key.a;
        p->key.b = src->key.b;
        p->value = src->value;
        if (p->value) p->value->AddRef();
    }
    p->next = 0;
    return p;
}

struct HashMapBase {
    uint32_t pad0;
    HNode<void>** mBuckets;     // +4
    uint32_t      mBucketCount; // +8
    HIter find(const HKey& k);  // 0x00a7bf40
};

// @ 0x00a7bf40
HIter HashMapBase::find(const HKey& k)
{
    uint32_t idx = k.a % mBucketCount;
    HNode<void>** pBucket = mBuckets + idx;
    HIter it;
    it.node = *pBucket;
    it.bucket = (void**)pBucket;
    HNode<void>* n = (HNode<void>*)it.node;
    if (n) {
        do {
            if (k.a == n->key.a && k.b == n->key.b)
                return HIter(it);
            n = n->next;
            it.node = n;
        } while (n);
    }
    it.bucket = (void**)(mBuckets + mBucketCount);
    it.node = *it.bucket;
    return HIter(it);
}

struct HashMap1 : HashMapBase {
    HInsRes insert(const HPair<IRefT1>& v, HTag t);   // 0x00a7be70
    IRefT1** operator[](const HKey& k);             // 0x00a7c100
};
struct HashMap2 : HashMapBase {
    HInsRes insert(const HPair<IRefT2>& v, HTag t);   // 0x00a7bfb0
    IRefT2** operator[](const HKey& k);             // 0x00a7c180
};

// @ 0x00a7c100
IRefT1** HashMap1::operator[](const HKey& k)
{
    {
        HIter it = find(k);
        if (it.node != mBuckets[mBucketCount])
            return &((HNode<IRefT1>*)it.node)->value;
    }
    HPair<IRefT1> p;
    p.key = k;
    p.value = 0;
    HInsRes ins = insert(p, HTag());
    IRefT1** r = &((HNode<IRefT1>*)ins.first.node)->value;
    if (p.value) p.value->Release();
    return r;
}

// @ 0x00a7c180
IRefT2** HashMap2::operator[](const HKey& k)
{
    {
        HIter it = find(k);
        if (it.node != mBuckets[mBucketCount])
            return &((HNode<IRefT2>*)it.node)->value;
    }
    HPair<IRefT2> p;
    p.key = k;
    p.value = 0;
    HInsRes ins = insert(p, HTag());
    IRefT2** r = &((HNode<IRefT2>*)ins.first.node)->value;
    if (p.value) p.value->Release();
    return r;
}

struct Registry {
    char pad[4];
    HashMap1 mMap1;      // +4
    char pad2[0x24 - 0x4 - sizeof(HashMap1)];
    HashMap2 mMap2;      // +0x24
    void Set1(HKey key, IRefT1* val);   // 0x00a7c200
    void Set2(HKey key, IRefT2* val);   // 0x00a7c240
};

// @ 0x00a7c200
void Registry::Set1(HKey key, IRefT1* val)
{
    IRefT1** slot = mMap1[key];
    IRefT1* old = *slot;
    if (val != old) {
        if (val) val->AddRef();
        *slot = val;
        if (old) old->Release();
    }
}

// @ 0x00a7c240
void Registry::Set2(HKey key, IRefT2* val)
{
    IRefT2** slot = mMap2[key];
    IRefT2* old = *slot;
    if (val != old) {
        if (val) val->AddRef();
        *slot = val;
        if (old) old->Release();
    }
}

// ====================================================================== Halton sequences
// @ 0x00a7c280  (bit-reversal van der Corput value in [0,1))
__declspec(noinline) float VanDerCorput(uint32_t v)
{
    uint32_t a = (((v >> 1) ^ (v + v)) & 0x55555555) ^ (v << 1);
    uint32_t b = (((a >> 2) ^ (a * 4)) & 0x33333333) ^ (a << 2);
    v = (((b >> 4) ^ (b << 4)) & 0x0f0f0f0f) ^ (b * 16);
    union { uint32_t u; float f; } r;
    r.u = (((v >> 16) & 0xfe) | (v & 0xff00)) >> 1 | ((v & 0xff) | 0x7f00) << 15;
    return r.f - 1.0f;
}

// @ 0x00a7c300  (radical inverse, base 2)
__declspec(noinline) float RadicalInverse2(int n)
{
    float r = 0.0f;
    float result = 0.0f;
    float f = 0.5f;
    for (; n > 0; n >>= 1) {
        if (n & 1) {
            r = f + r;
            result = r;
        }
        f = f * 0.5f;
    }
    return result;
}

struct Halton2 {
    float mX;       // +0  base 2
    float mY;       // +4  base 3
    int   mIndex;   // +8
    int   mDigits3; // +0xc
    int   Next();            // 0x00a7c350
    Halton2(int index);      // 0x00a7c3d0
};

// @ 0x00a7c350
int Halton2::Next()
{
    mIndex = mIndex + 1;
    mX = VanDerCorput(mIndex);
    mDigits3 = mDigits3 + 1;
    uint32_t mask = 3;
    int step = 1;
    float f = 1.0f / 3.0f;
    if ((mDigits3 & 3) == 3) {
        do {
            mDigits3 = mDigits3 + step;
            mY = mY - f * 2.0f;
            mask = mask * 4;
            step = step * 4;
            f = f * (1.0f / 3.0f);
        } while (((uint32_t)mDigits3 & mask) == mask);
    }
    mY = mY + f;
    return mIndex;
}

// @ 0x00a7c3d0
Halton2::Halton2(int index)
{
    mX = RadicalInverse2(index);
    mY = 0.0f;
    mIndex = index;
    mDigits3 = 0;
    float f = 1.0f / 3.0f;
    uint8_t shift = 0;
    for (; index != 0; index /= 3) {
        int digit = index % 3;
        mDigits3 |= digit << shift;
        shift += 2;
        mY = (float)digit * f + mY;
        f = f * (1.0f / 3.0f);
    }
}

struct Halton3 {
    float mX;       // +0  base 2
    float mY;       // +4  base 3
    float mZ;       // +8  base 5
    int   mIndex;   // +0xc
    int   mDigits3; // +0x10
    int   mDigits5; // +0x14
    int   Next();            // 0x00a7c450
    Halton3(int index);      // 0x00a7c540
};

// @ 0x00a7c450
int Halton3::Next()
{
    mIndex = mIndex + 1;
    mX = VanDerCorput(mIndex);
    mDigits3 = mDigits3 + 1;
    uint32_t mask = 3;
    int step = 1;
    float f = 1.0f / 3.0f;
    if ((mDigits3 & 3) == 3) {
        do {
            mDigits3 = mDigits3 + step;
            mY = mY - f * 2.0f;
            mask = mask * 4;
            step = step * 4;
            f = f * (1.0f / 3.0f);
        } while (((uint32_t)mDigits3 & mask) == mask);
    }
    mY = mY + f;
    mDigits5 = mDigits5 + 1;
    uint32_t mask5 = 7;
    uint32_t want5 = 5;
    int step5 = 3;
    float f5 = 0.2f;
    if ((mDigits5 & 7) == 5) {
        do {
            mDigits5 = mDigits5 + step5;
            mask5 = mask5 * 8;
            mZ = mZ - f5 * 4.0f;
            want5 = want5 * 8;
            step5 = step5 * 8;
            f5 = f5 * 0.2f;
        } while ((mask5 & (uint32_t)mDigits5) == want5);
    }
    mZ = mZ + f5;
    return mIndex;
}

// @ 0x00a7c540
Halton3::Halton3(int index)
{
    mX = RadicalInverse2(index);
    int n = index;
    mIndex = index;
    mY = 0.0f;
    mDigits3 = 0;
    float f = 1.0f / 3.0f;
    uint8_t shift = 0;
    for (int m = n; m != 0; m /= 3) {
        int digit = m % 3;
        mDigits3 |= digit << shift;
        shift += 2;
        mY = (float)digit * f + mY;
        f = f * (1.0f / 3.0f);
    }
    shift = 0;
    mZ = 0.0f;
    mDigits5 = 0;
    f = 0.2f;
    for (int m = n; m != 0; m /= 5) {
        int digit = m % 5;
        mDigits5 |= digit << shift;
        shift += 3;
        mZ = (float)digit * f + mZ;
        f = f * 0.2f;
    }
}
