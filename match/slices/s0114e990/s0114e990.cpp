// s0114e990 -- rw::audio::core PC-build audio plug-in bodies that sit between
// Resample::PreProcess and PeakingIir2: the resample kernel, Rechannel::Process,
// RawPuller2 PreProcess/Process, the peaking biquad (coefficients + kernel + Process),
// the per-channel IIR state clear, and Pause PreProcess/Process.
//
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE   (RenderWare 4 audio core: VC .NET 2003)
#include "../../include/types.h"
#include <string.h>
#include <math.h>
#include <xmmintrin.h>

// The original calls the import stubs for the block copies/clears instead of inlining
// rep movs/stos.
#pragma function(memcpy)
#pragma function(memset)

typedef float f32;
typedef double f64;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef signed char s8;

// ---------------------------------------------------------------------------------------
// Audio processing context and channel-buffer descriptors (offsets from the PC build)
// ---------------------------------------------------------------------------------------
struct AudioChannelBuffer {
    char  pad0[4];
    f32*  mpSamples;   // +0x04
    char  pad8[0x0E - 0x08];
    u16   muStride;    // +0x0E
};

struct AudioProcessContext {
    char  pad00000[0x30000];
    char  pad30000[0x0C];
    AudioChannelBuffer* mpSrcBuffer;  // +0x3000C
    AudioChannelBuffer* mpDstBuffer;  // +0x30010
    AudioChannelBuffer* mpAuxBuffer;  // +0x30014
    void* mpFormat;                   // +0x30018
    u32   muMixerCpuCycles;           // +0x3001C
    s32   mNumSamples;                // +0x30020
    f32   mfSampleRate;               // +0x30024
    f32   mfResampleGain;             // +0x30028
    u8    mbChannelCount;             // +0x3002C
};

struct AudioFormat {
    char pad0[0x0C];
    f32  mfSampleRate; // +0x0C
};

extern char g_mixScratch[];  // 0x016e8300

struct PosDst { u32 pos; f32* dst; };
PosDst InterpRamp(u32 pos, s32 step, u32 end, const f32* src, f32* dst); // 0x0114e780

class Resample { public:
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
    f32  mfRampPrev;        // +0x50
    f32  mfRampCur;         // +0x54

    void SetResampleIncrement(f32 ratio);   // 0x0114e860
};

// ReChannelGainWrite: (ppDst, ppSrc, gain, numDst, numSrc, numSamples)
void __cdecl ReChannelGainWrite(f32** ppDst, f32** ppSrc, f32 gain, u32 numDst,
                                u32 numSrc, s32 numSamples);  // 0x0112d590

// =======================================================================================
// Rechannel::Process  (0x0114ec60) -- force the input frame to the plug-in's output
// channel count, re-writing the gain matrix, then ping-pong the buffer slots.
// =======================================================================================
struct Rechannel {
    char pad0[0x20];
    u8   mbFlag20;       // +0x20
    u8   mbChannelCount; // +0x21
};

// @ 0x0114ec60
int __cdecl RechannelProcess(Rechannel* self, AudioProcessContext* ctx)
{
    u32 numSamples = (u32)ctx->mNumSamples;
    u32 inCh = ctx->mbChannelCount;

    if (!numSamples)
        self->mbFlag20 = (u8)inCh;

    u32 outCh = self->mbChannelCount;
    if (inCh != outCh)
    {
        if (numSamples)
        {
            AudioChannelBuffer* src = ctx->mpSrcBuffer;
            AudioChannelBuffer* dst = ctx->mpDstBuffer;

            f32* srcPtr[6];
            f32* dstPtr[6];

            u32 srcCount = inCh;
            if (srcCount > 6)
                srcCount = 6;
            u32 c = 0;
            if (srcCount != 0)
            {
                do {
                    srcPtr[c] = src->mpSamples + src->muStride * c;
                    ++c;
                } while (c < srcCount);
            }

            c = 0;
            if (outCh != 0)
            {
                do {
                    dstPtr[c] = dst->mpSamples + dst->muStride * c;
                    ++c;
                } while (c < outCh);
            }

            ReChannelGainWrite(dstPtr, srcPtr, 1.0f, outCh, inCh, (s32)numSamples);
        }

        AudioChannelBuffer* tmp = ctx->mpSrcBuffer;
        ctx->mpSrcBuffer = ctx->mpDstBuffer;
        ctx->mpDstBuffer = tmp;
        ctx->mbChannelCount = self->mbChannelCount;
    }
    return 1;
}

