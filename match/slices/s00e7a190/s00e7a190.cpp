// Slice s00e7a190 -- SPGonzago/SPCellGame.obj (batch spcg1).
// Cell-stage per-frame update: the master cell dispatch (record selection by controller mode,
// the 0x10xx behaviour switch), the death/break handlers that emit 5/6/0x0a commands, the drop
// path (SP::sDropLoot / FUN_00e52a40), the ladder/drop spawn loop and the transform placement
// of staged cells. Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU, no /EHsc).
//
// Offsets follow the retail disassembly. gCellGame is cCellGame (mCells object pool at +0x1c,
// command pool at +0x54, layer controller at +0x5190); camera forward is (0x16b3c28,c2c,c30)
// and the orthogonal basis lives at 0x15a7c4c..0x15a7c58.
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

extern char   gMatrix_16b3dac;    // 0x016b3dac  default Matrix33
extern float  gk_1485720;         // 0x01485720  1.0f
extern float  gk_1485378;         // 0x01485378  0.0f (epsilon compare)

// ---------------------------------------------------------------- object pools
struct cObjectPool {
    void* GetSafe(int id);   // 0x00b721d0
    void* Get(int id);       // 0x00b72210
    int   Alloc();           // 0x00b72160
    void* Next(int* it);     // 0x00b72230
    int   Front();           // 0x00e31100
};

// Scratch "layer catalog query" context (0x00743b50 ctor / 0x00e82130 dtor), thiscall.
struct cLayerCtx {
    void Begin();            // 0x00743b50
    void End();              // 0x00e82130
};

// Command record handed to the command pool (gCellGame+0x54). Raw-dword basis copies.
struct cCellCmd {
    char  pad00[4];
    int   x04;               // +0x04
    char  x08;               // +0x08
    char  pad09[0x13];
    float t1c;               // +0x1c
    float t20;               // +0x20
    int   kind24;            // +0x24
    int   src28;             // +0x28
    int   arg2c;             // +0x2c
    int   arg30;             // +0x30
    int   arg34;             // +0x34
    int   arg38;             // +0x38
    int   arg3c;             // +0x3c
    float f40;               // +0x40
    float f44;               // +0x44
    int   from48, from4c, from50;   // +0x48
    int   to54, to58, to5c;         // +0x54
    int   dir60, dir64, dir68, dir6c;// +0x60
    int   flag70;            // +0x70
    char  flag74;            // +0x74
    int   flag78;            // +0x78
};

namespace SP {
    void sUpdateAICaterpillar(int cell, float dt);   // 0x00e78fc0
    int  sGetSourceLevel(void);                      // 0x00e4ee60
    void sDropLoot(int a, int b, int c, float* p, float f, int lvl, int flag, float dt, int x, int y); // 0x00e771d0
}

