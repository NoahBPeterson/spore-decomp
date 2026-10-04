// slice s00573520
// cAppModeEditorBase methods; built /O2 /arch:SSE /fp:fast (see manifest).
#include <new>
#include <string.h>
#include <math.h>
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);

// ---------------------------------------------------------------------------
// Shared helpers
// ---------------------------------------------------------------------------
namespace EA {
namespace Random {
class RandomLinearCongruential {
public:
    uint32_t mnSeed;
    uint32_t RandomUint32Uniform(uint32_t n);
    double RandomDoubleUniform();
};
}
class Stopwatch {
public:
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    void Restart();
};
}
extern EA::Random::RandomLinearCongruential sMathRandom;


template <typename It, typename T> inline It find_u(It first, It last, const T& v) { for (; first != last; ++first) if (*first == v) break; return first; }
inline float RandomRangeClamped(float a, float b)
{
    const double lo = a;
    const double hi = b;
    double d = lo + (hi - lo) * sMathRandom.RandomDoubleUniform();
    if (d >= hi)
        d = hi;
    else if (d < lo)
        d = lo;
    return (float)d;
}

struct Vector2 { float x, y; };
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3 operator+(const Vector3& o) const { return Vector3(x + o.x, y + o.y, z + o.z); }
    Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
};
inline Vector3 operator*(float s, const Vector3& v) { return Vector3(s * v.x, s * v.y, s * v.z); }

struct BoundingBox { Vector3 mMin; Vector3 mMax; };
struct RectF {
    float mLeft, mTop, mRight, mBottom;
    RectF(const RectF& r) : mLeft(r.mLeft), mTop(r.mTop), mRight(r.mRight), mBottom(r.mBottom) {}
};

struct CollisionFilter {
    uint32_t mTypes[2];
    uint32_t mA, mB, mC;
    uint8_t mMode;
    bool mbFlag;
    CollisionFilter() { mTypes[0] = 0; mTypes[1] = 0; mA = 0; mB = 0; mC = 0; mbFlag = false; }
    void SetType(uint32_t i) { if (i < 64) mTypes[i >> 5] |= 1u << (i & 31); }
};
struct ICollider {
    PV8 PV
    virtual int Raycast(const Vector3* start, const Vector3* end, int a, Vector3* hit, Vector3* normal,
                        CollisionFilter* filter, int b, int c);   // +0x24
};
struct IModelManager {
    PV8 PV2
    virtual uint32_t GetTypeIndex(uint32_t id, int flags);   // +0x28
};

struct IObject {
    virtual void* Cast(uint32_t id);   // +0x00
    virtual int AddRef();              // +0x04
    virtual int Release();             // +0x08
};

struct IRefCount {
    virtual int AddRef();     // +0x00
    virtual int Release();    // +0x04
};

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

namespace SP {
struct cEditorBlock;

struct cSPEditorAnimatedEventInfo : IObject {
    uint32_t mData[11];
    cSPEditorAnimatedEventInfo();     // 0x59d960
    void MessagePost(uint32_t id, int a, int b, uint32_t target, int c, float scale, int d, int e, float f);
};

struct cSPEditorVehicleAbilities : IObject {
    struct Key { uint32_t a, b, c; };
    uint32_t mData[24];
    cSPEditorVehicleAbilities(Key key, uint32_t type, uint32_t id, int a, int b);
};

struct cBlockFlags {
    uint32_t mValue;
    inline bool Get(int n) const { return ((mValue >> n) & 1) != 0; }
};

struct cEditorBlock : IObject {
    char pad4[0x3ec - 4];
    struct cSPEditorHandle* mpHandle;     // +0x3ec
    char pad3f0[0xdc8 - 0x3f0];
    cBlockFlags mFlags;                    // +0xdc8

