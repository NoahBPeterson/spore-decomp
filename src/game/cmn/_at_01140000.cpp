// src/game/cmn/_at_01140000.cpp -- migrated from slice(s) s0114da70, s0114cb60, s0113fc50 by tools/migrate/rewrite.py
// Object file: cmn/_at_01140000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <xmmintrin.h>
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern unsigned char g_16e7c1c;   // 0x16e7c1c
extern "C" __declspec(dllimport) double __cdecl ldexp(double, int);   // msvcr90

// ---- items of slice s0113fc50 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define A8(a)  (*(unsigned char*)(a))
#define A32(a) (*(unsigned int*)(a))
#define Ad(a)  (*(double*)(a))
extern unsigned char g_16e7c1c;   // 0x16e7c1c
extern "C" __declspec(dllimport) double __cdecl ldexp(double, int);   // msvcr90
void  __cdecl F_0113fec0(int);                          // 0x113fec0 (slice 16)
int   __cdecl Sub_1141150(int);                         // 0x1141150
int   __cdecl Sub_1156660(int, int*);                   // 0x1156660
void  __cdecl Sub_1142a20(int, int, float);             // 0x1142a20
void  __cdecl Sub_1156310(int, int);                    // 0x1156310
void  __cdecl Sub_1156b40(int, int, int);               // 0x1156b40 (MIX_filteradd)
void  __cdecl Sub_1142730(int);                         // 0x1142730
int   __cdecl Sub_1156800(void);                        // 0x1156800
#define D  (A32(0x16e7c78))
void FUN_01140930(int a, int val);
void SNDPLATFORM_highpass(int a, int val);
int  F_01140b20(int a, int val);
float F_01140190(unsigned char* p);
struct SndDecoder {
    char         pad0[0x04];
    unsigned char* src;    // +0x04
    short*       dst;      // +0x08
    int          count;    // +0x0c
    int          field10;  // +0x10
    short        chans;    // +0x14

    void SetState(short* p);            // 0x1140380
    void DecodeS16(int srcs, int n);    // 0x11402f0
    void DecodeRaw(int srcs, int n);    // 0x11403b0
    void DecodeSwap(int srcs, int n);   // 0x1140460
    void DecodeMul(int srcs, int n);    // 0x1140560
    int  Setup(void* buf, int a, int n);// 0x1140530
    void* Dtor(unsigned char flags);    // 0x11404f0
};
// ---- items of slice s0113fc50 end

// ---- items of slice s0114cb60 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma function(memcpy)
typedef float f32;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
namespace rw {
namespace audio {
namespace core {
struct AudioChannelBuffer {
    char  pad0[4];
    f32*  mpSamples;   // +0x04 channel-0 sample base
    char  pad8[0x0E - 0x08];
    u16   muStride;    // +0x0E inter-channel stride in samples
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct ChannelPointers {
    f32* mpStart;   // +0x00
    f32* mpEnd;     // +0x04
    f32* mpLoopEnd; // +0x08
    f32* mpCursor;  // +0x0C
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct TapContext {
    f32* mpBase;      // +0x00
    f32* mpTap;       // +0x04
    f32* mpTap2;      // +0x08
    f32* mpRamp;      // +0x0C
    f32* mpLoadedEnd; // +0x10
    f32* mpOut;       // +0x14
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct TapRecord {
    s32  miLength;  // +0x00
    s32  miLength2; // +0x04
    s32  miSelect;  // +0x08
    f32* mpOut;     // +0x0C
};
}
}
}
namespace rw {
namespace audio {
namespace core {
typedef void* (*IFilterFunc)(void* self, s32 count, s32 src, s32 channel, TapContext* ctx);
}
}
}
namespace rw {
namespace audio {
namespace core {
class DelayLine {
public:
    f32* mpBuffer;             // +0x00
    void* mpFilter;            // +0x04
    f32* mpLocalBuffer;        // +0x08
    s32  miMaxDelaySamples;    // +0x0C
    s32  miReadLength;         // +0x10
    s32  miCapacity;           // +0x14
    s32  miGuardSamples;       // +0x18
    s32  miLocalBufferSamples; // +0x1C
    s32  miAvailableSamples;   // +0x20
    s32  miCleanCursor;        // +0x24
    s32  miReadPosition;       // +0x28
    s32  miFilterReadPosition; // +0x2C
    s32  miChannelCount;       // +0x30
    s32  miWritePhase;         // +0x34
    u8   mbFilterChanged;      // +0x38

