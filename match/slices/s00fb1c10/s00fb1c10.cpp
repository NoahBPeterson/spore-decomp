// Slice s00fb1c10: SP::cTerrainSphereQuad::SamplePosition (Claude-coined name); the function itself is
// marked with its address further down, next to the other four functions of this slice.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same module as the other cTerrainSphereQuad slices.
//
// Given a point (px, py) in the face's [0,1]^2 coordinates, finds the enclosing cell of the quad's
// (mChunkRes x mChunkRes) grid, computes the four corner positions (cube-map terrain height mapped
// onto the sphere through the face axis table at 0x01491094) and linearly interpolates them over the
// cell's two triangles (split along the diagonal fx + fy = 1).
#include "types.h"
#include <math.h>

struct cCubeMapCoord { float u, v; int face; };

namespace SP {

struct cTerrainMapU16 {                     // SP::cTerrainMap<unsigned short>
    float GetFloat(cCubeMapCoord* c);       // @ 0x00f8d620
};

class cTerrainMapSet { public:
    unsigned pad00[2];
    cTerrainMapU16* mHeightMap;   // +0x08
    unsigned pad0c[0x34 / 4 - 3];
    float mRadius;                              // +0x34
    float mMaxHeight;                           // +0x38
};

class cTerrainSphere { public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual cTerrainMapSet* GetMapSet();        // +0xc
    virtual void* GetInfo();                    // +0x10
};

// cube face -> axis permutation, 3 bytes per entry padded to 4, indexed by face >> 1
extern const unsigned char g_cubeAxes[][4];     // @ 0x01491094

inline const int& MinI(const int& a, const int& b) { return b < a ? b : a; }

// direction on the unit cube face (u, v in [0,1]) projected to the sphere, scaled by h
__forceinline void CubeToSphere(float* out, int face, float qu, float qv, float h)
{
    float a = qu * 2.0f - 1.0f;
    float b = qv * 2.0f - 1.0f;
    float inv = 1.0f / sqrtf(a * a + b * b + 1.0f);
    float s = inv;
    if (face & 1) s = -inv;
    const unsigned char* t = g_cubeAxes[face >> 1];
    float d[3];
    d[t[0]] = s * a;
    d[t[1]] = inv * b;
    d[t[2]] = s;
    out[0] = d[0] * h;
    out[1] = d[1] * h;
    out[2] = d[2] * h;
}

// a cell of the terrain quad tree whose cube-map coordinates are sampled for the span mask
struct cMaskCell {
    unsigned char pad00[0x54];
    float mRadius;                  // +0x54
    unsigned char pad58[0x94 - 0x58];
    float mU;                       // +0x94
    float mV;                       // +0x98
    int   mFace;                    // +0x9c
    unsigned char padA0[0x104 - 0xA0];
    float mA;                       // +0x104
    unsigned char pad108[0x114 - 0x108];
    float mB;                       // +0x114
};

// the job whose per-span byte mask the quad fills: cell pointer at +0, mask bytes at +7
struct cSpanJob {
    cMaskCell* mpCell;              // +0x00
    unsigned char pad04[3];
    unsigned char mMask[9];         // +0x07
};

class cTerrainSphereQuad { public:
    cTerrainSphere* mSphere;        // +0x00
    cTerrainSphereQuad* mpMorph;    // +0x04
    unsigned pad08[4];
    int   mChunkRes;                // +0x18
    int   mFace;                    // +0x1c
    float mOriginX;                 // +0x20
    float mOriginY;                 // +0x24
    unsigned pad28[2];
    float mFaceScale;               // +0x30
    unsigned pad34[3];

