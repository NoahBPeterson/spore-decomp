// Slice s010c44d0 -- Havok 3.1.0 hkTriSampledHeightField* shapes and the
// hkTriSampledHeightFieldCollection / hkTriSampledHeightFieldBvTreeShape vtables
// (0x010c44d0 .. 0x010c5470).  Statically linked x87 build.
//
// Functional-equivalence rewrite.  Layouts are the retail 32-bit ones (see
// match/include/havok31/hkReflectedClasses.h).  hkMonitorStream timers use
// TlsGetValue/TlsSetValue exactly like the original inline expansions.
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP  (Havok objects were built by VC .NET 2003).
#include "types.h"
#include <intrin.h>
#include <math.h>

#pragma pack(push, 4)

// ---------------------------------------------------------------------------
// monitor stream
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;   // 0x016e42a8
extern const char    hkTimerEnd[];              // 0x0149cc34 (timer end marker)
extern const char    hkTtrcTriangle[];          // 0x014a3c30 ("TtrcTriangle")

struct hkMonitorRecord { const char* m_name; uint32_t m_time; uint32_t m_pad; };

static void hkTimerBegin(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurTls);
    if (cur < end) {
        hkMonitorRecord* r = (hkMonitorRecord*)cur;
        r->m_name = name;
        r->m_time = (uint32_t)__rdtsc();
        TlsSetValue(g_hkMonitorStreamCurTls, r + 1);
    }
}
static void hkTimerEndStamp()
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurTls);
    if (cur < end) {
        hkMonitorRecord* r = (hkMonitorRecord*)cur;
        r->m_name = hkTimerEnd;
        r->m_time = (uint32_t)__rdtsc();
        TlsSetValue(g_hkMonitorStreamCurTls, r + 1);
    }
}

// ---------------------------------------------------------------------------
// Havok types
// ---------------------------------------------------------------------------
class hkReferencedObject {
public:
    virtual void v0();          // +0x00 (dtor slot, scalar deleting)
    virtual void v1();          // +0x04 (dtor slot)
    uint16_t m_memSizeAndFlags;   // +0x04  (note: real layout +4/+6)
    uint16_t m_referenceCount;    // +0x06
    void removeReference()
    {
        if (m_memSizeAndFlags != 0 && --m_referenceCount == 0)
            delete this;
    }
};

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };

struct hkTransform { hkVector4 m_rotation[3]; hkVector4 m_translation; };   // 0x40
struct hkAabb      { hkVector4 m_min, m_max; };                            // 0x20

class hkBool {
public:
    char m_bool;
    hkBool() {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
};

struct hkShapeRayCastInput {
    hkVector4 m_from;          // +0x00
    hkVector4 m_to;            // +0x10
    uint32_t    m_filterInfo;    // +0x20
    void*     m_filter;        // +0x24
};
struct hkShapeRayCastOutput {
    float     m_normal[4];     // +0x00
    uint32_t    m_shapeKey;      // +0x10
    float     m_hitFraction;   // +0x14
};

struct hkArrayU32 { uint32_t* m_data; int m_size; int m_capacityAndFlags; };
extern "C" void hkArrayUtil_grow(void* array, int elemSize);                  // 0x0107f530
extern "C" void hkArrayUtil_reserveExactly(void* array, int n, int elemSize); // 0x0107f4a0

class hkSphere { public: hkVector4 m_center; float m_radius; };

// hkShape vtable (+0x0c = getAabb, +0x24 = getNextKey/getHeight, +0x28 = getChildShape)
class hkShape : public hkReferencedObject {
public:
    uint32_t m_userData;                                                            // +0x08
    // slots 0 (+0x00) and 1 (+0x04) are the destructors inherited from hkReferencedObject
    virtual void vslot2();                                                          // +0x08
    virtual void getAabb(const hkTransform& t, float tol, hkAabb& out) const;        // +0x0c
    virtual void vslot4();                                                          // +0x10
    virtual hkBool castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const;  // +0x14
    virtual void vslot6();                                                          // +0x18
    virtual void vslot7();                                                          // +0x1c
    virtual void vslot8();                                                          // +0x20
};

class hkShapeCollection : public hkShape {
public:
    uint8_t m_disableWelding;   // +0x0c
    virtual uint32_t getNextKey(uint32_t k) const;                                      // +0x24
    virtual const hkShape* getChildShape(uint32_t k, char (&buf)[512]) const;            // +0x28
};

class hkHeightFieldShape : public hkShape {
public:
    // slot +0x24 of a heightfield is getHeight(x, z)
    virtual float getHeight(int x, int z) const;
    virtual const hkShape* getChildShape(uint32_t k, char (&buf)[512]) const;            // +0x28
};

class hkSampledHeightFieldShape : public hkHeightFieldShape {
public:
    int32_t     m_xRes;                            // +0x0c
    int32_t     m_zRes;                            // +0x10
    float     m_heightCenter;                    // +0x14
    hkVector4 m_intToFloatScale;                 // +0x20
    hkVector4 m_floatToIntScale;                 // +0x30
    hkVector4 m_floatToIntOffsetFloorCorrected;  // +0x40
};

class hkTriangleShape : public hkShape {
public:
    float     m_radius;        // +0x0c
    hkVector4 m_vertexA;       // +0x10
    hkVector4 m_vertexB;       // +0x20
    hkVector4 m_vertexC;       // +0x30
    hkBool castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const;
};

class hkTriSampledHeightFieldCollection : public hkShapeCollection {
public:
    hkSampledHeightFieldShape* m_heightfield;   // +0x10
    float                      m_radius;        // +0x14

