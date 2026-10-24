// Slice s00af4da0 -- SP collision shape (swept sphere vs. box / polygon).
//
//  0x00af4da0  SPShape constructor (default state, empty AABB, identity xform)
//  0x00af4ea0  SPShape::InitSpan   (kind 1: segment / boxed sweep)
//  0x00af4f70  SPShape::InitPoly   (kind 2: clipped-polygon sweep)
//  0x00af5060  swept sphere vs. oriented box: segment-box test + init kind 1
//  0x00af5400  swept sphere vs. polygon: quadratic time-of-impact + clip + init kind 2
//
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include <string.h>
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef float          f32;

// ---------------------------------------------------------------- callees
extern "C" u8    __cdecl FUN_006989d0(const f32* a, const f32* b, const void* box, f32* t); // 0x006989d0 SP::SegmentBoxIntersect
extern "C" u8    __cdecl FUN_0069a240(const f32* a, const f32* b, const f32* poly, int n, f32* outA, f32* outB); // 0x0069a240 SP::ClipSegmentToPolygon
extern "C" f32   __cdecl FUN_00698b30(const f32* q, const f32* a, const f32* b); // 0x00698b30 SP::QuaternionSlerp
extern "C" f32   __cdecl FUN_00698e00(const f32* out, const f32* p, const f32* a, const f32* b); // 0x00698e00 SP::DistancePointSegment

// ---------------------------------------------------------------- globals
extern "C" f32 DAT_0145c3e0;   // +FLT_MAX
extern "C" f32 DAT_013f51ac;   // -FLT_MAX
extern "C" f32 DAT_01485720;   // _HK_REAL_ONE (1.0f)
extern "C" f32 DAT_0167ae24;
extern "C" f32 DAT_0167ae28;
extern "C" f32 DAT_0167ae2c;
extern "C" f32 DAT_0167ae78;
extern "C" f32 DAT_0167ae7c;
extern "C" f32 DAT_0167ae80;
extern "C" f32 DAT_0167ae54[];
extern "C" f32 DAT_013eb8b0[];
extern "C" f32 DAT_013ec4b8;

// ---------------------------------------------------------------- types
struct Vec3 { f32 x, y, z; };

// {DAT_0167ae24, DAT_0167ae28, DAT_0167ae2c} viewed as one 12-byte block.
extern "C" Vec3 DAT_0167ae24_v;

struct Mat33 {
    f32 m[9];
    void* __thiscall Assign(const f32* src);   // 0x0041cb40 Matrix33Template<float,0> ctor
};

// cSPTransform: 0x70..0xa8 (0x38 bytes).
struct cSPTransform {
    u16   flags0;      // 0x70
    u16   flags2;      // 0x72
    Vec3  origin;      // 0x74
    f32   scale;       // 0x80
    Mat33 basis;       // 0x84
    void* __thiscall Assign(const void* src);       // 0x00537dc0 cSPTransform::operator=
    void  __thiscall BackTransformPoint(f32* p);    // 0x004ff6d0
};

// 8-dword orientation block copied verbatim (0x00..0x20).
struct Orientation { u32 w[8]; };

// Swept-sphere / sweep primitive built by this module.
struct SPShape {
    Orientation orient;    // 0x00
    int         kind;      // 0x20
    int         type;      // 0x24  (1 = span, 2 = polygon)
    Vec3        pos;       // 0x28
    Vec3        worldPos;  // 0x34
    u8          flag40;    // 0x40
    char        pad41[3];  // 0x41
    f32         radiusA;   // 0x44
    Vec3        halfExt;   // 0x48
    f32         extra54;   // 0x54
    Vec3        lo;        // 0x58  (running AABB min)
    Vec3        hi;        // 0x64  (running AABB max)
    cSPTransform xf;       // 0x70
    Vec3        normal;    // 0xa8
    int         fieldB4;   // 0xb4
    int         fieldB8;   // 0xb8
    Vec3        contact;   // 0xbc
    f32         depth;     // 0xc8
    SPShape* __thiscall InitDefault();   // 0x00af4da0
};
typedef char spshape_size_check[(sizeof(SPShape) == 0xcc) ? 1 : -1];

// Oriented/deformed box accepted by the collision helpers.
struct SPBox {
    u16   flags;       // 0x00
    u16   pad02;       // 0x02
    Vec3  center;      // 0x04
    f32   scale;       // 0x10
    Mat33 basis;       // 0x14
};
typedef char spbox_size_check[(sizeof(SPBox) == 0x38) ? 1 : -1];

