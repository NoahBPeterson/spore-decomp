// Slice s00cd1be0 -- SP::cTribeInputStrategy::HandleMessage (tribe-stage input/message handler).
// Module flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc: string/intrusive_ptr locals get no EH frame).
// Retail layout follows the Spore ModAPI cTribeInputStrategy (size 0xD0, IHandler at +0x3C);
// HandleMessage is the IHandler override, so `this` is the +0x3C subobject.
#include "types.h"

void operator delete[](void* p);   // 0x00f47380 (EA allocator)

// ------------------------------------------------------------------ small helper types
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

namespace EA {
// EA::Variant (size 0x14): mFlags at +0x10; bit 4 = owns heap storage.
struct Variant {
    union { int mInt32; uint32_t mUint32; uint64_t mUint64; uint32_t mRaw[4]; };
    uint16_t mFlags;   // +0x10
    uint16_t mTypeId;  // +0x12
    Variant(const int& v);      // 0x005bf350
    ~Variant() { if (mFlags & 4) Destruct(0); }
    void Destruct(int);         // 0x0093db80
};
}

namespace eastl {
// eastl::basic_string<wchar_t> (16 bytes incl. allocator)
struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    wstring(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~wstring() { DeallocateSelf(); }
    void RangeInitialize(const wchar_t* p);  // 0x00579a90
    void DeallocateSelf();                   // 0x00933960
};

// eastl::intrusive_ptr<T>: ctor out of line (0x0061df40, AddRef = vslot 1), dtor Release (vslot 2).
template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr(T* p);
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
};

// eastl::fixed_vector<T*, 32, true> (overflow allowed); push_back is out of line.
template <class T> struct fixed_vector32 {
    T* mpBegin;          // +0x00
    T* mpEnd;            // +0x04
    T* mpCapacity;       // +0x08
    uint32_t mAllocator; // +0x0c overflow allocator
    void* mpPoolBegin;   // +0x10
    uint32_t mPad;       // +0x14
    T mBuffer[32];       // +0x18
    fixed_vector32() {
        mpPoolBegin = mBuffer;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 32;
    }
    ~fixed_vector32() {
        if (mpBegin && mpBegin != mpPoolBegin) operator delete[](mpBegin);
    }
    void push_back(const T& v);  // 0x00cd0a70
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
};
}

// ------------------------------------------------------------------ message plumbing
struct cMessageArgs {               // object returned by msg->GetArgs()
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void* GetArg(int index);   // +0x1c
};
struct cMessageResult {             // object returned by msg->GetResult()
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void SetResult(int index, EA::Variant* value);  // +0x20
};
struct cMessageData {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual cMessageArgs* GetArgs();      // +0x10
    virtual cMessageResult* GetResult();  // +0x14
    int field_4;
    int mParam;                           // +0x08
};

struct cArgObject {                 // arg 0 of a generic message
    void* GetObject();                    // 0x00bd6a60
};

// ------------------------------------------------------------------ game classes (stubs)
struct cGameInputManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void SetInputStrategy(void* strategy, int, int);    // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void SetInputMode(uint32_t modeID, int);            // +0x64
    uint32_t pad04[(0x110 - 4) / 4];
    int mEditorDepth;                                           // +0x110
};

struct cMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void MessageSend(uint32_t id, void* data, void* handler);           // +0x14
    virtual void MessagePost(uint32_t id, void* data, int, void* handler);      // +0x18
};

struct cUIHints { void SetEnabled(int hint, bool enabled); };   // 0x0067c420 (ret 8)
struct cUIHintsB { void Show(int which); };                     // 0x00801930

struct cDisplayStrategy {           // cTribeDisplayStrategy
    void MakeTribeIcons();          // 0x00ccd8a0
    void ccaa80(void* p);           // 0x00ccaa80
    void ccab80();                  // 0x00ccab80
    void cca060();                  // 0x00cca060
};
struct cTribeHUD { void ShowMessage(const eastl::wstring& text); };  // 0x00af1450

struct cSpatialSub {                // embedded interface (+0xc0 / +0x34 / +0x120)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vector3* GetPosition();     // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool IsDestroyed();         // +0x58
};
struct cSpatialSub2 {               // +0x120 of a tribe
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vector3* GetPosition(int);  // +0x2c
};

struct cTribe;
struct cCitizen {                   // cSPCreatureCitizen
    uint32_t pad00[0xc0 / 4];
    cSpatialSub mSpatial;           // +0xc0
    int c0b760();                   // 0x00c0b760
    bool c24560();                  // 0x00c24560
    void GiveOrder(int order, void* target, int);   // 0x00c275b0
};
struct cCitizenVector { cCitizen** mpBegin; cCitizen** mpEnd; };
struct cIntVector { int* mpBegin; int* mpEnd; };

struct cTribeTotals { uint32_t pad[0x628 / 4]; int mCount[5]; };   // +0x628..+0x638

struct cTribe {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual int GetPoliticalID();               // +0x4c
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70();
    virtual int GetMemberCount();               // +0x74
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c();
    virtual cCitizenVector* GetMembers();       // +0x90
    virtual void v94();
    virtual void SelectAll(int);                // +0x98
    virtual void SelectMembers(int, int);       // +0x9c
    virtual void va0(); virtual void va4(); virtual void va8();
    virtual void* GetEnemyTarget();             // +0xac
    virtual void vb0(); virtual void vb4(); virtual void vb8();
    virtual cIntVector* GetTools();             // +0xbc

