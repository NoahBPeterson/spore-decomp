// Havok 3.1.0 (statically linked, ~2005 MSVC x87 build): hkMoppBvTreeShape, hkMeshShape,
// hkListShape, hkFastMeshShape, hkCylinderShape statistics and a small FPU probe.
//
// Functional-equivalence rewrite (not byte-exact). Layouts are the retail 32-bit ones.
// Float rules: all aabb merges below use the exact compare polarity of the original
// (fcomp/fnstsw/test ah) so NaNs fall to the same side; expressions that stay on the
// x87 stack are written in double and marked X87-PRECISION.
#include "types.h"
#include <new>
#if defined(_M_IX86) || defined(_M_X64) || defined(__SSE__)
#include <xmmintrin.h>
#endif
#if defined(_MSC_VER)
#include <intrin.h>
#endif

#ifndef _WIN64
#define HK_OFFSET_CHECK(name, cond) typedef char name[(cond) ? 1 : -1]
#else
#define HK_OFFSET_CHECK(name, cond)
#endif

template <typename T> struct hkArray { T* m_data; int32_t m_size; int32_t m_capacityAndFlags; };
struct hkVector4 {
    float m_x, m_y, m_z, m_w;
    // @ 0x01081360  this = transform * v (position); w is written by the callee
    void setTransformedPos(const struct hkTransform& t, const hkVector4& v);
};
struct hkTransform { hkVector4 m_rotation[3]; hkVector4 m_translation; };
struct hkAabb { hkVector4 m_min, m_max; };
struct hkBool {                                   // non-trivial ctor: returned through a hidden pointer
    char m_bool;
    hkBool() {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
};
extern "C++" void hkArrayUtil_reserveMore(void* array, int elemSize);   // @ 0x0107f530

// ---- float helpers ----------------------------------------------------------------------
static inline int32_t hkFistp(float f)
{
#if defined(_M_IX86) || defined(_M_X64) || defined(__SSE__)
    return _mm_cvtss_si32(_mm_set_ss(f));       // round-to-nearest-even, 0x80000000 on overflow/NaN like fistp
#else
    if (!(f >= -2147483648.0f && f < 2147483648.0f)) return (int32_t)0x80000000;
    return (int32_t)lrintf(f);
#endif
}
// Min/max merge rules lifted from the compare sequences (NaN: the new value wins).
//   mergeMin:  fld a; fcomp b; jp/else ->  a < b ? a : b
//   mergeMax:  fld a; fcomp b; test 0x41 -> a > b ? a : b
static inline float hkMergeMin(float a, float b) { return (a < b) ? a : b; }
static inline float hkMergeMax(float a, float b) { return (a > b) ? a : b; }

// ---- monitor stream timers --------------------------------------------------------------
// HK_TIMER_BEGIN / HK_TIMER_END expand to the TLS monitor-stream append the original inlines:
//   if (cur < end) { cur->name = name; cur->time = low32(rdtsc); cur++ (12 byte records); }
extern unsigned long g_hkMonitorStreamEndTls;      // 0x016e42a8
extern unsigned long g_hkMonitorStreamCurTls;      // 0x016e42a4
struct hkMonitorStreamRecord { const char* m_name; uint32_t m_time; uint32_t m_pad; };
#ifdef _WIN32
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
static inline void* hkTlsGet(unsigned long i) { return TlsGetValue(i); }
static inline void  hkTlsSet(unsigned long i, void* v) { TlsSetValue(i, v); }
#else
void* hkTlsGet(unsigned long i);
void  hkTlsSet(unsigned long i, void* v);
#endif
static inline uint32_t hkRdtscLow()
{
#if defined(_MSC_VER)
    return (uint32_t)__rdtsc();
#else
    return (uint32_t)__builtin_ia32_rdtsc();
#endif
}
static inline void hkMonitorStamp(const char* name)
{
    void* end = hkTlsGet(g_hkMonitorStreamEndTls);
    void* cur = hkTlsGet(g_hkMonitorStreamCurTls);
    if (cur < end) {
        hkMonitorStreamRecord* r = (hkMonitorStreamRecord*)hkTlsGet(g_hkMonitorStreamCurTls);
        r->m_name = name;
        r->m_time = hkRdtscLow();
        hkTlsSet(g_hkMonitorStreamCurTls, r + 1);
    }
}

// ---- base classes -----------------------------------------------------------------------
struct hkReferencedObject {
    virtual ~hkReferencedObject() {}
    uint16_t m_memSizeAndFlags;     // +4 (0 = not heap allocated, never deleted)
    uint16_t m_referenceCount;      // +6
    // Same as hkReferencedObject::removeReference() (inlined everywhere in the binary)
    inline void removeReference()
    {
        if (m_memSizeAndFlags != 0) {
            if (--m_referenceCount == 0) delete this;
        }
    }
    inline void addReference() { if (m_memSizeAndFlags != 0) m_referenceCount++; }
};

struct hkStatisticsCollector {
    virtual ~hkStatisticsCollector();
    virtual void beginObject(const char* name, int flags, const void* obj);                                   // +4
    virtual void addArray(const char* name, int memClass, const void* data, int used, int allocated);        // +8
    virtual void addReferencedObject(const char* name, int memClass, const void* obj);                        // +0xc
    virtual void vslot4();
    virtual void vslot5();
    virtual void endObject();                                                                                // +0x18
};

struct hkShapeRayCastInput;
struct hkShapeRayCastOutput;
struct hkCdBody;
struct hkRayHitCollector;

struct hkShape : hkReferencedObject {
    uint32_t m_userData;            // +8
    virtual void vslot1();
    virtual void vslot2();
    virtual void getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const;   // +0x0c
    virtual void vslot4();
    virtual void vslot5();
    virtual void vslot6();
    virtual void vslot7();
    virtual void vslot8();
    virtual uint32_t getNextKey(uint32_t oldKey) const;                                           // +0x24
    virtual const hkShape* getChildShape(uint32_t key, char (&buffer)[512]) const;                // +0x28
};

struct hkTriangleShape : hkShape {
    float     m_radius;             // +0x0c
    hkVector4 m_vertices[3];        // +0x10, +0x20, +0x30
};

// hkTriangleUtil::isNonDegenerate(a, b, c, tolerance)  @ 0x010eb310
extern hkBool hkTriangleUtil_isNonDegenerate(const hkVector4& a, const hkVector4& b, const hkVector4& c, float tol);
extern float hkMeshShape_triangleDegeneracyTolerance;        // 0x015ba31c (1.0e-7f at load)

// ---- hkMoppBvTreeShape ------------------------------------------------------------------
struct hkMoppCode : hkReferencedObject {
    uint32_t  m_pad08[2];
    hkVector4 m_info;               // +0x10: xyz = offset, w = scale
    hkArray<uint8_t> m_data;        // +0x20: data, +0x24 size
};
struct hkShapeCollection;

struct hkMoppObbVirtualMachine {
    // @ 0x01101e90
    void queryAabb(const hkMoppCode* code, const hkAabb& aabb, hkArray<uint32_t>* out);
};
struct hkMoppLongRayVirtualMachine {
    uint8_t  m_pad[0x40];
    uint32_t m_zero0;               // +0x40 (zeroed by the callers)
    uint32_t m_zero1;               // +0x44
    // @ 0x01102fc0
    hkBool queryLongRay(const hkShapeCollection* coll, const hkMoppCode* code,
                        const hkShapeRayCastInput& in, hkShapeRayCastOutput& out);
    // @ 0x01103140
    void queryLongRay(const hkShapeCollection* coll, const hkMoppCode* code,
                      const hkShapeRayCastInput& in, const hkCdBody& body, hkRayHitCollector& collector);
};

struct hkMoppBvTreeShape : hkShape {
    hkShapeCollection* m_child;     // +0x0c
    hkMoppCode*        m_code;      // +0x10

