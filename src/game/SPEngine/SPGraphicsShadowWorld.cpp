// src/game/SPEngine/SPGraphicsShadowWorld.cpp -- migrated from slice(s) s00782860, s007819d0, s00780b70, s0077ff30, s0077f020 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsShadowWorld.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <math.h>
#include "cSPMatrix4.h"
#include "SP/cPropertyList.h"
#include "SP/cRenderConvolutionShadow.h"
#include "SP/cShadowWorld.h"
#include "SP/cViewer.h"
#include <stddef.h>

// unnamed retail callees and globals (address in the comment)
extern void* FUN_0067dd50();

// ---- items of slice s0077f020 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_0067dd60();   // 0x0067DD60 returns the graphics manager
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
namespace rw {
namespace graphics {
class Raster_s0077_f020 {
public:
    struct Locked {
        void* pixelData;             // +0x00
        Raster_s0077_f020* raster;              // +0x04
        unsigned int level;          // +0x08
        unsigned int stride;         // +0x0c
        unsigned int sliceStride;    // +0x10
        unsigned int lockFlags;      // +0x14
        unsigned int volumeDepth;    // +0x18
    };
    Raster_s0077_f020* Lock(unsigned int, unsigned char, Locked&);   // 0x011EF750
    Raster_s0077_f020* Unlock(Locked&);                              // 0x011EF880
};
}
}
namespace SP {
 unsigned int ColorRGBAToU32(const float* c);   // 0x004580C0
}
struct RasterRef {
    rw::graphics::Raster_s0077_f020* mRaster;   // +0x00
    unsigned int mFlags;             // +0x04
    volatile long mRefCount;         // +0x08
};
struct Mgr {
virtual void p00();
virtual void p01();
virtual void p02();
virtual void p03();
virtual void p04();
virtual void p05();
virtual void p06();
virtual void p07();
virtual void p08();
virtual void p09();
virtual void p10();
virtual void p11();
    virtual void p12();
    virtual void release(RasterRef* p);      // slot 13 (0x34)
    virtual void p14();
    virtual RasterRef* create(unsigned int name, unsigned int arg,
                              int w, int a, int b, int c, int d, int e); // slot 15 (0x3c)
virtual void p16();
virtual void p17();
virtual void p18();
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
struct Float3 { float x, y, z; };
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
struct cShadowWorld_s0077_f020 {
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
struct Elem12 { void* mObj; int mA; int mB; };
// ---- items of slice s0077f020 end

// ---- items of slice s0077ff30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_Unk153a2e8;
extern int   g_16fa3a8;
extern int   g_16f954c, g_16f9550, g_16f9558, g_16f955c;
extern int   g_16f966c, g_16f9670, g_16f9678, g_16f967c, g_16f9680;
extern int   g_16fa168, g_16fa16c, g_16fa164;
extern int   g_16fa1a0, g_16fa19c, g_16fa1a4;
extern int   g_16fa248, g_16fa244, g_16fa24c;
extern int   g_16fa210, g_16fa20c, g_16fa214;
extern float g_140e8f8;
#pragma intrinsic(_InterlockedExchangeAdd)
struct cPropertyList {
    bool GetDescription(uint32_t key);
};
struct Raster {
    int mField0;                    // +0x0 (raster handle / vtable word)
};
struct RectID { int a; int b; };
struct cShadowWorld;
struct ShaderObj {
    char     pad_00[0x1c];
    uint32_t mMatrix44[16];         // +0x1c
    uint32_t mMatrix34[12];         // +0x5c
};
struct Mat44 { uint32_t w[16]; };
struct Mat34 { uint32_t w[12]; };
void Matrix44_ctor(void* out, const void* src);
void Matrix3_Assign(void* out, const void* src);
Raster* CreateRaster(int w, int h, int a, int b, int c);
void    GetImageResource(void* r);
int*    Property_GetInt(void* prop);
void*   FUN_0077f040(cShadowWorld* owner, int a, bool b, int c);
void*   EastlAllocate(unsigned int size, const char* name, int a, int b, int c, int d);
struct cShadowWorld {
    void** vftable;                 // +0x000
    int    mRefCount;               // +0x004
    char   pad_008[5];              // +0x008
    bool   mUnkD;                   // +0x00d
    char   pad_00e[2];
    void*  mLightingWorld;          // +0x010
    bool   mUnk14;                  // +0x014
    bool   mUnk15;                  // +0x015
    char   pad_016[0x044 - 0x016];
    int    mUnk44;                  // +0x044
    char   pad_048[0x0e8 - 0x048];
    Raster* mShadowDB;              // +0x0e8
    char   pad_0ec[0x0f4 - 0x0ec];
    Raster* mShadowMaps[2];         // +0x0f4
    RectID  mShadowMapRectIDs[2];   // +0x0fc
    Raster* mShadowBasisMaps[2][4]; // +0x10c
    RectID  mShadowBasisMapRectIDs[2][4]; // +0x12c
    char   pad_16c[0x1ac - 0x16c];
    float  mUnk1ac;                 // +0x1ac
    char   pad_1b0[0x1bc - 0x1b0];
    void*  mRenderShadow;           // +0x1bc
    int    mUnk1c0;                 // +0x1c0
    bool   mUnk1c4;                 // +0x1c4
    char   pad_1c5[0x220 - 0x1c5];
    int    mUnk220;                 // +0x220

    void Init(int n);
    void Update();
    void Cleanup();
    void Apply();
    void SetLightingWorld();
    void NotifyLighting();
};
struct cRenderConvolutionShadow {
    void**   vftable;               // +0x000
    int      mRefCount;             // +0x004
    char     pad_008[4];
    char     mViewers[2 * 0x174];   // +0x00c
    cShadowWorld* mShadowWorld;     // +0x2f4
    char     pad_2f8[0x470 - 0x2f8];
    int      mNumShadowMaps;        // +0x470
    int      mCounter;              // +0x474
    bool     mDoBlur;               // +0x478

