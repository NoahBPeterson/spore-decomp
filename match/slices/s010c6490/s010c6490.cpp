// Slice s010c6490 -- Havok 3.1 shape tail: storage/simple-mesh destructors and accessors,
// plane-shape ray/sphere casts, statistics, and a few small vtable helpers.
//
// Module flags: /O2 /MD /Gy /EHsc /TP /vc71   (Havok 3.1.0 was built with VC .NET 2003 cl 13.10)
#include "types.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef unsigned char  hkUchar;
typedef unsigned short hkUint16;
typedef unsigned int   hkUint32;

// ---- monitor stream (TLS) ----------------------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern "C" unsigned __int64 __rdtsc(void);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorEndMarker[];             // 0x0149cc34

// ---- memory ------------------------------------------------------------------------------------------------
extern unsigned long g_hkThreadMemoryTls;   // 0x016e4174

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

class hkMemory
{ public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    __declspec(nothrow) void deallocateChunk(void* p, int size, int type);   // vtable +0x14
};
extern hkMemory* g_hkMemory;   // 0x016e4178

template <typename T> class hkArray
{ public:
    T* m_data;
    int m_size;
    int m_capacityAndFlags;
    __forceinline void freeStorageIfOwned()
    {
        int c = m_capacityAndFlags;
        _ReadWriteBarrier();
        if (!(c & (int)0x80000000))
            hkThreadMemory::getInstance()->deallocateChunk(m_data,
                (int)((m_capacityAndFlags & 0x3fffffff) * sizeof(T)), HK_MEMORY_CLASS_ARRAY);
    }
};

// ---- Havok shapes ------------------------------------------------------------------------------------------
class __declspec(align(16)) hkVector4 { public: float x, y, z, w;
    void setRotatedDir(const struct hkTransform& rotation, const hkVector4& dir);      // 0x010814a0
    void setTransformedPos(const struct hkTransform& transform, const hkVector4& p);   // 0x01081360
};
struct __declspec(align(16)) hkAabb { hkVector4 m_min; hkVector4 m_max; };
struct __declspec(align(16)) hkTransform { hkUint32 m_rotation[12]; hkVector4 m_translation; };

class hkCdBody
{ public:
    void*    m_shape;      // +0x0
    hkUint32 m_shapeKey;   // +0x4
    void*    m_motion;     // +0x8
    hkCdBody* m_parent;    // +0xc
};

// A real vptr (the class is polymorphic) + 4 bytes of bookkeeping = 0x8, then m_userData at +0x8.
class hkReferencedObject { public: virtual void vptrAnchor(); hkUint16 m_memSizeAndFlags; hkUint16 m_referenceCount; };  // 0x8
class hkShape : public hkReferencedObject { public: int m_userData; };                                              // 0xc
class hkShapeCollection : public hkShape { public: hkUchar m_disableWelding; };                                     // 0x10

struct hkShapeRayCastInput
{
    hkVector4 m_from;      // +0x0
    hkVector4 m_to;        // +0x10
    hkUint32 m_filterInfo; // +0x20
    void* m_rayShapeCollectionFilter;   // +0x24
};
struct hkShapeRayCastOutput
{
    hkVector4 m_normal;    // +0x0
    hkUint32 m_shapeKey;   // +0x10
    float    m_hitFraction;// +0x14
};

class hkRayHitCollector
{ public:
    virtual void addHit(const hkCdBody& body, const float* hit);   // slot 0
    float m_earlyOutHitFraction;   // +0x4
};

class hkStatisticsCollector
{ public:
    virtual void slot0();
    virtual void beginObject(const char* name, int id, const void* obj);              // +0x4
    virtual void addArray(const char* name, int id, const void* ptr, int size, int sizeInMemory);  // +0x8
    virtual void slotC();
    virtual void slot10();
    virtual void slot14();
    virtual void endObject();   // +0x18
};

