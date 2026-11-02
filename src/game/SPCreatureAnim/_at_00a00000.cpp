// src/game/SPCreatureAnim/_at_00a00000.cpp -- migrated from slice(s) s00a01810, s00a00980, s009ffa00 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/_at_00a00000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <string.h>
#include <math.h>

// ---- items of slice s009ffa00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct GoalObj {                 // refcounted payload of AnimGoal::field_00
    char    pad_00[0xad];
    char    field_ad;
    char    pad_ae[0x0a];
    double  field_b8;
    void AddRef();               // 0x0099c970
    void Release();              // 0x009a3630
    void FUN_009a3080(int a);    // 0x009a3080
    void FUN_009a3220(int a, void* b, int c);   // 0x009a3220
    GoalObj* FUN_009a34a0();     // 0x009a34a0 (ctor)
};
struct GoalObj2 {                // refcounted payload of AnimGoal::field_04
    void AddRef();               // 0x009ac2a0
    void Release();              // 0x009ae1c0
};
struct CreatureInst {
    char pad[0x0];
    void Release();              // 0x009c4cc0 (nSPCreatureAnim::creature_instance_data::Release)
    void AddRef();               // 0x00a17060
};
struct AnimGoal;
struct AnimGoal {
    GoalObj*  field_00;      // +0x00
    GoalObj2* field_04;      // +0x04
    int       mChildren[24]; // +0x08
    int       mChildCount;   // +0x68
    int       field_6c;      // +0x6c
    float     field_70;
    float     field_74;
    float     field_78;
    uint8_t   field_7c;
    char      pad_7d[3];
    int       field_80;
    uint8_t   field_84;
    char      pad_85[3];
    float     field_88;
    float     field_8c;
    float     field_90;
    float     field_94;
    float     field_98;
    uint8_t   field_9c;
    uint8_t   field_9d;
    char      pad_9e[2];
    float     field_a0;
    char      pad_a4[4];
    double    field_a8;
    int       field_b0;
    int       field_b4;
    float     field_b8;
    int       field_bc;
    int       field_c0;
    float     field_c4;
    float     field_c8;
    float     field_cc;
    float     field_d0;
    uint8_t   field_d4;
    char      pad_d5[3];
    int       field_d8;
    int       field_dc;
    int       field_e0;
    int       field_e4;
    int       field_e8;
    int       field_ec;

    AnimGoal* operator=(AnimGoal* o);   // 0x009ffb50 (thiscall, ret 4)
    void Reset();                       // 0x00a00490
    void Stop(char a, char b);          // 0x00a00670
    void FUN_009aa4c0(GoalObj** src);   // 0x009aa4c0
};
struct QueuedBlender {
    uint32_t     mSeq;               // +0x000
    uint32_t     pad_04;
    AnimGoal     mGoals[16];         // +0x008, stride 0xf0
    uint32_t     field_f08;          // +0xf08
    uint32_t     mActive[16];        // +0xf0c
    uint32_t     mQueue[16];         // +0xf4c
    char         pad_f8c[0x10];
    int          field_f9c;          // +0xf9c
    int          field_fa0;          // +0xfa0
    uint32_t     mCurrent;           // +0xfa4
    uint32_t     mPending;           // +0xfa8
    uint8_t      field_fac;          // +0xfac
    char         pad_fad[3];
    float        field_fb0;          // +0xfb0
    float        field_fb4;          // +0xfb4
    float        field_fb8;          // +0xfb8
    CreatureInst* field_fbc;         // +0xfbc
    int          field_fc0;          // +0xfc0
    float        field_fc4;          // +0xfc4
    float        field_fc8;          // +0xfc8
    uint8_t      field_fcc;          // +0xfcc

    void ResetAll(char full);                      // 0x00a007d0
    void SetCreature(CreatureInst* c, int v);      // 0x00a00910
    void ClearPendingGoal();                       // 0x00a008b0
    void SelectPending(uint32_t handle);           // 0x00a006f0
};
// ---- items of slice s009ffa00 end

