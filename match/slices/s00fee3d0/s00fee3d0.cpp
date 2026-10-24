// Slice s00fee3d0: SP::cSPMissionManager mission selection / generation.
// Retail build (MSVC 2008 SP1). Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

// ------------------------------------------------------------ free helpers ---
void* NounManager();                                                    // 0x00b3d300
void* FUN_01021300();                                                   // 0x01021300
void* SpaceGameGet();                                                   // 0x01002bd0
void* RelationshipManager();                                            // 0x00b3d2c0
void* GetSpaceRelationshipTuning();                                     // 0x010407c0
void* FUN_00b3d2a0();                                                   // 0x00b3d2a0
int   FUN_00fec010(void* weights);                                      // 0x00fec010
void  operator_delete_array(void* p);                                   // 0x00f47380

// --------------------------------------------------------------- data types -----
struct cSPMission;

// cGameDataList<T>: 4-byte header then the item SpVector at +0x04.
struct SpVecPV {
    void** mpBegin;                     // +0x00
    void** mpEnd;                       // +0x04
    void** mpCap;                       // +0x08
};

struct MissionList {
    unsigned mPad00;                    // +0x00
    SpVecPV  mItems;                    // +0x04 <-- returned list's vector
};

struct cGameNounManager {
    MissionList* GetGameDataVector(unsigned a, unsigned b, unsigned c, unsigned d, int e); // 0x00b21340
    char* GetCurrentTerrainSphere();                                            // 0x00f67d90
};

struct RelMgr     { float calc(unsigned a, unsigned b, int c); };   // 0x00d00a10
struct RelTuning  { float get(); };                                 // 0x01040860
struct StarMgr    { void  PickRandomAsset(void** out, int flag); }; // 0x00bb7940
struct InsertVec  { char  FUN_00fe4180(unsigned key); };            // 0x00fe4180
struct cMissionHelper { void FUN_00c4b240(void* asset); };         // 0x00c4b240

struct TerrainSphere {
    char FUN_00c75d70(void* empire, void** out);      // 0x00c75d70
    char FUN_00c772c0(unsigned flag);                 // 0x00c772c0
};

struct cModel { char mPad00[0x13c]; void* mPlanet; };   // planet pointer at +0x13c

struct cEmpire {
    char     mPad00[0x58];                    // +0x000
    int      mArchetype;                      // +0x058
    char     mPad5c[0x84 - 0x5c];             // +0x05c
    unsigned mEmpireID;                       // +0x084
    void*  GetHomePlanet();                   // 0x00c31730
    int    GetWeaponryLevel();                // 0x00c317a0
    char   FUN_00c31bc0(cEmpire* other);      // 0x00c31bc0
};

// Virtual slots of cSPMission are reached through __thiscall pointers taken
// straight from the vftable: +0x060 -> int state, +0x114 -> void draw,
// +0x134 -> char conversation(empire, planet).
struct cSPMission {
    unsigned GetMissionID();                  // 0x01030e10
    void*    GetOwnerEmpire();                // 0x00c451e0
    cModel*  GetModel();                      // 0x00c45ce0
    void*    GetTargetPlanet();               // 0x00970b30
    char     IsActive();                      // 0x00c44c80
};

// 0x38-byte mission requisite record held in the three requisition lists.
struct Req38 {
    unsigned  mMissionID;             // +0x00
    unsigned  mPad04;                 // +0x04
    unsigned* mpVec;                  // +0x08  (begin)
    unsigned* mpVecEnd;               // +0x0c
    char      mPad10[0x30 - 0x10];    // +0x10
    unsigned  mFlags30;               // +0x30
    unsigned  mFlags34;               // +0x34
};

// eastl rbtree node (key unsigned, mapped unsigned).
struct MapNode {
    MapNode* mpNodeRight;             // +0x00
    MapNode* mpNodeLeft;              // +0x04
    MapNode* mpNodeParent;            // +0x08
    int      mColor;                  // +0x0c
    unsigned mKey;                    // +0x10
    unsigned mValue;                  // +0x14
};

// rbtree header: 4 bytes of padding then the anchor node at +0x04.
struct MissionStateMap {
    unsigned mPad00;                  // +0x00
    MapNode  mAnchor;                 // +0x04

