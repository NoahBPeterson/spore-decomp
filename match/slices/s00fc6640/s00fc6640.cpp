// Slice s00fc6640: SP::cWeatherManager constructor, per-frame update and teardown
// (0x00fc6640 .. 0x00fc741f).  Object file SPTerrain/SPWeatherManager.obj.
//
// 0x00fc6640  construct the weather manager (member stores + two property templates)
// 0x00fc6950  per-frame update (storm scan, message build, phase/temperature step)
// 0x00fc6d10  tear the managed effect objects down and reset the state fields
// 0x00fc6f00  advance the weather state machine
//
// Retail layout confirmed against the 0x00fc6640 constructor and the sibling slices
// s00fc4cd0 / s00fc5900 of the same object file.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>
#include <math.h>

// ---------------------------------------------------------------- float globals
extern "C" const float g_013eb8c8;   // 0x013eb8c8  (phase step / freeze threshold)
extern "C" const float g_0141b034;   // 0x0141b034
extern "C" const float g_014471ec;   // 0x014471ec
extern "C" const float g_01486f6c;   // 0x01486f6c
extern "C" const float g_014914fc;   // 0x014914fc
extern "C" const float g_01491508;   // 0x01491508  (0.95f, storm threshold)
extern "C" const float g_01485720;   // 0x01485720  (1.0f)

// ------------------------------------------------------------ vtable sentinels
extern void* g_vtbl_013eb384;   // 0x013eb384
extern void* g_vtbl_014915f4;   // 0x014915f4
extern void* g_vtbl_01491604;   // 0x01491604

// The shared direct-property list singleton the two property templates bind to.
extern void* g_propList_015fd918;   // 0x015fd918

// --------------------------------------------------------- message server globals
extern void* g_013eb844;   // 0x013eb844
extern void* g_013eb90c;   // 0x013eb90c

// ------------------------------------------------------------------ free helpers
struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};

IRefCounted** CopyPtrs(IRefCounted** first, IRefCounted** last, IRefCounted** result);  // 0x0042f530
extern "C" void EASTL_allocator_deallocate(void* p);                                   // 0x00f47380

// ------------------------------------------- state-machine data (0x00fc6f00)
extern "C" const float g_016d70f8;   // 0x016d70f8  launch direction seed (x)
extern "C" const float g_016d70fc;   // 0x016d70fc  launch direction seed (y)
extern "C" const float g_016d7100;   // 0x016d7100  launch direction seed (z)
extern "C" const float g_016d7104;   // 0x016d7104  basis seed matrix (9 floats)
extern "C" const float g_015b1724;   // 0x015b1724  reference up axis (x)
extern "C" const float g_015b1728;   // 0x015b1728  reference up axis (y)
extern "C" const float g_015b172c;   // 0x015b172c  reference up axis (z)
extern "C" const float g_015b1730;   // 0x015b1730  fallback axis (x)
extern "C" const float g_015b1734;   // 0x015b1734  fallback axis (y)
extern "C" const float g_015b1738;   // 0x015b1738  fallback axis (z)
extern "C" const float g_013ec4b8;   // 0x013ec4b8  normalization epsilon (1e-8f)
extern "C" const float g_013eb960;   // 0x013eb960  alignment tolerance (0.01f)

// ------------------------------------------------------- polymorphic object shape
// Any reference-counted/polymorphic object the manager stores by pointer; only the
// vtable slot numbers matter.  Slot 0 = AddRef, slot 1 = Release, slot 3 = vf0c.
class cRefObj_s00fc6640 {
public:
    virtual void vf00();
    virtual void vf04();
    virtual void vf08(int arg);   // 0x08
    virtual void vf0c(int arg);   // 0x0c
    virtual bool vf10();          // 0x10  is-alive test
    virtual void vf14();
    virtual void vf18(void* record);   // 0x18  apply a motion record
    virtual void vf1c();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2c();
    virtual void vf30();
    virtual void vf34();
    virtual void vf38(void* camInfo, float t, void* outList, void* modelMask);   // 0x38 collect visible effects
    virtual void vf3c();
    virtual void vf40();
    virtual void vf44(int a, void* p, int b);   // 0x44
    virtual void vf48(int a, void* p, int b);   // 0x48
    virtual void vf4c();
    virtual void vf50();
    virtual void vf54();
    virtual void vf58();
    virtual void vf5c();
    virtual void vf60();
    virtual void vf64();
    virtual void vf68();
    virtual void vf6c();
    virtual void vf70();
    virtual void vf74();
    virtual void vf78();
    virtual void vf7c();
    virtual void vf80();
    virtual void vf84();
    virtual void vf88();
    virtual void vf8c();
    virtual void vf90();
    virtual void vf94();
    virtual void vf98(int a, int b);   // 0x98
    virtual void vf9c();
    virtual void vfA0();
    virtual void vfA4();
    virtual void vfA8();
    virtual void vfAC();
    virtual void vfB0();
    virtual void vfB4();
    virtual void vfB8();
    virtual void vfBC();
    virtual void vfC0();
    virtual void vfC4();
    virtual void vfC8();
    virtual void vfCC(int a, float value);   // 0xcc
    virtual void vfD0();                     // 0xd0
    virtual void vfD4();                     // 0xd4
};

