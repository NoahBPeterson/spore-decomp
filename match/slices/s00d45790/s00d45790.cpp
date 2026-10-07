// SP::cCreatureModeStrategy::HandleSimulationUpdate  @ 0x00d45790
//
// ~3 KB __thiscall per-frame update of the creature game (/O2 /arch:SSE, no EH frame).
// While loading (mLoadingState.mState != 0xd) it only drives ContinueLoading. Otherwise it
// updates ornaments, posse members, herds (evolving herds the player has "caught up with" to the
// next archetype generation), scenarios, the end-of-game trigger, the reload stopwatch, the
// avatar's minimap marker, the display layer and the "cockpit" camera, and finally hands the
// frame to the game-mode manager.
//
//   void __thiscall HandleSimulationUpdate(cCreatureModeStrategy* this, float a, float b)  (ret 8)

#include "types.h"
#include <math.h>

// float -> int with the current MXCSR rounding (asm helper in the original).
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }
#pragma warning(disable: 4035)

struct Vector2
{
    float x, y;
    __forceinline Vector2() {}
    __forceinline Vector2(float a, float b) : x(a), y(b) {}
    __forceinline Vector2(const Vector2& o) : x(o.x), y(o.y) {}
};
struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
struct BoundingBox { Vector3 min, max; };

class cPropertyList;

// --- game objects ----------------------------------------------------------------------
class cCreatureStats   // cSPCreatureBase sub-object at +0xc0
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual int  GetTerrainRegion(float x, float y);          // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual bool IsInPosse();                                  // +0x58
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual BoundingBox GetBoundingBox();                      // +0x6c
    virtual float GetRadius(int a, int b, int c);              // +0x70
    virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32();
    virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
    virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40();
    virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
    virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48();
    virtual void s49();
    virtual float GetHealthFraction();                         // +0xc8
};

class cSPCreatureBase
{
public:
    uint32_t       pad00[0xc0 / 4];
    cCreatureStats mStats;               // +0xc0
    char           padc4[0xb5e - 0xc4];
    bool           mbReachedEnd;         // +0xb5e
    char           padb5f[0x1004 - 0xb5f];
    ResourceKey    mSpeciesKey;          // +0x1004
};

class cPosseMember   // objects of game-data type 0x018eb45e
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void Update(uint32_t deltaMS);                     // +0x60
    char pad04[0x135 - 4];
    bool mbIsInPosse;                                          // +0x135
};

class cInteractiveOrnament { public: void Update(uint32_t deltaMS); };   // 0x00c408f0

class cSpeciesProfile
{
public:
    char        pad[0x504];
    ResourceKey mKey;                                          // +0x504
};

struct ProfileKeyVector { ResourceKey* mpBegin; ResourceKey* mpEnd; ResourceKey* mpCapacity; };
struct CreatureVector { cSPCreatureBase** mpBegin; cSPCreatureBase** mpEnd; };

class cSpeciesArchetype;

class cHerd
{
public:
    uint32_t         pad00[0x40 / 4];
    CreatureVector   mHerd;              // +0x40
    uint32_t         pad48[(0x85 - 0x48) / 4];
    char             pad84;
    bool             mbEvolves;          // +0x85
    char             pad86[2];
    uint32_t         mSpeciesType;       // +0x88
    uint32_t         mSpeciesGroup;      // +0x8c
    uint32_t         pad90;
    float            mEvolveDistance;    // +0x94
    uint32_t         pad98[3];
    cSpeciesProfile* mpProfile;          // +0xa4
    ProfileKeyVector mEvolvedSpeciesProfileKeys;   // +0xa8
    uint32_t         padb4[(0xf0 - 0xb4) / 4];
    uint32_t         mGeneration;        // +0xf0

    bool IsActive();                                           // 0x00c6a020
    void Update(uint32_t deltaMS);                             // 0x00c6d7c0
    cSpeciesProfile* GetProfileForGeneration(uint32_t gen);    // 0x00c6abf0
    void UpdateFromArchetype(cSpeciesArchetype* a, int b);     // 0x00c6e200
};

