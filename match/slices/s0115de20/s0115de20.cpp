// Slice s0115de20 -- rw::audio::core FFT helper routines.
//
//   FftTable* allocation / release / table setup  (0x0115e330, 0x0115e3c0, 0x0115e3f0)
//   FftStream::Process                            (0x0115de20, 1290 bytes)
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc; rw::audio::core).
//
// FftStream is a sub-object of the mixer's voice/stream object (the mixer passes
// `voice + 0x50` as `this`).  It keeps two input blocks, a spectrum block, a
// short-lived phase/angle table and two accumulator work blocks, and advances a
// three-stage pipeline one "block descriptor" (FftBlock) per call:
//   stage 0: real FFT finishing pass on freshly captured rows, results -> mSpectrum
//   stage 1: overlap-add/rotate pass, mSpectrum -> mAnalysis
//   stage 2: second FFT pass on mAnalysis; every mPeriod blocks the two accumulator
//            work blocks are folded together and the transform phase is advanced.
// The final loop copies the finished block back into the caller's output buffer.
#include "types.h"
#include <math.h>

namespace rw { namespace audio { namespace core {
class System {
 public:
    void* Alloc(uint32_t size, const char* name, uint32_t align, uint32_t flags);  // 0x0112c820
    void  Free(void* p, uint32_t flags);                                             // 0x0112c850
};
}}}  // namespace rw::audio::core

extern rw::audio::core::System* gAudioSystem;  // 0x016e61a8

extern "C" void* __cdecl memset(void* dst, int value, unsigned int size);        // 0x011e073e
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int size);  // 0x011e0744

// Table header; the cos/sin/bit-reversal arrays live behind it at the stored byte offsets.
struct FftTable {
    int   log2n;          // +0x00  log2 of the real FFT size, minus one
    int   half;           // +0x04  cos/sin table length (size/2 + 1)
    int   size;           // +0x08  real FFT size / 2
    int   cosOffset;      // +0x0c  float cos[]
    int   sinOffset;      // +0x10  float sin[]
    int   bitrevOffset;   // +0x14  int   bitrev[]
};

// Returned by FFT_Alloc: the table block and its byte size (freed by FFT_Free).
struct FftPair {
    FftTable* table;      // +0x00
    unsigned  size;       // +0x04
};

// Per-block pipeline counts, one entry per mixer block.
struct FftBlock {
    int mixCount;         // +0x00  frames rotated into mAnalysis
    int fftCount;         // +0x04  frames finished into mSpectrum
    int finishCount;      // +0x08  frames run through the last butterfly stage
};

// Caller-supplied sample buffer (same shape for input and output).
struct SampleBuffer {
    int            unk00;     // +0x00
    float*         samples;   // +0x04  channel-interleaved rows
    int            unk08;     // +0x08
    unsigned short unk0c;     // +0x0c
    unsigned short stride;    // +0x0e  floats per row
};

// FFT pipeline state; layout matches the original object exactly.
class FftStream {
 public:
    void Process(const SampleBuffer* in, SampleBuffer* out, int unused,
                 unsigned* stamp);                               // 0x0115de20

 private:
    void Rotate(const float* src, const short* phase, float* dst);  // 0x0115dc10

    void*           mAlloc;        // +0x00  allocation base
    float*          mIn[2];        // +0x04  input blocks (mIn[0] == mAlloc)
    float*          mSpectrum;     // +0x0c  spectrum block
    short*          mPhaseTable;   // +0x10  interleaved phase/angle words
    float*          mAnalysis;     // +0x14  accumulated analysis rows
    float*          mWork[2];      // +0x18  accumulator work blocks
    int             mWorkSize;     // +0x20  bytes in one work block
    int             mFftFrames;    // +0x24  frames per FFT row
    int             mChannels;     // +0x28  number of channels (1 or more)
    int             mPeriod;       // +0x2c  blocks per transform period
    int             mPhase;        // +0x30  current transform phase
    int             mRemainder;    // +0x34  samples left over at setup
    int             mRowStride;    // +0x38  floats per captured row
    int             mBins;         // +0x3c  bins per row
    int             mBinsX2p2;     // +0x40  2*bins + 2 (FFT row length)
    int             mCopyFloats;   // +0x44  floats copied per FFT row
    int             mInStride;     // +0x48  floats between input rows
    int             mSpecStride;   // +0x4c  floats between spectrum rows
    int             mWorkStride;   // +0x50  floats between work rows
    int             mNumPasses;    // +0x54  number of sub-blocks per FFT block
    int             mWorkCount;    // +0x58  phase words per channel per frame
    int             mSubBlock;     // +0x5c  current block within the period
    float           mScale;        // +0x60  setup ratio
    int             mSelA;         // +0x64  accumulator selector (0/1)
    int             mSelB;         // +0x68  input selector (0/1)
    FftTable*       mTable;        // +0x6c  FFT tables
    int             mUnk70;        // +0x70
    int             mRowCount;     // +0x74  rows in one phase
    int             mBandCount;    // +0x78  bands per block
    FftBlock*       mBlocks;       // +0x7c  block descriptors
    int             mPos0;         // +0x80  stage 0 progress
    int             mPos1;         // +0x84  stage 1 progress
    int             mPos2;         // +0x88  stage 2 progress
    int             mCursor;       // +0x8c  current frame cursor
    unsigned char   mReady;        // +0x90  initialised flag
};

