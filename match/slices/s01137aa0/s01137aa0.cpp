// Slice s01137aa0: RenderWare 4 core audio -- rw::audio::core::SndPlayer1 request/stream handling.
// Built with VC .NET 2003 (cl 13.10) + /GL /LTCG, so most of these cannot be byte-exact from a
// single-object compile; the source below is the complete behaviour-equivalent reconstruction.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <xmmintrin.h>
#include <emmintrin.h>

extern "C" void* memcpy(void*, const void*, unsigned int);

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
    void** vftable;                          // +0x00
    System* mpSystem;                        // +0x04
    Voice* mpVoice;                          // +0x08
    Attribute_t* mpAttribute;                // +0x0c
    PlugInDescRunTime* mpPlugInDescRunTime;  // +0x10
    float mLatencyInSamples;                 // +0x14
    float mDecaySamples;                     // +0x18
    unsigned int mCpuTicks;                  // +0x1c
    unsigned char mInputChannels;            // +0x20
    unsigned char mOutputChannels;           // +0x21
    unsigned char pad22[2];
};

struct TimerHandle {
    void* mItemHandle;              // +0x00
    void* mpCallback;               // +0x04
    void* mpContext;                // +0x08
    char* mpName;                   // +0x0c
    unsigned int mCpuTicks;         // +0x10
    unsigned char mStage;           // +0x14
    unsigned char mTimerVisibility; // +0x15
    unsigned char pad16[2];
};

struct ChunkInfo {
    int   f00;      // +0x00
    int   size;     // +0x04
    char* pData;    // +0x08
};

struct Stream {
    char pad00[4];
    int  QueueFile(int a0, int a1, int a2, void* cb, int cbArg); // 0x011e69d0
    ChunkInfo* GetChunk();                                       // 0x011e6b50
    int  FUN_011e6bf0();                                         // 0x011e6bf0
    int  FUN_011e6c00(int);                                      // 0x011e6c00
    int  FUN_011e6c40();                                         // 0x011e6c40
    int  FUN_011e6c80(int);                                      // 0x011e6c80
    int  FUN_011e7c70(ChunkInfo*);                               // 0x011e7c70
};

struct StreamPool {
    void* CreateStream(float rate, void* cb, void* ctx);         // 0x0112dfa0
    void  ReleaseStream(void* handle);                           // 0x0112e1e0
};

struct System {
    char pad00[0x20];
    char* mpCommandBuffer;       // +0x20
    char pad24[0x90];
    unsigned int mCommandIndex;  // +0xb4

    void* Alloc(int size, const char* name, int align, int alloc); // 0x0112c820
    void  Free(void* p, int alloc);                                // 0x0112c850
    void  RemoveTimer(TimerHandle* t);                             // 0x0112dad0
    int   Lock();                                                  // 0x0112c600
    int   Unlock();                                                // 0x0112c620
    DecoderRegistry* GetDecoderRegistry();                         // 0x0112dc80
};

struct Voice {
    char pad00[0x38];
    float mPriority;             // +0x38
    void  FUN_0112e450();        // 0x0112e450
};

struct Decoder {
    char pad00[0x20];
    unsigned short mNumChannels; // +0x20
    char FUN_0114c8c0(char* data, unsigned int size, int flag,
                      int a3, void* a4, int a5);                 // 0x0114c8c0
    void FUN_01133f40();                                         // 0x01133f40
};

struct DecoderRegistry {
    int  FUN_01133ed0(int key);                                  // 0x01133ed0
    Decoder* DecoderFactory(int codecObj, int codec, int a, System* sys); // 0x01133fc0
};

struct RequestExternal {           // size 0x50 (PDB)
    double streamFileOffset;       // +0x00
    char*  pSampleData;            // +0x08
    int    loopStartStreamOffset;  // +0x0c
    int    gigaSamplesInRam;       // +0x10
    int    numSamplesFed;          // +0x14
    int    numBytesFed;            // +0x18
    char*  pStreamLoopFileName;    // +0x1c
    StreamPool* pStreamPool;       // +0x20
    void*  streamHandle;           // +0x24
    Stream* pRwCoreStream;         // +0x28
    int    streamerRequestId;      // +0x2c
    char*  pNextChunk;             // +0x30
    char*  pLoopStartChunk;        // +0x34
    void*  pSeekData;              // +0x38
    int    playerSkip;             // +0x3c
    unsigned int seekChunkOffset;  // +0x40
    int    seekDataVersion;        // +0x44
    unsigned char codec;           // +0x48
    unsigned char playType;        // +0x49
    unsigned char feedSlotLatest;  // +0x4a
    unsigned char expelMode;       // +0x4b
    bool   seekChunkIsNewFeed;     // +0x4c
    unsigned char pad4d[3];
};

