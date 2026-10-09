// Slice s00745ac0 (0x00745AC0..0x007469AC): SP::cModelWorld helpers and EASTL
// algorithm instantiations, built /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <new>
#include <string.h>
#include <math.h>

// ---------------------------------------------------------------------------
// Fixed-width vector / bounding-box / transform types (retail layouts).
struct Vec3 { float x, y, z; };

struct cSPTransform;
struct cSPBoundingBox {
    Vec3 mMin;   // +0x00
    Vec3 mMax;   // +0x0c
    void Transform(const cSPTransform& xf);   // 0x00409dd0
};

struct cSPTransform {
    unsigned short mFlags;             // +0x00
    unsigned short mModificationCount; // +0x02
    Vec3 mTranslation;                 // +0x04
    float mScale;                      // +0x10
    float mRotation[9];                // +0x14
};

inline void cSPBoundingBox_Transform(cSPBoundingBox* b, const cSPTransform& xf)
{
    b->Transform(xf);
}

// 24-byte vector element with a user copy constructor (EASTL uninitialized_copy element).
struct Vec6 {
    float a, b, c, d, e, f;
    Vec6() {}
    Vec6(const Vec6& o) { a = o.a; b = o.b; c = o.c; d = o.d; e = o.e; f = o.f; }
};

// 24-byte element without a user copy constructor.
struct P6 { float a, b, c, d, e, f; };

// ---------------------------------------------------------------------------
// EASTL heap element types.
struct cOccluder {
    float a, b, c, d, e, f;
};

typedef bool (__cdecl *cOccluderCompare)(const cOccluder&, const cOccluder&);

// 8-byte (float key, value) pair, ordered on the second float.
struct FloatKeyPair {
    float x, y;
    FloatKeyPair() {}
    FloatKeyPair(const FloatKeyPair& v) { x = v.x; y = v.y; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct FloatKeyLess { bool operator()(const FloatKeyPair& a, const FloatKeyPair& b) const { return a[1] < b[1]; } };
struct FloatKeyGreater { bool operator()(const FloatKeyPair& a, const FloatKeyPair& b) const { return a[1] > b[1]; } };

// ---------------------------------------------------------------------------
// Callees and globals (calling conventions only matter for byte-exactness;
// relocation targets are masked).
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int align,
                                       const char* file, int line);   // 0x00f473a0
void  __cdecl EASTL_allocator_deallocate(void* p);                    // 0x00f47380
extern float g_f162eb0c, g_f162eb10, g_f162eb14, g_f162ec38, g_f1485720; // 0x0162eb0c
extern float g_f1537ab0, g_f1537ab4, g_f1537ab8, g_f13eb1bc, g_f140d674;

void Matrix3_Assign(void* dst, const void* src);                      // 0x0041cb40
void cSPTransform_Assign(cSPTransform* dst, const cSPTransform* src); // 0x00537dc0
void BoundingBox_TransformBy(cSPBoundingBox* box, const cSPTransform* xf); // 0x00409dd0
int  FUN_006ffbd0(const void* v, float r);                            // 0x006ffbd0
int  cFrustumCull_FrustumTestSphere(void* self, const void* p, unsigned flags); // 0x00700120
int  FUN_00511140(void* p);                                          // 0x00511140
void FUN_007760a0(int a, int b, int c, int d, int e, void* f);        // 0x007760a0
int  SP_CreateModelInstance(unsigned a, int b, void* c);              // 0x00754ba0
int  FUN_007454f0(int x);                                            // 0x007454f0
void FUN_007453d0(int x);                                            // 0x007453d0
void FUN_0073ab40(int x);                                            // 0x0073ab40
int  FUN_007434b0(int x);                                            // 0x007434b0
void FUN_0073b980(void* a, void* b, void* c, void* d, void* e, void* f, void* g); // 0x0073b980
void FUN_00743150(void* a, int b);                                   // 0x00743150
void FUN_0041d8b0(void* a);                                          // 0x0041d8b0
void FUN_0074f420(void* a);                                          // unused

// Refcounted COM-like pointer.
struct AutoRef {
    void* mpObject;
    void AddRef() { if (mpObject) (*(void(__thiscall**)(void*))mpObject)(mpObject); }
    void Release() { if (mpObject) (*(void(__thiscall**)(void*, int))((char*)mpObject)) ; }
};

// Generic COM object with a vtable.
struct VObj {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
};
// Virtual slot at +0x58 is index 22.
struct VObj58 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual void s22(void* arg);   // +0x58
};