// The generic reference-counted effect factory behind the manager's +0x0c pointer.
class cEffectFactory_s00fc6640 {
public:
    virtual void vf00();   // 0x00
    virtual void vf04();   // 0x04
    virtual bool vf08(uint32_t id, int arg, cRefObj_s00fc6640** outEffect);   // 0x08
    virtual void vf0c();   // 0x0c
    virtual void vf10();   // 0x10
};

// The model manager singleton (0x0067dd80) and its model lookup at vtable +0x28.
class cModelManager_s00fc6640 {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0c();
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1c();
    virtual void vf20(); virtual void vf24();
    virtual uint32_t vf28(uint32_t id, int arg);   // 0x28
};

// The viewer behind the manager's +0x0dc pointer; GetCameraLocationInfo is a direct
// (non-virtual) thiscall taking four cSPVector3 pointers.
class cViewer_s00fc6640 {
public:
    void GetCameraLocationInfo(void* out, void* a, void* b, void* c);   // 0x007c3d30
};

// The bitset of candidate model ids (five words plus two flag bytes).
struct cModelMask_s00fc6640 {
    uint32_t mWords[5];   // +0x00
    uint8_t  mFlags[2];   // +0x14
};

// The visibility result list: an eastl vector with a 64-byte inline buffer.
struct cVisibleVec_s00fc6640 {
    cRefObj_s00fc6640** mpBegin;      // +0x00
    cRefObj_s00fc6640** mpEnd;        // +0x04
    cRefObj_s00fc6640** mpCapacity;   // +0x08
    cRefObj_s00fc6640*  mStorage[16]; // +0x0c
};

// The camera information block GetCameraLocationInfo fills in (three floats plus
// the camera's cell/level words).
struct cCameraInfo_s00fc6640 {
    float    mX, mY, mZ;   // +0x00..+0x08
    int32_t  mLevel;       // +0x0c
    int32_t  mCell;        // +0x10
};

// A plain 3-vector and a row-major 3x3 basis with the direct matrix constructor
// (0x0041cb40 seeds it from a global axis block).
struct cVector3_s00fc6640 {
    float mX, mY, mZ;
};

struct cMatrix33_s00fc6640 {
    float mValue[9];

    void InitFrom(const void* pSrc);   // 0x0041cb40
};

// The motion record handed to the created effect's vf18: a flags/count pair, the
// launch position, a reserved word and the orthonormal basis.
struct cMotionRecord_s00fc6640 {
    uint16_t            mFlags;      // +0x00
    uint16_t            mCount;      // +0x02
    cVector3_s00fc6640  mPosition;   // +0x04
    float               m10;         // +0x10
    cMatrix33_s00fc6640 mBasis;      // +0x14
};

// The two global accessors the per-frame update goes through.
cModelManager_s00fc6640* ModelManager();      // 0x0067dd80
cRefObj_s00fc6640*       EffectsRenderer();   // 0x0067de00

// A property template member (+0xb0 / +0xc0): mod count, the property list pointer,
// the list's own vtable-shaped field, and the bound property id.
class cPropTpl_s00fc6640 {
public:
    int32_t  mModCount;     // +0x00
    void*    mpList;        // +0x04
    void*    mListVtbl;     // +0x08
    int32_t  mPropertyID;   // +0x0c

    void BindB(void* pList);   // 0x007e6720
};

// The second template differs only in the property type, so its bind helper is a
// different instantiation, and its count field is a byte.
class cPropTplC_s00fc6640 {
public:
    uint8_t  mCount;        // +0x00
    uint8_t  m1, m2, m3;    // +0x01..+0x03
    void*    mpList;        // +0x04
    void*    mListVtbl;     // +0x08
    int32_t  mPropertyID;   // +0x0c

