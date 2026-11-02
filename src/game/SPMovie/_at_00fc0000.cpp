// src/game/SPMovie/_at_00fc0000.cpp -- migrated from slice(s) s00fcfe60, s00fcf130, s00fce1e0, s00fcd210, s00fc8450 by tools/migrate/rewrite.py
// Object file: SPMovie/_at_00fc0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/Thread/Mutex.h"
#include <new>
#include <intrin.h>
#include <string.h>
#include <emmintrin.h>

// ---- items of slice s00fc8450 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace movie {
struct IRefCounted {
    virtual void Destroy(int flags);                                // +0x00
};
}
}
namespace rw {
namespace movie {
struct ChunkTracker {
    IRefCounted* mpRef;                         // +0x00  only counted once
    unsigned int mLimit;                        // +0x04
    unsigned int mTotal;                        // +0x08
};
}
}
// ---- items of slice s00fc8450 end

// ---- items of slice s00fcd210 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int         vp6_decode_frame(int, int, int, int, int); // 0xfd6bf0
extern "C" int         vp6_get_info(int, void*);            // 0xfd6a50
extern "C" void sub_00fd2970(void*);   // 0xfd2970
extern "C" void sub_00fd5fa0(void);    // 0xfd5fa0
extern "C" void sub_00fd69c0(void*, int, int); // 0xfd69c0
extern "C" void sub_00fd6c10(void*);   // 0xfd6c10
typedef unsigned char  u8;
struct DecodeOptions;
static unsigned int cw_ctl(unsigned int newv, unsigned int mask)
{
    return ((unsigned int (__cdecl*)(unsigned int, unsigned int))0x13cc384)(newv, mask);
}
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
struct StreamChunk {
    char   m_pad00[0x04];
    int    mSize;    // +0x04
    int    mData;    // +0x08
};
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
extern "C" void        util_Copy16(u8*, u8*, int);          // 0x11ea910
struct Vp6Ext {
    void Ctor3c0();
    void Ctor940(int p2);
    void CtorDE80();
    void Ctor3E0(int p2, int p3, int p4);
};
struct ILayoutElem {
    void SetSerializer();
};
struct Vp6Stream43 {
    void Method430();
};
// ---- items of slice s00fcd210 end

// ---- items of slice s00fce1e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
struct BitState {
    u32 pad00;      // +0x00
    u32 range;      // +0x04
    u32 value;      // +0x08
    int bits;       // +0x0c
    int pos;        // +0x10
    u8* buf;        // +0x14
};
struct BitCache {
    int count;      // +0x00
    u32 cache;      // +0x04
    const u8* p;    // +0x08
};
extern u32 g_bitMask[];    // 0x14923e8
// ---- items of slice s00fce1e0 end

// ---- items of slice s00fcf130 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  FUN_00fcef00(int reader, int bit);          // 0xfcef00  get bit
extern "C" int  FUN_00fcef80(int reader);                    // 0xfcef80  get bit
extern "C" int  DAT_014921f0[];      // Huffman symbol value table
extern "C" int  DAT_01492220[];      // sf-band group base table
extern "C" int  DAT_014923a8[];      // sf-band type table (byte view in places)
extern "C" int  DAT_01492cc8[];      // sample-format flags
typedef unsigned char byte;
struct BitReaderA {
    int    m_00;
    unsigned m_04;
    unsigned m_08;
    int    m_0c;
    int    m_10;
    byte*  m_14;
};
struct BitReader {
    int    m_00;
    unsigned m_04;
    byte*  m_08;
};
extern "C" int  FUN_00fcf080(BitReader* r, int n);           // 0xfcf080  get n bits
extern "C" int  FUN_00fcf0e0(BitReader* r);                  // 0xfcf0e0  get 1 bit
extern "C" byte FUN_00fd36c0(int p, short* dst, int flag,
                             byte* a4, byte* a5);            // 0xfd36c0  plain PCM
extern "C" byte DAT_014931f0[];      // sf-band -> pcm format table
extern "C" void (*DAT_016d9580)(int, int, int, int, int, int, int);
extern "C" void (*DAT_016d9584)(int, int, int, int, int);
extern "C" void (*DAT_016d9684)(int, int, int);
extern "C" void (*DAT_016d968c)(int, int, int, int);
extern "C" void (*DAT_016d9690)(int, int, int, int);
extern "C" void (*DAT_016d95ac)(int, int, int);
extern "C" void (*DAT_016d958c)(int, int, int);
extern "C" void (*DAT_016d941c)(int, int, int);
// ---- items of slice s00fcf130 end

