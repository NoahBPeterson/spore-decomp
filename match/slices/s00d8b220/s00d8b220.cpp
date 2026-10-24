// Slice s00d8b220: SP::cCreatureBase behaviour-tree nodes of the creature
// brain (roar / charge actions and the target-selection conditions).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-   (no /EHsc: no local object
// with a destructor that needs an unwind frame).
//
// Every routine is a brain node body with the fixed argument list
// (creature, int, int, unsigned, stimuli*, out*) -- the ints and the unsigned
// are unused.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed   int   i32;

#define VFUNC(obj, off) ((*(void***)(obj))[(off) / 4])

// ---------------------------------------------------------------- constants
// Floats / globals read out of the .data of the image.
extern "C" float DAT_0169f03c;      // creature colour, red
extern "C" float DAT_0169f040;      // creature colour, green
extern "C" float DAT_0169f044;      // creature colour, blue
extern "C" float DAT_01485720;      // 1.0f
extern "C" float DAT_01470f1c;      // 2.0f
extern "C" float DAT_013ec4b4;      // 0.9f
extern "C" float DAT_0147c030;      // FLT_MAX
extern "C" float DAT_015d9c6c;      // float of an empty property variant
extern "C" float DAT_01486110;      // reload default A
extern "C" float DAT_013f0e84;      // reload default B
extern "C" float DAT_0169f0f0;      // reloaded tummy values
extern "C" float DAT_0169f0f4;
extern "C" float DAT_0169f0f8;
extern "C" float DAT_0169f0fc;
extern "C" u32   DAT_0158446c;      // time stamp copied into creature +0x1670

// ------------------------------------------------------------ engine objects
struct cBehaviorStimuli {                     // nSPBehaviorTree + 0x08
    void Notify(i32 kind, i32 value, float priority, void* source);   // 0x00bc97f0
    i32  Play(i32 anim, i32 flags);                                   // 0x00bc96a0
    void GetAny();                                                    // 0x00d997e0
};

struct nSPBehaviorTree {
    u8                 mPad00[8];
    cBehaviorStimuli   mStimuli;              // +0x08
};

struct cSettingsFlags {
    u8  mPad00[0x6c];
    u32 mBits0   : 3;                         // +0x6c
    u32 mbFlag3  : 1;                         // +0x6c bit 3
    u32 mRest    : 28;
};
cSettingsFlags* CreatureSettings();           // 0x00d51660

// Property slot handed back by the modifier list lookup (vtable +0x24).
struct Variant {
    const float* mpData;                      // +0x00
    u32    mPad04[3];
    u8     mFlags10;                          // +0x10
    u8     mPad11;
    u16    mType12;                           // +0x12

    float GetFloat() const
    {
        if (mType12 == 0x0d || mType12 == 0x10) {
            if ((mFlags10 & 0x30) != 0)
                return *mpData;
            return *(const float*)(mType12 != 0 ? (const void*)this : 0);
        }
        return DAT_015d9c6c;
    }
};

struct cModifiers {
    void Release() { ((void(__thiscall*)(void*))VFUNC(this, 0x04))(this); }
    bool GetProperty(u32 hash, const Variant** ppOut)
    {
        return ((bool(__thiscall*)(void*, u32, const Variant**))VFUNC(this, 0x24))(this, hash, ppOut);
    }
};

struct cCreatureModeStrategy {                // singleton @ 0x0169e294
    u8             mPad00[0xb4];
    cModifiers*    mpModifiers;               // +0xb4
};
extern "C" cCreatureModeStrategy* DAT_0169e294;

struct cGameNounManager {                     // SP::NounManager() 0x00b3d300
    void* GetAvatar();                        // 0x00b1fdb0
};
cGameNounManager* NounManager();              // 0x00b3d300

struct HitHelper {                            // singleton @ 0x0168ab6c
    void Process(void* query);                // 0x00bc8080
};
HitHelper* HitHelperInstance();               // 0x00bc8000

// The +0x20 / +0x24 members of a near-list entry (game data objects).
struct cNearbyComponent {
    void* QueryInterface(u32 iid) { return ((void*(__thiscall*)(void*, u32))VFUNC(this, 0x0c))(this, iid); }
    i32   GetTypeID()             { return ((i32(__thiscall*)(void*))VFUNC(this, 0x20))(this); }
    bool  IsAvailable()           { return ((bool(__thiscall*)(void*))VFUNC(this, 0x2c))(this); }
    i32   GetPoliticalID()        { return ((i32(__thiscall*)(void*))VFUNC(this, 0x4c))(this); }
};

