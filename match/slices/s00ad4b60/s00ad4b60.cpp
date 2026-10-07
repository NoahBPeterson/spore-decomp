// Slice s00ad4b60: cdecl callback @ 0x00AD4B60 (2568 bytes), stored as a function pointer at
// 0x00AD587F. It resolves the game object a scripted (cinematic) action targets, by target kind
// (switch on data->mTargetKind, 9 cases), then places the object at the action's position.
//   0 avatar (tribe mode: the player chieftain, else the first idle tribe member)
//   1 creature mode: first free member of the player's herd, else spawn one; tribe mode: first
//     free tribe member
//   2 a member of the herd of species mSpeciesID (the herd is created when missing)
//   3 the space-tool object of kind 4 whose property list 0x034D97FA names 0x7ECBE6F5
//   4 the player's UFO inventory, 5 FUN_00AD4A10's object, 6 a new 0xDC-byte camera object at
//     the player empire's home star
//   7 creature mode: the avatar's vehicle/creature; tribe mode: the chieftain of tribe mTribeID
//     (or a free member); scenario mode: the avatar's creature or its fallback object
//   8 creature mode: the last creature of NounManager's list at +0x5C
// Then (when a target was found): registers it under mTargetID with the cinematic manager,
// computes the destination, moves/orients the object on the planet surface, snaps/locomotes it
// and wakes creatures up. Always returns 1.
// Class, member and function names are Claude-coined from usage (ModAPI ids: kGameCreature
// 0x1654C01, kGameTribe 0x1654C02, kScenarioMode 0x1654C10).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the locals with dtors have no EH frame).
#include "types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00F473A0
void operator delete(void* p, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

struct Vector3
{
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    bool operator!=(const Vector3& v) const { return x != v.x || y != v.y || z != v.z; }
};
struct Quaternion { float x, y, z, w; };
extern Vector3 kInvalidPosition;                                   // 0x0167A4BC

struct RefCounted
{
    virtual int AddRef();
    virtual int Release();
};

template<class T> struct AutoRefCount
{
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p);                                  // out of line (0x00B5F950 for cHerd)
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    __forceinline T*& AsOutParam()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return mpObject;
    }
};

// ---------------------------------------------------------------------------------------------
// The game-object interface the target points at (AddRef/Release at slots 0xBC/0xC0).
#define V(n) virtual void v##n()
struct cGameObject
{
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28);
    virtual const Vector3& GetPosition();                                         // +0x2C
    V(30); V(34);
    virtual void SetPosition(const Vector3& pos);                                 // +0x38
    V(3c); V(40);
    virtual void SetPositionAndOrientation(const Vector3& pos, const Quaternion& q); // +0x44
    V(48); V(4c); V(50); V(54);
    virtual bool IsBusy();                                                         // +0x58
    virtual cGameObject* CastObject(uint32_t typeID);                              // +0x5C
    V(60); V(64); V(68); V(6c); V(70); V(74); V(78); V(7c); V(80); V(84); V(88); V(8c);
    V(90); V(94); V(98); V(9c); V(a0); V(a4); V(a8); V(ac); V(b0); V(b4);
    virtual void* Cast(uint32_t typeID);                                           // +0xB8
    virtual int AddRef();                                                          // +0xBC
    virtual int Release();                                                         // +0xC0
    uint32_t pad_04[(0x50 - 0x04) / 4];
    uint32_t mFlags;                                                               // +0x50
};

struct cGameObjectPtr
{
    cGameObject* mpObject;
    cGameObjectPtr& operator=(cGameObject* p);                      // 0x00C70110
};

// Target of the action (0x30 bytes): placement data plus the object.
struct cActionTarget
{
    Vector3 mPosition;
    uint32_t pad_0c[(0x2C - 0x0C) / 4];
    cGameObjectPtr mpObject;                                        // +0x2C
    cActionTarget();                                                // 0x00AD7940
    ~cActionTarget();                                               // 0x00AD7AD0
};

// Animation/behaviour controller hanging off a creature (+0xB54).
struct cBehaviorRule
{
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28); V(2c);
    V(30); V(34); V(38); V(3c);
    virtual void SetState(void* owner, int state, int arg);                        // +0x40
};
struct cBehaviorOwner
{
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28); V(2c);
    V(30); V(34); V(38); V(3c); V(40); V(44); V(48); V(4c); V(50); V(54); V(58); V(5c);
    V(60); V(64); V(68); V(6c);
    virtual cBehaviorRule* GetRule();                                              // +0x70
};

