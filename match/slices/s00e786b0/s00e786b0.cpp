// Slice s00e786b0 -- SP Cell/plant UI + digestion message helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- shared types
struct Vec3 { float x, y, z; };                 // 12-byte position vector

struct SpawnBox {                               // plant spawn area handed to SP::sGenPlants
    float mMinX;                                // +0x00
    float mMinY;                                // +0x04
    float mPad08;                               // +0x08
    float mMaxX;                                // +0x0c
    float mMaxY;                                // +0x10
};

struct RandomGlobal {                           // 0x01601760  cRandomGlobal
    double RandomDouble();                      // 0x009360d0
};

struct CatalogScratch {                         // 4-byte scratch object built on the stack
    int   mHandle;                              // +0x00
    void* VecClear();                           // 0x00743b50  ?VecClear@cModelWorld@@QAEPAXXZ
    void  FUN_00e82130();                       // 0x00e82130  release
};

// ---------------------------------------------------------------- globals
extern char* g_cellGame;        // 0x016b3c04  _gspCellGame
extern char* g_16b3c0c;         // 0x016b3c0c
extern float g_1457e0c;         // 0x1457e0c  plant radius factor (1/15)
extern float g_1485378;         // 0x1485378  _HK_REAL_ZERO
extern float g_1485720;         // 0x1485720  _HK_REAL_ONE
extern float g_13ec480;         // 0x13ec480  attachment ring step (0.2)
extern float g_1488874;         // 0x1488874  attachment ring step (0.1)
extern float g_1483c20;         // 0x1483c20  eater scale (cube root of ten)
extern float g_1483bd0[8];      // 0x1483bd0  per-level plant radius
extern int   g_1483e60;         // 0x1483e60  plant-count threshold, level mode 1000
extern int   g_1483c34[];       // 0x1483c34  plant-count threshold records (stride 7 dwords)
extern int   g_1483c14[];       // 0x1483c14  plant-count values (stride 7 dwords)
extern const char g_15a7c4c[];  // 0x15a7c4c  cell-type name passed to CreateCell
extern Vec3  g_16b3c28;         // 0x016b3c28  default spawn position
extern RandomGlobal g_1601760;  // 0x01601760  cRandomGlobal

// ---------------------------------------------------------------- cell game types
struct CellModeStore {                              // *(CellGame + 0x5190)
    char  _pad000[0x01c];
    int   mLevelMode;                               // +0x01c  set to 1000 for the plant-heavy mode
    char  _pad020[0x07c - 0x020];
    int   mEatMode;                                // +0x07c  one of the three eater variants
};

struct CellGame {                                   // 0x016b3c04  _gspCellGame
    char  _pad000[0x01c];
    char  mCellStore[4];                            // +0x01c  the cell store
    char  _pad020[0x40fc - (0x01c + 4)];
    int   mAvatarCell;                              // +0x40fc  the player's cell id
    char  _pad4100[0x411c - 0x4100];
    int   mSelectedCell;                            // +0x411c
    char  _pad4120[0x514c - 0x4120];
    float mLevelSize;                               // +0x514c
    char  _pad5150[0x516c - 0x5150];
    int   mField516c;                               // +0x516c
    char  _pad5170[0x5190 - 0x5170];
    CellModeStore* mModeStore;                      // +0x5190
    char  _pad5194[0x51d4 - 0x5194];
    int   mSourceCell;                              // +0x51d4
};

struct CellObj {                                    // a cell instance
    int   mId;                                      // +0x000
    char  _pad004[0x048 - 0x004];
    int   mAttachAnchor;                            // +0x048  anchor handed to FUN_00e61370
    Vec3  mPos;                                     // +0x04c
    float mScale;                                   // +0x058
    char  _pad05c[0x080 - 0x05c];
    float mField80;                                 // +0x080
    char  _pad084[0x0fc - 0x084];
    int   mFieldFc;                                 // +0x0fc
    char  _pad100[0x108 - 0x100];
    int   mCatalogId;                               // +0x108  id passed to FUN_00e4cc40
    char  _pad10c[0x1f0 - 0x10c];
    float mTimer;                                   // +0x1f0
    char  _pad1f4[0x240 - 0x1f4];
    int   mCounter;                                 // +0x240  eat counter
    char  _pad244[0x248 - 0x244];
    int   mFlag248;                                 // +0x248
    char  _pad24c[0x358 - 0x24c];
    int   mField358;                                // +0x358
    int   mField35c;                                // +0x35c
};

