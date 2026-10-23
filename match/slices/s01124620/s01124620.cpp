// Slice s01124620 (Havok 3.1.0 inertia tensor computer).
//
//   0x01124620  InternalInertiaTensorComputer::compFaceIntegrals
//   0x01124820  InternalInertiaTensorComputer::computeInertialTensorInternal
//   0x01124930  InternalInertiaTensorComputer::init
//   0x011249c0  hkInertiaTensorComputer::combineMassProperties
//   0x01124c40  InternalInertiaTensorComputer::compVolumeIntegrals
//   0x01125000  InternalInertiaTensorComputer::compShift
//   0x011251e0  hkInertiaTensorComputer::computeGeometryVolumeMassProperties
//   0x011252d0  hkInertiaTensorComputer::computeVertexHullVolumeMassProperties
//
// Compile flags: /vc71 /O2 /MD /Gy /TP   (Havok 3.1.0, cl 13.10.3077)

#include <math.h>

typedef float hkReal;

enum hkResult
{
    HK_SUCCESS = 0,
    HK_FAILURE = 1
};

// HK_REAL_MAX in this build is 3.40282e+38f == 0x7f7fffee (not FLT_MAX).
#define HK_REAL_MAX 3.40282e+38f

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016e4174

class hkThreadMemory
{
public:
    void deallocateChunk(void* p, int numBytes, int memoryClass);   // 0x0107db10
};

class __declspec(align(16)) hkVector4
{
public:
    hkReal x, y, z, w;

    hkVector4() {}
    hkVector4(const hkVector4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}

    void setTransformedPos(const class hkTransform& t, const hkVector4& v);   // 0x01081360
};

class __declspec(align(16)) hkMatrix3
{
public:
    hkVector4 m_col0;
    hkVector4 m_col1;
    hkVector4 m_col2;

    void changeBasis(const class hkRotation& r);   // 0x01082130
    void add(const hkMatrix3& m);                  // 0x01081ad0
    hkMatrix3& operator=(const hkMatrix3& m);      // 0x0044a8c0
};

class hkRotation : public hkMatrix3
{
};

class hkTransform
{
public:
    hkRotation m_rotation;
    hkVector4 m_translation;
};

struct hkMassProperties
{
    hkReal m_volume;          // +0x00
    hkReal m_mass;            // +0x04
    hkVector4 m_centerOfMass; // +0x10
    hkMatrix3 m_inertiaTensor;// +0x20
};

struct hkMassElement
{
    hkMassProperties m_properties;   // +0x00
    hkTransform m_transform;         // +0x50
};

class hkArrayUtil
{
public:
    static void _reserve(void* array, int numElem, int sizeElem);   // 0x0107f4a0
};

#define HK_ARRAY_DONT_DEALLOCATE 0x80000000

template <typename T>
class hkArray
{
public:
    hkArray() : m_data(0), m_size(0), m_capacityAndFlags(HK_ARRAY_DONT_DEALLOCATE) {}

    T* m_data;
    int m_size;
    int m_capacityAndFlags;

    int getSize() const { return m_size; }
    int getCapacity() const { return m_capacityAndFlags & 0x3fffffff; }

    void reserve(int n)
    {
        const int capacity = getCapacity();
        if (capacity < n)
        {
            int cap2 = 2 * capacity;
            int newSize = (n < cap2) ? cap2 : n;
            hkArrayUtil::_reserve(this, newSize, sizeof(T));
        }
    }

    void setSize(int n)
    {
        reserve(n);
        m_size = n;
    }

    T& operator[](int i) { return m_data[i]; }
    const T& operator[](int i) const { return m_data[i]; }

    ~hkArray()
    {
        if (!(m_capacityAndFlags & 0x80000000))
        {
            hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex);
            tm->deallocateChunk(m_data, (m_capacityAndFlags & 0x3fffffff) * (int)sizeof(T), 0x14);
        }
    }
};

struct hkGeometry
{
    struct Triangle
    {
        int m_a;
        int m_b;
        int m_c;
    };

    hkArray<hkVector4> m_vertices;   // +0x00
    hkArray<Triangle> m_triangles;   // +0x0c
};

struct hkStridedVertices
{
    hkReal* m_vertices;   // +0x00
    int m_numVertices;    // +0x04
    int m_striding;       // +0x08
};

class hkGeometryUtility
{
public:
    static void createConvexGeometry(const hkStridedVertices& stridedVertsIn, hkGeometry& geometryOut,
                                     hkArray<hkVector4>& planeEquationsOut, int mode);   // 0x010edf70
};

