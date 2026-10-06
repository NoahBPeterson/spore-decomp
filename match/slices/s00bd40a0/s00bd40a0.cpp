// Slice s00bd40a0: the single function in this slice is
//   0x00BD40A0  cBuildingScenario::BuildFootprintRegions  (7678 bytes, __thiscall, no args)
//   (method name is Claude-coined; the class is Simulator::cBuildingScenario per ModAPI:
//    cBuilding is 0x340 bytes, cSpatialObject base at +0x34, vector at +0x344, Transform at +0x388.)
//
// What it does (Galactic Adventures scenario building):
//   1. clears the "regions valid" byte (+0x340) and the region vector (+0x344, 0xC64-byte records);
//   2. copies the model's transform into +0x388 and forces its scale to 1;
//   3. lays an n x n grid (n = min(ceil(d/2), 16), d = (footprint radius + 2) * 2) over the
//      building in the plane spanned by its direction and right vectors, snaps every grid point to
//      the planet surface (cPlanetModel 0x00B81630) and asks 0x00B52E00 which cells are free (1);
//   4. greedily merges free cells into rectangles (grid cells relabelled 2, 3, ...), one record per
//      rectangle bigger than a single cell, then one record per remaining single free cell; each
//      record gets a closed 5-point outline (snapped corner + sides), a radius and a centre;
//   5. moves every outline point into the local space of the +0x388 transform.
//
// Status: complete, not byte-exact (see nonmatching.txt). Same ordered call / vtable-slot /
// constant sequence as the original; size 7589 vs 7678. Remaining differences are register
// allocation, stack-slot layout (frame 0x19e4 vs 0x1a0c) and float scheduling.
// The label fill is a rep stosd in the original (written here with the __stosd intrinsic).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (movss/cvtsi2ss scalar SSE, x87 only for the
// sqrt/1/x of the normalize helper and the float return of GetFootprintRadius; no EH frame).
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
void operator delete[](void* p);                                         // 0x00f47380
extern "C" void* __cdecl memmove(void* dst, const void* src, size_t n);  // 0x011e0744 thunk
#include <math.h>

#pragma warning(disable:4035)
// EA math helper: hand-written SSE asm (as in the original).
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

extern "C" void __stosd(unsigned long* dest, unsigned long data, size_t count);
#pragma intrinsic(__stosd)

template<class T> __forceinline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template<class T> __forceinline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

// ---------------------------------------------------------------------------------------
// Math
struct Vector3 {
    float x, y, z;
    __forceinline Vector3() {}
    __forceinline Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    __forceinline Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    __forceinline Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    __forceinline Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
};

__forceinline Vector3 Normalized(const Vector3& v)
{
    float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + 1e-8f);
    return Vector3(v.x * inv, v.y * inv, v.z * inv);
}
__forceinline Vector3 Cross(const Vector3& a, const Vector3& b)
{
    return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - b.z * a.x, b.y * a.x - a.y * b.x);
}

struct Quaternion { float x, y, z, w; };

struct Matrix3 {
    Vector3 row[3];
    __forceinline Matrix3() {}
    Matrix3(const Matrix3& m);                                   // 0x0041cb40
    __forceinline Vector3 operator*(const Vector3& v) const
    {
        return Vector3(row[0].z * v.z + row[0].y * v.y + v.x * row[0].x,
                       row[1].z * v.z + row[1].y * v.y + row[1].x * v.x,
                       row[2].z * v.z + row[2].y * v.y + v.x * row[2].x);
    }
};

extern Vector3 g_ZeroVector;        // 0x0168b66c  (Vector3::ZERO)
extern Matrix3 g_IdentityMatrix3;   // 0x0168bc38  (Matrix3::IDENTITY)

struct cSPTransform {
    uint16_t mFlags;              // +0x0
    uint16_t mModificationCount;  // +0x2
    Vector3  mTranslation;        // +0x4
    float    mScale;              // +0x10
    Matrix3  mRotation;           // +0x14

    __forceinline cSPTransform() : mFlags(0), mModificationCount(0), mTranslation(g_ZeroVector),
                                   mScale(1.0f)
    {
        mRotation.row[0] = Vector3(g_IdentityMatrix3.row[0]);
        mRotation.row[1] = Vector3(g_IdentityMatrix3.row[1]);
        mRotation.row[2] = Vector3(g_IdentityMatrix3.row[2]);
    }
    __forceinline cSPTransform(const cSPTransform& t)
        : mFlags(t.mFlags), mModificationCount(t.mModificationCount), mTranslation(t.mTranslation),
          mScale(t.mScale), mRotation(t.mRotation) {}
    cSPTransform& operator=(const cSPTransform& x);              // 0x00537dc0
    __forceinline void SetScale(float s) { mModificationCount++; mScale = s; }
};

// ---------------------------------------------------------------------------------------
// Allocator whose embedded buffers carry a zero word in front of them: deallocate frees only
// heap blocks (word before the block non-zero).
__forceinline void SpFree(void* p)
{
    if (p && ((uint32_t*)p)[-1] != 0)
        operator delete[](p);
}

