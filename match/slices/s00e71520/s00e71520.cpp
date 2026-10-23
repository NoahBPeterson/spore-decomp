// Slice s00e71520 -- SPGonzago/SPCellGame.obj (batch spcg1).
// Cell-stage gameplay commands: build "cell command" records into the command pool
// (gCellGame+0x54) for the avatar and nearby cells, drive the cell step/announce state
// machine, and dispatch the gather/selected-cell scenes.
// Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU, no /EHsc).
//
// Offsets follow the retail disassembly. gCellGame is cCellGame (mCells object pool at
// +0x1c, command pool at +0x54, layer controller at +0x5190); gCellUI is the cell UI object.
// Camera forward is (0x16b3c28,0x16b3c2c,0x16b3c30); the orthogonal basis lives at
// 0x15a7c4c..0x15a7c58. kLevelSize is the per-level world-size table at 0x1483bd0.
#include "types.h"
#include <string.h>
#include <math.h>

// ---------------------------------------------------------------- globals
extern char*  gCellGame;          // 0x016b3c04
extern char*  gCellUI;            // 0x016b3c0c

extern float  gFwd_16b3c28;       // 0x016b3c28  camera forward
extern float  gFwd_16b3c2c;       // 0x016b3c2c
extern float  gFwd_16b3c30;       // 0x016b3c30

extern float  gBasis_15a7c4c;     // 0x015a7c4c  orthogonal basis
extern float  gBasis_15a7c50;
extern float  gBasis_15a7c54;
extern float  gBasis_15a7c58;

extern float  gLevelSize;         // 0x01483bd0  kLevelSize[] (indexed by level)

extern float  gk_13eb1bc;         // 0x013eb1bc  -1.0f sentinel
extern float  gk_1485720;         // 0x01485720  1.0f
extern float  gk_1488874;         // 0x01488874  0.1f
extern float  gk_13eb8a0;         // 0x013eb8a0  0.25f
extern float  gk_1440f84;         // 0x01440f84  1/6
extern float  gk_13f6bf8;         // 0x013f6bf8  0.033333335f
extern float  gk_1485378;         // 0x01485378  0.0f (epsilon compare)
extern float  gk_1471064;         // 0x01471064  0.5f
extern float  gk_13f9428;         // 0x013f9428  0.001f

// ---------------------------------------------------------------- object pools / temp ctx
// cObjectPool: GetSafe (+0x00b721d0) returns the object or null; Get (+0x00b72210) assumes
// the handle is live; Alloc (+0x00b72160) reserves a fresh handle in the pool.
struct cObjectPool {
    void* GetSafe(int id);   // 0x00b721d0
    void* Get(int id);       // 0x00b72210
    int   Alloc();           // 0x00b72160
};

// The scratch "layer catalog query" context (0x00743b50 ctor / 0x00e82130 dtor), thiscall.
struct cLayerCtx {
    void Begin();            // 0x00743b50
    void End();              // 0x00e82130
};

// A command record handed to the command pool. Field names describe usage in this slice.
struct cCellCmd {
    char  pad00[4];
    int   x04;               // +0x04
    char  x08;               // +0x08
    char  pad09[0x13];
    float t1c;               // +0x1c  duration A
    float t20;               // +0x20  duration B
    int   kind24;            // +0x24  command kind
    int   src28;             // +0x28  source handle
    int   arg2c;             // +0x2c
    int   arg30;             // +0x30
    int   arg34;             // +0x34
    int   arg38;             // +0x38
    int   arg3c;             // +0x3c
    float f40;               // +0x40
    float f44;               // +0x44
    float from48, from4c, from50;   // +0x48  start point
    float to54, to58, to5c;         // +0x54  end point
    float dir60, dir64, dir68, dir6c;// +0x60 direction / basis
    int   flag70;            // +0x70
    char  flag74;            // +0x74
    int   flag78;            // +0x78
};