// =======================================================================================
// Resample::Process (0x0114e990) -- fixed-point 16.16 resampling: pre-ramp the previous
// block's tail, walk the stream with InterpRamp, then post-ramp into the next block.
// Approximate reconstruction: control flow follows the original; byte-exactness is not
// claimed (large greenfield body, several compiler-chosen register lifetimes).
// =======================================================================================
// @ 0x0114e990
int __cdecl ResampleProcess(Resample* self, AudioProcessContext* ctx, s32 a3)
{
    const f32 kFrac = 1.5258789e-05f;

    for (;;)
    {
        const f32 fmtRate = ((AudioFormat*)ctx->mpFormat)->mfSampleRate;
        const f32 rate = ctx->mfSampleRate;
        const u8  channels = self->mbChannelCount;

        u32 numSamples = (u32)ctx->mNumSamples;
        const s32 limit3C = self->miField3C;
        if ((s32)numSamples > limit3C)
            numSamples = (u32)limit3C;

        const s32 maxOut = self->miField40;

        self->miAcc16_16 &= (u8)a3 - 1;

        if (self->mfPrevRate != rate)
        {
            self->miAcc16_16 = 0;
            self->SetResampleIncrement((rate / fmtRate) * self->mfPitch);
            self->mfPrevRate = rate;
        }

        if (self->miAcc16_16 == 0 && self->miIncr16_16 == 0x10000 &&
            (s32)numSamples <= maxOut)
        {
            ctx->mNumSamples = (s32)numSamples;
            ctx->mfSampleRate = fmtRate;
            return 1;
        }

        AudioChannelBuffer* srcBuf = ctx->mpSrcBuffer;
        AudioChannelBuffer* dstBuf = ctx->mpDstBuffer;
        const s32 step = self->miIncr16_16;

        u32 end = (u32)step * (u32)maxOut + (u32)self->miAcc16_16;
        const u32 cap = numSamples * 0x10000 - 0xFFFF;
        if (end > cap)
            end = cap;

        u32 pos = (u32)self->miAcc16_16;
        f32* dstLast = 0;
        f32* lastDstEnd = 0;

        for (u32 ch = 0; ch < channels; ++ch)
        {
            f32* src = srcBuf->mpSamples + srcBuf->muStride * ch;
            f32* dst = dstBuf->mpSamples + dstBuf->muStride * ch;
            f32* dstEnd = dst + maxOut;
            lastDstEnd = dstEnd;

            if (dst != dstEnd && pos + 0x20000 <= 0x10000)
            {
                const f32 prev = self->mfRampPrev;
                const f32 cur  = self->mfRampCur;
                const f32 diff = cur - prev;
                u32 p = pos + 0x20000;
                do
                {
                    *dst = ((f32)(s32)p * kFrac) * diff + prev;
                    p += (u32)step;
                    ++dst;
                    if (p > 0x10000)
                        break;
                } while (dst != dstEnd);
                pos = p - 0x20000;
            }

            if ((s32)numSamples > 0)
            {
                const f32 oldCur = self->mfRampCur;
                if (numSamples == 1)
                {
                    self->mfRampPrev = oldCur;
                    self->mfRampCur = src[0];
                }
                else
                {
                    self->mfRampPrev = src[numSamples - 2];
                    self->mfRampCur = src[numSamples - 1];
                }

                if (dst != dstEnd && pos > 0xFFFF0000)
                {
                    const f32 first = src[0];
                    const f32 diff = first - oldCur;
                    u32 p = pos + 0x10000;
                    do
                    {
                        *dst = ((f32)(s32)p * kFrac) * diff + oldCur;
                        p += (u32)step;
                        ++dst;
                        if (p > 0xFFFF)
                            break;
                    } while (dst != dstEnd);
                    pos = p - 0x10000;
                }

                PosDst r = InterpRamp(pos, step, end, src, dst);
                pos = r.pos;
                dstLast = r.dst;
            }
        }

        s32 acc = (s32)pos - (s32)numSamples * 0x10000;
        if ((u32)(acc + 0x80000000) < 0x7ffe0000)
            acc = 0;
        self->miAcc16_16 = acc;

        const s32 written = maxOut - (s32)((lastDstEnd - dstLast) >> 2);

        AudioChannelBuffer* tmp = ctx->mpSrcBuffer;
        ctx->mpSrcBuffer = ctx->mpDstBuffer;
        ctx->mpDstBuffer = tmp;
        ctx->mNumSamples = written;
        ctx->mfSampleRate = fmtRate;

        if (written == maxOut)
            return 1;
        if (written != 0)
            return 1;
        if ((u8)a3 == 0)
            return 1;

        a3 = 0;
        self->miField3C = 0;
        ctx->mfSampleRate = rate;
    }
}

