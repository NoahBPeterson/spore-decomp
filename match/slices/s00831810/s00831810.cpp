// Slice s00831810 -- SP::cSPUIDebugConsole (derives the SPUI standard drawable).
// Region flags /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------- masked externs
extern char g_vtblEditorResource;      // 0x13eb938
extern char g_vtblContentValidation;   // 0x13ec458
extern char g_vtblCreatureAbility;     // 0x13ef094
extern char g_vtblConsole;             // 0x141a894
extern char g_vtblConsoleSec;          // 0x141a884
extern char g_vtblPaintSystem;         // 0x13eb394

extern "C" void __cdecl EA_Free(void *);          // 0xf47380
extern "C" int  __cdecl FUN_00987900();           // 0x987900
extern "C" void __cdecl _ReadWriteBarrier(void);

struct ShadowDesc {
    uint32_t mode1, mode2, f8, fc, f10;
    float    s14, s18, s1c, s20;
    uint32_t f24;
    void SetMode1(int mode);   // 0x00830280 (other TU)
    void SetMode2(int mode);   // 0x00830150 (other TU)
};

struct ImageInfo2 {
    void    *vptr0, *vptr4;
    uint32_t r8;
    void    *mpImage, *mpIcon;
    char     pad[0x84];
    void CopyFrom(const ImageInfo2 *src);   // 0x008310a0 (other TU)
};

struct Stopwatch { double GetElapsed(); };  // 0x93a3a0
struct Animator  { void Dtor(); };          // 0x7f8c20

struct DebugConsole {
    void    *vptr0;        // +0x000
    void    *vptr4;        // +0x004
    uint32_t r8;           // +0x008
    void    *mpAlloc;      // +0x00c
    char     pad10[0x24];  // +0x010..+0x034 (stopwatch at +0x10)
    float    f34;          // +0x034
    uint8_t  b38;          // +0x038
    char     pad39[7];
    char     mAnimator[0x24]; // +0x040
    void    *f64;          // +0x064
    char     pad68[0x14];
    char     mInfo[0x98];  // +0x07c
    void    *mImageInfos[8]; // +0x114
    uint8_t  mbHasUserDefaults; // +0x134
    char     pad135[0xdb];  // +0x135..+0x210
    void    *mpText;        // +0x210

    void  ResetImages();      // 0x00831ef0
    void  Dtor();             // 0x00832160
    bool  CheckTimeout();     // 0x008321d0
    bool  StateCheck();       // 0x00832370
    void  Update();           // 0x008326c0
    void  Dtor2();            // 0x00832710
    void *GetImageInfo(int index);   // 0x00830c00 (other TU)
};

// ---------------------------------------------------------------- 0x00831ef0
void DebugConsole::ResetImages()
{
    FUN_00987900();
    for (int i = 0; i < 8; ++i) {
        void *p = mImageInfos[i];
        if (p == 0) {
            void *def = (char *)this + 0x7c;
            void *old = mImageInfos[i];
            if (def != old) {
                if (def)
                    ((void (__thiscall *)(void *))(*(void ***)def)[0])(def);
                mImageInfos[i] = def;
                if (old)
                    ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
            }
        } else {
            ((ShadowDesc *)((char *)p + 0x70))->SetMode1(*(int *)((char *)p + 0x70));
            ((ShadowDesc *)((char *)p + 0x70))->SetMode2(*(int *)((char *)p + 0x74));
            ((ShadowDesc *)((char *)p + 0x48))->SetMode1(*(int *)((char *)p + 0x48));
            ((ShadowDesc *)((char *)p + 0x48))->SetMode2(*(int *)((char *)p + 0x4c));
        }
    }
    mbHasUserDefaults = 0;
    void *def = (char *)this + 0x7c;
    if (mImageInfos[0] == 0) {
        void *old = mImageInfos[0];
        if (def != old) {
            if (def)
                ((void (__thiscall *)(void *))(*(void ***)def)[0])(def);
            mImageInfos[0] = def;
            if (old)
                ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
        }
    }
    ((ImageInfo2 *)mImageInfos[0])->CopyFrom((const ImageInfo2 *)def);
}

