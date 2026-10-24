// slice s00638e90: cSPPlayModeSubModeAction (Spore creature-editor play-mode action).
// Two spellings of the same layout exist in the PDB: SP::cSPPlayModeSubModeAction (five of the
// functions here) and the global ::cSPPlayModeSubModeAction (FUN_00639350, FUN_00639b70).
#include "../s00636320/s00636320.h"
#include <intrin.h>

typedef unsigned int uint32;

// ---------------------------------------------------------------------------
// vtable dispatch helpers (vptr access through these macros is accepted)
// ---------------------------------------------------------------------------
typedef void  (__thiscall *T0)(void*);
typedef void  (__thiscall *T1)(void*, void*);
typedef void  (__thiscall *T2)(void*, void*, int);
typedef void  (__thiscall *T3)(void*, void*, int, int);
typedef void  (__thiscall *T4)(void*, void*, int, int, void*);
typedef int   (__thiscall *TVT4)(void*, void*, int, int, void*);
typedef float (__thiscall *T5f)(void*, uint32, uint32, int, int, int);

#define VTSLOT(o, off)  (*(void**)((char*)(*(void**)o) + (off)))
#define F(x)            (*(float*)&(x))

// ---------------------------------------------------------------------------
// Externals (hex-named for the ones only reachable by address)
// ---------------------------------------------------------------------------
extern "C" float* FUN_0059aed0(void*, float*, void*);        // 0x0059aed0 Vector3MatrixMul
extern "C" void   FUN_0059cf00(uint32, float, float, float, int, int);  // 0x0059cf00
extern "C" void   FUN_0059cea0(uint32, float, int);          // 0x0059cea0
extern "C" void   FUN_0059cfb0(uint32, float, float, float, int);       // 0x0059cfb0
extern "C" void   FUN_0059d110(uint32, float*);              // 0x0059d110
extern "C" float  FUN_0069b760(void*, void*, void*, int);     // 0x0069b760
extern "C" void   FUN_0059cbd0(void*);                       // 0x0059cbd0
extern "C" void   FUN_00583900(void);                        // 0x00583900
extern "C" int    FUN_009322b0(void*);                       // 0x009322b0
extern "C" int    FUN_00932960(void*);                       // 0x00932960
extern "C" void   FUN_00635350(int, int);                    // 0x00635350
extern "C" void*  FUN_00a04ad0(int);                         // 0x00a04ad0
extern "C" void   FUN_009d3f70(int);                         // 0x009d3f70
extern "C" void   FUN_009ce720(void*, void*);                // 0x009ce720
extern "C" void   FUN_00a006f0(void*);                       // 0x00a006f0

namespace SP {
int* AssetBrowser();                        // 0x00401030 GetSetting3-ish helper
int* SporeGuide();                          // 0x00401040 GetSetting4-ish helper
}

extern uint32 DAT_015f82b8;   // 0x015f82b8
extern uint32 DAT_015f82bc;   // 0x015f82bc
extern uint32 DAT_015f82c0;   // 0x015f82c0
extern uint32 DAT_015f8264;   // 0x015f8264
extern uint32 DAT_015f8268;   // 0x015f8268
extern uint32 DAT_015f826c;   // 0x015f826c
extern uint32 DAT_015f823c;   // 0x015f823c
extern uint32 DAT_015f81b4;   // 0x015f81b4
extern uint32 DAT_01523e7c;   // 0x01523e7c
extern uint32 DAT_01523e80;   // 0x01523e80
extern uint32 DAT_01523e84;   // 0x01523e84
extern uint32 DAT_01523e88;   // 0x01523e88
extern uint32 DAT_01523e8c;   // 0x01523e8c
extern uint32 DAT_01523b74[64];          // 0x01523b74 anim-id table
extern unsigned char DAT_013ec468;       // 0x013ec468
extern uint32 DAT_013fec0c;   // 0x013fec0c float 2.0f
extern uint32 DAT_013fec10;   // 0x013fec10 float 4.0f
extern uint32 DAT_013f0e84;   // 0x013f0e84 float 400.0f

