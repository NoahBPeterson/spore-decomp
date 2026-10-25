// src/game/SPGonzago/SPGameTerrainCursorView.cpp -- migrated from slice(s) s00e8d0e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameTerrainCursorView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
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
class cGameTerrainCursorView : public cSpatialObjectView {
public:
    cGameTerrainCursorView();
    ~cGameTerrainCursorView();
    void HandleSimulationUpdate();
    void SetFlag(char bSet);
    char GetFlag();
};
void* operator new(size_t nSize, void* pPlace);
void* GonzagoModelWorld(void* pFirst, void* pSecond);
void* GonzagoModelWorld();
void* GetLayoutManager(uint32_t nId);
void* GetWorldMainWindow(void* pLayout);
void* GetUUIManager();
void* CreateFrame(uint32_t nSize, uint32_t nAlign, const char* pName, void* pManager);
void* CreateWindow(uint32_t nSize, uint32_t nAlign, const char* pName, void* pManager);
void BuildFrameDrawable(void* pOut, void* pSource);
void SetModelTransform(void* pModel, const float* pTransform);
void LoadModelFile(void* pModel);
void GetMousePosition(float* pOut);
float GetFloatProperty(void* pProperties, uint32_t nId);
void* GetProperties();
void GetVectorProperty(void* pProperties, uint32_t nId, float* pOut);
void* CreateObject(size_t nSize, const char* pName);
void* GetPlanetModel();
// ---- items of slice s00e8d0e0 end

// @ 0x00e8d6b0
uint32_t PackColor(float fRed, float fGreen, float fBlue, float fAlpha)
{
    uint32_t nRed = (uint32_t)(int)(fRed * 255.0f);
    uint32_t nGreen = (uint32_t)(int)(fGreen * 255.0f);
    uint32_t nBlue = (uint32_t)(int)(fBlue * 255.0f);
    uint32_t nAlpha = (uint32_t)(int)(fAlpha * 255.0f);
    return (((nRed << 8) | (nGreen & 0xff)) << 8 | (nBlue & 0xff)) << 8 |
           (nAlpha & 0xff);
}

// @ 0x00e8d740
void cGameTerrainCursorView::SetFlag(char bSet)
{
    uint32_t* pFlags = &mpObject->mFlags;
    if (bSet != 0) {
        *pFlags = *pFlags | 1;
        return;
    }
    *pFlags = *pFlags & 0xfffffffe;
}

// @ 0x00e8d760
char cGameTerrainCursorView::GetFlag()
{
    char cFlags = (uint8_t)mpObject->mFlagByte;
    return (char)(cFlags & 1);
}

