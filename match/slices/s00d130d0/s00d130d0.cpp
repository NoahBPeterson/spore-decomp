// Slice s00d130d0 -- SP::cCommunityEditor::HandleMessage (0x00d130d0, 4965 bytes, /O2).
//
// Message dispatcher of the city/colony ("community") editor: palette selection, swatch
// rollovers, editor launches (vehicle/building/tool editors), placement of new buildings,
// vehicles, tribe tools and decorations from the palette, and the first-time UI hints.
// Messages of the shared palette group are forwarded to HandlePaletteMessage (0x00d12910).
//
// Layouts are the retail ones (they differ from the 2008 PDB); members are named from the
// PDB/ModAPI where the role is clear and by offset otherwise.
#include "types.h"

// ---------------------------------------------------------------------------------------
// Common value types
// ---------------------------------------------------------------------------------------
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

struct Quaternion {
    float x, y, z, w;
};

// Placeholder virtual slots (4 bytes each) used to put real virtuals at their retail slots.
#define VS1(n) virtual void n();
#define VS4(n) VS1(n##0) VS1(n##1) VS1(n##2) VS1(n##3)
#define VS16(n) VS4(n##a) VS4(n##b) VS4(n##c) VS4(n##d)

// EA operator new (name + flags); no matching placement delete.
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file,
                   int line);

extern const char kAppAllocName[]; // "App" (0x013ebc58)

namespace EA {

// AutoRefCount<T>: AddRef at slot 0, Release at slot 1 of T.
template <typename T> class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p); // 0x00572660
    ~AutoRefCount()
    {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount& operator=(T* p); // 0x00b5f950
    T** AsPPTypeParam();           // 0x00a16f40
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

} // namespace EA

namespace eastl {

// intrusive_ptr<T>: AddRef at slot 1, Release at slot 2 of T.
template <typename T> class intrusive_ptr {
public:
    T* mpObject;
    intrusive_ptr(T* p); // 0x0061df40
    ~intrusive_ptr() { mpObject->Release(); }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

template <typename T> class vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    void push_back(const T& value); // 0x00454860 (uint32_t), 0x00e1c7f0 (AutoRefCount)
    T& operator[](uint32_t n) { return mpBegin[n]; }
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct wstring {
    uint32_t mData[9];
    wstring& operator=(const wchar_t* p); // 0x005c3d90
};

} // namespace eastl

// ---------------------------------------------------------------------------------------
// Engine objects (only the members and virtual slots this function touches)
// ---------------------------------------------------------------------------------------
namespace SP {

class cCity;
class cTribe;
class cCommunity;
class cSpatialObject;
class cSPPaletteItem;

struct RefObject {
    virtual int AddRef();
    virtual int Release();
};

struct cPropertyList : RefObject {};
struct cSwatch : RefObject {};

class IResource : public RefObject {};

class cEditorResource {
public:
    uint32_t pad00[6];
    uint32_t mModelType; // +0x18
};

class IResourceManager {
public:
    VS1(v00) VS1(v04) VS1(v08)
    virtual bool GetResource(const ResourceKey& name, IResource** ppResource, int arg8, void* pDBPF,
                             void* pFactory, const ResourceKey* pCacheName); // +0x0c
};

class IPropertyManager {
public:
    VS4(v) VS4(w) VS1(x0) VS1(x1) VS1(x2)
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** ppList); // +0x2c
};

class IConfigManager {
public:
    VS4(v) VS4(w) VS4(x)
    virtual uint32_t GetConfigValue(uint32_t id); // +0x30
};

class IApp {
public:
    VS4(v) VS4(w) VS4(x) VS1(y0) VS1(y1)
    virtual uint32_t GetCurrentModeID(); // +0x38
};

class IMessage {
public:
    virtual void v00();
    virtual int AddRef();  // +0x04
    virtual int Release(); // +0x08
};

class IMessageServer {
public:
    VS4(v) VS1(w0)
    virtual void PostMessage(uint32_t messageID, IMessage* pMessage, int flags);           // +0x14
    virtual void MessageSend(uint32_t messageID, void* pData, int flags, void* pHandler); // +0x18
};

class SlotMessage : public IMessage {
public:
    uint32_t pad04;
    int mSlot;           // +0x08
    uint32_t pad0c[9];
    uint32_t mMessageID; // +0x30
    uint32_t pad34[3];
    explicit SlotMessage(int arg); // 0x00421c80
};

namespace Editor {
class cEditorLaunchData : public IMessage {
public:
    uint32_t pad04[2];
    uint32_t mConfig;                   // +0x0c
    ResourceKey mModelKey;              // +0x10
    uint32_t mCallingAppModeID;         // +0x1c
    uint32_t pad20;
    uint32_t mEditorValidationLevel[4]; // +0x24
    bool mCanSwitchEditor;              // +0x34
    bool mUseAlternateName;             // +0x35
    bool mShowLoadButton;               // +0x36
    bool mShowSaveButton;               // +0x37
    bool mShowNewButton;                // +0x38
    bool mConfirmOnExit;                // +0x39
    bool pad3a[2];
    bool mShowPublishButton;            // +0x3c
    bool mAllowNaming;                  // +0x3d
    bool pad3e[2];
    eastl::wstring mAlternateName;      // +0x40
    bool mUsePlanetColors;              // +0x64
    bool pad65[8];
    bool mUseSphere;                    // +0x6d
    bool pad6e[2];
    eastl::vector<uint32_t> mPlanetColors; // +0x70
    uint32_t pad80[4];
    uint32_t mCallerID;                 // +0x90
    EA::AutoRefCount<RefObject> mCallerData; // +0x94
    uint32_t pad98;

