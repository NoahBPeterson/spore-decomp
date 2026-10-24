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
class VertexBuffer { public:
    VBDesc* desc;           // +0
    void*   d3dvb;          // +4
    unsigned base;          // +8
    unsigned numVertices;   // +0xc
    void* Lock(int flags, int offsetBytes, int sizeBytes);     // 0x011f3620
    void  Unlock();                                            // 0x011f36a0
};
} }

namespace SP {

template <class T> class cTerrainMap { public:
    float GetFloat(const cCubeMapCoord& c) const;       // 0x00f8d620
};

class cTerrainMapSet { public:
    unsigned pad00[2];
    cTerrainMap<unsigned short>* mHeightMap;   // +0x08
    unsigned pad0c[0x34 / 4 - 3];
    float mRadius;                              // +0x34
    float mMaxHeight;                           // +0x38
    float mWaterHeight;                         // +0x3c
};

class cTerrainSphere { public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual cTerrainMapSet* GetMapSet();        // +0xc
    virtual void* GetInfo();                    // +0x10
};

class cDirectPropertyList { public:
    bool  GetBool(unsigned id);                 // 0x006a25a0 (named SP::cPropertyList::GetDescription by Ghidra)
    float GetFloatProperty(unsigned id);        // 0x006a2710
};
extern cDirectPropertyList* g_AppProperties;    // 0x015fd918
void __cdecl GetFloatProp(cDirectPropertyList* list, unsigned id, float* out);   // 0x0040cf10
extern char g_016d66aa;                         // 0x016d66aa

extern const float kOne;                        // 0x01485720 (1.0f)
extern const float kNegOne;                     // 0x013eb1bc (-1.0f)
// Axis order of the opposite hemisphere: three 4-byte entries holding the 0/1/2 permutations
// {012}, {201}, {120}; the first entry of the {012,120,201} table lives 0xc bytes earlier.
extern const unsigned char g_faceAxisOrderNeg[][4];   // 0x014910a0

// wraps a cube-face coordinate that left [0,1] onto the neighbouring face
void __cdecl WrapCubeCoord(int* face, float* u, float* v, int a, int b, int c);   // 0x00685200

struct Vec4 {
    union {
        struct { float x, y, z, w; };
        float v[4];
    };
};

// rw::math::fpu::Matrix44Template<float,0>; the only member the quad needs is the 4x4 block
struct Matrix44 {
    Vec4 r[4];                                  // 4 x 16 bytes
    Matrix44(const float* src);                 // 0x0045dca0 (real call, never inlined)
};
float* __cdecl Transpose(float* dst, const float* src);            // 0x006ffdc0, returns dst
void   __cdecl SetShaderParam(int id, const void* value, int n);   // 0x00777ae0

extern const float kTwo;                        // 0x01470f1c (2.0f)
// Tail of the sprite/terrain info block reachable through cTerrainSphere::GetInfo(); only the
// morph-target pointer at +0x2f4+0x54 is of interest here.
struct cInfoTail { unsigned pad54[0x54 / 4]; void* mpTarget; };

class cTerrainSphereQuad { public:
    cTerrainSphere* mSphere;        // +0x00
    cTerrainSphereQuad* mParent;    // +0x04
    unsigned pad08[4];
    int   mChunkRes;                // +0x18
    int   mFace;                    // +0x1c
    float mOriginX;                 // +0x20
    float mOriginY;                 // +0x24
    unsigned pad28[2];
    float mFaceScale;               // +0x30
    unsigned pad34[3];
    int   mAxisX;                   // +0x40
    int   mAxisY;                   // +0x44
    int   mAxisZ;                   // +0x48
    float mScaleX;                  // +0x4c
    float mScaleY;                  // +0x50
    float mScaleZ;                  // +0x54
    float mUVOffX;                  // +0x58
    float mUVOffY;                  // +0x5c
    float mUVScale;                 // +0x60
    float mFaceParam;               // +0x64
    unsigned pad68[(0x88 - 0x68) / 4];
    float mMinH;                    // +0x88
    float mMaxH;                    // +0x8c
    unsigned pad90[1];
    rw::graphics::VertexBuffer** mHeightVB;   // +0x94
    unsigned pad98[3];
    Matrix44 mWorld;                // +0xa4  world transform handed to the shader
    Vec4 mFaceTransform[4];         // +0xe4  uv offset/scale, face parameter, axis indices, sign scales
    Vec4 mFaceAxes[3];              // +0x124 cube-face basis rows (permuted, then sign-scaled)

