// SP::cSPSimulatorSpaceGame::HandleMessage (0x0100b890, 6206 bytes).
//
// The space game's EA::Messaging::IHandler override: one big dispatch on the
// message ID (city hall pie menu commands, sell/repair/demolish building,
// creature editor round trips, banning, alliance events, community editor
// colony view, ...).  `this` is the IHandler subobject (object + 0x10), so the
// full-object helpers (ConfigUpdated etc.) are called with `this - 0x10`.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the AutoRefCount locals
// have no EH frame).
//
// Every callee is an external (relocated) call in the original, so most methods
// below are only declared.  Names come from the card (dev-PDB names where they
// fit, the 2008 enum eSimulatorSpaceGameMessages for the message IDs) or from
// what the callee does; the unknown ones carry their address.  Field offsets are
// the retail ones read from the disassembly (they differ from the 2008 PDB).
#include "types.h"

typedef unsigned int size_t;

#define PV(n) virtual void _v##n();

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00F473A0
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};

struct Vector3 {
    float x, y, z;
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
struct Quaternion { float x, y, z, w; };
// 3 rows of 4 floats (the 4th column is padding)
struct Matrix34 { float m[3][4]; };
struct Matrix3 {
    float m[3][3];
    explicit Matrix3(const Matrix34& s)
    {
        m[0][0] = s.m[0][0]; m[0][1] = s.m[0][1]; m[0][2] = s.m[0][2];
        m[1][0] = s.m[1][0]; m[1][1] = s.m[1][1]; m[1][2] = s.m[1][2];
        m[2][0] = s.m[2][0]; m[2][1] = s.m[2][1]; m[2][2] = s.m[2][2];
    }
};
Quaternion MatrixToQuaternion(const Matrix3& m, bool normalize);   // 0x0046D660

// Refcounted interfaces: Release is slot 1 (IUnknown-like) or slot 2 (classes
// with a virtual dtor in slot 0).
struct RefCounted1 {
    virtual int AddRef();     // slot 0
    virtual int Release();    // slot 1
};
struct RefCounted2 {
    PV(0)
    virtual int AddRef();     // slot 1
    virtual int Release();    // slot 2
};

namespace EA {
template <class T> class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T** AsPPTypeParam()
    {
        if (mpObject) {
            T* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};

// EA::Variant (0x18 bytes)
struct Variant {
    uint32_t mData[4];
    uint16_t mFlags;   // +0x10
    uint16_t mType;    // +0x12
    uint16_t m14;
    uint16_t m16;
    Variant() : mFlags(0), m16(0) {}
    ~Variant()
    {
        if (mFlags & 4)
            Destruct(0);
    }
    void Destruct(int);                         // 0x0093DB80
    Variant& operator=(const uint32_t& v);      // 0x00422EB0
    uint32_t GetUInt32();                       // 0x00BD6A60
    // an object held by pointer (flags 0x30) or stored inline
    RefCounted1* GetObject()
    {
        if (mFlags & 0x30)
            return *(RefCounted1**)mData;
        if (mType)
            return (RefCounted1*)this;
        return 0;
    }
};
}  // namespace EA
using EA::AutoRefCount;
using EA::Variant;

struct IUnknownCast : public RefCounted1 {
    PV(2)
    virtual void* Cast(uint32_t typeID);        // slot 3
};

// ---------------------------------------------------------------------------
// Messages
// ---------------------------------------------------------------------------
struct IArgList {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual Variant* GetAt(int index);          // slot 7
};
struct IResponse {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
    virtual void SetValue(int index, const Variant& v);   // slot 8
};
struct cMessage {
    virtual int AddRef();
    virtual int Release();
    PV(2) PV(3)
    virtual IArgList* GetArgs();                // slot 4
    virtual IResponse* GetResponse();           // slot 5
};
// generic payload: +8 / +0x10 / +0x18
struct cParamMessage : public cMessage {
    uint32_t m04;
    uint32_t mParam1;      // +0x08
    uint32_t m0c;
    uint32_t mParam2;      // +0x10
    uint32_t m14;
    uint32_t mParam3;      // +0x18
};
// editor return message (0x030c11c7)
struct cEditorResultMsg : public cMessage {
    uint32_t m04, m08;
    uint32_t mResultType;  // +0x0c
    uint32_t m10;
    uint32_t mEditorID;    // +0x14
    ResourceKey mKey;      // +0x18
    uint32_t pad24[8];
    bool mbSaved;          // +0x44
};

// ---------------------------------------------------------------------------
// Game objects
// ---------------------------------------------------------------------------
struct cCombatant {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual void SetDamageLevel(int level);     // slot 11 (0x2c)
    int GetDamageState();                       // 0x008E7F80
};
struct cGameData : public RefCounted1 {
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsDestroyed();                 // slot 11 (0x2c)
    virtual cGameData* GetGameDataOwner();      // slot 12 (0x30)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual uint32_t GetPoliticalID();          // slot 19 (0x4c)
};
struct IQuaternionSource {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual const Quaternion& GetOrientation(int); // slot 12 (0x30)
};
struct cBuilding : public cGameData {
    PV(20) PV(21) PV(22)
    virtual float GetSellValue();               // slot 23 (0x5c)
    virtual float GetRepairCost();              // slot 24 (0x60)
    PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32)
    virtual uint32_t GetBuildingID();           // slot 33 (0x84)
    bool IsUnderConstruction();                 // 0x00C3F540
};
struct cBuildingWithFrame : public cBuilding {  // returned by 0x01002E10
    uint32_t pad04[12];
    IQuaternionSource mOrientation;             // +0x34
    uint32_t pad38[58];
    cCombatant mCombatant;                      // +0x120
};
struct cBuildingC : public cBuilding {          // returned by 0x00B67760
    uint32_t pad04[71];
    cCombatant mCombatant;                      // +0x120
};
struct cVehicle : public cGameData {            // returned by 0x00B67780
    uint32_t pad04[353];
    cCombatant mCombatant;                      // +0x588
    float GetSellValue();                       // 0x00BD0110
    uint32_t GetVehicleID();                    // 0x00BCE5C0
};
struct cCity {
    void RemoveBuilding(cBuilding* b);          // 0x00BE33E0
    void RemoveVehicle(cVehicle* v, int);       // 0x00BE2070
    void Update();                              // 0x00BD9E50
    int GetBuildingCount();                     // 0x00BBC840
};
struct cHomePlanetRecord {
    void* GetStarRecord();                      // 0x00CE6950
};
struct cEmpireVisuals {
    uint32_t pad[0x504 / 4];
    ResourceKey mKey;                           // +0x504
};
struct cEmpireIDList { uint32_t* mpBegin; uint32_t* mpEnd; };
struct cEmpire {
    uint32_t pad00[0x50 / 4];
    uint32_t mFlags;                            // +0x50
    uint32_t pad54[12];
    uint32_t mPoliticalID;                      // +0x84
    int GetMoney();                             // 0x00C30CB0
    void AddMoney(int amount);                  // 0x00C31A00
    bool IsAlly();                              // 0x00C308B0
    cEmpireVisuals* GetVisuals();               // 0x00C30C80
    cHomePlanetRecord* GetHomePlanet();         // 0x00C31730
    cEmpireIDList* GetAllies();                 // 0x0108DB30
};
struct cPlanetRecord {
    bool HasFlag(int f);                        // 0x00C71400
    void SetFlag(int f, int v);                 // 0x00C71430
};
struct cTerrainSphere {
    uint32_t pad[0x10e8 / 4];
    RefCounted1* mpTerrainData;                 // +0x10e8
    bool HasEvent(uint32_t id);                 // 0x00C772C0
    void SetEvent(uint32_t id);                 // 0x00C77BF0
};
struct cSPPlayerInventoryData {
    uint32_t pad[0x6b4 / 4];
    float m6b4;                                 // +0x6b4
    float m6b8;                                 // +0x6b8
};
struct cSpaceInventoryItem : public RefCounted2 {
    uint32_t pad04[30];
    int m7c;                                    // +0x7c
};
struct cSPPlayerInventory {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
    PV(25) PV(26) PV(27) PV(28)
    virtual bool HasTool(const ResourceKey& toolID);                   // slot 29 (0x74)
    PV(30) PV(31)
    virtual void AddItem(cSpaceInventoryItem* item, int, int);          // slot 32 (0x80)
    PV(33) PV(34)
    virtual void* GetSpeciesSlot();                                     // slot 35 (0x8c)
    void SetActiveTool();                       // 0x00FF3E80
    void* GetActiveTool();                      // 0x00FF3F00
};
struct cSPSpaceToolData : public RefCounted2 {
    int GetUseCost();                           // 0x01050020
};
struct cSPToolManager {
    bool CreateToolFromToolID(const ResourceKey& id, cSpaceInventoryItem** ppTool);  // 0x0104E340
};
struct cSPSimPlanetHighLOD {
    void OnCelebrationEffectOver();             // 0x00FF6290
    bool IsBusy();                              // 0x00FF6360
    void OnCVGTransition();                     // 0x00FF6190
    void MakeUFOVisible();                      // 0x00FF6200
    void ShowUFOForTransition();                // 0x00FF60D0
};
struct cCachedEventData {
    void SetEvent(int bits, int value);         // 0x00FE5430
};
struct cSPSimulatorPlayerUFO {
    int IsBusy0();                              // 0x00BDDD10
    int IsBusy1();                              // 0x00FFC2D0
    int IsBusy2();                              // 0x00FFC320
    void CancelAction(int, int);                // 0x00FFD710
    void ClearTarget();                         // 0x00FFC330
    void RepairUFO();                           // 0x010019A0
    void ContactEmpire(uint32_t politicalID, int);   // 0x01001700
    bool CanContact(cEmpire* empire);           // 0x00FFF270
    void AddPosseMember(uint32_t politicalID, int);  // 0x010027B0
    cSPPlayerInventoryData* GetPlayerInventory();    // 0x00A1AD60
};
struct cGlobal16dc0fc {
    uint32_t pad[0x54 / 4];
    struct cMission { void Refresh(); /* 0x00FF5B20 */ }* m54;
};
struct cTool14 {                                // object at full + 0x14
    void UnlockBadge(uint32_t id);              // 0x0106DCD0
    void BeginColonyView();                     // 0x01066D60
    void EndColonyView();                       // 0x01066DD0
};
struct cCommunityEditor {
    void Activate(cCity* city, int);            // 0x00D0E170
    void Deactivate(int, int);                  // 0x00D100B0
    bool IsActive();                            // 0x00D0A160
    void SetMode(int);                          // 0x00D09690
};
struct cPlanetImpostor : public RefCounted1 {
    void* GetImage();                           // 0x0046F260
};
struct cImageWriter : public RefCounted1 {      // new("Simulator") 0x30 bytes, ctor 0x009986E0
    void* mpImage;                              // +0x04
    struct cResource {                          // +0x08
        uint32_t vptr, refs;
        ResourceKey mKey;                       // +0x08
    } mResource;
    uint32_t pad1c[5];
    cImageWriter();   // 0x009986e0 (equiv t3)
};
struct cSpeciesProfile : public RefCounted1 {
    const ResourceKey& GetKey();                // 0x00C0BC00
};
struct cEditorLaunchData : public RefCounted2 { // 0x9c bytes
    uint32_t pad04[2];
    uint32_t mEditorID;                         // +0x0c
    ResourceKey mSpeciesKey;                    // +0x10
    uint32_t pad1c[6];
    bool m34, m35, m36, m37, m38, m39, m3a, m3b, m3c, m3d;
    uint8_t pad3e[0x26];
    bool m64;                                   // +0x64
    uint8_t pad65[0x2f];
    AutoRefCount<RefCounted1> mpTerrain;        // +0x94
    uint32_t pad98;
    cEditorLaunchData();                        // 0x005A9080
};
struct cEditorLauncher {
    void Launch(cEditorLaunchData* data);       // 0x00B1DEE0
};
struct cStarRecord : public RefCounted1 {
    void SetVisited(int);                       // 0x00BD83B0
};
struct cStarList {
    cStarRecord** mpBegin;
    cStarRecord** mpEnd;
    uint32_t mpCapacity;
    uint32_t mAllocator;
};
struct cStarVector {                            // eastl::vector<AutoRefCount<cStarRecord>, sp_vector_allocator>
    AutoRefCount<cStarRecord>* mpBegin;
    AutoRefCount<cStarRecord>* mpEnd;
    AutoRefCount<cStarRecord>* mpCapacity;
    uint32_t mAllocator;
    cStarVector(const cStarList& x);            // 0x00BA95A0
    ~cStarVector();                             // 0x00AE6970
    int size() const { return (int)(mpEnd - mpBegin); }
    AutoRefCount<cStarRecord>& operator[](int i) { return mpBegin[i]; }
};
struct cGameNounManager {
    void RemoveCity(cCity* c);                  // 0x00B225D0
    cTerrainSphere* GetCurrentTerrainSphere();  // 0x00F67D90
    const cStarList& GetStars();                // 0x00ACE2C0
};
struct cSpeciesManager {
    void MakeInventoryItemFromSpecies(cSpaceInventoryItem** ppItem, const ResourceKey& key, int, int);  // 0x00AC0CB0
};
struct cGameModeManager {
    uint32_t GetModeIDByName(const char* name); // 0x00AD7DB0
    bool IsPlanetBusterBlocked();               // 0x00AC80F0
};
struct cCursorManager {
    void SetLocalCursor(uint32_t id);           // 0x00801BB0
};
struct cMessageServer {
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void PostMSG(uint32_t id, int, int);           // slot 5
    virtual void PostMSG4(uint32_t id, int, int, int);     // slot 6
};
struct cResourceObject : public RefCounted1 {};
struct IResourceManager {
    PV(0) PV(1) PV(2)
    virtual bool GetResource(const ResourceKey& key, cResourceObject** ppDst, int, int, int, int);  // slot 3
    PV(4) PV(5) PV(6) PV(7)
    virtual void WriteResource(cImageWriter::cResource* res, int, uint32_t saveArea, uint32_t, int); // slot 8
};
struct IImageCache {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual void SetImage(uint32_t instanceID, uint32_t groupID, cPlanetImpostor* impostor, int);  // slot 20 (0x50)
};
struct cThumbnailMarker : public RefCounted1 {};
struct cRelationshipManager {
    float RecordEvent(uint32_t idA, uint32_t idB, uint32_t eventID, float scale);  // 0x00D06240
};
struct cSPUIEventLog {
    void PostFeedbackEvent(uint32_t a, uint32_t b, int, int, int, int);  // 0x00DD8640
};
struct cSPSpaceGfx {
    void AllianceGraphCreate();                 // 0x01037700
};
namespace Achievements {
struct Controller {
    void AutoTest(uint32_t id, int);            // 0x00676E90
    void AwardAchievement(uint32_t id);         // 0x00676710
};
}
struct cAllianceEvent {
    uint32_t pad[3];
    struct { uint32_t pad[7]; int mCount; }* m0c;   // +0x0c, count at +0x1c
    void SetType(int);                          // 0x007EB820
};
struct cColonyLauncher {
    void Update();                              // 0x01016950
    bool IsBusy();                              // 0x00A98020
    int GetState();                             // 0x00985E40
};
struct cTerrainCameraController {
    Vector3 SetOrientation(const Quaternion& q);       // 0x00B12DD0
    void ResetInterpolation(Vector3 v);                // 0x00B10760
    Matrix34 GetFrame();                               // 0x00B13790
};
struct cSPSpacePlanetCameraController {
    Matrix34 GetFrame();                               // 0x01017200
};
struct cICameraController;
struct ICameraManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual cICameraController* GetActiveCameraController();   // slot 14 (0x38)
};
struct IApp {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual ICameraManager* GetCameraManager();         // slot 20 (0x50)
};
struct cCameraModeManager {
    void SetMode(uint32_t id);                  // 0x00B5CDE0
};
struct cUIThing3f0 { void Hide(); /* 0x00E19010 */ };
struct cUIThing400 { void Show(int); /* 0x00E14C10 */ };

