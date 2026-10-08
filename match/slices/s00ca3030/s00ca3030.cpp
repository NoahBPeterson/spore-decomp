// slice s00ca3030 - 0x00ca3770: find the point on the planet surface nearest to the camera that lies on
// a ring of directions around a ray (spiral search outward in 16-unit radius steps).
// Compile with /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include <math.h>
#include <float.h>
#include "types.h"

struct Vector3 {
    float x, y, z;
};
struct Quaternion { float x, y, z, w; };

#pragma intrinsic(sin, cos, sqrt)

extern Vector3 gNoPoint;     // 0x01699b08: the "no result" vector
extern float gTwoPi;         // 0x0169a280
extern const float gMinSearchStep;  // 0x014763b0 (16.0)

namespace SP {
class cPlanetModel {
public:
    int GetContinent(const Vector3* p);           // 0x00b88590 (thiscall)
    float GetRadius();                            // 0x00b7e4d0 (thiscall, returns float in st0)
    uint32_t GetTerrainFlags(const Vector3* p);   // 0x00b7e840 (thiscall, ret 4)
    void Project(Vector3* out, const Vector3* in);   // 0x00b81630 (thiscall, ret 8)
};
cPlanetModel* PlanetModel();                      // 0x00b3d350 (cdecl)
}
using SP::cPlanetModel;

Vector3 __cdecl QuatRotate(const Vector3& v, const Quaternion& q);   // 0x0059aed0 (sret first)

struct ICamera {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10();
    virtual const Vector3* GetPosition();     // +0x2c
};

static inline float InvLength(float x, float y, float z) {
    return 1.0f / (float)sqrt(x * x + (y * y + z * z) + 1e-8f);
}

class cSurfaceSearcher {
public:
    char pad0[0x34];
    ICamera mCamera;              // +0x34 (embedded interface subobject)
    char pad38[0xb1c - 0x38];
    int mMode;                    // +0xb1c
    Vector3* FindNearestSurfacePoint(Vector3* out, const Vector3* dir, float dist);   // 0x00ca3770
};

Vector3* cSurfaceSearcher::FindNearestSurfacePoint(Vector3* out, const Vector3* dir, float dist) {
    cPlanetModel* pm = SP::PlanetModel();
    if (!pm || (dir->x == gNoPoint.x && dir->y == gNoPoint.y && dir->z == gNoPoint.z)) {
        out->x = gNoPoint.x;
        out->y = gNoPoint.y;
        out->z = gNoPoint.z;
        return out;
    }
    const Vector3* c = mCamera.GetPosition();
    Vector3 cam;
    cam.x = c->x; cam.y = c->y; cam.z = c->z;

    const float* pr = &gMinSearchStep;
    if (!(gMinSearchStep > dist)) pr = &dist;
    float radius = *pr;
    const int continent = pm->GetContinent(&cam);
    const float planetRadius = pm->GetRadius();
    const float invR = 1.0f / planetRadius;
    float angle = invR * radius;

    float dx = dir->x, dy = dir->y, dz = dir->z;
    float sd = InvLength(dx, dy, dz);
    float sc = InvLength(cam.x, cam.y, cam.z);
    float ax = (cam.y * sc) * (dz * sd) - (cam.z * sc) * (dy * sd);
    float ay = (cam.z * sc) * (dx * sd) - (dz * sd) * (sc * cam.x);
    float az = (dy * sd) * (sc * cam.x) - (cam.y * sc) * (dx * sd);
    float sa = InvLength(ax, ay, az);
    Vector3 axis;
    axis.y = ay * sa;
    axis.z = az * sa;
    axis.x = sa * ax;

    Vector3 best = gNoPoint;
    float bestDist = FLT_MAX;
    while (angle < gTwoPi) {
        Vector3 start = *dir;
        float s = (float)sin(angle * 0.5f);
        float co = (float)cos(angle * 0.5f);
        Quaternion q;
        q.x = s * axis.x;
        q.y = axis.y * s;
        q.z = axis.z * s;
        q.w = co;
        Vector3 pt = QuatRotate(start, q);

        int n = (int)(gTwoPi * radius * 0.0625f);
        float step = gTwoPi / (float)n;
        float t = 0.0f;
        float rx = dir->x, ry = dir->y, rz = dir->z;
        float sr = InvLength(rx, ry, rz);
        float ux = sr * rx, uy = sr * ry, uz = sr * rz;
        for (int i = n; i > 0; --i) {
            float sn = (float)sin(t * 0.5f);
            float cs = (float)cos(t * 0.5f);
            float qz = uz * sn;
            float qy = uy * sn;
            float qx = sn * ux;
            float yy = qy * qy;
            float zy = qz * qy;
            float yx = qy * qx;
            float wy = cs * qy;
            Vector3 r;
            r.x = ((wy + qz * qx) * pt.z + (yx - cs * qz) * pt.y) * 2.0f + (1.0f - (qz * qz + yy) * 2.0f) * pt.x;
            r.y = ((cs * qz + yx) * pt.x + (zy - cs * qx) * pt.z) * 2.0f + (1.0f - (qz * qz + qx * qx) * 2.0f) * pt.y;
            r.z = ((qz * qx - wy) * pt.x + (cs * qx + zy) * pt.y) * 2.0f + (1.0f - (qx * qx + yy) * 2.0f) * pt.z;
            if (pm->GetContinent(&r) == continent) {
                int mode = mMode;
                cPlanetModel* pm2 = SP::PlanetModel();
                bool ok;
                if (mode == 0) {
                    ok = (pm2->GetTerrainFlags(&r) & 0x98000000) == 0;
                } else if (mode == 1) {
                    ok = (pm2->GetTerrainFlags(&r) & 0x58000000) == 0;
                } else if (mode == 2) {
                    ok = (~(pm2->GetTerrainFlags(&r) >> 29) & 1) != 0;
                } else {
                    ok = true;
                }
                if (ok) {
                    float ey = r.y - cam.y;
                    float ex = r.x - cam.x;
                    float ez = r.z - cam.z;
                    float d = ez * ez + ey * ey + ex * ex;
                    if (bestDist > d) {
                        best = r;
                        bestDist = d;
                    }
                }
            }
            t += step;
        }
        if (best.x != gNoPoint.x || best.y != gNoPoint.y || best.z != gNoPoint.z) {
            pm->Project(out, &best);
            return out;
        }
        radius += gMinSearchStep;
        angle = invR * radius;
    }
    out->x = gNoPoint.x;
    out->y = gNoPoint.y;
    out->z = gNoPoint.z;
    return out;
}