// @ 0x00e8d880
void cGameTerrainCursorView::HandleSimulationUpdate()
{
    char bActive = ((cDispatchObject*)mpAnimated)->CallChar(0xbc);
    if (bActive == 0 && (mpFrame->mFlags & 0x8000) != 0)
        ((cDispatchObject*)mpFrame)->Call(0x16c, (void*)0);

    bActive = ((cDispatchObject*)mpAnimated)->CallChar(0xbc);
    if (bActive != 0 && (mpFrame->mFlags & 0x8000) == 0)
        ((cDispatchObject*)mpFrame)->Call(0x16c, (uint32_t)1);

    void* pPlanet = GetPlanetModel();
    if (*(int*)((uint8_t*)pPlanet + 0x24) != 0) {
        float aTransform[9];
        void* pSource = (void*)(intptr_t)mpAnimated;
        (void)pSource;
        GetMousePosition(aTransform);
        BuildFrameDrawable(aTransform, aTransform);
        SetModelTransform(aTransform, aTransform);
        mpFrame->mFlags = mpFrame->mFlags | (1u << 15);
        float fValue = ((cDispatchObject*)mpAnimated)->CallFloat(0xb4);
        *(float*)((uint8_t*)mpFrame + 0x58) = fValue;
        mpFrame->mFlags = (mpFrame->mFlags & 0xfffffff9u) | 6;
    }

    if (((cDispatchObject*)mpAnimated)->CallChar(0xa8) == 0) {
        if (mpFrame != nullptr) {
            void* pLayout = GetLayoutManager(0x5b598fa);
            void* pWindow = GetWorldMainWindow(pLayout);
            ((cDispatchObject*)pWindow)->Call(0xe0, (uint32_t)(intptr_t)mpFrame);
            if (mpFrame != nullptr) {
                Frame* pOld = mpFrame;
                mpFrame = nullptr;
                ((cDispatchObject*)pOld)->Call(0x04);
            }
        }
        return;
    }

    if (mpFrame == nullptr) {
        void* pProperties = GetProperties();
        float aColor[4];
        GetVectorProperty(pProperties, 0x42c3672, aColor);
        float aColor2[4];
        GetVectorProperty(pProperties, 0x67ce649, aColor2);
        float fSize = GetFloatProperty(pProperties, 0x42c38ab);

        void* pManager = GetUUIManager();
        void* pFrame = CreateFrame(0x60, 4, "UI/GameTerrainCursorView", pManager);
        *(float*)((uint8_t*)pFrame + 0x58) = fSize;
        *(float*)((uint8_t*)pFrame + 0x50) = fSize;
        *(float*)((uint8_t*)pFrame + 0x54) = fSize;
        *(float*)((uint8_t*)pFrame + 0x4c) = fSize;
        *(uint32_t*)((uint8_t*)pFrame + 0x0c) = 2;
        *(uint32_t*)((uint8_t*)pFrame + 0x10) = PackColor(aColor[1], aColor[2],
                                                         aColor[0], aColor[3]);

        void* pWindow = CreateWindow(0x20c, 4, "UI/SPGameTerrainCursorView", pManager);
        if (pWindow != nullptr)
            pWindow = (uint8_t*)pWindow + 4;
        if (pWindow != (void*)mpFrame) {
            if (pWindow != nullptr)
                ((cDispatchObject*)pWindow)->Call(0x00);
            mpFrame = (Frame*)pWindow;
            if (pWindow != nullptr)
                ((cDispatchObject*)pWindow)->Call(0x04);
        }
        ((cDispatchObject*)mpFrame)->Call(0xb0, pFrame);
        ((cDispatchObject*)mpFrame)->Call(0xac, PackColor(aColor2[2], fSize, aColor2[0],
                                                        aColor2[1]));
        void* pLayout = GetLayoutManager(0x5b598fa);
        void* pMain = GetWorldMainWindow(pLayout);
        ((cDispatchObject*)pMain)->Call(0xd8, (uint32_t)(intptr_t)mpFrame);
        if (mpFrame == nullptr)
            return;
    }

    float aMouse[4];
    GetMousePosition(aMouse);
    float* pRect = (float*)((cDispatchObject*)mpFrame)->Call(0x34);
    float aNew[4];
    aNew[0] = aMouse[0];
    aNew[1] = aMouse[1];
    aNew[2] = aMouse[2];
    aNew[3] = aMouse[3];
    if (pRect[0] != aNew[0] || pRect[1] != aNew[1] || pRect[2] != aNew[2] ||
        pRect[3] != aNew[3]) {
        float aRect[4];
        aRect[0] = aNew[0];
        aRect[1] = aNew[1];
        aRect[2] = aNew[2];
        aRect[3] = aNew[3];
        ((cDispatchObject*)mpFrame)->Call(0x60, aRect);
    }
}

// @ 0x00e8dd90
void* loadModel()
{
    void* pWorld = GonzagoModelWorld();
    void* pModel = ((cDispatchObject*)pWorld)->Call(0x0c, (void*)(intptr_t)0x7f70e30b,
                                                    (uint32_t)0x5c4fce4c);
    *(uint32_t*)((uint8_t*)pModel + 4) |= 2;
    *(float*)((uint8_t*)pModel + 0x4c) = 1.0f;
    *(float*)((uint8_t*)pModel + 0x50) = 1.0f;
    *(float*)((uint8_t*)pModel + 0x54) = 1.0f;
    *(float*)((uint8_t*)pModel + 0x58) = 1.0f;
    void* pOld = *(void**)((uint8_t*)pModel + 0x64);
    if (pOld != nullptr) {
        *(void**)((uint8_t*)pModel + 0x64) = nullptr;
        ((cDispatchObject*)pOld)->Call(0x04);
    }
    return pModel;
}

// @ 0x00e8de10
cGameTerrainCursorView* CreateGameTerrainCursorView(cSpatialObject* pObject)
{
    cGameTerrainCursorView* pView =
        (cGameTerrainCursorView*)CreateObject(0x40, "Simulator/cGameTerrainCursorView");
    if (pView != nullptr)
        ::new ((void*)pView) cGameTerrainCursorView();

    cAnimatingCreature* pModel = nullptr;
    if (pObject != nullptr)
        pModel = (cAnimatingCreature*)pObject->GetComponent(0x014a4edc);

    cAnimatingCreature* pOld = pView->mpAnimated;
    if (pModel != pOld) {
        if (pModel != nullptr)
            ((cDispatchObject*)pModel)->Call(0x00);
        pView->mpAnimated = pModel;
        if (pOld != nullptr)
            ((cDispatchObject*)pOld)->Call(0x04);
    }

    void* pLoaded = loadModel();
    LoadModelFile(pLoaded);
    ((cDispatchObject*)pView)->Call(0x24, pObject);
    return pView;
}
