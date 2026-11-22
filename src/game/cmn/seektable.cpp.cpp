// src/game/cmn/seektable.cpp.cpp -- migrated from slice(s) s0114bce0 by tools/migrate/rewrite.py
// Object file: cmn/seektable.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.
// The functions of this object are free functions of rw::audio::core with no canonical declaration; they are landed
// verbatim with their slice-local types (TODO(rewrite): replace by canonical classes when they get headers).
// TODO(rewrite): local stubs, replace by canonical classes

#include "game/types.h"

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

    bool ScanPacked(const unsigned char* pData, unsigned int length);
};

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

} // namespace core
} // namespace audio
} // namespace rw
