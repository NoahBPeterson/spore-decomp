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
extern "C" __declspec(dllimport) unsigned long long __cdecl __rdtsc();

extern unsigned long g_hkThreadMemoryTls;    // 0x016e4174
extern unsigned long g_hkMonitorCurrentTls;  // 0x016e42a4
extern unsigned long g_hkMonitorEndTls;      // 0x016e42a8

void* FUN_0107daa0(int nbytes, int cl);   // hkThreadMemory::allocateChunk
void  FUN_0107db10(void* p, int nbytes, int cl); // hkThreadMemory::deallocateChunk

// ---------------------------------------------------------------------------
// math
// ---------------------------------------------------------------------------
struct HK_ALIGN16 hkVector4 { float x, y, z, w; };

struct hkAabb { hkVector4 m_min; hkVector4 m_max; };
struct hkTransform { hkVector4 m_rot[3]; hkVector4 m_trans; };
struct hkSphere { hkVector4 m_pos; };          // radius lives in .w in this build
struct hkCdVertex { hkVector4 m_pos; };

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
struct hkArray
{
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
struct hkStatisticsCollector
{
    virtual void s0();
    virtual void beginObject(const char* name, int mode, const void* obj);              // +4
    virtual void addArray(const char* name, int elemSize, const void* ptr, int used, int alloc); // +8
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void endObject();                                                           // +0x18
};

struct hkReferencedObject
{
    virtual ~hkReferencedObject();
    virtual void calcStatistics(hkStatisticsCollector* c) const;
    hkInt16 m_memSizeAndFlags;   // +4
    hkInt16 m_referenceCount;    // +6
};

struct hkShape : hkReferencedObject
{
    int m_userData;              // +8
    virtual int getType() const;
    virtual void getAabb(const hkTransform& t, float tol, hkAabb& out) const;
    virtual float getMaximumProjection(const hkVector4& dir) const;
    virtual void castRay(const void* input, void* output) const;
};
struct hkSphereRepShape : hkShape {};
struct hkConvexShape : hkSphereRepShape { float m_radius; };  // +0xc

struct FourVectors { hkVector4 m_x, m_y, m_z; };

struct hkConvexVerticesShape : hkConvexShape
{
    hkVector4 m_aabbHalfExtents;              // +0x10
    hkVector4 m_aabbCenter;                   // +0x20
    hkArray<FourVectors> m_rotatedVertices;   // +0x30
    int m_numVertices;                        // +0x3c
    hkArray<hkVector4> m_planeEquations;      // +0x40

    void copyVertexData(const float* data, int stride, int numVertices);
    void f1fe0(const void* a, int stride, int numVertices, const hkArray<hkVector4>* src);
    void getAabb(const hkTransform& t, float tol, hkAabb& out) const;
    void castRay(const void* input, void* output) const;
    void calcStatistics(hkStatisticsCollector* c) const;
    ~hkConvexVerticesShape();
};

struct hkCapsuleShape : hkConvexShape
{
    hkVector4 m_vertexA;   // +0x10
    hkVector4 m_vertexB;   // +0x20