// ---------------------------------------------------------------- 0x008320d0
void DebugConsole_Ctor(DebugConsole *self)
{
    self->vptr4 = (void *)0x13ef094;
    self->r8 = 0;
    void *p = (char *)self + 0x10;
    self->vptr0 = (void *)0x141a830;
    self->vptr4 = (void *)0x141a82c;
    self->mpAlloc = p;
    if (p) {
        *(uint32_t *)p = 0x86421357;
        void *q = self->mpAlloc;
        *(uint32_t *)((char *)q + 4) = 0x1f0;
        q = self->mpAlloc;
        *(uint32_t *)((char *)q + 0x14) = 0;
        *(uint32_t *)((char *)q + 0x10) = 8;
        void *e = (char *)q + 0x10;
        void *r = self->mpAlloc;
        *(int *)((char *)e + 8) = *(int *)((char *)r + 4) - 8;
        *(void **)((char *)e + 0xc) = e;
        r = self->mpAlloc;
        *(int *)((char *)r + 8) = *(int *)((char *)r + 4) - 8;
        r = self->mpAlloc;
        *(void **)((char *)r + 0xc) = e;
    } else {
        self->mpAlloc = 0;
    }
    self->mpText = 0;
}

// ---------------------------------------------------------------- 0x00832160
void DebugConsole::Dtor()
{
    vptr0 = (void *)0x141a830;
    vptr4 = (void *)0x141a82c;
    EA_Free(mpText);
    mpAlloc = 0;
    vptr4 = (void *)&g_vtblCreatureAbility;
    vptr0 = (void *)&g_vtblEditorResource;
}

// ---------------------------------------------------------------- 0x008321d0
bool DebugConsole::CheckTimeout()
{
    void *pi = (void *)((int (__thiscall *)(void *))(*(void ***)f64)[0x10 / 4])(f64);
    char *r = (char *)((int (__thiscall *)(void *))(*(void ***)pi)[0x38 / 4])(pi);
    if (*(float *)(r + 0xc) >= 0.0f) {
        double t = ((Stopwatch *)((char *)this + 0x10))->GetElapsed();
        if ((float)t * *(float *)((char *)this + 0x24) <= *(float *)((char *)this + 0x30))
            return false;
    }
    return true;
}

// ---------------------------------------------------------------- 0x00832370
bool DebugConsole::StateCheck()
{
    void *p = (char *)this + 0x10;
    if (*(uint32_t *)p != 0 || *(uint32_t *)((char *)p + 4) != 0)
        return true;
    return false;
}

// ---------------------------------------------------------------- 0x008326c0
void DebugConsole::Update()
{
}

// ---------------------------------------------------------------- 0x00832710
void DebugConsole::Dtor2()
{
    *(void **)this = &g_vtblConsole;
    *(void **)((char *)this + 8) = &g_vtblConsoleSec;
    _ReadWriteBarrier();
    void *a = *(void **)((char *)this + 0x88);
    void *cap = *(void **)((char *)this + 0x90);
    if ((((int)((char *)cap - (char *)a) & ~1) > 2) && a && a != *(void **)((char *)this + 0x98))
        EA_Free(a);
    void *c = *(void **)((char *)this + 0x64);
    if (c)
        ((void (__thiscall *)(void *))(*(void ***)c)[1])(c);
    void *d = *(void **)((char *)this + 0x60);
    if (d)
        ((void (__thiscall *)(void *))(*(void ***)d)[1])(d);
    ((Animator *)((char *)this + 0x40))->Dtor();
    *(void **)((char *)this + 8) = &g_vtblPaintSystem;
    *(void **)this = &g_vtblContentValidation;
}

// ---------------------------------------------------------------- 0x00832010
int FUN_00832010(void * /*self*/, int /*a*/, int /*kind*/, void * /*val*/)
{
    return 0;
}

// ---------------------------------------------------------------- 0x00831810 cSPUIStdDrawable::Draw
#include <math.h>

