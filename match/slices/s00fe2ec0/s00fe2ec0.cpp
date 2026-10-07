// slice s00fe2ec0 -- SP::cAppModeSpace::HandleMessage (IHandler subobject entry, this = full+4).
//
// Big message switch of the space-stage app mode: combatant death feedback,
// species change, empire contact/war, scanning, ban-mode toggles, planet
// destination warps (with a teleport visual effect), state machine reload and
// mission-list cleanup.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE  (no /EHsc: the AutoRefCount local has no EH frame;
// /arch:SSE gives the fucomip float compares).

#include "types.h"
typedef uint8_t uint8; typedef uint16_t uint16; typedef uint32_t uint32; typedef uint64_t uint64;

struct Vector3 { float x, y, z; Vector3() {} };
struct Matrix3 { float m[9]; Matrix3() {} };

// SP Transform (XformMsg ctor is folded with Transform::Transform at 0x434040).
struct Transform {
    uint16 mnFlags;
    uint16 mnTransformCount;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;
    Transform();
    void SetOffset(const Vector3& v) { mnFlags |= 4; mnTransformCount++; mOffset = v; }
    void SetRotation(const Matrix3& m) { mRotation = m; mnFlags |= 2; mnTransformCount++; }
};

namespace SP {
Vector3 normalized_safe(const Vector3& v);
Vector3 OrthogonalVector(const Vector3& v);
Matrix3 Matrix3FromFacingAndUp(const Vector3& facing, const Vector3& up);
}

struct ResKey {
    uint32 a, b, c;
    ResKey() : a(0), b(0), c(0) {}
};

// Message payload: parameters live at +8, +0x10, +0x18.
struct SpaceMsg {
    uint32 pad0[2];
    uint32 p8;
    uint32 pad1;
    uint32 p10;
    uint32 pad2;
    uint32 p18;
};

struct KeyTriple {
    uint32 a, b, c;
    KeyTriple() {}
    KeyTriple(uint32 x, uint32 y, uint32 z) : a(x), b(y), c(z) {}
};

// --- game objects -------------------------------------------------------
struct cGameDataVt {
    virtual void v00();
    virtual void v04();
    virtual cGameDataVt* GetSelf();        // +8
    virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual uint32 GetID();                 // +0x2c
};

struct cCombatantLike : cGameDataVt {};

struct cCombatant : cCombatantLike {
    int GetDamageState();                   // 0x8e7f80
};

struct Ivfn58 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool IsDestroyed();             // +0x58
};

struct cCommunity {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual uint32 GetOwnerID();            // +0x4c
    char pad[0x11c];
    Ivfn58 m120;                            // +0x120
    void Reaction();                        // 0xbdbf10
};

struct cBuildingLike {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80();
    virtual cCommunity* GetCommunity();     // +0x84
};

struct cCreatureLike {
    cCommunity* GetCommunity();             // 0xbce5c0
};

struct cEnemyLike {
    char pad[0x714];
    int mState;                             // +0x714
};

struct cInvSub34 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vector3* GetDestination();      // +0x2c
};

struct cInvBase0 {
    virtual void v00();
    char pad04[0x30];
    cInvSub34 m34;                          // +0x34
    char pad38[0x508 - 0x38];
};

struct cPlayerInventory : cInvBase0, cCombatantLike {};

struct cSpaceSim {
    cPlayerInventory* GetPlayerInventory(); // 0xa1ad60
    void SetPlanetDestination(Vector3* pos, int a, int b, int c, int d); // 0xffc350
    void OnWarp();                          // 0xffc030
};

struct cEmpire {
    char pad[0x84];
    uint32 mPoliticalID;                    // +0x84
    bool IsDestroyed();                     // 0xc30910
    void Fn930();                           // 0xc30930
    void Fn9b0(int);                        // 0xc309b0
    bool HasContact();                      // 0xc31c60
    bool IsAlly();                          // 0xc308b0
    struct cPlanetRecord* GetHomePlanet();  // 0xc31730
    void SetSpecies(void* profile);         // 0xc33690
};

struct cPlanetRecord {
    void* GetCommContext();                 // 0xce6950
};

struct cPlanet {
    char pad[0x13c];
    cPlanetRecord* mRecord;                 // +0x13c
    cEmpire* GetOwner();                    // 0xc71e30
    void Fn430(int, int);                   // 0xc71430
};

struct cTerrainSphere {
    void PlayMusic(uint32 id);              // 0xc77bf0
    bool HasMusic(uint32 id);               // 0xc772c0
};

