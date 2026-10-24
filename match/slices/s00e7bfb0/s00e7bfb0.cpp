// Slice s00e7bfb0 -- SPGonzago/SPCellGame.obj: cell-stage update helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU; no /EHsc).
//
// Layouts come from the dev-build PDB (SP::cSPCell 0x388) with retail offsets confirmed against the
// disassembly where they differ. cSPCell is the 0x388-byte pool element in cCellGame::mCells
// (cCellGame+0x1c); the 0x4c-stride "marker" records handled by sMarkerActivate belong to a spawn
// list and are modelled by cMarker.
#include "types.h"
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t  uint8;
typedef int32_t  int32;

extern "C" double __cdecl exp(double);

#define FMAX 3.402823466e+38F

struct Vec3 { float x, y, z; };

// ------------------------------------------------------------------ globals
extern char* gspCellGame;     // 0x016b3c04
extern char* gspCellGfx;      // 0x016b3c08
extern char* gspCellUI;       // 0x016b3c0c
extern char* g_16b3c10;       // 0x016b3c10
extern float g_13ec5b4;       // 0x013ec5b4  1000.0f
extern float g_14908cc;       // 0x014908cc
extern float g_13f9428;       // 0x013f9428
extern float g_14856bc;       // 0x014856bc
extern float g_14851ec;       // 0x014851ec  1.5258789e-05f (2^-16)
extern float g_1485378;       // 0x01485378  0.0f
extern float g_1485720;       // 0x01485720  1.0f
extern float g_13f6a20;       // 0x013f6a20  0.85f
extern float g_147d1a0;       // 0x0147d1a0  2.25f
extern uint32 g_levelSize[];  // 0x01483bd0
extern int   g_scaleTable[];  // 0x01483c14 (stride 0x1c cell-scale records)
extern int   g_scale1000[];   // 0x01483e60 (level-1000 record)

struct RandomLinearCongruential {                 // 0x009360d0 thiscall
    double RandomDoubleUniform();
};
extern RandomLinearCongruential sMathRandom;      // 0x01601760

// ------------------------------------------------------------------ pools / game objects
struct cObjectPool {                              // cSPObjectPoolT<T,N>
    int   Begin();                                // 0x00e31100
    void* Next(int* pIterator);                   // 0x00b72230
    void* GetSafe(int handle);                    // 0x00b721d0
    void* Get(int handle);                        // 0x00b72210
    void  Free(int handle);                       // 0x00b72260
    void  Clear();                                // 0x00b72110
};

struct cSPCell {                                  // retail offsets
    uint32 id;                                    // +0x000
    uint8  pad004[0x0c - 0x04];
    float  f0c;                                   // +0x00c
    float  f10;                                   // +0x010
    uint8  pad014[0x18 - 0x14];
    int    f18;                                   // +0x018
    int    f1c;                                   // +0x01c
    uint8  pad020[0x24 - 0x20];
    int    f24;                                   // +0x024
    int    type;                                  // +0x028
    float  f2c;                                   // +0x02c
    float  f30;                                   // +0x030
    float  f34;                                   // +0x034
    float  f38;                                   // +0x038
    int    group;                                 // +0x03c
    int    f40;                                   // +0x040
    uint8  f44;                                   // +0x044
    uint8  pad045[0x48 - 0x45];
    uint16 flags48;                               // +0x048
    uint16 count4a;                               // +0x04a
    Vec3   pos;                                   // +0x04c
    float  f58;                                   // +0x058
    uint8  pad05c[0x84 - 0x5c];
    Vec3   prevPos;                               // +0x084
    Vec3   velocity;                              // +0x090
    float  f9c;
    float  fA0;                                   // +0x0a0
    float  fA4;                                   // +0x0a4
    float  fA8;                                   // +0x0a8
    float  fAC;                                   // +0x0ac
    float  fB0;                                   // +0x0b0
    float  fB4;                                   // +0x0b4
    uint8  pad0b8[0xfc - 0xb8];
    int    fFC;                                   // +0x0fc
    uint8  pad100[0x108 - 0x100];
    int    f108;                                  // +0x108
    uint8  pad10c[0x1c4 - 0x10c];
    Vec3   f1c4;                                  // +0x1c4
    uint8  pad1d0[0x248 - 0x1d0];
    int    f248;                                  // +0x248
    uint8  pad24c[0x250 - 0x24c];
    int    f250;                                  // +0x250
    int    indices[64];                           // +0x254
    uint8  f354;                                  // +0x354
    uint8  pad355[0x358 - 0x355];
    int    f358;                                  // +0x358
    int    f35c;                                  // +0x35c
    int    f360;                                  // +0x360
    uint8  pad364[0x36c - 0x364];
    int    f36c;                                  // +0x36c
    int    f370;                                  // +0x370
};

