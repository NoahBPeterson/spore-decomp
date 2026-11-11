// src/game/SPMovie/movieplayer.cpp -- migrated from slice(s) s00fcb210, s00fca300 by tools/migrate/rewrite.py
// Object file: SPMovie/movieplayer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* FUN_011e7910(int a, void* b, int c, int d, int e, int f);
extern "C" char  FUN_011ea7d0(const char* path);
extern "C" unsigned long long FUN_011ea850(const char* path);
#include <intrin.h>
#pragma intrinsic(__rdtsc)
#pragma intrinsic(_ReadWriteBarrier)

// ---- items of slice s00fca300 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace core {
namespace filesys {
class Stream; class AsyncOp_s00fc_a300;
}
}
}
namespace rw {
namespace movie {
struct ICoreAllocator
{
    virtual void v0();                                                   // +0x00
    virtual void* Alloc(unsigned int size, const char* name, int a,
                        int b, int c);                                   // +0x04
virtual void v2();
virtual void v3();
    virtual void Free(void* p, int a);                                   // +0x10
};
}
}
namespace rw {
namespace movie {
struct StreamContext
{
    void* mStreamEnd;       // +0x00
    int32_t mFileLength;    // +0x04
    int32_t mBytesSoFar;    // +0x08
};
}
}
namespace rw {
namespace movie {
struct StreamerContext
{
    void* mStreamEnd;       // +0x00
    int32_t mFileLength;    // +0x04
    int32_t mBytesSoFar;    // +0x08
    int32_t mField0c;       // +0x0c
    int32_t mField10;       // +0x10
    uint8_t pad_14[0x34 - 0x14];
    void Ctor();            // 0x00fcd3c0
};
}
}
namespace rw {
namespace movie {
class MovieRenderer
{ public:
    MovieRenderer* Ctor(ICoreAllocator* a);   // 0x00fcbc70
    void SetVideoPositionX(float v);   // 0x00fcbf10
    void SetVideoPositionY(float v);   // 0x00fcbf50
    void SetVideoScaleX(float v);      // 0x00fcbf90
    void SetVideoScaleY(float v);      // 0x00fcbfd0
};
}
}
namespace rw {
namespace movie {
class MovieTimer
{ public:
    MovieTimer* Ctor(ICoreAllocator* a);   // 0x00fcc0b0
    void SetCallback(void* fn);            // 0x00fcc140
};
}
}
namespace rw {
namespace movie {
class MovieDecoder
{ public:
    MovieDecoder* Ctor(ICoreAllocator* a);   // 0x00fc90e0
    void SetCallback(void* fn);              // 0x00fc91d0
};
}
}
namespace rw {
namespace movie {
class MoviePlayer
{ public:
    ICoreAllocator* mAllocator;                     // +0x00
    void* mStreamerParseFunc;                       // +0x04
    void* mStreamerVideoFilterFunc;                 // +0x08
    void* mStreamerAudioFilterFunc;                 // +0x0c
    void* mStreamerDataFilterFunc;                  // +0x10
    void* mStreamerSubtitleFilterFunc;              // +0x14
    void* mStreamerSubtitleFilterContext;           // +0x18
    StreamContext mVideoStreamingContext;           // +0x1c
    StreamContext mAudioStreamingContext;           // +0x28
    StreamContext mSubtitleStreamingContext;        // +0x34
    void* mDataCallbackFunc;                        // +0x40
    void* mStreamerVideoCallbackFunc;               // +0x44
    void* mStreamerAudioCallbackFunc;               // +0x48
    void* mStreamerSubtitleCallbackFunc;            // +0x4c
    void* mStreamerDataPreloadCallbackFunc;         // +0x50
    void* mStreamerVideoPreloadCallbackFunc;        // +0x54
    void* mStreamerAudioPreloadCallbackFunc;        // +0x58
    void* mStreamerSubtitlePreloadCallbackFunc;     // +0x5c
    void* mAudioStreamerContext;                    // +0x60
    char* mVideoFilePath;                           // +0x64
    uint32_t mVideoFilePathSize;                    // +0x68
    uint32_t mVideoFilePathOffset;                  // +0x6c
    uint32_t mVideoDataSize;                        // +0x70
    uint32_t mVideoDataSizeHi;                      // +0x74
    char* mAudioFilePath;                           // +0x78
    uint32_t mAudioFilePathSize;                    // +0x7c
    char* mSubtitleFilePath;                        // +0x80
    uint32_t mSubtitleFilePathSize;                 // +0x84
    uint8_t mPreloadVideoFile;                      // +0x88
    uint8_t mPreloadAudioFile;                      // +0x89
    uint8_t mPreloadSubtitleFile;                   // +0x8a
    uint8_t pad_8b;                                 // +0x8b
    uint32_t mNumberAudioTracks;                    // +0x8c
    uint32_t mSelectedAudioTrack;                   // +0x90
    float mVolume;                                  // +0x94
    float mVideoPositionX;                          // +0x98
    float mVideoPositionY;                          // +0x9c
    float mVideoPositionZ;                          // +0xa0
    float mVideoScaleX;                             // +0xa4
    float mVideoScaleY;                             // +0xa8
    uint32_t mWidth;                                // +0xac
    uint32_t mHeight;                               // +0xb0
    uint32_t mTotalFrames;                          // +0xb4
    void* mCurrentVideoRenderable;                  // +0xb8
    StreamerContext mStreamingContext;              // +0xbc
    float mPlaybackFps;                             // +0xf0
    float mVideoRenderingDelay;                     // +0xf4
    int32_t mLastRenderedFrame;                     // +0xf8
    uint32_t mGoalFrame;                            // +0xfc
    int32_t mPreviousGoalFrame;                     // +0x100
    uint32_t mVideoDecodeThreadProcessor;           // +0x104
    uint32_t mNumVideoRenderables;                  // +0x108
    MovieDecoder* mMovieDecoder;                    // +0x10c
    MovieRenderer* mMovieRenderer;                  // +0x110
    MovieTimer* mMovieTimer;                        // +0x114
    void* mMovieStreamBuffer;                       // +0x118
    void* mVideoStream;                             // +0x11c
    void* mDataStream;                              // +0x120
    void* mNullStream;                              // +0x124
    uint32_t mAudioStreamRequestId;                 // +0x128
    void* mAudioStreamBuffer;                       // +0x12c
    void* mAudioStream;                             // +0x130
    void* mAudioNullStream;                         // +0x134
    void* mSubtitleStreamBuffer;                    // +0x138
    void* mSubtitleStream;                          // +0x13c
    void* mSubtitleNullStream;                      // +0x140
    void* mSubtitlePreloadBuffer;                   // +0x144
    void* mAudioPreloadBuffer;                      // +0x148
    void* mVideoPreloadBuffer;                      // +0x14c
    uint32_t mState;                                // +0x150
    uint8_t mField154;                              // +0x154
    uint8_t pad_155[3];                             // +0x155
    uint32_t mEventLogger;                          // +0x158
    uint8_t mIsAVIFile;                             // +0x15c
    uint8_t pad_15d[3];                             // +0x15d
    uint8_t pad_160[0x240 - 0x160];                 // +0x160 .. +0x240
    uint32_t mLastGettable;                         // +0x240
    uint32_t mAvgDeltaGettable;                     // +0x244