    void BindC(void* pList);   // 0x00dea7b0
};

// The managed-effect vector at +0x170 (EA sp_vector: three pointers).
class cVec170_s00fc6640 {
public:
    cRefObj_s00fc6640** mpBegin;      // +0x00
    cRefObj_s00fc6640** mpEnd;        // +0x04
    cRefObj_s00fc6640** mpCapacity;   // +0x08

    void Deallocate(cRefObj_s00fc6640** pBegin, cRefObj_s00fc6640** pEnd);   // 0x00533500
    void Insert(cRefObj_s00fc6640** where, cRefObj_s00fc6640** value);      // 0x00a0a360
};

// ------------------------------------------------------------------- the manager
class cWeatherManager_s00fc6640 {
public:
    cWeatherManager_s00fc6640();
    void UpdateStormPhase(int32_t dt);   // 0x00fc6950
    void ResetEffects();      // 0x00fc6d10
    void UpdateStateMachine(float x, float y, float z, int32_t arg4);   // 0x00fc6f00

    void*    mpVtbl0;          // +0x000
    int32_t  mRefCount;        // +0x004
    void*    mpVtbl8;          // +0x008
    cEffectFactory_s00fc6640* mp0C;   // +0x00c
    void*    mp10;             // +0x010
    void*    mp14;             // +0x014
    void*    mp18;             // +0x018
    void*    mp1C;             // +0x01c
    void*    mp20;             // +0x020
    void*    mp24;             // +0x024
    void*    mp28;             // +0x028
    cRefObj_s00fc6640* mp2C;   // +0x02c  current storm effect
    void*    mp30;             // +0x030
    void*    mp34;             // +0x034
    void*    mp38;             // +0x038
    void*    mp3C;             // +0x03c
    void*    mp40;             // +0x040
    uint32_t m44;              // +0x044
    int32_t  mID48, mID4C, mID50, mID54, mID58, mID5C, mID60, mID64;   // +0x048..+0x064
    int32_t  mID68, mID6C, mID70, mID74, mID78, mID7C;                 // +0x068..+0x07c
    int32_t  mID80, mID84, mID88, mID8C;                              // +0x080..+0x08c
    int32_t  mID90;            // +0x090
    uint32_t mStormTimer;      // +0x094  elapsed time in the current storm phase
    uint32_t mStormDuration;   // +0x098  duration of the current storm phase
    float    mFreezeID;        // +0x09c
    uint32_t mA0;              // +0x0a0
    uint32_t mA4;              // +0x0a4
    uint32_t mA8;              // +0x0a8
    uint8_t  mAC;              // +0x0ac
    uint8_t  mAD;              // +0x0ad
    uint8_t  mAE;              // +0x0ae
    uint8_t  mAF;              // +0x0af
    cPropTpl_s00fc6640 mPropB; // +0x0b0
    uint8_t  mC0Count;         // +0x0c0
    uint8_t  mC1, mC2, mC3;    // +0x0c1..+0x0c3
    void*    mpC4List;         // +0x0c4
    void*    mpC8Vtbl;         // +0x0c8
    int32_t  mCCID;            // +0x0cc
    uint32_t mD0;                     // +0x0d0
    cRefObj_s00fc6640* mD4;           // +0x0d4  effects renderer
    cRefObj_s00fc6640* mD8;           // +0x0d8  effect slot list
    cViewer_s00fc6640* mDC;           // +0x0dc  viewer
    uint32_t mE0, mE4, mE8;           // +0x0e0..+0x0e8
    float    mEC, mF0, mF4, mF8, mFC;                // +0x0ec..+0x0fc
    float    m100, m104, m108, m10C, m110, m114, m118, m11C, m120;  // +0x100..+0x120
    float    m124, m128, m12C, m130, m134, m138;     // +0x124..+0x138
    int32_t  m13C, m140, m144;                       // +0x13c..+0x144
    int32_t  m148, m14C;                             // +0x148..+0x14c
    int32_t  m150, m154, m158, m15C;                 // +0x150..+0x15c
    uint32_t m160;                                   // +0x160
    int32_t  m164, m168;                             // +0x164..+0x168
    uint8_t  m16C;                                   // +0x16c
    uint8_t  m16D;                                   // +0x16d
    uint8_t  m16E, m16F;                             // +0x16e..+0x16f
    cVec170_s00fc6640 mEffects;                      // +0x170
    uint32_t m17C;                                   // +0x17c
    uint32_t m180;                                   // +0x180
    uint32_t mRndSeed;                               // +0x184 (RandomLinearCongruential)
    uint32_t mRndStoredSeed;                         // +0x188
    int32_t  m18C;                                   // +0x18c
    float    m190, m194, m198;                       // +0x190..+0x198
    int32_t  m19C;                                   // +0x19c
};