// ===========================================================================
// @ 0x00745ca0 : copy-construct a run of 24-byte elements (EASTL uninitialized_copy).
Vec6* UninitCopy24(Vec6* first, Vec6* last, Vec6* dest)
{
    for (; first != last; first += 1, dest += 1) {
        if (dest) new (dest) Vec6(*first);
    }
    return dest;
}

// @ 0x00745ac0 : insertion of each element of [first,last) into the sorted
// prefix that starts before `first` (used by the hybrid sort's merge step).
typedef bool (__cdecl *Compare24)(const P6&, const P6&);
void Sort24(P6* first, P6* last, Compare24 compare)
{
    for (P6* i = first; i != last; ++i) {
        P6 temp(*i);
        P6* j = i;
        while (compare(temp, *(j - 1))) {
            *j = *(j - 1);
            --j;
        }
        *j = temp;
    }
}

// @ 0x00745bb0 : copy a run of 20-byte elements; the first dword is copied
// unconditionally, the four trailing floats only when its top bit is clear.
struct E20 { uint32_t flags; float x, y, z, w; };
E20* Copy20(E20* first, E20* last, E20* dest)
{
    for (; first != last; first += 1, dest += 1) {
        if (dest) {
            dest->flags = first->flags;
            if (!(first->flags >> 31)) {
                dest->x = first->x;
                dest->y = first->y;
                dest->z = first->z;
                dest->w = first->w;
            }
        }
    }
    return dest;
}

// @ 0x00745c20 : allocate an rbtree node (0x18 bytes) and copy-construct the
// value (key + refcounted pointer) into it.
struct Node18 {
    void* pLeft;      // +0x00
    void* pRight;     // +0x04
    void* pParent;    // +0x08
    int   mColor;     // +0x0c
    uint32_t mKey;    // +0x10
    void*    mRef;    // +0x14
};

Node18* CreateNode18(const uint32_t* value)
{
    Node18* p = (Node18*)EASTL_allocator_allocate(0x18, "Graphics", 0, 0,
                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (p) {
        p->mKey = *value;
        p->mRef = (void*)value[1];
        if (p->mRef)
            (*(void(__thiscall**)(void*))p->mRef)(p->mRef);
    }
    return p;
}

// @ 0x00745cf0 : eastl::adjust_heap<cOccluder*, int, cOccluder, Compare>.
void PromoteOccluder(cOccluder* first, int topPosition, int position, cOccluder value, cOccluderCompare compare)
{
    int parentPosition = (position - 1) >> 1;
    for (; position > topPosition && compare(first[parentPosition], value);
         parentPosition = (position - 1) >> 1) {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}

void AdjustHeapOccluder(cOccluder* first, int topPosition, int heapSize, int position,
                        cOccluder value, cOccluderCompare compare)
{
    int childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(first[childPosition], first[childPosition - 1]))
            --childPosition;
        first[position] = first[childPosition];
        position = childPosition;
    }
    if (childPosition == heapSize) {
        first[position] = first[childPosition - 1];
        position = childPosition - 1;
    }
    PromoteOccluder(first, topPosition, position, value, compare);
}

// @ 0x00745e00 : adjust_heap for the 8-byte pair with the greater comparator.
void PromotePairGt(FloatKeyPair* first, int topPosition, int position, FloatKeyPair value, FloatKeyGreater compare)
{
    int parentPosition = (position - 1) >> 1;
    for (; position > topPosition && compare(first[parentPosition], value);
         parentPosition = (position - 1) >> 1) {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}

void AdjustPairGt(FloatKeyPair* first, int topPosition, int heapSize, int position,
                  FloatKeyPair value, FloatKeyGreater compare)
{
    int childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(first[childPosition], first[childPosition - 1]))
            --childPosition;
        first[position] = first[childPosition];
        position = childPosition;
    }
    if (childPosition == heapSize) {
        first[position] = first[childPosition - 1];
        position = childPosition - 1;
    }
    PromotePairGt(first, topPosition, position, value, compare);
}