    MoviePlayer* Ctor(ICoreAllocator* allocator);    // 0x00fca720
    void OpenFiles(unsigned int videoBufferSize, int flags);   // 0x00fcab70
    int  ConfigureVideo(const char* path, unsigned int a, unsigned int b,
                        unsigned int c, unsigned int d);        // 0x00fcaa70
    void SetDataCallback(void* fn);                 // 0x00fca9b0
    void SetVideoFilter(void* fn);                  // 0x00fca9d0
    void SetAudioCallback(void* fn);                // 0x00fca9f0
    void SetStreamerSubtitleFilter(void* fn);       // 0x00fcaa10
    void SetAudioStreamFilter(void* fn);            // 0x00fcaa40
    void SetVideoPositionX(float v);                // 0x00fcb150
    void SetVideoPositionY(float v);                // 0x00fcb180
    void SetVideoScaleX(float v);                   // 0x00fcb1b0
    void SetVideoScaleY(float v);                   // 0x00fcb1e0
};
}
}
extern "C" void* FUN_011e7910(int a, void* b, int c, int d, int e, int f);
extern "C" char  FUN_011ea7d0(const char* path);
extern "C" unsigned long long FUN_011ea850(const char* path);
namespace rw {
namespace core {
namespace filesys {
class Stream
{ public:
    void SetOffset(int off);                               // 0x011e6cd0
    int  GetOffset();                                      // 0x011e69c0
    void SetFilter(int off, void* fn, void* ctx);          // 0x011e7950
    void* CreateReadRequest(void* a);                      // 0x011e79f0
    int  QueueMem(void* buf, int size, void* fn, void* ctx); // 0x011e6aa0
    int  QueueFile(const char* path, int off, int hi, void* fn, void* ctx);  // 0x011e69d0
};
}
}
}
namespace rw {
namespace core {
namespace filesys {
class AsyncOp_s00fc_a300
{ public:
    AsyncOp_s00fc_a300();
    int  OpenPath(const char* path, int, int, int, int);   // 0x011e8a40
    void Run(void* a);                                     // 0x011e8740
    int  Wait();                                           // 0x011e8770
    void Read(int f, void* buf, int a, int b, int size, int c, int d, int e);   // 0x011e8820
    void Finish(int f, int a);                             // 0x011e89e0
    void Delete();                                         // 0x011e8530
};
}
}
}
// ---- items of slice s00fca300 end

