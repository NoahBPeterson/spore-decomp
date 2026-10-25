// src/game/SPGonzago/SPNestView.cpp -- migrated from slice(s) s00e8e0d0, s00e8d0e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPNestView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cAnimatingCreature.h"
#include "SP/cSpatialObject.h"
#include "SP/cGameDataView.h"
#include "SP/cModelInstance.h"
#include <math.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern void* gVtableEgg;

// ---- items of slice s00e8d0e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int intptr_t;
#define nullptr 0
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
struct ModelKey {
    uint32_t mType;
    uint32_t mInstance;
    uint32_t mGroup;
};
struct cMethodTable {
    void* mSlots[0x80];
};
struct cDispatchObject {
    cMethodTable* mpMethods;                    // 0x00

    void* Call(int nSlot) {
        return ((void* (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    void* Call(int nSlot, void* pArg1) {
        return ((void* (*)(void*, void*))mpMethods->mSlots[nSlot >> 2])(this, pArg1);
    }
    void* Call(int nSlot, uint32_t nArg1) {
        return ((void* (*)(void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1);
    }
    void* Call(int nSlot, uint32_t nArg1, uint32_t nArg2) {
        return ((void* (*)(void*, uint32_t, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1, nArg2);
    }
    void* Call(int nSlot, void* pArg1, uint32_t nArg2) {
        return ((void* (*)(void*, void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, pArg1, nArg2);
    }
    void* Call(int nSlot, uint32_t nArg1, void* pArg2) {
        return ((void* (*)(void*, uint32_t, void*))mpMethods->mSlots[nSlot >> 2])(this, nArg1, pArg2);
    }
    void CallVoid(int nSlot, void* pArg1, uint32_t nArg2) {
        ((void (*)(void*, void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, pArg1, nArg2);
    }
    float CallFloat(int nSlot) {
        return ((float (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    char CallChar(int nSlot) {
        return ((char (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
};
class cSpatialObject {
public:
    void* mpMethods;                            // 0x00
    union {
        uint32_t mFlags;                        // 0x04
        uint8_t mFlagByte;                      // 0x04
    };

    void* GetComponent(uint32_t nKey) {
        return ((void* (*)(void*, uint32_t))((cMethodTable*)mpMethods)->mSlots[0xb8 >> 2])(this, nKey);
    }
};
class cAnimatingCreature {
public:
    uint8_t mPad000[0x80];                      // 0x000
    float mfEffectValue;                        // 0x080
};
struct Frame {
    cMethodTable* mpMethods;                    // 0x00
    uint32_t mFlags;                            // 0x04
    uint8_t mPad08[0x38];                       // 0x08
    int mnRefCount;                             // 0x40
};
class cSpatialObjectView {
public:
    cSpatialObjectView();

    void* mpVftable;                            // 0x00
    uint32_t mPad04[5];                         // 0x04
    Vec3 mColor;                                // 0x18
    ModelKey mKey;                              // 0x24
    void* mpPad30;                              // 0x30
    cAnimatingCreature* mpAnimated;             // 0x34
    cSpatialObject* mpObject;                   // 0x38
    Frame* mpFrame;                             // 0x3c
};
class cNestView : public cSpatialObjectView {
public:
    cNestView();
    void SetupNestModelKey();
};
class cEggView : public cSpatialObjectView {
public:
    cEggView();
};
extern void* gVtableEgg;
char* GetCurrentGameMode();
void SetAppPropertyPointer(uint32_t nId, void* pValue);
void UpdateNestModelKey(void* pModel, const ModelKey* pKey);
int IsCreatureAllowed();
void* GetCreatureAppearance();
int GetCreatureStageCount();
void* GetToolOwner();
// ---- items of slice s00e8d0e0 end

// ---- items of slice s00e8e0d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned int, void* p) throw() { return p; }
void* __cdecl operator_new(unsigned size, const char* file, int a, int b, int c, int d);  // 0xf473a0
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
void __cdecl Matrix3FromQuaternion(float* pBasis, const void* pQuaternion);   // 0x?
struct cSPTransform_s00e8_e0d0;
struct IRefCounted {
    virtual void v00();
    virtual void Release();                // +0x04
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
struct cSpatialObject_s00e8_e0d0 {                    // the game side a view is attached to
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
struct tEffectParam : IRefCounted {        // EA::Swarm::cResourceOverridesParam
    virtual void v00();
    virtual void Release();                // +0x04
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
    uint32_t mField04;                     // +0x04
    uint32_t mField08;                     // +0x08
    uint32_t mField0c;                     // +0x0c
    uint32_t mField10;                     // +0x10
    uint32_t mField14;                     // +0x14
    uint32_t mField18;                     // +0x18
    uint32_t mField1c;                     // +0x1c
    uint32_t mField20;                     // +0x20
    uint32_t mField24;                     // +0x24
    uint32_t mField28;                     // +0x28
    uint32_t mField2c;                     // +0x2c
    uint32_t mField30;                     // +0x30
    uint32_t mField34;                     // +0x34
    uint32_t mField38;                     // +0x38
    uint32_t mField3c;                     // +0x3c
    static tEffectParam* __cdecl Create(int count);   // 0x?
};
struct cEffect {
    virtual void v00();                    // +0x00
    virtual void Release();                // +0x04
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void SetTransform(void* pTransform);     // +0x18
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual void v2c();
    virtual void SetLooping(bool looping);           // +0x30
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual void AddParam(int slot, tEffectParam* pParam);   // +0x4c
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
    virtual cSpatialObject_s00e8_e0d0* GetOwner();    // +0x0c
    virtual void SetVisible(int visible);  // +0x10
    virtual void v14();                    // +0x14
    virtual void SetActive(int active);    // +0x18
    virtual void v1c();                    // +0x1c
    virtual void v20();                    // +0x20
    virtual void AttachObject(cSpatialObject_s00e8_e0d0* pObject);      // +0x24
    virtual void SetModel(void* pObject, void* pModelWorld);            // +0x28
    virtual cModelInstance* GetModel();                      // +0x2c
    virtual void v30();                    // +0x30
    virtual float GetLevel();              // +0x34
};
struct cSpatialObjectView_s00e8_e0d0 : cGameDataView {
    void* mpPrev;                          // +0x04
    void* mpNext;                          // +0x08
    cSpatialObject_s00e8_e0d0* mpObject;              // +0x0c (AutoRef)
    IRefCounted* mpObjectCombatant;        // +0x10 (AutoRef)
    bool mbSelected;                       // +0x14
    uint8_t pad15[3];
    Vector3 mColor;                        // +0x18
    cModelKey mKey;                        // +0x24
    bool mbFlag30;                         // +0x30
    bool mbFlag31;                         // +0x31
    bool mbFlag32;                         // +0x32

    cSpatialObjectView_s00e8_e0d0();
    virtual ~cSpatialObjectView_s00e8_e0d0();
    virtual void HandleSimulationUpdate(void* a, void* b);   // 0xe92ca0
    void StartEffect(float scale, int a);                    // 0xc88f?? 0x00c88980
};
struct cEggView_s00e8_e0d0 : cSpatialObjectView_s00e8_e0d0 {
    uint32_t mEffectA;                     // +0x34
    uint32_t mEffectB;                     // +0x38

    cEggView_s00e8_e0d0() : mEffectA(0), mEffectB(0) { mColor = Vector3(1.0f, 1.0f, 1.0f); }
    void CreateAndStartScaledEffect(uint32_t effectID, uint32_t a, int b);  // 0xe8e420
    virtual void HandleSimulationUpdate(void* a, void* b);                  // 0xe8e5d0
};
struct cNestView_s00e8_e0d0 : cSpatialObjectView_s00e8_e0d0 {
    cNestView_s00e8_e0d0() { mColor = Vector3(1.0f, 1.0f, 1.0f); }
    virtual void HandleSimulationUpdate(void* a, void* b);                  // 0xe8e220
};
void* __cdecl GonzagoModelWorld(void* pModel);                                    // 0xb3d520
cEffect* __cdecl CreateEffectById(uint32_t effectID, uint32_t b);                 // 0xc8ad30
void __cdecl DestroyEffectById(uint32_t effectID, int a);                         // 0xc89d60
void __cdecl FinishEffect(uint32_t effectID);                                     // 0xc8aa60
uint8_t* __cdecl GetCurrentGameMode_s00e8_e0d0();                                            // 0xb5b800
bool __cdecl IsInteractionMode();                                                 // 0xc6a020
void __cdecl SetOtherState(int value, int a);                                     // 0xb3d310
void __cdecl StartToolEffect(cSimulatorObject* pObject, uint32_t a);              // 0xb48770
bool __cdecl CheckToolSlot(cSimulatorObject* pObject, int a);                     // 0xb53940
void __cdecl RefreshToolVisual(cSimulatorObject* pObject);                        // 0xb470b0
void* __cdecl ModelManager();                                                     // 0x?
uint32_t __cdecl GetModelIdForFlash(void* a, int b);                              // ModelManager()->vtbl+0x28
extern uint32_t gModelWorldName;         // 0x015a8890
extern uint8_t gGameModePlanet;          // 0x01654c01
extern uint32_t gEffectParamA[4];        // 0x015d96fc
extern uint32_t gEffectParamB[4];        // 0x015d99fc
extern uint32_t gEffectParamC[4];        // 0x015d97fc
// ---- items of slice s00e8e0d0 end

// @ 0x00e8df50
void cNestView::SetupNestModelKey()
{
    ModelKey key;
    key.mType = 0xe960f03f;
    key.mInstance = 0;
    key.mGroup = 0;

    if (GetCurrentGameMode() == (char*)0x01654c01) {
        SetAppPropertyPointer(0, nullptr);
        void* pStage = (void*)(intptr_t)GetCreatureStageCount();
        void* pAppearance = GetCreatureAppearance();
        if (pAppearance == (void*)pStage) {
            void* pCreature = (void*)(intptr_t)*(uint32_t*)((uint8_t*)this + 0x128);
            int nState = 0;
            if (pCreature != nullptr && *(char*)((uint8_t*)pCreature + 0x84) != 0) {
                GetToolOwner();
                nState = IsCreatureAllowed();
            }
            if (nState == 0)
                key.mType = 0x87b2acc2;
            else if (nState == 1)
                key.mType = 0x87b2acc3;
            else
                key.mType = 0x87b2acc0;
        } else {
            key.mType = 0xfe29a98d;
            if (*(char*)((uint8_t*)pAppearance + 400) == 0)
                key.mType = 0x2d12268b;
        }
        key.mInstance = 0;
        key.mGroup = 0;
    }

    uint32_t* pCurrent = (uint32_t*)(((cDispatchObject*)this)->Call(0x34));
    (void)pCurrent;
    ModelKey current = *(ModelKey*)((uint8_t*)this + 0x24);
    if (current.mType != key.mType || current.mInstance != key.mInstance ||
        current.mGroup != key.mGroup) {
        UpdateNestModelKey((uint8_t*)this + 0x34, &key);
    }
}

// @ 0x00e8e050
cEggView::cEggView()
{
    mpAnimated = nullptr;
    mpObject = nullptr;
    mColor.mX = 1.0f;
    mColor.mY = 1.0f;
    mpVftable = &gVtableEgg;
    mColor.mZ = 1.0f;
}

// @ 0x00e8e0d0
cEggView_s00e8_e0d0* __cdecl CreateEggView(cSpatialObject_s00e8_e0d0* pOwner)
{
    cEggView_s00e8_e0d0* pView = (cEggView_s00e8_e0d0*)operator_new(sizeof(cEggView_s00e8_e0d0), "Simulator/cEggView", 0, 0, 0, 0);
    if (pView)
        new (pView) cEggView_s00e8_e0d0();
    pView->AttachObject(pOwner);
    return pView;
}

// @ 0x00e8e160
cNestView_s00e8_e0d0* __cdecl CreateNestView(cSimulatorObject* pOwner)
{
    cNestView_s00e8_e0d0* pView = (cNestView_s00e8_e0d0*)operator_new(sizeof(cNestView_s00e8_e0d0), "Simulator/cNestView", 0, 0, 0, 0);
    if (pView)
        new (pView) cNestView_s00e8_e0d0();

    cSimulatorObject* pObject = 0;
    if (pOwner)
        pObject = pOwner->GetObjectById(0x1b92b27);
    pObject->SetupNestModelKey();
    void* const pModelWorld = GonzagoModelWorld(pObject->mModel.GetModelWorld((const char*)&gModelWorldName));
    pView->SetModel(pOwner, pModelWorld);
    return pView;
}

// @ 0x00e8e220
void __thiscall cNestView_s00e8_e0d0::HandleSimulationUpdate(void* a, void* b)
{
    cSpatialObject_s00e8_e0d0* const pOwner = GetOwner();
    cSimulatorObject* const pObject = pOwner ? pOwner->GetSimObject(0x1b92b27) : 0;

    if (!pObject->mbReady) {
        if (pObject->mModel.GetModel())
            RefreshToolVisual(pObject);
        SetActive(0);
        SetVisible(0);
        pObject->mModel.RefreshModelWorld();
        return;
    }

    if (pObject->mSelection.GetHighlightObject() == 0 && !mbSelected) {
        if (!CheckToolSlot(pObject, 0)) {
            SetOtherState(1, 1);
            StartToolEffect(pObject, 1);
        }
    }

    if (pObject->mbModelDirty) {
        const Vector3 saved = *pObject->mModel.GetModelWorld((const char*)&gModelWorldName);
        GetOwner()->GetSimObject(0x1b92b27)->SetupNestModelKey();
        pObject->mbModelDirty = false;
        const Vector3& current = *pObject->mModel.GetModelWorld((const char*)&gModelWorldName);
        if (saved.x != current.x || saved.y != current.y || saved.z != current.z)
            pObject->mModel.RefreshModelWorld();
    }

    if (GetModel() == 0 && pObject->mModel.IsReady())
        SetModel(GetOwner(), GonzagoModelWorld(pObject->mModel.GetModelWorld((const char*)&gModelWorldName)));

    SetActive(1);
    SetVisible(1);

    cModelInstance* const pModel = GetModel();
    if (pModel) {
        const uint32_t id = GetModelIdForFlash(ModelManager(), 0);
        if (id < 0x40)
            pModel->mDrawFlags[(id >> 5) & 1] |= 1u << (id & 0x1f);
    }

    cSpatialObjectView_s00e8_e0d0::HandleSimulationUpdate(a, b);
}

// @ 0x00e8e420
void __thiscall cEggView_s00e8_e0d0::CreateAndStartScaledEffect(uint32_t effectID, uint32_t a, int b)
{
    cEffect* const pEffect = CreateEffectById(effectID, a);
    if (!pEffect)
        return;

    pEffect->v00();

    cSPTransform_s00e8_e0d0 transform;
    const Vector3& position = mpObject->GetPosition();
    transform.mMask |= 4;
    transform.mOrientationMask += 1;
    transform.mPosition = position;

    float basis[9];
    Matrix3FromQuaternion(basis, mpObject->GetOrientation());
    memcpy(transform.mBasis, basis, sizeof(basis));
    transform.mMask |= 2;
    transform.mOrientationMask += 2;
    transform.mScale = (float)b;

    pEffect->SetTransform(&transform);

    tEffectParam* const pParam = tEffectParam::Create(3);
    if (pParam)
        pParam->v00();
    pParam->mField18 = 1;
    pParam->mField10 = gEffectParamA[b];
    pParam->mField14 = 0;
    pParam->mField28 = 2;
    pParam->mField20 = gEffectParamB[b];
    pParam->mField24 = 0;
    pParam->mField38 = 3;
    pParam->mField30 = gEffectParamC[b];
    pParam->mField34 = 0;
    pEffect->AddParam(3, pParam);
    pEffect->SetLooping(true);
    StartEffect(transform.mOrientation.y, 1);
    pParam->Release();
    pEffect->Release();
}

// @ 0x00e8e5d0
void __thiscall cEggView_s00e8_e0d0::HandleSimulationUpdate(void* a, void* b)
{
    cSpatialObject_s00e8_e0d0* const pOwner = mpObject;
    cSimulatorObject* const pObject = GetOwner()->GetSimObject(0x2a0349a);

    if (pOwner->mIsSelected) {
        pOwner->mIsSelected = false;

        cSPTransform_s00e8_e0d0 transform;
        transform.mMask = 0;
        transform.mOrientationMask = 0;
        transform.mPosition = pOwner->GetPosition();
        transform.mMask |= 4;
        transform.mOrientationMask += 1;

        float basis[9];
        Matrix3FromQuaternion(basis, pOwner->GetOrientation());
        memcpy(transform.mBasis, basis, sizeof(basis));
        transform.mScale = pObject->mEffectScale;
        transform.mMask |= 2;
        transform.mOrientationMask += 2;

        if (GetCurrentGameMode_s00e8_e0d0() == &gGameModePlanet && pOwner->IsHighlighted()) {
            DestroyEffectById(mEffectA, 0);
        }
        DestroyEffectById(mEffectA, 1);

        transform.mScale = pOwner->GetScale();
        transform.mOrientationMask += 1;

        cModelInstance* const pModel = GetModel();
        if (pModel)
            pModel->SetTransform(transform);
    }

    if (pObject->mpToolData == 0 || !IsInteractionMode()) {
        DestroyEffectById(mEffectA, 1);
        mEffectA = 0;
    } else if (!pObject->mbEffectPending) {
        DestroyEffectById(mEffectA, 1);
    } else {
        pObject->mbEffectPending = false;
        switch (pObject->mEffectKind) {
        case 0: CreateAndStartScaledEffect(0xee5eeced, 1, mEffectA); break;
        case 1: CreateAndStartScaledEffect(0xcd57ac50, 1, mEffectA); break;
        case 2: CreateAndStartScaledEffect(0xcd57ac53, 1, mEffectA); break;
        case 3: CreateAndStartScaledEffect(0x4a9d2f4c, 1, mEffectA); break;
        case 4: CreateAndStartScaledEffect(0x91363bfd, 1, mEffectA); break;
        case 5: CreateAndStartScaledEffect(0x865b5257, 1, mEffectA); break;
        case 6: CreateAndStartScaledEffect(0xb70973f3, 1, mEffectA); break;
        }
    }
    FinishEffect(mEffectA);
}
