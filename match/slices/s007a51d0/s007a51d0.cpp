// slice s007a51d0 — SP::cGraphicsSystem render-target / texture initialisation,
// per-frame rendering update, bake-buffer recycling and the graphics-system ctor.
// Module flags: /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <intrin.h>

// One unnamed vtable slot. Names are class-scoped, so the same macro sequence can be
// reused to reach the exact retail vtable byte offset in each interface.
#define PV(n) virtual void pv##n();

namespace SP {

// ---------------------------------------------------------------------------
// Render target description returned by the RTT manager's create call.
// ---------------------------------------------------------------------------
struct cRenderTargetRectID {
    int mPageID;      // +0x00
    int mAllocID;     // +0x04
};

// ---------------------------------------------------------------------------
// Texture instance: the intrusive reference count lives at +0x08.
// ---------------------------------------------------------------------------
class cTextureInstance {
public:
    void* mField0;                 // +0x00
    void* mField4;                 // +0x04
    volatile long mRefCount;       // +0x08
};

// ---------------------------------------------------------------------------
// Intrusive texture handle.
// ---------------------------------------------------------------------------
class cTextureHandle {
public:
    void* mpObject;                                 // +0x00
    void* SetImageResource(void* resource);          // va 00576650
    void  Release();
};

void cTextureHandle::Release()
{
    cTextureInstance* inst = (cTextureInstance*)mpObject;
    if (inst == 0)
        return;
    mpObject = 0;
    if (_InterlockedDecrement(&inst->mRefCount) < 1)
        _InterlockedIncrement(&inst->mRefCount);
}

// ---------------------------------------------------------------------------
// Graphics-system property list (the application globals live behind a pointer).
// ---------------------------------------------------------------------------
class cDirectPropertyList {
public:
    bool GetDescription(uint32_t id) const;           // va 006a25a0
    int  GetIntProperty(uint32_t id) const;           // va 006a2660
};

// ---------------------------------------------------------------------------
// Render target manager: the four vtable entries this slice uses.
// ---------------------------------------------------------------------------
class cRenderTargetManager {
public:
    PV(0) PV(1) PV(2) PV(3)
    virtual cRenderTargetRectID* CreateRenderTarget(cRenderTargetRectID* out, int width,
                                                    int height, int format, int flags,
                                                    int key, int extra);   // 0x10
    virtual void  ReleaseRenderTarget(int pageID, int allocID);            // 0x14
    PV(6)
    virtual void* GetRenderTargetImage(int pageID, int allocID);           // 0x1c
    PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual void  SetRenderTargetName(int pageID, int allocID, const char* name);  // 0x48
};

// ---------------------------------------------------------------------------
// Renderer (slot 0x34 = per-frame submit, slot 0x80 = effects pass).
// ---------------------------------------------------------------------------
class cRenderService {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    virtual void UpdateRenderer(int delta);      // 0x34
    PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31)
    virtual void UpdateEffects(int delta);       // 0x80
};

// ---------------------------------------------------------------------------
// Viewport extent (the first pair sits at +0, the second at +4).
// ---------------------------------------------------------------------------
struct cViewportExtent {
    unsigned short mWidth;      // +0x00
    unsigned short mHeight;     // +0x02
    unsigned short mWidth2;     // +0x04
    unsigned short mHeight2;    // +0x06
};

class cViewportInfo {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual cViewportExtent* GetExtent();        // 0x1c
};
cViewportInfo* GetViewportInfo();                // va 0067dd50

// ---------------------------------------------------------------------------
// Primary base of cGraphicsSystem; also carries the debug-draw entry point.
// ---------------------------------------------------------------------------
class cIGraphicsSystem {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual void ReleaseSelf();                  // 0x30
    void UpdateDebugDraw();                      // va 007a4e40 (cDebugDraw::Update)
};

class cContentValidationSummarizer {
public:
    virtual void v0();
};