// =======================================================================================
// RawPuller2 -- raw PCM pull source plug-in
// =======================================================================================
typedef bool (*RawPuller2FillFn)(u32 frames, void* dst, f32 gain, void* context);

struct RawPuller2 {
    void*             mpVTable;         // +0x00
    void*             mpSystem;         // +0x04
    char              pad8[0x24 - 0x08];
    RawPuller2FillFn  mpCallback;       // +0x24
    void*             mpContext;        // +0x28
    f32               mfRate;           // +0x2C
    u32               muFrameCount;     // +0x30
    u8                mbRestart;        // +0x34
    u8                mbNumChannels;    // +0x35
};

// @ 0x0114ed60
int __cdecl RawPuller2PreProcess(RawPuller2* self, int /*a2*/, int /*a3*/, int a4)
{
    self->muFrameCount = (u32)a4;
    return 0;
}

// @ 0x0114ed70
int __cdecl RawPuller2Process(RawPuller2* self, AudioProcessContext* ctx)
{
    if (!self->mpCallback)
        return 0;

    const u32 ch = self->mbNumChannels;

    if (self->mbRestart)
    {
        ctx->mbChannelCount = ch;
        ctx->mNumSamples = 0;
        ctx->mfSampleRate = self->mfRate;
        self->mbRestart = 0;
        return 1;
    }

    const f32 gain = ctx->mfResampleGain;
    AudioChannelBuffer* oldDst = ctx->mpDstBuffer;
    AudioChannelBuffer* oldSrc = ctx->mpSrcBuffer;

    ctx->mbChannelCount = ch;
    ctx->mpSrcBuffer = oldDst;
    ctx->mpDstBuffer = oldSrc;
    ctx->mNumSamples = (s32)self->muFrameCount;
    ctx->mfSampleRate = self->mfRate;

    if (self->mpCallback(self->muFrameCount, g_mixScratch, gain, self->mpContext))
    {
        const AudioChannelBuffer* out = ctx->mpSrcBuffer;
        const u32 frames = self->muFrameCount;
        for (u32 i = 0; i < ch; ++i)
            memcpy(out->mpSamples + out->muStride * i, g_mixScratch + 4 * frames * i, 4 * frames);
        return 1;
    }
    return 0;
}

