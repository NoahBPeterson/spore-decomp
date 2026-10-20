// Slice s00fcd210 -- rw::movie video decode/encode, SList, VideoRenderable.
// Reconstructed from the retail object. Byte-exact-first; local stub declarations
// are used instead of shared headers (see slice notes).

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

struct DecodeOptions;

static unsigned int cw_ctl(unsigned int newv, unsigned int mask)
{
    return ((unsigned int (__cdecl*)(unsigned int, unsigned int))0x13cc384)(newv, mask);
}

// ---------------------------------------------------------------------------
// SList / SNode (rw::core container, templated on a comparator)
// ---------------------------------------------------------------------------
struct SNode {
    void** m_vtbl;   // +0x00
    // the object payload (comparison key) is embedded at +0x10
};

struct SList {
    char   m_pad00[0x04];
    SNode* m_head;       // +0x04
    SNode* m_tail;       // +0x08
    int    m_count;      // +0x0c
    int    LoadNewNode_helper();
};

// ---------------------------------------------------------------------------
// jpeg / vp6 encoder structs
// ---------------------------------------------------------------------------
struct ICoreAllocator {
    void* m_vtbl;  // +0x00
};

struct VideoEncoder_Jpeg {
    char          m_pad00[0x04];
    ICoreAllocator* mAllocator;             // +0x04
    void (*mEncodedDataCallback)(u8*, int, int, void*); // +0x08
    void (*mEncodingErrorCallback)(const char*, void*); // +0x0c
    void*         mEncodedDataCallbackData; // +0x10
    void*         mEncodingErrorCallbackData; // +0x14
    u8*           mEncodeBuffer;            // +0x18
    unsigned int  mEncodeBufferSize;        // +0x1c
    unsigned int  mEncodeBufferPos;         // +0x20
    unsigned int  mWidth;                   // +0x24
    unsigned int  mHeight;                  // +0x28
    char          m_pad2c[0x04];
    unsigned int  mBitsPerSecond;           // +0x30
    unsigned int  mQuality;                 // +0x34
    unsigned int  mFrameNumber;             // +0x38

    void Init(ICoreAllocator* alloc);
    void Shutdown();
    unsigned int GetSuggestedDecoderBufferSize();
    void SetBitsPerSecond(unsigned int v);
    unsigned int GetBitsPerSecond();
    void SetQuality(unsigned int v);
    void Encode(void* frame);
};

struct VideoDecoder_Vp6 {
    void*      m_vtbl;        // +0x00
    void*      m_pad04;
    void*      mStream;       // +0x08 (rw::core::filesys::Stream*)
    int        mCount;        // +0x0c
    int        m_a10;         // +0x10
    int        m_a14;         // +0x14
    int        m_a18;         // +0x18

    void Decode(int p2, DecodeOptions* opt);
};

struct Vp6Frame {
    char          m_pad00[0x04];
    u8*           mPlaneY;      // +0x04
    u8*           mPlaneU;      // +0x08
    u8*           mPlaneV;      // +0x0c
    char          m_pad10[0x0c];
    int           mStrideY;     // +0x1c
    int           mStrideU;     // +0x20
    int           mStrideV;     // +0x24
    char          m_pad28[0x0c];
    int           mFrameIndex;  // +0x34
    int           mFrameNumber; // +0x38
    char          m_pad3c[0x04];
    u8            mIsKeyFrame;  // +0x40
    char          m_pad41[0x0f];
    u8            mFlag50;      // +0x50
    u8            mFlag51;      // +0x51
};

// ---------------------------------------------------------------------------
// VideoRenderable
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// stream / alloc / helper externs
// ---------------------------------------------------------------------------
struct StreamChunk {
    char   m_pad00[0x04];
    int    mSize;    // +0x04
    int    mData;    // +0x08
};

