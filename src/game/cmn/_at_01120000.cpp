// src/game/cmn/_at_01120000.cpp -- migrated from slice(s) s0112dca0, s0112ce20 by tools/migrate/rewrite.py
// Object file: cmn/_at_01120000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl rw_memset(void* dst, int value, unsigned bytes); // 0x011e073e
#include <string.h>

// ---- items of slice s0112ce20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl rw_memset(void* dst, int value, unsigned bytes); // 0x011e073e
namespace rw {
namespace audio {
namespace core {
void CopyWithGain(float* pDst, const float* pSrc, float gain, int numSamples); // 0x01134260
}
}
}
namespace rw {
namespace audio {
namespace core {
void MixWithGain(float* pDst, const float* pSrc, float gain, int numSamples);  // 0x011342c0
}
}
}
namespace rw {
namespace audio {
namespace core {
static const float KF_CHANNEL_FOLD = 0.70700002f;
}
}
}
// ---- items of slice s0112ce20 end

// ---- items of slice s0112dca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma function(memcpy)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
namespace rw {
namespace audio {
namespace core {
class System_s0112_dca0;
}
}
}
namespace rw {
namespace audio {
namespace core {
class System_s0112_dca0
{ public:
    void*  mpStackAllocator;     // +0x0
    void*  mpAssertImplementation;// +0x4
    double mSystemTime;          // +0x8
    void*  mExpelledVoiceList;   // +0x10
    void*  mpAllocator;          // +0x14
    void*  mpPhysicalAlloc;      // +0x18
    void*  mpPhysicalFree;       // +0x1c
    char*  mpCommandBuffer;      // +0x20
    void*  mpMasteringSubMix;    // +0x24
    void*  mpPlugInRegistry;     // +0x28
    void*  mpDecoderRegistry;    // +0x2c
    void*  mpEncoderRegistry;    // +0x30
    void*  mpProfiler;           // +0x34
    void*  mpJobScheduler;       // +0x38
    void*  mMutexIsLockedFn;     // +0x3c
    void*  mMutexLockFn;         // +0x40
    void*  mMutexUnlockFn;       // +0x44
    void*  mpExecuteCommandsMutex;// +0x48
    void*  mpMutex;              // +0x4c
    void*  mpLockThreadId;       // +0x50
    void*  mpRwAudioCoreThreadId;// +0x54
    void*  mpVoiceListNodes;     // +0x58
    u8     mTimerList[4];        // +0x5c
    u8     mTimerManager[0x48];  // +0x60
    void*  mpAssertHandler;      // +0xa8
    void*  mGetCsisLibraryType;  // +0xac
    u32    mCommandBufferSize;   // +0xb0
    u32    mCommandIndex;        // +0xb4
    u32    mCommandBufferHighWater;// +0xb8
    float  mSystemTimerPeriod;   // +0xbc
    float  mSampleRate;          // +0xc0
    float  mCpuFrequency;        // +0xc4
    float  mCpuLoadLimit;        // +0xc8
    u32    mMixerCpuTicks;       // +0xcc
    u32    mCommandExecutionCpuTicks;// +0xd0
    u32    mTimerExecutionCpuTicks;// +0xd4
    u32    mLoadBalancerCpuTicks;// +0xd8
    u32    mExpelVoicesCpuTicks; // +0xdc
    u32    mCommandTimeStamp;    // +0xe0
    u8     pad1[0xc];            // +0xe4
    u16    mNumActiveVoices;     // +0xf0
    u16    mMaxActiveVoices;     // +0xf2

    void* Alloc(int size, const char* name, int align, int a5); // 0x0112c820
    void  Free(void* p, void* allocator);                       // 0x0112c850
    void  RemoveTimer(void* timerHandle);                       // 0x0112dad0
    void  FUN_0112c590();                                       // 0x0112c590
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Stream { void ReleaseChunk(void* chunk); };                             // 0x011e7c70
}
}
}
namespace rw {
namespace audio {
namespace core {
void  FUN_01133450(void);                                                      // 0x01133450
}
}
}
namespace rw {
namespace audio {
namespace core {
void  FUN_01133460(void);                                                      // 0x01133460
}
}
}
namespace rw {
namespace audio {
namespace core {
void  SNDPKTPLAY_submit(int a, void* b);                                      // 0x0112e9?? external
}
}
}
namespace rw {
namespace audio {
namespace core {
int __fastcall Stream_GetChunk(void* stream);                                           // rw::core::filesys::Stream::GetChunk
}
}
}
// ---- items of slice s0112dca0 end

// @ 0x0112ce20
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite1x2(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    const float scaled = gain * KF_CHANNEL_FOLD;
    CopyWithGain(ppDst[0], ppSrc[0], scaled, numSamples);
    CopyWithGain(ppDst[1], ppSrc[0], scaled, numSamples);
}
}}}  // namespace rw::audio::core

