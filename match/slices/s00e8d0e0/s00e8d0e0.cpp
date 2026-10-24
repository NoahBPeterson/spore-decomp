// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00e8d0e0.
//
// The gameplay object views of the editor: the plant view that binds a plant
// model and drives its growth effect, the terrain cursor view that keeps a UI
// cursor frame in sync with the mouse position, and the small nest / egg views.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;
typedef int int32_t;
typedef int intptr_t;
#define nullptr 0

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

struct Vec4 {
    float mX;
    float mY;
    float mZ;
    float mW;
};

// A model / noun reference: type, instance and group identifiers.
struct ModelKey {
    uint32_t mType;
    uint32_t mInstance;
    uint32_t mGroup;
};

struct cMethodTable {
    void* mSlots[0x80];
};

// Any retail object with an indirect dispatch table at offset zero.
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

// A spatial object: flags word at +0x04, transform services in the vtable.
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

class cPlanetModel;

// The UI frame used by the terrain cursor view (vtable at +0x00).
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

class cGameTerrainCursorView : public cSpatialObjectView {
public:
    cGameTerrainCursorView();
    ~cGameTerrainCursorView();
    void HandleSimulationUpdate();
    void SetFlag(char bSet);
    char GetFlag();
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

void* operator new(size_t nSize, void* pPlace);

extern void* gVtableGamePlant;
extern void* gVtableTerrainCursor;
extern void* gVtableNest;
extern void* gVtableEgg;
extern ModelKey gDefaultKey;
extern Vec3 gUnitScale;
extern Vec3 gDefaultColor;

// ---------------------------------------------------------------------------
// retail services
// ---------------------------------------------------------------------------
char* GetCurrentGameMode();
void* GonzagoModelWorld(void* pFirst, void* pSecond);
void* GonzagoModelWorld();
void* GetEffectManager();
void* GetEffectSystem();
void* GetRenderManager();
void* GetLayoutManager(uint32_t nId);
void* GetWorldMainWindow(void* pLayout);
void* GetUUIManager();
void* CreateFrame(uint32_t nSize, uint32_t nAlign, const char* pName, void* pManager);
void* CreateWindow(uint32_t nSize, uint32_t nAlign, const char* pName, void* pManager);
void AddWindow(void* pParent, void* pChild);
void BuildFrameDrawable(void* pOut, void* pSource);
void SetFrameDrawable(void* pFrame, void* pDrawable);
void ReleaseWindow(void* pWindow);
void SetWindowLayout(void* pWindow, void* pFrame, uint32_t nFlags);
void PostRoomMessage(void* pSource, uint32_t nId);
void* GetRoom();
float GetPlantGrowth();
float GetPlantEffectScale();
void* GetPlantStage();
void ReleaseCreature(void* pCreature);
void WatcherAttach(cAnimatingCreature* pCreature, void* pModel);
void SetModelEffect(cAnimatingCreature* pCreature, cAnimatingCreature* pModel);
void DestroyEffect(void* pEffect);
void ReleaseEffect(cAnimatingCreature* pCreature);
void* CreateModelInstance(uint32_t nType, uint32_t nGroup, uint32_t nFlags);
void SetModelTransform(void* pModel, const float* pTransform);
void LoadModelFile(void* pModel);
void SetModelPosition(void* pModel, const float* pPosition);
void SetModelRotation(void* pModel, const float* pRotation, float fScale);
void SetCreatureAttachments(cAnimatingCreature* pCreature, void* pModel);
void* FindEffectSlot(cSpatialObjectView* pView);
void ReleaseObject(void* pObject);
void GetMousePosition(float* pOut);
float GetFloatProperty(void* pProperties, uint32_t nId);
void* GetProperties();
void GetVectorProperty(void* pProperties, uint32_t nId, float* pOut);
void* GetCamera();
void ApplyCursorFrame(void* pFrame, const Vec4* pRect);
void AddRefObject(void* pObject);
void* CreateObject(size_t nSize, const char* pName);
void ReleaseRefObject(void* pObject);
void SetMouseCursor(void* pFrame);
void ApplyWindowColor(void* pWindow, uint32_t nColor);
void SetAppPropertyPointer(uint32_t nId, void* pValue);
void SetTerrainCursorSize(float fSize);
void UpdateNestModelKey(void* pModel, const ModelKey* pKey);
float rw_fpu_conversion();
void* GetPlanetModel();
int IsCreatureAllowed();
void* GetCreatureAppearance();
int GetCreatureStageCount();
void* GetToolOwner();
void* ComputeCreatureScale();

void Sleep_ms(int nMs);

// ---------------------------------------------------------------------------
// 0x00e8d0e0  cGamePlantView::cGamePlantView
// ---------------------------------------------------------------------------
// @ 0x00e8d0e0
cGamePlantView::cGamePlantView()
{
    mpVftable = &gVtableGamePlant;
    mpAnimated = nullptr;

    mColor.mX = 0.0f;
    mColor.mY = 1.0f;
    mColor.mZ = 0.0f;

    mKey.mType = 0xc602cd31;
    mKey.mInstance = 0;
    mKey.mGroup = 0x5c4fce4c;

    if (mpAnimated != nullptr) {
        mpAnimated = nullptr;
        ReleaseEffect(mpAnimated);
    }
    mpObject = nullptr;
}

// ---------------------------------------------------------------------------
// 0x00e8d160  cGamePlantView::~cGamePlantView
// ---------------------------------------------------------------------------
// @ 0x00e8d160
cGamePlantView::~cGamePlantView()
{
    mpVftable = &gVtableGamePlant;

    if (mpObject != nullptr) {
        void* pModel = mpObject->GetComponent(0xaeb336b4);
        if (pModel != nullptr)
            SetCreatureAttachments((cAnimatingCreature*)0, nullptr);
    }

    if (mpAnimated != nullptr) {
        SetCreatureAttachments(mpAnimated, nullptr);
        void* pManager = GetEffectManager();
        ((cDispatchObject*)pManager)->Call(0x3c, (void*)mpAnimated);
        if (mpAnimated != nullptr) {
            mpAnimated = nullptr;
            ReleaseEffect(mpAnimated);
        }
    }
    if (mpAnimated != nullptr)
        ReleaseEffect(mpAnimated);
    mpVftable = &gVtableGamePlant;
}

// ---------------------------------------------------------------------------
// 0x00e8d1e0  cGamePlantView::UpdateEffectScale
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00e8d260  cGamePlantView::HandleSimulationUpdate
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00e8d4f0  cGamePlantView::Create
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00e8d6b0  PackColor
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00e8d740  cGameTerrainCursorView::SetFlag
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00e8d760  cGameTerrainCursorView::GetFlag
// ---------------------------------------------------------------------------
// @ 0x00e8d760
char cGameTerrainCursorView::GetFlag()
{
    char cFlags = (uint8_t)mpObject->mFlagByte;
    return (char)(cFlags & 1);
}

// ---------------------------------------------------------------------------
// 0x00e8d770  cGameTerrainCursorView::cGameTerrainCursorView
// ---------------------------------------------------------------------------
// @ 0x00e8d770
cGameTerrainCursorView::cGameTerrainCursorView()
{
    mpVftable = &gVtableTerrainCursor;
    mpAnimated = nullptr;
    mpObject = nullptr;
    mpFrame = nullptr;
}

// ---------------------------------------------------------------------------
// 0x00e8d790  cGameTerrainCursorView::~cGameTerrainCursorView
// ---------------------------------------------------------------------------
// @ 0x00e8d790
cGameTerrainCursorView::~cGameTerrainCursorView()
{
    Frame* pFrame = mpFrame;
    mpVftable = &gVtableTerrainCursor;
    if (pFrame != nullptr) {
        ((cDispatchObject*)pFrame)->Call(0x16c, (void*)0);
        pFrame = mpFrame;
        if (pFrame != nullptr) {
            mpFrame = nullptr;
            if (pFrame->mnRefCount < 2) {
                ((cDispatchObject*)pFrame)->Call(0x170, (uint32_t)(pFrame->mFlags >> 31));
            } else {
                pFrame->mnRefCount = pFrame->mnRefCount - 1;
            }
        }
    }

    if (mpFrame != nullptr) {
        void* pLayout = GetLayoutManager(0x5b598fa);
        void* pWindow = GetWorldMainWindow(pLayout);
        if (pWindow != nullptr)
            ((cDispatchObject*)pWindow)->Call(0xe0, (uint32_t)(intptr_t)mpFrame);
        if (mpFrame != nullptr) {
            Frame* pOld = mpFrame;
            mpFrame = nullptr;
            ((cDispatchObject*)pOld)->Call(0x04);
        }
    }
    if (mpFrame != nullptr)
        ((cDispatchObject*)mpFrame)->Call(0x04);

    pFrame = mpFrame;
    if (pFrame != nullptr) {
        if (pFrame->mnRefCount < 2)
            ((cDispatchObject*)pFrame)->Call(0x170, (uint32_t)(pFrame->mFlags >> 31));
        else
            pFrame->mnRefCount = pFrame->mnRefCount - 1;
    }
    if (mpAnimated != nullptr)
        ((cDispatchObject*)mpAnimated)->Call(0x04);
}

// ---------------------------------------------------------------------------
// 0x00e8d880  cGameTerrainCursorView::HandleSimulationUpdate
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00e8dd90  loadModel
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00e8de10  CreateGameTerrainCursorView
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00e8ded0  cNestView::cNestView
// ---------------------------------------------------------------------------
// @ 0x00e8ded0
cNestView::cNestView()
{
    mColor.mX = 1.0f;
    mColor.mY = 1.0f;
    mpVftable = &gVtableNest;
    mColor.mZ = 1.0f;
}

// ---------------------------------------------------------------------------
// 0x00e8df50  cNestView::SetupNestModelKey
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00e8e050  cEggView::cEggView
// ---------------------------------------------------------------------------
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
