// Slice s00508fd0, file B header: the types behind the 0x00508fd0 table
// builder in s00508fd0_builderA.cpp. Lives beside the slice sources so the
// callee declarations' `// 0x...` annotations are in the annotation scan
// (slice *.h files).
//
// The retail body (`?Build@MPT@@QAEXXZ`, 1142 bytes) is reproduced exactly,
// frame included. Its frame map, decoded from the disassembly and confirmed
// slot-for-slot against this build:
//
//   -0x004  first            (int)
//   -0x008..-0x020  id[0x18] (24 bytes of frame the body never touches;
//                             declared so the name walk leaves the hole)
//   -0x10c  res              (NWV, 240 bytes: 0xf0)
//   -0x110..-0x134  10 named counters/frame locals
//   -0x138  nodes            (&mNodes cache for the first Resize)
//   -0x13c..-0x148  4 dead dwords
//   -0x149  cur              (AL, 1 byte; the scratch ctor's allocator)
//   -0x150  mParts recv
//   -0x154  mNodes Resize recv
//   -0x158..-0x160  3 dead dwords
//   -0x164  Clear recv
//   -0x168  baseEnd          (FillPairs end bound = mpEnd)
//   -0x16c  base             (FillPairs start bound = mpBegin)
//   -0x170  p                (FillPairs cursor)
//   -0x174  elem recv        (&dst->mNodes, per-node loop)
//   -0x178..-0x190  6 dead dwords
//   -0x190  psd              (&mSlotData[ok])
//   -0x194  ps8              (&mSlots80[ok])
//   -0x198  mRecs recv
//   -0x19c  mSlots6c recv
//   -0x1a0  sweep iter
//   -0x1a4  this
//
// The dead dwords come from the s004057b0 recipe: unused locals inside a
// __forceinline helper body allot at the expansion's position, in body order.

#pragma once

#include "../../include/types.h"

// the allocator blob handed to the scratch vector's constructor
struct AL {
    char mState;
};

struct MPT;

// the 12-byte node-weight record
struct NW {
    int mId;
    int mSlotData;
    int mSlot;
};

// 12-byte-record vector header (0x18 bytes: the elements' mRecs at +0x80
// and this->mNodes at +0x08 are this shape). align(4) matters: the 0xf0-byte
// local takes an 8-aligned slot without it, but retail's sits on a 4.
struct __declspec(align(4)) NWB {
    NW*   mpBegin;                    // +0x00
    NW*   mpEnd;                      // +0x04
    NW*   mpCap;                      // +0x08
    int   mF0c;                       // +0x0c
    int   mF10;                       // +0x10
    int   mF14;                       // +0x14

    void Erase(NW* first, NW* last);              // 0x000050f740
    void Copy(const NWB& x);                      // 0x000050dea0
    void Dtor();                                  // 0x00005156b0
    unsigned Count() { return ((char*)mpEnd - (char*)mpBegin) / 12; }

    // the element's record-list clear; its expansion reserves the three dead
    // dwords at -0x158..-0x160, which sit after the receiver home
    __forceinline void Clear() {
        unsigned v0, v1, v2;
        Erase(mpBegin, mpEnd);
    }

    // the fill-path record writes. One field per helper, so each element
    // address is computed at its own use site: retail stores mId, then
    // computes &mSlotData[ok] and stores, then &mSlots80[ok] and stores.
    // Passing the address as a forceinlined argument is what keeps the two
    // operator[] element-address temps (-0x190 psd, -0x194 ps8) in the frame.
    __forceinline void SetSlotData(int* p) { mpEnd[-1].mSlotData = *p; }
    __forceinline void SetSlot(int* p) { mpEnd[-1].mSlot = *p; }
};

// the header plus inline storage (the local scratch builder, 0xf0 bytes)
struct NWV : NWB {
    NW mStorage[0xd8 / 12];           // +0x18..+0xef

    void Ctor(const AL& alloc);       // 0x0000540470
    void Init();                      // 0x000050cf70
    void Add();                       // 0x000041ffc0

    // the ctor+init pair. The allocator local is `cur`: declaring it inside
    // this forceinlined body is what puts its 1-byte slot at -0x149, inside
    // the temp region rather than among Build's own locals.
    __forceinline void Create() {
        AL cur;
        Ctor(cur);
        Init();
    }

