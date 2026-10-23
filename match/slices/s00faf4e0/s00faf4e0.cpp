// Slice s00faf4e0 -- 0x0faxxxx region: the ribbon-polygon rasteriser of
// cTerrainSphereQuad.  A cRibbonFacePoly holds a list of 0x14-byte cRibbonFaceVertex
// (position + texcoord + alpha), four of which form the bilinear "patch" at +0xc0;
// the quad's render routine walks a switch over the ribbon face id and assigns the
// matching raster-state parameters.
#include "types.h"
#include <intrin.h>
#include <float.h>

namespace rw {
namespace graphics {

class CompiledState
{
public:
    void Dispatch();                                    // 0x011ee580
};

class RasterState
{
public:
    void Assign(CompiledState* state, int index, int value);   // 0x00fc27e0
    CompiledState* mpState;     // +0x00
    int            mIndex;      // +0x04
    int            mValue;      // +0x08
    int            mCached;     // +0x0c
};

} // namespace graphics
} // namespace rw

using rw::graphics::CompiledState;
using rw::graphics::RasterState;

struct cSPVector2 { float x, y; };
struct cSPVector3 { float x, y, z; };

struct cRibbonFaceVertex           // 0x14
{
    cSPVector2 mPos;               // +0x00
    cSPVector2 mTC;                // +0x08
    float      mAlpha;             // +0x10
};

// One ribbon polygon (0x110 bytes).  mpBegin/mpEnd bracket the cRibbonFaceVertex list
// (inline fixed_vector storage or a heap block); mPatch is the bilinear patch read by
// InterpolateRibbonPoly.
struct cRibbonFacePoly
{
    cRibbonFaceVertex* mpBegin;     // +0x00
    cRibbonFaceVertex* mpEnd;       // +0x04
    uint32_t           mPad08[39];  // +0x08 .. +0xa3
    float              mTopV;       // +0xa4
    float              mLengthV;    // +0xa8
    int                mRibbonID;   // +0xac
    float              mMinX;       // +0xb0
    float              mMinY;       // +0xb4
    float              mMaxX;       // +0xb8
    float              mMaxY;       // +0xbc
    cRibbonFaceVertex  mPatch[4];   // +0xc0 .. +0x10f

    void FUN_00fafda0();            // 0x00fafda0
    void FUN_00faff10();            // 0x00faff10
};

// Min/Max returning a reference (eastl/STL style): the reference-select idiom the
// original 0x00faff10 spells as a pointer choose over two stack slots.
template <class T> const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template <class T> const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

class cTextureInstance
{
public:
    int  mFirst;                    // +0x00
    int  GetRaster();               // 0x0046f260
};

extern cTextureInstance* g_pTextureInstance;    // 0x016c9f58
extern int g_lastFace;                          // 0x015b1538
extern int g_lastKey;                           // 0x015b153c

class cTerrainSphere
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* GetMapSet();      // +0x0c
    virtual void* GetInfo();        // +0x10

    int GetQuadKeyA(int face);      // 0x00f98260
    int GetQuadKeyB(int face);      // 0x00f98270
    int GetQuadKeyC(int face);      // 0x00f98280
    int GetKeyD(int face);          // 0x00f96910
    int GetKeyE();                  // 0x00f96a00
};

class cTerrainSphereQuad
{
public:
    cTerrainSphere* mSphere;            // +0x00
    uint32_t        mPad04[5];          // +0x04 .. +0x17
    int             mChunkRes;          // +0x18
    int             mFace;              // +0x1c
    uint32_t        mPad20[84];         // +0x20 .. +0x16f
    void*           mAboveBelowMap;     // +0x170
    uint32_t        mAboveBelowCount;   // +0x174
    int             mAboveBelowStride;  // +0x178

    void FUN_00faf890();                                        // 0x00faf890
    void FUN_00faf4e0(int key, RasterState* states, int flag);  // 0x00faf4e0
};

// custom EA array allocator (0x00f473a0)
void* operator new[](unsigned int size, const char* name, int a, int b, int c, int d);
// 0x0092cb00
unsigned int* Memset32(unsigned int* dst, unsigned int value, int count);

int* FUN_00f48a60();                                                    // 0x00f48a60

cRibbonFaceVertex InterpolateRibbonPoly(const cRibbonFacePoly& poly,
                                        const cSPVector2& facePos);      // 0x00fafb50
char FUN_00faf920(cRibbonFacePoly* poly, float* pOut1, float* pOut2,
                  float v);                                             // 0x00faf920

// @ 0x00faf890 -- cTerrainSphereQuad::FUN_00faf890
void cTerrainSphereQuad::FUN_00faf890()
{
    if (mAboveBelowMap != 0)
    {
        operator delete(mAboveBelowMap);
        mAboveBelowMap = 0;
    }
    int raw = mChunkRes;
    _ReadWriteBarrier();
    int n = raw + 2;
    int q = n / 32 + 1;
    mAboveBelowStride = q;
    unsigned int count = q * n * 2;
    mAboveBelowCount = count;
    mAboveBelowMap = new("Terrain/SphereQuad/mAboveBelowMap", 0, 0, 0, 0) unsigned int[count];
    if (mAboveBelowMap != 0)
        Memset32((unsigned int*)mAboveBelowMap, 0, mAboveBelowCount);
}

