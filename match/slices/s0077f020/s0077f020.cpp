// Slice s0077f020: shadow/world render state helpers (region 0x77f020-0x77fde0).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>
#include <math.h>

extern void* FUN_0067dd50();
extern "C" void* __cdecl FUN_0067dd60();   // 0x0067DD60 returns the graphics manager

namespace rw { namespace graphics {
class Raster {
public:
    struct Locked {
        void* pixelData;             // +0x00
        Raster* raster;              // +0x04
        unsigned int level;          // +0x08
        unsigned int stride;         // +0x0c
        unsigned int sliceStride;    // +0x10
        unsigned int lockFlags;      // +0x14
        unsigned int volumeDepth;    // +0x18
    };
    Raster* Lock(unsigned int, unsigned char, Locked&);   // 0x011EF750
    Raster* Unlock(Locked&);                              // 0x011EF880
};
}}
namespace SP { unsigned int ColorRGBAToU32(const float* c); }   // 0x004580C0

// A reference-counted raster handle.  +0 is the raster, +4 is a flag word and
// +8 is the intrusively ref-counted long used by the manager's handle type.
struct RasterRef {
    rw::graphics::Raster* mRaster;   // +0x00
    unsigned int mFlags;             // +0x04
    volatile long mRefCount;         // +0x08
};

// Material manager pseudo-object.  Only the slots used by this slice are named;
// 0x34 is a release callback and 0x3c creates a raster handle.
struct Mgr {
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12();
    virtual void release(RasterRef* p);      // slot 13 (0x34)
    virtual void p14();
    virtual RasterRef* create(unsigned int name, unsigned int arg,
                              int w, int a, int b, int c, int d, int e); // slot 15 (0x3c)
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

// @ 0x0077fbb0
// Build the 64x2 RGBA gradient lookup used by the shadow convolution.  The
// original samples sin/cos at pi*t, 3pi*t, 5pi*t and 7pi*t, where
// t = (i + 0.5) * 1.9875, and writes two 64-entry colour rows into the locked
// raster (the second row starts 0x100 bytes into the pixel data).
void __cdecl FUN_0077fbb0() {
    static const float kPi = 3.1415927410125732f;   // 0x0153A108
    static const float kT  = 1.9875000715255737f;   // 0x0140E964
    static const unsigned int kRasterName = 0x7543c109u;
    static const unsigned int kRasterArg  = 0x40202100u; // 0x0153A2E8

    Mgr* mgr = (Mgr*)FUN_0067dd60();
    RasterRef* ref = mgr->create(kRasterName, kRasterArg, 0x40, 2, 1, 8, 0x15, 0);

    if (ref)
        _InterlockedIncrement(&ref->mRefCount);

    if ((ref->mFlags & 1u) == 0) {
        Mgr* releaseMgr = (Mgr*)FUN_0067dd60();
        releaseMgr->release(ref);
    }

    rw::graphics::Raster::Locked locked;
    if (ref->mRaster->Lock(2, 0, locked)) {
        unsigned int* row0 = (unsigned int*)locked.pixelData;
        unsigned int* row1 = (unsigned int*)((char*)locked.pixelData + 0x100);
        for (unsigned int i = 0; i < 0x40; ++i) {
            float t = ((float)i + 0.5f) * kT;
            float a = kPi * t;
            float b = a * 3.0f;

            float c0[4];
            c0[0] = (cosf(a) + 1.0f) * 0.5f;
            c0[1] = (cosf(b) + 1.0f) * 0.5f;
            c0[2] = (sinf(a) + 1.0f) * 0.5f;
            c0[3] = (sinf(b) + 1.0f) * 0.5f;
            row0[i] = SP::ColorRGBAToU32(c0);

            float d = a * 5.0f;
            float e = a * 7.0f;
            float c1[4];
            c1[0] = (cosf(d) + 1.0f) * 0.5f;
            c1[1] = (cosf(e) + 1.0f) * 0.5f;
            c1[2] = (sinf(d) + 1.0f) * 0.5f;
            c1[3] = (sinf(e) + 1.0f) * 0.5f;
            row1[i] = SP::ColorRGBAToU32(c1);
        }

        if ((ref->mFlags & 1u) == 0) {
            Mgr* releaseMgr = (Mgr*)FUN_0067dd60();
            releaseMgr->release(ref);
        }
        ref->mRaster->Unlock(locked);
    }

    _InterlockedIncrement(&ref->mRefCount);
    _InterlockedDecrement(&ref->mRefCount);
    if (ref->mRefCount < 1)
        _InterlockedIncrement(&ref->mRefCount);
}

// @ 0x0077fde0  (partial)
void __cdecl FUN_0077fde0() {
}