struct FeedDesc {                  // size 0x10 (PDB)
    ChunkInfo* pChunkInfo;         // +0x00
    Stream* pRwCoreStream;         // +0x04
    int     chunkSamplesPlayed;    // +0x08
    unsigned char decoderRequestHandle; // +0x0c
    unsigned char feedState;       // +0x0d
    unsigned char requestIndex;    // +0x0e
    unsigned char pad0F;
};

// Per-request internal descriptor (stride 0x30): this + mRequestInternalOffset + i*0x30.
struct RequestInternal {
    double streamFileOffset;       // +0x00
    Decoder* pDecoder;             // +0x08
    float  handle;                 // +0x0c
    float  f10;                    // +0x10
    int    samplesFed;             // +0x14
    int    f18;                    // +0x18
    void*  f1C;                    // +0x1c
    int    f20;                    // +0x20
    int    f24;                    // +0x24
    unsigned short numChannels;    // +0x28
    unsigned char state;           // +0x2a
    unsigned char codec;           // +0x2b
    int    f2C;                    // +0x2c
};  // 0x30

struct SndPlayer1 : PlugIn {
    Attribute_t mAttribute[3];                    // +0x28
    TimerHandle mTimerHandle;                     // +0x40
    RequestExternal* mpRequestExternal;           // +0x58
    FeedDesc mFeedDesc[20];                       // +0x5c
    Decoder* mpLoadedDecoder;                     // +0x19c
    float mCurrentRequestHandle;                  // +0x1a0
    float mCurrentRequestSampleRate;              // +0x1a4
    int   mCurrentRequestSamplesPlayed;           // +0x1a8
    int   mCurrentRequestNumSamples;              // +0x1ac
    float* mpRequestHandle;                       // +0x1b0
    float mLastRequestHandleProcessed;            // +0x1b4
    float mLastRequestHandleSuccessfullyProcessed;// +0x1b8
    float mPreviousSampleRate;                    // +0x1bc
    unsigned short mSamplesRequested;             // +0x1c0
    unsigned short mDeclickBufferOffset;          // +0x1c2
    unsigned short mRequestInternalOffset;        // +0x1c4
    unsigned char mMaxChannels;                   // +0x1c6
    unsigned char mNextFreeRequest;               // +0x1c7
    unsigned char mNextRequestToFree;             // +0x1c8
    unsigned char mCurrentRequest;                // +0x1c9
    unsigned char mMaxRequests;                   // +0x1ca
    unsigned char mDcOffsetsGathered;             // +0x1cb
    unsigned char mNumDeclickSamples;             // +0x1cc
    unsigned char mNextFeedSlotToFill;            // +0x1cd
    unsigned char mNextFeedSlotToFree;            // +0x1ce
    unsigned char mTimerAdded;                    // +0x1cf

    RequestInternal* internal(int i)
    { return (RequestInternal*)((char*)this + mRequestInternalOffset + i * 0x30); }

    void  FreeRequest(int index);                         // 0x01137aa0
    void  FreeFinishedRequests();                         // 0x01137bc0
    void  Shutdown();                                     // 0x01137c90
    void  SendCommand(int cmd, void* param);              // 0x01138130
    char* FeedChunk(char* data, int index, char a, char b);// 0x01138050
    bool  StreamNextChunk(int index, int a3, int a4);     // 0x011384b0
    bool  HandleLoopStart(int index);                     // 0x01138570
    bool  HandleSampleEnd(int index, unsigned char* out); // 0x01138640
    bool  StartRequest(int index);                        // 0x011387b0
    void  FUN_011376d0(int a, int b);                     // 0x011376d0
    void  FUN_011377f0(int a, int b, int c);              // 0x011377f0
    void  FUN_01137950();                                 // 0x01137950
    void  FUN_011379f0(int* out);                         // 0x011379f0
};

