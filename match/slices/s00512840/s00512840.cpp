// slice s00512840: decal projection onto a mesh (/Od module).
// Flood-fills the mesh triangles reachable from the start triangle through
// seamless edges, projects each triangle onto the decal plane (uv = offset +
// (dot(uAxis,p), dot(vAxis,p))), keeps the triangles that overlap the unit uv
// square, appends their three vertices to the vertex vector and finally
// splits the new vertex range into batches of at most 36000 vertices.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// rw::math::Vector2 (math-library type returned by operator+)
struct RwVector2 {
    float x, y;
    RwVector2() {}
    RwVector2(float ax, float ay) : x(ax), y(ay) {}
};
RwVector2 operator+(const RwVector2& a, const RwVector2& b);  // 0x004FE7F0

struct Vector2 {
    float x, y;
    Vector2& operator=(const RwVector2& o) {
        x = o.x;
        y = o.y;
        return *this;
    }
    float& operator[](int i) { return (&x)[i]; }
};

struct Vector3 {
    float x, y, z;
    float Dot(const Vector3& o) const { return x * o.x + y * o.y + z * o.z; }
};
inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

float FastAcos(float x);                              // 0x00513930
bool IsEdgeInside(const Vector2& a, const Vector2& b);  // 0x00513BA0

extern float gDecalAngleBias;   // 0x015DD788
extern float gDecalAngleScale;  // 0x015DD784

// edge -> next / previous edge of the same triangle
static const signed char kNextEdge[3] = {1, 1, -2};   // 0x013F18D0
static const signed char kPrevEdge[3] = {2, -1, -1};  // 0x013F18D8

inline void GetTriangleEdges(uint32_t e, uint32_t& next, uint32_t& prev) {
    uint32_t edge = e;
    uint32_t m = edge - (edge / 3) * 3;
    next = kNextEdge[m] + edge;
    prev = kPrevEdge[m] + edge;
}

// pending flood-fill entry: the edge we arrived through and, if the edge is
// seamless, the indices of the two shared vertices already emitted
struct FillEntry {
    uint32_t edge;
    int a;
    int b;
    FillEntry() {}
    FillEntry(int e, int va, int vb) : edge(e), a(va), b(vb) {}
};

template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];

    bool empty() const;                     // out of line
    void push_back();                       // out of line
    void push_back(const T& v);             // out of line
    void resize(uint32_t n);                // out of line
    void resize(uint32_t n, const T& v);    // out of line
    T* erase(T* first, T* last);            // out of line
    T& back() { return *(mpEnd - 1); }
    void pop_back() { --mpEnd; }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
};

struct Mesh {
    uint32_t pad0[2];
    SpVector<Vector3> mPositions;      // +0x08
    SpVector<Vector3> mNormals;        // +0x1c
    SpVector<Vector2> mUVs;            // +0x30
    uint32_t pad44[5];
    SpVector<int> mPositionIndices;    // +0x58
    SpVector<int> mNormalIndices;      // +0x6c
    SpVector<int> mUVIndices;          // +0x80
    SpVector<uint32_t> mOpposite;      // +0x94
};

struct HalfEdge {
    uint32_t edge;
    bool seamless;
};

struct MeshAccessor {
    const Vector3* mPositions;      // -0x20
    const Vector3* mNormals;        // -0x1c
    const Vector2* mUVs;            // -0x18
    const int* mPositionIndices;    // -0x14
    const int* mNormalIndices;      // -0x10
    const int* mUVIndices;          // -0x0c
    const uint32_t* mOpposite;      // -0x08

    MeshAccessor(const Mesh& mesh);    // 0x005139F0
    const Vector3& Normal(uint32_t e) const { return mNormals[mNormalIndices[e]]; }
    const Vector3& Position(uint32_t e) const { return mPositions[mPositionIndices[e]]; }
    const Vector2& UV(uint32_t e) const { return mUVs[mUVIndices[e]]; }
    HalfEdge Opposite(uint32_t e) const;  // 0x00513A90
};

struct DecalParams {
    int mStartTriangle;     // +0x00
    Vector3 mDir;           // +0x04
    Vector3 mUAxis;         // +0x10
    Vector3 mVAxis;         // +0x1c
    RwVector2 mOffset;      // +0x28
    int mBatchData[3];      // +0x30
    int mVertexData[2];     // +0x3c
    uint8_t mFlags[4];      // +0x44
};

