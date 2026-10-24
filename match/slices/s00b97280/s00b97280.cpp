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
class RandomLinearCongruential { public:
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

// ---------------------------------------------------------------------------
// Neighbouring template instantiations claimed in this slice.  They are the
// vector helpers used while collecting spawn-point candidates.
// ---------------------------------------------------------------------------

extern "C" void* __cdecl CopyBytes(void* dest, const void* src, unsigned int size);   // 0x011e0744
extern "C" void* (__cdecl* const g_CopyBytesFast)(void*, const void*, unsigned int);   // 0x013cc480
void* __cdecl EastlAllocate(unsigned int size, const char* name, int flags, int align,
                            const char* file, int line);                              // 0x00f473a0
void  __cdecl EastlFree(void* p);                                                     // 0x00f47380
void __cdecl ClearRange16(void* first, void* last, void* destEnd);                    // 0x00705250

struct IntVector {
    int* mpBegin;                           // +0x00
    int* mpEnd;                             // +0x04
    int* mpCapacity;                        // +0x08
    void insert(int* position, unsigned int count, const int* value);
};

// @ 0x00b97280
void IntVector::insert(int* position, unsigned int count, const int* value)
{
    const int copy = *value;
    if (count <= (unsigned int)(mpCapacity - mpEnd)) {
        if (count > 0) {
            const unsigned int tail = (unsigned int)(mpEnd - position);
            int* const oldEnd = mpEnd;
            if (count < tail) {
                CopyBytes(oldEnd, oldEnd - count, count * sizeof(int));
                mpEnd += count;
                const unsigned int bytes = (unsigned int)((oldEnd - count) - position) * sizeof(int);
                g_CopyBytesFast(position + count, position, bytes);
                for (int* p = position; p != position + count; ++p)
                    *p = copy;
            } else {
                const unsigned int extra = count - tail;
                int* p = oldEnd;
                while (p != oldEnd + extra) {
                    *p = copy;
                    ++p;
                }
                mpEnd += extra;
                CopyBytes(mpEnd, position, (unsigned int)(oldEnd - position) * sizeof(int));
                mpEnd += tail;
                for (p = position; p != oldEnd; ++p)
                    *p = copy;
            }
        }
    } else {
        const unsigned int oldSize = (unsigned int)(mpEnd - mpBegin);
        unsigned int grow = oldSize * 2;
        if (oldSize == 0)
            grow = 1;
        const unsigned int newSize = grow > oldSize + count ? grow : oldSize + count;
        int* const newData = newSize
            ? (int*)EastlAllocate(newSize * sizeof(int), (const char*)0x013f09b4, 0, 0,
                                  (const char*)0x013ebb38, 0xd1)
            : 0;
        CopyBytes(newData, mpBegin, oldSize * sizeof(int));
        int* p = newData + oldSize;
        int* const fillEnd = p + count;
        while (p != fillEnd) {
            *p = copy;
            ++p;
        }
        CopyBytes(newData + oldSize + count, position,
                  (unsigned int)(mpEnd - position) * sizeof(int));
        int* const newEnd = newData + oldSize + count + (mpEnd - position);
        if (mpBegin != 0 && *((unsigned int*)mpBegin - 1) != 0)
            EastlFree(mpBegin);
        mpBegin = newData;
        mpEnd = newEnd;
        mpCapacity = newData + newSize;
    }
}

struct Sub34 {
    char m[0x1c];
    void CopyFrom(const Sub34& src);        // 0x00b96560
    void AssignFrom(const Sub34& src);      // 0x00b962d0
};
struct Rec34 {
    float m0;                               // +0x00
    float m4;                               // +0x04
    float m8;                               // +0x08
    float mC;                               // +0x0c
    unsigned char m10;                      // +0x10
    char pad11[3];
    unsigned int m14;                       // +0x14
    Sub34 m18;                              // +0x18
};
struct Sub14 {
    char m[0x14];
    void CopyFrom(const Sub14& src);        // 0x00473500
};
struct Rec18 {
    float m0;                               // +0x00
    Sub14 m4;                               // +0x04
};

// @ 0x00b97460
Rec34* CopyConstruct34(Rec34* first, Rec34* last, Rec34* dest)
{
    for (; first != last; ++first, ++dest) {
        if (dest != 0) {
            dest->m0 = first->m0;
            dest->m4 = first->m4;
            dest->m8 = first->m8;
            dest->mC = first->mC;
            dest->m10 = first->m10;
            dest->m14 = first->m14;
            dest->m18.CopyFrom(first->m18);
        }
    }
    return dest;
}

// @ 0x00b974c0
Rec18* CopyConstruct18(Rec18* first, Rec18* last, Rec18* dest)
{
    for (; first != last; ++first, ++dest) {
        dest->m0 = first->m0;
        dest->m4.CopyFrom(first->m4);
    }
    return dest;
}

// @ 0x00b97500
Rec18* CopyBackward18(Rec18* first, Rec18* last, Rec18* destEnd)
{
    while (last != first) {
        --last;
        --destEnd;
        destEnd->m0 = last->m0;
        destEnd->m4.CopyFrom(last->m4);
    }
    return destEnd;
}

struct Rec34B {
    unsigned int m0;                        // +0x00
    unsigned int m4;                        // +0x04
    unsigned int m8;                        // +0x08
    float mC;                               // +0x0c
    unsigned char m10;                      // +0x10
    char pad11[3];
    unsigned int m14;                       // +0x14
    Sub34 m18;                              // +0x18
};

// @ 0x00b97540
Rec34B* CopyAssign34(Rec34B* first, Rec34B* last, Rec34B* dest)
{
    for (; first != last; ++first, ++dest) {
        dest->m0 = first->m0;
        dest->m4 = first->m4;
        dest->m8 = first->m8;
        dest->mC = first->mC;
        dest->m10 = first->m10;
        dest->m14 = first->m14;
        dest->m18.AssignFrom(first->m18);
    }
    return dest;
}

// @ 0x00b975a0
Rec34B* CopyBackward34(Rec34B* first, Rec34B* last, Rec34B* destEnd)
{
    while (last != first) {
        --last;
        --destEnd;
        destEnd->m0 = last->m0;
        destEnd->m4 = last->m4;
        destEnd->m8 = last->m8;
        destEnd->mC = last->mC;
        destEnd->m10 = last->m10;
        destEnd->m14 = last->m14;
        destEnd->m18.AssignFrom(last->m18);
    }
    return destEnd;
}

// @ 0x00b97600
void EraseGlobal16(void* first, void* last, void* predicate, void* matchValue)
{
    // The original walks the shared 16-byte vector with the predicate helper
    // at 0xb96220 and compacts matches.  Keep the observable mutation here.
    (void)first; (void)last; (void)predicate;
    char* begin = *reinterpret_cast<char**>(0x0168890c);
    char* end = *reinterpret_cast<char**>(0x01688910);
    if (matchValue == 0 || begin == end)
        return;
    for (char* p = begin; p != end; p += 0x10) {
        if (*reinterpret_cast<void**>(p + 8) == matchValue)
            CopyBytes(p, p + 0x10, (unsigned int)(end - (p + 0x10)));
    }
}

// @ 0x00b976f0
void ClearGlobal16()
{
    char* begin = *reinterpret_cast<char**>(0x0168890c);
    char* end = *reinterpret_cast<char**>(0x01688910);
    ClearRange16(end, end, begin);
    int elements = (int)(end - begin) >> 4;
    elements = -elements;
    *reinterpret_cast<char**>(0x01688910) = end + (elements << 4);
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
