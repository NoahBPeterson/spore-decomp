// s00f4baa0: SP::cTerrainBrushEffect ribbon-brush imprint paths and the two eastl::vector
// instantiations they use.  Retail build (x87 float copies, no frame pointer, no /GS).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned int size_t;

// eastl pushes its per-type element copy ctor through this out-of-line stdcall iterator
// (real PDB name: `vector copy constructor iterator').
extern "C" void __stdcall VectorCopyCtorIterator(void* dst, const void* src, int elemSize,
                                                 int count, void* ctor);   // 0x00406540

// the element copy ctor 0x00406540 invokes for cBrushVertex (7 floats, ret 4)
extern "C" void BrushVertexCopyCtor(void* dst, const void* src);           // 0x00705c00

// ---------------------------------------------------------------------------
// rw / SP value types
// ---------------------------------------------------------------------------
struct cSPVector3 {                   // 0x0c
    float x, y, z;
};

struct cSPVector2 {                   // 0x08
    float x, y;
};

// ---------------------------------------------------------------------------
// texture instance + EA::AutoRefCount<cTextureInstance> (out-of-line
// operator=(T*) at 0x00576650, inlined Release())
// ---------------------------------------------------------------------------
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)

struct cTextureInstance {
    void*          vftable;           // +0x00
    unsigned int   mField04;          // +0x04
    volatile long  mnRefCount;        // +0x08

    int Release() {
        _InterlockedDecrement(&mnRefCount);
        if (_InterlockedExchangeAdd(&mnRefCount, 0) < 1) {
            _InterlockedIncrement(&mnRefCount);
            return 1;
        }
        return _InterlockedExchangeAdd(&mnRefCount, 0);
    }
};

float RandomRange(float lo, float hi);                    // 0x007d45d0

struct TexRef {                       // EA::AutoRefCount<cTextureInstance>
    cTextureInstance* mpObject;       // +0x00

    TexRef& operator=(cTextureInstance* p);               // 0x00576650
    ~TexRef() {
        if (mpObject)
            mpObject->Release();
    }
};

namespace SP {

struct cBrushVertex {                 // 0x1c
    cSPVector3 mPosition;             // +0x00
    cSPVector2 mUV;                   // +0x0c
    float      mIntensity;            // +0x14
    float      mSize;                 // +0x18

    cBrushVertex() {}
    cBrushVertex(const cBrushVertex& o) {
        mPosition.x = o.mPosition.x;
        mPosition.y = o.mPosition.y;
        mPosition.z = o.mPosition.z;
        mUV.x = o.mUV.x;
        mUV.y = o.mUV.y;
        mIntensity = o.mIntensity;
        mSize = o.mSize;
    }
};

struct cRibbonBrushPoly {             // 0x1c4
    int          mNumVertices;        // +0x000
    cBrushVertex mVertices[16];       // +0x004

    cRibbonBrushPoly() {}
    cRibbonBrushPoly(const cRibbonBrushPoly& o) {
        mNumVertices = o.mNumVertices;
        VectorCopyCtorIterator(mVertices, o.mVertices, sizeof(cBrushVertex), 16,
                               (void*)BrushVertexCopyCtor);
    }
};

struct cRibbonFalloffParams {         // 0x44
    int   mField00[11];               // +0x00
    int   mFallOffOp;                 // +0x2c
    float mFallOffN1;                 // +0x30
    float mFallOffN2;                 // +0x34
    int   mGradientCondOp;            // +0x38
    float mGradientCondN1;            // +0x3c
    float mGradientCondN2;            // +0x40
};

// ---------------------------------------------------------------------------
// frame payload types built by ApplyBrush / ApplyGlobalBrush
// ---------------------------------------------------------------------------
struct cBrushTextureInfo {            // 0x78
    TexRef mTexture;                  // +0x00
    char   mField04;                  // +0x04
    char   mFilterGlobal;             // +0x05
    char   mDoCubeMap;                // +0x06
    char   pad07;                     // +0x07
    float  mGaussianSlope;            // +0x08
    int    mDrawMode;                 // +0x0c
    float  mVary;                     // +0x10
    float  mLevelRangeValue1;         // +0x14
    float  mLevelRangeValue2;         // +0x18
    float  mIntensity;                // +0x1c
    float  mRotationX;                // +0x20
    float  mRotationY;                // +0x24
    float  mRotationZ;                // +0x28
    char   pad2c[0x10];               // +0x2c
    int    mReserved;                 // +0x3c
    char   pad40[0x38];               // +0x40
};

struct cBrushHeightInfo {             // 0x7c
    char  mDoFiltering;               // +0x00
    char  mRibbonKernel;              // +0x01
    char  pad02[2];                   // +0x02
    cRibbonFalloffParams mFalloff;    // +0x04
    int   mGradientCondOp;            // +0x48
    float mGradientCondN1;            // +0x4c
    float mGradientCondN2;            // +0x50
    int   mGradientFallOffOp;         // +0x54
    float mGradientFallOffN1;         // +0x58
    float mGradientFallOffN2;         // +0x5c
    char  pad60[0x1c];                // +0x60
};

} // namespace SP

