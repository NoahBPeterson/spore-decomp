// Slice s00cd8070 -- SP::cTribeModeStrategy::HandleMessage (tribe-stage strategy message handler).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the event-payload temporaries get no EH frame).
// HandleMessage overrides the IHandler at +8 of the retail cTribeModeStrategy, so `this` inside it is
// the +8 subobject and calls on the strategy itself go through `lea ecx,[this-8]`.
#include "types.h"

// ------------------------------------------------------------------ small helper types
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey() {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};

__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

template <class T> __forceinline const T& min_ref(const T& a, const T& b) { return (b < a) ? b : a; }

// ------------------------------------------------------------------ messages
struct cMessage {                   // generic message payload (field layout per message id)
    uint32_t pad00[2];
    void* m08;          // +0x08
    uint32_t m0c;       // +0x0c
    uint32_t m10;       // +0x10
    uint32_t m14;       // +0x14
    uint32_t m18;       // +0x18 (address used as an argument for the planner messages)
    uint32_t pad1c[3];
    void* m28;          // +0x28
    uint32_t pad2c[6];
    bool m44;           // +0x44
};

struct XformMsg {                   // 0x38 bytes; ctor @0x434040
    uint16_t flags;
    uint16_t count;
    Vector3 pos;
    float scale;
    float rot[9];
    XformMsg();         // 0x00434040
};

struct cTransitionEvent {           // 0x30-byte event payload (ad7a30 ctor / ad7ad0 dtor)
    uint32_t data[12];
    cTransitionEvent(void* src);    // 0x00ad7a30
    ~cTransitionEvent();            // 0x00ad7ad0
};

// ------------------------------------------------------------------ managers / game objects (stubs)
struct cPlayerState {
    void FUN_00adf390(int);                                        // 0x00adf390
    void FUN_00ae09b0(uint32_t id, const cTransitionEvent& e, int); // 0x00ae09b0
    void FUN_00ae0930(const char* s, int a, int b, int c, int d, int e);  // 0x00ae0930
    int  FUN_00ad7db0(const char* name);                           // 0x00ad7db0
};
cPlayerState* FUN_00b3d4d0();       // 0x00b3d4d0

struct cConfigManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual int GetValue(uint32_t id);    // +0x30
};
cConfigManager* ConfigManager();    // 0x0067dd30

struct cGameTimeManager { void IncPauseGate(uint32_t id); };   // 0x00b32220
cGameTimeManager* GameTimeManager();     // 0x00b3d380

struct cHintManager {
    void ShowHint(ResourceKey key, void* handler, int a, float x, float y, float z, int b, int c);  // 0x0067aaf0 
};
cHintManager* FUN_0067caf0();       // 0x0067caf0

struct cAchievements { void FUN_00676ed0(uint32_t id, int a, int b); };   // 0x00676ed0
cAchievements* FUN_00675250();      // 0x00675250

struct cPollinator { void FUN_0060d860(uint32_t id, const ResourceKey& key); };       // 0x0060d860
cPollinator* FUN_0067cb30();        // 0x0067cb30


struct cTerrainSphere {
    uint32_t pad[0x10f0 / 4];
    float m10f0;        // +0x10f0
    float m10f4;        // +0x10f4
    uint32_t pad10f8[2];
    void* m1100;        // +0x1100
    int  FUN_00c77340(uint32_t id);              // 0x00c77340
    void FUN_00cd3e00(void* p);                  // 0x00cd3e00
    void FUN_00cd3e30(void* p);                  // 0x00cd3e30
    void FUN_00c77320(uint32_t id);              // 0x00c77320
    void FUN_00c79f00(uint32_t id, int value);   // 0x00c79f00
};

struct cPositional {                // subobject at +0x120 of tribes
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();   // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool IsDestroyed();             // +0x58
};

struct cBehaviorList { void* FUN_00bc97f0(int a, uint32_t flags, float f, void* target); };  // 0x00bc97f0
struct cCreature {
    uint32_t pad[0xb4c / 4];
    struct { uint32_t pad[2]; cBehaviorList list; }* mpBehavior;   // +0xb4c (list at +8)
};
struct cCreatureVector { cCreature** mpBegin; cCreature** mpEnd; };

