// src/game/SPTerrain/SPTerrainMapSet.cpp -- migrated from slice(s) s00f927c0, s00f918d0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainMapSet.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTerrainMapBase.h"
#include "SP/cTerrainMapSet.h"
#include "SP/cTerrainStateMgr.h"
#include <new>
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern const uint8_t g01491464[16]; // 0x01491464  nibble-expansion table

// ---- items of slice s00f918d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl operator new[](unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
extern const uint8_t g01491464[16]; // 0x01491464  nibble-expansion table
struct HRCell { uint16_t mLo; uint16_t mHi; };
struct HRSource { uint16_t mWords[8]; };
struct HeightRanges {
    int mCounts[6];      // +0x00
    HRCell* mpData;      // +0x18
    HeightRanges* Init();                                             // 0x00f92540
    int Merge(int level, int index, int x0, int y0, int x1, int y1);  // 0x00f925b0
};
// ---- items of slice s00f918d0 end

// ---- items of slice s00f927c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const unsigned char g_scatter[];                     // 0x01491464
void* __cdecl EAAllocate(unsigned int size, const char* name, int, int, int, int);  // 0x00f473a0
void __cdecl op_delete(void*);                                                       // 0x00f47380
struct GmeRefCount {
    GmeRefCount() : mRefCount(0) {}
    virtual ~GmeRefCount() {}
    void AddRef() { ++mRefCount; }
    void Release() {
        int m = mRefCount;
        mRefCount = m - 1;
        if (m - 1 == 0) {
            mRefCount = 1;
            delete this;
        }
    }
    int mRefCount;                                          // +0x04
};
struct CubeUV { float u; float v; int face; };
struct cTerrainMapBase : GmeRefCount {
    unsigned int  mFaceSize;                                // +0x08
    unsigned int  mModCount;                                // +0x0c
};
struct cTerrainMapU16 : cTerrainMapBase {
    unsigned short* mBegin;                                 // +0x10
    float GetFloat(const CubeUV*);                          // 0x00f8d620
    void  GetVector4(float*, const CubeUV*);                // 0x00f89e50
};
struct cHeightRanges {
    cHeightRanges();                                        // 0x00f92540
    ~cHeightRanges() { op_delete(mCells); mCells = 0; }
    unsigned short* At(int, int, int, int);                 // 0x00f63da0
    int mField00;                                           // +0x00
    int mField04;                                           // +0x04
    int mField08;                                           // +0x08
    int mField0C;                                           // +0x0c
    int mField10;                                           // +0x10
    int mField14;                                           // +0x14
    unsigned short* mCells;                                 // +0x18
};
struct cSPVector3_s00f9_27c0 { float x, y, z; };
extern cSPVector3_s00f9_27c0 g_defNormal;                              // 0x016c9c08
extern cSPVector3_s00f9_27c0 g_n;                                      // 0x015b0fa4
struct TerrainRect {
    int m0;                                                 // +0x00
    int m1;                                                 // +0x04
    int m2;                                                 // +0x08
    int m3;                                                 // +0x0c
    int m4;                                                 // +0x10
    int m5;                                                 // +0x14
    unsigned int* m6;                                       // +0x18

    void Build(cTerrainMapU16*, int, int, int, int, int);   // 0x00f92e30
    void Set(cTerrainMapU16*, int, const float*);           // 0x00f92ff0
    void Fill(int, int, int, int, int, int);                // 0x00f925b0
};
struct cTerrainMapSet : GmeRefCount {
    cTerrainMapSet();                                       // 0x00f92a50
    virtual ~cTerrainMapSet();                              // 0x00f92b10
    float GetHeightAt(const cSPVector3_s00f9_27c0&);                   // 0x00f927c0
    void  GetHeightRange(int, int, int, int, float*, float*);  // 0x00f929c0
    void  ReleaseMaps();                                    // 0x00f92b90
    void  RegisterMap(int, cTerrainMapBase*);               // 0x00f92be0
    void  GetNormalAt(cSPVector3_s00f9_27c0*, const cSPVector3_s00f9_27c0*);      // 0x00f92c20

