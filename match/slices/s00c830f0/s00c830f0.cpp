// Slice s00c830f0 -- SP::cSimPlanetLowLOD::UpdateTerraforming (0x00c830f0, 2672 bytes).
//
// Per-update terraforming bookkeeping of the low-LOD planet simulation:
//   * on the first update the remembered level is the planet's T-score minus 2;
//   * in space mode a pending "terraform finished" state is resolved (resets the planet's
//     atmosphere/temperature drift, refreshes the space UI);
//   * the current terraform level (TerraformingManager) is compared to the remembered one:
//     the terrain-sphere entry of the planet gets its initial level / plant count; on a
//     change the planet's ecosystem stage is updated, the player gets the up/down
//     message, effect, audio and tutorial events, AI owners record a relationship event,
//     and the timer for the ecosystem collapse is (re)started or stopped;
//   * when the collapse timer expires (tuning property 0x3c5e2f2, seconds) or a collapse is
//     pending, the higher ecosystem levels are destroyed (TerraformingManager), the
//     extinction map is cleared, and at level 0 every creature/city on the active planet
//     is notified, colonies of type 0x18c43e8 are removed (tech level 4) and, if no
//     colony is left, the planet is reset;
//   * finally the cached atmosphere/temperature values are pushed to the terraforming
//     manager and the UI when they changed.
//
// Retail layout of cSimPlanetLowLOD is newer than the 2008 PDB: offsets come from the asm.
// Member and helper names are Claude-coined except where a symbol is known
// (TerraformingManager, NounManager, GetCurrentTerrainSphere, cSPTimer, RecordEvent, ...).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (no /EHsc: the local vectors have no EH frame)
#include "types.h"
#include <math.h>

typedef unsigned int uint;

void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);                                   // 0x00f473a0
void operator delete[](void* p);                                                 // 0x00f47380

// ------------------------------------------------------------------ properties
struct Property {
    uint32_t pad00[4];
    short    pad10;
    short    mnType;            // +0x12 (0xd = float)
    float* GetFloat();          // 0x0041ea70
};
struct PropertyList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};
PropertyList** GetTerraformTuning();                         // 0x01049a10

// ------------------------------------------------------------------ messaging / effects / audio
struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void PostMSG(uint32_t id, int a, int b);             // +0x14
    virtual void SendMSG(uint32_t id, int a, int b, int c);      // +0x18
};
IMessageServer* MessageServer();                             // 0x0067dcc0

struct IVisualEffect {
    virtual int AddRef();
    virtual int Release();                                   // +0x04
    virtual bool Start(int flags);                           // +0x08
};
struct IEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, IVisualEffect** dst);  // +0x2c
};
IEffectsManager* EffectsManager();                           // 0x0067ddd0

template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    // releases the current object and hands out the slot for an out parameter
    T** reset_out()
    {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};

struct IAudioSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual int GetRecorderState();                          // +0x20
};
IAudioSystem* GetAudioSystemAT();                            // 0x00a206f0 (EA::Audio::GetSystemAT)
inline int GetRecorderState()
{
    IAudioSystem* a = GetAudioSystemAT();
    return a ? a->GetRecorderState() : 0;
}
void PlayTerraformAudio(uint32_t id, int recorderState);    // 0x00435ed0 (labelled KillSetiEffects)

// ------------------------------------------------------------------ universe / empires
struct cEmpire {
    uint32_t pad00[0x84 / 4];
    uint32_t mPoliticalID;      // +0x84
};
struct cPlanetRecord {
    struct Elem12 { uint32_t a, b, c; };
    uint32_t pad00[0x2c / 4];
    uint32_t mFlags;            // +0x2c
    uint32_t pad30[(0xd0 - 0x30) / 4];
    Elem12*  mpPlantsBegin;     // +0xd0
    Elem12*  mpPlantsEnd;       // +0xd4
    uint32_t GetID();           // 0x00ce6950
    uint32_t PlantCount() { return (uint32_t)(mpPlantsEnd - mpPlantsBegin); }
};
void*          GetUniverseContext();                         // 0x01021080
struct cPlanet* GetActivePlanet();                           // 0x01021260
cPlanetRecord* GetActivePlanetRecord();                      // 0x010212a0
cEmpire*       GetPlayerEmpire();                            // 0x01021300
uint32_t       GetPlayerEmpireID();                          // 0x01021090
int            GetCurrentGameMode();                         // 0x00b5b800

struct cRelationshipManager {
    float RecordEvent(uint32_t politicalID, uint32_t otherID, uint32_t eventID, float scale);  // 0x00d06240
};
cRelationshipManager* RelationshipManager();                 // 0x00b3d2c0

