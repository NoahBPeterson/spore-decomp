// Slice s00af6bf0: planet-surface path tracer (iterative ray march that follows hits around the planet).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <float.h>

struct Vec3 { float x, y, z; };

// 0x100-byte trace result record. Real layout: id +0x20, normal +0x34, flag +0x40, dist +0x44,
// then the hit-point record at +0xf0 (w flag) / +0xf4 (position).
struct Hit {
    char  p0[0x20];
    int   id;
    char  p1[0x34 - 0x24];
    Vec3  normal;
    bool  flag;
    char  p2[3];
    float dist;
    char  p3[0xf0 - 0x48];
    float w;
    Vec3  pos;

    Hit();                          // 0x00af4da0 (default-initialises the record)
    void CopyBase(const Hit* src);  // 0x00af1910 (copies bytes 0..0xef)
    void CopyAll(const Hit* src);   // 0x00af3e00 (CopyBase + w/pos)
};

namespace SP {
void* PlanetModel();                                  // 0x00b3d350 returns the global model
float* normalized_safe(float* out, const float* v);   // 0x00449c20
}

extern Vec3 gInvalidVec;                              // 0x0167ae24 sentinel vector

typedef float (*CastFn)(void* ctx, const float* origin, const float* dir, float maxDist, Hit* hit);

// 0x00af5b40: probe/refine a hit; returns nonzero on success
char ProbeHit(Hit* hit, const float* a, const float* b, bool flag, char* outFlag, float p3);  // 0x00af5b40
// 0x00af6400: sweep to one side, fills 'outArr' with up to 'count' hits, returns the count
int SweepSide(void* ctx, float p3, CastFn cast, const float* a, const float* b, float side,
              Hit* hit, Hit* outArr, int count, Hit* outBase, int idx, float* outDist, int extra);  // 0x00af6400

static inline bool IsInvalid(const Vec3& v)
{
    return v.x == gInvalidVec.x && v.y == gInvalidVec.y && v.z == gInvalidVec.z;
}

static inline void StoreHitPoint(Hit* dst, const Hit* src)
{
    dst->CopyBase(src);
    dst->w = src->w;
    dst->pos.x = src->pos.x;
    dst->pos.y = src->pos.y;
    dst->pos.z = src->pos.z;
}

