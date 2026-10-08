// slice s005816f0 -- SP::cAppModeEditorBase::DrawLayer (2475 B) and the unrelated function at 0x005820a0.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
//
// DrawLayer is the cILayer entry point of the editor (this = the cILayer subobject, so the
// object's own `this` is this-4 where a callee wants it). It renders the model world through the
// world's layer renderer (vtable slot 0x13c) for the layer codes 0xc, 0xd, 0xf, 0x11, 0x14, 0x1a;
// every other layer code is ignored.
#include "types.h"

struct Color {
    float r, g, b, a;
    Color(float r_, float g_, float b_, float a_) : r(r_), g(g_), b(b_), a(a_) {}
};

struct cViewer {
    void Copy(const cViewer* src, int a, int b);     // 0x007c50b0 (SP::cViewer::Copy)
    void SetTarget(int a, int b);                    // 0x007c3ce0
    void SetRaster(const void* r, int a);            // 0x007c4be0
    void SetClearColor(const Color& c);           // 0x007c3c20
    void Flush(int mode);                            // 0x007c3c50
    void SetClearFlags(int f);                       // 0x007c3cc0
};

struct DrawCtx {                                      // arg 3 of DrawLayer
    cViewer* viewer;
    int a, b, c;
};

struct ILayerDraw {                                   // result of the world's slot 0x13c
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void Draw(int a0, int layer, DrawCtx* ctx, int a3);   // +0xc
};

struct IModelWorld {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual void s60();
    virtual void s61();
    virtual void s62();
    virtual void s63();
    virtual void s64();
    virtual void s65();
    virtual void s66();
    virtual void s67();
    virtual void s68();
    virtual void s69();
    virtual void s70();
    virtual void s71();
    virtual void s72();
    virtual void s73();
    virtual void s74();
    virtual void s75();
    virtual void s76();
    virtual void s77();
    virtual void s78();
    virtual ILayerDraw* GetLayerDraw();               // +0x13c
};

struct IDevA {                                        // FUN_0067dd40() result
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual bool Query3c();                            // +0x3c
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41();
    virtual void GetPair(int which, int* out, int z);  // +0xa8
};

struct IDevB {                                        // FUN_0067de00() result
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
    virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
    virtual void s52(); virtual void s53();
    virtual void GetPair(int* out);                     // +0xd8
};

IDevA* GetDevA();                                     // 0x0067dd40
IDevB* GetDevB();                                     // 0x0067de00

struct PropList {
    char GetDescription(unsigned id);                 // 0x006a25a0
};
extern PropList* gAppProps;                              // 0x015fd918

struct SceneObj {                                     // skin scene object
    int pad0;
    unsigned flags;       // +4
    char pad8[0x44];
    float tint[3];        // +0x4c
    float alpha;          // +0x58 (after tint)
};

struct SkinMgr {
    SceneObj* GetSceneObject(int which);              // 0x004c45d0
};

struct Block {
    char pad0[0x10];
    SceneObj* scene;       // +0x10
    char pad14[0xdc8 - 0x14];
    unsigned flags;        // +0xdc8
};

struct EditorModel {
    void GetTint(float* out, int z);                  // 0x004adca0
    int GetBlockCount();                              // 0x004accf0
    Block* GetBlock(int i);                           // 0x004accb0
};

struct PaletteUI {
    char IsPaintByNumber();                           // 0x005ca920
};

struct PaletteSub { virtual void s0(); virtual void s1(); virtual void s2();
                    virtual void Draw(int a0, int layer, DrawCtx* ctx, int a3); };
struct PaletteCat { char pad0[0x38]; PaletteSub* sub; };

void __cdecl SetShaderParam(int id, const void* p, int arg);    // 0x00777ae0
void __cdecl SetRenderState(int state, unsigned value);        // 0x00529350
void __cdecl FUN_005720f0(int flag);                            // 0x005720f0

extern volatile unsigned gRenderStateDirty;           // 0x016fa38c
extern int gRS_Mode;                                  // 0x016f923c
extern void* gRS_Aux;                                 // 0x016f9218
extern float gConstTiny;                              // 0x013f5c88
extern unsigned gDefaultLeglessHeight;                // 0x016f6e34

struct EditorBase;
struct EditorBaseMain {
    void DrawLayerGif(int a0, int layer, DrawCtx* ctx, int a3);   // 0x005812b0
};