    uint32_t pad04[(0x120 - 4) / 4];
    cSpatialSub2 mSpatial;                      // +0x120
    uint32_t pad124[(0x20c - 0x124) / 4];
    uint32_t mFoodStore;                        // +0x20c

    void ReserveToolsSlots(int);                // 0x00c998c0
    cTribeTotals* c8e820(int);                  // 0x00c8e820
    int GetAdultPopulation();                   // 0x00c8f370
    int c8e990();                               // 0x00c8e990
    void c94b50(float amount);                  // 0x00c94b50
    void c8fb50();                              // 0x00c8fb50
    bool c8e850();                              // 0x00c8e850
    bool c8e870();                              // 0x00c8e870
};

struct cOwnedObject {               // result of FUN_00b676e0: something owned by a tribe
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual cTribe* GetTribe();         // +0x58
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatialSub mSpatial;               // +0x34
};

struct cHut {                       // FUN_00cce8d0 result
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual cTribe* GetTribe();         // +0x58
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatialSub mSpatial;               // +0x34
};

struct cFood {                      // FUN_00ae6740 result
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void SetAmount(float);      // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void Consume(int);          // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual float GetAmount(int, int, void*, int);  // +0x58
};

struct cTribeTool {                 // FUN_00cce8f0 result
    uint32_t pad[0x134 / 4];
    float mHealth;                      // +0x134
    void SetHealth(float);              // 0x00c35b40
};

struct cCreatureObj {               // FUN_00f19200 result
    uint32_t pad00[0xc0 / 4];
    cSpatialSub mSpatial;               // +0xc0
    uint32_t padc4[(0xb28 - 0xc4) / 4];
    uint32_t mEffectRef;                // +0xb28
    uint32_t padb2c[(0xb4c - 0xb2c) / 4];
    int mMoodState;                     // +0xb4c
    uint32_t padb50[(0xb58 - 0xb50) / 4];
    uint32_t mFlags;                    // +0xb58
};

struct cWidget {                    // FUN_00ac86f0 result
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44();
    virtual void Toggle();              // +0x48
    virtual void v4c();
    virtual bool IsOn();                // +0x50
};

struct cTerrainCursor {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60();
    virtual void Reset();               // +0x64
    virtual void v68(); virtual void v6c();
    virtual int IsActive();             // +0x70
    virtual void v74(); virtual void v78(); virtual void v7c(); virtual void v80();
    virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void Cancel();              // +0xa4
    virtual bool IsPlacing();           // +0xa8
    virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void SetVisible(int);       // +0xb8
};

struct cPlanetRecord { uint32_t pad[0x1104 / 4]; uint32_t mPlanetType; };   // +0x1104
struct cTribePlanet {               // FUN_00f67d90 result (used with c77bf0/c772c0)
    void c77bf0(uint32_t id);           // 0x00c77bf0
    bool c772c0(uint32_t id);           // 0x00c772c0
};
struct cGameNounManager {
    cTribe* GetPlayerTribe();           // 0x00bfc5f0
    void* GetCurrentPlanet();           // 0x00f67d90
};

struct cTribeModeStrategy {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void CancelAction();                // +0x60
    virtual void v64();
    virtual int GetActionCount();               // +0x68
    virtual cDisplayStrategy* GetDisplayStrategy();  // +0x6c (also used as the HUD)

    uint32_t pad04[(0x28 - 4) / 4];
    bool mbPreEditor;                           // +0x28
    bool mbCityHallEditor;                      // +0x29
    uint8_t pad2a[0x198 - 0x2a];
    bool field_198;                             // +0x198
    uint8_t pad199[0x1a4 - 0x199];
    bool mbTutorial;                            // +0x1a4
    uint8_t pad1a5[0x390 - 0x1a5];
    int mTrackHut;                              // +0x390

    static cTribeModeStrategy* Instance();      // 0x00cd40b0
    void cd4b70(int);                           // 0x00cd4b70
    void SignalTribeEvent(uint32_t);            // 0x00cd6980
    bool cd4460(uint32_t);                      // 0x00cd4460
    void TrackTribeMember(void*, int);          // 0x00cd50b0
    void SetTrackHut(int);                      // 0x00cd4bc0
    struct cEffect* cd52e0(int, Vector3);       // 0x00cd52e0
    void cd71b0(bool, int);                     // 0x00cd71b0
    void cdb3a0(int, int);                      // 0x00cdb3a0
    void IncrementGoalProgress();               // 0x00cdab10
    void cd6390(int);                           // 0x00cd6390
    uint32_t GetTrackIndex();                   // 0x005723e0
};
struct cEffectParams { uint32_t pad[7]; int field_1c; };
struct cEffect {
    uint32_t pad[3];
    cEffectParams* mpParams;                    // +0x0c
    void SetFlags(int);                         // 0x007eb820
};

struct cCommunityEditor {
    void Activate(void* tribe, int);            // 0x00d0e170
    void Deactivate(int, int);                  // 0x00d100b0
    void d09690(int);                           // 0x00d09690
    bool d0a160();                              // 0x00d0a160
};