struct cHutOwner {                  // object returned by cTribe vslot 0xac
    uint32_t pad[0x34 / 4];
    uint32_t m34;       // +0x34
};

struct cTribe {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual cCreatureVector* GetMembers();      // +0x90
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8();
    virtual char* GetHut();                     // +0xac
    uint32_t pad04[(0x120 - 4) / 4];
    cPositional mPositional;                    // +0x120
    void FUN_00c8e730(int);                     // 0x00c8e730
    void FUN_00c8eb50(ResourceKey* key);         // 0x00c8eb50
    void FUN_00c93000();                        // 0x00c93000
    void UpgradeHut();                          // 0x00c919e0
    void UpdateModel();                         // 0x00c91a40
    void FUN_00c99840();                        // 0x00c99840
    cCreature* GetChieftain();                  // 0x00c8fd30
    struct cTribeTools* FUN_00c90460();         // 0x00c90460
};

struct cToolEffects {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void PlayEffect(void* obj, uint32_t id, int a, float f, int b);   // +0x70
};
struct cToolOwner {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void SetPosition(Vector3* v);       // +0x38
    virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual cToolEffects* GetEffects();         // +0xb0
};
struct cToolItem {
    uint32_t pad;
    uint32_t mFlags;                            // +0x04, bit 0 = effect played
    bool IsEffectPlayed() const { return (mFlags & 1) != 0; }
    void SetEffectPlayed() { mFlags |= 1; }
};
template <class T> struct PtrVector {           // eastl::vector<T*>
    T** mpBegin;
    T** mpEnd;
    T** mpCapacity;
    uint32_t mAllocator;
    bool empty() const { return mpBegin == mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T*& operator[](uint32_t i) { return mpBegin[i]; }
};
struct cTribeTools {
    uint32_t pad[0x34 / 4];
    cToolOwner mOwner;                          // +0x34
    uint32_t pad38[(0x108 - 0x38) / 4];
    PtrVector<cToolItem> mItems;                // +0x108
    uint32_t pad118;
    PtrVector<void> mItemModels;                // +0x11c
};

struct cGameNounManager {
    cTribe* GetPlayerTribe();                       // 0x00bfc5f0
    cTerrainSphere* GetCurrentTerrainSphere();      // 0x00f67d90
};
cGameNounManager* NounManager();    // 0x00b3d300

uint32_t GetCurrentGameMode();      // 0x00b5b800
const uint32_t kTribeModeID = 0x1654c02;

struct cTerrainMgr {
    struct cEntry { uint32_t pad[2]; uint32_t m08; uint32_t pad0c; uint32_t m10; };
    cEntry* FUN_00b1de80();         // 0x00b1de80
};
cTerrainMgr* FUN_00b3d320();        // 0x00b3d320
extern cTerrainMgr::cEntry* DAT_01581288;

struct cXformSource {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void GetTransform(XformMsg* xf);    // +0x20
};

struct cTribeTuningData { void Init(); };   // 0x00ce6af0
extern cTribeTuningData gTribeTuningData;   // 0x01581208
void FUN_00d40b20(uint32_t id);     // 0x00d40b20

struct cB3d340 { void FUN_00b27170(); };   // 0x00b27170
cB3d340* FUN_00b3d340();            // 0x00b3d340
struct cEventLog { void FUN_00dd6d70(); };   // 0x00dd6d70
cEventLog* EventLog();              // 0x00b3d3e0

struct cPlanetModel { void FUN_00b81630(Vector3* out, Vector3* in); };   // 0x00b81630
cPlanetModel* PlanetModel();        // 0x00b3d350

struct cToolManager {
    int FUN_00ac79d0();                                  // 0x00ac79d0
    struct cToolPlacer* FUN_00ac7ab0(float f, int a, int b);    // 0x00ac7ab0
};
cToolManager* FUN_00b3d2b0();       // 0x00b3d2b0
extern float DAT_015812d4;

struct cToolPlacer {                // returned by cToolManager::FUN_00ac7ab0
    uint32_t pad[0x34 / 4];
    cToolOwner mOwner;              // +0x34
    uint32_t pad38[(0x124 - 0x38) / 4];
    bool m124;                      // +0x124
    struct cToolHost {
        virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
        virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
        virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
        virtual void Attach(cToolPlacer* p);    // +0x30
    }* mpHost;                      // +0x128
    uint32_t pad12c;
    int m130;                       // +0x130
};

struct cGameInputManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void SetInputStrategy(void* strategy, int, int);    // +0x20
};
cGameInputManager* GameInputManager();   // 0x00b3d250

