// rw::audio::core AIFF stream player (RenderWare 4 audio core, VC .NET 2003, /GL+/LTCG).
// The original was LTCG-linked, so most of these functions cannot be byte-exact from a single
// object; the leaf functions (no calls) are matched in manifest.txt and the rest are complete,
// behaviour-equivalent source (nonmatching.txt).  32-bit only (the code shuffles 32-bit pointers).
// Flags: /vc71 /O2 /MD /Gy /TP
#include "types.h"

namespace rw { namespace audio { namespace core {

struct AiffPlayer;

// RenderWare's float->int scaling helpers round (cvtss2si), not truncate (cvttss2si).
// A couple of instructions in an otherwise-C++ function, as docs/matching.md permits.
static inline int RwFloat2Int(float f)
{
    int r;
    __asm { cvtss2si eax, f }
    __asm { mov r, eax }
    return r;
}

// ---------------------------------------------------------------- filesys Stream (PDB candidates)
struct Stream {
    void* GetChunk();                 // 0x011e6b50
    void  ReleaseChunk(void* chunk);  // 0x011e7c70  (rw::core::filesys::Stream::ReleaseChunk)
};

// ---------------------------------------------------------------- audio core System singleton
struct System {
    void* Alloc(unsigned size, const char* name, int align, int flags);  // 0x0112c820
    void  Free(void* p, int flags);                                       // 0x0112c850
};
extern System* g_pSystem;   // 0x016e61a8

// ---------------------------------------------------------------- decoder interface (3 codecs)
struct Decoder {
    virtual int Decode(int offset, int count, int bytes);  // slot 0
    virtual int Fill(void** channels, int bytes);          // slot 1
    virtual int Init(void* header);                        // slot 2
    virtual int Stop(int immediate);                       // slot 3
};
struct RawDecoder {                       // constructors, return 'this'
    void* FUN_01140510();                 // 0x01140510 (type 1)
    void* FUN_01140440();                 // 0x01140440 (type 2)
    void* FUN_01140390();                 // 0x01140390 (type 3)
};

// ---------------------------------------------------------------- free-function callees
typedef void (*EventFn)(void*, AiffPlayer*);
void*  FUN_011402c0(unsigned size);                    // 0x011402c0  operator new
void   FUN_01132fe0(void* p);                          // 0x01132fe0
void   FUN_0113fca0(void* p);                          // 0x0113fca0
int    FUN_0113f1c0(int index);                        // 0x0113f1c0
int    FUN_0113f1d0(EventFn fn, int a2, void* a3, void* slot, int size);  // 0x0113f1d0
int    FUN_0113f250(int handle, void* a, void* b, void* c);              // 0x0113f250
int    FUN_0113fba0(int handle, int value);            // 0x0113fba0
int    FUN_0113fdd0(int handle, int index, int value); // 0x0113fdd0
int    FUN_0113ff00(int handle, int value);            // 0x0113ff00
int    FUN_0113f9b0(int handle);                       // 0x0113f9b0
int    FUN_0113f750(int handle);                       // 0x0113f750
char*  FUN_01140110(char* data, unsigned tag, int len);// 0x01140110
float  FUN_01140290(const void* extended80);           // 0x01140290
int    SNDPKTPLAY_submit(int handle, void* packet);    // 0x0113f5c0
void   FUN_0112fa50(AiffPlayer* self, int a, int b, int c, int d);  // 0x0112fa50
void   FUN_0112fb50(AiffPlayer* self);                 // 0x0112fb50

// ---------------------------------------------------------------- sub-objects of the player
struct AiffFormat {                 // pointed to by +0x14
    float  f0;                      // +0x00
    float  f1;                      // +0x04  (*4096)
    float  f2;                      // +0x08  (*127)
    float* p3;                      // +0x0c  (points at a float)
    float  f4;                      // +0x10
    float  f5;                      // +0x14
};

struct AiffStreamState {            // +0x18, initialised by FUN_01132fe0
    uint8_t  f0, f1, f2, f3, f4, f5;   // +0x18..+0x1d
    uint16_t w6;                    // +0x1e
    uint16_t w8;                    // +0x20
    uint16_t wa;                    // +0x22
    uint16_t wc;                    // +0x24
    uint16_t we;                    // +0x26
};

struct AiffPuller {                 // +0x28, initialised by FUN_0113fca0 (0x64 bytes)
    uint16_t w0;                    // +0x00
    uint8_t  b2, b3, b4, b5, b6;    // +0x02..+0x06
    uint16_t gain[6];               // +0x08..+0x13
    uint32_t f14[6];                // +0x14..+0x2b
    uint32_t pad2c[6];              // +0x2c..+0x43
    uint32_t f44, f48, f4c, f50;    // +0x44,0x48,0x4c,0x50
    uint32_t f54, f58, f5c, f60;    // +0x54,0x58,0x5c,0x60
};

struct AiffEvent { char pad[0x260]; };

struct AiffPlayer {
    int          mPosition;      // 0x00
    int          mBytesDone;     // 0x04
    int          mSamplesDone;   // 0x08
    int          mState;         // 0x0c
    int          mStarted;       // 0x10
    AiffFormat*  mpFormat;       // 0x14
    AiffStreamState m18;         // 0x18
    AiffPuller   mPuller;        // 0x28
    uint16_t     mFrameSamples;  // 0x8c
    uint8_t      mChannels;      // 0x8e
    uint8_t      mBits;          // 0x8f
    int          mSamplesLeft;   // 0x90
    Stream*      mpStream;       // 0x94
    int          mSingleMode;    // 0x98
    int          mTotalBytes;    // 0x9c
    int          mBytesUsed;     // 0xa0
    int          mHandle;        // 0xa4
    int          mStartHandle;   // 0xa8
    Decoder*     mpDecoder;      // 0xac
    uint32_t     mSampleCount;   // 0xb0
    float        mFrameRate;     // 0xb4
    int16_t      mBlockAlign;    // 0xb8
    int16_t      mCodecType;     // 0xba
    int          mPending;       // 0xbc
    int          mChunkSize;     // 0xc0
    void*        mpExtra;        // 0xc4
    void*        mChanBuf[4];    // 0xc8 (channel sample buffers)
    void*        mChunk[4];      // 0xd8 (file chunks held by each slot)
    int          mActive[4];     // 0xe8
    AiffEvent    mEvent;         // 0xf8
};

// packet handed to SNDPKTPLAY_submit: +4 size (bit31 = loop), +0xc.. per-channel pointers
struct SndPacket {
    int      field0;             // +0x00
    uint32_t size;               // +0x04
    int      field8;             // +0x08
    void*    channel[8];         // +0x0c
};

void AiffPlayer_releaseBuffer(void* channelBuffer, AiffPlayer* self);
void AiffPlayer_processBuffer(void* channelBuffer, AiffPlayer* self);

// @ 0x0112fc10
// Called when one decode slot finishes: find the slot, release its chunk and clear it.
void AiffPlayer_releaseBuffer(void* channelBuffer, AiffPlayer* self)
{
    int i = 0;
    void** slot = self->mChanBuf;
    do {
        if (channelBuffer == *slot) break;
        ++i;
        ++slot;
    } while (i < 4);

    self->mPending--;
    void* chunk = self->mChunk[i];
    if (chunk != 0) {
        self->mpStream->ReleaseChunk(chunk);
        self->mChunk[i] = 0;
    }
    self->mActive[i] = 0;
    if (self->mPending == 0 && (unsigned)self->mSamplesLeft == 0)
        self->mState = 3;
    FUN_0112fb50(self);
}

// @ 0x0112fc90
// (Re)initialise a player that already has its slots/streams: reset the helper sub-objects,
// (re)allocate the four decode buffers, register the decode-completion timer, read the format
// fields, install the decoder and prime up to four chunks.
void AiffPlayer_reset(AiffPlayer* self)
{
    FUN_01132fe0(&self->m18);
    FUN_0113fca0(&self->mPuller);

    void* base = g_pSystem->Alloc(0x4000, "Aiff Player decode buffers", 0x10, 0);
    self->mChanBuf[0] = base;
    self->mChanBuf[1] = (char*)base + 0x1000;
    self->mChanBuf[2] = (char*)base + 0x2000;
    self->mChanBuf[3] = (char*)base + 0x3000;
    self->mActive[0] = 0; self->mActive[1] = 0; self->mActive[2] = 0; self->mActive[3] = 0;
    self->mChunk[0] = 0;  self->mChunk[1] = 0;  self->mChunk[2] = 0;  self->mChunk[3] = 0;

    int size = FUN_0113f1c0(0xc);
    self->mHandle = FUN_0113f1d0(&AiffPlayer_releaseBuffer, 0, self, &self->mEvent, size);

    AiffFormat* fmt = self->mpFormat;
    self->mFrameSamples = (int16_t)(float)self->mFrameRate;   // cvttss2si [self+0xb4]
    self->mBits = 8;
    self->mChannels = (uint8_t)self->mBlockAlign;             // byte at +0xb8
    self->mPuller.b5 = 0x7f;

    self->m18.f0 = (uint8_t)RwFloat2Int(fmt->f0 * 127.0f);
    self->m18.w8 = (int16_t)RwFloat2Int(self->mpFormat->f1 * 4096.0f);
    self->m18.f3 = (uint8_t)RwFloat2Int(fmt->f2 * 127.0f);
    self->m18.wc = (int16_t)RwFloat2Int(fmt->f4);
    self->m18.we = (int16_t)RwFloat2Int(fmt->f5);
    self->m18.f4 = (uint8_t)RwFloat2Int(fmt->p3[0] * 127.0f);

    uint8_t channels = self->mChannels;
    int i = 0;
    if (channels != 0) {
        const uint8_t* rgain = (const uint8_t*)0x014cafd2;
        do {
            self->mPuller.gain[i] = (uint16_t)((uint16_t)rgain[i + (unsigned)channels * 6] << 8);
            ++i;
        } while (i < (int)(unsigned)self->mChannels);
    }

    int start = FUN_0113f250(self->mHandle, &self->mFrameSamples, &self->mPuller, &self->m18);
    self->mStartHandle = start;
    if (self->mState == 1)
        FUN_0113fba0(start, 0);

    int16_t ct = self->mCodecType;
    if (ct == 2) {
        void* p = FUN_011402c0(0x18);
        self->mpDecoder = p ? (Decoder*)((RawDecoder*)p)->FUN_01140440() : 0;
    } else if (ct == 3) {
        void* p = FUN_011402c0(0x18);
        self->mpDecoder = p ? (Decoder*)((RawDecoder*)p)->FUN_01140390() : 0;
    }
    self->mpDecoder->Init(&self->mBlockAlign);

    int chunkSize = self->mChunkSize;
    self->mStarted = 1;
    int n = 0;
    int total = 0;
    do {
        if ((unsigned)(self->mTotalBytes - total) <= (unsigned)chunkSize) break;
        FUN_0112fb50(self);
        chunkSize = self->mChunkSize;
        self->mBytesUsed += chunkSize;
        ++n;
        total += chunkSize;
    } while (n < 4);
    self->mState = 0;
}

// @ 0x0112ff40
// Destroy the player: stop the decoder, free the packet player and all buffers, stop the timer
// and free the player itself.
int AiffPlayer_destroy(AiffPlayer* self)
{
    if (self != 0) {
        self->mSingleMode = 0;
        if (self->mState != 2) {
            if (self->mpDecoder != 0) {
                if (self->mCodecType == 1)
                    self->mpDecoder->Stop(1);
                if ((self->mCodecType == 2 || self->mCodecType == 3) && self->mpDecoder != 0)
                    self->mpDecoder->Stop(1);
                self->mpDecoder = 0;
            }
            FUN_0113f9b0(self->mHandle);
            FUN_0113f750(self->mHandle);
            if (self->mpExtra != 0 && self->mSingleMode != 0) {
                self->mpStream->ReleaseChunk(self->mpExtra);
                self->mpExtra = 0;
            }
            int i = 0;
            do {
                if (self->mActive[i] == 1) {
                    AiffPlayer_releaseBuffer(self->mChanBuf[i], self);
                    self->mActive[i] = 0;
                }
                ++i;
            } while (i < 4);
            if (self->mChanBuf[0] != 0) {
                g_pSystem->Free(self->mChanBuf[0], 0);
                self->mChanBuf[0] = 0;
                self->mChanBuf[1] = 0;
                self->mChanBuf[2] = 0;
                self->mChanBuf[3] = 0;
            }
            self->mState = 2;
        }
        g_pSystem->Free(self, 0);
    }
    return 0;
}

// @ 0x01130060
// Decode-completion timer: if the stream is not finished and work is pending, decode one
// block into the slot's buffers and submit it; otherwise mark the player finished.
void AiffPlayer_processBuffer(void* channelBuffer, AiffPlayer* self)
{
    int i = 0;
    void** slot = self->mChanBuf;
    do {
        if (channelBuffer == *slot) break;
        ++i;
        ++slot;
    } while (i < 4);

    self->mPending--;

    if (self->mPosition >= self->mTotalBytes || (unsigned)self->mSamplesLeft == 0) {
        if (self->mPending == 0 && (unsigned)self->mSamplesLeft == 0)
            self->mState = 3;
        return;
    }

    int count = self->mChunkSize;
    if (self->mCodecType <= 1)
        count >>= 1;
    if ((unsigned)count > (unsigned)self->mSamplesLeft)
        count = self->mSamplesLeft;

    int perFrame = (int)self->mBlockAlign * (int)self->mCodecType;
    unsigned bytes = (unsigned)count / (unsigned)perFrame;

    self->mpDecoder->Decode(self->mBytesUsed, count, (int)bytes);

    void* base = self->mChanBuf[i];
    void* arr1[16];
    SndPacket pkt;
    pkt.field0 = 0;
    pkt.field8 = 0;
    int n = (int)self->mBlockAlign;
    if (n > 0) {
        int step = 0x4000 / (n * 4);
        for (int j = 0; j < n; ++j) {
            void* p = (char*)base + j * step;
            arr1[j] = p;
            pkt.channel[j] = p;
        }
    }
    self->mpDecoder->Fill(arr1, (int)bytes);

    pkt.size = bytes | 0x80000000u;
    SNDPKTPLAY_submit(self->mHandle, &pkt);

    self->mBytesDone += count;
    self->mSamplesDone += (int)bytes;
    self->mPosition += count;
    self->mBytesUsed += count;
    self->mPending++;
    self->mSamplesLeft -= count;
}

// @ 0x01130230
// Set one gain coefficient of the puller's per-channel mix table.
int AiffPlayer_setTableGain(void* fmt, int index, AiffPlayer* self)
{
    float* p = (float*)((AiffFormat*)fmt)->p3;
    FUN_0113fdd0(self->mStartHandle, index, RwFloat2Int(p[index] * 127.0f));
    return 0;
}

// @ 0x01130270
// Start playback from the beginning.
int AiffPlayer_start(AiffPlayer* self)
{
    FUN_0113fba0(self->mStartHandle, 0);
    self->mState = 1;
    return 0;
}

// @ 0x011302a0
// Set the start position (in samples).
int AiffPlayer_setStart(void* fmt, AiffPlayer* self)
{
    FUN_0113fba0(self->mStartHandle, (int)(RwFloat2Int(((AiffFormat*)fmt)->f1 * 4096.0f)));
    self->mState = 0;
    return 0;
}

// @ 0x011302e0
int AiffPlayer_setChannel(void* fmt, AiffPlayer* self)
{
    FUN_0113ff00(self->mStartHandle, (int)(RwFloat2Int(((AiffFormat*)fmt)->f0 * 127.0f)));
    return 0;
}

// @ 0x01130380
// Read the player's state word (thiscall-style free function in the original: object on stack).
int AiffPlayer_getState(AiffPlayer* self, int* out)
{
    *out = self->mState;
    return 0;
}

// @ 0x01130390
int AiffPlayer_getProgress(AiffPlayer* self, float* out)
{
    *out = (float)self->mSamplesDone / (float)(unsigned short)self->mFrameSamples;
    return 0;
}

// @ 0x011303c0
int AiffPlayer_getPosition(AiffPlayer* self, float* out)
{
    if (self->mStarted == 1 && self->mState != 0 && self->mState != 1) {
        *out = -1.0f;
        return 0;
    }
    unsigned v = self->mSampleCount;
    if (v != 0) {
        *out = (float)v / self->mFrameRate;
        return 0;
    }
    *out = -1.0f;
    return 0;
}

// @ 0x01130430
int AiffPlayer_acquireSampleBlock(int a0, unsigned requested, int a2, AiffPlayer* self, unsigned* out)
{
    *out = 0;
    unsigned left = (unsigned)self->mSamplesLeft;
    unsigned chunk = (unsigned)self->mChunkSize;
    if (chunk < left) {
        if (chunk <= requested) {
            *out = chunk;
            self->mSamplesLeft -= self->mChunkSize;
            if (self->mSingleMode == 0)
                FUN_0112fb50(self);
            return 1;
        }
    } else if (left <= requested) {
        *out = left;
        self->mSamplesLeft = 0;
        if (self->mSingleMode == 0)
            FUN_0112fb50(self);
        return 2;
    }
    return 0;
}

// @ 0x011304b0
// Parse a data block (COMM + SSND chunks), fill the format/decoder fields and return the object.
AiffPlayer* AiffPlayer_setupFromBlock(AiffFormat* fmt, void* data, int len, int a3,
                                      Stream* stream, int* bytesRead, int a6, AiffPlayer* self)
{
    self->mpFormat = fmt;
    self->mBlockAlign = 0;
    self->mPosition = 0;
    self->mBytesDone = 0;
    self->mSamplesDone = 0;
    self->mBytesUsed = (int)data;
    self->mTotalBytes = len;
    self->mState = 0;
    self->mSampleCount = 0;
    self->mFrameRate = 0.0f;
    self->mCodecType = 0;
    self->mPending = 0;
    self->mpStream = stream;
    self->mChunkSize = 0;
    self->mpExtra = 0;

    char* comm = FUN_01140110((char*)data, 0x434f4d4d, len);
    uint16_t u1 = *(uint16_t*)(comm + 8);
    uint32_t u4 = *(uint32_t*)(comm + 0xa);
    uint16_t u2 = *(uint16_t*)(comm + 0xe);
    ((uint8_t*)self)[0xb8] = (uint8_t)(u1 >> 8);
    ((uint8_t*)self)[0xb9] = (uint8_t)u1;
    ((uint8_t*)self)[0xb0] = (uint8_t)(u4 >> 24);
    ((uint8_t*)self)[0xb1] = (uint8_t)(u4 >> 16);
    ((uint8_t*)self)[0xb2] = (uint8_t)(u4 >> 8);
    ((uint8_t*)self)[0xb3] = (uint8_t)u4;
    ((uint8_t*)self)[0xba] = (uint8_t)(u2 >> 8);
    ((uint8_t*)self)[0xbb] = (uint8_t)u2;

    self->mFrameRate = FUN_01140290(comm + 0x10);

    int16_t ct = self->mCodecType;
    if (0 < ct && ct < 9)
        self->mCodecType = 1;
    if (8 < ct && ct < 0x11)
        self->mCodecType = 2;
    if (0x10 < ct && ct < 0x19)
        self->mCodecType = 3;
    if (0x18 < ct && ct < 0x21)
        self->mCodecType = 4;

    self->mSamplesLeft = (int)(short)self->mCodecType * (int)(short)self->mBlockAlign * (int)self->mSampleCount;

    char* ssnd = FUN_01140110((char*)data, 0x53534e44, len);
    self->mBytesUsed = (int)(ssnd + 0x10);
    *bytesRead = (int)((ssnd + 0x10) - (char*)data);
    self->mChunkSize = (int)(short)self->mCodecType << 11;
    self->mSingleMode = 1;
    return self;
}

// @ 0x01130680
// Create a complete AIFF player from an in-memory file image: allocate it, register the timer,
// parse the chunks, install the decoder and prime up to four packets.  The decoder sample-count
// is also kept in a local so the reference build can pass it to the packet player.
AiffPlayer* AiffPlayer_create(void* fmt, void* data, int len)
{
    int size = FUN_0113f1c0(0xc);
    AiffPlayer* self = (AiffPlayer*)g_pSystem->Alloc((unsigned)(size + 0xf8),
                                                     "AIFF Player Instance", 0x10, 0);
    self->mpFormat = (AiffFormat*)fmt;
    self->mPosition = 0;
    self->mBytesDone = 0;
    self->mSamplesDone = 0;
    self->mStarted = 0;
    self->mTotalBytes = len;
    self->mSampleCount = 0;
    self->mFrameRate = 0.0f;
    self->mCodecType = 0;
    self->mPending = 0;
    self->mSamplesLeft = len;
    self->mSingleMode = 1;
    self->mpStream = 0;
    self->mpExtra = 0;
    self->mBlockAlign = 0;

    int h = FUN_0113f1d0(&AiffPlayer_processBuffer, 0, self, &self->mEvent, size);
    self->mHandle = h;

    FUN_01132fe0(&self->m18);
    FUN_0113fca0(&self->mPuller);

    char* comm = FUN_01140110((char*)data, 0x434f4d4d, len);
    uint16_t u1 = *(uint16_t*)(comm + 8);
    uint32_t u4 = *(uint32_t*)(comm + 0xa);
    uint16_t u2 = *(uint16_t*)(comm + 0xe);
    ((uint8_t*)self)[0xb8] = (uint8_t)(u1 >> 8);
    ((uint8_t*)self)[0xb9] = (uint8_t)u1;
    ((uint8_t*)self)[0xb0] = (uint8_t)(u4 >> 24);
    ((uint8_t*)self)[0xb1] = (uint8_t)(u4 >> 16);
    ((uint8_t*)self)[0xb2] = (uint8_t)(u4 >> 8);
    ((uint8_t*)self)[0xb3] = (uint8_t)u4;
    ((uint8_t*)self)[0xba] = (uint8_t)(u2 >> 8);
    ((uint8_t*)self)[0xbb] = (uint8_t)u2;

    self->mFrameRate = FUN_01140290(comm + 0x10);

    int16_t ct = self->mCodecType;
    if (0 < ct && ct < 9)
        self->mCodecType = 1;
    if (8 < ct && ct < 0x11)
        self->mCodecType = 2;
    if (0x10 < ct && ct < 0x19)
        self->mCodecType = 3;
    if (0x18 < ct && ct < 0x21)
        self->mCodecType = 4;

    AiffFormat* f = self->mpFormat;
    self->mFrameSamples = (int16_t)(float)self->mFrameRate;
    self->mBits = 8;
    self->mChannels = (uint8_t)self->mBlockAlign;
    self->mPuller.b5 = 0x7f;

    self->m18.f0 = (uint8_t)RwFloat2Int(f->f0 * 127.0f);
    self->m18.w8 = (int16_t)RwFloat2Int(self->mpFormat->f1 * 4096.0f);
    self->m18.f3 = (uint8_t)RwFloat2Int(f->f2 * 127.0f);
    self->m18.wc = (int16_t)RwFloat2Int(f->f4);
    self->m18.we = (int16_t)RwFloat2Int(f->f5);
    self->m18.f4 = (uint8_t)RwFloat2Int(f->p3[0] * 127.0f);

    {
        uint8_t channels = self->mChannels;
        int j = 0;
        if (channels != 0) {
            const uint8_t* rgain = (const uint8_t*)0x014cafd2;
            do {
                self->mPuller.gain[j] = (uint16_t)((uint16_t)rgain[j + (unsigned)channels * 6] << 8);
                ++j;
            } while (j < (int)(unsigned)self->mChannels);
        }
    }

    self->mStartHandle = FUN_0113f250(self->mHandle, &self->mFrameSamples, &self->mPuller, &self->m18);

    char* ssnd = FUN_01140110((char*)data, 0x53534e44, len);
    self->mBytesUsed = (int)(ssnd + 0x10);

    void* base = g_pSystem->Alloc(0x4000, "Aiff Player decode buffers", 0x10, 0);
    self->mChanBuf[0] = base;
    self->mChanBuf[1] = (char*)base + 0x1000;
    self->mChanBuf[2] = (char*)base + 0x2000;
    self->mChanBuf[3] = (char*)base + 0x3000;
    self->mChunk[0] = 0; self->mChunk[1] = 0; self->mChunk[2] = 0; self->mChunk[3] = 0;
    self->mActive[0] = 0; self->mActive[1] = 0; self->mActive[2] = 0; self->mActive[3] = 0;

    self->mChunkSize = (int)(short)self->mCodecType << 11;

    int16_t type = self->mCodecType;
    if (type == 1) {
        void* p = FUN_011402c0(0x18);
        self->mpDecoder = p ? (Decoder*)((RawDecoder*)p)->FUN_01140510() : 0;
    }
    if (type == 2) {
        void* p = FUN_011402c0(0x18);
        self->mpDecoder = p ? (Decoder*)((RawDecoder*)p)->FUN_01140440() : 0;
    } else if (type == 3) {
        void* p = FUN_011402c0(0x18);
        self->mpDecoder = p ? (Decoder*)((RawDecoder*)p)->FUN_01140390() : 0;
    }
    self->mpDecoder->Init(&self->mBlockAlign);

    self->mSamplesLeft = (int)(short)self->mCodecType * (int)(short)self->mBlockAlign * (int)self->mSampleCount;

    int i = 0;
    void** chanPtr = self->mChanBuf;
    do {
        if (self->mPosition >= self->mTotalBytes) break;

        int16_t ctype = self->mCodecType;
        unsigned count;
        if (ctype <= 1)
            count = (unsigned)self->mChunkSize / (unsigned)(int)ctype;
        else
            count = (unsigned)self->mChunkSize;
        if (count > (unsigned)self->mSamplesLeft)
            count = (unsigned)self->mSamplesLeft;

        unsigned bytes = count / (unsigned)((int)ctype * (int)self->mBlockAlign);

        self->mpDecoder->Decode(self->mBytesUsed, (int)count, (int)bytes);

        void* base2 = *chanPtr;
        void* arr1[16];
        SndPacket pkt;
        pkt.field0 = 0;
        pkt.field8 = 0;
        int n = (int)self->mBlockAlign;
        int loopFlag = (i > 0) ? (int)0x80000000 : 0;
        if (n > 0) {
            int step = 0x4000 / (n * 4);
            for (int j = 0; j < n; ++j) {
                void* p = (char*)base2 + j * step;
                arr1[j] = p;
                pkt.channel[j] = p;
            }
        }
        self->mpDecoder->Fill(arr1, (int)bytes);

        pkt.size = bytes | (unsigned)loopFlag;
        SNDPKTPLAY_submit(self->mHandle, &pkt);

        self->mPending++;
        self->mBytesDone += count;
        self->mSamplesDone += (int)bytes;
        self->mPosition += count;
        self->mBytesUsed += count;
        self->mSamplesLeft -= count;

        ++chanPtr;
        ++i;
    } while (i < 4);
    return self;
}

// @ 0x01130be0
// Classify a 4-byte chunk id: TAG/TAG+ -> -1, ID3 -> -2, RIFF -> -3, MPEG frame sync -> id, else 0.
int AiffPlayer_checkChunkID(uint32_t id)
{
    if ((id & 0xffffff00) == 0x54414700)   // "TAG\0"
        return -1;
    if ((id & 0xffffff00) == 0x49443300)   // "ID3\0"
        return -2;
    if (id == 0x52494646)                  // "RIFF"
        return -3;
    if ((id & 0xffe00000) == 0xffe00000 &&
        (id & 0xf000) != 0xf000 &&
        (id & 0xc00) != 0xc00)
        return (int)id;
    return 0;
}

} } } // namespace rw::audio::core
