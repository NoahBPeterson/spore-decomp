// Slice s00fc9310: rw::movie (RenderWare "rpmovie") -- the movie decoder / renderer
// (rw::movie::MovieDecoder) and the AVI movie encoder (rw::movie::MovieEncoder_Avi).
// MSVC 2008 SP1 x86 (VS2008 SP1 cl 15.00).
#include "types.h"
#include <intrin.h>
#pragma intrinsic(__rdtsc)

namespace rw { namespace core { namespace timer {
class Stopwatch
{ public:
    void* vftable;        // +0x00
    void* mCallback;      // +0x04
    int32_t mUnits;       // +0x08
    int32_t pad_0c;       // +0x0c
    int32_t mStartLo;     // +0x10
    int32_t mStartHi;     // +0x14
    int32_t mElapsedLo;   // +0x18
    int32_t mElapsedHi;   // +0x1c
    float mScale;         // +0x20
    Stopwatch* Ctor(int units, int a);   // 0x011e82d0
    void Stop();                         // 0x011e83a0
};
}}}
using rw::core::timer::Stopwatch;
unsigned long long GetStopwatchCycle();   // 0x011e8080

// ---------------------------------------------------------------------------
// EAThread pieces used by the decoder thread startup / teardown.
// ---------------------------------------------------------------------------
namespace EA { namespace Thread {
struct ThreadParameters
{
    int32_t mFields[5];        // +0x00
    const char* mName;         // +0x14
    void Ctor();               // 0x00922900
};
int  FUN_00922920();                               // 0x00922920
class Thread
{ public:
    int  GetStatus(int* pStatus) const;                       // 0x00922a10
    void Begin(void* fn, void* arg, ThreadParameters* p, int a);   // 0x00922f30
    void SetPriority(int a);                                  // 0x00922c40
};
void ThreadRelease(Thread* t);                     // 0x00923310
class Semaphore { public: int Post(int count); };  // 0x00922740
void DestructSemaphore(Semaphore* s);              // 0x00922800
void ThreadSleep(const int* pTime);                // 0x00921df0
}}

using EA::Thread::Thread;
using EA::Thread::Semaphore;
using EA::Thread::ThreadParameters;
using EA::Thread::ThreadSleep;

// 0x01491ad4: how long the decoder holds off between status polls.
extern int32_t g_videoDecodeThreadPause;   // 0x01491ad4
// 0x00fc9220: decoder thread entry point.
extern void VideoDecodeThreadFn();         // 0x00fc9220

namespace rw {
namespace movie {

struct ICoreAllocator
{
    virtual void  v0();                                                          // +0x00
    virtual void* Alloc(unsigned int size, const char* name, int a, int b, int c);   // +0x04
    virtual void* AllocBlock(unsigned int size, const char* name, int flag);      // +0x08
    virtual void  Free(void* p, int a);                                          // +0x0c
};

// 0x00fc8580 / 0x00fc8550 / 0x00fc8500: BufferedWriter helpers (PDB: BufferedWriter, size 0x20).
class BufferedWriter
{ public:
    void* mEncodedDataCallback;      // +0x00
    void* mEncodedDataCallbackData;  // +0x04
    uint8_t* mBuffer;                // +0x08
    int32_t mBufferSize;             // +0x0c
    int32_t mBufferPos;              // +0x10
    int32_t mBufferRemotePos;        // +0x14
    int32_t mRemoteSize;             // +0x18
    int32_t mRemotePos;              // +0x1c

