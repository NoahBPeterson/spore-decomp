// SPGonzago/SPCellGame.obj -- one shape-matching step for a cell's node mesh.
//
// A cell owns up to 64 indices into the fluid-particle system's node field.
// This function refreshes the cell's tessellation state, gathers the touched
// nodes' positions, runs one shape-matching goal step (0x00e85dc0) against the
// per-level rest pose, installs the resulting rotation/translation on the cell
// transform, and stores each node's (goal - position) offset into the particle
// displacement array that the fluid update (0x00e59ee0) adds to the positions.
//
// Retail flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (the goal loop below is
// scalar-SSE; the default /fp:precise build selects x87 and is not comparable).
//
// 0x00e5a1a0 and 0x00e5a2a0 are internal-linkage helpers of this translation
// unit (retail hands them their cell/matrix arguments in a register), so they
// are defined here rather than declared.
//
// Retail offsets used here (verified against this function's body):
//   cell+0x024   Matrix33 deformation matrix   (SP::cSPCell::mDeformationMatrix)
//   cell+0x048   transform: flags, version, position, scale, rotation (+0x5c)
//   cell+0x1d0   float eval timer              (SP::cSPCell::mEvalTimer)
//   cell+0x248   int   tessellation state      (SP::cSPCell::mTessilation)
//   cell+0x24c   int   level (indexes the per-level rest-pose tables)
//   cell+0x250   int   node count
//   cell+0x254   int[64] node indices
//   definition+0x0ac  bool  shape matching suspended

#include "game/types.h"
#include <string.h>

struct Vec3_s00e5_a430 { float x, y, z; };
struct Matrix33_s00e5_a430 { float m[9]; };

// SP::cSPTransform as it sits at cell+0x48 (0x38 bytes; it ends on mZOffset).
struct Transform_s00e5_a430 {
    unsigned short     mFlags;     // 0x48
    unsigned short     mVersion;   // 0x4a
    Vec3_s00e5_a430    mPosition;  // 0x4c
    float              mScale;     // 0x58 shape-match scale
    Matrix33_s00e5_a430 mRotation; // 0x5c
};

struct Cell_s00e5_a430 {
    char                pad_000[0x24];
    Matrix33_s00e5_a430 mDeformationMatrix; // 0x24
    Transform_s00e5_a430 mTransform;        // 0x48
    char                pad_080[0x1d0 - 0x80];
    float               mEvalTimer;         // 0x1d0
    char                pad_1d4[0x248 - 0x1d4];
    int                 mTessilation;       // 0x248
    int                 mLevel;             // 0x24c
    int                 mNumNodes;          // 0x250
    int                 mNodeIndex[64];     // 0x254
};

// The object passed as the second argument (the cell's creature definition).
struct CellDefinition_s00e5_a430 {
    int  mID;                            // 0x00
    char pad_004[0xac - 0x04];
    bool mSuspendShapeMatching;          // 0xac
};

// SP::cCellGame, only the member this function walks through.
struct CellGame_s00e5_a430 { char pad_000[0x4108]; void* mpFluidParticles; };
extern CellGame_s00e5_a430* gspCellGame_s00e5_a430;   // 0x016b3c04

// ---- globals -------------------------------------------------------------
extern const char  g_16b3dac[36];                     // 0x016b3dac  identity Matrix33
extern const float kf14851ec;                         // 1.5258789e-05f
extern char        gRestPose_016ad6c0[];              // rest pose, 0x300 bytes per level
extern char        gAqqWork_016ae2c0[];               // Aqq workspace, 0x144 bytes per level
extern const float gUnitMasses_01482c20[];            // 1.0f per node

extern const float kf1485720;                         // 1.0f
extern const float kf1470f1c;                         // 2.0f
extern const float kf13eb8c8;                         // 0.3f
extern const float kf15a7c34, kf15a7c38, kf15a7c3c;
extern const float kf15a7c40;
extern float g16b4434, g16b4438, g16b443c;
extern int   g16b4440;

// ---- callees -------------------------------------------------------------
struct ObjHolder_s00e5_a430 { void Init(); void Cleanup(); };  // 0x00743b50 / 0x00e82130
struct ObjIter_s00e5_a430 { int mHandle; };                   // 4-byte lookup iterator

void* FUN_00e823a0(int id, void* out);                         // 0x00e4cc40
void  FUN_00e51a40(int, int, void*, int);                      // 0x00e51a40
float FUN_006994a0(float*, float*, const void*);               // 0x006994a0
void  FUN_00e85dc0(int n, const float* restOffsets, const float* masses,
                   const float* aqq, const float* positions, float scale,
                   float beta, float* goals, float* rotation,
                   float* translation);                        // 0x00e85dc0