// ---------------------------------------------------------------- callees (cdecl)
extern "C" void*  __cdecl FUN_00e4cc40(unsigned id, void* out);            // 0x00e4cc40 layer-catalog entry
extern "C" float  __cdecl FUN_00e69480(void* cell, int handle, int flag);  // 0x00e69480
extern "C" int    __cdecl FUN_00e693f0(void* cell, void* a, void* b, float f, int* out); // 0x00e693f0
extern "C" void   __cdecl FUN_00e52a00(void);                             // 0x00e52a00 frame tick
extern "C" float  __cdecl FUN_00e6d200(void* cell, int a, int b, int c);   // 0x00e6d200
extern "C" void*  __cdecl FUN_00e52910(int handle);                        // 0x00e52910
extern "C" int    __cdecl FUN_00e679e0(int a, int b, int c);               // 0x00e679e0
extern "C" int    __cdecl FUN_00e4cce0(int id);                            // 0x00e4cce0
extern "C" void*  __cdecl FUN_00e62200(int id, float f);                   // 0x00e62200
extern "C" int    __cdecl FUN_00e58980(void* a, void* b);                  // 0x00e58980
extern "C" void   __cdecl FUN_00e576f0(int handle);                        // 0x00e576f0 apply
extern "C" void   __cdecl FUN_00e58890(int a, int b, int c);               // 0x00e58890
extern "C" void   __cdecl FUN_00e67cb0(void* a, void* out);                // 0x00e67cb0
extern "C" int    __cdecl FUN_00e67c40(void* a, void* b);                  // 0x00e67c40
extern "C" void   __cdecl FUN_00e56f80(void* a, float* v);                 // 0x00e56f80 face
extern "C" void   __cdecl FUN_00e6eec0(int a, int b, float c, float d, float e); // 0x00e6eec0 StepCell
extern "C" int    __cdecl FUN_00e87260(int id, void* p, float f, int* out, int n, int z); // 0x00e87260
extern "C" int    __cdecl FUN_00e4ee60(void);                             // 0x00e4ee60 SP::sGetSourceLevel
extern "C" char   __cdecl FUN_00e57460(void* a, void* b);                  // 0x00e57460 same group
extern "C" void   __cdecl FUN_00e70950(void* cell, int param);             // 0x00e70950
extern "C" void   __cdecl FUN_00e70bc0(void* cell, int param);             // 0x00e70bc0
extern "C" float  __cdecl FUN_00e696a0(float* v, float dt);                // 0x00e696a0
extern "C" float  __cdecl FUN_00e695f0(float* v, float dt);                // 0x00e695f0
extern "C" float  __cdecl FUN_00e69740(float* v, float dt);                // 0x00e69740
extern "C" char   __cdecl FUN_00e507d0(float a, float b);                  // 0x00e507d0 predicate
extern "C" void   __cdecl FUN_00e69190(void* cell, float f, int* a, int* b, int* c, int d, int e); // 0x00e69190
extern "C" int    __cdecl FUN_00e573e0(void* a, void* b);                  // 0x00e573e0
extern "C" void   __cdecl FUN_00e5c8e0(void);                              // 0x00e5c8e0 spawn
extern "C" void   __cdecl FUN_00e59500(int handle);                        // 0x00e59500
extern "C" void*  __cdecl FUN_00e51ee0(int k, float f, int a, int b, int c, int d, int e,
                                       int f2, int g, int h, int i, int j, int l, int m, int n, int o); // 0x00e51ee0
extern "C" void   __cdecl FUN_00e592f0(int a, int b, int c, int d, int e); // 0x00e592f0

// thiscall helpers reached through the trigger manager / screen objects.
struct cTriggerMgr { void SetModal(int); };   // 0x00ad7e40
struct cTriggerMgr* GetTriggerMgr();          // 0x00b3d4d0

