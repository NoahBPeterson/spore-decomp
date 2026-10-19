// Slice s00741210 (0x00741210-0x00741aa0): SP::cModelInstance geometry construction.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
#include "types.h"
#include <intrin.h>

// External callees (masked relocations).
extern "C" void FUN_007403c0(void* p);   // 0x7403c0
extern "C" void FUN_007418f0(void* a, void* b);   // 0x7418f0

struct ResBase {
    virtual void v0();
    virtual void v1();
};

struct cMI_Construct {
    char    pad0[8];
    void*   mBegin8;                  // +0x8
    void*   mEndc;                    // +0xc
    char    pad10[0xc4 - 0x10];
    ResBase* mResource;               // +0xc4

    void AddGeometryFromArena(ResBase* p);          // 0x741210
    bool ConstructFromArenaResource(ResBase* p);    // 0x741a40
    void Sub3c0(ResBase* p);                        // 0x7403c0
};

// ---------------------------------------------------------------------------
// @ 0x00741a40  SP::cModelInstance::ConstructFromArenaResource
// ---------------------------------------------------------------------------
bool cMI_Construct::ConstructFromArenaResource(ResBase* p)
{
    ResBase* old = mResource;
    if (p != old) {
        if (p)
            p->v0();
        mResource = p;
        if (old)
            old->v1();
    }
    AddGeometryFromArena(p);
    if (mBegin8 == mEndc)
        return false;
    Sub3c0(p);
    return true;
}

// ===========================================================================
// Remaining geometry helpers (large; reconstruction in progress).
// ===========================================================================


// ---------------------------------------------------------------------------
// @ 0x00741aa0  eastl::vector<8-byte refcounted>::insert
// ---------------------------------------------------------------------------
struct RefCounted {
    virtual void v0();
    virtual void v1();
    volatile int mnRefCount;         // +0x4
};

struct RefPair8 {
    int         value;               // +0x0
    RefCounted* p;                   // +0x4
    RefPair8& operator=(const RefPair8& o);               // 0x0042f8b0 (thiscall, ret 4)
};

RefPair8* __cdecl CopyPairs(RefPair8* first, RefPair8* last, RefPair8* dst);      // 0x0073c410
RefPair8* __cdecl ReleasePairs(RefPair8* first, RefPair8* last, RefPair8* dst);   // 0x0073c450
RefPair8* __cdecl copy_backward_ref(RefPair8* first, RefPair8* last, RefPair8* result);   // 0x0073f440
void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int flags, int debugFlags, const char* file, int line);   // 0x00f473a0
void __cdecl EASTL_allocator_deallocate(void* p);     // 0x00f47380

struct Vec8 {
    RefPair8* mpBegin;               // +0x0
    RefPair8* mpEnd;                 // +0x4
    RefPair8* mpCapacity;            // +0x8
    RefPair8* insert(RefPair8* pos, const RefPair8* v);
    __declspec(noinline) void DoInsertValue(RefPair8* pos, const RefPair8* v);   // 0x7418f0
};

RefPair8* Vec8::insert(RefPair8* pos, const RefPair8* v)
{
    RefPair8* p = mpEnd;
    int idx = (int)(pos - mpBegin);
    if (pos == p && p != mpCapacity) {
        mpEnd = p + 1;
        if (p != 0) {
            p->value = v->value;
            RefCounted* r = v->p;
            p->p = r;
            if (r) {
                _InterlockedIncrement((volatile long*)&r->mnRefCount);
            }
        }
    } else {
        DoInsertValue(pos, v);
    }
    return mpBegin + idx;
}


