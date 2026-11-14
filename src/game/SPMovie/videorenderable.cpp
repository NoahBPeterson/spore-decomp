// src/game/SPMovie/videorenderable.cpp
// Object file: SPMovie/videorenderable.obj.
//
// The buffer holder that the movie renderer hands to the renderer back end. No canonical header declares the
// class yet, so the layout lives here; each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// Stand-in for the video renderable whose data buffers the renderer allocates. Field names after mFormat are
// guesses; only the offsets matter.
struct VideoRenderable {
    void*        mData[3];          // +0x00  pointers into the per-plane data buffers
    int          mSize[3];          // +0x0c  their sizes in bytes
    char         pad18[0x08];       // +0x18
    unsigned int mWidth;            // +0x24
    unsigned int mHeight;           // +0x28
    char         pad2c[0x04];       // +0x2c
    int          mFormat;           // +0x30  pixel format; 4 is the empty/closed value
    int          mFrameNumber;      // +0x34
    int          mNumBuffersUsed;   // +0x38
    int          mUseCount;         // +0x3c
    unsigned char mIsReadyToRender; // +0x40
    char         pad41[0x03];       // +0x41
    void*        mContext[3];       // +0x44
    unsigned char mDropFrameFlag;   // +0x50
    unsigned char mFlipFlag;        // +0x51

    VideoRenderable();
};

// Pixel format used as "no format" by these buffers.
static const int kFormatNone = 4;

// @ 0x00fcdec0
VideoRenderable::VideoRenderable()
{
    char* p = (char*)this;
    *(int*)(p + 0x04) = 0;
    *(int*)(p + 0x08) = 0;
    *(int*)(p + 0x0c) = 0;
    *(int*)(p + 0x10) = 0;
    *(int*)(p + 0x14) = 0;
    *(int*)(p + 0x18) = 0;
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 0x2c) = 0;
    *(int*)(p + 0x30) = kFormatNone;
    *(int*)(p + 0x34) = 0;
    *(int*)(p + 0x38) = 0;
    *(int*)(p + 0x3c) = 0;
    *(int*)(p + 0x44) = 0;
    *(int*)(p + 0x48) = 0;
    *(int*)(p + 0x4c) = 0;
    *(int*)(p + 0x00) = 0x37047734;
    *(unsigned char*)(p + 0x40) = 0;
    *(unsigned char*)(p + 0x50) = 0;
    *(unsigned char*)(p + 0x51) = 0;
}

// @ 0x00fcdf10
extern "C" void __fastcall FUN_00fcdf10(int* self)
{
    *self = 0;
}

// @ 0x00fcdf40
void rw_movie_VideoRenderable_GetDataBufSizes(int w, int h, int format, int flag, unsigned int* out)
{
    // Number of pixels, shared by the two packed-ish formats.
    unsigned int pixels;

    switch (format) {
    case 0:
    case 1:
        pixels = (unsigned int)(w * h);
        if (flag == 1) {
            // Single strided plane.
            out[0] = (pixels >> 1) * 3;
            out[1] = 0;
            out[2] = 0;
            return;
        }
        // One luma plane plus two quarter-size chroma planes.
        out[0] = pixels;
        out[1] = pixels >> 2;
        out[2] = pixels >> 2;
        return;
    case 2:
        if (flag == 1) {
            out[0] = (unsigned int)(w * h * 3);
            out[1] = 0;
            out[2] = 0;
        }
        return;
    case 3:
        if (flag == 1) {
            out[0] = (unsigned int)(w * h * 4);
            out[1] = 0;
            out[2] = 0;
        }
        return;
    }
    return;
}
