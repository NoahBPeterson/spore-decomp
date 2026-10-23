// Slice s010d53d0: Havok 3.1.0 sphere-vs-box collision agent and the symmetric
// sphere/box flip wrapper.
//
//  010d53d0  hkSphereBoxAgent::processCollision
//  010d5850  hkSphereBoxAgent::getClosestPoints
//  010d5ca0  hkSphereBoxAgent::staticGetClosestPoints
//  010d60f0  hkSphereBoxAgent::staticGetPenetrations
//  010d63a0  hkSymmetricAgent<hkSphereBoxAgent>::getClosestPoints wrapper
//
// Flags: /vc71 /O2 /MD /Gy /TP  (Havok 3.1.0 was built by VC .NET 2003).
#include "types.h"
#include <intrin.h>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkTtrcSphereBox[];                // 0x014a4720 ("TtSphereBox")
extern const char hkTtrcEnd[];                      // 0x0149cc34

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, fabs)

// ---------------------------------------------------------------------------
// Monitor-stream scope guard (shared with the other Havok collision slices).
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// shared types
// ---------------------------------------------------------------------------
class hkTransform;

struct __declspec(align(16)) hkVector4
{
    float x, y, z, w;
    void setTransformedInversePos(const hkTransform& xf, const hkVector4& p);  // 0x010813d0
};

class hkTransform
{ public:
    hkVector4 m_basis[3];           // +0, +0x10, +0x20
    hkVector4 m_translation;        // +0x30
};

class hkCdBody
{ public:
    const void*     m_shape;        // +0
    unsigned        m_shapeKey;     // +4
    const void*     m_motion;       // +8
    const hkCdBody* m_parent;       // +0xc
};

struct hkCollisionInput
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
};

struct hkProcessCollisionInput
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
};

// sphere shape: radius at +0xc, centre is the motion translation.
class hkSphereShape
{ public:
    char  m_pad[0xc];
    float m_radius;                 // +0xc
};

// box shape: radius at +0xc, half extents (x,y,z,w) at +0x10.
class hkBoxShape
{ public:
    char      m_pad[0xc];
    float     m_radius;             // +0xc
    hkVector4 m_halfExtents;        // +0x10
};

// hkContactPoint (0x30 bytes, separating normal at +0x10, id at +0x20).
class hkContactPoint
{ public:
    hkVector4 m_position;           // +0
    hkVector4 m_separatingNormal;   // +0x10
    char      m_pad[0x10];          // +0x20 (contact id lives here)
};

struct hkProcessCdPoint { hkContactPoint m_contact; };   // 0x30

struct hkProcessCollisionOutput
{
    hkProcessCdPoint* m_firstFreeContactPoint;  // +0
};

// ---------------------------------------------------------------------------
// collectors
// ---------------------------------------------------------------------------
class hkCdPointCollector
{
public:
    virtual ~hkCdPointCollector() {}
    virtual void addCdPoint(const void* point) = 0;   // slot 1
    float m_earlyOutDistance;                         // +4
};

class hkCdBodyPairCollector
{
public:
    virtual ~hkCdBodyPairCollector() {}
    virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b) = 0;  // slot 1
    char m_earlyOut;                                  // +4
    const void* m_extra;                              // +8
};

// hkContactMgr: the agent caches the contact point index for its pair.
class hkContactMgr
{
public:
    virtual void v0();                                          // +0
    virtual void v1();                                          // +4
    virtual unsigned short createContactPoint(const hkCdBody&, const hkCdBody&,
                                              const hkProcessCollisionInput&,
                                              hkContactPoint*);  // +8
    virtual void v3();                                          // +0xc
    virtual void removeContactPoint(unsigned short index);      // +0x10
};

// ---------------------------------------------------------------------------
// float helpers (the originals use SSE-style sign flipping / clamping on x87)
// ---------------------------------------------------------------------------
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

// |value| clamped to limit, then re-signed from `value` (clamp toward the box).
static __forceinline float hkClampAbs(float value, float limit)
{
    return hkFlipSign(hkMinF((float)fabs(value), limit), value);
}

// ---------------------------------------------------------------------------
// agents
// ---------------------------------------------------------------------------
class hkCollisionAgent
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
};

class hkSphereBoxAgent : public hkCollisionAgent
{
public:
    unsigned short m_pad0;              // +4
    unsigned short m_pad1;              // +6
    hkContactMgr*  m_contactMgr;        // +8
    unsigned short m_contactPointId;    // +0xc (0xffff when none cached)
    char           m_pad2[2];

    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkProcessCollisionInput& input,
                                  hkProcessCollisionOutput& output);          // 0x010d53d0
    virtual void getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkCollisionInput& input,
                                  hkCdPointCollector& collector);             // 0x010d5850
    static void staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                       const hkCollisionInput& input,
                                       hkCdPointCollector& collector);        // 0x010d5ca0
    static void staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                      const hkCollisionInput& input,
                                      hkCdBodyPairCollector& collector);      // 0x010d60f0
};