struct cTrackedObject {             // EA::AutoRefCount target (IRefCount: Release = vslot 1)
    virtual void AddRef();
    virtual void Release();
};
struct AutoRefCountTracked {
    cTrackedObject* mpObject;
    AutoRefCountTracked& operator=(void* p);    // 0x00b5f950
};

struct cStopwatch {                 // EA::Stopwatch at +0xa8
    uint32_t mStart[2];
    uint32_t mTotal[2];
    uint32_t pad[2];
    void Restart();                             // 0x00571e80
    void Reset() { mStart[0] = 0; mStart[1] = 0; mTotal[0] = 0; mTotal[1] = 0; }
};

struct cGameTimeManager {
    void IncPauseGate(uint32_t);                // 0x00b32220
    void DecPauseGate(uint32_t);                // 0x00b32250
    bool cce590();                              // 0x00cce590
};
struct cCheatHandler { void b10c40(int); void b13bb0(Vector3*, int);  // 0x00b10c40 / 0x00b13bb0
    uint8_t pad[0x10]; bool mbEdgeScroll;       // +0x10
    uint8_t pad11[0x365 - 0x11]; bool field_365; // +0x365
    uint8_t pad366[0x390 - 0x366]; bool field_390; // +0x390
};
struct cTriggerResolver { int ResolveTrigger(const char* name); };   // 0x00ad7db0
struct cFoodHUD {
    void ac7ab0(float amount, void* store, int);    // 0x00ac7ab0
    float ac7d10(float amount, void* store, int);   // 0x00ac7d10
};
struct cRelationshipManager { float RecordEvent(int a, int b, uint32_t ev, float amount); };  // 0x00d06240
struct cMissionUI {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void Refresh(int);                  // +0x28
    void cd3bf0(void*);                         // 0x00cd3bf0
    void PlayHint(uint32_t);                    // 0x00b706a0
};
struct cEffectManager { void ba48b0(int, void*, void*); };   // 0x00ba48b0
struct cTutorialUI { void e190c0(int); };                    // 0x00e190c0
struct cMusic { void e2f270(int); };                         // 0x00e2f270
struct cToolbar {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void Show(int);                     // +0x24
};
struct cWindowManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void* FindWindowByID(uint32_t);     // +0x40
};
struct cApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual cWindowManager* GetWindowManager(); // +0x50
};
struct cCamera {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual void* GetTarget();                  // +0x34
};
struct cRandom { uint32_t RandomUint32Uniform(uint32_t n); };   // 0x00a68fb0

// Ref-counted message objects created with the 6-arg EA operator new.
struct cEditorLaunchData {
    virtual void v00(); virtual void AddRef(); virtual void Release();
    uint32_t field_4;                           // +0x04
    int mRefCount;                              // +0x08
    uint32_t mEditorName;                       // +0x0c
    uint32_t pad10[(0x34 - 0x10) / 4];
    bool mbSporepediaCanSwitch;                 // +0x34
    bool mbDisableNameEdit;                     // +0x35
    bool mbAllowSporepedia;                     // +0x36
    bool mShowSaveButton;                       // +0x37
    bool mShowNewButton;                        // +0x38
    bool mShowExitButton;                       // +0x39
    bool mShowPublishButton;                    // +0x3a
    bool mShowCancelButton;                     // +0x3b
    bool field_3C;                              // +0x3c
    bool field_3D;                              // +0x3d
    uint8_t pad3e[0x64 - 0x3e];
    bool field_64;                              // +0x64
    uint8_t pad65[0x90 - 0x65];
    uint32_t field_90;                          // +0x90
    uint32_t pad94[2];
    cEditorLaunchData();                        // 0x005a9080
};
struct cSlotMessage {
    virtual void v00(); virtual void AddRef(); virtual void Release();
    int mParam;                                 // +0x08
    uint32_t pad0c[(0x30 - 0x0c) / 4];
    uint32_t mMessageID;                        // +0x30
    uint32_t pad34[3];
    cSlotMessage(int);                          // 0x00421c80
};

void* operator new(size_t size, const char* name, int, int, const char*, int);
void Editor_Launch(cEditorLaunchData* data);       // 0x005a9200

