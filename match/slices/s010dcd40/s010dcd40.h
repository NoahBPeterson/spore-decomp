// Havok 3.1.0 (statically linked into SporeApp.exe) -- collision agents slice s010dcd40.
// Class stubs: members at the offsets seen in the 32-bit binary; names follow the dev-build PDB mangling
// and the Havok 6.x headers (hkX == hkpX).  Pointers are real pointers, so struct sizes differ on 64-bit
// (the *behaviour* is what is ported); fixed-width types are used for everything that is not a pointer.
#pragma once
#include "types.h"
#include <stddef.h>
#include <intrin.h>

typedef float hkReal;
typedef float hkTime;
typedef uint16_t hkContactPointId;
typedef uint8_t hkBool;

// HK_REAL_MAX in this build: 3.40282e+38f == 0x7f7fffee (NOT FLT_MAX).
#define HK_REAL_MAX 3.40282e+38f

struct hkVector4 { float x, y, z, w; };
struct hkTransform {
    hkVector4 m_rot[3];
    hkVector4 m_trans;
    void setMulInverseMul(const hkTransform& a, const hkTransform& b);   // this = inverse(a) * b
};
// hkContactPoint: position (0x00), separating normal xyz + distance w (0x10)
struct hkContactPoint {
    hkVector4 m_position;
    hkVector4 m_separatingNormal;   // w = distance
    void setFlipped(const hkContactPoint& other);
};
struct hkProcessCdPoint { hkContactPoint m_contact; uint32_t m_extra[4]; };   // 0x30 bytes

// ---- reference counted base --------------------------------------------------------------------
struct hkReferencedObject {
    virtual void* hkReferencedObject_deletingDtor(unsigned int flags);   // vtable slot 0 (scalar deleting destructor)
    uint16_t m_memSizeAndFlags;
    int16_t  m_referenceCount;
};

// ---- memory manager (hkMemory::s_instance @ 0x016e4178, allocateChunk = vtable slot 4) ---------------
struct hkMemory {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void* allocateChunk(int nbytes, int memClass);
    static hkMemory* s_instance;
};
enum { HK_MEMORY_CLASS_COLLIDE = 0x1c };
// HK_DECLARE_CLASS_ALLOCATOR: allocateChunk(size, COLLIDE), then m_memSizeAndFlags = size (before the ctor runs).
#define HK_DECLARE_AGENT_ALLOCATOR \
    void* operator new(size_t n) { \
        void* p = hkMemory::s_instance->allocateChunk((int)n, HK_MEMORY_CLASS_COLLIDE); \
        ((hkReferencedObject*)p)->m_memSizeAndFlags = (uint16_t)n; return p; } \
    void operator delete(void*) {}

// ---- shapes ---------------------------------------------------------------------------------------
struct hkCdVertex { float x, y, z; union { float w; uint32_t wBits; }; };
struct hkSphere { hkVector4 m_pos; };                                          // 16 bytes
struct hkCollisionSpheresInfo { int m_numSpheres; hkBool m_useBuffer; };      // hkSphereRepShape::hkCollisionSpheresInfo

struct hkShape : hkReferencedObject {
    uint32_t m_userData;                       // +8
};
// vtable slots: 0 dtor .. 6 placeholders; 7 getCollisionSpheresInfo; 8 getCollisionSpheres;
// hkConvexShape: 9 getSupportingVertex; 10 convertVertexIdsToVertices; 11 getFirstVertex
struct hkConvexShape : hkShape {
    float m_radius;                            // +0xc
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const;
    virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;
    virtual void getSupportingVertex(const hkVector4& dir, hkCdVertex& supportingVertexOut) const;
    virtual void convertVertexIdsToVertices(const uint16_t* ids, int numIds, hkCdVertex* verticesOut) const;
    virtual void getFirstVertex(hkVector4& v) const;
};
struct hkConvexShapeRef { hkConvexShape* m_shape; uint32_t m_unknown; };      // 8-byte array element (stride 8 in the binary)
struct hkConvexListShape;
struct hkConvexListConvexShape : hkConvexShape {
    hkConvexShapeRef* m_subShapesData;         // +0x10
    int m_subShapesSize;                       // +0x14
    hkConvexListConvexShape() {}
    inline hkConvexListConvexShape(const hkConvexListShape& list);                 // temp view used by the agents
    virtual void getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const;
    virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;
    virtual void getSupportingVertex(const hkVector4& dir, hkCdVertex& supportingVertexOut) const;
    virtual void convertVertexIdsToVertices(const uint16_t* ids, int numIds, hkCdVertex* verticesOut) const;
    virtual void getFirstVertex(hkVector4& v) const;
};
struct hkConvexListShape : hkConvexListConvexShape {
    int m_subShapesCapacity;                   // +0x18
    float m_minDistanceToUseConvexHullForGsk;  // +0x1c
};
inline hkConvexListConvexShape::hkConvexListConvexShape(const hkConvexListShape& list)
{
    m_userData = 0;
    m_referenceCount = 1;
    m_radius = list.m_subShapesData[0].m_shape->m_radius;
    m_subShapesData = list.m_subShapesData;
    m_subShapesSize = list.m_subShapesSize;
}

