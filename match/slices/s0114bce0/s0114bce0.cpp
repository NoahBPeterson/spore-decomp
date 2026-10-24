// Slice s0114bce0 -- rw::audio::core pitched/EARenderWare sample voice (0x0114bce0..0x0114cb56).
//
// The functions are the x86 build of the "rwaudio" streamed sample decoder:
//   * Unpack0::UnpackInt32 -- format-0 variable-length integer decoder (0x0114c2e0)
//   * BitStreamReader::Next -- run-length reader over a packed table (0x0114c3e0)
//   * SampleRegions::ScanPacked / ScanBlocks / Init / Reset -- region-table scanners
//     that pick the block covering a sample position (0x0114c470 .. 0x0114c880)
//   * SlotPool::AddSlot -- appends a playback slot to a voice (0x0114c8c0)
//   * the vibrato buffer copy and the sin-LFO renderer (0x0114c950, 0x0114ca30)
//   * RenderPitchedVoice -- the main pitched-playback render step (0x0114bce0)
//
// Object layouts follow the member offsets the original code touches; the ones
// that only appear as plain scalars keep descriptive names.

#include "types.h"
#include <string.h>
#include <math.h>

namespace rw
{
namespace audio
{
namespace core
{

// ---------------------------------------------------------------------------
// 0x0114c2e0 -- format-0 variable-length integer decoder.  The prefix nibble of
// the first byte selects the byte count (1..5); the payload carries the value
// and, in the signed form, the sign in its low bit (value = -1 - magnitude).
// ---------------------------------------------------------------------------
class Unpack0
{
public:
    static int UnpackInt32(const unsigned char* pSrc, unsigned int* pDst);
};

// @ 0x0114c2e0
int Unpack0::UnpackInt32(const unsigned char* pSrc, unsigned int* pDst)
{
    int v0 = pSrc[0];
    int magnitude;
    int sign;
    int count;

    if (v0 < 0xc0)
    {
        magnitude = v0 >> 1;
        sign = v0 & 1;
        count = 1;
    }
    else if (v0 < 0xf0)
    {
        int v1 = pSrc[1];
        magnitude = ((((v0 << 8) | v1) >> 1) & 0xffff9fff) + 0x60;
        sign = v1 & 1;
        count = 2;
    }
    else if (v0 < 0xfc)
    {
        int v1 = pSrc[1];
        int v2 = pSrc[2];
        magnitude = ((((((v0 << 8) | v1) & 0xffff0fff) << 8) | (v2 & 0xff0fffff)) >> 1) + 0x1860;
        sign = v2 & 1;
        count = 3;
    }
    else if (v0 < 0xff)
    {
        int v1 = pSrc[1];
        int v2 = pSrc[2];
        int v3 = pSrc[3];
        magnitude = (((((((v1 << 8) | v2) & 0x3ffff) | ((v0 & 3) << 16)) << 8) |
                      (v3 & 0x3fffffe)) >> 1) + 0x61860;
        sign = v3 & 1;
        count = 4;
    }
    else
    {
        magnitude = (((((pSrc[1] << 8) | pSrc[2]) << 8) | pSrc[3]) << 8) | pSrc[4];
        sign = 0;
        count = 5;
    }

    if (sign != 0)
    {
        *pDst = -1 - magnitude;
        return count;
    }
    *pDst = magnitude;
    return count;
}

// ---------------------------------------------------------------------------
// 0x0114c3e0 -- run-length reader over the packed table: a count (signed, so a
// negative count marks the end of the stream) followed by the value repeated
// while the count lasts.
// ---------------------------------------------------------------------------
struct BitStreamReader
{
    /* 0x00 */ const unsigned char** mppData;
    /* 0x04 */ int mValue;
    /* 0x08 */ int mRemaining;
    /* 0x0c */ uint8_t mbValid;
    /* 0x0d */ uint8_t mPad0d[3];

    explicit BitStreamReader(const unsigned char** ppData)
        : mppData(ppData), mValue(0), mRemaining(0), mbValid(0) {}