    void DrawLayer(int a, int b, int c, void* arg4);
    void BuildBasisMap(int a, int b, void* c);
    void BuildBasisMapHelper(int a, void* b);
};
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();
};
struct AutoRef {
    void* mpObject;
    AutoRef(void* p) : mpObject(p) {
        if (mpObject)
            _InterlockedExchangeAdd((volatile long*)((char*)mpObject + 8), 1);
    }
    ~AutoRef() {
        if (mpObject) {
            volatile long* rc = (volatile long*)((char*)mpObject + 8);
            _InterlockedExchangeAdd(rc, -1);
            if (_InterlockedExchangeAdd(rc, 0) < 1)
                _InterlockedExchangeAdd(rc, 1);
            else
                _InterlockedExchangeAdd(rc, 0);
        }
    }
};
struct LightingRefHolder {
    char pad0[0x10];
    IRefCounted* mObj;              // +0x10
    void SetLightingWorld(IRefCounted* p);
};
struct BoolFlagHolder {
    char pad0[4];
    bool mFlag;                     // +4
    void SetFlag(bool b);
};
extern cPropertyList* g_AppProperties;
void* Graphics_67dd60();
void* Graphics_67dda0();
void* EffectsManager();
void cShadowWorld::Apply()
{
    if (mUnk14 != 0 && mUnk1ac >= g_140e8f8)
        mUnk44 = 3;
    else
        mUnk44 = 2;

    int t0 = mShadowBasisMaps[0][0]->mField0;
    g_16fa3a8 |= 0x80;
    g_16f954c |= 0x70;
    g_16f966c = t0;
    g_16fa168 = 2;
    g_16fa164 = 2;
    g_16fa16c = 2;
    if (mUnk14 != 0) {
        int t1 = mShadowBasisMaps[0][1]->mField0;
        g_16fa3a8 |= 0x100;
        g_16f9550 |= 0x70;
        g_16f9670 = t1;
        g_16fa1a0 = 2;
        g_16fa19c = 2;
        g_16fa1a4 = 2;
        int t2 = mShadowBasisMaps[1][0]->mField0;
        g_16fa3a8 |= 0x800;
        g_16f955c |= 0x70;
        g_16f967c = t2;
        g_16fa248 = 2;
        g_16fa244 = 2;
        g_16fa24c = 2;
    }

    void* g = Graphics_67dd60();
    AutoRef ar((void*)((void*(__thiscall*)(void*, uint32_t, int, int))((void**)(*(void**)g))[8])(g, 0x7543c109, g_Unk153a2e8, 0));
    void* p = ar.mpObject;
    if (p) {
        if ((*(uint8_t*)((char*)p + 4) & 1) == 0) {
            void* g2 = Graphics_67dd60();
            ((void(__thiscall*)(void*, void*))((void**)(*(void**)g2))[13])(g2, p);
        }
        g_16fa3a8 |= 0x400;
        g_16f9558 |= 0x70;
        g_16f9678 = *(int*)p;
        g_16fa210 = 2;
        g_16fa20c = 2;
        g_16fa214 = 0;
    }
}
void cRenderConvolutionShadow::BuildBasisMapHelper(int, void*) {}
void cRenderConvolutionShadow::DrawLayer(int, int, int, void* arg4)
{
    *((int*)((char*)mShadowWorld + 0x10)) += 1;

    int old = mCounter;
    mCounter = old + 1;
    int idx = old % mNumShadowMaps;

    void* em = EffectsManager();
    ShaderObj* sh = (ShaderObj*)((void*(__thiscall*)(void*))((void**)(*(void**)em))[0x28])(em);

    uint32_t M44[16];
    uint32_t M33[9];
    Matrix44_ctor(M44, sh->mMatrix44);
    Matrix3_Assign(M33, sh->mMatrix34);

    uint32_t s80 = sh->mMatrix34[9];
    uint32_t s84 = sh->mMatrix34[10];
    uint32_t s88 = sh->mMatrix34[11];
    int s966c = g_16f966c;
    int s9670 = g_16f9670;
    int s967c = 0, s9680 = 0;

    g_16fa3a8 |= 0x80;
    g_16f966c = 0;
    if (1 < mNumShadowMaps) { g_16fa3a8 |= 0x800; s967c = g_16f967c; g_16f967c = 0; }
    g_16fa3a8 |= 0x100;
    g_16f9670 = 0;
    if (1 < mNumShadowMaps) { g_16fa3a8 |= 0x1000; s9680 = g_16f9680; g_16f9680 = 0; }

    uint32_t* v = (uint32_t*)(mViewers + idx * 0x174);
    sh->mMatrix34[0] = v[0]; sh->mMatrix34[1] = v[1]; sh->mMatrix34[2] = v[2];
    sh->mMatrix34[3] = v[4]; sh->mMatrix34[4] = v[5]; sh->mMatrix34[5] = v[6];
    sh->mMatrix34[6] = v[8]; sh->mMatrix34[7] = v[9]; sh->mMatrix34[8] = v[10];
    sh->mMatrix34[9] = v[12]; sh->mMatrix34[10] = v[13]; sh->mMatrix34[11] = v[14];
    *(Mat44*)sh->mMatrix44 = *(Mat44*)(v + 0x30);

    if (1 < mNumShadowMaps && mDoBlur) {
        if (idx == 0) {
            BuildBasisMapHelper(1, arg4);
        } else {
            BuildBasisMap(1, 1, arg4);
            BuildBasisMapHelper(0, arg4);
            BuildBasisMap(0, 0, arg4);
            BuildBasisMap(0, 1, arg4);
        }
    } else {
        BuildBasisMapHelper(0, arg4);
        BuildBasisMap(0, 0, arg4);
        if (1 < mNumShadowMaps && mShadowWorld->mUnk1ac >= g_140e8f8) {
            BuildBasisMap(0, 1, arg4);
            BuildBasisMapHelper(1, arg4);
            BuildBasisMap(1, 0, arg4);
        }
    }

    *(Mat44*)sh->mMatrix44 = *(Mat44*)M44;
    *(Mat34*)sh->mMatrix34 = *(Mat34*)M33;
    sh->mMatrix34[9] = s80; sh->mMatrix34[10] = s84; sh->mMatrix34[11] = s88;
    g_16fa3a8 |= 0x80;
    g_16f966c = s966c;
    if (1 < mNumShadowMaps) { g_16fa3a8 |= 0x800; g_16f967c = s967c; }
    g_16fa3a8 |= 0x100;
    g_16f9670 = s9670;
    if (1 < mNumShadowMaps) { g_16fa3a8 |= 0x1000; g_16f9680 = s9680; }
    *((int*)((char*)mShadowWorld + 0x10)) -= 1;
}
static void AssignRef(void** slot, void* p);  // 0x00780270 (defined below; used by a stub's inline body)
void cShadowWorld::Init(int)
{
    int width = 0x200;
    int height = 0x200;
    if (g_AppProperties) {
        void* local = 0;
        if (((bool(__thiscall*)(cPropertyList*, uint32_t, void**))((void**)g_AppProperties)[9])(g_AppProperties, 0x276ac00, &local)
            && *(uint16_t*)((char*)local + 0x12) == 9) {
            width = *Property_GetInt(local);
            height = width;
        }
    }
    int height2 = 0x200;
    if (g_AppProperties) {
        void* local = 0;
        if (((bool(__thiscall*)(cPropertyList*, uint32_t, void**))((void**)g_AppProperties)[9])(g_AppProperties, 0x33cb1dad, &local)
            && *(uint16_t*)((char*)local + 0x12) == 9) {
            height2 = *Property_GetInt(local);
        }
    }

    mShadowDB = CreateRaster(width, width, 1, 2, 0x50);

    void* g = Graphics_67dda0();
    int rid[2];
    ((void(__thiscall*)(void*, int*, int, int, int, int, uint32_t, int))((void**)(*(void**)g))[4])(g, rid, width, width, 0x15, 0, 0xd24f7, 0);
    mShadowMapRectIDs[1].a = rid[0];
    mShadowMapRectIDs[1].b = rid[1];
    ((void(__thiscall*)(void*, int, int, const char*))((void**)(*(void**)g))[0x12])(g, rid[0], rid[1], "ShadowMap");
    void* res = (void*)((void*(__thiscall*)(void*, int, int))((void**)(*(void**)g))[7])(g, mShadowMapRectIDs[1].a, mShadowMapRectIDs[1].b);
    GetImageResource(res);

    bool blur = g_AppProperties->GetDescription(0x5879277);
    int format = mUnk15 ? 0x72 : 0x15;

    int numMaps = height2;
    for (int i = 0; i < numMaps; ++i) {
        int cnt = 2;
        if (i == numMaps - 1)
            cnt = 1;
        for (int j = 0; j < cnt; ++j) {
            int rr[2];
            ((void(__thiscall*)(void*, int*, int, int, int, int, uint32_t, int))((void**)(*(void**)g))[4])(g, rr, width, width, format, 0, 0x140e928, 0);
            if (rr[0] != -1) {
                ((void(__thiscall*)(void*, int, int, const char*))((void**)(*(void**)g))[0x12])(g, rr[0], rr[1], "WorldShadowBasisMap");
                void* obj = (void*)((void*(__thiscall*)(void*, int, int))((void**)(*(void**)g))[7])(g, rr[0], rr[1]);
                int k = i * 4 + j;
                AssignRef((void**)&mShadowBasisMaps[0][k], obj);
                mShadowBasisMapRectIDs[0][k].a = rr[0];
                mShadowBasisMapRectIDs[0][k].b = rr[1];
            }
        }
        if (blur) {
            for (int j = 2; j < 4; ++j) {
                int rr[2];
                ((void(__thiscall*)(void*, int*, int, int, int, int, uint32_t, int))((void**)(*(void**)g))[4])(g, rr, width, width, format, 0, 0x140e928, 0);
                if (rr[0] != -1) {
                    ((void(__thiscall*)(void*, int, int, const char*))((void**)(*(void**)g))[0x12])(g, rr[0], rr[1], "WorldShadowBasisMapBlur");
                    void* obj = (void*)((void*(__thiscall*)(void*, int, int))((void**)(*(void**)g))[7])(g, rr[0], rr[1]);
                    int k = i * 4 + j;
                    AssignRef((void**)&mShadowBasisMaps[0][k], obj);
                    mShadowBasisMapRectIDs[0][k].a = rr[0];
                    mShadowBasisMapRectIDs[0][k].b = rr[1];
                }
            }
        }
    }

    void* s = EastlAllocate(0x47c, "Graphics", 0, 0, 0, 0);
    if (s)
        s = FUN_0077f040(this, 0, blur, 0);
    if (s != mRenderShadow) {
        void* old = mRenderShadow;
        if (s)
            _InterlockedExchangeAdd((volatile long*)((char*)s + 8), 1);
        mRenderShadow = s;
        if (old) {
            volatile long* rc = (volatile long*)((char*)old + 8);
            _InterlockedExchangeAdd(rc, -1);
            if (_InterlockedExchangeAdd(rc, 0) < 1)
                _InterlockedExchangeAdd(rc, 1);
            else
                _InterlockedExchangeAdd(rc, 0);
        }
    }
}
// ---- items of slice s0077ff30 end

// ---- items of slice s00780b70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_FovToTan;                                // @ 0x153a108
extern const float g_DotToStrength;                           // @ 0x153a2f0
extern const float g_BiasScale;                               // @ 0x1633bc4
extern const bool  g_UseViewWindow;                           // @ 0x153a2ec
#pragma intrinsic(sqrt, fabs, tan)
struct Vec3 { float x, y, z; };
struct Mat33 {
    float m[9];
    Mat33(const Mat33& o);                                    // @ 0x41cb40
};
struct Mat44_s0078_0b70 { float m[16]; };
struct cModTracker {
    int GetModificationCount();                               // @ 0x6237a0
};
struct cPropertyList_s0078_0b70 {
    char pad00[0x30];
    cModTracker* mpTracker;                                   // +0x30
    int mLocalVersion;                                        // +0x34
    bool GetDescription(uint32_t key);                        // @ 0x6a25a0
    __forceinline int GetVersion() { return (mpTracker ? mpTracker->GetModificationCount() : 0) + mLocalVersion; }
};
extern cPropertyList_s0078_0b70* g_AppProperties_s0078_0b70;                        // @ 0x15fd918
struct cViewer {
    char pad00[0x40];
    Mat44_s0078_0b70 mViewMatrix;                                        // +0x40
    char pad80[0xc0 - 0x80];
    Mat44_s0078_0b70 mProjMatrix;                                        // +0xc0
    char pad100[0x174 - 0x100];
    void SetTransform(const void* xform);                     // @ 0x7c4d00
    void SetNear(float n);                                    // @ 0x7c4ba0
    void SetFar(float f);                                     // @ 0x7c4bc0
    void SetViewAngleY(float a);                              // @ 0x7c53d0
    void SetViewWindow(float w, float h);                     // @ 0x7c5440
    void GetViewWindow(float* w, float* h);                   // @ 0x7c40c0
    void SetViewScale(float w, float h);                      // @ 0x7c4b00
    void ProjectPoint(Vec3* out, const Vec3* p);              // @ 0x7c4180
    void SetViewShift(float x, float y);                      // @ 0x7c4ad0
};
struct cRenderConvolutionShadow_s0078_0b70 {
    char pad00[0xc];
    cViewer mViewers[3];                                      // +0x0c
    char pad468[4];
    bool mUseConvolution;                                     // +0x46c
    int mNumViewers;                                          // +0x470
    int mFrame;                                               // +0x474
    bool mSliced;                                             // +0x478
};
struct IShadowManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual void SetRenderShadow(cRenderConvolutionShadow_s0078_0b70* rs, int param, int flags);   // 0x4c
};
IShadowManager* GetShadowManager();                           // @ 0x67dd50
struct cShadowWorld_s0078_0b70 {
    void Cleanup();                                           // @ 0x7806a0
    void Update();                                            // @ 0x780ab0
    void RefreshShadowMaterial();                             // @ 0x77f640
    void SetLightingWorld();                                  // @ 0x77f6a0
};
float SampleCurve(int size, const float* curve, float t);     // @ 0x77eef0
float Clamp01(float v);                                       // @ 0x5a6e00
void  Transpose(Mat44_s0078_0b70* out, const Mat44_s0078_0b70* in);                 // @ 0x6ffdc0 (cdecl, returns out)
void  ReportError(int code, int a, int b);                    // @ 0x777ae0
extern const Vec3  g_CameraBase;                              // @ 0x1633bd0
extern const Vec3  g_AxisUp;                                  // @ 0x153a124
extern const Mat33 g_IdentityRot;                             // @ 0x1633d14
struct cShadowXform {
    uint16_t mFlags;                                          // +0x00
    uint16_t mModCount;                                       // +0x02
    Vec3 mTranslation;                                        // +0x04
    float mScale;                                             // +0x10
    Mat33 mRotation;                                          // +0x14
    uint32_t pad38[2];
    __forceinline cShadowXform(const Vec3& t, const Mat33& r) : mFlags(0), mModCount(0), mTranslation(t), mScale(1.0f), mRotation(r) {}
    void LookAlong(const Vec3& up, const Vec3& dir);          // @ 0x6bac90
};
struct cShadowUpdater {
    void** mVtbl;                                             // +0x00 (slot 0x50: OnShadowsUpdated)
    bool mHasTarget;                                          // +0x04
    bool mEnabled;                                            // +0x05
    bool mUpdateEnabled;                                      // +0x06
    char pad07[5];
    bool mConvolution;                                        // +0x0c
    bool mFlagD;                                              // +0x0d
    char pad0e[2];
    int mUserParam;                                           // +0x10
    char pad14[0x2c];
    float mDepthBase;                                         // +0x40
    float mDepthScale;                                        // +0x44
    float mStrength;                                          // +0x48
    float mOne;                                               // +0x4c
    Vec3 mLightDir;                                           // +0x50
    float mLightBias;                                         // +0x5c
    float mFocusScaleA;                                       // +0x60
    float mFocusScaleB;                                       // +0x64
    float mShiftX;                                            // +0x68
    float mShiftY;                                            // +0x6c
    Mat44_s0078_0b70 mLightMatrix;                                       // +0x70
    float mViewMatrix[12];                                    // +0xb0
    char pade0[0x164 - 0xe0];
    Vec3 mShadowDirection;                                    // +0x164
    Vec3 mTargetShadowDirection;                              // +0x170
    Vec3 mTargetLocation;                                     // +0x17c
    Vec3 mTargetUp;                                           // +0x188
    Vec3 mViewerLocation;                                     // +0x194
    float mShadowScale;                                       // +0x1a0
    float mFocus;                                             // +0x1a4
    Vec3 mCameraOffset;                                       // +0x1a8
    cRenderConvolutionShadow_s0078_0b70* mRenderShadow;                  // +0x1b4
    int mCachedVersion;                                       // +0x1b8
    char pad1bc[4];
    float mRangeMin;                                          // +0x1c0
    float mRangeMax;                                          // +0x1c4
    float mFocusMin;                                          // +0x1c8
    float mFocusMax;                                          // +0x1cc
    float mCasterRadiusScale;                                 // +0x1d0
    char pad1d4[4];
    int mScaleCurveSize; float* mScaleCurve;                  // +0x1d4  (scale curve)
    int mStrengthCurveSize; float* mStrengthCurve;            // +0x1dc
    int mDepthCurveSize; float* mDepthCurve;                  // +0x1e4
    int mCasterCurveSize; float* mCasterCurve;                // +0x1ec
    int mFocusCurveSize; float* mFocusCurve;                  // +0x1f4
    float mLightBiasScale;                                    // +0x1fc
    float mLightDirScale;                                     // +0x200
    float mDotSnap;                                           // +0x204
    float mTargetSnap;                                        // +0x208
    char pad20c[4];
    float mShadowDirLerp;                                     // +0x210
    float mScaleSnap;                                         // +0x214
    int mManagerParam;                                        // +0x218