    cTerrainMapBase* mMaps[11];                             // +0x08
    float mRadius;                                          // +0x34
    float mMaxHeight;                                       // +0x38
    float mWaterHeight;                                     // +0x3c
    float mWaterDelta;                                      // +0x40
    float mBeachHeight;                                     // +0x44
    float mMinCliffGradient;                                // +0x48
    float mMaxCliffGradient;                                // +0x4c
    float mHeightRangeX;                                    // +0x50
    float mHeightRangeY;                                    // +0x54
    cHeightRanges* mHeightRanges;                           // +0x58
};
// ---- items of slice s00f927c0 end

// @ 0x00f92540
HeightRanges* HeightRanges::Init()
{
    mCounts[0] = 0x555;
    mpData = 0;
    int n = 0x1ffe;
    mpData = new ("Terrain/HeightRanges/cCell", 0, 0, 0, 0) HRCell[n];
    mCounts[1] = 1;
    mCounts[2] = 5;
    mCounts[3] = 0x15;
    mCounts[4] = 0x55;
    mCounts[5] = 0x155;
    return this;
}

// @ 0x00f925b0
int HeightRanges::Merge(int level, int index, int x0, int y0, int x1, int y1)
{
    const int y1Raw = y1;
    x0 /= 2;
    x1 /= 2;
    y0 /= 2;
    y1 /= 2;
    if (x0 == x1)
        return y1Raw + (y1Raw < 0 ? 1 : 0);
    int* p = mCounts + level + 2;
    int ret = level;
    do {
        if (y0 == y1)
            return ret;
        HRCell* pA = mpData + (p[-1] + mCounts[0] * index);
        HRSource* pB = (HRSource*)(mpData + (p[0] + mCounts[0] * index));
        int changed = 0;
        if (y0 >= y1)
            return y0;
        for (int y = y0; y < y1; ++y) {
            if (x0 < x1) {
                const uint8_t* pYHi = &g01491464[y >> 4];
                const uint8_t* pYLo = &g01491464[y & 0xf];
                for (int x = x0; x < x1; ++x) {
                    unsigned xHi = g01491464[x >> 4];
                    unsigned xLo = g01491464[x & 0xf];
                    unsigned idx = ((xHi | (*pYHi << 1)) << 7 | *pYLo) * 2 | xLo;
                    HRSource* src = pB + idx;
                    HRCell* dst = pA + idx;
                    uint16_t lo = src->mWords[0];
                    uint16_t hi = src->mWords[1];
                    if (lo > src->mWords[2]) lo = src->mWords[2];
                    if (hi < src->mWords[3]) hi = src->mWords[3];
                    if (lo > src->mWords[4]) lo = src->mWords[4];
                    if (hi < src->mWords[5]) hi = src->mWords[5];
                    if (lo > src->mWords[6]) lo = src->mWords[6];
                    if (hi < src->mWords[7]) hi = src->mWords[7];
                    if (dst->mLo != lo || dst->mHi != hi) {
                        ++changed;
                        dst->mLo = lo;
                        dst->mHi = hi;
                    }
                }
            }
        }
        if (changed == 0)
            return y1;
        if (level <= 0)
            return y1;
        x0 /= 2;
        --level;
        --p;
        y0 /= 2;
        x1 /= 2;
        y1 /= 2;
        ret = y1;
    } while (x0 != x1);
    return y1;
}

