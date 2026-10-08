// Weighted covariance of a 3D point set (xx, xy, xz, yy, yz, zz).
#include "types.h"

struct Vec3 { float x, y, z; };
static inline Vec3 Load(const Vec3* a, int i) { return a[i]; }
static inline Vec3 Scale(const Vec3& a, float s) { Vec3 r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; return r; }
static inline Vec3 AddScaled(const Vec3& a, const Vec3& p, float s) { Vec3 r; r.x = p.x * s + a.x; r.y = p.y * s + a.y; r.z = p.z * s + a.z; return r; }
static inline Vec3 Sub(const Vec3& a, float x, float y, float z) { Vec3 r; r.x = a.x - x; r.y = a.y - y; r.z = a.z - z; return r; }

// @ 0x008a4a20
void WeightedCovariance(float* cov, int n, const Vec3* pts, const float* w)
{
    Vec3 mean; mean.x = 0.0f; mean.y = 0.0f; mean.z = 0.0f;
    float sw = 0.0f;
    for (int i = 0; i < n; ++i) {
        Vec3 p = Load(pts, i);
        float wi = w[i];
        sw += wi;
        mean = AddScaled(mean, p, wi);
    }
    float inv = 1.0f / sw;
    float mx = mean.x * inv, my = mean.y * inv, mz = mean.z * inv;
    for (int k = 0; k < 6; ++k) cov[k] = 0.0f;
    for (int i = 0; i < n; ++i) {
        Vec3 p = Load(pts, i);
        Vec3 d = Sub(p, mx, my, mz);
        Vec3 dw = Scale(d, w[i]);
        cov[0] += dw.x * d.x;
        cov[1] += dw.y * d.x;
        cov[2] += dw.z * d.x;
        cov[3] += dw.y * d.y;
        cov[4] += dw.z * d.y;
        cov[5] += dw.z * d.z;
    }
}