struct EaterCandidate {                             // a candidate eater record at +0xe0/+0x194/+0x248
    int   mId;                                      // +0x000  -1 when the record is absent
    char  _pad004[0x06c - 0x004];
    int   mCounter6c;                               // +0x06c
    int   mLimit70;                                 // +0x070
    float mField74;                                 // +0x074
    int   mLootId78;                                // +0x078
};

struct EaterInfo {                                  // FUN_00e4cc40 / FUN_00e52910 result
    char  _pad000[0x004];
    float mRange;                                   // +0x004
    char  _pad008[0x060 - 0x008];
    int   mState60;                                 // +0x060
    char  _pad064[0x06c - 0x064];
    int   mCounter6c;                               // +0x06c
    int   mLimit70;                                 // +0x070
    float mField74;                                 // +0x074
    int   mLootId78;                                // +0x078
    char  _pad07c[0x09c - 0x07c];
    int   mKey9c;                                   // +0x09c
    float mTimerA0;                                 // +0x0a0
    char  _pad0a4[0x0e0 - 0x0a4];
    EaterCandidate mDefault;                        // +0x0e0  fallback candidate
    char  _padE0[0x194 - (0x0e0 + sizeof(EaterCandidate))];
    EaterCandidate mMid;                            // +0x194  candidate of eat mode 2
    char  _padMid[0x248 - (0x194 + sizeof(EaterCandidate))];
    EaterCandidate mAlt;                            // +0x248  candidate of eat mode 0
    char  _pad2c4[0x308 - (0x248 + sizeof(EaterCandidate))];
    float mSpawnRange;                              // +0x308
};

// ---------------------------------------------------------------- callees (0x00e78e70)
void __cdecl FUN_00e538b0(int);
void __cdecl SP_sOnButtonSaveClick(void);
void __cdecl FUN_00e53ad0(void);
void __cdecl FUN_00e53920(void);
void __cdecl SP_sOnQuitDesktopButtonClick(void);
void __cdecl FUN_00e501f0(void);
void __cdecl FUN_00e53a20(void);
bool __cdecl FUN_00e00ac0(void);
void __cdecl FUN_00e53660(int, int);
void __cdecl SP_ShowContextSensitiveSporeGuide(void);
void __cdecl FUN_00e539c0(void);
void __cdecl FUN_00e78e40(void);
void __cdecl FUN_00e760f0(void);
void __cdecl FUN_00e53860(int);
void __cdecl FUN_00e5daa0(void);

// ---------------------------------------------------------------- shared callees
int  __cdecl FUN_00e4cc40(int, void*);          // 0x00e4cc40  thunk_FUN_00e823a0: entry of a catalog id
int  __cdecl FUN_00e4cce0(int);                 // 0x00e4cce0  LayerCatalog_GetEntry
int  __cdecl FUN_00e52910(int);                 // 0x00e52910  eater record of a cell
int  __cdecl FUN_00e52a40(int, int);            // 0x00e52a40  look up by (cell, key)
bool __cdecl FUN_00e56f20(int);                 // 0x00e56f20  is the id in the current level range
void __cdecl FUN_00e57170(float);               // 0x00e57170  set (cell pointer in EAX)
void __cdecl FUN_00e57260(int, float, float);    // 0x00e57260  build a cell from a float payload
bool __cdecl FUN_00e5d410(int, Vec3*, float);   // 0x00e5d410  cell box overlap test
void __cdecl FUN_00e61370(void*, int, float);   // 0x00e61370  attachment offset from (anchor, angle)
void __cdecl FUN_00e61d90(int, int);            // 0x00e61d90  notify state (cell pointer in EAX)
void __cdecl FUN_00e780a0(int, int, float, int); // 0x00e780a0  emit/queue one cell
void __cdecl FUN_00e86f70(int);                 // 0x00e86f70  finish the plant group
int  __cdecl FUN_00b72210(int);                 // 0x00b72210  cell lookup by id
int  __cdecl FUN_00e87260(int, int, float, int*, int, int);  // 0x00e87260  collect + transform cells
int  __cdecl FUN_00e74a20(int, int, float, int, int, float, float, int, const char*, int); // 0x00e74a20 CreateCell
int  __cdecl FUN_00e76d70(int, int, void*, int, int, int);   // 0x00e76d70 SP::sCreateCellAttachment
int  __cdecl FUN_00e78230(int, Vec3*, float, int);           // 0x00e78230 plant factory, type 0
int  __cdecl FUN_00e783d0(int, Vec3*, float, int);           // 0x00e783d0 SP::sCreatePlant_Type1
int  __cdecl FUN_00e78570(int, Vec3*, float, int);           // 0x00e78570 SP::sCreatePlant_Type2