    DelayLine();                                            // 0x0114d730
    void Release();                                         // 0x0114d770
    bool Init(s32 channels, s32 maxDelaySamples, s32 readLength); // 0x0114d7b0
    bool Resize(s32 maxDelaySamples);                       // 0x0114d840
    void Reset(s32 readPosition);                           // 0x0114d9d0
    void CalcChannelPointers(ChannelPointers* pOut, s32 channel, s32 offset) const; // 0x0114d9f0
    f32* WrapCursor(const ChannelPointers* pPtrs, s32 backOffset) const; // 0x0114da40

    // helpers used by ReverbModel1::Process (reference DelayLine.cpp)
    void SetFilter(void* pFilter) { mpFilter = pFilter; }
    void SetLocalBuffer(f32* p, s32 n) { mpLocalBuffer = p; miLocalBufferSamples = n; }
    s32  ReadData(const ChannelPointers* p, f32* dst, s32 backOffset, s32 count) const;
    void WriteData(const ChannelPointers* p, const f32* src, s32 backOffset, s32 count) const;
    f32* LoadTaps(const ChannelPointers* p, TapRecord* taps, s32 tapCount) const;
    void IncrementalClean(s32 count, s32 offset, TapContext* c) const;
    s32  MarshalDelayData(s32 channel, s32 count, s32 offset, TapContext* c);
    void UnmarshalDelayData(s32 channel, s32 count, TapContext* c);
    void ApplyFilter(s32 count, const AudioChannelBuffer* in, const AudioChannelBuffer* out, s32 src);
};
}
}
}
namespace rw {
namespace audio {
namespace core {
s32 DelayLine::ReadData(const ChannelPointers* p, f32* dst, s32 backOffset, s32 count) const
{
    if (count == 0)
        return 0;
    s32 produced = count;
    if (count >= backOffset)
        produced = backOffset;
    const f32* src = p->mpCursor - backOffset;
    if (src < p->mpStart || p->mpEnd <= src)
        src += (miCapacity - miGuardSamples);
    s32 first = (s32)(p->mpEnd - src);
    if (produced < first)
        first = produced;
    memcpy(dst, src, (size_t)(4 * first));
    memcpy(dst + first, p->mpStart, (size_t)(4 * (produced - first)));
    return produced;
}
}
}
}
namespace rw {
namespace audio {
namespace core {
void DelayLine::WriteData(const ChannelPointers* p, const f32* src, s32 backOffset, s32 count) const
{
    f32* dst = p->mpCursor - backOffset;
    if (dst < p->mpStart || p->mpEnd <= dst)
        dst += (miCapacity - miGuardSamples);
    if (count < (s32)(p->mpEnd - p->mpStart)) {
        s32 first = (s32)(p->mpEnd - dst);
        if (count < first)
            first = count;
        memcpy(dst, src, (size_t)(4 * first));
        memcpy(p->mpStart, src + first, (size_t)(4 * (count - first)));
    }
}
}
}
}
namespace rw {
namespace audio {
namespace core {
f32* DelayLine::LoadTaps(const ChannelPointers* p, TapRecord* taps, s32 tapCount) const
{
    taps[0].miSelect = 0;
    if (tapCount == 2) {
        const bool firstLonger = taps[0].miLength >= taps[1].miLength;
        taps[0].miSelect = firstLonger ? 0 : 1;
        taps[1].miSelect = firstLonger ? 1 : 0;
    }
    f32* dst = mpLocalBuffer;
    s32 avail = (taps[taps[0].miSelect].miLength + 31) & ~31;
    for (s32 tap = 0; tap < tapCount; ++tap) {
        TapRecord* rec = &taps[taps[tap].miSelect];
        const s32 lenRounded = (rec->miLength + 31) & ~31;
        const s32 pad = lenRounded - rec->miLength;
        const s32 len2Rounded = (rec->miLength2 + pad + 31) & ~31;
        s32 read;
        if (lenRounded > avail) {
            s32 span = avail - (lenRounded - len2Rounded);
            rec->mpOut = dst + (pad - lenRounded + avail);
            if (span < 0)
                span = 0;
            read = ReadData(p, dst, avail, span);
            avail += read;
        } else {
            rec->mpOut = dst + pad;
            read = ReadData(p, dst, lenRounded, len2Rounded);
            avail = lenRounded - read;
        }
        dst += read;
    }
    return dst;
}
}
}
}
namespace rw {
namespace audio {
namespace core {
void DelayLine::IncrementalClean(s32 count, s32 offset, TapContext* c) const
{
    if (miCleanCursor >= miCapacity)
        return;
    s32 n = miReadPosition - miCleanCursor - offset;
    const s32 limit = count + miReadLength - 1;
    if (n >= limit)
        n = limit;
    if (n < 0)
        n = 0;
    for (s32 k = 0; k < n; ++k)
        c->mpTap[k] = 0.0f;
    if (c->mpTap2) {
        const s32 base = miReadLength;
        s32 m = miFilterReadPosition - offset - miCleanCursor;
        if (m >= base + 127)
            m = base + 127;
        const s32 cap2 = base + count - 1;
        if (m >= cap2)
            m = cap2;
        if (m < 0)
            m = 0;
        for (s32 k = 0; k < m; ++k)
            c->mpTap2[k] = 0.0f;
    }
}
}
}
}
namespace rw {
namespace audio {
namespace core {
s32 DelayLine::MarshalDelayData(s32 channel, s32 count, s32 offset, TapContext* c)
{
    ChannelPointers ptrs;
    TapRecord taps[2];
    CalcChannelPointers(&ptrs, channel, offset);
    s32 tapCount = 1;
    taps[0].miLength = miReadPosition;
    taps[0].miLength2 = miReadLength + count - 1;
    taps[0].mpOut = 0;
    if (mbFilterChanged) {
        s32 window = count;
        if (count >= 128)
            window = 128;
        taps[1].miLength = miFilterReadPosition;
        taps[1].miLength2 = miReadLength + window - 1;
        taps[1].mpOut = 0;
        tapCount = 2;
    }
    f32* loadedEnd = LoadTaps(&ptrs, taps, tapCount);
    c->mpTap = taps[0].mpOut;
    c->mpLoadedEnd = loadedEnd;
    c->mpTap2 = mbFilterChanged ? taps[1].mpOut : 0;
    IncrementalClean(count, offset, c);
    return count;
}
}
}
}
namespace rw {
namespace audio {
namespace core {
void DelayLine::UnmarshalDelayData(s32 channel, s32 count, TapContext* c)
{
    ChannelPointers ptrs;
    CalcChannelPointers(&ptrs, channel, 0);
    WriteData(&ptrs, c->mpLoadedEnd - count, 0, count);
}
}
}
}
namespace rw {
namespace audio {
namespace core {
void DelayLine::ApplyFilter(s32 count, const AudioChannelBuffer* in, const AudioChannelBuffer* out, s32 src)
{
    f32 ramp[128];
    if (mbFilterChanged) {
        f32 coeff = 0.9921875f;
        for (s32 k = 0; k < 128; ++k) {
            ramp[k] = coeff;
            coeff -= 0.0078125f;
        }
    }

    for (s32 channel = 0; channel < miChannelCount; ++channel) {
        s32 rampRemaining = 0;
        TapContext ctx;
        ctx.mpBase = in->mpSamples + (u32)in->muStride * channel;
        ctx.mpOut = out->mpSamples + (u32)out->muStride * channel;
        ctx.mpTap2 = 0;
        ctx.mpRamp = 0;
        if (mbFilterChanged) {
            rampRemaining = 128;
            ctx.mpRamp = ramp;
        }
        for (s32 i = 0; i < count; UnmarshalDelayData(channel, i, &ctx)) {
            const s32 total = MarshalDelayData(channel, count, i, &ctx);
            s32 remainder = total;
            if (rampRemaining) {
                s32 chunk = rampRemaining < total ? rampRemaining : total;
                ctx.mpRamp = ramp + (128 - rampRemaining);
                ((IFilterFunc)((void**)mpFilter)[0])(mpFilter, chunk, src, channel, &ctx);
                i += chunk;
                rampRemaining -= chunk;
                ctx.mpBase += chunk; ctx.mpTap += chunk; ctx.mpTap2 += chunk;
                ctx.mpRamp += chunk; ctx.mpLoadedEnd += chunk; ctx.mpOut += chunk;
                remainder = total - chunk;
            }
            if (remainder) {
                ctx.mpTap2 = 0;
                ctx.mpRamp = 0;
                ((IFilterFunc)((void**)mpFilter)[0])(mpFilter, remainder, src, channel, &ctx);
                i += remainder;
                ctx.mpBase += remainder; ctx.mpTap += remainder; ctx.mpTap2 += remainder;
                ctx.mpRamp += remainder; ctx.mpLoadedEnd += remainder; ctx.mpOut += remainder;
            }
        }
    }

    const s32 capacity = miCapacity;
    s32 writePhase = (count + miWritePhase) % capacity;
    if (writePhase <= miGuardSamples)
        writePhase = miGuardSamples;
    miWritePhase = writePhase;
    s32 clean = count + miCleanCursor;
    if (clean >= capacity)
        clean = capacity;
    miCleanCursor = clean;
    s32 avail = miAvailableSamples + count;
    if (avail >= capacity)
        avail = capacity;
    miAvailableSamples = avail;
    mbFilterChanged = 0;
}
}
}
}
// ---- items of slice s0114cb60 end

// ---- items of slice s0114da70 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma function(memset)
typedef short s16;
namespace rw {
namespace audio {
namespace core {
class CombFilter { public:
    void* mpApplyFunc;  // +0x00
    void* mpResetFunc;  // +0x04
    s32   miReadLength; // +0x08
    s32   miChannels;   // +0x0C
    f32   mfGain1;      // +0x10
    f32   mfGain2;      // +0x14
    f32   mfGain3;      // +0x18
    f32   mfGain4;      // +0x1C
    f32   mfState;      // +0x20

