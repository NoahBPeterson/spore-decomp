// Slice s010c7100 -- Havok 3.1: hkMultiSphereShape (getAabb / castRay / castRayWithCollector),
// hkMultiRayShape (calcStatistics / getAabb) and the two hkMoppBvTreeShape query forwarders.
// Module flags: /vc71 /O2 /MD /Gy /TP   (Havok 3.1.0 was built with VC .NET 2003 cl 13.10)
#include "types.h"
#include <math.h>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// VC7.1 (cl 13.10) ships no __rdtsc intrinsic; the original Havok code used a tiny inline-asm helper that
// reads the low 32 bits of the TSC for the monitor-stream timestamp.
static __forceinline unsigned hkRdtsc()
{
    unsigned t;
    __asm { rdtsc }
    __asm { mov t, eax }
    return t;
}

// Havok's HK_REAL_MAX sentinel (bit pattern 0x7f7fffee), used to seed AABB bounds.
#define HK_REAL_MAX 3.402820018375656e+38f

typedef unsigned char hkUchar;
typedef unsigned int  hkUint32;

// ---- Havok monitor stream (TLS) ----------------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorEndMarker[];             // 0x0149cc34

// ---- Havok thread memory -----------------------------------------------------------------------------------
extern unsigned long g_hkThreadMemoryTls;           // 0x016e4174
class hkThreadMemory
{ public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* onStackOverflow(int);
    virtual void onStackUnderflow(void*);
    hkUint32 pad[7];
    __declspec(nothrow) void deallocateChunk(void* p, int numBytes, int memoryClass);   // 0x0107db10
    static __forceinline hkThreadMemory* getInstance() { return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls); }
};
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };

extern "C" void hkArrayReserve(void* array, int newCapacity, int elementSize);   // 0x0107f4a0

// ---- core Havok types --------------------------------------------------------------------------------------
class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };
struct __declspec(align(16)) hkAabb    { hkVector4 m_min, m_max; };
// hkTransform: a 3x4 rotation (three hkVector4 columns) followed by the translation.
struct __declspec(align(16)) hkTransform { hkVector4 m_rotation[3]; hkVector4 m_translation; };
struct __declspec(align(16)) hkSphere { hkVector4 m_pos; };

template <typename T> class hkArray { public: T* m_data; int m_size; int m_capacityAndFlags; };
struct hkRay { hkVector4 m_start; hkVector4 m_end; };
template <typename T, int N> class hkInplaceArray { public: hkArray<T> m_array; T m_storage[N]; };

// hkBool is a class with a user copy ctor, so it is returned through a hidden pointer (as the original does).
class hkBool
{
public:
    hkUchar m_bool;
    hkBool() {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    hkBool(const hkBool& o) : m_bool(o.m_bool) {}
    operator bool() const { return m_bool != 0; }
};

struct hkShapeRayCastInput  { hkVector4 m_from; hkVector4 m_to; };
struct hkShapeRayCastOutput { hkVector4 m_hitPoint; hkUint32 m_shapeKey; float m_hitFraction; };

class hkCdBody
{ public:
    void*    m_shape;      // +0x0
    hkUint32 m_shapeKey;   // +0x4
    void*    m_motion;     // +0x8
    hkCdBody* m_parent;    // +0xc
};

class hkRayHitCollector
{ public:
    virtual void addHit(const hkCdBody& body, const float* hit);   // slot 0
    float m_earlyOutHitFraction;                                   // +0x4
};

class hkStatisticsCollector
{ public:
    virtual void slot0();
    virtual void beginObject(const char* name, int id, const void* obj);                          // +0x4
    virtual void addArray(const char* name, int id, const void* ptr, int size, int sizeInMemory);  // +0x8
    virtual void slotC();
    virtual void slot10();
    virtual void slot14();
    virtual void endObject();                                                                      // +0x18
};

// ---- hkMultiSphereShape ------------------------------------------------------------------------------------
// hkMultiSphereShape derives from a vptr+m_flags+m_userData base (as Havok's hkShape does); keeping the
// 16-byte-aligned sphere member in the *derived* class is what makes MSVC pack it at +0x10 (a flat class
// with an align(16) member gets 4 bytes of padding after the vptr).
struct hkShapeBase
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    hkUint32 m_flags;      // +0x4
    hkUint32 m_userData;   // +0x8
};
struct hkMultiSphereShape : hkShapeBase
{
    virtual hkBool castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const;                              // +0x14
    virtual void castRayWithCollector(const hkShapeRayCastInput& in, const hkCdBody& body, hkRayHitCollector& col) const; // +0x18
    virtual void getAabb(const hkTransform& t, float tol, hkAabb& aabb) const;                                           // +0x1c
    hkUint32 m_n;           // +0xc
    hkVector4 m_spheres[1]; // +0x10 (w = radius)
};