// Locomotion interface (cast id 0x0116DD1B).
struct cLocomotionRequest
{
    uint32_t* mpData;                                               // eastl vector storage
    uint32_t pad_04[(0x74 - 0x04) / 4];
    cLocomotionRequest();                                           // 0x00AC9850
    ~cLocomotionRequest()
    {
        if (mpData && mpData[-1])
            operator delete[](mpData);
    }
};
struct cLocomotion
{
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28); V(2c);
    V(30); V(34); V(38); V(3c); V(40); V(44); V(48); V(4c); V(50); V(54); V(58); V(5c);
    V(60); V(64); V(68); V(6c); V(70); V(74); V(78); V(7c); V(80); V(84); V(88); V(8c);
    V(90); V(94); V(98); V(9c); V(a0); V(a4); V(a8); V(ac); V(b0); V(b4); V(b8); V(bc);
    V(c0); V(c4); V(c8); V(cc); V(d0); V(d4); V(d8);
    virtual void Request(const cLocomotionRequest& request);                      // +0xDC
    V(e0); V(e4); V(e8);
    virtual void SnapToGround();                                                   // +0xEC
};

struct cCreatureBase0 { virtual void v00(); uint32_t pad_04[(0xC0 - 0x04) / 4]; };

struct cCreature : cCreatureBase0, cGameObject
{
    // cGameObject occupies +0xC0..+0x114 (its mFlags is creature +0x110)
    uint8_t pad_114[0x137 - 0x114];
    bool mbCanSwim;                                                 // +0x137
    uint8_t pad_138[0x2B0 - 0x138];
    int mMovementMode;                                              // +0x2B0
    uint8_t pad_2b4[0xB54 - 0x2B4];
    cBehaviorOwner* mpBehavior;                                     // +0xB54
    uint8_t pad_b58[0xB5E - 0xB58];
    bool mbIsDead;                                                  // +0xB5E

    bool IsIdle();                                                  // 0x00C0B770
    void SetAwake(int v);                                           // 0x00C0CFF0
    void WakeUp(int v);                                             // 0x00C14750
    cCreature* GetCreature();                                       // 0x00C0EE90
    cGameObject* GetFallbackObject();                               // 0x00C0EE60

    __forceinline void AlertBehavior()
    {
        mpBehavior->GetRule()->SetState((cBehaviorRule*)mpBehavior, 2, 1);
    }
};

struct CreatureVector { cCreature** mpBegin; cCreature** mpEnd; };

struct cHerd : RefCounted
{
    uint32_t pad_04[(0x40 - 0x04) / 4];
    CreatureVector mMembers;                                        // +0x40
    uint32_t pad_48[(0x88 - 0x48) / 4];
    uint32_t mSpeciesID;                                            // +0x88
    uint32_t field_8c;                                              // +0x8C
    uint32_t pad_90[(0xA4 - 0x90) / 4];
    uint32_t mSpeciesKey;                                           // +0xA4
    uint32_t pad_a8[(0xF0 - 0xA8) / 4];
    uint32_t field_f0;                                              // +0xF0
    const Vector3& GetPosition();                                   // 0x00C6ACC0
    void UpdateFromArchetype(int archetype, bool b);                // 0x00C6E200
};
struct HerdVector { cHerd** mpBegin; cHerd** mpEnd; };

struct cTribe
{
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28); V(2c);
    V(30); V(34); V(38); V(3c); V(40); V(44); V(48); V(4c); V(50); V(54); V(58); V(5c);
    V(60); V(64); V(68); V(6c); V(70); V(74); V(78); V(7c); V(80); V(84); V(88); V(8c);
    virtual const CreatureVector& GetMembers();                                    // +0x90
    cCreature* GetChieftain();                                      // 0x00C8FD30
};
#undef V

struct cObjectBase34 { virtual void v00(); uint32_t pad_04[(0x34 - 0x04) / 4]; };
struct ResourceKey
{
    uint32_t instanceID, typeID, groupID;
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};
struct cToolObject : cObjectBase34, cGameObject
{
    uint8_t pad_88[0x64C - 0x88];
    ResourceKey mModelKey;                                          // +0x64C
    int mKind;                                                      // +0x658
    __forceinline ResourceKey GetModelKey() const { return mModelKey; }
};
struct ToolVector { cToolObject** mpBegin; cToolObject** mpEnd; };
struct cSpaceInventory : cObjectBase34, cGameObject {};

