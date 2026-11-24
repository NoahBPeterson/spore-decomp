// Slice s00508fd0, file B header: the types behind the 0x00508fd0 table
// builder transcription in s00508fd0_builderA.cpp. Lives beside the slice
// sources so the callee declarations' `// 0x...` annotations are in the
// annotation scan (slice *.h files).

#pragma once

#include "../../include/types.h"

// ---------------------------------------------------------------------------
// callees: out-of-line vector members (no bodies here — the retail body
// calls them); the inline helpers carry their real bodies below
// ---------------------------------------------------------------------------

// the allocator blob handed to the scratch vector's constructor
struct AL {
    char mState;
};

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
    __forceinline void Clear() { Erase(mpBegin, mpEnd); }
    // the fill-path record write: the record id and the two per-corner
    // table reads, whose addresses the call materialises as the spill
    // temps retail shows at -0x190/-0x194
    __forceinline void Set(int hdr, int* psd, int* ps8) {
        mpEnd[-1].mId = hdr;
        mpEnd[-1].mSlotData = *psd;
        mpEnd[-1].mSlot = *ps8;
    }
};

// the header plus inline storage (the local scratch builder, 0xf0 bytes)
struct NWV : NWB {
    NW mStorage[0xd8 / 12];           // +0x18..+0xef

    void Ctor(const AL& alloc);       // 0x0000540470
    void Init();                      // 0x000050cf70
    void Add();                       // 0x000041ffc0
    __forceinline void Sweep() { for (NW* p = mpBegin; p < mpEnd; p += 1) {} }
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
// element address as the return temp, which is what spills in the retail
// body's fill path
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
    __forceinline void FillPairs(const Pair& fill) {
        // declared before use so the collision tie-break lands `end` on the
        // higher slot (retail allots end, first, p downward); the initialiser
        // order stays retail's (mpEnd read first)
        Pair* first;
        Pair* end;
        end = mBaseTabTab.mpEnd;
        first = mBaseTabTab.mpBegin;
        for (Pair* p = first; p != end; p += 1)
            *p = fill;
    }
};