    MapNode* findNode(const unsigned& key) const
    {
        MapNode* anchor = (MapNode*)&mAnchor;
        MapNode* lower = anchor;
        MapNode* cur = mAnchor.mpNodeParent;
        while (cur != 0) {
            if (cur->mKey >= key) {
                lower = cur;
                cur = cur->mpNodeLeft;
            } else {
                cur = cur->mpNodeRight;
            }
        }
        if (lower == anchor || key < lower->mKey) {
            lower = anchor;
        }
        return lower;
    }

    MapNode** find(MapNode** result, const unsigned* key) const;   // 0x00e5c780
};

// sp_vector<float, sp_vector_allocator>
struct SpVectorF {
    float* mpBegin;                   // +0x00
    float* mpEnd;                     // +0x04
    float* mpCap;                     // +0x08
    void   resize(int n);             // 0x004afc80
};

struct cGameData {
    char        mPad00[0x70];         // +0x000
    InsertVec*  mOwner;               // +0x070
    InsertVec*  SetGameDataOwner2();  // 0x00bfc5f0
};

struct cSPMissionManager {
    char  mPad00[0x14];               // +0x000
    bool  mDebugDraw;                 // +0x014
    char  mPad15[0x1c - 0x15];        // +0x015
    unsigned* mForcedMission;         // +0x01c
    Req38* mTutBegin;                 // +0x020
    Req38* mTutEnd;                   // +0x024
    char  mPad28[0x34 - 0x28];        // +0x028
    Req38* mNpcBegin;                 // +0x034
    Req38* mNpcEnd;                   // +0x038
    char  mPad3c[0x48 - 0x3c];        // +0x03c
    Req38* mColBegin;                 // +0x048
    Req38* mColEnd;                   // +0x04c
    char  mPad50[0x5c - 0x50];        // +0x050
    MissionStateMap mStates;          // +0x05c
    char  mPad78[0xe0 - 0x78];        // +0x078
    unsigned mMaxMissions;            // +0x0e0
    char  mPadE4[0xec - 0xe4];        // +0x0e4
    int   mWeaponryThreshold;         // +0x0ec
    char  mPadF0[0x108 - 0xf0];       // +0x0f0
    unsigned* mVec108;                // +0x108
    unsigned* mVec10c;                // +0x10c
    char  mPad110[0x11c - 0x110];     // +0x110
    unsigned* mVec11c;                // +0x11c
    unsigned* mVec120;                // +0x120
    char  mPad124[0x130 - 0x124];     // +0x124
    unsigned* mVec130;                // +0x130
    unsigned* mVec134;                // +0x134

    unsigned    GetNumNonEventMissions(int flag);                       // 0x00fedd80
    cSPMission* CreateMissionFromID(unsigned id, void* planet, void* empire, int flags); // 0x00fec590
    char  FUN_00fec900(void* planet);                                   // 0x00fec900
    char  FUN_00fec8a0(void* planet);                                   // 0x00fec8a0
    char  FUN_00fecbf0();                                               // 0x00fecbf0
    char  FUN_00febd30(int index);                                      // 0x00febd30
    int   GetMissionWeightForColony(unsigned id);                       // 0x00fed430
    int   GetMissionWeightForEmpire(unsigned id, void* empire);         // 0x00fed640
    float FUN_00fedfe0(unsigned id);                                    // 0x00fedfe0
    float FUN_00fedf20(unsigned id);                                    // 0x00fedf20
    char  IsNPCMissionAvailable(void* empire, int index);               // 0x00febc90

    char  FUN_00fee3d0(void* empire, void* planet);
    cSPMission* GetMissionByID(int id);
    cSPMission* GetActiveMissionForEmpireAndPlanet(void* empire, void* planet);
    char  IsPlanetARaidTarget(void* planet, unsigned* out);
    int   HasMissionConversationWithEmpireAndPlanet(void* empire, void* planet);
    char  FUN_00fee730(void* empire, void* planet);
    char  FUN_00fee820();
    void  DebugDraw();
    char  FUN_00fee930(int id);
    unsigned GetNextAvailableTutorialMission();
    char  FUN_00feebb0();
    char  FUN_00feec30();
    char  FUN_00feecb0();
    unsigned FUN_00feed30(void* empire, void* planet);
};

