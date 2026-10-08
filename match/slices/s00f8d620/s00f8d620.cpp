// Slice s00f8d620 -- SP::cTerrainMap<unsigned short>::GetFloat (0x00f8d620).
// ushort-texel variant of s00f88650: texel value (v - 32768) / 32768.
// `uv` = {u, v, face (int bits)}. A mask of which corners are off-face (bit0 c00, bit1 c10,
// bit2 c01, bit3 c11) selects: 0 = all direct; 3/5/10/12 = two corners wrapped by WrapCubeFace;
// 7/11/13/14 = three corners off, so the off-map corner is the average of the other three; any
// other mask returns 0.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct FaceUV { float u, v; int face; };

void WrapCubeFace(int size, int* face, int* x, int* y, int* rot, int* flip);   // 0x00684ca0

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

    float GetFloat(const FaceUV* uv);
};

#define TEXEL(f, y, x) (float)mpBegin[(((f) * mFaceSize + (y)) * mFaceSize) + (x)]

// @ 0x00f8d620
template <>
float cTerrainMap<unsigned short>::GetFloat(const FaceUV* uv)
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

    float v00, v10, v01, v11;

    switch (idx) {
    case 0:
        v00 = TEXEL(face, y0, x0);
        v10 = TEXEL(face, y0, x1);
        v01 = TEXEL(face, y1, x0);
        v11 = TEXEL(face, y1, x1);
        break;
    default:
        return 0.0f;
    case 3:
        if (((c00y | c00x) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c00f, &c00x, &c00y, 0, 0);
        if (((c10x | c10y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c10f, &c10x, &c10y, 0, 0);
        v00 = TEXEL(c00f, c00y, c00x);
        v10 = TEXEL(c10f, c10y, c10x);
        v01 = TEXEL(c01f, c01y, c01x);
        v11 = TEXEL(c11f, c11y, c11x);
        break;
    case 5:
        if (((c00y | c00x) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c00f, &c00x, &c00y, 0, 0);
        if (((c01x | c01y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c01f, &c01x, &c01y, 0, 0);
        v00 = TEXEL(c00f, c00y, c00x);
        v10 = TEXEL(c10f, c10y, c10x);
        v01 = TEXEL(c01f, c01y, c01x);
        v11 = TEXEL(c11f, c11y, c11x);
        break;
    case 7:
        v11 = TEXEL(face, y1, x1);
        if (((c10x | c10y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c10f, &c10x, &c10y, 0, 0);
        if (((c01x | c01y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c01f, &c01x, &c01y, 0, 0);
        v10 = TEXEL(c10f, c10y, c10x);
        v01 = TEXEL(c01f, c01y, c01x);
        v00 = ((v11 + v01) + v10) * 0.33333334f;
        break;
    case 10:
        if (((c10x | c10y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c10f, &c10x, &c10y, 0, 0);
        if (((c11x | c11y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c11f, &c11x, &c11y, 0, 0);
        v00 = TEXEL(c00f, c00y, c00x);
        v10 = TEXEL(c10f, c10y, c10x);
        v01 = TEXEL(c01f, c01y, c01x);
        v11 = TEXEL(c11f, c11y, c11x);
        break;
    case 0xb:
        v01 = TEXEL(face, y1, x0);
        if (((c00y | c00x) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c00f, &c00x, &c00y, 0, 0);
        if (((c11x | c11y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c11f, &c11x, &c11y, 0, 0);
        v11 = TEXEL(c11f, c11y, c11x);
        v00 = TEXEL(c00f, c00y, c00x);
        v10 = ((v11 + v01) + v00) * 0.33333334f;
        break;
    case 0xc:
        if (((c01y | c01x) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c01f, &c01x, &c01y, 0, 0);
        if (((c11x | c11y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c11f, &c11x, &c11y, 0, 0);
        v00 = TEXEL(c00f, c00y, c00x);
        v10 = TEXEL(c10f, c10y, c10x);
        v01 = TEXEL(c01f, c01y, c01x);
        v11 = TEXEL(c11f, c11y, c11x);
        break;
    case 0xd:
        v10 = TEXEL(face, y0, x1);
        if (((c00y | c00x) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c00f, &c00x, &c00y, 0, 0);
        if (((c11x | c11y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c11f, &c11x, &c11y, 0, 0);
        v11 = TEXEL(c11f, c11y, c11x);
        v00 = TEXEL(c00f, c00y, c00x);
        v01 = ((v11 + v10) + v00) * 0.33333334f;
        break;
    case 0xe:
        v00 = TEXEL(face, y0, x0);
        if (((c10x | c10y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c10f, &c10x, &c10y, 0, 0);
        if (((c01x | c01y) & ~(mFaceSize - 1)) != 0)
            WrapCubeFace(mFaceSize, &c01f, &c01x, &c01y, 0, 0);
        v01 = TEXEL(c01f, c01y, c01x);
        v10 = TEXEL(c10f, c10y, c10x);
        v11 = ((v01 + v10) + v00) * 0.33333334f;
        break;
    }

    float ix = 1.0f - tx;
    float iy = 1.0f - ty;
    return (((ix * v01 + v11 * tx) * ty + (v10 * tx + ix * v00) * iy) - 32768.0f) * 3.0517578e-05f;
}

}  // namespace SP

float Instantiate_GetFloat(SP::cTerrainMap<unsigned short>* m, const FaceUV* uv) { return m->GetFloat(uv); }
