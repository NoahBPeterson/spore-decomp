// Havok 3.1.0 slice s01129d50 (0x01129D50..0x0112AD10): hkDisableEntityCollisionFilter (ctor/dtor),
// hkDashpotAction, hkConstrainedSystemFilter, hkAngularDashpotAction and the hkBinaryPackfileReader
// loading helpers. Functionally equivalent portable source (not byte exact).
// Float math: the two applyAction functions use x87 float loads/stores; values the asm keeps on the x87 stack
// without storing are marked "X87-PRECISION". acos comes from the CRT (__CIacos); no inline fsqrt/fsin.
#include "s01129d50.h"
#include <math.h>
#include <string.h>

// ---- types used by this slice (stubs; 32-bit layouts in comments) -----------------------------------------------
class hkEntity;
class hkPhantom;
class hkShape;
class hkShapeCollection;
struct hkCollisionInput;
struct hkShapeRayCastInput;
struct hkWorldRayCastInput;

class hkEntityListener
{
public:
    virtual ~hkEntityListener() {}                           // 0
    virtual void entityAddedCallback(hkEntity*) {}           // 1 (0x010829F0, empty)
    virtual void entityRemovedCallback(hkEntity*) {}         // 2
    virtual void entityShapeSetCallback(hkEntity*) {}        // 3 (0x00AF84F0)
};

class hkConstraintData
{
public:
    virtual ~hkConstraintData() {}
    virtual void v1();
    virtual void v2();
    virtual int getType() const;                             // 3 (+0xc)
};
struct hkConstraintInstance                                  // 32-bit layout
{
    uint32_t m_vptr; hkInt16 m_memSize; hkInt16 m_refCount;  // +0x00
    uint32_t m_owner;                                        // +0x08
    hkConstraintData* m_data;                                // +0x0c
    hkEntity* m_entities[2];                                 // +0x10, +0x14
};
struct hkConstraintInternal { hkConstraintInstance* m_constraint; uint32_t m_rest[6]; };   // 0x1c bytes

class hkEntity
{
public:
    void activate();                                         // 0x01088AE0
    void removeEntityListener(hkEntityListener* l);          // 0x01088A20
    uint32_t m_pad0[22];                                     // +0x00..+0x57
    hkMotion* m_motion;                                      // +0x58
    uint32_t m_pad1[5];                                      // +0x5c..+0x6f
    hkArrayPOD<hkConstraintInternal> m_constraintsMaster;    // +0x70 (data), +0x74 (size)
    hkArrayPOD<hkConstraintInstance*> m_constraintsSlave;    // +0x7c (data), +0x80 (size)
    uint32_t m_pad2[11];                                     // +0x88..+0xb3
    hkArrayPOD<hkEntityListener*> m_entityListeners;         // +0xb4 (data), +0xb8 (size)
};

struct hkCollidable                                          // hkLinkedCollidable prefix, 32-bit layout
{
    hkShape* m_shape;                                        // +0x00
    uint32_t m_shapeKey;                                     // +0x04
    void* m_motion;                                          // +0x08
    hkCollidable* m_parent;                                  // +0x0c
    int m_ownerOffset;                                       // +0x10 owner = (char*)this + m_ownerOffset
    uint32_t m_handleId;                                     // +0x14
    uint8_t m_handleType;                                    // +0x18 (1 == BROAD_PHASE_ENTITY)
};
struct hkCdBody;

// ---- collision filter family (hkCollisionFilter = hkReferencedObject + four filter interfaces) --------------------
class hkCollidableCollidableFilter
{
public:
    virtual ~hkCollidableCollidableFilter() {}                                                // 0
    virtual hkBool isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const = 0;  // 1
};
class hkShapeCollectionFilter
{
public:
    virtual hkBool isCollisionEnabled(const hkCollisionInput& input, const hkCdBody& a, const hkCdBody& b,
                                      const hkShapeCollection& bCollection, hkUint32 keyB) const = 0;   // 0
    virtual ~hkShapeCollectionFilter() {}                                                     // 1
};
class hkRayShapeCollectionFilter
{
public:
    virtual hkBool isCollisionEnabled(const hkShapeRayCastInput& input, const hkShapeCollection& collection,
                                      hkUint32 key) const = 0;                                // 0
    virtual ~hkRayShapeCollectionFilter() {}                                                  // 1
};
class hkRayCollidableFilter
{
public:
    virtual ~hkRayCollidableFilter() {}                                                       // 0
    virtual hkBool isCollisionEnabled(const hkWorldRayCastInput& input, const hkCollidable& c) const = 0;   // 1
};