// options struct passed to the decoder
struct DecodeOptions {
    char   m_pad00[0x04];
    u8*    mDstY;      // +0x04
    u8*    mDstU;      // +0x08
    u8*    mDstV;      // +0x0c
    int    mOut10;     // +0x10
    int    mSize14;    // +0x14
    int    mSize18;    // +0x18
    int    mStrideY;   // +0x1c
    int    mStrideU;   // +0x20
    int    mStrideV;   // +0x24
    int    mSize28;    // +0x28
    int    mSize2c;    // +0x2c
    int    mSize30;    // +0x30
    int    mFrameIndex; // +0x34
    int    mFrameNumber; // +0x38
    char   m_pad3c[0x04];
    u8     mIsKeyFrame; // +0x40
    char   m_pad41[0x0f];
    u8     mFlag50;     // +0x50
    u8     mFlag51;     // +0x51
};

extern "C" StreamChunk* rw_Stream_GetChunk(void* stream);   // 0x11e6b50
extern "C" void        rw_Chunk_Release(StreamChunk* c);    // 0x11e7c70
extern "C" int         vp6_decode_frame(int, int, int, int, int); // 0xfd6bf0
extern "C" int         vp6_get_info(int, void*);            // 0xfd6a50
extern "C" void        util_Copy16(u8*, u8*, int);          // 0x11ea910

// =========================================================================
// rw::SList::InsertSorted
// =========================================================================
extern "C" SNode* SList_LoadNewNode(SList* self, void* key, int a3);  // 0xfccf40

// @ 0x00fcd210
extern "C" int SList_InsertSorted(SList* self, void* key, SNode* node, int a4)
{
    SNode* pNew = SList_LoadNewNode(self, key, a4);
    if (self->m_count == 0) {
        self->m_tail = pNew;
        self->m_head = pNew;
        self->m_count = 1;
        return 0;
    }
    SNode* cur = self->m_head;
    SNode* prev = 0;
    bool done = false;
    while (cur != 0 && !done) {
        void** vt1 = (void**)cur->m_vtbl;
        void** vt2 = (void**)node->m_vtbl;
        int lhs = ((int (*)(void*))vt1[0])((char*)cur + 0x10);
        int rhs = ((int (*)(void*, int))vt2[0])(key, lhs);
        if (rhs == -1) {
            done = true;
        } else {
            prev = cur;
            cur = (SNode*)((void* (*)(void*))((void**)cur->m_vtbl)[3])(cur);
        }
    }
    (void)a4;
    if (prev == 0) {
        ((void (*)(void*, SNode*))((void**)pNew->m_vtbl)[4])(pNew, self->m_head);
        self->m_count++;
        self->m_head = pNew;
        return 0;
    }
    if (cur == 0) {
        ((void (*)(void*, SNode*))((void**)prev->m_vtbl)[4])(prev, pNew);
        self->m_count++;
        self->m_tail = pNew;
        return 0;
    }
    ((void (*)(void*, SNode*))((void**)prev->m_vtbl)[3])(prev, pNew);
    ((void (*)(void*, SNode*))((void**)pNew->m_vtbl)[4])(pNew, cur);
    self->m_count++;
    return 0;
}

// =========================================================================
// FUN_00fcd320 / FUN_00fcd370  --  compare+insert trampolines
// =========================================================================
struct Vp6Tramp {
    int  Method320(int p2, int p3, int* p4);
    int  Method370(int p2, int p3, int* p4);
    void* Get();
};

// @ 0x00fcd320
int Vp6Tramp::Method320(int p2, int p3, int* p4)
{
    int uVar1 = (int)Get();
    if (p2 == 0 || p3 == 0)
        return -1;
    if (p4 == 0) {
        util_Copy16((u8*)uVar1, (u8*)p2, p3);
    } else {
        int iVar2 = ((int (*)(int, int, int))((void**)*p4)[0])(uVar1, p2, p3);
        if (iVar2 == -1)
            return -1;
    }
    return 0;
}