struct cNounManager {
    cTerrainSphere* GetCurrentTerrainSphere(); // 0xf67d90
    void* GetFn2c0();                       // 0xace2c0
};

struct cRelationshipManager {
    bool IsAtWar(cEmpire* e, int b);        // 0xd01ff0
    float GetEvent(uint32 a, uint32 b, uint32 ev); // 0xd01b80
    float RecordEvent(uint32 a, uint32 b, uint32 ev, float f); // 0xd06240
};

struct cEventLog {
    void PostFeedbackEvent(uint32 a, uint32 b, int c, int d, int e, int f); // 0xdd8640
};

struct cTribeLike {
    void Fn5430(int, int);                  // 0xfe5430
};

struct cGameNounManager {
    char pad[0x50];
    uint32 mbFlag0 : 1;                     // +0x50 bitfield
    uint32 mbSpaceMission : 1;
    uint32 mbFlag2 : 1;
    uint32 mbFlag3 : 1;
    uint32 mbTutorialMission : 1;
    cTribeLike* GetPlayerTribe();           // 0xbfc5f0
    void Fn3480();                          // 0x1003480
};

struct cSpeciesManager {
    void* GetProfile(const KeyTriple& key); // 0x4df550
};

struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void PostMSG(uint32 id, int a, int b, int c); // +0x18
};

struct IGameInputManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void Reset();                   // +0x1c
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual int GetMode();                  // +0x34
    virtual void SetMode(int m);            // +0x38
};

struct IPosSource {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void GetPosition(Vector3& out, int a, cCombatantLike* who); // +0x40
};

struct IVisualEffect {
    virtual void v00();
    virtual int Release();                  // +4
    virtual void Start(int);                // +8
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void SetTransform(const Transform& t); // +0x18
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T** AsPPTypeParam();                    // 0xa16f40
};

struct IEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool CreateVisualEffect(uint32 id, int flags, IVisualEffect** out); // +0x2c
};

struct cCameraController {
    void Fn270(int);                        // 0x1017270
};

struct ICameraManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void* GetActiveCameraController(); // +0x38
};

struct IApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual ICameraManager* GetCameraManager(); // +0x50
};

struct IConfigManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void* GetPropertyList(uint32 id); // +0x30
};

struct cA98 { bool IsBusy(); };            // 0xa98020
struct cDD4 { void Fn(); };                 // 0xadda70
struct cGameTimeManager { char pad[0x48]; uint8 mFlags; };
struct cUniverseContext;

struct cWarSystem { void Update(); };       // 0x100d9f0
extern cWarSystem* g_WarSystem;             // 0x16dc798

namespace SP {
cSpaceSim* GetUFOSimulator();               // 0xffbe50
void* GetCurrentGameMode();                 // 0xb5b800
IGameInputManager* GameInputManager();      // 0xb3d250
IPosSource* PosSource();                    // 0xb3d240
cRelationshipManager* RelationshipManager();// 0xb3d2c0
cNounManager* NounManager();                // 0xb3d300
cEventLog* EventLog();                      // 0xb3d3e0
cGameTimeManager* GameTimeManager();        // 0xb3d380
cDD4* Fn4d0();                              // 0xb3d4d0
IMessageServer* MessageServer();            // 0x67dcc0
IEffectsManager* EffectsManager();          // 0x67ddd0
IApp* App();                                // 0x67dd10
IConfigManager* ConfigManager();            // 0x67dd30
cSpeciesManager* SpeciesManager();          // 0x401090
cA98* Fn5df0();                             // 0x1015df0
cPlanet* GetActivePlanet();                 // 0x1021260
cPlanetRecord* GetActivePlanetRecord();     // 0x10212a0
cEmpire* GetPlayerEmpire();                 // 0x1021300
uint32 GetPlayerEmpireID();                 // 0x1021090
cPlanetRecord* GetPlayerHomePlanet();       // 0x1021370
cUniverseContext* GetUniverseContext();     // 0x1021080
cCreatureLike* AsCreature(cCombatant* c);   // 0xbcd430
cBuildingLike* AsBuilding(cCombatant* c);   // 0xc5b430
cEnemyLike* AsEnemy(cCombatant* c);         // 0xae3370
bool IsBlockadeOwner(cPlanet* p);           // 0x102c600
bool CheckEnemyDeath(cEnemyLike* e, cPlayerInventory* inv, int b); // 0x102aa50
cCommunity* FindCommunity(void* a, uint32 id); // 0xac9dd0
void DoCommunityReaction(cCommunity* c, float f, uint32 id); // 0xff5270
void* GetCreatureFromStimulus(uint32 s);    // 0xc032a0
void ScanBuilding(void* c);                 // 0x1058680
struct cScannable { KeyTriple GetKey(); }; // 0xc3e1e0
cScannable* FindScannable(uint32 s);        // 0xfd9e60
void ScanObject(const KeyTriple& key);               // 0x10534c0
void EndBanMode(int);                       // 0xdd1840
void ToggleBanningContent(int);             // 0xdd17f0
void EndPlanetMode(int);                    // 0xe09a50
void StartPlanetMode(int);                  // 0xe099d0
void CommEvent(uint32 id, cEmpire* e, const ResKey& a, const ResKey& b, void* ctx, int c, const ResKey& d, const ResKey& f); // 0xe39ab0
cCameraController* AsPlanetCamera(void* c); // 0xc37590
}
uint32 SPIDFromName(const char* name);      // 0x571cf0
void SetGlobalProperty(uint32 id, float f); // 0x5ca880