// Retail layout (0x90 bytes):
//   0x00 m_axis[3]           triangle projection axis indices
//   0x0c m_mult[10]          projection integrals
//   0x34 m_face[12]          face integrals
//   0x64 m_volume
//   0x68 m_P[3]              first moments
//   0x74 m_D[3]              second moment diagonal
//   0x80 m_O[3]              second moment off-diagonal
//   0x8c m_pad
class InternalInertiaTensorComputer
{
public:
    __declspec(noinline) void compProjectionIntegrals(const hkVector4* verts);   // 0x01124320
    __declspec(noinline) void compFaceIntegrals(const hkVector4* verts, const hkVector4& n);
    __declspec(noinline) void computeInertialTensorInternal(hkReal a, hkReal b, hkVector4& com, hkMatrix3& inertia);
    void init();
    __declspec(noinline) void compVolumeIntegrals(const hkGeometry* geom, const hkVector4& shift);
    __declspec(noinline) static hkVector4 compShift(const hkGeometry* geom);

    int m_axis[3];
    hkReal m_mult[10];
    hkReal m_face[12];
    hkReal m_volume;
    hkReal m_P[3];
    hkReal m_D[3];
    hkReal m_O[3];
    hkReal m_pad;
};

class hkInertiaTensorComputer
{
public:
    static hkResult combineMassProperties(const hkArray<hkMassElement>& elements, hkMassProperties& result);
    __declspec(noinline) static hkResult computeGeometryVolumeMassProperties(const hkGeometry* geom, hkReal mass, hkMassProperties& result);
    static hkResult computeVertexHullVolumeMassProperties(const hkReal* vertexIn, int striding, int numVertices,
                                                          hkReal mass, hkMassProperties& result);
    static void shiftInertiaFromCom(hkVector4& shift, hkReal mass, hkMatrix3& inertia);   // 0x01124280
};

// @ 0x01124620 InternalInertiaTensorComputer::compFaceIntegrals
void InternalInertiaTensorComputer::compFaceIntegrals(const hkVector4* verts, const hkVector4& n)
{
    compProjectionIntegrals(verts);

    const hkReal* np = &n.x;
    const hkReal* v0 = &verts[0].x;

    hkReal w = -((v0[0] * np[0] + v0[1] * np[1]) + v0[2] * np[2]);
    hkReal k1 = 1.0f / np[m_axis[2]];
    hkReal k2 = k1 * k1;
    hkReal k3 = k2 * k1;
    hkReal A = np[m_axis[0]];
    hkReal B = np[m_axis[1]];

    hkReal m0 = m_mult[0];
    hkReal m1 = m_mult[1];
    hkReal m2 = m_mult[2];
    hkReal m3 = m_mult[3];
    hkReal m4 = m_mult[4];
    hkReal m5 = m_mult[5];
    hkReal m6 = m_mult[6];
    hkReal m7 = m_mult[7];
    hkReal m8 = m_mult[8];
    hkReal m9 = m_mult[9];

    hkReal wm0 = w * m0;
    hkReal ab = A * B;
    hkReal tab = ab * m4;
    hkReal t1 = m2 * B + A * m1;

    m_face[0] = k1 * m1;
    m_face[1] = k1 * m2;
    m_face[2] = -(((m2 * B + A * m1) + wm0)) * k2;
    m_face[3] = k1 * m3;
    m_face[4] = k1 * m5;
    m_face[5] = (B * B * m5 + (A * m3 * A + ((tab + tab) + ((t1 + t1) + wm0) * w))) * k3;
    m_face[6] = k1 * m6;
    m_face[7] = k1 * m9;
    m_face[8] = -(k3 * k1) * (((A * A) * A) * m6
                + ((((A * m7) * A) * B) * 3.0f
                + (((B * m9) * B) * B
                + ((((A * m8) * B) * B) * 3.0f
                + (((((m2 * B + A * m1) * 3.0f) + wm0) * w
                + ((B * B * m5 + ((A * m3) * A + (tab + tab))) * 3.0f)) * w)))));
    m_face[9] = k1 * m7;
    m_face[10] = -((w * m5 + (B * m9 + A * m8)) * k2);

    hkReal t2 = (A * m7) * B;
    hkReal t3 = B * m4 + A * m3;
    m_face[11] = ((B * B) * m6 + (((B * m8) * B)
                + ((t2 + t2) + (w * m1 + (t3 + t3)) * w))) * k3;
}

