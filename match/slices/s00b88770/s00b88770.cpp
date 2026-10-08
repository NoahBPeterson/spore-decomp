// Slice s00b88770 -- cPlanetModel::RayCast (0x00b88770, 2032 bytes, thiscall, ret 0x18).
//
// Casts a ray from `pos` (a point near the planet, direction = normalized pos) against the planet
// model's cube-map flag grid (6 faces x 128 x 128 uint32 cells at +0x4c; bit 31 = a per-cell flag,
// bits 16..25 an index into a per-region table at +0x50).  The ray direction picks the cube face
// and cell; FUN_00685450 lists the cell rectangles within `radius` cells of it, and every cell
// whose flag equals `wantFlag` is turned into a point on the unit cube-sphere (axes from the
// table at 0x014653b8).  The nearest such point (within maxDist, at most 500) wins.  If one was
// found it is snapped to the surface (ToSurface) and then marched back along the ray from `pos`
// in steps of `step` (default 1.0) while the terrain height there is on the wrong side of the
// sea level; finally it is scaled to max(terrain height, sea level) on the unit direction.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <float.h>

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, fabs)

__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}
__forceinline int FloatToInt(float f) { __asm cvttss2si eax, f }

struct Vec3 { float x, y, z; };

namespace SP {
struct cTerrainMapSet {
    char  pad[0x34];
    float mBase;      // +0x34
    float mScale;     // +0x38
    float mFactor;    // +0x3c
    float GetHeightAt(const Vec3* p);       // 0x00f927c0
};
class cTerrainSource {
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual cTerrainMapSet* GetTerrainMapSet();   // +0x0c
};
}

// 0x00685450: lists the cell rectangles within `radius` cells of cell[0..2] = {u, v, face}
int __cdecl GridCellRects(int size, const int* cell, int radius, int* out);

extern const unsigned char g_faceAxes[];     // 0x014653b8: 4 bytes per face pair

static const float kMaxDist = 500.0f;     // address taken below, so it gets its own storage

class cPlanetModel {
public:
    bool RayCast(const Vec3* pos, float maxDist, Vec3* out, float step, bool wantFlag, unsigned minVal);

    void  Rebuild();                                   // 0x00b87dc0
    Vec3* ToSurface(Vec3* ret, const Vec3* p);         // 0x00b81630 (ret 8)

    char  pad0[0x20];
    int   mUseHeightMap;                               // +0x20
    SP::cTerrainSource* mpTerrain;                     // +0x24
    char  pad1[0x24];
    unsigned* mpCells;                                 // +0x4c
    unsigned* mpRegionBegin;                           // +0x50
    unsigned* mpRegionEnd;                             // +0x54
    char  pad2[0x20];
    char  mDirty;                                      // +0x78
};