// ---------------------------------------------------------------------------
// SP::cGraphicsSystem
// ---------------------------------------------------------------------------
class cGraphicsSystem : public cIGraphicsSystem, public cContentValidationSummarizer {
public:
    void*  mField08;                  // +0x08
    bool   mField0c;                  // +0x0c
    char   pad0d[3];                  // +0x0d
    cRenderService* mRenderer;        // +0x10
    void*  mField14;                  // +0x14
    cRenderTargetManager* mRTTManager;// +0x18
    void*  mField1c;                  // +0x1c
    void*  mField20;                  // +0x20
    void*  mField24;                  // +0x24
    void*  mField28;                  // +0x28
    void*  mField2c;                  // +0x2c
    void*  mField30;                  // +0x30
    void*  mField34;                  // +0x34
    cRenderService* mEffectsRenderer; // +0x38
    void*  mField3c;                  // +0x3c
    void*  mField40;                  // +0x40
    void*  mField44;                  // +0x44
    void*  mField48;                  // +0x48
    void*  mField4c;                  // +0x4c (retail ctor leaves this untouched)
    void*  mField50;                  // +0x50 (retail ctor leaves this untouched)

    cTextureHandle mSplatterTexture;          // +0x54
    cTextureHandle mAnimGifExportTexture;     // +0x58
    cTextureHandle mEditGifExportTexture;     // +0x5c
    cTextureHandle mBakeInfoTexture;          // +0x60
    cTextureHandle mNMapSpecTexture;          // +0x64
    cTextureHandle mAOTexture;                // +0x68
    cTextureHandle mFinalBakedTexture;        // +0x6c
    cTextureHandle mSmallFinalBakedTexture;   // +0x70
    cTextureHandle mShadowBlurTexture;        // +0x74
    cTextureHandle mShadowTexture;            // +0x78
    cTextureHandle mDepthTexture;             // +0x7c
    void*  mField80;                          // +0x80
    cTextureHandle mSnapshotTexture;          // +0x84
    void*  mField88;                          // +0x88
    cTextureHandle mBakeBuffers[2];           // +0x8c
    cTextureHandle mLargeThumbnailTexture;    // +0x94
    cTextureHandle mThumbnailBoundsTexture;   // +0x98
    void*  mBakeBufferRasters[4];             // +0x9c

    cRenderTargetRectID mFieldAc;             // +0xac
    cRenderTargetRectID mFieldB4;             // +0xb4
    cRenderTargetRectID mFieldBc;             // +0xbc
    cRenderTargetRectID mFieldC4;             // +0xc4
    int    mTextureFlags;                     // +0xcc (four one-byte dirty flags)
    cRenderTargetRectID mAOTextureRectID;           // +0xd0
    cRenderTargetRectID mSplatterTextureRectID;     // +0xd8
    cRenderTargetRectID mAnimGifExportRectID;       // +0xe0
    cRenderTargetRectID mEditGifExportRectID;       // +0xe8
    cRenderTargetRectID mBakeInfoRectID;            // +0xf0
    cRenderTargetRectID mNMapSpecRectID;            // +0xf8
    cRenderTargetRectID mFinalBakedRectID;          // +0x100
    cRenderTargetRectID mSmallFinalBakedRectID;     // +0x108
    cRenderTargetRectID mShadowBlurRectID;          // +0x110
    cRenderTargetRectID mShadowRectID;              // +0x118
    cRenderTargetRectID mField120;                  // +0x120
    cRenderTargetRectID mField128;                  // +0x128
    cRenderTargetRectID mDepthRectID;               // +0x130
    cRenderTargetRectID mSnapshotRectID;            // +0x138
    cRenderTargetRectID mField140;                  // +0x140
    cRenderTargetRectID mBakeBufferRectIDs[2];      // +0x148
    cRenderTargetRectID mLargeThumbnailRectID;      // +0x158
    cRenderTargetRectID mThumbnailBoundsRectID;     // +0x160

    bool   mField168;                 // +0x168
    bool   mField169;                 // +0x169
    bool   mField16a;                 // +0x16a
    char   pad16b;                    // +0x16b
    int    mField16c;                 // +0x16c
    unsigned short mField170;         // +0x170
    char   pad172[2];                 // +0x172
    float  mField174;                 // +0x174
    float  mField178;                 // +0x178
    float  mField17c;                 // +0x17c
    float  mField180;                 // +0x180
    float  mField184;                 // +0x184
    bool   mField188;                 // +0x188
    char   pad189[3];                 // +0x189
    int    mField18c;                 // +0x18c
    bool   mField190;                 // +0x190

    cGraphicsSystem();                                 // va 007a6010

