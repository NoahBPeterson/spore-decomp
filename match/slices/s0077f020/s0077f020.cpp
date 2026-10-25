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

// ---- editor shadow-world element (0x174-byte record) ------------------------------------
// The element type is only ever handled through its out-of-line methods (0x7c3xxx /
// 0x7c4xxx); no field of it is touched by this slice, so the body is opaque here.
struct Element174 {
    unsigned char mData[0x174];
    void F_7c3f70();                 // 0x007c3f70 construct
    void F_7c4000();                 // 0x007c4000 destroy
    void F_7c3ba0();                 // 0x007c3ba0 destroy-in-place
    void F_7c4dd0(int a);            // 0x007c4dd0 reset
    void F_7c4a60(void* v);          // 0x007c4a60 assign small vector
    void F_7c3ce0(int a, int b);     // 0x007c3ce0 set pair
    void F_7c3c20(void* p);          // 0x007c3c20 set name
    void F_7c4b00(float a, float b); // 0x007c4b00 set two floats
    void F_7c4be0(void* p, int a);   // 0x007c4be0 bind slot
    void F_7c3cc0(void* p);          // 0x007c3cc0 set pointer
    void F_7c3c50(int a);            // 0x007c3c50 set mode
    bool F_7c4fd0();                 // 0x007c4fd0 validate
    void F_7c3c10();                 // 0x007c3c10 commit
};

// ---- cShadowWorld: render-side world state shared by 0x77f6a0 / 0x77f980 -----------------
struct cShadowWorld {
    char pad0[0x0e];
    unsigned char mReady;        // +0x0e
    char pad0f[0x14 - 0x0f];
    unsigned char mFlag14;       // +0x14
    char pad15[0x18 - 0x15];
    void* mPropertyHost;         // +0x18
    char pad1c[0x44 - 0x1c];
    int   mDirty;                // +0x44
    char pad48[0xf4 - 0x48];
    int*  mSrcA;                 // +0xf4
    int*  mSrcB;                 // +0xf8
    int   mTexA;                 // +0xfc
    char pad100[0x104 - 0x100];
    int   mTexB;                 // +0x104
    char pad108[0x1c8 - 0x108];
    float mF1c8;                 // +0x1c8
    float mF1cc;                 // +0x1cc
    int   mI1d0;                 // +0x1d0
    int   mI1d4;                 // +0x1d4
    float mF1d8;                 // +0x1d8
    int   mI1dc;                 // +0x1dc
    int   mI1e0;                 // +0x1e0
    int   mI1e4;                 // +0x1e4
    int   mI1e8;                 // +0x1e8
    int   mI1ec;                 // +0x1ec
    int   mI1f0;                 // +0x1f0
    int   mI1f4;                 // +0x1f4
    int   mI1f8;                 // +0x1f8
    int   mI1fc;                 // +0x1fc
    int   mI200;                 // +0x200
    float mF204;                 // +0x204
    float mF208;                 // +0x208
    float mF20c;                 // +0x20c
    float mF210;                 // +0x210
    float mF214;                 // +0x214
    float mF218;                 // +0x218
    float mF21c;                 // +0x21c
};

// ---- cSPEditorShadowWorld: owns two 0x174-byte element records plus an owner record ------
struct ShadowWorldEditor {
    void* mVT0;                  // +0x00
    void* mVT4;                  // +0x04
    int   mPad8;                 // +0x08
    Element174 mElems[2];        // +0x0c
    void* mWorld;                // +0x2f4
    Element174 mOwner;           // +0x2f8
    unsigned char mFlag46c;      // +0x46c
    int   mCount;                // +0x470
    int   mFlag474;              // +0x474
    unsigned char mFlag478;      // +0x478
};

