// SP::cTerrainSphereQuad::BuildRibbonVerts @ 0x00fb50d0  (/O2 /MD /Gy /TP /arch:SSE, no /EHsc)
//
// Retail rewrite of the 2008 dev-build BuildRibbonVerts (dev 0x012e68d0, which clipped the ribbon polygons with
// SplitPolysByLine). The retail version rasterizes every ribbon polygon onto the quad's chunk grid instead:
//   * the polygons arrive sorted by ribbon id; all polygons of one ribbon are scan-converted row by row into a
//     function-static grid of cells (4 vertices + "inside" flags each), interpolating texture coordinates and
//     alpha across each row from the polygon's bilinear patch (InterpolateRibbonPoly, 0x00fafb50);
//   * when the ribbon id changes (or the list ends) the touched cells are flushed: their grid-corner positions
//     (CalcMorphedPoint) and normals (normal map) are resolved once per grid point in a second static grid,
//     and each cell emits two triangles (corners 0,1,2 / 1,3,2) into mRibbonVerts.
// Caller: RebuildRibbonVerts (0x00fb6660) passes this+0x18c after clearing mRibbonVerts (this+0x1a0).
// Layouts follow the dev PDB (cTerrainSphereQuad, cRibbonUnmorphedVert, cRibbonFaceVertex) shifted to the
// retail offsets seen in the binary.
#include "types.h"
#include <xmmintrin.h>
#include <new>
#include <float.h>

struct cSPVector2 { float x, y; };
struct cSPVector3 { float x, y, z; };
struct cSPVector4 { float x, y, z, w; };
struct cCubeMapCoord { float u, v; int face; };

namespace SP {

struct cRibbonFaceVertex        // 0x14
{
    cSPVector2 mPos;
    cSPVector2 mTC;
    float      mAlpha;
};

struct cRibbonUnmorphedVert     // 0x30
{
    cSPVector3 mPos[2];         // +0x00 eastl::pair<cSPVector3,cSPVector3> (morphed, unmorphed)
    cSPVector3 mNorm;           // +0x18
    uint32_t   mColor;          // +0x24
    cSPVector2 mTex;            // +0x28
};

struct cMorphedPoint { cSPVector3 first, second; };   // eastl::pair<cSPVector3,cSPVector3>

// eastl::vector<T, sp_vector_allocator>
template <class T>
struct SPVector
{
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator;

    SPVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SPVector();
    int  size() const { return (int)(mpEnd - mpBegin); }
    T&   operator[](int i) { return mpBegin[i]; }
    void resize(int n);                         // sCells: 0x00fb4c10, sPoints: 0x00fb42d0
    void reserve(int n);                        // mRibbonVerts: 0x00fb37d0
    T*   DoInsertValue(T* position, const T& value);   // mRibbonVerts: 0x00fb3880
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new ((void*)mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

// eastl::fixed_vector<cSPVector2, 7, true> (local, overflow to the heap)
struct FixedVector2x7
{
    cSPVector2* mpBegin;
    cSPVector2* mpEnd;
    cSPVector2* mpCapacity;
    uint32_t    mOverflowAllocator;
    cSPVector2* mpPoolBegin;
    uint32_t    mPad;
    cSPVector2  mBuffer[7];

    FixedVector2x7() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 7), mpPoolBegin(mBuffer) {}
    ~FixedVector2x7()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    cSPVector2& operator[](int i) { return mpBegin[i]; }
    cSPVector2* DoInsertValue(cSPVector2* position, const cSPVector2& value);   // 0x00fb3320
    void push_back(const cSPVector2& value)
    {
        if (mpEnd < mpCapacity)
            ::new ((void*)mpEnd++) cSPVector2(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

// One ribbon polygon as stored in the quad's ribbon geometry (0x110 bytes).
struct cRibbonFacePoly
{
    cRibbonFaceVertex*  mpBegin;        // +0x00 fixed_vector<cRibbonFaceVertex,7>
    cRibbonFaceVertex*  mpEnd;          // +0x04
    uint32_t            mVecPad[39];    // rest of the fixed_vector (+0x08 .. +0xa4)
    float               mTopV;          // +0xa4 texture v of the ribbon's leading edge
    float               mLengthV;       // +0xa8 visible v range below mTopV
    int                 mRibbonID;      // +0xac
    uint32_t            mPad[4];        // +0xb0
    cRibbonFaceVertex   mPatch[4];      // +0xc0 bilinear patch read by InterpolateRibbonPoly
};

template <class T> struct cTerrainMap
{
    cSPVector4 GetVector4(const cCubeMapCoord& coord) const;   // cTerrainMap<unsigned int>: 0x00f89e50
};

struct cTerrainMapSet
{
    uint32_t                    mPad[3];
    cTerrainMap<unsigned int>*  mNormalMap;     // +0xc
};

struct cTerrainSphereInfo
{
    uint32_t   mPad[0x59c / 4];
    cSPVector3 mRibbonColor;                    // +0x59c
};

struct cTerrainSphere
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual cTerrainMapSet*     GetMapSet();    // +0xc
    virtual cTerrainSphereInfo* GetInfo();      // +0x10
};

// Static cell / grid-point caches.
struct RibbonCell                               // 200 bytes
{
    cRibbonUnmorphedVert mVerts[4];             // +0x00
    bool                 mInside[4];            // +0xc0
    bool                 mUsed;                 // +0xc4
};

struct RibbonGridPoint                          // 0x28 bytes
{
    cMorphedPoint mPos;                         // +0x00
    cSPVector3    mNorm;                        // +0x18
    bool          mValid;                       // +0x24
};

extern cSPVector3 gRibbonNormalBias;            // 0x015b1550 (1,1,1)

// bilinear interpolation of the polygon's patch at a face position (0x00fafb50)
cRibbonFaceVertex InterpolateRibbonPoly(const cRibbonFacePoly& poly, const cSPVector2& facePos);

static inline int FloatToInt(float f) { return _mm_cvtss_si32(_mm_set_ss(f)); }
static inline int FloorToInt(float f)
{
    int i = FloatToInt(f);
    if (f < (float)i) i = i - 1;
    return i;
}
static inline int CeilToInt(float f)
{
    int i = FloatToInt(f);
    if ((float)i < f) i = i + 1;
    return i;
}
template <class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

static int sCachedRes = -1;     // 0x015b1594
static int sCellRes   = -1;     // 0x015b1590 (cells per side)
static int sPointRes  = -1;     // 0x015b158c (grid points per side)

class cTerrainSphereQuad
{
public:
    cTerrainSphere*                 mSphere;            // +0x0
    uint32_t                        mPad04[5];
    int                             mChunkRes;          // +0x18
    int                             mFace;              // +0x1c
    cSPVector2                      mFaceMin;           // +0x20
    cSPVector2                      mFaceMax;           // +0x28
    float                           mFaceScale;         // +0x30
    uint32_t                        mPad34[0x5b];
    SPVector<cRibbonUnmorphedVert>  mRibbonVerts;       // +0x1a0

    cMorphedPoint CalcMorphedPoint(int x, int y) const;   // 0x00fb2400

    // grid coordinates -> face coordinates
    cSPVector2 GridToFace(float gx, float gy) const
    {
        const float inv = 1.0f / (float)mChunkRes;
        cSPVector2 r;
        r.x = (gx * inv) * mFaceScale + mFaceMin.x;
        r.y = mFaceMin.y + mFaceScale * (inv * gy);
        return r;
    }

    void BuildRibbonVerts(const SPVector<cRibbonFacePoly>& polys);
};

// @ 0x00fb50d0
void cTerrainSphereQuad::BuildRibbonVerts(const SPVector<cRibbonFacePoly>& polys)
{
    if (polys.mpBegin == polys.mpEnd)
        return;

    static SPVector<RibbonCell>      sCells;
    static SPVector<RibbonGridPoint> sPoints;

    if (mChunkRes != sCachedRes)
    {
        sCachedRes = mChunkRes;
        sCellRes = mChunkRes;
        sCells.resize(mChunkRes * mChunkRes);
        sPointRes = mChunkRes + 1;
        sPoints.resize(sPointRes * sPointRes);
    }
    for (unsigned i = 0; i < (unsigned)sCells.size(); i++)
        sCells[i].mUsed = false;
    for (unsigned i = 0; i < (unsigned)sPoints.size(); i++)
        sPoints[i].mValid = false;

    const cTerrainMap<unsigned int>* normalMap = mSphere->GetMapSet()->mNormalMap;
    int curRibbon = -1;
    int numCells = 0;

    int r = FloatToInt(mSphere->GetInfo()->mRibbonColor.x * 255.0f);
    int g = FloatToInt(mSphere->GetInfo()->mRibbonColor.y * 255.0f);
    int b = FloatToInt(mSphere->GetInfo()->mRibbonColor.z * 255.0f);
    if (r < 0) r = 0;
    if (r > 255) r = 255;
    if (g < 0) g = 0;
    if (g > 255) g = 255;
    if (b < 0) b = 0;
    if (b > 255) b = 255;
    const uint32_t rgb = (uint32_t)((((b << 8) | g) << 8) | r);

    // row interpolants (tc.u, tc.v, alpha) carried from one row's lower edge to the next row's upper edge
    float upU, upV, upA, upStepU, upStepV, upStepA;
    float loU, loV, loA, loStepU, loStepV, loStepA;

    for (const cRibbonFacePoly* poly = polys.mpBegin; ; ++poly)
    {
        if (poly == polys.mpEnd || curRibbon != poly->mRibbonID)
        {
            if (curRibbon != -1 && numCells > 0)
            {
                // flush the finished ribbon: two triangles per touched cell
                mRibbonVerts.reserve(mRibbonVerts.size() + numCells * 6);
                const int kTriCorners[6] = { 0, 1, 2, 1, 3, 2 };
                for (int row = 0; row < sCellRes; row++)
                {
                    for (int col = 0; col < sCellRes; col++)
                    {
                        RibbonCell& cell = sCells[row * sCellRes + col];
                        if (!cell.mUsed)
                            continue;
                        int rows[4], cols[4];
                        cols[0] = col; cols[2] = col; cols[1] = col + 1; cols[3] = col + 1;
                        rows[0] = row; rows[1] = row; rows[2] = row + 1; rows[3] = row + 1;
                        for (int i = 0; i < 4; i++)
                        {
                            const int pr = rows[i];
                            const int pc = cols[i];
                            RibbonGridPoint& pt = sPoints[pr * sPointRes + pc];
                            if (!pt.mValid)
                            {
                                const cSPVector2 facePos = GridToFace((float)pc, (float)pr);
                                pt.mPos = CalcMorphedPoint(pc, pr);
                                cCubeMapCoord coord;
                                coord.u = facePos.x;
                                coord.v = facePos.y;
                                coord.face = mFace;
                                const cSPVector4 n = normalMap->GetVector4(coord);
                                pt.mNorm.x = n.x * 2.0f - gRibbonNormalBias.x;
                                pt.mNorm.y = n.y * 2.0f - gRibbonNormalBias.y;
                                pt.mNorm.z = n.z * 2.0f - gRibbonNormalBias.z;
                                pt.mValid = true;
                            }
                        }
                        for (int k = 0; k < 6; k++)
                        {
                            const int c = kTriCorners[k];
                            const RibbonGridPoint& pt = sPoints[rows[c] * sPointRes + cols[c]];
                            cRibbonUnmorphedVert& v = cell.mVerts[c];
                            v.mPos[0] = pt.mPos.first;
                            v.mPos[1] = pt.mPos.second;
                            v.mNorm = pt.mNorm;
                            mRibbonVerts.push_back(v);
                        }
                        cell.mUsed = false;
                    }
                }
                numCells = 0;
            }
            if (poly == polys.mpEnd)
                return;
            curRibbon = poly->mRibbonID;
        }
        if (poly == polys.mpEnd)
            return;

        const int numVerts = (int)(poly->mpEnd - poly->mpBegin);
        if (numVerts <= 2)
            continue;

        // polygon in grid coordinates
        FixedVector2x7 gridVerts;
        for (int i = 0; i < numVerts; i++)
        {
            const cRibbonFaceVertex& fv = poly->mpBegin[i];
            const float res = (float)mChunkRes;
            const float invScale = 1.0f / mFaceScale;
            cSPVector2 gp;
            gp.x = ((fv.mPos.x - mFaceMin.x) * invScale) * res;
            gp.y = res * (invScale * (fv.mPos.y - mFaceMin.y));
            gridVerts.push_back(gp);
        }

        float maxY = -1.0f;
        float minY = FLT_MAX;
        for (int i = 0; i < numVerts; i++)
        {
            maxY = Max(maxY, gridVerts[i].y);
            minY = Min(minY, gridVerts[i].y);
        }
        const int zero = 0;
        int lo = FloorToInt(minY);
        const int startRow = Max(lo, zero);
        int hi = CeilToInt(maxY);
        int lastPoint = sPointRes - 1;
        const int endRow = Min(hi, lastPoint);

        for (int y = startRow; y < endRow; y++)
        {
            // horizontal extent of the polygon over this row (with one row of slack)
            int minX = 0x40000000;
            int maxX = -1;
            for (int i = 0; i < numVerts; )
            {
                const cSPVector2& p0 = gridVerts[i];
                i++;
                const cSPVector2& p1 = gridVerts[i % numVerts];
                if ((p0.y > (float)(y - 1) || p1.y > (float)(y - 1)) &&
                    (p0.y < (float)(y + 1) || p1.y < (float)(y + 1)))
                {
                    const float dy = p1.y - p0.y;
                    if (dy == 0.0f)
                    {
                        int f1 = FloorToInt(p1.x);
                        int f0 = FloorToInt(p0.x);
                        minX = Min(f0, Min(f1, minX));
                        int c1 = CeilToInt(p1.x);
                        int c0 = CeilToInt(p0.x);
                        maxX = Max(Max(maxX, c1), c0);
                    }
                    else
                    {
                        float t = ((float)y - p0.y) / dy;
                        const float tMin = 0.0f;
                        const float tMax = 1.0f;
                        t = Min(Max(t, tMin), tMax);
                        const float x = (p1.x - p0.x) * t + p0.x;
                        int f = FloorToInt(x);
                        minX = Min(f, minX);
                        int c = CeilToInt(x);
                        maxX = Max(maxX, c);
                    }
                }
            }
            const int zeroX = 0;
            const int startCol = Max(minX, zeroX);
            int lastCol = sPointRes - 1;
            const int endCol = Min(maxX, lastCol);

            const float fRes = (float)(sPointRes - 1);
            const float invRes = 1.0f / fRes;
            if (y == startRow)
            {
                const float fy = (float)y;
                const cRibbonFaceVertex left = InterpolateRibbonPoly(*poly, GridToFace(0.0f, fy));
                const cRibbonFaceVertex right = InterpolateRibbonPoly(*poly, GridToFace(fRes, fy));
                upStepU = (right.mTC.x - left.mTC.x) * invRes;
                upStepV = invRes * (right.mTC.y - left.mTC.y);
                upU = left.mTC.x;
                upV = left.mTC.y;
                upA = left.mAlpha;
                upStepA = (right.mAlpha - left.mAlpha) * invRes;
            }
            else
            {
                upU = loU;
                upV = loV;
                upA = loA;
                upStepU = loStepU;
                upStepV = loStepV;
                upStepA = loStepA;
            }

            const float fy = (float)y;
            const float fy1 = fy + 1.0f;
            {
                const cRibbonFaceVertex left = InterpolateRibbonPoly(*poly, GridToFace(0.0f, fy1));
                const cRibbonFaceVertex right = InterpolateRibbonPoly(*poly, GridToFace(fRes, fy1));
                loStepU = (right.mTC.x - left.mTC.x) * invRes;
                loStepV = invRes * (right.mTC.y - left.mTC.y);
                loU = left.mTC.x;
                loV = left.mTC.y;
                loA = left.mAlpha;
                loStepA = (right.mAlpha - left.mAlpha) * invRes;
            }

            const float fx0 = (float)startCol;
            float curUpU = upU + upStepU * fx0;
            float curUpV = upV + fx0 * upStepV;
            float curLoU = loStepU * fx0 + loU;
            float curUpA = fx0 * upStepA + upA;
            float curLoV = fx0 * loStepV + loV;
            float curLoA = fx0 * loStepA + loA;

            for (int x = startCol; x < endCol; x++)
            {
                const int cornerX[4] = { 0, 1, 0, 1 };
                const int cornerY[4] = { 0, 0, 1, 1 };
                const float one = 1.0f;
                const float fx = (float)x;
                cRibbonUnmorphedVert verts[4];
                bool inside[4];

                for (int i = 0; i < 4; i++)
                {
                    const int dx = cornerX[i];
                    const int dy = cornerY[i];
                    float u, v, a;
                    if (dx)
                    {
                        if (dy) { u = curLoU + loStepU; v = curLoV + loStepV; a = curLoA + loStepA; }
                        else    { u = curUpU + upStepU; v = curUpV + upStepV; a = curUpA + upStepA; }
                    }
                    else
                    {
                        if (dy) { u = curLoU; v = curLoV; a = curLoA; }
                        else    { u = curUpU; v = curUpV; a = curUpA; }
                    }
                    // evaluated but unused in the retail build
                    InterpolateRibbonPoly(*poly, GridToFace((float)dx + fx, (float)dy + fy));

                    const float zeroA = 0.0f;
                    const float alpha = Min(Max(a, zeroA), one);
                    bool in = true;
                    if (v > poly->mTopV || v < poly->mTopV - poly->mLengthV)
                        in = false;
                    const int alphaByte = FloorToInt(alpha * 255.0f + 0.5f);
                    inside[i] = in;
                    verts[i].mColor = ((uint32_t)alphaByte << 24) | rgb;
                    verts[i].mTex.x = u;
                    verts[i].mTex.y = v;
                }

                RibbonCell& cell = sCells[y * sCellRes + x];
                if (!cell.mUsed)
                {
                    numCells++;
                    cell.mVerts[0] = verts[0]; cell.mInside[0] = inside[0];
                    cell.mVerts[1] = verts[1]; cell.mInside[1] = inside[1];
                    cell.mVerts[2] = verts[2]; cell.mInside[2] = inside[2];
                    cell.mUsed = true;
                    cell.mVerts[3] = verts[3]; cell.mInside[3] = inside[3];
                }
                else
                {
                    int count = cell.mInside[0] ? 1 : 0;
                    if (cell.mInside[1]) count++;
                    if (cell.mInside[2]) count++;
                    if (cell.mInside[3]) count++;
                    if (count < 4)
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            if (!cell.mInside[i] && inside[i])
                            {
                                cell.mVerts[i] = verts[i];
                                cell.mInside[i] = inside[i];
                            }
                        }
                    }
                }

                curUpU += upStepU;
                curUpV += upStepV;
                curLoU += loStepU;
                curLoV += loStepV;
                curUpA += upStepA;
                curLoA += loStepA;
            }
        }
    }
}

} // namespace SP
