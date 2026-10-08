// w1g1 slice s005182f0 -- nSPSkinner paint-job Render entry points and the
// field-swap helper. cPaintDilateJob::Render (0x5183c0) is a partial skeleton.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void* SP_AppSystem();                                  // 0x0067dd00
void* GetSingleton();                                  // 0x00401080
float GetFloatProperty(uint32_t prop);                 // 0x006a2710

extern void* gAppProperties;                           // 0x015fd918
extern const float kOne;                               // 0x01485720
extern const float kZero;                              // 0x01485378
extern const float kConst6110;                         // 0x01486110
extern const float kConstB95C;                         // 0x013eb95c

class cRTTBuffer {
public:
    uint32_t pad0;           // 0x00
    uint32_t material;       // 0x04
    uint32_t pad1;           // 0x08
    float params[12];        // 0x0c: three 16-byte parameter vectors
    uint32_t textures[2];    // 0x3c
    int maxparam;            // 0x44
    int maxtexture;          // 0x48
    uint8_t pad2[0x58 - 0x4c];
    int width;               // 0x58
    int height;              // 0x5c
    uint32_t texture;        // 0x60

    void Setup();                                          // 0x00528e90
    void Set(int a, int b, int c, int d);                  // 0x00529280
    int Reserve(int n);                                    // 0x00529520
    void Tri(float* a, float* b, float* c, uint32_t col);  // 0x005295b0
    void Flush();                                          // 0x00529690
    void vertex(float* a, float* b, int flags);            // 0x005296b0
    void BeginDraw();                                      // 0x00529bf0
    void SwapWith(cRTTBuffer* o);                          // 0x00518b00
};

namespace nSPSkinner {

// ---------------------------------------------------------------------------
// cPaintRenderJob
// ---------------------------------------------------------------------------
class cPaintRenderJob {
public:
    uint8_t pad0[0x14];
    int mStage;   // 0x14
    bool RenderInternal();   // 0x00517430
    bool Render();           // 0x005182f0
};

// @ 0x005182f0
bool cPaintRenderJob::Render()
{
    int* app = (int*)SP_AppSystem();
    char ok = ((char(__thiscall*)(void*))(*(void**)(*app + 0x44)))(app);
    if (ok == 0) {
        if ((mStage == 0) && RenderInternal())
            return true;
        if ((mStage == 2) && RenderInternal())
            return true;
        if ((mStage == 3) && RenderInternal())
            return true;
        return RenderInternal();
    }
    for (int i = 0;; ++i) {
        if ((i > 0xb) && (mStage == 0))
            return false;
        if (RenderInternal())
            break;
    }
    return true;
}

// ---------------------------------------------------------------------------
// field swap helper (0x518b00)
// ---------------------------------------------------------------------------
class cFieldSwap {
public:
    uint32_t f0;                 // 0x00
    uint8_t pad1[0x50 - 0x04];
    uint32_t f50, f54;           // 0x50, 0x54
    uint32_t f58, f5c, f60;      // 0x58, 0x5c, 0x60