    CombFilter();                                  // 0x0114dce0
    void SetGains(f32, f32, f32, f32);             // 0x0114dcb0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
CombFilter* CombFilterReset(CombFilter* self);     // 0x0114dca0
}
}
}
namespace rw {
namespace audio {
namespace core {
class AllPassFilter { public:
    void* mpApplyFunc;  // +0x00
    void* mpResetFunc;  // +0x04
    s32   miReadLength; // +0x08
    s32   miChannels;   // +0x0C
    f32   mfGain1;      // +0x10
    f32   mfGain2;      // +0x14

    AllPassFilter();                                // 0x0114e230
};
}
}
}
namespace rw {
namespace audio {
namespace core {
f32 CombFilterFunc(s32 count, f32 g1, f32 g2, f32 g3, f32 g4, f32 state, f32* base, f32* work,
                   f32* accum, f32* feedforward, s32 lowPass); // 0x0114da70
}
}
}
namespace rw {
namespace audio {
namespace core {
void AllPassFilterFunc(s32 count, f32 g1, f32 g2, f32* base, f32* work, f32* feedforwardA,
                       f32* feedforwardB, s32 lowPass); // 0x0114dd20
}
}
}
namespace rw {
namespace audio {
namespace core {
void* CombFilterApply(CombFilter* self, s32 count, s32 src, s32 /*channel*/, TapContext* ctx); // 0x0114dc20
}
}
}
namespace rw {
namespace audio {
namespace core {
void* AllPassFilterApply(AllPassFilter* self, s32 count, s32 src, s32 /*channel*/, TapContext* ctx); // 0x0114e1b0
}
}
}
namespace rw {
namespace audio {
namespace core {
struct AudioProcessContext {
    char pad0[0x30000];
    char pad30000[0x0C];
    AudioChannelBuffer* mpSrcBuffer; // +0x3000C
    AudioChannelBuffer* mpDstBuffer; // +0x30010
    char  pad14[4];
    char* mpFormat;                  // +0x30018
    char  pad1c[4];
    s32   mNumSamples;               // +0x30020
    f32   mfField24;                 // +0x30024
    f32   mfResampleGain;            // +0x30028
    s32   mChannelCount;             // +0x3002C
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class System_s0114_da70 { public:
    char pad0[0x14];
    void* Alloc(u32 size, const char* tag, int flags, int align);  // 0x0112c820 (rw::audio::core::System::Alloc)
    void  Free(void* p, int flags);  // 0x0112c850 (rw::audio::core::System::Free)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern System_s0114_da70* g_pSystem; // DAT_016e61a8
}
}
}
namespace rw {
namespace audio {
namespace core {
class FastFirEngine;
}
}
}
namespace rw {
namespace audio {
namespace core {
class FastFirEngine { public:
    void* mpBuffer;    // +0x00
    f32*  mpInput[2];  // +0x04 / +0x08
    f32*  mpFreq;      // +0x0C
    void* mpImpulse;   // +0x10
    f32*  mpConv;      // +0x14
    f32*  mpOutput[2]; // +0x18 / +0x1C
    s32   miConvBytes; // +0x20
    s32   miBlockFftLen; // +0x24
    s32   miField28;   // +0x28
    s32   miNumBlocks; // +0x2C
    s32   miWriteBlock;// +0x30
    s32   miField34;   // +0x34
    s32   miFrameLen;  // +0x38
    s32   miBlockLen;  // +0x3C
    s32   miFftClearLen; // +0x40
    s32   miField44;   // +0x44
    s32   miBlockStride; // +0x48
    s32   miField4C;   // +0x4C
    s32   miField50;   // +0x50
    s32   miNumPasses; // +0x54
    s32   miField58;   // +0x58
    s32   miCurPass;   // +0x5C
    f32   mfField60;   // +0x60
    s32   miPingA;     // +0x64
    s32   miPingB;     // +0x68
    void* mpFft;       // +0x6C
    s32   miField70;   // +0x70
    s32   miInputChannels; // +0x74
    s32   miOutputChannels;// +0x78
    void* mpDist;      // +0x7C
    s32   miFftDone;   // +0x80
    s32   miMacDone;   // +0x84
    s32   miIfftDone;  // +0x88
    s32   miField8C;   // +0x8C
    u8    mbField90;   // +0x90