struct cMarker {                                  // 0x4c-stride spawn marker record
    uint8 pad00[0x0c];
    float f0c;                                    // +0x0c
    float f10;                                    // +0x10
    uint8 pad14[0x18 - 0x14];
    int   f18;                                    // +0x18
    int   f1c;                                    // +0x1c
    uint8 pad20[0x24 - 0x20];
    int   f24;                                    // +0x24
    int   type;                                   // +0x28
    float f2c;                                    // +0x2c
    float f30;                                    // +0x30
    float f34;                                    // +0x34
    float f38;                                    // +0x38
    int   group;                                  // +0x3c
    int   f40;                                    // +0x40
    uint8 f44;                                    // +0x44
    uint8 pad45[3];
    float f48;                                    // +0x48
};

struct cGridBlock {                               // pool element at cCellGame+0x38 (mGridSquares)
    int   pad0;
    int   a4;                                     // +0x04
    int   lvl;                                    // +0x08
    int   x;                                      // +0x0c
    int   y;                                      // +0x10
    uint8 b14;                                    // +0x14
};

// ------------------------------------------------------------------ callees
void  FUN_01042570(float* out, void* p, float a, float b, float c, float d);   // 0x01042570
void  FUN_01042500(void* p, float a, float b, float c);                        // 0x01042500
void  FUN_00e780a0(int id, int a, float b, int c);                             // 0x00e780a0
void  FUN_00e553a0(int n, void* array, void* out);                             // 0x00e553a0
void  FluidParticlesSampleVelocity(void* out, void* world, void* pos);         // 0x00e4e3c0
void  FUN_00e6d790(void* out);                                                 // 0x00e6d790
void  FUN_00e87040(int a, int b, void* c, float d);                            // 0x00e87040
bool  sCellIsOutOfRange(cSPCell* p);                                           // 0x00e5f8c0
float FUN_00e5a9c0(cMarker* m, ...);                                           // 0x00e5a9c0
float FUN_00e5a910(float a, float b, float c, float d, int e, int f, int g,
                   void* h, int i, int j);                                     // 0x00e5a910
float sGetBoxSizeMultiplier2(int a, int b);                                    // 0x00e51ff0
int   __fastcall SP_sGetSourceLevel(int unusedEcx, int level);                 // 0x00e4ee60 (level in edx)
void  sRandomExtents(void* out, int a, int b);                                 // 0x00e5fb50
void  sMarkerActivate(cMarker* m, int a, int b, int c, int d, int e);          // 0x00e7c3f0
void  sGenPlants(int a, int b, int c, float d, float e, float f);              // 0x00e78830
void  sGenCluster(int a, int b, float c, float d, int e, float f);             // 0x00e75350
void  sGenDistribute(int a, int b, float c, float d, float e);                 // 0x00e75900
void  FUN_00e5aa20(void* out, int a, void* b);                                 // 0x00e5aa20
void* FUN_00e4cc40(int a, void* out);                                          // 0x00e4cc40 -> 0x00e823a0
// 0x18-byte scratch object the spawn/scatter helpers build in their frame. The retail helpers take
// it in ecx (__thiscall): 0x00743b50 zeroes its first dword, 0x00e82130 releases whatever
// refcounted object is stored there. Declaring them as free functions left ecx holding whatever the
// caller had in it, so the store/release hit a random address.
struct TempScratch {
    char raw[0x18];
    void Clear();     // 0x00743b50
    void Release();   // 0x00e82130
};
void  sCinematicGoldy_Start();                                                 // 0x00e79720
bool  FUN_00e7bfb0(cSPCell* p, float dt);                                      // 0x00e7bfb0
void  FUN_00e7a190();                                                          // 0x00e7a190
void  CellUpdateAnimation(cSPCell* p, void* def, float dt);                    // 0x00e6d340
void  sUpdateCellDeformation(cSPCell* p, void* def, float dt);                 // 0x00e5a430
int   FUN_00e57340(cSPCell* p);                                                // 0x00e57340
void  FUN_00e6dae0(cSPCell* p);                                                // 0x00e6dae0
void  FUN_00e6b370(cSPCell* p);                                                // 0x00e6b370
void  FUN_00e5ac10(cSPCell* p, float dt);                                      // 0x00e5ac10
void  FUN_00e5ae80(cSPCell* p, float dt);                                      // 0x00e5ae80
void  FUN_00e53660(int a, int b);                                              // 0x00e53660
void  FUN_00e50450(int a);                                                     // 0x00e50450
void  FUN_00e56a10();                                                          // 0x00e56a10
void* ConfigManager();                                                         // 0x0067dd30
void* FUN_00e4fca0();                                                          // 0x00e4fca0
void* FUN_00e56870();                                                          // 0x00e56870
void  FUN_00e7ba30(float a);                                                   // 0x00e7ba30
void* GetTriggerMgr();                                                         // 0x00b3d4d0
void  Sim_goStop(void* mgr);                                                   // 0x00ad7dc0
void* LayerCatalog_ApplyA(void* out);                                          // 0x00e4ce40
void  FUN_00e7c6c0(cGridBlock* p, int a);                                      // 0x00e7c6c0
bool  FUN_00e5cde0(cSPCell* p);                                                // 0x00e5cde0
bool  FUN_00e78c00(cSPCell* p, void* def);                                     // 0x00e78c00
uint32 FNV1_String8(const char* s, uint32 hash, int a, int b);                 // 0x00932e80