    void Write32(uint32_t v);        // 0x00fc8580 (ret 4)
    void Write16(uint16_t v);        // 0x00fc8550 (ret 4)
    void WriteFill(int v, int n);    // 0x00fc8500 (ret 8)
    void Init();                     // 0x00fc8350
};

// Encoder interfaces: only the vtable slots used here are named; the rest are placeholders.
class IEncoder
{ public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();   // +0x00..+0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();   // +0x10..+0x1c
};

class IVideoEncoder : public IEncoder
{ public:
    virtual void v8(); virtual void v9();                                  // +0x20, +0x24
    virtual uint32_t GetWidth();        // +0x28
    virtual void v11();                 // +0x2c
    virtual uint32_t GetHeight();       // +0x30
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual uint32_t GetQuality();      // +0x48
    virtual uint32_t GetPlanes();       // +0x4c
    virtual uint32_t GetBitCount();     // +0x50
    virtual uint32_t GetBufferSize();   // +0x54
    virtual void AddFrame(void* frame); // +0x58
    virtual void v22();                 // +0x5c
};

class IAudioEncoder : public IEncoder
{ public:
    virtual void v8(); virtual void v9();                 // +0x20, +0x24
    virtual uint32_t GetSlot28();       // +0x28
    virtual void v11();                 // +0x2c
    virtual uint32_t GetSlot30();       // +0x30
    virtual uint32_t GetSlot34();       // +0x34
    virtual uint32_t GetSlot38();       // +0x38
    virtual uint32_t GetSlot3C();       // +0x3c
    virtual uint32_t GetSlot40();       // +0x40
    virtual uint32_t GetSlot44();       // +0x44
    virtual void AddSamples(void* samples);   // +0x48
};

struct AviIndexEntry
{
    uint32_t dwChunkId;    // +0x00
    uint32_t dwFlags;      // +0x04
    uint32_t dwOffset;     // +0x08
    uint32_t dwSize;       // +0x0c
};

struct AviIndexBlock
{
    AviIndexEntry* data;   // +0x00
    uint32_t count;        // +0x04
    AviIndexBlock* next;   // +0x08
};

// Audio payload handed to MovieEncoder_Avi::AddAudioSamples.
struct AudioSamples
{
    void*    mBuffer;      // +0x00
    uint32_t mSampleRate;  // +0x04
    uint32_t mPad08;       // +0x08
    uint32_t mSize;        // +0x0c
};

class MovieEncoder_Avi
{ public:
    void* vftable;                       // +0x00
    ICoreAllocator* mAllocator;          // +0x04
    void* mEncodingErrorCallback;        // +0x08
    void* mEncodingErrorCallbackData;    // +0x0c
    uint32_t mBufferSize;                // +0x10
    BufferedWriter mBufferedWriter;      // +0x14
    IAudioEncoder* mAudioEncoder;        // +0x34
    IVideoEncoder* mVideoEncoder;        // +0x38
    uint32_t mMicrosecondsPerFrame;      // +0x3c
    uint32_t mMicrosecondsAudioBuffered; // +0x40
    uint32_t mTotalFrames;               // +0x44
    uint32_t mTotalAudioSamples;         // +0x48
    AviIndexBlock mFirstIndexBlock;      // +0x4c
    AviIndexBlock* mActiveAVIIndexBlock; // +0x58
    uint32_t mNumAVIIndexEntries;        // +0x5c
    uint32_t mNumAVIIndexEntriesPerBlock; // +0x60
    uint32_t mRiffChunkSize;             // +0x64
    uint32_t mNextChunkOffset;           // +0x68
    Stopwatch* mStopwatch;               // +0x6c
    float mTotalElapsedTime;             // +0x70

    uint32_t NextDataExpected();                    // 0x00fc9950
    void AddAudioSamples(AudioSamples* samples);     // 0x00fc9970
    void AddVideoFrame(void* frame);                 // 0x00fc9a10
    uint32_t WriteAVIHeaders();                      // 0x00fc9a60
    void BeginEncoding();                            // 0x00fca0e0
    void AddAVIIndexEntry(const AviIndexEntry* e);   // 0x00fca160
    void FreeAVIIndexEntries();                      // 0x00fca250
    MovieEncoder_Avi* Ctor(uint32_t bufferSize);     // 0x00fca2c0
};

// ---------------------------------------------------------------------------
// rw::movie renderable pool.  The object MovieDecoder points at (+0x34) is the
// renderable manager; the list accessors below are the ones this slice calls.
// ---------------------------------------------------------------------------
class VideoRenderable;

class VideoRenderableManager
{ public:
    void* mAllocator;            // +0x00
    void* mEmptyList;            // +0x04
    void* mFilledList;           // +0x08
    void* mSentToDecoderList;    // +0x0c
    void* mSentToRendererList;   // +0x10
    uint32_t mPad14;             // +0x14
    uint8_t mListMutex[0x30];    // +0x18
    void* mComparator;           // +0x48

    void ShutdownAll();                                  // 0x00fce010
    void AddToEmptyList(void* renderable);               // 0x00fce0a0
    uint32_t GetEmptyListSize();                         // 0x00fce0e0
    void AddToFilledList(void* renderable);              // 0x00fce110
    VideoRenderable* PeekFilledListIndex(uint32_t i);    // 0x00fce150
    uint32_t GetFilledListSize();                        // 0x00fce1b0
    void AddToRendererList(void* renderable);            // 0x00fce1e0
    uint32_t GetRendererListSize();                      // 0x00fce220
    void AddToDecoderList(void* renderable);             // 0x00fce250
    uint32_t GetDecoderListSize();                       // 0x00fce290
    VideoRenderable* PopFromEmptyList();                 // 0x00fce2c0
    VideoRenderable* PeekFilledList();                   // 0x00fce320
    VideoRenderable* PopFromFilledList();                // 0x00fce380
    VideoRenderable* PopFromRendererList();              // 0x00fce3e0
    VideoRenderable* GetFromDecoderList(uint32_t i);     // 0x00fce440
    VideoRenderable* RemoveFromDecoderList(uint32_t i);  // 0x00fce4c0
};

// A decoded video frame handed to the renderer.
class VideoRenderable
{ public:
    uint8_t mPad00[0x34];      // +0x00
    int32_t mFrameNumber;      // +0x34
    uint32_t mPad38;           // +0x38
    int32_t mState;            // +0x3c
    uint8_t mDecodedFlag;      // +0x40
    uint8_t mPad41[0x0f];      // +0x41
    uint8_t mFilledFlag;       // +0x50
    uint8_t mPad51[0x03];      // +0x51

