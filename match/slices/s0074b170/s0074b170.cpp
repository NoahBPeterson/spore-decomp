// Slice s0074b170: cModelWorld load-queue / draw-list helpers (~0x0074b170-0x0074c020).
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar float moves, EH prologs present).
#include "../../include/types.h"
#include <new>
#include <math.h>

struct IPropList;
static inline void** VT(void* p) { return *(void***)p; }

extern "C" void __cdecl eastl_dealloc(void*);
extern "C" void* __cdecl eastl_alloc(uint32_t size, const char* name, int a, int b, const char* file, int line);

// ---------------------------------------------------------------------------
// @ 0x0074B310  vector<T>::DoInsertValue (element size 0x1c, EH)
// ---------------------------------------------------------------------------
struct T1c {
    uint32_t b[7];                 // 0x1c bytes
    T1c(const T1c&);
};
extern "C" void __cdecl FUN_00747980(const T1c* v);   // grow path

struct Vec1c {
    char pad[0x18];
    T1c* end;      // +0x18
    char pad2[4];
    T1c* cap;      // +0x20
    void DoInsert(const T1c* v);
};

void Vec1c::DoInsert(const T1c* val)
{
    T1c* e = end;
    if ((char*)e + 0x1c == (char*)cap) {
        FUN_00747980(val);
    } else {
        end = (T1c*)((char*)e + 0x1c);
        if (e)
            new (e) T1c(*val);
    }
}

// ---------------------------------------------------------------------------
// @ 0x0074B490  heap-swap loop (element 8 bytes, float key at +4)
// ---------------------------------------------------------------------------
extern "C" void __cdecl FUN_00748010(void*, void*, void*);
extern "C" void __cdecl FUN_00748060(void*, void*, void*);
extern "C" void __cdecl FUN_00745e00(void*, int, int, int, uint32_t, uint32_t, void*);

void heap_loop_b490(void* a, void* b, void* c, void* d)
{
    FUN_00748010(a, b, d);
    char* p = (char*)b;
    while (p < (char*)c) {
        float key = *(float*)(p + 4);
        if (key > *(float*)((char*)a + 4)) {
            uint32_t k = *(uint32_t*)(p + 4);
            uint32_t o = *(uint32_t*)p;
            uint32_t k0 = *(uint32_t*)a;
            uint32_t k1 = *(uint32_t*)((char*)a + 4);
            *(uint32_t*)p = k0;
            *(uint32_t*)(p + 4) = k1;
            FUN_00745e00(a, 0, (int)((char*)b - (char*)a) >> 3, 0, o, k, d);
        }
        p += 8;
    }
    FUN_00748060(a, b, d);
}

// ---------------------------------------------------------------------------
// @ 0x0074B510  heap-swap loop (comparator reversed)
// ---------------------------------------------------------------------------
extern "C" void __cdecl FUN_007480c0(void*, void*, void*);
extern "C" void __cdecl FUN_00748110(void*, void*, void*);
extern "C" void __cdecl FUN_00745e80(void*, int, int, int, uint32_t, uint32_t, void*);

void heap_loop_b510(void* a, void* b, void* c, void* d)
{
    FUN_007480c0(a, b, d);
    char* p = (char*)b;
    while (p < (char*)c) {
        if (*(float*)((char*)a + 4) > *(float*)(p + 4)) {
            uint32_t k = *(uint32_t*)(p + 4);
            uint32_t o = *(uint32_t*)p;
            uint32_t k0 = *(uint32_t*)a;
            uint32_t k1 = *(uint32_t*)((char*)a + 4);
            *(uint32_t*)p = k0;
            *(uint32_t*)(p + 4) = k1;
            FUN_00745e80(a, 0, (int)((char*)b - (char*)a) >> 3, 0, o, k, d);
        }
        p += 8;
    }
    FUN_00748110(a, b, d);
}

// ---------------------------------------------------------------------------
// @ 0x0074B690  SP::cModelWorld::SetInWorld
// ---------------------------------------------------------------------------
struct ListNode { ListNode* prev; ListNode* next; char pad[4]; uint32_t flags; };

namespace SP {
class cModelWorld { public:
    char pad0[0x1c];
    char mWorldType;       // +0x1c
    char pad1[0x1a0 - 0x1d];
    ListNode  mListA;      // +0x19c anchor area
    char pad2[4];
    ListNode  mListB;      // +0x1a4 anchor area
    void AddAttachments(ListNode* n);
    void ShutdownModel(ListNode* n);
    void SetInWorld(ListNode* n, bool b);
    void UpdateFromPropList(IPropList* pl, void* mdl, uint32_t flags, int unused);
};
}