// ---- items of slice s00a00980 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int DAT_015509dc;
extern "C" int DAT_01550ad4;
extern "C" int DAT_015509f4;
extern "C" int DAT_0166bff0;
extern "C" int DAT_0166cbec;
typedef unsigned int uint;
struct QueuedBlender_s00a0_0980;
struct AnimCommand {
    void*         mAnim;            // +0x00
    void*         mAnimBaked;       // +0x04
    uint          mDeferred[8][3];  // +0x08 .. +0x68 (8 ids * 0xc)
    uint          mDeferredIdx;     // +0x68
    uint          mLinkedHandle;    // +0x6c
    float         mDurationOverride;// +0x70
    uint          mHandle;          // +0x74
    float         mDelay;           // +0x78
    uint          mPad7c;           // +0x7c
    uint          mPad80;           // +0x80
    bool          mFlag84;          // +0x84
    char          mPad85[3];        // +0x85
    float         mCursor;          // +0x88
    uint          mPad8c;           // +0x8c
    uint          mPad90;           // +0x90
    uint          mPad94;           // +0x94
    float         mWeight98;        // +0x98
    uint          mPad9c;           // +0x9c
    float         mA0;              // +0xa0
    uint          mPadA4[3];        // +0xa4 .. +0xb0
    uint          mSeq;             // +0xb0
    uint          mSeqGen;          // +0xb4
    float         mBakeScale;       // +0xb8
    uint          mAnimId;          // +0xbc
    uint          mStatus;          // +0xc0
    float         mTransition;      // +0xc4
    int           mEnabled;         // +0xc8
    uint          mPadCC;           // +0xcc
    float         mWeightD0;        // +0xd0
    bool          mActiveD4;        // +0xd4
    char          mPadD5[7];        // +0xd5 .. +0xdc
    int           mCb1;             // +0xdc callback fn ptr
    uint          mCb1a;            // +0xe0
    uint          mCb1b;            // +0xe4
    int           mCb2;             // +0xe8 callback fn ptr
    uint          mCb2a;            // +0xec
};
struct QueuedBlender_s00a0_0980 {
    uint        mSeq;               // +0x000
    uint        mPad04;             // +0x004
    AnimCommand mCommands[16];      // +0x008 (0xf0 each)
    uint        mCommandsTail;      // +0xf08
    uint        mActive[16];        // +0xf0c
    uint        mQueued[16];        // +0xf4c
    bool        mNewlyActivated[16];// +0xf8c
    uint        mQueueTail;         // +0xf9c
    uint        mQueueHead;         // +0xfa0
    uint        mPrimary;           // +0xfa4
    uint        mDefault;           // +0xfa8
    bool        mFlagFac;           // +0xfac
    char        mPadFad[3];         // +0xfad
    uint        mPadFb0;            // +0xfb0
    uint        mPadFb4;            // +0xfb4
    float       mEaseTime;          // +0xfb8
    void*       mCreature;          // +0xfbc
    void*       mBakedMgr;          // +0xfc0
    uint        mPadFc4;            // +0xfc4
    uint        mPadFc8;            // +0xfc8
    bool        mFlagFcc;           // +0xfcc