    hkMoppBvTreeShape(const hkShapeCollection* collection, const hkMoppCode* code);
    ~hkMoppBvTreeShape();
    void queryAabb(const hkAabb& aabb, hkArray<uint32_t>& hits) const;
    void calcStatistics(hkStatisticsCollector* c) const;
    hkBool castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const;
    void castRayWithCollector(const hkShapeRayCastInput& in, const hkCdBody& body, hkRayHitCollector& collector) const;
};

// @ 0x010c8130
hkMoppBvTreeShape::hkMoppBvTreeShape(const hkShapeCollection* collection, const hkMoppCode* code)
{
    m_referenceCount = 1;
    m_userData = 0;
    m_child = (hkShapeCollection*)collection;
    ((hkReferencedObject*)collection)->addReference();
    m_code = (hkMoppCode*)code;
    ((hkReferencedObject*)code)->addReference();
}

// @ 0x010c8180
hkMoppBvTreeShape::~hkMoppBvTreeShape()
{
    m_code->removeReference();
    ((hkReferencedObject*)m_child)->removeReference();
}

// @ 0x010c81d0
void hkMoppBvTreeShape::queryAabb(const hkAabb& aabb, hkArray<uint32_t>& hits) const
{
    hkMoppCode* code = m_code;

    float ox = code->m_info.m_x, oy = code->m_info.m_y, oz = code->m_info.m_z, ow = code->m_info.m_w;
    // X87-PRECISION: the quotient 2^24 / scale stays unrounded in st(0) and is added to each
    // offset component, rounding only at the fstp to float.
    double q = 16777216.0 / (double)code->m_info.m_w;       // 2^24 const @ 0x014a3fa4

    hkAabb box;
    box.m_min.m_x = ox; box.m_min.m_y = oy; box.m_min.m_z = oz; box.m_min.m_w = ow;
    box.m_max.m_x = (float)((double)ox + q);
    box.m_max.m_y = (float)((double)oy + q);
    box.m_max.m_z = (float)((double)oz + q);
    box.m_max.m_w = ow;

    // Clamp to the query box. First four: keep own value only if strictly greater (fcomp +
    // test ah,0x41); last four: keep own value only if not less (test ah,5 / jnp).
    if (!(box.m_min.m_x > aabb.m_min.m_x)) box.m_min.m_x = aabb.m_min.m_x;
    if (!(box.m_min.m_y > aabb.m_min.m_y)) box.m_min.m_y = aabb.m_min.m_y;
    if (!(box.m_min.m_z > aabb.m_min.m_z)) box.m_min.m_z = aabb.m_min.m_z;
    if (!(box.m_min.m_w > aabb.m_min.m_w)) box.m_min.m_w = aabb.m_min.m_w;
    if (!(box.m_max.m_x < aabb.m_max.m_x)) box.m_max.m_x = aabb.m_max.m_x;
    if (!(box.m_max.m_y < aabb.m_max.m_y)) box.m_max.m_y = aabb.m_max.m_y;
    if (!(box.m_max.m_z < aabb.m_max.m_z)) box.m_max.m_z = aabb.m_max.m_z;
    if (!(box.m_max.m_w < aabb.m_max.m_w)) box.m_max.m_w = aabb.m_max.m_w;

    hkMoppObbVirtualMachine vm;
    vm.queryAabb(code, box, &hits);
}

// @ 0x010c8320
void hkMoppBvTreeShape::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("MoppShape", 1, this);
    c->addReferencedObject("Mesh", 1, m_child);
    c->addArray("Mopp", 1, m_code, m_code->m_data.m_size, 0);
    c->endObject();
}

