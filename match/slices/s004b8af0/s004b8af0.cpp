// Slice s004b8af0: SP::cSPEditorPhysicsWorld (the editor's Havok world wrapper) plus the Havok
// inline-class code and eastl::vector<AutoRefCount<cSPEditorModel>> instances it pulls in.
// Flags: /Od /Oy /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc). /Oy is what gives the
// aligned-locals functions (Init, CreateFloor) their `push ebp; mov ebp,esp; and esp,-16` esp-relative frame.
#include "types.h"

#pragma pack(push, 4)

template <int N> inline void ScratchSlots() { uint32_t s[N]; }

inline void* operator new(unsigned int, void* p) { return p; }

void EASTLFree(void* p);                                             // 0x00F47380

// ---------------------------------------------------------------------------
// Havok 4.x (only what this file needs)
// ---------------------------------------------------------------------------
typedef float hkReal;

class hkMemory {
public:
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void* allocateChunk(int nbytes, int cl);                 // 0x10
    virtual void deallocateChunk(void* p, int nbytes, int cl);       // 0x14
    static hkMemory* s_instance;                                     // 0x016E4178
    static hkMemory& getInstance() { return *s_instance; }
};

#define HK_DECLARE_CLASS_ALLOCATOR(CLS) \
    void* operator new(unsigned int nbytes) { \
        hkReferencedObject* b = static_cast<hkReferencedObject*>(hkMemory::getInstance().allocateChunk(nbytes, CLS)); \
        b->m_memSizeAndFlags = (unsigned short)nbytes; \
        return b; } \
    void operator delete(void* p) { \
        hkReferencedObject* b = static_cast<hkReferencedObject*>(p); \
        hkMemory::getInstance().deallocateChunk(p, b->m_memSizeAndFlags, CLS); }

class hkBaseObject {
public:
    virtual ~hkBaseObject() {}
};

// @ 0x4b8ef0  hkReferencedObject::`scalar deleting destructor' (implicit)
class hkReferencedObject : public hkBaseObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x12)
    unsigned short m_memSizeAndFlags;           // +0x4
    short m_referenceCount;                     // +0x6
    hkReferencedObject() : m_referenceCount(1) {}
    virtual ~hkReferencedObject() {}
    // Havok's HK_FORCE_INLINE: a plain inline containing `delete this` is never inlined by cl at /Ob1
    __forceinline void removeReference()
    {
        if (m_memSizeAndFlags != 0) {
            --m_referenceCount;
            if (m_referenceCount == 0)
                delete this;
        }
    }
};

class hkBool {
public:
    char m_bool;
    hkBool() {}
    hkBool(bool b) { m_bool = (char)b; }
    hkBool& operator=(bool e) { m_bool = (char)e; return *this; }
};

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    hkVector4() {}
    hkVector4(hkReal a, hkReal b, hkReal c, hkReal d = 0.0f) { x = a; y = b; z = c; w = d; }
    void operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    void set(hkReal a, hkReal b, hkReal c, hkReal d = 0.0f) { x = a; y = b; z = c; w = d; }
};

class hkCollidableCollidableFilter { public: virtual ~hkCollidableCollidableFilter() {} virtual void isCollisionEnabled() = 0; };
class hkShapeCollectionFilter { public: virtual ~hkShapeCollectionFilter() {} virtual void isCollisionEnabled2() = 0; };
class hkRayShapeCollectionFilter { public: virtual ~hkRayShapeCollectionFilter() {} virtual void isCollisionEnabled3() = 0; };
class hkRayCollidableFilter { public: virtual ~hkRayCollidableFilter() {} virtual void isCollisionEnabled4() = 0; };

// @ 0x4b9010  hkCollisionFilter::hkCollisionFilter (implicit, emitted out of line)
// @ 0x4b90c0  hkCollisionFilter::`scalar deleting destructor' (implicit)
class hkCollisionFilter : public hkReferencedObject, public hkCollidableCollidableFilter,
                          public hkShapeCollectionFilter, public hkRayShapeCollectionFilter,
                          public hkRayCollidableFilter {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x24)
};

