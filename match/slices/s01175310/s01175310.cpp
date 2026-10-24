// Slice s01175310: one frame decode of the RenderWare/EATech speech codec (LPC vocoder), @ 0x01175310.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
// The voice state at `v` holds a little-endian bit reader (+0 read pointer, +4 bit buffer, +8 bit count) and
// the previous frame's 12 reflection (PARCOR) coefficients at +0x114. One frame:
//   * 12 quantised reflection coefficients (4 x 6 bits, then 8 x 5 bits) are looked up in a shared table
//     (the 5-bit ones use the upper half, tab+16) and turned into per-quarter deltas ((q - old) * 0.25);
//   * 4 sub-frames of 108 samples: each reads an 8-bit lag (pos - lag selects the pitch source in the history
//     ring), a 4-bit pitch gain (x 1/15) and a 6-bit excitation gain, then decodes the excitation
//     (0x011741c0: algebraic pulses, stride 1, or stride 2 with a 2-bit pulse offset/interpolation selector)
//     and mixes excitation * gain + history[lag] * pitchGain into the output;
//   * the 12 coefficients are advanced by one delta each quarter and the all-pole filter LpcSynthesize
//     (0x011746c0) runs over the output after every step (offsets 0, 12, 24, 36; the last one covers the rest);
//   * finally the last 324 output samples are moved into the history ring (memmove).
#include "types.h"

struct LpcVoice {
    const unsigned char* p;                  // +0x000 bit reader: read pointer
    unsigned int buf;                        // +0x004 bit buffer
    int cnt;                                 // +0x008 valid bit count
    int mode;                                // +0x00c 0: dense excitation, else sparse (stride 2)
    int thresh;                              // +0x010 first-index threshold selecting the excitation codebook
    float gain[64];                          // +0x014 excitation gain table
    float refl[12];                          // +0x114 reflection coefficients (interpolated per quarter)
    float hist[12];                          // +0x144 synthesis filter history (circular)
    float ring[324];                         // +0x174 history ring (0x510 bytes), directly followed by out[]
    float out[432];                          // +0x684 excitation in / speech out, in place
};

extern "C" void* (__cdecl* _imp__memcpy)(void*, const void*, unsigned int);   // IAT 0x015c3848 (msvcr90 memcpy)
extern unsigned int g_bitMask[];             // 0x015c4b74: g_bitMask[n] = (1 << n) - 1
extern float g_quantTab[];                   // 0x015c4b98: reflection quantiser table (64 entries)
extern "C" void __cdecl FUN_011741c0(LpcVoice* v, int sparse, float* out, int stride);   // excitation decode

// helper at 0x01174420 (static, refl in ECX, a in EDI)
// Step-up recursion done by running the lattice: T holds the backward lattice state, U the
// successive lattice outputs, a[] the resulting predictor coefficients.
static void ReflectionToLpc(const float* r, float* a)
{
    float T[12];
    float U[12];
    for (int k = 10; k >= 0; k--) T[k + 1] = r[k];
    T[0] = 1.0f;
    for (int i = 0; i < 12; i++) {
        float e = -(r[11] * T[11]);
        for (int k = 10; k >= 0; k--) {
            e -= r[k] * T[k];
            T[k + 1] = r[k] * e + T[k];
        }
        T[0] = e;
        U[i] = e;
        for (int j = 0; j < i; j++) e -= a[j] * U[i - 1 - j];
        a[i] = e;
    }
}

// One output sample j of a 12-sample block: coefficient a[(k + j) % 12] pairs with history
// slot k, and the new sample overwrites slot 11 - j (the oldest one).
#define LPC_TAP(k, j) a[((k) + (j)) % 12] * v->hist[k]
#define LPC_STEP(j)                                                                        \
    {                                                                                      \
        float y = p[j] + LPC_TAP(0, j) + LPC_TAP(1, j) + LPC_TAP(2, j) + LPC_TAP(3, j)     \
                  + LPC_TAP(4, j) + LPC_TAP(5, j) + LPC_TAP(6, j) + LPC_TAP(7, j)          \
                  + LPC_TAP(8, j) + LPC_TAP(9, j) + LPC_TAP(10, j) + LPC_TAP(11, j);       \
        v->hist[11 - (j)] = y;                                                             \
        p[j] = y;                                                                          \
    }

// helper at 0x011746c0 (static: voice in ESI, offset in EAX, numBlocks on the stack)
static void LpcSynthesize(LpcVoice* v, int offset, int numBlocks)
{
    float a[12];
    float* p = &v->out[offset];
    ReflectionToLpc(v->refl, a);
    for (int i = 0; i < numBlocks; i++) {
        LPC_STEP(0) LPC_STEP(1) LPC_STEP(2) LPC_STEP(3) LPC_STEP(4) LPC_STEP(5)
        LPC_STEP(6) LPC_STEP(7) LPC_STEP(8) LPC_STEP(9) LPC_STEP(10) LPC_STEP(11)
        p += 12;
    }
}


