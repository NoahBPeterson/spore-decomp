// Slice s00e6f850 -- SP cell TU: per-mode cell steering / look-at helpers.
// 0x00e70650 orients a cell toward the avatar cell; the 0x00e6f850.. block routes a cell toward a
// target record (record view selection, find-cell filtering, collision-cylinder avoidance).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU; no /EHsc).
#include "types.h"
#include <math.h>
typedef uint32_t uint32;

struct cObjectPool {
    void* GetSafe(int index);                 // 0x00b721d0 (thiscall, ret 4)
    void* Get(int index);                     // 0x00b72210 (thiscall, ret 4)
};

struct cLevelInfo {
    char pad0[0x7c];
    int  mMode;                               // +0x7c (view selector)
};

struct cGameStub {                            // gspCellGame (only the fields this TU touches)
    char pad0[0x1c];
    cObjectPool mCells;                       // +0x1c
    char pad1[0x40fc - 0x1d];
    void* mpWorld;                            // +0x40fc collision world for collectCylinder
    char pad2[0x411c - 0x4100];
    int mAvatarCellIndex;                     // +0x411c
    char pad3[0x5190 - 0x4120];
    cLevelInfo* mpLevelInfo;                  // +0x5190
};
extern cGameStub* gspCellGame;                // 0x016b3c04

struct cEntity {
    int   mIndex;                             // +0x00
    unsigned char mDone;                      // +0x04
    char  pad05[3];
    float mPosA;                              // +0x08
    float mPosB;                              // +0x0c
    float mPosC;                              // +0x10
    float mQuat[4];                           // +0x14..+0x20
    char  pad24[0x4c - 0x24];
    float mX;                                 // +0x4c (target position x)
    float mY;                                 // +0x50
    float mZ;                                 // +0x54
    float mScale;                             // +0x58
    char  pad5c[0x108 - 0x5c];
    uint32 field_108;                         // +0x108 (record key)
    char  pad10c[0x174 - 0x10c];
    int   field174;                           // +0x174
    char  pad178[0x1c4 - 0x178];
    float mAccumX;                            // +0x1c4
    float mAccumY;                            // +0x1c8
    float mAccumZ;                            // +0x1cc
    char  pad1d0[0x1dc - 0x1d0];
    int   mHandle1dc;                         // +0x1dc (orbit target handle)
    char  pad1e0[0x1e4 - 0x1e0];
    int   mState1e4;                          // +0x1e4 (mode selector)
    int   mHandle1e8;                         // +0x1e8 (chase target handle)
    float mTimer1ec;                          // +0x1ec
    char  pad1f0[0x1f8 - 0x1f0];
    float mTimer1f8;                          // +0x1f8
    float mAnchorX;                           // +0x1fc
    float mAnchorY;                           // +0x200
    float mAnchorZ;                           // +0x204
    char  pad208[0x23c - 0x208];
    float mTimer23c;                          // +0x23c
    char  pad240[0x358 - 0x240];
    int   mLevel;                             // +0x358
    int   mSrcLevel;                          // +0x35c
};

struct CellRecord {                           // one selectable view inside a record base
    int   id;                                 // +0x00
    float radius;                             // +0x04
    char  pad08[0x10 - 0x08];
    uint32 field10;                           // +0x10 (hash override)
    char  pad14[0x18 - 0x14];
    float f18;                                // +0x18
    char  pad1c[0x40 - 0x1c];
    float f40;                                // +0x40
    unsigned char flag44;                     // +0x44
    char  pad45[3];
};

struct CellRecordBase {
    char pad000[0xe0];
    CellRecord def;                           // +0xe0 (fallback view)
    char pad128[0x194 - 0x128];
    CellRecord mode2;                         // +0x194 (mode 2 view)
    char pad1dc[0x248 - 0x1dc];
    CellRecord mode0;                         // +0x248 (mode 0 view)
};

struct cHandleRef {                           // 4-byte handle holder (ctor 0x00743b50, dtor 0x00e82130)
    int mp;
    cHandleRef();                             // 0x00743b50
    ~cHandleRef();                            // 0x00e82130
};

