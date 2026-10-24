// SporeApp.exe slice s00e34290 -- SPUI swatch widgets / asset view (gold6, worker 36)

#include "types.h"

// ---------------------------------------------------------------------------
// shared interfaces
// ---------------------------------------------------------------------------

// Minimal reference-counted interface: slot 1 releases, slot 2 frees.
struct IRefCounted {
    virtual void     v00();                                 // +0x00
    virtual uint32_t Release();                             // +0x04
    virtual uint32_t v08();                                 // +0x08
    virtual void     v0c();
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();                                  // +0x18
    virtual void     v1c();
    virtual void     v20();                                  // +0x20
    virtual void     v24();                                  // +0x24
};

// Reference block behind the smart pointer held at cSPSwatchView+0x188.
struct RefBlock;

struct RefBlockVtbl {
    void   (*pAddRef)(RefBlock*);                           // +0x00
    void   (*pRelease)(RefBlock*);                          // +0x04
    void*  mpUnused08[0x5a];                                // +0x08 .. +0x16c
    void (__stdcall *pDestroy)(RefBlock*, bool bDelete);    // +0x170
};

struct RefBlock {
    RefBlockVtbl* mpVtbl;                                   // +0x00
    int32_t       mFlags;                                   // +0x04
    char          mPad08[0x38];                             // +0x08 .. +0x3f
    int32_t       mRefCount;                                // +0x40
};

// UTFWin-style window object (only the entry points this slice calls).
struct IWindow {
    virtual void     v00();                                 // +0x00
    virtual void     v04();                                 // +0x04
    virtual void     v08();                                 // +0x08
    virtual IWindow* v0c(uint32_t id);                      // +0x0c
    virtual void     v10();                                 // +0x10
    virtual void     v14();                                 // +0x14
    virtual void     v18();                                 // +0x18
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24(uint32_t a, uint32_t b);           // +0x24
    virtual void     v28();
    virtual void     v2c();
    virtual void     v30();
    virtual void     v34();
    virtual void     v38();
    virtual void     v3c();
    virtual void     v40();
    virtual void     v44();
    virtual void     v48();
    virtual void     v4c();
    virtual void     v50();
    virtual void     v54();
    virtual void     v58();
    virtual void     v5c();
    virtual void     v60();
    virtual void     v64();
    virtual void     v68();
    virtual void     v6c();
    virtual void     v70();
    virtual void     v74();
    virtual void     v78();
    virtual void     v7c();
    virtual void     v80();
    virtual void     v84();
    virtual void     v88();
    virtual void     v8c();
    virtual void     v90();
};

// ---- external free functions / methods ----
struct MessageServerT {
    virtual void     v00();                                 // +0x00
    virtual void     v04();
    virtual void     v08();
    virtual void     v0c();
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24();
    virtual void     v28();
    virtual void     v2c(void* pHandler, uint32_t msgId, uint32_t unused);  // +0x2c
};

MessageServerT* MessageServer();                            // 0x0067dcc0

struct cSPUIRolloverCivRelationship {
    void ShowRelationshipRollover(int32_t a, int32_t b, int32_t c);   // 0x00e2d6a0
};

// ---- layout keys ----
struct EAKey {
    uint32_t m0;
    uint32_t m4;
    uint32_t m8;

    EAKey() : m0(0), m4(0), m8(0) {}
    EAKey(uint32_t a, uint32_t b, uint32_t c) : m0(a), m4(b), m8(c) {}
};

struct cSPUILayout {
    virtual void v00();                                               // +0x00
    virtual void v04();
    virtual void v08();

    cSPUILayout* ctor();                                              // 0x00810000
    bool Init(const EAKey& key, bool flag, uint32_t group);           // 0x008120d0
    bool SetParentWin(IWindow* pParent, bool flag, uint32_t group);   // 0x008121b0
    void SetReloadCallback(void (*pCallback)(void*, cSPUILayout*), void* pContext);  // 0x00810090
};

// EA allocator entry point: size plus the fixed allocator tag and four defaults.
void* operator new(uint32_t cb, void* pAllocator, int32_t a, int32_t b, int32_t c, int32_t d);  // 0x00f473a0

// ---------------------------------------------------------------------------
// cToolButton -- the small buttons on the swatch strip
// ---------------------------------------------------------------------------
struct cToolButton {
    char     mPad00[0x1a];
    bool     mbActive;                                      // +0x1a
    uint32_t mToolId;                                       // +0x1c
    char     mPad20[1];
    bool     mbEnabled;                                     // +0x21

