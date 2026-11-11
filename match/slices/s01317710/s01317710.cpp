// @ 0x01317710
// Simulator/SPGonzago startup: g_167b550 = g_15673a4 + 20000 (0x4e20). Both are plain globals
// written by the planet-property loader in SPPlanet.cpp; declared here by address.
#include "types.h"

extern uint32_t g_15673a4;   // 0x015673a4
extern uint32_t g_167b550;   // 0x0167b550

void FUN_01317710()
{
    g_167b550 = g_15673a4 + 0x4e20;
}
