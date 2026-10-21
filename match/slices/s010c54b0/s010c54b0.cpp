// Slice s010c54b0 -- Havok 3.1 shape wrappers: hkTransformShape virtuals (aabb / projection / ray casts),
// the sampled height-field shape queries, and the hkStorageMeshShape subpart storage/destructor family.
//
// Module flags: /O2 /MD /Gy /EHsc /TP /vc71   (Havok 3.1.0 was built with VC .NET 2003 cl 13.10)
//
// No PDB names exist for the three helpers that have no exported symbol; they are coined below and marked.
#include "types.h"
#include <math.h>

typedef unsigned char  hkUchar;
typedef unsigned short hkUint16;
typedef unsigned int   hkUint32;
typedef          int   hkInt32;

struct hkFinishLoadedObjectFlag { int m_finishing; };

// ---- monitor stream (TLS) ----------------------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern "C" unsigned __int64 __rdtsc(void);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorEndMarker[];             // 0x0149cc34
extern const char hkMonitorTimerTtrcTransform[];    // 0x014a3d30

struct hkMonitorTimer
{
    void enter()
    {
        unsigned char* end = *(unsigned char**)TlsGetValue(g_hkMonitorStreamEndTls);
        unsigned char* cur = *(unsigned char**)TlsGetValue(g_hkMonitorStreamCurrentTls);
        if (cur < end) {
            *(const char**)cur = hkMonitorTimerTtrcTransform;
            *(unsigned int*)(cur + 4) = (unsigned int)__rdtsc();
            TlsSetValue(g_hkMonitorStreamCurrentTls, cur + 12);
        }
    }
    void leave()
    {
        unsigned char* end = *(unsigned char**)TlsGetValue(g_hkMonitorStreamEndTls);
        unsigned char* cur = *(unsigned char**)TlsGetValue(g_hkMonitorStreamCurrentTls);
        if (cur < end) {
            *(const void**)cur = hkMonitorEndMarker;
            *(unsigned int*)(cur + 4) = (unsigned int)__rdtsc();
            TlsSetValue(g_hkMonitorStreamCurrentTls, cur + 12);
        }
    }
};

// ---- memory ------------------------------------------------------------------------------------------------
extern unsigned long g_hkThreadMemoryTls;   // 0x016e4174
extern unsigned long g_hkMemoryInstance;    // 0x016e4178

struct hkThreadMemory
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    void deallocateChunk(void* p, int nbytes, int cls);   // 0x0107db10
    static hkThreadMemory* getInstance() { return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls); }
};

struct hkMemory
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void* allocate(int nbytes, int cls);                 // slot 4 (+0x10)
    virtual void  deallocate(void* p, int nbytes, int cls);      // slot 5 (+0x14)
    static hkMemory* getInstance() { return (hkMemory*)g_hkMemoryInstance; }
};

struct hkArrayUtil
{
    static void _reserveMore(void* array, int elementSize);       // 0x0107f530
    static void _reserve(void* array, int n, int elementSize);    // 0x0107f4a0
};

enum
{
    HK_MEMORY_CLASS_ARRAY = 0x14,
    HK_MEMORY_CLASS_BASE  = 0x15,
    HK_MEMORY_CLASS_MESH  = 0x22,
    HK_MEMORY_CLASS_SHAPE = 0x24
};

// ---- math --------------------------------------------------------------------------------------------------
struct hkVector4
{
    float x, y, z, w;
    void setRotatedDir(const struct hkRotation& r, const hkVector4& d);   // 0x010814a0
};

struct hkRotation
{
    float m[12];
};

struct hkTransform
{
    float m[16];           // 3x4 rotation at +0x00, translation at +0x30
    void setMul(const hkTransform& a, const hkTransform& b);              // 0x01080ef0
};

struct hkAabb
{
    hkVector4 m_min;
    hkVector4 m_max;
};

void hkTransform::setMul(const hkTransform& a, const hkTransform& b)
{
    hkTransform r;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            float v = a.m[i * 4] * b.m[j] + a.m[i * 4 + 1] * b.m[4 + j]
                    + a.m[i * 4 + 2] * b.m[8 + j];
            if (j == 3)
                v += a.m[12 + i];
            r.m[i * 4 + j] = v;
        }
    }
    *this = r;
}

void hkVector4::setRotatedDir(const hkRotation& r, const hkVector4& d)
{
    float rx = r.m[0] * d.x + r.m[4] * d.y + r.m[8] * d.z;
    float ry = r.m[1] * d.x + r.m[5] * d.y + r.m[9] * d.z;
    float rz = r.m[2] * d.x + r.m[6] * d.y + r.m[10] * d.z;
    float rw = r.m[3] * d.x + r.m[7] * d.y + r.m[11] * d.z;
    x = rx; y = ry; z = rz; w = rw;
}

