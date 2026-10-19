// src/game/SPAudio/AudioPluginDelay.cpp -- migrated from slice(s) s00a14a60 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioPluginDelay.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"
#include <math.h>
#include <string.h>
#include <stddef.h>

// ---- items of slice s00a14a60 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace audio {
namespace core {
struct ChanBuf { char pad0[4]; float* data; char pad8[6]; uint16_t stride; };   // +4 data, +0xe stride (floats/row)
}
}
}
namespace rw {
namespace audio {
namespace core {
struct MixCfg { char pad[0xc]; float rate; };                                    // +0xc sample rate
}
}
}
namespace rw {
namespace audio {
namespace core {
struct MixCtx {
    char pad[0x3000c];
    ChanBuf* bufA;      // +0x3000c  input
    ChanBuf* bufB;      // +0x30010  output
    char pad14[4];
    MixCfg* cfg;        // +0x30018
    char pad1c[4];
    int count;          // +0x30020  samples per block
    char pad24[4];
    float tempo;        // +0x30028
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct System_s00a1_4a60 {
    void* Alloc(uint32_t size, const char* name, uint32_t align, uint32_t flags);   // 0x0112c820
    void Free(void* p, uint32_t flags);                                             // 0x0112c850
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern System_s00a1_4a60* gSystem;                          // 0x016e61a8
}
}
}
namespace rw {
namespace audio {
namespace core {
void __cdecl Memset32(void* dst, int value, unsigned count);   // 0x0092cb00
}
}
}
namespace rw {
namespace audio {
namespace core {
struct EffectOwner { char pad[0x28]; float mTailTime; };   // accumulated tail length of all effects
}
}
}
namespace rw {
namespace audio {
namespace core {
struct MultiDelayLine {           // 0xc bytes per voice at +0x24
    float* mpBuffer;              // +0x00 allocated delay line
    float* mpPos;                 // +0x04 read/write position
    int mSize;                    // +0x08 floats
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct MultiDelayVoice {          // 0x10 bytes per voice at +0x78
    float mDelay;                 // +0x00 seconds, clamped to [0, 60]
    float pad04;
    float mFeedback;              // +0x08 (clamped to [0, 0.999] only for the tail estimate)
    float pad0c;
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct MultiDelay {
    static int Process(MultiDelay* fx, MixCtx* ctx);   // 0x00a15220
    char pad00[8];
    EffectOwner* mpOwner;         // +0x08
    char pad0c[0xc];
    float mTail;                  // +0x18
    char pad1c[5];
    uint8_t mVoices;              // +0x21
    char pad22[2];
    MultiDelayLine mLines[6];     // +0x24
    char pad6c[4];
    float mMix;                   // +0x70 wet/dry
    char pad74[4];
    MultiDelayVoice mVoice[6];    // +0x78
};
}
}
}
namespace rw {
namespace audio {
namespace core {
#define DELAY_SCAN()                                                    \
    {                                                                   \
        float a = p[0];                                                 \
        if (a < 0.0f) a = 0.0f; else if (a > 60.0f) a = 60.0f;          \
        float b = p[2];                                                 \
        p += 2;                                                         \
        if (b < 0.0f) b = 0.0f; else if (b > 0.999f) b = 0.999f;        \
        p += 2;                                                         \
        if (maxDelay < a) maxDelay = a;                                 \
        if (maxFeedback < b) maxFeedback = b;                           \
    }
}
}
}
namespace rw {
namespace audio {
namespace core {
#define DELAY_STEP(K)                                                   \
    {                                                                   \
        float delayed = *pos;                                           \
        float input = src[K];                                           \
        *pos = delayed * feedback + input;                              \
        if (wet == 0.0f) {                                              \
            dst[K] = input;                                             \
        } else if (wet == 1.0f) {                                       \
            dst[K] = delayed;                                           \
        } else {                                                        \
            dst[K] = input * dry + delayed * wet;                       \
        }                                                               \
        pos++;                                                          \
        if (pos >= end) pos = s->mpBuffer;                              \
    }
}
}
}
// ---- items of slice s00a14a60 end

// @ 0x00a15220
namespace rw { namespace audio { namespace core {
int MultiDelay::Process(MultiDelay* fx, MixCtx* ctx)
{
    int voices = fx->mVoices;
    float maxDelay = 0.0f;
    float maxFeedback = 0.0f;
    const float* p = &fx->mVoice[0].mDelay;
    int i = 0;
    if (voices >= 4) {
        int g = ((unsigned)(voices - 4) >> 2) + 1;
        i = g * 4;
        do {
            DELAY_SCAN()
            DELAY_SCAN()
            DELAY_SCAN()
            DELAY_SCAN()
        } while (--g != 0);
    }
    if (i < voices) {
        int r = voices - i;
        do {
            DELAY_SCAN()
        } while (--r != 0);
    }

    if (maxDelay > 0.0f) {
        double ratio = log(0.01f) / log(maxFeedback);
        double tail = ratio * maxDelay;
        tail = tail * ctx->cfg->rate;
        tail = tail * ctx->tempo;
        fx->mpOwner->mTailTime = (float)((tail - fx->mTail) + fx->mpOwner->mTailTime);
        fx->mTail = (float)tail;

        int count = ctx->count;
        float wet = fx->mMix;
        ChanBuf* in = ctx->bufA;
        ChanBuf* out = ctx->bufB;
        float dry = 1.0f - wet;
        const MultiDelayVoice* vp = &fx->mVoice[0];
        for (int v = 0; v < voices; v++) {
            MultiDelayLine* s = &fx->mLines[v];
            float* src = in->data + in->stride * v;
            float* dst = out->data + out->stride * v;
            float delay = vp->mDelay;
            if (delay < 0.0f) delay = 0.0f; else if (delay > 60.0f) delay = 60.0f;
            float feedback = vp->mFeedback;
            vp++;
            uint32_t size = (uint32_t)((ctx->cfg->rate * ctx->tempo) * delay);
            if (s->mpBuffer && (uint32_t)s->mSize != size) {
                gSystem->Free(s->mpBuffer, 0);
                s->mpBuffer = 0;
            }
            if (size == 0) {
                memcpy(dst, src, count * 4);
                continue;
            }
            if (!s->mpBuffer) {
                s->mpBuffer = (float*)gSystem->Alloc(size * 4, "rw::audio::core::MultiDelay::DelayBuffer", 4, 0);
                if (s->mpBuffer) {
                    Memset32(s->mpBuffer, 0, size);
                    s->mpPos = s->mpBuffer;
                    s->mSize = (int)size;
                }
            }
            if (!s->mpBuffer)
                continue;
            float* end = s->mpBuffer + s->mSize;
            float* pos = s->mpPos;
            int j = 0;
            if (count >= 4) {
                int g = ((unsigned)(count - 4) >> 2) + 1;
                j = g * 4;
                do {
                    DELAY_STEP(0) DELAY_STEP(1) DELAY_STEP(2) DELAY_STEP(3)
                    src += 4;
                    dst += 4;
                } while (--g != 0);
            }
            if (j < count) {
                int r = count - j;
                do {
                    DELAY_STEP(0)
                    src++;
                    dst++;
                } while (--r != 0);
            }
            s->mpPos = pos;
        }
        ChanBuf* t = ctx->bufB;
        ctx->bufB = ctx->bufA;
        ctx->bufA = t;
    }
    return 1;
}
}}}  // namespace rw::audio::core
