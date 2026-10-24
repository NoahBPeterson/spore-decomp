// Slice s00db2fd0.
//
// Two Spore state-machine tick functions plus the EASTL-style fixed-stride slot
// pool they allocate their state blocks from:
//
//   00db2fd0  SP::REACT_TO_TARGET_Tick                   (phase machine, 7 phases)
//   00db33d0  SP::cGalaxyGameEntryImpl::HandleSimulationUpdate (phase machine, 10 phases)
//   00db3390  the matching "release" half of 00db33d0
//   00db3c40 / 00db3c90 / 00db3da0 / 00db3e30
//             cResizableObjectPoolT<SP::cGroupMovement> members
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vector3f { float x, y, z; };

class cPropSet;

// --- globals ---------------------------------------------------------------
extern const float kPropDefaultA;                                // 0x013ec5b4
extern const float kPropDefaultB;                                // 0x01473c70
extern const float kSpeedScale;                                  // 0x0140e968
extern const float kProbeStep;                                  // 0x01470f1c
extern const float kInvalidPos;                                  // 0x0169f3b8
extern const char  kAllocFile[];                                 // 0x013ebb38
extern const char  kAllocTag[];                                  // 0x013f09b4

enum { kPoolSlotStride = 0x250 };                                // bytes per pool slot

// ---------------------------------------------------------------------------
// UTFWin / Swarm style COM object.  Only the vtable slots that this slice
// dereferences are named; the rest are placeholders so the offsets line up.
// ---------------------------------------------------------------------------
class IWin {
 public:
    PV(0)
    virtual void  Release();                                     // +0x04
    virtual void  pv02(int a);                                   // +0x08
    virtual void* pv03(int index);                               // +0x0c
    virtual char  pv04();                                        // +0x10
    PV(5)
    virtual void  pv06(void* msg);                               // +0x18
    PV(7) PV(8) PV(9) PV(10)
    virtual void* pv11();                                        // +0x2c
    virtual void* pv12();                                        // +0x30
    virtual void* pv13();                                        // +0x34
    virtual void  pv14(void* p);                                 // +0x38
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    virtual void* pv23(float* out);                              // +0x5c
    PV(24) PV(25) PV(26) PV(27)
    virtual double pv28();                                       // +0x70
    PV(29) PV(30) PV(31) PV(32)
    virtual void  pv33();                                        // +0x84
    PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
    virtual cPropSet* pv45(void* a);                             // +0xb4

    void FUN_00bcb960(int a);                                    // 0x00bcb960
    void FUN_00bcc010();                                         // 0x00bcc010
};

// EA::AutoRefCount<EA::UTFWinControls::IWinText> -- owns one raw reference.
class AutoRefCountText {
 public:
    AutoRefCountText& operator=(IWin* p);                         // 0x00b5f950

    IWin* mpRef;                                                 // +0x00
};

// The property bag reached through creature->pv45(interface).
class cPropSet {
 public:
    uint8_t pad00[0x130];
    void*   mpProps_130;                                         // +0x130
};

class cSporeNounManager {
 public:
    IWin* FUN_00daed70();                                        // 0x00daed70
};

class cPlanetModel {
 public:
    double FUN_00b7e4d0();                                       // 0x00b7e4d0
    char   RayCast(float* ray);                                  // 0x00b88770
    char   FUN_00b88f60(float dist, float* from, float* out);    // 0x00b88f60
};

// The object embedded at creature+0xc0 (cLocomotiveObject).  In 00db2fd0 slot
// +0x2c is a plain getter; the 00db33d0 call sites pass arguments, so both
// views are declared and the caller picks the one that matches.
class cSimLoco {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual void* pv11(float a, void* b, float c, int d, int e); // +0x2c
    virtual void* pv12();                                        // +0x30

    char IsNearGoal();                                           // 0x00c42e20
};