// A user-declared constructor makes hkBool non-POD, so MSVC returns it through a hidden pointer, as the binary does.
class hkBool
{
public:
    hkBool(char b) : m_bool(b) {}
    hkBool join(bool b) { m_bool = b ? 1 : 0; return *this; }
    hkBool operator==(const hkBool& b) { m_bool = (m_bool == b.m_bool) ? 1 : 0; return *this; }
    operator bool() const { return m_bool != 0; }
    char m_bool;
};

// ---- collision interfaces ----------------------------------------------------------------------------------
struct hkShapeRayCastInput
{
    hkVector4 m_from;
    hkVector4 m_to;
    hkVector4 m_extra;
};

struct hkShapeRayCastOutput
{
    hkVector4 m_normal;
};

struct hkRayHitCollector
{
    virtual void v0();
    virtual void v1();
    unsigned int m_pad[4];
};

struct hkCdBody
{
    const struct hkShape* m_shape;          // +0
    unsigned int m_shapeKey;                // +4
    const hkTransform* m_transform;         // +8
    const hkCdBody* m_parent;               // +0xc
};

struct hkShape
{
    virtual void* destroy(unsigned int flags);
    virtual void v1();
    virtual void v2();
    virtual void getAabb(const hkTransform& transform, float radius, hkAabb& aabb) const;
    virtual float getMaximumProjection(const hkVector4& dir) const;
    virtual hkBool castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const;
    virtual void castRayWithCollector(const hkShapeRayCastInput& in, const hkCdBody& body,
                                      hkRayHitCollector& collector) const;

    hkUint16 m_memSizeAndFlags;   // +0x04
    hkUint16 m_referenceCount;    // +0x06
    hkUint32 m_userData;          // +0x08

    void removeReference()
    {
        if (m_memSizeAndFlags != 0) {
            --m_referenceCount;
            if (m_referenceCount == 0)
                (*(void(__fastcall**)(void*, int))(*(void**)this))(this, 1);
        }
    }
};

// ---- hkTransformShape --------------------------------------------------------------------------------------
extern void* g_vtbl_hkTransformShape[];   // 0x014a3d14
extern void* g_vtbl_GmeRefCount[];        // 0x013ef094
extern void* g_vtbl_hkStorageMeshShape[]; // 0x014a3d84

struct hkTransformShape : hkShape
{
    virtual void* destroy(unsigned int flags);                                                  // 0x010c54b0
    virtual void getAabb(const hkTransform& transform, float radius, hkAabb& aabb) const;       // 0x010c5520
    virtual float getMaximumProjection(const hkVector4& dir) const;                             // 0x010c5560
    virtual hkBool castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const;     // 0x010c5650
    virtual void castRayWithCollector(const hkShapeRayCastInput& in, const hkCdBody& body,
                                      hkRayHitCollector& collector) const;                      // 0x010c5830

    hkShape* m_shape;        // +0x0c
    hkUint32 m_pad10;        // +0x10
    hkUint32 m_pad14;        // +0x14
    hkUint32 m_pad18;        // +0x18
    hkUint32 m_pad1c;        // +0x1c
    hkTransform m_transform; // +0x20
};

// @ 0x010c54b0
void* hkTransformShape::destroy(unsigned int flags)
{
    hkShape* s = m_shape;
    *(void**)this = (void*)0x014a3d14;
    s->removeReference();
    *(void**)this = (void*)0x013ef094;
    if ((flags & 1) != 0)
        hkMemory::getInstance()->deallocate(this, m_memSizeAndFlags, HK_MEMORY_CLASS_SHAPE);
    return this;
}

// @ 0x010c5520
void hkTransformShape::getAabb(const hkTransform& transform, float radius, hkAabb& aabb) const
{
    __declspec(align(16)) hkTransform local;
    local.setMul(transform, m_transform);
    m_shape->getAabb(local, radius, aabb);
}

// @ 0x010c5560
float hkTransformShape::getMaximumProjection(const hkVector4& dir) const
{
    float proj;
    {
        hkVector4 d;
        d.x = dir.x * m_transform.m[0] + (dir.y * m_transform.m[1] + dir.z * m_transform.m[2]);
        d.y = dir.x * m_transform.m[4] + (dir.y * m_transform.m[5] + dir.z * m_transform.m[6]);
        d.z = dir.x * m_transform.m[8] + (dir.y * m_transform.m[9] + dir.z * m_transform.m[10]);
        d.w = 0.0f;
        proj = m_shape->getMaximumProjection(d);
    }
    float a = dir.y * proj;
    float b = dir.x * proj;
    float c = dir.z * proj;
    float tx = (a * m_transform.m[1] + (b * m_transform.m[5] + c * m_transform.m[9])) + m_transform.m[13];
    float ty = (a * m_transform.m[0] + (b * m_transform.m[4] + c * m_transform.m[8])) + m_transform.m[12];
    float tz = (a * m_transform.m[2] + (b * m_transform.m[6] + c * m_transform.m[10])) + m_transform.m[14];
    return (tz * dir.z + (tx * dir.x)) + (ty * dir.y);
}