// 0xDC-byte placeholder object used as a camera target.
struct cCameraObject : cGameObject
{
    uint32_t pad_54[(0xDC - 0x54) / 4];
    cCameraObject();                                                // 0x00AD2750
};

struct cStarRecord { const Vector3& GetPosition(); };           // 0x005C65E0
struct cEmpire { cStarRecord* GetHomeStar(); };                 // 0x00C30C60
cEmpire* GetPlayerEmpire();                                         // 0x01021300
struct cSPSimulatorSpaceGame { cSpaceInventory* GetPlayerInventory(); }; // 0x00A1AD60
cSPSimulatorSpaceGame* GetUFOSimulator();                           // 0x00FFBE50

struct cGameNounManager
{
    cCreature* GetAvatar();                                         // 0x00B1FDB0
    cTribe* GetPlayerTribe();                                       // 0x00BFC5F0
    cHerd* GetPlayerHerd();                                         // 0x00989360
    HerdVector* GetHerds();                                         // 0x00ACDA00
    ToolVector* GetToolObjects();                                   // 0x00AD49E0
    CreatureVector* GetCreatures();                                 // 0x00B1F9C0
    cHerd* CreateHerd(const Vector3& pos, void* pSpecies, int a, int b, int c, int d); // 0x00B23940
};
cGameNounManager* NounManager();                                    // 0x00B3D300

struct cPlanetModel
{
    Vector3 GetRandomSurfacePosition();                             // 0x00B81720
    Quaternion BuildSurfaceOrientation(const Vector3& pos);         // 0x00B7F190
    bool IsInWater(const Vector3& pos);                             // 0x00B7E3E0
    float GetRadiusAt(const Vector3& pos);                          // 0x00B7EF70
    float GetWaterHeight();                                         // 0x00B7E390
};
cPlanetModel* PlanetModel();                                        // 0x00B3D350

struct cCinematicManager
{
    uint32_t pad_00[0x148 / 4];
    uint32_t mCurrentScene;                                         // +0x148
    bool IsObjectReserved(cGameObject* pObject);                    // 0x00ADB360
    void RegisterTarget(uint32_t id, cActionTarget& target, uint32_t scene); // 0x00AE09B0
    void AddObject(void* pObject, uint32_t scene);                  // 0x00AE0A80
};
cCinematicManager* CinematicManager();                              // 0x00B3D4D0

struct cSpeciesManager { int GetSpeciesArchetype(uint32_t speciesID, int arg); }; // 0x004E0050
cSpeciesManager* SpeciesManager();                                  // 0x00401090
void* GetSpeciesProfile(int a, uint32_t speciesID, int b, int c, bool* pOut); // 0x00B9A750
cCreature* CreateCreature(const Vector3& pos, uint32_t speciesKey, bool a, cHerd* herd, int b, bool c); // 0x00C099E0

struct cPropertyList : RefCounted {};
struct IPropertyManager
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList*& pList); // +0x2C
};
IPropertyManager* PropertyManager();                                // 0x0067DE30
bool GetPropertyAsKey(cPropertyList* pList, uint32_t id, ResourceKey& dst); // 0x006A1250

uint32_t GetCurrentGameMode();                                      // 0x00B5B800
enum { kGameCreature = 0x1654C01, kGameTribe = 0x1654C02, kScenarioMode = 0x1654C10 };

// Small out-of-line helpers of this file.
bool GetNamedTarget(uint32_t id, cActionTarget* pTarget);           // 0x00AD2650
cCreature* GetTargetCreature(cGameObjectPtr* p);                    // 0x00AD2690 (Cast 0xD0036E08)
cTribe* GetTargetTribe(cGameObjectPtr* p);                          // 0x00AD26B0 (Cast 0x4F396A66)
cGameObject* GetScenarioObject(cGameObject* p);                     // 0x00AD26D0 (CastObject 0x01186577)
cSpaceInventory* GetActionInventory();                              // 0x00AD4A10

struct cActionData
{
    uint32_t pad_00[3];
    int mTargetKind;                                                // +0x0C
    uint32_t mTargetID;                                             // +0x10
    uint32_t mSpeciesID;                                            // +0x14
    uint32_t mTribeID;                                              // +0x18
    int mPlacement;                                                 // +0x1C
    int mPlacementArg1;                                             // +0x20
    int mPlacementArg2;                                             // +0x24
    Vector3 mOffset;                                                // +0x28
    bool mbAlert;                                                   // +0x34
};
struct cAction
{
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cActionData* Cast(uint32_t typeID);                     // +0x0C
};