// ---------------------------------------------------------------------------
// Creature base.  The COM methods inherited from IWin live in its vtable; the
// extra members are ordinary this-call helpers.
// ---------------------------------------------------------------------------
class cSPCreatureBase : public IWin {
 public:
    void* PlayAnimation(int animId, int a, int b);               // 0x00c12190
    char  WaitForAnimEventOrEnd(int ev, int* out, int a, int anim, int b); // 0x00c14ef0
    char  AnimationFinished(int anim);                           // 0x00c12400
    void  SetCurrentToolEffect(int a, int b);                    // 0x00c24f40
    void  FUN_00c196a0(void* a, int b, int c);                   // 0x00c196a0
    void  MoveToPointAndFacingAtSpeed(int a, void* b, float c, float d); // 0x00c1c5c0
    void* InterruptAnimation(int a, int b, int c);               // 0x00c12310
    void* FUN_00c22820();                                        // 0x00c22820
    void  FUN_00c26310(int a);                                   // 0x00c26310

    uint8_t pad00[0xbc];                                         // IWin's vptr occupies +0x00..+0x04
    cSimLoco mLoco_c0;                                           // +0xc0
};

// EA::Swarm::cIVisualEffect reference used by the simulation state.
class cVisualEffect {
 public:
    PV(0)
    virtual void Release();                                      // +0x04
    virtual void pv02(int a);                                    // +0x08
    virtual char pv04();                                         // +0x10
    PV(5)
    virtual void pv06(void* msg);                                // +0x18
};

class cEffectsManager {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual char AddEffect(int id, int a, void* out);             // +0x2c
};

// EA::XformMsg -- the transform message posted to the effect object.
class XformMsg {
 public:
    XformMsg();                                                  // 0x00434040
    void FUN_00571d40(const float* pos);                         // 0x00571d40

    uint16_t mFlags_00;                                          // +0x00
    uint16_t mCount_02;                                          // +0x02
    uint8_t  pad04[0x0c];                                        // +0x04
    float    mScale_10;                                          // +0x10
    float    mMatrix_14[9];                                      // +0x14
};

// --- free helpers and callees ---------------------------------------------
void* FUN_00f473a0(uint32_t size, const char* name, int a, uint32_t b,
                   const char* file, int line);                  // 0x00f473a0
void  FUN_00f47380(void* p);                                     // 0x00f47380
void  FUN_00da61e0(void* a, int b);                              // 0x00da61e0
void  FUN_00da6240(void* a, uint32_t b, int c);                  // 0x00da6240
float GetPropertyT_float(void* mgr, uint32_t id, float def);     // 0x004e1c70
cPlanetModel* FUN_00b3d350();                                    // 0x00b3d350
cSporeNounManager* NounManager();                                // 0x00b3d300
cEffectsManager* EffectsManagerPtr();                            // 0x0067ddd0
void  SpawnLocatingCallResponse(void* a, void* b);               // 0x00d38cc0
char  Vector3_NotEqual(const float* a, const float* b);          // 0x0041dd30
float* normalized_safe(float* out, const float* in);             // 0x00449c20
float* Matrix3FromFacingAndUp(float* out, const float* facing,
                              const float* up);                  // 0x0069b440
void   Matrix3FromQuaternion(float* out, const float* q);        // 0x0059c190

// ---------------------------------------------------------------------------
// cResizableObjectPoolT<SP::cGroupMovement>
//
// A slot is kPoolSlotStride bytes: a 4 byte link word (bit 31 set while the
// slot is on the free list, bits 0..29 the index of the next free slot)
// followed by the object itself.
// ---------------------------------------------------------------------------
class cGroupMovement {
 public:
    virtual void FUN_vtbl0(int a);                               // +0x00
};

struct cPoolSlotBits {
    uint32_t mNext : 30;                                         // index of next free slot
    uint32_t mUsed : 1;                                          // +0x1e
    uint32_t mFree : 1;                                          // +0x1f
};

struct cPoolSlot {
    union {
        uint32_t      mLink_00;                                  // +0x00
        cPoolSlotBits mBits;
    };
    cGroupMovement mObject;                                      // +0x04
};

