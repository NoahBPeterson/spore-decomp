// src/game/SPAudio/AudioPluginChorus.cpp -- migrated from slice(s) s00a14a60 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioPluginChorus.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
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
extern const int gSineTable[];                   // 0x01449558, 16.16 fixed point sine, 4096 entries
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
struct ChorusVoice {              // 0x28 bytes per voice at +0xa0
    float mMix;                   // +0x00 wet/dry
    float pad04;
    float mDelay;                 // +0x08 seconds, clamped to [0, 1]
    float pad0c;
    float mFeedback;              // +0x10 clamped to [0, 0.999]
    float pad14;
    float mRate;                  // +0x18 LFO rate (Hz)
    float pad1c;
    float mDepth;                 // +0x20 LFO depth (samples)
    float pad24;
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct ChorusLine {               // 0x14 bytes per voice at +0x24
    float* mpBuffer;              // +0x00 allocated delay line
    float* mpWrite;               // +0x04
    float* mpRead;                // +0x08
    int mSize;                    // +0x0c floats
    uint32_t mPhase;              // +0x10 LFO phase, 0..0x0fffffff
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Chorus {
    static int Process(Chorus* fx, MixCtx* ctx);   // 0x00a14a60
    char pad00[8];
    EffectOwner* mpOwner;         // +0x08
    char pad0c[0xc];
    float mTail;                  // +0x18
    char pad1c[5];
    uint8_t mVoices;              // +0x21
    char pad22[2];
    ChorusLine mLines[6];         // +0x24
    char pad9c[4];
    ChorusVoice mVoice[6];        // +0xa0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
#define CHORUS_SCAN()                                                   \
    {                                                                   \
        float a = p[0];                                                 \
        if (a < 0.0f) a = 0.0f; else if (a > 1.0f) a = 1.0f;            \
        float b = p[2];                                                 \
        p += 2;                                                         \
        if (b < 0.0f) b = 0.0f; else if (b > 0.999f) b = 0.999f;        \
        p += 8;                                                         \
        if (maxDelay < a) maxDelay = a;                                 \
        if (maxFeedback < b) maxFeedback = b;                           \
    }
}
}
}
// ---- items of slice s00a14a60 end

// @ 0x00a14a60
namespace rw { namespace audio { namespace core {
int Chorus::Process(Chorus* fx, MixCtx* ctx)
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
            CHORUS_SCAN()
            CHORUS_SCAN()
            CHORUS_SCAN()
            CHORUS_SCAN()
        } while (--g != 0);
    }
    if (i < voices) {
        int r = voices - i;
        do {
            CHORUS_SCAN()
        } while (--r != 0);
    }

    if (maxDelay > 0.0f) {
        double tail = log(0.01f) / log(maxFeedback) * maxDelay * ctx->cfg->rate * ctx->tempo;
        fx->mpOwner->mTailTime = (float)((tail - fx->mTail) + fx->mpOwner->mTailTime);
        fx->mTail = (float)tail;

        int count = ctx->count;
        ChanBuf* in = ctx->bufA;
        ChanBuf* out = ctx->bufB;
        for (int v = 0; v < voices; v++) {
            const ChorusVoice& cv = fx->mVoice[v];
            ChorusLine* s = &fx->mLines[v];
            float* src = in->data + in->stride * v;
            float* dst = out->data + out->stride * v;
            float delay = cv.mDelay;
            if (delay == 0.0f) {
                memcpy(dst, src, count * 4);
                continue;
            }
            float rate = ctx->cfg->rate;
            float wet = cv.mMix;
            float dry = 1.0f - wet;
            float feedback = cv.mFeedback;
            float modRate = cv.mRate;
            float depth = cv.mDepth;
            int depthInt = (int)depth;
            uint32_t phaseInc = (uint32_t)(((modRate / rate) * 4096.0f) * 65536.0f);
            if (modRate == 0.0f || depth == 0.0f) {
                modRate = 0.0f;
                depth = 0.0f;
            }
            float t = rate * ctx->tempo;
            double c1 = ceil((double)(t * modRate));
            double c2 = ceil((double)(depth + depth));
            double c3 = ceil((double)(t * delay));
            uint32_t size = (uint32_t)(((c3 + (float)c2) + (float)c1) + 1.0);
            if (s->mpBuffer && (uint32_t)s->mSize != size) {
                gSystem->Free(s->mpBuffer, 0);
                s->mpBuffer = 0;
            }
            if (!s->mpBuffer) {
                s->mpBuffer = (float*)gSystem->Alloc(size * 4, "rw::audio::core::Chorus::DelayBuffer", 4, 0);
                Memset32(s->mpBuffer, 0, size);
                s->mpWrite = s->mpBuffer;
                double rd = ceil(((float)c1 + depth) + 1.0);
                s->mSize = (int)size;
                s->mPhase = 0xc000000;
                s->mpRead = s->mpBuffer + (uint32_t)rd;
                if (!s->mpBuffer)
                    continue;
            }
            float* buf = s->mpBuffer;
            float* end = buf + s->mSize;
            float* wp = s->mpWrite;
            float* rp = s->mpRead;
            for (int k = 0; k < count; k++) {
                if (wp >= end) wp = s->mpBuffer;
                if (rp >= end) rp = s->mpBuffer;
                float delayed;
                if (modRate == 0.0f || depth == 0.0f) {
                    delayed = *rp;
                } else {
                    int m = gSineTable[s->mPhase >> 16] * depthInt;
                    int whole = m >> 16;
                    float frac = (float)(m & 0xffff) * (1.0f / 65536.0f);
                    if (whole < 0) frac = 1.0f - frac;
                    float* q = rp + whole;
                    if (q >= end) q -= size;
                    if (q < s->mpBuffer) q += size;
                    float* q1 = q + 1;
                    if (q1 == end) q1 = s->mpBuffer;
                    delayed = (*q1 - *q) * frac + *q;
                    s->mPhase += phaseInc;
                    while (s->mPhase >= 0x10000000)
                        s->mPhase -= 0x10000000;
                }
                float input = src[k];
                *wp = delayed * feedback + input;
                if (wet == 0.0f) {
                    dst[k] = input;
                } else if (wet == 1.0f) {
                    dst[k] = delayed;
                } else {
                    dst[k] = input * dry + delayed * wet;
                }
                wp++;
                rp++;
            }
            s->mpRead = rp;
            s->mpWrite = wp;
        }
        ChanBuf* t = ctx->bufB;
        ctx->bufB = ctx->bufA;
        ctx->bufA = t;
    }
    return 1;
}
}}}  // namespace rw::audio::core
