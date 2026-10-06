// Slice s009ffa00 -- nSPCreatureAnim::queued_blender goal helpers: handle-pair resolver,
// per-goal property setters, AnimGoal::Reset/operator=, queue reset.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: functions here use no EH frame)
#include "types.h"
#include <intrin.h>

extern "C" void* __cdecl operator_new(unsigned int size, const char* name,
                                      int a, int b, int c, int d);   // 0x00f473a0

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
struct TmpObj { void FUN_0099f0b0(); };       // 0x0099f0b0
struct CreatureInst {
    char pad[0x0];
    void Release();              // 0x009c4cc0 (nSPCreatureAnim::creature_instance_data::Release)
    void AddRef();               // 0x00a17060
};
struct ChildSlot { int id; float a; float b; };
struct AnimGoal;
struct GoalPool {                // eastl::vector<GoalObj*> of recycled objects
    GoalObj** begin;
    GoalObj** end;
    GoalObj** cap;
    void FUN_009ab170(GoalObj** where, AnimGoal* src);   // 0x009ab170 (thiscall)
};
extern GoalPool* g_goalPool;     // 0x0166c064
extern float g_defaultA;         // 0x01550b78
extern float g_defaultB;         // 0x01550b74

extern "C" void  __cdecl FUN_009a1ad0(GoalObj* p);                       // 0x009a1ad0
extern "C" GoalObj* __cdecl FUN_009a37a0(int key);                       // 0x009a37a0
extern "C" int   __cdecl FUN_009a4550(void* a, void* b);                 // 0x009a4550
extern "C" char  __cdecl FUN_009a38f0(void* a, int key, TmpObj** out);   // 0x009a38f0
extern "C" void  __cdecl FUN_009a3680(int a, int key);                   // 0x009a3680

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

struct GoalPair { AnimGoal* first; AnimGoal* second; };

// ---------------------------------------------------------------- goal-pair resolver

// @ 0x009FFE10
void __cdecl ResolveGoalPair(GoalPair* out, QueuedBlender* b, uint32_t handle) {
    AnimGoal* a = 0;
    AnimGoal* c = 0;
    if (handle != 0) {
        AnimGoal* g = (AnimGoal*)((char*)b + (handle & 0xff) * 0xf0 - 0xe8);
        if (g->field_b4 == (int)(handle >> 8)) {
            a = g;
            uint32_t h2 = (uint32_t)g->field_6c;
            if (h2 != 0) {
                AnimGoal* g2 = (AnimGoal*)((char*)b + (h2 & 0xff) * 0xf0 - 0xe8);
                if (g2->field_b4 == (int)(h2 >> 8))
                    c = g2;
            }
        }
    }
    out->second = c;
    out->first = a;
}

// Property setters: apply to the goal named by a handle and to its linked goal.
#define SETTER_BOTH(VA, NAME, FIELD, TYPE)                                       \
    /* @ 0x ## VA */                                                             \
    int __cdecl NAME(QueuedBlender* b, uint32_t handle, TYPE v) {               \
        GoalPair p;                                                              \
        ResolveGoalPair(&p, b, handle);                                          \
        if (p.first)  p.first->FIELD = v;                                        \
        if (p.second) p.second->FIELD = v;                                       \
        if (p.first == 0 && p.second == 0)                                       \
            return 0;                                                            \
        return 1;                                                                \
    }

// @ 0x009FFE80
SETTER_BOTH(009FFE80, SetGoalField8c, field_8c, float)
// @ 0x009FFEE0
SETTER_BOTH(009FFEE0, SetGoalFieldA0, field_a0, float)
// @ 0x009FFF40
SETTER_BOTH(009FFF40, SetGoalField70, field_70, float)
// @ 0x009FFF90
SETTER_BOTH(009FFF90, SetGoalField74, field_74, float)
// @ 0x009FFFE0
SETTER_BOTH(009FFFE0, SetGoalField78, field_78, float)
// @ 0x00A00030
SETTER_BOTH(00A00030, SetGoalFieldBC, field_bc, int)
// @ 0x00A00080
SETTER_BOTH(00A00080, SetGoalFieldD8, field_d8, int)
// @ 0x00A000D0
SETTER_BOTH(00A000D0, SetGoalFieldC8, field_c8, float)
// @ 0x00A00130
SETTER_BOTH(00A00130, SetGoalFieldDC, field_dc, int)
// @ 0x00A001F0
SETTER_BOTH(00A001F0, SetGoalField80, field_80, int)
// @ 0x00A00240
SETTER_BOTH(00A00240, SetGoalField84, field_84, uint8_t)
// @ 0x00A00290
SETTER_BOTH(00A00290, SetGoalField88, field_88, float)

