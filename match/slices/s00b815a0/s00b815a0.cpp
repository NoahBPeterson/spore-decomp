// SporeApp.exe slice s00b815a0 -- SP::cPlanetModel surface-position queries.
// Build: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast
#include <math.h>

typedef unsigned int uint;

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

// ---- external helpers -----------------------------------------------------
void  RandomDirection3(Vec3* out);                                   // 0x00b7e560
float RandomFloatRange(float lo, float hi);                          // 0x00572a10
Vec3* QuaternionFromDirections(Quat* out, const Vec3* a, const Vec3* b); // 0x00698180
void  Matrix3FromQuaternion(float* out, const Quat* q);              // 0x0059c190
float* FUN_0059aed0(float* out, const float* a, const float* b);    // 0x0059aed0
char  FUN_005a9c40(Vec3* a, Vec3* b, Vec3* c, float d, float* out); // 0x005a9c40
int   FUN_00b3d310();                                                // 0x00b3d310
float FUN_00b65b10(Vec3* a, int b, int c, int d, int e, float* out); // 0x00b65b10

struct cTerrainSphere {
    Quat BuildSurfaceOrientation(const Vec3& a, const Vec3& b);      // 0x00f9c960
};

extern float DAT_0167ecd0;
extern float DAT_01688274;
extern Vec3  DAT_01688278;
extern Vec3  DAT_016881f0;             // fallback surface direction
extern float DAT_0156b614, DAT_0156b618, DAT_0156b61c, DAT_0156b620;

#define VTC(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

// ---- the planet model -----------------------------------------------------
struct cPlanetModel {
    char  pad0[0x20];
    void* mpSphere;      // +0x20
    void* mpISphere;     // +0x24
    float f28;           // +0x28
    char  pad1[0xf0 - 0x2c];
    char  f0;            // +0xf0

    long double GetRadiusAt(uint coords);                            // 0x00b7ef70
    void  DirectionToSurfacePosition(Vec3* out, const Vec3* dir);    // 0x00b815a0
    void  FUN_00b81630(Vec3* out, const Vec3* dir);                  // 0x00b81630
    Vec3* FUN_00b816f0(Vec3* out, const Vec3* dir);                  // 0x00b816f0
    void  FUN_00b81720(Vec3* out);                                   // 0x00b81720
    void  MakeRandomWorldPosition(Vec3* out, const Vec3* dir, float a, float b); // 0x00b81780
    void  FUN_00b81a40(Vec3* out, const Vec3* dir, float a, float b);            // 0x00b81a40
    void  FUN_00b81c80(Vec3* out, const Vec3* a, const Vec3* b, float s);        // 0x00b81c80
    int   IsPositionBelowSurface(const Vec3* dir);                   // 0x00b81f90
    Vec3* FUN_00b82060(Vec3* out, int a, int b);                     // 0x00b82060
    void  FUN_00b82110(Vec3* out, Vec3* a, Vec3* b);                 // 0x00b82110
    long double FUN_00b82310(void* param);                           // 0x00b82310
};

// =======================================================================================
// 00b815a0 -- SP::cPlanetModel::DirectionToSurfacePosition
// =======================================================================================
void cPlanetModel::DirectionToSurfacePosition(Vec3* out, const Vec3* dir)
{
    float f4 = (float)GetRadiusAt((uint)dir);
    float inv = 1.0f / sqrtf(dir->x * dir->x + dir->y * dir->y + dir->z * dir->z + 1e-8f);
    Vec3 res;
    res.x = dir->x * inv * f4;
    res.y = inv * dir->y * f4;
    res.z = inv * dir->z * f4;
    out->x = res.x;
    out->y = res.y;
    out->z = res.z;
}

// =======================================================================================
// 00b81630 -- like above but the radius is clamped to at least the local height
// =======================================================================================
void cPlanetModel::FUN_00b81630(Vec3* out, const Vec3* dir)
{
    float r = (float)GetRadiusAt((uint)dir);
    float h;
    if (mpISphere) {
        int m = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
        h = *(float*)(m + 0x3c) * *(float*)(m + 0x38) + *(float*)(m + 0x34);
    } else {
        h = 0.0f;
    }
    if (r > h) {
    } else {
        r = h;
    }
    float inv = 1.0f / sqrtf(dir->x * dir->x + dir->y * dir->y + dir->z * dir->z + 1e-8f);
    Vec3 res;
    float xi = dir->x * inv;
    float yi = dir->y * inv;
    float zi = dir->z * inv;
    res.x = xi * r;
    res.y = yi * r;
    res.z = zi * r;
    out->x = res.x;
    out->y = res.y;
    out->z = res.z;
}

