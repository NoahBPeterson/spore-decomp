// slice s0058be50 -- SP::cAppModeEditorBase::HandleSimulationUpdate (4238 B).
// The editor's per-frame tick: idle-timeout check, effect cleanup, manipulator update, sell-back /
// cloning / asymmetry rollovers, physics, deform-handle preview, effects-mask update, UI and palette
// updates, spine/skin/model updates, per-editor verb-icon recomputation, verb-tray sounds, tactility,
// camera auto-zoom, animated creature, idle animations, mouse-move update, hints, tutorials, saving,
// app-switch handling, model sounds, shadow-world centre of interest and the mode cursor.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
// Names follow the 2008 dev build twin (SPAppModeEditorBase.obj) where its calls line up.
#include "types.h"

#pragma warning(disable:4035)
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

#define PV(n) virtual void _v##n();

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
extern const Vector3 kTransformZero;       // @ 0x15e4fd4
extern const Vector3 kCameraFocusDefault;  // @ 0x15e4f18
extern const Vector3 kShadowDirection;     // @ 0x150cd50
extern const float kInvalidAbilityValue;   // @ 0x150cea8

struct Matrix3 {
    float m[9];
    Matrix3(const Matrix3& o);             // @ 0x41cb40 (out of line)
};
extern const Matrix3 kTransformIdentity;   // @ 0x15e5114

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3 mTranslation;
    float mScale;
    Matrix3 mRotation;
    __forceinline cSPTransform()
        : mFlags(0), mModificationCount(0), mTranslation(kTransformZero), mScale(1.0f),
          mRotation(kTransformIdentity) {}
    void SetTranslation(const Vector3& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
};

struct cSPBoundingBox {
    Vector3 mMin, mMax;
    Vector3 GetCenter() const { return (mMin + mMax) * 0.5f; }
};

namespace EA {
#pragma pack(push, 4)
class Stopwatch {
public:
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    bool IsRunning() const { return mnStartTime != 0; }
    uint64_t GetElapsedTime() const;                                  // @ 0x93a5e0
};
#pragma pack(pop)
}

namespace SP {

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();                                            // 0x04
};
template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T** ReleaseAndGetAddressOf()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
typedef AutoRefCount<cPropertyList> PropertyListPtr;
template<class T> struct RefPtr {           // intrusive pointer member (only read here)
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

class cIPropertyManager {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool GetPropertyListRaw(uint32_t instanceID, uint32_t groupID, cPropertyList** ppList);  // 0x2c
    bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& list)
    {
        return GetPropertyListRaw(instanceID, groupID, list.ReleaseAndGetAddressOf());
    }
};
cIPropertyManager* PropertyManager();                                // @ 0x67de30
bool GetPropertyAsInt(const cPropertyList* list, uint32_t id, int* value);               // @ 0x410370
bool GetPropertyAsKeyInstance(const cPropertyList* list, uint32_t id, uint32_t* value);  // @ 0x6a12a0
bool GetPropertyAsVector3(const cPropertyList* list, uint32_t id, Vector3* value);       // @ 0x6a1110

class cDirectPropertyList {
public:
    char pad0[0x3c];
    int* mpDirectValues;                    // +0x3c
    int GetIntProperty(uint32_t id) const;                            // @ 0x6a2660
    bool GetBoolProperty(uint32_t id) const;                          // @ 0x6a25a0
    bool GetDirectBool(int index) const { return mpDirectValues[index] != 0; }
};
extern cDirectPropertyList* sAppProperties;                           // @ 0x15fd918

struct cTestSystem {
    char pad0[0x70];
    struct ListNode { ListNode* mpNext; ListNode* mpPrev; } mTests;  // +0x70
    bool IsTestingInProgress() const { return mTests.mpNext != &mTests; }
};
extern cTestSystem* sTestSystem;                                      // @ 0x15fd928

class cString {
public:
    uint32_t mData[5];
    cString(uint32_t tableID, uint32_t instanceID, const wchar_t* source);  // @ 0x6b5770
    ~cString();                                                       // @ 0x6b5240
    const wchar_t* GetText();                                         // @ 0x6b55c0
};

// ---- editor objects ----
class cSPEditorBlock;
class cSPEditorHandle {
public:
    cSPEditorBlock* GetEditorBlock();                                 // @ 0x47e6c0
};
class cSPEditorHandleBase {
public:
    PV(0) PV(1) PV(2)
    virtual void* Cast(uint32_t typeID);                              // 0x0c
};
template<class T> struct RefPtr;
template<class T, class U> inline T* object_cast(const RefPtr<U>& p)
{
    return p.mpObject ? (T*)p.mpObject->Cast(T::kType) : 0;
}
class cSPEditorHandleDeform : public cSPEditorHandle {
public:
    enum { kType = 0x050a993c };
};