// @ 0x00b88770
bool cPlanetModel::RayCast(const Vec3* pos, float maxDist, Vec3* out, float step, bool wantFlag, unsigned minVal)
{
    if (mDirty) {
        mDirty = 0;
        Rebuild();
    }

    const float& lim = (maxDist > 500.0f) ? kMaxDist : maxDist;

    float c[3];
    c[0] = pos->x;
    c[1] = pos->y;
    c[2] = pos->z;
    float len = (float)sqrt(c[2] * c[2] + c[1] * c[1] + c[0] * c[0]);
    if (len <= 1.5258789e-05f)
        return false;

    float inv = 1.0f / len;
    float scaled = inv * 128.0f;
    int radius = CeilToInt(scaled * lim);
    c[0] = c[0] * inv;
    float ax = (float)fabs(c[0]);
    c[1] = c[1] * inv;
    c[2] = c[2] * inv;
    float ay = (float)fabs(c[1]);
    inv = inv * lim;
    float az = (float)fabs(c[2]);
    float limit2 = inv * inv;
    float best = FLT_MAX;

    int cell[3];
    if (az < ax || az < ay) {
        if (ay < ax) {
            cell[0] = FloatToInt((c[1] / c[0] + 1.0f) * 64.0f);
            cell[1] = FloatToInt((c[2] / ax + 1.0f) * 64.0f);
            cell[2] = (c[0] < 0.0f) ? 3 : 2;
        } else {
            cell[0] = FloatToInt((c[2] / c[1] + 1.0f) * 64.0f);
            cell[1] = FloatToInt((c[0] / ay + 1.0f) * 64.0f);
            cell[2] = (c[1] < 0.0f) ? 5 : 4;
        }
    } else {
        cell[0] = FloatToInt((c[0] / c[2] + 1.0f) * 64.0f);
        cell[1] = FloatToInt((c[1] / az + 1.0f) * 64.0f);
        cell[2] = (c[2] < 0.0f) ? 1 : 0;
    }
    if (cell[0] == 0x80) cell[0] = 0x7f;
    if (cell[1] == 0x80) cell[1] = 0x7f;

    int rects[25];
    int nRects = GridCellRects(0x80, cell, radius, rects);

    float d0 = c[0], d1 = c[1], d2 = c[2];
    const int* r = rects;
    for (; nRects > 0; nRects--, r += 5) {
        int face = r[0];
        int j1 = r[3];
        int i1 = r[4];
        for (int i = r[2]; i < i1; i++) {
            for (int j = r[1]; j < j1; j++) {
                unsigned* cp = mpCells + (face * 0x80 + i) * 0x80 + j;
                if (wantFlag == (bool)((*cp >> 31) & 1)) {
                    const unsigned char* ax3 = &g_faceAxes[(face >> 1) * 4];
                    float u = ((float)j + 0.5f) * 0.015625f - 1.0f;
                    float v = ((float)i + 0.5f) * 0.015625f - 1.0f;
                    float n = 1.0f / (float)sqrt(v * v + u * u + 1.0f);
                    float s = n;
                    if (face & 1)
                        s = -n;
                    c[ax3[0]] = s * u;
                    c[ax3[1]] = n * v;
                    c[ax3[2]] = s;
                    float dz = c[2] - d2;
                    float dx = c[0] - d0;
                    float dy = c[1] - d1;
                    float dd = dx * dx + dz * dz + dy * dy;
                    if (dd < best && dd <= limit2) {
                        if (minVal == 0) {
                            out->x = c[0]; out->y = c[1]; out->z = c[2];
                            best = dd;
                        } else {
                            int idx = ((unsigned short*)cp)[1] & 0x3ff;
                            if (idx >= 0 && idx < (int)(mpRegionEnd - mpRegionBegin) && mpRegionBegin[idx] > minVal) {
                                out->x = c[0]; out->y = c[1]; out->z = c[2];
                                best = dd;
                            }
                        }
                    }
                }
            }
        }
    }

    float seaLevel;
    if (mpTerrain) {
        SP::cTerrainMapSet* ms = mpTerrain->GetTerrainMapSet();
        seaLevel = ms->mFactor * ms->mScale + ms->mBase;
    } else {
        seaLevel = 0.0f;
    }

    if (best == FLT_MAX)
        return false;

    Vec3 tmp;
    Vec3* sp = ToSurface(&tmp, out);
    out->x = sp->x; out->y = sp->y; out->z = sp->z;

    float ex = out->x, ez = out->z, ey = out->y;
    float fx = ex - pos->x;
    float fz = ez - pos->z;
    float fy = ey - pos->y;
    float flen = (float)sqrt(fy * fy + (fz * fz + fx * fx));
    float finv = 1.0f / (flen + 1.5258789e-05f);
    float ny = fy * finv;
    float nz = fz * finv;
    float nx = finv * fx;
    float stp = step;
    if (!(step > 0.0f))
        stp = 1.0f;
    float t = flen - stp;
    while (t > 0.0f) {
        Vec3 p;
        p.y = ny * t + pos->y;
        p.z = nz * t + pos->z;
        p.x = pos->x + nx * t;
        float h;
        if (mUseHeightMap) {
            h = mpTerrain->GetTerrainMapSet()->GetHeightAt(&p);
        } else if (mpTerrain && mpTerrain->GetTerrainMapSet()) {
            h = mpTerrain->GetTerrainMapSet()->mBase;
        } else {
            h = 500.0f;
        }
        if (wantFlag != (seaLevel <= h))
            break;
        t = t - stp;
        out->x = p.x; out->y = p.y; out->z = p.z;
    }

    float h2;
    if (mUseHeightMap) {
        h2 = mpTerrain->GetTerrainMapSet()->GetHeightAt(out);
    } else if (mpTerrain && mpTerrain->GetTerrainMapSet()) {
        h2 = mpTerrain->GetTerrainMapSet()->mBase;
    } else {
        h2 = 500.0f;
    }
    float sea2;
    if (mpTerrain) {
        SP::cTerrainMapSet* ms = mpTerrain->GetTerrainMapSet();
        sea2 = ms->mFactor * ms->mScale + ms->mBase;
    } else {
        sea2 = 0.0f;
    }
    if (h2 > sea2)
        sea2 = h2;
    float oz = out->z, oy = out->y, ox = out->x;
    float k = 1.0f / (float)sqrt(ox * ox + (oy * oy + oz * oz) + 1e-08f);
    out->x = k * ox * sea2;
    out->y = k * oy * sea2;
    out->z = k * oz * sea2;
    return true;
}