// ---- items of slice s00fcb210 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace core {
namespace timer {
class Stopwatch
{ public:
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
}
}
}
using rw::core::timer::Stopwatch;
namespace rw {
namespace core {
namespace filesys {
class Stream_s00fc_b210
{ public:
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
}  // namespace rw::core::filesys
}
}
using rw::core::filesys::Stream_s00fc_b210;
void FUN_011e7c70(Stream_s00fc_b210* self, void* chunk);   // release a chunk (ret 4)
void FUN_011e7cf0(Stream_s00fc_b210* self);                // destroy/release stream
struct ICoreAllocator_s00fc_b210
{
    virtual void  v00();                                   // +0x00
    virtual void* Alloc(uint32_t size, const char* name, int a,
                        int b, int c);                     // +0x04
    virtual void  v08();                                   // +0x08
    virtual void  Free(void* p, int a);                    // +0x0c
};
namespace rw {
namespace movie {
class IVideoRenderer
{ public:
    virtual void v00();                       // +0x00
    virtual void v04(void* a);                // +0x04
    virtual int  v08();                       // +0x08
    virtual int  v0c();                       // +0x0c
    virtual void v10(int a, int b);           // +0x10
    virtual void v14(float a);                // +0x14
    virtual void v18(float a);                // +0x18
    virtual void v1c(float a);                // +0x1c
virtual void v20();
virtual void v24();
virtual void v28();
    virtual void v2c(float a);                // +0x2c
    virtual void v30(float a);                // +0x30
virtual void v34();
virtual void v38();
    virtual void v3c(int a);                  // +0x3c
};
}
}
namespace rw {
namespace movie {
class IAudioRenderer
{ public:
    virtual void v00();                       // +0x00
    virtual void v04(int a, int b, int c);    // +0x04
    virtual int  v08();                       // +0x08
    virtual void v0c();
    virtual void v10(int a, int b);           // +0x10
    virtual void v14(void* a);                // +0x14
    virtual void v18(void* a);                // +0x18
    virtual void v1c(void* a);                // +0x1c
virtual void v20();
virtual void v24();
virtual void v28();
    virtual void v2c();                       // +0x2c (no args in the audio iface)
    virtual void v30();                       // +0x30
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
    virtual void v64();
    virtual void v68(void* a);                // +0x68
};
}
}
namespace rw {
namespace movie {
class MovieDecoder_s00fc_b210
{ public:
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
    void SetVideoStream(Stream_s00fc_b210* s);                // 0x00fc91e0
    void SetAudioStream(Stream_s00fc_b210* s, uint32_t id);   // 0x00fc91f0
    void VideoDecodeThreadFcn(Stream_s00fc_b210* s);          // 0x00fc9210
    void PrepareDecoder(int* a, int b, int c, int d, int e, int f,
                        int g, int h, int i);      // 0x00fc9310
    void Shutdown();                               // 0x00fc96d0
    void Destroy();                                // 0x00fc97a0
};
}
}
namespace rw {
namespace movie {
class MovieRenderer_s00fc_b210
{ public:
    ICoreAllocator_s00fc_b210* mAllocator;       // +0x00
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

    MovieRenderer_s00fc_b210* Ctor(ICoreAllocator_s00fc_b210* allocator);      // 0x00fcbc70
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
}
}
namespace rw {
namespace movie {
void FUN_00fcbce0(MovieRenderer_s00fc_b210* self, void* fn);        // set video callback
}
}
namespace rw {
namespace movie {
void FUN_00fcc010(MovieRenderer_s00fc_b210* self, void* a, void* b); // render step
}
}
namespace rw {
namespace movie {
struct IMovieTimerCallback
{
    virtual void  v0();          // +0x00
    virtual void  v1();          // +0x04
    virtual void  v2();          // +0x08
    virtual float v3();          // +0x0c  (returns elapsed seconds)
};
}
}
namespace rw {
namespace movie {
class MovieTimer_s00fc_b210
{ public:
    ICoreAllocator_s00fc_b210* mAllocator;   // +0x00
    Stopwatch*      mStopwatch;   // +0x04
    IMovieTimerCallback* mCallback; // +0x08

