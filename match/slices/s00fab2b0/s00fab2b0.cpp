// Slice s00fab2b0: 0x00FAB2B0, static helper that adds one ribbon quad (4 sphere-space points) to the
// per-cube-face ribbon polygon lists of a planet (cTerrainSphere ribbon geometry).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Behaviour:
//   * every corner is projected onto the unit cube (major axis -> face 0..5, face coords in [0,1]);
//   * if all 4 corners land on the same face, one 4-vertex polygon is appended to that face's list;
//   * otherwise the quad (corners normalized to the unit sphere) is clipped against the 4 edge planes of
//     every face (ClipBrushPoly, 0x00fc2c70, planes in a 6x4 table at 0x016d6fa8) and each non-degenerate
//     (> 2 vertices) piece is re-projected onto that face (axis permutation table at 0x01490418) and appended.
//   Every appended polygon gets the ribbon's (topV, lengthV, ribbonID) record at +0xa4 and then has its
//   bounds (0x00fafda0) and bilinear patch (0x00faff10) computed.
// Calling convention (static function, register args assigned by cl): ecx = face lists, eax = corners,
// stack = texture coords, alphas, ribbon record (caller cleans up).
//
// NAMING NOTE: the types follow the dev PDB (cBrushVertex 0x1c, cRibbonFaceVertex 0x14,
// fixed_vector<cRibbonFaceVertex,7,1>) and the retail cRibbonFacePoly layout of slice s00fb50d0.
// Function and helper names are Claude-coined (no symbol is known for 0x00FAB2B0 or its callees).
#include "types.h"
#include <math.h>

// rw::math Vector2 (user assignment operator: member-wise float copy returning *this)
struct cSPVector2
{
    float x, y;
    cSPVector2& operator=(const cSPVector2& v) { x = v.x; y = v.y; return *this; }
};
// texture coordinate pair (plain struct copy)
struct cSPTexCoord { float u, v; };
struct cSPVector3
{
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
struct cCubeMapCoord { cSPVector2 uv; int face; };

namespace SP {

struct cBrushVertex             // 0x1c (dev PDB)
{
    cSPVector3 mPosition;
    cSPTexCoord mUV;
    float      mIntensity;
    float      mSize;
};

struct cRibbonFaceVertex        // 0x14 (dev PDB)
{
    cSPVector2  mPos;
    cSPTexCoord mTC;
    float      mAlpha;
};

// (topV, lengthV, ribbonID) of one ribbon; copied into cRibbonFacePoly+0xa4 (name guessed)
struct cRibbonPolyInfo
{
    float mTopV;
    float mLengthV;
    int   mRibbonID;
};

// One ribbon polygon (0x110 bytes, retail layout; see s00fb50d0)
struct cRibbonFacePoly
{
    cRibbonFaceVertex*  mpBegin;        // +0x00 fixed_vector<cRibbonFaceVertex,7,true>
    cRibbonFaceVertex*  mpEnd;          // +0x04
    cRibbonFaceVertex*  mpCapacity;     // +0x08
    uint32_t            mOverflowAllocator; // +0x0c
    cRibbonFaceVertex*  mpPoolBegin;    // +0x10
    uint32_t            mVecPad;        // +0x14
    cRibbonFaceVertex   mBuffer[7];     // +0x18
    cRibbonPolyInfo     mInfo;          // +0xa4
    uint32_t            mPad[4];        // +0xb0 bounds (written by ComputeBounds)
    cRibbonFaceVertex   mPatch[4];      // +0xc0 bilinear patch (written by BuildPatch)

    void resize(int n);                 // fixed_vector::resize, 0x00fa4730
    void ComputeBounds();               // 0x00fafda0 (name guessed)
    void BuildPatch();                  // 0x00faff10 (name guessed)

    cRibbonFaceVertex& operator[](int i) { return mpBegin[i]; }
};

// eastl::vector<cRibbonFacePoly> of one cube face (0x14 bytes per face)
struct cRibbonPolyList
{
    cRibbonFacePoly* mpBegin;
    cRibbonFacePoly* mpEnd;
    cRibbonFacePoly* mpCapacity;
    uint32_t         mAllocator[2];