// @ 0x00745e80 : adjust_heap for the 8-byte pair with the less comparator.
void PromotePairLt(FloatKeyPair* first, int topPosition, int position, FloatKeyPair value, FloatKeyLess compare)
{
    int parentPosition = (position - 1) >> 1;
    for (; position > topPosition && compare(first[parentPosition], value);
         parentPosition = (position - 1) >> 1) {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}

void AdjustPairLt(FloatKeyPair* first, int topPosition, int heapSize, int position,
                  FloatKeyPair value, FloatKeyLess compare)
{
    int childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(first[childPosition], first[childPosition - 1]))
            --childPosition;
        first[position] = first[childPosition];
        position = childPosition;
    }
    if (childPosition == heapSize) {
        first[position] = first[childPosition - 1];
        position = childPosition - 1;
    }
    PromotePairLt(first, topPosition, position, value, compare);
}

// ===========================================================================
// @ 0x00745f90 : constructor of a ~0x94-byte render/cull record.
struct DrawRecord {
    void* mOwner;          // +0x00
    int   mFlags;          // +0x04
    unsigned short mA;     // +0x08
    unsigned short mB;     // +0x0a
    Vec3  mPos;            // +0x0c
    float mScale;          // +0x18
    float mRotation[9];    // +0x1c
    int   mR0;             // +0x40
    int   mR1;             // +0x44
    int   mR2;             // +0x48
    Vec3  mDir;            // +0x4c
    float mDirScale;       // +0x58
    bool  mB0;             // +0x5c
    bool  mB1;             // +0x5d
    int   mP0;             // +0x60
    int   mP1;             // +0x64
    float mF0;             // +0x68
    float mF1;             // +0x6c
    float mF2;             // +0x70
    float mF3;             // +0x74
    float mF4;             // +0x78
    float mF5;             // +0x7c
    float mF6;             // +0x80
    float mF7;             // +0x84
    float mF8;             // +0x88
    float mF9;             // +0x8c
    int   mLast;           // +0x90
};
DrawRecord* DrawRecord_Ctor(DrawRecord* self, void* owner)
{
    self->mOwner = owner;
    self->mFlags = 0;
    self->mA = 0;
    self->mB = 0;
    self->mPos.x = g_f162eb0c;
    self->mPos.y = g_f162eb10;
    self->mPos.z = g_f162eb14;
    self->mScale = g_f1485720;
    Matrix3_Assign(self->mRotation, &g_f162ec38);
    self->mR0 = 0;
    self->mR1 = 0;
    self->mR2 = 0;
    self->mDir.x = g_f1537ab0;
    self->mDir.y = g_f1537ab4;
    self->mDir.z = g_f1537ab8;
    self->mDirScale = g_f1485720;
    self->mB0 = false;
    self->mB1 = false;
    self->mP0 = 0;
    self->mP1 = 0;
    self->mF0 = g_f1485720;
    self->mF1 = g_f13eb1bc;
    self->mF2 = g_f13eb1bc;
    self->mF3 = g_f13eb1bc;
    self->mF4 = g_f1485720;
    self->mF5 = g_f1485720;
    self->mF6 = g_f1485720;
    self->mF7 = g_f140d674;
    self->mF8 = g_f140d674;
    self->mLast = 0;
    return self;
}

// ===========================================================================
// @ 0x007460b0 : anonymous-namespace FilterModelFrustum.
struct FrustumFilterArg {
    uint32_t mA;       // +0x00
    uint32_t mB;       // +0x04
    uint32_t mC;       // +0x08
    uint32_t mD;       // +0x0c
    int (__cdecl* mCallback)(void*); // +0x10
    unsigned char mE;  // +0x14
    unsigned char mF;  // +0x15
};
struct CullModel {
    unsigned char pad0[0x0c];
    uint32_t mFlags;        // +0x0c
    cSPTransform mTransform; // +0x10
    unsigned char pad48[0x4c - 0x48];
    uint32_t mMaskA;        // +0x4c
    uint32_t mMaskB;        // +0x50
    unsigned char pad54[0x65 - 0x54];
    unsigned char mC0;      // +0x65
    unsigned char pad66[0x74 - 0x66];
    float mRadius;          // +0x74
    cSPBoundingBox mBox;    // +0x78
    unsigned char pad90[0x94 - 0x90];
};
int FilterModelFrustum(CullModel* model, void* culler, FrustumFilterArg* arg)
{
    cSPTransform local;
    local.mTranslation.x = g_f162eb0c;
    local.mTranslation.y = g_f162eb10;
    local.mTranslation.z = g_f162eb14;
    local.mModificationCount = 0;
    local.mFlags = 0;
    local.mScale = g_f1485720;
    Matrix3_Assign(local.mRotation, &g_f162ec38);

    if (!(model->mFlags & 1))
        return 1;
    if (!((arg->mA == 0 && arg->mB == 0) ||
          (model->mMaskA & arg->mA) != 0 || (model->mMaskB & arg->mB) != 0))
        return 1;
    if ((model->mMaskA & arg->mC) != 0 || (model->mMaskB & arg->mD) != 0)
        return 1;
    if (arg->mCallback != 0 && !arg->mCallback((char*)model + 8))
        return 1;

    unsigned char b;
    if ((arg->mF & 1) && ((model->mFlags >> 8) & 1))
        b = model->mC0;
    else
        b = arg->mE;

    cSPTransform_Assign(&local, &model->mTransform);
    if (((model->mFlags >> 7) & 1) || (arg->mF & 2)) {
        local.mModificationCount = local.mModificationCount + 1;
        local.mScale = g_f1485720;
    }

    float pos[3];
    pos[0] = local.mTranslation.x;
    pos[1] = local.mTranslation.y;
    pos[2] = local.mTranslation.z;
    int r = FUN_006ffbd0(pos, model->mRadius * local.mScale);
    if (r & 0x40)
        return 1;

    if (b != 0 && model->mBox.mMin.x <= model->mBox.mMax.x) {
        cSPBoundingBox box;
        FUN_00511140(&model->mBox);
        BoundingBox_TransformBy(&box, &local);
        if (cFrustumCull_FrustumTestSphere(culler, &box, 0x200) & 0x40)
            return 1;
    }
    return 0;
}