    void ClearQueued();                          // 00a00980
    void FUN_00a00c40(uint param);               // 00a00c40
    void Activate(uint idx, char force);         // 00a00d50
    void Deactivate(uint idx);                   // 00a00f10
    void FUN_00a00f90(AnimCommand* cmd, uint x); // 00a00f90
    void FUN_00a01050(uint x);                   // 00a01050
    void UpdateCreatureBodies(uint a2, float a3, float a4, uint a5,
                              uint a6, uint a7, float a8); // 00a010c0
};
struct XC {
    void  FUN_00a00490();
    void* FUN_009a34a0();
    void  FUN_0099c970();
    void  FUN_009a3630();
    void  FUN_009ae1c0();
    void  FUN_009a3220(uint, uint, uint);
    void  FUN_009fee90();
    void  FUN_00a00670(bool, int);
    void  FUN_009ff440();
    uint  FUN_009ff380();
    uint  FUN_009ff040();
    uint  FUN_009aa8a0(uint, uint, uint);
    void  FUN_009abe90(uint, uint, uint, uint);
    void  FUN_009a9b90(uint);
    void  FUN_00a008b0();
    void  FUN_009b9090();
    float FUN_009ac2b0(float, float, int, uint);
    float FUN_009afe90(float);
    void  FUN_009ffb50();
};
void  __cdecl FUN_009a1ad0(void*);
uint  __cdecl FUN_009a4550(uint, uint);
void  __cdecl FUN_009f9b40(void*);
void  __cdecl FUN_009fbb80(void*, float);
void  __cdecl FUN_009bcab0(void*, float, float);
void  __cdecl FUN_009bd2b0(void*);
void  __cdecl FUN_009bcc70(void*, float);
void  __cdecl FUN_009a6cc0(uint, void*);
void  __cdecl FUN_009bd550(float, float, void*, int);
void  __cdecl FUN_009bd6f0(void*);
void  __cdecl FUN_009cb760(void*);
void  __cdecl FUN_009be150(void*);
void  __cdecl FUN_009a7f10(uint, void*, void*, uint, float);
void  __cdecl FUN_009ff880(void*, void*);
char  __cdecl FUN_009ffa00(void*, void*);
void* __cdecl operator_new(size_t, const char*, int, int, int, int);
extern "C" uint* g_166c064;   // 0x0166c064
extern "C" uint DAT_0166cbe8;
uint FUN_00a009e0(QueuedBlender_s00a0_0980* b);
AnimCommand* FUN_00a00b10(QueuedBlender_s00a0_0980* b, AnimCommand* src, uint handle, uint a2);
// ---- items of slice s00a00980 end

// ---- items of slice s00a01810 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct AnimReference {
    uint32_t animID;        // +0x00
    float    duration;      // +0x04
    float    durationScale; // +0x08
};
class RefObj;
class anim_qb;
class anim_query {
public:
    RefObj*      field_0;       // +0x00
    RefObj*      field_4;       // +0x04
    AnimReference anims[8];     // +0x08
    int          field_68;      // +0x68
    int          field_6C;      // +0x6C
    float        field_70;      // +0x70
    float        field_74;      // +0x74
    float        field_78;      // +0x78
    bool         field_7C;      // +0x7C
    int          mode;          // +0x80
    bool         idle;          // +0x84
    float        blendInTime;   // +0x88
    float        field_8C;      // +0x8C
    float        field_90;      // +0x90
    float        field_94;      // +0x94
    float        field_98;      // +0x98
    bool         field_9C;      // +0x9C
    bool         field_9D;      // +0x9D
    float        field_A0;      // +0xA0
    int          field_A4;      // +0xA4
    double       field_A8;      // +0xA8
    int          field_B0;      // +0xB0
    int          field_B4;      // +0xB4
    float        field_B8;      // +0xB8
    int          field_BC;      // +0xBC
    int          field_C0;      // +0xC0
    float        field_C4;      // +0xC4
    float        field_C8;      // +0xC8
    float        field_CC;      // +0xCC
    float        field_D0;      // +0xD0
    bool         field_D4;      // +0xD4
    uint32_t     animID;        // +0xD8
    int          field_DC;      // +0xDC
    int          field_E0;      // +0xE0
    int          field_E4;      // +0xE4
    int          field_E8;      // +0xE8
    int          field_EC;      // +0xEC