extern void FftFinish(FftTable* table, float* data);       // 0x0115f190
extern void FftButterfly(FftTable* table, float* data);    // 0x0115ffe0
extern void SwapWords(short* data, int count);             // 0x0115ddd0

// Reads/writes the caller's 32-bit counter in big-endian byte order.
static int ReadStamp(const unsigned* stamp)
{
    unsigned value = *stamp;
    unsigned char bytes[4];
    bytes[0] = (unsigned char)(value >> 24);
    bytes[1] = (unsigned char)(value >> 16);
    bytes[2] = (unsigned char)(value >> 8);
    bytes[3] = (unsigned char)value;
    int result;
    memcpy(&result, bytes, 4);
    return result;
}

static void WriteStamp(unsigned* stamp, int value)
{
    unsigned char* bytes = (unsigned char*)stamp;
    bytes[0] = (unsigned char)(value >> 24);
    bytes[1] = (unsigned char)(value >> 16);
    bytes[2] = (unsigned char)(value >> 8);
    bytes[3] = (unsigned char)value;
}

// @ 0x0115de20
void FftStream::Process(const SampleBuffer* in, SampleBuffer* out, int unused,
                        unsigned* stamp)
{
    int i;

    if (!mReady) {
        memset(mIn[1], 0, (unsigned)(mRowCount * mInStride) * 4);
        memset(mAnalysis, 0, (unsigned)(mFftFrames * mBandCount) * 4);
        memset(mWork[0], 0, (unsigned)(mBandCount * mWorkStride) * 4);
        memset(mWork[1], 0, (unsigned)(mBandCount * mWorkStride) * 4);
        mReady = 1;
    }

    // Capture this block's rows into the selected input block.
    for (i = 0; i < mRowCount; ++i) {
        memcpy(mIn[mSelB] + mSubBlock * mRowStride + i * mInStride,
               (const float*)in->samples + i * in->stride,
               (unsigned)in->stride * 4);
    }

    // Stage 0: finish the real FFT on the other input block, one row per frame.
    int fftCount = mBlocks[mSubBlock].fftCount;
    if (fftCount > 0) {
        int sel = (mSelB == 0);
        int end = mPos0 + fftCount;
        for (i = mPos0; i < end; ++i) {
            float* row = mIn[sel] + i * mInStride;
            memset(row + mBins, 0, (unsigned)(mBinsX2p2 - mBins) * 4);
            FftFinish(mTable, row);
            memcpy(mSpectrum + (mRowCount * mPhase + i) * mSpecStride,
                   row, (unsigned)mCopyFloats * 4);
        }
        mPos0 += fftCount;
        if (mPos0 == mRowCount) {
            if (*stamp) {
                int idx = -ReadStamp(stamp);
                if (idx == -1 || (idx < mPeriod && idx == mCursor)) {
                    SwapWords(mPhaseTable + mCursor * mChannels * mWorkCount,
                              mChannels * mWorkCount);
                    if (idx == -1)
                        *stamp = 0xffffffff;
                }
                if (idx != -1) {
                    if (idx == mPeriod - 1)
                        *stamp = 0;
                    else
                        WriteStamp(stamp, -(idx + 1));
                }
                ++mCursor;
            }
        }
    }

    // Stage 1: rotate the spectrum into the analysis accumulator.
    int mixCount = mBlocks[mSubBlock].mixCount;
    if (mixCount > 0) {
        for (int band = 0; band < mBandCount; ++band) {
            float* dst = mAnalysis + band * mFftFrames;
            if (mPos1 == 0)
                memset(dst, 0, (unsigned)mFftFrames * 4);
            int end = mPos1 + mixCount;
            if (end > mCursor)
                end = mCursor;
            for (i = mPos1; i < end; ++i) {
                int ph = mPhase - i;
                if (ph < 0)
                    ph += mPeriod;
                const short* phase;
                if (mChannels == 1)
                    phase = mPhaseTable + i * mWorkCount;
                else
                    phase = mPhaseTable + (i * mChannels + band) * mWorkCount;
                const float* spec;
                if (mRowCount == 1)
                    spec = mSpectrum + ph * mSpecStride;
                else
                    spec = mSpectrum + (mRowCount * ph + band) * mSpecStride;
                Rotate(spec, phase, dst);
            }
        }
        mPos1 += mixCount;
    }

    // Stage 2: run the last butterfly stage over the analysis rows.
    int finishCount = mBlocks[mSubBlock].finishCount;
    if (finishCount > 0) {
        int end = mPos2 + finishCount;
        for (i = mPos2; i < end; ++i)
            FftButterfly(mTable, mAnalysis + i * mFftFrames);
        mPos2 += finishCount;
    }

    if (mSubBlock < mNumPasses - 1) {
        ++mSubBlock;
    } else {
        // Period complete: fold the two work blocks and advance the phase.
        int sel = (mSelA == 0);
        for (int band = 0; band < mBandCount; ++band) {
            float* other = mWork[sel] + band * mBins;
            float* cur = mWork[mSelA] + band * mBins;
            const float* src = mAnalysis + band * mFftFrames;
            for (int k = 0; k < mBins; ++k) {
                other[k] += src[k];
                cur[k] = src[mBins + k];
            }
        }
        ++mPhase;
        if (mPhase >= mPeriod)
            mPhase = 0;
        if (mSelA == 0) {
            mSelA = 1;
            mSelB = 1;
        } else {
            mSelA = 0;
            mSelB = 0;
        }
        mSubBlock = 0;
        mPos0 = 0;
        mPos1 = 0;
        mPos2 = 0;
    }

    // Hand the finished block back to the caller.
    for (i = 0; i < mBandCount; ++i) {
        memcpy((float*)((char*)out->samples + i * out->stride * 4),
               mWork[mSelA] + mSubBlock * mRowStride + i * mBins,
               (unsigned)mRowStride * 4);
    }
}

