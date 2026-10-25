// src/game/SPGonzago/SPOrnamentView.cpp -- migrated from slice(s) s00e8e0d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPOrnamentView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameDataView.h"
#include "SP/cModelInstance.h"
#include "SP/cSpatialObject.h"
#include <math.h>
#include <string.h>

// ---- items of slice s00e8e0d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned int, void* p) throw() { return p; }
void* __cdecl operator_new(unsigned size, const char* file, int a, int b, int c, int d);  // 0xf473a0
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct cSPTransform_s00e8_e0d0;
struct IRefCounted {
    virtual void v00();
    virtual void Release();                // +0x04
};
template <class T> struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    void Reset()
    {
        if (mpObject) {
            T* const pOld = mpObject;
            mpObject = 0;
            pOld->Release();
        }
    }
};
struct cSPUIMeter : IRefCounted {
    void Shutdown(bool immediate);         // 0xe06940
};
struct cModelKey {
    uint32_t mType;                        // +0x00
    uint32_t mGroup;                       // +0x04
    uint32_t mInstance;                    // +0x08
};
struct cGonzagoModel {                     // model attachment at +0x34 of a sim object
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
    virtual bool IsReady();                         // +0x90
    virtual uint32_t v94();
    virtual Vector3* GetModelWorld(const char* name);   // +0x98
virtual void v9c();
virtual void va0();
    virtual void RefreshModelWorld();                // +0xa4
    virtual void* GetModel();                        // +0xac
};
struct cSelection {                        // selection helper embedded at +0x70
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual const Vector3& GetPosition();            // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual void SetHighlightRadius(float radius);   // +0x70
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
    virtual void* GetHighlightObject();              // +0xac
};
struct cModelInstance {                    // renderable instance a view owns
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
    virtual void v30();
    void SetTransform(const cSPTransform_s00e8_e0d0& transform);    // render transform lives at +8
    uint32_t mDrawFlags[8];                // +0x44 bit array (32..63)
};
struct cSimulatorObject {                  // the simulation side a view drives
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cSimulatorObject* GetObjectById(uint32_t id);   // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual uint32_t GetId();                                // +0x20
virtual void v24();
virtual void v28();
virtual void v2c();
    virtual void v30();

    uint8_t pad04[0x34 - 0x04];
    cGonzagoModel mModel;                  // +0x34
    uint8_t pad34[0x70 - (0x34 + sizeof(cGonzagoModel))];
    cSelection mSelection;                 // +0x70
    uint8_t pad70[0x84 - (0x70 + sizeof(cSelection))];
    uint32_t mFlags;                       // +0x84
    uint8_t pad88[0xa9 - 0x88];
    bool mbReady;                          // +0xa9
    uint8_t padAA[0xdf - 0xaa];
    bool mbHighlighted;                    // +0xdf
    uint8_t padE0[0x108 - 0xe0];
    int mState;                            // +0x108
    int mLevel;                            // +0x110
    uint8_t pad114[0x120 - 0x114];
    bool mbModelDirty;                     // +0x120
    uint8_t pad121[0x1e8 - 0x121];
    int mEffectKind;                       // +0x1e8
    bool mbEffectPending;                  // +0x1ec
    uint8_t pad1ED[0x1f4 - 0x1ed];
    void* mpToolData;                      // +0x1f4
    uint8_t pad1F8[0x220 - 0x1f8];
    float mEffectScale;                    // +0x220
    uint8_t pad224[0x238 - 0x224];
    float mHighlightMin;                   // +0x238
    float mHighlightGrow;                  // +0x23c
    float mHighlightShrink;                // +0x240
    float mHighlightNear;                  // +0x244
    float mHighlightFar;                   // +0x248

    void SetupNestModelKey();              // 0xe8df50
    void ShowTooltip(bool canMine, void* a);   // 0xc3f8b0
};
struct cSpatialObject {                    // the game side a view is attached to
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cSimulatorObject* GetSimObject(uint32_t id);     // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual uint32_t GetId();                                // +0x20
    virtual bool IsHighlighted();                            // +0x24
    virtual void v28();
    virtual const Vector3& GetPosition();                    // +0x2c
    virtual const void* GetOrientation();                    // +0x30
    virtual float GetScale();                                // +0x34
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
    virtual int GetKind();                                   // +0x60
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual uint32_t GetModelKeyId();                        // +0x70
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
    virtual void* GetHighlightedModel();                     // +0xac
virtual void vb0();
virtual void vb4();
    virtual cSimulatorObject* GetInteractableObject(uint32_t id);    // +0xb8