    MovieTimer_s00fc_b210* Ctor(ICoreAllocator_s00fc_b210* allocator);   // 0x00fcc0b0
    void  Destroy();                               // 0x00fcc100
    void  Update();                                // 0x00fcc150
    void  Sync();                                  // 0x00fcc180
    float Elapsed();                               // 0x00fcc190
};
}
}
namespace rw {
namespace movie {
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
}
}
namespace rw {
namespace movie {
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
}
}
namespace rw {
namespace movie {
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
}
}
namespace rw {
namespace movie {
struct AVIPCMWaveFormat             // 0x10 bytes
{
    uint16_t wFormatTag;            // +0x00
    uint16_t nChannels;             // +0x02
    uint32_t nSamplesPerSec;        // +0x04
    uint32_t nAvgBytesPerSec;       // +0x08
    uint16_t nBlockAlign;           // +0x0c
    uint16_t wBitsPerSample;        // +0x0e
};
}
}
namespace rw {
namespace movie {
char FUN_00fc80f0(int* cursor, int* remaining, uint32_t* outId);
}
}
namespace rw {
namespace movie {
char FUN_00fc8120(int* cursor, int* remaining, uint32_t* outChunk);
}
}
namespace rw {
namespace movie {
char FUN_00fc8150(int* cursor, int* remaining, void* out);
}
}
namespace rw {
namespace movie {
char FUN_00fc8180(int* cursor, int* remaining, void* out);
}
}
namespace rw {
namespace movie {
char FUN_00fc81b0(int* cursor, int* remaining, void* out);
}
}
namespace rw {
namespace movie {
extern uint32_t g_fcc_hdrl;   // 0x015b17c0
}
}
namespace rw {
namespace movie {
extern uint32_t g_fcc_RIFF;   // 0x015b179c
}
}
namespace rw {
namespace movie {
extern uint32_t g_fcc_LIST;   // 0x015b17a4
}
}
namespace rw {
namespace movie {
extern uint32_t g_fcc_avih;   // 0x015b17ac
}
}
namespace rw {
namespace movie {
extern uint32_t g_fcc_strh;   // 0x015b17b4
}
}
namespace rw {
namespace movie {
extern uint32_t g_fcc_strf;   // 0x015b17b8
}
}
namespace rw {
namespace movie {
extern uint32_t g_fcc_vids;   // 0x015b17cc
}
}
namespace rw {
namespace movie {
extern uint32_t g_fcc_auds;   // 0x015b17d0
}
}
namespace rw {
namespace movie {
class MoviePlayer_s00fc_b210
{ public:
    ICoreAllocator_s00fc_b210* mAllocator;                 // +0x00
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
    MovieDecoder_s00fc_b210* mMovieDecoder;                // +0x10c
    MovieRenderer_s00fc_b210* mMovieRenderer;              // +0x110
    MovieTimer_s00fc_b210* mMovieTimer;                    // +0x114
    void* mMovieStreamBuffer;                   // +0x118
    Stream_s00fc_b210* mVideoStream;                       // +0x11c
    Stream_s00fc_b210* mDataStream;                        // +0x120
    Stream_s00fc_b210* mNullStream;                        // +0x124
    uint32_t mAudioStreamRequestId;             // +0x128
    void* mAudioStreamBuffer;                   // +0x12c
    Stream_s00fc_b210* mAudioStream;                       // +0x130
    Stream_s00fc_b210* mAudioNullStream;                   // +0x134
    void* mSubtitleStreamBuffer;                // +0x138
    Stream_s00fc_b210* mSubtitleStream;                    // +0x13c
    Stream_s00fc_b210* mSubtitleNullStream;                // +0x140
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
}
}
namespace rw {
namespace movie {
void FUN_00fc9050(void* eventLogger);
}
}
namespace rw {
namespace movie {
void FUN_00fc8650(void* eventLogger);
}
}
namespace rw {
namespace movie {
void FUN_00fc94f0(int index, void* outA, void* outB);
}
}
namespace rw {
namespace movie {
void FUN_00c2e4e0(void* p);            // UTFWin element teardown
}
}
namespace rw {
namespace movie {
void FUN_00fc9650();                   // video-render callback
}
}
namespace rw {
namespace movie {
namespace EA {
namespace Thread {
void ThreadSleep(void* tag);           // 0x00921df0
}
}
}
}
// ---- items of slice s00fcb210 end

// @ 0x00fca720
rw::movie::MoviePlayer* rw::movie::MoviePlayer::Ctor(rw::movie::ICoreAllocator* allocator)
{
    mStreamingContext.Ctor();
    mAllocator = allocator;
    mStreamerParseFunc = 0;
    mStreamerVideoFilterFunc = 0;
    mStreamerAudioFilterFunc = 0;
    mDataCallbackFunc = 0;
    mStreamerVideoCallbackFunc = 0;
    mStreamerAudioCallbackFunc = 0;
    mStreamerSubtitleCallbackFunc = 0;
    mStreamerDataPreloadCallbackFunc = 0;
    mStreamerVideoPreloadCallbackFunc = 0;
    mStreamerAudioPreloadCallbackFunc = 0;
    mStreamerSubtitlePreloadCallbackFunc = 0;
    mStreamerDataFilterFunc = 0;
    mStreamerSubtitleFilterFunc = 0;
    mStreamerSubtitleFilterContext = 0;
    mVideoFilePath = 0;
    mAudioFilePath = 0;
    mSubtitleFilePath = 0;
    mPreloadVideoFile = 0;
    mPreloadAudioFile = 0;
    mPreloadSubtitleFile = 0;
    mNumberAudioTracks = 0;
    mSelectedAudioTrack = 0;
    mVolume = 1.0f;
    mVideoPositionX = 0.0f;
    mVideoPositionY = 0.0f;
    mVideoPositionZ = 0.0f;
    mVideoScaleX = 1.0f;
    mVideoScaleY = 1.0f;
    mWidth = 0;
    mHeight = 0;
    mTotalFrames = 0;
    mCurrentVideoRenderable = 0;
    mVideoDecodeThreadProcessor = 2;
    mNumVideoRenderables = 8;
    mPlaybackFps = 0.0f;
    mVideoRenderingDelay = 0.0f;
    mLastRenderedFrame = -1;
    mPreviousGoalFrame = -1;
    mGoalFrame = 0;
    mAudioStreamRequestId = 0;
    mMovieStreamBuffer = 0;
    mVideoStream = 0;
    mDataStream = 0;
    mNullStream = 0;
    mAudioStream = 0;
    mAudioStreamBuffer = 0;
    mAudioNullStream = 0;
    mSubtitleStream = 0;
    mSubtitleStreamBuffer = 0;
    mSubtitleNullStream = 0;
    mSubtitlePreloadBuffer = 0;
    mAudioPreloadBuffer = 0;
    mVideoPreloadBuffer = 0;
    mField154 = 0;
    mEventLogger = 0;

    if (allocator != 0) {
        rw::movie::MovieDecoder* dec = (rw::movie::MovieDecoder*)mAllocator->Alloc(0x4c, "MovieDecoder object", 1, 4, 0);
        mMovieDecoder = dec;
        mMovieDecoder = dec ? dec->Ctor(mAllocator) : 0;

        rw::movie::MovieRenderer* ren = (rw::movie::MovieRenderer*)mAllocator->Alloc(0x50, "MovieRenderer object", 1, 4, 0);
        mMovieRenderer = ren;
        mMovieRenderer = ren ? ren->Ctor(mAllocator) : 0;

        rw::movie::MovieTimer* tm = (rw::movie::MovieTimer*)mAllocator->Alloc(0xc, "MovieTimer object", 1, 4, 0);
        mMovieTimer = tm;
        mMovieTimer = tm ? tm->Ctor(mAllocator) : 0;
        mState = 0;
    }
    else {
        mState = 7;
    }
    mIsAVIFile = 0;
    mLastGettable = 0;
    mAvgDeltaGettable = 0;
    return this;
}

// @ 0x00fca9b0
void rw::movie::MoviePlayer::SetDataCallback(void* fn)
{
    if (mState <= 1)
        mDataCallbackFunc = fn;
}

// @ 0x00fca9d0
void rw::movie::MoviePlayer::SetVideoFilter(void* fn)
{
    if (mState <= 1)
        mStreamerVideoCallbackFunc = fn;
}

// @ 0x00fca9f0
void rw::movie::MoviePlayer::SetAudioCallback(void* fn)
{
    if (mState <= 1)
        mStreamerSubtitleCallbackFunc = fn;
}

// @ 0x00fcaa10
void rw::movie::MoviePlayer::SetStreamerSubtitleFilter(void* fn)
{
    if (mState <= 1) {
        mStreamerDataPreloadCallbackFunc = fn;
        ((rw::movie::MovieTimer*)mMovieTimer)->SetCallback(fn);
    }
}

// @ 0x00fcaa40
void rw::movie::MoviePlayer::SetAudioStreamFilter(void* fn)
{
    if (mState <= 1) {
        mStreamerAudioPreloadCallbackFunc = fn;
        mMovieDecoder->SetCallback(fn);
    }
}

// @ 0x00fcaa70
int rw::movie::MoviePlayer::ConfigureVideo(const char* path, unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    switch (mState) {
    case 0: break;
    default: return -1;
    case 1: return -1;
    case 2: return -1;
    case 3: return -1;
    case 4: return -1;
    case 5: return -1;
    case 6: return -1;
    case 7: return -1;
    }
    if (FUN_011ea7d0(path)) {
    mVideoFilePathSize = a;
    mVideoFilePathOffset = b;
    mVideoFilePath = (char*)path;
    if ((c | d) != 0)
        mVideoDataSizeHi = d;
    else {
        unsigned long long sz = FUN_011ea850(path);
        c = (unsigned int)sz;
        mVideoDataSizeHi = (unsigned int)(sz >> 32);
    }
    mVideoDataSize = c;
    const char* e = path;
    while (*e != 0)
        ++e;
    if (e - path > 3 && e[-4] == '.' && e[-3] == 'a' && e[-2] == 'v' && e[-1] == 'i') {
        mIsAVIFile = 1;
        return 0;
    }
    mIsAVIFile = 0;
    return 0;
    }
    mVideoFilePath = 0;
    mVideoFilePathSize = 0;
    mVideoFilePathOffset = 0;
    mVideoDataSize = 0;
    mVideoDataSizeHi = 0;
    return -1;
}

// @ 0x00fcab70
void rw::movie::MoviePlayer::OpenFiles(unsigned int videoBufferSize, int flags)
{
    if (mState != 0)
        return;

    if (mAudioFilePath != 0) {
        mAudioStreamBuffer = mAllocator->Alloc(0x20000, "Audio Stream Buffer", 1, 0x10, 0);
        mAudioStream = (void*)FUN_011e7910(2, mAudioStreamBuffer, 0x20000, 0, 0, 0);
        ((rw::core::filesys::Stream*)mAudioStream)->SetOffset(0);
        int off = ((rw::core::filesys::Stream*)mAudioStream)->GetOffset();
        ((rw::core::filesys::Stream*)mAudioStream)->SetFilter(off, mStreamerAudioFilterFunc, 0);
        mAudioNullStream = ((rw::core::filesys::Stream*)mAudioStream)->CreateReadRequest(0);
        int off2 = ((rw::core::filesys::Stream*)mAudioStream)->GetOffset();
        ((rw::core::filesys::Stream*)mAudioStream)->SetFilter(off2, (void*)0x00b1fbf0, 0);

        rw::movie::StreamContext* sc = &mAudioStreamingContext;
        sc->mStreamEnd = 0;
        sc->mFileLength = mAudioFilePathSize;
        sc->mBytesSoFar = 0;

        if (!mPreloadAudioFile) {
            mAudioStreamRequestId = ((rw::core::filesys::Stream*)mAudioStream)->QueueFile(mAudioFilePath, 0, 0,
                                                                      mStreamerParseFunc, sc);
        }
        else {
            rw::core::filesys::AsyncOp_s00fc_a300 op;
            op.OpenPath(mAudioFilePath, 0, 0, 0, 0);
            op.Run((void*)0x01491d80);
            int f = op.Wait();
            mAudioPreloadBuffer = mAllocator->Alloc(mAudioFilePathSize, "Audio Preload Buffer", 1, 4, 0);
            op.Read(f, mAudioPreloadBuffer, 0, 0, mAudioFilePathSize, 0, 0, 0);
            op.Run((void*)0x01491d80);
            op.Finish(f, 0);
            op.Run((void*)0x01491d80);
            mAudioStreamRequestId = ((rw::core::filesys::Stream*)mAudioStream)->QueueMem(mAudioPreloadBuffer,
                                                                      mAudioFilePathSize,
                                                                      mStreamerParseFunc, sc);
            op.Delete();
        }
    }

    if (mVideoFilePath != 0) {
        mMovieStreamBuffer = mAllocator->Alloc(videoBufferSize, "Video Stream Buffer", 1, 0x10, 0);
        mVideoStream = (void*)FUN_011e7910(2, mMovieStreamBuffer, videoBufferSize, 0, 0, 0);
        ((rw::core::filesys::Stream*)mVideoStream)->SetOffset(flags);
        int off = ((rw::core::filesys::Stream*)mVideoStream)->GetOffset();
        ((rw::core::filesys::Stream*)mVideoStream)->SetFilter(off, mStreamerVideoFilterFunc, 0);

        if (mAudioStreamRequestId == 0 && mStreamerAudioFilterFunc != 0) {
            mAudioStream = ((rw::core::filesys::Stream*)mVideoStream)->CreateReadRequest(0);
            int o = ((rw::core::filesys::Stream*)mVideoStream)->GetOffset();
            ((rw::core::filesys::Stream*)mVideoStream)->SetFilter(o, mStreamerAudioFilterFunc, 0);
        }
        if (mDataCallbackFunc != 0 && mStreamerDataFilterFunc != 0) {
            mDataStream = ((rw::core::filesys::Stream*)mVideoStream)->CreateReadRequest(0);
            int o = ((rw::core::filesys::Stream*)mVideoStream)->GetOffset();
            ((rw::core::filesys::Stream*)mVideoStream)->SetFilter(o, mStreamerDataFilterFunc, 0);
        }
        mNullStream = ((rw::core::filesys::Stream*)mVideoStream)->CreateReadRequest(0);
        int o2 = ((rw::core::filesys::Stream*)mVideoStream)->GetOffset();
        ((rw::core::filesys::Stream*)mVideoStream)->SetFilter(o2, (void*)0x00b1fbf0, 0);

        rw::movie::StreamContext* vc = &mVideoStreamingContext;
        vc->mStreamEnd = 0;
        vc->mFileLength = mVideoFilePathSize;
        vc->mBytesSoFar = 0;

        if (!mPreloadVideoFile) {
            if (mAudioStreamRequestId == 0) {
                mAudioStreamRequestId = ((rw::core::filesys::Stream*)mVideoStream)->QueueFile(mVideoFilePath,
                                                                          mVideoFilePathOffset,
                                                                          0, mStreamerParseFunc, vc);
            }
            else {
                ((rw::core::filesys::Stream*)mVideoStream)->QueueFile(mVideoFilePath, mVideoFilePathOffset, 0,
                                                   mStreamerParseFunc, vc);
            }
        }
        else {
            rw::core::filesys::AsyncOp_s00fc_a300 op;
            op.OpenPath(mVideoFilePath, 0, 0, 0, 0);
            op.Run((void*)0x01491d80);
            int f = op.Wait();
            mVideoPreloadBuffer = mAllocator->Alloc(mVideoFilePathSize, "Video Preload Buffer", 1, 4, 0);
            op.Read(f, mVideoPreloadBuffer, 0, 0, mVideoFilePathSize, 0, 0, 0);
            op.Run((void*)0x01491d80);
            op.Finish(f, 0);
            op.Run((void*)0x01491d80);
            if (mAudioStreamRequestId == 0) {
                mAudioStreamRequestId = ((rw::core::filesys::Stream*)mVideoStream)->QueueMem(mVideoPreloadBuffer,
                                                                          mVideoFilePathSize,
                                                                          mStreamerParseFunc, vc);
                op.Delete();
            }
            else {
                ((rw::core::filesys::Stream*)mVideoStream)->QueueMem(mVideoPreloadBuffer, mVideoFilePathSize,
                                                  mStreamerParseFunc, vc);
                op.Delete();
            }
        }
    }

    if (mSubtitleFilePath != 0) {
        mSubtitleStreamBuffer = mAllocator->Alloc(0x4000, "Subtitle Stream Buffer", 1, 0x10, 0);
        mSubtitleStream = (void*)FUN_011e7910(2, mSubtitleStreamBuffer, 0x4000, 0, 0, 0);
        ((rw::core::filesys::Stream*)mSubtitleStream)->SetOffset(0);
        int off = ((rw::core::filesys::Stream*)mSubtitleStream)->GetOffset();
        ((rw::core::filesys::Stream*)mSubtitleStream)->SetFilter(off, mStreamerSubtitleFilterFunc,
                                              mStreamerSubtitleFilterContext);
        mSubtitleNullStream = ((rw::core::filesys::Stream*)mSubtitleStream)->CreateReadRequest(0);
        int o = ((rw::core::filesys::Stream*)mSubtitleStream)->GetOffset();
        ((rw::core::filesys::Stream*)mSubtitleStream)->SetFilter(o, (void*)0x00b1fbf0, 0);

        rw::movie::StreamContext* sc = &mSubtitleStreamingContext;
        sc->mStreamEnd = 0;
        sc->mFileLength = mSubtitleFilePathSize;
        sc->mBytesSoFar = 0;

        if (mPreloadSubtitleFile) {
            rw::core::filesys::AsyncOp_s00fc_a300 op;
            op.OpenPath(mSubtitleFilePath, 0, 0, 0, 0);
            op.Run((void*)0x01491d80);
            int f = op.Wait();
            mSubtitlePreloadBuffer = mAllocator->Alloc(mSubtitleFilePathSize,
                                                       "Subtitle Preload Buffer", 1, 4, 0);
            op.Read(f, mSubtitlePreloadBuffer, 0, 0, mSubtitleFilePathSize, 0, 0, 0);
            op.Run((void*)0x01491d80);
            op.Finish(f, 0);
            op.Run((void*)0x01491d80);
            ((rw::core::filesys::Stream*)mSubtitleStream)->QueueMem(mSubtitlePreloadBuffer, mSubtitleFilePathSize,
                                                 mStreamerParseFunc, sc);
            op.Delete();
            mState = 1;
            return;
        }
        ((rw::core::filesys::Stream*)mSubtitleStream)->QueueFile(mSubtitleFilePath, 0, 0, mStreamerParseFunc, sc);
    }
    mState = 1;
}

// @ 0x00fcb150
void rw::movie::MoviePlayer::SetVideoPositionX(float v)
{
    if (mState <= 4) {
        mVideoPositionX = v;
        mMovieRenderer->SetVideoPositionX(v);
    }
}

// @ 0x00fcb180
void rw::movie::MoviePlayer::SetVideoPositionY(float v)
{
    if (mState <= 4) {
        mVideoPositionY = v;
        mMovieRenderer->SetVideoPositionY(v);
    }
}

// @ 0x00fcb1b0
void rw::movie::MoviePlayer::SetVideoScaleX(float v)
{
    if (mState <= 4) {
        mVideoScaleX = v;
        mMovieRenderer->SetVideoScaleX(v);
    }
}

// @ 0x00fcb1e0
void rw::movie::MoviePlayer::SetVideoScaleY(float v)
{
    if (mState <= 4) {
        mVideoScaleY = v;
        mMovieRenderer->SetVideoScaleY(v);
    }
}

// @ 0x00fcb210
bool rw::movie::MoviePlayer_s00fc_b210::ParseAVIHeaders(int flag)
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

