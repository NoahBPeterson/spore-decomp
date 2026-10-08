// Slice s00d73090 -- 0x00d73350 (1638 bytes): scatter sample points over the planet-surface patch around a
// direction.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc; aligned frame, x87 sqrt, SSE arithmetic).
//
// `obj` holds a vector of 0x1c-byte cells at +0x40 (begin/end/capacity; eastl::vector with the Simulator
// allocator). The function only runs when the vector is empty. It
//   * works out which cube-map face (6 faces of a 256x256 grid) the direction `dir` hits and the grid
//     cell on that face;
//   * asks 0x00685450 for the grid rectangles (per face) that cover `radius` around that cell;
//   * for every grid cell in those rectangles builds the unit direction through the cell centre, keeps it
//     only if it lies within `radius` of `dir`, maps it to the planet surface (DirectionToSurfacePosition),
//     requires the surface point to be above the water, to be on continent `continent`, to have a valid
//     surface frame (0x00b88f60) and a ray result (0x00d72520, FLT_MAX = miss);
//   * and appends {point, ray hit} as a cell unless an existing cell is closer than `spacing` in either.
// Names are Claude-coined (the function has no PDB name).
#include "types.h"

#include <math.h>
#include <float.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

// cell record of 0x1c bytes
struct Cell {
    uint8_t mFlag;
    Vector3 mPoint;      // +0x04 surface point
    Vector3 mHit;        // +0x10 ray result point
};

// grid rectangle returned by 0x00685450: face plus [x0,x1) x [y0,y1)
struct FaceRect {
    int face;
    int x0, y0, x1, y1;
};

// eastl::vector<Cell> with the three non-inlined members at their addresses
struct CellVector {
    Cell* mpBegin;
    Cell* mpEnd;
    Cell* mpCapacity;

    Cell* erase(Cell* first, Cell* last);               // 0x00d73090 (thiscall, ret 8)
    void  reserve(unsigned n);                          // 0x00d72fd0 (thiscall, ret 4)
    void  DoInsertValue(Cell* pos, const Cell& value);  // 0x00d73100 (thiscall, ret 8)

    void clear() { erase(mpBegin, mpEnd); }
    Cell& push_back()
    {
        if (mpEnd < mpCapacity) {
            ++mpEnd;
        } else {
            Cell tmp;
            DoInsertValue(mpEnd, tmp);
        }
        return *(mpEnd - 1);
    }
};

// rounding float->int (cvtss2si)
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

__forceinline int TruncToInt(float f) { __asm cvttss2si eax, f }

extern const uint8_t kFaceAxes[3][4];                   // 0x0147bd6c

namespace SP {

struct cPlanetModel {
    float    GetWaterHeight();                                          // 0x00b7e390
    Vector3* DirectionToSurfacePosition(Vector3* out, Vector3* dir);    // 0x00b815a0 (thiscall, ret 8)
    int      GetContinent(Vector3* pos);                                // 0x00b88590 (thiscall, ret 4)
    bool     GetSurfaceFrame(Vector3* pos, float radius, Vector3* out); // 0x00b88f60 (thiscall, ret 0xc)
};
cPlanetModel* PlanetModel();                                            // 0x00b3d350

} // namespace SP

int GatherFaceRects(int size, const int* center, int radius, FaceRect* out);                          // 0x00685450 (cdecl)
float CastRay(const Vector3* pos, const Vector3* dir, float tolerance, float radius, Vector3* out);   // 0x00d72520 (cdecl)

struct cSurfaceSampler {
    char pad00[0x40];
    CellVector mCells;                                  // +0x40
};