// ---------------------------------------------------------------- callees
extern "C" char   FUN_00e52960(int cell);                                  // 0x00e52960 stage-active
extern "C" void   FUN_00e76a80(int self, int other, float dt);             // 0x00e76a80
extern "C" void*  FUN_00e52910(int handle);                                // 0x00e52910 resolve handle
extern "C" int    FUN_00e67c40(void* a, void* b);                          // 0x00e67c40
extern "C" void   FUN_00e6f800(int cell, int avatar, float dt, float f, int f40, int a, int b, int c); // 0x00e6f800
extern "C" void   FUN_00e71c00(int cell, int other, float dt);             // 0x00e71c00
extern "C" void   FUN_00e71ce0(int* cell, int other);                      // 0x00e71ce0
extern "C" void   FUN_00e6f5b0(int cell, float dt);                        // 0x00e6f5b0
extern "C" void   FUN_00e71300(float dt);                                  // 0x00e71300
extern "C" void   FUN_00e70650(int cell, float dt);                        // 0x00e70650 OrientToAvatar
extern "C" void   FUN_00e704b0(int cell, int other, float dt);             // 0x00e704b0
extern "C" void   FUN_00e702d0(int cell, int other, float dt);             // 0x00e702d0
extern "C" void   FUN_00e7a0a0(int cell, int other, float dt);             // 0x00e7a0a0
extern "C" void   FUN_00e6f990(int cell, float dt);                        // 0x00e6f990
extern "C" void   FUN_00e707d0(int cell, float dt);                        // 0x00e707d0
extern "C" void   FUN_00e6fbb0(int cell, float dt);                        // 0x00e6fbb0
extern "C" void   FUN_00e6fd70(int cell, float dt);                        // 0x00e6fd70
extern "C" void   FUN_00e6fce0(int cell, float dt);                        // 0x00e6fce0
extern "C" void   FUN_00e7a0d0(int cell, float dt);                        // 0x00e7a0d0
extern "C" int    FUN_00e57340(void* cell);                                // 0x00e57340 source
extern "C" int    FNV1_String8(const char* s, unsigned seed, int one);     // 0x00932e80
extern "C" void   FUN_00e66840(void* cell, int id);                        // 0x00e66840
extern "C" int    SPIDFromName(const char* name);                          // 0x00571cf0
extern "C" void   FUN_00e71f00(void* cell, int a);                         // 0x00e71f00
extern "C" void   FUN_00e514c0(void);                                      // 0x00e514c0 emit
extern "C" void*  FUN_00e4cc40(unsigned id, void* out);                    // 0x00e4cc40 layer-catalog entry
extern "C" int    FUN_00e4cce0(int a);                                     // 0x00e4cce0 LayerCatalog_GetEntry
extern "C" int    FUN_00e52a40(int a, int b, int c, float f, int d, int e); // 0x00e52a40
extern "C" float  FUN_00e6d200(void* cell, int a, int b, int c);           // 0x00e6d200
extern "C" void   FUN_00e59170(int a, float f);                            // 0x00e59170 reset
extern "C" void   FUN_00e72060(void* cell, int a, int b, float dt);        // 0x00e72060
extern "C" char   FUN_00e57460(void* a, void* b);                          // 0x00e57460 same group
extern "C" int    FUN_00e58980(void* a, void* b);                          // 0x00e58980 cell-pair
extern "C" void   FUN_00e62340(void* cell, int a);                         // 0x00e62340
extern "C" void   FUN_00e57910(int a);                                     // 0x00e57910
extern "C" void   FUN_00e576f0(int handle);                                // 0x00e576f0 apply
extern "C" void*  FUN_00e51ee0(int k, float f, int a, int b, int c, int d, int e,
                               int f2, int g, int h, int i, int j, int l, int m, int n, int o); // 0x00e51ee0
extern "C" void   FUN_00e59010(int a, int b, int c, int d, int e, int f);  // 0x00e59010
extern "C" void   FUN_00e59200(int handle);                                // 0x00e59200 remove
extern "C" void   FUN_00e780a0(int handle, int a, float f, int b);         // 0x00e780a0
extern "C" void   FUN_00e68000(int a, int b, void* c);                     // 0x00e68000
extern "C" void   FUN_0040ce80(void* t);                                   // 0x0040ce80
extern "C" void   FUN_00537dc0(void* dst, void* src);                      // 0x00537dc0 operator=
extern "C" void   FUN_0040ccb0(void* a, void* b);                          // 0x0040ccb0 ComposeTransforms
extern "C" void   FUN_004ff6d0(void* ctx, void* pt);                       // 0x004ff6d0 BackTransformPoint
extern "C" void   FUN_0041cb40(void* dst, void* src);                      // 0x0041cb40 Matrix3::Assign
extern "C" int    FUN_00e516c0(void* cell);                                // 0x00e516c0 source
extern "C" float  FUN_00e6d6d0(int a, int b, int c, int d, int e, int f);  // 0x00e6d6d0
extern "C" void   FUN_00e62b80(void* t, int a, int b, float f, int c, int d, int e, int g, int h); // 0x00e62b80
extern "C" int    FUN_00e31100(void);                                      // 0x00e31100 pool front
extern "C" void   FUN_00e72200(int handle);                                // 0x00e72200
extern "C" void   FUN_00e5c8e0(void);                                      // 0x00e5c8e0 spawn
extern "C" void   FUN_00e59260(int handle);                                // 0x00e59260 reset
extern "C" void   FUN_00e7add0(int handle, int a, float dt);               // 0x00e7add0
extern "C" int    FUN_00e7a4a0(int* cell, int p2, int p3, int p4, int p5, float p6); // 0x00e7a4a0
extern "C" void   FUN_00e7a770(int handle, int a, int b, int c, int d, float f);     // 0x00e7a770