// ---------------------------------------------------------------------------
// Layouts of the sub objects touched
// ---------------------------------------------------------------------------
struct cAnimatingCreature {
    unsigned char mPad00[0x10];                 // +0x00
    float         mRotation[3];                 // +0x10
    unsigned char mPad1C[0x154 - 0x1C];         // +0x1c
    uint32        mField154;                    // +0x154
    unsigned char mPad158[0x164 - 0x158];       // +0x158
    uint32        mField164;                    // +0x164
    uint32        mField168;                    // +0x168
    uint32        mField16C;                    // +0x16c
    unsigned char mPad170[0x17c - 0x170];       // +0x170
    int*          mIndex;                       // +0x17c
    unsigned char mPad180[0x184 - 0x180];       // +0x180
    void*         mField184;                    // +0x184
};

struct cSPPlayMode {
    unsigned char mPad00[0x14];                 // +0x00
    float         mSleepEffectObject;           // +0x14
    float         mIdleTime;                    // +0x18
    unsigned char mSleepAnimChangeTime;         // +0x1c
    unsigned char mPad1D[0x5d - 0x1d];          // +0x1d
    void*         mShadowViewer;                // +0x5d
    void ForceBabiesToIdle(int n);              // 0x006296e0
    void SetAllBabyPhotoModes(int n);           // 0x006288a0
};

// view of the editor base with the fields this slice touches
struct cAppModeEditorBaseV {
    unsigned char mPad00[0x78];
    void*         mpEditorUI;                   // +0x78
    unsigned char mPad7C[0x84 - 0x7C];
    void*         mSaveModelWorld;              // +0x84
    unsigned char mPad88[0x358 - 0x88];
    void*         mShadowViewer;                // +0x358
};

struct cSPEditorAnimatedCreatureManager {
    void SetCreatureSpeeds(uint32 id, float a, float b);   // 0x0059d0b0
    void SetCreatureIsTurning(uint32 id, int on);          // 0x0059cee0
};

// alias spellings used by the PDB for the same layout
namespace SP {
struct cAnimatingCreature_s0063_7f80;
struct cSPPlayModeAnimation;                    // anim object; only its vptr is used
}

// ---------------------------------------------------------------------------
// The shared layout.  field offsets come from the original disassembly.
// ---------------------------------------------------------------------------
struct cSPPlayModeSubModeActionLayout {
    virtual void FUN_vtbl0();                   // +0x00 placeholder (forces the vfptr at offset 0)
    cAppModeEditorBaseV* mEditorBaseMode;       // +0x04
    SP::cSPPlayModeAnimation* mAnim;            // +0x08
    int           mField0C;                     // +0x0c
    cSPPlayMode*  mPlayMode;                    // +0x10
    unsigned char mPad14[6];                    // +0x14
    unsigned char mIsWalking;                   // +0x1a
    unsigned char mPad1B[0x38 - 0x1B];          // +0x1b
    void*         mObj38;                       // +0x38
    int           mField3C;                     // +0x3c
    float         mKeyClickTime;                // +0x40
    void*         mObj44;                       // +0x44
    cSPEditorAnimatedCreatureManager* mAnimCreatureMgr;  // +0x48
    uint32        mCreatureID;                  // +0x4c
    cAnimatingCreature* mAnimCreature;          // +0x50
    void*         mAlloc54;                     // +0x54
    unsigned char mPad58[0x68 - 0x58];          // +0x58
    int           mCurrIdleAnimState;           // +0x68
    unsigned char mPad6C[0x88 - 0x6C];          // +0x6c
    int           mLastBoredAnimID;             // +0x88
    uint32        mIdleAnimTimer;               // +0x8c
    float         mRandomIdleTimer;             // +0x90
    float         mRandomIdleSwitchTimer;       // +0x94
    float         mQueuedBoredAnimID;           // +0x98
    unsigned char mMouthBidx;                   // +0x9c
    unsigned char mPad9D[0xdc - 0x9D];          // +0x9d
    unsigned char mKeyInputButtonState[6];      // +0xdc .. +0xe1
    unsigned char mPadE2[0x10c - 0xE2];         // +0xe2
    void*         mObj10C;                      // +0x10c
    unsigned char mPad110[0x200 - 0x110];       // +0x110  (tail; this[1] begins at +0x200)
    uint32        mNextVftable;                 // +0x200
    uint32        mNextEditorBaseMode;          // +0x204
    uint32        mNextCounter;                 // +0x208 (mAnim slot of this[1])
};