// @ 0x007418f0  eastl::vector<RefPair8>::DoInsertValue (insert one element, grow if full)
void Vec8::DoInsertValue(RefPair8* pos, const RefPair8* v)
{
    RefPair8* end = mpEnd;
    if (end != mpCapacity) {
        const RefPair8* pv = v;
        if (v >= pos && v < end)
            ++pv;
        if (end != 0) {
            end->value = end[-1].value;
            RefCounted* r = end[-1].p;
            end->p = r;
            if (r)
                _InterlockedIncrement((volatile long*)&r->mnRefCount);
        }
        copy_backward_ref(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
        return;
    }
    unsigned n = (unsigned)(end - mpBegin);
    unsigned newCap = (n > 0) ? n * 2 : 1;
    RefPair8* newBegin = newCap ?
        (RefPair8*)EASTL_allocator_allocate(newCap * sizeof(RefPair8), "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    RefPair8* oldBegin = mpBegin;
    RefPair8* newPos = CopyPairs(oldBegin, pos, newBegin);
    ReleasePairs(oldBegin, pos, newBegin);
    if (newPos) {
        newPos->value = v->value;
        RefCounted* r = v->p;
        newPos->p = r;
        if (r)
            _InterlockedIncrement((volatile long*)&r->mnRefCount);
    }
    RefPair8* oldEnd = mpEnd;
    RefPair8* newEnd = CopyPairs(pos, oldEnd, newPos + 1);
    ReleasePairs(pos, oldEnd, newPos + 1);
    if (mpBegin)
        EASTL_allocator_deallocate(mpBegin);
    mpBegin = newBegin;
    mpEnd = newEnd;
    mpCapacity = newBegin + newCap;
}


// ---------------------------------------------------------------------------
// SP::cLoadQueue<...>::StallUntilLoaded: clear the output vector, then collect the shader data of
// every loaded model that has dirty soft state.
// ---------------------------------------------------------------------------
extern "C" void* EASTL_memmove(void* dst, const void* src, unsigned int n);   // 0x011e0744

struct UIntVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void DoInsertValue(uint32_t* pos, const uint32_t& v);   // 0x004558a0
    void erase(uint32_t* first, uint32_t* last)
    {
        EASTL_memmove(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const uint32_t& v)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

struct ShaderOwner {
    char pad0[8];
    uint32_t mDirty;                                // +0x8
    const uint32_t* D3D9GetShaderData(int id);      // 0x011edcf0
};

struct LoadedModel {
    char pad0[4];
    ShaderOwner* mOwner;                            // +0x4
};

struct cLoadQueueS {
    char pad0[0x30];
    LoadedModel** mpBegin;                          // +0x30
    LoadedModel** mpEnd;                            // +0x34
    void StallUntilLoaded(UIntVec* out);
};

// @ 0x00741710
void cLoadQueueS::StallUntilLoaded(UIntVec* out)
{
    out->clear();
    const int n = (int)(mpEnd - mpBegin);
    for (int i = 0; i < n; ++i) {
        ShaderOwner* o = mpBegin[i]->mOwner;
        if (o && (o->mDirty & 8)) {
            const uint32_t* d = o->D3D9GetShaderData(0x20f);
            if (d)
                out->push_back(*d);
        }
    }
}

// ---------------------------------------------------------------------------
// SP::cModelInstance::AddGeometryFromArena: walk the arena's exported objects, collecting meshes,
// materials and the bounding box.
// ---------------------------------------------------------------------------
#include <math.h>
#include <xmmintrin.h>
#pragma intrinsic(sqrt)

struct Elem { uint32_t a, b; Elem(); ~Elem(); };               // 0x006c0fa0 / 0x00c2e4e0
__declspec(noinline) Elem::Elem() { a = 0; b = 1; }
__declspec(noinline) Elem::~Elem() {}
struct ExpObj { uint32_t type; void* obj; uint32_t z0, z1, z2, z3; Elem arr[4];
    ExpObj() : type(0), obj(0), z0(0), z1(0), z2(0), z3(0) { arr[0].a = 0; arr[0].b = 1; }
};
struct Arena {
    int GetNumExportedObjects();                           // 0x011e23a0
    void GetExportedObjectByIndex(int idx, ExpObj* out);   // 0x011e28e0
};
struct ResKey { unsigned instanceID, typeID, groupID; };
struct SrcModel {
    char pad0[8];
    ResKey mKey;                                           // +0x08 resource key
    char pad14[4];
    Arena* arena;                                          // +0x18
};

extern wchar_t gEmptyString16[2];                          // 0x01667bac
void operator delete[](void* p);                           // 0x00f47380

struct EString16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    unsigned mAllocator;
    EString16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~EString16() {
        if ((int)(((unsigned)mpCapacity - (unsigned)mpBegin) & 0xfffffffe) > 2 && mpBegin)
            operator delete[](mpBegin);
    }
};

#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();
struct ResManager {
    V4(p0) V4(p1) V4(p2) V4(p3) V4(p4) V4(p5) V4(p6)
    virtual void q28(); virtual void q29(); virtual void q30();
    virtual void KeyToName(const ResKey* key, EString16* out);   // +0x7c
};
ResManager* __cdecl GetManager();                          // 0x0067dcd0

struct MatInfo;
struct MatRes;
struct MaterialManager {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9();
    virtual MatInfo* Wrap(MatRes* r);                      // +0x28
    virtual void m11(); virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual MatRes* Create(unsigned id, SrcModel* src);    // +0x40
};
MaterialManager* __cdecl GetMaterialManager();             // 0x0067dd70

struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    void DoInsertValue(void** pos, void* const& v);        // 0x006ec4a0
    void push_back(void* const& v)
    {
        void** p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p)
                *p = v;
        } else {
            DoInsertValue(p, v);
        }
    }
};