    if (rw::movie::g_fcc_hdrl != 0)
    {
        do
        {
            char ok = rw::movie::FUN_00fc80f0(&local_48, &remaining, &local_40);
            if (ok == 0)
                return false;

            if (local_40 == rw::movie::g_fcc_RIFF || local_40 == rw::movie::g_fcc_LIST)
            {
                ok = rw::movie::FUN_00fc8120(&local_48, &remaining, (uint32_t*)&local_44);
                if (ok == 0)
                    return false;
            }
            else if (local_40 == rw::movie::g_fcc_avih)
            {
                ok = rw::movie::FUN_00fc8150(&local_48, &remaining, &mAVIHeader);
                if (ok == 0)
                    return false;
            }
            else if (local_40 == rw::movie::g_fcc_strh)
            {
                ok = rw::movie::FUN_00fc8150(&local_48, &remaining, local_38);
                if (ok == 0)
                    return false;
                if (local_38[0] == rw::movie::g_fcc_vids)
                {
                    uint32_t* src = local_38;
                    uint32_t* dst = (uint32_t*)&mAVIVidsStreamHeader;
                    for (int i = 14; i != 0; --i)
                        *dst++ = *src++;
                }
                else if (local_38[0] == rw::movie::g_fcc_auds)
                {
                    uint32_t* src = local_38;
                    uint32_t* dst = (uint32_t*)&mAVIAudsStreamHeader;
                    for (int i = 14; i != 0; --i)
                        *dst++ = *src++;
                }
            }
            else if (local_40 == rw::movie::g_fcc_strf)
            {
                if (local_38[0] == rw::movie::g_fcc_vids)
                    ok = rw::movie::FUN_00fc8180(&local_48, &remaining, &mAVIBitmapInfoHeader);
                else if (local_38[0] == rw::movie::g_fcc_auds)
                    ok = rw::movie::FUN_00fc81b0(&local_48, &remaining, &mAVIPCMWaveFormat);
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
        } while (local_44 != (int)rw::movie::g_fcc_hdrl);
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
void rw::movie::MoviePlayer_s00fc_b210::Decode()
{
    if (mState - 2 > 2u)
        return;

    float elapsed = mMovieTimer->Elapsed();
    int goal = (int)((mVideoRenderingDelay + elapsed) * (mPlaybackFps * 0.001f));
    mGoalFrame = (uint32_t)goal;
    rw::movie::FUN_00fc94f0(goal, &mCurrentVideoRenderable, (char*)this + 0xbc);

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
void rw::movie::MoviePlayer_s00fc_b210::Render()
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

    rw::movie::FUN_00fcc010(mMovieRenderer, &mCurrentVideoRenderable, (char*)this + 0xbc);
    EA::Thread::ThreadSleep((void*)0x01491d7c);
    if (mAudioStream != 0)
        mAudioStream->GetChunk();
}

// @ 0x00fcb6e0
void rw::movie::MoviePlayer_s00fc_b210::Tick()
{
    if (mState - 2 <= 2u)
    {
        mMovieRenderer->PauseVideo();
        mMovieTimer->Sync();
    }
}

// @ 0x00fcb710
void rw::movie::MoviePlayer_s00fc_b210::TickReverse()
{
    if (mState - 2 <= 2u)
    {
        mMovieRenderer->ResumeVideo();
        mMovieTimer->Update();
    }
}

// @ 0x00fcb740
void rw::movie::MoviePlayer_s00fc_b210::Shutdown()
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
void rw::movie::MoviePlayer_s00fc_b210::Destroy()
{
    if (mEventLogger != 0)
    {
        rw::movie::FUN_00fc8650((void*)mEventLogger);
        rw::movie::FUN_00fc9050((void*)mEventLogger);
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
        rw::movie::FUN_00c2e4e0(mMovieRenderer);
        mAllocator->Free(mMovieRenderer, 0);
        mMovieRenderer = 0;
    }
    if (mMovieDecoder != 0)
    {
        mMovieDecoder->Destroy();
        mAllocator->Free(mMovieDecoder, 0);
        mMovieDecoder = 0;
    }
    rw::movie::FUN_00c2e4e0((char*)this + 0xbc);
}

// @ 0x00fcb920
bool rw::movie::MoviePlayer_s00fc_b210::PreparePlayer(int flag)
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
            rw::movie::FUN_00fcbce0(mMovieRenderer, (void*)mRenderCallbackCtx);
            mMovieDecoder->SetVideoStream(mVideoStream);
        }
    }