// ---------------------------------------------------------------- 0x00e7a190
// Master per-cell dispatch: pick the active record by controller mode, run 0x00e76a80, then
// branch on the resolved entity id (0x51b0 / 0x51d4 / avatar) or the record "kind" switch.
// @ 0x00e7a190
void FUN_00e7a190(int* self, int* other, float dt)
{
    int  mode = *(int*)(*(int*)(gCellGame + 0x5190) + 0x7c);
    int* rec;
    if (mode == 0) {
        rec = (int*)((char*)other + 0x248);
    } else if (mode == 2) {
        rec = (int*)((char*)other + 0x194);
    } else {
        rec = (int*)((char*)other + 0xe0);
    }
    if ((mode == 0 || mode == 2) && *rec == -1) rec = (int*)((char*)other + 0xe0);

    if (*rec != 0 || *self == *(int*)(gCellGame + 0x411c)) {
        FUN_00e76a80((int)self, (int)other, dt);

        if (*(char*)((char*)self + 0x112) != 0 && self[99] != 8) {
            self[99] = 10;
            return;
        }
        if (*(char*)((char*)self + 0x16c) != 0) return;
        if (*(char*)(gCellGame + 0x51db) == 1 &&
            *(int*)(gCellGame + 0x411c) == *self) return;

        int id = *self;
        if (id == *(int*)(gCellGame + 0x51b0)) {
            char* s1 = (char*)FUN_00e52910((int)other);
            float f = *(float*)(s1 + 0x1c);
            if (f == 0.0f) f = *(float*)(s1 + 0x18);
            if (*(int*)(gCellGame + 0x51b4) == 3) {
                char* s2 = (char*)FUN_00e52910((int)other);
                unsigned char b = *(unsigned char*)(s2 + 0x44);
                int r  = FUN_00e67c40(self, other);
                char* s3 = (char*)FUN_00e52910((int)other);
                FUN_00e6f800((int)self, *(int*)(gCellGame + 0x411c), dt, f,
                             *(int*)(s3 + 0x40), r, 1, (int)b);
                return;
            }
        }
        if (id == *(int*)(gCellGame + 0x51d4)) {
            FUN_00e71c00((int)self, (int)other, dt);
            return;
        }
        if (id == *(int*)(gCellGame + 0x411c)) {
            FUN_00e6f5b0((int)self, dt);
            return;
        }

        void* ent = FUN_00e52910((int)other);
        switch (*(int*)ent) {
        case 0x1001: FUN_00e71300(dt); break;
        case 0x1003: FUN_00e70650((int)self, dt); return;
        case 0x1004: FUN_00e704b0((int)self, (int)other, dt); return;
        case 0x1005: FUN_00e702d0((int)self, (int)other, dt); return;
        case 0x1006: FUN_00e7a0a0((int)self, (int)other, dt); return;
        case 0x1007: FUN_00e6f990((int)self, dt); return;
        case 0x1008: SP::sUpdateAICaterpillar((int)self, dt); return;
        case 0x1009: FUN_00e707d0((int)self, dt); return;
        case 0x100b: FUN_00e6fbb0((int)self, dt); return;
        case 0x100c: FUN_00e6fd70((int)self, dt); return;
        case 0x100d: FUN_00e6fce0((int)self, dt); return;
        case 0x100e: FUN_00e7a0d0((int)self, dt); return;
        }
    }
}