// @ 0x00af6bf0
int TracePlanetPath(void* ctx, const float* initDir, float p3, CastFn cast, const float* start,
                    const float* end, Hit* out, int maxHits, int* state, float* outLen,
                    const Hit* prev, int extra)
{
    Vec3 pos, target, dir, d;
    float total, len, inv, dist;
    int n, iter;
    bool cont;
    char cs;

    SP::PlanetModel();
    pos.x = start[0]; pos.y = start[1]; pos.z = start[2];
    target.x = end[0]; target.y = end[1]; target.z = end[2];
    cont = true;
    *state = 4;
    total = 0.0f;
    Hit firstHit;                       // constructed after the setup stores, as in the original
    n = 0;
    iter = 0;

    if (0 < maxHits) {
        while (cont) {
            Hit hit;
            d.z = target.z - pos.z;
            d.y = target.y - pos.y;
            d.x = target.x - pos.x;
            hit.w = 0.0f;
            len = sqrtf(d.x * d.x + (d.y * d.y + d.z * d.z));
            inv = 1.0f / (len + 1.5258789e-05f);
            dir.x = inv * d.x;
            dir.y = inv * d.y;
            dir.z = inv * d.z;
            dist = cast(ctx, &pos.x, &dir.x, len, &hit);
            hit.dist = dist;
            if (len < dist) {
                cont = false;
                *state = 0;
                goto next;
            }
            hit.pos.x = dir.x * dist + pos.x;
            hit.pos.y = dir.y * dist + pos.y;
            hit.pos.z = dir.z * dist + pos.z;

            if (hit.id == 0) {
                total = dist + total;
                StoreHitPoint(&out[n], &hit);
                n = n + 1;
                if (*state != 5)
                    *state = 3;
                break;
            }
            if (n + 1 == maxHits) {
                total = dist + total;
                hit.w = 1.0f;
                out[n].CopyAll(&hit);
                n = n + 1;
                *state = 5;
                break;
            }
            if (iter == 0)
                firstHit.CopyAll(&hit);
            cs = 0;
            bool okNormal;
            if (!hit.flag || IsInvalid(hit.normal))
                okNormal = true;
            else
                okNormal = false;
            if (ProbeHit(&hit, &pos.x, &target.x, okNormal, &cs, p3) == 0) {
                Hit negHits[12];
                Hit posHits[12];
                float bestNeg = FLT_MAX;
                float bestPos = FLT_MAX;
                float prevAdj = 0.0f;
                int cntNeg, cntPos;
                float chosen;

                if (prev != 0) {
                    const Hit* p = prev;
                    for (int i = 0; i < maxHits; ++i, ++p) {
                        if (p->id == hit.id && IsInvalid(hit.normal)) {
                            prevAdj = p->w;
                            break;
                        }
                    }
                }
                cntNeg = SweepSide(ctx, p3, cast, &pos.x, &target.x, -1.0f, &hit, negHits,
                                   maxHits - n, out, n, &bestNeg, extra);
                cntPos = SweepSide(ctx, p3, cast, &pos.x, &target.x, 1.0f, &hit, posHits,
                                   maxHits - n, out, n, &bestPos, extra);
                if (prevAdj == -1.0f && bestNeg != FLT_MAX)
                    bestPos = bestPos * 2.0f;
                if (prevAdj == 1.0f && bestPos != FLT_MAX)
                    bestNeg = bestNeg * 2.0f;

                if ((initDir[0] != gInvalidVec.x || initDir[1] != gInvalidVec.y ||
                     initDir[2] != gInvalidVec.z) && n == 0) {
                    float adj;
                    if (0 < cntNeg) {
                        Vec3 v, nd;
                        float l, il;
                        float tmp[3];
                        v.z = negHits[0].pos.z - pos.z;
                        v.y = negHits[0].pos.y - pos.y;
                        v.x = negHits[0].pos.x - pos.x;
                        l = sqrtf(v.x * v.x + (v.y * v.y + v.z * v.z));
                        il = 1.0f / (l + 1.5258789e-05f);
                        nd.x = il * v.x;
                        nd.y = il * v.y;
                        nd.z = il * v.z;
                        if (IsInvalid(negHits[0].normal)) {
                            adj = -(((initDir[2] * nd.z + initDir[1] * nd.y) + initDir[0] * nd.x) * l);
                        } else {
                            float* nn = SP::normalized_safe(tmp, &negHits[0].normal.x);
                            adj = ((nn[2] * nd.z + nn[1] * nd.y) + nn[0] * nd.x) * (l + 1.0f);
                        }
                        bestNeg = adj + bestNeg;
                    }
                    if (0 < cntPos) {
                        Vec3 v, nd;
                        float l, il;
                        float tmp[3];
                        v.z = posHits[0].pos.z - pos.z;
                        v.y = posHits[0].pos.y - pos.y;
                        v.x = posHits[0].pos.x - pos.x;
                        l = sqrtf(v.x * v.x + (v.y * v.y + v.z * v.z));
                        il = 1.0f / (l + 1.5258789e-05f);
                        nd.x = il * v.x;
                        nd.y = il * v.y;
                        nd.z = il * v.z;
                        if (IsInvalid(posHits[0].normal)) {
                            adj = -(((initDir[2] * nd.z + initDir[1] * nd.y) + initDir[0] * nd.x) * l);
                        } else {
                            float* nn = SP::normalized_safe(tmp, &posHits[0].normal.x);
                            adj = ((nn[2] * nd.z + nn[1] * nd.y) + nn[0] * nd.x) * (l + 1.0f);
                        }
                        bestPos = adj + bestPos;
                    }
                }

                if (bestPos <= bestNeg) {
                    if (bestPos == FLT_MAX) {
                        char r = ProbeHit(&hit, &pos.x, &pos.x, false, 0, 0.0f);
                        cont = false;
                        if (r == 0)
                            *state = 0;
                        else
                            *state = 1;
                        goto next;
                    }
                    chosen = bestPos;
                    if (0 < cntPos) {
                        Hit* dst = out + n;
                        const Hit* src = posHits;
                        n += cntPos;
                        do {
                            StoreHitPoint(dst, src);
                            ++dst;
                            ++src;
                        } while (--cntPos != 0);
                    }
                } else {
                    chosen = bestNeg;
                    if (0 < cntNeg) {
                        Hit* dst = out + n;
                        const Hit* src = negHits;
                        n += cntNeg;
                        do {
                            StoreHitPoint(dst, src);
                            ++dst;
                            ++src;
                        } while (--cntNeg != 0);
                    }
                }
                total = chosen + total;
                pos.x = out[n - 1].pos.x;
                pos.y = out[n - 1].pos.y;
                pos.z = out[n - 1].pos.z;
            } else {
                *state = 5;
                if (!okNormal || cs == 0 || iter > 12) {
                    total = dist + total;
                    hit.w = 1.0f;
                    out[n].CopyAll(&hit);
                    n = n + 1;
                    break;
                }
                if (iter == 0 && ProbeHit(&hit, end, &pos.x, true, &cs, p3) != 0 && !hit.flag) {
                    hit.pos.x = pos.x;
                    hit.pos.y = pos.y;
                    hit.pos.z = pos.z;
                    hit.w = 1.0f;
                    total = sqrtf((pos.z - start[2]) * (pos.z - start[2]) +
                                  (pos.y - start[1]) * (pos.y - start[1]) +
                                  (pos.x - start[0]) * (pos.x - start[0])) + total;
                    out[n].CopyAll(&hit);
                    n = n + 1;
                }
            }
next:
            iter = iter + 1;
            if (maxHits <= n)
                break;
        }
    }

    if ((unsigned int)(*state - 4) < 2) {
        float a0 = start[0], a1 = start[1], a2 = start[2];
        float b0 = end[0], b1 = end[1], b2 = end[2];
        float dx = b0 - a0;
        float dy = b1 - a1;
        float dz = b2 - a2;
        float il = 1.0f / sqrtf((dy * dy + (dz * dz + dx * dx)) + 1e-08f);
        float ndy = il * dy;
        float ndz = il * dz;
        float ndx = il * dx;
        float ib = 1.0f / sqrtf((b0 * b0 + (b1 * b1 + b2 * b2)) + 1e-08f);
        float nx = (ib * b2) * ndy - (ib * b1) * ndz;
        float ny = (ib * b0) * ndz - ndx * (ib * b2);
        float nz = ndx * (ib * b1) - (ib * b0) * ndy;
        float R = firstHit.dist;
        float planeD = -(((a2 + R * ndz) * nz + (a1 + R * ndy) * ny) + (ndx * R + a0) * nx);
        float rsq = R * R;
        int k = 1;
        if (1 < n) {
            const float* cur = &out[1].pos.z;
            const Hit* pv = out;
            do {
                float py = pv->pos.y;
                float denom = ((*cur - pv->pos.z) * nz + (cur[-1] - py) * ny) + (cur[-2] - pv->pos.x) * nx;
                if (denom != 0.0f) {
                    float t = -((((pv->pos.z * nz + py * ny) + nx * pv->pos.x) + planeD) / denom);
                    if (0.0f <= t && t <= 1.0f) {
                        float ez = *cur - pv->pos.z;
                        float qy = (pv->pos.y + t * (cur[-1] - pv->pos.y)) - a1;
                        float qz = (pv->pos.z + t * ez) - a2;
                        float qx = ((cur[-2] - pv->pos.x) * t + pv->pos.x) - a0;
                        if (((qx * qx + qz * qz) + qy * qy < rsq) ||
                            ((qz * ndz + qy * ndy) + qx * ndx < 0.0f)) {
                            float s, vx, vy, vz, iv;
                            total = R;
                            *state = 5;
                            firstHit.w = 1.0f;
                            s = 0.0f;
                            if (0.0f <= R - p3)
                                s = R - p3;
                            vz = end[2] - start[2];
                            vy = end[1] - start[1];
                            vx = end[0] - start[0];
                            n = 1;
                            iv = 1.0f / sqrtf((vx * vx + (vy * vy + vz * vz)) + 1e-08f);
                            firstHit.pos.x = start[0] + s * (iv * vx);
                            firstHit.pos.y = start[1] + s * (vy * iv);
                            firstHit.pos.z = start[2] + s * (vz * iv);
                            out[0].CopyBase(&firstHit);
                            out[0].w = firstHit.w;
                            out[0].pos.x = firstHit.pos.x;
                            out[0].pos.y = firstHit.pos.y;
                            out[0].pos.z = firstHit.pos.z;
                            break;
                        }
                    }
                }
                ++k;
                pv = out + (k - 1);
                cur += 0x40;
            } while (k < n);
        }
    }
    if (outLen != 0)
        *outLen = total;
    return n;
}
// --- equivalence checker address annotations
    void ProbeHit(...); // 0x00af5b40
    void SweepSide(...); // 0x00af6400

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