// =======================================================================================
// 00b816f0 -- pick one of the two transforms based on the f0 flag
// =======================================================================================
Vec3* cPlanetModel::FUN_00b816f0(Vec3* out, const Vec3* dir)
{
    if (f0)
        FUN_00b81630(out, dir);
    else
        DirectionToSurfacePosition(out, dir);
    return out;
}

// =======================================================================================
// 00b81720 -- random direction scaled to the surface radius
// =======================================================================================
void cPlanetModel::FUN_00b81720(Vec3* out)
{
    Vec3 d;
    RandomDirection3(&d);
    float r = (float)GetRadiusAt((uint)&d);
    Vec3 res;
    res.x = d.x * r;
    res.y = d.y * r;
    res.z = d.z * r;
    out->x = res.x;
    out->y = res.y;
    out->z = res.z;
}

// =======================================================================================
// 00b81780 -- SP::cPlanetModel::MakeRandomWorldPosition
// =======================================================================================
void cPlanetModel::MakeRandomWorldPosition(Vec3* out, const Vec3* dir, float a, float b)
{
    float d0, d1, d2;            // local_50/4c/48
    Quat  q;                     // local_44/40/3c/38
    Quat  q2;                    // local_34/30/2c/28
    float m[9];                  // local_24..local_4
    float r;
    Vec3  res;                   // local_44/40/3c (result direction)
    float inv;

    if (1.0f < dir->x * dir->x + dir->y * dir->y + dir->z * dir->z) {
        if (0.0f < b) {
            if (b <= a)
                b = a;
            else
                b = RandomFloatRange(a, b);
            float t = RandomFloatRange(0.0f, DAT_01688274);
            d2 = 0.0f;
            d0 = cosf(t) * b;
            d1 = sinf(t) * b;
        } else {
            d0 = DAT_016881f0.x;
            d1 = DAT_016881f0.y;
            d2 = DAT_016881f0.z;
        }
        Vec3* u = QuaternionFromDirections(&q, &DAT_01688278, dir);
        if (mpISphere == 0) {
            q2.x = DAT_0156b614;
            q2.y = DAT_0156b618;
            q2.z = DAT_0156b61c;
            q2.w = DAT_0156b620;
        } else {
            q2 = ((cTerrainSphere*)mpSphere)->BuildSurfaceOrientation(*dir, *u);
        }
        Matrix3FromQuaternion(m, &q2);
        m[6] = m[6] * d2;
        m[7] = m[7] * d2;
        m[1] = m[1] * d0;
        d2 = ((m[5] * d1 + m[8] * d2) + m[2] * d0) + dir->z;
        d0 = dir->x + ((m[3] * d1 + m[6]) + m[0] * d0);
        d1 = ((m[4] * d1 + m[7]) + m[1]) + dir->y;
        r = (float)GetRadiusAt((uint)&d0);
        inv = 1.0f / sqrtf(d0 * d0 + (d2 * d2 + d1 * d1));
        res.x = inv * d0;
        res.y = d1 * inv;
        res.z = d2 * inv;
    } else {
        RandomDirection3(&res);
        r = (float)GetRadiusAt((uint)&res);
    }
    out->x = res.x * r;
    out->y = res.y * r;
    out->z = res.z * r;
}

