// Slice s00e794f0 -- SPGonzago/SPCellGame.obj (batch spcg1).
// The "goldy" cinematic sequence plus the digestion/eat step machine: enter the goldy
// cinematic, place the two goldy cells and post the trigger, then the per-cell eat/digest
// timers (0x21c/0x224/0x228/0x230/0x234/0x238) that drive assist/far announce steps and the
// final digestion loot drop.
// Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU, no /EHsc).
//
// Layouts follow the dev-build PDB with retail offsets confirmed against the disassembly.
// gCellGame is cCellGame (mCells pool at +0x1c, command pool at +0x54, layer controller at
// +0x5190); gCellUI is the cell UI object. Camera forward is (0x16b3c28,0x16b3c2c,0x16b3c30);
// the orthogonal basis lives at 0x15a7c4c..0x15a7c58. A cell's position is at +0x4c.
#include "types.h"
#include <math.h>
#include <string.h>

// ---------------------------------------------------------------- globals
extern char*  gCellGame;          // 0x016b3c04
extern char*  gCellUI;            // 0x016b3c0c

extern int    gFwd_16b3c28;       // 0x016b3c28  camera forward (copied as raw dwords)
extern int    gFwd_16b3c2c;       // 0x016b3c2c
extern int    gFwd_16b3c30;       // 0x016b3c30

extern int    gBasis_15a7c4c;     // 0x015a7c4c  orthogonal basis
extern int    gBasis_15a7c50;
extern int    gBasis_15a7c54;
extern int    gBasis_15a7c58;

extern float  gK_1471064;         // 0x01471064  0.5f
extern float  gK_13ec4b8;         // 0x013ec4b8  1e-08f
extern float  gK_13ec480;         // 0x013ec480  0.2f
extern float  gK_13eb8a0;         // 0x013eb8a0  0.25f
extern float  gK_1473c70;         // 0x01473c70  10.0f
extern float  gK_1486110;         // 0x01486110  5.0f
extern float  gK_14007f4;         // 0x014007f4  15.0f
extern float  gK_1414a84;         // 0x01414a84  3.5f
extern float  gK_1483f34;         // 0x01483f34  4.5f
extern float  gK_13eecd8;         // 0x013eecd8  20.0f
extern float  gK_14853e0;         // 0x014853e0  4.0f
extern float  gK_13ec5b4;         // 0x013ec5b4  1000.0f

// ---------------------------------------------------------------- object pools
// cObjectPool: GetSafe (+0x00b721d0) returns the object or null; Get (+0x00b72210) assumes
// the handle is live; Alloc (+0x00b72160) reserves a fresh handle in the pool.
struct cObjectPool {
    void* GetSafe(int id);   // 0x00b721d0
    void* Get(int id);       // 0x00b72210
    int   Alloc();           // 0x00b72160
};

// Trigger / simulation manager reached through 0x00b3d4d0.
struct cTriggerMgr {
    void goExit();                                                  // 0x00ad7df0 Sim::goExit
    void PostTrigger(const char* name, int a, int b, int c, int d, int e); // 0x00ae0930
};
cTriggerMgr* GetTriggerMgr();   // 0x00b3d4d0

// A command record handed to the command pool (same layout as the sibling slices): +0x04 holds
// either 0 or a callback pointer, +0x24 the command kind, +0x28 the source handle.
struct cCellCmd {
    char  pad00[4];
    int   x04;               // +0x04  callback / 0
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
    int   from48, from4c, from50;   // +0x48  start point (raw dwords)
    int   to54, to58, to5c;         // +0x54  end point
    int   dir60, dir64, dir68, dir6c;// +0x60 direction / basis
    int   flag70;            // +0x70
    char  flag74;            // +0x74
    int   flag78;            // +0x78
};

namespace SP { void sCinematicGoldy_Start(void); }