    void SamplePosition(float* out, float px, float py);            // 0x00fb1c10
    void QuadPos(float* out, int ix, int iy);                       // 0x00fb2290
    void CalcMorphedPoint(float* out, int ix, int iy);              // 0x00fb2400
    void BuildSpanMask(cSpanJob* job);                              // 0x00fb2550
};

// @ 0x00fb1c10
void cTerrainSphereQuad::SamplePosition(float* out, float px, float py)
{
    cTerrainMapSet* ms = mSphere->GetMapSet();
    mSphere->GetInfo();
    float base = ms->mRadius + 0.05f;
    float range = ms->mMaxHeight;
    cTerrainMapU16* map = ms->mHeightMap;

    float n = (float)mChunkRes;
    float inv = 1.0f / mFaceScale;
    px = ((px - mOriginX) * inv) * n;
    py = ((py - mOriginY) * inv) * n;
    int ix = MinI((int)px, mChunkRes - 1);
    int iy = MinI((int)py, mChunkRes - 1);
    float tx = px - (float)ix;
    float ty = py - (float)iy;

    cCubeMapCoord q;
    __declspec(align(16)) float p0[3];
    float p1[3], p2[3], p3[3];
    q.face = mFace;

    q.u = (mFaceScale * (float)ix) / (float)mChunkRes + mOriginX;
    q.v = (mFaceScale * (float)iy) / (float)mChunkRes + mOriginY;
    CubeToSphere(p0, q.face, q.u, q.v, map->GetFloat(&q) * range + base);

    q.u = ((float)(ix + 1) * mFaceScale) / (float)mChunkRes + mOriginX;
    CubeToSphere(p1, q.face, q.u, q.v, map->GetFloat(&q) * range + base);

    q.v = ((float)(iy + 1) * mFaceScale) / (float)mChunkRes + mOriginY;
    CubeToSphere(p2, q.face, q.u, q.v, map->GetFloat(&q) * range + base);

    q.u = (mFaceScale * (float)ix) / (float)mChunkRes + mOriginX;
    CubeToSphere(p3, q.face, q.u, q.v, map->GetFloat(&q) * range + base);

    if (tx + ty < 1.0f) {
        out[0] = ((p1[0] - p0[0]) * tx + p0[0]) + (p3[0] - p0[0]) * ty;
        out[1] = ((p1[1] - p0[1]) * tx + p0[1]) + (p3[1] - p0[1]) * ty;
        out[2] = ((p1[2] - p0[2]) * tx + p0[2]) + (p3[2] - p0[2]) * ty;
    } else {
        float rx = 1.0f - tx;
        float ry = 1.0f - ty;
        out[0] = ((p3[0] - p2[0]) * rx + p2[0]) + (p1[0] - p2[0]) * ry;
        out[1] = ((p3[1] - p2[1]) * rx + p2[1]) + (p1[1] - p2[1]) * ry;
        out[2] = ((p3[2] - p2[2]) * rx + p2[2]) + (p1[2] - p2[2]) * ry;
    }
}

// @ 0x00fb2290  one grid corner of the quad, projected onto the sphere at the terrain height
void cTerrainSphereQuad::QuadPos(float* out, int ix, int iy)
{
    cTerrainMapSet* ms = mSphere->GetMapSet();
    mSphere->GetInfo();
    float radius = ms->mRadius;
    float range = ms->mMaxHeight;
    cTerrainMapU16* map = ms->mHeightMap;

    float qv = (float)iy;
    float qu = (float)ix;
    cCubeMapCoord q;
    q.face = mFace;
    q.u = (qu * mFaceScale) / (float)mChunkRes + mOriginX;
    q.v = (qv * mFaceScale) / (float)mChunkRes + mOriginY;

    float h = (radius + 0.05f) + map->GetFloat(&q) * range;
    CubeToSphere(out, q.face, q.u, q.v, h);
}

// @ 0x00fb2400  the two morphed corners of a grid cell (odd/even split of the morph target)
void cTerrainSphereQuad::CalcMorphedPoint(float* out, int ix, int iy)
{
    if (mpMorph && !(ix % 2 == 0 && iy % 2 == 0)) {
        float inv = 1.0f / (float)mChunkRes;
        float px = mOriginX + mFaceScale * (inv * (float)ix);
        float py = mOriginY + mFaceScale * (inv * (float)iy);
        float q[3];
        float p[3];
        QuadPos(q, ix, iy);
        mpMorph->SamplePosition(p, px, py);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
        out[3] = q[0]; out[4] = q[1]; out[5] = q[2];
        return;
    }
    float q[3];
    QuadPos(q, ix, iy);
    out[0] = q[0]; out[1] = q[1]; out[2] = q[2];
    out[3] = q[0]; out[4] = q[1]; out[5] = q[2];
}

// @ 0x00fb2550  fill the 8 span-mask bytes (+7 .. +15) of the job from the cell's projected quad row
void cTerrainSphereQuad::BuildSpanMask(cSpanJob* job)
{
    cMaskCell* cell = job->mpCell;
    float s2 = mFaceScale * 2.0f;
    float ox2 = mOriginX * 2.0f - 1.0f;
    float oy2 = mOriginY * 2.0f - 1.0f;

    float px, py;
    if (cell->mFace == mFace) {
        px = cell->mU * 2.0f - 1.0f;
        py = cell->mV * 2.0f - 1.0f;
    } else {
        float d[3];
        CubeToSphere(d, cell->mFace, cell->mU, cell->mV, 1.0f);
        if (mFace == 0 || mFace == 1) {
            px = d[0] / d[2];
            py = d[1] / fabsf(d[2]);
        } else if (mFace == 4 || mFace == 5) {
            px = d[2] / d[1];
            py = d[0] / fabsf(d[1]);
        } else {
            px = d[1] / d[0];
            py = d[2] / fabsf(d[0]);
        }
    }

    float r = cell->mRadius / sqrtf(cell->mB * cell->mB + cell->mA * cell->mA) * cell->mB * 0.5f;
    float rr = r * r;
    float om = 1.0f - rr;
    float A = px * px * rr - (py * py + 1.0f) * om;
    float inv = 1.0f / (2.0f * A);
    float B = 2.0f * px * py;
    float Q = B * B - 4.0f * A * (py * rr - (px * px + 1.0f) * om);
    float L = 4.0f * (px * B - 2.0f * py * A);
    float C = px * px * 4.0f - 4.0f * A * (rr - (py + px * px) * om);
    float invS2 = 1.0f / s2;
    float step = s2 * 0.125f;

    int prevX = 0, prevY = 0;
    for (int i = 0; i <= 8; ++i) {
        float t = (float)i * step + oy2;
        float lin = t * B + 2.0f * px;
        float disc = t * t * Q + t * L + C;
        if (disc < 0.0f) {
            prevX = 8;
            prevY = 0;
            continue;
        }
        float s = sqrtf(disc);
        int x = (int)ceilf((((s - lin) * inv) - ox2) * invS2 * 8.0f);
        int y = (int)floorf((((-s - lin) * inv) - ox2) * invS2 * 8.0f);
        if (i > 0) {
            int mx = prevX < x ? x : prevX;
            int my = prevY < y ? y : prevY;
            if (mx < 0) mx = 0; else if (mx > 8) mx = 8;
            if (my < 0) my = 0; else if (my > 8) my = 8;
            job->mMask[i] = (unsigned char)(~((1u << mx) - 1u) & ((1u << my) - 1u));
        }
        prevX = x;
        prevY = y;
    }
}

// 0x30-byte record copied by the two helpers below (9 floats, a pointer-sized word, then 2 floats)
struct Rec30 {
    float f00, f04, f08, f0c, f10, f14, f18, f1c, f20;   // +0x00 .. +0x20
    void* p24;                                           // +0x24
    float f28, f2c;                                      // +0x28, +0x2c

    Rec30& operator=(const Rec30& o);                    // @ 0x00fb29f0
};

// @ 0x00fb29f0
Rec30& Rec30::operator=(const Rec30& o)
{
    f00 = o.f00; f04 = o.f04; f08 = o.f08; f0c = o.f0c; f10 = o.f10;
    f14 = o.f14; f18 = o.f18; f1c = o.f1c; f20 = o.f20;
    p24 = o.p24;
    f28 = o.f28; f2c = o.f2c;
    return *this;
}

// @ 0x00fb2a40  copy [first,last) into dst, 0x30 bytes at a time
void CopyRange30(Rec30* first, Rec30* last, Rec30* dst)
{
    while (first != last) {
        if (dst)
            *dst = *first;
        ++first;
        ++dst;
    }
}

}
