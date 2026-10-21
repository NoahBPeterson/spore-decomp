// Slice s00fcb210: rw::movie::MoviePlayer (Decode/Render/ParseAVIHeaders/PreparePlayer and
// the small state helpers), rw::movie::MovieRenderer, rw::movie::MovieTimer, rw::SList::GetNode.
// MSVC 2008 SP1 x86 (VS2008 SP1 cl 15.00), /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <intrin.h>
#pragma intrinsic(__rdtsc)

typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef int            int32_t;

// ===========================================================================
// rw::core::timer
// ===========================================================================
namespace rw { namespace core { namespace timer {

struct Stopwatch
{
    void*   vftable;     // +0x00
    void*   mCallback;   // +0x04
    int32_t mUnits;      // +0x08
    int32_t pad_0c;
    int32_t mStartLo;    // +0x10
    int32_t mStartHi;    // +0x14
    int32_t mElapsedLo;  // +0x18
    int32_t mElapsedHi;  // +0x1c
    float   mScale;      // +0x20

    virtual void Destroy(int a);        // +0x00 (deleting-ish dtor)
};

unsigned __int64 GetStopwatchCycle();        // 0x011e8080 (returns edx:eax)
void    Stopwatch_Stop(Stopwatch* s);        // 0x011e83a0
Stopwatch* Stopwatch_Ctor(Stopwatch* mem, int units, int a);   // 0x011e82d0 __thiscall
float      Stopwatch_ElapsedF(Stopwatch* s);                   // 0x011e8440 (returns st0)
}}} // namespace rw::core::timer

using rw::core::timer::Stopwatch;

// ===========================================================================
// rw::core::filesys
// ===========================================================================
namespace rw { namespace core { namespace filesys {

struct Stream
{
    int32_t field00;
    int32_t field04;
    int32_t field08;
    int32_t field0c;
    uint8_t pad_10[0x30 - 0x10];
    int32_t field30;

    void* GetChunk();     // 0x011e6b50
    int   Status();       // 0x011e6bf0  (reads [this+0xc])
    int   Poll();         // 0x011e6c40
};

}}} // namespace rw::core::filesys

using rw::core::filesys::Stream;

void FUN_011e7c70(Stream* self, void* chunk);   // release a chunk (ret 4)
void FUN_011e7cf0(Stream* self);                // destroy/release stream

// ===========================================================================
// ICoreAllocator
// ===========================================================================
struct ICoreAllocator
{
    virtual void  v00();                                   // +0x00
    virtual void* Alloc(uint32_t size, const char* name, int a,
                        int b, int c);                     // +0x04
    virtual void  v08();                                   // +0x08
    virtual void  Free(void* p, int a);                    // +0x0c
};

// ===========================================================================
// rw::SList (intrusive singly linked list)
// ===========================================================================
namespace rw {

struct IListNode
{
    virtual void   v00();   // +0x00
    virtual void   v04();   // +0x04
    virtual void   v08();   // +0x08
    virtual void*  Next();  // +0x0c  (returns the following node)
};

struct SList
{
    uint32_t pad_00;   // +0x00
    void*    mHead;    // +0x04
    void*    mTail;    // +0x08
    uint32_t mLength;  // +0x0c

    void* GetNode(uint32_t index) const;   // 0x00fcc220
};

} // namespace rw

// ===========================================================================
// rw::movie interfaces / objects
// ===========================================================================
namespace rw { namespace movie {
struct IVideoRenderer
{
    virtual void v00();                       // +0x00
    virtual void v04(void* a);                // +0x04
    virtual int  v08();                       // +0x08
    virtual int  v0c();                       // +0x0c
    virtual void v10(int a, int b);           // +0x10
    virtual void v14(float a);                // +0x14
    virtual void v18(float a);                // +0x18
    virtual void v1c(float a);                // +0x1c
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(float a);                // +0x2c
    virtual void v30(float a);                // +0x30
    virtual void v34(); virtual void v38();
    virtual void v3c(int a);                  // +0x3c
};

struct IAudioRenderer
{
    virtual void v00();                       // +0x00
    virtual void v04(int a, int b, int c);    // +0x04
    virtual int  v08();                       // +0x08
    virtual void v0c();
    virtual void v10(int a, int b);           // +0x10
    virtual void v14(void* a);                // +0x14
    virtual void v18(void* a);                // +0x18
    virtual void v1c(void* a);                // +0x1c
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c();                       // +0x2c (no args in the audio iface)
    virtual void v30();                       // +0x30
    virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64();
    virtual void v68(void* a);                // +0x68
};

// ---------------------------------------------------------------------------
// MovieDecoder (owned by the decoder slice; only the called methods here)
// ---------------------------------------------------------------------------
struct MovieDecoder
{
    void*   vftable;      // +0x00
    int32_t field04;
    int32_t mStatus;      // +0x08
    int32_t pad_0c;
    int32_t field10;
    int32_t field14;
    int32_t field18;
    int32_t field1c;
    int32_t field20;