struct EditorLayer {                                   // cILayer subobject of cAppModeEditorBase
    char pad0[0x80];
    IModelWorld* mModelWorld;                          // +0x80
    char pad84[4];
    IModelWorld* mBackgroundModelWorld;                // +0x88
    char pad8c[8];
    EditorModel* mEditorModel;                         // +0x94
    char pad98[0x14c - 0x98];
    SkinMgr* mSkinManager;                             // +0x14c
    char pad150[0x294 - 0x150];
    unsigned mMinLeglessHeightBits;                    // +0x294
    char pad298[0x2ed - 0x298];
    bool mTintDebug;                                   // +0x2ed
    char pad2ee[0x318 - 0x2ee];
    int mPaintMode;                                    // +0x318
    char pad31c[0x35c - 0x31c];
    PaletteCat* mPaintPaletteUI;                       // +0x35c
    char pad360[0x380 - 0x360];
    bool mSkipFrames;                                  // +0x380
    char pad381[0x394 - 0x381];
    bool mFlag394;                                     // +0x394
    char pad395[0x3ac - 0x395];
    float mF3ac;                                       // +0x3ac
    char pad3b0[0x3c0 - 0x3b0];
    PaletteUI* mPaletteUI;                             // +0x3c0
    char pad3c4[0x3cc - 0x3c4];
    cViewer* mViewerA;                                 // +0x3cc
    cViewer* mViewerB;                                 // +0x3d0
    char pad3d4[0x3dc - 0x3d4];
    bool mFlag3dc;                                     // +0x3dc
    char pad3dd[0x4a8 - 0x3dd];
    unsigned mCount4a8;                                // +0x4a8

    void DrawLayer(int a0, int layer, DrawCtx* ctx, int a3);
};

static inline unsigned Bit(unsigned v, int n) { return (v >> n) & 1; }

static inline void SetTint(SceneObj* s, const float* v)
{
    s->flags |= 2;
    s->alpha = 1.0f;
    s->tint[0] = v[0];
    s->tint[1] = v[1];
    s->tint[2] = v[2];
}