// namespace-scoped class: HasRequiredPart / SetIdleAnimation / StartBoredAnimation /
// MarkKeyInputKeyDown / CaptureGIF
namespace SP {

struct cSPPlayModeSubModeAction : cSPPlayModeSubModeActionLayout {
    bool  HasRequiredPart(uint32 unused);
    float SetIdleAnimation(cAnimatingCreature* creature, uint32 id, bool a, bool b);
    void  StartBoredAnimation(uint32 t);
    void  MarkKeyInputKeyDown(uint32 idx);
    void  CaptureGIF();
};

struct cSPPlayModeUI {
    static void SetEnabled(uint32 id, int on);
    static void SetEnableTakePictureButton(int on);
    static void SetEnableRecordMovieButton(int on);
};

} // namespace SP

// global class: FUN_00639350 / FUN_00639b70 (destructor)
struct cSPPlayModeSubModeAction : cSPPlayModeSubModeActionLayout {
    void FUN_00639350();
    void FUN_00639b70();
};

// sibling-scope aliases referenced by the original call sites
namespace SP {

struct cSPPlayModeSubModeAction_s0063_7f80 : cSPPlayModeSubModeActionLayout {
    bool AnyKeyDown();                                          // 0x006389b0
    void SetWalkAnimation(cAnimatingCreature* c, uint32 id);    // 0x006388e0
};

} // namespace SP

// cSPPlayMode::WakeupCreature is a free function in the original
extern "C" void WakeupCreature(cSPPlayMode* mode);              // 0x0062a760