    bool CanShowAbilities();               // 0x44c030
    void GetKey(cSPEditorVehicleAbilities::Key* key, int a, int b);   // 0x438f20
    const BoundingBox& GetBBox(BoundingBox* tmp, int a, int b, int c); // 0x44ae00
    void SetSelected(int);                 // 0x43a830
    void OnDeselect();                     // 0x43e2b0
    uint32_t GetHandleIndex(struct cSPEditorHandle* h);   // 0x43c3d0
    void SetHandleState(uint32_t idx, int a);             // 0x43e7e0
    void SetActiveHandle(uint32_t idx);                   // 0x43e760
};

struct cSPEditorHandle {
    virtual int AddRef();                         // +0x00
    virtual int Release();                        // +0x04
    PV
    virtual cSPEditorHandle* Cast(uint32_t id);   // +0x0c
    virtual uint32_t GetType();                   // +0x10
    PV4 PV2 PV
    virtual void SetState(int state, int b);      // +0x30
    cEditorBlock* GetBlock();                     // 0x47e6c0
    int IsLocked();                               // 0x47ec20
};
struct cSPEditorHandleDeform : cSPEditorHandle {};

struct cSPUIPropertyLayout {
    void Setup(cSPEditorVehicleAbilities::Key* key, IObject* abilities, struct IOwner* owner, int a, int b, int c);   // 0x5ed750
    void SetMode(int m);                          // 0x5ed320
    void SetPositionAndOffset(float x, float y, float w, float h);
    void Hide();                                  // 0x5ed6c0
};
struct cPropertyLayoutMgr { cSPUIPropertyLayout* GetLayout(); };   // 0x801920
cPropertyLayoutMgr* PropertyLayoutMgr();                          // 0x401020

struct IWindow {
    PV8 PV4 PV
    virtual const RectF& GetArea();               // +0x34
};
struct IWindowManager {
    PV
    virtual IWindow* GetMainWindow();             // +0x04
};
IWindowManager* WindowManager();

struct cViewer { void ScreenToWorld(float x, float y, Vector3* nearPt, Vector3* farPt); };   // 0x7c4510
struct IApp {
    PV16 PV4 PV2
    virtual cViewer* GetViewer();                 // +0x58
};
IApp* App();
IModelManager* ModelManager();

struct IMessageServer;
struct IMessageListener { virtual bool HandleMessage(uint32_t id, void* msg); };
struct IMessageServer {
    PV4 PV
    virtual void PostMSG(uint32_t id, void* data, int flags);   // +0x14
    PV2 PV
    virtual void AddHandler(IMessageListener* h, uint32_t id);   // +0x24
};
IMessageServer* MessageServer();

struct HandlerRegistration {
    IMessageServer* mpServer;
    IMessageListener* mpHandler;
    const uint32_t* mpIds;
    uint32_t mnCount;
    int mnPriority;
    inline void Register(IMessageServer* server, IMessageListener* handler, const uint32_t* ids, uint32_t count) {
        mpServer = server;
        mpHandler = handler;
        mpIds = ids;
        mnCount = count;
        mnPriority = 0;
        if (server && handler)
            for (uint32_t i = 0; i < count; ++i)
                server->AddHandler(handler, ids[i]);
    }
};

struct IPlayMode {
    PV4 PV2
    virtual bool OnMouseMove(float x, float y, uint32_t state);   // +0x18
};
struct ISkinManager {
    PV4 PV2 PV
    virtual bool OnMouseMove(float x, float y, uint32_t state);   // +0x1c
    PV2
    virtual cEditorBlock* GetBlock();                             // +0x28
};
struct IOwner {
    PV
    virtual uint32_t GetId(int);                                  // +0x04
    virtual void SetKey(cSPEditorVehicleAbilities::Key* key);     // +0x08
};
struct IAppModeCheck {
    PV8 PV
    virtual bool IsActive();                                      // +0x24
};
IAppModeCheck* GameModeCheck();                                   // 0x607a60

struct cPaletteUI {
    bool IsActive();                 // 0x5dc450
    void SetVisible(bool b);         // 0x5dd090
    void Refresh(bool b, int c);     // 0x5de690
};
struct cUIManager { void SetMode(bool a, int b); };   // 0x67c420
cUIManager* UIManager();                             // 0x67cac0

struct cModel { char pad0[0xc]; uint32_t mKey[3]; char pad18[0x58 - 0x18]; uint32_t mType; void SetLocked(bool); void SetDirty(int); };   // 0x4adba0 / 0x4adfc0
struct cPartsPalette { void Refresh(int a, int b); void Update(); };   // 0x43cfc0 / 0x43cad0
struct cBlockRef {
    cEditorBlock* mpObject;
    cBlockRef& operator=(cEditorBlock* p);    // 0x4b09b0
};
struct cHint { void Show(); };              // 0x5cc690
struct cSymmetry { bool IsReady(); };       // 0x5ca920
struct cUndo { bool Raycast(int a, Vector3 origin, Vector3 dir, Vector3* hitPos, Vector3* hitNormal, int b, int c); };   // 0x4c4a30
struct cLimitsData { char pad0[0x6d]; bool mbOverLimit; };
struct cAssetMgr { IObject* Find(uint32_t key, int flags); };   // 0x45ae10
cAssetMgr* AssetManager();                                     // 0x401050
struct cRolloverInfo { char pad0[0x144]; uint32_t mId; };
struct cEditorState {
    char pad0[8];
    uint32_t mOwnerId;      // +0x08
    int mEditorMode;        // +0x0c
    uint32_t mRolloverId;   // +0x10
    bool mbFlagA;           // +0x14
    bool mbFlagB;           // +0x15
};
struct EffectEntry;
struct EffectEntry {        // 0x30 bytes
    uint32_t mId;
    float mDelay;           // +0x04
    float mSize;            // +0x08
    char pad0c[0x1a - 0x0c];
    bool mbActive;          // +0x1a
    bool mbScaleA;          // +0x1b
    bool mbScaleB;          // +0x1c
    char pad1d[0x20 - 0x1d];
    float mBaseSize;        // +0x20
    float mScale;           // +0x24
    char pad28[8];
};

bool __cdecl IsSameAssembly(cEditorBlock* a, cEditorBlock* b);   // 0x4a60a0
bool __cdecl IsRootBlock(cEditorBlock* b);                       // 0x4a2060
void __cdecl PlayEditorEvent(uint32_t id);                       // 0x4a88d0
void __cdecl ProjectToScreen(const Vector3& pt, float& x, float& y);   // 0x4a3760
namespace cSPUISpace { void KillSetiEffects(uint32_t id, void* owner); }
cSPEditorHandleDeform* __cdecl interface_cast_deform(AutoRefCount<cSPEditorHandle>* p);   // 0x572770
}
void __cdecl PostSoundMessage(const void* obj, uint32_t value);   // 0x572020