    void SetVideoFilter(void* fn);                 // 0x00fc91a0
    void SetAudioFilter(void* fn);                 // 0x00fc91b0
    void SetSubtitleFilter(void* fn);              // 0x00fc91c0
    void SetVideoStream(Stream* s);                // 0x00fc91e0
    void SetAudioStream(Stream* s, uint32_t id);   // 0x00fc91f0
    void VideoDecodeThreadFcn(Stream* s);          // 0x00fc9210
    void PrepareDecoder(int* a, int b, int c, int d, int e, int f,
                        int g, int h, int i);      // 0x00fc9310
    void Shutdown();                               // 0x00fc96d0
    void Destroy();                                // 0x00fc97a0
};

// ---------------------------------------------------------------------------
// MovieRenderer
// ---------------------------------------------------------------------------
struct MovieRenderer
{
    ICoreAllocator* mAllocator;       // +0x00
    void*           mVideoRenderer;   // +0x04
    IAudioRenderer* mAudioRenderer;   // +0x08
    void*           mTimer;           // +0x0c
    int32_t         mAudioFormatA;    // +0x10
    int32_t         mAudioFormatB;    // +0x14
    int32_t         mAudioChannels;   // +0x18
    int32_t         mSubtitleFormatA; // +0x1c
    int32_t         mSubtitleFormatB; // +0x20
    float           mAudioDelay;      // +0x24
    float           mVideoDelay;      // +0x28
    float           mDelay;           // +0x2c
    float           mVolume;          // +0x30
    float           mPosX;            // +0x34
    float           mPosY;            // +0x38
    float           mPosZ;            // +0x3c
    float           mScaleX;          // +0x40
    float           mScaleY;          // +0x44
    uint32_t        mVideoState;      // +0x48
    int32_t         mState;           // +0x4c

    MovieRenderer* Ctor(ICoreAllocator* allocator);      // 0x00fcbc70
    void  Configure(void* fn, void* ctx);                // 0x00fcbcf0
    void  ConfigureAudio(void* fn, void* ctx);           // 0x00fcbd10
    void  Prepare(void* a, void* b, void* c, void* d);   // 0x00fcbd30
    float GetVideoDelay();                               // 0x00fcbe60
    void  PlayVideo();                                   // 0x00fcbe90
    void  PauseVideo();                                  // 0x00fcbec0
    void  ResumeVideo();                                 // 0x00fcbef0
    void  SetVideoPositionX(float v);                    // 0x00fcbf10
    void  SetVideoPositionY(float v);                    // 0x00fcbf50
    void  SetVideoScaleX(float v);                       // 0x00fcbf90
    void  SetVideoScaleY(float v);                       // 0x00fcbfd0
    void  SetRenderCallback(void* a, void* b);           // 0x00fcc010
    void  Stop();                                        // 0x00fcc060
};

void FUN_00fcbce0(MovieRenderer* self, void* fn);        // set video callback
void FUN_00fcc010(MovieRenderer* self, void* a, void* b); // render step

// ---------------------------------------------------------------------------
// MovieTimer
// ---------------------------------------------------------------------------
struct IMovieTimerCallback
{
    virtual void  v0();          // +0x00
    virtual void  v1();          // +0x04
    virtual void  v2();          // +0x08
    virtual float v3();          // +0x0c  (returns elapsed seconds)
};

struct MovieTimer
{
    ICoreAllocator* mAllocator;   // +0x00
    Stopwatch*      mStopwatch;   // +0x04
    IMovieTimerCallback* mCallback; // +0x08

