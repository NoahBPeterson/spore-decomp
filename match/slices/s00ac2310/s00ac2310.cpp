// Slice s00ac2310: planet-surface sample lookup / path-walk support, the code that
// sits next to the s00ac4ff0 path-relaxation pass.  Names are Claude-coined from
// usage except SP::PlanetModel (PDB).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

typedef unsigned int uint;

struct Vec3Plain { float x, y, z; };

// SP::PlanetModel() returns a holder; its +0x24 member is an object whose virtual
// slot 3 yields the model proper (height fields at +0x34/+0x38), and the holder's
// +0x4c member is the cell array.
struct cPlanetModel {
    unsigned char pad0[0x34];
    float mHalf;                        // 0x34
    float mHeightScale;                 // 0x38
};

typedef void* (__thiscall *GetModelFn)(void*);

struct ModelHolder {
    unsigned char pad[0x24];
    void** mModelIfc;                   // 0x24  object whose [0] is its vtable
    unsigned char pad28[0x24];
    int* mCells;                        // 0x4c
    float GetWaterHeight();             // 0x00b7e390
    float GetWaterHeight2();            // 0x00b7e4d0
};

extern ModelHolder* __cdecl PlanetModel();                  // 0x00b3d350

// invoke the model point-set accessor (virtual slot 3) on the holder's +0x24 object
static inline cPlanetModel* GetModel(ModelHolder* holder)
{
    void** obj = holder->mModelIfc;
    return (cPlanetModel*)((GetModelFn)((void**)obj[0])[3])(obj);
}

// packed cube-face direction code -> cell index
static inline uint CellIndex(uint code)
{
    uint lo = (code >> 8) & 0xff;
    uint hi = (code >> 0x11) * 128;
    return ((lo + hi) << 7) + (code & 0xff);
}

static inline int CodeFace(uint c) { return (int)(c >> 0x11); }
static inline int CodeU(uint c)    { return (int)(c & 0xff); }
static inline int CodeV(uint c)    { return (int)((c >> 8) & 0xff); }

// fill out[perm[2k]] with component k of the surface normal of (face, u) at
// fraction v within the cell
extern void __cdecl SampleSurfaceNormal(int face, int u, int v, float* out);   // 0x00ac1510

extern float __cdecl VecLength(const Vec3Plain* v);                          // 0x00b830b0
extern float __cdecl Distance3(const Vec3Plain* a, const Vec3Plain* b);      // 0x00ac1b30
extern Vec3Plain* __cdecl ProjectPoint(Vec3Plain* out, const Vec3Plain* in); // 0x00b81630 (thiscall, ret 8)
extern float __cdecl FUN_00c9eb60();                                        // 0x00c9eb60

// ---- globals ------------------------------------------------------------------
extern float gMaxValue;               // 0x01565ba4  FLT_MAX
extern float gCellFrac;               // 0x0140d4f8  3.0518509e-05
extern float gTwiceOct;               // 0x013eeda0  8.0
extern float gSixteen;                // 0x01459e24  16.0
extern float gTen;                    // 0x01459e28  10.0
extern const float kOne;              // 0x01485720  1.0
extern const float kScale64;          // 0x0140f334  64.0
extern const float kZero;             // 0x01485378  0.0

// =============================================================================
// @ 0x00ac2310  Distance between the two surface bubbles picked out by the packed
// direction codes a and b.
float __cdecl SurfaceSampleDistance(uint a, uint b)
{
    ModelHolder* holder = PlanetModel();
    cPlanetModel* model = GetModel(holder);
    int* cells = holder->mCells;
    int cb = cells[CellIndex(b)];
    int ca = 0;
    char taken = 0;

    if ((cb & 0x98000000) != 0) {
        ca = cells[CellIndex(a)];
        if ((ca & 0x98000000) != 0)
            taken = 1;
        else
            return gMaxValue;
    }

    float lo = model->mHalf;
    float hi = model->mHeightScale;
    float hb = (float)((short)cb - 0x8000) * hi * gCellFrac + lo;
    ca = cells[CellIndex(a)];
    float ha = (float)((short)ca - 0x8000) * hi * gCellFrac + lo;

    float na[4], nb[4];
    SampleSurfaceNormal(CodeFace(a), CodeU(a), CodeV(a), na);
    SampleSurfaceNormal(CodeFace(b), CodeU(b), CodeV(b), nb);

    float dx = na[0] * hb - nb[0] * ha;
    float dy = na[1] * hb - nb[1] * ha;
    float dz = na[2] * hb - nb[2] * ha;
    float d = sqrtf(dz * dz + (dy * dy + dx * dx));
    if (ha < hb)
        d = (hb - ha) * gTwiceOct + d;
    if (taken)
        d = d * gSixteen;
    return d;
}

