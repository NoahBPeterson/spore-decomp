// Slice s00b8aea0 -- FUN_00b8aea0, here SP::cPlanetModel::BuildPoliticalZoneMap (name coined:
// the PDB has no name for it). 3275 bytes.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the vector locals have no EH frame).
//
// Rebuilds mPoliticalZoneIdxMap, a 6 x 64 x 64 cube map (one byte per texel) that gives the political
// zone owning each texel of the planet:
//  * every political zone k >= 1 contributes its continent and its normalized center direction;
//  * a texel is "claimable" when it lies on a land continent (not flagged in mContinentFlags) of at
//    least 40 cells;
//  * starting from the texel under each zone center, the zones grow over the cube map in rounds
//    (cone half-angle iter * pi/16, iter = 3..16), flood-filling neighbors (WrapCubeFace across cube
//    edges) and marking texels with the zone bit;
//  * finally each texel takes the zone whose center direction is closest among the zones that
//    reached it (0 = none), then the zone geometry is rebuilt (0x00b8a760).
// Re-entrancy: a second call while one is running only records a pending request.
#include "types.h"
#include <math.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
};
inline void* operator new(size_t, void* p) throw() { return p; }

struct CubeCell { int x, y, face; };

struct random_access_iterator_tag {};

void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0

static const char kAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// eastl::allocator (named "Simulator") deallocate: the block carries its size before it.
inline void EASTLFree(void* p)
{
    if (p && ((int*)p)[-1] != 0)
        operator delete[](p);
}

