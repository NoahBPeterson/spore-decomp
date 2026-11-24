// Slice s00508fd0, file B: table builder A.
// The matched neighbours live in s00508fd0.cpp; this file transcribes the
// PARTIAL stub from partial.txt directly out of the disassembly.
//
// @ 0x00508fd0
//
// Object = SP::MeshPaintTarget (the cSkinObject +0x34 mesh holder, see
// src/game/SPBake/_at_004c0000.cpp). The body is integer /Od code: no
// floats, no vtables, no EH. Retail frame 0x1a4 on a frame pointer. The
// loop state lives in plain locals plus one 0xf0-byte local node-weight
// builder object whose ctor (0x540470) zeroes the vector header and whose
// init (0x50cf70) points begin/end at the inline storage.

#include "../../include/types.h"

// ---------------------------------------------------------------------------
// callees: out-of-line vector members (no bodies here — the retail body
// calls them); the inlined helpers carry their real bodies below
// ---------------------------------------------------------------------------

// the 12-byte node-weight record
struct NodeWeight {
    int mId;
    int mSlotData;
    int mSlot;
};

// 12-byte-record vector with inline storage (the local builder object)
struct NWBuilder {
    NodeWeight* mpBegin;      // +0x00
    NodeWeight* mpEnd;        // +0x04
    NodeWeight* mpCapacity;   // +0x08
    int   mF0c;               // +0x0c
    int   mF10;               // +0x10
    int   mF14;               // +0x14
    NodeWeight mStorage[0xd8 / 12];   // +0x18..+0xef

    void Ctor(char* alloc);            // 0x00540470 (zeroes the header)
    void Init();                       // 0x0050cf70 (points begin/end at storage)
    void Add();                        // 0x0041ffc0 (append one record)
    void Erase(NodeWeight* first, NodeWeight* last);  // 0x0050f740
    void Copy(const NWBuilder& x);     // 0x0050dea0 (operator=)
    void Dtor();                       // 0x005156b0
    unsigned Count() { return mpEnd - mpBegin; }
};

// 12-byte-record vector
struct NWVec {
    NodeWeight* mpBegin;      // +0x00
    NodeWeight* mpEnd;        // +0x04
    NodeWeight* mpCapacity;   // +0x08
    unsigned Count() { return mpEnd - mpBegin; }
};

// the element's record vector (+0x80): out-of-line erase/copy
struct RecVec {
    NodeWeight* mpBegin;
    NodeWeight* mpEnd;
    NodeWeight* mpCapacity;
    void Erase(NodeWeight* first, NodeWeight* last);  // 0x0050f740
    void Copy(const NWBuilder& x);                    // 0x0050dea0
    unsigned Count() { RecVec& v = *this; return v.mpEnd - v.mpBegin; }
};

// int vector
struct IntVec {
    int*   mpBegin;           // +0x00
    int*   mpEnd;             // +0x04
    int*   mpCapacity;        // +0x08
    void Resize(unsigned n);  // 0x004cd3c0
    unsigned Count() { IntVec& v = *this; return v.mpEnd - v.mpBegin; }
};

// one element of the +0xe4 part list (SkinBuildData)
struct SkinBuildData {
    unsigned mIndex;          // +0x00
    unsigned mf04;            // +0x04
    NWVec    mNodes;          // +0x08
    char     pad1c[0x6c - 0x14];
    IntVec   mSlots6c;        // +0x6c
    char     pad80[0x80 - 0x74];
    RecVec   mRecs;           // +0x80
    char     pad94[0xe4 - 0x94];
};

// pointer-element vector (the SkinBuildData* list)
typedef SkinBuildData* SkinBuildDataPtr;
struct PtrVec {
    SkinBuildDataPtr* mpBegin;   // +0x00
    SkinBuildDataPtr* mpEnd;     // +0x04
    SkinBuildDataPtr* mpCapacity;// +0x08
    unsigned Count() { PtrVec& v = *this; return v.mpEnd - v.mpBegin; }
    SkinBuildDataPtr At(unsigned i) { SkinBuildDataPtr* b = mpBegin; return b[i]; }
};