// =============================================================================
// @ 0x00ac2520  Quantize the position v into a cube-face direction code, then
// apply the same bubble-distance test used by SurfaceSampleDistance.
float __cdecl SurfaceDistanceByPos(const Vec3Plain* v, uint code)
{
    ModelHolder* holder = PlanetModel();
    cPlanetModel* model = GetModel(holder);
    int* cells = holder->mCells;
    int cb = cells[CellIndex(code)];
    char taken = 0;

    if ((cb & 0x98000000) != 0) {
        float x = v->x;
        float y = v->y;
        float z = v->z;
        float ax = fabsf(x);
        float ay = fabsf(y);
        float az = fabsf(z);
        int u, w, face;
        if (az < ax || az < ay) {
            if (ay < ax) {
                u = (int)((y / x + kOne) * kScale64);
                w = (int)((z / ax + kOne) * kScale64);
                face = (x < kZero) ? 3 : 2;
            } else {
                u = (int)((z / y + kOne) * kScale64);
                w = (int)((x / ay + kOne) * kScale64);
                face = (y < kZero) ? 5 : 4;
            }
        } else {
            u = (int)((x / z + kOne) * kScale64);
            w = (int)((y / az + kOne) * kScale64);
            face = (z < kZero) ? 1 : 0;
        }
        if (u == 0x80) u = 0x7f;
        if (w == 0x80) w = 0x7f;
        if ((cells[(face * 0x80 + w) * 0x80 + u] & 0x98000000) == 0)
            return gMaxValue;
        taken = 1;
    }

    float hi = model->mHeightScale;
    float ha = (float)((short)cb - 0x8000) * hi * gCellFrac + model->mHalf;

    float len = VecLength(v);
    float nx = (v->x / len) * len;
    float ny = (v->y / len) * len;
    float nz = (v->z / len) * len;
    float na[4];
    SampleSurfaceNormal(CodeFace(code), CodeU(code), CodeV(code), na);

    float dx = na[0] * ha - nx;
    float dy = na[1] * ha - ny;
    float dz = na[2] * ha - nz;
    float d = sqrtf(dz * dz + (dy * dy + dx * dx));
    if (len < ha)
        d = (ha - len) * gTwiceOct + d;
    if (taken)
        d = d * gSixteen;
    return d;
}

// =============================================================================
// @ 0x00ac28c0  Like SurfaceDistanceByPos but using GetWaterHeight for the
// vertical term and returning FLT_MAX unless the sample is under water.
float __cdecl DistanceUnderWater(uint a, uint b)
{
    ModelHolder* holder = PlanetModel();
    int* cells = holder->mCells;
    cPlanetModel* model = GetModel(holder);
    int cb = cells[CellIndex(b)];

    if ((cb & 0x58000000) == 0) {
        float hi = model->mHeightScale;
        float lo = model->mHalf;
        float w = holder->GetWaterHeight()
                - ((float)((short)cb - 0x8000) * hi * gCellFrac + lo);
        if (w > 0.0f) {
            float scale = 1.0f;
            if (w < 6.0f)
                scale = 2.0f;
            float na[4], nb[4];
            SampleSurfaceNormal(CodeFace(a), CodeU(a), CodeV(a), na);
            SampleSurfaceNormal(CodeFace(b), CodeU(b), CodeV(b), nb);
            float dx = nb[0] - na[0];
            float dy = nb[1] - na[1];
            float dz = nb[2] - na[2];
            float d = sqrtf(dz * dz + (dy * dy + dx * dx)) * holder->GetWaterHeight();
            return d * scale;
        }
    }
    return gMaxValue;
}

// =============================================================================
// @ 0x00ac2a20  Gap between the unit-sphere direction of v and the surface
// sample under code, scaled by the water height.  FLT_MAX if the cell is taken.
float __cdecl SurfaceGapByPos(const Vec3Plain* v, uint code)
{
    ModelHolder* holder = PlanetModel();
    if ((holder->mCells[CellIndex(code)] & 0x58000000) != 0)
        return gMaxValue;

    float x = v->x;
    float y = v->y;
    float z = v->z;
    float inv = 1.0f / sqrtf(z * z + (y * y + x * x));
    float nx = x * inv;
    float ny = y * inv;
    float nz = z * inv;

    float na[4];
    SampleSurfaceNormal(CodeFace(code), CodeU(code), CodeV(code), na);
    float dx = na[0] - nx;
    float dy = na[1] - ny;
    float dz = na[2] - nz;
    float d = sqrtf(dz * dz + (dy * dy + dx * dx)) * holder->GetWaterHeight();
    return d;
}

