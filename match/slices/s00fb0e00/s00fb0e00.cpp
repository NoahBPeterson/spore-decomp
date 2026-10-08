// Slice s00fb0e00: SP::cTerrainSphereQuad::RebuildHeightVB @ 0x00fb0e00 (Claude-coined name).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same module as the other cTerrainSphereQuad slices.
//
// Locks the quad's height vertex buffer and writes, for every grid point of the (mChunkRes+3)^2 grid
// (one border row/column on each side for skirts/morphing), a 4x16-bit record:
//   word0 (dword [0]):  low 16 = packed height, high 16 = packed morph target height
//   word1 (dword [4]):  only if the vertex format has a second element: low 16 = packed "cap" height, high 16 = packed raw height
// Heights are cube-map terrain heights (cTerrainMap<ushort>::GetFloat) mapped by round(h*32767)+0x8000, clamped below at 0.
// Border points are pushed down by a skirt depth (property 0xd81e2934, default 0.15) to hide cracks. Odd grid points
// take the average of their two neighbours (so the mesh morphs to the parent LOD).
#include "types.h"
#include <float.h>

struct cSPVector2 { float x, y; };
struct cCubeMapCoord { float u, v; int face; };

namespace rw { namespace graphics {
struct VBDesc { char pad[0xc]; unsigned short numElements; unsigned char pad2; unsigned char stride; };   // +0xc, +0xf
struct VertexBuffer {
    VBDesc* desc;           // +0
    void*   d3dvb;          // +4
    unsigned base;          // +8
    unsigned numVertices;   // +0xc
    void* Lock(int flags, int offsetBytes, int sizeBytes);     // 0x011f3620
    void  Unlock();                                            // 0x011f36a0
};
} }

namespace SP {

template <class T> struct cTerrainMap {
    float GetFloat(const cCubeMapCoord& c) const;       // 0x00f8d620
};

struct cTerrainMapSet {
    unsigned pad00[2];
    cTerrainMap<unsigned short>* mHeightMap;   // +0x08
    unsigned pad0c[0x34 / 4 - 3];
    float mRadius;                              // +0x34
    float mMaxHeight;                           // +0x38
    float mWaterHeight;                         // +0x3c
};

struct cTerrainSphere {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual cTerrainMapSet* GetMapSet();        // +0xc
    virtual void* GetInfo();                    // +0x10
};

struct cDirectPropertyList {
    bool  GetBool(unsigned id);                 // 0x006a25a0 (named SP::cPropertyList::GetDescription by Ghidra)
    float GetFloatProperty(unsigned id);        // 0x006a2710
};
extern cDirectPropertyList* g_AppProperties;    // 0x015fd918
void __cdecl GetFloatProp(cDirectPropertyList* list, unsigned id, float* out);   // 0x0040cf10
extern char g_016d66aa;                         // 0x016d66aa

// wraps a cube-face coordinate that left [0,1] onto the neighbouring face
void __cdecl WrapCubeCoord(int* face, float* u, float* v, int a, int b, int c);   // 0x00685200

struct cTerrainSphereQuad {
    cTerrainSphere* mSphere;        // +0x00
    cTerrainSphereQuad* mParent;    // +0x04
    unsigned pad08[4];
    int   mChunkRes;                // +0x18
    int   mFace;                    // +0x1c
    unsigned pad20[4];
    float mFaceScale;               // +0x30
    unsigned pad34[(0x58 - 0x34) / 4];
    float mUVOffX;                  // +0x58
    float mUVOffY;                  // +0x5c
    float mUVScale;                 // +0x60
    unsigned pad64[(0x88 - 0x64) / 4];
    float mMinH;                    // +0x88
    float mMaxH;                    // +0x8c
    unsigned pad90[1];
    rw::graphics::VertexBuffer** mHeightVB;   // +0x94