// hkPlaneShape: hkShape (+0x0), m_plane (+0x10), aabb min (+0x20), aabb ext (+0x30), cosAngle (+0x34).
// The ray-cast helpers take the plane itself as the shape's "normal" (m_plane.w is its offset).
class hkPlaneShape : public hkShape { public:
    hkUint32  m_pad0c;      // +0xc  (alignment gap before the 16-byte plane)
    hkVector4 m_plane;      // +0x10
    hkVector4 m_aabbMin;    // +0x20
    hkVector4 m_aabbExt;    // +0x30
    float     m_cosAngle;   // +0x34
    void castRayWithCollector(const hkShapeRayCastInput& in, const hkCdBody& body, hkRayHitCollector& col) const;  // 0x010c69e0
    void collideSpheres(const void* input, hkVector4* out) const;               // 0x010c6c20
    void castSphere(const void* input, const hkCdBody& body, hkRayHitCollector& col) const;  // 0x010c6a40
    void getAabb(const hkTransform& t, float tol, hkAabb& aabb) const;          // 0x010c6d60
    hkUchar castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const;   // 0x010c6d90
    void calcStatistics(hkStatisticsCollector* c) const;                        // 0x010c69a0
};

struct hkAabbUtil
{
    static void calcAabb(const hkTransform& t, const hkVector4& plane, const hkVector4& ext, float radius, hkAabb& out);  // 0x010c16b0
};

// ---- hkSimpleMeshShape -------------------------------------------------------------------------------------
struct hkSimpleMeshShapeTriangle { int m_a, m_b, m_c; };
// A 12-byte array header specialised for the vector array (the templated form gets 16 bytes).
struct hkVertexArray
{
    hkVector4* m_data;   // +0x0
    int m_size;          // +0x4
    int m_capacityAndFlags;   // +0x8
    __forceinline void freeStorageIfOwned()
    {
        int c = m_capacityAndFlags;
        _ReadWriteBarrier();
        if (!(c & (int)0x80000000))
            hkThreadMemory::getInstance()->deallocateChunk(m_data,
                (m_capacityAndFlags & 0x3fffffff) * 16, HK_MEMORY_CLASS_ARRAY);
    }
};
struct hkSimpleMeshShape : hkShapeCollection
{
    hkVertexArray m_vertices;                       // +0x10
    hkArray<hkSimpleMeshShapeTriangle> m_triangles; // +0x1c
    hkArray<hkUchar> m_materialIndices;             // +0x28
    float m_radius;                                 // +0x34
    hkSimpleMeshShape(float radius);                                    // 0x010c6890
    virtual ~hkSimpleMeshShape();                                       // 0x010c6900
    void getAabb(const hkTransform& t, float tol, hkAabb& aabb) const;  // 0x010c6570
    void* getChildShape(hkUint32 key, void* buf) const;                 // 0x010c6700
    hkUint32 getNextKey(hkUint32 key) const;                            // 0x010c67b0
    void calcStatistics(hkStatisticsCollector* c) const;                // 0x010c67d0
};

// Output buffer view used by hkSimpleMeshShape::getChildShape (a one-triangle hkShapeShim).
struct hkTriangleShim
{
    void*    vftable;    // +0x0
    hkUint16 m_type;     // +0x4
    hkUint16 m_flags;    // +0x6
    hkUint32 m_shapeKey; // +0x8
    float    m_radius;   // +0xc
    float    m_a[4];     // +0x10
    float    m_b[4];     // +0x20
    float    m_c[4];     // +0x30
};

// ---- hkStorageMeshShape ------------------------------------------------------------------------------------
struct hkStorageMeshShapeSubpartStorage
{
    hkArray<float>    m_vertices;          // +0x0
    hkArray<hkUint16> m_indices16;         // +0xc
    hkArray<hkUint32> m_indices32;         // +0x18
    hkArray<hkUchar>  m_materialIndices;   // +0x24
    hkArray<hkUint32> m_materials;         // +0x30
    hkArray<hkUint16> m_materialIndices16; // +0x3c
    ~hkStorageMeshShapeSubpartStorage();   // 0x010c5de0
};

