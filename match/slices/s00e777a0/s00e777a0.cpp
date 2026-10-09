// Slice s00e777a0: Cell game spawning (poke, drop pieces, create plants).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct Vector3 { float x, y, z; Vector3() {} Vector3(float a,float b,float c):x(a),y(b),z(c){} };

struct CellKey { int a, b, c; };

struct CellInfo {
    char pad[0xcc];
    int mFieldCC;   // 0xcc
    char padD0[0xd4 - 0xd0];
    int mFieldD4;   // 0xd4
};

struct ObjectPool {
    void* Get(int handle) const;         // 0x00b72210
    void* GetChecked(int handle) const;  // 0x00b721d0
    int   Alloc();                       // 0x00b72160
    void  Free(int handle);              // 0x00b72260
};

struct cLevelInfo { char pad[0x1c]; int mStage; };   // +0x1c

struct cCellGame {
    char pad0[0x1c];
    ObjectPool mCells;   // 0x1c
    char pad20[0x40fc - 0x20];
    int mSel40fc;        // 0x40fc
    int mSel4100;        // 0x4100
    int mObstacleGrid;   // 0x4104
    char pad4108[0x411c - 0x4108];
    int mHandle411c;     // 0x411c
    char pad4120;
    char mByte4121;
    char pad4122[0x5190 - 0x4122];
    cLevelInfo* mpLevelInfo;  // 0x5190
    int mField5194;           // 0x5194
};

struct cCellGfx { char pad0[0x168]; ObjectPool mEffects; };

struct CellState {
    char pad0[0xe0];
    int mFieldE0;         // 0xe0
    char padE4[0xf4 - 0xe4];
    float mFieldF4;       // 0xf4
    char padF8[0x936 - 0xf8];
    char mField936;       // 0x936
};

struct cCell {
    int mHandle;          // 0x00
    char pad04[0x1c - 4];
    float mField1c;       // 0x1c
    float mField20;       // 0x20
    int mField24;         // 0x24
    int mField28;         // 0x28
    int mField2c;         // 0x2c
    int mField30;         // 0x30
    int mField34;         // 0x34
    int mField38;         // 0x38
    int mField3c;         // 0x3c
    int mField40;         // 0x40
    int mField44;         // 0x44
    Vector3 mVec48;       // 0x48
    Vector3 mVec54;       // 0x54
    Vector3 mVec60;       // 0x60
    Vector3 mVec6c;       // 0x6c
    int mField78;         // 0x78
    char pad7c[0x1c4 - 0x7c];
    float mField1c4;      // 0x1c4
    float mField1c8;      // 0x1c8
    float mField1cc;      // 0x1cc
};

struct Cell2 {
    char pad0[0x358];
    int mField358;        // 0x358
    int mField35c;        // 0x35c
    int mField360;        // 0x360
    int mField364;        // 0x364
    char pad368[0x370 - 0x368];
    int mField370;        // 0x370
};

// Long-lived cell object used by the spawn helpers (cells live in gspCellGame->mCells).
struct cSpawnCell {
    int mHandle;          // 0x000
    char pad004[0x1c - 4];
    float mField1c;       // 0x1c
    float mField20;       // 0x20
    int mField24;         // 0x24
    int mField28;         // 0x28
    int mField2c;         // 0x2c
    int mField30;         // 0x30
    int mField34;         // 0x34
    int mField38;         // 0x38
    int mField3c;         // 0x3c
    int mField40;         // 0x40
    int mField44;         // 0x44
    char mField48[4];     // 0x48
    Vector3 mPos;         // 0x4c
    float mRadius;        // 0x58
    char pad05c[0xfc - 0x5c];
    CellKey mKey;         // 0x0fc
    int mType;            // 0x108
    char pad10c[0x17f - 0x10c];
    char mField17f;       // 0x17f
    char pad180[0x1b0 - 0x180];
    int mField1b0;
    char pad1b4[0x248 - 0x1b4];
    int mPoolHandle;      // 0x248
    char pad24c[0x358 - 0x24c];
    int mField358;        // 0x358
    int mField35c;        // 0x35c
    int mField360;        // 0x360
    int mField364;        // 0x364
    char pad368[0x370 - 0x368];
    int mField370;        // 0x370
};

