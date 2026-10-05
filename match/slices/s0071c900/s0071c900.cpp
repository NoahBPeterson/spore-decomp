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

// @ 0x0071c9e0
void SimCmd_torus_c9e0(IVt* self, int nSegments, float radius)
{
    void** vt = self->mpVtbl;
    ((Fn0)vt[3])(self);
    ((Fn1)vt[0x13])(self, 0);
    float angle = 6.2831853f / (float)(nSegments * 2);
    for (int ring = 0; ring < nSegments / 2; ++ring) {
        float a = angle * (float)(ring * 2);
        ((FnPv)vt[6])(self, &a);
        (void)radius;
    }
}

// @ 0x0071cc20
void SimCmd_cc20(IVt* self, const float* p0, const float* p1)
{
    void** vt = self->mpVtbl;
    ((Fn0)vt[3])(self);
    ((FnPv)vt[6])(self, p0);
    float v[3] = { p1[0], p0[1], p0[2] };
    ((FnPv)vt[6])(self, v);
}

// @ 0x0071cde0
void SimCmd_cde0(IVt* self, const float* p)
{
    void** vt = self->mpVtbl;
    ((Fn0)vt[3])(self);
    ((FnPv)vt[6])(self, p);
    ((FnPv)vt[6])(self, p);
}

// @ 0x0071d0d0
void SP_CreateArrowheadMesh(IVt* self, const float* p)
{
    void** vt = self->mpVtbl;
    ((Fn0)vt[3])(self);
    float v[3] = { p[0], p[1], p[2] };
    ((FnPv)vt[6])(self, v);
    ((Fn1)vt[0x14])(self, 4);
    ((Fn0)vt[0x1f])(self);
    ((Fn0)vt[4])(self);
}

// @ 0x0071d2f0
void SimCmd_d2f0(IVt* self)
{
    void** vt = self->mpVtbl;
    ((Fn0)vt[3])(self);
    float m[12];
    for (int i = 0; i < 12; ++i) m[i] = 0.0f;
    m[2] = 1.0f;
    m[3] = 1.0f;
    m[7] = 1.0f;
    ((FnPv)vt[6])(self, m);
}