struct cHintTarget;
struct cHutTracker { void FUN_00cd52e0(int kind, Vector3 pos); };   // 0x00cd52e0
extern cHutTracker* DAT_0169b2c8;

void FUN_00cd49d0(uint32_t a, uint32_t b, void* c);  // 0x00cd49d0

// civ-mode strategy and its ref-counted city/vehicle object
struct cCivObject {
    uint32_t pad;
    uint32_t mFlags;                // +0x04
    uint32_t pad08[(0x40 - 8) / 4];
    int mnRefCount;                 // +0x40
};
struct cCivPtr {                    // intrusive pointer: inline AddRef, out-of-line dtor
    cCivObject* mpObject;
    cCivPtr(cCivObject* p) : mpObject(p) { if (p) ++p->mnRefCount; }
    ~cCivPtr();                     // 0x005765e0
};
struct cCivModeStrategy {
    uint32_t pad[0x104 / 4];
    cCivObject* m104;               // +0x104
};
cCivModeStrategy* CivModeStrategy();     // 0x00cf74c0

// tribe-mode sub-objects
struct cTribeInputStrategy {
    uint32_t pad;
    uint32_t mInput;                // +0x04 (input-strategy interface)
    uint32_t pad08[(0x5c - 8) / 4];
    struct cTool { bool FUN_00d09660(); }* m5c;  // +0x5c
    void FUN_00cd16a0(int value);   // 0x00cd16a0
};
struct cTribeDisplayStrategy {
    void FUN_00cc93b0(int);         // 0x00cc93b0
    void FUN_00cc8aa0(int);         // 0x00cc8aa0
};
struct cTribeMusic { void FUN_00b706a0(uint32_t id); };   // 0x00b706a0
struct cTribePlanner { void FUN_00572620(cMessage* msg); };   // 0x00572620

extern char DAT_0157f174[];         // hint handlers
extern char DAT_0157f17c[];
extern ResourceKey DAT_0157f0e4, DAT_0157f0f0, DAT_0157f0fc, DAT_0157f108, DAT_0157f120,
    DAT_0157f12c, DAT_0157f15c, DAT_0157f168;

// ------------------------------------------------------------------ the strategy
struct cIModeStrategy {
    virtual void v00();
    uint32_t pad04;
};
struct IHandler {
    virtual bool HandleMessage(uint32_t messageID, void* msg);
};

class cTribeModeStrategy : public cIModeStrategy, public IHandler {
public:
    uint32_t pad0c[(0x28 - 0xc) / 4];
    bool mbInCityHallEditorDuringTransitionFlow;    // +0x28
    bool mbInAccessoryEditorDuringTransitionFlow;   // +0x29
    uint16_t pad2a;
    uint32_t pad2c[(0x23c - 0x2c) / 4];
    cTribeInputStrategy* mpInputStrategy;           // +0x23c
    cTribeDisplayStrategy* mpDisplayStrategy;       // +0x240
    uint32_t pad244[(0x2f8 - 0x244) / 4];
    cTribePlanner mPlanner;                         // +0x2f8
    uint32_t pad2fc[(0x394 - 0x2fc) / 4];
    cTribeMusic* mpMusic;                           // +0x394

