// Havok 3.1.0 agent3 entry points: capsule/triangle process, box/box agent3, predictive-GSK cylinder create,
// plus the two dispatcher registrations for the capsule/triangle and box/box agents.
// Flags: /O2 /MD /Gy /TP   (x87 float math, 16-byte aligned frames, no /EHsc, no /fp:fast)
//
//  0x010fd4c0  hkCapsuleTriangleAgent3::process
//  0x010fda70  hkCapsuleTriangleAgent3 registration
//  0x010fdae0  hkBoxBoxAgent3::removePoint
//  0x010fdb20  hkBoxBoxAgent3::commitPotential
//  0x010fdb50  hkBoxBoxAgent3::create
//  0x010fdb70  hkBoxBoxAgent3::destroy
//  0x010fdbe0  hkBoxBoxAgent3::process
//  0x010fdec0  hkBoxBoxAgent3 registration
//  0x010fdf30  hkPredGskCylinderAgent3::create
#include "types.h"
#include <math.h>

typedef int   hkInt32;
typedef float hkReal;
typedef unsigned short hkContactPointId;

class hkBool {
public:
    char m_bool;
    hkBool() {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
};

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
};

class hkRotation {
public:
    hkVector4 c0, c1, c2;
};

class hkTransform {
public:
    hkRotation m_rotation;
    hkVector4  m_translation;
};

class hkShape {
public:
    virtual void v00(); virtual void v04(); virtual int getType() const; virtual void v0c();
    unsigned int m_pad[2];      // +0x4, +0x8
    float        m_radius;      // +0xc
};

class hkCdBody {
public:
    const hkShape*     m_shape;     // +0x0
    unsigned int       m_shapeKey;  // +0x4
    const hkTransform* m_motion;    // +0x8
    const hkCdBody*    m_parent;    // +0xc
};

struct hkCollisionInput { private:
public:
    void*   m_dispatcher;             // +0x0
    void*   m_filter;                 // +0x4
    float   m_tolerance;              // +0x8
    hkBool  m_createPredictiveAgents; // +0xc
};

struct hkProcessCdPoint {
    hkVector4        m_position;         // +0x00
    hkVector4        m_separatingNormal; // +0x10
    hkContactPointId m_contactPointId;   // +0x20
    unsigned short   m_pad22;            // +0x22
    unsigned int     m_pad24[3];         // +0x24
};

struct hkPendingContact {
    void*                m_entry;     // +0x0
    hkProcessCdPoint**   m_contact;   // +0x4
    void*                m_agentData; // +0x8
};

struct hkProcessCollisionOutput {
    hkProcessCdPoint* m_firstFreeContactPoint;   // +0x0
    unsigned int      m_pad[0xc0f];
    hkPendingContact* m_potentialContacts;       // +0x3040
};

struct hkCollisionInput;

class hkContactMgr {
public:
    virtual void v00();
    virtual void v04();
    virtual hkContactPointId addContactPoint(const hkCdBody& a, const hkCdBody& b,
                                             const hkCollisionInput& input, hkProcessCdPoint& cp);  // +0x08
    virtual hkInt32 reserveContactPoints(hkInt32 n);                                               // +0x0c
    virtual void removeContactPoint(hkContactPointId id);                                          // +0x10
};

struct hkProcessCollisionInput { private:
public:
    void*       m_dispatcher;             // +0x0
    void*       m_filter;                 // +0x4
    float       m_tolerance;              // +0x8
    hkBool      m_createPredictiveAgents; // +0xc
    float       m_stepInfo[4];            // +0x10
    void*       m_config;                 // +0x20
    void*       m_dynamicsInfo;           // +0x24
    const void* m_collisionQualityInfo;   // +0x28
};

struct hkAgent3ProcessInput {
    const hkCdBody*                m_bodyA;      // +0x0
    const hkCdBody*                m_bodyB;      // +0x4
    const hkProcessCollisionInput* m_input;      // +0x8
    hkContactMgr*                  m_contactMgr; // +0xc
    hkTransform                    m_aTb;        // +0x10
    float                          m_distAtT1;   // +0x50
};

