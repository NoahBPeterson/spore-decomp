// Slice s005ba320 -- one 4.7 KB /O2 editor function (cSPEditorManipulationStacking region).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: locals with dtors but no EH frame).
//
// 0x005ba320 picks the block a dragged block should be stacked on: for every block of the
// pile it intersects the mouse ray with the vertical plane through the candidate, scores the
// candidate by the screen-space (camera x) overlap of both bounding boxes, then linear-casts
// the dragged block's Havok body down onto the best hit and returns the body it lands on.
//
// Class/member names: `this` is SP::cSPEditorManipulationStacking (dev PDB: mBlock is an
// AutoRefCount<cSPEditorBlock> at +0x20; the retail Vector3 at +0x48 is taken to be
// mTargetPosition, since the only caller writes both right after this call).
// The method name FindStackingTarget and the callee names GetStackCandidates (0x4905d0) and
// PrepareBlockForStacking (0x4a6690) are descriptive, not from the PDB.
// Havok 3.1 layouts: match/include/havok31/hkReflectedClasses.h.
//
// Status: complete, not byte-exact. Call order, vtable slots and constants match the original
// one for one; the remaining differences are stack-slot packing and register choice (e.g. the
// original keeps `block` in ebx, and builds each hkAabb corner temp x-first).

#include "types.h"

typedef unsigned int size_type;
inline void* operator new(unsigned int, void* p) { return p; }
void __cdecl operator delete[](void* p);  // 0x00f47380

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(fabs, sqrt)

// ---------------------------------------------------------------------------
// math
// ---------------------------------------------------------------------------
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
    cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
    void Set(float fx, float fy, float fz) { x = fx; y = fy; z = fz; }
    cSPVector3 operator+(const cSPVector3& v) const { return cSPVector3(x + v.x, y + v.y, z + v.z); }
    cSPVector3 operator*(float f) const { return cSPVector3(x * f, y * f, z * f); }
    cSPVector3 operator-() const { return cSPVector3(-x, -y, -z); }
    float Dot(const cSPVector3& v) const { return x * v.x + y * v.y + z * v.z; }
};

extern cSPVector3 kSPUpAxis;   // 0x015ea68c
extern float gStackingHeightTolerance;  // 0x015134dc (0.05)

#define FLT_MAX_VALUE 3.402823466e+38F
#define FLT_MIN_VALUE 1.175494351e-38F
#define HK_ALIGN16 __declspec(align(16))
#define HK_REAL_MAX 3.40282e+38f
#define HK_REAL_EPSILON 1.192092896e-07F

struct HK_ALIGN16 hkVector4 {
    float x, y, z, w;
    hkVector4() {}
    hkVector4(float a, float b, float c, float d = 0.0f) : x(a), y(b), z(c), w(d) {}
    hkVector4(const hkVector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    float& operator()(int i) { return (&x)[i]; }
    const float& operator()(int i) const { return (&x)[i]; }
    void setTransformedInversePos(const struct hkTransform& t, const hkVector4& v);  // 0x010813d0
};

struct hkTransform {
    hkVector4 m_rotation[3];
    hkVector4 m_translation;
    static const hkTransform& getIdentity() { return s_identity; }
    static const hkTransform s_identity;   // 0x015b9b20
};

struct hkAabb {
    hkVector4 m_min;
    hkVector4 m_max;
};

// ---------------------------------------------------------------------------
// Havok physics
// ---------------------------------------------------------------------------
struct hkThreadMemory {
    void deallocateChunk(void* p, int nbytes, int cls);  // 0x0107db10
    static unsigned long s_threadMemoryInstance;          // 0x016e4174 (TLS index)
    static hkThreadMemory& getInstance() { return *static_cast<hkThreadMemory*>(TlsGetValue(s_threadMemoryInstance)); }
};

enum { HK_MEMORY_CLASS_COLLIDE = 0x14 };

template <typename T>
struct hkArray {
    enum { CAPACITY_MASK = 0x3fffffff, DONT_DEALLOCATE_FLAG = 0x80000000 };
    T* m_data;
    int m_size;
    int m_capacityAndFlags;
    int getSize() const { return m_size; }
    int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
    T& operator[](int i) { return m_data[i]; }
    ~hkArray()
    {
        if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
            hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * sizeof(T), HK_MEMORY_CLASS_COLLIDE);
    }
};