    MovieTimer* Ctor(ICoreAllocator* allocator);   // 0x00fcc0b0
    void  Destroy();                               // 0x00fcc100
    void  Update();                                // 0x00fcc150
    void  Sync();                                  // 0x00fcc180
    float Elapsed();                               // 0x00fcc190
};

// ---------------------------------------------------------------------------
// AVI structures
// ---------------------------------------------------------------------------
struct AVIHeader                    // 0x38 bytes
{
    uint32_t dwMicroSecPerFrame;    // +0x00
    uint32_t dwMaxBytesPerSec;      // +0x04
    uint32_t dwPaddingGranularity;  // +0x08
    uint32_t dwFlags;               // +0x0c
    uint32_t totalFrames;           // +0x10
    uint32_t dwInitialFrames;       // +0x14
    uint32_t dwStreams;             // +0x18
    uint32_t dwSuggestedBufferSize; // +0x1c
    uint32_t width;                 // +0x20
    uint32_t height;                // +0x24
    uint32_t dwReserved[4];         // +0x28
};

struct AVIStreamHeader              // 0x38 bytes
{
    uint32_t fccType;               // +0x00
    uint32_t fccHandler;            // +0x04
    uint32_t dwFlags;               // +0x08
    uint16_t wPriority;             // +0x0c
    uint16_t wLanguage;             // +0x0e
    uint32_t dwInitialFrames;       // +0x10
    uint32_t scale;                 // +0x14
    uint32_t rate;                  // +0x18
    uint32_t dwStart;               // +0x1c
    uint32_t dwLength;              // +0x20
    uint32_t dwSuggestedBufferSize; // +0x24
    uint32_t dwQuality;             // +0x28
    uint32_t dwSampleSize;          // +0x2c
    int16_t  rcFrame[4];            // +0x30
};

struct AVIBitmapInfoHeader          // 0x28 bytes
{
    uint32_t biSize;                // +0x00
    int32_t  biWidth;               // +0x04
    int32_t  biHeight;              // +0x08
    uint16_t biPlanes;              // +0x0c
    uint16_t biBitCount;            // +0x0e
    uint32_t biCompression;         // +0x10
    uint32_t biSizeImage;           // +0x14
    int32_t  biXPelsPerMeter;       // +0x18
    int32_t  biYPelsPerMeter;       // +0x1c
    uint32_t biClrUsed;             // +0x20
    uint32_t biClrImportant;        // +0x24
};

struct AVIPCMWaveFormat             // 0x10 bytes
{
    uint16_t wFormatTag;            // +0x00
    uint16_t nChannels;             // +0x02
    uint32_t nSamplesPerSec;        // +0x04
    uint32_t nAvgBytesPerSec;       // +0x08
    uint16_t nBlockAlign;           // +0x0c
    uint16_t wBitsPerSample;        // +0x0e
};

// AVIUtils FCC/reader helpers (cdecl, 3 args).
char FUN_00fc80f0(int* cursor, int* remaining, uint32_t* outId);
char FUN_00fc8120(int* cursor, int* remaining, uint32_t* outChunk);
char FUN_00fc8150(int* cursor, int* remaining, void* out);
char FUN_00fc8180(int* cursor, int* remaining, void* out);
char FUN_00fc81b0(int* cursor, int* remaining, void* out);

// FCC constants (the original compares the loaded dword against these globals).
extern uint32_t g_fcc_hdrl;   // 0x015b17c0
extern uint32_t g_fcc_RIFF;   // 0x015b179c
extern uint32_t g_fcc_LIST;   // 0x015b17a4
extern uint32_t g_fcc_avih;   // 0x015b17ac
extern uint32_t g_fcc_strh;   // 0x015b17b4
extern uint32_t g_fcc_strf;   // 0x015b17b8
extern uint32_t g_fcc_vids;   // 0x015b17cc
extern uint32_t g_fcc_auds;   // 0x015b17d0

// ---------------------------------------------------------------------------
// MoviePlayer
// ---------------------------------------------------------------------------
struct IVideoDecoder;   // opaque

struct MoviePlayer
{
    ICoreAllocator* mAllocator;                 // +0x00
    void* mStreamerParseFunc;                   // +0x04
    void* mStreamerVideoFilterFunc;             // +0x08
    void* mStreamerAudioFilterFunc;             // +0x0c
    void* mStreamerDataFilterFunc;              // +0x10
    void* mStreamerSubtitleFilterFunc;          // +0x14
    void* mStreamerSubtitleFilterContext;       // +0x18
    uint8_t pad_1c[0x40 - 0x1c];                // +0x1c
    uint32_t mVideoFilterCtx;                   // +0x40
    uint32_t mAudioFilterCtx;                   // +0x44
    uint32_t mSubtitleFilterCtx;                // +0x48
    uint32_t mRenderCallbackCtx;                // +0x4c
    uint32_t mSubtitleCallbackCtx;              // +0x50
    uint8_t pad_54[0x60 - 0x54];                // +0x54
    uint32_t mDataCallbackFuncContext;          // +0x60
    uint8_t pad_64[0x78 - 0x64];                // +0x64
    uint32_t mAudioFilePathPresent;             // +0x78
    uint8_t pad_7c[0x8c - 0x7c];                // +0x7c
    uint32_t mNumberAudioTracks;                // +0x8c
    uint32_t mSelectedAudioTrack;               // +0x90
    uint8_t pad_94[0xac - 0x94];                // +0x94
    uint32_t mWidth;                            // +0xac
    uint32_t mHeight;                           // +0xb0
    uint32_t mTotalFrames;                      // +0xb4
    void* mCurrentVideoRenderable;              // +0xb8
    uint8_t pad_bc[0xf0 - 0xbc];                // +0xbc
    float mPlaybackFps;                         // +0xf0
    float mVideoRenderingDelay;                 // +0xf4
    int32_t mLastRenderedFrame;                 // +0xf8
    uint32_t mGoalFrame;                        // +0xfc
    int32_t mPreviousGoalFrame;                 // +0x100
    uint32_t mVideoDecodeThreadProcessor;       // +0x104
    uint32_t mNumVideoRenderables;              // +0x108
    MovieDecoder* mMovieDecoder;                // +0x10c
    MovieRenderer* mMovieRenderer;              // +0x110
    MovieTimer* mMovieTimer;                    // +0x114
    void* mMovieStreamBuffer;                   // +0x118
    Stream* mVideoStream;                       // +0x11c
    Stream* mDataStream;                        // +0x120
    Stream* mNullStream;                        // +0x124
    uint32_t mAudioStreamRequestId;             // +0x128
    void* mAudioStreamBuffer;                   // +0x12c
    Stream* mAudioStream;                       // +0x130
    Stream* mAudioNullStream;                   // +0x134
    void* mSubtitleStreamBuffer;                // +0x138
    Stream* mSubtitleStream;                    // +0x13c
    Stream* mSubtitleNullStream;                // +0x140
    void* mSubtitlePreloadBuffer;               // +0x144
    void* mAudioPreloadBuffer;                  // +0x148
    void* mVideoPreloadBuffer;                  // +0x14c
    uint32_t mState;                            // +0x150
    uint8_t mField154;                          // +0x154
    uint8_t pad_155[3];                         // +0x155
    uint32_t mEventLogger;                      // +0x158
    uint8_t mIsAVIFile;                         // +0x15c
    uint8_t pad_15d[3];                         // +0x15d
    AVIHeader mAVIHeader;                       // +0x160
    AVIStreamHeader mAVIVidsStreamHeader;       // +0x198
    AVIStreamHeader mAVIAudsStreamHeader;       // +0x1d0
    AVIBitmapInfoHeader mAVIBitmapInfoHeader;   // +0x208
    AVIPCMWaveFormat mAVIPCMWaveFormat;         // +0x230
    uint8_t pad_240[0x240 - 0x240];             // +0x240 (movie cursor block below)