// @ 0x010c7100
void hkMultiSphereShape::getAabb(const hkTransform& t, float tol, hkAabb& aabb) const
{
    float pts[256];
    int n = (int)m_n;
    for (int i = 0; i < n; ++i) {
        const hkVector4& c = m_spheres[i];
        pts[i * 4 + 0] = t.m_rotation[0].x * c.x + t.m_rotation[1].x * c.y + t.m_rotation[2].x * c.z + t.m_translation.x;
        pts[i * 4 + 1] = t.m_rotation[0].y * c.x + t.m_rotation[1].y * c.y + t.m_rotation[2].y * c.z + t.m_translation.y;
        pts[i * 4 + 2] = t.m_rotation[0].z * c.x + t.m_rotation[1].z * c.y + t.m_rotation[2].z * c.z + t.m_translation.z;
        pts[i * 4 + 3] = 0.0f;
    }
    float mn[4], mx[4];
    for (int j = 0; j < 4; ++j) { mn[j] = HK_REAL_MAX; mx[j] = -HK_REAL_MAX; }
    for (int i = 0; i < n; ++i) {
        float r = m_spheres[i].w;
        for (int j = 0; j < 4; ++j) {
            float lo = pts[i * 4 + j] - r;
            float hi = pts[i * 4 + j] + r;
            if (lo <= mn[j]) mn[j] = lo;
            if (mx[j] <= hi) mx[j] = hi;
        }
    }
    aabb.m_min.x = mn[0] - tol;
    aabb.m_min.y = mn[1] - tol;
    aabb.m_min.z = mn[2] - tol;
    aabb.m_min.w = mn[3] - tol;
    aabb.m_max.x = mx[0] + tol;
    aabb.m_max.y = mx[1] + tol;
    aabb.m_max.z = mx[2] + tol;
    aabb.m_max.w = mx[3] + tol;
}