extern const float kCellUp[3];                // 0x015a7c40 (0,0,1)
extern const float kAxisY[3];                 // 0x015a7c34 (0,1,0)
extern const float kTen;                      // 0x01473c70 10.0f
extern const float kTwo;                      // 0x01470f1c 2.0f
extern const float kHalf;                     // 0x01471064 0.5f
extern const float kSix;                      // 0x0147b9f0 6.0f
extern const float kOne;                      // 0x01485720 1.0f
extern const float kOneAndHalf;               // 0x01485548 1.5f
extern const float kZero;                     // 0x01485378 0.0f
extern const float kTwoAndHalf;               // 0x01486114 2.5f
extern const float kPointTwo;                 // 0x013ec480 0.2f
extern const float kEpsilon;                  // 0x013ec4b8 1e-8f
extern const float kQuarter;                  // 0x013eb8a0 0.25f
extern const float kSignMask;                 // 0x013eb8b0
extern const float k36;                       // 0x01485af0 36.0f
extern const float kAnchorRadius;             // 0x015a8540 20.0f
extern const float kAvatarRadius;             // 0x015a8544 5.0f

namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    uint32 mnSeed;
    double RandomDoubleUniform();             // 0x009360d0 (thiscall)
};
} }
extern EA::Random::RandomLinearCongruential sMathRandom;   // 0x01601760

// ---------------------------------------------------------------- callees
CellRecordBase* GetCellKey(uint32 value, cHandleRef* tmp);              // 0x00e4cc40 (cdecl)
CellRecord* GetCellRecord(CellRecordBase* base);                        // 0x00e52910 (cdecl)
uint32 FUN_00e67c40(cEntity* self, CellRecordBase* base);               // 0x00e67c40 (cdecl)
void   StepCell(cEntity* self, float dt, float f18, float f40, uint32 hash, int mode); // 0x00e6eec0 (self in ESI)
void   FUN_00e6eec0(float dt, float f18, float f40, uint32 hash, int mode);           // 0x00e6eec0 (self already in ESI)
void   FUN_00e6f660(cEntity* self, const float* pos, float dt, float f18, float f40,
                    uint32 hash, int mode, unsigned char last);         // 0x00e6f660 (cdecl, 8 args)
void   FUN_00e6f800(cEntity* self, uint32 handle, float dt, float f18, float f40,
                    uint32 hash, int mode, unsigned char last);         // 0x00e6f800 (cdecl, 8 args)
float* FUN_00e5eb20(float* out, cEntity* cell);                         // 0x00e5eb20
unsigned FUN_00e56e50(int want, int slot, int srcLevel, float* pos, float radius); // 0x00e56e50
bool   FUN_00e56dc0(int* ids, int count, int skip, unsigned char flag); // 0x00e56dc0
int    FUN_00e87360(void* world, const float* a, const float* dir, float r1, float r2,
                    int* out, int max);                                 // 0x00e87360 collectCylinder
float* FUN_0059aed0(float* out, const float* v, const float* q);        // 0x0059aed0
void   RandomDirection3(float* out);                                   // 0x00b7e560
float* Vector3_Normalize(float* out, const float* in);                  // 0x00436ce0
float* QuaternionFromFacingAndUp(float* out, const float* facing, const float* up); // 0x0069b600

// ---------------------------------------------------------------- 0x00e6f850
// @ 0x00e6f850
void FUN_00e6f850(cEntity* cell, const float* p, float f18, float f40, uint32 hash, int last,
                  float dt)
{
    float dy = p[1] - cell->mY;
    float dx = p[0] - cell->mX;
    float dz = p[2] - cell->mZ;
    float inv = 1.0f / sqrtf(dy * dy + dx * dx + dz * dz + kEpsilon);
    float tx = inv * dx;
    float ty = inv * dy;
    float tz = inv * dz;
    float target[3];
    target[0] = cell->mX - tx * kTen;
    target[1] = cell->mY - ty * kTen;
    target[2] = cell->mZ - tz * kTen;
    FUN_00e6f660(cell, target, dt, f18, f40, hash, 2, (unsigned char)last);
}

// ---------------------------------------------------------------- 0x00e6f940
// @ 0x00e6f940
void FUN_00e6f940(cEntity* cell, uint32 handle, float f18, float f40, uint32 hash, int last,
                  float dt)
{
    cObjectPool& cells = gspCellGame->mCells;
    cEntity* other = (cEntity*)cells.Get((int)handle);
    FUN_00e6f850(cell, &other->mX, f18, f40, hash, last, dt);
}