class hkCollisionFilter : public hkReferencedObject, public hkCollidableCollidableFilter,
                          public hkShapeCollectionFilter, public hkRayShapeCollectionFilter,
                          public hkRayCollidableFilter
{
public:
    virtual ~hkCollisionFilter() {}     // 0x005EFD40 (resets the base vtables)
    // Default implementations: the shared "return true" stubs 0x01129350 / 0x01129C60 / 0x01082D70.
    virtual hkBool isCollisionEnabled(const hkCollisionInput&, const hkCdBody&, const hkCdBody&,
                                      const hkShapeCollection&, hkUint32) const { return true; }
    virtual hkBool isCollisionEnabled(const hkShapeRayCastInput&, const hkShapeCollection&, hkUint32) const { return true; }
    virtual hkBool isCollisionEnabled(const hkWorldRayCastInput&, const hkCollidable&) const { return true; }
protected:
    hkCollisionFilter() {}
};

struct hkFinishLoadedObjectFlag { int m_finishing; };

class hkDisableEntityCollisionFilter : public hkCollisionFilter, public hkEntityListener
{
public:
    HK_DECLARE_CLASS_ALLOCATOR_B(0x24)
    hkDisableEntityCollisionFilter(hkFinishLoadedObjectFlag);                 // 0x01129D50
    virtual ~hkDisableEntityCollisionFilter();                                // 0x01129E30
    virtual hkBool isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const;   // 0x01129C70
    virtual void entityRemovedCallback(hkEntity* e);                          // 0x01129D20
    hkArrayPOD<hkEntity*> m_disabledEntities;                                 // +0x1c
};

class hkConstrainedSystemFilter : public hkCollisionFilter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR_B(0x24)
    virtual ~hkConstrainedSystemFilter();                                     // 0x0112A3C0 (scalar deleting form)
    virtual hkBool isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const;   // 0x0112A430
    virtual hkBool isCollisionEnabled(const hkCollisionInput& input, const hkCdBody& a, const hkCdBody& b,
                                      const hkShapeCollection& bCollection, hkUint32 keyB) const;   // 0x0112A2B0
    virtual hkBool isCollisionEnabled(const hkShapeRayCastInput& input, const hkShapeCollection& collection,
                                      hkUint32 key) const;                    // 0x0112A300
    virtual hkBool isCollisionEnabled(const hkWorldRayCastInput& input, const hkCollidable& c) const;   // 0x0112A340
    hkCollisionFilter* m_otherFilter;                                         // +0x18
};

// ---- actions ----------------------------------------------------------------------------------------------------
class hkAction : public hkReferencedObject
{
public:
    virtual void applyAction(const hkStepInfo& stepInfo) = 0;                  // 2
    virtual void getEntities(hkArray<hkEntity*>& out) = 0;                     // 3
    virtual void getPhantoms(hkArray<hkPhantom*>& out) {}                      // 4 (0x010829F0)
    virtual void entityRemovedCallback(hkEntity* e) = 0;                       // 5
    virtual hkAction* clone(const hkArray<hkEntity*>& newEntities, const hkArray<hkPhantom*>& newPhantoms) const = 0;   // 6
    void* m_world;                                                             // +0x08
    void* m_island;                                                            // +0x0c
    hkUint32 m_userData;                                                       // +0x10
    const char* m_name;                                                        // +0x14
};

class hkBinaryAction : public hkAction
{
public:
    hkBinaryAction(hkEntity* a, hkEntity* b, hkUint32 userData);               // 0x0120B960
    virtual void getEntities(hkArray<hkEntity*>& out);                         // 0x0120BA00
    virtual void entityRemovedCallback(hkEntity* e);                           // 0x0120B8D0
    hkEntity* m_entityA;                                                       // +0x18
    hkEntity* m_entityB;                                                       // +0x1c
};

class hkDashpotAction : public hkBinaryAction
{
public:
    HK_DECLARE_CLASS_ALLOCATOR_B(0x26)
    hkDashpotAction(hkEntity* a, hkEntity* b, hkUint32 userData);              // 0x01129F40
    virtual void applyAction(const hkStepInfo& stepInfo);                      // 0x01129FC0
    virtual hkAction* clone(const hkArray<hkEntity*>& newEntities, const hkArray<hkPhantom*>& newPhantoms) const;   // 0x0112A200
    hkVector4 m_point[2];                                                      // +0x20 (attach points in A and B)
    float m_strength;                                                          // +0x40
    float m_damping;                                                           // +0x44
    uint32_t m_pad48[2];                                                       // +0x48 (not initialised by the ctor)
    hkVector4 m_impulse;                                                       // +0x50
};