class cSPEditorBlock {
public:
    char pad0[0xdc8];
    uint32_t mBooleanAttributes[2];         // +0xdc8 (eastl::bitset<64>)
    bool HasAttribute(int i) const { bool b = ((mBooleanAttributes[i >> 5] >> (i & 31)) & 1) != 0; return b; }
    int GetIndexForHandle(cSPEditorHandle* handle);                   // @ 0x43c3d0
    void UpdateHandlePreviewDeform(float delta, int index);           // @ 0x43e3f0
    void UpdateEffectsMask();                                         // @ 0x4488c0
    cSPBoundingBox GetBBox(int type, bool a, bool b);                 // @ 0x44ae00
};
enum { kAttrSellable = 1, kAttrHasSellValue = 32 + 5 };
int GetBlockSellValue(cSPEditorBlock* block, int flags);              // @ 0x491350

class cSPEditorModel {
public:
    char pad0[0x58];
    void* mpResource;                       // +0x58
    bool IsModelBalanced();                                           // @ 0x4ad070
    uint32_t GetBlockCount();                                         // @ 0x4accf0
    cSPEditorBlock* GetBlock(uint32_t index);                         // @ 0x4accb0
    void Update(int deltaMS);                                         // @ 0x4ad210
};

class cSPEditorEffect {
public:
    virtual void AddRef();                                            // 0x00
    virtual void Release();                                           // 0x04
    PV(2) PV(3)
    virtual bool IsRunning();                                         // 0x10
    PV(5)
    virtual void SetTransform(cSPTransform* t);                       // 0x18
    PV(7)
    virtual void GetTransform(cSPTransform* t);                       // 0x20
    PV(9) PV(10)
    virtual void Stop(bool hardStop);                                 // 0x2c
};
class cSPEditorEffects {
public:
    cSPEditorEffect* Get(uint32_t id);                                // @ 0x45b210
    cSPEditorEffect* GetForBlock(cSPEditorBlock* block);              // @ 0x45b210
    void Destroy(cSPEditorBlock* block);                              // @ 0x45b150
};
cSPEditorEffects* EditorEffects();                                    // @ 0x401050

class cSPEditorSellBackDetachedRollover {
public:
    bool IsVisible();                                                 // @ 0x5cc100
    void Hide();                                                      // @ 0x5cc0e0
};
class cSPEditorSellBackRollover {
public:
    char pad0[0x78];
    char mCursorAttachment[0x28];           // +0x78 (cursor-attachment window base)
    int mValue;                             // +0xa0
    bool IsVisible();                                                 // @ 0x5cc6c0
    void Hide();                                                      // @ 0x5cc690
    void Show(const wchar_t* text, int value, bool canAfford);        // @ 0x5cc750
};
class cSPEditorAsymmetryRollover {
public:
    char pad0[0x78];
    char mCursorAttachment[4];              // +0x78
    bool IsVisible();                                                 // @ 0x5beeb0
    void Hide();                                                      // @ 0x5bee80
    void Show(const wchar_t* text);                                   // @ 0x5bef50
};
class cSPUICursorManager {
public:
    void SetCursorAttachment(void* window);                           // @ 0x8017f0
};
cSPUICursorManager* CursorManager();                                  // @ 0x67cab0

