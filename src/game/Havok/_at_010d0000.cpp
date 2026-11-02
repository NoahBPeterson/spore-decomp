// src/game/Havok/_at_010d0000.cpp -- migrated from slice(s) s010df100, s010dcd40, s010d6420, s010d53d0, s010d4730, s010d37d0, s010d28c0, s010d18c0, s010d0920, s010cfcf0 by tools/migrate/rewrite.py
// Object file: Havok/_at_010d0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorTimerEndTag[];           // 0x0149cc34 ("Et")
extern const char hkTtMultiSphereTri[];             // 0x014a4570 ("TtMultiSphereTri")
extern void* g_hkMemoryInstance;                 // 0x016e4178
#include <intrin.h>
#include <stddef.h>
#pragma intrinsic(__rdtsc)

// ---- items of slice s010cfcf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorTimerEndTag[];           // 0x0149cc34 ("Et")
extern const char hkTtMultiSphereTri[];             // 0x014a4570 ("TtMultiSphereTri")
struct hkMonitorCommand { const char* m_command; uint32_t m_time0; uint32_t m_pad; };
static __forceinline void hkTimerCommand(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end)
    {
        hkMonitorCommand* c = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        c->m_command = name;
        volatile uint32_t t = (uint32_t)__rdtsc();
        c->m_time0 = t;
        TlsSetValue(g_hkMonitorStreamCurrentTls, c + 1);
    }
}
class __declspec(align(16)) hkVector4_s010c_fcf0 { public: float x, y, z, w; };
class hkTransform_s010c_fcf0 { public: hkVector4_s010c_fcf0 m_col0, m_col1, m_col2, m_translation; };   // 0x40 bytes
class hkShape_s010c_fcf0 {  // 0xc bytes
    public: virtual ~hkShape_s010c_fcf0();
    int m_pad[2];
};
class hkConvexShape : public hkShape_s010c_fcf0 { public: float m_radius; };                                              // radius +0xc
class hkTriangleShape : public hkConvexShape { public: hkVector4_s010c_fcf0 m_vertices[3]; };                              // vertices +0x10
struct hkMultiSphereShape : hkShape_s010c_fcf0 { int m_numSpheres; hkVector4_s010c_fcf0 m_spheres[8]; };               // count +0xc, spheres +0x10
class hkCdBody_s010c_fcf0
{
public:
    const hkShape_s010c_fcf0* m_shape;        // +0
    unsigned       m_shapeKey;     // +4
    const hkTransform_s010c_fcf0* m_motion;   // +8
    const hkCdBody_s010c_fcf0* m_parent;      // +0xc
};
struct hkCollisionInput_s010c_fcf0 { int pad[2]; float m_tolerance; };   // tolerance +8
class hkContactPoint_s010c_fcf0 { public: hkVector4_s010c_fcf0 m_position; hkVector4_s010c_fcf0 m_separatingNormal;
    void FUN_010d0040(const hkVector4_s010c_fcf0& normal, float w);   // w = distance
    void setFlipped(const hkContactPoint_s010c_fcf0& other); };       // 0x010cecf0
struct hkCollideTriangleUtil
{
    struct ClosestPointTriangleCache { float m_QQ, m_RR, m_QR, m_invTriNormal; };
    struct ClosestPointTriangleResult { hkVector4_s010c_fcf0 hitDirection; float distance; };
    enum ClosestPointTriangleStatus { HIT_TRIANGLE_FACE = 0, HIT_TRIANGLE_EDGE };
    static void __cdecl setupClosestPointTriangleCache(const hkVector4_s010c_fcf0* triangle, ClosestPointTriangleCache& cache);   // 0x01105d80
    static ClosestPointTriangleStatus __cdecl closestPointTriangle(const hkVector4_s010c_fcf0& position, const hkVector4_s010c_fcf0* tri,
        const ClosestPointTriangleCache& cache, ClosestPointTriangleResult& result);                                     // 0x01106010
};
#define HK_XFORM_ONE(O, I) { \
        const float x = (I).x, y = (I).y, z = (I).z; \
        (O).x = (m00 * x + (m10 * y + m20 * z)) + tx; \
        (O).y = (m01 * x + (m11 * y + m21 * z)) + ty; \
        (O).z = (m02 * x + (m12 * y + m22 * z)) + tz; \
        (O).w = 0.0f; }
static __forceinline void transformPoints(const hkTransform_s010c_fcf0& t, const hkVector4_s010c_fcf0* in, int n, hkVector4_s010c_fcf0* out)
{
    const float m00 = t.m_col0.x, m01 = t.m_col0.y, m02 = t.m_col0.z;
    const float m10 = t.m_col1.x, m11 = t.m_col1.y, m12 = t.m_col1.z;
    const float m20 = t.m_col2.x, m21 = t.m_col2.y, m22 = t.m_col2.z;
    const float tx = t.m_translation.x, ty = t.m_translation.y, tz = t.m_translation.z;
    int i = 0;
    if (n >= 4)
    {
        int blocks = ((n - 4) >> 2) + 1;
        i = blocks * 4;
        const hkVector4_s010c_fcf0* p = in;
        hkVector4_s010c_fcf0* q = out;
        do {
            HK_XFORM_ONE(q[0], p[0]) HK_XFORM_ONE(q[1], p[1]) HK_XFORM_ONE(q[2], p[2]) HK_XFORM_ONE(q[3], p[3])
            p += 4; q += 4;
        } while (--blocks);
    }
    for (; i < n; ++i)
        HK_XFORM_ONE(out[i], in[i])
}
typedef unsigned short hkContactPointId;
struct hkProcessCollisionInput_s010c_fcf0 : hkCollisionInput_s010c_fcf0 { };
struct hkProcessCdPoint { hkContactPoint_s010c_fcf0 m_contact; hkContactPointId m_id; char m_pad[14]; };   // 0x30 bytes
struct hkProcessCollisionOutput
{
    hkProcessCdPoint* m_firstFreeContactPoint;       // +0x00
    char              m_padding4[0x1c];              // +0x04
    float             m_separatingNormal[3];         // +0x20
    char              m_padding2c[0x3008];           // +0x2c
    float             m_cachedDistance;              // +0x3034
};
class hkContactMgr
{
public:
    virtual void pad0();
    virtual void pad1();
    virtual hkContactPointId addContactPoint(const hkCdBody_s010c_fcf0& a, const hkCdBody_s010c_fcf0& b, const hkProcessCollisionInput_s010c_fcf0& input,
                                             hkProcessCdPoint& cp);                  // +0x08
    virtual void pad3();
    virtual void removeContactPoint(hkContactPointId id);                            // +0x10
};
class hkMultiSphereTriangleAgent
{
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void processCollision(const hkCdBody_s010c_fcf0& bodyA, const hkCdBody_s010c_fcf0& bodyB, const hkProcessCollisionInput_s010c_fcf0& input,
                                  hkProcessCollisionOutput& result);                   // 0x010d0130
    int                m_pad4;                                                         // +4 refcount
    hkContactMgr*      m_contactMgr;                                                   // +8
    hkCollideTriangleUtil::ClosestPointTriangleCache m_closestPointTriangleCache;     // +0xc
    hkContactPointId   m_contactPointId[8];                                            // +0x1c
};
extern void* g_hkMemoryInstance;                 // 0x016e4178
class hkMemory
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void* allocate(int size, int alignment);         // +0x10
    virtual void  deallocate(void* ptr, int size, int alignment);   // +0x14
};
class hkAgentBase
{
public:
    virtual void destroy(int flags);                         // vtable slot 0
};
void __cdecl FUN_01105d80(const hkVector4_s010c_fcf0* triangle, void* cache);
struct hkAgent44
{
    void*    m_vtable;           // +0x00
    uint16_t m_size;             // +0x04
    uint16_t m_flags;            // +0x06
    void*    m_contactMgr;       // +0x08
    char     m_cache[0x10];      // +0x0c
    uint32_t m_id1c;             // +0x1c
    uint32_t m_id20;             // +0x20
    uint32_t m_id24;             // +0x24
    uint32_t m_id28;             // +0x28
};
// ---- items of slice s010cfcf0 end

// ---- items of slice s010d0920 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char hkTtMultiSphereTriangle[];        // 0x014a4584 ("TtMultiSphereTriangle")
class __declspec(align(16)) hkVector4_s010d_0920 { public: float x, y, z, w; };
class hkTransform_s010d_0920 { public: hkVector4_s010d_0920 m_col0, m_col1, m_col2, m_translation; };   // 0x40 bytes
class hkShape_s010d_0920 {  // 0xc bytes
    public: virtual ~hkShape_s010d_0920();
    int m_pad[2];
};
class hkConvexShape_s010d_0920 : public hkShape_s010d_0920 { public: float m_radius; };                                              // radius +0xc
class hkTriangleShape_s010d_0920 : public hkConvexShape_s010d_0920 { public: hkVector4_s010d_0920 m_vertices[3]; };                              // vertices +0x10
struct hkMultiSphereShape_s010d_0920 : hkShape_s010d_0920 { int m_numSpheres; hkVector4_s010d_0920 m_spheres[8]; };               // count +0xc, spheres +0x10
class hkCdBody_s010d_0920
{
public:
    const hkShape_s010d_0920* m_shape;        // +0
    unsigned       m_shapeKey;     // +4
    const hkTransform_s010d_0920* m_motion;   // +8
    const hkCdBody_s010d_0920* m_parent;      // +0xc
};
struct hkCollisionInput_s010d_0920 { int pad[2]; float m_tolerance; };   // tolerance +8
class hkContactPoint_s010d_0920 { public: hkVector4_s010d_0920 m_position; hkVector4_s010d_0920 m_separatingNormal; };   // w = distance
struct hkCdPoint { hkContactPoint_s010d_0920 m_contact; const hkCdBody_s010d_0920* m_cdBodyA; const hkCdBody_s010d_0920* m_cdBodyB; };   // 0x28 bytes
class hkCdPointCollector_s010d_0920
{
public:
    virtual ~hkCdPointCollector_s010d_0920() {}
    virtual void addCdPoint(const hkCdPoint& point) = 0;                     // slot 1
    float m_earlyOutDistance;
};
struct hkCollideTriangleUtil_s010d_0920
{
    struct ClosestPointTriangleCache { float m_QQ, m_RR, m_QR, m_invTriNormal; };
    struct ClosestPointTriangleResult { hkVector4_s010d_0920 hitDirection; float distance; };
    enum ClosestPointTriangleStatus { HIT_TRIANGLE_FACE = 0, HIT_TRIANGLE_EDGE };
    static void __cdecl setupClosestPointTriangleCache(const hkVector4_s010d_0920* triangle, ClosestPointTriangleCache& cache);   // 0x01105d80
    static ClosestPointTriangleStatus __cdecl closestPointTriangle(const hkVector4_s010d_0920& position, const hkVector4_s010d_0920* tri,
        const ClosestPointTriangleCache& cache, ClosestPointTriangleResult& result);                                     // 0x01106010
};
static __forceinline void transformPoints_s010d_0920(const hkTransform_s010d_0920& t, const hkVector4_s010d_0920* in, int n, hkVector4_s010d_0920* out)
{
    const float m00 = t.m_col0.x, m01 = t.m_col0.y, m02 = t.m_col0.z;
    const float m10 = t.m_col1.x, m11 = t.m_col1.y, m12 = t.m_col1.z;
    const float m20 = t.m_col2.x, m21 = t.m_col2.y, m22 = t.m_col2.z;
    const float tx = t.m_translation.x, ty = t.m_translation.y, tz = t.m_translation.z;
    int i = 0;
    if (n >= 4)
    {
        int blocks = ((n - 4) >> 2) + 1;
        i = blocks * 4;
        const hkVector4_s010d_0920* p = in;
        hkVector4_s010d_0920* q = out;
        do {
            HK_XFORM_ONE(q[0], p[0]) HK_XFORM_ONE(q[1], p[1]) HK_XFORM_ONE(q[2], p[2]) HK_XFORM_ONE(q[3], p[3])
            p += 4; q += 4;
        } while (--blocks);
    }
    for (; i < n; ++i)
        HK_XFORM_ONE(out[i], in[i])
}
class hkMultiSphereTriangleAgent_s010d_0920
{
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void getClosestPoints(const hkCdBody_s010d_0920& bodyA, const hkCdBody_s010d_0920& bodyB, const hkCollisionInput_s010d_0920& input,
                                  hkCdPointCollector_s010d_0920& collector);                          // 0x010d0920
    static void staticGetClosestPoints(const hkCdBody_s010d_0920& bodyA, const hkCdBody_s010d_0920& bodyB, const hkCollisionInput_s010d_0920& input,
                                       hkCdPointCollector_s010d_0920& collector);                     // 0x010d1100
    int m_pad[2];                                                                          // +4 refcount, +8 contactMgr
    hkCollideTriangleUtil_s010d_0920::ClosestPointTriangleCache m_closestPointTriangleCache;         // +0xc
};
#define HK_REPORT_CLOSEST(SPH, I, CACHE) \
    { \
        volatile float radiusSum = sphereShapeA->m_spheres[I].w + triangleShapeB->m_radius; \
        hkCollideTriangleUtil_s010d_0920::closestPointTriangle(SPH[I], vertices, CACHE, result); \
        if (radiusSum + input.m_tolerance > result.distance) \
        { \
            const float k = triangleShapeB->m_radius - result.distance; \
            point.m_contact.m_position.x = result.hitDirection.x * k + SPH[I].x; \
            point.m_contact.m_position.y = result.hitDirection.y * k + SPH[I].y; \
            point.m_contact.m_position.z = result.hitDirection.z * k + SPH[I].z; \
            point.m_contact.m_position.w = result.hitDirection.w * k + SPH[I].w; \
            point.m_contact.m_separatingNormal.x = result.hitDirection.x; \
            point.m_contact.m_separatingNormal.y = result.hitDirection.y; \
            point.m_contact.m_separatingNormal.z = result.hitDirection.z; \
            point.m_contact.m_separatingNormal.w = result.distance - radiusSum; \
            collector.addCdPoint(point); \
        } \
    }
// ---- items of slice s010d0920 end

// ---- items of slice s010d18c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class __declspec(align(16)) hkVector4_s010d_18c0 { public: float x, y, z, w; };
class hkTransform_s010d_18c0 { public: hkVector4_s010d_18c0 m_col0, m_col1, m_col2, m_translation; };   // 0x40 bytes
class hkShape_s010d_18c0 {  // 0xc bytes
    public: virtual ~hkShape_s010d_18c0();
    int m_pad[2];
};
class hkConvexShape_s010d_18c0 : public hkShape_s010d_18c0 { public: float m_radius; };                                              // radius +0xc
class hkTriangleShape_s010d_18c0 : public hkConvexShape_s010d_18c0 { public: hkVector4_s010d_18c0 m_vertices[3]; };                              // vertices +0x10
struct hkMultiSphereShape_s010d_18c0 : hkShape_s010d_18c0 { int m_numSpheres; hkVector4_s010d_18c0 m_spheres[8]; };               // count +0xc, spheres +0x10
class hkCdBody_s010d_18c0
{
public:
    const hkShape_s010d_18c0* m_shape;        // +0
    unsigned       m_shapeKey;     // +4
    const hkTransform_s010d_18c0* m_motion;   // +8
    const hkCdBody_s010d_18c0* m_parent;      // +0xc
};
struct hkCollisionInput_s010d_18c0 { int pad; };
class hkCdBodyPairCollector_s010d_18c0
{
public:
    virtual ~hkCdBodyPairCollector_s010d_18c0() {}
    virtual void addCdBodyPair(const hkCdBody_s010d_18c0& a, const hkCdBody_s010d_18c0& b) = 0;     // slot 1
};
struct hkCollideTriangleUtil_s010d_18c0
{
    struct ClosestPointTriangleCache { float m_QQ, m_RR, m_QR, m_invTriNormal; };
    struct ClosestPointTriangleResult { hkVector4_s010d_18c0 hitDirection; float distance; };
    enum ClosestPointTriangleStatus { HIT_TRIANGLE_FACE = 0, HIT_TRIANGLE_EDGE };
    static void __cdecl setupClosestPointTriangleCache(const hkVector4_s010d_18c0* triangle, ClosestPointTriangleCache& cache);   // 0x01105d80
    static ClosestPointTriangleStatus __cdecl closestPointTriangle(const hkVector4_s010d_18c0& position, const hkVector4_s010d_18c0* tri,
        const ClosestPointTriangleCache& cache, ClosestPointTriangleResult& result);                                     // 0x01106010
};
static __forceinline void transformPoints_s010d_18c0(const hkTransform_s010d_18c0& t, const hkVector4_s010d_18c0* in, int n, hkVector4_s010d_18c0* out)
{
    const float m00 = t.m_col0.x, m01 = t.m_col0.y, m02 = t.m_col0.z;
    const float m10 = t.m_col1.x, m11 = t.m_col1.y, m12 = t.m_col1.z;
    const float m20 = t.m_col2.x, m21 = t.m_col2.y, m22 = t.m_col2.z;
    const float tx = t.m_translation.x, ty = t.m_translation.y, tz = t.m_translation.z;
    int i = 0;
    if (n >= 4)
    {
        int blocks = ((n - 4) >> 2) + 1;
        i = blocks * 4;
        const hkVector4_s010d_18c0* p = in;
        hkVector4_s010d_18c0* q = out;
        do {
            HK_XFORM_ONE(q[0], p[0]) HK_XFORM_ONE(q[1], p[1]) HK_XFORM_ONE(q[2], p[2]) HK_XFORM_ONE(q[3], p[3])
            p += 4; q += 4;
        } while (--blocks);
    }
    for (; i < n; ++i)
        HK_XFORM_ONE(out[i], in[i])
}
class hkMultiSphereTriangleAgent_s010d_18c0
{
public:
    virtual void pad0();
    virtual void pad1();
    virtual void getPenetrations(const hkCdBody_s010d_18c0& bodyA, const hkCdBody_s010d_18c0& bodyB, const hkCollisionInput_s010d_18c0& input,
                                 hkCdBodyPairCollector_s010d_18c0& collector);                       // 0x010d18c0
    static void staticGetPenetrations(const hkCdBody_s010d_18c0& bodyA, const hkCdBody_s010d_18c0& bodyB, const hkCollisionInput_s010d_18c0& input,
                                      hkCdBodyPairCollector_s010d_18c0& collector);                  // 0x010d1f40
    int m_pad[2];                                                                          // +4 refcount, +8 contactMgr
    hkCollideTriangleUtil_s010d_18c0::ClosestPointTriangleCache m_closestPointTriangleCache;         // +0xc
};
// ---- items of slice s010d18c0 end

// ---- items of slice s010d28c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char hkTtrcCapsuleTri[];               // 0x014a4620 ("TtCapsuleTri")
extern const char hkTtrcCapsTriangle[];             // 0x014a4630 ("TtCapsTriangle")
extern const char hkTtrcEnd[];                      // 0x0149cc34
struct __declspec(align(16)) hkVector4_s010d_28c0
{
    float x, y, z, w;
};
class hkCdBody_s010d_28c0
{
public:
    const void*     m_shape;        // +0
    unsigned        m_shapeKey;     // +4
    const void*     m_motion;       // +8  (the hkTransform)
    const hkCdBody_s010d_28c0* m_parent;       // +0xc
};
struct hkCollisionInput_s010d_28c0
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
};
struct hkProcessCollisionInput_s010d_28c0
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
};
struct hkProcessCollisionOutput_s010d_28c0
{
    void* m_firstContactPoint;      // +0
    int   m_pad[7];
    hkVector4_s010d_28c0 m_separatingNormal;   // +0x20
    int   m_contactPointCount;      // +0x3034
};
class hkContactPoint_s010d_28c0
{
public:
    hkVector4_s010d_28c0 m_position;           // +0
    hkVector4_s010d_28c0 m_separatingNormal;   // +0x10
};
class hkCdPointCollector_s010d_28c0
{
public:
    virtual ~hkCdPointCollector_s010d_28c0() {}
    virtual void addCdPoint(const void* point) = 0;   // slot 1 (+4)
    float m_earlyOutDistance;                         // +4
};
class hkContactMgr_s010d_28c0
{
public:
    virtual void v0();                                                                   // +0x00
    virtual void v1();                                                                   // +0x04
    virtual unsigned short addPoint(const void*, const void*, const void*, const void*); // +0x08
    virtual void v3();                                                                   // +0x0c
    virtual void removePoint(unsigned short key);                                        // +0x10
};
struct hkCapsTriangleManifold
{
    hkContactPoint_s010d_28c0 m_contact[3];    // +0, +0x20, +0x40
};
class hkTransform_s010d_28c0
{
public:
    hkVector4_s010d_28c0 m_basis[3];           // +0, +0x10, +0x20
    hkVector4_s010d_28c0 m_translation;        // +0x30
};
class hkCapsuleShape
{
public:
    char      m_pad[0xc];
    float     m_radius;             // +0xc
    hkVector4_s010d_28c0 m_vertexA;            // +0x10
    hkVector4_s010d_28c0 m_vertexB;            // +0x20
};
class hkTriangleShape_s010d_28c0
{
public:
    char      m_pad[0xc];
    float     m_radius;             // +0xc
    hkVector4_s010d_28c0 m_vertexA;            // +0x10
    hkVector4_s010d_28c0 m_vertexB;            // +0x20
    hkVector4_s010d_28c0 m_vertexC;            // +0x30
};
#define HK_XFORM_ONE_s010d_28c0(O, I, T) { \
        const float x = (I).x, y = (I).y, z = (I).z; \
        const float m00 = (T).m_basis[0].x, m01 = (T).m_basis[0].y, m02 = (T).m_basis[0].z; \
        const float m10 = (T).m_basis[1].x, m11 = (T).m_basis[1].y, m12 = (T).m_basis[1].z; \
        const float m20 = (T).m_basis[2].x, m21 = (T).m_basis[2].y, m22 = (T).m_basis[2].z; \
        const float tx = (T).m_translation.x, ty = (T).m_translation.y, tz = (T).m_translation.z; \
        (O).x = (m00 * x + (m10 * y + m20 * z)) + tx; \
        (O).y = (m01 * x + (m11 * y + m21 * z)) + ty; \
        (O).z = (m02 * x + (m12 * y + m22 * z)) + tz; \
        (O).w = 0.0f; }
