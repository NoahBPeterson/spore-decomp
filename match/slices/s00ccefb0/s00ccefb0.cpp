// Slice s00ccefb0 -- tribe-stage cursor picker: maps the object under the mouse (and the picked terrain
// position) to a tribe cursor id (0 = default ... 0x30 = UFO).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (tribe-mode module; no /EHsc: the selection
// fixed_vector local gets no EH frame).
#include "types.h"

#define VPAD(n) virtual void vpad##n()

// ------------------------------------------------------------------ math
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    static const Vector3 ZERO;                                          // 0169b1c8
};
bool operator!=(const Vector3& a, const Vector3& b);                    // 0041dd30

// ------------------------------------------------------------------ simulator objects
// Every noun is a cGameData; the type-specific slots past 0x4c are declared on the stubs below.
struct cGameData {
    VPAD(0); VPAD(1); VPAD(2);
    virtual void* Cast(uint32_t typeID);                                // +0x0c
    VPAD(4); VPAD(5); VPAD(6); VPAD(7);
    virtual uint32_t GetNounID();                                       // +0x20
    VPAD(9); VPAD(10); VPAD(11);
    virtual uint32_t GetModelKey();                                     // +0x30 (ornament model id)
    VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18);
    virtual uint32_t GetPoliticalID();                                  // +0x4c
};

// Secondary-base interfaces embedded in the nouns.
struct cSpatialPart {           // +0x34 / +0xc0 / +0x120 sub-objects
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual const Vector3& GetPosition();                               // +0x2c
    VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    virtual bool IsMoving();                                            // +0x50
    VPAD(21);
    virtual bool IsUnderConstruction();                                 // +0x58 (flag/selectable test)
};

struct cCombatant {             // +0x120 of tools/huts
    float GetHealthPercentage();                                        // 00bfc490
    int GetDamageState();                                               // 008e7f80
};

struct cTimerLike {             // +0x5a8 of a citizen
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20);
    VPAD(21);
    virtual float GetValue();                                           // +0x58
};

struct cHerdInfo { uint32_t pad[0x1d8 / 4]; uint32_t mBehaviorID; };   // +0x1d8

struct cTribe;

struct cCreatureCitizen : cGameData {
    uint32_t pad04[(0xc0 - 4) / 4];
    cSpatialPart mLocomotive;                                           // +0xc0
    uint32_t pad0c4[(0x5a8 - 0xc4) / 4];
    cTimerLike mTimer;                                                  // +0x5a8
    uint32_t pad5ac[(0x5e0 - 0x5ac) / 4];
    float mThreshold;                                                   // +0x5e0
    uint32_t pad5e4[(0xb4c - 0x5e4) / 4];
    cHerdInfo* mpHerd;                                                  // +0xb4c
    uint32_t padb50[(0xb5c - 0xb50) / 4];
    uint8_t mb5c, mb5d;
    uint8_t mbBusy;                                                     // +0xb5e
    cTribe* GetTribe();                                                 // 00c22f50
    int GetActivity();                                                  // 00c22dc0
};

struct cCreatureAnimal : cGameData {
    uint32_t pad04[(0xc0 - 4) / 4];
    cSpatialPart mLocomotive;                                           // +0xc0
    uint32_t pad0c4[(0xb5c - 0xc4) / 4];
    uint8_t mb5c, mb5d;
    uint8_t mbBusy;                                                     // +0xb5e
    bool IsFlagged();                                                   // 00c0c0e0
};

struct cTribe : cGameData {
    uint32_t pad04[(0x120 - 4) / 4];
    cSpatialPart mSpatial;                                              // +0x120
    uint32_t pad124[(0x20c - 0x124) / 4];
    uint32_t mFood[1];                                                  // +0x20c
    uint32_t pad210[(0x554 - 0x210) / 4];
    uint8_t mb554, mb555;
    uint8_t mbDefeated;                                                 // +0x556
    bool HasToolA();                                                    // 00c8e850
    bool HasToolB();                                                    // 00c8e870
    bool IsRaided();                                                    // 00c8eb90
    bool IsAllied();                                                    // 00b1fbf0
    cCreatureCitizen* GetLeader();                                      // 00c00650
};

struct cFoodStore { float GetAmount(); };                               // 00cee380

struct cTribeTool : cGameData {
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatialPart mSpatial;                                              // +0x34
    uint32_t pad038[(0x120 - 0x38) / 4];
    cCombatant mCombatant;                                              // +0x120
    VPAD(20); VPAD(21);
    virtual int GetToolType();                                          // +0x58
    cTribe* GetTribe();                                                 // 00c9d9e0
};