struct hkAgent3Input {
    const hkCdBody*         m_bodyA;  // +0x0
    const hkCdBody*         m_bodyB;  // +0x4
    const hkCollisionInput* m_input;  // +0x8
    hkTransform             m_aTb;    // +0xc
};

struct hkAgentEntry {
    unsigned char m_streamCommand;     // +0x0
    unsigned char m_agentType;         // +0x1
    unsigned char m_numContactPoints;  // +0x2
    unsigned char m_size;              // +0x3
    unsigned int  m_userData;          // +0x4
};

class hkCapsuleShape {
public:
    virtual void v00(); virtual void v04(); virtual int getType() const; virtual void v0c();
    unsigned int m_pad[2];      // +0x4, +0x8
    float        m_radius;      // +0xc
    hkVector4    m_vertex[2];   // +0x10, +0x20
};

class hkTriangleShape {
public:
    virtual void v00(); virtual void v04(); virtual int getType() const; virtual void v0c();
    unsigned int m_pad[2];      // +0x4, +0x8
    float        m_radius;      // +0xc
    hkVector4    m_vertex[3];   // +0x10, +0x20, +0x30
};

// hkBoxBoxManifold: 8 cached feature points followed by the point bookkeeping.
class hkBoxBoxManifold {
public:
    struct hkFeatureContactPoint {
        unsigned char    m_featureIdA;     // +0x0
        unsigned char    m_featureIdB;     // +0x1
        hkContactPointId m_contactPointId; // +0x2
    };
    hkFeatureContactPoint m_contactPoints[8];   // +0x00
    unsigned char  m_faceVertexFeatureCount;    // +0x20
    unsigned char  m_numPoints;                 // +0x21
    hkBool         m_isComplete;                // +0x22
    hkBool         m_manifoldNormalInitialized; // +0x23
    unsigned int   m_pad24[3];                  // +0x24
    hkVector4      m_manifoldNormalA;           // +0x30
    hkVector4      m_manifoldNormalB;           // +0x40

    void removePoint(int index);   // 0x010ec4a0
    void init();                   // 0x010ec500
};

// --------------------------------------------------------------------------------------------------------
// hkBoxBoxCollisionDetection: box/box manifold builder (only the members the agents touch).
// --------------------------------------------------------------------------------------------------------
class hkBoxBoxCollisionDetection {
public:
    const hkCdBody*           m_bodyA;    // +0x00
    const hkCdBody*           m_bodyB;    // +0x04
    const hkCollisionInput*   m_env;      // +0x08
    hkContactMgr*             m_contactMgr; // +0x0c
    hkProcessCollisionOutput* m_result;   // +0x10
    const hkTransform*        m_wTa;      // +0x14
    const hkTransform*        m_wTb;      // +0x18
    unsigned int              m_pad1c;    // +0x1c
    hkRotation                m_aRb;      // +0x20
    hkVector4                 m_aTb;      // +0x50
    hkVector4                 m_radiusA;  // +0x60
    hkVector4                 m_radiusB;  // +0x70
    hkVector4                 m_tolerance4;         // +0x80
    hkVector4                 m_boundaryToleranceA; // +0x90
    hkVector4                 m_boundaryToleranceB; // +0xa0
    hkReal                    m_tolerance;          // +0xb0
    unsigned int              m_padb4[3];
    hkVector4                 m_dinA;     // +0xc0
    hkVector4                 m_dinB;     // +0xd0

    void calcManifold(hkBoxBoxManifold& manifold) const;   // 0x0110b3a0
};

// --------------------------------------------------------------------------------------------------------
// collision dispatcher registration
// --------------------------------------------------------------------------------------------------------
class hkBoxBoxManifold;

// The dispatcher object itself (opaque: registerAgent3 needs no member state).
class hkCollisionDispatcher {
public:
    struct Agent3Funcs {
        void* (*m_createFunc)();
        void  (*m_destroyFunc)();
        void  (*m_cleanupFunc)();
        void  (*m_removePointFunc)();
        void  (*m_commitPotentialFunc)();
        void  (*m_createZombieFunc)();
        void  (*m_updateFilterFunc)();
        void  (*m_invalidateTimFunc)();
        void  (*m_warpTimeFunc)();
        void  (*m_sepNormalFunc)();
        void* (*m_processFunc)();
        hkBool m_isPredictive;
        hkBool m_ignoreSymmetricVersion;
    };
    hkInt32 registerAgent3(Agent3Funcs& funcs, int typeA, int typeB);   // 0x010cd4c0
};