// @ 0x00A00180
int __cdecl SetGoalFieldE0(QueuedBlender* b, uint32_t handle, int lo, int hi) {
    GoalPair p;
    ResolveGoalPair(&p, b, handle);
    if (p.first) {
        p.first->field_e0 = lo;
        p.first->field_e4 = hi;
    }
    if (p.second) {
        p.second->field_e0 = lo;
        p.second->field_e4 = hi;
    }
    if (p.first == 0 && p.second == 0)
        return 0;
    return 1;
}

// @ 0x00A002F0
int __cdecl SetGoalFlagD4(QueuedBlender* b, uint32_t handle, char v) {
    GoalPair p;
    ResolveGoalPair(&p, b, handle);
    if (p.first) {
        p.first->field_d4 = v;
        if (p.first->field_00)
            p.first->field_00->field_ad = v;
    }
    if (p.first == 0 && p.second == 0)
        return 0;
    return 1;
}

// @ 0x00A00340
int __cdecl SetGoalFieldCC(QueuedBlender* b, uint32_t handle, float v) {
    GoalPair p;
    ResolveGoalPair(&p, b, handle);
    if (p.first) {
        p.first->field_cc = v;
        if (p.first->field_00)
            p.first->field_00->field_b8 = v;
    }
    if (p.second) {
        p.second->field_cc = v;
        if (p.second->field_00)
            p.second->field_00->field_b8 = v;
    }
    if (p.first == 0 && p.second == 0)
        return 0;
    return 1;
}

// @ 0x00A003C0
int __cdecl ScaleGoalFieldD0(QueuedBlender* b, uint32_t handle, float v) {
    GoalPair p;
    ResolveGoalPair(&p, b, handle);
    if (p.first) {
        p.first->field_d0 = v;
        if (p.first->field_00)
            p.first->field_00->field_b8 = v * p.first->field_00->field_b8;
    }
    if (p.second) {
        p.second->field_d0 = v;
        if (p.second->field_00)
            p.second->field_00->field_b8 = v * p.second->field_00->field_b8;
    }
    if (p.first == 0 && p.second == 0)
        return 0;
    return 1;
}

// @ 0x00A00450
bool __cdecl SetGoalFieldE8(QueuedBlender* b, uint32_t handle, int lo, int hi) {
    GoalPair p;
    ResolveGoalPair(&p, b, handle);
    AnimGoal* a = p.first;
    if (a) {
        a->field_e8 = lo;
        a->field_ec = hi;
    }
    return (bool)a;
}

// @ 0x009FFDB0
bool __cdecl IsPendingGoal(QueuedBlender* b, uint32_t handle) {
    extern AnimGoal* __cdecl FindGoalByHandle(QueuedBlender*, uint32_t);   // 0x009ff6f0
    AnimGoal* g = 0;
    if (handle != 0) {
        g = FindGoalByHandle(b, handle);
    } else {
        if (b->mCurrent < 0x10) {
            uint32_t v = b->mActive[b->mCurrent];
            if (v < 0x10)
                g = (AnimGoal*)((char*)b + v * 0xf0 + 8);
        }
    }
    return g == (AnimGoal*)((char*)b + b->mPending * 0xf0 + 8);
}

// ---------------------------------------------------------------- AnimGoal copy / reset