// =======================================================================================
// PeakingIir2 -- the 2nd-order peaking (bell) filter shape
// =======================================================================================
struct PeakingIir2 {
    char pad0[0x21];
    u8   mbChannelCount;    // +0x21
    char pad22[0x28 - 0x22];
    f32  mfCutoffFreq;      // +0x28
    char pad2c[0x30 - 0x2C];
    f32  mfGain;            // +0x30
    char pad34[0x38 - 0x34];
    f32  mfQ;               // +0x38
    char pad3c[0x40 - 0x3C];
    f32  mState[6][4];      // +0x40 .. +0x9F
    s32  mbActive;          // +0xA0
    f32  mfA1;              // +0xA4
    f32  mfA2;              // +0xA8
    f32  mfB0;              // +0xAC
    f32  mfB1;              // +0xB0
    f32  mfB2;              // +0xB4
    f32  mfLastOmega;       // +0xB8
    f32  mfLastGain;        // +0xBC
    f32  mfLastQ;           // +0xC0

    void CalculateFilterCoefficients(f32 omega, f32 gain, f32 q);  // 0x0114ee60
    int  Process(AudioProcessContext* ctx);                        // 0x0114ef10
};

// ---- the biquad kernel: 8 samples per iteration, state in self[0..3] ----------------
// @ 0x0114f100
void __fastcall Iir2Filter(f32* state, int /*edx*/, f32* dst, f32* src, const f32* coef)
{
    const f32 a1 = coef[0];
    const f32 a2 = coef[1];
    const f32 b0 = coef[2];
    const f32 b1 = coef[3];
    const f32 b2 = coef[4];

    f32 x1 = state[0];
    f32 x2 = state[1];
    f32 y1 = state[2];
    f32 y2 = state[3];

    const f32* end = src + 0x100;
    while (src < end)
    {
        const f32 x0 = src[0];
        const f32 x1n = src[1];
        const f32 y0 = (x0 * b0 + x1 * b1 + x2 * b2 + 1e-18f) - y1 * a1 - y2 * a2;

        const f32 x2n = src[2];
        const f32 y1o = (x1n * b0 + x0 * b1 + x1 * b2 + 1e-18f) - y0 * a1 - y1 * a2;

        const f32 x3 = src[3];
        const f32 x4 = src[4];
        const f32 x5 = src[5];
        const f32 y2o = (x2n * b0 + x1n * b1 + x0 * b2 + 1e-18f) - y1o * a1 - y0 * a2;
        const f32 y3 = (x3 * b0 + x2n * b1 + x1n * b2 + 1e-18f) - y2o * a1 - y1o * a2;
        const f32 y4 = (x4 * b0 + x3 * b1 + x2n * b2 + 1e-18f) - y3 * a1 - y2o * a2;
        const f32 y5 = (x5 * b0 + x4 * b1 + x3 * b2 + 1e-18f) - y4 * a1 - y3 * a2;

        const f32 x6 = src[6];
        const f32 y6 = (x6 * b0 + x5 * b1 + x4 * b2 + 1e-18f) - y5 * a1 - y4 * a2;

        const f32 x7 = src[7];
        const f32 y7 = (x7 * b0 + x6 * b1 + x5 * b2 + 1e-18f) - y6 * a1 - y5 * a2;

        dst[0] = y0;
        dst[1] = y1o;
        dst[2] = y2o;
        dst[3] = y3;
        dst[4] = y4;
        dst[5] = y5;
        dst[6] = y6;
        dst[7] = y7;

        x1 = x7;
        x2 = x6;
        y1 = y7;
        y2 = y6;

        src += 8;
        dst += 8;
    }

    state[0] = x1;
    state[1] = x2;
    state[2] = y1;
    state[3] = y2;
}

// @ 0x0114f4f0 -- clear the four-float per-channel IIR state
__declspec(noinline) void __fastcall ClearIirState(f32* state, int /*edx*/)
{
    state[0] = 0.0f;
    state[1] = 0.0f;
    state[2] = 0.0f;
    state[3] = 0.0f;
}

// @ 0x0114ee60
void PeakingIir2::CalculateFilterCoefficients(f32 omega, f32 gain, f32 q)
{
    const f32 c = cosf(omega);
    const f32 s = sinf(omega);

    const f32 sOver2Q = s / (q * 2.0f);
    const f32 A = sqrtf(gain);
    const f32 alpha = sOver2Q / A;
    const f32 k = 1.0f / (alpha + 1.0f);
    const f32 v13 = A * sOver2Q;

    mfA1 = k * (c * -2.0f);
    mfA2 = (1.0f - alpha) * k;
    mfB0 = (1.0f + v13) * k;
    mfB1 = k * (c * -2.0f);
    mfB2 = (1.0f - v13) * k;
}

