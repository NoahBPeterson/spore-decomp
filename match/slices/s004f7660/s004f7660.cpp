// Slice 0x004F7660..0x004F85AE: unoptimized module (/Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast, no EH):
//   - map<uint32_t, vector<Elem16>> node helpers: DoAllocateNode, DoNuke, node scalar deleting dtor
//   - eastl heap algorithms over ResourceMan::Key: make_heap, adjust_heap, promote_heap, sort_heap
//   - closest-triangle / ray-triangle searches over an indexed triangle list
//   - aligned block free, CPU SIMD level detection (inline asm)
//   - a 4-slot structure-of-arrays of spherical force fields
// ScratchSlots<N>() reproduces the unused stack slots that the original's inlined EASTL helpers
// left in each /Od frame (needed for byte-identical frame offsets).
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
extern "C" void* __cdecl memset(void* p, int c, size_t n);
extern "C" double __cdecl sqrt(double x);
#pragma intrinsic(sqrt)
inline float sqrtf(float x) { return (float)sqrt((double)x); }
// returns the float root widened to double: the float->double step is what makes cl spill/reload it
inline double Sqrt(float x) { return sqrtf(x); }

void* __cdecl EASTL_Allocate(void* alloc, size_t n, size_t align, size_t offset);  // 0x0042DEE0
void  __cdecl EASTL_allocator_deallocate(void* p);                                 // 0x00F47380

template <int N> inline void ScratchSlots() { uint32_t s[N]; }

struct sp_vector_allocator { const char* mpName; };

namespace EA { namespace ResourceMan {
struct Key {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};
inline bool operator<(const Key& a, const Key& b)
{
    if (a.mInstance != b.mInstance) return a.mInstance < b.mInstance;
    if (a.mGroup != b.mGroup) return a.mGroup < b.mGroup;
    return a.mType < b.mType;
}
} }
using EA::ResourceMan::Key;

// ---------------------------------------------------------------------------
// map<uint32_t, vector<Elem16>> nodes
// ---------------------------------------------------------------------------
struct Elem16 { uint32_t mData[4]; };

struct Elem16Vector {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCapacity;
    sp_vector_allocator mAllocator;
    uint32_t mExtra;

    Elem16Vector(const Elem16Vector& x);               // 0x004F6CC0
    ~Elem16Vector() {
        for (Elem16* p = mpBegin; p < mpEnd; ++p) {}
        ScratchSlots<3>();
        DoFreeBase();
    }
    void DoFreeBase();                                 // ~VectorBase, 0x00554B10
};

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
struct value_type {
    uint32_t first;
    Elem16Vector second;
};
struct Node : rbtree_node_base {
    value_type mValue;
};

struct UIntMap {
    uint32_t mCompare;
    rbtree_node_base mAnchor;
    size_t mnSize;
    sp_vector_allocator mAllocator;

    Node* DoAllocateNode(const value_type& value);
    void DoNuke(Node* pNode);

    inline void DoFreeNode(Node* pNode) {
        pNode->~Node();
        Deallocate(pNode);
    }
    static inline void Deallocate(void* p) { void* q = p; EASTL_allocator_deallocate(q); }
};

// @ 0x004F7660
Node* UIntMap::DoAllocateNode(const value_type& value)
{
    Node* const pNode = (Node*)EASTL_Allocate(&mAllocator, sizeof(Node), 4, 0);
    ::new(&pNode->mValue) value_type(value);
    ScratchSlots<12>();
    return pNode;
}

// @ 0x004F7B50
void UIntMap::DoNuke(Node* pNode)
{
    while (pNode) {
        DoNuke((Node*)pNode->mpNodeRight);
        Node* const pNodeLeft = (Node*)pNode->mpNodeLeft;
        DoFreeNode(pNode);
        pNode = pNodeLeft;
    }
}

