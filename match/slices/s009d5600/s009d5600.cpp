// Slice s009d5600 — an anonymous animated-event/player object: the two
// quaternion-stepping helpers used by the animation driver, the driver loop
// itself, and the distance/radius helper.
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include <math.h>
#include <intrin.h>
#include "s009d5600.h"

// 0x009ce010 — rotate a quaternion by `ang` about the x axis (a static leaf
// helper of the same translation unit: pointer in eax, float on the stack).
static __declspec(noinline) void H9ce010(Q4* o, float ang)
{
    float h = ang * 0.5f;
    float s = sinf(h), c = cosf(h);
    float x = o->x, y = o->y, z = o->z, w = o->w;
    o->x = x * c + w * s + y * 0.0f - z * 0.0f;
    o->y = y * c + w * 0.0f - x * s + z * 0.0f;
    o->z = z * c + w * 0.0f + x * 0.0f - y * s;
    o->w = w * c - x * 0.0f - y * 0.0f - z * s;
}

// sign(f7c) with the 1e-6 dead band.
static float sgn6(float v)
{
    if (g_14479b0 <= v)
    {
        if (v <= g_14479b0) return g_1485378;
        return g_1485720;
    }
    return g_13eb1bc;
}

// @ 0x009d5600
void __thiscall Ent::Fn5600(Ent* p, float a)
{
    Q4* v24 = &this->v24;
    *v24 = q88;

    char* o2 = (char*)o_c8;
    if (*(u8*)(*(char**)o2 + 0x3f5) != 0) return;
    void* arr = *(void**)(o2 + 0x2e4);
    void* q = *(void**)((char*)arr + o58 * 0x2bc);
    if (((XKey*)((char*)q + 0x150))->IsInTable(0x74667370, 0)) return;

    float A = *(float*)(o2 + 0x160c);
    float B = *(float*)(o2 + 0x1604);
    float C = *(float*)(o2 + 0x1608);
    float D = *(float*)(o2 + 0x161c);

    float local30 = B - f80 * D;
    float local2c = f7c * D + C;
    float local18 = A;

    float qx = q88.x, qy = q88.y, qz = q88.z, qw = q88.w;
    float X = (qz * qy + qw * qx) * g_1470f1c;
    float Y = g_1485720 - (qz * qz + qx * qx) * g_1470f1c;
    float Z = (qy * qx - qz * qw) * g_1470f1c;
    float dot = (-X * local18 + -Y * local2c) + -Z * local30;

    if (dot < g_1485378) a = g_1485720 - a;

    if (g_15515dc != 0 && o64 != 0 && o68 != 0)
    {
        float outv;
        FnCeec0(&outv, (g_1485720 - f78) * g_155125c * a);

        H9ce010(v24, sgn6(f7c) * local18 + ff0);

        float t;
        if (g_15509e0 != 0)
        {
            float den = local2c * local2c + local30 * local30;
            float f10 = (den <= g_14479b0) ? g_1485378 : (dot / den) * dot;
            t = (*(float*)((char*)p + 0xdc) * outv) * f10;
        }
        else t = g_1485378;

        Q4 qb, out, *r;
        qb.x = sinf(t * g_1471064);
        qb.y = g_1485378;
        qb.z = g_1485378;
        qb.w = cosf(t * g_1471064);
        r = QuatMul(&out, v24, &qb);
        v24->x = r->x; v24->y = r->y; v24->z = r->z; v24->w = r->w;

        if (g_15509e0 != 0) FnCf080(p, a, t);

        float s2 = sgn6(f7c);
        float ang = (s2 * local2c) * g_1471064;
        Q4 qb2;
        qb2.x = g_1485378;
        qb2.y = sinf(ang);
        qb2.z = g_1485378;
        qb2.w = cosf(ang);
        r = QuatMul(&out, v24, &qb2);
        v24->x = r->x; v24->y = r->y; v24->z = r->z; v24->w = r->w;
        return;
    }

    H9ce010(v24, ff0);

    float t;
    if (g_15509e0 != 0)
    {
        float den = local2c * local2c + local30 * local30;
        float f10 = (den <= g_14479b0) ? g_1485378 : (dot / den) * dot;
        t = ((((a - *(float*)((char*)p + 0x6c)) * (a - g_1485720)) *
              *(float*)((char*)p + 0xdc)) * *(float*)((char*)p + 0x68)) * f10 * a;
    }
    else t = g_1485378;

    float qx1 = v24->x, qy1 = v24->y, qz1 = v24->z, qw1 = v24->w;
    float sn = sinf(t * g_1471064);
    float cs = cosf(t * g_1471064);
    Q4 qb;
    qb.x = sn; qb.y = g_1485378; qb.z = g_1485378; qb.w = cs;
    float w = qw1, x = qx1, y = qy1, z = qz1;
    v24->x = ((x * cs + w * sn) - z * 0.0f) + y * 0.0f;
    v24->y = ((y * cs + w * 0.0f) - x * sn) + z * 0.0f;
    v24->z = ((z * cs + w * 0.0f) + x * 0.0f) - y * sn;
    v24->w = ((w * cs - x * 0.0f) - y * 0.0f) - z * sn;

    if (g_15509e0 != 0) FnCf080(p, a, t);
}

