// Slice s00fca300: RenderWare movie encoder (rw::movie::MovieEncoder_Avi) and player
// (rw::movie::MoviePlayer) methods plus the small "property setter" methods.
// MSVC 2008 SP1 x86 (VS2008 SP1 cl 15.00).
#include "types.h"
#include <intrin.h>
#pragma intrinsic(__rdtsc)

namespace rw { namespace core { namespace filesys {
struct Stream; struct AsyncOp;
}}}
namespace rw { namespace core { namespace timer {
struct Stopwatch
{
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

namespace rw {
namespace movie {

struct BufferedWriter
{
    void*   pc0; void* pc1; void* pbuf; int32_t sz, pos, rpos, rsz, rpos2;
    uint8_t* GetBuffer();          // 0x0093b6c0
    void SetBuffer(void*, int);    // 0x00fc8390
    void Write32(uint32_t);        // 0x00fc8580
    void WriteFill(int, int);      // 0x00fc8500
    void WriteData(const void*, int);  // 0x00fc84b0
    void FlushRemote(int a, int b);   // 0x00fc8450
    void Flush();                  // 0x00fc83b0
};

struct IEncoder
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();   // +0x10
    virtual void v5(); virtual void v6();
    virtual void SetOutputBufferCallback(void* fn, void* ctx);   // +0x1c
};

struct IAudioEncoder : IEncoder
{
};

struct IVideoEncoder : IEncoder
{
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual float GetFrameRate();   // +0x38
};


struct AviIndexEntry
{
    uint32_t dwChunkId;   // +0x00
    uint32_t dwFlags;     // +0x04
    uint32_t dwOffset;    // +0x08
    uint32_t dwSize;      // +0x0c
};

struct AviIndexBlock
{
    AviIndexEntry* data;   // +0x00
    uint32_t count;        // +0x04
    AviIndexBlock* next;   // +0x08
};

struct MovieEncoder_Avi
{
    void* vftable;                        // +0x00
    void* mAllocator;                     // +0x04
    void* mEncodingErrorCallback;         // +0x08
    void* mEncodingErrorCallbackData;     // +0x0c
    uint32_t mBufferSize;                 // +0x10
    BufferedWriter mBufferedWriter;       // +0x14
    IAudioEncoder* mAudioEncoder;         // +0x34
    IVideoEncoder* mVideoEncoder;         // +0x38
    uint32_t mMicrosecondsPerFrame;       // +0x3c
    uint32_t mMicrosecondsAudioBuffered;  // +0x40
    uint32_t mTotalFrames;                // +0x44
    uint32_t mTotalAudioSamples;          // +0x48
    AviIndexBlock mFirstIndexBlock;       // +0x4c
    void* mActiveAVIIndexBlock;           // +0x58
    uint32_t mNumAVIIndexEntries;         // +0x5c
    uint32_t mNumAVIIndexEntriesPerBlock; // +0x60
    uint32_t mRiffChunkSize;              // +0x64
    uint32_t mNextChunkOffset;            // +0x68
    Stopwatch* mStopwatch;                // +0x6c
    float mTotalElapsedTime;              // +0x70

