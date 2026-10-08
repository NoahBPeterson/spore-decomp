// Slice s00fabd60: 0x00FABD60, builds the ribbon quads of one ribbon (a road/river-like strip drawn on the
// planet's terrain sphere) from its path points, then hands the per-cube-face polygon lists to the six face
// quads. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Behaviour (for every path point i, 0x24-byte points whose first three floats are a direction on the sphere):
//   * miter direction: the normalized cross products with the previous and next point (end points reuse the
//     point itself), summed; the corner cosine between the previous / next segments (clamped to
//     [-1, 0.999]; -1 at the end points) scales it by sqrt(2 / (1 - cos)) (6 units wide);
//   * the centre is the point normalized to radius 500;
//   * from the second point on one quad (centre -/+ offset of the previous and of this point) is appended with
//     AddRibbonQuad (0x00fab2b0): texture coordinates (+-1, running length), alpha ramping in at the first and
//     out at the last segment, info (running length, segment length, ribbonID);
//   * finally every non-null face quad (this+0x118 .. +0x12c) receives its polygon list (0x00fb7920) and the
//     six lists are destroyed.
// NAMING NOTE: no symbol is known for 0x00FABD60; names are Claude-coined. AddRibbonQuad and the polygon
// types and the AddRibbonQuad body (copied from slice s00fab2b0, kept static so cl gives it the same
// register convention) come from slice s00fab2b0.
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
void ClipBrushPoly(cBrushVertex* verts, int* numVerts, const cSPVector3* plane);   // 0x00fc2c70

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

