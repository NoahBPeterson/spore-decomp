// Slice s00508fd0, file B: table builder A.
// The sibling functions live in s00508fd0.cpp; this file transcribes the
// PARTIAL stub from partial.txt directly out of the disassembly.
//
// @ 0x00508fd0
//
// Object = SP::MeshPaintTarget (the cSkinObject +0x34 mesh holder, see
// src/game/SPBake/_at_004c0000.cpp). The body is integer /Od code: no
// floats, no vtables, no EH. Retail frame 0x1a4 on a frame pointer.
//
// The retail frame is 13 named automatics (name-hash order, the ranks the
// od_rankf probe measured) plus 27 temporaries, every one accounted for by
// an inline-expansion mechanism: the out-of-line vector calls are wrapped in
// __forceinline members whose materialised receivers/return temps/locals
// take the slots (the s00508fd0 sibling notes the same lever). The locals
// are named to the /Od walk's rank order so they land on the retail slots;
// the body's semantics follow the retail uses, not the letters: `corner` is
// the 0..2 corner-in-node counter, `ok` is the node's corner id, `allocByte`
// holds the pair slot value.


#include "s00508fd0_builderA.h"

// @ 0x00508fd0
void MPT::Build()
{
    // the 0x18-byte hole between `first` and `res` in the retail frame —
    // no code touches it, but it occupies the slots the name-hash walk
    // assigns between them (the od_rankf pick table's row 2). Declared
    // BEFORE first: the two names collide, and the later declaration
    // takes the earlier (higher) slot.
    char id[0x18];
    int first;
    unsigned count;
    NWV res;
    unsigned corner;
    int nNodes;
    unsigned elem;
    int last;
    int cap;
    SkinBuildData* dst;
    unsigned nHdr;
    int allocByte;
    unsigned ok;
    // retail's two lowest-rank named locals: the &mNodes cache for the
    // first Resize, and the one-byte allocator handed to Ctor
    int nodes;
    AL cur;

    mTotal = 0;
    first = 0;

    // retail spells the first Resize through a named &mNodes cache (one
    // store from the spilled this, two loads for the Count diff)
    NWB& nodesRef = mNodes;
    mBaseTabTab.Resize((nodesRef.Count() + 1) >> 1);

    // the local record scratch: the ctor zeroes the header, then the init
    // points begin/end at the inline storage (cur: the named one-byte
    // allocator retail hands to Ctor)
    res.Ctor(cur);
    res.Init();

    for (count = 0; count < mParts.Count(); ++count) {
        dst = mParts.mpBegin[count];

        // reserve 3 * nodeCount node-weight records on the element
        dst->mSlots6c.Resize(dst->mNodes.Count() * 3);

        // clear the element's record list, then the scratch
        dst->mRecs.Clear();
        res.Erase(res.mpBegin, res.mpEnd);

        cap = -1;
        last = cap;
        FillPairs(*(const Pair*)&last);

        // per-node loop: the node's id picks a corner id, the corner id's
        // pair slot is (re)filled, and every corner of the node gets it
        for (elem = 0; elem < dst->mNodes.Count(); ++elem) {
            nNodes = dst->mNodes.mpBegin[elem];

            for (corner = 0; corner < 3; ++corner) {
                ok = nNodes * 3 + corner;
                nHdr = mIds[ok];
                allocByte = mBaseTabTab.mpBegin[nHdr >> 1].At(nHdr & 1);
                if (allocByte == -1) {
                    allocByte = res.Count();
                    res.Add();
                    res.Set(nHdr, &mSlotData[ok], &mSlots80[ok]);
                    mBaseTabTab.mpBegin[nHdr >> 1].At(nHdr & 1) = allocByte;
                }
                dst->mSlots6c.mpBegin[elem * 3 + corner] = allocByte;
            }
        }

        dst->mRecs.Copy(res);
        mTotal = mTotal + dst->mRecs.Count();
        first = first + dst->mSlots6c.Count();
    }

    res.Sweep();
    res.Dtor();
}