    bool mIsSelected;                      // +0x2c? (scene flags live after the vftable)
};
struct cSPTransform_s00e8_e0d0 {                      // render transform handed to an effect
    uint16_t mMask;                        // +0x00
    uint16_t mOrientationMask;             // +0x02
    Vector3 mPosition;                     // +0x04
    Vector3 mOrientation;                  // +0x10
    float mScale;                          // +0x1c
    float mBasis[9];                       // +0x20 (optional 3x3 basis)
};
struct cGameDataView {
    virtual void v00();                    // +0x00
    virtual void Release();                // +0x04
    virtual void v08();                    // +0x08
    virtual cSpatialObject* GetOwner();    // +0x0c
    virtual void SetVisible(int visible);  // +0x10
    virtual void v14();                    // +0x14
    virtual void SetActive(int active);    // +0x18
    virtual void v1c();                    // +0x1c
    virtual void v20();                    // +0x20
    virtual void AttachObject(cSpatialObject* pObject);      // +0x24
    virtual void SetModel(void* pObject, void* pModelWorld);            // +0x28
    virtual cModelInstance* GetModel();                      // +0x2c
    virtual void v30();                    // +0x30
    virtual float GetLevel();              // +0x34
};
struct cSpatialObjectView : cGameDataView {
    void* mpPrev;                          // +0x04
    void* mpNext;                          // +0x08
    cSpatialObject* mpObject;              // +0x0c (AutoRef)
    IRefCounted* mpObjectCombatant;        // +0x10 (AutoRef)
    bool mbSelected;                       // +0x14
    uint8_t pad15[3];
    Vector3 mColor;                        // +0x18
    cModelKey mKey;                        // +0x24
    bool mbFlag30;                         // +0x30
    bool mbFlag31;                         // +0x31
    bool mbFlag32;                         // +0x32

    cSpatialObjectView();
    virtual ~cSpatialObjectView();
    virtual void HandleSimulationUpdate(void* a, void* b);   // 0xe92ca0
    void StartEffect(float scale, int a);                    // 0xc88f??
};
struct cTotemPoleView : cSpatialObjectView {
    bool mbFlag34;                         // +0x34
    cTotemPoleView() : mbFlag34(false) {}
};
struct cOrnamentView : cSpatialObjectView {
    virtual ~cOrnamentView();               // 0xe8eaa0
};
struct cMineralView : cSpatialObjectView {
    uint32_t mField34;                     // +0x34
    bool mbLoadingModel;                   // +0x38
    bool mbAnimationsStarted;              // +0x39
    bool mbEffectsInLOD;                   // +0x3a
    bool mbField3b;                        // +0x3b
    AutoRef<cSPUIMeter> mProgressMeter;    // +0x3c
    AutoRef<cSPUIMeter> mGeyserMeter;      // +0x40
    AutoRef<cSPUIMeter> mPumpMeter;        // +0x44

    cMineralView();
    virtual ~cMineralView();                                            // 0xe8f000
    void OnMouseDown(void* a, void* b);                                 // 0xe8ec30
    void UpdateMiningTooltip(void* a);                                  // 0xe8ef10
};
void* __cdecl GonzagoModelWorld(void* pModel);                                    // 0xb3d520
void* __cdecl GetToolData(uint32_t id);                                           // 0xd37cb0
IRefCounted* __cdecl GetToolByKey(uint32_t key);                                  // 0xb6fa60
void* __cdecl Viewer();                                                           // App()->vtbl+0x58
void __cdecl GetCameraLocation(void* a, float* pOut);                             // 0x7c3d30
extern uint32_t gNestModelName;          // 0x015a88a8
// ---- items of slice s00e8e0d0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern uint32_t gNestModelName;          // 0x015a88a8