    cEditorLaunchData(); // 0x005a9080
};
} // namespace Editor

class cEditorManager {
public:
    void LaunchEditor(Editor::cEditorLaunchData* pData); // 0x00b1dee0
};

class cLocaleTable {
public:
    const wchar_t* GetText(uint32_t id); // 0x00b6a6e0
};

class cTerrainSphere {
public:
    uint32_t pad[0x10fc / 4];
    int mColors[5];      // +0x10fc
    void ShowUIHint(uint32_t hintID); // 0x00c77bf0
};

class cGameNounManager {
public:
    cTerrainSphere* GetCurrentTerrainSphere();      // 0x00f67d90
    void* CreateNoun(uint32_t nounID);              // 0x00b20c60
    void RemoveNoun(uint32_t id);                   // 0x00b225d0
    class cCivilization* GetPlayerCivilization();   // 0x00b25fb0
};

class cGameTimeManager {
public:
    void IncPauseGate(uint32_t id); // 0x00b32220
};

class cTribeModeStrategy {
public:
    uint32_t pad[0x19c / 4];
    EA::AutoRefCount<RefObject> mTribeText; // +0x19c
    uint32_t pad1a0[(0x24c - 0x1a0) / 4];
    uint32_t mEditedToolType;               // +0x24c
    static cTribeModeStrategy* Instance();  // 0x00cd40b0
};

class cEmpire {
public:
    uint32_t pad[3];
    cLocaleTable mNames; // +0x0c
};

class cCivilization {
public:
    VS16(v) VS1(w0) VS1(w1) VS1(w2)
    virtual uint32_t GetModelTypeForItem(uint32_t itemID); // +0x4c
    uint32_t pad04[14];
    struct tGameData {
        cLocaleTable mNames;      // +0x3c (string table lookup at +8)
        uint32_t mPoliticalID;    // +0x40
        uint32_t GetPoliticalID() const { return mPoliticalID; }
    } mData;                      // +0x3c
    void* GetCitizenAudio();      // 0x00bef950
    uint32_t GetModelTypeKey(uint32_t modelType); // 0x00bf9770
    int CanAffordVehicle(int specialty);          // 0x00bf2100
    void* CreateVehicleFromModelType(uint32_t modelType, const ResourceKey& key); // 0x00bf4b10
};

class cCityHall {
public:
    VS16(v) VS4(w) VS4(x)
    virtual void SetCityID(uint32_t id); // +0x60
};

class cCity {
public:
    VS16(v) VS4(w) VS4(x) VS1(y0) VS1(y1) VS1(y2)
    virtual cCityHall* GetCityHall(); // +0x6c
    cCivilization* GetCivilization();         // 0x00bd9bf0
    int GetVehicleSpecialty();                // 0x00bd81d0
    Vector3 GetVehicleSpawnPoint(int locomotion); // 0x00bdca30
    void* CreateBuilding();                   // 0x00be1fb0
    void AddDecoration(void* pObject);        // 0x00be1e80
    void AddBuilding(void* pObject, int arg); // 0x00be1ef0
};

class cCityHallBuildingSet {
public:
    void Refresh(); // 0x00be6f40
};

class cSpatialObject {
public:
    VS4(v) VS4(w) VS1(x0) VS1(x1) VS1(x2)
    virtual void* SetScale(float scale);                  // +0x2c
    virtual const Quaternion& GetOrientation();           // +0x30
    virtual void v34();
    virtual void SetPosition(const Vector3& position);    // +0x38
    virtual void SetOrientation(const Quaternion& q);     // +0x3c
    VS16(z) VS4(q) VS1(r)
    virtual void SetModelKey(uint32_t key);               // +0x94
    virtual void* GetModelWorldPosition();                // +0x98
};

// Tribe tools expose a snap-locator interface at +0x34 (slot +0x2c differs from cSpatialObject).
class cToolSpatial {
public:
    VS4(v) VS4(w) VS1(x0) VS1(x1) VS1(x2)
    virtual int GetSnapLocator(); // +0x2c
};

class cTribeTool {
public:
    VS16(v) VS4(w) VS4(x) VS1(y)
    virtual void SetTribe(cTribe* pTribe); // +0x64
    uint32_t pad04[12];
    cToolSpatial mSpatial;                 // +0x34
    uint32_t pad38[19];
    uint32_t mFlags;                       // +0x84
    uint32_t pad88[6];
    bool padA0[2];
    bool mbIsBeingPlaced;                  // +0xa2
    void Prepare();                        // 0x00c9d140
};

struct tSnapSlot {
    uint32_t data[6];
    void StartEffect(); // 0x00afa0a0
};

class cToolSnapSet {
public:
    uint32_t pad[0x50 / 4];
    tSnapSlot* mpSlots;                       // +0x50
    int FindSlotIndex(int locator);           // 0x00afab70
};

class cTribe {
public:
    VS16(v) VS16(w) VS4(x) VS4(y) VS4(z) VS1(q)
    virtual cTribeTool* CreateTool(uint32_t toolType);   // +0xb4
    virtual void RemoveTool(cTribeTool* pTool);          // +0xb8
    uint32_t pad04[(0x3b4 - 4) / 4];
    cToolSnapSet mToolSnapSet;                           // +0x3b4
    cTribeTool* GetToolOfType(uint32_t toolType);        // 0x00c8f6e0
};

class cBuilding {
public:
    VS16(v) VS4(w) VS1(x)
    virtual void SetCity(cCity* pCity); // +0x54
    uint32_t pad04[12];
    cSpatialObject mSpatial;            // +0x34
    uint32_t pad38[26];
    bool padA0[2];
    bool mbIsBeingPlaced;               // +0xa2
    void* GetModel();                   // 0x00bce470
};

class cBuildingModel {
public:
    void SetRadius(void* p); // 0x00c3f160
};

class cDecoration {
public:
    uint32_t pad[0x70 / 4];
    cSpatialObject mSpatial;            // +0x70
    uint32_t pad74[(0xde - 0x74) / 4];
    bool padDC[2];
    bool mbIsBeingPlaced;               // +0xde
    void SetModelProperty(uint32_t propertyID, uint32_t value); // 0x00c6f770
};

class cVehicle {
public:
    virtual void v00();
    virtual int Release(); // +0x04
    uint32_t pad04[12];
    cSpatialObject mSpatial;            // +0x34
    uint32_t pad38[(0x5d0 - 0x38) / 4];
    uint32_t mBehavior;                 // +0x5d0
    uint32_t pad5d4[(0xb1c - 0x5d4) / 4];
    int mLocomotion;                    // +0xb1c
    int mPurpose;                       // +0xb20
    void SetJustEyeCandy(bool value);   // 0x00c9ecb0
    void SetSpeedBoost(int value);      // 0x00ca80e0
};

class IBehaviorManager {
public:
    VS4(v) VS4(w) VS4(x) VS1(y0) VS1(y1)
    virtual void Track(void* pBehavior); // +0x38
};

class IGameInputManager {
public:
    VS16(v) VS4(w) VS4(x) VS1(y)
    virtual void SetCursor(int cursorID, int arg); // +0x64
};

class IWindow {
public:
    VS4(v) VS1(w0) VS1(w1)
    virtual void SetFlag(int flag, int value); // +0x18
};

class cSellBackRollover {
public:
    VS1(v0) VS1(v1)
    virtual void Hide(); // +0x08
};

class ICameraManager {
public:
    VS4(v) VS4(w) VS4(x) VS1(y0) VS1(y1)
    virtual Vector3 Pick(int mode, Vector3 screen); // +0x38
};

class cPlanetModel {
public:
    Vector3 ToSurface(const Vector3& pos);                           // 0x00b81630
    Quaternion GetSurfaceOrientation(const Vector3& pos, const Quaternion& q); // 0x00b7f1f0
};

class cAudioState {};
class cSpaceInventory {
public:
    uint32_t pad[3];
    struct { uint32_t pad[7]; float mValue; }* mpData; // +0x0c
    void SetMode(int mode);                           // 0x007eb820
};

class cSimulatorSpaceGame {
public:
    cSpaceInventory* GetInventory(int which); // 0x01005180
    class cGameData* GetPlayerTribe(int arg); // 0x00bfc5f0
};

class cGameData {
public:
    void SetGameDataOwner(int arg); // 0x00fe5430
};

class cPlanetSurface {
public:
    VS16(v) VS1(w0) VS1(w1) VS1(w2)
    virtual void* GetSurfaceData(); // +0x4c
};

class cPlanet {
public:
    uint32_t pad[0xd4 / 4];
    cPlanetSurface mSurface;     // +0xd4
    bool IsHomeworld();          // 0x00c70b50
};

class cCivModeStrategy {
public:
    void OnVehicleCreated(cVehicle* pVehicle);         // 0x00cf8ec0
    void DoNextCivTutorial(uint32_t id, int arg);      // 0x00cfa990
};

class cUIHintManager {
public:
    void ShowHint(ResourceKey key, const void* pLayout, int arg, Vector3 position, int arg2,
                  int arg3);                           // 0x0067aaf0
};

class cUIHints {
public:
    void SetEnabled(int arg, int enabled);             // 0x0067c420
};

class cRotationRing {
public:
    void SetVisibility(bool visible); // 0x00ea0010
};

class cSPPaletteUI {
public:
    int FindCategoryIndex(); // 0x005ca9c0
};

class cSPPaletteItem {
public:
    uint32_t pad[3];
    uint32_t mInstanceID; // +0x0c
    uint32_t pad10;
    uint32_t mGroupID;    // +0x14
    uint32_t pad18[3];
    uint32_t mItemType;   // +0x24
};

class cCommunity {};

// Free helpers
cTribe* GetTribe(cCommunity* const& pCommunity);  // 0x00d08ee0 (Cast 0x4f396a66)
cCity* GetCity(cCommunity* const& pCommunity);    // 0x00d08ec0 (Cast 0xee9b2232)
uint32_t GetModelType(cSPPaletteItem* pItem);     // 0x00d0a6e0
uint32_t GetEditorConfigFromModelType(uint32_t modelType); // 0x00432f10
cGameNounManager* NounManager();                  // 0x00b3d300
cEditorManager* EditorManager();                  // 0x00b3d320
IApp* App();                                      // 0x0067dd10
IConfigManager* ConfigManager();                  // 0x0067dd30
IMessageServer* MessageServer();                  // 0x0067dcc0
IResourceManager* ResourceManager();              // 0x0067dcd0
IPropertyManager* PropertyManager();              // 0x0067de30
cGameTimeManager* GameTimeManager();              // 0x00b3d380
IGameInputManager* GameInputManager();            // 0x00b3d250
IBehaviorManager* BehaviorManager();              // 0x00b3d260
ICameraManager* CameraManager();                  // 0x00b3d240
cPlanetModel* PlanetModel();                      // 0x00b3d350
uint32_t GetCurrentGameMode();                    // 0x00b5b800
cEmpire* GetPlayerEmpire();                       // 0x01021300
cPlanet* GetActivePlanet();                       // 0x01021260
cSimulatorSpaceGame* SpaceGame();                 // 0x01002bd0
cCivModeStrategy* CivModeStrategy();              // 0x00cf74c0
cUIHintManager* UIHintManager();                  // 0x0067caf0
cUIHints* UIHints();                              // 0x0067cac0
cAudioState* GetAudioState();                     // 0x00435e90
void PlayAudio(uint32_t soundID, cAudioState* pState); // 0x00435ed0
cVehicle* AsVehicle(cSpatialObject* pObject);     // 0x00b33e60
void SetBeingPlaced(void* pObject, bool value);   // 0x00ba57a0
float GetHomeTerrainScore(void* pSurface);        // 0x00bce400
float GetTerrainScore(void* pSurface);            // 0x00bcde40
void PlayVehicleAudio(uint32_t eventID, void* pAudio, void* pPosition, const Vector3& offset,
                      uint32_t politicalID, int arg6, int arg7); // 0x00e3c7c0
bool GetPropertyAsUint32(cPropertyList* pList, uint32_t id, uint32_t& value);   // 0x004af210
bool GetPropertyAsKeyInstance(cPropertyList* pList, uint32_t id, uint32_t& value); // 0x006a12a0
cSPPaletteItem* interface_cast_PaletteItem(EA::AutoRefCount<RefObject>* p);    // 0x005767b0
cEditorResource* interface_cast_EditorResource(EA::AutoRefCount<IResource>* p); // 0x00421eb0

extern const ResourceKey kVehicleHintKey;   // 0x01582544
extern const ResourceKey kBuildingHintKey;  // 0x01582574
extern const void* const kHintLayout;       // 0x015825c8
extern const uint32_t kDefaultValidationLevel[4]; // 0x015da7c4
extern const float kToolScale;              // 0x014853e0 (4.0)

// Message payloads
struct tPaletteSelectMessage {
    uint32_t pad[5];
    uint32_t mModelType;   // +0x14
    ResourceKey mKey;      // +0x18
    uint32_t pad24[8];
    uint32_t mPaletteInstance; // +0x44
};

struct tEditModelMessage {
    uint32_t pad[3];
    uint32_t mConfig;      // +0x0c
    ResourceKey mKey;      // +0x10
    uint32_t mToolType;    // +0x1c
};

struct tShopMessage {
    uint32_t mModelType;   // +0x00
    uint32_t pad04;
    int mMode;             // +0x08
};

struct tPaletteItemMessage {
    uint32_t pad[8];
    EA::AutoRefCount<RefObject> mItem; // +0x20
};

class cCommunityEditor {
public:
    virtual void v00();
    virtual void v04();
    virtual int Release(); // +0x08
    uint32_t pad04[(0x40 - 4) / 4];
    cCommunity* mpCommunity;                 // +0x40
    uint32_t pad44[2];
    uint32_t mRecentlyEditedModelType;       // +0x4c
    ResourceKey mRecentlyEditedModelKey;     // +0x50 (instance, type, group)
    uint8_t mPaletteInstance;                // +0x5c
    uint8_t pad5d[3];
    uint32_t mShoppingModelType;             // +0x60
    uint32_t pad64;
    IWindow* mpWinBudget;                    // +0x68
    uint32_t pad6c[4];
    cSellBackRollover* mpSellbackRollover;   // +0x7c
    uint32_t pad80[11];
    cRotationRing* mpRotationRing;           // +0xac
    uint32_t padb0;
    cSPPaletteUI* mpPaletteUI;               // +0xb4
    uint32_t padb8;
    uint32_t mRotationAnchorNoun;            // +0xbc
    cSpatialObject* mpManipulatedObject;     // +0xc0
    uint32_t mRotationAnchorFlags;           // +0xc4
    uint32_t mAnchorState;                   // +0xc8
    uint32_t padcc[7];
    Vector3 mCursorScreenPos;                // +0xe8
    uint32_t padf4;
    int mSnapIndices[4];                     // +0xf8
    uint32_t pad108[(0x1f0 - 0x108) / 4];
    eastl::vector<EA::AutoRefCount<cVehicle> > mPlacedVehicles; // +0x1f0
    uint32_t pad200[2];
    bool mbIsShutDown;                       // +0x208

