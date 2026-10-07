// Havok 3.1.0 hkInertiaTensorComputer::computeTriangleSurfaceMassProperties (hkInertiaTensorComputer.cpp).
// No Havok 3.1 source is available; reconstructed from the binary, with names from symbols/havok_names.txt
// and the Havok 6.x header (hkpInertiaTensorComputer.h) for the parameter names.
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);

typedef float hkReal;
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };

extern unsigned long g_hkThreadMemoryTls;   // 0x016E4174 (hkThreadMemory instance TLS slot)

class hkThreadMemory
{
public:
    void* allocateChunk(int nbytes, int cl);             // 0x0107DAA0
    void deallocateChunk(void* p, int nbytes, int cl);   // 0x0107DB10
    static __forceinline hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls); }
};

struct hkArrayUtil
{
    static void __cdecl _reserveExactly(void* array, int numElem, int sizeElem);   // 0x0107F4A0
};

class __declspec(align(16)) hkVector4
{
public:
    hkReal x, y, z, w;

    __forceinline hkReal& operator()(int i) { return (&x)[i]; }
    __forceinline const hkReal& operator()(int i) const { return (&x)[i]; }
    __forceinline void operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    __forceinline void set(hkReal a, hkReal b, hkReal c, hkReal d) { x = a; y = b; z = c; w = d; }
    __forceinline void setAdd4(const hkVector4& a, const hkVector4& b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; }
    __forceinline void setSub4(const hkVector4& a, const hkVector4& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
    __forceinline void add4(const hkVector4& a) { x += a.x; y += a.y; z += a.z; w += a.w; }
    __forceinline void mul4(hkReal s) { x *= s; y *= s; z *= s; w *= s; }
    __forceinline void addMul4(hkReal s, const hkVector4& a) { x += s * a.x; y += s * a.y; z += s * a.z; w += s * a.w; }
    __forceinline void setCross(const hkVector4& a, const hkVector4& b)
    {
        const hkReal nx = a.y * b.z - a.z * b.y;
        const hkReal ny = a.z * b.x - a.x * b.z;
        const hkReal nz = a.x * b.y - a.y * b.x;
        set(nx, ny, nz, 0.0f);
    }
    __forceinline hkReal lengthSquared3() const { return x * x + y * y + z * z; }
    __forceinline hkReal length3() const { return sqrtf(lengthSquared3()); }
    __forceinline hkReal lengthInverse3() const
    {
        hkReal l2 = lengthSquared3();
        return (l2 != 0.0f) ? 1.0f / sqrtf(l2) : 0.0f;
    }
    __forceinline void normalize3() { mul4(lengthInverse3()); }

    static __forceinline float sqrtf(float f) { return (float)::sqrt((double)f); }
};
class hkMatrix3
{
public:
    hkVector4 m_col0, m_col1, m_col2;
    void operator=(const hkMatrix3& m);                  // 0x0044A8C0
    __forceinline hkVector4& getColumn(int i) { return (&m_col0)[i]; }
    __forceinline hkReal& operator()(int r, int c) { return getColumn(c)(r); }
};

template <class T> class hkArray
{
public:
    enum { CAPACITY_MASK = 0x3fffffff, LOCKED_FLAG = 0x40000000, DONT_DEALLOCATE_FLAG = 0x80000000 };
    T* m_data;
    int m_size;
    int m_capacityAndFlags;

    __forceinline hkArray() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
    __forceinline hkArray(T* buffer, int size, int capacity) : m_data(buffer), m_size(size), m_capacityAndFlags(capacity | DONT_DEALLOCATE_FLAG) {}
    __forceinline ~hkArray() { releaseMemory(); }
    __forceinline int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
    __forceinline void releaseMemory()
    {
        if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
            hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * sizeof(T), 0x14);
    }
    __forceinline T& operator[](int i) { return m_data[i]; }
    static __forceinline void copy(T* dst, const T* src, int n)
    {
        for (int i = 0; i < n; ++i)
            dst[i] = src[i];
    }
    __forceinline hkArray& operator=(const hkArray& a)
    {
        if (getCapacity() < a.m_size)
        {
            if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
                hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * sizeof(T), 0x14);
            int n = a.m_size;
            m_data = static_cast<T*>(hkThreadMemory::getInstance().allocateChunk(n * sizeof(T), 0x14));
            m_capacityAndFlags = n | (m_capacityAndFlags & LOCKED_FLAG);
        }
        m_size = a.m_size;
        copy(m_data, a.m_data, m_size);
        return *this;
    }
    __forceinline T& expandOne()
    {
        int oldSize = m_size;
        int newSize = oldSize + 1;
        if (getCapacity() < newSize)
        {
            int cap2 = 2 * getCapacity();
            hkArrayUtil::_reserveExactly(this, (newSize < cap2) ? cap2 : newSize, sizeof(T));
        }
        m_size = newSize;
        return m_data[oldSize];
    }
};

