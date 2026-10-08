// Slice s00fc9310: rw::movie::MovieEncoder_Avi::WriteAVIHeaders (RenderWare movie AVI writer).
// Writes the RIFF/AVI header: hdrl LIST (avih main header, video strl: strh + strf BITMAPINFOHEADER,
// optional audio strl: strh + strf WAVEFORMAT), a JUNK pad to a 2048-byte boundary, then the movi LIST header.
#include "types.h"

namespace rw {
namespace movie {

// 0x00fc8580 / 0x00fc8550 / 0x00fc8500: BufferedWriter helpers (PDB: BufferedWriter, size 0x20).
struct BufferedWriter
{
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
};

// Encoder interfaces: only the vtable slots used here are named; the rest are placeholders.
struct IVideoEncoder
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual uint32_t GetWidth();        // +0x28
    virtual void v11();
    virtual uint32_t GetHeight();       // +0x30
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual uint32_t GetQuality();      // +0x48
    virtual uint32_t GetPlanes();       // +0x4c
    virtual uint32_t GetBitCount();     // +0x50
    virtual uint32_t GetBufferSize();   // +0x54
    virtual uint32_t GetSlot58();       // +0x58 (unused here)
    virtual uint32_t GetSlot5C();       // +0x5c
};

struct IAudioEncoder
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual uint32_t GetSlot28();       // +0x28
    virtual void v11();
    virtual uint32_t GetSlot30();       // +0x30
    virtual uint32_t GetSlot34();       // +0x34
    virtual uint32_t GetSlot38();       // +0x38
    virtual uint32_t GetSlot3C();       // +0x3c
    virtual uint32_t GetSlot40();       // +0x40
    virtual uint32_t GetSlot44();       // +0x44
};

struct MovieEncoder_Avi
{
    void* vftable;                      // +0x00
    void* mAllocator;                   // +0x04
    void* mEncodingErrorCallback;       // +0x08
    void* mEncodingErrorCallbackData;   // +0x0c
    uint32_t mBufferSize;               // +0x10
    BufferedWriter mBufferedWriter;     // +0x14
    IAudioEncoder* mAudioEncoder;       // +0x34
    IVideoEncoder* mVideoEncoder;       // +0x38
    uint32_t mMicrosecondsPerFrame;     // +0x3c
    uint32_t mMicrosecondsAudioBuffered; // +0x40
    uint32_t mTotalFrames;              // +0x44
    uint32_t mTotalAudioSamples;        // +0x48
    uint32_t mFirstIndexBlock[3];       // +0x4c
    void* mActiveAVIIndexBlock;         // +0x58
    uint32_t mNumAVIIndexEntries;       // +0x5c
    uint32_t mNumAVIIndexEntriesPerBlock; // +0x60
    uint32_t mRiffChunkSize;            // +0x64
    uint32_t mNextChunkOffset;          // +0x68
    void* mStopwatch;                   // +0x6c
    float mTotalElapsedTime;            // +0x70

    uint32_t WriteAVIHeaders();         // 0x00fc9a60
};

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

// @ 0x00fc9a60  rw::movie::MovieEncoder_Avi::WriteAVIHeaders
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