    void  Reset();              // 0xa00490
    char  Test();               // 0x9ff020
    void  Set670(int a, int b); // 0xa00670
};
class RefObj {
public:
    char   pad[0xb0];
    double mBlendA;          // +0xb0
    double mBlendB;          // +0xb8
    char   pad_rest[0x1000 - 0xc0];
    void  Rel9ae1c0();
    void  Rel9a3630();
    void  Rel9c4cc0();
    float Ac2b0();                                                   // 0x9ac2b0
    void  Acac0(float scale, void* cid, RefObj* f0, float blend, int a, int b, int c);  // 0x9acac0
};
class anim_qb {
public:
    int          field_0;        // +0x00
    int          field_4;        // +0x04
    anim_query   queries[16];    // +0x08
    int          field_F08;      // +0xF08
    unsigned int field_F0C[16];  // +0xF0C
    int          field_F4C[16];  // +0xF4C
    int          field_F8C;
    int          field_F90;
    int          field_F94;
    int          field_F98;
    int          field_F9C;
    unsigned int field_FA0;
    unsigned int field_FA4;
    unsigned int field_FA8;
    bool         field_FAC;      // +0xFAC
    float        field_FB0;
    float        field_FB4;
    float        field_FB8;
    void*        p_anim_cid;     // +0xFBC
    int          field_FC0;
    float        field_FC4;
    float        field_FC8;
    bool         field_FCC;

    anim_qb();                                   // 0xa01c10
    ~anim_qb();                                  // 0xa01c70
    void UpdateQuery(uint32_t id, float delta);  // 0xa01cd0
    void Foo(int, int);                          // 0xa01f10
    void Update(float dt, bool b, int a, int c); // 0xa01f40
    bool Bar(int);                               // 0xa02440
    void Reset(int flag);                        // 0xa007d0
    void Commit();                               // 0xa00980
    void Remove(int index);                      // 0xa00f10
    void Ret(anim_query* q, int a);              // 0xa00f90
    void D50(int a, int b);                      // 0xa00d50
};
extern "C" void  __cdecl    q_swap(anim_query* a, anim_query* b);
// ---- items of slice s00a01810 end

// @ 0x00a006f0
void QueuedBlender::SelectPending(uint32_t handle)
{
    extern AnimGoal* __cdecl FindGoalByHandle(QueuedBlender*, uint32_t);   // 0x009ff6f0
    AnimGoal* g = FindGoalByHandle(this, handle);
    if (g == 0)
        return;
    if (mPending < 0x10) {
        AnimGoal* pg = (AnimGoal*)((char*)this + mPending * 0xf0 + 8);
        if (g != pg) {
            pg->field_84 = 0;
            AnimGoal* pg2 = (AnimGoal*)((char*)this + mPending * 0xf0 + 8);
            if (pg2->field_c0 == 0 && mPending != mActive[mCurrent]) {
                pg2->Reset();
                for (int i = 0; i < 16; ++i) {
                    if (mActive[i] == mPending)
                        mActive[i] = 0xffffffff;
                }
            }
        }
    }
    if (mPending >= 0x10 || g != (AnimGoal*)((char*)this + mPending * 0xf0 + 8)) {
        g->field_84 = 1;
        for (int i = 0; i < 16; ++i) {
            if (g == &mGoals[i]) {
                mPending = i;
                break;
            }
        }
    }
}

// @ 0x00a008b0
void QueuedBlender::ClearPendingGoal()
{
    if (mPending < 0x10) {
        AnimGoal* g = &mGoals[mPending];
        if (g->field_00 != 0 || ((uint32_t)g->mChildCount < 8 && g->mChildren[g->mChildCount * 3] != 0))
            g->Reset();
        for (int i = 0; i < 16; ++i) {
            if (mActive[i] == mPending)
                mActive[i] = 0xffffffff;
        }
    }
}

// @ 0x00a00980
void QueuedBlender_s00a0_0980::ClearQueued()
{
    uint* p = mQueued;
    int n = 0x10;
    do {
        uint v = *p;
        if (v != 0xffffffffu && v != mDefault)
            ((XC*)&mCommands[v])->FUN_00a00490();
        *p = 0xffffffffu;
        p++;
        n--;
    } while (n != 0);
    mQueueHead = 0xffffffffu;
    mQueueTail = 0xffffffffu;
}