struct cTribeHut : cGameData {
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatialPart mSpatial;                                              // +0x34
    uint32_t pad038[(0x120 - 0x38) / 4];
    cCombatant mCombatant;                                              // +0x120
    VPAD(20); VPAD(21);
    virtual cTribe* GetTribe();                                         // +0x58
};

struct cTribeFoodMat : cGameData {
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatialPart mSpatial;                                              // +0x34
    uint32_t pad038[(0x10c - 0x38) / 4];
    cTribe* mpTribe;                                                    // +0x10c
};

struct cFruit : cGameData {
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatialPart mSpatial;                                              // +0x34
};

struct cGameBundle : cGameData {
    uint32_t pad04[(0x128 - 4) / 4];
    uint32_t mOwnerID;                                                  // +0x128
};

struct cOrnament : cGameData {
    uint32_t pad04[(0x228 - 4) / 4];
    uint32_t mOrnamentType;                                             // +0x228
};

struct cOrnamentModel { uint32_t pad[0x2c0 / 4]; float mHeight; };    // +0x2c0

void* object_cast(cGameData* p, uint32_t nounID);                       // 00ac80d0
cGameData* ToGameData(cGameData* p);                                    // 00c9f060
struct cPickInfo { uint32_t pad[4]; Vector3 mPosition; };               // +0x10
cPickInfo* GetPickInfo(cGameData* p);                                   // 00c22df0
cTribe* GetTribeByPoliticalID(uint32_t id);                            // 00ac7880
cOrnamentModel* GetOrnamentModel(uint32_t key);                         // 00ac8730
bool CanUseToolA(cGameData* p);                                         // 00dd18b0
bool CanUseToolB(cGameData* p);                                         // 00e09ad0
bool IsCitizenIdle(cCreatureCitizen* p);                                // 00da81f0

enum {
    kGameData = 0x17f243b, kTribeTool = 0x18c8f0c, kGameDataUFO = 0x18ebadc, kCreatureAnimal = 0x18eb45e,
    kCreatureCitizen = 0x18eb4b7, kGameBundle = 0x18c431c, kOrnament = 0x18c88e4, kFruit = 0x2c9cc91,
    kTribeHut = 0x1e4daae, kEgg = 0x2a034cd, kTribeFoodMat = 0x629bafe
};

// ------------------------------------------------------------------ selection vector
struct SpatialRef { void* mpObject; };
cCreatureCitizen* ToCitizen(const SpatialRef& r);                       // 00c9f000

struct SpatialVector {          // eastl::vector<AutoRefCount<cSpatialObject>, sp_vector_allocator>
    SpatialRef* mpBegin;
    SpatialRef* mpEnd;
    SpatialRef* mpCapacity;
    uint32_t mAllocator[2];
    ~SpatialVector();                                                   // 00ad92d0
};

// sp_vector_allocator keeps a "heap block" word just before the storage (0 = not heap).
template <int N>
struct SpatialFixedVector : SpatialVector {
    uint32_t mHeapFlag;
    SpatialRef mBuffer[N];
    SpatialFixedVector() {
        mHeapFlag = 0;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + N;
    }
};

// ------------------------------------------------------------------ managers
struct cTribeModeController { bool IsPlacing(); };                      // 00d09660

struct cTribeInputStrategy {
    uint32_t pad[0x5c / 4];
    cTribeModeController* mpController;                                 // +0x5c
    uint32_t pad60[(0xa0 - 0x60) / 4];
    int mToolMode;                                                      // +0xa0
    uint32_t pada4;
    uint64_t mPendingAction;                                            // +0xa8
};

struct cTribeModeStrategy {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    VPAD(20); VPAD(21); VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26); VPAD(27);
    virtual cTribeInputStrategy* GetInputStrategy();                    // +0x70
    uint32_t pad[(0x390 - 4) / 4];
    int mDifficulty;                                                    // +0x390
    static cTribeModeStrategy* Instance();                              // 00cd40b0
};