// --------------------------------------------------------------- methods -----
// @ 0x00fee3d0
char cSPMissionManager::FUN_00fee3d0(void* empire, void* planet)
{
    cEmpire* player = (cEmpire*)FUN_01021300();
    void* home = player->GetHomePlanet();
    unsigned count = GetNumNonEventMissions(0);
    if (empire == player) {
        if (planet == home) {
            return 1;
        }
        if (count < mMaxMissions && FUN_00fec900(planet)) {
            return 1;
        }
    } else if (count < mMaxMissions && FUN_00fec8a0(planet)) {
        unsigned playerID = ((cEmpire*)FUN_01021300())->mEmpireID;
        unsigned empireID = ((cEmpire*)empire)->mEmpireID;
        RelMgr* rel = (RelMgr*)RelationshipManager();
        float damage = rel->calc(empireID, playerID, 0);
        float tuning = ((RelTuning*)GetSpaceRelationshipTuning())->get();
        if (tuning > damage) {
            return 0;
        }
        return 1;
    }
    return 0;
}

// @ 0x00fee480
cSPMission* cSPMissionManager::GetMissionByID(int id)
{
    cGameNounManager* nm = (cGameNounManager*)NounManager();
    MissionList* list = nm->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00fed010, 0x00b1e520, 0x2aa5ada);
    SpVecPV& v = list->mItems;
    void** p = v.mpBegin;
    void** end = v.mpEnd;
    for (; p != end; ++p) {
        cSPMission* m = (cSPMission*)*p;
        if (m != 0 && m->GetMissionID() == (unsigned)id) {
            return m;
        }
        }
    return 0;
}

// @ 0x00fee4f0
cSPMission* cSPMissionManager::GetActiveMissionForEmpireAndPlanet(void* empire, void* planet)
{
    cGameNounManager* nm = (cGameNounManager*)NounManager();
    MissionList* list = nm->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00fed010, 0x00b1e520, 0x2aa5ada);
    SpVecPV& v = list->mItems;
    void** p = v.mpBegin;
    void** end = v.mpEnd;
    for (; p != end; ++p) {
        cSPMission* m = (cSPMission*)*p;
        if (m != 0 && m->GetOwnerEmpire() == empire
            && (planet == 0 || m->GetModel()->mPlanet == planet)) {
            switch (((int (__thiscall*)(void*))((*(void***)m))[0x60 / 4])(m)) {
            case 3:
            case 5:
                return m;
            }
        }
        }
    return 0;
}

// @ 0x00fee590
char cSPMissionManager::IsPlanetARaidTarget(void* planet, unsigned* out)
{
    cGameNounManager* nm = (cGameNounManager*)NounManager();
    MissionList* list = nm->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00fed010, 0x00b1e520, 0x2aa5ada);
    SpVecPV& v = list->mItems;
    void** p = v.mpBegin;
    void** end = v.mpEnd;
    for (; p != end; ++p) {
        cSPMission* m = (cSPMission*)*p;
        if (m != 0
            && m->GetTargetPlanet() != 0
            && ((cModel*)m->GetTargetPlanet())->mPlanet == planet
            && ((int (__thiscall*)(void*))((*(void***)m))[0x60 / 4])(m) == 3
            && (m->GetMissionID() == 0xa4b0a2df
                || m->GetMissionID() == 0xbbae6b99
                || m->GetMissionID() == 0xc4956aa7
                || m->GetMissionID() == 0xd646c543
                || m->GetMissionID() == 0x25089345
                || m->GetMissionID() == 0x56afe39d)) {
            if (m->GetOwnerEmpire() != 0) {
                *out = ((cEmpire*)m->GetOwnerEmpire())->mEmpireID;
                return 1;
            }
            *out = 0xffffffff;
            return 1;
        }
        }
    return 0;
}