// 0x00e5a1a0 -- refresh the cell's tessellation level from its height.
__declspec(noinline) static void FUN_00e5a1a0(char* cell)
{
    if (*(int*)(cell + 0x248) != 0 &&
        *(int*)(cell + 0x35c) != *(int*)((char*)gspCellGame_s00e5_a430 + 0x4100)) {
        float f = *(float*)(cell + 0x58);
        int lvl;
        if (f < kf1470f1c) {
            if (f < kf1485720) {
                lvl = (f < kf13eb8c8) ? 0 : 1;
            } else {
                lvl = 2;
            }
        } else {
            lvl = 3;
        }
        if (*(int*)(cell + 0x24c) != lvl) {
            char o1[4];
            char o2[4];
            ((ObjHolder_s00e5_a430*)o1)->Init();
            char* r = (char*)FUN_00e823a0(*(int*)(cell + 0x108), o1);
            ((ObjHolder_s00e5_a430*)o2)->Init();
            FUN_00e823a0(*(int*)r, o2);
            int state = *(int*)(r + 0xb4);
            if (state != 0 && state != 5) {
                FUN_00e51a40(0x16ae800, *(int*)cell, cell + 0x250, *(int*)(cell + 0x24c));
                *(int*)(cell + 0x24c) = lvl;
            }
            ((ObjHolder_s00e5_a430*)o2)->Cleanup();
            ((ObjHolder_s00e5_a430*)o1)->Cleanup();
        }
    }
}

// force an out-of-line copy so the helper keeps its own calling convention
void keep_00e5a1a0(char* cell) { FUN_00e5a1a0(cell); }

// 0x00e5a2a0 -- orientation difference of two rotation matrices over d.  Retail
// calls it with all three arguments on the stack.
float FUN_00e5a2a0(float* a, float* b, float d);

// @ 0x00e5a430
void FUN_00e5a430(Cell_s00e5_a430* cell, CellDefinition_s00e5_a430* definition, float elapsed)
{
    FUN_00e5a1a0((char*)cell);

    if (definition->mSuspendShapeMatching)
        return;

    const int count = cell->mNumNodes;
    if (count == 1) {
        memcpy(&cell->mDeformationMatrix, g_16b3dac, sizeof(Matrix33_s00e5_a430));
        return;
    }
    if (cell->mTessilation == 0)
        return;

    Vec3_s00e5_a430 positions[64];
    Vec3_s00e5_a430 goals[64];
    for (int i = 0; i < count; ++i) {
        const int node = cell->mNodeIndex[i];
        positions[i] = *(const Vec3_s00e5_a430*)((char*)gspCellGame_s00e5_a430->mpFluidParticles
                                               + 4 + node * 12);
    }

    ObjIter_s00e5_a430 object;
    ((ObjHolder_s00e5_a430*)&object)->Init();
    FUN_00e823a0(definition->mID, &object);

    const int level = cell->mLevel;
    Matrix33_s00e5_a430 rotation;
    FUN_00e85dc0(count, (const float*)(gRestPose_016ad6c0 + level * 0x300), gUnitMasses_01482c20,
                 (const float*)(gAqqWork_016ae2c0 + level * 0x144), (const float*)positions,
                 cell->mTransform.mScale, 0.0f, (float*)goals, rotation.m,
                 cell->mDeformationMatrix.m);

    Transform_s00e5_a430* xf = &cell->mTransform;
    cell->mEvalTimer = FUN_00e5a2a0(cell->mTransform.mRotation.m, rotation.m, elapsed);
    xf->mFlags |= 2;
    ++xf->mVersion;
    xf->mRotation = rotation;

    for (int i = 0; i < count; ++i) {
        const Vec3_s00e5_a430& goal = goals[i];
        const Vec3_s00e5_a430& from = positions[i];
        Vec3_s00e5_a430 delta;
        delta.x = goal.x - from.x;
        delta.y = goal.y - from.y;
        delta.z = 0.0f;
        float d2 = delta.x * delta.x;
        d2 += delta.y * delta.y;
        if (d2 < kf14851ec)
            continue;
        *(Vec3_s00e5_a430*)((char*)gspCellGame_s00e5_a430->mpFluidParticles + 0x11944
                            + cell->mNodeIndex[i] * 12) = delta;
    }

    ((ObjHolder_s00e5_a430*)&object)->Cleanup();
}
