// Slice s00c44f20: SP::cSPMission::ValidateProgressEvent
// Retail stores the progress-event id at +0x148 (header places a Key there; unverified).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

struct cSPUIEventLog {
    void RemoveEvent(unsigned int id, bool b);  // 0x00dd6d10
};

cSPUIEventLog* EventLog();  // 0x00b3d3e0

struct cSPMission {
    char pad[0x148];
    unsigned int mProgressEventID;  // 0x148 retail evidence from this function

    void ValidateProgressEvent();  // 0x00c44f20
};

// @ 0x00c44f20
void cSPMission::ValidateProgressEvent()
{
    unsigned int id = mProgressEventID;
    if (id != 0xffffffff) {
        EventLog()->RemoveEvent(id, true);
        mProgressEventID = 0xffffffff;
    }
}