// @ 0x00f927c0
float cTerrainMapSet::GetHeightAt(const cSPVector3_s00f9_27c0& p)
{
    if (mMaps[0] == 0)
        return mRadius;

    cTerrainMapU16* map = (cTerrainMapU16*)mMaps[0];
    CubeUV uv;

    float x = p.x;
    float y = p.y;
    float z = p.z;
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);

    if (ax <= az && ay <= az) {
        uv.u = (x / z + 1.0f) * 0.5f;
        uv.v = (y / az + 1.0f) * 0.5f;
        if (z < 0.0f) {
            uv.face = 1;
            return map->GetFloat(&uv) * mMaxHeight + mRadius;
        }
        uv.face = 0;
        return map->GetFloat(&uv) * mMaxHeight + mRadius;
    }
    if (ay < ax) {
        uv.u = (y / x + 1.0f) * 0.5f;
        uv.v = (z / ax + 1.0f) * 0.5f;
        uv.face = 2;
        if (x < 0.0f)
            uv.face = 3;
        return map->GetFloat(&uv) * mMaxHeight + mRadius;
    }
    uv.u = (z / y + 1.0f) * 0.5f;
    uv.v = (x / ay + 1.0f) * 0.5f;
    if (y < 0.0f) {
        uv.face = 5;
        return map->GetFloat(&uv) * mMaxHeight + mRadius;
    }
    uv.face = 4;
    return map->GetFloat(&uv) * mMaxHeight + mRadius;
}

// @ 0x00f929c0
void cTerrainMapSet::GetHeightRange(int a2, int a3, int a4, int a5, float* a6, float* a7)
{
    if (mHeightRanges != 0) {
        int sh = a2 - 4;
        if (sh > 0) {
            a4 >>= sh;
            a2 -= sh;
            a5 >>= sh;
        }
        unsigned short* p = mHeightRanges->At(a2, a3, a4, a5);
        *a6 = (float)(int)(p[0] - 0x8000) * 3.0518509447574615e-05f;
        *a7 = (float)(int)(p[1] - 0x8000) * 3.0518509447574615e-05f;
    } else {
        *a6 = mHeightRangeX;
        *a7 = mHeightRangeY;
    }
}

// @ 0x00f92a50
cTerrainMapSet::cTerrainMapSet()
{
    mMaps[0] = 0;
    mMaps[1] = 0;
    mMaps[2] = 0;
    mMaps[3] = 0;
    mMaps[4] = 0;
    mMaps[5] = 0;
    mMaps[6] = 0;
    mMaps[7] = 0;
    mMaps[8] = 0;
    mMaps[9] = 0;
    mMaps[10] = 0;
    mRadius = 500.0f;
    mMaxHeight = 100.0f;
    mWaterHeight = 0.0f;
    mWaterDelta = 0.0f;
    mBeachHeight = 0.025f;
    mMinCliffGradient = 0.0f;
    mMaxCliffGradient = 0.0f;
    mHeightRangeX = -1.0f;
    mHeightRangeY = 1.0f;
    void* p = EAAllocate(0x1c, "Terrain/TerrainMapSet/cHeightRanges", 0, 0, 0, 0);
    mHeightRanges = p ? new (p) cHeightRanges : 0;
}

// @ 0x00f92b10
cTerrainMapSet::~cTerrainMapSet()
{
    cHeightRanges* hr = mHeightRanges;
    if (hr != 0) {
        op_delete(hr->mCells);
        hr->mCells = 0;
        op_delete(hr);
    }

    cTerrainMapBase** p = mMaps + 11;
    int n = 10;
    do {
        cTerrainMapBase* q = *--p;
        if (q != 0)
            q->Release();
    } while (--n >= 0);
}

// @ 0x00f92b90
void cTerrainMapSet::ReleaseMaps()
{
    for (int i = 0; i < 11; ++i) {
        cTerrainMapBase* p = mMaps[i];
        if (p != 0) {
            mMaps[i] = 0;
            p->Release();
        }
    }
}

// @ 0x00f92be0
void cTerrainMapSet::RegisterMap(int idx, cTerrainMapBase* p)
{
    cTerrainMapBase* old = mMaps[idx];
    if (p != old) {
        if (p != 0)
            p->AddRef();
        mMaps[idx] = p;
        if (old != 0)
            old->Release();
    }
}