// ---------------------------------------------------------------- 0x00e71520
// Build the "gather cell" command: query the layer catalog entry for the cell's layer, run the
// command entity search (0x00e693f0), emit a leader command, then for each returned cell emit a
// follower command and update its 0x244 timer. Finishes with 0x00e58890.
// @ 0x00e71520
void FUN_00e71520(char* cell, int param2, int* param3)
{
    if (*(char*)(cell + 0x17f) == 1) return;

    char ctx[0x18];
    ((cLayerCtx*)ctx)->Begin();
    void* ent = FUN_00e4cc40(*(int*)(cell + 0x108), ctx);
    float f0 = FUN_00e69480(cell, (int)ent, 1);
    int list[512];
    int n = FUN_00e693f0(cell, param3, &param2, f0, list);
    FUN_00e52a00();

    void* cp = ((cObjectPool*)(gCellGame + 0x1c))->Get(*(int*)cell);
    float t = FUN_00e6d200(cp, 0, 0x1e, *(int*)((char*)cp + 0x1b0));

    cObjectPool* cmdp = (cObjectPool*)(gCellGame + 0x54);
    cCellCmd* cmd = (cCellCmd*)cmdp->Get(cmdp->Alloc());
    cmd->t1c = t; cmd->t20 = t;
    cmd->kind24 = 0x11;
    cmd->src28 = *(int*)cell;
    cmd->arg2c = *(int*)param3;
    cmd->arg30 = param2;
    cmd->arg34 = -1;
    cmd->arg38 = 0; cmd->arg3c = 0;
    cmd->f40 = 0.0f; cmd->f44 = 0.0f;
    cmd->from48 = gFwd_16b3c28; cmd->from4c = gFwd_16b3c2c; cmd->from50 = gFwd_16b3c30;
    cmd->to54   = gFwd_16b3c28; cmd->to58   = gFwd_16b3c2c; cmd->to5c   = gFwd_16b3c30;
    cmd->dir60 = gBasis_15a7c4c; cmd->dir64 = gBasis_15a7c50;
    cmd->dir68 = gBasis_15a7c54; cmd->dir6c = gBasis_15a7c58;
    cmd->flag70 = 0; cmd->flag74 = 0; cmd->flag78 = 0;
    cmd->x04 = 0; cmd->x08 = 0;

    void* s = FUN_00e52910((int)ent);
    int num;
    if (*(int*)s == 0x1001 || *(int*)(gCellGame + 0x411c) == *(int*)cell) {
        int x = FUN_00e679e0(*(int*)(cell + 0xfc), *(int*)(cell + 0x100), *(int*)(cell + 0x104));
        num = *(int*)(x + 0x126c);
        if (n <= num) num = n;
    } else {
        void* s2 = FUN_00e52910((int)ent);
        num = *(int*)((char*)s2 + 0x5c);
        if (n <= num) num = n;
    }

    for (int i = 0; i < num; i++) {
        int id = list[i];
        int k = 0xe;
        int kind = 1;
        void* a = ((cObjectPool*)(gCellGame + 0x1c))->Get(id);
        if (*(int*)((char*)a + 0x108) == FUN_00e4cce0(0x16)) { k = 0x3c; kind = 2; }

        void* b = ((cObjectPool*)(gCellGame + 0x1c))->Get(id);
        float t2 = FUN_00e6d200(b, 0, k, *(int*)((char*)b + 0x1b0));

        cCellCmd* cmd2 = (cCellCmd*)cmdp->Get(cmdp->Alloc());
        cmd2->t1c = t2; cmd2->t20 = t2;
        cmd2->kind24 = 2;
        cmd2->src28 = id;
        cmd2->arg2c = param2 - 0;
        cmd2->arg30 = param2;
        cmd2->arg34 = -1;
        cmd2->arg38 = kind;
        cmd2->arg3c = *(int*)(cell + 0x108);
        cmd2->f40 = 0.0f; cmd2->f44 = 0.0f;
        cmd2->from48 = gFwd_16b3c28; cmd2->from4c = gFwd_16b3c2c; cmd2->from50 = gFwd_16b3c30;
        cmd2->to54   = gFwd_16b3c28; cmd2->to58   = gFwd_16b3c2c; cmd2->to5c   = gFwd_16b3c30;
        cmd2->dir60 = gBasis_15a7c4c; cmd2->dir64 = gBasis_15a7c50;
        cmd2->dir68 = gBasis_15a7c54; cmd2->dir6c = gBasis_15a7c58;
        cmd2->flag70 = 0;
        cmd2->flag74 = (char)(*(int*)cell == *(int*)(gCellGame + 0x411c));
        cmd2->flag78 = 0;
        cmd2->x04 = 0; cmd2->x08 = 0;

        void* c = ((cObjectPool*)(gCellGame + 0x1c))->Get(id);
        *(float*)((char*)c + 0x90) = gFwd_16b3c28;
        *(float*)((char*)c + 0x94) = gFwd_16b3c2c;
        *(float*)((char*)c + 0x98) = gFwd_16b3c30;

        if ((*(int*)(gCellGame + 0x411c) == *(int*)cell || *(int*)(gCellGame + 0x411c) == *(int*)c)
            && *(int*)((char*)c + 0x248) != 0) {
            void* r = FUN_00e62200(*(int*)c, (float)*(int*)((char*)c + 0x244) * gk_1440f84);
            if (r != 0) *(float*)((char*)r + 0x24) = gk_1471064;
        }

        int* timer = (int*)((char*)c + 0x244);
        *timer -= FUN_00e58980(cell, c);
        if (*timer < 0) *timer = 0;
        FUN_00e576f0(*(int*)cell);
    }

    FUN_00e58890(*(int*)cell, *param3, param2);
    ((cLayerCtx*)ctx)->End();
}