// ---------------------------------------------------------------------------
// heap algorithms over Key
// ---------------------------------------------------------------------------
// @ 0x004F7A70
void promote_heap(Key* first, int topPosition, int position, Key value)
{
    for (int parentPosition = (position - 1) >> 1;
         (position > topPosition) && (*(first + parentPosition) < value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}

// @ 0x004F7890
void adjust_heap(Key* first, int topPosition, int heapSize, int position, Key value)
{
    int childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (*(first + childPosition) < *(first + (childPosition - 1)))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    promote_heap(first, topPosition, position, value);
    ScratchSlots<3>();
}

// @ 0x004F7800
void make_heap(Key* first, Key* last)
{
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            const Key temp(*(first + parentPosition));
            adjust_heap(first, parentPosition, heapSize, parentPosition, temp);
        } while (parentPosition != 0);
    }
}

inline void pop_heap(Key* first, Key* last)
{
    const Key tempBottom(*(last - 1));
    *(last - 1) = *first;
    adjust_heap(first, 0, (int)(last - first - 1), 0, tempBottom);
}

// @ 0x004F79D0
void sort_heap(Key* first, Key* last)
{
    for (; (last - first) > 1; --last)
        pop_heap(first, last);
}

// ---------------------------------------------------------------------------
// triangle searches
// ---------------------------------------------------------------------------
struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(const float& x_, const float& y_) : x(x_), y(y_) {}
};
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
Vector3 operator*(const float& s, const Vector3& v);           // 0x0041DE40
Vector3 operator+(const Vector3& a, const Vector3& b);         // 0x0041DC10

float DistanceSqPointTriangle(const Vector3& point, const Vector3& v0, const Vector3& v1, const Vector3& v2,
                              float* pU, float* pV);           // 0x00505850
bool IntersectRayTriangle(const Vector3& origin, const Vector3& direction, const Vector3& v0, const Vector3& v1,
                          const Vector3& v2, float* pT, float* pU, float* pV, bool bCullBackFaces);  // 0x00505170

// @ 0x004F7C00
bool IntersectRayTriangles(const char* pVertices, int stride, const uint32_t* pIndices, uint32_t triangleCount,
                           const Vector3& origin, const Vector3& direction, bool bCullBackFaces, bool bFirstHit,
                           uint32_t* pTriangleIndex, float* pT, Vector2* pBarycentric, Vector3* pPoint)
{
    uint32_t bestIndex = 0xFFFFFFFF;
    float minT = 3.402823466e+38F;
    Vector2 hitUV;
    for (uint32_t i = 0; i < triangleCount; ++i) {
        const Vector3& p1 = *(const Vector3*)(pVertices + pIndices[i * 3 + 0] * stride);
        const Vector3& p2 = *(const Vector3*)(pVertices + pIndices[i * 3 + 1] * stride);
        const Vector3& p3 = *(const Vector3*)(pVertices + pIndices[i * 3 + 2] * stride);
        float hitT, hitU, hitV;
        if (IntersectRayTriangle(origin, direction, p1, p2, p3, &hitT, &hitU, &hitV, bCullBackFaces) && (hitT >= 0.0f)) {
            if (hitT < minT) {
                minT = hitT;
                hitUV.x = hitU;
                hitUV.y = hitV;
                bestIndex = i;
            }
            if (bFirstHit)
                break;
        }
    }
    if (bestIndex == 0xFFFFFFFF) {
        return false;
    } else {
        if (pTriangleIndex)
            *pTriangleIndex = bestIndex;
        if (pBarycentric)
            *pBarycentric = Vector2(hitUV.x, hitUV.y);
        if (pT)
            *pT = minT;
        Vector3 bary;
        bary.x = hitUV.x;
        bary.y = hitUV.y;
        bary.z = 1.0f - bary.x - bary.y;
        if (pPoint) {
            const Vector3& p0 = *(const Vector3*)(pVertices + pIndices[bestIndex * 3 + 0] * stride);
            const Vector3& p1 = *(const Vector3*)(pVertices + pIndices[bestIndex * 3 + 1] * stride);
            const Vector3& p2 = *(const Vector3*)(pVertices + pIndices[bestIndex * 3 + 2] * stride);
            *pPoint = bary.z * p0 + bary.x * p1 + bary.y * p2;
        }
        return true;
    }
}