using namespace SP;

// ---------------------------------------------------------------------------
// SP::cTerrainBrushDescription (retail layout: the dev-PDB description is 8
// bytes shorter up to mSpacingCurve, 0xc bytes shorter after it)
// ---------------------------------------------------------------------------
struct FloatVector {                  // eastl::vector<float, sp_vector_allocator>, 0x14
    void*    mpBegin;                 // +0x00
    void*    mpEnd;                   // +0x04
    void*    mpCapacity;              // +0x08
    unsigned mAlloc[2];               // +0x0c
};

struct cTerrainBrushDescription {     // 0x108
    int    mDescriptionBase[2];       // +0x00
    float  mLocation[3];              // +0x08
    int    pad14;                     // +0x14
    int    mTexture[2];               // +0x18
    unsigned char mDrawMode;          // +0x20
    bool   mDoGaussian;               // +0x21
    char   pad22[2];                  // +0x22
    float  mGaussianSlope;            // +0x24
    float  mLifetime;                 // +0x28
    FloatVector mSizeCurve;           // +0x2c
    FloatVector mIntensityCurve;      // +0x40
    bool   mWaterLevelIsZero;         // +0x54
    char   pad55[3];                  // +0x55
    float  mIntensityVary;            // +0x58
    float  mSizeVary;                 // +0x5c
    float  mRotationVary;             // +0x60
    float  mTextureOffset[2];         // +0x64
    float  mLevelValue;               // +0x6c
    float  mLevelVary;                // +0x70
    float  mLevelRangeValue1;         // +0x74
    float  mLevelRangeValue2;         // +0x78
    float  mImprintsPerSecond;        // +0x7c
    bool   mDoFiltering;              // +0x80
    bool   mFilterGlobal;             // +0x81
    unsigned char mKernelType;        // +0x82
    unsigned char mKernelOp;          // +0x83
    float  mDeltaAmount;              // +0x84
    FloatVector mSpacingCurve;        // +0x88
    float  mSpacingVary;              // +0x9c
    unsigned char mCondOp;            // +0xa0
    char   padA1[3];                  // +0xa1
    float  mCondN1;                   // +0xa4
    float  mCondN2;                   // +0xa8
    unsigned char mFallOffOp;         // +0xac
    char   padAd[3];                  // +0xad
    float  mFallOffN1;                // +0xb0
    float  mFallOffN2;                // +0xb4
    unsigned char mGradientCondOp;    // +0xb8
    char   padB9[3];                  // +0xb9
    float  mGradientCondN1;           // +0xbc
    float  mGradientCondN2;           // +0xc0
    unsigned char mGradientFallOffOp; // +0xc4
    char   padC5[3];                  // +0xc5
    float  mGradientFallOffN1;        // +0xc8
    float  mGradientFallOffN2;        // +0xcc
    bool   mDoCubeMap;                // +0xd0
    char   padD1[3];                  // +0xd1
    float  mRot[3];                   // +0xd4
    float  mRotVary[3];               // +0xe0
    bool   mRibbonBrush;              // +0xec
    char   padEd[0x108 - 0xed];       // +0xed
};

// ---------------------------------------------------------------------------
// eastl::vector with the Simulator allocator
// ---------------------------------------------------------------------------
extern const char gSimulatorName[];   // 0x013f09b4
extern const char gAllocatorPath[];   // 0x013ebb38

void* EAAllocate(size_t size, const char* name, unsigned a, unsigned b, const char* file,
                 int line);           // 0x00f473a0