    bool ParseAVIHeaders(int flag);   // 0x00fcb210
    void Decode();                    // 0x00fcb490
    void Render();                    // 0x00fcb5e0
    void Tick();                      // 0x00fcb6e0
    void TickReverse();               // 0x00fcb710
    void Shutdown();                  // 0x00fcb740
    void Destroy();                   // 0x00fcb860
    bool PreparePlayer(int flag);     // 0x00fcb920
};

void FUN_00fc9660(void* eventLogger);
void FUN_00fc9050(void* eventLogger);
void FUN_00fc8650(void* eventLogger);
void FUN_00fc94f0(int index, void* outA, void* outB);
void FUN_00c2e4e0(void* p);            // UTFWin element teardown
void FUN_00fc9650();                   // video-render callback
void FUN_00fc9670();                   // decoder-ready callback
void FUN_011e8440(void* stopwatch);

namespace EA { namespace Thread {
void ThreadSleep(void* tag);           // 0x00921df0
}}

} // namespace movie
} // namespace rw

using namespace rw::movie;
using namespace rw::core::filesys;
using rw::SList;

// ===========================================================================
// MovieRenderer
// ===========================================================================

// @ 0x00fcbc70
MovieRenderer* MovieRenderer::Ctor(ICoreAllocator* allocator)
{
    mAllocator       = allocator;
    mVideoRenderer   = 0;
    mAudioRenderer   = 0;
    mTimer           = 0;
    mAudioFormatA    = 0;
    mAudioFormatB    = 0;
    mAudioChannels   = 0;
    mSubtitleFormatA = 0;
    mSubtitleFormatB = 0;
    mAudioDelay      = 0.0f;
    mVideoDelay      = 0.0f;
    mDelay           = 0.0f;
    mVolume          = 1.0f;
    mPosX            = 0.0f;
    mPosY            = 0.0f;
    mPosZ            = 0.0f;
    mScaleX          = 1.0f;
    mScaleY          = 1.0f;
    mVideoState      = 0;
    mState           = 0;
    return this;
}

// @ 0x00fcbcf0
void MovieRenderer::Configure(void* fn, void* ctx)
{
    if (mVideoState == 0)
    {
        mAudioFormatA = (int32_t)fn;
        mAudioFormatB = (int32_t)ctx;
    }
}

