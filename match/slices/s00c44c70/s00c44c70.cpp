// @ 0x00c44c70
// cSPMissionEradicate::FUN_00c44c70 — returns the mission's target-state word at +0x84.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct cSPMissionEradicate {
    char pad00[0x84];
    int  m84;                 // +0x84
    int  FUN_00c44c70();
};

int cSPMissionEradicate::FUN_00c44c70()
{
    return m84;
}
