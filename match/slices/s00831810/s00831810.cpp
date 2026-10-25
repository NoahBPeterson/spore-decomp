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

// The console's timer slot (+0x10): the low/high pair is tested as a unit and the
// same object provides the restart / property-flush helpers the retail code calls.
struct ConsoleTimer {
    uint32_t mLow;                  // +0x00
    uint32_t mHigh;                 // +0x04
    uint32_t mExtra8;               // +0x08
    uint32_t mExtraC;               // +0x0c
    void Start();                   // 0x00435480
    void SetBoolProperty();         // 0x0093a2e0
    long long GetElapsedTicks();    // 0x0093a3a0
};

// Rect view handed out by a view root (only the left/right edges are read here).
struct ViewRect {
    float mPad0;                    // +0x00
    float mLeft;                    // +0x04
    float mPad8;                    // +0x08
    float mRight;                   // +0x0c
};

struct Vec2 { float x, y; };

// Interface views of the console target object (DebugConsole+0x64).  The same
// object is seen through two views because the retail code calls vtable slot 4
// both with and without the window-build arguments.
struct IViewRoot {
    virtual void Unk00();
    virtual void Unk01();
    virtual void Unk02();
    virtual void Unk03();
    virtual void Unk04();
    virtual void Unk05();
    virtual void Unk06();
    virtual void Unk07();
    virtual void Unk08();
    virtual void Unk09();
    virtual void Unk0a();
    virtual void Unk0b();
    virtual void Unk0c();
    virtual void Unk0d();
    virtual ViewRect *GetRect();                    // +0x38
    virtual void Unk0f();
    virtual void Unk10();
    virtual void Unk11();
    virtual void Unk12();
    virtual void Unk13();
    virtual void Unk14();
    virtual void Unk15();
    virtual void Unk16();
    virtual void Unk17();
    virtual void Unk18();
    virtual void Unk19();
    virtual void Unk1a();
    virtual void Unk1b();
    virtual void SetPosition(float x, float y);     // +0x70
    virtual void SetSize(float w, float h);         // +0x74
    virtual void Unk1e();
    virtual void Unk1f();
    virtual void SetOwnerWidth(void *p);            // +0x80
};

struct IConsoleTarget {
    virtual void Unk00();
    virtual void Unk01();
    virtual void Unk02();
    virtual void Unk03();
    virtual IViewRoot *GetRoot();                   // +0x10
    virtual void Unk05();
    virtual void Unk06();
    virtual void Unk07();
    virtual void RefreshRect(int a, int b, Vec2 *out);   // +0x20
    virtual void Unk09();
    virtual void Unk0a();
    virtual void Unk0b();
    virtual void Unk0c();
    virtual void Unk0d();
    virtual void Unk0e();
    virtual void Unk0f();
    virtual void Unk10();
    virtual void Unk11();
    virtual void Unk12();
    virtual void Unk13();
    virtual void Unk14();
    virtual void Unk15();
    virtual void Unk16();
    virtual void Unk17();
    virtual void Unk18();
    virtual void Unk19();
    virtual void Unk1a();
    virtual void Unk1b();
    virtual void SetPosition(float x, float y);     // +0x70
    virtual void SetSize(float w, float h);         // +0x74
    virtual void Unk1e();
    virtual void Unk1f();
    virtual void SetOwnerWidth(void *p);            // +0x80
};

// Second view of the same target: slot 4 builds the window animation target.
struct IWindowBuilder {
    virtual void Unk00();
    virtual void Unk01();
    virtual void Unk02();
    virtual void Unk03();
    virtual void *BuildWindow(Vec2 anchor, void *work);    // +0x10
};

struct IRefCounted {
    virtual void Unk00();
    virtual void Release();                         // +0x04
};

// Console behaviour ramp (cSPUIBehaviorTimeFunctionSmoothRamp, 0x007f60d0).
struct BehaviorRamp {
    void *mpVtbl;                   // +0x00
    void *mpRef;                    // +0x04
    void *mpRef2;                   // +0x08
    float mValue;                   // +0x0c
    float mSpan;                    // +0x10
    char  pad14[0x1c];              // +0x14..+0x30
    void  Build(float duration, float a, float b, float c, float d);   // 0x007f60d0
};

// Message object posted to the UI messaging server (0x0040 bytes).
struct UiBehaviorMessage {
    void    *mpVtbl;                // +0x00
    uint32_t mRefCount;             // +0x04
    void    *mpOwner;               // +0x08
    void    *mpUnk0c;               // +0x0c
    uint32_t mBehaviour;            // +0x10
    char     pad14[0x1c];           // +0x14..+0x30
    uint32_t mMessageId;            // +0x30
    char     pad34[4];              // +0x34
    uint32_t mFlags38;              // +0x38
    uint32_t mPad3c;                // +0x3c
};

