// Slice s005bb5a0 -- one 2.9 KB /O2 editor function (cSPEditorManipulationStacking region).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: locals with dtors but no EH frame).
//
// 0x005bb5a0 moves a dragged block onto a stack: it remembers the block's position and
// orientation, pins it, linear-casts its Havok body along the mouse ray, and walks the sorted
// hits looking for a body whose top lies flush (within gStackingHeightTolerance) under the
// dragged block's bottom. If one is found the block is placed there (projected onto the drag
// plane for low camera angles); otherwise the position/orientation are restored and
// FindStackingTarget (0x005ba320), then the free-move fallback (0x005b9b40), are tried. Finally
// the block is re-parented to the block it now rests on and turned to face away from it.
//
// Names: the PDB candidate for this function is SP::cSPEditorManipulationStacking::MoveBlockStacking
// (caller-scored). Member/callee names other than PDB/Havok ones are descriptive.
// Havok 3.1 layouts: match/include/havok31/hkReflectedClasses.h. Types are shared in spirit with
// the sibling slice s005ba320 (FindStackingTarget).

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
    cSPVector3 operator+(const cSPVector3& v) const { return cSPVector3(x + v.x, y + v.y, z + v.z); }
    cSPVector3 operator-(const cSPVector3& v) const { return cSPVector3(x - v.x, y - v.y, z - v.z); }
    cSPVector3 operator*(float f) const { return cSPVector3(x * f, y * f, z * f); }
    float Dot(const cSPVector3& v) const { return x * v.x + y * v.y + z * v.z; }
    float LengthSquared() const { return x * x + y * y + z * z; }
    float Length() const { return (float)sqrt(LengthSquared()); }
    cSPVector3 Normalized() const
    {
        float len = Length();
        float inv = 1.0f / len;
        return cSPVector3(inv * x, inv * y, inv * z);
    }
};

struct cSPMatrix3 {
    cSPVector3 m[3];
    cSPMatrix3(const cSPMatrix3& o);   // 0x0041cb40
};

extern cSPVector3 kSPUpAxis;            // 0x015ea68c
extern float gStackingHeightTolerance;  // 0x015134dc (0.05)
extern float gNoParentBottom;           // 0x015ea5a8
extern float gLowAngleCosine;           // 0x0151379c
extern float gStackRayLength;           // 0x015137a0

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
    void set(float a, float b, float c, float d = 0.0f) { x = a; y = b; z = c; w = d; }
    void setTransformedPos(const struct hkTransform& t, const hkVector4& v);         // 0x01081360
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

struct hkBool {
    char m_bool;
    hkBool(bool b) { m_bool = (char)b; }
    operator bool() const { return m_bool != 0; }
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
    hkBool hasHit() const { return m_hits.getSize() > 0; }
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
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    T& operator[](size_type n) { return mpBegin[n]; }
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

// ---------------------------------------------------------------------------
// Spore editor
// ---------------------------------------------------------------------------
namespace SP {

struct cSPEditorBlock;

struct cSPEditorPhysicsWorld {
    hkWorld* World();                   // 0x004b91c0
    void UpdateCollisionFilters();      // 0x004b9420
    void SetDefaultFloorFilter();       // 0x004b9470
    uint32_t pad00[3];
    hkRigidBody* mpFloorBody;           // +0xc
};

struct cSPEditorModel {
    cSPEditorPhysicsWorld* GetPhysicsWorld();   // 0x004ad450
    void NumberBlocks();                        // 0x004ad4e0
};

struct cSPEditorBlock {
    virtual void Dispose();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad04[9];
    cSPEditorModel* mEditorModel;   // +0x28
    uint32_t pad2c[4];
    int mUIState;                   // +0x3c
    uint32_t pad40[2];
    cSPVector3 mPosition;           // +0x48
    uint32_t pad54[21];
    cSPMatrix3 mOrientation;        // +0xa8
    uint32_t padcc[48];
    hkRigidBody* mpRigidBody;       // +0x18c
    uint32_t pad190[107];
    cSPEditorBlock* mParentBlock;   // +0x33c

