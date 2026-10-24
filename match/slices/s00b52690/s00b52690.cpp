// Slice s00b52690 -- 0x00b52690, 1892 bytes (__cdecl, 7 stack args).
//
// Puts a spatial object (`obj`) back on the planet surface: it (1) re-orients the object on the
// terrain according to `orientMode` (1 surface orientation, 2 pitched surface orientation, 3 surface
// normal orientation), (2) lets the sibling routine 0x00b523e0 sync the Havok body `body`, (3) works
// out the lowest point of the body's shape in the surface frame (shape AABB under the rotation
// surface-orientation^-1 * body rotation, plus the rotated center of the object's local extents),
// (4) projects the body position onto the planet surface (0x00b82df0, three bool-like options) and
// (5) sweeps a temporary hkSimpleShapePhantom (same shape and transform as the body) along the
// radial line from (distance - height offset) to (distance - 0.05) with setPositionAndLinearCast.  If
// the cast hits, the body is moved to the hit position, its velocities are zeroed and 0x00b52230
// finishes the sync.  `useCenterDistance` replaces the surface distance by the body's distance to
// the planet center.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (SSE scalar math; sqrt chains in x87).
#include "types.h"

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef float hkReal;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define VFN(p, off) ((*(void***)(p))[(off) / 4])

// ---- math -----------------------------------------------------------------------------------------
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct BoundingBox { Vector3 lower, upper; };