// @ 0x010c83a0
hkBool hkMoppBvTreeShape::castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const
{
    hkMonitorStamp("TtrcMopp");                     // timer begin
    hkMoppLongRayVirtualMachine vm;
    vm.m_zero0 = 0;
    vm.m_zero1 = 0;
    hkBool hit = vm.queryLongRay(m_child, m_code, in, out);
    hkMonitorStamp("Et");                           // timer end (@ 0x0149cc34)
    return hit;
}

// @ 0x010c8490
void hkMoppBvTreeShape::castRayWithCollector(const hkShapeRayCastInput& in, const hkCdBody& body,
                                             hkRayHitCollector& collector) const
{
    hkMonitorStamp("TtrcMopp");
    hkMoppLongRayVirtualMachine vm;
    vm.m_zero0 = 0;
    vm.m_zero1 = 0;
    vm.queryLongRay(m_child, m_code, in, body, collector);
    hkMonitorStamp("Et");
}

// ---- hkMeshShape ------------------------------------------------------------------------
struct hkMeshMaterial { uint32_t m_filterInfo; };

struct hkMeshShapeSubpart {                // 0x30 bytes
    const float* m_vertexBase;             // +0x00
    int32_t m_vertexStriding;              // +0x04
    int32_t m_numVertices;                 // +0x08
    const void* m_indexBase;               // +0x0c
    int8_t  m_stridingType;                // +0x10 (1 = 16 bit indices, else 32 bit)
    int8_t  m_materialIndexStridingType;   // +0x11 (1 = 8 bit material indices, else 16 bit)
    int16_t m_pad12;
    int32_t m_indexStriding;               // +0x14
    int32_t m_numTriangles;                // +0x18
    const void* m_materialIndexBase;       // +0x1c
    int32_t m_materialIndexStriding;       // +0x20
    const void* m_materialBase;            // +0x24
    int32_t m_materialStriding;            // +0x28
    int32_t m_numMaterials;                // +0x2c
};
HK_OFFSET_CHECK(chk_subpart_size, sizeof(hkMeshShapeSubpart) == 0x30 || sizeof(void*) != 4);