static __forceinline unsigned ReadBits(LpcVoice* v, int n)
{
    unsigned r = v->buf & g_bitMask[n];
    v->cnt -= n;
    int c = v->cnt;
    unsigned rest = v->buf >> n;
    v->buf = rest;
    if (c < 8) {
        const unsigned char* q = v->p;
        unsigned b = *q;
        v->p = q + 1;
        v->buf = (b << c) | rest;
        v->cnt = c + 8;
    }
    return r;
}

#define DELTA6(k) { unsigned i = ReadBits(v, 6); d[k] = (g_quantTab[i] - v->refl[k]) * 0.25f; }
#define DELTA5(k) { unsigned i = ReadBits(v, 5); d[k] = (g_quantTab[16 + i] - v->refl[k]) * 0.25f; }
#define ADD6(k) { v->refl[(k) + 0] = d[(k) + 0] + v->refl[(k) + 0]; v->refl[(k) + 1] = d[(k) + 1] + v->refl[(k) + 1]; \
                  v->refl[(k) + 2] = d[(k) + 2] + v->refl[(k) + 2]; v->refl[(k) + 3] = d[(k) + 3] + v->refl[(k) + 3]; \
                  v->refl[(k) + 4] = d[(k) + 4] + v->refl[(k) + 4]; v->refl[(k) + 5] = d[(k) + 5] + v->refl[(k) + 5]; }

// @ 0x01175310
namespace SpeechCodec { void DecodeFrame(LpcVoice* v);
void DecodeFrame(LpcVoice* v)
{
    float d[12];
    int sparseSel;
    {
        unsigned i0 = ReadBits(v, 6);
        sparseSel = (int)i0 < v->thresh;
        d[0] = (g_quantTab[i0] - v->refl[0]) * 0.25f;
    }
    DELTA6(1) DELTA6(2) DELTA6(3)
    DELTA5(4) DELTA5(5) DELTA5(6) DELTA5(7) DELTA5(8) DELTA5(9) DELTA5(10) DELTA5(11)

    const float c1 = 0.018032679f, c2 = 0.11459156f, c3 = 0.59738594f;
    float work[5 + 108 + 5];
    float* buf = work + 5;
    float* dst = v->out;

    for (int pos = 0xd8; pos < 0x288; pos += 0x6c) {
        int base = pos - (int)ReadBits(v, 8);
        float mix = (float)ReadBits(v, 4) * 0.06666667f;
        float gain = v->gain[ReadBits(v, 6)];

        if (v->mode == 0) {
            FUN_011741c0(v, sparseSel, buf, 1);
        } else {
            unsigned off = ReadBits(v, 1);
            unsigned zero = ReadBits(v, 1);
            FUN_011741c0(v, sparseSel, buf + off, 2);
            if (zero == 0) {
                for (int k = 0; k < 5; k++) { work[k] = 0.0f; work[113 + k] = 0.0f; }
                float* q = buf + (6 - off);
                for (int n = 0x36; n != 0; n--) {
                    q[-5] = ((q[-10] + q[0]) * c1 - (q[-8] + q[-2]) * c2) + (q[-6] + q[-4]) * c3;
                    q += 2;
                }
                gain = gain * 0.5f;
            } else {
                float* q = buf + (1 - off);
                for (int n = 0x36; n != 0; n--) { *q = 0.0f; q += 2; }
            }
        }

        const float* src = v->ring + base;
        for (int j = 0; j < 0x6c; j += 9) {
            dst[0] = buf[j + 0] * gain + src[j + 0] * mix;
            dst[1] = buf[j + 1] * gain + src[j + 1] * mix;
            dst[2] = buf[j + 2] * gain + src[j + 2] * mix;
            dst[3] = buf[j + 3] * gain + src[j + 3] * mix;
            dst[4] = buf[j + 4] * gain + src[j + 4] * mix;
            dst[5] = buf[j + 5] * gain + src[j + 5] * mix;
            dst[6] = buf[j + 6] * gain + src[j + 6] * mix;
            dst[7] = buf[j + 7] * gain + src[j + 7] * mix;
            dst[8] = buf[j + 8] * gain + src[j + 8] * mix;
            dst += 9;
        }
    }

    _imp__memcpy(v->ring, &v->out[108], 0x510);
    for (int k = 0; k < 12; k += 6) ADD6(k)
    LpcSynthesize(v, 0, 1);
    for (int k = 0; k < 12; k += 6) ADD6(k)
    LpcSynthesize(v, 12, 1);
    for (int k = 0; k < 12; k += 6) ADD6(k)
    LpcSynthesize(v, 24, 1);
    for (int k = 0; k < 12; k += 6) ADD6(k)
    LpcSynthesize(v, 36, 0x21);
}
} // namespace SpeechCodec