extern "C" void __cdecl hkCollideCapsuleUtilManifoldCapsVsTriangle(
    const hkVector4_s010d_28c0* capSegment, float capRadius,
    const hkVector4_s010d_28c0* triangle, float triRadius,
    const void* cache, float extraRadius, int singleCheck,
    void* out);                                          // 0x01107270
extern "C" void __cdecl hkCollideTriangleUtilSetupCache(const hkVector4_s010d_28c0* triangle, void* cache);  // 0x01105e90
class hkCapsuleTriangleAgent
{
public:
    virtual void processCollision(const hkCdBody_s010d_28c0& bodyA, const hkCdBody_s010d_28c0& bodyB,
                                  const hkProcessCollisionInput_s010d_28c0& input,
                                  hkProcessCollisionOutput_s010d_28c0& output);            // 0x010d28c0
    virtual void getClosestPoints(const hkCdBody_s010d_28c0& bodyA, const hkCdBody_s010d_28c0& bodyB,
                                  const hkCollisionInput_s010d_28c0& input,
                                  hkCdPointCollector_s010d_28c0& collector);               // 0x010d2d80
    static void staticGetClosestPoints(const hkCdBody_s010d_28c0& bodyA, const hkCdBody_s010d_28c0& bodyB,
                                       const hkCollisionInput_s010d_28c0& input,
                                       hkCdPointCollector_s010d_28c0& collector);          // 0x010d32a0

    int            m_pad4;              // +4
    hkContactMgr_s010d_28c0*  m_contactMgr;        // +8
    unsigned short m_keys[3];           // +0xc
    unsigned short m_pad12;             // +0x12
    char           m_cache[0x40];       // +0x14  (hkCapsuleTriangleUtil::ShapeCache)
};
// ---- items of slice s010d28c0 end

// ---- items of slice s010d37d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char hkTtrcCapsCaps[];                 // 0x014a4688 ("TtCapsCaps")
class hkBool_s010d_37d0
{
public:
    char m_bool;
    hkBool_s010d_37d0() {}
    hkBool_s010d_37d0(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
};
struct __declspec(align(16)) hkVector4_s010d_37d0
{
    float x, y, z, w;
};
class hkCdBody_s010d_37d0
{ public:
    const void*     m_shape;        // +0
    unsigned        m_shapeKey;     // +4
    const void*     m_motion;       // +8
    const hkCdBody_s010d_37d0* m_parent;       // +0xc
};
struct hkCollisionInput_s010d_37d0
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
};
class hkContactPoint_s010d_37d0
{ public:
    hkVector4_s010d_37d0 m_position;           // +0
    hkVector4_s010d_37d0 m_separatingNormal;   // +0x10
    void setFlipped(const hkContactPoint_s010d_37d0& other);   // 0x010cecf0
};
class hkCdBodyPairCollector_s010d_37d0
{
public:
    virtual ~hkCdBodyPairCollector_s010d_37d0() {}
    virtual void addCdBodyPair(const hkCdBody_s010d_37d0& a, const hkCdBody_s010d_37d0& b) = 0;   // slot 1
    hkBool_s010d_37d0 m_earlyOut;              // +4
    const void* m_extra;            // +8
};
class hkCdPointCollector_s010d_37d0
{
public:
    virtual ~hkCdPointCollector_s010d_37d0() {}
    virtual void addCdPoint(const void* point) = 0;   // slot 1
    float m_earlyOutDistance;       // +4
};
extern "C" void __cdecl hkCollideCapsuleUtilManifoldCapsVsCapsule(
    const hkVector4_s010d_37d0* capA, float radiusA, const hkVector4_s010d_37d0* capB, float radiusB,
    void* out);                                              // 0x01106490
struct hkContactManifold
{
    hkContactPoint_s010d_37d0 m_contact[3];    // +0, +0x20, +0x40
};
class hkContactMgr_s010d_37d0
{ public:
    virtual void v0();                                                                   // +0x00
    virtual void v1();                                                                   // +0x04
    virtual unsigned short addPoint(const void*, const void*, const void*, const void*); // +0x08
    virtual void v3();                                                                   // +0x0c
    virtual void removePoint(unsigned short key);                                        // +0x10
};
class hkCapsuleTriangleAgent_s010d_37d0;
class hkCollisionAgent
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
};
class hkCapsuleTriangleAgent_s010d_37d0 : public hkCollisionAgent
{
public:
    void getPenetrations(const hkCdBody_s010d_37d0& bodyA, const hkCdBody_s010d_37d0& bodyB,
                         const hkCollisionInput_s010d_37d0& input, hkCdBodyPairCollector_s010d_37d0& collector);   // 0x010d37d0
    static void staticGetPenetrations(const hkCdBody_s010d_37d0& bodyA, const hkCdBody_s010d_37d0& bodyB,
                                      const hkCollisionInput_s010d_37d0& input, hkCdBodyPairCollector_s010d_37d0& collector);  // 0x010d3c10
    void getClosestPoints(const hkCdBody_s010d_37d0& bodyA, const hkCdBody_s010d_37d0& bodyB,
                          const hkCollisionInput_s010d_37d0& input, hkCdPointCollector_s010d_37d0& collector);    // 0x010d2d80
    void processCollision(const hkCdBody_s010d_37d0& bodyA, const hkCdBody_s010d_37d0& bodyB,
                          const void* input, void* output);                                  // 0x010d28c0
    void getPenetrationsWrapper(const void* bodyA, const void* bodyB,
                                const void* input, void* collector);                     // 0x010d4070
    void getClosestPointsWrapper(const void* bodyA, const void* bodyB,
                                 const void* input, void* collector);                    // 0x010d40f0
    void processCollisionThunk(const void* bodyA, const void* bodyB,
                               const void* input, void* output);                         // 0x010d4170
};
struct hkTempPairCollector
{
    const void* m_vtbl;             // +0
    char        m_earlyOut;         // +4
    const void* m_extra;            // +8
};
struct hkTempPointCollector
{
    const void* m_vtbl;             // +0
    unsigned    m_earlyOutDistance; // +4
    const void* m_extra;            // +8
};
class hkMemory_s010d_37d0
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void* alloc(int size, int cls);      // +0x10
};
extern hkMemory_s010d_37d0* g_hkMemory;                     // 0x016e4178
class hkCapsuleCapsuleAgent : public hkCollisionAgent
{
public:
    void processCollision(const void* bodyA, const void* bodyB,
                          const void* input, void* output);   // 0x010d42c0
    int m_pad[2];                                             // +4 refcount, +8 mgr
    unsigned short m_keys[3];                                 // +0xc, +0xe, +0x10
};
class hkTransform_s010d_37d0
{ public:
    hkVector4_s010d_37d0 m_basis[3];           // +0, +0x10, +0x20
    hkVector4_s010d_37d0 m_translation;        // +0x30
};
class hkCapsuleShape_s010d_37d0
{ public:
    char      m_pad[0xc];
    float     m_radius;             // +0xc
    hkVector4_s010d_37d0 m_vertexA;            // +0x10
    hkVector4_s010d_37d0 m_vertexB;            // +0x20
};
#define HK_XFORM_ONE_s010d_37d0(O, I, T) { \
        const float x = (I).x, y = (I).y, z = (I).z; \
        const float m00 = (T).m_basis[0].x, m01 = (T).m_basis[0].y, m02 = (T).m_basis[0].z; \
        const float m10 = (T).m_basis[1].x, m11 = (T).m_basis[1].y, m12 = (T).m_basis[1].z; \
        const float m20 = (T).m_basis[2].x, m21 = (T).m_basis[2].y, m22 = (T).m_basis[2].z; \
        const float tx = (T).m_translation.x, ty = (T).m_translation.y, tz = (T).m_translation.z; \
        (O).x = (m00 * x + (m10 * y + m20 * z)) + tx; \
        (O).y = (m01 * x + (m11 * y + m21 * z)) + ty; \
        (O).z = (m02 * x + (m12 * y + m22 * z)) + tz; \
        (O).w = 0.0f; }
// ---- items of slice s010d37d0 end

// ---- items of slice s010d4730 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct __declspec(align(16)) hkVector4_s010d_4730
{
    float x, y, z, w;
};
class hkCdBody_s010d_4730
{ public:
    const void*     m_shape;        // +0
    unsigned        m_shapeKey;     // +4
    const void*     m_motion;       // +8
    const hkCdBody_s010d_4730* m_parent;       // +0xc
};
struct hkCollisionInput_s010d_4730
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
};
class hkCdPointCollector_s010d_4730
{
public:
    virtual ~hkCdPointCollector_s010d_4730() {}
    virtual void addCdPoint(const void* point) = 0;   // slot 1
    float m_earlyOutDistance;       // +4
};
class hkCdBodyPairCollector_s010d_4730
{
public:
    virtual ~hkCdBodyPairCollector_s010d_4730() {}
    virtual void addCdBodyPair(const hkCdBody_s010d_4730& a, const hkCdBody_s010d_4730& b) = 0;   // slot 1
    char m_earlyOut;                // +4
    const void* m_extra;            // +8
};
class hkCapsuleCapsuleAgent_s010d_4730 : public hkCollisionAgent
{
public:
    void getClosestPoints(const hkCdBody_s010d_4730& bodyA, const hkCdBody_s010d_4730& bodyB,
                          const hkCollisionInput_s010d_4730& input, hkCdPointCollector_s010d_4730& collector);          // 0x010d4730
    static void staticGetClosestPoints(const hkCdBody_s010d_4730& bodyA, const hkCdBody_s010d_4730& bodyB,
                                       const hkCollisionInput_s010d_4730& input, hkCdPointCollector_s010d_4730& collector); // 0x010d4b00
    static void staticGetPenetrations(const hkCdBody_s010d_4730& bodyA, const hkCdBody_s010d_4730& bodyB,
                                      const hkCollisionInput_s010d_4730& input, hkCdBodyPairCollector_s010d_4730& collector); // 0x010d4ed0
};
class hkTransform_s010d_4730
{ public:
    hkVector4_s010d_4730 m_basis[3];           // +0, +0x10, +0x20
    hkVector4_s010d_4730 m_translation;        // +0x30
};
class hkCapsuleShape_s010d_4730
{ public:
    char      m_pad[0xc];
    float     m_radius;             // +0xc
    hkVector4_s010d_4730 m_vertexA;            // +0x10
    hkVector4_s010d_4730 m_vertexB;            // +0x20
};
#define HK_XFORM_ONE_s010d_4730(O, I, T) { \
        const float v0 = (I).x, v1 = (I).y, v2 = (I).z; \
        const float xx = (T).m_basis[0].x, xy = (T).m_basis[0].y, xz = (T).m_basis[0].z; \
        const float yx = (T).m_basis[1].x, yy = (T).m_basis[1].y, yz = (T).m_basis[1].z; \
        const float zx = (T).m_basis[2].x, zy = (T).m_basis[2].y, zz = (T).m_basis[2].z; \
        const float tx = (T).m_translation.x, ty = (T).m_translation.y, tz = (T).m_translation.z; \
        (O).x = (v0 * xx + (v1 * yx + v2 * zx)) + tx; \
        (O).y = (v0 * xy + (v1 * yy + v2 * zy)) + ty; \
        (O).z = (v0 * xz + (v1 * yz + v2 * zz)) + tz; \
        (O).w = 0.0f; }
struct hkCapsCapsClosestPointResult
{
    hkVector4_s010d_4730 m_closestPointA;      // +0
    hkVector4_s010d_4730 m_closestPointB;      // +0x10
    float     m_distanceSquared;    // +0x20
    float     m_pad0;               // +0x24
};
extern "C" int __cdecl hkCollideCapsuleUtilClostestPointCapsVsCaps(
    const hkVector4_s010d_4730* capA, float radiusA, const hkVector4_s010d_4730* capB, float radiusB,
    float tolerance, hkCapsCapsClosestPointResult* out);         // 0x01106f80
class hkMemory_s010d_4730
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void* alloc(int size, int cls);      // +0x10
};
extern hkMemory_s010d_4730* hkMemory_s_instance;            // 0x016e4178
struct hkContactMgr;
typedef hkCollisionAgent* (__cdecl *hkAgentCreateFunc)(const hkCdBody_s010d_4730&, const hkCdBody_s010d_4730&,
                                                       const hkCollisionInput_s010d_4730&, hkContactMgr*);
typedef void (__cdecl *hkAgentGetPenetrationsFunc)(const hkCdBody_s010d_4730&, const hkCdBody_s010d_4730&,
                                                   const hkCollisionInput_s010d_4730&, hkCdBodyPairCollector_s010d_4730&);
typedef void (__cdecl *hkAgentGetClosestPointsFunc)(const hkCdBody_s010d_4730&, const hkCdBody_s010d_4730&,
                                                    const hkCollisionInput_s010d_4730&, hkCdPointCollector_s010d_4730&);
typedef void (__cdecl *hkAgentLinearCastFunc)(const hkCdBody_s010d_4730&, const hkCdBody_s010d_4730&, const void*,
                                              hkCdPointCollector_s010d_4730&, hkCdPointCollector_s010d_4730*);
struct hkAgentFuncs
{
    hkAgentCreateFunc            m_createFunc;          // +0
    hkAgentGetPenetrationsFunc   m_getPenetrationsFunc; // +4
    hkAgentGetClosestPointsFunc  m_getClosestPointFunc; // +8
    hkAgentLinearCastFunc        m_linearCastFunc;      // +0xc
    char                         m_isFlipped;           // +0x10
    char                         m_isPredictive;        // +0x11
    short                        m_pad0;                // +0x12
    unsigned                     m_flags;               // +0x14 (0x18-byte struct in the retail build)
};
class hkCollisionDispatcher_s010d_4730
{ public:
    char          m_pad0[0x190];
    unsigned char m_agent2Types[32][32];               // +0x190
    unsigned char m_agent2TypesPredictive[32][32];     // +0x590
    hkAgentFuncs  m_agent2Func[1];                     // +0x990
    void registerCollisionAgent(hkAgentFuncs& funcs, int typeA, int typeB);   // 0x010cd3e0
};
class hkCollideTriangleUtil_s010d_4730
{
public:
    struct ClosestLineSegLineSegResult
    {
        hkVector4_s010d_4730 m_closestPointA;      // +0
        hkVector4_s010d_4730 m_closestPointB;      // +0x10
        float     m_distanceSquared;    // +0x20 (single float, result block is 0x24 bytes)
    };
    static int closestLineSegLineSeg(const hkVector4_s010d_4730& A, const hkVector4_s010d_4730& dA, const hkVector4_s010d_4730& B,
                                     const hkVector4_s010d_4730& dB, ClosestLineSegLineSegResult& result); // 0x01105940
};
// ---- items of slice s010d4730 end

// ---- items of slice s010d53d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char hkTtrcSphereBox[];                // 0x014a4720 ("TtSphereBox")
extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, fabs)
class hkTransform_s010d_53d0;
struct __declspec(align(16)) hkVector4_s010d_53d0
{
    float x, y, z, w;
    void setTransformedInversePos(const hkTransform_s010d_53d0& xf, const hkVector4_s010d_53d0& p);  // 0x010813d0
};
class hkTransform_s010d_53d0
{ public:
    hkVector4_s010d_53d0 m_basis[3];           // +0, +0x10, +0x20
    hkVector4_s010d_53d0 m_translation;        // +0x30
};
class hkCdBody_s010d_53d0
{ public:
    const void*     m_shape;        // +0
    unsigned        m_shapeKey;     // +4
    const void*     m_motion;       // +8
    const hkCdBody_s010d_53d0* m_parent;       // +0xc
};
struct hkCollisionInput_s010d_53d0
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
};
struct hkProcessCollisionInput_s010d_53d0
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
};
class hkSphereShape
{ public:
    char  m_pad[0xc];
    float m_radius;                 // +0xc
};
class hkBoxShape
{ public:
    char      m_pad[0xc];
    float     m_radius;             // +0xc
    hkVector4_s010d_53d0 m_halfExtents;        // +0x10
};
class hkContactPoint_s010d_53d0
{ public:
    hkVector4_s010d_53d0 m_position;           // +0
    hkVector4_s010d_53d0 m_separatingNormal;   // +0x10
    char      m_pad[0x10];          // +0x20 (contact id lives here)
};
struct hkProcessCdPoint_s010d_53d0 { hkContactPoint_s010d_53d0 m_contact; };   // 0x30
struct hkProcessCollisionOutput_s010d_53d0
{
    hkProcessCdPoint_s010d_53d0* m_firstFreeContactPoint;  // +0
};
class hkCdPointCollector_s010d_53d0
{
public:
    virtual ~hkCdPointCollector_s010d_53d0() {}
    virtual void addCdPoint(const void* point) = 0;   // slot 1
    float m_earlyOutDistance;                         // +4
};
class hkCdBodyPairCollector_s010d_53d0
{
public:
    virtual ~hkCdBodyPairCollector_s010d_53d0() {}
    virtual void addCdBodyPair(const hkCdBody_s010d_53d0& a, const hkCdBody_s010d_53d0& b) = 0;  // slot 1
    char m_earlyOut;                                  // +4
    const void* m_extra;                              // +8
};
class hkContactMgr_s010d_53d0
{
public:
    virtual void v0();                                          // +0
    virtual void v1();                                          // +4
    virtual unsigned short createContactPoint(const hkCdBody_s010d_53d0&, const hkCdBody_s010d_53d0&,
                                              const hkProcessCollisionInput_s010d_53d0&,
                                              hkContactPoint_s010d_53d0*);  // +8
    virtual void v3();                                          // +0xc
    virtual void removeContactPoint(unsigned short index);      // +0x10
};
union hkFloatBits { float f; unsigned u; };
static __forceinline float hkMinF(float a, float b) { return (a < b) ? a : b; }
static __forceinline float hkFlipSign(float value, float signSource)
{
    hkFloatBits v, s;
    v.f = value;
    s.f = signSource;
    v.u ^= (s.u & 0x80000000u);
    return v.f;
}
static __forceinline float hkNegFlip(float value, float signSource)
{
    return -hkFlipSign(value, signSource);
}
static __forceinline float hkClampAbs(float value, float limit)
{
    return hkFlipSign(hkMinF((float)fabs(value), limit), value);
}
class hkSphereBoxAgent : public hkCollisionAgent
{
public:
    unsigned short m_pad0;              // +4
    unsigned short m_pad1;              // +6
    hkContactMgr_s010d_53d0*  m_contactMgr;        // +8
    unsigned short m_contactPointId;    // +0xc (0xffff when none cached)
    char           m_pad2[2];

    virtual void processCollision(const hkCdBody_s010d_53d0& bodyA, const hkCdBody_s010d_53d0& bodyB,
                                  const hkProcessCollisionInput_s010d_53d0& input,
                                  hkProcessCollisionOutput_s010d_53d0& output);          // 0x010d53d0
    virtual void getClosestPoints(const hkCdBody_s010d_53d0& bodyA, const hkCdBody_s010d_53d0& bodyB,
                                  const hkCollisionInput_s010d_53d0& input,
                                  hkCdPointCollector_s010d_53d0& collector);             // 0x010d5850
    static void staticGetClosestPoints(const hkCdBody_s010d_53d0& bodyA, const hkCdBody_s010d_53d0& bodyB,
                                       const hkCollisionInput_s010d_53d0& input,
                                       hkCdPointCollector_s010d_53d0& collector);        // 0x010d5ca0
    static void staticGetPenetrations(const hkCdBody_s010d_53d0& bodyA, const hkCdBody_s010d_53d0& bodyB,
                                      const hkCollisionInput_s010d_53d0& input,
                                      hkCdBodyPairCollector_s010d_53d0& collector);      // 0x010d60f0
};
struct hkSymPointCollectorLocal
{
    void*               m_vtable;       // +0
    unsigned            m_earlyOut;     // +4 (bit pattern 0x7f7fffee)
    hkCdPointCollector_s010d_53d0* m_forward;      // +8
};
class hkSymmetricSphereBoxAgent : public hkSphereBoxAgent
{
public:
    virtual void getClosestPoints(const hkCdBody_s010d_53d0& bodyA, const hkCdBody_s010d_53d0& bodyB,
                                  const hkCollisionInput_s010d_53d0& input,
                                  hkCdPointCollector_s010d_53d0& collector);   // 0x010d63a0
};
// ---- items of slice s010d53d0 end