// @ 0x009FFB50
AnimGoal* AnimGoal::operator=(AnimGoal* o) {
    GoalObj* n0 = o->field_00;
    GoalObj* old0 = field_00;
    if (n0 != old0) {
        if (n0)
            n0->AddRef();
        field_00 = n0;
        if (old0)
            old0->Release();
    }
    GoalObj2* n1 = o->field_04;
    GoalObj2* old1 = field_04;
    if (n1 != old1) {
        if (n1)
            n1->AddRef();
        field_04 = n1;
        if (old1)
            old1->Release();
    }
    mChildren[0] = o->mChildren[0];
    mChildren[1] = o->mChildren[1];
    mChildren[2] = o->mChildren[2];
    mChildren[3] = o->mChildren[3];
    mChildren[4] = o->mChildren[4];
    mChildren[5] = o->mChildren[5];
    mChildren[6] = o->mChildren[6];
    mChildren[7] = o->mChildren[7];
    mChildren[8] = o->mChildren[8];
    mChildren[9] = o->mChildren[9];
    mChildren[10] = o->mChildren[10];
    mChildren[11] = o->mChildren[11];
    mChildren[12] = o->mChildren[12];
    mChildren[13] = o->mChildren[13];
    mChildren[14] = o->mChildren[14];
    mChildren[15] = o->mChildren[15];
    mChildren[16] = o->mChildren[16];
    mChildren[17] = o->mChildren[17];
    mChildren[18] = o->mChildren[18];
    mChildren[19] = o->mChildren[19];
    mChildren[20] = o->mChildren[20];
    mChildren[21] = o->mChildren[21];
    mChildren[22] = o->mChildren[22];
    mChildren[23] = o->mChildren[23];
    mChildCount = o->mChildCount;
    field_6c = o->field_6c;
    field_70 = o->field_70;
    field_74 = o->field_74;
    field_78 = o->field_78;
    field_7c = o->field_7c;
    field_80 = o->field_80;
    field_84 = o->field_84;
    field_88 = o->field_88;
    field_8c = o->field_8c;
    field_90 = o->field_90;
    field_94 = o->field_94;
    field_98 = o->field_98;
    field_9c = o->field_9c;
    field_9d = o->field_9d;
    field_a0 = o->field_a0;
    field_a8 = o->field_a8;
    field_b0 = o->field_b0;
    field_b4 = o->field_b4;
    field_b8 = o->field_b8;
    field_bc = o->field_bc;
    field_c0 = o->field_c0;
    field_c4 = o->field_c4;
    field_c8 = o->field_c8;
    field_cc = o->field_cc;
    field_d0 = o->field_d0;
    field_d4 = o->field_d4;
    field_d8 = o->field_d8;
    field_dc = o->field_dc;
    field_e0 = o->field_e0;
    field_e4 = o->field_e4;
    field_e8 = o->field_e8;
    field_ec = o->field_ec;
    return this;
}

// @ 0x00A00490
void AnimGoal::Reset() {
    GoalObj* p = field_00;
    field_a8 = 0.0;
    field_70 = 0.0f;
    field_74 = 0.0f;
    field_78 = 0.0f;
    field_7c = 0;
    field_88 = 0.0f;
    field_80 = 1;
    field_84 = 0;
    field_94 = 1.0f;
    field_98 = 0.0f;
    field_8c = 0.0f;
    field_90 = 1.0f;
    field_cc = -1.0f;
    field_d0 = 1.0f;
    field_d4 = 0;
    field_9c = 0;
    field_9d = 0;
    field_a0 = 0.0f;
    field_b0 = 0;
    field_b4 = 0;
    field_b8 = 0.0f;
    field_bc = 0;
    field_c0 = 0;
    field_c4 = 0.0f;
    field_c8 = 0.0f;
    if (p) {
        FUN_009a1ad0(p);
        field_00->FUN_009a3080(0);
        GoalPool* pool = g_goalPool;
        GoalObj** top = pool->end;
        if (top < pool->cap) {
            pool->end = top + 1;
            if (top) {
                GoalObj* q = field_00;
                *top = q;
                if (q)
                    q->AddRef();
            }
        } else {
            pool->FUN_009ab170(top, this);
        }
        if (field_00) {
            GoalObj* t = field_00;
            field_00 = 0;
            t->Release();
        }
    }
    if (field_04) {
        GoalObj2* t = field_04;
        field_04 = 0;
        t->Release();
    }
    // children 0..7: {obj, -1.0f, 1.0f}
    ChildSlot* cs = (ChildSlot*)mChildren;
    for (int i = 0; i < 8; ++i) {
        cs[i].id = 0;
        cs[i].b = 1.0f;
        cs[i].a = -1.0f;
    }
    mChildCount = 0;
    field_6c = 0;
    field_d8 = 0;
    field_dc = 0;
    field_e0 = 0;
    field_e4 = 0;
    field_e8 = 0;
    field_ec = 0;
}

