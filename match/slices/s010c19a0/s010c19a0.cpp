// Slice s010c19a0 -- Havok 3.1.0 hkConvexVerticesShape / hkCapsuleShape and collision helpers.
//
// Region is /O2 /MD with /arch:SSE (scalar movss for hkVector4 copies, x87 for the
// plane/vertex arithmetic). Member offsets come from the dev PDB (tools/pdb_type.py)
// and were confirmed against the disassembly.
#include "types.h"

typedef int hkInt32;
typedef unsigned int hkUint32;
typedef short hkInt16;

#define HK_ALIGN16 __declspec(align(16))

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
#include <intrin.h>

extern unsigned long g_hkThreadMemoryTls;    // 0x016e4174
extern unsigned long g_hkMonitorCurrentTls;  // 0x016e42a4
extern unsigned long g_hkMonitorEndTls;      // 0x016e42a8

void* FUN_0107daa0(int nbytes, int cl);   // hkThreadMemory::allocateChunk
void  FUN_0107db10(void* p, int nbytes, int cl); // hkThreadMemory::deallocateChunk

// ---------------------------------------------------------------------------
// math
// ---------------------------------------------------------------------------
struct HK_ALIGN16 hkVector4 { float x, y, z, w; };

class hkAabb { public: hkVector4 m_min; hkVector4 m_max; };
class hkTransform { public: hkVector4 m_rot[3]; hkVector4 m_trans; };
class hkSphere { public: hkVector4 m_pos; };          // radius lives in .w in this build
class hkCdVertex { public: hkVector4 m_pos; };

struct hkAabbUtil
{
    static void calcAabb(const hkTransform& t, const hkVector4& halfExtents,
                         const hkVector4& center, float tol, hkAabb& out);   // 0x010c16b0
    static void calcAabb(const float* verts, int numVerts, int stride, hkAabb& out); // 0x010cd8e0
};

// ---------------------------------------------------------------------------
// memory / arrays
// ---------------------------------------------------------------------------
#define HK_ARRAY_CAPACITY_MASK 0x3fffffff
struct hkArrayUtil
{
    static void _reserveMore(void* arrayBase, int elemSize);                          // 0x0107f530
    static void _reserveExactly(void* arrayBase, int numElem, int elemSize);          // 0x0107f4a0
};

template <typename T>
class hkArray
{ public:
    T* m_data;
    int m_size;
    int m_capacityAndFlags;

    int getCapacity() const { return m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK; }
    void setSize(int n)
    {
        if (getCapacity() < n)
        {
            int c = getCapacity() * 2;
            if (c <= n) c = n;
            hkArrayUtil::_reserveExactly(this, c, (int)sizeof(T));
        }
        m_size = n;
    }
    void pushBack(const T& t)
    {
        if (m_size == getCapacity())
            hkArrayUtil::_reserveMore(this, (int)sizeof(T));
        m_data[m_size] = t;
        m_size = m_size + 1;
    }
};

// ---------------------------------------------------------------------------
// referenced objects / shapes
// ---------------------------------------------------------------------------
class hkStatisticsCollector
{ public:
    virtual void s0();
    virtual void beginObject(const char* name, int mode, const void* obj);              // +4
    virtual void addArray(const char* name, int elemSize, const void* ptr, int used, int alloc); // +8
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void endObject();                                                           // +0x18
};

class hkReferencedObject
{ public:
    virtual ~hkReferencedObject(); // 0x013ef094
    virtual void calcStatistics(hkStatisticsCollector* c) const;
    hkInt16 m_memSizeAndFlags;   // +4
    hkInt16 m_referenceCount;    // +6
};

class hkShape : public hkReferencedObject { public:
    int m_userData;              // +8
    virtual int getType() const;
    virtual void getAabb(const hkTransform& t, float tol, hkAabb& out) const;
    virtual float getMaximumProjection(const hkVector4& dir) const;
    virtual void castRay(const void* input, void* output) const;
};
class hkSphereRepShape : public hkShape { public:};
class hkConvexShape : public hkSphereRepShape { public: float m_radius; };  // +0xc

struct FourVectors { hkVector4 m_x, m_y, m_z; };