// ---------------------------------------------------------------------------------------------
// The voice stream around the codec (0x01175ca0 .. 0x011761f0): packet framing for the framed mode
// and the sample feeder that pulls decoded granules of 28 samples. Both roles describe the same
// state the codec reads through LpcVoice above. Names are Claude-coined from usage.
// ---------------------------------------------------------------------------------------------

// Big-endian 16-bit field of a packet header: the parser stores the two network-order bytes and
// later reads the pair back as a signed sample count / slot index.
struct Be16 {
    union {
        short mValue;                   // +0x00 signed value
        unsigned char mBytes[2];        // +0x00 network order, mBytes[0] is the low byte
    };
};

// Packet-mode view of the stream: a bit reader over the packet payload, the 432-sample buffer the
// codec fills, and the framing state of the packet being parsed.
struct VoiceStream {
    const unsigned char* mpRead;        // +0x0000 bit reader position
    unsigned int mBitBuf;               // +0x0004 bit buffer
    int mBitCnt;                        // +0x0008 valid bit count
    unsigned char mCodec[0x684 - 0x0c]; // +0x000c codec state (see LpcVoice)
    float mSamples[432];                // +0x0684 decoded block / the packet's samples
    int mBuffered;                      // +0x0d44 samples held in mSamples
    const unsigned char* mpPacket;      // +0x0d48 read position inside the packet
    unsigned char* mpOut;               // +0x0d4c caller's destination
    Be16 mPacketSamples;                // +0x0d50 sample count of the current packet
    Be16 mPacketOffset;                 // +0x0d52 first sample slot the packet fills
    int mBytesLeft;                     // +0x0d54 packet bytes still to produce
    int mBytesTotal;                    // +0x0d58 size of the packet that was started
    int mCodecMode;                     // +0x0d5c codec sub-mode handed to the frame decoder
    int mSyncPending;                   // +0x0d60 a 0xee marker opened the current packet
    int mStreaming;                     // +0x0d64 1: packets are framed and sampled

    VoiceStream* ResetPacket();                             // 0x01175ca0
    int StartPacket(const unsigned char* pData, int nTotal, int nBytes);     // 0x01175ce0
    void SetPositions(int* pState, int nFlags);             // 0x01175d70
    int Read(int* ppOut, int nSamples);                     // 0x01175da0
};

// Frame decoder of the codec (0x01175170): arms the bit reader with a payload and a codec mode.
extern void __stdcall FUN_01175170(const unsigned char* pData, void* pStream, int mode);

// Feeder view of the stream: a fill callback that produces granules of 28 samples, handed out in
// arbitrary chunk sizes.
struct SampleFeeder {
    void (__cdecl *mpfnFill)(int* pCount);  // +0x0000 granule producer
    int mPending;                       // +0x0004 samples of the last granule not handed out yet
    int mAvailable;                     // +0x0008 samples the source can still produce
    int mMode;                          // +0x000c source mode
    const float* mpSrc;                 // +0x0010 read position inside the pending samples
    unsigned char mPad14[0x24 - 0x14];  // +0x0014
    float mGranule[28];                 // +0x0024 granule the fill callback decodes into
    int mFillCount;                     // +0x0094 samples asked from / produced by the callback
    float mCoefA;                       // +0x0098
    float mCoefB;                       // +0x009c
    void* mpSource;                     // +0x00a0
    float* mpDst;                       // +0x00a4 write position in the caller's buffer

    int SetSource(void* pSource, int nMode, int nAvailable);   // 0x01175f50
    int Read(float** ppDst, int nSamples);                     // 0x01175f80
    void SetCoefs(const float* pCoefs);                        // 0x011761f0
};

// @ 0x01175ca0
// Drops any packet in flight and puts the stream back into framed (sampled) mode.
VoiceStream* VoiceStream::ResetPacket()
{
    mBuffered = 0;
    mBytesLeft = 0;
    mBytesTotal = 0;
    mPacketSamples.mValue = 0;
    mPacketOffset.mValue = 0;
    mCodecMode = 0;
    mSyncPending = 0;
    mStreaming = 1;
    return this;
}

// @ 0x01175ce0
// Starts a packet: hands the payload to the frame decoder. Fails while a packet is still running.
int VoiceStream::StartPacket(const unsigned char* pData, int nTotal, int nBytes)
{
    if (pData == 0)
        return -1;
    if (mBytesLeft != 0)
        return -1;
    mBytesLeft = nBytes;
    mBytesTotal = nTotal;
    mBuffered = 0;
    mpPacket = pData;
    if (mStreaming == 1) {
        mSyncPending = (*pData == 0xee);
        pData++;
    }
    FUN_01175170(pData, this, mCodecMode);
    return 0;
}

