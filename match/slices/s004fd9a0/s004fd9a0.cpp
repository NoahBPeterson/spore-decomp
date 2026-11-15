// Slice s004fd9a0: allocator/vector/string helpers (unoptimized module:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast).
#include "types.h"

struct Vector2 { float x, y; };

struct Vec10 { void FUN_00425990(); };            // 0x00425990
struct Sub24 { void thunk_00926640(); };          // 0x00926640
struct Alloc { void* PopChunk(); char AddCore(int b, int c); };
struct WStr {
    void FUN_004feb50();                          // 0x004feb50
    void FUN_00442365(const wchar_t* first, const wchar_t* last); // 0x00423650 (assign)
    void Assign(const wchar_t* s);
};
struct Owner { void Destroy(); };

// @ 0x004fddb0
int MaxIndex(const float* p)
{
    if (p[0] <= p[1]) {
        if (p[1] <= p[2])
            return 2;
        return 1;
    } else {
        if (p[0] <= p[2])
            return 2;
        return 0;
    }
}

// @ 0x004fde40
void* Alloc::PopChunk()
{
    Alloc* alloc = this;
    for (;;) {
        if (*(void**)((char*)alloc + 0x10)) {
            void* c = *(void**)((char*)alloc + 0x10);
            *(void**)((char*)alloc + 0x10) = *(void**)c;
            return c;
        }
        if (!AddCore(0, 0))
            return 0;
    }
}

// @ 0x004fe7f0
Vector2* AddVec2(Vector2* out, const Vector2* a, const Vector2* b)
{
    Vector2 r;
    r.x = a->x + b->x;
    r.y = a->y + b->y;
    Vector2 s = r;
    *out = s;
    return out;
}

// @ 0x004fdd60
void Owner::Destroy()
{
    void* self = this;
    ((Sub24*)((char*)self + 0x24))->thunk_00926640();
    for (uint32_t i = *(uint32_t*)((char*)self + 0x10); i < *(uint32_t*)((char*)self + 0x14); i += 4) {
    }
    ((Vec10*)((char*)self + 0x10))->FUN_00425990();
}

// @ 0x004fe860
void WStr::Assign(const wchar_t* s)
{
    void* self = this;
    FUN_004feb50();
    *(char*)((char*)self + 0x3c) = 0;
    const wchar_t* end = s;
    while (*end)
        ++end;
    FUN_00442365(s, end);
}

// ---------------------------------------------------------------------------
// 16-byte-element vector, triangle-mesh queries and the editor transform record.
// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };

struct Elem16 { uint32_t mData[4]; };

struct ElemVector {
    Elem16* mpBegin;        // +0x00
    Elem16* mpEnd;          // +0x04
    Elem16* mpCapacity;     // +0x08
    uint32_t mAllocator;    // +0x0c
    void Insert(Elem16* position, const Elem16& value);
};

void* __cdecl EASTL_Allocate(void* allocator, uint32_t size, uint32_t alignment, int flags); // 0x0042dee0
void __cdecl FreeRawBlock(void* block);                                                       // 0x00f47380
Elem16* __cdecl CopyElems(Elem16* first, Elem16* last, Elem16* dst);                          // 0x004fdcb0

struct AABB {
    Vec3 mMin;              // +0x00
    Vec3 mMax;              // +0x0c
};

struct BVHNode {
    Vec3 mMin;              // +0x00
    Vec3 mMax;              // +0x0c
    union {
        const uint32_t* mpLeafIndices;  // +0x18, leaf
        BVHNode* mpChild0;              // +0x18, internal
    };
    union {
        uint32_t mLeafCount;            // +0x1c, leaf
        BVHNode* mpChild1;              // +0x1c, internal
    };
};

struct MeshBVH {
    uint8_t mPad00[8];      // +0x00
    Vec3* mpVertices;       // +0x08
    const uint32_t* mpIndices; // +0x0c
    uint8_t mPad10[0x34];   // +0x10
    float mBestDistSq;      // +0x44
    uint32_t mBestTri;      // +0x48
    float mBestU;           // +0x4c
    float mBestV;           // +0x50
    void SearchNearest(const BVHNode* node, const Vec3* point);
    void SearchRay(const BVHNode* node, const Vec3* origin, const Vec3* dir, char cull);
};