// ---------------------------------------------------------------- 0x00e71980
// Cell step/announce state machine. Advances the two 0x158/0x15c timers, and when a timer
// crosses zero fires the announce predicate (0x00e507d0) and the follow-up cell command.
// @ 0x00e71980
void FUN_00e71980(char* cell, float dt)
{
    if (*(int*)(cell + 0xfc) == 0 || *(char*)(cell + 0x112) != 0) {
        *(float*)(cell + 0x158) = 0.0f;
        return;
    }

    float v[3];
    v[0] = *(float*)(cell + 0xfc);
    v[1] = *(float*)(cell + 0x100);
    v[2] = *(float*)(cell + 0x104);
    float f3 = FUN_00e696a0(v, dt);
    v[0] = *(float*)(cell + 0xfc);
    v[1] = *(float*)(cell + 0x100);
    v[2] = *(float*)(cell + 0x104);
    float f4 = FUN_00e695f0(v, dt);

    if (f3 == gk_13eb1bc) return;

    v[0] = *(float*)(cell + 0xfc);
    v[1] = *(float*)(cell + 0x100);
    v[2] = *(float*)(cell + 0x104);
    float f5 = FUN_00e69740(v, dt);
    float f6 = FUN_00e69480(cell, (int)dt, 0);

    if (*(float*)(cell + 0x158) <= 0.0f) {
        // --- timer 0x158 idle, try 0x15c ---
        if (!(*(float*)(cell + 0x15c) < 0.0f) && (f5 > 0.0f)) {
            float x = *(float*)(cell + 0x15c) - f5;
            *(float*)(cell + 0x15c) = x;
            if (!(x >= 1.0f) && (x > 0.0f)) {
                if (FUN_00e507d0(x, gk_13eb8a0)) {
                    if (*(int*)(cell + 0x248) != 0) {
                        *(char*)(cell + 0x18a) = 1;
                        *(float*)(cell + 0x160) = f6;
                        return;
                    }
                }
                *(char*)(cell + 0x18a) = 0;
                return;
            }
            goto announce;
        }
    }
    else {
        float x = *(float*)(cell + 0x158) - f5;
        *(float*)(cell + 0x158) = x;
        if (x >= 1.0f) return;
        if (x > 0.0f) {
            if (FUN_00e507d0(x, gk_1488874)) {
                if (*(int*)(cell + 0x248) != 0) {
                    *(char*)(cell + 0x18a) = 1;
                    *(float*)(cell + 0x160) = f6;
                    return;
                }
            }
            *(char*)(cell + 0x18a) = 0;
            return;
        }
    }

    *(float*)(cell + 0x158) = 0.0f;
    *(float*)(cell + 0x15c) = f5;

announce:
    if (*(int*)(cell + 0x248) == 0) {
        *(char*)(cell + 0x18a) = 0;
    } else {
        *(char*)(cell + 0x18a) = 1;
        *(float*)(cell + 0x160) = f6;
    }
    {
        int a, b, c;
        FUN_00e69190(cell, f4, &a, &b, &c, 0, 0);
        if (a != 0) {
            void* p = ((cObjectPool*)(gCellGame + 0x1c))->Get(a);
            FUN_00e71520(cell, b, &c);
            int r = FUN_00e573e0(cell, p);
            if (r < 2) {
                *(float*)(cell + 0x158) = f4;
                return;
            }
        }
    }
    *(float*)(cell + 0x158) = f3;
}

