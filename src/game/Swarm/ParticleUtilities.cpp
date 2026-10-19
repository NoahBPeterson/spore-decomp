// src/game/Swarm/ParticleUtilities.cpp -- migrated from slice(s) s00a7b370 by tools/migrate/rewrite.py
// Object file: Swarm/ParticleUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>

// ---- items of slice s00a7b370 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
struct FloatVec {          // eastl::vector<float> (begin, end, capacity)
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    void PushSlow(float* pEnd, const float* v);   // 0x00455660 (thiscall)
    void push_back(const float& v) {
        float* p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p) *p = v;
        } else {
            PushSlow(p, &v);
        }
    }
};
struct Vec3Vec { Vec3* mpBegin; Vec3* mpEnd; Vec3* mpCapacity; };
struct Vertex {            // 0x1c bytes: position, direction, parameter
    Vec3 pos;
    Vec3 dir;
    float param;
};
struct VertexVec {
    Vertex* mpBegin;
    Vertex* mpEnd;
    Vertex* mpCapacity;
    void PushSlow(Vertex* pEnd, const Vertex* v);   // 0x00a7a9d0
    Vertex* erase(Vertex* first, Vertex* last);    // 0x00d73090 (thiscall, ret 8)
};
extern const Vec3 kDefaultDir;                      // 0x016770dc
template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template<class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
struct PathBuilder {
    char       pad00[0x38];
    Vec3Vec    mPoints;       // +0x38
    char       pad44[0x4c - 0x44];
    FloatVec   mWidths;       // +0x4c
    char       pad58[0x60 - 0x58];
    Vec3Vec    mTangents;     // +0x60
    char       pad6c[0x74 - 0x6c];
    FloatVec   mParams;       // +0x74
    char       pad80[0x88 - 0x80];
    bool*      mpDone;        // +0x88
    char       pad8c[0x90 - 0x8c];
    VertexVec* mpOut;         // +0x90
    void Build(bool skip);    // 0x00a7b370
};
static inline float SegLen(const Vec3& a, const Vec3& b)
{
    float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}
// ---- items of slice s00a7b370 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern const Vec3 kDefaultDir;                      // 0x016770dc

// @ 0x00a7b370
void PathBuilder::Build(bool skip)
{
    if (skip) return;
    int n = (int)(mPoints.mpEnd - mPoints.mpBegin);
    int nTan = (int)(mTangents.mpEnd - mTangents.mpBegin);
    int nWidth = (int)(mWidths.mpEnd - mWidths.mpBegin);
    int nParam = (int)(mParams.mpEnd - mParams.mpBegin);
    bool normalize = false;

    if (nParam == 0) {
        if (nWidth == 1) {
            float total = 0.0f;
            for (int i = 1; i < n; ++i)
                total += SegLen(mPoints.mpBegin[i], mPoints.mpBegin[i - 1]);
            float v = total / mWidths.mpBegin[0];
            mParams.push_back(v);
            normalize = true;
        } else {
            float zero = 0.0f;
            mParams.push_back(zero);
            float acc = 0.0f;
            for (int i = 1; i < n; ++i) {
                Vec3 d;
                d.x = mPoints.mpBegin[i].x - mPoints.mpBegin[i - 1].x;
                d.y = mPoints.mpBegin[i].y - mPoints.mpBegin[i - 1].y;
                d.z = mPoints.mpBegin[i].z - mPoints.mpBegin[i - 1].z;
                float w = (mWidths.mpBegin[i - 1] + mWidths.mpBegin[i]) * 0.5f;
                if (w > 0.0f)
                    acc = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z) / w + acc;
                mParams.push_back(acc);
            }
        }
    } else if (nParam == 1) {
        normalize = true;
    }

    if (normalize && n > 1) {
        float last = mParams.mpEnd[-1];
        float total = 0.0f;
        for (int i = 1; i < n; ++i)
            total += SegLen(mPoints.mpBegin[i], mPoints.mpBegin[i - 1]);
        mParams.mpBegin[0] = 0.0f;
        float acc = 0.0f;
        float inv = 1.0f / total;
        for (int i = 1; i < n; ++i) {
            acc += SegLen(mPoints.mpBegin[i], mPoints.mpBegin[i - 1]);
            float v = inv * acc * last;
            mParams.push_back(v);
        }
    }

    if (nWidth == 0 && nTan == 0) {
        float last = mParams.mpEnd[-1];
        float total = 0.0f;
        for (int i = 1; i < n; ++i)
            total += SegLen(mPoints.mpBegin[i], mPoints.mpBegin[i - 1]);
        float w;
        if (last > 0.0f) w = total / last;
        else w = 0.0f;
        mWidths.push_back(w);
        nWidth = 1;
    }

    mpOut->erase(mpOut->mpBegin, mpOut->mpEnd);
    for (int i = 0; i < n; ++i) {
        Vertex v;
        v.pos = mPoints.mpBegin[i];
        v.param = mParams.mpBegin[i];
        if (nWidth > 0) {
            float w = (nWidth > 1) ? mWidths.mpBegin[i] : mWidths.mpBegin[0];
            int ia = Max(i - 1, 0);
            int ib = Min(i + 1, n - 1);
            Vec3 d;
            d.x = mPoints.mpBegin[ib].x - mPoints.mpBegin[ia].x;
            d.y = mPoints.mpBegin[ib].y - mPoints.mpBegin[ia].y;
            d.z = mPoints.mpBegin[ib].z - mPoints.mpBegin[ia].z;
            float len = sqrtf(d.z * d.z + d.y * d.y + d.x * d.x);
            if (len > 1e-6f) {
                float s = w / len;
                v.dir.x = d.x * s;
                v.dir.y = d.y * s;
                v.dir.z = d.z * s;
            } else {
                v.dir = kDefaultDir;
            }
        } else if (nTan > 0) {
            const Vec3& t = (nTan > 1) ? mTangents.mpBegin[i] : mTangents.mpBegin[0];
            v.dir = t;
        }
        VertexVec* out = mpOut;
        Vertex* p = out->mpEnd;
        if (p < out->mpCapacity) {
            out->mpEnd = p + 1;
            if (p) *p = v;
        } else {
            out->PushSlow(p, &v);
        }
    }
    *mpDone = true;
}