// ---------------------------------------------------------------- callees
extern "C" void  FUN_00e780a0(int handle, int a, float f, int b);          // 0x00e780a0
extern "C" void  FUN_00e5f010(int a, int b, float d, int c);               // 0x00e5f010
extern "C" void  __fastcall FUN_00e79460(float* center, int pool, float radius, int exclude); // 0x00e79460
extern "C" void  __fastcall FUN_00e78b20(float* center, int pool, float radius, int exclude); // 0x00e78b20
extern "C" float* FUN_00e5eb20(float* out, int cell);                      // 0x00e5eb20 world-axis bias
extern "C" void  FUN_00e577a0(int cell, float* dir);                       // 0x00e577a0
extern "C" int   FUN_00e5cde0(void* cell);                                 // 0x00e5cde0 cell-visibility
extern "C" int   FUN_00e4cce0(int id);                                     // 0x00e4cce0 LayerCatalog_GetEntry
extern "C" void* FUN_00e74a20(int pool, void* pos, int z, int entry);      // 0x00e74a20 CreateCell
extern "C" void  FUN_00e70e30(int a, int b, float c);                      // 0x00e70e30
extern "C" float FUN_00e6d200(int cell, int a, int b, int c);              // 0x00e6d200
extern "C" void* FUN_00e52910(int handle);                                 // 0x00e52910 resolve handle
extern "C" int   FUN_00e67c40(int a, int b);                               // 0x00e67c40
extern "C" void  FUN_00e6f660(int cell, float* pos, float dt, float f, int x); // 0x00e6f660
extern "C" void  FUN_00e6f800(int cell, int handle, float dt, float f, int x); // 0x00e6f800
extern "C" void  FUN_00e6f940(int cell, int handle, float f, int x);       // 0x00e6f940
extern "C" void  FUN_00e6ff60(int cell, float f, int x);                   // 0x00e6ff60
extern "C" char  FUN_00e57ce0(int cell, int handle);                       // 0x00e57ce0
extern "C" int   FUN_00e4ee60(void);                                       // 0x00e4ee60 SP::sGetSourceLevel
extern "C" void  FUN_00e791f0(int cell, int handle, float dt);             // 0x00e791f0 SP::sDigestionOutput
extern "C" void  FUN_00e771d0(int a, int b, int c, float* p, float d,
                              int e, int f, float g, int h, int i);        // 0x00e771d0 SP::sDropLoot

// ---------------------------------------------------------------- 0x00e794f0
// Enter the "goldy" cinematic: reset the layer controller's 0x90 block, exit the simulation,
// clear the UI + record state, hide/collapse the other goldy cell, and snap the camera-follow
// point to either the recorded cell position or the camera forward depending on `back`.
// @ 0x00e794f0
void FUN_00e794f0(int a, int b, float c, char back)
{
    char* lc = *(char**)(gCellGame + 0x5190);
    *(int*)(lc + 0x90)   = 1;
    *(int*)(lc + 0x94)   = 0;
    *(int*)(lc + 0x98)   = 0;
    *(float*)(lc + 0x9c) = 0.0f;

    GetTriggerMgr()->goExit();

    char* self = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(gCellGame + 0x411c));
    if (self == 0) return;

    *(int*)(gCellUI + 0xe0)   = 0;
    *(float*)(gCellUI + 0xf4) = gK_1414a84;

    char* t = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(b);
    if (t != 0) *(char*)(t + 0x354) = 0;

    char* o = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(a);
    if (o != 0) {
        if (FUN_00e5cde0(o)) {
            FUN_00e5f010(*(int*)o, *(int*)(gCellGame + 0x411c), gK_1483f34, 0);
        }
        FUN_00e780a0(a, 1, c, 0);
    }

    FUN_00e79460((float*)(self + 0x4c), *(int*)(gCellGame + 0x40fc), gK_1473c70,
                 *(int*)(gCellGame + 0x411c));

    if (back == 0) {
        *(int*)(self + 0x170)     = *(int*)(gCellGame + 0x516c);
        *(int*)(gCellUI + 0xe0)   = *(int*)(gCellGame + 0x411c);
        *(float*)(gCellUI + 0xf4) = gK_1486110;
        *(float*)(gCellUI + 0x80) = gK_13eecd8;
        FUN_00e5f010(*(int*)(gCellGame + 0x411c), *(int*)(gCellGame + 0x516c), gK_1483f34, 0);
    } else {
        *(float*)(gCellUI + 0x80) = gK_13eecd8;
        *(float*)(gCellUI + 0x48) = *(float*)(self + 0x4c);
        *(float*)(gCellUI + 0x4c) = *(float*)(self + 0x50);
        *(float*)(gCellUI + 0x50) = *(float*)(self + 0x54);
        *(float*)(gCellUI + 0x54) = *(float*)(gCellUI + 0x48);
        *(float*)(gCellUI + 0x58) = *(float*)(gCellUI + 0x4c);
        *(float*)(gCellUI + 0x5c) = *(float*)(gCellUI + 0x50);
        *(float*)(gCellUI + 0x60) = *(float*)(gCellUI + 0x48);
        *(float*)(gCellUI + 0x64) = *(float*)(gCellUI + 0x4c);
        *(float*)(gCellUI + 0x68) = *(float*)(gCellUI + 0x50);
        FUN_00e5f010(*(int*)(gCellGame + 0x516c), *(int*)(gCellGame + 0x411c), gK_1483f34, 0);
    }
    *(char*)(gCellGame + 0x518c) = 0;
}