// @ 0x00e8eaa0
cOrnamentView::~cOrnamentView()
{
}

// @ 0x00e8eaf0
cTotemPoleView* __cdecl CreateTotemPoleView(cSimulatorObject* pOwner)
{
    cTotemPoleView* pView = 0;
    if (pOwner && pOwner->GetId() == 0x55cf865) {
        pView = (cTotemPoleView*)operator_new(sizeof(cTotemPoleView), "Simulator/cTotemPoleView", 0, 0, 0, 0);
        if (pView)
            new (pView) cTotemPoleView();
        void* const pModelWorld = GonzagoModelWorld(pOwner->mModel.GetModelWorld((const char*)&gNestModelName));
        pView->SetModel(pOwner, pModelWorld);
    }
    return pView;
}

// @ 0x00e8eb90
bool __stdcall GetOrnamentModelKey(const cSimulatorObject* pObject, cModelKey* pOutKey)
{
    cModelKey key;
    switch (pObject->mState) {
    case 0:
        key.mType = 0x1e42e0c6;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        key.mType = 0x1e42e0c5;
        break;
    case 5:
        key.mType = 0;
        key.mGroup = 0;
        key.mInstance = 0;
        *pOutKey = key;
        return true;
    default:
        return false;
    }
    key.mGroup = 0;
    key.mInstance = 0xf37c24e6;
    *pOutKey = key;
    return true;
}

// @ 0x00e8ec30
void __thiscall cMineralView::OnMouseDown(void* a, void* b)
{
    cSpatialObjectView::HandleSimulationUpdate(a, b);

    cSpatialObject* const pOwner = mpObject;
    if (!pOwner)
        return;

    cSimulatorObject* const pTarget = pOwner->GetInteractableObject(0x2e71a5a);
    if (!pTarget || !pTarget->mSelection.GetHighlightObject())
        return;

    const Vector3& highlightPos = pTarget->mSelection.GetPosition();
    float camPos[4];
    GetCameraLocation(Viewer(), camPos);

    const float dx = camPos[0] - highlightPos.x;
    const float dy = camPos[1] - highlightPos.y;
    const float dz = camPos[2] - highlightPos.z;
    const float distance = (float)sqrt(dx * dx + dy * dy + dz * dz);

    const float grown = pTarget->mHighlightGrow * distance;
    const float shrunk = distance * pTarget->mHighlightShrink;
    float radius = pTarget->mHighlightMin;
    if (radius < grown)
        radius = grown;
    if (shrunk <= radius)
        radius = shrunk;

    pTarget->mSelection.SetHighlightRadius(radius);
    pTarget->mbHighlighted = pTarget->mHighlightNear <= distance && distance < pTarget->mHighlightFar;
}

// @ 0x00e8ef10
void __thiscall cMineralView::UpdateMiningTooltip(void* a)
{
    if (!mpObject)
        return;

    cSimulatorObject* const pObject = mpObject->GetInteractableObject(0x398420d);
    if (!pObject)
        return;

    const int level = pObject->mLevel;
    bool canMine = false;
    if ((pObject->mFlags & 0x100) == 0 && GetToolData(0) != 0 && level == 4) {
        IRefCounted* const pToolA = GetToolByKey(0x4ad11866);
        IRefCounted* const pToolB = GetToolByKey(0x8d61d137);
        if (pToolA || pToolB)
            canMine = true;
    }

    pObject->ShowTooltip(canMine, a);
    (void)a;
}

// @ 0x00e8efd0
cMineralView::cMineralView()
: mField34(0), mbLoadingModel(false), mbAnimationsStarted(false),
      mbEffectsInLOD(false)
{
}

// @ 0x00e8f000
cMineralView::~cMineralView()
{
    if (mProgressMeter.mpObject) {
        mProgressMeter.mpObject->Shutdown(true);
        mProgressMeter.Reset();
    }
    if (mGeyserMeter.mpObject) {
        mGeyserMeter.mpObject->Shutdown(true);
        mGeyserMeter.Reset();
    }
    if (mPumpMeter.mpObject) {
        mPumpMeter.mpObject->Shutdown(true);
        mPumpMeter.Reset();
    }
}