    __forceinline cShadowWorld_s0078_0b70* World() { return (cShadowWorld_s0078_0b70*)((char*)this - 8); }
    __forceinline void OnShadowsUpdated(int param) { ((void (__thiscall*)(cShadowUpdater*, int))mVtbl[0x50 / 4])(this, param); }
    void UpdateShadows();                                     // @ 0x780b70
};
// ---- items of slice s00780b70 end

// ---- items of slice s007819d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefObj {
    virtual void AddRef();
    virtual void Release();
};
struct E12 {
    IRefObj* p;
    int      a;
    int      b;

    E12() {}
    E12(const E12& o) { p = o.p; if (p) p->AddRef(); a = o.a; b = o.b; }
    E12(IRefObj* pp, int aa, int bb) { p = pp; if (p) p->AddRef(); a = aa; b = bb; }
    ~E12() { if (p) p->Release(); }
};
struct Vec12 {
    E12* begin;                     // +0x0
    E12* end;                       // +0x4
    E12* cap;                       // +0x8

    __declspec(noinline) Vec12* Assign(const Vec12& src);           // 0x00782270
    __declspec(noinline) void   Destroy();                          // 0x00781b10
    __declspec(noinline) Vec12* ConstructRange(const Vec12& src);   // 0x00781a60
    __declspec(noinline) void   push_back(const E12& value);        // 0x00782540

