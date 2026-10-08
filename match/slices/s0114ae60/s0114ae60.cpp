// Slice s0114ae60: 0x0114B110 (cdecl, 2 stack args, plain ret, 2239 bytes)
//
// Per-block driver of a crossfading multi-channel sample re-buffer (audio library code, statically
// linked; SSE-compiled like the MP3 decoder next to it).
//   a = the stream/crossfader object, b = a block context holding two planar output buffers
//   (swapped at the end) and the number of samples ready in the current one.
// For every block it first splits the incoming `count` samples into n1 (up to the period at +0x4c)
// and n2 (the rest), hands them to the per-channel feeders (0x0114aa40), then, per channel and
// depending on the state at +0x6c (1 = crossfade-in by a search offset, 2 = linear crossfade of the
// first <=16 samples, other = plain copy), appends the new samples to the channel's ring buffer,
// and finally copies the common available amount to the output buffer and advances all counters.
// Helper names are descriptive (the callees are not decompiled yet).
#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);           // 0x011e0744 (static thunk)
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

struct Channel {                    // 0x1c bytes
    float xfade;                    // +0x00 residual fade phase
    float* src[2];                  // +0x04 the two input block pointers of this channel
    float* ring;                    // +0x0c ring buffer base
    int offsetResult;               // +0x10 (result of Search)
    int count;                      // +0x14 samples buffered
    int offset;                     // +0x18 read offset in ring
};

struct OutBuf {
    uint32_t pad00;
    float* data;                    // +0x04
    uint32_t pad08[1];
    uint16_t pad0c;
    uint16_t stride;                // +0x0e floats per channel
};

struct Owner {
    uint32_t pad[10];
    float total;                    // +0x28
};

struct BlockCtx {
    char pad00[0x3000c];
    OutBuf* cur;                    // +0x3000c
    OutBuf* prev;                   // +0x30010
    uint32_t pad30014[3];
    int count;                      // +0x30020
};

class cCrossfader {
public:
    void Feed(float** src, float** dst, int n1, int n2, int pos, float* out, bool first);   // 0x0114aa40 (ret 0x1c)
    int Search(float* a, float* b);                                                         // 0x0114ae60 (ret 8)
    int Prepare(Channel* ch);                                                               // 0x0114a680 (ret 4)
    void Blend(float* a, float* b, float* ring, Channel* ch, int offset);                   // 0x0114a750 (ret 0x14)

    uint32_t pad00[2];
    Owner* mpOwner;                 // +0x08
    uint32_t pad0c;
    uint32_t pad10;
    float mTime;                    // +0x14
    float mPrevTime;                // +0x18
    uint32_t pad1c[3];
    float* mpSrc[2];                // +0x28
    uint32_t pad30[4];
    int mMode;                      // +0x40
    float mFade;                    // +0x44
    uint32_t pad48;
    int mPeriod;                    // +0x4c
    uint32_t pad50[2];
    uint32_t mChannels;             // +0x58
    int mPos;                       // +0x5c
    int mLimit;                     // +0x60
    uint32_t pad64;
    int mMaxOut;                    // +0x68
    int mState;                     // +0x6c
    uint32_t pad70[3];
    uint8_t mFlip;                  // +0x7c
    uint8_t pad7d;
    uint16_t mChanOffset;           // +0x7e
};

