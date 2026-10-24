// Slice s00e8e0d0 — Simulator object views: egg, nest, totem pole, mineral and
// ornament view factories, their simulation updates and the mineral meter teardown.
// Flags: /O2 /MD /Gy /TP /arch:SSE for every row except 0x00e8e5d0 and
// 0x00e8ec30, which are x87 code and take the default flag set.
#include <math.h>
#include <string.h>

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

inline void* operator new(unsigned int, void* p) throw() { return p; }
void* __cdecl operator_new(unsigned size, const char* file, int a, int b, int c, int d);  // 0xf473a0

// ---------------------------------------------------------------------------
// math
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Matrix33 {
    Vector3 mRow[3];
};

void __cdecl Matrix3FromQuaternion(float* pBasis, const void* pQuaternion);   // 0x?

struct cSPTransform;

// ---------------------------------------------------------------------------
// refcounted objects
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// simulator and game objects
// ---------------------------------------------------------------------------
struct cModelKey {
    uint32_t mType;                        // +0x00
    uint32_t mGroup;                       // +0x04
    uint32_t mInstance;                    // +0x08
};

struct cGonzagoModel {                     // model attachment at +0x34 of a sim object
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74();
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c();
    virtual bool IsReady();                         // +0x90
    virtual uint32_t v94();
    virtual Vector3* GetModelWorld(const char* name);   // +0x98
    virtual void v9c(); virtual void va0();
    virtual void RefreshModelWorld();                // +0xa4
    virtual void* GetModel();                        // +0xac
};

struct cSelection {                        // selection helper embedded at +0x70
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();            // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void SetHighlightRadius(float radius);   // +0x70
    virtual void v74(); virtual void v78(); virtual void v7c(); virtual void v80();
    virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8();
    virtual void* GetHighlightObject();              // +0xac
};

struct cModelInstance {                    // renderable instance a view owns
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    void SetTransform(const cSPTransform& transform);    // render transform lives at +8
    uint32_t mDrawFlags[8];                // +0x44 bit array (32..63)
};

struct cSimulatorObject {                  // the simulation side a view drives
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cSimulatorObject* GetObjectById(uint32_t id);   // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual uint32_t GetId();                                // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c();
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
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cSimulatorObject* GetSimObject(uint32_t id);     // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual uint32_t GetId();                                // +0x20
    virtual bool IsHighlighted();                            // +0x24
    virtual void v28();
    virtual const Vector3& GetPosition();                    // +0x2c
    virtual const void* GetOrientation();                    // +0x30
    virtual float GetScale();                                // +0x34
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c();
    virtual int GetKind();                                   // +0x60
    virtual void v64(); virtual void v68(); virtual void v6c();
    virtual uint32_t GetModelKeyId();                        // +0x70
    virtual void v74(); virtual void v78(); virtual void v7c(); virtual void v80();
    virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8();
    virtual void* GetHighlightedModel();                     // +0xac
    virtual void vb0(); virtual void vb4();
    virtual cSimulatorObject* GetInteractableObject(uint32_t id);    // +0xb8

    bool mIsSelected;                      // +0x2c? (scene flags live after the vftable)
};

// ---------------------------------------------------------------------------
// effects and render transforms
// ---------------------------------------------------------------------------
struct tEffectParam : IRefCounted {        // EA::Swarm::cResourceOverridesParam
    virtual void v00();
    virtual void Release();                // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30();
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
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void SetTransform(void* pTransform);     // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c();
    virtual void SetLooping(bool looping);           // +0x30
    virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48();
    virtual void AddParam(int slot, tEffectParam* pParam);   // +0x4c
};

struct cSPTransform {                      // render transform handed to an effect
    uint16_t mMask;                        // +0x00
    uint16_t mOrientationMask;             // +0x02
    Vector3 mPosition;                     // +0x04
    Vector3 mOrientation;                  // +0x10
    float mScale;                          // +0x1c
    float mBasis[9];                       // +0x20 (optional 3x3 basis)
};

// ---------------------------------------------------------------------------
// the view hierarchy
// ---------------------------------------------------------------------------
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

struct cEggView : cSpatialObjectView {
    uint32_t mEffectA;                     // +0x34
    uint32_t mEffectB;                     // +0x38

    cEggView() : mEffectA(0), mEffectB(0) { mColor = Vector3(1.0f, 1.0f, 1.0f); }
    void CreateAndStartScaledEffect(uint32_t effectID, uint32_t a, int b);  // 0xe8e420
    virtual void HandleSimulationUpdate(void* a, void* b);                  // 0xe8e5d0
};