// @ 0x00fcd370
int Vp6Tramp::Method370(int p2, int p3, int* p4)
{
    int uVar1 = (int)Get();
    if (p2 == 0 || p3 == 0)
        return -1;
    if (p4 == 0) {
        util_Copy16((u8*)p2, (u8*)uVar1, p3);
    } else {
        int iVar2 = ((int (*)(int, int, int))((void**)*p4)[0])(p2, uVar1, p3);
        if (iVar2 == -1)
            return -1;
    }
    return 0;
}

// =========================================================================
// FUN_00fcd3c0  -- ctor: zero 3 fields, set two to -1
// =========================================================================
struct Vp6Ext {
    void Ctor3c0();
    void Ctor940(int p2);
    void CtorDE80();
    void Ctor3E0(int p2, int p3, int p4);
};

// @ 0x00fcd3c0
void Vp6Ext::Ctor3c0()
{
    int* self = (int*)this;
    self[0] = 0;
    self[1] = 0;
    self[2] = 0;
    self[3] = -1;
    self[4] = -1;
}

// =========================================================================
// FUN_00fcd3e0  -- vp6 decoder-extra ctor
// =========================================================================
extern "C" void sub_00fd2970(void*);   // 0xfd2970
extern "C" void sub_00fd5fa0(void);    // 0xfd5fa0
extern "C" void sub_00fd69c0(void*, int, int); // 0xfd69c0

// @ 0x00fcd3e0
void Vp6Ext::Ctor3E0(int p2, int p3, int p4)
{
    int self = (int)this;
    *(int*)(self + 0x04) = p2;
    *(int*)(self + 0x10) = p3;
    *(int*)(self + 0x14) = p4;
    *(int*)(self + 0x0c) = 0;
    sub_00fd2970((void*)p2);
    sub_00fd5fa0();
    sub_00fd69c0((void*)(self + 0x18), *(int*)(self + 0x10), *(int*)(self + 0x14));
}

// =========================================================================
// FUN_00fcd430  -- +0x18 release, tail-call
// =========================================================================
extern "C" void sub_00fd6c10(void*);   // 0xfd6c10
struct ILayoutElem {
    void SetSerializer();
};
extern "C" void ILayoutElem_SetSerializer_thiscall(); // 0xc2e4e0

struct Vp6Stream43 {
    void Method430();
};

// @ 0x00fcd430
void Vp6Stream43::Method430()
{
    sub_00fd6c10((void*)((char*)this + 0x18));
    ((ILayoutElem*)((char*)this + 0x18))->SetSerializer();
}