    FastFirEngine();                                        // 0x0114e300
    ~FastFirEngine();                                       // 0x0114e340
    int  SetChannels(s32 inputChannels, s32 outputChannels);// 0x0114e370
    void* Filter(AudioChannelBuffer* in, void* out, s32 a4, s32 a5); // 0x0115de20
    void Reset();                                           // 0x0114e580
    int  Configure(s32 channels, s32 blockSize, s32 a4, s32 a5, s32 a6, s32 impulseSamples,
                   s16* pImpulse);                          // 0x0114e5e0
    void LoadDistributionCalc(s32 sizeLog2, s32 numBlocks); // 0x0114e400
    f32  EstimateLoad(s32 a2, s32 a3, s32 a4, s32 a5);      // 0x0114e390
};
}
}
}
namespace rw {
namespace audio {
namespace core {
void* FFT_Free(void** handle); // 0x0115e3c0
}
}
}
namespace rw {
namespace audio {
namespace core {
class ReverbIR1 { public:
    char pad0[4];
    s32  miField04;        // +0x04
    char pad8[0x21 - 0x08];
    u8   mbChannelCount;   // +0x21
    char pad22[0x50 - 0x22];
    FastFirEngine mEngine; // +0x50 (sizeof == 0x94)
    s32  miFieldE4;        // +0xE4
    s32  miState;          // +0xE8