// ---- items of slice s00fcfe60 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short u16;
typedef short          s16;
struct Vp6Ctx
{
    u32  pad00[2];              // +0x00
    u8*  mRowDest;              // +0x08  destination row used by the block writers
    u8*  mRowSrcA;              // +0x0c  first source row (0x84/0x94/0xa4/0xb4)
    u8*  mRowSrcB;              // +0x10  second source row (0xdc/0xe4/0xec)
    u32  mLastToken;            // +0x14
    u32  mFiltA;                // +0x18
    u32  mFiltB;                // +0x1c
    u32  mFiltC;                // +0x20
    u32  mFiltD;                // +0x24
    u32  mPredA;                // +0x28
    u32  mPredB;                // +0x2c
    u16  mEdges30[8];           // +0x30 (2 shorts per slot, 4 slots)
    u16  mEdge3c[2];            // +0x3c
    u16  mEdge40[2];            // +0x40
    u16  mEdge44[2];            // +0x44
    u16  mEdge48[2];            // +0x48
    u16  mEdge4c[2];            // +0x4c
    u16  mEdge54[2];            // +0x54
    u16  mEdge58[2];            // +0x58
    u32  pad5c[(0x60 - 0x5c) / 4];   // +0x5c
    u32  mStride60;             // +0x60
    u32  pad64;                 // +0x64
    u32  mRowOff68;             // +0x68
    u32  mStride6c;             // +0x6c
    u32  mFlags70;              // +0x70
    u32  mMvSize74;             // +0x74
    u32  mMvSize78;             // +0x78
    u32  mFiltIndex7c;          // +0x7c
    u32  mCurFilter80;          // +0x80 (pointer value, compared to 0)
    u32  pad84[(0xc4 - 0x84) / 4];   // +0x84 .. +0xc3 (four 16-byte predictor rows)
    u32  mPredBaseC4;           // +0xc4
    u32  padc8[(0x158 - 0xc8) / 4];  // +0xc8
    u32  mWidth158;             // +0x158
    u32  mWidth15c;             // +0x15c
    u32  mSpans160;             // +0x160
    u32  pad164[(0x194 - 0x164) / 4];// +0x164
    u32  mUOff194;              // +0x194
    u32  mVOff198;              // +0x198
    u32  mPrevOff19c;           // +0x19c
    u32  mTokens1a0;            // +0x1a0
    u32  pad1a4[2];             // +0x1a4
    u32  mStride1ac;            // +0x1ac
    u32  pad1b0[(0x330 - 0x1b0) / 4];// +0x1b0
    u8   mQuant330;             // +0x330
    u8   pad331[(0x350 - 0x331)];
    u32  mCoeff350;             // +0x350
    u32  mRows358;              // +0x358
    u8   pad35c[(0x3b62 - 0x35c)];
    u8   mDecode3b62;           // +0x3b62
};
u32 FUN_00fcf600(Vp6Ctx* c);
u32 FUN_00fcf660(Vp6Ctx* c, u32 prev, u32 tok);
void FUN_00fcf770(Vp6Ctx* c, void* out, int n);
void FUN_00fcf9a0(Vp6Ctx* c, int plane, u32 x, int n, void* out);
// ---- items of slice s00fcfe60 end

// @ 0x00fc85b0
namespace rw { namespace movie {
int ValidateChunk(const int* header, unsigned int size, unsigned int type, ChunkTracker* tracker, bool (*callback)(const int*, void*), void* context, unsigned int* outLength)
{
    if (size < 8)
        return 0;
    if (callback != 0 && !callback(header, context))
        return 0;
    unsigned int length = (unsigned int)header[1];
    if (size < length)
        return 0;
    *outLength = length;
    if (tracker != 0) {
        tracker->mTotal += length;
        if (tracker->mTotal >= tracker->mLimit)
            return 2;
        if (tracker->mpRef != 0 && *header == *(const int*)tracker->mpRef)
            return 2;
    }
    return 1;
}
}}  // namespace rw::movie

// @ 0x00fc8640
namespace rw { namespace movie {
bool IsSCChunk(const char* data)
{
    if (data[0] == 'S' && data[1] == 'C')
        return true;
    return false;
}
}}  // namespace rw::movie

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

