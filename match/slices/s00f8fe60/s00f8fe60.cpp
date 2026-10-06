// Slice s00f8fe60 -- SP::cTerrainMap<unsigned int>::BlendMapEdges (0x00f8fe60, 6759 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the local vector gets no EH frame).
//
// The map is a cube map: 6 faces of mFaceSize x mFaceSize packed directions (Direction4c,
// one byte per component, xyz biased to [-1,1], w in [0,1]). For every face, each border
// texel is replaced by (2*inner + across) / 3, where `inner` is the texel one step inside
// the face and `across` is the texel two steps outside it (WrapCubeFace maps it onto the
// neighbouring face). Results go to a scratch copy first, then only the border texels are
// copied back, so the reads all see the unblended map.
//
// The `Removing unreachable block` warnings in Ghidra are the x87 unsigned->float fix-ups
// (`fadd 2^32`) of `c >> 24`, which can never be negative.
#include "types.h"

extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);   // 0x011e0744 thunk
void EASTLFree(void* p);                                                         // 0x00f47380

struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
};
extern Vector4 kVector4One;   // 0x015b0f90 = {1,1,1,1}

namespace eastl {

struct allocator {};

template <class T, class Allocator = allocator> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector() { DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin)); }

    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T& operator[](uint32_t n) { return mpBegin[n]; }

    void resize(uint32_t n);                       // 0x004cd3c0 (folded with vector<void*>::resize)
    T* erase(T* first, T* last)
    {
        T* const position = (T*)memmove(first, last, (uint32_t)((char*)mpEnd - (char*)last)) + (mpEnd - last);
        mpEnd -= (last - first);
        (void)position;
        return first;
    }
    void DoFree(T* p, uint32_t) { if (p && *((uint32_t*)p - 1)) EASTLFree(p); }
};

} // namespace eastl

namespace SP {

void WrapCubeFace(int size, int* face, int* x, int* y, int* rot, int* flip);   // 0x00684ca0
uint32_t Direction4fToDirection4c(const Vector4& v);                            // 0x00f87c10

// Unpack a Direction4c: xyz from [0,255] to [-1,1], w to [0,1].
__forceinline void Direction4cToDirection4f(uint32_t c, Vector4& v)
{
    v.x = (float)(c & 0xff);
    v.y = (float)((c >> 8) & 0xff);
    v.z = (float)((c >> 16) & 0xff);
    v.w = (float)(c >> 24) * (1.0f / 255.0f);
    v.x = v.x * (1.0f / 255.0f) * 2.0f - kVector4One.x;
    v.y = v.y * (1.0f / 255.0f) * 2.0f - kVector4One.y;
    v.z = v.z * (1.0f / 255.0f) * 2.0f - kVector4One.z;
}

// (2*inner + across) / 3, re-packed.
__forceinline uint32_t BlendEdge(const Vector4& a, const Vector4& b)
{
    Vector4 r;
    r.x = (a.x * 2.0f + b.x) * (1.0f / 3.0f);
    r.y = (a.y * 2.0f + b.y) * (1.0f / 3.0f);
    r.z = (a.z * 2.0f + b.z) * (1.0f / 3.0f);
    r.w = (a.w * 2.0f + b.w) * (1.0f / 3.0f);
    return Direction4fToDirection4c(r);
}

class cTerrainMapBase {
public:
    virtual ~cTerrainMapBase();
    int mnRefCount;          // +0x04
    unsigned int mFaceSize;  // +0x08
    unsigned int mModCount;  // +0x0c
    struct allocator_128 : eastl::allocator {};
};

template <class T> class cTerrainMap : public cTerrainMapBase {
public:
    typedef eastl::vector<T, allocator_128> MapData;

    // Texel (x, y) of `face`; coordinates outside the face wrap onto its neighbours.
    // The range test assumes a power-of-two face size.
    __forceinline T GetCubeValue(int face, int x, int y)
    {
        int size = mFaceSize;
        if ((x | y) & ~(size - 1))
            WrapCubeFace(size, &face, &x, &y, 0, 0);
        return mMapData[(size * face + y) * size + x];
    }

    // Border texel `dst` of the scratch copy = blend of texel (ix, iy) and texel (ox, oy).
    __forceinline uint32_t BlendTexels(int face, int ix, int iy, int ox, int oy)
    {
        Vector4 inner, across;
        Direction4cToDirection4f(GetCubeValue(face, ix, iy), inner);
        Direction4cToDirection4f(GetCubeValue(face, ox, oy), across);
        return BlendEdge(inner, across);
    }

    void BlendMapEdges();

    MapData mMapData;        // +0x10
};

// @ 0x00f8fe60
template <> void cTerrainMap<unsigned int>::BlendMapEdges()
{
    const int size = mFaceSize;
    const int faceArea = size * size;
    MapData blended;
    blended.resize(faceArea * 6);
    const int lastRow = (size - 1) * size;

    int faceBase = 0;
    for (int face = 0; face < 6; ++face) {
        // left and right columns
        for (int y = 1; y < size - 1; ++y) {
            blended[faceBase + y * size] =
                BlendTexels(face, 1, y, -2, y);
            blended[faceBase + y * size + size - 1] =
                BlendTexels(face, size - 2, y, size + 1, y);
        }
        // top and bottom rows
        for (int x = 1; x < size - 1; ++x) {
            blended[faceBase + x] =
                BlendTexels(face, x, 1, x, -2);
            blended[faceBase + lastRow + x] =
                BlendTexels(face, x, size - 2, x, size + 1);
        }
        // corners (diagonal neighbours)
        blended[faceBase] =
            BlendTexels(face, 1, 1, -2, -2);
        blended[faceBase + size - 1] =
            BlendTexels(face, size - 2, 1, size + 1, -2);
        blended[faceBase + lastRow] =
            BlendTexels(face, 1, size - 2, -2, size + 1);
        blended[faceBase + faceArea - 1] =
            BlendTexels(face, size - 2, size - 2, size + 1, size + 1);
        faceBase += faceArea;
    }

    // Copy only the border texels back.
    faceBase = 0;
    for (int face = 0; face < 6; ++face) {
        for (int y = 0; y < size; ++y) {
            mMapData[faceBase + y * size] = blended[faceBase + y * size];
            mMapData[faceBase + y * size + size - 1] = blended[faceBase + y * size + size - 1];
        }
        for (int x = 1; x < size - 1; ++x) {
            mMapData[faceBase + x] = blended[faceBase + x];
            mMapData[faceBase + lastRow + x] = blended[faceBase + lastRow + x];
        }
        faceBase += faceArea;
    }

    blended.erase(blended.begin(), blended.end());
}

} // namespace SP
