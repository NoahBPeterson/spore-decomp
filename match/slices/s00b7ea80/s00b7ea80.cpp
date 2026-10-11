// Slice s00b7ea80: cPlanetModel terrain/orientation queries + a family of trivially-copyable
// element copy/uninitialized-copy/fill loops (std::copy / uninitialized_copy / fill_n).
//
// The model object owns a cTerrainSphere at +0x20 and a cITerrainSphere at +0x24; most routines
// dispatch through the interface's vtable slot +0x0c to get the concrete map/height source.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"
#include <math.h>

#define VTC(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

// 0x18-byte element: { int; float; float; float; char; char; int } (+2 bytes pad before the int)
struct S18 { int a; float b, c, d; char e; char f; int g; };  // +0x12..+0x13 implicit padding
// 0x24-byte element, layout A: floats 0,4,8,c; int at 0x10; floats 14,18,1c; int at 0x20
struct S24a { float a, b, c, d; int e; float f, g, h; int i; };
// 0x24-byte element, layout B: floats 0..14; int at 0x18; floats 1c,20
struct S24b { float a, b, c, d, e, f; int g; float h, i; };

void  operator_delete__(void* p);                                // 0x00f47380
void  FUN_00f8afd0(unsigned a, unsigned b, float c, int d, int e, int f, void* out); // 0x00f8afd0
void  FUN_00b7e0b0(int p);                                       // 0x00b7e0b0

struct cTerrainMapSet {
    float GetFloat(float* uv);                                   // SP::cTerrainMap<unsigned>::GetFloat 0x00f88650
    float GetHeightAt();                                         // cTerrainMapSet::GetHeightAt 0x00f927c0
};

extern float DAT_0156b614, DAT_0156b618, DAT_0156b61c, DAT_0156b620;
extern float DAT_016881f0, DAT_016881f4, DAT_016881f8;

// =======================================================================================
// 00b7f5c0 -- uninitialized_copy of 0x18-byte elements through an output iterator
// =======================================================================================
S18** FUN_00b7f5c0(S18** out, const S18* first, const S18* last, S18* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->a = first->a; dst->b = first->b; dst->c = first->c; dst->d = first->d;
                dst->e = first->e; dst->f = first->f; dst->g = first->g;
            }
            first++;
            dst++;
        } while (first != last);
        *out = dst;
    }
    return out;
}

// =======================================================================================
// 00b7f630 -- copy a range of 0x18-byte elements
// =======================================================================================
S18* FUN_00b7f630(const S18* first, const S18* last, S18* dst)
{
    while (first != last) {
        if (dst) {
            dst->a = first->a; dst->b = first->b; dst->c = first->c; dst->d = first->d;
            dst->e = first->e; dst->f = first->f; dst->g = first->g;
        }
        first++;
        dst++;
    }
    return dst;
}

// =======================================================================================
// 00b7f710 -- copy a range of 0x24-byte elements (layout A)
// =======================================================================================
S24a* FUN_00b7f710(const S24a* first, const S24a* last, S24a* dst)
{
    while (first != last) {
        if (dst) {
            dst->a = first->a; dst->b = first->b; dst->c = first->c; dst->d = first->d;
            dst->e = first->e; dst->f = first->f; dst->g = first->g; dst->h = first->h;
            dst->i = first->i;
        }
        first++;
        dst++;
    }
    return dst;
}

// =======================================================================================
// 00b7f780 -- uninitialized_copy of 0x24-byte elements (layout B) through an output iterator
// =======================================================================================
void FUN_00b7f780(S24b** out, const S24b* first, const S24b* last, S24b* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->a = first->a; dst->b = first->b; dst->c = first->c; dst->d = first->d;
                dst->e = first->e; dst->f = first->f; dst->g = first->g; dst->h = first->h;
                dst->i = first->i;
            }
            first++;
            dst++;
        } while (first != last);
        *out = dst;
    }
}