// @ 0x01124820 InternalInertiaTensorComputer::computeInertialTensorInternal
void InternalInertiaTensorComputer::computeInertialTensorInternal(hkReal a, hkReal b, hkVector4& com, hkMatrix3& inertia)
{
    com.x = m_P[0] / m_volume;
    com.y = m_P[1] / m_volume;
    com.z = m_P[2] / m_volume;

    hkReal* m = &inertia.m_col0.x;

    m[0] = (m_D[1] + m_D[2]) * b;
    m[5] = (m_D[0] + m_D[2]) * b;
    m[10] = (m_D[0] + m_D[1]) * b;

    hkReal t = -(b * m_O[0]);
    m[1] = t;
    m[4] = t;
    t = -(b * m_O[1]);
    m[6] = t;
    m[9] = t;
    t = -(b * m_O[2]);
    m[8] = t;
    m[2] = t;

    m[0] = m[0] - (com.z * com.z + com.y * com.y) * a;
    m[5] = m[5] - (com.z * com.z + com.x * com.x) * a;
    m[10] = m[10] - (com.y * com.y + com.x * com.x) * a;

    t = com.x * com.y * a + m[1];
    m[1] = t;
    m[4] = t;
    t = com.z * com.y * a + m[6];
    m[6] = t;
    m[9] = t;
    t = com.z * com.x * a + m[8];
    m[8] = t;
    m[2] = t;
}

// @ 0x01124930 InternalInertiaTensorComputer::init
void InternalInertiaTensorComputer::init()
{
    m_axis[0] = 0;
    m_axis[1] = 0;

    m_mult[4] = 0.0f;
    m_mult[3] = 0.0f;
    m_mult[2] = 0.0f;
    m_mult[1] = 0.0f;

    for (int i = 0; i < 24; i++)
    {
        ((hkReal*)&m_mult[5])[i] = 0.0f;
    }

    m_face[7] = 1.0f;
    m_volume = 1.0f;
    m_D[1] = 1.0f;

    m_pad = 0.0f;
    m_O[2] = 0.0f;
    m_O[1] = 0.0f;
    m_O[0] = 0.0f;
}

// @ 0x011249c0 hkInertiaTensorComputer::combineMassProperties
hkResult hkInertiaTensorComputer::combineMassProperties(const hkArray<hkMassElement>& elements, hkMassProperties& result)
{
    hkVector4 comSum;
    hkReal totalMass = 0.0f;
    hkReal totalVolume = 0.0f;

    comSum.x = 0.0f;
    comSum.y = 0.0f;
    comSum.z = 0.0f;
    comSum.w = 0.0f;

    for (int i = 0; i < elements.getSize(); i++)
    {
        const hkMassElement& e = elements[i];
        hkVector4 transformed;
        transformed.setTransformedPos(e.m_transform, e.m_properties.m_centerOfMass);

        hkReal mass = e.m_properties.m_mass;
        comSum.x += transformed.x * mass;
        comSum.y += transformed.y * mass;
        comSum.z += transformed.z * mass;
        comSum.w += transformed.w * mass;
        totalMass += e.m_properties.m_mass;
        totalVolume += e.m_properties.m_volume;
    }

    if (totalMass <= 0.0f)
    {
        return HK_FAILURE;
    }

    hkReal invMass = 1.0f / totalMass;

    result.m_centerOfMass.x = comSum.x * invMass;
    result.m_centerOfMass.y = comSum.y * invMass;
    result.m_centerOfMass.z = comSum.z * invMass;
    result.m_centerOfMass.w = comSum.w * invMass;
    result.m_mass = totalMass;
    result.m_volume = totalVolume;

    result.m_inertiaTensor.m_col0.x = 0.0f;
    result.m_inertiaTensor.m_col0.y = 0.0f;
    result.m_inertiaTensor.m_col0.z = 0.0f;
    result.m_inertiaTensor.m_col0.w = 0.0f;
    result.m_inertiaTensor.m_col1.x = 0.0f;
    result.m_inertiaTensor.m_col1.y = 0.0f;
    result.m_inertiaTensor.m_col1.z = 0.0f;
    result.m_inertiaTensor.m_col1.w = 0.0f;
    result.m_inertiaTensor.m_col2.x = 0.0f;
    result.m_inertiaTensor.m_col2.y = 0.0f;
    result.m_inertiaTensor.m_col2.z = 0.0f;
    result.m_inertiaTensor.m_col2.w = 0.0f;

    for (int i = 0; i < elements.getSize(); i++)
    {
        const hkMassElement& e = elements[i];

        hkMatrix3 mat = e.m_properties.m_inertiaTensor;
        mat.changeBasis(e.m_transform.m_rotation);

        hkVector4 transformed;
        transformed.setTransformedPos(e.m_transform, e.m_properties.m_centerOfMass);

        transformed.x -= result.m_centerOfMass.x;
        transformed.y -= result.m_centerOfMass.y;
        transformed.z -= result.m_centerOfMass.z;
        transformed.w -= result.m_centerOfMass.w;

        shiftInertiaFromCom(transformed, e.m_properties.m_mass, mat);
        result.m_inertiaTensor.add(mat);
    }

    return HK_SUCCESS;
}

