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
static inline float Length(const Vector3& a) { return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z); }
static inline Vector3 NormalizedSafe(const Vector3& a) {
    float inv = 1.0f / sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + 1e-8f);
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
};
PlanetModel* __cdecl GetPlanetModel();                                  // 0x00b3d350 (SP::PlanetModel)

// @ 0x00cbcde0  BuildFlightArcPath (cdecl: 6 floats + out vector; returns false when the points are < 300 apart)
bool BuildFlightArcPath(Vector3 a, Vector3 b, SpVectorV3* out)
{
    if (Length(a - b) < 300.0f)
        return false;

    float rad = GetPlanetModel()->GetRadius();
    float R = rad + 80.0f;

    // ---- arc leaving A toward B
    Vector3 u = NormalizedSafe(b - a);
    float la = Length(a);
    float k = ((rad + 80.0f) - la) * -4.4444445e-05f;
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
            Vector3 p = b + tb * s;
            float h = ((s - 150.0f) * (s - 150.0f)) * kb + R;
            arr[i] = NormalizedSafe(p) * h;
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
