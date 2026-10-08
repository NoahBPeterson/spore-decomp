// s00c015e0: obstacle/steering avoidance pass (0xc015e0). Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>
#include <stdlib.h>
#include <new>

struct SteerEntry {            // 0x2c bytes; the constructor only sets mKind2 = 1
    int type;
    int flag;
    float x, y, z;
    float w;
    uint32_t pad[5];
    SteerEntry() { flag = 1; }
};

struct SteerVec {
    SteerEntry* mpBegin;
    SteerEntry* mpEnd;
    SteerEntry* mpCap;
    void DoInsertValue(SteerEntry* pos, const SteerEntry& v);
    inline void push_back() {
        if (mpEnd < mpCap) {
            ::new (mpEnd++) SteerEntry();
        } else {
            SteerEntry e;
            DoInsertValue(mpEnd, e);
        }
    }
};

struct SteerCtx {
    float px, py, pz;
    uint32_t pad0[5];
    float tx, ty, tz;
    uint32_t pad1[0x15];
    struct Src {
        virtual void s0();
        virtual void s1();
        virtual void s2();
        virtual void s3();
        virtual void s4();
        virtual void s5();
        virtual void s6();
        virtual void s7();
        virtual void s8();
        virtual void s9();
        virtual void s10();
        virtual void s11();
        virtual void s12();
        virtual void s13();
        virtual void s14();
        virtual void s15();
        virtual void s16();
        virtual void s17();
        virtual void s18();
        virtual void s19();
        virtual void s20();
        virtual void s21();
        virtual void s22();
        virtual void s23();
        virtual void s24();
        virtual void s25();
        virtual void s26();
        virtual void s27();
        virtual void s28();
        virtual float Radius(); } *src;   // +0x80
    SteerVec out;                                              // +0x84
};

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, r; };

struct PointVec {
    Vec3* mpBegin; Vec3* mpEnd; Vec3* mpCap;
    PointVec() { mpBegin = 0; mpEnd = 0; mpCap = 0; }
    ~PointVec() { if (mpBegin) free(mpBegin); }
};

struct Zone {
    uint32_t pad[0x258 / 4];
    float rMin;     // +0x258
    float rMax;     // +0x25c
    void FillPoints(PointVec* v);
};

struct Avoider {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual Vec3* GetPosition(Vec3* out);   // +0x58
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual Zone* GetZone();                // +0x6c
    uint32_t pad[14];
    Vec4* mpObsBegin;                       // +0x3c
    Vec4* mpObsEnd;                         // +0x40
    void Avoid(SteerCtx* ctx);
};

static inline float len3(float x, float y, float z) { return sqrtf(x * x + z * z + y * y); }

void Avoider::Avoid(SteerCtx* ctx)
{
    Vec3 A, B, dir, an;
    A.x = ctx->px; A.y = ctx->py; A.z = ctx->pz;
    B.x = ctx->tx; B.y = ctx->ty; B.z = ctx->tz;
    const float selfR = ctx->src->Radius();

    dir.x = B.x - A.x; dir.y = B.y - A.y; dir.z = B.z - A.z;
    float inv = 1.0f / sqrtf(dir.x * dir.x + dir.z * dir.z + dir.y * dir.y + 1e-8f);
    dir.x = inv * dir.x; dir.y = dir.y * inv; dir.z = dir.z * inv;
    float inv2 = 1.0f / sqrtf(A.x * A.x + A.y * A.y + A.z * A.z + 1e-8f);
    an.x = A.x * inv2; an.y = A.y * inv2; an.z = A.z * inv2;

    int count = (int)(mpObsEnd - mpObsBegin);
    for (int i = 0; i < count; ++i) {
        const Vec4& o = mpObsBegin[i];
        float ox = o.x, oy = o.y, oz = o.z, orad = o.r;
        float ex = ox - A.x, ey = oy - A.y, ez = oz - A.z;
        float d2 = ex * ex + ez * ez + ey * ey;
        float gap = (sqrtf(d2) - orad) - selfR;
        if (gap > 0.0f) {
            if (gap < 4.0f) {
            if (ex * dir.x + ez * dir.z + ey * dir.y > 0.0f) {
                float fx = ox - B.x, fy = oy - B.y, fz = oz - B.z;
                float d2b = fx * fx + fz * fz + fy * fy;
                float db = sqrtf(d2b);
                if (db >= 1.0f) {
                    bool skip = false;
                    if (db < orad + 4.0f) {
                        float i1 = 1.0f / sqrtf(d2b + 1e-8f);
                        float i0 = 1.0f / sqrtf(d2 + 1e-8f);
                        if ((ez * i0) * (fz * i1) + (ey * i0) * (fy * i1) + (i0 * ex) * (i1 * fx) > 0.9f)
                            skip = true;
                    }
                    if (!skip) {
                        ctx->out.push_back();
                        SteerEntry* e = ctx->out.mpEnd - 1;
                        float cx = an.z * dir.y - an.y * dir.z;
                        float cy = dir.z * an.x - an.z * dir.x;
                        float cz = an.y * dir.x - dir.y * an.x;
                        e->type = 2;
                        if (ez * cz + ey * cy + ex * cx > 0.0f) {
                            cx *= -1.0f; cy *= -1.0f; cz *= -1.0f;
                        }
                        float s = 4.0f - gap;
                        e->x = cx * s; e->y = cy * s; e->z = cz * s;
                        if (gap < 1.0f)
                            e->flag = 2;
                    }
                }
            }
            }
        } else {
            float fx = ox - B.x, fy = oy - B.y, fz = oz - B.z;
            if (orad < sqrtf(fx * fx + fy * fy + fz * fz)) {
                ctx->out.push_back();
                SteerEntry* e = ctx->out.mpEnd - 1;
                e->type = 4;
                e->x = ox; e->y = oy; e->z = oz;
                e->flag = 2;
                e->w = 2.0f;
            }
        }
    }

    Zone* zone = GetZone();
    if (!zone) return;
    Vec3 tmp;
    Vec3* pos = GetPosition(&tmp);
    float r1 = zone->rMin;
    float pdx = A.x - pos->x, pdy = A.y - pos->y, pdz = A.z - pos->z;
    float dist = sqrtf(pdx * pdx + pdz * pdz + pdy * pdy);
    if (!(dist > r1 - 4.0f)) return;
    float r2 = zone->rMax;
    if (!(r2 + 4.0f > dist)) return;

    static PointVec pts;
    zone->FillPoints(&pts);
    int n = (int)(pts.mpEnd - pts.mpBegin);
    int j = 0;
    if (n > 0) {
        float thresh = r2 - r1;
        const Vec3* p = pts.mpBegin;
        do {
            float qx = A.x - p->x, qy = A.y - p->y, qz = A.z - p->z;
            if (thresh > sqrtf(qx * qx + qz * qz + qy * qy)) break;
            ++j; ++p;
        } while (j < n);
    }
    if (j == n) {
        ctx->out.push_back();
        SteerEntry* e = ctx->out.mpEnd - 1;
        e->type = 4;
        Vec3* q = GetPosition(&tmp);
        e->x = tmp.x; e->y = tmp.y; e->z = tmp.z;
        (void)q;
        if (r1 > dist) {
            e->w = (4.0f - (r1 - dist)) * 0.25f;
        } else if (dist > r2) {
            e->w = (4.0f - (r2 - dist)) * 0.25f;
        } else {
            e->w = -1.0f;
        }
    }
}
