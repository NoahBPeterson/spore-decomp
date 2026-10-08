// Slice s011388f0: RenderWare 4 core audio -- SndPlayer1/Snd9Service/SinePlayer/SampleCapture glue.
// Built with VC .NET 2003 (cl 13.10) + /GL /LTCG; none of these are byte-exact from a single-object
// compile, so this is the complete behaviour-equivalent reconstruction.
// Types whose layout is only partly known are addressed by offset through A<T>(), matching the style
// of the other RenderWare slices (the shared "audio player" bases differ per derived class).
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <xmmintrin.h>

typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;

template <class T> static inline T& A(void* p, int off) { return *(T*)((char*)p + off); }
static inline char* RING(void* sys) { return *(char**)((char*)sys + 0x20) + *(unsigned*)((char*)sys + 0xb4); }

namespace rw { namespace audio { namespace core {

struct System;
struct Voice;
struct Decoder;
struct DecoderRegistry;
struct StreamPool;
struct PlugInDescRunTime;
struct Stream;

struct Attribute_t { union { double f64; float f32; }; };
struct PlugIn {
    void** vftable; System* mpSystem; Voice* mpVoice; Attribute_t* mpAttribute;
    PlugInDescRunTime* mpPlugInDescRunTime; float mLatencyInSamples; float mDecaySamples;
    unsigned int mCpuTicks; unsigned char mInputChannels; unsigned char mOutputChannels; unsigned char pad22[2];
};
struct TimerHandle {
    void* mItemHandle; void* mpCallback; void* mpContext; char* mpName;
    unsigned int mCpuTicks; unsigned char mStage; unsigned char mTimerVisibility; unsigned char pad16[2];
};
struct ChunkInfo { int f00; int size; char* pData; };
struct Stream {
    char pad00[4];
    int QueueFile(int, int, int, void*, int); ChunkInfo* GetChunk();
    int FUN_011e6bf0(); int FUN_011e6c00(int); int FUN_011e6c40(); int FUN_011e6c80(int); int FUN_011e7c70(ChunkInfo*);
};
struct StreamPool { void* CreateStream(float, void*, void*); void ReleaseStream(void*); };
struct System {
    char pad00[0x20]; char* mpCommandBuffer; char pad24[0x90]; unsigned int mCommandIndex; // +0xb4
    void* Alloc(int size, const char* name, int align, int alloc); void Free(void* p, int alloc);
    void RemoveTimer(TimerHandle* t); int Lock(); int Unlock(); DecoderRegistry* GetDecoderRegistry();
};
struct Decoder {
    char pad00[0x20]; unsigned short mNumChannels;
    char FUN_0114c8c0(char*, unsigned, int, int, void*, int); void FUN_01133f40();
};
struct DecoderRegistry { int FUN_01133ed0(int); Decoder* DecoderFactory(int, int, int, System*); };
struct RequestExternal {
    double streamFileOffset; char* pSampleData; int loopStartStreamOffset; int gigaSamplesInRam;
    int numSamplesFed; int numBytesFed; char* pStreamLoopFileName; StreamPool* pStreamPool;
    void* streamHandle; Stream* pRwCoreStream; int streamerRequestId; char* pNextChunk;
    char* pLoopStartChunk; void* pSeekData; int playerSkip; unsigned seekChunkOffset;
    int seekDataVersion; unsigned char codec; unsigned char playType; unsigned char feedSlotLatest;
    unsigned char expelMode; bool seekChunkIsNewFeed; unsigned char pad4d[3];
};
struct FeedDesc {
    ChunkInfo* pChunkInfo; Stream* pRwCoreStream; int chunkSamplesPlayed;
    unsigned char decoderRequestHandle; unsigned char feedState; unsigned char requestIndex; unsigned char pad0F;
};
struct RequestInternal {
    double streamFileOffset; Decoder* pDecoder; float handle; float f10; int samplesFed; int f18;
    void* f1C; int f20; int f24; unsigned short numChannels; unsigned char state; unsigned char codec; int f2C;
};
struct SndPlayer1 : PlugIn {
    Attribute_t mAttribute[3]; TimerHandle mTimerHandle; RequestExternal* mpRequestExternal;
    FeedDesc mFeedDesc[20]; Decoder* mpLoadedDecoder; float mCurrentRequestHandle; float mCurrentRequestSampleRate;
    int mCurrentRequestSamplesPlayed; int mCurrentRequestNumSamples; float* mpRequestHandle;
    float mLastRequestHandleProcessed; float mLastRequestHandleSuccessfullyProcessed; float mPreviousSampleRate;
    unsigned short mSamplesRequested; unsigned short mDeclickBufferOffset; unsigned short mRequestInternalOffset;
    unsigned char mMaxChannels; unsigned char mNextFreeRequest; unsigned char mNextRequestToFree;
    unsigned char mCurrentRequest; unsigned char mMaxRequests; unsigned char mDcOffsetsGathered;
    unsigned char mNumDeclickSamples; unsigned char mNextFeedSlotToFill; unsigned char mNextFeedSlotToFree;
    unsigned char mTimerAdded;
    RequestInternal* internal(int i) { return (RequestInternal*)((char*)this + mRequestInternalOffset + i * 0x30); }
    void FreeFinishedRequests(); void FUN_01137950();                     // 0x01137bc0 / 0x01137950
    bool StartRequest(int); bool HandleLoopStart(int);                    // 0x011387b0 / 0x01138570
    bool HandleSampleEnd(int, u8*); bool StreamNextChunk(int, int, int);  // 0x01138640 / 0x011384b0
};

// Stub owner for the __thiscall helpers whose real class is only partly known.
struct AudioObj {
    void F_d00();              // 0x01138d00
    void F_000(int, int*);     // 0x01139000
    void F_0b0();              // 0x011390b0
    void F_2c0(int, int*);     // 0x011392c0
    void F_4b0();              // 0x011394b0
    void F_660(int, int*);     // 0x01139660
    void F_730();              // 0x01139730
    void F_820(int, int*);     // 0x01139820
    void F_8b0();              // 0x011398b0
};
// SubMix mix-input link/unlink helpers: __thiscall (this = the input node).
struct SubMix {
    void FUN_01137420(int, int);   // 0x01137420
    void FUN_01137450(void*);      // 0x01137450
};
// TimerManager::AddTimer is __thiscall: this = TimerManager, 6 stack args, ret 8.
struct TimerMgr {
    char AddTimer(void*, void*, void*, const char*, int, int); // 0x0112d8e0
};
} } } // namespace rw::audio::core