    bool  InitSplatterTexture();                       // va 007a52f0
    bool  InitAnimGifExportTexture();                  // va 007a5370
    bool  InitEditGifExportTexture();                  // va 007a5410
    bool  InitAOTexture();                             // va 007a54b0
    bool  InitBakeInfoTexture();                       // va 007a5530
    bool  InitNMapSpecTexture();                       // va 007a55b0
    bool  InitFinalBakedTexture();                     // va 007a5630
    bool  InitSmallFinalBakedTexture();                // va 007a56b0
    bool  InitDepthTexture();                          // va 007a5730
    bool  InitShadowTexture();                         // va 007a57d0
    bool  InitShadowBlurTexture();                     // va 007a5860
    bool  InitSnapshotTexture();                       // va 007a5900
    bool  InitLargeThumbnailTexture();                 // va 007a5990
    bool  InitThumbnailBoundsTexture();                // va 007a5a20
    cTextureHandle* InitBakeBuffer(int index);         // va 007a5f70
    void  RecycleBakeBuffers();                        // va 007a5ef0
    void  UpdateRendering(int delta);                  // va 007a5290
    void  ReleaseGifExportTextures();                  // va 007a51d0
};

extern cDirectPropertyList* gAppProperties;   // va 015fd918

// ======================== render / export management =======================

// @ 0x007a51d0
void SP::cGraphicsSystem::ReleaseGifExportTextures()
{
    if (mAnimGifExportTexture.mpObject != 0) {
        mRTTManager->ReleaseRenderTarget(mAnimGifExportRectID.mPageID,
                                         mAnimGifExportRectID.mAllocID);
        mAnimGifExportTexture.Release();
    }
    if (mEditGifExportTexture.mpObject != 0) {
        mRTTManager->ReleaseRenderTarget(mEditGifExportRectID.mPageID,
                                         mEditGifExportRectID.mAllocID);
        mEditGifExportTexture.Release();
    }
    ReleaseSelf();
}

// @ 0x007a5290
void SP::cGraphicsSystem::UpdateRendering(int delta)
{
    if (mRenderer != 0)
        mRenderer->UpdateRenderer(delta);                 // 0x34
    if (mEffectsRenderer != 0)
        mEffectsRenderer->UpdateEffects(delta);           // 0x80
    if (mField188) {
        if (gAppProperties->GetDescription(0x64574ab))
            ((cIGraphicsSystem*)this)->UpdateDebugDraw();
    }
    mTextureFlags = 0x01010101;
}

// =========================== texture initialisers ==========================