int MixerProcess(cCrossfader* a, BlockCtx* b)
{
    int n1 = 0;
    int n2 = 0;
    int total = 0;
    int moved = 0;
    int take = 0;
    int minCount = 0;
    int space = 0;
    int offsetResult = 0;
    bool fedFirst = false;
    float* srcIn[2];
    float* srcCh[2];

    if (a->mState == 0)
        return 1;

    unsigned other = a->mFlip ^ 1;
    int count = b->count;
    OutBuf* bufCur = b->cur;
    OutBuf* bufPrev = b->prev;
    Channel* chans = (Channel*)((char*)a + a->mChanOffset);
    bool lt = a->mMaxOut < a->mLimit;
    int pos = a->mPos;
    bool ready = (a->mState == 1) ? (count + pos >= a->mPeriod * 2) : true;
    bool full = lt && ready;

    if (a->mMode == 1) {
        if (!full && count <= 0)
            goto skip;
        srcIn[0] = a->mpSrc[0];
        srcIn[1] = a->mpSrc[1];
    }
    if (count > 0) {
        if (pos < a->mPeriod) {
            n1 = a->mPeriod - pos;
            if (count < n1)
                n1 = count;
        }
        else {
            n1 = 0;
        }
        n2 = count - n1;
        a->mPos = pos + count;
        if (a->mMode == 1) {
            for (int c = 0; c < (int)a->mChannels; c++) {
                srcCh[0] = chans[c].src[0];
                srcCh[1] = chans[c].src[1];
                a->Feed(srcCh, srcIn, n1, n2, pos, bufCur->data + bufCur->stride * c, c == 0);
            }
            fedFirst = true;
        }
    }
skip:
    if (a->mMode == 1 && full && a->mState == 1) {
        chans[0].offsetResult = a->Search(srcIn[a->mFlip], srcIn[other]);
        offsetResult = a->Prepare(&chans[0]);
    }

    for (unsigned c = 0; c < a->mChannels; c++) {
        Channel* cp = &chans[c];
        float* ring = cp->ring;
        if (full || count > 0) {
            srcCh[0] = cp->src[0];
            srcCh[1] = cp->src[1];
            if (!fedFirst && count > 0)
                a->Feed(srcCh, 0, n1, n2, pos, bufCur->data + bufCur->stride * c, c == 0);
            if (full) {
                if (a->mState == 1) {
                    total = (a->mFade < 1.0f) ? a->mPeriod * 2 : a->mPeriod;
                    if (a->mMode == 0) {
                        int v = a->Search(srcCh[a->mFlip], srcCh[other]);
                        cp->offsetResult = v;
                        offsetResult = v;
                        float f = a->mFade;
                        if (f < 1.0f) {
                            float x = (float)(a->mPeriod * 2) * (1.0f - f) + cp->xfade;
                            if (fabs(x - (float)v) <= fabs(x)) {
                                offsetResult = -v;
                                cp->xfade = x - (float)v;
                            }
                            else {
                                offsetResult = 0;
                                cp->xfade = x;
                            }
                        }
                        else {
                            float x = (1.0f - f) * (float)a->mPeriod + cp->xfade;
                            float y = (float)v + x;
                            if (fabs(y) <= fabs(x)) {
                                cp->xfade = y;
                            }
                            else {
                                cp->xfade = x;
                                offsetResult = 0;
                            }
                        }
                    }
                    if (a->mState == 1) {
                        take = cp->count;
                        if (a->mMaxOut <= take)
                            take = a->mMaxOut;
                        memcpy(bufPrev->data + bufPrev->stride * c, ring + cp->offset, take * 4);
                        cp->count -= take;
                        if (cp->count <= 0)
                            cp->offset = 0;
                        else
                            cp->offset += take;
                        if (cp->count > 0) {
                            memmove(ring, ring + cp->offset, cp->count * 4);
                            cp->offset = 0;
                        }
                        a->Blend(srcCh[a->mFlip], srcCh[other], ring, cp, offsetResult);
                        goto next;
                    }
                }
                if (a->mState == 2) {
                    if (cp->count > 0) {
                        memmove(ring, ring + cp->offset, cp->count * 4);
                        cp->offset = 0;
                    }
                    if (c == 0) {
                        total = a->mPos;
                        if (total > a->mPeriod) {
                            n1 = a->mPeriod;
                            n2 = total - a->mPeriod;
                        }
                        else {
                            n1 = total;
                            n2 = 0;
                        }
                    }
                    float* copySrc;
                    int copyLen;
                    if (cp->count == a->mMaxOut) {
                        copySrc = srcCh[a->mFlip];
                        copyLen = n1;
                        goto copyTail;
                    }
                    else {
                        int d = cp->count - a->mMaxOut;
                        int p = d;
                        if (d >= 16)
                            p = 16;
                        if (n1 < p)
                            p = n1;
                        float* dst = ring + a->mMaxOut;
                        float* src = srcCh[a->mFlip];
                        float step = -1.0f / (float)p;
                        float w = 1.0f;
                        for (int i = 0; i < p; i++) {
                            dst[i] = (1.0f - w) * src[i] + w * dst[i];
                            w += step;
                        }
                        cp->count = a->mMaxOut + p;
                        copyLen = n1 - p;
                        if (copyLen > 0) {
                            copySrc = srcCh[a->mFlip] + p;
                        copyTail:
                            memcpy(ring + cp->count, copySrc, copyLen * 4);
                            cp->count += copyLen;
                        }
                    }
                    if (n2 > 0) {
                        memcpy(ring + cp->count, srcCh[other], n2 * 4);
                        cp->count += n2;
                    }
                    if (c >= a->mChannels - 1)
                        a->mState = 3;
                }
                else {
                    take = cp->count;
                    if (a->mMaxOut <= take)
                        take = a->mMaxOut;
                    memcpy(bufPrev->data + bufPrev->stride * c, ring + cp->offset, take * 4);
                    cp->count -= take;
                    if (cp->count <= 0)
                        cp->offset = 0;
                    else
                        cp->offset += take;
                    if (cp->count > 0) {
                        memmove(ring, ring + cp->offset, cp->count * 4);
                        cp->offset = 0;
                    }
                    if (c == 0) {
                        total = a->mPos;
                        if (total > a->mPeriod) {
                            n1 = a->mPeriod;
                            n2 = total - a->mPeriod;
                        }
                        else {
                            n1 = total;
                            n2 = 0;
                        }
                    }
                    memcpy(ring + cp->count, srcCh[a->mFlip], n1 * 4);
                    cp->count += n1;
                    if (n2 > 0) {
                        memcpy(ring + cp->count, srcCh[other], n2 * 4);
                        cp->count += n2;
                    }
                }
            }
        }
    next:
        if (c == 0) {
            minCount = chans[0].count;
            space = a->mLimit - take;
        }
        else if (cp->count < minCount) {
            minCount = cp->count;
        }
        int m = space;
        if (minCount < space)
            m = minCount;
        moved = m;
        memcpy(bufPrev->data + (bufPrev->stride * c + take), ring + cp->offset, m * 4);
    }

    for (unsigned c = 0; c < a->mChannels; c++) {
        chans[c].count -= moved;
        if (chans[c].count <= 0)
            chans[c].offset = 0;
        else
            chans[c].offset += moved;
    }
    a->mPos -= moved;
    if (moved == a->mPeriod)
        a->mFlip ^= 1;
    if (a->mState == 3 && a->mPos <= 0 && chans[0].count <= 0)
        a->mState = 0;

    OutBuf* t = b->prev;
    b->prev = b->cur;
    b->cur = t;
    b->count = take + moved;
    float f = (float)(a->mPos * 2);
    a->mTime = f;
    a->mpOwner->total = (f - a->mPrevTime) + a->mpOwner->total;
    a->mPrevTime = f;
    return 1;
}