// @ 0x010c76a0
hkBool hkMultiSphereShape::castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const
{
    {
        unsigned char* end = *(unsigned char**)TlsGetValue(g_hkMonitorStreamEndTls);
        unsigned char* cur = *(unsigned char**)TlsGetValue(g_hkMonitorStreamCurrentTls);
        if (cur < end) {
            *(const char**)cur = "TtrcMultiSpher";
            *(unsigned int*)(cur + 4) = hkRdtsc();
            TlsSetValue(g_hkMonitorStreamCurrentTls, cur + 0xc);
        }
    }
    hkUchar hit = 0;
    int n = (int)m_n;
    for (int i = 0; i < n; ++i) {
        const hkVector4& c = m_spheres[i];
        float mx = in.m_from.x - c.x;
        float my = in.m_from.y - c.y;
        float mz = in.m_from.z - c.z;
        float mw = in.m_from.w - c.w;
        float dx = (in.m_to.x - c.x) - mx;
        float dy = (in.m_to.y - c.y) - my;
        float dz = (in.m_to.z - c.z) - mz;
        float b = (dx * mx + (dy * my + dz * mz)) * 2.0f;
        if (b < 0.0f) {
            float a = dx * dx + (dy * dy + dz * dz);
            float disc = b * b - (((mx * mx + (my * my + mz * mz)) - c.w * c.w) * a) * 4.0f;
            if (disc > 0.0f) {
                float t = (-b - sqrtf(disc)) * 0.5f;
                if (t < a && t >= 0.0f) {
                    t = t / a;
                    if (t < out.m_hitFraction) {
                        out.m_hitFraction = t;
                        hit = 1;
                        float s = 1.0f - t;
                        out.m_hitPoint.x = (in.m_to.x - c.x) * t + mx * s;
                        out.m_hitPoint.y = (in.m_to.y - c.y) * t + my * s;
                        out.m_hitPoint.z = (in.m_to.z - c.z) * t + mz * s;
                        out.m_hitPoint.w = (in.m_to.w - c.w) * t + mw * s;
                        float inv = 1.0f / c.w;
                        out.m_shapeKey = (hkUint32)i;
                        out.m_hitPoint.x *= inv;
                        out.m_hitPoint.y *= inv;
                        out.m_hitPoint.z *= inv;
                        out.m_hitPoint.w *= inv;
                    }
                }
            }
        }
    }
    {
        unsigned char* end = *(unsigned char**)TlsGetValue(g_hkMonitorStreamEndTls);
        unsigned char* cur = *(unsigned char**)TlsGetValue(g_hkMonitorStreamCurrentTls);
        if (cur < end) {
            *(const void**)cur = hkMonitorEndMarker;
            *(unsigned int*)(cur + 4) = hkRdtsc();
            TlsSetValue(g_hkMonitorStreamCurrentTls, cur + 0xc);
        }
    }
    return hkBool(hit != 0);
}

// @ 0x010c79a0
void hkMultiSphereShape::castRayWithCollector(const hkShapeRayCastInput& in, const hkCdBody& body,
                                              hkRayHitCollector& col) const
{
    hkShapeRayCastOutput out;
    out.m_hitFraction = col.m_earlyOutHitFraction;
    if (castRay(in, out)) {
        const float* m = (const float*)body.m_motion;
        float px = out.m_hitPoint.x;
        float py = out.m_hitPoint.y;
        float pz = out.m_hitPoint.z;
        out.m_hitPoint.x = m[0] * px + m[4] * py + m[8] * pz;
        out.m_hitPoint.y = (m[1] * px + m[9] * pz) + m[5] * py;
        out.m_hitPoint.z = m[2] * px + m[6] * py + m[10] * pz;
        out.m_hitPoint.w = 0.0f;
        col.addHit(body, (const float*)&out.m_hitPoint);
    }
}

// ---- hkMultiRayShape ---------------------------------------------------------------------------------------
// Each ray is two hkVector4 endpoints (0x20 bytes); m_rays is an hkArray's data at +0xc, size +0x10,
// capacityAndFlags +0x14.  vptr +0x0, 8 bytes of hkShape header -> m_rays at +0xc.
struct hkMultiRayShape
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void calcStatistics(hkStatisticsCollector* c) const;
    virtual void getAabb(const hkTransform& t, float tol, hkAabb& aabb) const;
    hkUint32 m_pad4;             // +0x4
    hkUint32 m_pad8;             // +0x8
    hkVector4* m_rays;           // +0xc
    int m_numRays;               // +0x10
    int m_raysCapacityAndFlags;  // +0x14
};

// @ 0x010c7a50
void hkMultiRayShape::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("MultiRay", 1, this);
    if ((m_raysCapacityAndFlags & 0x80000000) == 0) {
        c->addArray("Rays", 1, m_rays, m_numRays << 5, (m_raysCapacityAndFlags & 0x3fffffff) * (int)sizeof(hkRay));
    }
    c->endObject();
}

