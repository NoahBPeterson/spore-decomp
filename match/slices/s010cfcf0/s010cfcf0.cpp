// Slice s010cfcf0 -- Havok 3.1.0 hkMultiSphereTriangleAgent::processCollision (0x010d0130).
// Opens a "TtMultiSphereTri" monitor timer, transforms the triangle's 3 vertices and the multi-sphere's
// spheres into world space, then for every sphere computes the closest point on the triangle.  If the distance
// is below (sphere radius + triangle radius + tolerance) it appends a contact point (position, separating normal
// with w = distance - radiusSum) to the output, asking the contact manager for a point id when the sphere has
// none yet; otherwise it releases the sphere's previously allocated contact point id.
// Note the agent's id slot for sphere i is m_contactPointId[numSpheres - 1 - i] in the binary.
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <intrin.h>
#pragma intrinsic(__rdtsc)

#define VTFN(obj, slot) (*(void***)(obj))[slot]

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

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };
struct hkVector3 { float x, y, z; };
class hkTransform { public: hkVector4 m_col0, m_col1, m_col2, m_translation; };   // 0x40 bytes

// ---- shapes ----
class hkShape { public: virtual ~hkShape(); int m_pad[2]; };                                         // 0xc bytes
class hkConvexShape : public hkShape { public: float m_radius; };                                              // radius +0xc
class hkTriangleShape : public hkConvexShape { public: hkVector4 m_vertices[3]; };                              // vertices +0x10
struct hkMultiSphereShape : hkShape { int m_numSpheres; hkVector4 m_spheres[8]; };               // count +0xc, spheres +0x10

class hkCdBody
{
public:
    const hkShape* m_shape;        // +0
    unsigned       m_shapeKey;     // +4
    const hkTransform* m_motion;   // +8
    const hkCdBody* m_parent;      // +0xc
};
struct hkCollisionInput { int pad[2]; float m_tolerance; };   // tolerance +8
class hkContactPoint { public: hkVector4 m_position; hkVector4 m_separatingNormal;
    void FUN_010d0040(const hkVector4& normal, float w);   // w = distance
    void setFlipped(const hkContactPoint& other); };       // 0x010cecf0
struct hkCdPoint { hkContactPoint m_contact; const hkCdBody* m_cdBodyA; const hkCdBody* m_cdBodyB; };   // 0x28 bytes
class hkCdPointCollector
{
public:
    virtual ~hkCdPointCollector() {}
    virtual void addCdPoint(const hkCdPoint& point) = 0;                     // slot 1
    float m_earlyOutDistance;
};

struct hkCollideTriangleUtil
{
    struct ClosestPointTriangleCache { float m_QQ, m_RR, m_QR, m_invTriNormal; };
    struct ClosestPointTriangleResult { hkVector4 hitDirection; float distance; };
    enum ClosestPointTriangleStatus { HIT_TRIANGLE_FACE = 0, HIT_TRIANGLE_EDGE };
    static void __cdecl setupClosestPointTriangleCache(const hkVector4* triangle, ClosestPointTriangleCache& cache);   // 0x01105d80
    static ClosestPointTriangleStatus __cdecl closestPointTriangle(const hkVector4& position, const hkVector4* tri,
        const ClosestPointTriangleCache& cache, ClosestPointTriangleResult& result);                                     // 0x01106010
};

// hkVector4Util::transformPoints: out[i] = R * in[i] + t, w cleared. The transform is copied to scalars first
// (x87 build, unrolled by 4 as in the binary).
#define HK_XFORM_ONE(O, I) { \
        const float x = (I).x, y = (I).y, z = (I).z; \
        (O).x = (m00 * x + (m10 * y + m20 * z)) + tx; \
        (O).y = (m01 * x + (m11 * y + m21 * z)) + ty; \
        (O).z = (m02 * x + (m12 * y + m22 * z)) + tz; \
        (O).w = 0.0f; }
static __forceinline void transformPoints(const hkTransform& t, const hkVector4* in, int n, hkVector4* out)
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
        const hkVector4* p = in;
        hkVector4* q = out;
        do {
            HK_XFORM_ONE(q[0], p[0]) HK_XFORM_ONE(q[1], p[1]) HK_XFORM_ONE(q[2], p[2]) HK_XFORM_ONE(q[3], p[3])
            p += 4; q += 4;
        } while (--blocks);
    }
    for (; i < n; ++i)
        HK_XFORM_ONE(out[i], in[i])
}