    VideoRenderable* Ctor();   // 0x00fcdec0
    void OnDecoded();          // 0x00fcdf30
    void Release();            // 0x00fcdf10
    void Reset();              // 0x00fcdf20
};

class IVideoRenderableOperations
{ public:
    virtual void v0();                                                   // +0x00
    virtual void v1(void* r, void* a, void* b, int c, int d);            // +0x04
    virtual void v2(void* allocator);                                    // +0x08
    virtual void v3();                                                   // +0x0c
    virtual void v4(void* r);                                            // +0x10
    virtual void v5();                                                   // +0x14
    virtual void v6(void* r);                                            // +0x18
};

class IVideoDecoder
{ public:
    virtual void v0();                                  // +0x00
    virtual bool Init(void* allocator, void* a, void* b); // +0x04
    virtual void Shutdown();                            // +0x08
    virtual int  GetFrameType();                        // +0x0c
    virtual void SetStreamTap(void* handle);            // +0x10
};

class IAudioDecoder
{ public:
    virtual void v0();                                              // +0x00
    virtual bool Init(void* allocator, void* a, void* b, void* c);  // +0x04
    virtual void Shutdown();                                        // +0x08
    virtual void SetStreamTap(void* handle, int requestId);         // +0x0c
};

class ISubtitleDecoder
{ public:
    virtual void v0();                                      // +0x00
    virtual bool Init(void* allocator);                     // +0x04
    virtual void v2();                                      // +0x08
    virtual void SetStreamTap(void* handle);                // +0x0c
    virtual void SetCurrentTime(int time, void* a);         // +0x10
};

// Movie playback state machine.
class MovieDecoder
{ public:
    ICoreAllocator* mAllocator;                    // +0x00
    IVideoDecoder* mVideoDecoder;                  // +0x04
    IAudioDecoder* mAudioDecoder;                  // +0x08
    ISubtitleDecoder* mSubtitleDecoder;            // +0x0c
    IVideoRenderableOperations* mVideoRenderableOperations;   // +0x10
    void* mVideoStreamTapHandle;                   // +0x14
    void* mAudioStreamTapHandle;                   // +0x18
    int32_t mAudioStreamRequestId;                 // +0x1c
    void* mSubtitleStreamTapHandle;                // +0x20
    Thread* mVideoDecodeThread;                    // +0x24
    void* mVideoThreadData;                        // +0x28
    Semaphore* mEmptyVideoRenderablesSemaphore;     // +0x2c
    void* mField30;                                // +0x30
    VideoRenderableManager* mRenderableQueue;      // +0x34
    uint32_t mNumVideoRenderables;                 // +0x38
    uint32_t mPad3c;                               // +0x3c
    uint32_t mTotalFrames;                         // +0x40
    uint32_t mPad44;                               // +0x44
    uint32_t mState;                               // +0x48

    void PrepareDecoder(void* a1, void* a2, uint32_t a3, void* a4, void* a5,
                        void* a6, uint32_t a7, uint32_t a8, uint32_t a9);   // 0x00fc9310
    void UpdateRenderables(int frame, int* outFrame, void* a3);             // 0x00fc94f0
    void Teardown();                                                       // 0x00fc96d0
    void Release();                                                        // 0x00fc97a0
};

void DecodeVideoFrame(VideoRenderable* r, MovieDecoder* dec);              // 0x00fc9670

} // namespace movie
} // namespace rw

// AVIUtils::FCC_RIFF (rw::movie::AVIUtils): fourcc table "RIFF","AVI ","LIST","hdrl","avih","strl","strh",
// "strf","JUNK","movi","mjpg","MJPG","vids","auds","txts","idx1" (read as dwords out of one string).
extern const uint32_t FCC_RIFF[16]; // 0x015b179c
extern uint32_t g_aviFlagA;   // 0x01491800
extern uint32_t g_aviFlagB;   // 0x014917f0
extern uint32_t g_aviFlagC;   // 0x014917f8 (audio present)
extern uint16_t g_waveFormatTag; // 0x01491838

using namespace rw::movie;