// @ 0x00fcbd10
void MovieRenderer::ConfigureAudio(void* fn, void* ctx)
{
    if (mState == 0)
    {
        mSubtitleFormatA = (int32_t)fn;
        mSubtitleFormatB = (int32_t)ctx;
    }
}

// @ 0x00fcbd30
void MovieRenderer::Prepare(void* a, void* b, void* c, void* d)
{
    if (mVideoState == 0)
    {
        if (mAudioRenderer != 0)
        {
            mAudioRenderer->v04((int)mAllocator, (int)c, (int)d);
            mVideoDelay = (float)mAudioRenderer->v08();
            mAudioRenderer->v10(mAudioFormatA, mAudioFormatB);
            mAudioRenderer->v14((void*)mAudioChannels);
        }
        mVideoState = 1;
    }
    if (mState == 0)
    {
        if (mVideoRenderer != 0)
        {
            IVideoRenderer* vr = (IVideoRenderer*)mVideoRenderer;
            vr->v04((void*)mAllocator);
            vr->v0c();
            vr->v10(mSubtitleFormatA, mSubtitleFormatB);
            vr->v14(mPosX);
            vr->v18(mPosY);
            vr->v1c(mPosZ);
            vr->v2c(mScaleX);
            vr->v30(mScaleY);
        }
        if (mTimer != 0)
            ((IVideoRenderer*)mTimer)->v04((void*)mAllocator);
        mDelay = mVideoDelay - mAudioDelay;
        mState = 1;
    }
}

// @ 0x00fcbe60
float MovieRenderer::GetVideoDelay()
{
    switch (mState)
    {
    case 1:
    case 2:
        return mDelay;
    case 0:
    case 3:
    case 4:
        return 0.0f;
    default:
        return 0.0f;
    }
}

// @ 0x00fcbe90
void MovieRenderer::PlayVideo()
{
    if (mVideoState - 1 == 0)
    {
        if (mAudioRenderer != 0)
            mAudioRenderer->v20();
        mVideoState = 2;
    }
}

// @ 0x00fcbec0
void MovieRenderer::PauseVideo()
{
    if (mVideoState - 1 <= 1u)
    {
        IAudioRenderer* ar = mAudioRenderer;
        if (ar != 0)
            ar->v24();
        mVideoState = 3;
    }
}

// @ 0x00fcbef0
void MovieRenderer::ResumeVideo()
{
    if (mVideoState == 3)
    {
        if (mAudioRenderer != 0)
            mAudioRenderer->v28();
        mVideoState = 2;
    }
}

// @ 0x00fcbf10
void MovieRenderer::SetVideoPositionX(float v)
{
    if (mState == 0)
    {
        mPosX = v;
    }
    else if (mState - 1 <= 1u)
    {
        mPosX = v;
        if (mVideoRenderer != 0)
            ((IVideoRenderer*)mVideoRenderer)->v14(v);
    }
}

// @ 0x00fcbf50
void MovieRenderer::SetVideoPositionY(float v)
{
    if (mState == 0)
    {
        mPosY = v;
    }
    else if (mState - 1 <= 1u)
    {
        mPosY = v;
        if (mVideoRenderer != 0)
            ((IVideoRenderer*)mVideoRenderer)->v18(v);
    }
}

// @ 0x00fcbf90
void MovieRenderer::SetVideoScaleX(float v)
{
    if (mState == 0)
    {
        mScaleX = v;
    }
    else if (mState - 1 <= 1u)
    {
        mScaleX = v;
        if (mVideoRenderer != 0)
            ((IVideoRenderer*)mVideoRenderer)->v2c(v);
    }
}

// @ 0x00fcbfd0
void MovieRenderer::SetVideoScaleY(float v)
{
    if (mState == 0)
    {
        mScaleY = v;
    }
    else if (mState - 1 <= 1u)
    {
        mScaleY = v;
        if (mVideoRenderer != 0)
            ((IVideoRenderer*)mVideoRenderer)->v30(v);
    }
}

// @ 0x00fcc010
void MovieRenderer::SetRenderCallback(void* a, void* b)
{
    switch (mState)
    {
    case 1:
        mState = 2;
        break;
    case 2:
        break;
    default:
        return;
    }
    if (mVideoRenderer != 0)
        ((IVideoRenderer*)mVideoRenderer)->v3c((int)a);
    if (mTimer != 0)
        ((IAudioRenderer*)mTimer)->v68(b);
}

// @ 0x00fcc060
void MovieRenderer::Stop()
{
    switch (mVideoState)
    {
    case 0:
    case 1:
    case 4:
        mVideoState = 5;
        break;
    case 2:
    case 3:
        if (mAudioRenderer != 0)
            mAudioRenderer->v2c();
        mVideoState = 5;
        break;
    default:
        break;
    }
    if ((uint32_t)mState <= 2u)
        mState = 3;
}