namespace SP {
class SPEditorCollisionFilter : public hkCollisionFilter {
public:
    virtual void isCollisionEnabled();
    virtual void isCollisionEnabled2();
    virtual void isCollisionEnabled3();
    virtual void isCollisionEnabled4();
};
}

// @ 0x4b8f50  hkWorldCinfo::`scalar deleting destructor'
class hkWorldCinfo : public hkReferencedObject {
public:
    char pad08[0x10 - 0x8];
    hkVector4 m_gravity;                        // +0x10
    char pad20[0xa0 - 0x20];
    hkWorldCinfo();                                                  // 0x010880E0
    virtual ~hkWorldCinfo() {}
    void setupSolverInfo(int st);                                    // 0x01087FD0
    void setBroadPhaseWorldSize(hkReal size);                        // 0x010881D0
};

class hkCollisionDispatcher;
struct hkAgentRegisterUtil { static void registerAllAgents(hkCollisionDispatcher* dis); };  // 0x010C25A0

class hkShape : public hkReferencedObject { public: int m_userData; };
class hkConvexShape : public hkShape { public: hkReal m_radius; };           // +0xc
class hkBoxShape : public hkConvexShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x24)
    hkVector4 m_halfExtents;                    // +0x10
    hkBoxShape(const hkVector4& halfExtents, hkReal radius);        // 0x010C05D0
};

struct hkTypedBroadPhaseHandle { int m_id; char m_type, m_ownerOffset; unsigned short m_objectQualityType; unsigned int m_collisionFilterInfo; };
class hkCollidable {
public:
    char pad00[0x14];
    hkTypedBroadPhaseHandle m_broadPhaseHandle; // +0x14
    hkReal m_allowedPenetrationDepth;           // +0x20
    void setCollisionFilterInfo(unsigned int info) { m_broadPhaseHandle.m_collisionFilterInfo = info; }
};
struct hkMaterial { signed char m_responseType; hkReal m_friction; hkReal m_restitution; };

class hkWorld;
class hkWorldObject : public hkReferencedObject {
public:
    hkWorld* m_world;                           // +0x8
    void* m_userData;                           // +0xc
    char* m_name;                               // +0x10
    uint32_t m_multithreadLock[2];              // +0x14
    hkCollidable m_collidable;                  // +0x1c
    char pad40[0x58 - 0x40];
    hkCollidable* getCollidableRw() { return &m_collidable; }
};
class hkEntity : public hkWorldObject {
public:
    void* m_motion;                             // +0x58
    void* m_simulationIsland;                   // +0x5c
    hkMaterial m_material;                      // +0x60
    char pad6c[0xd0 - 0x6c];
};
struct hkRigidBodyCinfo {
    unsigned int m_collisionFilterInfo;         // +0x0
    hkShape* m_shape;                           // +0x4
    char pad08[0x10 - 0x8];
    hkVector4 m_position;                       // +0x10
    char pad20[0xa0 - 0x20];
    hkReal m_restitution;                       // +0xa0
    char padA4[0xb0 - 0xa4];
    signed char m_motionType;                   // +0xb0
    char padB1[0xc0 - 0xb1];
    hkRigidBodyCinfo();                                              // 0x01087ED0
};
class hkRigidBody : public hkEntity {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x2a)
    hkRigidBody(const hkRigidBodyCinfo& info);                       // 0x010878B0
    void removeReference();                                          // 0x0109AE60 (out of line)
};

class hkWorld : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x2c)
    char pad08[0x80 - 0x8];
    hkCollisionDispatcher* m_collisionDispatcher;   // +0x80
    char pad84[0xb5 - 0x84];
    hkBool m_wantDeactivation;                  // +0xb5
    char padB6[0x2f0 - 0xb6];
    hkWorld(const hkWorldCinfo& info, unsigned int sdkVersion);      // 0x010840E0
    hkCollisionDispatcher* getCollisionDispatcher() { return m_collisionDispatcher; }
    void setCollisionFilter(hkCollisionFilter* filter, hkBool runUpdate, int updateMode, int collectionMode);  // 0x01086F80
    void updateCollisionFilterOnWorld(int updateMode, int collectionMode);  // 0x010869E0
    void addEntity(hkRigidBody* entity, int activation);             // 0x01082EE0
    void stepDeltaTime(hkReal dt);                                   // 0x01082A90
};