// @ 0x00fee6b0
int cSPMissionManager::HasMissionConversationWithEmpireAndPlanet(void* empire, void* planet)
{
    cGameNounManager* nm = (cGameNounManager*)NounManager();
    MissionList* list = nm->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00fed010, 0x00b1e520, 0x2aa5ada);
    SpVecPV& v = list->mItems;
    void** p = v.mpBegin;
    void** end = v.mpEnd;
    for (; p != end; ++p) {
        cSPMission* m = (cSPMission*)*p;
        if (m != 0 && ((char (__thiscall*)(void*, void*, void*))((*(void***)m))[0x134 / 4])(m, empire, planet)) {
            return 1;
        }
        }
    return 0;
}

// @ 0x00fee730
char cSPMissionManager::FUN_00fee730(void* empire, void* planet)
{
    if (GetActiveMissionForEmpireAndPlanet(empire, planet) != 0) {
        return 0;
    }
    cEmpire* player = (cEmpire*)FUN_01021300();
    if (!player->FUN_00c31bc0((cEmpire*)empire)) {
        return 0;
    }
    if (((cEmpire*)empire)->GetWeaponryLevel() < mWeaponryThreshold - 1) {
        return 0;
    }
    int theirs = ((cEmpire*)empire)->mArchetype;
    switch (player->mArchetype) {
    case 9:
        if (theirs == 0 || theirs == 9 || theirs == 0x12) return 0;
        break;
    case 10:
        if (theirs == 1 || theirs == 0x0a) return 0;
        break;
    case 11:
        if (theirs == 2 || theirs == 0x0b) return 0;
        break;
    case 12:
        if (theirs == 3 || theirs == 0x0c) return 0;
        break;
    case 13:
        if (theirs == 4 || theirs == 0x0d) return 0;
        break;
    case 14:
        if (theirs == 5 || theirs == 0x0e) return 0;
        break;
    case 15:
        if (theirs == 6 || theirs == 0x0f || theirs == 0x11) return 0;
        break;
    case 16:
        if (theirs == 7 || theirs == 0x10) return 0;
        break;
    }
    return 1;
}

// @ 0x00fee820
char cSPMissionManager::FUN_00fee820()
{
    cGameNounManager* nm = (cGameNounManager*)NounManager();
    MissionList* list = nm->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00fed010, 0x00b1e520, 0x2aa5ada);
    SpVecPV& v = list->mItems;
    void** p = v.mpBegin;
    void** end = v.mpEnd;
    for (; p != end; ++p) {
        cSPMission* m = (cSPMission*)*p;
        unsigned id = m->GetMissionID();
        if (m != 0 && m->IsActive()
            && (id == 0x29e235c0
                || id == 0x34ca76bf
                || id == 0x0b9656f6
                || id == 0x4b708009
                || id == 0xc052cccf
                || id == 0x2b795e0d
                || id == 0x5d182075
                || id == 0xf46a1fc4)) {
            return 1;
        }
        }
    return 0;
}

// @ 0x00fee8d0
void cSPMissionManager::DebugDraw()
{
    if (!mDebugDraw) {
        return;
    }
    cGameNounManager* nm = (cGameNounManager*)NounManager();
    MissionList* list = nm->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00fed010, 0x00b1e520, 0x2aa5ada);
    SpVecPV& v = list->mItems;
    void** p = v.mpBegin;
    void** end = v.mpEnd;
    for (; p != end; ++p) {
        cSPMission* m = (cSPMission*)*p;
        if (m != 0) {
            ((void (__thiscall*)(void*))((*(void***)m))[0x114 / 4])(m);
        }
        }
}

// @ 0x00fee930
char cSPMissionManager::FUN_00fee930(int id)
{
    MapNode* slot;
    MapNode* node = *mStates.find(&slot, (const unsigned*)&id);
    if (node != &mStates.mAnchor) {
        if (node->mValue == 2 || node->mValue == 3) {
            return 1;
        }
    }
    char ok;
    switch (id) {
    case -0x1c0a6b1f: {                       // 0xe3f594e1
        cSPMission* m = GetMissionByID(id);
        if (m != 0 && m->IsActive()) {
            return 0;
        }
        TerrainSphere* ts = (TerrainSphere*)((cGameNounManager*)NounManager())->GetCurrentTerrainSphere();
        ok = ts->FUN_00c772c0(0x4ac8010);
        break;
    }
    case -0x6951388c: {                       // 0x96aec774
        cSPMission* m = GetMissionByID(id);
        if (m != 0 && m->IsActive()) {
            return 0;
        }
        ok = ((cGameData*)SpaceGameGet())->SetGameDataOwner2()->FUN_00fe4180(0x3ae13c90);
        break;
    }
    case -0x69513889: {                       // 0x96aec777
        cSPMission* m = GetMissionByID(id);
        if (m != 0 && m->IsActive()) {
            return 0;
        }
        ok = ((cGameData*)SpaceGameGet())->SetGameDataOwner2()->FUN_00fe4180(0x3ae13c93);
        break;
    }
    case 0x62613a1d: {
        cSPMission* m = GetMissionByID(id);
        if (m != 0 && m->IsActive()) {
            return 0;
        }
        ok = ((cGameData*)SpaceGameGet())->SetGameDataOwner2()->FUN_00fe4180(0x372e73ee);
        break;
    }
    default:
        return 0;
    }
    if (ok) {
        return 1;
    }
    return 0;
}