    void SetPosition(const cSPVector3& pos, bool notify);      // 0x00448e90
    void SetOrientation(const cSPMatrix3& m, bool notify);     // 0x00449420
    void SetUIState(int state, bool a, bool b, bool c);        // 0x0043a5e0
    void AddChildBlock(cSPEditorBlock* child);                 // 0x00438700
    void RemoveChildBlock(cSPEditorBlock* child);              // 0x00438a40
    void PointAt(cSPVector3 dir, cSPVector3 pos);              // 0x00437b00
};

struct cViewer {
    void GetCameraLocationInfo(cSPVector3* pos, cSPVector3* dir, int a, int b);  // 0x007c3d30
};

struct cSPApp {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual cViewer* GetViewer();   // +0x58
};

cSPApp* App();   // 0x0067dd10

struct BlockList;

namespace EditorUtils {
cSPEditorBlock* PickBlockForPinning(cSPEditorBlock* block, BlockList& blocks, cSPVector3 origin,
                                    cSPVector3 dir, cSPVector3& outNormal, cSPVector3& outPos,
                                    bool& outIsPin, int* level);   // 0x004a4d60
}

void PrepareBlockForStacking(cSPEditorBlock* block, BlockList* pile, int a, int b, int c);  // 0x004a6690
cSPEditorBlock* FindBlockByRigidBody(cSPEditorModel* model, hkRigidBody* body);           // 0x004a4cf0

struct cSPPlane {
    cSPVector3 mNormal;
    float mD;
    cSPPlane(const cSPVector3& normal, const cSPVector3& point) : mNormal(normal), mD(-normal.Dot(point)) {}
};

struct cSPEditorManipulationStacking {
    uint32_t pad00[8];
    cSPEditorBlock* mStackParent;              // +0x20
    uint32_t pad24[6];
    cSPVector3 mMouseOffset;                   // +0x3c
    cSPVector3 mTargetPosition;                // +0x48
    uint32_t pad54[6];
    cSPVector3 mPlanePoint;                    // +0x6c
    cSPVector3 mPlaneNormal;                   // +0x78
    int mParentPreviousState;                  // +0x84