// singletons / free functions
cMessageServer* MessageServer();                // 0x0067DCC0
IResourceManager* GetResourceManager();         // 0x0067DCD0
IApp* App();                                    // 0x0067DD10
IImageCache* GetImageCache();                   // 0x0067DD60
Achievements::Controller* GetAchievements();    // 0x00675250
cCursorManager* CursorManager();                // 0x0067CAB0
cGameNounManager* NounManager();                // 0x00B3D300
cEditorLauncher* EditorLauncher();              // 0x00B3D320
cSPToolManager* ToolManager();                  // 0x00B3D390
cSPUIEventLog* EventLog();                      // 0x00B3D3E0
cUIThing3f0* UI_b3d3f0();                       // 0x00B3D3F0
cUIThing400* UI_b3d400();                       // 0x00B3D400
cSpeciesManager* SpeciesManager();              // 0x00B3D450
cSPSpaceGfx* SpaceGfx();                        // 0x00B3D470
cGameModeManager* GameModeManager();            // 0x00B3D4D0
cRelationshipManager* RelationshipManager();    // 0x00B3D2C0
cCameraModeManager* CameraModeManager();        // 0x00B3D230
struct cPlanetModel { const ResourceKey& GetPlanetKey(); /* 0x00B7E380 */ };
cPlanetModel* PlanetModel();                    // 0x00B3D350
void* GetCurrentGameMode();                     // 0x00B5B800
extern char g_SpaceGameMode;                    // 0x01654C10
extern cGlobal16dc0fc* g_p16dc0fc;              // 0x016DC0FC
struct cSPConfig { uint32_t pad[0x88 / 4]; char m88; };
cSPConfig* GetSPConfig();                       // 0x00FD9C60
cSPSimulatorPlayerUFO* GetUFOSimulator();       // 0x00FFBE50
cEmpire* GetPlayerEmpire();                     // 0x01021300
uint32_t GetPlayerEmpireID();                   // 0x01021090
cPlanetRecord* GetActivePlanet();               // 0x01021260
void BlowUpPlanet();                            // 0x01004E50
cColonyLauncher* ColonyLauncher();              // 0x01015DF0
struct cSpaceToolValues { float GetPriceScale(); /* 0x00CF7A50 */ };
cSpaceToolValues* SpaceToolValues();            // 0x00CF74C0
uint32_t GetSaveArea(uint32_t id);              // 0x006B1F90

