// Slice s0071c900: SP::Simulator mesh/primitive command helpers.  Each takes a
// builder interface (vtable calls) and emits geometry.  Optimized module:
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.
#include "types.h"

// Object whose first dword is a vtable of function pointers; slots are at byte
// offsets 0xc, 0x10, 0x18, 0x1c, 0x20, 0x4c, 0x50, 0x58, 0x64, 0x68, 0x7c.
struct IVt {
    void** mpVtbl;      // +0x0
};

typedef void (__thiscall* Fn0)(IVt*);
typedef void (__thiscall* Fn1)(IVt*, int);
typedef void (__thiscall* Fn2)(IVt*, int, int);
struct Vec3 {
    float x, y, z;
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
};
typedef void (__thiscall* FnP)(IVt*, const Vec3&);
typedef void (__thiscall* FnPi)(IVt*, const Vec3&, int);
typedef void (__thiscall* FnPv)(IVt*, const void*);

struct Vector3 {
    float x, y, z;
};

// @ 0x0071c900
void SimCmd_exec_c900(IVt* self)
{
    ((Fn0)self->mpVtbl[3])(self);                          // +0xc
    ((Fn1)self->mpVtbl[0x13])(self, 0);                    // +0x4c(0)
    ((FnP)self->mpVtbl[6])(self, Vec3(0.0f, 0.0f, 0.0f));  // +0x18
    ((FnP)self->mpVtbl[7])(self, Vec3(0.0f, 0.0f, 1.0f));  // +0x1c
    ((FnPi)self->mpVtbl[8])(self, Vec3(0.0f, 0.0f, 0.0f), 0); // +0x20
    ((Fn1)self->mpVtbl[0x14])(self, 4);                    // +0x50(4)
    ((Fn2)self->mpVtbl[0x19])(self, 7, 0);                 // +0x64(7,0)
    ((Fn2)self->mpVtbl[0x19])(self, 7, 0);
    ((Fn2)self->mpVtbl[0x19])(self, 7, 0);
    ((Fn0)self->mpVtbl[0x1f])(self);                       // +0x7c
    ((Fn0)self->mpVtbl[4])(self);                          // tail +0x10
}

// Real identity (see SP::cGraphicsSystem::CreateBuiltinModels at 0x007a7210):
// these are the built-in-model mesh generators fed to a cIMeshBuilder.
//   c900 = unit plane, c9e0 = UV sphere/disc, cc20 = quad, cde0 = box,
//   d0d0 = arrowhead, d2f0 = three-part gizmo.

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
#pragma intrinsic(sin, cos)

// Axis / angle constants in the module's read-only pool.
extern const float   g_angle2Pi;   // 0x0162a8e0  (2*pi)
extern const Vector3 g_axisX;      // 0x01536700
extern const Vector3 g_axisY;      // 0x0153670c
extern const Vector3 g_axisZ;      // 0x01536718

// v8 (+0x20) takes a UV pointer plus a stage flag.
typedef void (__thiscall* FnPvi)(IVt*, const void*, int);

// v26 (+0x68) takes (vertexCount, indexArray, flags).
typedef void (__thiscall* FnVii)(IVt*, int, const int*, int);

// @ 0x0071c9e0  SP::CreateDiscMesh
void __cdecl CreateDiscMesh(IVt* self, float radius, int segments)
{
    ((Fn0)self->mpVtbl[3])(self);       // +0xc  begin mesh
    ((Fn1)self->mpVtbl[0x13])(self, 0); // +0x4c  texture stage 0

    int half = segments / 2;
    if (half >= 0) {
        float fSeg = (float)segments;
        for (int ring = 0; ring <= half; ++ring) {
            float v = (float)(ring * 2) / fSeg;
            float polar = ((float)ring / fSeg) * g_angle2Pi;
            float cosP = (float)cos(polar);
            float sinP = (float)sin(polar);
            for (int i = 0; i <= segments; ++i) {
                float u = (float)i / fSeg;
                float az = u * g_angle2Pi;
                float cosA = (float)cos(az);
                float sinA = (float)sin(az);

                Vector3 p;
                p.x = cosA * sinP * radius;
                p.y = sinA * sinP * radius;
                p.z = cosP * radius;
                ((FnPv)self->mpVtbl[6])(self, &p);      // +0x18 position

                Vector3 n;
                n.x = cosA * sinP;
                n.y = sinA * sinP;
                n.z = cosP;
                ((FnPv)self->mpVtbl[7])(self, &n);      // +0x1c normal

                Vector3 uv;
                uv.x = u;
                uv.y = v;
                uv.z = 0.0f;
                ((FnPvi)self->mpVtbl[8])(self, &uv, 0);  // +0x20 texcoord
            }
        }
    }

    for (int row = 0; row < half; ++row) {
        int rowStart = row * (segments + 1);
        int nextRow = rowStart + segments + 1;
        for (int i = 0; i < segments; ++i) {
            ((Fn1)self->mpVtbl[0x14])(self, 9);         // +0x50 primitive type
            ((Fn2)self->mpVtbl[0x19])(self, 7, rowStart + i);
            ((Fn2)self->mpVtbl[0x19])(self, 7, nextRow + i);
            if (row < half - 1)
                ((Fn2)self->mpVtbl[0x19])(self, 7, nextRow + i + 1);
            if (row > 0)
                ((Fn2)self->mpVtbl[0x19])(self, 7, rowStart + i + 1);
            ((Fn0)self->mpVtbl[0x1f])(self);           // +0x7c end primitive
        }
    }

    ((Fn0)self->mpVtbl[4])(self);       // +0x10 end mesh
}

