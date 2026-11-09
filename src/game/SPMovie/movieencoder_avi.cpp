// src/game/SPMovie/movieencoder_avi.cpp -- migrated from slice(s) s00fca300, s00fc9310 by tools/migrate/rewrite.py
// Object file: SPMovie/movieencoder_avi.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#ifndef NULL
#define NULL 0
#endif

// unnamed retail callees and globals (address in the comment)
extern const uint32_t FCC_RIFF[16]; // 0x015b179c
extern uint32_t g_aviFlagA;   // 0x01491800
extern uint32_t g_aviFlagB;   // 0x014917f0
extern uint32_t g_aviFlagC;   // 0x014917f8 (audio present)
extern uint16_t g_waveFormatTag; // 0x01491838
#include <intrin.h>
#pragma intrinsic(__rdtsc)

// ---- items of slice s00fc9310 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace core {
namespace timer {
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
}
}
}
using rw::core::timer::Stopwatch;
unsigned long long GetStopwatchCycle();   // 0x011e8080
namespace rw {
namespace movie {
struct ICoreAllocator
{
    virtual void  v0();                                                          // +0x00
    virtual void* Alloc(unsigned int size, const char* name, int a, int b, int c);   // +0x04
    virtual void* AllocBlock(unsigned int size, const char* name, int flag);      // +0x08
    virtual void  Free(void* p, int a);                                          // +0x0c
};
}
}
namespace rw {
namespace movie {
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
}
}
namespace rw {
namespace movie {
class IEncoder
{ public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
};
}
}
namespace rw {
namespace movie {
class IVideoEncoder : public IEncoder
{ public:
virtual void v8();
virtual void v9();
    virtual uint32_t GetWidth();        // +0x28
    virtual void v11();                 // +0x2c
    virtual uint32_t GetHeight();       // +0x30
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual uint32_t GetQuality();      // +0x48
    virtual uint32_t GetPlanes();       // +0x4c
    virtual uint32_t GetBitCount();     // +0x50
    virtual uint32_t GetBufferSize();   // +0x54
    virtual void AddFrame(void* frame); // +0x58
    virtual void v22();                 // +0x5c
};
}
}
namespace rw {
namespace movie {
class IAudioEncoder : public IEncoder
{ public:
virtual void v8();
virtual void v9();
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
}
}
namespace rw {
namespace movie {
struct AviIndexEntry
{
    uint32_t dwChunkId;    // +0x00
    uint32_t dwFlags;      // +0x04
    uint32_t dwOffset;     // +0x08
    uint32_t dwSize;       // +0x0c
};
}
}
namespace rw {
namespace movie {
struct AviIndexBlock
{
    AviIndexEntry* data;   // +0x00
    uint32_t count;        // +0x04
    AviIndexBlock* next;   // +0x08
};
}
}
namespace rw {
namespace movie {
struct AudioSamples
{
    void*    mBuffer;      // +0x00
    uint32_t mSampleRate;  // +0x04
    uint32_t mPad08;       // +0x08
    uint32_t mSize;        // +0x0c
};
}
}
namespace rw {
namespace movie {
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
}
}
extern const uint32_t FCC_RIFF[16]; // 0x015b179c
extern uint32_t g_aviFlagA;   // 0x01491800
extern uint32_t g_aviFlagB;   // 0x014917f0
extern uint32_t g_aviFlagC;   // 0x014917f8 (audio present)
extern uint16_t g_waveFormatTag; // 0x01491838
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
// ---- items of slice s00fc9310 end

// ---- items of slice s00fca300 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint16_t g_aviVideoFourccHi;   // 0x015b17e0
extern uint16_t g_aviAudioFourccHi;   // 0x015b17e8
extern uint32_t g_aviIndexFlagsA;     // 0x01491818
extern uint32_t g_aviIndexFlagsB;     // 0x01491808
extern uint32_t g_aviIdx1Fcc;         // 0x015b17d8 ("idx1")
namespace rw {
namespace core {
namespace timer {
class Stopwatch_s00fc_a300
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
    Stopwatch_s00fc_a300* Ctor(int units, int a);   // 0x011e82d0
    void Stop();                         // 0x011e83a0
};
}
}
}
using rw::core::timer::Stopwatch_s00fc_a300;
namespace rw {
namespace movie {
class BufferedWriter_s00fc_a300
{ public:
    void*   pc0; void* pc1; void* pbuf; int32_t sz, pos, rpos, rsz, rpos2;
    uint8_t* GetBuffer();          // 0x0093b6c0
    void SetBuffer(void*, int);    // 0x00fc8390
    void Write32(uint32_t);        // 0x00fc8580
    void WriteFill(int, int);      // 0x00fc8500
    void WriteData(const void*, int);  // 0x00fc84b0
    void FlushRemote(int a, int b);   // 0x00fc8450
    void Flush();                  // 0x00fc83b0
};
}
}
namespace rw {
namespace movie {
class IEncoder_s00fc_a300
{ public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual void v4();   // +0x10
virtual void v5();
virtual void v6();
    virtual void SetOutputBufferCallback(void* fn, void* ctx);   // +0x1c
};
}
}
namespace rw {
namespace movie {
class IAudioEncoder_s00fc_a300 : public IEncoder_s00fc_a300 { public:
};
}
}
namespace rw {
namespace movie {
class IVideoEncoder_s00fc_a300 : public IEncoder_s00fc_a300 { public:
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual float GetFrameRate();   // +0x38
};
}
}
namespace rw {
namespace movie {
class MovieEncoder_Avi_s00fc_a300
{ public:
    void* vftable;                        // +0x00
    void* mAllocator;                     // +0x04
    void* mEncodingErrorCallback;         // +0x08
    void* mEncodingErrorCallbackData;     // +0x0c
    uint32_t mBufferSize;                 // +0x10
    BufferedWriter_s00fc_a300 mBufferedWriter;       // +0x14
    IAudioEncoder_s00fc_a300* mAudioEncoder;         // +0x34
    IVideoEncoder_s00fc_a300* mVideoEncoder;         // +0x38
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
    Stopwatch_s00fc_a300* mStopwatch;                // +0x6c
    float mTotalElapsedTime;              // +0x70