// @ 0x00f92c20
void cTerrainMapSet::GetNormalAt(cSPVector3_s00f9_27c0* out, const cSPVector3_s00f9_27c0* in)
{
    cTerrainMapU16* map = (cTerrainMapU16*)mMaps[1];
    if (map == 0) {
        out->x = g_defNormal.x;
        out->y = g_defNormal.y;
        out->z = g_defNormal.z;
        return;
    }

    float x = in->x;
    float y = in->y;
    float z = in->z;

    CubeUV uv;
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);
    if (az < ax || az < ay) {
        if (ay < ax) {
            uv.u = (y / x + 1.0f) * 0.5f;
            uv.v = (z / ax + 1.0f) * 0.5f;
            uv.face = 2;
            if (x < 0.0f)
                uv.face = 3;
        } else {
            uv.u = (z / y + 1.0f) * 0.5f;
            uv.v = (x / ay + 1.0f) * 0.5f;
            if (y < 0.0f)
                uv.face = 5;
            else
                uv.face = 4;
        }
    } else {
        uv.u = (x / z + 1.0f) * 0.5f;
        uv.v = (y / az + 1.0f) * 0.5f;
        if (z < 0.0f)
            uv.face = 1;
        else
            uv.face = 0;
    }

    float r[4];
    map->GetVector4(r, &uv);
    out->x = r[0] * 2.0f - g_n.x;
    out->y = r[1] * 2.0f - g_n.y;
    out->z = r[2] * 2.0f - g_n.z;
}

// @ 0x00f92e30
void TerrainRect::Build(cTerrainMapU16* map, int p3, int p4, int p5, int p6, int p7)
{
    int face = map->mFaceSize;
    int g = (face + (face >> 31 & 0xf)) >> 4;
    int r0 = this->m0;
    int r5 = this->m5;
    unsigned int* outBase = this->m6;

    if (p5 < p7) {
        unsigned short* rowp = (unsigned short*)((char*)map->mBegin
            + face * face * p3 * 2 + g * face * p5 * 2);
        int j = p5;
        do {
            if (p4 < p6) {
                unsigned short* src = (unsigned short*)((char*)rowp + g * p4 * 2);
                int i = p4;
                do {
                    int idx = ((((g_scatter[(i >> 4) & 0xf] | g_scatter[(j >> 4) & 0xf] * 2) << 7)
                                | g_scatter[j & 0xf]) * 2) | g_scatter[i & 0xf];
                    unsigned short* cell = (unsigned short*)((char*)outBase + (r0 * p3 + r5) * 4 + idx * 4);
                    unsigned short v = src[0];
                    cell[0] = v;
                    cell[1] = v;
                    if (g > 0) {
                        unsigned short* rp = src;
                        for (int r = g; r != 0; --r) {
                            for (int c = 0; c < g; ++c) {
                                unsigned short u = rp[c];
                                if (u < cell[0]) cell[0] = u;
                                else if (cell[1] < u) cell[1] = u;
                            }
                            rp += face;
                        }
                    }
                    ++i;
                    src += g;
                } while (i < p6);
            }
            rowp += g * face;
            ++j;
        } while (j < p7);
    }

    Fill(3, p3, p4, p5, p6, p7);
}

// @ 0x00f92ff0
void TerrainRect::Set(cTerrainMapU16* map, int a3, const float* v)
{
    float f1 = 0.0f;
    if (0.0f <= v[1]) f1 = v[1];
    if (1.0f <= f1) f1 = 1.0f;

    float f0 = 0.0f;
    if (0.0f <= v[0]) f0 = v[0];
    if (1.0f <= f0) f0 = 1.0f;

    float f3 = 0.0f;
    if (0.0f <= v[3]) f3 = v[3];
    if (1.0f <= f3) f3 = 1.0f;

    float f2 = 0.0f;
    if (0.0f <= v[2]) f2 = v[2];
    if (1.0f <= f2) f2 = 1.0f;

    int i1 = (int)(f0 * 16.0f);
    if (f0 * 16.0f < (float)i1) --i1;
    int i2 = (int)(f1 * 16.0f);
    if (f1 * 16.0f < (float)i2) --i2;
    int i3 = (int)(f2 * 16.0f);
    if ((float)i3 < f2 * 16.0f) ++i3;
    int i4 = (int)(f3 * 16.0f);
    if ((float)i4 < f3 * 16.0f) ++i4;

    Build(map, a3, i1, i2, i3, i4);
}