void  operator delete[](void* p);     // 0x00f47380

namespace eastl {

struct sp_vector_allocator {
    int mFlags;
    int mUnused;

    bool operator==(const sp_vector_allocator&) const { return true; }
    void deallocate(void* p, size_t) {
        if (p != 0 && ((int*)p)[-1] != 0)
            ::operator delete[](p);
    }
};

template <class T, class Allocator> class vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    void DoInsertValue(T* position, const T& value);
    void push_back();
    void erase(T* first, T* last);    // 0x00d73090
};

} // namespace eastl

typedef eastl::vector<cBrushVertex, eastl::sp_vector_allocator> BrushVertexVector;
typedef eastl::vector<cRibbonBrushPoly, eastl::sp_vector_allocator> RibbonPolyVector;

// out-of-line eastl copy helpers the instantiated vectors call
cBrushVertex*  CopyVerticesForward(cBrushVertex* first, cBrushVertex* last, cBrushVertex* dest);          // 0x00f4b1d0
cRibbonBrushPoly* CopyPolysBackward(cRibbonBrushPoly* first, cRibbonBrushPoly* last, cRibbonBrushPoly* dest); // 0x00f4b190
cRibbonBrushPoly* CopyPolysForward(cRibbonBrushPoly* first, cRibbonBrushPoly* last, cRibbonBrushPoly* dest);  // 0x00f4b4c0

inline void* operator new(size_t, void* p) { return p; }

template <class T>
inline T* CopyBackward(T* first, T* last, T* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}

// ---------------------------------------------------------------------------
// SP::cTerrainBrushEffect / SP::cTerrainEditor
// ---------------------------------------------------------------------------
class cTerrainEditor {
public:
    float GetRandom01();                                                              // 0x00f678d0
    void  ApplyBrush(cBrushTextureInfo* texInfo, cBrushHeightInfo* heightInfo, int count,
                     cRibbonBrushPoly* polys, int flags);                             // 0x00f6e120
    void  ApplyGlobalBrush(cBrushTextureInfo* texInfo, cBrushHeightInfo* heightInfo,
                           int flags, float vary);                                    // 0x00f6df40
};

cTerrainEditor* TerrainEditor();                                                      // 0x00f48a70

class cTerrainBrushEffect {
public:
    void*                     vftable;                    // +0x00
    char                      pad04[0x0c - 0x04];         // +0x04
    cTerrainBrushDescription* mDesc;                      // +0x0c
    bool                      mIsActive;                  // +0x10
    char                      pad11[0x9c - 0x11];         // +0x11
    float                     mOverallTime;               // +0x9c
    char                      padA0[0xbc - 0xa0];         // +0xa0
    float                     mVary;                      // +0xbc
    cTextureInstance*         mpTexture;                  // +0xc0
    BrushVertexVector         mRibbonBrushList;           // +0xc4

    void ApplyBrush(float intensity, int count, cRibbonBrushPoly* polys,
                    const cRibbonFalloffParams* params);                              // 0x00f4baa0
    void ApplyGlobalBrush(float vary, const cRibbonFalloffParams* params);             // 0x00f4bcb0
    void Start(int a);                                                                // 0x00f4c2c0
    void Imprint(float intensity, int count, cRibbonBrushPoly* polys,
                 const cRibbonFalloffParams* params);                                 // 0x00f4b870
};

float gRealOne;               // _HK_REAL_ONE, 0x01485720