struct hkMeshMaterial;
extern uint32_t hkMeshShape_defaultMaterial;   // 0x016e42d0 (shared zero material / dummy index byte)

struct hkMeshShape : hkShape {
    uint32_t  m_pad0c;                     // +0x0c
    hkVector4 m_scaling;                   // +0x10
    int32_t   m_numBitsForSubpartIndex;    // +0x20
    hkArray<hkMeshShapeSubpart> m_subparts;// +0x24 data, +0x28 size, +0x2c cap
    float     m_radius;                    // +0x30
    uint8_t   m_pad34[0x3c - 0x34];

    hkMeshShape(int finishLoadedFlag);
    virtual uint32_t getFirstKey() const;
    virtual uint32_t getNextKey(uint32_t oldKey) const;
    virtual const hkShape* getChildShape(uint32_t key, char (&buffer)[512]) const;
    virtual void getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const;
    virtual uint32_t getCollisionFilterInfo(uint32_t key) const;
    virtual void addSubpart(const hkMeshShapeSubpart& part);
    virtual void calcStatistics(hkStatisticsCollector* c) const;
    const hkMeshMaterial* getMeshMaterial(uint32_t key) const;
};
HK_OFFSET_CHECK(chk_mesh_radius, sizeof(hkShape) == 0x0c || sizeof(void*) != 4);

// @ 0x010c8560
uint32_t hkMeshShape::getFirstKey() const
{
    char buffer[512];
    const hkTriangleShape* tri = (const hkTriangleShape*)getChildShape(0, *(char(*)[512])buffer);
    hkBool ok = hkTriangleUtil_isNonDegenerate(tri->m_vertices[0], tri->m_vertices[1], tri->m_vertices[2],
                                               hkMeshShape_triangleDegeneracyTolerance);
    if (ok.m_bool == 1)
        return 0;
    return getNextKey(0);
}

// @ 0x010c85c0
const hkMeshMaterial* hkMeshShape::getMeshMaterial(uint32_t key) const
{
    uint32_t bits = (uint32_t)m_numBitsForSubpartIndex;
    uint32_t local = (0xffffffffu >> (bits & 0x1f)) & key;
    const hkMeshShapeSubpart& sp = m_subparts.m_data[key >> ((0x20 - bits) & 0x1f)];
    if (sp.m_materialIndexBase == 0)
        return 0;
    const uint8_t* idxAddr = (const uint8_t*)sp.m_materialIndexBase + (uint32_t)sp.m_materialIndexStriding * local;
    uint32_t idx;
    if (sp.m_materialIndexStridingType == 1) idx = *(const uint8_t*)idxAddr;
    else                                      idx = *(const uint16_t*)idxAddr;
    return (const hkMeshMaterial*)((const uint8_t*)sp.m_materialBase + (int32_t)(sp.m_materialStriding * idx));
}

// @ 0x010c8630 (hkMeshShape::getNextKey, slot 9)
uint32_t hkMeshShape::getNextKey(uint32_t oldKey) const
{
    const hkMeshShape* self = this;
    uint32_t bits = (uint32_t)self->m_numBitsForSubpartIndex;
    uint32_t subpartIdx = oldKey >> ((0x20 - bits) & 0x1f);
    uint32_t local = (0xffffffffu >> (bits & 0x1f)) & oldKey;
    int32_t byteOff = (int32_t)(subpartIdx * 0x30);
    uint32_t key;
    char buffer[512];
    for (;;) {
        local = local + 1;
        if (*(const int32_t*)((const uint8_t*)self->m_subparts.m_data + 0x18 + byteOff) <= (int32_t)local) {
            subpartIdx = subpartIdx + 1;
            byteOff += 0x30;
            if ((uint32_t)self->m_subparts.m_size <= subpartIdx)
                return 0xffffffffu;
            local = 0;
        }
        key = (subpartIdx << ((0x20u - bits) & 0x1f)) | local;
        const hkTriangleShape* tri = (const hkTriangleShape*)self->getChildShape(key, *(char(*)[512])buffer);
        hkBool ok = hkTriangleUtil_isNonDegenerate(tri->m_vertices[0], tri->m_vertices[1], tri->m_vertices[2],
                                                   hkMeshShape_triangleDegeneracyTolerance);
        if (ok.m_bool == 1) break;
    }
    return key;
}

