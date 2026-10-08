// Slice s00af6400: planet-surface "sweep to one side" (SweepSide, called from TracePlanetPath 0x00af6bf0).
// Marches a point from `start` toward `end` through a cast callback, hitting shapes (Hit records, 0x100 bytes,
// shape type at +0x24). Each accepted step is stored in `out[n]`; returns the count, total length in *outDist
// (FLT_MAX on failure).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <float.h>
#include <math.h>

struct Vec3 { float x, y, z; };

// 0x100-byte trace/shape record (16-byte aligned: the original frame is aligned).
__declspec(align(16)) struct Hit {
    uint32_t p00[8];     // +0x00
    int      id;         // +0x20
    int      type;       // +0x24 shape type: 0 sphere, 1 box, 2 polyline, 3 shell
    Vec3     center;     // +0x28
    uint32_t p34[(0x40 - 0x34) / 4];
    int      flag;       // +0x40
    uint32_t p44[(0x54 - 0x44) / 4];
    float    radius;     // +0x54
    uint32_t box[(0x70 - 0x58) / 4];     // +0x58
    uint32_t xform[(0xa8 - 0x70) / 4];   // +0x70
    uint32_t meshPt[(0xb4 - 0xa8) / 4];  // +0xa8
    uint32_t vertCount;  // +0xb4
    Vec3*    verts;      // +0xb8
    uint32_t pBC[(0xc8 - 0xbc) / 4];
    float    extraRadius;// +0xc8
    uint32_t pCC[(0xf0 - 0xcc) / 4];
    float    w;          // +0xf0
    Vec3     pos;        // +0xf4
    uint32_t pFC;

    Hit();                       // 0x00af4da0
    Hit(const Hit& src);         // 0x00af6250
    void Copy(const Hit* src);   // 0x00af1910
};

typedef float (*CastFn)(void* ctx, const Vec3* origin, const Vec3* dir, float maxDist, Hit* hit);

bool  Steer(const Vec3* pos, const Vec3* end, Vec3* outPt, float side, float margin, Hit* hit, int extra);  // 0x00af1a90 (cdecl)
char  ProbeHit(Hit* hit, const Vec3* a, const Vec3* b, int push, char* moved, float margin);                // 0x00af5b40 (cdecl)
bool  SweepSphere(Hit* hit, int id, const Vec3* pos, const Vec3* center, const Vec3* dir, float* len,
                  float margin, float radius, int flag, Hit* hit2);                                         // 0x00af17f0 (cdecl)
bool  SweepBox(Hit* hit, int id, const Vec3* pos, const Vec3* center, const Vec3* dir, float* len,
               float margin, const void* xform, const void* box, int flag, Hit* hit2);                       // 0x00af5060 (cdecl)
bool  SweepMesh(Hit* hit, int id, const Vec3* pos, const Vec3* center, const Vec3* end, const Vec3* dir,
                float* len, float margin, const void* xform, const void* meshPt, float meshRadius,
                const Vec3* verts, uint32_t nVerts, float radius, int flag, Hit* hit2);                     // 0x00af5400 (cdecl)