// @ 0x01124c40 InternalInertiaTensorComputer::compVolumeIntegrals
void InternalInertiaTensorComputer::compVolumeIntegrals(const hkGeometry* geom, const hkVector4& shift)
{
    m_O[2] = 0.0f;
    m_O[1] = 0.0f;
    m_O[0] = 0.0f;
    m_D[2] = 0.0f;
    m_D[1] = 0.0f;
    m_D[0] = 0.0f;
    m_P[2] = 0.0f;
    m_P[1] = 0.0f;
    m_P[0] = 0.0f;
    m_volume = 0.0f;

    for (int i = 0; i < geom->m_triangles.getSize(); i++)
    {
        const hkGeometry::Triangle& tri = geom->m_triangles[i];
        const hkVector4& p0 = geom->m_vertices[tri.m_a];
        const hkVector4& p1 = geom->m_vertices[tri.m_b];
        const hkVector4& p2 = geom->m_vertices[tri.m_c];

        hkVector4 v0, v1, v2;
        v0.x = p0.x + shift.x;
        v0.y = p0.y + shift.y;
        v0.z = p0.z + shift.z;
        v0.w = p0.w + shift.w;
        v1.x = p1.x + shift.x;
        v1.y = p1.y + shift.y;
        v1.z = p1.z + shift.z;
        v1.w = p1.w + shift.w;
        v2.x = p2.x + shift.x;
        v2.y = p2.y + shift.y;
        v2.z = p2.z + shift.z;
        v2.w = p2.w + shift.w;

        hkReal e1x = v1.x - v0.x;
        hkReal e1y = v1.y - v0.y;
        hkReal e1z = v1.z - v0.z;
        hkReal e2x = v2.x - v0.x;
        hkReal e2y = v2.y - v0.y;
        hkReal e2z = v2.z - v0.z;

        hkVector4 n;
        n.x = e1y * e2z - e1z * e2y;
        n.y = e1z * e2x - e1x * e2z;
        n.z = e1x * e2y - e1y * e2x;
        n.w = 0.0f;

        hkReal len = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);
        if (len > 0.0f)
        {
            hkReal inv = 1.0f / len;
            n.x *= inv;
            n.y *= inv;
            n.z *= inv;
            n.w *= inv;

            hkReal ax = fabsf(n.x);
            hkReal ay = fabsf(n.y);
            hkReal az = fabsf(n.z);
            if (ax > ay && ax > az)
            {
                m_axis[2] = 0;
            }
            else
            {
                m_axis[2] = (ay > az) ? 1 : 2;
            }

            m_axis[0] = (m_axis[2] + 1) % 3;
            m_axis[1] = (m_axis[0] + 1) % 3;

            compFaceIntegrals(&v0, n);

            hkReal f;
            if (m_axis[0] == 0)
            {
                f = m_face[0];
            }
            else if (m_axis[1] == 0)
            {
                f = m_face[1];
            }
            else
            {
                f = m_face[2];
            }
            m_volume += n.x * f;

            const hkReal* np = &n.x;
            m_P[m_axis[0]] += np[m_axis[0]] * m_face[3];
            m_P[m_axis[1]] += np[m_axis[1]] * m_face[4];
            m_P[m_axis[2]] += np[m_axis[2]] * m_face[5];

            m_D[m_axis[0]] += np[m_axis[0]] * m_face[6];
            m_D[m_axis[1]] += np[m_axis[1]] * m_face[7];
            m_D[m_axis[2]] += np[m_axis[2]] * m_face[8];

            m_O[m_axis[0]] += np[m_axis[0]] * m_face[9];
            m_O[m_axis[1]] += np[m_axis[1]] * m_face[10];
            m_O[m_axis[2]] += np[m_axis[2]] * m_face[11];
        }
    }

    m_P[0] *= 0.5f;
    m_P[1] *= 0.5f;
    m_P[2] *= 0.5f;
    m_D[0] *= 1.0f / 3.0f;
    m_D[1] *= 1.0f / 3.0f;
    m_D[2] *= 1.0f / 3.0f;
    m_O[0] *= 0.5f;
    m_O[1] *= 0.5f;
    m_O[2] *= 0.5f;
}

