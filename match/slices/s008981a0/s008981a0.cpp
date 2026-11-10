// Slice s008981a0: EA::Text run-array cursor (the dev public is a bare 0x008981a0;
// the shape is a ValueFlagPair member that advances over an array of 8-byte runs).
// Flags: /O2 /MD /Gy /TP
#include "types.h"
#include <intrin.h>

typedef unsigned int u32;

// One run of a LineLayout: byte 0 carries the run kind, bit 0x10 "has a value".
struct Run {
    unsigned char mKind;                // +0x00
    unsigned char mPad[7];

    bool HasFlag10() const { return (mKind & 0x10) != 0; }
};

// A LineLayout's run array lives in an eastl vector at +0x40 (begin/end).
struct LineLayout {
    u32   mPad00[0x40 / 4];
    Run*  mpBegin;                      // +0x40
    Run*  mpEnd;                        // +0x44
};

struct ValueFlagPair {
    LineLayout* mpValue;                // +0x00
    u32         mFlag;                  // +0x04  current run index

    bool Next(int* pIndex);
};

// @ 0x008981a0
// Advances the cursor to the next run whose flags byte has 0x10;
// returns false (and clamps the index to the end) when there is none.
bool ValueFlagPair::Next(int* pIndex)
{
    u32 i = mFlag;
    LineLayout* layout = mpValue;
    u32 count = (u32)(layout->mpEnd - layout->mpBegin);
    _ReadWriteBarrier();
    if (i < count) {
        Run* run = layout->mpBegin + i;
        do {
            if (run->HasFlag10()) {
                *pIndex = i;
                mFlag = i + 1;
                return true;
            }
            ++i;
            ++run;
        } while (i < count);
    }
    mFlag = count;
    return false;
}