// @ 0x010c5650
hkBool hkTransformShape::castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const
{
    hkMonitorTimer timer;
    timer.enter();

    hkShapeRayCastInput local = in;
    local.m_from.w = 0.0f;
    local.m_to.w = 0.0f;
    local.m_extra.x = 0.0f;

    float dx = in.m_from.x - m_transform.m[12];
    float dy = in.m_from.y - m_transform.m[13];
    float dz = in.m_from.z - m_transform.m[14];
    local.m_from.x = dx * m_transform.m[0] + (dy * m_transform.m[1] + dz * m_transform.m[2]);
    local.m_from.y = dx * m_transform.m[4] + (dy * m_transform.m[5] + dz * m_transform.m[6]);
    local.m_from.z = dx * m_transform.m[8] + (dy * m_transform.m[9] + dz * m_transform.m[10]);

    dx = in.m_to.x - m_transform.m[12];
    dy = in.m_to.y - m_transform.m[13];
    dz = in.m_to.z - m_transform.m[14];
    local.m_to.x = dx * m_transform.m[0] + (dy * m_transform.m[1] + dz * m_transform.m[2]);
    local.m_to.y = dx * m_transform.m[4] + (dy * m_transform.m[5] + dz * m_transform.m[6]);
    local.m_to.z = dx * m_transform.m[8] + (dy * m_transform.m[9] + dz * m_transform.m[10]);

    hkBool hit = m_shape->castRay(local, out);
    if (hit.m_bool != 0) {
        hkVector4 v = out.m_normal;
        out.m_normal.setRotatedDir(*(const hkRotation*)&m_transform, v);
    }

    timer.leave();
    return hit;
}

// @ 0x010c5830
void hkTransformShape::castRayWithCollector(const hkShapeRayCastInput& in, const hkCdBody& body,
                                            hkRayHitCollector& collector) const
{
    hkMonitorTimer timer;
    timer.enter();

    hkShapeRayCastInput local = in;
    local.m_from.w = 0.0f;
    local.m_to.w = 0.0f;
    local.m_extra.x = 0.0f;

    float dx = in.m_from.x - m_transform.m[12];
    float dy = in.m_from.y - m_transform.m[13];
    float dz = in.m_from.z - m_transform.m[14];
    local.m_from.x = dx * m_transform.m[0] + (dy * m_transform.m[1] + dz * m_transform.m[2]);
    local.m_from.y = dx * m_transform.m[4] + (dy * m_transform.m[5] + dz * m_transform.m[6]);
    local.m_from.z = dx * m_transform.m[8] + (dy * m_transform.m[9] + dz * m_transform.m[10]);

    dx = in.m_to.x - m_transform.m[12];
    dy = in.m_to.y - m_transform.m[13];
    dz = in.m_to.z - m_transform.m[14];
    local.m_to.x = dx * m_transform.m[0] + (dy * m_transform.m[1] + dz * m_transform.m[2]);
    local.m_to.y = dx * m_transform.m[4] + (dy * m_transform.m[5] + dz * m_transform.m[6]);
    local.m_to.z = dx * m_transform.m[8] + (dy * m_transform.m[9] + dz * m_transform.m[10]);

    hkTransform world;
    world.setMul(*body.m_transform, m_transform);

    hkCdBody sub;
    sub.m_shape = m_shape;
    sub.m_shapeKey = body.m_shapeKey;
    sub.m_transform = &world;
    sub.m_parent = &body;

    m_shape->castRayWithCollector(local, sub, collector);

    timer.leave();
}