void SP::cModelWorld::SetInWorld(ListNode* n, bool b)
{
    if (mWorldType == 0)
        return;
    if (((n->flags >> 0xf) & 1) == (uint32_t)b)
        return;
    ListNode* node = (ListNode*)((char*)n - 8);
    ListNode* prev = node->prev;
    ListNode* next = node->next;
    next->prev = prev;
    prev->next = next;
    node->prev = 0;
    node->next = 0;
    if (b) {
        node->next = mListA.next;
        node->prev = &mListA;
        mListA.next = node;
        node->next->prev = node;
        AddAttachments(node);
    } else {
        node->next = mListB.next;
        node->prev = &mListB;
        mListB.next = node;
        node->next->prev = node;
        ShutdownModel(node);
    }
    if (b)
        node->flags |= 0x8000;
    else
        node->flags &= 0xffff7fff;
}

// ---------------------------------------------------------------------------
// @ 0x0074B170  cLoadQueue reset/clear (this in ecx; EH frame; refcount/list walk)
// ---------------------------------------------------------------------------
struct ClqJob { int Release(); };                       // SP::cJob::Release 0x00690120
struct ClqRef { char pad[4]; uint32_t mnRef; };         // refcounted + vtable
struct SlotEntry {                                      // 0x1c-byte local (EH-scoped)
    uint32_t w[7];
    SlotEntry();
    ~SlotEntry();
};
SlotEntry::SlotEntry() { w[0] = 0; w[1] = 0; w[2] = 0; w[3] = 0; w[4] = 0; w[5] = 0; w[6] = 0; }
SlotEntry::~SlotEntry() {}

void __fastcall cloadqueue_b170(void* self_)
{
    char* s = (char*)self_;
    if (s[0x1c] == 0)
        return;
    s[0x1c] = 0;

    ClqJob* j = *(ClqJob**)(s + 0x20);
    if (j) { *(void**)(s + 0x20) = 0; j->Release(); }
    j = *(ClqJob**)(s + 0x24);
    if (j) { *(void**)(s + 0x24) = 0; j->Release(); }

    void** slot = (void**)(s + 0x34);
    for (int i = 6; i != 0; --i, ++slot) {
        void* p = *slot;
        if (p) {
            *slot = 0;
            uint32_t* rc = (uint32_t*)((char*)p + 4);
            if (--*rc == 0) {
                *rc = 1;
                ((void(__thiscall*)(void*, int))VT(p)[0])(p, 1);
            }
        }
    }
    *(int*)(s + 0x2c) = 6;
    j = *(ClqJob**)(s + 0x30);
    if (j) { *(void**)(s + 0x30) = 0; j->Release(); }
    *(void**)(s + 0x4c) = 0;

    SlotEntry scratch;
    *(void**)s = 0;
    void* p4 = *(void**)(s + 4);
    if (p4) {
        *(void**)(s + 4) = 0;
        ((void(__thiscall*)(void*))VT(p4)[1])(p4);
    }
    *(void**)(s + 8) = 0;
    *(void**)(s + 0xc) = 0;
    *(void**)(s + 0x10) = 0;
    *(void**)(s + 0x14) = 0;
    *(void**)(s + 0x18) = 0;

    void* p28 = *(void**)(s + 0x28);
    if (p28) {
        *(void**)(s + 0x28) = 0;
        uint32_t n = *(uint32_t*)((char*)p28 + 0x40);
        if (n > 1) { *(uint32_t*)((char*)p28 + 0x40) = n - 1; return; }
        int b = (*(int*)((char*)p28 + 4) >> 31) & 1;
        ((void(__thiscall*)(void*, int))VT(p28)[0x170 / 4])(p28, b);
    }
    (void)scratch;
}

// ---------------------------------------------------------------------------
// @ 0x0074B2B0  cLoadQueue<T...>::~cLoadQueue   (EH, member-array destruction)
// ---------------------------------------------------------------------------
namespace SP {
struct cLoadingModel { uint32_t pad[0x14]; ~cLoadingModel(); };   // 0x50 bytes
struct LoadDeque { ~LoadDeque(); };
struct cLoadQueue {
    char pad[4];
    cLoadingModel arr[8];                       // +4, 0x50 each
    LoadDeque dq;                               // +0x284
    ~cLoadQueue();
};
}
SP::cLoadQueue::~cLoadQueue() {}