// @ 0x0115e330
int FFT_Alloc(int n, char flag, FftPair* out)
{
    if (!flag)
        --n;
    unsigned size = 1u << n;
    int half = (int)(size / 2) + 1;
    unsigned bytes = (size + 2u * half + 8u) * 4u;
    FftTable* table = (FftTable*)gAudioSystem->Alloc(bytes, "FFT instance", 0x80, 0);
    if (!table) {
        out->table = 0;
        out->size = 0;
        return -1;
    }
    int sinOffset = 0x18 + half * 4;
    table->sinOffset = sinOffset;
    table->size = (int)size;
    table->half = half;
    table->bitrevOffset = sinOffset + half * 4;
    table->log2n = n;
    table->cosOffset = 0x18;
    out->table = table;
    out->size = bytes;
    return 0;
}

// @ 0x0115e3c0
int FFT_Free(FftPair* out)
{
    gAudioSystem->Free(out->table, 0);
    out->table = 0;
    out->size = 0;
    return 0;
}

// @ 0x0115e3f0
int FFT_Setup(FftTable* table)
{
    int log2n = table->log2n;
    int size = table->size;
    int* bitrev = (int*)((char*)table + table->bitrevOffset);
    int half = table->half;
    float* cosT = (float*)((char*)table + table->cosOffset);
    float* sinT = (float*)((char*)table + table->sinOffset);

    for (int k = 0; k < half; ++k) {
        float a = (float)k * 3.14159274f / (float)size;
        cosT[k] = (float)cos((double)a);
        sinT[k] = (float)sin((double)a);
    }

    for (int i = 0; i < size; ++i) {
        unsigned v = 0;
        bitrev[i] = (int)v;
        unsigned c = (unsigned)i;
        for (int b = 0; b < log2n; ++b) {
            v <<= 1;
            v |= c & 1;
            c >>= 1;
        }
        bitrev[i] = (int)v;
    }

    bitrev[size] = size;
    bitrev[size + 1] = size + 1;
    return 0;
}