void ComputeTargetPosition(Vector3& dst, cActionTarget& target, int placement, int arg1, int arg2,
                           const Vector3& offset);                  // 0x00AD2AE0

// @ 0x00AD4B60
int ResolveActionTarget(cAction* pAction)
{
    if (!pAction)
        return 1;
    cActionData* data = pAction->Cast(0x0447FF9B);
    if (!data)
        return 1;

    cActionTarget target;
    switch (data->mTargetKind) {
    case 0:
        target.mpObject = NounManager()->GetAvatar();
        if (GetCurrentGameMode() == kGameTribe) {
            cTribe* tribe = NounManager()->GetPlayerTribe();
            target.mpObject = tribe->GetChieftain();
            if (!target.mpObject.mpObject) {
                const CreatureVector& members = tribe->GetMembers();
                for (cCreature** it = members.mpBegin, **end = members.mpEnd; it != end; ++it) {
                    cCreature* member = *it;
                    if (!CinematicManager()->IsObjectReserved(member) && member->IsIdle() && !member->mbIsDead) {
                        target.mpObject = member;
                        break;
                    }
                }
            }
        }
        break;

    case 1:
        switch (GetCurrentGameMode()) {
        case kGameCreature: {
            cHerd* herd = NounManager()->GetPlayerHerd();
            cGameObject* found = 0;
            for (cCreature** it = herd->mMembers.mpBegin, **end = herd->mMembers.mpEnd; it != end; ++it) {
                cCreature* member = *it;
                if (!member->IsBusy() && !CinematicManager()->IsObjectReserved(member) && !member->mbIsDead) {
                    found = member;
                    break;
                }
            }
            if (!found) {
                cCreature* creature = CreateCreature(herd->GetPosition(), herd->mSpeciesKey, true, herd, 0, true);
                CinematicManager()->AddObject(creature, CinematicManager()->mCurrentScene);
                found = creature;
            }
            target.mpObject = found;
            if (data->mbAlert)
                GetTargetCreature(&target.mpObject)->AlertBehavior();
            break;
        }
        case kGameTribe: {
            cTribe* tribe = NounManager()->GetPlayerTribe();
            const CreatureVector& members = tribe->GetMembers();
            for (cCreature** it = members.mpBegin, **end = members.mpEnd; it != end; ++it) {
                cCreature* member = *it;
                if (!CinematicManager()->IsObjectReserved(member) && !member->mbIsDead) {
                    target.mpObject = member;
                    break;
                }
            }
            break;
        }
        }
        break;

    case 2:
        if (data->mSpeciesID) {
            AutoRefCount<cHerd> herd;
            HerdVector* herds = NounManager()->GetHerds();
            int count = (int)(herds->mpEnd - herds->mpBegin);
            for (int i = 0; i < count; ++i) {
                if (herds->mpBegin[i]->mSpeciesID == data->mSpeciesID)
                    herd = herds->mpBegin[i];
            }
            if (!herd) {
                bool created = false;
                void* pSpecies = GetSpeciesProfile(0, data->mSpeciesID, 0, 0, &created);
                if (!pSpecies)
                    break;
                herd = NounManager()->CreateHerd(PlanetModel()->GetRandomSurfacePosition(), pSpecies, 0, 0, 0, 0);
                if (!herd)
                    break;
                herd->mSpeciesID = data->mSpeciesID;
                herd->field_8c = 0;
                herd->field_f0 = 0;
                herd->UpdateFromArchetype(SpeciesManager()->GetSpeciesArchetype(herd->mSpeciesID, 0), true);
                CinematicManager()->AddObject(herd, CinematicManager()->mCurrentScene);
            }
            cCreature* creature = CreateCreature(PlanetModel()->GetRandomSurfacePosition(), herd->mSpeciesKey, true, herd, 0, true);
            if (data->mbAlert)
                creature->AlertBehavior();
            CinematicManager()->AddObject(creature, CinematicManager()->mCurrentScene);
            target.mpObject = creature;
        }
        break;

    case 7:
        switch (GetCurrentGameMode()) {
        case kGameCreature: {
            cCreature* creature = NounManager()->GetAvatar()->GetCreature();
            if (data->mbAlert)
                creature->AlertBehavior();
            target.mpObject = creature;
            break;
        }
        case kGameTribe: {
            cActionTarget tribeTarget;
            if (!GetNamedTarget(data->mTribeID, &tribeTarget))
                return 1;
            GetNamedTarget(data->mTribeID, &tribeTarget);
            cTribe* tribe = GetTargetTribe(&tribeTarget.mpObject);
            target.mpObject = tribe->GetChieftain();
            if (!target.mpObject.mpObject) {
                const CreatureVector& members = tribe->GetMembers();
                for (cCreature** it = members.mpBegin, **end = members.mpEnd; it != end; ++it) {
                    cCreature* member = *it;
                    if (!CinematicManager()->IsObjectReserved(member) && member->IsIdle() && !member->mbIsDead) {
                        target.mpObject = member;
                        break;
                    }
                }
            }
            break;
        }
        case kScenarioMode: {
            cCreature* avatar = NounManager()->GetAvatar();
            cCreature* creature = avatar->GetCreature();
            if (creature) {
                if (data->mbAlert)
                    creature->AlertBehavior();
                target.mpObject = creature;
            } else
                target.mpObject = GetScenarioObject(avatar->GetFallbackObject());
            break;
        }
        }
        break;

    case 8:
        if (GetCurrentGameMode() == kGameCreature) {
            CreatureVector* creatures = NounManager()->GetCreatures();
            if (creatures->mpBegin != creatures->mpEnd)
                target.mpObject = creatures->mpEnd[-1];
        }
        break;

    case 4:
        target.mpObject = GetUFOSimulator()->GetPlayerInventory();
        break;

    case 5:
        target.mpObject = GetActionInventory();
        break;

    case 6: {
        target.mpObject = new("Simulator", 0, 0, 0, 0) cCameraObject();
        Vector3 position = GetPlayerEmpire()->GetHomeStar()->GetPosition();
        target.mpObject.mpObject->SetPosition(position);
        break;
    }

    case 3: {
        ToolVector* tools = NounManager()->GetToolObjects();
        int count = (int)(tools->mpEnd - tools->mpBegin);
        for (int i = 0; i < count; ++i) {
            if (tools->mpBegin[i]->mKind == 4) {
                AutoRefCount<cPropertyList> pPropList;
                ResourceKey key;
                PropertyManager()->GetPropertyList(tools->mpBegin[i]->GetModelKey().instanceID, 0x034D97FA, pPropList.AsOutParam());
                GetPropertyAsKey(pPropList, 0x034F1A4F, key);
                if (key.instanceID == 0x7ECBE6F5)
                    target.mpObject = tools->mpBegin[i];
            }
        }
        break;
    }
    }

    if (target.mpObject.mpObject) {
        CinematicManager()->RegisterTarget(data->mTargetID, target, CinematicManager()->mCurrentScene);
        Vector3 position;
        ComputeTargetPosition(position, target, data->mPlacement, data->mPlacementArg1, data->mPlacementArg2, data->mOffset);
        if (position != kInvalidPosition) {
            cGameObject* object = target.mpObject.mpObject;
            object->SetPositionAndOrientation(position, PlanetModel()->BuildSurfaceOrientation(position));
            if (target.mpObject.mpObject) {
                cLocomotion* locomotion = (cLocomotion*)target.mpObject.mpObject->Cast(0x0116DD1B);
                if (locomotion)
                    locomotion->SnapToGround();
            }
            if (PlanetModel()->IsInWater(position))
                target.mpObject.mpObject->mFlags |= 0x1000;
            if (target.mpObject.mpObject) {
                cCreature* creature = (cCreature*)target.mpObject.mpObject->Cast(0xCE9F6639);
                if (creature && (creature->mFlags & 0x1000)) {
                    float radius = PlanetModel()->GetRadiusAt(creature->GetPosition());
                    if (PlanetModel()->GetWaterHeight() > radius) {
                        creature->mbCanSwim = false;
                        creature->mMovementMode = 3;
                    }
                }
            }
        }
        if (target.mpObject.mpObject) {
            cLocomotion* locomotion = (cLocomotion*)target.mpObject.mpObject->Cast(0x0116DD1B);
            if (locomotion)
                locomotion->Request(cLocomotionRequest());
            if (target.mpObject.mpObject) {
                cCreature* creature = (cCreature*)target.mpObject.mpObject->Cast(0xD0036E08);
                if (creature) {
                    creature->SetAwake(0);
                    if (!creature->mbIsDead)
                        creature->WakeUp(1);
                }
            }
        }
    }
    return 1;
}