    void Shutdown();  // 0x00fca300 (rw::movie::MovieEncoder_Avi::Shutdown)
    void EndEncoding();   // 0x00fca360
    void AllocateBuffer();  // 0x00fca5c0 (rw::movie::MovieEncoder_Avi::AllocateBuffer)
    void Init(void* allocator);  // 0x00fca640 (rw::movie::MovieEncoder_Avi::Init)
    void SetAudioEncoder(IAudioEncoder_s00fc_a300* e);  // 0x00fca6a0 (rw::movie::MovieEncoder_Avi::SetAudioEncoder)
    void SetVideoEncoder(IVideoEncoder_s00fc_a300* e);  // 0x00fca6c0 (rw::movie::MovieEncoder_Avi::SetVideoEncoder)
    uint32_t WriteAVIHeaders();           // 0x00fc9a60
    void AddAVIIndexEntry(const int* entry);   // 0x00fca160
    void FreeAVIIndexEntries();           // 0x00fca250
};
}
}
namespace rw {
namespace movie {
void EncodeAudioData(const void* data, int size, MovieEncoder_Avi_s00fc_a300* self);   // 0x00fca460
}
}
namespace rw {
namespace movie {
void EncodeVideoData(const void* data, int size, int type, MovieEncoder_Avi_s00fc_a300* self);   // 0x00fca510
}
}
namespace rw {
namespace movie {
    void EndEncoding();   // 0x00fca360
}
}
// ---- items of slice s00fca300 end

// @ 0x00fc9950
uint32_t rw::movie::MovieEncoder_Avi::NextDataExpected()
{
    uint32_t type = 1;
    if (mAudioEncoder != 0 && mMicrosecondsAudioBuffered < mMicrosecondsPerFrame)
        return type;
    return 2;
}

