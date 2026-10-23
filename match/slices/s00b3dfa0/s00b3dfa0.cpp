// Slice s00b3dfa0 -- SPGonzago planet-model geometry helpers.  This VA range sits in a modmap gap
// between SPGonzagoAccessor.obj and SPCinematicManager.obj; the module is most likely SPPlanetModel.obj
// (no migrated src/game counterpart exists yet, so this is a standalone slice).
// Segment/segment and segment/polygon closest-point, sphere/sphere contact, and surface-orientation
// helpers.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int i32;

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

// ---- original data constants (relocations; masked by chk) ---------------------------------------
extern const float   g_eps;      // 0x01461154  1.5258789e-05f
extern const float   g_one;      // 0x01485720  1.0f
extern const Vector3 g_invalid;  // 0x0167eb8c
extern const Vector3 g_default;  // 0x015696a4

// ---- clamp helper (SSE maxss/minss; see s0043e3f0) ----------------------------------------------
inline float Dot(const Vector3& u, const Vector3& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

// ---- forward declarations of callees -------------------------------------------------------------
struct cPlanetModel;
cPlanetModel* PlanetModel();                                                     // 0x00b3d350
void RebuildStaticCollision();                                                   // 0x00b5a750
void FUN_00b55680(void* obj, int a, int b);                                      // 0x00b55680
void FUN_00b3e620(void* self, int mode, int a3, int a4, int a5, int a6);         // 0x00b3e620
int  __stdcall FUN_00b3e860(const Vector3* p, const Vector3* a, const Vector3* b,
                            Vector3* out1, Vector3* out2);                       // 0x00b3e860

// ---- cPlanetModel surface helpers ----------------------------------------------------------------
struct cPlanetModel {
    Vector3*    ProjectToSurface(Vector3* out, const Vector3* in, int a3, int a4, int a5, int a6); // 0x00b82df0
    float       GetHeight(float* out, int a2);                                   // 0x00b7e430
    Quaternion* BuildSurfaceOrientation(Quaternion* out, const Vector3* v, const Quaternion* q);   // 0x00b7f1f0
    Quaternion* BuildPitchedSurfaceOrientation(Quaternion* out, const Vector3* v, const Quaternion* q, float f); // 0x00b7f2b0
    Quaternion* BuildSurfaceNormalOrientation(Quaternion* out, const Vector3* v, const Quaternion* q, float f);  // 0x00b7f320
};

// ---- vtable object used by 00b3e620 (slots 0x2c / 0x30 / 0x38 / 0x3c) ---------------------------
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16

struct VObj {
    PV8 PV2 PV                              // 0x00 .. 0x28
    virtual Vector3*    GetPos();           // 0x2c
    virtual Quaternion* GetQuat();          // 0x30
    virtual void        v34();              // 0x34
    virtual void        SetPos(Vector3*);   // 0x38
    virtual void        SetQuat(Quaternion*); // 0x3c
};

// ---- vtable object used by 00b3e5e0 (slot 0xb8) --------------------------------------------------
struct CAvoider;
struct CAvoiderOwner {
    PV32 PV8 PV4 PV2                        // 0x00 .. 0xb4
    virtual CAvoiderOwner* Find(int id);    // 0xb8
    CAvoider* GetAvoider();                 // 0x00c23290
};
struct CAvoider {
    void Avoid(void* self);                 // 0x00c015e0
};

// ---- shape / contact used by 00b3e3e0 ------------------------------------------------------------
struct Shape {
    void  GetCenter(Vector3& out) const;    // 0x00b3d9c0
    float GetRadius() const;                // 0x00b3d630
};

struct Contact {
    Vector3 p;               // 0x000
    u8      pad0[0xc0 - 0x0c];
    Vector3 q;               // 0x0c0
    u8      pad1[0x180 - 0x0cc];
    u32     flag;            // 0x180
    Vector3 n;               // 0x184
    float   d;               // 0x190
    Vector3 e;               // 0x194
};

// =================================================================================================
// @ 0x00b3dfa0
float FUN_00b3dfa0(const Vector3* p1, const Vector3* p2, const Vector3* p3, const Vector3* p4,
                   Vector3* out1, Vector3* out2)
{
    float d1x = p2->x - p1->x, d1y = p2->y - p1->y, d1z = p2->z - p1->z;
    float d2x = p4->x - p3->x, d2y = p4->y - p3->y, d2z = p4->z - p3->z;
    float rx = p1->x - p3->x, ry = p1->y - p3->y, rz = p1->z - p3->z;

    float A = d1z * d1z + d1x * d1x + d1y * d1y;
    float B = d2z * d1z + d2y * d1y + d2x * d1x;
    float C = d2z * d2z + d2y * d2y + d2x * d2x;
    float D = rz * d1z + ry * d1y + rx * d1x;
    float E = rz * d2z + ry * d2y + rx * d2x;

    float denom = C * A - B * B;

    float sNum = 0.0f, sDen = denom, tNum = E, tDen = C;

    if (denom >= g_eps) {
        float s1 = E * B - D * C;
        if (s1 >= 0.0f) {
            sNum = s1;
            tNum = E * A - D * B;
            if (denom < s1) {
                sNum = denom;
                tNum = E + B;
                tDen = C;
            }
        } else {
            sNum = 0.0f;
            tNum = E;
            tDen = C;
        }
    } else {
        sNum = 0.0f;
        sDen = 1.0f;
        tNum = E;
        tDen = C;
    }

    if (tNum >= 0.0f) {
        if (tNum > tDen) {
            sNum = B - D;
            tNum = tDen;
            goto clamp_s;
        }
    } else {
        sNum = -D;
        tNum = 0.0f;
        goto clamp_s;
    }
    goto done;

clamp_s:
    if (sNum >= 0.0f) {
        float old = sDen;
        sDen = A;
        if (A < sNum) {
            sNum = old;
            sDen = old;
        }
    } else {
        sNum = 0.0f;
    }

done:
    float s = (fabsf(sNum) >= g_eps) ? sNum / sDen : 0.0f;
    float t = (fabsf(tNum) >= g_eps) ? tNum / tDen : 0.0f;

    if (out1) {
        out1->x = p1->x + d1x * s;
        out1->y = d1y * s + p1->y;
        out1->z = p1->z + d1z * s;
    }
    if (out2) {
        out2->x = p3->x + d2x * t;
        out2->y = p3->y + d2y * t;
        out2->z = p3->z + d2z * t;
    }

    float ex = (d1x * s + rx) - d2x * t;
    float ey = (d1y * s + ry) - d2y * t;
    float ez = (d1z * s + rz) - d2z * t;
    return sqrtf(ey * ey + (ez * ez + ex * ex));
}

// =================================================================================================
// @ 0x00b3e3e0
void FUN_00b3e3e0(const Shape* a, const Shape* b, Contact* out)
{
    Vector3 c1, c2;
    a->GetCenter(c1);
    b->GetCenter(c2);
    float r1 = a->GetRadius();
    float r2 = b->GetRadius();

    float dx = c2.x - c1.x, dy = c2.y - c1.y, dz = c2.z - c1.z;
    float sum = r1 + r2;
    float dist2 = dz * dz + dy * dy + dx * dx;
    if (sum * sum <= dist2)
        return;

    float dist = sqrtf(dist2);
    float overlap = sum - dist;
    float inv = g_one / (dist + g_eps);

    float nx = dx * inv, ny = dy * inv, nz = dz * inv;

    float m1 = r1 - overlap;
    out->p.x = nx * m1 + c1.x;
    out->p.y = ny * m1 + c1.y;
    out->p.z = nz * m1 + c1.z;

    float m2 = r2 - overlap;
    out->q.x = c2.x - nx * m2;
    out->q.y = c2.y - ny * m2;
    out->q.z = c2.z - nz * m2;

    out->flag = 1;
    out->n.x = nx;
    out->n.y = ny;
    out->n.z = nz;
    out->d = 0.0f;
    out->e.x = nx * overlap;
    out->e.y = ny * overlap;
    out->e.z = nz * overlap;
}

// =================================================================================================
// @ 0x00b3e5e0
void FUN_00b3e5e0(void* self)
{
    CAvoiderOwner* p = *(CAvoiderOwner**)((char*)self + 0x80);
    if (p) {
        CAvoiderOwner* r = p->Find(0x4f176642);
        if (r) {
            CAvoider* q = r->GetAvoider();
            if (q)
                q->Avoid(self);
        }
    }
}

// =================================================================================================
// @ 0x00b3e620
void FUN_00b3e620(void* self_, int mode, int a3, int a4, int a5, int a6)
{
    VObj* self = (VObj*)self_;

    Vector3 v;
    Vector3* pv = self->GetPos();
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    if (v.x == g_invalid.x && v.y == g_invalid.y && v.z == g_invalid.z) {
        v.x = g_default.x;
        v.y = g_default.y;
        v.z = g_default.z;
    }

    cPlanetModel* pm = PlanetModel();
    Vector3 outv;
    Vector3* res = pm->ProjectToSurface(&outv, &v, a3, a4, a5, a6);
    v = *res;
    self->SetPos(&v);

    if (mode != 0) {
        if ((u8)a4 != 0 || (u8)a5 != 0) {
            float h;
            if (0.0f < pm->GetHeight(&h, 1))
                mode = 1;
        }
    }

    Quaternion q;
    Quaternion* pq = self->GetQuat();
    q.x = pq->x;
    q.y = pq->y;
    q.z = pq->z;
    q.w = pq->w;

    Quaternion r;
    if (mode == 1)
        r = *pm->BuildSurfaceOrientation(&r, &v, &q);
    else if (mode == 2)
        r = *pm->BuildPitchedSurfaceOrientation(&r, &v, &q, 1.0f);
    else if (mode == 3)
        r = *pm->BuildSurfaceNormalOrientation(&r, &v, &q, 1.0f);
    else
        return;

    self->SetQuat(&r);
}

// =================================================================================================
// @ 0x00b3e800
void __stdcall FUN_00b3e800(int, int)
{
    RebuildStaticCollision();
}

// =================================================================================================
// @ 0x00b3e810
struct ThisObj {
    u8 pad0[0x20];
    int m20;                 // 0x20
    void Refresh(void* param);   // 0x00b3e810
};

void ThisObj::Refresh(void* param)
{
    if (m20 != 0) {
        if ((u32)(m20 - 1) <= 1 && *(char*)((char*)param + 0xa6) != 0)
            FUN_00b3e620(param, 1, 0, 0, 0, 0);
    } else {
        FUN_00b55680(param, 0, 0);
    }
}

// =================================================================================================
// @ 0x00b3e860
int __stdcall FUN_00b3e860(const Vector3* p, const Vector3* a, const Vector3* b,
                           Vector3* out1, Vector3* out2)
{
    Vector3 r = { p->x - a->x, p->y - a->y, p->z - a->z };
    Vector3 d = { b->x - a->x, b->y - a->y, b->z - a->z };

    // Original emits the dot-product addends y,z,x (numerator) / z,y,x (denominator) under
    // /fp:fast reassociation; source-level grouping cannot force that order, so this function
    // stays a scheduling-level byte mismatch (functionally equivalent).
    float num = Dot(r, d);
    float den = Dot(d, d);
    float t = Clamp(num / den, 0.0f, 1.0f);

    *out1 = *p;
    out2->x = a->x + t * d.x;
    out2->y = t * d.y + a->y;
    out2->z = a->z + t * d.z;
    return 1;
}

// =================================================================================================
// @ 0x00b3e980
void __stdcall FUN_00b3e980(const Vector3* p1, const Vector3* p2, const Vector3* p3, const Vector3* p4,
                            Vector3* out1, Vector3* out2)
{
    float d1x = p2->x - p1->x, d1y = p2->y - p1->y, d1z = p2->z - p1->z;
    float d2x = p4->x - p3->x, d2y = p4->y - p3->y, d2z = p4->z - p3->z;

    float cx = d2z * d1y - d2y * d1z;
    float cy = d1z * d2x - d2z * d1x;
    float cz = d2y * d1x - d1y * d2x;

    float vx = cy * d2z - cz * d2y;
    float vy = cz * d2x - cx * d2z;
    float vz = cx * d2y - cy * d2x;

    float t = ((p3->x * vx + p3->z * vz) + p3->y * vy)
            - ((p1->x * vx + p1->z * vz) + p1->y * vy);
    t = t / ((vy * d1y + vz * d1z) + vx * d1x);
    t = Clamp(t, 0.0f, 1.0f);

    Vector3 pt;
    pt.x = p1->x + t * d1x;
    pt.y = d1y * t + p1->y;
    pt.z = p1->z + d1z * t;

    FUN_00b3e860(&pt, p3, p4, out1, out2);
}

// =================================================================================================
// @ 0x00b3eb90
int __stdcall FUN_00b3eb90(const Vector3* pts, int n, Vector3* out, int* outCount,
                           const Vector3* plane, float offset)
{
    char sign[32];
    bool anyIn = false;
    bool anyOut = false;
    int i = 0;

    if (n > 3) {
        float nx = plane->x, ny = plane->y, nz = plane->z;
        do {
            bool b0 = (pts[i].x * nx + pts[i].y * ny + pts[i].z * nz) - offset < 0.0f;
            bool b1 = (pts[i + 1].x * nx + pts[i + 1].y * ny + pts[i + 1].z * nz) - offset < 0.0f;
            bool b2 = (pts[i + 2].x * nx + pts[i + 2].y * ny + pts[i + 2].z * nz) - offset < 0.0f;
            bool b3 = (pts[i + 3].x * nx + pts[i + 3].y * ny + pts[i + 3].z * nz) - offset < 0.0f;
            sign[i] = b0;
            sign[i + 1] = b1;
            sign[i + 2] = b2;
            sign[i + 3] = b3;
            anyIn = anyIn | b0 | b1 | b2 | b3;
            anyOut = anyOut | !b0 | !b1 | !b2 | !b3;
            i += 4;
        } while (i < n - 3);
    }

    if (i < n) {
        float nx = plane->x, ny = plane->y, nz = plane->z;
        do {
            bool b = (pts[i].x * nx + pts[i].y * ny + pts[i].z * nz) - offset < 0.0f;
            sign[i] = b;
            anyIn = anyIn | b;
            anyOut = anyOut | !b;
            i++;
        } while (i < n);
    }

    if (!anyIn) {
        *outCount = 0;
        return 0;
    }

    if (!anyOut) {
        *outCount = n;
        for (int k = 0; k < n; k++)
            out[k] = pts[k];
        return 1;
    }

    *outCount = 0;
    int limit = (n > 2) ? n : 1;
    int prev = n - 1;
    char prevSign = sign[prev];
    for (int j = 0; j < limit; j++) {
        if (prevSign) {
            if (*outCount >= 0x20)
                return 1;
            out[*outCount] = pts[prev];
            (*outCount)++;
        }
        if (sign[j] != prevSign) {
            if (*outCount >= 0x20)
                return 1;
            float nx = plane->x, ny = plane->y, nz = plane->z;
            float e0 = pts[j].x - pts[prev].x;
            float e1 = pts[j].y - pts[prev].y;
            float e2 = pts[j].z - pts[prev].z;
            float t = (offset - ((pts[prev].y * ny + pts[prev].z * nz) + pts[prev].x * nx))
                    / ((ny * e1 + nz * e2) + nx * e0);
            Vector3* dst = &out[*outCount];
            dst->x = e0 * t + pts[prev].x;
            dst->y = pts[prev].y + e1 * t;
            dst->z = pts[prev].z + e2 * t;
            (*outCount)++;
        }
        prev = j;
        prevSign = sign[j];
    }
    return 1;
}