    int Next();
};

// @ 0x0114c3e0
int BitStreamReader::Next()
{
    int value;
    if (mRemaining <= 0)
    {
        int used = Unpack0::UnpackInt32(*mppData, (unsigned int*)&value);
        *mppData += used;
        mRemaining = value + 1;
        mbValid = 1;
        if (value < 0)
        {
            mbValid = 0;
            mRemaining = 1 - value;
        }
        if (mbValid != 0)
        {
            used = Unpack0::UnpackInt32(*mppData, (unsigned int*)&value);
            *mppData += used;
            mValue += value;
        }
    }
    if (mbValid == 0)
    {
        int used = Unpack0::UnpackInt32(*mppData, (unsigned int*)&value);
        *mppData += used;
        mValue += value;
    }
    --mRemaining;
    return mValue;
}

// ---------------------------------------------------------------------------
// Region table of a streamed sample.  Each block is {step, offset, length,
// last}; the scanner picks the block containing the requested position and
// publishes mStart/mBlockPos/mCount/mTail/mOffset/mbLast for the renderer.
// ---------------------------------------------------------------------------
struct SampleRegions
{
    /* 0x00 */ int mStart;
    /* 0x04 */ int mBlockPos;
    /* 0x08 */ int mTail;
    /* 0x0c */ int mCount;
    /* 0x10 */ int mOffset;
    /* 0x14 */ int mFlags;
    /* 0x18 */ int mBlockSize;
    /* 0x1c */ uint8_t mbLast;
    /* 0x1d */ uint8_t mPad1d[3];