    hkRigidBody* FindStackingTarget(cSPEditorBlock* block, BlockList* pile, cSPVector3 rayOrigin,
                                    cSPVector3 rayDirection, cSPVector3* outPosition);   // 0x005ba320
    void MoveBlockFree(cSPEditorBlock* block, BlockList* pile, cSPVector3 rayOrigin,
                       cSPVector3 rayDirection, cSPVector3* outPosition);                // 0x005b9b40
    int MoveBlockStacking(cSPEditorBlock* block, BlockList* pile, cSPVector3 rayOrigin,
                          cSPVector3 rayDirection);
};

inline bool IsWithin(float a, float b, float tolerance) { return fabs(a - b) < tolerance; }

template <typename T> inline const T& max_alt(const T& a, const T& b) { return (a < b) ? b : a; }

// @ 0x005bb5a0
int cSPEditorManipulationStacking::MoveBlockStacking(cSPEditorBlock* block, BlockList* pile,
    cSPVector3 rayOrigin, cSPVector3 rayDirection)
{
    hkRigidBody* rb = block->mpRigidBody;
    if (rb == 0)
        return 0;

    hkAabb rbAabb;
    rb->getCollidable()->getShape()->getAabb(hkTransform::getIdentity(), 0.0f, rbAabb);
    cSPVector3 savedPosition(block->mPosition);
    cSPEditorModel* model = block->mEditorModel;
    cSPMatrix3 savedOrientation(block->mOrientation);

    cSPVector3 pinNormal;
    cSPVector3 pinPosition;
    cSPVector3 pickOrigin = rayOrigin - mMouseOffset;
    bool isPin = false;
    cSPEditorBlock* picked = EditorUtils::PickBlockForPinning(block, *pile, pickOrigin,
        rayDirection, pinNormal, pinPosition, isPin, 0);

    float bottom;
    if (block->mParentBlock)
        bottom = rb->getPosition()(2) + rbAabb.m_min(2);
    else
        bottom = gNoParentBottom;
    float pickedTop = 0.0f;
    if (picked && picked->mpRigidBody) {
        hkAabb pickedAabb;
        picked->mpRigidBody->getCollidable()->getShape()->getAabb(picked->mpRigidBody->getTransform(), 0.0f, pickedAabb);
        pickedTop = pickedAabb.m_max(2);
    }
    float minHeight = max_alt(bottom, pickedTop);

    model->NumberBlocks();
    PrepareBlockForStacking(block, pile, 0, 1, 1);
    model->GetPhysicsWorld()->UpdateCollisionFilters();

    hkLinearCastInput input;
    rb->setPosition(hkVector4(rayOrigin.x, rayOrigin.y, rayOrigin.z, 0.0f));
    cSPVector3 to = rayOrigin + rayDirection * gStackRayLength;
    input.m_to.set(to.x, to.y, to.z, 0.0f);
    hkAllCdPointCollector collector;
    model->GetPhysicsWorld()->World()->linearCast(rb->getCollidable(), input, collector);

    cSPVector3 cameraPosition;
    cSPVector3 cameraDirection;
    App()->GetViewer()->GetCameraLocationInfo(&cameraPosition, &cameraDirection, 0, 0);
    bool lowAngle = fabs(kSPUpAxis.Dot(cameraDirection)) < gLowAngleCosine;

    model->GetPhysicsWorld()->SetDefaultFloorFilter();

    cSPEditorBlock* parent = 0;
    bool found = false;
    cSPVector3 finalPosition;
    hkVector4 localPos;
    if (collector.hasHit()) {
        collector.sortPoints();
        hkTransform rbTransform(rb->getTransform());
        eastl::vector<hkRigidBody*> visited;
        int numHits = collector.getHits().getSize();
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
            localPos.setTransformedInversePos(rbTransform, contactPos);

            float fraction = contact.getDistance();
            cSPVector3 castTo(input.m_to(0), input.m_to(1), input.m_to(2));
            cSPVector3 p = castTo * fraction + rayOrigin * (1.0f - fraction);

            hkAabb hitAabb;
            hitBody->getCollidable()->getShape()->getAabb(hkTransform::getIdentity(), 0.0f, hitAabb);
            float blockBottom = rbAabb.m_min(2) + p.z;
            float hitTop = hitBody->getPosition()(2) + hitAabb.m_max(2);
            float rise = hitTop - minHeight;
            if (fabs(blockBottom - hitTop) < gStackingHeightTolerance && rise < gStackingHeightTolerance) {
                finalPosition = p;
                cSPVector3 position(finalPosition);
                found = true;
                if (lowAngle) {
                    cSPPlane plane(mPlaneNormal, mPlanePoint);
                    float denom = plane.mNormal.Dot(rayDirection);
                    if (denom != 0.0f) {
                        float t = -((plane.mNormal.Dot(finalPosition) + plane.mD) / denom);
                        if (t >= 0.0f) {
                            position.x = rayDirection.x * t + finalPosition.x;
                            position.y = rayDirection.y * t + finalPosition.y;
                        }
                    }
                }
                block->SetPosition(position, true);
                if (model->GetPhysicsWorld()->mpFloorBody != hitBody)
                    parent = FindBlockByRigidBody(model, hitBody);
                if (parent == block)
                    parent = 0;
                mStackParent = parent;
                mTargetPosition = position;
                break;
            }
        }
    }

    if (!found) {
        block->SetPosition(savedPosition, true);
        block->SetOrientation(savedOrientation, true);
        hkRigidBody* target = FindStackingTarget(block, pile, rayOrigin, rayDirection, &finalPosition);
        if (target == 0) {
            block->SetPosition(savedPosition, true);
            block->SetOrientation(savedOrientation, true);
            MoveBlockFree(block, pile, rayOrigin, rayDirection, &finalPosition);
            parent = 0;
        } else {
            if (model->GetPhysicsWorld()->mpFloorBody != target)
                parent = FindBlockByRigidBody(model, target);
            if (parent == block)
                parent = 0;
        }
        block->SetPosition(finalPosition, true);
    }

    if (block->mParentBlock != parent) {
        if (block->mParentBlock) {
            block->mParentBlock->SetUIState(mParentPreviousState, true, false, true);
            block->mParentBlock->RemoveChildBlock(block);
        }
        if (parent) {
            mParentPreviousState = parent->mUIState;
            parent->SetUIState(2, true, false, true);
            parent->AddChildBlock(block);
        }
    }
    if (parent) {
        hkVector4 worldPos;
        worldPos.setTransformedPos(block->mpRigidBody->getTransform(), localPos);
        cSPVector3 d = cSPVector3(worldPos(0), worldPos(1), worldPos(2)) - block->mPosition;
        cSPVector3 dir = d.Normalized();
        if (dir.Length() > 0.5f)
            block->PointAt(dir, block->mPosition);
    }
    return 0;
}

} // namespace SP