// ------------------------------------------------------------------ free functions / globals
cGameInputManager* GameInputManager();              // 0x00b3d250
cGameNounManager* NounManager();                    // 0x00b3d300
cGameTimeManager* GameTimeManager();                // 0x00b3d380
cMessageServer* MessageServer();                    // 0x0067dcc0
cApp* App();                                        // 0x0067dd10
cRelationshipManager* RelationshipManager();        // 0x00b3d2c0
cCheatHandler* CheatHandler();                      // 0x00b3d280
cCamera* CameraManager();                           // 0x00b3d240
cFoodHUD* FoodHUD();                                // 0x00b3d2b0
cTutorialUI* TutorialUI();                          // 0x00b3d3f0
cEffectManager* EffectManager();                    // 0x00b3d4c0
cTriggerResolver* TriggerResolver();                // 0x00b3d4d0
cMusic* MusicManager();                             // 0x00b3d4f0
cTerrainCursor* GetGameTerrainCursor();             // 0x00b30d70
cUIHints* UIHints();                                // 0x0067cac0
cUIHintsB* UIHintsB();                              // 0x0067cab0
cToolbar* TribeToolbar();                           // 0x00cc8b10
cMissionUI* MissionUI();                            // 0x00cd3440
void EndBanMode(int);                               // 0x00dd1840
void ToggleBanningContent(int);                     // 0x00dd17f0
void EndPlannerMode(int);                           // 0x00e09a50
bool IsBanDialogUp();                               // 0x00dd1220
void ShowConfirmationDialog(void*);                 // 0x00dd1aa0
bool IsPlannerDialogUp();                           // 0x00e09530
void ShowPlannerDialog(void*);                      // 0x00e09bf0
void* object_cast_GameData(void* p);                // 0x00c9f060
void object_cast_unused(void* p);                   // 0x00b18e00
cOwnedObject* object_cast_Owned(void* p);           // 0x00b676e0
void* object_cast_Type(void* p, uint32_t typeID);   // 0x00ac80d0
cWidget* object_cast_Widget(void* p);               // 0x00ac86f0
cCreatureObj* object_cast_Creature(void* p);        // 0x00f19200
cCitizen* object_cast_Citizen(void* p);             // 0x00c0c380
cFood* object_cast_Food(void* p);                   // 0x00ae6740
cCitizen* GetFoodGatherer(cFood* p);                // 0x00ae3390
cHut* GetFoodHut(cFood* p);                         // 0x00cce8d0
cTribeTool* object_cast_TribeTool(void* p);         // 0x00cce8f0
void NotifyNewTarget(void* p);                      // 0x00cd1960
void SetMoodState(cCreatureObj* c, int a, int b);   // 0x00c2e4e0
int GetRecorderState();                             // 0x00435e90
void KillSetiEffects(uint32_t id, int state);       // 0x00435ed0
void* window_cast(void* w);                         // 0x00b5cc20
void ResetTribeOverlay();                           // 0x00b676a0

extern int g_HandledCount;                          // 0x0169b1c4
extern Vector3 g_Vector3Zero;                       // 0x0169b1c8
extern uint32_t g_FoodAmountKey;                    // 0x0169b270
extern bool g_ShowTribeIcons;                       // 0x016c5c0c
extern bool g_FreeWill;                             // 0x01695370
extern bool g_CheatFlag365;                         // 0x0157ecdc
extern cRandom g_Random;                            // 0x01601760

// ------------------------------------------------------------------ the class
class cInputStrategy {
public:
    virtual ~cInputStrategy();
    uint32_t mStateMachine[0x38 / 4];               // +0x04
};

class IHandler {
public:
    virtual bool HandleMessage(uint32_t messageID, void* msg) = 0;
};

class cTribeInputStrategy : public cInputStrategy, public IHandler {
public:
    cTribeModeStrategy* mpModeStrategy;             // +0x40
    uint32_t field_44[5];                           // +0x44
    float mSkipDistanceSqr;                         // +0x58
    cCommunityEditor* mpCommunityEditor;            // +0x5c
    uint32_t mCommunityInput[0x40 / 4];             // +0x60 (an embedded input strategy)
    int mBanMode;                                   // +0xa0 (1 = ban, 2 = planner)
    uint32_t field_a4;                              // +0xa4
    cStopwatch mTrackingTimer;                      // +0xa8
    AutoRefCountTracked mTrackedObject;             // +0xc0
    bool mbFreeWillHint;                            // +0xc4
    uint32_t field_c8;                              // +0xc8
    uint32_t field_cc;

    static bool sIsInEditor;                        // 0x01686af0

    bool HandleMessage(uint32_t messageID, void* msg);

    int cceae0(void* obj, int param, Vector3* pos);     // 0x00cceae0
    int ccebd0(void* obj, int param, Vector3* pos);     // 0x00ccebd0
    int SetAbilityMode(void* obj, int param, Vector3* pos);  // 0x00cd0660
    void ccea10(void* target, int);                     // 0x00ccea10
    void ccec20(int);                                   // 0x00ccec20
    void cd0950();                                      // 0x00cd0950
    void cce5b0();                                      // 0x00cce5b0
    void cce5e0();                                      // 0x00cce5e0
    void Init(void*);                                   // 0x00cd0aa0
};