class hkConvexVerticesShape : public hkConvexShape { public:
    hkVector4 m_aabbHalfExtents;              // +0x10
    hkVector4 m_aabbCenter;                   // +0x20
    hkArray<FourVectors> m_rotatedVertices;   // +0x30
    int m_numVertices;                        // +0x3c
    hkArray<hkVector4> m_planeEquations;      // +0x40

    void copyVertexData(const float* data, int stride, int numVertices);
    void f1fe0(const void* a, int stride, int numVertices, const hkArray<hkVector4>* src);
    void getAabb(const hkTransform& t, float tol, hkAabb& out) const;
    // (hkBool ret = hidden first pointer, hkShapeRayCastInput const&, hkShapeRayCastOutput&): ret 0xc
    void castRay(unsigned char* hitOut, const void* input, void* output) const;
    void calcStatistics(hkStatisticsCollector* c) const;
    ~hkConvexVerticesShape();
};

class hkCapsuleShape : public hkConvexShape { public:
    hkVector4 m_vertexA;   // +0x10
    hkVector4 m_vertexB;   // +0x20

    hkCapsuleShape(const hkVector4& a, const hkVector4& b, float radius);
    void getSupportingVertex(const hkVector4& dir, hkCdVertex& out) const;
    void getFirstVertex(hkVector4& out) const;
    const hkSphere* getCollisionSpheres(hkSphere* buffer) const;
    void calcStatistics(hkStatisticsCollector* c) const;
};

class hkCdBody
{ public:
    const hkShape* m_shape;   // +0
    hkUint32 m_shapeKey;      // +4
    const void* m_motion;     // +8
    const hkCdBody* m_parent; // +0xc
};

struct hkCdPoint { hkUint32 m[12]; };
class hkAllCdPointCollector
{ public:
    virtual void addCdPoint(const hkCdPoint& p);   // slot +?
    char pad[0x10 - 4];
    hkArray<hkCdPoint> m_points;                   // +0x10
    void sortPoints();
};

struct hkRootCdPoint { hkUint32 m[12]; };
struct hkAlgorithm
{
    struct lessRootCdPoint
    {
        char pad;
        bool operator()(const hkRootCdPoint& a, const hkRootCdPoint& b) const
        { return *(const float*)((const char*)&a + 0x1c) < *(const float*)((const char*)&b + 0x1c); }
    };
    template <typename T, typename L>
    static void quickSortRecursive(T* base, int lo, int hi, L less);
};

// ---------------------------------------------------------------------------
// external registration / misc helpers
// ---------------------------------------------------------------------------
void FUN_0107f4a0(void*, int, int);
void FUN_0107f530(void*, int);
void FUN_010cd8e0(const void*, int, int, void*);

// hkAgentRegisterUtil::registerAllAgents fan-out.  Every helper takes the dispatcher
// in ecx (__thiscall) and pops only its real stack arguments -- the ones that forward
// the dispatcher to hkCollisionDispatcher::registerAgentFuncs do it straight from ecx,
// so they are declared as (unused) members instead of one-argument cdecl functions.
struct hkCollisionDispatcherOps
{
    void setFlag(char v);                       // 0x010ccbc0
    void registerAlternateShapeTypes();         // 0x010e7d70
    void reg010e7ce0();                         // 0x010e7ce0
    void reg010e6a70();                         // 0x010e6a70
    void reg010e5540();                         // 0x010e5540
    void reg010e1c70();                         // 0x010e1c70
    void reg010ceee0();                         // 0x010ceee0
    void reg010e1720();                         // 0x010e1720
    void reg010e1510();                         // 0x010e1510
    void reg010e0500();                         // 0x010e0500
    void reg010df500();                         // 0x010df500
    void reg010df2c0();                         // 0x010df2c0
    void reg010de080();                         // 0x010de080
    void reg010cef70();                         // 0x010cef70
    void reg010dcfc0();                         // 0x010dcfc0
    void reg010d9f10();                         // 0x010d9f10
    void registerAgentFuncs(int, int);          // 0x01100cf0
    void reg010ff6d0();                         // 0x010ff6d0
    void reg010d9e50();                         // 0x010d9e50
    void reg010fdec0();                         // 0x010fdec0
    void reg010d92a0();                         // 0x010d92a0
    void reg010d8940();                         // 0x010d8940
    void reg010d75f0();                         // 0x010d75f0
    void reg010d64a0();                         // 0x010d64a0
    void reg010d5320();                         // 0x010d5320
    void reg010d41f0();                         // 0x010d41f0
    void reg010fda70();                         // 0x010fda70
    void reg010d2730();                         // 0x010d2730
    void reg010cff70();                         // 0x010cff70
    void reg010cf000();                         // 0x010cf000
};