// Ring command record: [0]=callback, [1]=context.  Slice-8 address range holds 0x01137a30.
struct PlayRec {
    void* code;             // +0x00
    SndPlayer1* self;       // +0x04
    double f08;             // +0x08
    double f10;             // +0x10
    double f18;             // +0x18
    int    f20;             // +0x20
    int    f24;             // +0x24
    int    f28;             // +0x28
    unsigned short recSize; // +0x2c
    unsigned char f2e;      // +0x2e
    unsigned char f2f;
    float  f30;             // +0x30
    int    f34;
    char   name[1];         // +0x38
};

// Payload the game passes to SendCommand (cmd 5); cmd 0 passes a different descriptor.
struct CmdPayload {
    double f00;
    double f08;
    double f10;
    int    i18;
    int    i1c;
    int    i20;
    int    i24;
    float  f28;
    float  f2c;
};

// cmd 0's parameter: name pointer sits at +0x10 (the original copies param+0x10 -> struct+0x18).
struct CmdParam {
    double f00;
    double f08;
    int    i10;
    int    i14;
    int    i18;
    float  f1c;
    float  f20;
};

} } } // namespace rw::audio::core

using namespace rw::audio::core;

extern rw::audio::core::System* g_pSystem;      // 0x016e61a8
extern const float g_one;                        // 0x01485720
extern const float g_reqHandleMax;               // 0x014ab748
extern const int   g_codecTable[];               // 0x014ab6f8
extern const float g_u32ToFloat;                 // 0x013f4fd0

// ring callbacks / out-of-slice callees
extern "C" int FUN_01137cd0(void* rec);          // 0x01137cd0
extern "C" int FUN_01137a30(void* rec);          // 0x01137a30
extern "C" int FUN_01137d60(char* data, unsigned int size, int, int, int, int, unsigned int* out);
rw::audio::core::StreamPool* __cdecl FUN_0112df80(int id);   // 0x0112df80
char __cdecl FUN_011e0744(void* dst, const void* src, unsigned int n); // 0x011e0744