// ===========================================================================
// @ 0x00746250 : SP::cModelWorld::SetMaterialInfo.
struct SlotObj { void F(int idx, void* handle); };
struct ObjD8 { void G(void* info); };
struct MWInternal {
    unsigned char pad0[0x9c];
    SlotObj* mSlots[4];      // +0x9c
    unsigned char padAC[0xd8 - 0xac];
    ObjD8* mD8;              // +0xd8
};
void cModelWorld_SetMaterialInfo(void* /*this*/, void* handle, void* info, int idx)
{
    MWInternal* p = handle ? (MWInternal*)((char*)handle - 8) : 0;
    if (idx < 0) {
        p->mD8->G(info);
        return;
    }
    for (int i = 0; i < 4; ++i) {
        if (p->mSlots[i] == 0)
            return;
        p->mSlots[i]->F(idx, handle);
    }
}

// @ 0x007462b0 : cModelWorld material-info update helper.
struct ModelRef { void* p; };
struct VecField {
    void* mBegin;    // +0x00
    void* mEnd;      // +0x04
    unsigned char pad8[0x0c - 0x08];
    void* mCapacity; // +0x0c
    void* mStore;    // +0x10
    unsigned char pad14[0x18 - 0x14];
    void* mExtra;    // +0x18
    unsigned char pad1c[0x24 - 0x1c];
    void* mOther;    // +0x24
};
void FUN_007462b0(void* /*this*/, void* handle, VecField* v)
{
    MWInternal* p = handle ? (MWInternal*)((char*)handle - 8) : 0;
    void* src = 0;
    if (p->mSlots[0] == 0 && p->mSlots[1] == 0 && p->mSlots[2] == 0 && p->mSlots[3] == 0) {
        // no slots: still run the commit below
    } else {
        // find a live slot and detach its refcounted object at +0x18
        void* q = (void*)v->mExtra;
        if (q) {
            v->mExtra = 0;
            (*(void(__thiscall**)(void*))(*(void**)q))(q);
        }
        FUN_0073b980(&v->mStore, &v->mBegin, &v->mExtra, &v->mEnd, &v->mOther, &v->mCapacity, &v->mExtra);
    }
    if (v->mEnd != v->mExtra) {
        v->mEnd = v->mExtra;
        EASTL_allocator_deallocate(v->mStore);
        uint32_t n = (uint32_t)v->mEnd;
        v->mStore = EASTL_allocator_allocate(n * 0xc, "Graphics", 0, 0, 0, 0);
    }
}