// hkMeshShape layout: scaling +0x10, subparts +0x24, radius +0x30.  m_storage (+0x40) is the
// array of SubpartStorage pointers.
struct hkStorageMeshShape : hkShapeCollection
{
    float m_scaling[4];             // +0x10
    int   m_numBitsForSubpartIndex; // +0x20
    void* m_subpartsA;              // +0x24
    int   m_subpartsSize;           // +0x28
    int   m_subpartsCapAndFlags;    // +0x2c
    float m_radius;                 // +0x30
    hkUint32 m_pad34[3];            // +0x34 .. +0x3f
    hkStorageMeshShapeSubpartStorage** m_storage;   // +0x40
    int   m_storageSize;            // +0x44
    int   m_storageCapAndFlags;     // +0x48
    ~hkStorageMeshShape();          // 0x010c6490
};

// ---- hkMultiSphereShape ------------------------------------------------------------------------------------
struct hkCollisionSpheresInfo { hkUint32 m_numSpheres; hkUchar m_hasSpheres; };
class hkSphereRepShape : public hkReferencedObject { public: int m_userData; };   // 0xc
struct hkMultiSphereShape : hkSphereRepShape
{
    hkUint32 m_n;           // +0xc (the original reads [this+0xc])
    void getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const;   // 0x010c70a0
    void calcStatistics(hkStatisticsCollector* c) const;                // 0x010c70c0
};

// ---- hkShapeContainer (the vtable-only stub at 0x010c70b0) -------------------------------------------------
struct hkShapeContainer
{
    void* getShape(hkUint32 dummy) const;   // 0x010c70b0
};

// @ 0x010c6490
hkStorageMeshShape::~hkStorageMeshShape()
{
    for (int i = 0; i < m_storageSize; ++i) {
        hkStorageMeshShapeSubpartStorage* s = *(hkStorageMeshShapeSubpartStorage**)((char*)m_storage + i * 4);
        if (s != 0) {
            s->~hkStorageMeshShapeSubpartStorage();
            g_hkMemory->deallocateChunk(s, 0x48, 0x22);
        }
    }
    {
        int c = m_storageCapAndFlags;
        _ReadWriteBarrier();
        if (!(c & (int)0x80000000))
            hkThreadMemory::getInstance()->deallocateChunk(m_storage,
                (m_storageCapAndFlags & 0x3fffffff) * 4, HK_MEMORY_CLASS_ARRAY);
    }
    {
        int c = m_subpartsCapAndFlags;
        _ReadWriteBarrier();
        if (!(c & (int)0x80000000))
            hkThreadMemory::getInstance()->deallocateChunk(m_subpartsA,
                (m_subpartsCapAndFlags & 0x3fffffff) * 0x30, HK_MEMORY_CLASS_ARRAY);
    }
    *(void**)this = (void*)0x013ef094;
}

// @ 0x010c6570
void hkSimpleMeshShape::getAabb(const hkTransform& t, float tolerance, hkAabb& out) const
{
    out.m_min.x = out.m_min.y = out.m_min.z = 3.402820018375656e+38f;
    out.m_min.w = 0.0f;
    out.m_max.x = out.m_max.y = out.m_max.z = -3.402820018375656e+38f;
    out.m_max.w = 0.0f;
    hkVector4 v;
    for (int i = 0; i < m_vertices.m_size; ++i) {
        v.setTransformedPos(t, *(const hkVector4*)((const char*)m_vertices.m_data + i * 16));
        if (out.m_min.x > v.x) out.m_min.x = v.x;
        if (out.m_min.y > v.y) out.m_min.y = v.y;
        if (out.m_min.z > v.z) out.m_min.z = v.z;
        if (out.m_min.w > v.w) out.m_min.w = v.w;
        if (v.x > out.m_max.x) out.m_max.x = v.x;
        if (v.y > out.m_max.y) out.m_max.y = v.y;
        if (v.z > out.m_max.z) out.m_max.z = v.z;
        if (v.w > out.m_max.w) out.m_max.w = v.w;
    }
    float r = tolerance + m_radius;
    out.m_min.x -= r; out.m_min.y -= r; out.m_min.z -= r; out.m_min.w -= r;
    out.m_max.x += r; out.m_max.y += r; out.m_max.z += r; out.m_max.w += r;
}