    E12*  Allocate(unsigned n, E12* first, E12* last);              // 0x007809f0
    void  DestroyRange(E12* first, E12* last);                      // 0x007809c0
    void  InsertAux(E12* pos, const E12& value);                    // 0x00760ca0
};
struct E36Part {
    Vec12 v;                        // +0x00
    char  pad_0c[8];                // +0x0c
    int   a;                        // +0x14
    bool  b;                        // +0x18
    int   c;                        // +0x1c
    ~E36Part() { v.Destroy(); }
};
struct E36 {
    void* p0;                       // +0x00
    Vec12 v;                        // +0x04
    char  pad_10[8];                // +0x10
    int   a;                        // +0x18
    bool  b;                        // +0x1c
    int   c;                        // +0x20
    E36*  Construct(void* p0a, E36Part src);   // 0x00781c30 (thiscall)
};
struct cSWsub {
    void* vtbl;                     // +0x00
    char  pad04[0x10];              // +0x04
    Vec12 mVec;                     // +0x14
    char  pad20[8];                 // +0x20
    E36*  mE36b;                    // +0x28
    E36*  mE36e;                    // +0x2c
    E36*  mE36c;                    // +0x30
    char  pad34[0x1c4 - 0x34];      // +0x34
    bool  mFlag1c4;                 // +0x1c4
    char  pad1c5[0x21c - 0x1c5];    // +0x1c5
    int   mInt21c;                  // +0x21c
    int   mInt220;                  // +0x220
    int   mInt224;                  // +0x224

