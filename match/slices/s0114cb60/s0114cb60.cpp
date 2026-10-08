// rw::audio::core slice s0114cb60 -- Send::Process, the Resample 16.16 linear-interpolation
// kernel, Scp0::Process, Route::Process, ReverbModel1::Process, and the DelayLine members.
//
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE  (RenderWare 4 core was built with VC .NET 2003 +
// /LTCG and scalar SSE; see docs/matching.md "Toolchain").  Functions that call other
// functions cannot be byte-exact from a single-object compile (LTCG kept values live across
// calls); the leaves are.
//
// Class layouts are the real X360/dev-PDB ones (work/ext/gh_b5 reference, member order is
// authoritative), grounded against the retail disassembly offsets.
#include "../../include/types.h"
#include <string.h>

typedef float f32;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

namespace rw {
namespace audio {
namespace core {

// ---------------------------------------------------------------------------------------
// Shared little views
// ---------------------------------------------------------------------------------------
struct AudioChannelBuffer {
    char  pad0[4];
    f32*  mpSamples;   // +0x04 channel-0 sample base
    char  pad8[0x0E - 0x08];
    u16   muStride;    // +0x0E inter-channel stride in samples
};

struct AudioProcessContext {
    char pad0[0x30000];
    char pad30000[0x0C];
    AudioChannelBuffer* mpSrcBuffer;     // +0x3000C
    AudioChannelBuffer* mpDstBuffer;     // +0x30010
    char  pad14[4];
    char* mpFormat;                      // +0x30018 (rate at +0x0C)
    char  pad1c[4];
    s32   mNumSamples;                   // +0x30020
    f32   mfField24;                     // +0x30024
    f32   mfResampleGain;                // +0x30028
    s32   mChannelCount;                 // +0x3002C
};

struct System {
    char** mpObjectTable; // +0x00
    void* Alloc(u32 size, const char* tag, int flags, int align); // thiscall on the singleton
    void  Free(void* p, int flags);
};
extern System* g_pSystem; // DAT_016e61a8 -- pointer to the shared rwaudio System

// ---------------------------------------------------------------------------------------
// SubMixConnector (embedded in Send at +0x30, Route at +0x24)
// ---------------------------------------------------------------------------------------
struct SubMix {
    char pad0[0x8C];
    u16 muRefCount; // +0x8C
};

struct SubMixConnector {
    char  pad0[8];
    f32*  mpSubMixBuffer;     // +0x08
    SubMix* mpSubMix;         // +0x0C
    u8    mNumSubMixChannels; // +0x10
    char  pad11[3];

    f32* GetSubMixBuffer(); // 0x011374e0
};

// ---------------------------------------------------------------------------------------
// Send -- 0x0114cb60 = Send::Process
// ---------------------------------------------------------------------------------------
struct Send {
    char pad0[0x0C];
    void* mpAttributes;       // +0x0C
    char pad10[0x20 - 0x10];
    u8   mbFlag20;            // +0x20 input channel count
    char pad21[0x28 - 0x21];
    f32  mfGain;              // +0x28
    char pad2c[0x30 - 0x2C];
    SubMixConnector mSubMixConnector; // +0x30
    f32  mDeClickValue[6];    // +0x44
    f32  mfCurrentGain;       // +0x5C
    u8   mbNeedReset;         // +0x60

    static int Process(Send* self, AudioProcessContext* ctx, char resetRamp); // 0x0114cb60
};

#define KI_MIXER_FRAME_SIZE 256

void ReChannelGainMix(f32** dst, f32** src, f32 gain, s32 dstCh, s32 srcCh, s32 count); // 0x0115d470
void ReChannelGainMixRamp(f32** dst, f32** src, f32 gain, f32 prevGain, s32 dstCh, s32 srcCh, s32 count); // 0x0115d500

// @ 0x0114cb60
int Send::Process(Send* self, AudioProcessContext* ctx, char resetRamp)
{
    if (resetRamp || self->mbNeedReset) {
        self->mbNeedReset = 0;
        self->mfCurrentGain = self->mfGain;
    }

    if (self->mfGain != self->mfCurrentGain || self->mfCurrentGain != 0.0f) {
        const u32 numSubMixChannels = self->mSubMixConnector.mNumSubMixChannels;
        if (numSubMixChannels == 0) {
            self->mbNeedReset = 1;
            return 1;
        }

        const u32 inputChannels = self->mbFlag20;
        f32* const pSubMixBuffer = self->mSubMixConnector.GetSubMixBuffer();
        AudioChannelBuffer* srcBuffer = ctx->mpSrcBuffer;

        f32* local[12];

        for (u32 c = 0; c < inputChannels; ++c)
            local[c] = srcBuffer->mpSamples + srcBuffer->muStride * c;

        for (u32 i = 0; i < numSubMixChannels; ++i)
            local[6 + i] = pSubMixBuffer + KI_MIXER_FRAME_SIZE * i;

        if (self->mfGain == self->mfCurrentGain)
            ReChannelGainMix(local + 6, local, self->mfGain, numSubMixChannels, inputChannels,
                             KI_MIXER_FRAME_SIZE);
        else
            ReChannelGainMixRamp(local + 6, local, self->mfGain, self->mfCurrentGain,
                                 numSubMixChannels, inputChannels, KI_MIXER_FRAME_SIZE);

        self->mfCurrentGain = self->mfGain;

        for (u32 c = 0; c < inputChannels; ++c)
            self->mDeClickValue[c] = local[c][KI_MIXER_FRAME_SIZE - 1] * self->mfGain;
    }

    return 1;
}

// ---------------------------------------------------------------------------------------
// The Resample 2-tap 16.16 linear-interpolation kernel.  0x0114cd30.
//   0x0114cd30(accWhole*, count, src, dst, accFrac*) -- LTCG register ABI.
// ---------------------------------------------------------------------------------------
// @ 0x0114cd30
void LinearInterpolate(u32 frames, const f32* pSrc, f32* pDst, u32* pAccWhole, u32* pAccFrac,
                       u32 inc)
{
    u32 whole = *pAccWhole;
    u32 frac = *pAccFrac >> 16;

    for (u32 i = 0; i < frames; ++i) {
        const f32 s0 = pSrc[whole];
        const f32 s1 = pSrc[whole + 1];
        const f32 t = (f32)(s32)frac * 1.5258e-05f; // flt_14ce5c8 (rounded 1/65536)
        pDst[i] = (s1 - s0) * t + s0;

        const u32 phase = frac + inc;
        whole += (phase >> 16);
        frac = phase & 0xFFFFu;
    }
    *pAccFrac = frac << 16;
    *pAccWhole = whole;
}

// ---------------------------------------------------------------------------------------
// Scp0::Process -- descriptor guid 'Scp0'.  0x0114ceb0.  Resample-shaped converter.
// ---------------------------------------------------------------------------------------
s32 Scp0MixChannels(s32* pDst, s32* pSrc, f32 gain, s32 dstCh, s32 srcCh, s32 frame); // 0x0112d590

struct Scp0 {
    char pad0[4];
    void* mpSystem;           // +0x04 (System; its first field is the stack allocator table)
    char pad8[0x21 - 0x08];
    u8   mbChannelCount;      // +0x21
    char pad22[0x48 - 0x22];
    f32  mfInputRate;         // +0x48
    s32  miField4C;           // +0x4C
    s32  miField50;           // +0x50
    s32  miField54;           // +0x54 (non-zero => active)
    char pad58[0x5C - 0x58];
    f32  mfRatio;             // +0x5C
    s32  miField60;           // +0x60
    s32  miIncr16_16;         // +0x64
    s32  miAcc16_16;          // +0x68
    s32  miField6C;           // +0x6C
    s32  miField70;           // +0x70
    u16  muField74;           // +0x74
    u16  muField76;           // +0x76
    s32  miField78;           // +0x78
    u8   mbChannelsOut;       // +0x7C
    u8   mbField7D;           // +0x7D

    static int Process(Scp0* self, AudioProcessContext* ctx); // 0x0114ceb0
};

// @ 0x0114ceb0
int Scp0::Process(Scp0* self, AudioProcessContext* ctx)
{
    if (self->miField54 == 0)
        return 1;

    u32 uNumChannels = self->mbChannelCount;
    f32 fRate = *(f32*)(ctx->mpFormat + 0x0C);
    AudioChannelBuffer* pSrc = ctx->mpSrcBuffer;
    u32 uCount = (u32)self->miField4C;

    s32 aChan[12];
    s32 aHist[12];
    for (int i = 0; i < 12; ++i) { aChan[i] = 0; aHist[i] = 0; }

    if (uNumChannels != 0) {
        for (u32 i = 0; i < uNumChannels; ++i)
            aChan[i] = (s32)(pSrc->mpSamples + pSrc->muStride * i);
    }

    // The original reads the stack-allocator cursor through the System cached at self+0x04:
    // cursor = *(*self->mpSystem + 0x0C) (the allocator table's 4th dword).
    void* pSystem = *(void**)((char*)self + 4);
    s32* pAllocTop = (s32*)(*(s32*)pSystem + 0x0C); // StackAllocator cursor

    if (uNumChannels != uCount) {
        s32 saved = *pAllocTop;
        s32 body = saved - (s32)(uCount * 0x400);
        *pAllocTop = body;
        if (uCount != 0) {
            for (u32 i = 0; i < uCount; ++i)
                aHist[i] = body + (s32)(i * 0x400);
        }
        Scp0MixChannels(aHist, aChan, 1.0f, (s32)uCount, (s32)uNumChannels, 0x100);
        for (u32 i = 0; i < uCount; ++i)
            aChan[i] = aHist[i];
    }

    if (fRate != self->mfInputRate) {
        f32 ratio = fRate / self->mfInputRate;
        if (self->mfRatio != ratio) {
            s32 inc = (s32)(ratio * 65536.0f);
            if (inc > 0x40000)
                inc = 0x40000;
            self->mfRatio = ratio;
            self->miIncr16_16 = inc;
        }

        s32 alloc1 = *pAllocTop;
        s32 histTop = alloc1 - 0x480;
        *pAllocTop = histTop;
        s32 alloc2 = *pAllocTop;
        s32 scratch = alloc2 - (s32)((((u32)self->miField4C * (u32)self->miField60 * 4) + 0x7F) & ~0x7Fu);
        *pAllocTop = scratch;

        s32 destEnd = (s32)self->mbChannelsOut + 0x100;
        if (uCount != 0) {
            for (u32 i = 0; i < uCount; ++i)
                aHist[i] = scratch + (s32)(i * self->miField60 * 4);
        }

        char* pIn = (char*)self + self->muField74;
        s32 nAvail = destEnd - (s32)self->mbField7D + 1;
        s32 blockCount;
        if (nAvail < 1)
            blockCount = 0;
        else if (self->miIncr16_16 == 0)
            blockCount = 0x2000;
        else
            blockCount = (s32)((((u32)nAvail << 16) - (u32)self->miAcc16_16 - 1u) / (u32)self->miIncr16_16);

        for (u32 blk = 0; blk < uCount; ++blk) {
            for (u32 i = 0; i < self->mbChannelsOut; ++i)
                *(f32*)(histTop + 4 * i) = *(f32*)pIn;
            pIn += 4 * self->mbChannelsOut;
            memcpy((void*)(histTop + 4 * self->mbChannelsOut), (void*)aChan[blk], 0x400);

            u32 acc = (u32)self->miAcc16_16 << 16;
            s32 whole = 0;
            LinearInterpolate((u32)(destEnd - 0x100), (f32*)(histTop), (f32*)(aHist[blk]),
                              (u32*)&whole, &acc, (u32)self->miIncr16_16);
            (void)blockCount; (void)aHist;
        }
        self->mfInputRate = fRate;
    }

    return 1;
}

// ---------------------------------------------------------------------------------------
// Route -- descriptor guid 'Rou0'.  0x0114d350 = Route::Process.
// ---------------------------------------------------------------------------------------
struct Route {
    char pad0[0x24];
    SubMixConnector mSubMixConnector; // +0x24
    f32  mDeClickValue[6];            // +0x38
    u8   mau8Gain[3];                 // +0x50 [0]=sourceStart [1]=targetStart [2]=numChannels
    char pad53;

    static int Process(Route* self, AudioProcessContext* ctx, char resetRamp); // 0x0114d350
};

void MixWithGain(f32* dst, const f32* src, f32 gain, s32 count); // 0x011342c0

// @ 0x0114d350
int Route::Process(Route* self, AudioProcessContext* ctx, char /*resetRamp*/)
{
    if (self->mSubMixConnector.mNumSubMixChannels == 0)
        return 1;

    f32* destination = self->mSubMixConnector.GetSubMixBuffer() +
                       (u32)self->mau8Gain[1] * KI_MIXER_FRAME_SIZE;
    AudioChannelBuffer* srcBuffer = ctx->mpSrcBuffer;

    for (u32 channel = 0; channel < self->mau8Gain[2]; ++channel) {
        const u32 sourceChannel = (u32)self->mau8Gain[0] + channel;
        const f32* source = srcBuffer->mpSamples + (u32)srcBuffer->muStride * sourceChannel;

        MixWithGain(destination, source, 1.0f, KI_MIXER_FRAME_SIZE);
        self->mDeClickValue[(u32)self->mau8Gain[1] + channel] = source[KI_MIXER_FRAME_SIZE - 1];
        destination += KI_MIXER_FRAME_SIZE;
    }
    return 1;
}

// ---------------------------------------------------------------------------------------
// DelayLine (real x86 layout, 4-byte pointers)
// ---------------------------------------------------------------------------------------
struct ChannelPointers {
    f32* mpStart;   // +0x00
    f32* mpEnd;     // +0x04
    f32* mpLoopEnd; // +0x08
    f32* mpCursor;  // +0x0C
};

struct TapContext {
    f32* mpBase;      // +0x00
    f32* mpTap;       // +0x04
    f32* mpTap2;      // +0x08
    f32* mpRamp;      // +0x0C
    f32* mpLoadedEnd; // +0x10
    f32* mpOut;       // +0x14
};

struct TapRecord {
    s32  miLength;  // +0x00
    s32  miLength2; // +0x04
    s32  miSelect;  // +0x08
    f32* mpOut;     // +0x0C
};

typedef void* (*IFilterFunc)(void* self, s32 count, s32 src, s32 channel, TapContext* ctx);

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

// @ 0x0114d730
DelayLine::DelayLine()
{
    mpBuffer = 0;
    mpFilter = 0;
    mpLocalBuffer = 0;
    miMaxDelaySamples = 0;
    miReadLength = 0;
    miCapacity = 0;
    miGuardSamples = 0;
    miLocalBufferSamples = 0;
    miAvailableSamples = 0;
    miCleanCursor = 0;
    miReadPosition = 0;
    miFilterReadPosition = 0;
    miChannelCount = 0;
    miWritePhase = 0;
    mbFilterChanged = 0;
}

// @ 0x0114d770
void DelayLine::Release()
{
    if (mpBuffer) {
        g_pSystem->Free(mpBuffer, 0);
        mpBuffer = 0;
    }
    mpLocalBuffer = 0;
    mpFilter = 0;
    miMaxDelaySamples = 0;
}

// @ 0x0114d7b0
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

// @ 0x0114d840
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

// @ 0x0114d9d0
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

// @ 0x0114d9f0
void DelayLine::CalcChannelPointers(ChannelPointers* pOut, s32 channel, s32 offset) const
{
    f32* const pStart = mpBuffer + (u32)channel * (u32)miCapacity;
    pOut->mpStart = pStart;
    pOut->mpEnd = pStart + miCapacity;
    pOut->mpLoopEnd = pOut->mpEnd - miGuardSamples;
    pOut->mpCursor = pStart + ((miWritePhase + offset) % miCapacity + miGuardSamples);
}

// @ 0x0114da40
f32* DelayLine::WrapCursor(const ChannelPointers* pPtrs, s32 backOffset) const
{
    f32* p = pPtrs->mpCursor - backOffset;
    if (p < pPtrs->mpStart || pPtrs->mpEnd <= p)
        p += (miCapacity - miGuardSamples);
    return p;
}

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

void DelayLine::UnmarshalDelayData(s32 channel, s32 count, TapContext* c)
{
    ChannelPointers ptrs;
    CalcChannelPointers(&ptrs, channel, 0);
    WriteData(&ptrs, c->mpLoadedEnd - count, 0, count);
}

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

// ---------------------------------------------------------------------------------------
// ReverbModel1 -- descriptor guid 'RM10'.  0x0114d3e0 = ReverbModel1::Process.
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
};

struct AllPassFilter {
    void* mpApplyFunc;  // +0x00
    void* mpResetFunc;  // +0x04
    s32   miReadLength; // +0x08
    s32   miChannels;   // +0x0C
    f32   mfGain1;      // +0x10
    f32   mfGain2;      // +0x14
};

// Out-of-line filter entry points installed by Process (homed in the ReverbFilters TU).
void* CombFilterApply(CombFilter* self, s32 count, s32 src, s32 channel, TapContext* ctx);   // 0x0114dc20
CombFilter* CombFilterReset(CombFilter* self);                                              // 0x0114dca0
void* AllPassFilterApply(AllPassFilter* self, s32 count, s32 src, s32 channel, TapContext* ctx); // 0x0114e1b0
void* AllPassFilterReset(AllPassFilter* self);                                              // 0x00c2e4e0

struct ReverbModel1 {
    char pad0[4];             // +0x00 vtable
    System* mpSystem;         // +0x04
    char pad8[0x21 - 0x8];
    u8   mbChannelCount;      // +0x21 reverb mode
    char pad22[0x28 - 0x22];
    f32  mfDecayTime;         // +0x28
    char pad2c[0x30 - 0x2C];
    f32  mfRoomSize;          // +0x30
    char pad34[0x38 - 0x34];
    f32  mfDamping;           // +0x38
    char pad3c[0x40 - 0x3C];
    AllPassFilter mAllPass[3]; // +0x40 (0x18 each)
    DelayLine     mAllPassDelay[3]; // +0x88 (0x3C each)
    char pad13c[0x1DC - 0x13C];
    CombFilter    mComb[6];    // +0x1DC (0x24 each)
    DelayLine     mCombDelay[6]; // +0x2B4 (0x3C each)
    char pad41c[0x434 - 0x41C];
    f32  mfAllPassMixGain;     // +0x434
    u8   mbAllPassConfigured;  // +0x438
    u8   mbAllPassCount;       // +0x439
    u8   mbTimerAdded;         // +0x43A

    static int Process(ReverbModel1* self, AudioProcessContext* ctx); // 0x0114d3e0
};

#define KI_REVERB_SCRATCH_SAMPLES 0x300

// @ 0x0114d3e0
int ReverbModel1::Process(ReverbModel1* self, AudioProcessContext* ctx)
{
    AudioChannelBuffer* pSrc = ctx->mpSrcBuffer;
    AudioChannelBuffer* pDst = ctx->mpDstBuffer;

    f32** ppScratchTable = *(f32***)self->mpSystem;
    f32* pScratchTop = ppScratchTable[3];
    f32* pLocalBuffer = pScratchTop - KI_REVERB_SCRATCH_SAMPLES;
    ppScratchTable[3] = pLocalBuffer;

    for (int i = 0; i < 6; ++i) {
        self->mComb[i].mpApplyFunc = (void*)&CombFilterApply;
        self->mComb[i].mpResetFunc = (void*)&CombFilterReset;
        self->mCombDelay[i].SetFilter(&self->mComb[i]);
        self->mCombDelay[i].SetLocalBuffer(pLocalBuffer, KI_REVERB_SCRATCH_SAMPLES);
    }
    for (int i = 0; i < self->mbAllPassCount; ++i) {
        self->mAllPass[i].mpApplyFunc = (void*)&AllPassFilterApply;
        self->mAllPass[i].mpResetFunc = (void*)&AllPassFilterReset;
        self->mAllPassDelay[i].SetFilter(&self->mAllPass[i]);
        self->mAllPassDelay[i].SetLocalBuffer(pLocalBuffer, KI_REVERB_SCRATCH_SAMPLES);
    }

    if (self->mfDecayTime > 0.0f) {
        self->mCombDelay[0].ApplyFilter(256, pSrc, pDst, 0);
        for (int i = 1; i < 6; ++i)
            self->mCombDelay[i].ApplyFilter(256, pSrc, pDst, 1);

        AudioChannelBuffer* pOldSrc = ctx->mpSrcBuffer;
        AudioChannelBuffer* pOldDst = ctx->mpDstBuffer;
        ctx->mpDstBuffer = pOldSrc;
        ctx->mpSrcBuffer = pOldDst;

        const u8 mode = self->mbChannelCount;
        if (mode == 1) {
            self->mAllPassDelay[0].ApplyFilter(256, pOldDst, pOldSrc, 0);
        } else if (mode == 2) {
            self->mAllPassDelay[1].ApplyFilter(256, pOldDst, pOldSrc, 0);
            memcpy(pOldSrc->mpSamples + pOldSrc->muStride * 1, pOldSrc->mpSamples, 0x400);
            self->mAllPassDelay[0].ApplyFilter(256, pOldDst, pOldSrc, 0);
        } else if (mode == 4) {
            self->mAllPassDelay[1].ApplyFilter(256, pOldDst, pOldSrc, 0);
            memcpy(pOldSrc->mpSamples + pOldSrc->muStride * 1, pOldSrc->mpSamples, 0x400);
            memcpy(pOldSrc->mpSamples + pOldSrc->muStride * 3, pOldSrc->mpSamples, 0x400);
            self->mAllPassDelay[0].ApplyFilter(256, pOldDst, pOldSrc, 0);
            memcpy(pOldSrc->mpSamples + pOldSrc->muStride * 2, pOldSrc->mpSamples, 0x400);
        } else {
            self->mAllPassDelay[2].ApplyFilter(256, pOldDst, pOldSrc, 0);
            memcpy(pOldSrc->mpSamples + pOldSrc->muStride * 2, pOldSrc->mpSamples, 0x400);
            memcpy(pOldSrc->mpSamples + pOldSrc->muStride * 4, pOldSrc->mpSamples, 0x400);
            self->mAllPassDelay[1].ApplyFilter(256, pOldDst, pOldSrc, 0);
            memcpy(pOldSrc->mpSamples + pOldSrc->muStride * 1, pOldSrc->mpSamples, 0x400);
            self->mAllPassDelay[0].ApplyFilter(256, pOldDst, pOldSrc, 0);
            memcpy(pOldSrc->mpSamples + pOldSrc->muStride * 3, pOldSrc->mpSamples, 0x400);
            memset(pOldSrc->mpSamples + pOldSrc->muStride * 5, 0, 0x400);
        }

        AudioChannelBuffer* pSwap = ctx->mpSrcBuffer;
        ctx->mpSrcBuffer = ctx->mpDstBuffer;
        ctx->mpDstBuffer = pSwap;
    } else {
        for (u32 channel = 0; channel < self->mbChannelCount; ++channel)
            memset(pSrc->mpSamples + pSrc->muStride * channel, 0, 0x400);
    }

    ppScratchTable[3] = pScratchTop;
    return 1;
}

} // namespace core
} // namespace audio
} // namespace rw
