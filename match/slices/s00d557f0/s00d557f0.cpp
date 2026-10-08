// slice s00d557f0 — SetStarPattern (PDB name), space-turret fire pattern.
// Fills `out` with `count` points on a five-pointed star around `pos`: an inner ring and
// an outer ring of five points (rotating `dir` about the normalized `pos` axis), then
// fills the edges with evenly spaced interpolation points.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(cos, sin, sqrt)

inline void* operator new(unsigned int, void* p) throw() { return p; }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator() {}
};

template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    T* erase(T* first, T* last);
    void DoInsertValue(T* pos, const T& v);
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(v);
        else
            DoInsertValue(mpEnd, v);
    }
    void clear() { erase(mpBegin, mpEnd); }
};

typedef SpVector<Vector3> Vec3Vector;
template <> Vector3* Vec3Vector::erase(Vector3* first, Vector3* last);          // 0x50f740
template <> void Vec3Vector::DoInsertValue(Vector3* pos, const Vector3& v);     // 0x4b5ad0

extern float g_169ebf0;     // base angular step (radians)

// Adds five points of one star ring: the direction `d` rotated about the unit axis of `p`
// by successive angles, scaled by `scale` and offset by `p`.
static __forceinline void AddStarRing(Vec3Vector& out, const Vector3& p, const Vector3& d,
                               float scale, float angle, const float& step)
{
    for (int i = 5; i != 0; --i) {
        float inv = 1.0f / (float)sqrt(p.x * p.x + (p.z * p.z + p.y * p.y));
        float s = (float)sin(angle * 0.5f);
        float c = (float)cos(angle * 0.5f);
        float qy = (p.y * inv) * s;
        float qz = (p.z * inv) * s;
        float qx = s * (inv * p.x);
        float rx = (((c * qy + qz * qx) * d.z + (qy * qx - c * qz) * d.y) * 2.0f +
                     (1.0f - (qz * qz + qy * qy) * 2.0f) * d.x) * scale + p.x;
        float ry = (((qz * qy - c * qx) * d.z + (c * qz + qy * qx) * d.x) * 2.0f +
                     (1.0f - (qz * qz + qx * qx) * 2.0f) * d.y) * scale + p.y;
        float rz = (((c * qx + qz * qy) * d.y + (qz * qx - c * qy) * d.x) * 2.0f +
                     (1.0f - (qx * qx + qy * qy) * 2.0f) * d.z) * scale + p.z;
        Vector3 r(rx, ry, rz);
        out.push_back(r);
        angle = step + angle;
    }
}

// @ 0x00d557f0
void SetStarPattern(int count, Vec3Vector& out, Vector3 p, Vector3 d, float radius)
{
    out.clear();
    static float sStep = g_169ebf0 * 0.2f;

    int n = count;
    if (n >= 5) {
        AddStarRing(out, p, d, radius * 0.5f, 0.0f, sStep);
        n -= 5;
        if (n >= 5) {
            AddStarRing(out, p, d, radius, sStep * 0.5f, sStep);
            n -= 5;
        }
    }

    int m = n / 10;
    if (m != 0) {
        const Vector3* v = out.mpBegin;
        float dx = v[0].x - v[5].x;
        float dy = v[0].y - v[5].y;
        float dz = v[0].z - v[5].z;
        float stepT = (float)sqrt(dx * dx + (dy * dy + dz * dz)) / (float)(m + 1);
        for (int j = 0; j < 5; ++j) {
            const Vector3* base = out.mpBegin;
            Vector3 a = base[j];
            Vector3 b = base[j + 5];
            Vector3 c = base[(j < 4) ? j + 1 : 0];
            if (m > 0) {
                Vector3 d1(b.x - a.x, b.y - a.y, b.z - a.z);
                Vector3 d2(b.x - c.x, b.y - c.y, b.z - c.z);
                float inv1 = 1.0f / (float)sqrt(d1.y * d1.y + (d1.z * d1.z + d1.x * d1.x));
                Vector3 u1(inv1 * d1.x, d1.y * inv1, d1.z * inv1);
                float inv2 = 1.0f / (float)sqrt(d2.y * d2.y + (d2.z * d2.z + d2.x * d2.x));
                Vector3 u2(inv2 * d2.x, d2.y * inv2, d2.z * inv2);
                float t = stepT;
                for (int k = m; k != 0; --k) {
                    Vector3 q1(u1.x * t + a.x, u1.y * t + a.y, u1.z * t + a.z);
                    out.push_back(q1);
                    Vector3 q2(u2.x * t + c.x, u2.y * t + c.y, u2.z * t + c.z);
                    out.push_back(q2);
                    t = t + stepT;
                }
            }
        }
    }
}