// =========================================================================
// FUN_00fcd450  -- rw::movie::VideoDecoder_Vp6::Decode (PDB candidate)
// =========================================================================
// @ 0x00fcd450
void VideoDecoder_Vp6::Decode(int p2, DecodeOptions* opt)
{
    StreamChunk* chunk = rw_Stream_GetChunk(mStream);
    if (chunk == 0) {
        opt->mOut10 = 0;
        opt->mIsKeyFrame = 1;
        return;
    }
    u8*  data = (u8*)chunk->mData;
    int  size = chunk->mSize - 8;
    if (size == 0) {
        rw_Chunk_Release(chunk);
        opt->mIsKeyFrame = 1;
        opt->mFrameIndex = mCount;
        opt->mFlag51 = 1;
        opt->mFlag50 = 1;
        mCount++;
        return;
    }
    opt->mFlag50 = 0;
    unsigned int oldCw = cw_ctl(0, 0);
    cw_ctl(0x10000, 0x30000);
    int rc = vp6_decode_frame(m_a18, (int)(data + 8), size, m_a10, m_a14);
    rw_Chunk_Release(chunk);
    if (rc != 0) {
        cw_ctl(oldCw, 0xfffff);
        opt->mIsKeyFrame = 1;
        return;
    }
    int wh[2];
    vp6_get_info(m_a18, wh);
    int w = wh[0];
    int h = wh[1];
    int idx = opt->mFrameNumber;
    int fmt = ((int (*)(void*))((void**)m_vtbl)[3])(this);

    if (fmt == 0) {
        u8* planeY;
        u8* planeU;
        u8* planeV;
        if (idx == 1) {
            planeY = opt->mDstY;
            planeU = (u8*)(h * w) + (int)opt->mDstY;
            planeV = (u8*)((h * w * 5) >> 2) + (int)opt->mDstY;
        } else {
            planeY = opt->mDstY;
            planeU = opt->mDstU;
            planeV = opt->mDstV;
        }
        u8* src = (u8*)((w * 3 + 0x123) * 0x10) + opt->mFrameIndex;
        int strideY = m_a10;
        int w60 = w + 0x60;
        opt->mStrideY = strideY;
        for (int i = 0; i < h; i++) {
            util_Copy16(planeY, src, w);
            planeY += strideY;
            src += w60;
        }
        int hh = w60 >> 1;
        u8* srcB = (u8*)((h + 0x60) * w60 + (hh * 3 + 3) * 8) + opt->mFrameIndex;
        int strideC = w >> 1;
        opt->mStrideU = m_a10 >> 1;
        for (int i = 0; i < (h & 0xfffffffe); i++) {
            util_Copy16(planeU, srcB, strideC);
            planeU += opt->mStrideU;
            srcB += hh;
        }
        u8* srcC = (u8*)((h + 0x60) * w60 * 5 >> 2) + (hh * 3 + 3) * 8 + opt->mFrameIndex;
        opt->mStrideV = opt->mStrideU;
        for (int i = 0; i < (h & 0xfffffffe); i++) {
            util_Copy16(planeV, srcC, strideC);
            planeV += opt->mStrideV;
            srcC += hh;
        }
        int total = h * w;
        if (idx == 1) {
            opt->mOut10 = total * 3 >> 1;
            opt->mSize28 = h;
            opt->mSize30 = 0;
        } else {
            opt->mOut10 = total;
            opt->mSize14 = total >> 2;
            opt->mSize18 = total >> 2;
            opt->mSize28 = h;
            opt->mSize30 = 0;
        }
    } else {
        if (idx == 1) {
            if (h == (int)m_a10 && w == (int)m_a14) {
                unsigned int n = ((m_a10 + 0x60) * (m_a14 + 0x60) * 3) >> 1;
                util_Copy16(opt->mDstY, (u8*)opt->mFrameIndex, n);
                opt->mOut10 = n;
                opt->mOut10 = (h * w * 3) >> 1;
            } else {
                int dst = opt->mFrameIndex;
                int s1 = (m_a14 + 0x60) * (m_a10 + 0x60);
                u8* pV = (u8*)((s1 * 5 >> 2) + dst);
                u8* pY = (u8*)(s1 + dst);
                int stride = m_a10 + 0x60;
                u8* s = (u8*)opt->mFrameIndex;
                for (int i = 0; i < h + 0x60; i++) {
                    util_Copy16((u8*)dst, s, stride);
                    s += stride;
                    dst += m_a10 + 0x60;
                }
                u8* t = (u8*)((h + 0x60) * (w + 0x60) + opt->mFrameIndex);
                int sc = (w >> 1) + 0x30;
                int dc = ((unsigned int)m_a10 >> 1) + 0x30;
                for (int i = 0; i < ((h + 0x60) >> 1); i++) {
                    util_Copy16(pY, t, sc);
                    pY += dc;
                    t += sc;
                }
                u8* t2 = (u8*)((((h + 0x60) * (w + 0x60) * 5) >> 2) + opt->mFrameIndex);
                for (int i = 0; i < ((h + 0x60) >> 1); i++) {
                    util_Copy16(pV, t2, sc);
                    pV += dc;
                    t2 += sc;
                }
                if (idx == 1)
                    opt->mOut10 = (h * w * 3) >> 1;
                else {
                    opt->mOut10 = h * w;
                    opt->mSize14 = (h * w) >> 2;
                    opt->mSize18 = opt->mSize14;
                }
            }
        } else {
            int dstV = opt->mFrameIndex;
            int dstY = opt->mFrameIndex;
            u8* pV = (u8*)opt->mFrameIndex;
            u8* pY = (u8*)opt->mFrameIndex;
            (void)dstV; (void)dstY;
            int stride = m_a10 + 0x60;
            u8* s = (u8*)opt->mFrameIndex;
            int rows = h + 0x60;
            int i = 0;
            while (i < rows) {
                util_Copy16((u8*)dstY, s, stride);
                s += stride;
                dstY += m_a10 + 0x60;
                i++;
            }
            u8* t = (u8*)((h + 0x60) * (w + 0x60) + opt->mFrameIndex);
            int sc = (w >> 1) + 0x30;
            int dc = ((unsigned int)m_a10 >> 1) + 0x30;
            for (int k = 0; k < (rows >> 1); k++) {
                util_Copy16(pY, t, sc);
                pY += dc;
                t += sc;
            }
            u8* t2 = (u8*)((((h + 0x60) * (w + 0x60) * 5) >> 2) + opt->mFrameIndex);
            for (int k = 0; k < (rows >> 1); k++) {
                util_Copy16(pV, t2, sc);
                pV += dc;
                t2 += sc;
            }
            opt->mOut10 = h * w;
            opt->mSize14 = (h * w) >> 2;
            opt->mSize18 = opt->mSize14;
        }
        opt->mSize28 = w;
        opt->mSize30 = 1;
    }
    opt->mSize2c = h;
    opt->mFrameIndex = mCount;
    opt->mFlag51 = 1;
    mCount++;
    cw_ctl(oldCw, 0xfffff);
    opt->mIsKeyFrame = 1;
}