class cSPEditorManipulator {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual void Update(float delta);                                 // 0x24
};
class cEditorLimits {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    virtual bool CanAfford(cSPEditorBlock* block);                    // 0x34
};
class cIModelWorld {
public:
    PV(0) PV(1) PV(2) PV(3)
    virtual int GetPendingLoadCount();                                // 0x10
};
class cSPEditorPhysicsWorld {
public:
    void UpdatePhysics(int deltaMS);                                  // @ 0x4b95c0
};
class cSPEditorSkinManager {
public:
    struct cSkin { char pad0[8]; void* mpResource; };
    cSkin* GetSkin(int index);                                        // @ 0x4c49e0
    struct cEditorUIState { uint32_t mState[2]; };
    void Update(cSPEditorBlock* active, bool b, cEditorUIState torsoState);  // @ 0x4c38e0
    void UpdatePaintedSkin();                                         // @ 0x4c4290
};
class cSPEditorSpine {
public:
    void Update(int deltaMS, cSPEditorModel* model);                  // @ 0x5d07f0
    void DrawPathDebug();                                             // @ 0xc2e4e0
};
class cSPEditorUI {
public:
    void UpdateIdleTimeout();                                         // @ 0x5dc580
    void Update(int deltaMS);                                         // @ 0x5de450
    class IWindow* FindWindowByID(uint32_t id);                       // @ 0x5dc310
};
class IWindow {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual const float* GetArea();                                   // 0x38
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    virtual void SetArea(const float* area);                          // 0x6c
    PV(28) PV(29) PV(30)
    virtual void SetFlag(int flag, bool value);                       // 0x7c
};
namespace SPUIHelpers {
void AnchorWindowToWindow(IWindow* window, IWindow* anchor, int flags, IWindow* parent);  // @ 0x807340
}
class cSPPlayMode {
public:
    void Update(int deltaMS);                                         // @ 0x62c550
};
class cSPEditorBudget {
public:
    void Update(int deltaMS);                                         // @ 0x4582b0
};
class cSPEditorComplexityMeter {
public:
    void SetComplexityMeterPercentage(float percent);                 // @ 0x5a7410
    void Update(int deltaMS);                                         // @ 0x5a7220
};
class cSPPaletteUI {
public:
    void UpdateCategories(int deltaMS);                               // @ 0x5ca980
};
class cSpeciesProfile {
public:
    uint32_t mData[0xa08 / 4];
    struct cInit { void* mpBegin; void* mpEnd; void* mpCapacity; cInit() : mpBegin(0), mpEnd(0), mpCapacity(0) {} };
    cSpeciesProfile(const cInit& init, int flags);                    // @ 0x4d3dd0
    ~cSpeciesProfile();                                               // @ 0x4d44e0
    bool Update(void* resource);                                      // @ 0x4d5020
};
class cSPPaintPaletteUI {
public:
    void Update(int deltaMS, cSpeciesProfile* profile, int region);   // @ 0x59a980
};
class cSPEditorVerbIconTray {
public:
    uint32_t GetSoundKey();                                           // @ 0x1137690
    float GetTotal();                                                 // @ 0x885d10
};
struct VerbIconList {                       // eastl::vector<AutoRefCount<cSPEditorVerbIconData>>
    void* mpBegin; void* mpEnd; void* mpCapacity;
    VerbIconList() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VerbIconList();                                                  // @ 0x4b5440
};
struct cAbilityValue { int mAbility; float mValue; };
extern "C" void EASTL_allocator_deallocate(void* p);                 // @ 0xf47380
struct AbilityValueList {                   // a plain array buffer released through the EA allocator
    cAbilityValue* mpBegin; cAbilityValue* mpEnd; cAbilityValue* mpCapacity;
    AbilityValueList() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~AbilityValueList() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EASTL_allocator_deallocate(mpBegin); }
    int size() const { return (int)(mpEnd - mpBegin); }
};
class cSPVerbTrayCollection {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void SetIcons(VerbIconList* icons);                       // 0x14
    PV(6)
    virtual void Update(int deltaMS);                                 // 0x1c
    int GetTrayCount();                                               // @ 0x605930
    float GetTotalHeight();                                           // @ 0x6058b0
    cSPEditorVerbIconTray* GetTray(int index);                        // @ 0x5c1ce0
};
namespace EditorUtils {
void PlayEditorSound(uint32_t group, uint32_t instance, float value, int flags);  // @ 0x435f40
void ComputeCellVerbIcons(void* resource, cSPVerbTrayCollection* trays, int region, float value);  // @ 0x4e87f0
void ComputeCreatureVerbIcons(cSPEditorModel* model, cSPVerbTrayCollection* trays);               // @ 0x4e6bc0
void ComputeVehicleVerbIcons(VerbIconList* icons, void* resource);                                 // @ 0x4e7990
void ComputeVehicleAbilityValues(cSPEditorModel* model, AbilityValueList* values);                 // @ 0x4333c0
void ComputeVehicleAbilities(AbilityValueList* values, VerbIconList* icons, void* resource);       // @ 0x4e7610
}
class cEditorTactilityManager {
public:
    PV(0) PV(1)
    virtual void Update(int deltaMS);                                 // 0x08
};
cEditorTactilityManager* EditorTactilityManager();                    // @ 0x401060
class cEditorCameraController {
public:
    void SetCameraOffsetPosition(Vector3 position, bool instant);     // @ 0x5a2010
    void DoAutoZoom(cSPEditorModel* model, int deltaMS);              // @ 0x5a33c0
};
class cCameraManager {
public:
    PV(0) PV(1) PV(2)
    virtual cEditorCameraController* GetCamera(uint32_t id);          // 0x0c
};
class cGameModeManager {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual cCameraManager* GetCameraManager();                       // 0x38
};
class cIGameModeOwner {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual cGameModeManager* GetGameModeManager();                   // 0x50
};
class cSPEditorAnimatedCreatureManager {
public:
    bool GetCreaturePosition(uint32_t creatureID, Vector3* position);  // @ 0x59d110
    void Update(int deltaMS);                                         // @ 0x59d610
    bool IsAnimationPlaying(uint32_t creatureID, uint32_t animID);    // @ 0x59cc40
};
class cUIHints {
public:
    void Update();                                                    // @ 0x67c960
};
cUIHints* UIHints();                                                  // @ 0x67cac0
class cAchievementNotifier {
public:
    void Update();                                                    // @ 0x5fdf40
};
cAchievementNotifier* AchievementNotifier();                          // @ 0x67cae0
class cViewer {
public:
    void GetCameraLocationInfo(Vector3* position, Vector3* direction, Vector3* up, Vector3* right) const;  // @ 0x7c3d30
};
class cRenderer {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual cViewer* GetMainViewer();                                 // 0x1c
};
class cIApp {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual cRenderer* GetRenderer();                                 // 0x50
};
cIApp* App();                                                         // @ 0x67dd10
class cShadowWorld {
public:
    PV(0) PV(1) PV(2)
    virtual void Update();                                            // 0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual void SetDirection(const Vector3* direction);              // 0x30
    PV(13)
    virtual void SetCentreOfInterest(const Vector3* centre, const Vector3* direction);  // 0x38
    virtual void SetEffectiveViewer(const Vector3* cameraPosition);   // 0x3c
    PV(16) PV(17) PV(18)
    virtual uint32_t GetType();                                       // 0x4c
};
class cLightingWorld {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual cPropertyList* GetPropertyList();                         // 0x38
};
class cSPEditorAnimatedEventInfo {
public:
    PV(0)
    virtual int AddRef();                                             // 0x04
    virtual int Release();                                            // 0x08
};

