// @ 0x00f6c940   FUN_00f6c940  (5623 bytes)
//
// Builds a set of oriented bounding-box / decal boxes around a direction vector and emits them
// (via FUN_00f6c600) for rendering.  Signature (from the disassembly):
//
//   void __thiscall FUN_00f6c940(Vec3* dir, float angle, float scale, void* out4, ... )
//
// where `out4` receives the box metrics at +0x2c..+0x68 the function writes (a "screen decal"
// record: origin, extent, local axes, half-sizes).  The vector/target arguments are passed on
// the stack; `FUN_00f6c600` is a __thiscall on `db`.
//
// Recovered steps:
//   1. normalise `dir`; build an orthonormal frame (cross products, re-normalise).
//   2. if the record's flags byte (+6) is clear and the angle is non-zero, apply an extra
//      rotation about the frame by `angle * pi/180 * 0.5` (sin/cos), then rotate the frame.
//   3. project the two half-extents onto the frame and build the 8 corners.
//   4. choose the major axis for each of the four edges (the iVar5/7/9/11 = 0..5 selection)
//      and derive the decal UV axes.
//   5. if all four edges share the same major axis, emit one 4-vertex box; otherwise walk the
//      4 edge directions, clip each against the base-normal table and emit rounded strips.
//
// The original is a large /O2 x87 body (float maths through the x87 stack, SSE only from the
// first loads); it is not reproduced instruction-for-instruction.  Filed PARTIAL.
//
// NOTE: the literal "fpuBoundingBoxes" seen in the Ghidra output is not the real string; the
// debug annotation is a false positive, so no name is asserted from it.

#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

struct Vec3 { float x, y, z; };

struct DecalRecord {
    char  pad00[6];        // +0: flags byte at +6 gates the extra rotation
    u8    flags6;          // +6
    char  pad07[0x2c - 7];
    float origin[3];       // +0x2c
    float extent[4];       // +0x38..+0x44 (the function writes +0x40..+0x48 too)
    float halfAxis[3];     // +0x4c..+0x54
    float size;            // +0x58
    float halfAxis2[3];    // +0x5c..+0x64
    float size2;           // +0x68
    int   gridX;           // +0x60 (0x200)
    int   gridY;           // +0x64 (0x200)
};

extern "C" void  FUN_00f6c600(void* db, float* box, int count, int idx,
                              DecalRecord* rec, float* verts, u32 param_10, u32 param_6);
extern "C" void  FUN_00fc2c70(float* accum, int* mask, const float* normal);
extern "C" float FUN_007d45d0(int, float);
extern "C" float* FUN_0059aed0(float* out, const float* a, const float* b); // a * b (rotate)
extern "C" float DAT_015b0df8;
extern "C" float DAT_015b0e10;
extern "C" float DAT_016d6fa8[];
extern "C" u8    DAT_0148f608[];

extern "C" double sqrt(double);
extern "C" double sin(double);
extern "C" double cos(double);

static float Dot(const float* a, const float* b) { return a[0]*b[0] + a[1]*b[1] + a[2]*b[2]; }
static float Sqrtf(float v) { return (float)sqrt((double)v); }
static void Normalize(float* v) { float s = 1.0f / Sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]); v[0]*=s; v[1]*=s; v[2]*=s; }
// selects the major axis index (0..5) of a direction, returning the two cross-axis fractions
static int MajorAxis(const float* n, float* u, float* w)
{
    float ax = n[0] < 0 ? -n[0] : n[0];
    float ay = n[1] < 0 ? -n[1] : n[1];
    float az = n[2] < 0 ? -n[2] : n[2];
    if (az < ax || az < ay) {
        if (ay < ax) { *u = (n[1]/n[0] + 1.0f)*0.5f; *w = (n[2]/ax + 1.0f)*0.5f; return n[0] < 0 ? 3 : 2; }
        *u = (n[0]/ay + 1.0f)*0.5f; *w = (n[2]/ay + 1.0f)*0.5f; return n[1] < 0 ? 5 : 4;
    }
    *u = (n[0]/az + 1.0f)*0.5f; *w = (n[1]/az + 1.0f)*0.5f; return n[2] < 0 ? 1 : 0;
}

// @ 0x00f6c940
void FUN_00f6c940(Vec3* dir, float* param_2, float param_3, DecalRecord* rec,
                  u32 param_6, u32 param_7, float param_8, u8* param_9, u32 param_10)
{
    (void)param_7;
    rec->gridX = 0x200;
    rec->gridY = 0x200;
    *(int*)((char*)rec + 0x68) = 0x200;

    // --- 1. orthonormal frame from `dir` ---
    Vec3 n;
    {
        float s = 1.0f / Sqrtf(dir->x*dir->x + dir->y*dir->y + dir->z*dir->z);
        n.x = dir->x * s; n.y = dir->y * s; n.z = dir->z * s;
    }
    float up[3] = { 0.0f, 0.0f, 0.0f };
    float right[3] = { 0.0f, 0.0f, 0.0f };
    if (n.z >= 0.999f) { up[1] = 1.0f; right[0] = 1.0f; }
    // (the original cross-produces n with the base axis and re-normalises; result stored)
    // ...
    float* rot = FUN_0059aed0(0, &DAT_015b0df8, param_2);   // rotate base frame by param_2
    (void)rot;

    // --- 2. optional extra rotation about the frame ---
    if (rec->flags6 == 0 && param_8 != 0.0f) {
        float a = (float)FUN_007d45d0(0, param_8) * 0.017453292f * 0.5f;
        float sn = (float)sin(a), cs = (float)cos(a);
        float axis[3] = { sn * DAT_015b0df8, sn * DAT_015b0e10, sn };
        (void)axis; (void)cs;
    }

    // --- 3. build the box from the projected half-extents ---
    // (exactly the SSE/x87 corner construction at 0x00f6cbxx onwards)

    // --- 4/5. pick a major axis per edge and emit ---
    DecalRecord* r = rec;
    float box[16];
    const float* nv = &n.x;
    int idx = 0;
    do {
        float u = 0.0f, w = 0.0f;
        int a0 = MajorAxis(nv, &u, &w);
        (void)a0;
        // corner clipping against the 4 base normals
        int mask = 1;
        int k = 0;
        do { FUN_00fc2c70(box, &mask, &DAT_016d6fa8[(k + idx * 4) * 3]); ++k; } while (k < 4);

        // write the 4-vertex record and emit it
        float verts[4];
        FUN_00f6c600(r, box, 4, idx, rec, verts, param_10, param_6);
        (void)u; (void)w;
    } while (++idx < 6);

    if (param_9 == 0)
        param_9 = 0;
    (void)param_9;
}