// @ 0x0071cc20  SP::CreateQuadMesh
void __cdecl CreateQuadMesh(IVt* self, const Vector3& vmin, const Vector3& vmax)
{
    ((Fn0)self->mpVtbl[3])(self);

    Vector3 p;
    p = vmin;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmax.x; p.y = vmin.y; p.z = vmin.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p = vmax;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmin.x; p.y = vmax.y; p.z = vmax.z;
    ((FnPv)self->mpVtbl[6])(self, &p);

    // Normal points along the axis of the thinner dimension.
    float dz = vmax.z - vmin.z;
    float dy = vmax.y - vmin.y;
    if (dz < 0.0f) dz = -dz;
    if (dy < 0.0f) dy = -dy;
    const Vector3* n = (dz <= dy) ? &g_axisZ : &g_axisY;
    ((FnPv)self->mpVtbl[7])(self, n);

    Vector3 uv;
    uv.z = 0.0f;
    uv.x = 0.0f; uv.y = 1.0f; ((FnPvi)self->mpVtbl[8])(self, &uv, 0);
    uv.x = 1.0f; uv.y = 1.0f; ((FnPvi)self->mpVtbl[8])(self, &uv, 0);
    uv.x = 1.0f; uv.y = 0.0f; ((FnPvi)self->mpVtbl[8])(self, &uv, 0);
    uv.x = 0.0f; uv.y = 0.0f; ((FnPvi)self->mpVtbl[8])(self, &uv, 0);

    ((Fn1)self->mpVtbl[0x13])(self, 0);         // +0x4c
    ((Fn1)self->mpVtbl[0x14])(self, 9);         // +0x50
    ((Fn1)self->mpVtbl[0x16])(self, 0);         // +0x58
    ((Fn2)self->mpVtbl[0x19])(self, 5, 0);      // +0x64
    ((Fn2)self->mpVtbl[0x19])(self, 5, 1);
    ((Fn2)self->mpVtbl[0x19])(self, 5, 2);
    ((Fn2)self->mpVtbl[0x19])(self, 5, 3);
    ((Fn0)self->mpVtbl[0x1f])(self);            // +0x7c
    ((Fn0)self->mpVtbl[4])(self);               // +0x10
}

// Six quads of a unit box; each entry is four vertex indices.
static const int s_boxQuads[6][4] = {
    { 1, 3, 7, 5 },
    { 2, 0, 4, 6 },
    { 3, 2, 6, 7 },
    { 0, 1, 5, 4 },
    { 4, 5, 7, 6 },
    { 2, 3, 1, 0 },
};

// @ 0x0071cde0  SP::CreateBoxMesh
void __cdecl CreateBoxMesh(IVt* self, const Vector3& vmin, const Vector3& vmax)
{
    ((Fn0)self->mpVtbl[3])(self);

    Vector3 p;
    p.x = vmin.x; p.y = vmin.y; p.z = vmin.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmax.x; p.y = vmin.y; p.z = vmin.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmin.x; p.y = vmax.y; p.z = vmin.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmax.x; p.y = vmax.y; p.z = vmin.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmin.x; p.y = vmin.y; p.z = vmax.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmax.x; p.y = vmin.y; p.z = vmax.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmin.x; p.y = vmax.y; p.z = vmax.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmax.x; p.y = vmax.y; p.z = vmax.z;
    ((FnPv)self->mpVtbl[6])(self, &p);

    Vector3 n;
    n.x = g_axisX.x; n.y = g_axisX.y; n.z = g_axisX.z;
    ((FnPv)self->mpVtbl[7])(self, &n);
    n.x = -g_axisX.x; n.y = -g_axisX.y; n.z = -g_axisX.z;
    ((FnPv)self->mpVtbl[7])(self, &n);
    n.x = g_axisY.x; n.y = g_axisY.y; n.z = g_axisY.z;
    ((FnPv)self->mpVtbl[7])(self, &n);
    n.x = -g_axisY.x; n.y = -g_axisY.y; n.z = -g_axisY.z;
    ((FnPv)self->mpVtbl[7])(self, &n);
    n.x = g_axisZ.x; n.y = g_axisZ.y; n.z = g_axisZ.z;
    ((FnPv)self->mpVtbl[7])(self, &n);
    n.x = -g_axisZ.x; n.y = -g_axisZ.y; n.z = -g_axisZ.z;
    ((FnPv)self->mpVtbl[7])(self, &n);

    ((Fn1)self->mpVtbl[0x13])(self, 0);         // +0x4c

    for (int k = 0; k < 6; ++k) {
        ((Fn1)self->mpVtbl[0x14])(self, 9);     // +0x50
        ((Fn1)self->mpVtbl[0x16])(self, k);     // +0x58
        ((FnVii)self->mpVtbl[0x1a])(self, 4, s_boxQuads[k], 0); // +0x68
        ((Fn0)self->mpVtbl[0x1f])(self);        // +0x7c
    }

    ((Fn0)self->mpVtbl[4])(self);               // +0x10
}