    void FUN_007824e0();                            // pop_back-like
    void FUN_007825d0(void* obj, unsigned flag);    // emplace via virtual fetch
    void FUN_00782660(void* obj, unsigned flag);    // emplace a fresh 16-byte object
    void FUN_00782740(void* obj, unsigned flag);    // emplace from a refcounted object
};
void* EastlAllocate(unsigned int size, const char* name, int a, int b, const char* file, int line);
void  EastlFree(void* p);
void  FUN_0077fa70(void* out, void* first, void* last, void* dst, void* extra);
void* FUN_00760ba0(void* first, void* last, void* dst);
void __fastcall FUN_0077f6a0(void* self);
void  FUN_00777ae0(int a, int b, int c);
void  FUN_00780810(void* self);
void  FUN_0077f980(void* self);
struct ShadowSub {
    char pad0[4];
    char mUnk4;
    char mUnk5;
    char mUnk6;
    char pad7[1];
    int  mUnk8;
    char pad_c[4];
    int  mUnk10;
    char pad_14[0x1bc - 0x14];
    bool mUnk1bc;
    void TryApply(int other);
};
// ---- items of slice s007819d0 end

// ---- items of slice s00782860 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct E12_s0078_2860 { void* p; int a; int b; };
struct Vec12_s0078_2860 { E12_s0078_2860* begin; E12_s0078_2860* end; E12_s0078_2860* cap; };
struct E36_s0078_2860 {
    void* p0;                       // +0x00
    Vec12_s0078_2860 v;                        // +0x04 (ends +0x10)
    char  pad_10[8];                // +0x10
    int   a;                        // +0x18
    unsigned char b;                // +0x1c
    int   c;                        // +0x20
};
void  EastlDeallocate(void* p, int a);
void  __fastcall FUN_00781a60(Vec12_s0078_2860* self, int dummy, const Vec12_s0078_2860* src);
E36_s0078_2860*  FUN_00781b80(E36_s0078_2860* first, E36_s0078_2860* last, E36_s0078_2860* dst);
void  FUN_00781cb0(E36_s0078_2860* first, E36_s0078_2860* last, E36_s0078_2860* dst);
void  FUN_00782470(E36_s0078_2860* first, E36_s0078_2860* last, E36_s0078_2860* dst);
void  __fastcall FUN_00782270(Vec12_s0078_2860* self, int dummy, const Vec12_s0078_2860* src);
void  __fastcall FUN_00782A60(int p, int dummy, const E36_s0078_2860* src);
void  __fastcall FUN_00782860(int p, int dummy, const E36_s0078_2860* pos, const E36_s0078_2860* value);
// ---- items of slice s00782860 end