// @ 0x00fcd430
void Vp6Stream43::Method430()
{
    sub_00fd6c10((void*)((char*)this + 0x18));
    ((ILayoutElem*)((char*)this + 0x18))->SetSerializer();
}

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

// @ 0x00fcef00
int DecodeBit(BitState* s, int prob)
{
    u32 range = s->range;
    u32 low = ((range - 1) * (u32)prob >> 8) + 1;
    int bits = s->bits;
    u32 value = s->value;
    u32 cmp = low << 24;
    int high = 0;
    if (value >= cmp) {
        low = range - low;
        value -= cmp;
        high = 1;
    }
    if (low < 0x80) {
        do {
            low += low;
            value += value;
            if (--bits == 0) {
                value |= s->buf[s->pos];
                bits = 8;
                s->pos++;
            }
        } while (low < 0x80);
        s->bits = bits;
    }
    s->value = value;
    s->range = low;
    return high;
}

// @ 0x00fcef80
int DecodeBitProb(BitState* s)
{
    u32 range = s->range;
    u32 value = s->value;
    int bits = s->bits;
    u32 half = (range + 1) >> 1;
    int high;
    if (value >= (half << 24)) {
        value -= half << 24;
        range -= half;
        high = 1;
    } else {
        range = half;
        high = 0;
    }
    range += range;
    value += value;
    if (--bits == 0) {
        value |= s->buf[s->pos];
        s->pos++;
        bits = 8;
    }
    s->range = range;
    s->bits = bits;
    s->value = value;
    return high;
}

// @ 0x00fcefe0
u32 ReadBits(BitState* s, int count)
{
    count--;
    u32 out = 0;
    if (count < 0)
        return 0;
    do {
        u32 range = s->range;
        u32 value = s->value;
        int bits = s->bits;
        u32 half = (range + 1) >> 1;
        u32 bit;
        if (value >= (half << 24)) {
            range -= half;
            value -= half << 24;
            bit = 1;
        } else {
            range = half;
            bit = 0;
        }
        range += range;
        value += value;
        if (--bits == 0) {
            value |= s->buf[s->pos];
            s->pos++;
            bits = 8;
        }
        s->bits = bits;
        out |= bit << count;
        s->range = range;
        s->value = value;
        count--;
    } while (count >= 0);
    return out;
}

// @ 0x00fcf080
u32 ReadCachedBits(BitCache* s, int count)
{
    u32 keep = g_bitMask[s->count];
    s->cache &= keep;
    int shift = count - s->count;
    u32 out = 0;
    if (shift > 0) {
        out = s->cache << shift;
        const u8* p = s->p;
        s->cache = ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | p[3];
        s->p = p + 4;
        shift -= 0x20;
    }
    s->count = -shift;
    return s->cache >> (-shift) | out;
}

// @ 0x00fcf0e0
u32 ReadCachedBit(BitCache* s)
{
    if (s->count != 0) {
        int n = --s->count;
        return (s->cache >> n) & 1;
    }
    const u8* p = s->p;
    s->cache = ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | p[3];
    s->p = p + 4;
    s->count = 0x1f;
    return s->cache >> 31;
}

// @ 0x00fcf130
bool FUN_00fcf130(BitReaderA* s, int n)
{
    unsigned range = s->m_04;
    unsigned value = s->m_08;
    int      bits  = s->m_0c;
    unsigned inc   = (((range - 1) * (unsigned)n) >> 8) + 1;
    bool     ok;

    if ((inc << 24) <= value) {
        range -= inc;
        value -= inc << 24;
        ok = true;
    }
    else {
        range = inc;
        ok = false;
    }

    while (range < 0x80) {
        range += range;
        value += value;
        if (--bits == 0) {
            value |= s->m_14[s->m_10];
            s->m_10 = s->m_10 + 1;
            bits = 8;
        }
    }

    s->m_04 = range;
    s->m_08 = value;
    s->m_0c = bits;
    return ok;
}