float __cdecl DistPointBoxSq(const Vec3* point, const Vec3* lo, const Vec3* hi);              // 0x005056d0
float __cdecl SqrDistancePointTriangle(const Vec3* point, const Vec3* v0, const Vec3* v1,
                                       const Vec3* v2, float* u, float* v);                   // 0x00505850
bool __cdecl RayIntersectsBox(Vec3 origin, Vec3 direction, const AABB* box);                  // 0x00503c50
bool __cdecl RayTri(const Vec3* origin, const Vec3* direction, const Vec3* v0, const Vec3* v1,
                    const Vec3* v2, float* t, float* u, float* v, char cull);                 // 0x00505170

struct Mat33 {
    float m[9];
    Mat33() {}
    Mat33(const Mat33& other);                                                            // 0x0041cb40
};
Vec3 __cdecl operator*(const Vec3& v, const Mat33& m);                                    // 0x0041daf0
Vec3* __cdecl ScaleInPlace(Vec3* v, const float* s);                                      // 0x0041dba0
Mat33 __cdecl Matrix33FromAxisAngle(const Vec3* axis, float angle);                       // 0x00453b20

extern const float kRealZero;       // 0x01485378  _HK_REAL_ZERO
extern const float kRealOne;        // 0x01485720  _HK_REAL_ONE
extern const float kDegToRad;       // 0x013f1258
extern const float kMinScale;       // 0x013ec480
extern const float kMaxScale;       // 0x013eb8a0
extern const float kSweepAngle;     // 0x013ec4d4
extern const float kHalfSpread;     // 0x013f1290

struct TransformDesc {
    uint32_t mId;               // +0x00
    uint8_t  mFlag04;           // +0x04
    uint8_t  mPad05[3];         // +0x05
    uint32_t mField08;          // +0x08
    uint32_t mOwnerId;          // +0x0c
    float    mPrimaryScale;     // +0x10
    float    mOffset14;         // +0x14
    float    mOffset18;         // +0x18
    uint32_t mOffset1c;         // +0x1c
    float    mMinScale;         // +0x20
    float    mOffset24;         // +0x24
    float    mMaxScale;         // +0x28
    uint32_t mPad2c;            // +0x2c
    double   mZero30;           // +0x30
    uint32_t mUseAngle;         // +0x38
    float    mAngle;            // +0x3c
    float    mSecondaryScale;   // +0x40
    uint32_t mMode;             // +0x44
    float    mSweep;            // +0x48
    float    mOffset4c;         // +0x4c
    float    mHalfSpread;       // +0x50
    uint8_t  mFlag54;           // +0x54
    uint8_t  mPad55[3];         // +0x55
    float    mSecondaryAngle;   // +0x58
    float    mField5c;          // +0x5c
    Vec3     mAxis60;           // +0x60
    Vec3     mAxis6c;           // +0x6c
    Vec3     mAxis78;           // +0x78
    float    mField84;          // +0x84
    uint8_t  mPad88;            // +0x88
    uint8_t  mFlag89;           // +0x89
    uint8_t  mPad8a[2];         // +0x8a
    Vec3     mOrigin8c;         // +0x8c
    float    mField98;          // +0x98
    uint32_t mField9c;          // +0x9c
    uint32_t mFielda0;          // +0xa0
    uint32_t mFielda4;          // +0xa4

    TransformDesc(uint32_t ownerId);
    void ComputeFrame(const Vec3* axis, const Vec3* refA, const Vec3* refB, int scaleMode,
                      Vec3* outA, Vec3* outB, char applySecondary);
};