class hkAngularDashpotAction : public hkBinaryAction
{
public:
    HK_DECLARE_CLASS_ALLOCATOR_B(0x26)
    hkAngularDashpotAction(hkEntity* a, hkEntity* b, hkUint32 userData);       // 0x0112A5C0
    virtual void applyAction(const hkStepInfo& stepInfo);                      // 0x0112A610
    virtual hkAction* clone(const hkArray<hkEntity*>& newEntities, const hkArray<hkPhantom*>& newPhantoms) const;   // 0x0112A890
    hkQuaternion m_rotation;                                                   // +0x20
    float m_strength;                                                          // +0x30
    float m_damping;                                                           // +0x34
};

// ---- packfile reader (layouts from the reflection data / dev PDB, 32-bit) ----------------------------------------
struct hkPackfileHeader                     // 0x40 bytes
{
    int m_magic[2];                         // +0x00 (0x57e0e057, 0x10c0c010)
    int m_userTag;                          // +0x08
    int m_fileVersion;                      // +0x0c
    uint8_t m_layoutRules[4];               // +0x10
    int m_numSections;                      // +0x14
    int m_contentsSectionIndex;             // +0x18
    int m_contentsSectionOffset;            // +0x1c
    int m_contentsClassNameSectionIndex;    // +0x20
    int m_contentsClassNameSectionOffset;   // +0x24
    char m_contentsVersion[16];             // +0x28
    int m_pad[2];                           // +0x38
};
struct hkPackfileSectionHeader              // 0x30 bytes
{
    char m_sectionTag[19];                  // +0x00
    char m_nullByte;                        // +0x13
    int m_absoluteDataStart;                // +0x14
    int m_localFixupsOffset;                // +0x18
    int m_globalFixupsOffset;               // +0x1c
    int m_virtualFixupsOffset;              // +0x20
    int m_externalFixupsOffset;             // +0x24
    int m_endOffset;                        // +0x28
    int m_spare;                            // +0x2c
};
static const int HK_PACKFILE_MAGIC0 = 0x57e0e057;
static const int HK_PACKFILE_MAGIC1 = 0x10c0c010;
enum { HK_MEMORY_CLASS_EXPORT = 5 };       // memory class used by the packfile loader

class hkPackfileObjectUpdateTracker
{
public:
    uint32_t m_pad[13];                     // +0x00..+0x33
    const char* m_contentsClassName;        // +0x34 (name inferred from hkBinaryPackfileReader::getContentsClassName)
};

class hkBinaryPackfileReader;
class hkBinaryAllocatedData : public hkReferencedObject
{
public:
    hkArrayPOD<void*> m_memory;             // +0x08
    uint32_t m_chunks[3];                   // +0x14
};

class hkPackfileReader : public hkReferencedObject
{
public:
    virtual hkResult loadEntireFile(hkStreamReader* reader) = 0;                       // 2
    virtual void* getContentsWithRegistry(const char* className, const void* registry) = 0;   // 3
    virtual void* getContents(const char* className);                                  // 4 (0x0112BE10)
    virtual const char* getContentsClassName() = 0;                                    // 5
    virtual void* getLoadedObjects() = 0;                                              // 6
    virtual void* getUpdateTracker() = 0;                                              // 7
    virtual const char* getOriginalContentsVersion() = 0;                              // 8
    virtual void slot9() {}                                                            // 9 (0x0093B6C0)
    virtual hkResult loadEntireFileInplace(void* data, int dataSize) = 0;              // 10
};

class hkBinaryPackfileReader : public hkPackfileReader
{
public:
    virtual hkResult loadEntireFile(hkStreamReader* reader);                           // 0x0112B090
    virtual void* getContentsWithRegistry(const char* className, const void* registry);   // 0x0112B390
    virtual const char* getContentsClassName();                                        // 0x0112A990
    virtual void* getLoadedObjects();                                                  // 0x0112B110
    virtual void* getUpdateTracker();                                                  // 0x0112B7F0
    virtual const char* getOriginalContentsVersion();                                  // 0x0112A910
    virtual hkResult loadEntireFileInplace(void* data, int dataSize);                  // 0x0112AAB0
    virtual int getSectionIndex(const char* sectionTag);                               // 0x0112A940
    virtual void* getSectionDataByIndex(int sectionIndex, int offset);                 // 0x0112AA90

    hkResult fixupGlobalReferences();                                                  // 0x0112A9C0
    hkResult loadFileHeader(hkStreamReader* reader, hkPackfileHeader* header);         // 0x0112AC40
    hkResult loadSectionHeadersNoSeek(hkStreamReader* reader, hkPackfileSectionHeader* sections);   // 0x0112AD10