// @ 0x010c8700 (hkMeshShape::getChildShape, slot 10)
const hkShape* hkMeshShape::getChildShape(uint32_t key, char (&buffer)[512]) const
{
    const hkMeshShape* self = this;
    uint32_t bits = (uint32_t)self->m_numBitsForSubpartIndex;
    const hkMeshShapeSubpart& sp = self->m_subparts.m_data[key >> ((0x20 - bits) & 0x1f)];
    const uint8_t* idx = (const uint8_t*)sp.m_indexBase + sp.m_indexStriding * ((0xffffffffu >> (bits & 0x1f)) & key);
    const uint8_t* vbase = (const uint8_t*)sp.m_vertexBase;
    int32_t stride = sp.m_vertexStriding;

    uint32_t i0, i1, i2;
    if (sp.m_stridingType == 1) {
        i0 = ((const uint16_t*)idx)[0];
        i1 = ((const uint16_t*)idx)[1];
        i2 = ((const uint16_t*)idx)[2];
    } else {
        i0 = ((const uint32_t*)idx)[0];
        i1 = ((const uint32_t*)idx)[1];
        i2 = ((const uint32_t*)idx)[2];
    }
    const float* v0 = (const float*)(vbase + i0 * stride);
    const float* v1 = (const float*)(vbase + i1 * stride);
    const float* v2 = (const float*)(vbase + i2 * stride);
    float sx = self->m_scaling.m_x, sy = self->m_scaling.m_y, sz = self->m_scaling.m_z;

    hkTriangleShape* tri = (hkTriangleShape*)buffer;
    if (tri) {
        // hkTriangleShape(radius): only the refcount, userdata, radius and vptr are written
        new (tri) hkTriangleShape;
        tri->m_referenceCount = 1;
        tri->m_userData = 0;
        tri->m_radius = self->m_radius;
    }
    tri->m_vertices[0].m_z = v0[2] * sz;
    tri->m_vertices[0].m_x = v0[0] * sx;
    tri->m_vertices[0].m_y = v0[1] * sy;
    tri->m_vertices[0].m_w = 0.0f;
    tri->m_vertices[1].m_x = sx * v1[0];
    tri->m_vertices[1].m_y = v1[1] * sy;
    tri->m_vertices[1].m_z = v1[2] * sz;
    tri->m_vertices[1].m_w = 0.0f;
    tri->m_vertices[2].m_x = sx * v2[0];
    tri->m_vertices[2].m_y = v2[1] * sy;
    tri->m_vertices[2].m_z = v2[2] * sz;
    tri->m_vertices[2].m_w = 0.0f;
    return tri;
}

// @ 0x010c8840
uint32_t hkMeshShape::getCollisionFilterInfo(uint32_t key) const
{
    const hkMeshMaterial* m = getMeshMaterial(key);
    if (m != 0)
        return m->m_filterInfo;
    return 0;
}

// Local helper compiled with a register convention (ecx = vertex, eax = scaling, esi = aabb).
// @ 0x010c8860
static void hkMeshShape_includeVertex(const hkTransform& t, const float* vertex, const hkVector4* scaling, hkAabb* aabb)
{
    hkVector4 scaled;
    scaled.m_x = vertex[0] * scaling->m_x;
    scaled.m_y = vertex[1] * scaling->m_y;
    scaled.m_z = vertex[2] * scaling->m_z;
    scaled.m_w = 0.0f;
    hkVector4 p;
    p.setTransformedPos(t, scaled);
    // min part: keep the old value only when strictly less than the new one
    aabb->m_min.m_x = hkMergeMin(aabb->m_min.m_x, p.m_x);
    aabb->m_min.m_y = hkMergeMin(aabb->m_min.m_y, p.m_y);
    aabb->m_min.m_z = hkMergeMin(aabb->m_min.m_z, p.m_z);
    aabb->m_min.m_w = hkMergeMin(aabb->m_min.m_w, p.m_w);
    aabb->m_max.m_x = hkMergeMax(aabb->m_max.m_x, p.m_x);
    aabb->m_max.m_y = hkMergeMax(aabb->m_max.m_y, p.m_y);
    aabb->m_max.m_z = hkMergeMax(aabb->m_max.m_z, p.m_z);
    aabb->m_max.m_w = hkMergeMax(aabb->m_max.m_w, p.m_w);
}