// @ 0x00a009e0
uint FUN_00a009e0(QueuedBlender_s00a0_0980* b)
{
    int best = -1;
    int it = 0;
    for (;;) {
        if (best >= 0 && (uint)best != b->mDefault) {
            AnimCommand* c = &b->mCommands[best];
            if (c->mAnim == 0 &&
                (c->mDeferredIdx >= 8 || c->mDeferred[c->mDeferredIdx][0] == 0))
                return (uint)best;
        }
        if ((uint)best <= 0x10) {
            AnimCommand* c = &b->mCommands[best];
            if (c->mAnim == 0) {
                uint h = c->mHandle;
                if (h == 0) { ((XC*)c)->FUN_00a00490(); return (uint)best; }
                AnimCommand* s = &b->mCommands[(h & 0xff) - 1];
                if (s->mSeqGen != (h >> 8)) { ((XC*)c)->FUN_00a00490(); return (uint)best; }
                if (s->mAnim == 0) {
                    uint h2 = s->mLinkedHandle;
                    if (h2 == 0) { ((XC*)c)->FUN_00a00490(); return (uint)best; }
                    AnimCommand* s2 = &b->mCommands[(h2 & 0xff) - 1];
                    if (s2->mSeqGen != (h2 >> 8)) { ((XC*)c)->FUN_00a00490(); return (uint)best; }
                    if (s2->mAnim == 0) { ((XC*)c)->FUN_00a00490(); return (uint)best; }
                }
            }
        }
        uint t = b->mCommandsTail;
        int nx = (int)(t + 1);
        if (nx < 0) {
            uint m = (uint)(-nx) & 0x8000000fu;
            if ((int)m < 0) m = ((m - 1) | 0xfffffff0u) + 1;
            if (m != 0) m = 0x10 - m;
            nx = (int)m;
        } else {
            nx = (int)((uint)nx & 0x8000000fu);
            if (nx < 0) nx = (int)((((uint)nx - 1) | 0xfffffff0u) + 1);
        }
        if (t == 0xf) b->mSeq++;
        it++;
        b->mCommandsTail = (uint)nx;
        if (it >= 0x10) return 0xffffffffu;
        best = nx;
    }
}

// @ 0x00a00b10
AnimCommand* FUN_00a00b10(QueuedBlender_s00a0_0980* b, AnimCommand* src, uint handle, uint a2)
{
    uint idx = FUN_00a009e0(b);
    if (idx >= 0x10) return 0;
    AnimCommand* c = &b->mCommands[idx];
    ((XC*)c)->FUN_00a00490();
    if (g_166c064[0] == g_166c064[1]) {
        void* p = operator_new(0xe0, "Anim/aid", 0, 0, 0, 0);
        void* nv = p ? ((XC*)p)->FUN_009a34a0() : 0;
        void* old = c->mAnim;
        if (nv != old) {
            if (nv) ((XC*)nv)->FUN_0099c970();
            c->mAnim = nv;
            if (old) ((XC*)old)->FUN_009a3630();
        }
    } else {
        void* nv = (void*)*(uint*)(g_166c064[1] - 4);
        void* old = c->mAnim;
        if (nv != old) {
            if (nv) ((XC*)nv)->FUN_0099c970();
            c->mAnim = nv;
            if (old) ((XC*)old)->FUN_009a3630();
        }
        g_166c064[1] -= 4;
        void* v = (void*)*(uint*)(g_166c064[1]);
        if (v) ((XC*)v)->FUN_009a3630();
    }
    uint r = FUN_009a4550(*(uint*)b->mCreature, a2);
    ((XC*)c->mAnim)->FUN_009a3220(a2, (uint)b->mCreature, r);
    ((XC*)c)->FUN_009fee90();
    c->mActiveD4 = true;
    ((AnimCommand*)c->mAnim)->mActiveD4 = true;
    c->mSeqGen = b->mSeq;
    c->mLinkedHandle = handle;
    src->mLinkedHandle = b->mSeq * 0x100 + 1 + (idx & 0xff);
    return c;
}