// ---- hkStorageSampledHeightFieldShape ----------------------------------------------------------------------
struct hkStorageSampledHeightFieldShape : hkShape
{
    hkInt32 m_widthX;         // +0x0c
    hkInt32 m_widthZ;         // +0x10
    hkUint32 m_pad14;         // +0x14
    hkUint32 m_pad18;         // +0x18
    hkUint32 m_pad1c;         // +0x1c
    hkUint32 m_pad20;         // +0x20
    float    m_sy2;           // +0x24
    hkUint32 m_pad28;         // +0x28
    hkUint32 m_pad2c;         // +0x2c
    float    m_sx;            // +0x30
    float    m_sy;            // +0x34
    float    m_sz;            // +0x38
    float    m_sw;            // +0x3c
    float    m_ox;            // +0x40
    hkUint32 m_pad44;         // +0x44
    float    m_oz;            // +0x48
    hkUint32 m_pad4c;         // +0x4c
    hkUint32 m_pad50;         // +0x50
    hkUint32 m_pad54;         // +0x54
    hkUint32 m_pad58;         // +0x58
    hkUint32 m_pad5c;         // +0x5c
    const float* m_heights;   // +0x60
    hkUint32 m_pad64;         // +0x64
    hkUint32 m_pad68;         // +0x68
    hkUchar  m_triangleFlip;  // +0x6c

    hkBool getTriangleFlip() const;                                    // 0x010c59f0
    float getHeightAt(int x, int z) const;                             // 0x010c5a00
    void collideSpheres(const struct hkHeightFieldCollideSpheresInput& in, hkVector4* out) const;  // 0x010c5a20
};

// @ 0x010c59f0
hkBool hkStorageSampledHeightFieldShape::getTriangleFlip() const
{
    return hkBool(m_triangleFlip);
}

// @ 0x010c5a00
float hkStorageSampledHeightFieldShape::getHeightAt(int x, int z) const
{
    return m_heights[m_widthX * z + x];
}

struct hkHeightFieldCollideSpheresInput
{
    const hkVector4* m_spheres;   // +0
    int m_numSpheres;             // +4
};

// @ 0x010c5a20
void hkStorageSampledHeightFieldShape::collideSpheres(const hkHeightFieldCollideSpheresInput& in,
                                                      hkVector4* out) const
{
    const hkVector4* s = in.m_spheres;
    int count = in.m_numSpheres;
    if (count > 0) {
        do {
            out->x = 0.0f;
            out->y = 1.0f;
            out->z = 0.0f;
            out->w = 3.40282e+38f;

            float sy = m_sy;
            float cy = s->y;
            unsigned int cx = (unsigned int)((s->x + m_ox) * m_sx + 196608.0f) >> 6 & 0xffff;
            unsigned int cz = (unsigned int)((m_oz + s->z) * m_sz + 196608.0f) >> 6 & 0xffff;

            if ((int)cx < m_widthX - 1 && (int)cz < m_widthZ - 1) {
                float fx = s->x * m_sx - (float)cx;
                float fz = m_sz * s->z - (float)cz;
                float h;
                float e1, e2;
                const float* c00;
                const float* c10;
                if (m_triangleFlip == 0) {
                    c00 = m_heights + (m_widthX * cz + cx);
                    float h00y = c00[1];
                    c10 = m_heights + ((cz + 1) * m_widthX + cx);
                    float h10x = *c10;
                    if (fz + fx <= 1.0f) {
                        h = *c00;
                        e1 = h00y - h;
                        e2 = h10x - h;
                    } else {
                        float h11y = c10[1];
                        e1 = h11y - h10x;
                        e2 = h11y - h00y;
                        h = (e2 * fz + (fx - 1.0f) * e1) + h00y;
                    }
                } else {
                    c00 = m_heights + (m_widthX * cz + cx);
                    h = *c00;
                    c10 = m_heights + ((cz + 1) * m_widthX + cx);
                    float h11y = c10[1];
                    if (fx <= fz) {
                        float h10x = *c10;
                        e1 = h11y - h10x;
                        e2 = h10x - h;
                    } else {
                        float h00y = c00[1];
                        e1 = h00y - h;
                        e2 = h11y - h00y;
                    }
                    h = (e1 * fx + e2 * fz) + h;
                }

                out->x = -e1;
                out->z = -e2;
                out->x = m_sx * out->x;
                out->y = m_sy * out->y;
                out->z = m_sz * out->z;
                out->w = m_sw * out->w;

                float len2 = out->z * out->z + (out->y * out->y + out->x * out->x);
                float inv;
                if (len2 == 0.0f)
                    inv = 0.0f;
                else
                    inv = 1.0f / (float)sqrt(len2);
                out->x = inv * out->x;
                out->y = inv * out->y;
                out->z = inv * out->z;
                out->w = inv * out->w;
                out->w = (sy * cy - h) * m_sy2 - s->w;
            }
            out++;
            s++;
            count--;
        } while (count != 0);
    }
}