// ---------------------------------------------------------------------------
// EA / eastl
// ---------------------------------------------------------------------------
namespace EA {
template <class T> class RefCountTemplate {
public:
    virtual ~RefCountTemplate() {}
    T mRefCount;                                // +0x4
    RefCountTemplate() : mRefCount(0) {}
    T AddRef() { return mRefCount++ + 1; }
    // Contains `delete this`, so cl declines to inline it, yet callers still reserve its frame.
    T Release()                                                      // 0x00453540
    {
        T r = mRefCount-- - 1;
        if (r)
            return r;
        mRefCount = 1;
        delete this;
        return 0;
    }
};

template <class T> class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount(T* pObject = 0) : mpObject(pObject) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCount& operator=(T* pObject)                              // 0x0041D980
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
};
}

namespace SP {
class cISPEditorNameProvider { public: virtual void _v0(); };
class cSPEditorModel : public cISPEditorNameProvider, public EA::RefCountTemplate<int> {
public:
    void NumberBlocks();                                             // 0x004AD4E0
};
}

namespace eastl {
struct sp_vector_allocator { const char* mpName; uint32_t mFlags; };

template <class In, class Out>
__forceinline Out copy_impl(In first, In last, Out result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}

template <class In, class Out>
__forceinline Out copy(In first, In last, Out result)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    return copy_impl(first, last, result);
}

template <class T> __forceinline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}

template <class I, class T> inline I find(I first, I last, const T& value)
{
    while ((first != last) && (*first != value))
        ++first;
    return first;
}

template <class I, class O, class T> inline O remove_copy(I first, I last, O result, const T& value)
{
    for (; first != last; ++first) {
        if (!(*first == value)) {
            *result = *first;
            ++result;
        }
    }
    return result;
}

template <class I, class T> inline I remove(I first, I last, const T& value)
{
    first = eastl::find(first, last, value);
    if (first != last) {
        I i(first);
        return eastl::remove_copy(++i, last, first, value);
    }
    return first;
}

template <class T> inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }

template <class T, class A = sp_vector_allocator> class vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;

    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) { ScratchSlots<1>(); }
    ~vector()
    {
        destruct(mpBegin, mpEnd);
        DoFree();
        ScratchSlots<3>();
    }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    bool empty() const;                                              // 0x00526430
    T& operator[](uint32_t n) { return *(mpBegin + n); }
    T* erase(T* first, T* last)
    {
        T* const position = eastl::copy(last, mpEnd, first);
        destruct(position, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(T* position, const T& value);                 // 0x004B9960
    void DoFree();                                                   // 0x00425990
};
}

namespace SP {
typedef EA::AutoRefCount<cSPEditorModel> ModelRef;

class cSPEditorPhysicsWorld : public EA::RefCountTemplate<int> {
public:
    hkWorld* mPhysicsWorld;                     // +0x8
    hkRigidBody* mFloor;                        // +0xc
    float mGravity;                             // +0x10
    float mLapseTime;                           // +0x14
    eastl::vector<ModelRef> mModels;            // +0x18
    bool mUseDynamics;                          // +0x2c