    void Shutdown();
    void EndEncoding();   // 0x00fca360
    void AllocateBuffer();
    void Init(void* allocator);
    void SetAudioEncoder(IAudioEncoder* e);
    void SetVideoEncoder(IVideoEncoder* e);
    uint32_t WriteAVIHeaders();           // 0x00fc9a60
    void AddAVIIndexEntry(const int* entry);   // 0x00fca160
    void FreeAVIIndexEntries();           // 0x00fca250
};

void EncodeAudioData(const void* data, int size, MovieEncoder_Avi* self);   // 0x00fca460
void EncodeVideoData(const void* data, int size, int type, MovieEncoder_Avi* self);   // 0x00fca510
    void EndEncoding();   // 0x00fca360

// ---------------------------------------------------------------------------
// rw::movie::MovieRenderer: only the float setters used here.
// ---------------------------------------------------------------------------
struct ICoreAllocator
{
    virtual void v0();                                                   // +0x00
    virtual void* Alloc(unsigned int size, const char* name, int a,
                        int b, int c);                                   // +0x04
    virtual void v2(); virtual void v3();
    virtual void Free(void* p, int a);                                   // +0x10
};

struct StreamContext
{
    void* mStreamEnd;       // +0x00
    int32_t mFileLength;    // +0x04
    int32_t mBytesSoFar;    // +0x08
};

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

struct MovieRenderer
{
    MovieRenderer* Ctor(ICoreAllocator* a);   // 0x00fcbc70
    void SetVideoPositionX(float v);   // 0x00fcbf10
    void SetVideoPositionY(float v);   // 0x00fcbf50
    void SetVideoScaleX(float v);      // 0x00fcbf90
    void SetVideoScaleY(float v);      // 0x00fcbfd0
};

struct MovieTimer
{
    MovieTimer* Ctor(ICoreAllocator* a);   // 0x00fcc0b0
    void SetCallback(void* fn);            // 0x00fcc140
};

struct MovieDecoder
{
    MovieDecoder* Ctor(ICoreAllocator* a);   // 0x00fc90e0
    void SetCallback(void* fn);              // 0x00fc91d0
};

struct MoviePlayer
{
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

} // namespace movie
} // namespace rw

using namespace rw::movie;
using namespace rw::core::filesys;

extern uint16_t g_aviVideoFourccHi;   // 0x015b17e0
extern uint16_t g_aviAudioFourccHi;   // 0x015b17e8
extern uint32_t g_aviIndexFlagsA;     // 0x01491818
extern uint32_t g_aviIndexFlagsB;     // 0x01491808
extern uint32_t g_aviIdx1Fcc;         // 0x015b17d8 ("idx1")
void* __fastcall StopwatchCtor(void* mem, int unused, int units, int a);   // 0x011e82d0
unsigned long long GetStopwatchCycle();   // 0x011e8080

extern "C" {
    void* FUN_011e7910(int a, void* b, int c, int d, int e, int f);
    char  FUN_011ea7d0(const char* path);
    unsigned long long FUN_011ea850(const char* path);
    int   FUN_011e8770();
    void  FUN_011e8820();
    void  FUN_011e89e0();
    void  FUN_011e8a40();
    void  FUN_011e8530();
}

namespace rw { namespace core { namespace filesys {
struct Stream
{
    void SetOffset(int off);                               // 0x011e6cd0
    int  GetOffset();                                      // 0x011e69c0
    void SetFilter(int off, void* fn, void* ctx);          // 0x011e7950
    void* CreateReadRequest(void* a);                      // 0x011e79f0
    int  QueueMem(void* buf, int size, void* fn, void* ctx); // 0x011e6aa0
    int  QueueFile(const char* path, int off, int hi, void* fn, void* ctx);  // 0x011e69d0
};
struct AsyncOp
{
    AsyncOp();
    int  OpenPath(const char* path, int, int, int, int);   // 0x011e8a40
    void Run(void* a);                                     // 0x011e8740
    int  Wait();                                           // 0x011e8770
    void Read(int f, void* buf, int a, int b, int size, int c, int d, int e);   // 0x011e8820
    void Finish(int f, int a);                             // 0x011e89e0
    void Delete();                                         // 0x011e8530
};
}}}

// ---------------------------------------------------------------------------
// 0x00fcb150 / 0x00fcb180 / 0x00fcb1b0 / 0x00fcb1e0
// MoviePlayer float property setters: gate on mState < 5, store the float,
// and forward to the renderer.  The x87 push/stpop accounts for the
// "movss + fld + push ecx + fstp [esp]" shape of the original.
// ---------------------------------------------------------------------------
// @ 0x00fcb150
void MoviePlayer::SetVideoPositionX(float v)
{
    if (mState <= 4) {
        mVideoPositionX = v;
        mMovieRenderer->SetVideoPositionX(v);
    }
}

// @ 0x00fcb180
void MoviePlayer::SetVideoPositionY(float v)
{
    if (mState <= 4) {
        mVideoPositionY = v;
        mMovieRenderer->SetVideoPositionY(v);
    }
}

// @ 0x00fcb1b0
void MoviePlayer::SetVideoScaleX(float v)
{
    if (mState <= 4) {
        mVideoScaleX = v;
        mMovieRenderer->SetVideoScaleX(v);
    }
}

// @ 0x00fcb1e0
void MoviePlayer::SetVideoScaleY(float v)
{
    if (mState <= 4) {
        mVideoScaleY = v;
        mMovieRenderer->SetVideoScaleY(v);
    }
}

// ---------------------------------------------------------------------------
// 0x00fca9b0 / 0x00fca9d0 / 0x00fca9f0 / 0x00fcaa10 / 0x00fcaa40
// State-gated property setters (mState < 2).
// ---------------------------------------------------------------------------
// @ 0x00fca9b0
void MoviePlayer::SetDataCallback(void* fn)
{
    if (mState <= 1)
        mDataCallbackFunc = fn;
}

// @ 0x00fca9d0
void MoviePlayer::SetVideoFilter(void* fn)
{
    if (mState <= 1)
        mStreamerVideoCallbackFunc = fn;
}

// @ 0x00fca9f0
void MoviePlayer::SetAudioCallback(void* fn)
{
    if (mState <= 1)
        mStreamerSubtitleCallbackFunc = fn;
}

// @ 0x00fcaa10
void MoviePlayer::SetStreamerSubtitleFilter(void* fn)
{
    if (mState <= 1) {
        mStreamerDataPreloadCallbackFunc = fn;
        ((MovieTimer*)mMovieTimer)->SetCallback(fn);
    }
}

// @ 0x00fcaa40
void MoviePlayer::SetAudioStreamFilter(void* fn)
{
    if (mState <= 1) {
        mStreamerAudioPreloadCallbackFunc = fn;
        mMovieDecoder->SetCallback(fn);
    }
}

// ---------------------------------------------------------------------------
// 0x00fca300  MovieEncoder_Avi::Shutdown
// ---------------------------------------------------------------------------
// @ 0x00fca300
void MovieEncoder_Avi::Shutdown()
{
    if (mStopwatch != 0) {
        (*(void (__thiscall**)(void*, int))*(void**)mStopwatch)(mStopwatch, 0);
        void* alloc = mAllocator;
        Stopwatch* sw = mStopwatch;
        (*(void (__thiscall**)(void*, Stopwatch*, int))((uint8_t*)(*(void**)alloc) + 0xc))(alloc, sw, 0);
        mStopwatch = 0;
    }
    uint8_t* buf = mBufferedWriter.GetBuffer();
    if (buf != 0) {
        if (mAllocator != 0) {
            (*(void (__thiscall**)(void*, uint8_t*, int))((uint8_t*)(*(void**)mAllocator) + 0xc))(mAllocator, buf, 0);
            return;
        }
        if (mEncodingErrorCallback != 0) {
            ((void (__cdecl*)(const char*, void*))mEncodingErrorCallback)
                ("MovieEncoder_Avi: Allocator is NULL - unable to free compression buffer.",
                 mEncodingErrorCallbackData);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00fca6a0 / 0x00fca6c0  encoder hookup
// ---------------------------------------------------------------------------
// @ 0x00fca6a0
void MovieEncoder_Avi::SetAudioEncoder(IAudioEncoder* e)
{
    mAudioEncoder = e;
    if (e != 0) {
        e->SetOutputBufferCallback((void*)&EncodeAudioData, this);
    }
}

// @ 0x00fca6c0
void MovieEncoder_Avi::SetVideoEncoder(IVideoEncoder* e)
{
    mVideoEncoder = e;
    if (mVideoEncoder != 0) {
        float us = 1000000.0f;
        float fps = mVideoEncoder->GetFrameRate();
        mMicrosecondsPerFrame = (uint32_t)(us / fps);
        mVideoEncoder->SetOutputBufferCallback((void*)&EncodeVideoData, this);
    }
}

// ---------------------------------------------------------------------------
// 0x00fca460 / 0x00fca510  encode one chunk + index the write
// ---------------------------------------------------------------------------
// @ 0x00fca460
void EncodeAudioData(const void* data, int size, MovieEncoder_Avi* self)
{
    if (self == 0)
        return;
    BufferedWriter& w = self->mBufferedWriter;
    w.Write32(((uint32_t)g_aviAudioFourccHi << 16) | 0x3130);
    w.Write32((uint32_t)size);
    w.WriteData(data, size);
    int pad = ((size + 1) & ~1) - size;
    w.WriteFill(0xff, pad);
    int entry[4];
    entry[0] = (int)(((uint32_t)g_aviAudioFourccHi << 16) | 0x3130);
    entry[1] = (int)(g_aviIndexFlagsA | g_aviIndexFlagsB);
    entry[2] = (int)self->mNextChunkOffset;
    entry[3] = size;
    self->AddAVIIndexEntry(entry);
    self->mNextChunkOffset += pad + size + 8;
    self->mRiffChunkSize += pad + size + 8;
}

// @ 0x00fca510
void EncodeVideoData(const void* data, int size, int type, MovieEncoder_Avi* self)
{
    if (self == 0)
        return;
    BufferedWriter& w = self->mBufferedWriter;
    w.Write32(((uint32_t)g_aviVideoFourccHi << 16) | 0x3030);
    w.Write32((uint32_t)size);
    w.WriteData(data, size);
    int pad = ((size + 1) & ~1) - size;
    w.WriteFill(0xff, pad);
    int entry[4];
    entry[0] = (int)(((uint32_t)g_aviVideoFourccHi << 16) | 0x3030);
    entry[1] = (int)g_aviIndexFlagsB;
    entry[2] = (int)self->mNextChunkOffset;
    entry[3] = size;
    self->AddAVIIndexEntry(entry);
    self->mNextChunkOffset += pad + size + 8;
    self->mRiffChunkSize += pad + size + 8;
}

// ---------------------------------------------------------------------------
// 0x00fca5c0  MovieEncoder_Avi::AllocateBuffer
// ---------------------------------------------------------------------------
// @ 0x00fca5c0
void MovieEncoder_Avi::AllocateBuffer()
{
    uint8_t* buf = mBufferedWriter.GetBuffer();
    if (buf != 0) {
        if (mAllocator != 0) {
            (*(void (__thiscall**)(void*, uint8_t*, int))((uint8_t*)(*(void**)mAllocator) + 0xc))(mAllocator, buf, 0);
        }
        else if (mEncodingErrorCallback != 0) {
            ((void (__cdecl*)(const char*, void*))mEncodingErrorCallback)
                ("MovieEncoder_Avi: Allocator is NULL - unable to free compression buffer.",
                 mEncodingErrorCallbackData);
        }
    }
    if (mAllocator != 0) {
        void* p = (*(void* (__thiscall**)(void*, uint32_t, const char*, int))
                   ((uint8_t*)(*(void**)mAllocator) + 8))(mAllocator, mBufferSize, "AVI Compression Buffer", 1);
        mBufferedWriter.SetBuffer(p, mBufferSize);
        return;
    }
    if (mEncodingErrorCallback != 0) {
        ((void (__cdecl*)(const char*, void*))mEncodingErrorCallback)
            ("MovieEncoder_Avi: Allocator is NULL - unable to allocate compression buffer.",
             mEncodingErrorCallbackData);
    }
}

// ---------------------------------------------------------------------------
// 0x00fca640  MovieEncoder_Avi::Init
// ---------------------------------------------------------------------------
// @ 0x00fca640
void MovieEncoder_Avi::Init(void* allocator)
{
    mAllocator = allocator;
    AllocateBuffer();
    mNumAVIIndexEntriesPerBlock = 60000000u / mMicrosecondsPerFrame;
    Stopwatch* sw = (Stopwatch*)(*(void* (__thiscall**)(void*, int, const char*, int, int, int))
                ((uint8_t*)(*(void**)mAllocator) + 4))
               (mAllocator, 0x28, "Stopwatch", 1, 4, 0);
    mStopwatch = sw;
    mStopwatch = sw ? sw->Ctor(3, 0) : 0;
}

// ---------------------------------------------------------------------------
// 0x00fca360  MovieEncoder_Avi::EndEncoding
// ---------------------------------------------------------------------------
// @ 0x00fca360
void MovieEncoder_Avi::EndEncoding()
{
    Stopwatch* sw = mStopwatch;
    unsigned long long now;
    if (sw->mUnits == 1)
        now = __rdtsc();
    else
        now = GetStopwatchCycle();
    sw->mStartHi = (int)(now >> 32);
    sw->mStartLo = (int)now;

    if (mAudioEncoder != 0)
        mAudioEncoder->v4();
    if (mVideoEncoder != 0) {
        mVideoEncoder->v4();
        mBufferedWriter.Write32(g_aviIdx1Fcc);
        mBufferedWriter.Write32(mNumAVIIndexEntries * 16);

        AviIndexBlock* b = &mFirstIndexBlock;
        while (b != 0) {
            if (b->data != 0) {
                for (uint32_t i = 0; i < b->count; ++i) {
                    mBufferedWriter.Write32(b->data[i].dwChunkId);
                    mBufferedWriter.Write32(b->data[i].dwFlags);
                    mBufferedWriter.Write32(b->data[i].dwOffset);
                    mBufferedWriter.Write32(b->data[i].dwSize);
                }
            }
            b = b->next;
        }
        mRiffChunkSize += mNumAVIIndexEntries * 16 + 8;
        mBufferedWriter.FlushRemote(0, 1);
        WriteAVIHeaders();
        mBufferedWriter.Flush();
        FreeAVIIndexEntries();
    }
    mStopwatch->Stop();
}

// ---------------------------------------------------------------------------
// 0x00fca720  rw::movie::MoviePlayer::MoviePlayer
// ---------------------------------------------------------------------------
// @ 0x00fca720
MoviePlayer* MoviePlayer::Ctor(ICoreAllocator* allocator)
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
        MovieDecoder* dec = (MovieDecoder*)mAllocator->Alloc(0x4c, "MovieDecoder object", 1, 4, 0);
        mMovieDecoder = dec;
        mMovieDecoder = dec ? dec->Ctor(mAllocator) : 0;

        MovieRenderer* ren = (MovieRenderer*)mAllocator->Alloc(0x50, "MovieRenderer object", 1, 4, 0);
        mMovieRenderer = ren;
        mMovieRenderer = ren ? ren->Ctor(mAllocator) : 0;

        MovieTimer* tm = (MovieTimer*)mAllocator->Alloc(0xc, "MovieTimer object", 1, 4, 0);
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

// ---------------------------------------------------------------------------
// 0x00fcaa70  rw::movie::MoviePlayer::ConfigureVideo
// ---------------------------------------------------------------------------
// @ 0x00fcaa70
int MoviePlayer::ConfigureVideo(const char* path, unsigned int a, unsigned int b,
                                unsigned int c, unsigned int d)
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

// ---------------------------------------------------------------------------
// 0x00fcab70  rw::movie::MoviePlayer::OpenFiles
// ---------------------------------------------------------------------------
// @ 0x00fcab70
void MoviePlayer::OpenFiles(unsigned int videoBufferSize, int flags)
{
    if (mState != 0)
        return;

    if (mAudioFilePath != 0) {
        mAudioStreamBuffer = mAllocator->Alloc(0x20000, "Audio Stream Buffer", 1, 0x10, 0);
        mAudioStream = (void*)FUN_011e7910(2, mAudioStreamBuffer, 0x20000, 0, 0, 0);
        ((Stream*)mAudioStream)->SetOffset(0);
        int off = ((Stream*)mAudioStream)->GetOffset();
        ((Stream*)mAudioStream)->SetFilter(off, mStreamerAudioFilterFunc, 0);
        mAudioNullStream = ((Stream*)mAudioStream)->CreateReadRequest(0);
        int off2 = ((Stream*)mAudioStream)->GetOffset();
        ((Stream*)mAudioStream)->SetFilter(off2, (void*)0x00b1fbf0, 0);

        StreamContext* sc = &mAudioStreamingContext;
        sc->mStreamEnd = 0;
        sc->mFileLength = mAudioFilePathSize;
        sc->mBytesSoFar = 0;

        if (!mPreloadAudioFile) {
            mAudioStreamRequestId = ((Stream*)mAudioStream)->QueueFile(mAudioFilePath, 0, 0,
                                                                      mStreamerParseFunc, sc);
        }
        else {
            AsyncOp op;
            op.OpenPath(mAudioFilePath, 0, 0, 0, 0);
            op.Run((void*)0x01491d80);
            int f = op.Wait();
            mAudioPreloadBuffer = mAllocator->Alloc(mAudioFilePathSize, "Audio Preload Buffer", 1, 4, 0);
            op.Read(f, mAudioPreloadBuffer, 0, 0, mAudioFilePathSize, 0, 0, 0);
            op.Run((void*)0x01491d80);
            op.Finish(f, 0);
            op.Run((void*)0x01491d80);
            mAudioStreamRequestId = ((Stream*)mAudioStream)->QueueMem(mAudioPreloadBuffer,
                                                                      mAudioFilePathSize,
                                                                      mStreamerParseFunc, sc);
            op.Delete();
        }
    }

    if (mVideoFilePath != 0) {
        mMovieStreamBuffer = mAllocator->Alloc(videoBufferSize, "Video Stream Buffer", 1, 0x10, 0);
        mVideoStream = (void*)FUN_011e7910(2, mMovieStreamBuffer, videoBufferSize, 0, 0, 0);
        ((Stream*)mVideoStream)->SetOffset(flags);
        int off = ((Stream*)mVideoStream)->GetOffset();
        ((Stream*)mVideoStream)->SetFilter(off, mStreamerVideoFilterFunc, 0);

        if (mAudioStreamRequestId == 0 && mStreamerAudioFilterFunc != 0) {
            mAudioStream = ((Stream*)mVideoStream)->CreateReadRequest(0);
            int o = ((Stream*)mVideoStream)->GetOffset();
            ((Stream*)mVideoStream)->SetFilter(o, mStreamerAudioFilterFunc, 0);
        }
        if (mDataCallbackFunc != 0 && mStreamerDataFilterFunc != 0) {
            mDataStream = ((Stream*)mVideoStream)->CreateReadRequest(0);
            int o = ((Stream*)mVideoStream)->GetOffset();
            ((Stream*)mVideoStream)->SetFilter(o, mStreamerDataFilterFunc, 0);
        }
        mNullStream = ((Stream*)mVideoStream)->CreateReadRequest(0);
        int o2 = ((Stream*)mVideoStream)->GetOffset();
        ((Stream*)mVideoStream)->SetFilter(o2, (void*)0x00b1fbf0, 0);

        StreamContext* vc = &mVideoStreamingContext;
        vc->mStreamEnd = 0;
        vc->mFileLength = mVideoFilePathSize;
        vc->mBytesSoFar = 0;

        if (!mPreloadVideoFile) {
            if (mAudioStreamRequestId == 0) {
                mAudioStreamRequestId = ((Stream*)mVideoStream)->QueueFile(mVideoFilePath,
                                                                          mVideoFilePathOffset,
                                                                          0, mStreamerParseFunc, vc);
            }
            else {
                ((Stream*)mVideoStream)->QueueFile(mVideoFilePath, mVideoFilePathOffset, 0,
                                                   mStreamerParseFunc, vc);
            }
        }
        else {
            AsyncOp op;
            op.OpenPath(mVideoFilePath, 0, 0, 0, 0);
            op.Run((void*)0x01491d80);
            int f = op.Wait();
            mVideoPreloadBuffer = mAllocator->Alloc(mVideoFilePathSize, "Video Preload Buffer", 1, 4, 0);
            op.Read(f, mVideoPreloadBuffer, 0, 0, mVideoFilePathSize, 0, 0, 0);
            op.Run((void*)0x01491d80);
            op.Finish(f, 0);
            op.Run((void*)0x01491d80);
            if (mAudioStreamRequestId == 0) {
                mAudioStreamRequestId = ((Stream*)mVideoStream)->QueueMem(mVideoPreloadBuffer,
                                                                          mVideoFilePathSize,
                                                                          mStreamerParseFunc, vc);
                op.Delete();
            }
            else {
                ((Stream*)mVideoStream)->QueueMem(mVideoPreloadBuffer, mVideoFilePathSize,
                                                  mStreamerParseFunc, vc);
                op.Delete();
            }
        }
    }

    if (mSubtitleFilePath != 0) {
        mSubtitleStreamBuffer = mAllocator->Alloc(0x4000, "Subtitle Stream Buffer", 1, 0x10, 0);
        mSubtitleStream = (void*)FUN_011e7910(2, mSubtitleStreamBuffer, 0x4000, 0, 0, 0);
        ((Stream*)mSubtitleStream)->SetOffset(0);
        int off = ((Stream*)mSubtitleStream)->GetOffset();
        ((Stream*)mSubtitleStream)->SetFilter(off, mStreamerSubtitleFilterFunc,
                                              mStreamerSubtitleFilterContext);
        mSubtitleNullStream = ((Stream*)mSubtitleStream)->CreateReadRequest(0);
        int o = ((Stream*)mSubtitleStream)->GetOffset();
        ((Stream*)mSubtitleStream)->SetFilter(o, (void*)0x00b1fbf0, 0);

        StreamContext* sc = &mSubtitleStreamingContext;
        sc->mStreamEnd = 0;
        sc->mFileLength = mSubtitleFilePathSize;
        sc->mBytesSoFar = 0;

        if (mPreloadSubtitleFile) {
            AsyncOp op;
            op.OpenPath(mSubtitleFilePath, 0, 0, 0, 0);
            op.Run((void*)0x01491d80);
            int f = op.Wait();
            mSubtitlePreloadBuffer = mAllocator->Alloc(mSubtitleFilePathSize,
                                                       "Subtitle Preload Buffer", 1, 4, 0);
            op.Read(f, mSubtitlePreloadBuffer, 0, 0, mSubtitleFilePathSize, 0, 0, 0);
            op.Run((void*)0x01491d80);
            op.Finish(f, 0);
            op.Run((void*)0x01491d80);
            ((Stream*)mSubtitleStream)->QueueMem(mSubtitlePreloadBuffer, mSubtitleFilePathSize,
                                                 mStreamerParseFunc, sc);
            op.Delete();
            mState = 1;
            return;
        }
        ((Stream*)mSubtitleStream)->QueueFile(mSubtitleFilePath, 0, 0, mStreamerParseFunc, sc);
    }
    mState = 1;
}
