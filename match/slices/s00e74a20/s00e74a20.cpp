// Slice s00e74a20 -- cell stage: SP::sCreateCell-style factory. Allocates a cCell from the cell game's
// object pool, derives its pose / orientation / mass from the cell definition, registers its collision
// proxy with the physics world and picks the per-level behaviour record.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU; no /EHsc: the resource-ref local gets no EH frame)
#include "types.h"

#pragma intrinsic(sin, cos)
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);

typedef uint16_t uint16;
typedef uint8_t uint8;

// ---------------------------------------------------------------- math
struct Vector3 {                          // POD: struct copies go through integer registers
    float x, y, z;
};
struct Vector3f {                         // copies per float (movss)
    float x, y, z;
    Vector3f() {}
    Vector3f(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct Quat {
    Vector3 v;
    float w;
};
struct Matrix3 { float m[9]; };

extern const Vector3 kUnitZ;              // 015a7c40
extern const Quat kQuatIdentity;          // 015a7c4c
extern const Vector3 kVec3Zero;           // 016b3c28
extern const Matrix3 kMatrix3Identity;    // 016b3dac
extern float kTwoPi;                      // 016b3dd0 (runtime-initialised)
extern const float kLevelSize[];          // 01483bd0: 10, 30, 100, 300, ...

struct RandomLinearCongruential { double RandomDoubleUniform(); };    // 009360d0
extern RandomLinearCongruential sMathRandom;                          // 01601760

struct cSPTransform {                     // 0x38 bytes
    uint16 mFlags;                        // +0x00
    uint16 mModificationCount;            // +0x02
    Vector3 mTranslation;                 // +0x04
    float mScale;                         // +0x10
    Matrix3 mRotation;                    // +0x14
};

// ---------------------------------------------------------------- the cell
struct cCell {
    int mIndex;                           // +0x000 (pool handle)
    uint8 mActive; uint8 pad005[3];       // +0x004
    Vector3 mPosition;                    // +0x008
    Quat mOrientation;                    // +0x014
    uint32_t pad024[(0x48 - 0x24) / 4];
    cSPTransform mTransform;              // +0x048
    float mRelativeElevation;             // +0x080
    uint32_t pad084[3];
    Vector3 mVelocity;                    // +0x090
    uint32_t pad09c;
    float mOpacity;                       // +0x0a0
    float mField0a4;                      // +0x0a4
    float mField0a8;                      // +0x0a8
    float mField0ac;                      // +0x0ac
    uint32_t pad0b0;
    float mSize;                          // +0x0b4
    float mMass;                          // +0x0b8
    float mInvMass;                       // +0x0bc
    cSPTransform mVisualTransform;        // +0x0c0
    uint32_t pad0f8;
    Vector3 mModelKey;                    // +0x0fc (ResourceKey: instance, type, group)
    int mDefId;                           // +0x108
    int mField10c;
    uint8 mByte110, mByte111, mByte112, mByte113;
    uint32_t pad114;
    int mField118;
    int mField11c;
    int mField120;
    int mField124;
    int mField128;
    Vector3f mField12c;
    Vector3 mField138;
    int mField144;
    uint32_t pad148;
    int mField14c;
    float mField150;
    uint32_t pad154;
    float mField158;                      // +0x158 (written by FUN_00e6cad0)
    float mField15c;                      // +0x15c
    uint32_t pad160[(0x1c0 - 0x160) / 4];
    float mField1c0;
    uint32_t pad1c4[3];
    float mField1d0;
    uint32_t pad1d4[(0x1fc - 0x1d4) / 4];
    Vector3 mField1fc;
    uint32_t pad208[(0x234 - 0x208) / 4];
    float mField234;
    uint32_t pad238[(0x244 - 0x238) / 4];
    int mField244;
    int mField248, mField24c, mField250;
    uint32_t pad254[(0x354 - 0x254) / 4];
    uint8 mByte354; uint8 pad355[3];
    int mField358;                        // +0x358 level index
    int mField35c;                        // +0x35c group
    int mField360;                        // +0x360 handle from FUN_00e868f0
    int mField364;                        // +0x364 collision proxy
    float mField368;
    int mField36c;
    int mField370;
    float mField374;
};

// Per-level behaviour record in the cell definition (stride 0xb4, at def+0xe0 / +0x194 / +0x248).
struct cLevelInfo {
    int mType;                            // +0x00 (-1 = absent)
    uint32_t pad04[(0x48 - 0x04) / 4];
    float mLimit;                         // +0x48
    uint32_t pad4c[(0xb4 - 0x4c) / 4];
};
struct cCellDef {                         // resolved by FUN_00e823a0
    uint32_t pad00[0xac / 4];
    uint8 mSpecial; uint8 padad[3];       // +0xac
    uint32_t padb0;
    int mKind;                            // +0xb4
    uint32_t padb8[(0xe0 - 0xb8) / 4];
    cLevelInfo mLevels[3];                // +0xe0, +0x194, +0x248
    uint32_t pad2fc[(0x304 - 0x2fc) / 4];
    uint32_t mField304;
};

// Resource reference holder (ctor 00743b50, dtor 00e82130).
struct cDefRef {
    cDefRef();
    ~cDefRef();
    void* mp;
};

struct cObjectPool {                      // cSPObjectPoolT<cCell>
    int New();                            // 00b72160
    cCell* Get(int index);                // 00b72210
};

struct cCellSerializableData { uint32_t pad[0x7c / 4]; int mStage; };   // +0x7c

struct cCellGame {
    uint32_t pad0000[0x1c / 4];
    cObjectPool mCells;                   // +0x001c
    uint32_t pad0020[(0x40fc - 0x20) / 4];
    int midPlayerCell;                    // +0x40fc
    int mGroup4100;                       // +0x4100
    void* mpPhysics;                      // +0x4104
    uint32_t pad4108[(0x514c - 0x4108) / 4];
    float mField514c;                     // +0x514c
    uint32_t pad5150[(0x5190 - 0x5150) / 4];
    cCellSerializableData* mpSerializableData;   // +0x5190
};
extern cCellGame* gspCellGame;            // 016b3c04

// ---------------------------------------------------------------- callees
cCellDef* GetCellDef(int defId, cDefRef* ref);                 // 00e4cc40 -> 00e823a0
float FUN_004df2d0(const void* p);                             // 004df2d0 (cdecl, x87 return)
float FUN_00e4f9d0(int defId);                                 // 00e4f9d0 (static in the cell TU: xmm0 return)
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quat* q);   // 0059c190
Vector3* FUN_00e5eb20(Vector3* out, cCell* c);                 // 00e5eb20
Vector3* FUN_00e65640(Vector3* out, int defId);                // 00e65640
void FUN_00e6cad0(cCellDef* def, Vector3 key, float* a, float* b);   // 00e6cad0
void FUN_00e6d790(cCell* c, Vector3* center, float* radius);   // 00e6d790 (esi = cell, edi = center, [esp+4] = radius)
int FUN_00e868f0(int group, Vector3* center, float radius, int index);   // 00e868f0
int FUN_00bbbdd0(void* physics, int index, const float* lo, const float* hi, int filter);   // 00bbbdd0 (thunk to 00bbb120)

union P8 { uint8 flag; float radius; };

// @ 0x00e74a20
int __cdecl CreateCell(int group, const Vector3* pos, float elevation, int defId, int level,
                       float sizeScale, float size, P8 radiusOrFlag, const Quat* orient, int filter)
{
    cCellDef* def;
    cDefRef ref;
    def = GetCellDef(defId, &ref);

    if (size == 0.0f) {
        float scale;
        if (level != -1)
            scale = kLevelSize[level] * 0.033333335f;
        else
            scale = 1.0f;
        size = scale / gspCellGame->mField514c * FUN_004df2d0(&def->mField304) * sizeScale;
    } else {
        size = sizeScale * size;
    }

    int id = gspCellGame->mCells.New();
    cCell* cell = gspCellGame->mCells.Get(id);
    cell->mActive = 1;
    cell->mPosition = *pos;
    cell->mField1d0 = 0.0f;

    int zero = 0;
    if (def->mSpecial == 1) {
        cell->mOrientation = kQuatIdentity;
    } else {
        Quat* q = &cell->mOrientation;
        float w;
        if (orient == 0) {
            float half = (float)(sMathRandom.RandomDoubleUniform() * kTwoPi * 0.5f);
            float s = (float)sin(half);
            float c = (float)cos(half);
            Vector3f axis(s * kUnitZ.x, s * kUnitZ.y, s * kUnitZ.z);
            q->v.x = axis.x; q->v.y = axis.y; q->v.z = axis.z;
            w = c;
        } else {
            q->v = orient->v;
            w = orient->w;
        }
        q->w = w;
    }
    cell->mTransform.mTranslation = cell->mPosition;
    cell->mTransform.mFlags |= 4;
    cell->mTransform.mModificationCount++;
    Matrix3 rot;
    cell->mTransform.mRotation = *Matrix3FromQuaternion(&rot, &cell->mOrientation);
    cell->mTransform.mFlags |= 2;
    cell->mTransform.mModificationCount++;

    if (group == gspCellGame->mGroup4100) {
        Vector3 tmp;
        Vector3* v = FUN_00e5eb20(&tmp, cell);
        cell->mVelocity.x = v->x;
        cell->mVelocity.y = v->y;
        cell->mVelocity.z = v->z;
    } else {
        cell->mVelocity = kVec3Zero;
    }
    cell->mRelativeElevation = elevation;
    cell->mOpacity = 1.0f;
    cell->mField0a4 = 1.0f;
    cell->mSize = size;
    cell->mField0a8 = 0.0f;
    cell->mField0ac = 10.0f;
    float mass = FUN_00e4f9d0(defId) * size * size;
    cell->mMass = mass;
    cell->mInvMass = 1.0f / mass;
    if (radiusOrFlag.flag) {
        cell->mTransform.mModificationCount++;
        cell->mTransform.mScale = cell->mSize;
    }
    cell->mField11c = 1;
    cell->mField128 = 0;
    cell->mField118 = 0;
    cell->mField120 = 0;
    cell->mField124 = 0;
    cell->mField12c = Vector3f(kUnitZ.x * 10.0f + pos->x, kUnitZ.y * 10.0f + pos->y, kUnitZ.z * 10.0f + pos->z);
    cell->mField138 = *(Vector3*)&cell->mField12c;
    cell->mField144 = 0;
    cell->mField1c0 = 1.0f;
    cell->mVisualTransform.mRotation = kMatrix3Identity;
    cell->mVisualTransform.mScale = 1.0f;
    cell->mVisualTransform.mTranslation = kVec3Zero;
    cell->mVisualTransform.mFlags = 0;
    cell->mVisualTransform.mModificationCount = 0;
    {
        Vector3 keyTmp;
        cell->mModelKey = *FUN_00e65640(&keyTmp, defId);
    }
    cell->mDefId = defId;
    cell->mByte111 = 0;
    cell->mByte112 = 0;
    cell->mByte113 = 0;
    cell->mByte110 = 0;
    cell->mField10c = 0;
    cell->mField368 = 0.0f;
    cell->mField36c = 0;
    cell->mField370 = 0;
    cell->mField374 = 0.0f;
    cell->mField14c = 0;
    FUN_00e6cad0(def, cell->mModelKey, &cell->mField158, &cell->mField15c);
    cell->mField150 = 0.0f;
    cell->mField244 = 6;
    cell->mField248 = 0;
    cell->mField24c = 0;
    cell->mField250 = 0;
    cell->mByte354 = 0;
    cell->mField358 = level;
    cell->mField35c = group;

    Vector3 center;
    FUN_00e6d790(cell, &center, &radiusOrFlag.radius);
    cell->mField360 = FUN_00e868f0(group, &center, radiusOrFlag.radius, id);
    if (group == gspCellGame->midPlayerCell) {
        int f = filter;
        if (f == -1) {
            if (def->mKind == 7)
                f = -5;
            else if (def->mKind == 5)
                f = -5;
            else
                f = id;
        }
        float lo[2], hi[2];
        hi[0] = center.x + radiusOrFlag.radius;
        hi[1] = center.y + radiusOrFlag.radius;
        lo[0] = center.x - radiusOrFlag.radius;
        lo[1] = center.y - radiusOrFlag.radius;
        cell->mField364 = FUN_00bbbdd0(gspCellGame->mpPhysics, cell->mIndex, lo, hi, f);
    } else {
        cell->mField364 = -1;
    }

    cLevelInfo* info;
    switch (gspCellGame->mpSerializableData->mStage) {
    case 0:
        info = &def->mLevels[2];
        if (info->mType == -1)
            info = &def->mLevels[0];
        break;
    case 1:
        info = &def->mLevels[0];
        break;
    case 2:
        info = &def->mLevels[1];
        if (info->mType == -1)
            info = &def->mLevels[0];
        break;
    default:
        info = &def->mLevels[0];
        break;
    }
    double limit = info->mLimit;
    double v = sMathRandom.RandomDoubleUniform() * limit;
    if (v < limit) {
        if (v < 0.0)
            v = 0.0;
    } else {
        v = limit;
    }
    cell->mField234 = (float)v;
    if (info->mType == 0x100c)
        cell->mField1fc = cell->mTransform.mTranslation;
    return id;
}