struct AVIMainHeader
{
    uint32_t dwMicroSecPerFrame, dwMaxBytesPerSec, dwPaddingGranularity, dwFlags, dwTotalFrames,
             dwInitialFrames, dwStreams, dwSuggestedBufferSize, dwWidth, dwHeight, dwReserved[4];
};
struct AVIStreamHeader
{
    uint32_t fccType, fccHandler, dwFlags;
    uint16_t wPriority, wLanguage;
    uint32_t dwInitialFrames, dwScale, dwRate, dwStart, dwLength, dwSuggestedBufferSize, dwQuality, dwSampleSize;
    uint16_t rcLeft, rcTop, rcRight, rcBottom;
};
struct BitmapInfoHeader
{
    uint32_t biSize, biWidth, biHeight;
    uint16_t biPlanes, biBitCount;
    uint32_t biCompression, biSizeImage, biXPelsPerMeter, biYPelsPerMeter, biClrUsed, biClrImportant;
};
struct WaveFormat
{
    uint16_t wFormatTag, nChannels;
    uint32_t nSamplesPerSec, nAvgBytesPerSec;
    uint16_t nBlockAlign, wBitsPerSample;
};

// ===========================================================================
// MovieDecoder
// ===========================================================================

// @ 0x00fc9310
void MovieDecoder::PrepareDecoder(void* a1, void* a2, uint32_t a3, void* a4, void* a5,
                                  void* a6, uint32_t a7, uint32_t a8, uint32_t a9)
{
    if (mState != 0)
        return;

    if (mVideoRenderableOperations != 0)
        mVideoRenderableOperations->v2(mAllocator);

    if (mVideoDecoder != 0) {
        mVideoDecoder->Init(mAllocator, a1, a2);
        mTotalFrames = a3;
        mVideoDecoder->SetStreamTap(mVideoStreamTapHandle);
        int frameType = mVideoDecoder->GetFrameType();
        if (frameType == 1) {
            a1 = (uint8_t*)a1 + 0x60;
            a2 = (uint8_t*)a2 + 0x60;
        }
        if (a8 > 0) {
            for (uint32_t n = a8; n > 0; --n) {
                VideoRenderable* renderable =
                    (VideoRenderable*)mAllocator->Alloc(0x54, "VideoRenderable object", 1, 4, 0);
                renderable = renderable ? renderable->Ctor() : 0;
                mVideoRenderableOperations->v1(renderable, a1, a2, frameType, a9);
                mRenderableQueue->AddToEmptyList(renderable);
                ++mNumVideoRenderables;
                mEmptyVideoRenderablesSemaphore->Post(1);
            }
        }
    }

    if (mAudioDecoder != 0) {
        mAudioDecoder->Init(mAllocator, a4, a5, a6);
        mAudioDecoder->SetStreamTap(mAudioStreamTapHandle, mAudioStreamRequestId);
    }
    if (mSubtitleDecoder != 0) {
        mSubtitleDecoder->Init(mAllocator);
        mSubtitleDecoder->SetStreamTap(mSubtitleStreamTapHandle);
    }

    mState = 1;

    if (mVideoDecoder != 0) {
        ThreadParameters params;
        params.Ctor();
        params.mName = "VideoDecodeThread";
        mVideoDecodeThread->Begin((void*)&VideoDecodeThreadFn, this, &params,
                                  EA::Thread::FUN_00922920());
        mVideoDecodeThread->SetPriority(a7);

        bool anyDecoded = false;
        while (!anyDecoded) {
            ThreadSleep(&g_videoDecodeThreadPause);
            if (mRenderableQueue->GetEmptyListSize() == 0) {
                uint32_t filled = mRenderableQueue->GetFilledListSize();
                uint32_t used = mRenderableQueue->GetDecoderListSize();
                if (filled > 0)
                    return;
                for (uint32_t i = 0; i < used; ++i) {
                    uint8_t decodedFlag =
                        mRenderableQueue->GetFromDecoderList(i)->mDecodedFlag;
                    if (decodedFlag == 1)
                        anyDecoded = decodedFlag;
                }
            }
        }
    }
}