// ---- external callees -------------------------------------------------------------------------------------
extern "C" void     __cdecl hkCollideCapsuleUtilManifoldCapsVsTriangle(const hkVector4* capSegment, float capRadius,
                                                                      const hkVector4* triangle, float triRadius,
                                                                      const hkVector4* scaleAndNormal,
                                                                      float extraRadius, int singleCheck,
                                                                      void* out);                          // 0x01107270
extern "C" void*    __cdecl hkCapsuleTriangleAgent3_create(const hkAgent3Input& input, hkAgentEntry* entry,
                                                           void* agentData);                               // 0x010fd060
extern "C" void     __cdecl hkCapsuleTriangleAgent3_destroy(hkAgentEntry* entry, void* agentData,
                                                            hkContactMgr* mgr);                                // 0x010fd0e0
extern "C" void     __cdecl hkCapsuleTriangleAgent3_cleanup(hkAgentEntry* entry, void* agentData);            // 0x010fd0a0
extern "C" void     __cdecl hkCapsuleTriangleAgent3_removePoint(hkAgentEntry* entry, void* agentData,
                                                                hkContactPointId id);                          // 0x010fd010
extern "C" void     __cdecl hkCapsuleTriangleAgent3_commitPotential(hkAgentEntry* entry, void* agentData,
                                                                    hkContactPointId id);                      // 0x010fd040
extern "C" void     __cdecl hkCapsuleTriangleAgent3_sepNormal(const hkAgent3Input& input, void* agentData,
                                                              hkVector4& normal);                              // 0x010fd0f0
extern "C" void*    __cdecl hkBoxBoxAgent3_create(const hkAgent3Input& input, hkAgentEntry* entry,
                                                  void* agentData);                                        // 0x010fdb50
extern "C" void*    __cdecl hkBoxBoxAgent3_destroy(hkAgentEntry* entry, void* agentData, hkContactMgr* mgr);   // 0x010fdb70
extern "C" void     __cdecl hkBoxBoxAgent3_removePoint(hkAgentEntry* entry, void* agentData,
                                                       hkContactPointId id);                                   // 0x010fdae0
extern "C" void     __cdecl hkBoxBoxAgent3_commitPotential(hkAgentEntry* entry, void* agentData,
                                                           hkContactPointId id);                               // 0x010fdb20
extern "C" void*    __cdecl hkBoxBoxAgent3_process(const hkAgent3ProcessInput& input, hkAgentEntry* entry,
                                                   void* agentData, hkVector4* separatingNormal,
                                                   hkProcessCollisionOutput& result);                          // 0x010fdbe0
extern "C" void     __cdecl hkBoxBox_createZombie(hkAgentEntry* entry, void* agentData, hkContactPointId id);  // 0x00c2e4e0
extern "C" void*    __cdecl hkPredGskCylinderAgent3_create(const hkAgent3Input& input, hkAgentEntry* entry,
                                                           void* agentData);                               // 0x010fdf30
extern "C" void*    __cdecl hkGsk_cacheInit(const hkAgent3Input& input, hkAgentEntry* entry, void* cache);      // 0x010ff820

// ---- monitor-stream timer commands (TLS) -------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(__rdtsc)
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char g_hkTimerEndTag0[];               // 0x0143cd94
extern const char g_hkTimerEndTag1[];               // 0x0149cc34

#define HK_TIMER_CMD(name) do { \
    void* end_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end_) { \
        unsigned int* c_ = (unsigned int*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_[0] = (unsigned int)(name); \
        c_[1] = (unsigned int)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 3); } } while (0)

