// Slice s00e6cbd0: Cell game spawn/animation selection helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
struct Matrix3 { float m[9]; };

// Row vector * matrix (the module's transform convention).
inline Vector3 operator*(const Vector3& v, const Matrix3& mm)
{
    return Vector3(v.x * mm.m[0] + v.y * mm.m[3] + v.z * mm.m[6],
                   v.x * mm.m[1] + v.y * mm.m[4] + v.z * mm.m[7],
                   v.x * mm.m[2] + v.y * mm.m[5] + v.z * mm.m[8]);
}

struct CellKey { int a, b, c; };

struct CellSpawn {
    int f0;          // 0x00
    int f1;          // 0x04
    float weight;    // 0x08
    int flag;        // 0x0c
    int type;        // 0x10
    char outA;       // 0x14
    char pad15[3];
    int f6;          // 0x18
    int f7;          // 0x1c
    char outB;       // 0x20
    char pad21[3];
};
extern CellSpawn gCellSpawns[];   // 0x01483f70

struct CellInfo {
    char pad0[0x1214];
    int mField1214;   // 0x1214
    char pad1218[0x1238 - 0x1218];
    Vector3 mVec1238; // 0x1238
    float mScale1244; // 0x1244
    char pad1248[0x1284 - 0x1248];
    int mField1284;   // 0x1284
    int mField1288;   // 0x1288
};

CellInfo* FindCellInfo(CellKey key);   // 0x00e679e0

struct EffectObj {
    void FUN_00e4f100(int id, float v, int a, int b);   // 0x00e4f100
    float FUN_00e4f040(int r);                          // 0x00e4f040
    void FUN_00e4f330(int a, float b, float c, float d, int e);  // 0x00e4f330
};

struct ObjectPool {
    void* Get(int handle) const;         // 0x00b72210
    void* GetChecked(int handle) const;  // 0x00b721d0
    int   Alloc();                       // 0x00b72160
};

struct cCell {
    int mHandle;         // 0x00
    char pad04[0x48 - 0x4];
    short mFlags;        // 0x48
    char pad4a[0x4c - 0x4a];
    Vector3 mPosition;   // 0x4c
    float mRadius;       // 0x58
    Matrix3 mOrient;     // 0x5c
    char pad80[0x90 - 0x80];
    Vector3 mVelocity;   // 0x90
    char pad9c[0xfc - 0x9c];
    CellKey mKey;        // 0xfc
    int mType;           // 0x108
    char pad10c[0x18c - 0x10c];
    int mState0;         // 0x18c
    char pad190[0x1ac - 0x190];
    char mFlag1ac;       // 0x1ac
    char pad1ad[0x1b0 - 0x1ad];
    int mState1;         // 0x1b0
    int mState2;         // 0x1b4
    float mTimer;        // 0x1b8
    char pad1bc[0x248 - 0x1bc];
    int mPoolHandle;     // 0x248
    int mAnimIdx;        // 0x24c
    int mAnimCount;      // 0x250
    int mAnimData;       // 0x254
    char pad258[0x35c - 0x258];
    int mEffectGroup;    // 0x35c
    int mEffect;         // 0x360
    int mObstacle;       // 0x364
    char pad368[0x390 - 0x368];
    char mFlag390;       // 0x390
    char mFlag391;       // 0x391
};

struct cLevelInfo {
    char pad0[0x1c];
    int mField1c;   // 0x1c
    char pad20[0x74 - 0x20];
    int mField74;   // 0x74
};

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
    char mByte4121;      // 0x4121
    char pad4122[0x5190 - 0x4122];
    cLevelInfo* mpLevelInfo;  // 0x5190
};

struct cCellGfx {
    char pad0[0x168];
    ObjectPool mEffects;   // 0x168
    char pad16c[0x16254 - 0x16c];
    int mField16254;       // 0x16254
};

extern cCellGame* gspCellGame;   // 0x016b3c04
extern cCellGfx* gspCellGfx;     // 0x016b3c08