// ---------------------------------------------------------------- 00af4da0
// Default-construct: empty AABB (min=+MAX, max=-MAX), identity xform.
// @ 0x00af4da0
SPShape* __thiscall SPShape::InitDefault()
{
    SPShape* self = this;
    self->radiusA = 0.0f;
    self->kind   = 0;
    self->type   = 0;
    self->flag40 = 0;
    f32 vhi = DAT_0145c3e0;
    f32 tv[3] = { vhi, vhi, vhi };
    memcpy(&self->lo, tv, sizeof(tv));
    f32 vlo = DAT_013f51ac;
    f32 tw[3] = { vlo, vlo, vlo };
    memcpy(&self->hi, tw, sizeof(tw));
    self->xf.flags2 = 0;
    self->xf.flags0 = 0;
    self->xf.origin.x = DAT_0167ae24;
    self->xf.origin.y = DAT_0167ae28;
    self->xf.origin.z = DAT_0167ae2c;
    self->xf.scale = DAT_01485720;
    self->xf.basis.Assign(DAT_0167ae54);
    memset(&self->orient, 0, sizeof(self->orient));
    return self;
}

// ---------------------------------------------------------------- 00af4ea0
// @ 0x00af4ea0
extern "C" void __cdecl FUN_00af4ea0(SPShape* self, int kind, const Vec3* a, const Vec3* b,
                                     const void* xform, const f32* src6, u8 flag,
                                     const Orientation* orient)
{
    self->kind  = kind;
    self->type  = 1;
    self->pos   = *a;
    self->halfExt = *b;
    self->xf.Assign(xform);
    const Vec3* p6 = (const Vec3*)src6;
    self->hi = p6[1];
    self->lo = p6[0];
    self->flag40 = flag;
    self->worldPos = DAT_0167ae24_v;
    if (orient) {
        self->orient = *orient;
        return;
    }
    memset(&self->orient, 0, sizeof(self->orient));
}

// ---------------------------------------------------------------- 00af4f70
// @ 0x00af4f70
extern "C" void __cdecl FUN_00af4f70(SPShape* self, int kind, const Vec3* a, const Vec3* b,
                                     f32 f54, const void* xform, const Vec3* n, f32 f_c8,
                                     int b4, int b8, u8 flag, const Orientation* orient)
{
    self->kind  = kind;
    self->type  = 2;
    self->pos   = *a;
    self->halfExt = *b;
    self->xf.Assign(xform);
    self->extra54 = f54;
    self->normal = *n;
    self->depth = f_c8;
    self->fieldB8 = b4;
    self->fieldB4 = b8;
    self->flag40 = flag;
    self->worldPos = DAT_0167ae24_v;
    if (orient != 0) {
        self->orient = *orient;
        return;
    }
    memset(&self->orient, 0, sizeof(self->orient));
}

// ---------------------------------------------------------------- 00af5060
// Swept sphere vs. oriented box. Returns 1 on contact.
// @ 0x00af5060
extern "C" u8 __cdecl FUN_00af5060(SPShape* obj, int kind, const Vec3* start, const Vec3* arg4,
                                   const Vec3* dir, f32* out, f32 radius, const SPBox* box,
                                   const f32* boxF, int p10, int p11)
{
    f32 invScale;
    Vec3 p0, p1;
    f32 t;

    f32 s = *out;
    f32 dx = dir->x * s;
    f32 dy = dir->y * s;
    f32 dz = dir->z * s;

    f32 sw = box->scale;
    f32 ex, ey, ez;
    f32 px = start->x - box->center.x;
    f32 py = start->y - box->center.y;
    f32 pz = start->z - box->center.z;
    if (sw != 1.0f) {
        invScale = 1.0f / sw;
        px *= invScale;
        py *= invScale;
        pz *= invScale;
    }
    ex = start->x + dx;
    ey = start->y + dy;
    ez = start->z + dz;

    p0.x = px; p0.y = py; p0.z = pz;
    if ((box->flags & 2) != 0) {
        p0.x = box->basis.m[2] * pz + box->basis.m[1] * py + box->basis.m[0] * px;
        p0.y = box->basis.m[5] * pz + box->basis.m[4] * py + box->basis.m[3] * px;
        p0.z = box->basis.m[8] * pz + box->basis.m[7] * py + box->basis.m[6] * px;
    }

    f32 qx = ex - box->center.x;
    f32 qy = ey - box->center.y;
    f32 qz = ez - box->center.z;
    if (sw != 1.0f) {
        invScale = 1.0f / sw;
        qx *= invScale;
        qy *= invScale;
        qz *= invScale;
    }
    p1.x = qx; p1.y = qy; p1.z = qz;
    if ((box->flags & 2) != 0) {
        p1.x = box->basis.m[2] * qz + box->basis.m[1] * qy + box->basis.m[0] * qx;
        p1.y = box->basis.m[5] * qz + box->basis.m[4] * qy + box->basis.m[3] * qx;
        p1.z = box->basis.m[8] * qz + box->basis.m[7] * qy + box->basis.m[6] * qx;
    }

    if (!FUN_006989d0(&p0.x, &p1.x, boxF, &t))
        return 0;

    f32 vz = p1.z - p0.z;
    f32 vy = p1.y - p0.y;
    f32 vx = p1.x - p0.x;
    f32 dist = (*out * t) * radius;
    *out = dist;
    f32 sum = vx * vx + (vy * vy + vz * vz);
    f32 invlen = 1.0f / (f32)sqrt((double)sum);
    Vec3 contact;
    contact.x = dist * (vx * invlen) + p0.x;
    contact.y = dist * (vy * invlen) + p0.y;
    contact.z = dist * (vz * invlen) + p0.z;
    FUN_00af4ea0(obj, kind, arg4, &contact, box, boxF, (u8)p10, (const Orientation*)p11);
    return 1;
}

