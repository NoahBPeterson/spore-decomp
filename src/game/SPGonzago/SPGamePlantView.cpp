// src/game/SPGonzago/SPGamePlantView.cpp -- migrated from slice(s) s00e8d0e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGamePlantView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cAnimatingCreature.h"
#include "SP/cSpatialObject.h"

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
class cGamePlantView : public cSpatialObjectView {
public:
    cGamePlantView();
    ~cGamePlantView();
    void UpdateEffectScale();
    void HandleSimulationUpdate(void* pParam2, uint32_t nParam3);
    cGamePlantView* Create(cSpatialObject* pObject);
};
void* operator new(size_t nSize, void* pPlace);
char* GetCurrentGameMode();
void* GonzagoModelWorld(void* pFirst, void* pSecond);
void* GonzagoModelWorld();
void* GetEffectManager();
void* GetEffectSystem();
float GetPlantGrowth();
float GetPlantEffectScale();
void* GetPlantStage();
void SetModelEffect(cAnimatingCreature* pCreature, cAnimatingCreature* pModel);
void ReleaseEffect(cAnimatingCreature* pCreature);
void* CreateModelInstance(uint32_t nType, uint32_t nGroup, uint32_t nFlags);
void LoadModelFile(void* pModel);
void SetCreatureAttachments(cAnimatingCreature* pCreature, void* pModel);
void* CreateObject(size_t nSize, const char* pName);
// ---- items of slice s00e8d0e0 end

// @ 0x00e8d1e0
void cGamePlantView::UpdateEffectScale()
{
    float fScale = GetPlantEffectScale();
    bool bChanged = !(mpAnimated == nullptr && fScale == 1.0f);
    if (mpAnimated != nullptr)
        mpAnimated->mfEffectValue = fScale;

    void* pTarget = ((cDispatchObject*)this)->Call(0x2c);
    if (pTarget == nullptr)
        return;
    if (bChanged) {
        *(uint32_t*)((uint8_t*)pTarget + 0x58) = 0;
        *(uint32_t*)((uint8_t*)pTarget + 4) |= 2;
        return;
    }
    *(uint32_t*)((uint8_t*)pTarget + 0x58) = 0x3f800000;
    *(uint32_t*)((uint8_t*)pTarget + 4) |= 2;
}

