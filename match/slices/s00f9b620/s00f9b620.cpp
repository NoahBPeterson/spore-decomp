// Slice s00f9b620 -- SP::cTerrainSphere terrain colour sampling, editor-generate,
// decal/ribbon rendering, layer draw dispatch, effect reset, resource load and
// colour-map update (0x00f9b620 .. 0x00f9c0d0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE float, x87 for uint->float)
#include "types.h"
#include <math.h>
#include <string.h>

// ---- external helpers ------------------------------------------------------------------
void*  __cdecl SP_TerrainEditor();                        // 0x00f48a70
void*  __cdecl SP_App();                                  // 0x0067dd10
void*  __cdecl SP_ModelManager();                         // 0x0067dd80
void*  __cdecl SP_EffectsManager();                       // 0x0067ddd0
void*  __cdecl SP_MaterialManager();                      // 0x0067dd70
void*  __cdecl FUN_0067dd60();                            // 0x0067dd60
void*  __cdecl FUN_0067ddc0();                            // 0x0067ddc0
void   __cdecl FUN_006dde30(int a, int b, void* c);       // 0x006dde30
void   __cdecl FUN_006ddef0(void* a);                     // 0x006ddef0
void   __cdecl FUN_00777ae0(int id, void* a, int b);      // 0x00777ae0
void   __cdecl FUN_007c3c10(void* viewer);                // 0x007c3c10
void   __cdecl FUN_007c3cb0(void* a);                     // 0x007c3cb0
bool   __cdecl FUN_007c4fd0(void* viewer);                // 0x007c4fd0
void   __cdecl FUN_007c4ba0(void* viewer, float f);       // 0x007c4ba0
void   __cdecl FUN_006ffe00(void* a, void* b);            // 0x006ffe00
void   __cdecl FUN_006b4b60(void* a, void* b, int c, int d); // 0x006b4b60
void*  __cdecl SP_GetSaveArea(uint32_t id);                // 0x006b1f90
void   __cdecl FUN_00f97750(void* self);                  // 0x00f97750
void   __cdecl FUN_00f96c60();                            // 0x00f96c60
void   __stdcall FUN_00f986f0(int i);                     // 0x00f986f0
void   __cdecl FUN_00fb8a00();                            // 0x00fb8a00
int    __cdecl FUN_011ef750(int a, int b, void* c);       // 0x011ef750
void   __cdecl FUN_011ef880(void* a);                     // 0x011ef880
void   __cdecl rw_D3D9Sync();                             // 0x011f21a0
void   __cdecl rw_CopyMatrix(void* a, void* b);           // 0x006ffe00
char   __cdecl FUN_006ddcc0(int a, int b, void* c, void* d); // 0x006ddcc0
void*  __cdecl operator_new__(void* a, int b, int size);  // 0x011e073e
void   __cdecl FUN_006ddd80(int a, void* b, uint32_t c, void* d); // 0x006ddd80

// TerrainEditor singleton members (__thiscall)
struct TerrainEditor {
    void  Init(void* a);        // 0x00f67a60
    void  Reset();              // 0x00f67da0
    void  SetValue(float v);    // 0x00f67540
    bool  IsEditing();          // 0x00f678a0
};
bool __cdecl GetPropertyAsVector3(void* list, uint32_t id, float* out);  // 0x006a1110
bool __cdecl ListGetDescription(void* list, uint32_t id);                // 0x006a25a0
struct Prop { uint32_t* GetUInt(); };                                    // 0x0041ea00 (__thiscall)
struct Variant {                                                         // 0x14 bytes
    uint32_t m0, m1, m2, m3;    // +0x00
    uint16_t mFlags;            // +0x10
    uint16_t mType;             // +0x12
    void SetInt(void* v);       // 0x00427fd0 (__thiscall)
    void Destruct(int a);       // 0x0093db80 (__thiscall)
};
uint32_t __cdecl Property_GetUInt(void* prop);                           // 0x0041ea00
bool     __cdecl Property_GetBool(void* prop);                           // 0x0041e920
int      __cdecl Property_GetInt(void* prop);                            // 0x0041e990
void     __cdecl Variant_SetInt(void* v, int a);                         // 0x00427fd0
void     __cdecl Variant_Destruct(void* v, int a);                       // 0x0093db80
struct Matrix44 { float m[16]; void Ctor(void* src); };                 // 0x0045dca0 (__thiscall)
void     __cdecl Viewer_Copy(void* self, void* other, int a, int b);     // 0x007c50b0
void     __cdecl GetImageResource(void* dst, void* src);                 // 0x00576650
struct ImgSlot { void GetImageResource(void* src); };                    // __thiscall form