// ============================================================================================================
// @ 0x010fd4c0
void* __cdecl hkCapsuleTriangleAgent3_process(const hkAgent3ProcessInput& input, hkAgentEntry* entry,
                                               void* agentData, hkVector4* separatingNormal,
                                               hkProcessCollisionOutput& result)
{
    HK_TIMER_CMD("TtCapsTri3");

    const hkCdBody* bodyA = input.m_bodyA;
    const hkCdBody* bodyB = input.m_bodyB;
    const hkCapsuleShape*  capsule  = (const hkCapsuleShape*)bodyA->m_shape;
    const hkTriangleShape* triangle = (const hkTriangleShape*)bodyB->m_shape;
    const hkTransform* wTa = bodyA->m_motion;
    const hkTransform* wTb = bodyB->m_motion;

    // capsule segment endpoints in world space
    hkVector4 capSegment[2];
    capSegment[0].x = wTa->m_rotation.c0.x * capsule->m_vertex[0].x
                    + (wTa->m_rotation.c0.y * capsule->m_vertex[0].y
                       + wTa->m_rotation.c0.z * capsule->m_vertex[0].z) + wTa->m_translation.x;
    capSegment[0].y = wTa->m_rotation.c1.x * capsule->m_vertex[0].x
                    + (wTa->m_rotation.c1.y * capsule->m_vertex[0].y
                       + wTa->m_rotation.c1.z * capsule->m_vertex[0].z) + wTa->m_translation.y;
    capSegment[0].z = wTa->m_rotation.c2.x * capsule->m_vertex[0].x
                    + (wTa->m_rotation.c2.y * capsule->m_vertex[0].y
                       + wTa->m_rotation.c2.z * capsule->m_vertex[0].z) + wTa->m_translation.z;
    capSegment[0].w = 0.0f;
    capSegment[1].x = wTa->m_rotation.c0.x * capsule->m_vertex[1].x
                    + (wTa->m_rotation.c0.y * capsule->m_vertex[1].y
                       + wTa->m_rotation.c0.z * capsule->m_vertex[1].z) + wTa->m_translation.x;
    capSegment[1].y = wTa->m_rotation.c1.x * capsule->m_vertex[1].x
                    + (wTa->m_rotation.c1.y * capsule->m_vertex[1].y
                       + wTa->m_rotation.c1.z * capsule->m_vertex[1].z) + wTa->m_translation.y;
    capSegment[1].z = wTa->m_rotation.c2.x * capsule->m_vertex[1].x
                    + (wTa->m_rotation.c2.y * capsule->m_vertex[1].y
                       + wTa->m_rotation.c2.z * capsule->m_vertex[1].z) + wTa->m_translation.z;
    capSegment[1].w = 0.0f;

    // triangle vertices in world space
    hkVector4 tri[3];
    tri[0].x = wTb->m_rotation.c0.x * triangle->m_vertex[0].x
             + (wTb->m_rotation.c0.y * triangle->m_vertex[0].y
                + wTb->m_rotation.c0.z * triangle->m_vertex[0].z) + wTb->m_translation.x;
    tri[0].y = wTb->m_rotation.c1.x * triangle->m_vertex[0].x
             + (wTb->m_rotation.c1.y * triangle->m_vertex[0].y
                + wTb->m_rotation.c1.z * triangle->m_vertex[0].z) + wTb->m_translation.y;
    tri[0].z = wTb->m_rotation.c2.x * triangle->m_vertex[0].x
             + (wTb->m_rotation.c2.y * triangle->m_vertex[0].y
                + wTb->m_rotation.c2.z * triangle->m_vertex[0].z) + wTb->m_translation.z;
    tri[0].w = 0.0f;
    tri[1].x = wTb->m_rotation.c0.x * triangle->m_vertex[1].x
             + (wTb->m_rotation.c0.y * triangle->m_vertex[1].y
                + wTb->m_rotation.c0.z * triangle->m_vertex[1].z) + wTb->m_translation.x;
    tri[1].y = wTb->m_rotation.c1.x * triangle->m_vertex[1].x
             + (wTb->m_rotation.c1.y * triangle->m_vertex[1].y
                + wTb->m_rotation.c1.z * triangle->m_vertex[1].z) + wTb->m_translation.y;
    tri[1].z = wTb->m_rotation.c2.x * triangle->m_vertex[1].x
             + (wTb->m_rotation.c2.y * triangle->m_vertex[1].y
                + wTb->m_rotation.c2.z * triangle->m_vertex[1].z) + wTb->m_translation.z;
    tri[1].w = 0.0f;
    tri[2].x = wTb->m_rotation.c0.x * triangle->m_vertex[2].x
             + (wTb->m_rotation.c0.y * triangle->m_vertex[2].y
                + wTb->m_rotation.c0.z * triangle->m_vertex[2].z) + wTb->m_translation.x;
    tri[2].y = wTb->m_rotation.c1.x * triangle->m_vertex[2].x
             + (wTb->m_rotation.c1.y * triangle->m_vertex[2].y
                + wTb->m_rotation.c1.z * triangle->m_vertex[2].z) + wTb->m_translation.y;
    tri[2].z = wTb->m_rotation.c2.x * triangle->m_vertex[2].x
             + (wTb->m_rotation.c2.y * triangle->m_vertex[2].y
                + wTb->m_rotation.c2.z * triangle->m_vertex[2].z) + wTb->m_translation.z;
    tri[2].w = 0.0f;

    // 3 contact points, 0x20 bytes each (position, separating normal)
    hkProcessCdPoint points[3];
    hkCollideCapsuleUtilManifoldCapsVsTriangle(capSegment, capsule->m_radius, tri, triangle->m_radius,
                                               &input.m_aTb.m_rotation.c2, 0x7f7fffee, 1, points);

    // pick the deepest of the first two contacts as the separating normal
    int numPoints = 0;
    if (points[0].m_separatingNormal.w <= points[1].m_separatingNormal.w)
    {
        separatingNormal->x = points[1].m_separatingNormal.x;
        separatingNormal->y = points[1].m_separatingNormal.y;
        separatingNormal->z = points[1].m_separatingNormal.z;
        separatingNormal->w = points[1].m_separatingNormal.w;
        numPoints = 1;
    }
    else
    {
        separatingNormal->x = points[0].m_separatingNormal.x;
        separatingNormal->y = points[0].m_separatingNormal.y;
        separatingNormal->z = points[0].m_separatingNormal.z;
        separatingNormal->w = points[0].m_separatingNormal.w;
    }

    hkContactPointId ids[3];
    ids[0] = ((const hkContactPointId*)agentData)[0];
    ids[1] = ((const hkContactPointId*)agentData)[1];
    ids[2] = ((const hkContactPointId*)agentData)[2];

    hkContactMgr* contactMgr = input.m_contactMgr;
    const float tolerance = input.m_input->m_tolerance;

    for (int i = 0; i < 3; ++i)
    {
        hkProcessCdPoint* cp = &points[i];
        if (tolerance <= cp->m_separatingNormal.w)
        {
            // point is too far away: drop the cached one
            if (ids[i] != 0xffff)
                contactMgr->removeContactPoint(ids[i]);
            ids[i] = 0xffff;
            continue;
        }

        hkContactPointId id = ids[i];
        if (id == 0xffff)
        {
            if (result.m_potentialContacts)
            {
                if (contactMgr->reserveContactPoints(1) != 0)
                {
                    ids[i] = 0xffff;
                    continue;
                }
                hkPendingContact* pending = result.m_potentialContacts;
                result.m_potentialContacts = pending + 1;
                hkProcessCdPoint* resume = result.m_firstFreeContactPoint;
                pending->m_entry     = entry;
                pending->m_contact   = &resume;
                pending->m_agentData = agentData;
                id = 0xffff;
            }
            else
            {
                id = contactMgr->addContactPoint(*bodyA, *bodyB, *(const hkCollisionInput*)input.m_input, *cp);
                if (id == 0xffff)
                {
                    ids[i] = 0xffff;
                    continue;
                }
            }
        }

        hkProcessCdPoint* out = result.m_firstFreeContactPoint;
        result.m_firstFreeContactPoint = out + 1;
        out->m_position         = cp->m_position;
        out->m_separatingNormal = cp->m_separatingNormal;
        out->m_contactPointId   = id;

        if (i == numPoints && result.m_potentialContacts)
        {
            *result.m_potentialContacts->m_contact = out;
            result.m_potentialContacts = (hkPendingContact*)((char*)result.m_potentialContacts + 4);
        }
        ids[i] = id;
    }

    ((hkContactPointId*)agentData)[0] = ids[0];
    ((hkContactPointId*)agentData)[1] = ids[1];
    ((hkContactPointId*)agentData)[2] = ids[2];
    entry->m_numContactPoints = (unsigned char)numPoints;

    HK_TIMER_CMD(g_hkTimerEndTag1);
    return (char*)agentData + 0x20;
}