// @ 0x00fc9970
void rw::movie::MovieEncoder_Avi::AddAudioSamples(rw::movie::AudioSamples* samples)
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
void rw::movie::MovieEncoder_Avi::AddVideoFrame(void* frame)
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
uint32_t rw::movie::MovieEncoder_Avi::WriteAVIHeaders()
{
    rw::movie::BufferedWriter* w = &mBufferedWriter;

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
        rw::movie::IVideoEncoder* v = mVideoEncoder;
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
            rw::movie::IAudioEncoder* a = mAudioEncoder;
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
void rw::movie::MovieEncoder_Avi::BeginEncoding()
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
void rw::movie::MovieEncoder_Avi::AddAVIIndexEntry(const rw::movie::AviIndexEntry* entry)
{
    if (mActiveAVIIndexBlock == 0)
        return;

    if (mActiveAVIIndexBlock->count == mNumAVIIndexEntriesPerBlock) {
        if (mAllocator != 0) {
            mActiveAVIIndexBlock->next = (rw::movie::AviIndexBlock*)
                mAllocator->AllocBlock(0xc, "AVI Index Block", 1);
            rw::movie::AviIndexBlock* block = mActiveAVIIndexBlock->next;
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
            mActiveAVIIndexBlock->data = (rw::movie::AviIndexEntry*)
                mAllocator->AllocBlock(mNumAVIIndexEntriesPerBlock << 4, "AVI Index Buffer", 1);
        } else if (mEncodingErrorCallback != 0) {
            ((void (__cdecl*)(const char*, void*))mEncodingErrorCallback)
                ("MovieEncoder_Avi: Allocator is NULL - unable to allocate index buffer.",
                 mEncodingErrorCallbackData);
        }
    }

    if (mActiveAVIIndexBlock->data == 0)
        return;

    rw::movie::AviIndexEntry* e = mActiveAVIIndexBlock->data + mActiveAVIIndexBlock->count;
    *e = *entry;
    ++mActiveAVIIndexBlock->count;
    ++mNumAVIIndexEntries;
}

// @ 0x00fca250
void rw::movie::MovieEncoder_Avi::FreeAVIIndexEntries()
{
    if (mAllocator != 0) {
        rw::movie::AviIndexBlock* first = &mFirstIndexBlock;
        mActiveAVIIndexBlock = first;
        while (mActiveAVIIndexBlock != 0) {
            if (mActiveAVIIndexBlock->data != 0)
                mAllocator->Free(mActiveAVIIndexBlock->data, 0);

            rw::movie::AviIndexBlock* block = mActiveAVIIndexBlock;
            rw::movie::AviIndexBlock* next = block->next;
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
rw::movie::MovieEncoder_Avi* rw::movie::MovieEncoder_Avi::Ctor(uint32_t bufferSize)
{
    vftable = (void*)0x1491b68;
    mBufferedWriter.Init();

    rw::movie::AviIndexBlock* first = &mFirstIndexBlock;
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

// @ 0x00fca300
void rw::movie::MovieEncoder_Avi_s00fc_a300::Shutdown()
{
    if (mStopwatch != 0) {
        (*(void (__thiscall**)(void*, int))*(void**)mStopwatch)(mStopwatch, 0);
        void* alloc = mAllocator;
        Stopwatch_s00fc_a300* sw = mStopwatch;
        (*(void (__thiscall**)(void*, Stopwatch_s00fc_a300*, int))((uint8_t*)(*(void**)alloc) + 0xc))(alloc, sw, 0);
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

// @ 0x00fca360
void rw::movie::MovieEncoder_Avi_s00fc_a300::EndEncoding()
{
    Stopwatch_s00fc_a300* sw = mStopwatch;
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

        rw::movie::AviIndexBlock* b = &mFirstIndexBlock;
        while (b != 0) {
            if (b->data != 0) {
                for (uint32_t i = 0; i < b->count; ++i) {
                    char* base = (char*)(i * 16);
                    mBufferedWriter.Write32(*(uint32_t*)(base + (uint32_t)b->data + 0));
                    mBufferedWriter.Write32(*(uint32_t*)(base + (uint32_t)b->data + 4));
                    mBufferedWriter.Write32(*(uint32_t*)(base + (uint32_t)b->data + 8));
                    mBufferedWriter.Write32(*(uint32_t*)(base + (uint32_t)b->data + 12));
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

// @ 0x00fca460
void rw::movie::EncodeAudioData(const void* data, int size, rw::movie::MovieEncoder_Avi_s00fc_a300* self)
{
    if (self == 0)
        return;
    rw::movie::BufferedWriter_s00fc_a300& w = self->mBufferedWriter;
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
void rw::movie::EncodeVideoData(const void* data, int size, int type, rw::movie::MovieEncoder_Avi_s00fc_a300* self)
{
    if (self == 0)
        return;
    rw::movie::BufferedWriter_s00fc_a300& w = self->mBufferedWriter;
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

// @ 0x00fca5c0
void rw::movie::MovieEncoder_Avi_s00fc_a300::AllocateBuffer()
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

// @ 0x00fca640
void rw::movie::MovieEncoder_Avi_s00fc_a300::Init(void* allocator)
{
    mAllocator = allocator;
    AllocateBuffer();
    mNumAVIIndexEntriesPerBlock = 60000000u / mMicrosecondsPerFrame;
    Stopwatch_s00fc_a300* sw = (Stopwatch_s00fc_a300*)(*(void* (__thiscall**)(void*, int, const char*, int, int, int))
                ((uint8_t*)(*(void**)mAllocator) + 4))
               (mAllocator, 0x28, "Stopwatch", 1, 4, 0);
    mStopwatch = sw;
    mStopwatch = sw ? sw->Ctor(3, 0) : 0;
}

// @ 0x00fca6a0
void rw::movie::MovieEncoder_Avi_s00fc_a300::SetAudioEncoder(rw::movie::IAudioEncoder_s00fc_a300* e)
{
    mAudioEncoder = e;
    if (e != 0) {
        e->SetOutputBufferCallback((void*)&rw::movie::EncodeAudioData, this);
    }
}

// @ 0x00fca6c0
void rw::movie::MovieEncoder_Avi_s00fc_a300::SetVideoEncoder(rw::movie::IVideoEncoder_s00fc_a300* e)
{
    mVideoEncoder = e;
    if (mVideoEncoder != 0) {
        float us = 1000000.0f;
        float fps = mVideoEncoder->GetFrameRate();
        mMicrosecondsPerFrame = (uint32_t)(us / fps);
        mVideoEncoder->SetOutputBufferCallback((void*)&rw::movie::EncodeVideoData, this);
    }
}
