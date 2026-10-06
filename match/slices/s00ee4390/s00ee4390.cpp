// Slice s00ee4390: SP::cSPEditorManipulatorUIBlockWinProc::DoMessage
// (retail VA 0x00EE4390, 4328 bytes; dev-build PDB 0x00D42290).
//
// This is a single, very large message dispatcher: a switch over the UTFWin message
// id (msg + 8) with a 0xe-entry jump table at 0x00EE5458, dispatching into dozens of
// nested command-id cases (msg[4]) and calling into the editor/UI command layers
// (cSPUISpace, WindowManager, cSPEditorVerbIconTray, cHideOnMoveScreenPosition, ...).
//
// NOTE: incomplete. A full behaviourally-equivalent reconstruction was not completed
// within this pass; the body below is only a placeholder so the slice compiles. See
// partial.txt. Do not treat this as decompiled.
#include "types.h"

namespace SP {

class cSPEditorManipulatorUIBlockWinProc {
public:
    // IWinProc + RefCountVTemplate<int>, then mApp at +0xc (dev-PDB layout).
    char pad[0xc];
    void* mApp;  // +0xc
    unsigned int DoMessage(int source, const void* msg);
};

}  // namespace SP

// @ 0x00EE4390
unsigned int SP::cSPEditorManipulatorUIBlockWinProc::DoMessage(
    int /*source*/, const void* /*msg*/) {
    return 0;
}