    bool HandleMessage(uint32_t messageID, void* pMessage);
    bool HandlePaletteMessage(uint32_t messageID, void* pMessage);          // 0x00d12910
    const ResourceKey* GetKeyForModelType(uint32_t modelType);              // 0x00d09600
    void SetupShoppingUI(uint32_t modelType, ResourceKey key, int arg);     // 0x00d08b50
    void HandleSwatchRolloverOff(cSwatch* pSwatch);                  // 0x00d0def0
    void HandleSwatchRolloverOn(cSwatch* pSwatch);                     // 0x00d0e0c0
    void UpdateSwatchForModelType(uint32_t modelType, const ResourceKey& key, int arg); // 0x00d0c820
    void UpdateLimitMeter(int category);                                    // 0x00d0a1e0
    const Vector3* GetCommunityCenter(int arg);                             // 0x00d09960
    void SetCameraTarget(Vector3 position);                                 // 0x00d08aa0
    cVehicle* CreateVehicle(uint32_t modelType);                            // 0x00d091c0
    void SetManipulatedObject(cSpatialObject* pObject);                     // 0x00d09f60
    void SetObjectSpecificData();                                           // 0x00d09ad0
    void UpdateVehicleList();                                               // 0x00d0c010
    int GetObjectCost(cSpatialObject* pObject, int arg, int modelType);     // 0x00d0abd0
    void PlaceVehicle(cVehicle* pVehicle);                                  // 0x00d0d570
    void UpdateSnapping();                                                  // 0x00d0db30
    void UpdatePlacementEffects();                                          // 0x00d0a540