// SetSeed(this, seed) on the manager's RandomLinearCongruential at +0x184.
class cRandom_s00fc6640 {
public:
    uint32_t mSeed;        // +0x00
    uint32_t mStoredSeed;  // +0x04

    void SetSeed(int32_t seed);   // 0x00936090
};

// The message server and the message sent by ResetEffects.
class cMsgServer_s00fc6640 {
public:
    virtual void vf00();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c();
    virtual void vf10();
    virtual void vf14(uint32_t type, void* msg, int32_t arg);

    void Send(uint32_t type, void* msg, int32_t arg);   // hmm: via slot 5
};

extern "C" void* fn_0067dcc0();   // 0x0067dcc0  SP::MessageServer()

// A 0x3c-byte message posted by ResetEffects: base vtable, atomic refcount, payload
// floats/words, the message type at +0x30 and a flag word at +0x38.
class cMsgStack_s00fc6640 {
public:
    void*            mpVtbl;      // +0x00
    volatile int32_t mRefCount;   // +0x04
    float            mF08;        // +0x08
    int32_t          mPayload[9]; // +0x0c..+0x2f
    uint32_t         mType;       // +0x30
    int32_t          m34;         // +0x34
    int32_t          m38;         // +0x38
    int32_t          m3C;         // +0x3c

    void Construct(int32_t arg);  // 0x00421c80
    void Destroy();               // 0x00421cf0
};

// ------------------------------------------------------------------ constructor
// @ 0x00fc6640
cWeatherManager_s00fc6640::cWeatherManager_s00fc6640()
{
    const float kFreeze = g_013eb8c8;

    mRefCount = 0;
    *(void* volatile*)&mpVtbl8 = (void*)&g_vtbl_013eb384;
    *(void* volatile*)&mpVtbl0 = (void*)&g_vtbl_01491604;
    *(void* volatile*)&mpVtbl8 = (void*)&g_vtbl_014915f4;

    mp0C = 0;
    mp10 = 0;
    mp14 = 0;
    mp18 = 0;
    mp1C = 0;
    mp20 = 0;
    mp24 = 0;
    mp28 = 0;
    mp2C = 0;
    mp30 = 0;
    mp34 = 0;
    mp38 = 0;
    mp3C = 0;
    mp40 = 0;

    mID48 = 0;
    mID4C = 0;
    mID50 = 0;
    mID54 = 0;
    mID58 = 0;
    mID5C = 0;
    mID60 = 0;
    mID64 = 0;
    mID68 = 0;
    mID6C = 0;
    mID70 = 0;
    mID74 = 0;
    mID78 = 0;
    mID7C = 0;

    mID80 = 0;
    mID84 = 0;
    mID88 = 0;
    mID8C = 0;
    mID90 = 0;
    mStormTimer = 0;

    mStormDuration = 3000;
    mFreezeID = kFreeze;
    mA0 = 0;
    mA4 = 0;
    mA8 = 0;
    mAC = 0;
    mAD = 0;

    void* pList = g_propList_015fd918;

    cPropTpl_s00fc6640* propB = &mPropB;
    propB->mModCount = 2;
    propB->mpList = pList;
    if (pList != 0)
        ((cRefObj_s00fc6640*)pList)->vf00();
    propB->mListVtbl = (void*)0x3ffad0a;
    propB->mPropertyID = 0;
    if (pList != 0)
        propB->BindB(pList);

    pList = g_propList_015fd918;

    cPropTplC_s00fc6640* propC = (cPropTplC_s00fc6640*)&mC0Count;
    propC->mCount = 1;
    propC->mpList = pList;
    if (pList != 0)
        ((cRefObj_s00fc6640*)pList)->vf00();
    propC->mListVtbl = (void*)0x588bf6d;
    propC->mPropertyID = 0;
    if (pList != 0)
        propC->BindC(pList);

    const float kStormLevel = g_01491508;
    const float kZero = 0.0f;

    mD0 = 0;
    mD4 = 0;
    mD8 = 0;
    mDC = 0;
    mE0 = 0;
    mE4 = 0;
    mE8 = 0;

    mEC = kZero;
    mF0 = kZero;
    mF4 = kZero;
    mF8 = kZero;
    mFC = kZero;

    m100 = kStormLevel;
    m104 = kStormLevel;
    m108 = kStormLevel;
    m10C = kStormLevel;
    m110 = kStormLevel;
    m114 = kStormLevel;
    m118 = kStormLevel;
    m11C = kStormLevel;
    m120 = kStormLevel;

    m124 = g_0141b034;
    m128 = g_014471ec;
    m12C = g_01486f6c;
    m130 = g_013eb8c8;
    m134 = g_014914fc;
    m138 = kZero;

    _ReadWriteBarrier();
    m13C = 9;
    m140 = 9;

    _ReadWriteBarrier();
    m148 = 0;
    m14C = 0;
    _ReadWriteBarrier();
    m150 = 5;
    m154 = 5;
    _ReadWriteBarrier();
    m158 = 3;
    m15C = 3;
    m160 = 5;
    m164 = 0;
    m168 = 0;
    m16D = 0;
    _ReadWriteBarrier();
    mEffects.mpBegin = 0;
    mEffects.mpEnd = 0;
    mEffects.mpCapacity = 0;
    ((cRandom_s00fc6640*)&mRndSeed)->SetSeed(-1);

    const float kPhase = g_014914fc;

    mRndStoredSeed = 0;
    _ReadWriteBarrier();
    m19C = 5;
    m18C = -1;
    m190 = kPhase;
    m194 = kPhase;
    m198 = kPhase;
}