// @ 0x009d5b50
void __thiscall Ent::Fn5b50(Ent* p, float a)
{
    Q4* v24 = &this->v24;
    *v24 = q88;

    char* o2 = (char*)o_c8;
    if (*(u8*)(*(char**)o2 + 0x3f5) != 0) return;
    void* arr = *(void**)(o2 + 0x2e4);
    void* q = *(void**)((char*)arr + o58 * 0x2bc);
    if (((XKey*)((char*)q + 0x150))->IsInTable(0x74667370, 0)) return;

    if (g_15515dc == 0 || o64 == 0 || o68 == 0)
    {
        H9ce010(v24, ff0);
        return;
    }

    o2 = (char*)o_c8;
    float A = *(float*)(o2 + 0x160c);
    float B = *(float*)(o2 + 0x1604);
    float C = *(float*)(o2 + 0x1608);
    float D = *(float*)(o2 + 0x161c);

    float local30 = B - f80 * D;
    float local2c = f7c * D + C;
    float local18 = A;

    float qx = q88.x, qy = q88.y, qz = q88.z, qw = q88.w;
    float X = (qz * qy + qw * qx) * g_1470f1c;
    float Y = g_1485720 - (qz * qz + qx * qx) * g_1470f1c;
    float Z = (qy * qx - qz * qw) * g_1470f1c;
    float dot = (-X * local18 + -Y * local2c) + -Z * local30;

    float a2 = a;
    if (dot < g_1485378) a2 = g_1485720 - a;

    float outv;
    FnCeec0(&outv, (g_1485720 - (g_1485720 - a2) * f78) * g_155125c);

    H9ce010(v24, sgn6(f7c) * local18 + ff0);

    float t;
    if (g_15509e0 != 0)
    {
        float den = local2c * local2c + local30 * local30;
        float f10 = (den <= g_14479b0) ? g_1485378 : (dot / den) * dot;
        t = (*(float*)((char*)p + 0xdc) * outv) * f10;
    }
    else t = g_1485378;

    Q4 qb, out, *r;
    qb.x = sinf(t * g_1471064);
    qb.y = g_1485378;
    qb.z = g_1485378;
    qb.w = cosf(t * g_1471064);
    r = QuatMul(&out, v24, &qb);
    v24->x = r->x; v24->y = r->y; v24->z = r->z; v24->w = r->w;

    if (g_15509e0 != 0) FnCf080(p, a2, t);

    float ang = (sgn6(f7c) * local2c) * g_1471064;
    Q4 qb2;
    qb2.x = g_1485378;
    qb2.y = sinf(ang);
    qb2.z = g_1485378;
    qb2.w = cosf(ang);
    r = QuatMul(&out, v24, &qb2);
    v24->x = r->x; v24->y = r->y; v24->z = r->z; v24->w = r->w;
}

