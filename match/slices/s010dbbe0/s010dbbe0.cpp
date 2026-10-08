// Havok 3.1.0 (statically linked): hkHeightFieldAgent::processCollision @ 0x010DC300.
// Sphere-set shape (A) against a height field (B): transform A's collision spheres into B's space, ask the
// height field to collide them, then turn every sphere with distance <= tolerance into a contact point
// (adding it to the contact manager on first contact, removing it again once the sphere has separated).
// Compile flags: /vc71 /O2 /MD /Gy /EHsc /TP (Havok was built with VC .NET 2003).
#include "types.h"
#include <stddef.h>

typedef float hkReal;
typedef uint16_t hkContactPointId;

__declspec(align(16)) struct hkVector4 {
    float x, y, z, w;
};
typedef hkVector4 hkSphere;     // xyz = centre, w = radius

struct hkTransform {
    hkVector4 m_col0, m_col1, m_col2, m_trans;
    void setMulInverseMul(const hkTransform& a, const hkTransform& b);   // 0x010810F0: this = inverse(a) * b
};

struct hkContactPoint {
    hkVector4 m_position;
    hkVector4 m_separatingNormal;   // w = distance
};

class hkShape;
class hkCdBody {
public:
    const hkShape* m_shape;          // +0
    uint32_t m_shapeKey;             // +4
    const hkTransform* m_motion;     // +8
    const hkCdBody* m_parent;        // +0xc
};

struct hkProcessCollisionInput {
    void* m_dispatcher;      // +0
    uint32_t m_pad[1];       // +4
    hkReal m_tolerance;      // +8
};

// One entry of the output's contact point list: the contact point plus the manager's id for it.
struct hkProcessCollisionOutputContactPoint {
    hkContactPoint m_contact;           // +0x00
    hkContactPointId m_contactPointId;  // +0x20
    uint16_t m_pad[7];
};
struct hkProcessCollisionOutput {
    hkProcessCollisionOutputContactPoint* m_firstFreeContactPoint;   // +0
};

struct hkCollisionSpheresInfo { int m_numSpheres; uint8_t m_useBuffer; };

class hkShape {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6();
    virtual void getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const;         // slot 7
    virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;        // slot 8
};
class hkHeightFieldShape {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6();
    struct CollideSpheresInput { const hkSphere* m_spheres; int m_numSpheres; hkReal m_tolerance; };
    virtual void collideSpheres(const CollideSpheresInput& input, hkVector4* outputArray) const;   // slot 7
};

class hkContactMgr {
public:
    virtual void s0();
    virtual void s1();
    virtual hkContactPointId addContactPoint(const hkCdBody& a, const hkCdBody& b,
                                             const hkProcessCollisionInput& input, hkContactPoint& cp);   // slot 2
    virtual void s3();
    virtual void removeContactPoint(hkContactPointId id);                                                  // slot 4
};

// ---- monitor stream timers (HK_TIMER_BEGIN_LIST / SPLIT / END), inlined TLS appends -------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern unsigned long g_hkThreadMemoryTls;           // 0x016e4174
extern const char hkMonitorEndTag[];                // 0x00143cd94

struct hkMonitorCommand { const char* m_name; uint32_t m_time; uint32_t m_pad; };
struct hkMonitorCommand2 { hkMonitorCommand m_first; const char* m_secondCommand; };

#define HK_TIMER_BEGIN_LIST(a, b) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand2* c_ = (hkMonitorCommand2*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_first.m_name = a; c_->m_secondCommand = b; \
        uint32_t t_; __asm { rdtsc } __asm { mov t_, eax } \
        c_->m_first.m_time = t_; \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_SPLIT_LIST(name) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_name = name; \
        uint32_t t_; __asm { rdtsc } __asm { mov t_, eax } \
        c_->m_time = t_; \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_END_LIST() HK_TIMER_SPLIT_LIST(hkMonitorEndTag)

// ---- hkThreadMemory stack allocator (hkAllocateStack / hkDeallocateStack) ---------------------------------
class hkThreadMemoryRaw {
public:
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void* allocateStackSlow(int size);          // slot 3
    virtual void deallocateStackSlow(void* p);          // slot 4
    char pad[0x1c];
    char* m_stackCurrent;     // +0x20
    char* m_stackPrev;        // +0x24
    char* m_stackBase;        // +0x28
    char* m_stackEnd;         // +0x2c
};
static inline hkThreadMemoryRaw* hkThreadMemoryGet() { return (hkThreadMemoryRaw*)TlsGetValue(g_hkThreadMemoryTls); }

// hkAllocateStack<hkSphere>(n + 1)
static inline hkSphere* hkAllocateStackSpheres(int n)
{
    hkThreadMemoryRaw* tm = hkThreadMemoryGet();
    int size = (n << 4) & ~0xf;
    char* cur = tm->m_stackCurrent;
    char* next = cur + size;
    if ((uint32_t)next > (uint32_t)tm->m_stackEnd)
        return (hkSphere*)tm->allocateStackSlow(size);
    tm->m_stackCurrent = next;
    return (hkSphere*)cur;
}
static inline void hkDeallocateStackSpheres(void* p)
{
    hkThreadMemoryRaw* tm = hkThreadMemoryGet();
    tm->m_stackCurrent = (char*)p;
    if (p == tm->m_stackBase)
        tm->deallocateStackSlow(p);
}

// out[i] = R * in[i] + t, w copied (unrolled by 4 as in the binary)
#define HK_XFORM_ONE(D, S) { \
        const hkVector4 v_ = (S); const float x = v_.x, y = v_.y, z = v_.z; \
        (D).x = ((m20 * z + m10 * y) + m00 * x) + tx; \
        (D).y = ((m21 * z + m11 * y) + m01 * x) + ty; \
        (D).z = ((m22 * z + m12 * y) + m02 * x) + tz; \
        (D).w = v_.w; }
