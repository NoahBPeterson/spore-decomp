// Slice s00725e40 — mesh connectivity helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//   00725e40: SP::cMeshClusterer::AssignCharts (complete, not byte-exact).
//   007269b0: eastl::vector<SP::cClusterInfo, sp_vector_allocator>::DoInsertValues
//             (element stride 0x64) — reconstructed from the decompile.
#include "types.h"
#include <math.h>
#include <float.h>

extern "C" {
    int   FUN_0071ddc0(void* p, int a, int b, int c, int d);
    int   FUN_0071e040(void* p, int idx, int id);
    void  FUN_007249f0(void* p);
    void  FUN_00725130(void* p);
    void* FUN_00f473a0(unsigned n, const char* name, int f, int df, const char* file, int line);
    void  FUN_00f47380(void* p);
    int   FUN_00721f50(int src, int srcEnd, int dst);
    void  FUN_00720e60(int src, int srcEnd, int dst);
    void  FUN_00721ed0(int dst, unsigned n, int value, int dst2);
    void  FUN_00721d80(int value);
    void  FUN_00721e50(void* p, ...);
    void  FUN_00722ac0(int src, int srcEnd, int dst);
    void  FUN_00723bf0(int first, int last, int tmp);
}

// ---------------------------------------------------------------------------
// 0x00725e40: SP::cMeshClusterer::AssignCharts (name from the dev build's function order;
// dev 0x00f47690, 2620 bytes). Projects every cluster onto a tangent frame built from its
// normal, optionally aligns the frame with the cluster boundary's best-fit rectangle,
// writes the per-element UVs into a new kMDTexCoord element array and computes the area
// of each cluster in UV space.
// Layouts are the retail ones (EASTL vectors are 0x14 bytes here, 0x10 in the 2008 PDB).
// ---------------------------------------------------------------------------
namespace SP {

struct cSPVector2 {
    float x, y;
    cSPVector2() {}
    cSPVector2(float ax, float ay) : x(ax), y(ay) {}
    cSPVector2& operator-=(const cSPVector2& o) { float nx = x - o.x; float ny = y - o.y; x = nx; y = ny; return *this; }
    cSPVector2& operator*=(float s) { float nx = x * s; float ny = y * s; x = nx; y = ny; return *this; }
};
inline cSPVector2 operator-(const cSPVector2& a, const cSPVector2& b) { return cSPVector2(a.x - b.x, a.y - b.y); }

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& o) : x(o.x), y(o.y), z(o.z) {}
    cSPVector3& operator=(const cSPVector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline cSPVector3 operator+(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline cSPVector3 operator*(const cSPVector3& a, float s) { return cSPVector3(a.x * s, a.y * s, a.z * s); }
inline float Dot(const cSPVector3& a, const cSPVector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline cSPVector3 Cross(const cSPVector3& a, const cSPVector3& b)
{
    return cSPVector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
inline cSPVector3 Normalize(const cSPVector3& v)
{
    float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    float inv = 1.0f / len;
    return cSPVector3(v.x * inv, v.y * inv, v.z * inv);
}

cSPVector3 OrthogonalVector(const cSPVector3& v);  // 0x006985b0

extern const uint32_t kEltMasks[];  // 0x0140d0ac: value mask per element size (index = byte count)

struct IRefCounted { virtual int AddRef(); virtual int Release(); };

// SP::cEltArrayRef (0x10)
struct cEltArrayRef {
    int          mNumElts;    // +0
    uint8_t*     mData;       // +4
    uint16_t     mEltSize;    // +8
    uint16_t     mEltStride;  // +a
    IRefCounted* mDataRC;     // +c

    cEltArrayRef(int n, int eltSize)
        : mNumElts(n), mData(0), mEltSize((uint16_t)eltSize), mEltStride((uint16_t)eltSize), mDataRC(0) {}
    ~cEltArrayRef() { if (mDataRC) mDataRC->Release(); }

    template<class T> T& At(int i) const { return *(T*)(mData + mEltStride * i); }
};
struct cIndexArrayRef : cEltArrayRef {
    uint32_t Index(int i) const { return *(uint32_t*)(mData + mEltStride * i) & kEltMasks[mEltSize]; }
};
void AllocateEltArray(cEltArrayRef& a);  // 0x00720070

struct cMDElementArray {       // 0x20
    int mSemantic, mNumber, mType, mClass;
    cEltArrayRef mArray;       // +0x10
};
struct cMDFormatEntry { short mElts; short mIndices; };
struct cMDSection {            // 0x8c (retail)
    uint32_t pad0[5];
    cMDFormatEntry* mFormat;   // +0x14 (fixed_vector mpBegin)
    uint32_t pad18[11];
    cIndexArrayRef* mEltIndices;  // +0x44 (fixed_vector mpBegin)
    uint32_t pad48[17];
};
struct cMeshData {
    uint32_t pad0[2];
    cMDElementArray* mEltArrays;  // +0x08
    uint32_t padc[4];
    cMDSection* mSections;        // +0x1c
};
int  FindFormatEntry(cMeshData* mesh, int section, int semantic, int number, int flags);   // 0x0071e090
int  AddEltArray(cMeshData* mesh, int semantic, int number, int type, int cls, const cEltArrayRef& a);  // 0x0071f0f0
void AddSectionElement(cMeshData* mesh, int section, int eltArray, const cIndexArrayRef& idx);      // 0x0071f040

inline void* SpAllocate(uint32_t n)
{
    return FUN_00f473a0(n, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
}
inline void SpFree(void* p)
{
    if (p && ((int*)p)[-1] != 0)
        FUN_00f47380(p);
}

// eastl::vector<unsigned int, sp_vector_allocator>
struct UIntVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t  mAllocator[2];

    __forceinline explicit UIntVector(uint32_t n)
    {
        mpBegin = n ? (uint32_t*)SpAllocate(n * sizeof(uint32_t)) : 0;
        mpCapacity = mpBegin + n;
        uint32_t* cur = mpBegin;
        for (uint32_t k = n; k > 0; --k)
            *cur++ = 0;
        mpEnd = mpBegin + n;
    }
    ~UIntVector() { SpFree(mpBegin); }
    uint32_t& operator[](int i) { return mpBegin[i]; }
};

struct forward_iterator_tag { forward_iterator_tag() {} };

inline cSPVector2* CopyV2(cSPVector2* first, cSPVector2* last, cSPVector2* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}

// eastl::vector<cSPVector2, sp_vector_allocator>
struct Vector2Vector {
    cSPVector2* mpBegin;
    cSPVector2* mpEnd;
    cSPVector2* mpCapacity;
    uint32_t    mAllocator[2];

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void DoInsertValues(cSPVector2* position, uint32_t n, const cSPVector2& value);       // 0x00479830
    void DoInsertFromIterator(cSPVector2* position, const cSPVector2* first, const cSPVector2* last,
                              forward_iterator_tag);                                       // 0x005107d0
    cSPVector2* erase(cSPVector2* first, cSPVector2* last)
    {
        CopyV2(last, mpEnd, first);
        mpEnd -= (last - first);
        return first;
    }
    void resize(uint32_t n)
    {
        if (n > size())
            DoInsertValues(mpEnd, n - size(), cSPVector2());
        else
            erase(mpBegin + n, mpEnd);
    }
    void insert(cSPVector2* position, const cSPVector2* first, const cSPVector2* last)
    {
        DoInsertFromIterator(position, first, last, forward_iterator_tag());
    }
};

// Boundary helpers (cdecl, same module)
void RemoveDuplicatePoints(Vector2Vector* v);                                     // 0x00721240
void FindConvexHull(const cSPVector2* pts, int n, Vector2Vector* out);            // 0x007247c0
void ComputeBounds(Vector2Vector* v, cSPVector2* bmin, cSPVector2* bmax);         // 0x00720920
void FindBestRectAxis(const cSPVector2* pts, int n, cSPVector2* bmin, cSPVector2* bmax,
                      cSPVector2* axis);                                           // 0x00721340

// SP::cClusterInfo (0x64 retail)
struct cClusterInfo {
    int        mNumFaces;          // +0x00
    cSPVector3 mNormal;            // +0x04
    cSPVector3 mCentre;            // +0x10
    float      mArea;              // +0x1c
    float      mProjArea;          // +0x20
    float      mTexArea;           // +0x24
    cSPVector2 mMinUV;             // +0x28
    cSPVector2 mMaxUV;             // +0x30
    int        mFacesStart;        // +0x38
    int        mFacesEnd;          // +0x3c
    int        mIndicesStart;      // +0x40
    int        mIndicesEnd;        // +0x44
    int        mBorderIndicesStart;// +0x48
    int        mBorderIndicesEnd;  // +0x4c
    Vector2Vector mBoundaryCoords; // +0x50
};

template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

struct cMeshClusterer {
    void*         vfptr;               // +0x00
    int           mRefCount;           // +0x04
    cMeshData*    mMeshData;           // +0x08
    cClusterInfo* mClusterInfo;        // +0x0c (vector mpBegin)
    uint32_t      pad10[4];
    cEltArrayRef  mClusterIndices;     // +0x20 (cEltArrayRefT<unsigned int>)
    int           mNumClusterElements; // +0x30
    cEltArrayRef  mClusterFaces;       // +0x34 (cEltArrayRefT<unsigned int>)
    int           mSection;            // +0x44
    uint32_t      pad48[16];
    int           mNumClusters;        // +0x88

    void Prepare();                    // 0x00723140
    void AssignCharts(int texCoordSet, bool normalize, bool alignToBoundary);
};

// @ 0x00725e40
void cMeshClusterer::AssignCharts(int texCoordSet, bool normalize, bool alignToBoundary)
{
    Prepare();

    int fmtIndex = FindFormatEntry(mMeshData, mSection, 1 /*kMDPosition*/, 0, 0);
    const cEltArrayRef& positions =
        mMeshData->mEltArrays[mMeshData->mSections[mSection].mFormat[fmtIndex].mElts].mArray;
    const cIndexArrayRef& posIndices =
        mMeshData->mSections[mSection].mEltIndices[mMeshData->mSections[mSection].mFormat[fmtIndex].mIndices];

    // cluster element -> vertex index
    UIntVector vertIndex(mNumClusterElements);
    for (int i = 0; i < mNumClusters; ++i) {
        const cClusterInfo& ci = mClusterInfo[i];
        for (int f = ci.mFacesStart; f < ci.mFacesEnd; ++f) {
            int e = mClusterFaces.At<int>(f) * 3;
            vertIndex[mClusterIndices.At<int>(e)]     = posIndices.Index(e);
            vertIndex[mClusterIndices.At<int>(e + 1)] = posIndices.Index(e + 1);
            vertIndex[mClusterIndices.At<int>(e + 2)] = posIndices.Index(e + 2);
        }
    }

    cEltArrayRef uvs(mNumClusterElements, sizeof(cSPVector2));
    AllocateEltArray(uvs);

    for (int i = 0; i < mNumClusters; ++i) {
        cClusterInfo& ci = mClusterInfo[i];

        cSPVector3 u = Normalize(OrthogonalVector(ci.mNormal));
        cSPVector3 v = Cross(ci.mNormal, u);
        int numBorder = ci.mBorderIndicesEnd - ci.mBorderIndicesStart;
        cSPVector3 a = u;
        cSPVector3 b = v;

        if (alignToBoundary && numBorder > 4) {
            ci.mBoundaryCoords.resize(numBorder);
            for (int k = ci.mBorderIndicesStart; k < ci.mBorderIndicesEnd; ++k) {
                cSPVector3 d = positions.At<cSPVector3>(vertIndex[k]) - ci.mCentre;
                ci.mBoundaryCoords.mpBegin[k - ci.mBorderIndicesStart] = cSPVector2(Dot(d, u), Dot(d, v));
            }
            RemoveDuplicatePoints(&ci.mBoundaryCoords);
            FindConvexHull(ci.mBoundaryCoords.mpBegin, ci.mBoundaryCoords.size(), &ci.mBoundaryCoords);
            cSPVector2 bmin, bmax, axis;
            ComputeBounds(&ci.mBoundaryCoords, &bmin, &bmax);
            FindBestRectAxis(ci.mBoundaryCoords.mpBegin, ci.mBoundaryCoords.size(), &bmin, &bmax, &axis);
            a = u * axis.x + v * axis.y;
            b = u * -axis.y + v * axis.x;
        }

        ci.mMinUV = cSPVector2(FLT_MAX, FLT_MAX);
        ci.mMaxUV = cSPVector2(-FLT_MAX, -FLT_MAX);
        for (int k = ci.mIndicesStart; k < ci.mIndicesEnd; ++k) {
            cSPVector3 d = positions.At<cSPVector3>(vertIndex[k]) - ci.mCentre;
            cSPVector2 uv(Dot(d, a), -Dot(d, b));
            uvs.At<cSPVector2>(k) = uv;
            if (uv.x < ci.mMinUV.x) ci.mMinUV.x = uv.x;
            if (uv.x > ci.mMaxUV.x) ci.mMaxUV.x = uv.x;
            if (uv.y < ci.mMinUV.y) ci.mMinUV.y = uv.y;
            if (uv.y > ci.mMaxUV.y) ci.mMaxUV.y = uv.y;
        }

        if (normalize) {
            cSPVector2 ext = ci.mMaxUV - ci.mMinUV;
            const float& m = Max(ext.x, ext.y);
            float scale = 1.0f;
            if (m > 0.0001f)
                scale = 1.0f / m;
            for (int k = ci.mIndicesStart; k < ci.mIndicesEnd; ++k) {
                uvs.At<cSPVector2>(k) -= ci.mMinUV;
                uvs.At<cSPVector2>(k) *= scale;
            }
            ci.mMaxUV -= ci.mMinUV;
            ci.mMinUV -= ci.mMinUV;
            ci.mMinUV *= scale;
            ci.mMaxUV *= scale;
        }

        ci.mBoundaryCoords.resize(0);
        if (numBorder != 0) {
            const cSPVector2* uvData = (const cSPVector2*)uvs.mData;
            ci.mBoundaryCoords.insert(ci.mBoundaryCoords.mpBegin,
                                      uvData + ci.mBorderIndicesStart, uvData + ci.mBorderIndicesEnd);
            RemoveDuplicatePoints(&ci.mBoundaryCoords);
            FindConvexHull(ci.mBoundaryCoords.mpBegin, ci.mBoundaryCoords.size(), &ci.mBoundaryCoords);
        }

        // UV-space area: Newell normal of the triangle lifted to 3D (the z coordinates are
        // never set in the original, only the x/y components of the normal are used).
        ci.mTexArea = 0.0f;
        for (int f = ci.mFacesStart; f < ci.mFacesEnd; ++f) {
            int e = mClusterFaces.At<int>(f) * 3;
            const cSPVector2& t0 = uvs.At<cSPVector2>(mClusterIndices.At<int>(e));
            const cSPVector2& t1 = uvs.At<cSPVector2>(mClusterIndices.At<int>(e + 1));
            const cSPVector2& t2 = uvs.At<cSPVector2>(mClusterIndices.At<int>(e + 2));
            cSPVector3 p0, p1, p2;
            p0.x = t0.x; p0.y = t0.y;
            p1.x = t1.x; p1.y = t1.y;
            p2.x = t2.x; p2.y = t2.y;
            float nx = (p0.y - p1.y) * (p0.z + p1.z) + (p1.y - p2.y) * (p1.z + p2.z) + (p2.y - p0.y) * (p2.z + p0.z);
            float ny = (p0.z - p1.z) * (p0.x + p1.x) + (p1.z - p2.z) * (p1.x + p2.x) + (p2.z - p0.z) * (p2.x + p0.x);
            nx *= 0.5f;
            ny *= 0.5f;
            ci.mTexArea += sqrtf(nx * nx + ny * ny);
        }
    }

    AddSectionElement(mMeshData, mSection,
                      AddEltArray(mMeshData, 8 /*kMDTexCoord*/, texCoordSet, 2, 2, uvs),
                      *(const cIndexArrayRef*)&mClusterIndices);
}

} // namespace SP

// @ 0x007269b0
// eastl::vector<SP::cClusterInfo, eastl::sp_vector_allocator>::DoInsertValues(position, n, value)
// (element size 100, vector header = begin/end/cap).
void FUN_007269b0(int* param_1, int param_2, unsigned param_3, int param_4)
{
    if ((unsigned)((param_1[2] - param_1[1]) / 100) < param_3) {
        int   count = (param_1[1] - *param_1) / 100;   // current size
        unsigned cap = count * 2;
        if (count == 0)
            cap = 1;
        unsigned need = count + param_3;
        if (need < cap)
            need = cap;
        int newBuf;
        if (need == 0)
            newBuf = 0;
        else
            newBuf = (int)FUN_00f473a0(need * 100, "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        int oldEnd = param_1[1];
        int oldBeg = *param_1;
        int mid = FUN_00721f50(oldBeg, param_2, newBuf);
        FUN_00720e60(oldBeg, param_2, newBuf);
        FUN_00721ed0(mid, param_3, param_4, mid);      // fill n values
        int afterFill = param_3 * 100 + mid;
        int pos = param_1[1];
        FUN_00721f50(pos, oldEnd, afterFill);          // relocate [pos,end)
        FUN_00720e60(pos, oldEnd, afterFill);
        (void)oldEnd;
        if (oldBeg && *(int*)(oldBeg - 4) != 0)
            FUN_00f47380((void*)oldBeg);
        param_1[1] = afterFill;
        *param_1 = newBuf;
        param_1[2] = need * 100 + newBuf;
    } else if (param_3 != 0) {
        FUN_00721d80(param_4);
        int   end  = param_1[1];
        unsigned old = (unsigned)((param_1[1] - param_2) / 100);
        if (param_3 < old) {
            int cut = end + param_3 * -100;
            FUN_00721e50(&param_4, cut, end, end);
            int oldPos = param_2;
            param_1[1] = param_1[1] + param_3 * 100;
            FUN_00722ac0(param_2, cut, end);
            FUN_00723bf0(oldPos, param_3 * 100 + oldPos, 0);
        } else {
            FUN_00721ed0(end, param_3 - old, 0, param_2);
            int oldPos = param_2;
            param_1[1] = param_1[1] + (param_3 - old) * 100;
            FUN_00721e50(&param_2, param_2, end, param_1[1], param_2);
            param_1[1] = param_1[1] + old * 100;
            FUN_00723bf0(oldPos, end, 0);
        }
    }
}
