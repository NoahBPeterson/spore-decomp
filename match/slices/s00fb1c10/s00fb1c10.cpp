// Slice s00fb1c10: SP::cTerrainSphereQuad::SamplePosition @ 0x00fb1c10 (Claude-coined name).
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

struct cTerrainMapSet {
    unsigned pad00[2];
    cTerrainMapU16* mHeightMap;   // +0x08
    unsigned pad0c[0x34 / 4 - 3];
    float mRadius;                              // +0x34
    float mMaxHeight;                           // +0x38
};

struct cTerrainSphere {
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

struct cTerrainSphereQuad {
    cTerrainSphere* mSphere;        // +0x00
    unsigned pad04[5];
    int   mChunkRes;                // +0x18
    int   mFace;                    // +0x1c
    float mOriginX;                 // +0x20
    float mOriginY;                 // +0x24
    unsigned pad28[2];
    float mFaceScale;               // +0x30

    void SamplePosition(float* out, float px, float py);       // 0x00fb1c10
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

}