// ---- items of slice s010d6420 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char hkTtrcSphereTri[];                // 0x014a47b0 ("TtSphereTri")
struct __declspec(align(16)) hkVector4_s010d_6420
{
    float x, y, z, w;
};
class hkCdBody_s010d_6420
{ public:
    const void*     m_shape;        // +0
    unsigned        m_shapeKey;     // +4
    const void*     m_motion;       // +8
    const hkCdBody_s010d_6420* m_parent;       // +0xc
};
struct hkCollisionInput_s010d_6420
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
};
class hkTransform_s010d_6420
{ public:
    hkVector4_s010d_6420 m_basis[3];           // +0, +0x10, +0x20
    hkVector4_s010d_6420 m_translation;        // +0x30
};
class hkTriangleShape_s010d_6420
{ public:
    char      m_pad[0xc];
    float     m_radius;             // +0xc
    hkVector4_s010d_6420 m_vertex[3];          // +0x10, +0x20, +0x30
};
class hkCdPointCollector_s010d_6420
{
public:
    virtual ~hkCdPointCollector_s010d_6420() {}
    virtual void addCdPoint(const void* point) = 0;   // slot 1
    float m_earlyOutDistance;       // +4
};
class hkCdBodyPairCollector_s010d_6420
{
public:
    virtual ~hkCdBodyPairCollector_s010d_6420() {}
    virtual void addCdBodyPair(const hkCdBody_s010d_6420& a, const hkCdBody_s010d_6420& b) = 0;   // slot 1
    char m_earlyOut;                // +4
    const void* m_extra;            // +8
};
class hkContactPoint_s010d_6420
{ public:
    hkVector4_s010d_6420 m_position;           // +0
    hkVector4_s010d_6420 m_separatingNormal;   // +0x10 (w = distance)
    hkVector4_s010d_6420 m_pad;                // +0x20
    void setFlipped(const hkContactPoint_s010d_6420& other);    // 0x010cecf0
};
struct hkProcessCdPoint_s010d_6420 { hkContactPoint_s010d_6420 m_contact; };  // 0x30 bytes (contact is 0x30)
typedef float hkTime;
struct hkProcessCollisionInput_s010d_6420
{
    char  m_pad0[8];
    float m_tolerance;              // +8
};
struct hkProcessCollisionOutput_s010d_6420
{
    hkProcessCdPoint_s010d_6420* m_firstFreeContactPoint;  // +0
    char              m_pad0[0x10 - 4];
    hkContactPoint_s010d_6420    m_toiContact;             // +0x10
    hkProcessCdPoint_s010d_6420  m_contactPoints[256];     // +0x30
    hkTime            m_toiTime;                // +0x3034
};
class hkContactMgr_s010d_6420
{
public:
    virtual void v0();                                          // +0
    virtual void v1();                                          // +4
    virtual unsigned short createContactPoint(const hkCdBody_s010d_6420&, const hkCdBody_s010d_6420&,
                                              const hkProcessCollisionInput_s010d_6420&,
                                              hkContactPoint_s010d_6420*);  // +8
    virtual void v3();                                          // +0xc
    virtual void removeContactPoint(unsigned short index);      // +0x10
};
class hkMemory_s010d_6420
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void* alloc(int size, int cls);      // +0x10
};
extern hkMemory_s010d_6420* hkMemory_s_instance_s010d_6420;            // 0x016e4178
class hkCollideTriangleUtil_s010d_6420
{
public:
    struct ClosestPointTriangleCache
    {
        hkVector4_s010d_6420 m_rows[5];        // +0 .. +0x4f
    };

    struct ClosestPointTriangleResult
    {
        hkVector4_s010d_6420 m_closestPoint;   // +0
        float     m_distance;       // +0x10
    };

    enum ClosestPointTriangleStatus { CPT_OK = 0 };

    static void setupClosestPointTriangleCache(const hkVector4_s010d_6420* verts,
                                               ClosestPointTriangleCache& cache);  // 0x01105d80
    static ClosestPointTriangleStatus closestPointTriangle(const hkVector4_s010d_6420& point,
                                                           const hkVector4_s010d_6420* verts,
                                                           const ClosestPointTriangleCache& cache,
                                                           ClosestPointTriangleResult& result); // 0x01106010
};
class hkSphereTriangleAgent : public hkCollisionAgent
{
public:
    unsigned short  m_shapeType;                // +4
    unsigned short  m_isFlipped;                // +6
    hkContactMgr_s010d_6420*   m_contactMgr;               // +8
    unsigned short  m_contactPointIndex;        // +0xc (-1 when none cached)
    char            m_pad0[2];
    hkCollideTriangleUtil_s010d_6420::ClosestPointTriangleCache m_cache;   // +0x10

    static hkCollisionAgent* createSphereTriangleAgent(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB,
                                                       const hkCollisionInput_s010d_6420& input,
                                                       hkContactMgr_s010d_6420* mgr);         // 0x010d6530
    static hkCollisionAgent* createTriangleSphereAgent(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB,
                                                       const hkCollisionInput_s010d_6420& input,
                                                       hkContactMgr_s010d_6420* mgr);         // 0x010d6680

    void processCollision(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB,
                          const hkProcessCollisionInput_s010d_6420& input,
                          hkProcessCollisionOutput_s010d_6420& output);                       // 0x010d66e0
    void getClosestPoints(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB,
                          const hkCollisionInput_s010d_6420& input, hkCdPointCollector_s010d_6420& collector);   // 0x010d6a80
    static void staticGetClosestPoints(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB,
                                       const hkCollisionInput_s010d_6420& input,
                                       hkCdPointCollector_s010d_6420& collector);             // 0x010d6e00
    void getPenetrations(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB,
                         const hkCollisionInput_s010d_6420& input,
                         hkCdBodyPairCollector_s010d_6420& collector);                        // 0x010d7190
    static void staticGetPenetrations(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB,
                                      const hkCollisionInput_s010d_6420& input,
                                      hkCdBodyPairCollector_s010d_6420& collector);           // 0x010d7300
};
static __forceinline void hkTriXformVertex(hkVector4_s010d_6420& out, const hkVector4_s010d_6420& v,
                                           const hkTransform_s010d_6420& m)
{
    out.x = m.m_basis[0].x * v.x + (m.m_basis[1].x * v.y + m.m_basis[2].x * v.z) + m.m_translation.x;
    out.y = m.m_basis[0].y * v.x + (m.m_basis[1].y * v.y + m.m_basis[2].y * v.z) + m.m_translation.y;
    out.z = m.m_basis[0].z * v.x + (m.m_basis[1].z * v.y + m.m_basis[2].z * v.z) + m.m_translation.z;
    out.w = 0.0f;
}
static __forceinline void hkTriLocalPoint(hkVector4_s010d_6420& out, const hkVector4_s010d_6420& p,
                                          const hkTransform_s010d_6420& m)
{
    const float dx = p.x - m.m_translation.x;
    const float dy = p.y - m.m_translation.y;
    const float dz = p.z - m.m_translation.z;
    out.x = dx * m.m_basis[0].x + (dy * m.m_basis[0].y + dz * m.m_basis[0].z);
    out.y = dx * m.m_basis[1].x + (dy * m.m_basis[1].y + dz * m.m_basis[1].z);
    out.z = dx * m.m_basis[2].x + (dy * m.m_basis[2].y + dz * m.m_basis[2].z);
    out.w = 0.0f;
}
struct hkSymPairCollectorLocal
{
    void*                  m_vtable;        // +0
    unsigned char          m_earlyOut;      // +4
    hkCdBodyPairCollector_s010d_6420* m_forward;       // +8
};
class hkSymmetricSphereTriangleAgent : public hkSphereTriangleAgent
{
public:
    void getPenetrations(const hkCdBody_s010d_6420&, const hkCdBody_s010d_6420&, const hkCollisionInput_s010d_6420&,
                         hkCdBodyPairCollector_s010d_6420&);                       // 0x010d7470
    void getClosestPoints(const hkCdBody_s010d_6420&, const hkCdBody_s010d_6420&, const hkCollisionInput_s010d_6420&,
                          hkCdPointCollector_s010d_6420&);                         // 0x010d74f0
};
struct hkSymPointCollectorLocal_s010d_6420
{
    void*               m_vtable;       // +0
    unsigned            m_earlyOut;     // +4 (bit pattern 0x7f7fffee)
    hkCdPointCollector_s010d_6420* m_forward;      // +8
};
// ---- items of slice s010d6420 end

// ---- items of slice s010dcd40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char hkMonitorEndTag[];                // string at 0x00143cd94
#ifdef _WIN32
#endif
typedef float hkReal;
typedef uint16_t hkContactPointId_s010d_cd40;
typedef uint8_t hkBool;
#define HK_REAL_MAX 3.40282e+38f
class hkVector4_s010d_cd40 { public: float x, y, z, w; };
class hkTransform_s010d_cd40 { public:
    hkVector4_s010d_cd40 m_rot[3];
    hkVector4_s010d_cd40 m_trans;
    void setMulInverseMul(const hkTransform_s010d_cd40& a, const hkTransform_s010d_cd40& b);   // this = inverse(a) * b
};
class hkContactPoint_s010d_cd40 { public:
    hkVector4_s010d_cd40 m_position;
    hkVector4_s010d_cd40 m_separatingNormal;   // w = distance
    void setFlipped(const hkContactPoint_s010d_cd40& other);
};
struct hkProcessCdPoint_s010d_cd40 { hkContactPoint_s010d_cd40 m_contact; uint32_t m_extra[4]; };   // 0x30 bytes
class hkReferencedObject_s010d_cd40 { public:
    virtual void* hkReferencedObject_deletingDtor(unsigned int flags);   // vtable slot 0 (scalar deleting destructor)
    uint16_t m_memSizeAndFlags;
    int16_t  m_referenceCount;
};
class hkMemory_s010d_cd40 { public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual void* allocateChunk(int nbytes, int memClass);
    static hkMemory_s010d_cd40* s_instance;
};
enum { HK_MEMORY_CLASS_COLLIDE = 0x1c };
#define HK_DECLARE_AGENT_ALLOCATOR \
    void* operator new(size_t n) { \
        void* p = hkMemory_s010d_cd40::s_instance->allocateChunk((int)n, HK_MEMORY_CLASS_COLLIDE); \
        ((hkReferencedObject_s010d_cd40*)p)->m_memSizeAndFlags = (uint16_t)n; return p; } \
    void operator delete(void*) {}