// ---------------------------------------------------------------- 0x00e786b0
// @ 0x00e786b0
int __cdecl SP_sCreatePlant_Type3(int param_1, int param_2, float param_3, int param_4)
{
    const int layerA = FUN_00e4cce0(0x10);
    const int layerB = FUN_00e4cce0(0x11);
    const int layerC = FUN_00e4cce0(0x12);

    const int levelMode = ((CellGame*)g_cellGame)->mModeStore->mLevelMode;
    int threshold;
    if (levelMode == 1000) {
        threshold = g_1483e60;
    } else {
        int i = 0;
        if (levelMode >= 0) {
            const int* p = g_1483c34;
            do {
                p += 7;
                ++i;
            } while (levelMode >= *p);
        }
        threshold = g_1483c14[i * 7];
    }

    const int cellId = FUN_00e74a20(param_1, param_2, 0.0f, layerA, param_4,
                                    1.0f, 0.0f, 1, g_15a7c4c, -1);
    const CellObj* cell = (const CellObj*)FUN_00b72210(cellId);
    if (threshold <= param_4) {
        int ring = 0;
        do {
            ++ring;
            float offset[3];
            FUN_00e61370(offset, (int)&cell->mAttachAnchor, (float)ring * g_13ec480);
            const int childId = FUN_00e76d70((int)cell, 1, offset, param_4 - 1, layerB, cellId);
            const CellObj* child = (const CellObj*)FUN_00b72210(childId);
            if (threshold < param_4) {
                int leaf = 3;
                do {
                    float leafOffset[3];
                    FUN_00e61370(leafOffset, (int)&child->mAttachAnchor, (float)leaf * g_1488874);
                    FUN_00e76d70((int)child, 1, leafOffset, param_4 - 2, layerC, cellId);
                    ++leaf;
                } while (leaf < 8);
            }
        } while (ring < 5);
    }
    return cellId;
}

// ---------------------------------------------------------------- 0x00e78830
// @ 0x00e78830
void __cdecl SP_sGenPlants(int param_1, int param_2, SpawnBox* param_3, float param_4, float param_5,
                           float param_6, int param_7, int, char param_9)
{
    CellGame* game = (CellGame*)g_cellGame;
    const float spanX = param_3->mMaxX - param_3->mMinX;
    const float spanY = param_3->mMaxY - param_3->mMinY;
    Vec3 pos = g_16b3c28;

    const int layerId = FUN_00e4cce0(10);
    CatalogScratch scratch;
    scratch.VecClear();
    const EaterInfo* entry = (const EaterInfo*)FUN_00e4cc40(layerId, &scratch);
    float range = entry->mSpawnRange;
    scratch.FUN_00e82130();
    range = (g_1483bd0[param_7] / game->mLevelSize) * range * g_1457e0c;

    float remaining = param_6;
    while (remaining > 0.0f) {
        if (g_1601760.RandomDouble() <= (double)remaining) {
            float maxScale = param_5;
            if (param_5 == 0.0f)
                maxScale = param_4;
            double scale = g_1601760.RandomDouble() * ((double)maxScale - (double)param_4)
                           + (double)param_4;
            if (scale > (double)maxScale)
                scale = (double)maxScale;
            if (scale < (double)param_4)
                scale = (double)param_4;
            const float finalScale = (float)scale;

            int cellIds[512];
            int tries = 0;
            int found = 1;
            while (found > 0) {
                if (tries >= 10)
                    goto next;
                ++tries;
                pos.x = (float)(g_1601760.RandomDouble() * (double)spanX
                                + (double)param_3->mMinX);
                pos.y = (float)(g_1601760.RandomDouble() * (double)spanY
                                + (double)param_3->mMinY);
                if (!FUN_00e5d410(param_2, &pos, range) || param_9 != 0) {
                    if (param_2 != game->mAvatarCell)
                        break;
                    found = FUN_00e87260(param_2, (int)&pos, range, cellIds, 0x200, 0);
                }
            }
            if (tries < 10) {
                switch (param_1) {
                case 0: FUN_00e78230(param_2, &pos, finalScale, param_7); break;
                case 1: FUN_00e783d0(param_2, &pos, finalScale, param_7); break;
                case 2: SP_sCreatePlant_Type3(param_2, (int)&pos, finalScale, param_7); break;
                case 3: FUN_00e78570(param_2, &pos, finalScale, param_7); break;
                }
                FUN_00e86f70(param_2);
            }
        }
    next:
        remaining -= 1.0f;
    }
}