// ---------------------------------------------------------------------------
// @ 0x0074B390  eastl::partial_sort<cOccluder*>
// ---------------------------------------------------------------------------
struct cOccluder { float x, y, z, nx, ny, nz; };            // 0x18 bytes
typedef bool (__cdecl* OccluderComp)(const cOccluder&, const cOccluder&);
extern "C" void MakeHeapOccluder(cOccluder*, cOccluder*, OccluderComp);                      // 0x00747eb0
extern "C" void PopHeapOccluder(cOccluder*, cOccluder*, OccluderComp);                       // 0x00747f30
extern "C" void AdjustHeapOccluder(cOccluder*, int, int, int, cOccluder, OccluderComp);      // 0x00745cf0

void partial_sort_b390(void* a, void* b, void* c, void* cmp)
{
    cOccluder* first  = (cOccluder*)a;
    cOccluder* middle = (cOccluder*)b;
    cOccluder* last   = (cOccluder*)c;
    OccluderComp compare = (OccluderComp)cmp;

    MakeHeapOccluder(first, middle, compare);
    if (middle < last) {
        for (cOccluder* i = middle; i < last; ++i) {
            if (compare(*i, *first)) {
                cOccluder tmp = *i;
                *i = *first;
                AdjustHeapOccluder(first, 0, (int)(middle - first), 0, tmp, compare);
            }
        }
    }
    PopHeapOccluder(first, middle, compare);
}

// ---------------------------------------------------------------------------
// @ 0x0074B760  SP::cModelWorld::UpdateFromPropList
//   Resets the model's transform/bbox to defaults, then reads the model's property list:
//   scale (0xfba611), translate (0xfba610), euler degrees (0xfba613), bounds, radius, quaternion.
// ---------------------------------------------------------------------------
struct Vec3f { float x, y, z; };
struct Mat3f { float m[9]; };
struct FloatField {                              // float member assigned through a user operator=
    float v;
    FloatField& operator=(const float& o) { v = o; return *this; }
};
struct BBoxf { Vec3f mMin, mMax; };

struct Matrix33Template {                       // rw::math::fpu::Matrix33Template<float,0>
    float m[9];
    Matrix33Template() {}
    Matrix33Template(const Matrix33Template& x);   // 0x0041cb40 (Matrix3::Assign), out of line
};
struct RwMat33 {
    float m[9];
    RwMat33(const Matrix33Template& x);            // 0x0041cb40 (row-wise copy), out of line
};
struct V3 {                                     // Vector3 with a user copy ctor (movss copies)
    float x, y, z;
    uint32_t pad;
    V3() {}
    V3(float a, float b, float c) : x(a), y(b), z(c) {}
    V3(const V3& o) : x(o.x), y(o.y), z(o.z) {}
};
Matrix33Template Matrix33FromEulerXYZ(const V3& angles);   // 0x00453920

struct XForm {                                  // cSPTransform, 0x38 bytes
    uint16_t mFlags;
    uint16_t mCount;
    Vec3f mOffset;
    float mScale;
    Mat3f mRot;
};

struct Property {
    void* mpData;           // +0
    uint32_t pad4;
    int mnItemCount;        // +8
    uint32_t padC;
    uint16_t mnFlags;       // +0x10
    uint16_t mnType;        // +0x12

    float* GetFloat();      // 0x0041ea70
    BBoxf* GetBBox();       // 0x005f2320
    __forceinline void* Items()
    {
        if (mnFlags & 0x30)
            return mpData;
        return mnType ? (void*)this : 0;
    }
};
extern const float kDefaultFloat;   // 0x015d1168
extern const bool kDefaultBool;     // 0x015d115d
const Vec3f* GetDefaultVec3();      // 0x006bb5e0
const BBoxf* GetDefaultBBox();      // 0x006bb630
const float* GetDefaultVec4();      // 0x006bb610