union hkFloatBits { uint32_t u; float f; };

// @ 0x010c8980
void hkMeshShape::getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const
{
    const hkMeshShape* self = this;
    hkFloatBits big, small_;
    big.u = 0x7f7fffeeu;           // 3.40282e+38 (HK_REAL_MAX, not FLT_MAX)
    small_.u = 0xff7fffeeu;        // -3.40282e+38
    out.m_min.m_x = big.f; out.m_min.m_y = big.f; out.m_min.m_z = big.f; out.m_min.m_w = 0.0f;
    out.m_max.m_x = small_.f; out.m_max.m_y = small_.f; out.m_max.m_z = small_.f; out.m_max.m_w = 0.0f;

    for (int s = 0; s < self->m_subparts.m_size; ++s) {
        const hkMeshShapeSubpart* sp = (const hkMeshShapeSubpart*)((const uint8_t*)self->m_subparts.m_data + s * 0x30);
        for (int t = 0; t < sp->m_numTriangles; ++t) {
            const uint8_t* idx = (const uint8_t*)sp->m_indexBase + sp->m_indexStriding * t;
            uint32_t i0, i1, i2;
            if (sp->m_stridingType == 1) {
                i0 = ((const uint16_t*)idx)[0];
                i1 = ((const uint16_t*)idx)[1];
                i2 = ((const uint16_t*)idx)[2];
            } else {
                i0 = ((const uint32_t*)idx)[0];
                i1 = ((const uint32_t*)idx)[1];
                i2 = ((const uint32_t*)idx)[2];
            }
            const uint8_t* vb = (const uint8_t*)sp->m_vertexBase;
            int32_t stride = sp->m_vertexStriding;
            hkMeshShape_includeVertex(localToWorld, (const float*)(vb + i0 * stride), &self->m_scaling, &out);
            hkMeshShape_includeVertex(localToWorld, (const float*)(vb + i1 * stride), &self->m_scaling, &out);
            hkMeshShape_includeVertex(localToWorld, (const float*)(vb + i2 * stride), &self->m_scaling, &out);
        }
    }

    // X87-PRECISION: t = tolerance + radius stays unrounded in st(0) for all eight updates.
    double t = (double)tolerance + (double)self->m_radius;
    out.m_min.m_x = (float)((double)out.m_min.m_x - t);
    out.m_min.m_y = (float)((double)out.m_min.m_y - t);
    out.m_min.m_z = (float)((double)out.m_min.m_z - t);
    out.m_min.m_w = (float)((double)out.m_min.m_w - t);
    out.m_max.m_x = (float)(t + (double)out.m_max.m_x);
    out.m_max.m_y = (float)(t + (double)out.m_max.m_y);
    out.m_max.m_z = (float)(t + (double)out.m_max.m_z);
    out.m_max.m_w = (float)(t + (double)out.m_max.m_w);
}

// @ 0x010c8b00
void hkMeshShape::addSubpart(const hkMeshShapeSubpart& part)
{
    if (m_subparts.m_size == (m_subparts.m_capacityAndFlags & 0x3fffffff))
        hkArrayUtil_reserveMore(&m_subparts, 0x30);
    hkMeshShapeSubpart* dst = &m_subparts.m_data[m_subparts.m_size];
    m_subparts.m_size++;
    *dst = part;                                    // twelve dword copies
    if (dst->m_materialIndexBase == 0) {            // no materials: point at the shared dummy material
        dst->m_numMaterials = 1;
        dst->m_materialBase = &hkMeshShape_defaultMaterial;
        dst->m_materialIndexBase = &hkMeshShape_defaultMaterial;
    }
}

// @ 0x010c8b60
void hkMeshShape::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("MeshShape", 1, this);
    if (m_subparts.m_capacityAndFlags >= 0)
        c->addArray("SubParts", 1, m_subparts.m_data, m_subparts.m_size * 0x30,
                    (m_subparts.m_capacityAndFlags & 0x3fffffff) * 0x30);
    c->endObject();
}

