// SPMovie/videoencoder_jpeg.obj -- JPEG video encoder (libjpeg backend).
// Each function keeps its '// @ 0xVA' marker; the VA is the retail address.

#include "game/types.h"

// Callees and globals owned by other translation units (address in the comment).
extern "C" void DoInsertValue(void* dst, void* src, int count);   // 0x11e0744
extern "C" int  jpeg_std_error(void*);                            // 0x85f190
extern "C" void jpeg_create_compress_170(void*, int, int);        // 0x8502a0
extern "C" void jpeg_set_defaults(void*);                         // 0x855a30
extern "C" void jpeg_set_quality(void*, int, int);                // 0x8550e0
extern "C" void jpeg_start_compress(void*, int);                  // 0x850570
extern "C" void jpeg_write_scanlines(void*, void*, int);          // 0x8505f0
extern "C" void jpeg_finish_compress(void*);                      // 0x8503f0
extern "C" void jpeg_destroy(void*);                              // 0x850370
extern "C" void FUN_00fcdc10();                                   // 0xfcdc10

typedef unsigned char u8;

// rw::movie::ICoreAllocator, as the object spells it (see the slice's local copy).
struct ICoreAllocator {
    void* m_vtbl;  // +0x00
};

// rw::movie::VideoEncoder_Jpeg (retail member offsets).
struct VideoEncoder_Jpeg {
    char            m_pad00[0x04];
    ICoreAllocator* mAllocator;                          // +0x04
    void (*mEncodedDataCallback)(u8*, int, int, void*);  // +0x08
    void (*mEncodingErrorCallback)(const char*, void*);  // +0x0c
    void*           mEncodedDataCallbackData;            // +0x10
    void*           mEncodingErrorCallbackData;          // +0x14
    u8*             mEncodeBuffer;                       // +0x18
    unsigned int    mEncodeBufferSize;                   // +0x1c
    unsigned int    mEncodeBufferPos;                    // +0x20
    unsigned int    mWidth;                              // +0x24
    unsigned int    mHeight;                             // +0x28
    char            m_pad2c[0x04];
    unsigned int    mBitsPerSecond;                      // +0x30
    unsigned int    mQuality;                            // +0x34
    unsigned int    mFrameNumber;                        // +0x38

    void Init(ICoreAllocator* alloc);
    void Shutdown();
    unsigned int GetSuggestedDecoderBufferSize();
    void SetBitsPerSecond(unsigned int v);
    unsigned int GetBitsPerSecond();
    void SetQuality(unsigned int v);
    void Encode(void* frame);
};

// The three callbacks FUN_00fcda10 installs are free functions of SPMovie/_at_00fc0000.obj.
extern "C" void FUN_00fcd970(int self);   // 0x00fcd970
extern "C" int  FUN_00fcd9a0(int self);   // 0x00fcd9a0
extern "C" void FUN_00fcd9e0(int self);   // 0x00fcd9e0

// Highest quality the caller may ask for; higher values are clamped with an error.
static const unsigned int kMaxQuality = 10000;

// @ 0x00fcda10
// Lazily allocates the 0x20-byte callback block at this+0x14 and fills it: three callbacks
// (0x00fcd970/0x00fcd9a0/0x00fcd9e0) plus the two arguments.
extern "C" void FUN_00fcda10(int self, int p2, int p3)
{
    if (*(int*)(self + 0x14) == 0) {
        int v = ((int (*)(int, int, int))**(void***)(self + 4))(self, 0, 0x20);
        *(int*)(self + 0x14) = v;
    }
    int* p = *(int**)(self + 0x14);
    p[2] = (int)&FUN_00fcd970;
    p[3] = (int)&FUN_00fcd9a0;
    p[4] = (int)&FUN_00fcd9e0;
    p[5] = p2;
    p[6] = p3;
}

// @ 0x00fcda60
void VideoEncoder_Jpeg::Init(ICoreAllocator* alloc)
{
    unsigned int sz = mHeight * mWidth * 2 + 0x100;
    mEncodeBufferSize = sz;
    mAllocator = alloc;
    mEncodeBuffer = (u8*)((void* (__thiscall*)(ICoreAllocator*, unsigned int, const char*, int))
                          ((void**)alloc->m_vtbl)[2])(alloc, sz, "JPEG Encode Buffer", 1);
}

// @ 0x00fcdaa0
void VideoEncoder_Jpeg::Shutdown()
{
    if (mEncodeBuffer != 0 && mAllocator != 0) {
        ((void (*)(void*, u8*, int))((void**)mAllocator->m_vtbl)[3])(mAllocator, mEncodeBuffer, 0);
        mEncodeBuffer = 0;
        mEncodeBufferSize = 0;
    }
}

// @ 0x00fcdb00
unsigned int VideoEncoder_Jpeg::GetSuggestedDecoderBufferSize()
{
    return (mHeight * mWidth * 3) >> 1;
}