// ---- relocation targets ------------------------------------------------------------------
extern "C" void* __cdecl F_67dd70();                                          // 0x0067dd70 render manager
extern "C" void  __cdecl F_777ae0(int cmd, void* p, int a);                   // 0x00777ae0
extern "C" void  __cdecl F_6de020(void* tex, void* slot, int arg);            // 0x006de020
extern "C" bool  __cdecl F_6a08b0(void* bag, int id, void* out1, void* out2);// 0x006a08b0 read pair
extern "C" void  __cdecl F_6a10c0(void* bag, int id, void* out1);             // 0x006a10c0 read one
extern "C" void  __cdecl F_40cf10(void* bag, int id, void* out1);             // 0x0040cf10 read float
extern "C" void  __cdecl F_11e0b85(void* dst, int size, int count,
                                   void* ctor, void* dtor);                   // 0x011e0b85 eh vector ctor
extern "C" void  __cdecl F_11e0b22(void* dst, int size, int count,
                                   void* dtor);                               // 0x011e0b22 eh vector dtor

extern void* g_15fd918;             // 0x015fd918 property singleton
extern int   g_1633c90;             // 0x01633c90 raster name
extern int   g_153a2e8;             // 0x0153a2e8 raster arg
extern int   g_table1633e34[];      // 0x01633e34 texture-id table
extern const float g_1486110;       // 0x01486110
extern const float g_13ec4d0;       // 0x013ec4d0
extern const float g_1485720;       // 0x01485720
extern const float g_13ef61c;       // 0x013ef61c
extern const float g_13eb1bc;       // 0x013eb1bc
extern const float g_1488874;       // 0x01488874
extern const float g_140e968;       // 0x0140e968
extern const float g_1471064;       // 0x01471064

// raster-stage dirty flags written by 0x77f980
extern unsigned int g_stageFlags;   // 0x016fa3a8
extern int g_stageTex0;             // 0x016f966c
extern unsigned int g_stageBits0;   // 0x016f954c
extern int g_stage0a;               // 0x016fa154
extern int g_stage0b;               // 0x016fa158
extern int g_stage0c;               // 0x016fa168
extern int g_stage0d;               // 0x016fa164
extern int g_stage0e;               // 0x016fa16c
extern int g_stageTex1;             // 0x016f9670
extern unsigned int g_stageBits1;   // 0x016f9550
extern int g_stage1a;               // 0x016fa18c
extern int g_stage1b;               // 0x016fa190
extern int g_stage1c;               // 0x016fa1a0
extern int g_stage1d;               // 0x016fa19c
extern int g_stage1e;               // 0x016fa1a4

// ============================================================================================
// @ 0x0077f040  cSPEditorShadowWorld constructor (thiscall, ret 0x10)
// ============================================================================================
ShadowWorldEditor* __fastcall FUN_0077f040(ShadowWorldEditor* self, void* world,
                                          int arg2, unsigned char arg3, int count) {
    self->mVT0  = (void*)0x140e954;
    self->mVT4  = (void*)0x140e950;
    self->mPad8 = 0;
    F_11e0b85(&self->mElems[0], 0x174, 2, (void*)0x7c3f70, (void*)0x7c4000);
    self->mWorld = world;
    self->mOwner.F_7c3f70();
    self->mFlag46c = arg3;
    self->mCount   = count;
    self->mFlag474 = 0;
    self->mFlag478 = 0;
    int vec[4] = { 0, 0, arg2, arg2 };
    if (count > 0) {
        Element174* e = &self->mElems[0];
        for (int i = 0; i < count; ++i) {
            e->F_7c4dd0(0);
            e->F_7c4a60(vec);
            e->F_7c3ce0(0xa, 0);
            e->F_7c3c20((void*)0x153a208);
            e->F_7c4b00(1.0f, 1.0f);
            int* slot = (int*)((char*)self->mWorld + 0xfc);
            if (*slot != -1) {
                e->F_7c4be0(slot, 1);
                e->F_7c3cc0(*(void**)((char*)self->mWorld + 0xe8));
            }
            ++e;
        }
    }
    self->mOwner.F_7c4dd0(0);
    self->mOwner.F_7c4a60(vec);
    self->mOwner.F_7c3c20((void*)0x153a208);
    self->mOwner.F_7c3cc0(0);

    void* s = g_15fd918;
    if (s != 0) {
        void* out = 0;
        bool ok = ((bool(__thiscall*)(void*, int, void**))
                       (*(void***)s)[0x24 / 4])(s, 0x688fe4b, &out);
        if (ok && *(unsigned short*)((char*)out + 0x12) == 1) {
            if (*(unsigned char*)((char*)out + 0x10) & 0x30)
                out = *(void**)out;
            self->mFlag478 = *(unsigned char*)out;
        }
    }
    return self;
}