struct Canvas { virtual void v0(); virtual void SetValue(int v); };   // Begin2D result, slot 1 = 0x4
struct RefImage { virtual void AddRef(); virtual void Release(); };
struct ARef {
    RefImage *p;
    ~ARef() { if (p) p->Release(); }
};
struct DropShadowDesc {
    uint32_t mSize, mStrength, mQuality;
    float mOffsetX, mOffsetY, mSizeX, mSizeY, mSmoothness, mSaturation;
    uint32_t mColor;
    void SetStrength(uint32_t s);   // 0x00830150 (other TU)
};
extern "C" void __cdecl CopyWithQualityAdjustment(DropShadowDesc *dst, const DropShadowDesc *src, int quality); // 0x96e3a0

struct StdImageInfo {
    void *vt0, *vt4;
    int mRef;
    ARef mpImage;          // +0x0c
    ARef mpImageIcon;      // +0x10
    uint32_t mImageColor, mImageIconColor, mIconDrawMode;   // +0x14..
    uint32_t mShadowStrokeMode, mShadowHaloMode;            // +0x20, +0x24
    float mBgScale[2], mBgOffset[2], mIconScale[2], mIconOffset[2];
    DropShadowDesc mShadowStroke;   // +0x48
    DropShadowDesc mShadowHalo;     // +0x70
    StdImageInfo();                 // 0x00830810 (other TU)
};

inline int FloatToInt(float f)
{
    __declspec(align(8)) __int64 result;
    __asm { fld f
            fistp result }
    return (int)result;
}

struct RenderContext { Canvas *Begin2D(int flag); };     // 0x95bc10
struct DrawParams { uint32_t flags; uint32_t f4; uint32_t color; uint32_t fc; };
struct RectF {
    float l, t, r, b;
    bool operator==(const RectF &o) const { return l == o.l && t == o.t && r == o.r && b == o.b; }
    float Width() const { return r - l; }
    float Height() const { return b - t; }
    RectF &operator=(const RectF &o) { l = o.l; t = o.t; r = o.r; b = o.b; return *this; }
};

extern "C" void __cdecl DrawStdButton(Canvas *c, const RectF *r, uint32_t color, uint32_t state, float thickness); // 0x95d780
extern "C" void __cdecl DrawFocusRect(Canvas *c, const RectF *r, uint32_t color, float w);   // 0x95da40

struct DrawLayerPass {
    StdImageInfo *info;
    RefImage *image;
    uint32_t color;
    uint32_t isIcon;
    DropShadowDesc *shadow;
    bool enabled;
};

struct StdDrawable {
    char pad0[0x50];
    float mFocusWidth;          // +0x50
    char pad54[0x138 - 0x54];
    DrawParams mDrawParams;     // +0x138
    RectF mDrawArea;            // +0x148
    float mOOWidth, mOOHeight;  // +0x158
    void FillInfo(uint32_t flags, StdImageInfo *out);                                     // 0x831410
    void DrawLayer(Canvas *c, const RectF *r, StdImageInfo *info, uint32_t color, uint32_t isIcon); // 0x830d90
    void Draw(RenderContext *ctx, const RectF *area, const DrawParams *params);
};