// @ 0x00feea60
unsigned cSPMissionManager::GetNextAvailableTutorialMission()
{
    unsigned flag = 0;
    char* ts = ((cGameNounManager*)NounManager())->GetCurrentTerrainSphere();
    if (ts != 0 && ((TerrainSphere*)ts)->FUN_00c772c0(0x4ac8010)) {
        flag = 1;
    }
    Req38* begin = mTutBegin;
    int count = (int)(mTutEnd - begin);
    if (count <= 0) {
        return 0xffffffff;
    }
    int offset = 0;
    for (int i = 0; i < count; i++, offset += 0x38) {
        Req38* req = (Req38*)((char*)begin + offset);
        unsigned key = req->mMissionID;
        MapNode* node = mStates.findNode(key);
        if (node != &mStates.mAnchor && node->mValue == 1) {
            continue;
        }
        if (FUN_00fee930((int)key)) {
            continue;
        }
        int n = (int)(req->mpVecEnd - req->mpVec);
        bool allIn = true;
        for (int j = 0; j < n; j++) {
            if (!((cGameData*)SpaceGameGet())->SetGameDataOwner2()->FUN_00fe4180(req->mpVec[j])) {
                allIn = false;
                break;
            }
        }
        if (req->mFlags30 == (req->mFlags30 & flag) && (req->mFlags34 & flag) == 0) {
            if (!allIn) {
                return 0xffffffff;
            }
            return req->mMissionID;
        }
    }
    return 0xffffffff;
}

// @ 0x00feebb0
char cSPMissionManager::FUN_00feebb0()
{
    int count = (int)(mVec134 - mVec130);
    for (int i = 0; i < count; i++) {
        unsigned key = mVec130[i];
        MapNode* node = mStates.findNode(key);
        if (node != &mStates.mAnchor && node->mValue == 1) {
            continue;
        }
        if (!FUN_00fee930((int)key)) {
            return 1;
        }
    }
    return 0;
}

// @ 0x00feec30
char cSPMissionManager::FUN_00feec30()
{
    int count = (int)(mVec120 - mVec11c);
    for (int i = 0; i < count; i++) {
        unsigned key = mVec11c[i];
        MapNode* node = mStates.findNode(key);
        if (node != &mStates.mAnchor && node->mValue == 1) {
            continue;
        }
        if (!FUN_00fee930((int)key)) {
            return 1;
        }
    }
    return 0;
}

// @ 0x00feecb0
char cSPMissionManager::FUN_00feecb0()
{
    int count = (int)(mVec10c - mVec108);
    for (int i = 0; i < count; i++) {
        unsigned key = mVec108[i];
        MapNode* node = mStates.findNode(key);
        if (node != &mStates.mAnchor && node->mValue == 1) {
            continue;
        }
        if (!FUN_00fee930((int)key)) {
            return 1;
        }
    }
    return 0;
}