struct cGameTerrainCursor {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    VPAD(20); VPAD(21); VPAD(22);
    virtual void GetSelection(SpatialVector& out);                      // +0x5c
    VPAD(24); VPAD(25); VPAD(26); VPAD(27);
    virtual int GetSelectionCount();                                    // +0x70
    VPAD(29); VPAD(30); VPAD(31); VPAD(32); VPAD(33); VPAD(34); VPAD(35); VPAD(36); VPAD(37); VPAD(38);
    VPAD(39); VPAD(40); VPAD(41);
    virtual bool IsRectangleSelecting();                                // +0xa8
};
cGameTerrainCursor* GetGameTerrainCursor();                             // 00b30d70

struct IWindow {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6);
    virtual uint32_t GetControlID();                                    // +0x1c
};
struct IWindowManager {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17);
    virtual IWindow* GetMouseWindow(int);                               // +0x48
};
IWindowManager* WindowManager();                                        // 0067caa0

struct cGameModeState { uint32_t pad[0x2c / 4]; int mState; };          // +0x2c
cGameModeState* GameModeState();                                        // 00b3d4d0

struct cUIState { char IsMouseOverUI(); };                              // 00b5ca60
cUIState* UIState();                                                    // 00b3d230

struct cListLink { cListLink* mpNext; cListLink* mpPrev; };
struct cTestSystem { uint32_t pad[0x70 / 4]; cListLink mTests; };       // +0x70
extern cTestSystem* sTestSystem;                                        // 015fd928

struct cViewer {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13);
    virtual Vector3 GetCursorPosition(int, Vector3 offset);             // +0x38
};
cViewer* Viewer();                                                      // 00b3d240

struct cGameNounManager { cTribe* GetPlayerTribe(); };                  // 00bfc5f0
cGameNounManager* NounManager();                                        // 00b3d300

struct cPlanetModel {
    int GetRegion(const Vector3& pos);                                  // 00b88590
    bool IsLand(const Vector3& pos);                                    // 00b7e3e0
};
cPlanetModel* PlanetModel();                                            // 00b3d350

struct cRelationshipManager { int GetRelationship(uint32_t a, uint32_t b, int c); };  // 00d00a70
cRelationshipManager* RelationshipManager();                            // 00b3d2c0

struct cPlayer { uint32_t GetPoliticalID(); };                          // 00ac79d0
cPlayer* Player();                                                      // 00b3d2b0

void* GetActivePlanet();                                                // 01021260

struct PropertyList;
extern PropertyList* g_TribeProperties;                                 // 0158128c
float GetPropertyFloat(PropertyList* list, uint32_t id, float def);     // 004e1c70