int  FUN_00e516c0(cCell* c);            // 0x00e516c0
float FUN_00e563e0(cCell* c);           // 0x00e563e0
bool FUN_00e5c460(int handle, int v);   // 0x00e5c460
bool FUN_00e5c410(int handle, int v);   // 0x00e5c410
int* FUN_00e823a0(int id, void* iter);  // 0x00e823a0 (thunk 0x00e4cc40)
void FUN_00743b50(void* iter);          // 0x00743b50
void FUN_00e82130(void* iter);          // 0x00e82130
void* FUN_00e52910(int x);              // 0x00e52910
void FUN_00e51930();                    // 0x00e51930

struct IContext;

struct IDelegate {
    IContext* FUN_007ec160();           // 0x007ec160 (thiscall, no args)
};
struct IContext {
    void FUN_007eb820(int v);           // 0x007eb820 (thiscall, one arg)
    char pad[0xc];
    int* mOut;                          // 0x0c
};
IDelegate* __stdcall FUN_0067de90(int, int);   // 0x0067de90
void FUN_00e5cb60(void* a, void* out, void* b, void* c, int handle, int k, int z);  // 0x00e5cb60
void FUN_00e5ce90(void* a, int b, bool c, int d, int e, CellKey key);                 // 0x00e5ce90
void FUN_00e83e30(void* a, void* b, int* key);      // 0x00e83e30
void FUN_00e52060(void* a, int b, int* c);          // 0x00e52060
class RandomLCG {
public:
    double RandomDoubleUniform();                   // 0x009360d0
};
extern RandomLCG gMathRandom;                       // 0x01601760
void MoveObstacle(int grid, int obstacle, const void* vMin, const void* vMax);   // 0x00bbc2f0
extern char gCellSpawnTableTag[];   // 0x016ae800

// @ 0x00e6d680
bool FUN_00e6d680(cCell* c)
{
    if (c->mKey.a == 0)
        return false;
    CellInfo* info = FindCellInfo(c->mKey);
    return info->mField1214 > 0;
}

// @ 0x00e6d6d0
float FUN_00e6d6d0(cCell* c)
{
    float r = 0.7f;
    if (c->mKey.a != 0 && !FUN_00e6d680(c)) {
        switch (FUN_00e516c0(c)) {
        case 0: r = -0.7f; break;
        case 1: r = 0.0f; break;
        case 3: r = 1.4f; break;
        case 4: r = 2.1f; break;
        case 5: r = 2.8f; break;
        }
    }
    return r;
}

// fwd
int FUN_00e6cbd0(int handle, int a2, unsigned a3, int* outA, int* outB);

// @ 0x00e6d180
void FUN_00e6d180(cCell* c, int a2, int a3, int* out4, float* out5, int* out6, int* out7)
{
    float f;
    int r = FUN_00e6cbd0(c->mHandle, a2, (unsigned)a3, out6, out7);
    *out4 = r;
    if (c->mPoolHandle == 0) {
        *out5 = 1.0f;
        return;
    }
    EffectObj* obj;
    {
        ObjectPool& pool = gspCellGfx->mEffects;
        obj = (EffectObj*)pool.Get(c->mPoolHandle);
    }
    f = obj->FUN_00e4f040(r);
    *out5 = f;
}

// @ 0x00e6d200
float FUN_00e6d200(cCell* c, int a2, int a3, int a4)
{
    if (c->mKey.a == 0 || c->mPoolHandle == 0)
        return 1.0f;

    int local_4;
    float local_10;
    int local_8;
    bool bFlag;
    FUN_00e6d180(c, a2, a3, &local_4, &local_10, &local_8, (int*)&bFlag);

    float local_c = 0.2f;
    float local_14 = 0.2f;
    if (a4 == 0x32 || a4 == 0x33)
        local_14 = 0.7f;
    if (a4 == 0x2f || a4 == 0x2b || a4 == 0x2c)
        local_14 = 0.0f;
    if (a3 == 0x2f)
        local_c = 0.0f;

    if (bFlag) {
        float s = FUN_00e563e0(c);
        local_10 = local_10 * s;
        local_c = local_c * s;
        local_14 = local_14 * s;
    }

    EffectObj* obj;
    {
        ObjectPool& pool = gspCellGfx->mEffects;
        obj = (EffectObj*)pool.Get(c->mPoolHandle);
    }
    obj->FUN_00e4f330(local_4, local_10, local_c, local_14, local_8);

    if (local_8)
        c->mState2 = a3;
    c->mState1 = a3;
    c->mTimer = local_10;
    return local_10;
}