// @ 0x00fc94f0
void MovieDecoder::UpdateRenderables(int frame, int* outFrame, void* a3)
{
    if ((uint32_t)(mState - 1) > 1)
        return;

    VideoRenderable* renderable;
    if (mVideoDecoder == 0) {
        *outFrame = 0;
        renderable = 0;
    } else {
        uint32_t used = mRenderableQueue->GetDecoderListSize();
        uint32_t i = 0;
        while (i < used) {
            renderable = mRenderableQueue->GetFromDecoderList(i);
            if (renderable->mDecodedFlag != 0) {
                renderable = mRenderableQueue->RemoveFromDecoderList(i);
                mVideoRenderableOperations->v6(renderable);
                mRenderableQueue->AddToFilledList(renderable);
                --used;
            } else {
                ++i;
            }
        }

        uint32_t filled = mRenderableQueue->GetFilledListSize();
        uint32_t count = 0;
        renderable = 0;
        int prev = 0;
        bool havePrev = false;
        for (uint32_t k = filled; k > 0; --k) {
            renderable = mRenderableQueue->PeekFilledListIndex(k - 1);
            if (havePrev)
                renderable->mFrameNumber = prev;
            if (renderable->mFilledFlag != 0) {
                prev = renderable->mFrameNumber;
                havePrev = true;
            } else {
                havePrev = false;
            }
        }

        if (filled > 0) {
            for (;;) {
                renderable = mRenderableQueue->PeekFilledList();
                if (renderable->mFrameNumber >= frame)
                    break;
                ++count;
                if (count >= filled)
                    break;
                renderable = mRenderableQueue->PopFromFilledList();
                if (renderable->mState == 0) {
                    mRenderableQueue->AddToEmptyList(renderable);
                    mEmptyVideoRenderablesSemaphore->Post(1);
                } else {
                    mRenderableQueue->AddToFilledList(renderable);
                }
            }
            renderable->Reset();
        }
        *outFrame = (int)renderable;
    }

    if (mSubtitleDecoder != 0)
        mSubtitleDecoder->SetCurrentTime(renderable->mFrameNumber, a3);
}

// @ 0x00fc9670
void DecodeVideoFrame(VideoRenderable* r, MovieDecoder* dec)
{
    r->OnDecoded();
    if (r->mState > 0)
        return;

    uint32_t n = dec->mRenderableQueue->GetFilledListSize();
    for (uint32_t i = 0; i < n; ++i) {
        VideoRenderable* x = dec->mRenderableQueue->PopFromRendererList();
        if (x->mState > 0) {
            dec->mRenderableQueue->AddToFilledList(x);
        } else {
            dec->mRenderableQueue->AddToEmptyList(x);
            dec->mEmptyVideoRenderablesSemaphore->Post(1);
            break;
        }
    }
}

// @ 0x00fc96d0
void MovieDecoder::Teardown()
{
    bool posted = false;
    mState = 4;
    int status = mVideoDecodeThread->GetStatus(0);
    while (status == 1) {
        if (!posted) {
            if (mRenderableQueue->GetEmptyListSize() != 0) {
                VideoRenderable* r = mRenderableQueue->PopFromFilledList();
                mRenderableQueue->AddToEmptyList(r);
                mEmptyVideoRenderablesSemaphore->Post(1);
                posted = true;
            } else if (mRenderableQueue->GetFilledListSize() != 0) {
                VideoRenderable* r = mRenderableQueue->PopFromRendererList();
                mRenderableQueue->AddToEmptyList(r);
                mEmptyVideoRenderablesSemaphore->Post(1);
                posted = true;
            } else if (mRenderableQueue->GetDecoderListSize() != 0) {
                VideoRenderable* r = mRenderableQueue->RemoveFromDecoderList(0);
                mRenderableQueue->AddToEmptyList(r);
                mEmptyVideoRenderablesSemaphore->Post(1);
                posted = true;
            }
        }
        int pause = 0;
        ThreadSleep(&pause);
        status = mVideoDecodeThread->GetStatus(0);
    }

    if (mVideoDecoder != 0)
        mVideoDecoder->Shutdown();
    if (mAudioDecoder != 0)
        mAudioDecoder->Shutdown();
    if (mVideoRenderableOperations != 0)
        mVideoRenderableOperations->v3();
}

// @ 0x00fc97a0
void MovieDecoder::Release()
{
    ThreadRelease(mVideoDecodeThread);
    mAllocator->Free(mVideoThreadData, 0);
    EA::Thread::DestructSemaphore(mEmptyVideoRenderablesSemaphore);
    mAllocator->Free(mField30, 0);

    while (mRenderableQueue->GetEmptyListSize() > 0) {
        VideoRenderable* r = mRenderableQueue->PopFromEmptyList();
        mVideoRenderableOperations->v4(r);
        r->Release();
        mAllocator->Free(r, 0);
    }
    while (mRenderableQueue->GetFilledListSize() > 0) {
        VideoRenderable* r = mRenderableQueue->PopFromFilledList();
        mVideoRenderableOperations->v4(r);
        r->Release();
        mAllocator->Free(r, 0);
    }
    while (mRenderableQueue->GetDecoderListSize() > 0) {
        VideoRenderable* r = mRenderableQueue->RemoveFromDecoderList(0);
        mVideoRenderableOperations->v4(r);
        r->Release();
        mAllocator->Free(r, 0);
    }
    while (mRenderableQueue->GetRendererListSize() > 0) {
        VideoRenderable* r = mRenderableQueue->PopFromRendererList();
        mVideoRenderableOperations->v4(r);
        r->Release();
        mAllocator->Free(r, 0);
    }
    if (mRenderableQueue != 0) {
        mRenderableQueue->ShutdownAll();
        mAllocator->Free(mRenderableQueue, 0);
        mRenderableQueue = 0;
    }
}