struct ArchetypeGenVector
{
    void** mpBegin; void** mpEnd;
    __forceinline uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
class cSpeciesArchetype
{
public:
    char pad[0x3c4];
    ArchetypeGenVector mGenerations;                           // +0x3c4
};

class cSpeciesManager
{
public:
    cSpeciesProfile*   GetAvatarProfile();                     // 0x004df420
    cSpeciesArchetype* GetSpeciesArchetype(uint32_t type, uint32_t gen);   // 0x004e0050
};
cSpeciesManager* SpeciesManager();                             // 0x00401090

class cPlanet { public: bool SetSpeciesAsScanned(const ResourceKey* key); };   // 0x00c73ea0
namespace cSPLivingUniverse { cPlanet* GetActivePlanet(); }    // 0x01021260

void FUN_00b97600(uint32_t group, uint32_t type, uint32_t gen, cSpeciesProfile* p);
cSpeciesProfile* FUN_00b9a750(uint32_t group, uint32_t type, uint32_t gen,
                              cSpeciesProfile* oldProfile, bool* created);

// --- game-data vectors ------------------------------------------------------------------
template<class T> struct PtrVector
{
    T** mpBegin;
    T** mpEnd;
    __forceinline uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    __forceinline T*& operator[](uint32_t i) { return mpBegin[i]; }
};
template<class T> struct GameDataVector
{
    bool         mbDirty;
    PtrVector<T> mData;                  // +0x04
};

typedef void (*GameDataFn)();
void FUN_00cd7d10(); void FUN_00d3d420(); void FUN_00d3d440(); void FUN_00ace0f0();
void FUN_00accc30(); void FUN_00b1e500();

class cGameNounManager
{
public:
    cSPCreatureBase* GetAvatar();                                                   // 0x00b1fdb0
    void* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d, uint32_t type);   // 0x00b21340
};
cGameNounManager* NounManager();       // 0x00b3d300

// --- small managers -----------------------------------------------------------------------
class cGameTimeManager
{
public:
    char    pad[0x48];
    uint8_t mPauseFlags;                 // +0x48
    uint32_t ScaleDelta(uint32_t deltaMS);   // 0x00b31c60
    __forceinline bool IsPaused() { return (mPauseFlags & 1) != 0; }
};
cGameTimeManager* GameTimeManager();   // 0x00b3d380

class cGameModeManager
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void PreUpdate(uint32_t deltaMS);    // +0x2c
    virtual void PostUpdate(uint32_t deltaMS);   // +0x30
    void Update(uint32_t deltaMS);               // 0x00b5e9a0
};
cGameModeManager* GameModeManager();   // 0x00b3d230

struct cSimState { char pad[0x28]; bool mbSuspended; };   // +0x28
cSimState* FUN_00b3d320();

struct cGameState { char pad[0x2c]; int mState; };        // +0x2c
cGameState* FUN_00b3d4d0();

class cLoadGate { public: bool IsReady(); };               // 0x00e36e00
cLoadGate* FUN_00b3d410();

class cMinimap { public: void SetRegion(int region); };   // 0x00acc700
cMinimap* FUN_00b3d480();

class cAvatarMarker { public: void SetPosition(const Vector3* pos, float radius); };   // 0x00b76d20
cAvatarMarker* FUN_00b3d3c0();

Vector2 FUN_00ac8f00(cPropertyList* list, uint32_t key, Vector2 def);   // property vector2 lookup

class cAchievementsController { public: void AutoTest(uint32_t id, uint32_t a); };   // 0x00676e90
cAchievementsController* AchievementsController();       // 0x00675250

void FUN_01022920(uint32_t deltaMS);
namespace anon { void SetGlobalAudioProperties(cSPCreatureBase* avatar); }   // 0x00d41a70
float FUN_00d2e360();
void  FUN_00d425f0(float a);
void  FUN_00d3aa70();
void  FUN_00b6dbd0(float b);

extern bool  g_bHealthAudioEnabled;    // 0x0169e381
extern bool  g_bHealthAudioActive;     // 0x0169e380
extern float g_HealthAudioValue;       // 0x0169e384
extern bool  g_bHerdsEvolve;           // 0x01582df4

class cSPTimer
{
public:
    bool IsRunning();                  // 0x00feba90
    uint64_t GetElapsedTime();         // 0x00bc3190
    void Stop();                       // 0x00bc3110
};

struct Stopwatch
{
    uint64_t mnStartTime;              // +0x00
    uint64_t mnTotalElapsedTime;       // +0x08
    uint32_t mUnits;                   // +0x10
    float    mfStopwatchCyclesToUnitsCoefficient;   // +0x14
    int64_t  GetElapsedCycles();       // 0x0093a3a0
    __forceinline void Reset() { mnStartTime = 0; mnTotalElapsedTime = 0; }
};