    void  SetupVertexScale(int flag);           // 0x00fb0bd0
    bool  RebuildHeightVB();                    // 0x00fb0e00
};

// minss/maxss clamp helper of the /arch:SSE module
inline float ClampF(float v, float lo, float hi)
{
    __asm {
        movss xmm0, v
        maxss xmm0, lo
        minss xmm0, hi
        movss v, xmm0
    }
    return v;
}

inline int RoundToInt(float f) { __asm cvtss2si eax, f }

// round(h*32767) + 0x8000, clamped below at 0 through a reference select, truncated to 16 bits
__forceinline unsigned short PackHeight(float h)
{
    float scaled = h * 32767.0f;
    int t = RoundToInt(scaled) + 0x8000;
    int zero = 0;
    const int& r = t > 0 ? t : zero;
    return (unsigned short)r;
}

// @ 0x00fb0e00
bool cTerrainSphereQuad::RebuildHeightVB()
{
    rw::graphics::VertexBuffer** pvb = mHeightVB;
    if (!pvb || !*pvb) return false;
    rw::graphics::VertexBuffer* vb = *pvb;
    rw::graphics::VBDesc* desc = vb->desc;
    if (!desc) return false;

    bool hasSecond = desc->numElements > 1;
    unsigned char vsize = desc->stride;
    unsigned* out = (unsigned*)vb->Lock(10, vsize * vb->base, vsize * vb->numVertices);
    if (!out) return false;

    unsigned stride = vb->desc->stride;
    int n = mChunkRes + 3;
    cTerrainMapSet* mapSet = mSphere->GetMapSet();
    cTerrainMap<unsigned short>* hmap = mapSet->mHeightMap;
    mMinH = FLT_MAX;
    mMaxH = 0.0f;
    mSphere->GetInfo();
    float water = mapSet->mWaterHeight;
    float radius = mapSet->mRadius;
    float maxHeight = mapSet->mMaxHeight;
    float waterRadius = water * maxHeight + radius;
    float invRes = 1.0f / (float)mChunkRes;
    float halfStep = mFaceScale * invRes;
    SetupVertexScale(1);

    float skirt = 0.15f;
    GetFloatProp(g_AppProperties, 0xd81e2934, &skirt);
    bool smooth = g_AppProperties->GetBool(0xf3ea2b1d);
    if (g_016d66aa == 0) {
        if (!smooth) smooth = false;
        else {
            smooth = true;
            if (mParent != 0) smooth = false;
        }
    }
    float smoothAmt = g_AppProperties->GetFloatProperty(0x7580d2c2);

    float rowAcc = 0.0f;
    for (int i = 0; i < n; i++) {
        float colAcc = 0.0f;
        bool rowEdge = (i == 0) || (i == n - 1);
        if (i > 1 && i < n - 1) rowAcc += invRes;
        int iOdd = i & 1;
        for (int j = 0; j < n; j++) {
            bool isEdge = !(!rowEdge && j != 0 && j != n - 1);
            if (j > 1 && j < n - 1) colAcc += invRes;

            cCubeMapCoord c;
            c.face = mFace;
            c.v = mUVScale * rowAcc + mUVOffY;
            c.u = mUVScale * colAcc + mUVOffX;
            float u0 = c.u, v0 = c.v;
            if (c.u < 0.0f || c.v < 0.0f || c.u > 1.0f || c.v > 1.0f)
                WrapCubeCoord(&c.face, &c.u, &c.v, 0, 0, 0);

            float h = hmap->GetFloat(c);
            float h2 = h;
            if (h * maxHeight + radius < waterRadius) h2 = water;
            if (isEdge) {
                float lo = h2 - skirt;
                float hi = h2 - 0.01f;
                h2 = ClampF(mMinH, lo, hi);
            }
            unsigned short pHeight = PackHeight(h2);
            unsigned short pRaw = PackHeight(h);
            unsigned short pA = pHeight, pB = pRaw;

            int jOdd = j & 1;
            if (!isEdge && (!jOdd || !iOdd)) {
                cCubeMapCoord c1, c2;
                c1.face = c2.face = mFace;
                c1.u = u0; c1.v = v0;
                c2.u = u0; c2.v = v0;
                if (!jOdd) {
                    c1.u = u0 - halfStep;
                    c2.u = u0 + halfStep;
                    if (!iOdd) {
                        c1.v = v0 + halfStep;
                        c2.v = v0 - halfStep;
                    }
                } else {
                    c1.v = v0 - halfStep;
                    c2.v = v0 + halfStep;
                }
                if (c1.u < 0.0f || c1.v < 0.0f || c1.u > 1.0f || c1.v > 1.0f)
                    WrapCubeCoord(&c1.face, &c1.u, &c1.v, 0, 0, 0);
                if (c2.u < 0.0f || c2.v < 0.0f || c2.u > 1.0f || c2.v > 1.0f)
                    WrapCubeCoord(&c2.face, &c2.u, &c2.v, 0, 0, 0);
                float g1 = hmap->GetFloat(c1);
                float g2 = hmap->GetFloat(c2);
                float avg = (g2 + g1) * 0.5f;
                float avgClamped = avg;
                if (avg < water) avgClamped = water;
                pA = PackHeight(avgClamped);
                pB = PackHeight(avg);
            }

            out[0] = ((unsigned)pA << 16) | pHeight;
            (void)pB;
            unsigned short pLast;
            if (hasSecond) {
                if (smooth && u0 > invRes && 1.0f - invRes > u0 && v0 > invRes && 1.0f - invRes > v0) {
                    float r = smoothAmt * invRes;
                    int fc = mFace;
                    cCubeMapCoord k0 = { u0 - r, v0, fc };
                    cCubeMapCoord k1 = { u0 + r, v0, fc };
                    cCubeMapCoord k2 = { u0, v0 - r, fc };
                    cCubeMapCoord k3 = { u0, v0 + r, fc };
                    cCubeMapCoord k4 = { u0 - r, v0 - r, fc };
                    cCubeMapCoord k5 = { u0 - r, v0 + r, fc };
                    cCubeMapCoord k6 = { u0 + r, v0 - r, fc };
                    cCubeMapCoord k7 = { u0 + r, v0 + r, fc };
                    float g[8];
                    g[0] = hmap->GetFloat(k0);
                    g[1] = hmap->GetFloat(k1);
                    g[2] = hmap->GetFloat(k2);
                    g[3] = hmap->GetFloat(k3);
                    g[4] = hmap->GetFloat(k4);
                    g[5] = hmap->GetFloat(k5);
                    g[6] = hmap->GetFloat(k6);
                    g[7] = hmap->GetFloat(k7);
                    float m12 = g[0] > g[1] ? g[0] : g[1];
                    float m34 = g[2] > g[3] ? g[2] : g[3];
                    float m56 = g[4] > g[5] ? g[4] : g[5];
                    float m78 = g[6] > g[7] ? g[6] : g[7];
                    float mA = m12 > m34 ? m12 : m34;
                    float mB = m56 > m78 ? m56 : m78;
                    float m = mA > mB ? mA : mB;
                    if (!(m > h)) m = h;
                    if (m > water) m = water;
                    pLast = PackHeight(m);
                } else {
                    float m = h2;
                    if (m > water) m = water;
                    pLast = PackHeight(m);
                }
                out[1] = ((unsigned)pB << 16) | pLast;
            }
            out = (unsigned*)((char*)out + stride);
        }
    }
    (*mHeightVB)->Unlock();
    return true;
}

} // namespace SP