// ---------------------------------------------------------------- 0x00e6f990
// @ 0x00e6f990
void FUN_00e6f990(cEntity* cell, float dt)
{
    cHandleRef ref;
    CellRecordBase* base = GetCellKey(cell->field_108, &ref);

    CellRecord* view;
    switch (gspCellGame->mpLevelInfo->mMode) {
    case 0:
        view = &base->mode0;
        if (view->id == -1)
            view = &base->def;
        break;
    case 2:
        view = &base->mode2;
        if (view->id == -1)
            view = &base->def;
        break;
    case 1:
    default:
        view = &base->def;
        break;
    }

    int lvl = cell->mLevel - 1;
    int hi = 0x13;
    int zero = 0;
    int* p = (lvl < 0) ? &zero : &lvl;
    if (*p > 0x13)
        p = &hi;

    int sel = *p;
    unsigned idx = FUN_00e56e50(3, sel, cell->mSrcLevel, &cell->mX, view->radius);
    if (idx != 0) {
        float f18 = GetCellRecord(base)->f18;
        float f40 = GetCellRecord(base)->f40;
        uint32 hash = FUN_00e67c40(cell, base);
        unsigned char extra = GetCellRecord(base)->flag44;
        cEntity* other = (cEntity*)gspCellGame->mCells.Get((int)idx);
        FUN_00e6f660(cell, &other->mX, dt, f18, f40, hash, 0, extra);
        return;
    }

    cEntity* av = (cEntity*)gspCellGame->mCells.GetSafe(gspCellGame->mAvatarCellIndex);
    if (av) {
        float pos[3];
        FUN_00e5eb20(pos, av);
        float s = av->mScale;
        float x = pos[0] * s * kTwo + av->mX;
        float y = av->mY + pos[1] * s * kTwo;
        float z = av->mZ + pos[2] * s * kTwo;
        pos[0] = x;
        pos[1] = y;
        pos[2] = z;
        FUN_00e6f660(cell, pos, dt,
                     GetCellRecord(base)->f18, GetCellRecord(base)->f40,
                     FUN_00e67c40(cell, base), 0, GetCellRecord(base)->flag44);
    }
}

// ---------------------------------------------------------------- 0x00e6fbb0
// @ 0x00e6fbb0
void FUN_00e6fbb0(cEntity* cell, float dt)
{
    cHandleRef ref;
    CellRecordBase* base = GetCellKey(cell->field_108, &ref);

    if (cell->mState1e4 != 1) {
        FUN_00e6eec0(dt, GetCellRecord(base)->f18, GetCellRecord(base)->f40,
                 FUN_00e67c40(cell, base), 0);
        return;
    }

    int lvl = cell->mLevel + 1;
    int hi = 0x13;
    int zero = 0;
    int* p = (lvl < 0) ? &zero : &lvl;
    if (*p > 0x13)
        p = &hi;

    int sel = *p;
    CellRecord* view = GetCellRecord(base);
    unsigned idx = FUN_00e56e50(3, sel, cell->mSrcLevel, &cell->mX, view->radius);
    if (idx != 0) {
        FUN_00e6f800(cell, idx, dt,
                     GetCellRecord(base)->f18, GetCellRecord(base)->f40,
                     FUN_00e67c40(cell, base), 0, GetCellRecord(base)->flag44);
    }
}

// ---------------------------------------------------------------- 0x00e6fce0
// @ 0x00e6fce0
void FUN_00e6fce0(cEntity* cell, float dt)
{
    if (0.0f >= cell->mTimer1f8)
        return;

    cHandleRef ref;
    CellRecordBase* base = GetCellKey(cell->field_108, &ref);
    cell->mTimer1f8 = cell->mTimer1f8 - dt;
    FUN_00e6eec0(dt, GetCellRecord(base)->f18, GetCellRecord(base)->f40,
                 FUN_00e67c40(cell, base), 0);
}

