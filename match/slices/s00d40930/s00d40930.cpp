#include "types.h"

// ---------------------------------------------------------------------------
// Shared views over the retail game objects this slice touches. Every field is
// named; no raw-offset reads.
// ---------------------------------------------------------------------------

struct cVec3 {
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
};

// Creature/animal record walk in the game-data vector.
struct cHerdObj {
    uint8_t  mPad000[0x34];       // +0x000
    cVec3    mPosition;           // +0x034
    uint8_t  mPad040[0xa4 - 0x40];// +0x040
    uint32_t mProfileId;          // +0x0a4
    uint8_t  mPad0a8[0x120 - 0xa8];// +0x0a8
    int32_t  mRangeMin;           // +0x120
    int32_t  mRangeMax;           // +0x124
    uint8_t  mPad128[0x160 - 0x128];// +0x128
    void*    mNest;               // +0x160
    uint8_t  mPad164[0x1e8 - 0x164];// +0x164
    int32_t  mKind;               // +0x1e8
    uint8_t  mPad1ec[0x1f0 - 0x1ec];// +0x1ec
    int32_t  mField1F0;           // +0x1f0
    uint8_t  mPad1f4[0x218 - 0x1f4];// +0x1f4
    void*    mOwner;              // +0x218
};

// Avatar herd mirror returned by the avatar query helper.
struct cAvatarHerd {
    uint8_t  mPad000[0x40];       // +0x000
    void**   mHerdBegin;          // +0x040
    void**   mHerdEnd;            // +0x044
    void**   mHerdCap;            // +0x048
    uint8_t  mPad04c[0x54 - 0x4c];// +0x04c
    void**   mAnimalBegin;        // +0x054
    void**   mAnimalEnd;          // +0x058
    uint8_t  mPad05c[0x84 - 0x5c];// +0x05c
    uint8_t  mFlockFlag;          // +0x084
    uint8_t  mPad085[0x88 - 0x85];// +0x085
    uint32_t mField88;            // +0x088
    uint8_t  mPad08c[0x90 - 0x8c];// +0x08c
    void*    mField90;            // +0x090
    uint8_t  mPad094[0xf0 - 0x94];// +0x094
    uint32_t mFieldF0;            // +0x0f0
    uint8_t  mPad0f4[0x160 - 0xf4];// +0x0f4
    void*    mNest;               // +0x160
};

// One game-data record exposed by the game-data vector.
struct cGameDataVec {
    void**   mBegin;              // +0x04
    void**   mEnd;                // +0x08
};

// ---------------------------------------------------------------------------
// External helpers and globals (retail addresses in comments).
// ---------------------------------------------------------------------------
struct cGameNounManager {
    void* GetSelectedAnimal();                                   // 0x00989360
    void* GetAvatar();                                           // 0x00b1fdb0
    void* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, void* tag); // 0x00b21340
};
void*  NounManager();                                            // 0x00b3d300
void*  PlanetModel();                                            // 0x00b3d350
void*  GetTriggerMgr();                                          // 0x00b3d4d0
void   LoadCreatureGameplayTuning(uint32_t id, uint32_t tag);    // 0x00d3d870

void*  GetPosition(void* obj);                                   // 0x00c6acc0
void*  GetContinent(void* planet, const cVec3* pos);             // 0x00b88590
void*  GetSetting9();                                            // 0x00401090
void*  GetAvatarProfile(void* speciesMgr);                       // 0x004df420
void*  GetAvatarHerd(void* avatar);                              // 0x00c04590
int    GetDesiredAvatarHerd(uint8_t includeLoose);               // 0x00d40b40

extern int   gSelectedPlanetIndex;                               // DAT_0169e370
extern float gAvatarHerdPosX;                                    // DAT_0167ea30
extern float gAvatarHerdPosY;                                    // DAT_0167ea34
extern float gAvatarHerdPosZ;                                    // DAT_0167ea38