// __thiscall virtual-call helpers: reproduces the original's
// `mov ecx,obj; push args; call [vtable+off]` sequence.
typedef void  (__thiscall *Tv0)(void*);
typedef void  (__thiscall *Tv1)(void*, int);
typedef int   (__thiscall *Ti0)(void*);
typedef void* (__thiscall *Tp0)(void*);
typedef void* (__thiscall *Tp1)(void*, uint32_t);
#define VTO(p, off) (*(void***)(p))[(off) / 4]

struct cDirectPropertyList {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void Set(uint32_t id, void* v);     // +0x14
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool Get(uint32_t id, void* out);   // +0x24
};
struct IResourceMgr {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void* GetModel(uint32_t id);        // +0x1c (ModelManager)
};
struct IEffectMgr {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void* v10();
    virtual void* Get(uint32_t id);             // +0x54
};
struct IRenderThing {
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
    virtual void v4c();
    virtual int  v50(int a);                    // +0x50
    virtual void v54();
    virtual void* v58(int a);                   // +0x58
};
struct IImgMgr {
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
    virtual void* v3c(void* a, void* b, int c, int d, int e, int f, int g, int h);  // +0x3c
};
struct IDecalMgr {
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
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7c();
    virtual void v80();                         // +0x80
};
struct cTerrainQuad {
    void BufferDrawRibbonGeometry(void* a);     // 0x00fb0100
};
struct cViewer {
    void Copy(void* other, int a, int b);       // 0x007c50b0
    bool Update();                              // 0x007c4fd0
    void Reset();                               // 0x007c3c10
    void SetZoom(float f);                      // 0x007c4ba0
};
struct Sync94 { void Sync(void* a); };          // 0x006ffe00 (this = cTS142+0x92c)

// ---- globals ---------------------------------------------------------------------------
extern void* g_sAppProperties;      // 0x015fd918
extern float g_fHalf;               // 0x01471064 == 0.5f
extern float g_fOne;                // 0x01485720 == 1.0f
extern float g_fColorScale;         // 0x013eecd4 == 1/255
extern float g_f2p32;               // 0x013f4fd0 == 4294967296.0f
extern uint32_t g_imgIdsA[];        // 0x014904ac
extern uint32_t g_imgIdsB[];        // 0x0149047c
extern uint32_t g_imgIdsC[];        // 0x01490494
extern void* g_imgMgr;              // 0x015b11f0
extern float g_dat15b1194;          // 0x015b1194
extern float g_dat15b1198;          // 0x015b1198
extern float g_dat15b119c;          // 0x015b119c
extern void* g_dat016c9e68;         // 0x016c9e68
extern void* g_dat016c9e40;         // 0x016c9e40
extern int   g_dat016c9e44[];       // 0x016c9e44

// ---- receiver --------------------------------------------------------------------------
struct cTS142 {
    uint8_t  pad0[0x28];
    cDirectPropertyList* mpProps;   // +0x28
    uint8_t  pad2c[0x30 - 0x2c];
    float    mScale;                // +0x30
    uint8_t  pad34[0x74 - 0x34];
    uint8_t  mSub74[0x30];          // +0x74
    uint8_t  padA4[0xb8 - 0xa4];
    uint8_t  mSubB8[0x44];          // +0xb8
    void*    mpFC;                  // +0xfc
    uint8_t  pad100[0x108 - 0x100];
    uint8_t  mByte108;              // +0x108
    uint8_t  pad109[0x10c - 0x109];
    float    mF10c;                 // +0x10c
    uint8_t  pad110[0x148 - 0x110];
    void*    mImg148[6];            // +0x148 .. +0x160
    void*    mImg160[6];            // +0x160 .. +0x178
    void*    mImg178[6];            // +0x178 .. +0x190
    void*    mpDecalBegin;          // +0x190
    void*    mpDecalEnd;            // +0x194
    uint8_t  pad198[0x1d0 - 0x198];
    int      mDecalIdMode;          // +0x1d0
    uint8_t  pad1d4[0x20c - 0x1d4];
    uint8_t* mp20c;                 // +0x20c
    uint8_t  pad210[0x30c - 0x210];
    float    mMat30c[10];           // +0x30c .. +0x334
    uint8_t  pad334[0x4f8 - 0x334];
    uint8_t  mShader4f8[0x1d0];     // +0x4f8
    uint8_t  pad6c8[0x814 - 0x6c8];
    int      mF814;                 // +0x814
    int      mF818;                 // +0x818
    uint8_t  pad81c[0x8d8 - 0x81c];
    int      mF8d8;                 // +0x8d8
    uint8_t  pad8dc[0x8e4 - 0x8dc];
    cViewer* mpViewer;              // +0x8e4
    uint8_t  pad8e8[0x92c - 0x8e8];
    uint8_t  mMat92c[0x40];         // +0x92c