// @ 0x005816f0  (2475 bytes)
void EditorLayer::DrawLayer(int a0, int layer, DrawCtx* ctx, int a3)
{
    int pair[2];
    int pair2[2];
    DrawCtx c;
    switch (layer) {
    case 0xc:
        if (mBackgroundModelWorld) {
            if (!GetDevA()->Query3c())
                mMinLeglessHeightBits = gDefaultLeglessHeight;
            SetShaderParam(0x223, 0, 0);
            mBackgroundModelWorld->GetLayerDraw()->Draw(a0, layer, ctx, a3);
            SetShaderParam(0x223, (const void*)mMinLeglessHeightBits, 1);
        }
        return;

    case 0x1a:
        ctx->viewer->Flush(6);
        // fall through
    case 0xd:
        if (mModelWorld) {
            if (layer == 0xd) {
                if (mTintDebug && gAppProps->GetDescription(0x3d1bc93)) {
                    float v[3];
                    mEditorModel->GetTint(v, 0);
                    SceneObj* s1 = mSkinManager->GetSceneObject(1);
                    SceneObj* s0 = mSkinManager->GetSceneObject(0);
                    SceneObj* s2 = mSkinManager->GetSceneObject(2);
                    if (s1) SetTint(s1, v);
                    if (s0) SetTint(s0, v);
                    if (s2) SetTint(s2, v);
                    int n = mEditorModel->GetBlockCount();
                    for (int i = 0; i < n; ++i) {
                        Block* b = mEditorModel->GetBlock(i);
                        if (b && b->scene && !Bit(b->flags, 7) && !Bit(b->flags, 10))
                            SetTint(b->scene, v);
                    }
                }
                PaletteCat* cat = mPaintPaletteUI;
                if (cat) {
                    PaletteSub* sub = cat->sub;
                    if (sub)
                        sub->Draw(a0, 0xd, ctx, a3);
                }
            }
            SetShaderParam(0x223, (const void*)mMinLeglessHeightBits, 1);
            mModelWorld->GetLayerDraw()->Draw(a0, layer, ctx, a3);
            SetShaderParam(0x223, 0, 0);
        }
        return;
    case 0x14:
        if (mFlag3dc)
            ((EditorBaseMain*)((char*)this - 4))->DrawLayerGif(a0, layer, ctx, a3);
        return;

    case 0xf:
        if (mModelWorld && mPaintMode == 1 && mPaletteUI && mPaletteUI->IsPaintByNumber() &&
            mFlag394 && mCount4a8 != 0) {
            mViewerB->Copy(ctx->viewer, 0, 0);
            mViewerB->SetTarget(0xc, 0);
            pair[0] = -1;
            pair[1] = -1;
            GetDevA()->GetPair(1, pair, 0);
            mViewerB->SetRaster(pair, 1);
            mViewerB->SetClearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
            mViewerB->Flush(1);
            c.viewer = mViewerB;
            c.a = ctx->a;
            c.b = ctx->b;
            c.c = ctx->c;
            mModelWorld->GetLayerDraw()->Draw(a0, layer, &c, a3);
        }
        return;

    case 0x11:
        if (mModelWorld && !mSkipFrames) {
            if (mPaintMode == 1) {
                if (!mPaletteUI || !mPaletteUI->IsPaintByNumber())
                    return;
                mViewerB->Copy(ctx->viewer, 0, 0);
                if (!mFlag394 && mCount4a8 != 0) {
                    mViewerB->SetTarget(0xc, 0);
                    pair[0] = -1;
                    pair[1] = -1;
                    GetDevA()->GetPair(1, pair, 0);
                    mViewerB->SetRaster(pair, 1);
                    mViewerB->SetClearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
                    mViewerB->Flush(1);
                    c.viewer = mViewerB;
                    c.a = ctx->a;
                    c.b = ctx->b;
                    c.c = ctx->c;
                    mModelWorld->GetLayerDraw()->Draw(a0, layer, &c, a3);
                }
                mViewerB->SetTarget(0xc, 0);
                pair2[0] = -1;
                pair2[1] = -1;
                GetDevB()->GetPair(pair2);
                mViewerB->SetRaster(pair2, 1);
                mViewerB->SetClearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
                mViewerB->Flush(1);
                DrawCtx c2;
                c2.viewer = mViewerB;
                c2.a = ctx->a;
                c2.b = ctx->b;
                c2.c = ctx->c;
                float v3ac = mF3ac;
                SetShaderParam(0x230, &v3ac, 0);
                mModelWorld->GetLayerDraw()->Draw(a0, layer, &c2, a3);
                SetShaderParam(0x230, 0, 0);
                return;
            }
            {
                int savedMode = gRS_Mode;
                void* savedAux = gRS_Aux;
                                c.a = ctx->a;
                c.b = ctx->b;
                c.c = ctx->c;
                int modeIs4 = (savedMode == 4);
                c.viewer = mViewerA;
                mViewerA->Copy(ctx->viewer, 0, 1);
                mViewerA->SetTarget(0xe, 0);
                if (mCount4a8 != 0) {
                    gRenderStateDirty |= 0x10080;
                    gRS_Mode = 4;
                    gRS_Aux = 0;
                    SetRenderState(0x17, 4);
                    pair[0] = -1;
                    pair[1] = -1;
                    GetDevA()->GetPair(1, pair, 0);
                    mViewerA->SetRaster(pair, 1);
                    mViewerA->SetClearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
                    mViewerA->Flush(1);
                    float tiny = gConstTiny;
                    SetShaderParam(0x220, &tiny, 0);
                    mModelWorld->GetLayerDraw()->Draw(a0, layer, &c, a3);
                    SetShaderParam(0x220, 0, 0);
                }
                gRenderStateDirty |= 0x10080;
                gRS_Mode = 8;
                gRS_Aux = 0;
                pair2[0] = -1;
                pair2[1] = -1;
                GetDevB()->GetPair(pair2);
                mViewerA->SetRaster(pair2, 1);
                mViewerA->SetClearFlags(0);
                mViewerA->SetClearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
                mViewerA->Flush(1);
                c.viewer = mViewerA;
                mModelWorld->GetLayerDraw()->Draw(a0, layer, &c, a3);
                mViewerA->SetTarget(0, 0);
                FUN_005720f0(modeIs4);
                gRenderStateDirty |= 0x80;
                gRS_Aux = savedAux;
                SetRenderState(0x17, savedMode);
            }
            return;
        }
        if (mSkipFrames)
            mViewerA->Flush(1);
        return;
    }
}

// @ 0x005820a0  (429 bytes)
void FUN_005820a0() {}
