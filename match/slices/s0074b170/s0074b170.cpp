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
struct cModelWorld {
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
// @ 0x0074B170  cLoadQueue reset/clear   (partial: refcount/list walk stubbed)
// ---------------------------------------------------------------------------
void cloadqueue_b170(void* self)
{
    (void)self;
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
// @ 0x0074B390  eastl::partial_sort<cOccluder*>   (partial)
// ---------------------------------------------------------------------------
void partial_sort_b390(void* a, void* b, void* c, void* cmp)
{
    (void)a; (void)b; (void)c; (void)cmp;
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
// @ 0x0074BDA0  slot-list find helper   (partial)
// ---------------------------------------------------------------------------
void list_find_bda0(void* self, void* key)
{
    (void)self; (void)key;
}

// ---------------------------------------------------------------------------
// @ 0x0074BE40  slot-list erase by key   (partial)
// ---------------------------------------------------------------------------
void list_erase_be40(void* self, int* key)
{
    (void)self; (void)key;
}

// ---------------------------------------------------------------------------
// @ 0x0074BF10  vector::insert (element 8B)   (partial: growth path)
// ---------------------------------------------------------------------------
void vec_insert_bf10(void* self, void* pos, void* val)
{
    (void)self; (void)pos; (void)val;
}

// ---------------------------------------------------------------------------
// @ 0x0074C020  vector::insert (element 0x18B)   (partial: growth path)
// ---------------------------------------------------------------------------
void vec_insert_c020(void* self, void* pos, void* val)
{
    (void)self; (void)pos; (void)val;
}