// @ 0x010c6700
void* hkSimpleMeshShape::getChildShape(hkUint32 key, void* buf) const
{
    hkTriangleShim* out = (hkTriangleShim*)buf;
    if (out != 0) {
        out->m_radius = m_radius;
        out->m_flags = 1;
        out->m_shapeKey = 0;
        out->vftable = (void*)0x014a3bfc;
    } else {
        out = 0;
    }
    hkUint32 tri = key * 3;
    const hkUint32* idx = (const hkUint32*)((const char*)m_triangles.m_data + tri * 4);
    {
        const hkVector4* v = (const hkVector4*)((const char*)m_vertices.m_data + idx[0] * 16);
        out->m_a[0] = v->x; out->m_a[1] = v->y; out->m_a[2] = v->z; out->m_a[3] = v->w;
    }
    {
        const hkVector4* v = (const hkVector4*)((const char*)m_vertices.m_data + idx[1] * 16);
        out->m_b[0] = v->x; out->m_b[1] = v->y; out->m_b[2] = v->z; out->m_b[3] = v->w;
    }
    {
        const hkVector4* v = (const hkVector4*)((const char*)m_vertices.m_data + idx[2] * 16);
        out->m_c[0] = v->x; out->m_c[1] = v->y; out->m_c[2] = v->z; out->m_c[3] = v->w;
    }
    return out;
}

// @ 0x010c67b0
hkUint32 hkSimpleMeshShape::getNextKey(hkUint32 key) const
{
    hkUint32 k = key + 1;
    if ((int)k >= m_triangles.m_size)
        k = 0xffffffff;
    return k;
}

// @ 0x010c67d0
void hkSimpleMeshShape::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("StorageMesh", 1, this);
    if (m_vertices.m_capacityAndFlags >= 0)
        c->addArray("Vertices", 1, m_vertices.m_data, m_vertices.m_size << 4, (m_vertices.m_capacityAndFlags & 0x3fffffff) << 4);
    if (m_triangles.m_capacityAndFlags >= 0)
        c->addArray("Triangles", 1, m_triangles.m_data, m_triangles.m_size * 0xc,
                    (m_triangles.m_capacityAndFlags & 0x3fffffff) * 0xc);
    if (m_materialIndices.m_capacityAndFlags >= 0)
        c->addArray("MaterialIds", 1, m_materialIndices.m_data, m_materialIndices.m_size,
                    m_materialIndices.m_capacityAndFlags & 0x3fffffff);
    c->endObject();
}

// @ 0x010c6890
extern "C" void hkShapeCollectionCtor_(void* self);   // 0x010e7fd0
hkSimpleMeshShape::hkSimpleMeshShape(float radius)
{
    hkShapeCollectionCtor_(this);
    m_vertices.m_data = 0; m_vertices.m_size = 0; m_vertices.m_capacityAndFlags = (int)0x80000000;
    m_triangles.m_data = 0; m_triangles.m_size = 0; m_triangles.m_capacityAndFlags = (int)0x80000000;
    m_materialIndices.m_data = 0; m_materialIndices.m_size = 0; m_materialIndices.m_capacityAndFlags = (int)0x80000000;
    m_radius = radius;
}

// @ 0x010c6900
hkSimpleMeshShape::~hkSimpleMeshShape()
{
    if (m_materialIndices.m_capacityAndFlags >= 0)
        hkThreadMemory::getInstance()->deallocateChunk(m_materialIndices.m_data,
            m_materialIndices.m_capacityAndFlags & 0x3fffffff, HK_MEMORY_CLASS_ARRAY);
    if (m_triangles.m_capacityAndFlags >= 0)
        hkThreadMemory::getInstance()->deallocateChunk(m_triangles.m_data,
            (m_triangles.m_capacityAndFlags & 0x3fffffff) * 0xc, HK_MEMORY_CLASS_ARRAY);
    if (m_vertices.m_capacityAndFlags >= 0)
        hkThreadMemory::getInstance()->deallocateChunk(m_vertices.m_data,
            (m_vertices.m_capacityAndFlags & 0x3fffffff) * 0x10, HK_MEMORY_CLASS_ARRAY);
    *(void**)this = (void*)0x013ef094;
}