cGameData* GetGameData(uint32_t id);            // 0x00C9F060
void SelectGameData(uint32_t id);               // 0x00B18E00
cGameData* CastToCityHall(cGameData* p);        // 0x00CF7D20 interface_cast<cBuildingCityHall>
bool CanBanObject(cGameData* p);                // 0x00DD18B0
bool CanBanObject2(cGameData* p);               // 0x00E09AD0
void ShowConfirmationDialog(void* p);           // 0x00DD1AA0 cUIBanningContent
void ShowConfirmationDialog2(void* p);          // 0x00E09BF0
cCity* CastToCity(cGameData* p);                // 0x00AC86D0
cBuildingC* CastToBuilding(AutoRefCount<cGameData>* p);        // 0x00B67760
cVehicle* CastToVehicle(AutoRefCount<cGameData>* p);           // 0x00B67780
cBuildingWithFrame* CastToBuilding2(AutoRefCount<cGameData>* p); // 0x01002E10
void PostSpaceEvent(uint32_t id, void* p2, const ResourceKey* k3, ResourceKey* k4,
                    void* p5, int p6, ResourceKey* k7, ResourceKey* k8);   // 0x00E39AB0
void SetGameFlag(const char* name, uint32_t id, int value);    // 0x01041C50
void ShowSpaceMessage(uint32_t id, int);        // 0x01043500
cThumbnailMarker* CastResource(AutoRefCount<cResourceObject>* p);   // 0x00421F60
cTerrainCameraController* CastToTerrainCamera(cICameraController* c);           // 0x00B5CC20
cSPSpacePlanetCameraController* CastToPlanetCamera(cICameraController* c);      // 0x00C37590