// --- camera -------------------------------------------------------------------------------
struct LightParams
{
    uint16_t mA;
    uint16_t mB;
    Vector4  mColor;                   // +0x04
    Vector3  mRows[3];                 // +0x14
};
struct Matrix3 { Vector3 r[3]; __forceinline Vector3 Row(int i) const { return r[i]; } };
extern Vector3 g_SunColor;             // 0x0169e298
extern Matrix3 g_SunOrientation;       // 0x0169e3c0

struct PlanetTransform { uint32_t d[5]; void Finalize(); };   // 0x00fb8db0
class cPlanetCamera
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual PlanetTransform GetTransform();                    // +0x10
};
struct cPlanetModel { char pad[0x24]; cPlanetCamera* mpCamera; };
cPlanetModel* PlanetModel();           // 0x00b3d350

class cLightingObj { public: void Fill(LightParams* p); };   // 0x007c40f0

class cCamera
{
public:
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual void Commit();                                     // +0x0c
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void SetPlanetTransform(const PlanetTransform* t);   // +0x30
    virtual void v13();
    virtual void SetTarget(const Vector3* vel, const Vector3* dir);   // +0x38
    virtual void SetSunColor(const Vector4* c);                // +0x3c
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual uint32_t GetType();                                // +0x4c
};
cCamera* FUN_0067ddc0();

class cLocomotiveObject { public: const Vector3* GetVelocity(); };   // 0x00d20610
class cObjectFinder
{
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual cLocomotiveObject* Find(uint32_t id);              // +0x0c
};
class cWindowMgr
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual cLightingObj* GetLighting();                       // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual cObjectFinder* GetFinder();                        // +0x38
};
class cApp
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual cWindowMgr* GetWindowManager();                    // +0x50
};
cApp* App();                           // 0x0067dd10

// --- strategies ---------------------------------------------------------------------------
class cCreatureModeInputStrategy
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void Update(uint32_t deltaMS);                     // +0x10
    void SetInputPriorityStrategy(int s);                      // 0x00d33ec0
};
class cCreatureDisplayStrategy { public: void DrawLayer(int layer, uint32_t deltaMS); };   // 0x00d2dd20

class cCreatureModeScenario
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void Update(float seconds);                        // +0x10
};

// --- local containers ---------------------------------------------------------------------
// sp_fixed_vector<cHerd*, 16>: the word before the inline buffer is 0, a heap block has a
// non-zero header there.
template<class T, int N> struct FixedVector
{
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];
    int      mBufferHeader;
    T        mBuffer[N];

    __forceinline FixedVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + N), mBufferHeader(0) {}
    __forceinline ~FixedVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }
    void DoInsertValue(T* pos, const T& value);   // 0x00b96600
    __forceinline void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p) *p = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};

// eastl::hash_map<cSpeciesProfile*, cSpeciesProfile*>
struct ProfileNode { cSpeciesProfile* first; cSpeciesProfile* second; ProfileNode* mpNext; };
extern ProfileNode* gpEmptyBucketArray[2];   // 0x0154df28

struct prime_rehash_policy
{
    float    mfMaxLoadFactor;
    float    mfGrowthFactor;
    uint32_t mnNextResize;
    __forceinline prime_rehash_policy(float f = 1.0f) : mfMaxLoadFactor(f), mfGrowthFactor(2.0f), mnNextResize(0) {}
};

struct ProfileMap
{
    struct iterator
    {
        ProfileNode*  mpNode;
        ProfileNode** mpBucket;
        __forceinline iterator(ProfileNode* n, ProfileNode** b) : mpNode(n), mpBucket(b) {}
        __forceinline iterator(ProfileNode** b) : mpNode(*b), mpBucket(b) {}
        __forceinline iterator(const iterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
        __forceinline bool operator==(const iterator& x) const { return mpNode == x.mpNode; }
        __forceinline ProfileNode* operator->() const { return mpNode; }
    };

    ProfileNode**       mpBucketArray;
    uint32_t            mnBucketCount;
    uint32_t            mnElementCount;
    prime_rehash_policy mRehashPolicy;

