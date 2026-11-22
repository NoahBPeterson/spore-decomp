// src/game/SPBake/Tessellator.cpp -- migrated from slice(s) s0114e990, s0114da70 by tools/migrate/rewrite.py
// Object file: SPBake/Tessellator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"
#include <string.h>
#include <math.h>
#include <xmmintrin.h>
#pragma function(memset)

// ---- items of slice s0114da70 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef float f32;
typedef double f64;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
namespace rw {
namespace audio {
namespace core {
struct AudioChannelBuffer {
    char pad0[4];
    f32* mpSamples; // +0x04
    char pad8[0x0E - 0x08];
    u16  muStride;  // +0x0E
};
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
class Resample;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct PosDst { u32 pos; f32* dst; };
}
}
}
namespace rw {
namespace audio {
namespace core {
union U32F32 { u32 u; f32 f; };
}
}
}
namespace rw {
namespace audio {
namespace core {
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

    void SetResampleIncrement(f32 ratio);                   // 0x0114e860
    int  PreProcess(AudioProcessContext* ctx, s32 a3, s32 outputSamples); // 0x0114e8f0
};
}
}
}
// ---- items of slice s0114da70 end

// ---- items of slice s0114e990 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma function(memcpy)
struct AudioChannelBuffer_s0114_e990 {
    char  pad0[4];
    f32*  mpSamples;   // +0x04
    char  pad8[0x0E - 0x08];
    u16   muStride;    // +0x0E
};
struct AudioProcessContext_s0114_e990 {
    char  pad00000[0x30000];
    char  pad30000[0x0C];
    AudioChannelBuffer_s0114_e990* mpSrcBuffer;  // +0x3000C
    AudioChannelBuffer_s0114_e990* mpDstBuffer;  // +0x30010
    AudioChannelBuffer_s0114_e990* mpAuxBuffer;  // +0x30014
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
struct PosDst_s0114_e990 { u32 pos; f32* dst; };
PosDst_s0114_e990 InterpRamp(u32 pos, s32 step, u32 end, const f32* src, f32* dst); // 0x0114e780
class Resample_s0114_e990 { public:
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
// ---- items of slice s0114e990 end

// @ 0x0114e780
namespace rw { namespace audio { namespace core {
PosDst InterpRamp(u32 pos, s32 step, u32 end, const f32* src, f32* dst)
{
    if (pos < end) {
        static volatile const f32 kFracBias = -128.0f;  // 0xC3000000
        s32 limit = (s32)(end - (u32)step);         // end - step
        if ((s32)pos < limit) {
            do {
                const u32 whole = pos >> 16;
                const f32 s0 = src[whole];
                const f32 s1 = src[whole + 1];
                U32F32 cv; cv.u = (pos & 0xFFFFu) | 0x43000000u;
                const f32 frac = kFracBias + cv.f;
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
            s0 = s0 + (s1 - s0) * (kFracBias + cv.f);
        }
        *dst++ = s0;
        pos += (u32)step;
    }
    PosDst r = { pos, dst };
    return r;
}
}}}  // namespace rw::audio::core

// @ 0x0114e860
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core

// @ 0x0114e8f0
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core

// @ 0x0114e990
int __cdecl ResampleProcess(Resample_s0114_e990* self, AudioProcessContext_s0114_e990* ctx, s32 a3)
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

        AudioChannelBuffer_s0114_e990* srcBuf = ctx->mpSrcBuffer;
        AudioChannelBuffer_s0114_e990* dstBuf = ctx->mpDstBuffer;
        const s32 step = self->miIncr16_16;

        u32 end = (u32)step * (u32)maxOut + (u32)self->miAcc16_16;
        const u32 cap = numSamples * 0x10000 - 0xFFFF;
        if (end > cap)
            end = cap;

        u32 pos = 0;
        f32* dstLast = 0;
        f32* lastDstEnd = 0;

        for (u32 ch = 0; ch < channels; ++ch)
        {
            f32* src = srcBuf->mpSamples + srcBuf->muStride * ch;
            f32* dst = dstBuf->mpSamples + dstBuf->muStride * ch;
            f32* dstEnd = dst + maxOut;
            lastDstEnd = dstEnd;
            // the original re-reads the accumulator for every channel (it only writes the
            // object field back after the whole channel loop)
            u32 p = (u32)self->miAcc16_16;

            if (dst != dstEnd && p + 0x20000 <= 0x10000)
            {
                const f32 prev = self->mfRampPrev;
                const f32 cur  = self->mfRampCur;
                const f32 diff = cur - prev;
                p += 0x20000;
                do
                {
                    *dst = ((f32)(s32)p * kFrac) * diff + prev;
                    p += (u32)step;
                    ++dst;
                    if (p > 0x10000)
                        break;
                } while (dst != dstEnd);
                p -= 0x20000;
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

                if (dst != dstEnd && p > 0xFFFF0000)
                {
                    const f32 first = src[0];
                    const f32 diff = first - oldCur;
                    p += 0x10000;
                    do
                    {
                        *dst = ((f32)(s32)p * kFrac) * diff + oldCur;
                        p += (u32)step;
                        ++dst;
                        if (p > 0xFFFF)
                            break;
                    } while (dst != dstEnd);
                    p -= 0x10000;
                }

                PosDst_s0114_e990 r = InterpRamp(p, step, end, src, dst);
                p = r.pos;
                dst = r.dst;
            }

            pos = p;
            dstLast = dst;
        }

        s32 acc = (s32)pos - (s32)numSamples * 0x10000;
        if ((u32)(acc + 0x80000000) < 0x7ffe0000)
            acc = 0;
        self->miAcc16_16 = acc;

        const s32 written = maxOut - (s32)((lastDstEnd - dstLast) >> 2);

        AudioChannelBuffer_s0114_e990* in = ctx->mpSrcBuffer;
        AudioChannelBuffer_s0114_e990* out = ctx->mpDstBuffer;
        ctx->mpDstBuffer = in;
        ctx->mpSrcBuffer = out;
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