struct cPoolNode {
    union {
        cPoolNode* mpFreeLink_00;                                // +0x00 free-list link
        uint32_t   mValue_00;                                    // +0x00 payload
    };
    uint32_t   mValue_04;                                        // +0x04
    uint32_t   mValue_08;                                        // +0x08
    uint32_t   mValue_0c;                                        // +0x0c
    cPoolNode* mpNext_10;                                        // +0x10
};

// out-parameter of cResizableObjectPoolT::FindFreeSlot.
struct cPoolFind {
    cPoolNode* mpNode_00;                                        // +0x00
    cPoolNode** mpSlot_04;                                       // +0x04
};

class cResizableObjectPoolT {
 public:
    cGroupMovement* GetObject(uint32_t index);                   // 0x00db3c40
    void  ReleaseSlot(uint32_t index);                           // 0x00db3c90
    cPoolFind* FindFreeSlot(cPoolFind* out, cPoolNode* node,
                            cPoolNode** head);                   // 0x00db3da0
    void  AllocNode(cPoolNode* src);                             // 0x00db3e30
    uint32_t FUN_00daed20(uint32_t index);                       // 0x00daed20

    uint8_t*       mpBegin_00;                                   // +0x00
    uint8_t*       mpEnd_04;                                     // +0x04
    uint8_t        pad08[4];                                     // +0x08
    int32_t        mCount_0c;                                    // +0x0c
    uint8_t        pad10[4];                                     // +0x10
    uint32_t       mIndex_14;                                    // +0x14
    uint32_t       mFreeHead_18;                                 // +0x18
    cPoolNode*     mpFreeList_1c;                                // +0x1c
    uint8_t        pad20[4];                                     // +0x20
    cPoolNode*     mpDeleteBegin_24;                             // +0x24
    cPoolNode*     mpDeleteEnd_28;                               // +0x28
    uint32_t       mNodeSize_2c;                                 // +0x2c
    cPoolNode*     mpSentinel_30;                                // +0x30
};

// @ 0x00db3c40
cGroupMovement* cResizableObjectPoolT::GetObject(uint32_t index)
{
    uint32_t i = index & 0xbfffffff;
    int32_t  count = (int32_t)(mpEnd_04 - mpBegin_00) / kPoolSlotStride;

    if (i < (uint32_t)count)
    {
        bool free = ((cPoolSlot*)(mpBegin_00 + i * kPoolSlotStride))->mBits.mFree;
        if (!free)
            return &((cPoolSlot*)(mpBegin_00 + i * kPoolSlotStride))->mObject;
    }
    return 0;
}

// @ 0x00db3c90
void cResizableObjectPoolT::ReleaseSlot(uint32_t index)
{
    cPoolSlot* slot = (cPoolSlot*)(mpBegin_00 + index * kPoolSlotStride);

    slot->mObject.FUN_vtbl0(0);
    slot->mLink_00 = (slot->mLink_00 & 0xc0000000) |
                     (mFreeHead_18 & 0x3fffffff) | 0x80000000;
    mFreeHead_18 = index;
    if (mIndex_14 == index)
        mIndex_14 = FUN_00daed20(index);
}

// @ 0x00db3da0
cPoolFind* cResizableObjectPoolT::FindFreeSlot(cPoolFind* out, cPoolNode* node,
                                               cPoolNode** head)
{
    cPoolNode* p = node->mpNext_10;
    out->mpSlot_04 = head;
    out->mpNode_00 = p;
    while (p == 0)
    {
        out->mpSlot_04 += 1;
        p = *out->mpSlot_04;
        out->mpNode_00 = p;
    }

    cPoolNode* cur = *head;
    if (cur == node)
    {
        // cur == node here; the free-list head is unlinked in one step.
        *head = node->mpNext_10;
    }
    else
    {
        cPoolNode* prev = cur;
        cPoolNode* q = prev->mpNext_10;
        while (q != node)
        {
            prev = q;
            q = prev->mpNext_10;
        }
        prev->mpNext_10 = q->mpNext_10;
    }

    if (node != mpSentinel_30)
    {
        if (node >= mpDeleteBegin_24 && node < mpDeleteEnd_28)
        {
            node->mpFreeLink_00 = mpFreeList_1c;
            mpFreeList_1c = node;
            mCount_0c--;
            return out;
        }
        FUN_00f47380(node);
    }
    mCount_0c--;
    return out;
}