    void FUN_00cd5010(void* data);                  // 0x00cd5010
    void NotifyDataDestroyed(void* data);           // 0x00cd5070
    void SignalTribeEvent(uint32_t id);             // 0x00cd6980
    void SetTrackHut(bool b);                       // 0x00cd4bc0
    void FUN_00cd5b80();                            // 0x00cd5b80
    void FUN_00cd4b70(int);                         // 0x00cd4b70
    void FUN_00cd7320(Vector3 v);                   // 0x00cd7320

    bool HandleMessage(uint32_t messageID, void* msg);
};

static __forceinline void ShowHint(const ResourceKey& key, void* handler)
{
    FUN_0067caf0()->ShowHint(key, handler, 0, -1.0f, -1.0f, 0.0f, 0, 0);
}

// 0x00cd8070
bool cTribeModeStrategy::HandleMessage(uint32_t messageID, void* msgData)
{
    cMessage* msg = (cMessage*)msgData;
    switch (messageID) {
    case 0x1a0219e: {
        void* data = (void*)msg->m10;
        if (data) {
            if ((int)msg->m08 == 3) FUN_00cd5010(data);
            if ((int)msg->m08 == 4) {
                NotifyDataDestroyed(data);
                return false;
            }
        }
        break;
    }
    case 0xf62def: {
        uint32_t id = msg->m10;
        uint32_t idx = msg->m18;
        if (id == 0xf71fa311) {
            FUN_00d40b20(id);
            return false;
        }
        if (FUN_00b3d320() && GetCurrentGameMode() == kTribeModeID) {
            cTerrainMgr::cEntry* e = FUN_00b3d320()->FUN_00b1de80();
            if (e == DAT_01581288 && e->m08 == idx && e->m10 == id) {
                gTribeTuningData.Init();
                return false;
            }
        }
        break;
    }
    case 0x30c11c7:
        if (msg && msg->m0c == 0x116dd1b) {
            FUN_00b3d4d0()->FUN_00adf390(1);
            SignalTribeEvent(0x5312da01);
            mPlanner.FUN_00572620(msg->m44 ? 0 : msg);
            if (mbInCityHallEditorDuringTransitionFlow) {
                if (msg->m14 == 0x99e92f05 && !msg->m44)
                    NounManager()->GetCurrentTerrainSphere()->FUN_00cd3e00(&msg->m18);
                return true;
            }
            if (mbInAccessoryEditorDuringTransitionFlow) {
                uint32_t k = msg->m14;
                if ((k == 0x7d433fad || k == 0xf670aa43 || k == 0x9ad7d4aa) && !msg->m44)
                    NounManager()->GetCurrentTerrainSphere()->FUN_00cd3e30(&msg->m18);
                return true;
            }
        }
        break;
    case 0x420e32a:
        FUN_00b3d340()->FUN_00b27170();
        EventLog()->FUN_00dd6d70();
        return false;
    case 0x44f1189:
        if (GetCurrentGameMode() == kTribeModeID) {
            cTribeInputStrategy* input = mpInputStrategy;
            if (input && input->m5c && !input->m5c->FUN_00d09660())
                mpDisplayStrategy->FUN_00cc93b0(1);
            int trigger = (int)msg->m08;
            if (trigger == FUN_00b3d4d0()->FUN_00ad7db0("TRG_Begin")) {
                if (ConfigManager()->GetValue(0x4ea96cb)) {
                    mpMusic->FUN_00b706a0(0x5312da01);
                    { cGameTimeManager* timeMgr = GameTimeManager(); timeMgr->IncPauseGate(0x4bf38a7); }
                    ShowHint(DAT_0157f108, 0);
                    ShowHint(DAT_0157f120, 0);
                    ShowHint(DAT_0157f0f0, DAT_0157f17c);
                    return false;
                }
            } else if (trigger == FUN_00b3d4d0()->FUN_00ad7db0("TRG_FirstBaby")) {
                if (ConfigManager()->GetValue(0x4ea96cb)) {
                    { cGameTimeManager* timeMgr = GameTimeManager(); timeMgr->IncPauseGate(0x4bf38a7); }
                    ShowHint(DAT_0157f0e4, DAT_0157f174);
                    return false;
                }
            } else if (trigger == FUN_00b3d4d0()->FUN_00ad7db0("TRG_PRE_FirstTribeAppears")) {
                if (ConfigManager()->GetValue(0x4ea96cb)) {
                    void* hasTribes = NounManager()->GetCurrentTerrainSphere()->m1100;
                    { cGameTimeManager* timeMgr = GameTimeManager(); timeMgr->IncPauseGate(0x4bf38a7); }
                    if (hasTribes) {
                        ShowHint(DAT_0157f15c, DAT_0157f174);
                        return false;
                    }
                    ShowHint(DAT_0157f168, DAT_0157f174);
                    return false;
                }
            }
        }
        break;
    case 0x56cf231:
        SetTrackHut(true);
        return false;
    case 0x575116e: {
        cTribe* tribe = NounManager()->GetPlayerTribe();
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        if (tribe && sphere && sphere->FUN_00c77340(0x575e6e1)) {
            sphere->FUN_00c77320(0x575e6e1);
            tribe->FUN_00c93000();
            tribe->UpgradeHut();
            return false;
        }
        break;
    }
    case 0x575116f: {
        cTribe* tribe = NounManager()->GetPlayerTribe();
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        if (tribe && sphere && sphere->FUN_00c77340(0x575e6e2)) {
            sphere->FUN_00c77320(0x575e6e2);
            tribe->UpdateModel();
            return false;
        }
        break;
    }
    case 0x5751170: {
        cTribe* tribe = NounManager()->GetPlayerTribe();
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        if (tribe && sphere && sphere->FUN_00c77340(0x575e6e3)) {
            sphere->FUN_00c77320(0x575e6e3);
            tribe->FUN_00c99840();
            return false;
        }
        break;
    }
    case 0x5c80207: {
        cTribe* tribe = NounManager()->GetPlayerTribe();
        if (tribe) {
            DAT_0169b2c8->FUN_00cd52e0(4, tribe->mPositional.GetPosition());
            char* victim = (char*)msg->m08;
            uint32_t a = msg->m10;
            uint32_t b = msg->m18;
            FUN_00b3d4d0()->FUN_00ae09b0(0xf1a267bd, cTransitionEvent(victim ? victim + 0xc0 : 0), 0);
            FUN_00cd49d0(a, b, victim ? victim + 0x5a8 : 0);
            mpDisplayStrategy->FUN_00cc93b0(0);
            FUN_00675250()->FUN_00676ed0(0xd456d958, 4, 1);
            FUN_00b3d4d0()->FUN_00ae0930("TRG_PRE_PopDestroyed", 1, 0, 0, 0, 0);
            ResourceKey key(0, 0, 0);
            tribe->FUN_00c8eb50(&key);
            FUN_0067cb30()->FUN_0060d860(0x89d36710, key);
            return false;
        }
        break;
    }
    case 0x58baddd: {
        cTribe* tribe = (cTribe*)msg->m08;
        void* target = (void*)msg->m10;
        cTribe* attacker = (cTribe*)msg->m18;
        if (tribe) {
            tribe->FUN_00c8e730(1);
            if (tribe->mPositional.IsDestroyed()) {
                DAT_0169b2c8->FUN_00cd52e0(4, tribe->mPositional.GetPosition());
                char* hut = tribe->GetHut();
                FUN_00b3d4d0()->FUN_00ae09b0(0xd749c1, cTransitionEvent(hut ? hut + 0x34 : 0), 0);
                mpDisplayStrategy->FUN_00cc93b0(0);
                FUN_00cd49d0((uint32_t)attacker, 0, hut ? hut + 0x120 : 0);
                FUN_00675250()->FUN_00676ed0(0xd456d958, 4, 1);
                FUN_00b3d4d0()->FUN_00ae0930("TRG_PRE_HutDestroyed", 1, 0, 0, 0, 0);
                ResourceKey key(0, 0, 0);
                tribe->FUN_00c8eb50(&key);
                FUN_0067cb30()->FUN_0060d860(0x89d36710, key);
                return false;
            }
            if (target && attacker) {
                cCreatureVector* members = attacker->GetMembers();
                for (cCreature** it = members->mpBegin; it != members->mpEnd; ++it)
                    (*it)->mpBehavior->list.FUN_00bc97f0(0, 0x4000000, 3.402823466e+38f, target);
                return false;
            }
        }
        break;
    }
    case 0x5cc2589: {
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        if (sphere) {
            const float& lo = min_ref(sphere->m10f0, sphere->m10f4);
            if (lo / sphere->m10f4 >= 1.0f) {
                mpDisplayStrategy->FUN_00cc8aa0(1);
                sphere->FUN_00c79f00(0x566cdf0, RoundToInt(sphere->m10f4));
                if (ConfigManager()->GetValue(0x4ea96cb)) {
                    { cGameTimeManager* timeMgr = GameTimeManager(); timeMgr->IncPauseGate(0x4bf38a7); }
                    ShowHint(DAT_0157f0fc, 0);
                    ShowHint(DAT_0157f12c, DAT_0157f174);
                    return false;
                }
            }
        }
        break;
    }
    case 0x5cd5482: {
        cTribe* tribe = NounManager()->GetPlayerTribe();
        if (tribe) {
            cTribeTools* tools = tribe->FUN_00c90460();
            if (tools && !tools->mItemModels.empty()) {
                uint32_t n = tools->mItemModels.size();
                for (uint32_t i = 0; i < n; i++) {
                    cToolItem* item = tools->mItems[i];
                    if (!item->IsEffectPlayed()) {
                        item->SetEffectPlayed();
                        tools->mOwner.GetEffects()->PlayEffect(item, 0x95bff1ca, 2, 0.0f, 0);
                    }
                }
                return false;
            }
        }
        break;
    }
    case 0x60b5320: {
        cTribe* tribe = NounManager()->GetPlayerTribe();
        if (tribe) {
            cCreature* chief = tribe->GetChieftain();
            if (chief) {
                int* behavior = (int*)chief->mpBehavior->list.FUN_00bc97f0(0, 0x10000000, 5.0f, 0);
                if (behavior) {
                    behavior[3] = 2;
                    return false;
                }
            }
        }
        break;
    }
    case 0x60c7ac7: {
        cXformSource* src = (cXformSource*)msg->m10;
        if (src) {
            XformMsg xf;
            src->GetTransform(&xf);
            Vector3 pos;
            PlanetModel()->FUN_00b81630(&pos, &xf.pos);
            cToolPlacer* placer = FUN_00b3d2b0()->FUN_00ac7ab0(DAT_015812d4, FUN_00b3d2b0()->FUN_00ac79d0(), 1);
            placer->m130 = 1;
            placer->m124 = true;
            placer->mOwner.SetPosition(&pos);
            placer->mpHost->Attach(placer);
            return false;
        }
        break;
    }
    case 0x628304e:
        FUN_00cd5b80();
        return false;
    case 0x63bbc42: {
        Vector3 pos(*(Vector3*)((char*)msg->m28 + 4));
        FUN_00cd7320(pos);
        return false;
    }
    case 0x6677221:
        FUN_00cd4b70(0);
        return false;
    case 0x679c40d:
        if (GetCurrentGameMode() == kTribeModeID) {
            mpInputStrategy->FUN_00cd16a0(ConfigManager()->GetValue(0x679b868));
            GameInputManager()->SetInputStrategy(&mpInputStrategy->mInput, 0, 0);
            return false;
        }
        break;
    case 0x694797d: {
        cCivObject* p = CivModeStrategy()->m104;
        {
            cCivPtr hold(p);
        }
        if (p) {
            p->mFlags &= ~1u;
            return false;
        }
        break;
    }
    case 0x69479a8: {
        cCivObject* p = CivModeStrategy()->m104;
        {
            cCivPtr hold(p);
        }
        if (p) p->mFlags |= 1;
        break;
    }
    }
    return false;
}