// eastl::vector<CubeCell>
struct CubeCellVector {
    CubeCell* mpBegin;
    CubeCell* mpEnd;
    CubeCell* mpCapacity;
    uint32_t mAllocator[2];
    ~CubeCellVector() { EASTLFree(mpBegin); }
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    CubeCell& operator[](int i) { return mpBegin[i]; }
    CubeCellVector& operator=(const CubeCellVector& x);                // 0x00b375f0
    void swap(CubeCellVector& x);                                      // 0x00b85190
    void reserve(uint32_t n);                                          // 0x00b84a60
    void DoInsertValue(CubeCell* position, const CubeCell& value);     // 0x00b535d0
    void DoInsertFromIterator(CubeCell* position, CubeCell* first, CubeCell* last,
                              random_access_iterator_tag);             // 0x00b84cb0
    void push_back(const CubeCell& value)
    {
        if (mpEnd < mpCapacity) {
            ::new (mpEnd++) CubeCell(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
    void insert(CubeCell* position, CubeCell* first, CubeCell* last)
    {
        DoInsertFromIterator(position, first, last, random_access_iterator_tag());
    }
    CubeCell* erase(CubeCell* first, CubeCell* last)
    {
        CubeCell* const position = first;
        CubeCell* d = first;
        for (CubeCell* s = last; s != mpEnd; ++s, ++d)
            *d = *s;
        mpEnd -= (last - first);
        return position;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

// eastl::vector<eastl::vector<CubeCell>>
struct CubeCellVectorVector {
    CubeCellVector* mpBegin;
    CubeCellVector* mpEnd;
    CubeCellVector* mpCapacity;
    uint32_t mAllocator[2];
    CubeCellVectorVector(uint32_t n, const char& allocator);           // 0x00b85e10
    ~CubeCellVectorVector()
    {
        for (CubeCellVector* p = mpBegin; p < mpEnd; ++p)
            p->~CubeCellVector();
        EASTLFree(mpBegin);
    }
    CubeCellVector& operator[](int i) { return mpBegin[i]; }
};

// eastl::fixed_vector<uint32_t, 64>
struct FixedIDVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mOverflowAllocator;
    uint32_t* mpPoolBegin;
    uint32_t pad;
    uint32_t mBuffer[64];
    FixedIDVector()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 64;
    }
    ~FixedIDVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    void DoInsertValue(uint32_t* position, const uint32_t& value);     // 0x004281d0
    void push_back(const uint32_t& value)
    {
        if (mpEnd < mpCapacity) {
            ::new (mpEnd++) uint32_t(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};

// eastl::fixed_vector<Vector3, 64>
struct FixedVector3Vector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mOverflowAllocator;
    Vector3* mpPoolBegin;
    uint32_t pad;
    __declspec(align(16)) float mBuffer[64 * 3];
    FixedVector3Vector()
    {
        mpPoolBegin = (Vector3*)mBuffer;
        mpBegin = (Vector3*)mBuffer;
        mpEnd = (Vector3*)mBuffer;
        mpCapacity = (Vector3*)mBuffer + 64;
    }
    ~FixedVector3Vector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    void DoInsertValue(Vector3* position, const Vector3& value);       // 0x00ac4720
    void push_back(const Vector3& value)
    {
        if (mpEnd < mpCapacity) {
            ::new (mpEnd++) Vector3(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};

// eastl::vector<uint32_t> with the "Simulator" allocator, n zero-filled elements.
template <uint32_t n>
struct MaskVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    MaskVector()
    {
        mpBegin = (uint32_t*)new ("Simulator", 0, 0, kAllocatorFile, 0xd1) char[n * sizeof(uint32_t)];
        uint32_t* q = mpBegin;
        for (uint32_t i = n; i != 0; --i)
            *q++ = 0;
        mpEnd = mpBegin + n;
        mpCapacity = mpBegin + n;
    }
    ~MaskVector() { EASTLFree(mpBegin); }
};

namespace SP {
int WrapCubeFace(int size, int* face, int* x, int* y, int* rot, int* flip);   // 0x00684ca0
}

extern const unsigned char g_cubeFaceAxes[];   // 0x014653b8: 4 bytes per face pair

// Unit direction of the center of texel (x, y) of cube face <face> (64 x 64 faces).
__forceinline void CubeTexelDirection(int face, float fx, float fy, float* v)
{
    const unsigned char* axes = &g_cubeFaceAxes[(face >> 1) * 4];
    float inv = 1.0f / sqrtf(fx * fx + fy * fy + 1.0f);
    float s = inv;
    if (face & 1)
        s = -s;
    v[axes[0]] = s * fx;
    v[axes[1]] = inv * fy;
    v[axes[2]] = s;
}
inline float TexelCoord(int i) { return ((float)i + 0.5f) * 0.03125f - 1.0f; }

extern int g_PoliticalZoneUpdateCount;      // 0x016881e4
extern int g_PoliticalZoneUpdateBusy;       // 0x016881e8
extern int g_PoliticalZoneUpdatePending;    // 0x016881ec

namespace SP {

struct cPoliticalZone {
    uint32_t mPoliticalID;      // 0x00
    Vector3 mCenter;            // 0x04
    bool mCityZone;             // 0x10
    bool mVisible;              // 0x11
    uint32_t mpCity;            // 0x14
};

class cPlanetModel {
public:
    uint32_t pad00[0x50 / 4];
    uint32_t* mContinentAreasBegin;     // 0x50
    uint32_t* mContinentAreasEnd;       // 0x54
    uint32_t pad58[(0x64 - 0x58) / 4];
    bool* mContinentFlags;              // 0x64
    uint32_t pad68[(0x80 - 0x68) / 4];
    cPoliticalZone* mPoliticalZonesBegin;   // 0x80
    cPoliticalZone* mPoliticalZonesEnd;     // 0x84
    uint32_t pad88[(0x94 - 0x88) / 4];
    uint8_t* mPoliticalZoneIdxMap;      // 0x94

    int GetContinent(const Vector3* pos);   // 0x00b88590
    void RebuildPoliticalZones();           // 0x00b8a760
    void BuildPoliticalZoneMap();
};

void cPlanetModel::BuildPoliticalZoneMap()
{
    g_PoliticalZoneUpdateCount++;
    if (g_PoliticalZoneUpdateBusy) {
        g_PoliticalZoneUpdatePending = 1;
        return;
    }

    FixedIDVector continents;
    FixedVector3Vector directions;
    uint8_t* zoneMap = mPoliticalZoneIdxMap;
    int numZones = mPoliticalZonesEnd - mPoliticalZonesBegin;
    g_PoliticalZoneUpdatePending = 0;
    g_PoliticalZoneUpdateBusy = 1;
    continents.push_back(0);
    directions.push_back(Vector3(0.0f, 0.0f, 0.0f));

    for (int i = 1; i < numZones; i++) {
        continents.push_back(GetContinent(&mPoliticalZonesBegin[i].mCenter));
        Vector3 c = mPoliticalZonesBegin[i].mCenter;
        float inv = 1.0f / sqrtf(c.z * c.z + c.y * c.y + c.x * c.x + 1e-8f);
        Vector3 dir(inv * c.x, inv * c.y, inv * c.z);
        directions.push_back(dir);
    }

    // 1 = texel on a land continent big enough to hold a zone; zone bits are or'ed in later.
    MaskVector<6 * 64 * 64> mask;
    uint32_t* p = mask.mpBegin;
    for (int face = 0; face < 6; face++) {
        for (int y = 0; y < 64; y++) {
            float fy = TexelCoord(y);
            for (int x = 0; x < 64; x++) {
                float v[3];
                CubeTexelDirection(face, TexelCoord(x), fy, v);
                int continent = GetContinent((const Vector3*)v);
                bool land = mContinentFlags[continent] == 0;
                uint32_t area = (continent >= 0 && continent < (int)(mContinentAreasEnd - mContinentAreasBegin))
                                    ? mContinentAreasBegin[continent] : 0;
                *p++ = (land && area >= 40) ? 1 : 0;
            }
        }
    }

    {
        char allocator;
        CubeCellVectorVector frontier(numZones, allocator);
        CubeCellVectorVector pending(numZones, allocator);
        frontier[0].reserve(100);
        for (int i = 1; i < numZones; i++) {
            frontier[i].reserve(100);
            pending[i].reserve(100);
            const Vector3& d = directions.mpBegin[i];
            float ax = fabs(d.x);
            float ay = fabs(d.y);
            float az = fabs(d.z);
            CubeCell cell;
            if (az >= ax && az >= ay) {
                cell.x = (int)((d.x / d.z + 1.0f) * 32.0f);
                cell.y = (int)((d.y / az + 1.0f) * 32.0f);
                cell.face = (d.z >= 0.0f) ? 0 : 1;
            } else if (ay >= ax) {
                cell.x = (int)((d.z / d.y + 1.0f) * 32.0f);
                cell.y = (int)((d.x / ay + 1.0f) * 32.0f);
                cell.face = (d.y >= 0.0f) ? 4 : 5;
            } else {
                cell.x = (int)((d.y / d.x + 1.0f) * 32.0f);
                cell.y = (int)((d.z / ax + 1.0f) * 32.0f);
                cell.face = (d.x >= 0.0f) ? 2 : 3;
            }
            if (cell.x == 64)
                cell.x = 63;
            if (cell.y == 64)
                cell.y = 63;
            pending[i].push_back(cell);
        }

        for (int iter = 3; iter <= 16; iter++) {
            float cosLimit = cosf(3.14159274f * 0.0625f * iter);
            for (int i = 1; i < numZones; i++) {
                frontier[i] = pending[i];
                pending[i].clear();
            }
            bool changed;
            do {
                changed = false;
                uint32_t bit = 2;
                for (int i = 1; i < numZones; i++, bit <<= 1) {
                    CubeCellVector& cells = frontier[i];
                    int count = cells.size();
                    for (int j = 0; j < count; j++) {
                        CubeCell& c = cells[j];
                        int x = c.x;
                        int y = c.y;
                        int face = c.face;
                        float v[3];
                        CubeTexelDirection(face, TexelCoord(x), TexelCoord(y), v);
                        const Vector3& d = directions.mpBegin[i];
                        if (cosLimit > d.y * v[1] + d.z * v[2] + v[0] * d.x) {
                            pending[i].push_back(c);
                        } else {
                            uint32_t& m = mask.mpBegin[(face * 64 + y) * 64 + x];
                            uint32_t old = m;
                            m = old | bit;
                            if (old == 0) {
                                CubeCell neighbors[4];
                                neighbors[0].x = c.x - 1;
                                neighbors[0].y = c.y;
                                neighbors[0].face = c.face;
                                neighbors[1].x = c.x + 1;
                                neighbors[1].y = c.y;
                                neighbors[1].face = c.face;
                                neighbors[2].x = c.x;
                                neighbors[2].y = c.y - 1;
                                neighbors[2].face = c.face;
                                neighbors[3].x = c.x;
                                neighbors[3].y = c.y + 1;
                                neighbors[3].face = c.face;
                                for (int k = 0; k < 4; k++) {
                                    CubeCell& n = neighbors[k];
                                    if ((n.x | n.y) & ~63)
                                        WrapCubeFace(64, &n.face, &n.x, &n.y, 0, 0);
                                }
                                frontier[0].insert(frontier[0].mpEnd, neighbors, neighbors + 4);
                            }
                        }
                    }
                    if (!frontier[0].empty())
                        changed = true;
                    cells.swap(frontier[0]);
                    frontier[0].clear();
                }
            } while (changed);
        }
    }

    uint32_t* bits = mask.mpBegin;
    uint8_t* out = zoneMap;
    for (int face = 0; face < 6; face++) {
        for (int y = 0; y < 64; y++) {
            float fy = TexelCoord(y);
            for (int x = 0; x < 64; x++) {
                uint32_t zoneBits = *bits;
                float v[3];
                CubeTexelDirection(face, TexelCoord(x), fy, v);
                int best = 0;
                float bestDot = -1.0f;
                uint32_t bit = 2;
                for (int k = 1; k < numZones; k++, bit <<= 1) {
                    if (zoneBits & bit) {
                        const Vector3& d = directions.mpBegin[k];
                        float dot = d.y * v[1] + d.x * v[0] + d.z * v[2];
                        if (dot > bestDot) {
                            bestDot = dot;
                            best = k;
                        }
                    }
                }
                out[x] = (uint8_t)best;
                bits++;
            }
            out += 64;
        }
    }

    RebuildPoliticalZones();
}

}  // namespace SP