    hkBinaryAllocatedData* m_allocatedData;                                            // +0x08
    hkPackfileHeader* m_header;                                                        // +0x0c
    hkPackfileSectionHeader* m_sections;                                               // +0x10
    hkArrayPOD<void*> m_sectionData;                                                   // +0x14 (hkInplaceArray<void*,16>)
    void* m_sectionDataStorage[16];                                                    // +0x20
    int m_streamOffset;                                                                // +0x60
    void* m_loadedObjects;                                                             // +0x64
    hkPackfileObjectUpdateTracker* m_tracker;                                          // +0x68
};

// =====================================================================================================================
// hkDisableEntityCollisionFilter
// =====================================================================================================================

// @ 0x01129d50
hkDisableEntityCollisionFilter::hkDisableEntityCollisionFilter(hkFinishLoadedObjectFlag)
{
    // hkReferencedObject() sets the reference count to 1; the memory size stays untouched (0x01129D52).
    m_disabledEntities.m_data = 0;
    m_disabledEntities.m_size = 0;
    m_disabledEntities.m_capacityAndFlags = (int)0x80000000;   // DONT_DEALLOCATE_FLAG
}

// @ 0x01129e10
// Finish-loaded-object hook: re-runs the constructor on a freshly deserialised object (the asm returns the
// object pointer in EAX but the hook is called as a void function).
void finishLoadedObject_hkDisableEntityCollisionFilter(void* p)
{
    if (p != 0)
    {
        hkFinishLoadedObjectFlag flag; flag.m_finishing = 1;
        new (p) hkDisableEntityCollisionFilter(flag);
    }
}

// @ 0x01129e30
hkDisableEntityCollisionFilter::~hkDisableEntityCollisionFilter()
{
    hkEntityListener* listener = static_cast<hkEntityListener*>(this);   // this + 0x18
    for (int i = 0; i < m_disabledEntities.m_size; ++i)
    {
        hkEntity* entity = m_disabledEntities.m_data[i];
        int index = entity->m_entityListeners.indexOf(listener);
        if (index >= 0)
            entity->removeEntityListener(listener);
    }
    m_disabledEntities.freeBuffer((int)sizeof(hkEntity*));
    // base destructors restore the hkEntityListener / hkCollisionFilter vtables
}

// =====================================================================================================================
// hkDashpotAction
// =====================================================================================================================

// @ 0x01129f40
hkDashpotAction::hkDashpotAction(hkEntity* a, hkEntity* b, hkUint32 userData)
    : hkBinaryAction(a, b, userData)
{
    m_strength = 0.1f;      // 0x3dcccccd
    m_damping = 0.01f;      // 0x3c23d70a
    m_point[0].x = 0.0f; m_point[0].y = 0.0f; m_point[0].z = 0.0f; m_point[0].w = 0.0f;
    m_point[1].x = 0.0f; m_point[1].y = 0.0f; m_point[1].z = 0.0f; m_point[1].w = 0.0f;
    // m_impulse is intentionally left uninitialised (the original does not touch +0x50..+0x5f)
}

// @ 0x01129fc0
void hkDashpotAction::applyAction(const hkStepInfo& stepInfo)
{
    HK_TIMER_BEGIN("TtDashpot");

    hkEntity* entityA = m_entityA;
    hkEntity* entityB = m_entityB;
    float dt = stepInfo.m_deltaTime * 151.0f;           // stored to a float slot

    hkVector4 pointA;
    pointA.setTransformedPos(entityA->m_motion->m_transform, m_point[0]);
    hkVector4 pointB;
    pointB.setTransformedPos(entityB->m_motion->m_transform, m_point[1]);

    // X87-PRECISION: dx, dy stay on the x87 stack unrounded; dz, dw are stored to float slots.
    hkX87Real dx = (hkX87Real)pointA.x - pointB.x;
    hkX87Real dy = (hkX87Real)pointA.y - pointB.y;
    float dz = pointA.z - pointB.z;
    float dw = pointA.w - pointB.w;

    const hkVector4& velA = entityA->m_motion->m_linearVelocity;
    const hkVector4& velB = entityB->m_motion->m_linearVelocity;
    float vx = velA.x - velB.x;
    float vy = velA.y - velB.y;
    float vz = velA.z - velB.z;
    float vw = velA.w - velB.w;

    // spring term: impulse = (dt * strength) * delta
    // X87-PRECISION: k1 for the x component is the unrounded register value, the others use the float copy.
    hkX87Real k1reg = (hkX87Real)dt * m_strength;
    float k1 = (float)k1reg;
    m_impulse.x = (float)(k1reg * dx);
    m_impulse.y = (float)(dy * k1);
    m_impulse.z = dz * k1;
    m_impulse.w = dw * k1;

    // damping term: impulse += (dt * damping) * velocityDelta
    // X87-PRECISION: k2 and vx*k2 are not stored in the original.
    hkX87Real k2 = (hkX87Real)dt * m_damping;
    hkX87Real vxk2 = (hkX87Real)vx * k2;
    float vyk2 = (float)((hkX87Real)vy * k2);
    float vzk2 = (float)((hkX87Real)vz * k2);
    float vwk2 = (float)((hkX87Real)vw * k2);
    m_impulse.x = (float)(vxk2 + m_impulse.x);
    m_impulse.y = vyk2 + m_impulse.y;
    m_impulse.z = vzk2 + m_impulse.z;
    m_impulse.w = vwk2 + m_impulse.w;

    hkVector4 negImpulse;
    negImpulse.x = m_impulse.x * -1.0f;
    negImpulse.y = m_impulse.y * -1.0f;
    negImpulse.z = m_impulse.z * -1.0f;
    negImpulse.w = m_impulse.w * -1.0f;

    entityA->activate();
    entityA->m_motion->applyPointImpulse(negImpulse, pointA);
    entityB->activate();
    entityB->m_motion->applyPointImpulse(m_impulse, pointB);

    HK_TIMER_END();
}