    if (mAudioStream != 0)
    {
        ++mNumberAudioTracks;
        mMovieDecoder->SetAudioFilter((void*)mAudioFilterCtx);
        mMovieDecoder->SetAudioStream(mAudioStream, mAudioStreamRequestId);
        mMovieRenderer->Configure((void*)rw::movie::FUN_00fc9650, (void*)mMovieDecoder);
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

// @ 0x00fcbc70
rw::movie::MovieRenderer_s00fc_b210* rw::movie::MovieRenderer_s00fc_b210::Ctor(ICoreAllocator_s00fc_b210* allocator)
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
void rw::movie::MovieRenderer_s00fc_b210::Configure(void* fn, void* ctx)
{
    if (mVideoState == 0)
    {
        mAudioFormatA = (int32_t)fn;
        mAudioFormatB = (int32_t)ctx;
    }
}

// @ 0x00fcbd10
void rw::movie::MovieRenderer_s00fc_b210::ConfigureAudio(void* fn, void* ctx)
{
    if (mState == 0)
    {
        mSubtitleFormatA = (int32_t)fn;
        mSubtitleFormatB = (int32_t)ctx;
    }
}

// @ 0x00fcbd30
void rw::movie::MovieRenderer_s00fc_b210::Prepare(void* a, void* b, void* c, void* d)
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
            rw::movie::IVideoRenderer* vr = (rw::movie::IVideoRenderer*)mVideoRenderer;
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
            ((rw::movie::IVideoRenderer*)mTimer)->v04((void*)mAllocator);
        mDelay = mVideoDelay - mAudioDelay;
        mState = 1;
    }
}

// @ 0x00fcbe60
float rw::movie::MovieRenderer_s00fc_b210::GetVideoDelay()
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
void rw::movie::MovieRenderer_s00fc_b210::PlayVideo()
{
    if (mVideoState - 1 == 0)
    {
        IAudioRenderer* audio = mAudioRenderer;
        if (audio != 0)
        {
            typedef void (__thiscall* PlayFunction)(IAudioRenderer*);
            PlayFunction* table = *(PlayFunction**)audio;
            _ReadWriteBarrier();
            table[8](audio);
        }
        mVideoState = 2;
    }
}

// @ 0x00fcbec0
void rw::movie::MovieRenderer_s00fc_b210::PauseVideo()
{
    if (mVideoState - 1 <= 1u)
    {
        rw::movie::IAudioRenderer* ar = mAudioRenderer;
        if (ar != 0)
            ar->v24();
        mVideoState = 3;
    }
}

// @ 0x00fcbef0
void rw::movie::MovieRenderer_s00fc_b210::ResumeVideo()
{
    if (mVideoState == 3)
    {
        if (mAudioRenderer != 0)
            mAudioRenderer->v28();
        mVideoState = 2;
    }
}

// @ 0x00fcbf10
void rw::movie::MovieRenderer_s00fc_b210::SetVideoPositionX(float v)
{
    if (mState == 0)
    {
        mPosX = v;
    }
    else if (mState - 1 <= 1u)
    {
        mPosX = v;
        if (mVideoRenderer != 0)
            ((rw::movie::IVideoRenderer*)mVideoRenderer)->v14(v);
    }
}

// @ 0x00fcbf50
void rw::movie::MovieRenderer_s00fc_b210::SetVideoPositionY(float v)
{
    if (mState == 0)
    {
        mPosY = v;
    }
    else if (mState - 1 <= 1u)
    {
        mPosY = v;
        if (mVideoRenderer != 0)
            ((rw::movie::IVideoRenderer*)mVideoRenderer)->v18(v);
    }
}

// @ 0x00fcbf90
void rw::movie::MovieRenderer_s00fc_b210::SetVideoScaleX(float v)
{
    if (mState == 0)
    {
        mScaleX = v;
    }
    else if (mState - 1 <= 1u)
    {
        mScaleX = v;
        if (mVideoRenderer != 0)
            ((rw::movie::IVideoRenderer*)mVideoRenderer)->v2c(v);
    }
}

// @ 0x00fcbfd0
void rw::movie::MovieRenderer_s00fc_b210::SetVideoScaleY(float v)
{
    if (mState == 0)
    {
        mScaleY = v;
    }
    else if (mState - 1 <= 1u)
    {
        mScaleY = v;
        if (mVideoRenderer != 0)
            ((rw::movie::IVideoRenderer*)mVideoRenderer)->v30(v);
    }
}

// @ 0x00fcc010
void rw::movie::MovieRenderer_s00fc_b210::SetRenderCallback(void* a, void* b)
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
        ((rw::movie::IVideoRenderer*)mVideoRenderer)->v3c((int)a);
    if (mTimer != 0)
        ((rw::movie::IAudioRenderer*)mTimer)->v68(b);
}

// @ 0x00fcc060
void rw::movie::MovieRenderer_s00fc_b210::Stop()
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
