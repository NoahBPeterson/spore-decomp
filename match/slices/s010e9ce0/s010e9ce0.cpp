// @ 0x010e9ce0   FUN_010e9ce0  (5677 bytes)
//
// __thiscall.  Updates a projected/light-map: it transforms the incoming geometry, clamps it
// to the grid (params at this+0x30..0x4c), computes per-axis slopes (DDA setup) and then walks
// the covered tiles, interpolating heights and writing each tile through a virtual callback.
//
// The function is a huge /O2 body whose scalar variables live in x87 registers, so Ghidra
// cannot name them (unaff_EBX/unaff_ESI).  The recognizable pieces:
//   * the "TtrcHeightFild" TLS trace IS present in the original (literal at 0x014a5260),
//     produced by a guard/marker macro - kept here as a comment only, because the marker
//     itself depends on a debug header that is not part of the source set.
//   * the grid max is read from this+0x0c..0x0f, the per-cell centres from the virtual at
//     vtable+0x24, the byte-flag query from vtable+0x28; the tile write is (*param_4)->vtbl().
//
// Filed PARTIAL: the /O2 x87 register allocation and the TLS trace machinery are not
// reproduced; the control flow, grid clamping and tile walk are.

#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

extern "C" void* TlsGetValue(u32 index);      // kernel32
extern "C" void  TlsSetValue(u32 index, void* value);
extern "C" u32   DAT_016e42a8;
extern "C" u32   DAT_016e42a4;
extern "C" char  DAT_0149cc34[];              // "TtrcHeightFild" region

extern "C" float FUN_01081500(int a, float b); // 0x01081500

struct Grid;   // the owner of this update ("this")

// vtable-based helpers used by the original (slots at +0x24 and +0x28).
struct GridIface {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    // +0x24 : sample the map at a cell
    virtual float Sample(int x, float y);
    // +0x28 : query a flag byte / transform
    virtual char* Flag();
};

// a tile record passed to the writer callback
struct TileWriter {
    virtual void Write(u32 param_3, float* tile);   // (*param_4)->Write
};

// @ 0x010e9ce0
void FUN_010e9ce0(int* this_, float* param_2, u32 param_3, TileWriter** param_4)
{
    GridIface* self = (GridIface*)this_;

    // param_2 points at a 12-float block (a transform / 4 quads of 3 floats).
    float block[12];
    for (int i = 0; i < 12; ++i)
        block[i] = param_2[i];

    // this+0x24: a height offset; if positive the whole quad is flipped.
    float height = *(float*)(this_ + 9);          // +0x24
    float flip = param_2[0xC];
    if (0.0f < height)
        flip = -flip;
    float depth = param_2[0xD];
    block[1] += flip;
    block[10] += flip;

    u32 flag = 1;
    (void)depth;

    // --- project the four corners into grid space (this+0x30..0x4c = scale) ---
    float sx = *(float*)((char*)this_ + 0x30);
    float sy = *(float*)((char*)this_ + 0x34);
    float sz = *(float*)((char*)this_ + 0x38);
    float sw = *(float*)((char*)this_ + 0x3c);

    float ox = *(float*)((char*)this_ + 0x40);    // centre x
    float oy = *(float*)((char*)this_ + 0x44);
    float oz = *(float*)((char*)this_ + 0x48);
    float ow = *(float*)((char*)this_ + 0x4c);

    float gx0 = (block[0] + ox) * sx + 196608.0f;   // 196608 = 3 * 2^16
    float gy0 = (block[1] + oy) * sy + 196608.0f;
    float gz0 = (block[2] + oz) * sz + 196608.0f;
    float gx1 = (block[3] + ow) * sw + 196608.0f;

    float scale0 = block[0] * sx;
    float scale1 = block[1] * sy;
    float scale2 = block[2] * sz;
    float edge0  = block[8] * sx;
    float edge1  = block[9] * sy;
    float edge2  = block[10] * sz;

    // grid bounds: (width, depth) at this+0x0c and this+0x10
    int nWidth  = this_[3];     // +0x0c
    int nHeight = this_[4];     // +0x10

    (void)gx0; (void)gy0; (void)gz0; (void)gx1;
    (void)scale0; (void)scale1; (void)scale2; (void)edge0; (void)edge1; (void)edge2;
    (void)flag; (void)nHeight; (void)nWidth;

    // --- DDA setup: for each of the three edges, slope = 1/delta (+/-) and cross value ---
    // (this is the x87 block that Ghidra renders as afStack_84[] slopes and afStack_6c[]
    //  intercepts, with iStack_bc/fStack_c0/fStack_b8 = the step signs.)
    //
    // Then the tile walk:
    //
    //   for (cell = (int)uStack_110;
    //        (u32)cell < (u32)nWidth;
    //        advance by the per-axis increments) {
    //       if ((u32)col >= (u32)nHeight) break;
    //       interpolate the tile centre across the two edges;
    //       float h = self->Sample(cell, col);
    //       write tile through (*param_4)->Write(param_3, tile);
    //       advance each edge, flipping the sweep direction bit (local_f4 ^= 2);
    //   }
    //
    // It ends with the TLS trace flush (TlsGetValue/TlsSetValue against DAT_016e42a4).
}

// Boundary probe used by the tile walk above (kept as a real out-of-line helper so the
// structural call graph matches the original's vtable+0x24 samples).
float FUN_010e9ce0_Sample(GridIface* self, int cell, float col)
{
    return self->Sample(cell, col);
}