__forceinline const float* ValFloat(Property* p)
{
    if (p->mnType == 0xd || p->mnType == 0x10) return (const float*)p->Items();
    return &kDefaultFloat;
}
__forceinline const bool* ValBool(Property* p)
{
    if (p->mnType == 1 || p->mnType == 0x10) return (const bool*)p->Items();
    return &kDefaultBool;
}
__forceinline const Vec3f* ValVec3(Property* p)
{
    if (p->mnType == 0x31 || p->mnType == 0x10) return (const Vec3f*)p->Items();
    return GetDefaultVec3();
}
__forceinline const BBoxf* ValBBox(Property* p)
{
    if (p->mnType == 0x39 || p->mnType == 0x10) return (const BBoxf*)p->Items();
    return GetDefaultBBox();
}
__forceinline const float* ValVec4(Property* p)
{
    if (p->mnType == 0x34 || p->mnType == 0x10) return (const float*)p->Items();
    return GetDefaultVec4();
}

struct IPropList {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
    virtual bool Get(uint32_t id, Property** out);       // +0x24
};
bool __cdecl GetPropertyAsFloatArray(IPropList* pl, uint32_t id, int* count, float** arr);   // 0x006a08b0

struct BBoxMember : BBoxf {
    void TransformBy(XForm* t);             // 0x00409dd0 (cSPBoundingBox::Transform)
};

struct ModelRec {                               // model record passed to UpdateFromPropList
    char pad0[0xc];
    uint32_t mFlags;                            // +0x0c
    char pad10[0x54 - 0x10];
    float mQuat[4];                             // +0x54
    char pad64[0x70 - 0x64];
    uint16_t mUpdateCount;                      // +0x70
    char pad72[2];
    FloatField mRadius;                         // +0x74
    BBoxMember mBox;                            // +0x78
    char pad90[0x9c - 0x90];
    int f9c;                                    // +0x9c
    char pada0[0xac - 0xa0];
    int fac;                                    // +0xac
    char padb0[0xd4 - 0xb0];
    float* mpArr;                               // +0xd4
    char padd8[0xe4 - 0xd8];
    XForm mXform;                               // +0xe4
    char pad11c[0x129 - 0x11c];
    uint8_t mCount129;                          // +0x129
};

extern const Mat3f gIdentity3;      // 0x0162ec4c
extern const Vec3f gZeroVec3;       // 0x0162eb0c

static __forceinline Vec3f GetV3(Property* p) { return *ValVec3(p); }
static __forceinline Vec3f ScaleV3(const Vec3f& a, float s)
{
    Vec3f r;
    r.x = a.x * s; r.y = a.y * s; r.z = a.z * s;
    return r;
}
static __forceinline float Len3(const Vec3f& v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }
static __forceinline const float& MaxF(const float& a, const float& b) { return (a < b) ? b : a; }

