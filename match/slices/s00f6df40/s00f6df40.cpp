// slice s00f6df40: 0x00f6e120 splits ribbon-brush polygons over the six faces of a cube map.
// Each polygon is clipped against the four side planes of every face, projected onto that face
// (u,v in [0,1] -> texels of the target), its bounds are accumulated, and the projected polygon is
// appended to the face's eastl::vector<SP::cRibbonBrushPoly, sp_vector_allocator>.  Faces with polygons
// are then rendered by 0x00f6c800.
// Names: BrushCubeSplitter / SplitPolysToCubeFaces are Claude-coined; SP::cRibbonBrushPoly,
// SP::cBrushVertex and the DoInsertValue instance are real (dev PDB).
// No EH frame although the face vectors have destructors: built without /EHsc.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int size_t;
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
extern "C" void* __cdecl memset(void*, int, size_t);
#pragma intrinsic(memcpy, memset)
void operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct cSPVector2 {
    float x, y;
    cSPVector2() {}
    cSPVector2(const cSPVector2& o) : x(o.x), y(o.y) {}
};

namespace SP {
struct cBrushVertex {   // 0x1c
    cSPVector3 mPosition;   // 0x00
    cSPVector2 mUV;         // 0x0c
    float mIntensity;       // 0x14
    float mSize;            // 0x18
};
struct cRibbonBrushPoly {   // 0x1c4
    int mNumVertices;
    cBrushVertex mVertices[16];
};
}
using namespace SP;

struct AABox {   // min/max box, empty while min.x > max.x
    cSPVector3 mMin;
    cSPVector3 mMax;
    void Extend(const cSPVector3& p) {
        if (mMin.x > mMax.x) {
            mMin = p;
            mMax = p;
        } else {
            if (mMin.x > p.x) mMin.x = p.x;
            else if (p.x > mMax.x) mMax.x = p.x;
            if (mMin.y > p.y) mMin.y = p.y;
            else if (p.y > mMax.y) mMax.y = p.y;
            if (mMin.z > p.z) mMin.z = p.z;
            else if (p.z > mMax.z) mMax.z = p.z;
        }
    }
};

struct Rect {
    float x1, y1, x2, y2;
    Rect(float a, float b, float c, float d) : x1(a), y1(b), x2(c), y2(d) {}
};

namespace eastl {
struct sp_vector_allocator {
    int mFlags;
    int mUnused;
    sp_vector_allocator() {}
    void deallocate(void* p) {
        if (((int*)p)[-1] != 0)
            ::operator delete[](p);
    }
};

template <class T, class Allocator> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase() {
        if (mpBegin)
            mAllocator.deallocate(mpBegin);
    }
};

template <class T, class Allocator> struct vector : VectorBase<T, Allocator> {
    void DoInsertValue(T* position, const T& value);   // 0x00f4c180 (cRibbonBrushPoly instance)
    void push_back(const T& value) {
        if (this->mpEnd < this->mpCapacity)
            ::new (this->mpEnd++) T(value);
        else
            DoInsertValue(this->mpEnd, value);
    }
    bool empty() const { return this->mpBegin == this->mpEnd; }
};
}

typedef eastl::vector<cRibbonBrushPoly, eastl::sp_vector_allocator> PolyVector;

struct BrushTarget {
    char pad0[0x60];
    unsigned int mWidth;    // 0x60
    unsigned int mHeight;   // 0x64
    unsigned int mDepth;    // 0x68
};

void ClipPolyToPlane(cBrushVertex* verts, int* numVerts, const cSPVector3* plane);   // 0x00fc2c70

extern const cSPVector3 gCubeFaceClipPlanes[6][4];   // 0x016d6fa8
extern const uint8_t gCubeFaceAxes[3][4];            // 0x0148f608

struct BrushCubeSplitter {
    void RenderFace(PolyVector* polys, int face, BrushTarget* target, int arg, const Rect* rect,
                    bool flag, int extra);   // 0x00f6c800
    void SplitPolysToCubeFaces(int arg, BrushTarget* target, int numPolys,
                               const cRibbonBrushPoly* polys, int extra);
};

void BrushCubeSplitter::SplitPolysToCubeFaces(int arg, BrushTarget* target, int numPolys,
                                              const cRibbonBrushPoly* polys, int extra) {
    target->mWidth = 0x200;
    target->mHeight = 0x200;
    target->mDepth = 0x200;

    PolyVector faces[6];
    AABox bounds[6];
    memset(bounds, 0, sizeof(bounds));

    cRibbonBrushPoly out;
    cBrushVertex verts[16];
    for (int p = 0; p < numPolys; p++, polys++) {
        for (int face = 0; face < 6; face++) {
            int numVerts = polys->mNumVertices;
            for (int k = 0; k < numVerts; k++)
                verts[k] = polys->mVertices[k];
            int plane;
            for (plane = 0; plane < 4; plane++) {
                if (numVerts == 0)
                    break;
                ClipPolyToPlane(verts, &numVerts, &gCubeFaceClipPlanes[face][plane]);
            }
            if (numVerts == 0)
                continue;

            out.mNumVertices = numVerts;
            const uint8_t* axes = gCubeFaceAxes[face >> 1];
            float sign = (face & 1) ? -1.0f : 1.0f;
            float signs[3];
            signs[0] = sign;
            signs[1] = 1.0f;
            signs[2] = sign;
            int i0 = axes[0], i1 = axes[1], i2 = axes[2];
            float s0 = signs[i0];
            float s1 = signs[i1];
            float s2 = signs[i2];
            for (int v = 0; v < numVerts; v++) {
                const cBrushVertex& src = verts[v];
                float tmp[3];
                tmp[i0] = src.mPosition.x * s0;
                tmp[i1] = s1 * src.mPosition.y;
                tmp[i2] = src.mPosition.z * s2;
                float inv = 1.0f / tmp[2];
                float u = (tmp[0] * inv + 1.0f) * 0.5f;
                float w = (tmp[1] * inv + 1.0f) * 0.5f;
                bounds[face].Extend(cSPVector3(u, w, 0.0f));
                cBrushVertex& dst = out.mVertices[v];
                dst.mPosition = cSPVector3((float)target->mWidth * u, (float)target->mHeight * w, 0.0f);
                dst.mUV = src.mUV;
                dst.mIntensity = src.mIntensity;
            }
            faces[face].push_back(out);
        }
    }

    for (int face = 0; face < 6; face++) {
        if (!faces[face].empty()) {
            const AABox& b = bounds[face];
            Rect r(b.mMin.x, b.mMin.y, b.mMax.x, b.mMax.y);
            RenderFace(&faces[face], face, target, arg, &r, true, extra);
        }
    }
}