    __forceinline void ClearRotationAnchor()
    {
        uint32_t noun = mRotationAnchorNoun;
        mRotationAnchorFlags = 0;
        if (noun) {
            NounManager()->RemoveNoun(noun);
            mRotationAnchorNoun = 0;
        }
    }
};

// Shared tail of the two "first vehicle / first building" hint messages.
static __forceinline void ShowFirstTimeHint(const ResourceKey& key)
{
    GameTimeManager()->IncPauseGate(0x4bf38a7);
    UIHintManager()->ShowHint(key, &kHintLayout, 0, Vector3(-1.0f, -1.0f, 0.0f), 0, 0);
    UIHints()->SetEnabled(0, 1);
}

static bool sVehicleHintShown;  // 0x0169d587
static bool sBuildingHintShown; // 0x0169d584
static bool sDecorHintShown;    // 0x0169d588

// @ 0x00d130d0
bool cCommunityEditor::HandleMessage(uint32_t messageID, void* pMessage)
{
    if (messageID == 0x30c11c7) {
        if (pMessage) {
            tPaletteSelectMessage* pSel = (tPaletteSelectMessage*)pMessage;
            mRecentlyEditedModelType = pSel->mModelType;
            mRecentlyEditedModelKey.instanceID = pSel->mKey.instanceID;
            mRecentlyEditedModelKey.typeID = pSel->mKey.typeID;
            mRecentlyEditedModelKey.groupID = pSel->mKey.groupID;
            mPaletteInstance = (uint8_t)pSel->mPaletteInstance;
        }
        return false;
    }

    if (messageID == 0x71d4dfc3 || messageID == 0x71d4dfc4 || messageID == 0x71d4dfc5 ||
        messageID == 0x71d4dfc6 || messageID == 0x71d4dfc7 || messageID == 0x62ec2a6 ||
        messageID == 0x609ea30 || messageID == 0x71d4dfcd || messageID == 0x71d4dfce ||
        messageID == 0x332a303a || messageID == 0x71d4dfca || messageID == 0x71d4dfcc ||
        messageID == 0x71d4dfcb || messageID == 0x332a303b)
        return HandlePaletteMessage(messageID, pMessage);

    if (!mpCommunity)
        return false;
    if (mbIsShutDown)
        return false;

    cSpatialObject* pObject = 0;
    bool bPlaced = false;
    bool bSetCursor = true;
    int vehicleModelType = -1;
    int cursorID = 0;
    cTribe* pTribe = GetTribe(mpCommunity);
    cCity* pCity = GetCity(mpCommunity);

    if (messageID == 0x53850bae) {
        tEditModelMessage* pEdit = (tEditModelMessage*)pMessage;
        if (!pEdit)
            return false;
        cTerrainSphere* pSphere = NounManager()->GetCurrentTerrainSphere();
        mRecentlyEditedModelKey.instanceID = pEdit->mKey.instanceID;
        mRecentlyEditedModelKey.typeID = pEdit->mKey.typeID;
        mRecentlyEditedModelKey.groupID = pEdit->mKey.groupID;

        eastl::intrusive_ptr<Editor::cEditorLaunchData> pLaunchData(
            new (kAppAllocName, 0, 0, 0, 0) Editor::cEditorLaunchData());
        Editor::cEditorLaunchData* pData = pLaunchData.get();
        pData->mModelKey.instanceID = pEdit->mKey.instanceID;
        pData->mModelKey.typeID = pEdit->mKey.typeID;
        pData->mModelKey.groupID = pEdit->mKey.groupID;
        pData->mConfig = pEdit->mConfig;
        if (pData->mCallerData.mpObject) {
            RefObject* pOld = pData->mCallerData.mpObject;
            pData->mCallerData.mpObject = 0;
            pOld->Release();
        }
        pData->mEditorValidationLevel[0] = kDefaultValidationLevel[0];
        pData->mEditorValidationLevel[1] = kDefaultValidationLevel[1];
        pData->mEditorValidationLevel[2] = kDefaultValidationLevel[2];
        pData->mEditorValidationLevel[3] = kDefaultValidationLevel[3];
        pData->mUseAlternateName = true;
        pData->mCanSwitchEditor = false;
        pData->mShowLoadButton = false;
        pData->mShowNewButton = false;
        pData->mShowSaveButton = false;
        pData->mConfirmOnExit = false;
        pData->mShowPublishButton = true;
        pData->mUseSphere = true;
        pData->mPlanetColors.push_back(pSphere->mColors[0]);
        pData->mPlanetColors.push_back(pSphere->mColors[1]);
        pData->mPlanetColors.push_back(pSphere->mColors[2]);
        pData->mPlanetColors.push_back(pSphere->mColors[3]);
        pData->mPlanetColors.push_back(pSphere->mColors[4]);

        if (pTribe) {
            pData->mCallerID = 0x116dd1b;
            uint32_t toolType = pEdit->mToolType;
            cTribeModeStrategy::Instance()->mEditedToolType = toolType;
            pData->mAlternateName = ((cLocaleTable*)((char*)pTribe + 0x230))->GetText(0xf);
            pData->mAllowNaming = false;
            pData->mUsePlanetColors = false;
            pData->mCallerData = (RefObject*)cTribeModeStrategy::Instance()->mTribeText;
        } else if (pCity) {
            if (GetCurrentGameMode() == 0x1654c05) {
                pData->mCallerID = 0x66787bc;
                pData->mAlternateName = GetPlayerEmpire()->mNames.GetText(0x11);
                pData->mAllowNaming = true;
            } else {
                pData->mCallerID = 0x66787bb;
                pData->mAlternateName = pCity->GetCivilization()->mData.mNames.GetText(0x10);
                pData->mAllowNaming = false;
            }
            pData->mUsePlanetColors = true;
        }
        EditorManager()->LaunchEditor(pData);
        return false;
    }

    if (pCity) {
        if (messageID == 0x133b269e) {
            if (pMessage) {
                cSPPaletteItem* pItem =
                    interface_cast_PaletteItem(&((tPaletteItemMessage*)pMessage)->mItem);
                if (pItem) {
                    ClearRotationAnchor();
                    uint32_t modelType = GetModelType(pItem);
                    mShoppingModelType = modelType;
                    SetupShoppingUI(modelType, *GetKeyForModelType(modelType), 0);
                }
            }
            return false;
        }
        if (messageID == 0x4a314e6) {
            tShopMessage* pShop = (tShopMessage*)pMessage;
            uint32_t modelType = pShop->mModelType;
            ResourceKey key;
            key.instanceID = 0;
            key.typeID = 0;
            key.groupID = 0;
            if (pShop->mMode == 1)
                key = *GetKeyForModelType(modelType);
            mRecentlyEditedModelType = modelType;
            uint32_t config = GetEditorConfigFromModelType(modelType);
            cTerrainSphere* pSphere = NounManager()->GetCurrentTerrainSphere();

            eastl::intrusive_ptr<Editor::cEditorLaunchData> pLaunchData(
                new (kAppAllocName, 0, 0, 0, 0) Editor::cEditorLaunchData());
            uint32_t modeID = App()->GetCurrentModeID();
            Editor::cEditorLaunchData* pData = pLaunchData.get();
            pData->mCallingAppModeID = modeID;
            pData->mModelKey = key;
            pData->mConfig = config;
            pData->mCallerID = 0x91d4af08;
            pData->mShowLoadButton = true;
            pData->mShowNewButton = true;
            pData->mShowSaveButton = true;
            pData->mConfirmOnExit = false;
            pData->mShowPublishButton = true;
            pData->mAllowNaming = true;
            pData->mEditorValidationLevel[0] = kDefaultValidationLevel[0];
            pData->mEditorValidationLevel[1] = kDefaultValidationLevel[1];
            pData->mEditorValidationLevel[2] = kDefaultValidationLevel[2];
            pData->mEditorValidationLevel[3] = kDefaultValidationLevel[3];
            pData->mUsePlanetColors = true;
            pData->mUseSphere = true;
            pData->mPlanetColors.push_back(pSphere->mColors[0]);
            pData->mPlanetColors.push_back(pSphere->mColors[1]);
            pData->mPlanetColors.push_back(pSphere->mColors[2]);
            pData->mPlanetColors.push_back(pSphere->mColors[3]);
            pData->mPlanetColors.push_back(pSphere->mColors[4]);
            EditorManager()->LaunchEditor(pData);
            return true;
        }
    }

    if (messageID == 0x522f9cd) {
        EA::AutoRefCount<cSwatch> pRollover(*(cSwatch**)pMessage);
        HandleSwatchRolloverOff(pRollover);
        return true;
    }
    if (messageID == 0x522f9ce) {
        EA::AutoRefCount<cSwatch> pRollover(*(cSwatch**)pMessage);
        HandleSwatchRolloverOn(pRollover);
        return true;
    }

    switch (messageID) {
    case 0x44ef2b8: {
        int category = mpPaletteUI->FindCategoryIndex();
        if (mpRotationRing && mpPaletteUI) {
            GetCurrentGameMode();
            mpRotationRing->SetVisibility(category == 3);
        }
        UpdateLimitMeter(category);
        SetCameraTarget(*GetCommunityCenter(0));
        if (GetCurrentGameMode() == 0x1654c05)
            return false;
        if (!pCity)
            return false;
        if (category == 0) {
            NounManager()->GetCurrentTerrainSphere()->ShowUIHint(0x566493f);
            if (sVehicleHintShown)
                return false;
            sVehicleHintShown = true;
            eastl::intrusive_ptr<SlotMessage> pHint(new (kAppAllocName, 0, 0, 0, 0) SlotMessage(0));
            SlotMessage* pMsg = pHint.get();
            pMsg->mMessageID = 0x63c0580;
            pMsg->mSlot = -15;
            MessageServer()->PostMessage(pMsg->mMessageID, pMsg, 0);
        } else if (category == 1) {
            NounManager()->GetCurrentTerrainSphere()->ShowUIHint(0x566492c);
            if (GetCurrentGameMode() == 0x1654c05)
                return false;
            if (sBuildingHintShown)
                return false;
            sBuildingHintShown = true;
            eastl::intrusive_ptr<SlotMessage> pHint(new (kAppAllocName, 0, 0, 0, 0) SlotMessage(0));
            SlotMessage* pMsg = pHint.get();
            pMsg->mMessageID = 0x63c0504;
            pMsg->mSlot = -15;
            MessageServer()->PostMessage(pMsg->mMessageID, pMsg, 0);
        }
        return false;
    }

    case 0x5132389: {
        eastl::vector<ResourceKey>* pKeys = *(eastl::vector<ResourceKey>**)pMessage;
        EA::AutoRefCount<IResource> pResource;
        if (!pKeys)
            return false;
        int count = pKeys->size();
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                ResourceKey key = (*pKeys)[i];
                if (ResourceManager()->GetResource(key, pResource.AsPPTypeParam(), 0, 0, 0, 0)) {
                    cEditorResource* pEditorResource = interface_cast_EditorResource(&pResource);
                    if (pEditorResource) {
                        pCity->GetCivilization()->CreateVehicleFromModelType(
                            pEditorResource->mModelType, key);
                        UpdateSwatchForModelType(pEditorResource->mModelType, key, 0);
                    }
                }
            }
        }
        return false;
    }