template <typename T, int N>
struct hkInplaceArray : hkArray<T> {
    T m_storage[N];
    hkInplaceArray()
    {
        this->m_data = m_storage;
        this->m_size = 0;
        this->m_capacityAndFlags = N | hkArray<T>::DONT_DEALLOCATE_FLAG;
    }
};

struct hkShape {
    virtual ~hkShape();
    virtual void calcStatistics(void* collector) const;
    virtual int getType() const;
    virtual void getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const;  // +0xc
    virtual float getMaximumProjection(const hkVector4& direction) const;                     // +0x10
};

struct hkCdBody {
    const hkShape* m_shape;
    unsigned int m_shapeKey;
    const void* m_motion;
    const hkCdBody* m_parent;
    const hkShape* getShape() const { return m_shape; }
};

struct hkCollidable : hkCdBody {
    int m_ownerOffset;               // +0x10
    unsigned int m_broadPhaseHandle[3];
    float m_allowedPenetrationDepth;
    void* getOwner() const { return (void*)((char*)this + m_ownerOffset); }
};

struct hkMotionState {
    hkTransform m_transform;
};

struct hkMotion {
    void* vtbl_;
    unsigned int m_memSizeAndRefCount;
    int m_solverData;
    unsigned int pad_;
    hkMotionState m_motionState;     // +0x10
};

struct hkRigidBody {
    void* vtbl_;                     // +0x0
    unsigned int m_memSizeAndRefCount;
    unsigned int m_world;
    unsigned int m_userData;
    char* m_name;
    unsigned int m_multithreadLock[2];
    hkCollidable m_collidable;       // +0x1c
    unsigned int m_collisionEntries[3];  // +0x40 hkArray
    unsigned int m_properties[3];
    hkMotion* m_motion;              // +0x58

    const hkCollidable* getCollidable() const { return &m_collidable; }
    const hkTransform& getTransform() const { return m_motion->m_motionState.m_transform; }
    const hkVector4& getPosition() const { return getTransform().m_translation; }
    void setPosition(const hkVector4& position);  // 0x01087820
};

struct hkContactPoint {
    hkVector4 m_position;
    hkVector4 m_separatingNormal;
    const hkVector4& getPosition() const { return m_position; }
    float getDistance() const { return m_separatingNormal.w; }
};

struct hkRootCdPoint {
    hkContactPoint m_contact;
    const hkCollidable* m_rootCollidableA;
    unsigned int m_shapeKeyA;
    const hkCollidable* m_rootCollidableB;
    unsigned int m_shapeKeyB;
};

struct hkCdPointCollector {
    hkCdPointCollector() { m_earlyOutDistance = HK_REAL_MAX; }
    virtual ~hkCdPointCollector() {}
    virtual void addCdPoint(const void* point) = 0;
    float m_earlyOutDistance;
};

struct hkAllCdPointCollector : hkCdPointCollector {
    hkAllCdPointCollector() {}
    virtual ~hkAllCdPointCollector() {}
    virtual void addCdPoint(const void* point);
    hkInplaceArray<hkRootCdPoint, 8> m_hits;     // +0x10
    hkArray<hkRootCdPoint>& getHits() { return m_hits; }
    void sortPoints();                            // 0x010c2570
};

struct hkLinearCastInput {
    hkVector4 m_to;
    float m_maxExtraPenetration;
    float m_startPointTolerance;
    hkLinearCastInput() : m_maxExtraPenetration(HK_REAL_EPSILON), m_startPointTolerance(HK_REAL_EPSILON) {}
};

struct hkWorld {
    void linearCast(const hkCollidable* collA, const hkLinearCastInput& input,
                    hkCdPointCollector& castCollector, hkCdPointCollector* startCollector = 0);  // 0x01082b90
};

// ---------------------------------------------------------------------------
// EASTL (retail sp_vector_allocator keeps a header word in front of each block)
// ---------------------------------------------------------------------------
namespace eastl {

struct sp_vector_allocator {
    const char* mpName;
    unsigned int mFlags;
    sp_vector_allocator() {}
    void deallocate(void* p, size_type)
    {
        if (((unsigned int*)p)[-1])
            delete[] (char*)p;
    }
};

template <typename T, typename Allocator = sp_vector_allocator>
struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase()
    {
        if (mpBegin)
            DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
    }
    void DoFree(T* p, size_type n) { mAllocator.deallocate(p, n * sizeof(T)); }
};