// ===========================================================================
// MovieEncoder_Avi
// ===========================================================================

// @ 0x00fc9950
uint32_t MovieEncoder_Avi::NextDataExpected()
{
    uint32_t type = 1;
    if (mAudioEncoder != 0 && mMicrosecondsAudioBuffered < mMicrosecondsPerFrame)
        return type;
    return 2;
}

// @ 0x00fc9970
void MovieEncoder_Avi::AddAudioSamples(AudioSamples* samples)
{
    Stopwatch* sw = mStopwatch;
    unsigned long long now;
    if (sw->mUnits == 1)
        now = __rdtsc();
    else
        now = GetStopwatchCycle();
    sw->mStartHi = (int)(now >> 32);
    sw->mStartLo = (int)now;

    if (mAudioEncoder != 0) {
        mAudioEncoder->AddSamples(samples);
        mTotalAudioSamples += samples->mSize;
        mMicrosecondsAudioBuffered +=
            (unsigned int)((float)samples->mSize / (float)samples->mSampleRate * 1000000.0f);
    }
    mStopwatch->Stop();
}

// @ 0x00fc9a10
void MovieEncoder_Avi::AddVideoFrame(void* frame)
{
    Stopwatch* sw = mStopwatch;
    unsigned long long now;
    if (sw->mUnits == 1)
        now = __rdtsc();
    else
        now = GetStopwatchCycle();
    sw->mStartHi = (int)(now >> 32);
    sw->mStartLo = (int)now;

    if (mVideoEncoder != 0) {
        mVideoEncoder->AddFrame(frame);
        ++mTotalFrames;
        mMicrosecondsAudioBuffered -= mMicrosecondsPerFrame;
    }
    mStopwatch->Stop();
}