// @ 0x0114ef10
int __cdecl PeakingIir2Process(PeakingIir2* self, AudioProcessContext* ctx)
{
    const f32 KF_TWO_PI = 6.2831855f;
    const f32 KF_OMEGA_HI = 3.1384511f;
    const f32 KF_OMEGA_LO = 0.003141593f;
    const f32 KF_Q_MIN = 0.2f;
    const f32 KF_Q_MAX = 20.0f;

    f32 omega = (self->mfCutoffFreq / ((AudioFormat*)ctx->mpFormat)->mfSampleRate) * KF_TWO_PI;
    if (omega < KF_OMEGA_LO)
        omega = KF_OMEGA_LO;
    if (omega > KF_OMEGA_HI)
        omega = KF_OMEGA_HI;

    const f32 gain = self->mfGain;

    if (gain == 1.0f)
    {
        if (self->mbActive == 1)
        {
            for (u32 ch = 0; ch < self->mbChannelCount; ++ch)
                ClearIirState(self->mState[ch], 0);
            self->mbActive = 0;
        }
        self->mfLastGain = self->mfGain;
        self->mfLastOmega = omega;
        self->mfLastQ = self->mfQ;
        return 1;
    }

    if (!self->mbActive)
        self->mbActive = 1;

    if (self->mfQ < KF_Q_MIN)
        self->mfQ = KF_Q_MIN;
    else if (self->mfQ > KF_Q_MAX)
        self->mfQ = KF_Q_MAX;

    if (omega != self->mfLastOmega || gain != self->mfLastGain || self->mfQ != self->mfLastQ)
    {
        self->CalculateFilterCoefficients(omega, gain, self->mfQ);
        self->mfLastOmega = omega;
        self->mfLastGain = self->mfGain;
        self->mfLastQ = self->mfQ;
    }

    AudioChannelBuffer* src = ctx->mpSrcBuffer;
    AudioChannelBuffer* dst = ctx->mpDstBuffer;
    for (u32 ch = 0; ch < self->mbChannelCount; ++ch)
        Iir2Filter(self->mState[ch], 0,
                   dst->mpSamples + dst->muStride * ch,
                   src->mpSamples + src->muStride * ch,
                   &self->mfA1);

    AudioChannelBuffer* dst2 = ctx->mpDstBuffer;
    AudioChannelBuffer* src2 = ctx->mpSrcBuffer;
    ctx->mpSrcBuffer = dst2;
    ctx->mpDstBuffer = src2;
    return 1;
}

// =======================================================================================
// Pause -- gate the block through, ramping the gain while the pause control crosses
// PC layout: +0x28 control, +0x30 gain, +0x4C/+0x50 sample counters,
// +0x54 requested samples (u16), +0x56 ramp remaining, +0x57 state, +0x58 discontinuity
// =======================================================================================
struct Pause {
    char pad0[0x21];
    u8   mbChannelCount;             // +0x21
    char pad22[0x28 - 0x22];
    f32  mfPauseControl;             // +0x28
    char pad2c[0x30 - 0x2C];
    f32  mfGain;                     // +0x30
    char pad34[0x4C - 0x34];
    u32  muSampleLimit;              // +0x4C
    u32  muSampleCursor;             // +0x50
    u16  mOutputSamplesRequested;    // +0x54
    u8   mSamplesRemaining;          // +0x56
    u8   mPauseState;                // +0x57
    u8   mDiscontinuity;             // +0x58
};