// =========================================================================
// FUN_00fcd940  -- vp6 substructure ctor
// =========================================================================
// @ 0x00fcd940
void Vp6Ext::Ctor940(int p2)
{
    int self = (int)this;
    *(int*)(self + 0x00) = 0x1491fd8;
    *(int*)(self + 0x04) = 0;
    *(int*)(self + 0x08) = 0;
    *(int*)(self + 0x0c) = 0;
    *(int*)(self + 0x10) = 0;
    *(int*)(self + 0x14) = 0;
    *(int*)(self + 0x1c) = 0;
    if (p2 == 0 || p2 == 1)
        *(int*)(self + 0x1c) = p2;
}

// =========================================================================
// FUN_00fcd970 / 9a0 / 9e0 / a10  -- bitstream source vtable helpers
// =========================================================================
// @ 0x00fcd970
extern "C" void FUN_00fcd970(int self)
{
    int* p = *(int**)(self + 0x14);
    int v = ((int (*)(int, int, int))**(void***)(self + 4))(self, 1, 0x1000);
    p[7] = v;
    p[0] = v;
    p[1] = 0x1000;
}

// @ 0x00fcd9a0
extern "C" int FUN_00fcd9a0(int self)
{
    int* p = *(int**)(self + 0x14);
    if (p[5] != 0)
        ((void (*)(int, int, int))p[5])(p[7], 0x1000, p[6]);
    p[0] = p[7];
    p[1] = 0x1000;
    return 1;
}

// @ 0x00fcd9e0
extern "C" void FUN_00fcd9e0(int self)
{
    int* p = *(int**)(self + 0x14);
    int n = 0x1000 - p[1];
    if (n != 0 && p[5] != 0)
        ((void (*)(int, int, int))p[5])(p[7], n, p[6]);
}

// @ 0x00fcda10
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

// =========================================================================
// rw::movie::VideoEncoder_Jpeg
// =========================================================================
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

// =========================================================================
// FUN_00fcdb20  -- pixel format conversion dispatcher
// =========================================================================
extern "C" void DoInsertValue(void* dst, void* src, int count);   // 0x11e0744

// @ 0x00fcdb20
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

// =========================================================================
// VideoEncoder_Jpeg setters/getters
// =========================================================================
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
    if (v > 10000) {
        if (mEncodingErrorCallback != 0)
            mEncodingErrorCallback(
                "VideoEncoder_Jpeg: Quality must be between 0 and 10000.",
                mEncodingErrorCallbackData);
        v = 10000;
    }
    mQuality = v;
}

