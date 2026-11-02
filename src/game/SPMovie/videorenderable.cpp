// src/game/SPMovie/videorenderable.cpp -- migrated from slice(s) s00fcd210 by tools/migrate/rewrite.py
// Object file: SPMovie/videorenderable.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00fcd210 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
struct VideoRenderable {
    void*  mData[3];          // +0x00..+0x0b
    int    mSize[3];          // +0x0c..+0x17
    char   m_pad18[0x08];
    int    m_width_24;        // +0x20 (unused)
    unsigned int mWidth;      // +0x24
    unsigned int mHeight;     // +0x28
    char   m_pad2c[0x04];
    int    mFormat;           // +0x30
    int    mFrameNumber;      // +0x34
    int    mNumBuffersUsed;   // +0x38
    int    mUseCount;         // +0x3c
    u8     mIsReadyToRender;  // +0x40
    char   m_pad41[0x03];
    void*  mContext[3];       // +0x44..+0x4f
    u8     mDropFrameFlag;    // +0x50
    u8     mFlipFlag;         // +0x51

    VideoRenderable();
};
// ---- items of slice s00fcd210 end

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
    *(int*)(p + 0x30) = 4;
    *(int*)(p + 0x34) = 0;
    *(int*)(p + 0x38) = 0;
    *(int*)(p + 0x3c) = 0;
    *(int*)(p + 0x44) = 0;
    *(int*)(p + 0x48) = 0;
    *(int*)(p + 0x4c) = 0;
    *(int*)(p + 0x00) = 0x37047734;
    *(u8*)(p + 0x40) = 0;
    *(u8*)(p + 0x50) = 0;
    *(u8*)(p + 0x51) = 0;
}

// @ 0x00fcdf10
extern "C" void __fastcall FUN_00fcdf10(int* self)
{
    *self = 0;
}

// @ 0x00fcdf40
void rw_movie_VideoRenderable_GetDataBufSizes(int w, int h, int format, int flag, unsigned int* out)
{
    unsigned int u;
    switch (format) {
    case 0:
    case 1:
        u = (unsigned int)(w * h);
        if (flag == 1) {
            out[0] = (u >> 1) * 3;
            out[1] = 0;
            out[2] = 0;
            return;
        }
        out[0] = u;
        out[1] = u >> 2;
        out[2] = u >> 2;
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