// @ 0x00fcdb20
// Repacks n 32-bit source pixels from format fmt into tightly packed 24-bit BGR
// rows: fmt 0 (BGRA, the four bytes are read with the alpha first), 3 (RGBA),
// 4 (BGRA) and 1 (24-bit, moved verbatim by DoInsertValue). Format 2 needs no work.
extern "C" void FUN_00fcdb20(int fmt, unsigned char* src, unsigned char* dst, int n)
{
    switch (fmt) {
    case 0:
        if (n > 0) {
            src = src + 2;
            do {
                dst[0] = src[-1];
                dst[1] = src[0];
                dst[2] = src[1];
                dst += 3;
                src += 4;
            } while (--n != 0);
        }
        return;
    case 3:
        if (n > 0) {
            do {
                dst[0] = src[2];
                dst[1] = src[1];
                dst[2] = src[0];
                dst += 3;
                src += 4;
            } while (--n != 0);
        }
        return;
    case 4:
        if (n > 0) {
            do {
                dst[0] = src[0];
                dst[1] = src[1];
                dst[2] = src[2];
                dst += 3;
                src += 4;
            } while (--n != 0);
        }
        return;
    case 1:
        DoInsertValue(dst, src, n * 3);
        return;
    case 2:
        return;
    }
}

// @ 0x00fcdc40
void VideoEncoder_Jpeg::SetBitsPerSecond(unsigned int v)
{
    mBitsPerSecond = v;
    if (mEncodingErrorCallback != 0)
        mEncodingErrorCallback(
            "VideoEncoder_Jpeg: Cannot invoke SetBytesPerSecond.  Use SetQuality instead.",
            mEncodingErrorCallbackData);
}

// @ 0x00fcdc60
unsigned int VideoEncoder_Jpeg::GetBitsPerSecond()
{
    if (mEncodingErrorCallback != 0)
        mEncodingErrorCallback(
            "VideoEncoder_Jpeg: Cannot invoke GetBytesPerSecond.  Use GetQuality instead.",
            mEncodingErrorCallbackData);
    return mBitsPerSecond;
}

// @ 0x00fcdc80
void VideoEncoder_Jpeg::SetQuality(unsigned int v)
{
    if (v > kMaxQuality) {
        if (mEncodingErrorCallback != 0)
            mEncodingErrorCallback(
                "VideoEncoder_Jpeg: Quality must be between 0 and 10000.",
                mEncodingErrorCallbackData);
        v = kMaxQuality;
    }
    mQuality = v;
}

// @ 0x00fcdcb0
void VideoEncoder_Jpeg::Encode(void* frame)
{
    int* fi = (int*)frame;
    if (fi[1] != (int)mWidth || fi[2] != (int)mHeight) {
        if (mEncodingErrorCallback != 0)
            mEncodingErrorCallback(
                "VideoEncoder_Jpeg: the supplied VideoFrame object has the wrong dimensions.",
                mEncodingErrorCallbackData);
        return;
    }
    u8 cinfo[0x1f4];  // jpeg_compress_struct; the fields written below are part of it.
    int* ci = (int*)cinfo;
    ci[0] = jpeg_std_error(cinfo + 0x174);
    jpeg_create_compress_170(cinfo, 0x3d, 0x170);
    FUN_00fcda10((int)cinfo, (int)&FUN_00fcdc10, (int)this);
    *(int*)(cinfo + 0x34) = fi[1];
    *(int*)(cinfo + 0x38) = fi[2];
    *(int*)(cinfo + 0x3c) = 3;  // input_components
    *(int*)(cinfo + 0x40) = 2;  // in_color_space
    jpeg_set_defaults(cinfo);
    jpeg_set_quality(cinfo, mQuality / 100, 1);
    *(int*)(cinfo + 0x168) = 0;
    mEncodeBufferPos = 0;
    jpeg_start_compress(cinfo, 1);
    u8* line = (u8*)((void* (__thiscall*)(ICoreAllocator*, unsigned int, const char*, int))
                     ((void**)mAllocator->m_vtbl)[2])(mAllocator, *(int*)(cinfo + 0x34) * 3,
                                                      "JPEG Line Buffer", 0);
    if (line != 0) {
        // Bytes per source pixel: 24-bit data is packed, every other format is 32-bit.
        int bpp = 1;
        switch (fi[0]) {
        case 0: case 3: case 4: bpp = 4; break;
        case 1: bpp = 3; break;
        }
        for (int y = 0; y < *(int*)(cinfo + 0x34); y++) {
            FUN_00fcdb20(fi[0], (u8*)(fi[1] * y * bpp + fi[3]), line, *(int*)(cinfo + 0x30));
            jpeg_write_scanlines(cinfo, &line, 1);
        }
        ((void (__thiscall*)(ICoreAllocator*, u8*, int))
         ((void**)mAllocator->m_vtbl)[3])(mAllocator, line, 0);
    }
    jpeg_finish_compress(cinfo);
    jpeg_destroy(cinfo);
    if (mEncodedDataCallback != 0)
        mEncodedDataCallback(mEncodeBuffer, mEncodeBufferPos, mFrameNumber, mEncodedDataCallbackData);
    mFrameNumber++;
}