template <typename T, typename Allocator = sp_vector_allocator>
struct vector : VectorBase<T, Allocator> {
    using VectorBase<T, Allocator>::mpBegin;
    using VectorBase<T, Allocator>::mpEnd;
    using VectorBase<T, Allocator>::mpCapacity;

    vector() {}
    ~vector() { DoDestroyValues(mpBegin, mpEnd); }
    void DoDestroyValues(T* first, T* last)
    {
        for (; first < last; ++first)
            first->~T();
    }
    bool empty() const { return mpBegin == mpEnd; }
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    T& operator[](size_type n) { return mpBegin[n]; }
    void resize(size_type n);                              // 0x00473810 (vector<cSPVector3>)
    void DoInsertValue(T* position, const T& value);       // 0x00630b30 (pointer vectors)
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

} // namespace eastl

namespace EA {
template <typename T>
struct AutoRefCount {
    T* mpObject;
    ~AutoRefCount()
    {
        if (mpObject)
            mpObject->Release();
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
} // namespace EA

// ---------------------------------------------------------------------------
// Spore editor
// ---------------------------------------------------------------------------
namespace SP {

struct cSPPlane {
    cSPVector3 mNormal;
    float mD;
    cSPPlane(const cSPVector3& normal, const cSPVector3& point) : mNormal(normal), mD(-normal.Dot(point)) {}
};

struct cSPBoundingBox {
    cSPVector3 mMin;
    cSPVector3 mMax;
};

struct cSPEditorPhysicsWorld {
    void SetFloorFilter(bool enable);   // 0x004b9440
    hkWorld* World();                   // 0x004b91c0
};

struct cSPEditorModel {
    cSPEditorPhysicsWorld* GetPhysicsWorld();   // 0x004ad450
    void NumberBlocks();                        // 0x004ad4e0
    float GetGridSize();                        // 0x004adaa0 (returns +0x38)
};

struct cSPEditorBlock {
    virtual void Dispose();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad04[9];
    cSPEditorModel* mEditorModel;   // +0x28
    uint32_t pad2c[7];
    cSPVector3 mPosition;           // +0x48
    uint32_t pad54[78];
    hkRigidBody* mpRigidBody;       // +0x18c

    void GetBBox(cSPBoundingBox* box, int a, int b, int c);  // 0x0044ae00
};

struct cSPCamera {
    cSPVector3 WorldToProjection(const cSPVector3& p);  // 0x007c4180
};

struct cSPApp {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual cSPCamera* GetCamera();   // +0x58
};

cSPApp* App();   // 0x0067dd10

typedef eastl::vector<EA::AutoRefCount<cSPEditorBlock> > BlockList;

void GetStackCandidates(cSPEditorBlock* block, int mode, BlockList* out);              // 0x004905d0
void PrepareBlockForStacking(cSPEditorBlock* block, int mode, int a, int b, int c);   // 0x004a6690

struct cSPEditorManipulationStacking {
    uint32_t pad00[8];
    EA::AutoRefCount<cSPEditorBlock> mBlock;   // +0x20
    uint32_t pad24[9];
    cSPVector3 mTargetPosition;                // +0x48