    bool Init(const unsigned char* pData, unsigned int length);
    bool ScanPacked(const unsigned char* pData, unsigned int length);
    bool ScanBlocks(const unsigned char* pData, unsigned int length);
    void Reset(const unsigned char* pData, unsigned int length);
};

// 0x0114c600 -- reads a 16-byte block as four big-endian words: every group of
// four bytes is stored in reverse order.
// @ 0x0114c600
static void __fastcall Swap16Bytes(unsigned char* pDst, const unsigned char* pSrc)
{
    pDst[0] = pSrc[3];
    pDst[1] = pSrc[2];
    pDst[2] = pSrc[1];
    pDst[3] = pSrc[0];
    pDst[4] = pSrc[7];
    pDst[5] = pSrc[6];
    pDst[6] = pSrc[5];
    pDst[7] = pSrc[4];
    pDst[8] = pSrc[11];
    pDst[9] = pSrc[10];
    pDst[10] = pSrc[9];
    pDst[11] = pSrc[8];
    pDst[12] = pSrc[15];
    pDst[13] = pSrc[14];
    pDst[14] = pSrc[13];
    pDst[15] = pSrc[12];
}

// 0x0114c470 -- scan a packed (variable-length encoded) region table.
// @ 0x0114c470
bool SampleRegions::ScanPacked(const unsigned char* pData, unsigned int length)
{
    unsigned int target = length - mBlockSize;
    if ((int)target < 1)
        target = 0;

    BitStreamReader r0(&pData), r1(&pData), r2(&pData), r3(&pData);
    int step = r0.Next();
    int offset = r1.Next();
    int len = r2.Next();
    int last = r3.Next();
    int base = mStart;
    int pos = 0;
    int accBase = 0;
    int accOffset = 0;

    while (len >= 0)
    {
        if ((pos <= (int)target && (int)target < pos + len) || last == 1)
        {
            if (offset == 0)
                mStart = 0;
            else
                mStart = accBase + base;
            int count = (int)(length - pos);
            mBlockPos = pos;
            if (mBlockSize < count)
                count = mBlockSize;
            mTail = (int)(length - count) - pos;
            mCount = count;
            mOffset = accOffset;
            mbLast = (last == 1);
        }
        pos += len;
        if ((int)length < pos)
            return false;
        accBase += offset;
        accOffset += step;
        step = r0.Next();
        offset = r1.Next();
        len = r2.Next();
        last = r3.Next();
    }
    return true;
}

// 0x0114c670 -- scan a region table of 16-byte big-endian blocks.
// @ 0x0114c670
bool SampleRegions::ScanBlocks(const unsigned char* pData, unsigned int length)
{
    unsigned int target = length - mBlockSize;
    if ((int)target < 1)
        target = 0;

    int base = mStart;
    unsigned char header[16];
    Swap16Bytes(header, pData);
    const unsigned char* pBlock = pData + 16;
    int blockLen = *(int*)&header[8];
    int pos = 0;
    int accBase = 0;
    int accOffset = 0;

    while (blockLen >= 0)
    {
        int offset = *(int*)&header[4];
        int step = *(int*)&header[0];
        int last = *(int*)&header[12];
        if ((pos <= (int)target && (int)target < pos + blockLen) || last == 1)
        {
            if (offset == 0)
                mStart = 0;
            else
                mStart = accOffset + base;
            int count = (int)(length - pos);
            mBlockPos = pos;
            if (mBlockSize < count)
                count = mBlockSize;
            mTail = (int)(length - count) - pos;
            mCount = count;
            mOffset = accBase;
            mbLast = (last == 1);
        }
        pos += blockLen;
        if ((int)length < pos)
            return false;
        accOffset += offset;
        accBase += step;
        Swap16Bytes(header, pBlock);
        pBlock += 16;
        blockLen = *(int*)&header[8];
    }
    return true;
}

// 0x0114c7e0 -- parse the stream header and dispatch to the matching scanner.
// @ 0x0114c7e0
bool SampleRegions::Init(const unsigned char* pData, unsigned int length)
{
    unsigned char entry = pData[1];
    mFlags = (signed char)entry & 0xf;
    mBlockSize = (pData[2] << 8) | pData[3];

    unsigned int start = ((unsigned int)pData[4] << 24) | ((unsigned int)pData[5] << 16) |
                         ((unsigned int)pData[6] << 8) | pData[7];
    if (start != 0)
        mStart = (int)(start + (unsigned int)pData);
    else
        mStart = 0;

    const unsigned char* pBlocks = pData + 8;
    switch (entry >> 4)
    {
    case 0:
        return ScanBlocks(pBlocks, length);
    case 1:
        return ScanPacked(pBlocks, length);
    }
    return false;
}

// 0x0114c880 -- drop the region of a stream that failed to initialise.
// @ 0x0114c880
void SampleRegions::Reset(const unsigned char* pData, unsigned int length)
{
    char ok = 1;
    if (pData[0] == 0)
        ok = Init(pData, length);
    if (ok != 0)
    {
        mStart = 0;
        mBlockPos = 0;
        mTail = 0;
        mOffset = 0;
        mFlags = 0;
    }
}

// ---------------------------------------------------------------------------
// 0x0114c8c0 -- fixed-size slot pool living in the same allocation as the
// owner: mArrayOffset points at the slot array, mNext/mWrapAt/mFlushAt keep the
// ring cursor, and the owner is told about every new slot.
// ---------------------------------------------------------------------------
struct PlaybackSlot
{
    /* 0x00 */ void* mpData;
    /* 0x04 */ int mOffset;
    /* 0x08 */ int mLength;
    /* 0x0c */ int mState;
    /* 0x10 */ uint8_t mChannel;
    /* 0x11 */ uint8_t mFlags;
    /* 0x12 */ uint16_t mPad12;
};

class SlotPool
{
public:
    virtual void OnSlotAdded(unsigned int index) = 0;

    unsigned char AddSlot(void* pData, int state, uint8_t channel, int length, int offset,
                          uint8_t flags);

