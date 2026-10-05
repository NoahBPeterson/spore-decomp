#include "types.h"

// Slice s005e3280: SP::cSPEditorVerbIcon (transition / disappear) and friends.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.

// ---------------------------------------------------------------------------------------------
// @ 0x005e3d40  (matched): set state then tail-call the transition update.
struct VerbIcon {
    char pad[0x64];
    int m64;              // +0x64
    void FUN_005e3920();
    void FUN_005e3d40();
};
void VerbIcon::FUN_005e3d40()
{
    m64 = 2;
    FUN_005e3920();
}

// ---------------------------------------------------------------------------------------------
// Not reconstructed.  See partial.txt.

// @ 0x005e3280
void FUN_005e3280(void* self) { (void)self; }

// @ 0x005e3920
// 1046-byte transition routine, not decompiled (declared in VerbIcon; see partial.txt)

// @ 0x005e3d50
void FUN_005e3d50(void* self) { (void)self; }