namespace EA {
struct Stopwatch {
    uint64 mnStartTime;
    uint64 mnTotalElapsedTime;
    uint32 mnUnits;
    float mfCoefficient;
    void Restart();                         // 0x571e80
    uint64 GetElapsedTime() const;          // 0x93a5e0
    void Reset() { mnStartTime = 0; mnTotalElapsedTime = 0; }
};
}

// eastl::list<KeyTriple> sentinel + iterator (user copy ctor: by-value copies in place).
struct ListNode { ListNode* mpNext; ListNode* mpPrev; };
struct ListIter {
    ListNode* mpNode;
    ListIter(ListNode* p) : mpNode(p) {}
    ListIter(const ListIter& x) : mpNode(x.mpNode) {}
};
struct KeyList {
    ListNode mNode;
    ListIter begin() { return ListIter(mNode.mpNext); }
    ListIter end() { return ListIter(&mNode); }
    bool empty() const { return mNode.mpNext == &mNode; }
    ListIter erase(ListIter it);            // 0xfdc4b0
};
ListIter FindKey(ListIter first, ListIter last, const KeyTriple& value); // 0xfdb230

// --- cAppModeSpace ------------------------------------------------------
struct cIModeStrategy { virtual void ms00(); };
struct IHandler { virtual bool HandleMessage(uint32 messageID, void* msg); };

namespace SP {
class cAppModeSpace : public cIModeStrategy, public IHandler {
public:
    virtual bool HandleMessage(uint32 messageID, void* msg);
    void OnNewGame();                       // 0xfd9d30
    void OnLoadGame();                      // 0xfd9d90
    void Fn9de0();                          // 0xfd9de0
    void Fnabf0();                          // 0xfdabf0
    void Fnade0();                          // 0xfdade0
    void SetDefaultPickPriority();          // 0xfddba0
    void Fndfa0();                          // 0xfddfa0
    void HandleMessage2();                  // 0xfdfbc0
    void LoadStateMachine(void* props);     // 0xfe1a20