    case 0x63bdfbe:
        if (ConfigManager()->GetConfigValue(0x4ea96cb))
            ShowFirstTimeHint(kVehicleHintKey);
        return false;

    case 0x63c0504:
    case 0x63c0580:
        if (!sDecorHintShown) {
            sDecorHintShown = true;
            if (ConfigManager()->GetConfigValue(0x4ea96cb) > 0)
                ShowFirstTimeHint(kBuildingHintKey);
        }
        return false;

    case 0xb2e18705: {
        cSPPaletteItem* pItem =
            interface_cast_PaletteItem(&((tPaletteItemMessage*)pMessage)->mItem);
        uint32_t modelType = GetModelType(pItem);

        switch (pItem->mItemType) {
        case 0x2b885df4: // city hall decoration set
            if (!pCity)
                return false;
            if (!pCity->GetCityHall())
                return false;
            pCity->GetCityHall()->SetCityID(pItem->mInstanceID);
            ((cCityHallBuildingSet*)pCity)->Refresh();
            return false;

        case 0xfcafd26: { // tribe tool
            if (!pTribe)
                return false;
            EA::AutoRefCount<cPropertyList> pProps;
            uint32_t toolType = 0;
            if (PropertyManager()->GetPropertyList(pItem->mInstanceID, pItem->mGroupID,
                                                   pProps.AsPPTypeParam()) &&
                (GetPropertyAsUint32(pProps, 0x4294750, toolType), toolType)) {
                cTribeTool* pOldTool = pTribe->GetToolOfType(toolType);
                cTribeTool* pTool = pTribe->CreateTool(toolType);
                if (pTool) {
                    pTool->mFlags |= 8;
                    pObject = (cSpatialObject*)&pTool->mSpatial;
                    bPlaced = true;
                    pTool->SetTribe(pTribe);
                    pTool->Prepare();
                    SetManipulatedObject(pObject);
                    pTool->mbIsBeingPlaced = true;
                    cursorID = 0x3e84;
                    cToolSnapSet* pSnapSet = &pTribe->mToolSnapSet;
                    if (pOldTool && pSnapSet) {
                        int slot = pSnapSet->FindSlotIndex(pOldTool->mSpatial.GetSnapLocator());
                        pSnapSet->mpSlots[slot].StartEffect();
                        pTribe->RemoveTool(pOldTool);
                    }
                }
            }
            break;
        }

        case 0x142462a: { // building
            if (!pCity)
                return false;
            cBuilding* pBuilding = (cBuilding*)pCity->CreateBuilding();
            if (!pBuilding)
                return false;
            pObject = &pBuilding->mSpatial;
            bSetCursor = true;
            pBuilding->mbIsBeingPlaced = true;
            if (pBuilding->GetModel())
                ((cBuildingModel*)pBuilding->GetModel())->SetRadius(pObject->SetScale(kToolScale));
            SetManipulatedObject(pObject);
            cursorID = 0x3e81;
            if (GetCurrentGameMode() == 0x1654c05) {
                cSpaceInventory* pInventory = SpaceGame()->GetInventory(0x12);
                pInventory->SetMode(8);
                pInventory->mpData->mValue =
                    GetHomeTerrainScore(GetActivePlanet()->mSurface.GetSurfaceData());
            }
            goto placed;
        }

        case 0x4d863c8b: { // decoration
            if (!pCity)
                return false;
            cDecoration* pDecor = (cDecoration*)NounManager()->CreateNoun(0x18c88e4);
            if (!pDecor)
                return false;
            pObject = &pDecor->mSpatial;
            pDecor->SetModelProperty(0x2ae5ba7,
                                     pCity->GetCivilization()->GetModelTypeForItem(pItem->mInstanceID));
            pDecor->mbIsBeingPlaced = true;
            pCity->AddDecoration(pDecor);
            SetManipulatedObject(pObject);
            cursorID = 0x3e83;
            SetObjectSpecificData();
            goto placed;
        }

        case 0x8bfac054: { // vehicle
            if (!pCity)
                return false;
            if (modelType == (uint32_t)-1)
                return false;
            if (!pCity->GetCivilization()->CanAffordVehicle(pCity->GetVehicleSpecialty())) {
                MessageServer()->MessageSend(0x2cb6a8f, 0, 0, 0);
                return false;
            }
            vehicleModelType = modelType;
            cVehicle* pVehicle = CreateVehicle(modelType);
            if (!pVehicle)
                return false;
            pObject = &pVehicle->mSpatial;
            EA::AutoRefCount<cPropertyList> pProps;
            bool bSpawnAtPoint = false;
            uint32_t vehicleKind;
            bool bSpawn = bSpawnAtPoint;
            if (PropertyManager()->GetPropertyList(pItem->mInstanceID, pItem->mGroupID,
                                                   pProps.AsPPTypeParam()) &&
                GetPropertyAsKeyInstance(pProps, 0x57fb25a, vehicleKind) &&
                vehicleKind == 0x5e71ab9b)
                bSpawn = true;
            SetManipulatedObject(pObject);
            if (!bSpawn) {
                cursorID = 0x3e85;
            } else {
                pObject->SetPosition(pCity->GetVehicleSpawnPoint(pVehicle->mLocomotion));
                pVehicle->SetSpeedBoost(10);
                bSetCursor = false;
            }
            UpdateVehicleList();
            {
                EA::AutoRefCount<cVehicle> pRef(pVehicle);
                mPlacedVehicles.push_back(pRef);
            }
            SetBeingPlaced(pVehicle, true);
            if (GetCurrentGameMode() == 0x1654c05) {
                pVehicle->SetJustEyeCandy(true);
                IBehaviorManager* pBehaviors = BehaviorManager();
                if (pBehaviors)
                    pBehaviors->Track(&pVehicle->mBehavior);
            } else {
                CivModeStrategy()->OnVehicleCreated(pVehicle);
                uint32_t eventID = 0x703af052;
                switch (pVehicle->mLocomotion) {
                case 0:
                    switch (pVehicle->mPurpose) {
                    case 1: eventID = 0xad067a5e; break;
                    case 2: eventID = 0xe7454134; break;
                    }
                    break;
                case 1:
                    CivModeStrategy()->DoNextCivTutorial(0x6d3814ed, 0);
                    switch (pVehicle->mPurpose) {
                    case 0: eventID = 0x300602f6; break;
                    case 1: eventID = 0x10d02b2a; break;
                    case 2: eventID = 0x8b3fcdf4; break;
                    }
                    break;
                case 2:
                    CivModeStrategy()->DoNextCivTutorial(0xced8b9d4, 0);
                    switch (pVehicle->mPurpose) {
                    case 0: eventID = 0xf5195d53; break;
                    case 1: eventID = 0x1181713f; break;
                    case 2: eventID = 0x1ca7441; break;
                    }
                    break;
                }
                PlayVehicleAudio(eventID,
                                 (char*)NounManager()->GetPlayerCivilization()->GetCitizenAudio() +
                                     0x504,
                                 pObject->GetModelWorldPosition(), Vector3(0.0f, 0.0f, 0.0f),
                                 NounManager()->GetPlayerCivilization()->mData.GetPoliticalID(), 0, 0);
            }
            goto placed;
        }

        case 0x81c74dbc: { // creature / citizen
            if (!pCity)
                return false;
            uint32_t nounID = 0;
            EA::AutoRefCount<cPropertyList> pProps;
            if (PropertyManager()->GetPropertyList(pItem->mInstanceID, pItem->mGroupID,
                                                   pProps.AsPPTypeParam()))
                GetPropertyAsKeyInstance(pProps, 0x456b66a, nounID);
            if (nounID && modelType != (uint32_t)-1) {
                cBuilding* pNoun = (cBuilding*)NounManager()->CreateNoun(nounID);
                if (pNoun) {
                    bPlaced = true;
                    pObject = &pNoun->mSpatial;
                    pNoun->SetCity(pCity);
                    pNoun->mbIsBeingPlaced = true;
                    pObject->SetModelKey(pCity->GetCivilization()->GetModelTypeKey(modelType));
                    pCity->AddBuilding(pNoun, 0);
                    if (GetCurrentGameMode() == 0x1654c05) {
                        cSpaceInventory* pInventory = SpaceGame()->GetInventory(0x11);
                        pInventory->SetMode(8);
                        pInventory->mpData->mValue =
                            GetTerrainScore(GetActivePlanet()->mSurface.GetSurfaceData());
                        if (!GetActivePlanet()->IsHomeworld())
                            SpaceGame()->GetPlayerTribe(0)->SetGameDataOwner(1);
                    }
                    SetBeingPlaced(pNoun, true);
                    SetManipulatedObject(pObject);
                    cursorID = 0x3e82;
                }
            }
            break;
        }

        default:
            return false;
        }

        if (!bPlaced)
            return false;

    placed:
        mpWinBudget->SetFlag(0, -GetObjectCost(pObject, 0, vehicleModelType));
        PlayAudio(0x3d2f6e8e, GetAudioState());
        if (bSetCursor)
            GameInputManager()->SetCursor(cursorID, 1);
        ClearRotationAnchor();
        mAnchorState = 0;
        SetObjectSpecificData();
        mSnapIndices[0] = -1;
        mSnapIndices[1] = -1;
        mSnapIndices[2] = -1;
        mSnapIndices[3] = -1;
        if (bSetCursor) {
            EA::AutoRefCount<cVehicle> pVehicle(AsVehicle(mpManipulatedObject));
            if (pVehicle) {
                int locomotion = pVehicle->mLocomotion;
                Vector3 spawn = GetCity(mpCommunity)->GetVehicleSpawnPoint(locomotion);
                pVehicle->mSpatial.SetPosition(spawn);
                PlaceVehicle(pVehicle);
                return false;
            }
            if (mpManipulatedObject) {
                Vector3 picked = CameraManager()->Pick(1, mCursorScreenPos);
                Vector3 surface = PlanetModel()->ToSurface(picked);
                mpManipulatedObject->SetPosition(surface);
                mpManipulatedObject->SetOrientation(PlanetModel()->GetSurfaceOrientation(
                    surface, mpManipulatedObject->GetOrientation()));
                UpdateSnapping();
                UpdatePlacementEffects();
            }
        } else {
            SetManipulatedObject(0);
            if (mpSellbackRollover)
                mpSellbackRollover->Hide();
        }
        return false;
    }
    }
    return false;
}

} // namespace SP