// @ 0x01125000 InternalInertiaTensorComputer::compShift
hkVector4 InternalInertiaTensorComputer::compShift(const hkGeometry* geom)
{
    hkVector4 shift;
    shift.x = 0.0f;
    shift.y = 0.0f;
    shift.z = 0.0f;
    shift.w = 0.0f;

    hkVector4 min;
    min.x = HK_REAL_MAX;
    min.y = HK_REAL_MAX;
    min.z = HK_REAL_MAX;
    min.w = HK_REAL_MAX;

    hkVector4 max;
    max.x = -HK_REAL_MAX;
    max.y = -HK_REAL_MAX;
    max.z = -HK_REAL_MAX;
    max.w = -HK_REAL_MAX;

    int numVertices = geom->m_vertices.getSize();
    const hkVector4* verts = geom->m_vertices.m_data;
    for (int i = 0; i < numVertices; i++)
    {
        const hkVector4& v = verts[i];
        if (v.x < min.x) min.x = v.x;
        if (v.y < min.y) min.y = v.y;
        if (v.z < min.z) min.z = v.z;
        if (v.w < min.w) min.w = v.w;
        if (max.x < v.x) max.x = v.x;
        if (max.y < v.y) max.y = v.y;
        if (max.z < v.z) max.z = v.z;
        if (max.w < v.w) max.w = v.w;
    }

    if (numVertices != 0)
    {
        shift.x = max.x + min.x;
        shift.y = max.y + min.y;
        shift.z = max.z + min.z;
        shift.w = max.w + min.w;
        shift.x *= 0.5f;
        shift.y *= 0.5f;
        shift.z *= 0.5f;
        shift.w *= 0.5f;
    }

    hkVector4 result;
    result.x = -shift.x;
    result.y = -shift.y;
    result.z = -shift.z;
    result.w = -shift.w;
    return result;
}

// @ 0x011251e0 hkInertiaTensorComputer::computeGeometryVolumeMassProperties
hkResult hkInertiaTensorComputer::computeGeometryVolumeMassProperties(const hkGeometry* geom, hkReal mass,
                                                                     hkMassProperties& result)
{
    if (mass <= 0.0f)
    {
        return HK_FAILURE;
    }

    hkVector4 shift = InternalInertiaTensorComputer::compShift(geom);
    shift.w = 0.0f;

    InternalInertiaTensorComputer itc;
    itc.compVolumeIntegrals(geom, shift);

    if (itc.m_volume <= 0.0f)
    {
        return HK_FAILURE;
    }

    result.m_volume = itc.m_volume;

    hkVector4 com;
    hkMatrix3 inertia;
    itc.computeInertialTensorInternal(mass, mass / itc.m_volume, com, inertia);

    result.m_centerOfMass.w = com.w;
    result.m_centerOfMass.x = com.x - shift.x;
    result.m_centerOfMass.y = com.y - shift.y;
    result.m_centerOfMass.z = com.z - shift.z;

    result.m_inertiaTensor = inertia;
    result.m_mass = mass;
    return HK_SUCCESS;
}

// @ 0x011252d0 hkInertiaTensorComputer::computeVertexHullVolumeMassProperties
hkResult hkInertiaTensorComputer::computeVertexHullVolumeMassProperties(const hkReal* vertexIn, int striding,
                                                                       int numVertices, hkReal mass,
                                                                       hkMassProperties& result)
{
    if (mass <= 0.0f)
    {
        return HK_FAILURE;
    }

    hkArray<hkVector4> vertices;
    vertices.setSize(numVertices);

    const char* p = (const char*)vertexIn;
    for (int i = 0; i < numVertices; i++)
    {
        const hkReal* v = (const hkReal*)p;
        vertices[i].x = v[0];
        vertices[i].y = v[1];
        vertices[i].z = v[2];
        p += striding;
    }

    hkStridedVertices sv;
    sv.m_vertices = (hkReal*)vertices.m_data;
    sv.m_striding = sizeof(hkVector4);
    sv.m_numVertices = numVertices;

    hkGeometry geom;
    hkArray<hkVector4> planeEquations;
    hkGeometryUtility::createConvexGeometry(sv, geom, planeEquations, 1);

    computeGeometryVolumeMassProperties(&geom, mass, result);
    result.m_mass = mass;
    return HK_SUCCESS;
}