// @ 0x0112a200
hkAction* hkDashpotAction::clone(const hkArray<hkEntity*>& newEntities, const hkArray<hkPhantom*>& newPhantoms) const
{
    if (newEntities.m_size == 2 && newPhantoms.m_size == 0)
    {
        hkDashpotAction* c = new hkDashpotAction(newEntities.m_data[0], newEntities.m_data[1], m_userData);
        memcpy(&c->m_point[0], &m_point[0], sizeof(hkVector4));      // dword copies in the binary
        memcpy(&c->m_point[1], &m_point[1], sizeof(hkVector4));
        memcpy(&c->m_strength, &m_strength, sizeof(float));
        memcpy(&c->m_damping, &m_damping, sizeof(float));
        memcpy(&c->m_impulse, &m_impulse, sizeof(hkVector4));
        return c;
    }
    return 0;
}

// =====================================================================================================================
// hkConstrainedSystemFilter
// =====================================================================================================================

// @ 0x0112a2b0
hkBool hkConstrainedSystemFilter::isCollisionEnabled(const hkCollisionInput& input, const hkCdBody& a, const hkCdBody& b,
                                                     const hkShapeCollection& bCollection, hkUint32 keyB) const
{
    if (m_otherFilter != 0)
    {
        const hkShapeCollectionFilter* f = static_cast<const hkShapeCollectionFilter*>(m_otherFilter);
        if (!f->isCollisionEnabled(input, a, b, bCollection, keyB))
            return false;
    }
    return true;
}

// @ 0x0112a300
hkBool hkConstrainedSystemFilter::isCollisionEnabled(const hkShapeRayCastInput& input, const hkShapeCollection& collection,
                                                     hkUint32 key) const
{
    if (m_otherFilter != 0)
    {
        const hkRayShapeCollectionFilter* f = static_cast<const hkRayShapeCollectionFilter*>(m_otherFilter);
        if (!f->isCollisionEnabled(input, collection, key))
            return false;
    }
    return true;
}

// @ 0x0112a340
hkBool hkConstrainedSystemFilter::isCollisionEnabled(const hkWorldRayCastInput& input, const hkCollidable& c) const
{
    if (m_otherFilter != 0)
    {
        const hkRayCollidableFilter* f = static_cast<const hkRayCollidableFilter*>(m_otherFilter);
        if (!f->isCollisionEnabled(input, c))
            return false;
    }
    return true;
}

// @ 0x0112a3c0
// Scalar deleting destructor: releases m_otherFilter, runs ~hkCollisionFilter (0x005EFD40), and (flag & 1)
// frees through hkMemory::deallocateChunk(this, memSize, 0x24) (the class allocator's operator delete).
hkConstrainedSystemFilter::~hkConstrainedSystemFilter()
{
    if (m_otherFilter != 0)
        m_otherFilter->removeReference();
}