// ---------------------------------------------------------------- 0x00e7a4a0
// Death handler: if this is the acting cell run the "gather" scene, else play the death one-shot
// (0x00e66840), announce (0x00e71f00), optional drop via FUN_00e52a40 + SP::sDropLoot, then emit
// the 0x06 command with the 0x00e6d200 durations and 0x00e59170 reset.
// @ 0x00e7a4a0
int FUN_00e7a4a0(int* cell, int p2, int p3, int p4, int p5, float p6)
{
    if (*(char*)((char*)cell + 0x112) != 0) return 0;
    if (*(char*)((char*)cell + 0x113) != 0) return 0;

    if (*(int*)(gCellGame + 0x411c) == *cell) {
        if (*(char*)(gCellGame + 0x5169) != 0) return 0;
        int v = *(int*)(gCellGame + 0x5158);
        if (v == 5 || v == 3) return 0;
        FUN_00e72060(cell, p2, p3, p6);
        return 1;
    }

    *(char*)((char*)cell + 0x113) = 1;
    int n = FUN_00e57340(cell);
    if (n < 2) {
        int h = FNV1_String8("cell_death_oneshot_small", 0x811c9dc5u, 1);
        FUN_00e66840(cell, h);
    } else {
        n = FUN_00e57340(cell);
        const char* s = (n < 3) ? "cell_death_oneshot" : "cell_death_oneshot_large";
        FUN_00e66840(cell, SPIDFromName(s));
    }
    FUN_00e71f00(cell, p2);

    if (p4 != 0) {
        FUN_00e514c0();
        (*(int*)(*(int*)(gCellGame + 0x5190) + 0x6c))++;
    }

    if (*(int*)((char*)cell + 0x358) != 0) {
        char raw[0x10];
        cLayerCtx* ctx = (cLayerCtx*)raw;
        ctx->Begin();
        void* e = FUN_00e4cc40(*(int*)((char*)cell + 0x108), raw);
        int lvl = SP::sGetSourceLevel();
        int v   = *(int*)((char*)cell + 0x358);
        if (v > lvl - 1 && v < lvl + 2) {
            int u = FUN_00e52a40(v, -1, *(int*)((char*)e + 0xd4), p6, 0, 0);
            SP::sDropLoot(*(int*)((char*)cell + 0x108), (int)((char*)cell + 0xfc),
                          *(int*)((char*)cell + 0x35c), (float*)((char*)cell + 0x4c),
                          *(float*)((char*)cell + 0x58), u, p5, p6, 0, 0);
        }
        ctx->End();
    }

    void* c1 = ((cObjectPool*)(gCellGame + 0x1c))->Get(*cell);
    FUN_00e6d200((char*)c1, 0, 10, *(int*)((char*)c1 + 0x1b0));
    void* c2 = ((cObjectPool*)(gCellGame + 0x1c))->Get(*cell);
    float t  = FUN_00e6d200((char*)c2, 0, 7, *(int*)((char*)c2 + 0x1b0));

    int slot = ((cObjectPool*)(gCellGame + 0x54))->Alloc();
    cCellCmd* cmd = (cCellCmd*)((cObjectPool*)(gCellGame + 0x54))->Get(slot);
    cmd->t1c = t; cmd->t20 = t;
    cmd->kind24 = 6;
    cmd->src28 = *cell;
    cmd->arg2c = 0;
    cmd->arg30 = -1; cmd->arg34 = -1;
    cmd->arg38 = 0;  cmd->arg3c = 0;
    cmd->f40 = 0.0f; cmd->f44 = 0.0f;
    cmd->from48 = *(int*)&gFwd_16b3c28; cmd->from4c = *(int*)&gFwd_16b3c2c;
    cmd->from50 = *(int*)&gFwd_16b3c30;
    cmd->to54   = *(int*)&gFwd_16b3c28; cmd->to58   = *(int*)&gFwd_16b3c2c;
    cmd->to5c   = *(int*)&gFwd_16b3c30;
    cmd->dir60  = *(int*)&gBasis_15a7c4c; cmd->dir64 = *(int*)&gBasis_15a7c50;
    cmd->dir68  = *(int*)&gBasis_15a7c54; cmd->dir6c = *(int*)&gBasis_15a7c58;
    cmd->flag70 = 0; cmd->flag74 = 0; cmd->flag78 = 0;
    cmd->x04 = 0; cmd->x08 = 0;

    FUN_00e59170(*cell, p6);
    return 1;
}

// ---------------------------------------------------------------- 0x00e7a770
// Guarded wrapper: only run the death handler when the cell exists and its 0x244 timer is idle.
// @ 0x00e7a770
void FUN_00e7a770(int handle, int a, int b, int c, int d, float f)
{
    cObjectPool* pool = (cObjectPool*)(gCellGame + 0x1c);
    char* cell = (char*)pool->GetSafe(handle);
    if (cell == 0) return;
    if (*(int*)(cell + 0x244) != 0) return;
    FUN_00e7a4a0((int*)cell, a, b, c, d, f);
}