    // count-then-append. The six unused locals stand in for the six dead
    // dwords at -0x178..-0x190 that retail's expansion of this count leaves
    // between the elem-loop receiver and the Set argument homes.
    __forceinline unsigned TakeSlot() {
        unsigned d0, d1, d2, d3, d4, d5;
        return Count();
    }

    // the scratch sweep before the dtor: an empty 12-byte stride walk
    __forceinline void Sweep() {
        for (NW* p = mpBegin; p < mpEnd; p += 1) {}
    }
};

// int-record vector with an out-of-line resize (the element's per-node
// tables: mNodes at +0x08 and mSlots6c at +0x6c)
struct IdVec {
    int*   mpBegin;                   // +0x00
    int*   mpEnd;                     // +0x04
    int*   mpCap;                     // +0x08
    unsigned mAlloc[2];               // +0x0c

    void Resize(unsigned n);          // 0x00004cd3c0
    int Count() { return mpEnd - mpBegin; }
};

// int list with an inline subscript (the MPT's per-corner id tables at
// +0x58/+0x6c/+0x80, 0x14 bytes each); the subscript materialises the
// element address as the return temp, which is what spills in the fill path
struct IdList {
    int*   mpBegin;                   // +0x00
    int*   mpEnd;                     // +0x04
    int*   mpCap;                     // +0x08
    unsigned mAlloc[2];               // +0x0c

    __forceinline int& operator[](unsigned i) { return mpBegin[i]; }
};

// one row of two half slots, selected by (half id & 1)
struct Pair {
    int mSlot[2];
    __forceinline int& At(unsigned col) { return mSlot[col]; }
};

// the base pair table (this+0x1b8)
struct PairTab {
    Pair* mpBegin;                    // +0x00
    Pair* mpEnd;                      // +0x04
    Pair* mpCap;                      // +0x08

    void Resize(unsigned n);          // 0x000050da10
};

// one element of the +0xe4 part list
struct SkinBuildData {
    unsigned mIndex;                  // +0x00
    unsigned mf04;                    // +0x04
    IdVec    mNodes;                  // +0x08 per-node ids
    char     pad20[0x6c - 0x1c];
    IdVec    mSlots6c;                // +0x6c per-corner slot table
    NWB      mRecs;                   // +0x80 built node-weight records
    char     pad98[0xe4 - 0x98];
};

// pointer-element vector (the SkinBuildData* list)
struct PtrVec {
    SkinBuildData** mpBegin;          // +0x00
    SkinBuildData** mpEnd;            // +0x04
    SkinBuildData** mpCap;            // +0x08
    unsigned Count() { return mpEnd - mpBegin; }
};

// the object; only the members this body touches are named
struct MPT {
    char pad00[0x08];
    NWB     mNodes;                   // +0x08 12-byte-record vector
    char pad20[0x58 - 0x20];
    IdList  mIds;                     // +0x58 per-corner id list (ends +0x6c)
    IdList  mSlotData;                // +0x6c per-corner slot data (ends +0x80)
    IdList  mSlots80;                 // +0x80 per-corner slot table (ends +0x94)
    char pad94[0x50];
    PtrVec  mParts;                   // +0xe4 SkinBuildData* list
    char padf0[0x1c];
    int  mTotal;                      // +0x10c
    char pad110[0xa8];
    PairTab mBaseTabTab;              // +0x1b8 (half-id -> pair) table

    void Build();

    // the base-table fill. Two things are load-bearing:
    //  * the locals are declared here (inside a forceinlined helper) rather
    //    than in Build, which is what allots them in the temp region at
    //    -0x168/-0x16c/-0x170 instead of among Build's own locals;
    //  * `base` takes the higher slot (-0x16c) and `baseEnd` the one below
    //    (-0x168) -- the /Od name walk, not the semantics, decides this, so
    //    the loop's end bound lives in `base` and its start in `baseEnd`.
    // The parameter is a const reference, not a value: retail copies the
    // record as a block (both halves loaded, then the cursor, then both
    // stores), which only the reference spelling produces here.
    __forceinline void FillPairs(const Pair& fill) {
        Pair* baseEnd;
        Pair* base;
        base = mBaseTabTab.mpEnd;
        baseEnd = mBaseTabTab.mpBegin;
        for (Pair* p = baseEnd; p != base; p += 1)
            *p = fill;
    }
};
