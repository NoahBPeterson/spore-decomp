// Slice s00fddba0: SP::cAppModeSpace::TransitionFromPlanetToSolar (0x00fde3e0). The PDB-candidate name
// (cSPSimulatorWalkAround::UpdateBeaming) is a single-caller guess; by position this is the inverse of
// TransitionFromSolarToPlanet at 0x00fdeac0, so it is named after it.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
//   void __thiscall TransitionFromPlanetToSolar(cAppModeSpace* this, bool bUpdateEmpire)   (ret 4)
//
// Leaving a planet for the solar system: raises the space game's "transitioning" flag (+0x50 bit 0),
// drops the cached models, then parks the player's UFO next to the active planet (when the camera view
// reports flag A it flies out along the planet's orientation by a fixed distance and takes the combined
// planet * UFO orientation; otherwise it takes an orientation looking at the planet), restores the
// space-game camera / chase state, re-shows hidden solar-system planets, awards the play-time and
// "ten fully built T3 colonies" achievements, resets the tutorial popup, updates the player empire HUD,
// notifies the active planet record, clears the transition flag, posts message 0x5e37a2c and releases
// the temporary star list.
#include "types.h"
#include <math.h>

void* operator new[](unsigned int n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
void operator delete[](void* p);                                                                                       // 0x00f47380

#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define VIRT4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

extern const Vector3 kUpAxisY;      // 0x015b4028 (0, 1, 0)
extern const Vector3 kUpAxisZ;      // 0x015b4034 (0, 0, 1)
extern const Vector3 kFlyOutScale;  // 0x015b4204 (x = 10.0)
extern bool gViewFlagA;             // 0x016dd441

// ---- spatial objects (planet, UFO sub-object): vtable +0x2c position, +0x30 orientation ----------
class cSpatialObject
{
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* GetPosition();                  // +0x2c
    virtual const Quaternion* GetOrientation();            // +0x30
};

class cPlanetInfo
{
public:
    bool IsHidden();                                       // 0x00b8d970 ((flags >> 8) & 1)
};

class cPlanet : public cSpatialObject
{
public:
    int GetKind();                                         // 0x00c70880 (0 and 1 are skipped)
    uint32_t pad04[(0x13c - 0x04) / 4];
    cPlanetInfo* mpInfo;                                   // +0x13c
};

class cSolarSystem
{
public:
    uint32_t pad00[0x10 / 4];
    cPlanet** mPlanetsBegin;                               // +0x10
    cPlanet** mPlanetsEnd;                                 // +0x14
};

class cStar
{
public:
    cSolarSystem* GetSolarSystem();                        // 0x00c8b770
    virtual int AddRef();
    virtual int Release();
};

class cSPGameDataUFO
{
public:
    void SetDestination(const Vector3* p);                 // 0x00c3bfe0
    void SetDestination(cPlanet* planet);                  // 0x00c3c190
    void PopToDestination();                               // 0x00c37e60

    uint32_t       pad00[0x34 / 4];
    cSpatialObject mSpatial;                               // +0x34
    uint32_t       pad38[(0x730 - 0x38) / 4];
    Quaternion     mOrientation;                           // +0x730
};

class cEffect
{
public:
    void Stop(int fast);                                   // 0x0106ab20 (ret 4)
};

class cSPSpaceGameState                                    // object at cAppModeSpace +0x15c
{
public:
    void Reset();                                          // 0x0100a960
    void Update();                                         // 0x01003a50
    void ChaseFromPlanetToSolar();                         // 0x01007ed0
    uint32_t pad00[0x14 / 4];
    cEffect* mpActiveEffect;                               // +0x14
    uint32_t pad18[(0x50 - 0x18) / 4];
    uint32_t mFlags;                                       // +0x50
};

class cStarList { public: uint32_t pad00[0x2c / 4]; cStar** mBegin; cStar** mEnd; };   // vector at +0x2c
class cSpaceGame { public: uint32_t pad00[0x30 / 4]; cStarList* mpStars; };            // +0x30

class cSPSimulatorSpaceGame
{
public:
    cSPGameDataUFO* GetPlayerInventory();                  // 0x00a1ad60
};

// ---- globals / singletons ----------------------------------------------------------------------------
cStar* GetActiveStar();                                    // 0x01021230
cPlanet* GetActivePlanet();                                // 0x01021260
void* GetActivePlanetRecord();                             // 0x010212a0
cSPSimulatorSpaceGame* GetUFOSimulator();                  // 0x00ffbe50
cSpaceGame* SpaceGameGet();                                // 0x01002bd0

class cHud
{
public:
    bool IsActive();                                       // 0x00a98020
    int GetMode();                                         // 0x00985e40
    void Show();                                           // 0x01016950
};
cHud* GetHud();                                            // 0x01015df0

// App() -> (+0x50) mode manager -> (+0x38) current mode -> (+0xc) query by type id
class cCameraView
{
public:
    char pad00[0xb4];
    Vector3 mTarget;                                       // +0xb4
    char padc0[0x13d - 0xc0];
    bool mbFlag;                                           // +0x13d
};
class cHudCtl
{
public:
    void Apply(const Vector3* target, bool flag);          // 0x0101bb90 (ret 8)
};
class cModeObject
{
public:
    virtual void m0(); virtual void m1(); virtual void m2();
    virtual void* Query(uint32_t typeID);                  // +0xc
};
class cModeManager
{
public:
    VIRT4(a) VIRT4(b) VIRT4(c) virtual void c4(); virtual void c5();
    virtual cModeObject* GetCurrentMode();                 // +0x38
};
class cApp
{
public:
    VIRT4(a) VIRT4(b) VIRT4(c) VIRT4(d) VIRT4(e)
    virtual cModeManager* GetModeManager();                // +0x50
};
cApp* App();                                               // 0x0067dd10

class cMessageServer
{
public:
    VIRT4(a) virtual void v10(); virtual void v14();
    virtual void PostMessage(uint32_t id, int a, int b, int c);   // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void Notify(void* target, uint32_t id, int param);    // +0x2c (ret 0xc)
};
cMessageServer* MessageServer();                           // 0x0067dcc0

class cPlanetModel
{
public:
    void Refresh();                                        // 0x00b8c0f0
};
cPlanetModel* PlanetModel();                               // 0x00b3d350
class cTerrainSphere
{
public:
    void SetModel(uint32_t id);                            // 0x00c77bf0 (ret 4)
};
class cNounManager
{
public:
    cTerrainSphere* GetCurrentTerrainSphere();             // 0x00f67d90
};
cNounManager* NounManager();                               // 0x00b3d300
class cEffectsMgr
{
public:
    void Play(uint32_t id);                                // 0x00b5cde0 (ret 4)
};
cEffectsMgr* GetEffectsMgr();                              // 0x00b3d230
class cPlanetRegistry
{
public:
    void Show(cPlanet* p);                                 // 0x00b7daf0 (ret 4)
};
cPlanetRegistry* GetPlanetRegistry();                      // 0x00b3d360

class cSPTimer
{
public:
    unsigned __int64 GetElapsedTime();                     // 0x00bc3190
};
class cAchievementsController
{
public:
    void AwardAchievement(uint32_t id);                    // 0x00676710 (ret 4)
};
cAchievementsController* GetAchievements();                // 0x00675250

struct cTuning
{
    int GetMaxBuildingsForT3Colony();                      // 0x01049ef0
};
cTuning* GetTerraformTuning();                             // 0x01049a10 (returns &global 0x016e0d04)
void GetTurretAndBuildingCounts(cStar* star, int* turrets, int* buildings);   // 0x00c70380 (cdecl)

struct cTutorialStep { uint32_t pad00[2]; uint32_t mID; };   // +8
class cTutorial
{
public:
    uint32_t pad00[0x4c / 4];
    cTutorialStep* mpCurrent;                              // +0x4c
    void Close(uint32_t id, int flag);                     // 0x0067c8c0 (ret 8)
};
cTutorial* GetTutorial();                                  // 0x0067cac0
class cPopup
{
public:
    void Refresh();                                        // 0x01065d20
};
cPopup* GetPopup();                                        // 0x010666a0

class cEmpire
{
public:
    int GetID();                                           // 0x00c30c80
    void* GetUFOKey();                                     // 0x00c326b0
};
cEmpire* GetPlayerEmpire();                                // 0x01021300
class cHudEmpire
{
public:
    void Update(int id);                                   // 0x004df3e0 (ret 4)
};
cHudEmpire* GetHudEmpire();                                // 0x00401090

void NotifyActivePlanetRecord(void* record);               // 0x00fde230 (cdecl)

// helpers of the vector / quaternion library
Vector3* RotateByQuaternion(Vector3* out, const Vector3* v, const Quaternion* q);   // 0x0059aed0 (cdecl)
Vector3* OrthogonalVector(Vector3* out, const Vector3* v);                          // 0x006985b0 (cdecl)
Quaternion* QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing, const Vector3* up);   // 0x0069b600 (cdecl)

