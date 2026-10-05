// slice s00636560: cSPPlayModeUI message dispatcher (3702 bytes).
// PARTIAL: the original is a ~100-case switch over the message command with a large
// UI update body; this skeleton only keeps the signature so the slice compiles.
#include "../s00636320/s00636320.h"

// @ 0x00636560
bool cSPPlayModeUI::DoMessageInternal(uint32_t a, void* msg)
{
    (void)a;
    (void)msg;
    return false;
}