// @ 0x010c69a0
void hkPlaneShape::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("PlaneShape", 1, this);
    c->endObject();
}

// @ 0x010c69e0
void hkPlaneShape::castRayWithCollector(const hkShapeRayCastInput& in, const hkCdBody& body, hkRayHitCollector& col) const
{
    hkShapeRayCastOutput shim;
    shim.m_normal = m_plane;
    shim.m_shapeKey = 0;
    shim.m_hitFraction = m_cosAngle;
    if (castRay(in, shim)) {
        hkVector4 dir;
        dir.setRotatedDir(*(const hkTransform*)body.m_motion, in.m_to);
        col.addHit(body, (const float*)&dir);
    }
}

// @ 0x010c6a40
void hkPlaneShape::castSphere(const void* input, const hkCdBody& body, hkRayHitCollector& col) const
{
    const float* p = (const float*)input;   // hkSphereCastInput: from, to, radius, ...
    float fVar1 = (m_plane.x * p[0] + (m_plane.y * p[1] + m_plane.z * p[2])) + m_plane.w - p[0xc];
    float fVar2 = (m_plane.x * p[4] + (m_plane.y * p[5] + m_plane.z * p[6])) + m_plane.w - p[0xc];
    if (fVar1 >= 0.0f || fVar2 > fVar1)
        return;
    fVar2 = fVar1 - fVar2;
    if (p[0xd] > fVar2)
        return;
    if (fVar1 < 0.0f == (fVar1 == 0.0f))
        fVar1 = fVar1 / fVar2;
    else
        fVar1 = 0.0f;
    fVar2 = 1.0f - fVar1;
    float ax = (fVar2 * p[0] + fVar1 * p[4]) - m_aabbMin.x; if (ax < 0) ax = -ax;
    float ay = (fVar2 * p[1] + fVar1 * p[5]) - m_aabbMin.y; if (ay < 0) ay = -ay;
    float az = (fVar2 * p[2] + fVar1 * p[6]) - m_aabbMin.z; if (az < 0) az = -az;
    if ((((az < m_aabbExt.z) << 1) | ((ay < m_aabbExt.y) << 2) | ((ax < m_aabbExt.x) * -8) & 0xe) == 0xe) {
        float hit[5];
        hit[0] = m_plane.x; hit[1] = m_plane.y; hit[2] = m_plane.z; hit[3] = m_plane.w;
        *(int*)&hit[4] = -1;
        col.addHit(body, hit);
    }
}

// @ 0x010c6c20
struct hkCollideSpheresInput { hkVector4* m_spheres; int m_numSpheres; };

void hkPlaneShape::collideSpheres(const void* input, hkVector4* out) const
{
    const hkCollideSpheresInput* in = (const hkCollideSpheresInput*)input;
    float* sphere = (float*)in->m_spheres;
    int count = in->m_numSpheres;
    if (--count < 0)
        return;
    ++count;
    do {
        float ax = sphere[0] - m_aabbMin.x; if (ax < 0) ax = -ax;
        float ay = sphere[1] - m_aabbMin.y; if (ay < 0) ay = -ay;
        float az = sphere[2] - m_aabbMin.z; if (az < 0) az = -az;
        float aw = sphere[3] - m_aabbMin.w; if (aw < 0) aw = -aw;
        int bx = (ax <= m_aabbExt.x) << 3;
        int by = (ay <= m_aabbExt.y) << 2;
        int bz = (az <= m_aabbExt.z) << 1;
        int bw = (aw <= m_aabbExt.w);
        if (((bx | by | bz | bw) & 0xe) == 0xe) {
            out->x = m_plane.x; out->y = m_plane.y; out->z = m_plane.z; out->w = m_plane.w;
            out->w = sphere[0] * m_plane.x + (m_plane.z * sphere[2] + m_plane.y * sphere[1]) + m_plane.w;
        } else {
            out->w = 3.40282e+38f;
        }
        out = (hkVector4*)((char*)out + 16);
        sphere += 4;
    } while (--count != 0);
}

// @ 0x010c6d60
void hkPlaneShape::getAabb(const hkTransform& t, float tol, hkAabb& aabb) const
{
    hkAabbUtil::calcAabb(t, m_aabbExt, m_aabbMin, tol, aabb);
}