// ---- hkStorageMeshShape subpart storage --------------------------------------------------------------------
struct hkMeshShapeSubpart
{
    void*        m_vertices;              // +0x00
    hkUint32     m_vertexStride;          // +0x04
    hkInt32      m_numVertices;           // +0x08
    void*        m_indices;               // +0x0c
    hkUchar      m_has16BitIndices;       // +0x10
    hkUchar      m_materialType;          // +0x11
    hkUint16     m_pad12;                 // +0x12
    hkUint32     m_indexStride;           // +0x14
    hkInt32      m_numTriangles;          // +0x18
    void*        m_materialIndices;       // +0x1c
    hkUint32     m_materialIndexStride;   // +0x20
    void*        m_materials;             // +0x24
    hkUint32     m_materialStride;        // +0x28
    hkInt32      m_numMaterials;          // +0x2c
};

template <class T>
struct hkArray
{
    T*     m_data;               // +0
    int    m_size;               // +4
    hkUint32 m_capacityAndFlags; // +8
    int capacity() const { return (int)(m_capacityAndFlags & 0x3fffffff); }
};

// Coined name: the 0x48-byte per-subpart storage block owned by hkStorageMeshShape.
struct hkStorageMeshShapeSubpartStorage
{
    hkArray<float>                 m_vertices;            // +0x00
    hkArray<hkUint16>              m_indices16;           // +0x0c
    hkArray<hkUint32>              m_indices32;           // +0x18
    hkArray<hkUchar>               m_materialIndices8;    // +0x24
    hkArray<hkUint32>              m_materials;           // +0x30
    hkArray<hkUint16>              m_materialIndices16;   // +0x3c

    ~hkStorageMeshShapeSubpartStorage();   // 0x010c5de0
};

// Coined name: a 0x30-byte storage block with one 0x30-stride array at +0x24.
struct hkSubpartBuilder
{
    hkUint32 m_pad00[9];               // +0x00..0x20
    hkArray<hkUchar> m_items;          // +0x24
    ~hkSubpartBuilder();               // 0x010c5da0
};

struct hkShapeCollection : hkShape
{
};

struct hkMeshShape : hkShapeCollection
{
    hkUint32 m_pad0c[6];   // +0x0c..0x20
    void init(hkFinishLoadedObjectFlag f);   // 0x010c8bc0
};

struct hkStorageMeshShape : hkMeshShape
{
    hkArray<hkMeshShapeSubpart>       m_subparts;   // +0x24
    hkUint32 m_pad30;                               // +0x30
    hkUint32 m_pad34;                               // +0x34
    hkUint32 m_pad38;                               // +0x38
    hkUint32 m_pad3c;                               // +0x3c
    hkArray<hkStorageMeshShapeSubpartStorage*> m_storage;   // +0x40

    hkStorageMeshShape* finish(hkFinishLoadedObjectFlag f);  // 0x010c5ee0
    void addSubpart(const hkMeshShapeSubpart& subpart);      // 0x010c5f50
    void hkStorageMeshShape_addSubpartElements(hkMeshShapeSubpart* dst, hkStorageMeshShapeSubpartStorage* sp, const hkMeshShapeSubpart& p);
};

extern hkUchar g_emptyMaterialTable[];   // 0x016e42d0

// @ 0x010c5da0
hkSubpartBuilder::~hkSubpartBuilder()
{
    if (!(m_items.m_capacityAndFlags & 0x80000000))
        hkThreadMemory::getInstance()->deallocateChunk(m_items.m_data,
                                                       (m_items.m_capacityAndFlags & 0x3fffffff) * 0x30,
                                                       HK_MEMORY_CLASS_ARRAY);
    *(void**)this = (void*)0x013ef094;
}

// @ 0x010c5de0
hkStorageMeshShapeSubpartStorage::~hkStorageMeshShapeSubpartStorage()
{
    if (!(m_materialIndices16.m_capacityAndFlags & 0x80000000))
        hkThreadMemory::getInstance()->deallocateChunk(m_materialIndices16.m_data,
                                                       (m_materialIndices16.m_capacityAndFlags & 0x3fffffff) << 1,
                                                       HK_MEMORY_CLASS_ARRAY);
    if (!(m_materials.m_capacityAndFlags & 0x80000000))
        hkThreadMemory::getInstance()->deallocateChunk(m_materials.m_data,
                                                       (m_materials.m_capacityAndFlags & 0x3fffffff) << 2,
                                                       HK_MEMORY_CLASS_ARRAY);
    if (!(m_materialIndices8.m_capacityAndFlags & 0x80000000))
    if (!(m_materialIndices8.m_capacityAndFlags & 0x80000000))
        hkThreadMemory::getInstance()->deallocateChunk(m_materialIndices8.m_data,
                                                       (int)(m_materialIndices8.m_capacityAndFlags & 0x3fffffff),
                                                       HK_MEMORY_CLASS_ARRAY);
    if (!(m_indices32.m_capacityAndFlags & 0x80000000))
        hkThreadMemory::getInstance()->deallocateChunk(m_indices32.m_data,
                                                       (m_indices32.m_capacityAndFlags & 0x3fffffff) << 2,
                                                       HK_MEMORY_CLASS_ARRAY);
    if (!(m_indices16.m_capacityAndFlags & 0x80000000))
        hkThreadMemory::getInstance()->deallocateChunk(m_indices16.m_data,
                                                       (m_indices16.m_capacityAndFlags & 0x3fffffff) << 1,
                                                       HK_MEMORY_CLASS_ARRAY);
    if (!(m_vertices.m_capacityAndFlags & 0x80000000))
        hkThreadMemory::getInstance()->deallocateChunk(m_vertices.m_data,
                                                       (m_vertices.m_capacityAndFlags & 0x3fffffff) << 2,
                                                       HK_MEMORY_CLASS_ARRAY);
}

