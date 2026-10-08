// Slice s00b8a760: SP::cPlanetModel::RebuildPoliticalZones (name from the s00b8aea0 caller comment).
// 0x00B8A760, 1842 bytes. Called at the end of BuildPoliticalZoneMap, it turns the 6 x 64 x 64 political-zone
// byte map (+0x94) into the zone border graph the national-boundary builder walks:
//   1. radius = terrain radius (500.0 without a planet sphere);
//   2. the tile map (+0xf4, a hash map keyed by cube-map vertex x/y/face) is cleared and, for every cube
//      vertex whose four surrounding texels (WrapCubeFace across cube edges) do not all carry the same
//      zone, a node is inserted holding the unit direction of the vertex, the four zone ids and four
//      "edge is not a border" flags;
//   3. every node gets its final surface position: the average of the border-corner directions around
//      it (when exactly two edges are borders the vertex direction is weighted by 2), scaled by radius;
//   4. cNatlBoundsBuilder::Build (+0xa8) is run over the tile map.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc; x87 constants 1/32 and 1.0 stay on the FPU stack).
#include "types.h"
#include <math.h>

// ---- tile map (shared layout with s00b89a30) ---------------------------------------------
struct TileKey {
    int x, y, z;
};
struct Vec3 { float x, y, z; };
struct TileValue {              // node + 0x0c
    Vec3        mPos;           // +0x00
    signed char mLevel[4];      // +0x0c zone id per texel around the vertex
    bool        mDone[4];       // +0x10 edge is not a border
};
struct TileNode {
    TileKey     mKey;           // +0x00
    TileValue   mValue;         // +0x0c
    TileNode*   mpNext;         // +0x20
};
struct TileIterator {
    TileNode*  mpNode;
    TileNode** mpBucket;
    TileIterator() {}
    explicit TileIterator(TileNode** pBucket) : mpNode(*pBucket), mpBucket(pBucket)
    {
        if (!mpNode)
            increment_bucket();
    }
    void increment_bucket()
    {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    void increment()
    {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
};
struct TileMap {
    uint32_t   mUnk0;
    TileNode** mpBucketArray;   // +4
    uint32_t   mnBucketCount;   // +8
    uint32_t   mnElementCount;  // +0xc
    TileValue& operator[](const TileKey& k);                              // 0xb85ca0
    void DoFreeNodes(TileNode** pBuckets, uint32_t n);                    // 0xb7f430
    TileNode* end_node() const { return mpBucketArray[mnBucketCount]; }
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
};

extern const unsigned char g_cubeFaceAxes[];   // 0x014653b8: 4 bytes per face pair

// @ 0x00b7e220: step a cube-map cell back onto its face (key = {x, y, face}); dx/dy, when given, are
// rotated with the cell. Defined here because the original TU lets the compiler see its register use.
__declspec(noinline) void __cdecl FUN_00b7e220(uint32_t size, TileKey* key, int* dx, int* dy)
{
    for (;;) {
        uint32_t face = (uint32_t)key->z;
        uint32_t sgn = (face & 1) - 1;
        uint32_t nsgn = ~sgn;
        int axis = (int)face >> 1;
        int flip = (int)((nsgn & 2) - 1);
        if (!((int)face >> 2 <= key->x)) {
            if (key->x > (int)(size - ((int)face >> 2))) {
                key->z = (nsgn & 1) + (uint32_t)g_cubeFaceAxes[axis * 4 + 1] * 2;
                int old = key->x;
                key->x = (int)(nsgn & size) - key->y * flip;
                key->y = (old - (int)size) * flip + (int)(sgn & size);
                if (dx != 0) {
                    int t = *dx;
                    *dx = -(*dy * flip);
                    *dy = t * flip;
                }
                continue;
            }
            int half = (axis + 1) >> 1;
            int ny;
            if (key->y < half) {
                key->z = (uint32_t)g_cubeFaceAxes[((int)face >> 1) * 4 + 2] * 2 + 1;
                ny = key->y + (int)size;
            } else {
                if (key->y <= (int)(size - half))
                    return;
                key->z = (uint32_t)g_cubeFaceAxes[((int)face >> 1) * 4 + 2] * 2;
                ny = key->y - (int)size;
            }
            int oldx = key->x;
            key->x = ny * flip + (int)(sgn & size);
            key->y = (int)(nsgn & size) - oldx * flip;
            if (dx != 0) {
                int t = *dx;
                *dx = *dy * flip;
                *dy = -(t * flip);
            }
            continue;
        }
        key->z = (sgn & 1) + (uint32_t)g_cubeFaceAxes[axis * 4 + 1] * 2;
        int nx = key->x + (int)size;
        int ny = key->y * flip + (int)(sgn & size);
        key->x = ny;
        key->y = (int)(nsgn & size) - nx * flip;
        if (dx != 0) {
            int t = *dx;
            *dx = *dy * flip;
            *dy = -(t * flip);
        }
    }
}

namespace SP { int __cdecl WrapCubeFace(int size, int* face, int* x, int* y, int a, int b); }   // 0x684ca0

struct CubeCell { int x, y, face; };

// Unit direction of the cube vertex (fx, fy) on <face>.
__forceinline void CubeVertexDirection(int face, float fx, float fy, float* v)
{
    const unsigned char* axes = &g_cubeFaceAxes[(face >> 1) * 4];
    float d = fy * fy; d += fx * fx; d += 1.0f; float inv = 1.0f / sqrtf(d);
    float s = inv;
    if (face & 1)
        s = -s;
    v[axes[0]] = s * fx;
    v[axes[1]] = inv * fy;
    v[axes[2]] = s;
}
inline float VertexCoord(int i) { return (float)i * 0.03125f - 1.0f; }

// ---- planet ----------------------------------------------------------------
struct cTerrainMapSet {
    char  pad00[0x34];
    float mRadius;      // +0x34
};
struct ISphere {
    virtual void a(); virtual void b(); virtual void c();
    virtual cTerrainMapSet* GetMap();           // slot 0xc
};
struct cNatlBoundsBuilder {
    void Build(TileMap* tiles);                 // 0xb89a30
};

namespace SP {

class cPlanetModel {
public:
    char     pad00[0x24];
    ISphere* mpISphere;                         // +0x24
    char     pad28[0x94 - 0x28];
    uint8_t* mPoliticalZoneIdxMap;              // +0x94
    char     pad98[0xa8 - 0x98];
    cNatlBoundsBuilder* mpNatlBoundsBuilder;    // +0xa8
    char     pada8[0xf4 - 0xac];
    TileMap  mTileMap;                          // +0xf4

    float GetRadius()
    {
        if (mpISphere != 0) {
            if (mpISphere->GetMap() != 0)
                return mpISphere->GetMap()->mRadius;
        }
        return 500.0f;
    }

    void RebuildPoliticalZones();               // 0x00b8a760
};

// @ 0x00B8A760
void cPlanetModel::RebuildPoliticalZones()
{
    float radius = GetRadius();
    uint8_t* zoneMap = mPoliticalZoneIdxMap;
    mTileMap.clear();

    for (int face = 0; face < 6; ++face) {
        int yMin = (face + 2) >> 2;
        int xMin = face >> 2;
        for (int y = yMin; y <= 0x40 - yMin; ++y) {
            for (int x = xMin; x <= 0x40 - xMin; ++x) {
                CubeCell cells[4];
                cells[0].x = x - 1; cells[0].y = y - 1; cells[0].face = face;
                cells[1].x = x;     cells[1].y = y - 1; cells[1].face = face;
                cells[2].x = x;     cells[2].y = y;     cells[2].face = face;
                cells[3].x = x - 1; cells[3].y = y;     cells[3].face = face;
                if ((cells[0].x | cells[0].y) & ~63)
                    WrapCubeFace(64, &cells[0].face, &cells[0].x, &cells[0].y, 0, 0);
                if ((cells[1].x | cells[1].y) & ~63)
                    WrapCubeFace(64, &cells[1].face, &cells[1].x, &cells[1].y, 0, 0);
                if ((cells[2].x | cells[2].y) & ~63)
                    WrapCubeFace(64, &cells[2].face, &cells[2].x, &cells[2].y, 0, 0);
                if ((cells[3].x | cells[3].y) & ~63)
                    WrapCubeFace(64, &cells[3].face, &cells[3].x, &cells[3].y, 0, 0);
                char c[4];
                c[0] = zoneMap[(cells[0].face * 64 + cells[0].y) * 64 + cells[0].x];
                c[1] = zoneMap[(cells[1].face * 64 + cells[1].y) * 64 + cells[1].x];
                c[2] = zoneMap[(cells[2].face * 64 + cells[2].y) * 64 + cells[2].x];
                c[3] = zoneMap[(cells[3].face * 64 + cells[3].y) * 64 + cells[3].x];
                if (c[0] != c[1] || c[0] != c[2] || c[0] != c[3]) {
                    TileKey wrapped;
                    wrapped.x = x; wrapped.y = y; wrapped.z = face;
                    FUN_00b7e220(64, &wrapped, 0, 0);
                    TileKey key;
                    key.x = x; key.y = y; key.z = face;
                    TileValue& value = mTileMap[key];
                    Vec3 pv;
                    CubeVertexDirection(face, VertexCoord(x), VertexCoord(y), &pv.x);
                    value.mPos = pv;
                    value.mLevel[0] = c[0];
                    value.mLevel[1] = c[1];
                    value.mLevel[2] = c[2];
                    value.mLevel[3] = c[3];
                    value.mDone[0] = c[3] == c[0];
                    value.mDone[1] = c[0] == c[1];
                    value.mDone[2] = c[1] == c[2];
                    value.mDone[3] = c[2] == c[3];
                }
            }
        }
    }

    for (TileIterator it(mTileMap.mpBucketArray); it.mpNode != mTileMap.end_node(); it.increment()) {
        TileNode* node = it.mpNode;
        float sx = 0.0f, sy = 0.0f, sz = 0.0f;
        int borders = 0;
        int prev = 3;
        for (int i = 0; i < 4; ++i) {
            if (node->mValue.mLevel[prev] != node->mValue.mLevel[i]) {
                TileKey key;
                uint32_t a = (i & 2) - 1;
                uint32_t b = (i & 1) - 1;
                key.x = node->mKey.x + (b & a);
                key.y = node->mKey.y + (~b & a);
                key.z = node->mKey.z;
                FUN_00b7e220(64, &key, 0, 0);
                float v[3];
                CubeVertexDirection(key.z, VertexCoord(key.x), VertexCoord(key.y), v);
                ++borders;
                sx = sx + v[0];
                sy = v[1] + sy;
                sz = v[2] + sz;
            }
            prev = i;
        }
        float d[3];
        CubeVertexDirection(node->mKey.z, VertexCoord(node->mKey.x), VertexCoord(node->mKey.y), d);
        if (borders == 2) {
            float wx = d[0] * 2.0f + sx;
            float wy = d[1] * 2.0f + sy;
            float wz = d[2] * 2.0f + sz;
            float inv = 1.0f / sqrtf(wx * wx + (wy * wy + wz * wz));
            node->mValue.mPos.x = inv * wx * radius;
            node->mValue.mPos.y = wy * inv * radius;
            node->mValue.mPos.z = wz * inv * radius;
        } else {
            node->mValue.mPos.x = d[0] * radius;
            node->mValue.mPos.y = d[1] * radius;
            node->mValue.mPos.z = d[2] * radius;
        }
    }

    mpNatlBoundsBuilder->Build(&mTileMap);
}

}  // namespace SP