typedef unsigned short hkContactPointId;
struct hkProcessCollisionInput : hkCollisionInput { };
struct hkProcessCdPoint { hkContactPoint m_contact; hkContactPointId m_id; char m_pad[14]; };   // 0x30 bytes
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
    virtual hkContactPointId addContactPoint(const hkCdBody& a, const hkCdBody& b, const hkProcessCollisionInput& input,
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
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input,
                                  hkProcessCollisionOutput& result);                   // 0x010d0130
    int                m_pad4;                                                         // +4 refcount
    hkContactMgr*      m_contactMgr;                                                   // +8
    hkCollideTriangleUtil::ClosestPointTriangleCache m_closestPointTriangleCache;     // +0xc
    hkContactPointId   m_contactPointId[8];                                            // +0x1c
};

// @ 0x010d0130
void hkMultiSphereTriangleAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                  const hkProcessCollisionInput& input,
                                                  hkProcessCollisionOutput& result)
{
    hkTimerCommand(hkTtMultiSphereTri);

    const hkMultiSphereShape* sphereShapeA = (const hkMultiSphereShape*)bodyA.m_shape;
    const hkTriangleShape* triangleShapeB = (const hkTriangleShape*)bodyB.m_shape;

    hkVector4 vertices[3];
    transformPoints(*bodyB.m_motion, triangleShapeB->m_vertices, 3, vertices);

    const int numSpheres = sphereShapeA->m_numSpheres;
    hkVector4 spheres[8];
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

// ---------------------------------------------------------------------------
// Havok agent factories, contact-point helpers and wrapper trampolines.
// ---------------------------------------------------------------------------

extern void* g_hkMemoryInstance;                 // 0x016e4178
extern unsigned long g_hkThreadMemoryTls;        // 0x016e4174
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
class hkThreadMemory
{
public:
    void deallocateChunk(void* data, int size, int alignment);       // 0x0107db10
};
class hkAgentBase
{
public:
    virtual void destroy(int flags);                         // vtable slot 0
};
struct hkMultiRayConvexAgentBase
{
    void getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                          const hkCollisionInput& input, void* collector);   // 0x010cf0d0
};
class hkMultiRayConvexAgent
{
public:
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkProcessCollisionInput& input,
                                  hkProcessCollisionOutput& output);        // 0x010cf8d0
};
struct hkAgentWrapper
{
    void  FUN_010cfcf0(void* a1, void* a2, void* a3, void* a4);
    void  FUN_010cfd30(void* a1, void* a2, void* a3, void* a4);
    void* FUN_010cfdb0(unsigned char flags);
    void  FUN_010cfe10(void* a1, void* a2, void* a3, void* a4, void* a5);
};
void __fastcall FUN_010cf8d0(void* self, const hkCdBody& bodyA, const hkCdBody& bodyB,
                            const hkProcessCollisionInput& input, hkProcessCollisionOutput& output);
void __fastcall FUN_010cf850(void* self, const hkCdBody& bodyA, const hkCdBody& bodyB,
                            const hkCollisionInput& input, hkContactMgr* mgr);
void __cdecl FUN_01105d80(const hkVector4* triangle, void* cache);
void __cdecl FUN_010cecf0(hkContactPoint* point, const hkContactPoint* src);
void __fastcall FUN_0107db10(void* threadMemory, void* data, int size);

struct hkPointCollector
{
    void* m_vtable;              // +0x00
    int   m_field4;              // +0x04
    void* m_field8;              // +0x08
};

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

struct hkRefObject
{
    void*    m_vtable;               // +0x00
    uint16_t m_size;                 // +0x04
    uint16_t m_pad6;                 // +0x06
    int      m_pad8;                 // +0x08
    void*    m_data0c;               // +0x0c
    int      m_pad10;                // +0x10
    int      m_flags14;              // +0x14
};

// @ 0x010cfcf0
void hkAgentWrapper::FUN_010cfcf0(void* a1, void* a2, void* a3, void* a4)
{
    hkPointCollector collector;
    collector.m_field8 = a4;
    collector.m_field4 = 0x7f7fffee;
    collector.m_vtable = (void*)0x014a43a4;
    ((hkMultiRayConvexAgentBase*)this)->getClosestPoints(*(const hkCdBody*)a2,
                                                         *(const hkCdBody*)a1,
                                                         *(const hkCollisionInput*)a3,
                                                         &collector);
}