// ---------------------------------------------------------------------------
// @ 0x00f4baa0
// ---------------------------------------------------------------------------
void cTerrainBrushEffect::ApplyBrush(float intensity, int count, cRibbonBrushPoly* polys,
                                     const cRibbonFalloffParams* params)
{
    float vary = 0.0f;
    if (mDesc->mWaterLevelIsZero) {
        float r = TerrainEditor()->GetRandom01();
        vary = r + r - gRealOne;
    }

    cBrushTextureInfo texInfo;
    texInfo.mTexture.mpObject = 0;
    texInfo.mTexture = mpTexture;
    if (mpTexture == 0 || mDesc->mDoGaussian)
        texInfo.mField04 = 1;
    else
        texInfo.mField04 = 0;

    cTerrainBrushDescription* desc = mDesc;
    texInfo.mGaussianSlope = desc->mGaussianSlope;
    texInfo.mIntensity = intensity;
    texInfo.mFilterGlobal = (char)desc->mFilterGlobal;
    texInfo.mDoCubeMap = (char)desc->mDoCubeMap;
    texInfo.mDrawMode = desc->mDrawMode;
    texInfo.mVary = mVary + vary;
    texInfo.mLevelRangeValue1 = desc->mLevelRangeValue1;
    texInfo.mLevelRangeValue2 = desc->mLevelRangeValue2;
    if (texInfo.mDrawMode != 5 && texInfo.mDrawMode != 6) {
        texInfo.mLevelRangeValue1 = texInfo.mLevelRangeValue1 + vary;
        texInfo.mLevelRangeValue2 = texInfo.mLevelRangeValue2 + vary;
    }

    cBrushHeightInfo heightInfo;
    texInfo.mReserved = 0;
    heightInfo.mDoFiltering = desc->mDoFiltering;
    heightInfo.mFalloff = *params;
    heightInfo.mRibbonKernel = 0;
    heightInfo.mGradientCondOp = desc->mGradientCondOp;
    heightInfo.mGradientCondN1 = desc->mGradientCondN1;
    heightInfo.mGradientCondN2 = desc->mGradientCondN2;
    heightInfo.mGradientFallOffOp = desc->mGradientFallOffOp;
    heightInfo.mGradientFallOffN1 = desc->mGradientFallOffN1;
    heightInfo.mGradientFallOffN2 = desc->mGradientFallOffN2;
    if (desc->mDoFiltering && desc->mKernelType == 0x12)
        heightInfo.mRibbonKernel = 1;

    TerrainEditor()->ApplyBrush(&texInfo, &heightInfo, count, polys, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00f4bcb0
// ---------------------------------------------------------------------------
void cTerrainBrushEffect::ApplyGlobalBrush(float vary, const cRibbonFalloffParams* params)
{
    float localVary = 0.0f;
    float rx, ry, rz;
    if (mDesc->mWaterLevelIsZero) {
        float r = TerrainEditor()->GetRandom01();
        localVary = r + r - gRealOne;
    }

    cBrushTextureInfo texInfo;
    texInfo.mTexture.mpObject = 0;
    if (mpTexture == 0 || mDesc->mDoGaussian)
        texInfo.mField04 = 1;
    else
        texInfo.mField04 = 0;

    cTerrainBrushDescription* desc = mDesc;
    texInfo.mGaussianSlope = desc->mGaussianSlope;
    texInfo.mIntensity = vary;
    texInfo.mFilterGlobal = (char)desc->mFilterGlobal;
    rx = RandomRange(desc->mRot[0], desc->mRotVary[0]);
    ry = RandomRange(desc->mRot[1], desc->mRotVary[1]);
    rz = RandomRange(desc->mRot[2], desc->mRotVary[2]);
    texInfo.mVary = mVary + localVary;
    texInfo.mRotationX = rx;
    texInfo.mRotationY = ry;
    texInfo.mRotationZ = rz;
    texInfo.mDrawMode = desc->mDrawMode;
    texInfo.mLevelRangeValue1 = desc->mLevelRangeValue1;
    texInfo.mLevelRangeValue2 = desc->mLevelRangeValue2;
    if (texInfo.mDrawMode != 5 && texInfo.mDrawMode != 6) {
        texInfo.mLevelRangeValue1 = texInfo.mLevelRangeValue1 + localVary;
        texInfo.mLevelRangeValue2 = texInfo.mLevelRangeValue2 + localVary;
    }
    texInfo.mReserved = 0;
    texInfo.mTexture = mpTexture;

    cBrushHeightInfo heightInfo;
    heightInfo.mDoFiltering = desc->mDoFiltering;
    heightInfo.mFalloff = *params;
    heightInfo.mRibbonKernel = 0;
    heightInfo.mGradientCondOp = desc->mGradientCondOp;
    heightInfo.mGradientCondN1 = desc->mGradientCondN1;
    heightInfo.mGradientCondN2 = desc->mGradientCondN2;
    heightInfo.mGradientFallOffOp = desc->mGradientFallOffOp;
    heightInfo.mGradientFallOffN1 = desc->mGradientFallOffN1;
    heightInfo.mGradientFallOffN2 = desc->mGradientFallOffN2;
    if (desc->mDoFiltering && desc->mKernelType == 0x12)
        heightInfo.mRibbonKernel = 1;

    TerrainEditor()->ApplyGlobalBrush(&texInfo, &heightInfo, 0, localVary);
}

// ---------------------------------------------------------------------------
// @ 0x00f4bf30
// ---------------------------------------------------------------------------
void BrushVertexVector::DoInsertValue(cBrushVertex* position, const cBrushVertex& value)
{
    if (this->mpEnd != this->mpCapacity) {
        const cBrushVertex* pValue = &value;
        if (pValue >= position && pValue < this->mpEnd)
            ++pValue;
        ::new ((void*)this->mpEnd) cBrushVertex(*(this->mpEnd - 1));
        CopyBackward(position, this->mpEnd - 1, this->mpEnd);
        *position = *pValue;
        ++this->mpEnd;
        return;
    }

    unsigned int nPrevSize = (unsigned int)(this->mpEnd - this->mpBegin);
    unsigned int nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
    cBrushVertex* pNewData = nNewSize
        ? (cBrushVertex*)EAAllocate(nNewSize * sizeof(cBrushVertex), gSimulatorName, 0, 0,
                                    gAllocatorPath, 0xd1)
        : 0;
    cBrushVertex* pNewEnd = CopyVerticesForward(this->mpBegin, position, pNewData);
    ::new ((void*)pNewEnd) cBrushVertex(value);
    pNewEnd = CopyVerticesForward(position, this->mpEnd, ++pNewEnd);
    if (this->mpBegin != 0 && ((int*)this->mpBegin)[-1] != 0)
        ::operator delete[](this->mpBegin);
    this->mpEnd = pNewEnd;
    this->mpBegin = pNewData;
    this->mpCapacity = pNewData + nNewSize;
}

// ---------------------------------------------------------------------------
// @ 0x00f4c150
// ---------------------------------------------------------------------------
void BrushVertexVector::push_back()
{
    if (this->mpEnd < this->mpCapacity) {
        ++this->mpEnd;
        return;
    }
    DoInsertValue(this->mpEnd, cBrushVertex());
}

// ---------------------------------------------------------------------------
// @ 0x00f4c180
// ---------------------------------------------------------------------------
void RibbonPolyVector::DoInsertValue(cRibbonBrushPoly* position, const cRibbonBrushPoly& value)
{
    if (this->mpEnd != this->mpCapacity) {
        const cRibbonBrushPoly* pValue = &value;
        if (pValue >= position && pValue < this->mpEnd)
            ++pValue;
        ::new ((void*)this->mpEnd) cRibbonBrushPoly(*(this->mpEnd - 1));
        CopyPolysBackward(position, this->mpEnd - 1, this->mpEnd);
        *position = *pValue;
        ++this->mpEnd;
        return;
    }

    unsigned int nPrevSize = (unsigned int)(this->mpEnd - this->mpBegin);
    unsigned int nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
    cRibbonBrushPoly* pNewData = nNewSize
        ? (cRibbonBrushPoly*)EAAllocate(nNewSize * sizeof(cRibbonBrushPoly), gSimulatorName, 0, 0,
                                        gAllocatorPath, 0xd1)
        : 0;
    cRibbonBrushPoly* pNewEnd = CopyPolysForward(this->mpBegin, position, pNewData);
    ::new ((void*)pNewEnd) cRibbonBrushPoly(value);
    pNewEnd = CopyPolysForward(position, this->mpEnd, ++pNewEnd);
    if (this->mpBegin != 0 && ((int*)this->mpBegin)[-1] != 0)
        ::operator delete[](this->mpBegin);
    this->mpEnd = pNewEnd;
    this->mpBegin = pNewData;
    this->mpCapacity = pNewData + nNewSize;
}

// ---------------------------------------------------------------------------
// @ 0x00f4c2c0
// ---------------------------------------------------------------------------
void cTerrainBrushEffect::Start(int a)
{
    if (mIsActive)
        return;
    mIsActive = true;
    mOverallTime = 0.0f;
    if (mDesc->mRibbonBrush)
        mRibbonBrushList.erase(mRibbonBrushList.mpBegin, mRibbonBrushList.mpEnd);
}
