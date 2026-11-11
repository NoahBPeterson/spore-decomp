// Slice s00898ce0 -- construct the "report" object: fill two eastl::vector
// headers in place through the 5-argument init at 0x00921260; the first one is
// [this+0x1c] with allocator 0 and no arena argument, the second [this+8] with
// the arena pointer the caller handed in (and arena+0x100 as its capacity
// field); both are made self-referential (empty) at the end.
//
// Attempt (no byte match; residual in nonmatching.txt): the 5-argument
// prototype below is the only readable shape found; the original also fills a
// 0x14-byte stack temporary parent (its first field 0), which the source cannot
// name yet.

#include "game/types.h"

// Flags: /O2 /MD /Gy /EHsc /TP /Isrc/game/include

struct ElemVec                   // eastl::vector<0x10-byte element>
{
    void*    mpLink;             // +0x00  self-pointer when empty
    void*    mpBegin;            // +0x04
    void*    mpEnd;              // +0x08
    void*    mpCapacity;         // +0x0c
    void*    mpAlloc;            // +0x10
    uint32_t mCapacity2;         // +0x14

    void Init(void* begin, int count, int elemSize, void* alloc, int flags);  // 0x00921260
};

struct Report
{
    ElemVec* mpLink0;            // +0x00
    ElemVec* mpLink1;            // +0x04
    ElemVec  mVec;               // +0x08
    ElemVec  mSub;               // +0x1c

    Report* Build(void* arena);  // 0x00898ce0
};

// @ 0x00898ce0
Report* Report::Build(void* arena)
{
    mSub.Init(&mSub, 0x100, 0x10, 0, (int)4);
    mVec.Init(arena, 0x100, 0x10, 0, (int)4);
    mVec.mpAlloc = arena;
    mVec.mpCapacity = (char*)arena + 0x100;
    mVec.mCapacity2 = 0x10;
    mSub.mpLink = this;
    mVec.mpLink = this;
    return this;
}
