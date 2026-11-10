// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

namespace SP {

class cSPUIEventLog {
public:
    void RemoveEvent(unsigned int eventID, char immediate);
};

cSPUIEventLog* __cdecl EventLog();

class cSPMission {
public:
    uint32_t mUnknown000[0x148 / sizeof(uint32_t)];
    unsigned int mProgressEventID;

    void ValidateProgressEvent();
};

// @ 0x00c44f20
void cSPMission::ValidateProgressEvent()
{
    if (mProgressEventID != 0xffffffff) {
        EventLog()->RemoveEvent(mProgressEventID, 1);
        mProgressEventID = 0xffffffff;
    }
}

}