    ~hkTriSampledHeightFieldCollection();

    void getAabb(const hkTransform& t, float tol, hkAabb& out) const;
    uint32_t getNextKey(uint32_t key) const;
    const hkShape* getChildShape(uint32_t key, char (&buf)[512]) const;
};

class hkBvTreeShape : public hkShape {
public:
    hkShapeCollection* m_shapeCollection;   // +0x0c
    virtual void queryAabb(const hkAabb& aabb, hkArrayU32& hits) const;   // +0x24
    virtual void queryObb(const hkTransform& t, const hkVector4& extents, float tol,
                          hkArrayU32& hits) const;                        // +0x28
};

class hkTriSampledHeightFieldBvTreeShape : public hkBvTreeShape {
public:
    hkBool m_wantAabbRejectionTest;         // +0x10

    ~hkTriSampledHeightFieldBvTreeShape();

    hkBool castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const;
    void castRayWithCollector(const hkShapeRayCastInput& in, const void* body, void* collector) const;
    void queryAabb(const hkAabb& aabb, hkArrayU32& hits) const;
    void querySphere(const hkSphere& s, hkArrayU32& hits) const;
    void queryObb(const hkTransform& t, const hkVector4& extents, float tol, hkArrayU32& hits) const;
};

// hkAabbUtil @ 0x010c03a0
extern "C" void hkAabbUtil_calcAabb(const hkTransform& t, const hkVector4& halfExtents,
                                    float tol, hkAabb& out);
// hkMemory::s_instance @ 0x016e4178
extern void* g_hkMemoryInstance;

// ---------------------------------------------------------------------------
// @ 0x010c44d0  hkTriangleShape::castRay (slot 5)
// ---------------------------------------------------------------------------
hkBool hkTriangleShape::castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const
{
    hkTimerBegin(hkTtrcTriangle);

    const float Ax = m_vertexA.x, Ay = m_vertexA.y, Az = m_vertexA.z;

    // edge vectors
    float e0x = m_vertexB.x - Ax;
    float e0y = m_vertexB.y - Ay;
    float e0z = m_vertexB.z - Az;
    float e1x = m_vertexC.x - Ax;
    float e1y = m_vertexC.y - Ay;
    float e1z = m_vertexC.z - Az;

    // normal = -(e0 x e1)
    float nx = e1z * e0y - e1y * e0z;
    float ny = e0z * e1x - e1z * e0x;
    float nz = e1y * e0x - e0y * e1x;

    float d  = nx * Ax + (ny * Ay + nz * Az);

    float fFrom = (ny * in.m_from.y + (nz * in.m_from.z + nx * in.m_from.x)) - d;
    float fTo   = (nx * in.m_to.x   + (ny * in.m_to.y   + nz * in.m_to.z))   - d;

    if ((fTo * fFrom < 0.0f) || (fFrom == 0.0f && fTo != 0.0f)) {
        float t = fFrom / (fFrom - fTo);
        if (t < out.m_hitFraction) {
            float eps = (ny * ny + (nz * nz + nx * nx)) * -0.0001f;
            float om  = 1.0f - t;
            float px  = t * in.m_to.x + om * in.m_from.x;
            float py  = om * in.m_from.y + t * in.m_to.y;
            float pz  = om * in.m_from.z + t * in.m_to.z;

            float ax = Ax - px, ay = Ay - py, az = Az - pz;
            float bx = m_vertexB.x - px, by = m_vertexB.y - py, bz = m_vertexB.z - pz;

            if (eps <= (az * bx - bz * ax) * ny +
                       ((by * ax - ay * bx) * nz +
                        (bz * ay - by * az) * nx)) {
                float cx = m_vertexC.x - px, cy = m_vertexC.y - py, cz = m_vertexC.z - pz;
                if ((eps <= (bz * cx - cz * bx) * ny +
                            ((cy * bx - by * cx) * nz +
                             (cz * by - cy * bz) * nx)) &&
                    (eps <= (cz * ax - az * cx) * ny +
                            ((ay * cx - cy * ax) * nz +
                             (cy * az - cz * ay) * nx))) {
                    out.m_hitFraction = t;
                    out.m_normal[3]   = 0.0f;
                    if (fFrom <= 0.0f) {
                        out.m_normal[0] = -nx; out.m_normal[1] = -ny; out.m_normal[2] = -nz;
                    } else {
                        out.m_normal[0] =  nx; out.m_normal[1] =  ny; out.m_normal[2] =  nz;
                    }
                    float len2 = out.m_normal[2] * out.m_normal[2] +
                                 (out.m_normal[1] * out.m_normal[1] +
                                  out.m_normal[0] * out.m_normal[0]);
                    float inv = (len2 == 0.0f) ? 0.0f : 1.0f / (float)sqrt(len2);
                    out.m_shapeKey   = 0xffc00000u;     // original stores -NAN here
                    out.m_normal[0]  = inv * out.m_normal[0];
                    out.m_normal[1]  = inv * out.m_normal[1];
                    out.m_normal[2]  = inv * out.m_normal[2];
                    out.m_normal[3]  = inv * 0.0f;
                    hkTimerEndStamp();
                    return hkBool(true);
                }
            }
        }
    }
    hkTimerEndStamp();
    return hkBool(false);
}

// ---------------------------------------------------------------------------
// @ 0x010c49a0  hkTriSampledHeightFieldCollection::getAabb (slot 3)
// ---------------------------------------------------------------------------
void hkTriSampledHeightFieldCollection::getAabb(const hkTransform& t, float tol, hkAabb& out) const
{
    m_heightfield->getAabb(t, tol + m_radius, out);
}

// ---------------------------------------------------------------------------
// @ 0x010c49d0  hkTriSampledHeightFieldCollection::getNextKey (slot 9)
// ---------------------------------------------------------------------------
uint32_t hkTriSampledHeightFieldCollection::getNextKey(uint32_t key) const
{
    if ((key & 1) == 0)
        return key | 1;

    uint32_t z = key >> 16;
    int    x = (int)((key >> 1) & 0x7fff) + 1;
    const hkSampledHeightFieldShape* hf = m_heightfield;
    if (x == hf->m_xRes - 1) {
        x = 0;
        z = z + 1;
        if (z == (uint32_t)(hf->m_zRes - 1))
            return 0xffffffffu;
    }
    return (z * 0x8000 + (uint32_t)x) * 2;
}

// ---------------------------------------------------------------------------
// @ 0x010c4a20  hkTriangleShape constructor (placement)
// ---------------------------------------------------------------------------
void hkTriangleShapeCtor(hkTriangleShape* self)
{
    // 0x010e7fd0 (hkShapeCollection/hkShape ctor) sets the base vptr; the retail
    // sequence is: if (this) { baseCtor(this); this->vtbl = &hkTriangleShape::vtbl; }
    if (self != 0)
        *(void**)self = (void*)0x014a3c54;   // hkTriangleShape vtable
}

// ---------------------------------------------------------------------------
// @ 0x010c4a40  hkTriSampledHeightFieldCollection::getChildShape (slot 10)
// ---------------------------------------------------------------------------
const hkShape* hkTriSampledHeightFieldCollection::getChildShape(uint32_t key, char (&buf)[512]) const
{
    uint32_t xIdx = (key >> 1) & 0x7fff;
    uint32_t zIdx = key >> 16;

    hkTriangleShape* tri = 0;
    if (&buf[0] != 0) {
        hkTriangleShape* t = (hkTriangleShape*)&buf[0];
        t->m_memSizeAndFlags = 1;                              // word at +6
        t->m_radius          = m_radius;                       // dword at +0x0c
        t->m_userData        = 0;                              // dword at +0x08
        *(void**)t           = (void*)0x014a3bfc;              // hkTriangleShape vtable
        tri = t;
    }

    const hkSampledHeightFieldShape* hf = m_heightfield;

    float h00 = hf->getHeight((int)xIdx,     (int)zIdx);
    float h10 = hf->getHeight((int)xIdx + 1, (int)zIdx);
    float h01 = hf->getHeight((int)xIdx,     (int)zIdx + 1);
    float h11 = hf->getHeight((int)xIdx + 1, (int)zIdx + 1);

    float sx = hf->m_intToFloatScale.x, sy = hf->m_intToFloatScale.y,
          sz = hf->m_intToFloatScale.z;

    float x0 = (float)(int)xIdx       * sx;
    float x1 = (float)((int)xIdx + 1) * sx;
    float z0 = (float)(int)zIdx       * sz;
    float z1 = (float)((int)zIdx + 1) * sz;
    float y00 = h00 * sy, y10 = h10 * sy, y01 = h01 * sy, y11 = h11 * sy;

    if ((key & 1) == 0) {
        tri->m_vertexA.x = x1; tri->m_vertexA.y = y10; tri->m_vertexA.z = z0;
        tri->m_vertexA.w = 0.0f;
        tri->m_vertexB.x = x0; tri->m_vertexB.y = y01; tri->m_vertexB.z = z1;
        tri->m_vertexB.w = 0.0f;
        tri->m_vertexC.x = x1; tri->m_vertexC.y = y11; tri->m_vertexC.z = z1;
        tri->m_vertexC.w = 0.0f;
    } else {
        tri->m_vertexA.x = x0; tri->m_vertexA.y = y00; tri->m_vertexA.z = z0;
        tri->m_vertexA.w = 0.0f;
        tri->m_vertexB.x = x0; tri->m_vertexB.y = y01; tri->m_vertexB.z = z1;
        tri->m_vertexB.w = 0.0f;
        tri->m_vertexC.x = x1; tri->m_vertexC.y = y10; tri->m_vertexC.z = z0;
        tri->m_vertexC.w = 0.0f;
    }
    return tri;
}

// ---------------------------------------------------------------------------
// @ 0x010c4d40  hkTriSampledHeightFieldCollection destructor (deleting)
// ---------------------------------------------------------------------------
hkTriSampledHeightFieldCollection::~hkTriSampledHeightFieldCollection()
{
    m_heightfield->removeReference();
}

// ---------------------------------------------------------------------------
// @ 0x010c4d90  hkTriSampledHeightFieldBvTreeShape::castRay
// ---------------------------------------------------------------------------
hkBool hkTriSampledHeightFieldBvTreeShape::castRay(const hkShapeRayCastInput& in,
                                                   hkShapeRayCastOutput& out) const
{
    hkTriSampledHeightFieldCollection* coll =
        (hkTriSampledHeightFieldCollection*)m_shapeCollection;
    return coll->m_heightfield->castRay(in, out);
}

// ---------------------------------------------------------------------------
// @ 0x010c4dc0  hkTriSampledHeightFieldBvTreeShape::castRayWithCollector
// ---------------------------------------------------------------------------
void hkTriSampledHeightFieldBvTreeShape::castRayWithCollector(const hkShapeRayCastInput& in,
                                                              const void* body, void* collector) const
{
    hkTriSampledHeightFieldCollection* coll =
        (hkTriSampledHeightFieldCollection*)m_shapeCollection;
    void** vtbl = *(void***)coll->m_heightfield;
    ((void(*)(const hkShapeRayCastInput&, const void*, void*))vtbl[6])(in, body, collector);
}

// ---------------------------------------------------------------------------
// @ 0x010c4dd0  hkTriSampledHeightFieldBvTreeShape destructor (non-deleting)
// ---------------------------------------------------------------------------
hkTriSampledHeightFieldBvTreeShape::~hkTriSampledHeightFieldBvTreeShape()
{
    m_shapeCollection->removeReference();
}

// ---------------------------------------------------------------------------
// @ 0x010c4e20  hkTriSampledHeightFieldBvTreeShape::querySphere
// ---------------------------------------------------------------------------
void hkTriSampledHeightFieldBvTreeShape::querySphere(const hkSphere& s, hkArrayU32& hits) const
{
    float r  = s.m_radius;
    float nr = -r;
    hkAabb box;
    box.m_min.x = nr + s.m_center.x;
    box.m_min.y = nr + s.m_center.y;
    box.m_min.z = nr + s.m_center.z;
    box.m_min.w = nr + s.m_center.w;
    box.m_max.x = r + s.m_center.x;
    box.m_max.y = r + s.m_center.y;
    box.m_max.z = r + s.m_center.z;
    box.m_max.w = r + s.m_center.w;
    queryAabb(box, hits);
}

// ---------------------------------------------------------------------------
// @ 0x010c4e90  hkTriSampledHeightFieldBvTreeShape::queryObb
// ---------------------------------------------------------------------------
void hkTriSampledHeightFieldBvTreeShape::queryObb(const hkTransform& t, const hkVector4& extents,
                                                  float tol, hkArrayU32& hits) const
{
    hkAabb box;
    hkAabbUtil_calcAabb(t, extents, tol, box);
    queryAabb(box, hits);
}

// ---------------------------------------------------------------------------
// @ 0x010c4f50  hkTriSampledHeightFieldBvTreeShape::queryAabb
// ---------------------------------------------------------------------------
void hkTriSampledHeightFieldBvTreeShape::queryAabb(const hkAabb& aabb, hkArrayU32& hits) const
{
    const hkTriSampledHeightFieldCollection* coll =
        (const hkTriSampledHeightFieldCollection*)m_shapeCollection;
    const hkSampledHeightFieldShape* hf = coll->m_heightfield;
    float r  = coll->m_radius;
    float nr = -r;

    uint32_t zMin = (uint32_t)(((nr + aabb.m_min.z) + hf->m_floatToIntOffsetFloorCorrected.z) *
                           hf->m_floatToIntScale.z + 196608.0f) >> 6 & 0xffff;
    uint32_t xMin = (uint32_t)(((nr + aabb.m_min.x) + hf->m_floatToIntOffsetFloorCorrected.x) *
                           hf->m_floatToIntScale.x + 196608.0f) >> 6 & 0xffff;
    uint32_t xMax = (uint32_t)((( r + aabb.m_max.x) + hf->m_floatToIntOffsetFloorCorrected.x) *
                           hf->m_floatToIntScale.x + 196608.0f) >> 6 & 0xffff;
    uint32_t zMax = (uint32_t)((( r + aabb.m_max.z) + hf->m_floatToIntOffsetFloorCorrected.z) *
                           hf->m_floatToIntScale.z + 196608.0f) >> 6 & 0xffff;

    uint32_t xLim = (uint32_t)(hf->m_xRes - 1);
    uint32_t zLim = (uint32_t)(hf->m_zRes - 1);
    if ((xMin < xLim || xMax < xLim) && (zMin < zLim || zMax < zLim)) {
        if (xLim <= xMin) xMin = 0;
        if (zLim <= zMin) zMin = 0;
        if (xLim <= xMax) xMax = (uint32_t)(hf->m_xRes - 2);
        if (zLim <= zMax) zMax = (uint32_t)(hf->m_zRes - 2);

        int size = hits.m_size;
        float y0 = nr + aabb.m_min.y;
        float y1 =  r + aabb.m_max.y;

        if (!m_wantAabbRejectionTest.m_bool) {
            for (uint32_t x = xMin; x <= xMax; ++x) {
                if (zMin <= zMax) {
                    uint32_t base  = (zMin * 0x8000 + x) * 2;
                    int    count = (int)(zMax - zMin) + 1;
                    do {
                        if (hits.m_size == (hits.m_capacityAndFlags & 0x3fffffff))
                            hkArrayUtil_grow(&hits, 4);
                        hits.m_data[hits.m_size] = base;
                        size = hits.m_size;
                        hits.m_size = size + 1;
                        if ((uint32_t)(size + 1) == (uint32_t)(hits.m_capacityAndFlags & 0x3fffffff))
                            hkArrayUtil_grow(&hits, 4);
                        hits.m_data[hits.m_size] = base | 1;
                        base += 0x10000;
                        count = count - 1;
                        hits.m_size = hits.m_size + 1;
                    } while (count != 0);
                }
            }
            return;
        }

        bool testLow = true, testHigh = true;
        for (uint32_t x = xMin; x <= xMax; ++x) {
            if (zMin <= zMax) {
                uint32_t e = (zMin * 0x8000 + x) * 2;
                for (uint32_t z = zMin; z <= zMax; ++z) {
                    if (hits.m_size == (hits.m_capacityAndFlags & 0x3fffffff))
                        hkArrayUtil_grow(&hits, 4);
                    hits.m_data[hits.m_size] = e;
                    int i = hits.m_size;
                    hits.m_size = i + 1;
                    if ((uint32_t)(i + 1) == (uint32_t)(hits.m_capacityAndFlags & 0x3fffffff))
                        hkArrayUtil_grow(&hits, 4);
                    hits.m_data[hits.m_size] = e | 1;
                    hits.m_size = hits.m_size + 1;
                    if (testLow || testHigh) {
                        float h  = hf->getHeight((int)x, (int)z);
                        float hs = h * hf->m_floatToIntScale.w;
                        if (y0 < hs) testLow = false;
                        if (hs < y1) testHigh = false;
                    }
                    e += 0x10000;
                }
            }
        }
        if (!testLow && !testHigh)
            return;

        for (uint32_t x = xMin; x <= xMax + 1; ++x) {
            float h  = hf->getHeight((int)x, (int)(zMax + 1));
            float hs = h * hf->m_floatToIntScale.w;
            if (y0 < hs) testLow = false;
            if (hs < y1) testHigh = false;
        }
        for (uint32_t z = zMin; z <= zMax + 1; ++z) {
            float h  = hf->getHeight((int)(xMax + 1), (int)z);
            float hs = h * hf->m_floatToIntScale.w;
            if (y0 < hs) testLow = false;
            if (hs < y1) testHigh = false;
        }
        if (testLow || testHigh) {
            if ((int)(hits.m_capacityAndFlags & 0x3fffffff) < size) {
                int want = (hits.m_capacityAndFlags & 0x3fffffff) * 2;
                if (want <= size) want = size;
                hkArrayUtil_reserveExactly(&hits, want, 4);
            }
            hits.m_size = size;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x010c5470  hkTriSampledHeightFieldBvTreeShape::calcStatistics
// ---------------------------------------------------------------------------
void hkTriSampledHeightFieldBvTreeShape_calcStatistics(const void* self, void* collector)
{
    uint8_t* p  = (uint8_t*)self;
    void** vt = *(void***)collector;
    ((void(*)(void*, const char*, int, const void*))vt[1])(collector, "TransformShp", 1, self);
    ((void(*)(void*, const char*, int, const void*))vt[3])(collector, "ChildShape", 1,
                                                          *(void**)(p + 0x0c));
    ((void(*)(void*))vt[6])(collector);
}

#pragma pack(pop)