// @ 0x00e6d340
namespace SP {
void CellUpdateAnimation(cCell* c, int a2, float dt)
{
    if (c->mFlag1ac != 0 && c->mPoolHandle != 0) {
        ObjectPool& pool = gspCellGfx->mEffects;
        EffectObj* o = (EffectObj*)pool.Get(c->mPoolHandle);
        o->FUN_00e4f100(0xaaaa0066, 1.6f, 0, -1);
    }
    if (c->mPoolHandle != 0) {
        ObjectPool& pool = gspCellGfx->mEffects;
        EffectObj* o = (EffectObj*)pool.Get(c->mPoolHandle);
        if (c->mFlag390 != 0) {
            o->FUN_00e4f100(0xaaaa0101, 0.0f, 1, -1);
            o->FUN_00e4f100(0xaaaa0103, 0.0f, 1, -1);
            o->FUN_00e4f100(0xaaaa0105, 0.0f, 1, -1);
        }
        if (c->mFlag391 != 0) {
            o->FUN_00e4f100(0xaaaa0100, 0.0f, 1, -1);
            o->FUN_00e4f100(0xaaaa0102, 0.0f, 1, -1);
            o->FUN_00e4f100(0xaaaa0104, 0.0f, 1, -1);
        }
    }
    if (c->mState0 != c->mState1) {
        FUN_00e6d200(c, a2, c->mState0, c->mState1);
        return;
    }
    float t = c->mTimer - dt;
    c->mTimer = t;
    if (t > 0.0f)
        return;
    FUN_00e6d200(c, a2, c->mState2, c->mState1);
}
}

// @ 0x00e6d4a0
void FUN_00e6d4a0(int* key, int* outA, int* outB)
{
    if (gspCellGame->mByte4121 == 1) {
        CellInfo* info = FindCellInfo(*(CellKey*)key);
        *outA = info->mField1288;
        *outB = info->mField1284;
        return;
    }
    char buf[0x1290];
    FUN_00e83e30(buf, buf + 4, key);
    FUN_00e52060(buf, 1, (int*)0);
    *outA = *(int*)(buf + 0x128c);
    *outB = *(int*)(buf + 0x1288);
}

// @ 0x00e6d560
void FUN_00e6d560()
{
    IContext* p = FUN_0067de90(0, 1)->FUN_007ec160();
    p->FUN_007eb820(3);
    p->mOut[0] = gspCellGame->mpLevelInfo->mField74;
    p->mOut[1] = gspCellGame->mpLevelInfo->mField1c;
    cCell* c = (cCell*)gspCellGame->mCells.GetChecked(gspCellGame->mHandle411c);
    if (c == 0) {
        p->mOut[2] = (int)c;
        return;
    }
    CellInfo* info = FindCellInfo(c->mKey);
    p->mOut[2] = *(int*)info;
}

// @ 0x00e6d600
void FUN_00e6d600()
{
    IContext* p = FUN_0067de90(0, 5)->FUN_007ec160();
    p->FUN_007eb820(2);
    p->mOut[0] = gspCellGame->mpLevelInfo->mField74;
    cCell* c = (cCell*)gspCellGame->mCells.GetChecked(gspCellGame->mHandle411c);
    if (c == 0) {
        p->mOut[1] = (int)c;
        return;
    }
    CellInfo* info = FindCellInfo(c->mKey);
    p->mOut[1] = *(int*)info;
}

// @ 0x00e6d790
void FUN_00e6d790(cCell* c, Vector3* center, float* radius)
{
    if (c->mPoolHandle == 0) {
        center->x = c->mPosition.x;
        center->y = c->mPosition.y;
        center->z = c->mPosition.z;
        *radius = c->mRadius;
        return;
    }
    CellInfo* info = FindCellInfo(c->mKey);
    *radius = info->mScale1244 * c->mRadius;
    center->x = info->mVec1238.x;
    center->y = info->mVec1238.y;
    center->z = info->mVec1238.z;
    if (c->mFlags & 2) {
        Vector3 v = *center;
        *center = v * c->mOrient;
    }
    center->x = center->x * c->mRadius;
    center->y = center->y * c->mRadius;
    center->z = center->z * c->mRadius;
    center->x = center->x + c->mPosition.x;
    center->y = center->y + c->mPosition.y;
    center->z = center->z + c->mPosition.z;
}