// @ 0x00fc6950
void cWeatherManager_s00fc6640::UpdateStormPhase(int32_t dt)
{
    if (mAD == 0)
        return;
    if (mEffects.mpBegin == mEffects.mpEnd)
        return;

    // Drop the finished effects from the live list.  CopyPtrs compacts the range
    // [next, end) down over the slot being erased, and the element left dangling at
    // the back is released.
    cRefObj_s00fc6640** it = mEffects.mpBegin;
    while (it != mEffects.mpEnd) {
        cRefObj_s00fc6640** next = it + 1;
        cRefObj_s00fc6640* effect = *it;
        if (effect == 0 || !effect->vf10()) {
            if (next < mEffects.mpEnd)
                CopyPtrs((IRefCounted**)next, (IRefCounted**)mEffects.mpEnd, (IRefCounted**)it);
            --mEffects.mpEnd;
            cRefObj_s00fc6640* tail = *mEffects.mpEnd;
            if (tail != 0)
                tail->vf04();
        }
        else {
            it = next;
        }
    }

    // Work out the visibility set the effect renderer should use this frame: the
    // manager's own model plus the camera's cell.
    uint32_t model = ModelManager()->vf28(0x60dfad7, 0);

    cCameraInfo_s00fc6640 camInfo;
    mDC->GetCameraLocationInfo(&camInfo, 0, 0, 0);

    cModelMask_s00fc6640 mask;
    mask.mWords[0] = 0;
    mask.mWords[1] = 0;
    mask.mWords[2] = 0;
    mask.mWords[3] = 0;
    mask.mWords[4] = 0;
    mask.mFlags[0] = 0;
    mask.mFlags[1] = 0;
    if (model < 64)
        mask.mWords[model >> 5] |= 1u << (model & 31);

    cVisibleVec_s00fc6640 visible;
    visible.mpBegin = visible.mStorage;
    visible.mpEnd = visible.mStorage;
    visible.mpCapacity = visible.mStorage + 16;
    mD4->vf38(&camInfo, 1.0f, &visible, &mask);

    cMsgStack_s00fc6640 msg;

    if (visible.mpEnd - visible.mpBegin == 0)
        goto StateStep;

    // Effects are visible: (re)create the storm effect when the current one is gone.
    if (mp2C != 0 && mp2C->vf10())
        goto StateStep;

    if (mp2C != 0) {
        cRefObj_s00fc6640* old = mp2C;
        mp2C = 0;
        old->vf04();
    }
    if (!mp0C->vf08((uint32_t)mID50, 0, &mp2C))
        goto Cleanup;

    m15C = 1;
    mStormTimer = 0;
    mp2C->vf08(0);
    mD8->vf98(0x16, 1);
    msg.Construct(0);
    msg.mType = 0x553fe73;
    msg.mF08 = 1.0f;
    goto SendMessage;

StateStep:
    if (m15C == 1) {
        // Phase 1: ramp the storm in as the timer approaches its duration.
        if (mStormTimer > mStormDuration) {
            m15C = 0;
            goto AddDt;
        }
        float ratio = (float)mStormTimer / (float)mStormDuration;
        EffectsRenderer()->vfCC(0, (mFreezeID - 1.0f) * ratio + 1.0f);
    }
    else {
        if (visible.mpEnd - visible.mpBegin == 0 && mp2C != 0) {
            // Nothing is visible any more: ramp the effect back out.
            m15C = 2;
            mStormTimer = 0;
            mp2C->vf0c(0);
            if (mp2C != 0) {
                cRefObj_s00fc6640* old = mp2C;
                mp2C = 0;
                old->vf04();
            }
            mD8->vf98(0x16, 0);
            msg.Construct(0);
            msg.mType = 0x553fe73;
            msg.mF08 = 0.0f;
            goto SendMessage;
        }

        if (m15C != 2)
            goto Cleanup;

        if (mStormTimer > mStormDuration) {
            EffectsRenderer()->vfD0();
            m15C = 3;
            goto AddDt;
        }
        float ratio = (float)mStormTimer / (float)mStormDuration;
        EffectsRenderer()->vfCC(0, (1.0f - mFreezeID) * ratio + mFreezeID);
    }

AddDt:
    mStormTimer += dt;
    goto Cleanup;

SendMessage:
    ((cMsgServer_s00fc6640*)fn_0067dcc0())->vf14(msg.mType, &msg, 0);
    msg.Destroy();

Cleanup:
    if (visible.mpBegin != 0 && visible.mpBegin != visible.mStorage)
        EASTL_allocator_deallocate(visible.mpBegin);
}