// ============================================================================================================
// @ 0x010fda70
void __cdecl hkCapsuleTriangleAgent3_register(hkCollisionDispatcher* dispatcher)
{
    const int typeA = 8;
    const int typeB = 6;
    hkCollisionDispatcher::Agent3Funcs funcs;
    funcs.m_createFunc          = (void* (*)())&hkCapsuleTriangleAgent3_create;
    funcs.m_destroyFunc         = (void (*)())&hkCapsuleTriangleAgent3_destroy;
    funcs.m_cleanupFunc         = (void (*)())&hkCapsuleTriangleAgent3_cleanup;
    funcs.m_removePointFunc     = (void (*)())&hkCapsuleTriangleAgent3_removePoint;
    funcs.m_commitPotentialFunc = (void (*)())&hkCapsuleTriangleAgent3_commitPotential;
    funcs.m_createZombieFunc    = (void (*)())&hkBoxBox_createZombie;
    funcs.m_updateFilterFunc    = 0;
    funcs.m_invalidateTimFunc   = 0;
    funcs.m_warpTimeFunc        = 0;
    funcs.m_sepNormalFunc       = (void (*)())&hkCapsuleTriangleAgent3_sepNormal;
    funcs.m_processFunc         = (void* (*)())&hkCapsuleTriangleAgent3_process;
    funcs.m_isPredictive        = hkBool(false);
    funcs.m_ignoreSymmetricVersion = hkBool(false);
    dispatcher->registerAgent3(funcs, typeA, typeB);
}