// ---------------------------------------------------------------- 0x00e71c00
// Announce one cell: pick the reachable record (0x248/0x194/0xe0 by controller mode), snap its
// facing to the avatar position (0x00e56f80) and step it (0x00e6eec0).
// @ 0x00e71c00
void FUN_00e71c00(int param1, int param2, int param3, int param4)
{
    char local[0x18];
    FUN_00e67cb0((void*)param1, local);

    int* pi;
    int mode = *(int*)(*(int*)(gCellGame + 0x5190) + 0x7c);
    if (mode == 0) {
        pi = (int*)(param2 + 0x248);
        if (*pi == -1) goto use_default;
    } else if (mode == 1) {
        goto use_default;
    } else if (mode == 2) {
        pi = (int*)(param2 + 0x194);
        if (*pi == -1) goto use_default;
    } else {
        goto use_default;
    }
    goto have;
use_default:
    pi = (int*)(param2 + 0xe0);
have:
    {
        int iVar1 = pi[0x10];
        int avatar = *(int*)(gCellGame + 0x411c);
        int uVar4 = FUN_00e67c40((void*)param1, (void*)param2);
        void* c = ((cObjectPool*)(gCellGame + 0x1c))->Get(avatar);
        float v[3];
        v[0] = *(float*)((char*)c + 0x4c);
        v[1] = *(float*)((char*)c + 0x50);
        v[2] = *(float*)((char*)c + 0x54);
        FUN_00e56f80((void*)param1, v);
        FUN_00e6eec0(param3, uVar4, *(float*)&iVar1, *(float*)&param4, 0.0f);
    }
}

// ---------------------------------------------------------------- 0x00e71ce0
// For every cell within the pick radius of the avatar (0x00e87260), split into the "near"
// (0x00e70950) and "far" (0x00e70bc0) announce paths by the 0xe0-record timer.
// @ 0x00e71ce0
void FUN_00e71ce0(int* cell, int param2)
{
    char ctx[0x18];
    ((cLayerCtx*)ctx)->Begin();
    int iVar5 = (int)FUN_00e4cc40(cell[0x42], ctx);

    int* pi;
    int mode = *(int*)(*(int*)(gCellGame + 0x5190) + 0x7c);
    if (mode == 0) {
        pi = (int*)(iVar5 + 0x248);
        if (*pi == -1) goto use_default;
    } else if (mode == 1) {
        goto use_default;
    } else if (mode == 2) {
        pi = (int*)(iVar5 + 0x194);
        if (*pi == -1) goto use_default;
    } else {
        goto use_default;
    }
    goto have;
use_default:
    pi = (int*)(iVar5 + 0xe0);
have:
    {
        float* near_t = (float*)(pi + 10);   // +0x28
        if (near_t[0] == 0.0f && *(float*)(pi + 0xe) == 0.0f) {
            ((cLayerCtx*)ctx)->End();
            return;
        }
        float* far_t = (float*)(pi + 0xe);
        if (*(float*)(pi + 0xe) < *near_t || *(float*)(pi + 0xe) == *near_t) far_t = near_t;

        int lvl = cell[0xd6];
        int iVar3 = (int)cell;
        if (lvl == -1) lvl = FUN_00e4ee60();
        float dist = ((float*)(&gLevelSize))[lvl] / *(float*)(gCellGame + 0x514c);
        int list[512];
        int cnt = FUN_00e87260(cell[0xd7], cell + 0x13, (dist * *far_t) * gk_13f6bf8,
                               list, 0x200, 0);

        for (int i = 0; i < cnt; i++) {
            void* p = ((cObjectPool*)(gCellGame + 0x1c))->Get(list[i]);
            if (FUN_00e57460(cell, p) && *(int*)p != *cell) {
                float dx = *(float*)((char*)cell + 0x4c) - *(float*)((char*)p + 0x4c);
                float dy = *(float*)((char*)cell + 0x50) - *(float*)((char*)p + 0x50);
                float dz = *(float*)((char*)cell + 0x54) - *(float*)((char*)p + 0x54);
                float d = (float)sqrt((double)(dz * dz + dy * dy) + (double)(dx * dx))
                          - *(float*)((char*)cell + 0x58) - *(float*)((char*)p + 0x58);
                float m = 0.0f;
                if (0.0f <= d) m = d;
                if (*(float*)(pi + 10) > m) {
                    *(int*)((char*)p + 0x220) = param2;
                    *(float*)((char*)p + 0x21c) = *(float*)(pi + 0xc);
                    FUN_00e70950(p, param2);
                } else if (m < *(float*)(pi + 0xe)) {
                    *(int*)((char*)p + 0x22c) = param2;
                    *(float*)((char*)p + 0x230) = *(float*)(pi + 0xf);
                    FUN_00e70bc0(p, param2);
                }
                (void)iVar3;
            }
        }
        ((cLayerCtx*)ctx)->End();
    }
}