// ============================================================================================
// @ 0x0077f210  cSPEditorShadowWorld destructor (thiscall, ret 0)
// ============================================================================================
void __fastcall FUN_0077f210(ShadowWorldEditor* self) {
    self->mVT0 = (void*)0x140e954;
    self->mVT4 = (void*)0x140e950;
    if (self->mCount > 0) {
        Element174* e = &self->mElems[0];
        for (int i = 0; i < self->mCount; ++i) {
            e->F_7c3ba0();
            ++e;
        }
    }
    self->mOwner.F_7c3ba0();
    self->mOwner.F_7c4000();
    F_11e0b22(&self->mElems[0], 0x174, 2, (void*)0x7c4000);
    self->mVT4 = (void*)0x13ef094;
    self->mVT0 = (void*)0x13eb938;
}

// ============================================================================================
// @ 0x0077f2c0  dispatch one element's 12-byte item list through vcall slot 0xc
// ============================================================================================
void __fastcall FUN_0077f2c0(ShadowWorldEditor* self, int index, void* arg2) {
    Element174* e = &self->mElems[index];
    e->F_7c3c50(7);

    cShadowWorld* w = (cShadowWorld*)self->mWorld;
    F_777ae0(0x223, (char*)w + 0x44, 0);

    unsigned char* begin = (unsigned char*)*(void**)((char*)w + 0x1c);
    int n = (*(int*)((char*)w + 0x20) - *(int*)((char*)w + 0x1c)) / 12;
    int off = 0;
    for (int i = 0; i < n; ++i) {
        unsigned char* it = begin + off;
        void* obj = *(void**)it;
        int   sel = (index != 0) ? *(int*)(it + 8) : *(int*)(it + 4);
        void* out = 0;
        ((void(__thiscall*)(void*, int, int, void**, void*))
             (*(void***)obj)[0xc / 4])(obj, sel, i, &out, arg2);
        off += 0xc;
    }
}

// ============================================================================================
// @ 0x0077f380  build the basis map for one (element, slot) pair
// ============================================================================================
void __fastcall FUN_0077f380(ShadowWorldEditor* self, int a, int b, int c) {
    int id = g_table1633e34[b + a * 2];
    if (id == -1)
        return;

    void* mgr = F_67dd70();
    void* tex = ((void* (__thiscall*)(void*, int))
                     (*(void***)mgr)[0x28 / 4])(mgr, id);

    int k = b + a * 4;
    cShadowWorld* w = (cShadowWorld*)self->mWorld;

    self->mOwner.F_7c4be0((char*)w + k * 8 + 0x12c, 1);
    self->mOwner.F_7c3c50(7);
    if (self->mOwner.F_7c4fd0()) {
        F_777ae0(0x201, 0, 0);
        F_6de020(tex, *(void**)((char*)w + 0xf4), c);
        self->mOwner.F_7c3c10();
    }

    if (self->mFlag46c) {
        void* mgr2 = F_67dd70();
        void* tex2 = ((void* (__thiscall*)(void*, int))
                          (*(void***)mgr2)[0x28 / 4])(mgr2, 0x52d76551);
        self->mOwner.F_7c4be0((char*)w + k * 8 + 0x13c, 1);
        if (self->mOwner.F_7c4fd0()) {
            F_6de020(tex2, *(void**)((char*)w + k * 4 + 0x10c), c);
            self->mOwner.F_7c3c10();
        }

        void* mgr3 = F_67dd70();
        void* tex3 = ((void* (__thiscall*)(void*, int))
                          (*(void***)mgr3)[0x28 / 4])(mgr3, 0x356a4c94);
        self->mOwner.F_7c4be0((char*)w + k * 8 + 0x12c, 1);
        if (self->mOwner.F_7c4fd0()) {
            F_6de020(tex3, *(void**)((char*)w + k * 4 + 0x114), c);
            self->mOwner.F_7c3c10();
        }
    }
}