// ---------------------------------------------------------------------------
// 0x00638e90  SP::cSPPlayModeSubModeAction::HasRequiredPart
// ---------------------------------------------------------------------------
// @ 0x00638E90
bool SP::cSPPlayModeSubModeAction::HasRequiredPart(uint32)
{
    int* idx = mAnimCreature->mIndex;
    int  local_40c = 0;
    int  local_408 = 0x74756f6d;
    int  local_404 = 0;
    int  local_400 = 0;
    unsigned char bufA[0x3c4];
    unsigned char bufB[0x14];
    unsigned char bufC[0x14];

    ((TVT4)VTSLOT(mAnimCreature, 0x74))(mAnimCreature, bufA, 0xff, *idx, &local_40c);
    int iVar2 = ((TVT4)VTSLOT(mAnimCreature, 0x74))(mAnimCreature, bufB, 0xff, *idx, &local_40c);
    int iVar3 = ((TVT4)VTSLOT(mAnimCreature, 0x74))(mAnimCreature, bufC, 0xff, *idx, &local_400);

    int kind = *(int*)(bufA + 0x3c4 - 0x30);
    switch (kind) {
    case 1:
    case 0xb:
    case 0xe:
        break;
    case 10:
        return true;
    case 0xc:
    case 0xd:
        if (iVar2 != 0)
            return true;
        break;
    case 0xf:
        if (iVar2 != 0 && iVar3 != 0)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00638fd0  SP::cSPPlayModeSubModeAction::SetIdleAnimation
// ---------------------------------------------------------------------------
// @ 0x00638FD0
float SP::cSPPlayModeSubModeAction::SetIdleAnimation(cAnimatingCreature* creature, uint32 id,
                                                     bool param_4, bool param_5)
{
    uint32 animId = 0x4330667u;
    float  fStack_8;
    uint32 local_20 = 1;
    uint32 local_18, local_14, local_10;
    float  local_c[3];

    if (creature == mAnimCreature)
        mCurrIdleAnimState = 0;

    cAnimatingCreature* pcVar3 = creature;
    int  mIndexed = 0;
    int  local_1c = 0;
    if (pcVar3 != 0) {
        FUN_00a04ad0(0);
        FUN_009d3f70((int)pcVar3->mIndex + 0x15b8);
        FUN_009ce720(&mIndexed, &local_1c);
    }

    local_18 = DAT_015f82b8 ^ 0x80000000u;
    local_14 = DAT_015f82bc ^ 0x80000000u;
    local_10 = DAT_015f82c0 ^ 0x80000000u;
    float* pfVar4 = FUN_0059aed0(local_c, (float*)&local_18, mAnimCreature->mRotation);

    float dot = 0.0f;
    if (pcVar3 != 0)
        dot = ((float*)pcVar3->mIndex)[0x7c / 4] * pfVar4[2]
            + ((float*)pcVar3->mIndex)[0x78 / 4] * pfVar4[1]
            + ((float*)pcVar3->mIndex)[0x74 / 4] * pfVar4[0];

    bool secondPath = (mIndexed == 2) && (dot > F(DAT_01523e88));

    if (!secondPath) {
        if (param_4) {
            uint32 n = 9;
            if (mPlayMode->mSleepEffectObject <= 15.0f)
                n = 4;
            (void)n;
            do {
                switch (n & 0) {
                case 0: animId = 0x4112345u; break;
                case 1: animId = 0x411238eu; break;
                case 2: animId = 0x41123a5u; break;
                case 3: animId = 0x44d7f20u; break;
                case 4: animId = 0x407986cu; break;
                case 5: animId = 0x4079862u; break;
                case 6: animId = 0x4079874u; break;
                case 7: animId = 0x4079879u; break;
                case 8: animId = 0x4330317u; break;
                }
                break;
            } while (mLastBoredAnimID == (int)animId);
            mLastBoredAnimID = (int)animId;
            if (pcVar3 != 0) {
                pcVar3->mField154 = 1;
                pcVar3->mField164 = DAT_01523e7c;
                pcVar3->mField168 = DAT_01523e80;
                pcVar3->mField16C = DAT_01523e84;
            }
        }
    }
    else {
        local_20 = 0;
    }

    uint32 uVar7 = id;
    SP::cSPPlayModeAnimation* pcVar2 = mAnim;
    if (!param_5) {
        fStack_8 = ((T5f)VTSLOT(pcVar2, 0xc))(pcVar2, id, animId, (int)local_20, 1, 0);
    }
    else {
        int zero = 0;
        fStack_8 = ((T5f)VTSLOT(pcVar2, 0xc))(pcVar2, id, animId, (int)local_20, 0, (int)&zero);
        if (pcVar3 != 0 && pcVar3->mField184 != 0)
            FUN_00a006f0(&zero);
    }

    if (local_10 == 2) {
        int zero = 0;
        ((T5f)VTSLOT(mAnim, 0xc))(mAnim, uVar7, 0x4330667u, 1, 0, (int)&zero);
        if (pcVar3 != 0 && pcVar3->mField184 != 0)
            FUN_00a006f0(&zero);
        if (local_10 == 2) {
            if (pcVar3 != mAnimCreature)
                return fStack_8;
            mRandomIdleTimer = -(float)mQueuedBoredAnimID;
            mRandomIdleSwitchTimer = fStack_8;
            return fStack_8;
        }
    }
    return fStack_8;
}

// ---------------------------------------------------------------------------
// 0x006392e0  SP::cSPPlayModeSubModeAction::StartBoredAnimation
// ---------------------------------------------------------------------------
// @ 0x006392E0
void SP::cSPPlayModeSubModeAction::StartBoredAnimation(uint32 t)
{
    float r = ((T5f)VTSLOT(mAnim, 0xc))(mAnim, mCreatureID, t, 0, 1, 0);
    mIdleAnimTimer = t;
    SetIdleAnimation(mAnimCreature, mCreatureID, false, true);
    mPlayMode->mIdleTime = mPlayMode->mSleepEffectObject + r + 7.0f;
    mPlayMode->mSleepAnimChangeTime = 1;
    mQueuedBoredAnimID = 0.0f;
}

// ---------------------------------------------------------------------------
// 0x006398f0  SP::cSPPlayModeSubModeAction::MarkKeyInputKeyDown
// ---------------------------------------------------------------------------
// @ 0x006398F0
void SP::cSPPlayModeSubModeAction::MarkKeyInputKeyDown(uint32 idx)
{
    if (mKeyInputButtonState[idx] == 0) {
        mKeyInputButtonState[idx] = 1;
        if (mKeyClickTime <= 0.0f || 400.0f <= mKeyClickTime) {
            mKeyClickTime = 0.0f;
            if (mEditorBaseMode->mSaveModelWorld != 0 && mAnimCreatureMgr != 0) {
                mAnimCreatureMgr->SetCreatureSpeeds(mCreatureID, F(DAT_013fec0c), F(DAT_015f81b4));
                mCurrIdleAnimState = 1;
            }
        }
        else if (mEditorBaseMode->mSaveModelWorld != 0 && mAnimCreatureMgr != 0) {
            mAnimCreatureMgr->SetCreatureSpeeds(mCreatureID, F(DAT_013fec10), F(DAT_015f81b4));
            mCurrIdleAnimState = 2;
        }

        if (mKeyInputButtonState[2] || mKeyInputButtonState[0] || mKeyInputButtonState[1] ||
            mKeyInputButtonState[3] || mKeyInputButtonState[4] || mKeyInputButtonState[5]) {
            WakeupCreature(mPlayMode);
            mPlayMode->ForceBabiesToIdle(-1);
            mPlayMode->SetAllBabyPhotoModes(0);
            ((SP::cSPPlayModeSubModeAction_s0063_7f80*)this)->SetWalkAnimation(mAnimCreature,
                                                                              mCreatureID);
            mIsWalking = 1;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00639a10  SP::cSPPlayModeSubModeAction::CaptureGIF
// ---------------------------------------------------------------------------
// @ 0x00639A10
void SP::cSPPlayModeSubModeAction::CaptureGIF()
{
    if (FUN_009322b0((void*)&DAT_013ec468) == 0) {
        if (FUN_00932960((void*)&DAT_013ec468) == 0) {
            SP::cSPPlayModeUI::SetEnabled(0x58b74e8, 1);
            return;
        }
    }

    mNextCounter = 0;
    FUN_00635350(0, 1);
    SP::cSPPlayModeUI::SetEnableTakePictureButton(0);
    SP::cSPPlayModeUI::SetEnableRecordMovieButton(0);
    int iv = 0;                        // cDirectPropertyList::GetIntProperty(0x5d2e91b)
    uint32 animId;
    if (iv == 0) {
        if (0xd < (int)mNextCounter)
            mNextCounter = 0;
        uint32 c = mNextCounter;
        animId = DAT_01523b74[c];
        mNextCounter = c + 1;
    }
    else {
        animId = DAT_01523b74[(iv - 1u) % 0xe];
    }
    if (mCurrIdleAnimState != 0)
        mMouthBidx = 1;
    FUN_0059cbd0(mEditorBaseMode->mShadowViewer);
    ((T5f)VTSLOT(mAnim, 0xc))(mAnim, mCreatureID, animId, 0, 1, 0);
    FUN_00583900();
}

// ---------------------------------------------------------------------------
// 0x00639350  ::cSPPlayModeSubModeAction::FUN_00639350
// ---------------------------------------------------------------------------
// @ 0x00639350
void cSPPlayModeSubModeAction::FUN_00639350()
{
    int* ab = SP::AssetBrowser();
    if ((*(char*)((char*)ab + 0x1c) != 0) ||
        (*(char*)((char*)(ab = SP::SporeGuide()) + 0x1c) != 0)) {
        if (mKeyInputButtonState[5] || mKeyInputButtonState[4] || mKeyInputButtonState[3] ||
            mKeyInputButtonState[2] || mKeyInputButtonState[1] || mKeyInputButtonState[0]) {
            *(uint32*)mKeyInputButtonState = 0;
            *(unsigned short*)(mKeyInputButtonState + 4) = 0;
        }
        return;
    }

    if (!((SP::cSPPlayModeSubModeAction_s0063_7f80*)this)->AnyKeyDown())
        return;

    int* iVar2 = (int*)((char*)mAnimCreature + 0x10);
    uint32 t82bc = DAT_015f82bc ^ 0x80000000u;
    uint32 t82c0 = DAT_015f82c0 ^ 0x80000000u;
    uint32 t8268 = DAT_015f8268 ^ 0x80000000u;
    uint32 t826c = DAT_015f826c ^ 0x80000000u;
    float local_24 = -F(DAT_015f82b8);
    float local_20 = F(t82bc);
    float local_1c = F(t82c0);
    float local_18 = -F(DAT_015f8264);
    float local_14 = F(t8268);
    float local_10 = F(t826c);

    float local_c[3];
    float* pfVar3 = FUN_0059aed0(local_c, &local_24, iVar2);
    float v24 = pfVar3[0], v20 = pfVar3[1], v1c = pfVar3[2];
    pfVar3 = FUN_0059aed0(local_c, &local_18, iVar2);
    float fVar11 = v24 * 0.25f, fVar12 = v20 * 0.25f, fVar13 = v1c * 0.25f;
    float fVar6 = pfVar3[0] * 0.25f, fVar8 = pfVar3[1] * 0.25f, fVar10 = pfVar3[2] * 0.25f;

    float local_30, local_2c, local_28;
    FUN_0059d110(mCreatureID, &local_30);

    float fVar7 = fVar13, fVar5 = fVar11, fVar9 = fVar12;
    int uVar14 = 0;

    if (mKeyInputButtonState[0] == 0) {
        if (mKeyInputButtonState[2] != 0) {
            FUN_0059cf00(mCreatureID, -fVar11 + local_30, local_2c + -fVar12, -fVar13 + local_28, 0, 1);
            mAnimCreature->mField154 = 1;
            mAnimCreature->mField164 = DAT_01523e7c;
            mAnimCreature->mField168 = DAT_01523e80;
            mAnimCreature->mField16C = DAT_01523e84;
            goto LAB_00639629;
        }
        if (mKeyInputButtonState[4] == 0) {
            fVar7 = fVar10; fVar5 = fVar6; fVar9 = fVar8;
            if (mKeyInputButtonState[5] == 0)
                goto LAB_00639629;
            goto LAB_00639600;
        }
        fVar5 = -fVar6; fVar7 = -fVar10; fVar9 = -fVar8;
    }

LAB_00639600:
    FUN_0059cf00(mCreatureID, local_30 + fVar5, local_2c + fVar9, fVar7 + local_28, 0, 1);

LAB_00639629:
    uVar14 = 0;
    if (mKeyInputButtonState[1] == 0) {
        if (mKeyInputButtonState[3] != 0) {
            float n18 = -F(DAT_015f82b8);
            float n14 = F(t82bc);
            float n10 = F(t82c0);
            float n24 = fVar6 + fVar11, n20 = fVar8 + fVar12, n1c = fVar10 + fVar13;
            float ang = FUN_0069b760(&n24, &n18, &DAT_015f823c, 0);
            (void)n14; (void)n10; (void)n1c; (void)n20;
            FUN_0059cea0(mCreatureID, -ang, uVar14);
            FUN_0059cfb0(mCreatureID, (fVar6 * F(DAT_01523e8c) + fVar11) + local_30,
                         local_2c + (fVar8 * F(DAT_01523e8c) + fVar12),
                         fVar10 * F(DAT_01523e8c) + fVar13, 0);
            mAnimCreatureMgr->SetCreatureIsTurning(mCreatureID, 1);
            return;
        }
    }
    else {
        float n18 = -F(DAT_015f82b8);
        float n14 = F(t82bc);
        float n10 = F(t82c0);
        float n24 = fVar11 - fVar6, n20 = fVar12 - fVar8, n1c = fVar13 - fVar10;
        float ang = FUN_0069b760(&n24, &n18, &DAT_015f823c, 0);
        (void)n14; (void)n10; (void)n1c; (void)n20;
        FUN_0059cea0(mCreatureID, -ang, uVar14);
        float neg = -F(DAT_01523e8c);
        FUN_0059cfb0(mCreatureID, (fVar6 * neg + fVar11) + local_30,
                     local_2c + (fVar8 * neg + fVar12), fVar10 * neg + fVar13, 0);
        uVar14 = 1;
    }
    mAnimCreatureMgr->SetCreatureIsTurning(mCreatureID, uVar14);
}

// ---------------------------------------------------------------------------
// 0x00639b70  ::cSPPlayModeSubModeAction::~cSPPlayModeSubModeAction (destructor)
// ---------------------------------------------------------------------------
// @ 0x00639B70
void cSPPlayModeSubModeAction::FUN_00639b70()
{
    *(void**)this = (void*)0x13fec78;
    _ReadWriteBarrier();
    if (mObj10C != 0)
        ((T0)VTSLOT(mObj10C, 4))(mObj10C);
    if (mAlloc54 != 0 && ((int*)mAlloc54)[-1] != 0)
        operator delete(mAlloc54);
    if (mObj44 != 0)
        ((T0)VTSLOT(mObj44, 4))(mObj44);
    if (mObj38 != 0)
        ((T0)VTSLOT(mObj38, 4))(mObj38);
    *(void**)this = (void*)0x13fec40;
}