// ---- bodies / inputs / collectors -------------------------------------------------------------------
struct hkCdBody {
    const hkShape* m_shape;                    // +0
    uint32_t m_shapeKey;                       // +4
    const hkTransform* m_motion;               // +8
    const hkCdBody* m_parent;                  // +0xc
};
struct hkCollisionDispatcher;
struct hkCollisionInput {
    hkCollisionDispatcher* m_dispatcher;       // +0
    uint32_t m_pad[3];
};
struct hkProcessCollisionInput : hkCollisionInput {};
struct hkLinearCastCollisionInput : hkCollisionInput {
    hkVector4 m_path;                          // +0x10
    uint32_t m_pad2[4];                        // total 0x30 bytes (12 dwords copied by the symmetric agent)
};

struct hkCdPoint { hkContactPoint m_contact; const hkCdBody* m_cdBodyA; const hkCdBody* m_cdBodyB; };

struct hkCdPointCollector {
    virtual void hkCdPointCollector_v0();
    virtual void addCdPoint(const hkCdPoint& point);
    float m_earlyOutDistance;                  // +4
};
struct hkCdBodyPairCollector {
    virtual void hkCdBodyPairCollector_v0();
    virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b);
    hkBool m_earlyOut;                         // +4
};
struct hkContactMgr;

struct hkProcessCollisionOutput {
    hkProcessCdPoint* m_firstFreeContactPoint; // +0
    uint32_t m_pad0[3];
    hkContactPoint m_toiContact;               // +0x10 (position, normal+distance)
    hkProcessCdPoint m_contactPoints[256];     // +0x30
    uint32_t m_toiProperties;                  // +0x3030
    hkTime   m_toiTime;                        // +0x3034
    uint32_t m_pad1[2];
    uint32_t* m_potentialContacts;             // +0x3040 (0x1008 bytes copied by the backup)
};

// ---- Havok monitor stream (timers).  TLS slot @0x016e42a4 = current write pointer, @0x016e42a8 = end.
// The binary stores 12/16 byte commands; the profiler stream is only a debug aid, so struct sizes follow
// pointer size on 64-bit.  rdtsc keeps the low 32 bits only (as in the binary).
#ifdef _WIN32
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
#endif
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorEndTag[];                // string at 0x00143cd94
struct hkMonitorCommand { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_pad; };   // 12 bytes (32-bit)
struct hkMonitorCommand2 { hkMonitorCommand m_first; const char* m_secondCommand; };               // 16 bytes (32-bit)
#define HK_TIMER_BEGIN_LIST(a, b) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand2* c_ = (hkMonitorCommand2*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_first.m_commandAndMonitor = a; c_->m_secondCommand = b; \
        c_->m_first.m_time0 = (uint32_t)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_SPLIT_LIST(name) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_commandAndMonitor = name; \
        c_->m_time0 = (uint32_t)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_END_LIST() HK_TIMER_SPLIT_LIST(hkMonitorEndTag)

// ---- collision agents -----------------------------------------------------------------------------------
struct hkGskCache {
    uint32_t m_pad[3];                         // 12 bytes
    void init(const hkConvexShape* shapeA, const hkConvexShape* shapeB, const hkTransform& aTb);
};
struct hkGskManifold {
    uint8_t m_numVertsA, m_numVertsB, m_numContactPoints, m_pad;
    struct ContactPoint { uint8_t m_dimA, m_dimB; hkContactPointId m_id; uint32_t m_allVerts; } m_contactPoints[4];
    uint8_t m_padding[32];
};

struct hkCollisionAgent : hkReferencedObject {
    hkContactMgr* m_contactMgr;                // +8
    virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);
    virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6();
    virtual void invalidateTim(hkCollisionInput& input);
    virtual void warpTime(hkTime oldTime, hkTime newTime, hkCollisionInput& input);
    virtual void cleanup();
    virtual void removePoint(hkContactPointId id);
    virtual void commitPotential(hkContactPointId id);
    virtual void createZombie(hkContactPointId id);
};
struct hkHeightFieldAgent : hkCollisionAgent {
    uint32_t m_pad[3];                         // object size 0x18
    hkHeightFieldAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);
    virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);
};
struct hkGskBaseAgent : hkCollisionAgent {
    hkGskCache m_cache;                        // +0xc
    hkTime m_timeOfSeparatingNormal;           // +0x18
    hkReal m_allowedPenetration;               // +0x1c
    hkVector4 m_separatingNormal;              // +0x20  (w = -1 when invalid)
    HK_DECLARE_AGENT_ALLOCATOR
    hkGskBaseAgent(const hkCdBody& a, const hkCdBody& b, hkContactMgr* mgr);
    virtual void invalidateTim(hkCollisionInput& input);
    virtual void warpTime(hkTime oldTime, hkTime newTime, hkCollisionInput& input);
    static void staticGetPenetrations(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkCdBodyPairCollector& c);
    static void staticGetClosestPoints(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkCdPointCollector& c);
    static void staticLinearCast(const hkCdBody& a, const hkCdBody& b, const hkLinearCastCollisionInput& input, hkCdPointCollector& c, hkCdPointCollector* start);   // 0x010ebc80 (equiv t2)
};
struct hkGskfAgent : hkGskBaseAgent {
    hkGskManifold m_manifold;                  // +0x30
    virtual void removePoint(hkContactPointId id);
    virtual void commitPotential(hkContactPointId id);
    virtual void createZombie(hkContactPointId id);
};
struct hkPredGskfAgent : hkGskfAgent {
    uint32_t m_pad2[3];                        // up to 0x80
    hkPredGskfAgent(const hkCdBody& a, const hkCdBody& b, hkContactMgr* mgr);
};