// ============================================================================================================
// @ 0x010fdae0
void __cdecl hkBoxBoxAgent3_removePoint(hkAgentEntry* entry, void* agentData, hkContactPointId id)
{
    hkBoxBoxManifold* manifold = (hkBoxBoxManifold*)agentData;
    int n = manifold->m_numPoints;
    for (int i = 0; i < n; ++i)
    {
        if (manifold->m_contactPoints[i].m_contactPointId == id)
        {
            manifold->removePoint(i);
            entry->m_numContactPoints = (unsigned char)(entry->m_numContactPoints - 1);
            return;
        }
    }
}

// ============================================================================================================
// @ 0x010fdb20
void __cdecl hkBoxBoxAgent3_commitPotential(hkAgentEntry* entry, void* agentData, hkContactPointId id)
{
    (void)entry;
    hkBoxBoxManifold* manifold = (hkBoxBoxManifold*)agentData;
    const int n = manifold->m_numPoints;
    for (int i = 0; i < n; ++i)
    {
        if (manifold->m_contactPoints[i].m_contactPointId == 0xffff)
        {
            manifold->m_contactPoints[i].m_contactPointId = id;
            break;
        }
    }
}

// ============================================================================================================
// @ 0x010fdb50
void* __cdecl hkBoxBoxAgent3_create(const hkAgent3Input& input, hkAgentEntry* entry, void* agentData)
{
    hkBoxBoxManifold* manifold = (hkBoxBoxManifold*)agentData;
    if (manifold)
        manifold->init();
    return (char*)manifold + 0x50;
}

// ============================================================================================================
// @ 0x010fdb70
void* __cdecl hkBoxBoxAgent3_destroy(hkAgentEntry* entry, void* agentData, hkContactMgr* mgr)
{
    hkBoxBoxManifold* manifold = (hkBoxBoxManifold*)agentData;
    for (unsigned int i = 0; i < manifold->m_numPoints; ++i)
    {
        hkContactPointId id = manifold->m_contactPoints[i].m_contactPointId;
        if (id != 0xffff)
            mgr->removeContactPoint(id);
    }
    manifold->m_numPoints = 0;
    entry->m_numContactPoints = 0;
    return (char*)manifold + 0x50;
}