// @ 0x010c8bc0  hkMeshShape(hkFinishLoadedObjectFlag): vptr 0x014a3fe4
hkMeshShape::hkMeshShape(int finishLoadedFlag)
{
    m_referenceCount = 1;
    if (finishLoadedFlag != 0) {
        // upgrade serialized subparts: material index stride type 0 (invalid) becomes 1
        for (int i = 0; i < m_subparts.m_size; ++i) {
            if (m_subparts.m_data[i].m_materialIndexStridingType == 0)
                m_subparts.m_data[i].m_materialIndexStridingType = 1;
        }
    }
}

// @ 0x010c8c10  null-guarded finish-loaded constructor wrapper (cdecl, takes the object)
void hkMeshShape_constructFinishLoaded(hkMeshShape* self)
{
    if (self != 0)
        new (self) hkMeshShape(1);
}

// ---- hkListShape ------------------------------------------------------------------------
struct hkListShapeChildInfo { hkShape* m_shape; uint32_t m_collisionFilterInfo; };

struct hkThreadMemory {
    // @ 0x0107db10
    void deallocateChunk(void* p, int nbytes, int memoryClass);
};
extern unsigned long g_hkThreadMemoryTls;   // 0x016e4174 (hkThreadLocalData<hkThreadMemory*>::s_threadMemoryInstance)

struct hkListShape : hkShape {
    uint32_t m_pad0c;                                 // +0x0c
    hkListShapeChildInfo* m_childInfo;                // +0x10
    int32_t m_numChildren;                            // +0x14
    int32_t m_childCapacityAndFlags;                  // +0x18

    ~hkListShape();
    virtual void getAabb(const hkTransform& t, float tolerance, hkAabb& out) const;
    virtual uint32_t getNextKey(uint32_t oldKey) const;
    virtual uint32_t getCollisionFilterInfo(uint32_t key) const;
    virtual void calcStatistics(hkStatisticsCollector* c) const;
};

// @ 0x010c8c30
void hkListShape::getAabb(const hkTransform& t, float tolerance, hkAabb& out) const
{
    const hkListShape* self = this;
    self->m_childInfo[0].m_shape->getAabb(t, tolerance, out);
    for (int i = 1; i < self->m_numChildren; ++i) {
        hkAabb tmp;
        self->m_childInfo[i].m_shape->getAabb(t, tolerance, tmp);
        out.m_min.m_x = hkMergeMin(out.m_min.m_x, tmp.m_min.m_x);
        out.m_min.m_y = hkMergeMin(out.m_min.m_y, tmp.m_min.m_y);
        out.m_min.m_z = hkMergeMin(out.m_min.m_z, tmp.m_min.m_z);
        out.m_min.m_w = hkMergeMin(out.m_min.m_w, tmp.m_min.m_w);
        out.m_max.m_x = hkMergeMax(out.m_max.m_x, tmp.m_max.m_x);
        out.m_max.m_y = hkMergeMax(out.m_max.m_y, tmp.m_max.m_y);
        out.m_max.m_z = hkMergeMax(out.m_max.m_z, tmp.m_max.m_z);
        out.m_max.m_w = hkMergeMax(out.m_max.m_w, tmp.m_max.m_w);
    }
}

// @ 0x010c8d60  hkListShape::getNextKey (slot 9)
uint32_t hkListShape::getNextKey(uint32_t oldKey) const
{
    const hkListShape* self = this;
    int32_t key = (int32_t)oldKey + 1;
    if (self->m_numChildren <= key)
        key = -1;
    return (uint32_t)key;
}

// @ 0x010c8d90
uint32_t hkListShape::getCollisionFilterInfo(uint32_t key) const
{
    return m_childInfo[key].m_collisionFilterInfo;
}

// @ 0x010c8da0
void hkListShape::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("ListShape", 1, this);
    if (m_childCapacityAndFlags >= 0)
        c->addArray("ChildPtrs", 1, m_childInfo, m_numChildren << 3, (m_childCapacityAndFlags & 0x3fffffff) << 3);
    for (int i = 0; i < m_numChildren; ++i)
        c->addReferencedObject("Child", 1, m_childInfo[i].m_shape);
    c->endObject();
}

// @ 0x010c8e40  (fastcall)
hkListShape::~hkListShape()
{
    for (int i = 0; i < m_numChildren; ++i)
        m_childInfo[i].m_shape->removeReference();
    if (m_childCapacityAndFlags >= 0) {
        hkThreadMemory* mem = (hkThreadMemory*)hkTlsGet(g_hkThreadMemoryTls);
        mem->deallocateChunk(m_childInfo, (m_childCapacityAndFlags & 0x3fffffff) << 3, 0x14);
    }
}

