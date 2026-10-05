// Slice s0077ff30: SP::cShadowWorld / SP::cRenderConvolutionShadow shadow-map
// management (retail layout, /O2 /MD /Gy /EHsc /TP).  Offsets differ from the
// 2008 dev-PDB layout, so every member is placed at the retail offset observed
// in the disassembly; unknown gaps are char pads.
#include "types.h"
#include <intrin.h>
#pragma intrinsic(_InterlockedExchangeAdd)

// ---------------------------------------------------------------------------
// shared stub types
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

// ===========================================================================
// small holder members (functions 0x00780210 / 0x00780250)
// ===========================================================================
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

struct Elem12 {
    IRefCounted* mObj;              // +0
    int mField4;                    // +4
    int mField8;                    // +8
};

// @ 0x00780a50
Elem12* MoveBackward12(Elem12* first, Elem12* last, Elem12* dLast)
{
    while (last != first) {
        --last;
        --dLast;
        IRefCounted* src = last->mObj;
        IRefCounted* dst = dLast->mObj;
        if (src != dst) {
            if (src)
                src->AddRef();
            dLast->mObj = src;
            if (dst)
                dst->Release();
        }
        dLast->mField4 = last->mField4;
        dLast->mField8 = last->mField8;
    }
    return dLast;
}

// ---------------------------------------------------------------------------
// externals (relocations are masked, so only the calling shapes matter)
extern cPropertyList* g_AppProperties;
extern int g_Unk153a2e8;

void* Graphics_67dd60();
void* Graphics_67dda0();
void* Graphics_67dd50();
void* EffectsManager();
void  FUN_0077fbb0();
void  FUN_0077fde0();
void  FUN_00777ae0(int a, int b, int c);
void  FUN_00761110(void* p);

// render-state globals
extern int   g_16fa3a8;
extern int   g_16f954c, g_16f9550, g_16f9558, g_16f955c;
extern int   g_16f966c, g_16f9670, g_16f9678, g_16f967c, g_16f9680;
extern int   g_16fa168, g_16fa16c, g_16fa164;
extern int   g_16fa1a0, g_16fa19c, g_16fa1a4;
extern int   g_16fa248, g_16fa244, g_16fa24c;
extern int   g_16fa210, g_16fa20c, g_16fa214;
extern float g_140e8f8;

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

// ===========================================================================
// 0x00780ab0 : cShadowWorld::Update
// ===========================================================================
void cShadowWorld::Update()
{
    void* g = Graphics_67dd60();
    bool b = ((bool(__thiscall*)(void*, uint32_t, int))((void**)(*(void**)g))[10])(g, 0x7543c109, g_Unk153a2e8);
    if (!b) {
        FUN_0077fbb0();
        FUN_0077fde0();
    }
    cPropertyList* pl = g_AppProperties;
    if (pl->GetDescription(0x276abef)
        && pl->GetDescription(0x276abf0)
        && mRenderShadow == 0) {
        pl = g_AppProperties;
        mUnkD = 1;
        mLightingWorld = 0;
        mUnk1c4 = pl->GetDescription(0x33cb1dac);
        mUnk14 = pl->GetDescription(0x276abf8);
        mUnk15 = pl->GetDescription(0x65a8c87);
        int n = 1;
        if (mUnk14)
            n = 2;
        if (mUnk1c4)
            Init(n);
    }
}

// ===========================================================================
// 0x007806a0 : cShadowWorld::Cleanup
// ===========================================================================
void cShadowWorld::Cleanup()
{
    if (mUnkD) {
        FUN_00777ae0(0x223, 0, 0);
        if (mRenderShadow) {
            void* g = Graphics_67dd50();
            ((void(__thiscall*)(void*, int))((void**)(*(void**)g))[20])(g, mUnk220);
        }
    }
    if (mRenderShadow) {
        void* p = mRenderShadow;
        mRenderShadow = 0;
        ((void(__thiscall*)(void*))((void**)(*(void**)p))[1])(p);
    }
    void* g2 = Graphics_67dda0();
    if (mShadowDB) {
        FUN_00761110(mShadowDB);
        mShadowDB = 0;
    }
    Raster** sm = mShadowMaps;
    RectID*  sr = mShadowMapRectIDs;
    Raster** bm = mShadowBasisMaps[0];
    RectID*  br = mShadowBasisMapRectIDs[0];
    for (int i = 0; i < 2; ++i) {
        if (*sm) {
            if (*sm) {
                Raster* p = *sm;
                *sm = 0;
                volatile long* rc = (volatile long*)((char*)p + 8);
                _InterlockedExchangeAdd(rc, -1);
                if (_InterlockedExchangeAdd(rc, 0) < 1)
                    _InterlockedExchangeAdd(rc, 1);
                else
                    _InterlockedExchangeAdd(rc, 0);
            }
            ((void(__thiscall*)(void*, int, int))((void**)(*(void**)g2))[5])(g2, sr->a, sr->b);
        }
        for (int j = 4; j != 0; --j) {
            if (*bm) {
                if (*bm) {
                    Raster* p = *bm;
                    *bm = 0;
                    volatile long* rc = (volatile long*)((char*)p + 8);
                    _InterlockedExchangeAdd(rc, -1);
                    if (_InterlockedExchangeAdd(rc, 0) < 1)
                        _InterlockedExchangeAdd(rc, 1);
                    else
                        _InterlockedExchangeAdd(rc, 0);
                }
                ((void(__thiscall*)(void*, int, int))((void**)(*(void**)g2))[5])(g2, br->a, br->b);
            }
            ++bm;
            ++br;
        }
        ++sm;
        ++sr;
    }
}

// ===========================================================================
// 0x00780810 : render-state apply (uses basis-map rasters as three textures)
// ===========================================================================
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

// ===========================================================================
// 0x0077ff30 : cRenderConvolutionShadow::DrawLayer
// ===========================================================================
void cRenderConvolutionShadow::BuildBasisMap(int, int, void*) {}
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

// ===========================================================================
// 0x00780270 : cShadowWorld::Init
// ===========================================================================
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