// =======================================================================================
// 00b7f800 -- fill_n of 0x24-byte elements (layout B)
// =======================================================================================
void FUN_00b7f800(S24b* dst, unsigned count, const S24b* src)
{
    for (; count > 0; count--) {
        if (dst) {
            dst->a = src->a; dst->b = src->b; dst->c = src->c; dst->d = src->d;
            dst->e = src->e; dst->f = src->f; dst->g = src->g; dst->h = src->h;
            dst->i = src->i;
        }
        dst++;
    }
}

// =======================================================================================
// 00b7f860 -- fill_n of 0x18-byte elements
// =======================================================================================
void FUN_00b7f860(S18* dst, unsigned count, const S18* src)
{
    for (; count > 0; count--) {
        if (dst) {
            dst->a = src->a; dst->b = src->b; dst->c = src->c; dst->d = src->d;
            dst->e = src->e; dst->f = src->f; dst->g = src->g;
        }
        dst++;
    }
}

// =======================================================================================
// 00b7f8b0 -- copy a range of 0x24-byte elements (layout B)
// =======================================================================================
S24b* FUN_00b7f8b0(const S24b* first, const S24b* last, S24b* dst)
{
    while (first != last) {
        if (dst) {
            dst->a = first->a; dst->b = first->b; dst->c = first->c; dst->d = first->d;
            dst->e = first->e; dst->f = first->f; dst->g = first->g; dst->h = first->h;
            dst->i = first->i;
        }
        first++;
        dst++;
    }
    return dst;
}

// =======================================================================================
// the planet model
// =======================================================================================
struct cTerrainSphere {
    void        BuildSurfaceOrientation(Quat* out, const Vec3& a, const Vec3& b) const;      // 0x00f9c960
    void        BuildSurfaceOrientation2(Quat* out, const Vec3& a, const Vec3& b);           // 0x00f9c660
    void        BuildPitchedSurfaceOrientation(Quat* out, const Vec3& a, const Vec3& b, float c); // 0x00f9cc50
    void        BuildSurfaceNormalOrientation(Quat* out, const Vec3& a, const Vec3& b, float c);  // 0x00f9d080
};

struct cPlanetModel {
    char  pad0[0x1c];
    int   f1c;           // +0x1c
    void* mpSphere;      // +0x20
    void* mpISphere;     // +0x24
    float f28;           // +0x28
    char  pad1[0x94 - 0x2c];
    int   f94;           // +0x94
    char  pad2[0xec - 0x98];
    int   fec;           // +0xec

    int   FUN_ea80(const Vec3* v);                    // 0x00b7ea80
    float FUN_ec50();                                 // 0x00b7ec50
    float FUN_ecc0(const Vec3* v);                    // 0x00b7ecc0
    void  FUN_ee70(Vec3* out, Vec3* in);              // 0x00b7ee70
    float GetRadiusAt(unsigned coords);               // 0x00b7ef70
    float FUN_efe0(float p);                          // 0x00b7efe0
    void  FUN_f060(Vec3* out, const Vec3* v, float* frac); // 0x00b7f060
    char  FUN_00b7e3e0(const Vec3* v);                // 0x00b7e3e0
    int   FUN_00b7f4a0(unsigned n);                   // 0x00b7f4a0
    void  FUN_f390(int v);                            // 0x00b7f390
    void  FUN_f510(unsigned n);                       // 0x00b7f510

    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* a);                     // 0x00b7f190
    Quat* BuildSurfaceOrientation_2(Quat* out, const Vec3* a, const Vec3* b);    // 0x00b7f1f0
    Quat* BuildSurfaceOrientation2(Quat* out, const Vec3* a, const Vec3* b);     // 0x00b7f250
    Quat* BuildPitchedSurfaceOrientation(Quat* out, const Vec3* a, const Vec3* b, float c); // 0x00b7f2b0
    Quat* BuildSurfaceNormalOrientation(Quat* out, const Vec3* a, const Vec3* b, float c);  // 0x00b7f320
};

