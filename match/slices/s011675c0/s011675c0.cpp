// @ 0x011675c0 : flip the sign of two floats (+0x14, +0x1c) in each of the 9 cells of each of the 8 rows
#include "types.h"
#include <xmmintrin.h>

struct Cell { float f[8]; };
struct Row { Cell c[9]; };

// Written out per cell: a nested 9-iteration loop does not reproduce the original's 4x outer unroll.
#define NEGATE_CELL(i) r->c[i].f[5] *= -1.0f; r->c[i].f[7] *= -1.0f;

void NegateRows(Row* rows)
{
    Row* end = (Row*)((char*)rows + 0x900);
    for (Row* r = rows; r < end; ++r)
    {
        NEGATE_CELL(0) NEGATE_CELL(1) NEGATE_CELL(2)
        NEGATE_CELL(3) NEGATE_CELL(4) NEGATE_CELL(5)
        NEGATE_CELL(6) NEGATE_CELL(7) NEGATE_CELL(8)
    }
}

// ---------------------------------------------------------------------------
// Quantised height-field block codec lives in heightcodec.h; this translation
// unit holds the base-class implementation (the derived block class is in
// s011675c0_block.cpp, which is why its destructor calls the base one).
// ---------------------------------------------------------------------------

#include "heightcodec.h"

// @ 0x011680f0
void cHeightCodec::SetHandle(unsigned handle)
{
    mpSourceData = (const unsigned char*)handle;
    mSourceCopy = handle;
    mCursor = handle;
    mCursorOffset = 0;
    mCursorExtra = 0;
}

// @ 0x01168110
cHeightCodec::cHeightCodec()
{
    mInited = 0;
    mHandle4c = 0;
}

// @ 0x01168130
void cHeightCodec::AllocBlocks()
{
    if (g_compactBlocks != 0) {
        mpData = g_alloc_016f16ec(mBlockCount * 0x480);
        MemSet(mpData, 0, mBlockCount * 0x480);
    } else {
        mpData = g_alloc_016f16ec(mBlockCount * 0x900);
        MemSet(mpData, 0, mBlockCount * 0x900);
    }
}

// @ 0x01168190
int cHeightCodec::Decode(unsigned desc)
{
    if ((desc & 0xffe00000) != 0xffe00000)
        return -1;

    unsigned char dim = (unsigned char)(4 - ((desc >> 0x11) & 3));
    unsigned char bit9 = (unsigned char)((desc >> 9) & 1);
    mBit42 = bit9;
    unsigned char type43 = (unsigned char)((desc >> 6) & 3);
    mType43 = type43;
    mCellDim = dim;
    mType44 = (unsigned char)((desc >> 4) & 3);
    mBit3f = (unsigned char)((desc >> 0x10) & 1);
    mBit45 = (unsigned char)((desc >> 3) & 1);
    unsigned char nibble40 = (unsigned char)((desc >> 0xc) & 0xf);
    mBit3e = (unsigned char)((desc >> 0x13) & 1);
    mNibble40 = nibble40;
    mBit46 = (unsigned char)((desc >> 2) & 1);

    if ((desc & 0x100000) != 0) {
        mMode3b = (unsigned char)(((desc >> 0x13) & 1) == 0);
        mMode3a = 0;
    } else {
        mMode3b = 1;
        mMode3a = 1;
    }

    int type10 = (desc >> 0xa) & 3;
    unsigned char mode3c;
    if (mMode3a != 0) {
        mode3c = (unsigned char)(type10 + 6);
        mIndex41 = mode3c;
    } else {
        mIndex41 = (unsigned char)(mMode3b * 3 + type10);
        mode3c = (unsigned char)((mMode3b ? 3 : 0) + type10);
    }
    mMode3c = mode3c;

    mBlockCount = (unsigned char)((type43 != 3) + 1);
    unsigned size = g_sizeTable[mIndex41];
    mSize08 = size;
    mSize04 = size;

    if (nibble40 == 0)
        return -1;

    unsigned char mode3b = mMode3b;
    int blockSize = g_spanTable[((mode3b * 3 + dim) << 4) + nibble40];
    mBlockSize = blockSize;

    if (dim == 1) {
        mComputedSize = (blockSize * 0x2ee0 / (int)mSize04 + bit9) * 4 - 4;
        return 0;
    }

    int computed = blockSize * 0x23280 / (int)mSize04;
    mComputedSize = computed;
    if (dim == 3 && mode3b != 0)
        mComputedSize = computed >> 1;
    if (bit9 != 0)
        ++mComputedSize;
    mComputedSize += -4;
    return 0;
}