// @ 0x00fc6d10
void cWeatherManager_s00fc6640::ResetEffects()
{
    if (mp14) ((cRefObj_s00fc6640*)mp14)->vf0c(1);
    if (mp18) ((cRefObj_s00fc6640*)mp18)->vf0c(1);
    if (mp1C) ((cRefObj_s00fc6640*)mp1C)->vf0c(1);
    if (mp20) ((cRefObj_s00fc6640*)mp20)->vf0c(1);
    if (mp24) ((cRefObj_s00fc6640*)mp24)->vf0c(1);
    if (mp28) ((cRefObj_s00fc6640*)mp28)->vf0c(1);
    if (mp2C) ((cRefObj_s00fc6640*)mp2C)->vf0c(1);
    if (mp30) ((cRefObj_s00fc6640*)mp30)->vf0c(1);
    if (mp34) ((cRefObj_s00fc6640*)mp34)->vf0c(1);

    for (cRefObj_s00fc6640** it = (cRefObj_s00fc6640**)mEffects.mpBegin;
         it != (cRefObj_s00fc6640**)mEffects.mpEnd; ++it)
        (*it)->vf0c(1);

    cRefObj_s00fc6640* p;

    p = (cRefObj_s00fc6640*)mp14; if (p) { mp14 = 0; p->vf04(); }
    p = (cRefObj_s00fc6640*)mp18; if (p) { mp18 = 0; p->vf04(); }
    p = (cRefObj_s00fc6640*)mp1C; if (p) { mp1C = 0; p->vf04(); }
    p = (cRefObj_s00fc6640*)mp20; if (p) { mp20 = 0; p->vf04(); }
    p = (cRefObj_s00fc6640*)mp24; if (p) { mp24 = 0; p->vf04(); }
    p = (cRefObj_s00fc6640*)mp28; if (p) { mp28 = 0; p->vf04(); }
    p = (cRefObj_s00fc6640*)mp2C; if (p) { mp2C = 0; p->vf04(); }
    p = (cRefObj_s00fc6640*)mp30; if (p) { mp30 = 0; p->vf04(); }
    p = (cRefObj_s00fc6640*)mp34; if (p) { mp34 = 0; p->vf04(); }

    cVec170_s00fc6640* vec = &mEffects;
    vec->Deallocate(vec->mpBegin, vec->mpEnd);

    mAC = 0;
    m150 = 5;
    m158 = 3;
    m13C = 9;

    cMsgStack_s00fc6640 msg;
    msg.mType = 0;
    *(void* volatile*)&msg.mpVtbl = (void*)&g_013eb90c;
    _InterlockedExchange((volatile long*)&msg.mRefCount, 0);
    *(void* volatile*)&msg.mpVtbl = (void*)&g_013eb844;
    msg.m38 = 0;
    msg.mType = 0x553fe73;
    msg.mF08 = 0.0f;

    cMsgServer_s00fc6640* server = (cMsgServer_s00fc6640*)fn_0067dcc0();
    server->vf14(msg.mType, &msg, 0);
    msg.Destroy();
}