// @ 0x00a00c40
void QueuedBlender_s00a0_0980::FUN_00a00c40(uint param)
{
    uint v = mActive[param];
    if (v != mDefault) {
        AnimCommand* src = &mCommands[v];
        AnimCommand* dst = &mCommands[mDefault];
        mActive[param] = mDefault;
        uint i = 0;
        do {
            if (i != param && mActive[i] == mDefault)
                mActive[i] = 0xffffffffu;
            i++;
        } while (i < 0x10);
        if (dst->mStatus == 3)
            dst->mStatus = 1;
        uint h = src->mLinkedHandle;
        if (h != 0) {
            dst->mLinkedHandle = h;
            AnimCommand* s = &mCommands[(h & 0xff) - 1];
            if ((h & 0xff) - 1 < 0x10 && s->mSeqGen == (h >> 8))
                s->mHandle = dst->mSeqGen * 0x100 + 1 + (mDefault & 0xff);
            ((XC*)dst)->FUN_00a00490();
        } else {
            dst->mLinkedHandle = src->mSeqGen * 0x100 + 1 + (v & 0xff);
            src->mLinkedHandle = dst->mSeqGen * 0x100 + 1 + (mDefault & 0xff);
        }
    }
}

// @ 0x00a01050
void QueuedBlender_s00a0_0980::FUN_00a01050(uint x)
{
    uint* p = mActive;
    int n = 0x10;
    do {
        uint v = *p;
        if (v < 0x10) {
            AnimCommand* c = &mCommands[v];
            if (c->mAnim != 0 ||
                (c->mDeferredIdx < 8 && c->mDeferred[c->mDeferredIdx][0] != 0))
                FUN_00a00f90(c, x);
        }
        p++;
        n--;
    } while (n != 0);
    mPrimary = ((XC*)this)->FUN_009ff380();
}