// =======================================================================================
// 00b81a40 -- variant of MakeRandomWorldPosition without the flag/range branch
// =======================================================================================
void cPlanetModel::FUN_00b81a40(Vec3* out, const Vec3* dir, float a, float b)
{
    float d0, d1, d2;
    Quat  q;
    Quat  q2;
    float m[9];
    float r;
    Vec3  res;
    float inv;

    if (1.0f < dir->x * dir->x + dir->y * dir->y + dir->z * dir->z) {
        float t = b;
        d2 = 0.0f;
        d0 = cosf(t) * a;
        d1 = sinf(t) * a;
        Vec3* u = QuaternionFromDirections(&q, &DAT_01688278, dir);
        if (mpISphere == 0) {
            q2.x = DAT_0156b614;
            q2.y = DAT_0156b618;
            q2.z = DAT_0156b61c;
            q2.w = DAT_0156b620;
        } else {
            q2 = ((cTerrainSphere*)mpSphere)->BuildSurfaceOrientation(*dir, *u);
        }
        Matrix3FromQuaternion(m, &q2);
        m[6] = m[6] * d2;
        m[7] = m[7] * d2;
        m[1] = m[1] * d0;
        d2 = ((m[5] * d1 + m[8] * d2) + m[2] * d0) + dir->z;
        d0 = dir->x + ((m[3] * d1 + m[6]) + m[0] * d0);
        d1 = ((m[4] * d1 + m[7]) + m[1]) + dir->y;
        r = (float)GetRadiusAt((uint)&d0);
        inv = 1.0f / sqrtf(d0 * d0 + (d2 * d2 + d1 * d1));
        res.x = inv * d0;
        res.y = d1 * inv;
        res.z = d2 * inv;
    } else {
        RandomDirection3(&res);
        r = (float)GetRadiusAt((uint)&res);
    }
    out->x = res.x * r;
    out->y = res.y * r;
    out->z = res.z * r;
}

// =======================================================================================
// 00b81c80 -- surface position along an arc between two directions
// =======================================================================================
void cPlanetModel::FUN_00b81c80(Vec3* out, const Vec3* pa, const Vec3* pb, float s)
{
    Vec3 va, vb;
    va.x = pa->x;
    float l1 = 1.0f / sqrtf((va.x * va.x + pa->y * pa->y) + pa->z * pa->z);
    va.x = va.x * l1;
    va.z = l1 * pa->z;
    va.y = l1 * pa->y;

    vb.x = pb->x;
    float l2 = 1.0f / sqrtf((vb.x * vb.x + pb->y * pb->y) + pb->z * pb->z);
    vb.x = vb.x * l2;
    vb.y = pb->y * l2;
    vb.z = pb->z * l2;

    float r = (float)GetRadiusAt((uint)&va);

    float cx = vb.z * va.y - va.z * vb.y;
    float cy = va.z * vb.x - vb.z * va.x;
    float cz = vb.y * va.x - vb.x * va.y;
    float inv = 1.0f / sqrtf(cy * cy + (cz * cz + cx * cx));
    float sn, cs;
    if ((vb.z * va.z + vb.y * va.y) + vb.x * va.x <= 0.0f) {
        float t = (s / r) * -0.5f;
        sn = sinf(t);
        cs = cosf(t);
    } else {
        float t = (s / r) * 0.5f;
        sn = sinf(t);
        cs = cosf(t);
    }
    Quat q;
    q.w = cs;
    q.x = sn * (inv * cx);
    q.y = (cy * inv) * sn;
    q.z = (cz * inv) * sn;
    Vec3 axis;
    axis.x = q.x;
    axis.y = q.y;
    axis.z = q.z;
    float* p = FUN_0059aed0((float*)&q, (const float*)&va, (const float*)&axis);
    float rx = p[0], ry = p[1], rz = p[2];
    float rr2 = (float)GetRadiusAt((uint)&rx);
    float inv2 = 1.0f / sqrtf((ry * ry + (rz * rz + rx * rx)) + 1e-8f);
    out->x = (inv2 * rx) * rr2;
    out->y = (ry * inv2) * rr2;
    out->z = (rz * inv2) * rr2;
}

// =======================================================================================
// 00b81f90 -- SP::cPlanetModel::IsPositionBelowSurface
// =======================================================================================
int cPlanetModel::IsPositionBelowSurface(const Vec3* dir)
{
    float r = (float)GetRadiusAt((uint)dir);
    float x = dir->x;
    float y = dir->y;
    float z = dir->z;
    float inv = 1.0f / sqrtf((y * y + z * z) + x * x + 1e-8f);
    Vec3 p;
    p.x = (x * inv) * r;
    p.y = r * (y * inv);
    p.z = r * (z * inv);
    if ((dir->z * dir->z + dir->y * dir->y) + dir->x * dir->x <
        (p.x * p.x + p.z * p.z) + p.y * p.y)
        return 1;
    return 0;
}

