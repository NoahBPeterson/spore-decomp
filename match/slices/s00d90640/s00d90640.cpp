// Slice s00d90640 -- a contiguous block of SP::CitizenTree behavior-tree callbacks
// (0x00d90640 .. 0x00d91510, 40 functions). Reconstructed from the retail disassembly.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#define PVN(n) virtual void pv##n();

// ---------------------------------------------------------------------------------------------
// small shared types

struct Vec3 { float x, y, z; };

namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t limit);       // 0x00a68fb0
};
}}
extern EA::Random::RandomLinearCongruential sMathRandom;  // 0x01601760

namespace nSPBehaviorTree {
struct behavior_stimuli {
    int   Play(int a, int b);                           // 0x00bc96a0
    void  ClearAll(int a, int b);                       // 0x00bc98f0
    void* GetAny();                                     // 0x00d997e0
};
}

// a stimulus slot filled in by the tick callbacks: pointer lands at +4
struct StimulusSlot { uint32_t mId; void* mpTarget; };

// iterator entry: the object pointer lives at +8
struct IterEntry { uint8_t pad0[8]; void* mpObject; };

// auxiliary geometry returned through vtable+0x68 (floats at +8 and +0x14)
struct AuxGeom { uint8_t pad00[8]; float f08; uint8_t pad0c[8]; float f14; };

// out-struct written by the activate/tick callbacks
struct BehaviorStateOut {
    int      m00;                                       // +0x00
    float    mf04;                                      // +0x04
    int      m08;                                       // +0x08
    float    mf0C;                                      // +0x0c
    uint8_t  m10;                                       // +0x10
    uint8_t  mPad11[3];
    float    mf14;                                      // +0x14
    uint8_t  m18;                                       // +0x18
};

// per-callback persistent state blocks
struct TickState  { int mMode; float mf4; };            // +0x00 / +0x04
struct AdmireState { char mFlag; uint8_t pad0[3]; int mCount; };     // +0x00 / +0x04
struct RubbleState { char mFlag; uint8_t pad0[3]; int mId; int mAnim; };  // +0x00 / +0x04 / +0x08

// ---------------------------------------------------------------------------------------------
// behavior-tree sub-objects (non-virtual members, dispatched with `this` in ecx)

class cActionCircle {                                   // 0x00afae50 / 0x00d5c470 / 0x00d5c580
public:
    void RemoveAgent(void* agent);                      // 0x00afae50
};

class cAgentPos {                                       // 0x00afad70
public:
    int CheckPosition(Vec3* pos);                       // 0x00afad70
};

class cBehaviorAgent {                                  // the object at cSPCreatureCitizen+0xfb8
public:
    uint8_t       mPad000[0x70];                        // +0x000
    cActionCircle mCircle070;                           // +0x070
    uint8_t       mPad071[0xd4 - 0x71];                 // +0x071 .. +0x0d3
    cAgentPos     mPos;                                 // +0x0d4
    uint8_t       mPad0D5[0x1a8 - 0xd5];                // +0x0d5 .. +0x1a7
    int           mn1A8;                                // +0x1a8
    int           mn1AC;                                // +0x1ac
    uint8_t       mPad1B0[0x1bc - 0x1b0];               // +0x1b0 .. +0x1bb
    cActionCircle mCircle1BC;                           // +0x1bc
    uint8_t       mPad1BD[0x1c8 - 0x1bd];               // +0x1bd .. +0x1c7
    uint32_t      mn1C8;                                // +0x1c8
    uint8_t       mPad1CC[0xa28 - 0x1cc];               // +0x1cc .. +0xa27
    int           mnA28;                                // +0xa28
    int           mUnkA2C;                              // +0xa2c
    int           mnA30;                                // +0xa30
    int           mUnkA34;                              // +0xa34
    int           mnA38;                                // +0xa38
    int           mUnkA3C;                              // +0xa3c
    int           mUnkA40;                              // +0xa40
    int           mnA44;                                // +0xa44
    uint8_t       mUnkA48[8];                           // +0xa48 .. +0xa4f
    uint8_t       mbA50;                                // +0xa50

    int* GetCounter(uint32_t idx);                      // 0x00d576b0
    void EnterZone(void* p, int b);                     // 0x00d5c470
    void ExitZone(void* p);                             // 0x00d5c580
};