// ===========================================================================
// @ 0x010c19a0  hkConvexVerticesShape::copyVertexData
void hkConvexVerticesShape::copyVertexData(const float* data, int stride, int numVertices)
{
    m_numVertices = numVertices;
    int n4 = (numVertices + 3) & ~3;
    int blocks = n4 / 4;               // signed division truncates toward zero, like the original
    if (m_rotatedVertices.getCapacity() < blocks)
    {
        int c = m_rotatedVertices.getCapacity() * 2;
        if (c <= blocks) c = blocks;
        hkArrayUtil::_reserveExactly(&m_rotatedVertices, c, 0x30);
    }
    FourVectors* fv = m_rotatedVertices.m_data;
    const char* p = (const char*)data;
    m_rotatedVertices.m_size = blocks;
    int i = 0;
    for (; i < numVertices; ++i)
    {
        int b = i >> 2;
        int l = i & 3;
        float* base = (float*)&fv[b];
        base[0 + l] = *(const float*)(p + 0);
        base[4 + l] = *(const float*)(p + 4);
        base[8 + l] = *(const float*)(p + 8);
        p += stride;
    }
    const char* last = p - stride;
    for (; i < n4; ++i)
    {
        int b = i >> 2;
        int l = i & 3;
        float* base = (float*)&fv[b];
        base[0 + l] = *(const float*)(last + 0);
        base[4 + l] = *(const float*)(last + 4);
        base[8 + l] = *(const float*)(last + 8);
    }

    hkAabb aabb;
    hkAabbUtil::calcAabb(data, numVertices, stride, aabb);
    // the original rounds each sum/difference to float (a member store) before scaling by 0.5f;
    // cl71 keeps x87 intermediates otherwise, so the temp is volatile to force the float store
    volatile float s;
    s = aabb.m_min.x + aabb.m_max.x;  m_aabbCenter.x = s * 0.5f;
    s = aabb.m_min.y + aabb.m_max.y;  m_aabbCenter.y = s * 0.5f;
    s = aabb.m_min.z + aabb.m_max.z;  m_aabbCenter.z = s * 0.5f;
    s = aabb.m_min.w + aabb.m_max.w;  m_aabbCenter.w = s * 0.5f;
    s = aabb.m_max.x - aabb.m_min.x;  m_aabbHalfExtents.x = s * 0.5f;
    s = aabb.m_max.y - aabb.m_min.y;  m_aabbHalfExtents.y = s * 0.5f;
    s = aabb.m_max.z - aabb.m_min.z;  m_aabbHalfExtents.z = s * 0.5f;
    s = aabb.m_max.w - aabb.m_min.w;  m_aabbHalfExtents.w = s * 0.5f;
}

// @ 0x010c1c60  hkConvexVerticesShape::getAabb
void hkConvexVerticesShape::getAabb(const hkTransform& t, float tol, hkAabb& out) const
{
    hkAabbUtil::calcAabb(t, m_aabbHalfExtents, m_aabbCenter, tol + m_radius, out);
}

// shape ray cast output: point/normal (0x00), material (0x10), fraction (0x14)
struct hkShapeRayCastOut { hkVector4 m_vec; hkUint32 m_material; float m_fraction; };

// hkMonitorStream timer split (12-byte entry: name, time; the third dword is left untouched)
struct hkTimerEntry { const char* m_name; hkUint32 m_time; hkUint32 m_pad; };
static inline void hkTimerSplit(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorEndTls);
    void* cur = TlsGetValue(g_hkMonitorCurrentTls);
    if ((unsigned)cur < (unsigned)end)
    {
        hkTimerEntry* p = (hkTimerEntry*)TlsGetValue(g_hkMonitorCurrentTls);
        p->m_name = name;
        p->m_time = (hkUint32)__rdtsc();
        TlsSetValue(g_hkMonitorCurrentTls, p + 1);
    }
}