// @ 0x00fafda0 -- cRibbonFacePoly::FUN_00fafda0
void cRibbonFacePoly::FUN_00fafda0()
{
    float minX = FLT_MAX;
    float maxX = -FLT_MAX;
    float minY = FLT_MAX;
    float maxY = FLT_MAX;

    int n = (int)(mpEnd - mpBegin);
    for (int i = 0; i < n; i++)
    {
        float x = mpBegin[i].mPos.x;
        float y = mpBegin[i].mPos.y;
        if (x <= minX) minX = x;
        if (maxX <= x) maxX = x;
        if (y <= minY) minY = y;
        if (maxY <= y) maxY = y;
    }

    mMinX = minX;
    mMinY = minY;
    mMaxX = maxX;
    mMaxY = maxY;
}

// @ 0x00fafb50 -- InterpolateRibbonPoly
cRibbonFaceVertex InterpolateRibbonPoly(const cRibbonFacePoly& poly,
                                        const cSPVector2& facePos)
{
    float f13 = (facePos.x - poly.mPatch[0].mPos.x) /
                (poly.mPatch[1].mPos.x - poly.mPatch[0].mPos.x);
    float f17 = 1.0f - f13;
    float f19 = poly.mPatch[1].mPos.y * f13 + poly.mPatch[0].mPos.y * f17;

    float f15 = (facePos.x - poly.mPatch[2].mPos.x) /
                (poly.mPatch[3].mPos.x - poly.mPatch[2].mPos.x);
    float f18 = 1.0f - f15;
    float f16 = poly.mPatch[3].mPos.y * f15 + poly.mPatch[2].mPos.y * f18;

    float f14 = (facePos.y - f19) / (f16 - f19);
    float f20 = 1.0f - f14;

    cRibbonFaceVertex v;
    v.mPos.x = (poly.mPatch[3].mPos.x * f15 + poly.mPatch[2].mPos.x * f18) * f14 +
               f20 * (poly.mPatch[1].mPos.x * f13 + poly.mPatch[0].mPos.x * f17);
    v.mPos.y = f16 * f14 + f20 * f19;
    v.mTC.x = (poly.mPatch[3].mTC.x * f15 + poly.mPatch[2].mTC.x * f18) * f14 +
              f20 * (poly.mPatch[1].mTC.x * f13 + poly.mPatch[0].mTC.x * f17);
    v.mTC.y = (poly.mPatch[3].mTC.y * f15 + poly.mPatch[2].mTC.y * f18) * f14 +
              (poly.mPatch[1].mTC.y * f13 + poly.mPatch[0].mTC.y * f17) * f20;
    v.mAlpha = (poly.mPatch[2].mAlpha * f18 + poly.mPatch[3].mAlpha * f15) * f14 +
               f20 * (poly.mPatch[0].mAlpha * f17 + poly.mPatch[1].mAlpha * f13);
    return v;
}

// @ 0x00faf920 -- FUN_00faf920
char FUN_00faf920(cRibbonFacePoly* poly, float* pOut1, float* pOut2, float v)
{
    cRibbonFaceVertex* begin = poly->mpBegin;
    cRibbonFaceVertex* end = poly->mpEnd;
    unsigned int count = (unsigned int)(end - begin);
    if (count < 3)
        return 0;

    bool bVar3 = true;
    bool bVar2 = true;
    for (cRibbonFaceVertex* p = begin; p != end; p++)
    {
        float y = p->mPos.y;
        if (v - 1.52587890625e-05f <= y)
        {
            if (v + 1.52587890625e-05f < y)
            {
                bVar3 = false;
                bVar2 = false;
            }
        }
        else
        {
            bVar3 = true;
            bVar2 = true;
        }
    }

    char cVar8 = 0;
    char local_19 = 0;
    cRibbonFaceVertex* prev = end - 1;
    for (cRibbonFaceVertex* cur = begin; cur != end; cur++)
    {
        float y = cur->mPos.y;
        bool hit;
        if (bVar2)
            hit = (v + 1.0e-08f < y);
        else
            hit = (y < v - 1.0e-08f);
        if (hit)
        {
            float f9 = (v - prev->mPos.y) / (y - prev->mPos.y);
            union { float f; unsigned int u; } fb;
            fb.f = f9;
            if ((fb.u & 0x7fffffffu) > 0x7f800000u)
                f9 = 0.5f;
            float f10 = 1.0f - f9;
            float f14 = y * f9 + prev->mPos.y * f10;
            float f11 = cur->mPos.x * f9 + f10 * prev->mPos.x;
            float f12 = cur->mTC.x * f9 + prev->mTC.x * f10;
            float f13 = cur->mTC.y * f9 + prev->mTC.y * f10;
            float f9b = prev->mAlpha * f10 + cur->mAlpha * f9;
            if (cVar8 == 0 || f11 < pOut1[0])
            {
                pOut1[0] = f11;
                pOut1[1] = f14;
                pOut1[2] = f12;
                pOut1[3] = f13;
                pOut1[4] = f9b;
                cVar8 = local_19;
            }
            if (cVar8 == 0 || (pOut2[0] <= f11 && f11 != pOut2[0]))
            {
                pOut2[0] = f11;
                pOut2[1] = f14;
                pOut2[2] = f12;
                pOut2[3] = f13;
                pOut2[4] = f9b;
            }
            bVar2 = !bVar3;
            cVar8 = 1;
            local_19 = 1;
            bVar3 = bVar2;
        }
        prev = cur;
    }
    return cVar8;
}