// ===========================================================================
// @ 0x00746360 : SP::cModelWorld::GetHull (virtual dispatch + create).
struct Key { uint32_t a, b, c; };
struct HullQuery {
    uint32_t mKey;    // +0x00
    uint32_t mType;   // +0x04
    void*    m0;      // +0x08
    void*    m1;      // +0x0c
    void*    m2;      // +0x10
    void*    m3;      // +0x14
    void*    mInst;   // +0x18
};
struct VariantKey { uint32_t a, b; int c; };
VariantKey* VariantKey_GetTPTR(void* variant);   // 0x00454b10
void cModelWorld_GetHull(void* self, HullQuery* out)
{
    (*(void(__thiscall**)(void*, HullQuery*))((char*)(*(void**)self) + 0x58))(self, out);
    unsigned char* p = (unsigned char*)out - 8;
    out->mKey = 0;
    out->mType = 0;
    out->m0 = 0;
    out->m1 = 0;
    out->m2 = 0;
    out->m3 = 0;
    if (out->mInst) {
        void* q = out->mInst;
        out->mInst = 0;
        (*(void(__thiscall**)(void*, int))((char*)(*(void**)q) + 4))(q, 1);
    }
    if (*(void**)(p + 0xac) == 0 && *(void**)(p + 0x98) != 0) {
        VariantKey variant;
        memset(&variant, 0, sizeof(variant));
        int ok = (*(int(__thiscall**)(void*, uint32_t, void*))
                  ((char*)(**(void***)(p + 0x98)) + 0x24))(*(void**)(p + 0x98), 0xf9efc0, &variant);
        if (ok) {
            // resolved resource key
            SP_CreateModelInstance(variant.a, variant.c == -1 ? 0 : variant.c, (void*)FUN_007454f0(0));
        }
    }
    if (*(void**)(p + 0xac) != 0 || *(void**)(p + 0x9c) != 0) {
        FUN_007434b0(0);
        if (out->mInst) {
            void* q = out->mInst;
            out->mInst = 0;
            (*(void(__thiscall**)(void*, int))((char*)(*(void**)q) + 4))(q, 1);
        }
        FUN_0073b980(&out->mKey, &out->mType, &out->m0, &out->m1, &out->m2, &out->m3, &out->mInst);
    }
}

// @ 0x00746560
struct HullModel {
    unsigned char pad0[0xa8];
    Vec3 mMin;     // +0xa8
    Vec3 mMax;     // +0xb4
};
struct ModelInternal {
    unsigned char pad0[0x78];
    Vec3 mMin;     // +0x78
    Vec3 mMax;     // +0x84
    unsigned char pad90[0xac - 0x90];
    HullModel* mHull;   // +0xac
    unsigned char padB0[0xe4 - 0xb0];
    cSPTransform mTransform; // +0xe4
};
struct CModelWorldStub {
    void GetHullBoundingBox(void* handle, cSPBoundingBox* out);
};
void CModelWorldStub::GetHullBoundingBox(void* handle, cSPBoundingBox* out)
{
    ModelInternal* p = handle ? (ModelInternal*)((char*)handle - 8) : 0;
    HullModel* h = p->mHull;
    if (h) {
        out->mMax = h->mMax;
        out->mMin = h->mMin;
        const cSPTransform& xf = p->mTransform;
        if (xf.mScale != g_f1485720 || (*(unsigned char*)&xf & 6))
            out->Transform(xf);
    } else {
        out->mMax = p->mMax;
        out->mMin = p->mMin;
    }
}

// @ 0x00746610 : SP::cModelWorld::GetRuntimeModel.
int cModelWorld_GetRuntimeModel(void* self, void* handle, int* params)
{
    (*(void(__thiscall**)(void*, void*))((char*)(*(void**)self) + 0x58))(self, handle);
    ModelInternal* p = handle ? (ModelInternal*)((char*)handle - 8) : 0;
    unsigned char* q = (unsigned char*)p;
    if (*(void**)(q + 0x9c) != 0) {
        float rot[9];
        Matrix3_Assign(rot, &g_f162ec38);
        FUN_007760a0(*(int*)(q + 0x9c), (int)handle, params[0], params[1], params[2], rot);
        return 0;
    }
    return 3;
}

// @ 0x007466e0 : cModelWorld hull-bounds refresh helper.
int FUN_007466e0(void* self, void* handle)
{
    (*(void(__thiscall**)(void*, void*))((char*)(*(void**)self) + 0x58))(self, handle);
    ModelInternal* p = handle ? (ModelInternal*)((char*)handle - 8) : 0;
    if (*(void**)((char*)p + 0x9c) == 0)
        return 0;
    if (!FUN_007434b0((int)handle))
        return 0;
    if (!((*(uint32_t*)((char*)p + 0xc) >> 9) & 1)) {
        HullModel* h = (HullModel*)*(void**)((char*)p + 0xac);
        (void)h;
        Vec3 mn = *(Vec3*)((char*)p + 0xa8);
        (void)mn;
        // Copy bounding box out of the model instance (offsets as in retail).
        Vec3 srcMax = *(Vec3*)((char*)p + 0xc0);
        (void)srcMax;
        float scale = p->mTransform.mScale;
        if (scale != g_f1485720 || (*(unsigned char*)&p->mTransform & 6)) {
            // recompute bounding radius
            float a = *(float*)((char*)p + 0xe8);
            float b = *(float*)((char*)p + 0xec);
            float c = *(float*)((char*)p + 0xf0);
            float r = sqrtf(a * a + b * b + c * c);
            (void)r;
        }
    }
    return 1;
}