namespace EA { namespace Messaging {
struct IMessageServer {
    virtual void Unk00();
    virtual void Unk01();
    virtual void Unk02();
    virtual void Unk03();
    virtual void Unk04();
    virtual void Unk05();
    virtual void PostMessage(uint32_t id, void *msg, int a, int b);   // +0x18
};

IMessageServer *GetServer();   // 0x00883860
} }   // namespace EA::Messaging
extern "C" void *__cdecl FUN_00f473a0(uint32_t size, const char *name, int a, int b, int c, int d);   // 0x00f473a0
extern "C" void *__cdecl SPUICreateWindowAnimationTargetPosition(void *window, void *work);            // 0x007f7050

// EA::Allocator::FixedBufferAllocator lives inline at DebugConsole+0x0c.
struct FixedBufInfo {
    uint32_t mSize;                 // +0x00
    uint32_t mCapacity;             // +0x04
    uint32_t mOffset;               // +0x08
    uint32_t mLink;                 // +0x0c
    uint32_t mSignature;            // +0x10
};
struct FixedBufferAllocator {
    FixedBufInfo *mpInfo;           // +0x00
    void Free(void *p);             // 0x004bcab0
    void destroy_shared();          // 0x004bca10
};

// cSPUIAnimator lives inline at DebugConsole+0x40.
struct AnimatorS {
    bool HasAnimation(void *ref, unsigned int id);   // 0x007f62c0
    bool RemoveAnimation(void *ref, int id);         // 0x007f6210
    void Update();                                   // 0x007f63b0
    void Dtor();                                     // 0x007f8c20
    void AddAnimation(void *target, void *ref, int id);   // 0x007f8d10
};

struct DebugConsole {
    void    *vptr0;        // +0x000
    void    *vptr4;        // +0x004
    uint32_t r8;           // +0x008
    void    *mpAlloc;      // +0x00c
    ConsoleTimer mTimer;   // +0x010..+0x020
    char     pad20[4];     // +0x020
    float    fAnimScale;   // +0x024
    char     pad28[8];     // +0x028..+0x030
    float    fDuration;    // +0x030
    float    f34;          // +0x034
    uint8_t  b38;          // +0x038
    uint8_t  mbFlag39;     // +0x039
    char     pad3a[2];     // +0x03a
    uint32_t mBehaviourId; // +0x03c
    char     mAnimator[0x20]; // +0x040..+0x060
    void    *mpRectProvider;  // +0x060
    void    *f64;          // +0x064
    char     pad68[0x14];  // +0x068..+0x07c
    char     mInfoInline[0xc];  // +0x07c
    void    *mpOwnerWidth;      // +0x088
    char     mInfoTail[0x88];   // +0x08c..+0x114
    void    *mImageInfos[8]; // +0x114
    uint8_t  mbHasUserDefaults; // +0x134
    char     pad135[0xdb];  // +0x135..+0x210
    void    *mpText;        // +0x210

    void  ResetImages();      // 0x00831ef0
    DebugConsole *Ctor();           // 0x008320d0
    void  Dtor();             // 0x00832160
    bool  CheckTimeout();     // 0x008321d0
    bool  SetTextProperty(struct PropOut *out, int kind, const struct StrVal *val);   // 0x00832010
    bool  StateCheck();       // 0x00832370
    void  Update();           // 0x008326c0
    bool  LayoutCheck(int mode);    // 0x00832230
    void  RefreshValues();          // 0x008324d0
    void  ApplyPending();           // 0x00832580
    void  Dtor2();            // 0x00832710
    void *GetImageInfo(int index);   // 0x00830c00 (other TU)
};

// ---------------------------------------------------------------- 0x00831ef0
// @ 0x00831ef0
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
    ((ImageInfo2 *)def)->CopyFrom((const ImageInfo2 *)mImageInfos[0]);
}

// ---------------------------------------------------------------- 0x008320d0
// @ 0x008320d0
DebugConsole *DebugConsole::Ctor()
{
    DebugConsole *self = this;
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
        *(void **)((char *)r + 0xc) = (char *)e + 8;
    } else {
        self->mpAlloc = 0;
    }
    self->mpText = 0;
    return self;
}