// @ 0x0112a430
hkBool hkConstrainedSystemFilter::isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const
{
    hkEntity* entityA = (a.m_handleType == 1) ? (hkEntity*)((uintptr_t)&a + a.m_ownerOffset) : (hkEntity*)0;
    hkEntity* entityB = (b.m_handleType == 1) ? (hkEntity*)((uintptr_t)&b + b.m_ownerOffset) : (hkEntity*)0;

    if (m_otherFilter != 0)
    {
        const hkCollidableCollidableFilter* f = static_cast<const hkCollidableCollidableFilter*>(m_otherFilter);
        if (!f->isCollisionEnabled(a, b))
            return false;
    }
    if (entityA == 0 || entityB == 0)
        return true;

    // Search the constraints of the entity that has fewer of them for one that links the two entities.
    hkEntity* searched;
    hkEntity* other;
    if (entityA->m_constraintsSlave.m_size + entityA->m_constraintsMaster.m_size >
        entityB->m_constraintsSlave.m_size + entityB->m_constraintsMaster.m_size)
    {
        searched = entityB;
        other = entityA;
    }
    else
    {
        searched = entityA;
        other = entityB;
    }
    int numMaster = searched->m_constraintsMaster.m_size;
    int total = searched->m_constraintsSlave.m_size + numMaster;
    for (int i = 0; i < total; ++i)
    {
        hkConstraintInstance* inst;
        if (i < numMaster)
            inst = searched->m_constraintsMaster.m_data[i].m_constraint;
        else
            inst = searched->m_constraintsSlave.m_data[i - numMaster];
        if (inst != 0 && inst->m_data->getType() != 0xb)    // 0xb: constraint type that never disables collisions
        {
            if (inst->m_entities[0] == other || inst->m_entities[1] == other)
                return false;
        }
    }
    return true;
}

// =====================================================================================================================
// hkAngularDashpotAction
// =====================================================================================================================

// @ 0x0112a5c0
hkAngularDashpotAction::hkAngularDashpotAction(hkEntity* a, hkEntity* b, hkUint32 userData)
    : hkBinaryAction(a, b, userData)
{
    m_strength = 0.1f;      // 0x3dcccccd
    m_damping = 0.01f;      // 0x3c23d70a
    m_rotation.x = 0.0f;
    m_rotation.y = 0.0f;
    m_rotation.z = 0.0f;
    m_rotation.w = 1.0f;
}

// @ 0x0112a610
void hkAngularDashpotAction::applyAction(const hkStepInfo& stepInfo)
{
    float dt = stepInfo.m_deltaTime * 200.0f;
    hkEntity* entityB = m_entityB;
    hkEntity* entityA = m_entityA;
    hkMotion* motionB = entityB->m_motion;

    hkQuaternion q;
    q.setMul(motionB->m_rotation, m_rotation);
    hkMotion* motionA = entityA->m_motion;
    hkQuaternion conj;
    conj.x = -q.x; conj.y = -q.y; conj.z = -q.z; conj.w = q.w;
    q.setMul(motionA->m_rotation, conj);

    float wx = motionA->m_angularVelocity.x - motionB->m_angularVelocity.x;
    float wy = motionA->m_angularVelocity.y - motionB->m_angularVelocity.y;
    float wz = motionA->m_angularVelocity.z - motionB->m_angularVelocity.z;
    float ww = motionA->m_angularVelocity.w - motionB->m_angularVelocity.w;

    // hkQuaternion::getAngle: 2 * acos(|w|), with the clamps of the hkMath::acos wrapper.
    float absW = fabsf(q.w);
    hkX87Real angle;     // X87-PRECISION: acos result (extended precision) is doubled before being stored
    if (!(absW >= 1.0f))                     // |w| < 1 or NaN (fcomp, test ah,1)
        angle = acos((double)absW);          // __CIacos
    else if (!(absW > 0.0f))                 // fcomp 0.0, test ah,0x41
        angle = 3.1415927f;                  // 0x40490fdb
    else
        angle = 0.0f;
    float angle2 = (float)(angle + angle);

    // axis * angle (the x component stays on the x87 stack, 0.0 when the angle is tiny)
    hkX87Real ax = 0.0;                      // X87-PRECISION
    float ay = 0.0f, az = 0.0f, aw = 0.0f;
    if (fabsf(angle2) > 0.001f)              // 0x3a83126f; skipped when <= 0.001 or NaN
    {
        ax = (hkX87Real)q.x * angle2;
        ay = q.y * angle2;
        az = q.z * angle2;
        aw = q.w * angle2;
    }

    // spring term
    // X87-PRECISION: k1 register value is used unrounded for x, the stored float copy for the rest;
    // ax*k1 and ay*k1 are not stored.
    hkX87Real k1reg = (hkX87Real)dt * m_strength;
    float k1 = (float)k1reg;
    hkX87Real axk = ax * k1reg;
    hkX87Real ayk = (hkX87Real)ay * k1;
    az = az * k1;
    aw = aw * k1;

    // damping term
    // X87-PRECISION: k2 and wx*k2 are not stored.
    hkX87Real k2 = (hkX87Real)dt * m_damping;
    hkX87Real wxk2 = (hkX87Real)wx * k2;
    float wyk2 = (float)((hkX87Real)wy * k2);
    float wzk2 = (float)((hkX87Real)wz * k2);
    float wwk2 = (float)((hkX87Real)ww * k2);

    hkVector4 impulse;
    impulse.x = (float)(axk + wxk2);
    impulse.y = (float)(ayk + wyk2);
    impulse.z = az + wzk2;
    impulse.w = aw + wwk2;

    entityB->activate();
    entityB->m_motion->applyAngularImpulse(impulse);

    impulse.x = -impulse.x;
    impulse.y = -impulse.y;
    impulse.z = -impulse.z;
    impulse.w = -impulse.w;
    entityA->activate();
    entityA->m_motion->applyAngularImpulse(impulse);
}