    __forceinline ProfileMap() : mnBucketCount(0), mnElementCount(0), mRehashPolicy()
    {
        mnBucketCount = 1;
        mpBucketArray = gpEmptyBucketArray;
    }
    __forceinline ~ProfileMap()
    {
        clear();
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
    void DoFreeNodes(ProfileNode** buckets, uint32_t n);         // 0x00693230 (folded)
    cSpeciesProfile*& operator[](cSpeciesProfile* const& key);   // 0x00b474c0
    __forceinline void clear() { DoFreeNodes(mpBucketArray, mnBucketCount); mnElementCount = 0; }
    __forceinline void DoFreeBuckets(ProfileNode** buckets, uint32_t n)
    {
        if (n > 1) operator delete[](buckets);
    }
    __forceinline iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    __forceinline ProfileNode* DoFindNode(ProfileNode* pNode, cSpeciesProfile* const& k)
    {
        for (; pNode; pNode = pNode->mpNext)
            if (k == pNode->first)
                return pNode;
        return 0;
    }
    __forceinline iterator find(cSpeciesProfile* const& k)
    {
        const uint32_t n = (uint32_t)k % mnBucketCount;
        ProfileNode* const pNode = DoFindNode(mpBucketArray[n], k);
        return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
    }
};

template<class T> __forceinline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }

// --- the strategy ---------------------------------------------------------------------------
class cCreatureModeStrategy
{
public:
    void*    vtbl;                                 // +0x00
    uint32_t pad04[(0x28 - 4) / 4];
    cSPTimer mEnterEditorSafetyTimer;              // +0x28
    char     pad29[0x48 - 0x29];
    bool     mbGainedEvoPoints;                    // +0x48
    char     pad49[0x64 - 0x49];
    cCreatureModeInputStrategy* mpInputStrategy;   // +0x64
    cCreatureDisplayStrategy*   mpDisplayStrategy; // +0x68
    uint32_t pad6c[(0x88 - 0x6c) / 4];
    Stopwatch mReloadStopwatch;                    // +0x88
    uint32_t mState;                               // +0xa0  (cLoadingState)
    uint32_t mPreviousMode;                        // +0xa4
    uint32_t mCurrentMode;                         // +0xa8
    uint32_t mFrames;                              // +0xac
    int      mGameMode;                            // +0xb0
    cPropertyList* mpCreaturePropList;             // +0xb4
    cPropertyList* mpCreatureVerbPropList;         // +0xb8
    cCreatureModeScenario** mScenariosBegin;       // +0xbc
    cCreatureModeScenario** mScenariosEnd;         // +0xc0
    uint32_t padc4[(0xe4 - 0xc4) / 4];
    bool     mbShowTutorial;                       // +0xe4
    bool     mbTutorialFromIntro;                  // +0xe5
    bool     mbWaitForLoadGate;                    // +0xe6

    void ContinueLoading(uint32_t deltaMS);        // 0x00d43e30
    void NotifyWantToGoToEditor(bool b);           // 0x00d3c6a0
    void HandleSimulationUpdate(float gameDelta, float realDelta);
};

enum { kMODE_ENDING = 1, kLoadingDone = 0xd };

void cCreatureModeStrategy::HandleSimulationUpdate(float gameDelta, float realDelta)
{
    if (FUN_00b3d320()->mbSuspended) {
        GameModeManager()->Update((uint32_t)realDelta);
        return;
    }

    uint32_t deltaMS = RoundToInt(realDelta * 1000.0f);
    RoundToInt(gameDelta * 1000.0f);

    if (mbShowTutorial && mbWaitForLoadGate) {
        if (!FUN_00b3d410()->IsReady())
            return;
        mbWaitForLoadGate = false;
    }

    if (mState != kLoadingDone) {
        mFrames++;
        ContinueLoading(deltaMS);
        return;
    }

    uint32_t scaledMS = GameTimeManager()->ScaleDelta(deltaMS);
    FUN_01022920(scaledMS);
    AchievementsController()->AutoTest(0x838a3cf4, scaledMS);

    cGameModeManager* modeMgr = GameModeManager();
    modeMgr->PreUpdate(deltaMS);

    if (!GameTimeManager()->IsPaused()) {
        cGameNounManager* nounMgr = NounManager();
        cSPCreatureBase* avatar = nounMgr->GetAvatar();

        int state = FUN_00b3d4d0()->mState;
        if (state == 1 || state == 2) {
            Vector2 pos = FUN_00ac8f00(mpCreaturePropList, 0x509beb7, Vector2(100.0f, 150.0f));
            FUN_00b3d480()->SetRegion(avatar->mStats.GetTerrainRegion(pos.x, pos.y));
        }

        if (mEnterEditorSafetyTimer.IsRunning() && mEnterEditorSafetyTimer.GetElapsedTime() > 1) {
            NotifyWantToGoToEditor(false);
            mEnterEditorSafetyTimer.Stop();
        }

        mpInputStrategy->Update(scaledMS);
        anon::SetGlobalAudioProperties(avatar);

        GameDataVector<cInteractiveOrnament>* ornaments = (GameDataVector<cInteractiveOrnament>*)
            nounMgr->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00d3d440, FUN_00b1e500, 0x3a2511e);
        uint32_t n = ornaments->mData.size();
        for (uint32_t i = 0; i < n; i++) {
            cInteractiveOrnament* o = ornaments->mData[i];
            if (o)
                o->Update(scaledMS);
        }

        GameDataVector<cPosseMember>* posse = (GameDataVector<cPosseMember>*)
            nounMgr->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00ace0f0, FUN_00b1e500, 0x18eb45e);
        n = posse->mData.size();
        for (uint32_t i = 0; i < n; i++) {
            cPosseMember* m = posse->mData[i];
            if (m && m->mbIsInPosse)
                m->Update(scaledMS);
        }