// @ 0x010c1c90  hkConvexVerticesShape::castRay (monitor-stream timers omitted)
void hkConvexVerticesShape::castRay(unsigned char* hitOut, const void* input_, void* output_) const
{
    hkTimerSplit((const char*)0x14a27e0);      // "TtrcConvexVert"
    const hkVector4& origin = *(const hkVector4*)input_;
    const hkVector4& dir = *((const hkVector4*)input_ + 1);
    hkShapeRayCastOut* out = (hkShapeRayCastOut*)output_;
    float reference = out->m_fraction;         // local_28: the caller's fraction, never written back
    float fraction = -1.0f;                    // local_2c
    hkVector4 point;                           // local_20..0x2c
    int i = m_planeEquations.m_size - 1;
    const hkVector4* planes = m_planeEquations.m_data;
    for (; i >= 0; --i)
    {
        const hkVector4& pl = planes[i];
        float d0 = pl.x * origin.x + pl.y * origin.y + pl.z * origin.z + pl.w;
        float d1 = pl.x * dir.x + pl.y * dir.y + pl.z * dir.z + pl.w;
        if (d0 < 0.0f)
        {
            if (d1 < 0.0f)
            {
                continue;                      // both ends inside: no crossing on this plane
            }
            float f = d0 / (d0 - d1);
            if (!(reference < f)) reference = f;
        }
        else
        {
            if (d1 >= 0.0f)
            {
                hkTimerSplit((const char*)0x149cc34);   // "Et"
                *hitOut = 0;
                return;
            }
            float f = d0 / (d0 - d1);
            if (fraction < f) { fraction = f; point = pl; }
        }
        if (reference < fraction)
        {
            hkTimerSplit((const char*)0x149cc34);       // "Et"
            *hitOut = 0;
            return;
        }
    }
    if (!(fraction < 0.0f))
    {
        out->m_vec = point;
        out->m_material = 0xffffffff;
        out->m_fraction = fraction;
        hkTimerSplit((const char*)0x149cc34);           // "Et"
        *hitOut = 1;
        return;
    }
    hkTimerSplit((const char*)0x149cc34);               // "Et"
    *hitOut = 0;
}

// @ 0x010c1f40  hkConvexVerticesShape::calcStatistics
void hkConvexVerticesShape::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("CvxVerts", 1, this);
    if ((int)((hkUint32)m_rotatedVertices.m_capacityAndFlags) >= 0)
    {
        c->addArray("Verts", 1, m_rotatedVertices.m_data, m_rotatedVertices.m_size * 0x30,
                    m_rotatedVertices.getCapacity() * 0x30);
    }
    if ((int)((hkUint32)m_planeEquations.m_capacityAndFlags) >= 0)
    {
        c->addArray("Verts", 1, m_planeEquations.m_data, m_planeEquations.m_size << 4,
                    m_planeEquations.m_capacityAndFlags << 4);
    }
    c->endObject();
}

// @ 0x010c1fe0  hkConvexVerticesShape constructor from an hkConvexVerticesShape-like source
void hkConvexVerticesShape::f1fe0(const void* a, int stride, int numVertices, const hkArray<hkVector4>* src)
{
    m_numVertices = 0;
    m_memSizeAndFlags = 1;
    m_userData = 0;
    *(void**)this = (void*)0x14a2804;
    m_rotatedVertices.m_data = 0; m_rotatedVertices.m_size = 0;
    m_rotatedVertices.m_capacityAndFlags = (int)0x80000000;
    m_planeEquations.m_data = 0; m_planeEquations.m_size = 0;
    m_planeEquations.m_capacityAndFlags = (int)0x80000000;
    if (src->m_size > 0)
    {
        m_planeEquations.m_data = (hkVector4*)FUN_0107daa0(src->m_size << 4, 0x14);
        m_planeEquations.m_capacityAndFlags = (m_planeEquations.m_capacityAndFlags & 0x40000000) | src->m_size;
    }
    m_planeEquations.m_size = src->m_size;
    copyVertexData((const float*)a, stride, numVertices);
}