namespace rw { namespace audio { namespace core {

void __cdecl FreeAllRequests(SndPlayer1* self);  // 0x01137c30

// @ 0x01137aa0  SndPlayer1::FreeRequest
void SndPlayer1::FreeRequest(int index)
{
    System* sys = mpSystem;
    RequestInternal* ri = internal(index);
    RequestExternal* re = &mpRequestExternal[index];
    Decoder* dec = ri->pDecoder;
    if (dec) {
        void (*cb)(Decoder*) = *(void (**)(Decoder*))((char*)dec + 0xc);
        if (cb)
            cb(dec);
        void* buf = *(void**)((char*)dec + 0x10);
        if (buf)
            g_pSystem->Free(buf, 0);
        g_pSystem->Free(dec, 0);
        ri->pDecoder = 0;
    }

    FeedDesc* fd = mFeedDesc;
    for (int i = 0; i < 0x14; i++, fd++) {
        if (fd->requestIndex == index) {
            fd->feedState = 0;
            ChunkInfo* ci = fd->pChunkInfo;
            if (ci) {
                re->numBytesFed -= ci->size;
                if (re->streamHandle)
                    re->pRwCoreStream->FUN_011e7c70(ci);
                fd->pChunkInfo = 0;
            }
        }
    }
    if (re->streamHandle) {
        sys->Lock();
        re->pStreamPool->ReleaseStream(re->streamHandle);
        sys->Unlock();
    }
    if (re->pStreamLoopFileName)
        sys->Free(re->pStreamLoopFileName, 0);
    ri->state = 0;
    if (re->expelMode == 1)
        mpVoice->FUN_0112e450();
}

// @ 0x01137bc0  SndPlayer1::FreeFinishedRequests
void SndPlayer1::FreeFinishedRequests()
{
    unsigned char b = mNextRequestToFree;
    while (internal(b)->state == 4) {
        FreeRequest(b);
        unsigned char n = (unsigned char)(b + 1);
        b = (n == mMaxRequests) ? 0 : n;
        mNextRequestToFree = b;
    }
}

// @ 0x01137c30  free all requests (helper, cdecl)
void __cdecl FreeAllRequests(SndPlayer1* self)
{
    for (unsigned int i = 0; i < self->mMaxRequests; i++)
        if (self->internal(i)->state != 0)
            self->FreeRequest(i);
    self->mCurrentRequest = 0;
    self->mNextFreeRequest = 0;
    self->mNextRequestToFree = 0;
}

// @ 0x01137c90  SndPlayer1::Shutdown
void SndPlayer1::Shutdown()
{
    FreeAllRequests(this);
    if (mTimerAdded == 1)
        mpSystem->RemoveTimer(&mTimerHandle);
    if (mpRequestHandle)
        mpSystem->Free(mpRequestHandle, 0);
}

// @ 0x01137de0  SndPlayer1 ring callback: begin a play request
unsigned int __cdecl FUN_01137de0(void* recv)
{
    PlayRec* rec = (PlayRec*)recv;
    SndPlayer1* self = rec->self;
    System* sys = self->mpSystem;

    self->mLastRequestHandleProcessed = rec->f30;

    RequestInternal* ri = self->internal(self->mNextFreeRequest);
    if (ri->state != 0)
        return (unsigned int)rec->recSize;

    RequestExternal* re = &self->mpRequestExternal[self->mNextFreeRequest];

    ri->handle = rec->f30;
    ri->pDecoder = 0;
    ri->streamFileOffset = rec->f08;
    re->streamFileOffset = rec->f10;
    re->expelMode = rec->f2e;
    ri->state = 1;
    re->numSamplesFed = 0;
    re->numBytesFed = 0;
    re->streamHandle = 0;
    re->streamerRequestId = 0;
    re->pStreamLoopFileName = 0;

    self->FUN_011376d0(self->mNextFreeRequest, rec->f24);

    // The original converts the x87 float*double product with `fistp dword`, which rounds to
    // nearest (FPCW 0x027F) and yields 0x80000000 on overflow/NaN. A plain (int) cast uses
    // __ftol2, which truncates and returns the low 32 bits of an int64 (differing in
    // [2^31, 2^63)). `cvtsd2si` (round-nearest per MXCSR, integer-indefinite on overflow)
    // reproduces the original exactly; the product must round to double first, so pass it
    // through _mm_set_sd rather than letting it stay in an extended-precision x87 register.
    int n = _mm_cvtsd_si32(_mm_set_sd((double)ri->f10 * rec->f18));
    if (n <= 0)
        n = 0;
    if (n != 0) {
        if (re->playType == 2)
            n = 0;
        if (ri->f18 >= 0)
            n = 0;
    }
    if (n < ri->samplesFed) {
        self->FUN_011377f0(self->mNextFreeRequest, rec->f28, n);

        unsigned char pt = re->playType;
        if (pt == 1 || pt == 2) {
            StreamPool* pool = FUN_0112df80(rec->f20);
            re->pStreamPool = pool;
            void* h = pool->CreateStream(self->mpVoice->mPriority,
                                         (void*)&FreeAllRequests, self);
            re->streamHandle = h;
            if (!h)
                goto fail;
            re->pRwCoreStream = *(Stream**)((char*)h + 0x14);
            if (ri->f18 >= 0) {
                char* nm = rec->name;
                char* e = nm;
                while (*e)
                    e++;
                unsigned int len = (unsigned int)(e - nm) + 1;
                void* dst = sys->Alloc((int)len, "SndPlayer1 StreamLoopFileName", 0x10, 0);
                re->pStreamLoopFileName = (char*)dst;
                if (!dst)
                    goto fail;
                FUN_011e0744(dst, nm, len);
            }
            if (!(re->playType == 2 && ri->f18 >= 0 && re->gigaSamplesInRam > ri->f18)) {
                __int64 off = (__int64)((double)re->seekChunkOffset + re->streamFileOffset);
                int id = re->pRwCoreStream->QueueFile(
                    (int)rec->name, (int)(unsigned int)off,
                    (int)((unsigned __int64)off >> 32), (void*)&FUN_01137d60, (int)self);
                re->streamerRequestId = id;
            }
            if (ri->f18 >= 0 &&
                !(re->playType == 2 && re->gigaSamplesInRam < ri->samplesFed)) {
                for (int k = 0; k < 2; k++) {
                    __int64 off = (__int64)((double)re->loopStartStreamOffset + re->streamFileOffset);
                    int id = re->pRwCoreStream->QueueFile(
                        (int)rec->name, (int)(unsigned int)off,
                        (int)((unsigned __int64)off >> 32), (void*)&FUN_01137d60, (int)self);
                    if (re->streamerRequestId == 0)
                        re->streamerRequestId = id;
                }
            }
        }
        ri->state = 1;
        unsigned char b = (unsigned char)(self->mNextFreeRequest + 1);
        b = (b == self->mMaxRequests) ? 0 : b;
        self->mNextFreeRequest = b;
        self->mLastRequestHandleSuccessfullyProcessed = rec->f30;
        return (unsigned int)(int)(float)rec->recSize;
    }
fail:
    ri->samplesFed = 0;
    ri->state = 0;
    return (unsigned int)(int)(float)rec->recSize;
}

// @ 0x01138050  SndPlayer1::FeedChunk
char* SndPlayer1::FeedChunk(char* data, int index, char flag2, char flag3)
{
    RequestInternal* ri = internal(index);
    RequestExternal* re = &mpRequestExternal[index];
    unsigned int size  = ((unsigned int)(unsigned char)data[0] << 24) |
                         ((unsigned int)(unsigned char)data[1] << 16) |
                         ((unsigned int)(unsigned char)data[2] << 8) |
                         (unsigned int)(unsigned char)data[3];
    unsigned int size2 = ((unsigned int)(unsigned char)data[4] << 24) |
                         ((unsigned int)(unsigned char)data[5] << 16) |
                         ((unsigned int)(unsigned char)data[6] << 8) |
                         (unsigned int)(unsigned char)data[7];
    unsigned char slot = re->feedSlotLatest;
    FeedDesc* fd = &mFeedDesc[slot];
    fd->feedState = 1;
    fd->chunkSamplesPlayed = 0;
    fd->requestIndex = (unsigned char)index;
    fd->pRwCoreStream = re->pRwCoreStream;
    int a3v, a4v, a5v;
    if (flag3 == 0) {
        a3v = a4v = a5v = 0;
    } else {
        fd->chunkSamplesPlayed = ri->f20;
        a5v = re->seekDataVersion;
        a4v = (int)re->pSeekData;
        a3v = ri->f20;
    }
    char r = ri->pDecoder->FUN_0114c8c0(data + 8, size2, (flag2 == 0) ? 1 : 0,
                                        a3v, (void*)a4v, a5v);
    fd->decoderRequestHandle = (unsigned char)r;
    re->numSamplesFed += (int)size2;
    return data + size;
}

// @ 0x01138130  SndPlayer1::SendCommand
void SndPlayer1::SendCommand(int cmd, void* param)
{
    System* sys = mpSystem;
    CmdParam* pp = (CmdParam*)param;
    CmdPayload payload;
    CmdPayload* pl;
    int edx;

    if (cmd == 0) {
        payload.f00 = pp->f00;
        payload.f08 = pp->f08;
        payload.f10 = 0.0;
        payload.i18 = pp->i10;
        payload.i1c = pp->i14;
        payload.i20 = 0;
        payload.i24 = pp->i18;
        payload.f28 = pp->f1c;
        payload.f2c = pp->f20;
        pl = &payload;
        edx = 0;
        goto shared;
    }
    if (cmd == 5) {
        pl = (CmdPayload*)param;
        edx = 5;
        goto shared;
    }
    if (cmd == 1) {
        int* rec = (int*)(sys->mpCommandBuffer + sys->mCommandIndex);
        sys->mCommandIndex += 8;
        rec[1] = (int)this;
        rec[0] = (int)&FUN_01137cd0;
        return;
    }
    if (cmd == 2) {
        float f = *(float*)param;
        float r = 0.0f;
        if (f < mAttribute[0].f32 ||
            ((f == mAttribute[0].f32 ||
              (f <= mLastRequestHandleProcessed &&
               mLastRequestHandleSuccessfullyProcessed <= f &&
               f != mLastRequestHandleSuccessfullyProcessed)) &&
             mAttribute[2].f64 == 0.0))
            r = g_one;
        *(float*)((char*)param + 4) = r;
        return;
    }
    if (cmd == 3) {
        int i = 0;
        if (mMaxRequests == 0)
            return;
        float f = *(float*)param;
        int extOff = 0;
        int intOff = 0;
        for (;;) {
            RequestInternal* ri = (RequestInternal*)((char*)this + mRequestInternalOffset + intOff);
            if (ri->handle == f) {
                unsigned char st = ri->state;
                if (st != 4 && st != 0) {
                    RequestExternal* re = (RequestExternal*)((char*)mpRequestExternal + extOff);
                    unsigned char pt = re->playType;
                    if (pt == 1 || pt == 2) {
                        *(float*)((char*)param + 4) = (float)re->numBytesFed;
                        *(float*)((char*)param + 8) = 0.0f;
                        if (re->pRwCoreStream == 0) {
                            *(float*)((char*)param + 8) = g_one;
                            return;
                        }
                        int x;
                        if (ri->f18 < 0) {
                            x = re->pRwCoreStream->FUN_011e6c00(re->streamerRequestId);
                        } else if ((float)(unsigned int)i == mAttribute[0].f32) {
                            x = re->pRwCoreStream->FUN_011e6bf0();
                        } else {
                            x = re->pRwCoreStream->FUN_011e6c00(re->streamerRequestId);
                        }
                        *(float*)((char*)param + 4) += (float)x;
                        if (re->pRwCoreStream->FUN_011e6c80(re->streamerRequestId) == 3) {
                            *(float*)((char*)param + 8) = g_one;
                            return;
                        }
                        if (re->pRwCoreStream->FUN_011e6c40() != 2)
                            return;
                        *(float*)((char*)param + 8) = g_one;
                        return;
                    }
                    if (pt == 0) {
                        *(float*)((char*)param + 4) = 0.0f;
                        *(float*)((char*)param + 8) = g_one;
                        return;
                    }
                }
            }
            intOff += 0x30;
            *(float*)((char*)param + 4) = 0.0f;
            *(float*)((char*)param + 8) = 0.0f;
            i++;
            extOff += 0x50;
            if ((unsigned char)i >= mMaxRequests)
                return;
        }
    }
    if (cmd != 4)
        return;
    {
        char* rec = sys->mpCommandBuffer + sys->mCommandIndex;
        sys->mCommandIndex += 0x18;
        ((int*)rec)[1] = (int)this;
        ((int*)rec)[0] = (int)&FUN_01137a30;
        *(double*)(rec + 8) = *(double*)param;
        *(float*)(rec + 0x10) = *(float*)((char*)param + 8);
    }
    return;

shared:
    {
        float* rh = mpRequestHandle;
        *rh = *rh + g_one;
        rh = mpRequestHandle;
        if (*rh > g_reqHandleMax)
            *rh = g_one;
        rh = mpRequestHandle;
        float cur = *rh;
        pl->f2c = cur;
        if (edx == 0)
            *(float*)((char*)param + 0x20) = cur;

        char* name = (char*)pl->i18;
        unsigned int size;
        if (name == 0) {
            size = 1;
        } else {
            char* e = name;
            while (*e)
                e++;
            size = (unsigned int)(e - name) + 1;
        }
        char* ring = sys->mpCommandBuffer + sys->mCommandIndex;
        unsigned int recSize = (size + 0x3b) & ~3u;
        sys->mCommandIndex += recSize;
        PlayRec* rec = (PlayRec*)ring;
        rec->self = this;
        rec->code = (void*)&FUN_01137de0;
        rec->f30 = *mpRequestHandle;
        rec->f08 = pl->f00;
        rec->f10 = pl->f08;
        rec->f18 = pl->f10;
        rec->f24 = pl->i1c;
        rec->f28 = pl->i20;
        rec->f20 = pl->i24;
        rec->f2e = (unsigned char)_mm_cvtss_si32(_mm_load_ss(&pl->f28));
        rec->recSize = (unsigned short)recSize;
        if (size != 1) {
            char* dst = rec->name;
            for (unsigned int k = 0; k < size; k++)
                dst[k] = name[k];
        } else {
            rec->name[0] = 0;
        }
    }
}

// @ 0x011384b0  SndPlayer1::StreamNextChunk
bool SndPlayer1::StreamNextChunk(int index, int a3, int a4)
{
    RequestInternal* ri = internal(index);
    RequestExternal* re = &mpRequestExternal[index];
    if (ri->state == 1 && re->streamerRequestId != 0 &&
        re->pRwCoreStream->FUN_011e6c80(re->streamerRequestId) == 0) {
        ri->samplesFed = 0;
        return 0;
    }
    ChunkInfo* ci = re->pRwCoreStream->GetChunk();
    if (!ci)
        return 0;
    unsigned char fslot = mNextFeedSlotToFill;
    bool fresh = (mFeedDesc[fslot].feedState == 0);
    unsigned char useSlot = (unsigned char)index;
    if (fresh) {
        useSlot = fslot;
        mNextFeedSlotToFill = (unsigned char)((fslot + 1 == 0x14) ? 0 : fslot + 1);
    }
    re->numBytesFed += ci->size;
    if (!fresh)
        return 0;
    re->feedSlotLatest = useSlot;
    mFeedDesc[useSlot].pChunkInfo = ci;
    FeedChunk(ci->pData, index, (char)a3, (char)a4);
    return 1;
}

// @ 0x01138570  SndPlayer1::HandleLoopStart
bool SndPlayer1::HandleLoopStart(int index)
{
    RequestInternal* ri = internal(index);
    RequestExternal* re = &mpRequestExternal[index];
    if (re->playType == 0) {
        re->pLoopStartChunk = re->pNextChunk;
        unsigned char slot = mNextFeedSlotToFill;
        if (mFeedDesc[slot].feedState == 0)
            mNextFeedSlotToFill = (unsigned char)((slot + 1 == 0x14) ? 0 : slot + 1);
        else
            slot = (unsigned char)index;
        re->feedSlotLatest = slot;
        re->pNextChunk = FeedChunk(re->pNextChunk, index, 1, 0);
        return 1;
    }
    if (re->playType == 1 || ri->f18 >= re->gigaSamplesInRam) {
        if (StreamNextChunk(index, 1, 0) == 0)
            return 0;
    } else {
        re->pLoopStartChunk = re->pNextChunk;
        int slot;
        FUN_011379f0(&slot);
        re->feedSlotLatest = (unsigned char)slot;
        re->pNextChunk = FeedChunk(re->pNextChunk, index, 1, 0);
    }
    return 1;
}

// @ 0x01138640  SndPlayer1::HandleSampleEnd
bool SndPlayer1::HandleSampleEnd(int index, unsigned char* out)
{
    RequestInternal* ri = internal(index);
    RequestExternal* re = &mpRequestExternal[index];
    if (ri->f18 < 0) {
        *out = 1;
        return 1;
    }
    *out = 0;
    if (re->playType == 0) {
        if (ri->f18 == 0)
            re->pLoopStartChunk = re->pSampleData;
        unsigned char slot = mNextFeedSlotToFill;
        if (mFeedDesc[slot].feedState == 0)
            mNextFeedSlotToFill = (unsigned char)((slot + 1 == 0x14) ? 0 : slot + 1);
        else
            slot = (unsigned char)index;
        re->feedSlotLatest = slot;
        ri->samplesFed = ri->f18;
        re->pNextChunk = FeedChunk(re->pLoopStartChunk, index, 1, 0);
        return 1;
    }
    if (re->playType == 1) {
        __int64 off = (__int64)((double)re->loopStartStreamOffset + re->streamFileOffset);
        re->pRwCoreStream->QueueFile((int)re->pStreamLoopFileName, (int)(unsigned int)off,
                                     (int)((unsigned __int64)off >> 32),
                                     (void*)&FUN_01137d60, (int)this);
        ri->samplesFed = ri->f18;
        if (StreamNextChunk(index, 1, 0) == 0)
            return 0;
    } else {
        ri->samplesFed = ri->f18;
        if (ri->f18 < re->gigaSamplesInRam) {
            if (ri->f18 == 0)
                re->pLoopStartChunk = re->pSampleData;
            int slot;
            FUN_011379f0(&slot);
            re->feedSlotLatest = (unsigned char)slot;
            re->pNextChunk = FeedChunk(re->pLoopStartChunk, index, 1, 0);
        }
        if (re->gigaSamplesInRam < ri->samplesFed) {
            __int64 off = (__int64)((double)re->loopStartStreamOffset + re->streamFileOffset);
            re->pRwCoreStream->QueueFile((int)re->pStreamLoopFileName, (int)(unsigned int)off,
                                         (int)((unsigned __int64)off >> 32),
                                         (void*)&FUN_01137d60, (int)this);
            if (re->gigaSamplesInRam <= ri->f18) {
                if (StreamNextChunk(index, 1, 0) == 0)
                    return 0;
            }
        }
    }
    return 1;
}

// @ 0x011387b0  SndPlayer1::StartRequest
bool SndPlayer1::StartRequest(int index)
{
    RequestInternal* ri = internal(index);
    RequestExternal* re = &mpRequestExternal[index];
    System* sys = mpSystem;

    sys->Lock();
    DecoderRegistry* dr = sys->GetDecoderRegistry();
    int codecObj = dr->FUN_01133ed0(g_codecTable[re->codec]);
    Decoder* dec = dr->DecoderFactory(codecObj, ri->codec, 0x14, sys);
    ri->pDecoder = dec;
    if (!dec) {
        sys->Unlock();
        return 0;
    }
    ri->numChannels = dec->mNumChannels;
    bool flag = (ri->f24 != 0 || ri->f20 != 0 || re->playerSkip != 0);

    unsigned char pt = re->playType;
    if (pt == 0 || pt == 2) {
        unsigned char slot = mNextFeedSlotToFill;
        unsigned char useSlot = (unsigned char)flag;
        if (mFeedDesc[slot].feedState == 0) {
            useSlot = slot;
            mNextFeedSlotToFill = (unsigned char)((slot + 1 == 0x14) ? 0 : slot + 1);
        }
        re->feedSlotLatest = useSlot;
        re->pNextChunk = FeedChunk(re->pSampleData + re->seekChunkOffset, index,
                                   (char)re->seekChunkIsNewFeed, (char)flag);
    } else {
        if (StreamNextChunk(index, (int)re->seekChunkIsNewFeed, (int)flag) == 0) {
            if (ri->pDecoder) {
                ri->pDecoder->FUN_01133f40();
                ri->pDecoder = 0;
            }
            sys->Unlock();
            return 0;
        }
    }
    sys->Unlock();
    return 1;
}

} } } // namespace rw::audio::core