// ---- Havok 3.1 (only what this function needs) ----------------------------------------------------
struct __declspec(align(16)) hkVector4 {
    float x, y, z, w;
    hkVector4() {}
    hkVector4(const hkVector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    hkVector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
    void operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
};
class hkQuaternion { public: float x, y, z, w; };
struct __declspec(align(16)) hkRotation {
    hkVector4 m_col0, m_col1, m_col2;
    hkRotation() {}
    void set(const hkQuaternion& q);                                         // 0x010824a0
};
struct __declspec(align(16)) hkTransform {
    hkRotation m_rotation;
    hkVector4 m_translation;
    hkTransform() {}
};
class hkAabb { public: hkVector4 m_min, m_max; };

class hkMemory {
public:
    PV4
    virtual void* allocateChunk(int nbytes, int cl);                         // 0x10
    virtual void freeChunk(void* p, int align, int nbytes);                  // 0x14
    static hkMemory* s_instance;                                             // 0x016e4178
    static hkMemory& getInstance() { return *s_instance; }
};

class hkReferencedObject {
public:
    virtual ~hkReferencedObject();                                           // 0x00
    u16 m_memSizeAndFlags;                                                   // 0x04
    u16 m_referenceCount;                                                    // 0x06
    void removeReference()
    {
        if (m_memSizeAndFlags != 0 && --m_referenceCount == 0)
            ((void (__thiscall*)(hkReferencedObject*, int))VFN(this, 0))(this, 1);
    }
};

class hkShape : public hkReferencedObject {
public:
    PV2
    virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;   // 0x0c
};

class hkWorldObject : public hkReferencedObject {
public:
    void* m_world;                                                           // 0x08
    void* m_userData;                                                        // 0x0c
    void removeReference();                                                  // 0x0109ae60 (out of line here)
};

class hkMotion {
public:
    PV8 PV8 PV4 PV2                                                          // slots 0..21
    virtual void setAngularVelocity(const hkVector4& v);                     // 0x58
    virtual void setLinearVelocity(const hkVector4& v);                      // 0x5c
    u8 pad[0x80 - 4];                                                        // motion state: transform at +0x10 (position +0x40)
    hkQuaternion m_rotation;                                                 // 0x80
};

extern const hkVector4 hkVector4_zero;                                       // 0x016e42d0
extern const hkVector4 kHalf;                                                // 0x0149d620 (-0.5 x4)

class hkRigidBody : public hkWorldObject {
public:
    u8 pad10[0x1c - 0x10];
    hkShape* m_shape;                                                        // 0x1c (collidable's shape)
    u8 pad20[0x58 - 0x20];
    hkMotion* m_motion;                                                      // 0x58
    void setPosition(const hkVector4& p);                                    // 0x01087820
    void activate();                                                         // 0x01088ae0
    __forceinline void setLinearVelocity(const hkVector4& v)
    {
        activate();
        m_motion->setLinearVelocity(v);
    }
    __forceinline void setAngularVelocity(const hkVector4& v)
    {
        activate();
        m_motion->setAngularVelocity(v);
    }
};

struct hkLinearCastInput {
    hkVector4 m_to;
    hkReal m_maxExtraPenetration;
    hkReal m_startPointTolerance;
    hkLinearCastInput() {}
};

struct hkRootCdPoint {
    hkVector4 m_position;
    hkVector4 m_separatingNormal;   // w = distance
    const void* m_rootCollidableA;
    unsigned m_shapeKeyA;
    const void* m_rootCollidableB;
    unsigned m_shapeKeyB;
};

class hkCdPointCollector {
public:
    hkReal m_earlyOutDistance;
    virtual ~hkCdPointCollector() {}
    virtual void addCdPoint(const void* event) = 0;
    virtual void reset();
};
class hkClosestCdPointCollector : public hkCdPointCollector {   // vtable 0x013ef52c
public:
    hkRootCdPoint m_hitPoint;                                    // +0x10
    __forceinline hkClosestCdPointCollector()
    {
        m_hitPoint.m_rootCollidableA = 0;
        m_hitPoint.m_separatingNormal.w = 3.40282e+038f;
        m_earlyOutDistance = 3.40282e+038f;
    }
    virtual ~hkClosestCdPointCollector() {}
    virtual void addCdPoint(const void* event);
    virtual void reset();
    bool hasHit() const { return m_hitPoint.m_rootCollidableA != 0; }
};

class hkPhantom : public hkWorldObject {};
class hkSimpleShapePhantom : public hkPhantom {
public:
    void* operator new(size_t nbytes)
    {
        hkReferencedObject* b = (hkReferencedObject*)hkMemory::getInstance().allocateChunk((int)nbytes, 0x2e);
        b->m_memSizeAndFlags = (u16)nbytes;
        return b;
    }
    void operator delete(void*) {}
    hkSimpleShapePhantom(const hkShape* shape, const hkTransform& transform, u32 collisionFilterInfo);   // 0x0108c750
    PV8 PV2 PV                                                               // slots 1..11 (own)
    virtual void setPositionAndLinearCast(const hkVector4& position, const hkLinearCastInput& input,
                                          hkCdPointCollector& castCollector,
                                          hkCdPointCollector* startCollector);   // 0x30
    PV                                                                       // slot 13 (0x34)
    virtual void collect(void* out);                                         // slot 14 (0x38)
    void setPosition(const hkVector4* position, float tolerance);            // 0x0108dbb0
    void* construct(const hkShape* shape, const hkTransform& transform, u32 collisionFilterInfo);
    u8 pad[0x130 - 0x10];
};

class hkWorld {
public:
    hkPhantom* addPhantom(hkPhantom* phantom);                               // 0x01083320
    void removePhantom(hkPhantom* phantom);                                  // 0x01083400
};
extern hkWorld* g_hkWorld;                                                   // 0x0167ecd0

// ---- Spore ----------------------------------------------------------------------------------------
class cSpatialObject {
public:
    PV8 PV2 PV
    virtual const Vector3& GetPosition();                                    // 0x2c
    virtual const Quaternion& GetOrientation();                              // 0x30
    virtual float GetScale();                                                // 0x34
    virtual void SetPosition(const Vector3& v);                              // 0x38
    virtual void SetOrientation(const Quaternion& q);                        // 0x3c
    PV8 PV2
    virtual const BoundingBox& GetLocalExtents();                            // 0x68
    virtual int slot6C(int);                                                 // 0x6c
    virtual float GetBoundingRadius();                                       // 0x70
};

class cPlanetModel {
public:
    u8 pad[0x20];
    Quaternion* BuildSurfaceOrientation(Quaternion* out, const Vector3* pos);                      // 0x00b7f190
    Quaternion* BuildSurfaceOrientation(Quaternion* out, const Vector3* pos, const Quaternion* orient);   // 0x00b7f1f0
    Quaternion* BuildPitchedSurfaceOrientation(Quaternion* out, const Vector3* pos,
                                               const Quaternion* orient, float pitch);             // 0x00b7f2b0
    Quaternion* BuildSurfaceNormalOrientation(Quaternion* out, const Vector3* pos,
                                              const Quaternion* orient, float pitch);              // 0x00b7f320
    // options are bool-like dwords tested as bytes by the callee
    Vector3* ProjectToSurface(Vector3* out, const Vector3* pos, int a, int b, int c, int d);       // 0x00b82df0
};
cPlanetModel* PlanetModel();                                                 // 0x00b3d350
void SyncBodyBefore(cSpatialObject* obj, hkRigidBody* body);                 // 0x00b523e0
void SyncBodyAfter(cSpatialObject* obj, hkRigidBody* body);                  // 0x00b52230

// @ 0x00b52690
void PlaceObjectOnSurface(cSpatialObject* obj, hkRigidBody* body, bool useCenterDistance, int orientMode,
                          int optA, int optB, int optC)
{
    cPlanetModel* planet = PlanetModel();

    Quaternion tmp1, tmp2, tmp3;
    const Quaternion* r;
    switch (orientMode) {
    case 3:
        r = planet->BuildSurfaceNormalOrientation(&tmp3, &obj->GetPosition(), &obj->GetOrientation(),
                                                  obj->GetBoundingRadius());
        break;
    case 2:
        r = planet->BuildPitchedSurfaceOrientation(&tmp2, &obj->GetPosition(), &obj->GetOrientation(),
                                                   obj->GetBoundingRadius());
        break;
    case 1:
        r = planet->BuildSurfaceOrientation(&tmp1, &obj->GetPosition(), &obj->GetOrientation());
        break;
    default:
        goto sync;
    }
    {
        Quaternion q = *r;
        obj->SetOrientation(q);
    }
sync:
    SyncBodyBefore(obj, body);

    hkMotion* motion = body->m_motion;

    // rotation of the body relative to the surface orientation at its position
    Quaternion surfTmp;
    Quaternion* sq = planet->BuildSurfaceOrientation(&surfTmp, (const Vector3*)((char*)motion + 0x40));
    float ax = sq->x, ay = sq->y, az = sq->z, aw = sq->w;
    motion = body->m_motion;
    hkQuaternion rel;
    rel.w = ((aw * motion->m_rotation.w + motion->m_rotation.y * ay) + motion->m_rotation.x * ax) +
            az * motion->m_rotation.z;
    rel.x = (motion->m_rotation.x * aw + (az * motion->m_rotation.y - ay * motion->m_rotation.z)) -
            motion->m_rotation.w * ax;
    rel.y = (aw * motion->m_rotation.y + (motion->m_rotation.z * ax - az * motion->m_rotation.x)) -
            ay * motion->m_rotation.w;
    rel.z = (aw * motion->m_rotation.z + (ay * motion->m_rotation.x - motion->m_rotation.y * ax)) -
            az * motion->m_rotation.w;

    hkTransform tx;
    tx.m_rotation.m_col0 = hkVector4(1.0f, 0.0f, 0.0f, 0.0f);
    tx.m_rotation.m_col1 = hkVector4(0.0f, 1.0f, 0.0f, 0.0f);
    tx.m_rotation.m_col2 = hkVector4(0.0f, 0.0f, 1.0f, 0.0f);
    tx.m_translation = hkVector4(0.0f, 0.0f, 0.0f, 0.0f);
    tx.m_rotation.set(rel);

    hkAabb aabb;
    body->m_shape->getAabb(tx, 0.0f, aabb);

    // lowest point of the shape: AABB minimum plus the rotated center of the local extents
    const BoundingBox* ext = &obj->GetLocalExtents();
    float cx = (ext->upper.x + ext->lower.x) * 0.5f;
    float cy = (ext->upper.y + ext->lower.y) * 0.5f;
    float cz = (ext->upper.z + ext->lower.z) * 0.5f;
    hkVector4 k = kHalf;
    float dot = (cz * rel.z + cy * rel.y) + cx * rel.x;
    float rotatedZ = ((dot * rel.z + (rel.w * rel.w + k.z) * cz) + (cy * rel.x - rel.y * cx) * rel.w) * 2.0f;
    float heightOffset = aabb.m_min.z + rotatedZ;

    Vector3 up;
    planet->ProjectToSurface(&up, (const Vector3*)((char*)body->m_motion + 0x40), optA, optB, optC, 0);
    float dist = (float)sqrt((double)up.y * up.y + (double)up.z * up.z + (double)up.x * up.x);
    obj->GetBoundingRadius();
    float inv = 1.0f / dist;
    float nx = inv * up.x;
    float ny = up.y * inv;
    float nz = up.z * inv;
    float nw = inv * 0.0f;
    if (useCenterDistance) {
        hkMotion* m = body->m_motion;
        const float* p = (const float*)((char*)m + 0x40);
        dist = (float)sqrt((double)p[0] * p[0] + (double)p[1] * p[1] + (double)p[2] * p[2]);
    }
    float d1 = dist - heightOffset;
    float d2 = dist - 0.05f;
    hkVector4 from(nx * d1, ny * d1, nz * d1, nw * d1);
    hkVector4 to(nx * d2, ny * d2, nz * d2, nw * d2);

    hkSimpleShapePhantom* phantom =
        new hkSimpleShapePhantom(body->m_shape, *(const hkTransform*)((char*)body->m_motion + 0x10), 0xc);
    g_hkWorld->addPhantom(phantom);
    phantom->removeReference();

    hkLinearCastInput input;
    input.m_to = to;
    input.m_maxExtraPenetration = 0.05f;
    input.m_startPointTolerance = 0.05f;
    hkClosestCdPointCollector collector;
    phantom->setPositionAndLinearCast(from, input, collector, 0);
    if (collector.hasHit()) {
        float t = collector.m_hitPoint.m_separatingNormal.w;
        float s = 1.0f - t;
        hkVector4 hit;
        hit.x = t * to.x + s * from.x;
        hit.y = t * to.y + s * from.y;
        hit.z = t * to.z + s * from.z;
        hit.w = t * to.w + s * from.w;
        body->setPosition(hit);
        SyncBodyAfter(obj, body);
        body->setLinearVelocity(hkVector4_zero);
        body->setAngularVelocity(hkVector4_zero);
    }
    ((hkWorld*)phantom->m_world)->removePhantom(phantom);
}

// ===================================================================================================
// eastl hashtables: bucket array at +4, bucket count at +8 (the end iterator is buckets[count]).
// ===================================================================================================
struct HNode {
    HNode* mpNext;          // +0x00
    u32    mValue;          // +0x04
};

struct HIter {              // 8-byte iterator used by the u32 -> T tables
    HNode* mpNode;          // +0x00
    void*  mpBucket;        // +0x04
};

struct KeyIter {            // 12-byte iterator used by the Key -> T table
    HNode* mpNode;          // +0x00
    void*  mpBucket;        // +0x04
    u8     mbInserted;      // +0x08
    u8     mPad[3];
};

struct HashTable {
    u32     mf0;            // +0x00
    HNode** mpBuckets;      // +0x04
    u32     mnBucket;       // +0x08
    void   find(HIter* out, const u32* key);              // 0x00645ed0
    HIter* find2(HIter* out, const u32* key);             // 0x00b41b30
    void   erase(HIter* out, HIter it);                   // 0x00b51640
    int    GetValue14c8(u32 key);                         // 0x00b532f0
};

struct Key4 { u32 a, b, c, d; };

struct KeyTable {
    u32     mf0;            // +0x00
    HNode** mpBuckets;      // +0x04
    u32     mnBucket;       // +0x08
    void find(KeyIter* out, const void* key);             // 0x00833840
    void insert(KeyIter* out, const void* key, u32 tag);  // 0x00b51930
    int  GetTextureInstance(const Key4* key);             // 0x00b533a0
};

struct RBTree {
    void InsertNode(void** out, void* parent, const u32* key, u8 flag);   // 0x00b53700
};
struct CollectorOps {
    void*  mpVtable;        // +0x00
    void*  mf4;             // +0x04
    void*  mpBegin;         // +0x08
    u32    mnSize;          // +0x0c
    int    mnCapacity;      // +0x10
    u32 capacity() const { return (u32)mnCapacity & 0x3fffffffu; }
    void* Destroy(u8 flags);                                             // 0x00b53790
};

struct ObjLike {
    void dtorA();           // 0x00aef2f0
    void dtorB();           // 0x00aefae0
};
void __cdecl FreeMem(void* p);                                           // 0x00f47380
void* __cdecl AllocMem(int size, const char* name, int a, int b, const char* file, int line);
                                                                         // 0x00f473a0
void __cdecl PairCleanup(void* key, void* value);                        // 0x00b4f6d0
void __cdecl RBTreeInsert(void* node, void* parent, void* header, int right);   // 0x009216a0

struct HKThreadMemory {
    void deallocateBlock(void* p, int nbytes, int align);                // 0x0107db10
};
extern u32 g_tlsIndex;                                                   // 0x016e4174
extern void* (__stdcall* g_TlsGetValue)(u32);                            // 0x013cc2bc

// @ 0x00b532b0
void* GetTableValue(void* key)
{
    HashTable* t = (HashTable*)0x0167ed58;
    HIter it;
    u32 k = (u32)key;
    t->find(&it, &k);
    HNode* end = t->mpBuckets[t->mnBucket];
    if (it.mpNode != end)
        return (void*)it.mpNode->mValue;
    return 0;
}

// @ 0x00b532f0
int HashTable::GetValue14c8(u32 key)
{
    HashTable* t = (HashTable*)((char*)this + 0x14c8);
    HIter it;
    u32 k = key;
    HIter* p = t->find2(&it, &k);
    if (p->mpNode != t->mpBuckets[t->mnBucket])
        return (int)((char*)p->mpNode + 4);
    return 0;
}

// @ 0x00b533a0
int KeyTable::GetTextureInstance(const Key4* key)
{
    KeyIter it;
    find(&it, key);
    if (it.mpNode == mpBuckets[mnBucket]) {
        Key4 pair = { key->a, key->b, key->c, 0 };
        ((u8*)&key)[0] = 0;
        insert(&it, &pair, (u32)key);
    }
    return (int)((char*)it.mpNode + 0xc);
}

// @ 0x00b530e0
void UnregisterCell(void* key, int kind)
{
    HIter it;

    ((HashTable*)0x01682a48)->find(&it, (const u32*)&key);
    if (it.mpNode != ((HashTable*)0x01682a48)->mpBuckets[((HashTable*)0x01682a48)->mnBucket]) {
        void* v = (void*)it.mpNode->mValue;
        ((u8*)v)[0x130] = 1;
        ((HashTable*)0x01682a48)->erase(&it, it);
        ((hkWorld*)*(void**)((char*)v + 8))->removePhantom((hkPhantom*)v);
    }

    ((HashTable*)0x016852e8)->find(&it, (const u32*)&key);
    if (it.mpNode != ((HashTable*)0x016852e8)->mpBuckets[((HashTable*)0x016852e8)->mnBucket]) {
        void* v = (void*)it.mpNode->mValue;
        ((HashTable*)0x016852e8)->erase(&it, it);
        if (v)
            ((hkWorld*)*(void**)((char*)v + 8))->removePhantom((hkPhantom*)v);
    }

    if (kind == 0) {
        ((HashTable*)0x016801a8)->find(&it, (const u32*)&key);
        if (it.mpNode != ((HashTable*)0x016801a8)->mpBuckets[((HashTable*)0x016801a8)->mnBucket]) {
            void* v = (void*)it.mpNode->mValue;
            ((HashTable*)0x016801a8)->erase(&it, it);
            PairCleanup(key, v);
        }
    }
    else {
        ((HashTable*)0x0167ed58)->find(&it, (const u32*)&key);
        if (it.mpNode != ((HashTable*)0x0167ed58)->mpBuckets[((HashTable*)0x0167ed58)->mnBucket]) {
            void* v = (void*)it.mpNode->mValue;
            ((HashTable*)0x0167ed58)->erase(&it, it);
            if (v) {
                ((ObjLike*)v)->dtorA();
                ((ObjLike*)v)->dtorB();
                FreeMem(v);
            }
        }
    }

    ((HashTable*)0x016815f8)->find(&it, (const u32*)&key);
    if (it.mpNode != ((HashTable*)0x016815f8)->mpBuckets[((HashTable*)0x016815f8)->mnBucket]) {
        void* v = (void*)it.mpNode->mValue;
        ((HashTable*)0x016815f8)->erase(&it, it);
        if (v)
            ((hkWorld*)*(void**)((char*)v + 8))->removePhantom((hkPhantom*)v);
    }
}

// @ 0x00b535d0
struct Item12 { u32 a, b, c; };
struct Vec12 {
    void* mpBegin;          // +0x00
    void* mpEnd;            // +0x04
    void* mpCap;            // +0x08
    void Insert(Item12* pos, const Item12* value);                        // 0x00b535d0
};
Item12* __cdecl Copy12(Item12* first, Item12* last, Item12* dest);       // 0x00a11310

void Vec12::Insert(Item12* pos, const Item12* value)
{
    Item12* end = (Item12*)mpEnd;
    if (end != (Item12*)mpCap) {
        const Item12* val = value;
        if (pos <= value && value < end)
            val = value + 1;
        end->a = end[-1].a;
        end->b = end[-1].b;
        end->c = end[-1].c;
        Item12* dst = (Item12*)mpEnd;
        Item12* last = dst - 1;
        while (last != pos)
            *--dst = *--last;
        *pos = *val;
        mpEnd = (char*)mpEnd + 0xc;
        return;
    }

    int n = (int)((char*)end - (char*)mpBegin) / 0xc;
    n = (n == 0) ? 1 : n * 2;
    Item12* mem;
    if (n != 0)
        mem = (Item12*)AllocMem(n * 0xc, "Simulator", 0, 0,
                                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                 0xd1);
    else
        mem = 0;
    Item12* at = Copy12((Item12*)mpBegin, pos, mem);
    if (at != 0) {
        at->a = value->a;
        at->b = value->b;
        at->c = value->c;
    }
    Item12* newEnd = Copy12(pos, (Item12*)mpEnd, at + 1);
    void* old = mpBegin;
    if (old != 0 && *(int*)((char*)old - 4) != 0)
        FreeMem(old);
    mpBegin = mem;
    mpEnd = newEnd;
    mpCap = (char*)mem + n * 0xc;
}

// @ 0x00b53700
void RBTree::InsertNode(void** out, void* parent, const u32* key, u8 flag)
{
    void** outp = out;
    int right = (flag == 0 && parent != (char*)this + 4 &&
                 *(const int*)key >= *(int*)((char*)parent + 0x10)) ? 1 : 0;
    void* node = *(void**)((char*)this + 0x18);
    if (node != 0)
        *(void**)((char*)this + 0x18) = *(void**)node;
    else {
        int size = *(int*)((char*)this + 0x28);
        node = AllocMem(size, "Simulator", 0, 0,
                        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                        0xd1);
    }
    if ((char*)node + 0x10 != 0)
        *(u32*)((char*)node + 0x10) = *key;
    RBTreeInsert(node, parent, (char*)this + 4, right);
    ++*(u32*)((char*)this + 0x14);
    *outp = node;
}

// @ 0x00b53790
void* CollectorOps::Destroy(u8 flags)
{
    *(void**)this = (void*)0x0146144c;
    if (mnCapacity >= 0) {
        void* tls = g_TlsGetValue(g_tlsIndex);
        ((HKThreadMemory*)tls)->deallocateBlock(mpBegin, capacity() << 4, 0x14);
    }
    *(void**)this = (void*)0x013ef534;
    if (flags & 1) {
        hkMemory* mem = hkMemory::s_instance;
        mem->freeChunk(this, 8, 0x1c);
    }
    return this;
}

// ===================================================================================================
// Contact collector used by the sweep below (0x14-byte header followed by 16 inline 16-byte points).
// ===================================================================================================
class HkContactCollector {
public:
    void* mpVtable;         // +0x00
    u8    mbFlag;           // +0x04
    u8    mPad[3];
    u8*   mpBegin;          // +0x08
    u32   mnSize;           // +0x0c
    u32   mnCapacity;       // +0x10
    u8    mInline[0x100];   // +0x14