        cSPCreatureBase* avatar2 = NounManager()->GetAvatar();
        if (g_bHealthAudioEnabled && g_bHealthAudioActive)
            g_HealthAudioValue = avatar2->mStats.GetHealthFraction();
        else
            g_HealthAudioValue = 0.0f;

        cSpeciesManager* speciesMgr = SpeciesManager();
        bool bHerdsEvolve = g_bHerdsEvolve;
        float seconds = (float)scaledMS * 0.001f;
        {
            FixedVector<cHerd*, 16> evolvingHerds;
            cSpeciesProfile* avatarProfile = speciesMgr->GetAvatarProfile();
            float maxEvolveDistance = FUN_00d2e360();

            GameDataVector<cHerd>* herds = (GameDataVector<cHerd>*)
                nounMgr->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00accc30, FUN_00b1e500, 0x1be418e);
            int herdCount = (int)herds->mData.size();
            for (int i = 0; i < herdCount; i++) {
                cHerd* herd = herds->mData[i];
                if (herd->IsActive())
                    herd->Update(scaledMS);
                if (mbGainedEvoPoints && herd->mbEvolves && herd->mpProfile != avatarProfile && bHerdsEvolve &&
                    herd->mEvolveDistance > 0.0f && herd->mEvolveDistance < maxEvolveDistance)
                {
                    uint32_t numGens = speciesMgr->GetSpeciesArchetype(herd->mSpeciesType, herd->mGeneration)->mGenerations.size();
                    uint32_t nextGen = herd->mGeneration + 1;
                    if (min_alt(nextGen, numGens) > herd->mGeneration)
                        evolvingHerds.push_back(herd);
                }
            }

            if (evolvingHerds.mpBegin != evolvingHerds.mpEnd) {
                cPlanet* planet = cSPLivingUniverse::GetActivePlanet();
                mbGainedEvoPoints = false;
                ProfileMap replaced;
                for (cHerd** it = evolvingHerds.mpBegin, **itEnd = evolvingHerds.mpEnd; it != itEnd; ++it) {
                    cHerd* herd = *it;
                    uint32_t numGens = speciesMgr->GetSpeciesArchetype(herd->mSpeciesType, herd->mGeneration)->mGenerations.size();
                    uint32_t nextGen = herd->mGeneration + 1;
                    uint32_t gen = min_alt(nextGen, numGens);
                    cSpeciesArchetype* archetype = speciesMgr->GetSpeciesArchetype(herd->mSpeciesType, gen);
                    cSpeciesProfile* oldProfile = herd->mpProfile;
                    cSpeciesProfile* profile = herd->GetProfileForGeneration(gen);
                    if (!profile)
                        continue;

                    cSpeciesProfile* newProfile;
                    ProfileMap::iterator found = replaced.find(profile);
                    if (found == replaced.end()) {
                        newProfile = profile;
                        if (planet->SetSpeciesAsScanned(&profile->mKey)) {
                            bool bCreated = false;
                            FUN_00b97600(herd->mSpeciesGroup, herd->mSpeciesType, gen, profile);
                            newProfile = FUN_00b9a750(herd->mSpeciesGroup, herd->mSpeciesType, gen, oldProfile, &bCreated);
                            if (!newProfile)
                                continue;
                            if (planet->SetSpeciesAsScanned(&newProfile->mKey))
                                continue;
                            replaced[profile] = newProfile;
                            herd->mEvolvedSpeciesProfileKeys.mpBegin[gen] = newProfile->mKey;
                        }
                    } else {
                        newProfile = found->second;
                        herd->mEvolvedSpeciesProfileKeys.mpBegin[gen] = newProfile->mKey;
                    }

                    herd->mGeneration = gen;
                    herd->mpProfile = newProfile;
                    herd->UpdateFromArchetype(archetype, 1);
                    if (newProfile != oldProfile) {
                        for (cSPCreatureBase** c = herd->mHerd.mpBegin, **cEnd = herd->mHerd.mpEnd; c != cEnd; ++c) {
                            cSPCreatureBase* creature = *c;
                            if (!creature->mStats.IsInPosse())
                                creature->mSpeciesKey = newProfile->mKey;
                        }
                    }
                }
            }