// ---------------------------------------------------------------- 0x00e78b20
int  __cdecl FUN_00e87260(int, int, float, int*, int, int);   // 0x00e87260  collect + transform cells
void __cdecl FUN_00e780a0(int, int, float, int);              // 0x00e780a0  emit/queue one cell
int  __cdecl FUN_00b72210(int);                               // 0x00b72210  cell lookup by id

// @ 0x00e78b20
void __fastcall FUN_00e78b20(int param_1, int param_2, float param_3, int param_4)
{
    int local_800[512];
    const int n = FUN_00e87260(param_2, param_1, param_3, local_800, 0x200, 0);
    for (int i = 0; i < n; ++i)
        if (local_800[i] != param_4)
            FUN_00e780a0(local_800[i], 0, 0.0f, 0);
}

// ---------------------------------------------------------------- 0x00e78b80
// @ 0x00e78b80  (the exclusion id arrives in EDI, i.e. it is a caller register)
void __fastcall FUN_00e78b80(int param_1, int param_2, float param_3, int param_4)
{
    int local_800[512];
    const int n = FUN_00e87260(param_2, param_1, param_3, local_800, 0x200, 0);
    for (int i = 0; i < n; ++i) {
        int* p = (int*)FUN_00b72210(local_800[i]);
        if (*p != param_4 && p[0x3f] != 0)          // +0xfc
            FUN_00e780a0(*p, 0, 0.0f, 0);
    }
}

// ---------------------------------------------------------------- 0x00e78c00
bool __cdecl FUN_00e5cde0(void);      // 0x00e5cde0  cell visibility test (input in EAX)
bool __cdecl FUN_00e5d340(void);      // 0x00e5d340  extended-box test (input in EAX)
void __cdecl FUN_00e66010(int);       // 0x00e66010  select/add the cell to something
void __cdecl FUN_00e6d8f0(int, int);  // 0x00e6d8f0  activate/deactivate the cell

// @ 0x00e78c00
bool __cdecl FUN_00e78c00(int param_1, int param_2)
{
    const bool visible = FUN_00e5cde0();
    const int  cls = *(int*)(param_2 + 0xb4);
    if ((cls == 5 && visible) ||
        (cls == 6 &&
         *(int*)(*(int*)(g_cellGame + 0x5190) + 0x34 + *(int*)(param_2 + 0xb8) * 4) != 0)) {
        FUN_00e780a0(*(int*)param_1, 0, 0.0f, 0);
        return false;
    }
    if (visible) {
        if (*(int*)(param_1 + 0x248) != 0)
            FUN_00e66010(0);
    } else {
        if (cls == 6 && FUN_00e5d340()) {
            if (*(int*)(g_cellGame + 0x516c) != *(int*)param_1) {
                FUN_00e780a0(*(int*)param_1, 0, 0.0f, 0);
                return false;
            }
        }
        if (*(int*)(param_2 + 0xb4) == 6 && *(int*)(g_cellGame + 0x516c) != *(int*)param_1) {
            FUN_00e780a0(*(int*)(g_cellGame + 0x516c), 0, 0.0f, 0);
            *(int*)(g_cellGame + 0x516c) = *(int*)param_1;
        }
        if (*(int*)(param_1 + 0x248) == 0) {
            FUN_00e6d8f0(*(int*)param_1, 0);
            return true;
        }
    }
    return true;
}