// the behavior-stimuli owner at cSPCreatureCitizen+0xb4c
class cBehaviorStimuliOwner {
public:
    uint8_t  mPad000[8];                                // +0x00
    nSPBehaviorTree::behavior_stimuli mStimuli;         // +0x08
    uint8_t  mPadStim[0x1c8 - 9];                       // +0x09 .. +0x1c7
    uint32_t mn1C8;                                     // +0x1c8
};

// ---------------------------------------------------------------------------------------------
// object model

class cLocomotiveObject {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    virtual Vec3* GetPosition();                        // +0x2c
    PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21)
    PVN(22) PVN(23) PVN(24) PVN(25)
    virtual void* GetAux68();                           // +0x68
    uint8_t mPad04[0x5c];                               // +0x04 .. +0x5f (size 0x60)
    char IsNearGoal();                                  // 0x00c42e20
};

class cGameObject {
public:
    PVN(0) PVN(1) PVN(2)
    virtual void* GetChild0c();                         // +0x0c
    PVN(4) PVN(5) PVN(6) PVN(7)
    virtual int   GetType20();                          // +0x20
    PVN(9) PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18)
    virtual int   GetIdentity4c();                      // +0x4c
    PVN(20) PVN(21) PVN(22) PVN(23) PVN(24) PVN(25)
    virtual void* GetModel68();                         // +0x68
    uint8_t mPad04[0x30];                               // +0x04 .. +0x33
    cLocomotiveObject mLoco34;                          // +0x34 (size 0x60)
    uint8_t mPad94[0x508 - 0x94];                       // +0x94 .. +0x507
    uint8_t mStimulus508;                               // +0x508 (target registered as a stimulus)
};

class cCombatant {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4)
    PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10) PVN(11) PVN(12) PVN(13) PVN(14)
    PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21)
    virtual float GetMaxHealth();                       // +0x58
    uint8_t mPad04[0x11];                               // +0x04
    char    mb15;                                       // +0x15
    uint8_t mPad16[0x22];                               // +0x16 .. +0x37
    float   mfHealth38;                                 // +0x38
    uint8_t mPad3c[4];                                  // +0x3c .. +0x3f (size 0x40)
    int GetDamageState();                               // 0x008e7f80
};

class cCommunity {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    PVN(21)
    virtual float GetCap58();                           // +0x58
    uint8_t mPad04[0x34];                               // +0x04 .. +0x37 (size 0x38)
    void EnsureTimer(void* agent);                      // 0x00bfddc0
};

class cCityVisualizer {
public:
    PVN(0)
    void StartSpecialVignette(void* spec, void* pCitizen);   // 0x00d5f4d0
};

class cCity {
public:
    PVN(0)
    uint8_t mPad04[0x2d0 - 0x04];                       // +0x04 .. +0x2cf
    int     mn2D0;                                      // +0x2d0
    int  GetVehicleSpecialty();                         // 0x00bd81d0
    int  FUN_00bd8190();                                // 0x00bd8190
    void FUN_00bd8170(int v);                           // 0x00bd8170
};

class cPlanetModel {
public:
    PVN(0)
    void DirectionToSurfacePosition(Vec3& out, Vec3* dir);   // 0x00b815a0
};

class cGameNounManager {
public:
    PVN(0)
    int* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, void* key);   // 0x00b21340
};