struct DecalVertex {  // 0x1c
    Vector2 mUV;        // +0x00
    int mData[2];       // +0x08
    Vector2 mDecalUV;   // +0x10
    float mFade;        // +0x18
};

inline void CopyVertex(DecalVertex& d, const DecalVertex& s) { d = s; }
struct DecalBatch {  // 0x18
    int mStart;          // +0x00
    int mCount;          // +0x04
    uint8_t mFlags[4];   // +0x08
    int mData[3];        // +0x0c
};

SpVector<uint8_t> sVisitedTriangles;  // 0x015DD75C
SpVector<FillEntry> sFillStack;       // 0x015DD770

struct cDecalBuilder {
    SpVector<DecalVertex> mVertices;  // +0x00
    SpVector<DecalBatch> mBatches;    // +0x14

    void Project(const Mesh& mesh, const DecalParams& params);
};

// @ 0x00512840
void cDecalBuilder::Project(const Mesh& mesh, const DecalParams& params)
{
    bool first;
    DecalVertex* verts;
    int i;
    DecalBatch* batch;
    uint32_t numTris;
    int e;
    uint32_t next, prev;
    FillEntry entry;
    int base, i1, i2;
    DecalVertex* dst;
    Vector3 pos;
    Vector2 uv0, uv1, uv2;
    float fade0, fade1, fade2;
    float d0, d1, d2;
    uint32_t remaining;
    uint32_t maxVerts;

    mBatches.push_back();
    batch = &mBatches.back();
    batch->mStart = (int)(mVertices.mpEnd - mVertices.mpBegin);
    batch->mCount = 0;
    batch->mFlags[0] = params.mFlags[0];
    batch->mFlags[1] = params.mFlags[1];
    batch->mFlags[2] = params.mFlags[2];
    batch->mFlags[3] = params.mFlags[3];
    for (i = 0; i < 3; i++)
        batch->mData[i] = params.mBatchData[i];

    MeshAccessor acc(mesh);
    numTris = (uint32_t)mesh.mPositionIndices.size() / 3;
    sVisitedTriangles.erase(sVisitedTriangles.mpBegin, sVisitedTriangles.mpEnd);
    sVisitedTriangles.resize(numTris, 0);
    sFillStack.erase(sFillStack.mpBegin, sFillStack.mpEnd);
    sFillStack.push_back(FillEntry(params.mStartTriangle * 3, -1, -1));
    sVisitedTriangles[params.mStartTriangle] = 1;

    first = true;
    verts = mVertices.mpBegin;
    while (!sFillStack.empty()) {
        entry = sFillStack.back();
        sFillStack.pop_back();
        e = entry.edge;
        GetTriangleEdges(e, next, prev);

        if (entry.a != -1) {
            d0 = Dot(params.mDir, acc.Normal(e));
            fade0 = (gDecalAngleBias - FastAcos(d0)) * gDecalAngleScale;
            pos = acc.Position(e);
            uv0 = params.mOffset + RwVector2(params.mUAxis.Dot(pos), params.mVAxis.Dot(pos));
            uv1 = verts[entry.a].mDecalUV;
            fade1 = verts[entry.a].mFade;
            uv2 = verts[entry.b].mDecalUV;
            fade2 = verts[entry.b].mFade;
        } else {
            d0 = Dot(params.mDir, acc.Normal(e));
            d1 = Dot(params.mDir, acc.Normal(next));
            d2 = Dot(params.mDir, acc.Normal(prev));
            fade0 = (gDecalAngleBias - FastAcos(d0)) * gDecalAngleScale;
            fade1 = (gDecalAngleBias - FastAcos(d1)) * gDecalAngleScale;
            fade2 = (gDecalAngleBias - FastAcos(d2)) * gDecalAngleScale;
            pos = acc.Position(e);
            uv0 = params.mOffset + RwVector2(params.mUAxis.Dot(pos), params.mVAxis.Dot(pos));
            pos = acc.Position(next);
            uv1 = params.mOffset + RwVector2(params.mUAxis.Dot(pos), params.mVAxis.Dot(pos));
            pos = acc.Position(prev);
            uv2 = params.mOffset + RwVector2(params.mUAxis.Dot(pos), params.mVAxis.Dot(pos));
        }

        // reject triangles entirely outside the unit uv square
        if ((uv0[0] <= 0.0f && uv1[0] <= 0.0f && uv2[0] <= 0.0f) ||
            (uv0[0] >= 1.0f && uv1[0] >= 1.0f && uv2[0] >= 1.0f) ||
            (uv0[1] <= 0.0f && uv1[1] <= 0.0f && uv2[1] <= 0.0f) ||
            (uv0[1] >= 1.0f && uv1[1] >= 1.0f && uv2[1] >= 1.0f))
            continue;
        // (the original tests the (uv0, uv1) edge twice)
        if (!IsEdgeInside(uv0, uv1) || !IsEdgeInside(uv0, uv1) || !IsEdgeInside(uv2, uv0))
            continue;
        {
            base = (int)(mVertices.mpEnd - mVertices.mpBegin);
            mVertices.resize(base + 3);
            verts = mVertices.mpBegin;
            dst = &verts[base];
            dst[0].mUV = acc.UV(e);
            dst[0].mData[0] = params.mVertexData[0];
            dst[0].mData[1] = params.mVertexData[1];
            dst[0].mDecalUV = uv0;
            dst[0].mFade = fade0;
            if (entry.a != -1) {
                i1 = entry.a;
                i2 = entry.b;
                CopyVertex(dst[1], verts[entry.a]);
                CopyVertex(dst[2], verts[entry.b]);
            } else {
                i1 = base + 1;
                i2 = base + 2;
                dst[1].mUV = acc.UV(next);
                dst[1].mData[0] = params.mVertexData[0];
                dst[1].mData[1] = params.mVertexData[1];
                dst[1].mDecalUV = uv1;
                dst[1].mFade = fade1;
                dst[2].mUV = acc.UV(prev);
                dst[2].mData[0] = params.mVertexData[0];
                dst[2].mData[1] = params.mVertexData[1];
                dst[2].mDecalUV = uv2;
                dst[2].mFade = fade2;
            }

            // spread across edges where the decal still faces the surface
            if (fade0 > 0.0f || fade1 > 0.0f) {
                HalfEdge h = acc.Opposite(e);
                uint32_t tri = h.edge / 3;
                if (!sVisitedTriangles[tri]) {
                    sVisitedTriangles[tri] = 1;
                    sFillStack.push_back();
                    if (h.seamless)
                        sFillStack.back() = FillEntry(h.edge, i1, base);
                    else
                        sFillStack.back() = FillEntry(h.edge, -1, -1);
                }
            }
            if (fade2 > 0.0f || fade0 > 0.0f) {
                HalfEdge h = acc.Opposite(prev);
                uint32_t tri = h.edge / 3;
                if (!sVisitedTriangles[tri]) {
                    sVisitedTriangles[tri] = 1;
                    sFillStack.push_back();
                    if (h.seamless)
                        sFillStack.back() = FillEntry(h.edge, base, i2);
                    else
                        sFillStack.back() = FillEntry(h.edge, -1, -1);
                }
            }
            if (first && (fade1 > 0.0f || fade2 > 0.0f)) {
                HalfEdge h = acc.Opposite(next);
                uint32_t tri = h.edge / 3;
                if (!sVisitedTriangles[tri]) {
                    sVisitedTriangles[tri] = 1;
                    sFillStack.push_back();
                    if (h.seamless)
                        sFillStack.back() = FillEntry(h.edge, i2, i1);
                    else
                        sFillStack.back() = FillEntry(h.edge, -1, -1);
                }
            }
            first = false;
        }
    }

    // split the new vertices into batches of at most 36000
    remaining = mVertices.size() - mBatches.back().mStart;
    maxVerts = 36000;
    while (remaining > 36000) {
        mBatches.back().mCount = 36000;
        mBatches.push_back(mBatches.back());
        mBatches.back().mStart += 36000;
        remaining -= 36000;
    }
    if (remaining == 0)
        mBatches.pop_back();
    else
        mBatches.back().mCount = remaining;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct E {
    void resize(unsigned int, unsigned char&); // 0x00473810
    void erase(unsigned char*, unsigned char*); // 0x0050f740
};
struct UFillEntry {
    void erase(int*, int*); // 0x0050f740
};
}