// ---------------------------------------------------------------- 0x00e78d10
struct CellStub { int b721d0(int); };  // 0x00b721d0  CellGame::findCell (this = CellGame + 0x1c)

struct CellScratch {                  // 8-byte scratch built on the stack
    int   mField0;                    // +0x00
    float mField4;                    // +0x04
    void* VecClear();                 // 0x00743b50  ?VecClear@cModelWorld@@QAEPAXXZ
    void  FUN_00e82130();             // 0x00e82130  release
};
int  __cdecl FUN_00e4ce40(void*);     // 0x00e4ce40  LayerCatalog_ApplyA
void __cdecl FUN_00e75ea0(void);      // 0x00e75ea0  proximity action (args in registers)

// @ 0x00e78d10
void __cdecl FUN_00e78d10(void)
{
    int iVar1 = ((CellStub*)(g_cellGame + 0x1c))->b721d0(*(int*)(g_cellGame + 0x51d4));
    int iVar2 = ((CellStub*)(g_cellGame + 0x1c))->b721d0(*(int*)(g_cellGame + 0x411c));
    if (iVar1 != 0 && iVar2 != 0) {
        CellScratch scratch;
        scratch.VecClear();
        const int iVar3 = FUN_00e4ce40(&scratch);
        scratch.mField4 = *(float*)(iVar3 + 0x10c);
        scratch.FUN_00e82130();
        const float fX = *(float*)(iVar1 + 0x4c) - *(float*)(iVar2 + 0x4c);
        const float fY = *(float*)(iVar1 + 0x50) - *(float*)(iVar2 + 0x50);
        const float fZ = *(float*)(iVar1 + 0x54) - *(float*)(iVar2 + 0x54);
        if (fX * fX + fY * fY + fZ * fZ <= scratch.mField4 * scratch.mField4)
            FUN_00e75ea0();
    }
}

// ---------------------------------------------------------------- 0x00e78de0
int  __cdecl FUN_00b3d4d0(void);
static __declspec(noinline) void FUN_00e77930(int);   // static: retail passes the object in ESI

struct ObjStub  { void ad7e40(int modal); };

// @ 0x00e78de0
void __cdecl FUN_00e78de0(void)
{
    ((ObjStub*)FUN_00b3d4d0())->ad7e40(0);
    *(char*)(g_16b3c0c + 0x936) = 0;
    *(char*)(g_16b3c0c + 0xe4) = 0;
    CellStub* cells = (CellStub*)(g_cellGame + 0x1c);
    int v = cells->b721d0(*(int*)(g_cellGame + 0x411c));
    *(char*)(g_cellGame + 0x51dc) = 0;
    if (v)
        FUN_00e77930(v);
}

// ---------------------------------------------------------------- 0x00e78e40
void __cdecl FUN_00e53580(void);
// @ 0x00e78e40
void __cdecl FUN_00e78e40(void)
{
    FUN_00e53580();
    int v = ((CellStub*)(g_cellGame + 0x1c))->b721d0(*(int*)(g_cellGame + 0x411c));
    if (v)
        FUN_00e77930(v);
}

// Static stand-in for the retail TU-local callee (0x00e77930).  The replay resolves the
// call site to the original body, so this body is never executed; it only keeps the
// internal register convention (object arrives in ESI) at the two call sites above.
static __declspec(noinline) void FUN_00e77930(int v)
{
    if (*(char*)(v + 0x180) != 1) {
        FUN_00b3d4d0();
        *(volatile int*)(v + 0x60) = v;
    }
}

