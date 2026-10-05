// Slice s00780b70: one 3680-byte SP::cAppModeTerrainEditor::HandleSimulationUpdate
// (PDB caller-scored) / SP::cSPSimulatorSpaceGame::PlanetContextActivate (Ghidra
// caller-scored).  /O2 /MD /Gy /TP module.
//
// PARTIAL: only the property-toggle / enable / property-change-refresh front end
// is reproduced.  The bulk (distance curve sampling, direction lerp+normalise,
// the 2048-step render loop, and the two inlined Matrix44 transforms) is not
// translated, so this file is listed in partial.txt, not nonmatching.txt.
#include "types.h"

struct cPropertyList {
    bool GetDescription(uint32_t key);
};

extern cPropertyList* g_AppProperties;

void FUN_007806a0(int* self);
void FUN_00780ab0(int* self);
void FUN_0077f6a0(int* self);
void FUN_0077f640(int* self);

// @ 0x00780B70
float __fastcall PlanetContextActivate(int* param_1)
{
    cPropertyList* pl = g_AppProperties;
    bool enabled = pl->GetDescription(0x276abef) && pl->GetDescription(0x276abf0);
    if (enabled != *((char*)param_1 + 5)) {
        if (!enabled) {
            if (param_1[0x6d] != 0)
                FUN_007806a0(param_1);
        } else if (param_1[0x6d] == 0) {
            FUN_00780ab0(param_1);
        }
        *((char*)param_1 + 5) = enabled;
    }

    if (!enabled || *((char*)param_1 + 4) == 0)
        return 0.0f;

    FUN_0077f6a0(param_1);
    FUN_0077f640(param_1);

    // --- omitted: the remainder of the original function ---
    return 0.0f;
}
