// src/game/cmn/mixer.cpp.cpp -- migrated from slice(s) s011549c0 by tools/migrate/rewrite.py
// Object file: cmn/mixer.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/PlugIn.h"
#include "rw/audio/core/System.h"
#include "rw/audio/core/Voice.h"

// unnamed retail callees and globals (address in the comment)
extern const float  kOne;           // 0x01485720  1.0f
#include <math.h>
#include <xmmintrin.h>
#include <intrin.h>

// ---- items of slice s011549c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef float f32;
typedef double f64;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
extern const float  kOne;           // 0x01485720  1.0f
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
void* FUN_01143430(s32 a, s32 b, s32 c, void* name, void* obj, void* sys);
void  eastl_vector_insert(void* dst, void* src, u32 size);  // 0x011e0744 (CRT memmove thunk)
void* operator_new_arr(void* dst, s32 fill, u32 size);      // 0x011e073e (CRT memset thunk)
// ---- items of slice s011549c0 end

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