namespace SP {
struct cAppModeBase0 {
    virtual ~cAppModeBase0();
    char pad04[0xc];
};

class cAppModeEditorBase : public cAppModeBase0, public IMessageListener {
public:
    char pad14[0x28 - 0x14];
    float mMouseX;                   // +0x28
    float mMouseY;                   // +0x2c
    uint32_t mMouseState;            // +0x30
    int mMouseButton;                // +0x34
    bool mbMouseMoved;               // +0x38
    char pad39[3];
    uint32_t mStateFlags;            // +0x3c
    char pad40[0x70 - 0x40];
    float mHintTimer;                // +0x70
    char pad74[4];
    cPaletteUI* mpPalette;           // +0x78
    IPlayMode* mpPlayMode;           // +0x7c
    char pad80[4];
    ICollider* mpCollider;           // +0x84
    char pad88[0x98 - 0x88];
    cModel* mpModel;                 // +0x98
    char pad9c[0xc0 - 0x9c];
    int mMouseDownX;                 // +0xc0
    int mMouseDownY;                 // +0xc4
    char padc8[4];
    cBlockRef mActiveBlock;          // +0xcc
    cBlockRef mBlockRefD0;           // +0xd0
    cPartsPalette* mpPartsPalette;   // +0xd4
    char padd8[0xe4 - 0xd8];
    cSPEditorHandle* mpRolloverHandle;   // +0xe4
    char pade8[0xf4 - 0xe8];
    cSPEditorHandle* mpPendingHandle;    // +0xf4
    char padf8[0x140 - 0xf8];
    bool mbHandleSnap;               // +0x140
    bool mbDeformActive;             // +0x141
    char pad142[0x148 - 0x142];
    ISkinManager* mpSkinManager;     // +0x148
    char pad14c[4];
    cUndo* mpUndo;                   // +0x150
    char pad154[0x1a0 - 0x154];
    int mbHasAsset;                  // +0x1a0
    char pad1a4[0x1cc - 0x1a4];
    cLimitsData* mpLimits;           // +0x1cc
    char pad1d0[0x20c - 0x1d0];
    uint16_t mLayoutFlags;           // +0x20c
    char pad20e[0x2a0 - 0x20e];
    cRolloverInfo* mpRolloverInfo;   // +0x2a0
    char pad2a4[0x2b3 - 0x2a4];
    bool mbSkipMouseMove;            // +0x2b3
    bool mbClickCandidate;           // +0x2b4
    char pad2b5[0x2f1 - 0x2b5];
    bool mbHideRollover;             // +0x2f1
    char pad2f2[0x31c - 0x2f2];
    int mEditorMode;                 // +0x31c
    uint32_t* mIdsBegin;             // +0x320
    uint32_t* mIdsEnd;               // +0x324
    char pad328[0x36c - 0x328];
    EffectEntry* mEffectsBegin;      // +0x36c
    EffectEntry* mEffectsEnd;        // +0x370
    char pad374[0x385 - 0x374];
    bool mbCursorSet;                // +0x385
    char pad386[0x397 - 0x386];
    bool mbInputLocked;              // +0x397
    bool mbHasActiveBlock;           // +0x398
    char pad399[0x3b0 - 0x399];
    int mActiveHandle;               // +0x3b0
    int mLastHandle;                 // +0x3b4
    char pad3b8[0x3c4 - 0x3b8];
    cSymmetry* mpSymmetry;           // +0x3c4
    char pad3c8[0x434 - 0x3c8];
    IOwner* mpOwner;                 // +0x434
    char pad438[0x470 - 0x438];
    bool mbModelLocked;              // +0x470
    char pad471[0x498 - 0x471];
    cHint* mpHint;                   // +0x498
    char pad49c[0x4b2 - 0x49c];
    bool mbFlag4B2;                  // +0x4b2
    bool mbFlag4B3;                  // +0x4b3
    char pad4b4[0x5a8 - 0x4b4];
    EA::Stopwatch mStopwatch;        // +0x5a8
    char pad5c0[0x5e8 - 0x5c0];
    HandlerRegistration mRegistration;   // +0x5e8