// ---------------------------------------------------------------- 0x00e79720
// SP::sCinematicGoldy_Start: place the two goldy cinematic cells (layers 1 and 2), flag the
// acting cell, build the 0x24 "goldy" command, publish the active gather slot and post the
// "goldies_demise" trigger.
// @ 0x00e79720
void SP::sCinematicGoldy_Start(void)
{
    if (*(char*)(gCellGame + 0x410c) != 0) return;

    char* self = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(gCellGame + 0x411c));
    if (self == 0) return;

    *(char*)(*(int*)(gCellGame + 0x5190) + 0x68) = 1;

    char* c = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(gCellGame + 0x516c));
    if (c != 0) FUN_00e780a0(*(int*)c, 0, 0.0f, 0);

    char scratch[0x18];
    float* d = (float*)FUN_00e5eb20((float*)scratch, (int)self);
    FUN_00e577a0((int)(self + 0x4c), d);

    FUN_00e78b20((float*)(gCellUI + 0x48), *(int*)(gCellGame + 0x40fc), gK_1486110,
                 *(int*)(gCellGame + 0x411c));
    FUN_00e78b20((float*)(gCellUI + 0x48), *(int*)(gCellGame + 0x40fc), gK_14007f4,
                 *(int*)(gCellGame + 0x411c));

    char posA[0xc], posB[0xc];
    int e1 = FUN_00e4cce0(1);
    char* cellA = (char*)FUN_00e74a20(*(int*)(gCellGame + 0x40fc), posA, 0, e1);
    int e2 = FUN_00e4cce0(2);
    char* cellB = (char*)FUN_00e74a20(*(int*)(gCellGame + 0x40fc), posB, 0, e2);

    *(char*)(gCellGame + 0x518c) = 1;

    char* p1 = (char*)((cObjectPool*)(gCellGame + 0x1c))->Get((int)cellA);
    *(char*)(p1 + 0x354) = 1;

    char* p2 = (char*)((cObjectPool*)(gCellGame + 0x1c))->Get((int)cellB);
    *(float*)(p2 + 0x230) = gK_13ec5b4;
    *(char*)(p2 + 0x354)  = 1;
    *(int*)(p2 + 0x22c)   = (int)cellA;
    *(int*)(gCellUI + 0xe0)   = (int)cellA;
    *(float*)(gCellUI + 0xf4) = gK_1473c70;

    int slot = ((cObjectPool*)(gCellGame + 0x54))->Alloc();
    cCellCmd* cmd = (cCellCmd*)((cObjectPool*)(gCellGame + 0x54))->Get(slot);
    cmd->t1c = gK_14007f4;
    cmd->t20 = gK_14007f4;
    cmd->kind24 = 0x24;
    cmd->src28 = (int)cellA;
    cmd->arg2c = (int)cellB;
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
    *(int*)(gCellGame + 0x5198) = slot;
    GetTriggerMgr()->PostTrigger("goldies_demise", 0, 0, 0, 0, 0);
}

// ---------------------------------------------------------------- 0x00e79a00
// sDropLoot callback for the "eat" command: resolve the source cell, compute a drop point one
// half-radius along its facing from the cell centre and emit the digestion loot.
// @ 0x00e79a00
int FUN_00e79a00(int cmd, float dt)
{
    char* c = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(cmd + 0x28));
    if (c == 0) return 0;

    int flag = *(int*)(cmd + 0x70);
    float r  = *(float*)(c + 0x58) * gK_1471064;

    float scratch[0x6];
    float* d = (float*)FUN_00e5eb20(scratch, (int)c);

    int lvl = *(int*)(c + 0x358);
    float p[3];
    p[0] = *(float*)(c + 0x4c) + d[0] * r;
    p[1] = *(float*)(c + 0x50) + d[1] * r;
    p[2] = *(float*)(c + 0x54) + d[2] * r;

    if (lvl == -1) lvl = FUN_00e4ee60();

    FUN_00e771d0(*(int*)(c + 0x108), (int)(c + 0xfc), *(int*)(c + 0x35c), p,
                 gK_13ec480, lvl, flag, dt, 0, 0);
    return 1;
}

