// @ 0x00c44f20
// cSPMissionEradicate::FUN_00c44f20 — removes the mission's event-log entry at +0x148.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct cSPMissionEradicate {
    char pad00[0x148];
    int  m148;                // +0x148
    void FUN_00c44f20();
};

struct cSPUIEventLog {
    void RemoveEvent(unsigned int id, unsigned int b);   // 0x00dd6d10
};

void* __cdecl SP_EventLog();                             // 0x00b3d3e0

void cSPMissionEradicate::FUN_00c44f20()
{
    if (m148 != -1)
    {
        ((cSPUIEventLog*)SP_EventLog())->RemoveEvent((unsigned int)m148, 1);
        m148 = -1;
    }
}