// ---- hkFastMeshShape --------------------------------------------------------------------
// FastMesh keeps its triangles in one float4-vertex, 16-bit-index subpart referenced by +0x24.
struct hkFastMeshShape : hkMeshShape {
    hkFastMeshShape(int finishLoadedFlag);
    virtual const hkShape* getChildShape(uint32_t key, char (&buffer)[512]) const;
};

// @ 0x010c8ee0 (hkFastMeshShape::getChildShape, slot 10)
const hkShape* hkFastMeshShape::getChildShape(uint32_t key, char (&buffer)[512]) const
{
    const hkMeshShape* self = this;
    const hkMeshShapeSubpart* sp = self->m_subparts.m_data;     // *(this+0x24): subpart 0
    int32_t off = sp->m_indexStriding * (int32_t)key;
    const uint8_t* vbase = (const uint8_t*)sp->m_vertexBase;
    int32_t stride = sp->m_vertexStriding;
    const uint8_t* idx = (const uint8_t*)sp->m_indexBase;
    const float* v0 = (const float*)(vbase + (uint32_t)*(const uint16_t*)(idx + off) * stride);
    const float* v1 = (const float*)(vbase + (uint32_t)*(const uint16_t*)(idx + off + 2) * stride);
    const float* v2 = (const float*)(vbase + (uint32_t)*(const uint16_t*)(idx + off + 4) * stride);

    hkTriangleShape* tri = (hkTriangleShape*)buffer;
    if (tri) {
        new (tri) hkTriangleShape;
        tri->m_referenceCount = 1;
        tri->m_userData = 0;
        tri->m_radius = self->m_radius;
    }
    tri->m_vertices[0].m_x = self->m_scaling.m_x * v0[0];
    tri->m_vertices[0].m_y = self->m_scaling.m_y * v0[1];
    tri->m_vertices[0].m_z = self->m_scaling.m_z * v0[2];
    tri->m_vertices[0].m_w = self->m_scaling.m_w * v0[3];
    tri->m_vertices[1].m_x = v1[0] * self->m_scaling.m_x;
    tri->m_vertices[1].m_y = self->m_scaling.m_y * v1[1];
    tri->m_vertices[1].m_z = self->m_scaling.m_z * v1[2];
    tri->m_vertices[1].m_w = self->m_scaling.m_w * v1[3];
    tri->m_vertices[2].m_x = self->m_scaling.m_x * v2[0];
    tri->m_vertices[2].m_y = self->m_scaling.m_y * v2[1];
    tri->m_vertices[2].m_z = self->m_scaling.m_z * v2[2];
    tri->m_vertices[2].m_w = self->m_scaling.m_w * v2[3];
    return tri;
}

// @ 0x010c8fe0  null-guarded finish-loaded ctor of the fast mesh (vptr 0x014a4060)
hkFastMeshShape::hkFastMeshShape(int finishLoadedFlag) : hkMeshShape(1) {}
void hkFastMeshShape_constructFinishLoaded(hkFastMeshShape* self)
{
    if (self != 0)
        new (self) hkFastMeshShape(1);
}

// ---- hkCylinderShape / misc -------------------------------------------------------------
// @ 0x010c9030
void hkCylinderShape_calcStatistics(const void* self, hkStatisticsCollector* c)
{
    c->beginObject("Cylinder", 1, self);
    c->endObject();
}

// @ 0x010c9050
// Probes the FPU rounding behaviour: walks x = 0, 0.01, 0.02 ... until fistp(x) != 0 (the
// first x that rounds to 1, i.e. just above 0.5 under round-to-nearest) and returns x;
// returns 1.0 if nothing rounded up before x reached 1.1.
float hkFpuRoundingProbe()
{
    float x = 0.0f;
    do {
        if (hkFistp(x) != 0)
            return x;
        // X87-PRECISION: fst stores the rounded float, but fcomp compares the unrounded
        // extended sum x + 0.01f against 1.1f (consts @ 0x013eb960, 0x013ef54c).
        double sum = (double)x + (double)0.01f;
        x = (float)sum;
        if (!(sum < (double)1.1f)) break;
    } while (true);
    return 1.0f;                                   // const @ 0x01485720
}
