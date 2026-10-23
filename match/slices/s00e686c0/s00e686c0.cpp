// Slice s00e686c0 -- SP cell TU (SPCellGame.obj): enemy/candidate selection helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU; no /EHsc).
//
// These are (mostly) static helpers of the big Cell TU.  A "cell" is the large
// simulated object: position at +0x4c, radius +0x58, orientation matrix +0x5c,
// key at +0xfc, level at +0x358, effect group at +0x35c.  Several helpers take a
// "filter" record (two floats + six condition bytes) and several use a per-stage
// handle selected by GetLevelHandle.
#include "types.h"
#include <math.h>

typedef unsigned char u8;

// ------------------------------------------------------------------ math
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
};

// ------------------------------------------------------------------ game objects
struct LevelInfo {
    char pad0[0x1c];
    int mStage;              // +0x1c  (passed to sGetSourceLevel; +0x7c selects the stage)
    char pad20[0x7c - 0x20];
    int mStageIndex;         // +0x7c  selects cell+0x248 / +0x194 / +0xe0
};

struct ObjectPool {
    void* Get(int handle) const;      // 0x00b72210 (thiscall, ret 4)
};

struct CellKey { int a, b, c; };

// A per-shape record inside CellInfo (stride 0x48).
struct CellRecord {
    int     mType;       // +0x00
    Vector3 mVec;        // +0x04
    char    pad10[0x34 - 0x10];
    float   mRadius;     // +0x34
    char    pad38[0x48 - 0x38];
};

struct CellInfo {
    int mCount;              // +0x00
    int mF04;                // +0x04
    // CellRecord array at +0x08, stride 0x48
    char  pad08[0x1214 - 0x08];
    int   mF1214;            // +0x1214
    int   mF1218;            // +0x1218
    char  pad121c[0x124c - 0x121c];
    float mF124c;            // +0x124c
    char  pad1250[0x1260 - 0x1250];
    float mF1260;            // +0x1260
    char  pad1264[0x1268 - 0x1264];
    float mF1268;            // +0x1268
    char  pad126c[0x1284 - 0x126c];
    int   mF1284;            // +0x1284
    int   mF1288;            // +0x1288
};

// The two-float + six-byte "conditions" record produced by 0xe68b30 and read by
// 0xe68870 / 0xe68910.
struct CellFilter {
    float f0;    // +0x00
    float f4;    // +0x04
    char  b8;    // +0x08
    char  b9;    // +0x09
    char  bA;    // +0x0a
    char  bB;    // +0x0b
    char  bC;    // +0x0c
    char  bD;    // +0x0d
};

struct cCell {
    int      mHandle;        // +0x000
    char     pad04[0x48 - 0x04];
    short    mFlags;         // +0x048
    short    mVersion;       // +0x04a
    Vector3  mPosition;      // +0x04c
    float    mRadius;        // +0x058
    float    mOrient[9];     // +0x05c
    char     pad80[0x90 - 0x80];
    Vector3  mVelocity;      // +0x090
    char     pad9c[0xfc - 0x9c];
    int      mKeyA;          // +0x0fc
    int      mKeyB;          // +0x100
    int      mKeyC;          // +0x104
    int      mType;          // +0x108
    char     pad10c[0x112 - 0x10c];
    char     mFlag112;       // +0x112
    char     pad113[0x15c - 0x113];
    float    mF15c;          // +0x15c
    char     pad160[0x17c - 0x160];
    char     mFlag17c;       // +0x17c
    char     pad17d[0x189 - 0x17d];
    char     mFlag189;       // +0x189
    char     pad18a[0x2fc - 0x18a];
    int      mF2fc;          // +0x2fc
    char     mFlag300;       // +0x300
    char     mFlag301;       // +0x301
    char     pad302[0x358 - 0x302];
    int      mLevel;         // +0x358
    int      mEffectGroup;   // +0x35c
    int      mEffect;        // +0x360
    int      mObstacle;      // +0x364
};

struct cCellGame {
    char pad0[0x1c];
    ObjectPool mCells;             // +0x001c
    char pad20[0x411c - 0x20];
    int midPlayerCell;             // +0x411c
    char pad4120[0x5190 - 0x4120];
    LevelInfo* mpLevelInfo;        // +0x5190
};

extern cCellGame* gspCellGame;         // 0x016b3c04
extern const float kLevelSize[];       // 0x01483bd0
extern const float g_1485720;          // 1.0f
extern const float g_13eb95c;          // 3.0f
extern const float g_1485378;          // threshold
extern const float g_13ebc4c;          // 60.0f
extern const float g_13eb1bc;          // -1.0f
extern const Vector3 gCellWorldCenter; // 0x016b3c28
extern const float gCellTileOrient[12]; // 0x016b3dac (9 used)