    HkContactCollector()
    {
        mpBegin = mInline;
        mpVtable = (void*)0x0146144c;
        mnCapacity = 0x80000010;
        mnSize = 0;
        mbFlag = 0;
    }
    ~HkContactCollector()
    {
        int c = (int)mnCapacity;
        mpVtable = (void*)0x0146144c;
        if (c >= 0) {
            void* tls = g_TlsGetValue(g_tlsIndex);
            ((HKThreadMemory*)tls)->deallocateBlock(mpBegin, (c & 0x3fffffff) << 4, 0x14);
        }
    }
    void reset()
    {
        mnSize = 0;
        mbFlag = 0;
    }
};

struct HkShapeObj : public hkReferencedObject {
    u32   mf8;              // +0x08
    float mConvexRadius;    // +0x0c
    hkVector4 mHalfExtents; // +0x10
    void* construct(const hkVector4* half, float radius);                // 0x010c05d0
};

extern float g_convexRadius;                                             // 0x015ba104

// @ 0x00b52e00
void SweepShapeOnSurface(const Vector3* extents, const hkQuaternion* orientation, void* physObj,
                         const Vector3* positions, u32* results, int count)
{
    hkVector4 half(extents->x * 0.5f, extents->y * 0.5f, extents->z * 0.5f, 0.0f);

    HkShapeObj* shape = (HkShapeObj*)hkMemory::getInstance().allocateChunk(0x20, 0x24);
    shape->m_memSizeAndFlags = 0x20;
    float convexRadius = g_convexRadius;
    shape->construct(&half, convexRadius);

    hkTransform transform;
    transform.m_translation = hkVector4(positions[0].x, positions[0].y, positions[0].z, 0.0f);
    hkQuaternion q = *orientation;
    transform.m_rotation.set(q);

    hkSimpleShapePhantom* phantom =
        (hkSimpleShapePhantom*)hkMemory::getInstance().allocateChunk(0x130, 0x2e);
    phantom->m_memSizeAndFlags = 0x130;
    phantom->construct((hkShape*)shape, transform, 6);
    shape->removeReference();
    g_hkWorld->addPhantom(phantom);
    phantom->removeReference();

    ((void (__thiscall*)(void*))VFN(physObj, 0xac))(physObj);
    int id = ((int (__thiscall*)(void*, int))VFN(physObj, 0xb8))(physObj, 0x17f243b);

    HkContactCollector collector;
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            hkVector4 v(positions[i].x, positions[i].y, positions[i].z, 0.0f);
            phantom->setPosition(&v, 0.0f);
            results[i] = 0;
            collector.reset();
            phantom->collect(&collector);
            u8* e = collector.mpBegin;
            u8* eEnd = collector.mpBegin + collector.mnSize * 0x10;
            for (; e != eEnd; e += 0x10) {
                int* o = *(int**)(e + 8);
                if (*(char*)((char*)o + 0x18) == 1) {
                    int* t = (int*)((char*)o + *(int*)((char*)o + 0x10));
                    if (t != 0) {
                        int v2 = *(int*)((char*)t + 0xc);
                        if (v2 != 0 && v2 == id) {
                            results[i] = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    if (phantom)
        ((hkWorld*)*(void**)((char*)phantom + 8))->removePhantom(phantom);
}