struct cNearbyEntry {                         // element of creature +0x1124
    float  mfDistance00;                      // +0x00
    u32    mPad04;
    void*  mpCreature08;                      // +0x08
    float  mfPriority0c;                      // +0x0c
    u32    mPad10[4];
    cNearbyComponent* mpComp20;               // +0x20
    cNearbyComponent* mpComp24;               // +0x24
};
#define PRIORITY(pEntry) ((pEntry)->mfPriority0c)

// Entry validators.  Both are members of the iterator context object that
// lives at iterator + 0x08 (the callee never reads `this` for 0x00c02600).
struct cNeighbourFilter {
    bool IsValidEntry(void* entry);           // 0x00c02600
};

struct cNearbyIterator {                      // 0x0c bytes (0x00b3d850)
    cNearbyEntry**  mpCur;                    // +0x00
    cNearbyEntry**  mpEnd;                    // +0x04
    cNeighbourFilter mFilter;                 // +0x08
    void Next();                              // 0x00b3d850
    void Advance()
    {
        do {
            ++mpCur;
            if (mpCur == mpEnd)
                return;
        } while (!mFilter.IsValidEntry(*mpCur));
    }
};

struct cNounFilter {
    bool IsValidEntry(void* entry);           // 0x00c03520
};

struct cNounIterator {                        // 0x0c bytes (0x00b3d870)
    void**   mpCur;                           // +0x00
    void**   mpEnd;                           // +0x04
    cNounFilter mFilter;                      // +0x08
    void Next();                              // 0x00b3d870
    void Advance()
    {
        do {
            ++mpCur;
            if (mpCur == mpEnd)
                return;
        } while (!mFilter.IsValidEntry(*mpCur));
    }
};

// ------------------------------------------------------- the creature object
struct cCombatantBlock {
    i32 GetDamageState();                     // 0x008e7f80
};

struct cLocomotive {                          // embedded at creature +0xc0
    void*  m_vftable;                         // +0x000
    u8     mPad004[0x40 - 0x004];             // +0x004

    float GetExtra();                         // 0x0104c040 (reads +0x26c)
    float GetRadius() { return ((float(__thiscall*)(void*))VFUNC(this, 0x74))(this); }
    void* QueryNeighbours(float radius, void* list, void* info, u32 hash)
    {
        return ((void*(__thiscall*)(void*, float, void*, void*, u32))VFUNC(this, 0x2c))(
            this, radius, list, info, hash);
    }
    void IssueRequest(void* request) { ((void(__thiscall*)(void*, void*))VFUNC(this, 0xdc))(this, request); }
};

struct cCreatureBase {
    void*  m_vftable;                         // +0x000
    u8     mPad004[0xc0 - 0x004];
    cLocomotive mLoco;                        // +0x0c0
    u8     mPad100[0x110 - 0x100];
    u32    mFlags110;                         // +0x110
    u8     mPad114[0x137 - 0x114];
    u8     mb137;                             // +0x137
    u8     mPad138[0x5a8 - 0x138];
    cCombatantBlock mCombatant;               // +0x5a8
    u8     mPad5ac[0xb20 - 0x5ac];
    void*  mpSpecies;                         // +0xb20
    u8     mPadB24[0xb4c - 0xb24];
    nSPBehaviorTree* mpBehaviorTree;          // +0xb4c
    u8     mPadB50[0xb58 - 0xb50];
    u32    mBitsB58  : 9;                     // +0xb58
    u32    mbFlagB59 : 1;                     // +0xb58 bit 9
    u32    mRestB58  : 22;
    u8     mPadB5c[0xb5e - 0xb5c];
    u8     mbDeadB5E;                         // +0xb5e
    u8     mPadB5f[0x101c - 0xb5f];
    i32    m101c;                             // +0x101c
    u8     mPad1020[0x1124 - 0x1020];
    cNearbyEntry** mpNearbyBegin;             // +0x1124
    cNearbyEntry** mpNearbyEnd;               // +0x1128
    u8     mPad112c[0x140c - 0x112c];
    void** mpIterBegin140c;                   // +0x140c
    void** mpIterEnd1410;                     // +0x1410
    u8     mPad1414[0x1670 - 0x1414];
    u32    m1670;                             // +0x1670