extern cCellGame* gspCellGame;    // 0x016b3c04
extern cCellGfx* gspCellGfx;      // 0x016b3c08
extern CellState* gspCellState;   // 0x016b3c0c
extern Vector3 gCellWorldCenter;  // 0x016b3c28
extern Vector3 gDefaultTransform; // 0x015a7c4c
extern float gField3dd0;          // 0x016b3dd0
extern const float gOrientA[6];   // 0x015a7c34
extern float gField15a7c4c[4];    // 0x015a7c4c
extern const float gConst1464c18; // 0x01464c18  (1/7)
extern const float gConst1488874; // 0x0148874   (0.1)
extern const float gConst1485548; // 0x01485548  (1.5)

struct cCellStageInfo { int mLevel; int mStart; int pad[5]; };
extern const cCellStageInfo kCellStages[];    // 0x01483c14
extern const cCellStageInfo kCellEditorStage; // 0x01483e60

int  FUN_00e4cce0(int id);                       // 0x00e4cce0
int  FUN_00e4cce0_5(int id, int a, float b, float c, float d);  // 0x00e4cce0
void FUN_00743b50(void* iter);                   // 0x00743b50
int* FUN_00e4cc40(int id, void* iter);           // 0x00e4cc40 (thunk to 0x00e823a0)
void FUN_00e82130(void* iter);                   // 0x00e82130
int  sGetSourceLevel();                          // 0x00e4ee60
int  sCreateLeakAttachment(void* a, int b, int c, int d, int e);   // 0x00e76af0
int  FUN_00e6d200(cSpawnCell* c, int a2, int a3, int a4);         // 0x00e6d200
void FUN_00e51ee0(int a1, float f2, int a3, int a4, int a5, int a6, int a7, int a8, int a9,
                  int a10, int a11, int a12, int a13, int a14, int a15, int a16);  // 0x00e51ee0
void FUN_00e593b0(int a, int b, int c, int d);   // 0x00e593b0
void FUN_00b3d4d0(int a);                        // 0x00b3d4d0
void FUN_00ad7e40(int a);                        // 0x00ad7e40
void FUN_00e598e0(float f);                      // 0x00e598e0
void FUN_00e86980(int a, int b);                 // 0x00e86980
void FUN_00bbbde0(int grid, int obstacle);       // 0x00bbbde0 (thunk to 0x00bbb210)
void FUN_00e66010(int a);                        // 0x00e66010
void FUN_00e67890(cSpawnCell* c);                // 0x00e67890
void FUN_00e59200(int a);                        // 0x00e59200
void FUN_00e61370(void* out, void* in, float t);// 0x00e61370
int  sCreateCellAttachment(cSpawnCell* c, int a, void* vec, int b, int type, int key); // 0x00e76d70
int  FUN_00e74a20(int a1, int a2, float f1, int type, int count, float f2, float f3,
                  int one, const void* def, int neg1);   // 0x00e74a20
void sDropLoot(int a1, void* key, int a3, void* pos, float radius, int lvl, int a7, int a8,
               void* out, int* count);                  // 0x00e771d0
int  FUN_00e76540(void* a, int b, int c);        // 0x00e76540
int  FUN_00e76540b(void* a, int b, int c, int d, const void* e, float f, float g, float h); // 0x00e76540
int  FUN_00e76480(int a, int b, const void* c);  // 0x00e76480
int  FUN_00b72210(void* pool, int handle);       // 0x00b72210

class RandomLCG { public: double RandomDoubleUniform(); };  // 0x009360d0
extern RandomLCG gMathRandom;   // 0x01601760

// Stage level for a cell level (mirrors the inlined kCellStages scan).
inline int GetStageLevel(int stage)
{
    int* p;
    if (stage == 1000) {
        p = (int*)&kCellEditorStage;
    } else {
        int i = 0;
        p = (int*)&kCellStages[0];
        if (stage >= 0) {
            p = (int*)&kCellStages[1].mStart;
            do { p += 7; i++; } while (stage >= *p);
        }
        p = (int*)&kCellStages[0] + i * 7;
    }
    return *p;
}