// @ 0x010c21c0  hkConvexVerticesShape::~hkConvexVerticesShape
hkConvexVerticesShape::~hkConvexVerticesShape()
{
    if ((int)((hkUint32)m_planeEquations.m_capacityAndFlags) >= 0)
    {
        FUN_0107db10(m_planeEquations.m_data, m_planeEquations.getCapacity() << 4, 0x14);
    }
    if ((int)((hkUint32)m_rotatedVertices.m_capacityAndFlags) >= 0)
    {
        FUN_0107db10(m_rotatedVertices.m_data, m_rotatedVertices.getCapacity() * 0x30, 0x14);
    }
    *(void**)this = (void*)0x13ef094;
}

struct hkConvexVerticesShapeAssign { void assign(const void* src_); };

// @ 0x010c2230  hkConvexVerticesShape assignment from an hkGeometry-like source
void hkConvexVerticesShapeAssign::assign(const void* src_)
{
    const hkUint32* src = (const hkUint32*)src_;
    char* s = (char*)this;
    if (*(void**)(s + 0x30) == 0 || *(const float*)((const char*)src + 0x1c) < *(float*)(s + 0x2c))
    {
        *(hkUint32*)(s + 0x10) = src[0];
        *(hkUint32*)(s + 0x14) = src[1];
        *(hkUint32*)(s + 0x18) = src[2];
        *(hkUint32*)(s + 0x1c) = src[3];
        *(hkUint32*)(s + 0x20) = src[4];
        *(hkUint32*)(s + 0x24) = src[5];
        *(hkUint32*)(s + 0x28) = src[6];
        *(hkUint32*)(s + 0x2c) = src[7];
        hkUint32 v = src[8];
        for (hkUint32 c = *(hkUint32*)(v + 0xc); c != 0; c = *(hkUint32*)(c + 0xc)) v = c;
        *(hkUint32*)(s + 0x30) = v;
        *(hkUint32*)(s + 0x34) = *(hkUint32*)(src[8] + 4);
        hkUint32 w = src[9];
        for (hkUint32 c = *(hkUint32*)(w + 0xc); c != 0; c = *(hkUint32*)(c + 0xc)) w = c;
        *(hkUint32*)(s + 0x38) = w;
        *(hkUint32*)(s + 0x3c) = *(hkUint32*)(src[9] + 4);
        *(hkUint32*)(s + 4) = src[7];
    }
}

// @ 0x010c2310  hkAllCdPointCollector::addCdPoint
void hkAllCdPointCollector::addCdPoint(const hkCdPoint& p)
{
    m_points.pushBack(p);
    hkCdPoint& out = m_points.m_data[m_points.m_size - 1];
    hkUint32 v = p.m[8];
    for (hkUint32 c = *(hkUint32*)(v + 0xc); c != 0; c = *(hkUint32*)(c + 0xc)) v = c;
    out.m[8] = v;
    out.m[9] = *(hkUint32*)(p.m[8] + 4);
    hkUint32 w = p.m[9];
    for (hkUint32 c = *(hkUint32*)(w + 0xc); c != 0; c = *(hkUint32*)(c + 0xc)) w = c;
    out.m[10] = w;
    out.m[11] = *(hkUint32*)(p.m[9] + 4);
}

// @ 0x010c23c0  hkAlgorithm::quickSortRecursive<hkRootCdPoint, less>
template <typename T, typename L>
void hkAlgorithm::quickSortRecursive(T* base, int lo, int hi, L less)
{
    while (lo < hi)
    {
        const float pivot = *(const float*)((const char*)&base[(lo + hi) >> 1] + 0x1c);
        int i = lo, j = hi;
        do
        {
            while (*(const float*)((const char*)&base[i] + 0x1c) < pivot) ++i;
            while (pivot < *(const float*)((const char*)&base[j] + 0x1c)) --j;
            if (j < i) break;
            if (i != j)
            {
                T tmp = base[i];
                base[i] = base[j];
                base[j] = tmp;
            }
            ++i; --j;
        } while (i <= j);
        if (lo < j) quickSortRecursive(base, lo, j, less);
        lo = i;
    }
}
template void hkAlgorithm::quickSortRecursive<hkRootCdPoint, hkAlgorithm::lessRootCdPoint>(
    hkRootCdPoint*, int, int, hkAlgorithm::lessRootCdPoint);