// @ 0x00db3e30
void cResizableObjectPoolT::AllocNode(cPoolNode* src)
{
    cPoolNode* node = mpFreeList_1c;

    if (node != 0)
        mpFreeList_1c = node->mpFreeLink_00;
    else
    {
        uint32_t size = mNodeSize_2c;
        node = (cPoolNode*)FUN_00f473a0(size, kAllocTag, 0, 0, kAllocFile, 0xd1);
    }

    if (node != 0)
    {
        node->mValue_00 = src->mValue_00;
        node->mValue_04 = src->mValue_04;
        node->mValue_08 = src->mValue_08;
        node->mValue_0c = src->mValue_0c;
    }
    node->mpNext_10 = 0;
}

// ---------------------------------------------------------------------------
// SP::REACT_TO_TARGET state block: the block is reached as the 6th argument.
// ---------------------------------------------------------------------------
struct REACT_State {
    IWin*            mpObj_00;                                   // +0x00 target
    int32_t          mPhase_04;                                  // +0x04 phase 0..6
    int32_t          mAnim_08;                                   // +0x08 animation handle
    AutoRefCountText mText_0c;                                   // +0x0c <IWinText> reference
};

// @ 0x00db2fd0
char FUN_00db2fd0(cSPCreatureBase* creature, void* a2, void* a3, void* a4,
                  void* a5, REACT_State* state)
{
    switch (state->mPhase_04)
    {
    case 0:
    {
        creature->FUN_00c196a0(state->mpObj_00, 1, 0);
        FUN_00da61e0(creature, 0x16);
        creature->pv45(state->mpObj_00);
        state->mAnim_08 = (int)creature->PlayAnimation(0x60db980, 1, -1);
        state->mPhase_04 = 1;
        break;
    }
    case 1:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0xe95450e, &out, 0, state->mAnim_08, 1))
        {
            creature->SetCurrentToolEffect(0, out);
            state->mPhase_04 = 2;
            return 1;
        }
        break;
    }
    case 2:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0x81d12704, &out, 0, state->mAnim_08, 1))
        {
            IWin* text = NounManager()->FUN_00daed70();
            state->mText_0c = text;
            IWin* sub = (IWin*)((char*)text + 0x34);
            IWin* loco = (IWin*)&creature->mLoco_c0;

            float t = (float)loco->pv28();
            t = t + (float)sub->pv28();

            Vector3f probe;
            float* dir = (float*)loco->pv23(&probe.x);
            Vector3f off;
            off.x = dir[0] * t;
            off.y = dir[1] * t;
            off.z = dir[2] * t;

            float* base = (float*)loco->pv11();
            Vector3f vec;
            vec.x = off.x + base[0];
            vec.y = off.y + base[1];
            vec.z = off.z + base[2];

            text->FUN_00bcb960(0);
            sub->pv14(&vec);
            sub->pv33();
            state->mPhase_04 = 3;
            return 1;
        }
        break;
    }
    case 3:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0xbfa50b5a, &out, 0, state->mAnim_08, 1))
        {
            IWin* text = state->mText_0c.mpRef;
            text->FUN_00bcb960(1);
            ((IWin*)((char*)text + 0x34))->pv33();
            state->mPhase_04 = 4;
            return 1;
        }
        break;
    }
    case 4:
    {
        if (creature->AnimationFinished(state->mAnim_08))
        {
            void* a = creature->FUN_00c22820();
            state->mAnim_08 = (int)creature->PlayAnimation(0x2c39200, 1, (int)a);
            state->mPhase_04 = 5;
            return 1;
        }
        break;
    }
    case 5:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0x7d7502fc, &out, 0, state->mAnim_08, 1))
        {
            creature->FUN_00c26310(out);
            state->mPhase_04 = 6;
            return 1;
        }
        break;
    }
    case 6:
    {
        if (creature->AnimationFinished(state->mAnim_08))
        {
            IWin* text = state->mText_0c.mpRef;
            text->FUN_00bcb960(2);
            text->FUN_00bcc010();
            FUN_00da6240(creature, 0x10000000, 0);
            return 0;
        }
        break;
    }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// SP::cGalaxyGameEntryImpl::HandleSimulationUpdate state block.