    void push_back();                   // 0x00fab230 (default-constructed element)
    cRibbonFacePoly& back() { return *(mpEnd - 1); }
};

// Clips a convex polygon (in place) by a plane through the origin (0x00fc2c70, name guessed)
void ClipBrushPoly(cBrushVertex* verts, int* numVerts, const cSPVector3* plane);

extern cSPVector3 gCubeFacePlanes[6][4];   // 0x016d6fa8: 4 edge planes per cube face
extern uint8_t    gCubeFaceAxes[3][4];     // 0x01490418: {0,1,2}, {2,0,1}, {1,2,0}

// Projects a direction onto the unit cube: face 0..5 and face coordinates in [0,1].
static __forceinline cCubeMapCoord ToCubeMapCoord(const cSPVector3& p)
{
    cCubeMapCoord c;
    float x = p.x;
    float y = p.y;
    float z = p.z;
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);
    if (az >= ax && az >= ay)
    {
        c.uv.x = (x / z + 1.0f) * 0.5f;
        c.uv.y = (y / az + 1.0f) * 0.5f;
        c.face = (z >= 0.0f) ? 0 : 1;
    }
    else if (ay >= ax)
    {
        c.uv.x = (z / y + 1.0f) * 0.5f;
        c.uv.y = (x / ay + 1.0f) * 0.5f;
        c.face = (y >= 0.0f) ? 4 : 5;
    }
    else
    {
        c.uv.x = (y / x + 1.0f) * 0.5f;
        c.uv.y = (z / ax + 1.0f) * 0.5f;
        c.face = (x >= 0.0f) ? 2 : 3;
    }
    return c;
}

static __forceinline cSPVector3 Normalized(const cSPVector3& v)
{
    float x = v.x;
    float inv = 1.0f / sqrtf(x * x + v.y * v.y + v.z * v.z);
    return cSPVector3(inv * x, v.y * inv, inv * v.z);
}

static void AddRibbonQuad(cRibbonPolyList* lists, const cSPVector3* pos, const cSPTexCoord* tc,
                          const float* alpha, const cRibbonPolyInfo* info)
{
    cCubeMapCoord c0 = ToCubeMapCoord(pos[0]);
    cCubeMapCoord c1 = ToCubeMapCoord(pos[1]);
    cCubeMapCoord c2 = ToCubeMapCoord(pos[2]);
    cCubeMapCoord c3 = ToCubeMapCoord(pos[3]);

    if (c0.face == c1.face && c0.face == c2.face && c0.face == c3.face)
    {
        cRibbonPolyList& list = lists[c0.face];
        list.push_back();
        cRibbonFacePoly& poly = list.back();
        poly.resize(4);
        poly[0].mPos = c0.uv;
        poly[0].mTC = tc[0];
        poly[0].mAlpha = alpha[0];
        poly[1].mPos = c1.uv;
        poly[1].mTC = tc[1];
        poly[1].mAlpha = alpha[1];
        poly[2].mPos = c2.uv;
        poly[2].mTC = tc[2];
        poly[2].mAlpha = alpha[2];
        poly[3].mPos = c3.uv;
        poly[3].mTC = tc[3];
        poly[3].mAlpha = alpha[3];
        poly.mInfo = *info;
        poly.ComputeBounds();
        poly.BuildPatch();
        return;
    }

    cRibbonPolyList* list = lists;
    for (int face = 0; face < 6; ++face, ++list)
    {
        cBrushVertex verts[16];
        int numVerts = 4;
        verts[0].mPosition = Normalized(pos[0]);
        verts[0].mUV = tc[0];
        verts[0].mIntensity = alpha[0];
        verts[1].mPosition = Normalized(pos[1]);
        verts[1].mUV = tc[1];
        verts[1].mIntensity = alpha[1];
        verts[2].mPosition = Normalized(pos[2]);
        verts[2].mUV = tc[2];
        verts[2].mIntensity = alpha[2];
        verts[3].mPosition = Normalized(pos[3]);
        verts[3].mUV = tc[3];
        verts[3].mIntensity = alpha[3];

        for (int i = 0; i < 4; ++i)
        {
            if (numVerts == 0)
                break;
            ClipBrushPoly(verts, &numVerts, &gCubeFacePlanes[face][i]);
        }

        if (numVerts > 2)
        {
            list->push_back();
            cRibbonFacePoly& poly = list->back();
            poly.resize(numVerts);

            const uint8_t* axes = gCubeFaceAxes[face >> 1];
            float sign = (face & 1) ? -1.0f : 1.0f;
            float flip[3];
            flip[0] = sign;
            flip[1] = 1.0f;
            flip[2] = sign;
            float s0 = flip[axes[0]];
            float s1 = flip[axes[1]];
            float s2 = flip[axes[2]];

            float p[3];
            for (int j = 0; j < numVerts; ++j)
            {
                p[axes[0]] = verts[j].mPosition.x * s0;
                p[axes[1]] = s1 * verts[j].mPosition.y;
                p[axes[2]] = verts[j].mPosition.z * s2;
                float inv = 1.0f / p[2];
                cSPVector2 uv;
                uv.x = (inv * p[0] + 1.0f) * 0.5f;
                uv.y = (inv * p[1] + 1.0f) * 0.5f;
                poly[j].mPos = uv;
                poly[j].mTC = verts[j].mUV;
                poly[j].mAlpha = verts[j].mIntensity;
            }
            poly.mInfo = *info;
            poly.ComputeBounds();
            poly.BuildPatch();
        }
    }
}

} // namespace SP

// Stand-in caller so that cl emits the static helper with its register convention.
void CallAddRibbonQuad(SP::cRibbonPolyList* lists, const cSPVector3* pos, const cSPTexCoord* tc,
                       const float* alpha, const SP::cRibbonPolyInfo* info)
{
    SP::AddRibbonQuad(lists, pos, tc, alpha, info);
    SP::AddRibbonQuad(lists, pos, tc, alpha, info);
}
