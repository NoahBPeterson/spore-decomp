// s00b146a0.cpp -- 0x00b146a0, one unnamed Spore member function.
//
// A __thiscall routine (this in ecx, `ret 0xc` = three stack arguments:
// float3* arg1, bool arg2, int arg3) that:
//
//   1. bails out if self[0x390] is set;
//   2. if self[0x12] == 0 and the low byte of arg3 == 0, forwards to
//      sub_b13bb0(self, arg1, 0) and returns;
//   3. if arg2 != 0, refreshes the transform at self+0x144 (sub_b0fa70);
//   4. obtains an object from the global factory sub_f48aa0, and if non-null:
//        a = sub_f987f0(obj);
//        b = sub_f927c0(obj->vtbl[3](arg1));
//        s = self->f2b4 + max(a, b);
//        dir = safe_normalise(arg1);                    // 1/sqrt(dot + 1e-8)
//        sub_b0fa70(self+0x18, dir, arg3);              // refresh transform A
//        sub_b0fae0(self+0x3c, dir, arg3);              // refresh transform B
//        v = safe_normalise(dir * s); v.z += 1.0f;
//        sub_f9c660(obj, v);
//        sub_f4ff00(self+0x90, v, arg3);
//   5. if the low byte of arg3 != 0, tears the object down (sub_b118a0) and
//      sets self[0x304] = 1.
//
// The routine interleaves x87 (sqrt/divide/compare) with SSE and calls one
// virtual method plus nine unnamed retail helpers.  The exact expression nesting
// that produced the x87/SSE schedule, and the byte layout of the two transform
// outputs that feed step 4, could not be recovered from the disassembly, so this
// is a faithful structural reconstruction, not a byte-exact one; see
// nonmatching.txt.
#include "types.h"
#include <math.h>

typedef unsigned char u8;
typedef unsigned      u32;
typedef float         f32;

// The retail helpers are __thiscall (receiver in ecx), modelled here as member
// functions -- x86 member functions are __thiscall by default.  They belong to
// several distinct receiver types whose identities are unknown, so one modelling
// type is used for all of them.  Addresses are the retail VAs.
struct SubRecv {
    void b13bb0(void* a, int b);        // 0x00b13bb0
    void b0fa70(void* vec, int c);      // 0x00b0fa70
    f32  f987f0();                      // 0x00f987f0  (float returned in st0)
    f32  f927c0();                      // 0x00f927c0
    void b0fae0(void* vec, int c);      // 0x00b0fae0
    void f9c660(void* out);             // 0x00f9c660
    void f4ff00(void* vec, int c);      // 0x00f4ff00
    void b118a0();                      // 0x00b118a0
};

void* __cdecl sub_f48aa0(void);         // 0x00f48aa0  (no receiver)

// The factory object has a vtable; slot 3 (offset +0x0c) is invoked with arg1 and
// its result is passed as the receiver of sub_f927c0.
struct IObject {
    virtual void  m0();
    virtual void  m1();
    virtual void  m2();
    virtual void* m3(void* a);
};

// Invented placeholder for the (unnamed) class owning 0x00b146a0.
struct SubObject {
    void f00b146a0(f32* arg1, bool arg2, int arg3);
};

// Safe 3-vector normalisation (epsilon at 0x013ec4b8 == 1e-8f).
static inline void safeNormalise3(const f32* v, f32* out)
{
    f32 inv = 1.0f / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + 1e-8f);
    out[0] = v[0] * inv;
    out[1] = v[1] * inv;
    out[2] = v[2] * inv;
}

// @ 0x00b146a0
void SubObject::f00b146a0(f32* arg1, bool arg2, int arg3)
{
    u8* self = (u8*)this;
    SubRecv* r = (SubRecv*)self;

    if (self[0x390])
        return;

    if (!self[0x12] && (arg3 & 0xff) == 0) {
        r->b13bb0(arg1, 0);
        return;
    }

    if (arg2) {
        f32 t = 0.0f;
        ((SubRecv*)(self + 0x144))->b0fa70(&t, arg3);
    }

    IObject* obj = (IObject*)sub_f48aa0();
    if (obj) {
        f32 a = ((SubRecv*)obj)->f987f0();
        f32 b = ((SubRecv*)obj->m3(arg1))->f927c0();
        f32 s = *(f32*)(self + 0x2b4) + (a > b ? a : b);

        f32 dir[3];
        safeNormalise3(arg1, dir);

        ((SubRecv*)(self + 0x18))->b0fa70(dir, arg3);
        ((SubRecv*)(self + 0x3c))->b0fae0(dir, arg3);

        f32 scaled[3];
        scaled[0] = dir[0] * s;
        scaled[1] = dir[1] * s;
        scaled[2] = dir[2] * s;

        f32 v[3];
        safeNormalise3(scaled, v);
        v[2] = v[2] + 1.0f;

        ((SubRecv*)obj)->f9c660(v);
        ((SubRecv*)(self + 0x90))->f4ff00(v, arg3);
    }

    if (arg3 & 0xff) {
        r->b118a0();
        self[0x304] = 1;
    }
}
