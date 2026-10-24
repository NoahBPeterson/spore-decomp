// slice s00db6e60: SP::MOVE_Tick (0x00db7190, 2500 bytes), __cdecl, 8 stack args.
// arg1 = creature (esi), arg5 = flags (bit 2 and bit 3 read), arg6 = float* position (edi),
// arg8 = float dt. Args 2, 3, 4 and 7 are not read by the original.
// PARTIAL: translation of the control flow from the asm and the Ghidra decompile. Field accesses are
// raw offsets; callee conventions come from the call sites. See partial.txt.
#include "types.h"

#define FIELD(p, off, T) (*(T*)((char*)(p) + (off)))

struct CreatureBase;   // opaque: only raw offsets are used

// Thiscall members of cSPCreatureBase, declared but not defined here.
struct CreatureBaseFns {
    void Hover(int);                                       // 0x00c13a30
    void SetSprinting(int);                                // 0x00c1ad10
    void InterruptAnimation(int, int, int);                // 0x00c12310 (guid, -1, 0)
    void PlayAnimation(int, int, int);                     // 0x00c12190 (guid, 1, -1)
    void TryJumpToTarget(int, const void*, const void*, int, int);  // 0x00c190e0
    unsigned PlayIdleAnimation(int, int);                  // 0x00bc96a0 (on mgr+8)
    unsigned GetCurrentAnimationGUID();                    // 0x00c0e040
    bool IsNearGoal();                                     // 0x00c42e20 (on +0xc0)
    bool IsEligible(int);                                  // 0x00c0c0e0 (returns bool)
};

// Free callees (cdecl unless noted in partial.txt).
bool   Vector3NotEqual(const float* a, const float* b);    // 0x0041dd30
float  Vec3Length(const float* v);                         // 0x004df2d0 returns float (fstp)
unsigned ChildOfPool(int idx);                             // pool GetObject, 0x00db3c40 (thiscall on 0x0159d548)

namespace SP {

// The retail function. Returns the value the original leaves in eax.
int MOVE_Tick(void* self, int a2, int a3, int a4, unsigned flags, float* pos, int a7, float dt)
{
    (void)a2; (void)a3; (void)a4; (void)a7;
    // dt-subtract timer on pos[0]; if it goes negative, reset to 1.0 and try a path step.
    float* pf = pos;
    pf[0] = pf[0] - dt;
    if (pf[0] < 0.0f) {
        pf[0] = 1.0f;
        // ... path/goal step (FUN_00bca2a0, FUN_00bcb510, pool GetObject, FUN_00db6fa0 / FUN_00db6ef0)
    }
    pf[1] = pf[1] - dt;
    pf[2] = pf[2] - dt;
    if (FIELD(self, 0x137, unsigned char) == 0 || (FIELD(self, 0x110, unsigned) & 0x1000) != 0)
        pf[3] = pf[3] + dt;
    (void)flags;
    return 1;   // TODO: remaining paths (IsNearGoal, animation/hover branches, hashtable find, return values)
}

} // namespace SP

// ---------------------------------------------------------------------------------------------
// 0x00db6e60 .. 0x00db7050: the movement-group helpers MOVE_Tick drives. Their class is
// SP::cGroupMovement; the dev-PDB order is shifted in the retail build, so every offset below is
// the retail one, read from the disassembly.
// ---------------------------------------------------------------------------------------------

inline void* operator new(unsigned int, void* p) { return p; }

// --- interfaces whose vtable slots the movement code calls -----------------------------------
// (dummy virtuals stand in for the slots nobody here calls; the offsets in the comments are exact)

class IEffect {                                                  // an entry in the effect system
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();   // +0x000
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();   // +0x010
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();   // +0x020
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();   // +0x030
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();   // +0x040
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();   // +0x050
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();   // +0x060
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();   // +0x070
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();   // +0x080
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();   // +0x090
    virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac();   // +0x0a0
    virtual void v0b0(); virtual void v0b4();                                             // +0x0b0
    virtual void* Cast(uint32_t typeId);                         // +0x0b8
    virtual void AddRef();                                       // +0x0bc
    virtual void Release();                                      // +0x0c0
};