extern const ResourceKey k_CreatureEdit;        // 0x016DC3C0
extern const ResourceKey k_CreatureCreate;      // 0x016DC3B4
extern const ResourceKey k_placecolony;         // 0x016DC1F8
extern const ResourceKey k_interplanetarydrive; // 0x016DC150

struct cThumbnail : public cThumbnailMarker {
    bool IsReady();                             // 0x00550970
};

// ---------------------------------------------------------------------------
// cSPSimulatorSpaceGame
// ---------------------------------------------------------------------------
namespace EA { namespace Messaging {
class IHandler {
public:
    virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
};
} }

namespace SP {
class cGonzagoSimulator {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual bool HandleSimulatorMessage(uint32_t messageID, void* pMessage);   // slot 7
    uint32_t mGonzago[3];
};

class cSPSimulatorSpaceGame : public cGonzagoSimulator, public EA::Messaging::IHandler {
public:
    enum {
        kMsgConfigChanged               = 0x00f62def,
        kMessageInputFlyToPlanet        = 0x022d38ee,
        kMessageCelebrationEffectOver   = 0x027c0ae1,
        kMessageInputFaceHome           = 0x02e81d88,
        kMessageInputUFOTarget          = 0x03056566,
        kMessageInputDefaultAction      = 0x03065e0f,
        kMsgEditorResult                = 0x030c11c7,
        kMsgDeselectObject              = 0x03337cbb,
        kMessageInputPreviewFilters     = 0x033b7638,
        kShowCityHallPieMenu            = 0x033cabf0,
        kCancelCityHallPieMenu          = 0x033cabf3,
        kMessageInputFlyToStar          = 0x03582d63,
        kSellBuildingCommand            = 0x035da7e9,
        kSellOutpostCommand             = 0x035eee4d,
        kRepairUFOCommand               = 0x037aac1d,
        kEditCreature                   = 0x03b092aa,
        kCreateCreature                 = 0x03c5dbc7,
        kRepairBuildingCommand          = 0x03e7de8f,
        kDemolishBuildingCommand        = 0x03e7de95,
        kMsgEmpireEvent                 = 0x04249453,
        kMsgAllianceFormed              = 0x04445d43,
        kMsgEmpireContact               = 0x04445d44,
        kBanObjectCommand               = 0x044ebe3f,
        kBanObjectCancel                = 0x044ecd59,
        kMsgGameModeChanged             = 0x044f1189,
        kBanObjectMouseOver             = 0x0456b08c,
        kMessageInputTurretTarget       = 0x04dd13d1,
        kMessageBlowUpPlanet            = 0x04f4d25e,
        kMessageInputCreatureTarget     = 0x05417b45,
        kMessageInputVehicleTarget      = 0x054a7806,
        kMessageInputMissileTarget      = 0x057df7e0,
        kMessageInputCelestialBody      = 0x0589c84b,
        kMessageShowUFOForTransition    = 0x0590cd26,
        kMsgCaptureImpostor             = 0x05fe8ea0,
        kMsgBan2Command                 = 0x062656dd,
        kMsgBan2MouseOver               = 0x062656de,
        kMsgBan2Cancel                  = 0x062656df,
        kMsgTutorialDone                = 0x064e43b9,
        kMsgRevealStars                 = 0x0678a3ef,
        kMsgHideStars                   = 0x0678a3f3,
        kMsgContactObject               = 0x14051500,
        kMsgColonyViewExit              = 0x71d4dfc8,
        kMsgColonyViewEnter             = 0x71d4dfc9,
        kMessageMakeUfoVisible          = 0x915b7724,
        kMessageImpostorCaptureComplete = 0x99eda4cd,
    };