// @ 0x00fab2b0
static __declspec(noinline) void AddRibbonQuad(cRibbonPolyList* lists, const cSPVector3* pos, const cSPTexCoord* tc,
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


// ---- slice s00fabd60 proper ----


namespace SP {

void __cdecl EASTL_allocator_deallocate(void* p);   // 0x00f47380

struct cRibbonPathPoint         // 0x24
{
    float x, y, z;
    float mPad[6];
};

struct cRibbonPath
{
    uint32_t           mPad;
    cRibbonPathPoint*  mpBegin;     // +0x04
    cRibbonPathPoint*  mpEnd;       // +0x08
};

// terrain quad of one cube face (this+0x18c holds its ribbon vertices; see s00fb50d0)
struct cFaceQuad
{
    void AddRibbonPolys(cRibbonPolyList* list);     // 0x00fb7920 (name guessed)
};

// eastl::vector<cRibbonFacePoly> destructor as inlined here
struct cLocalPolyList : cRibbonPolyList
{
    cLocalPolyList() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~cLocalPolyList()
    {
        for (cRibbonFacePoly* p = mpBegin; p < mpEnd; ++p)
        {
            if (p->mpBegin && p->mpBegin != p->mpPoolBegin)
                EASTL_allocator_deallocate(p->mpBegin);
        }
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
    }
};

struct cRibbonBuilder
{
    char       mPad[0x118];
    cFaceQuad* mFaceQuads[6];       // +0x118

    void BuildRibbon(int ribbonID, cRibbonPath* path);
};

// @ 0x00fabd60
void cRibbonBuilder::BuildRibbon(int ribbonID, cRibbonPath* path)
{
    cLocalPolyList lists[6];
    float runLen = 0.0f;
    int count = (int)(path->mpEnd - path->mpBegin);
    float prevCx = 0, prevCy = 0, prevCz = 0, prevOx = 0, prevOy = 0, prevOz = 0;

    for (int i = 0; i < count; ++i)
    {
        const cRibbonPathPoint* p = &path->mpBegin[i];
        const cRibbonPathPoint* pv = (i != 0) ? p - 1 : p;
        const cRibbonPathPoint* nx = (i != count - 1) ? p + 1 : p;

        float pvX = p->z * pv->y - p->y * pv->z;
        float pvY = p->x * pv->z - p->z * pv->x;
        float pvZ = p->y * pv->x - p->x * pv->y;
        float s0 = 1.0f / sqrtf(pvX * pvX + pvZ * pvZ + pvY * pvY + 1e-08f);
        float n0x = s0 * pvX;
        float n0y = pvY * s0;
        float n0z = pvZ * s0;

        float nxX = p->y * nx->z - p->z * nx->y;
        float nxY = p->z * nx->x - p->x * nx->z;
        float nxZ = p->x * nx->y - p->y * nx->x;
        float s1 = 1.0f / sqrtf(nxX * nxX + nxY * nxY + nxZ * nxZ + 1e-08f);

        float cosA;
        if (i == 0 || i == count - 1)
        {
            cosA = -1.0f;
        }
        else
        {
            float dnx = nx->x - p->x;
            float dny = nx->y - p->y;
            float dnz = nx->z - p->z;
            float dpx = pv->x - p->x;
            float dpy = pv->y - p->y;
            float dpz = pv->z - p->z;
            cosA = (dpx * dnx + (dpy * dny + dpz * dnz)) /
                   (sqrtf(dpz * dpz + dpy * dpy + dpx * dpx) * sqrtf(dnz * dnz + dny * dny + dnx * dnx));
            if (cosA <= -1.0f) cosA = -1.0f;
            if (cosA >= 0.999f) cosA = 0.999f;
        }

        float bx = s1 * nxX + n0x;
        float by = s1 * nxY + n0y;
        float bz = s1 * nxZ + n0z;

        float sp = 1.0f / sqrtf(p->y * p->y + (p->x * p->x + p->z * p->z));
        float cx = p->x * sp * 500.0f;
        float cy = sp * p->y * 500.0f;
        float cz = sp * p->z * 500.0f;

        float miter = sqrtf(2.0f / (1.0f - cosA));
        float sb = 1.0f / sqrtf(by * by + (bz * bz + bx * bx));
        float ox = sb * bx * miter * 6.0f;
        float oy = by * sb * miter * 6.0f;
        float oz = bz * sb * miter * 6.0f;

        if (i > 0)
        {
            float dx = cx - prevCx;
            float dy = cy - prevCy;
            float dz = cz - prevCz;
            float corners[12];
            corners[0] = prevCx - prevOx;
            corners[1] = prevCy - prevOy;
            corners[2] = prevCz - prevOz;
            corners[3] = prevOx + prevCx;
            corners[4] = prevOy + prevCy;
            corners[5] = prevOz + prevCz;
            corners[6] = ox + cx;
            corners[7] = oy + cy;
            corners[8] = oz + cz;
            corners[9] = cx - ox;
            corners[10] = cy - oy;
            corners[11] = cz - oz;
            float alpha[4];
            alpha[0] = (i == 1) ? 0.0f : 1.0f;
            alpha[1] = (i == 1) ? 0.0f : 1.0f;
            alpha[2] = (i == count - 1) ? 0.0f : 1.0f;
            alpha[3] = (i == count - 1) ? 0.0f : 1.0f;
            float startLen = runLen;
            runLen = sqrtf(dz * dz + (dy * dy + dx * dx)) + runLen;
            cSPTexCoord tc[4];
            tc[0].u = -1.0f; tc[0].v = startLen;
            tc[1].u = 1.0f;  tc[1].v = startLen;
            tc[2].u = 1.0f;  tc[2].v = runLen;
            tc[3].u = -1.0f; tc[3].v = runLen;
            cRibbonPolyInfo info;
            info.mTopV = runLen;
            info.mLengthV = sqrtf((dz * dz + dy * dy) + dx * dx);
            info.mRibbonID = ribbonID;
            AddRibbonQuad(lists, (const cSPVector3*)corners, tc, alpha, &info);
        }
        prevCx = cx; prevCy = cy; prevCz = cz;
        prevOx = ox; prevOy = oy; prevOz = oz;
    }

    for (int f = 0; f < 6; ++f)
    {
        if (mFaceQuads[f])
            mFaceQuads[f]->AddRibbonPolys(&lists[f]);
    }
}

} // namespace SP
