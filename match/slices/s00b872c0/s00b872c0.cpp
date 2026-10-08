// Slice s00b872c0 -- 0x00b872c0, 2276 bytes (__stdcall, ret 8).
//
// Builds a terrain-hugging ribbon for a polyline of planet-surface points and uploads it to the
// static vertex buffer (SP::cStaticBufferDraw).  `path` is a vector<Vec3> of points on / around
// the planet sphere (n >= 2 or the function does nothing), `color` the vertex colour (alpha forced
// to 0xff).  For every point P_i (prev Q = P_{i-1}, next R = P_{i+1}, clamped at the ends):
//   m1 = normalize(Q x P), m2 = normalize(P x R)            (eps 1e-8 inside the sqrt)
//   cos = clamp(dot(Q-P, R-P) / (|Q-P| |R-P|), -1, 0.999)    (-1 at the two ends)
//   S  = unit(P) * (terrainHeight(unit(P)) + 4.0)            (point lifted onto the terrain)
//   M  = normalize(m1 + m2) * sqrt(2 / (1 - cos))            (miter vector)
// and every segment emits a quad of four 36-byte vertices { pos, miter, color, u, v } at
// S_prev -/+ M_prev and S -/+ M, with v the accumulated length along the ribbon and u = 0/1
// across it.  The quads are collected in a local fixed_vector<Vertex,128> (resized to 4n-4) and
// finally copied into the static buffer in chunks (GetVertexBuffer / memcpy / Unlock).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast (x87 fsqrt/fdiv for 1/sqrt, SSE for the rest).
//
// @ 0x00b872c0

#include <string.h>
#include <math.h>
#include <xmmintrin.h>

typedef unsigned int uint32_t;

struct Vec3 { float x, y, z; };

struct RibbonVertex {           // 0x24 bytes
    Vec3 pos;
    Vec3 miter;
    uint32_t color;
    float u;
    float v;
};

struct PathVector {             // eastl::vector<Vec3>
    Vec3* mpBegin;
    Vec3* mpEnd;
};

namespace SP {

class cTerrainMapSet {
public:
    float GetHeightAt(const Vec3* unitDir);                          // 0x00f927c0
};

class cTerrainSource {          // object at PlanetModel()+0x24
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual cTerrainMapSet* GetTerrainMapSet();                      // +0x0c
    virtual int Slot4();                                             // +0x10 (result unused)
};

struct cPlanetModel {
    uint32_t pad[9];
    cTerrainSource* mpTerrain;                                       // +0x24
};
cPlanetModel* PlanetModel();                                         // 0x00b3d350

class cStaticBuffer {
public:
    int GetVertexBuffer(int count, RibbonVertex** ppOut, int* pOut2);   // 0x007a47c0
    void Unlock();                                                   // 0x007a4650
};

struct cStaticBufferDraw {
    cStaticBuffer* mpBuffer;
};
}

extern SP::cStaticBufferDraw* gStaticBufferDraw;                     // 0x015ddc84
void __cdecl EASTL_allocator_deallocate(void* p);                    // 0x00f47380

// eastl::fixed_vector<RibbonVertex, 128> (vector part)
struct VertexVector {
    RibbonVertex* mpBegin;
    RibbonVertex* mpEnd;
    RibbonVertex* mpCapacity;
    uint32_t mAllocatorPad;
    RibbonVertex* mpPool;
    void resize(unsigned n);                                         // 0x00b86910
};

__forceinline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