// =============================================================================
// @ 0x00ac2b40  Two-code distance: if the height of b is below the water line by
// more than FUN_00c9eb60(), the two surface points are joined at double the gap.
float __cdecl DistanceByHeight(uint a, uint b)
{
    ModelHolder* holder = PlanetModel();
    int* cells = holder->mCells;
    int cb = cells[CellIndex(b)];
    if ((cb & 0x20000000) != 0)
        return gMaxValue;

    cPlanetModel* model = GetModel(holder);
    float hi = model->mHeightScale;
    float height = (float)((short)cb - 0x8000) * hi * gCellFrac;
    if (FUN_00c9eb60() < height) {
        float na[4], nb[4];
        SampleSurfaceNormal(CodeFace(a), CodeU(a), CodeV(a), na);
        SampleSurfaceNormal(CodeFace(b), CodeU(b), CodeV(b), nb);
        float dx = nb[0] - na[0];
        float dy = nb[1] - na[1];
        float dz = nb[2] - na[2];
        float d = sqrtf(dz * dz + (dy * dy + dx * dx)) * holder->GetWaterHeight2();
        return d + d;
    }
    float na[4], nb[4];
    SampleSurfaceNormal(CodeFace(a), CodeU(a), CodeV(a), na);
    SampleSurfaceNormal(CodeFace(b), CodeU(b), CodeV(b), nb);
    float dx = nb[0] - na[0];
    float dy = nb[1] - na[1];
    float dz = nb[2] - na[2];
    return sqrtf(dz * dz + (dy * dy + dx * dx)) * holder->GetWaterHeight2();
}

// =============================================================================
// @ 0x00ac2d00  Like SurfaceGapByPos but gated on a different flag and using
// GetWaterHeight2.
float __cdecl SurfaceGapByPos2(const Vec3Plain* v, uint code)
{
    ModelHolder* holder = PlanetModel();
    if ((holder->mCells[CellIndex(code)] & 0x20000000) != 0)
        return gMaxValue;

    float x = v->x;
    float y = v->y;
    float z = v->z;
    float inv = 1.0f / sqrtf(z * z + (y * y + x * x));
    float nx = x * inv;
    float ny = y * inv;
    float nz = z * inv;

    float na[4];
    SampleSurfaceNormal(CodeFace(code), CodeU(code), CodeV(code), na);
    float dx = na[0] - nx;
    float dy = na[1] - ny;
    float dz = na[2] - nz;
    return sqrtf(dz * dz + (dy * dy + dx * dx)) * holder->GetWaterHeight2();
}

// =============================================================================
// @ 0x00ac2e20  Two-code bubble distance with extra occupancy flags and an
// optional projected-distance term (used when the raw gap is not FLT_MAX).
float __cdecl SurfaceSampleDistance2(uint a, uint b)
{
    ModelHolder* holder = PlanetModel();
    cPlanetModel* model = GetModel(holder);
    int* cells = holder->mCells;
    int cb = cells[CellIndex(b)];
    char taken = 0;

    if (cb < 0)
        return gMaxValue;
    if ((cb & 0x18000000) != 0) {
        if ((cells[CellIndex(a)] & 0x18000000) == 0)
            return gMaxValue;
        taken = 1;
    }

    float lo = model->mHalf;
    float hi = model->mHeightScale;
    float hb = (float)((short)cb - 0x8000) * hi * gCellFrac + lo;
    float ha = (float)((short)cells[CellIndex(a)] - 0x8000) * hi * gCellFrac + lo;

    float na[4], nb[4];
    SampleSurfaceNormal(CodeFace(a), CodeU(a), CodeV(a), na);
    float ax = na[0] * ha;
    float ay = na[1] * ha;
    float az = na[2] * ha;
    SampleSurfaceNormal(CodeFace(b), CodeU(b), CodeV(b), nb);

    float dx = nb[0] * hb - ax;
    float dy = nb[1] * hb - ay;
    float dz = nb[2] * hb - az;
    float d = sqrtf(dz * dz + (dy * dy + dx * dx));
    if (ha < hb)
        d = (hb - ha) * gTwiceOct + d;
    if ((cb & 0x4000000) != 0)
        d = d * gTen;
    if (taken)
        d = d * gSixteen;
    if (d != gMaxValue) {
        float pa[4], pb[4];
        SampleSurfaceNormal(CodeFace(a), CodeU(a), CodeV(a), pa);
        ProjectPoint((Vec3Plain*)pa, (const Vec3Plain*)pa);
        SampleSurfaceNormal(CodeFace(b), CodeU(b), CodeV(b), pb);
        ProjectPoint((Vec3Plain*)pb, (const Vec3Plain*)pb);
        float r = Distance3((const Vec3Plain*)pa, (const Vec3Plain*)pb);
        if (r != 0.0f)
            return r;
    }
    return d;
}
