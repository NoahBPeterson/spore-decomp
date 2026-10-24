// Slice s00cbcde0: flight-path arc generator between two points on a planet.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <math.h>
#include <new>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
static inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
static inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
static inline Vector3 operator*(float s, const Vector3& a) { return Vector3(s * a.x, s * a.y, s * a.z); }
static inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
// x87 sums the squares as (x*x + z*z) + y*y in the original, so keep that order here.
static inline float Length(const Vector3& a) { return sqrtf(a.x * a.x + a.z * a.z + a.y * a.y); }
static inline Vector3 NormalizedSafe(const Vector3& a) {
    float inv = 1.0f / sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + 1e-8f);
    return inv * a;
}
// The original's second-arc loop sums the squared length as (z*z + y*y) + x*x, and its
// intermediates are materialised separately, so that grouping survives at that site.  |p| is
// only a few units there, which makes the grouping visible in the last bit of the result.
static inline Vector3 NormalizedSafeArc(const Vector3& a) {
    float zz = a.z * a.z;
    float yy = a.y * a.y;
    float rr = zz + yy;
    float inv = 1.0f / sqrtf(rr + a.x * a.x + 1e-8f);
    return inv * a;
}

struct sp_alloc { unsigned int d[2]; };

struct SpVectorV3 {                    // eastl::vector<Vector3, sp_vector_allocator>
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    sp_alloc mAllocator;
    void DoInsertValue(Vector3* pos, const Vector3& v);                 // 0x004b5ad0
    void push_back(const Vector3& v) {
        if (mpEnd < mpCapacity) ::new((void*)mpEnd++) Vector3(v);
        else DoInsertValue(mpEnd, v);
    }
};

struct PlanetModel {
    float GetRadius();                                                  // 0x00b7e4d0 (thiscall, float in st0)
    float GetArcRadius(const Vector3* pA, const Vector3* pB);           // 0x00b81470
};
PlanetModel* __cdecl GetPlanetModel();                                  // 0x00b3d350 (SP::PlanetModel)

struct IPositioned {
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void p20(); virtual void p24(); virtual void p28();
    virtual Vector3* GetPosition();                                     // +0x2c
};

// @ 0x00cbd620  BuildFlightArcPathFromObjects (cdecl: two positioned objects, out vector, 3 floats; 64-segment arc)
bool BuildFlightArcPathFromObjects(IPositioned* pA, IPositioned* pB, SpVectorV3* out,
                                   float ox, float oy, float oz)
{
    Vector3 a = *pA->GetPosition();
    Vector3 b;
    if (pB)
        b = *pB->GetPosition() + Vector3(ox, oy, oz);
    else
        b = Vector3(ox, oy, oz);

    float arcRadius = GetPlanetModel()->GetArcRadius(&a, &b);
    if (arcRadius < 300.0f)
        return false;

    float R = arcRadius + 80.0f;
    for (int i = 0; i < 64; ++i) {
        float t = (float)i * (1.0f / 64.0f);
        Vector3 p = a * (1.0f - t) + b * t;
        p = NormalizedSafe(p) * R;
        out->push_back(p);
    }
    return true;
}

// @ 0x00cbcde0  BuildFlightArcPath (cdecl: 6 floats + out vector; returns false when the points are < 300 apart)
bool BuildFlightArcPath(Vector3 a, Vector3 b, SpVectorV3* out)
{
    if (Length(a - b) < 300.0f)
        return false;

    float R = GetPlanetModel()->GetRadius() + 80.0f;

    // ---- arc leaving A toward B
    Vector3 u = NormalizedSafe(b - a);
    float la = Length(a);
    float k = (R - la) * -4.4444445e-05f;
    Vector3 n = NormalizedSafe(a);
    Vector3 t = NormalizedSafe(u - Dot(n, u) * n);
    for (int i = 0; i < 12; ++i) {
        float s = (float)i * 12.5f;
        Vector3 p = a + t * s;
        float h = ((s - 150.0f) * (s - 150.0f)) * k + R;
        out->push_back(NormalizedSafe(p) * h);
    }

    // ---- arc leaving B toward A, kept in a local array
    Vector3 arr[12];
    {
        Vector3 e = NormalizedSafe(a - b);
        float lb = Length(b);
        float kb = (R - lb) * -4.4444445e-05f;
        Vector3 nb = NormalizedSafe(b);
        Vector3 tb = NormalizedSafe(e - Dot(nb, e) * nb);
        for (int i = 0; i < 12; ++i) {
            float s = (float)i * 12.5f;
            Vector3 p = s * tb + b;
            float h = ((s - 150.0f) * (s - 150.0f)) * kb + R;
            arr[i] = NormalizedSafeArc(p) * h;
        }
    }

    // ---- walk from the end of the first arc to the start of the second
    Vector3 cur = out->mpEnd[-1];
    float len;
    do {
        Vector3 w = arr[11] - cur;
        len = Length(w);
        Vector3 wn = w * (1.0f / len);
        Vector3 cn = NormalizedSafe(cur);
        Vector3 st = NormalizedSafe(wn - Dot(cn, wn) * cn);
        cur = cur + st * 16.0f;
        cur = NormalizedSafe(cur) * R;
        out->push_back(cur);
    } while (33.6f <= len);

    for (int i = 11; i >= 0; --i)
        out->push_back(arr[i]);
    return true;
}