// @ 0x00A00670
void AnimGoal::Stop(char a, char b) {
    if (b == 0 && (field_00 != 0 || ((uint32_t)mChildCount < 8 && mChildren[mChildCount * 3] != 0)) &&
        field_c0 != 0) {
        if (field_c0 != 3) {
            field_c0 = 3;
            field_c4 = field_78;
        }
    } else if (a != 0) {
        Reset();
    } else {
        if (field_00)
            FUN_009a1ad0(field_00);
        field_c4 = 0.0f;
        field_c0 = 0;
    }
}

// ---------------------------------------------------------------- queue operations

// @ 0x00A006F0
void QueuedBlender::SelectPending(uint32_t handle) {
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

// @ 0x00A007D0
void QueuedBlender::ResetAll(char full) {
    if (full) {
        mSeq = 1;
        _ReadWriteBarrier();
        CreatureInst* c = field_fbc;
        if (c) {
            field_fbc = 0;
            c->Release();
        }
        field_fc0 = 0;
    }
    field_fac = 0;
    field_fb0 = 0.0f;
    field_f08 = 0xffffffff;
    field_f9c = -1;
    field_fa0 = -1;
    mCurrent = 0xffffffff;
    mPending = 0xffffffff;
    field_fb4 = 1.0f;
    field_fb8 = 0.0f;
    field_fc4 = g_defaultA;
    float fb = g_defaultB;
    field_fcc = 0;
    field_fc8 = fb;
    for (int i = 0; i < 16; ++i) {
        mGoals[i].Reset();
        mActive[i] = 0xffffffff;
        mQueue[i] = 0xffffffff;
    }
}

// @ 0x00A008B0
void QueuedBlender::ClearPendingGoal() {
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

// @ 0x00A00910
void QueuedBlender::SetCreature(CreatureInst* c, int v) {
    ResetAll(1);
    CreatureInst* old = field_fbc;
    if (c != old) {
        if (c)
            c->AddRef();
        field_fbc = c;
        if (old)
            old->Release();
    }
    field_fc0 = v;
}

// ---------------------------------------------------------------- goal child loading

// @ 0x009FFA00
bool __cdecl LoadGoalChildren(QueuedBlender* b, AnimGoal* g) {
    while ((uint32_t)g->mChildCount < 8) {
        int key = g->mChildren[g->mChildCount * 3];
        GoalObj* o = FUN_009a37a0(key);
        if (o == 0) {
            TmpObj* tmp = 0;
            if (!FUN_009a38f0(*(void**)b->field_fbc, key, &tmp)) {
                FUN_009a3680(0, key);
                if (tmp)
                    tmp->FUN_0099f0b0();
                return false;
            }
            ++g->mChildCount;
            if (tmp)
                tmp->FUN_0099f0b0();
        } else {
            int r = FUN_009a4550(*(void**)b->field_fbc, o);
            if (r != 0) {
                GoalObj* old;
                if (g_goalPool->begin == g_goalPool->end) {
                    GoalObj* mem = (GoalObj*)operator_new(0xe0, "Anim/aid", 0, 0, 0, 0);
                    GoalObj* n = mem ? mem->FUN_009a34a0() : 0;
                    old = g->field_00;
                    if (n != old) {
                        if (n)
                            n->AddRef();
                        g->field_00 = n;
                        if (old)
                            old->Release();
                    }
                } else {
                    g->FUN_009aa4c0(g_goalPool->end - 1);
                    g_goalPool->end -= 1;
                    old = *g_goalPool->end;
                    if (old)
                        old->Release();
                }
                g->field_00->FUN_009a3220((int)o, b->field_fbc, r);
                return true;
            }
            ++g->mChildCount;
        }
    }
    return true;
}