// @ 0x00d73350
void PlaceSurfaceSamples(int continent, cSurfaceSampler* obj, Vector3* dir, float radius, float spacing)
{
    if (obj == 0 || obj->mCells.mpBegin != obj->mCells.mpEnd)
        return;
    CellVector* cells = &obj->mCells;

    SP::cPlanetModel* planet = SP::PlanetModel();
    float water = planet->GetWaterHeight();
    float waterSq = water * water;

    cells->clear();
    cells->reserve(RoundToInt(radius / spacing * 2.0f));

    float spacingSq = spacing * spacing;
    float len = sqrtf(dir->x * dir->x + dir->y * dir->y + dir->z * dir->z);
    float inv = 1.0f / len;
    float rayRadius = len * 0.0078125f * 0.5f + spacing;

    int rad = RoundToInt(inv * 256.0f * radius);

    float ax = fabsf(dir->x);
    float nx = dir->x * inv;
    float ny = dir->y * inv;
    float ay = fabsf(dir->y);
    float az = fabsf(dir->z);
    float nz = dir->z * inv;
    float coneSq = (inv * radius) * (inv * radius);

    FaceRect rects[5];
    int count;
    {
    int cell[3];
    if (az >= ax && az >= ay) {
        cell[0] = TruncToInt((dir->x / dir->z + 1.0f) * 128.0f);
        cell[1] = TruncToInt((dir->y / az + 1.0f) * 128.0f);
        cell[2] = (dir->z >= 0.0f) ? 0 : 1;
    } else if (ay >= ax) {
        cell[0] = TruncToInt((dir->z / dir->y + 1.0f) * 128.0f);
        cell[1] = TruncToInt((dir->x / ay + 1.0f) * 128.0f);
        cell[2] = (dir->y >= 0.0f) ? 4 : 5;
    } else {
        cell[0] = TruncToInt((dir->y / dir->x + 1.0f) * 128.0f);
        cell[1] = TruncToInt((dir->z / ax + 1.0f) * 128.0f);
        cell[2] = (dir->x >= 0.0f) ? 2 : 3;
    }
    if (cell[0] == 0x100)
        cell[0] = 0xff;
    if (cell[1] == 0x100)
        cell[1] = 0xff;

    count = GatherFaceRects(0x100, cell, rad, rects);
    }
    if (count <= 0)
        return;

    FaceRect* r = rects;
    do {
        for (int j = r->y0; j < r->y1; ++j) {
            for (int i = r->x0; i < r->x1; ++i) {
                float sy = ((float)j + 0.5f) * 0.0078125f - 1.0f;
                float sx = ((float)i + 0.5f) * 0.0078125f - 1.0f;
                float rl = 1.0f / sqrtf(sx * sx + sy * sy + 1.0f);
                const uint8_t* axes = kFaceAxes[r->face >> 1];
                float s = (r->face & 1) ? -rl : rl;
                float p[3];
                p[axes[0]] = s * sx;
                p[axes[1]] = rl * sy;
                p[axes[2]] = s;

                float d0 = p[0] - nx;
                float d2 = p[2] - nz;
                float d1 = p[1] - ny;
                if (d0 * d0 + d2 * d2 + d1 * d1 > coneSq)
                    continue;

                Vector3 pos;
                planet->DirectionToSurfacePosition(&pos, (Vector3*)p);
                if (waterSq > pos.x * pos.x + pos.y * pos.y + pos.z * pos.z)
                    continue;
                if (planet->GetContinent(&pos) != continent)
                    continue;
                Vector3 frame;
                if (!planet->GetSurfaceFrame(&pos, rayRadius, &frame))
                    continue;

                Vector3 down;
                down.x = -frame.x;
                down.y = -frame.y;
                down.z = -frame.z;
                Vector3 hit;
                if (CastRay(&pos, &down, 0.1f, rayRadius, &hit) == FLT_MAX)
                    continue;

                bool tooClose = false;
                for (Cell* c = cells->mpBegin; c != cells->mpEnd; ++c) {
                    float ex = c->mPoint.x - pos.x;
                    float ez = c->mPoint.z - pos.z;
                    float ey = c->mPoint.y - pos.y;
                    if (ex * ex + ez * ez + ey * ey < spacingSq) { tooClose = true; break; }
                    float hz = c->mHit.z - hit.z;
                    float hy = c->mHit.y - hit.y;
                    float hx = c->mHit.x - hit.x;
                    if (hz * hz + hy * hy + hx * hx < spacingSq) { tooClose = true; break; }
                }
                if (tooClose)
                    continue;

                Cell& n = cells->push_back();
                n.mFlag = 0;
                n.mPoint = pos;
                n.mHit = hit;
            }
        }
        ++r;
    } while (--count != 0);
}