// cSPUIStdDrawable::Draw @ 0x00831810
void StdDrawable::Draw(RenderContext *ctx, const RectF *area, const DrawParams *params)
{
    Canvas *canvas = ctx->Begin2D(0);
    canvas->SetValue(-1);
    mDrawParams = *params;
    StdImageInfo info;
    FillInfo(mDrawParams.flags, &info);
    if (!(mDrawArea == *area)) {
        mDrawArea = *area;
        mOOWidth = 1.0f / mDrawArea.Width() + 1e-6f;
        mOOHeight = 1.0f / mDrawArea.Height() + 1e-6f;
    }
    if (info.mpImage.p == 0 && info.mpImageIcon.p == 0) {
        DrawStdButton(canvas, &mDrawArea, params->color, params->flags & 0xf, 3.0f);
        if (params->flags & 0x10)
            DrawFocusRect(canvas, &mDrawArea, -1, mFocusWidth);
        return;
    }
    DrawLayerPass passes[6];
    passes[0].info = &info; passes[0].image = info.mpImage.p; passes[0].color = info.mImageColor;
    passes[0].isIcon = 0; passes[0].shadow = &info.mShadowHalo;
    passes[0].enabled = false;
    if (info.mShadowHaloMode == 1 || info.mShadowHaloMode == 2) passes[0].enabled = true;
    passes[1].info = &info; passes[1].image = info.mpImage.p; passes[1].color = info.mImageColor;
    passes[1].isIcon = 0; passes[1].shadow = &info.mShadowStroke;
    passes[1].enabled = false;
    if (info.mShadowStrokeMode == 1 || info.mShadowStrokeMode == 2) passes[1].enabled = true;
    passes[2].info = &info; passes[2].image = info.mpImage.p; passes[2].color = info.mImageColor;
    passes[2].isIcon = 0; passes[2].shadow = 0; passes[2].enabled = true;
    passes[3].info = &info; passes[3].image = info.mpImageIcon.p; passes[3].color = info.mImageIconColor;
    passes[3].isIcon = 1; passes[3].shadow = &info.mShadowHalo;
    passes[3].enabled = false;
    if (info.mShadowHaloMode == 1 || info.mShadowHaloMode == 3) passes[3].enabled = true;
    passes[4].info = &info; passes[4].image = info.mpImageIcon.p; passes[4].color = info.mImageIconColor;
    passes[4].isIcon = 1; passes[4].shadow = &info.mShadowStroke;
    passes[4].enabled = false;
    if (info.mShadowStrokeMode == 1 || info.mShadowStrokeMode == 3) passes[4].enabled = true;
    passes[5].info = &info; passes[5].image = info.mpImageIcon.p; passes[5].color = info.mImageIconColor;
    passes[5].isIcon = 1; passes[5].shadow = 0; passes[5].enabled = true;

    for (int off = 0; off < 6 * (int)sizeof(DrawLayerPass); off += sizeof(DrawLayerPass)) {
        DrawLayerPass &p = *(DrawLayerPass *)((char *)passes + off);
        if (p.image == 0 || !p.enabled)
            continue;
        if (p.shadow == 0) {
            DrawLayer(canvas, &mDrawArea, p.info, p.color, p.isIcon);
            continue;
        }
        DropShadowDesc d;
        d.mSize = 0; d.mStrength = 2; d.mQuality = 3;
        d.mOffsetX = 0.0f; d.mOffsetY = 0.0f; d.mSizeX = 0.0f; d.mSizeY = 0.0f;
        d.mColor = 0;
        d.SetStrength(2);
        CopyWithQualityAdjustment(&d, p.shadow, 1);
        float offX = d.mOffsetX, offY = d.mOffsetY;
        float negX = -d.mSizeX, negY = -d.mSizeY;
        float cenX = (negX + d.mSizeX) * 0.5f;
        float cenY = (negY + d.mSizeY) * 0.5f;
        uint32_t rgb = d.mColor & 0xffffff;
        float maxR2 = ((d.mSizeX - cenX) * (d.mSizeX - cenX) + (d.mSizeY - cenY) * (d.mSizeY - cenY)) + 1.0f;
        float dist = (float)sqrt((double)(d.mSizeX * d.mSizeX + d.mSizeY * d.mSizeY)) + 1.0f;
        for (float x = negX; x <= d.mSizeX; x += 1.0f) {
            for (float y = negY; y <= d.mSizeY; y += 1.0f) {
                float dx = (float)floor((double)(x + offX));
                float dy = (float)floor((double)(y + offY));
                if (dx != 0.0f || dy != 0.0f) {
                    RectF r;
                    r.l = mDrawArea.l + dx;
                    r.t = mDrawArea.t + dy;
                    r.r = mDrawArea.r + dx;
                    r.b = mDrawArea.b + dy;
                    float a = (d.mSaturation / dist) *
                              (1.0f - ((x - cenX) * (x - cenX) + (y - cenY) * (y - cenY)) / maxR2) + d.mSmoothness;
                    if (0.0f <= a) {
                        if (1.0f < a)
                            a = 1.0f;
                    } else {
                        a = 0.0f;
                    }
                    a = a * 255.0f;
                    uint32_t alpha = FloatToInt(a);
                    DrawLayer(canvas, &r, p.info, (alpha << 24) + rgb, p.isIcon);
                }
            }
        }
    }
}

// ---------------------------------------------------------------- unfinished big functions
void FUN_00832230(void *) {}
void FUN_008323d0(void *) {}
void FUN_008324d0(void *) {}
void FUN_00832580(void *) {}