class cSPCreatureCitizen {
public:
    // ---- vtable ----
    PVN(0)  PVN(1)  PVN(2)  PVN(3)  PVN(4)  PVN(5)  PVN(6)  PVN(7)  PVN(8)  PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18)
    virtual int   GetIdentity();                        // +0x4c
    PVN(20) PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29)
    PVN(30) PVN(31) PVN(32) PVN(33) PVN(34)
    virtual void  Flag8c();                             // +0x8c
    PVN(36) PVN(37)
    virtual int   GetMode98();                          // +0x98
    virtual void  SetMode9c(int);                       // +0x9c
    PVN(40) PVN(41) PVN(42) PVN(43) PVN(44) PVN(45) PVN(46) PVN(47) PVN(48) PVN(49)
    virtual void  FlagC8(int);                          // +0xc8

    // ---- data ----
    uint8_t  mPad04[0xbc];                              // +0x04 .. +0xbf
    cLocomotiveObject mLoco;                            // +0xc0 (size 0x60)
    cCombatant mCombatant;                              // +0x120 (size 0x40)
    uint8_t  mPad160[0x448];                            // +0x160 .. +0x5a7
    cCommunity mCommunity;                              // +0x5a8 (size 0x38)
    float    mf5E0;                                     // +0x5e0
    uint8_t  mPad5e4[0x568];                            // +0x5e4 .. +0xb4b
    cBehaviorStimuliOwner* mpB4C;                       // +0xb4c
    uint8_t  mPadB50[0x440];                            // +0xb50 .. +0xf8f
    char     mbF90;                                     // +0xf90
    uint8_t  mPadF91[0x27];                             // +0xf91 .. +0xfb7
    cBehaviorAgent* mpFB8;                              // +0xfb8
    char     mbFBC;                                     // +0xfbc
    uint8_t  mPadFBD[3];                                // +0xfbd .. +0xfbf
    int      mnFC0;                                     // +0xfc0
    uint8_t  mPadFC4[0x2c];                             // +0xfc4 .. +0xfef
    int      mnFF0;                                     // +0xff0
    uint8_t  mPadFF4[0x418];                            // +0xff4 .. +0x140b
    void*    mp140C;                                    // +0x140c  iterator begin
    void*    mp1410;                                    // +0x1410  iterator end

    // ---- helpers (thiscall, self == citizen) ----
    bool Flag388();                                     // 0x00c0c0e0
    int  GetAnimGuid();                                 // 0x00c0e040
    int  FUN_00c0e370();                                // 0x00c0e370
    void SetSprinting(int s);                           // 0x00c1ad10
    void InterruptAnimation(int anim, int a, int b);    // 0x00c12310
    int  PlayAnimation(int anim, int a, int b);         // 0x00c12190
    char AnimationFinished(int anim);                   // 0x00c123f0
    void Show();                                        // 0x00c0f2b0
    cCity* GetCity();                                   // 0x00c23e40
    uint32_t FUN_00c227b0();                            // 0x00c227b0
    void SetCurrentToolEffect(int a, int b);            // 0x00c24f40
    void FUN_00c0d0c0(int a, int b);                    // 0x00c0d0c0
};

// ---------------------------------------------------------------------------------------------
// free helpers

void* FUN_00d51660();                                   // 0x00d51660
void* GetCurrentGameMode();                             // 0x00b5b800
cPlanetModel* PlanetModel();                            // 0x00b3d350
cGameNounManager* NounManager();                        // 0x00b3d300
bool FUN_00c38990(void* self, int flag);                // 0x00c38990
bool FUN_00c03520(void* entry);                         // 0x00c03520
void FUN_00b3d870(void* ppIt);                          // 0x00b3d870
struct cLocoWrapper { void FUN_00b45410(); };           // 0x00b45410
cLocoWrapper* __stdcall FUN_00b3d310(void* p);          // 0x00b3d310
int  FUN_00d99a10(int v);                               // 0x00d99a10
int* FUN_00d998f0(int v);                               // 0x00d998f0

extern "C" void FUN_00cd7d10();
extern "C" void FUN_00d3d420();
extern "C" void FUN_00ad48b0();
extern "C" void FUN_00ae72d0();
extern "C" void FUN_00b1e500();