// =======================================================================================
// 00b7ea80 -- planet cube-face / vertex index lookup for a direction
// =======================================================================================
int cPlanetModel::FUN_ea80(const Vec3* v)
{
    float x = v->x, ax = fabsf(x);
    float y = v->y, ay = fabsf(y);
    float z = v->z, az = fabsf(z);
    int i7, i8, i9;
    if (az < ax || az < ay) {
        if (ay < ax) {
            i7 = (int)((y / x + 1.0f) * 32.0f);
            i8 = (int)((z / ax + 1.0f) * 32.0f);
            i9 = (x < 0.0f) ? 3 : 2;
        } else {
            i7 = (int)((z / y + 1.0f) * 32.0f);
            i8 = (int)((x / ay + 1.0f) * 32.0f);
            i9 = (y < 0.0f) ? 5 : 4;
        }
    } else {
        i7 = (int)((x / z + 1.0f) * 32.0f);
        i8 = (int)((y / az + 1.0f) * 32.0f);
        i9 = (z < 0.0f) ? 1 : 0;
    }
    if (i7 == 0x40) i7 = 0x3f;
    if (i8 == 0x40) i8 = 0x3f;
    return (int)*(char*)((i9 * 0x40 + i8) * 0x40 + f94 + i7);
}

// =======================================================================================
// 00b7ec50 -- closest-surface radius for a direction (cached in +0x28)
// =======================================================================================
float cPlanetModel::FUN_ec50()
{
    float out;
    if (f28 < 0.0f) {
        int a = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
        unsigned u1 = *(unsigned*)(a + 0xc);
        int b = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
        unsigned u2 = *(unsigned*)(b + 8);
        int c = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
        FUN_00f8afd0(u1, u2, *(float*)(c + 0x3c), 0, 0, 0, &out);
        f28 = out;
    }
    return f28;
}

// =======================================================================================
// 00b7ecc0 -- sample the terrain map at a direction (cube-face UV)
// =======================================================================================
float cPlanetModel::FUN_ecc0(const Vec3* v)
{
    void* s = mpISphere;
    int m0 = ((int(__thiscall*)(void*))VTC(s, 0xc))(s);
    void* map = *(void**)(m0 + 0xc);
    float f1 = v->x, f2 = v->y, f3 = v->z;
    float a1 = fabsf(f1), a2 = fabsf(f2), a3 = fabsf(f3);
    float u, w;
    if (a3 < a1 || a3 < a2) {
        if (a2 < a1) {
            u = (f2 / f1 + 1.0f) * 0.5f;
            w = (f3 / a1 + 1.0f) * 0.5f;
        } else {
            u = (f3 / f2 + 1.0f) * 0.5f;
            w = (f1 / a2 + 1.0f) * 0.5f;
        }
    } else {
        u = (f1 / f3 + 1.0f) * 0.5f;
        w = (f2 / a3 + 1.0f) * 0.5f;
    }
    int m1 = ((int(__thiscall*)(void*))VTC(s, 0xc))(s);
    float h = *(float*)(m1 + 0x38);
    float r = ((cTerrainMapSet*)map)->GetFloat(&u);
    return r * h;
}

// =======================================================================================
// 00b7ee70 -- build a tangent frame at a direction (cross product of two axes)
// =======================================================================================
void cPlanetModel::FUN_ee70(Vec3* out, Vec3* in)
{
    Vec3 n;
    void* s = mpISphere;
    ((void(__thiscall*)(void*, Vec3*, Vec3*))VTC(s, 0xc))(s, &n, in);
    float x = in->x, y = in->y, z = in->z;
    float inv = 1.0f / sqrtf(x * x + y * y + z * z);
    float nx = n.x, ny = n.y, nz = n.z;
    float a = ny * (inv * z) - nz * (inv * y);
    float b = nx * (inv * y) - ny * (x * inv);
    float c = nz * (x * inv) - nx * (inv * z);
    out->x = c * nz - b * ny;
    out->y = b * nx - nz * a;
    out->z = ny * a - c * nx;
}