// @ 0x00fc9a60
uint32_t MovieEncoder_Avi::WriteAVIHeaders()
{
    BufferedWriter* w = &mBufferedWriter;

    w->Write32(FCC_RIFF[0]);
    w->Write32(mRiffChunkSize);
    w->Write32(FCC_RIFF[1]);
    w->Write32(FCC_RIFF[2]);
    uint32_t hdrlSize = 0xc0;
    if (mAudioEncoder)
        hdrlSize = 0x124;
    w->Write32(hdrlSize);
    w->Write32(FCC_RIFF[3]);
    w->Write32(FCC_RIFF[4]);
    w->Write32(0x38);

    {
        AVIMainHeader mh;
        mh.dwMicroSecPerFrame = mMicrosecondsPerFrame;
        mh.dwFlags = g_aviFlagA | g_aviFlagB;
        if (mAudioEncoder)
            mh.dwFlags |= g_aviFlagC;
        mh.dwTotalFrames = mTotalFrames;
        mh.dwStreams = (mAudioEncoder != 0) + 1;
        mh.dwSuggestedBufferSize = mVideoEncoder->GetBufferSize();
        if (mAudioEncoder)
        {
            uint32_t vb = mVideoEncoder->GetBufferSize();
            uint32_t ab = mAudioEncoder->GetSlot44();
            if (ab > vb)
                mh.dwSuggestedBufferSize = mAudioEncoder->GetSlot44();
        }
        mh.dwWidth = mVideoEncoder->GetWidth();
        mh.dwHeight = mVideoEncoder->GetHeight();
        w->Write32(mh.dwMicroSecPerFrame);
        w->Write32(0);
        w->Write32(0);
        w->Write32(mh.dwFlags);
        w->Write32(mh.dwTotalFrames);
        w->Write32(0);
        w->Write32(mh.dwStreams);
        w->Write32(mh.dwSuggestedBufferSize);
        w->Write32(mh.dwWidth);
        w->Write32(mh.dwHeight);
        w->Write32(0);
        w->Write32(0);
        w->Write32(0);
        w->Write32(0);
    }

    // video stream: LIST strl / strh
    w->Write32(FCC_RIFF[2]);
    w->Write32(0x74);
    w->Write32(FCC_RIFF[5]);
    w->Write32(FCC_RIFF[6]);
    w->Write32(0x38);
    {
        AVIStreamHeader sh;
        sh.fccType = FCC_RIFF[12];
        sh.fccHandler = FCC_RIFF[10];
        sh.dwScale = mMicrosecondsPerFrame;
        sh.dwLength = mTotalFrames;
        sh.dwSuggestedBufferSize = mVideoEncoder->GetBufferSize();
        sh.dwQuality = mVideoEncoder->GetQuality();
        sh.rcRight = (uint16_t)mVideoEncoder->GetWidth();
        sh.rcBottom = (uint16_t)mVideoEncoder->GetHeight();
        w->Write32(sh.fccType);
        w->Write32(sh.fccHandler);
        w->Write32(0);
        w->Write16(0);
        w->Write16(0);
        w->Write32(0);
        w->Write32(sh.dwScale);
        w->Write32(1000000);
        w->Write32(0);
        w->Write32(sh.dwLength);
        w->Write32(sh.dwSuggestedBufferSize);
        w->Write32(sh.dwQuality);
        w->Write32(0);
        w->Write16(0);
        w->Write16(0);
        w->Write16(sh.rcRight);
        w->Write16(sh.rcBottom);
    }

    // video strf: BITMAPINFOHEADER
    w->Write32(FCC_RIFF[7]);
    w->Write32(0x28);
    {
        BitmapInfoHeader bi;
        bi.biWidth = mVideoEncoder->GetWidth();
        bi.biHeight = mVideoEncoder->GetHeight();
        bi.biPlanes = (uint16_t)mVideoEncoder->GetPlanes();
        bi.biBitCount = (uint16_t)mVideoEncoder->GetBitCount();
        bi.biCompression = FCC_RIFF[11];
        IVideoEncoder* v = mVideoEncoder;
        uint32_t bh = v->GetBitCount() * v->GetHeight();
        bi.biSizeImage = (mVideoEncoder->GetWidth() * bh) >> 3;
        w->Write32(0x28);
        w->Write32(bi.biWidth);
        w->Write32(bi.biHeight);
        w->Write16(bi.biPlanes);
        w->Write16(bi.biBitCount);
        w->Write32(bi.biCompression);
        w->Write32(bi.biSizeImage);
        w->Write32(0);
        w->Write32(0);
        w->Write32(0);
        w->Write32(0);
    }

    if (mAudioEncoder)
    {
        // audio stream: LIST strl / strh
        w->Write32(FCC_RIFF[2]);
        w->Write32(0x5c);
        w->Write32(FCC_RIFF[5]);
        w->Write32(FCC_RIFF[6]);
        w->Write32(0x38);
        {
            AVIStreamHeader sh;
            sh.fccType = FCC_RIFF[13];
            sh.dwScale = mAudioEncoder->GetSlot40();
            IAudioEncoder* a = mAudioEncoder;
            sh.dwRate = a->GetSlot40() * a->GetSlot28();
            sh.dwLength = mTotalAudioSamples;
            sh.dwSuggestedBufferSize = mAudioEncoder->GetSlot44();
            sh.dwQuality = mAudioEncoder->GetSlot38();
            sh.dwSampleSize = mAudioEncoder->GetSlot40();
            w->Write32(sh.fccType);
            w->Write32(0);
            w->Write32(0);
            w->Write16(0);
            w->Write16(0);
            w->Write32(0);
            w->Write32(sh.dwScale);
            w->Write32(sh.dwRate);
            w->Write32(0);
            w->Write32(sh.dwLength);
            w->Write32(sh.dwSuggestedBufferSize);
            w->Write32(sh.dwQuality);
            w->Write32(sh.dwSampleSize);
            w->Write16(0);
            w->Write16(0);
            w->Write16(0);
            w->Write16(0);
        }

        // audio strf: WAVEFORMAT
        w->Write32(FCC_RIFF[7]);
        w->Write32(0x10);
        {
            WaveFormat wf;
            wf.wFormatTag = g_waveFormatTag;
            wf.nChannels = (uint16_t)mAudioEncoder->GetSlot30();
            wf.nSamplesPerSec = mAudioEncoder->GetSlot28();
            wf.nAvgBytesPerSec = mAudioEncoder->GetSlot34() >> 3;
            wf.nBlockAlign = (uint16_t)mAudioEncoder->GetSlot40();
            wf.wBitsPerSample = (uint16_t)mAudioEncoder->GetSlot3C();
            w->Write16(wf.wFormatTag);
            w->Write16(wf.nChannels);
            w->Write32(wf.nSamplesPerSec);
            w->Write32(wf.nAvgBytesPerSec);
            w->Write16(wf.nBlockAlign);
            w->Write16(wf.wBitsPerSample);
        }
    }

    // JUNK pad up to the next 2048-byte boundary, then the movi LIST header.
    w->Write32(FCC_RIFF[8]);
    uint32_t used = hdrlSize + 0x28;
    uint32_t blocks = (used >> 11) + ((used & 0x7ff) == 0);
    uint32_t aligned = (blocks == 0) << 11;
    uint32_t pad = aligned - used;
    w->Write32(pad);
    w->WriteFill(0, pad);
    w->Write32(FCC_RIFF[2]);
    w->Write32(mNextChunkOffset);
    w->Write32(FCC_RIFF[9]);
    return aligned;
}