    i32  GetPoliticalID() { return ((i32(__thiscall*)(void*))VFUNC(this, 0x4c))(this); }
    void* GetTargetAsCreature();              // 0x00c0ee70
    i32  PlayAnimation(u32 id, i32 a, i32 b); // 0x00c12190
    void SetStealthed(bool a, bool b);        // 0x00c1aed0
    i32  InterruptAnimation(i32 id, i32 a, i32 b);     // 0x00c12310
    bool AnimationFinished(i32 id);           // 0x00c123f0
    bool AnimationFinishedA(i32 id);          // 0x00c12400
    bool CanReach(cCreatureBase* other);      // 0x00c0b8a0
};

// --------------------------------------------------- behaviour record types
// Locomotion request record (0x74 bytes): colour seed at +0x14.
struct cLocoRequest {
    void* mpBegin;                            // +0x00
    void* mpEnd;                              // +0x04
    void* mpCapacity;                         // +0x08
    u32   mPad0c;                             // +0x0c
    u32   mPad10;                             // +0x10
    float mfColorR;                           // +0x14
    float mfColorG;                           // +0x18
    float mfColorB;                           // +0x1c
    float mfOne;                              // +0x20
    u32   mZero24;                            // +0x24
    u32   mPad28[9];                          // +0x28 .. +0x4b
    u8    mbFlag4c;                           // +0x4c
    u8    mPad4d[3];
    float mfZero50;                           // +0x50
    float mfZero54;                           // +0x54
    float mfZero58;                           // +0x58
    u32   mZero5c;                            // +0x5c
    float mfTime60;                           // +0x60
    float mfRate64;                           // +0x64
    float mfLimit68;                          // +0x68
    float mfZero6c;                           // +0x6c
    u32   mZero70;                            // +0x70

    cLocoRequest* Init();                     // 0x00ac9850 (constructor)
};

// Animation record carried between the ticks of the charge action.
struct cChargeState {
    i32 mCurrentAnim;                         // +0x00
    i32 mAnimA;                               // +0x04
    i32 mAnimB;                               // +0x08
    i32 mAnimC;                               // +0x0c
    u8  mbInterrupted;                        // +0x10
    u8  mPad11[3];
    i32 mStage;                               // +0x14
};

// Small-buffer query descriptor handed to the locomotion query slot.
struct cQueryInfo {
    cNearbyEntry** mpBegin;                   // +0x00
    cNearbyEntry** mpEnd;                     // +0x04
    cNearbyEntry** mpCapacity;                // +0x08
    u32   mPad0c;                             // +0x0c
    u32   mPad10;                             // +0x10
    u32   mZero14;                            // +0x14
};

// ------------------------------------------------------- engine entry points
void* FUN_00d99470(void* handle);                       // 0x00d99470
void* FUN_00d998f0(void* object);                       // 0x00d998f0
void* FUN_00d999d0(void* block);                        // 0x00d999d0
float FUN_00d38a30(i32 which, void* creature);          // 0x00d38a30
float FUN_00d99ac0(void* locoA, void* locoB, i32 flag); // 0x00d99ac0
extern "C" void operator_delete_array(void* p);         // 0x00f47380

// The eastl vector buffer handed back by the locomotion query keeps its
// reference count in the dword in front of the data pointer.
static void SpReleaseVectorBuffer(void* pBuffer)
{
    if (pBuffer != 0 && ((i32*)pBuffer)[-1] != 0)
        operator_delete_array(pBuffer);
}

// Property lookup used by the tuning reload; inlined at each call site.
static __forceinline float GetPropFloat(cModifiers* pModifiers, u32 hash, float dflt)
{
    const Variant* pVariant = 0;
    if (pModifiers != 0 && pModifiers->GetProperty(hash, &pVariant))
        return pVariant->GetFloat();
    return dflt;
}

static __forceinline cLocoRequest* InitLocoRequest(cLocoRequest* pRequest)
{
    return pRequest->Init();
}