// ------------------------------------------------------------------ callees
int __fastcall FUN_00e4ee60(void* unused, int stage);     // SP::sGetSourceLevel (edx)
float FUN_00e837c0(int key, float f);                     // 0x00e837c0
cCell* FUN_00e52910(cCell* c);                            // 0x00e52910 (out of line here)
CellInfo* FUN_00e679e0(CellKey key);                      // 0x00e679e0
bool FUN_00e57460(cCell* a, cCell* b);                    // 0x00e57460
int  FUN_00e573e0(cCell* a, cCell* b);                    // 0x00e573e0
bool FUN_00e68470(cCell* a, cCell* b);                    // 0x00e68470
bool FUN_00e685f0(cCell* c);                              // 0x00e685f0
bool FUN_00e685b0(cCell* c);                              // 0x00e685b0
bool FUN_00e68630(cCell* c);                              // 0x00e68630
int  FUN_00e87260(int group, const void* pos, float radius, int* out, int max, int mask); // 0x00e87260
int  FUN_00e4cce0(int id);                                // 0x00e4cce0 LayerCatalog_GetEntry
bool FUN_00e52960();                                      // 0x00e52960
void FUN_00e68000(cCell* c, int index, void* msg);        // 0x00e68000

// Inlined copy of 0xe52910 (also emitted out of line as FUN_00e52910).
__forceinline char* GetLevelHandle(cCell* c)
{
    char* p;
    switch (gspCellGame->mpLevelInfo->mStageIndex) {
    case 0:
        p = (char*)c + 0x248;
        break;
    case 1:
        return (char*)c + 0xe0;
    case 2:
        p = (char*)c + 0x194;
        break;
    default:
        return (char*)c + 0xe0;
    }
    if (*(int*)p == -1)
        return (char*)c + 0xe0;
    return p;
}

__forceinline cCell* PoolGet(int handle)
{
    return (cCell*)((const ObjectPool*)((char*)gspCellGame + 0x1c))->Get(handle);
}

// @ 0x00e686c0
void FUN_00e686c0(cCell* cell, cCell* other, float* outA, float* outB)
{
    int lv = cell->mLevel;
    if (lv == -1) {
        *outA = 1.0f;
        *outB = 1.0f;
        return;
    }
    LevelInfo* li = gspCellGame->mpLevelInfo;
    int sl = FUN_00e4ee60(0, li->mStage);
    float ratio = FUN_00e837c0(0xd2916ee5,
                    (float)((double)kLevelSize[lv] / (double)kLevelSize[sl]));
    if (cell->mKeyA == 0) {
        *outA = ratio * 3.0f;
        *outB = ratio * 3.0f;
        return;
    }
    if (*(int*)FUN_00e52910(other) == 0x1001) {
        CellInfo* info = FUN_00e679e0(*(CellKey*)&cell->mKeyA);
        *outA = info->mF124c * ratio;
        *outB = info->mF124c * ratio;
        return;
    }
    const float zero = 0.0f;
    if (*((float*)FUN_00e52910(other) + 2) == zero)
        *outA = *((float*)FUN_00e52910(other) + 1) * ratio;
    else
        *outA = *((float*)FUN_00e52910(other) + 2) * ratio;
    if (*((float*)FUN_00e52910(other) + 3) != zero)
        *outB = *((float*)FUN_00e52910(other) + 3) * ratio;
    else
        *outB = *((float*)FUN_00e52910(other) + 1) * ratio;
}

// @ 0x00e68870
bool FUN_00e68870(cCell* ref, cCell* cand, CellFilter* f)
{
    if (cand->mFlag112 != 0)
        return false;
    if (FUN_00e57460(ref, cand))
        return false;
    if (FUN_00e573e0(ref, cand) < 2)
        return false;
    if (FUN_00e685f0(cand) && f->bA != 0)
        return true;
    if (FUN_00e685b0(cand) && f->b9 != 0)
        return true;
    if (cand->mKeyA != 0 && cand->mF15c > g_1485378 && f->bC != 0)
        return true;
    if (FUN_00e68630(cand) && f->bD != 0)
        return true;
    return false;
}

// @ 0x00e68910
bool FUN_00e68910(cCell* ref, cCell* cand, CellFilter* f)
{
    if (FUN_00e57460(ref, cand))
        return false;
    if (!FUN_00e68470(ref, cand))
        return false;
    int rel = FUN_00e573e0(ref, cand);
    if (f->b8 != 0) {
        if (rel != 0 && rel != 1) { /* fall through */ }
        else return false;
    }
    if (rel == 0)
        return false;
    if (FUN_00e685f0(cand)) {
        if (!FUN_00e685f0(ref) && f->bA != 0)
            return false;
    }
    if (cand->mFlag189 == 0)
        return true;
    return false;
}

