// Spherical-ish interpolation step of a position/direction pair around a centre (SP:: namespace).
#include <math.h>
#include "types.h"

struct Vec3f { float x, y, z; };

extern Vec3f g_DefaultVec;              // 0x016dfaf8
extern float* OrthogonalVector(float* a, float* b);   // 0x006985b0, cdecl
// 0x01042570 / 0x010426a0: scalar spring/approach helpers (cdecl)
extern void ApproachScalar(float* value, float* velocity, float target, float a, float b, float dt);
extern void ApproachVector(float* value, float* velocity, float* target, float a, float b, float dt);

static inline float ClampF(float v, float lo, float hi)
{
    float r;
    __asm {
        movss xmm0, v
        maxss xmm0, lo
        minss xmm0, hi
        movss r, xmm0
    }
    return r;
}

// @ 0x01042aa0
void ArcStep(float* pos, float* dir, float* target, float* centre, float* params,
             float p6, float p7, float dt)
{
    if (dt != 0.0f) {
        float dy = target[1] - pos[1];
        float dz = target[2] - pos[2];
        float dx = target[0] - pos[0];
        if ((dy * dy + dx * dx) + dz * dz < 1.5258789e-05f) {
            pos[0] = target[0];
            pos[1] = target[1];
            pos[2] = target[2];
            dir[0] = g_DefaultVec.x;
            dir[1] = g_DefaultVec.y;
            dir[2] = g_DefaultVec.z;
            return;
        }
        float tx = target[0] - centre[0];
        float py = pos[1] - centre[1];
        float ty = target[1] - centre[1];
        float pz = pos[2] - centre[2];
        float px = pos[0] - centre[0];
        float r2 = (px * px + pz * pz) + py * py;
        float tz = target[2] - centre[2];
        float r = sqrtf(r2);
        float dirY = dir[1];
        float inv = 1.0f / r;
        float nz = pz * inv;
        float ny = py * inv;
        float nx = inv * px;
        float d = (ny * dirY + nz * dir[2]) + dir[0] * nx;
        float perpX = dir[0] - nx * d;
        float perpY = dirY - ny * d;
        float perpZ = dir[2] - nz * d;
        float tr = sqrtf(ty * ty + (tz * tz + tx * tx));
        float t2 = ty * ty + (tz * tz + tx * tx);
        float s = 0.0f;
        ApproachScalar(&s, &d, tr - r, p6, params[0] * p7, dt);
        float newZ = nz * s + pos[2];
        float newY = ny * s + pos[1];
        float newX = nx * s + pos[0];
        pos[0] = newX;
        pos[2] = newZ;
        pos[1] = newY;
        float len = sqrtf(newX * newX + (newY * newY + newZ * newZ));
        volatile float i1v = 1.0f / sqrtf(r2 + 1e-08f);
        float i1 = i1v;
        volatile float i2v = 1.0f / sqrtf(t2 + 1e-08f);
        float i2 = i2v;
        float c = ((i2 * tx) * (i1 * px) + (tz * i2) * (pz * i1)) + (ty * i2) * (py * i1);
        c = ClampF(c, -1.0f, 1.0f);
        float ang = acosf(c);
        float* m = &tr;
        if (r <= tr) m = &r;
        float dot = ((tx - px) * nx + (tz - pz) * nz) + (ty - py) * ny;
        float qx = (tx - px) - dot * nx;
        float qz = (tz - pz) - nz * dot;
        float qy = (ty - py) - ny * dot;
        float arc = *m * ang;
        float ql = sqrtf(qy * qy + (qz * qz + qx * qx));
        float pl = sqrtf(perpY * perpY + (perpZ * perpZ + perpX * perpX));
        float ox, oy, oz;
        if (ql > 1.5258789e-05f) {
            float k = arc / ql;
            ox = qx * k; oy = qy * k; oz = qz * k;
        } else if (pl > 1.5258789e-05f) {
            float k = arc / pl;
            ox = perpX * k; oy = perpY * k; oz = perpZ * k;
        } else {
            float* o = OrthogonalVector(&qx, &nx);
            ox = o[0] * arc; oy = o[1] * arc; oz = o[2] * arc;
        }
        float v[3] = { g_DefaultVec.x, g_DefaultVec.y, g_DefaultVec.z };
        float off[3] = { ox, oy, oz };
        float vel[3] = { perpX, perpY, perpZ };
        ApproachVector(v, vel, off, p6, params[1] * p7, dt);
        v[2] = v[2] + pos[2];
        v[1] = v[1] + pos[1];
        v[0] = v[0] + pos[0];
        float f = 1.0f / sqrtf((v[0] * v[0] + (v[1] * v[1] + v[2] * v[2])) + 1e-08f);
        pos[0] = (v[0] * f) * len;
        pos[1] = (v[1] * f) * len;
        pos[2] = (v[2] * f) * len;
        dir[0] = nx * d + vel[0];
        dir[1] = ny * d + vel[1];
        dir[2] = nz * d + vel[2];
    }
}
