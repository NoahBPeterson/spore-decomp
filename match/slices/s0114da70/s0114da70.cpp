// rw::audio::core slice s0114da70 -- reverb building-block kernels (CombFilter / AllPassFilter),
// FastFirEngine members, the impulse-response reverb Process, the Resample increment/PreProcess,
// and the fixed-point ramp helper.
//
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE  (RenderWare 4 core: VC .NET 2003 + /LTCG and
// scalar SSE; see docs/matching.md).
#include "../../include/types.h"
#include <string.h>
#include <math.h>
#include <xmmintrin.h>

// The original routes the zero-fill paths through the real memset import (with a 32-bit
// byte count that wraps), so keep memset as a call instead of letting cl emit an inlined
// rep-stosd with a raw element count.
#pragma function(memset)

typedef float f32;
typedef double f64;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;

namespace rw {
namespace audio {
namespace core {

// ---------------------------------------------------------------------------------------
// TapContext (the filter apply argument record)
// ---------------------------------------------------------------------------------------
struct TapContext {
    f32* mpBase;      // +0x00
    f32* mpTap;       // +0x04
    f32* mpTap2;      // +0x08
    f32* mpRamp;      // +0x0C
    f32* mpLoadedEnd; // +0x10
    f32* mpOut;       // +0x14
};

// ---------------------------------------------------------------------------------------
// CombFilter / AllPassFilter flat records (slot 0/1 = apply/reset func pointers)
// ---------------------------------------------------------------------------------------
struct CombFilter {
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
// @ 0x0114dca0
CombFilter* CombFilterReset(CombFilter* self);     // 0x0114dca0

struct AllPassFilter {
    void* mpApplyFunc;  // +0x00
    void* mpResetFunc;  // +0x04
    s32   miReadLength; // +0x08
    s32   miChannels;   // +0x0C
    f32   mfGain1;      // +0x10
    f32   mfGain2;      // +0x14

    AllPassFilter();                                // 0x0114e230
};

// ---------------------------------------------------------------------------------------
// The recurrences (scalar form of the SSE kernels at 0x0114da70 / 0x0114dd20).
// ---------------------------------------------------------------------------------------
f32 CombFilterFunc(s32 count, f32 g1, f32 g2, f32 g3, f32 g4, f32 state, f32* base, f32* work,
                   f32* accum, f32* feedforward, s32 lowPass); // 0x0114da70
void AllPassFilterFunc(s32 count, f32 g1, f32 g2, f32* base, f32* work, f32* feedforwardA,
                       f32* feedforwardB, s32 lowPass); // 0x0114dd20

void* CombFilterApply(CombFilter* self, s32 count, s32 src, s32 /*channel*/, TapContext* ctx); // 0x0114dc20
void* AllPassFilterApply(AllPassFilter* self, s32 count, s32 src, s32 /*channel*/, TapContext* ctx); // 0x0114e1b0

// @ 0x0114da70
f32 CombFilterFunc(s32 count, f32 g1, f32 g2, f32 g3, f32 g4, f32 state, f32* base, f32* work,
                   f32* accum, f32* feedforward, s32 lowPass)
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

// @ 0x0114dd20
void AllPassFilterFunc(s32 count, f32 g1, f32 g2, f32* base, f32* work, f32* feedforwardA,
                       f32* feedforwardB, s32 lowPass)
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

// 0x0114dce0 -- CombFilter ctor (store order from the asm).
// @ 0x0114dce0
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

// 0x0114dcb0 -- CombFilter::SetGains
// @ 0x0114dcb0
void CombFilter::SetGains(f32 g1, f32 g2, f32 g3, f32 g4)
{
    mfGain1 = g1;
    mfGain2 = g2;
    mfGain3 = g3;
    mfGain4 = g4;
}

// 0x0114dca0 -- CombFilter reset (clears the loop state; returns self)
CombFilter* CombFilterReset(CombFilter* self)
{
    self->mfState = 0.0f;
    return self;
}

// 0x0114e230 -- AllPassFilter ctor (store order from the asm).
// @ 0x0114e230
AllPassFilter::AllPassFilter()
{
    mpApplyFunc = 0;
    mpResetFunc = 0;
    miChannels = 1;
    miReadLength = 1;
    mfGain1 = 0.0f;
    mfGain2 = 0.0f;
}

// 0x0114dc20 -- CombFilter apply dispatch
// @ 0x0114dc20
void* CombFilterApply(CombFilter* self, s32 count, s32 src, s32 /*channel*/, TapContext* ctx)
{
    if (ctx->mpTap2)
        return memset(ctx->mpOut, 0, (size_t)count * 4);
    self->mfState = CombFilterFunc(count, self->mfGain1, self->mfGain2, self->mfGain3, self->mfGain4,
                                   self->mfState, ctx->mpBase, ctx->mpTap, ctx->mpLoadedEnd,
                                   ctx->mpOut, src);
}

// 0x0114e1b0 -- AllPassFilter apply dispatch
// @ 0x0114e1b0
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

// ---------------------------------------------------------------------------------------
// AudioChannelBuffer / AudioProcessContext (shared views)
// ---------------------------------------------------------------------------------------
struct AudioChannelBuffer {
    char pad0[4];
    f32* mpSamples; // +0x04
    char pad8[0x0E - 0x08];
    u16  muStride;  // +0x0E
};

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

struct System {
    char pad0[0x14];
    void* Alloc(u32 size, const char* tag, int flags, int align);
    void  Free(void* p, int flags);
};
extern System* g_pSystem; // DAT_016e61a8

// ---------------------------------------------------------------------------------------
// FastFirEngine (real x86 layout == the reference's 4-byte X360 offsets)
// ---------------------------------------------------------------------------------------
struct VoiceStageConfig;
struct Resample;
struct FastFirEngine;

typedef void (*FFT_FreeFunc)(void**);

struct FastFirEngine {
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

void FFT_Alloc(s32 sizeLog2, char flag, void** outHandle);
void FFT_Init(void* handle);
void* FFT_Free(void** handle); // 0x0115e3c0

// 0x0114e300 -- ctor (store order from the asm)
// @ 0x0114e300
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

// 0x0114e340 -- destructor
// @ 0x0114e340
FastFirEngine::~FastFirEngine()
{
    if (mpBuffer)
        g_pSystem->Free(mpBuffer, 0);
    if (mpFft)
        FFT_Free(&mpFft);
}

// 0x0114e370 -- SetChannels
// @ 0x0114e370
int FastFirEngine::SetChannels(s32 inputChannels, s32 outputChannels)
{
    miInputChannels = inputChannels;
    miOutputChannels = outputChannels;
    return 1;
}

// 0x0114e580 -- Reset
// @ 0x0114e580
void FastFirEngine::Reset()
{
    if (mpBuffer) {
        g_pSystem->Free(mpBuffer, 0);
        mpBuffer = 0;
    }
    if (mpFft) {
        FFT_Free(&mpFft);
        mpFft = 0;
    }
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

// 0x0114e400 -- distribute the per-pass FFT/MAC/IFFT work (integer/floating, leaf).
// @ 0x0114e400
void FastFirEngine::LoadDistributionCalc(s32 param_2, s32 param_3)
{
    f32 fVar10 = (f32)miOutputChannels;
    f32 fVar8 = (f32)(param_2 - 1) * 18.09f;
    s32 iVar2 = miNumPasses;
    f32 fVar7 = (((1.0f - mfField60 * 0.01f) * (f32)param_3) * fVar10) * 22.65f / fVar8;
    f32 fVar11 = fVar7 / (f32)param_3;
    s32 iVar5 = 0, iVar4 = 0, iVar6 = 0, local_4 = 0;
    fVar7 = ((fVar10 * 10.97f) / fVar8 + (f32)miInputChannels) + fVar10 + fVar7;
    f32 fVar8b = 1.0f;
    s32 pass = 0;
    if (0 < iVar2) {
        s32 iVar3 = 0;
        do {
            f32 fVar9 = fVar7 / (f32)(iVar2 - pass);
            f32 fVar10b = fVar9;
            if (fVar8b * 0.5f <= fVar9) {
                do {
                    if (iVar4 < miInputChannels) {
                        int* p = (int*)((char*)mpDist + 4 + iVar3);
                        *p = *p + 1;
                        iVar4++;
                        fVar10b -= 1.0f;
                        if (miInputChannels <= iVar4)
                            fVar8b = fVar11;
                    } else if (iVar6 < param_3) {
                        int* p = (int*)((char*)mpDist + iVar3);
                        *p = *p + 1;
                        iVar6++;
                        fVar10b -= fVar11;
                        if (param_3 <= iVar6)
                            fVar8b = 1.0f;
                    } else if (iVar5 < miOutputChannels) {
                        int* p = (int*)((char*)mpDist + 8 + iVar3);
                        *p = *p + 1;
                        iVar5++;
                        fVar10b -= 1.0f;
                    } else {
                        fVar10b = 0.0f;
                    }
                    local_4 = iVar5;
                } while (fVar8b * 0.5f <= fVar10b);
            }
            fVar7 = fVar7 - (fVar9 - fVar10b);
            if (pass == miNumPasses - 1 && iVar5 < miOutputChannels) {
                int* p = (int*)((char*)mpDist + -4 + miNumPasses * 0xC);
                *p = *p + (miOutputChannels - local_4);
                iVar5 = local_4;
            }
            iVar2 = miNumPasses;
            pass++;
            iVar3 += 0xC;
        } while (pass < iVar2);
    }
}

// 0x0114e390 -- CPU-load estimate (x87, leaf).
// @ 0x0114e390
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

// 0x0114e5e0 -- Configure (reference FastFirEngine.cpp reconstruction)
// @ 0x0114e5e0
int FastFirEngine::Configure(s32 channels, s32 blockSize, s32 a4, s32 a5, s32 a6, s32 impulseSamples,
                             s16* pImpulse)
{
    if (mpBuffer)
        Reset();

    if (impulseSamples % blockSize) {
        miField34 = impulseSamples % blockSize;
        miNumBlocks = impulseSamples / blockSize + 1;
    } else {
        miField34 = blockSize;
        miNumBlocks = impulseSamples / blockSize;
    }

    miFrameLen = channels;
    miBlockLen = blockSize;
    miField50 = blockSize;

    const s32 fftClearLen = 2 * blockSize + 2;
    miFftClearLen = fftClearLen;

    mfField60 = ((f32)(blockSize - a4) / (f32)blockSize) * 100.0f;

    s32 v37 = fftClearLen / 16;
    if (fftClearLen % 16)
        ++v37;
    const s32 blockFftLen = 16 * v37;

    const s32 outputChannels = miOutputChannels;
    const s32 inputChannels = miInputChannels;

    miField44 = a5;
    miField4C = a5;
    miBlockStride = blockFftLen;
    miBlockFftLen = blockFftLen;
    miNumPasses = blockSize / channels;

    const s32 numBlocks = miNumBlocks;
    const s32 numPasses = blockSize / channels;
    const u32 outPartBytes = ((u32)outputChannels * (u32)blockSize) * 8u;
    const s32 inFreqBytes = 4 * inputChannels * blockFftLen;
    const s32 convBytes = 4 * outputChannels * blockFftLen;
    const s32 impFreqBytes = 4 * numBlocks * inputChannels * a5;

    miConvBytes = convBytes;

    const u32 totalBytes = (u32)(2 * (6 * numPasses + inFreqBytes) + convBytes) + outPartBytes +
                           (u32)impFreqBytes;

    void* buffer = g_pSystem->Alloc(totalBytes, "Reverb IR Buffer", 0x10, 0);
    mpBuffer = buffer;

    char* cursor = (char*)buffer;
    mpInput[0] = (f32*)cursor; cursor += inFreqBytes;
    mpInput[1] = (f32*)cursor; cursor += inFreqBytes;
    mpFreq = (f32*)cursor;     cursor += impFreqBytes;
    mpConv = (f32*)cursor;     cursor += convBytes;
    mpOutput[0] = (f32*)cursor; cursor += outPartBytes / 2;
    mpOutput[1] = (f32*)cursor; cursor += outPartBytes / 2;
    mpDist = cursor;

    memset(mpDist, 0, (size_t)((blockSize / channels) * 12));

    s32 sizeLog2 = 0;
    for (s32 n = 2 * blockSize; n > 1; n /= 2)
        ++sizeLog2;

    if (!mpFft) {
        FFT_Alloc(sizeLog2, 0, &mpFft);
        FFT_Init(mpFft);
    }

    miField28 = a6;
    mpImpulse = pImpulse;
    miField58 = a5 + 8;

    LoadDistributionCalc(sizeLog2, miNumBlocks);
    return 1;
}

// ---------------------------------------------------------------------------------------
// ReverbIR1 -- 0x0114e260 = Process (drives the embedded FastFirEngine).
// ---------------------------------------------------------------------------------------
struct ReverbIR1 {
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

// @ 0x0114e260
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

// ---------------------------------------------------------------------------------------
// The fixed-point ramp helper (0x0114e780).  Walks `src` at a 16.16 position, lerping the
// low-16 fraction between two taps, writing floats to `dst`.
// ---------------------------------------------------------------------------------------
struct PosDst { u32 pos; f32* dst; };
union U32F32 { u32 u; f32 f; };

// @ 0x0114e780
PosDst InterpRamp(u32 pos, s32 step, u32 end, const f32* src, f32* dst)
{
    if (pos < end) {
        const f32 kFracBias = -128.0f;              // 0xC3000000
        s32 limit = (s32)(end - (u32)step);         // end - step
        if ((s32)pos < limit) {
            do {
                const u32 whole = pos >> 16;
                const f32 s0 = src[whole];
                const f32 s1 = src[whole + 1];
                U32F32 cv; cv.u = (pos & 0xFFFFu) | 0x43000000u;
                const f32 frac = cv.f + kFracBias;
                *dst++ = s0 + (s1 - s0) * frac;
                pos += (u32)step;
            } while ((s32)pos < limit);
            limit += step;
            if ((s32)pos >= limit) {
                PosDst r = { pos, dst };
                return r;
            }
        }
        const u32 whole = pos >> 16;
        f32 s0 = src[whole];
        if (pos & 0xFFFFu) {
            const f32 s1 = src[whole + 1];
            U32F32 cv; cv.u = (pos & 0xFFFFu) | 0x43000000u;
            s0 = s0 + (s1 - s0) * (cv.f + kFracBias);
        }
        *dst++ = s0;
        pos += (u32)step;
    }
    PosDst r = { pos, dst };
    return r;
}

// ---------------------------------------------------------------------------------------
// Resample -- descriptor guid 'Rsp0'.  0x0114e860 SetResampleIncrement, 0x0114e8f0 PreProcess.
// ---------------------------------------------------------------------------------------
struct Resample {
    char pad0[0x08];
    void* mpVoice;          // +0x08
    char pad0c[0x18 - 0x0C];
    f32  mfLatency;         // +0x18
    char pad1c[0x21 - 0x1C];
    u8   mbChannelCount;    // +0x21
    char pad22[0x28 - 0x22];
    f32  mfPitch;           // +0x28
    char pad2c[0x30 - 0x2C];
    f32  mfPrevRate;        // +0x30
    f32  mfRequestedRatio;  // +0x34
    f32  mfActualRatio;     // +0x38
    s32  miField3C;         // +0x3C
    s32  miField40;         // +0x40
    s32  miIncr16_16;       // +0x44
    s32  miAcc16_16;        // +0x48

    void SetResampleIncrement(f32 ratio);                   // 0x0114e860
    int  PreProcess(AudioProcessContext* ctx, s32 a3, s32 outputSamples); // 0x0114e8f0
};

// 0x0114e860 -- clamp ratio to [0,4], latch it and the 16.16 increment, refresh the voice
// latency with min(1/ratio, 10000).
// @ 0x0114e860
void Resample::SetResampleIncrement(f32 ratio)
{
    mfRequestedRatio = ratio;

    s32 inc;
    if (ratio < 4.0f) {
        if (0.0f < ratio)
            inc = _mm_cvtss_si32(_mm_set_ss(ratio * 65536.0f)); // cvtss2si: round-nearest
        else
            inc = 0;
    } else {
        inc = 0x40000;
    }
    miIncr16_16 = inc;

    const f32 actual = (f32)inc * (1.0f / 65536.0f);
    mfActualRatio = actual;

    f32 latency = 1.0f / actual;
    if (!(10000.0f > latency))
        latency = 10000.0f;

    f32* pVoice = (f32*)mpVoice;
    pVoice[0x28 / 4] += latency - mfLatency;
    mfLatency = latency;
}

// 0x0114e8f0 -- PreProcess (cdecl free function, 4 stack args)
// @ 0x0114e8f0
int ResamplePreProcess(Resample* self, AudioProcessContext* ctx, s32 a3, s32 outputSamples)
{
    self->miField40 = outputSamples;
    self->miField3C = 0;

    if (self->mfPrevRate >= 0.0f) {
        f64 ratio = ((f64)self->mfPrevRate / (f64)*(f32*)(ctx->mpFormat + 0x0C)) * (f64)self->mfPitch;

        f64 diff = ratio - (f64)self->mfRequestedRatio;
        if (diff < 0.0)
            diff = -diff;
        if (!((f64)1.5258789e-05f > diff)) {
            self->miAcc16_16 = 0;
            self->SetResampleIncrement((f32)ratio);
        }

        ctx->mfResampleGain = self->mfActualRatio * ctx->mfResampleGain;

        self->miAcc16_16 = self->miAcc16_16 & ((u8)a3 - 1);
        s32 v = (outputSamples - 1) * self->miIncr16_16 + 0xFFFF + self->miAcc16_16;
        if (v >= 0)
            self->miField3C = (v >> 16) + 1;
    }
    return self->miField3C;
}

} // namespace core
} // namespace audio
} // namespace rw
