// Slice s00441440: the single function in this slice is
//   SP::cSPEditorBlock::BuildBlock   (0x00441440, 23469 bytes, thiscall, ret 0x20)
//
// It is a monolithic /Od /Ob1 editor initialiser: it reads a cPropertyList, sets
// up dozens of texture/sound/handle maps, builds rotation-ring handles, snap
// axes, pinning info and per-bone deform handles, and touches cSPEditorBlock
// members from +0x1c up to well past +0x700. Reproducing all ~7000 decompiled
// lines byte-for-byte was out of budget for this slice, so this file keeps a
// compiling skeleton with the exact signature / call shape.
//
// Bookkeeping: partial.txt.
#include "types.h"

namespace SP {
class cIModelWorld;
class cSPEditorBlock {
public:
    bool BuildBlock(unsigned int instance, unsigned int group, cIModelWorld* world,
                    cSPEditorBlock* parent, unsigned int flags, char fullInit,
                    char isVisible, char param9);
};
}  // namespace SP

// @ 0x00441440
bool SP::cSPEditorBlock::BuildBlock(unsigned int, unsigned int, cIModelWorld*,
                                    cSPEditorBlock*, unsigned int, char, char, char)
{
    return false;
}