// @ 0x00e68990
void FUN_00e68990(cCell* ref, float* filt, int* outA, int* outB, int* outC)
{
    if (outC != 0)
        *outC = 0;
    float* pr = (filt[1] > filt[0]) ? (filt + 1) : filt;
    int buf[0x200];
    int n = FUN_00e87260(ref->mEffectGroup, (char*)ref + 0x4c, *pr, buf, 0x200, 0);
    *outA = 0;
    float bestA = filt[1] * filt[1];
    *outB = 0;
    float bestB = filt[0] * filt[0];
    for (int i = 0; i < n; i++) {
        int h = buf[i];
        if (h == ref->mHandle)
            continue;
        cCell* obj = PoolGet(h);
        float dx = ref->mPosition.x - obj->mPosition.x;
        float dy = ref->mPosition.y - obj->mPosition.y;
        float dz = ref->mPosition.z - obj->mPosition.z;
        float d = dx * dx + dy * dy + dz * dz;
        if (FUN_00e68870(ref, obj, (CellFilter*)filt)) {
            if (d <= bestA) {
                *outA = obj->mHandle;
                bestA = d;
            }
        } else if (FUN_00e68910(ref, obj, (CellFilter*)filt)) {
            if (d <= bestB) {
                *outB = obj->mHandle;
                bestB = d;
            }
        } else if (outC != 0 && obj->mHandle != ref->mHandle) {
            *outC = obj->mHandle;
        }
    }
}

// @ 0x00e68b30
void FUN_00e68b30(cCell* a0, cCell* a1, CellFilter* out)
{
    FUN_00e686c0(a0, a1, &out->f0, &out->f4);
    out->b9 = GetLevelHandle(a1)[0x8d];
    out->bA = GetLevelHandle(a1)[0x8e];
    out->bB = GetLevelHandle(a1)[0x91];
    out->bD = GetLevelHandle(a1)[0x90];
    out->bC = GetLevelHandle(a1)[0x8f];
    out->b8 = GetLevelHandle(a1)[0x92];
}

// @ 0x00e68cd0
bool FUN_00e68cd0(cCell* c)
{
    if (c->mKeyA == 0)
        return false;
    CellInfo* info = FUN_00e679e0(*(CellKey*)&c->mKeyA);
    if (info->mF1260 == -1.0f)
        return false;
    return true;
}

// @ 0x00e68d20
#pragma float_control(precise, off)
bool FUN_00e68d20(cCell* c, const float* pt, float extra, int* outIdx, float* outDist)
{
    if (c->mKeyA == 0 || c->mKeyB == 0 || c->mKeyC == 0) {
    }
    if (c->mKeyA == 0 || *(int*)((char*)c + 0x248) == 0) {
        *outIdx = -1;
        float dx = c->mPosition.x - pt[0];
        float dy = c->mPosition.y - pt[1];
        float dz = c->mPosition.z - pt[2];
        float d2 = dx * dx + dy * dy + dz * dz;
        float d = (float)sqrt((double)d2) - c->mRadius;
        float val = 0.0f;
        if (d > 0.0f)
            val = d;
        *outDist = val;
        float thr = c->mRadius + extra;
        return d2 < thr * thr;
    }
    CellInfo* info = FUN_00e679e0(*(CellKey*)&c->mKeyA);
    int n = info->mCount;
    CellRecord* rec = (CellRecord*)((char*)info + 8);
    for (int i = 0; i < n; i++, rec = (CellRecord*)((char*)rec + 0x48)) {
        if (rec->mType != 0xc &&
            !(rec->mType == 2 && c->mHandle != gspCellGame->midPlayerCell))
            continue;
        float vx = rec->mVec.x, vy = rec->mVec.y, vz = rec->mVec.z;
        if (c->mFlags & 2) {
            float nx = c->mOrient[0] * vx + c->mOrient[3] * vy + c->mOrient[6] * vz;
            float ny = c->mOrient[1] * vx + c->mOrient[4] * vy + c->mOrient[7] * vz;
            float nz = c->mOrient[2] * vx + c->mOrient[5] * vy + c->mOrient[8] * vz;
            vx = nx; vy = ny; vz = nz;
        }
        float cx = c->mRadius * vx + c->mPosition.x;
        float cy = c->mRadius * vy + c->mPosition.y;
        float cz = c->mRadius * vz + c->mPosition.z;
        float recR = rec->mRadius * c->mRadius;
        float thr = recR + extra;
        float dx = cx - pt[0];
        float dy = cy - pt[1];
        float dz = cz - pt[2];
        float d2 = dx * dx + dy * dy + dz * dz;
        if (d2 < thr * thr) {
            *outIdx = i;
            float d = (float)sqrt((double)d2) - recR;
            float val = 0.0f;
            if (d > 0.0f)
                val = d;
            *outDist = val;
            return true;
        }
    }
    return false;
}
#pragma float_control(precise, on)