// @ 0x004fd9a0
void ElemVector::Insert(Elem16* position, const Elem16& value)
{
    if (mpEnd == mpCapacity) {
        uint32_t count = (uint32_t)(mpEnd - mpBegin);
        uint32_t newCapacity = count != 0 ? count * 2 : 1;
        Elem16* newBegin = newCapacity != 0
            ? (Elem16*)EASTL_Allocate(&mAllocator, newCapacity * 16, 4, 0)
            : 0;
        Elem16* inserted = CopyElems(mpBegin, position, newBegin);
        if (inserted != 0) {
            inserted->mData[0] = value.mData[0];
            inserted->mData[1] = value.mData[1];
            inserted->mData[2] = value.mData[2];
            inserted->mData[3] = value.mData[3];
        }
        Elem16* newEnd = CopyElems(position, mpEnd, inserted + 1);
        if (mpBegin != 0 && *(uint32_t*)((char*)mpBegin - 4) != 0)
            FreeRawBlock(mpBegin);
        mpBegin = newBegin;
        mpEnd = newEnd;
        mpCapacity = (Elem16*)((char*)newBegin + newCapacity * 16);
    } else {
        const Elem16* source = &value;
        if (position <= source && source < mpEnd)
            source = source + 1;
        if (mpEnd != 0) {
            mpEnd->mData[0] = (mpEnd - 1)->mData[0];
            mpEnd->mData[1] = (mpEnd - 1)->mData[1];
            mpEnd->mData[2] = (mpEnd - 1)->mData[2];
            mpEnd->mData[3] = (mpEnd - 1)->mData[3];
        }
        Elem16* dst = mpEnd;
        Elem16* src = mpEnd - 1;
        while (src != position) {
            --src;
            --dst;
            dst->mData[0] = src->mData[0];
            dst->mData[1] = src->mData[1];
            dst->mData[2] = src->mData[2];
            dst->mData[3] = src->mData[3];
        }
        position->mData[0] = source->mData[0];
        position->mData[1] = source->mData[1];
        position->mData[2] = source->mData[2];
        position->mData[3] = source->mData[3];
        ++mpEnd;
    }
}

// @ 0x004fdcb0
Elem16* __cdecl CopyElems(Elem16* first, Elem16* last, Elem16* dst)
{
    Elem16* firstStart = first;
    Elem16* dstStart = dst;
    while (first != last) {
        if (dst != 0) {
            dst->mData[0] = first->mData[0];
            dst->mData[1] = first->mData[1];
            dst->mData[2] = first->mData[2];
            dst->mData[3] = first->mData[3];
        }
        ++first;
        ++dst;
    }
    Elem16* result = dst;
    Elem16* q = dstStart;
    for (Elem16* p = firstStart; p != last; ++p, ++q) {
    }
    return result;
}

// @ 0x004fde90
void MeshBVH::SearchNearest(const BVHNode* node, const Vec3* point)
{
    if ((node->mLeafCount & 0xffffff00u) != 0) {
        const BVHNode* child0 = node->mpChild0;
        const BVHNode* child1 = node->mpChild1;
        float dist0 = DistPointBoxSq(point, &child0->mMin, &child0->mMax);
        float dist1 = DistPointBoxSq(point, &child1->mMin, &child1->mMax);
        if (dist1 <= dist0) {
            if (mBestDistSq > dist1) {
                SearchNearest(child1, point);
                if (mBestDistSq > dist0)
                    SearchNearest(child0, point);
            }
        } else {
            if (mBestDistSq > dist0) {
                SearchNearest(child0, point);
                if (mBestDistSq > dist1)
                    SearchNearest(child1, point);
            }
        }
    } else {
        uint32_t i = 0;
        uint32_t count = node->mLeafCount;
        for (; i < count; ++i) {
            uint32_t triangle = node->mpLeafIndices[i];
            float u;
            float v;
            float distance = SqrDistancePointTriangle(point,
                &mpVertices[mpIndices[triangle]],
                &mpVertices[mpIndices[triangle + 1]],
                &mpVertices[mpIndices[triangle + 2]], &u, &v);
            if (mBestDistSq > distance) {
                mBestDistSq = distance;
                mBestTri = triangle;
                mBestU = u;
                mBestV = v;
            }
        }
    }
}