// eastl::vector<int> (grid of cell states)
struct IntVector {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    uint32_t mAllocator;

    __forceinline IntVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~IntVector() { SpFree(mpBegin); }
    void DoInsertValues(int* position, unsigned n, const int& value);   // 0x004cea40
    __forceinline void erase(int* first, int* last)
    {
        memmove(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
    }
    __forceinline void resize(unsigned n)
    {
        if (n > (unsigned)(mpEnd - mpBegin)) {
            int value = 0;
            DoInsertValues(mpEnd, n - (mpEnd - mpBegin), value);
        } else {
            erase(mpBegin + n, mpEnd);
        }
    }
};

// eastl::fixed_vector<Vector3, 256> (sampled grid points)
struct PointFixedVector {
    Vector3* mpBegin;          // +0x00
    Vector3* mpEnd;            // +0x04
    Vector3* mpCapacity;       // +0x08
    uint32_t mOverflowAlloc;   // +0x0c
    Vector3* mpPoolBegin;      // +0x10
    uint32_t mPad;             // +0x14
    Vector3  mBuffer[256];     // +0x18

    __forceinline PointFixedVector()
    {
        mpPoolBegin = mBuffer;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        mpCapacity = mBuffer + 256;
    }
    __forceinline ~PointFixedVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    void DoInsertValue(Vector3* position, const Vector3& value);        // 0x00ac4720
    __forceinline void push_back(const Vector3& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) Vector3(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

// Region outline: vector<Vector3> with an in-record 256-point buffer (+0x4c in the record).
struct OutlineVector {
    Vector3* mpBegin;          // +0x00
    Vector3* mpEnd;            // +0x04
    Vector3* mpCapacity;       // +0x08
    uint32_t mAllocator[2];    // +0x0c
    uint32_t mBufferHeader;    // +0x14  0: buffer is not a heap block

    void DoInsertValue(Vector3* position, const Vector3& value);        // 0x004b5ad0
    __forceinline void push_back(const Vector3& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) Vector3(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct Region {                    // 0xc64 bytes
    cSPTransform  mTransform;      // +0x00
    float         mWeight;         // +0x38  (1.0)
    float         mRadius;         // +0x3c
    Vector3       mCenter;         // +0x40
    OutlineVector mOutline;        // +0x4c
    Vector3       mBuffer[256];    // +0x64

    __forceinline Region()
    {
        mOutline.mpBegin = mBuffer;
        mOutline.mpEnd = mBuffer;
        mOutline.mBufferHeader = 0;
        mOutline.mpCapacity = mBuffer + 256;
    }
    __forceinline ~Region() { SpFree(mOutline.mpBegin); }
};

Region* CopyRegions(Region* first, Region* last, Region* dest);      // 0x00bd2a10

struct RegionVector {
    Region* mpBegin;
    Region* mpEnd;
    Region* mpCapacity;
    uint32_t mAllocator[2];

    void DestroyRange(Region* first, Region* last);                    // 0x00bd17e0
    void DoInsertValue(Region* position, const Region& value);         // 0x00bd3f10
    __forceinline Region* erase(Region* first, Region* last)
    {
        Region* const position = CopyRegions(last, mpEnd, first);
        DestroyRange(position, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    __forceinline void clear() { erase(mpBegin, mpEnd); }
    __forceinline Region& push_back()
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) Region();
        else
            DoInsertValue(mpEnd, Region());
        return *(mpEnd - 1);
    }
};

// ---------------------------------------------------------------------------------------
struct cSPTransformHolder { uint32_t pad[2]; cSPTransform mTransform; };   // Graphics::Model (+8)
struct Model : cSPTransformHolder {
    __forceinline cSPTransform GetTransform() const { return mTransform; }
};

class cSpatialObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();                       // +0x2c
    virtual const Quaternion& GetOrientation();                 // +0x30
    virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58();
    virtual Vector3 GetDirection();                             // +0x5c
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70();
    virtual float GetFootprintRadius();                         // +0x74
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8();
    virtual Model* GetModel();                                  // +0xac
};

class cPlanetModel {
public:
    Vector3 ProjectToSurface(const Vector3& p);                 // 0x00b81630
};
namespace SP { cPlanetModel* PlanetModel(); }                   // 0x00b3d350

// 0x00b52e00: tests the sampled cells against the object (Havok); writes 1 into results[i]
// for every free cell.
void TestFootprintCells(const Vector3& cellExtents, const Quaternion& orientation,
                        cSpatialObject* pObject, const Vector3* points, int* results, int count);

class cBuildingScenario {
public:
    void BuildFootprintRegions();                               // 0x00BD40A0

    uint32_t       pad000[0x34 / 4];
    cSpatialObject mSpatial;                                    // +0x034 (cSpatialObject base)
    uint32_t       pad038[(0x340 - 0x38) / 4];
    bool           mbRegionsValid;                              // +0x340
    RegionVector   mRegions;                                    // +0x344
    uint32_t       pad358[(0x388 - 0x358) / 4];
    cSPTransform   mModelTransform;                             // +0x388
};

// @ 0x00BD40A0
void cBuildingScenario::BuildFootprintRegions()
{
    mbRegionsValid = false;
    mRegions.clear();

    float diameter = (mSpatial.GetFootprintRadius() + 2.0f) * 2.0f;
    mModelTransform = mSpatial.GetModel()->GetTransform();
    mModelTransform.SetScale(1.0f);

    float half = diameter * 0.5f;
    int maxCells = 16;
    int numCells = CeilToInt(half);
    int n = Min(numCells, maxCells);
    float cell = diameter / (float)n;
    float halfCell = cell * 0.5f;

    IntVector grid;
    grid.resize(n * n);

    cPlanetModel* pPlanet = SP::PlanetModel();
    float offset = halfCell - half;
    Vector3 dir = mSpatial.GetDirection();
    Vector3 up = Normalized(mSpatial.GetPosition());
    Vector3 right = Normalized(Cross(dir, up));
    Vector3 origin = mSpatial.GetPosition() + dir * offset + right * offset;

    Vector3 cellExtents(cell, cell, 4.0f);
    PointFixedVector points;
    for (int i = 0; i < n; ++i) {
        float a = (float)i * cell;
        for (int j = 0; j < n; ++j) {
            float b = (float)j * cell;
            Vector3 p = dir * a + origin + right * b;
            p = pPlanet->ProjectToSurface(p);
            points.push_back(p);
        }
    }
    TestFootprintCells(cellExtents, mSpatial.GetOrientation(), &mSpatial, points.mpBegin,
                       grid.mpBegin, (int)(points.mpEnd - points.mpBegin));

    // Merge free cells into rectangles.
    int label = 2;
    int k = 0;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col, ++k) {
            if (grid.mpBegin[k] != 1)
                continue;
            int c = col;
            while (c < n && grid.mpBegin[row * n + c] == 1)
                ++c;
            int width = c - col;
            int r;
            for (r = row + 1; r < n; ++r) {
                for (c = col; c < width + col; ++c)
                    if (grid.mpBegin[r * n + c] != 1)
                        goto done;
            }
        done:
            int height = r - row;
            if (width > 1 || height > 1) {
                for (int rr = row; rr < height + row; ++rr)
                {
                    int end = width + col;
                    if (col < end)
                        __stosd((unsigned long*)&grid.mpBegin[rr * n + col], (unsigned long)label, end - col);
                }

                Region& region = mRegions.push_back();
                region.mWeight = 1.0f;
                float h = (float)height * cell;
                float w = (float)width * cell;
                region.mRadius = Max(w, h) * 0.5f;
                float rowOff = (float)row * cell - halfCell - 0.1f;
                float colOff = (float)col * cell - halfCell - 0.1f;
                Vector3 corner = pPlanet->ProjectToSurface(dir * rowOff + origin + right * colOff);
                Vector3 sideW = right * (w + 0.2f);
                Vector3 sideH = dir * (h + 0.2f);
                region.mOutline.push_back(corner);
                region.mOutline.push_back(sideW + corner);
                region.mOutline.push_back(sideW + corner + sideH);
                region.mOutline.push_back(sideH + corner);
                region.mOutline.push_back(corner);
                ++label;
                region.mCenter = corner + sideW * 0.5f + sideH * 0.5f;
            }
        }
    }

    // One region per remaining single free cell.
    k = 0;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (grid.mpBegin[k++] != 1)
                continue;
            Region& region = mRegions.push_back();
            region.mWeight = 1.0f;
            region.mRadius = halfCell;
            float rowOff = (float)row * cell - halfCell;
            float colOff = (float)col * cell - halfCell;
            Vector3 corner = pPlanet->ProjectToSurface(origin + dir * rowOff + right * colOff);
            Vector3 sideW = right * cell;
            Vector3 sideH = dir * cell;
            region.mOutline.push_back(corner);
            region.mOutline.push_back(sideW + corner);
            region.mOutline.push_back(sideW + corner + sideH);
            region.mOutline.push_back(sideH + corner);
            region.mOutline.push_back(corner);
            region.mCenter = sideW * 0.5f + corner + sideH * 0.5f;
        }
    }

    // Move the outlines into the model transform's space.
    int numRegions = (int)(mRegions.mpEnd - mRegions.mpBegin);
    for (int i = 0; i < numRegions; ++i) {
        Region& region = mRegions.mpBegin[i];
        int numPoints = (int)(region.mOutline.mpEnd - region.mOutline.mpBegin);
        for (int j = 0; j < numPoints; ++j) {
            Vector3& p = region.mOutline.mpBegin[j];
            const cSPTransform& t = mModelTransform;
            p.x = p.x - t.mTranslation.x;
            p.y = p.y - t.mTranslation.y;
            p.z = p.z - t.mTranslation.z;
            if (t.mScale != 1.0f) {
                float inv = 1.0f / t.mScale;
                p.x = p.x * inv;
                p.y = inv * p.y;
                p.z = p.z * inv;
            }
            if (t.mFlags & 2)
                p = t.mRotation * p;
        }
    }
}
