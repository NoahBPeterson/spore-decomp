// Slice s0077f020: shadow/world render state helpers (region 0x77f020-0x77fde0).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern void* FUN_0067dd50();

// Material manager pseudo-object with the two vtable slots used here.
struct Mgr {
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18();
    virtual void f4c(int a, int b, int c);   // slot 19 (0x4c)
    virtual void f50(int a);                 // slot 20 (0x50)
};

struct ShadowCtx {
    char pad0[4];
    unsigned char f04;      // +0x04
    char pad5[0x1b4 - 5];
    int f1b4;               // +0x1b4
    char pad1b8[0x218 - 0x1b8];
    int f218;               // +0x218
    void FUN_0077f510(int v);
    void FUN_0077f5a0(float* a, float* b);
};

// @ 0x0077f510
void ShadowCtx::FUN_0077f510(int v) {
    if (f218 == v)
        return;
    if (f04 && f1b4) {
        Mgr* m = (Mgr*)FUN_0067dd50();
        m->f50(f218);
        m = (Mgr*)FUN_0067dd50();
        m->f4c(f1b4, v, 0);
    }
    f218 = v;
}

struct Float3 { float x, y, z; };

// @ 0x0077f5a0
void ShadowCtx::FUN_0077f5a0(float* a, float* b) {
    char* th = (char*)this;
    float dx = a[0] - *(float*)(th + 0x17c);
    float dy = a[1] - *(float*)(th + 0x180);
    float dz = a[2] - *(float*)(th + 0x184);
    float r = *(float*)(th + 0x208);
    if (r * r < (dx * dx + dy * dy) + dz * dz) {
        *(Float3*)(th + 0x17c) = *(Float3*)a;
        *(Float3*)(th + 0x188) = *(Float3*)b;
    }
}

// @ 0x0077f640
void __fastcall FUN_0077f640(char* p) {
    if (p[0xd] && *(int*)(p + 0x1bc)) {
        if (p[0xc] && p[0xe]) {
            Mgr* m = (Mgr*)FUN_0067dd50();
            m->f4c(*(int*)(p + 0x1bc), *(int*)(p + 0x220), 0);
            return;
        }
        Mgr* m = (Mgr*)FUN_0067dd50();
        m->f50(*(int*)(p + 0x220));
    }
}

// ---- best-effort / partial (see nonmatching.txt / partial.txt) ---------------------------

// @ 0x0077f020  (partial) compiler tail-call thunk forwarding constant 0x12
struct F020 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(int); };
void __fastcall FUN_0077f020(int p) {
    ((F020*)(*(void**)(p + 0xc)))->v3(0x12);
}

// @ 0x0077f2c0  (nonmatching) dispatch over elements calling a virtual per element
int FUN_0077f2c0_best(int p, int idx, int arg3) {
    (void)p; (void)idx; (void)arg3;
    return 0;
}

// @ 0x0077f980  (nonmatching) raster-stage dirty global setup
void __fastcall FUN_0077f980(int p) {
    (void)p;
}

// @ 0x0077f040  (partial) editor shadow-world constructor
void* __fastcall FUN_0077f040(void* p) {
    (void)p;
    return p;
}

// @ 0x0077f210  (partial) editor shadow-world destructor
void __fastcall FUN_0077f210(void* p) {
    (void)p;
}

// @ 0x0077f380  (partial) SP::cRenderConvolutionShadow::BuildBasisMap
void __fastcall FUN_0077f380_build(int p, int a, int b) {
    (void)p; (void)a; (void)b;
}

// @ 0x0077f6a0  (partial) SP::cShadowWorld::SetLightingWorld
void __fastcall FUN_0077f6a0(void* p) {
    (void)p;
}

// @ 0x0077fa70  (partial)
void __cdecl FUN_0077fa70() {
}

// @ 0x0077fb10  (partial)
void __cdecl FUN_0077fb10() {
}

// @ 0x0077fbb0  (partial)
void __cdecl FUN_0077fbb0() {
}

// @ 0x0077fde0  (partial)
void __cdecl FUN_0077fde0() {
}