    cSPEditorPhysicsWorld();
    virtual ~cSPEditorPhysicsWorld();
    void Clear();
    void Init();
    hkWorld* World();                                                // 0x004B91C0
    void CreateFloor(float size);
    void UpdateCollisionFilters();
    void SetFloorFilter(unsigned int filter);
    void SetDefaultFloorFilter();
    void AddModel(cSPEditorModel* model);
    void RemoveModel(cSPEditorModel* model);
    void UpdatePhysics(unsigned int deltaMs);
};

// @ 0x4b8af0
cSPEditorPhysicsWorld::cSPEditorPhysicsWorld()
    : mPhysicsWorld(0), mFloor(0), mGravity(0.0f), mLapseTime(0.0f), mUseDynamics(true)
{
    mModels.clear();
}

// @ 0x4b8bd0
cSPEditorPhysicsWorld::~cSPEditorPhysicsWorld()
{
    Clear();
}

// @ 0x4b8c10
void cSPEditorPhysicsWorld::Init()
{
    Clear();
    hkWorldCinfo info;
    info.setupSolverInfo(5);
    info.m_gravity = hkVector4(0.0f, 0.0f, -mGravity);
    info.setBroadPhaseWorldSize(300.0f);
    mPhysicsWorld = new hkWorld(info, 0x765c);
    mPhysicsWorld->m_wantDeactivation = false;
    hkAgentRegisterUtil::registerAllAgents(mPhysicsWorld->getCollisionDispatcher());
    hkCollisionFilter* filter = new SPEditorCollisionFilter();
    mPhysicsWorld->setCollisionFilter(filter, true, 0, 1);
    filter->removeReference();
    mLapseTime = 0.0f;
    CreateFloor(15.0f);
}

// @ 0x4b9140
void cSPEditorPhysicsWorld::Clear()
{
    if (mPhysicsWorld)
        mPhysicsWorld->removeReference();
    mPhysicsWorld = 0;
}

// @ 0x4b91e0
void cSPEditorPhysicsWorld::CreateFloor(float size)
{
    hkRigidBodyCinfo info;
    hkVector4 halfExtents(size, size, 0.5f);
    hkBoxShape* shape = new hkBoxShape(halfExtents, 0.0f);
    shape->m_radius = 0.01f;
    info.m_shape = shape;
    info.m_motionType = 7;
    info.m_position.set(0.0f, 0.0f, -0.5f);
    info.m_restitution = 0.0f;
    hkRigidBody* body = new hkRigidBody(info);
    shape->removeReference();
    body->m_material.m_friction = 1.0f;
    body->m_collidable.m_broadPhaseHandle.m_collisionFilterInfo = 0;
    mPhysicsWorld->addEntity(body, 1);
    mFloor = body;
    body->removeReference();
}

// @ 0x4b9420
void cSPEditorPhysicsWorld::UpdateCollisionFilters()
{
    World()->updateCollisionFilterOnWorld(0, 1);
}

// @ 0x4b9440
void cSPEditorPhysicsWorld::SetFloorFilter(unsigned int filter)
{
    if (mFloor)
        mFloor->getCollidableRw()->setCollisionFilterInfo(filter);
}

// @ 0x4b9470
void cSPEditorPhysicsWorld::SetDefaultFloorFilter()
{
    if (mFloor)
        mFloor->getCollidableRw()->setCollisionFilterInfo(0);
}

// @ 0x4b94a0
void cSPEditorPhysicsWorld::AddModel(cSPEditorModel* model)
{
    if (!mPhysicsWorld)
        Init();
    if (eastl::find(mModels.begin(), mModels.end(), model) == mModels.end())
        mModels.push_back(ModelRef(model));
}

// @ 0x4b9570
void cSPEditorPhysicsWorld::RemoveModel(cSPEditorModel* model)
{
    mModels.erase(eastl::remove(mModels.begin(), mModels.end(), model), mModels.end());
}

// @ 0x4b95c0
void cSPEditorPhysicsWorld::UpdatePhysics(unsigned int deltaMs)
{
    if (!mModels.empty())
        mModels[0]->NumberBlocks();
    float timeStep = 0.016f;
    float deltaTime = deltaMs * 0.001f;
    deltaTime = eastl::min(deltaTime, 0.2f);
    mLapseTime += deltaTime;
    if (mLapseTime >= timeStep && mUseDynamics) {
        while (mLapseTime >= timeStep) {
            if (mPhysicsWorld) {
                mPhysicsWorld->stepDeltaTime(timeStep);
                mLapseTime -= timeStep;
            }
        }
    }
}
}

// ---------------------------------------------------------------------------
// eastl::vector<AutoRefCount<cSPEditorModel>> members
// ---------------------------------------------------------------------------
namespace eastl {
// @ 0x4b96d0
template vector<SP::ModelRef>::~vector();
// @ 0x4b9740
template void vector<SP::ModelRef>::push_back(const SP::ModelRef&);
// @ 0x4b97e0
template SP::ModelRef* vector<SP::ModelRef>::erase(SP::ModelRef*, SP::ModelRef*);
// @ 0x4b98b0
template SP::ModelRef* remove<SP::ModelRef*, SP::cSPEditorModel*>(SP::ModelRef*, SP::ModelRef*, SP::cSPEditorModel* const&);
}

#pragma pack(pop)