// @ 0x00af6400
int SweepSide(void* ctx, float margin, CastFn cast, const Vec3* start, const Vec3* end, float side,
              const Hit* src, Hit* out, int count, const Hit* prev, int prevCount, float* outDist, int extra)
{
    Vec3 pos, tgt, dir, back;
    float len, c, t;
    int n = 0;

    pos.x = start->x; pos.y = start->y; pos.z = start->z;
    Hit A(*src);
    Hit B;
    *outDist = 0.0f;

    if (0 < count) {
        Hit* slot = out;
        int ii = 0;
        do {
            int k = 0;
            do {
                if (!Steer(&pos, end, &tgt, side, margin, &A, extra)) {
                    *outDist = FLT_MAX;
                    return n;
                }
                Vec3 d;
                d.x = tgt.x - pos.x;
                d.z = tgt.z - pos.z;
                d.y = tgt.y - pos.y;
                len = sqrtf(d.y * d.y + (d.z * d.z + d.x * d.x));
                float inv = 1.0f / (len + 1.5258789e-05f);
                dir.x = inv * d.x;
                dir.y = d.y * inv;
                dir.z = d.z * inv;
                if (A.type == 0 && Steer(end, &pos, &back, -side, margin, &A, extra)) {
                    len = sqrtf((tgt.y - back.y) * (tgt.y - back.y) +
                                ((tgt.z - back.z) * (tgt.z - back.z) + (tgt.x - back.x) * (tgt.x - back.x))) * 0.5f + len;
                    tgt.x = dir.x * len + pos.x;
                    tgt.y = dir.y * len + pos.y;
                    tgt.z = dir.z * len + pos.z;
                }
                c = cast(ctx, &pos, &dir, len, &B);
                if (B.id == 0)
                    break;
                for (int j = 0; j < prevCount; ++j) {
                    if (prev[j].id == B.id && prev[j].w != side) {
                        *outDist = FLT_MAX;
                        return 0;
                    }
                }
                if (B.id != A.id) {
                    Vec3 e;
                    e.x = end->x; e.y = end->y; e.z = end->z;
                    if (ProbeHit(&B, &pos, &e, 0, 0, margin)) {
                        t = 0.0f;
                        if (0.0f <= c - margin)
                            t = c - margin;
                        if (0.0f < t) {
                            tgt.x = t * dir.x + pos.x;
                            Hit* s = out + n;
                            tgt.y = dir.y * t + pos.y;
                            tgt.z = dir.z * t + pos.z;
                            *outDist = *outDist + t;
                            s->pos.x = tgt.x;
                            s->pos.y = tgt.y;
                            s->pos.z = tgt.z;
                            ++n;
                            s->Copy(&B);
                            s->w = side;
                        }
                        if (n != 0)
                            return n;
                        *outDist = FLT_MAX;
                        return 0;
                    }
                }
                A.Copy(&B);
                ++k;
            } while (k < 12);

            if (k == 12) {
                *outDist = FLT_MAX;
                return 0;
            }
            if (0.0f < len) {
                ++n;
                *outDist = *outDist + len;
                slot->pos.x = tgt.x;
                slot->pos.y = tgt.y;
                slot->pos.z = tgt.z;
                Hit* s = slot;
                ++slot;
                s->Copy(&A);
                s->w = side;
            }

            int idBefore = A.id;
            Vec3 prevPos = pos;
            Vec3 rem;
            rem.x = end->x - tgt.x;
            rem.y = end->y - tgt.y;
            rem.z = end->z - tgt.z;
            float mx = tgt.x - prevPos.x;
            float my = tgt.y - prevPos.y;
            float mz = tgt.z - prevPos.z;
            pos = tgt;
            Vec3 remDir = rem;
            if (!((rem.z * mz + rem.y * my) + rem.x * mx < 0.0f)) {
                len = sqrtf(rem.x * rem.x + (rem.y * rem.y + rem.z * rem.z));
                float inv = 1.0f / (len + 1.5258789e-05f);
                remDir.x = inv * rem.x;
                remDir.y = rem.y * inv;
                remDir.z = rem.z * inv;
                bool ok;
                switch (A.type) {
                case 0:
                    ok = SweepSphere(&A, A.id, &pos, &A.center, &remDir, &len, margin, A.radius, A.flag, &A);
                    break;
                case 1:
                    ok = SweepBox(&A, A.id, &pos, &A.center, &remDir, &len, margin, A.xform, A.box, A.flag, &A);
                    break;
                case 2:
                    ok = SweepMesh(&A, A.id, &pos, &A.center, end, &remDir, &len, margin, A.xform, A.meshPt,
                                   A.extraRadius, A.verts, A.vertCount, A.radius, A.flag, &A);
                    break;
                case 3: {
                    float r = cast(ctx, &pos, &remDir, len, &A);
                    ok = (r <= len && A.id == idBefore);
                    if (ok)
                        goto next;
                    break;
                }
                default:
                    ok = false;
                    break;
                }
                if (!ok) {
                    if (n == 0) {
                        *outDist = FLT_MAX;
                        return 0;
                    }
                    goto finish;
                }
            }
        next:
            ++ii;
        } while (ii < count);
        if (n != 0) {
        finish:
            float fx = end->x - pos.x, fy = end->y - pos.y, fz = end->z - pos.z;
            *outDist = sqrtf((fz * fz + fy * fy) + fx * fx) + *outDist;
            return n;
        }
    }
    *outDist = FLT_MAX;
    return 0;
}