struct cListA { int pad0[2]; int count; void* base; };   // +8 count, +0xc base, stride 0x4c
struct cListB { int count; void* base; };                // +0 count, +4 base, stride 0xc

// ---------------------------------------------------------------- 0x00e7bfb0
// Refresh one cell's "desired scale" interpolator and advance its animation timer. Returns false (and
// resets through 0x00e780a0) when the scale collapses and the cell is not the avatar.
// @ 0x00e7bfb0
bool FUN_00e7bfb0(cSPCell* p, float dt)
{
    float t = dt * 1000.0f;   // g_13ec5b4
    float v = p->f58;
    FUN_01042570(&v, (char*)p + 0xa8, p->fB4, p->fAC, g_14908cc, t);
    if (g_14851ec > v && p->id != *(int*)(gspCellGame + 0x411c)) {
        FUN_00e780a0(p->id, 0, dt, 0);
        return false;
    }
    p->count4a = (uint16)(p->count4a + 1);
    p->f58 = v;
    FUN_01042500((char*)p + 0xa0, p->fA4, g_13f9428, t);
    return true;
}

// ---------------------------------------------------------------- 0x00e7c080
// Move a cell by its integrated velocity / fluid-advected drift, refresh its previous position, then
// push the collision proxy to the physics world and kill out-of-range non-avatar cells.
// @ 0x00e7c080
void SP_sUpdateCellPosition(cSPCell* p, char* def, float dt)
{
    float px = p->pos.x, py = p->pos.y, pz = p->pos.z;
    p->prevPos.x = px; p->prevPos.y = py; p->prevPos.z = pz;

    if (p->f248 != 0 && p->f250 > 1) {
        p->f1c4.z = 0.0f;
        float vx = p->f1c4.x * dt;
        float vy = p->f1c4.y * dt;
        float vz = p->f1c4.z * dt;
        char* table = *(char**)(gspCellGame + 0x4108);
        for (int i = 0; i < p->f250; i++) {
            float* dst = (float*)(table + 0x4654 + p->indices[i] * 12);
            dst[0] += vx; dst[1] += vy; dst[2] += vz;
        }
        FUN_00e553a0(p->f250, p->indices, &p->velocity);
        p->velocity.z = 0.0f;
        p->pos.z = 0.0f;
        p->flags48 |= 4;
        p->count4a++;
    } else if (def[0xb4] != 0) {
        p->velocity.z = 0.0f;
        p->f1c4.z = 0.0f;
        if (p->f248 != 0) {
            float local[3];
            FluidParticlesSampleVelocity(local, *(void**)(gspCellGame + 0x4108), &p->pos);
            float k = 1.0f - (float)exp(-(double)dt);
            p->pos.x = (local[0] - p->pos.x) * k + p->pos.x;
            p->pos.y = p->pos.y + (local[1] - p->pos.y) * k;
            p->pos.z = p->pos.z + -p->pos.z * k;
        }
        float nx = p->f1c4.x * dt + p->pos.x;
        float ny = p->f1c4.y * dt + p->pos.y;
        float nz = p->f1c4.z * dt + p->pos.z;
        p->pos.x = nx; p->pos.y = ny; p->pos.z = nz;
        p->pos.x = p->velocity.x * dt + px;
        p->pos.y = p->velocity.y * dt + py;
        p->pos.z = p->velocity.z * dt + pz;
        p->flags48 |= 4;
        p->count4a++;
    }

    {
        // The retail code keeps two overlapping frame blocks: a Vec3-style input at the low end of
        // the scratch (passed as the third argument) and, 0x10 bytes above it, the 4-float temp
        // that 0x00e6d790 fills -- whose first float is passed by value as the fourth argument.
        char local[0x30];
        FUN_00e6d790(local + 0x10);
        FUN_00e87040(p->f35c, p->f360, local, *(float*)(local + 0x10));
    }
    if (sCellIsOutOfRange(p) && p->f354 == 0) {
        if (p->id != *(int*)(gspCellGame + 0x51b0))
            FUN_00e780a0(p->id, 0, dt, 0);
    }
}

