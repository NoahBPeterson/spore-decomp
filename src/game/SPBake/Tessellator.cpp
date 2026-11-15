// src/game/SPBake/Tessellator.cpp -- migrated from slice(s) s0114da70 by tools/migrate/rewrite.py
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