// @ 0x009d5f10
void __thiscall Ent::Fn5f10(Ent* p, float q3, float q4, float q5, float q6)
{
    if (!(0.0f < p->fa4)) return;

    float ph = p->f9c;
    float step0 = p->fac;
    float fVar1 = p->fb0;
    float left = p->fa0;

    fd0 = f78 * (p->fa8 * g_13ec488);
    fd8 = f78 * (fVar1 * g_13ec488);
    fd4 = f78 * (step0 * g_13ec488);
    fe8 = (p->fb4 * f78) * g_13ec488;
    o5d = 0;

    if (left > g_1551520) left = fmodf(left, g_1551520);

    while (left > g_1485378)
    {
        float v1 = (f6c + ph) - (float)floor((double)(f6c + ph));
        float lo = f100;
        float hi = f104;
        u8 fl = (v1 < lo || hi <= v1);
        o5c = fl;

        float w;
        if (v1 < lo) w = (g_1485720 - hi) + v1;
        else
        {
            float t = lo;
            if (hi <= v1) t = hi;
            w = v1 - t;
        }

        float span;
        if (fl != 0) span = (g_1485720 - hi) + lo;
        else span = hi - lo;
        w = span - w;

        float step = (left <= w) ? left : w;
        step = step + g_13f89bc;
        float frac = step / p->fa4;
        float scl = (g_14479b0 <= frac) ? frac : g_1485378;

        float ph2 = (f6c + ph) + step;
        float v2 = ph2 - (float)floor((double)ph2);
        f98 = v2;

        if (fl == 0)
        {
            float r = (ph2 - lo) / span;
            if (r > g_1485378) { if (r > g_1485720) r = g_1485720; }
            else r = g_1485378;
            Fn49b0(p, scl, r);
            Fn5600(p, r);
        }
        else
        {
            float t = (v2 <= hi) ? (g_1485720 - hi) + v2 : v2 - hi;
            float r = t / span;
            float r2 = g_1485378;
            if (r > g_1485378) { r2 = r; if (r > g_1485720) r2 = g_1485720; }
            Fn52f0(p, scl, r2, q3, q4, q5, q6);
            Fn5b50(p, r2);
        }

        if (left > step || w <= step)
        {
            if (o5c == 0) Fn46d0(p);
            else Fn42b0(p);
            o5d = 1;
        }

        ph = step + ph;
        left = left - step;
    }
}

// @ 0x009d62a0
float __thiscall Ent::Fn62a0(float d)
{
    Obj48* o = o48;
    float local = fabsf(o->f0c) * g_15514e4;
    const float& mv = (local > o->f08) ? local : o->f08;

    char* base = (char*)o->o24;
    char* e1 = *(char**)(base + 0xc8);
    char* tbl = *(char**)(e1 + 0x384);
    char* x0 = tbl + *(int*)(base + o_bc[0] * 0x108 + 0x58) * 0x468;
    char* x1 = tbl + *(int*)(base + o_bc[1] * 0x108 + 0x58) * 0x468;

    float dx = *(float*)(x0 + 0x10c) - *(float*)(x1 + 0x10c);
    float dy = *(float*)(x0 + 0x110) - *(float*)(x1 + 0x110);
    float dz = *(float*)(x0 + 0x114) - *(float*)(x1 + 0x114);

    float dist = sqrtf(dx * dx + dy * dy + dz * dz);
    float R = dist + (mv / fa4) * o->f80 * g_1471064;
    float diff = R * R - d * d;
    float zero = g_1485378;
    const float& q = (diff > g_1485378) ? diff : zero;
    return sqrtf(q) * g_1551524;
}
