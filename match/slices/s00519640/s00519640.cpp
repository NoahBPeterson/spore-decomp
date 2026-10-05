// nSPSkinner::cPaintSplatJob::Render  (unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE, no /EHsc)
// Multi-stage splat paint job. Each Render() call advances a stage (mStage) and processes up to ten
// blocks (mBlock); stage 3/4 composite the drawn splats into the output textures.
#include "types.h"

// ---------------------------------------------------------------- callees
int   GetPaintSystem();                                   // 0x00401080
void  RTTBuffer_Begin(void* self);                        // 0x00528e90
void  RTTBuffer_SetParams(void* self, int a, int b, int c, int d);  // 0x00529280
void  RTTBuffer_Draw(void* self, void* a, void* b, uint32_t color); // 0x005296b0
void  RTTBuffer_BeginDraw(void* self);                    // 0x00529bf0
void  Vector3_CopyCtor(void* dst, const void* src);       // 0x004098a0
void* FUN_00446ff0();                                     // 0x00446ff0
void* FUN_006bb640();                                     // 0x006bb640
void* FUN_0067dd60();                                     // 0x0067dd60

extern void* _sAppProperties;                             // 0x015df0f0 vicinity
extern float g_skinSplatA;                                // placeholder for _sAppProperties GetFloatProperty

// App-property singleton with a GetFloatProperty(unsigned) virtual.
struct DirectPropertyList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual float GetFloatProperty(unsigned key);          // +0x28
};

// Generic IMessage/ISerializer-like object with the slots used below.
struct SplatObj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool Has(int key);                             // +0x1c
    virtual void v8(); virtual void v9();
    virtual void* GetByKey(int key);                       // +0x28
};
struct TexFactory {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void* Create(const void* p, int a, int b, int type);  // +0x1c
    virtual void v8();
    virtual bool Valid(const void* p, int a, int b);        // +0x24
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void Release(void* p);                          // +0x34
};

namespace nSPSkinner {
struct cRTTBuffer {                 // size 0x64
    uint32_t mCamera;               // +0x00
    uint32_t material;              // +0x04
    uint32_t writemask;             // +0x08
    float    params[12];            // +0x0c  (cSPVector4 params[3])
    void*    textures[2];           // +0x3c
    int      maxparam;              // +0x44
    int      maxtexture;            // +0x48
    uint32_t vtxcount;              // +0x4c
    uint32_t pad50;                 // +0x50
    uint32_t mWidth;                // +0x58
    uint32_t mHeight;               // +0x5c
    void*    mTexture;              // +0x60
};
struct cPaintSplatJob {             // size 0x18
    uint32_t pad00[3];
    bool     mComplete;             // +0x0c
    uint8_t  pad0d[3];
    int      mStage;                // +0x10
    int      mBlock;                // +0x14
    virtual bool Render();
};
}  // namespace nSPSkinner