// @ 0x00fcf1b0
void FUN_00fcf1b0(int p, int band, int coeffs, int reader, int prev)
{
    byte  b  = ((byte*)DAT_014923a8)[*(int*)(p + 0x14)];
    int   acc = 0;
    int   hits = 0;

    if ((unsigned short)b == *(unsigned short*)(prev + 8)) {
        acc = *(short*)(prev + 0xa);
        hits = 1;
    }
    if ((unsigned short)b == *(unsigned short*)(reader + 8)) {
        acc += *(short*)(reader + 0xa);
        hits++;
    }

    short v;
    if (hits == 0)
        v = *(short*)(coeffs + b * 2);
    else if (hits == 2)
        v = (short)(((((unsigned)acc & 0xffff) >> 0xf) + (unsigned)acc) >> 1);
    else
        v = (short)acc;

    short* dst = (short*)(*(int*)(p + 4) + band * 0x80);
    *dst = (short)(*dst + v);
    *(short*)(coeffs + b * 2) = *dst;
}

// @ 0x00fcf230
int FUN_00fcf230(int table, BitReader* r, int groups)
{
    int      bits = r->m_00;
    unsigned idx  = ((1u << (bits & 0x1f)) - 1) & r->m_04;

    if (bits < 6)
        idx = ((unsigned)r->m_08[0] | (idx << 8)) >> ((bits + 2) & 0x1f);
    else
        idx = idx >> ((bits - 6) & 0x1f);

    r->m_00 -= (int)(*(unsigned short*)(table + idx * 2) >> 0xc);
    if (r->m_00 < 0) {
        byte* q = r->m_08;
        r->m_04 = ((unsigned)q[0] << 24) | ((unsigned)q[1] << 16) |
                  ((unsigned)q[2] << 8) | (unsigned)q[3];
        r->m_08 = q + 4;
        r->m_00 += 0x20;
    }

    unsigned code = *(unsigned short*)(table + idx * 2);
    if (code & 1)
        return (int)((code >> 1) & 0x1f);

    unsigned sel = code & 0x3e;
    unsigned bit;
    for (;;) {
        if (r->m_00 == 0) {
            byte* q = r->m_08;
            r->m_04 = ((unsigned)q[0] << 24) | ((unsigned)q[1] << 16) |
                      ((unsigned)q[2] << 8) | (unsigned)q[3];
            r->m_08 = q + 4;
            r->m_00 = 0x1f;
            bit = (unsigned)(q[0] >> 7);
        }
        else {
            int nb = r->m_00 - 1;
            r->m_00 = nb;
            bit = (r->m_04 >> nb) & 1;
        }
        sel = (sel >> 1) & 0x7f;
        sel = *(unsigned*)(groups + (bit != 0 ? 4 : 0) + sel * 0xc);
        if (sel & 1)
            break;
    }
    return (int)((sel >> 1) & 0x7f);
}

