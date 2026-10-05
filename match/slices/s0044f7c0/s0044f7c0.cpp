// slice s0044f7c0 -- SP::cSPEditorBlock::BuildBlock (6057 bytes).
// This body is far too large to reconstruct faithfully here; only the entry
// signature and the top-level shape are represented.  MARKED PARTIAL.
#include "types.h"

struct AutoRefBlockVec { unsigned int w[15]; };
struct cSPEditorBlock;

struct cSPEditorBlock {
    char pad0[0xdc8];
    unsigned int mFlags[2];   // +0xdc8

    // @ 0x0044f7c0
    cSPEditorBlock* BuildBlock(int type, cSPEditorBlock* source,
                               AutoRefBlockVec& a, AutoRefBlockVec& b);
};

// @ 0x0044f7c0
cSPEditorBlock* cSPEditorBlock::BuildBlock(int type, cSPEditorBlock* source,
                                           AutoRefBlockVec& a, AutoRefBlockVec& b) {
    // Full body (~6 KB, 20+ branches) not reconstructed.  It reads the block
    // resource, allocates/initialises the model + connectors, walks the child
    // block lists and populates the flag array.  Reproduced only as an outline.
    (void)type;
    (void)source;
    (void)a;
    (void)b;
    return 0;
}