// @ 0x0112a890
hkAction* hkAngularDashpotAction::clone(const hkArray<hkEntity*>& newEntities, const hkArray<hkPhantom*>& newPhantoms) const
{
    if (newEntities.m_size == 2 && newPhantoms.m_size == 0)
    {
        hkAngularDashpotAction* c = new hkAngularDashpotAction(newEntities.m_data[0], newEntities.m_data[1], m_userData);
        memcpy(&c->m_rotation, &m_rotation, sizeof(hkQuaternion));
        memcpy(&c->m_strength, &m_strength, sizeof(float));
        memcpy(&c->m_damping, &m_damping, sizeof(float));
        return c;
    }
    return 0;
}

// =====================================================================================================================
// hkBinaryPackfileReader
// =====================================================================================================================

// @ 0x0112a910
const char* hkBinaryPackfileReader::getOriginalContentsVersion()
{
    hkPackfileHeader* header = m_header;
    const char* version = header->m_contentsVersion;
    if ((uint8_t)version[0] == 0xff)           // unset: derive from the file version
    {
        if (header->m_fileVersion == 1)
            return "Havok-3.0.0";
        return (header->m_fileVersion == 2) ? "Havok-3.1.0" : (const char*)0;
    }
    return version;
}

// @ 0x0112a940
int hkBinaryPackfileReader::getSectionIndex(const char* sectionTag)
{
    for (int i = 0; i < m_header->m_numSections; ++i)
    {
        if (hkString::strCmp(m_sections[i].m_sectionTag, sectionTag) == 0)
            return i;
    }
    return -1;
}

// @ 0x0112a990
const char* hkBinaryPackfileReader::getContentsClassName()
{
    if (m_tracker != 0)
        return m_tracker->m_contentsClassName;
    int sectionIndex = m_header->m_contentsClassNameSectionIndex;
    int offset = m_header->m_contentsClassNameSectionOffset;
    if (sectionIndex >= 0 && offset >= 0)
        return (const char*)getSectionDataByIndex(sectionIndex, offset);
    return 0;
}

// @ 0x0112a9c0
hkResult hkBinaryPackfileReader::fixupGlobalReferences()
{
    for (int s = 0; s < m_header->m_numSections; ++s)
    {
        char* data = (char*)m_sectionData.m_data[s];
        if (data != 0)
        {
            const hkPackfileSectionHeader& sec = m_sections[s];
            // entries are (srcOffset, dstSectionIndex, dstOffset) int triples
            int* fix = (int*)(data + sec.m_globalFixupsOffset);
            for (int i = 0; i < (sec.m_virtualFixupsOffset - sec.m_globalFixupsOffset) / 4; i += 3, fix += 3)
            {
                if (fix[0] != -1)
                {
                    // 32-bit layout assumption: the fixed-up slot holds a 32-bit pointer
                    void* target = getSectionDataByIndex(fix[1], fix[2]);
                    *(void**)(data + fix[0]) = target;
                }
            }
        }
    }
    return HK_SUCCESS;
}

// @ 0x0112aa90
void* hkBinaryPackfileReader::getSectionDataByIndex(int sectionIndex, int offset)
{
    char* base = (char*)m_sectionData.m_data[sectionIndex];
    if (base != 0)
        return base + offset;
    return 0;
}

