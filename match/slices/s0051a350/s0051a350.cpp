// Slice 2: nSPSkinner splat-alpha job / paint-renderer helpers and the accompanying ctor/dtor pair.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

// ---------------------------------------------------------------- callees
int   GetPaintSystem();                                              // 0x00401080
void  RTTBuffer_Begin(void* self);                                   // 0x00528e90
void  RTTBuffer_SetParams(void* self, int a, int b, int c, int d);   // 0x00529280
void  RTTBuffer_Draw(void* self, void* a, void* b, uint32_t color);  // 0x005296b0
void  RTTBuffer_BeginDraw(void* self);                               // 0x00529bf0
int   FUN_0041d870(void* p);                                         // 0x0041d870
void  FUN_00423be0(int n, void* p);                                  // 0x00423be0
void  FUN_004c6ae0(void* dst, int a, int n, void* b);                // 0x004c6ae0
void  FUN_0041e5d0();                                                // 0x0041e5d0
void  FUN_00552750();                                                // 0x00552750
void  FUN_0051d1e0(void* p);                                         // 0x0051d1e0
void  FUN_0051d140();                                                // 0x0051d140
void  FUN_00402420();                                                // 0x00402420
struct SubObj { void FUN_0051d0d0(); };
void  FUN_0051d180(void* p);                                         // 0x0051d180
void  FUN_004259e0(void* a, void* b);                                // 0x004259e0
void  SP_cJob_GetStatus(void* job);                                  // 0x00690120
void  Raster_D3D9GetStreamedMipLevelSize(void* raster, int a, int b);
char  SP_GetPropertyAsKey(void* prop, int key, void* out);
void* FUN_0067dd40();                                                // 0x0067dd40
void* FUN_0067dd60();                                                // 0x0067dd60

extern void* g_splatVtblDerived;
extern void* g_splatVtblBase;

// Generic refcounted factory with the slots used above.
struct Factory {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void* Create(void* p, int a, int b, int type);         // +0x1c
    virtual void* v8(int key, int a, int b);                       // +0x20
    virtual bool  Valid(void* p, int a, int b);                    // +0x24
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void  Release(void* p);                                // +0x34
    virtual void v14(); virtual void v15();
    virtual void* CreateBuf(int a, int b, int c, int d, int e, int f); // +0x40
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21();
    virtual int   Make(void* a, int b, int c);                     // +0x58
};

namespace nSPSkinner {
struct cRTTBuffer {                 // size 0x64
    uint32_t mCamera; uint32_t material; uint32_t writemask;
    float    params[12];
    void*    textures[2];
    int      maxparam;
    int      maxtexture;
    uint32_t vtxcount; uint32_t pad50;
    uint32_t mWidth; uint32_t mHeight; void* mTexture;
};
struct cPaintSplatAlphaJob {        // size 0x18
    uint32_t pad00[3];
    bool     mComplete;
    uint8_t  pad0d[3];
    int      mStage;                // +0x10
    int      mBlock;                // +0x14
    virtual bool Render();
};
}  // namespace nSPSkinner

// The ctor/dtor/init cluster belongs to one 0x350-byte skin job class.
struct SkinJob {
    void* FUN_0051a8a0();
    void  FUN_0051a930();
    void  FUN_0051a9a0(int a2, char a3, char a4, int a5, int a6, int a7, int a8,
                       char a9, char a10, char a11);
    void  FUN_0051aaa0();
    void  FUN_0051ab50(char deep);
};