// @ 0x00e777a0
void SP_sPoke_Start(cSpawnCell* a1, Cell2* a2, int a3, int a4, int a5)
{
    if (a1->mField17f == 1)
        return;
    int it[4];
    FUN_00743b50(it);
    CellInfo* info = (CellInfo*)FUN_00e4cc40(*(int*)((char*)a2 + 0x108), &a1);
    int cc = info->mFieldCC;
    if (cc == 0) {
        FUN_00e82130(it);
        return;
    }
    int lvl = a1->mField358;
    if (lvl == -1)
        lvl = sGetSourceLevel();
    int att = sCreateLeakAttachment(a2, a4, lvl, cc, -1);
    if (att != 0) {
        cSpawnCell* c = (cSpawnCell*)gspCellGame->mCells.Get(a1->mHandle);
        int r = FUN_00e6d200(c, 0, 0x1c, c->mField1b0);
        FUN_00e51ee0(0xe, (float)r, *(int*)a1, *(int*)a2, a3, -1, 0, 0, 0, 0, a5, 0, 0, 0, 0, 0);
        FUN_00e593b0(*(int*)a1, *(int*)a2, a3, a5);
    }
    FUN_00e82130(it);
}

// @ 0x00e778b0
bool FUN_00e778b0(int* p)
{
    int h = p[0x28 / 4];
    ObjectPool& cells = gspCellGame->mCells;
    cSpawnCell* c = (cSpawnCell*)cells.GetChecked(h);
    if (c == 0)
        return false;
    int r = FUN_00e4cce0_5(8, (int)&gCellWorldCenter, 0.0f, 1.5f, 0.0f);
    r = FUN_00e76540(c, -1, r);
    gspCellState->mFieldE0 = r;
    gspCellState->mFieldF4 = 0.0f;
    return true;
}

// @ 0x00e77930
void FUN_00e77930(void* state_esi)
{
    cSpawnCell* cell = (cSpawnCell*)state_esi;
    if (*(char*)((char*)state_esi + 0x60) != 1 &&
        *(char*)((char*)state_esi + 0x113) == 0 &&
        *(char*)((char*)state_esi + 0x112) == 0) {
        FUN_00b3d4d0(1);
        FUN_00ad7e40(1);
        gspCellState->mField936 = 1;
        cSpawnCell* c = (cSpawnCell*)gspCellGame->mCells.Get(cell->mHandle);
        int r = FUN_00e6d200(c, 0, 0x29, c->mField1b0);
        float f = (float)r + 1.0f;
        int h = gspCellGfx->mEffects.Alloc();
        cSpawnCell* o = (cSpawnCell*)gspCellGfx->mEffects.Get(h);
        o->mField1c = f;
        o->mField20 = f;
        o->mField24 = 0x1e;
        o->mField28 = cell->mHandle;
        o->mField2c = 0;
        o->mField30 = -1;
        o->mField34 = -1;
        o->mField38 = 0;
        o->mField3c = 0;
        o->mField40 = 0;
        o->mField44 = 0;
        *(Vector3*)((char*)o + 0x48) = gCellWorldCenter;
        *(Vector3*)((char*)o + 0x54) = gCellWorldCenter;
        *(float*)((char*)o + 0x60) = gField15a7c4c[0];
        *(float*)((char*)o + 0x64) = gField15a7c4c[1];
        *(float*)((char*)o + 0x68) = gField15a7c4c[2];
        *(float*)((char*)o + 0x6c) = gField15a7c4c[3];
        *(int*)((char*)o + 0x70) = 0;
        *(char*)((char*)o + 0x74) = 0;
        *(int*)((char*)o + 0x78) = 0;
        *(int*)((char*)o + 0x4) = 0;
        *(char*)((char*)o + 0x8) = 0;
        cSpawnCell* o2 = (cSpawnCell*)gspCellGfx->mEffects.Get(h);
        *(void**)((char*)o2 + 4) = (void*)&FUN_00e778b0;
        gspCellGame->mField5194 = h;
        *(char*)((char*)state_esi + 1) = 1;
        FUN_00e598e0((float)r);
    }
}

// @ 0x00e77ac0
void SP_sDropPieces(cSpawnCell* cell, float* param_2, float param_3)
{
    if (cell->mField358 == 0)
        return;
    int lvl = cell->mField358 - 1;
    if (lvl < 0) lvl = 0;
    if (lvl > 0x13) lvl = 0x13;
    int local_818 = 0;
    float local_800[512];
    sDropLoot(cell->mType, &cell->mKey, cell->mField35c, &cell->mPos, cell->mRadius, lvl,
              (int)param_2, param_3, local_800, &local_818);
    if (local_818 <= 0)
        return;
    float inv = 1.0f / param_3;
    for (int i = 0; i < local_818; i++) {
        cSpawnCell* c = (cSpawnCell*)gspCellGame->mCells.Get((int)local_800[i]);
        float dx = c->mPos.x - param_2[0];
        float dy = c->mPos.y - param_2[1];
        float dz = c->mPos.z - param_2[2];
        float d2 = dx * dx + dy * dy + dz * dz;
        float f = 1.0f / (d2 + 1.5258789e-05f);
        *(float*)((char*)c + 0x1c8) += ((f * dz) * inv) * 10.0f;
        *(float*)((char*)c + 0x1c4) += ((f * dx) * inv) * 10.0f;
        *(float*)((char*)c + 0x1cc) += ((f * dy) * inv) * 10.0f;
    }
}