// ---------------------------------------------------------------- 0x00e6fd70
// @ 0x00e6fd70
void FUN_00e6fd70(cEntity* cell, float dt)
{
    cHandleRef ref;
    CellRecordBase* base = GetCellKey(cell->field_108, &ref);

    cEntity* av = (cEntity*)gspCellGame->mCells.GetSafe(gspCellGame->mAvatarCellIndex);
    bool near = false;
    if (av) {
        float dy = cell->mY - av->mY;
        float dz = cell->mZ - av->mZ;
        float dx = cell->mX - av->mX;
        float d2 = dy * dy + dz * dz + dx * dx;
        if (d2 <= kAvatarRadius * kAvatarRadius) {
            near = true;
        } else {
            float ddz = av->mZ - cell->mAnchorZ;
            float ddy = av->mY - cell->mAnchorY;
            float ddx = av->mX - cell->mAnchorX;
            float d2b = ddz * ddz + ddy * ddy + ddx * ddx;
            if (d2b <= kAnchorRadius * kAnchorRadius)
                near = true;
        }
    }

    if (near) {
        float f18 = GetCellRecord(base)->f18;
        float f40 = GetCellRecord(base)->f40;
        uint32 hash = FUN_00e67c40(cell, base);
        unsigned char extra = GetCellRecord(base)->flag44;
        cEntity* other = (cEntity*)gspCellGame->mCells.Get(av->mIndex);
        FUN_00e6f660(cell, &other->mX, dt, f18, f40, hash, 0, extra);
    } else {
        FUN_00e6f660(cell, &cell->mAnchorX, dt,
                     GetCellRecord(base)->f18, GetCellRecord(base)->f40,
                     FUN_00e67c40(cell, base), 0, GetCellRecord(base)->flag44);
    }
}

// ---------------------------------------------------------------- 0x00e6ff60
// @ 0x00e6ff60
void FUN_00e6ff60(cEntity* cell, float a2, float a3, uint32 a4, unsigned char a5, float dt)
{
    float t = cell->mTimer23c - dt;
    cell->mTimer23c = t;
    if (t > kZero) {
        FUN_00e6eec0(dt, a2, a3, a4, 0);
        return;
    }

    double r = sMathRandom.RandomDoubleUniform() * 0.0625;
    if (r >= 0.0625)
        r = 0.0625;
    else if (r < 0.0)
        r = 0.0;
    cell->mTimer23c = (float)(r + kQuarter);

    float dir[3];
    float base[3];
    base[0] = -kAxisY[0];
    base[1] = -kAxisY[1];
    base[2] = -kAxisY[2];
    FUN_0059aed0(dir, base, cell->mQuat);
    dir[2] = kZero;

    int ids[0x200];
    int count = FUN_00e87360(gspCellGame->mpWorld, &cell->mX, dir, kOneAndHalf, cell->mScale,
                             ids, 0x200);
    int i = 0;
    if (count > 1) {
        do {
            if (i >= 10)
                break;
            if (FUN_00e56dc0(ids, count, gspCellGame->mAvatarCellIndex, a5))
                break;
            float rnd[3];
            RandomDirection3(rnd);
            float inv = 1.0f / sqrtf(rnd[1] * rnd[1] + rnd[0] * rnd[0] + kEpsilon);
            dir[0] = rnd[0] * inv;
            dir[1] = rnd[1] * inv;
            dir[2] = kZero;
            count = FUN_00e87360(gspCellGame->mpWorld, &cell->mX, dir, kOneAndHalf, cell->mScale,
                                 ids, 0x200);
            ++i;
        } while (count > 1);
        if (i == 10) {
            cell->mPosA = cell->mX;
            cell->mPosB = cell->mY;
            cell->mPosC = cell->mZ;
            cell->mDone = 1;
            FUN_00e6eec0(dt, a2, a3, a4, 0);
            return;
        }
    }

    if (cell->field174 == 0) {
        float neg[3];
        neg[0] = -dir[0];
        neg[1] = -dir[1];
        neg[2] = -dir[2];
        float q[4];
        QuaternionFromFacingAndUp(q, neg, kCellUp);
        cell->mQuat[0] = q[0];
        cell->mQuat[1] = q[1];
        cell->mQuat[2] = q[2];
        cell->mQuat[3] = q[3];
    }
    cell->mPosA = cell->mX + dir[0] * kTen;
    cell->mPosB = cell->mY + dir[1] * kTen;
    cell->mPosC = cell->mZ + dir[2] * kTen;
    cell->mDone = 0;
    FUN_00e6eec0(dt, a2, a3, a4, 0);
}