namespace SP {

// @ 0x00d90640
float FUN_00d90640(cSPCreatureCitizen* p, void* a2, void* a3, uint32_t flags,
                   void* pStimuli, char* pOut)
{
    cGameObject* pSel = 0;
    void* pVar = FUN_00d51660();
    if ((flags & 0x800000) != 0)
        return 0.0f;
    if ((flags & 0x400) == 0) {
        if (pVar == 0)
            return 0.0f;
        if ((((uint32_t*)pVar)[0x6c / 4] >> 2 & 1) == 0)
            return 0.0f;
    }

    Vec3* pPos = p->mLoco.GetPosition();
    float bestSq;

    if (p->Flag388()) {
        AuxGeom* pAux = (AuxGeom*)p->mLoco.GetAux68();
        float r = (pAux->f14 - pAux->f08) + 20.0f;
        bestSq = r * r + 1600.0f;

        void** it = (void**)p->mp140C;
        void** itEnd = (void**)p->mp1410;
        if (it == itEnd)
            return 0.0f;
        if (!FUN_00c03520(*it))
            FUN_00b3d870(&it);
        if (it == itEnd)
            return 0.0f;
        do {
            void* pObj = ((IterEntry*)*it)->mpObject;
            if (pObj != 0) {
                cGameObject* pGO = (cGameObject*)pObj;
                if (pGO->GetType20() == (int)0x018ebadc && !FUN_00c38990(pObj, 1)) {
                    Vec3* pV = pGO->mLoco34.GetPosition();
                    float dz = pV->z - pPos->z, dy = pV->y - pPos->y, dx = pV->x - pPos->x;
                    float d = (dz * dz + dy * dy) + dx * dx;
                    if (bestSq > d) {
                        pSel = pGO;
                        bestSq = d;
                    }
                }
            }
            do {
                ++it;
                if (it == itEnd)
                    goto done;
            } while (!FUN_00c03520(*it));
        } while (it != itEnd);
    } else {
        cPlanetModel* pPlanet = PlanetModel();
        bestSq = 2900.0f;
        int* pVec = NounManager()->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00ad48b0,
                                                     FUN_00b1e500, (void*)0x018ebadc);
        void** pBegin = (void**)pVec[1];
        void** pEnd = (void**)pVec[2];
        if (pBegin == pEnd)
            return 0.0f;
        do {
            cGameObject* pObj = (cGameObject*)*pBegin;
            if (!FUN_00c38990(pObj, 1)) {
                Vec3* pV = pObj->mLoco34.GetPosition();
                float dz = pV->z - pPos->z, dy = pV->y - pPos->y, dx = pV->x - pPos->x;
                float d = (dz * dz + dy * dy) + dx * dx;
                if (bestSq > d) {
                    Vec3 surf;
                    pPlanet->DirectionToSurfacePosition(surf, pV);
                    float sz = pV->z - surf.z, sy = pV->y - surf.y, sx = pV->x - surf.x;
                    if (!(2500.0f <= (sz * sz + sy * sy) + sx * sx)) {
                        pSel = pObj;
                        bestSq = d;
                    }
                }
            }
            ++pBegin;
        } while (pBegin != pEnd);
    }

done:
    if (pSel == 0)
        return 0.0f;
    if (pStimuli != 0)
        ((nSPBehaviorTree::behavior_stimuli*)pStimuli)->GetAny();
    *pOut = 1;
    ((StimulusSlot*)pStimuli)->mpTarget = &pSel->mStimulus508;
    return 1.0f;
}

// @ 0x00d90950
float FUN_00d90950(cSPCreatureCitizen* p, void* a2, void* a3, uint32_t a4,
                   void* pStimuli, char* pOut)
{
    int* pVec = NounManager()->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00ae72d0,
                                                 FUN_00b1e500, (void*)0x018c6de8);
    if (pVec[1] == pVec[2])
        return 0.0f;

    int id = p->GetIdentity();
    void** it = (void**)p->mp140C;
    void** itEnd = (void**)p->mp1410;
    if (it != itEnd) {
        if (!FUN_00c03520(*it))
            FUN_00b3d870(&it);
        while (it != itEnd) {
            void* pObj = ((IterEntry*)*it)->mpObject;
            if (pObj != 0) {
                cGameObject* pGO = (cGameObject*)pObj;
                if (pGO->GetType20() == (int)0x018c6de8 && pGO->GetIdentity4c() != id) {
                    if (pStimuli != 0)
                        ((nSPBehaviorTree::behavior_stimuli*)pStimuli)->GetAny();
                    *pOut = 1;
                    ((StimulusSlot*)pStimuli)->mpTarget = &pGO->mStimulus508;
                    return 1.0f;
                }
            }
            do {
                ++it;
                if (it == itEnd)
                    return 0.0f;
            } while (!FUN_00c03520(*it));
        }
    }
    return 0.0f;
}

// @ 0x00d90a60
float FUN_00d90a60(cSPCreatureCitizen* p)
{
    if (GetCurrentGameMode() == (void*)0x01654c05 && p->mf5E0 <= 0.0f)
        return 1.0f;
    if (GetCurrentGameMode() == (void*)0x01654c04)
        if (p->mf5E0 < p->mCommunity.GetCap58())
            return 1.0f;
    return 0.0f;
}

// @ 0x00d90ac0
void FUN_00d90ac0(cSPCreatureCitizen* p, BehaviorStateOut* pOut)
{
    if (p->mf5E0 <= 1.5258789e-05f) {
        FUN_00b3d310(&p->mLoco)->FUN_00b45410();
        p->Flag8c();
        pOut->mf0C = 10.0f;
        pOut->mf14 = 1.5f;
        pOut->m18 = 0;
    }
}