// @ 0x00fcf330
byte FUN_00fcf330(int p, short* out, int ch)
{
    BitReader* r = (BitReader*)(p + 0x13c);
    int* count = (int*)(p + 0x3790 + ch * 4);
    int  n = *count;
    byte ret;
    int  k = 0;

    if (n > 0) {
        *count = n - 1;
        ret = 0;
    }
    else {
        int base = p + 0x2390 + ch * 0x80;
        int tbl  = p + 0x368 + ch * 0x90;
        int i = FUN_00fcf230(base, r, tbl);

        if (i == 0xb)
            return *(byte*)(p + 0x268);

        if (i == 0) {
            int x = FUN_00fcf080(r, 2) + 1;
            if (x == 3) {
                *count = FUN_00fcf080(r, 1) + 2;
                ret = 0;
            }
            else {
                if (x == 4) {
                    if (FUN_00fcf0e0(r) != 0) {
                        *count = FUN_00fcf080(r, 6) + 10;
                        ret = 0;
                        goto next;
                    }
                    x = FUN_00fcf080(r, 2) + 7;
                }
                *count = x - 1;
                ret = 0;
            }
        }
        else {
            unsigned val = (unsigned)DAT_014921f0[i];
            if (i > 4) {
                int neb = (i > 9) ? 11 : i - 4;
                val += (unsigned)FUN_00fcf080(r, neb);
            }
            int sgn = FUN_00fcf0e0(r);
            *out = (short)((-sgn ^ (int)val) + sgn);
            ret = (val > 1) ? 2 : 1;
            k = ret;
        }
    }

next:
    {
        int* count2 = (int*)(p + 0x3798 + ch * 4);
        int  m = *count2;
        if (m > 0) {
            *count2 = m - 1;
            return *(byte*)(p + 0x268);
        }
    }

    int i = 1;
    for (;;) {
        int row = DAT_01492220[i] + 6 * (ch + k * 2);
        int v = FUN_00fcf230(p + 0x2490 + row * 0x80, r, p + 0x500 + row * 0x90);

        if (v == 0xb) {
            if (i != 1)
                return *(byte*)(p + 0x267 + i);
            int x = FUN_00fcf080(r, 2) + 1;
            if (x == 3)
                x = FUN_00fcf080(r, 2) + 3;
            else if (x == 4) {
                if (FUN_00fcf0e0(r) != 0)
                    x = FUN_00fcf080(r, 6) + 0xb;
                else
                    x = FUN_00fcf080(r, 2) + 7;
            }
            *(int*)(p + 0x3798 + ch * 4) = x - 1;
            return *(byte*)(p + 0x267 + i);
        }

        if (v == 0) {
            int g = (i >= 6) ? 1 : 0;
            int j = FUN_00fcf230(p + 0x3690 + g * 0x80, r, p + 0x21b0 + g * 0xa8);
            if (j < 8)
                k += j;
            else
                k += FUN_00fcf080(r, 6) + 8;
            ret = 0;
        }
        else {
            unsigned val = (unsigned)DAT_014921f0[v];
            if (v > 4) {
                int neb = (v > 9) ? 11 : v - 4;
                val += (unsigned)FUN_00fcf080(r, neb);
            }
            unsigned bit;
            if (r->m_00 != 0) {
                int nb = r->m_00 - 1;
                r->m_00 = nb;
                bit = (r->m_04 >> nb) & 1;
            }
            else {
                byte* q = r->m_08;
                r->m_04 = ((unsigned)q[0] << 24) | ((unsigned)q[1] << 16) |
                          ((unsigned)q[2] << 8) | (unsigned)q[3];
                r->m_08 = q + 4;
                r->m_00 = 0x1f;
                bit = (unsigned)(q[0] >> 7);
            }
            out[*(byte*)(p + 0x1e8 + i)] = (short)((-(int)bit ^ (int)val) + (int)bit);
            ret = (val > 1) ? 2 : 1;
        }

        i++;
        if (i >= 0x40)
            break;
    }
    return *(byte*)(p + 0x267 + i);
}

// @ 0x00fcf600
int FUN_00fcf600(int p)
{
    int a = FUN_00fcef80(p + 0x10c);
    int b = FUN_00fcef80(p + 0x10c);

    switch (b + a * 2) {
    case 1:  return 2;
    case 2:  return 3;
    case 3:  return 4;
    default: return 0;
    }
}

// @ 0x00fcf660
int FUN_00fcf660(int p, int gr, int ch)
{
    int   r = p + 0x10c;
    int   band = ch * 10 + gr;
    byte* q;

    if (FUN_00fcef00(r, *(byte*)(p + 0x3812 + band)) != 0)
        return gr;

    q = (byte*)(p + 0x383a + band * 9);
    if (FUN_00fcef00(r, q[0]) != 0) {
        if (FUN_00fcef00(r, q[2]) == 0) {
            if (FUN_00fcef00(r, q[5]) != 0)
                return 7;
            return 1;
        }
        if (FUN_00fcef00(r, q[6]) != 0)
            return FUN_00fcef00(r, q[8]) + 8;
        return FUN_00fcef00(r, q[7]) + 5;
    }

    if (FUN_00fcef00(r, q[1]) != 0)
        return FUN_00fcef00(r, q[4]) + 3;
    return FUN_00fcef00(r, q[3]) * 2;
}