// =======================================================================================
// 00b7ef70 -- surface radius at a direction
// =======================================================================================
float cPlanetModel::GetRadiusAt(unsigned coords)
{
    if (mpSphere) {
        cTerrainMapSet* map = (cTerrainMapSet*)((void*(__thiscall*)(void*, unsigned))VTC(mpISphere, 0xc))(mpISphere, coords);
        return map->GetHeightAt();
    }
    if (mpISphere) {
        int m = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
        if (m) {
            int m2 = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
            float r = *(float*)(m2 + 0x34);
            return r;
        }
    }
    float r = 500.0f;
    return r;
}

// =======================================================================================
// 00b7efe0 -- radius clamped up to the terrain surface
// =======================================================================================
float cPlanetModel::FUN_efe0(float p)
{
    float r = GetRadiusAt(*(unsigned*)&p);
    float h;
    if (mpISphere) {
        int m = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
        h = *(float*)(m + 0x3c) * *(float*)(m + 0x38) + *(float*)(m + 0x34);
    } else {
        h = 0.0f;
    }
    if (r < h) {
        if (mpISphere) {
            int m = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
            h = *(float*)(m + 0x3c) * *(float*)(m + 0x38) + *(float*)(m + 0x34);
        } else {
            h = 0.0f;
        }
        r = h;
    }
    return r;
}

// =======================================================================================
// 00b7f060 -- sample position + surface normal against the terrain band
// =======================================================================================
void cPlanetModel::FUN_f060(Vec3* out, const Vec3* v, float* frac)
{
    void* s = mpISphere;
    int m = ((int(__thiscall*)(void*))VTC(s, 0xc))(s);
    float lo = *(float*)(m + 0x48);
    float hi = *(float*)(m + 0x4c);
    float r = FUN_ecc0(v);
    if (lo < r && !FUN_00b7e3e0(v)) {
        *frac = (r - lo) / (hi - lo);
        Vec3 n;
        FUN_ee70(&n, (Vec3*)v);
        float inv = 1.0f / sqrtf(n.x * n.x + n.y * n.y + n.z * n.z + 1e-08f);
        out->x = -(inv * n.x);
        out->y = -(inv * n.y);
        out->z = -(inv * n.z);
        return;
    }
    out->x = DAT_016881f0;
    out->y = DAT_016881f4;
    out->z = DAT_016881f8;
}

// =======================================================================================
// 00b7f190 -- BuildSurfaceOrientation (virtual, 1-arg form)
// =======================================================================================
Quat* cPlanetModel::BuildSurfaceOrientation(Quat* out, const Vec3* a)
{
    if (mpISphere) {
        void** vt = *(void***)mpSphere;
        ((void(__thiscall*)(void*, Quat*, const Vec3*))vt[0x10c / 4])(mpSphere, out, a);
        return out;
    }
    out->x = DAT_0156b614;
    out->y = DAT_0156b618;
    out->z = DAT_0156b61c;
    out->w = DAT_0156b620;
    return out;
}

// =======================================================================================
// 00b7f1f0 -- cTerrainSphere::BuildSurfaceOrientation
// =======================================================================================
Quat* cPlanetModel::BuildSurfaceOrientation_2(Quat* out, const Vec3* a, const Vec3* b)
{
    if (mpISphere) {
        ((cTerrainSphere*)mpSphere)->BuildSurfaceOrientation(out, *a, *b);
        return out;
    }
    out->x = DAT_0156b614;
    out->y = DAT_0156b618;
    out->z = DAT_0156b61c;
    out->w = DAT_0156b620;
    return out;
}