using namespace rw::audio::core;

extern rw::audio::core::System* g_pSystem;         // 0x016e61a8
extern const float g_one;                          // 0x01485720
extern u8 g_sndCfg00, g_sndCfg01, g_sndCfg02;      // 0x016e7c00,0x016e7bff,0x016e7bfa
extern void* g_p15bbb20;                           // 0x015bbb20
extern void* g_pTimerList;                         // 0x016e6288
extern void* g_pTimerList2;                        // 0x016e628c
extern const float g_tab014b23e0[];                // 0x014b23e0

extern "C" {
int  FUN_01142690(void);                            // 0x01142690
int  MIX_create(void* desc);                        // 0x01142a80
void SNDVOICEI_free(void);                          // 0x01141020
int  SNDSYS_restore(void);                          // 0x0113ef00
int  FUN_01141710(void);                            // 0x01141710
int  FUN_011332c0(void);                            // 0x011332c0
int  FUN_01133290(void);                            // 0x01133290
int  FUN_011431a0(void* ptrs, int n);               // 0x011431a0
int  FUN_0113f940(void);                            // 0x0113f940
void FUN_0112d590(void** a, void** b, float g, int c, int d, int e); // 0x0112d590
void* FUN_011373c0(void);                           // 0x011373c0
int  FUN_0114d770(void* ctx);                       // 0x0114d770
void* operator_new_arr(unsigned sz, int a, unsigned n); // 0x011e073e
double ceil(double);                                // msvcr90!ceil
int strcmp(const char*, const char*);
}