struct cNestView : cSpatialObjectView {
    cNestView() { mColor = Vector3(1.0f, 1.0f, 1.0f); }
    virtual void HandleSimulationUpdate(void* a, void* b);                  // 0xe8e220
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

// ---------------------------------------------------------------------------
// externals
// ---------------------------------------------------------------------------
cSimulatorObject* __cdecl GetCurrentSimObject(cSpatialObject* pObject, uint32_t id);  // inline use of +0x0c
void* __cdecl GonzagoModelWorld(void* pModel);                                    // 0xb3d520

cEffect* __cdecl CreateEffectById(uint32_t effectID, uint32_t b);                 // 0xc8ad30
void __cdecl DestroyEffectById(uint32_t effectID, int a);                         // 0xc89d60
void __cdecl FinishEffect(uint32_t effectID);                                     // 0xc8aa60
uint8_t* __cdecl GetCurrentGameMode();                                            // 0xb5b800
bool __cdecl IsInteractionMode();                                                 // 0xc6a020

void* __cdecl GetToolData(uint32_t id);                                           // 0xd37cb0
IRefCounted* __cdecl GetToolByKey(uint32_t key);                                  // 0xb6fa60
void __cdecl SetOtherState(int value, int a);                                     // 0xb3d310
void __cdecl StartToolEffect(cSimulatorObject* pObject, uint32_t a);              // 0xb48770
bool __cdecl CheckToolSlot(cSimulatorObject* pObject, int a);                     // 0xb53940
void __cdecl RefreshToolVisual(cSimulatorObject* pObject);                        // 0xb470b0
void* __cdecl Viewer();                                                           // App()->vtbl+0x58
void __cdecl GetCameraLocation(void* a, float* pOut);                             // 0x7c3d30
void* __cdecl ModelManager();                                                     // 0x?
uint32_t __cdecl GetModelIdForFlash(void* a, int b);                              // ModelManager()->vtbl+0x28


extern uint32_t gModelWorldName;         // 0x015a8890
extern uint32_t gNestModelName;          // 0x015a88a8
extern uint8_t gGameModePlanet;          // 0x01654c01
extern uint8_t gGameModeTerrainModeA;    // 0x01654c04
extern uint8_t gGameModeTerrainModeB;    // 0x01654c05
extern uint32_t gEffectParamA[4];        // 0x015d96fc
extern uint32_t gEffectParamB[4];        // 0x015d99fc
extern uint32_t gEffectParamC[4];        // 0x015d97fc

// ---------------------------------------------------------------------------
// @ 0x00e8e0d0
cEggView* __cdecl CreateEggView(cSpatialObject* pOwner)
{
    cEggView* pView = (cEggView*)operator_new(sizeof(cEggView), "Simulator/cEggView", 0, 0, 0, 0);
    if (pView)
        new (pView) cEggView();
    pView->AttachObject(pOwner);
    return pView;
}

// ---------------------------------------------------------------------------
// @ 0x00e8e160
cNestView* __cdecl CreateNestView(cSimulatorObject* pOwner)
{
    cNestView* pView = (cNestView*)operator_new(sizeof(cNestView), "Simulator/cNestView", 0, 0, 0, 0);
    if (pView)
        new (pView) cNestView();

    cSimulatorObject* pObject = 0;
    if (pOwner)
        pObject = pOwner->GetObjectById(0x1b92b27);
    pObject->SetupNestModelKey();
    void* const pModelWorld = GonzagoModelWorld(pObject->mModel.GetModelWorld((const char*)&gModelWorldName));
    pView->SetModel(pOwner, pModelWorld);
    return pView;
}

// ---------------------------------------------------------------------------
// @ 0x00e8e220
void __thiscall cNestView::HandleSimulationUpdate(void* a, void* b)
{
    cSpatialObject* const pOwner = GetOwner();
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

    cSpatialObjectView::HandleSimulationUpdate(a, b);
}

// ---------------------------------------------------------------------------
// @ 0x00e8e420
void __thiscall cEggView::CreateAndStartScaledEffect(uint32_t effectID, uint32_t a, int b)
{
    cEffect* const pEffect = CreateEffectById(effectID, a);
    if (!pEffect)
        return;

    pEffect->v00();

    cSPTransform transform;
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

// ---------------------------------------------------------------------------
// @ 0x00e8e5d0
void __thiscall cEggView::HandleSimulationUpdate(void* a, void* b)
{
    cSpatialObject* const pOwner = mpObject;
    cSimulatorObject* const pObject = GetOwner()->GetSimObject(0x2a0349a);

    if (pOwner->mIsSelected) {
        pOwner->mIsSelected = false;

        cSPTransform transform;
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

        if (GetCurrentGameMode() == &gGameModePlanet && pOwner->IsHighlighted()) {
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

// ---------------------------------------------------------------------------
// @ 0x00e8eaa0
cOrnamentView::~cOrnamentView()
{
}

// ---------------------------------------------------------------------------
// @ 0x00e8ead0
// cTotemPoleView::cTotemPoleView is defined inline in the class above.

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x00e8efd0
cMineralView::cMineralView()
    : mField34(0), mbLoadingModel(false), mbAnimationsStarted(false),
      mbEffectsInLOD(false)
{
}

// ---------------------------------------------------------------------------
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
