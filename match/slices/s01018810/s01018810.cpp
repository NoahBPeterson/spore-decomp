// Slice s01018810 -- 0x01018810: tangent-point solver for a cone/sphere constraint (camera helper).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (x87 sqrt/fsin/fcos/_CIacos mixed with SSE scalar math),
// like the neighbouring 0x01019090 slice.
//
// Given a direction vector `dir`, a reference axis `axis`, a radius R, a scale k and two angles, it
// computes the tangent point on the cone surface (written to *outA), reports the sphere point R*n in
// *outB and *outC, then (if the tangent direction leaves the cone, cos < cos(1.6231562)) rotates the
// tangent point by the quaternion about the axis cross product, and finally (when the resulting
// direction deviates from the cone half-angle) pushes outA/outB along the normalized dir.
#include "types.h"

#include <math.h>

struct Vector3 {
    float x, y, z;
};

struct Quaternion {
    float x, y, z, w;
};

Vector3* QuaternionRotate(Vector3* out, const Vector3* v, const Quaternion* q);   // 0x0059aed0 (cdecl)

// @ 0x01018810
void __stdcall ConeTangentSolve(const float* dir, const float* axis, float R, float k, float ang,
                                float off, float* outA, float* outB, float* outC)   // 0x01018810
{
    float dl = 1.0f / sqrtf(dir[2] * dir[2] + (dir[1] * dir[1] + dir[0] * dir[0]));
    float nz = dir[2] * dl;
    float ny = dir[1] * dl;
    float nx = dir[0] * dl;

    const float bx = axis[0], by = axis[1], bz = axis[2];   // the original loads the axis once, up front
    float half = ang * 0.5f - off;
    float rx = ny * R;
    float rz = nz * R;
    float rxx = nx * R;
    float cosv = cosf(half);
    float d = R - sinf(half) * k;

    float t = R * R - d * d;
    float r = (t > 0.0f) ? t : 0.0f;
    float sq = sqrtf(r);

    float invR = 1.0f / R;
    float tx = (nx * d + bx * sq) * invR;
    float tz = invR * (nz * d + bz * sq);
    float ty = invR * (ny * d + by * sq);

    float cx = bz * ny - by * nz;
    float cy = bx * nz - bz * nx;
    float cz = by * nx - ny * bx;

    float ux = cz * ty - cy * tz;
    float uy = cx * tz - tx * cz;
    float uz = tx * cy - cx * ty;

    float m = ((ux * rxx + uz * rz) + uy * rx) + cosv * k;
    double cmp = cos(1.6231561917811632);

    float px = tx * R + ux * m;
    outA[0] = px;
    float lx = px - rxx;
    float py = ty * R + uy * m;
    outA[1] = py;
    float ly = py - rx;
    float pz = tz * R + uz * m;
    outA[2] = pz;
    float lz = pz - rz;

    outB[0] = rxx;
    outB[1] = rx;
    outB[2] = rz;
    float c = ((lx * bx + bz * lz) + by * ly) / k;
    outC[0] = rxx;
    outC[1] = rx;
    outC[2] = rz;

    if (!((double)c > cmp)) {
        float ax = outA[0], ay = outA[1], az = outA[2];
        float d1x = outB[0] - ax, d1z = outB[2] - az, d1y = outB[1] - ay;
        float d2x = dir[0] - ax, d2y = dir[1] - ay, d2z = dir[2] - az;
        float i1 = 1.0f / sqrtf(d1y * d1y + (d1z * d1z + d1x * d1x));
        float i2 = 1.0f / sqrtf(d2y * d2y + (d2z * d2z + d2x * d2x));
        if (((i2 * d2z) * (i1 * d1z) + (i2 * d2y) * (i1 * d1y)) + (i1 * d1x) * (i2 * d2x) < cosv) {
            double px2 = dir[0], py2 = dir[1], pz2 = dir[2];
            float f = (float)(sqrt(pz2 * pz2 + (py2 * py2 + px2 * px2)) -
                              (double)R / ((double)ny * (double)ty + ((double)tz * (double)nz + (double)tx * (double)nx)));
            outA[0] = ax + nx * f;
            outA[1] = ay + ny * f;
            outA[2] = az + f * nz;
            outB[0] = outB[0] + nx * f;
            outB[1] = ny * f + outB[1];
            outB[2] = f * nz + outB[2];
            return;
        }
    } else {
        if (c <= -1.0f) c = -1.0f;
        if (1.0f <= c) c = 1.0f;
        float qi = 1.0f / sqrtf(cy * cy + (cz * cz + cx * cx));
        Vector3 axn;
        axn.x = qi * cx;
        axn.y = qi * cy;
        axn.z = qi * cz;
        double hang = ((double)(float)acos(c) - 1.6231562f) * 0.5;
        float sh = (float)sin(hang);
        float ch = (float)cos(hang);
        Quaternion q;
        q.x = sh * axn.x;
        q.y = sh * axn.y;
        q.z = sh * axn.z;
        q.w = ch;
        Vector3 lv;
        lv.x = lx;
        lv.y = ly;
        lv.z = lz;
        Vector3 res;
        Vector3* rr = QuaternionRotate(&res, &lv, &q);
        float qx = rr->x + rxx;
        float qy = rr->y + rx;
        float qz = rr->z + rz;
        outA[0] = qx;
        outA[1] = qy;
        outA[2] = qz;
        float e1y = dir[1] - qy, e1x = dir[0] - qx, e1z = dir[2] - qz;
        float e2x = outB[0] - qx, e2z = outB[2] - qz, e2y = outB[1] - qy;
        float i2 = 1.0f / sqrtf(e2y * e2y + (e2z * e2z + e2x * e2x));
        float len = sqrtf(e1y * e1y + (e1z * e1z + e1x * e1x));
        float i1 = 1.0f / len;
        float dot = ((i1 * e1z) * (i2 * e2z) + (i1 * e1y) * (i2 * e2y)) + (i1 * e1x) * (i2 * e2x);
        if (dot < cosv) {
            float pl = sqrtf(qy * qy + (qz * qz + qx * qx));
            float pi = 1.0f / pl;
            float s = (len * cosv - dot * len) + pl;
            outA[0] = (pi * qx) * s;
            outA[1] = (pi * qy) * s;
            outA[2] = (pi * qz) * s;
            return;
        }
    }
}