// @ 0x00519640 ?Render@cPaintSplatJob@nSPSkinner@@UAE_NXZ
bool nSPSkinner::cPaintSplatJob::Render()
{
    int ps1 = GetPaintSystem();
    int mat = *(int*)(ps1 + 0xc);
    cRTTBuffer* buf0 = *(cRTTBuffer**)(mat + 0x10);
    cRTTBuffer* buf1 = *(cRTTBuffer**)(mat + 0x14);
    int ps2 = GetPaintSystem();
    int skin = *(int*)(ps2 + 0x20);
    int blocks = *(int*)(*(int*)(skin + 8) + 0x98);
    int nBlocks = (*(int*)(*(int*)(skin + 8) + 0x9c) - *(int*)(*(int*)(skin + 8) + 0x98)) / 0x8c;

    if (mStage == 1)
        mStage = 2;
    if (mStage < 4) {
        if (mStage < 2)
            RTTBuffer_Begin(buf0);
        else
            RTTBuffer_Begin(buf1);

        float c4c, c48, c44, c40, c3c, c38, c34, c30, c2c, c28, c24, c20;
        c40 = 0.0f; c30 = 0.0f; c20 = 0.0f;
        Vector3_CopyCtor(&c4c, (char*)0x15df0f0 + 0);
        Vector3_CopyCtor(&c3c, (char*)0x15df0f0 + 0xc);
        Vector3_CopyCtor(&c2c, (char*)0x15df0f0 + 0x18);

        float fGloss = ((DirectPropertyList*)_sAppProperties)->GetFloatProperty(0x1c76d9b5);
        if (fGloss == 0.0f)
            fGloss = 1.0f;

        int drawn = 0;
        while (mBlock < nBlocks && drawn < 10) {
            if ((*(uint16_t*)(blocks + 8 + mBlock * 0x8c) & 1) == 0) {
                drawn++;
                uint32_t* rect = (uint32_t*)(mBlock * 0x10 + *(int*)(skin + 0x90));
                float uv0[2]; uv0[0] = (float)rect[0]; uv0[1] = (float)rect[1];
                float uv1[2]; uv1[0] = (float)rect[2]; uv1[1] = (float)rect[3];

                SplatObj* prop = *(SplatObj**)(*(int*)(skin + 0xc) + mBlock * 4);
                int* texA = 0;
                int* texB = 0;
                int* texC = 0;
                bool haveA = false, haveB = false, haveC = false;

                {
                    if (mStage == 0 && (haveA = prop->Has(0x2424655))) {
                        void* o = prop->GetByKey(0x2424655);
                        void* v;
                        if (*(int16_t*)((char*)o + 0x12) == 0x20 || *(int16_t*)((char*)o + 0x12) == 0x10)
                            v = FUN_00446ff0();
                        else
                            v = FUN_006bb640();
                        TexFactory* f = (TexFactory*)FUN_0067dd60();
                        if (f->Valid(v, ((int*)v)[1], ((int*)v)[2])) {
                            f = (TexFactory*)FUN_0067dd60();
                            texA = (int*)f->Create(v, ((int*)v)[1], ((int*)v)[2], 6);
                        }
                    }
                    if ((mStage == 0 || mStage == 1) && (haveB = prop->Has(0x2424657))) {
                        void* o = prop->GetByKey(0x2424657);
                        void* v;
                        if (*(int16_t*)((char*)o + 0x12) == 0x20 || *(int16_t*)((char*)o + 0x12) == 0x10)
                            v = FUN_00446ff0();
                        else
                            v = FUN_006bb640();
                        TexFactory* f = (TexFactory*)FUN_0067dd60();
                        if (f->Valid(v, ((int*)v)[1], ((int*)v)[2])) {
                            f = (TexFactory*)FUN_0067dd60();
                            texB = (int*)f->Create(v, ((int*)v)[1], ((int*)v)[2], 6);
                        }
                    }
                    if ((mStage == 2 || mStage == 3) && (haveC = prop->Has(0x2424656))) {
                        void* o = prop->GetByKey(0x2424656);
                        void* v;
                        if (*(int16_t*)((char*)o + 0x12) == 0x20 || *(int16_t*)((char*)o + 0x12) == 0x10)
                            v = FUN_00446ff0();
                        else
                            v = FUN_006bb640();
                        TexFactory* f = (TexFactory*)FUN_0067dd60();
                        if (f->Valid(v, ((int*)v)[1], ((int*)v)[2])) {
                            f = (TexFactory*)FUN_0067dd60();
                            texC = (int*)f->Create(v, ((int*)v)[1], ((int*)v)[2], 6);
                        }
                    }
                }
                (void)haveA; (void)haveB; (void)haveC;

                if (mStage == 0 && texA != 0 && texB != 0) {
                    RTTBuffer_SetParams(buf0, 1, 1, 1, 0);
                    buf0->material = 0xd9ec39bc;
                    if (buf0->maxparam < 1) buf0->maxparam = 1;
                    buf0->params[0] = c4c; buf0->params[1] = c48; buf0->params[2] = c44; buf0->params[3] = c40;
                    if (buf0->maxparam < 2) buf0->maxparam = 2;
                    buf0->params[4] = c3c; buf0->params[5] = c38; buf0->params[6] = c34; buf0->params[7] = c30;
                    if (buf0->maxparam < 3) buf0->maxparam = 3;
                    buf0->params[8] = c2c; buf0->params[9] = c28; buf0->params[10] = c24; buf0->params[11] = c20;
                    if ((texA[1] & 1) == 0)
                        ((TexFactory*)FUN_0067dd60())->Release(texA);
                    void* raster = (void*)*texA;
                    if (raster != 0 && buf0->maxtexture < 1) buf0->maxtexture = 1;
                    buf0->textures[0] = raster;
                    if ((texB[1] & 1) == 0)
                        ((TexFactory*)FUN_0067dd60())->Release(texB);
                    raster = (void*)*texB;
                    if (raster != 0 && buf0->maxtexture < 2) buf0->maxtexture = 2;
                    buf0->textures[1] = raster;
                    RTTBuffer_Draw(buf0, uv0, uv1, 0xffffffff);
                }
                if (mStage == 1 && texB != 0) {
                    RTTBuffer_SetParams(buf0, 0, 0, 0, 1);
                    buf0->material = 0xa91b6551;
                    if (buf0->maxparam < 1) buf0->maxparam = 1;
                    buf0->params[0] = 1.0f; buf0->params[1] = 1.0f; buf0->params[2] = 1.0f; buf0->params[3] = 1.0f;
                    if ((texB[1] & 1) == 0)
                        ((TexFactory*)FUN_0067dd60())->Release(texB);
                    void* raster = (void*)*texB;
                    if (raster != 0 && buf0->maxtexture < 1) buf0->maxtexture = 1;
                    buf0->textures[0] = raster;
                    buf0->textures[1] = 0;
                    RTTBuffer_Draw(buf0, uv0, uv1, 0xffffffff);
                }
                if (mStage == 2 && texC != 0) {
                    float f = *(float*)(mat + 0x30);
                    RTTBuffer_SetParams(buf1, 1, 0, 0, 0);
                    buf1->material = 0x3815422;
                    if (buf1->maxparam < 1) buf1->maxparam = 1;
                    buf1->params[0] = f; buf1->params[1] = f; buf1->params[2] = f; buf1->params[3] = 1.0f;
                    if ((texC[1] & 1) == 0)
                        ((TexFactory*)FUN_0067dd60())->Release(texC);
                    void* raster = (void*)*texC;
                    if (raster != 0 && buf1->maxtexture < 1) buf1->maxtexture = 1;
                    buf1->textures[0] = raster;
                    RTTBuffer_Draw(buf1, uv0, uv1, 0xffffffff);
                }
                if (mStage == 3 && texC != 0) {
                    float f = *(float*)(mat + 0x2c) * fGloss;
                    RTTBuffer_SetParams(buf1, 0, 0, 1, 0);
                    buf1->material = 0x968e3fff;
                    if (buf1->maxparam < 1) buf1->maxparam = 1;
                    buf1->params[0] = f; buf1->params[1] = f; buf1->params[2] = f; buf1->params[3] = 1.0f;
                    if ((texC[1] & 1) == 0)
                        ((TexFactory*)FUN_0067dd60())->Release(texC);
                    void* raster = (void*)*texC;
                    if (raster != 0 && buf1->maxtexture < 1) buf1->maxtexture = 1;
                    buf1->textures[0] = raster;
                    RTTBuffer_Draw(buf1, uv0, uv1, 0xffffffff);
                }
            }
            mBlock = mBlock + 1;
        }
        if (mStage < 2)
            RTTBuffer_BeginDraw(buf0);
        else
            RTTBuffer_BeginDraw(buf1);
        if (nBlocks <= mBlock) {
            mBlock = 0;
            mStage = mStage + 1;
        }
    }
    return mStage == 4;
}