// ---------------------------------------------------------------- 0x00e7a7c0
// Cell-vs-cell eat resolution: gate on stage-active + same group, run the pick (0x00e71ce0) and
// the pair test (0x00e58980), drain the 0x244 bites counter, then either run the death handler or
// the 0x00e51ee0 bite command + 0x00e59010 apply depending on the remaining timer.
// @ 0x00e7a7c0
char FUN_00e7a7c0(int* cell, int* other, int p3, int p4, int p5, float p6)
{
    if (FUN_00e52960((int)cell) == 0) return 0;
    if (!(FUN_00e57460(cell, other) == 0 && *(char*)((char*)cell + 0x17c) == 0 &&
          *(char*)((char*)cell + 0x111) == 0))
        return 0;

    FUN_00e71ce0(cell, *other);
    int bites = FUN_00e58980(other, cell);
    if (bites > 0) {
        if (*(int*)(gCellGame + 0x411c) == *cell ||
            *(int*)(gCellGame + 0x411c) == *other ||
            *(char*)((char*)other + 0x110) != 0) {
            FUN_00e62340(cell, *(int*)((char*)cell + 0x244));
        }
        int v = *(int*)((char*)cell + 0x244) - bites;
        *(int*)((char*)cell + 0x244) = v;
        if (v < 0) *(int*)((char*)cell + 0x244) = 0;
        FUN_00e57910((int)other);
        FUN_00e576f0(*other);
    }

    if ((float)*(int*)((char*)cell + 0x244) == 0.0f) {
        int flag;
        if (*(int*)(gCellGame + 0x411c) == *other ||
            *(char*)((char*)other + 0x110) != 0)
            flag = 1;
        else
            flag = (int)gCellGame & 0xffffff00;
        return FUN_00e7a4a0(cell, *other, *(int*)((char*)other + 0x108), flag, p4, p6);
    }

    char raw[0x10];
    cLayerCtx* ctx = (cLayerCtx*)raw;
    ctx->Begin();
    FUN_00e4cc40(*(int*)((char*)cell + 0x108), raw);

    int kind = 0x10;
    switch (p4) {
    case 1: kind = 0xe; break;
    case 3: kind = 0xf; break;
    case 5: kind = 0x11; break;
    }

    void* c1 = ((cObjectPool*)(gCellGame + 0x1c))->Get(*cell);
    float t  = FUN_00e6d200((char*)c1, 0, kind, *(int*)((char*)c1 + 0x1b0));

    int flag;
    if (*other == *(int*)(gCellGame + 0x411c) ||
        *(char*)((char*)other + 0x110) != 0)
        flag = 1;
    else
        flag = (int)gCellGame & 0xffffff00;

    if (t <= 0.0f) {
        FUN_00e7a770(*cell, *other, *(int*)((char*)other + 0x108), flag, p4, p6);
    } else {
        FUN_00e51ee0(2, t, *cell, *other, -1, -1, p4, *(int*)((char*)other + 0x108),
                     0, 0, p3, 0, 0, 0, flag, 0);
        FUN_00e59010(*cell, *other, p4, 1, 0, p3);
    }
    ctx->End();
    return 1;
}