    /* 0x04 */ uint8_t mPad04[0x18];
    /* 0x1c */ int mLastLength;
    /* 0x20 */ uint8_t mPad20[4];
    /* 0x24 */ int mArrayOffset;
    /* 0x28 */ uint8_t mPad28[7];
    /* 0x2f */ uint8_t mNextSlot;
    /* 0x30 */ uint8_t mPad30;
    /* 0x31 */ uint8_t mFlushSlot;
    /* 0x32 */ uint8_t mWrapSlot;
    /* 0x33 */ uint8_t mPad33;
};

// @ 0x0114c8c0
unsigned char SlotPool::AddSlot(void* pData, int state, uint8_t channel, int length, int offset,
                                uint8_t flags)
{
    unsigned char index = mNextSlot;
    PlaybackSlot* pSlot =
        (PlaybackSlot*)((unsigned char*)this + mArrayOffset + (unsigned int)index * 0x14);
    if (pSlot->mState != 0)
        return 0;

    pSlot->mpData = pData;
    pSlot->mOffset = offset;
    pSlot->mLength = length;
    pSlot->mState = state;
    pSlot->mChannel = channel;
    pSlot->mFlags = flags;

    OnSlotAdded(index);
    if (mNextSlot == mFlushSlot)
        mLastLength = pSlot->mLength;
    if (++mNextSlot >= mWrapSlot)
        mNextSlot = 0;
    return index;
}

// ---------------------------------------------------------------------------
// Mix target (the block at +0x30000) and its per-channel planar float buffer.
// ---------------------------------------------------------------------------
struct MixBuffer
{
    /* 0x00 */ void* mpOwner;
    /* 0x04 */ float* mpData;
    /* 0x08 */ int mSize;
    /* 0x0c */ uint16_t mPad0c;
    /* 0x0e */ uint16_t mStride;
};

// The mixer object every render step is handed.  The state a step publishes for
// the consumer lives at +0x30000 inside it, which is why the original code
// touches the fields below at those offsets.
struct MixTarget
{
    /* 0x00000 */ uint8_t mPad00[0x30000];
    /* 0x30000 */ double mPosition;
    /* 0x30008 */ uint8_t mPad08[4];
    /* 0x3000c */ MixBuffer* mpMixIn;
    /* 0x30010 */ MixBuffer* mpMixOut;
    /* 0x30014 */ uint8_t mPad14[4];
    /* 0x30018 */ struct SampleRateInfo* mpRate;
    /* 0x3001c */ uint8_t mPad1c[4];
    /* 0x30020 */ int mFrames;
    /* 0x30024 */ float mOutRate;
    /* 0x30028 */ float mSweepHz;
    /* 0x3002c */ uint8_t mChannels;
    /* 0x3002d */ uint8_t mPad2d[3];

    void SwapBuffers()
    {
        MixBuffer* pOld = mpMixOut;
        mpMixOut = mpMixIn;
        mpMixIn = pOld;
    }
};

struct SampleRateInfo
{
    /* 0x00 */ uint8_t mPad00[0xc];
    /* 0x0c */ float mSampleRate;
};

// Bookkeeping the pitched voice polls while it queues blocks.
struct QueueState
{
    /* 0x00 */ int mPad00[3];
    /* 0x0c */ int mRemaining;
};

// The queued block a pitched voice reads sample data from.
struct QueuedBlock
{
    int Read(void* pDst, int count);
};

// One entry of the pitched voice's region table (0x30 bytes).
struct Region
{
    /* 0x00 */ double mTime;
    /* 0x08 */ QueuedBlock* mpBlock;
    /* 0x0c */ float mGain;
    /* 0x10 */ float mRate;
    /* 0x14 */ int mLength;
    /* 0x18 */ int mLoopStart;
    /* 0x1c */ int mChunkLength;
    /* 0x20 */ int mLoopOffset;
    /* 0x24 */ int mLoopLength;
    /* 0x28 */ uint16_t mAlignment;
    /* 0x2a */ uint8_t mState;
    /* 0x2b */ uint8_t mSourceChannel;
    /* 0x2c */ uint8_t mPad2c[4];
};

// One output channel slot of the pitched voice.
struct ChannelSlot
{
    /* 0x00 */ int mWritten;
    /* 0x04 */ uint8_t mSourceChannel;
    /* 0x05 */ uint8_t mState;
    /* 0x06 */ uint8_t mPad06[10];
};

struct PitchedVoice
{
    /* 0x00 */ void* mpVtbl;
    /* 0x04 */ QueueState** mppQueue;
    /* 0x08 */ uint8_t mPad08[0x19];
    /* 0x21 */ uint8_t mChannels;
    /* 0x22 */ uint8_t mPad22[0x42];
    /* 0x64 */ ChannelSlot mSlots[19];
    /* 0x194 */ uint8_t mPad194[8];
    /* 0x19c */ QueuedBlock* mpQueued;
    /* 0x1a0 */ float mGain;
    /* 0x1a4 */ float mSlotRate;
    /* 0x1a8 */ int mQueuedLength;
    /* 0x1ac */ int mChunkLength;
    /* 0x1b0 */ uint8_t mPad1b0[0xc];
    /* 0x1bc */ float mLastRate;
    /* 0x1c0 */ uint16_t mMaxSamples;
    /* 0x1c2 */ uint16_t mOutOffset;
    /* 0x1c4 */ uint16_t mRegionOffset;
    /* 0x1c6 */ uint8_t mMaxChannels;
    /* 0x1c7 */ uint8_t mPad1c7[2];
    /* 0x1c9 */ uint8_t mRegionIndex;
    /* 0x1ca */ uint8_t mPad1ca;
    /* 0x1cb */ uint8_t mbDone;
    /* 0x1cc */ uint8_t mbHold;
    /* 0x1cd */ uint8_t mFirstChannel;
    /* 0x1ce */ uint8_t mCurrentChannel;