// @ 0x00d90b20
bool FUN_00d90b20(cSPCreatureCitizen* p, void* a2, void* a3, uint32_t a4, void* a5,
                  BehaviorStateOut* pOut)
{
    pOut->mf04 = 0.0f;
    pOut->mf0C = 10.0f;
    pOut->mf14 = 1.5f;
    pOut->m00 = 0;
    pOut->m08 = 0;
    pOut->m10 = 0;
    pOut->m18 = 0;
    if (p->mf5E0 <= 1.5258789e-05f) {
        FUN_00b3d310(&p->mLoco)->FUN_00b45410();
        p->Flag8c();
        pOut->mf0C = 10.0f;
        pOut->mf14 = 1.5f;
        pOut->m18 = 0;
    }
    return true;
}

// @ 0x00d90bb0
float FUN_00d90bb0(cSPCreatureCitizen* p, void* a2, void* a3, uint32_t a4,
                   void* pStimuli, char* pOut)
{
    int a = p->mpB4C->mStimuli.Play(0, 0x80);
    int v = FUN_00d99a10(a);
    if (v == 0) {
        p->mpB4C->mStimuli.ClearAll(0, 0x80);
    } else {
        cGameObject* pObj = (cGameObject*)FUN_00d998f0(v);
        if (pObj != 0) {
            cGameObject* pChild = (cGameObject*)pObj->GetChild0c();
            if (pChild->GetType20() != (int)0x02a034cd) {
                if (pStimuli != 0)
                    ((nSPBehaviorTree::behavior_stimuli*)pStimuli)->GetAny();
                ((StimulusSlot*)pStimuli)->mpTarget = pObj;
                *pOut = 1;
                return 1.0f;
            }
        }
    }
    return 0.0f;
}

// @ 0x00d90c40
void FUN_00d90c40(cSPCreatureCitizen* p)
{
    p->mpFB8->mnA30 -= 1;
}

// @ 0x00d90c60
char FUN_00d90c60(cSPCreatureCitizen* p)
{
    return !p->mLoco.IsNearGoal();
}

// @ 0x00d90c80
float FUN_00d90c80(void* a1, void* a2, void* a3, uint32_t flags)
{
    if ((flags & 1) == 0 && (flags & 0x1000) != 0)
        return 0.0f;
    return 1.0f;
}

// @ 0x00d90ca0
void FUN_00d90ca0(cSPCreatureCitizen* p)
{
    p->mnFC0 = 3;
    p->FUN_00c0d0c0(2, 0);
    p->mpFB8->mnA28 -= 1;
}

// @ 0x00d90cd0
void FUN_00d90cd0(cSPCreatureCitizen* p)
{
    p->SetSprinting(0);
}

// @ 0x00d90ce0
bool FUN_00d90ce0(cSPCreatureCitizen* p)
{
    if (p->mLoco.IsNearGoal()) {
        int anim = p->mpFB8->mn1A8 + 0x2481dda;
        if (p->GetAnimGuid() != anim)
            p->InterruptAnimation(anim, -1, 0);
    }
    return true;
}

// @ 0x00d90d30
float FUN_00d90d30(cSPCreatureCitizen* p)
{
    Vec3* v = p->mLoco.GetPosition();
    if (p->mpFB8->mPos.CheckPosition(v) == 0)
        return 0.0f;
    return 1.0f;
}

// @ 0x00d90d70
bool FUN_00d90d70(cSPCreatureCitizen* p, void* a2, void* a3, uint8_t flags,
                  void* a5, int* pState)
{
    if ((flags & 0x10) == 0)
        return false;
    switch (*pState) {
    case 0:
        if (!p->mLoco.IsNearGoal())
            return true;
        *pState = 1;
        goto play;
    case 1:
        if (!p->AnimationFinished(0))
            return true;
        goto play;
    default:
        return true;
    }
play:
    p->PlayAnimation(0x2481de3, 1, -1);
    return true;
}