struct cSPUIEventLog {
    void PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f);   // 0x00dd8640
};
cSPUIEventLog* EventLog();                                   // 0x00b3d3e0

struct cTutorial {
    void TerraformLevelChanged(int level, int oldLevel);     // 0x010681e0
    void Trigger(uint32_t id);                               // 0x0106dcd0
};
cTutorial* GetTutorial();                                    // 0x010666a0

struct cTribe { void FUN_00fe5430(int a, int b); };          // 0x00fe5430
struct cSpaceGame {
    void    FUN_01005180(int a);                             // 0x01005180
    cTribe* GetPlayerTribe();                                // 0x00bfc5f0
};
cSpaceGame* SpaceGameGet();                                  // 0x01002bd0

struct Z3 { int a, b, c; Z3() : a(0), b(0), c(0) {} };
void FUN_00e39ab0(uint32_t key, cEmpire* emp, Z3* d, Z3* c, uint32_t id, int zero, Z3* b, Z3* a);  // 0x00e39ab0

struct cTimeline { void FUN_00acd4a0(); };                   // 0x00acd4a0
cTimeline* FUN_00b3d480();                                   // 0x00b3d480

extern char g_ColonyReason[];                                // 0x01694bac
extern bool g_TerraformDisabled;                             // 0x016e06dc

// ------------------------------------------------------------------ planet
struct ByteVector {                                          // eastl::vector, sp_vector_allocator
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    const char* mpAllocName;
    ~ByteVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }
};

struct cPlanet {
    uint32_t pad00[0x13c / 4];
    cPlanetRecord* mpPlanetRecord;   // +0x13c
    int      GetTScore();             // 0x00c70880
    float    GetAtmosphereScore();    // 0x00c709d0
    float    GetTemperatureScore();   // 0x00c70a20
    bool     FUN_00c70a70();          // 0x00c70a70
    void     FUN_00c70aa0(float f);   // 0x00c70aa0
    void     SetNeedsReset(int b);    // 0x00c70de0
    int      GetTechLevel();          // 0x00c70e00
    void     SetEcosystemStage(int s);// 0x00c71550
    float    GetWaterScore();         // 0x00c71d30
    cEmpire* GetOwner();              // 0x00c71e30
    ByteVector GetCities();           // 0x00c73520
};

// ------------------------------------------------------------------ terrain sphere
struct cTerrainEntry {
    uint32_t pad00[0xa0 / 4];
    signed char mInitialLevel;        // +0xa0
    signed char mInitialPlants;       // +0xa1
};
struct cTerrainEntryMap {
    cTerrainEntry& operator[](const uint32_t& key);   // 0x00ba4e60
};
struct cTerrainSphere {
    uint32_t pad00[0x11c0 / 4];
    cTerrainEntryMap mEntries;        // +0x11c0
    void SetTerraformLevel(uint32_t planetID, int level);   // 0x00c83090
    bool HasMusic(uint32_t id);       // 0x00c772c0
    void PlayMusic(uint32_t id);      // 0x00c77bf0
};

// ------------------------------------------------------------------ game data / nouns
struct cGameData;
struct ILocatorSub {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14();
    virtual void SetTerraformState(float f, uint32_t empireID, int a, void* reason, int b);   // +0x18
};
struct cCreatureLike {
    uint32_t pad00[0x120 / 4];
    ILocatorSub mSub;                 // +0x120
    uint32_t pad124[(0x158 - 0x124) / 4];
    float    mF158;                   // +0x158
};
struct cGameData {
    virtual int AddRef();
    virtual int Release();            // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual void v6c(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8();
    virtual cCreatureLike* AsCreature();   // +0xac
    void FUN_00bdc050();              // 0x00bdc050
};

struct GDIter {
    cGameData** mp;
    __forceinline GDIter(cGameData** p) : mp(p) {}
    __forceinline GDIter(const GDIter& x) : mp(x.mp) {}
};
struct false_type {};
GDIter FUN_00829110(GDIter first, GDIter last, GDIter dest, false_type);   // 0x00829110 uninitialized_copy (AddRefs)

struct sp_allocator { const char* mpName; };

// eastl::vector<intrusive_ptr<cGameData>> with the "Simulator" sp allocator
struct GameDataPtrVector {
    cGameData** mpBegin;
    cGameData** mpEnd;
    cGameData** mpCapacity;
    sp_allocator mAllocator;

    void DoInit(int n, const sp_allocator& a);   // 0x00b93c60 (VectorBase(n, allocator), out of line)