// ---------------------------------------------------------------- 0x00e7c3f0
// Activate one spawn marker: pick the player/enemy resource handle from the marker group and dispatch
// to the plant / cluster / distribute generators.
// @ 0x00e7c3f0
void sMarkerActivate(cMarker* m, int a, int b, int group, int d, int e)
{
    int handle = (group == 1) ? *(int*)(gspCellGame + 0x4100) : *(int*)(gspCellGame + 0x40fc);
    switch (m->type) {
    case 0:
        sGenDistribute(handle, a, m->f0c, m->f10,
                       FUN_00e5a9c0(m, d, group, m->f18, d, b, e));
        break;
    case 1:
        sGenCluster(handle, a, m->f0c, m->f10, m->f40,
                    FUN_00e5a9c0(m, d, group, m->f1c, m->f44, d, b, e));
        break;
    case 2:
        sGenPlants(m->f24, handle, a, m->f0c, m->f10,
                   FUN_00e5a9c0(m, d, group, d, b, e));
        break;
    }
}

// ---------------------------------------------------------------- 0x00e7c500
// Recursively scatter spawn markers at a position: while the remaining budget is positive, roll a
// random marker from the source list and activate it (or recurse for group-3 boxes).
// @ 0x00e7c500
void FUN_00e7c500(float f, int a2, int a3, int a4, void* a5, void* a6, void* a7)
{
    while (f > g_1485378) {
        double r = sMathRandom.RandomDoubleUniform();
        if (!(r > (double)f)) {
            char local18[0x18];
            ((TempScratch*)local18)->Clear();
            void* key = FUN_00e4cc40((int)a6, local18);
            cListA* list = (cListA*)key;
            float ext[6];
            FUN_00e5aa20(ext, (int)a5, key);
            for (int i = 0; list && i < list->count; i++) {
                cMarker* m = (cMarker*)((char*)list->base + i * 0x4c);
                int ty = m->type;
                if (ty < 0) continue;
                if (ty <= 2) {
                    if (m->group == a3)
                        sMarkerActivate(m, (int)a5, (int)ext, a2, a3, (int)a7);
                } else if (ty == 3 && m->group == a3) {
                    sRandomExtents(ext, (int)a5, m->f48);
                    for (int j = -4; j < 1; j++) {
                        float mul = sGetBoxSizeMultiplier2(a3, a2) * g_13f6a20;
                        float r2 = FUN_00e5a910(m->f2c, m->f30, m->f34, m->f38,
                                                a2, j + a3, a4, ext, m->f24, (int)a7);
                        FUN_00e7c500(mul * mul * g_147d1a0 * r2, a2, a3, a4, a5, a6, a7);
                    }
                }
            }
            ((TempScratch*)local18)->Release();
        }
        f -= g_1485720;
    }
}

