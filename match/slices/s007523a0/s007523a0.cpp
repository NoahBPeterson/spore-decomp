// Slice s007523a0 -- SP::cEffectsRenderer::RenderMainEffectsLayer (retail 0x007523a0).
//
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.  Retail moved this routine onto the
// model-world render path: the entry pointer is the layer interface subobject
// at +4 of the model world, and the two model-world calls receive `this - 4`.
// The body sets up the per-viewer draw state, emits the batch-id pass, walks
// the opaque and alpha draw lists, and restores the blend mode.
//
// Not byte-exact: cl keeps `this` in ebp and `flags`/`viewer`/draw-set in
// ebx/esi/edi, while the original is ebp/esi/ebx/edi; our version also spills
// `this` once and folds the draw-set base into the `lea`.  Behavior is
// reconstructed field-for-field; see nonmatching.txt for the difftest verdict.
#include "types.h"

namespace SP {

// ---------------------------------------------------------------------------
// Interfaces stored in a draw-set record and handed back by the state sink.
// Only the slots the layer call actually uses are named; the rest preserve the
// retail vtable offsets.
// ---------------------------------------------------------------------------
struct ILightingWorld {
    virtual void v0();  virtual void v1();  virtual void v2();
    virtual void v3();  virtual void v4();  virtual void v5();
    virtual void v6();  virtual void v7();  virtual void v8();
    virtual void SetViewer(void* viewer);           // +0x24
};

struct IStateSink {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void SetTarget(void* target);           // +0x50
};

// Viewer/camera side object.  Both entry points are direct calls in retail.
struct cViewer {
    bool Update();                                  // 0x007c4fd0
    void PostUpdate();                              // 0x007c3c10
};

struct cDrawList;

// ---------------------------------------------------------------------------
// cDrawSetInfo: 0x20-byte per-layer record.  The retail array starts at
// +0x1b0 of the layer interface and is indexed by the low byte of the layer
// flags.
// ---------------------------------------------------------------------------
struct cDrawSetInfo {
    int32_t             mViewer;                    // +0x00 (index into viewers)
    int32_t             mDepthOffset;               // +0x04
    uint8_t             mPad08[0x18 - 0x08];        // +0x08
    ILightingWorld*     mLightingWorld;             // +0x18
    bool                mUseState;                  // +0x1c
    uint8_t             mPad1d[0x20 - 0x1d];        // +0x1d
};

struct cDrawList {
    void** mpBegin;                                 // +0x00
    void** mpEnd;                                   // +0x04
};

// ---------------------------------------------------------------------------
// cILayer: secondary interface subobject of the model world (the complete
// cModelWorld starts four bytes before `this`).  Only the touched region is
// named; gaps preserve the retail offsets.
// ---------------------------------------------------------------------------
struct cModelWorld;

struct cILayer {
    virtual void RenderMainEffectsLayer(uint32_t flags, void* unused,
                                        void** viewers, void* camera);
    uint8_t         mPad04[0x19 - 0x04];            // +0x04
    bool            mActive;                        // +0x19
    uint8_t         mPad1a[0x1b0 - 0x1a];           // +0x1a
    cDrawSetInfo    mDrawSets[8];                   // +0x1b0 (stride 0x20)
    uint8_t         mPad2b0[0x2e8 - 0x2b0];         // +0x2b0
    cDrawList       mDrawList;                      // +0x2e8
    uint8_t         mPad2f0[0x2fc - 0x2f0];         // +0x2f0
    cDrawList       mAlphaDrawList;                 // +0x2fc
};

// The complete model world.  cIModelWorld contributes the leading vptr so the
// cILayer base lands at +4, matching the retail call sites.
struct cIModelWorld {
    virtual void v0();
};

struct cModelWorld : cIModelWorld, cILayer {
    void UpdateVisibility(uint32_t flags, void* viewer, uint32_t index); // 0x007507e0
    void DrawLayer(bool alpha, cDrawList* list, uint32_t flags,
                   void* camera, void* viewer);      // 0x0074f800
};

// ---------------------------------------------------------------------------
// Application properties: g_sAppProperties->mProperties->mRendererFlag.
// ---------------------------------------------------------------------------
struct cPropertyList {
    uint8_t  mPad00[0x14];                          // +0x00
    uint32_t mRendererFlag;                         // +0x14
};

struct cAppProperties {
    uint8_t         mPad00[0x3c];                   // +0x00
    cPropertyList*  mProperties;                    // +0x3c
};

extern "C" cAppProperties* g_sAppProperties;        // 0x015fd918

// Render/raster state touched while the layer's batch-id pass is prepared.
extern "C" uint32_t g_renderStateDirty;             // 0x016fa38c
extern "C" uint32_t g_rasterStageDirty;             // 0x016fa3a8
extern "C" uint32_t g_blendState;                   // 0x016f923c
extern "C" uint32_t g_rasterStateA;                 // 0x016f9218
extern "C" void*    g_raster;                       // 0x016f9650

// Free callees (cdecl in retail).
extern "C" void FUN_00761cf0(int32_t depthOffset);              // 0x00761cf0
extern "C" void FUN_006e65a0(int32_t a, int32_t b, int32_t c);  // 0x006e65a0
extern "C" void FUN_00529350(uint32_t state, int32_t value);    // 0x00529350
extern "C" void FUN_006e6570(const float* color);               // 0x006e6570
extern "C" void FUN_00777ae0(uint32_t id, void* shader, int32_t a); // 0x00777ae0
extern "C" IStateSink* FUN_0067ddc0();                          // 0x0067ddc0
extern "C" void FUN_011f1340(int32_t mode);                     // 0x011f1340

// @ 0x007523a0
void cILayer::RenderMainEffectsLayer(uint32_t flags, void* unused,
                                     void** viewers, void* camera)
{
    (void)unused;

    if (!mActive)
        return;
    if (g_sAppProperties->mProperties->mRendererFlag == 0)
        return;

    uint32_t index = flags & 0xff;
    cDrawSetInfo& set = mDrawSets[index];
    int32_t viewerIndex = set.mViewer;
    if (viewerIndex < 0)
        return;

    void* viewer = viewers[viewerIndex];
    if (viewer == 0)
        return;

    if ((flags & 0x7f00) == 0)
        flags |= 0x7f00;

    cModelWorld& world = *static_cast<cModelWorld*>(this);

    if ((flags & 0x100) != 0)
        world.UpdateVisibility(flags, viewer, index);

    if ((flags & 0x3000) == 0)
        return;

    cViewer* renderViewer = static_cast<cViewer*>(viewer);
    if (!renderViewer->Update())
        return;

    uint32_t blend = flags & 0x800;
    if (blend != 0) {
        FUN_00761cf0(set.mDepthOffset);
        g_renderStateDirty |= 0x10080;
        g_rasterStageDirty |= 1;
        g_blendState = 4;
        g_rasterStateA = 1;
        g_raster = 0;
        FUN_006e65a0(0, 6, 2);
        FUN_006e65a0(0, 5, 2);
        FUN_006e65a0(0, 7, 2);
        FUN_00529350(0x17, 2);
        float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        FUN_006e6570(color);
        FUN_00777ae0(0x202, 0, 0);
        FUN_00777ae0(0x247, 0, 0);
        FUN_00777ae0(0x20c, 0, 0);
        FUN_00777ae0(0x21e, 0, 0);
        FUN_00777ae0(0x210, 0, 0);
        FUN_00777ae0(0x233, 0, 0);
        FUN_00777ae0(0x235, 0, 0);
        FUN_00777ae0(0x211, 0, 0);
        FUN_00777ae0(3, 0, 0);
        FUN_00777ae0(4, 0, 0);
    }

    if (set.mLightingWorld != 0)
        set.mLightingWorld->SetViewer(viewer);

    if (set.mUseState)
        FUN_0067ddc0()->SetTarget(set.mLightingWorld);

    if ((flags & 0x1000) != 0 && mDrawList.mpBegin != mDrawList.mpEnd)
        world.DrawLayer(false, &mDrawList, flags, camera, viewer);

    if ((flags & 0x2000) != 0 && mAlphaDrawList.mpBegin != mAlphaDrawList.mpEnd)
        world.DrawLayer(true, &mAlphaDrawList, flags, camera, viewer);

    renderViewer->PostUpdate();

    if (blend != 0)
        FUN_011f1340(0x10002);
}

}  // namespace SP