// =======================================================================================
// 00b82060 -- surface position of a coordinate, fallback to the default direction
// =======================================================================================
Vec3* cPlanetModel::FUN_00b82060(Vec3* out, int a, int b)
{
    Vec3 local;
    if (mpISphere != 0) {
        ((void(__thiscall*)(void*, Vec3*, int, int))VTC(mpSphere, 0x108))(mpSphere, &local, a, b);
        if (!(DAT_016881f0.x == local.x && DAT_016881f0.y == local.y && DAT_016881f0.z == local.z)) {
            DirectionToSurfacePosition(out, &local);
            return out;
        }
    }
    out->x = DAT_016881f0.x;
    out->y = DAT_016881f0.y;
    out->z = DAT_016881f0.z;
    return out;
}

// =======================================================================================
// 00b82110 -- project a position towards a direction and pick the nearer point
// =======================================================================================
void cPlanetModel::FUN_00b82110(Vec3* out, Vec3* pa, Vec3* pb)
{
    Vec3 local;
    FUN_00b82060(&local, (int)pa, (int)pb);
    float r;
    if (mpISphere == 0) {
        r = 0.0f;
    } else {
        int m = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
        r = *(float*)(m + 0x3c) * *(float*)(m + 0x38) + *(float*)(m + 0x34);
    }
    float f1 = pa->x;
    float q;
    if (r * r <= (f1 * f1 + pa->y * pa->y) + pa->z * pa->z &&
        FUN_005a9c40(pa, pb, &DAT_016881f0, r, &q)) {
        float f6 = pa->y + pb->y * q;
        float f8 = pa->z + pb->z * q;
        float f12 = f1 + pb->x * q;
        float near;
        if ((local.x == DAT_016881f0.x && local.y == DAT_016881f0.y && local.z == DAT_016881f0.z) ||
            (near = ((f8 - pa->z) * (f8 - pa->z) + (f6 - pa->y) * (f6 - pa->y)) + (f12 - f1) * (f12 - f1),
             near < ((local.z - pa->z) * (local.z - pa->z) + (local.y - pa->y) * (local.y - pa->y)) +
                    (local.x - f1) * (local.x - f1))) {
            out->x = f12;
            out->y = f6;
            out->z = f8;
            return;
        }
    }
    out->x = local.x;
    out->y = local.y;
    out->z = local.z;
}

// =======================================================================================
// 00b82310 -- surface radius of a subdivided world position
// =======================================================================================
long double cPlanetModel::FUN_00b82310(void* param)
{
    int h = FUN_00b3d310();
    if (*(int*)(h + 0x20) != 0)
        return GetRadiusAt((uint)param);

    Vec3 d;
    DirectionToSurfacePosition(&d, (const Vec3*)param);
    float f1 = d.z * d.z + (d.x * d.x + d.y * d.y);
    float f2 = sqrtf(f1);
    float f5;
    if (mpISphere != 0) {
        int m = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
        if (m != 0) {
            int m2 = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
            f5 = *(float*)(m2 + 0x34);
        } else {
            f5 = 500.0f;
        }
    } else {
        f5 = 500.0f;
    }
    float height = f5 * 2.0f - f2;

    struct Probe {
        Vec3   dir;        // +0x00 (local_6c/68/64)
        Vec3   dir2;       // +0x0c (local_60/5c/58)
        float  height;     // +0x18 (fStack_50)
        int    z0;         // +0x1c
        int    z1;         // +0x20
        int    out[4];     // +0x24 (local_40)
        float  res[3];     // +0x34 (fStack_30/2c/28)
    };
    Probe p;
    p.dir = d;
    p.dir2 = d;
    p.height = height;
    p.z0 = 0;
    p.z1 = 0;
    p.out[0] = 0; p.out[1] = 0; p.out[2] = 0; p.out[3] = 0;
    FUN_00b65b10(&p.dir2, (int)&DAT_0167ecd0, 0, 1, 6, (float*)p.out);
    if (p.out[0] != 0) {
        float v = (p.res[1] * p.res[1] + p.res[2] * p.res[2]) + p.res[0] * p.res[0];
        if (f1 < v)
            return (long double)sqrtf(v);
    }
    return (long double)f2;
}