// @ 0x004F7E70
void FindClosestTriangle(const char* pVertices, int stride, const uint32_t* pIndices, uint32_t triangleCount,
                         const Vector3& point, float* pDistance, uint32_t* pTriangleIndex, Vector2* pBarycentric,
                         Vector3* pClosestPoint)
{
    uint32_t bestIndex = 0xFFFFFFFF;
    float bestDist = 3.402823466e+38F;   // squared distance
    Vector2 hitUV;
    for (uint32_t i = 0; i < triangleCount; ++i) {
        const Vector3& v0 = *(const Vector3*)(pVertices + pIndices[i * 3 + 0] * stride);
        const Vector3& v1 = *(const Vector3*)(pVertices + pIndices[i * 3 + 1] * stride);
        const Vector3& vert2 = *(const Vector3*)(pVertices + pIndices[i * 3 + 2] * stride);
        float hitU, hitV;
        const float dist = DistanceSqPointTriangle(point, v0, v1, vert2, &hitU, &hitV);
        if (dist < bestDist) {
            bestDist = dist;
            hitUV.x = hitU;
            hitUV.y = hitV;
            bestIndex = i;
        }
    }
    if (pDistance)
        *pDistance = (float)Sqrt(bestDist);
    if (pTriangleIndex)
        *pTriangleIndex = bestIndex;
    if (pBarycentric)
        *pBarycentric = Vector2(hitUV.x, hitUV.y);
    Vector3 bary;
    bary.x = hitUV.x;
    bary.y = hitUV.y;
    bary.z = 1.0f - bary.x - bary.y;
    if (pClosestPoint) {
        const Vector3& p0 = *(const Vector3*)(pVertices + pIndices[bestIndex * 3 + 0] * stride);
        const Vector3& p1 = *(const Vector3*)(pVertices + pIndices[bestIndex * 3 + 1] * stride);
        const Vector3& p2 = *(const Vector3*)(pVertices + pIndices[bestIndex * 3 + 2] * stride);
        *pClosestPoint = bary.z * p0 + bary.x * p1 + bary.y * p2;
    }
}

// ---------------------------------------------------------------------------
// aligned free, SIMD detection
// ---------------------------------------------------------------------------
struct AlignedHeader {
    uint32_t mField0;
    void* mpBlock;
    uint32_t mField8;
    uint32_t mFieldC;
};

// @ 0x004F80B0
void AlignedFree(void* p)
{
    if (p) {
        char* pHeader = (char*)p;
        pHeader -= sizeof(AlignedHeader);
        void* const pBlock = ((AlignedHeader*)pHeader)->mpBlock;
        ((AlignedHeader*)pHeader)->mFieldC = 0;
        ((AlignedHeader*)pHeader)->mField8 = 0;
        ((AlignedHeader*)pHeader)->mpBlock = 0;
        ((AlignedHeader*)pHeader)->mField0 = 0;
        UIntMap::Deallocate(pBlock);
    }
}

extern int g_SimdLevel;                                // 0x0150CAA0, initially -1
extern int g_SimdFlags;                                // 0x015DB058
extern unsigned char g_FxsaveArea[512];                // 0x015DB390

// @ 0x004F8120
int GetSimdLevel()
{
    if (g_SimdLevel < 0) {
        g_SimdFlags = 0;
        g_SimdLevel = 0;
        __asm {
            mov eax, 1
            cpuid
            test edx, 0x2000000
            jz done
            mov g_SimdLevel, 1
            test edx, 0x4000000
            jz done
            mov g_SimdLevel, 2
            test edx, 0x1000000
            jz done
            fxsave g_FxsaveArea
            mov eax, dword ptr [g_FxsaveArea + 0x1C]
            test eax, 0x40
            jz done
            mov g_SimdFlags, 0x40
        done:
        }
    }
    return g_SimdLevel;
}