template <class T, unsigned N> class hkInplaceArray : public hkArray<T>
{
public:
    __forceinline hkInplaceArray(int size) : hkArray<T>(m_storage, size, N) {}
    __forceinline ~hkInplaceArray() {}
    T m_storage[N];
};

struct hkGeometry
{
    struct Triangle
    {
        int m_a, m_b, m_c;
        __forceinline void set(int a, int b, int c) { m_a = a; m_b = b; m_c = c; }
    };
    hkArray<hkVector4> m_vertices;   // +0x0
    hkArray<Triangle> m_triangles;   // +0xc
    __forceinline hkGeometry() {}
    ~hkGeometry();                   // 0x00453460
};

struct hkMassProperties
{
    hkReal m_volume;                 // +0x0
    hkReal m_mass;                   // +0x4
    hkVector4 m_centerOfMass;        // +0x10
    hkMatrix3 m_inertiaTensor;       // +0x20
    hkMassProperties();              // 0x00453250
};

class hkInertiaTensorComputer
{
public:
    static hkResult __cdecl computeGeometryVolumeMassProperties(const hkGeometry* geom, hkReal mass, hkMassProperties& result);   // 0x011251E0
    static void __cdecl shiftInertiaToCom(hkVector4& shift, hkReal mass, hkMatrix3& inertia);                                   // 0x011241E0
    static hkResult __cdecl computeTriangleSurfaceMassProperties(const hkVector4& v0, const hkVector4& v1, const hkVector4& v2,
                                                                 hkReal mass, hkReal surfaceThickness, hkMassProperties& result);
};