    void  SetupVertexScale(int flag);           // 0x00fb0bd0
    bool  RebuildHeightVB();                    // 0x00fb0e00
    void  BuildFaceTransform(void* pParent);    // 0x00fb1780
    void  ApplyFaceAxes();                      // 0x00fb1b80
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

// @ 0x00fb1780
void cTerrainSphereQuad::BuildFaceTransform(void* pParent)
{
    void* info = mSphere->GetInfo();
    cInfoTail* tail = (cInfoTail*)((char*)info + 0x2f4);

    Matrix44 mat((const float*)((const char*)pParent + 0xc0));
    float scratch[16];
    mWorld = *(Matrix44*)Transpose(scratch, (const float*)&mat);

    Vec4 v;
    v.x = mUVOffX;
    v.y = mUVOffY;
    v.z = mUVScale;
    v.w = 0.0f;
    mFaceTransform[0] = v;
    v.x = mFaceParam;
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = 0.0f;
    mFaceTransform[1] = v;
    v.x = (float)mAxisX;
    v.y = (float)mAxisY;
    v.z = (float)mAxisZ;
    v.w = 0.0f;
    mFaceTransform[2] = v;
    v.x = mScaleX;
    v.y = mScaleY;
    v.z = mScaleZ;
    v.w = 0.0f;
    mFaceTransform[3] = v;

    // the same 16-byte-stride store is reused for the (2,0,0,-1) cube-face basis
    v.x = kTwo;
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = kNegOne;
    mat.r[0] = v;
    v.x = 0.0f;
    v.y = kTwo;
    v.z = 0.0f;
    v.w = kNegOne;
    mat.r[1] = v;
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = kTwo;
    v.w = kNegOne;
    mat.r[2] = v;

    mFaceAxes[0] = mat.r[mAxisX];
    mFaceAxes[1] = mat.r[mAxisY];
    mFaceAxes[2] = mat.r[mAxisZ];

    float s0 = mScaleX;
    mFaceAxes[0].x = s0 * mFaceAxes[0].x;
    mFaceAxes[0].y = s0 * mFaceAxes[0].y;
    mFaceAxes[0].z = s0 * mFaceAxes[0].z;
    mFaceAxes[0].w = s0 * mFaceAxes[0].w;
    float s1 = mScaleY;
    mFaceAxes[1].x = s1 * mFaceAxes[1].x;
    mFaceAxes[1].y = s1 * mFaceAxes[1].y;
    mFaceAxes[1].z = s1 * mFaceAxes[1].z;
    mFaceAxes[1].w = s1 * mFaceAxes[1].w;
    float s2 = mScaleZ;
    mFaceAxes[2].x = s2 * mFaceAxes[2].x;
    mFaceAxes[2].y = s2 * mFaceAxes[2].y;
    mFaceAxes[2].z = s2 * mFaceAxes[2].z;
    mFaceAxes[2].w = s2 * mFaceAxes[2].w;

    SetShaderParam(0x301, &mWorld, 0);
    void* pTarget = tail->mpTarget;
    SetShaderParam(0x22f, pTarget ? (void*)((char*)pTarget + 0x18) : 0, 0);
}

// @ 0x00fb1b80
void cTerrainSphereQuad::ApplyFaceAxes()
{
    int idx = mFace;
    const unsigned char* p = g_faceAxisOrderNeg[idx >> 1];
    float one = kOne;
    float s = (idx & 1) ? kNegOne : one;
    mAxisX = p[0];
    mAxisY = p[1];
    mAxisZ = p[2];
    float f[3] = { s, one, s };
    mScaleX = f[p[0]];
    mScaleY = f[p[1]];
    mScaleZ = f[p[2]];
    mUVOffX = mOriginX;
    mUVOffY = mOriginY;
    mUVScale = mFaceScale;
}

} // namespace SP