// Reproduces the retail stack layout: positions followed by the index table in
// one block, which the normal pass walks with a nine-float stride.
union ArrowScratch {
    float   f[33];
    int32_t i[33];
};

// @ 0x0071d0d0  SP::CreateArrowheadMesh
void __cdecl CreateArrowheadMesh(IVt* self, float size)
{
    ((Fn0)self->mpVtbl[3])(self);

    ArrowScratch s;
    for (int k = 0; k < 33; ++k)
        s.i[k] = 0;

    // Four vertices of the arrowhead (tip up, two barbs, one raised centre).
    s.f[0]  = 0.0f;  s.f[1]  = 0.8f;  s.f[2]  = 0.0f;
    s.f[3]  = -0.35f; s.f[4] = -0.4f; s.f[5]  = 0.0f;
    s.f[6]  = 0.0f;  s.f[7]  = 0.0f;  s.f[8]  = 0.4f;
    s.f[9]  = 0.35f; s.f[10] = -0.4f; s.f[11] = 0.0f;

    for (int k = 0; k < 4; ++k) {
        Vector3 p;
        p.x = s.f[k * 3 + 0] * size;
        p.y = s.f[k * 3 + 1] * size;
        p.z = s.f[k * 3 + 2] * size;
        ((FnPv)self->mpVtbl[6])(self, &p);      // +0x18
    }

    ((Fn1)self->mpVtbl[0x13])(self, 0);         // +0x4c

    // Face index table: (0,1,2) (0,2,3) (3,2,1) (3,1,0).
    static const int s_arrowTris[12] = { 0, 1, 2, 0, 2, 3, 3, 2, 1, 3, 1, 0 };
    for (int k = 0; k < 12; ++k)
        s.i[12 + k] = s_arrowTris[k];

    for (int k = 0; k < 4; ++k) {
        const float* w = &s.f[k * 9];
        float a = w[0], b = w[1], c = w[2];
        float d = w[3], e = w[4], f = w[5];
        Vector3 n;
        n.x = e * c - b * f;
        n.y = a * f - d * c;
        n.z = d * b - a * e;
        ((FnPv)self->mpVtbl[7])(self, &n);      // +0x1c
    }

    for (int k = 0; k < 4; ++k) {
        ((Fn1)self->mpVtbl[0x14])(self, 9);     // +0x50
        ((Fn1)self->mpVtbl[0x16])(self, k);     // +0x58
        ((FnVii)self->mpVtbl[0x1a])(self, 3, &s.i[12 + k * 3], 0); // +0x68
        ((Fn0)self->mpVtbl[0x1f])(self);        // +0x7c
    }

    ((Fn0)self->mpVtbl[4])(self);               // +0x10
}

// @ 0x0071d2f0  SP::CreateMesh_d2f0
void __cdecl CreateMesh_d2f0(IVt* self, float size)
{
    ((Fn0)self->mpVtbl[3])(self);

    // Twelve vertices of a three-part gizmo (one part per 4 vertices).
    static const float s_verts[36] = {
        0.0f, 0.0f, 0.1f,   1.0f, 0.0f, 0.0f,
        0.0f, 0.1f, 0.0f,   0.0f, -0.1f, 0.0f,
        0.0f, 0.0f, 0.1f,   0.0f, 1.0f, 0.0f,
        0.1f, 0.0f, 0.0f,   -0.1f, 0.0f, 0.0f,
        0.0f, 0.1f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.1f, 0.0f, 0.0f,   -0.1f, 0.0f, 0.0f,
    };

    for (int k = 0; k < 12; ++k) {
        Vector3 p;
        p.x = s_verts[k * 3 + 0] * size;
        p.y = s_verts[k * 3 + 1] * size;
        p.z = s_verts[k * 3 + 2] * size;
        ((FnPv)self->mpVtbl[6])(self, &p);      // +0x18
    }

    static const int s_idx[9] = { 1, 0, 3, 1, 2, 0, 1, 3, 2 };

    for (int part = 0; part < 3; ++part) {
        ((Fn1)self->mpVtbl[0x13])(self, part);  // +0x4c
        int base = part * 4;
        for (int k = 0; k < 3; ++k) {
            ((Fn1)self->mpVtbl[0x14])(self, 9); // +0x50
            ((Fn1)self->mpVtbl[0x15])(self, s_idx[k * 3 + 0] + base); // +0x54
            ((Fn1)self->mpVtbl[0x15])(self, s_idx[k * 3 + 1] + base);
            ((Fn1)self->mpVtbl[0x15])(self, s_idx[k * 3 + 2] + base);
            ((Fn0)self->mpVtbl[0x1f])(self);    // +0x7c
        }
    }

    ((Fn0)self->mpVtbl[4])(self);               // +0x10
}