// ---------------------------------------------------------------- 0x00e7c6c0
// Scatter one level block: build the block's world-space box, resolve its source level and iterate the
// source list, spawning each matching entry.
// @ 0x00e7c6c0
void FUN_00e7c6c0(cGridBlock* b, int a2)
{
    float lo0 = FMAX, lo1 = FMAX, lo2 = FMAX;
    float hi0 = -FMAX, hi1 = -FMAX, hi2 = -FMAX;
    float z = 0.0f;
    int lvl = b->lvl;
    float size = (float)g_levelSize[lvl];
    float x0 = (float)b->x * size + (float)lvl * 0.0f;
    float y0 = (float)b->y * size + 0.0f;
    float x1 = (float)(b->x + 1) * size - 0.0f;
    float y1 = (float)(b->y + 1) * size - 0.0f;
    float s = g_1485720 / (*(float*)(gspCellGame + 0x514c) / (sGetBoxSizeMultiplier2(lvl, b->a4) * g_13f6a20));
    float bx0 = x0 * s, by0 = y0 * s, bz0 = z * s;
    float bx1 = x1 * s, by1 = y1 * s, bz1 = z * s;
    int handle, u8;
    if (b->a4 == 1) {
        handle = *(int*)(gspCellGame + 0x4100);
        u8 = *(int*)(gspCellGame + 0x4118);
    } else {
        handle = *(int*)(gspCellGame + 0x40fc);
        u8 = *(int*)(gspCellGame + 0x4114);
    }
    // The retail code does not read the level id directly: it maps it through the source-level
    // lookup (level id in edx, ecx ignored) -- 0x00e4ee60.
    int srcLevel = SP_sGetSourceLevel(0, *(int*)(*(char**)(gspCellGame + 0x5190) + 0x1c));
    char local[0x18];
    ((TempScratch*)local)->Clear();
    cListB* list = (cListB*)FUN_00e4cc40(u8, local);
    if (list) {
        for (int i = 0; i < list->count; i++) {
            char* e = (char*)list->base + i * 0xc;
            if (b->b14 == *(uint8*)(e + 4)) {
                int v = *(int*)(e + 8);
                if (v == -1 || v == srcLevel)
                    FUN_00e7c500(1.0f, b->a4, lvl, handle, &bx0, *(void**)e, (void*)a2);
            }
        }
    }
    ((TempScratch*)local)->Release();
    (void)lo0; (void)lo1; (void)lo2; (void)bx1; (void)by1; (void)bz1;
    (void)by0; (void)bz0; (void)hi0; (void)hi1; (void)hi2;
}

// ---------------------------------------------------------------- 0x00e7c8c0
// @ 0x00e7c8c0
void SP_sUpdateCells(float dt)
{
    cObjectPool* pool = (cObjectPool*)(gspCellGame + 0x1c);
    int it = pool->Begin();
    cSPCell* p;
    while ((p = (cSPCell*)pool->Next(&it)) != 0) {
        uint32 id = p->id;
        char local[0x18];
        ((TempScratch*)local)->Clear();
        void* def = FUN_00e4cc40(p->f108, local);
        bool ok = FUN_00e78c00(p, def);
        if (ok) {
            if (p->f35c == *(int*)(gspCellGame + 0x4100)) {
                Vec3 np;
                np.x = p->velocity.x * dt + p->pos.x;
                np.y = p->velocity.y * dt + p->pos.y;
                p->flags48 |= 4;
                p->count4a++;
                p->pos.x = np.x;
                np.z = p->velocity.z * dt + p->pos.z;
                p->pos.y = np.y;
                p->pos.z = np.z;
                {
                    int scale = *(int*)(*(char**)(gspCellGame + 0x5190) + 0x1c);
                    int threshold;
                    if (scale == 1000) threshold = g_scale1000[0];
                    else {
                        int idx = 0;
                        while (scale >= g_scaleTable[idx * 7 + 14]) idx++;
                        threshold = g_scaleTable[idx * 7];
                    }
                    if (p->f358 < threshold) {
                        p->fB4 = 0.0f;
                        p->fAC = g_14856bc;
                    }
                }
                FUN_00e7bfb0(p, dt);
                CellUpdateAnimation(p, def, dt);
            } else {
                FUN_00e7a190();
                if (p->id == id) {
                    CellUpdateAnimation(p, def, dt);
                    sUpdateCellDeformation(p, def, dt);
                    if (*(int*)((char*)def + 0xb8) != 0 && (*(uint8*)((char*)def + 0xb0) & 2) != 0) {
                        if (FUN_00e57340(p) < 2) p->fB4 = 0.0f;
                    }
                    if (p->id != *(int*)(gspCellGame + 0x411c) &&
                        p->fFC == *(int*)(*(char**)(gspCellGame + 0x5190) + 0x10)) {
                        if (FUN_00e57340(p) < 2) p->fB4 = 0.0f;
                    }
                    if (FUN_00e7bfb0(p, dt)) {
                        SP_sUpdateCellPosition(p, (char*)def, dt);
                        if (p->fFC != 0) {
                            FUN_00e6b370(p);
                            FUN_00e5ac10(p, dt);
                        }
                        if (p->id == id) {
                            FUN_00e6dae0(p);
                            FUN_00e5ae80(p, dt);
                            p->f1c4.x = *(float*)0x016b3c28;
                            p->f1c4.y = *(float*)0x016b3c2c;
                            p->f1c4.z = *(float*)0x016b3c30;
                        }
                    }
                }
            }
        }
        ((TempScratch*)local)->Release();
        p = (cSPCell*)pool->Next(&it);
    }
}