            for (cCreatureModeScenario** s = mScenariosBegin; s != mScenariosEnd; ++s)
                (*s)->Update(seconds);

            if (avatar && avatar->mbReachedEnd && mGameMode != kMODE_ENDING) {
                mpInputStrategy->SetInputPriorityStrategy(kMODE_ENDING);
                mGameMode = kMODE_ENDING;
            }
        }

        if (mReloadStopwatch.mnStartTime) {
            int64_t cycles = mReloadStopwatch.GetElapsedCycles();
            if ((float)cycles * mReloadStopwatch.mfStopwatchCyclesToUnitsCoefficient > 2.0f)
                mReloadStopwatch.Reset();
        }
        FUN_00d425f0(gameDelta);
    }

    FUN_00d3aa70();

    cSPCreatureBase* avatar = NounManager()->GetAvatar();
    if (avatar && FUN_00b3d3c0()) {
        int state = FUN_00b3d4d0()->mState;
        if (state != 1 && state != 2) {
            BoundingBox box = avatar->mStats.GetBoundingBox();
            Vector3 center;
            center.x = (box.max.x + box.min.x) * 0.5f;
            center.y = (box.max.y + box.min.y) * 0.5f;
            center.z = (box.max.z + box.min.z) * 0.5f;
            float radius = avatar->mStats.GetRadius(7, 1, 0);
            FUN_00b3d3c0()->SetPosition(&center, radius);
        }
    }

    if (mpDisplayStrategy)
        mpDisplayStrategy->DrawLayer(0, GameTimeManager()->IsPaused() ? 0 : deltaMS);

    modeMgr->PostUpdate(deltaMS);

    cCamera* camera = FUN_0067ddc0();
    if (camera && camera->GetType() == 0x5e51bb6) {
        cObjectFinder* finder = App()->GetWindowManager()->GetFinder();
        if (finder) {
            cLocomotiveObject* obj = finder->Find(0x2a7ecd2);
            if (obj) {
                Vector3 vel = *obj->GetVelocity();
                float invLen = 1.0f / sqrtf(vel.x * vel.x + (vel.y * vel.y + vel.z * vel.z) + 1e-08f);
                Vector3 dir;
                dir.x = invLen * vel.x;
                dir.y = vel.y * invLen;
                dir.z = vel.z * invLen;
                camera->SetTarget(&vel, &dir);
            }
        }
        cLightingObj* lighting = App()->GetWindowManager()->GetLighting();
        if (lighting) {
            LightParams params;
            params.mColor.x = g_SunColor.x;
            params.mColor.y = g_SunColor.y;
            params.mColor.z = g_SunColor.z;
            params.mColor.w = 1.0f;
            params.mA = 0;
            params.mB = 0;
            params.mRows[0] = g_SunOrientation.Row(0);
            params.mRows[1] = g_SunOrientation.Row(1);
            params.mRows[2] = g_SunOrientation.Row(2);
            lighting->Fill(&params);
            camera->SetSunColor(&params.mColor);
        }
        PlanetTransform xf = PlanetModel()->mpCamera->GetTransform();
        xf.Finalize();
        camera->SetPlanetTransform(&xf);
        camera->Commit();
    }

    FUN_00b6dbd0(realDelta);
    GameModeManager()->Update(deltaMS);
}
