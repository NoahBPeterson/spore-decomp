// Slice s00b97280 -- FUN_00b97720: pick a random spawn point on the planet's cube-map grid.
// With a reference position it gathers every grid cell inside the ring [minDist, maxDist] around
// that position (filtered by region size / free cells, two placement predicates and optionally
// "same continent"), then returns a random one, scaled to terrain height. Without a reference it
// returns the center of the first suitable grid region.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, fabs)

// float -> int rounding up (the module's asm helper; cvtss2si + cmovb)
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

// float -> int truncation (the module's asm helper)
__forceinline int FloatToInt(float f) { __asm cvttss2si eax, f }

struct Vec3 { float x, y, z; };

namespace SP {
int __cdecl WrapCubeFace(int n, int* face, int* x, int* y, int a, int b);  // 0x00684ca0
}

extern const unsigned char g_cubeAxes[];   // 0x01465948: 4 bytes per face pair

struct Region {
    char  valid;   // +0
    char  face;    // +1
    short y0;      // +2
    short y1;      // +4
    short x0;      // +6
    short x1;      // +8
    short pad;     // +0xa
    int   area;    // +0xc
};
struct Cell {
    Region* owner;          // +0
    unsigned int flags;     // +4
    int pad;
};
struct CubeCell { int x, y, face; };

struct cCubeGrid {          // 0x0156c060
    char pad0[0x8];
    Region** mRegionsBegin;      // +0x08
    Region** mRegionsEnd;        // +0x0c
    char pad10[0x14];
    int mN;                      // +0x24 cells per face edge
    char pad1[4];
    unsigned short* mHeights;    // +0x2c
    char pad2[4];
    Cell* mCells;                // +0x34
    int mStrideA;                // +0x38
    int mStrideB;                // +0x3c
    char pad3[4];
    float mScale;                // +0x44
    int mBase;                   // +0x48
    float mBias;                 // +0x4c  planet radius

    bool  IsCellFree(int idx, int face, int x, int y);   // 0x00b907f0
    float GetHeight(const int* p);                       // 0x00b917b0
};
extern cCubeGrid g_CubeGrid;        // 0x0156c060
extern bool g_CubeGridIgnoreFree;   // 0x0168888c

struct PlanetModel {
    int GetContinent(const Vec3& pos);   // 0x00b88590
};
namespace SP {
PlanetModel* PlanetModel();   // 0x00b3d350
void* NounManager();          // 0x00b3d300
}

namespace EA { namespace Random {
struct RandomLinearCongruential {
    unsigned int RandomUint32Uniform(unsigned int n);   // 0x00a68fb0
};
} }
extern EA::Random::RandomLinearCongruential g_SpawnRandom;   // 0x016888e8

bool __cdecl CellPassesSlope(const CubeCell* c, int n, float maxSlope, int mode);                  // 0x00b90d70
bool __cdecl CellPassesFilters(const CubeCell* c, float a, float b, float c2, float d, float e,
                               float f, int g, int h, int i);                                       // 0x00b95d50