    void FUN_00f9b620(uint32_t a, uint32_t b, uint32_t c, float* p5, float* p6, float* p7);
    void FUN_00f9b7f0();
    void FUN_00f9b8c0(int a, int b, int flag, uint8_t f5, float f6);
    void FUN_00f9ba40(void* mtx);
    void FUN_00f9bb50();
    void FUN_00f9bc40(uint32_t a, uint32_t b);
    void FUN_00f9bd00(void* p2, uint32_t a, uint32_t b);
    void FUN_00f9bee0(void* p2);
    void FUN_00f9c010(int idx);
    void FUN_00f9c0d0(void* p2);

    // sibling cTerrainSphere methods (defined in other slices)
    void FUN_00f97f50(uint32_t a, uint32_t b);
    void FUN_00f98530(void* viewer, uint32_t a);
    void FUN_00f98020(uint32_t a, uint32_t b);   // RenderWater
    void FUN_00f98170(uint32_t a, uint32_t b);
    void FUN_00f981d0(uint32_t a, uint32_t b);   // RenderAtmosphere
    void FUN_00f98970();                          // 0x00f98970 (SkyState::Update)
    void FUN_00f998f0();
};

// 0x00f9b620's extra mp20c offsets: +0x1f4, +0x20c, +0x334
struct Sub20c {
    uint8_t pad[0x28];
    void*   mp28;       // +0x28
    uint8_t pad2c[0x30 - 0x2c];
    float   mScale;     // +0x30
    uint8_t pad34[0x1f4 - 0x34];
    void*   mp1f4;      // +0x1f4
    uint8_t pad1f8[0x20c - 0x1f8];
    void*   mp20c;      // +0x20c
    uint8_t pad210[0x334 - 0x210];
    void*   mp334;      // +0x334
};
struct Sub334 {
    uint8_t pad[0x28];
    uint32_t* mp28;     // +0x28
};