// @ 0x01168330
int cHeightCodec::ResolveSource()
{
    int result;
    if (mpSourceData == 0) {
        unsigned id = mHandle4c;
        void** vt = *(void***)this;
        result = ((int (__thiscall*)(cHeightCodec*, unsigned))vt[1])(this, id);
    } else {
        unsigned value = mpSourceData[1] + ((unsigned)mpSourceData[0] << 8);
        value = (value << 8) + mpSourceData[2];
        value = (value << 8) + mpSourceData[3];
        void** vt = *(void***)this;
        result = ((int (__thiscall*)(cHeightCodec*, unsigned))vt[1])(this, value);
    }
    return (result + 1 != 0) - 1;
}

// @ 0x011683d0
void cHeightCodec::CopyHandle()
{
    mCursor = (unsigned)mpSourceData;
    mCursorOffset = 0;
    mCursorExtra = 0;
}

// @ 0x01168400
cHeightCodec::~cHeightCodec()
{
    if (mInited != 0) {
        mHandle4c = 0;
        mInited = 0;
        g_free_016f16f4(mpData);
    }
}

// @ 0x01168420 is the compiler-generated scalar deleting destructor of cHeightCodec

// @ 0x01168460
int cHeightCodec::Init(unsigned handle, unsigned unused)
{
    if (mInited != 0)
        ReleaseSource();
    mInited = 1;
    mpSourceData = (const unsigned char*)handle;
    mSourceCopy = handle;
    if (handle == 0)
        return -1;
    if (ResolveSource() != 0)
        return -1;
    AllocBlocks();
    OnAllocated();
    mCursor = (unsigned)mpSourceData;
    mCursorOffset = 0;
    mCursorExtra = 0;
    return 0;
}

// @ 0x011684c0
int ReadBigEndian(const unsigned char* data, int count)
{
    int value = 0;
    int n = count;
    const unsigned char* p = data;
    while (count != 0) {
        --count;
        value = (value << 8) + *p;
        ++p;
    }
    if (n == 1) {
        if (value > 0x7f)
            value -= 0x100;
    } else if (n == 2) {
        if (value > 0x7fff)
            value -= 0x10000;
    } else if (n == 3 && value > 0x7fffff) {
        value -= 0x1000000;
    }
    return value;
}

// The packed heights are rounded to the nearest fixed-point step, not truncated.
static __forceinline short ToFixed14(float value)
{
    return (short)_mm_cvtss_si32(_mm_set_ss(value));
}

// Written out per row: a nested loop does not reproduce the original's 8x unroll.
#define PACK_ROW(r) \
    out[(r) * 4 + 0] = ToFixed14(src[(r) * 72 + 0]); \
    out[(r) * 4 + 1] = ToFixed14(src[(r) * 72 + 1]); \
    out[(r) * 4 + 2] = ToFixed14(src[(r) * 72 + 2]); \
    out[(r) * 4 + 3] = ToFixed14(src[(r) * 72 + 3]);

// @ 0x01167cf0
void PackHeightBlock(const float* src, short* dst)
{
    short* end = dst + 576;
    for (short* out = dst; out < end; out += 32, src += 4) {
        PACK_ROW(0)
        PACK_ROW(1)
        PACK_ROW(2)
        PACK_ROW(3)
        PACK_ROW(4)
        PACK_ROW(5)
        PACK_ROW(6)
        PACK_ROW(7)
    }
}