// ---------------------------------------------------------------- 0x00e79af0
// Build a 0x32 "digestion" command for one cell: pick the digestion duration (0x2a) via
// 0x00e6d200, populate the command record and register the 0x00e79a00 loot callback.
// @ 0x00e79af0
void FUN_00e79af0(int* cell, int flag, float f40, float f44)
{
    if (*(char*)((char*)cell + 0x112) != 0) return;
    if (*(char*)((char*)cell + 0x113) != 0) return;
    if (*(char*)((char*)cell + 0x180) != 0) return;

    int h0 = *cell;
    cObjectPool* cells = (cObjectPool*)(gCellGame + 0x1c);
    char* p = (char*)cells->Get(h0);
    float t = FUN_00e6d200((int)p, 0, 0x2a, *(int*)(p + 0x1b0));
    int h = *cell;

    int slot = ((cObjectPool*)(gCellGame + 0x54))->Alloc();
    cObjectPool* cp = (cObjectPool*)(gCellGame + 0x54);
    cCellCmd* cmd = (cCellCmd*)cp->Get(slot);
    cmd->t1c = t; cmd->t20 = t;
    cmd->kind24 = 0x32;
    cmd->src28 = h;
    cmd->arg2c = 0;
    cmd->arg30 = -1;
    cmd->arg34 = -1;
    cmd->arg38 = 0; cmd->arg3c = 0;
    cmd->f40 = f40; cmd->f44 = f44;
    cmd->from48 = gFwd_16b3c28; cmd->from4c = gFwd_16b3c2c; cmd->from50 = gFwd_16b3c30;
    cmd->to54   = gFwd_16b3c28; cmd->to58   = gFwd_16b3c2c; cmd->to5c   = gFwd_16b3c30;
    cmd->dir60 = gBasis_15a7c4c; cmd->dir64 = gBasis_15a7c50;
    cmd->dir68 = gBasis_15a7c54; cmd->dir6c = gBasis_15a7c58;
    cmd->flag70 = flag; cmd->flag74 = 0; cmd->flag78 = 0;
    cmd->x04 = 0; cmd->x08 = 0;

    cObjectPool* cp2 = (cObjectPool*)(gCellGame + 0x54);
    cCellCmd* cmd2 = (cCellCmd*)cp2->Get(slot);
    cmd2->x04 = (int)FUN_00e79a00;
}