namespace rw { namespace audio { namespace core {

// @ 0x011388f0  SndPlayer1 timer client
void __cdecl FUN_011388f0(SndPlayer1* self)
{
    if (A<char>(A<void*>(self, 8), 0x47) == 2)
        return;
    self->FUN_01137950();
    self->FreeFinishedRequests();
    u8 b = self->mCurrentRequest;
    u16 off = self->mRequestInternalOffset;
    RequestInternal* ri = (RequestInternal*)((char*)self + off + b * 0x30);
    char st = ri->state;
    if (st == 4 || st == 0) {
        self->mAttribute[0].f32 = self->mCurrentRequestHandle;
        self->mAttribute[2].f64 = 0.0; self->mAttribute[1].f64 = 0.0;
        return;
    }
    self->mAttribute[0].f32 = self->mCurrentRequestHandle;
    self->mAttribute[2].f64 = (double)((float)self->mCurrentRequestNumSamples / self->mCurrentRequestSampleRate);
    self->mAttribute[1].f64 = (double)((float)self->mCurrentRequestSamplesPlayed / self->mCurrentRequestSampleRate);
    while (ri->samplesFed == 0) {
        b = (u8)(b + 1); b = (b == self->mMaxRequests) ? 0 : b;
        ri = (RequestInternal*)((char*)self + off + b * 0x30);
        st = ri->state;
        if (st == 4 || st == 0) return;
    }
    for (;;) {
        for (;;) {
            if (ri->state == 4 || ri->state == 0) return;
            if (self->mFeedDesc[self->mNextFeedSlotToFill].feedState != 0) return;
            void* h = self->mpRequestExternal[b].streamHandle;
            if (h) A<float>(h, 8) = A<float>(A<void*>(self, 8), 0x38);
            if (ri->state == 1) { if (!self->StartRequest(b)) return; ri->state = 2; }
            if (ri->state == 2 && self->mFeedDesc[self->mNextFeedSlotToFill].feedState == 0) break;
            b = (u8)(b + 1); b = (b == self->mMaxRequests) ? 0 : b;
            if (b == self->mCurrentRequest) return;
            ri = (RequestInternal*)((char*)self + off + b * 0x30);
        }
        int sf = self->mpRequestExternal[b].numSamplesFed;
        if (sf == ri->f18) { if (!self->HandleLoopStart(b)) return; }
        else if (sf == ri->samplesFed) {
            u8 out = 0;
            if (!self->HandleSampleEnd(b, &out)) return;
            if (out) {
                ri->state = 3;
                b = (u8)(b + 1); b = (b == self->mMaxRequests) ? 0 : b;
                if (b == self->mCurrentRequest) return;
                ri = (RequestInternal*)((char*)self + off + b * 0x30);
            }
        } else { if (!self->StreamNextChunk(b, 0, 0)) return; }
    }
}

// @ 0x01138af0  SndPlayer1::CreateInstance
bool __cdecl FUN_01138af0(SndPlayer1* self, float* pReq)
{
    if (pReq == 0) pReq = (float*)1;
    else pReq = (float*)_mm_cvtss_si32(_mm_load_ss(pReq));   /* cvtss2si: round to nearest */
    if (self) {
        *(void**)self = (void*)0x14ab718;
        /* PlugIn::Initialize<...>(self+0x40) */
        A<int>(self, 0x40) = 0;
        A<int>(self, 0x4c) = 0x13f9034;
        A<int>(self, 0x50) = 0;
        A<u8>(self, 0x54) = 3;
    }
    int a = (int)self;
    int b = (a + 0x1d7) & 0xfffffff8;
    self->mRequestInternalOffset = (u16)((((int)A<u8>(self, 0x21) * 4 + b + 7) & 0xfffffff8) - a);
    self->mDeclickBufferOffset = (u16)(b - a);
    A<int>(self, 0xc) = (int)((char*)self + 0x28);
    self->mTimerAdded = 0;
    void* buf = self->mpSystem->Alloc((int)pReq * 0x50 + 4, "SndPlayer1 RequestHandle and RequestExternal array", 0x10, 0);
    self->mpRequestHandle = (float*)buf;
    if (!buf) return false;
    self->mpRequestExternal = (RequestExternal*)((char*)buf + 4);
    self->mMaxRequests = (u8)(int)pReq;
    for (int i = 0, off = 0; i < (int)pReq; i++, off += 0x30)
        *(u8*)((char*)self + self->mRequestInternalOffset + off + 0x2a) = 0;
    self->mAttribute[2].f64 = 0.0; self->mAttribute[1].f64 = 0.0;
    self->mMaxChannels = A<u8>(self, 0x21);
    A<float>(self, 0x28) = 0.0f;
    *self->mpRequestHandle = 0.0f;
    self->mLastRequestHandleProcessed = 0.0f;
    self->mLastRequestHandleSuccessfullyProcessed = 0.0f;
    self->mCurrentRequest = 0; self->mNextRequestToFree = 0; self->mNextFreeRequest = 0;
    self->mCurrentRequestHandle = 0.0f;
    self->mCurrentRequestSampleRate = A<float>(self->mpSystem, 0xc0);
    self->mCurrentRequestSamplesPlayed = 0; self->mCurrentRequestNumSamples = 0;
    self->mNumDeclickSamples = 0; self->mDcOffsetsGathered = 0;
    self->mPreviousSampleRate = A<float>(self->mpSystem, 0xc0);
    self->mNextFeedSlotToFill = 0; self->mNextFeedSlotToFree = 0;
    for (int i = 0; i < 20; i++) { A<int>(self, 0x5c + i * 0x10) = 0; A<u8>(self, 0x5c + i * 0x10 + 0xd) = 0; }
    char ok = ((TimerMgr*)((char*)self->mpSystem + 0x60))->AddTimer(
                   (void*)((char*)self + 0x40), (void*)&FUN_011388f0, self, "SndPlayer", 1, 1);
    if (ok != 0)
        return false;
    self->mTimerAdded = 1;
    return true;
}

// @ 0x01138d00  Snd9Service::ReleaseEvent
void AudioObj::F_d00()
{
    void* self = this;
    if (A<char>(self, 0x68) == 1)
        A<System*>(self, 4)->RemoveTimer((TimerHandle*)((char*)self + 0x24));
    SNDSYS_restore();
    int p = A<int>(self, 0x3c);
    if (p) { g_pSystem->Free((void*)p, 0); A<int>(self, 0x3c) = 0; }
}

// @ 0x01138d40  Snd9Service::UpdateSnd9SampleRate
void __stdcall FUN_01138d40(float rate)
{
    struct Desc { int value; u8 f4; u8 f5; u8 pad6[2]; void* cb; u8 f0c; u8 pad0d[3]; } d;
    FUN_01142690();
    d.value = _mm_cvtss_si32(_mm_load_ss(&rate));
    d.f4 = g_sndCfg02;
    d.f5 = (u8)(g_sndCfg00 + g_sndCfg01);
    d.cb = (void*)&SNDVOICEI_free;
    d.f0c = 0;
    MIX_create(&d);
}

// @ 0x01138d90  Snd9Service timer client
void __cdecl FUN_01138d90(void* self)
{
    int local[6];
    local[0] = A<int>(self, 0x40); local[1] = A<int>(self, 0x44); local[2] = A<int>(self, 0x48);
    local[3] = A<int>(self, 0x4c); local[4] = A<int>(self, 0x50); local[5] = A<int>(self, 0x54);
    float sr = A<float>(A<void*>(self, 4), 0xc0);
    if (sr != A<float>(self, 0x58)) {
        FUN_01138d40(sr);
        A<float>(self, 0x58) = sr;
        A<int>(self, 0x5c) = 0; A<int>(self, 0x60) = 0; A<int>(self, 0x64) = 0;
    }
    FUN_01141710();
    int budget = 0x100;
    for (;;) {
        if (A<int>(self, 0x64) < 1) {
            A<int>(self, 0x5c) = A<int>(self, 0x5c) + 1;
            FUN_011332c0(); FUN_01133290();
            int v = (A<int>(self, 0x5c) * _mm_cvtss_si32(_mm_load_ss(&sr))) / 100;
            unsigned rem = (unsigned)((v - A<int>(self, 0x60)) & 0xffffff0);
            A<int>(self, 0x64) = (int)rem;
            A<int>(self, 0x60) = (int)(rem + A<int>(self, 0x60));
            if (A<int>(self, 0x5c) > 30000) { A<int>(self, 0x5c) = 0; A<int>(self, 0x60) = 0; }
        }
        int take = A<int>(self, 0x64);
        int use = take;
        if (budget <= take) use = budget;
        budget -= use;
        A<int>(self, 0x64) = take - use;
        FUN_011431a0(local, use);
        FUN_0113f940();
        int adv = use * 4;
        local[0] += adv; local[1] += adv; local[2] += adv;
        local[3] += adv; local[4] += adv; local[5] += adv;
        if (budget <= 0) break;
    }
}

// @ 0x01138ec0  Snd9Service::CreateInstance
bool __cdecl FUN_01138ec0(void* self)
{
    if (self) {
        *(void**)self = (void*)0x14b085c;
        /* PlugIn::Initialize<...>(self+0x24) */
        A<int>(self, 0x24) = 0;
        A<int>(self, 0x30) = 0x13f9034;
        A<int>(self, 0x34) = 0;
        A<u8>(self, 0x38) = 3;
    }
    A<u8>(self, 0x68) = 0;
    void* buf = A<System*>(self, 4)->Alloc(0x1800, "rw::audio::core::Snd9Service::mpMixBufStart", 0x80, 0);
    A<int>(self, 0x3c) = (int)buf;
    if (!buf) return false;
    A<int>(self, 0x40) = (int)((char*)buf + 0x400);
    A<int>(self, 0x44) = (int)((char*)buf + 0x800);
    A<int>(self, 0x50) = (int)buf;
    A<int>(self, 0x48) = (int)((char*)buf + 0x1000);
    A<int>(self, 0x54) = (int)((char*)buf + 0x1400);
    A<int>(self, 0x4c) = (int)((char*)buf + 0xc00);
    A<float>(self, 0x58) = A<float>(A<void*>(self, 4), 0xc0);
    A<int>(self, 0x5c) = 0; A<int>(self, 0x60) = 0; A<int>(self, 0x64) = 0;
    char ok = ((TimerMgr*)((char*)A<void*>(self, 4) + 0x60))->AddTimer(
                   (void*)((char*)self + 0x24), (void*)&FUN_01138d90, self, "Snd9Service", 1, 1);
    if (ok != 0)
        return false;
    A<u8>(self, 0x68) = 1;
    return true;
}

// @ 0x01138f70  install Snd9Service plugin runtime description
void __cdecl FUN_01138f70(void) { g_p15bbb20 = (void*)0x15bbb38; }

// @ 0x01138f90  SinePlayer::PlayHandler
int __cdecl FUN_01138f90(void* rec)
{
    int o = A<int>(rec, 4);
    *(double*)((char*)o + 0x28) = *(double*)((char*)rec + 8);
    A<u8>((void*)o, 0x3c) = 1;
    return 0x10;
}

// @ 0x01138fb0  SinePlayer::StopHandler
int __cdecl FUN_01138fb0(void* rec)
{
    A<u8>((void*)A<int>(rec, 4), 0x3c) = 0;
    return 8;
}

// @ 0x01138fd0  SinePlayer init
bool __cdecl FUN_01138fd0(void* p)
{
    if (p) *(void**)p = (void*)0x14b0934;
    A<int>(p, 0xc) = (int)((char*)p + 0x30);
    A<u8>(p, 0x3c) = 0;
    A<float>(p, 0x38) = 0.0f; A<float>(p, 0x30) = 0.0f;
    return true;
}

// @ 0x01139000  SinePlayer command ring
void AudioObj::F_000(int cmd, int* param)
{
    void* self = this;
    System* sys = A<System*>(self, 4);
    char* rec = RING(sys);
    if (cmd == 0) {
        sys->mCommandIndex += 0x10;
        A<int>(rec, 4) = (int)self;
        A<int>(rec, 0) = (int)&FUN_01138f90;
        A<int>(rec, 8) = param[0]; A<int>(rec, 0xc) = param[1];
        return;
    }
    sys->mCommandIndex += 8;
    A<int>(rec, 0) = (int)&FUN_01138fb0;
    A<int>(rec, 4) = (int)self;
}

// @ 0x011390b0  SinePlayer process
void AudioObj::F_0b0()
{
    void* self = this;
    SubMix* mix = (SubMix*)((char*)self + 0x30);
    if (A<char>(self, 0x40) == 0) { mix->FUN_01137450(0); return; }
    // The original keeps dst[] immediately below the six output floats, so an out-of-range
    // channel read (count > 6) aliases dst[6] onto out[0]; mirror that with one block.
    struct { void* dst[6]; float out[6]; } b;
    b.dst[0] = &b.out[0]; b.dst[1] = &b.out[1]; b.dst[2] = &b.out[2];
    b.dst[3] = &b.out[3]; b.dst[4] = &b.out[4]; b.dst[5] = &b.out[5];
    void* src[6];
    src[0] = (char*)self + 0x44; src[1] = (char*)self + 0x48; src[2] = (char*)self + 0x4c;
    src[3] = (char*)self + 0x50; src[4] = (char*)self + 0x54; src[5] = (char*)self + 0x58;
    FUN_0112d590(b.dst, src, 1.0f, (int)A<u8>(self, 0x40), (int)A<u8>(self, 0x20), 1);
    mix->FUN_01137450(b.dst[0]);
    A<float>(self, 0x44) = 0.0f; A<float>(self, 0x4c) = 0.0f; A<float>(self, 0x48) = 0.0f;
    A<float>(self, 0x50) = 0.0f; A<float>(self, 0x54) = 0.0f; A<float>(self, 0x58) = 0.0f;
}

// @ 0x011391a0  SinePlayer record handler
int __cdecl FUN_011391a0(void* rec)
{
    void* self = A<void*>(rec, 4);
    ((AudioObj*)self)->F_0b0();
    g_pTimerList = g_pTimerList2;
    for (void* p = FUN_011373c0(); p; p = FUN_011373c0()) {
        if (strcmp((char*)rec + 0xc, (char*)p + 0x4c) == 0) {
            ((SubMix*)((char*)self + 0x30))->FUN_01137420(A<int>(self, 8), (int)p);
            break;
        }
    }
    return A<int>(rec, 8);
}

// @ 0x01139230  SinePlayer record handler (single)
int __cdecl FUN_01139230(void* rec)
{
    void* self = A<void*>(rec, 4);
    ((AudioObj*)self)->F_0b0();
    if (A<int>(rec, 8))
        ((SubMix*)((char*)self + 0x30))->FUN_01137420(A<int>(self, 8), A<int>(rec, 8));
    return 0xc;
}

// @ 0x01139260  SampleCapture-ish init
bool __cdecl FUN_01139260(void* p)
{
    if (p) { *(void**)p = (void*)0x14b0e5c; A<int>(p, 0x38) = 0; A<int>(p, 0x3c) = 0; A<u8>(p, 0x40) = 0; }
    A<float>(p, 0x5c) = g_one; A<float>(p, 0x28) = g_one;
    A<u8>(p, 0x60) = 0;
    A<int>(p, 0xc) = (int)((char*)p + 0x28);
    A<float>(p, 0x44) = 0.0f; A<float>(p, 0x48) = 0.0f; A<float>(p, 0x4c) = 0.0f;
    A<float>(p, 0x50) = 0.0f; A<float>(p, 0x54) = 0.0f; A<float>(p, 0x58) = 0.0f;
    return true;
}

// @ 0x011392c0  SinePlayer command ring (named)
void AudioObj::F_2c0(int cmd, int* param)
{
    void* self = this;
    System* sys = A<System*>(self, 4);
    char* rec = RING(sys);
    if (cmd == 0) {
        sys->mCommandIndex += 0xc;
        A<int>(rec, 4) = (int)self; A<int>(rec, 0) = (int)&FUN_01139230; A<int>(rec, 8) = param[0];
        return;
    }
    char* name = (char*)param[0];
    char* e = name; while (*e) e++;
    unsigned len = (unsigned)(e - name) + 1;
    rec = RING(sys);
    unsigned rs = (len + 0x10) & ~3u;
    sys->mCommandIndex += rs;
    A<int>(rec, 0) = (int)&FUN_011391a0; A<int>(rec, 4) = (int)self; A<int>(rec, 8) = (int)rs;
    char* d = rec + 0xc;
    for (char* s = name; ; ) { char c = *s++; *d++ = c; if (!c) break; }
}

// @ 0x01139390  SampleCapture stop handler
int __cdecl FUN_01139390(void* rec)
{
    void* self = A<void*>(rec, 4);
    if (A<int>(self, 0x54)) {
        A<int>(self, 0x54) = 0;
        if (A<char>(self, 0x7e)) { A<System*>(self, 4)->RemoveTimer((TimerHandle*)((char*)self + 0x24)); A<char>(self, 0x7e) = 0; }
        A<float>(self, 0x40) = 0.0f;
    }
    return 8;
}

// @ 0x011393d0  SampleCapture timer callback
void __cdecl FUN_011393d0(void* self)
{
    int p = A<int>(self, 0x70);
    if (p == 0) { operator_new_arr((unsigned)A<int>(self, 0x78), 0, (unsigned)A<int>(self, 0x6c)); p = A<int>(self, 0x6c); }
    ((void(__cdecl*)(void*, int, void*))A<int>(self, 0x54))((void*)A<int>(self, 0x78), p, (void*)A<int>(self, 0x58));
    A<int>(self, 0x70) = 0;
}

// @ 0x01139450  SampleCapture ctor
bool __cdecl FUN_01139450(void* p)
{
    if (p) {
        *(void**)p = (void*)0x14b1788;
        /* PlugIn::Initialize<...>(p+0x24) */
        A<int>(p, 0x24) = 0;
        A<int>(p, 0x30) = 0x13f9034;
        A<int>(p, 0x34) = 0;
        A<u8>(p, 0x38) = 3;
    }
    A<float>(p, 0x40) = 0.0f;
    A<int>(p, 0xc) = (int)((char*)p + 0x40);
    u16 u = (u16)((((int)p + 0x87) & 0xfffffff8) - (int)p);
    A<u16>(p, 0x74) = u;
    A<u8>(p, 0x7e) = 0; A<int>(p, 0x78) = 0; A<int>(p, 0x70) = 0; A<int>(p, 0x54) = 0;
    operator_new_arr((unsigned)((char*)p + u), 0, 0x90);
    return true;
}

// @ 0x011394b0  SampleCapture destructor
void AudioObj::F_4b0()
{
    void* self = this;
    if (A<int>(self, 0x54)) {
        A<int>(self, 0x54) = 0;
        if (A<char>(self, 0x7e)) { A<System*>(self, 4)->RemoveTimer((TimerHandle*)((char*)self + 0x24)); A<char>(self, 0x7e) = 0; }
        A<float>(self, 0x40) = 0.0f;
    }
    int b = A<int>(self, 0x78);
    if (b) A<System*>(self, 4)->Free((void*)b, 0);
}

// @ 0x01139500  SampleCapture::StartHandler
int __cdecl FUN_01139500(void* rec)
{
    void* self = A<void*>(rec, 4);
    if (A<int>(self, 0x54) != 0)
        return A<int>(rec, 8);
    A<u8>(self, 0x7e) = 0; A<int>(self, 0x70) = 0;
    A<float>(self, 0x48) = A<float>(rec, 0xc);
    A<int>(self, 0x50) = _mm_cvtss_si32(_mm_load_ss((float*)((char*)rec + 0x14)));
    A<int>(self, 0x4c) = _mm_cvtss_si32(_mm_load_ss((float*)((char*)rec + 0x10)));
    A<int>(self, 0x54) = A<int>(rec, 0x18);
    A<int>(self, 0x58) = A<int>(rec, 0x1c);
    if (A<int>(self, 0x50) == 0) A<u16>(self, 0x76) = 2;
    double v = ceil((double)(A<float>(self, 0x48) * 256.0f) / A<float>(A<void*>(self, 4), 0xc0));
    A<int>(self, 0x60) = (int)v;
    unsigned sz = ((unsigned)A<u16>(self, 0x76) * (unsigned)A<int>(self, 0x60) * (unsigned)A<int>(self, 0x4c) + 0xf) & 0xfffffff0u;
    A<int>(self, 0x6c) = (int)sz;
    void* buf = A<System*>(self, 4)->Alloc((int)sz, "rw::audio::core::SampleCapture::mpBuf", 0x10, 0);
    A<int>(self, 0x78) = (int)buf;
    if (!buf) return 0;
    A<int>(self, 0x5c) = (int)0xbf800000;
    A<int>(self, 0x64) = 0; A<int>(self, 0x68) = 0; A<u8>(self, 0x7c) = 0; A<u8>(self, 0x7d) = 2;
    char ok = ((TimerMgr*)((char*)A<void*>(self, 4) + 0x60))->AddTimer(
                   (void*)((char*)self + 0x24), (void*)&FUN_011393d0, self, "SampleCapture", 1, 1);
    if (ok == 0) {
        A<u8>(self, 0x7e) = 1; A<float>(self, 0x40) = g_one;
    }
    return A<int>(rec, 8);
}

// @ 0x01139660  SampleCapture command ring
void AudioObj::F_660(int cmd, int* param)
{
    void* self = this;
    System* sys = A<System*>(self, 4);
    if (cmd == 0) {
        char* rec = RING(sys);
        sys->mCommandIndex += 0x20;
        A<int>(rec, 4) = (int)self; A<int>(rec, 0) = (int)&FUN_01139500; A<int>(rec, 8) = 0x20;
        A<int>(rec, 0xc) = param[0]; A<int>(rec, 0x10) = param[1]; A<int>(rec, 0x14) = param[2];
        A<int>(rec, 0x18) = param[3]; A<int>(rec, 0x1c) = param[4];
        return;
    }
    if (cmd == 1) {
        char* rec = RING(sys);
        sys->mCommandIndex += 8;
        A<int>(rec, 0) = (int)&FUN_01139390; A<int>(rec, 4) = (int)self;
    }
}

// @ 0x01139730  player process (clear)
void AudioObj::F_730()
{
    void* self = this;
    ((SubMix*)((char*)self + 0x24))->FUN_01137450((char*)self + 0x38);
    A<float>(self, 0x38) = 0.0f; A<float>(self, 0x3c) = 0.0f; A<float>(self, 0x40) = 0.0f;
    A<float>(self, 0x44) = 0.0f; A<float>(self, 0x48) = 0.0f; A<float>(self, 0x4c) = 0.0f;
}

// @ 0x01139770  player record handler
int __cdecl FUN_01139770(void* rec)
{
    void* self = A<void*>(rec, 4);
    ((SubMix*)((char*)self + 0x24))->FUN_01137450((char*)self + 0x38);
    A<float>(self, 0x38) = 0.0f; A<float>(self, 0x3c) = 0.0f; A<float>(self, 0x40) = 0.0f;
    A<float>(self, 0x44) = 0.0f; A<float>(self, 0x48) = 0.0f; A<float>(self, 0x4c) = 0.0f;
    if (A<int>(rec, 8)) {
        ((SubMix*)((char*)self + 0x24))->FUN_01137420(A<int>(self, 8), A<int>(rec, 8));
        A<u8>(self, 0x50) = (u8)(int)A<float>(rec, 0xc);
        A<u8>(self, 0x51) = (u8)(int)A<float>(rec, 0x10);
        A<u8>(self, 0x52) = (u8)(int)A<float>(rec, 0x14);
    }
    return 0x18;
}

// @ 0x011397e0  player ctor
bool __cdecl FUN_011397e0(void* p)
{
    if (p) { *(void**)p = (void*)0x14b1c8c; A<int>(p, 0x2c) = 0; A<int>(p, 0x30) = 0; A<u8>(p, 0x34) = 0; }
    A<float>(p, 0x38) = 0.0f; A<float>(p, 0x3c) = 0.0f; A<float>(p, 0x40) = 0.0f;
    A<float>(p, 0x44) = 0.0f; A<float>(p, 0x48) = 0.0f; A<float>(p, 0x4c) = 0.0f;
    return true;
}

// @ 0x01139820  player command ring
void AudioObj::F_820(int cmd, int* param)
{
    void* self = this;
    System* sys = A<System*>(self, 4);
    char* rec = RING(sys);
    sys->mCommandIndex += 0x18;
    A<int>(rec, 4) = (int)self; A<int>(rec, 0) = (int)&FUN_01139770;
    A<int>(rec, 8) = param[0]; A<int>(rec, 0xc) = param[1];
    A<int>(rec, 0x10) = param[2]; A<int>(rec, 0x14) = param[3];
}

// @ 0x011398b0  player destructor
void AudioObj::F_8b0()
{
    void* self = this;
    for (int i = 0; i < 6; i++)
        FUN_0114d770((char*)self + 0x2b4 + i * 0x3c);
    for (int i = 0; i < (int)A<u8>(self, 0x439); i++)
        FUN_0114d770((char*)self + 0x88 + i * 0x3c);
    if (A<char>(self, 0x43a))
        g_pSystem->RemoveTimer((TimerHandle*)((char*)self + 0x13c));
}

// @ 0x01139920  frequency/table converter  (__stdcall: ret 0xc)
int __stdcall FUN_01139920(float* src, int* out, float f)
{
    int i = 0;
    out[5] = 0;
    float* p = src;
    int n = 6;
    do {
        float a, b;
        if (f <= 48000.0f) { a = 1.0f; b = f; }
        else { a = f * 2.0833333e-05f; b = 48000.0f; }
        float lim = b * (*p * 0.002900232f);
        for (; i < 0x674; i++) {
            if (g_tab014b23e0[i] > lim) { *out = (int)g_tab014b23e0[i]; i++; break; }
        }
        if (a > 1.0f) *out = (int)((float)*out * a);
        out++; p++;
    } while (--n != 0);
    return n + 1;
}

} } } // namespace rw::audio::core