// @ 0x00fcf770
void FUN_00fcf770(int p, short* out, int gr)
{
    int r  = p + 0x10c;
    int s0 = 0;
    int s1 = 0;

    if (gr == 2) {
        if (*(int*)(p + 0x50) < 2) {
            s0 = *(short*)(p + 0x48);
            s1 = *(short*)(p + 0x4a);
        }
    }
    else if (*(int*)(p + 0x5c) < 2) {
        s0 = *(short*)(p + 0x54);
        s1 = *(short*)(p + 0x56);
    }

    for (int i = 0; i < 2; i++) {
        int v;
        if (FUN_00fcef00(r, *(byte*)(p + 0x37a2 + i)) == 0) {
            int base = i * 7 + p;
            if (FUN_00fcef00(r, *(byte*)(base + 0x37a4)) == 0) {
                if (FUN_00fcef00(r, *(byte*)(p + (i + 0x7f3) * 7)) == 0) {
                    v = FUN_00fcef00(r, *(byte*)(base + 0x37a6));
                }
                else {
                    v = FUN_00fcef00(r, *(byte*)(base + 0x37a7)) + 2;
                }
            }
            else {
                if (FUN_00fcef00(r, *(byte*)(base + 0x37a8)) == 0) {
                    v = FUN_00fcef00(r, *(byte*)(base + 0x37a9)) + 4;
                }
                else {
                    v = FUN_00fcef00(r, *(byte*)(base + 0x37aa)) + 6;
                }
            }
        }
        else {
            int b = p + i * 8;
            v = FUN_00fcef00(r, *(byte*)(b + 0x37b2)) +
                FUN_00fcef00(r, *(byte*)(b + 0x37b3)) * 2 +
                FUN_00fcef00(r, *(byte*)(b + 0x37b4)) * 4;
            v += FUN_00fcef00(r, *(byte*)(b + 0x37b9)) * 0x80;
            v += FUN_00fcef00(r, *(byte*)(b + 0x37b8)) * 0x40;
            v += FUN_00fcef00(r, *(byte*)(b + 0x37b7)) * 0x20;
            v += FUN_00fcef00(r, *(byte*)(b + 0x37b6)) * 0x10;
            if (v & 0xf0)
                v += FUN_00fcef00(r, *(byte*)(b + 0x37b5)) * 8;
            else
                v += 8;
        }

        if (v != 0) {
            if (FUN_00fcef00(r, *(byte*)(p + 0x37a0 + i)) != 0)
                v = -v;
        }

        if (i == 0)
            out[0] = (short)(s0 + v);
        else
            out[1] = (short)(v + s1);
    }
}

// @ 0x00fcf9a0
void FUN_00fcf9a0(int p, int pos, int ch, byte sel, int* out)
{
    int idx = *(int*)(p + 0x1ac) * pos + ch;
    int found = 0;
    int flag = 1;
    int diffs = 0;
    int i;

    for (i = 0; i < 0xc; i++) {
        int j = *(int*)(p + 0x2e8 + i * 4) + idx;
        if (DAT_014923a8[*(char*)(*(int*)(p + 0x350) + j)] == (int)sel) {
            int t = *(int*)(*(int*)(p + 0x358) + j * 4);
            if (t != 0) {
                flag = 2;
                found = t;
                break;
            }
        }
    }

    for (i = i + 1; i < 0xc; i++) {
        int j = *(int*)(p + 0x2e8 + i * 4) + idx;
        if (DAT_014923a8[*(char*)(*(int*)(p + 0x350) + j)] == (int)sel) {
            int t = *(int*)(*(int*)(p + 0x358) + j * 4);
            if (t != found) {
                if (t != 0) {
                    flag = 0;
                    break;
                }
            }
        }
    }

    if (sel != 1) {
        *(int*)(p + 0x5c) = i;
        *(int*)(p + 0x54) = i;
        *(int*)(p + 0x58) = diffs;
    }
    else {
        *out = flag;
        *(int*)(p + 0x50) = i;
        *(int*)(p + 0x48) = i;
        *(int*)(p + 0x4c) = diffs;
    }
}

// @ 0x00fcfab0
void FUN_00fcfab0(int p, int dst, int ch)
{
    unsigned mask  = (unsigned)*(int*)(p + 0x78);
    int      shift = *(int*)(p + 0x74);
    int      step  = *(int*)(p + 0x7c);
    int      base;

    base = *(int*)(p + 0x1c4);
    if (DAT_014923a8[*(int*)(p + 0x14)] == 2)
        base = *(int*)(p + 0x1c0);

    int x = *(short*)(p + 0x30 + ch * 4);
    int y = *(short*)(p + 0x32 + ch * 4);
    unsigned xm = (unsigned)x & mask;
    unsigned ym = (unsigned)y & mask;

    base += ((((y >> 31) & (int)mask) + y) >> shift) * step;
    base += (((x >> 31) & (int)mask) + x) >> shift;
    base += *(int*)(p + 0x68);

    int diff = 0;
    if (xm != 0) {
        if (*(short*)(p + 0x30 + ch * 4) > 0)
            diff = 1;
        else
            diff = -1;
    }
    if (ym != 0) {
        if (*(short*)(p + 0x32 + ch * 4) > 0)
            diff += step;
        else
            diff -= step;
    }

    if (diff == 0) {
        (*DAT_016d941c)(base, dst, step);
        return;
    }

    if (ch < 4) {
        xm = xm * 2;
        ym = ym * 2;
    }
    (*DAT_016d9580)(base, diff + base, dst, step, (int)xm, (int)ym, 0);
}