extern const float g_f0162e88c;     // 0x0162e88c
extern const float g_f0162e890;     // 0x0162e890
extern const float g_f0162e894;     // 0x0162e894
extern const float g_fMax;          // 0x0140d56c  FLT_MAX
extern const float g_fMin;          // 0x013f51ac  -FLT_MAX

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct BBox3 { Vec3 mMin, mMax; BBox3() {} BBox3(const Vec3& a, const Vec3& b) : mMin(a), mMax(b) {} };
struct ASrcBox {
    __m128 mn, mx;
    __m128 GetMin() const { return mn; }
    __m128 GetMax() const { return mx; }
};

template <class T> inline const T& MaxRef(const T& a, const T& b) { return (b < a) ? a : b; }

struct cMI_Geo {
    char pad0[8];
    PtrVec mMeshes;                 // +0x08
    char pad14[0x30 - 0x14];
    PtrVec mMats;                   // +0x30
    char pad3c[0xa8 - 0x3c];
    BBox3 mBox;                     // +0xa8
    float mRadius;                  // +0xc0
    void AddGeometryFromArena(SrcModel* src);
};

// @ 0x00741210
void cMI_Geo::AddGeometryFromArena(SrcModel* src)
{
    Arena* arena = src->arena;
    int n = arena->GetNumExportedObjects();
    mBox.mMin = Vec3(g_fMax, g_fMax, g_fMax);
    mBox.mMax = Vec3(g_fMin, g_fMin, g_fMin);
    MaterialManager* mm = GetMaterialManager();
    for (int i = 0; i < n; ++i) {
        ExpObj x;
        arena->GetExportedObjectByIndex(i, &x);
        switch (x.type) {
        case 0x2000c: {
            ResKey key = src->mKey;
            EString16 name;
            GetManager()->KeyToName(&key, &name);
            break;
        }
        case 0x2001a: {
            void* mesh = *(void**)x.obj;
            mMeshes.push_back(mesh);
            MatRes* r = mm->Create(((unsigned*)x.obj)[2], src);
            void* mat = mm->Wrap(r);
            mMats.push_back(mat);
            break;
        }
        case 0x80005: {
            const ASrcBox* sb = (const ASrcBox*)x.obj;
            BBox3 b(Vec3(sb->GetMin().m128_f32[0], sb->GetMin().m128_f32[1], sb->GetMin().m128_f32[2]),
                    Vec3(sb->GetMax().m128_f32[0], sb->GetMax().m128_f32[1], sb->GetMax().m128_f32[2]));
            if (mBox.mMin.x > mBox.mMax.x) {
                mBox = b;
            } else {
                if (mBox.mMin.x > b.mMin.x) mBox.mMin.x = b.mMin.x;
                if (b.mMax.x > mBox.mMax.x) mBox.mMax.x = b.mMax.x;
                if (mBox.mMin.y > b.mMin.y) mBox.mMin.y = b.mMin.y;
                if (b.mMax.y > mBox.mMax.y) mBox.mMax.y = b.mMax.y;
                if (mBox.mMin.z > b.mMin.z) mBox.mMin.z = b.mMin.z;
                if (b.mMax.z > mBox.mMax.z) mBox.mMax.z = b.mMax.z;
            }
            break;
        }
        }
    }
    if (mBox.mMin.x > mBox.mMax.x) {
        mBox.mMin = Vec3(g_f0162e88c - 1.0f, g_f0162e890 - 1.0f, g_f0162e894 - 1.0f);
        mBox.mMax = Vec3(g_f0162e88c + 1.0f, g_f0162e890 + 1.0f, g_f0162e894 + 1.0f);
    }
    Vec3 neg(-mBox.mMin.x, -mBox.mMin.y, -mBox.mMin.z);
    const float& rz = MaxRef(mBox.mMax.z, neg.z);
    const float& ry = MaxRef(mBox.mMax.y, neg.y);
    const float& rx = MaxRef(mBox.mMax.x, neg.x);
    mRadius = (float)sqrt(rx * rx + ry * ry + rz * rz);
}