// ---------------------------------------------------------------- 0x00e7aa20
// Stage one animated cell: resolve the two object handles, build the placement matrix from the
// camera forward, assign it to the cell transform, run 0x00e68000, then back-transform + scale
// every point of the 0x4108 array and finally place the animation group (0x00e62b80).
// @ 0x00e7aa20
void FUN_00e7aa20(int* p, float dt)
{
    char* iVar12 = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(p[1]);
    if (iVar12 == 0) {
        if (*(char*)((char*)p + 0x48) != 0) {
            FUN_00e780a0(p[3], 0, 0.0f, 0);
            return;
        }
        FUN_00e59200(*p);
        return;
    }
    char* iVar13 = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(p[3]);
    if (iVar13 == 0) {
        FUN_00e59200(*p);
        return;
    }

    float mat[6];
    memset(mat, 0, sizeof(mat));
    mat[0] = gFwd_16b3c28;
    mat[1] = gFwd_16b3c2c;
    mat[3] = gFwd_16b3c30;
    mat[5] = gk_1485720;
    (void)dt;

    char m33[0x1c];
    FUN_0041cb40(m33, &gMatrix_16b3dac);
    FUN_00e68000((int)iVar12, p[2], mat);

    char* xf = iVar13 + 0x48;
    FUN_0040ce80(xf);
    float saved58 = *(float*)(iVar13 + 0x58);
    FUN_00537dc0(xf, mat);
    FUN_0040ccb0(xf, (char*)p + 0x10);
    *(float*)(iVar13 + 0x58) = saved58;
    *(short*)(iVar13 + 0x4a) += 1;
    float saved4c = *(float*)(iVar13 + 0x4c);
    float saved50 = *(float*)(iVar13 + 0x50);
    *(short*)(xf) |= 4;
    *(short*)(iVar13 + 0x4a) += 1;
    *(float*)(iVar13 + 0x4c) = saved4c;
    *(float*)(iVar13 + 0x50) = saved50;
    *(float*)(iVar13 + 0x54) = 0.0f;

    if (*(int*)(iVar13 + 0x248) != 0 && *(int*)(iVar13 + 0x250) > 1) {
        char xf2[0x40];
        FUN_0040ce80(xf2);   // scratch transform copy source (kept logical)
        int* idx = (int*)(iVar13 + 0x254);
        for (int i = 0; i < *(int*)(iVar13 + 0x250); ++i, ++idx) {
            float* pt = (float*)(*(int*)(gCellGame + 0x4108) + 4 + *idx * 0xc);
            FUN_004ff6d0(xf, pt);
            float z = pt[2], y = pt[1], x = pt[0];
            if ((*(short*)(xf) & 2) != 0) {
                pt[0] = *(float*)(iVar13 + 0x5c) * x + *(float*)(iVar13 + 0x68) * y +
                        *(float*)(iVar13 + 0x74) * z;
                pt[1] = *(float*)(iVar13 + 0x60) * x + *(float*)(iVar13 + 0x6c) * y +
                        *(float*)(iVar13 + 0x78) * z;
                pt[2] = *(float*)(iVar13 + 0x64) * x + *(float*)(iVar13 + 0x70) * y +
                        *(float*)(iVar13 + 0x7c) * z;
            }
            float s = *(float*)(iVar13 + 0x58);
            pt[0] = pt[0] * s + *(float*)(iVar13 + 0x4c);
            pt[1] = pt[1] * s + *(float*)(iVar13 + 0x50);
            pt[2] = pt[2] * s + *(float*)(iVar13 + 0x54);
        }
    }

    int anim = *(int*)(iVar13 + 0x248);
    if (anim != 0) {
        int src = FUN_00e516c0(iVar13);
        void* ag = (void*)((cObjectPool*)(gCellGame + 0x1c))->Next((int*)&anim);

        float f = FUN_00e6d6d0((int)iVar13, (int)(iVar13 + 0xc0), *(int*)(iVar13 + 0x18c),
                               *(int*)(iVar13 + 0x24c), src, *(int*)(iVar13 + 0x35c));
        FUN_00e62b80(xf, *(int*)(iVar13 + 0xa0), *(int*)(iVar13 + 0x80), f,
                     (int)(iVar13 + 0xc0), *(int*)(iVar13 + 0x18c), *(int*)(iVar13 + 0x24c),
                     src, *(int*)(iVar13 + 0x35c));
        (void)ag;
    }
}

// ---------------------------------------------------------------- 0x00e7ad70
// Iterate the gCellGame+0x8c pool and stage each element.
// @ 0x00e7ad70
void FUN_00e7ad70(float dt)
{
    int it = ((cObjectPool*)(gCellGame + 0x8c))->Front();
    for (;;) {
        cObjectPool* pool = (cObjectPool*)(gCellGame + 0x8c);
        void* e = (void*)pool->Next(&it);
        if (e == 0) break;
        FUN_00e7aa20((int*)e, dt);
    }
}

