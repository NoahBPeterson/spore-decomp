// Slice s00fac5c0 -- strand ("ribbon") mesh builder that feeds six cube-face quadtrees.
// FUN_00fac5c0: for every strand of points it builds one quad per segment (tangent frame from
// neighbouring points, miter offset, running texture length) and hands the quad to the
// per-face builder (FUN_00fab2b0), then flushes every face tree.
#include "types.h"
#include <math.h>

extern void FreeArr(void* p);                  // 0x00f47380, operator delete[] (cdecl)

struct Point {                                  // 0x24 bytes
    float x, y, z;                              // +0x0
    float scale;                                // +0xc
    float pad[5];
};

struct Strand {
    uint32_t pad0;
    Point* mpBegin;                             // +0x4
    Point* mpEnd;                               // +0x8
};

// One 0x110-byte element of a face builder's vector (owns a heap block unless it points at its
// inline buffer at +0x10).
struct BuildElem {
    void* mpData;                               // +0x0
    uint32_t pad[3];
    void* mpInline;                             // +0x10
    uint32_t rest[(0x110 - 0x14) / 4];
};

// Per-face accumulator (a 0x14-byte vector of BuildElem); filled by Builder::AddQuad.
struct FaceBuilder {
    BuildElem* mpBegin;
    BuildElem* mpEnd;
    BuildElem* mpCapacity;
    uint32_t mAlloc[2];

    void Init() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    void Destroy()
    {
        BuildElem* last = mpEnd;
        for (BuildElem* p = mpBegin; p < last; ++p) {
            void* d = p->mpData;
            if (d != 0 && d != p->mpInline) FreeArr(d);
        }
        BuildElem* b = mpBegin;
        if (b != 0 && ((int*)b)[-1] != 0) FreeArr(b);
    }
    // 0x00fab2b0: eax = pos[4][3], stack = uv[4][2], alpha[4], info{len, segLen, strand}.
    // (The original passes pos in EAX; here it is the first stack argument.)
    void AddQuad(const float* pos, const float* uv, const float* alpha, const float* info);
};

struct FaceTree {
    char pad[8];
    void Clear();                               // 0x00fb7720
    void Flush(FaceBuilder* b);                 // 0x00fb78f0 (ret 4)
};

struct StrandMesh {
    char pad0[0x118];
    FaceTree* mFaces[6];                        // +0x118
    char pad1[0x2b8 - 0x130];
    Strand** mpStrands;                         // +0x2b8
    Strand** mpStrandsEnd;                      // +0x2bc

    void Build();
    int StrandCount() { return mpStrandsEnd - mpStrands; }
};

static const float kEps = 1e-8f;