// @ 0x00fcfbb0
void FUN_00fcfbb0(int p, int ch)
{
    int fmt = *(int*)(p + 0x14);

    if (fmt == 0) {
        (*DAT_016d9584)(*(int*)(p + 0x1dc),
                        *(int*)(p + 0x1bc) + *(int*)(p + 0x68),
                        *(int*)(p + 0x1c4) + *(int*)(p + 0x68),
                        *(int*)(p + 0x1cc), *(int*)(p + 0x6c));
        return;
    }

    if (DAT_01492cc8[fmt] != 0) {
        FUN_00fcfab0(p, *(int*)(p + 0x1dc), ch);
        (*DAT_016d968c)(*(int*)(p + 0x1dc), *(int*)(p + 0x1cc),
                        *(int*)(p + 0x1bc) + *(int*)(p + 0x68),
                        *(int*)(p + 0x6c));
        return;
    }

    if (fmt != 5) {
        (*DAT_016d9690)(*(int*)(p + 0x1dc),
                        *(int*)(p + 0x1bc) + *(int*)(p + 0x68),
                        *(int*)(p + 0x1cc), *(int*)(p + 0x6c));
        return;
    }

    (*DAT_016d9584)(*(int*)(p + 0x1dc),
                    *(int*)(p + 0x1bc) + *(int*)(p + 0x68),
                    *(int*)(p + 0x1c0) + *(int*)(p + 0x68),
                    *(int*)(p + 0x1cc), *(int*)(p + 0x6c));
}

// @ 0x00fcfc70
void FUN_00fcfc70(int p, int gr, int ch)
{
    int    off = gr * 0x80;
    int    band;
    byte   flags;
    int    fmt;

    if (*(int*)(p + 0x238c) == 0)
        flags = FUN_00fd36c0(p, (short*)(*(int*)(p + 4) + off),
                             *(int*)(p + 0x70) != 0,
                             (byte*)*(int*)(p + 8), (byte*)*(int*)(p + 0xc));
    else
        flags = FUN_00fcf330(p, (short*)(*(int*)(p + 4) + off),
                             *(int*)(p + 0x70) != 0);

    FUN_00fcf1b0(p, gr, *(int*)(p + 0x10), *(int*)(p + 8), *(int*)(p + 0xc));

    *(int*)(*(int*)(p + 0xc) + 4) = *(int*)(p + 0x18 + gr * 4);
    *(int*)(*(int*)(p + 8) + 4) = *(int*)(*(int*)(p + 0xc) + 4);
    *(short*)(*(int*)(p + 0xc) + 0xa) = *(short*)(off + *(int*)(p + 4));
    *(short*)(*(int*)(p + 8) + 0xa) = *(short*)(*(int*)(p + 0xc) + 0xa);
    *(short*)(*(int*)(p + 0xc) + 8) = *(unsigned short*)(&DAT_014923a8[*(int*)(p + 0x14)]);
    *(short*)(*(int*)(p + 8) + 8) = *(short*)(*(int*)(p + 0xc) + 8);

    fmt = DAT_014931f0[gr];
    if (flags < 3 && *(short*)(*(int*)(p + 4) + 2 + off) == 0) {
        (*DAT_016d958c)(*(int*)(p + 4) + off,
                        *(int*)(*(int*)(p + 0xf4) + 0x50 + fmt * 4),
                        *(int*)(p + 0x1cc));
        *(short*)(off + *(int*)(p + 4)) = 0;
        FUN_00fcfbb0(p, gr);
        return;
    }

    if (flags < 0xb) {
        int* d;
        (*DAT_016d95ac)(*(int*)(p + 4) + off,
                        *(int*)(*(int*)(p + 0xf4) + 0x50 + fmt * 4),
                        *(int*)(p + 0x1cc));
        d = (int*)(*(int*)(p + 4) + off);
        d[0] = 0;
        d[1] = 0;
        d[2] = 0;
        d[3] = 0;
        d[4] = 0;
        d[5] = 0;
        d[8] = 0;
        d[9] = 0;
        d[12] = 0;
        d[13] = 0;
        *(short*)(d + 16) = 0;
        FUN_00fcfbb0(p, gr);
        return;
    }

    (*DAT_016d9684)(*(int*)(p + 4) + off,
                    *(int*)(*(int*)(p + 0xf4) + 0x50 + fmt * 4),
                    *(int*)(p + 0x1cc));
    memset((void*)(*(int*)(p + 4) + off), 0, 0x80);
    FUN_00fcfbb0(p, gr);
}