// ---------------------------------------------------------------- 0x00e71f00
// Like 0x00e71ce0 but keyed on the 0xe0-record's +0x2c timer (all remaining cells of the same
// layer within the scaled pick radius), emitting the far announce path only.
// @ 0x00e71f00
void FUN_00e71f00(int* cell, int param2)
{
    char ctx[0x18];
    ((cLayerCtx*)ctx)->Begin();
    int iVar1 = (int)FUN_00e4cc40(cell[0x42], ctx);

    int* pi;
    int mode = *(int*)(*(int*)(gCellGame + 0x5190) + 0x7c);
    if (mode == 0) {
        pi = (int*)(iVar1 + 0x248);
        if (*pi == -1) goto use_default;
    } else if (mode == 1) {
        goto use_default;
    } else if (mode == 2) {
        pi = (int*)(iVar1 + 0x194);
        if (*pi == -1) goto use_default;
    } else {
        goto use_default;
    }
    goto have;
use_default:
    pi = (int*)(iVar1 + 0xe0);
have:
    if (*(float*)(pi + 0xb) == gk_1485378) {   // +0x2c == 0
        ((cLayerCtx*)ctx)->End();
        return;
    }

    int lvl = cell[0xd6];
    if (lvl == -1) lvl = FUN_00e4ee60();
    void* info = FUN_00e52910(iVar1);
    float scale = ((float*)(&gLevelSize))[lvl] / *(float*)(gCellGame + 0x514c);
    int list[512];
    int cnt = FUN_00e87260(cell[0xd7], cell + 0x13,
                           scale * *(float*)((char*)info + 0x2c) * gk_13f6bf8,
                           list, 0x200, 0);

    for (int i = 0; i < cnt; i++) {
        void* p = ((cObjectPool*)(gCellGame + 0x1c))->Get(list[i]);
        if (cell[0x42] == *(int*)((char*)p + 0x108) && *(int*)p != *cell) {
            *(int*)((char*)p + 0x220) = param2;
            void* q = FUN_00e52910(iVar1);
            *(float*)((char*)p + 0x21c) = *(float*)((char*)q + 0x34);
            FUN_00e70950(p, param2);
        }
    }
    ((cLayerCtx*)ctx)->End();
}

// ---------------------------------------------------------------- 0x00e72060
// Enter the gather scene: mark the cell, hide the screen modal, spawn the gather UI, emit the
// 0x1d "gather" command and flag the source cell for the pick.
// @ 0x00e72060
int FUN_00e72060(void* cell)
{
    *(char*)((char*)cell + 0x113) = 1;
    GetTriggerMgr()->SetModal(1);
    *(char*)(gCellUI + 0x936) = 1;
    FUN_00e5c8e0();

    void* c = ((cObjectPool*)(gCellGame + 0x1c))->Get(*(int*)cell);
    FUN_00e6d200(c, 0, 10, *(int*)((char*)c + 0x1b0));
    float f = FUN_00e6d200(c, 0, 7, *(int*)((char*)c + 0x1b0));

    cObjectPool* cmdp = (cObjectPool*)(gCellGame + 0x54);
    int slot = ((cObjectPool*)(gCellGame + 0x54))->Alloc();
    cCellCmd* cmd = (cCellCmd*)cmdp->Get(slot);
    cmd->t1c = f; cmd->t20 = f;
    cmd->kind24 = 0x1d;
    cmd->src28 = *(int*)cell;
    cmd->arg2c = 0;
    cmd->arg30 = -1;
    cmd->arg34 = -1;
    cmd->arg38 = 0; cmd->arg3c = 0;
    cmd->f40 = 0.0f; cmd->f44 = 0.0f;
    cmd->from48 = gFwd_16b3c28; cmd->from4c = gFwd_16b3c2c; cmd->from50 = gFwd_16b3c30;
    cmd->to54   = gFwd_16b3c28; cmd->to58   = gFwd_16b3c2c; cmd->to5c   = gFwd_16b3c30;
    cmd->dir60 = gBasis_15a7c4c; cmd->dir64 = gBasis_15a7c50;
    cmd->dir68 = gBasis_15a7c54; cmd->dir6c = gBasis_15a7c58;
    cmd->flag70 = 0; cmd->flag74 = 0; cmd->flag78 = 0;
    cmd->x04 = 0; cmd->x08 = 0;
    *(int*)(gCellGame + 0x5194) = slot;

    void* s = ((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)cell);
    if (s != 0) {
        *(char*)((char*)s + 0x16c) = 1;
        *(char*)((char*)s + 0x178) = 1;
        *(char*)((char*)s + 0x17c) = 1;
        *(int*)((char*)s + 0x18c) = 7;
    }
    *(int*)(gCellUI + 0xe0) = *(int*)cell;
    return 1;
}