// @ 0x0112aab0
hkResult hkBinaryPackfileReader::loadEntireFileInplace(void* data, int dataSize)
{
    // Dead scratch header: the original builds an all-0xff header with the magic filled in and never reads it.
    hkPackfileHeader scratch;
    hkString::memSet(&scratch, -1, 0x40);
    scratch.m_magic[0] = HK_PACKFILE_MAGIC0;
    scratch.m_magic[1] = HK_PACKFILE_MAGIC1;
    scratch.m_contentsVersion[0] = 0;

    hkPackfileHeader* header = (hkPackfileHeader*)data;
    if (header->m_magic[0] != HK_PACKFILE_MAGIC0 || header->m_magic[1] != HK_PACKFILE_MAGIC1)
        return HK_FAILURE;

    m_header = header;
    m_sections = (header->m_numSections > 0) ? (hkPackfileSectionHeader*)((char*)header + 0x40) : (hkPackfileSectionHeader*)0;

    int numSections = header->m_numSections;
    int cap = m_sectionData.m_capacityAndFlags & 0x3fffffff;
    if (cap < numSections)
    {
        int newCap = cap * 2;
        if (numSections >= newCap)
            newCap = numSections;
        hkArrayUtil::_reserveExactly(&m_sectionData, newCap, 4);
    }
    m_sectionData.m_size = numSections;

    for (int s = 0; s < m_header->m_numSections; ++s)
    {
        const hkPackfileSectionHeader& sec = m_sections[s];
        char* base = (char*)data + sec.m_absoluteDataStart;
        int* localFixups = (int*)(base + sec.m_localFixupsOffset);
        // (srcOffset, dstOffset) pairs: *(base + src) = base + dst
        for (int i = 0; i < (sec.m_globalFixupsOffset - sec.m_localFixupsOffset) / 4; i += 2)
        {
            if (localFixups[i] != -1)
                *(char**)(base + localFixups[i]) = base + localFixups[i + 1];   // 32-bit pointer slot
        }
        m_sectionData.m_data[s] = base;
    }

    int classNameSection = m_header->m_contentsClassNameSectionIndex;
    if (classNameSection >= 0 && m_header->m_contentsClassNameSectionOffset >= 0 && m_header->m_fileVersion < 3)
    {
        // Old files store a pointer to the class name; convert it to a section-relative offset.
        void* slot = getSectionDataByIndex(classNameSection, m_header->m_contentsClassNameSectionOffset);
        uintptr_t namePtr = *(uintptr_t*)slot;                                  // 0x00FC8380: *(int*)p
        m_header->m_contentsClassNameSectionOffset = (int)(namePtr - (uintptr_t)m_sectionData.m_data[classNameSection]);
    }
    return fixupGlobalReferences();
}

// @ 0x0112ac40
hkResult hkBinaryPackfileReader::loadFileHeader(hkStreamReader* reader, hkPackfileHeader* header)
{
    m_streamOffset = reader->seekTellSupported() ? reader->tell() : 0;

    if (header == 0)
    {
        header = (hkPackfileHeader*)hkMemory::s_instance->allocate(0x40, HK_MEMORY_CLASS_EXPORT);
        m_allocatedData->m_memory.pushBack(header);
    }
    if (reader->read(header, 0x40) == 0x40)
    {
        hkPackfileHeader scratch;                // dead scratch header (all 0xff), never read
        hkString::memSet(&scratch, -1, 0x40);
        if (header->m_magic[0] == HK_PACKFILE_MAGIC0 && header->m_magic[1] == HK_PACKFILE_MAGIC1)
        {
            m_header = header;
            return HK_SUCCESS;
        }
    }
    m_header = 0;
    return HK_FAILURE;
}

// @ 0x0112ad10
hkResult hkBinaryPackfileReader::loadSectionHeadersNoSeek(hkStreamReader* reader, hkPackfileSectionHeader* sections)
{
    if (sections == 0)
    {
        sections = (hkPackfileSectionHeader*)hkMemory::s_instance->allocate(m_header->m_numSections * 0x30, HK_MEMORY_CLASS_EXPORT);
        m_allocatedData->m_memory.pushBack(sections);
    }
    int nbytes = m_header->m_numSections * 0x30;
    if (reader->read(sections, nbytes) != nbytes)
        return HK_FAILURE;

    m_sections = sections;
    int numSections = m_header->m_numSections;
    int oldSize = m_sectionData.m_size;
    if (oldSize < numSections)                    // hkArray::setSize: grow and zero the new entries
    {
        int cap = m_sectionData.m_capacityAndFlags & 0x3fffffff;
        if (cap < numSections)
        {
            int newCap = cap * 2;
            if (numSections >= newCap)
                newCap = numSections;
            hkArrayUtil::_reserveExactly(&m_sectionData, newCap, 4);
        }
        for (int i = oldSize; i < numSections; ++i)
            m_sectionData.m_data[i] = 0;
    }
    m_sectionData.m_size = numSections;
    return HK_SUCCESS;
}
// --- equivalence checker address annotations
    extern unsigned int g_hkThreadMemoryTls; // 0x016e4174

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