// ============================================================================================================
// @ 0x010fdbe0
void* __cdecl hkBoxBoxAgent3_process(const hkAgent3ProcessInput& input, hkAgentEntry* entry,
                                     void* agentData, hkVector4* separatingNormal,
                                     hkProcessCollisionOutput& result)
{
    (void)separatingNormal;
    HK_TIMER_CMD("TtBoxBox3");

    const hkCdBody* bodyA = input.m_bodyA;
    const hkCdBody* bodyB = input.m_bodyB;
    const hkShape*  shapeA = bodyA->m_shape;
    const hkShape*  shapeB = bodyB->m_shape;

    hkBoxBoxCollisionDetection cd;
    cd.m_bodyA = bodyA;
    cd.m_bodyB = bodyB;
    cd.m_env = (const hkCollisionInput*)input.m_input;
    cd.m_contactMgr = input.m_contactMgr;
    cd.m_result = &result;
    cd.m_wTa = bodyA->m_motion;
    cd.m_wTb = bodyB->m_motion;

    // bounding radii of both boxes in the same frame
    hkVector4 radiusA, radiusB;
    radiusA.x = shapeA->m_radius + bodyA->m_motion->m_translation.x;
    radiusA.y = shapeA->m_radius + bodyA->m_motion->m_translation.y;
    radiusA.z = shapeA->m_radius + bodyA->m_motion->m_translation.z;
    radiusA.w = shapeA->m_radius + bodyA->m_motion->m_translation.w;
    radiusB.x = shapeB->m_radius + bodyB->m_motion->m_translation.x;
    radiusB.y = shapeB->m_radius + bodyB->m_motion->m_translation.y;
    radiusB.z = shapeB->m_radius + bodyB->m_motion->m_translation.z;
    radiusB.w = shapeB->m_radius + bodyB->m_motion->m_translation.w;
    (void)radiusB;

    cd.m_tolerance = 0.01f;

    hkBoxBoxManifold* manifold = (hkBoxBoxManifold*)agentData;
    cd.calcManifold(*manifold);

    entry->m_numContactPoints = manifold->m_numPoints;

    HK_TIMER_CMD(g_hkTimerEndTag1);
    return (char*)manifold + 0x50;
}

// ============================================================================================================
// @ 0x010fdec0
void __cdecl hkBoxBoxAgent3_register(hkCollisionDispatcher* dispatcher)
{
    hkCollisionDispatcher::Agent3Funcs funcs;
    funcs.m_createFunc          = (void* (*)())&hkBoxBoxAgent3_create;
    funcs.m_destroyFunc         = (void (*)())&hkBoxBoxAgent3_destroy;
    funcs.m_cleanupFunc         = 0;
    funcs.m_removePointFunc     = (void (*)())&hkBoxBoxAgent3_removePoint;
    funcs.m_commitPotentialFunc = (void (*)())&hkBoxBoxAgent3_commitPotential;
    funcs.m_createZombieFunc    = (void (*)())&hkBoxBox_createZombie;
    funcs.m_updateFilterFunc    = 0;
    funcs.m_invalidateTimFunc   = 0;
    funcs.m_warpTimeFunc        = 0;
    funcs.m_sepNormalFunc       = 0;
    funcs.m_processFunc         = (void* (*)())&hkBoxBoxAgent3_process;
    funcs.m_isPredictive        = hkBool(false);
    funcs.m_ignoreSymmetricVersion = hkBool(false);
    dispatcher->registerAgent3(funcs, 7, 7);
}

// ============================================================================================================
// @ 0x010fdf30
void* __cdecl hkPredGskCylinderAgent3_create(const hkAgent3Input& input, hkAgentEntry* entry, void* agentData)
{
    ((unsigned int*)entry)[1] = 0;
    if (((const hkShape*)input.m_bodyA->m_shape)->getType() == 5)
        ((unsigned int*)entry)[1] |= 1;
    if (((const hkShape*)input.m_bodyB->m_shape)->getType() == 5)
        ((unsigned int*)entry)[1] |= 2;
    return hkGsk_cacheInit(input, entry, agentData);
}