void SP::cModelWorld::UpdateFromPropList(IPropList* pl, void* mdl, uint32_t flags, int unused)
{
    ModelRec* m = (ModelRec*)mdl;
    XForm* t = &m->mXform;
    BBoxMember* box = &m->mBox;
    t->mRot = gIdentity3;
    t->mScale = 1.0f;
    t->mOffset = gZeroVec3;
    t->mFlags = 0;
    t->mCount = 0;
    box->mMin.x = -1.0f; box->mMin.y = -1.0f; box->mMin.z = -1.0f;
    box->mMax.x = 1.0f; box->mMax.y = 1.0f; box->mMax.z = 1.0f;
    m->mRadius = 1.0f;

    Property* prop = 0;
    bool hasBBox = false;

    if (pl->Get(0xfba611, &prop)) {
        t->mScale = *ValFloat(prop);
        t->mCount++;
    }
    if (pl->Get(0xfba610, &prop)) {
        V3 v(*(const V3*)ValVec3(prop));
        t->mFlags |= 4;
        t->mCount++;
        t->mOffset = *(Vec3f*)&v;
    }
    if (pl->Get(0xfba613, &prop)) {
        const Vec3f* d = ValVec3(prop);
        float dx = d->x, dy = d->y, dz = d->z;
        V3 e(dx * 0.017453292f, dy * 0.017453292f, dz * 0.017453292f);
        RwMat33 rot(Matrix33FromEulerXYZ(e));
        t->mFlags |= 2;
        t->mCount++;
        *(RwMat33*)&t->mRot = rot;
    }
    if (pl->Get(0x3704e55, &prop) && !*ValBool(prop))
        m->mFlags |= 0x40000;
    else
        m->mFlags &= 0xfffbffff;

    if (m->f9c == 0 && m->fac == 0) {
        if (pl->Get(0x31d2791, &prop)) {
            hasBBox = true;
            BBoxf* b = prop->GetBBox();
            box->mMax = b->mMax;
            box->mMin = b->mMin;
            if (t->mScale != 1.0f || (t->mFlags & 6))
                box->TransformBy(t);
        }
        if (pl->Get(0x31d2792, &prop)) {
            hasBBox = false;
            m->mRadius = *prop->GetFloat();
            if (t->mScale != 1.0f || (t->mFlags & 6)) {
                float r = m->mRadius.v * t->mScale;
                m->mRadius.v = r;
                m->mRadius.v = Len3(t->mOffset) + r;
            }
        }
    }
    m->mFlags &= 0xfffcffff;

    if (pl->Get(0xf9efba, &prop)) {
        hasBBox = true;
        const BBoxf* b = ValBBox(prop);
        box->mMax = b->mMax;
        box->mMin = b->mMin;
        if (t->mScale != 1.0f || (t->mFlags & 6))
            box->TransformBy(t);
        m->mFlags |= 0x10000;
        m->mFlags |= 0x20000;
    }
    if (pl->Get(0xf9efb9, &prop)) {
        m->mRadius = *ValFloat(prop);
        if (t->mScale != 1.0f || (t->mFlags & 6)) {
            float r = t->mScale * m->mRadius.v;
            m->mRadius.v = r;
            m->mRadius.v = Len3(t->mOffset) + r;
        }
        m->mFlags |= 0x20000;
    } else if (hasBBox) {
        Vec3f n;
        n.x = -box->mMin.x;
        n.y = -box->mMin.y;
        n.z = -box->mMin.z;
        const Vec3f& mx = m->mBox.mMax;
        const float& cz = MaxF(n.z, mx.z);
        const float& cy = MaxF(n.y, mx.y);
        const float& cx = MaxF(n.x, mx.x);
        m->mRadius.v = sqrtf(cz * cz + cy * cy + cx * cx);
    }
    if (!(flags & 0x10000000)) {
        int count;
        if (GetPropertyAsFloatArray(pl, 0x2e33a81, &count, &m->mpArr)) {
            if (count > 0)
                m->mCount129 = (uint8_t)count;
            else
                m->mpArr = 0;
        }
    }
    if (pl->Get(0xfba612, &prop)) {
        const float* q = ValVec4(prop);
        float a = q[0], b2 = q[1], c = q[2];
        float d = q[3];
        m->mQuat[0] = a; m->mQuat[1] = b2; m->mQuat[2] = c; m->mQuat[3] = d;
        m->mFlags |= 2;
    }
    AddAttachments((ListNode*)m);
    m->mUpdateCount++;
}

// ---------------------------------------------------------------------------
// @ 0x0074BDA0  slot-list find (this in ecx): chunk probe then vector insert
// ---------------------------------------------------------------------------
struct Quad { uint32_t v[4]; };
extern "C" void ChunkFind(uint32_t* out, Quad a, Quad b, int key);            // 0x00745560
struct Stub747190 { void* F(int*); };                                         // 0x00747190
struct SlotList {
    char pad0[0x28c];
    Quad mQ1;                                     // +0x28c
    Quad mQ2;                                     // +0x29c
    void Find(void* key);
    void Erase(int* key);
};
void SlotList::Find(void* key_)
{
    char* self = (char*)this;
    int* key = (int*)key_;
    int out[4];
    ChunkFind((uint32_t*)out, mQ1, mQ2, key[0]);
    if (out[0] != *(int*)(self + 0x29c)) {
        ((Stub747190*)out[0])->F(key);
        return;
    }
    ((Vec1c*)(self + 0x284))->DoInsert((const T1c*)key);
}

// ---------------------------------------------------------------------------
// @ 0x0074BE40  slot-list erase by key (this in ecx; EH frame; chunk walk)
// ---------------------------------------------------------------------------
void SlotList::Erase(int* key)
{
    char* self = (char*)this;
    int* p        = *(int**)(self + 0x28c);
    int* chunkEnd = *(int**)(self + 0x294);
    int** chunkArr = *(int***)(self + 0x298);
    int* limit    = *(int**)(self + 0x29c);
    if (p == limit)
        return;
    do {
        if (*p == *key) {
            SlotEntry scratch;
            (void)scratch;
            *p = 0;
            void* q = (void*)p[1];
            if (q) {
                p[1] = 0;
                ((void(__thiscall*)(void*))VT(q)[1])(q);
            }
            p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0; p[6] = 0;
        }
        p += 7;
        if (p == chunkEnd) {
            chunkArr += 1;
            p = *chunkArr;
            chunkEnd = p + 0x38;
        }
    } while (p != limit);
}