// @ 0x00e8d260
void cGamePlantView::HandleSimulationUpdate(void* pParam2, uint32_t nParam3)
{
    if (GetCurrentGameMode() == (char*)0x01654c05)
        return;
    if (mpObject == nullptr)
        return;

    void* pModel = mpObject->GetComponent(0xaeb336b4);
    if (pModel == nullptr)
        return;

    void* pPlant = GetPlantStage();
    if (pPlant == 0)
        goto Done;

    if (mpAnimated == nullptr)
        goto CreateEffect;

    if (*(void**)((uint8_t*)pPlant + 0x53c) != (void*)mpAnimated) {
        void* pSystem = GetEffectSystem();
        if (pSystem != nullptr) {
            void* pManager = GetEffectManager();
            ((cDispatchObject*)pManager)->Call(0x3c, (void*)mpAnimated);
        }
        SetCreatureAttachments((cAnimatingCreature*)0, nullptr);
        if (mpAnimated != nullptr) {
            mpAnimated = nullptr;
            ReleaseEffect(mpAnimated);
        }
    }
    if (mpAnimated == nullptr)
        goto CreateEffect;
    goto BindEffect;

CreateEffect:
    {
        uint32_t aKey[4];
        aKey[0] = 0;
        aKey[1] = 0;
        aKey[2] = 0;
        aKey[3] = 0;
        void* pInstance = nullptr;
        if (*(int*)((uint8_t*)pPlant + 0x504) == 0) {
            pInstance = (void*)(*(uint8_t**)((uint8_t*)pPlant + 0x51c));
            void* pManager = GetEffectManager();
            pInstance = ((cDispatchObject*)pManager)->Call(0x38, pInstance, 0);
        } else {
            aKey[0] = *(uint32_t*)((uint8_t*)pPlant + 0x508);
            aKey[3] = *(uint32_t*)((uint8_t*)pPlant + 0x504);
            aKey[2] = *(uint32_t*)((uint8_t*)pPlant + 0x50c);
            if (aKey[3] == 0) {
                pInstance = (void*)(*(uint8_t**)((uint8_t*)pPlant + 0x51c));
                void* pManager = GetEffectManager();
                pInstance = ((cDispatchObject*)pManager)->Call(0x38, pInstance, 0);
            } else {
                void* pManager = GetEffectManager();
                pInstance = ((cDispatchObject*)pManager)->Call(0x30, (void*)aKey);
            }
        }
        LoadModelFile(pInstance);
        if (mpAnimated == nullptr)
            return;
        CreateModelInstance(0, 0, 0);
        mpAnimated->mfEffectValue = GetPlantGrowth();
        SetCreatureAttachments(mpAnimated, pModel);
        SetModelEffect(mpAnimated, mpAnimated);
        void* pWorld = GonzagoModelWorld();
        ((cDispatchObject*)pWorld)->Call(0xb4, (void*)mpAnimated, (uint32_t)0);
    }

BindEffect:
    {
        uint32_t* pParams = (uint32_t*)((cDispatchObject*)pModel)->Call(0x2c);
        mpAnimated->mPad000[0] = (uint8_t)pParams[0];
        mpAnimated->mPad000[1] = (uint8_t)pParams[1];
        mpAnimated->mPad000[2] = (uint8_t)(pParams[1] >> 8);
        mpAnimated->mPad000[3] = (uint8_t)(pParams[1] >> 16);
        mpAnimated->mPad000[4] = (uint8_t)(pParams[1] >> 24);
        mpAnimated->mfEffectValue = (float)pParams[2];

        float* pScale = (float*)((cDispatchObject*)pModel)->Call(0x30);
        mpAnimated->mPad000[5] = (uint8_t)pScale[0];
        mpAnimated->mPad000[6] = (uint8_t)pScale[1];
        mpAnimated->mPad000[7] = (uint8_t)pScale[2];
        mpAnimated->mPad000[8] = (uint8_t)pScale[3];
    }

Done:
    UpdateEffectScale();
}

// @ 0x00e8d4f0
cGamePlantView* cGamePlantView::Create(cSpatialObject* pObject)
{
    void* pModel = nullptr;
    if (pObject != nullptr)
        pModel = pObject->GetComponent(0xaeb336b4);

    cGamePlantView* pView = (cGamePlantView*)CreateObject(0x40, "Simulator/cGamePlantView");
    if (pView != nullptr)
        ::new ((void*)pView) cGamePlantView();

    if (pModel != nullptr) {
        void* pStage = GetPlantStage();
        if (pStage != nullptr) {
            *(uint32_t*)((uint8_t*)pView + 0x24) = 0xc602cd31;
            *(uint32_t*)((uint8_t*)pView + 0x28) = 0;
            *(uint32_t*)((uint8_t*)pView + 0x2c) = 0x5c4fce4c;
            pView->mColor.mX = 1.0f;
            pView->mColor.mY = 1.0f;
            pView->mColor.mZ = 1.0f;
        }
    }

    uint32_t nType = *(uint32_t*)((uint8_t*)pModel + 0xac);
    (void)nType;
    if (nType == 0) {
        void* pWorld = GonzagoModelWorld((uint8_t*)this + 0x24, (uint8_t*)this + 0x18);
        ((cDispatchObject*)pView)->Call(0x28, pObject, (uint32_t)(intptr_t)pWorld);
    } else {
        ((cDispatchObject*)pView)->Call(0x24, pObject);
    }

    void* pStage = GetPlantStage();
    if (pStage != nullptr) {
        float fX = *(float*)((uint8_t*)pStage + 0x554) * -0.5f;
        float fY = *(float*)((uint8_t*)pStage + 0x558) * -0.5f;
        float fZ = *(float*)((uint8_t*)pStage + 0x55c);
        float aRect[4];
        aRect[0] = fX;
        aRect[1] = fY;
        aRect[2] = -fX;
        aRect[3] = -fY;
        ((cDispatchObject*)pModel)->Call(0x64, (void*)aRect, (uint32_t)0x3f800000);
        (void)fZ;
    }
    return pView;
}