// ---------------------------------------------------------------- 0x00e79c30
// Per-cell eat/digest step: pick the active record by controller mode, optionally snap the
// cell against the avatar (0x51dc), otherwise walk the timer cascade and run the matching
// step/announce helper, finishing with the assist command (0x00e6ff60).
// @ 0x00e79c30
void FUN_00e79c30(int cell, int other, float dt)
{
    int* pi;
    int mode = *(int*)(*(int*)(gCellGame + 0x5190) + 0x7c);
    if (mode == 0) {
        pi = (int*)(other + 0x248);
    } else if (mode == 2) {
        pi = (int*)(other + 0x194);
    } else {
        pi = (int*)(other + 0xe0);
    }
    if (pi != (int*)(other + 0xe0) && *pi == -1) pi = (int*)(other + 0xe0);

    float l10 = *(float*)(pi + 7); if (l10 == 0.0f) l10 = *(float*)(pi + 6);
    float lc  = *(float*)(pi + 8); if (lc  == 0.0f) lc  = *(float*)(pi + 6);
    float l8  = *(float*)(pi + 9); if (l8  == 0.0f) l8  = *(float*)(pi + 6);

    if (*(char*)(gCellGame + 0x51dc) != 0) {
        char* av = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(gCellGame + 0x411c));
        if (av != 0) {
            float dz = *(float*)(av + 0x54) - *(float*)(cell + 0x54);
            float dy = *(float*)(av + 0x50) - *(float*)(cell + 0x50);
            float dx = *(float*)(av + 0x4c) - *(float*)(cell + 0x4c);
            float inv = 1.0f / (float)sqrt((double)(dx * dx + dy * dy + dz * dz)
                                           + (double)gK_13ec4b8);
            float p[3];
            p[0] = *(float*)(cell + 0x4c) - (dx * inv) * gK_1473c70;
            p[1] = *(float*)(cell + 0x50) - (dy * inv) * gK_1473c70;
            p[2] = *(float*)(cell + 0x54) - (dz * inv) * gK_1473c70;

            void* s  = FUN_00e52910(other);
            int   r  = FUN_00e67c40(cell, other);
            void* s2 = FUN_00e52910(r);
            FUN_00e6f660(cell, p, dt, lc, *(int*)((char*)s2 + 0x40));
            (void)s;
            return;
        }
    }

    if (*(float*)(cell + 0x224) > 0.0f) {
        *(float*)(cell + 0x224) -= dt;
        return;
    }

    if (*(float*)(cell + 0x228) > 0.0f) {
        float x = *(float*)(cell + 0x228) - dt;
        *(char*)(cell + 0x178)  = 1;
        *(float*)(cell + 0x228) = x;
        if (x > 0.0f) return;
        void* s = FUN_00e52910(other);
        FUN_00e791f0(cell, *(int*)((char*)s + 0x78), dt);
        return;
    }

    if (*(float*)(cell + 0x21c) > 0.0f) {
        float x = *(float*)(cell + 0x21c) - dt;
        *(float*)(cell + 0x21c) = x;
        void* s = FUN_00e52910(other);
        int r   = FUN_00e67c40(cell, other);
        void* s2 = FUN_00e52910(r);
        (void)s;
        FUN_00e6f940(cell, *(int*)(cell + 0x220), l8, *(int*)((char*)s2 + 0x40));
        if (*(float*)(cell + 0x21c) > 0.0f) return;
        void* s3 = FUN_00e52910(other);
        *(float*)(cell + 0x224) = *(float*)((char*)s3 + 0x80);
        *(float*)(cell + 0x238) = 0.0f;
        return;
    }

    if (*(float*)(cell + 0x230) > 0.0f) {
        char* hold = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(cell + 0x22c));
        int ok = hold && FUN_00e57ce0(cell, (int)hold);
        void* s = FUN_00e52910(other);
        int r   = FUN_00e67c40(cell, other);
        void* s2 = FUN_00e52910(r);
        (void)s;
        FUN_00e6f800(cell, *(int*)(cell + 0x22c), dt, l10, *(int*)((char*)s2 + 0x40));
        if (*(int*)(cell + 0x22c) == *(int*)(gCellGame + 0x411c))
            *(char*)(gCellGame + 0x4120) = 1;
        float x = *(float*)(cell + 0x230) - dt;
        *(float*)(cell + 0x230) = x;
        if (x > 0.0f) return;
        void* s3 = FUN_00e52910(other);
        *(float*)(cell + 0x224) = *(float*)((char*)s3 + 0x88);
        *(float*)(cell + 0x238) = 0.0f;
        (void)ok;
        return;
    }

    void* s = FUN_00e52910(other);
    if (*(float*)((char*)s + 0x48) > 0.0f) {
        float x = *(float*)(cell + 0x234) - dt;
        *(float*)(cell + 0x234) = x;
        if (x > 0.0f) {
            void* a = FUN_00e52910(other);
            float f48 = *(float*)((char*)a + 0x4c);
            void* b = FUN_00e52910(other);
            int   h50 = *(int*)((char*)b + 0x50);
            FUN_00e79af0((int*)cell, h50, f48, 0.0f);
        }
    }

    void* s4 = FUN_00e52910(other);
    *(int*)(cell + 0x220) = 0;
    *(int*)(cell + 0x22c) = 0;
    int r  = FUN_00e67c40(cell, other);
    void* s5 = FUN_00e52910(r);
    FUN_00e6ff60(cell, lc, *(int*)((char*)s5 + 0x40));
    (void)s4;
}

// ---------------------------------------------------------------- 0x00e7a0a0
// Advance one cell's digestion: run the slow timer update then the step machine.
// @ 0x00e7a0a0
void FUN_00e7a0a0(int a, int b, float c)
{
    FUN_00e70e30(a, b, c);
    FUN_00e79c30(a, b, c);
}

// ---------------------------------------------------------------- 0x00e7a0d0
// cCellMode digestion tick: accumulate `dt` into the 0x148 timer and, when the cell is gone
// or the timer exceeds 4 seconds, hand the delta to 0x00e780a0.
// @ 0x00e7a0d0
void FUN_00e7a0d0(int* self, float dt)
{
    *(float*)((char*)self + 0x148) += dt;
    char* c = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)((char*)self + 0x14c));
    if (c == 0 || *(char*)(c + 0x113) != 0 || *(char*)(c + 0x112) != 0) {
        FUN_00e780a0(self[0], 0, dt, 0);
    } else if (*(float*)((char*)self + 0x148) > gK_14853e0) {
        FUN_00e780a0(self[0], 0, dt, 0);
    }
}

// ---------------------------------------------------------------- 0x00e7a160
// Cancel one cell's digestion by feeding a zero delta to 0x00e780a0.
// @ 0x00e7a160
void FUN_00e7a160(int handle)
{
    cObjectPool* pool = (cObjectPool*)(gCellGame + 0x1c);
    if (pool->GetSafe(handle) != 0)
        FUN_00e780a0(handle, 0, 0.0f, 0);
}
