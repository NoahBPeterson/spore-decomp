// Slice s00b89a30: national-boundary builder (Simulator "NatlBounds").
// Walks every tile of a planet's ownership hash map and traces each owned edge around the
// planet surface, producing two smoothed point strips (ground and curve) that are handed to
// the cNatlBounds object.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>
#include <intrin.h>

#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

inline void* operator new(unsigned int, void* p) throw() { return p; }
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                         // 0xf473a0
void __cdecl operator_delete__(void* p);                                 // 0xf47380

// ---- math ----------------------------------------------------------------
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
    Vec3 operator+(const Vec3& b) const { return Vec3(x + b.x, y + b.y, z + b.z); }
    Vec3 operator-(const Vec3& b) const { return Vec3(x - b.x, y - b.y, z - b.z); }
    Vec3 operator*(float f) const { return Vec3(x * f, y * f, z * f); }
    float Dot(const Vec3& b) const { return x * b.x + y * b.y + z * b.z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    Vec3 Normalized() const { float inv = 1.0f / Length(); return Vec3(x * inv, y * inv, z * inv); }
};
inline Vec3 Cross(const Vec3& a, const Vec3& b)
{
    return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
// maxss/minss helper used throughout this module.
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
inline const float& Max(const float& a, const float& b) { return (a < b) ? b : a; }

// ---- EASTL vector (sp_vector_allocator) -------------------------------------
struct sp_vector_allocator { uint32_t mFlags; sp_vector_allocator() {} };

template <typename T>
struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; sp_vector_allocator mAllocator;
    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector() { if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin); }
    T* begin() { return mpBegin; }
    T& front() { return *mpBegin; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void reserve(uint32_t n);                                            // 0x473890
    void DoInsertValue(T* position, const T& value);                     // 0x4b5ad0
    T* erase(T* first, T* last)
    {
        T* position = first;
        for (T* p = last; p != mpEnd; ++p, ++position)
            *position = *p;
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

// ---- planet ----------------------------------------------------------------
struct cTerrainMapSet {
    char  pad00[0x34];
    float mRadius;      // +0x34
    float mMaxHeight;   // +0x38
    float mWaterHeight; // +0x3c
    float GetHeightAt(const Vec3* p);                                    // 0xf927c0
};
struct ISphere {
    virtual void a(); virtual void b(); virtual void c();
    virtual cTerrainMapSet* GetMap();                                    // slot 0xc
};
struct cPlanetModel {
    char     pad00[0x20];
    void*    mpSphere;     // +0x20
    ISphere* mpISphere;    // +0x24

    float GetWaterHeight()                                               // 0xb7e390
    {
        if (mpISphere != 0) {
            cTerrainMapSet* t = mpISphere->GetMap();
            return t->mWaterHeight * t->mMaxHeight + t->mRadius;
        }
        return 0.0f;
    }
    cTerrainMapSet* GetTerrain()
    {
        if (mpISphere != 0 && mpISphere->GetMap() != 0)
            return mpISphere->GetMap();
        return 0;
    }
    float GetRadius()                                                    // 0xb7e4d0
    {
        if (mpISphere != 0) {
            if (mpISphere->GetMap() != 0)
                return mpISphere->GetMap()->mRadius;
        }
        return 500.0f;
    }
    float GetHeightAt(const Vec3& p)
    {
        if (mpSphere != 0)
            return mpISphere->GetMap()->GetHeightAt(&p);
        return GetRadius();
    }
};
cPlanetModel* __cdecl SP_PlanetModel();                                  // 0xb3d350

struct cGameNounManager {
    void GetGameDataVector(void* a, void* b, void* c, void* d, void* e); // 0xb21340
};
cGameNounManager* __cdecl SP_NounManager();                              // 0xb3d300
void __cdecl FUN_00cd7d10();
void __cdecl FUN_00d3d420();
void __cdecl FUN_00acdff0();
void __cdecl FUN_00b1e500();
extern char DAT_018c43e8;

// ---- tile map ------------------------------------------------------------------
struct TileKey {
    int x, y, z;
    bool operator==(const TileKey& b) const { return x == b.x && y == b.y && z == b.z; }
};
struct TileNode {
    TileKey     mKey;        // +0x00
    Vec3        mPos;        // +0x0c
    signed char mLevel[4];   // +0x18 owner level per edge
    bool        mDone[4];    // +0x1c edge already traced
    TileNode*   mpNext;      // +0x20
};
struct TileIterator {
    TileNode*  mpNode;
    TileNode** mpBucket;
    TileIterator() {}
    TileIterator(const TileIterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
    explicit TileIterator(TileNode** pBucket) : mpNode(*pBucket), mpBucket(pBucket)
    {
        if (!mpNode)
            increment_bucket();
    }
    void increment_bucket()
    {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    void increment()
    {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
};
struct TileMap {
    uint32_t   mUnk0;
    TileNode** mpBucketArray;   // +4
    uint32_t   mnBucketCount;   // +8
    TileIterator find(const TileKey& k);                                 // 0xb83af0
    TileNode* end_node() const { return mpBucketArray[mnBucketCount]; }
};

void __cdecl FUN_00b7e220(uint32_t face, TileKey* key, int* dx, int* dy); // 0xb7e220 cube-map step

extern const signed char gDirX[4];   // 0x1465420 {-1, 0, 1, 0}
extern const signed char gDirY[4];   // 0x1465424 { 0,-1, 0, 1}

// ---- NatlBounds -------------------------------------------------------------
struct cRefCounted {
    int mnRefCount;
    cRefCounted() { _InterlockedExchange((long*)&mnRefCount, 0); }
    virtual ~cRefCounted() {}
    void Release()
    {
        if (_InterlockedExchangeAdd((long*)&mnRefCount, -1) - 1 == 0) {
            _InterlockedExchange((long*)&mnRefCount, 1);
            delete this;
        }
    }
};
struct BoundsVec { void* mpBegin; void* mpEnd; void* mpCapacity; sp_vector_allocator mAllocator;
                   BoundsVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {} };
struct cNatlBounds : public cRefCounted {
    uint32_t  mUnk8;      // +0x08
    BoundsVec mStrips0;   // +0x0c
    BoundsVec mStrips1;   // +0x20
    BoundsVec mLevels;    // +0x34
    uint32_t  mUnk44;     // +0x44
    cNatlBounds() : mUnk8(0) {}
    ~cNatlBounds();
    void AddBoundary(const Vec3* ground, const Vec3* curve, int count, int level); // 0xb899b0
};

template <typename T>
struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr& operator=(T* pObject);                                // 0x8fd240
    T* operator->() const { return mpObject; }
    void reset0()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
};

struct cNatlBoundsBuilder {
    char  pad00[0xc];
    bool  mbBuilt;                         // +0x0c
    char  pad0d[0x24 - 0x0d];
    intrusive_ptr<cNatlBounds> mpBounds;   // +0x24
    bool  mbEnabled;                       // +0x28

    void Build(TileMap* tiles);
};

// @ 0x00b89a30
void cNatlBoundsBuilder::Build(TileMap* tiles)
{
    cPlanetModel* planet = SP_PlanetModel();
    mpBounds.reset0();
    if (!mbEnabled)
        return;

    float water = planet->GetWaterHeight();
    planet->GetTerrain();

    vector<Vec3> ground;
    vector<Vec3> curve;
    curve.reserve(1000);
    ground.reserve(1000);
    cGameNounManager* nouns = SP_NounManager();
    nouns->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                        (void*)FUN_00acdff0, (void*)FUN_00b1e500, &DAT_018c43e8);
    mpBounds = new("Simulator/NatlBounds", 0, 0, 0, 0) cNatlBounds();

    for (TileIterator it(tiles->mpBucketArray); it.mpNode != tiles->end_node(); it.increment()) {
        TileNode* node = it.mpNode;
        for (int edge = 0; edge < 4; ++edge) {
            if (node->mDone[edge])
                continue;
            int level = node->mLevel[edge];
            if (level <= 0)
                continue;

            TileKey key = node->mKey;
            ground.clear();
            curve.clear();
            Vec3 p0 = node->mPos;
            Vec3 p1 = node->mPos;
            int dx = gDirX[edge];
            int dy = gDirY[edge];
            TileKey startKey;
            Vec3 prevCtrl;

            for (int i = 0; i <= 2000; ++i) {
                key.x += dx;
                key.y += dy;
                FUN_00b7e220(0x40, &key, &dx, &dy);
                TileIterator next = tiles->find(key);
                if (next.mpNode == tiles->end_node())
                    break;
                TileNode* n = next.mpNode;

                // Pick the outgoing edge: rotate away from edges on the same side.
                uint32_t dir = (dx + dy + (dx & 1) + ((dy & 1) + 1) * 2) & 3;
                if (n->mLevel[dir] == level) {
                    dir = (dir + 1) & 3;
                    if (n->mLevel[dir] == level) {
                        dir = (dir + 1) & 3;
                        if (n->mLevel[dir] == level)
                            dir = (dir + 1) & 3;
                    }
                } else {
                    dir = (dir - 1) & 3;
                    if (n->mLevel[(dir - 1) & 3] == level) {
                        dir = (dir - 1) & 3;
                        if (n->mLevel[(dir - 1) & 3] == level)
                            dir = (dir - 1) & 3;
                    }
                }
                n->mDone[dir] = true;
                Vec3 p2 = n->mPos;

                if (i > 0) {
                    Vec3 toNext = p2 - p1;
                    Vec3 toPrev = p0 - p1;
                    float cosA = Clamp(toPrev.Dot(toNext) / (toNext.Length() * toPrev.Length()),
                                       -1.0f, 0.999f);
                    Vec3 n0 = Cross(p0, p1).Normalized();
                    Vec3 n1 = Cross(p1, p2).Normalized();
                    float bend = sqrtf(2.0f / (1.0f - cosA));
                    Vec3 ctrl = (n1 + n0).Normalized() * 5.0f * bend + p1;

                    if (i > 1) {
                        Vec3 dPos = p1 - p0;
                        Vec3 dCtrl = ctrl - prevCtrl;
                        for (int j = 0; j < 3; ++j) {
                            float t = (float)j / 3.0f;
                            Vec3 a = dPos * t + p0;
                            float hA = Max(water, planet->GetHeightAt(a)) + 0.6f;
                            Vec3 b = dCtrl * t + prevCtrl;
                            float hB = Max(water, planet->GetHeightAt(b)) + 0.6f;
                            float h = hB * 0.6f + hA * 0.4f;
                            ground.push_back(a * (hA / a.Length()));
                            curve.push_back(b * (h / b.Length()));
                        }
                        if (key == startKey)
                            break;
                    } else if (i == 1) {
                        startKey = key;
                    }
                    prevCtrl = ctrl;
                }
                p0 = p1;
                p1 = p2;
                dx = gDirX[dir];
                dy = gDirY[dir];
            }

            ground.push_back(ground.front());
            curve.push_back(curve.front());
            mpBounds->AddBoundary(ground.begin(), curve.begin(), (int)ground.size(), level);
        }
    }
    mbBuilt = true;
}