// @ 0x0077f040
ShadowWorldEditor* __fastcall FUN_0077f040(ShadowWorldEditor* self, void* world, int arg2, unsigned char arg3, int count)
{
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

// @ 0x0077f210
void __fastcall FUN_0077f210(ShadowWorldEditor* self)
{
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

// @ 0x0077f2c0
void __fastcall FUN_0077f2c0(ShadowWorldEditor* self, int index, void* arg2)
{
    Element174* e = &self->mElems[index];
    e->F_7c3c50(7);

    cShadowWorld_s0077_f020* w = (cShadowWorld_s0077_f020*)self->mWorld;
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

// @ 0x0077f380
void __fastcall FUN_0077f380(ShadowWorldEditor* self, int a, int b, int c)
{
    int id = g_table1633e34[b + a * 2];
    if (id == -1)
        return;

    void* mgr = F_67dd70();
    void* tex = ((void* (__thiscall*)(void*, int))
                     (*(void***)mgr)[0x28 / 4])(mgr, id);

    int k = b + a * 4;
    cShadowWorld_s0077_f020* w = (cShadowWorld_s0077_f020*)self->mWorld;

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

// @ 0x0077f510
void ShadowCtx::FUN_0077f510(int v)
{
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

// @ 0x0077f5a0
void ShadowCtx::FUN_0077f5a0(float* a, float* b)
{
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
void __fastcall FUN_0077f640(char* p)
{
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

// @ 0x0077f6a0
void __fastcall FUN_0077f6a0(cShadowWorld_s0077_f020* self)
{
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

// @ 0x0077f980
void __fastcall FUN_0077f980(cShadowWorld_s0077_f020* self)
{
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

// @ 0x0077fa70
Elem12** __cdecl FUN_0077fa70(Elem12** out, Elem12* first, Elem12* last, Elem12* dst)
{
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

// @ 0x0077fb10
Elem12* __cdecl FUN_0077fb10(Elem12* first, Elem12* last, Elem12* dst)
{
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

// @ 0x0077fbb0
void __cdecl FUN_0077fbb0()
{
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

    rw::graphics::Raster_s0077_f020::Locked locked;
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
void __cdecl FUN_0077fde0()
{
    Mgr* mgr = (Mgr*)FUN_0067dd60();
    RasterRef* ref = mgr->create((unsigned int)g_1633c90, (unsigned int)g_153a2e8,
                                 0x40, 1, 1, 8, 0x15, 0);

    if (ref)
        _InterlockedIncrement(&ref->mRefCount);

    if ((ref->mFlags & 1u) == 0) {
        Mgr* releaseMgr = (Mgr*)FUN_0067dd60();
        releaseMgr->release(ref);
    }

    rw::graphics::Raster_s0077_f020::Locked locked;
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

// @ 0x0077ff30
void cRenderConvolutionShadow::BuildBasisMap(int, int, void*)
{}

// @ 0x00780210
void LightingRefHolder::SetLightingWorld(IRefCounted* p)
{
    IRefCounted* old = mObj;
    if (p != old) {
        if (p)
            p->AddRef();
        mObj = p;
        if (old)
            old->Release();
    }
    ((cShadowWorld*)((char*)this - 8))->SetLightingWorld();
}

// @ 0x00780250
void BoolFlagHolder::SetFlag(bool b)
{
    if (mFlag != b) {
        mFlag = b;
        ((cShadowWorld*)((char*)this - 8))->NotifyLighting();
    }
}

// @ 0x00780270
static void AssignRef(void** slot, void* p)
{
    void* old = *slot;
    if (p != old) {
        if (p)
            _InterlockedExchangeAdd((volatile long*)((char*)p + 8), 1);
        *slot = p;
        if (old) {
            volatile long* rc = (volatile long*)((char*)old + 8);
            _InterlockedExchangeAdd(rc, -1);
            if (_InterlockedExchangeAdd(rc, 0) < 1)
                _InterlockedExchangeAdd(rc, 1);
            else
                _InterlockedExchangeAdd(rc, 0);
        }
    }
}

// @ 0x00780b70
void cShadowUpdater::UpdateShadows()
{
    cPropertyList_s0078_0b70* props = g_AppProperties_s0078_0b70;
    bool enabled = props->GetDescription(0x276abef) && props->GetDescription(0x276abf0);
    if (enabled != mEnabled) {
        if (!enabled) {
            if (mRenderShadow != 0)
                World()->Cleanup();
        } else if (mRenderShadow == 0) {
            World()->Update();
        }
        mEnabled = enabled;
    }

    bool active;
    if (!mEnabled || !mHasTarget) {
        active = false;
    } else {
        active = true;
        World()->SetLightingWorld();
    }
    World()->RefreshShadowMaterial();

    if (!active || !mUpdateEnabled) {
        ReportError(0x223, 0, 0);
        return;
    }

    // Re-read the property flags whenever the property list was modified.
    props = g_AppProperties_s0078_0b70;
    if (mCachedVersion != props->GetVersion()) {
        mCachedVersion = props->GetVersion();
        bool convolution = props->GetDescription(0x276abf8);
        bool flagB = props->GetDescription(0x5879277);
        bool flagD = props->GetDescription(0x65a8c87);
        if (mConvolution != convolution || mRenderShadow->mUseConvolution != flagB || mFlagD != flagD) {
            World()->Cleanup();
            World()->Update();
            GetShadowManager()->SetRenderShadow(mRenderShadow, mManagerParam, 0);
        }
    }

    // Distance from the viewer to the shadow target, mapped through the curves.
    Vec3 toViewer;
    toViewer.x = mViewerLocation.x - mTargetLocation.x;
    toViewer.y = mViewerLocation.y - mTargetLocation.y;
    toViewer.z = mViewerLocation.z - mTargetLocation.z;
    float dist = (float)sqrt((double)(toViewer.z * toViewer.z + toViewer.y * toViewer.y + toViewer.x * toViewer.x));
    float u = (dist - mRangeMin) / (mRangeMax - mRangeMin);
    float t = 0.0f;
    if (0.0f <= u) t = u;
    if (1.0f <= t) t = 1.0f;

    float strength = SampleCurve(mStrengthCurveSize, mStrengthCurve, t);
    float scaleTarget = SampleCurve(mScaleCurveSize, mScaleCurve, t);
    if (mScaleSnap < fabs((double)(mShadowScale - scaleTarget)))
        mShadowScale = (float)scaleTarget;

    // Steer the shadow direction toward the target direction, then renormalise it.
    float lerp = mShadowDirLerp;
    float inv = 1.0f - lerp;
    float dx = mTargetShadowDirection.x * lerp + mShadowDirection.x * inv;
    float dy = mTargetShadowDirection.y * lerp + mShadowDirection.y * inv;
    float dz = mTargetShadowDirection.z * lerp + mShadowDirection.z * inv;
    mShadowDirection.x = dx;
    mShadowDirection.y = dy;
    mShadowDirection.z = dz;
    float invLen = 1.0f / (float)sqrt((double)(dz * dz + (dy * dy + dx * dx)));
    mShadowDirection.x = invLen * dx;
    mShadowDirection.y = invLen * dy;
    mShadowDirection.z = invLen * dz;

    float dot = (mShadowDirection.z * mTargetUp.z + mShadowDirection.y * mTargetUp.y) + mShadowDirection.x * mTargetUp.x;
    float s = (float)fabs((double)dot) * g_DotToStrength;
    float dotFactor = 0.0f;
    if (0.0f <= s) dotFactor = s;
    if (1.0f <= dotFactor) dotFactor = 1.0f;
    strength = dotFactor * strength;
    if (dot < mDotSnap)
        mShadowDirection = mTargetUp;

    float casterDist = SampleCurve(mCasterCurveSize, mCasterCurve, t);
    float camDist = SampleCurve(mDepthCurveSize, mDepthCurve, t);
    if (camDist - 0.01f < casterDist)
        casterDist = camDist - 0.01f;
    float nearLimit = dist;
    if (casterDist <= dist)
        nearLimit = casterDist;

    float angle = mShadowScale;
    double tanValue = tan((double)g_FovToTan * 0.0027777778 * angle);
    float window = (float)(tanValue * camDist);
    if (nearLimit <= window)
        nearLimit = window;
    float farSpan = camDist + casterDist;

    // Aim the camera so the target stays inside the window.
    float along = (mTargetUp.z * toViewer.y + mTargetUp.y * toViewer.z) + mTargetUp.x * toViewer.x;
    float perpSq = dist * dist - along * along;
    float perp = 0.0f;
    if (0.0f <= perpSq) perp = perpSq;
    float room = (float)((tanValue * camDist) * mCasterRadiusScale - sqrt((double)perp));
    float roomClamped = 0.0f;
    if (0.0f <= room) roomClamped = room;
    float invDist = 1.0f / (dist + 1e-06f);
    Vec3 aim;
    aim.x = (-(toViewer.x - mTargetUp.x * along) * roomClamped) * invDist;
    aim.y = (-(toViewer.y - mTargetUp.y * along) * roomClamped) * invDist;
    aim.z = (-(toViewer.z - mTargetUp.z * along) * roomClamped) * invDist;
    float aimDx = aim.x - mCameraOffset.x;
    float aimDy = aim.y - mCameraOffset.y;
    float aimDz = aim.z - mCameraOffset.z;
    if (mTargetSnap * mTargetSnap < (aimDz * aimDz + aimDy * aimDy) + aimDx * aimDx)
        mCameraOffset = aim;

    cRenderConvolutionShadow_s0078_0b70* rs = mRenderShadow;
    float bias = (((mShadowDirection.z * mCameraOffset.z + mShadowDirection.y * mCameraOffset.y)
                   + mCameraOffset.x * mShadowDirection.x)) * g_BiasScale;
    float nearA = bias + (camDist - casterDist);
    float farA = bias + farSpan;
    float nearB = bias + (camDist - nearLimit);
    float farB = bias + (nearLimit + camDist);
    float shiftX = 0.0f;
    float shiftY = 0.0f;

    if (!rs->mSliced || rs->mFrame % rs->mNumViewers == 0) {
        if (!mConvolution) {
            mFocus = 1.0f;
        } else {
            float lo = mFocusMin;
            if (mFocusMax <= lo) {
                mFocus = SampleCurve(mFocusCurveSize, mFocusCurve, t);
            } else {
                float f = Clamp01((dist - lo) / (mFocusMax - lo));
                mFocus = 1.0f / SampleCurve(mFocusCurveSize, mFocusCurve, f);
            }
        }
        float invFocus = 1.0f / mFocus;

        cShadowXform xform(g_CameraBase, g_IdentityRot);
        Vec3 negDir;
        negDir.x = -mShadowDirection.x;
        negDir.y = -mShadowDirection.y;
        negDir.z = -mShadowDirection.z;
        xform.LookAlong(g_AxisUp, negDir);
        xform.mFlags |= 4;
        xform.mModCount++;
        xform.mTranslation.x = ((mShadowDirection.x * camDist + mTargetLocation.x) + mCameraOffset.x) + xform.mTranslation.x;
        xform.mTranslation.y = (mCameraOffset.y + (mTargetLocation.y + mShadowDirection.y * camDist)) + xform.mTranslation.y;
        xform.mTranslation.z = (mCameraOffset.z + (mTargetLocation.z + mShadowDirection.z * camDist)) + xform.mTranslation.z;

        for (int i = 0; i < rs->mNumViewers; i++) {
            cViewer* v = &rs->mViewers[i];
            v->SetTransform(&xform);
            v->SetNear(bias + nearA);
            v->SetFar(bias + farA);
            if (!g_UseViewWindow)
                v->SetViewAngleY(angle);
            else
                v->SetViewWindow((float)(tanValue * camDist), (float)(tanValue * camDist));
            if (i == 0 && mFocus >= 1.5f) {
                float w, h;
                v->GetViewWindow(&w, &h);
                w = w * invFocus;
                h = h * invFocus;
                v->SetViewScale(w, h);
                float sx, sy;
                if (mCasterRadiusScale <= 0.0f) {
                    sx = 0.0f;
                    sy = 0.0f;
                } else {
                    Vec3 p0, p1, probe;
                    v->ProjectPoint(&p0, &mTargetLocation);
                    probe.x = mTargetLocation.x + mCameraOffset.x;
                    probe.y = mTargetLocation.y + mCameraOffset.y;
                    probe.z = mTargetLocation.z + mCameraOffset.z;
                    v->ProjectPoint(&p1, &probe);
                    shiftY = p0.y - p1.y;
                    shiftX = p0.x - p1.x;
                    sy = -(h * shiftY);
                    sx = -(w * shiftX);
                }
                v->SetViewShift(sx, sy);
            }
        }
        OnShadowsUpdated(mUserParam);
    }

    rs = mRenderShadow;
    if (!rs->mSliced || rs->mFrame % rs->mNumViewers == 1) {
        float farPlane = bias + (nearLimit + camDist);
        float nearPlane = nearB;
        Mat44_s0078_0b70 m = rs->mViewers[0].mProjMatrix;
        Mat44_s0078_0b70 tmp;
        Transpose(&tmp, &m);
        m = tmp;
        mLightMatrix = m;
        Mat44_s0078_0b70 m2 = rs->mViewers[0].mViewMatrix;
        Transpose(&tmp, &m2);
        m2 = tmp;
        for (int k = 0; k < 12; k++)
            mViewMatrix[k] = m2.m[k];

        mDepthBase = bias + nearPlane;
        mOne = 1.0f;
        mDepthScale = 1.0f / (farPlane - nearPlane);
        mStrength = strength;
        mFocusScaleA = 1.0f / mFocus;
        mFocusScaleB = 1.0f / mFocus;
        mShiftX = shiftX;
        mShiftY = shiftY;
    }
    mLightDir.x = mLightDirScale * mShadowDirection.x;
    mLightDir.y = mShadowDirection.y * mLightDirScale;
    mLightDir.z = mShadowDirection.z * mLightDirScale;
    mLightBias = -(mLightBiasScale * mLightDirScale);
}

// @ 0x007819d0
void ShadowSub::TryApply(int other)
{
    ShadowSub* self = this;
    if (self->mUnk8 != 0)
        return;
    if (self->mUnk10 != 0 && other == self->mUnk10 && self->mUnk5 && self->mUnk4 && self->mUnk6) {
        FUN_00777ae0(0x20a, 0, 0);
        FUN_00777ae0(0x20b, 0, 0);
        FUN_00777ae0(0x223, (int)self + 0x3c, 1);
        if (self->mUnk1bc) {
            FUN_00780810((char*)self - 8);
            return;
        }
        FUN_0077f980((char*)self - 8);
        return;
    }
    FUN_00777ae0(0x223, 0, 0);
}

// @ 0x00781a60
Vec12* Vec12::ConstructRange(const Vec12& src)
{
    int count = (int)(src.end - src.begin) / 0xc;
    E12* buf;
    if (count == 0)
        buf = 0;
    else
        buf = (E12*)EastlAllocate(count * 0xc, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    begin = buf;
    end = buf;
    cap = (E12*)((char*)buf + count * 0xc);
    void* tmp = 0;
    FUN_0077fa70(&tmp, src.begin, src.end, buf, (void*)&src);
    end = (E12*)tmp;
    return this;
}

// @ 0x00782270
Vec12* Vec12::Assign(const Vec12& src)
{
    if (&src == this)
        return this;

    unsigned newCount = (unsigned)(src.end - src.begin) / 0xc;
    E12* oldBegin = begin;

    if ((unsigned)(cap - begin) / 0xc < newCount) {
        E12* fresh = Allocate(newCount, src.begin, src.end);
        DestroyRange(begin, end);
        if (begin && *(int*)((char*)begin - 4) != 0)
            EastlFree(begin);
        cap = (E12*)((char*)fresh + newCount * 0xc);
        begin = fresh;
        end = (E12*)((char*)fresh + newCount * 0xc);
        return this;
    }

    unsigned oldCount = (unsigned)(end - oldBegin) / 0xc;
    if (oldCount < newCount) {
        FUN_00760ba0(src.begin, (E12*)((char*)src.begin + oldCount * 0xc), oldBegin);
        void* srcEnd = src.end;
        void* tmp = 0;
        FUN_0077fa70(&tmp, (E12*)((char*)src.begin + ((char*)end - (char*)begin)),
                     srcEnd, end, srcEnd);
        end = (E12*)((char*)begin + newCount * 0xc);
        return this;
    }

    void* fresh = FUN_00760ba0(src.begin, src.end, oldBegin);
    DestroyRange((E12*)fresh, end);
    end = (E12*)((char*)begin + newCount * 0xc);
    return this;
}

// @ 0x007824e0
void cSWsub::FUN_007824e0()
{
    E36* last = (E36*)((char*)mE36e - 0x24);
    ((void(__thiscall*)(void*, void*))((void**)(*(void**)this))[0x10 / 4])(this, last->p0);
    mVec.Assign(last->v);
    mInt21c = last->a;
    ((void(__thiscall*)(void*, int))((void**)(*(void**)this))[0x14 / 4])(this, last->c);
    ((void(__thiscall*)(void*, int))((void**)(*(void**)this))[0x28 / 4])(this, last->b);
    FUN_0077f6a0((char*)this - 8);
    mE36e = (E36*)((char*)mE36e - 0x24);
    mE36e->v.Destroy();
}

// @ 0x00782860
void __fastcall FUN_00782860(int p, int dummy, const E36_s0078_2860* pos, const E36_s0078_2860* value)
{
    E36_s0078_2860* end = *(E36_s0078_2860**)(p + 4);
    if (end != *(E36_s0078_2860**)(p + 8)) {
        if (pos <= value && value < end)
            value = (const E36_s0078_2860*)((const char*)value + 0x24);
        E36_s0078_2860 tmp;
        tmp.p0 = end[-1].p0;
        FUN_00781a60(&tmp.v, 0, &end[-1].v);
        tmp.a = end[-1].a;
        tmp.b = end[-1].b;
        tmp.c = end[-1].c;
        FUN_00782470((E36_s0078_2860*)pos, (E36_s0078_2860*)((char*)end - 0x24), end);
        ((E36_s0078_2860*)pos)->p0 = value->p0;
        FUN_00782270(&((E36_s0078_2860*)pos)->v, 0, &value->v);
        ((E36_s0078_2860*)pos)->a = value->a;
        ((E36_s0078_2860*)pos)->b = value->b;
        ((E36_s0078_2860*)pos)->c = value->c;
        *(E36_s0078_2860**)(p + 4) = (E36_s0078_2860*)((char*)end + 0x24);
        return;
    }
    int count = (int)(end - *(E36_s0078_2860**)p) / 0x24;
    int cap = count ? count * 2 : 1;
    int alloc = cap * 0x24;
    E36_s0078_2860* buf = (E36_s0078_2860*)EastlAllocate(alloc, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    E36_s0078_2860* e1 = (E36_s0078_2860*)FUN_00781b80(*(E36_s0078_2860**)p, (E36_s0078_2860*)pos, buf);
    FUN_00781cb0(*(E36_s0078_2860**)p, (E36_s0078_2860*)pos, buf);
    if (e1) {
        e1->p0 = value->p0;
        FUN_00781a60(&e1->v, 0, &value->v);
        e1->a = value->a;
        e1->b = value->b;
        e1->c = value->c;
    }
    E36_s0078_2860* oldEnd = *(E36_s0078_2860**)(p + 4);
    E36_s0078_2860* e2 = (E36_s0078_2860*)FUN_00781b80((E36_s0078_2860*)pos, oldEnd, (E36_s0078_2860*)((char*)e1 + 0x24));
    FUN_00781cb0((E36_s0078_2860*)pos, oldEnd, (E36_s0078_2860*)((char*)e1 + 0x24));
    if (*(E36_s0078_2860**)p && *(int*)((char*)*(E36_s0078_2860**)p - 4) != 0)
        EastlDeallocate(*(E36_s0078_2860**)p, 0);
    *(E36_s0078_2860**)(p + 4) = e2;
    *(E36_s0078_2860**)p = buf;
    *(E36_s0078_2860**)(p + 8) = (E36_s0078_2860*)((char*)buf + alloc);
}

// @ 0x00782a60
void __fastcall FUN_00782A60(int p, int dummy, const E36_s0078_2860* src)
{
    E36_s0078_2860* end = *(E36_s0078_2860**)(p + 4);
    if (end < *(E36_s0078_2860**)(p + 8)) {
        *(E36_s0078_2860**)(p + 4) = end + 1;
        if (end) {
            end->p0 = src->p0;
            FUN_00781a60(&end->v, 0, &src->v);
            end->a = src->a;
            end->b = src->b;
            end->c = src->c;
        }
    } else {
        FUN_00782860(p, 0, end, src);
    }
}