// ---------------------------------------------------------------------------
// @ 0x00d8b220  SP::EPIC_ROAR_Activate
// ---------------------------------------------------------------------------
bool FUN_00d8b220(cCreatureBase* self, i32 a1, i32 a2, u32 a3, void* pStimuli, i32* pAnim)
{
    cLocoRequest req;
    req.mpBegin    = 0;
    req.mpEnd      = 0;
    req.mpCapacity = 0;
    req.mfColorR   = DAT_0169f03c;
    req.mfColorG   = DAT_0169f040;
    req.mfColorB   = DAT_0169f044;
    req.mfOne      = DAT_01485720;
    req.mZero24    = 0;
    req.mbFlag4c   = 0;
    req.mfZero50   = 0.0f;
    req.mfZero54   = 0.0f;
    req.mfZero58   = 0.0f;
    req.mZero5c    = 0;
    req.mfTime60   = DAT_01470f1c;
    req.mfRate64   = DAT_013ec4b4;
    req.mfLimit68  = DAT_0147c030;
    req.mfZero6c   = 0.0f;
    req.mZero70    = 0;

    self->mLoco.IssueRequest(&req);

    SpReleaseVectorBuffer(req.mpBegin);

    *pAnim = self->PlayAnimation(0xb27c9fde, 1, -1);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00d8b320  SP::ReloadModifierTuning
// ---------------------------------------------------------------------------
void ReloadModifierTuning()
{
    cModifiers* pModifiers = 0;
    if (DAT_0169e294 != 0)
        pModifiers = DAT_0169e294->mpModifiers;

    float valueA = GetPropFloat(pModifiers, 0x4247bf2b, DAT_01486110);
    float valueB = GetPropFloat(pModifiers, 0x703b9a9d, DAT_013f0e84);

    DAT_0169f0f0 = GetPropFloat(pModifiers, 0x7d10c1b8, DAT_01486110);
    DAT_0169f0f4 = valueA;
    DAT_0169f0f8 = valueB;
    DAT_0169f0fc = 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00d8b4c0  (charge action: start the run, then stop and clear stealth)
// ---------------------------------------------------------------------------
bool FUN_00d8b4c0(cCreatureBase* self, i32 a1, i32 a2, u32 a3, void* pStimuli, cChargeState* pState)
{
    i32 anim = self->mpBehaviorTree->mStimuli.Play(0, 0x00020000);
    if (anim == 0)
        return false;

    pState->mAnimA = *(i32*)(anim + 0x0c);
    pState->mAnimB = *(i32*)(anim + 0x14);
    pState->mAnimC = *(i32*)(anim + 0x18);
    pState->mbInterrupted = 0;

    self->SetStealthed(false, false);

    cLocoRequest req;
    req.mpBegin    = 0;
    req.mpEnd      = 0;
    req.mpCapacity = 0;
    req.mfColorR   = DAT_0169f03c;
    req.mfColorG   = DAT_0169f040;
    req.mfColorB   = DAT_0169f044;
    req.mfOne      = DAT_01485720;
    req.mZero24    = 0;
    req.mbFlag4c   = 0;
    req.mfZero50   = 0.0f;
    req.mfZero54   = 0.0f;
    req.mfZero58   = 0.0f;
    req.mZero5c    = 0;
    req.mfTime60   = DAT_01470f1c;
    req.mfRate64   = DAT_013ec4b4;
    req.mfLimit68  = DAT_0147c030;
    req.mfZero6c   = 0.0f;
    req.mZero70    = 0;

    self->mLoco.IssueRequest(&req);

    SpReleaseVectorBuffer(req.mpBegin);

    pState->mStage = 0;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00d8b5f0  (charge action tick: advance the run / stop animations)
// ---------------------------------------------------------------------------
bool FUN_00d8b5f0(cCreatureBase* self, i32 a1, i32 a2, u32 a3, void* pStimuli, cChargeState* pState)
{
    i32 anim = self->mpBehaviorTree->mStimuli.Play(0, 0x00020000);
    if (anim == 0)
        return false;

    if (pState->mStage != 2 && *(i32*)(anim + 0x0c) != pState->mAnimA) {
        pState->mAnimA = *(i32*)(anim + 0x0c);
        pState->mAnimB = *(i32*)(anim + 0x14);
        pState->mAnimC = *(i32*)(anim + 0x18);
        pState->mbInterrupted = 0;
        pState->mStage = 0;
    }

    if (pState->mStage == 0) {
        if (!pState->mbInterrupted) {
            if (self->mb137 != 0 || (self->mFlags110 & 0x1000) != 0) {
                cLocoRequest req;
                self->mLoco.IssueRequest(InitLocoRequest(&req));

                SpReleaseVectorBuffer(req.mpBegin);

                pState->mCurrentAnim = self->InterruptAnimation(*(i32*)(anim + 0x0c), -1, 0);
                pState->mbInterrupted = 1;
                if (self->mbFlagB59)
                    self->m1670 = DAT_0158446c;
            }
            if (!pState->mbInterrupted)
                goto checkStages;
        }
        if (self->AnimationFinishedA(pState->mCurrentAnim)) {
            if (self->mCombatant.GetDamageState() == 2) {
                if (pState->mAnimC == -1)
                    return false;
                pState->mCurrentAnim = self->InterruptAnimation(pState->mAnimC, -1, 0);
                pState->mStage = 2;
            } else {
                if (pState->mAnimB == -1)
                    return false;
                pState->mCurrentAnim = self->InterruptAnimation(pState->mAnimB, -1, 0);
                pState->mStage = 1;
            }
            pState->mbInterrupted = 1;
        }
    }

checkStages:
    if (pState->mStage == 2) {
        if (!pState->mbInterrupted)
            return true;
        if (!self->AnimationFinished(pState->mAnimC))
            return true;
        return false;
    }
    if (pState->mStage != 1)
        return true;
    if (!pState->mbInterrupted)
        return true;
    if (!self->AnimationFinished(pState->mAnimB))
        return true;
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00d8b790  (roar action: query the neighbourhood, wake the best target)
// ---------------------------------------------------------------------------
float FUN_00d8b790(cCreatureBase* self, i32 a1, i32 a2, u32 a3, void* pStimuli, i32* pOut)
{
    float radius = self->mLoco.GetRadius();
    radius += self->mLoco.GetExtra();

    cNearbyEntry* buffer[32];
    cQueryInfo info;
    info.mpCapacity = buffer + 32;
    info.mpBegin    = buffer;
    info.mpEnd      = buffer;
    info.mZero14    = 0;

    void* query = self->mLoco.QueryNeighbours(radius, buffer, &info, 0xb9d14c31);
    HitHelperInstance()->Process(query);

    i32 myID = self->GetPoliticalID();

    for (cNearbyEntry** pp = info.mpBegin; pp != info.mpEnd; ++pp) {
        cNearbyEntry* pEntry = *pp;
        cNearbyComponent* pA = pEntry->mpComp20;
        if (pA == 0 || pA->IsAvailable())
            continue;
        cNearbyComponent* pB = pEntry->mpComp24;
        if (pB == 0 || pB->IsAvailable())
            continue;
        if (pB->GetPoliticalID() == myID) {
            if (FUN_00d998f0(pA->QueryInterface(0x013f94d4)) != 0) {
                self->mpBehaviorTree->mStimuli.Notify(0x400, 0, PRIORITY(pEntry), pA);
                break;
            }
        } else if (pA->GetPoliticalID() == myID) {
            FUN_00d998f0(pB->QueryInterface(0x013f94d4));
            self->mpBehaviorTree->mStimuli.Notify(0x400, 0, PRIORITY(pEntry), pB);
            break;
        }
    }

    SpReleaseVectorBuffer(info.mpBegin);
    return 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00d8b910  (condition: a reachable neighbour creature is present)
// ---------------------------------------------------------------------------
float FUN_00d8b910(cCreatureBase* self, i32 a1, i32 a2, u32 a3, cBehaviorStimuli* pStimuli, u8* pOut)
{
    cSettingsFlags* pSettings = CreatureSettings();
    if (pSettings != 0 && pSettings->mbFlag3) {
        void* pFound = 0;
        cNearbyIterator it;
        it.mpCur = self->mpNearbyBegin;
        it.mpEnd = self->mpNearbyEnd;
        if (it.mpCur != it.mpEnd) {
            if (!it.mFilter.IsValidEntry(*it.mpCur))
                it.Next();
            while (it.mpCur != it.mpEnd) {
                cNearbyEntry* pEntry = *it.mpCur;
                if (pEntry->mpCreature08 != 0) {
                    if (FUN_00d99470(pEntry->mpCreature08) != 0) {
                        pFound = pEntry->mpCreature08;
                        break;
                    }
                }
                it.Advance();
            }
        }

        if (pFound == 0) {
            if (self->m101c != 1)
                return 0.0f;
            pFound = NounManager()->GetAvatar();
            if (pFound == 0)
                return 0.0f;
        }

        if (pStimuli != 0)
            pStimuli->GetAny();
        *pOut = 1;
        *(void**)((u8*)pStimuli + 4) = pFound ? (u8*)pFound + 0x5a8 : 0;
        return 1.0f;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00d8ba20  (condition: an enemy in the iterated noun list)
// ---------------------------------------------------------------------------
float FUN_00d8ba20(cCreatureBase* self, i32 a1, i32 a2, u32 a3, cBehaviorStimuli* pStimuli, u8* pOut)
{
    i32 myID = self->GetPoliticalID();

    cNounIterator it;
    it.mpCur = self->mpIterBegin140c;
    it.mpEnd = self->mpIterEnd1410;
    if (it.mpCur != it.mpEnd) {
        if (!it.mFilter.IsValidEntry(*it.mpCur))
            it.Next();
        while (it.mpCur != it.mpEnd) {
            cNearbyEntry* pEntry = (cNearbyEntry*)*it.mpCur;
            cNearbyComponent* pComp = (cNearbyComponent*)pEntry->mpCreature08;
            if (pComp != 0 && pComp->GetTypeID() == 0x0436f342 && pComp->GetPoliticalID() != myID) {
                if (pStimuli != 0)
                    pStimuli->GetAny();
                *pOut = 1;
                *(void**)((u8*)pStimuli + 4) = (u8*)pComp + 0x588;
                return 1.0f;
            }
            cNearbyComponent* pOther = (cNearbyComponent*)pEntry->mpCreature08;
            if (pOther != 0) {
                pOther = (cNearbyComponent*)pOther->QueryInterface(0x0e9cb8ba);
                if (pOther != 0 && pOther->GetPoliticalID() != myID
                    && pOther->QueryInterface(0x1007ae63) == 0) {
                    if (pStimuli != 0)
                        pStimuli->GetAny();
                    *pOut = 1;
                    *(void**)((u8*)pStimuli + 4) = (u8*)pOther + 0x120;
                    return 1.0f;
                }
            }
            it.Advance();
        }
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00d8bb70  (condition: a target within attack range)
// ---------------------------------------------------------------------------
float FUN_00d8bb70(cCreatureBase* self, i32 a1, i32 a2, u32 a3, cBehaviorStimuli* pStimuli, u8* pOut)
{
    float reach = FUN_00d38a30(3, self);

    cCreatureBase* pTarget = (cCreatureBase*)self->GetTargetAsCreature();
    if (pTarget != 0 && pTarget->mpSpecies != self->mpSpecies && pTarget->mbDeadB5E == 0) {
        float distance = FUN_00d99ac0(&pTarget->mLoco, &self->mLoco, 1);
        float range = FUN_00d38a30(5, self);
        if (distance <= range) {
            if (pStimuli != 0)
                pStimuli->GetAny();
            *pOut = 1;
            *(void**)((u8*)pStimuli + 4) = (u8*)pTarget + 0x5a8;
            return 1.0f;
        }
    }

    i32 anim = self->mpBehaviorTree->mStimuli.Play(0x400, 0);
    if (anim != 0) {
        cCreatureBase* pOther = (cCreatureBase*)FUN_00d999d0((void*)anim);
        if (pOther != 0 && pOther->mbDeadB5E == 0) {
            if (pStimuli != 0)
                pStimuli->GetAny();
            *pOut = 1;
            *(void**)((u8*)pStimuli + 4) = (u8*)pOther + 0x5a8;
            return 1.0f;
        }
    }

    cNearbyIterator it;
    it.mpCur = self->mpNearbyBegin;
    it.mpEnd = self->mpNearbyEnd;
    if (it.mpCur != it.mpEnd) {
        if (!it.mFilter.IsValidEntry(*it.mpCur))
            it.Next();
        while (it.mpCur != it.mpEnd) {
            cNearbyEntry* pEntry = *it.mpCur;
            if (pEntry->mfDistance00 > reach)
                break;
            cCreatureBase* pNear = (cCreatureBase*)pEntry->mpCreature08;
            if (pNear->mpSpecies != self->mpSpecies && pNear->mbDeadB5E == 0 && self->CanReach(pNear)) {
                if (pStimuli != 0)
                    pStimuli->GetAny();
                *pOut = 1;
                *(void**)((u8*)pStimuli + 4) = (u8*)pNear + 0x5a8;
                return 1.0f;
            }
            it.Advance();
        }
    }
    return 0.0f;
}