    Region* CurrentRegion()
    {
        return (Region*)((unsigned char*)this + mRegionOffset + (unsigned int)mRegionIndex * 0x30);
    }

    int Restart(MixTarget* pMix);
    bool FindPosition(MixTarget* pMix, double position, unsigned int* pOffset);
    void StopCurrent();
    bool HasSource(unsigned char index);
};

extern int GetSourceLength(unsigned char index);

int RenderPitchedVoice(PitchedVoice* pVoice, MixTarget* pMix);

// 0x0114bce0 -- render one mix step of a pitched voice.
// @ 0x0114bce0
int RenderPitchedVoice(PitchedVoice* pVoice, MixTarget* pMix)
{
    if (pVoice->mbHold != 0 && pVoice->mbDone != 0)
        return pVoice->Restart(pMix);

    Region* pRegion = pVoice->CurrentRegion();
    pVoice->mpQueued = 0;
    unsigned int found = 0;
    int srcPos = 0;
    unsigned int queueSave = 0;
    unsigned int queueLeft = 0;
    int copied = 0;

    if (pRegion->mState == 4 || pRegion->mState == 0)
        goto done;

    while (pRegion->mLength == 0)
    {
        pRegion->mState = 4;
        pVoice->StopCurrent();
        pRegion = pVoice->CurrentRegion();
        if (pRegion->mState == 4 || pRegion->mState == 0)
            goto done;
    }

    if (pRegion->mRate != pVoice->mLastRate || pRegion->mSourceChannel != pVoice->mChannels)
    {
        pMix->mFrames = 0;
        pMix->mChannels = pRegion->mSourceChannel;
        pMix->mOutRate = pRegion->mRate;
        pVoice->mLastRate = pRegion->mRate;
        pVoice->mChannels = pRegion->mSourceChannel;
        return 1;
    }

    if (pVoice->mSlots[pVoice->mCurrentChannel].mState == 0)
    {
        unsigned char channel = pVoice->mCurrentChannel;
        while (channel != pVoice->mFirstChannel)
        {
            if (++channel == 0x14)
                channel = 0;
            pVoice->mCurrentChannel = channel;
            if (pVoice->mSlots[channel].mState != 0)
                break;
        }
    }
    if (pVoice->mSlots[pVoice->mCurrentChannel].mState != 1)
        goto done;

    if (pRegion->mTime != 0.0)
    {
        if (!pVoice->FindPosition(pMix, pRegion->mTime, &found))
        {
            pVoice->mQueuedLength = 0;
            goto done;
        }
        if (found != 0)
        {
            int count = (int)found;
            if (count >= (int)pVoice->mMaxSamples)
                count = pVoice->mMaxSamples;
            MixBuffer* pBuf = pMix->mpMixOut;
            queueSave = (unsigned int)pBuf;
            for (int i = 0; i < pRegion->mSourceChannel; ++i)
                memset(pBuf->mpData + pBuf->mStride * i, 0, count * 4);
            pMix->SwapBuffers();
            pMix->mFrames = count;
            pMix->mChannels = pRegion->mSourceChannel;
            pMix->mOutRate = pRegion->mRate;
            pVoice->mQueuedLength = 0;
            return 1;
        }
        pRegion->mTime = 0.0;
    }

    QueueState* pQueue = *pVoice->mppQueue;
    int remaining = pQueue->mRemaining;
    queueSave = (unsigned int)remaining;
    remaining -= (pRegion->mAlignment + 0x7f) & ~0x7f;
    pQueue->mRemaining = remaining;
    queueLeft = (unsigned int)remaining;
    pVoice->mpQueued = pRegion->mpBlock;

    int available = GetSourceLength(pVoice->mSlots[pVoice->mCurrentChannel].mSourceChannel);
    int take = pRegion->mChunkLength;
    if (available < take)
        take = available;
    available -= take;
    srcPos = (int)pVoice->mMaxSamples;
    if (srcPos >= available)
        srcPos = available;

    MixBuffer* pBuf = pMix->mpMixOut;
    while (take != 0)
    {
        int chunk = take < 0x100 ? take : 0x100;
        take -= chunk;
        copied += pVoice->mpQueued->Read(pBuf->mpData, chunk);
    }
    int written = pVoice->mpQueued->Read(pBuf->mpData, srcPos);
    pMix->SwapBuffers();
    pMix->mFrames = written;
    pMix->mChannels = pRegion->mSourceChannel;
    pMix->mOutRate = pRegion->mRate;
    pVoice->mGain = pRegion->mGain;
    if (pVoice->mQueuedLength == 0)
        pVoice->mQueuedLength = pRegion->mLoopLength + pRegion->mLoopOffset;
    pVoice->mQueuedLength += written + copied;
    pVoice->mSlotRate = pRegion->mRate;
    pVoice->mChunkLength = pRegion->mLength;
    pVoice->mSlots[pVoice->mCurrentChannel].mWritten += written + copied;

    unsigned int left = (unsigned int)(available - (written + copied));
    if (pVoice->mQueuedLength == pRegion->mLength)
    {
        if (pRegion->mLoopStart >= 0)
        {
            pVoice->mQueuedLength = pRegion->mLoopStart;
        }
        else
        {
            pRegion->mState = 4;
            if (pVoice->mpQueued != 0)
            {
                pVoice->mpQueued = 0;
                (*pVoice->mppQueue)->mRemaining = (int)queueSave;
            }
            pVoice->StopCurrent();
            pRegion = pVoice->CurrentRegion();
            if (pVoice->HasSource(pRegion->mState) && pRegion->mpBlock != 0)
            {
                int remaining2 = (*pVoice->mppQueue)->mRemaining;
                queueSave = (unsigned int)remaining2;
                remaining2 -= (pRegion->mAlignment + 0x7f) & ~0x7f;
                (*pVoice->mppQueue)->mRemaining = remaining2;
                queueLeft = (unsigned int)remaining2;
                pVoice->mpQueued = pRegion->mpBlock;
            }
        }
    }

    if (left == 0)
    {
        do
        {
            if (pVoice->mSlots[pVoice->mCurrentChannel].mState != 1)
                break;
            pVoice->mSlots[pVoice->mCurrentChannel].mState = 2;
            unsigned char channel = pVoice->mCurrentChannel + 1;
            if (channel == 0x14)
                channel = 0;
            pVoice->mCurrentChannel = channel;
            if (pVoice->mpQueued != 0 && pVoice->mSlots[channel].mState == 1)
            {
                left = (unsigned int)GetSourceLength(pVoice->mSlots[channel].mSourceChannel);
                srcPos = (int)left;
            }
        } while (left == 0);
    }

done:
    if (pVoice->mpQueued != 0)
    {
        pVoice->mpQueued = 0;
        if (queueLeft != 0)
            (*pVoice->mppQueue)->mRemaining = (int)queueSave;
    }
    pMix->mChannels = pVoice->mChannels;
    pMix->mOutRate = pVoice->mLastRate;
    if (srcPos != 0)
    {
        MixBuffer* pBuf = pMix->mpMixIn;
        int channels = pVoice->mMaxChannels < pVoice->mChannels ? pVoice->mMaxChannels : pVoice->mChannels;
        float* pDst = (float*)((unsigned char*)pVoice + pVoice->mOutOffset);
        int i = 0;
        for (; i + 3 < channels; i += 4)
        {
            pDst[i + 0] = pBuf->mpData[pBuf->mStride * (i + 0) + srcPos - 1];
            pDst[i + 1] = pBuf->mpData[pBuf->mStride * (i + 1) + srcPos - 1];
            pDst[i + 2] = pBuf->mpData[pBuf->mStride * (i + 2) + srcPos - 1];
            pDst[i + 3] = pBuf->mpData[pBuf->mStride * (i + 3) + srcPos - 1];
        }
        for (; i < channels; ++i)
            pDst[i] = pBuf->mpData[pBuf->mStride * i + srcPos - 1];
        pVoice->mbDone = 1;
        return 1;
    }
    if (copied != 0 || pVoice->mMaxSamples != 0)
    {
        pMix->mFrames = 0;
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x0114c950 -- copy the six vibrato/LFO parameter planes into the target's
// mix buffer (one 0x400-byte plane per channel entry) and swap buffers.
// ---------------------------------------------------------------------------
struct VibratoBuffers
{
    /* 0x00 */ uint8_t mPad00[0x40];
    /* 0x40 */ void* mpPlane0;
    /* 0x44 */ void* mpPlane1;
    /* 0x48 */ void* mpPlane4;
    /* 0x4c */ void* mpPlane3;
    /* 0x50 */ void* mpPlane5;
    /* 0x54 */ void* mpPlane2;
};

// @ 0x0114c950
int CopyVibratoBuffers(VibratoBuffers* pVoice, MixTarget* pMix)
{
    MixBuffer* pBuf = pMix->mpMixOut;
    memcpy(pBuf->mpData, pVoice->mpPlane5, 0x400);
    memcpy(pBuf->mpData + pBuf->mStride, pVoice->mpPlane0, 0x400);
    memcpy(pBuf->mpData + pBuf->mStride * 2, pVoice->mpPlane1, 0x400);
    memcpy(pBuf->mpData + pBuf->mStride * 3, pVoice->mpPlane3, 0x400);
    memcpy(pBuf->mpData + pBuf->mStride * 4, pVoice->mpPlane4, 0x400);
    memcpy(pBuf->mpData + pBuf->mStride * 5, pVoice->mpPlane2, 0x400);
    pMix->SwapBuffers();
    return 1;
}

// ---------------------------------------------------------------------------
// 0x0114ca30 -- sin-LFO renderer: one sine sweep over the block, silent until
// the sweep reaches the region start time.
// ---------------------------------------------------------------------------
struct LfoVoice
{
    /* 0x00 */ uint8_t mPad00[0x21];
    /* 0x21 */ uint8_t mChannels;
    /* 0x22 */ uint8_t mPad22[6];
    /* 0x28 */ double mStartTime;
    /* 0x30 */ float mRate;
    /* 0x34 */ uint8_t mPad34[4];
    /* 0x38 */ float mPhase;
    /* 0x3c */ uint8_t mbEnabled;
    /* 0x3d */ uint8_t mPad3d[3];
    /* 0x40 */ int mFrames;
};

// @ 0x0114ca30
int RenderLfo(LfoVoice* pVoice, MixTarget* pMix)
{
    MixBuffer* pBuf = pMix->mpMixOut;
    pMix->mFrames = pVoice->mFrames;
    pMix->mChannels = pVoice->mChannels;
    pMix->mOutRate = pMix->mpRate->mSampleRate;

    if (pVoice->mbEnabled == 0)
        return 0;

    float step = pMix->mSweepHz / pMix->mpRate->mSampleRate * pVoice->mRate * 6.2831855f;
    for (int i = 0; i < pVoice->mFrames; ++i)
    {
        if (1.0 / pMix->mpRate->mSampleRate * i + pMix->mPosition < pVoice->mStartTime)
        {
            for (unsigned int ch = 0; ch < pVoice->mChannels; ++ch)
                pBuf->mpData[pBuf->mStride * ch + i] = 0.0f;
        }
        else
        {
            for (unsigned int ch = 0; ch < pVoice->mChannels; ++ch)
                pBuf->mpData[pBuf->mStride * ch + i] = sinf(pVoice->mPhase);
        }
        pVoice->mPhase += step;
        if (pVoice->mPhase >= 6.2831855f)
            pVoice->mPhase -= 6.2831855f;
    }
    pMix->SwapBuffers();
    return 1;
}

} // namespace core
} // namespace audio
} // namespace rw