// @ 0x00e77d50
void FUN_00e77d50(void* cell_esi)
{
    cSpawnCell* cell = (cSpawnCell*)cell_esi;
    for (int i = 0; i < 0x10; i++) {
        float a = ((float)i * gField3dd0 * 0.0625f) * 0.5f;
        float s = 0, c = 0;
        __asm { fld a }
        __asm { fsin }
        __asm { fstp s }
        __asm { fld a }
        __asm { fcos }
        __asm { fstp c }
        float p20 = gOrientA[3] * s;
        float p1c = gOrientA[4] * s;
        float p18 = gOrientA[5] * s;
        float f7 = -gOrientA[0];
        float f8 = -gOrientA[1];
        float f9 = -gOrientA[2];
        float v2c, v28, v24;
        v2c = (((p1c * p20 - c * p18) * f8 + (c * p1c + p18 * p20) * f9) * 2.0f +
               (1.0f - (p18 * p18 + p1c * p1c) * 2.0f) * f7) * 5.0f +
              (float)*(int*)((char*)cell + 0x24) * 1.2f;
        v28 = (((p18 * p1c - c * p20) * f9 + (c * p18 + p1c * p20) * f7) * 2.0f +
               (1.0f - (p18 * p18 + p20 * p20) * 2.0f) * f8) * 5.0f +
              (float)*(int*)((char*)cell + 0x28) * 1.2f;
        v24 = (((c * p20 + p18 * p1c) * f8 + (p18 * p20 - c * p1c) * f7) * 2.0f +
               (1.0f - (p1c * p1c + p20 * p20) * 2.0f) * f9) * 5.0f +
              (float)*(int*)((char*)cell + 0x2c) * 1.2f;
        int lvl = GetStageLevel(gspCellGame->mpLevelInfo->mStage);
        int r = FUN_00e4cce0(4);
        r = FUN_00e76480(lvl, r, &v2c);
        cSpawnCell* o = (cSpawnCell*)gspCellGame->mCells.Get(r);
        *(int*)((char*)o + 0xac) = 0x3951b717;
        if (cell->mHandle == gspCellGame->mHandle411c) {
            *(short*)((char*)o + 0x4a) = *(short*)((char*)o + 0x4a) + 1;
            *(float*)((char*)o + 0x58) = 0.6f;
            *(int*)((char*)o + 0x10c) = cell->mHandle;
            *(char*)((char*)o + 0x110) = 1;
        }
    }
}

// @ 0x00e780a0
void FUN_00e780a0(int handle, char flag, int a3, int a4)
{
    cSpawnCell* c = (cSpawnCell*)gspCellGame->mCells.GetChecked(handle);
    if (c == 0)
        return;
    if (handle == gspCellGame->mHandle411c)
        gspCellGame->mHandle411c = 0;
    cSpawnCell* cc = (cSpawnCell*)gspCellGame->mCells.Get(handle);
    FUN_00e86980(cc->mField35c, cc->mField360);
    if (cc->mField364 != -1)
        FUN_00bbbde0(gspCellGame->mObstacleGrid, cc->mField364);
    if (cc->mPoolHandle != 0) {
        FUN_00e66010(a4);
        if (flag != 0)
            FUN_00e67890(cc);
    }
    if (cc->mField370 != 0)
        FUN_00e59200(cc->mField370);
    if (flag != 0) {
        int it[4];
        FUN_00743b50(it);
        CellInfo* info = (CellInfo*)FUN_00e4cc40(cc->mType, it);
        int lvl = sGetSourceLevel() - 1;
        int idx = lvl;
        if (lvl >= 0) idx = lvl;
        if (idx > 0x13) idx = 0x13;
        if (cc->mField358 != idx)
            sDropLoot(cc->mType, &cc->mKey, cc->mField35c, &cc->mPos, cc->mRadius, idx,
                      info->mFieldD4, a3, 0, 0);
        FUN_00e82130(it);
    }
    gspCellGame->mCells.Free(handle);
}