// @ 0x010cfd30
void hkAgentWrapper::FUN_010cfd30(void* a1, void* a2, void* a3, void* a4)
{
    hkProcessCollisionOutput& output = *(hkProcessCollisionOutput*)a4;
    const float oldDistance = output.m_cachedDistance;
    hkProcessCdPoint* point = output.m_firstFreeContactPoint;

    ((hkMultiRayConvexAgent*)this)->hkMultiRayConvexAgent::processCollision(
        *(const hkCdBody*)a2, *(const hkCdBody*)a1,
        *(const hkProcessCollisionInput*)a3, output);

    while (point < output.m_firstFreeContactPoint) {
        hkContactPoint* contact = &point->m_contact;
        contact->setFlipped(*contact);
        point = (hkProcessCdPoint*)((char*)point + 0x30);
    }

    if (oldDistance != output.m_cachedDistance) {
        output.m_separatingNormal[0] = -output.m_separatingNormal[0];
        output.m_separatingNormal[1] = -output.m_separatingNormal[1];
        output.m_separatingNormal[2] = -output.m_separatingNormal[2];
    }
}

// @ 0x010cfdb0
void* hkAgentWrapper::FUN_010cfdb0(unsigned char flags)
{
    hkRefObject* object = (hkRefObject*)this;

    if ((object->m_flags14 & 0x80000000) != 0)
        goto after_deallocate;

    {
        hkThreadMemory* threadMemory = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        threadMemory->deallocateChunk(object->m_data0c,
                                     (object->m_flags14 & 0x3fffffff) << 1, 0x14);
    }

after_deallocate:
    object->m_vtable = (void*)0x013ef094;
    if ((flags & 1) != 0)
        ((hkMemory*)g_hkMemoryInstance)->deallocate(object, object->m_size, 0x1c);

    return this;
}

// @ 0x010cfe10
void hkAgentWrapper::FUN_010cfe10(void* a1, void* a2, void* a3, void* a4, void* a5)
{
    // Five-argument iterative-linear-cast wrapper.  The start/end point
    // collectors and the negated cd-point copy are not reconstructed yet.
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5;
}

// @ 0x010cff30
void* __cdecl FUN_010cff30(const hkCdBody& bodyA, const hkCdBody& bodyB,
                           const hkCollisionInput& input, hkContactMgr* mgr)
{
    void* mem = ((hkMemory*)g_hkMemoryInstance)->allocate(0x20, 0x1c);
    hkAgent44* node = (hkAgent44*)mem;
    node->m_size = 0x20;
    const hkCdBody& second = bodyB;
    const hkCdBody& first = bodyA;
    FUN_010cf850(node, second, first, input, mgr);
    node->m_vtable = (void*)0x014a44bc;
    return node;
}

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
void hkContactPoint::FUN_010d0040(const hkVector4& normal, float w)
{
    m_separatingNormal.x = normal.x;
    m_separatingNormal.y = normal.y;
    m_separatingNormal.z = normal.z;
    volatile float* normalW = &m_separatingNormal.w;
    *normalW = normal.w;
    m_separatingNormal.w = w;
}

// @ 0x010d0070
void* __cdecl FUN_010d0070(const hkCdBody& bodyA, const hkCdBody& bodyB,
                           const hkCollisionInput& input, hkContactMgr* mgr)
{
    void* mem = ((hkMemory*)g_hkMemoryInstance)->allocate(0x2c, 0x1c);
    hkAgent44* node = (hkAgent44*)mem;
    const hkCdBody* body = &bodyB;
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
    FUN_01105d80((const hkVector4*)((const char*)body->m_shape + 0x10), (void*)node->m_cache);
    return node;
}

// @ 0x010d00d0
void* __cdecl FUN_010d00d0(const hkCdBody& bodyA, const hkCdBody& bodyB,
                           const hkCollisionInput& input, hkContactMgr* mgr)
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
    FUN_01105d80((const hkVector4*)((const char*)bodyA.m_shape + 0x10), node->m_cache);
    node->m_vtable = (void*)0x014a453c;
    return node;
}