// @ 0x00fac5c0
void StrandMesh::Build()
{
    for (int f = 0; f < 6; ++f) {
        if (mFaces[f] != 0) mFaces[f]->Clear();
    }
    FaceBuilder builders[6];
    { FaceBuilder* q = builders; int c = 5; do { q->Init(); ++q; } while (--c >= 0); }

    for (unsigned s = 0; s < (unsigned)StrandCount(); ++s) {
        if (mpStrands[s] == 0) continue;
        int n = (mpStrands[s]->mpEnd - mpStrands[s]->mpBegin);
        float len = 0.0f;
        float prevPos[3], prevOff[3];
        for (int i = 0; i < n; ++i) {
            float scale = mpStrands[s]->mpBegin[i].scale;
            const Point* cur = &mpStrands[s]->mpBegin[i];
            const Point* prv = cur;
            if (i != 0) prv = &mpStrands[s]->mpBegin[i - 1];
            const Point* nxt = cur;
            if (i != n - 1) nxt = &mpStrands[s]->mpBegin[i + 1];

            // normal before the point: prv x cur
            float a0 = prv->y * cur->z - prv->z * cur->y;
            float a2 = prv->x * cur->y - prv->y * cur->x;
            float a1 = prv->z * cur->x - prv->x * cur->z;
            float ia = 1.0f / sqrtf((a1 * a1 + (a2 * a2 + a0 * a0)) + kEps);
            float na0 = a0 * ia, na1 = a1 * ia, na2 = a2 * ia;
            // normal after the point: cur x nxt
            float b0 = nxt->z * cur->y - nxt->y * cur->z;
            float b1 = nxt->x * cur->z - nxt->z * cur->x;
            float b2 = nxt->y * cur->x - nxt->x * cur->y;
            float ib = 1.0f / sqrtf((b2 * b2 + (b1 * b1 + b0 * b0)) + kEps);

            float dot;
            if (i == 0 || i == n - 1) {
                dot = -1.0f;
            } else {
                float p0 = prv->x - cur->x, p1 = prv->y - cur->y, p2 = prv->z - cur->z;
                float q0 = nxt->x - cur->x, q1 = nxt->y - cur->y, q2 = nxt->z - cur->z;
                dot = (p0 * q0 + (p1 * q1 + p2 * q2)) /
                      (sqrtf(p0 * p0 + (p1 * p1 + p2 * p2)) * sqrtf((q2 * q2 + q1 * q1) + q0 * q0));
                if (dot <= -1.0f) dot = -1.0f;
                if (0.999f <= dot) dot = 0.999f;
            }

            // miter direction
            float m0 = ib * b0 + na0;
            float m1 = b2 * ib + na2;
            float m2 = b1 * ib + na1;
            float ip = 1.0f / sqrtf(cur->x * cur->x + (cur->y * cur->y + cur->z * cur->z));
            float px = (ip * cur->x) * 500.0f;
            float py = (ip * cur->y) * 500.0f;
            float pz = (ip * cur->z) * 500.0f;
            float k = sqrtf(2.0f / (1.0f - dot));
            float im = 1.0f / sqrtf(m2 * m2 + (m1 * m1 + m0 * m0));
            float ox = (((im * m0) * k) * 6.0f) * scale;
            float oy = (((m2 * im) * k) * 6.0f) * scale;
            float oz = (((m1 * im) * k) * 6.0f) * scale;

            if (i > 0) {
                float pos[12], uv[8], alpha[4], info[3];
                pos[0] = prevPos[0] - prevOff[0];
                pos[1] = prevPos[1] - prevOff[1];
                pos[2] = prevPos[2] - prevOff[2];
                pos[3] = prevOff[0] + prevPos[0];
                pos[4] = prevPos[1] + prevOff[1];
                pos[5] = prevPos[2] + prevOff[2];
                pos[6] = ox + px;
                pos[7] = oy + py;
                pos[8] = oz + pz;
                pos[9] = px - ox;
                pos[10] = py - oy;
                pos[11] = pz - oz;
                float dx = px - prevPos[0], dy = py - prevPos[1], dz = pz - prevPos[2];
                float newLen = sqrtf(dz * dz + dy * dy + dx * dx) + len;
                uv[0] = -1.0f; uv[1] = len;
                uv[2] = 1.0f;  uv[3] = len;
                uv[4] = 1.0f;  uv[5] = newLen;
                uv[6] = -1.0f; uv[7] = newLen;
                alpha[0] = alpha[1] = (i == 1) ? 0.0f : 1.0f;
                alpha[2] = alpha[3] = (i == n - 1) ? 0.0f : 1.0f;
                len = newLen;
                info[0] = len;
                info[1] = sqrtf((dz * dz + dy * dy) + dx * dx);
                ((uint32_t*)info)[2] = s;
                builders[0].AddQuad(pos, uv, alpha, info);
            }
            prevPos[0] = px; prevPos[1] = py; prevPos[2] = pz;
            prevOff[0] = ox; prevOff[1] = oy; prevOff[2] = oz;
        }
    }

    for (int f = 0; f < 6; ++f) {
        if (mFaces[f] != 0) mFaces[f]->Flush(&builders[f]);
    }
    for (int k = 5; k >= 0; --k) builders[k].Destroy();
}