// ----------------------------------------------------------------------------------------
// @ 0x00f9b620
void cTS142::FUN_00f9b620(uint32_t a, uint32_t b, uint32_t c, float* p5, float* p6, float* p7)
{
    if (a < 0x40) {
        Sub334* s = (Sub334*)((Sub20c*)mp20c)->mp334;
        uint32_t v = s->mp28[a];
        p5[0] = (float)((v >> 16) & 0xff) * g_fColorScale;
        p5[1] = (float)((v >> 8) & 0xff) * g_fColorScale;
        p5[2] = (float)(v & 0xff) * g_fColorScale;
    }
    float scale = ((Sub20c*)mp20c)->mScale;
    if (b < 0x10) {
        uint8_t* i = (uint8_t*)((Sub20c*)mp20c)->mp20c;
        int n = *(int*)(i + 0x1c) - 1;
        float f = (float)(uint32_t)n;
        f = f * scale;
        int r = (int)floorf(f);
        if (f < (float)r)
            r = r - 1;
        uint32_t v = *(uint32_t*)(*(int*)(i + 0x28) +
                       ((*(uint32_t*)(i + 0x20) >> 1) * *(int*)(i + 0x1c) + r) * 4);
        p6[0] = (float)((v >> 16) & 0xff) * g_fColorScale;
        p6[1] = (float)((v >> 8) & 0xff) * g_fColorScale;
        p6[2] = (float)(v & 0xff) * g_fColorScale;
    }
    if (c < 0x10) {
        uint8_t* i = (uint8_t*)((Sub20c*)mp20c)->mp1f4;
        int n = *(int*)(i + 0x1c) - 1;
        float f = (float)(uint32_t)n;
        f = f * scale;
        int r = (int)floorf(f);
        if (f < (float)r)
            r = r - 1;
        uint32_t v = *(uint32_t*)(*(int*)(i + 0x28) + r * 4);
        p7[0] = (float)((v >> 16) & 0xff) * g_fColorScale;
        p7[1] = (float)((v >> 8) & 0xff) * g_fColorScale;
        p7[2] = (float)(v & 0xff) * g_fColorScale;
    }
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9b7f0
void cTS142::FUN_00f9b7f0()
{
    if (mpProps == 0)
        return;
    uint32_t val = 0;
    void* prop = 0;
    if (mpProps->Get(0x3ad556a, &prop) && *(int16_t*)((uint8_t*)prop + 0x12) == 10)
        val = *((Prop*)prop)->GetUInt();
    if (val == (uint32_t)mF814)
        return;
    ((Tv0)VTO(this, 0x80))(this);
    Variant var;
    var.mType = 10;
    var.mFlags = 2;
    var.SetInt(&mF814);
    mpProps->Set(0x3ad556a, &var);
    if (var.mFlags & 4)
        var.Destruct(0);
    FUN_006b4b60(mpProps, SP_GetSaveArea(0x31389b5), 0, 0);
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9b8c0
void cTS142::FUN_00f9b8c0(int a, int b, int flag, uint8_t f5, float f6)
{
    TerrainEditor* ed = (TerrainEditor*)SP_TerrainEditor();
    ed->Init(this);
    ed->Reset();
    *(uint32_t*)((uint8_t*)ed + 0x160) = 0;
    float v[3] = { g_fHalf, g_fHalf, g_fHalf };
    GetPropertyAsVector3(mpProps, 0x3a23f98, v);
    ed->SetValue(v[0]);
    if (!((TerrainEditor*)SP_TerrainEditor())->IsEditing()) {
        if ((uint8_t)flag != 0) {
            mByte108 = f5;
            mF10c = f6;
            mpFC = mSub74;
            goto call;
        }
        mpFC = mSub74;
    } else {
        mByte108 = 0;
        if (g_sAppProperties) {
            int pr = 0;
            if (((cDirectPropertyList*)g_sAppProperties)->Get(0x31989aaf, &pr) &&
                *(int16_t*)((uint8_t*)pr + 0x12) == 1)
                mByte108 = (uint8_t)Property_GetBool((void*)pr);
        }
        int iv = 10;
        if (g_sAppProperties) {
            int pr = 0;
            if (((cDirectPropertyList*)g_sAppProperties)->Get(0xab52b057, &pr) &&
                *(int16_t*)((uint8_t*)pr + 0x12) == 9)
                iv = Property_GetInt((void*)pr);
        }
        mF10c = (float)iv;
        mpFC = mSubB8;
    }
call:
    ((Tv0)VTO(mpFC, 8))(mpFC);
    if (mpFC != mSub74)
        mF818 = mF814;
    else {
        FUN_00f97750(this);
        mF818 = mF814;
    }
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9ba40
void cTS142::FUN_00f9ba40(void* mtx)
{
    if (mtx == 0) {
        void* app = SP_App();
        void* x = ((Tp0)VTO(app, 0x50))(app);
        mtx = ((Tp0)VTO(x, 0x1c))(x);
    }
    Matrix44 local;
    local.Ctor(mtx);
    float u3 = g_dat15b119c;
    float u4 = g_dat15b1198;
    float u5 = g_dat15b1194;
    Sub20c* s = (Sub20c*)mp20c;
    if (s != 0) {
        u5 = *(float*)((uint8_t*)s + 0x46c);
        u4 = *(float*)((uint8_t*)s + 0x470);
        u3 = *(float*)((uint8_t*)s + 0x474);
    }
    mMat30c[0] = local.m[12];   // wAxis.x
    mMat30c[1] = local.m[13];
    mMat30c[2] = local.m[14];
    *(uint32_t*)&mMat30c[3] = 0x3f800000;
    mMat30c[4] = local.m[4];    // yAxis.x
    mMat30c[5] = local.m[5];
    mMat30c[6] = local.m[6];
    mMat30c[7] = local.m[7];
    *(float*)((uint8_t*)this + 0x32c) = u5;
    *(float*)((uint8_t*)this + 0x330) = u4;
    *(float*)((uint8_t*)this + 0x334) = u3;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9bb50
void cTS142::FUN_00f9bb50()
{
    float* p = (float*)((uint8_t*)this + 0x498);
    for (int i = 0; i < 6; i++) {
        float a0 = p[-0x19];    // left
        float a2 = p[-0x18];    // top
        float a1 = p[-0x17];    // right
        float a3 = p[-0x16];    // bottom
        if (a0 != a1 && a2 != a3 && 0.0f < a1 && (a0 < 1.0f && 0.0f < a3) && a2 < 1.0f) {
            float x0 = p[-1];
            float y0 = p[0];
            float x1 = p[1];
            float y1 = p[2];
            if (x0 == x1 || y0 == y1) {
                p[-1] = a0; p[0] = a2; p[1] = a1; p[2] = a3;
            } else {
                float r = a0;
                if (a0 > x0) r = x0;
                p[-1] = r;
                r = y0;
                if (a2 <= r) r = a2;
                p[0] = r;
                r = x1;
                if (r <= a1) r = a1;
                p[1] = r;
                r = y1;
                if (r <= a3) r = a3;
                p[2] = r;
            }
        }
        FUN_00f986f0(i);
        p += 4;
    }
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9bc40
void cTS142::FUN_00f9bc40(uint32_t a, uint32_t b)
{
    FUN_00f98970();
    FUN_00777ae0(0x305, (uint8_t*)this + 0x4f8, 0);
    uint32_t id = 0xbacbe342;
    if (mDecalIdMode == 0)
        id = 0x2a6214d0;
    else if (mDecalIdMode == 1)
        id = 0x4a621add;
    IImgMgr* mm = (IImgMgr*)SP_MaterialManager();
    void* mat = ((Tp1)VTO(mm, 0x28))(mm, id);
    FUN_006dde30(2, 4, mat);
    int n = (int)((uint8_t*)mpDecalEnd - (uint8_t*)mpDecalBegin) >> 4;
    if (n > 0) {
        int off = 0;
        do {
            if ((((uint8_t*)mpDecalBegin)[off + 0xc] & 0x40) == 0)
                (*(cTerrainQuad**)((uint8_t*)mpDecalBegin + off))->BufferDrawRibbonGeometry((void*)a);
            off += 0x10;
            n--;
        } while (n != 0);
    }
    FUN_006ddef0((void*)a);
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9bd00
void cTS142::FUN_00f9bd00(void* p2, uint32_t a, uint32_t b)
{
    cDirectPropertyList* props = (cDirectPropertyList*)g_sAppProperties;
    mpViewer->Copy(*(void**)p2, 0, 0);
    uint32_t u3 = b & 0x4000000;
    if (u3 != 0 || (b & 0x2000000) != 0)
        ((Sync94*)((uint8_t*)this + 0x92c))->Sync((uint8_t*)mpViewer + 0xc0);
    if (!mpViewer->Update())
        return;
    void* mgr = SP_ModelManager();
    void* obj = ((Tp1)VTO(mgr, 0x1c))(mgr, 0x3fbae24);
    if (obj != 0) {
        void* g = FUN_0067ddc0();
        uint32_t u = (uint32_t)(uintptr_t)((Tp1)VTO(obj, 0x144))(obj, 0);
        ((Tv1)VTO(g, 0x50))(g, (int)u);
        props = (cDirectPropertyList*)g_sAppProperties;
    }
    rw_D3D9Sync();
    FUN_00f98970();
    FUN_00777ae0(0x305, (uint8_t*)this + 0x4f8, 0);
    if (ListGetDescription(props, 0xc0b97e13))
        FUN_00f97f50(a, b);
    if (ListGetDescription(props, 0xddca437d))
        FUN_00f98530(mpViewer, a);
    if (ListGetDescription(props, 0xab73e4f9))
        FUN_00f98020(a, b);
    if (ListGetDescription(props, 0x5016cc22) && (b & 0x1000000) == 0 && a == 0)
        FUN_00f98170(a, b);
    if (ListGetDescription(props, 0x5dee2437) && (b & 0x1000000) == 0 && a == 0)
        FUN_00f9bc40(a, b);
    if (ListGetDescription(props, 0x4f4edc94) && (b & 0x3000000) == 0) {
        if (a != 0) {
            mpViewer->Reset();
            mpViewer->SetZoom(1.0f);
            if (!mpViewer->Update())
                return;
        }
        FUN_00f981d0(a, b);
    }
    mpViewer->Reset();
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9bee0
void cTS142::FUN_00f9bee0(void* p2)
{
    void* self;
    if (this != 0)
        self = (uint8_t*)this + 4;
    else
        self = 0;
    if (((Tp1)VTO(p2, 0x58))(p2, 8) != self)
        return;
    if (g_dat016c9e68 != 0)
        FUN_00f96c60();
    if (mF8d8 != 0)
        FUN_00f998f0();
    IEffectMgr* em = (IEffectMgr*)SP_EffectsManager();
    void* e = ((Tp1)VTO(em, 0x54))(em, 0x3fbae24);
    ((Tv1)VTO(e, 0xc))(e, 3);
    ((Tv1)VTO(p2, 0x50))(p2, 10);
    IResourceMgr* mm = (IResourceMgr*)SP_ModelManager();
    void* m = ((Tp1)VTO(mm, 0x1c))(mm, 0x3fbae24);
    ((Tv1)VTO(m, 0x134))(m, 0);
    ((Tv1)VTO(p2, 0x50))(p2, 8);
    ((Tv1)VTO(p2, 0x50))(p2, 7);
    ((Tv1)VTO(p2, 0x50))(p2, 0x21);
    FUN_00777ae0(0x301, 0, 0);
    FUN_00777ae0(0x304, 0, 0);
    FUN_00777ae0(0x305, 0, 0);
    FUN_00777ae0(0x306, 0, 0);
    FUN_00777ae0(0x24b, 0, 0);
    FUN_00777ae0(0x23d, 0, 0);
    FUN_00777ae0(0x24c, 0, 0);
    FUN_00777ae0(0x24d, 0, 0);
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9c010
void cTS142::FUN_00f9c010(int idx)
{
    IImgMgr* m = (IImgMgr*)FUN_0067dd60();
    void* a = m->v3c((void*)g_imgIdsA[idx], g_imgMgr, 0x200, 0x200, 1, 8, 0x15, 0);
    ((ImgSlot*)((uint8_t*)this + 0x148 + idx * 4))->GetImageResource(a);
    void* b = m->v3c((void*)g_imgIdsB[idx], g_imgMgr, 0x200, 0x200, 1, 8, 0x51, 0);
    ((ImgSlot*)((uint8_t*)this + 0x160 + idx * 4))->GetImageResource(b);
    void* c = m->v3c((void*)g_imgIdsC[idx], g_imgMgr, 0x100, 0x100, 1, 8, 0x32, 0);
    ((ImgSlot*)((uint8_t*)this + 0x178 + idx * 4))->GetImageResource(c);
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9c0d0
void cTS142::FUN_00f9c0d0(void* p2)
{
    IImgMgr* mm = (IImgMgr*)SP_MaterialManager();
    void* mat = ((Tp1)VTO(mm, 0x28))(mm, 0x78a45ffb);
    FUN_007c3cb0(g_dat016c9e40);
    if (mpViewer->Update()) {
        float v0[4];
        float v1[4];
        if (FUN_006ddcc0(3, 4, v0, v1)) {
            uint8_t* q = (uint8_t*)operator_new__(0, 0, 0x70);
            uint32_t* w = (uint32_t*)q;
            w[4] = 0; w[5] = 0; w[6] = 0;
            w[0xb] = 0x3f800000; w[0xc] = 0; w[0xd] = 0;
            w[0x12] = 0x3f800000; w[0x13] = 0x3f800000; w[0x14] = 0;
            w[0x19] = 0; w[0x1a] = 0x3f800000; w[0x1b] = 0;
            w[0] = 0xbf800000; w[1] = 0x3f800000; w[2] = 0;
            w[7] = 0x3f800000; w[8] = 0x3f800000; w[9] = 0;
            w[0xe] = 0x3f800000; w[0xf] = 0xbf800000; w[0x10] = 0;
            w[0x15] = 0xbf800000; w[0x16] = 0xbf800000; w[0x17] = 0;
            FUN_006ddd80(3, mat, g_dat016c9e44[0], p2);
        }
        FUN_007c3c10(mpViewer);
    }
    TerrainEditor* ed = (TerrainEditor*)SP_TerrainEditor();
    if (!ed->IsEditing())
        return;
}