// @ 0x00faff10 -- cRibbonFacePoly::FUN_00faff10
void cRibbonFacePoly::FUN_00faff10()
{
    float local_c = FLT_MAX;
    float local_8 = -1.0f;
    int count = (int)(mpEnd - mpBegin);

    for (int i = 0; i < count; i++)
    {
        local_c = Min(local_c, mpBegin[i].mPos.y);
        local_8 = Max(local_8, mpBegin[i].mPos.y);
    }

    float range = local_8 - local_c;
    FUN_00faf920(this, &mPatch[0].mPos.x, &mPatch[1].mPos.x, range * 0.3f + local_c);
    FUN_00faf920(this, &mPatch[2].mPos.x, &mPatch[3].mPos.x, range * 0.6f + local_c);
}

// @ 0x00faf4e0 -- cTerrainSphereQuad::FUN_00faf4e0
void cTerrainSphereQuad::FUN_00faf4e0(int key, RasterState* states, int flag)
{
    if (g_lastFace == key && mFace == g_lastKey && flag == 0)
        return;

    g_lastFace = key;
    g_lastKey = mFace;

    int* table = FUN_00f48a60();
    int entry = *(int*)((char*)table + 0x5c + key * 4);
    if (entry == 0)
        return;
    CompiledState* pState = *(CompiledState**)(entry + 4);
    if (pState == 0)
        return;

    int** base = (int**)((char*)mSphere->GetInfo() + 0x2f4);

    switch (key)
    {
    case 0:
        states[0].Assign(pState, 0, mSphere->GetQuadKeyB(mFace));
        states[1].Assign(pState, 1, *base[3]);
        states[2].Assign(pState, 2, mSphere->GetKeyD(mFace));
        states[3].Assign(pState, 3, g_pTextureInstance->mFirst);
        break;
    case 1:
        states[0].Assign(pState, 0, mSphere->GetQuadKeyB(mFace));
        states[1].Assign(pState, 1, mSphere->GetQuadKeyA(mFace));
        states[2].Assign(pState, 2, mSphere->GetKeyD(mFace));
        break;
    case 2:
        states[0].Assign(pState, 0, mSphere->GetQuadKeyA(mFace));
        states[1].Assign(pState, 1, *base[1]);
        states[2].Assign(pState, 2, *base[0]);
        states[3].Assign(pState, 3, *base[2]);
        states[4].Assign(pState, 4, g_pTextureInstance->mFirst);
        states[5].Assign(pState, 5, mSphere->GetKeyE());
        break;
    case 3:
        states[0].Assign(pState, 0, mSphere->GetQuadKeyB(mFace));
        states[1].Assign(pState, 1, mSphere->GetQuadKeyA(mFace));
        states[2].Assign(pState, 2, *base[6]);
        states[3].Assign(pState, 3, *base[4]);
        states[4].Assign(pState, 4, *base[1]);
        states[5].Assign(pState, 5, *base[5]);
        states[6].Assign(pState, 6, *base[2]);
        states[7].Assign(pState, 7, g_pTextureInstance->mFirst);
        break;
    case 4:
        states[0].Assign(pState, 0, mSphere->GetQuadKeyB(mFace));
        states[1].Assign(pState, 1, mSphere->GetQuadKeyA(mFace));
        states[2].Assign(pState, 2, *base[4]);
        states[3].Assign(pState, 3, *base[7]);
        states[4].Assign(pState, 4, *base[9]);
        states[5].Assign(pState, 5, *base[8]);
        states[6].Assign(pState, 6, g_pTextureInstance->mFirst);
        break;
    case 5:
        states[0].Assign(pState, 0, g_pTextureInstance->mFirst);
        states[1].Assign(pState, 1, *base[12]);
        break;
    case 6:
    case 7:
    case 8:
    case 9:
        states[0].Assign(pState, 0, mSphere->GetQuadKeyB(mFace));
        states[1].Assign(pState, 1, flag);
        states[2].Assign(pState, 2, g_pTextureInstance->GetRaster());
        break;
    case 10:
        {
            int arr[5];
            arr[0] = 0;
            arr[1] = mSphere->GetQuadKeyA(mFace);
            arr[2] = mSphere->GetQuadKeyB(mFace);
            arr[3] = mSphere->GetQuadKeyC(mFace);
            arr[4] = mSphere->GetKeyD(mFace);
            int* t = FUN_00f48a60();
            states[0].Assign(pState, 0, arr[*(int*)((char*)t + 8)]);
        }
        break;
    default:
        break;
    }

    pState->Dispatch();
}