// @ 0x0112ce70
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite1x4(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    const float scaled = gain * KF_CHANNEL_FOLD;
    CopyWithGain(ppDst[0], ppSrc[0], scaled, numSamples);
    CopyWithGain(ppDst[1], ppSrc[0], scaled, numSamples);
    const unsigned bytes = (unsigned)numSamples << 2;
    rw_memset(ppDst[2], 0, bytes);
    rw_memset(ppDst[3], 0, bytes);
}
}}}  // namespace rw::audio::core

// @ 0x0112cee0
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite1x6(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[1], ppSrc[0], gain, numSamples);
    const unsigned bytes = (unsigned)numSamples << 2;
    rw_memset(ppDst[0], 0, bytes);
    rw_memset(ppDst[2], 0, bytes);
    rw_memset(ppDst[3], 0, bytes);
    rw_memset(ppDst[4], 0, bytes);
    rw_memset(ppDst[5], 0, bytes);
}
}}}  // namespace rw::audio::core

// @ 0x0112cf50
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite2x1(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    MixWithGain(ppDst[0], ppSrc[1], gain, numSamples);
}
}}}  // namespace rw::audio::core

// @ 0x0112cfa0
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite2x2(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[1], ppSrc[1], gain, numSamples);
}
}}}  // namespace rw::audio::core

// @ 0x0112cff0
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite2x4(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[1], ppSrc[1], gain, numSamples);
    const unsigned bytes = (unsigned)numSamples << 2;
    rw_memset(ppDst[2], 0, bytes);
    rw_memset(ppDst[3], 0, bytes);
}
}}}  // namespace rw::audio::core

// @ 0x0112d050
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite2x6(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[2], ppSrc[1], gain, numSamples);
    const unsigned bytes = (unsigned)numSamples << 2;
    rw_memset(ppDst[1], 0, bytes);
    rw_memset(ppDst[3], 0, bytes);
    rw_memset(ppDst[4], 0, bytes);
    rw_memset(ppDst[5], 0, bytes);
}
}}}  // namespace rw::audio::core

// @ 0x0112d0d0
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite4x1(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    float* dst0 = ppDst[0];
    CopyWithGain(dst0, ppSrc[0], gain, numSamples);
    MixWithGain(dst0, ppSrc[1], gain, numSamples);
    MixWithGain(dst0, ppSrc[2], gain, numSamples);
    MixWithGain(dst0, ppSrc[3], gain, numSamples);
}
}}}  // namespace rw::audio::core

// @ 0x0112d140
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite4x2(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    float* dst0 = ppDst[0];
    CopyWithGain(dst0, ppSrc[0], gain, numSamples);
    MixWithGain(dst0, ppSrc[2], gain, numSamples);
    float* dst1 = ppDst[1];
    CopyWithGain(dst1, ppSrc[1], gain, numSamples);
    MixWithGain(dst1, ppSrc[3], gain, numSamples);
}
}}}  // namespace rw::audio::core

// @ 0x0112d1c0
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite4x4(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[1], ppSrc[1], gain, numSamples);
    CopyWithGain(ppDst[2], ppSrc[2], gain, numSamples);
    CopyWithGain(ppDst[3], ppSrc[3], gain, numSamples);
}
}}}  // namespace rw::audio::core

// @ 0x0112d240
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite4x6(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[2], ppSrc[1], gain, numSamples);
    CopyWithGain(ppDst[3], ppSrc[2], gain, numSamples);
    CopyWithGain(ppDst[4], ppSrc[3], gain, numSamples);
    const unsigned bytes = (unsigned)numSamples << 2;
    rw_memset(ppDst[1], 0, bytes);
    rw_memset(ppDst[5], 0, bytes);
}
}}}  // namespace rw::audio::core

// @ 0x0112d2e0
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite6x1(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    float* dst0 = ppDst[0];
    CopyWithGain(dst0, ppSrc[1], gain, numSamples);
    MixWithGain(dst0, ppSrc[2], gain, numSamples);
    MixWithGain(dst0, ppSrc[4], gain, numSamples);
    MixWithGain(dst0, ppSrc[3], gain, numSamples);
    MixWithGain(dst0, ppSrc[0], gain, numSamples);
}
}}}  // namespace rw::audio::core

// @ 0x0112d370
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite6x2(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    const float foldGain = gain * KF_CHANNEL_FOLD;
    float* dst0 = ppDst[0];
    CopyWithGain(dst0, ppSrc[1], foldGain, numSamples);
    MixWithGain(dst0, ppSrc[0], gain, numSamples);
    MixWithGain(dst0, ppSrc[3], gain, numSamples);
    float* dst1 = ppDst[1];
    CopyWithGain(dst1, ppSrc[1], foldGain, numSamples);
    MixWithGain(dst1, ppSrc[2], gain, numSamples);
    MixWithGain(dst1, ppSrc[4], gain, numSamples);
}
}}}  // namespace rw::audio::core