// @ 0x00fcfe60
void FUN_00fcfe60(Vp6Ctx* c, int x, int y)
{
    u32 local;
    FUN_00fcf9a0(c, 0, (u32)x, 1, &local);
    u32 tok = FUN_00fcf660(c, c->mTokens1a0, local);
    c->mTokens1a0 = tok;
    ((u8*)(c->mCoeff350))[c->mStride1ac * x + y] = (u8)tok;
    c->mLastToken = tok;

    u16 v0 = 0, v1 = 0;
    if (tok != 7) {
        switch (tok) {
        case 2:  FUN_00fcf770(c, &local, 2); v0 = (u16)local; v1 = (u16)(local >> 16); break;
        case 3:  v0 = c->mEdge48[0]; v1 = c->mEdge48[1]; break;
        case 4:  v0 = c->mEdge4c[0]; v1 = c->mEdge4c[1]; break;
        case 6:  FUN_00fcf9a0(c, 0, (u32)x, 2, &local); FUN_00fcf770(c, &local, 6);
                 v0 = (u16)local; v1 = (u16)(local >> 16); break;
        case 8:  FUN_00fcf9a0(c, 0, (u32)x, 2, &local);
                 v0 = c->mEdge54[0]; v1 = c->mEdge54[1]; break;
        case 9:  FUN_00fcf9a0(c, 0, (u32)x, 2, &local);
                 v0 = c->mEdge58[0]; v1 = c->mEdge58[1]; break;
        default: v0 = 0; v1 = 0; break;
        }
        int slot = c->mStride1ac * x + y;
        u16* rows = (u16*)c->mRows358;
        rows[slot * 2 + 0] = v0;
        rows[slot * 2 + 1] = v1;
        for (int i = 0; i < 6; ++i) {
            c->mEdges30[i * 2 + 0] = v0;
            c->mEdges30[i * 2 + 1] = v1;
            ((u32*)&c->mEdges30[i * 2])[-0xd] = tok;
        }
        return;
    }

    c->mFiltA = FUN_00fcf600(c);
    c->mFiltB = FUN_00fcf600(c);
    c->mFiltC = FUN_00fcf600(c);
    c->mFiltD = FUN_00fcf600(c);
    c->mPredA = 7;
    c->mPredB = 7;

    int sumA = 0, sumB = 0;
    for (int i = 0; i < 4; ++i) {
        u32 f = (&c->mFiltA)[i];
        u16 a = 0, b = 0;
        if (f == 3) { a = c->mEdge48[0]; b = c->mEdge48[1]; sumA += (s16)a; sumB += (s16)b; }
        else if (f == 4) { a = c->mEdge4c[0]; b = c->mEdge4c[1]; sumA += (s16)a; sumB += (s16)b; }
        else if (f == 2) {
            u32 l; FUN_00fcf770(c, &l, 2);
            a = (u16)l; b = (u16)(l >> 16);
            sumA += (s16)a; sumB += (s16)b;
        }
        c->mEdges30[i * 2 + 0] = a;
        c->mEdges30[i * 2 + 1] = b;
    }

    int slot = c->mStride1ac * x + y;
    u16* rows = (u16*)c->mRows358;
    rows[slot * 2 + 0] = c->mEdge3c[0];
    rows[slot * 2 + 1] = c->mEdge3c[1];

    u16 r0 = (u16)(((sumA >> 31) + 1 + sumA) >> 2);
    u16 r1 = (u16)(((sumB >> 31) + 1 + sumB) >> 2);
    c->mEdge40[0] = r0;
    c->mEdge40[1] = r1;
    c->mEdge44[0] = r0;
    c->mEdge44[1] = r1;
}