// ---------------------------------------------------------------------------
// 0x00d40b40  pick the herd/animals the avatar should be assigned to
// ---------------------------------------------------------------------------
// @ 0x00d40b40
int GetDesiredAvatarHerd(uint8_t includeLoose)
{
    cGameNounManager* nm = (cGameNounManager*)NounManager();
    cHerdObj* current = (cHerdObj*)nm->GetSelectedAnimal();
    PlanetModel();
    if (!includeLoose
        && gSelectedPlanetIndex >= current->mRangeMin
        && gSelectedPlanetIndex <= current->mRangeMax) {
        return (int)current;
    }

    void* myContinent = GetContinent(PlanetModel(), (const cVec3*)GetPosition(current));
    float best = 3.402823466e+38F;
    void* profile = GetAvatarProfile(GetSetting9());

    cGameNounManager* nm2 = (cGameNounManager*)NounManager();
    cGameDataVec* vec = (cGameDataVec*)nm2->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                                              (void*)0x00accc30, (void*)0x00b1e500,
                                                              (void*)0x01be418e);
    void** it = vec->mBegin;
    void** end = vec->mEnd;
    if (it == end) {
        return (int)current;
    }
    for (; it != end; it++) {
        cHerdObj* obj = (cHerdObj*)*it;
        if (obj->mProfileId != (uint32_t)profile || obj->mNest == 0) {
            continue;
        }
        if (gSelectedPlanetIndex < obj->mRangeMin || gSelectedPlanetIndex > obj->mRangeMax) {
            continue;
        }
        void* continent = GetContinent(PlanetModel(), (const cVec3*)GetPosition(obj));
        if ((int)myContinent != (int)continent) {
            continue;
        }
        const cVec3* pos = (const cVec3*)GetPosition(obj);
        float dx = gAvatarHerdPosX - pos->x;
        float dy = gAvatarHerdPosY - pos->y;
        float dz = gAvatarHerdPosZ - pos->z;
        float dist = dx * dx + dy * dy + dz * dz;
        if (dist < best) {
            current = obj;
            best = dist;
        }
    }
    return (int)current;
}

// ---------------------------------------------------------------------------
// 0x00d40e70  post the species-migrate trigger actions for the avatar
// ---------------------------------------------------------------------------
struct cSubTarget {
    virtual bool IsEligible();                                   // slot +0x58
};
struct cSubObj {
    uint8_t     mPad00[0xc0];                                    // +0x000
    cSubTarget* mTarget;                                         // +0x0c0
};

struct cActionTarget {
    cActionTarget(const void* pos, void* handle);                // 0x00ad7a30
    ~cActionTarget();                                            // 0x00ad7ad0
};

struct cTriggerMgr {
    void* PostTrigger(const char* name, int a, int b, int c, int d, int e); // 0x00ae0930
    void  PostAction(uint32_t id, cActionTarget* target);        // 0x00ae09b0
};

void* GetUIRoot();                                               // 0x00d51660
struct cDOMNode { void* GetParent(); };                          // 0x00ff0420

// @ 0x00d40e70
void FUN_00d40e70(void)
{
    cTriggerMgr* tm = (cTriggerMgr*)GetTriggerMgr();
    void* handle = tm->PostTrigger("CRG_SpeciesMigrate", 1, 1, 0, 0, 0);

    cGameNounManager* nm = (cGameNounManager*)NounManager();
    void* avatar = nm->GetAvatar();
    cAvatarHerd* herd = (cAvatarHerd*)GetAvatarHerd(avatar);

    void** end = herd->mAnimalEnd;
    for (void** it = herd->mAnimalBegin; it != end; it++) {
        cHerdObj* obj = (cHerdObj*)*it;
        if (obj->mOwner == 0) {
            continue;
        }
        cSubObj* sub = (cSubObj*)obj->mOwner;
        if (!sub->mTarget->IsEligible()) {
            continue;
        }
        if (obj->mKind != 5) {
            continue;
        }
        obj->mField1F0 = 0x7fffffff;
        if (obj->mOwner != avatar) {
            continue;
        }
        cActionTarget target((const void*)((char*)obj + 0x34), handle);
        tm->PostAction(0x28930a2c, &target);
    }

    cHerdObj* best = (cHerdObj*)GetDesiredAvatarHerd(1);

    void* posA = herd->mNest ? (char*)herd->mNest + 0x34 : 0;
    cActionTarget targetA(posA, handle);
    tm->PostAction(0x6049a108, &targetA);

    void* posB = best->mNest ? (char*)best->mNest + 0x34 : 0;
    cActionTarget targetB(posB, handle);
    tm->PostAction(0x9667d819, &targetB);

    cDOMNode* node = (cDOMNode*)GetUIRoot();
    void* parent = node->GetParent();
    void* posC = parent ? (char*)parent + 0xc0 : 0;
    cActionTarget targetC(posC, handle);
    ((cTriggerMgr*)GetTriggerMgr())->PostAction(0x927b68d9, &targetC);
}

// 0x00d414e0  pick the creature AI tuning record for a tuning id
// @ 0x00d414e0
void __stdcall FUN_00d414e0(uint32_t tuningId)
{
    switch (tuningId - 0x01654c01) {
    case 0: LoadCreatureGameplayTuning(0xad56080c, 0x7c340397); return;
    case 1: LoadCreatureGameplayTuning(0x00000000, 0x7c340397); return;
    case 2: LoadCreatureGameplayTuning(0x02ae0c7e, 0x7c340397); return;
    case 3: LoadCreatureGameplayTuning(0xf71fa311, 0x7c340397); return;
    case 4: return;
    }
}