extern "C" int  jpeg_std_error(void*);              // 0x85f190
extern "C" void jpeg_create_compress_170(void*, int, int); // 0x8502a0
extern "C" void jpeg_set_defaults(void*);           // 0x855a30
extern "C" void jpeg_set_quality(void*, int, int);  // 0x8550e0
extern "C" void jpeg_start_compress(void*, int);    // 0x850570
extern "C" void jpeg_write_scanlines(void*, void*, int); // 0x8505f0
extern "C" void jpeg_finish_compress(void*);        // 0x8503f0
extern "C" void jpeg_destroy(void*);                // 0x850370
extern "C" void FUN_00fcdc10();                     // 0xfcdc10

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
    u8 cinfo[0x1f4];
    int* ci = (int*)cinfo;
    ci[0] = jpeg_std_error(cinfo + 0x174);
    jpeg_create_compress_170(cinfo, 0x3d, 0x170);
    FUN_00fcda10((int)cinfo, (int)&FUN_00fcdc10, (int)this);
    *(int*)(cinfo + 0x34) = fi[1];
    *(int*)(cinfo + 0x38) = fi[2];
    *(int*)(cinfo + 0x3c) = 3;
    *(int*)(cinfo + 0x40) = 2;
    jpeg_set_defaults(cinfo);
    jpeg_set_quality(cinfo, mQuality / 100, 1);
    *(int*)(cinfo + 0x168) = 0;
    mEncodeBufferPos = 0;
    jpeg_start_compress(cinfo, 1);
    u8* line = (u8*)((void* (__thiscall*)(ICoreAllocator*, unsigned int, const char*, int))
                     ((void**)mAllocator->m_vtbl)[2])(mAllocator, *(int*)(cinfo + 0x34) * 3,
                                                      "JPEG Line Buffer", 0);
    if (line != 0) {
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

// =========================================================================
// FUN_00fcde80  -- VideoEncoder_Jpeg ctor
// =========================================================================
// @ 0x00fcde80
void Vp6Ext::CtorDE80()
{
    int self = (int)this;
    *(int*)(self + 0x00) = 0x1492140;
    *(int*)(self + 0x04) = 0;
    *(int*)(self + 0x08) = 0;
    *(int*)(self + 0x0c) = 0;
    *(int*)(self + 0x18) = 0;
    *(int*)(self + 0x1c) = 0;
    *(int*)(self + 0x20) = 0;
    *(int*)(self + 0x24) = 0;
    *(int*)(self + 0x28) = 0;
    *(int*)(self + 0x2c) = 0;
    *(int*)(self + 0x30) = 0;
    *(int*)(self + 0x34) = 0;
    *(int*)(self + 0x38) = 0;
}

// =========================================================================
// rw::movie::VideoRenderable::VideoRenderable
// =========================================================================
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

// =========================================================================
// rw::movie::VideoRenderable::GetDataBufSizes
// =========================================================================
// @ 0x00fcdf40
void rw_movie_VideoRenderable_GetDataBufSizes(int w, int h, int format,
                                              int flag, unsigned int* out)
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

// =========================================================================
// FUN_00fcdfe0  -- VideoRenderable compare-by-frameNumber
// =========================================================================
// @ 0x00fcdfe0
extern "C" int __stdcall FUN_00fcdfe0(int* a, int* b)
{
    int vb = *(int*)(*b + 0x34);
    int va = *(int*)(*a + 0x34);
    if (va == vb)
        return 0;
    return (va > vb) ? 1 : -1;
}

// =========================================================================
// FUN_00fce010  -- VideoRenderable shutdown / release children
// =========================================================================
extern "C" void EA_Thread_Mutex_dtor(void*);   // 0x922130

struct EAThreadMutex {
    void  Lock(const char* name);
    void  Unlock();
};

struct RVRenderable {
    void ShutdownAll();
    void SetFrame0(int p2);
    int  GetFrame0();
    void SetFrame1(int p2);
    int  GetFrame1(int p2);
    int  GetFrame2();
};

// @ 0x00fce010
void RVRenderable::ShutdownAll()
{
    char* self = (char*)this;
    ((void (*)(void*))((void**)*(void**)(self + 0x0c))[0x88 / 4])(0);
    ((void (*)(int, int))((void**)*(void**)(self + 0x00))[3])(*(int*)(self + 0x0c), 0);
    ((void (*)(void*))((void**)*(void**)(self + 0x10))[0x88 / 4])(0);
    ((void (*)(int, int))((void**)*(void**)(self + 0x00))[3])(*(int*)(self + 0x10), 0);
    ((void (*)(void*))((void**)*(void**)(self + 0x08))[0x88 / 4])(0);
    ((void (*)(int, int))((void**)*(void**)(self + 0x00))[3])(*(int*)(self + 0x08), 0);
    ((void (*)(void*))((void**)*(void**)(self + 0x04))[0x88 / 4])(0);
    ((void (*)(int, int))((void**)*(void**)(self + 0x00))[3])(*(int*)(self + 0x04), 0);
    *(int*)(self + 0x48) = 0x14613b8;
    EA_Thread_Mutex_dtor((void*)(self + 0x18));
}

// =========================================================================
// Mutex-guarded accessors
// =========================================================================
extern "C" void EA_Thread_Mutex_Lock(void*, void*);    // 0x9221b0
extern "C" void EA_Thread_Mutex_Unlock(void*);         // 0x922270
extern const char g_mutexName[];                        // 0x149219c

// @ 0x00fce0a0
void RVRenderable::SetFrame0(int p2)
{
    EAThreadMutex* mtx = (EAThreadMutex*)((char*)this + 0x18);
    mtx->Lock(g_mutexName);
    int local = p2;
    ((void (*)(int*, int))((void**)*(void**)((char*)this + 0x04))[0x44 / 4])(&local, 0);
    mtx->Unlock();
}

// @ 0x00fce0e0
int RVRenderable::GetFrame0()
{
    EAThreadMutex* mtx = (EAThreadMutex*)((char*)this + 0x18);
    mtx->Lock(g_mutexName);
    int r = ((int (*)(void))((void**)*(void**)((char*)this + 0x04))[0x3c / 4])();
    mtx->Unlock();
    return r;
}

// @ 0x00fce110
void RVRenderable::SetFrame1(int p2)
{
    EAThreadMutex* mtx = (EAThreadMutex*)((char*)this + 0x18);
    mtx->Lock(g_mutexName);
    int local = p2;
    ((void (*)(int*, char*, int))((void**)*(void**)((char*)this + 0x08))[0x68 / 4])(&local, (char*)this + 0x48, 0);
    mtx->Unlock();
}

// @ 0x00fce150
int RVRenderable::GetFrame1(int p2)
{
    EAThreadMutex* mtx = (EAThreadMutex*)((char*)this + 0x18);
    mtx->Lock(g_mutexName);
    unsigned int n = ((unsigned int (*)(void))((void**)*(void**)((char*)this + 0x08))[0x3c / 4])();
    if (n <= (unsigned int)p2) {
        mtx->Unlock();
        return 0;
    }
    void* p = (void*)((void* (*)(int))((void**)*(void**)((char*)this + 0x08))[0x30 / 4])(p2);
    int* q = (int*)((int (*)(void*))((void**)p)[0])(p);
    int r = *q;
    mtx->Unlock();
    return r;
}

// @ 0x00fce1b0
int RVRenderable::GetFrame2()
{
    EAThreadMutex* mtx = (EAThreadMutex*)((char*)this + 0x18);
    mtx->Lock(g_mutexName);
    int r = ((int (*)(void))((void**)*(void**)((char*)this + 0x08))[0x3c / 4])();
    mtx->Unlock();
    return r;
}