    __forceinline GameDataPtrVector(const GameDataPtrVector& x, int)
    {
        DoInit((int)(x.mpEnd - x.mpBegin), x.mAllocator);
        mpEnd = FUN_00829110(GDIter(x.mpBegin), GDIter(x.mpEnd), GDIter(mpBegin), false_type()).mp;
    }
    __forceinline GameDataPtrVector(const GameDataPtrVector& x)
    {
        int n = (int)(x.mpEnd - x.mpBegin);
        mpBegin = n ? (cGameData**)operator new(n * sizeof(cGameData*), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1) : 0;
        mpEnd = FUN_00829110(GDIter(x.mpBegin), GDIter(x.mpEnd), GDIter(mpBegin), false_type()).mp;
        mpCapacity = mpBegin + n;
    }
    __forceinline ~GameDataPtrVector()
    {
        for (cGameData** p = mpBegin; p < mpEnd; ++p)
            if (*p) (*p)->Release();
        if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct tGameDataVector {
    bool              mbDirty;   // +0x0
    GameDataPtrVector mData;     // +0x4
};

void FUN_00cd7d10();   // 0x00cd7d10
void FUN_00d3d420();   // 0x00d3d420
void FUN_00accbb0();   // 0x00accbb0
void FUN_00acdff0();   // 0x00acdff0
void FUN_00b1e500();   // 0x00b1e500

struct cGameNounManager {
    tGameDataVector* GetGameDataVector(void (*create)(), void (*f2)(), void (*filter)(), void (*f4)(),
                                       uint32_t typeID);   // 0x00b21340
    void RemoveNoun(cGameData* noun);                       // 0x00b225d0
    void RemoveNounsOfType(uint32_t typeID);                // 0x00b22650
    void FUN_00b25ee0();                                    // 0x00b25ee0
    cTerrainSphere* GetCurrentTerrainSphere();              // 0x00f67d90
};
cGameNounManager* NounManager();                            // 0x00b3d300

// ------------------------------------------------------------------ terraforming manager
struct cTerraformingManager {
    int  GetTerraformLevel(cPlanetRecord* record);          // 0x00bbc670
    bool DestroyEcosystemLevel(int level, cPlanet* planet); // 0x00bbcb90
    void UpdatePlanetScores(cPlanet* planet, float atmosphere, float temperature, bool b);  // 0x00bbcf00
    void FUN_00bbe740(cPlanet* planet);                     // 0x00bbe740
    void FUN_00bc1450(cPlanet* planet);                     // 0x00bc1450
};
cTerraformingManager* TerraformingManager();                // 0x00b3d430

struct cSPTimer {
    uint32_t data[0x40 / 4];
    void     Restart();             // 0x00bc3130
    void     Stop();                // 0x00bc3170
    uint64_t GetElapsedTime();      // 0x00bc3190
    bool     IsRunning();           // 0x00feba90
};

// eastl::map, cleared inline (DoNukeSubtree out of line)
struct rbtree_node;
struct ExtinctionMap {
    uint32_t     mCompare;          // +0x00
    rbtree_node* mpNodeRight;       // +0x04 (anchor)
    rbtree_node* mpNodeLeft;        // +0x08
    rbtree_node* mpNodeParent;      // +0x0c
    char         mColor;            // +0x10
    uint32_t     mnSize;            // +0x14

    void DoNukeSubtree(rbtree_node* p);   // 0x009a9600
    void clear()
    {
        DoNukeSubtree(mpNodeParent);
        mpNodeRight = (rbtree_node*)&mpNodeRight;
        mpNodeLeft = (rbtree_node*)&mpNodeRight;
        mpNodeParent = 0;
        mColor = 0;
        mnSize = 0;
    }
};

__forceinline cTerrainEntry& TerrainEntry(cPlanetRecord* record)
{
    uint32_t planetID = record->GetID();
    cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
    return sphere->mEntries[planetID];
}

namespace SP {

class cSimPlanetLowLOD {
public:
    uint32_t pad000[0x4c / 4];
    cPlanet* mpPlanet;                   // +0x4c
    uint32_t pad050[(0x1fd0 - 0x50) / 4];
    bool     mbScoresDirty;              // +0x1fd0
    uint8_t  pad1fd1[3];
    float    mF1fd4;                     // +0x1fd4
    float    mF1fd8;                     // +0x1fd8
    float    mLastAtmosphere;            // +0x1fdc
    float    mLastTemperature;           // +0x1fe0
    float    mLastWater;                 // +0x1fe4
    int      mLastTerraformLevel;        // +0x1fe8
    uint32_t pad1fec;
    cSPTimer mCollapseTimer;             // +0x1ff0
    bool     mbFinishPending;            // +0x2030
    bool     mb2031;                     // +0x2031
    uint8_t  pad2032[0x20a0 - 0x2032];
    ExtinctionMap mExtinctionMap;        // +0x20a0

    void FUN_00c7f060();                 // 0x00c7f060
    bool FUN_00c7ee50();                 // 0x00c7ee50
    void FUN_00c7fab0(int arg);          // 0x00c7fab0

    void UpdateTerraforming(int arg);
};

// @ 0x00c830f0
void cSimPlanetLowLOD::UpdateTerraforming(int arg)
{
    cTerraformingManager* terraform;
    cPlanetRecord* record = mpPlanet->mpPlanetRecord;
    terraform = TerraformingManager();

    if (mLastTerraformLevel < 0)
        mLastTerraformLevel = mpPlanet->GetTScore() - 2;

    if (!g_TerraformDisabled && mbFinishPending && GetCurrentGameMode() == 0x1654c05) {
        FUN_00c7fab0(arg);
        if (FUN_00c7ee50()) {
            mbFinishPending = false;
            mb2031 = false;
            mF1fd4 = 0.0f;
            mF1fd8 = 0.0f;
            if (mpPlanet != 0 && !mpPlanet->FUN_00c70a70())
                mpPlanet->FUN_00c70aa0(mpPlanet->GetWaterScore());
            SpaceGameGet()->FUN_01005180(1);
        }
    }

    int level = terraform->GetTerraformLevel(record);
    bool isActive = GetUniverseContext() == 0 && mpPlanet == GetActivePlanet();
    bool collapsePending = false;

    if (TerrainEntry(record).mInitialLevel == -1)
        TerrainEntry(record).mInitialLevel = (signed char)level;
    if (TerrainEntry(record).mInitialPlants == -1) {
        uint32_t plants = record->PlantCount();
        TerrainEntry(record).mInitialPlants = (signed char)(plants / 3);
    }

    if (level != mLastTerraformLevel) {
        if (mpPlanet->GetTScore() >= 2) {
            switch (level) {
            case 0: mpPlanet->SetEcosystemStage(2); break;
            case 1: mpPlanet->SetEcosystemStage(3); break;
            case 2: mpPlanet->SetEcosystemStage(4); break;
            case 3: mpPlanet->SetEcosystemStage(5); break;
            default: mpPlanet->SetEcosystemStage(2); break;
            }
        }

        if (isActive) {
            MessageServer()->SendMSG(0x490d429, 0, 0, 0);
            uint32_t effectID = 0xc5be3f36;
            if (level <= mLastTerraformLevel)
                effectID = 0x95857906;
            intrusive_ptr<IVisualEffect> effect;
            if (EffectsManager()->CreateVisualEffect(effectID, 0, effect.reset_out()))
                effect->Start(0);
        }

        if (level < mLastTerraformLevel) {
            if (isActive)
                mCollapseTimer.Restart();
            else
                collapsePending = true;
        } else {
            mCollapseTimer.Stop();
        }

        if (mbFinishPending) {
            bool aiOwned;
            cEmpire* owner = mpPlanet->GetOwner();
            if (owner == 0 || owner == GetPlayerEmpire()) {
                aiOwned = false;
            } else {
                uint32_t pid = owner->mPoliticalID;
                aiOwned = true;
                if (level < mLastTerraformLevel)
                    RelationshipManager()->RecordEvent(pid, GetPlayerEmpireID(), 0x526e531, 1.0f);
                else
                    RelationshipManager()->RecordEvent(pid, GetPlayerEmpireID(), 0x526e535, 1.0f);
            }

            if (isActive) {
                GetTutorial()->TerraformLevelChanged(level, mLastTerraformLevel);
                if (level < mLastTerraformLevel)
                    PlayTerraformAudio(0x5877dcf4, GetRecorderState());
                else
                    PlayTerraformAudio(0xb1cdbbcf, GetRecorderState());

                if (!aiOwned) {
                    if (level > TerrainEntry(record).mInitialLevel) {
                        NounManager()->GetCurrentTerrainSphere()->SetTerraformLevel(record->GetID(), level);
                        SpaceGameGet()->GetPlayerTribe()->FUN_00fe5430(3, 1);
                        Z3 a, b, c, d;
                        FUN_00e39ab0(0xecc0fff3, 0, &d, &c, GetActivePlanetRecord()->GetID(), 0, &b, &a);
                    }
                    if (level > mLastTerraformLevel && !(record->mFlags & 0x800)) {
                        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
                        if (sphere != 0 && !sphere->HasMusic(0x4d7f97a)) {
                            sphere->PlayMusic(0x4d7f97a);
                            GetTutorial()->Trigger(0xb010e8b);
                        }
                    }
                }
            }
        }
        mLastTerraformLevel = level;
    }

    bool collapse = false;
    if (mCollapseTimer.IsRunning()) {
        float seconds = (float)mCollapseTimer.GetElapsedTime() * 0.001f;
        float delay = 0.0f;
        PropertyList* tuning = *GetTerraformTuning();
        Property* prop;
        if (tuning != 0 && tuning->GetProperty(0x3c5e2f2, prop) && prop->mnType == 0xd)
            delay = *prop->GetFloat();
        if (level == 0 || seconds > delay) {
            mCollapseTimer.Stop();
            collapse = true;
        }
    }
    if (collapse || collapsePending) {
        bool destroyed = false;
        if (level == 0 || !(mpPlanet->mpPlanetRecord->mFlags & 0x800)) {
            for (int i = 3; i > level; --i) {
                if (terraform->DestroyEcosystemLevel(i, mpPlanet))
                    destroyed = true;
            }
            if (destroyed) {
                cEmpire* owner = mpPlanet->GetOwner();
                if (owner != 0 && owner != GetPlayerEmpire())
                    RelationshipManager()->RecordEvent(owner->mPoliticalID, GetPlayerEmpireID(), 0x526e537, 1.0f);
                if (isActive)
                    EventLog()->PostFeedbackEvent(0x752e35a4, 0x131a9f54, 0, 0, 1, 0);
                mExtinctionMap.clear();
                TerraformingManager()->FUN_00bbe740(mpPlanet);
            }
        }
        TerraformingManager()->FUN_00bc1450(mpPlanet);

        if (level == 0) {
            if (isActive) {
                FUN_00b3d480()->FUN_00acd4a0();
                cGameNounManager* nouns = NounManager();
                GameDataPtrVector creatures(nouns->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0,
                                                                     FUN_00b1e500, 0x18c6d19)->mData, 0);
                int count = creatures.size();
                for (int i = 0; i < count; i++) {
                    cCreatureLike* c = creatures.mpBegin[i]->AsCreature();
                    if (c != 0)
                        c->mSub.SetTerraformState(c->mF158, GetPlayerEmpireID(), 0, g_ColonyReason, 0);
                }
                if (mpPlanet->GetTechLevel() == 4) {
                    GameDataPtrVector colonies(nouns->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00acdff0,
                                                                        FUN_00b1e500, 0x18c43e8)->mData);
                    int n = colonies.size();
                    for (int i = 0; i < n; i++) {
                        cGameData* colony = colonies.mpBegin[i];
                        colony->FUN_00bdc050();
                        nouns->RemoveNoun(colony);
                    }
                }
                nouns->RemoveNounsOfType(0x18c84a9);
                tGameDataVector* left = nouns->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00acdff0,
                                                                 FUN_00b1e500, 0x18c43e8);
                if (left->mData.mpBegin == left->mData.mpEnd) {
                    nouns->RemoveNounsOfType(0x18c6de8);
                    nouns->FUN_00b25ee0();
                    mpPlanet->SetNeedsReset(1);
                }
            } else {
                bool none;
                {
                    ByteVector cities = mpPlanet->GetCities();
                    none = cities.mpBegin == cities.mpEnd;
                }
                if (none)
                    mpPlanet->SetNeedsReset(1);
                return;
            }
        }
    }

    if (isActive) {
        if (fabsf(mpPlanet->GetAtmosphereScore() - mLastAtmosphere) > 0.0f ||
            fabsf(mpPlanet->GetTemperatureScore() - mLastTemperature) > 0.0f ||
            fabsf(mpPlanet->GetWaterScore() - mLastWater) > 0.0f) {
            terraform->UpdatePlanetScores(mpPlanet, mpPlanet->GetAtmosphereScore(),
                                          mpPlanet->GetTemperatureScore(), mbFinishPending);
            MessageServer()->PostMSG(0x1c3d2e0, 1, 0);
            mLastAtmosphere = mpPlanet->GetAtmosphereScore();
            mLastTemperature = mpPlanet->GetTemperatureScore();
            if (mLastWater != mpPlanet->GetWaterScore()) {
                mbScoresDirty = true;
                mLastWater = mpPlanet->GetWaterScore();
            }
        }
        if (mbScoresDirty)
            FUN_00c7f060();
    }
}

}  // namespace SP