// ------------------------------------------------------------------ the function
// @ 0x00ccefb0
int GetTribeCursorID(cGameData* pObject, const Vector3* pPickPos)
{
    cTribeInputStrategy* input = cTribeModeStrategy::Instance()->GetInputStrategy();
    if (!input)
        return 0;

    int modeState = GameModeState()->mState;
    if (modeState == 1 || modeState == 2)
        return 2;

    if (UIState()->IsMouseOverUI() == 1 &&
        (!sTestSystem || sTestSystem->mTests.mpNext == &sTestSystem->mTests)) {
        IWindow* window = WindowManager()->GetMouseWindow(1);
        if (!window)
            return 0;
        if (window->GetControlID() == 0x36ad4a4 || window->GetControlID() == 0x625cd52)
            return 0x26;
        return 0;
    }

    if (input->mpController->IsPlacing()) {
        if (!pObject)
            return 0;
        cGameData* data = (cGameData*)pObject->Cast(kGameData);
        if (!data)
            return 0;
        if (data->GetNounID() != kTribeTool)
            return 0;
        cTribeTool* tool = (cTribeTool*)object_cast(data, kTribeTool);
        if (!tool->mSpatial.IsUnderConstruction())
            return 0;
        if (tool->GetToolType() == 10)
            return 0;
        return 0x2f;
    }

    cGameTerrainCursor* cursor = GetGameTerrainCursor();
    if (cursor && cursor->IsRectangleSelecting())
        return 0;

    if (cTribeModeStrategy::Instance()->GetInputStrategy()->mPendingAction != 0)
        return 8;

    if (input->mToolMode == 1) {
        cGameData* data = ToGameData(pObject);
        if (data && CanUseToolA(data))
            return 4;
        return 3;
    }
    if (input->mToolMode == 2) {
        cGameData* data = ToGameData(pObject);
        if (data && CanUseToolB(data))
            return 6;
        return 5;
    }

    if (cursor->GetSelectionCount() == 0) {
        cGameData* data = ToGameData(pObject);
        if (!data)
            return 0;
        uint32_t noun = data->GetNounID();
        if (noun == kGameDataUFO)
            return 0x30;
        if (noun != kTribeHut)
            return 0;
        cTribeHut* hut = (cTribeHut*)object_cast(data, kTribeHut);
        if (!hut->mSpatial.IsUnderConstruction())
            return 0;
        return 0x26;
    }

    cTribe* tribe = NounManager()->GetPlayerTribe();
    cPlanetModel* planet = PlanetModel();
    int tribeRegion = planet->GetRegion(tribe->mSpatial.GetPosition());

    Vector3 pos = pPickPos ? *pPickPos : Viewer()->GetCursorPosition(0, Vector3::ZERO);
    bool sameRegion = true;
    if (pos != Vector3::ZERO)
        sameRegion = PlanetModel()->GetRegion(pos) == tribeRegion;

    cGameData* data = ToGameData(pObject);
    if (!data) {
        cPickInfo* pick = GetPickInfo(pObject);
        if (pick) {
            if (planet->GetRegion(pick->mPosition) != tribeRegion)
                return 7;
            if (tribe->HasToolA())
                return 0x25;
        }
    } else {
        GetActivePlanet();
        switch (data->GetNounID()) {
        case kGameDataUFO:
            return 0x30;

        case kOrnament: {
            cOrnament* ornament = (cOrnament*)object_cast(data, kOrnament);
            if (ornament->mOrnamentType == 0x356eb8a) {
                if (pos != Vector3::ZERO) {
                    if (!PlanetModel()->IsLand(pos))
                        return 1;
                    return tribe->IsAllied() ? 0x22 : 7;
                }
            } else if (ornament->mOrnamentType == 0x5b9a06e) {
                float minHeight = GetPropertyFloat(g_TribeProperties, 0xd2078a9b, 10.0f);
                cOrnamentModel* model = GetOrnamentModel(ornament->GetModelKey());
                if (model && model->mHeight > minHeight)
                    return 0x23;
            }
            break;
        }

        case kGameBundle: {
            cGameBundle* bundle = (cGameBundle*)object_cast(data, kGameBundle);
            uint32_t owner = bundle->mOwnerID;
            if (owner == Player()->GetPoliticalID())
                return 0x1b;
            cTribe* other = GetTribeByPoliticalID(bundle->mOwnerID);
            if (!other)
                break;
            if (other == NounManager()->GetPlayerTribe()) {
                if (!other->HasToolB())
                    return 0x1e;
                return other->HasToolA() + 0x1f;
            }
            if (other->mbDefeated)
                return 0x1b;
            switch (cTribeModeStrategy::Instance()->mDifficulty) {
            case 0:
                return (RelationshipManager()->GetRelationship(other->GetPoliticalID(), tribe->GetPoliticalID(), 1) >= 2) + 0xe;
            case 1:
                if (RelationshipManager()->GetRelationship(other->GetPoliticalID(), tribe->GetPoliticalID(), 1) < 4)
                    return 0x21;
                break;
            }
            break;
        }

        case kTribeTool: {
            cTribeTool* tool = (cTribeTool*)object_cast(data, kTribeTool);
            tool->GetTribe()->GetPoliticalID();
            if (tool->mSpatial.IsUnderConstruction()) {
                if (tool->mCombatant.GetHealthPercentage() < 1.0f) {
                    if (tool->mCombatant.GetHealthPercentage() <= 0.0f)
                        return 0;
                    return 9;
                }
                switch (tool->GetToolType()) {
                case 8:  return 0x11;
                case 7:  return 0x12;
                case 1:  return 0x13;
                case 2:  return 0x14;
                case 3:  return 0x15;
                case 4:  return 0x16;
                case 5:  return 0x17;
                case 6:  return 0x18;
                case 9:  return 0x19;
                case 10: return 0x1a;
                }
                return 0;
            }
            if (cTribeModeStrategy::Instance()->mDifficulty != 1)
                return 0;
            if (tool->GetToolType() == 10)
                return 0;
            if (tool->mCombatant.GetDamageState() == 2)
                return 0;
            return tool->GetTribe()->IsRaided() ? 0xc : 0x2a;
        }

        case kCreatureAnimal: {
            cCreatureAnimal* animal = (cCreatureAnimal*)object_cast(data, kCreatureAnimal);
            if (tribeRegion != planet->GetRegion(animal->mLocomotive.GetPosition()))
                return 7;
            if (!animal->mbBusy) {
                switch (cTribeModeStrategy::Instance()->mDifficulty) {
                case 0:
                    if (animal->IsFlagged())
                        return 0;
                    if (animal->GetPoliticalID() == tribe->GetPoliticalID())
                        return 0;
                    return 0x29;
                case 1:
                    return 0xb;
                }
            }
            if (tribe->HasToolB())
                return 0x1c;
            break;
        }

        case kCreatureCitizen: {
            cCreatureCitizen* citizen = (cCreatureCitizen*)object_cast(data, kCreatureCitizen);
            if (citizen->mbBusy == 1)
                return 0;
            if (citizen->mLocomotive.IsUnderConstruction()) {
                float threshold = citizen->mThreshold;
                if (citizen->mTimer.GetValue() > threshold) {
                    SpatialFixedVector<16> selection;
                    GetGameTerrainCursor()->GetSelection(selection);
                    for (SpatialRef* it = selection.mpBegin; it != selection.mpEnd; ++it) {
                        cCreatureCitizen* other = ToCitizen(*it);
                        if (other && other != citizen && other->GetActivity() == 9)
                            return 0x28;
                    }
                }
                return 0x2e;
            }
            switch (cTribeModeStrategy::Instance()->mDifficulty) {
            case 0: {
                if (citizen->GetTribe()->mbDefeated)
                    return 0;
                cTribe* other = citizen->GetTribe();
                if (RelationshipManager()->GetRelationship(other->GetPoliticalID(), tribe->GetPoliticalID(), 1) < 2)
                    return IsCitizenIdle(citizen) ? 0x10 : 0xd;
                if (citizen->mpHerd->mBehaviorID == 0x546e8804)
                    return 0x2d;
                cCreatureCitizen* leader = tribe->GetLeader();
                if (leader && (!leader->mLocomotive.IsMoving() || leader->mbBusy))
                    return 0x2b;
                return 0x27;
            }
            case 1:
                return citizen->GetTribe()->IsRaided() ? 0xa : 0x2a;
            }
            return 0;
        }

        case kFruit: {
            cFruit* fruit = (cFruit*)object_cast(data, kFruit);
            if (tribe->HasToolA() && planet->GetRegion(fruit->mSpatial.GetPosition()) == tribeRegion)
                return 0x24;
            break;
        }

        case kTribeHut: {
            cTribeHut* hut = (cTribeHut*)object_cast(data, kTribeHut);
            cTribe* owner = hut->GetTribe();
            owner->GetPoliticalID();
            if (hut->mSpatial.IsUnderConstruction()) {
                if (hut->mCombatant.GetHealthPercentage() < 1.0f) {
                    if (hut->mCombatant.GetHealthPercentage() > 0.0f)
                        return 9;
                }
                return 0x26;
            }
            if (owner->mbDefeated)
                return 0;
            if (hut->mCombatant.GetDamageState() == 2)
                return 0;
            switch (cTribeModeStrategy::Instance()->mDifficulty) {
            case 0:
                return (RelationshipManager()->GetRelationship(owner->GetPoliticalID(), tribe->GetPoliticalID(), 1) >= 2) + 0xe;
            case 1:
                return hut->GetTribe()->IsRaided() ? 0xc : 0x2a;
            }
            break;
        }

        case kEgg:
            if (cTribeModeStrategy::Instance()->mDifficulty == 1)
                return 0x1d;
            break;

        case kTribeFoodMat: {
            cTribeFoodMat* mat = (cTribeFoodMat*)object_cast(data, kTribeFoodMat);
            cTribe* owner = mat->mpTribe;
            mat->GetPoliticalID();
            if (mat->mSpatial.IsUnderConstruction()) {
                if (!tribe->HasToolB())
                    return 0x1e;
                return tribe->HasToolA() + 0x1f;
            }
            if (((cFoodStore*)owner->mFood)->GetAmount() <= 0.0f)
                return 0;
            switch (cTribeModeStrategy::Instance()->mDifficulty) {
            case 0:
                if (owner->mbDefeated)
                    return 0;
                return (RelationshipManager()->GetRelationship(owner->GetPoliticalID(), tribe->GetPoliticalID(), 1) >= 2) + 0xe;
            case 1:
                if (RelationshipManager()->GetRelationship(owner->GetPoliticalID(), tribe->GetPoliticalID(), 1) < 4)
                    return 0x21;
                break;
            }
            break;
        }
        }
    }
    return sameRegion ? 0 : 7;
}
