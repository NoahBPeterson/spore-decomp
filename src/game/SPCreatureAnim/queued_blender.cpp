// src/game/SPCreatureAnim/queued_blender.cpp -- migrated from slice(s) s009feb30 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/queued_blender.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPCreatureAnim/queued_blender.h"
#include "EA/ArgScript/cCommandBase.h"
#include "nSPCreatureAnim/creature_instance_data.h"
#pragma optimize("gt", off)

// ---- items of slice s009feb30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {} };
struct CreatureStatic { char pad[0x3f5]; char field_3f5; };
struct CreatureSub {
    int field_00;
    void FUN_009e3f70(int a, int b);                              // 0x009e3f70
    void FUN_009e4600(Vec3 v, int a, int b, int c, int d);        // 0x009e4600
};
struct CreatureInst {
    CreatureStatic* mStatic;       // +0x00
    char   pad_04[0x6c];
    float  mScale;                 // +0x70
    char   pad_74[0x1ec];
    char   field_260;              // +0x260
    char   pad_261[3];
    float  field_264;
    float  field_268;
    float  field_26c;
    char   pad_270[0x88];
    CreatureSub mSub;              // +0x2f8
    char   pad_2f8[0x1680 - 0x2f8 - 4 - 0];
    char   field_1680;
    char   pad_1681[0xb];
    char   field_168c;
    void FUN_009b8760(float dt);                                  // 0x009b8760
    void FUN_009b7b10(int a, int b);                              // 0x009b7b10
    void FUN_009b8720(float a);                                   // 0x009b8720
    void FUN_009b8d50(float dt);                                  // 0x009b8d50
    void FUN_009b8e40(float a);                                   // 0x009b8e40
    void FUN_009ba040(float dt, float a);                         // 0x009ba040
    void FUN_009c0680();                                          // 0x009c0680
    void FUN_009b8f40(float a);                                   // 0x009b8f40
    void UpdateWiggles(float dt, float a);                        // 0x009bb4f0
};
struct AnimGoal {
    int      field_00;       // +0x00
    int      field_04;       // +0x04
    int      mChildren[24];  // +0x08  (8 slots * 3 dwords, stride 0x0c)
    int      mChildCount;    // +0x68
    int      field_6c;       // +0x6c  packed handle of the active child
    float    field_70;       // +0x70
    float    field_74;       // +0x74
    float    field_78;       // +0x78
    uint8_t  field_7c;       // +0x7c
    char     pad_7d[3];
    int      field_80;       // +0x80
    uint8_t  field_84;       // +0x84
    char     pad_85[3];
    float    field_88;       // +0x88
    float    field_8c;       // +0x8c
    char     pad_90[4];
    float    field_94;       // +0x94
    char     pad_98[8];
    float    field_a0;       // +0xa0
    char     pad_a4[4];
    double   field_a8;       // +0xa8
    char     pad_b0[4];
    uint32_t field_b4;       // +0xb4
    char     pad_b8[4];
    int      field_bc;       // +0xbc
    int      field_c0;       // +0xc0
    float    field_c4;       // +0xc4
    char     pad_c8[4];
    float    field_cc;       // +0xcc
    float    field_d0;       // +0xd0
    uint8_t  field_d4;       // +0xd4
    char     pad_d5[3];
    int      field_d8;       // +0xd8
    char     pad_dc[0xf0 - 0xdc];

    void Init();
    void CopyFiltersFrom(AnimGoal* o);
    int  IsActive();
};
struct QueuedBlender {
    char     pad_00[8];
    AnimGoal mGoals[16];     // +0x08, stride 0xf0
    char     pad_f08[4];
    uint32_t mActive[16];    // +0xf0c
    uint32_t mQueue[16];     // +0xf4c
    uint32_t field_f8c;      // +0xf8c
    char     pad_f90[0xc];
    int      field_f9c;      // +0xf9c  queue write cursor
    int      field_fa0;      // +0xfa0  queue read cursor
    uint32_t mCurrent;       // +0xfa4
    uint32_t mPending;       // +0xfa8
    uint8_t  field_fac;      // +0xfac
    char     pad_fad[3];
    float    field_fb0;      // +0xfb0
    float    field_fb4;      // +0xfb4
    char     pad_fb8[4];
    CreatureInst* field_fbc;  // +0xfbc

    int      Count();
    int      FindFreeSlot();            // FUN_009ff380
    void     TransitionToNextAnimation();  // FUN_009ff440
    void     UpdateGoals(float dt, char param_3);
    int      QueuedToActive();
};
// ---- items of slice s009feb30 end

// @ 0x009fef70
#pragma optimize("", on)
int __cdecl packHandle(int base, uint8_t index)
{
    return (base << 8) + 1 + (int)index;
}

// @ 0x009fef90
int __cdecl packGoalHandle(QueuedBlender* blender, AnimGoal* goal)
{
    int result;
    if (goal != 0) {
        int idx = (int)((char*)goal - (char*)blender - 8) / 0xf0;
        result = (uint8_t)idx + 1 + (int)goal->field_b4 * 0x100;
    } else {
        result = 0;
    }
    return result;
}

// @ 0x009fefd0
int QueuedBlender::Count()
{
    uint32_t read = (uint32_t)field_fa0;
    int result = 0;
    if (read != 0xffffffff) {
        uint32_t write = (uint32_t)field_f9c;
        if (read <= write)
            result = (int)(write - read) + 1;
        else
            result = (int)(write + read) + 0x11;
    }
    return result;
}

// @ 0x009ff020
int AnimGoal::IsActive()
{
    if (field_00 == 0 && ((uint32_t)mChildCount >= 8 || mChildren[mChildCount * 3] == 0))
        return 0;
    return 1;
}

// @ 0x009ff440
void QueuedBlender::TransitionToNextAnimation()
{
    uint32_t old = (mCurrent < 0x10) ? mActive[mCurrent] : 0xffffffff;
    if (mCurrent >= 0x10)
        return;
    int next;
    if (field_fa0 != -1)
        next = QueuedToActive();
    else
        next = FindFreeSlot();
    mCurrent = (uint32_t)next;
    uint32_t cur = mActive[next];
    if (old == cur && cur < 0x10) {
        AnimGoal* g = (AnimGoal*)((char*)this + cur * 0xf0 + 8);
        if (g->field_c0 == 0)
            mCurrent = 0xffffffff;
    }
}