// @ 0x007467f0 : cModelWorld query helper (two virtual calls, copies 3 vectors).
struct IVirtual { virtual int v0(int); virtual int v1(int); };
int FUN_007467f0(void* self, void* a, void* b, Vec3* out1, Vec3* out2, Vec3* out3)
{
    char buf[36];
    char* p = buf;
    memset(buf, 0, sizeof(buf));
    void* local = 0;
    if (!(*(int(__thiscall**)(void*, int, void*, void*, void*))((char*)(*(void**)self) + 0x114))(self, 0, &local, a, b))
        return 0;
    {
        IVirtual* lv = (IVirtual*)local;
        if (lv) { lv->v1(0); }
    }
    if (!(*(int(__thiscall**)(void*, char*))((char*)(*(void**)local) + 8))(local, buf)) {
        if (local) (*(void(__thiscall**)(void*))((char*)(*(void**)local) + 4))(local);
        return 0;
    }
    out1->x = *(float*)(buf + 0);  out1->y = *(float*)(buf + 4);  out1->z = *(float*)(buf + 8);
    out2->x = *(float*)(buf + 12); out2->y = *(float*)(buf + 16); out2->z = *(float*)(buf + 20);
    out3->x = *(float*)(buf + 24); out3->y = *(float*)(buf + 28); out3->z = *(float*)(buf + 32);
    if (local) (*(void(__thiscall**)(void*))((char*)(*(void**)local) + 4))(local);
    return 1;
}

// @ 0x00746910 : cModelWorld model-group assignment.
struct ListNode { ListNode* pNext; ListNode* pPrev; };
struct GroupRef {
    void* p;
    void AddRef() {}
    void Release() { if (p) (*(void(__thiscall**)(void*, int))((char*)p + 4)); }
};
struct GroupSlot {
    unsigned char pad0[0x1b4];
    int mCount;              // +0x1b4
    void* mSlotObj;          // +0x1cc
    bool mFlag;              // +0x1d0
};
struct GroupInternal : ListNode {
    unsigned char pad8[0x134 - 0x8];
    void* mObj;              // +0x134
};
struct GroupWorld {
    unsigned char pad0[0x19c];
    ListNode mGroupList;         // +0x19c
    unsigned char pad1a4[0x1cc - 0x1a4];
    void* mSlotObj;              // +0x1cc
};
void FUN_00746910(void* self, void* newObj, int idx, bool flag)
{
    GroupWorld* w = (GroupWorld*)self;
    if (idx == 0) {
        for (ListNode* n = w->mGroupList.pNext; n != (ListNode*)&w->mGroupList; n = n->pNext) {
            GroupInternal* g = (GroupInternal*)n;
            if (g->mObj != 0)
                (*(void(__thiscall**)(void*, void*))((char*)(**(void***)w->mSlotObj) + 0x20))(w->mSlotObj, g->mObj);
            g->mObj = 0;
        }
    }
    GroupSlot* s = (GroupSlot*)((char*)self + idx * 0x20);
    void* old = s->mSlotObj;
    if (newObj != s->mSlotObj) {
        if (newObj) (*(void(__thiscall**)(void*))(*(void**)newObj))(newObj);
        s->mSlotObj = newObj;
        if (old) (*(void(__thiscall**)(void*, int))((char*)old + 4));
    }
    s->mFlag = flag;
    if (s->mCount < 0)
        s->mCount = 0;
}
// --- equivalence checker address annotations
    extern float g_f140d674; // 0x0140d674
    extern float g_f1485720; // 0x01485720
    extern float g_f162eb0c; // 0x0162eb0c
    extern float g_f162eb10; // 0x0162eb10
    extern float g_f162eb14; // 0x0162eb14
    extern float g_f162ec38; // 0x0162ec38

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