// @ 0x00fc6f00
void cWeatherManager_s00fc6640::UpdateStateMachine(float x, float y, float z, int32_t arg4)
{
    if (m160 == 0)
        return;

    // If enough effects are already live, retire the oldest one.
    uint32_t count = (uint32_t)(mEffects.mpEnd - mEffects.mpBegin);
    if (count != 0 && count >= m160) {
        cRefObj_s00fc6640* first = mEffects.mpBegin[0];
        if (first != 0 && first->vf10())
            first->vf0c(0);
    }

    cRefObj_s00fc6640* obj = 0;
    if (mp0C->vf08((uint32_t)mID84, 0, &obj)) {
        // Fill in the motion record the renderer consumes: a flags/count pair, the
        // launch position, a unit scale and an orthonormal basis.
        cMotionRecord_s00fc6640 record;
        record.mFlags = 0;
        record.mCount = 0;
        record.mPosition.mX = x;
        record.mPosition.mY = y;
        record.mPosition.mZ = z;
        record.m10 = 1.0f;
        record.mBasis.InitFrom(&g_016d7104);

        record.mFlags |= 4;
        record.mCount += 1;

        // Normalize the launch direction, then complete the basis from the reference
        // axis - or its negative when the direction already points along it.
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + g_013ec4b8);
        cVector3_s00fc6640 u, ref;
        u.mX = x * inv;
        u.mY = y * inv;
        u.mZ = z * inv;

        ref.mX = g_015b1724;
        ref.mY = g_015b1728;
        ref.mZ = g_015b172c;
        float align = u.mX * ref.mX + u.mY * ref.mY + u.mZ * ref.mZ;
        if (fabsf(align - 1.0f) <= g_013eb960) {
            ref.mX = -g_015b1730;
            ref.mY = -g_015b1734;
            ref.mZ = -g_015b1738;
        }

        float vx = u.mY * ref.mZ - u.mZ * ref.mY;
        float vy = u.mZ * ref.mX - u.mX * ref.mZ;
        float vz = u.mX * ref.mY - u.mY * ref.mX;
        float vInv = 1.0f / sqrtf(vx * vx + vy * vy + vz * vz + g_013ec4b8);
        vx *= vInv;
        vy *= vInv;
        vz *= vInv;

        float wx = vy * u.mZ - vz * u.mY;
        float wy = vz * u.mX - vx * u.mZ;
        float wz = vx * u.mY - vy * u.mX;
        float wInv = 1.0f / sqrtf(wx * wx + wy * wy + wz * wz + g_013ec4b8);
        wx *= wInv;
        wy *= wInv;
        wz *= wInv;

        cMatrix33_s00fc6640 basis;
        basis.mValue[0] = vx; basis.mValue[1] = vy; basis.mValue[2] = vz;
        basis.mValue[3] = wx; basis.mValue[4] = wy; basis.mValue[5] = wz;
        basis.mValue[6] = u.mX; basis.mValue[7] = u.mY; basis.mValue[8] = u.mZ;
        record.mBasis = basis;

        record.mFlags |= 2;
        record.mCount += 2;

        obj->vf18(&record);

        // The renderer's per-object slot depends on the phase the manager is in.
        int32_t mode = 1;
        if (m140 == 0 || m140 == 3 || m140 == 6)
            mode = 0;
        else if (m140 == 2 || m140 == 5 || m140 == 8)
            mode = 2;
        obj->vf48(3, &mode, 1);
        obj->vf44(2, &arg4, 1);
        obj->vf08(0);

        if (mEffects.mpEnd < mEffects.mpCapacity) {
            *mEffects.mpEnd = obj;
            ++mEffects.mpEnd;
            if (obj != 0)
                obj->vf00();
        }
        else {
            mEffects.Insert(mEffects.mpEnd, &obj);
        }
    }

    if (obj != 0)
        obj->vf04();
}