// ---------------------------------------------------------------- 0x00e7cb90
// @ 0x00e7cb90
void FUN_00e7cb90()
{
    char* p = *(char**)(gspCellGame + 0x5190);
    if (p[0x69] == 0)
        sCinematicGoldy_Start();
}

// ---------------------------------------------------------------- 0x00e7cbb0
// @ 0x00e7cbb0
void FUN_00e7cbb0(char a1, char a2, int* obj)
{
    GetTriggerMgr();
    Sim_goStop(0);
    if (a1) {
        (*(void(__thiscall**)(int*, int))(*(int*)obj + 0xc))(obj, 1);
    }
    (*(void(__thiscall**)(int*))(*(int*)obj + 4))(obj);
    if (a2 != 1) {
        char local[0x18];
        ((TempScratch*)local)->Clear();
        int* lv = (int*)LayerCatalog_ApplyA(local);
        int v = lv[0xdc / 4];
        ((TempScratch*)local)->Release();
        if (v != 1) {
            char local2[0x18];
            ((TempScratch*)local2)->Clear();
            int* lv2 = (int*)LayerCatalog_ApplyA(local2);
            int v2 = lv2[0xdc / 4];
            ((TempScratch*)local2)->Release();
            if (v2 != 2) {
                if (FUN_00e4fca0() != 0)
                    return;
                int h = (int)((cObjectPool*)(gspCellGame + 0x54))->GetSafe((int)g_16b3c10);
                if (!a1) return;
                if (h == 0) h = (int)FUN_00e56870();
                FUN_00e7ba30(*(float*)(h + 0x1c) - 4.0f);
                return;
            }
        }
        if (a1) {
            FUN_00e53660(2, 1);
            *(uint8*)(gspCellUI + 0x938) = 1;
            uint32 h1 = FNV1_String8("CAllout_CLG_Opening", 0x811c9dc5, 1, 0);
            FUN_00e50450((int)h1);
            uint32 h2 = FNV1_String8("CAllout_CLG_ProgressBar", 0x811c9dc5, 1, 0);
            FUN_00e50450((int)h2);
            return;
        }
        {
            void* cm = ConfigManager();
            if ((*(int(__thiscall**)(void*, int))(*(int*)cm + 0x30))(cm, 0x4ea96cb) != 0)
                FUN_00e56a10();
        }
    }
}

// ---------------------------------------------------------------- 0x00e7cd10
// @ 0x00e7cd10
void FUN_00e7cd10()
{
    cObjectPool* pool = (cObjectPool*)(gspCellGame + 0x1c);
    int it = pool->Begin();
    cSPCell* p;
    while ((p = (cSPCell*)pool->Next(&it)) != 0) {
        bool kill = false;
        if (FUN_00e5cde0(p) && p->f358 != -1) {
            cSPCell* q = (cSPCell*)pool->GetSafe(p->f36c);
            if (q) {
                cSPCell* prev;
                do {
                    prev = q;
                    q = (cSPCell*)pool->GetSafe(q->f36c);
                } while (q);
                if (prev == p)
                    kill = true;
            } else {
                kill = true;
            }
        }
        if (kill)
            FUN_00e780a0(p->id, 0, 0.0f, 0);
    }
    cObjectPool* grid = (cObjectPool*)(gspCellGame + 0x38);
    int it2 = grid->Begin();
    void* e;
    while ((e = grid->Next(&it2)) != 0)
        FUN_00e7c6c0((cGridBlock*)e, 0);
}