// @ 0x00d90dd0
bool UfoWaving_Tick(cSPCreatureCitizen* p)
{
    int r = p->mpB4C->mStimuli.Play(0x100, 0);
    if (r == 0)
        return false;
    if (p->mLoco.IsNearGoal()) {
        if (p->GetAnimGuid() != 0x2481dc7)
            p->InterruptAnimation(0x2481dc7, -1, 0);
    }
    return true;
}

// @ 0x00d90e30
bool FUN_00d90e30(cSPCreatureCitizen* p, void* a2, void* a3, void* a4, void* a5, int* pState)
{
    switch (*pState) {
    case 0:
        if (p->mLoco.IsNearGoal()) {
            p->InterruptAnimation(p->mpFB8->mn1AC, -1, 0);
            *pState = 1;
        }
        break;
    case 1:
        if (p->AnimationFinished(0))
            return false;
        break;
    default:
        break;
    }
    return true;
}

// @ 0x00d90e90
void RunFromDanger_Deactivate(cSPCreatureCitizen* p)
{
    p->SetSprinting(0);
    if (GetCurrentGameMode() == (void*)0x01654c05) {
        p->SetMode9c(0);
        int r = p->mpB4C->mStimuli.Play(4, 0);
        if (r == 0) {
            if (p->GetCity() != 0)
                p->GetCity()->mn2D0 -= 1;
        }
    }
}

// @ 0x00d90ef0
void WildPanic_Deactivate(cSPCreatureCitizen* p)
{
    p->InterruptAnimation(0x2481db0, -1, 0);
}

// @ 0x00d90f10
void CropCirclesAttract_Deactivate(cSPCreatureCitizen* p)
{
    if (p->GetMode98() == 5) {
        p->SetMode9c(0);
        int v = p->GetCity()->FUN_00bd8190() - 1;
        p->GetCity()->FUN_00bd8170(v);
    }
}

// @ 0x00d90f60
void FUN_00d90f60(cSPCreatureCitizen* p)
{
    p->SetCurrentToolEffect(0, -1);
    p->mpFB8->mnA38 -= 1;
    p->mpFB8->mCircle070.RemoveAgent(p);
}

// @ 0x00d90f90
bool FUN_00d90f90(cSPCreatureCitizen* p, void* a2, uint8_t flags, void* a4, void* a5, int* pOut)
{
    if (pOut != 0)
        *pOut = 0;
    p->GetCity();
    cBehaviorAgent* ag = p->mpFB8;
    uint32_t u = p->FUN_00c227b0();
    if (u > 3)
        return false;
    *ag->GetCounter(u) += 1;
    *pOut = 2 - (int)(flags & 1);
    return true;
}

// @ 0x00d90ff0
void FUN_00d90ff0(cSPCreatureCitizen* p)
{
    cBehaviorAgent* ag = p->mpFB8;
    uint32_t u = p->FUN_00c227b0();
    if (u > 3)
        return;
    int* pi = ag->GetCounter(u);
    if (*pi > 0)
        *pi -= 1;
}

// @ 0x00d91020
bool FUN_00d91020(cSPCreatureCitizen* p, void* a2, void* a3, void* a4, void* a5,
                  TickState* pState, void* a7, float dt)
{
    p->GetCity();
    switch (pState->mMode) {
    case 0:
        if (p->mLoco.IsNearGoal()) {
            pState->mMode = 1;
            pState->mf4 = 0.0f;
        }
        break;
    case 1: {
        float f = pState->mf4 + dt;
        pState->mf4 = f;
        if (5.0f < f)
            return false;
        break;
    }
    default:
        break;
    }
    return true;
}

// @ 0x00d91080
char FUN_00d91080(cSPCreatureCitizen* p)
{
    return p->mbFBC == '\0';
}

// @ 0x00d91090
void OffStage_Deactivate(cSPCreatureCitizen* p)
{
    p->mCombatant.mb15 = 1;
    p->mbF90 = 1;
    p->Show();
    p->mbFBC = 1;
    p->InterruptAnimation(0x2481db0, -1, 0);
}

// @ 0x00d910d0
bool IsFunctional(cSPCreatureCitizen* p)
{
    return p->mCombatant.GetDamageState() != 2;
}

// @ 0x00d910f0
void FUN_00d910f0(cSPCreatureCitizen* p, void* a2, void* a3, uint32_t flags)
{
    if ((flags & 0x40000) != 0)
        p->FlagC8(0);
}