    bool SetTool(uint32_t toolId, uint32_t data);           // 0x00e34eb0
    void SetEnabled(bool enabled);                          // 0x00e34ea0
};

// ---------------------------------------------------------------------------
// cAssetView -- the sporepedia asset view embedded in this widget
// ---------------------------------------------------------------------------
struct cNounTag;

struct ViewRecord {                                         // at cAssetView+0x34
    uint32_t m00;
    uint32_t m04;
    uint32_t m08;
};

struct cNounTag {
    bool IsValid();                                         // 0x00b7d4f0
};

struct cRefHolder {
    uint32_t Release();                                     // 0x0066bf70
};

struct cAssetView {
    char     mPad00[0x18];
    cSPUIRolloverCivRelationship* mpRollover;               // +0x18
    char     mPad1c[0x0c];
    cRefHolder* mpHolder;                                   // +0x28
    char     mPad2c[0x08];
    ViewRecord mRecord;                                     // +0x34
    char     mPad40[0x0a];
    bool     mbRecordValid;                                 // +0x4a

    void RefreshRecord(uint32_t flags);                     // 0x00e34da0
    void RefreshSwatch();                                   // 0x00e34af0
    void ShowRelationship(int32_t a, int32_t b, bool show);  // 0x00e35290
};

cNounTag* __stdcall ResolveNounTag(ViewRecord* pRecord);    // 0x00b3d360

// ---------------------------------------------------------------------------
// cSPSwatchView -- the swatch widget itself (bases: tracer, value store, paint)
// ---------------------------------------------------------------------------
struct ITracerBase {
    virtual ~ITracerBase();                                 // +0x00
    virtual void     v00();
    virtual void     v04();
};

struct CVSBase {
    virtual void     v00();                                 // +0x00 (this+0x04)
    virtual void     Update(int32_t delta);                 // 0x005f6f40
    uint32_t         mValue;                                // +0x04
};

struct PaintBase {
    virtual void     v00();                                 // +0x00 (this+0x0c)
    virtual void     v04();
    virtual void     v08();
    virtual void     v0c();
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24();
};

struct cXform {
    void RotateZ(float angle);                              // 0x007d1ac0
    void Assign(const float* pMatrix);                      // 0x0041cb40
};

// The 0x118 creature/model handle used by Update.
struct cSPSwatchModel {
    char mPad00[0x08];
    void PreRotateY(float angle);                           // 0x004099b0
};

struct cModelSource {
    void* GetModel(uint32_t* pKey);                         // 0x00e20f10
};

struct cSPSwatch;

struct cSPSwatchView : ITracerBase, CVSBase, PaintBase {
    char         mPad10[0x108];                             // +0x10 .. +0x117
    void*        mpCreature;                                // +0x118
    char         mPad1c[0x60];                              // +0x11c .. +0x17b
    uint32_t     m17c;                                      // +0x17c (asset id triple)
    uint32_t     m180;                                      // +0x180
    uint32_t     m184;                                      // +0x184
    RefBlock*    mpSwatchRef;                               // +0x188
    IRefCounted* mpTarget;                                  // +0x18c
    IRefCounted* mpExtra;                                   // +0x190

    ~cSPSwatchView();                                       // 0x00e34290
    void Update(int32_t delta);                             // 0x00e34310
    void InitSwatch(const ViewRecord& key, const ViewRecord& outer,
                    uint32_t a, uint32_t b, uint32_t c);    // 0x00e34540
};

struct cSPSwatchAbstract {
    virtual void v00();                                     // +0x00
    virtual void v04();
};

struct cSPSwatch : cSPSwatchAbstract {
    char mPad04[0x114];                                     // +0x04 .. +0x117
    uint32_t m118;
    char mPad1c[0x70];
    uint32_t m188;
    char mPad8c[4];
    uint32_t m18c;
    char mPad90[4];
    uint32_t m190;
};

void __fastcall DestructSPSwatch(cSPSwatch* pThis);         // 0x005f6df0

// ---------------------------------------------------------------------------
// swatch view: asset record / layout plumbing
// ---------------------------------------------------------------------------
struct cAssetSwatchWidget {
    char              mPad00[0x10];
    cSPUILayout*      mpLayout;                             // +0x10
    IWindow*          mpParent;                             // +0x14
    char              mPad18[0x0c];
    void*             mpAsset;                              // +0x24
    char              mPad28[0x08];
    cSPSwatchView*    mpView;                               // +0x30
    ViewRecord*       mpRecordKey;                          // +0x34 -> record triple
    char              mPad38[0x08];
    uint32_t          m40;                                  // +0x40
    uint32_t          m44;                                  // +0x44