// @ 0x0114f510
int __cdecl PausePreProcess(Pause* self, int /*a2*/, char force, u32 length)
{
    self->mOutputSamplesRequested = (u16)length;

    if (force || self->mDiscontinuity)
    {
        self->mDiscontinuity = 1;
        if (self->mfPauseControl == 1.0f)
        {
            self->mPauseState = 0;
            self->muSampleCursor = self->muSampleLimit;
        }
        else
        {
            if (self->mfPauseControl != 0.0f)
                goto resume;
            self->mPauseState = 2;
        }
        self->mSamplesRemaining = 0;
    }

resume:
    if (self->mfPauseControl == 0.0f)
    {
        if (self->mPauseState == 0 || self->mPauseState == 1)
            self->mSamplesRemaining = 0x40;
        return (int)length;
    }

    switch (self->mPauseState)
    {
    case 2:
        self->mSamplesRemaining = 0x40;
        // fall through
    case 3:
    {
        u32 out = self->mSamplesRemaining;
        if ((s32)out > (s32)length)
            out = length;
        self->mOutputSamplesRequested = (u16)out;
        return (int)out;
    }
    case 1:
    {
        u32 out = self->mSamplesRemaining;
        if ((s32)out > (s32)length)
            out = length;
        self->mOutputSamplesRequested = (u16)out;
        return (int)out;
    }
    case 0:
        return 0;
    }
    return 0;
}

// @ 0x0114f5c0
int __cdecl PauseProcess(Pause* self, AudioProcessContext* ctx)
{
    AudioChannelBuffer* dst = ctx->mpDstBuffer;
    const f32 control = self->mfPauseControl;
    AudioChannelBuffer* src = ctx->mpSrcBuffer;

    if (control == 1.0f && self->mPauseState == 0)
    {
        if (self->muSampleCursor >= self->muSampleLimit)
            return 0;
        self->muSampleCursor += self->mOutputSamplesRequested;
        ctx->mNumSamples = (s32)self->mOutputSamplesRequested;
        for (u32 ch = 0; ch < self->mbChannelCount; ++ch)
            memset(src->mpSamples + src->muStride * ch, 0, 4 * self->mOutputSamplesRequested);
        return 1;
    }

    self->mDiscontinuity = 0;
    if (control != 0.0f || self->mPauseState != 2)
    {
        const u32 numSamples = (u32)ctx->mNumSamples;
        const u32 ramp = self->mSamplesRemaining;
        u32 rampCount = (u32)self->mSamplesRemaining;
        f32 step;

        if (control == 0.0f)
        {
            self->mPauseState = 2;
            if (rampCount > numSamples)
            {
                rampCount = numSamples;
                self->mPauseState = 3;
            }
            step = (1.0f - self->mfGain);
        }
        else
        {
            if (rampCount > numSamples)
            {
                rampCount = numSamples;
                self->mPauseState = 1;
            }
            else
            {
                self->mPauseState = 0;
                self->muSampleCursor = 0;
            }
            step = self->mfGain * -1.0f;
        }

        step = step / (f32)(s32)ramp;
        const u32 remaining = numSamples - rampCount;

        f32 lastGain = 2.0f;
        for (u32 ch = 0; ch < self->mbChannelCount; ++ch)
        {
            f32 gain = self->mfGain;
            lastGain = gain;
            f32* pSrc = src->mpSamples + src->muStride * ch;
            f32* pDst = dst->mpSamples + dst->muStride * ch;
            for (u32 i = 0; i < rampCount; ++i)
            {
                *pDst++ = *pSrc++ * gain;
                gain += step;
            }
            lastGain = gain;
            for (u32 i = 0; i < remaining; ++i)
                *pDst++ = *pSrc++;
        }

        self->mSamplesRemaining -= (u8)rampCount;
        if (self->mPauseState == 2)
            self->mfGain = 1.0f;
        else if (self->mPauseState == 0)
            self->mfGain = 0.0f;
        else
            self->mfGain = lastGain;
    }

    AudioChannelBuffer* tmp = ctx->mpDstBuffer;
    ctx->mpDstBuffer = ctx->mpSrcBuffer;
    ctx->mpSrcBuffer = tmp;
    return 1;
}