// @ 0x00d91110
float FUN_00d91110(cSPCreatureCitizen* p)
{
    int id = p->mnFF0;
    if (id == p->GetIdentity())
        return 1.0f;
    return 0.0f;
}

// @ 0x00d91130
char FUN_00d91130(cSPCreatureCitizen* p)
{
    return !p->AnimationFinished(0);
}

// @ 0x00d91150
bool AdmireObject_Tick(cSPCreatureCitizen* p, void* a2, void* a3, void* a4, void* a5,
                       AdmireState* pState)
{
    if (p->mLoco.IsNearGoal()) {
        if (pState->mFlag != 0) {
            pState->mFlag = 0;
            p->PlayAnimation(0x2d5f9c5, 1, -1);
            return true;
        }
        if (p->AnimationFinished(0)) {
            pState->mCount += 1;
            if (pState->mCount > 3)
                return false;
            p->PlayAnimation(0x2d5f9c5, 1, -1);
        }
    }
    return true;
}

// @ 0x00d911c0
void AdmireObject_Deactivate(cSPCreatureCitizen* p)
{
    p->mpFB8->mCircle1BC.RemoveAgent(p);
    p->SetSprinting(0);
}

// @ 0x00d911f0
void ActInVignette_Activate(cSPCreatureCitizen* p)
{
    p->SetSprinting(0);
    p->InterruptAnimation(0x2481db0, -1, 0);
}

// @ 0x00d91250
void ActInVignette_Deactivate(cSPCreatureCitizen* p)
{
    p->mpB4C->mStimuli.ClearAll(0x800, 0);
    p->mpFB8->ExitZone(p);
}

// @ 0x00d91280
bool ReactToRubble_Tick(cSPCreatureCitizen* p, void* a2, void* a3, void* a4, void* a5,
                        RubbleState* pState)
{
    if (p->mpFB8->mnA44 != pState->mId)
        return false;
    if (p->mLoco.IsNearGoal()) {
        if (pState->mFlag != 0) {
            pState->mFlag = 0;
            int a = (int)sMathRandom.RandomUint32Uniform(3) + 0x51de063;
            p->InterruptAnimation(a, -1, 0);
            for (int i = 2; i != 0; --i) {
                int b = (int)sMathRandom.RandomUint32Uniform(3) + 0x51de063;
                pState->mAnim = p->PlayAnimation(b, 0, -1);
            }
            return true;
        }
        if (p->AnimationFinished(pState->mAnim))
            return false;
    }
    return true;
}

// @ 0x00d91320
int IsDamaged(cCombatant* c)
{
    if (c->GetDamageState() != 2) {
        float h = c->mfHealth38;
        if (h != c->GetMaxHealth())
            return 1;
    }
    return 0;
}

// @ 0x00d91360
int FUN_00d91360(cCombatant* c)
{
    float h = c->mfHealth38;
    if (h / c->GetMaxHealth() < 0.5f)
        return 1;
    return 0;
}

// @ 0x00d91390
bool FUN_00d91390(cSPCreatureCitizen* p)
{
    p->InterruptAnimation((int)sMathRandom.RandomUint32Uniform(3) + 0x2481dd4, -1, 0);
    p->mpB4C->mStimuli.ClearAll(0x1000, 0);
    return true;
}

// @ 0x00d913d0
bool FUN_00d913d0(cSPCreatureCitizen* p)
{
    return p->FUN_00c0e370() <= 1;
}

// @ 0x00d91480
bool AlienGreeting_Activate(cSPCreatureCitizen* p)
{
    p->mpB4C->mStimuli.ClearAll(0x1000, 0);
    if (p->mpFB8->mbA50 != 0)
        return false;
    switch (p->GetCity()->GetVehicleSpecialty()) {
    case 0:
        ((cCityVisualizer*)p->mpFB8)->StartSpecialVignette((void*)0xc3e4872d, p);
        return true;
    case 1:
        ((cCityVisualizer*)p->mpFB8)->StartSpecialVignette((void*)0xd013f836, p);
        return true;
    default:
        ((cCityVisualizer*)p->mpFB8)->StartSpecialVignette((void*)0xa9f7e664, p);
        return true;
    }
}

// @ 0x00d91510
unsigned char FUN_00d91510(cSPCreatureCitizen* p)
{
    uint32_t u = p->mpB4C->mn1C8 & 0x800;
    if (u != 0)
        return (unsigned char)u;
    return 1;
}

}  // namespace SP