// @ 0x00e69000
void FUN_00e69000(cCell* ref, const void* pt, float extra, int* outHandle, int* outIdx,
                  float* outDist, int* exclude, int excludeCount)
{
    int buf[0x200];
    int n = FUN_00e87260(ref->mEffectGroup, (char*)ref + 0x4c, ref->mRadius + extra, buf, 0x200, 0);
    *outDist = extra;
    *outHandle = 0;
    for (int i = 0; i < n; i++) {
        int h = buf[i];
        if (h == ref->mHandle)
            continue;
        int j = 0;
        for (; j < excludeCount; j++) {
            if (exclude[j] == h)
                break;
        }
        if (j < excludeCount)
            continue;
        cCell* obj = PoolGet(h);
        if (!FUN_00e52960())
            continue;
        if (obj->mFlag17c == 1)
            continue;
        if (FUN_00e573e0(ref, obj) == 4 && obj->mType == FUN_00e4cce0(0x16))
            continue;
        if (FUN_00e68cd0(obj))
            continue;
        int oi;
        float od;
        if (!FUN_00e68d20(obj, (const float*)pt, extra, &oi, &od))
            continue;
        if (od < *outDist) {
            *outHandle = buf[i];
            *outIdx = oi;
            *outDist = od;
        }
    }
}

// @ 0x00e69190
void FUN_00e69190(cCell* cell, float param_2, int* outA, int* outB, int* outC,
                  int* exclude, int excludeCount)
{
    *outB = 0;
    *outA = -1;
    *outC = -1;
    float best = param_2;
    CellInfo* info = FUN_00e679e0(*(CellKey*)&cell->mKeyA);
    int n = info->mCount;
    CellRecord* rec = (CellRecord*)((char*)info + 8);
    for (int i = 0; i < n; i++, rec = (CellRecord*)((char*)rec + 0x48)) {
        if (rec->mType != 6)
            continue;
        float msg[0x10];
        msg[0] = 0.0f;
        msg[1] = 0.0f;
        msg[2] = gCellWorldCenter.x;
        msg[3] = gCellWorldCenter.y;
        msg[4] = gCellWorldCenter.z;
        msg[5] = 1.0f;
        for (int k = 0; k < 9; k++)
            msg[6 + k] = gCellTileOrient[k];
        Vector3 pos;
        pos.x = gCellWorldCenter.x;
        pos.y = gCellWorldCenter.y;
        pos.z = gCellWorldCenter.z;
        FUN_00e68000(cell, i, msg);
        int outHandle = 0;
        int outIdx;
        float outDist;
        FUN_00e69000(cell, &pos, param_2, &outHandle, &outIdx, &outDist, exclude, excludeCount);
        if (outHandle != 0 && outDist <= best) {
            *outA = i;
            *outB = outHandle;
            *outC = outIdx;
            best = outDist;
        }
    }
}

// @ 0x00e693f0
int FUN_00e693f0(int unused0, int* start, float unused2, float radius, int* out)
{
    *out = *start;
    int i = 1;
    do {
        cCell* obj = PoolGet(out[i - 1]);
        int outHandle = 0;
        int outIdx;
        float outDist;
        FUN_00e69000(obj, (char*)obj + 0x4c, radius, &outHandle, &outIdx, &outDist, out, i);
        if (outHandle == 0)
            return i;
        out[i] = outHandle;
        i++;
    } while (i < 0x20);
    return i;
}

// @ 0x00e69480
float FUN_00e69480(cCell* cell, cCell* other, char flag)
{
    int* h = (int*)FUN_00e52910(other);
    float result;
    if (*h == 0x1001 || cell->mHandle == gspCellGame->midPlayerCell) {
        CellInfo* info = FUN_00e679e0(*(CellKey*)&cell->mKeyA);
        result = info->mF1268;
    } else if (flag && (result = *((float*)FUN_00e52910(other) + 0x16)) != 0.0f) {
        /* use result */
    } else {
        result = *((float*)FUN_00e52910(other) + 0x15);
    }
    if (cell->mLevel != -1)
        return (kLevelSize[cell->mLevel] / (*(float*)((char*)gspCellGame + 0x514c) * 60.0f)) * result;
    return result;
}

// @ 0x00e69580
int FUN_00e69580(cCell* c)
{
    if (c->mKeyA == 0)
        return 0;
    CellInfo* info = FUN_00e679e0(*(CellKey*)&c->mKeyA);
    if (gspCellGame->midPlayerCell != c->mHandle)
        return 1;
    if (info->mF1218 <= 2)
        return 1;
    return (info->mF1218 > 4) + 2;
}