// ---------------------------------------------------------------- 0x00832160
// The console owns its text through the inline fixed-buffer allocator at +0x0c:
// release the text, drop the shared buffer when its signature marks it shared,
// then clear the buffer link and restore the base tables.
// @ 0x00832160
void DebugConsole::Dtor()
{
    FixedBufferAllocator *alloc = reinterpret_cast<FixedBufferAllocator *>(&mpAlloc);
    vptr0 = (void *)0x141a830;
    vptr4 = (void *)0x141a82c;
    alloc->Free(mpText);
    if (alloc->mpInfo != 0 && (alloc->mpInfo->mSignature & 0x40000000) != 0)
        alloc->destroy_shared();
    alloc->mpInfo = 0;
    vptr4 = (void *)&g_vtblCreatureAbility;
    vptr0 = (void *)&g_vtblEditorResource;
}

// ---------------------------------------------------------------- 0x008321d0
// @ 0x008321d0
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
// A live timer value means the console is already armed; otherwise re-run the
// layout check, restart the timer when it reports work, and when the timer still
// reads zero flush the property and drop the running animation.
// @ 0x00832370
bool DebugConsole::StateCheck()
{
    ConsoleTimer *timer = &mTimer;
    if ((timer->mLow | timer->mHigh) != 0)
        return true;
    if (LayoutCheck(1))
        timer->Start();
    if ((timer->mLow | timer->mHigh) == 0) {
        timer->SetBoolProperty();
        reinterpret_cast<AnimatorS *>(mAnimator)->RemoveAnimation(f64, 0x61ee327);
    }
    if (timer->mLow | timer->mHigh)
        return true;
    return false;
}