// @ 0x00a010c0
void QueuedBlender_s00a0_0980::UpdateCreatureBodies(uint a2, float a3, float a4, uint a5, uint a6, uint a7, float a8)
{
    bool bl = (a5 & 0xff) != 0;
    if (mFlagFac && !bl) {
        if (DAT_015509dc)
            FUN_009f9b40(mCreature);
        if (DAT_01550ad4)
            FUN_009fbb80(mCreature, a3);
        void* cr = mCreature;
        if (*(char*)((char*)cr + 0x260) && DAT_0166bff0 &&
            !*(char*)((char*)(*(void**)cr) + 0x3f5) && *(char*)((char*)cr + 0x168c))
            ((XC*)cr)->FUN_009b9090();
    }
    if (!bl) {
        float v = mEaseTime;
        if (v > 0.0f) {
            if (v > 1.0f) v = 1.0f;
        } else v = 0.0f;
        FUN_009bcab0(mCreature, 1.0f - v, v);
        if ((a6 & 0xff) != 0 && mEaseTime > 0.0f) {
            uint* p = mActive;
            int n = 0x10;
            do {
                uint idx = *p;
                if (idx < 0x10) {
                    AnimCommand* c = &mCommands[idx];
                    if (c->mAnim != 0 && c->mAnimBaked != 0 && c->mStatus != 0 &&
                        c->mWeight98 > 0.0f) {
                        float t = c->mWeight98 / mEaseTime;
                        float r = ((XC*)c->mAnimBaked)->FUN_009ac2b0(1.0f - t, t, 1, (uint)mCreature);
                        ((XC*)c->mAnimBaked)->FUN_009afe90(r * c->mBakeScale);
                    }
                }
                p++;
                n--;
            } while (n != 0);
        }
        {
            void* cr = mCreature;
            if (*(char*)((char*)cr + 0x260))
                FUN_009bd2b0(cr);
            FUN_009bcc70(cr, a3);
            if (!(DAT_0166cbec & 1)) {
                DAT_0166cbec |= 1;
                uint ecx = 1;
                uint edi = 7;
                uint esi = 0x20007;
                uint ebx = 0;
                do {
                    if (esi == 0) break;
                    uint edx = (esi - 1) & esi;
                    uint eax = edx ^ esi;
                    esi = eax;
                    esi &= edi;
                    esi = (uint)(-(int)esi);
                    esi = (uint)((int)esi >> 31);
                    esi &= ecx;
                    eax = ~eax;
                    ebx |= esi;
                    edi &= eax;
                    ecx += ecx;
                    esi = edx;
                } while (edi != 0);
                DAT_0166cbe8 = 1u << (ebx & 0x1f);
            }
            if ((mFlagFac || *(char*)((char*)cr + 0x2d5)) &&
                *(char*)((char*)cr + 0x260) && (a7 & DAT_0166cbe8))
                FUN_009a6cc0(a2, cr);
            if (DAT_015509dc)
                FUN_009bd550(a3, a4, cr, 1);
            if (DAT_015509f4 && *(char*)((char*)cr + 0x168c))
                FUN_009bd6f0(cr);
            FUN_009cb760(cr);
            FUN_009be150(cr);
        }
    }
    // L_a3
    if (mPrimary >= 0x10 && mQueueHead < 0x10) {
        if (mQueueHead == 0xffffffffu)
            mPrimary = ((XC*)this)->FUN_009ff380();
        else
            mPrimary = ((XC*)this)->FUN_009ff040();
    }
    {
        uint* p = mActive;
        int n = 0x10;
        do {
            uint idx = *p;
            if (idx < 0x10) {
                AnimCommand* c = &mCommands[idx];
                if (c->mAnim != 0 && c->mStatus != 0)
                    FUN_009a7f10(a2, mCreature, c->mAnim, a7, a8);
            }
            p++;
            n--;
        } while (n != 0);
    }
    uint i = 0;
    for (;;) {
        uint idx = mActive[i];
        if (idx < 0x10) {
            AnimCommand* c = &mCommands[idx];
            if (c->mAnim != 0 && c->mStatus != 0) {
                uint st = c->mStatus;
                if (st == 1) {
                    c->mTransition -= a3;
                    if (!(c->mTransition > 0.0f))
                        c->mStatus = 2;
                } else if (st == 2) {
                    if (c->mA0 == 0.0f) {
                        FUN_00a00f90(c, 0);
                    } else if (c->mA0 > 0.0f) {
                        int li = (int)(long long)(ceil((double)c->mA0) - 1.0);
                        if ((int)c->mSeq == li) {
                            double q = *(double*)((char*)c->mAnim + 0xb0) /
                                       *(double*)((char*)c->mAnim + 0xb8);
                            double ip;
                            double frac = modf(q, &ip);
                            if (q < 0.0) frac = 1.0 - frac;
                            double value =
                                (double)c->mHandle / *(double*)((char*)c->mAnim + 0xb8) +
                                ((double)c->mA0 - (double)c->mSeq);
                            if (frac >= value)
                                FUN_00a00f90(c, 0);
                        }
                    }
                } else if (st == 3) {
                    c->mTransition -= a3;
                    if (!(c->mTransition > 0.0f))
                        Deactivate(i);
                }
                if (c->mEnabled == 0) {
                    c->mSeq = *(uint*)((char*)c->mAnim + 0xc4);
                } else if (c->mStatus != 3 &&
                           (*(double*)((char*)c->mAnim + 0xb8) - (double)c->mDelay) <
                           *(double*)((char*)c->mAnim + 0xb0)) {
                    c->mSeq++;
                    uint ni = FUN_00a009e0(this);
                    if (ni >= 0x10) return;
                    AnimCommand* nc = &mCommands[ni];
                    ((XC*)nc)->FUN_009ffb50();
                    c->mCb2a = 0;
                    FUN_009ff880(c, nc);
                    uint k = 0;
                    uint* pp = mActive;
                    do {
                        if (*pp == 0xffffffffu) { mActive[k] = ni; break; }
                        k++;
                        pp++;
                    } while (k < 0x10);
                    if (c->mAnim != 0) {
                        void* oa = c->mAnim;
                        c->mAnim = 0;
                        ((XC*)oa)->FUN_009a3630();
                    }
                    if (c->mAnimBaked != 0) {
                        void* ob = c->mAnimBaked;
                        c->mAnimBaked = 0;
                        ((XC*)ob)->FUN_009ae1c0();
                    }
                    memset(&c->mDeferred[0][0], 0, 0x60);
                    c->mDeferredIdx = 0;
                    uint local = 0;
                    ((void (__cdecl*)(uint, QueuedBlender_s00a0_0980*, void*, int, uint*))c->mCb2)
                        (c->mCb2a, this, &c->mDeferred[0][0], 8, &local);
                    if (FUN_009ffa00(this, c)) {
                        if (c->mAnim != 0)
                            FUN_009a1ad0(c->mAnim);
                        c->mTransition = 0.0f;
                        c->mStatus = 0;
                    } else {
                        uint h = c->mSeqGen * 0x100 + 1 + (idx & 0xff);
                        AnimCommand* ret = FUN_00a00b10(this, c, h, a2);
                        if (c->mAnim != 0)
                            FUN_009a1ad0(c->mAnim);
                        c->mTransition = 0.0f;
                        c->mStatus = 0;
                        mActive[i] = 0xffffffffu;
                        ret->mPad7c = 1;
                        uint ri = (uint)(((char*)ret - (char*)mCommands) / 0xf0);
                        uint k2 = 0;
                        uint* pp2 = mActive;
                        do {
                            if (*pp2 == 0xffffffffu) { mActive[k2] = ri; break; }
                            k2++;
                            pp2++;
                        } while (k2 < 0x10);
                        if (mPrimary == i)
                            mPrimary = k2;
                    }
                }
            }
        }
        i++;
        if (i >= 0x10) return;
    }
}