    char pad08[0x110 - 0x8];
    EA::Stopwatch mWarpTimer;               // +0x110
    char pad128[0x15c - 0x128];
    cGameNounManager* mpGameNounManager;    // +0x15c
    char pad160[0x16a - 0x160];
    bool mbMissionsDone;                    // +0x16a
    char pad16b[0x170 - 0x16b];
    KeyList mMissions;                      // +0x170
    char pad178[0x18c - 0x178];
    bool mbPendingPlanet;                   // +0x18c
};

static inline cCombatantLike* InventoryBase(cPlayerInventory* inv) { return inv; }

// @ 0x00fe2ec0
bool cAppModeSpace::HandleMessage(uint32 messageID, void* pMsg)
{
    SpaceMsg* msg = (SpaceMsg*)pMsg;
    switch (messageID) {
    case 0x1a0219e:
        switch (msg->p8) {
        case 1: OnNewGame(); break;
        case 6: OnLoadGame(); break;
        }
        return false;

    case 0x1622184: {
        cCombatant* combatant = (cCombatant*)msg->p8;
        cCombatantLike* attacker = (cCombatantLike*)msg->p10;
        if (combatant->GetDamageState() != 2)
            return true;
        cCreatureLike* creature = AsCreature(combatant);
        cBuildingLike* building = AsBuilding(combatant);
        if (attacker == GetUFOSimulator()->GetPlayerInventory() && (creature || building)) {
            cEmpire* owner = GetActivePlanet()->GetOwner();
            if (owner) {
                if (owner == GetPlayerEmpire())
                    EventLog()->PostFeedbackEvent(0xc88d9222, 0x131a9f54, 0, 0, 1, 0);
                else if (RelationshipManager()->IsAtWar(owner, 0))
                    EventLog()->PostFeedbackEvent(0x8c5cb303, 0x131a9f54, 0, 0, 1, 0);
            }
            cCommunity* community;
            if (building)
                community = building->GetCommunity();
            else if (creature)
                community = creature->GetCommunity();
            else
                return true;
            if (community && !community->m120.IsDestroyed()) {
                community->Reaction();
                float f = RelationshipManager()->RecordEvent(community->GetOwnerID(), GetPlayerEmpireID(), 0x526e53c, 1.0f);
                DoCommunityReaction(community, f, combatant->GetSelf()->GetID());
            }
            return true;
        }
        cEnemyLike* enemy = AsEnemy(combatant);
        if (attacker == GetUFOSimulator()->GetPlayerInventory() && enemy) {
            if (CheckEnemyDeath(enemy, GetUFOSimulator()->GetPlayerInventory(), IsBlockadeOwner(GetActivePlanet())))
                SetGlobalProperty(SPIDFromName("spg_war_enemy_death"), 1.0f);
        }
        cPlayerInventory* inv = GetUFOSimulator()->GetPlayerInventory();
        if (attacker == inv && enemy && enemy->mState == 6) {
            cCommunity* community = FindCommunity(NounManager()->GetFn2c0(), inv->GetSelf()->GetID());
            if (community && !community->m120.IsDestroyed())
                community->Reaction();
        }
        return true;
    }

    case 0x3795725: {
        cEmpire* empire = GetPlayerEmpire();
        void* mode = GetCurrentGameMode();
        if (!empire || mode == (void*)0x1654c10)
            return false;
        empire->SetSpecies(SpeciesManager()->GetProfile(KeyTriple(msg->p10, msg->p8, msg->p18)));
        MessageServer()->PostMSG(0x490d429, 0, 0, 0);
        return false;
    }

    case 0x3ac86b5: {
        cEmpire* empire = (cEmpire*)msg->p10;
        cEmpire* player = GetPlayerEmpire();
        uint8* extra = (uint8*)msg->p18;
        if (extra && extra[0x30])
            return false;
        if (empire && !empire->IsDestroyed()) {
            empire->Fn930();
            empire->Fn9b0(0);
            if (empire != player) {
                NounManager()->GetCurrentTerrainSphere()->PlayMusic(0x5f1f0cb);
                cRelationshipManager* rm = RelationshipManager();
                uint32 a = empire->mPoliticalID;
                if (rm->GetEvent(a, player->mPoliticalID, 0x5b6cf09) == 0.0f && rm->GetEvent(a, player->mPoliticalID, 0x5f62736) == 0.0f)
                    rm->RecordEvent(a, player->mPoliticalID, 0x5b6cf09, 1.0f);
                cGameNounManager* gnm = mpGameNounManager;
                if (gnm) {
                    cTribeLike* tribe = gnm->GetPlayerTribe();
                    if (tribe) {
                        tribe->Fn5430(4, 1);
                        cPlanetRecord* planet = GetActivePlanetRecord();
                        if (!planet)
                            planet = empire->GetHomePlanet();
                        if (empire->HasContact()) {
                            uint32 id = 0xaff54daa;
                            if (empire->IsAlly())
                                id = 0xf31ed5f3;
                            CommEvent(id, empire, ResKey(), ResKey(), planet->GetCommContext(), 0, ResKey(), ResKey());
                        }
                    }
                }
            }
        }
        if (empire == player) {
            cPlanet* planet = GetActivePlanet();
            cPlanetRecord* rec;
            if (planet && (rec = planet->mRecord) != GetPlayerHomePlanet())
                planet->Fn430(4, 1);
            g_WarSystem->Update();
        }
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        if (sphere && sphere->HasMusic(0x4ac8010))
            sphere->PlayMusic((empire != player) + 0x61f1455);
        return false;
    }

    case 0x3ec1631:
        if (msg) {
            uint32 stim = msg->p8;
            void* creature = GetCreatureFromStimulus(stim);
            if (creature) {
                ScanBuilding(creature);
                return true;
            }
            cScannable* s = FindScannable(stim);
            if (s) {
                ScanObject(s->GetKey());
            }
        }
        return true;

    case 0x452e0ca:
        if (GetCurrentGameMode() != (void*)0x1654c05)
            return false;
        if (Fn5df0()->IsBusy())
            return false;
        SetDefaultPickPriority();
        GameInputManager()->SetMode(0);
        EndBanMode(1);
        return false;

    case 0x44eaa93: {
        if (GetCurrentGameMode() != (void*)0x1654c05)
            return false;
        if (Fn5df0()->IsBusy())
            return false;
        IGameInputManager* gim = GameInputManager();
        switch (gim->GetMode()) {
        case 0:
            mpGameNounManager->Fn3480();
            Fndfa0();
            gim->SetMode(1);
            ToggleBanningContent(1);
            break;
        case 1:
            SetDefaultPickPriority();
            gim->SetMode(0);
            EndBanMode(1);
            break;
        }
        return false;
    }

    case 0x5e37a2c:
        Fn9de0();
        return false;

    case 0x5e37a3b:
        Fnabf0();
        return false;

    case 0x5e37a44:
        if (GetActivePlanetRecord())
            mbPendingPlanet = true;
        else
            Fnade0();
        return false;

    case 0x5e37a53:
        HandleMessage2();
        return false;

    case 0x6148657: {
        if (GameTimeManager()->mFlags & 1)
            return false;
        if (GetUniverseContext())
            return false;
        mWarpTimer.Restart();
        Vector3 pos;
        PosSource()->GetPosition(pos, 1, GetUFOSimulator()->GetPlayerInventory());
        GetUFOSimulator()->SetPlanetDestination(&pos, 0, 1, 0, 0);
        GetUFOSimulator()->OnWarp();
        AutoRefCount<IVisualEffect> effect;
        if (EffectsManager()->CreateVisualEffect(0x384e54a4, 0, effect.AsPPTypeParam())) {
            Transform xf;
            xf.SetOffset(pos);
            const Vector3& up = normalized_safe(pos);
            const Vector3& facing = normalized_safe(OrthogonalVector(up));
            xf.SetRotation(Matrix3FromFacingAndUp(facing, up));
            effect->SetTransform(xf);
            effect->Start(0);
        }
        cCameraController* cam = AsPlanetCamera(App()->GetCameraManager()->GetActiveCameraController());
        if (cam)
            cam->Fn270(0);
        return false;
    }

    case 0x6148658:
        if (GetUniverseContext())
            return false;
        if (!(GameTimeManager()->mFlags & 1)) {
            if (mWarpTimer.GetElapsedTime() > 250)
                GetUFOSimulator()->SetPlanetDestination(GetUFOSimulator()->GetPlayerInventory()->m34.GetDestination(), 1, 0, 1, 0);
        }
        mWarpTimer.Reset();
        return false;

    case 0x620222b: {
        if (GetCurrentGameMode() != (void*)0x1654c05)
            return false;
        if (Fn5df0()->IsBusy())
            return false;
        IGameInputManager* gim = GameInputManager();
        switch (gim->GetMode()) {
        case 0:
            mpGameNounManager->Fn3480();
            Fndfa0();
            gim->SetMode(2);
            StartPlanetMode(1);
            break;
        case 2:
            SetDefaultPickPriority();
            gim->SetMode(0);
            EndPlanetMode(1);
            break;
        }
        return false;
    }

    case 0x620271c:
        if (GetCurrentGameMode() != (void*)0x1654c05)
            return false;
        if (Fn5df0()->IsBusy())
            return false;
        SetDefaultPickPriority();
        GameInputManager()->SetMode(0);
        EndPlanetMode(1);
        return false;

    case 0x667af52:
        Fn4d0()->Fn();
        return false;

    case 0x679c40d:
        if (GetCurrentGameMode() != (void*)0x1654c05)
            return false;
        LoadStateMachine(ConfigManager()->GetPropertyList(0x679b880));
        return false;

    case 0x695e243:
        if (mpGameNounManager->mbSpaceMission || mpGameNounManager->mbTutorialMission) {
            KeyTriple key;
            key.a = msg->p8;
            key.b = msg->p18;
            key.c = msg->p10;
            ListIter it = FindKey(mMissions.begin(), mMissions.end(), key);
            if (it.mpNode != &mMissions.mNode)
                mMissions.erase(it);
            if (mMissions.empty())
                mbMissionsDone = true;
        }
        return true;

    case 0x71d4dfc8:
    case 0x71d4dfc9:
        GameInputManager()->Reset();
        return false;
    }
    return false;
}
} // namespace SP