// ===========================================================================
// MovieTimer
// ===========================================================================

// @ 0x00fcc0b0
MovieTimer* MovieTimer::Ctor(ICoreAllocator* allocator)
{
    mAllocator = allocator;
    Stopwatch* sw = (Stopwatch*)allocator->Alloc(0x28, "Stopwatch object", 1, 4, 0);
    mStopwatch = sw;
    if (sw != 0)
    {
        sw = rw::core::timer::Stopwatch_Ctor(sw, 4, 0);
        mStopwatch = sw;
        mCallback = 0;
        return this;
    }
    mStopwatch = 0;
    mCallback = 0;
    return this;
}

// @ 0x00fcc100
void MovieTimer::Destroy()
{
    mCallback = 0;
    if (mStopwatch != 0)
    {
        mStopwatch->Destroy(0);
        mAllocator->Free(mStopwatch, 0);
        mStopwatch = 0;
    }
}

// @ 0x00fcc150
void MovieTimer::Update()
{
    Stopwatch* sw = mStopwatch;
    unsigned __int64 v;
    if (sw->mUnits == 1)
    {
        v = __rdtsc();
    }
    else
    {
        v = rw::core::timer::GetStopwatchCycle();
    }
    sw->mStartHi = (int32_t)(v >> 32);
    sw->mStartLo = (int32_t)v;
}

// @ 0x00fcc180
void MovieTimer::Sync()
{
    rw::core::timer::Stopwatch_Stop(mStopwatch);
}

// @ 0x00fcc190
float MovieTimer::Elapsed()
{
    if (mCallback != 0)
    {
        float f = mCallback->v3();
        if (0.0f < f)
            return f;
    }
    return rw::core::timer::Stopwatch_ElapsedF(mStopwatch);
}

// @ 0x00fcc220
void* SList::GetNode(uint32_t index) const
{
    uint32_t i = index;
    if (i >= mLength)
        return 0;
    if (i == mLength - 1)
        return mTail;

    void* node = mHead;
    while (i > 0u && node != 0)
    {
        --i;
        node = ((IListNode*)node)->Next();
    }
    return node;
}

// ===========================================================================
// MoviePlayer
// ===========================================================================

// @ 0x00fcb210
bool MoviePlayer::ParseAVIHeaders(int flag)
{
    int chunk = (int)mVideoStream->GetChunk();
    while (chunk == 0)
    {
        EA::Thread::ThreadSleep((void*)0x01491d7c);
        int st = mVideoStream->Poll();
        if (st == 2)
        {
            mVideoStream = 0;
            return true;
        }
        if ((char)flag == 0)
            return false;
        chunk = (int)mVideoStream->GetChunk();
    }

    int local_48 = *(int*)(chunk + 8);
    int local_44 = 0;
    int remaining = *(int*)(chunk + 4);
    uint32_t local_38[14];
    uint32_t local_40 = 0;
    local_38[0] = 0;

    if (g_fcc_hdrl != 0)
    {
        do
        {
            char ok = FUN_00fc80f0(&local_48, &remaining, &local_40);
            if (ok == 0)
                return false;

            if (local_40 == g_fcc_RIFF || local_40 == g_fcc_LIST)
            {
                ok = FUN_00fc8120(&local_48, &remaining, (uint32_t*)&local_44);
                if (ok == 0)
                    return false;
            }
            else if (local_40 == g_fcc_avih)
            {
                ok = FUN_00fc8150(&local_48, &remaining, &mAVIHeader);
                if (ok == 0)
                    return false;
            }
            else if (local_40 == g_fcc_strh)
            {
                ok = FUN_00fc8150(&local_48, &remaining, local_38);
                if (ok == 0)
                    return false;
                if (local_38[0] == g_fcc_vids)
                {
                    uint32_t* src = local_38;
                    uint32_t* dst = (uint32_t*)&mAVIVidsStreamHeader;
                    for (int i = 14; i != 0; --i)
                        *dst++ = *src++;
                }
                else if (local_38[0] == g_fcc_auds)
                {
                    uint32_t* src = local_38;
                    uint32_t* dst = (uint32_t*)&mAVIAudsStreamHeader;
                    for (int i = 14; i != 0; --i)
                        *dst++ = *src++;
                }
            }
            else if (local_40 == g_fcc_strf)
            {
                if (local_38[0] == g_fcc_vids)
                    ok = FUN_00fc8180(&local_48, &remaining, &mAVIBitmapInfoHeader);
                else if (local_38[0] == g_fcc_auds)
                    ok = FUN_00fc81b0(&local_48, &remaining, &mAVIPCMWaveFormat);
                else
                {
                    local_48 += 0;
                    remaining -= 0;
                    continue;
                }
                if (ok == 0)
                    return false;
            }
            else
            {
                local_48  += 0;
                remaining -= 0;
            }
        } while (local_44 != (int)g_fcc_hdrl);
    }

    FUN_011e7c70(mVideoStream, (void*)chunk);

    mWidth       = mAVIHeader.width;
    mHeight      = mAVIHeader.height;
    mTotalFrames = mAVIHeader.totalFrames;

    float fNum = (float)(int)mAVIVidsStreamHeader.rate;
    if ((int)mAVIVidsStreamHeader.rate < 0)
        fNum += 4294967296.0f;
    float fDen = (float)(int)mAVIVidsStreamHeader.scale;
    if ((int)mAVIVidsStreamHeader.scale < 0)
        fDen += 4294967296.0f;
    mPlaybackFps = fNum / fDen;
    return true;
}