// @ 0x010c5ee0
hkStorageMeshShape* hkStorageMeshShape::finish(hkFinishLoadedObjectFlag f)
{
    init(f);
    *(void**)this = (void*)0x014a3d84;
    if (f.m_finishing != 0) {
        int count = m_subparts.m_size;
        int i = 0;
        if (count > 0) {
            int off = 0;
            do {
                hkStorageMeshShapeSubpartStorage* st = m_storage.m_data[i];
                hkMeshShapeSubpart* sp = (hkMeshShapeSubpart*)((char*)m_subparts.m_data + off);
                sp->m_vertices = st->m_vertices.m_data;
                if (sp->m_has16BitIndices == 1)
                    sp->m_indices = st->m_indices16.m_data;
                else
                    sp->m_indices = st->m_indices32.m_data;
                if (sp->m_materialType == 1)
                    sp->m_materialIndices = st->m_materialIndices8.m_data;
                else
                    sp->m_materialIndices = st->m_materialIndices16.m_data;
                sp->m_materials = st->m_materials.m_data;
                i++;
                off += 0x30;
            } while (i < count);
        }
    }
    return this;
}

// @ 0x010c5f50
void hkStorageMeshShape::addSubpart(const hkMeshShapeSubpart& p)
{
    if (m_subparts.m_size == (int)(m_subparts.m_capacityAndFlags & 0x3fffffff))
        hkArrayUtil::_reserveMore(&m_subparts, 0x30);
    hkMeshShapeSubpart* dst = (hkMeshShapeSubpart*)((char*)m_subparts.m_data + m_subparts.m_size * 0x30);
    m_subparts.m_size = m_subparts.m_size + 1;

    hkStorageMeshShapeSubpartStorage* st = (hkStorageMeshShapeSubpartStorage*)
        hkMemory::getInstance()->allocate(0x48, 0x22);
    if (st == 0) {
        st = 0;
    } else {
        st->m_vertices.m_data = 0;
        st->m_vertices.m_size = 0;
        st->m_vertices.m_capacityAndFlags = 0x80000000;
        st->m_indices16.m_data = 0;
        st->m_indices16.m_size = 0;
        st->m_indices16.m_capacityAndFlags = 0x80000000;
        st->m_indices32.m_data = 0;
        st->m_indices32.m_size = 0;
        st->m_indices32.m_capacityAndFlags = 0x80000000;
        st->m_materialIndices8.m_data = 0;
        st->m_materialIndices8.m_size = 0;
        st->m_materialIndices8.m_capacityAndFlags = 0x80000000;
        st->m_materials.m_data = 0;
        st->m_materials.m_size = 0;
        st->m_materials.m_capacityAndFlags = 0x80000000;
        st->m_materialIndices16.m_data = 0;
        st->m_materialIndices16.m_size = 0;
        st->m_materialIndices16.m_capacityAndFlags = 0x80000000;
    }

    if (m_storage.m_size == (int)(m_storage.m_capacityAndFlags & 0x3fffffff))
        hkArrayUtil::_reserveMore(&m_storage, 4);
    m_storage.m_data[m_storage.m_size] = st;
    int n = m_storage.m_size + 1;
    m_storage.m_size = n;
    hkStorageMeshShapeSubpartStorage* sp = m_storage.m_data[n - 1];

    hkStorageMeshShape_addSubpartElements(dst, sp, p);
}