// ---------------------------------------------------------------------------
// 4-slot structure-of-arrays of spherical force fields
// ---------------------------------------------------------------------------
struct FieldContribution {
    uint32_t mId;
    float mStrength;
};
struct FieldAccumulator {
    void Add(const FieldContribution& c);              // 0x005402C0
};

struct SphereFields {
    float mX[4];
    float mY[4];
    float mZ[4];
    float mRadiusSq[4];
    float mInvRadiusSq[4];
    float mStrength[4];
    float mScaledStrength[4];
    uint32_t mId[4];

    void Clear(int index);
    void Set(int index, const Vector3& position, float strength, float radius, uint32_t id);
    void SetRadius(int index, float radius);
    void Copy(int index, const SphereFields& other, int otherIndex);
    void Apply(const Vector3& position, FieldAccumulator* pAccumulator);
};

// @ 0x004F81A0
void SphereFields::Clear(int index)
{
    if (index == -1)
        memset(this, 0, sizeof(SphereFields));
    else {
        mX[index] = 0.0f;
        mY[index] = 0.0f;
        mZ[index] = 0.0f;
        mRadiusSq[index] = 0.0f;
        mInvRadiusSq[index] = 0.0f;
        mStrength[index] = 0.0f;
        mScaledStrength[index] = 0.0f;
        mId[index] = 0;
    }
}

// @ 0x004F8270
void SphereFields::Set(int index, const Vector3& position, float strength, float radius, uint32_t id)
{
    mX[index] = position[0];
    mY[index] = position[1];
    mZ[index] = position[2];
    mStrength[index] = strength;
    mId[index] = id;
    SetRadius(index, radius);
}

// @ 0x004F8300
void SphereFields::SetRadius(int index, float radius)
{
    const float radiusSq = radius * radius;
    mRadiusSq[index] = radiusSq;
    mInvRadiusSq[index] = 1.0f / radiusSq;
    mScaledStrength[index] = mStrength[index] * mInvRadiusSq[index];
}

// @ 0x004F8370
void SphereFields::Copy(int index, const SphereFields& other, int otherIndex)
{
    mX[index] = other.mX[otherIndex];
    mY[index] = other.mY[otherIndex];
    mZ[index] = other.mZ[otherIndex];
    mRadiusSq[index] = other.mRadiusSq[otherIndex];
    mInvRadiusSq[index] = other.mInvRadiusSq[otherIndex];
    mStrength[index] = other.mStrength[otherIndex];
    mScaledStrength[index] = other.mScaledStrength[otherIndex];
    mId[index] = other.mId[otherIndex];
}

// @ 0x004F8420
void SphereFields::Apply(const Vector3& position, FieldAccumulator* pAccumulator)
{
    for (int i = 0; i < 4; ++i) {
        if (mRadiusSq[i] != 0.0) {
            float distSq;
            float k;
            float t2;
            float strength;
            FieldContribution c;
            {
                const float vx = position[0] - mX[i];
                const float dy = position[1] - mY[i];
                const float dz = position[2] - mZ[i];
                distSq = vx * vx + dy * dy + dz * dz;
            }
            if (distSq < mRadiusSq[i]) {
                k = distSq * mInvRadiusSq[i] - 1.0f;   // falloff (r^2/R^2 - 1)
                t2 = k * k;
                strength = mStrength[i] * t2 * t2;
                if (strength > 0.0) {
                    c.mId = mId[i];
                    c.mStrength = strength;
                    pAccumulator->Add(c);
                }
            }
        }
    }
    ScratchSlots<2>();
}

// ---------------------------------------------------------------------------
struct FloatPair {
    uint32_t mPad[3];
    float mValue;
    float mNegValue;
    void Set(float value);
};

// @ 0x004F8580
void FloatPair::Set(float value)
{
    mNegValue = -value;
    mValue = value;
}

#pragma inline_depth(0)
// Not inlined: makes cl emit the node's scalar deleting destructor ??_GNode (0x004F7BA0) out of line.
void DestroyNode(Node* p) { p->~Node(); }
#pragma inline_depth()