class cLocomotiveObject {                                        // the creature's +0xc0 sub-object
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();   // +0x000
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();   // +0x010
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();   // +0x020
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();   // +0x030
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();   // +0x040
    virtual void v050(); virtual void v054();                                        // +0x050
    virtual bool v058();                                         // +0x058
    virtual void v05c(); virtual void v060(); virtual void v064(); virtual void v068();   // +0x05c
    virtual void v06c(); virtual void v070(); virtual void v074(); virtual void v078();   // +0x06c
    virtual void v07c(); virtual void v080(); virtual void v084(); virtual void v088();   // +0x07c
    virtual void v08c(); virtual void v090(); virtual void v094(); virtual void v098();   // +0x08c
    virtual void v09c(); virtual void v0a0(); virtual void v0a4(); virtual void v0a8();   // +0x09c
    virtual void v0ac(); virtual void v0b0(); virtual void v0b4(); virtual void v0b8();   // +0x0ac
    virtual void AddRef();                                       // +0x0bc
    virtual void Release();                                      // +0x0c0
    virtual void v0c4(); virtual void v0c8(); virtual void v0cc(); virtual void v0d0();   // +0x0c4
    virtual void v0d4(); virtual void v0d8(); virtual void v0dc(); virtual void v0e0();   // +0x0d4
    virtual void v0e4(); virtual void v0e8();                                        // +0x0e4
    virtual void v0ec();                                         // +0x0ec
};

class IGameObject {                                              // cSPCreatureBase's root object
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();   // +0x000
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();   // +0x010
    virtual uint32_t GetClassId();                               // +0x020
    virtual void v024(); virtual void v028(); virtual void v02c(); virtual void v030();   // +0x024
    virtual void v034(); virtual void v038(); virtual void v03c(); virtual void v040();   // +0x034
    virtual void v044(); virtual void v048(); virtual void v04c(); virtual void v050();   // +0x044
    virtual void v054(); virtual void v058(); virtual void v05c(); virtual void v060();   // +0x054
    virtual void v064(); virtual void v068(); virtual void v06c(); virtual void v070();   // +0x064
    virtual void v074(); virtual void v078(); virtual void v07c(); virtual void v080();   // +0x074
    virtual void v084(int, int, int);                            // +0x084
};

// --- owned references ------------------------------------------------------------------------
template <class T>
class AutoRefCount {
public:
    T* mpObject;                                                 // +0x00
    AutoRefCount(T* object) : mpObject(object) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& other) : mpObject(other.mpObject)
    {
        if (mpObject) mpObject->AddRef();
    }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};

// --- the movement group's own containers -----------------------------------------------------
class cGroupMovement;

class cCurvePoint {                                              // one sample of the group's curve
public:
    float mX;                                                    // +0x00
    float mY;                                                    // +0x04
    float mZ;                                                    // +0x08
    float mW;                                                    // +0x0c
    uint32_t mFlags;                                             // +0x10
    uint32_t mPad14[(0x38 - 0x14) / 4];                          // +0x14
    uint8_t mTail;                                               // +0x38
    uint8_t mPad39[3];                                           // +0x39
    void CopyFrom(const cCurvePoint* src);                       // 0x00ac1ff0 (ret 4)
};

class cCurveVector {                                             // SpVector<cCurvePoint>
public:
    cCurvePoint* mpBegin;                                        // +0x00
    cCurvePoint* mpEnd;                                          // +0x04
    cCurvePoint* mpEndOfStorage;                                 // +0x08
    void DoInsertValue(cCurvePoint* pos, const cCurvePoint* value);   // 0x00ac45e0 (ret 8)
    __forceinline void push_back(const cCurvePoint& value)
    {
        if (mpEnd < mpEndOfStorage) {
            cCurvePoint* slot = mpEnd;
            ++mpEnd;
            if (slot)
                slot->CopyFrom(&value);
        } else {
            DoInsertValue(mpEnd, &value);
        }
    }
};