    inline void PostDone(void* data) { MessageServer()->PostMSG(0x73e46f6, data, 0); }
    inline void PostModelChanged(cModel* model) { MessageServer()->PostMSG(0x73e46f6, model->mKey, 0); }
    void ShowBlockAbilities(cEditorBlock* block);
    void SetModelLocked(bool locked);
    bool OnMouseMove(float x, float y, uint32_t state);
    bool IsOverLimit();
    void UpdateHint();
    cEditorBlock* GetSelectableBlock();
    bool IsMousedOverModel(float x, float y);
    void SetActiveBlock(cEditorBlock* block, int handle);
    void SetRolloverHandle(cSPEditorHandle* handle, int unused);
    void SetAsset(uint32_t key);
    void SetPaletteVisible(bool visible);
    void OnEnter();
    void GetState(cEditorState* state);
    bool HasId(uint32_t id);
    void CreateEffects(uint32_t type, int param, float scale, float bonus);
    bool HasEffect(uint32_t id);
};

// @ 0x00573520
void cAppModeEditorBase::ShowBlockAbilities(cEditorBlock* block)
{
    if (block && mpOwner && !block->mFlags.Get(7) && !block->mFlags.Get(11) && !block->mFlags.Get(1) &&
        block->CanShowAbilities()) {
        cSPEditorVehicleAbilities::Key key;
        mActiveBlock.mpObject->GetKey(&key, -1, 0);
        mpOwner->SetKey(&key);
        cSPUIPropertyLayout* layout = PropertyLayoutMgr()->GetLayout();
        if (layout) {
            IObject* abilities = new("Editor", 0, 0, 0, 0) cSPEditorVehicleAbilities(key, mpModel->mType, 0x14880158, 0, 1);
            if (abilities)
                abilities->AddRef();
            layout->Setup(&key, abilities, mpOwner, mLayoutFlags, 0, 1);
            layout->SetMode(2);
            RectF area = WindowManager()->GetMainWindow()->GetArea();
            cEditorBlock* active = mActiveBlock.mpObject;
            BoundingBox tmp;
            const BoundingBox& bbox = active->GetBBox(&tmp, 0, 0, 0);
            Vector3 center = (bbox.mMax + bbox.mMin) * 0.5f;
            float screenX, screenY;
            ProjectToScreen(center, screenX, screenY);
            layout->SetPositionAndOffset(screenX, screenY, (area.mRight - area.mLeft) * 0.025f, (area.mBottom - area.mTop) * 0.0f);
            if (abilities)
                abilities->Release();
        }
    } else {
        cSPUIPropertyLayout* layout = PropertyLayoutMgr()->GetLayout();
        if (layout)
            layout->Hide();
    }
}

// @ 0x00573780
void cAppModeEditorBase::SetModelLocked(bool locked)
{
    if (locked != mbModelLocked) {
        mbModelLocked = locked;
        if (mpModel)
            mpModel->SetLocked(locked);
        if (!mpSkinManager && mpPartsPalette) {
            mpPartsPalette->Refresh(0, 1);
            mpPartsPalette->Update();
        }
    }
}

// @ 0x005737d0  (/arch:SSE /fp:fast)
bool cAppModeEditorBase::OnMouseMove(float x, float y, uint32_t state)
{
    if (mbInputLocked)
        return false;
    mMouseX = x;
    mMouseY = y;
    mMouseState = state;
    mbMouseMoved = true;
    if (mbSkipMouseMove) {
        mbSkipMouseMove = false;
        return true;
    }
    if (mEditorMode == 2 && (state & 0x38)) {
        mpPlayMode->OnMouseMove(x, y, state);
        return false;
    }
    if (mMouseButton == 0x3e9 || mMouseButton == 0x3ea || (mMouseButton == 0x3e8 && !mpSkinManager)) {
        if (fabs(x - mMouseDownX) > 3.0f || fabs(y - mMouseDownY) > 3.0f)
            mbClickCandidate = false;
        return false;
    }
    switch (mEditorMode) {
    case 0:
        if (mpSkinManager) {
            bool result = mpSkinManager->OnMouseMove(x, y, state);
            mBlockRefD0 = mpSkinManager->GetBlock();
            mpModel->SetDirty(1);
            return result;
        }
        break;
    case 2:
        mpPlayMode->OnMouseMove(x, y, state);
        return true;
    }
    return true;
}

// @ 0x00573950
bool cAppModeEditorBase::IsOverLimit()
{
    if (mpLimits)
        return mpLimits->mbOverLimit;
    return false;
}

// @ 0x00573970  (/arch:SSE /fp:fast)
void cAppModeEditorBase::UpdateHint()
{
    if (mbCursorSet && mHintTimer == 0.0f) {
        cSPEditorAnimatedEventInfo* msg = new("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo();
        if (msg)
            msg->AddRef();
        msg->MessagePost(0x6581b78e, 0, 0, 0, 0, 0.0f, 0, -1, 1.0f);
        mHintTimer = 250.0f;
        if (msg)
            msg->Release();
    }
}

// @ 0x00573a10
cEditorBlock* cAppModeEditorBase::GetSelectableBlock()
{
    cEditorBlock* b = mActiveBlock.mpObject;
    if (!b) {
        if (!mpRolloverHandle)
            return 0;
        cEditorBlock* r = mpRolloverHandle->GetBlock();
        if (!r || r->mpHandle != mpRolloverHandle)
            return 0;
        b = r;
    }
    return b->mFlags.Get(7) ? 0 : b;
}

// @ 0x00573a60  (/arch:SSE /fp:fast)
bool cAppModeEditorBase::IsMousedOverModel(float x, float y)
{
    Vector3 nearPt, farPt;
    App()->GetViewer()->ScreenToWorld(x, y, &nearPt, &farPt);
    cUndo* undo = mpUndo;
    if (undo) {
        Vector3 dir = farPt - nearPt;
        const float len = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + 1e-8f);
        const float inv = 1.0f / len;
        Vector3 hitPos, hitNormal;
        if (undo->Raycast(1, nearPt, inv * dir, &hitPos, &hitNormal, 0, 1))
            return true;
    }
    {
        CollisionFilter filter;
        filter.mMode = 4;
        filter.mbFlag = true;
        filter.SetType(ModelManager()->GetTypeIndex(0x9138fd8d, 0));
        if (mpCollider->Raycast(&nearPt, &farPt, 0, 0, 0, &filter, 0, 0))
            return true;
        return false;
    }
}

// @ 0x00573c00
void cAppModeEditorBase::SetActiveBlock(cEditorBlock* block, int handle)
{
    cEditorBlock* const old = mActiveBlock.mpObject;
    if (block != old || (block && handle != mActiveHandle)) {
        mActiveHandle = handle;
        mLastHandle = handle;
        if (old != block) {
            if (old) {
                const bool differs = !IsSameAssembly(block, old);
                if (mpRolloverHandle && differs)
                    IsSameAssembly(mpRolloverHandle->GetBlock(), mActiveBlock.mpObject);
                mActiveBlock.mpObject->SetSelected(0);
            }
            if (!block) {
                if (mActiveBlock.mpObject->mFlags.Get(3))
                    mActiveBlock.mpObject->OnDeselect();
                if (mActiveBlock.mpObject) {
                    cEditorBlock* p = mActiveBlock.mpObject;
                    mActiveBlock.mpObject = 0;
                    p->Release();
                }
                if (mpHint)
                    mpHint->Show();
            } else if (!block->mFlags.Get(1)) {
                mActiveBlock = block;
                if (!IsRootBlock(block) && mpHint)
                    mpHint->Show();
                bool activate;
                if (mEditorMode == 1)
                    activate = mpSymmetry && mpSymmetry->IsReady();
                else
                    activate = !mActiveBlock.mpObject->mFlags.Get(11) || !mActiveBlock.mpObject->mFlags.Get(10);
                if (activate) {
                    PlayEditorEvent(0xbb58117e);
                    mActiveBlock.mpObject->SetSelected(1);
                }
            }
            if (mEditorMode == 0 && (mStateFlags & 0x100))
                ShowBlockAbilities(mActiveBlock.mpObject);
        }
    }
    mbHasActiveBlock = mActiveBlock.mpObject != 0;
}

// @ 0x00573d70
void cAppModeEditorBase::SetRolloverHandle(cSPEditorHandle* handle, int unused)
{
    if (!handle && !mbHandleSnap)
        mbHandleSnap = true;
    if (handle == mpRolloverHandle && (!mpRolloverHandle || !mpRolloverHandle->IsLocked()))
        return;
    if (mpPendingHandle && mpPendingHandle != handle) {
        if (!mbHandleSnap)
            mbHandleSnap = true;
        mpPendingHandle = 0;
    }
    if (mpRolloverHandle == handle)
        return;
    if (handle) {
        cEditorBlock* b = handle->GetBlock();
        if (b && b->mFlags.Get(11))
            mbHandleSnap = false;
    }
    if (mpRolloverHandle) {
        mpRolloverHandle->SetState(3, 1);
        if (mbDeformActive) {
            if (mpRolloverHandle) {
                cSPEditorHandle* deform = mpRolloverHandle->Cast(0x50a993c);
                if (deform && deform->GetBlock()) {
                    cEditorBlock* b = deform->GetBlock();
                    b->SetHandleState(b->GetHandleIndex(deform), 1);
                }
            }
            mbDeformActive = false;
        }
    }
    cSPEditorHandle* const old = mpRolloverHandle;
    if (handle != old) {
        if (handle)
            handle->AddRef();
        mpRolloverHandle = handle;
        if (old)
            old->Release();
    }
    if (mpRolloverHandle) {
        cSPUISpace::KillSetiEffects(0xd2cfe2ad, this);
        SetActiveBlock(0, -1);
        mpRolloverHandle->SetState(0, 1);
        if (mpRolloverHandle->GetType() == 0x50a993c && mbHandleSnap) {
            cSPEditorHandleDeform* deform = interface_cast_deform((AutoRefCount<cSPEditorHandle>*)&mpRolloverHandle);
            cEditorBlock* deformBlock = deform->GetBlock();
            cSPEditorHandle* rollover = mpRolloverHandle;
            rollover->GetBlock()->SetActiveHandle(deformBlock->GetHandleIndex(deform));
            mbDeformActive = true;
        }
    } else {
        PostSoundMessage(this, 0);
    }
}

// @ 0x00573f20
void cAppModeEditorBase::SetAsset(uint32_t key)
{
    if (key) {
        IRefCount* asset = (IRefCount*)AssetManager()->Find(key, 1);
        if (asset) {
            asset->AddRef();
            mbHasAsset = 1;
            asset->Release();
            return;
        }
    }
    mbHasAsset = 0;
}

// @ 0x00573f70
void cAppModeEditorBase::SetPaletteVisible(bool visible)
{
    if (mpPalette->IsActive() != visible) {
        mpPalette->SetVisible(visible);
        mpPalette->Refresh(visible, 1);
    }
    UIManager()->SetMode(visible, 1);
}

static const uint32_t kEditorMessageIds[] = { 0x68cd252 };

// @ 0x00573fb0
void cAppModeEditorBase::OnEnter()
{
    if (GameModeCheck()->IsActive())
        return;
    mRegistration.Register(MessageServer(), this, kEditorMessageIds, 1);
    PostModelChanged(mpModel);
    SetPaletteVisible(false);
    mStopwatch.Restart();
}

// @ 0x00574080
void cAppModeEditorBase::GetState(cEditorState* state)
{
    if (state) {
        state->mOwnerId = mpOwner->GetId(0);
        state->mEditorMode = mEditorMode;
        state->mRolloverId = (mpRolloverInfo && !mbHideRollover) ? mpRolloverInfo->mId : 0;
        state->mbFlagA = mbFlag4B2;
        state->mbFlagB = mbFlag4B3;
    }
}

// @ 0x005740e0
bool cAppModeEditorBase::HasId(uint32_t id) { uint32_t* end = mIdsEnd; return find_u(mIdsBegin, end, id) != end; }

// @ 0x00574110  (/arch:SSE /fp:fast)
void cAppModeEditorBase::CreateEffects(uint32_t type, int param, float scale, float bonus)
{
    const int count = mEffectsEnd - mEffectsBegin;
    const int special = sMathRandom.RandomUint32Uniform(count - 1);
    float bigSize = 0.0f;
    uint32_t lastType = 0xffffffff;
    const uint32_t requestedType = type;
    for (int i = 0; i < count; ++i) {
        cSPEditorAnimatedEventInfo* msg = new("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo();
        if (msg)
            msg->AddRef();
        float size;
        if (count >= 3 && i == special) {
            size = RandomRangeClamped(4.0f, 5.5f);
            bigSize = size;
        } else
            size = RandomRangeClamped(1.75f, 2.3f);
        switch (type) {
        case 0x43773b7b:
        case 0x6035c10:
        case 0x22b31636:
        case 0x622c20c4:
        case 0xe646113d:
        case 0xe7782027:
            size += 0.5f;
            break;
        case 0x4878ee8:
            size += bonus;
            break;
        }
        if (requestedType == 0x70842ef6) {
            do {
                switch (sMathRandom.RandomUint32Uniform(6)) {
                case 0: type = 0x70842ef6; break;
                case 1: type = 0x6820bfd9; break;
                case 2: type = 0xeef6cd0; break;
                case 3: type = 0x4f21fc3b; break;
                case 4: type = 0xb3a731ca; break;
                case 5: type = 0xf10ff9fd; break;
                }
            } while (type == lastType);
            lastType = type;
        }
        if (type == 0x8b2f58fe) {
            mEffectsBegin[i].mbScaleA = true;
            mEffectsBegin[i].mScale = size;
        } else if (type == 0x5c4d694c) {
            mEffectsBegin[i].mbScaleB = true;
            mEffectsBegin[i].mScale = size;
        } else
            msg->MessagePost(type, 0, 0, mEffectsBegin[i].mId, 1, size, 0, param, scale);
        mEffectsBegin[i].mDelay = 0.0f;
        mEffectsBegin[i].mSize = size;
        mEffectsBegin[i].mBaseSize = size;
        if (count >= 3)
            mEffectsBegin[i].mSize = bigSize;
        float& sizeRef = mEffectsBegin[i].mSize;
        sizeRef += RandomRangeClamped(1.0f, 4.0f);
        mEffectsBegin[i].mbActive = true;
        if (msg)
            msg->Release();
    }
}

// @ 0x00574460
bool cAppModeEditorBase::HasEffect(uint32_t id)
{
    const int count = mEffectsEnd - mEffectsBegin;
    for (int i = 0; i < count; ++i) {
        if (mEffectsBegin[i].mId == id)
            return true;
    }
    return false;
}
}