static __forceinline void transformSpheres(const hkTransform& tr, const hkSphere* in, hkSphere* out, int n)
{
    const hkTransform& t = tr;
    const float m00 = t.m_col0.x, m01 = t.m_col0.y, m02 = t.m_col0.z;
    const float m10 = t.m_col1.x, m11 = t.m_col1.y, m12 = t.m_col1.z;
    const float m20 = t.m_col2.x, m21 = t.m_col2.y, m22 = t.m_col2.z;
    const float tx = t.m_trans.x, ty = t.m_trans.y, tz = t.m_trans.z;
    int i = 0;
    if (n >= 4)
    {
        int blocks = ((n - 4) >> 2) + 1;
        i = blocks * 4;
        const hkSphere* s = in;
        hkSphere* d = out;
        do {
            HK_XFORM_ONE(d[0], s[0]) HK_XFORM_ONE(d[1], s[1]) HK_XFORM_ONE(d[2], s[2]) HK_XFORM_ONE(d[3], s[3])
            s += 4; d += 4;
        } while (--blocks);
    }
    for (; i < n; ++i)
        HK_XFORM_ONE(out[i], in[i])
}

class hkHeightFieldAgent
{
public:
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);

    uint32_t m_pad4;                      // +4  (hkReferencedObject)
    hkContactMgr* m_contactMgr;           // +8
    hkContactPointId* m_contactPointId;   // +0xc  (hkArray data)
    int m_numContactPointIds;             // +0x10 (hkArray size) == number of spheres
};

// @ 0x010DC300
void hkHeightFieldAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                          const hkProcessCollisionInput& input, hkProcessCollisionOutput& result)
{
    HK_TIMER_BEGIN_LIST("HeightField", "bTA");

    const hkShape* shapeA = bodyA.m_shape;
    const hkHeightFieldShape* shapeB = (const hkHeightFieldShape*)bodyB.m_shape;
    hkTransform aTb;
    aTb.setMulInverseMul(*bodyB.m_motion, *bodyA.m_motion);

    const int numSpheres = m_numContactPointIds;
    hkSphere* sphereBuffer = hkAllocateStackSpheres(numSpheres + 1);
    hkContactPointId* ids = m_contactPointId;

    HK_TIMER_SPLIT_LIST("StgetSpheres");
    const hkSphere* spheres = shapeA->getCollisionSpheres(sphereBuffer);

    transformSpheres(aTb, spheres, sphereBuffer, numSpheres);

    hkVector4* results = (hkVector4*)hkAllocateStackSpheres(numSpheres + 1);
    HK_TIMER_SPLIT_LIST("Stcollide");
    hkHeightFieldShape::CollideSpheresInput csi;
    csi.m_spheres = sphereBuffer;
    csi.m_numSpheres = numSpheres;
    csi.m_tolerance = input.m_tolerance;
    shapeB->collideSpheres(csi, results);

    HK_TIMER_SPLIT_LIST("Stexamine");
    const hkReal tolerance = input.m_tolerance;
    for (int i = numSpheres - 1; i >= 0; --i, ++ids)
    {
        const hkSphere& sphere = sphereBuffer[numSpheres - 1 - i];
        const hkVector4& res = results[numSpheres - 1 - i];
        if (res.w > tolerance)
        {
            if (*ids != 0xffff)
            {
                m_contactMgr->removeContactPoint(*ids);
                *ids = 0xffff;
            }
        }
        else
        {
            const float s = -sphere.w;
            const float px = sphere.x + s * res.x;
            const float py = sphere.y + s * res.y;
            const float pz = sphere.z + s * res.z;
            const hkTransform* motionB = bodyB.m_motion;
            hkProcessCollisionOutputContactPoint* out = result.m_firstFreeContactPoint;
            hkContactPoint& cp = out->m_contact;
            cp.m_position.x = ((pz * motionB->m_col2.x + py * motionB->m_col1.x) + px * motionB->m_col0.x) + motionB->m_trans.x;
            cp.m_position.y = ((pz * motionB->m_col2.y + py * motionB->m_col1.y) + px * motionB->m_col0.y) + motionB->m_trans.y;
            cp.m_position.z = ((pz * motionB->m_col2.z + py * motionB->m_col1.z) + px * motionB->m_col0.z) + motionB->m_trans.z;
            cp.m_position.w = 0.0f;
            cp.m_separatingNormal.x = (res.z * motionB->m_col2.x + res.y * motionB->m_col1.x) + res.x * motionB->m_col0.x;
            cp.m_separatingNormal.y = (res.z * motionB->m_col2.y + res.y * motionB->m_col1.y) + res.x * motionB->m_col0.y;
            cp.m_separatingNormal.z = (res.z * motionB->m_col2.z + res.y * motionB->m_col1.z) + res.x * motionB->m_col0.z;
            cp.m_separatingNormal.w = 0.0f;
            cp.m_separatingNormal.w = res.w;
            if (*ids == 0xffff)
            {
                hkContactPointId id = m_contactMgr->addContactPoint(bodyA, bodyB, input, cp);
                *ids = id;
                if (id != 0xffff)
                    result.m_firstFreeContactPoint += 1;
            }
            else
            {
                result.m_firstFreeContactPoint += 1;
            }
            out->m_contactPointId = *ids;
        }
    }

    hkDeallocateStackSpheres(results);
    hkDeallocateStackSpheres(sphereBuffer);
    HK_TIMER_END_LIST();
}