// ---------------------------------------------------------------------------
struct SimuState {
    IWin*   mpObj_00;                                            // +0x00
    int32_t mPhase_04;                                           // +0x04 phase 0, 2..9
    float   mPos_08[3];                                          // +0x08 destination
    int32_t mAnim_14;                                            // +0x14 animation handle
    IWin*   mpEffect_18;                                         // +0x18 visual effect
};

// @ 0x00db3390
void FUN_00db3390(cSPCreatureBase* a1, void* a2, void* a3, void* a4, void* a5,
                  SimuState* state)
{
    if (state->mpEffect_18 != 0)
    {
        state->mpEffect_18->pv03(0);
        if (state->mpEffect_18 != 0)
        {
            IWin* old = state->mpEffect_18;
            state->mpEffect_18 = 0;
            old->Release();
        }
    }
    if (state->mpEffect_18 != 0)
        state->mpEffect_18->Release();
}

// @ 0x00db33d0
char FUN_00db33d0(cSPCreatureBase* creature, void* a2, void* a3, void* a4,
                  void* a5, SimuState* state)
{
    cSimLoco* loco = &creature->mLoco_c0;

    switch (state->mPhase_04)
    {
    case 0:
    {
        creature->FUN_00c196a0(state->mpObj_00, 1, 0);
        FUN_00da61e0(creature, 0x16);

        cPropSet* prop = creature->pv45(state->mpObj_00);
        float v1 = GetPropertyT_float(prop->mpProps_130, 0xc492c89f, kPropDefaultA);
        float v2 = GetPropertyT_float(prop->mpProps_130, 0x191dcad8, kPropDefaultB);
        float range = (float)(FUN_00b3d350()->FUN_00b7e4d0() * v2 * kSpeedScale);
        cPlanetModel* pm = FUN_00b3d350();

        Vector3f probe;
        Vector3f dest;
        Vector3f hit;

        float* pos = (float*)loco->pv11(v1, &probe.x, 1.0f, 1, (int)range);
        if (pm->RayCast(pos))
        {
            if (pm->RayCast(&dest.x))
            {
                Vector3f normal;
                if (!pm->FUN_00b88f60(v2, &hit.x, &normal.x))
                {
                    Vector3f delta;
                    delta.x = hit.x - dest.x;
                    delta.y = hit.y - dest.y;
                    delta.z = hit.z - dest.z;
                    float* n = normalized_safe(&normal.x, &delta.x);
                    normal.x = n[0];
                    normal.y = n[1];
                    normal.z = n[2];
                }

                Vector3f back;
                back.x = -normal.x;
                back.y = -normal.y;
                back.z = -normal.z;

                state->mPos_08[0] = back.x * v2 + hit.x;
                state->mPos_08[1] = back.y * v2 + hit.y;
                state->mPos_08[2] = back.z * v2 + hit.z;

                void* p = loco->pv11(1.0f, &back.x, kProbeStep, 0, 0);
                creature->MoveToPointAndFacingAtSpeed(2, p, 1.0f, 2.0f);
            }
        }

        void* anim = creature->FUN_00c22820();
        state->mAnim_14 = (int)creature->InterruptAnimation(0x6006755, (int)anim, 0);
        state->mPhase_04 = 2;
        return 1;
    }
    case 2:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0xe95450e, &out, 0, state->mAnim_14, 1))
        {
            creature->SetCurrentToolEffect(0, out);
            state->mAnim_14 = (int)creature->PlayAnimation(0x6006752, 1, -1);
            state->mPhase_04 = 3;
            return 1;
        }
        break;
    }
    case 3:
    {
        // Walk to the goal until the animation ends and the loco is close enough.
        if (!loco->IsNearGoal() || !creature->AnimationFinished(state->mAnim_14))
            break;

        IWin* goal = state->mpObj_00;
        cPropSet* prop = creature->pv45(state->mpObj_00);
        float v2 = GetPropertyT_float(prop->mpProps_130, 0x84f97568, kPropDefaultB);

        float* cur = (float*)((IWin*)loco)->pv11();
        float dx = state->mPos_08[0] - cur[0];
        float dy = state->mPos_08[1] - cur[1];
        float dz = state->mPos_08[2] - cur[2];

        // Inside the arrival radius of the goal, and the goal is a real position.
        if (Vector3_NotEqual(state->mPos_08, &kInvalidPos) &&
            v2 * v2 <= dx * dx + dy * dy + dz * dz)
        {
            SpawnLocatingCallResponse(creature, state->mPos_08);

            // Effect 0xa86f8d7e: place the "travelling" visual effect at the goal
            // position, oriented by the loco's current quaternion.
            cEffectsManager* fx = EffectsManagerPtr();
            if (fx->AddEffect(0xa86f8d7e, 0, state->mpEffect_18))
            {
                XformMsg msg;
                msg.FUN_00571d40(state->mPos_08);
                float mat[9];
                Matrix3FromQuaternion(mat, (float*)loco->pv12());
                for (int i = 0; i < 9; i++)
                    msg.mMatrix_14[i] = mat[i];
                msg.mFlags_00 |= 2;
                msg.mCount_02 = msg.mCount_02 + 2;
                msg.mScale_10 = 1.0f;
                state->mpEffect_18->pv06(&msg);
                state->mpEffect_18->pv02(0);
            }

            // Effect 0x6d8f14ef: second visual effect, anchored on the loco.
            cEffectsManager* fx2 = EffectsManagerPtr();
            if (fx2->AddEffect(0x6d8f14ef, 0, state->mpEffect_18))
            {
                XformMsg msg;
                msg.FUN_00571d40((float*)((IWin*)loco)->pv11());
                float mat[9];
                Matrix3FromQuaternion(mat, (float*)loco->pv12());
                for (int i = 0; i < 9; i++)
                    msg.mMatrix_14[i] = mat[i];
                msg.mFlags_00 |= 2;
                msg.mCount_02 = msg.mCount_02 + 2;
                msg.mScale_10 = 1.0f;
                goal->pv06(&msg);
                state->mpEffect_18->pv02(0);
            }

            void* anim = creature->FUN_00c22820();
            state->mAnim_14 = (int)creature->PlayAnimation(0x60ca7f9, 1, (int)anim);
            state->mPhase_04 = 4;
            if (goal != 0)
            {
                goal->Release();
                return 1;
            }
        }
        break;
    }
    case 4:
    {
        if (creature->AnimationFinished(state->mAnim_14))
        {
            state->mPhase_04 = 5;
            return 1;
        }
        break;
    }
    case 5:
    {
        if ((state->mpEffect_18 == 0 || !state->mpEffect_18->pv04()) &&
            creature->AnimationFinished(state->mAnim_14))
        {
            void* anim = creature->FUN_00c22820();
            state->mAnim_14 = (int)creature->PlayAnimation(0x60ca7fb, 1, (int)anim);
            state->mPhase_04 = 6;
            return 1;
        }
        break;
    }
    case 6:
    {
        if (creature->AnimationFinished(state->mAnim_14))
        {
            void* anim = creature->FUN_00c22820();
            state->mAnim_14 = (int)creature->PlayAnimation(0x609ea41, 1, (int)anim);
            state->mPhase_04 = 8;
        }
        break;
    }
    case 7:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0xe95450e, &out, 0, state->mAnim_14, 1))
        {
            creature->SetCurrentToolEffect(0, out);
            state->mPhase_04 = 8;
            return 1;
        }
        break;
    }
    case 8:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0x7d7502fc, &out, 0, state->mAnim_14, 1))
        {
            creature->FUN_00c26310(out);
            state->mPhase_04 = 9;
            return 1;
        }
        break;
    }
    case 9:
    {
        if (creature->AnimationFinished(state->mAnim_14))
        {
            FUN_00da6240(creature, 0x10000000, 0);
            return 0;
        }
        break;
    }
    }
    return 1;
}