// @ 0x0051a350 ?Render@cPaintSplatAlphaJob@nSPSkinner@@UAE_NXZ
bool nSPSkinner::cPaintSplatAlphaJob::Render()
{
    nSPSkinner::cRTTBuffer* buf;
    {
        int ps = GetPaintSystem();
        int mat = *(int*)(ps + 0xc);
        buf = *(nSPSkinner::cRTTBuffer**)(mat + 0x10);
    }
    int ps2 = GetPaintSystem();
    int skin = *(int*)(ps2 + 0x20);
    int blocks = *(int*)(*(int*)(skin + 8) + 0x98);
    int nBlocks = (*(int*)(*(int*)(skin + 8) + 0x9c) - *(int*)(*(int*)(skin + 8) + 0x98)) / 0x8c;
    RTTBuffer_Begin(buf);
    int drawn = 0;
    while (mBlock < nBlocks && drawn < 10) {
        if ((*(uint16_t*)(blocks + 8 + mBlock * 0x8c) & 1) == 0) {
            int prop[3]; prop[0] = 0; prop[1] = 0; prop[2] = 0;
            if (SP_GetPropertyAsKey(*(void**)(*(int*)(skin + 0xc) + mBlock * 4), 0x2424657, prop)) {
                int* tex = (int*)((Factory*)FUN_0067dd60())->Create(prop, prop[1], prop[2], 6);
                if (tex != 0) {
                    uint32_t* rect = (uint32_t*)(mBlock * 0x10 + *(int*)(skin + 0x90));
                    float uv0[2]; uv0[0] = (float)rect[0]; uv0[1] = (float)rect[1];
                    float uv1[2]; uv1[0] = (float)rect[2]; uv1[1] = (float)rect[3];
                    RTTBuffer_SetParams(buf, 0, 0, 0, 1);
                    buf->material = 0xa91b6551;
                    if (buf->maxparam < 1) buf->maxparam = 1;
                    buf->params[0] = 1.0f; buf->params[1] = 1.0f; buf->params[2] = 1.0f; buf->params[3] = 1.0f;
                    if ((tex[1] & 1) == 0)
                        ((Factory*)FUN_0067dd60())->Release(tex);
                    void* raster = (void*)*tex;
                    if (raster != 0 && buf->maxtexture < 1) buf->maxtexture = 1;
                    buf->textures[0] = raster;
                    buf->textures[1] = 0;
                    RTTBuffer_Draw(buf, uv0, uv1, 0xffffffff);
                    drawn++;
                }
            }
        }
        mBlock = mBlock + 1;
    }
    RTTBuffer_BeginDraw(buf);
    return nBlocks <= mBlock;
}

// @ 0x0051a6a0 FUN_0051a6a0
void FUN_0051a6a0(int* out)
{
    int* local_8 = 0;
    int* piVar1 = (int*)FUN_0067dd40();
    int* piVar2 = (int*)FUN_0067dd60();
    int st = FUN_0041d870(&local_8);
    int u = ((Factory*)piVar1)->Make((void*)st, 0, 0);
    ((Factory*)piVar2)->Make((void*)u, 0, 0);
    int* p8 = local_8;
    int n = p8[7] * p8[8];
    char local_29 = 0;
    int local_20 = 0;
    FUN_00423be0(n, &local_29);
    char local_35 = 0;
    FUN_004c6ae0(&local_20, local_20, n, &local_35);
    for (int i = 0; i < p8[7] * p8[8]; i++)
        *(char*)(local_20 + i) = *(char*)(p8[10] + 1 + i * 4);
    int* puVar4 = (int*)((Factory*)FUN_0067dd60())->CreateBuf(p8[7], p8[8], 1, 8, 0x32, 4);
    if (puVar4 != 0)
        puVar4[2] = puVar4[2] + 1;
    if ((puVar4[1] & 1) == 0)
        ((Factory*)FUN_0067dd60())->Release(puVar4);
    Raster_D3D9GetStreamedMipLevelSize((void*)*puVar4, local_20, 0);
    *out = (int)puVar4;
    FUN_0041e5d0();
    if (p8 != 0)
        (*(Factory**)p8)->v1();
}

// @ 0x0051a8a0 FUN_0051a8a0
void* SkinJob::FUN_0051a8a0()
{
    *(void**)this = &g_splatVtblBase;
    *(int*)((char*)this + 4) = 0;
    *(void**)this = &g_splatVtblDerived;
    ((SubObj*)((char*)this + 8))->FUN_0051d0d0();
    *(int*)((char*)this + 0x330) = 0;
    *(int*)((char*)this + 0x334) = 0;
    return this;
}

// @ 0x0051a930 FUN_0051a930
void SkinJob::FUN_0051a930()
{
    void* self = this;
    *(void**)self = &g_splatVtblDerived;
    if (*(void**)((char*)self + 0x334) != 0)
        SP_cJob_GetStatus(*(void**)((char*)self + 0x334));
    if (*(void**)((char*)self + 0x330) != 0)
        (*(Factory**)((char*)self + 0x330))->v1();
    FUN_0051d180((char*)self + 8);
    *(void**)self = &g_splatVtblBase;
}

