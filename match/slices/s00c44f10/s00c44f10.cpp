// @ 0x00c44f10
// Simple member getter: returns the dword at +0xf4 (adjacent to cSPMissionEradicate::FUN_00c44f20).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct cSPMissionEradicate {
    char pad00[0xf4];
    int  m0f4;                // +0xf4
    int GetF4();
};

int cSPMissionEradicate::GetF4()
{
    return m0f4;
}