// eastl::map<uint32_t, bool> (only find / operator[] are used)
struct TutorialShownMap {
    struct iterator { void* mpNode; };
    uint32_t mCompare;                      // +0x00 (+0x454 in the editor)
    char mAnchor[0x10];                     // +0x04 (+0x458)
    iterator find(const uint32_t& key);                               // @ 0xe5c780
    bool& operator[](const uint32_t& key);                            // @ 0x5841b0
    bool IsEnd(const iterator& it) { return it.mpNode == (void*)mAnchor; }
};

enum { kModeBuild = 0, kModePaint = 1, kModePlay = 2 };
enum { kSaveStateNone = 0, kSaveStateDone = 6 };
enum { kTransitionWaiting = 1, kTransitionDone = 0 };

class cAppModeEditorBase {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16)
    virtual int GetEditorID();                                        // 0x44
    virtual void HandleSimulationUpdate(float delta1, float delta2);

    uint32_t pad04[7];
    RefPtr<cIGameModeOwner> mpGameModeOwner;               // +0x20
    RefPtr<cPropertyList> mpPropList;                      // +0x24
    float mMouseX;                                  // +0x28
    float mMouseY;                                  // +0x2c
    uint32_t mMouseState;                           // +0x30
    uint32_t pad34[2];
    uint32_t mModifierFlags;                        // +0x3c
    uint32_t pad40[14];
    RefPtr<cSPEditorUI> mpEditorUI;                        // +0x78
    RefPtr<cSPPlayMode> mpPlayMode;                        // +0x7c
    RefPtr<cLightingWorld> mpLightingWorld;                // +0x80
    RefPtr<cIModelWorld> mpMainModelWorld;                 // +0x84
    uint32_t pad88[2];
    RefPtr<cSPEditorPhysicsWorld> mpPhysicsWorld;          // +0x90
    uint32_t pad94;
    RefPtr<cSPEditorModel> mpEditorModel;                  // +0x98
    uint32_t pad9c[12];
    RefPtr<cSPEditorBlock> mpActivePart;                   // +0xcc
    RefPtr<cSPEditorBlock> mpMovingPart;                   // +0xd0
    RefPtr<cSPEditorBlock> mpSelectedPart;                 // +0xd4
    uint32_t padd8[3];
    RefPtr<cSPEditorHandleBase> mpActiveHandle;            // +0xe4
    cSPEditorSkinManager::cEditorUIState mTorsoUIState;  // +0xe8
    uint32_t padf0[20];
    uint8_t pad140;
    bool mbPreviewDeformHandle;                     // +0x141
    bool mbShowCloningRollover;                     // +0x142
    bool mbShowAsymmetryRollover;                   // +0x143
    uint32_t pad144;
    RefPtr<cSPEditorManipulator> mpActiveManipulator;      // +0x148
    RefPtr<cSPEditorSpine> mpSpine;                        // +0x14c
    RefPtr<cSPEditorSkinManager> mpSkinManager;            // +0x150
    uint32_t pad154[16];
    uint32_t mTransitionAnimationID;                // +0x194
    int mTransitionState;                           // +0x198
    uint32_t pad19c[3];
    int mTransitionMode;                            // +0x1a8
    uint32_t pad1ac[8];
    RefPtr<void> mpEditorRequest;                          // +0x1cc
    uint32_t pad1d0[43];
    uint32_t mDeleteEffectID;                       // +0x27c
    uint32_t pad280[5];
    RefPtr<cShadowWorld> mpShadowWorld;                    // +0x294
    uint32_t pad298[3];
    RefPtr<cSPVerbTrayCollection> mpVerbIconTray;          // +0x2a4
    uint32_t mTutorialKey;                          // +0x2a8
    uint32_t pad2ac;
    bool mIsActive;                                 // +0x2b0
    uint8_t pad2b1[0x41];
    bool mbUseSpine;                                // +0x2f2
    uint8_t pad2f3[0x29];
    int mMode;                                      // +0x31c
    uint32_t pad320[11];
    int mCurrentBlockRegion;                        // +0x34c
    RefPtr<cSPEditorBudget> mpBudget;                      // +0x350
    RefPtr<cSPEditorComplexityMeter> mpComplexityMeter;    // +0x354
    uint32_t pad358;
    RefPtr<cSPPaintPaletteUI> mpPaintPaletteUI;            // +0x35c
    RefPtr<cSPEditorAnimatedCreatureManager> mpAnimCreatureManager;  // +0x360
    uint32_t mAnimatingCreatureID;                  // +0x364
    uint32_t pad368[6];
    AutoRefCount<cSPEditorAnimatedEventInfo> mpAnimEvent;  // +0x380
    uint8_t pad384;
    bool mbModelBalanced;                           // +0x385
    uint8_t pad386[2];
    int mPostSaveAction;                            // +0x388
    int mSaveInProgress;                            // +0x38c
    uint32_t pad390[11];
    RefPtr<cSPPaletteUI> mpPartsPaletteUI;                 // +0x3bc
    uint32_t pad3c0;
    RefPtr<cSPPaletteUI> mpPaintCategoriesUI;              // +0x3c4
    uint32_t pad3c8[6];
    bool mIsRecordingGIF;                           // +0x3e0
    bool mbCountGIFFrames;                          // +0x3e1
    uint8_t pad3e2[2];
    int mGIFFrameCount;                             // +0x3e4
    uint32_t pad3e8[19];
    RefPtr<cEditorLimits> mpEditorLimits;                  // +0x434
    uint32_t pad438[7];
    TutorialShownMap mTutorialShown;                // +0x454
    uint32_t pad468[11];
    RefPtr<cSPEditorSellBackRollover> mpSellBackRollover;  // +0x494
    RefPtr<cSPEditorSellBackRollover> mpCloningRollover;   // +0x498
    RefPtr<cSPEditorAsymmetryRollover> mpAsymmetryRollover;  // +0x49c
    uint32_t pad4a0;
    RefPtr<cSPEditorSellBackDetachedRollover> mpDeleteValueRollover;  // +0x4a4
    float mDeleteValueFadeTime;                     // +0x4a8
    uint32_t pad4ac[7];
    bool mbStopDeleteEffects;                       // +0x4c8
    bool mbDrawSpineDebug;                          // +0x4c9
    uint8_t pad4ca[0x5a8 - 0x4ca];
    EA::Stopwatch mIdleStopwatch;                   // +0x5a8

    cSPEditorModel* GetEditorModel() const { return mpEditorModel; }
    cSPEditorSkinManager::cSkin* GetSkin() { return mpSkinManager ? mpSkinManager->GetSkin(1) : 0; }

    void OnIdleTimeout();                                             // @ 0x575120
    void StopFade();                                                  // @ 0x5724a0
    cSPEditorBlock* GetCloningBlock();                                // @ 0x573a10
    float UpdateCurrentComplexityPercent();                           // @ 0x5745c0
    void UpdateSpineVertebra(int deltaMS);                            // @ 0x575520
    void HandleAnimatedEvent(cSPEditorAnimatedEventInfo* info);       // @ 0x585330
    void UpdateBabyCreatures(int deltaMS);                            // @ 0x577e10
    void UpdateAnimatedCreature();                                    // @ 0x57ae10
    void UpdateIdleAnimations(float x, float y, int deltaMS);         // @ 0x57e480
    bool OnMouseMoveUpdate(float x, float y, uint32_t state, int deltaMS);  // @ 0x58ba60
    void ShowTutorial();                                              // @ 0x572260
    void ContinueSaveInProgress();                                    // @ 0x585d40
    void HandleRequestedPostSaveAction();                             // @ 0x57ebf0
    void SendAppSwitchMessage();                                      // @ 0x57c0e0
    void UpdateModelSounds(int deltaMS);                              // @ 0x574f30
    void SetCursorBasedOnModeModifiers();                             // @ 0x5733d0
};