// @ 0x0051a9a0 FUN_0051a9a0
void SkinJob::FUN_0051a9a0(int a2, char a3, char a4, int a5, int a6, int a7, int a8,
                           char a9, char a10, char a11)
{
    void* self = this;
    *(int*)((char*)self + 0x33c) = 0;
    FUN_004259e0(*(void**)((char*)self + 8), *(void**)((char*)self + 0xc));
    *(int*)((char*)self + 0x340) = 0;
    *(int*)((char*)self + 0x344) = 0;
    *(int*)((char*)self + 0x338) = a2;
    *(char*)((char*)self + 0x348) = a3;
    *(char*)((char*)self + 0x349) = a4;
    int ps = GetPaintSystem();
    *(char*)((char*)self + 0x34a) = *(char*)(ps + 0x7e);
    *(int*)((char*)self + 0x320) = a5;
    *(int*)((char*)self + 0x324) = a6;
    *(int*)((char*)self + 0x328) = a7;
    *(int*)((char*)self + 0x32c) = a8;
    *(char*)((char*)self + 0x34b) = a9;
    *(char*)((char*)self + 0x34c) = a10;
    *(char*)((char*)self + 0x34d) = a11;
    *(char*)((char*)self + 0x34e) = 0;
    ((SkinJob*)self)->FUN_0051ab50(a3);
}

// @ 0x0051aaa0 FUN_0051aaa0
void SkinJob::FUN_0051aaa0()
{
    void* self = this;
    if (*(void**)((char*)self + 0x330) != 0) {
        *(char*)((char*)*(void**)((char*)self + 0x330) + 0xc) = 1;
        void* p = *(void**)((char*)self + 0x330);
        *(void**)((char*)self + 0x330) = 0;
        if (p != 0)
            (*(Factory**)p)->v1();
    }
    FUN_004259e0(*(void**)((char*)self + 8), *(void**)((char*)self + 0xc));
    *(int*)((char*)self + 0x33c) = -1;
}

// @ 0x0051ab50 ?PreloadTextures@cPaintRenderer@nSPSkinner@@QAEX_N@Z
void SkinJob::FUN_0051ab50(char deep)
{
    int ps = GetPaintSystem();
    int mat = *(int*)(ps + 0xc);
    int ps2 = GetPaintSystem();
    int skin = *(int*)(ps2 + 0x20);
    if (mat != 0 && skin != 0) {
        int blocks = *(int*)(*(int*)(skin + 8) + 0x98);
        int base = mat + 0x3c;
        int c = 0;
        int* it = 0;
        int* p = *(int**)(mat + 0x40);
        int v = *p;
        if (v == 0)
            FUN_00552750();
        for (;;) {
            it = p;
            c = v;
            int* end = (int*)(*(int*)(base + 4) + *(int*)(base + 8) * 4);
            if (c == *end)
                break;
            for (int i = 0; i < 3; i++) {
                if (*(int*)(c + 4 + i * 4) != 0)
                    FUN_0051d1e0((void*)(c + 4 + i * 4));
            }
            FUN_0051d140();
            v = c;
            p = it;
        }
        int tex = ((Factory*)FUN_0067dd60())->Make((void*)0xbd77bb98, 0, 0);
        if (tex != 0)
            *(int*)(tex + 8) = *(int*)(tex + 8) + 1;
        FUN_0051d1e0(&tex);
        if (tex != 0)
            FUN_00402420();
        if (deep != 0) {
            int nBlocks = (*(int*)(*(int*)(skin + 8) + 0x9c) - *(int*)(*(int*)(skin + 8) + 0x98)) / 0x8c;
            for (int j = 0; j < nBlocks; j++) {
                if ((*(uint16_t*)(blocks + 8 + j * 0x8c) & 1) == 0) {
                    int propKey = *(int*)(*(int*)(skin + 0xc) + j * 4);
                    int prop[3]; prop[0] = 0; prop[1] = 0; prop[2] = 0;
                    if (SP_GetPropertyAsKey((void*)propKey, 0x2424655, prop)) {
                        int t = (int)((Factory*)FUN_0067dd60())->Create(prop, prop[1], prop[2], 4);
                        if (t != 0) *(int*)(t + 8) = *(int*)(t + 8) + 1;
                        FUN_0051d1e0(&t);
                        if (t != 0) FUN_00402420();
                    }
                    if (SP_GetPropertyAsKey((void*)propKey, 0x2424657, prop)) {
                        int t = (int)((Factory*)FUN_0067dd60())->Create(prop, prop[1], prop[2], 4);
                        if (t != 0) *(int*)(t + 8) = *(int*)(t + 8) + 1;
                        FUN_0051d1e0(&t);
                        if (t != 0) FUN_00402420();
                    }
                    if (SP_GetPropertyAsKey((void*)propKey, 0x2424656, prop)) {
                        int t = (int)((Factory*)FUN_0067dd60())->Create(prop, prop[1], prop[2], 4);
                        if (t != 0) *(int*)(t + 8) = *(int*)(t + 8) + 1;
                        FUN_0051d1e0(&t);
                        if (t != 0) FUN_00402420();
                    }
                }
            }
        }
    }
}