class hkCdVertex { public: float x, y, z; union { float w; uint32_t wBits; }; };
class hkSphere { public: hkVector4_s010d_cd40 m_pos; };                                          // 16 bytes
struct hkCollisionSpheresInfo { int m_numSpheres; hkBool m_useBuffer; };      // hkSphereRepShape::hkCollisionSpheresInfo
class hkShape_s010d_cd40 : public hkReferencedObject_s010d_cd40 { public:
    uint32_t m_userData;                       // +8
};
class hkConvexShape_s010d_cd40 : public hkShape_s010d_cd40 { public:
    float m_radius;                            // +0xc
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
    virtual void getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const;
    virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;
    virtual void getSupportingVertex(const hkVector4_s010d_cd40& dir, hkCdVertex& supportingVertexOut) const;
    virtual void convertVertexIdsToVertices(const uint16_t* ids, int numIds, hkCdVertex* verticesOut) const;
    virtual void getFirstVertex(hkVector4_s010d_cd40& v) const;
};
struct hkConvexShapeRef { hkConvexShape_s010d_cd40* m_shape; uint32_t m_unknown; };      // 8-byte array element (stride 8 in the binary)
struct hkConvexListShape;
struct hkConvexListConvexShape : hkConvexShape_s010d_cd40 {
    hkConvexShapeRef* m_subShapesData;         // +0x10
    int m_subShapesSize;                       // +0x14
    hkConvexListConvexShape() {}
    inline hkConvexListConvexShape(const hkConvexListShape& list);                 // temp view used by the agents
    virtual void getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const;
    virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;
    virtual void getSupportingVertex(const hkVector4_s010d_cd40& dir, hkCdVertex& supportingVertexOut) const;
    virtual void convertVertexIdsToVertices(const uint16_t* ids, int numIds, hkCdVertex* verticesOut) const;
    virtual void getFirstVertex(hkVector4_s010d_cd40& v) const;
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
class hkCdBody_s010d_cd40 { public:
    const hkShape_s010d_cd40* m_shape;                    // +0
    uint32_t m_shapeKey;                       // +4
    const hkTransform_s010d_cd40* m_motion;               // +8
    const hkCdBody_s010d_cd40* m_parent;                  // +0xc
};
struct hkCollisionDispatcher_s010d_cd40;
struct hkCollisionInput_s010d_cd40 {
    hkCollisionDispatcher_s010d_cd40* m_dispatcher;       // +0
    uint32_t m_pad[3];
};
struct hkProcessCollisionInput_s010d_cd40 : hkCollisionInput_s010d_cd40 {};
struct hkLinearCastCollisionInput : hkCollisionInput_s010d_cd40 {
    hkVector4_s010d_cd40 m_path;                          // +0x10
    uint32_t m_pad2[4];                        // total 0x30 bytes (12 dwords copied by the symmetric agent)
};
struct hkCdPoint_s010d_cd40 { hkContactPoint_s010d_cd40 m_contact; const hkCdBody_s010d_cd40* m_cdBodyA; const hkCdBody_s010d_cd40* m_cdBodyB; };
class hkCdPointCollector_s010d_cd40 { public:
    virtual void hkCdPointCollector_v0();
    virtual void addCdPoint(const hkCdPoint_s010d_cd40& point);
    float m_earlyOutDistance;                  // +4
};
class hkCdBodyPairCollector_s010d_cd40 { public:
    virtual void hkCdBodyPairCollector_v0();
    virtual void addCdBodyPair(const hkCdBody_s010d_cd40& a, const hkCdBody_s010d_cd40& b);
    hkBool m_earlyOut;                         // +4
};
struct hkProcessCollisionOutput_s010d_cd40 {
    hkProcessCdPoint_s010d_cd40* m_firstFreeContactPoint; // +0
    uint32_t m_pad0[3];
    hkContactPoint_s010d_cd40 m_toiContact;               // +0x10 (position, normal+distance)
    hkProcessCdPoint_s010d_cd40 m_contactPoints[256];     // +0x30
    uint32_t m_toiProperties;                  // +0x3030
    hkTime   m_toiTime;                        // +0x3034
    uint32_t m_pad1[2];
    uint32_t* m_potentialContacts;             // +0x3040 (0x1008 bytes copied by the backup)
};
struct hkMonitorCommand_s010d_cd40 { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_pad; };   // 12 bytes (32-bit)
struct hkMonitorCommand2 { hkMonitorCommand_s010d_cd40 m_first; const char* m_secondCommand; };               // 16 bytes (32-bit)
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
        hkMonitorCommand_s010d_cd40* c_ = (hkMonitorCommand_s010d_cd40*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_commandAndMonitor = name; \
        c_->m_time0 = (uint32_t)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_END_LIST() HK_TIMER_SPLIT_LIST(hkMonitorEndTag)
struct hkGskCache {
    uint32_t m_pad[3];                         // 12 bytes
    void init(const hkConvexShape_s010d_cd40* shapeA, const hkConvexShape_s010d_cd40* shapeB, const hkTransform_s010d_cd40& aTb);
};
struct hkGskManifold {
    uint8_t m_numVertsA, m_numVertsB, m_numContactPoints, m_pad;
    struct ContactPoint { uint8_t m_dimA, m_dimB; hkContactPointId_s010d_cd40 m_id; uint32_t m_allVerts; } m_contactPoints[4];
    uint8_t m_padding[32];
};
class hkCollisionAgent_s010d_cd40 : public hkReferencedObject_s010d_cd40 { public:
    hkContactMgr* m_contactMgr;                // +8
    virtual void processCollision(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkProcessCollisionInput_s010d_cd40&, hkProcessCollisionOutput_s010d_cd40&);
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
    virtual void invalidateTim(hkCollisionInput_s010d_cd40& input);
    virtual void warpTime(hkTime oldTime, hkTime newTime, hkCollisionInput_s010d_cd40& input);
    virtual void cleanup();
    virtual void removePoint(hkContactPointId_s010d_cd40 id);
    virtual void commitPotential(hkContactPointId_s010d_cd40 id);
    virtual void createZombie(hkContactPointId_s010d_cd40 id);
};
struct hkHeightFieldAgent : hkCollisionAgent_s010d_cd40 {
    uint32_t m_pad[3];                         // object size 0x18
    hkHeightFieldAgent(const hkCdBody_s010d_cd40& a, const hkCdBody_s010d_cd40& b, const hkCollisionInput_s010d_cd40& input, hkContactMgr* mgr);
    virtual void processCollision(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkProcessCollisionInput_s010d_cd40&, hkProcessCollisionOutput_s010d_cd40&);
};
struct hkGskBaseAgent : hkCollisionAgent_s010d_cd40 {
    hkGskCache m_cache;                        // +0xc
    hkTime m_timeOfSeparatingNormal;           // +0x18
    hkReal m_allowedPenetration;               // +0x1c
    hkVector4_s010d_cd40 m_separatingNormal;              // +0x20  (w = -1 when invalid)
    HK_DECLARE_AGENT_ALLOCATOR
    hkGskBaseAgent(const hkCdBody_s010d_cd40& a, const hkCdBody_s010d_cd40& b, hkContactMgr* mgr);
    virtual void invalidateTim(hkCollisionInput_s010d_cd40& input);
    virtual void warpTime(hkTime oldTime, hkTime newTime, hkCollisionInput_s010d_cd40& input);
    static void staticGetPenetrations(const hkCdBody_s010d_cd40& a, const hkCdBody_s010d_cd40& b, const hkCollisionInput_s010d_cd40& input, hkCdBodyPairCollector_s010d_cd40& c);
    static void staticGetClosestPoints(const hkCdBody_s010d_cd40& a, const hkCdBody_s010d_cd40& b, const hkCollisionInput_s010d_cd40& input, hkCdPointCollector_s010d_cd40& c);
    static void staticLinearCast(const hkCdBody_s010d_cd40& a, const hkCdBody_s010d_cd40& b, const hkLinearCastCollisionInput& input, hkCdPointCollector_s010d_cd40& c, hkCdPointCollector_s010d_cd40* start);   // 0x010ebc80 (equiv t2)
};
struct hkGskfAgent : hkGskBaseAgent {
    hkGskManifold m_manifold;                  // +0x30
    virtual void removePoint(hkContactPointId_s010d_cd40 id);
    virtual void commitPotential(hkContactPointId_s010d_cd40 id);
    virtual void createZombie(hkContactPointId_s010d_cd40 id);
};
struct hkPredGskfAgent : hkGskfAgent {
    uint32_t m_pad2[3];                        // up to 0x80
    hkPredGskfAgent(const hkCdBody_s010d_cd40& a, const hkCdBody_s010d_cd40& b, hkContactMgr* mgr);
};
class hkSymmetricAgentFlipCollector : public hkCdPointCollector_s010d_cd40 { public:            // vtable 0x014a43a4
    hkCdPointCollector_s010d_cd40& m_original;                                     // +8
    hkSymmetricAgentFlipCollector(hkCdPointCollector_s010d_cd40& c) : m_original(c) { m_earlyOutDistance = HK_REAL_MAX; }
    virtual void addCdPoint(const hkCdPoint_s010d_cd40& point);
};
class hkSymmetricAgentFlipBodyCollector : public hkCdBodyPairCollector_s010d_cd40 { public:     // vtable 0x014a43b4
    hkCdBodyPairCollector_s010d_cd40& m_original;                                  // +8
    hkSymmetricAgentFlipBodyCollector(hkCdBodyPairCollector_s010d_cd40& c) : m_original(c) { m_earlyOut = 0; }
    virtual void addCdBodyPair(const hkCdBody_s010d_cd40& a, const hkCdBody_s010d_cd40& b);
};
class hkSymmetricAgentFlipCastCollector : public hkCdPointCollector_s010d_cd40 { public:        // vtable 0x014a43ac
    uint32_t m_pad[2];
    hkVector4_s010d_cd40 m_path;                                                   // +0x10
    hkCdPointCollector_s010d_cd40* m_original;                                     // +0x20
    hkSymmetricAgentFlipCastCollector(const hkVector4_s010d_cd40& path, hkCdPointCollector_s010d_cd40* c) : m_path(path), m_original(c) { m_earlyOutDistance = HK_REAL_MAX; }
    virtual void addCdPoint(const hkCdPoint_s010d_cd40& point);
};
struct hkSymmetricAgentLinearCast_hkHeightFieldAgent : hkHeightFieldAgent {
    hkSymmetricAgentLinearCast_hkHeightFieldAgent(const hkCdBody_s010d_cd40& A, const hkCdBody_s010d_cd40& B, const hkCollisionInput_s010d_cd40& input, hkContactMgr* mgr)
        : hkHeightFieldAgent(B, A, input, mgr) {}
    HK_DECLARE_AGENT_ALLOCATOR
    virtual void processCollision(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkProcessCollisionInput_s010d_cd40& input, hkProcessCollisionOutput_s010d_cd40& result);
    static void __stdcall staticGetClosestPoints(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkCollisionInput_s010d_cd40&, hkCdPointCollector_s010d_cd40&);
    static void __stdcall staticLinearCast(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkLinearCastCollisionInput&, hkCdPointCollector_s010d_cd40&, hkCdPointCollector_s010d_cd40*);
};
extern void __cdecl hkHeightFieldAgent_staticGetClosestPoints(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkCollisionInput_s010d_cd40&, hkCdPointCollector_s010d_cd40&);   // FUN_010db380
extern void __cdecl hkHeightFieldAgent_staticLinearCast(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkLinearCastCollisionInput&, hkCdPointCollector_s010d_cd40&, hkCdPointCollector_s010d_cd40*); // FUN_010dbd30
struct hkHeightFieldAgentCreator {
    static hkCollisionAgent_s010d_cd40* createHeightFieldAAgent(const hkCdBody_s010d_cd40& A, const hkCdBody_s010d_cd40& B, const hkCollisionInput_s010d_cd40& input, hkContactMgr* mgr);
};
struct hkProcessCollisionOutputBackup {
    hkProcessCdPoint_s010d_cd40* m_firstFreeContactPoint;     // +0
    uint32_t m_potentialContacts[0x402];           // +4 .. 0x100b  (0x402 dwords copied starting at +4)
    uint32_t m_pad;                                // +0x100c (not touched)
    uint32_t m_toiContact[8];                      // +0x1010 .. 0x102c
    hkTime   m_toiTime;                            // +0x1030
    uint32_t m_toiProperties;                      // +0x1034
    hkProcessCollisionOutputBackup(const hkProcessCollisionOutput_s010d_cd40& out);
    hkProcessCollisionOutputBackup* restore(hkProcessCollisionOutput_s010d_cd40& out);
};
class hkClosestCdPointCollector_s010d_cd40 : public hkCdPointCollector_s010d_cd40 { public:                // vtable 0x013ef52c
    uint32_t m_pad[2];
    hkContactPoint_s010d_cd40 m_hitContact;                                        // +0x10 (distance = w @ +0x2c)
    const hkCdBody_s010d_cd40* m_hitRootA;                                         // +0x30 (null: no hit)
    uint32_t m_pad3[3];
    hkClosestCdPointCollector_s010d_cd40() { m_earlyOutDistance = HK_REAL_MAX; m_hitContact.m_separatingNormal.w = HK_REAL_MAX; m_hitRootA = 0; }
    virtual void addCdPoint(const hkCdPoint_s010d_cd40& point);
};
struct hkConvexListHullPenetrationCollector : hkCdBodyPairCollector_s010d_cd40 {   // vtable 0x014a4abc
    hkConvexListHullPenetrationCollector() { m_earlyOut = 0; }
    virtual void addCdBodyPair(const hkCdBody_s010d_cd40& a, const hkCdBody_s010d_cd40& b);
};
struct hkConvexListHullCastCollector : hkCdPointCollector_s010d_cd40 {            // vtable 0x014a4ac4
    hkBool m_hit;                                                       // +8
    uint32_t m_pad[0xa - 3];
    hkContactPoint_s010d_cd40 m_contact;                                           // +0x10 (distance w @ +0x2c)
    hkConvexListHullCastCollector() { m_earlyOutDistance = HK_REAL_MAX; m_hit = 0; m_contact.m_separatingNormal.w = HK_REAL_MAX; }
    virtual void addCdPoint(const hkCdPoint_s010d_cd40& point);
};
struct hkConvexListAgent : hkPredGskfAgent {
    hkCollisionDispatcher_s010d_cd40* m_dispatcher;        // +0x80
    hkBool m_inGskMode;                         // +0x84
    uint8_t m_pad3[3];
    uint32_t m_pad4[2];                         // object size 0x90
    HK_DECLARE_AGENT_ALLOCATOR
    hkConvexListAgent(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkCollisionInput_s010d_cd40& input, hkContactMgr* mgr);
    virtual void invalidateTim(hkCollisionInput_s010d_cd40& input);
    virtual void warpTime(hkTime oldTime, hkTime newTime, hkCollisionInput_s010d_cd40& input);
    virtual void cleanup();
    virtual void removePoint(hkContactPointId_s010d_cd40 id);
    virtual void commitPotential(hkContactPointId_s010d_cd40 id);
    virtual void createZombie(hkContactPointId_s010d_cd40 id);
    static hkCollisionAgent_s010d_cd40* createConvexListAgent(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkCollisionInput_s010d_cd40&, hkContactMgr*);
    static hkCollisionAgent_s010d_cd40* createListConvexAgent(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkCollisionInput_s010d_cd40&, hkContactMgr*);
    static void staticGetClosestPoints(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkCollisionInput_s010d_cd40&, hkCdPointCollector_s010d_cd40&);
    static void staticGetPenetrations(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkCollisionInput_s010d_cd40&, hkCdBodyPairCollector_s010d_cd40&);
    static void staticLinearCast(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkLinearCastCollisionInput&, hkCdPointCollector_s010d_cd40&, hkCdPointCollector_s010d_cd40*);
};
struct hkSymmetricAgent_hkConvexListAgent : hkConvexListAgent {
    hkSymmetricAgent_hkConvexListAgent(const hkCdBody_s010d_cd40& A, const hkCdBody_s010d_cd40& B, const hkCollisionInput_s010d_cd40& input, hkContactMgr* mgr)
        : hkConvexListAgent(B, A, input, mgr) {}
    HK_DECLARE_AGENT_ALLOCATOR
    virtual void processCollision(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkProcessCollisionInput_s010d_cd40&, hkProcessCollisionOutput_s010d_cd40&);
};
extern void __cdecl hkAgent1nMachine_InvalidateTim(void* track, hkCollisionInput_s010d_cd40& input);                 // FUN_01103850
extern void __cdecl hkAgent1nMachine_WarpTime(void* track, hkTime oldTime, hkTime newTime, hkCollisionInput_s010d_cd40& input);   // FUN_01103930
extern void __cdecl hkAgent1nMachine_Destroy(void* track, hkCollisionDispatcher_s010d_cd40* dispatcher, hkContactMgr* mgr);       // FUN_01104760
extern void __cdecl hkGskManifold_cleanup(hkGskManifold* manifold, hkContactMgr* mgr);                    // _hkGskManifold_cleanup
extern void __cdecl hkShapeCollectionAgent_staticGetClosestPoints(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkCollisionInput_s010d_cd40&, hkCdPointCollector_s010d_cd40&);
extern void __cdecl hkShapeCollectionAgent_staticGetPenetrations(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkCollisionInput_s010d_cd40&, hkCdBodyPairCollector_s010d_cd40&);
extern void __cdecl hkConvexListAgent_staticGetClosestPointsChildren(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkCollisionInput_s010d_cd40&, hkCdPointCollector_s010d_cd40&);   // FUN_010dd410
extern void __cdecl hkConvexListAgent_staticLinearCastChildren(const hkCdBody_s010d_cd40&, const hkCdBody_s010d_cd40&, const hkLinearCastCollisionInput&, hkCdPointCollector_s010d_cd40&, hkCdPointCollector_s010d_cd40*); // FUN_010dd450
struct hkConvexListHullBody : hkCdBody_s010d_cd40 {
    hkConvexListConvexShape m_hull;
    hkConvexListHullBody(const hkCdBody_s010d_cd40& B) : m_hull(*(const hkConvexListShape*)B.m_shape)
    {
        m_shape = &m_hull;
        m_shapeKey = B.m_shapeKey;
        m_motion = B.m_motion;
        m_parent = &B;
    }
};
// ---- items of slice s010dcd40 end

// ---- items of slice s010df100 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned long g_hkThreadMemoryTls;                                                // 0x016e4174
extern void __cdecl hkAgentDefaultFunc();            // 0x00c2e4e0 (shared no-op used for the unused function slots)
class hkVector4_s010d_f100 { public: float x, y, z, w; };
class hkQuaternion_s010d_f100 { public:
    hkVector4_s010d_f100 m_vec;
    void setMul(const hkQuaternion_s010d_f100& a, const hkQuaternion_s010d_f100& b);               // this = a * b
};
class hkTransform_s010d_f100 { public:
    hkVector4_s010d_f100 m_rot[3];                                                      // rows
    hkVector4_s010d_f100 m_trans;
    void setMul(const hkTransform_s010d_f100& a, const hkTransform_s010d_f100& b);                 // this = a * b
};
class hkContactPoint_s010d_f100 { public:
    hkVector4_s010d_f100 m_position;
    hkVector4_s010d_f100 m_separatingNormal;                                            // w = distance
    void setFlipped(const hkContactPoint_s010d_f100& other);
};
struct hkProcessCdPoint_s010d_f100 { hkContactPoint_s010d_f100 m_contact; uint32_t m_extra[4]; };  // 0x30 bytes
class hkMotionState { public:
    hkTransform_s010d_f100 m_transform;                                                 // +0
    hkVector4_s010d_f100 m_centerOfMass0;                                               // +0x40
    hkVector4_s010d_f100 m_centerOfMass1;                                               // +0x50
    hkQuaternion_s010d_f100 m_rotation0;                                                // +0x60
    hkQuaternion_s010d_f100 m_rotation1;                                                // +0x70
    hkVector4_s010d_f100 m_centerOfMassLocal;                                           // +0x80
    uint32_t m_misc[7];                                                      // +0x90 .. 0xab (deltaAngle, objectRadius, ...)
    uint16_t m_h0;                                                           // +0xac
    uint16_t m_h1;                                                           // +0xae
    hkMotionState& operator=(const hkMotionState& other);                    // 0x010df5d0 (member-wise copy)
};
class hkReferencedObject_s010d_f100 { public:
    virtual void* hkReferencedObject_deletingDtor(unsigned int flags);       // slot 0
    uint16_t m_memSizeAndFlags;
    int16_t  m_referenceCount;
};
class hkMemory_s010d_f100 { public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual void* allocateChunk(int nbytes, int memClass);                   // slot 4
    virtual void deallocateChunk(void* p, int nbytes, int memClass);         // slot 5
    static hkMemory_s010d_f100* s_instance;
};
#define HK_DECLARE_AGENT_ALLOCATOR_s010d_f100(SIZE) \
    void* operator new(size_t n) { \
        void* p = hkMemory_s010d_f100::s_instance->allocateChunk((int)n, HK_MEMORY_CLASS_COLLIDE); \
        ((hkReferencedObject_s010d_f100*)p)->m_memSizeAndFlags = (uint16_t)n; return p; } \
    void operator delete(void*) {}
enum { HK_SHAPE_PHANTOM_CALLBACK = 0x1a };
class hkCdBody_s010d_f100;
struct hkCollisionInput_s010d_f100;
class hkShape_s010d_f100 : public hkReferencedObject_s010d_f100 { public:
    uint32_t m_userData;                                                     // +8
    virtual void sh1();
    virtual int getType() const;                                             // slot 2 (+8)
};
struct hkPhantomCallbackShape : hkShape_s010d_f100 {
virtual void sh3();
virtual void sh4();
virtual void sh5();
virtual void sh6();
    virtual void phantomEnterEvent(const hkCdBody_s010d_f100* a, const hkCdBody_s010d_f100* b, const hkCollisionInput_s010d_f100* input);   // slot 7 (+0x1c)
    virtual void phantomLeaveEvent(const hkCdBody_s010d_f100* a, const hkCdBody_s010d_f100* b);                                  // slot 8 (+0x20)
};
struct hkTransformShape : hkShape_s010d_f100 {
    hkShape_s010d_f100* m_childShape;                                                   // +0xc
    hkQuaternion_s010d_f100 m_rotation;                                                 // +0x10
    hkTransform_s010d_f100 m_transform;                                                 // +0x20
};
class hkCdBody_s010d_f100 { public:
    const hkShape_s010d_f100* m_shape;                    // +0
    uint32_t m_shapeKey;                       // +4
    const hkMotionState* m_motion;             // +8
    const hkCdBody_s010d_f100* m_parent;                  // +0xc
};
class hkCollisionDispatcher_s010d_f100;
struct hkCollisionInput_s010d_f100 {
    hkCollisionDispatcher_s010d_f100* m_dispatcher;       // +0
    uint32_t m_pad[2];
    hkBool m_createPredictiveAgents;           // +0xc (selects the predictive agent type table)
    uint8_t m_pad2[3];
};
struct hkProcessCollisionInput_s010d_f100 : hkCollisionInput_s010d_f100 {};
struct hkLinearCastCollisionInput_s010d_f100 : hkCollisionInput_s010d_f100 {
    hkVector4_s010d_f100 m_path;                          // +0x10
    uint32_t m_pad3[4];                        // total 0x30 bytes
};
struct hkCdPoint_s010d_f100 { hkContactPoint_s010d_f100 m_contact; const hkCdBody_s010d_f100* m_cdBodyA; const hkCdBody_s010d_f100* m_cdBodyB; };
class hkCdPointCollector_s010d_f100 { public:
    virtual void v0();
    virtual void addCdPoint(const hkCdPoint_s010d_f100& point);
    float m_earlyOutDistance;                  // +4
};
class hkCdBodyPairCollector_s010d_f100 { public:
    virtual void v0();
    virtual void addCdBodyPair(const hkCdBody_s010d_f100& a, const hkCdBody_s010d_f100& b);       // slot 1 (+4)
    hkBool m_earlyOut;                         // +4
};
struct hkProcessCollisionOutput_s010d_f100 {
    hkProcessCdPoint_s010d_f100* m_firstFreeContactPoint; // +0
    uint32_t m_pad0[3];
    hkContactPoint_s010d_f100 m_toiContact;               // +0x10
    hkProcessCdPoint_s010d_f100 m_contactPoints[256];     // +0x30
    uint32_t m_toiProperties;                  // +0x3030
    hkTime   m_toiTime;                        // +0x3034
};
class hkCollisionAgent_s010d_f100 : public hkReferencedObject_s010d_f100 { public:
    hkContactMgr* m_contactMgr;                // +8
    virtual void ag1();
    virtual void getPenetrations(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkCdBodyPairCollector_s010d_f100&);   // +8
    virtual void getClosestPoints(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkCdPointCollector_s010d_f100&);     // +0xc
    virtual void linearCast(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkLinearCastCollisionInput_s010d_f100&, hkCdPointCollector_s010d_f100&, hkCdPointCollector_s010d_f100*);  // +0x10
    virtual void processCollision(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkProcessCollisionInput_s010d_f100&, hkProcessCollisionOutput_s010d_f100&);  // +0x14
    virtual void cleanup();                                                                                            // +0x18
    virtual void updateShapeCollectionFilter(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&);               // +0x1c
};
typedef hkCollisionAgent_s010d_f100* (__cdecl *hkAgentCreateFunc_s010d_f100)(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkContactMgr*);
typedef void (__cdecl *hkAgentGetPenetrationsFunc_s010d_f100)(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkCdBodyPairCollector_s010d_f100&);
typedef void (__cdecl *hkAgentGetClosestPointsFunc_s010d_f100)(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkCdPointCollector_s010d_f100&);
typedef void (__cdecl *hkAgentLinearCastFunc_s010d_f100)(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkLinearCastCollisionInput_s010d_f100&, hkCdPointCollector_s010d_f100&, hkCdPointCollector_s010d_f100*);
struct hkAgentFuncs_s010d_f100 {                          // hkCollisionDispatcher::AgentFuncs (0x14 bytes in the 32-bit binary)
    hkAgentCreateFunc_s010d_f100 m_createFunc;            // +0
    hkAgentGetPenetrationsFunc_s010d_f100 m_getPenetrationsFunc;   // +4
    hkAgentGetClosestPointsFunc_s010d_f100 m_getClosestPointFunc;  // +8
    hkAgentLinearCastFunc_s010d_f100 m_linearCastFunc;    // +0xc
    hkBool m_isFlipped;                        // +0x10
    hkBool m_isPredictive;                     // +0x11
};
class hkCollisionDispatcher_s010d_f100 { public:
    uint8_t m_pad0[0x190];                     // (32-bit layout)
    uint8_t m_agent2Types[32][32];             // +0x190: [typeA][typeB] -> agent index (non predictive)
    uint8_t m_agent2TypesPredictive[32][32];   // +0x590
    hkAgentFuncs_s010d_f100 m_agent2Func[1];              // +0x990, stride 0x14 in the binary
    void registerCollisionAgent(hkAgentFuncs_s010d_f100& funcs, int typeA, int typeB);   // 0x010cd3e0
};
struct hkMonitorCommand_s010d_f100 { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_pad; };   // 12 bytes (32-bit)
#define HK_TIMER_COMMAND(name) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand_s010d_f100* c_ = (hkMonitorCommand_s010d_f100*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_commandAndMonitor = name; \
        c_->m_time0 = (uint32_t)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_BEGIN(name) HK_TIMER_COMMAND(name)
#define HK_TIMER_END()       HK_TIMER_COMMAND(hkMonitorTimerEndTag)
class hkSymmetricAgentFlipCastCollector_s010d_f100 : public hkCdPointCollector_s010d_f100 { public:        // vtable 0x014a43ac
    uint32_t m_pad[2];
    hkVector4_s010d_f100 m_path;                                                   // +0x10
    hkCdPointCollector_s010d_f100* m_original;                                     // +0x20
    hkSymmetricAgentFlipCastCollector_s010d_f100(const hkVector4_s010d_f100& path, hkCdPointCollector_s010d_f100* c) : m_path(path), m_original(c) { m_earlyOutDistance = HK_REAL_MAX; }
    virtual void addCdPoint(const hkCdPoint_s010d_f100& point);
};
class hkThreadMemory { public: void deallocateChunk(void* p, int nbytes, int memClass); };      // 0x0107db10
struct hkReferencedObjectWithArray : hkReferencedObject_s010d_f100 {
    uint32_t m_pad8;                           // +8
    uint32_t* m_data;                          // +0xc   hkArray: data (4 byte elements)
    int m_size;                                // +0x10
    int m_capacityAndFlags;                    // +0x14  (bit 31: do not deallocate)
    hkReferencedObjectWithArray* destroy(unsigned flags);
};
struct hkListAgent : hkCollisionAgent_s010d_f100 {
    uint32_t* m_agentsData;                    // +0xc
    int m_agentsSize;                          // +0x10
    int m_agentsCapacityAndFlags;              // +0x14
    uint32_t m_pad[4];                         // object size 0x28
    hkListAgent(const hkCdBody_s010d_f100& a, const hkCdBody_s010d_f100& b, const hkCollisionInput_s010d_f100& input, hkContactMgr* mgr);   // FUN_010dedf0
    virtual void linearCast(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkLinearCastCollisionInput_s010d_f100&, hkCdPointCollector_s010d_f100&, hkCdPointCollector_s010d_f100*);
};
struct hkSymmetricAgent_hkListAgent : hkListAgent {
    hkSymmetricAgent_hkListAgent(const hkCdBody_s010d_f100& A, const hkCdBody_s010d_f100& B, const hkCollisionInput_s010d_f100& input, hkContactMgr* mgr)
        : hkListAgent(B, A, input, mgr) {}
    HK_DECLARE_AGENT_ALLOCATOR_s010d_f100(0x28)
    virtual void linearCast(const hkCdBody_s010d_f100& bodyA, const hkCdBody_s010d_f100& bodyB, const hkLinearCastCollisionInput_s010d_f100& input, hkCdPointCollector_s010d_f100& collector, hkCdPointCollector_s010d_f100* startCollector);
    static hkCollisionAgent_s010d_f100* createListBAgent(const hkCdBody_s010d_f100& A, const hkCdBody_s010d_f100& B, const hkCollisionInput_s010d_f100& input, hkContactMgr* mgr);
};
static inline const hkCdBody_s010d_f100* hkCdBody_getRoot(const hkCdBody_s010d_f100* b)
{
    while (b->m_parent) b = b->m_parent;
    return b;
}
struct hkPhantomAgent : hkCollisionAgent_s010d_f100 {            // 0x24 bytes
    const hkCdBody_s010d_f100* m_rootA;                           // +0xc
    const hkCdBody_s010d_f100* m_rootB;                           // +0x10
    hkPhantomCallbackShape* m_phantomShapeA;           // +0x14
    hkPhantomCallbackShape* m_phantomShapeB;           // +0x18
    int m_shapeTypeA;                                  // +0x1c
    int m_shapeTypeB;                                  // +0x20
    HK_DECLARE_AGENT_ALLOCATOR_s010d_f100(0x24)
    hkPhantomAgent(const hkCdBody_s010d_f100& A, const hkCdBody_s010d_f100& B, hkContactMgr* mgr);
    virtual void getPenetrations(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkCdBodyPairCollector_s010d_f100&);
    virtual void cleanup();
    static void __cdecl staticGetPenetrations(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkCdBodyPairCollector_s010d_f100&);
    static hkCollisionAgent_s010d_f100* __cdecl createPhantomAgent(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkContactMgr*);
    static void __cdecl registerAgent(hkCollisionDispatcher_s010d_f100* dispatcher);
};
struct hkTransformAgent : hkCollisionAgent_s010d_f100 {           // 0x10 bytes
    hkCollisionAgent_s010d_f100* m_childAgent;                    // +0xc
    HK_DECLARE_AGENT_ALLOCATOR_s010d_f100(0x10)
    virtual void getPenetrations(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkCdBodyPairCollector_s010d_f100&);
    virtual void getClosestPoints(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkCdPointCollector_s010d_f100&);
    virtual void linearCast(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkLinearCastCollisionInput_s010d_f100&, hkCdPointCollector_s010d_f100&, hkCdPointCollector_s010d_f100*);
    virtual void processCollision(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkProcessCollisionInput_s010d_f100&, hkProcessCollisionOutput_s010d_f100&);
    virtual void cleanup();
    virtual void updateShapeCollectionFilter(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&);
    static hkTransformAgent* __cdecl createTransformAAgent(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkContactMgr*);
    static void __cdecl staticLinearCast(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkLinearCastCollisionInput_s010d_f100&, hkCdPointCollector_s010d_f100&, hkCdPointCollector_s010d_f100*);
    static void __cdecl staticGetClosestPoints(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkCdPointCollector_s010d_f100&);
    static void __cdecl staticGetPenetrations(const hkCdBody_s010d_f100&, const hkCdBody_s010d_f100&, const hkCollisionInput_s010d_f100&, hkCdBodyPairCollector_s010d_f100&);
};
struct hkTransformedChildBody : hkCdBody_s010d_f100 {
    hkTransform_s010d_f100 m_transform;
    hkTransformedChildBody(const hkCdBody_s010d_f100& A)
    {
        const hkTransformShape* shape = (const hkTransformShape*)A.m_shape;
        m_transform.setMul(A.m_motion->m_transform, shape->m_transform);
        m_parent = &A;
        m_motion = (const hkMotionState*)&m_transform;
        m_shapeKey = A.m_shapeKey;
        m_shape = shape->m_childShape;
    }
};
// ---- items of slice s010df100 end

// @ 0x010d0000
void __fastcall FUN_010d0000(hkMultiSphereTriangleAgent* self)
{
    for (int i = 0; i < 8; ++i) {
        hkContactPointId id = self->m_contactPointId[i];
        if (id != 0xffff)
            self->m_contactMgr->removeContactPoint(id);
    }
    if (self != 0)
        ((hkAgentBase*)self)->destroy(1);
}

// @ 0x010d0040
void hkContactPoint_s010c_fcf0::FUN_010d0040(const hkVector4_s010c_fcf0& normal, float w)
{
    m_separatingNormal.x = normal.x;
    m_separatingNormal.y = normal.y;
    m_separatingNormal.z = normal.z;
    volatile float* normalW = &m_separatingNormal.w;
    *normalW = normal.w;
    m_separatingNormal.w = w;
}

// @ 0x010d0070
void* __cdecl FUN_010d0070(const hkCdBody_s010c_fcf0& bodyA, const hkCdBody_s010c_fcf0& bodyB, const hkCollisionInput_s010c_fcf0& input, hkContactMgr* mgr)
{
    void* mem = ((hkMemory*)g_hkMemoryInstance)->allocate(0x2c, 0x1c);
    hkAgent44* node = (hkAgent44*)mem;
    const hkCdBody_s010c_fcf0* body = &bodyB;
    const uint32_t invalid = 0xffffffff;
    volatile hkAgent44* v = node;
    v->m_contactMgr = mgr;
    v->m_size = 0x2c;
    v->m_flags = 1;
    v->m_vtable = (void*)0x014a4508;
    v->m_id1c = invalid;
    v->m_id20 = invalid;
    v->m_id24 = invalid;
    v->m_id28 = invalid;
    FUN_01105d80((const hkVector4_s010c_fcf0*)((const char*)body->m_shape + 0x10), (void*)node->m_cache);
    return node;
}

// @ 0x010d00d0
void* __cdecl FUN_010d00d0(const hkCdBody_s010c_fcf0& bodyA, const hkCdBody_s010c_fcf0& bodyB, const hkCollisionInput_s010c_fcf0& input, hkContactMgr* mgr)
{
    void* mem = ((hkMemory*)g_hkMemoryInstance)->allocate(0x2c, 0x1c);
    hkAgent44* node = (hkAgent44*)mem;
    node->m_contactMgr = mgr;
    node->m_size = 0x2c;
    node->m_flags = 1;
    node->m_vtable = (void*)0x014a4508;
    node->m_id1c = 0xffffffff;
    node->m_id20 = 0xffffffff;
    node->m_id24 = 0xffffffff;
    node->m_id28 = 0xffffffff;
    FUN_01105d80((const hkVector4_s010c_fcf0*)((const char*)bodyA.m_shape + 0x10), node->m_cache);
    node->m_vtable = (void*)0x014a453c;
    return node;
}

// @ 0x010d0130
void hkMultiSphereTriangleAgent::processCollision(const hkCdBody_s010c_fcf0& bodyA, const hkCdBody_s010c_fcf0& bodyB, const hkProcessCollisionInput_s010c_fcf0& input, hkProcessCollisionOutput& result)
{
    hkTimerCommand(hkTtMultiSphereTri);

    const hkMultiSphereShape* sphereShapeA = (const hkMultiSphereShape*)bodyA.m_shape;
    const hkTriangleShape* triangleShapeB = (const hkTriangleShape*)bodyB.m_shape;

    hkVector4_s010c_fcf0 vertices[3];
    transformPoints(*bodyB.m_motion, triangleShapeB->m_vertices, 3, vertices);

    const int numSpheres = sphereShapeA->m_numSpheres;
    hkVector4_s010c_fcf0 spheres[8];
    transformPoints(*bodyA.m_motion, sphereShapeA->m_spheres, numSpheres, spheres);

    hkCollideTriangleUtil::ClosestPointTriangleResult res;
    for (int i = 0; i < numSpheres; i++)
    {
        hkContactPointId& id = m_contactPointId[numSpheres - 1 - i];
        float radiusSum = sphereShapeA->m_spheres[i].w + triangleShapeB->m_radius;
        hkCollideTriangleUtil::closestPointTriangle(spheres[i], vertices, m_closestPointTriangleCache, res);
        if (res.distance < radiusSum + input.m_tolerance)
        {
            const float k = triangleShapeB->m_radius - res.distance;
            hkProcessCdPoint* cp = result.m_firstFreeContactPoint;
            cp->m_contact.m_position = spheres[i];
            cp->m_contact.m_position.x = res.hitDirection.x * k + cp->m_contact.m_position.x;
            cp->m_contact.m_position.y = res.hitDirection.y * k + cp->m_contact.m_position.y;
            cp->m_contact.m_position.z = res.hitDirection.z * k + cp->m_contact.m_position.z;
            cp->m_contact.m_position.w = res.hitDirection.w * k + cp->m_contact.m_position.w;
            cp->m_contact.m_separatingNormal = res.hitDirection;
            cp->m_contact.m_separatingNormal.w = res.distance - radiusSum;
            if (id == 0xffff)
            {
                id = m_contactMgr->addContactPoint(bodyA, bodyB, input, *cp);
                if (id == 0xffff)
                    continue;
            }
            result.m_firstFreeContactPoint = (hkProcessCdPoint*)((char*)result.m_firstFreeContactPoint + 0x30);
            cp->m_id = id;
        }
        else if (id != 0xffff)
        {
            m_contactMgr->removeContactPoint(id);
            id = 0xffff;
        }
    }

    hkTimerCommand(hkMonitorTimerEndTag);
}

// @ 0x010d0920
void hkMultiSphereTriangleAgent_s010d_0920::getClosestPoints(const hkCdBody_s010d_0920& bodyA, const hkCdBody_s010d_0920& bodyB, const hkCollisionInput_s010d_0920& input, hkCdPointCollector_s010d_0920& collector)
{
    hkTimerCommand(hkTtMultiSphereTriangle);

    const hkMultiSphereShape_s010d_0920* sphereShapeA = (const hkMultiSphereShape_s010d_0920*)bodyA.m_shape;
    const hkTriangleShape_s010d_0920* triangleShapeB = (const hkTriangleShape_s010d_0920*)bodyB.m_shape;

    hkVector4_s010d_0920 vertices[3];
    transformPoints_s010d_0920(*bodyB.m_motion, triangleShapeB->m_vertices, 3, vertices);

    const int numSpheres = sphereShapeA->m_numSpheres;
    hkVector4_s010d_0920 spheres[8];
    transformPoints_s010d_0920(*bodyA.m_motion, sphereShapeA->m_spheres, numSpheres, spheres);

    hkCdPoint point;
    point.m_cdBodyA = &bodyA;
    point.m_cdBodyB = &bodyB;

    hkCollideTriangleUtil_s010d_0920::ClosestPointTriangleResult result;
    for (int i = 0; i < numSpheres; i++)
        HK_REPORT_CLOSEST(spheres, i, m_closestPointTriangleCache)

    hkTimerCommand(hkMonitorTimerEndTag);
}

// @ 0x010d1100
void hkMultiSphereTriangleAgent_s010d_0920::staticGetClosestPoints(const hkCdBody_s010d_0920& bodyA, const hkCdBody_s010d_0920& bodyB, const hkCollisionInput_s010d_0920& input, hkCdPointCollector_s010d_0920& collector)
{
    hkTimerCommand(hkTtMultiSphereTriangle);

    const hkMultiSphereShape_s010d_0920* sphereShapeA = (const hkMultiSphereShape_s010d_0920*)bodyA.m_shape;
    const hkTriangleShape_s010d_0920* triangleShapeB = (const hkTriangleShape_s010d_0920*)bodyB.m_shape;

    hkVector4_s010d_0920 vertices[3];
    transformPoints_s010d_0920(*bodyB.m_motion, triangleShapeB->m_vertices, 3, vertices);

    const int numSpheres = sphereShapeA->m_numSpheres;
    hkVector4_s010d_0920 spheres[8];
    transformPoints_s010d_0920(*bodyA.m_motion, sphereShapeA->m_spheres, numSpheres, spheres);

    hkCdPoint point;
    point.m_cdBodyA = &bodyA;
    point.m_cdBodyB = &bodyB;

    hkCollideTriangleUtil_s010d_0920::ClosestPointTriangleCache cache;
    hkCollideTriangleUtil_s010d_0920::setupClosestPointTriangleCache(triangleShapeB->m_vertices, cache);

    hkCollideTriangleUtil_s010d_0920::ClosestPointTriangleResult result;
    for (int i = 0; i < numSpheres; i++)
        HK_REPORT_CLOSEST(spheres, i, cache)

    hkTimerCommand(hkMonitorTimerEndTag);
}

// @ 0x010d18c0
void hkMultiSphereTriangleAgent_s010d_18c0::getPenetrations(const hkCdBody_s010d_18c0& bodyA, const hkCdBody_s010d_18c0& bodyB, const hkCollisionInput_s010d_18c0& input, hkCdBodyPairCollector_s010d_18c0& collector)
{
    const hkMultiSphereShape_s010d_18c0* sphereShapeA = (const hkMultiSphereShape_s010d_18c0*)bodyA.m_shape;
    const hkTriangleShape_s010d_18c0* triangleShapeB = (const hkTriangleShape_s010d_18c0*)bodyB.m_shape;

    hkVector4_s010d_18c0 vertices[3];
    transformPoints_s010d_18c0(*bodyB.m_motion, triangleShapeB->m_vertices, 3, vertices);

    const int numSpheres = sphereShapeA->m_numSpheres;
    hkVector4_s010d_18c0 spheres[8];
    transformPoints_s010d_18c0(*bodyA.m_motion, sphereShapeA->m_spheres, numSpheres, spheres);

    hkCollideTriangleUtil_s010d_18c0::ClosestPointTriangleResult result;
    for (int i = 0; i < numSpheres; i++)
    {
        const float radiusSum = sphereShapeA->m_spheres[i].w + triangleShapeB->m_radius;
        hkCollideTriangleUtil_s010d_18c0::closestPointTriangle(spheres[i], vertices, m_closestPointTriangleCache, result);
        if (result.distance < radiusSum)
        {
            collector.addCdBodyPair(bodyA, bodyB);
            return;
        }
    }
}

// @ 0x010d1f40
void hkMultiSphereTriangleAgent_s010d_18c0::staticGetPenetrations(const hkCdBody_s010d_18c0& bodyA, const hkCdBody_s010d_18c0& bodyB, const hkCollisionInput_s010d_18c0& input, hkCdBodyPairCollector_s010d_18c0& collector)
{
    const hkMultiSphereShape_s010d_18c0* sphereShapeA = (const hkMultiSphereShape_s010d_18c0*)bodyA.m_shape;
    const hkTriangleShape_s010d_18c0* triangleShapeB = (const hkTriangleShape_s010d_18c0*)bodyB.m_shape;

    hkVector4_s010d_18c0 vertices[3];
    transformPoints_s010d_18c0(*bodyB.m_motion, triangleShapeB->m_vertices, 3, vertices);

    const int numSpheres = sphereShapeA->m_numSpheres;
    hkVector4_s010d_18c0 spheres[8];
    transformPoints_s010d_18c0(*bodyA.m_motion, sphereShapeA->m_spheres, numSpheres, spheres);

    hkCollideTriangleUtil_s010d_18c0::ClosestPointTriangleCache cache;
    hkCollideTriangleUtil_s010d_18c0::setupClosestPointTriangleCache(triangleShapeB->m_vertices, cache);

    hkCollideTriangleUtil_s010d_18c0::ClosestPointTriangleResult result;
    for (int i = 0; i < numSpheres; i++)
    {
        const float radiusSum = sphereShapeA->m_spheres[i].w + triangleShapeB->m_radius;
        hkCollideTriangleUtil_s010d_18c0::closestPointTriangle(spheres[i], vertices, cache, result);
        if (result.distance < radiusSum)
        {
            collector.addCdBodyPair(bodyA, bodyB);
            return;
        }
    }
}

// @ 0x010d28c0
void hkCapsuleTriangleAgent::processCollision(const hkCdBody_s010d_28c0& bodyA, const hkCdBody_s010d_28c0& bodyB, const hkProcessCollisionInput_s010d_28c0& input, hkProcessCollisionOutput_s010d_28c0& output)
{
    hkTimerCommand(hkTtrcCapsuleTri);

    const hkCapsuleShape*  cap = (const hkCapsuleShape*)bodyA.m_shape;
    const hkTriangleShape_s010d_28c0* tri = (const hkTriangleShape_s010d_28c0*)bodyB.m_shape;
    const hkTransform_s010d_28c0& capXf = *(const hkTransform_s010d_28c0*)bodyA.m_motion;
    const hkTransform_s010d_28c0& triXf = *(const hkTransform_s010d_28c0*)bodyB.m_motion;

    hkVector4_s010d_28c0 capSeg[2];
    HK_XFORM_ONE_s010d_28c0(capSeg[0], cap->m_vertexA, capXf)
    HK_XFORM_ONE_s010d_28c0(capSeg[1], cap->m_vertexB, capXf)

    hkVector4_s010d_28c0 triVerts[3];
    HK_XFORM_ONE_s010d_28c0(triVerts[0], tri->m_vertexA, triXf)
    HK_XFORM_ONE_s010d_28c0(triVerts[1], tri->m_vertexB, triXf)
    HK_XFORM_ONE_s010d_28c0(triVerts[2], tri->m_vertexC, triXf)

    hkCapsTriangleManifold manifold;
    hkCollideCapsuleUtilManifoldCapsVsTriangle(capSeg, cap->m_radius, triVerts, tri->m_radius,
                                               (char*)this + 0x14, input.m_tolerance, 1, &manifold);

    hkContactMgr_s010d_28c0* mgr = *(hkContactMgr_s010d_28c0**)((char*)this + 8);
    unsigned short* keys = (unsigned short*)((char*)this + 0xc);
    for (int i = 0; i < 3; i++, keys++)
    {
        const hkContactPoint_s010d_28c0& c = manifold.m_contact[i];
        if (c.m_separatingNormal.w < input.m_tolerance)
        {
            if (*keys == 0xffff)
            {
                unsigned short k = mgr->addPoint(&bodyA, &bodyB, &input, &c);
                *keys = k;
                if (k == 0xffff)
                    continue;
            }
            hkContactPoint_s010d_28c0* p = (hkContactPoint_s010d_28c0*)output.m_firstContactPoint;
            output.m_firstContactPoint = (char*)p + 0x30;
            p->m_position = c.m_position;
            p->m_separatingNormal = c.m_separatingNormal;
            *(unsigned short*)((char*)p + 0x20) = *keys;
        }
        else
        {
            if (*keys != 0xffff)
            {
                mgr->removePoint(*keys);
                *keys = 0xffff;
            }
        }
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d2d80
void hkCapsuleTriangleAgent::getClosestPoints(const hkCdBody_s010d_28c0& bodyA, const hkCdBody_s010d_28c0& bodyB, const hkCollisionInput_s010d_28c0& input, hkCdPointCollector_s010d_28c0& collector)
{
    hkTimerCommand(hkTtrcCapsTriangle);

    const hkCapsuleShape*  cap = (const hkCapsuleShape*)bodyA.m_shape;
    const hkTriangleShape_s010d_28c0* tri = (const hkTriangleShape_s010d_28c0*)bodyB.m_shape;
    const hkTransform_s010d_28c0& capXf = *(const hkTransform_s010d_28c0*)bodyA.m_motion;
    const hkTransform_s010d_28c0& triXf = *(const hkTransform_s010d_28c0*)bodyB.m_motion;

    hkVector4_s010d_28c0 capSeg[2];
    HK_XFORM_ONE_s010d_28c0(capSeg[0], cap->m_vertexA, capXf)
    HK_XFORM_ONE_s010d_28c0(capSeg[1], cap->m_vertexB, capXf)

    hkVector4_s010d_28c0 triVerts[3];
    HK_XFORM_ONE_s010d_28c0(triVerts[0], tri->m_vertexA, triXf)
    HK_XFORM_ONE_s010d_28c0(triVerts[1], tri->m_vertexB, triXf)
    HK_XFORM_ONE_s010d_28c0(triVerts[2], tri->m_vertexC, triXf)

    hkCapsTriangleManifold manifold;
    hkCollideCapsuleUtilManifoldCapsVsTriangle(capSeg, cap->m_radius, triVerts, tri->m_radius,
                                               (char*)this + 0x14, input.m_tolerance, 0, &manifold);

    if (manifold.m_contact[1].m_separatingNormal.w < manifold.m_contact[0].m_separatingNormal.w)
    {
        if (manifold.m_contact[1].m_separatingNormal.w < input.m_tolerance)
            collector.addCdPoint(&manifold.m_contact[1]);
    }
    else
    {
        if (manifold.m_contact[0].m_separatingNormal.w < input.m_tolerance)
            collector.addCdPoint(&manifold.m_contact[0]);
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d32a0
void hkCapsuleTriangleAgent::staticGetClosestPoints(const hkCdBody_s010d_28c0& bodyA, const hkCdBody_s010d_28c0& bodyB, const hkCollisionInput_s010d_28c0& input, hkCdPointCollector_s010d_28c0& collector)
{
    hkTimerCommand(hkTtrcCapsTriangle);

    const hkCapsuleShape*  cap = (const hkCapsuleShape*)bodyA.m_shape;
    const hkTriangleShape_s010d_28c0* tri = (const hkTriangleShape_s010d_28c0*)bodyB.m_shape;
    const hkTransform_s010d_28c0& capXf = *(const hkTransform_s010d_28c0*)bodyA.m_motion;
    const hkTransform_s010d_28c0& triXf = *(const hkTransform_s010d_28c0*)bodyB.m_motion;

    char cache[0x40];
    hkCollideTriangleUtilSetupCache((const hkVector4_s010d_28c0*)((const char*)bodyB.m_shape + 0x10), cache);

    hkVector4_s010d_28c0 capSeg[2];
    HK_XFORM_ONE_s010d_28c0(capSeg[0], cap->m_vertexA, capXf)
    HK_XFORM_ONE_s010d_28c0(capSeg[1], cap->m_vertexB, capXf)

    hkVector4_s010d_28c0 triVerts[3];
    HK_XFORM_ONE_s010d_28c0(triVerts[0], tri->m_vertexA, triXf)
    HK_XFORM_ONE_s010d_28c0(triVerts[1], tri->m_vertexB, triXf)
    HK_XFORM_ONE_s010d_28c0(triVerts[2], tri->m_vertexC, triXf)

    hkCapsTriangleManifold manifold;
    hkCollideCapsuleUtilManifoldCapsVsTriangle(capSeg, cap->m_radius, triVerts, tri->m_radius,
                                               cache, input.m_tolerance, 0, &manifold);

    if (manifold.m_contact[1].m_separatingNormal.w < manifold.m_contact[0].m_separatingNormal.w)
    {
        if (manifold.m_contact[1].m_separatingNormal.w < input.m_tolerance)
            collector.addCdPoint(&manifold.m_contact[1]);
    }
    else
    {
        if (manifold.m_contact[0].m_separatingNormal.w < input.m_tolerance)
            collector.addCdPoint(&manifold.m_contact[0]);
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d4070
void hkCapsuleTriangleAgent_s010d_37d0::getPenetrationsWrapper(const void* bodyA, const void* bodyB, const void* input, void* collector)
{
    hkTempPairCollector tmp;
    tmp.m_extra = collector;
    tmp.m_earlyOut = 0;
    tmp.m_vtbl = (const void*)0x014a43b4;
    getPenetrations(*(const hkCdBody_s010d_37d0*)bodyB, *(const hkCdBody_s010d_37d0*)bodyA,
                    *(const hkCollisionInput_s010d_37d0*)input, *(hkCdBodyPairCollector_s010d_37d0*)&tmp);
}

// @ 0x010d40f0
void hkCapsuleTriangleAgent_s010d_37d0::getClosestPointsWrapper(const void* bodyA, const void* bodyB, const void* input, void* collector)
{
    hkTempPointCollector tmp;
    tmp.m_extra = collector;
    tmp.m_earlyOutDistance = 0x7f7fffeeu;
    tmp.m_vtbl = (const void*)0x014a43a4;
    getClosestPoints(*(const hkCdBody_s010d_37d0*)bodyB, *(const hkCdBody_s010d_37d0*)bodyA,
                     *(const hkCollisionInput_s010d_37d0*)input, *(hkCdPointCollector_s010d_37d0*)&tmp);
}

// @ 0x010d4170
void hkCapsuleTriangleAgent_s010d_37d0::processCollisionThunk(const void* bodyA, const void* bodyB, const void* input, void* output)
{
    float oldNormal = *(float*)((char*)output + 0x3034);
    const void* first = *(const void**)output;
    processCollision(*(const hkCdBody_s010d_37d0*)bodyB, *(const hkCdBody_s010d_37d0*)bodyA, input, output);
    for (unsigned cp = (unsigned)first; cp < *(unsigned*)output; cp += 0x30)
        ((hkContactPoint_s010d_37d0*)cp)->setFlipped(*(const hkContactPoint_s010d_37d0*)cp);
    if (oldNormal != *(float*)((char*)output + 0x3034))
    {
        float* n = (float*)((char*)output + 0x20);
        n[0] = -n[0];
        n[1] = -n[1];
        n[2] = -n[2];
    }
}

// @ 0x010d4280
void* hkCapsuleCapsuleAgent__create(const void* bodyA, const void* bodyB, const void* input, void* contactMgr)
{
    hkCapsuleCapsuleAgent* agent = (hkCapsuleCapsuleAgent*)g_hkMemory->alloc(0x14, 0x1c);
    *(void**)((char*)agent + 8) = contactMgr;
    *(unsigned short*)((char*)agent + 4) = 0x14;
    *(unsigned short*)((char*)agent + 6) = 1;
    *(void**)agent = (void*)0x014a4654;
    *(unsigned short*)((char*)agent + 0xc) = 0xffff;
    *(unsigned short*)((char*)agent + 0xe) = 0xffff;
    *(unsigned short*)((char*)agent + 0x10) = 0xffff;
    return agent;
}

// @ 0x010d42c0
void hkCapsuleCapsuleAgent::processCollision(const void* bodyA, const void* bodyB, const void* input, void* output)
{
    hkTimerCommand(hkTtrcCapsCaps);

    const hkTransform_s010d_37d0& xfA = *(const hkTransform_s010d_37d0*)((const hkCdBody_s010d_37d0*)bodyA)->m_motion;
    const hkTransform_s010d_37d0& xfB = *(const hkTransform_s010d_37d0*)((const hkCdBody_s010d_37d0*)bodyB)->m_motion;
    const hkCapsuleShape_s010d_37d0* capA = (const hkCapsuleShape_s010d_37d0*)((const hkCdBody_s010d_37d0*)bodyA)->m_shape;
    const hkCapsuleShape_s010d_37d0* capB = (const hkCapsuleShape_s010d_37d0*)((const hkCdBody_s010d_37d0*)bodyB)->m_shape;

    hkVector4_s010d_37d0 segA[2], segB[2];
    HK_XFORM_ONE_s010d_37d0(segA[0], capA->m_vertexA, xfA)
    HK_XFORM_ONE_s010d_37d0(segA[1], capA->m_vertexB, xfA)
    HK_XFORM_ONE_s010d_37d0(segB[0], capB->m_vertexA, xfB)
    HK_XFORM_ONE_s010d_37d0(segB[1], capB->m_vertexB, xfB)

    hkContactManifold manifold;
    const float tol = *(const float*)((const char*)input + 8);
    manifold.m_contact[0].m_separatingNormal.w = tol;
    manifold.m_contact[1].m_separatingNormal.w = tol;
    manifold.m_contact[2].m_separatingNormal.w = tol;
    hkCollideCapsuleUtilManifoldCapsVsCapsule(segA, capA->m_radius, segB, capB->m_radius, &manifold);

    hkContactMgr_s010d_37d0* mgr = *(hkContactMgr_s010d_37d0**)((char*)this + 8);
    for (int i = 0; i < 3; i++)
    {
        if (tol <= manifold.m_contact[i].m_separatingNormal.w)
        {
            if (m_keys[i] != 0xffff)
            {
                mgr->removePoint(m_keys[i]);
                m_keys[i] = 0xffff;
            }
        }
        else
        {
            if (m_keys[i] == 0xffff)
            {
                unsigned short k = mgr->addPoint(bodyA, bodyB, input, &manifold.m_contact[i]);
                m_keys[i] = k;
                if (k == 0xffff)
                    continue;
            }
            hkContactPoint_s010d_37d0* p = (hkContactPoint_s010d_37d0*)*(void**)output;
            *(char**)output = (char*)p + 0x30;
            p->m_position = manifold.m_contact[i].m_position;
            p->m_separatingNormal = manifold.m_contact[i].m_separatingNormal;
            *(unsigned short*)((char*)p + 0x20) = m_keys[i];
        }
    }
    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d4730
void hkCapsuleCapsuleAgent_s010d_4730::getClosestPoints(const hkCdBody_s010d_4730& bodyA, const hkCdBody_s010d_4730& bodyB, const hkCollisionInput_s010d_4730& input, hkCdPointCollector_s010d_4730& collector)
{
    hkTimerCommand(hkTtrcCapsCaps);

    const hkTransform_s010d_4730& xfA = *(const hkTransform_s010d_4730*)bodyA.m_motion;
    const hkTransform_s010d_4730& xfB = *(const hkTransform_s010d_4730*)bodyB.m_motion;
    const hkCapsuleShape_s010d_4730* capA = (const hkCapsuleShape_s010d_4730*)bodyA.m_shape;
    const hkCapsuleShape_s010d_4730* capB = (const hkCapsuleShape_s010d_4730*)bodyB.m_shape;

    hkVector4_s010d_4730 segA[2];
    HK_XFORM_ONE_s010d_4730(segA[0], capA->m_vertexA, xfA)
    HK_XFORM_ONE_s010d_4730(segA[1], capA->m_vertexB, xfA)

    hkVector4_s010d_4730 segB[2];
    HK_XFORM_ONE_s010d_4730(segB[0], capB->m_vertexA, xfB)
    HK_XFORM_ONE_s010d_4730(segB[1], capB->m_vertexB, xfB)

    hkCapsCapsClosestPointResult result;
    if (hkCollideCapsuleUtilClostestPointCapsVsCaps(segA, capA->m_radius, segB, capB->m_radius,
                                                    input.m_tolerance, &result) == 0)
    {
        collector.addCdPoint(&result);
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d4b00
void hkCapsuleCapsuleAgent_s010d_4730::staticGetClosestPoints(const hkCdBody_s010d_4730& bodyA, const hkCdBody_s010d_4730& bodyB, const hkCollisionInput_s010d_4730& input, hkCdPointCollector_s010d_4730& collector)
{
    hkTimerCommand(hkTtrcCapsCaps);

    const hkTransform_s010d_4730& xfA = *(const hkTransform_s010d_4730*)bodyA.m_motion;
    const hkTransform_s010d_4730& xfB = *(const hkTransform_s010d_4730*)bodyB.m_motion;
    const hkCapsuleShape_s010d_4730* capA = (const hkCapsuleShape_s010d_4730*)bodyA.m_shape;
    const hkCapsuleShape_s010d_4730* capB = (const hkCapsuleShape_s010d_4730*)bodyB.m_shape;

    hkVector4_s010d_4730 segA[2];
    HK_XFORM_ONE_s010d_4730(segA[0], capA->m_vertexA, xfA)
    HK_XFORM_ONE_s010d_4730(segA[1], capA->m_vertexB, xfA)

    hkVector4_s010d_4730 segB[2];
    HK_XFORM_ONE_s010d_4730(segB[0], capB->m_vertexA, xfB)
    HK_XFORM_ONE_s010d_4730(segB[1], capB->m_vertexB, xfB)

    hkCapsCapsClosestPointResult result;
    if (hkCollideCapsuleUtilClostestPointCapsVsCaps(segA, capA->m_radius, segB, capB->m_radius,
                                                    input.m_tolerance, &result) == 0)
    {
        collector.addCdPoint(&result);
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d4ed0
void hkCapsuleCapsuleAgent_s010d_4730::staticGetPenetrations(const hkCdBody_s010d_4730& bodyA, const hkCdBody_s010d_4730& bodyB, const hkCollisionInput_s010d_4730& input, hkCdBodyPairCollector_s010d_4730& collector)
{
    hkTimerCommand(hkTtrcCapsCaps);

    const hkTransform_s010d_4730& xfA = *(const hkTransform_s010d_4730*)bodyA.m_motion;
    const hkTransform_s010d_4730& xfB = *(const hkTransform_s010d_4730*)bodyB.m_motion;
    const hkCapsuleShape_s010d_4730* capA = (const hkCapsuleShape_s010d_4730*)bodyA.m_shape;
    const hkCapsuleShape_s010d_4730* capB = (const hkCapsuleShape_s010d_4730*)bodyB.m_shape;

    hkVector4_s010d_4730 segA[2];
    HK_XFORM_ONE_s010d_4730(segA[0], capA->m_vertexA, xfA)
    HK_XFORM_ONE_s010d_4730(segA[1], capA->m_vertexB, xfA)

    hkVector4_s010d_4730 segB[2];
    HK_XFORM_ONE_s010d_4730(segB[0], capB->m_vertexA, xfB)
    HK_XFORM_ONE_s010d_4730(segB[1], capB->m_vertexB, xfB)

    hkVector4_s010d_4730 dirA, dirB;
    dirA.x = segA[1].x - segA[0].x; dirA.y = segA[1].y - segA[0].y; dirA.z = segA[1].z - segA[0].z;
    dirB.x = segB[1].x - segB[0].x; dirB.y = segB[1].y - segB[0].y; dirB.z = segB[1].z - segB[0].z;

    hkCollideTriangleUtil_s010d_4730::ClosestLineSegLineSegResult res;
    hkCollideTriangleUtil_s010d_4730::closestLineSegLineSeg(segA[0], dirA, segB[0], dirB, res);

    float rsum = capB->m_radius + capA->m_radius;
    if (res.m_distanceSquared < rsum * rsum)
    {
        collector.addCdBodyPair(bodyA, bodyB);
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d5320
void __cdecl hkCapsuleCapsuleAgent__registerAgent(hkCollisionDispatcher_s010d_4730& dispatcher)
{
    hkAgentFuncs funcs;
    funcs.m_isFlipped = 0;
    funcs.m_isPredictive = 0;
    funcs.m_createFunc = (hkAgentCreateFunc)0x010d4280;
    funcs.m_getPenetrationsFunc = (hkAgentGetPenetrationsFunc)0x010d4ed0;
    funcs.m_getClosestPointFunc = (hkAgentGetClosestPointsFunc)0x010d4b00;
    funcs.m_linearCastFunc = (hkAgentLinearCastFunc)0x010ebc80;
    dispatcher.registerCollisionAgent(funcs, 8, 8);
}

// @ 0x010d5370
extern "C" void* hkSphereBoxAgent__create(const void* bodyA, const void* bodyB, const void* input, void* contactMgr)
{
    void* agent = hkMemory_s_instance->alloc(0x10, 0x1c);
    *(unsigned short*)((char*)agent + 4) = 0x10;
    *(unsigned short*)((char*)agent + 6) = 1;
    *(void**)((char*)agent + 8) = contactMgr;
    *(void**)agent = (void*)0x014a46b8;
    *(unsigned short*)((char*)agent + 0xc) = 0xffff;
    return agent;
}

// @ 0x010d53a0
extern "C" void* hkSymmetricSphereBoxAgent__create(const void* bodyA, const void* bodyB, const void* input, void* contactMgr)
{
    void* agent = hkMemory_s_instance->alloc(0x10, 0x1c);
    *(unsigned short*)((char*)agent + 4) = 0x10;
    *(unsigned short*)((char*)agent + 6) = 1;
    *(void**)((char*)agent + 8) = contactMgr;
    *(unsigned short*)((char*)agent + 0xc) = 0xffff;
    *(void**)agent = (void*)0x014a46ec;
    return agent;
}

// @ 0x010d53d0
void hkSphereBoxAgent::processCollision(const hkCdBody_s010d_53d0& bodyA, const hkCdBody_s010d_53d0& bodyB, const hkProcessCollisionInput_s010d_53d0& input, hkProcessCollisionOutput_s010d_53d0& output)
{
    hkTimerCommand(hkTtrcSphereBox);

    const hkSphereShape* sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkBoxShape*    box    = (const hkBoxShape*)bodyB.m_shape;
    const hkTransform_s010d_53d0&   boxXf  = *(const hkTransform_s010d_53d0*)bodyB.m_motion;
    const hkVector4_s010d_53d0&     sphPos = *(const hkVector4_s010d_53d0*)((const char*)bodyA.m_motion + 0x30);

    float* cp = (float*)output.m_firstFreeContactPoint;

    hkVector4_s010d_53d0 p;
    p.setTransformedInversePos(boxXf, sphPos);

    const float ax = (float)fabs(p.x);
    const float ay = (float)fabs(p.y);
    const float az = (float)fabs(p.z);

    // distance from the sphere centre to the box surface on each axis (<= 0)
    const float dX = hkMinF(ax, box->m_halfExtents.x) - ax;
    const float dY = hkMinF(ay, box->m_halfExtents.y) - ay;
    const float dZ = hkMinF(az, box->m_halfExtents.z) - az;

    float sep;

    if (dX >= 0.0f && dY >= 0.0f && dZ >= 0.0f)
    {
        // the sphere centre is inside the box: push out along the face with the
        // smallest penetration
        const float fX = ax - box->m_halfExtents.x;
        const float fY = ay - box->m_halfExtents.y;
        const float fZ = az - box->m_halfExtents.z;

        int          axis;
        float        fMax;
        const float* row;
        if (fX <= fY)
        {
            if (fY <= fZ) { axis = 2; fMax = fZ; row = &boxXf.m_basis[2].x; }
            else          { axis = 1; fMax = fY; row = &boxXf.m_basis[1].x; }
        }
        else
        {
            if (fX <= fZ) { axis = 2; fMax = fZ; row = &boxXf.m_basis[2].x; }
            else          { axis = 0; fMax = fX; row = &boxXf.m_basis[0].x; }
        }

        cp[4] = row[0];
        cp[5] = row[1];
        cp[6] = row[2];
        if (((const float*)&p)[axis] < 0.0f)
        {
            cp[4] = -cp[4];
            cp[5] = -cp[5];
            cp[6] = -cp[6];
            cp[7] = -cp[7];
        }

        sep = fMax - box->m_radius - sphere->m_radius;
    }
    else
    {
        // sphere centre outside the box: normalise the penetration vector and
        // rotate it into world space
        const float dist = (float)sqrt(dX * dX + (dZ * dZ + dY * dY));
        const float inv  = 1.0f / dist;

        // The original scales the per-axis penetration immediately, while `inv` still
        // lives in an x87 register; it is never rounded to float (which would overflow
        // to +inf for the tiny denormal distances this test can produce).
        const float sX = dX * inv;
        const float sY = dY * inv;
        const float sZ = dZ * inv;

        sep = dist - (box->m_radius + sphere->m_radius);

        if (sep > input.m_tolerance)
        {
            if (m_contactPointId != 0xffff)
            {
                m_contactMgr->removeContactPoint(m_contactPointId);
                m_contactPointId = 0xffff;
            }
            hkTimerCommand(hkTtrcEnd);
            return;
        }

        const float nx = hkNegFlip(sX, p.x);
        const float ny = hkNegFlip(sY, p.y);
        const float nz = hkNegFlip(sZ, p.z);

        cp[4] = nx * boxXf.m_basis[0].x + (ny * boxXf.m_basis[1].x + nz * boxXf.m_basis[2].x);
        cp[5] = nx * boxXf.m_basis[0].y + (ny * boxXf.m_basis[1].y + nz * boxXf.m_basis[2].y);
        cp[6] = nx * boxXf.m_basis[0].z + (ny * boxXf.m_basis[1].z + nz * boxXf.m_basis[2].z);
        cp[7] = 0.0f;
    }

    const float scale = -sep - sphere->m_radius;

    cp[0] = sphPos.x;
    cp[1] = sphPos.y;
    cp[2] = sphPos.z;
    cp[3] = sphPos.w;
    cp[0] = cp[0] + scale * cp[4];
    cp[1] = cp[1] + scale * cp[5];
    cp[2] = cp[2] + scale * cp[6];
    cp[3] = cp[3] + scale * cp[7];
    cp[7] = sep;

    if (m_contactPointId == 0xffff)
    {
        m_contactPointId = (unsigned short)m_contactMgr->createContactPoint(
            bodyA, bodyB, (const hkProcessCollisionInput_s010d_53d0&)input, (hkContactPoint_s010d_53d0*)cp);
    }
    if (m_contactPointId != 0xffff)
    {
        *(unsigned short*)(cp + 8) = m_contactPointId;
        output.m_firstFreeContactPoint = output.m_firstFreeContactPoint + 1;
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d5850
void hkSphereBoxAgent::getClosestPoints(const hkCdBody_s010d_53d0& bodyA, const hkCdBody_s010d_53d0& bodyB, const hkCollisionInput_s010d_53d0& input, hkCdPointCollector_s010d_53d0& collector)
{
    hkTimerCommand(hkTtrcSphereBox);

    const hkSphereShape* sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkBoxShape*    box    = (const hkBoxShape*)bodyB.m_shape;
    const hkTransform_s010d_53d0&   boxXf  = *(const hkTransform_s010d_53d0*)bodyB.m_motion;
    const hkVector4_s010d_53d0&     sphPos = *(const hkVector4_s010d_53d0*)((const char*)bodyA.m_motion + 0x30);

    hkVector4_s010d_53d0 p;
    p.setTransformedInversePos(boxXf, sphPos);

    const float ax = (float)fabs(p.x);
    const float ay = (float)fabs(p.y);
    const float az = (float)fabs(p.z);

    const float dX = hkMinF(ax, box->m_halfExtents.x) - ax;
    const float dY = hkMinF(ay, box->m_halfExtents.y) - ay;
    const float dZ = hkMinF(az, box->m_halfExtents.z) - az;

    hkVector4_s010d_53d0 normal;
    float     sep;

    if (dX >= 0.0f && dY >= 0.0f && dZ >= 0.0f)
    {
        const float fX = ax - box->m_halfExtents.x;
        const float fY = ay - box->m_halfExtents.y;
        const float fZ = az - box->m_halfExtents.z;

        int          axis;
        float        fMax;
        const float* row;
        if (fX <= fY)
        {
            if (fY <= fZ) { axis = 2; fMax = fZ; row = &boxXf.m_basis[2].x; }
            else          { axis = 1; fMax = fY; row = &boxXf.m_basis[1].x; }
        }
        else
        {
            if (fX <= fZ) { axis = 2; fMax = fZ; row = &boxXf.m_basis[2].x; }
            else          { axis = 0; fMax = fX; row = &boxXf.m_basis[0].x; }
        }

        normal.x = row[0];
        normal.y = row[1];
        normal.z = row[2];
        normal.w = 0.0f;
        if (((const float*)&p)[axis] < 0.0f)
        {
            normal.x = -normal.x;
            normal.y = -normal.y;
            normal.z = -normal.z;
            normal.w = -normal.w;
        }

        sep = fMax - box->m_radius - sphere->m_radius;
    }
    else
    {
        const float dist = (float)sqrt(dX * dX + (dZ * dZ + dY * dY));
        const float inv  = 1.0f / dist;

        // Scale the per-axis penetration before the early-out test, with `inv` still in
        // an x87 register (see processCollision for why it must not be rounded to float).
        const float sX = dX * inv;
        const float sY = dY * inv;
        const float sZ = dZ * inv;

        sep = dist - (box->m_radius + sphere->m_radius);

        if (sep > input.m_tolerance)
        {
            hkTimerCommand(hkTtrcEnd);
            return;
        }

        const float nx = hkNegFlip(sX, p.x);
        const float ny = hkNegFlip(sY, p.y);
        const float nz = hkNegFlip(sZ, p.z);

        normal.x = nx * boxXf.m_basis[0].x + (ny * boxXf.m_basis[1].x + nz * boxXf.m_basis[2].x);
        normal.y = nx * boxXf.m_basis[0].y + (ny * boxXf.m_basis[1].y + nz * boxXf.m_basis[2].y);
        normal.z = nx * boxXf.m_basis[0].z + (ny * boxXf.m_basis[1].z + nz * boxXf.m_basis[2].z);
        normal.w = 0.0f;
    }

    const float scale = -sep - sphere->m_radius;

    hkVector4_s010d_53d0 point;
    point.x = sphPos.x + scale * normal.x;
    point.y = sphPos.y + scale * normal.y;
    point.z = sphPos.z + scale * normal.z;
    point.w = sphPos.w + scale * normal.w;
    point.w = sep;

    collector.addCdPoint(&point);

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d5ca0
void hkSphereBoxAgent::staticGetClosestPoints(const hkCdBody_s010d_53d0& bodyA, const hkCdBody_s010d_53d0& bodyB, const hkCollisionInput_s010d_53d0& input, hkCdPointCollector_s010d_53d0& collector)
{
    hkTimerCommand(hkTtrcSphereBox);

    const hkSphereShape* sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkBoxShape*    box    = (const hkBoxShape*)bodyB.m_shape;
    const hkTransform_s010d_53d0&   boxXf  = *(const hkTransform_s010d_53d0*)bodyB.m_motion;
    const hkVector4_s010d_53d0&     sphPos = *(const hkVector4_s010d_53d0*)((const char*)bodyA.m_motion + 0x30);

    hkVector4_s010d_53d0 p;
    p.setTransformedInversePos(boxXf, sphPos);

    const float ax = (float)fabs(p.x);
    const float ay = (float)fabs(p.y);
    const float az = (float)fabs(p.z);

    const float dX = hkMinF(ax, box->m_halfExtents.x) - ax;
    const float dY = hkMinF(ay, box->m_halfExtents.y) - ay;
    const float dZ = hkMinF(az, box->m_halfExtents.z) - az;

    hkVector4_s010d_53d0 normal;
    float     sep;

    if (dX >= 0.0f && dY >= 0.0f && dZ >= 0.0f)
    {
        const float fX = ax - box->m_halfExtents.x;
        const float fY = ay - box->m_halfExtents.y;
        const float fZ = az - box->m_halfExtents.z;

        int          axis;
        float        fMax;
        const float* row;
        if (fX <= fY)
        {
            if (fY <= fZ) { axis = 2; fMax = fZ; row = &boxXf.m_basis[2].x; }
            else          { axis = 1; fMax = fY; row = &boxXf.m_basis[1].x; }
        }
        else
        {
            if (fX <= fZ) { axis = 2; fMax = fZ; row = &boxXf.m_basis[2].x; }
            else          { axis = 0; fMax = fX; row = &boxXf.m_basis[0].x; }
        }

        normal.x = row[0];
        normal.y = row[1];
        normal.z = row[2];
        normal.w = 0.0f;
        if (((const float*)&p)[axis] < 0.0f)
        {
            normal.x = -normal.x;
            normal.y = -normal.y;
            normal.z = -normal.z;
            normal.w = -normal.w;
        }

        sep = fMax - box->m_radius - sphere->m_radius;
    }
    else
    {
        const float dist = (float)sqrt(dX * dX + (dZ * dZ + dY * dY));
        const float inv  = 1.0f / dist;

        // Scale the per-axis penetration before the early-out test, with `inv` still in
        // an x87 register (see processCollision for why it must not be rounded to float).
        const float sX = dX * inv;
        const float sY = dY * inv;
        const float sZ = dZ * inv;

        sep = dist - (box->m_radius + sphere->m_radius);

        if (sep > input.m_tolerance)
        {
            hkTimerCommand(hkTtrcEnd);
            return;
        }

        const float nx = hkNegFlip(sX, p.x);
        const float ny = hkNegFlip(sY, p.y);
        const float nz = hkNegFlip(sZ, p.z);

        normal.x = nx * boxXf.m_basis[0].x + (ny * boxXf.m_basis[1].x + nz * boxXf.m_basis[2].x);
        normal.y = nx * boxXf.m_basis[0].y + (ny * boxXf.m_basis[1].y + nz * boxXf.m_basis[2].y);
        normal.z = nx * boxXf.m_basis[0].z + (ny * boxXf.m_basis[1].z + nz * boxXf.m_basis[2].z);
        normal.w = 0.0f;
    }

    const float scale = -sep - sphere->m_radius;

    hkVector4_s010d_53d0 point;
    point.x = sphPos.x + scale * normal.x;
    point.y = sphPos.y + scale * normal.y;
    point.z = sphPos.z + scale * normal.z;
    point.w = sphPos.w + scale * normal.w;
    point.w = sep;

    collector.addCdPoint(&point);

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d60f0
void hkSphereBoxAgent::staticGetPenetrations(const hkCdBody_s010d_53d0& bodyA, const hkCdBody_s010d_53d0& bodyB, const hkCollisionInput_s010d_53d0& input, hkCdBodyPairCollector_s010d_53d0& collector)
{
    hkTimerCommand(hkTtrcSphereBox);

    const hkSphereShape* sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkBoxShape*    box    = (const hkBoxShape*)bodyB.m_shape;
    const hkTransform_s010d_53d0&   boxXf  = *(const hkTransform_s010d_53d0*)bodyB.m_motion;
    const hkVector4_s010d_53d0&     sphPos = *(const hkVector4_s010d_53d0*)((const char*)bodyA.m_motion + 0x30);

    hkVector4_s010d_53d0 p;
    p.setTransformedInversePos(boxXf, sphPos);

    // closest point on the box surface in box space
    const float cx = hkClampAbs(p.x, box->m_halfExtents.x);
    const float cy = hkClampAbs(p.y, box->m_halfExtents.y);
    const float cz = hkClampAbs(p.z, box->m_halfExtents.z);

    // rotate back into world space and translate
    const float wx = cx * boxXf.m_basis[0].x + (cy * boxXf.m_basis[1].x + cz * boxXf.m_basis[2].x)
                     + boxXf.m_translation.x;
    const float wy = cx * boxXf.m_basis[0].y + (cy * boxXf.m_basis[1].y + cz * boxXf.m_basis[2].y)
                     + boxXf.m_translation.y;
    const float wz = cx * boxXf.m_basis[0].z + (cy * boxXf.m_basis[1].z + cz * boxXf.m_basis[2].z)
                     + boxXf.m_translation.z;

    const float dx = wx - sphPos.x;
    const float dy = wy - sphPos.y;
    const float dz = wz - sphPos.z;

    const float rsum = box->m_radius + sphere->m_radius;

    if (dx * dx + (dy * dy + dz * dz) < rsum * rsum)
    {
        collector.addCdBodyPair(bodyA, bodyB);
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d63a0
void hkSymmetricSphereBoxAgent::getClosestPoints(const hkCdBody_s010d_53d0& bodyA, const hkCdBody_s010d_53d0& bodyB, const hkCollisionInput_s010d_53d0& input, hkCdPointCollector_s010d_53d0& collector)
{
    hkSymPointCollectorLocal sym;
    sym.m_forward = &collector;
    sym.m_earlyOut = 0x7f7fffeeu;
    sym.m_vtable = (void*)0x014a43a4;

    hkSphereBoxAgent::getClosestPoints(bodyB, bodyA, input,
                                       *(hkCdPointCollector_s010d_53d0*)&sym);
}

// @ 0x010d6530
hkCollisionAgent* hkSphereTriangleAgent::createSphereTriangleAgent(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB, const hkCollisionInput_s010d_6420& input, hkContactMgr_s010d_6420* mgr)
{
    hkSphereTriangleAgent* agent = (hkSphereTriangleAgent*)hkMemory_s_instance_s010d_6420->alloc(0x20, 0x1c);
    agent->m_contactMgr = mgr;
    *(unsigned short*)((char*)agent + 4) = 0x20;
    *(unsigned short*)((char*)agent + 6) = 1;
    *(void**)agent = (void*)0x014a4748;
    *(unsigned short*)((char*)agent + 0xc) = 0xffff;
    hkCollideTriangleUtil_s010d_6420::setupClosestPointTriangleCache(
        (const hkVector4_s010d_6420*)((const char*)bodyB.m_shape + 0x10), agent->m_cache);
    return agent;
}

// @ 0x010d6680
hkCollisionAgent* hkSphereTriangleAgent::createTriangleSphereAgent(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB, const hkCollisionInput_s010d_6420& input, hkContactMgr_s010d_6420* mgr)
{
    hkSphereTriangleAgent* agent = (hkSphereTriangleAgent*)hkMemory_s_instance_s010d_6420->alloc(0x20, 0x1c);
    agent->m_contactMgr = mgr;
    *(unsigned short*)((char*)agent + 4) = 0x20;
    *(unsigned short*)((char*)agent + 6) = 1;
    *(void**)agent = (void*)0x014a4748;
    *(unsigned short*)((char*)agent + 0xc) = 0xffff;
    hkCollideTriangleUtil_s010d_6420::setupClosestPointTriangleCache(
        (const hkVector4_s010d_6420*)((const char*)bodyA.m_shape + 0x10), agent->m_cache);
    *(void**)agent = (void*)0x014a477c;
    return agent;
}

// @ 0x010d66e0
void hkSphereTriangleAgent::processCollision(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB, const hkProcessCollisionInput_s010d_6420& input, hkProcessCollisionOutput_s010d_6420& output)
{
    hkTimerCommand(hkTtrcSphereTri);

    const hkSphereShape*   sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkTriangleShape_s010d_6420* tri    = (const hkTriangleShape_s010d_6420*)bodyB.m_shape;
    const hkTransform_s010d_6420&     triXf  = *(const hkTransform_s010d_6420*)bodyB.m_motion;
    const hkTransform_s010d_6420&     sphXf  = *(const hkTransform_s010d_6420*)bodyA.m_motion;

    hkVector4_s010d_6420 verts[3];
    hkTriXformVertex(verts[0], tri->m_vertex[0], triXf);
    hkTriXformVertex(verts[1], tri->m_vertex[1], triXf);
    hkTriXformVertex(verts[2], tri->m_vertex[2], triXf);

    hkCollideTriangleUtil_s010d_6420::ClosestPointTriangleResult res;
    hkCollideTriangleUtil_s010d_6420::closestPointTriangle(sphXf.m_translation, verts, m_cache, res);

    hkTime rsum = sphere->m_radius + tri->m_radius;

    if (rsum + input.m_tolerance <= res.m_distance)
    {
        if (m_contactPointIndex != 0xffff)
        {
            m_contactMgr->removeContactPoint(m_contactPointIndex);
            m_contactPointIndex = 0xffff;
        }
    }
    else
    {
        float* cp = (float*)output.m_firstFreeContactPoint;
        float scale = tri->m_radius - res.m_distance;

        cp[0] = sphXf.m_translation.x;
        cp[1] = sphXf.m_translation.y;
        cp[2] = sphXf.m_translation.z;
        cp[3] = sphXf.m_translation.w;
        cp[0] = res.m_closestPoint.x * scale + cp[0];
        cp[1] = res.m_closestPoint.y * scale + cp[1];
        cp[2] = res.m_closestPoint.z * scale + cp[2];
        cp[3] = res.m_closestPoint.w * scale + cp[3];
        cp[4] = res.m_closestPoint.x;
        cp[5] = res.m_closestPoint.y;
        cp[6] = res.m_closestPoint.z;
        cp[7] = res.m_closestPoint.w;
        cp[7] = res.m_distance - rsum;

        if (m_contactPointIndex == 0xffff)
        {
            m_contactPointIndex = (unsigned short)m_contactMgr->createContactPoint(
                bodyA, bodyB, input, (hkContactPoint_s010d_6420*)cp);
        }
        if (m_contactPointIndex != 0xffff)
        {
            *(unsigned short*)(cp + 8) = m_contactPointIndex;
            output.m_firstFreeContactPoint = (hkProcessCdPoint_s010d_6420*)(cp + 0xc);
        }
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d6a80
void hkSphereTriangleAgent::getClosestPoints(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB, const hkCollisionInput_s010d_6420& input, hkCdPointCollector_s010d_6420& collector)
{
    hkTimerCommand(hkTtrcSphereTri);

    const hkSphereShape*   sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkTriangleShape_s010d_6420* tri    = (const hkTriangleShape_s010d_6420*)bodyB.m_shape;
    const hkTransform_s010d_6420&     triXf  = *(const hkTransform_s010d_6420*)bodyB.m_motion;
    const hkTransform_s010d_6420&     sphXf  = *(const hkTransform_s010d_6420*)bodyA.m_motion;

    hkVector4_s010d_6420 verts[3];
    hkTriXformVertex(verts[0], tri->m_vertex[0], triXf);
    hkTriXformVertex(verts[1], tri->m_vertex[1], triXf);
    hkTriXformVertex(verts[2], tri->m_vertex[2], triXf);

    hkCollideTriangleUtil_s010d_6420::ClosestPointTriangleResult res;
    hkCollideTriangleUtil_s010d_6420::closestPointTriangle(sphXf.m_translation, verts, m_cache, res);

    float rsum = sphere->m_radius + tri->m_radius;
    if (res.m_distance < rsum + input.m_tolerance)
    {
        hkVector4_s010d_6420 normal = res.m_closestPoint;
        float scale = tri->m_radius - res.m_distance;

        hkVector4_s010d_6420 point = sphXf.m_translation;
        point.x += normal.x * scale;
        point.y += normal.y * scale;
        point.z += normal.z * scale;
        point.w += normal.w * scale;

        collector.addCdPoint(&point);
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d6e00
void hkSphereTriangleAgent::staticGetClosestPoints(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB, const hkCollisionInput_s010d_6420& input, hkCdPointCollector_s010d_6420& collector)
{
    hkTimerCommand(hkTtrcSphereTri);

    const hkSphereShape*   sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkTriangleShape_s010d_6420* tri    = (const hkTriangleShape_s010d_6420*)bodyB.m_shape;
    const hkTransform_s010d_6420&     triXf  = *(const hkTransform_s010d_6420*)bodyB.m_motion;
    const hkTransform_s010d_6420&     sphXf  = *(const hkTransform_s010d_6420*)bodyA.m_motion;

    hkCollideTriangleUtil_s010d_6420::ClosestPointTriangleCache cache;
    hkCollideTriangleUtil_s010d_6420::setupClosestPointTriangleCache(
        (const hkVector4_s010d_6420*)((const char*)bodyB.m_shape + 0x10), cache);

    hkVector4_s010d_6420 verts[3];
    hkTriXformVertex(verts[0], tri->m_vertex[0], triXf);
    hkTriXformVertex(verts[1], tri->m_vertex[1], triXf);
    hkTriXformVertex(verts[2], tri->m_vertex[2], triXf);

    hkCollideTriangleUtil_s010d_6420::ClosestPointTriangleResult res;
    hkCollideTriangleUtil_s010d_6420::closestPointTriangle(sphXf.m_translation, verts, cache, res);

    float rsum = sphere->m_radius + tri->m_radius;
    if (res.m_distance < rsum + input.m_tolerance)
    {
        hkVector4_s010d_6420 normal = res.m_closestPoint;
        float scale = tri->m_radius - res.m_distance;

        hkVector4_s010d_6420 point = sphXf.m_translation;
        point.x += normal.x * scale;
        point.y += normal.y * scale;
        point.z += normal.z * scale;
        point.w += normal.w * scale;

        collector.addCdPoint(&point);
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d7190
void hkSphereTriangleAgent::getPenetrations(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB, const hkCollisionInput_s010d_6420& input, hkCdBodyPairCollector_s010d_6420& collector)
{
    hkTimerCommand(hkTtrcSphereTri);

    const hkSphereShape*   sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkTriangleShape_s010d_6420* tri    = (const hkTriangleShape_s010d_6420*)bodyB.m_shape;
    const hkTransform_s010d_6420&     triXf  = *(const hkTransform_s010d_6420*)bodyB.m_motion;
    const hkTransform_s010d_6420&     sphXf  = *(const hkTransform_s010d_6420*)bodyA.m_motion;

    hkVector4_s010d_6420 localPoint;
    hkTriLocalPoint(localPoint, sphXf.m_translation, triXf);

    float rsum = sphere->m_radius + tri->m_radius;

    hkCollideTriangleUtil_s010d_6420::ClosestPointTriangleResult res;
    hkCollideTriangleUtil_s010d_6420::closestPointTriangle(localPoint, (const hkVector4_s010d_6420*)((const char*)bodyB.m_shape + 0x10), m_cache, res);

    if (res.m_distance < rsum)
    {
        collector.addCdBodyPair(bodyA, bodyB);
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d7300
void hkSphereTriangleAgent::staticGetPenetrations(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB, const hkCollisionInput_s010d_6420& input, hkCdBodyPairCollector_s010d_6420& collector)
{
    hkTimerCommand(hkTtrcSphereTri);

    const hkSphereShape*   sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkTriangleShape_s010d_6420* tri    = (const hkTriangleShape_s010d_6420*)bodyB.m_shape;
    const hkTransform_s010d_6420&     triXf  = *(const hkTransform_s010d_6420*)bodyB.m_motion;
    const hkTransform_s010d_6420&     sphXf  = *(const hkTransform_s010d_6420*)bodyA.m_motion;

    hkCollideTriangleUtil_s010d_6420::ClosestPointTriangleCache cache;
    hkCollideTriangleUtil_s010d_6420::setupClosestPointTriangleCache(
        (const hkVector4_s010d_6420*)((const char*)bodyB.m_shape + 0x10), cache);

    hkVector4_s010d_6420 localPoint;
    hkTriLocalPoint(localPoint, sphXf.m_translation, triXf);

    float rsum = sphere->m_radius + tri->m_radius;

    hkCollideTriangleUtil_s010d_6420::ClosestPointTriangleResult res;
    hkCollideTriangleUtil_s010d_6420::closestPointTriangle(localPoint, (const hkVector4_s010d_6420*)((const char*)bodyB.m_shape + 0x10), cache, res);

    if (res.m_distance < rsum)
    {
        collector.addCdBodyPair(bodyA, bodyB);
    }

    hkTimerCommand(hkTtrcEnd);
}

// @ 0x010d7470
void hkSymmetricSphereTriangleAgent::getPenetrations(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB, const hkCollisionInput_s010d_6420& input, hkCdBodyPairCollector_s010d_6420& collector)
{
    hkSymPairCollectorLocal sym;
    sym.m_forward = &collector;
    sym.m_earlyOut = 0;
    sym.m_vtable = (void*)0x014a43b4;

    hkSphereTriangleAgent::getPenetrations(bodyB, bodyA, input,
                                           *(hkCdBodyPairCollector_s010d_6420*)&sym);
}

// @ 0x010d74f0
void hkSymmetricSphereTriangleAgent::getClosestPoints(const hkCdBody_s010d_6420& bodyA, const hkCdBody_s010d_6420& bodyB, const hkCollisionInput_s010d_6420& input, hkCdPointCollector_s010d_6420& collector)
{
    hkSymPointCollectorLocal_s010d_6420 sym;
    sym.m_forward = &collector;
    sym.m_earlyOut = 0x7f7fffeeu;
    sym.m_vtable = (void*)0x014a43a4;

    hkSphereTriangleAgent::getClosestPoints(bodyB, bodyA, input,
                                            *(hkCdPointCollector_s010d_6420*)&sym);
}

// @ 0x010dcd40
void hkSymmetricAgentLinearCast_hkHeightFieldAgent::processCollision(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkProcessCollisionInput_s010d_cd40& input, hkProcessCollisionOutput_s010d_cd40& result)
{
    hkProcessCdPoint_s010d_cd40* pp = result.m_firstFreeContactPoint;
    hkTime oldToi = result.m_toiTime;
    hkHeightFieldAgent::processCollision(bodyB, bodyA, input, result);
    for (; pp < result.m_firstFreeContactPoint; pp++) {
        pp->m_contact.setFlipped(pp->m_contact);
    }
    // binary: fucompp + test ah,0x44 / jnp  => taken when (oldToi != toiTime) including NaN
    if (oldToi != result.m_toiTime) {
        // hkToiEvent::flip(): negate the separating normal xyz (distance in w is kept)
        result.m_toiContact.m_separatingNormal.x = -result.m_toiContact.m_separatingNormal.x;
        result.m_toiContact.m_separatingNormal.y = -result.m_toiContact.m_separatingNormal.y;
        result.m_toiContact.m_separatingNormal.z = -result.m_toiContact.m_separatingNormal.z;
    }
}

// @ 0x010dce00
void __stdcall hkSymmetricAgentLinearCast_hkHeightFieldAgent::staticGetClosestPoints(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkCollisionInput_s010d_cd40& input, hkCdPointCollector_s010d_cd40& collector)
{
    hkSymmetricAgentFlipCollector flip(collector);
    hkHeightFieldAgent_staticGetClosestPoints(bodyB, bodyA, input, flip);
}

// @ 0x010dce40
void __stdcall hkSymmetricAgentLinearCast_hkHeightFieldAgent::staticLinearCast(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector_s010d_cd40& collector, hkCdPointCollector_s010d_cd40* startCollector)
{
    hkLinearCastCollisionInput flippedInput = input;
    // setNeg4: each of x,y,z,w negated (fchs)
    flippedInput.m_path.x = -input.m_path.x;
    flippedInput.m_path.y = -input.m_path.y;
    flippedInput.m_path.z = -input.m_path.z;
    flippedInput.m_path.w = -input.m_path.w;

    hkSymmetricAgentFlipCastCollector flip(input.m_path, &collector);
    if (startCollector) {
        hkSymmetricAgentFlipCastCollector startFlip(input.m_path, startCollector);
        hkHeightFieldAgent_staticLinearCast(bodyB, bodyA, flippedInput, flip, &startFlip);
    } else {
        hkHeightFieldAgent_staticLinearCast(bodyB, bodyA, flippedInput, flip, 0);
    }
}

// @ 0x010dcf80
hkCollisionAgent_s010d_cd40* hkHeightFieldAgentCreator::createHeightFieldAAgent(const hkCdBody_s010d_cd40& A, const hkCdBody_s010d_cd40& B, const hkCollisionInput_s010d_cd40& input, hkContactMgr* mgr)
{
    return new hkSymmetricAgentLinearCast_hkHeightFieldAgent(A, B, input, mgr);
}

// @ 0x010dd050
void hkConvexListConvexShape::getFirstVertex(hkVector4_s010d_cd40& v) const
{
    m_subShapesData[0].m_shape->getFirstVertex(v);
}

// @ 0x010dd060
const hkSphere* hkConvexListConvexShape::getCollisionSpheres(hkSphere* sphereBuffer) const
{
    hkSphere* buf = sphereBuffer;
    for (int i = 0; i < m_subShapesSize; i++) {
        const hkConvexShape_s010d_cd40* child = m_subShapesData[i].m_shape;
        hkCollisionSpheresInfo info;
        child->getCollisionSpheres(buf);
        child->getCollisionSpheresInfo(info);
        buf += info.m_numSpheres;
    }
    return sphereBuffer;
}

// @ 0x010dd0c0
void hkConvexListAgent::invalidateTim(hkCollisionInput_s010d_cd40& input)
{
    if (m_inGskMode) {
        hkGskBaseAgent::invalidateTim(input);
        return;
    }
    hkAgent1nMachine_InvalidateTim((char*)this + 0x30, input);
}

// @ 0x010dd0f0
void hkConvexListAgent::warpTime(hkTime oldTime, hkTime newTime, hkCollisionInput_s010d_cd40& input)
{
    if (m_inGskMode) {
        hkGskBaseAgent::warpTime(oldTime, newTime, input);
        return;
    }
    hkAgent1nMachine_WarpTime((char*)this + 0x30, oldTime, newTime, input);
}

// @ 0x010dd120
void hkConvexListAgent::removePoint(hkContactPointId_s010d_cd40 id)
{
    if (m_inGskMode) {
        hkGskfAgent::removePoint(id);
    }
}

// @ 0x010dd140
void hkConvexListAgent::commitPotential(hkContactPointId_s010d_cd40 id)
{
    if (m_inGskMode) {
        hkGskfAgent::commitPotential(id);
    }
}

// @ 0x010dd160
void hkConvexListAgent::createZombie(hkContactPointId_s010d_cd40 id)
{
    if (m_inGskMode) {
        hkGskfAgent::createZombie(id);
    }
}

// @ 0x010dd180
void hkConvexListAgent::cleanup()
{
    if (m_inGskMode) {
        hkGskManifold_cleanup(&m_manifold, m_contactMgr);
        hkReferencedObject_deletingDtor(1);      // virtual deleting destructor, flag 1 (vtable slot 0)
        return;
    }
    hkAgent1nMachine_Destroy((char*)this + 0x30, m_dispatcher, m_contactMgr);
    hkReferencedObject_deletingDtor(1);
}

// @ 0x010dd1d0
hkProcessCollisionOutputBackup::hkProcessCollisionOutputBackup(const hkProcessCollisionOutput_s010d_cd40& out)
{
    m_firstFreeContactPoint = out.m_firstFreeContactPoint;
    m_toiTime = out.m_toiTime;
    const uint32_t* src = (const uint32_t*)&out.m_toiContact;
    for (int i = 0; i < 8; i++) m_toiContact[i] = src[i];
    m_toiProperties = out.m_toiProperties;
    if (out.m_potentialContacts) {
        const uint32_t* s = out.m_potentialContacts;
        uint32_t* d = (uint32_t*)this + 1;
        for (int i = 0; i < 0x402; i++) d[i] = s[i];
    }
}

// @ 0x010dd260
hkProcessCollisionOutputBackup* hkProcessCollisionOutputBackup::restore(hkProcessCollisionOutput_s010d_cd40& out)
{
    out.m_firstFreeContactPoint = m_firstFreeContactPoint;
    out.m_toiTime = m_toiTime;
    uint32_t* dst = (uint32_t*)&out.m_toiContact;
    for (int i = 0; i < 8; i++) dst[i] = m_toiContact[i];
    out.m_toiProperties = m_toiProperties;
    if (out.m_potentialContacts) {
        uint32_t* d = out.m_potentialContacts;
        const uint32_t* s = (const uint32_t*)this + 1;
        for (int i = 0; i < 0x402; i++) d[i] = s[i];
    }
    return this;
}

// @ 0x010dd300
void hkConvexListConvexShape::convertVertexIdsToVertices(const uint16_t* ids, int numIds, hkCdVertex* verticesOut) const
{
    for (int i = 0; i < numIds; i++) {
        uint32_t idx = (uint16_t)(*ids) >> 8;
        uint32_t localId = (uint32_t)(*ids) & 0xff;
        m_subShapesData[idx].m_shape->convertVertexIdsToVertices((const uint16_t*)&localId, 1, verticesOut);
        verticesOut->wBits = ((verticesOut->wBits & 0xc0ffffff) + (idx << 8)) | 0x3f000000;
        ids++;
        verticesOut++;
    }
}

// @ 0x010dd380
void hkConvexListConvexShape::getCollisionSpheresInfo(hkCollisionSpheresInfo& infoOut) const
{
    infoOut.m_numSpheres = 0;
    infoOut.m_useBuffer = 1;
    for (int i = 0; i < m_subShapesSize; i++) {
        hkCollisionSpheresInfo info;
        m_subShapesData[i].m_shape->getCollisionSpheresInfo(info);
        infoOut.m_numSpheres += info.m_numSpheres;
    }
}

// @ 0x010dd580
void hkConvexListConvexShape::getSupportingVertex(const hkVector4_s010d_cd40& dir, hkCdVertex& out) const
{
    float best = -3.40282e+38f;     // 0xff7fffee
    int bestIdx = 0;
    for (int i = 0; i < m_subShapesSize; i++) {
        hkCdVertex v;
        m_subShapesData[i].m_shape->getSupportingVertex(dir, v);
        // X87-PRECISION: ((vx*dx)+(vy*dy))+(vz*dz) stays in an 80-bit register and is compared against the
        // float 'best' without being rounded first; only the winning value is stored (rounded) into best.
        float d = (v.x * dir.x + v.y * dir.y) + v.z * dir.z;
        if (best < d) {
            out = v;
            best = d;
            bestIdx = i;
        }
    }
    out.wBits = ((out.wBits & 0xc0ffffff) + (bestIdx << 8)) | 0x3f000000;
}

// @ 0x010dd640
hkConvexListAgent::hkConvexListAgent(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkCollisionInput_s010d_cd40& input, hkContactMgr* mgr)
: hkPredGskfAgent(bodyA, hkConvexListHullBody(bodyB), mgr)
{
    m_dispatcher = input.m_dispatcher;
    m_inGskMode = 1;
    hkConvexListHullBody hullB(bodyB);
    hkTransform_s010d_cd40 aTb;
    aTb.setMulInverseMul(*bodyA.m_motion, *bodyB.m_motion);
    m_cache.init((const hkConvexShape_s010d_cd40*)bodyA.m_shape, &hullB.m_hull, aTb);
    m_separatingNormal.w = -1.0f;            // 0xbf800000
    m_timeOfSeparatingNormal = -1.0f;
}

// @ 0x010dd750
hkCollisionAgent_s010d_cd40* hkConvexListAgent::createConvexListAgent(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkCollisionInput_s010d_cd40& input, hkContactMgr* mgr)
{
    if (mgr) {
        return new hkConvexListAgent(bodyA, bodyB, input, mgr);
    }
    return new hkGskBaseAgent(bodyA, bodyB, 0);
}

// @ 0x010dd7b0
void hkConvexListAgent::staticGetClosestPoints(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkCollisionInput_s010d_cd40& input, hkCdPointCollector_s010d_cd40& collector)
{
    HK_TIMER_BEGIN_LIST("LtCvxList", "checkHull");
    hkConvexListHullBody hullB(bodyB);
    hkConvexListHullPenetrationCollector penetration;
    hkGskBaseAgent::staticGetPenetrations(bodyA, hullB, input, penetration);
    if (penetration.m_earlyOut) {
        // hull is penetrated: query the children
        HK_TIMER_SPLIT_LIST("Stchildren");
        hkSymmetricAgentFlipCollector flip(collector);
        hkShapeCollectionAgent_staticGetClosestPoints(bodyB, bodyA, input, flip);
    } else {
        hkClosestCdPointCollector_s010d_cd40 hull;
        hkGskBaseAgent::staticGetClosestPoints(bodyA, hullB, input, hull);
        if (hull.m_hitRootA) {
            const hkConvexListShape* list = (const hkConvexListShape*)bodyB.m_shape;
            // binary: fcomp + test ah,0x41 / jne => children path unless (hullDistance > minDistance), NaN goes to children
            if (hull.m_hitContact.m_separatingNormal.w > list->m_minDistanceToUseConvexHullForGsk) {
                hkCdPoint_s010d_cd40 point;
                point.m_contact = hull.m_hitContact;
                point.m_cdBodyA = &bodyA;
                point.m_cdBodyB = &bodyB;
                collector.addCdPoint(point);
            } else {
                HK_TIMER_SPLIT_LIST("Stchildren");
                hkConvexListAgent_staticGetClosestPointsChildren(bodyA, bodyB, input, collector);
            }
        }
    }
    HK_TIMER_END_LIST();
}

// @ 0x010dda70
void hkConvexListAgent::staticGetPenetrations(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkCollisionInput_s010d_cd40& input, hkCdBodyPairCollector_s010d_cd40& collector)
{
    HK_TIMER_BEGIN_LIST("LtCvxList", "checkHull");
    hkConvexListHullBody hullB(bodyB);
    hkConvexListHullPenetrationCollector penetration;
    hkGskBaseAgent::staticGetPenetrations(bodyA, hullB, input, penetration);
    if (penetration.m_earlyOut) {
        HK_TIMER_SPLIT_LIST("Stchildren");
        hkSymmetricAgentFlipBodyCollector flip(collector);
        hkShapeCollectionAgent_staticGetPenetrations(bodyB, bodyA, input, flip);
    }
    HK_TIMER_END_LIST();
}

// @ 0x010ddc30
void hkConvexListAgent::staticLinearCast(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector_s010d_cd40& collector, hkCdPointCollector_s010d_cd40* startCollector)
{
    HK_TIMER_BEGIN_LIST("LtCvsListAgent", "checkHull");
    hkConvexListHullBody hullB(bodyB);
    hkConvexListHullCastCollector hull;
    hkGskBaseAgent::staticLinearCast(bodyA, hullB, input, hull, &hull);
    if (hull.m_hit) {
        HK_TIMER_SPLIT_LIST("Stchild");
        hkConvexListAgent_staticLinearCastChildren(bodyA, bodyB, input, collector, startCollector);
    }
    HK_TIMER_END_LIST();
}

// @ 0x010ddde0
void __stdcall hkConvexListAgent_staticLinearCastForwarder(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector_s010d_cd40& collector, hkCdPointCollector_s010d_cd40* startCollector)
{
    hkConvexListAgent::staticLinearCast(bodyA, bodyB, input, collector, startCollector);
}

// @ 0x010dde90
void __stdcall hkSymmetricAgent_hkConvexListAgent_staticGetClosestPoints(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkCollisionInput_s010d_cd40& input, hkCdPointCollector_s010d_cd40& collector)
{
    hkSymmetricAgentFlipCollector flip(collector);
    hkConvexListAgent::staticGetClosestPoints(bodyB, bodyA, input, flip);
}

// @ 0x010de010
hkCollisionAgent_s010d_cd40* hkConvexListAgent::createListConvexAgent(const hkCdBody_s010d_cd40& bodyA, const hkCdBody_s010d_cd40& bodyB, const hkCollisionInput_s010d_cd40& input, hkContactMgr* mgr)
{
    if (mgr) {
        return new hkSymmetricAgent_hkConvexListAgent(bodyA, bodyB, input, mgr);
    }
    return new hkGskBaseAgent(bodyA, bodyB, 0);
}

// @ 0x010df100
hkReferencedObjectWithArray* hkReferencedObjectWithArray::destroy(unsigned flags)
{
    if (m_capacityAndFlags >= 0) {
        hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        tm->deallocateChunk(m_data, (m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
    }
    *(void**)this = (void*)0x013ef094;
    if (flags & 1) {
        hkMemory_s010d_f100::s_instance->deallocateChunk(this, (int)m_memSizeAndFlags, 0x1c);
    }
    return this;
}

// @ 0x010df160
void hkSymmetricAgent_hkListAgent::linearCast(const hkCdBody_s010d_f100& bodyA, const hkCdBody_s010d_f100& bodyB, const hkLinearCastCollisionInput_s010d_f100& input, hkCdPointCollector_s010d_f100& collector, hkCdPointCollector_s010d_f100* startCollector)
{
    hkLinearCastCollisionInput_s010d_f100 flippedInput = input;
    flippedInput.m_path.x = -input.m_path.x;           // setNeg4
    flippedInput.m_path.y = -input.m_path.y;
    flippedInput.m_path.z = -input.m_path.z;
    flippedInput.m_path.w = -input.m_path.w;
    hkSymmetricAgentFlipCastCollector_s010d_f100 flip(input.m_path, &collector);
    if (startCollector) {
        hkSymmetricAgentFlipCastCollector_s010d_f100 startFlip(input.m_path, startCollector);
        hkListAgent::linearCast(bodyB, bodyA, flippedInput, flip, &startFlip);
    } else {
        hkListAgent::linearCast(bodyB, bodyA, flippedInput, flip, 0);
    }
}

// @ 0x010df280
hkCollisionAgent_s010d_f100* hkSymmetricAgent_hkListAgent::createListBAgent(const hkCdBody_s010d_f100& A, const hkCdBody_s010d_f100& B, const hkCollisionInput_s010d_f100& input, hkContactMgr* mgr)
{
    return new hkSymmetricAgent_hkListAgent(A, B, input, mgr);
}

// @ 0x010df350
void hkPhantomAgent::cleanup()
{
    if (m_shapeTypeA == HK_SHAPE_PHANTOM_CALLBACK) {
        m_phantomShapeA->phantomLeaveEvent(m_rootA, m_rootB);
    }
    if (m_shapeTypeB == HK_SHAPE_PHANTOM_CALLBACK) {
        m_phantomShapeB->phantomLeaveEvent(m_rootB, m_rootA);
    }
    hkReferencedObject_deletingDtor(1);
}

// @ 0x010df390
void hkPhantomAgent::getPenetrations(const hkCdBody_s010d_f100& bodyA, const hkCdBody_s010d_f100& bodyB, const hkCollisionInput_s010d_f100& input, hkCdBodyPairCollector_s010d_f100& collector)
{
    collector.addCdBodyPair(bodyA, bodyB);
}

// @ 0x010df3b0
void __cdecl hkPhantomAgent::staticGetPenetrations(const hkCdBody_s010d_f100& bodyA, const hkCdBody_s010d_f100& bodyB, const hkCollisionInput_s010d_f100& input, hkCdBodyPairCollector_s010d_f100& collector)
{
    collector.addCdBodyPair(bodyA, bodyB);
}

// @ 0x010df3d0
hkPhantomAgent::hkPhantomAgent(const hkCdBody_s010d_f100& A, const hkCdBody_s010d_f100& B, hkContactMgr* mgr)
{
    m_contactMgr = mgr;
    m_referenceCount = 1;
    m_rootA = hkCdBody_getRoot(&A);
    m_rootB = hkCdBody_getRoot(&B);
    m_shapeTypeA = A.m_shape->getType();
    m_shapeTypeB = B.m_shape->getType();
}

// @ 0x010df440
hkCollisionAgent_s010d_f100* __cdecl hkPhantomAgent::createPhantomAgent(const hkCdBody_s010d_f100& A, const hkCdBody_s010d_f100& B, const hkCollisionInput_s010d_f100& input, hkContactMgr* mgr)
{
    hkPhantomAgent* agent = new hkPhantomAgent(A, B, mgr);
    if (agent->m_shapeTypeA == HK_SHAPE_PHANTOM_CALLBACK) {
        hkPhantomCallbackShape* shape = (hkPhantomCallbackShape*)A.m_shape;
        shape->phantomEnterEvent(hkCdBody_getRoot(&A), hkCdBody_getRoot(&B), &input);
        agent->m_phantomShapeA = shape;
    }
    if (agent->m_shapeTypeB == HK_SHAPE_PHANTOM_CALLBACK) {
        hkPhantomCallbackShape* shape = (hkPhantomCallbackShape*)B.m_shape;
        shape->phantomEnterEvent(hkCdBody_getRoot(&B), hkCdBody_getRoot(&A), &input);
        agent->m_phantomShapeB = shape;
    }
    return agent;
}

// @ 0x010df500
void __cdecl hkPhantomAgent::registerAgent(hkCollisionDispatcher_s010d_f100* dispatcher)
{
    hkAgentFuncs_s010d_f100 f;
    f.m_isFlipped = 0;
    f.m_createFunc = &hkPhantomAgent::createPhantomAgent;
    f.m_getPenetrationsFunc = &hkPhantomAgent::staticGetPenetrations;
    f.m_getClosestPointFunc = (hkAgentGetClosestPointsFunc_s010d_f100)&hkAgentDefaultFunc;
    f.m_linearCastFunc = (hkAgentLinearCastFunc_s010d_f100)&hkAgentDefaultFunc;
    f.m_isPredictive = 1;
    dispatcher->registerCollisionAgent(f, HK_SHAPE_PHANTOM_CALLBACK, -1);
    dispatcher->registerCollisionAgent(f, -1, HK_SHAPE_PHANTOM_CALLBACK);
}

// @ 0x010df560
void hkTransformAgent::cleanup()
{
    m_childAgent->cleanup();
    hkReferencedObject_deletingDtor(1);
}

// @ 0x010df5d0
hkMotionState& hkMotionState::operator=(const hkMotionState& other)
{
    uint32_t* d = (uint32_t*)this;
    const uint32_t* s = (const uint32_t*)&other;
    for (int i = 0; i < 0x2b; i++) d[i] = s[i];     // dwords 0 .. 0xaa
    m_h0 = other.m_h0;
    m_h1 = other.m_h1;
    return *this;
}

// @ 0x010df6b0
hkTransformAgent* __cdecl hkTransformAgent::createTransformAAgent(const hkCdBody_s010d_f100& A, const hkCdBody_s010d_f100& B, const hkCollisionInput_s010d_f100& input, hkContactMgr* mgr)
{
    hkTransformAgent* agent = new hkTransformAgent;
    agent->m_contactMgr = mgr;
    agent->m_referenceCount = 1;
    // body A with the child shape and the composed motion (the whole motion state is copied first)
    const hkTransformShape* shape = (const hkTransformShape*)A.m_shape;
    const hkShape_s010d_f100* child = shape->m_childShape;
    hkMotionState tmpMotion;
    tmpMotion = *A.m_motion;
    tmpMotion.m_transform.setMul(A.m_motion->m_transform, shape->m_transform);
    hkCdBody_s010d_f100 childBody;
    childBody.m_shape = child;
    childBody.m_shapeKey = A.m_shapeKey;
    childBody.m_motion = &tmpMotion;
    childBody.m_parent = &A;
    hkCollisionDispatcher_s010d_f100* dispatcher = input.m_dispatcher;
    int typeA = child->getType();
    int typeB = B.m_shape->getType();
    const uint8_t (*table)[32] = input.m_createPredictiveAgents ? dispatcher->m_agent2TypesPredictive : dispatcher->m_agent2Types;
    uint8_t agentType = table[typeA][typeB];
    agent->m_childAgent = dispatcher->m_agent2Func[agentType].m_createFunc(childBody, B, input, mgr);
    return agent;
}

// @ 0x010df7a0
void hkTransformAgent::processCollision(const hkCdBody_s010d_f100& bodyA, const hkCdBody_s010d_f100& bodyB, const hkProcessCollisionInput_s010d_f100& input, hkProcessCollisionOutput_s010d_f100& result)
{
    HK_TIMER_BEGIN("TtTransform");
    const hkTransformShape* shape = (const hkTransformShape*)bodyA.m_shape;
    const hkMotionState* m = bodyA.m_motion;
    hkMotionState tmp;                                   // only the parts below are initialised (as in the binary)
    tmp.m_transform.setMul(m->m_transform, shape->m_transform);
    tmp.m_centerOfMass0 = m->m_centerOfMass0;
    tmp.m_centerOfMass1 = m->m_centerOfMass1;
    tmp.m_rotation0.setMul(m->m_rotation0, shape->m_rotation);
    tmp.m_rotation1.setMul(m->m_rotation1, shape->m_rotation);
    // centerOfMassLocal = R * (com - shapeTranslation), evaluated as ((c*R_i2) + (b*R_i1)) + (a*R_i0)
    // X87-PRECISION: a, b, c (the differences) and the partial sums stay in 80-bit registers; only the three results are stored as floats.
    float a = m->m_centerOfMassLocal.x - shape->m_transform.m_trans.x;
    float b = m->m_centerOfMassLocal.y - shape->m_transform.m_trans.y;
    float c = m->m_centerOfMassLocal.z - shape->m_transform.m_trans.z;
    const hkTransform_s010d_f100& R = shape->m_transform;
    tmp.m_centerOfMassLocal.x = (c * R.m_rot[0].z + b * R.m_rot[0].y) + a * R.m_rot[0].x;
    tmp.m_centerOfMassLocal.y = (c * R.m_rot[1].z + b * R.m_rot[1].y) + a * R.m_rot[1].x;
    tmp.m_centerOfMassLocal.z = (c * R.m_rot[2].z + b * R.m_rot[2].y) + a * R.m_rot[2].x;
    tmp.m_centerOfMassLocal.w = 0.0f;
    tmp.m_misc[0] = m->m_misc[0];
    tmp.m_misc[1] = m->m_misc[1];
    tmp.m_misc[2] = m->m_misc[2];
    tmp.m_misc[3] = m->m_misc[3];
    tmp.m_misc[4] = m->m_misc[4];
    hkCdBody_s010d_f100 childBody;
    childBody.m_shape = shape->m_childShape;
    childBody.m_shapeKey = bodyA.m_shapeKey;
    childBody.m_motion = &tmp;
    childBody.m_parent = &bodyA;
    m_childAgent->processCollision(childBody, bodyB, input, result);
    HK_TIMER_END();
}

// @ 0x010df9e0
void hkTransformAgent::linearCast(const hkCdBody_s010d_f100& bodyA, const hkCdBody_s010d_f100& bodyB, const hkLinearCastCollisionInput_s010d_f100& input, hkCdPointCollector_s010d_f100& collector, hkCdPointCollector_s010d_f100* startCollector)
{
    HK_TIMER_BEGIN("TtTransform");
    hkTransformedChildBody childBody(bodyA);
    m_childAgent->linearCast(childBody, bodyB, input, collector, startCollector);
    HK_TIMER_END();
}

// @ 0x010dfae0
void __cdecl hkTransformAgent::staticLinearCast(const hkCdBody_s010d_f100& bodyA, const hkCdBody_s010d_f100& bodyB, const hkLinearCastCollisionInput_s010d_f100& input, hkCdPointCollector_s010d_f100& collector, hkCdPointCollector_s010d_f100* startCollector)
{
    HK_TIMER_BEGIN("TtTransform");
    hkTransformedChildBody childBody(bodyA);
    hkCollisionDispatcher_s010d_f100* dispatcher = input.m_dispatcher;
    int typeA = childBody.m_shape->getType();
    int typeB = bodyB.m_shape->getType();
    uint8_t agentType = dispatcher->m_agent2Types[typeA][typeB];
    dispatcher->m_agent2Func[agentType].m_linearCastFunc(childBody, bodyB, input, collector, startCollector);
    HK_TIMER_END();
}

// @ 0x010dfc00
void hkTransformAgent::getClosestPoints(const hkCdBody_s010d_f100& bodyA, const hkCdBody_s010d_f100& bodyB, const hkCollisionInput_s010d_f100& input, hkCdPointCollector_s010d_f100& collector)
{
    HK_TIMER_BEGIN("TtTransform");
    hkTransformedChildBody childBody(bodyA);
    m_childAgent->getClosestPoints(childBody, bodyB, input, collector);
    HK_TIMER_END();
}

// @ 0x010dfd00
void __cdecl hkTransformAgent::staticGetClosestPoints(const hkCdBody_s010d_f100& bodyA, const hkCdBody_s010d_f100& bodyB, const hkCollisionInput_s010d_f100& input, hkCdPointCollector_s010d_f100& collector)
{
    HK_TIMER_BEGIN("TtTransform");
    hkTransformedChildBody childBody(bodyA);
    hkCollisionDispatcher_s010d_f100* dispatcher = input.m_dispatcher;
    int typeA = childBody.m_shape->getType();
    int typeB = bodyB.m_shape->getType();
    uint8_t agentType = dispatcher->m_agent2Types[typeA][typeB];
    dispatcher->m_agent2Func[agentType].m_getClosestPointFunc(childBody, bodyB, input, collector);
    HK_TIMER_END();
}

// @ 0x010dfe10
void hkTransformAgent::getPenetrations(const hkCdBody_s010d_f100& bodyA, const hkCdBody_s010d_f100& bodyB, const hkCollisionInput_s010d_f100& input, hkCdBodyPairCollector_s010d_f100& collector)
{
    HK_TIMER_BEGIN("TtTransform");
    hkTransformedChildBody childBody(bodyA);
    HK_TIMER_END();
    m_childAgent->getPenetrations(childBody, bodyB, input, collector);
}

// @ 0x010dff10
void __cdecl hkTransformAgent::staticGetPenetrations(const hkCdBody_s010d_f100& bodyA, const hkCdBody_s010d_f100& bodyB, const hkCollisionInput_s010d_f100& input, hkCdBodyPairCollector_s010d_f100& collector)
{
    HK_TIMER_BEGIN("TtTransform");
    hkTransformedChildBody childBody(bodyA);
    hkCollisionDispatcher_s010d_f100* dispatcher = input.m_dispatcher;
    int typeA = childBody.m_shape->getType();
    int typeB = bodyB.m_shape->getType();
    uint8_t agentType = dispatcher->m_agent2Types[typeA][typeB];
    dispatcher->m_agent2Func[agentType].m_getPenetrationsFunc(childBody, bodyB, input, collector);
    HK_TIMER_END();
}