template <class T>
class AutoRefVector {                                            // eastl::vector<EA::AutoRefCount<T>>
public:
    AutoRefCount<T>* mpBegin;                                    // +0x00
    AutoRefCount<T>* mpEnd;                                      // +0x04
    AutoRefCount<T>* mpEndOfStorage;                             // +0x08
    void DoInsertValue(AutoRefCount<T>* pos, const AutoRefCount<T>& value);   // 0x00bab900 (ret 8)
    __forceinline void push_back(const AutoRefCount<T>& value)
    {
        if (mpEnd < mpEndOfStorage) {
            AutoRefCount<T>* slot = mpEnd;
            ++mpEnd;
            if (slot)
                ::new ((void*)slot) AutoRefCount<T>(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};

class cEntityInfo {                                              // what the group knows per member
public:
    float mDoneTime;                                             // +0x00
    float mDistanceFromSlot2;                                    // +0x04
    int32_t mSlotIdx;                                            // +0x08
};

class cInfoNode {
public:
    cLocomotiveObject* mpKey;                                    // +0x00
    cEntityInfo mInfo;                                           // +0x04
    cInfoNode* mpNext;                                           // +0x10
};

class cMovementIterator {
public:
    cInfoNode* mpNode;                                           // +0x00
    void* mpBucket;                                              // +0x04
};

class cEntityInfoMap {                                           // eastl::hash_map<cLocomotiveObject*, cEntityInfo>
public:
    int32_t mnBucketCount;                                       // +0x00
    cInfoNode** mppBucketArray;                                  // +0x04
    int32_t mnBucket;                                            // +0x08
    uint32_t mPad0c[7];                                          // +0x0c (element count, rehash policy)
    cMovementIterator find(cLocomotiveObject* const& key);       // 0x00db4780 (ret 8)
    cMovementIterator erase(cMovementIterator it);               // 0x00db3da0 (ret 0xc)
    cEntityInfo* FindOrAdd(cLocomotiveObject* const& key);       // 0x00db5cf0 (ret 4)
};

namespace SP {

class cActionCircle {
public:
    class tSlot {
    public:
        bool mOccupied;                                          // +0x00
        uint32_t mPad04;                                         // +0x04
        uint32_t mReservingId;                                   // +0x08
        float mPos[3];                                           // +0x0c
        void Clear();                                            // 0x00afa0a0
    };
    uint32_t mPad00[0x50 / 4];                                   // +0x00
    tSlot* mpSlotBegin;                                          // +0x50
    uint32_t mSlotCount;                                         // +0x54
    uint32_t mPad58;                                             // +0x58
    tSlot* SlotAt(uint32_t index);                               // 0x00af9ff0 (ret 4)
};

} // namespace SP

struct Vector3 {
    float mX;                                                    // +0x00
    float mY;                                                    // +0x04
    float mZ;                                                    // +0x08
};

class cGroupMovement {                                           // the group object (retail layout)
public:
    uint32_t mPad00[2];                                          // +0x000
    cCurveVector mCurve;                                         // +0x008
    uint32_t mPad14[2];                                          // +0x014
    AutoRefVector<cLocomotiveObject> mEntities;                  // +0x01c
    uint32_t mPad28[(0x54 - 0x28) / 4];                          // +0x028
    cEntityInfoMap mInfoMap;                                     // +0x054
    uint32_t mPad7c[(0x190 - 0x7c) / 4];                         // +0x07c
    IEffect* mpObject;                                           // +0x190 (an owned reference)
    Vector3 mGoal;                                               // +0x194
    uint32_t mPad1a0[(0x1cc - 0x1a0) / 4];                       // +0x1a0
    int32_t mFlags1cc;                                           // +0x1cc
    bool mbFlag1d0;                                              // +0x1d0
    bool mbFlag1d1;                                              // +0x1d1
    uint8_t mPad1d2[2];                                          // +0x1d2
    SP::cActionCircle mActionCircle;                             // +0x1d4
    uint32_t mPad230[(0x23c - 0x230) / 4];                       // +0x230
    bool mbFlag23c;                                              // +0x23c
    uint32_t mPad240[(0x248 - 0x240) / 4];                       // +0x240
    uint32_t mSoundId248;                                        // +0x248

    void FUN_00db6e60(bool bSkipPoint);                          // 0x00db6e60 (ret 4)
    void FUN_00db6ef0(cLocomotiveObject* loco);                  // 0x00db6ef0 (ret 4)
    void FUN_00db6fa0(cLocomotiveObject* loco);                  // 0x00db6fa0 (ret 4)
};

// --- the rest of the world the four functions touch ------------------------------------------
struct cGroupMovementPool {
    cGroupMovement* GetObject(uint32_t slotRef);                 // 0x00db3c40 (ret 4)
};
extern cGroupMovementPool gGroupMovementPool;                    // 0x0159d548

struct cEntryState;

class cLocomotionMgr {                                           // the creature's +0xb4c
public:
    uint32_t mPad000[(0x600 - 0x000) / 4];                       // +0x000
    cEntryState* mpEntry;                                        // +0x600 (an owned reference)
    uint32_t mId604;                                             // +0x604
    void ReleaseEntry();                                         // 0x00bcb430
};

struct cEntryState {                                             // cLocomotionMgr::mpEntry
    uint32_t mPad000[(0x1a4 - 0x000) / 4];                       // +0x000
    uint32_t mGroupSlotRef;                                      // +0x1a4
    void* CurrentId();                                           // 0x00bc9b10
};

struct cSoundSlots {
    void Release(uint32_t slot);                                 // 0x00bc2180 (ret 4)
};

struct cTribeModeStrategy {
    uint32_t mPad000[(0x1c8 - 0x000) / 4];                       // +0x000
    cSoundSlots* mpSoundSlots;                                   // +0x1c8
    static cTribeModeStrategy* Instance();                       // 0x00cd40b0
};

struct cEffectPlayer {
    void PlayEffect(IEffect* effect);                            // 0x00aca360 (ret 4)
};
cEffectPlayer* EffectPlayer();                                   // 0x00b3d480

bool RemoveEntity(AutoRefVector<cLocomotiveObject>* list,
                  cLocomotiveObject** value);                    // 0x00afc4b0

class cSPCreatureBase : public IGameObject {                      // the creature the move driver gets
public:
    uint32_t mPad004[(0xc0 - 0x004) / 4];                        // +0x004
    cLocomotiveObject mLocomotive;                               // +0x0c0
    uint32_t mPadAfterLoco[(0xb4c - 0x0c0 - sizeof(cLocomotiveObject)) / 4];
    cLocomotionMgr* mpLocomotionMgr;                             // +0xb4c
    uint32_t mPadB50[(0xb64 - 0xb50) / 4];                       // +0xb50
    bool mbFlagB64;                                              // +0xb64

    void UpdateLocomotion(int);                                  // 0x00c14750 (ret 4)
    void SetSprinting(int);                                      // 0x00c1ad10 (ret 4)
    void Hover(int);                                             // 0x00c13a30 (ret 4)
};

struct cMoveArg {                                                // the payload the move driver receives
    uint32_t mPad00[4];                                          // +0x00
    bool mFlag;                                                  // +0x10
    uint8_t mPad11[0xb];                                         // +0x11
    IEffect* mpEffect;                                           // +0x1c
};

// ---------------------------------------------------------------------------------------------
// @ 0x00DB6E60
void cGroupMovement::FUN_00db6e60(bool bSkipPoint)
{
    if (bSkipPoint)
        return;
    cCurvePoint point;
    point.mX = mGoal.mX;
    point.mY = mGoal.mY;
    point.mZ = mGoal.mZ;
    point.mW = 1.0f;
    point.mFlags = 0;
    point.mTail = 0;
    mCurve.push_back(point);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00DB6EF0
void cGroupMovement::FUN_00db6ef0(cLocomotiveObject* loco)
{
    {
        AutoRefCount<cLocomotiveObject> holder(loco);
        mEntities.push_back(holder);
    }
    cEntityInfo info;
    info.mDoneTime = 0.0f;
    info.mDistanceFromSlot2 = 0.0f;
    info.mSlotIdx = -1;
    *mInfoMap.FindOrAdd(loco) = info;
    mbFlag1d0 = true;
    mFlags1cc = 1;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00DB6FA0
void cGroupMovement::FUN_00db6fa0(cLocomotiveObject* loco)
{
    cMovementIterator it = mInfoMap.find(loco);
    cInfoNode* node = it.mpNode;
    if (node != mInfoMap.mppBucketArray[mInfoMap.mnBucket]) {
        int32_t slotIdx = node->mInfo.mSlotIdx;
        if (slotIdx != -1) {
            SP::cActionCircle::tSlot* slot = mActionCircle.SlotAt((uint32_t)slotIdx);
            if (slot != 0 && slot->mOccupied && slot->mReservingId == 0)
                slot->Clear();
        }
        mInfoMap.erase(it);
    }
    RemoveEntity(&mEntities, &loco);
    mbFlag1d0 = true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00DB7050
void FUN_00db7050(cSPCreatureBase* creature, uint32_t a2, int32_t a3, uint32_t a4, uint32_t a5,
                  cMoveArg* arg)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    creature->mbFlagB64 = arg->mFlag;
    creature->mLocomotive.v0ec();
    creature->UpdateLocomotion(0);
    creature->SetSprinting(0);
    creature->Hover(0);
    creature->v084(0, 0, 0);

    cEntryState* entry = creature->mpLocomotionMgr->mpEntry;
    if (entry != 0) {
        cGroupMovement* group = gGroupMovementPool.GetObject(entry->mGroupSlotRef);
        if (creature->GetClassId() == 0x18eb4b7 && creature == entry->CurrentId() &&
            group->mSoundId248 != 0) {
            cTribeModeStrategy* strategy = cTribeModeStrategy::Instance();
            strategy->mpSoundSlots->Release(group->mSoundId248);
            group->mSoundId248 = 0;
        }
        group->FUN_00db6fa0(&creature->mLocomotive);
        if (group->mbFlag23c)
            creature->mpLocomotionMgr->ReleaseEntry();
    }

    if (creature->mLocomotive.v058()) {
        if (arg->mpEffect != 0) {
            IEffect* effect = arg->mpEffect;
            if (effect != 0 && effect->Cast(0x17f243b) != 0)
                EffectPlayer()->PlayEffect(effect);
        }
    }
    if (arg->mpEffect != 0)
        arg->mpEffect->Release();
}