// ============================================================================================
// @ 0x0077f6a0  cShadowWorld::SetLightingWorld — fill the lighting property block
// ============================================================================================
void __fastcall FUN_0077f6a0(cShadowWorld* self) {
    self->mF1c8 = g_1486110;
    self->mF1cc = g_13ec4d0;
    self->mF1d8 = g_1485720;
    self->mI1d0 = 0;
    self->mI1d4 = 0;
    self->mI1dc = 2;
    self->mI1e0 = (int)0x140e8fc;
    self->mI1e4 = 2;
    self->mI1e8 = (int)0x140e904;
    self->mI1ec = 1;
    self->mI1f0 = (int)0x140e90c;
    self->mI1f4 = 1;
    self->mI1f8 = (int)0x140e910;
    self->mI1fc = 1;
    self->mI200 = (int)0x140e914;
    self->mF204 = g_13ef61c;
    self->mF208 = g_1485720;
    self->mF20c = g_13eb1bc;
    self->mF210 = g_1485720;
    self->mF214 = g_1488874;
    self->mF218 = 0.0f;
    self->mF21c = 0.0f;
    self->mReady = 0;

    if (self->mPropertyHost == 0)
        return;

    void* bag = ((void* (__thiscall*)(void*))
                     (*(void***)self->mPropertyHost)[0x38 / 4])(self->mPropertyHost);

    self->mReady = (unsigned char)F_6a08b0(bag, 0x27f36bb, &self->mI1e4, &self->mI1e8);
    if (!self->mReady)
        return;

    F_6a10c0(bag, 0x27f36b9, &self->mF1c8);
    F_6a08b0(bag, 0x27f36ba, &self->mI1dc, &self->mI1e0);
    if (!self->mReady)
        return;

    F_6a08b0(bag, 0x5d1b951, &self->mI1ec, &self->mI1f0);
    F_6a08b0(bag, 0x5d1b952, &self->mI1f4, &self->mI1f8);

    if (self->mFlag14)
        F_6a08b0(bag, 0x614a8f1, &self->mF1c8, &self->mI200);

    F_6a08b0(bag, 0x6148bad, &self->mI1fc, &self->mI200);
    F_6a10c0(bag, 0x68ce755, &self->mI1d0);
    F_40cf10(bag, 0x692e9aa, &self->mI1dc);
    F_6a10c0(bag, 0x625e847, &self->mI1d4);
    F_40cf10(bag, 0x681a110, &self->mF204);
    F_40cf10(bag, 0x5879278, &self->mF208);
    F_40cf10(bag, 0x5879279, &self->mF20c);
    F_40cf10(bag, 0x587927a, &self->mF210);
    F_40cf10(bag, 0x587927b, &self->mF214);
}