// @ 0x00e6dae0
void FUN_00e6dae0(cCell* c)
{
    if (c->mObstacle == -1)
        return;
    Vector3 center;
    float radius;
    FUN_00e6d790(c, &center, &radius);
    float vmaxx = center.x + radius;
    float vmaxy = center.y + radius;
    float vminx = center.x - radius;
    float vminy = center.y - radius;
    MoveObstacle(gspCellGame->mObstacleGrid, c->mObstacle, &vminx, &vmaxx);
    (void)vmaxy; (void)vminy;
}

// @ 0x00e6d8f0
void FUN_00e6d8f0(int handle, int a2)
{
    cCell* cell = (cCell*)gspCellGame->mCells.Get(handle);
    int it1[4];
    FUN_00743b50(it1);
    int* p1 = FUN_00e823a0(cell->mType, it1);
    int it2[4];
    FUN_00743b50(it2);
    FUN_00e823a0(*p1, it2);

    int k;
    if (cell->mRadius >= 2.0f) k = 3;
    else if (cell->mRadius >= 1.0f) k = 2;
    else if (cell->mRadius >= 0.3f) k = 1;
    else k = 0;
    cell->mAnimIdx = k;

    if (k == 0 || cell->mEffectGroup != gspCellGame->mSel40fc ||
        p1[0x2d] == 0 || p1[0x2d] == 5) {
        cell->mAnimCount = 1;
        cell->mAnimData = -1;
    } else {
        int* p = (int*)&cell->mAnimData;
        FUN_00e5cb60(&gCellSpawnTableTag, &p, &cell->mFlags, &cell->mVelocity, handle, k, 0);
        cell->mAnimCount = (int)(p - (int*)&cell->mAnimData) >> 2;
    }

    int grp = cell->mEffectGroup;
    int cmp = gspCellGame->mSel40fc;
    int h = gspCellGfx->mEffects.Alloc();
    cell->mPoolHandle = h;
    EffectObj* obj = (EffectObj*)gspCellGfx->mEffects.Get(h);
    FUN_00e5ce90(obj, cell->mKey.a, (grp != cmp), *p1, a2, cell->mKey);

    cCell* c2 = (cCell*)gspCellGame->mCells.Get(handle);
    FUN_00e6d200(c2, 0, 0, c2->mState1);

    if (cell->mEffectGroup == gspCellGame->mSel4100 && gspCellGfx->mField16254 < 0x10)
        FUN_00e51930();

    FUN_00e82130(it2);
    FUN_00e82130(it1);
}

// @ 0x00e6cbd0
int FUN_00e6cbd0(int handle, int a2, unsigned a3, int* outA, int* outB)
{
    float total = 0.0f;
    unsigned mismatch = (unsigned)(gspCellGame->mHandle411c != handle);
    int picked[131];
    int n = 0;

    for (int i = 0; i < 131; i++) {
        CellSpawn& e = gCellSpawns[i];
        if (e.f0 == (int)a3 && (e.flag == (int)mismatch || e.flag == 2)) {
            int v = e.type;
            if (v != 1) {
                cCell* cell = (cCell*)gspCellGame->mCells.Get(handle);
                if (cell->mPoolHandle != 0) {
                    CellInfo* info = FindCellInfo(cell->mKey);
                    int* q = (int*)info;
                    int cnt = *q;
                    for (int j = 0; j < cnt; j++) {
                        if (q[2 + j * 0x12] == (unsigned)v)
                            goto check;
                    }
                }
                continue;
            }
        check:
            if (FUN_00e5c460(handle, e.f6) && FUN_00e5c410(handle, e.f7)) {
                total = total + e.weight;
                picked[n++] = i;
            }
        }
    }

    if (total != 0.0f) {
        float rr = (float)gMathRandom.RandomDoubleUniform() * total;
        if (rr < 0.0f)
            rr = 0.0f;
        for (int i = 0; i < n; i++) {
            int idx = picked[i];
            rr = rr - gCellSpawns[idx].weight;
            if (rr <= 0.0f) {
                *outA = gCellSpawns[idx].outA;
                *outB = gCellSpawns[idx].outB;
                return gCellSpawns[idx].f1;
            }
        }
    }
    *outA = 0;
    return 0;
}
