// rw::audio::core slice s011549c0 -- the Mixer's input-plugin pump (ProcessInputPlugIns),
// the per-voice Execute mixer, the Mixer ctor/global-list init, the two timer-manager
// inits (timeGetTime + rdtsc), the Profiler ctor/End pair, the f32->i16 / f32->i32
// conversion kernels, the SSE float clamp, the channel-interleave kernel and the
// resonance-coefficient / volume-setup helpers.
//
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE  (RenderWare 4 core: VC .NET 2003 + scalar SSE;
// see docs/matching.md).  RenderWare-4-core calls are equivalence-only, leaves match.
#include "../../include/types.h"
#include <math.h>
#include <xmmintrin.h>
#include <intrin.h>

typedef float f32;
typedef double f64;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef unsigned __int64 u64;
typedef long long i64;

// ---------------------------------------------------------------------------------------
// Win32 imports (called through their IAT slots, exactly like the original)
// ---------------------------------------------------------------------------------------
extern "C" {
__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
__declspec(dllimport) int __stdcall QueryPerformanceFrequency(i64* lpFrequency);
}

// ---------------------------------------------------------------------------------------
// Module-level data the slice reads (addresses from the retail image; every reference is
// a relocation, so the exact address never has to be reproduced).
// ---------------------------------------------------------------------------------------
extern u32** g_mixerList;           // 0x016e61a8
extern u8    g_profilerStorage;     // 0x016f1680  (the Profiler singleton)
extern u8    g_profilerVTable;      // 0x014ce73c
extern u8    g_regionTop;           // 0x016eb6ff
extern const float  kOne;           // 0x01485720  1.0f
extern const float  kTwenty;        // 0x013eecd8  20.0f
extern const float  kI32Scale;      // 0x014ce74c
extern const float  kI16Scale;      // 0x01449540  32767.0f
extern const float  kMinFreq;       // 0x0143ea90  1e9f
extern const float  kTenF;          // 0x014ce760  10.0f
extern const float  kThirtyF;       // 0x014ce764  30.0f
extern const float  kNeg500;        // 0x013fec74  -500.0f
extern const float  kDbScale;       // 0x013ec478  0.05f
extern const float  kPowScale;      // 0x013f7344  0.95f
extern const float  kNeg2;          // 0x013ef61c  -2.0f
extern const float  kPercent;       // 0x013eb960  0.01f
extern const float  kTwoPow32F;     // 0x013f4fd0  2^32
extern const double kTen;           // 0x0140ebb0  10.0
extern const double kOneD;          // 0x013f1688  1.0
extern const u8     kSignFlip[16];  // 0x013eb8b0  0x80000000 x4

// ---------------------------------------------------------------------------------------
// Flat records (retail x86 layouts)
// ---------------------------------------------------------------------------------------
struct SampleBuffer {
    void* mpSystem;      // +0x00
    u8*   mpStorage;     // +0x04
    u32   mField8;       // +0x08
    u16   mFieldC;       // +0x0C
    u16   mMaxSamples;   // +0x0E
    u8    mField10;      // +0x10
};

struct VoiceStageData {         // 12 bytes
    void* mpPreProcess;         // +0x00
    void* mpProcess;            // +0x04
    u32   mField8;              // +0x08
};

struct PlugIn {
    u8  mPad00[0x1C];
    u32 mCpuTicks;              // +0x1C
    u8  mPad20;
    u8  mOutputChannels;        // +0x21
};

struct Voice {
    f32 mAverage;                  // +0x00
    f32 mHistory[2];               // +0x04, +0x08
    u32 mSlotSwitcher;             // +0x0C
    u8  mPad10[0x08];              // +0x10
    VoiceStageData* mpPlugInLocationDescs; // +0x18
    u8  mPad1C[0x10];              // +0x1C
    f32 mDecayEatenSamples;        // +0x2C
    u8  mPad30[0x0C];              // +0x30
    u32 mCpuTicks;                 // +0x3C
    u8  mPad40[0x04];              // +0x40
    u8  mNumPlugIns;               // +0x44
    u8  mDiscontinuityPlugIn;      // +0x45
    u8  mInputPlugInStartPoint;    // +0x46
    u8  mPad47[0x03];              // +0x47
    u8  mField4A;                  // +0x4A
    u8  mPad4B;                    // +0x4B
    PlugIn* mpPlugIns[1];          // +0x4C
};

struct MixerExecuteParams {
    f64 mfSystemTime;        // +0x00
    void* mpVoiceListNodes;  // +0x08
    f32 mfOutputSampleRate;  // +0x0C
    u16 muNumVoices;         // +0x10
};

struct Mixer {
    u8   mBuffer[0x30000];        // +0x00000
    f64  mCurrentMixTime;         // +0x30000
    void* mpSystem;               // +0x30008
    void* mpSampleBuffer[3];      // +0x3000C
    MixerExecuteParams* mpMixerExecuteParams; // +0x30018
    u32  mMixerCpuCycles;         // +0x3001C
    u32  mSrcNumSamples;          // +0x30020
    f32  mSrcSampleRate;          // +0x30024
    f32  mTotalPitch;             // +0x30028
    u8   mSrcNumChannels;         // +0x3002C

    Mixer();
    int  Execute(MixerExecuteParams* params);                                  // 0x01154ca0
    int  ProcessInputPlugIns(VoiceStageData* stages, void* node, Voice* voice); // 0x011549c0
    int  HandleBufferStatusUnavailable(Voice* voice, PlugIn* plugIn, s32 count); // 0x01154920
};

// Timer manager (timeGetTime + rdtsc bookkeeping, Mixer's mix clock)
struct MixerTimer {
    u32 mField0;      // +0x00
    u32 mField4;      // +0x04
    u32 mField8;      // +0x08
    u8  mPad0C[0x04]; // +0x0C
    f32 mf10;         // +0x10
    f32 mf14;         // +0x14
    f32 mf18;         // +0x18
    u32 mPad1C;       // +0x1C
    u32 mCycleLo;     // +0x20
    u32 mCycleHi;     // +0x24
    u32 mTimeMs;      // +0x28

    void Init();             // 0x01154eb0
    void Tick();             // 0x01154ee0
    void Init(void* owner);  // 0x01154f00
};

struct System {
    u8  mPad00[0x34];
    void* mpProfiler;    // +0x34
    void* GetProfiler(); // 0x01155670
};

struct ProfilerLayout {
    void* mpVTable;           // +0x00
    u32   mPad04;             // +0x04
    f64   mfNextReportTime;   // +0x08
    f32   mfAverage;          // +0x10
    u32   muAccumTicks;       // +0x14
    u32   muReportBaseCycle;  // +0x18
    u32   muBeginCycle;       // +0x1C
    u32   muLastEndCycle;     // +0x20
    u32   muMaxTicks;         // +0x24
    u32   muHasBaseline;      // +0x28
    u32   muWrapCount;        // +0x2C
    void* mpTimeSource;       // +0x30
    void End();               // 0x01154fb0
};

extern ProfilerLayout g_profiler;

// Opaque owner of the resonance-coefficient block; both helpers are thiscall members
// (ecx = this, args on the stack).
struct ResonanceCore {
    void Setup(f32 param);                          // 0x01155690  (ret 4)
    void SetCoefficients(f32 freq, f32 bandwidth);  // 0x011558f0  (ret 8)
};

// the retail build folds this profiler's cycle source to the constant 1
static __forceinline u32 GetCpuCycle() { return 1; }

// out-of-slice helpers this slice calls (relocations are masked)
void* FUN_01143430(s32 a, s32 b, s32 c, void* name, void* obj, void* sys);
void  FUN_0115690(void* self, f32 rate);
void  FUN_011631c0(void* self, void* mixer, u8 flag);
void  FUN_011633e0(void* self);
void  FUN_01163380(void* self, f32 a, f32 b, f32 c, s32 d, s32 e, s32 f);
void  eastl_vector_insert(void* dst, void* src, u32 size);  // 0x011e0744 (CRT memmove thunk)
void* operator_new_arr(void* dst, s32 fill, u32 size);      // 0x011e073e (CRT memset thunk)

// ---------------------------------------------------------------------------------------
// 0x011549c0 -- Mixer::ProcessInputPlugIns: pull one 0x100-frame block through every
// voice's plugin chain, front to back, and top the destination buffer up.
// ---------------------------------------------------------------------------------------
// @ 0x011549c0
int Mixer::ProcessInputPlugIns(VoiceStageData* stages, void* node, Voice* voice)
{
    (void)node;
    u32 accum = 0;        // local_1c
    u32 savedChans = 0;   // local_14
    f32 savedRate = 0.0f; // local_4
    s32 pass = 0;         // local_c
    s32 status = 0;       // local_18
    s32 chunk = 0;        // iVar5

    for (;;) {
        mTotalPitch = kOne;
        u32 stage = voice->mInputPlugInStartPoint;
        VoiceStageData* pStage = stages + stage;
        PlugIn** ppPlug = (PlugIn**)((u8*)voice + 0x4C) + stage;
        s32 avail = 0x100 - (s32)accum;
        do {
            chunk = avail;
            PlugIn* p = *ppPlug;
            typedef s32 (__cdecl* PreProcProc)(PlugIn*, Mixer*, s32, s32);
            PreProcProc proc = (PreProcProc)pStage->mpPreProcess;
            avail = proc(p, this, (s32)((s32)voice->mDiscontinuityPlugIn < (s32)stage), chunk);
            if (avail > 0xFF)
                avail = 0x100;
            if (pass == 0)
                p->mCpuTicks = 0;
            --ppPlug;
            pStage -= 1;
            --stage;
            p->mCpuTicks = p->mCpuTicks;
        } while ((s32)stage >= 0);

        ++pass;
        s32 i = 0;
        do {
            PlugIn* p = *(PlugIn**)((u8*)voice + 0x4C + i * 4);
            typedef s32 (__cdecl* ProcessProc)(PlugIn*, Mixer*, s32);
            ProcessProc proc = (ProcessProc)stages[i].mpProcess;
            status = proc(p, this, (s32)((s32)voice->mDiscontinuityPlugIn < i));
            if (status == 0) {
                if (i == 0)
                    status = HandleBufferStatusUnavailable(voice, p, chunk);
                if (status == 0) {
                    p->mCpuTicks = p->mCpuTicks;
                    goto Tail;
                }
            } else if (i == 0) {
                voice->mDecayEatenSamples = 0.0f;
            }
            p->mCpuTicks = p->mCpuTicks;
            ++i;
        } while (i <= (s32)voice->mInputPlugInStartPoint);
        if (status != 1)
            goto Tail;

        u32 chans = mSrcNumChannels;
        s32 samples = (s32)mSrcNumSamples;
        if (samples != 0) {
            SampleBuffer* pDst = (SampleBuffer*)mpSampleBuffer[2];
            if (accum == 0) {
                mpSampleBuffer[2] = mpSampleBuffer[0];
                mpSampleBuffer[0] = pDst;
            } else {
                SampleBuffer* pSrc = (SampleBuffer*)mpSampleBuffer[0];
                for (u32 c = 0; c < chans; ++c)
                    eastl_vector_insert(
                        pDst->mpStorage + (u32)pDst->mMaxSamples * c + accum,
                        pSrc->mpStorage + (u32)pSrc->mMaxSamples * c,
                        (u32)samples * 4);
            }
            savedRate = mSrcSampleRate;
            mCurrentMixTime = (f64)samples /
                              (f64)mpMixerExecuteParams->mfOutputSampleRate +
                              mCurrentMixTime;
            savedChans = chans;
        }
        accum += (u32)samples;
        if (accum > 0xFF)
            goto Done;
    }
Tail:
    if (accum != 0) {
        SampleBuffer* pDst = (SampleBuffer*)mpSampleBuffer[2];
        for (u32 c = 0; c < savedChans; ++c)
            operator_new_arr(pDst->mpStorage + (u32)pDst->mMaxSamples * c + accum, 0,
                             (0x100 - accum) * 4);
        mSrcNumChannels = (u8)savedChans;
        mSrcSampleRate = savedRate;
        status = 1;
    }
Done:
    {
        void* t = mpSampleBuffer[0];
        mpSampleBuffer[0] = mpSampleBuffer[2];
        mpSampleBuffer[2] = t;
        mSrcNumSamples = 0x100;
        return status;
    }
}

// ---------------------------------------------------------------------------------------
// 0x01154ca0 -- Mixer::Execute: allocate the three source buffers, run every voice's
// plugin chain and refresh the CPU-cycle averages.
// ---------------------------------------------------------------------------------------
// @ 0x01154ca0
int Mixer::Execute(MixerExecuteParams* params)
{
    mpMixerExecuteParams = params;

    // --- allocate the three source buffers (names live in a parallel table) ---
    {
        int n = 3;
        void** ppBuf = mpSampleBuffer;
        u8* pNames = (u8*)0x016eb300;   // module name table (address masked)
        void* pOwner = this;
        do {
            *ppBuf = FUN_01143430(0x40, 6, 0x100, pNames, pOwner, mpSystem);
            ++ppBuf;
            pOwner = (u8*)pOwner + 0x10000;
            pNames += 0x114;
            --n;
        } while (n != 0);
    }

    int status = 0;
    u32 i = 0;                       // voice index (kept live across the inner code)
    if (mpMixerExecuteParams->muNumVoices != 0) {
        do {
            void* nodes = mpMixerExecuteParams->mpVoiceListNodes;
            Voice* voice = *(Voice**)((u8*)nodes + i * 8);
            if (voice->mField4A == 0) {
                VoiceStageData* descs = voice->mpPlugInLocationDescs;
                mTotalPitch = kOne;
                u32 stage;
                if (voice->mInputPlugInStartPoint == 0xFF) {
                    stage = 0;
                    status = 1;
                } else {
                    mCurrentMixTime = mpMixerExecuteParams->mfSystemTime;
                    status = ProcessInputPlugIns(descs, (u8*)nodes + i * 8, voice);
                    stage = (u32)voice->mInputPlugInStartPoint + 1;
                }
                mCurrentMixTime = mpMixerExecuteParams->mfSystemTime;
                if (status == 1) {
                    while (stage < (u32)voice->mNumPlugIns) {
                        PlugIn* plug = voice->mpPlugIns[stage];
                        status = ((s32 (__cdecl*)(PlugIn*, Mixer*, s32))descs[stage].mpProcess)
                                    (plug, this, (s32)((u32)voice->mDiscontinuityPlugIn < stage));
                        if (status == 0) {
                            status = HandleBufferStatusUnavailable(voice, plug, 0x100);
                            if (status == 0)
                                break;
                        } else if (stage == 0) {
                            voice->mDecayEatenSamples = 0.0f;
                        }
                        plug->mCpuTicks = 0;
                        ++stage;
                    }
                    if (status != 1)
                        goto Stats;
                    voice->mDiscontinuityPlugIn = voice->mNumPlugIns;
                }
            Stats:
                u32 slot = voice->mSlotSwitcher;
                voice->mAverage = voice->mHistory[1] + voice->mHistory[0];
                voice->mCpuTicks = 0;
                voice->mHistory[slot] = 0.0f;
                voice->mSlotSwitcher = (u32)(voice->mSlotSwitcher == 0);
            }
            ++i;
        } while ((s32)i < (s32)(u32)mpMixerExecuteParams->muNumVoices);
    }
    mMixerCpuCycles = 0;
    return status;
}

// ---------------------------------------------------------------------------------------
// 0x01154e50 -- Mixer::Mixer: zero the mix state and (re)link the global mixer list node.
// ---------------------------------------------------------------------------------------
// @ 0x01154e50
Mixer::Mixer()
{
    mMixerCpuCycles = 0;
    mSrcNumChannels = 0;
    mSrcNumSamples = 0;
    mSrcSampleRate = 0.0f;

    u32** list = g_mixerList;
    u32* node = *list;
    node[0] = (u32)list;

    u32 upper = 0x80;
    if (upper <= (u32)&g_profilerStorage)
        upper = ((u32)&g_profilerStorage >> 7) << 7;
    u32 lower = (u32)&g_regionTop & 0xFFFFFF80u;

    node[2] = lower;
    node[1] = upper;
    node[3] = upper;
}

// ---------------------------------------------------------------------------------------
// 0x01154eb0 / 0x01154f00 -- MixerTimer inits (wall clock + TSC).
// ---------------------------------------------------------------------------------------
// @ 0x01154eb0
void MixerTimer::Init()
{
    mTimeMs = timeGetTime();
    u64 t = __rdtsc();
    mCycleLo = (u32)t;
    mCycleHi = (u32)(t >> 32);
    mField4 = 0;
    mf10 = 0.0f;
    mf14 = 0.0f;
    mf18 = 0.0f;
}

// @ 0x01154ee0
void MixerTimer::Tick()
{
    mField4 = mField4 + (1 - mField8);
    *(u32*)((u8*)mField0 + 0xD8) = 0;
}

// @ 0x01154f00
void MixerTimer::Init(void* owner)
{
    mField0 = (u32)owner;
    mTimeMs = timeGetTime();
    u64 t = __rdtsc();
    mCycleLo = (u32)t;
    mCycleHi = (u32)(t >> 32);
    mField4 = 0;
    mf10 = 0.0f;
    mf14 = 0.0f;
    mf18 = 0.0f;

    i64 freq = 0;
    QueryPerformanceFrequency(&freq);
    f32 f = (f32)freq;
    if (kMinFreq > f)
        *(f32*)((u8*)owner + 0xC4) = kMinFreq;
    else
        *(f32*)((u8*)owner + 0xC4) = f;
}

// ---------------------------------------------------------------------------------------
// 0x01154fb0 -- Profiler::End: close the frame, fold the TSC delta and periodically
// publish the averaged cycle count.
// ---------------------------------------------------------------------------------------
// @ 0x01154fb0
void ProfilerLayout::End()
{
    f64 lfNow = *(f64*)((u8*)mpTimeSource + 8);
    u32 luCycle = GetCpuCycle();

    if (luCycle < muLastEndCycle)
        ++muWrapCount;
    muLastEndCycle = luCycle;

    u32 luTicks = (luCycle - muBeginCycle) >> 6;
    muAccumTicks += luTicks;
    if (luTicks > muMaxTicks)
        muMaxTicks = luTicks;

    if (mfNextReportTime - lfNow > kTen)
        mfNextReportTime = lfNow;

    if (mfNextReportTime <= lfNow) {
        f32 lfAverage = (f32)muAccumTicks /
            (((f32)(muWrapCount << 26) - (f32)muReportBaseCycle) * kPercent);
        if (lfAverage >= 0.0f && muHasBaseline != 0)
            mfAverage = lfAverage;
        muHasBaseline = luCycle;
        muAccumTicks = 0;
        muReportBaseCycle = 0;
        muWrapCount = 0;
        mfNextReportTime += kOneD;
    }
}

// ---------------------------------------------------------------------------------------
// 0x01155090 -- Profiler construction: initialise the singleton and hand back its address.
// ---------------------------------------------------------------------------------------
// @ 0x01155090
// The retail build compiled this constructor for size (fldz from an /Os-style fold).
#pragma optimize("s", on)
ProfilerLayout* Profiler_Init(void* timeSource)
{
    g_profiler.mfNextReportTime = 0.0;
    g_profiler.mpTimeSource = timeSource;
    g_profiler.muAccumTicks = 0;
    g_profiler.muReportBaseCycle = 0;
    g_profiler.muBeginCycle = 0;
    g_profiler.muLastEndCycle = 0;
    g_profiler.muMaxTicks = 0;
    g_profiler.muHasBaseline = 0;
    g_profiler.muWrapCount = 0;
    g_profiler.mpVTable = (void*)&g_profilerVTable;
    g_profiler.mfAverage = 0.0f;
    return &g_profiler;
}
#pragma optimize("", on)

// ---------------------------------------------------------------------------------------
// 0x01155110 -- float -> signed 16-bit scale (x * 32767), block form + scalar tail.
// ---------------------------------------------------------------------------------------
// @ 0x01155110
void FUN_01155110(s16* dst, const f32* src, u32 count)
{
    if (((((u32)dst | (u32)src) & 0xF) == 0) && ((count & 7) == 0)) {
        const f32* end = src + count;
        do {
            dst[0] = (s16)(src[0] * 32767);
            dst[1] = (s16)(src[1] * 32767);
            dst[2] = (s16)(src[2] * 32767);
            dst[3] = (s16)(src[3] * 32767);
            dst[4] = (s16)(src[4] * 32767);
            dst[5] = (s16)(src[5] * 32767);
            dst[6] = (s16)(src[6] * 32767);
            dst[7] = (s16)(src[7] * 32767);
            src += 8;
            dst += 8;
        } while (src != end);
        return;
    }
    const f32* end = src + count;
    for (; src < end; ++src, ++dst)
        *dst = (s16)(*src * 32767.0f);
}

// ---------------------------------------------------------------------------------------
// 0x011551d0 -- float -> signed 32-bit scale (x * 2^31-ish), block form + scalar tail.
// ---------------------------------------------------------------------------------------
// @ 0x011551d0
void FUN_011551d0(s32* dst, const f32* src, u32 count)
{
    if (((((u32)dst | (u32)src) & 0xF) == 0) && ((count & 7) == 0)) {
        const f32* end = src + count;
        do {
            dst[0] = (s32)(src[0] * kI32Scale);
            dst[1] = (s32)(src[1] * kI32Scale);
            dst[2] = (s32)(src[2] * kI32Scale);
            dst[3] = (s32)(src[3] * kI32Scale);
            dst[4] = (s32)(src[4] * kI32Scale);
            dst[5] = (s32)(src[5] * kI32Scale);
            dst[6] = (s32)(src[6] * kI32Scale);
            dst[7] = (s32)(src[7] * kI32Scale);
            src += 8;
            dst += 8;
        } while (src != end);
        return;
    }
    const f32* end = src + count;
    for (; src < end; ++src, ++dst)
        *dst = (s32)(*src * kI32Scale);
}

// ---------------------------------------------------------------------------------------
// 0x011552a0 -- in-place vector clamp: v = min(max(v, lo), hi), SSE block + scalar tail.
// ---------------------------------------------------------------------------------------
// @ 0x011552a0
void FUN_011552a0(f32* ptr, f32 lo, f32 hi, s32 count)
{
    if (count == 0)
        return;
    f32* end = ptr + count;
    if (count >= 0xC) {
        while (((u32)ptr & 0xF) != 0) {
            __m128 v = _mm_load_ss(ptr);
            v = _mm_max_ss(v, _mm_set1_ps(lo));
            v = _mm_min_ss(v, _mm_set1_ps(hi));
            _mm_store_ss(ptr, v);
            ++ptr;
            --count;
        }
        do {
            _mm_store_ps(ptr, _mm_min_ps(_mm_max_ps(_mm_load_ps(ptr), _mm_set1_ps(lo)), _mm_set1_ps(hi)));
            _mm_store_ps(ptr + 4, _mm_min_ps(_mm_max_ps(_mm_load_ps(ptr + 4), _mm_set1_ps(lo)), _mm_set1_ps(hi)));
            ptr += 8;
            count -= 8;
        } while (ptr <= end - 8);
        if (count == 0)
            return;
    }
    do {
        __m128 v = _mm_load_ss(ptr);
        v = _mm_max_ss(v, _mm_set1_ps(lo));
        v = _mm_min_ss(v, _mm_set1_ps(hi));
        _mm_store_ss(ptr, v);
        ++ptr;
        --count;
    } while (count != 0);
}

// ---------------------------------------------------------------------------------------
// 0x01155330 -- channel-interleave kernel: gather `count` frames from planar channels
// into an interleaved destination (6/4/2/1 channels).
// ---------------------------------------------------------------------------------------
// @ 0x01155330
void FUN_01155330(f32* dst, SampleBuffer* src, s32 format, s32 count)
{
    if (format == 6) {
        u32 stride = src->mMaxSamples;
        f32* base = (f32*)src->mpStorage;
        f32* c0 = base;
        f32* c1 = base + stride;
        f32* c2 = base + stride * 2;
        f32* c3 = base + stride * 3;
        f32* c4 = base + stride * 4;
        f32* c5 = base + stride * 5;
        for (s32 i = 0; i < count; ++i) {
            dst[0] = c0[i];
            dst[1] = c1[i];
            dst[2] = c2[i];
            dst[3] = c3[i];
            dst[4] = c4[i];
            dst[5] = c5[i];
            dst += 6;
        }
    } else if (format == 4) {
        u32 stride = src->mMaxSamples;
        f32* base = (f32*)src->mpStorage;
        for (s32 i = 0; i < count; ++i) {
            dst[0] = base[i];
            dst[1] = base[stride + i];
            dst[2] = base[stride * 2 + i];
            dst[3] = base[stride * 3 + i];
            dst += 4;
        }
    } else if (format == 2) {
        u32 stride = src->mMaxSamples;
        f32* base = (f32*)src->mpStorage;
        for (s32 i = 0; i < count; ++i) {
            dst[0] = base[i];
            dst[1] = base[stride + i];
            dst += 2;
        }
    } else if (format == 1) {
        eastl_vector_insert(dst, src->mpStorage, (u32)count * 4);
    }
}

// ---------------------------------------------------------------------------------------
// 0x01155670 -- System::GetProfiler: lazily build the singleton and return it.
// ---------------------------------------------------------------------------------------
__declspec(noinline) ProfilerLayout* Profiler_Init(void* timeSource);

// @ 0x01155670
void* System::GetProfiler()
{
    if (mpProfiler == 0)
        mpProfiler = Profiler_Init(this);
    return mpProfiler;
}

// ---------------------------------------------------------------------------------------
// 0x01155690 -- resonance/volume setup: clamp the dB gain, convert it to linear and post
// the filter coefficients.
// ---------------------------------------------------------------------------------------
// @ 0x01155690
void ResonanceCore::Setup(f32 param)
{
    u8* self = (u8*)this;
    if (*(f32*)(self + 0x38) < 0.0f)
        *(f32*)(self + 0x38) = 0.0f;
    else if (*(f32*)(self + 0x38) > kTenF)
        *(f32*)(self + 0x38) = kTenF;

    if (*(f32*)(self + 0x40) < 0.0f)
        *(f32*)(self + 0x40) = 0.0f;
    else if (*(f32*)(self + 0x40) > kThirtyF)
        *(f32*)(self + 0x40) = kThirtyF;

    if (*(f32*)(self + 0x28) < kNeg500)
        *(f32*)(self + 0x28) = kNeg500;

    f32 gain = (f32)pow(kTen, (f64)(*(f32*)(self + 0x28) * kDbScale));

    s32 a = (s32)(param * *(f32*)(self + 0x38));
    if (a == 0) a = 1;
    s32 b = (s32)(param * *(f32*)(self + 0x40));
    if (b == 0) b = 1;
    s32 c = (*(f32*)(self + 0x48) == kOne) ? 1 : 0;
    f32 d = kOne / *(f32*)(self + 0x30) - kOne;

    FUN_01163380(self + 0x50, gain, gain * kPowScale, d, a, b, c);
}

// ---------------------------------------------------------------------------------------
// 0x011557a0 -- resonance-filter activation / retune (the function between the two
// slice callers).
// ---------------------------------------------------------------------------------------
// @ 0x011557a0
int FUN_011557a0(void* self_, Mixer* mixer)
{
    u8* self = (u8*)self_;
    if (*(f32*)(self + 0x28) >= kTwenty || kOne >= *(f32*)(self + 0x30)) {
        if (*(u32*)(self + 0xB8) == 1) {
            FUN_011633e0(self + 0x50);
            *(u32*)(self + 0xB8) = 0;
        }
        *(f32*)(self + 0xA0) = *(f32*)(self + 0x28);
        *(f32*)(self + 0xA4) = *(f32*)(self + 0x30);
        return 1;
    }
    if (*(u32*)(self + 0xB8) == 0)
        *(u32*)(self + 0xB8) = 1;

    f32 rate = mixer->mpMixerExecuteParams->mfOutputSampleRate;

    if (!(*(f32*)(self + 0x28) == *(f32*)(self + 0xA0) &&
          *(f32*)(self + 0x30) == *(f32*)(self + 0xA4) &&
          *(f32*)(self + 0x38) == *(f32*)(self + 0xA8) &&
          *(f32*)(self + 0x40) == *(f32*)(self + 0xAC) &&
          *(f32*)(self + 0x48) == *(f32*)(self + 0xB0) &&
          rate == *(f32*)(self + 0xB4))) {
        FUN_0115690(self, rate);
        *(f32*)(self + 0xA0) = *(f32*)(self + 0x28);
        *(f32*)(self + 0xB4) = rate;
        *(f32*)(self + 0xA4) = *(f32*)(self + 0x30);
        *(f32*)(self + 0xA8) = *(f32*)(self + 0x38);
        *(f32*)(self + 0xAC) = *(f32*)(self + 0x40);
        *(f32*)(self + 0xB0) = *(f32*)(self + 0x48);
    }
    FUN_011631c0(self + 0x50, mixer, *(u8*)(self + 0x21));
    return 1;
}

// ---------------------------------------------------------------------------------------
// 0x011558f0 -- resonance coefficient pair from (freq, bandwidth); x87 sin/cos.
// ---------------------------------------------------------------------------------------
// @ 0x011558f0
void ResonanceCore::SetCoefficients(f32 freq, f32 bandwidth)
{
    u8* self = (u8*)this;
    f32 q = freq / bandwidth;
    if (q > kTwenty)
        q = kTwenty;

    f32 s = (f32)sin((f64)freq);
    f32 v = s / (q + q);
    f32 c = (f32)cos((f64)freq);
    f32 w = kOne / (v + kOne);

    *(f32*)(self + 0x9C) = (kOne - v) * w;
    *(f32*)(self + 0xA0) = w * v;
    *(f32*)(self + 0xA4) = 0.0f;
    *(f32*)(self + 0x98) = c * kNeg2 * w;
    *(f32*)(self + 0xA8) = -(w * v);
}