// @ 0x00fcb490
void MoviePlayer::Decode()
{
    if (mState - 2 > 2u)
        return;

    float elapsed = mMovieTimer->Elapsed();
    int goal = (int)((mVideoRenderingDelay + elapsed) * (mPlaybackFps * 0.001f));
    mGoalFrame = (uint32_t)goal;
    FUN_00fc94f0(goal, &mCurrentVideoRenderable, (char*)this + 0xbc);

    if (mVideoFilterCtx == 0)
    {
        int c = (int)mVideoStream->GetChunk();
        if (c != 0)
            FUN_011e7c70(mVideoStream, (void*)c);
    }
    if (mAudioFilterCtx == 0 && mAudioStream != 0)
    {
        int c = (int)mAudioStream->GetChunk();
        if (c != 0)
            FUN_011e7c70(mAudioStream, (void*)c);
    }
    if (mDataStream != 0)
    {
        int c = (int)mDataStream->GetChunk();
        if (c != 0)
        {
            void (*cb)(int, int, int) = (void (*)(int, int, int))mStreamerSubtitleFilterFunc;
            cb(*(int*)(c + 8) + 8, *(int*)(c + 4) - 8, (int)mDataCallbackFuncContext);
            FUN_011e7c70(mDataStream, (void*)c);
        }
    }
    {
        int c = (int)mNullStream->GetChunk();
        if (c != 0)
            FUN_011e7c70(mNullStream, (void*)c);
    }
    if (mAudioNullStream != 0)
    {
        int c = (int)mAudioNullStream->GetChunk();
        if (c != 0)
            FUN_011e7c70(mAudioNullStream, (void*)c);
    }
    if (mSubtitleNullStream != 0)
    {
        int c = (int)mSubtitleNullStream->GetChunk();
        if (c != 0)
            FUN_011e7c70(mSubtitleNullStream, (void*)c);
    }
}

// @ 0x00fcb5e0
void MoviePlayer::Render()
{
    if (mState == 2)
    {
        mMovieTimer->Update();
        mState = 3;
        mMovieRenderer->PlayVideo();
    }
    else if (mState <= 2)
        return;
    else if (mState > 4)
        return;

    if (mCurrentVideoRenderable != 0)
        mLastRenderedFrame = *(int*)((char*)mCurrentVideoRenderable + 0x34);

    FUN_00fcc010(mMovieRenderer, &mCurrentVideoRenderable, (char*)this + 0xbc);
    EA::Thread::ThreadSleep((void*)0x01491d7c);
    if (mAudioStream != 0)
        mAudioStream->GetChunk();
}

// @ 0x00fcb6e0
void MoviePlayer::Tick()
{
    if (mState - 2 <= 2u)
    {
        mMovieRenderer->PauseVideo();
        mMovieTimer->Sync();
    }
}

// @ 0x00fcb710
void MoviePlayer::TickReverse()
{
    if (mState - 2 <= 2u)
    {
        mMovieRenderer->ResumeVideo();
        mMovieTimer->Update();
    }
}