// ============================================================================================
// @ 0x0077f980  cShadowWorld raster-stage dirty-flag setup
// ============================================================================================
void __fastcall FUN_0077f980(cShadowWorld* self) {
    int v = (self->mFlag14 != 0);
    self->mDirty = v;

    int k3 = 3;
    int k2 = k3 - 1;

    if (self->mTexA != -1) {
        int src = *self->mSrcA;
        g_stageFlags |= 0x80u;
        g_stageTex0 = src;
        unsigned int f = g_stageBits0 | 1u;
        f |= (unsigned int)k2;
        f |= 0x20u;
        f |= 0x10u;
        f |= 0x40u;
        g_stage0a = k3;
        g_stage0b = k3;
        g_stage0c = k2;
        g_stage0d = k2;
        g_stageBits0 = f;
        g_stage0e = k2;
    } else {
        g_stageFlags |= 0x80u;
        g_stageTex0 = 0;
    }

    if (self->mTexB != -1) {
        int src = *self->mSrcB;
        g_stageFlags |= 0x100u;
        g_stageTex1 = src;
        unsigned int f = g_stageBits1 | 1u;
        f |= (unsigned int)k2;
        f |= 0x20u;
        f |= 0x10u;
        f |= 0x40u;
        g_stage1a = k3;
        g_stage1b = k3;
        g_stage1c = k2;
        g_stage1d = k2;
        g_stageBits1 = f;
        g_stage1e = k2;
    } else {
        g_stageFlags |= 0x100u;
        g_stageTex1 = 0;
    }
}

// ============================================================================================
// @ 0x0077fa70  copy-construct [first,last) into *out, bumping each element's first object
// ============================================================================================
struct Elem12 { void* mObj; int mA; int mB; };

Elem12** __cdecl FUN_0077fa70(Elem12** out, Elem12* first, Elem12* last, Elem12* dst) {
    *out = dst;
    if (first == last)
        return out;
    while (first != last) {
        Elem12* d = (Elem12*)*out;
        d->mObj = first->mObj;
        if (d->mObj != 0)
            (*(void(__thiscall**)(void*))d->mObj)(d->mObj);   // add-ref through vtable[0]
        d->mA = first->mA;
        d->mB = first->mB;
        *out = d + 1;
        ++first;
    }
    return out;
}

// ============================================================================================
// @ 0x0077fb10  copy-construct [first,last) into dst, bumping each element's first object
// ============================================================================================
Elem12* __cdecl FUN_0077fb10(Elem12* first, Elem12* last, Elem12* dst) {
    if (first == last)
        return dst;
    while (first != last) {
        if (dst != 0) {
            dst->mObj = first->mObj;
            if (dst->mObj != 0)
                (*(void(__thiscall**)(void*))dst->mObj)(dst->mObj);   // add-ref
            dst->mA = first->mA;
            dst->mB = first->mB;
        }
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x0077f020  (partial) compiler tail-call thunk forwarding constant 0x12
struct F020 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(int); };
void __fastcall FUN_0077f020(int p) {
    ((F020*)(*(void**)(p + 0xc)))->v3(0x12);
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

// @ 0x0077fde0
// Build the single 64-entry polynomial gradient (t, t^2, t^3, t^4) used as the
// convolution ramp; writes one row into the locked raster.
void __cdecl FUN_0077fde0() {
    Mgr* mgr = (Mgr*)FUN_0067dd60();
    RasterRef* ref = mgr->create((unsigned int)g_1633c90, (unsigned int)g_153a2e8,
                                 0x40, 1, 1, 8, 0x15, 0);

    if (ref)
        _InterlockedIncrement(&ref->mRefCount);

    if ((ref->mFlags & 1u) == 0) {
        Mgr* releaseMgr = (Mgr*)FUN_0067dd60();
        releaseMgr->release(ref);
    }

    rw::graphics::Raster::Locked locked;
    if (ref->mRaster->Lock(2, 0, locked)) {
        unsigned int* row = (unsigned int*)locked.pixelData;
        for (int i = 0; i < 0x40; ++i) {
            float t = ((float)i + g_1471064) * g_140e968;
            float c[4];
            c[0] = t;
            c[1] = t * t;
            c[2] = t * t * t;
            c[3] = t * t * t * t;
            row[i] = SP::ColorRGBAToU32(c);
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