// (half-id -> pair) entry
struct Pair {
    int mSlot;
    int mFill;
};

// reserve helper on the base pair table (out-of-line __thiscall)
struct PairTab {
    void Resize(unsigned n);  // 0x0050da10
};

// the object; only the members this body touches are named
struct MPT {
    char pad00[0x08];
    NWVec   mNodes;           // +0x08 node vector
    char pad14[0x44];
    int*  mIds;               // +0x58 per-corner id list
    char pad5c[0x10];
    int*  mSlotData;          // +0x6c per-corner slot table
    char pad70[0x10];
    int*  mSlots80;           // +0x80 slot table (per-corner)
    char pad84[0x60];
    PtrVec  mParts;           // +0xe4 SkinBuildData* list
    char padf0[0x1c];
    int  mTotal;              // +0x10c
    char pad110[0xa8];
    PairTab mBaseTabTab;      // +0x1b8 (half-id -> pair) table
    Pair* mBaseTabBegin;      // +0x1b8 (same storage, raw view)
    Pair* mBaseTabEnd;        // +0x1bc

    void Build();
};

// @ 0x00508fd0
void MPT::Build()
{
    int p30;
    char p13[0x14];
    NWBuilder t10;
    unsigned prev;
    SkinBuildData* p16;
    int n22;
    int p11;
    int p14;
    int n35;
    int n29;
    int t16;
    int v31;
    int t30;
    int owner;
    char n23;

    p30 = 0;
    mTotal = 0;

    // reserve ((nodeCount/12) + 1) / 2 pairs in the base pair table
    mBaseTabTab.Resize((mNodes.Count() + 1) >> 1);

    // the local record scratch: the ctor zeroes the header, then the
    // NodeWeightVector init points begin/end at the inline storage
    t10.Ctor(&n23);
    t10.Init();

    for (prev = 0; prev < mParts.Count(); ++prev) {
        p16 = mParts.At(prev);
        SkinBuildData* el = p16;

        // reserve 3 * nodeCount node-weight records on the element
        el->mSlots6c.Resize(el->mNodes.Count() * 3u);

        // clear the element's record list, then the scratch
        el->mRecs.Erase(el->mRecs.mpBegin, el->mRecs.mpEnd);
        t10.Erase(t10.mpBegin, t10.mpEnd);

        n22 = -1;
        p11 = n22;
        Pair* baseEnd = mBaseTabEnd;
        Pair* base = mBaseTabBegin;
        for (Pair* p = base; p != baseEnd; ++p) {
            p->mSlot = p11;
            p->mFill = n22;
        }

        // per-node corner loop
        for (p14 = 0; p14 < (int)el->mNodes.Count(); ++p14) {
            n35 = el->mNodes.mpBegin[p14].mId;

            for (t16 = 0; t16 < 3; ++t16) {
                v31 = p14 * 3 + t16;
                t30 = mIds[v31];
                owner = base[t30 >> 1].mSlot;
                if (owner == -1) {
                    t10.Add();
                    owner = t10.mpEnd - t10.mpBegin;
                    t10.mpEnd[-1].mId = t30;
                    t10.mpEnd[-1].mSlotData = mSlotData[v31];
                    t10.mpEnd[-1].mSlot = mSlots80[v31];
                    base[t30 >> 1].mSlot = owner;
                }
                el->mSlots6c.mpBegin[v31] = owner;
            }
        }

        el->mRecs.Copy(t10);
        mTotal = mTotal + el->mRecs.Count();
        p30 += el->mSlots6c.Count();
    }

    for (NodeWeight* p = t10.mpBegin; p < t10.mpEnd; ++p) {
    }
    t10.Dtor();
}