    void SwapWith(cFieldSwap* o);   // 0x00518b00
};

template <class T> inline void swapv(T& a, T& b) { T t = a; a = b; b = t; }

// @ 0x00518b00
void cFieldSwap::SwapWith(cFieldSwap* o)
{
    swapv(*(uint64_t*)((char*)this + 0x50), *(uint64_t*)((char*)o + 0x50));
    swapv(*(uint32_t*)((char*)this + 0x60), *(uint32_t*)((char*)o + 0x60));
    swapv(*(uint32_t*)((char*)this + 0x58), *(uint32_t*)((char*)o + 0x58));
    swapv(*(uint32_t*)((char*)this + 0x5c), *(uint32_t*)((char*)o + 0x5c));
    swapv(*(uint32_t*)this, *(uint32_t*)o);
}

// ---------------------------------------------------------------------------
// cPaintCopyIdentityJob::Render
// ---------------------------------------------------------------------------
class cPaintCopyIdentityJob {
public:
    bool Render();   // 0x00518bf0
};

// @ 0x00518bf0
bool cPaintCopyIdentityJob::Render()
{
    int iVar1 = (int)GetSingleton();
    cRTTBuffer* buf = *(cRTTBuffer**)(*(int*)(iVar1 + 0xc) + 0x10);
    int iVar2 = (int)GetSingleton();
    int p = *(int*)(*(int*)(iVar2 + 0xc) + 0x14);

    buf->Setup();
    buf->Set(0, 0, 0, 1);
    buf->material = 0x58653eac;

    uint32_t raster = *(uint32_t*)(p + 0x60);
    if ((raster != 0) && ((int)buf->maxtexture < 1))
        buf->maxtexture = 1;
    buf->textures[0] = raster;

    float a0 = kOne, a1 = kOne;
    float b0 = kZero, b1 = kZero;
    buf->vertex(&b0, &a0, -1);
    buf->Set(1, 1, 1, 1);
    buf->BeginDraw();
    return true;
}

// ---------------------------------------------------------------------------
// cPaintDifferentiateJob::Render
// ---------------------------------------------------------------------------
class cPaintDifferentiateJob {
public:
    bool Render();   // 0x00518cf0
};

// @ 0x00518cf0
bool cPaintDifferentiateJob::Render()
{
    uint32_t prop = 0x0c19db33;
    float val = GetFloatProperty(prop);
    if (val == kZero)
        val = kConst6110;

    float f4 = kZero, f8 = kZero;
    float d4 = kZero, d8 = kZero, dc = kZero;

    uint8_t c0[4] = { 0, 0, 0, 0xff };
    uint32_t col0 = *(uint32_t*)c0;
    uint8_t c1[4] = { 0, 0, 0, 0 };
    uint32_t col1 = *(uint32_t*)c1;

    int s = (int)GetSingleton();
    cRTTBuffer* buf = *(cRTTBuffer**)(*(int*)(s + 0xc) + 0x18);
    int ctx = *(int*)(*(int*)(s + 0xc) + 0x14);

    buf->Setup();
    buf->material = 0x9e74d163;

    uint32_t raster = *(uint32_t*)(ctx + 0x60);
    if ((raster != 0) && ((int)buf->maxtexture < 1))
        buf->maxtexture = 1;
    buf->textures[0] = raster;

    float invW = 1.0f / (float)*(int*)(ctx + 0x58);
    float invH = 1.0f / (float)*(int*)(ctx + 0x5c);

    float q0 = invW;
    float q1 = invH;
    float q2 = val / kConstB95C;
    float q3 = kZero;

    if ((int)buf->maxtexture <= 0)
        buf->maxtexture = 1;
    float* dst = (float*)((char*)buf + 0xc + 0);
    dst[0] = q0; dst[1] = q1; dst[2] = q2; dst[3] = q3;

    float r0 = kOne, r1 = kOne;
    float s0 = kZero, s1 = kZero;
    buf->vertex(&s0, &r0, -1);
    buf->BeginDraw();
    return true;
}

// ---------------------------------------------------------------------------
// cPaintDilateJob::Render
// ---------------------------------------------------------------------------
struct cDilateMesh {
    uint8_t pad0[0x30];
    float* verts;             // 0x30 (8 bytes per vertex)
    uint8_t pad1[0x58 - 0x34];
    uint32_t* idxBegin;       // 0x58
    uint32_t* idxEnd;         // 0x5c
    uint8_t pad2[0x80 - 0x60];
    uint32_t* indices;        // 0x80
};
struct cDilateVec { char* begin; char* end; };
struct cDilateModel { uint8_t pad[0x98]; cDilateVec parts; };   // 0x98
struct cDilateObj { uint8_t pad[8]; cDilateModel* model; };
struct cDilateSingleton {
    uint8_t pad0[0xc];
    char* table;              // 0xc
    cDilateMesh* mesh;        // 0x10
    uint8_t pad1[0x20 - 0x14];
    cDilateObj* obj;          // 0x20
};

inline const int& MinRef(const int& a, const int& b) { return (a < b) ? a : b; }

class cPaintDilateJob {
public:
    uint8_t pad0[0x10];
    int mComponent;   // 0x10
    int mPasses;      // 0x14
    int mStage;       // 0x18
    bool Render();   // 0x005183c0
};

// @ 0x005183c0
bool cPaintDilateJob::Render()
{
    float f4 = kZero, f8 = kZero;
    float d4 = kZero, d8 = kZero, dc = kZero;
    uint8_t c0[4] = { 0, 0, 0, 0xff };
    uint32_t col0 = *(uint32_t*)c0;
    uint8_t c1[4] = { 0, 0, 0, 0 };
    uint32_t col1 = *(uint32_t*)c1;

    cDilateSingleton* sing = (cDilateSingleton*)GetSingleton();
    cRTTBuffer* buf = *(cRTTBuffer**)(sing->table + 0x10 + mComponent * 4);

    if (mStage == 0) {
        buf->Setup();
        buf->Set(0, 0, 0, 1);
        buf->material = 0xf8b396;
        buf->Reserve(2);
        float p0[2] = { kZero, kZero };
        buf->Tri(p0, &f4, &d4, col1);
        float p1[2] = { kOne, kZero };
        buf->Tri(p1, &f4, &d4, col1);
        float p2[2] = { kOne, kOne };
        buf->Tri(p2, &f4, &d4, col1);
        float p3[2] = { kOne, kOne };
        buf->Tri(p3, &f4, &d4, col1);
        float p4[2] = { kZero, kOne };
        buf->Tri(p4, &f4, &d4, col1);
        float p5[2] = { kZero, kZero };
        buf->Tri(p5, &f4, &d4, col1);
        buf->Flush();

        cDilateMesh* mesh = ((cDilateSingleton*)GetSingleton())->mesh;
        cDilateObj* obj = ((cDilateSingleton*)GetSingleton())->obj;
        char* partsBegin = obj->model->parts.begin;
        int nParts = (obj->model->parts.end - obj->model->parts.begin) / 0x8c;
        (void)partsBegin; (void)nParts;
        uint32_t i = 0;
        uint32_t remaining = (uint32_t)(mesh->idxEnd - mesh->idxBegin) / 3;
        while (remaining != 0) {
            int got = buf->Reserve(remaining);
            uint32_t end = got * 3 + i;
            for (; i < end; ++i)
                buf->Tri((float*)((char*)mesh->verts + mesh->indices[i] * 8),
                         (float*)((char*)mesh->verts + mesh->indices[i] * 8), &d4, col0);
            remaining -= got;
            buf->Flush();
        }
        buf->Set(1, 1, 1, 1);
        buf->BeginDraw();
        mStage = 1;
        return false;
    }

    int* app = (int*)SP_AppSystem();
    char ok = ((char(__thiscall*)(void*))(*(void**)(*app + 0x44)))(app);
    int cap = (ok != 0) ? 8 : 2;
    int rem = mPasses - mStage + 1;
    int n = MinRef(rem, cap);
    cRTTBuffer* cur = buf;
    cDilateSingleton* sing2 = (cDilateSingleton*)GetSingleton();
    cRTTBuffer* dst = *(cRTTBuffer**)(sing2->table + 0x18);

    for (int i = 0; i < n; ++i) {
        dst->Setup();
        dst->material = 0xfa2f3df4;
        float invW = 1.0f / (float)buf->width;
        float invH = 1.0f / (float)buf->height;
        float q0 = invW, q1 = invH, q2 = kZero, q3 = kZero;
        if (dst->maxparam <= 0)
            dst->maxparam = 1;
        dst->params[0] = q0; dst->params[1] = q1;
        dst->params[2] = q2; dst->params[3] = q3;
        uint32_t raster = buf->texture;
        if ((raster != 0) && (dst->maxtexture < 1))
            dst->maxtexture = 1;
        dst->textures[0] = raster;
        float r0 = kOne, r1 = kOne;
        float s0 = kZero, s1 = kZero;
        dst->vertex(&s0, &r0, -1);
        dst->BeginDraw();
        dst->SwapWith(buf);
    }
    if (buf != cur) {
        dst->Setup();
        dst->material = 0xa0468560;
        uint32_t raster = buf->texture;
        if ((raster != 0) && (dst->maxtexture < 1))
            dst->maxtexture = 1;
        dst->textures[0] = raster;
        float r0 = kOne, r1 = kOne;
        float s0 = kZero, s1 = kZero;
        dst->vertex(&s0, &r0, -1);
        dst->BeginDraw();
        dst->SwapWith(buf);
    }
    mStage = mStage + n;
    return mStage > mPasses;
}

} // namespace nSPSkinner