// @ 0x00a01810
void qb_set_query(anim_qb* qb, int index, int mode, bool idle)
{
    if (mode == 0 && qb->field_FA0 == -1) {
        int i = qb->field_FA4;
        if (i >= 16) {
            mode = 1;
        } else if (qb->field_F0C[i] < 16) {
            int v = qb->field_F0C[i];
            if (v == qb->field_FA8 || *(int*)((char*)qb + v * 0xf0 + 0xc8) == 3)
                mode = 1;
        }
    }

    switch (mode) {
    case 0: {
        int n = qb->field_F9C + 1;
        n = n % 16;
        if (n < 0)
            n += 16;
        if (qb->field_FA0 >= 16) {
            qb->field_FA0 = n;
            qb->field_F9C = n;
            qb->field_F4C[n] = index;
            return;
        }
        if (qb->field_FA0 != n) {
            qb->field_F9C = n;
            qb->field_F4C[n] = index;
        }
        break;
    }
    case 1: {
        if (qb->field_FA4 < 16) {
            int a = qb->field_F0C[qb->field_FA4];
            if (a < 16) {
                anim_query* qA = &qb->queries[a];
                anim_query* qB = &qb->queries[index];
                q_swap(qB, qA);
                if (qA->field_C0 == 0) {
                    int cur = qb->field_F0C[qb->field_FA4];
                    int old = qb->field_FA8;
                    qb->field_F0C[qb->field_FA4] = -1;
                    if (cur != old || idle)
                        qA->Reset();
                }
            }
        }
        int i;
        for (i = 0; i < 16; ++i)
            if (qb->field_F0C[i] == -1)
                break;
        if (i < 16) {
            qb->field_F0C[i] = index;
            qb->field_FA4 = i;
            if (idle) {
                unsigned int old = qb->field_FA8;
                if (old < 16 && old != (unsigned int)index) {
                    if (qb->queries[old].Test())
                        qb->queries[old].Set670(1, 0);
                }
                qb->field_FA8 = index;
            }
        }
        qb->Commit();
        break;
    }
    case 2: {
        int i;
        for (i = 0; i < 16; ++i)
            if (qb->field_F0C[i] == -1)
                break;
        if (i < 16)
            qb->field_F0C[i] = index;
        break;
    }
    }
}