// ================================================================ 0x00cd1be0
bool cTribeInputStrategy::HandleMessage(uint32_t messageID, void* msgp)
{
    cMessageData* msg = (cMessageData*)msgp;

    if (messageID == 0x706bf688) {
        g_HandledCount++;
        return true;
    }
    if (messageID == 0x44eaa93) {
        if (mBanMode == 1) {
            mBanMode = 0;
            EndBanMode(1);
        } else {
            mBanMode = 1;
            ToggleBanningContent(1);
        }
        GameInputManager()->SetInputMode(0x4518420, 1);
        return true;
    }
    if (messageID == 0xfc6d2c) {
        if (mBanMode == 1) goto endBan;
        if (mBanMode == 2) goto endPlanner;
    } else if (messageID == 0x452e0ca) {
endBan:
        GameInputManager()->SetInputMode(0x4518420, 1);
        mBanMode = 0;
        EndBanMode(1);
        return true;
    } else if (messageID == 0x620222b) {
        cce5e0();
        GameInputManager()->SetInputMode(0x6203086, 1);
        return true;
    } else if (messageID == 0x620271c) {
endPlanner:
        GameInputManager()->SetInputMode(0x6203086, 1);
        mBanMode = 0;
        EndPlannerMode(1);
        return true;
    } else if (messageID == 0xb2699146) {
        if (mpCommunityEditor) {
            GameInputManager()->mEditorDepth++;
            mpModeStrategy->cd4b70(0);
            ccec20(0);
            UIHints()->SetEnabled(0, true);
            UIHints()->SetEnabled(1, true);
            cTribeModeStrategy::Instance()->cd52e0(0, g_Vector3Zero);
            cCommunityEditor* editor = mpCommunityEditor;
            editor->Activate(object_cast_GameData(NounManager()->GetPlayerTribe()), 0);
            if (msg && msg->mParam != -1)
                mpCommunityEditor->d09690(msg->mParam);
            GameInputManager()->SetInputStrategy(mCommunityInput, 0, 0);
        }
        return true;
    } else if (messageID == 0xb2699147) {
        GameInputManager()->mEditorDepth--;
        UIHints()->SetEnabled(0, true);
        UIHints()->SetEnabled(1, true);
        if (mpModeStrategy->mbTutorial)
            mpModeStrategy->SignalTribeEvent(0x64be5ff);
        if (mpCommunityEditor) {
            mpCommunityEditor->Deactivate(0, 1);
            ccec20(1);
            GameInputManager()->SetInputStrategy(mStateMachine, 0, 0);
            cTribe* tribe = NounManager()->GetPlayerTribe();
            tribe->ReserveToolsSlots(0);
            cIntVector* tools = tribe->GetTools();
            if ((uint32_t)(tools->mpEnd - tools->mpBegin) > 1)
                mpModeStrategy->SignalTribeEvent(0x9a44d4ab);
            cTribeTotals* t = tribe->c8e820(0);
            if (t->mCount[4] + t->mCount[3] + t->mCount[2] + t->mCount[1] + t->mCount[0] != 0)
                mpModeStrategy->SignalTribeEvent(0x5312da01);
        }
        return true;
    } else if (messageID == 0x44f1189) {
        cEditorLaunchData* data;
        int trigger = msg->mParam;
        if (trigger == TriggerResolver()->ResolveTrigger("TRG2CVG_PreEditor")) {
            GameTimeManager()->IncPauseGate(0x4bf38a6);
            GameInputManager()->mEditorDepth++;
            cTribeModeStrategy::Instance()->mbPreEditor = true;
            eastl::intrusive_ptr<cEditorLaunchData> request(new ("App", 0, 0, 0, 0) cEditorLaunchData());
            data = request.mpObject;
            data->mEditorName = 0x99e92f05;
            data->field_90 = 0x116dd1b;
            data->mbSporepediaCanSwitch = false;
            data->mbAllowSporepedia = true;
            data->mShowNewButton = true;
            data->mShowSaveButton = true;
            data->mShowExitButton = false;
            data->mShowCancelButton = false;
            data->field_3C = true;
            data->field_3D = true;
            data->field_64 = true;
            Editor_Launch(data);
            sIsInEditor = true;
            return true;
        }
        trigger = msg->mParam;
        if (trigger != TriggerResolver()->ResolveTrigger("TRG2CVG_ShowCityHall"))
            return false;
        GameTimeManager()->IncPauseGate(0x4bf38a6);
        GameInputManager()->mEditorDepth++;
        cTribeModeStrategy::Instance()->mbCityHallEditor = true;
        {
            eastl::intrusive_ptr<cEditorLaunchData> request(new ("App", 0, 0, 0, 0) cEditorLaunchData());
            uint32_t planetType = ((cPlanetRecord*)NounManager()->GetCurrentPlanet())->mPlanetType;
            data = request.mpObject;
            if (planetType == 0xc2ca9495)
                data->mEditorName = 0xf670aa43;
            else
                data->mEditorName = planetType != 0x60a78928 ? 0x7d433fad : 0x9ad7d4aa;
            data->field_90 = 0x116dd1b;
            data->mbSporepediaCanSwitch = false;
            data->mbAllowSporepedia = true;
            data->mShowNewButton = true;
            data->mShowSaveButton = true;
            data->mShowExitButton = false;
            data->mShowCancelButton = false;
            data->field_3C = true;
            data->field_3D = true;
            data->field_64 = true;
            Editor_Launch(data);
            sIsInEditor = true;
        }
        return true;
    } else if (messageID == 0xd33b6aa2) {
        UIHintsB()->Show(0);
        return false;
    } else if (messageID == 0x533b6aa4) {
        UIHintsB()->Show(1);
        return false;
    }

    // ---- generic messages: arg0 = object, arg1 = int, arg3 = position
    {
        cMessageArgs* args = msg->GetArgs();
        void* rawObject = ((cArgObject*)args->GetArg(0))->GetObject();
        void* object = object_cast_GameData(rawObject);
        object_cast_unused(rawObject);
        int param = *(int*)args->GetArg(1);
        Vector3 pos = *(Vector3*)args->GetArg(3);
        int result = 0;

        switch (messageID) {
        case 0xe615bf:
            result = cceae0(object, param, &pos);
            break;
        case 0xe39174:
            result = ccebd0(object, param, &pos);
            break;
        case 0xfc6d2c: {
            ccea10(0, 1);
            cCheatHandler* cheat = CheatHandler();
            if (cheat) cheat->b10c40(0);
            cTerrainCursor* cursor = GetGameTerrainCursor();
            if (mpModeStrategy->GetActionCount() > 0 || cursor->IsPlacing()) {
                mpModeStrategy->CancelAction();
                cursor->Reset();
                cursor->SetVisible(0);
                cursor->Cancel();
            } else {
                MessageServer()->MessageSend(0x64eb18e, 0, 0);
            }
            break;
        }
        case 0xfc6f3b:
            NotifyNewTarget(object);
            result = SetAbilityMode(object, param, &pos);
            break;
        case 0xfc6f3c: {
            cCitizen* citizen = object_cast_Citizen(object);
            if (citizen) mpModeStrategy->TrackTribeMember(citizen, 1);
            break;
        }
        case 0xfdd7df:
            g_ShowTribeIcons = !g_ShowTribeIcons;
            if (cTribeModeStrategy::Instance()->GetDisplayStrategy())
                cTribeModeStrategy::Instance()->GetDisplayStrategy()->MakeTribeIcons();
            break;
        case 0xfdd7de: {
            cTribe* tribe = NounManager()->GetPlayerTribe();
            cOwnedObject* owned = object_cast_Owned(object);
            if (owned && owned->GetTribe()) tribe = owned->GetTribe();
            if (tribe) {
                if (param > 0) {
                    float amount = (float)param;
                    FoodHUD()->ac7ab0(amount, &tribe->mFoodStore, tribe->c8e990());
                    tribe->c94b50(amount);
                } else if (param < 0) {
                    float amount = (float)-param;
                    FoodHUD()->ac7d10(amount, &tribe->mFoodStore, 0);
                    tribe->c94b50(-amount);
                }
            }
            break;
        }
        case 0x17e03fe:
            switch (param) {
            case 0:
                mTrackingTimer.Reset();
                if (mTrackedObject.mpObject) {
                    cTrackedObject* old = mTrackedObject.mpObject;
                    mTrackedObject.mpObject = 0;
                    old->Release();
                }
                break;
            case 1: {
                mTrackingTimer.Restart();
                mTrackedObject = object;
                char* typed = (char*)object_cast_Type(object, 0x18c88e4);
                if (typed && *(uint32_t*)(typed + 0x228) == 0x356eb8a && mTrackedObject.mpObject) {
                    cTrackedObject* old = mTrackedObject.mpObject;
                    mTrackedObject.mpObject = 0;
                    old->Release();
                }
                break;
            }
            }
            mpModeStrategy->cd4b70(0);
            break;
        case 0x17e0419: {
            cCheatHandler* cheat = CheatHandler();
            if (cheat) {
                cheat->mbEdgeScroll = !cheat->mbEdgeScroll;
                if (cheat->mbEdgeScroll) {
                    cTribeModeStrategy* mode = cTribeModeStrategy::Instance();
                    eastl::wstring text(L"Edge Scroll ON");
                    ((cTribeHUD*)mode->GetDisplayStrategy())->ShowMessage(text);
                } else {
                    cTribeModeStrategy* mode = cTribeModeStrategy::Instance();
                    eastl::wstring text(L"Edge Scroll OFF");
                    ((cTribeHUD*)mode->GetDisplayStrategy())->ShowMessage(text);
                }
            }
            break;
        }
        case 0x17e041c:
            cd0950();
            break;
        case 0x1aedf1d:
            cTribeModeStrategy::Instance()->cd71b0(mpModeStrategy->mTrackHut == 0, 1);
            break;
        case 0x1aedf1e: {
            cTribe* tribe = NounManager()->GetPlayerTribe();
            if (!tribe) break;
            if (param & 1) {
                cCitizenVector* members = tribe->GetMembers();
                if (members->mpBegin == members->mpEnd) break;
                uint32_t count = (uint32_t)(members->mpEnd - members->mpBegin);
                uint32_t start = mpModeStrategy->GetTrackIndex();
                if (start >= count) start = 0;
                Vector3 from = *members->mpBegin[start]->mSpatial.GetPosition();
                uint32_t i = start;
                cCitizen* next;
                for (;;) {
                    i = (i + 1) % count;
                    if (i == start) {
                        next = members->mpBegin[(i + 1) % count];
                        break;
                    }
                    next = members->mpBegin[i];
                    Vector3* p = next->mSpatial.GetPosition();
                    float dx = from.x - p->x;
                    float dy = from.y - p->y;
                    float dz = from.z - p->z;
                    if (!(mSkipDistanceSqr > dz * dz + dy * dy + dx * dx)) break;
                }
                if (next) mpModeStrategy->TrackTribeMember(next, 1);
                break;
            }
            if (CheatHandler() && !CheatHandler()->field_390)
                CheatHandler()->b13bb0(tribe->mSpatial.GetPosition(0), 0);
            mpModeStrategy->SetTrackHut(1);
            mpModeStrategy->cd4b70(0);
            break;
        }
        case 0x1aedf20:
        case 0x1aedf21:
        case 0x1aedf22:
        case 0x1aedf23:
        case 0x1aedf24:
            mpModeStrategy->cd4b70(0);
            break;
        case 0x1d5e693: {
            if (!object) break;
            cWidget* widget = object_cast_Widget(object);
            if (widget) widget->Toggle();
            cCreatureObj* creature = object_cast_Creature(object);
            if (!creature) break;
            if (widget->IsOn())
                SetMoodState(creature, 3, creature->mMoodState);
            else
                SetMoodState(creature, creature->mMoodState, 1);
            break;
        }
        case 0x2c0edc1: {
            cTribe* tribe = NounManager()->GetPlayerTribe();
            cOwnedObject* owned = object_cast_Owned(object);
            if (owned && owned->GetTribe()) tribe = owned->GetTribe();
            if (tribe) tribe->SelectAll(1);
            break;
        }
        case 0x2c0edc2: {
            cTribe* tribe = NounManager()->GetPlayerTribe();
            cOwnedObject* owned = object_cast_Owned(object);
            if (owned && owned->GetTribe()) tribe = owned->GetTribe();
            if (!tribe) break;
            Vector3* where = owned ? owned->mSpatial.GetPosition() : &g_Vector3Zero;
            cEffect* effect = cTribeModeStrategy::Instance()->cd52e0(3, *where);
            if (effect) {
                effect->SetFlags(8);
                effect->mpParams->field_1c = 1;
            }
            if (tribe->GetMemberCount() > 1) tribe->SelectMembers(0, 1);
            break;
        }
        case 0x346048a: {
            GetGameTerrainCursor()->Reset();
            cCitizen* citizen = object_cast_Citizen(object);
            if (citizen && mpModeStrategy->GetDisplayStrategy())
                mpModeStrategy->GetDisplayStrategy()->ccaa80(citizen);
            if (!GetGameTerrainCursor()->IsActive()) result = 1;
            break;
        }
        case 0x3c708fa:
            g_FreeWill = !g_FreeWill;
            if (g_FreeWill) {
                cTribeModeStrategy* mode = cTribeModeStrategy::Instance();
                eastl::wstring text(L"Free Will ON");
                ((cTribeHUD*)mode->GetDisplayStrategy())->ShowMessage(text);
            } else {
                cTribeModeStrategy* mode = cTribeModeStrategy::Instance();
                eastl::wstring text(L"Free Will OFF");
                ((cTribeHUD*)mode->GetDisplayStrategy())->ShowMessage(text);
            }
            break;
        case 0x3c708fb:
            if (CheatHandler()) {
                g_CheatFlag365 = !g_CheatFlag365;
                bool v = g_CheatFlag365;
                CheatHandler()->field_365 = v;
            }
            break;
        case 0x4518421:
            if (!IsBanDialogUp() && object) ShowConfirmationDialog(object);
            break;
        case 0x4518422:
            cce5b0();
            GameInputManager()->SetInputMode(0x4518420, 1);
            break;
        case 0x46ab558: {
            cFood* food = object_cast_Food(object);
            if (!food) break;
            void* target = 0;
            cCitizen* gatherer = GetFoodGatherer(food);
            if (gatherer && !gatherer->mSpatial.IsDestroyed()) target = gatherer;
            cHut* hut = GetFoodHut(food);
            if (hut && !hut->mSpatial.IsDestroyed()) target = hut->GetTribe();
            if (target) MissionUI()->cd3bf0(target);
            KillSetiEffects(0x65f6559d, GetRecorderState());
            food->SetAmount(food->GetAmount(-1, 2, &g_FoodAmountKey, 0) * 0.25f);
            break;
        }
        case 0x46ab559: {
            cTribeTool* tool = object_cast_TribeTool(object);
            if (tool) tool->SetHealth((float)param + tool->mHealth);
            cTribe* tribe = NounManager()->GetPlayerTribe();
            cOwnedObject* owned = object_cast_Owned(object);
            if (tribe && owned && owned->GetTribe()) {
                if (owned->GetTribe() != tribe) MissionUI()->cd3bf0(owned->GetTribe());
                cTribe* other = owned->GetTribe();
                RelationshipManager()->RecordEvent(other->GetPoliticalID(), tribe->GetPoliticalID(),
                                                   0x530cf0a + (param <= 0), 1.0f);
            }
            cCreatureObj* creature = object_cast_Creature(object);
            if (creature) {
                if (!creature->mSpatial.IsDestroyed()) MissionUI()->cd3bf0(creature);
                creature->mFlags |= 0x80;
                EffectManager()->ba48b0(3, &creature->mEffectRef, creature);
                MissionUI()->Refresh(0);
            }
            cTribeModeStrategy::Instance()->IncrementGoalProgress();
            break;
        }
        case 0x46ab55a: {
            cFood* food = object_cast_Food(object);
            if (food) food->Consume(0);
            break;
        }
        case 0x5666546:
            cTribeModeStrategy::Instance()->cdb3a0(g_Random.RandomUint32Uniform(2) + 1, 0);
            cTribeModeStrategy::Instance()->IncrementGoalProgress();
            break;
        case 0x57526c7: {
            cTribe* tribe = NounManager()->GetPlayerTribe();
            cOwnedObject* owned = object_cast_Owned(object);
            if (!tribe || !owned || !owned->GetTribe()) break;
            cTribe* other = owned->GetTribe();
            void* enemyTarget = tribe->GetEnemyTarget();
            int wanted = tribe->GetAdultPopulation() - 2;
            const int one = 1;
            int count = *(wanted > one ? &wanted : &one);
            cCitizenVector* members = other->GetMembers();
            int n = (int)(members->mpEnd - members->mpBegin);
            eastl::fixed_vector32<cCitizen*> chosen;
            int needed = count;
            int remaining = n;
            for (int i = 0; i < n; i++) {
                cCitizen* c = members->mpBegin[i];
                if (c->c0b760() == 1) {
                    const int zero = 0;
                    int need = needed;
                    const int* pNeed = need < 0 ? &zero : &need;
                    if (c->c24560() || *pNeed >= remaining) {
                        chosen.push_back(c);
                        needed--;
                    }
                }
                remaining--;
            }
            int j = 0;
            for (cCitizen** it = chosen.begin(); it != chosen.end(); ++it) {
                if (param > 0)
                    (*it)->GiveOrder(9, tribe, 0);
                else if (enemyTarget)
                    (*it)->GiveOrder(0xf, enemyTarget, 0);
                if (++j >= count) break;
            }
            break;
        }
        case 0x5fa3b4d:
            if (mpModeStrategy->GetDisplayStrategy())
                mpModeStrategy->GetDisplayStrategy()->cca060();
            break;
        case 0x6203087:
            if (!IsPlannerDialogUp() && object) ShowPlannerDialog(object);
            break;
        case 0x6203088:
            cce5e0();
            GameInputManager()->SetInputMode(0x6203086, 1);
            break;
        case 0x6204441:
            if (mpModeStrategy->GetDisplayStrategy())
                mpModeStrategy->GetDisplayStrategy()->ccab80();
            if (!GetGameTerrainCursor()->IsActive()) result = 1;
            break;
        case 0x6417055: {
            bool off = param < 1;
            ccea10(object_cast_GameData(CameraManager()->GetTarget()), off);
            if (!off) {
                if (!mpModeStrategy->cd4460(0x56d1871) && mpModeStrategy->cd4460(0x64be5ff))
                    mpModeStrategy->SignalTribeEvent(0x83861976);
                mpModeStrategy->cd4b70(0);
            }
            break;
        }
        case 0x6417056: {
            bool on = param > 0;
            if (CheatHandler() && CheatHandler()->field_390) on = false;
            cCheatHandler* w = (cCheatHandler*)window_cast(
                App()->GetWindowManager()->FindWindowByID(0xe3057616));
            if (w) w->b10c40(on);
            if (mbFreeWillHint && !on) {
                cTribeModeStrategy* mode = cTribeModeStrategy::Instance();
                if (!mode->cd4460(0x56d1871) && mode->cd4460(0x64be5ff))
                    mode->SignalTribeEvent(0x53203528);
            }
            mbFreeWillHint = on;
            break;
        }
        case 0x65fa205:
            ResetTribeOverlay();
            break;
        case 0x107e6fa9: {
            cTribe* tribe = NounManager()->GetPlayerTribe();
            if (tribe) tribe->c8fb50();
            break;
        }
        case 0x506d38c9:
            NotifyNewTarget(object);
            Init(rawObject);
            break;
        case 0x71d4dfc8:
            if (mpCommunityEditor) {
                if (mpCommunityEditor->d0a160())
                    MessageServer()->MessagePost(0xb2699147, 0, 0, 0);
                else
                    result = 2;
            }
            break;
        case 0x71d4dfc9: {
            eastl::intrusive_ptr<cSlotMessage> slot(new ("App", 0, 0, 0, 0) cSlotMessage(0));
            cSlotMessage* m = slot.mpObject;
            m->mMessageID = 0xb2699146;
            m->mParam = param == 0xcf ? 2 : 0;
            MessageServer()->MessagePost(m->mMessageID, m, 0, 0);
            break;
        }
        case 0x90a1f327:
            TribeToolbar()->Show(1);
            break;
        case 0xb449df6f:
            TutorialUI()->e190c0(0);
            break;
        case 0xb50a6210: {
            mpModeStrategy->field_198 = true;
            mpModeStrategy->mbTutorial = false;
            mpModeStrategy->cd6390(0);
            if (GameTimeManager()->cce590()) {
                GameTimeManager()->DecPauseGate(0x64beb65);
                MusicManager()->e2f270(0);
                GameInputManager()->mEditorDepth--;
            }
            if (CheatHandler()) CheatHandler()->field_390 = false;
            cTribePlanet* planet = (cTribePlanet*)NounManager()->GetCurrentPlanet();
            if (!planet) break;
            planet->c77bf0(0x64c010f);
            planet->c77bf0(0x53203528);
            planet->c77bf0(0x83861976);
            planet->c77bf0(0x64d44f9);
            planet->c77bf0(0x64e70b3);
            planet->c77bf0(0x5ac72d7c);
            planet->c77bf0(0x56d1871);
            if (planet->c772c0(0x14363974)) break;
            cTribe* tribe = NounManager()->GetPlayerTribe();
            if (!tribe) break;
            if (tribe->c8e850() && tribe->c8e870())
                MissionUI()->PlayHint(0x2d99d0b);
            else if (tribe->c8e850())
                MissionUI()->PlayHint(0x391c432);
            else if (tribe->c8e870())
                MissionUI()->PlayHint(0x69ba7f0d);
            break;
        }
        case 0xf0a1f2e5:
            object_cast_Type(object, 0x1e4daae);
            break;
        }

        EA::Variant v(result);
        msg->GetResult()->SetResult(0, &v);
    }
    return false;
}