    static int Process(ReverbIR1* self, AudioProcessContext* ctx);
};
}
}
}
// ---- items of slice s0114da70 end

// @ 0x01140030
int F_01140030(int a, int val)
{
    if (*(unsigned char*)0x16e7c1c == 0) return -10;
    int handle = Sub_1141150(a);
    if (handle >= 0) {
        int local = -1;
        int r = Sub_1156660(handle, &local);
        while (r != 0) {
            FUN_01140930(local, val);
            r = Sub_1156660(handle, &local);
        }
    }
    return handle;
}

// @ 0x011400a0
int F_011400a0(int a, int val)
{
    if (*(unsigned char*)0x16e7c1c == 0) return -10;
    int handle = Sub_1141150(a);
    if (handle >= 0) {
        int local = -1;
        int r = Sub_1156660(handle, &local);
        while (r != 0) {
            SNDPLATFORM_highpass(local, val);
            r = Sub_1156660(handle, &local);
        }
    }
    return handle;
}

// @ 0x01140110
char* F_01140110(char* p, unsigned tag, int n)
{
    char c2 = (char)(tag >> 16);
    char c3 = (char)(tag >> 8);
    for (;;) {
        if (n < 1) return 0;
        char c1 = (char)(tag >> 24);
        if (p[0] == c1 && p[1] == c2 && p[2] == c3 && p[3] == (char)tag) {
            if (!(c1 == 'd' && c2 == 'a' && c3 == 't' && (char)tag == 'a')) return p;
            if (*(unsigned*)(p + 4) != 0) return p;
        }
        n--;
        p++;
    }
}

// @ 0x01140190
float F_01140190(unsigned char* p)
{
    unsigned int hi = (((unsigned)(signed char)p[0] & 0x7f) << 8) | p[1];
    int mid = (int)(((unsigned)p[2] << 24) | ((unsigned)p[3] << 16) | ((unsigned)p[4] << 8) | p[5]);
    int lo  = (int)(((unsigned)p[6] << 24) | ((unsigned)p[7] << 16) | ((unsigned)p[8] << 8) | p[9]);
    double res;
    if (hi == 0) {
        if (mid == 0 && lo == 0) {
            res = 0.0;
            goto sign;
        }
    } else if (hi == 0x7fff) {
        res = Ad(0x15bfe78);
        goto sign;
    }
    {
        double a = ldexp((double)(int)((unsigned)mid + 0x80000000u) + 2147483648.0, (int)hi - 0x401e);
        double b = ldexp((double)(int)((unsigned)lo + 0x80000000u) + 2147483648.0, (int)hi - 0x403e);
        res = a + b;
    }
sign:
    if (p[0] & 0x80) res = -res;
    return (float)res;
}

// @ 0x01140290
float F_01140290(void* p)
{
    unsigned char buf[12];
    *(unsigned*)&buf[0] = *(unsigned*)p;
    *(unsigned*)&buf[4] = *(unsigned*)((char*)p + 4);
    *(unsigned short*)&buf[8] = *(unsigned short*)((char*)p + 8);
    return F_01140190(buf);
}

// @ 0x011402f0
void SndDecoder::DecodeS16(int srcs, int n)
{
    int c = count;
    if (c == 0) return;
    if (n < c) c = n;
    int i = 0;
    if (c > 0) {
        do {
            short s = 0;
            if (chans > 0) {
                do {
                    short* d = (short*)(*(int*)(srcs + s * 4) + i * 2);
                    dst = d;
                    *d = (short)((*src - 0x80) * 0x100);
                    src = src + 1;
                    s++;
                } while (s < chans);
            }
            i++;
        } while (i < c);
    }
    count = count - c;
}

// @ 0x01140380
void SndDecoder::SetState(short* p)
{
    *(short*)((char*)this + 0x14) = *p;
}

// @ 0x011403b0
void SndDecoder::DecodeRaw(int srcs, int n)
{
    if (count == 0) return;
    if (n > count) n = count;
    count = count - n;
    int i = 0;
    while (n > 0) {
        for (short s = 0; s < chans; s++) {
            unsigned short* d = (unsigned short*)(*(int*)(srcs + s * 4) + i * 2);
            dst = (short*)d;
            *d = (unsigned short)((src[0] << 8) | src[1]);
            src = src + 3;
        }
        i++;
        n--;
    }
    volatile SndDecoder* keep = this;
    if (keep == this) return;
}

// @ 0x01140460
void SndDecoder::DecodeSwap(int srcs, int n)
{
    if (count == 0) return;
    if (n > count) n = count;
    count = count - n;
    int i = 0;
    while (n > 0) {
        for (short s = 0; s < chans; s++) {
            unsigned short* d = (unsigned short*)(*(int*)(srcs + s * 4) + i * 2);
            dst = (short*)d;
            unsigned short v = *(unsigned short*)src;
            *d = (unsigned short)((v >> 8) | (v << 8));
            src = src + 2;
        }
        i++;
        n--;
    }
    volatile SndDecoder* keep = this;
    if (keep == this) return;
}

// @ 0x011404f0
void* SndDecoder::Dtor(unsigned char flags)
{
    *(void**)this = (void*)0x14cafa0;
    if ((flags & 1) != 0) {
        (*(void(__cdecl**)(void*))0x16f16f4)(this);
    }
    return this;
}

// @ 0x01140530
int SndDecoder::Setup(void* buf, int a, int n)
{
    if (buf != 0 && count == 0) {
        count = n;
        src = (unsigned char*)buf;
        field10 = a;
        return 0;
    }
    return -1;
}

// @ 0x01140560
void SndDecoder::DecodeMul(int srcs, int n)
{
    int c = count;
    if (c == 0) return;
    if (n < c) c = n;
    int i = 0;
    if (c > 0) {
        do {
            short s = 0;
            if (chans > 0) {
                do {
                    short* d = (short*)(*(int*)(srcs + s * 4) + i * 2);
                    dst = d;
                    *d = (short)((unsigned short)*src * 0x100);
                    src = src + 1;
                    s++;
                } while (s < chans);
            }
            i++;
        } while (i < c);
    }
    count = count - c;
}

// @ 0x011405e0
int F_011405e0(int a, int val)
{
    if (*(unsigned char*)0x16e7c1c == 0) return -10;
    int handle = Sub_1141150(a);
    if (handle >= 0) {
        int local = -1;
        int r = Sub_1156660(handle, &local);
        while (r != 0) {
            F_01140b20(local, val);
            r = Sub_1156660(handle, &local);
        }
    }
    return handle;
}

// @ 0x01140650
void FUN_01140650(int a)
{
    int o = a * 0x84 + D;
    int tbl = A32(0x16e804c) + a * 0x18;
    char c = *(char*)(o + 99);
    float f = *(float*)(o + 0x48);
    int i = 0;
    if (A8(0x16e7be4) != 0) {
        do {
            Sub_1142a20(a, i, *(float*)(tbl + i * 4) * (((float)(int)c * f) * 0.007874016f));
            i++;
        } while (i < (int)A8(0x16e7be4));
    }
}

// @ 0x011406e0
void FUN_011406e0(int a)
{
    int o = a * 0x84 + D;
    int v = A32(0x16e804c) + a * 0x18;
    if (*(char*)(o + 0x1f) == 0) {
        Sub_1156310(*(unsigned short*)(o + 0x1c), v);
        F_0113fec0(a);
        return;
    }
    int i = 0;
    if (A8(0x16e7be4) != 0) {
        do {
            *(unsigned*)(v + i * 4) = 0;
            i++;
        } while (i < (int)A8(0x16e7be4));
    }
    *(unsigned*)(v + 0x14) = 0x3f800000;
    F_0113fec0(a);
}

// @ 0x01140760
int F_01140760(void)
{
    A8(0x16e7bfc) = 1;
    A8(0x16e7c23) = (unsigned char)Sub_1156800();
    return 0;
}

// @ 0x01140780
int F_01140780(void)
{
    Sub_1142730(A8(0x16e7bfd));
    if (g_16e7c1c != 0) {
        A32(0x16e7bf4) = A32(0x16e7c0c);
        A32(0x16e7bf8) = A32(0x16e7c10);
        A8(0x16e7bfd) = A8(0x16e7bfd);
        A32(0x16e7bfc) = A32(0x16e7c14);
        A32(0x16e7c00) = A32(0x16e7c18);
        return 0;
    }
    if (A8(0x16e7bfc) != 0) {
        if ((Sub_1156800() & 2) != 0) {
            A8(0x16e7c23) |= 2;
            return 0;
        }
    }
    A8(0x16e7c23) &= 0xfd;
    A8(0x16e7bfc) = 0;
    return 0;
}

// @ 0x01140b20
int F_01140b20(int a, int val)
{
    int o = a * 0x84 + D;
    int i = 0;
    if (*(char*)(o + 0x23) != 0) {
        short* ps = (short*)(o + 4);
        do {
            Sub_1156b40(*ps, i, val);
            i++;
            ps++;
        } while (i < (int)*(unsigned char*)(o + 0x23));
    }
    return 0;
}

// @ 0x0114d9d0
namespace rw { namespace audio { namespace core {
void DelayLine::Reset(s32 readPosition)
{
    const s32 capacity = miCapacity;
    miAvailableSamples = capacity;
    const s32 guard = miGuardSamples;
    miWritePhase = guard;
    miCleanCursor = 0;
    miReadPosition = readPosition;
    mbFilterChanged = 0;
}
}}}  // namespace rw::audio::core

// @ 0x0114da70
namespace rw { namespace audio { namespace core {
f32 CombFilterFunc(s32 count, f32 g1, f32 g2, f32 g3, f32 g4, f32 state, f32* base, f32* work, f32* accum, f32* feedforward, s32 lowPass)
{
    if (lowPass == 0)
        memset(feedforward, 0, (size_t)count * 4);
    for (s32 n = 0; n < count; ++n) {
        // the SSE kernel computes base - work*g2 as one vector lane, then subtracts
        // state*g1 serially, so preserve that association for bit-exact rounding.
        const f32 out = (base[n] - work[n + 1] * g2) - state * g1;
        accum[n] = out;
        feedforward[n] = (work[n] * g3 + work[n + 1]) * g4 + feedforward[n];
        state = accum[n];
    }
    return state;
}
}}}  // namespace rw::audio::core

// @ 0x0114dc20
namespace rw { namespace audio { namespace core {
void* CombFilterApply(CombFilter* self, s32 count, s32 src, s32 /*channel*/, TapContext* ctx)
{
    if (ctx->mpTap2)
        return memset(ctx->mpOut, 0, (size_t)count * 4);
    self->mfState = CombFilterFunc(count, self->mfGain1, self->mfGain2, self->mfGain3, self->mfGain4,
                                   self->mfState, ctx->mpBase, ctx->mpTap, ctx->mpLoadedEnd,
                                   ctx->mpOut, src);
}
}}}  // namespace rw::audio::core

// @ 0x0114dca0
namespace rw { namespace audio { namespace core {
CombFilter* CombFilterReset(CombFilter* self)
{
    self->mfState = 0.0f;
    return self;
}
}}}  // namespace rw::audio::core

// @ 0x0114dcb0
namespace rw { namespace audio { namespace core {
void CombFilter::SetGains(f32 g1, f32 g2, f32 g3, f32 g4)
{
    mfGain1 = g1;
    mfGain2 = g2;
    mfGain3 = g3;
    mfGain4 = g4;
}
}}}  // namespace rw::audio::core

// @ 0x0114dce0
namespace rw { namespace audio { namespace core {
CombFilter::CombFilter()
{
    mpApplyFunc = 0;
    mpResetFunc = 0;
    miChannels = 1;
    miReadLength = 2;
    mfGain1 = 0.0f;
    mfGain2 = 0.0f;
    mfGain3 = 0.0f;
    mfGain4 = 0.0f;
    mfState = 0.0f;
}
}}}  // namespace rw::audio::core

// @ 0x0114dd20
namespace rw { namespace audio { namespace core {
void AllPassFilterFunc(s32 count, f32 g1, f32 g2, f32* base, f32* work, f32* feedforwardA, f32* feedforwardB, s32 lowPass)
{
    const f32 kFlush = 1.0e-18f;
    for (s32 n = 0; n < count; ++n) {
        const f32 biased = work[n] + kFlush;
        work[n] = biased - kFlush;
        const f32 y = base[n] - g1 * work[n];
        feedforwardA[n] = y;
        const f32 yb = y + kFlush;
        feedforwardA[n] = yb - kFlush;
        const f32 tap = feedforwardA[n] * g1 + work[n];
        feedforwardB[n] = lowPass ? tap * g2 + feedforwardB[n] : tap * g2;
    }
}
}}}  // namespace rw::audio::core

// @ 0x0114e1b0
namespace rw { namespace audio { namespace core {
void* AllPassFilterApply(AllPassFilter* self, s32 count, s32 src, s32 /*channel*/, TapContext* ctx)
{
    if (ctx->mpTap2)
        return memset(ctx->mpOut, 0, (size_t)count * 4);
    AllPassFilterFunc(count, self->mfGain1, self->mfGain2, ctx->mpBase, ctx->mpTap,
                      ctx->mpLoadedEnd, ctx->mpOut, src);
    // For count <= 0 the kernel never enters either loop, so it leaves eax holding whatever
    // the caller had live there (the receiver). The positive cases leave the kernel's own eax.
    if (count <= 0)
        return self;
}
}}}  // namespace rw::audio::core

// @ 0x0114e230
namespace rw { namespace audio { namespace core {
AllPassFilter::AllPassFilter()
{
    mpApplyFunc = 0;
    mpResetFunc = 0;
    miChannels = 1;
    miReadLength = 1;
    mfGain1 = 0.0f;
    mfGain2 = 0.0f;
}
}}}  // namespace rw::audio::core

// @ 0x0114e260
namespace rw { namespace audio { namespace core {
int ReverbIR1::Process(ReverbIR1* self, AudioProcessContext* ctx)
{
    AudioChannelBuffer* src = ctx->mpSrcBuffer;

    switch (self->miState) {
    case 0:
        for (u32 ch = 0; ch < self->mbChannelCount; ++ch)
            memset(src->mpSamples + src->muStride * ch, 0, 0x400);
        break;
    case 1:
        self->mEngine.Filter(src, ctx->mpDstBuffer, self->miField04, self->miFieldE4);
        {
            AudioChannelBuffer* a = ctx->mpSrcBuffer;
            ctx->mpSrcBuffer = ctx->mpDstBuffer;
            ctx->mpDstBuffer = a;
        }
        break;
    }
    return 1;
}
}}}  // namespace rw::audio::core

// @ 0x0114e300
namespace rw { namespace audio { namespace core {
FastFirEngine::FastFirEngine()
{
    mpFft = 0;
    miField70 = 0;
    mpBuffer = 0;
    miCurPass = 0;
    miWriteBlock = 0;
    miPingA = 0;
    miPingB = 0;
    miFftDone = 0;
    miMacDone = 0;
    miIfftDone = 0;
    miField8C = 0;
    mbField90 = 0;
}
}}}  // namespace rw::audio::core

// @ 0x0114e340
namespace rw { namespace audio { namespace core {
FastFirEngine::~FastFirEngine()
{
    if (mpBuffer)
        g_pSystem->Free(mpBuffer, 0);
    if (mpFft)
        FFT_Free(&mpFft);
}
}}}  // namespace rw::audio::core

// @ 0x0114e370
namespace rw { namespace audio { namespace core {
int FastFirEngine::SetChannels(s32 inputChannels, s32 outputChannels)
{
    miInputChannels = inputChannels;
    miOutputChannels = outputChannels;
    return 1;
}
}}}  // namespace rw::audio::core

// @ 0x0114e390
namespace rw { namespace audio { namespace core {
f32 FastFirEngine::EstimateLoad(s32 a2, s32 a3, s32 a4, s32 a5)
{
    const float p3 = (float)a3;
    const float fVar3 = (float)(p3 * log((double)p3) / log(2.0)); // p3 * log2(p3)
    const float outCh = (float)miOutputChannels;
    return ((outCh * 18.09f) * fVar3 +
            ((outCh * p3) * 10.97f +
             (((float)miInputChannels * 18.09f) * fVar3 +
              ((((float)a4 / p3) * (float)a2) * outCh) * 22.65f))) /
           (float)(a3 / a5);
}
}}}  // namespace rw::audio::core