// ---------------------------------------------------------------- 0x00e702d0
// @ 0x00e702d0
void FUN_00e702d0(cEntity* cell, CellRecordBase* other, float dt)
{
    if (cell->mTimer1ec > kZero) {
        cell->mTimer1ec = cell->mTimer1ec - dt;
        return;
    }

    cEntity* target = (cEntity*)gspCellGame->mCells.GetSafe(cell->mHandle1e8);
    if (!target)
        return;

    float dx = cell->mX - target->mX;
    float dy = cell->mY - target->mY;
    float dz = cell->mZ - target->mZ;
    float dist = sqrtf(dz * dz + dy * dy + dx * dx);
    if (dist > kPointTwo) {
        cell->mPosA = target->mX;
        cell->mPosB = target->mY;
        cell->mPosC = target->mZ;
        cell->mDone = 0;
        FUN_00e6eec0(dt, kOneAndHalf, kOne, FUN_00e67c40(cell, other), 0);
        return;
    }

    cEntity* av = (cEntity*)gspCellGame->mCells.GetSafe(gspCellGame->mAvatarCellIndex);
    if (!av)
        return;
    float delta[3];
    delta[0] = av->mX - cell->mX;
    delta[1] = av->mY - cell->mY;
    delta[2] = av->mZ - cell->mZ;
    float d2 = delta[2] * delta[2] + delta[1] * delta[1] + delta[0] * delta[0];
    if (d2 > k36)
        return;

    cell->mDone = 1;
    float n[3];
    Vector3_Normalize(n, delta);
    float inv = kOne / dt;
    cell->mAccumX = cell->mAccumX + n[0] * kSix * inv;
    cell->mAccumY = cell->mAccumY + n[1] * kSix * inv;
    cell->mAccumZ = cell->mAccumZ + n[2] * kSix * inv;
    cell->mTimer1ec = kOne;
}

// ---------------------------------------------------------------- 0x00e704b0
// @ 0x00e704b0
void FUN_00e704b0(cEntity* cell, CellRecordBase* other, float dt)
{
    cEntity* target = (cEntity*)gspCellGame->mCells.GetSafe(cell->mHandle1dc);
    if (!target)
        return;

    float angle = dt * kTwoAndHalf;
    float s = sinf(angle);
    float c = cosf(angle);
    float q[4];
    q[0] = kCellUp[0] * s;
    q[1] = kCellUp[1] * s;
    q[2] = kCellUp[2] * s;
    q[3] = c;

    float delta[3];
    delta[0] = cell->mX - target->mX;
    delta[1] = cell->mY - target->mY;
    delta[2] = cell->mZ - target->mZ;
    float rot[3];
    FUN_0059aed0(rot, delta, q);

    float inv = kOne / sqrtf(rot[2] * rot[2] + rot[1] * rot[1] + rot[0] * rot[0]);
    cell->mPosA = target->mX + rot[0] * inv * kTwo;
    cell->mPosB = target->mY + rot[1] * inv * kTwo;
    cell->mPosC = target->mZ + rot[2] * inv * kTwo;
    cell->mDone = 0;
    FUN_00e6eec0(dt, kHalf, kOne, FUN_00e67c40(cell, other), 0);
}

// ---------------------------------------------------------------- 0x00e70650
// @ 0x00e70650
static void OrientToAvatar(cEntity* self, float p)   // self in EAX
{
    cEntity* av = (cEntity*)gspCellGame->mCells.GetSafe(gspCellGame->mAvatarCellIndex);
    if (av) {
        cHandleRef tmp;
        CellRecordBase* R = GetCellKey(self->field_108, &tmp);
        float dx = av->mX - self->mX;
        float dy = av->mY - self->mY;
        float dz = av->mZ - self->mZ;
        const CellRecord* rec = GetCellRecord(R);
        float d2 = (dy * dy + dx * dx) + dz * dz;
        if (d2 <= rec->radius * rec->radius) {
            float inv = (float)(1.0 / sqrt((double)d2));
            float facing[3] = { -(inv * dx), -(inv * dy), -(inv * dz) };
            float out[4];
            const float* q = QuaternionFromFacingAndUp(out, facing, kCellUp);
            self->mQuat[0] = q[0];
            self->mQuat[1] = q[1];
            self->mQuat[2] = q[2];
            self->mQuat[3] = q[3];
            self->mPosA = av->mX;
            self->mPosB = av->mY;
            self->mPosC = av->mZ;
            self->mDone = 0;
            uint32 X = FUN_00e67c40(self, R);
            FUN_00e6eec0(p, GetCellRecord(R)->f18, GetCellRecord(R)->f40, X, 0);
        }
    }
}

// Stand-in caller so the static helper is emitted with its register convention.
void OrientToAvatarEntry(cEntity* self, float p)
{
    OrientToAvatar(self, p);
}