// @ 0x00e78230
int FUN_00e78230(int a1, int a2, int a3, int count)
{
    int uv2 = FUN_00e4cce0(10);
    int uv3 = FUN_00e4cce0(0xb);
    int uv4 = FUN_00e4cce0(0xc);
    int lvl0 = GetStageLevel(gspCellGame->mpLevelInfo->mStage);
    int cell = FUN_00e74a20(a1, a2, 0.0f, uv2, count, 1.0f, 0.0f, 1, &gDefaultTransform, -1);
    cSpawnCell* cp;
    { ObjectPool& cells = gspCellGame->mCells; cp = (cSpawnCell*)cells.Get(cell); }
    if (count < lvl0)
        goto done78230;
    {
        for (int i = 0; i < 10; i++) {
            Vector3 local_18;
            FUN_00e61370(&local_18, (void*)((char*)cp + 0x48), (float)i * 0.1f);
            int att = sCreateCellAttachment(cp, 1, &local_18, count - 1, uv3, cell);
            cSpawnCell* ap;
            { ObjectPool& cells = gspCellGame->mCells; ap = (cSpawnCell*)cells.Get(att); }
            if (count > lvl0) {
                for (int j = 3; j < 8; j++) {
                    Vector3 local_c;
                    FUN_00e61370(&local_c, (void*)((char*)ap + 0x48), (float)j * 0.1f);
                    sCreateCellAttachment(ap, 1, &local_c, count - 2, uv4, cell);
                }
            }
        }
    }
done78230:
    return cell;
}

// @ 0x00e783d0
namespace SP {
int sCreatePlant_Type1(int a1, int a2, int a3, int count)
{
    int uv2 = FUN_00e4cce0(0xd);
    int uv3 = FUN_00e4cce0(0xe);
    int uv4 = FUN_00e4cce0(0xf);
    int lvl0 = GetStageLevel(gspCellGame->mpLevelInfo->mStage);
    int cell = FUN_00e74a20(a1, a2, 0.0f, uv2, count, 1.0f, 0.0f, 1, &gDefaultTransform, -1);
    cSpawnCell* cp;
    { ObjectPool& cells = gspCellGame->mCells; cp = (cSpawnCell*)cells.Get(cell); }
    if (count < lvl0)
        goto done783d0;
    {
        for (int i = 0; i < 7; i++) {
            Vector3 local_18;
            FUN_00e61370(&local_18, (void*)((char*)cp + 0x48), (float)i * 0.14285715f);
            int att = sCreateCellAttachment(cp, 1, &local_18, count - 1, uv3, cell);
            cSpawnCell* ap;
            { ObjectPool& cells = gspCellGame->mCells; ap = (cSpawnCell*)cells.Get(att); }
            if (count > lvl0) {
                for (int j = 4; j < 7; j++) {
                    Vector3 local_c;
                    FUN_00e61370(&local_c, (void*)((char*)ap + 0x48), (float)j * 0.1f);
                    sCreateCellAttachment(ap, 1, &local_c, count - 2, uv4, cell);
                }
            }
        }
    }
done783d0:
    return cell;
}
}

// @ 0x00e78570
namespace SP {
int sCreatePlant_Type2(int a1, int a2, int a3, int count)
{
    int n = count;
    int uv3 = FUN_00e4cce0(0xe);
    int lvl0 = GetStageLevel(gspCellGame->mpLevelInfo->mStage);
    int cell = FUN_00e74a20(a1, a2, 0.0f, uv3, count, 1.0f, 0.0f, 1, &gDefaultTransform, -1);
    if (lvl0 <= count) {
        int remaining = 8;
        int cur = cell;
        do {
            cSpawnCell* cp = (cSpawnCell*)gspCellGame->mCells.Get(cur);
            double rnd = gMathRandom.RandomDoubleUniform();
            float f = (float)((rnd + rnd) - 1.0);
            if (f > 1.0f) f = 1.0f;
            if (f < -1.0f) f = -1.0f;
            Vector3 local_c;
            FUN_00e61370(&local_c, (void*)((char*)cp + 0x48), (float)(f * 0.1 + 0.75));
            int att = sCreateCellAttachment(cp, 1, &local_c, n, uv3, cur);
            gspCellGame->mCells.Get(att);
            if (lvl0 < n)
                cur = att;
            remaining--;
        } while (remaining != 0);
    }
    return cell;
}
}