// fixed-capacity vector of candidate cells (static local storage)
struct CubeCellVector {
    CubeCell* mpBegin;
    CubeCell* mpEnd;
    CubeCell* mpCapacity;
    int mAllocator[2];
    int mOverflow;              // +0x14
    CubeCell mBuffer[256];      // +0x18
    CubeCellVector() {
        mOverflow = 0;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 256;
    }
    ~CubeCellVector();                                              // 0x013c2e20 (atexit)
    CubeCell* erase(CubeCell* first, CubeCell* last);               // 0x009e0480
    void DoInsertValue(CubeCell* position, const CubeCell& value);  // 0x00b535d0
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const CubeCell& value) {
        if (mpEnd < mpCapacity) {
            CubeCell* p = mpEnd++;
            if (p) *p = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};

// unit direction of a cube-map cell center
__forceinline void CellDirection(int face, int x, int y, Vec3& out)
{
    float inv = 1.0f / (float)g_CubeGrid.mN;
    float fa = (((float)x + 0.5f) * inv) * 2.0f - 1.0f;
    float fb = (((float)y + 0.5f) * inv) * 2.0f - 1.0f;
    const unsigned char* t = &g_cubeAxes[(face >> 1) * 4];
    float nrm = 1.0f / (float)sqrt((fb * fb + fa * fa) + 1.0f);
    float s = nrm;
    if (face & 1) s = -nrm;
    float* v = &out.x;
    v[t[0]] = s * fa;
    v[t[1]] = nrm * fb;
    v[t[2]] = s;
}

// @ 0x00b97720
bool FUN_00b97720(Vec3* out, const Vec3* pos, bool usePos, float minDist, float maxDist,
                  float a1c, float a20, float minArea, float a28, float a2c, float a30, float a34,
                  float maxSlope, int a3c, int a40, int a44, bool sameContinent)
{
    float cellSize = g_CubeGrid.mBias / (float)g_CubeGrid.mN;
    float invCell = 1.0f / cellSize;
    float minCells = invCell * invCell * minArea;
    PlanetModel* pm = SP::PlanetModel();
    SP::NounManager();

    if (usePos) {
        Vec3 n;
        float inv = 1.0f / (float)sqrt(((pos->x * pos->x + pos->y * pos->y) + pos->z * pos->z) + 1e-08f);
        n.x = pos->x * inv;
        n.y = pos->y * inv;
        n.z = pos->z * inv;
        float ax = (float)fabs(pos->x);
        float ay = (float)fabs(pos->y);
        float az = (float)fabs(pos->z);
        float half = (float)g_CubeGrid.mN * 0.5f;
        CubeCell center;
        if (az >= ax && az >= ay) {
            center.x = FloatToInt((pos->x / pos->z + 1.0f) * half);
            center.y = FloatToInt((pos->y / az + 1.0f) * half);
            center.face = (pos->z >= 0.0f) ? 0 : 1;
        } else if (ay >= ax) {
            center.x = FloatToInt((pos->z / pos->y + 1.0f) * half);
            center.y = FloatToInt((pos->x / ay + 1.0f) * half);
            center.face = (pos->y >= 0.0f) ? 4 : 5;
        } else {
            center.x = FloatToInt((pos->y / pos->x + 1.0f) * half);
            center.y = FloatToInt((pos->z / ax + 1.0f) * half);
            center.face = (pos->x >= 0.0f) ? 2 : 3;
        }
        if (center.x == g_CubeGrid.mN) center.x--;
        if (center.y == g_CubeGrid.mN) center.y--;

        int continent = pm->GetContinent(*pos);
        float invHeight = 1.0f / g_CubeGrid.GetHeight(&center.x);
        float minR = invHeight * minDist;
        float minRSq = minR * minR;
        float maxR = invHeight * maxDist;
        float maxRSq = maxR * maxR;
        int minSpan = CeilToInt(invCell * minDist * 0.5f);
        int span = CeilToInt(invCell * maxDist * 0.5f);
        (void)minSpan;
        int xStart = center.x - span;
        int xEnd = center.x + span;
        int yStart = center.y - span;
        int yEnd = center.y + span;
        bool allowCenter = cellSize > minDist;

        static CubeCellVector sCandidates;
        sCandidates.clear();

        for (int x = xStart; x <= xEnd; ++x) {
            for (int y = yStart; y <= yEnd; ++y) {
                CubeCell c;
                c.x = x;
                c.y = y;
                c.face = center.face;
                do {
                } while (SP::WrapCubeFace(g_CubeGrid.mN, &c.face, &c.x, &c.y, 0, 0));
                int idx = (c.face * g_CubeGrid.mN + c.y) * g_CubeGrid.mN + c.x;
                Region* r = g_CubeGrid.mCells[idx].owner;
                if ((r && (float)r->area >= minCells) ||
                    (!g_CubeGridIgnoreFree && g_CubeGrid.IsCellFree(idx, c.face, c.x, c.y))) {
                    if (maxSlope < 1.5258789e-05f || CellPassesSlope(&c, g_CubeGrid.mN, maxSlope, a40)) {
                        Vec3 v;
                        CellDirection(c.face, c.x, c.y, v);
                        float d2 = ((v.z - n.z) * (v.z - n.z) + (v.y - n.y) * (v.y - n.y)) + (v.x - n.x) * (v.x - n.x);
                        if (d2 <= maxRSq && d2 >= minRSq &&
                            (allowCenter || c.x != center.x || c.y != center.y || c.face != center.face) &&
                            (!sameContinent || pm->GetContinent(v) == continent) &&
                            CellPassesFilters(&c, a1c, a20, a28, a2c, a30, a34, a3c, a40, a44)) {
                            sCandidates.push_back(c);
                        }
                    }
                }
            }
        }

        int count = (int)(sCandidates.mpEnd - sCandidates.mpBegin);
        if (count > 0) {
            int i = (int)g_SpawnRandom.RandomUint32Uniform(count);
            const CubeCell& c = sCandidates.mpBegin[i];
            int face = c.face;
            int cx = c.x;
            int cy = c.y;
            CellDirection(face, cx, cy, n);
            unsigned int a0 = (unsigned int)(g_CubeGrid.mStrideA * cx) / (unsigned int)g_CubeGrid.mN;
            unsigned int b0 = (unsigned int)(g_CubeGrid.mStrideB * cy) / (unsigned int)g_CubeGrid.mN;
            int hidx = a0 + b0 + g_CubeGrid.mStrideB * face + g_CubeGrid.mBase;
            int h = (int)g_CubeGrid.mHeights[hidx] - 0x8000;
            float height = ((float)h * g_CubeGrid.mScale) * 3.051851e-05f + g_CubeGrid.mBias;
            out->x = n.x * height;
            out->y = n.y * height;
            out->z = n.z * height;
            return true;
        }
    } else {
        Region** end = g_CubeGrid.mRegionsEnd;
        for (Region** it = g_CubeGrid.mRegionsBegin; it != end; ++it) {
            Region* r = *it;
            CubeCell c;
            c.x = (r->x1 - r->x0) / 2 + r->x0;
            c.y = (r->y1 - r->y0) / 2 + r->y0;
            c.face = r->face;
            do {
            } while (SP::WrapCubeFace(g_CubeGrid.mN, &c.face, &c.x, &c.y, 0, 0));
            if ((float)r->area > minCells &&
                CellPassesSlope(&c, g_CubeGrid.mN, maxSlope, a40) &&
                CellPassesFilters(&c, a1c, a20, a28, a2c, a30, a34, a3c, a40, a44)) {
                float height = g_CubeGrid.GetHeight(&c.x);
                Vec3 v;
                CellDirection(c.face, c.x, c.y, v);
                out->x = v.x * height;
                out->y = v.y * height;
                out->z = v.z * height;
                return true;
            }
        }
    }
    return false;
}