// @ 0x007a52f0
bool SP::cGraphicsSystem::InitSplatterTexture()
{
    int dim = mField170;
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "SplatterRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mSplatterTexture.SetImageResource(image);
        mSplatterTextureRectID.mPageID = pageID;
        mSplatterTextureRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a5370
bool SP::cGraphicsSystem::InitAnimGifExportTexture()
{
    int w = gAppProperties->GetIntProperty(0x5893ed4);
    int h = gAppProperties->GetIntProperty(0x5893ee8);
    int size = h * w;
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, size, size, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "AnimGIFExportRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mAnimGifExportTexture.SetImageResource(image);
        mAnimGifExportRectID.mPageID = pageID;
        mAnimGifExportRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a5410
bool SP::cGraphicsSystem::InitEditGifExportTexture()
{
    int w = gAppProperties->GetIntProperty(0x5893ed4);
    int h = gAppProperties->GetIntProperty(0x5893ee8);
    int size = h * w;
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, size, size, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "EditGIFExportRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mEditGifExportTexture.SetImageResource(image);
        mEditGifExportRectID.mPageID = pageID;
        mEditGifExportRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a54b0
bool SP::cGraphicsSystem::InitAOTexture()
{
    int dim = mField170;
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xba595d5d, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "AORTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mAOTexture.SetImageResource(image);
        mAOTextureRectID.mPageID = pageID;
        mAOTextureRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a5530
bool SP::cGraphicsSystem::InitBakeInfoTexture()
{
    int dim = mField170;
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "BakeInfoRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mBakeInfoTexture.SetImageResource(image);
        mBakeInfoRectID.mPageID = pageID;
        mBakeInfoRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a55b0
bool SP::cGraphicsSystem::InitNMapSpecTexture()
{
    int dim = mField170;
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "NMapSpecRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mNMapSpecTexture.SetImageResource(image);
        mNMapSpecRectID.mPageID = pageID;
        mNMapSpecRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a5630
bool SP::cGraphicsSystem::InitFinalBakedTexture()
{
    int dim = mField170;
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "FinalBakedRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mFinalBakedTexture.SetImageResource(image);
        mFinalBakedRectID.mPageID = pageID;
        mFinalBakedRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a56b0
bool SP::cGraphicsSystem::InitSmallFinalBakedTexture()
{
    int dim = mField170 >> 1;
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "SmallFinalBakedRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mSmallFinalBakedTexture.SetImageResource(image);
        mSmallFinalBakedRectID.mPageID = pageID;
        mSmallFinalBakedRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a5730
bool SP::cGraphicsSystem::InitDepthTexture()
{
    cViewportExtent* extent = GetViewportInfo()->GetExtent();
    int width = extent->mWidth;
    int height = extent->mWidth2;
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, width, height, 0x15, 0, 0x9b304161, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "DepthTexture");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mDepthTexture.SetImageResource(image);
        mDepthRectID.mPageID = pageID;
        mDepthRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a57d0
bool SP::cGraphicsSystem::InitShadowTexture()
{
    GetViewportInfo()->GetExtent();
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, 0x200, 0x200, 0x15, 8, 0xf19d8d5, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "ShadowRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mShadowTexture.SetImageResource(image);
        mShadowRectID.mPageID = pageID;
        mShadowRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a5860
bool SP::cGraphicsSystem::InitShadowBlurTexture()
{
    cViewportExtent* extent = GetViewportInfo()->GetExtent();
    int width = extent->mWidth;
    int height = extent->mWidth2;
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, width, height, 0x15, 9, 0xfd9802c7, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "ShadowBlurTexture");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mShadowBlurTexture.SetImageResource(image);
        mShadowBlurRectID.mPageID = pageID;
        mShadowBlurRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a5900
bool SP::cGraphicsSystem::InitSnapshotTexture()
{
    cViewportExtent* extent = GetViewportInfo()->GetExtent();
    int width = (int)extent->mWidth | ((int)extent->mHeight << 16);
    int height = (int)extent->mWidth2 | ((int)extent->mHeight2 << 16);
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, width, height, 0x15, 9, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "CameraSnapshot");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mSnapshotTexture.SetImageResource(image);
        mSnapshotRectID.mPageID = pageID;
        mSnapshotRectID.mAllocID = allocID;
    }
    return mSnapshotTexture.mpObject != 0;
}

// @ 0x007a5990
bool SP::cGraphicsSystem::InitLargeThumbnailTexture()
{
    int dim = gAppProperties->GetIntProperty(0x8649077);
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "LargeThumbnailRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mLargeThumbnailTexture.SetImageResource(image);
        mLargeThumbnailRectID.mPageID = pageID;
        mLargeThumbnailRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a5a20
bool SP::cGraphicsSystem::InitThumbnailBoundsTexture()
{
    cRenderTargetRectID tmp;
    cRenderTargetRectID* rt =
        mRTTManager->CreateRenderTarget(&tmp, 0x40, 0x40, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "ThumbnailBoundsRect");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mThumbnailBoundsTexture.SetImageResource(image);
        mThumbnailBoundsRectID.mPageID = pageID;
        mThumbnailBoundsRectID.mAllocID = allocID;
        return true;
    }
    return false;
}

// @ 0x007a5ef0
void SP::cGraphicsSystem::RecycleBakeBuffers()
{
    for (int i = 0; i < 2; ++i) {
        if (mBakeBufferRasters[i] != 0) {
            mRTTManager->ReleaseRenderTarget(mBakeBufferRectIDs[i].mPageID,
                                             mBakeBufferRectIDs[i].mAllocID);
            if (mBakeBuffers[i].mpObject != 0)
                mBakeBuffers[i].Release();
        }
    }
}

// @ 0x007a5f70
SP::cTextureHandle* SP::cGraphicsSystem::InitBakeBuffer(int index)
{
    cTextureHandle* slot = &mBakeBuffers[index];
    if (slot->mpObject == 0) {
        int dim = mField170;
        cRenderTargetRectID tmp;
        cRenderTargetRectID* rt =
            mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
        int pageID = rt->mPageID;
        int allocID = rt->mAllocID;
        mRTTManager->SetRenderTargetName(pageID, allocID, "BakeBuffers");
        if (pageID != -1) {
            void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
            slot->SetImageResource(image);
            mBakeBufferRectIDs[index].mPageID = pageID;
            mBakeBufferRectIDs[index].mAllocID = allocID;
        }
    }
    return slot;
}

// @ 0x007a6010
SP::cGraphicsSystem::cGraphicsSystem()
{
    mField08 = 0;
    mField0c = false;
    mRenderer = 0;
    mField14 = 0;
    mRTTManager = 0;
    mField1c = 0;
    mField20 = 0;
    mField24 = 0;
    mField28 = 0;
    mField2c = 0;
    mField30 = 0;
    mField34 = 0;
    mEffectsRenderer = 0;
    mField3c = 0;
    mField40 = 0;
    mField44 = 0;
    mField48 = 0;
    // mField4c / mField50 are intentionally left untouched by the retail ctor.

    mSplatterTexture.mpObject = 0;
    mAnimGifExportTexture.mpObject = 0;
    mEditGifExportTexture.mpObject = 0;
    mBakeInfoTexture.mpObject = 0;
    mNMapSpecTexture.mpObject = 0;
    mAOTexture.mpObject = 0;
    mFinalBakedTexture.mpObject = 0;
    mSmallFinalBakedTexture.mpObject = 0;
    mShadowBlurTexture.mpObject = 0;
    mShadowTexture.mpObject = 0;
    mDepthTexture.mpObject = 0;
    mField80 = 0;
    mSnapshotTexture.mpObject = 0;
    mField88 = 0;
    mBakeBuffers[0].mpObject = 0;
    mBakeBuffers[1].mpObject = 0;
    mLargeThumbnailTexture.mpObject = 0;
    mThumbnailBoundsTexture.mpObject = 0;
    mBakeBufferRasters[0] = 0;
    mBakeBufferRasters[1] = 0;
    mBakeBufferRasters[2] = 0;
    mBakeBufferRasters[3] = 0;

    mFieldAc.mPageID = -1;      mFieldAc.mAllocID = -1;
    mFieldB4.mPageID = -1;      mFieldB4.mAllocID = -1;
    mFieldBc.mPageID = -1;      mFieldBc.mAllocID = -1;
    mFieldC4.mPageID = -1;      mFieldC4.mAllocID = -1;
    mAOTextureRectID.mPageID = -1;          mAOTextureRectID.mAllocID = -1;
    mSplatterTextureRectID.mPageID = -1;    mSplatterTextureRectID.mAllocID = -1;
    mAnimGifExportRectID.mPageID = -1;      mAnimGifExportRectID.mAllocID = -1;
    mEditGifExportRectID.mPageID = -1;      mEditGifExportRectID.mAllocID = -1;
    mBakeInfoRectID.mPageID = -1;           mBakeInfoRectID.mAllocID = -1;
    mNMapSpecRectID.mPageID = -1;           mNMapSpecRectID.mAllocID = -1;
    mFinalBakedRectID.mPageID = -1;         mFinalBakedRectID.mAllocID = -1;
    mSmallFinalBakedRectID.mPageID = -1;    mSmallFinalBakedRectID.mAllocID = -1;
    mShadowBlurRectID.mPageID = -1;         mShadowBlurRectID.mAllocID = -1;
    mShadowRectID.mPageID = -1;             mShadowRectID.mAllocID = -1;
    mField120.mPageID = -1;                 mField120.mAllocID = -1;
    mField128.mPageID = -1;                 mField128.mAllocID = -1;
    mDepthRectID.mPageID = -1;              mDepthRectID.mAllocID = -1;
    mSnapshotRectID.mPageID = -1;           mSnapshotRectID.mAllocID = -1;
    mField140.mPageID = -1;                 mField140.mAllocID = -1;
    mBakeBufferRectIDs[0].mPageID = -1;     mBakeBufferRectIDs[0].mAllocID = -1;
    mBakeBufferRectIDs[1].mPageID = -1;     mBakeBufferRectIDs[1].mAllocID = -1;
    mLargeThumbnailRectID.mPageID = -1;     mLargeThumbnailRectID.mAllocID = -1;
    mThumbnailBoundsRectID.mPageID = -1;    mThumbnailBoundsRectID.mAllocID = -1;

    mField168 = false;
    mField169 = false;
    mField16a = false;
    mField16c = -1;
    mField170 = 0x100;
    mField174 = 200.0f;
    mField178 = 1000.0f;
    mField17c = 50.0f;
    mField180 = 5000.0f;
    mField184 = 10.0f;
    mField188 = false;
    mField18c = 0;
    mField190 = false;

    mTextureFlags = 0x01010101;
}

}  // namespace SP