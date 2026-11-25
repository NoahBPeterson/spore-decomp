// Slice s00508fd0, file B: table builder A.
// The sibling functions live in s00508fd0.cpp; this file is a byte-exact
// reconstruction of the 1142-byte retail body.
//
// @ 0x00508fd0
//
// Object = SP::MeshPaintTarget (the cSkinObject +0x34 mesh holder, see
// src/game/SPBake/_at_004c0000.cpp). The body is integer /Od code: no
// floats, no vtables, no EH. Retail frame 0x1a4 on a frame pointer.
//
// Build() rebuilds the paint target's node-weight tables:
//   * grow the +0x1b8 half-id -> pair table to half the live record count;
//   * for every SkinBuildData on the +0xe4 list: reserve 3 records per node,
//     clear its record list and the scratch builder, fill every base pair with
//     the sentinel -1, then for each node and each of its 3 corners look the
//     corner id up in the +0x58 list and, when its base pair slot is still -1,
//     append a record to the scratch (index, slot data, slot) and store the
//     new record index in the pair; every corner then gets that index in the
//     +0x6c table;
//   * copy the scratch into the element's own list, accumulate the record
//     count into +0x10c and the slot count into `first`, and finally sweep and
//     destroy the scratch.
//
// Every automatic, temporary and dead dword of the retail frame is reproduced
// by an inline-expansion mechanism; the slot map and the mechanisms are
// documented in s00508fd0_builderA.h.

#include "s00508fd0_builderA.h"

// @ 0x00508fd0
void MPT::Build()
{
    // the 0x18-byte hole between `first` and `res` in the retail frame — no
    // code touches it, but it occupies the slots the name walk assigns
    // between them. Declared BEFORE first: the two names collide there and
    // the later declaration takes the higher slot.
    char id[0x18];
    int first;
    unsigned count;
    NWV res;
    unsigned corner;
    int nNodes;
    unsigned elem;
    // one 8-byte Pair, not two ints: retail clears it with the chained
    // assignment below and copies it as a block in FillPairs
    Pair last;
    SkinBuildData* dst;
    unsigned nHdr;
    int allocByte;
    unsigned ok;
    // the &mNodes cache for the first Resize. A pointer, not a reference:
    // a reference local emits a 24-byte self-copy retail does not have.
    NWB* nodes;
    // the four dead dwords between that cache and the allocator byte at
    // -0x149: unused locals here (not inside Create) so the name walk allots
    // them below `nodes`, which is where retail's four slots sit
    unsigned j, m, pos, node;

    mTotal = 0;
    first = 0;

    nodes = &mNodes;
    mBaseTabTab.Resize((nodes->Count() + 1) >> 1);

    // the local record scratch: the ctor zeroes the header, then the init
    // points begin/end at the inline storage (the allocator local `cur` lives
    // inside the Create wrapper, which is where retail's 1-byte slot sits)
    res.Create();

    for (count = 0; count < mParts.Count(); ++count) {
        dst = mParts.mpBegin[count];

        // reserve 3 * nodeCount node-weight records on the element. Called
        // directly: any wrapper spelling materialises a receiver home retail
        // does not have.
        dst->mSlots6c.Resize(dst->mNodes.Count() * 3);

        // clear the element's record list, then the scratch
        dst->mRecs.Clear();
        res.Erase(res.mpBegin, res.mpEnd);

        last.mSlot[0] = last.mSlot[1] = -1;
        FillPairs(last);

        // per-node loop: the node's id picks a corner id, the corner id's
        // pair slot is (re)filled, and every corner of the node gets it
        for (elem = 0; elem < dst->mNodes.Count(); ++elem) {
            nNodes = dst->mNodes.mpBegin[elem];

            for (corner = 0; corner < 3; ++corner) {
                ok = nNodes * 3 + corner;
                nHdr = mIds[ok];
                allocByte = mBaseTabTab.mpBegin[nHdr >> 1].At(nHdr & 1);
                if (allocByte == -1) {
                    allocByte = res.TakeSlot();
                    res.Add();
                    // one statement per field, so each element address is
                    // computed at its own use site (retail stores mId, then
                    // the +0x6c element, then the +0x80 one)
                    res.mpEnd[-1].mId = nHdr;
                    res.SetSlotData(&mSlotData[ok]);
                    res.SetSlot(&mSlots80[ok]);
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