// ---------------------------------------------------------------- 0x00e7add0
// Break handler: resolve the record, drop loot (clamped level 0..0x13 via layer 7) then either
// clear the gather (acting cell) or play the death one-shot.
// @ 0x00e7add0
void FUN_00e7add0(int handle, int p2, float dt)
{
    char* c = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(handle);
    if (c == 0) return;

    char raw[0x10];
    cLayerCtx* ctx = (cLayerCtx*)raw;
    ctx->Begin();
    FUN_00e4cc40(*(int*)(c + 0x108), raw);

    if (*(int*)(c + 0x358) != 0) {
        int lc[3];
        lc[1] = *(int*)(c + 0x358) - 1;
        lc[2] = 0x13;
        lc[0] = 0;
        int* pv = lc;
        if (lc[1] >= 0) pv = lc + 1;
        if (*pv > 0x13) pv = lc + 2;
        int entry = FUN_00e4cce0(7);
        SP::sDropLoot(*(int*)(c + 0x108), (int)(c + 0xfc), *(int*)(c + 0x35c),
                      (float*)(c + 0x4c), *(float*)(c + 0x58), *pv, entry, dt, 0, 0);
    }

    if (handle == *(int*)(gCellGame + 0x411c)) {
        FUN_00e72200(p2);
        ctx->End();
        return;
    }
    FUN_00e780a0(handle, 1, dt, 0);
    ctx->End();
}

// ---------------------------------------------------------------- 0x00e7aee0
// Break/death entry: skip for states 7/8/9, play the break one-shot, bump the gather/spawn
// counters for the acting cell, then emit the 0x05 command with the 0x00e6d200 duration.
// @ 0x00e7aee0
void FUN_00e7aee0(int* cell, int* other, float dt)
{
    int st = cell[99];
    if (st == 7 || st == 8 || st == 9) return;
    if (*(char*)((char*)cell + 0x17c) != 0) return;

    int h = FNV1_String8("cell_death_break", 0x811c9dc5u, 1);
    FUN_00e66840(cell, h);

    if (*(int*)((char*)cell + 0xfc) == 0) {
        FUN_00e7add0(*cell, 0, dt);
        return;
    }

    if (*other == *(int*)(gCellGame + 0x411c) && *(char*)((char*)cell + 0x112) == 0) {
        FUN_00e514c0();
        (*(int*)(*(int*)(gCellGame + 0x5190) + 0x6c))++;
    }
    if (*cell == *(int*)(gCellGame + 0x411c)) {
        FUN_00e5c8e0();
        (*(int*)(*(int*)(gCellGame + 0x5190) + 0x70))++;
    }

    void* c1 = ((cObjectPool*)(gCellGame + 0x1c))->Get(*cell);
    float t  = FUN_00e6d200((char*)c1, 0, 8, *(int*)((char*)c1 + 0x1b0));

    int slot = ((cObjectPool*)(gCellGame + 0x54))->Alloc();
    cCellCmd* cmd = (cCellCmd*)((cObjectPool*)(gCellGame + 0x54))->Get(slot);
    cmd->t1c = t; cmd->t20 = t;
    cmd->kind24 = 5;
    cmd->src28 = *cell;
    cmd->arg2c = 0;
    cmd->arg30 = -1; cmd->arg34 = -1;
    cmd->arg38 = 0;  cmd->arg3c = 0;
    cmd->f40 = 0.0f; cmd->f44 = 0.0f;
    cmd->from48 = *(int*)&gFwd_16b3c28; cmd->from4c = *(int*)&gFwd_16b3c2c;
    cmd->from50 = *(int*)&gFwd_16b3c30;
    cmd->to54   = *(int*)&gFwd_16b3c28; cmd->to58   = *(int*)&gFwd_16b3c2c;
    cmd->to5c   = *(int*)&gFwd_16b3c30;
    cmd->dir60  = *(int*)&gBasis_15a7c4c; cmd->dir64 = *(int*)&gBasis_15a7c50;
    cmd->dir68  = *(int*)&gBasis_15a7c54; cmd->dir6c = *(int*)&gBasis_15a7c58;
    cmd->flag70 = 0; cmd->flag74 = 0; cmd->flag78 = 0;
    cmd->x04 = 0; cmd->x08 = 0;

    FUN_00e59260(*cell);
}
