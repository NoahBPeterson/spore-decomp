// Slice s00cfab90: 0x00CFAB90..0x00CFB660.
//  0x00cfab90  FUN_00cfab90  (598 B)
//  0x00cfadf0  FUN_00cfadf0  (584 B)
//  0x00cfb040  FUN_00cfb040  ( 99 B)
//  0x00cfb0b0  FUN_00cfb0b0  (138 B)
//  0x00cfb140  FUN_00cfb140  (374 B)
//  0x00cfb2c0  FUN_00cfb2c0  (848 B)
//  0x00cfb610  SP::cCivModeStrategy::GetNumberedCity  ( 70 B)
//  0x00cfb660  SP::cCivModeStrategy::FinishMaxLoad    (548 B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// Game-data vector returned by cGameNounManager::GetGameDataVector.
struct tVecData {
    int     m00;         // +0x00
    void*   mItems[2];   // +0x04  begin, +0x08  end
};

struct cGameNounManager {
    tVecData* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340
    void*     CreateNoun(void* id);                                            // 0x00b20c60
};

struct cCivModeStrategy {
    void* GetNumberedCity(int index);    // 0x00cfb610
};

void* NounManager();   // 0x00b3d300

// ---------------------------------------------------------------- 0x00cfab90

// @ 0x00cfab90
void FUN_00cfab90(void) {}

// ---------------------------------------------------------------- 0x00cfadf0

// @ 0x00cfadf0
void FUN_00cfadf0(void) {}

// ---------------------------------------------------------------- 0x00cfb040

// @ 0x00cfb040
void FUN_00cfb040(void) {}

// ---------------------------------------------------------------- 0x00cfb0b0

// @ 0x00cfb0b0
void FUN_00cfb0b0(void) {}

// ---------------------------------------------------------------- 0x00cfb140

// @ 0x00cfb140
void FUN_00cfb140(void) {}

// ---------------------------------------------------------------- 0x00cfb2c0

// @ 0x00cfb2c0
void FUN_00cfb2c0(void) {}

// ---------------------------------------------------------------- 0x00cfb610

// @ 0x00cfb610
void* cCivModeStrategy::GetNumberedCity(int index)
{
    cGameNounManager* nm = (cGameNounManager*)NounManager();
    tVecData* v = nm->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                        (void*)0x00acdff0, (void*)0x00b1e500,
                                        (void*)0x018c43e8);
    void** items = (void**)&v->mItems[0];
    if (index < (void**)items[1] - (void**)items[0])
        return ((void**)items[0])[index];
    return 0;
}

// ---------------------------------------------------------------- 0x00cfb660

// @ 0x00cfb660
void FUN_00cfb660(void) {}