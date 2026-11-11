// Slice s00e62340 -- SP cell-game "bites" UI helper (unnamed in the retail PDB).
//
// Called as FUN_00e62340(cell, v) where v is the cell's +0x244 bites counter.
// If the cell has live UI (+0x248), it creates/looks up the cell's part UI record
// (sFindOrCreateUI, 0x00e62200) with the part id at cell+0 and the rate v/6, then
// sets that record's +0x24 field to 0.5f.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

struct cPartUIRecord_00e62340 {
    char  pad_000[0x24];
    float mRate;                 // +0x24
};

struct cCell_00e62340 {
    int   mPartID;               // +0x000
    char  pad_004[0x248 - 0x004];
    int   mHasUI;                // +0x248
};

extern "C" void* sFindOrCreateUI(int partID, float a);   // 0x00e62200
extern float g_1440f84;        // 0x01440f84  1/6
extern float g_1471064;        // 0x01471064  0.5f

// @ 0x00e62340
extern "C" void FUN_00e62340(cCell_00e62340* cell, int v)
{
    if (cell->mHasUI != 0) {
        cPartUIRecord_00e62340* rec =
            (cPartUIRecord_00e62340*)sFindOrCreateUI(cell->mPartID, (float)v * g_1440f84);
        if (rec != 0)
            rec->mRate = g_1471064;
    }
}