// @ 0x0058be50
void cAppModeEditorBase::HandleSimulationUpdate(float delta1, float delta2)
{
    if (!mIsActive)
        return;

    if (mIdleStopwatch.IsRunning()) {
        int idleTimeout = 2000;
        PropertyListPtr propList;
        if (PropertyManager()->GetPropertyList(0xb55619c2, 0x851d4139, propList))
            GetPropertyAsInt(propList, 0x091756c5, &idleTimeout);
        if (mIdleStopwatch.GetElapsedTime() > idleTimeout) {
            OnIdleTimeout();
            mpEditorUI->UpdateIdleTimeout();
        }
    }

    if (mbStopDeleteEffects) {
        if (mpMainModelWorld && mpMainModelWorld->GetPendingLoadCount() > 0)
            return;
        AutoRefCount<cSPEditorEffect> effect(EditorEffects()->Get(0xb8deeb8b));
        if (effect)
            effect->Stop(false);
        AutoRefCount<cSPEditorEffect> deleteEffect(EditorEffects()->Get(mDeleteEffectID));
        if (deleteEffect)
            deleteEffect->Stop(false);
        mbStopDeleteEffects = false;
    }

    float deltaMS = delta2 * 1000.0f;
    int deltaTime = RoundToInt(delta2 * 1000.0f);

    cSPEditorSkinManager::cSkin* skin;
    if (!(mpAnimCreatureManager && mpSkinManager && (skin = mpSkinManager->GetSkin(1)) != 0)) {
        bool balanced = mpEditorModel->IsModelBalanced();
        if (balanced != mbModelBalanced) {
            mbModelBalanced = balanced;
            if (!balanced)
                StopFade();
        }
    }

    if (mpDeleteValueRollover && mpDeleteValueRollover->IsVisible()) {
        mDeleteValueFadeTime -= delta2;
        if (mDeleteValueFadeTime <= 0.0f)
            mpDeleteValueRollover->Hide();
    }

    if (mpActiveManipulator)
        mpActiveManipulator->Update(deltaMS);

    mbShowCloningRollover = false;
    if (!mpActiveManipulator && (mMouseState & 4) && mMode == kModeBuild)
        mbShowCloningRollover = true;
    if (mpCloningRollover) {
        if (!mbShowCloningRollover && mpCloningRollover->IsVisible()) {
            mpCloningRollover->Hide();
        } else if (mbShowCloningRollover) {
            cSPEditorBlock* block = GetCloningBlock();
            if (block) {
                int value = GetBlockSellValue(block, 2);
                if (!mpCloningRollover->IsVisible() || value != mpCloningRollover->mValue) {
                    bool canAfford = mpEditorLimits->CanAfford(block);
                    cString text(0x496bfb26, 1, L"Copy For ");
                    mpCloningRollover->Show(text.GetText(), value, canAfford);
                    CursorManager()->SetCursorAttachment(
                        mpCloningRollover ? mpCloningRollover->mCursorAttachment : 0);
                }
            }
        }
    }

    mbShowAsymmetryRollover = false;
    if (!mpActiveManipulator && (mModifierFlags & 0x200) && mMode == kModeBuild)
        mbShowAsymmetryRollover = true;
    if (mpAsymmetryRollover) {
        if (!mbShowAsymmetryRollover && mpAsymmetryRollover->IsVisible()) {
            mpAsymmetryRollover->Hide();
        } else if (mbShowAsymmetryRollover) {
            cSPEditorBlock* block = GetCloningBlock();
            if (block) {
                if (!mpAsymmetryRollover->IsVisible()) {
                    cString text(0x496bfb26, 8, L"Make Asymmetric");
                    mpAsymmetryRollover->Show(L"Make Asymmetric");
                    CursorManager()->SetCursorAttachment(
                        mpAsymmetryRollover ? mpAsymmetryRollover->mCursorAttachment : 0);
                }
            } else {
                mpAsymmetryRollover->Hide();
            }
        }
    }

    if (mpPhysicsWorld)
        mpPhysicsWorld->UpdatePhysics(deltaTime);

    if (mpActiveHandle && mbPreviewDeformHandle) {
        cSPEditorHandleDeform* deform = object_cast<cSPEditorHandleDeform>(mpActiveHandle);
        if (deform && deform->GetEditorBlock()) {
            cSPEditorBlock* block = deform->GetEditorBlock();
            block->UpdateHandlePreviewDeform(delta2, block->GetIndexForHandle(deform));
        }
    }

    if (mpSelectedPart)
        mpSelectedPart->UpdateEffectsMask();

    uint32_t sellMode = 0;
    GetPropertyAsKeyInstance(mpPropList, 0xd3a86352, &sellMode);
    if (sellMode) {
        bool sellable = false;
        for (uint32_t i = 0; i < mpEditorModel->GetBlockCount(); i++) {
            cSPEditorBlock* block = mpEditorModel->GetBlock(i);
            if (block->HasAttribute(kAttrHasSellValue) && block->HasAttribute(kAttrSellable)) {
                sellable = true;
                break;
            }
        }
        if (!sellable) {
            if (mpSellBackRollover->IsVisible())
                mpSellBackRollover->Hide();
        } else if (!mpSellBackRollover->IsVisible()) {
            int value = 0;
            if (mpMovingPart)
                value = GetBlockSellValue(mpMovingPart, 1);
            cString text(0x496bfb26, 2, L"Sell For ");
            mpSellBackRollover->Show(text.GetText(), value, true);
            CursorManager()->SetCursorAttachment(
                mpSellBackRollover ? mpSellBackRollover->mCursorAttachment : 0);
        }
    }

    cSPEditorBlock* movingPart = mpMovingPart;
    if (movingPart && EditorEffects()->GetForBlock(movingPart)) {
        cSPEditorEffect* effect = EditorEffects()->GetForBlock(movingPart);
        if (!effect->IsRunning()) {
            EditorEffects()->Destroy(movingPart);
        } else {
            cSPTransform transform;
            effect->GetTransform(&transform);
            transform.SetTranslation(mpMovingPart->GetBBox(0, false, false).GetCenter());
            effect->SetTransform(&transform);
        }
    }

    if (mpVerbIconTray)
        mpVerbIconTray->Update(deltaTime);
    if (mpComplexityMeter) {
        mpComplexityMeter->SetComplexityMeterPercentage(UpdateCurrentComplexityPercent());
        mpComplexityMeter->Update(deltaTime);
    }
    if (mpPaintPaletteUI) {
        cSpeciesProfile::cInit init;
        cSpeciesProfile profile(init, 0);
        if (GetSkin()->mpResource && profile.Update(GetSkin()->mpResource))
            mpPaintPaletteUI->Update(deltaTime, &profile, mCurrentBlockRegion);
        else
            mpPaintPaletteUI->Update(deltaTime, 0, 0);
    }
    if (mpBudget)
        mpBudget->Update(deltaTime);
    if (mpPartsPaletteUI)
        mpPartsPaletteUI->UpdateCategories(deltaTime);
    if (mpPaintCategoriesUI)
        mpPaintCategoriesUI->UpdateCategories(deltaTime);
    if (mpEditorUI)
        mpEditorUI->Update(deltaTime);

    if (mMode == kModeBuild && mbUseSpine && mpSpine) {
        mpSpine->Update(deltaTime, mpEditorModel);
        UpdateSpineVertebra(deltaTime);
    }
    if (mpEditorModel)
        mpEditorModel->Update(deltaTime);
    if (mbDrawSpineDebug && mpSpine)
        mpSpine->DrawPathDebug();

    if (mpSkinManager) {
        if (mMode == kModeBuild)
            mpSkinManager->Update(mpActivePart, false, mTorsoUIState);
        else
            mpSkinManager->UpdatePaintedSkin();
    }

    if (mpAnimEvent) {
        HandleAnimatedEvent(mpAnimEvent);
        mpAnimEvent = 0;
    }

    switch (mMode) {
    case kModeBuild: {
        switch (GetEditorID()) {
        case (int)0xe46c381e: case (int)0x9adf00a9: case (int)0xa56567f7: case (int)0xb7af8ff8: case 0x156276d1:
        case (int)0xfd4902bd: case 0x290adace: case 0x247e2615: case 0x281f5960: case 0x312e9d6a:
        case 0x465c50ba: case 0x37e82da1: case 0x5bf8f774:
        {
            cSPEditorSkinManager::cSkin* skin;
            if (!(sTestSystem && sTestSystem->IsTestingInProgress()) && (skin = GetSkin()) != 0 &&
                mpVerbIconTray)
                EditorUtils::ComputeCellVerbIcons(skin->mpResource, mpVerbIconTray, mCurrentBlockRegion, -1.0f);
            break;
        }
        case 0x1d2ec0a0: case 0x1d2ec0a4: case 0x1d2ec0a5: case 0x1d2ec0a6: case 0x1d2ec0a7:
        case (int)0xef18a560: case 0x3615a30b:
            if (mpVerbIconTray)
                EditorUtils::ComputeCreatureVerbIcons(mpEditorModel, mpVerbIconTray);
            break;
        case (int)0x8f963dcb: case (int)0x99f87089: case (int)0x9ad7d4aa: case (int)0xc0b74287: case (int)0xf670aa43:
        case 0x1a4e0708: case 0x1f2a25b6: case 0x2a5147a9: case 0x441cd3e6: case 0x449c040f:
        case 0x7d433fad:
            if (mpVerbIconTray) {
                AbilityValueList abilities;
                EditorUtils::ComputeVehicleAbilityValues(mpEditorModel, &abilities);
                VerbIconList icons;
                EditorUtils::ComputeVehicleAbilities(&abilities, &icons, mpEditorModel->mpResource);
                mpVerbIconTray->SetIcons(&icons);
                int count = abilities.size();
                for (int i = 0; i < count; i++) {
                    if (abilities.mpBegin[i].mValue != kInvalidAbilityValue) {
                        EditorUtils::PlayEditorSound(0x1d6253c0, 0x766d2f71, (float)i, 0);
                        EditorUtils::PlayEditorSound(0x1d6253c0, 0x447e8ae5, abilities.mpBegin[i].mValue, 0);
                    }
                }
            }
            break;
        default:
            if (mpVerbIconTray) {
                VerbIconList icons;
                EditorUtils::ComputeVehicleVerbIcons(&icons, mpEditorModel->mpResource);
                mpVerbIconTray->SetIcons(&icons);
            }
            break;
        }

        IWindow* trayWindow = mpEditorUI->FindWindowByID(0x0630c829);
        if (trayWindow) {
            if (mpVerbIconTray && mpVerbIconTray->GetTrayCount() > 0) {
                const float* src = trayWindow->GetArea();
                struct Area { float left, top, right, bottom; } area;
                area.left = src[0];
                area.top = src[1];
                area.right = src[2];
                area.bottom = src[3];
                float height = mpVerbIconTray->GetTotalHeight();
                area.bottom = area.top + height + 45.0f;
                trayWindow->SetArea(&area.left);
            } else {
                trayWindow->SetFlag(1, false);
            }
            IWindow* anchor = mpEditorUI->FindWindowByID(0x0760a5d8);
            if (anchor)
                SPUIHelpers::AnchorWindowToWindow(trayWindow, anchor, 0x84, 0);
        }
        break;
    }
    case kModePlay:
        UpdateBabyCreatures(deltaTime);
        mpPlayMode->Update(deltaTime);
        break;
    }

    if (mpVerbIconTray) {
        int trayCount = mpVerbIconTray->GetTrayCount();
        for (int i = 0; i < trayCount; i++) {
            if (mpVerbIconTray->GetTray(i)->GetSoundKey() > 0)
                EditorUtils::PlayEditorSound(0x1d6253c0, mpVerbIconTray->GetTray(i)->GetSoundKey(),
                                             mpVerbIconTray->GetTray(i)->GetTotal(), 0);
        }
    }

    cEditorTactilityManager* tactility = EditorTactilityManager();
    if (tactility)
        tactility->Update(deltaTime);

    cCameraManager* cameraManager = mpGameModeOwner->GetGameModeManager()->GetCameraManager();
    if (cameraManager) {
        cEditorCameraController* camera = cameraManager->GetCamera(0x029da727);
        if (camera) {
            if (mMode == kModePlay) {
                Vector3 position;
                if (mpAnimCreatureManager->GetCreaturePosition(mAnimatingCreatureID, &position))
                    camera->SetCameraOffsetPosition(position, false);
            } else {
                camera->SetCameraOffsetPosition(kCameraFocusDefault, true);
                if (sAppProperties->GetDirectBool(0x31) && !mpActiveManipulator)
                    camera->DoAutoZoom(mpEditorModel, deltaTime);
            }
        }
    }

    if (mpAnimCreatureManager) {
        UpdateAnimatedCreature();
        if (mIsRecordingGIF) {
            uint32_t frameRate = sAppProperties->GetIntProperty(0x05893ee8);
            uint32_t frameTime = sAppProperties->GetIntProperty(0x05893ef5);
            mpAnimCreatureManager->Update(frameTime * 1000 / (frameRate * frameRate));
            if (mbCountGIFFrames)
                mGIFFrameCount++;
        } else {
            mpAnimCreatureManager->Update(deltaTime);
        }
    }

    UpdateIdleAnimations(mMouseX, mMouseY, deltaTime);
    OnMouseMoveUpdate(mMouseX, mMouseY, mMouseState, deltaTime);
    UIHints()->Update();
    if (AchievementNotifier())
        AchievementNotifier()->Update();

    if (mpEditorRequest && sAppProperties->GetBoolProperty(0x05949bf1)) {
        if (mTutorialShown.IsEnd(mTutorialShown.find(mTutorialKey))) {
            mTutorialShown[mTutorialKey] = true;
            ShowTutorial();
        }
    }

    if (mSaveInProgress != kSaveStateNone && mSaveInProgress != kSaveStateDone) {
        ContinueSaveInProgress();
        if (mSaveInProgress == kSaveStateDone) {
            HandleRequestedPostSaveAction();
            mPostSaveAction = 0;
        }
    }

    if (mTransitionMode == kTransitionWaiting) {
        if (mTransitionState == kTransitionWaiting &&
            !mpAnimCreatureManager->IsAnimationPlaying(mAnimatingCreatureID, mTransitionAnimationID))
            mTransitionState = kTransitionDone;
        SendAppSwitchMessage();
    }

    UpdateModelSounds(deltaTime);

    if (mpShadowWorld && mpShadowWorld->GetType() == 0x05e51c99) {
        if (mMode == kModePlay) {
            Vector3 position;
            if (mpAnimCreatureManager->GetCreaturePosition(mAnimatingCreatureID, &position))
                mpShadowWorld->SetCentreOfInterest(&position, &kShadowDirection);
        } else {
            mpShadowWorld->SetCentreOfInterest(&kCameraFocusDefault, &kShadowDirection);
        }
        Vector3 cameraPosition;
        App()->GetRenderer()->GetMainViewer()->GetCameraLocationInfo(&cameraPosition, 0, 0, 0);
        mpShadowWorld->SetEffectiveViewer(&cameraPosition);
        Vector3 direction = kShadowDirection;
        GetPropertyAsVector3(mpLightingWorld->GetPropertyList(), 0x0100eab8, &direction);
        mpShadowWorld->SetDirection(&direction);
        mpShadowWorld->Update();
    }

    SetCursorBasedOnModeModifiers();
}

}  // namespace SP