hkResult __cdecl hkInertiaTensorComputer::computeTriangleSurfaceMassProperties(const hkVector4& v0, const hkVector4& v1, const hkVector4& v2,
                                                                               hkReal mass, hkReal surfaceThickness, hkMassProperties& result)
{
    if (mass <= 0.0f || surfaceThickness < 0.0f)
    {
        return HK_FAILURE;
    }

    hkVector4 normal;
    {
        hkVector4 e1; e1.setSub4(v2, v1);
        hkVector4 e0; e0.setSub4(v0, v1);
        normal.setCross(e1, e0);
    }
    const hkReal area = normal.length3();   // twice the triangle area

    hkVector4 centerOfMass;
    hkMatrix3 inertia;

    if (surfaceThickness < 1e-5f)
    {
        // Infinitely thin triangle: second moments of a uniform triangle about the origin, then shift to the COM.
        centerOfMass.setAdd4(v0, v1);
        centerOfMass.add4(v2);
        centerOfMass.mul4(1.0f / 3.0f);

        const hkReal cxx = (9.0f * centerOfMass(0) * centerOfMass(0) + v0(0) * v0(0) + v2(0) * v2(0) + v1(0) * v1(0)) * mass * (1.0f / 12.0f);
        const hkReal cyy = (9.0f * centerOfMass(1) * centerOfMass(1) + v0(1) * v0(1) + v2(1) * v2(1) + v1(1) * v1(1)) * mass * (1.0f / 12.0f);
        const hkReal czz = (9.0f * centerOfMass(2) * centerOfMass(2) + v0(2) * v0(2) + v2(2) * v2(2) + v1(2) * v1(2)) * mass * (1.0f / 12.0f);
        hkReal c[3][3];
        c[0][0] = cxx; c[1][1] = cyy; c[2][2] = czz;
        c[0][1] = (v2(1) * v2(0) + v0(0) * v0(1) + v1(0) * v1(1) + 9.0f * centerOfMass(1) * centerOfMass(0)) * mass * (1.0f / 12.0f);
        c[0][2] = (v0(0) * v0(2) + v2(2) * v2(0) + 9.0f * centerOfMass(2) * centerOfMass(0) + v1(0) * v1(2)) * mass * (1.0f / 12.0f);
        c[1][2] = (9.0f * centerOfMass(2) * centerOfMass(1) + v2(1) * v2(2) + v1(1) * v1(2) + v0(2) * v0(1)) * mass * (1.0f / 12.0f);
        inertia(0, 0) = c[1][1] + c[2][2];
        inertia(1, 1) = c[0][0] + c[2][2];
        inertia(2, 2) = c[0][0] + c[1][1];
        inertia(0, 1) = inertia(1, 0) = -c[0][1];
        inertia(0, 2) = inertia(2, 0) = -c[0][2];
        inertia(1, 2) = inertia(2, 1) = -c[1][2];

        hkInertiaTensorComputer::shiftInertiaToCom(centerOfMass, mass, inertia);
    }
    else if (area < 1e-5f)
    {
        // Degenerate triangle: a point mass at the centroid.
        centerOfMass.setAdd4(v0, v1);
        centerOfMass.add4(v2);
        centerOfMass.mul4(1.0f / 3.0f);

        const hkReal x = centerOfMass(0);
        const hkReal y = centerOfMass(1);
        const hkReal z = centerOfMass(2);
        inertia(0, 0) = (y * y + z * z) * mass;
        inertia(1, 1) = (x * x + z * z) * mass;
        inertia(2, 2) = (x * x + y * y) * mass;
        inertia(0, 1) = inertia(1, 0) = -(x * y * mass);
        inertia(0, 2) = inertia(2, 0) = -(x * z * mass);
        inertia(1, 2) = inertia(2, 1) = -(y * z * mass);
    }
    else
    {
        // Thick triangle: a prism of height surfaceThickness centred on the triangle.
        normal.normalize3();

        hkInplaceArray<hkVector4, 6> vertices(6);
        const hkReal halfThickness = surfaceThickness * 0.5f;
        const hkReal minusHalfThickness = surfaceThickness * -0.5f;
        vertices[0] = v0; vertices[0].addMul4(halfThickness, normal);
        vertices[1] = v0; vertices[1].addMul4(minusHalfThickness, normal);
        vertices[2] = v1; vertices[2].addMul4(halfThickness, normal);
        vertices[3] = v1; vertices[3].addMul4(minusHalfThickness, normal);
        vertices[4] = v2; vertices[4].addMul4(halfThickness, normal);
        vertices[5] = v2; vertices[5].addMul4(minusHalfThickness, normal);

        hkMassProperties massProperties;
        {
            hkGeometry geom;
            geom.m_vertices = vertices;
            geom.m_triangles.expandOne().set(0, 2, 4);
            geom.m_triangles.expandOne().set(1, 5, 3);
            geom.m_triangles.expandOne().set(0, 3, 2);
            geom.m_triangles.expandOne().set(0, 1, 3);
            geom.m_triangles.expandOne().set(1, 0, 4);
            geom.m_triangles.expandOne().set(1, 4, 5);
            geom.m_triangles.expandOne().set(2, 5, 4);
            geom.m_triangles.expandOne().set(2, 3, 5);

            hkInertiaTensorComputer::computeGeometryVolumeMassProperties(&geom, mass, massProperties);
        }
        centerOfMass = massProperties.m_centerOfMass;
        inertia = massProperties.m_inertiaTensor;
    }

    result.m_mass = mass;
    result.m_inertiaTensor = inertia;
    result.m_centerOfMass = centerOfMass;
    result.m_volume = area * surfaceThickness * 0.5f;
    return HK_SUCCESS;
}