// @ 0x010c6d90
hkUchar hkPlaneShape::castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const
{
    {
        unsigned char* end = *(unsigned char**)TlsGetValue(g_hkMonitorStreamEndTls);
        unsigned char* cur = *(unsigned char**)TlsGetValue(g_hkMonitorStreamCurrentTls);
        if (cur < end) {
            *(const char**)cur = "TtrcPlane";
            *(unsigned int*)(cur + 4) = (unsigned int)__rdtsc();
            TlsSetValue(g_hkMonitorStreamCurrentTls, cur + 0xc);
        }
    }
    float f0 = m_plane.x * in.m_from.x + (m_plane.y * in.m_from.y + m_plane.z * in.m_from.z) + m_plane.w;
    float f1 = m_plane.x * in.m_to.x + (m_plane.y * in.m_to.y + m_plane.z * in.m_to.z) + m_plane.w;
    if (0.0f <= f0 && f1 < 0.0f) {
        float t = f0 / (f0 - f1);
        float t1 = 1.0f - t;
        float px = t1 * in.m_from.x + t * in.m_to.x;
        float py = t1 * in.m_from.y + t * in.m_to.y;
        float pz = t1 * in.m_from.z + t * in.m_to.z;
        float ax = px - m_aabbMin.x; if (ax < 0) ax = -ax;
        float ay = py - m_aabbMin.y; if (ay < 0) ay = -ay;
        float az = pz - m_aabbMin.z; if (az < 0) az = -az;
        if ((((az < m_aabbExt.z) << 1) | ((ay < m_aabbExt.y) << 2) | ((ax < m_aabbExt.x) * -8) & 0xe) == 0xe) {
            out.m_hitFraction = t;
            out.m_normal = m_plane;
            out.m_shapeKey = 0xffffffff;
            {
                unsigned char* end = *(unsigned char**)TlsGetValue(g_hkMonitorStreamEndTls);
                unsigned char* cur = *(unsigned char**)TlsGetValue(g_hkMonitorStreamCurrentTls);
                if (cur < end) {
                    *(const void**)cur = hkMonitorEndMarker;
                    *(unsigned int*)(cur + 4) = (unsigned int)__rdtsc();
                    TlsSetValue(g_hkMonitorStreamCurrentTls, cur + 0xc);
                }
            }
            return 1;
        }
    }
    {
        unsigned char* end = *(unsigned char**)TlsGetValue(g_hkMonitorStreamEndTls);
        unsigned char* cur = *(unsigned char**)TlsGetValue(g_hkMonitorStreamCurrentTls);
        if (cur < end) {
            *(const void**)cur = hkMonitorEndMarker;
            *(unsigned int*)(cur + 4) = (unsigned int)__rdtsc();
            TlsSetValue(g_hkMonitorStreamCurrentTls, cur + 0xc);
        }
    }
    return 0;
}

// @ 0x010c70a0
void hkMultiSphereShape::getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const
{
    info.m_numSpheres = m_n;
    info.m_hasSpheres = 0;
}

// @ 0x010c70c0
void hkMultiSphereShape::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("MultiSphere", 1, this);
    c->endObject();
}

// @ 0x010c70b0
void* hkShapeContainer::getShape(hkUint32 dummy) const
{
    (void)dummy;
    return (void*)((char*)this + 0x10);
}

// @ 0x010c7010
class hkCollisionFilter { public: virtual ~hkCollisionFilter(); };   // 0x005efd40
struct hkCollisionFilterSub : hkCollisionFilter
{
    virtual ~hkCollisionFilterSub();
};
hkCollisionFilterSub::~hkCollisionFilterSub()
{
    *(void**)((char*)this + 0x0)  = (void*)0x0149dba0;
    *(void**)((char*)this + 0x8)  = (void*)0x0149db98;
    *(void**)((char*)this + 0xc)  = (void*)0x0149db90;
    *(void**)((char*)this + 0x10) = (void*)0x0149db88;
    *(void**)((char*)this + 0x14) = (void*)0x0149db80;
}