// @ 0x010c7b40
void hkMultiRayShape::getAabb(const hkTransform& t, float tol, hkAabb& aabb) const
{
    (void)tol;
    int n = m_numRays;
    int endpoints = n * 2;
    hkRay buf[16];
    hkArray<hkRay> pts;
    pts.m_data = buf;
    pts.m_size = 0;
    pts.m_capacityAndFlags = (int)0x80000010;
    if (endpoints > 16) {
        int cap = endpoints > 31 ? endpoints : 32;
        hkArrayReserve(&pts, cap, 0x20);
    }
    hkVector4* dst = (hkVector4*)pts.m_data;
    const hkVector4* src = m_rays;
    for (int i = 0; i < endpoints; ++i) {
        float x = src[i].x, y = src[i].y, z = src[i].z;
        dst[i].x = t.m_rotation[0].x * x + t.m_rotation[1].x * y + t.m_rotation[2].x * z + t.m_translation.x;
        dst[i].y = t.m_rotation[0].y * x + t.m_rotation[1].y * y + t.m_rotation[2].y * z + t.m_translation.y;
        dst[i].z = t.m_rotation[0].z * x + t.m_rotation[1].z * y + t.m_rotation[2].z * z + t.m_translation.z;
        dst[i].w = 0.0f;
    }
    float mn[4], mx[4];
    for (int j = 0; j < 4; ++j) { mn[j] = HK_REAL_MAX; mx[j] = -HK_REAL_MAX; }
    for (int i = 0; i < n; ++i) {
        const float* r = (const float*)&pts.m_data[i];
        for (int j = 0; j < 8; ++j) {
            if (r[j] <= mn[j & 3]) mn[j & 3] = r[j];
            if (mx[j & 3] <= r[j]) mx[j & 3] = r[j];
        }
    }
    aabb.m_min.x = mn[0];
    aabb.m_min.y = mn[1];
    aabb.m_min.z = mn[2];
    aabb.m_min.w = mn[3];
    aabb.m_max.x = mx[0];
    aabb.m_max.y = mx[1];
    aabb.m_max.z = mx[2];
    aabb.m_max.w = mx[3];
    if (pts.m_capacityAndFlags >= 0) {
        hkThreadMemory::getInstance()->deallocateChunk(pts.m_data,
            (pts.m_capacityAndFlags & 0x3fffffff) * (int)sizeof(hkRay), HK_MEMORY_CLASS_ARRAY);
    }
}

// ---- hkMoppBvTreeShape -------------------------------------------------------------------------------------
class __declspec(align(16)) hkMoppSphereVirtualMachine
{
public:
    void querySphere(const void* code, const hkSphere& sphere, hkArray<hkUint32>& out);   // 0x011013f0
    hkVector4 m_a, m_b;                                                                   // 0x20 bytes
};

class __declspec(align(16)) hkMoppObbVirtualMachine
{
public:
    void queryObb(const void* code, const hkTransform& t, const hkVector4& v, float r,
                  hkArray<hkUint32>& out);                                                // 0x01101c00
    hkVector4 m_a, m_b, m_c, m_d;                                                         // 0x40 bytes
};

struct hkMoppCode;
class hkMoppBvTreeShape
{ public:
    hkUint32 m_pad0[4];      // +0x00 .. +0x0f
    const hkMoppCode* m_code;// +0x10
    void querySphere(const hkSphere& sphere, hkArray<hkUint32>& out) const;
    void queryObb(const hkTransform& t, const hkVector4& v, float r, hkArray<hkUint32>& out) const;
};

// @ 0x010c80b0
void hkMoppBvTreeShape::querySphere(const hkSphere& sphere, hkArray<hkUint32>& out) const
{
    hkMoppSphereVirtualMachine vm;
    vm.querySphere(m_code, sphere, out);
}

// @ 0x010c80e0
void hkMoppBvTreeShape::queryObb(const hkTransform& t, const hkVector4& v, float r,
                                 hkArray<hkUint32>& out) const
{
    hkMoppObbVirtualMachine vm;
    vm.queryObb(m_code, t, v, r, out);
}