// ---------------------------------------------------------------- 0x00e72200
// Toggle the gather cancel flag, or (when clearing) emit the 0x07 "cancel" command for the
// avatar, hide the modal and release the gather (0x00e59500).
// @ 0x00e72200
void FUN_00e72200(char flag)
{
    if (flag != 0) {
        *(char*)(gCellGame + 0x51d8) = 1;
        *(char*)(gCellGame + 0x51d9) = flag;
        return;
    }

    int avatar = *(int*)(gCellGame + 0x411c);
    void* c = ((cObjectPool*)(gCellGame + 0x1c))->Get(avatar);
    float f = FUN_00e6d200(c, 0, 9, *(int*)((char*)c + 0x1b0));

    cObjectPool* cmdp = (cObjectPool*)(gCellGame + 0x54);
    int slot = ((cObjectPool*)(gCellGame + 0x54))->Alloc();
    cCellCmd* cmd = (cCellCmd*)cmdp->Get(slot);
    cmd->t1c = f; cmd->t20 = f;
    cmd->kind24 = 7;
    cmd->src28 = avatar;
    cmd->arg2c = 0;
    cmd->arg30 = -1;
    cmd->arg34 = -1;
    cmd->arg38 = 0; cmd->arg3c = 0;
    cmd->f40 = 0.0f; cmd->f44 = 0.0f;
    cmd->from48 = gFwd_16b3c28; cmd->from4c = gFwd_16b3c2c; cmd->from50 = gFwd_16b3c30;
    cmd->to54   = gFwd_16b3c28; cmd->to58   = gFwd_16b3c2c; cmd->to5c   = gFwd_16b3c30;
    cmd->dir60 = gBasis_15a7c4c; cmd->dir64 = gBasis_15a7c50;
    cmd->dir68 = gBasis_15a7c54; cmd->dir6c = gBasis_15a7c58;
    cmd->flag70 = 0; cmd->flag74 = 0; cmd->flag78 = 0;
    cmd->x04 = 0; cmd->x08 = 0;

    GetTriggerMgr()->SetModal(1);
    *(char*)(gCellUI + 0x936) = 1;
    *(int*)(gCellGame + 0x5194) = slot;
    FUN_00e59500(avatar);
}

// ---------------------------------------------------------------- 0x00e72360
// Place the selected gather cell: skip if the source is flagged, build a 0x0a command via
// 0x00e51ee0 with the 0x1b0 duration, set its 0x0c scale to 0.001 and run 0x00e592f0.
// @ 0x00e72360
void FUN_00e72360(int* cell, int* other, int param3, int param4, int param5, int param6)
{
    if (*(char*)((char*)cell + 0x17f) == 1) return;
    if (FUN_00e57460(cell, other)) return;

    void* c = ((cObjectPool*)(gCellGame + 0x1c))->Get(*cell);
    float f = FUN_00e6d200(c, 0, 4, *(int*)((char*)c + 0x1b0));
    int slot = (int)FUN_00e51ee0(10, f, *cell, *other, param3, -1, param6, 0, 0, 0,
                                 param4, param5, 0, 0, 0, 0);
    void* p = ((cObjectPool*)(gCellGame + 0x54))->Get(slot);
    *(float*)((char*)p + 0x0c) = gk_13f9428;
    FUN_00e592f0(*cell, *other, param3, param4, param5);
}