    void ConfigUpdated();                       // 0x010060D0
    bool IsInputBlocked();                      // 0x00B18E40
    cAllianceEvent* CreateAllianceEvent(int);   // 0x01005180
    void OnEmpireEvent(const uint32_t* params); // 0x01004FC0

    virtual bool HandleMessage(uint32_t messageID, void* pMessage);

    cTool14* mpTool14;                                      // +0x14
    uint32_t m18, m1c;
    cCommunityEditor* mCommunityEditor;                     // +0x20
    AutoRefCount<cEditorResultMsg> mEditorResult;           // +0x24
    AutoRefCount<cGameData> mpSelectedObject;               // +0x28
    uint32_t m2c[5];
    cSPPlayerInventory* mPlayerInventory;                   // +0x40
    uint32_t mSaveField44;                                  // +0x44
    AutoRefCount<cPlanetImpostor> mPlanetImpostor;          // +0x48
    bool mIsCapturingImpostor;                              // +0x4c
    bool mImpostorCaptured;                                 // +0x4d
    bool m4e;
    bool mImpostorSaved;                                    // +0x4f
    uint32_t m50;
    cSPSimPlanetHighLOD* mHighLODPlanetSim;                 // +0x54
    uint32_t m58[6];
    cCachedEventData* mCachedEventData;                     // +0x70
    bool mShowDebugCityPlanner;                             // +0x74
    bool mColonyEmpty;                                      // +0x75
    bool mWasEditCreature;                                  // +0x76
};

// Bit 6 of cEmpire::mFlags marks an empire whose thumbnail is already known.
static __forceinline bool EmpireThumbnailReady(cEmpire* empire)
{
    ResourceKey key = empire->GetVisuals()->mKey;
    key.typeID = 0x30bdee3;
    bool ready = false;
    AutoRefCount<cResourceObject> res;
    if (GetResourceManager()->GetResource(key, res.AsPPTypeParam(), 0, 0, 0, 0)) {
        AutoRefCount<cThumbnail> thumb((cThumbnail*)CastResource(&res));
        ready = thumb->IsReady();
    }
    return ready;
}

bool cSPSimulatorSpaceGame::HandleMessage(uint32_t messageID, void* pMessage)
{
    uint32_t result = 0;
    cParamMessage* msg = (cParamMessage*)pMessage;

    switch (messageID) {
    case kMsgConfigChanged:
        if (msg->mParam2 == 0x2ae0c7e && msg->mParam3 == 0x521d0174)
            ConfigUpdated();
        return false;

    case kMessageCelebrationEffectOver:
        if (mHighLODPlanetSim)
            mHighLODPlanetSim->OnCelebrationEffectOver();
        return true;

    case kMessageInputFlyToPlanet:
    case kMessageInputFaceHome:
    case kMessageInputUFOTarget:
    case kMessageInputDefaultAction:
    case kMessageInputPreviewFilters:
    case kMessageInputFlyToStar:
    case kMessageInputTurretTarget:
    case kMessageInputCreatureTarget:
    case kMessageInputVehicleTarget:
    case kMessageInputMissileTarget:
    case kMessageInputCelestialBody:
        if (IsInputBlocked())
            return true;
        return HandleSimulatorMessage(messageID, pMessage);

    case kMsgDeselectObject: {
        uint32_t id = msg->mParam1;
        if (mpSelectedObject && !mpSelectedObject->IsDestroyed()) {
            cBuildingC* building = CastToBuilding(&mpSelectedObject);
            cVehicle* vehicle = CastToVehicle(&mpSelectedObject);
            if ((building && building->GetBuildingID() == id) ||
                (vehicle && vehicle->GetVehicleID() == id))
                mpSelectedObject = 0;
        }
        return false;
    }

    case kMsgEditorResult: {
        cEditorResultMsg* em = (cEditorResultMsg*)pMessage;
        if (em && (em->mResultType == 0x66787bc || em->mResultType == 0x7ce3cb0 ||
                   em->mResultType == 0x7ce1750)) {
            mEditorResult = em;
            return false;
        }
        cSPPlayerInventory* inventory = mPlayerInventory;
        uint32_t editorID = em->mEditorID;
        if (editorID == 0x9ea3031a || editorID == 0x372e2c04 || editorID == 0xccc35c46 ||
            editorID == 0x65672ade || editorID == 0x4178b8e8) {
            AutoRefCount<cSpaceInventoryItem> item;
            if (!em->mbSaved) {
                SpeciesManager()->MakeInventoryItemFromSpecies(item.AsPPTypeParam(), em->mKey, 5, 0);
                inventory->AddItem(item, 0, 1);
            }
            else {
                if (ToolManager()->CreateToolFromToolID(
                        mWasEditCreature ? k_CreatureEdit : k_CreatureCreate, item.AsPPTypeParam())) {
                    item->m7c = 1;
                    mPlayerInventory->AddItem(item, 0, 1);
                }
            }
        }
        if (em->mEditorID == 0x98e03c0d) {
            ResourceKey k1, k2, k3;
            PostSpaceEvent(0x8efe000f, 0, &em->mKey, &k3, 0, 0, &k2, &k1);
        }
        return false;
    }

    case kShowCityHallPieMenu:
        if (!mHighLODPlanetSim->IsBusy() && mPlayerInventory->HasTool(k_interplanetarydrive)) {
            uint32_t id = msg->GetArgs()->GetAt(0)->GetUInt32();
            cGameData* object = GetGameData(id);
            SelectGameData(id);
            mpSelectedObject = CastToCityHall(object);
        }
        break;

    case kCancelCityHallPieMenu: {
        cSPSimulatorPlayerUFO* ufo = GetUFOSimulator();
        if (ufo->IsBusy0() || ufo->IsBusy1() || ufo->IsBusy2()) {
            ufo->CancelAction(0, 0);
            ufo->ClearTarget();
        }
        else if (mPlayerInventory->GetActiveTool()) {
            if (mPlayerInventory)
                mPlayerInventory->SetActiveTool();
        }
        else
            MessageServer()->PostMSG(0x64eb18e, 0, 0);
        break;
    }

    case kSellOutpostCommand:
        if (mpSelectedObject && !mpSelectedObject->IsDestroyed()) {
            cCity* city = CastToCity(mpSelectedObject->GetGameDataOwner());
            NounManager()->RemoveCity(city);
            AutoRefCount<cSPSpaceToolData> tool;
            ToolManager()->CreateToolFromToolID(k_placecolony, (cSpaceInventoryItem**)tool.AsPPTypeParam());
            float scale = SpaceToolValues()->GetPriceScale();
            GetPlayerEmpire()->AddMoney((int)(tool->GetUseCost() * scale));
        }
        mpSelectedObject = 0;
        break;

    case kSellBuildingCommand:
        if (mpSelectedObject && !mpSelectedObject->IsDestroyed()) {
            cBuildingC* building = CastToBuilding(&mpSelectedObject);
            if (building && building->mCombatant.GetDamageState() != 2) {
                float scale = SpaceToolValues()->GetPriceScale();
                GetPlayerEmpire()->AddMoney((int)(building->GetSellValue() * scale));
                cCity* city = CastToCity(mpSelectedObject->GetGameDataOwner());
                if (city) {
                    city->RemoveBuilding(building);
                    city->Update();
                }
            }
            else {
                cVehicle* vehicle = CastToVehicle(&mpSelectedObject);
                if (vehicle && vehicle->mCombatant.GetDamageState() != 2) {
                    float scale = SpaceToolValues()->GetPriceScale();
                    GetPlayerEmpire()->AddMoney((int)(vehicle->GetSellValue() * scale));
                    cCity* city = CastToCity(mpSelectedObject->GetGameDataOwner());
                    if (city) {
                        city->RemoveVehicle(vehicle, 0);
                        city->Update();
                    }
                }
            }
        }
        mpSelectedObject = 0;
        break;

    case kRepairUFOCommand:
        GetUFOSimulator()->RepairUFO();
        break;

    case kCreateCreature:
        if (mPlayerInventory->GetSpeciesSlot()) {
            mWasEditCreature = false;
            if (mPlayerInventory)
                mPlayerInventory->SetActiveTool();
            cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
            RefCounted1* terrain = 0;
            if (sphere && sphere->mpTerrainData)
                terrain = sphere->mpTerrainData;
            AutoRefCount<cEditorLaunchData> data;
            data = new ("App", 0, 0, 0, 0) cEditorLaunchData();
            data->mEditorID = 0xb7af8ff8;
            data->mpTerrain = terrain;
            data->m34 = false;
            data->m36 = false;
            data->m38 = false;
            data->m37 = false;
            data->m39 = false;
            data->m3c = true;
            data->m3d = true;
            data->m64 = true;
            EditorLauncher()->Launch(data);
        }
        return false;

    case kEditCreature:
        if (mPlayerInventory->GetSpeciesSlot()) {
            mWasEditCreature = true;
            AutoRefCount<cSpeciesProfile> species((cSpeciesProfile*)msg->mParam1);
            if (species) {
                const ResourceKey& key = species->GetKey();
                uint32_t instanceID = key.instanceID;
                uint32_t typeID = key.typeID;
                uint32_t groupID = key.groupID;
                if (mPlayerInventory)
                    mPlayerInventory->SetActiveTool();
                cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
                RefCounted1* terrain = 0;
                if (sphere && sphere->mpTerrainData)
                    terrain = sphere->mpTerrainData;
                GetAchievements()->AutoTest(0xc287732e, 1);
                AutoRefCount<cEditorLaunchData> data;
                data = new ("App", 0, 0, 0, 0) cEditorLaunchData();
                data->mEditorID = 0xb7af8ff8;
                data->mSpeciesKey.instanceID = instanceID;
                data->mSpeciesKey.typeID = typeID;
                data->mSpeciesKey.groupID = groupID;
                data->mpTerrain = terrain;
                data->m34 = false;
                data->m36 = false;
                data->m38 = false;
                data->m37 = false;
                data->m39 = false;
                data->m3c = true;
                data->m3d = true;
                data->m64 = true;
                EditorLauncher()->Launch(data);
            }
        }
        return false;

    case kRepairBuildingCommand: {
        cEmpire* empire = GetPlayerEmpire();
        if (mpSelectedObject && !mpSelectedObject->IsDestroyed()) {
            cBuildingC* building = CastToBuilding(&mpSelectedObject);
            if (building) {
                cCombatant* combatant = &building->mCombatant;
                if (combatant->GetDamageState() == 2) {
                    float money = (float)empire->GetMoney();
                    if (money > building->GetRepairCost()) {
                        empire->AddMoney((int)-building->GetRepairCost());
                        combatant->SetDamageLevel(0);
                    }
                    else
                        ShowSpaceMessage(0x3e7e341, 0);
                }
            }
        }
        mpSelectedObject = 0;
        break;
    }

    case kDemolishBuildingCommand:
        if (mpSelectedObject && !mpSelectedObject->IsDestroyed()) {
            cBuildingC* building = CastToBuilding(&mpSelectedObject);
            if (building && building->mCombatant.GetDamageState() == 2 &&
                !building->IsUnderConstruction())
                CastToCity(mpSelectedObject->GetGameDataOwner())->RemoveBuilding(building);
        }
        mpSelectedObject = 0;
        break;

    case kMsgEmpireEvent: {
        cColonyLauncher* launcher = ColonyLauncher();
        if (launcher && (launcher->IsBusy() || launcher->GetState() == 2))
            launcher->Update();
        uint32_t params[3];
        params[0] = msg->mParam3;
        params[1] = msg->mParam1;
        params[2] = msg->mParam2;
        OnEmpireEvent(params);
        return false;
    }

    case kMsgAllianceFormed: {
        cEmpire* empireA = (cEmpire*)msg->mParam1;
        cEmpire* empireB = (cEmpire*)msg->mParam2;
        cEmpire* other = 0;
        if (empireA == GetPlayerEmpire())
            other = empireB;
        if (empireB == GetPlayerEmpire())
            other = empireA;
        if (!other)
            return false;

        MessageServer()->PostMSG4(0x43f2585, 0, 0, 0);
        GetUFOSimulator()->AddPosseMember(other->mPoliticalID, 1);
        cCachedEventData* cached = mCachedEventData;
        if (cached) {
            cached->SetEvent(1, 1);
            if (other->IsAlly())
                cached->SetEvent(0x10, 1);
        }
        cEmpireIDList* allies = GetPlayerEmpire()->GetAllies();
        cAllianceEvent* event = CreateAllianceEvent(2);
        event->SetType(8);
        event->m0c->mCount = (int)(allies->mpEnd - allies->mpBegin);
        RelationshipManager()->RecordEvent(other->mPoliticalID, GetPlayerEmpireID(), 0x526e524, 1.0f);

        bool readyA = (empireA->mFlags >> 6) & 1;
        bool readyB = (empireB->mFlags >> 6) & 1;
        if (!readyA)
            readyA = EmpireThumbnailReady(empireA);
        if (!readyB)
            readyB = EmpireThumbnailReady(empireB);
        if (readyA && readyB)
            GetAchievements()->AutoTest(0x4106aa7d, 1);

        ResourceKey k1, k2, k3, k4;
        PostSpaceEvent(0x36d9282b, other, &k3, &k4, other->GetHomePlanet()->GetStarRecord(), 0, &k2, &k1);
        SpaceGfx()->AllianceGraphCreate();
        return false;
    }

    case kMsgEmpireContact: {
        cEmpire* empireA = (cEmpire*)msg->mParam1;
        cEmpire* empireB = (cEmpire*)msg->mParam2;
        cEmpire* other = 0;
        if (empireA == GetPlayerEmpire())
            other = empireB;
        if (empireB == GetPlayerEmpire())
            other = empireA;
        if (other && GetUFOSimulator()->CanContact(other))
            GetUFOSimulator()->ContactEmpire(other->mPoliticalID, 0);
        return false;
    }

    case kBanObjectCommand: {
        RefCounted1* object = msg->GetArgs()->GetAt(0)->GetObject();
        if (object)
            ShowConfirmationDialog(((IUnknownCast*)object)->Cast(0x17f243b));
        else
            ShowConfirmationDialog(0);
        break;
    }

    case kBanObjectCancel:
        MessageServer()->PostMSG(0x452e0ca, 0, 0);
        break;

    case kMsgGameModeChanged: {
        uint32_t modeID = msg->mParam1;
        if (modeID == GameModeManager()->GetModeIDByName("CVG2SPG_short")) {
            GetUFOSimulator()->GetPlayerInventory()->m6b4 = 1.0f;
            GetUFOSimulator()->GetPlayerInventory()->m6b8 = 1.0f;
            g_p16dc0fc->m54->Refresh();
            return true;
        }
        if (modeID == GameModeManager()->GetModeIDByName("CVG2SPG")) {
            GetUFOSimulator()->GetPlayerInventory()->m6b4 = 1.0f;
            GetUFOSimulator()->GetPlayerInventory()->m6b8 = 1.0f;
            g_p16dc0fc->m54->Refresh();
            if (GetSPConfig()->m88 == 1)
                GetAchievements()->AwardAchievement(0x2b9868da);
            cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
            if (!sphere)
                return true;
            if (sphere->HasEvent(0x65fee65))
                return true;
            sphere->SetEvent(0x65fee65);
            if (mHighLODPlanetSim)
                mHighLODPlanetSim->OnCVGTransition();
            mpTool14->UnlockBadge(0x53f235af);
            mpTool14->UnlockBadge(0x437dec9f);
            mpTool14->UnlockBadge(0xfed1079);
            return true;
        }
        if (modeID == GameModeManager()->GetModeIDByName("SPG_FlightSchool101Complete"))
            mpTool14->UnlockBadge(0xa9c3987b);
        return true;
    }

    case kBanObjectMouseOver: {
        cGameData* object = GetGameData(msg->GetArgs()->GetAt(0)->GetUInt32());
        if (object && CanBanObject(object)) {
            CursorManager()->SetLocalCursor(0xf212a38b);
            break;
        }
        CursorManager()->SetLocalCursor(0x5ecbdffd);
        break;
    }

    case kMessageBlowUpPlanet:
        if (GameModeManager()->IsPlanetBusterBlocked()) {
            MessageServer()->PostMSG4(messageID, 0, 0, 0);
            return true;
        }
        BlowUpPlanet();
        return true;

    case kMessageShowUFOForTransition:
        if (mHighLODPlanetSim)
            mHighLODPlanetSim->ShowUFOForTransition();
        return true;

    case kMsgCaptureImpostor:
        if (mPlanetImpostor) {
            IResourceManager* resourceManager = GetResourceManager();
            uint32_t saveArea = GetSaveArea(0x31389b5);
            void* image = mPlanetImpostor->GetImage();
            const ResourceKey& planetKey = PlanetModel()->GetPlanetKey();
            uint32_t instanceID = planetKey.instanceID;
            uint32_t groupID = planetKey.groupID;
            if (image && resourceManager) {
                AutoRefCount<cImageWriter> writer(new ("Simulator", 0, 0, 0, 0) cImageWriter());
                cImageWriter::cResource* res = writer ? &writer->mResource : 0;
                writer->mpImage = image;
                writer->AddRef();
                res->mKey.instanceID = instanceID;
                res->mKey.typeID = 0x2f7d0004;
                groupID = (groupID & 0xffffff01) | 1;
                res->mKey.groupID = groupID;
                resourceManager->WriteResource(res, 0, saveArea, mSaveField44, 0);
                writer->mpImage = 0;
                writer->AddRef();
                GetImageCache()->SetImage(instanceID, groupID, mPlanetImpostor, 0);
            }
            mPlanetImpostor = 0;
        }
        mImpostorSaved = true;
        return true;

    case kMsgBan2Command: {
        RefCounted1* object = msg->GetArgs()->GetAt(0)->GetObject();
        if (object)
            ShowConfirmationDialog2(((IUnknownCast*)object)->Cast(0x17f243b));
        else
            ShowConfirmationDialog2(0);
        break;
    }

    case kMsgBan2MouseOver: {
        cGameData* object = GetGameData(msg->GetArgs()->GetAt(0)->GetUInt32());
        if (object && CanBanObject2(object)) {
            CursorManager()->SetLocalCursor(0xf6879190);
            break;
        }
        CursorManager()->SetLocalCursor(0x5ecbdffd);
        break;
    }

    case kMsgBan2Cancel:
        MessageServer()->PostMSG(0x620271c, 0, 0);
        break;

    case kMsgTutorialDone:
        if (msg->mParam1 == 0x4dc4aacb)
            SetGameFlag("SPG_FlightSchool101Complete", 0x328bb159, 1);
        return true;

    case kMsgHideStars: {
        cStarVector stars(NounManager()->GetStars());
        int count = stars.size();
        for (int i = 0; i < count; i++)
            stars[i]->SetVisited(0);
        return false;
    }

    case kMsgRevealStars: {
        cStarVector stars(NounManager()->GetStars());
        int count = stars.size();
        for (int i = 0; i < count; i++)
            stars[i]->SetVisited(1);
        return false;
    }

    case kMsgContactObject:
        if (GetCurrentGameMode() != &g_SpaceGameMode)
            GetUFOSimulator()->ContactEmpire(((cGameData*)msg->mParam1)->GetPoliticalID(), 0);
        return false;

    case kMsgColonyViewEnter:
        if (msg)
            msg->GetArgs()->GetAt(1);
        result = 2;
        if (mpSelectedObject) {
            cBuildingWithFrame* building = CastToBuilding2(&mpSelectedObject);
            if (building && !building->IsDestroyed() &&
                building->mCombatant.GetDamageState() != 2) {
                cCity* city = CastToCity(building->GetGameDataOwner());
                if (city) {
                    result = 0;
                    mpTool14->BeginColonyView();
                    if (UI_b3d3f0())
                        UI_b3d3f0()->Hide();
                    mColonyEmpty = city->GetBuildingCount() == 1;
                    cSPSpacePlanetCameraController* planetCamera =
                        CastToPlanetCamera(App()->GetCameraManager()->GetActiveCameraController());
                    if (planetCamera) {
                        Matrix34 frame = planetCamera->GetFrame();
                        CameraModeManager()->SetMode(0xebb801);
                        cTerrainCameraController* camera =
                            CastToTerrainCamera(App()->GetCameraManager()->GetActiveCameraController());
                        Matrix3 rotation(frame);
                        camera->SetOrientation(MatrixToQuaternion(rotation, true));
                        camera->SetOrientation(building->mOrientation.GetOrientation(0));
                        camera->ResetInterpolation(Vector3(0.0f, 0.0f, 0.0f));
                    }
                    else
                        CameraModeManager()->SetMode(0xebb801);
                    mCommunityEditor->Activate(city, 0);
                    if (!msg)
                        return false;
                    mCommunityEditor->SetMode(0);
                }
            }
        }
        break;

    case kMsgColonyViewExit:
        if (mCommunityEditor->IsActive()) {
            mCommunityEditor->Deactivate(0, 1);
            CastToTerrainCamera(App()->GetCameraManager()->GetActiveCameraController())->GetFrame();
            CameraModeManager()->SetMode(0x1103193);
            CastToPlanetCamera(App()->GetCameraManager()->GetActiveCameraController());
            if (mpSelectedObject) {
                cCity* city = CastToCity(CastToBuilding(&mpSelectedObject)->GetGameDataOwner());
                if (mColonyEmpty && city->GetBuildingCount() > 1) {
                    cPlanetRecord* planet = GetActivePlanet();
                    EventLog()->PostFeedbackEvent(0x7572d123, 0x131a9f54, 0, 0, 1, 0);
                    if (!planet->HasFlag(1))
                        planet->SetFlag(1, 1);
                }
            }
            mpSelectedObject = 0;
            mpTool14->EndColonyView();
            if (UI_b3d400())
                UI_b3d400()->Show(1);
        }
        else
            result = 2;
        break;

    case kMessageMakeUfoVisible:
        if (mHighLODPlanetSim)
            mHighLODPlanetSim->MakeUFOVisible();
        return true;

    case kMessageImpostorCaptureComplete:
        mImpostorCaptured = true;
        return true;
    }

    if (msg) {
        IResponse* response = msg->GetResponse();
        Variant v;
        v = result;
        response->SetValue(0, v);
    }
    return false;
}
}  // namespace SP
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