// @ 0x00b872c0
void __stdcall BuildPathRibbon(PathVector* path, unsigned color)
{
    if ((unsigned)(path->mpEnd - path->mpBegin) < 2)
        return;

    SP::cStaticBufferDraw* draw = gStaticBufferDraw;
    uint32_t col = color | 0xff000000;

    SP::cTerrainMapSet* mapSet = SP::PlanetModel()->mpTerrain->GetTerrainMapSet();
    SP::PlanetModel()->mpTerrain->Slot4();

    RibbonVertex storage[128];
    VertexVector verts;
    verts.mpBegin = storage;
    verts.mpEnd = storage;
    verts.mpCapacity = storage + 128;
    verts.mpPool = storage;
    verts.resize((unsigned)(path->mpEnd - path->mpBegin) * 4 - 4);

    RibbonVertex* out = verts.mpBegin;
    Vec3 prevM, prevS;
    float length = 0.0f;
    int n = (int)(path->mpEnd - path->mpBegin);

    for (int i = 0; i < n; i++) {
        const Vec3* P = path->mpBegin + i;
        const Vec3* Q = P;
        if (i != 0)
            Q = P - 1;
        const Vec3* R = P;
        if (i != n - 1)
            R = P + 1;

        // m1 = normalize(Q x P)
        float c1x = P->z * Q->y - P->y * Q->z;
        float c1y = P->x * Q->z - P->z * Q->x;
        float c1z = P->y * Q->x - P->x * Q->y;
        float r1 = 1.0f / sqrtf((c1x * c1x + c1z * c1z + c1y * c1y) + 1e-08f);
        Vec3 m1;
        m1.x = c1x * r1;
        m1.y = c1y * r1;
        m1.z = c1z * r1;

        // m2 = normalize(P x R)
        float c2x = P->y * R->z - P->z * R->y;
        float c2y = P->z * R->x - P->x * R->z;
        float c2z = P->x * R->y - P->y * R->x;
        float r2 = 1.0f / sqrtf((c2x * c2x + c2z * c2z + c2y * c2y) + 1e-08f);
        Vec3 m2;
        m2.x = c2x * r2;
        m2.y = c2y * r2;
        m2.z = c2z * r2;

        float cosv;
        if (i == 0 || i == n - 1) {
            cosv = -1.0f;
        } else {
            float d1x = R->x - P->x;
            float d1y = R->y - P->y;
            float d1z = R->z - P->z;
            float d0x = Q->x - P->x;
            float d0y = Q->y - P->y;
            float d0z = Q->z - P->z;
            float dot = (d0z * d1z + d0y * d1y) + d0x * d1x;
            float l1 = sqrtf((d1z * d1z + d1y * d1y) + d1x * d1x);
            float l0 = sqrtf((d0z * d0z + d0y * d0y) + d0x * d0x);
            cosv = Clamp(dot / (l1 * l0), -1.0f, 0.999f);
        }

        // lift the unit direction onto the terrain
        float px = P->x;
        float inv = 1.0f / sqrtf((P->y * P->y + P->z * P->z) + px * px);
        Vec3 dir;
        dir.x = px * inv;
        dir.y = inv * P->y;
        dir.z = P->z * inv;
        float h = mapSet->GetHeightAt(&dir) + 4.0f;
        Vec3 S;
        S.x = dir.x * h;
        S.y = dir.y * h;
        S.z = dir.z * h;

        float sx = m2.x + m1.x;
        float sy = m2.y + m1.y;
        float sz = m2.z + m1.z;
        float scale = sqrtf(2.0f / (1.0f - cosv));
        float rs = 1.0f / sqrtf((sx * sx + sz * sz) + sy * sy);
        Vec3 M;
        M.x = (rs * sx) * scale;
        M.y = (sy * rs) * scale;
        M.z = (sz * rs) * scale;

        if (i > 0) {
            out[0].pos.x = prevS.x - prevM.x;
            out[0].pos.y = prevS.y - prevM.y;
            out[0].pos.z = prevS.z - prevM.z;
            out[0].miter = prevM;
            out[0].color = col;
            out[0].u = 0.0f;
            out[0].v = length;

            out[1].pos.x = prevM.x + prevS.x;
            out[1].pos.y = prevM.y + prevS.y;
            out[1].pos.z = prevM.z + prevS.z;
            out[1].miter = prevM;
            out[1].color = col;
            out[1].u = 1.0f;
            out[1].v = length;

            length = sqrtf(((S.z - prevS.z) * (S.z - prevS.z) + (S.y - prevS.y) * (S.y - prevS.y)) +
                           (S.x - prevS.x) * (S.x - prevS.x)) + length;

            out[2].pos.x = S.x + M.x;
            out[2].pos.y = S.y + M.y;
            out[2].pos.z = S.z + M.z;
            out[2].miter = M;
            out[2].color = col;
            out[2].u = 1.0f;
            out[2].v = length;

            out[3].pos.x = S.x - M.x;
            out[3].pos.y = S.y - M.y;
            out[3].pos.z = S.z - M.z;
            out[3].miter = M;
            out[3].color = col;
            out[3].u = 0.0f;
            out[3].v = length;
            out += 4;
        }
        prevM = M;
        prevS = S;
    }

    // upload in chunks
    int total = (int)(verts.mpEnd - verts.mpBegin);
    int done = 0;
    while (done < total) {
        RibbonVertex* dst;
        int extra;
        int got = draw->mpBuffer->GetVertexBuffer(total - done, &dst, &extra);
        memcpy(dst, verts.mpBegin + done, got * sizeof(RibbonVertex));
        draw->mpBuffer->Unlock();
        total = (int)(verts.mpEnd - verts.mpBegin);
        done += got;
    }

    if (verts.mpBegin != 0 && verts.mpBegin != verts.mpPool)
        EASTL_allocator_deallocate(verts.mpBegin);
}