    hkRigidBody* FindStackingTarget(cSPEditorBlock* block, int mode, cSPVector3 rayOrigin,
                                    cSPVector3 rayDirection, cSPVector3* outPosition);
};

inline void cSPBoundingBox_GetCorners(const cSPBoundingBox& box, cSPVector3* c)
{
    const cSPVector3& mn = box.mMin;
    const cSPVector3& mx = box.mMax;
    c[0].Set(mn.x, mn.y, mn.z);
    c[1].Set(mx.x, mn.y, mn.z);
    c[2].Set(mn.x, mx.y, mn.z);
    c[3].Set(mx.x, mx.y, mn.z);
    c[4].Set(mn.x, mn.y, mx.z);
    c[5].Set(mx.x, mn.y, mx.z);
    c[6].Set(mn.x, mx.y, mx.z);
    c[7].Set(mx.x, mx.y, mx.z);
}

__forceinline void GetAabbCorners(const hkAabb& aabb, cSPVector3* c)
{
    c[0] = cSPVector3(aabb.m_min(0), aabb.m_min(1), aabb.m_min(2));
    c[1] = cSPVector3(aabb.m_max(0), aabb.m_min(1), aabb.m_min(2));
    c[2] = cSPVector3(aabb.m_min(0), aabb.m_max(1), aabb.m_min(2));
    c[3] = cSPVector3(aabb.m_max(0), aabb.m_max(1), aabb.m_min(2));
    c[4] = cSPVector3(aabb.m_min(0), aabb.m_min(1), aabb.m_max(2));
    c[5] = cSPVector3(aabb.m_max(0), aabb.m_min(1), aabb.m_max(2));
    c[6] = cSPVector3(aabb.m_min(0), aabb.m_max(1), aabb.m_max(2));
    c[7] = cSPVector3(aabb.m_max(0), aabb.m_max(1), aabb.m_max(2));
}

template <typename T> inline const T& max_alt(const T& a, const T& b) { return (a < b) ? b : a; }
template <typename T> inline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }

// @ 0x005ba320
hkRigidBody* cSPEditorManipulationStacking::FindStackingTarget(cSPEditorBlock* block, int mode,
    cSPVector3 rayOrigin, cSPVector3 rayDirection, cSPVector3* outPosition)
{
    cSPEditorModel* pModel = block->mEditorModel;
    hkRigidBody* pBody = block->mpRigidBody;
    if (pBody == 0)
        return 0;

    // Screen-space x extent of the dragged block.
    hkAabb aabb;
    pBody->getCollidable()->getShape()->getAabb(pBody->getTransform(), 0.0f, aabb);
    cSPVector3 corners[8];
    GetAabbCorners(aabb, corners);
    float blockTop = aabb.m_max(2);
    float blockMinX = FLT_MAX_VALUE;
    float blockMaxX = FLT_MIN_VALUE;
    for (int i = 0; i < 8; ++i) {
        cSPVector3 p = App()->GetCamera()->WorldToProjection(corners[i]);
        if (blockMinX > p.x) blockMinX = p.x;
        if (p.x > blockMaxX) blockMaxX = p.x;
    }
    cSPVector3 blockScreenPos = App()->GetCamera()->WorldToProjection(block->mPosition);

    BlockList candidates;
    GetStackCandidates(block, mode, &candidates);
    int bestIndex = -1;
    if (!candidates.empty()) {
        int count = (int)candidates.size();
        cSPVector3 horizontal(rayDirection.x, rayDirection.y, 0.0f);
        eastl::vector<cSPVector3> hits;
        hits.resize(count);
        float bestScore = FLT_MAX_VALUE;
        for (int i = 0; i < count; ++i) {
            cSPEditorBlock* candidate = candidates[i];
            cSPVector3 position(candidate->mPosition);
            if (candidate == mBlock)
                position = mTargetPosition;

            // vertical plane through the candidate, facing the camera
            cSPPlane plane(-horizontal, position);
            float denom = plane.mNormal.Dot(rayDirection);
            if (denom == 0.0f)
                continue;
            float t = -((plane.mNormal.Dot(rayOrigin) + plane.mD) / denom);
            if (t >= 0.0f) {
                hits[i] = rayOrigin + rayDirection * t;
                cSPVector3& hit = hits[i];
                float dx = hit.x - block->mPosition.x;
                float dy = hit.y - block->mPosition.y;
                float distToBlock = (float)sqrt(dx * dx + dy * dy);

                cSPVector3 candCorners[8];
                float candTop;
                if (candidates[i]->mpRigidBody) {
                    hkRigidBody* body = candidates[i]->mpRigidBody;
                    hkAabb candAabb;
                    body->getCollidable()->getShape()->getAabb(body->getTransform(), 0.0f, candAabb);
                    GetAabbCorners(candAabb, candCorners);
                    candTop = candAabb.m_max(2);
                } else {
                    cSPBoundingBox box;
                    candidates[i]->GetBBox(&box, 0, 0, 0);
                    cSPBoundingBox_GetCorners(box, candCorners);
                    candTop = box.mMax.z;
                }
                float ex = hit.x - position.x;
                float ey = hit.y - position.y;
                float distToCandidate = (float)sqrt(ex * ex + ey * ey);
                float heightDiff = (float)fabs(candTop - blockTop);

                float minX = FLT_MAX_VALUE;
                float maxX = FLT_MIN_VALUE;
                for (int k = 0; k < 8; ++k) {
                    cSPVector3 p = App()->GetCamera()->WorldToProjection(candCorners[k]);
                    if (minX > p.x) minX = p.x;
                    if (p.x > maxX) maxX = p.x;
                }
                float overlap = maxX - minX + blockMaxX - blockMinX
                              - (max_alt(maxX, blockMaxX) - min_alt(minX, blockMinX));
                if (overlap > 0.0f) {
                    float score = (heightDiff + distToCandidate + distToBlock) / overlap;
                    if (bestScore > score) {
                        bestScore = score;
                        bestIndex = i;
                    }
                }
            }
        }

        if (bestIndex != -1) {
            cSPVector3* bestHit = &hits[bestIndex];
            cSPVector3 start(*bestHit);
            start.z = pModel->GetGridSize() * 0.05f + start.z;
            cSPVector3 down = -kSPUpAxis;
            cSPEditorModel* model = block->mEditorModel;
            model->NumberBlocks();
            hkRigidBody* rb = block->mpRigidBody;
            if (rb == 0)
                return 0;
            hkVector4 savedPosition(rb->getPosition());
            PrepareBlockForStacking(block, mode, 0, 1, 1);
            model->GetPhysicsWorld()->SetFloorFilter(true);

            hkLinearCastInput input;
            cSPVector3 to = start + down * 20.0f;
            input.m_to = hkVector4(to.x, to.y, to.z, 0.0f);
            rb->setPosition(hkVector4(start.x, start.y, start.z, 0.0f));
            rb->getCollidable()->getShape()->getMaximumProjection(hkVector4(0.0f, 0.0f, -1.0f, 0.0f));

            hkAllCdPointCollector collector;
            model->GetPhysicsWorld()->World()->linearCast(block->mpRigidBody->getCollidable(), input, collector);

            bool found = false;
            if (collector.getHits().getSize() > 0) {
                collector.sortPoints();
                hkRigidBody* foundBody = 0;
                cSPVector3 foundPosition;
                eastl::vector<hkRigidBody*> visited;
                int numHits = collector.getHits().getSize();
                hkAabb rbAabb;
                rb->getCollidable()->getShape()->getAabb(hkTransform::getIdentity(), 0.0f, rbAabb);
                hkTransform rbTransform(rb->getTransform());
                for (int i = 0; i < numHits; ++i) {
                    hkRootCdPoint& pt = collector.getHits()[i];
                    hkRigidBody* hitBody = (hkRigidBody*)pt.m_rootCollidableB->getOwner();
                    hkContactPoint contact(pt.m_contact);
                    int n = (int)visited.size();
                    int j;
                    for (j = 0; j < n; ++j)
                        if (visited[j] == hitBody)
                            break;
                    if (j < n)
                        continue;
                    visited.push_back(hitBody);

                    hkVector4 contactPos(contact.getPosition());
                    hkVector4 localPos;
                    localPos.setTransformedInversePos(rbTransform, contactPos);

                    float fraction = contact.getDistance();
                    cSPVector3 castTo(input.m_to(0), input.m_to(1), input.m_to(2));
                    cSPVector3 p = castTo * fraction + start * (1.0f - fraction);

                    hkAabb hitAabb;
                    hitBody->getCollidable()->getShape()->getAabb(hkTransform::getIdentity(), 0.0f, hitAabb);
                    if (fabs((rbAabb.m_min(2) + p.z) - (hitBody->getPosition()(2) + hitAabb.m_max(2)))
                        < gStackingHeightTolerance) {
                        float drop = bestHit->z - p.z;
                        float stackOffset = pModel->GetGridSize() * 0.05f;
                        if (drop < stackOffset * 3.0f) {
                            foundPosition = p;
                            foundBody = hitBody;
                            found = true;
                            break;
                        }
                    }
                }
                model->NumberBlocks();
                rb->setPosition(savedPosition);
                if (found && foundBody && foundBody != rb) {
                    *outPosition = foundPosition;
                    return foundBody;
                }
            }
        }
    }
    return 0;
}

} // namespace SP
