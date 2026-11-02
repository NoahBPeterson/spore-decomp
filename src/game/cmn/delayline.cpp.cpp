// src/game/cmn/delayline.cpp.cpp -- migrated from slice(s) s0114cb60 by tools/migrate/rewrite.py
// Object file: cmn/delayline.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <xmmintrin.h>
#pragma function(memcpy)

// ---- items of slice s0114cb60 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
class System_s0114_cb60 { public:
    char** mpObjectTable; // +0x00
    void* Alloc(u32 size, const char* tag, int flags, int align); // thiscall on the singleton 0x0112c820
    void  Free(void* p, int flags);  // 0x0112c850 (rw::audio::core::System::Free)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern System_s0114_cb60* g_pSystem; // DAT_016e61a8 -- pointer to the shared rwaudio System
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

// @ 0x0114d7b0
namespace rw { namespace audio { namespace core {
bool DelayLine::Init(s32 channels, s32 maxDelaySamples, s32 readLength)
{
    s32 delay = maxDelaySamples;
    if (delay <= readLength + 255)
        delay = readLength + 255;

    const u32 capacity = ((u32)(delay + 0x20) & 0xFFFFFFE0u) + ((u32)(readLength + 0x1E) & 0xFFFFFFE0u);

    void* pRing = 0;
    if (delay != 0) {
        pRing = g_pSystem->Alloc(4u * capacity * (u32)channels, "rw::audio::core::DelayLine::DelayBuffer", 0x80, 0);
        if (!pRing)
            return false;
    }

    miMaxDelaySamples = delay;
    miReadLength = readLength;
    miGuardSamples = 0;
    miWritePhase = 0;
    miChannelCount = channels;
    miCapacity = (s32)capacity;
    miAvailableSamples = (s32)capacity;
    mpBuffer = (f32*)pRing;
    return true;
}
}}}  // namespace rw::audio::core

// @ 0x0114d840
namespace rw { namespace audio { namespace core {
bool DelayLine::Resize(s32 maxDelaySamples)
{
    if (!mpBuffer)
        return Init(miChannelCount, maxDelaySamples, miReadLength);

    bool ok = true;
    const s32 newCapacity = ((maxDelaySamples + 0x20) & ~31) + miGuardSamples;

    if (miCapacity < newCapacity) {
        f32* pNew = (f32*)g_pSystem->Alloc(4u * (u32)miChannelCount * (u32)newCapacity,
                                           "rw::audio::core::DelayLine::DelayBuffer", 0x80, 0);
        if (!pNew)
            return false;

        f32* pChannelDst = pNew;
        for (s32 channel = 0; channel < miChannelCount; ++channel) {
            ChannelPointers old;
            CalcChannelPointers(&old, channel, 0);

            const s32 clean = miCleanCursor;
            const f32* pSrc = WrapCursor(&old, clean);
            f32* const pBody = pChannelDst + (newCapacity - miGuardSamples);
            f32* const pBodyStart = pBody - clean;

            s32 first = clean;
            const s32 tail = (s32)(old.mpLoopEnd - pSrc);
            if (clean >= tail)
                first = tail;

            memcpy(pBodyStart, pSrc, (size_t)(4 * first));
            memcpy(pBodyStart + first, old.mpStart, (size_t)(4 * (miCleanCursor - first)));
            memcpy(pChannelDst, pBody, (size_t)(4 * miGuardSamples));

            pChannelDst += newCapacity;
        }

        if (mpBuffer)
            g_pSystem->Free(mpBuffer, 0);

        miWritePhase = miGuardSamples;
        mpBuffer = pNew;
        miCapacity = newCapacity;
    }

    miMaxDelaySamples = maxDelaySamples;
    return ok;
}
}}}  // namespace rw::audio::core

// @ 0x0114d9f0
namespace rw { namespace audio { namespace core {
void DelayLine::CalcChannelPointers(ChannelPointers* pOut, s32 channel, s32 offset) const
{
    f32* const pStart = mpBuffer + (u32)channel * (u32)miCapacity;
    pOut->mpStart = pStart;
    pOut->mpEnd = pStart + miCapacity;
    pOut->mpLoopEnd = pOut->mpEnd - miGuardSamples;
    pOut->mpCursor = pStart + ((miWritePhase + offset) % miCapacity + miGuardSamples);
}
}}}  // namespace rw::audio::core

// @ 0x0114da40
namespace rw { namespace audio { namespace core {
f32* DelayLine::WrapCursor(const ChannelPointers* pPtrs, s32 backOffset) const
{
    f32* p = pPtrs->mpCursor - backOffset;
    if (p < pPtrs->mpStart || pPtrs->mpEnd <= p)
        p += (miCapacity - miGuardSamples);
    return p;
}
}}}  // namespace rw::audio::core