// @ 0x00fcb740
void MoviePlayer::Shutdown()
{
    mMovieRenderer->Stop();
    mMovieDecoder->Shutdown();

    if (mAudioFilePathPresent != 0 && mAudioStream != 0)
    {
        FUN_011e7cf0(mAudioStream);
        mAudioStream = 0;
        mAudioFilePathPresent = 0;
    }
    if (mDataStream != 0)
    {
        FUN_011e7cf0(mDataStream);
        mDataStream = 0;
    }
    if (mAudioNullStream != 0)
    {
        FUN_011e7cf0(mAudioNullStream);
        mAudioNullStream = 0;
    }
    if (mVideoFilterCtx != 0)
    {
        mAllocator->Free((void*)mVideoFilterCtx, 0);
        mVideoFilterCtx = 0;
    }
    if (mSubtitleCallbackCtx != 0)
    {
        mAllocator->Free((void*)mSubtitleCallbackCtx, 0);
        mSubtitleCallbackCtx = 0;
    }
    if (mAudioFilterCtx != 0)
    {
        mAllocator->Free((void*)mAudioFilterCtx, 0);
        mAudioFilterCtx = 0;
    }
    if (mSubtitleFilterCtx != 0)
    {
        mAllocator->Free((void*)mSubtitleFilterCtx, 0);
        mSubtitleFilterCtx = 0;
    }
    if (mRenderCallbackCtx != 0)
    {
        mAllocator->Free((void*)mRenderCallbackCtx, 0);
        mRenderCallbackCtx = 0;
    }
    mState = 6;
}

// @ 0x00fcb860
void MoviePlayer::Destroy()
{
    if (mEventLogger != 0)
    {
        FUN_00fc8650((void*)mEventLogger);
        FUN_00fc9050((void*)mEventLogger);
        mAllocator->Free((void*)mEventLogger, 0);
        mEventLogger = 0;
    }
    if (mMovieTimer != 0)
    {
        mMovieTimer->Destroy();
        mAllocator->Free(mMovieTimer, 0);
        mMovieTimer = 0;
    }
    if (mMovieRenderer != 0)
    {
        FUN_00c2e4e0(mMovieRenderer);
        mAllocator->Free(mMovieRenderer, 0);
        mMovieRenderer = 0;
    }
    if (mMovieDecoder != 0)
    {
        mMovieDecoder->Destroy();
        mAllocator->Free(mMovieDecoder, 0);
        mMovieDecoder = 0;
    }
    FUN_00c2e4e0((char*)this + 0xbc);
}

// @ 0x00fcb920
bool MoviePlayer::PreparePlayer(int flag)
{
    if (mState != 1)
        return true;

    if (mVideoStream != 0)
    {
        if (mIsAVIFile)
        {
            if (!ParseAVIHeaders(flag))
                return false;
        }
        else
        {
            mWidth = 0;
            mHeight = 0;
            mPlaybackFps = 0.0f;
            int st = mVideoStream->Status();
            while (st < 0x20)
            {
                EA::Thread::ThreadSleep((void*)0x01491d7c);
                st = mVideoStream->Poll();
                if (st == 2)
                    break;
                if ((char)flag == 0)
                    return false;
                st = mVideoStream->Status();
            }
            st = mVideoStream->Status();
            if (st < 0x20)
            {
                mVideoStream = 0;
            }
            else
            {
                int c = (int)mVideoStream->GetChunk();
                if (c != 0)
                {
                    int* p = *(int**)(c + 8);
                    if (*p == 0x6468564d)   // 'MVhd'
                    {
                        mWidth       = *(uint16_t*)((char*)p + 0x0c);
                        mHeight      = *(uint16_t*)((char*)p + 0x0e);
                        mTotalFrames = (uint32_t)p[4];
                        float f = (float)p[6];
                        if (p[6] < 0)
                            f += 4294967296.0f;
                        mPlaybackFps = f / (float)*(uint16_t*)((char*)p + 0x1c);
                    }
                    FUN_011e7c70(mVideoStream, (void*)c);
                }
            }
        }

        if (mVideoStream != 0)
        {
            mMovieDecoder->SetVideoFilter(mStreamerVideoFilterFunc);
            FUN_00fcbce0(mMovieRenderer, (void*)mRenderCallbackCtx);
            mMovieDecoder->SetVideoStream(mVideoStream);
        }
    }

    if (mAudioStream != 0)
    {
        ++mNumberAudioTracks;
        mMovieDecoder->SetAudioFilter((void*)mAudioFilterCtx);
        mMovieDecoder->SetAudioStream(mAudioStream, mAudioStreamRequestId);
        mMovieRenderer->Configure((void*)FUN_00fc9650, (void*)mMovieDecoder);
    }

    if (mSubtitleStream != 0)
    {
        int st = mSubtitleStream->Status();
        while (st == 0)
        {
            EA::Thread::ThreadSleep((void*)0x01491d7c);
            st = mSubtitleStream->Poll();
            if (st == 2)
                break;
            if ((char)flag == 0)
                return false;
            st = mSubtitleStream->Status();
        }
        st = mSubtitleStream->Status();
        if (st < 1)
        {
            mSubtitleStream = 0;
        }
        else
        {
            mMovieDecoder->SetSubtitleFilter((void*)mSubtitleFilterCtx);
            mMovieDecoder->VideoDecodeThreadFcn(mSubtitleStream);
        }
    }

    return true;
}