// ---------------------------------------------------------------- 0x00e78e70
// @ 0x00e78e70
bool __stdcall FUN_00e78e70(int unused, int* msg)
{
    if (msg[2] == (int)0x287259f6) {
        switch (msg[3]) {
        case 0x447060c: FUN_00e538b0(1); return true;
        case 0x10f366e: SP_sOnButtonSaveClick(); return true;
        case 0x10ed852: FUN_00e53ad0(); return true;
        case (int)0xd305ca84: FUN_00e53920(); return true;
        case 0x10f366d: SP_sOnQuitDesktopButtonClick(); return true;
        case 0x2268ba4: FUN_00e501f0(); return true;
        case 0x43b72d0: FUN_00e53a20(); return true;
        case 0x447060a:
            if (!FUN_00e00ac0())
                FUN_00e53660(2, 1);
            SP_ShowContextSensitiveSporeGuide();
            return true;
        case 0x595e0a8: FUN_00e53ad0(); return true;
        case 0x44827b8: FUN_00e539c0(); return true;
        case 0x44827b9: FUN_00e78e40(); return true;
        case 0x44837c0: FUN_00e760f0(); return true;
        case 0x6244208: FUN_00e53860(1); return true;
        case 0x6455c5e: FUN_00e5daa0(); return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------- 0x00e78fc0
// @ 0x00e78fc0
void __cdecl SP_sUpdateAICaterpillar(int param_1, float param_2)
{
    CellObj* cell = (CellObj*)param_1;
    CellGame* game = (CellGame*)g_cellGame;
    CatalogScratch scratch;
    scratch.VecClear();
    const EaterInfo* entry = (const EaterInfo*)FUN_00e4cc40(cell->mCatalogId, &scratch);

    if (cell->mTimer > 0.0f) {
        const float rest = cell->mTimer - param_2;
        cell->mTimer = rest;
        if (rest < 0.0f) {
            const EaterInfo* active = (const EaterInfo*)FUN_00e52910((int)entry);
            if (active->mState60 == 0) {
                FUN_00e780a0(cell->mId, 1, param_2, 0);
            } else {
                const EaterInfo* active2 = (const EaterInfo*)FUN_00e52910((int)entry);
                const int key = FUN_00e52a40(cell->mField358, active2->mKey9c);
                if (FUN_00e56f20(key)) {
                    const EaterInfo* active3 = (const EaterInfo*)FUN_00e52910((int)entry);
                    FUN_00e74a20(cell->mField35c, (int)&cell->mPos, cell->mField80,
                                 active3->mState60, key, 1.0f, 0.0f, 0, 0, 0);
                    FUN_00e61d90((int)cell, 3);
                    FUN_00e780a0(cell->mId, 0, 0.0f, 0);
                } else {
                    const EaterInfo* active4 = (const EaterInfo*)FUN_00e52910((int)entry);
                    cell->mTimer = active4->mTimerA0;
                    scratch.FUN_00e82130();
                    return;
                }
            }
        }
        scratch.FUN_00e82130();
        return;
    }

    const int other = ((CellStub*)game->mCellStore)->b721d0(game->mSelectedCell);
    if (other != 0) {
        const CellObj* target = (const CellObj*)other;
        const float dx = target->mPos.x - cell->mPos.x;
        const float dy = target->mPos.y - cell->mPos.y;
        const float dz = target->mPos.z - cell->mPos.z;
        const EaterInfo* active = (const EaterInfo*)FUN_00e52910((int)entry);
        const float reach = active->mRange;
        if (reach * reach < dx * dx + dy * dy + dz * dz) {
            const EaterInfo* active2 = (const EaterInfo*)FUN_00e52910((int)entry);
            if (active2->mState60 != 0)
                goto done;
        }
        FUN_00e61d90((int)cell, 4);
        const EaterInfo* active3 = (const EaterInfo*)FUN_00e52910((int)entry);
        cell->mTimer = active3->mTimerA0;
    }
done:
    scratch.FUN_00e82130();
}

// ---------------------------------------------------------------- 0x00e791a0
void __cdecl FUN_00e514c0(void);      // 0x00e514c0  emit (args in registers)

// @ 0x00e791a0  (both cell pointers arrive in registers: EAX = cell A, ESI = cell B)
void __cdecl FUN_00e791a0(int param_1, int param_2, float param_3)
{
    if (*(int*)param_2 == *(int*)(g_cellGame + 0x411c))
        FUN_00e514c0();
    if (*(int*)(param_1 + 0x248) != 0 && *(int*)(param_2 + 0x248) != 0)
        FUN_00e780a0(*(int*)param_1, 1, param_3, 0);
}

// ---------------------------------------------------------------- 0x00e791f0
void __cdecl FUN_00e5eb20(float*, int);   // 0x00e5eb20  unpack the cell transform
void __cdecl SP_sDropLoot(int, int, int, float*, float, int, int, float, int, int); // 0x00e771d0

// @ 0x00e791f0
void __cdecl SP_sDigestionOutput(int param_1, int param_2, float param_3)
{
    if (param_2 == 0)
        return;

    float local_18, local_14, local_10;
    FUN_00e5eb20(&local_18, param_1);

    const float scale = *(float*)(param_1 + 0x58);
    float pos[3];
    pos[0] = *(float*)(param_1 + 0x4c) + local_18 * scale;
    pos[1] = *(float*)(param_1 + 0x50) + local_14 * scale;
    pos[2] = *(float*)(param_1 + 0x54) + local_10 * scale;

    SP_sDropLoot(*(int*)(param_1 + 0x108), param_1 + 0xfc, *(int*)(param_1 + 0x35c),
                 pos, scale * 0.25f, *(int*)(param_1 + 0x358),
                 param_2, param_3, 0, 0);
}

// ---------------------------------------------------------------- 0x00e792b0
// @ 0x00e792b0
void __cdecl SP_sDigestion_End(int param_1, float param_2)
{
    CatalogScratch scratch;
    const int iVar1 = ((CellStub*)(g_cellGame + 0x1c))->b721d0(param_1);
    if (iVar1 == 0)
        return;
    scratch.VecClear();
    const int uVar2 = FUN_00e4cc40(*(int*)(iVar1 + 0x108), &scratch);
    const int iVar3 = FUN_00e52910(uVar2);
    SP_sDigestionOutput(iVar1, *(int*)(iVar3 + 0x78), param_2);
    scratch.FUN_00e82130();
}

// ---------------------------------------------------------------- 0x00e79320
// candidate eater record selected by the cell game's eat mode (+0x5190 -> +0x7c)
static EaterCandidate* EaterCandidateOf(EaterInfo* entry, int eatMode)
{
    if (eatMode == 0) {
        if (entry->mAlt.mId != -1)
            return &entry->mAlt;
        return &entry->mDefault;
    }
    if (eatMode == 2) {
        if (entry->mMid.mId != -1)
            return &entry->mMid;
        return &entry->mDefault;
    }
    return &entry->mDefault;
}

// @ 0x00e79320
void __cdecl SP_sOnEatEater(int param_1, float param_2)
{
    CellObj* cell = (CellObj*)param_1;
    CatalogScratch scratch;
    scratch.VecClear();
    EaterInfo* entry = (EaterInfo*)FUN_00e4cc40(cell->mCatalogId, &scratch);

    ++cell->mCounter;
    const int eaten = cell->mCounter;
    const int eatMode = ((CellGame*)g_cellGame)->mModeStore->mEatMode;

    const EaterCandidate* candidate = EaterCandidateOf(entry, eatMode);
    if (candidate->mCounter6c >= 1) {
        const EaterInfo* active = (const EaterInfo*)FUN_00e52910((int)entry);
        if (active->mCounter6c != eaten)
            goto body;
        FUN_00e57170(cell->mScale * g_1483c20);
        goto reset;
    }
body:
    {
        const EaterCandidate* candidate2 = EaterCandidateOf(entry, eatMode);
        if (eaten >= candidate2->mLimit70)
            goto done;
        const EaterInfo* active = (const EaterInfo*)FUN_00e52910((int)entry);
        if (active->mField74 > 0.0f)
            FUN_00e57260((int)cell, param_2, active->mField74);
        else {
            const EaterInfo* active2 = (const EaterInfo*)FUN_00e52910((int)entry);
            SP_sDigestionOutput((int)cell, active2->mLootId78, param_2);
        }
    }
reset:
    cell->mCounter = 0;
done:
    scratch.FUN_00e82130();
}

// ---------------------------------------------------------------- 0x00e79460
// @ 0x00e79460  (the exclusion id arrives in EBP-adjacent stack slot, i.e. a plain stack arg)
void __fastcall FUN_00e79460(int param_1, int param_2, float param_3, int param_4)
{
    int local_800[512];
    const int n = FUN_00e87260(param_2, param_1, param_3, local_800, 0x200, 0);
    for (int i = 0; i < n; ++i) {
        int* p = (int*)FUN_00b72210(local_800[i]);
        if (*p != param_4 && p[0x3f] != 0 && FUN_00e5cde0())   // +0xfc
            FUN_00e780a0(*p, 0, 0.0f, 0);
    }
}