// ---------------------------------------------------------------- 00af5400
// Swept sphere vs. convex polygon. Returns 1 on contact.
// @ 0x00af5400
extern "C" u32 __cdecl FUN_00af5400(SPShape* obj, int kind, const Vec3* p3, const Vec3* p4,
                                    const Vec3* p5, const Vec3* p6, f32* p7, f32 p8,
                                    cSPTransform* xform, const Vec3* p10, f32 p11, const Vec3* poly,
                                    int npoly, f32 p14, int p15, const Orientation* p16)
{
    f32 l70, l6c, l68, l64, l60, l5c, l58, l54, l50, l4c, l48, l44, l40, l3c, l38, l34, l30;
    f32 outB;
    f32 l20[7];

    f32 fVar9 = *p7;
    f32 l28 = p6->y * fVar9;
    l60 = p3->z;
    l64 = p3->y;
    l68 = p3->x;
    f32 fVar6 = l68 - p4->x;
    f32 fVar8 = l60 - p4->z;
    f32 fVar7 = l64 - p4->y;
    l70 = (fVar6 * (fVar9 * p6->x) + fVar8 * (p6->z * fVar9)) + fVar7 * l28;
    fVar6 = ((fVar6 * fVar6 + fVar8 * fVar8) + fVar7 * fVar7) - (p11 + p14) * (p11 + p14);
    l6c = l70 * l70 - fVar6 * (fVar9 * fVar9);
    if (fVar6 >= 0.0f) {
        if (l6c < 0.0f)
            return 0;
        l6c = (f32)sqrt((double)l6c);
        if (l6c - l70 < 0.0f)
            return 0;
        if (fVar9 * fVar9 < -l70 - l6c)
            return 0;
    }
    l5c = p5->x;
    l58 = p5->y;
    l54 = p5->z;
    l50 = l68;
    l4c = l64;
    l48 = l60;
    xform->BackTransformPoint(&l50);
    xform->BackTransformPoint(&l5c);
    l64 = l5c - l50;
    l68 = l58 - l4c;
    l70 = l68 * l68 + l64 * l64;
    l48 = 0.0f;
    l54 = 0.0f;
    fVar9 = 1.0f / (f32)sqrt((double)(l70 + 1e-08f));
    l60  = (l68 * fVar9) * DAT_0167ae80;
    l44  = l60 - (fVar9 * 0.0f) * DAT_0167ae7c;
    l3c  = (fVar9 * l64) * DAT_0167ae7c - (l68 * fVar9) * DAT_0167ae78;
    l40  = (fVar9 * 0.0f) * DAT_0167ae78 - (fVar9 * l64) * DAT_0167ae80;
    fVar9 = (p10->y - l4c) * l64 - (p10->x - l50) * l68;
    if (fVar9 <= 0.0f) {
        if (fVar9 >= 0.0f)
            goto LAB_5895;
        l38 = -l50;
        fVar9 = -l4c;
        l34 = fVar9;
        fVar6 = fVar9 * l68 + l38 * l64;
        if (fVar6 > 0.0f) {
            if (fVar6 < l70) {
                fVar6 = fVar6 / l70;
                l30 = -(fVar6 * 0.0f);
                l34 = -(l68 * fVar6 + l4c);
                fVar9 = -(l64 * fVar6 + l50);
                l38 = fVar9;
                fVar6 = l34 * l34 + l30 * l30;
            } else {
                fVar9 = -l58;
                fVar6 = -l5c * -l5c;
            }
        } else {
            fVar6 = l38 * l38;
        }
        l70 = (f32)sqrt((double)(fVar9 * fVar9 + fVar6));
        if (p14 <= l70)
            l70 = p14;
        fVar9 = l70;
    } else {
        fVar9 = -l50;
        l34 = -l4c;
        l38 = fVar9;
        fVar6 = l34 * l68 + fVar9 * l64;
        if (fVar6 > 0.0f) {
            if (fVar6 < l70) {
                fVar6 = fVar6 / l70;
                l38 = -(l64 * fVar6 + l50);
                l30 = -(fVar6 * 0.0f);
                fVar9 = -(l68 * fVar6 + l4c);
                l34 = fVar9;
                fVar6 = l30 * l30 + l38 * l38;
                goto LAB_572f;
            }
            fVar9 = -l58 * -l58;
            fVar6 = -l5c * -l5c;
        } else {
            fVar6 = l34 * l34;
LAB_572f:
            fVar9 = fVar9 * fVar9;
        }
        l70 = (f32)sqrt((double)(fVar9 + fVar6));
        if (p14 <= (f32)sqrt((double)(fVar9 + fVar6)))
            l70 = p14;
        fVar9 = -l70;
    }
    l44 = l44 * fVar9;
    l48 = l3c * fVar9;
    l40 = l40 * fVar9;
    l5c = l44 + l5c;
    l50 = l44 + l50;
    l58 = l40 + l58;
    l4c = l40 + l4c;
    l3c = l48;

LAB_5895:
    l54 = l48;
    if (FUN_0069a240(&l50, &l5c, &poly->x, npoly, &l38, &outB)) {
        obj->contact.x = l50;
        obj->contact.y = l4c;
        obj->contact.z = l48;
        if (obj->contact.x == l38 && obj->contact.y == l34 && obj->contact.z == l30) {
            obj->contact.x = obj->contact.x - l44;
            obj->contact.y = obj->contact.y - l40;
            obj->contact.z = obj->contact.z - l3c;
        }
        fVar9 = (f32)sqrt((double)(((l30 - l48) * (l30 - l48) +
                                    (l34 - l4c) * (l34 - l4c)) +
                                    (l38 - l50) * (l38 - l50))) - p14;
        f32 l20v = 0.0f;
        if (fVar9 >= 0.0f)
            l20v = fVar9;
        *p7 = l20v * p8;
        FUN_00af4f70(obj, kind, p4, (const Vec3*)&l38, p14, xform, p10, p11, (int)poly, npoly,
                     (u8)p15, p16);
        return 1;
    }
    l5c = p5->x;
    l58 = p5->y;
    l54 = p5->z;
    xform->BackTransformPoint(&l5c);
    l54 = 0.0f;
    l44 = poly->x;
    l40 = poly->y;
    l3c = poly->z;
    int iVar3 = 1;
    l6c = 0.0f;
    l70 = p14;
    const Vec3* pfVar2 = poly;
    if (1 < npoly) {
        do {
            const Vec3* pfVar4 = pfVar2 + 1;
            f32 fVar5 = FUN_00698b30(&l5c, &l44, &pfVar4->x);
            l60 = fVar5;
            if (fVar5 < l70) {
                l70 = l60;
                l6c = (f32)iVar3;
            }
            l44 = pfVar4->x;
            l40 = pfVar2[1].y;
            l3c = pfVar2[1].z;
            iVar3 = iVar3 + 1;
            pfVar2 = pfVar4;
        } while (iVar3 < npoly);
        if (l6c != 0.0f) {
            obj->contact.x = l50;
            obj->contact.y = l4c;
            obj->contact.z = l48;
            FUN_00698e00(l20, &l5c, &poly[(int)l6c - 1].x, &poly[(int)l6c].x);
            FUN_00af4f70(obj, kind, p4, (const Vec3*)l20, p14, xform, p10, p11, (int)poly, npoly,
                         (u8)p15, p16);
            return 1;
        }
    }
    return 0;
}
