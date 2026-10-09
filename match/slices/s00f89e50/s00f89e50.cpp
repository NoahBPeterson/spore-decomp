// Slice s00f89e50 -- SP::cTerrainMap<unsigned int>::GetVector4 (0x00f89e50, 4480 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Bilinear sample of a cube-map of packed Direction4c texels. `uv` = {u, v, face (int bits)}.
// The four corner texels (x0/x1, y0/y1) are fetched; corners falling off the face edge are
// remapped via WrapCubeFace. A mask of which corners are off-face (bit0 c00, bit1 c10,
// bit2 c01, bit3 c11) selects: 0 = all direct; 3/5/10/12 = two corners wrapped; 7/11/13/14 =
// three corners off, so the off-map corner is the average of the other three; anything else
// returns a constant vector.
#include "types.h"

struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
};

struct FaceUV { float u, v; int face; };

Vector4 __cdecl ToVector4(uint32_t packed);     // 0x00f885f0 (file-static in the original)
void WrapCubeFace(int size, int* face, int* x, int* y, int* rot, int* flip);   // 0x00684ca0
extern Vector4 kDefaultVector4;   // 0x016c9bd4

#pragma warning(disable:4035)
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

namespace SP {

struct cTerrainMapBase {
    uint32_t pad0[2];
    uint32_t mFaceSize;   // +0x8
    uint32_t mModCount;   // +0xc
};

template <class T> struct cTerrainMap : cTerrainMapBase {
    T* mpBegin;           // +0x10 (vector storage)
    T* mpEnd;
    T* mpCapacity;

    void GetVector4(Vector4* result, const FaceUV* uv);
};

#define TEXEL(f, y, x) mpBegin[(((f) * mFaceSize + (y)) * mFaceSize) + (x)]

template <>
void cTerrainMap<unsigned int>::GetVector4(Vector4* result, const FaceUV* uv)
{
    float size = (float)mFaceSize;
    int face = *(const int*)&uv->face;
    float fx = uv->u * size - 0.5f;
    float fy = uv->v * size - 0.5f;
    int x0 = FloorToInt(fx);
    int y0 = FloorToInt(fy);
    int x1 = x0 + 1;
    int y1 = y0 + 1;
    float tx = fx - (float)x0;
    float ty = fy - (float)y0;
    uint32_t mask = ~(mFaceSize - 1);

    // Per-corner (x, y, face); wrapped in place when off the face.
    int c00x = x0, c00y = y0, c00f = face;
    int c10x = x1, c10y = y0, c10f = face;
    int c01x = x0, c01y = y1, c01f = face;
    int c11x = x1, c11y = y1, c11f = face;

    uint32_t m00 = (y0 | x0) & mask;
    uint32_t m10 = (y0 | x1) & mask;
    uint32_t m01 = (y1 | x0) & mask;
    uint32_t m11 = (y1 | x1) & mask;
    unsigned idx = (m11 ? 8u : 0u) + (m00 ? 1u : 0u) + (m01 ? 4u : 0u) + (m10 ? 2u : 0u);

    Vector4 v00, v10, v01, v11;

    switch (idx) {
    case 0:
        v00 = ToVector4(TEXEL(face, y0, x0));
        v10 = ToVector4(TEXEL(face, y0, x1));
        v01 = ToVector4(TEXEL(face, y1, x0));
        v11 = ToVector4(TEXEL(face, y1, x1));
        break;
    default:
        *result = kDefaultVector4;
        return;
    case 3:
        if (((c00y | c00x) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c00f, &c00x, &c00y, 0, 0);
        if (((c10x | c10y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c10f, &c10x, &c10y, 0, 0);
        v00 = ToVector4(TEXEL(c00f, c00y, c00x));
        v10 = ToVector4(TEXEL(c10f, c10y, c10x));
        v01 = ToVector4(TEXEL(c01f, c01y, c01x));
        v11 = ToVector4(TEXEL(c11f, c11y, c11x));
        break;
    case 5:
        if (((c00y | c00x) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c00f, &c00x, &c00y, 0, 0);
        if (((c01x | c01y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c01f, &c01x, &c01y, 0, 0);
        v00 = ToVector4(TEXEL(c00f, c00y, c00x));
        v10 = ToVector4(TEXEL(c10f, c10y, c10x));
        v01 = ToVector4(TEXEL(c01f, c01y, c01x));
        v11 = ToVector4(TEXEL(c11f, c11y, c11x));
        break;
    case 7:
        v11 = ToVector4(TEXEL(face, y1, x1));
        if (((c10x | c10y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c10f, &c10x, &c10y, 0, 0);
        if (((c01x | c01y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c01f, &c01x, &c01y, 0, 0);
        v10 = ToVector4(TEXEL(c10f, c10y, c10x));
        v01 = ToVector4(TEXEL(c01f, c01y, c01x));
        v00.x = ((v01.x + v10.x) + v11.x) * 0.33333334f;
        v00.y = ((v01.y + v10.y) + v11.y) * 0.33333334f;
        v00.z = ((v01.z + v10.z) + v11.z) * 0.33333334f;
        v00.w = ((v01.w + v10.w) + v11.w) * 0.33333334f;
        break;
    case 10:
        if (((c10x | c10y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c10f, &c10x, &c10y, 0, 0);
        if (((c11x | c11y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c11f, &c11x, &c11y, 0, 0);
        v00 = ToVector4(TEXEL(c00f, c00y, c00x));
        v10 = ToVector4(TEXEL(c10f, c10y, c10x));
        v01 = ToVector4(TEXEL(c01f, c01y, c01x));
        v11 = ToVector4(TEXEL(c11f, c11y, c11x));
        break;
    case 0xb:
        v01 = ToVector4(TEXEL(face, y1, x0));
        if (((c00y | c00x) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c00f, &c00x, &c00y, 0, 0);
        if (((c11x | c11y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c11f, &c11x, &c11y, 0, 0);
        v00 = ToVector4(TEXEL(c00f, c00y, c00x));
        v11 = ToVector4(TEXEL(c11f, c11y, c11x));
        v10.x = ((v01.x + v00.x) + v11.x) * 0.33333334f;
        v10.y = ((v01.y + v00.y) + v11.y) * 0.33333334f;
        v10.z = ((v01.z + v00.z) + v11.z) * 0.33333334f;
        v10.w = ((v01.w + v00.w) + v11.w) * 0.33333334f;
        break;
    case 0xc:
        if (((c01y | c01x) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c01f, &c01x, &c01y, 0, 0);
        if (((c11x | c11y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c11f, &c11x, &c11y, 0, 0);
        v00 = ToVector4(TEXEL(c00f, c00y, c00x));
        v10 = ToVector4(TEXEL(c10f, c10y, c10x));
        v01 = ToVector4(TEXEL(c01f, c01y, c01x));
        v11 = ToVector4(TEXEL(c11f, c11y, c11x));
        break;
    case 0xd:
        v10 = ToVector4(TEXEL(face, y0, x1));
        if (((c00y | c00x) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c00f, &c00x, &c00y, 0, 0);
        if (((c11x | c11y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c11f, &c11x, &c11y, 0, 0);
        v00 = ToVector4(TEXEL(c00f, c00y, c00x));
        v11 = ToVector4(TEXEL(c11f, c11y, c11x));
        v01.x = ((v10.x + v00.x) + v11.x) * 0.33333334f;
        v01.y = ((v00.y + v10.y) + v11.y) * 0.33333334f;
        v01.z = ((v00.z + v10.z) + v11.z) * 0.33333334f;
        v01.w = ((v00.w + v10.w) + v11.w) * 0.33333334f;
        break;
    case 0xe:
        v00 = ToVector4(TEXEL(face, y0, x0));
        if (((c10x | c10y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c10f, &c10x, &c10y, 0, 0);
        if (((c01x | c01y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c01f, &c01x, &c01y, 0, 0);
        v10 = ToVector4(TEXEL(c10f, c10y, c10x));
        v01 = ToVector4(TEXEL(c01f, c01y, c01x));
        v11.x = (v01.x + (v10.x + v00.x)) * 0.33333334f;
        v11.y = (v01.y + (v00.y + v10.y)) * 0.33333334f;
        v11.z = (v01.z + (v00.z + v10.z)) * 0.33333334f;
        v11.w = (v01.w + (v00.w + v10.w)) * 0.33333334f;
        break;
    }

    float ix = 1.0f - tx;
    float iy = 1.0f - ty;
    result->x = (iy * (v00.x * ix + v10.x * tx) + (v01.x * ix + v11.x * tx) * ty) * 0.003921569f;
    result->y = (iy * (ix * v00.y + v10.y * tx) + (ix * v01.y + v11.y * tx) * ty) * 0.003921569f;
    result->z = (iy * (ix * v00.z + v10.z * tx) + (ix * v01.z + v11.z * tx) * ty) * 0.003921569f;
    result->w = (iy * (ix * v00.w + v10.w * tx) + (ix * v01.w + v11.w * tx) * ty) * 0.003921569f;
}

}  // namespace SP

void Instantiate(SP::cTerrainMap<unsigned int>* m, Vector4* r, const FaceUV* uv) { m->GetVector4(r, uv); }
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