// =======================================================================================
// 00b7f250 -- cTerrainSphere::BuildSurfaceOrientation2
// =======================================================================================
Quat* cPlanetModel::BuildSurfaceOrientation2(Quat* out, const Vec3* a, const Vec3* b)
{
    if (mpISphere) {
        ((cTerrainSphere*)mpSphere)->BuildSurfaceOrientation2(out, *a, *b);
        return out;
    }
    out->x = DAT_0156b614;
    out->y = DAT_0156b618;
    out->z = DAT_0156b61c;
    out->w = DAT_0156b620;
    return out;
}

// =======================================================================================
// 00b7f2b0 -- cTerrainSphere::BuildPitchedSurfaceOrientation
// =======================================================================================
Quat* cPlanetModel::BuildPitchedSurfaceOrientation(Quat* out, const Vec3* a, const Vec3* b, float c)
{
    if (mpISphere) {
        ((cTerrainSphere*)mpSphere)->BuildPitchedSurfaceOrientation(out, *a, *b, c);
        return out;
    }
    out->x = DAT_0156b614;
    out->y = DAT_0156b618;
    out->z = DAT_0156b61c;
    out->w = DAT_0156b620;
    return out;
}

// =======================================================================================
// 00b7f320 -- cTerrainSphere::BuildSurfaceNormalOrientation
// =======================================================================================
Quat* cPlanetModel::BuildSurfaceNormalOrientation(Quat* out, const Vec3* a, const Vec3* b, float c)
{
    if (mpISphere) {
        ((cTerrainSphere*)mpSphere)->BuildSurfaceNormalOrientation(out, *a, *b, c);
        return out;
    }
    out->x = DAT_0156b614;
    out->y = DAT_0156b618;
    out->z = DAT_0156b61c;
    out->w = DAT_0156b620;
    return out;
}

// =======================================================================================
// 00b7f390 -- selection-type setter; drops the cached sphere on a usable transition
// =======================================================================================
void cPlanetModel::FUN_f390(int v)
{
    if (fec != v) {
        if (mpSphere) {
            switch (v) {
            case 0x1654c01: case 0x1654c02: case 0x1654c04:
            case 0x1654c05: case 0x1654c06: case 0x1654c10:
                FUN_00b7e0b0((int)mpSphere);
            }
        }
        fec = v;
    }
}

// =======================================================================================
// 00b7f510 -- rehash the bucket array
// =======================================================================================
void cPlanetModel::FUN_f510(unsigned n)
{
    int table = FUN_00b7f4a0(n);
    unsigned i = 0;
    if (*(unsigned*)((char*)this + 8) != 0) {
        do {
            int node = *(int*)(*(int*)((char*)this + 4) + i * 4);
            while (node) {
                unsigned h = (unsigned)(*(int*)(node + 8) * 0xfd + *(int*)node * 0x25 + *(int*)(node + 4)) % n;
                *(int*)(*(int*)((char*)this + 4) + i * 4) = *(int*)(node + 0x20);
                *(int*)(node + 0x20) = *(int*)(table + h * 4);
                *(int*)(table + h * 4) = node;
                node = *(int*)(*(int*)((char*)this + 4) + i * 4);
            }
            i++;
        } while (i < *(unsigned*)((char*)this + 8));
    }
    int p = *(int*)((char*)this + 4);
    if (*(unsigned*)((char*)this + 8) > 1 && p != *(int*)((char*)this + 0x30)) {
        if (p >= *(int*)((char*)this + 0x24) && p < *(int*)((char*)this + 0x28)) {
            *(int*)p = *(int*)((char*)this + 0x1c);
            *(int*)((char*)this + 0x1c) = p;
            *(int*)((char*)this + 4) = table;
            *(unsigned*)((char*)this + 8) = n;
            return;
        }
        operator_delete__((void*)p);
    }
    *(int*)((char*)this + 4) = table;
    *(unsigned*)((char*)this + 8) = n;
}