// ---------------------------------------------------------------------------
// @ 0x0074BF10  eastl::vector<T8>::insert(position, value)  (element 8B)
// ---------------------------------------------------------------------------
struct Pair8 { uint32_t a, b; };
extern "C" void* FUN_0099efa0(char* first, char* last, char* dst);          // 0x0099efa0 uninit move
struct Vec8Ins {
    void Insert(void* pos, void* val);
};
void Vec8Ins::Insert(void* pos_, void* val_)
{
    char* self = (char*)this;
    Pair8* end = *(Pair8**)(self + 4);
    if (end != *(Pair8**)(self + 8)) {
        Pair8* position = (Pair8*)pos_;
        const Pair8* value = (const Pair8*)val_;
        const Pair8* pValue = value;
        if (pValue >= position && pValue < end)
            ++pValue;
        if (end)
            *end = end[-1];
        Pair8* src = end - 1;
        Pair8* dst = end;
        while (src != position) {
            --src; --dst;
            *dst = *src;
        }
        *position = *pValue;
        *(Pair8**)(self + 4) = end + 1;
        return;
    }
    int nPrev = (int)(*(Pair8**)(self + 4) - *(Pair8**)self);
    int nNew = (nPrev > 0) ? nPrev * 2 : 1;
    Pair8* pNew = nNew ? (Pair8*)eastl_alloc((uint32_t)(nNew * 8), "Graphics", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    Pair8* p = (Pair8*)FUN_0099efa0((char*)*(Pair8**)self, (char*)pos_, (char*)pNew);
    if (p)
        *p = *(const Pair8*)val_;
    Pair8* pEnd = (Pair8*)FUN_0099efa0((char*)pos_, (char*)*(Pair8**)(self + 4), (char*)(p + 1));
    Pair8* begin0 = *(Pair8**)self;
    if (begin0 && begin0 != *(Pair8**)(self + 0x10))
        eastl_dealloc(begin0);
    *(Pair8**)self = pNew;
    *(Pair8**)(self + 4) = pEnd;
    *(Pair8**)(self + 8) = pNew + nNew;
}

// ---------------------------------------------------------------------------
// @ 0x0074C020  eastl::vector<Vertex3D>::insert(position, value)  (element 0x18)
// ---------------------------------------------------------------------------
struct Vec6 { float mX, mY, mZ, mNX, mNY, mNZ; };                           // EA::Text::Vertex3D
extern "C" char* UninitCopy24(char* first, char* last, char* dst);          // 0x00745ca0
extern "C" char* CopyBackward24(char* first, char* last, char* dst);        // 0x00cc8b50
struct Vec24Ins {
    void Insert(void* pos, void* val);
};
void Vec24Ins::Insert(void* pos_, void* val_)
{
    char* self = (char*)this;
    Vec6* end = *(Vec6**)(self + 4);
    if (end != *(Vec6**)(self + 8)) {
        Vec6* position = (Vec6*)pos_;
        const Vec6* value = (const Vec6*)val_;
        const Vec6* pValue = value;
        if (pValue >= position && pValue < end)
            ++pValue;
        if (end)
            *end = end[-1];
        CopyBackward24((char*)position, (char*)(end - 1), (char*)end);
        *position = *pValue;
        *(Vec6**)(self + 4) = end + 1;
        return;
    }
    int nPrev = (int)(((char*)*(Vec6**)(self + 4) - *(char**)self) / 0x18);
    int nNew = (nPrev > 0) ? nPrev * 2 : 1;
    Vec6* pNew = nNew ? (Vec6*)eastl_alloc((uint32_t)(nNew * 0x18), "Graphics", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    char* p = UninitCopy24((char*)*(Vec6**)self, (char*)pos_, (char*)pNew);
    if (p)
        *(Vec6*)p = *(const Vec6*)val_;
    Vec6* pEnd = (Vec6*)UninitCopy24((char*)pos_, (char*)*(Vec6**)(self + 4), p + 0x18);
    Vec6* begin0 = *(Vec6**)self;
    if (begin0 && begin0 != *(Vec6**)(self + 0x10))
        eastl_dealloc(begin0);
    *(Vec6**)self = pNew;
    *(Vec6**)(self + 4) = pEnd;
    *(Vec6**)(self + 8) = pNew + nNew;
}
