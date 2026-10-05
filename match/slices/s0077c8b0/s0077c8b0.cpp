// Slice s0077c8b0: RenderWare shader-constant helpers / small containers (region 0x77c8b0-0x77d7f0).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

// ---- D3D9 device -------------------------------------------------------------------------
extern void* g_pDevice;   // 0x16f89d0
struct D3D9Vtbl { void* slots[112]; };
typedef void (__stdcall *PFN_SetConstF)(void* self, unsigned reg, const float* data, unsigned count);
#define SETVS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[94]))((dev), (reg), (data), (n)))
#define SETPS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[109]))((dev), (reg), (data), (n)))

extern void* FUN_011f1120();
extern float  g_one;                        // 0x1485720

// 0x00777ae0  shader-constant dirty/notify helper
void __cdecl FUN_00777ae0(int code, void* obj, int changed);

// @ 0x0077c970
struct GfxConst {
    void FUN_0077c970(float a, float b, float c, float d);
    void FUN_0077ca20(unsigned idx, float a, float b, float c, float d);
    int  FUN_0077cad0(short id);
    int  FUN_0077cb10(unsigned a, unsigned b);
};

struct ImgElt { void GetImageResource(unsigned arg); };  // 0x00576650

void GfxConst::FUN_0077c970(float a, float b, float c, float d) {
    float* p = (float*)this;
    bool changed = false;
    if (p[0] != a || p[1] != b || p[2] != c || p[3] != d)
        changed = true;
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
    FUN_00777ae0(0x20c, this, changed ? 1 : 0);
}

// @ 0x0077ca20
void GfxConst::FUN_0077ca20(unsigned idx, float a, float b, float c, float d) {
    float* q = (float*)((char*)this + (idx & 0xffff) * 0x10);
    bool changed = false;
    if (q[0] != a || q[1] != b || q[2] != c || q[3] != d)
        changed = true;
    q[0] = a;
    q[1] = b;
    q[2] = c;
    q[3] = d;
    FUN_00777ae0(0x206, this, changed ? 1 : 0);
}

// @ 0x0077cad0
int GfxConst::FUN_0077cad0(short id) {
    int n = (*(int*)((char*)this + 0xc) - *(int*)((char*)this + 8)) >> 2;
    if (n > 0) {
        int* q = *(int**)((char*)this + 8);
        int i = 0;
        do {
            if (*(short*)(*q + 4) == id)
                return i;
            ++i;
            ++q;
        } while (i < n);
    }
    return -1;
}

// @ 0x0077cb10
int GfxConst::FUN_0077cb10(unsigned a, unsigned b) {
    int n1 = *(int*)((char*)this + 0xc) + 1;
    char* elem = (char*)this + n1 * 0x10;
    *(unsigned*)elem = a;
    ((ImgElt*)(elem + 4))->GetImageResource(b);
    *(int*)((char*)this + 0xc) += 1;
    return *(int*)((char*)this + 0xc) - 1;
}

// ---- global shader-constant sources ------------------------------------------------------
extern int*   g_16f6f00;   // 0x16f6f00
extern float* g_16f6e60;   // 0x16f6e60
extern void*  g_16f6ebc;   // 0x16f6ebc
extern void*  g_16f6e64;   // 0x16f6e64
extern float* g_16f6ec8;   // 0x16f6ec8
extern void*  g_16f6dd0;   // 0x16f6dd0
extern float* g_lights0;   // 0x16f8914
extern float  g_1632e28, g_1632e2c, g_1632e30, g_1632e34;  // 0x1632e28

// @ 0x0077c8b0  normalized camera direction + distance
void __cdecl FUN_0077c8b0(unsigned reg, unsigned p2, int isVS) {
    if (g_16f6f00 == 0)
        return;
    int obj = (int)FUN_011f1120();
    float x = *(float*)(obj + 0x30);
    float y = *(float*)(obj + 0x34);
    float z = *(float*)(obj + 0x38);
    float len2 = x * x + (y * y + z * z);
    float inv = 1.0f / (float)sqrt(len2 + 1e-08f);
    float len = (float)sqrt(len2);
    float v[4];
    v[0] = x * inv;
    v[1] = y * inv;
    v[2] = z * inv;
    v[3] = len;
    if (isVS)
        SETVS(g_pDevice, reg, v, 1);
    else
        SETPS(g_pDevice, reg, v, 1);
}

// @ 0x0077d130
float* __fastcall FUN_0077d130(float* p) {
    p[0] = g_1632e28;
    p[1] = g_1632e2c;
    p[2] = g_1632e30;
    p[3] = g_1632e34;
    return p;
}

// @ 0x0077d170
float* __fastcall FUN_0077d170(float* p) {
    for (int i = 0; i < 16; ++i)
        p[i] = 0.0f;
    return p;
}

// ---- remaining slice-53 functions (see nonmatching.txt / partial.txt) --------------------

extern void* g_vtbl_13ef094;  // 0x13ef094
extern void* g_vtbl_140e878;  // 0x140e878

// @ 0x0077d1d0  constructor: install vftable, clear refcount (atomic), install final vftable
struct CtorObj { void* vtbl; int field1; int field2; int field3; int field4; };
void __fastcall FUN_0077d1d0(CtorObj* p) {
    p->vtbl = &g_vtbl_13ef094;
    p->field1 = 0;
    p->vtbl = &g_vtbl_140e878;
    p->field2 = 0;
    p->field3 = 0;
    p->field4 = 0;
}

// @ 0x0077cb40  (partial) dirt/distance shader constant; SSE/x87 body not reproduced
void __cdecl FUN_0077cb40(unsigned reg, unsigned p2, int isVS) {
    (void)reg; (void)p2; (void)isVS;
}

// @ 0x0077cd50  (partial) interpolated light-probe shader constants; SSE body not reproduced
void __cdecl FUN_0077cd50(unsigned reg, unsigned count, int isVS) {
    (void)reg; (void)count; (void)isVS;
}

// @ 0x0077d200  (partial) transform * something shader constants; SSE body not reproduced
void __cdecl FUN_0077d200(unsigned reg, unsigned p2, int isVS) {
    (void)reg; (void)p2; (void)isVS;
}

// @ 0x0077d450  (partial) eastl vector copy with shared-refcount elements; body not reproduced
struct GfxVecSlot {
    void* FUN_0077d450(void* src);
};
void* GfxVecSlot::FUN_0077d450(void* src) {
    (void)src;
    return this;
}

// @ 0x0077d510  (partial) eastl vector grow/reserve; body not reproduced
struct GfxVec {
    unsigned* begin; unsigned* end; unsigned* cap;
    void FUN_0077d510(int a, unsigned b, void* c);
};
void GfxVec::FUN_0077d510(int a, unsigned b, void* c) {
    (void)a; (void)b; (void)c;
}

// @ 0x0077d6c0  (partial) allocate+construct helper; EASTL allocator body not reproduced
void* __cdecl FUN_0077d6c0(unsigned n, void* a, void* b) {
    (void)n; (void)a; (void)b;
    return 0;
}

// @ 0x0077d710  (partial) EH-guarded factory that builds one of two object kinds; body not reproduced
void* __cdecl FUN_0077d710(void* p) {
    (void)p;
    return 0;
}