// @ 0x01137d60  stream-header callback: big-endian length, with optional in-place byte swap
extern "C" int FUN_01137d60(char* data, unsigned int size, int, int, int, int, unsigned int* out)
{
    if (size < 8)
        return 0;
    union U { unsigned int u; unsigned char b[4]; } u;
    u.b[0] = (unsigned char)data[3];
    u.b[1] = (unsigned char)data[2];
    u.b[2] = (unsigned char)data[1];
    u.b[3] = (unsigned char)data[0];
    unsigned int v = u.u;
    unsigned int sig = v >> 31;
    v &= 0x7fffffff;
    if (v > size)
        return 0;
    *out = v;
    if (sig == 1) {
        data[0] = (char)(v >> 24);
        data[1] = (char)(v >> 16);
        data[2] = (char)(v >> 8);
        data[3] = (char)v;
        return 2;
    }
    return 1;
}

// @ 0x01137cd0  ring callback: reset all requests / counters
extern "C" int FUN_01137cd0(void* recv)
{
    using namespace rw::audio::core;
    SndPlayer1* self = *(SndPlayer1**)((char*)recv + 4);
    for (unsigned int i = 0; i < self->mMaxRequests; i++)
        if (self->internal(i)->state != 0)
            self->FreeRequest(i);
    self->mCurrentRequest = 0;
    self->mNextFreeRequest = 0;
    self->mNextRequestToFree = 0;
    self->mCurrentRequestSamplesPlayed = 0;
    self->mCurrentRequestNumSamples = 0;
    self->mNextFeedSlotToFill = 0;
    self->mNextFeedSlotToFree = 0;
    self->mNumDeclickSamples = 0x10;
    return 8;
}