// eastl::vector<AutoRefCount<cMWModel>> helpers
class cMWModel;
struct cModelRef { cMWModel* p; };
cModelRef* copy_impl(cModelRef* first, cModelRef* last, cModelRef* dest);            // 0x005f4e10 (cdecl)
// uninitialized copy of AutoRefCount<cStar>: AddRef each element
cStar*** uninitialized_copy_stars(cStar*** out, cStar** first, cStar** last, cStar** dest, int tag);   // 0x00829110 (cdecl)

struct ModelVector
{
    cModelRef* mpBegin;                                    // +0x144 in cAppModeSpace
    cModelRef* mpEnd;
    cModelRef* mpCapacity;
    void DoDestroyValues(cModelRef* first, cModelRef* last);   // 0x005f3680 (ret 8)
    cModelRef* erase(cModelRef* first, cModelRef* last)
    {
        cModelRef* itDest = copy_impl(last, mpEnd, first);
        DoDestroyValues(itDest, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

inline Quaternion QuatMul(const Quaternion& a, const Quaternion& b)
{
    float c0 = a.z * b.y - a.y * b.z;
    float c1 = b.z * a.x - a.z * b.x;
    float c2 = a.y * b.x - b.y * a.x;
    Quaternion r;
    r.x = (a.x * b.w + b.x * a.w) + c0;
    r.y = (a.y * b.w + b.y * a.w) + c1;
    r.z = (a.z * b.w + b.z * a.w) + c2;
    r.w = a.w * b.w - ((a.z * b.z + a.y * b.y) + a.x * b.x);
    return r;
}

class cModeBase { public: void* mpVtbl; };                         // interface sub-object at +0x04

class cAppModeSpace
{
public:
    void TransitionFromPlanetToSolar(bool bUpdateEmpire);          // 0x00fde3e0
    bool Shutdown();                                               // 0x00fde180
    void ShutdownSPG();                                            // 0x00fdc150
    static void SetDefaultPickPriority();                          // 0x00fddba0

    char pad00[0x04];
    cModeBase mBase;                                               // +0x04 message-server target
    char pad08[0x144 - 0x08];
    ModelVector mModels;                                           // +0x144
    char pad150[0x15c - 0x150];
    cSPSpaceGameState* mpSpaceGame;                                // +0x15c
    static cAppModeSpace* sInstance;                               // 0x016d9938
};

// @ 0x00fde3e0
void cAppModeSpace::TransitionFromPlanetToSolar(bool bUpdateEmpire)
{
    mpSpaceGame->mFlags |= 1;
    mModels.clear();

    cStar* star = GetActiveStar();
    cPlanet* planet = GetActivePlanet();
    cSPGameDataUFO* ufo = GetUFOSimulator()->GetPlayerInventory();

    cHud* hud = GetHud();
    if (hud && (hud->IsActive() || hud->GetMode() == 2))
        hud->Show();

    cModeObject* mode = App()->GetModeManager()->GetCurrentMode();
    cCameraView* view = 0;
    bool viewFlagA;
    bool viewFlagB;
    if (mode && (view = (cCameraView*)mode->Query(0x303154cd)) != 0)
    {
        viewFlagA = gViewFlagA;
        viewFlagB = view->mbFlag;
    }
    else
    {
        view = 0;
        viewFlagA = false;
        viewFlagB = false;
    }

    const Vector3* src;
    Vector3 viewTarget;
    if (view == 0)
        src = &kUpAxisY;
    else
    {
        viewTarget.x = view->mTarget.x;
        viewTarget.y = view->mTarget.y;
        viewTarget.z = view->mTarget.z;
        src = &viewTarget;
    }
    Vector3 camTarget;
    camTarget.x = src->x; camTarget.y = src->y; camTarget.z = src->z;

    const Vector3* ufoSrc = ufo->mSpatial.GetPosition();
    Vector3 ufoPos;
    ufoPos.x = ufoSrc->x; ufoPos.y = ufoSrc->y; ufoPos.z = ufoSrc->z;

    mpSpaceGame->Reset();
    PlanetModel()->Refresh();
    NounManager()->GetCurrentTerrainSphere()->SetModel(0x574ac66);
    GetEffectsMgr()->Play(0x1103192);

    if (viewFlagA)
    {
        const Quaternion* planetOri = planet->GetOrientation();
        Vector3 rotated;
        Vector3* p = RotateByQuaternion(&rotated, &ufoPos, planetOri);
        float x = p->x, y = p->y, z = p->z;
        float inv = 1.0f / (float)sqrt(x * x + z * z + y * y);
        float offX = (inv * x) * kFlyOutScale.x;
        float offY = (y * inv) * kFlyOutScale.x;
        float offZ = (z * inv) * kFlyOutScale.x;
        const Vector3* pos = planet->GetPosition();
        Vector3 dest;
        dest.x = pos->x + offX;
        dest.y = pos->y + offY;
        dest.z = pos->z + offZ;
        ufo->SetDestination(&dest);

        const Quaternion* a = planet->GetOrientation();
        const Quaternion* b = ufo->mSpatial.GetOrientation();
        ufo->mOrientation = QuatMul(*a, *b);
        ufo->PopToDestination();
        ufo->SetDestination(planet);
    }
    else
    {
        ufo->SetDestination(planet);
        Vector3 facing;
        Quaternion q;
        Quaternion* r = QuaternionFromFacingAndUp(&q, OrthogonalVector(&facing, &kUpAxisZ), &kUpAxisZ);
        ufo->mOrientation = *r;
        ufo->PopToDestination();
    }

    mpSpaceGame->Update();
    mpSpaceGame->ChaseFromPlanetToSolar();

    cModeObject* mode2 = App()->GetModeManager()->GetCurrentMode();
    if (mode2)
    {
        cHudCtl* ctl = (cHudCtl*)mode2->Query(0x303154cc);
        if (ctl)
            ctl->Apply(&camTarget, viewFlagB);
    }

    if (mpSpaceGame->mpActiveEffect)
        mpSpaceGame->mpActiveEffect->Stop(0);

    cSolarSystem* ss = star->GetSolarSystem();
    if (ss)
    {
        int n = (int)(ss->mPlanetsEnd - ss->mPlanetsBegin);
        for (int i = 0; i < n; i++)
        {
            cPlanet* p = ss->mPlanetsBegin[i];
            int kind = p->GetKind();
            if (kind != 0 && kind != 1 && p != GetActivePlanet() && !p->mpInfo->IsHidden())
                GetPlanetRegistry()->Show(p);
        }
    }

    unsigned __int64 elapsed = ((cSPTimer*)((char*)sInstance + 0xa8))->GetElapsedTime();
    if (elapsed > 144000000)
        GetAchievements()->AwardAchievement(0x256184b1);

    cStarList* list = SpaceGameGet()->mpStars;
    int count = (int)(list->mEnd - list->mBegin);
    cStar** buf;
    if (count != 0)
        buf = (cStar**)operator new[](count * 4, "Simulator", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    else
        buf = 0;
    cStar** bufEnd;
    uninitialized_copy_stars(&bufEnd, list->mBegin, list->mEnd, buf, bUpdateEmpire);

    if ((unsigned)(bufEnd - buf) >= 10)
    {
        int full = 0;
        for (cStar** it = buf; it != bufEnd; ++it)
        {
            int turrets = 0, buildings = 0;
            GetTurretAndBuildingCounts(*it, &turrets, &buildings);
            if (turrets + buildings >= GetTerraformTuning()->GetMaxBuildingsForT3Colony() * 3)
                full++;
        }
        if (full >= 10)
            GetAchievements()->AwardAchievement(0xfbe4dc0d);
    }

    cTutorial* tut = GetTutorial();
    if (tut->mpCurrent && tut->mpCurrent->mID == 0xf98be0b8)
    {
        tut->Close(0xf98be0b8, 1);
        GetPopup()->Refresh();
    }

    if (bUpdateEmpire)
        GetHudEmpire()->Update(GetPlayerEmpire()->GetID());

    NotifyActivePlanetRecord(GetActivePlanetRecord());
    mpSpaceGame->mFlags &= 0xfffffffe;
    MessageServer()->PostMessage(0x5e37a2c, 0, 0, 0);

    for (cStar** it = buf; it < bufEnd; ++it)
        if (*it)
            (*it)->Release();
    if (buf && ((int*)buf)[-1] != 0)
        operator delete[](buf);
}

// ---------------------------------------------------------------------------
// Pick-priority tables and space-mode shutdown.
// ---------------------------------------------------------------------------
#include <string.h>

struct PickPriority
{
    uint32_t mKey;          // interface id the picker looks for
    uint32_t mMode;         // pick mode it applies to
    int32_t  mPriority;     // lower runs first
    PickPriority(uint32_t key, uint32_t mode, int32_t priority)
        : mKey(key), mMode(mode), mPriority(priority) {}
};

// eastl::vector<PickPriority>: 12-byte elements, grown through DoInsertValue.
struct PickPriorityVec
{
    PickPriority* mpBegin;
    PickPriority* mpEnd;
    PickPriority* mpCapacity;

    PickPriorityVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}

    void DoInsertValue(PickPriority* pos, const PickPriority& value);       // 0x00b535d0 (ret 8)

    void push_back(const PickPriority& value)
    {
        PickPriority* end = mpEnd;
        if (end < mpCapacity)
        {
            mpEnd = end + 1;
            if (end != 0)
                *end = value;
        }
        else
        {
            DoInsertValue(end, value);
        }
    }

    ~PickPriorityVec()
    {
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
};

class cPickPriorityMgr
{
public:
    VIRT4(a) VIRT4(b) virtual void v20(); virtual void v24(); virtual void v28();
    virtual void SetList(PickPriorityVec* list, int mode);                 // +0x2c (ret 8)
};
cPickPriorityMgr* PickPriorityMgr();                                       // 0x00b3d240

// @ 0x00fddba0
void cAppModeSpace::SetDefaultPickPriority()
{
    PickPriorityVec list;
    list.push_back(PickPriority(0xb033b403, 1, 10));
    list.push_back(PickPriority(0x137e8e0, 1, 10));
    list.push_back(PickPriority(0xb033b403, 2, 20));
    list.push_back(PickPriority(0x137e8e0, 2, 20));
    list.push_back(PickPriority(0xe9cb8ba, 2, 40));
    list.push_back(PickPriority(0x436f315, 0, 30));
    list.push_back(PickPriority(0xe9cb8ba, 0, 30));
    list.push_back(PickPriority(0x175cdc9, 0, 30));
    list.push_back(PickPriority(0xce9f6639, 0, 30));
    list.push_back(PickPriority(0x3275872, 1, 100));
    list.push_back(PickPriority(0x44462a6, 1, 100));
    list.push_back(PickPriority(0x38cfb68, 0, 100));
    list.push_back(PickPriority(0x3275872, 2, 110));
    list.push_back(PickPriority(0x44462a6, 2, 110));
    PickPriorityMgr()->SetList(&list, 0);
}

// @ 0x00fddfa0
void FUN_00fddfa0()
{
    PickPriorityVec list;
    list.push_back(PickPriority(0xb033b403, 1, 10));
    list.push_back(PickPriority(0x137e8e0, 1, 10));
    list.push_back(PickPriority(0xb033b403, 2, 20));
    list.push_back(PickPriority(0x137e8e0, 2, 20));
    list.push_back(PickPriority(0xe9cb8ba, 1, 30));
    list.push_back(PickPriority(0xce9f6639, 0, 30));
    PickPriorityMgr()->SetList(&list, 0);
}

// ---- shutdown helpers ---------------------------------------------------------------------------------
void FUN_00e1dbd0();                                                       // 0x00e1dbd0
extern uint32_t g_cheatFlag;                                               // 0x015b732c

class cCheatManager
{
public:
    VIRT4(a) virtual void v10(); virtual void v14(); virtual void v18();
    virtual void SetFlag(uint32_t flag);                                   // +0x1c (ret 4)
};
cCheatManager* CheatManager();                                             // 0x0067de20

// The message server talks to the interface sub-object at +0x04 of the mode; the
// retail build null-checks the mode pointer for every conversion.
inline cModeBase* GetModeBase(cAppModeSpace* mode)
{
    return (mode != 0) ? &mode->mBase : 0;
}

// @ 0x00fde180
bool cAppModeSpace::Shutdown()
{
    FUN_00e1dbd0();
    mModels.clear();

    cMessageServer* server = MessageServer();
    if (server != 0)
    {
        server->Notify(GetModeBase(this), 0x1a0219e, 0xffffd8f1);
        server->Notify(GetModeBase(this), 0x3795725, 0xffffd8f1);
    }
    CheatManager()->SetFlag(g_cheatFlag);
    ShutdownSPG();
    return true;
}

// ---- planet record notification -----------------------------------------------------------------------
class cObjectTemplateDB
{
public:
    VIRT4(a) VIRT4(b) VIRT4(c) VIRT4(d) VIRT4(e) VIRT4(f)
    virtual void Unregister(void* entry);                                  // +0x60 (ret 4)
};
cObjectTemplateDB* ObjectTemplateDB();                                     // 0x0067cb40

class cBioElemSort
{
public:
    void* Func_bb9b80();                                                   // 0x00bb9b80
    int   Func_bb9ae0();                                                   // 0x00bb9ae0
    int   GetAvatar();                                                     // 0x00b1fdb0
};

class cStarManager
{
public:
    cEmpire* GetEmpireByID(int id);                                        // 0x00ba9370 (ret 4)
};
cStarManager* StarManager();                                               // 0x00b3d2a0

struct PlanetTemplateRef { uint32_t mKey; uint32_t mField04; uint32_t mField08; };
struct PlanetTemplateVec { PlanetTemplateRef* mpBegin; PlanetTemplateRef* mpEnd; };

struct cPlanetRecord
{
    char pad00[0xd0];
    PlanetTemplateRef* mTemplatesBegin;                                    // +0xd0
    PlanetTemplateRef* mTemplatesEnd;                                      // +0xd4
    char padD8[0x15c - 0xd8];
    PlanetTemplateVec** mExtraBegin;                                       // +0x15c
    PlanetTemplateVec** mExtraEnd;                                         // +0x160
    cBioElemSort* SortBanners();                                           // 0x00b8de30
};

// @ 0x00fde230
void NotifyActivePlanetRecord(void* record_)
{
    cPlanetRecord* record = (cPlanetRecord*)record_;

    int count = (int)(record->mTemplatesEnd - record->mTemplatesBegin);
    for (int i = 0; i < count; i++)
        ObjectTemplateDB()->Unregister(&record->mTemplatesBegin[i]);

    cBioElemSort* sort = record->SortBanners();

    void* key = sort->Func_bb9b80();
    if (*(int*)key != 0)
        ObjectTemplateDB()->Unregister(key);

    if (sort->Func_bb9ae0() == 5)
    {
        cEmpire* empire = StarManager()->GetEmpireByID(sort->GetAvatar());
        if (empire != 0)
            ObjectTemplateDB()->Unregister(empire->GetUFOKey());
    }

    int n = (int)(record->mExtraEnd - record->mExtraBegin);
    PlanetTemplateVec** buf = 0;
    if (n != 0)
        buf = (PlanetTemplateVec**)operator new[](n * 4, "Simulator", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    memcpy(buf, record->mExtraBegin, n * 4);

    int copied = n;
    for (int i = 0; i < copied; i++)
    {
        PlanetTemplateVec* v = buf[i];
        int m = (int)(v->mpEnd - v->mpBegin);
        for (int j = 0; j < m; j++)
        {
            PlanetTemplateRef* e = &v->mpBegin[j];
            if (e->mKey != 0 && e->mKey != 0xffffffff)
                ObjectTemplateDB()->Unregister(e);
        }
    }

    if (buf != 0 && ((int*)buf)[-1] != 0)
        operator delete[](buf);
}