// ---------------------------------------------------------------- 0x008326c0
// Idle tick: while no console animation runs, apply a pending refresh and then
// poll the timeout (refreshing the values when it expires); the animator is
// updated last, by tail call.
// @ 0x008326c0
void DebugConsole::Update()
{
    AnimatorS *anim = reinterpret_cast<AnimatorS *>(mAnimator);
    if (!anim->HasAnimation(f64, 0x61ee329)) {
        if (b38 != 0)
            ApplyPending();
        uint32_t elapsed = mTimer.mLow | mTimer.mHigh;
        if (elapsed != 0) {
            if (CheckTimeout())
                RefreshValues();
        }
    }
    anim->Update();
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
extern "C" unsigned __cdecl wcslen(const wchar_t *);
#pragma intrinsic(wcslen)

struct PropOut { uint32_t pad0; uint32_t *mpSlot; };      // *mpSlot receives the text pointer
struct StrVal  { uint32_t mInstance; uint32_t pad4; uint32_t mTable; };
struct SPString {                                          // SP::cString (retail size 0x14)
    uint32_t raw[5];
    SPString(unsigned table, unsigned instance, const wchar_t *text);   // 0x006b5770
    ~SPString();                                           // 0x006b5240
    const wchar_t *GetText();                              // 0x006b55c0
};
struct FixedBufAlloc {
    void  Free(void *p);                                   // 0x004bcab0
    void *Malloc(unsigned size, unsigned align);           // 0x004bfc40
};

// @ 0x00832010
bool DebugConsole::SetTextProperty(PropOut *out, int kind, const StrVal *val)
{
    if (kind == 0x12) {
        SPString s(val->mTable, val->mInstance, 0);
        FixedBufAlloc *fba = (FixedBufAlloc *)((char *)this + 0xc);
        fba->Free(mpText);
        const wchar_t *t = s.GetText();
        unsigned len = wcslen(t);
        mpText = fba->Malloc(len * 2 + 2, 4);
        const wchar_t *src = s.GetText();
        wchar_t *dst = (wchar_t *)mpText;
        wchar_t c;
        do {
            c = *src;
            *dst = c;
            ++src;
            ++dst;
        } while (c != 0);
        *out->mpSlot = (uint32_t)mpText;
        return true;
    }
    return false;
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

// ---------------------------------------------------------------- 0x00832230
// Re-arm the console's animation: bail out while the timeout has not expired
// (or while the named animation still runs when the caller is not forcing), then
// rebuild the ramp from the remaining time and the target's width and push it
// into the animator.
// @ 0x00832230
bool DebugConsole::LayoutCheck(int animate)
{
    if (CheckTimeout())
        return false;
    AnimatorS *anim = reinterpret_cast<AnimatorS *>(mAnimator);
    if (animate == 0 && anim->HasAnimation(f64, 0x61ee327))
        return false;

    // remaining time scaled by the console's animation speed
    float remaining = fDuration - (float)mTimer.GetElapsedTicks() * fAnimScale;

    IConsoleTarget *target = reinterpret_cast<IConsoleTarget *>(f64);
    IViewRoot *root = target->GetRoot();
    ViewRect *rect = root->GetRect();
    float span = rect->mLeft - rect->mRight;

    BehaviorRamp ramp;
    ramp.Build(remaining, 0.0f, 0.0f, 0.0f, 0.0f);

    Vec2 anchor;
    anchor.x = 0.0f;
    anchor.y = ramp.mValue;
    void *window = reinterpret_cast<IWindowBuilder *>(f64)->BuildWindow(anchor, &span);
    void *targetPos = SPUICreateWindowAnimationTargetPosition(window, &span);
    anim->AddAnimation(targetPos, f64, 0x61ee327);

    // the builder handed back two owned references
    ramp.mpVtbl = (void *)0x013f6400;
    ramp.mpRef2 = (void *)0x013f63fc;
    if (ramp.mSpan == 0.0f && ramp.mpRef2 != 0)
        static_cast<IRefCounted *>(ramp.mpRef2)->Release();
    ramp.mpVtbl = (void *)0x013f63fc;
    if (ramp.mpRef != 0)
        static_cast<IRefCounted *>(ramp.mpRef)->Release();
    return true;
}

// ---------------------------------------------------------------- 0x008324d0
// Refresh the console values: stop the named animations, reset the timer block
// and post a behaviour message so the UI re-reads the console's behaviour id.
// @ 0x008324d0
void DebugConsole::RefreshValues()
{
    ConsoleTimer *timer = &mTimer;
    if ((timer->mLow | timer->mHigh) != 0) {
        if (!CheckTimeout())
            reinterpret_cast<AnimatorS *>(mAnimator)->RemoveAnimation(f64, 0x61ee329);
    }
    timer->SetBoolProperty();
    reinterpret_cast<AnimatorS *>(mAnimator)->RemoveAnimation(f64, 0x61ee327);
    timer->mLow = 0;
    timer->mHigh = 0;
    timer->mExtra8 = 0;
    timer->mExtraC = 0;

    UiBehaviorMessage *msg = static_cast<UiBehaviorMessage *>(
        FUN_00f473a0(0x40, (const char *)0x013f6b3c, 0, 0, 0, 0));
    if (msg == 0) {
        msg = 0;
    } else {
        msg->mMessageId = 0x0620837e;
        msg->mpVtbl = (void *)0x013eb90c;
        msg->mRefCount = 0;
        msg->mpVtbl = (void *)0x013eb844;
        msg->mFlags38 = 0;
    }
    msg->mpOwner = this;
    msg->mBehaviour = mBehaviourId;
    EA::Messaging::IMessageServer *server = EA::Messaging::GetServer();
    server->PostMessage(msg->mMessageId, msg, 0, 0);
}

// ---------------------------------------------------------------- 0x00832580
// Finish the pending layout change: push the target's rect onto the view root,
// restart the fade animation and notify the messaging server that the console
// was laid out again.
// @ 0x00832580
void DebugConsole::ApplyPending()
{
    IConsoleTarget *target = reinterpret_cast<IConsoleTarget *>(f64);
    IViewRoot *root = target->GetRoot();
    root->SetOwnerWidth(mpOwnerWidth);

    ViewRect *rect = reinterpret_cast<IViewRoot *>(mpRectProvider)->GetRect();
    float extent = rect->mRight - rect->mLeft;

    Vec2 rect2;
    target->RefreshRect(1, 1, &rect2);
    root->SetSize(rect2.y - rect2.x, 0.0f);
    root->SetPosition(0.0f, extent);

    AnimatorS *anim = reinterpret_cast<AnimatorS *>(mAnimator);
    anim->RemoveAnimation(f64, 0x61ee328);
    mTimer.SetBoolProperty();
    anim->RemoveAnimation(f64, 0x61ee327);
    if (mbFlag39)
        StateCheck();
    b38 = 0;

    UiBehaviorMessage *msg = static_cast<UiBehaviorMessage *>(
        FUN_00f473a0(0x40, (const char *)0x013f6b3c, 0, 0, 0, 0));
    if (msg == 0) {
        msg = 0;
    } else {
        msg->mMessageId = 0x0620837e;
        msg->mpVtbl = (void *)0x013eb90c;
        msg->mRefCount = 0;
        msg->mpVtbl = (void *)0x013eb844;
        msg->mFlags38 = 0;
    }
    msg->mpOwner = this;
    msg->mBehaviour = mBehaviourId;
    EA::Messaging::IMessageServer *server = EA::Messaging::GetServer();
    server->PostMessage(msg->mMessageId, msg, 0, 0);
}

// ---------------------------------------------------------------- 0x008323d0
void FUN_008323d0(void *) {}