// @ 0x0112d420
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite6x4(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    const float foldGain = gain * KF_CHANNEL_FOLD;
    CopyWithGain(ppDst[0], ppSrc[1], foldGain, numSamples);
    MixWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[1], ppSrc[1], foldGain, numSamples);
    MixWithGain(ppDst[1], ppSrc[2], gain, numSamples);
    CopyWithGain(ppDst[2], ppSrc[3], gain, numSamples);
    CopyWithGain(ppDst[3], ppSrc[4], gain, numSamples);
}
}}}  // namespace rw::audio::core

// @ 0x0112d4e0
namespace rw { namespace audio { namespace core {
void ReChannelGainWrite6x6(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[1], ppSrc[1], gain, numSamples);
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[2], ppSrc[2], gain, numSamples);
    CopyWithGain(ppDst[3], ppSrc[3], gain, numSamples);
    CopyWithGain(ppDst[4], ppSrc[4], gain, numSamples);
    CopyWithGain(ppDst[5], ppSrc[5], gain, numSamples);
}
}}}  // namespace rw::audio::core

// @ 0x0112e980
namespace rw { namespace audio { namespace core {
void FUN_0112e980(void* p1, int p2)
{
    extern System_s0112_dca0* g_pAudioSystem; // 0x016e61a8
    g_pAudioSystem->Alloc(p2, (const char*)p1, 0x10, 0);
}
}}}  // namespace rw::audio::core

// @ 0x0112e9b0
namespace rw { namespace audio { namespace core {
void FUN_0112e9b0(int* s, int param_2, unsigned param_3, int param_4, u8 param_5)
{
    (void)param_4; (void)param_5;
    unsigned blocks = param_3 / (unsigned)((int)*(short*)((char*)s + 0xc2) *
                                          (int)(short)s[0x30]);
    typedef void (*SubmitFn)(int, unsigned, unsigned);
    ((SubmitFn)(*(int*)(s[0x2b])))(param_2, param_3, blocks);

    int n = (short)s[0x30];
    unsigned vals[8];
    int base = *(int*)((int)s * 5 + 200);
    int step = n ? (0x4000 / (n * 4)) : 0;
    for (int i = 0; i < n; ++i)
        vals[i] = (unsigned)(base + i * step);

    typedef void (*Submit2)(unsigned*, unsigned);
    ((Submit2)(*(int*)(s[0x2b]) + 4))(vals, blocks);
    FUN_01133450();
    SNDPKTPLAY_submit(s[0x28], vals);
    FUN_01133460();
    s[2] += blocks;
    s[0x31] += 1;
    *s += param_3;
}
}}}  // namespace rw::audio::core

// @ 0x0112eab0
namespace rw { namespace audio { namespace core {
void FUN_0112eab0(int p)
{
    if (*(int*)(p + 0xb0) == 0)
    {
        int i = 0;
        int* q = (int*)(p + 0xd8);
        do
        {
            if (q[4] == 0)
            {
                int chunk = Stream_GetChunk(*(void**)(p + 0x94));
                if (chunk == 0) return;
                FUN_0112e9b0((int*)p, *(int*)(chunk + 8), *(unsigned*)(chunk + 4), i, 1);
                *q = chunk;
            }
            ++i;
            ++q;
        } while (i < 4);
    }
    else
    {
        if (*(int*)(p + 0xb4) == 0)
        {
            *(int*)(p + 0xb4) = Stream_GetChunk(*(void**)(p + 0x94));
            ((Stream*)*(void**)(p + 0x94))->ReleaseChunk(*(void**)(p + 0xb4));
        }
        int chunk = Stream_GetChunk(*(void**)(p + 0x94));
        if (chunk != 0)
        {
            FUN_0112e9b0((int*)p, *(int*)(chunk + 8), *(unsigned*)(chunk + 4), 0, 0);
            *(int*)(p + 0xd8) = chunk;
            *(int*)(p + 0xb4) = 0;
            *(int*)(p + 0xb0) = 0;
        }
    }
}
}}}  // namespace rw::audio::core

// @ 0x0112eb70
namespace rw { namespace audio { namespace core {
void FUN_0112eb70(int id, int p)
{
    int i = 0;
    int* q = (int*)(p + 0xc8);
    while (i < 4)
    {
        if (id == *q) break;
        ++i;
        ++q;
    }
    *(int*)(p + 0xc4) -= 1;
    int chunk = *(int*)(p + 0xd8 + i * 4);
    if (chunk != 0)
    {
        ((Stream*)*(void**)(p + 0x94))->ReleaseChunk((void*)chunk);
        *(int*)(p + 0xd8 + i * 4) = 0;
    }
    *(int*)(p + 0xe8 + i * 4) = 0;
    if (*(int*)(p + 0xc4) == 0 && *(int*)(p + 0x90) == 0)
        *(int*)(p + 0xc) = 3;
    FUN_0112eab0(p);
}
}}}  // namespace rw::audio::core