// @ 0x00feed30
unsigned cSPMissionManager::FUN_00feed30(void* empire, void* planet)
{
    if (!FUN_00fee3d0(empire, planet)) {
        return 0;
    }
    cEmpire* player = (cEmpire*)FUN_01021300();
    void* home = player->GetHomePlanet();
    unsigned result = 0;
    SpVectorF weights;

    if (empire == player) {
        if (planet == home) {
            unsigned id = GetNextAvailableTutorialMission();
            if (mForcedMission != 0) {
                id = (unsigned)mForcedMission;
            }
            result = (unsigned)CreateMissionFromID(id, planet, empire, 0);
            mForcedMission = 0;
            return result;
        }
        int count = (int)(mColEnd - mColBegin);
        weights.mpBegin = 0;
        weights.mpEnd = 0;
        weights.mpCap = 0;
        weights.resize(count);
        for (int i = 0; i < count; i++) {
            Req38* req = &mColBegin[i];
            float value = 0.0f;
            if (FUN_00febd30(i)) {
                int w = GetMissionWeightForColony(req->mMissionID);
                float wf = (float)w;
                value = FUN_00fedfe0(req->mMissionID) * wf;
            }
            weights.mpBegin[i] = value;
        }
        bool done = false;
        do {
            int idx = FUN_00fec010(&weights);
            if (idx < 0 || idx >= count) {
                break;
            }
            unsigned id = mColBegin[idx].mMissionID;
            if (mForcedMission != 0) {
                id = (unsigned)mForcedMission;
            }
            result = (unsigned)CreateMissionFromID(id, planet, empire, 0);
            if (result == 0) {
                for (int i = 0; i < count; i++) {
                    if (mColBegin[i].mMissionID == id) {
                        weights.mpBegin[i] = 0.0f;
                    }
                }
            } else {
                done = true;
            }
            mForcedMission = 0;
        } while (!done);
    } else {
        if (FUN_00fecbf0()) {
            unsigned key = 0x2ab57fac;
            MapNode* slot;
            MapNode* node = *mStates.find(&slot, &key);
            if (node == &mStates.mAnchor || (node->mValue != 2 && node->mValue != 3)) {
                result = (unsigned)CreateMissionFromID(0x2ab57fac, planet, empire, 0);
                if (result != 0) {
                    goto cleanup;
                }
            }
            char* ts = ((cGameNounManager*)NounManager())->GetCurrentTerrainSphere();
            void* out = 0;
            if (((TerrainSphere*)ts)->FUN_00c75d70(empire, &out)) {
                result = (unsigned)CreateMissionFromID((unsigned)out, planet, empire, 0);
                if (result != 0) {
                    goto cleanup;
                }
            }
        }
        int count = (int)(mNpcEnd - mNpcBegin);
        weights.mpBegin = 0;
        weights.mpEnd = 0;
        weights.mpCap = 0;
        weights.resize(count);
        for (int i = 0; i < count; i++) {
            Req38* req = &mNpcBegin[i];
            float value = 0.0f;
            if (IsNPCMissionAvailable(empire, i)) {
                int w = GetMissionWeightForEmpire(req->mMissionID, empire);
                float wf = (float)w;
                value = FUN_00fedf20(req->mMissionID) * wf;
            }
            weights.mpBegin[i] = value;
        }
        bool done = false;
        do {
            int idx = FUN_00fec010(&weights);
            if (idx < 0 || idx >= count) {
                break;
            }
            unsigned id = mNpcBegin[idx].mMissionID;
            if (mForcedMission != 0) {
                id = (unsigned)mForcedMission;
            }
            if (id == 0x9bd15777) {
                if (FUN_00fecbf0()) {
                    void* asset = 0;
                    StarMgr* star = (StarMgr*)FUN_00b3d2a0();
                    star->PickRandomAsset(&asset, 1);
                    if (asset != 0) {
                        result = (unsigned)CreateMissionFromID(0x831e4599, planet, empire, 0);
                        if (result != 0) {
                            ((cMissionHelper*)result)->FUN_00c4b240(asset);
                        }
                    }
                }
            } else {
                result = (unsigned)CreateMissionFromID(id, planet, empire, 0);
            }
            if (result != 0) {
                done = true;
            } else {
                for (int i = 0; i < count; i++) {
                    if (mNpcBegin[i].mMissionID == id) {
                        weights.mpBegin[i] = 0.0f;
                    }
                }
            }
            mForcedMission = 0;
        } while (!done);
    }
cleanup:
    if (weights.mpBegin != 0 && ((unsigned*)weights.mpBegin)[-1] != 0) {
        operator_delete_array(weights.mpBegin);
    }
    return result;
}