void hkStorageMeshShape::hkStorageMeshShape_addSubpartElements(hkMeshShapeSubpart* dst, hkStorageMeshShapeSubpartStorage* sp,
                                            const hkMeshShapeSubpart& p)
{
    // ---- vertices ----
    int vOld = sp->m_vertices.m_size;
    int vTotal = vOld + p.m_numVertices * 3;
    if (sp->m_vertices.capacity() < vTotal) {
        int cap = sp->m_vertices.capacity() * 2;
        if (cap <= vTotal)
            cap = vTotal;
        hkArrayUtil::_reserve(&sp->m_vertices, cap, 4);
    }
    sp->m_vertices.m_size = vTotal;
    {
        float* vdst = sp->m_vertices.m_data + vOld;
        const char* vsrc = (const char*)p.m_vertices;
        int i = 0;
        if (p.m_numVertices > 0) {
            do {
                vdst[0] = ((const float*)vsrc)[0];
                vdst[1] = ((const float*)vsrc)[1];
                vdst[2] = ((const float*)vsrc)[2];
                vsrc += p.m_vertexStride;
                vdst += 3;
                i++;
            } while (i < p.m_numVertices);
        }
    }
    dst->m_vertices = sp->m_vertices.m_data;
    dst->m_vertexStride = 0xc;
    dst->m_numVertices = p.m_numVertices;

    void* indexBase;
    if (p.m_has16BitIndices == 1) {
        unsigned int strideWords = (unsigned int)p.m_indexStride >> 1;
        unsigned int s = strideWords;
        if (s > 2)
            s = 3;
        dst->m_indexStride = s * 2;
        int add = p.m_numTriangles;
        if (strideWords == 1)
            add = add + 2;
        else if (strideWords == 2)
            add = add * 2 + 1;
        else
            add = add * 3;
        int old = sp->m_indices16.m_size;
        int total = old + add;
        if (sp->m_indices16.capacity() < total) {
            int cap = sp->m_indices16.capacity() * 2;
            if (cap <= total)
                cap = total;
            hkArrayUtil::_reserve(&sp->m_indices16, cap, 2);
        }
        sp->m_indices16.m_size = total;
        hkUint16* idst = sp->m_indices16.m_data + old;
        indexBase = idst;
        const char* isrc = (const char*)p.m_indices;
        int i = 0;
        if (p.m_numTriangles > 0) {
            do {
                ((hkUint16*)idst)[0] = ((const hkUint16*)isrc)[0];
                ((hkUint16*)idst)[1] = ((const hkUint16*)isrc)[1];
                ((hkUint16*)idst)[2] = ((const hkUint16*)isrc)[2];
                idst = (hkUint16*)((char*)idst + dst->m_indexStride);
                isrc += p.m_indexStride;
                i++;
            } while (i < p.m_numTriangles);
        }
    } else {
        unsigned int strideWords = (unsigned int)p.m_indexStride >> 2;
        unsigned int s = strideWords;
        if (s > 2)
            s = 3;
        dst->m_indexStride = s * 4;
        int add = p.m_numTriangles;
        if (strideWords == 1)
            add = add + 2;
        else if (strideWords == 2)
            add = add * 2 + 1;
        else
            add = add * 3;
        int old = sp->m_indices32.m_size;
        int total = old + add;
        if (sp->m_indices32.capacity() < total) {
            int cap = sp->m_indices32.capacity() * 2;
            if (cap <= total)
                cap = total;
            hkArrayUtil::_reserve(&sp->m_indices32, cap, 4);
        }
        sp->m_indices32.m_size = total;
        hkUint32* idst = sp->m_indices32.m_data + old;
        indexBase = idst;
        const char* isrc = (const char*)p.m_indices;
        int i = 0;
        if (p.m_numTriangles > 0) {
            do {
                ((hkUint32*)idst)[0] = ((const hkUint32*)isrc)[0];
                ((hkUint32*)idst)[1] = ((const hkUint32*)isrc)[1];
                ((hkUint32*)idst)[2] = ((const hkUint32*)isrc)[2];
                idst = (hkUint32*)((char*)idst + dst->m_indexStride);
                isrc += p.m_indexStride;
                i++;
            } while (i < p.m_numTriangles);
        }
    }
    dst->m_has16BitIndices = p.m_has16BitIndices;
    dst->m_numTriangles = p.m_numTriangles;
    dst->m_indices = indexBase;
    dst->m_materialType = p.m_materialType;

    // ---- material indices ----
    const char* matIdx = (const char*)p.m_materialIndices;
    if (matIdx == 0) {
        dst->m_materialIndices = 0;
        dst->m_materialIndexStride = 0;
    } else {
        if (p.m_materialType == 1) {
            if (p.m_materialIndexStride == 0) {
                if (sp->m_materialIndices8.m_size == sp->m_materialIndices8.capacity())
                    hkArrayUtil::_reserveMore(&sp->m_materialIndices8, 1);
                int old = sp->m_materialIndices8.m_size;
                sp->m_materialIndices8.m_data[old] = *(const hkUchar*)matIdx;
                sp->m_materialIndices8.m_size = old + 1;
                dst->m_materialIndices = sp->m_materialIndices8.m_data + old;
            } else {
                int old = sp->m_materialIndices8.m_size;
                int total = p.m_numTriangles + old;
                if (sp->m_materialIndices8.capacity() < total) {
                    int cap = sp->m_materialIndices8.capacity() * 2;
                    if (cap <= total)
                        cap = total;
                    hkArrayUtil::_reserve(&sp->m_materialIndices8, cap, 1);
                }
                sp->m_materialIndices8.m_size = total;
                hkUchar* d = sp->m_materialIndices8.m_data + old;
                dst->m_materialIndices = d;
                const char* s3 = matIdx;
                int i = 0;
                if (p.m_numTriangles > 0) {
                    do {
                        d[i] = *s3;
                        s3 += p.m_materialIndexStride;
                        i++;
                    } while (i < p.m_numTriangles);
                }
            }
        } else if (p.m_materialIndexStride == 0) {
            if (sp->m_materialIndices16.m_size == sp->m_materialIndices16.capacity())
                hkArrayUtil::_reserveMore(&sp->m_materialIndices16, 2);
            int old = sp->m_materialIndices16.m_size;
            sp->m_materialIndices16.m_data[old] = *(const hkUint16*)matIdx;
            sp->m_materialIndices16.m_size = old + 1;
            dst->m_materialIndices = sp->m_materialIndices16.m_data + old;
        } else {
            int old = sp->m_materialIndices16.m_size;
            int total = p.m_numTriangles + old;
            if (sp->m_materialIndices16.capacity() < total) {
                int cap = sp->m_materialIndices16.capacity() * 2;
                if (cap <= total)
                    cap = total;
                hkArrayUtil::_reserve(&sp->m_materialIndices16, cap, 2);
            }
            sp->m_materialIndices16.m_size = total;
            hkUint16* d = sp->m_materialIndices16.m_data + old;
            dst->m_materialIndices = d;
            const char* s3 = matIdx;
            int i = 0;
            if (p.m_numTriangles > 0) {
                do {
                    d[i] = *(const hkUint16*)s3;
                    s3 += p.m_materialIndexStride;
                    i++;
                } while (i < p.m_numTriangles);
            }
        }
        dst->m_materialIndexStride = p.m_materialIndexStride;
        if (dst->m_materialIndexStride != 0) {
            if (dst->m_materialType == 1)
                dst->m_materialIndexStride = 1;
            else if (dst->m_materialType == 2)
                dst->m_materialIndexStride = 2;
        }
    }

    if (dst->m_materialIndices == 0) {
        dst->m_numMaterials = 1;
        dst->m_materials = g_emptyMaterialTable;
        dst->m_materialStride = 0;
        dst->m_materialIndices = g_emptyMaterialTable;
        return;
    }

    // ---- materials ----
    if (p.m_materialStride != 0) {
        int old = sp->m_materials.m_size;
        int total = p.m_numMaterials + old;
        if (sp->m_materials.capacity() < total) {
            int cap = sp->m_materials.capacity() * 2;
            if (cap <= total)
                cap = total;
            hkArrayUtil::_reserve(&sp->m_materials, cap, 4);
        }
        hkUint32* d = sp->m_materials.m_data;
        sp->m_materials.m_size = total;
        const char* s4 = (const char*)p.m_materials;
        int i = 0;
        if (p.m_numMaterials > 0) {
            do {
                d[old + i] = *(const hkUint32*)s4;
                s4 += p.m_materialStride;
                i++;
            } while (i < p.m_numMaterials);
        }
        dst->m_materialStride = 4;
        dst->m_numMaterials = p.m_numMaterials;
        dst->m_materials = sp->m_materials.m_data;
    } else {
        if (sp->m_materials.m_size == sp->m_materials.capacity())
            hkArrayUtil::_reserveMore(&sp->m_materials, 4);
        int old = sp->m_materials.m_size;
        sp->m_materials.m_data[old] = *(const hkUint32*)p.m_materials;
        sp->m_materials.m_size = old + 1;
        dst->m_materialStride = 0;
        dst->m_numMaterials = 1;
        dst->m_materials = sp->m_materials.m_data;
    }
}

// @ 0x010c6470
// Coined name: the loading thunk that re-runs hkStorageMeshShape::finish(1) on a raw block.
void* hkStorageMeshShape_finishThunk(void* p)
{
    void* r = (void*)1;
    if (p != 0) {
        hkFinishLoadedObjectFlag f;
        f.m_finishing = 1;
        r = ((hkStorageMeshShape*)p)->finish(f);
    }
    return r;
}