// ===========================================================================
// @ 0x010d53d0
// hkSphereBoxAgent::processCollision: put the sphere centre into box space,
// find whether it is inside the box, compute the separating normal and the
// separation, then create/refresh the cached contact point.
// ===========================================================================
void hkSphereBoxAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                        const hkProcessCollisionInput& input,
                                        hkProcessCollisionOutput& output)
{
    hkTimerCommand(hkTtrcSphereBox);

    const hkSphereShape* sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkBoxShape*    box    = (const hkBoxShape*)bodyB.m_shape;
    const hkTransform&   boxXf  = *(const hkTransform*)bodyB.m_motion;
    const hkVector4&     sphPos = *(const hkVector4*)((const char*)bodyA.m_motion + 0x30);

    float* cp = (float*)output.m_firstFreeContactPoint;

    hkVector4 p;
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
            bodyA, bodyB, (const hkProcessCollisionInput&)input, (hkContactPoint*)cp);
    }
    if (m_contactPointId != 0xffff)
    {
        *(unsigned short*)(cp + 8) = m_contactPointId;
        output.m_firstFreeContactPoint = output.m_firstFreeContactPoint + 1;
    }

    hkTimerCommand(hkTtrcEnd);
}

// ===========================================================================
// @ 0x010d5850
// hkSphereBoxAgent::getClosestPoints: same sphere/box separation test, but the
// resulting point is handed to a collector instead of a cached contact point.
// ===========================================================================
void hkSphereBoxAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                        const hkCollisionInput& input,
                                        hkCdPointCollector& collector)
{
    hkTimerCommand(hkTtrcSphereBox);

    const hkSphereShape* sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkBoxShape*    box    = (const hkBoxShape*)bodyB.m_shape;
    const hkTransform&   boxXf  = *(const hkTransform*)bodyB.m_motion;
    const hkVector4&     sphPos = *(const hkVector4*)((const char*)bodyA.m_motion + 0x30);

    hkVector4 p;
    p.setTransformedInversePos(boxXf, sphPos);

    const float ax = (float)fabs(p.x);
    const float ay = (float)fabs(p.y);
    const float az = (float)fabs(p.z);

    const float dX = hkMinF(ax, box->m_halfExtents.x) - ax;
    const float dY = hkMinF(ay, box->m_halfExtents.y) - ay;
    const float dZ = hkMinF(az, box->m_halfExtents.z) - az;

    hkVector4 normal;
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

    hkVector4 point;
    point.x = sphPos.x + scale * normal.x;
    point.y = sphPos.y + scale * normal.y;
    point.z = sphPos.z + scale * normal.z;
    point.w = sphPos.w + scale * normal.w;
    point.w = sep;

    collector.addCdPoint(&point);

    hkTimerCommand(hkTtrcEnd);
}

// ===========================================================================
// @ 0x010d5ca0
// hkSphereBoxAgent::staticGetClosestPoints: identical query, no cached state.
// ===========================================================================
void hkSphereBoxAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                              const hkCollisionInput& input,
                                              hkCdPointCollector& collector)
{
    hkTimerCommand(hkTtrcSphereBox);

    const hkSphereShape* sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkBoxShape*    box    = (const hkBoxShape*)bodyB.m_shape;
    const hkTransform&   boxXf  = *(const hkTransform*)bodyB.m_motion;
    const hkVector4&     sphPos = *(const hkVector4*)((const char*)bodyA.m_motion + 0x30);

    hkVector4 p;
    p.setTransformedInversePos(boxXf, sphPos);

    const float ax = (float)fabs(p.x);
    const float ay = (float)fabs(p.y);
    const float az = (float)fabs(p.z);

    const float dX = hkMinF(ax, box->m_halfExtents.x) - ax;
    const float dY = hkMinF(ay, box->m_halfExtents.y) - ay;
    const float dZ = hkMinF(az, box->m_halfExtents.z) - az;

    hkVector4 normal;
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

    hkVector4 point;
    point.x = sphPos.x + scale * normal.x;
    point.y = sphPos.y + scale * normal.y;
    point.z = sphPos.z + scale * normal.z;
    point.w = sphPos.w + scale * normal.w;
    point.w = sep;

    collector.addCdPoint(&point);

    hkTimerCommand(hkTtrcEnd);
}

// ===========================================================================
// @ 0x010d60f0
// hkSphereBoxAgent::staticGetPenetrations: clamp the sphere centre onto the box
// (in box space), transform it back to world space and report the body pair
// when the boxes' bounding spheres overlap.
// ===========================================================================
void hkSphereBoxAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                             const hkCollisionInput& input,
                                             hkCdBodyPairCollector& collector)
{
    hkTimerCommand(hkTtrcSphereBox);

    const hkSphereShape* sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkBoxShape*    box    = (const hkBoxShape*)bodyB.m_shape;
    const hkTransform&   boxXf  = *(const hkTransform*)bodyB.m_motion;
    const hkVector4&     sphPos = *(const hkVector4*)((const char*)bodyA.m_motion + 0x30);

    hkVector4 p;
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

// ===========================================================================
// hkSymmetricAgent<hkSphereBoxAgent>::getClosestPoints: run the box agent with
// the bodies swapped through a stack collector that forwards to the real one.
// ===========================================================================
struct hkSymPointCollectorLocal
{
    void*               m_vtable;       // +0
    unsigned            m_earlyOut;     // +4 (bit pattern 0x7f7fffee)
    hkCdPointCollector* m_forward;      // +8
};

class hkSymmetricSphereBoxAgent : public hkSphereBoxAgent
{
public:
    virtual void getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkCollisionInput& input,
                                  hkCdPointCollector& collector);   // 0x010d63a0
};

// @ 0x010d63a0
void hkSymmetricSphereBoxAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                 const hkCollisionInput& input,
                                                 hkCdPointCollector& collector)
{
    hkSymPointCollectorLocal sym;
    sym.m_forward = &collector;
    sym.m_earlyOut = 0x7f7fffeeu;
    sym.m_vtable = (void*)0x014a43a4;

    hkSphereBoxAgent::getClosestPoints(bodyB, bodyA, input,
                                       *(hkCdPointCollector*)&sym);
}
