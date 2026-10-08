// Slice s0077d800: EASTL vector helpers and shader-constant registration tables.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---- EASTL-ish container helpers ---------------------------------------------------------
struct U32Vec {
    unsigned* begin;   // +0
    unsigned* end;     // +4
    unsigned* cap;     // +8
    void DoInsertValue(unsigned* pos, unsigned* val);   // 0x004558a0
};

extern void __cdecl copy_impl_r(void* a, void* b, void* c);  // 0x00705250
extern void* __cdecl FUN_00706ab0(void* a, void* b, void* c);

struct Vec16 {
    char pad[0x14];
    void Grow(void* a, unsigned b, void* c);   // 0x0077d510
};

struct Vec8Thing {
    char pad[8];
    int  FUN_0077d970(unsigned val);
    void FUN_0077d800(void* first, void* last);
    void FUN_0077d9c0(unsigned n, void* val);
};

struct BigVec {
    char pad[0x14];
    void* FUN_0077e260(unsigned a, unsigned b);
    void* FUN_0077e2c0(void* a, void* b);
};

struct CamThing {
    char pad[0x180];
    void FUN_0077ef60(float* v);
};

#pragma warning(disable:4035)
static __forceinline int FloorToInt(float f) {
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

// @ 0x0077d970
int Vec8Thing::FUN_0077d970(unsigned val) {
    U32Vec* v = (U32Vec*)((char*)this + 8);
    unsigned* end = v->end;
    if (end < v->cap) {
        v->end = end + 1;
        if (end != 0) {
            *end = val;
            return (int)(v->end - v->begin) - 1;
        }
    } else {
        v->DoInsertValue(end, &val);
    }
    return (int)(v->end - v->begin) - 1;
}

// @ 0x0077d9c0
void Vec8Thing::FUN_0077d9c0(unsigned n, void* val) {
    int p = (int)this;
    int end = *(int*)(p + 4);
    int cur = (end - *(int*)(p)) >> 4;
    if (n > (unsigned)cur) {
        ((Vec16*)p)->Grow((void*)end, n - cur, val);
        return;
    }
    int dest = n * 0x10 + *(int*)(p);
    copy_impl_r((void*)end, (void*)end, (void*)dest);
    *(int*)(p + 4) = *(int*)(p + 4) + (((end - dest) >> 4) * -0x10);
}

// @ 0x0077eef0  linear interpolation into a float array (x87 return)
float __cdecl FUN_0077eef0(int n, float* arr, float t) {
    if (n == 1)
        return arr[0];
    t = (float)(n - 1) * t;
    int i = FloorToInt(t);
    float r = arr[i];
    float d = t - (float)i;
    if (d > 0.0f)
        r = (arr[i + 1] - r) * d + r;
    return r;
}

struct Float3 { float x, y, z; };

// @ 0x0077ef60
void CamThing::FUN_0077ef60(float* v) {
    char* th = (char*)this;
    float f = 1.0f - (*(float*)(th + 0x16c) * v[2] +
                      *(float*)(th + 0x168) * v[1] +
                      *(float*)(th + 0x164) * v[0]);
    if (f > *(float*)(th + 0x20c))
        *(Float3*)(th + 0x164) = *(Float3*)v;
    *(Float3*)(th + 0x170) = *(Float3*)v;
}

// ---- partial skeletons (see partial.txt) -------------------------------------------------

// @ 0x0077d800  (partial) vector assign/grow
void Vec8Thing::FUN_0077d800(void* first, void* last) {
    (void)first; (void)last;
}

// @ 0x0077d8c0  (partial) EH destructor: release elements, reset vector, restore vftable
void __fastcall FUN_0077d8c0(void* p) {
    (void)p;
}

// @ 0x0077e260  (partial) EH constructor with inline 0x100-byte storage
void* BigVec::FUN_0077e260(unsigned a, unsigned b) {
    (void)a; (void)b;
    return this;
}

// @ 0x0077e2c0  (partial) EH constructor with inline 0x40-byte storage
void* BigVec::FUN_0077e2c0(void* a, void* b) {
    (void)a; (void)b;
    return this;
}

// @ 0x0077e4a0  (partial) inverse-transform + normalization-constant setup
void __cdecl FUN_0077e4a0(unsigned reg, unsigned p2, int isVS) {
    (void)reg; (void)p2; (void)isVS;
}

// @ 0x0077e6d0  registers the whole rw shader-constant table: SetShaderDef(id, a, b, c, setter),
// then records each constant's size (bytes) in g_shConstSizes[id].
typedef void (__cdecl *ShFn)();
extern void __cdecl SetShaderDef(int id, ShFn a, ShFn b, ShFn c, ShFn setter);   // 0x011f4270
extern int g_shConstSizes[0x340];                                                  // 0x01631ef0
extern "C" void* __cdecl memset(void*, int, size_t);
extern void __cdecl ShNoOp();                    // 0x00c2e4e0 (ret)
extern void __cdecl ShResolveTwo();              // 0x011fb1c0
extern void __cdecl ShUnresolveTwo();            // 0x011fb1f0
extern void __cdecl ShNoOp2();                   // 0x011fb220
extern void __cdecl F777e10(); extern void __cdecl F777e30();
extern void __cdecl F777cb0(); extern void __cdecl F777d60();
extern void __cdecl SkinBones();      extern void __cdecl SkinWeights();    extern void __cdecl UvTweak();
extern void __cdecl ExpandAmount();   extern void __cdecl RatePair();       extern void __cdecl F77da20();
extern void __cdecl TransformBasis(); extern void __cdecl F77daf0();        extern void __cdecl SunDir();
extern void __cdecl Flag();           extern void __cdecl Color();          extern void __cdecl F777e50();
extern void __cdecl F777e90();        extern void __cdecl BoneMatrix3();    extern void __cdecl LightRows();
extern void __cdecl LightRowsXform(); extern void __cdecl ArrayA();         extern void __cdecl F77e320();
extern void __cdecl Normalization();  extern void __cdecl FocusDistance();  extern void __cdecl F77dbc0();
extern void __cdecl F77dc90();        extern void __cdecl ViewportRatios(); extern void __cdecl F777ed0();
extern void __cdecl F779790();        extern void __cdecl Projector();      extern void __cdecl ArrayB();
extern void __cdecl F77dd60();        extern void __cdecl CameraLight();    extern void __cdecl F77de30();
extern void __cdecl DirectionBasis(); extern void __cdecl TransformBlock(); extern void __cdecl F77af70();
extern void __cdecl LightBlock();     extern void __cdecl F777f00();        extern void __cdecl F777f40();
extern void __cdecl F77df00();        extern void __cdecl F77dfd0();        extern void __cdecl F77cd50();
extern void __cdecl F778fd0();        extern void __cdecl F779030();        extern void __cdecl F779130();
extern void __cdecl F77cb40();        extern void __cdecl F77e0a0();        extern void __cdecl F77e170();
extern void __cdecl F777f80();        extern void __cdecl F77c8b0();

void __cdecl FUN_0077e6d0() {
    SetShaderDef(0x200, F777e10, F777e30, F777e30, SkinBones);
    memset(g_shConstSizes, 0, 0xd00);
    SetShaderDef(4, ShResolveTwo, ShUnresolveTwo, ShUnresolveTwo, F777cb0);
    SetShaderDef(3, ShNoOp2, ShNoOp2, ShNoOp2, F777d60);
    SetShaderDef(0x201, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x201] = 8;
    SetShaderDef(0x202, ShNoOp, ShNoOp, ShNoOp, SkinWeights);   g_shConstSizes[0x202] = 0x14;
    SetShaderDef(0x203, ShNoOp, ShNoOp, ShNoOp, UvTweak);   g_shConstSizes[0x203] = 8;
    SetShaderDef(0x204, ShNoOp, ShNoOp, ShNoOp, ExpandAmount);   g_shConstSizes[0x204] = 0x10;
    SetShaderDef(0x205, ShNoOp, ShNoOp, ShNoOp, RatePair);   g_shConstSizes[0x205] = 0x14;
    SetShaderDef(0x206, ShNoOp, ShNoOp, ShNoOp, F77da20);   g_shConstSizes[0x206] = 0x100;
    SetShaderDef(0x207, 0, 0, 0, 0);
    SetShaderDef(0x208, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x208] = 8;
    SetShaderDef(0x209, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x209] = 4;
    SetShaderDef(0x20a, ShNoOp, ShNoOp, ShNoOp, TransformBasis);   g_shConstSizes[0x20a] = 0x40;
    SetShaderDef(0x20b, ShNoOp, ShNoOp, ShNoOp, F77daf0);   g_shConstSizes[0x20b] = 0x40;
    SetShaderDef(0x20c, ShNoOp, ShNoOp, ShNoOp, SunDir);   g_shConstSizes[0x20c] = 0x10;
    SetShaderDef(0x20d, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x20d] = 0x64;
    SetShaderDef(0x20e, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x20e] = 8;
    SetShaderDef(0x20f, ShNoOp, ShNoOp, ShNoOp, Flag);   g_shConstSizes[0x20f] = 8;
    SetShaderDef(0x210, ShNoOp, ShNoOp, ShNoOp, Color);   g_shConstSizes[0x210] = 0x14;
    SetShaderDef(0x211, ShNoOp, ShNoOp, ShNoOp, F777e50);   g_shConstSizes[0x211] = 0x14;
    SetShaderDef(0x212, ShNoOp, ShNoOp, ShNoOp, F777e90);   g_shConstSizes[0x212] = 0x20;
    SetShaderDef(0x213, ShNoOp, ShNoOp, ShNoOp, BoneMatrix3);   g_shConstSizes[0x213] = 0x30;
    SetShaderDef(0x214, 0, 0, 0, LightRows);
    SetShaderDef(0x215, 0, 0, 0, LightRowsXform);
    SetShaderDef(0x216, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x216] = 1;
    SetShaderDef(0x217, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x217] = 1;
    SetShaderDef(0x219, 0, 0, 0, ArrayA);
    SetShaderDef(0x21a, 0, 0, 0, F77e320);
    SetShaderDef(0x254, 0, 0, 0, Normalization);
    SetShaderDef(0x21b, 0, 0, 0, FocusDistance);
    SetShaderDef(0x21c, ShNoOp, ShNoOp, ShNoOp, F77dbc0);   g_shConstSizes[0x21c] = 0x20;
    SetShaderDef(0x21e, ShNoOp, ShNoOp, ShNoOp, F77dc90);   g_shConstSizes[0x21e] = 0x10;
    SetShaderDef(0x21f, 0, 0, 0, ViewportRatios);
    SetShaderDef(0x220, ShNoOp, ShNoOp, ShNoOp, F777ed0);   g_shConstSizes[0x220] = 0x10;
    SetShaderDef(0x221, 0, 0, 0, F779790);
    SetShaderDef(0x222, 0, 0, 0, Projector);
    SetShaderDef(0x223, ShNoOp, ShNoOp, ShNoOp, ArrayB);   g_shConstSizes[0x223] = 0xa4;
    SetShaderDef(0x224, ShNoOp, ShNoOp, ShNoOp, F77dd60);   g_shConstSizes[0x224] = 0x98;
    SetShaderDef(0x225, 0, 0, 0, CameraLight);
    SetShaderDef(0x226, ShNoOp, ShNoOp, ShNoOp, F77de30);   g_shConstSizes[0x226] = 0x10;
    SetShaderDef(0x23e, 0, 0, 0, DirectionBasis);
    SetShaderDef(0x227, 0, 0, 0, TransformBlock);
    SetShaderDef(0x228, 0, 0, 0, F77af70);
    SetShaderDef(0x229, 0, 0, 0, LightBlock);
    SetShaderDef(0x24b, 0, 0, 0, F777f00);
    SetShaderDef(0x252, 0, 0, 0, F777f40);
    SetShaderDef(0x22d, ShNoOp, ShNoOp, ShNoOp, F77df00);   g_shConstSizes[0x22d] = 0x10;
    SetShaderDef(0x22e, ShNoOp, ShNoOp, ShNoOp, F77dfd0);   g_shConstSizes[0x22e] = 0x10;
    SetShaderDef(0x22f, ShNoOp, ShNoOp, ShNoOp, F77cd50);   g_shConstSizes[0x22f] = 0x3fcc;
    SetShaderDef(0x230, ShNoOp, ShNoOp, ShNoOp, F778fd0);   g_shConstSizes[0x230] = 4;
    SetShaderDef(0x231, ShNoOp, ShNoOp, ShNoOp, F779030);   g_shConstSizes[0x231] = 0xc;
    SetShaderDef(0x232, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x232] = 1;
    SetShaderDef(0x237, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x237] = 1;
    SetShaderDef(0x23b, ShNoOp, ShNoOp, ShNoOp, F779130);   g_shConstSizes[0x23b] = 0x60;
    SetShaderDef(0x244, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x244] = 1;
    SetShaderDef(0x22e, ShNoOp, ShNoOp, ShNoOp, F77cb40);   g_shConstSizes[0x22e] = 0x10;
    SetShaderDef(0x245, ShNoOp, ShNoOp, ShNoOp, ShNoOp);   g_shConstSizes[0x245] = 0xc;
    SetShaderDef(0x246, ShNoOp, ShNoOp, ShNoOp, ShNoOp);   g_shConstSizes[0x246] = 0x14;
    SetShaderDef(0x247, ShNoOp, ShNoOp, ShNoOp, F77e0a0);   g_shConstSizes[0x247] = 0x10;
    SetShaderDef(0x248, ShNoOp, ShNoOp, ShNoOp, F77e170);   g_shConstSizes[0x248] = 0x10;
    SetShaderDef(0x255, ShNoOp, ShNoOp, ShNoOp, F777f80);   g_shConstSizes[0x255] = 0x20;
    SetShaderDef(0x256, ShNoOp, ShNoOp, ShNoOp, F77c8b0);
    g_shConstSizes[0x256] = 0x10;
}