// @ 0x010c2570  hkAllCdPointCollector::sortPoints
void hkAllCdPointCollector::sortPoints()
{
    if (m_points.m_size > 1)
    {
        hkAlgorithm::lessRootCdPoint less;
        hkAlgorithm::quickSortRecursive<hkRootCdPoint, hkAlgorithm::lessRootCdPoint>(
            (hkRootCdPoint*)m_points.m_data, 0, m_points.m_size - 1, less);
    }
}

// @ 0x010c25a0  register all collision agents
void FUN_010c25a0(void* mgr_)
{
    hkCollisionDispatcherOps* mgr = (hkCollisionDispatcherOps*)mgr_;
    mgr->registerAlternateShapeTypes();
    mgr->reg010e7ce0();
    mgr->reg010e6a70();
    mgr->setFlag(0);
    mgr->reg010e5540();
    mgr->reg010e1c70();
    mgr->reg010ceee0();
    mgr->reg010e1720();
    mgr->setFlag(1);
    mgr->setFlag(0);
    mgr->reg010e1510();
    mgr->setFlag(1);
    mgr->reg010e0500();
    mgr->reg010df500();
    mgr->setFlag(0);
    mgr->reg010df2c0();
    mgr->setFlag(1);
    mgr->reg010de080();
    mgr->reg010cef70();
    mgr->reg010dcfc0();
    mgr->reg010d9f10();
    mgr->registerAgentFuncs(1, 1);
    mgr->reg010ff6d0();
    mgr->reg010d9e50();
    mgr->reg010fdec0();
    mgr->reg010d92a0();
    mgr->reg010d8940();
    mgr->reg010d75f0();
    mgr->registerAgentFuncs(6, 4);
    mgr->registerAgentFuncs(4, 6);
    mgr->reg010d64a0();
    mgr->reg010d5320();
    mgr->reg010d41f0();
    mgr->reg010fda70();
    mgr->reg010d2730();
    mgr->reg010cff70();
    mgr->reg010cf000();
}

// @ 0x010c26f0  hkCapsuleShape::calcStatistics
void hkCapsuleShape::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("CapsuleShape", 1, this);
    c->endObject();
}

// @ 0x010c2730  hkCapsuleShape::hkCapsuleShape
hkCapsuleShape::hkCapsuleShape(const hkVector4& a, const hkVector4& b, float radius)
{
    // the original only writes the reference-count halfword at +6 (memSizeAndFlags at +4 is left alone)
    m_radius = radius;
    m_referenceCount = 1;
    m_userData = 0;
    *(void**)this = (void*)0x14a2888;
    m_vertexA = a;
    m_vertexB = b;
    m_vertexA.w = radius;
    m_vertexB.w = radius;
}

// @ 0x010c27a0  hkCapsuleShape::getSupportingVertex
void hkCapsuleShape::getSupportingVertex(const hkVector4& dir, hkCdVertex& out) const
{
    // the original groups the y/z products inside the x term (x87 evaluation order)
    float d = (m_vertexB.x - m_vertexA.x) * dir.x
            + ((m_vertexB.y - m_vertexA.y) * dir.y
             + (m_vertexB.z - m_vertexA.z) * dir.z);
    // both branches copy a vertex and then store the raw w word (0.5f, and 0.5f | 0x10 for B)
    if (d < 0.0f)
    {
        out.m_pos = m_vertexA;
        *(hkUint32*)&out.m_pos.w = 0x3f000000;
    }
    else
    {
        out.m_pos = m_vertexB;
        *(hkUint32*)&out.m_pos.w = 0x3f000010;
    }
}

// @ 0x010c2830  hkCapsuleShape::getFirstVertex
void hkCapsuleShape::getFirstVertex(hkVector4& out) const
{
    out = m_vertexB;
}

// @ 0x010c2850  hkCapsuleShape::getCollisionSpheres
const hkSphere* hkCapsuleShape::getCollisionSpheres(hkSphere* buffer) const
{
    buffer[0].m_pos = m_vertexA;
    buffer[1].m_pos = m_vertexB;
    return buffer;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct hkReferencedObject {
    ~hkReferencedObject(); // 0x013ef094
};
}