    void InitLayout();                                      // 0x00e34470
    void LoadLayout();                                      // 0x00e34020
    void CreateSwatch();                                    // 0x00e34af0
    bool HandleMessage();                                   // 0x00e34a00
    void HandleMessage2();                                  // 0x00e34bd0
};

void __fastcall LoadLayoutOfWidget(cAssetSwatchWidget* pThis);   // 0x00e34020
void ReloadAssetSwatch(void* pContext, cSPUILayout* pLayout);  // 0x00e34200
void* __fastcall SetupSwatchMessage(void* pMsg);            // 0x00401020
cSPSwatchView* __fastcall CtorSPSwatchView(cSPSwatchView* pThis);  // 0x00e34220
struct cSPSwatchManager {
    cSPSwatch* __fastcall CreateSwatch();                   // 0x005f0ca0
};

struct cSPUIMeter {
    virtual void v00();                                     // +0x00
    virtual void v04();
    void Shutdown(bool a);                                  // 0x00e06940
};

// ---------------------------------------------------------------------------
// cToolButton bodies
// ---------------------------------------------------------------------------

// @ 0x00e34ea0
void cToolButton::SetEnabled(bool enabled)
{
    mbEnabled = !enabled;
}

// @ 0x00e34eb0
bool cToolButton::SetTool(uint32_t toolId, uint32_t data)
{
    switch (toolId) {
    case 0x03e9a620:
        mbActive = true;
        mToolId = data;
        return true;
    case 0x03e9a625:
        mbActive = false;
        mToolId = 0;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// cAssetView bodies
// ---------------------------------------------------------------------------

// @ 0x00e34da0
void cAssetView::RefreshRecord(uint32_t flags)
{
    if (!mbRecordValid) {
        cNounTag* pTag = ResolveNounTag(&mRecord);
        mbRecordValid = pTag->IsValid();
        if (mbRecordValid)
            RefreshSwatch();
    }
    if (mpHolder)
        mpHolder->Release();
    (void)flags;
}

// @ 0x00e35290
void cAssetView::ShowRelationship(int32_t a, int32_t b, bool show)
{
    mpRollover->ShowRelationshipRollover(a, b, show == 0);
}

// ---------------------------------------------------------------------------
// cSPSwatchView bodies
// ---------------------------------------------------------------------------

// @ 0x00e34290
cSPSwatchView::~cSPSwatchView()
{
    if (mpExtra)
        mpExtra->Release();
    if (mpTarget)
        mpTarget->Release();
    if (mpSwatchRef) {
        int32_t count = mpSwatchRef->mRefCount;
        if (count > 1) {
            mpSwatchRef->mRefCount = count - 1;
        } else {
            mpSwatchRef->mpVtbl->pDestroy(mpSwatchRef, mpSwatchRef->mFlags >> 31);
        }
    }
}

// @ 0x00e34310
void cSPSwatchView::Update(int32_t delta)
{
    CVSBase::Update(delta);
    float angle = (float)delta / 1000.0f * 360.0f;
    cSPSwatchModel* pModel = (cSPSwatchModel*)mpCreature;
    if (pModel) {
        ((cModelSource*)pModel)->GetModel(0);
        pModel->PreRotateY(angle);
    }
    cSPSwatchModel* pSwatch = (cSPSwatchModel*)mpSwatchRef;
    if (pSwatch) {
        ((cModelSource*)pSwatch)->GetModel(0);
        pSwatch->PreRotateY(angle);
    }
    if (mpTarget) {
        uint32_t color[4];
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
        color[3] = 0x3f800000;
        cXform xform;
        xform.Assign((const float*)&color[0]);
        mpTarget->v20();
        xform.RotateZ(angle);
        mpTarget->v18();
    }
}

// @ 0x00e34540
// Retail is a 1207-byte setup routine: it copies the asset key triple, calls
// cSPSwatch::Init with seven ids, nudges the creature transform and drives the
// editor camera controller. Only that outline is reproduced here.
void cSPSwatchView::InitSwatch(const ViewRecord& key, const ViewRecord& outer,
                               uint32_t a, uint32_t b, uint32_t c)
{
    m17c = outer.m00;
    m180 = outer.m04;
    m184 = outer.m08;
    CVSBase::Update(0);
    (void)a;
    (void)b;
    (void)c;
    (void)key;
    if (mpCreature) {
        cSPSwatchModel* pModel = (cSPSwatchModel*)mpCreature;
        ((cModelSource*)pModel)->GetModel(0);
        pModel->PreRotateY(0.0f);
    }
}

// ---------------------------------------------------------------------------
// swatch widget bodies
// ---------------------------------------------------------------------------

// @ 0x00e34470
void cAssetSwatchWidget::InitLayout()
{
    cSPUILayout* pNew = (cSPUILayout*)operator new(0x18, (void*)0x013f6b3c, 0, 0, 0, 0);
    if (pNew)
        pNew = pNew->ctor();
    else
        pNew = 0;
    cSPUILayout* pOld = mpLayout;
    if (pNew != pOld) {
        if (pNew)
            pNew->v04();
        mpLayout = pNew;
        if (pOld)
            pOld->v08();
    }
    mpLayout->Init(EAKey(0xf0f17503, 0x0510a95b, 0x40464100), true, 0x05b598fa);
    mpLayout->SetParentWin(mpParent, true, 0x05b598fa);
    mpLayout->SetReloadCallback(ReloadAssetSwatch, this);
    LoadLayoutOfWidget(this);
}

// @ 0x00e34e00
// Retail reads its argument from esi (framereless callback); see nonmatching.txt.
void HandleAssetSwatchObject(void* pObject)
{
    if (!pObject)
        return;
}

// @ 0x00e34a00
bool cAssetSwatchWidget::HandleMessage()
{
    return mpAsset != 0;
}

// @ 0x00e34af0
void cAssetSwatchWidget::CreateSwatch()
{
    if (!mpAsset)
        return;
    ViewRecord key;
    key.m00 = mpRecordKey->m00;
    key.m04 = mpRecordKey->m04;
    key.m08 = mpRecordKey->m08;
    cNounTag* pTag = ResolveNounTag(&key);
    if (!pTag->IsValid())
        return;
}

// @ 0x00e34bd0
void cAssetSwatchWidget::HandleMessage2()
{
    (void)mpView;
}

// @ 0x00e34f40
void AssetSwatchUpdate(void* pWidget)
{
    (void)pWidget;
}

// ---------------------------------------------------------------------------
// swatch-strip service object: two vtables, meter + paint bases
// ---------------------------------------------------------------------------
// First base: vptr at +0x00, one dword payload at +0x04. Its destructor lives
// out of line (retail tail-jumps to 0x008014b0, another translation unit).
struct cSwatchStripBase {
    virtual ~cSwatchStripBase();                            // +0x00
    uint32_t mFlags;                                        // +0x04
};

// PaintSystem half: vptr at +0x08, inline virtual destructor.
struct PaintSystem {
    virtual ~PaintSystem() {}                               // +0x00 (this+0x08)
};

struct cSwatchStripService : cSwatchStripBase, PaintSystem {
    uint32_t     mPad0c;                                    // +0x0c
    IRefCounted* mpWindow;                                  // +0x10
    IRefCounted* mp10Ref;                                   // +0x14
    IRefCounted* mpSwatch;                                  // +0x18
    cSPUIMeter*  mpMeter;                                   // +0x1c

    ~cSwatchStripService();                                 // 0x00e351b0
};

// @ 0x00e351b0
cSwatchStripService::~cSwatchStripService()
{
    MessageServerT* pServer = MessageServer();
    if (pServer) {
        pServer->v2c((PaintSystem*)this, 0x03e9a620, 0xffffd8f1);
        pServer->v2c((PaintSystem*)this, 0x03e9a625, 0xffffd8f1);
    }
    mpSwatch->v24();
    if (mpSwatch) {
        IRefCounted* pSwatch = mpSwatch;
        mpSwatch = 0;
        pSwatch->Release();
    }
    if (mpMeter)
        mpMeter->Shutdown(true);
    if (mpMeter) {
        cSPUIMeter* pMeter = mpMeter;
        mpMeter = 0;
        pMeter->v04();
    }
    if (mpMeter)
        mpMeter->v04();
    if (mpSwatch)
        mpSwatch->Release();
    if (mp10Ref)
        mp10Ref->Release();
    if (mpWindow)
        mpWindow->Release();
}