// @ 0x00fca0e0
void MovieEncoder_Avi::BeginEncoding()
{
    Stopwatch* sw = mStopwatch;
    sw->mStartLo = 0;
    sw->mStartHi = 0;
    sw->mElapsedLo = 0;
    sw->mElapsedHi = 0;

    Stopwatch* clock = mStopwatch;
    unsigned long long now;
    if (clock->mUnits == 1)
        now = __rdtsc();
    else
        now = GetStopwatchCycle();
    clock->mStartHi = (int)(now >> 32);
    clock->mStartLo = (int)now;

    if (mVideoEncoder != 0) {
        mMicrosecondsAudioBuffered = 0;
        mTotalFrames = 0;
        mTotalAudioSamples = 0;
        mActiveAVIIndexBlock = &mFirstIndexBlock;
        mNumAVIIndexEntries = 0;
        mRiffChunkSize = 0;
        mNextChunkOffset = 4;
        uint32_t headerSize = WriteAVIHeaders();
        mRiffChunkSize += headerSize - 8;
        mVideoEncoder->v3();
    }
    if (mAudioEncoder != 0)
        mAudioEncoder->v3();
    mStopwatch->Stop();
}

// @ 0x00fca160
void MovieEncoder_Avi::AddAVIIndexEntry(const AviIndexEntry* entry)
{
    if (mActiveAVIIndexBlock == 0)
        return;

    if (mActiveAVIIndexBlock->count == mNumAVIIndexEntriesPerBlock) {
        if (mAllocator != 0) {
            mActiveAVIIndexBlock->next = (AviIndexBlock*)
                mAllocator->AllocBlock(0xc, "AVI Index Block", 1);
            AviIndexBlock* block = mActiveAVIIndexBlock->next;
            block->data = 0;
            block->count = 0;
            block->next = 0;
        } else if (mEncodingErrorCallback != 0) {
            ((void (__cdecl*)(const char*, void*))mEncodingErrorCallback)
                ("MovieEncoder_Avi: Allocator is NULL - unable to allocate index block.",
                 mEncodingErrorCallbackData);
        }
        mActiveAVIIndexBlock = mActiveAVIIndexBlock->next;
    }

    if (mActiveAVIIndexBlock == 0)
        return;

    if (mActiveAVIIndexBlock->data == 0) {
        if (mAllocator != 0) {
            mActiveAVIIndexBlock->data = (AviIndexEntry*)
                mAllocator->AllocBlock(mNumAVIIndexEntriesPerBlock << 4, "AVI Index Buffer", 1);
        } else if (mEncodingErrorCallback != 0) {
            ((void (__cdecl*)(const char*, void*))mEncodingErrorCallback)
                ("MovieEncoder_Avi: Allocator is NULL - unable to allocate index buffer.",
                 mEncodingErrorCallbackData);
        }
    }

    if (mActiveAVIIndexBlock->data == 0)
        return;

    AviIndexEntry* e = mActiveAVIIndexBlock->data + mActiveAVIIndexBlock->count;
    *e = *entry;
    ++mActiveAVIIndexBlock->count;
    ++mNumAVIIndexEntries;
}

// @ 0x00fca250
void MovieEncoder_Avi::FreeAVIIndexEntries()
{
    if (mAllocator != 0) {
        AviIndexBlock* first = &mFirstIndexBlock;
        mActiveAVIIndexBlock = first;
        while (mActiveAVIIndexBlock != 0) {
            if (mActiveAVIIndexBlock->data != 0)
                mAllocator->Free(mActiveAVIIndexBlock->data, 0);

            AviIndexBlock* block = mActiveAVIIndexBlock;
            AviIndexBlock* next = block->next;
            if (block != first)
                mAllocator->Free(block, 0);

            mActiveAVIIndexBlock = next;
        }
        mActiveAVIIndexBlock = first;
        first->data = 0;
        return;
    }

    if (mEncodingErrorCallback != 0)
        ((void (__cdecl*)(const char*, void*))mEncodingErrorCallback)
            ("MovieEncoder_Avi: Allocator is NULL - unable to free index buffers.",
             mEncodingErrorCallbackData);
}

// @ 0x00fca2c0
MovieEncoder_Avi* MovieEncoder_Avi::Ctor(uint32_t bufferSize)
{
    vftable = (void*)0x1491b68;
    mBufferedWriter.Init();

    AviIndexBlock* first = &mFirstIndexBlock;
    mAllocator = 0;
    mEncodingErrorCallback = 0;
    mAudioEncoder = 0;
    mVideoEncoder = 0;
    mStopwatch = 0;
    mBufferSize = bufferSize;
    first->data = 0;
    first->count = 0;
    first->next = 0;
    return this;
}