    hkCapsuleShape(const hkVector4& a, const hkVector4& b, float radius);
    void getSupportingVertex(const hkVector4& dir, hkCdVertex& out) const;
    void getFirstVertex(hkVector4& out) const;
    const hkSphere* getCollisionSpheres(hkSphere* buffer) const;
    void calcStatistics(hkStatisticsCollector* c) const;
};

struct hkCdBody
{
    const hkShape* m_shape;   // +0
    hkUint32 m_shapeKey;      // +4
    const void* m_motion;     // +8
    const hkCdBody* m_parent; // +0xc
};

struct hkCdPoint { hkUint32 m[12]; };
struct hkAllCdPointCollector
{
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
void FUN_010ccbc0(void*, char);
void FUN_010e7d70(void*);
void FUN_010e7ce0(void*);
void FUN_010e6a70(void*);
void FUN_010e5540(void*);
void FUN_010e1c70(void*);
void FUN_010ceee0(void*);
void FUN_010e1720(void*);
void FUN_010e1510(void*);
void FUN_010e0500(void*);
void FUN_010df500(void*);
void FUN_010df2c0(void*);
void FUN_010de080(void*);
void FUN_010cef70(void*);
void FUN_010dcfc0(void*);
void FUN_010d9f10(void*);
void FUN_01100cf0(void*, int, int);
void FUN_010ff6d0(void*);
void FUN_010d9e50(void*);
void FUN_010fdec0(void*);
void FUN_010d92a0(void*);
void FUN_010d8940(void*);
void FUN_010d75f0(void*);
void FUN_010d64a0(void*);
void FUN_010d5320(void*);
void FUN_010d41f0(void*);
void FUN_010fda70(void*);
void FUN_010d2730(void*);
void FUN_010cff70(void*);
void FUN_010cf000(void*);

// ===========================================================================
// @ 0x010c19a0  hkConvexVerticesShape::copyVertexData
void hkConvexVerticesShape::copyVertexData(const float* data, int stride, int numVertices)
{
    m_numVertices = numVertices;
    int n4 = (numVertices + 3) & ~3;
    int blocks = n4 >> 2;
    if (m_rotatedVertices.getCapacity() < blocks)
    {
        int c = m_rotatedVertices.getCapacity() * 2;
        if (c <= blocks) c = blocks;
        hkArrayUtil::_reserveExactly(&m_rotatedVertices, c, 0x30);
    }
    FourVectors* fv = m_rotatedVertices.m_data;
    const char* p = (const char*)data;
    for (int i = 0; i < numVertices; ++i)
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
    for (int i = numVertices; i < n4; ++i)
    {
        int b = i >> 2;
        int l = i & 3;
        float* base = (float*)&fv[b];
        base[0 + l] = *(const float*)(last + 0);
        base[4 + l] = *(const float*)(last + 4);
        base[8 + l] = *(const float*)(last + 8);
    }
    m_rotatedVertices.m_size = n4 >> 2;

    hkAabb aabb;
    hkAabbUtil::calcAabb(data, numVertices, stride, aabb);
    m_aabbCenter.x = (aabb.m_min.x + aabb.m_max.x) * 0.5f;
    m_aabbCenter.y = (aabb.m_min.y + aabb.m_max.y) * 0.5f;
    m_aabbCenter.z = (aabb.m_min.z + aabb.m_max.z) * 0.5f;
    m_aabbCenter.w = (aabb.m_min.w + aabb.m_max.w) * 0.5f;
    m_aabbHalfExtents.x = (aabb.m_max.x - aabb.m_min.x) * 0.5f;
    m_aabbHalfExtents.y = (aabb.m_max.y - aabb.m_min.y) * 0.5f;
    m_aabbHalfExtents.z = (aabb.m_max.z - aabb.m_min.z) * 0.5f;
    m_aabbHalfExtents.w = (aabb.m_max.w - aabb.m_min.w) * 0.5f;
}

// @ 0x010c1c60  hkConvexVerticesShape::getAabb
void hkConvexVerticesShape::getAabb(const hkTransform& t, float tol, hkAabb& out) const
{
    hkAabbUtil::calcAabb(t, m_aabbHalfExtents, m_aabbCenter, tol + m_radius, out);
}

// @ 0x010c1c90  hkConvexVerticesShape::castRay (monitor-stream timers omitted)
void hkConvexVerticesShape::castRay(const void* input_, void* output_) const
{
    const hkVector4& input = *(const hkVector4*)input_;
    hkVector4* output = (hkVector4*)output_;
    float bestFraction = output->w;
    float bestProjected = -1.0f;
    hkVector4 bestPoint(*(hkVector4*)output);
    int i = m_numVertices - 1;
    const hkVector4* planes = m_planeEquations.m_data;
    if (i >= 0)
    {
        do
        {
            const hkVector4& pl = planes[i];
            float d0 = pl.x * input.x + pl.y * input.y + pl.z * input.z + pl.w;
            float d1 = pl.x * ((const float*)input_)[4] + pl.y * ((const float*)input_)[5]
                     + pl.z * ((const float*)input_)[6] + pl.w;
            if (d0 < 0.0f)
            {
                if (d1 >= 0.0f)
                {
                    float f = d0 / (d0 - d1);
                    if (bestFraction < f) { bestProjected = bestPoint.w; }
                    else { bestPoint = pl; bestProjected = f; }
                }
            }
            else if (d1 < 0.0f)
            {
                float f = d0 / (d0 - d1);
                if (bestProjected < f) { bestProjected = f; }
                else { bestPoint = pl; bestProjected = f; }
            }
            --i;
        } while (i >= 0);
    }
    if (bestProjected >= 0.0f)
    {
        output->x = bestPoint.x; output->y = bestPoint.y; output->z = bestPoint.z;
        output->w = bestProjected;
        *((hkUint32*)output + 4) = 0xffffffff;
    }
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

// @ 0x010c2230  hkConvexVerticesShape assignment from an hkGeometry-like source
void FUN_010c2230(void* self, const void* src_)
{
    const hkUint32* src = (const hkUint32*)src_;
    char* s = (char*)self;
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
void FUN_010c25a0(void* mgr)
{
    FUN_010e7d70(mgr);
    FUN_010e7ce0(mgr);
    FUN_010e6a70(mgr);
    FUN_010ccbc0(mgr, 0);
    FUN_010e5540(mgr);
    FUN_010e1c70(mgr);
    FUN_010ceee0(mgr);
    FUN_010e1720(mgr);
    FUN_010ccbc0(mgr, 1);
    FUN_010ccbc0(mgr, 0);
    FUN_010e1510(mgr);
    FUN_010ccbc0(mgr, 1);
    FUN_010e0500(mgr);
    FUN_010df500(mgr);
    FUN_010ccbc0(mgr, 0);
    FUN_010df2c0(mgr);
    FUN_010ccbc0(mgr, 1);
    FUN_010de080(mgr);
    FUN_010cef70(mgr);
    FUN_010dcfc0(mgr);
    FUN_010d9f10(mgr);
    FUN_01100cf0(mgr, 1, 1);
    FUN_010ff6d0(mgr);
    FUN_010d9e50(mgr);
    FUN_010fdec0(mgr);
    FUN_010d92a0(mgr);
    FUN_010d8940(mgr);
    FUN_010d75f0(mgr);
    FUN_01100cf0(mgr, 6, 4);
    FUN_01100cf0(mgr, 4, 6);
    FUN_010d64a0(mgr);
    FUN_010d5320(mgr);
    FUN_010d41f0(mgr);
    FUN_010fda70(mgr);
    FUN_010d2730(mgr);
    FUN_010cff70(mgr);
    FUN_010cf000(mgr);
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
    m_radius = radius;
    m_memSizeAndFlags = 1;
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
    float d = (m_vertexB.x - m_vertexA.x) * dir.x
            + (m_vertexB.y - m_vertexA.y) * dir.y
            + (m_vertexB.z - m_vertexA.z) * dir.z;
    if (d < 0.0f)
    {
        out.m_pos = m_vertexA;
        out.m_pos.w = 0.5f;
    }
    else
    {
        out.m_pos = m_vertexB;
        out.m_pos.w = 0.5f;
        *(hkUint32*)&out.m_pos.w |= 0x10;
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
