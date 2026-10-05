// nSPSkinner::cPaintAmbOccJob::Render  (unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE, no /EHsc)
// Ambient-occlusion paint job. For each of the two material RTT components it binds the component,
// uploads the per-block AO value (read from each block's property list) as a vertex colour and draws
// every block quad; the first component keeps the procedural parameters, the second is the identity pass.
#include "types.h"

// ---------------------------------------------------------------- callees (masked relocations)
void* GetPaintSystem();                                        // 0x00401080
int   FUN_0041d870(void* state);                               // 0x0041d870
int   InitVerbCollection(void* p);                             // 0x004bb860
void* SP_PropertyManager();                                    // 0x0067de30
void  GetFloatProperty(void* obj, uint32_t key, float* out);   // 0x0040cf10
void  RTTBuffer_Begin(void* self);                             // 0x00528e90
void  RTTBuffer_SetParams(void* self, int a, int b, int c, int d);   // 0x00529280
void* GetTextureHandle(void* self);                            // 0x00525aa0
void  RTTBuffer_Draw(void* self, uint32_t color, float* a, float* b); // 0x005296b0
void  RTTBuffer_BeginDraw(void* self);                         // 0x00529bf0

extern float g_1485720;    // 0x01485720
extern float g_1485378;    // 0x01485378

// ---------------------------------------------------------------- minimal layouts
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
struct cPaintAmbOccJob {
    virtual bool Render();          // +0x00
};
}  // namespace nSPSkinner

// Pointer vector at +0xe4 (the baked skinner result).
struct ResultObj {
    uint32_t pad00[0x39];
    void**   mE4begin;              // +0xe4
    void**   mE4end;                // +0xe8
};

struct RigBlock {                   // 0x8c bytes
    uint32_t pad00[2];
    uint16_t mFlags;                // +0x08
    uint16_t pad0a;
    uint8_t  pad0c[0x80];
};

struct ModelObj {
    uint8_t  pad00[0x18];
    void*    mEditorModel;          // +0x18
    uint8_t  pad1c[0x7c];           // to 0x98
    RigBlock* mBlocksBegin;         // +0x98
    RigBlock* mBlocksEnd;           // +0x9c
};

struct SkinObj {                    // SP::cSkinObject
    uint32_t pad00[2];
    ModelObj* mpModel;              // +0x08
    void**    mBlockProps;          // +0x0c
};

struct AOVert {
    uint32_t pad00[0x16];
    float x0;                       // +0x58
    float x1;                       // +0x5c
    float y0;                       // +0x60
    float y1;                       // +0x64
};

struct PropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetProperty(int key, float def, void* it);   // +0x2c
};

struct PropIterator {
    virtual void v0();
    virtual void Release();         // +0x04
};

inline int RoundToInt(float f) { return (int)(f + 0.5f); }

// @ 0x00518f10 ?Render@cPaintAmbOccJob@nSPSkinner@@UAE_NXZ
bool nSPSkinner::cPaintAmbOccJob::Render()
{
    void* ps = GetPaintSystem();
    ResultObj* result = *(ResultObj**)((char*)ps + 0x10);
    void* mat = *(void**)((char*)ps + 0xc);
    nSPSkinner::cRTTBuffer* comp0 = *(nSPSkinner::cRTTBuffer**)((char*)mat + 0x10);
    nSPSkinner::cRTTBuffer* comp1 = *(nSPSkinner::cRTTBuffer**)((char*)mat + 0x14);
    SkinObj* skin = *(SkinObj**)((char*)ps + 0x20);
    ModelObj* model = skin->mpModel;
    RigBlock* blocks = model->mBlocksBegin;
    int nBlocks = (int)((char*)model->mBlocksEnd - (char*)model->mBlocksBegin) / 0x8c;

    float fParam0 = g_1485720;
    float fParam1 = g_1485378;
    uint32_t defBits = 0x40200100;
    float fDefault = *(float*)&defBits;

    int r = InitVerbCollection(model->mEditorModel);
    int key = (r == 0x438f6347) ? 0xf01f7f52 : 0xf1cf8a9d;
    void* pIter = 0;
    int it = FUN_0041d870(&pIter);
    PropertyManager* pm = (PropertyManager*)SP_PropertyManager();
    if (pm->GetProperty(key, fDefault, (void*)it)) {
        GetFloatProperty(pIter, 0x26cabbf, &fParam0);
        GetFloatProperty(pIter, 0x26dc91e, &fParam1);
    }
    for (int i = 0; i < 2; i++) {
        nSPSkinner::cRTTBuffer* cur;
        if (i == 0) {
            cur = comp0;
            RTTBuffer_Begin(cur);
            RTTBuffer_SetParams(cur, 1, 1, 1, 0);
        } else {
            cur = comp1;
            RTTBuffer_Begin(cur);
            RTTBuffer_SetParams(cur, 1, 0, 0, 0);
        }
        cur->material = 0xbc487ecb;
        if (cur->maxparam < 1)
            cur->maxparam = 1;
        cur->params[0] = fParam0;
        cur->params[1] = fParam1;
        cur->params[2] = g_1485378;
        cur->params[3] = g_1485378;
        void* tex = GetTextureHandle(ps);
        if (tex != 0 && cur->maxtexture < 1)
            cur->maxtexture = 1;
        cur->textures[0] = tex;

        int ai = 0;
        int count = (int)(((char*)result->mE4end - (char*)result->mE4begin) / 4);
        for (int j = 0; j < nBlocks; j++) {
            RigBlock* block = (RigBlock*)((char*)blocks + j * 0x8c);
            void* bp = skin->mBlockProps[j];
            if ((block->mFlags & 1) == 0) {
                float c = g_1485720;
                GetFloatProperty(bp, 0xd669e3c7, &c);
                if (c < 0.0f)
                    c = 0.0f;
                c = c * 255.0f;
                if (c > 255.0f)
                    c = 255.0f;
                uint32_t ci = (uint32_t)RoundToInt(c);
                uint32_t color = (ci << 24) | (ci << 16) | (ci << 8) | ci;
                AOVert* p = (AOVert*)result->mE4begin[ai];
                ai++;
                float va[2]; va[0] = p->x0; va[1] = p->y0;
                float vb[2]; vb[0] = p->x1; vb[1] = p->y1;
                RTTBuffer_Draw(cur, color, va, vb);
            }
        }
        while (ai < count) {
            AOVert* p = (AOVert*)result->mE4begin[ai];
            ai++;
            float va[2]; va[0] = p->x0; va[1] = p->y0;
            float vb[2]; vb[0] = p->x1; vb[1] = p->y1;
            RTTBuffer_Draw(cur, 0xffffffffu, va, vb);
        }
        RTTBuffer_SetParams(cur, 1, 1, 1, 1);
        RTTBuffer_BeginDraw(cur);
    }
    if (pIter != 0)
        ((PropIterator*)pIter)->Release();
    return true;
}