// @ 0x004fe070
void MeshBVH::SearchRay(const BVHNode* node, const Vec3* origin, const Vec3* dir, char cull)
{
    if ((node->mLeafCount & 0xffffff00u) != 0) {
        if (RayIntersectsBox(*origin, *dir, (const AABB*)node->mpChild0))
            SearchRay(node->mpChild0, origin, dir, cull);
        if (RayIntersectsBox(*origin, *dir, (const AABB*)node->mpChild1))
            SearchRay(node->mpChild1, origin, dir, cull);
    } else {
        uint32_t i = 0;
        uint32_t count = node->mLeafCount;
        for (; i < count; ++i) {
            uint32_t triangle = node->mpLeafIndices[i];
            float t;
            float u;
            float v;
            if (RayTri(origin, dir, &mpVertices[mpIndices[triangle]],
                       &mpVertices[mpIndices[triangle + 1]],
                       &mpVertices[mpIndices[triangle + 2]], &t, &u, &v, cull)
                && t >= kRealZero && mBestDistSq > t) {
                mBestDistSq = t;
                mBestTri = triangle;
                mBestU = u;
                mBestV = v;
            }
        }
    }
}

// @ 0x004fe2a0
TransformDesc::TransformDesc(uint32_t ownerId)
{
    mId = 0;
    mFlag04 = 0;
    mField08 = 0;
    mOwnerId = ownerId;
    mPrimaryScale = kRealOne;
    mOffset14 = kRealZero;
    mOffset18 = kRealZero;
    mOffset1c = 0;
    mMinScale = kMinScale;
    mOffset24 = kRealZero;
    mMaxScale = kMaxScale;
    mZero30 = 0.0;
    mUseAngle = 0;
    mAngle = kRealZero;
    mSecondaryScale = kRealOne;
    mMode = 0;
    mSweep = kSweepAngle;
    mOffset4c = kRealZero;
    mHalfSpread = kHalfSpread;
    mFlag54 = 0;
    mSecondaryAngle = kRealZero;
    mField5c = kRealOne;
    mAxis60.x = kRealOne;
    mAxis60.y = kRealOne;
    mAxis60.z = kRealOne;
    mAxis6c.x = kRealOne;
    mAxis6c.y = kRealOne;
    mAxis6c.z = kRealOne;
    mAxis78.x = kRealOne;
    mAxis78.y = kRealOne;
    mAxis78.z = kRealOne;
    mField84 = kRealOne;
    mFlag89 = 0;
    mOrigin8c.x = kRealZero;
    mOrigin8c.y = kRealZero;
    mOrigin8c.z = kRealZero;
    mField98 = kRealOne;
    mField9c = 0;
    mFielda0 = 0;
    mFielda4 = 0;
}

// @ 0x004fe510
void TransformDesc::ComputeFrame(const Vec3* axis, const Vec3* refA, const Vec3* refB, int scaleMode,
                                 Vec3* outA, Vec3* outB, char applySecondary)
{
    float angle = kRealZero;
    if (mUseAngle == 0)
        angle = mAngle;
    float radians = angle * kDegToRad;
    Mat33 generated = Matrix33FromAxisAngle(axis, radians);
    Mat33 rotation = generated;
    Vec3 rotatedB = *refB * rotation;
    *outB = rotatedB;
    Vec3 rotatedA = *refA * rotation;
    *outA = rotatedA;
    if (applySecondary != 0) {
        Mat33 secondaryGenerated = Matrix33FromAxisAngle(outA, mSecondaryAngle);
        Mat33 secondary = secondaryGenerated;
        Vec3 twisted = *outB * secondary;
        *outB = twisted;
    }
    if (scaleMode == 1) {
        float scale = mPrimaryScale * mSecondaryScale;
        ScaleInPlace(outA, &scale);
        ScaleInPlace(outB, &mPrimaryScale);
    } else if (scaleMode == 2) {
        float inverse = kRealOne / (mPrimaryScale * mSecondaryScale);
        ScaleInPlace(outA, &inverse);
        float inverse2 = kRealOne / mPrimaryScale;
        ScaleInPlace(outB, &inverse2);
    }
}