// @ 0x01175d70
// Continues a packet from a three-word state block: bit buffer, slot count and codec mode.
void VoiceStream::SetPositions(int* pState, int nFlags)
{
    mBitBuf = pState[0];
    mCodecMode = pState[2];
    mBuffered = pState[1];
}

// @ 0x01175da0
// Produces up to nSamples samples of the running packet: it drains what the codec already decoded,
// decoding another frames' worth whenever the request is not satisfied yet. In framed mode every
// decoded block is followed by a new packet header and its 16-bit samples.
int VoiceStream::Read(int* ppOut, int nSamples)
{
    int left = mBytesLeft;
    int buffered = mBuffered;
    if (left == 0)
        return 0;
    mpOut = (unsigned char*)*ppOut;
    if (nSamples < left)
        left = nSamples;
    int done = left;
    if (done > 0) {
        for (;;) {
            if (done < buffered)
                buffered = done;
            _imp__memcpy(mpOut, &mSamples[432 - mBuffered], buffered * 4);
            mBuffered -= buffered;
            mpOut += buffered * 4;
            done -= buffered;
            if (done < 1)
                break;
            SpeechCodec::DecodeFrame((LpcVoice*)this);
            buffered = 432;
            mBuffered = buffered;
            if (mStreaming != 1)
                continue;
            mpPacket = mpRead - 1;
            if (mSyncPending != 0) {
                const unsigned char* p = mpPacket;
                mPacketOffset.mBytes[0] = p[1];
                mPacketOffset.mBytes[1] = p[0];
                mPacketSamples.mBytes[0] = p[3];
                mPacketSamples.mBytes[1] = p[2];
                mpPacket += 4 + (short)mPacketSamples.mValue * 2;
                mpRead = mpPacket + 1;
                float* pSlot = &mSamples[(short)mPacketOffset.mValue];
                const unsigned char* q = p + 4;
                Be16 sample;
                for (short i = 0; i < (short)mPacketSamples.mValue; i++) {
                    sample.mBytes[0] = q[1];
                    sample.mBytes[1] = q[0];
                    *pSlot++ = (float)(short)sample.mValue;
                    q += 2;
                }
                mSyncPending = 0;
            }
            if (*mpPacket == 0xee)
                mSyncPending = 1;
            mBitCnt = 8;
            mBitBuf = *mpRead;
            mpRead++;
        }
    }
    mBytesLeft -= left;
    return left;
}

// @ 0x01175f50
// Arms the feeder with a sample source; only accepted while nothing is left over.
int SampleFeeder::SetSource(void* pSource, int nMode, int nAvailable)
{
    if (pSource == 0)
        return -1;
    if (mAvailable != 0)
        return -1;
    mAvailable = nAvailable;
    mMode = nMode;
    mpSource = pSource;
    return 0;
}

// @ 0x01175f80
// Hands out up to nSamples samples: first the leftovers of the previous granule, then whole granules
// straight from the fill callback, and finally a partial granule that is buffered for the next call.
int SampleFeeder::Read(float** ppDst, int nSamples)
{
    int done = 0;
    mpDst = *ppDst;
    if (mAvailable == 0)
        return 0;
    if (nSamples > mAvailable)
        nSamples = mAvailable;
    if (mPending != 0) {
        int n = mPending;
        if (n > nSamples)
            n = nSamples;
        for (int i = 0; i < n; i++) {
            *mpDst++ = *mpSrc++;
        }
        mAvailable -= n;
        mPending -= n;
        nSamples -= n;
        done = n;
    }
    int whole = nSamples / 28 * 28;
    int rest = nSamples - whole;
    mFillCount = whole;
    if (whole > 0) {
        mpfnFill(&mFillCount);
        mAvailable -= whole;
        done += whole;
    }
    if (rest > 0) {
        float* pOld = mpDst;
        mFillCount = rest;
        mpDst = mGranule;
        mpfnFill(&mFillCount);
        mAvailable -= rest;
        mpSrc = mpDst + mFillCount;
        mPending = -mFillCount;
        mpDst -= 28;                    // the callback leaves mpDst one past the granule
        for (int k = 0; k < rest; k++)
            pOld[k] = mpDst[k];
        done += rest;
    }
    if (mAvailable <= 0)
        mPending = 0;
    return done;
}

// @ 0x011761f0
void SampleFeeder::SetCoefs(const float* pCoefs)
{
    mCoefA = pCoefs[0];
    mCoefB = pCoefs[1];
}
