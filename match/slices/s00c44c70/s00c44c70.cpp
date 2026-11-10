// Slice s00c44c70: SP::cSPMission state helpers.
// Retail reads the mission state dword at +0x84 (header says 0x5c; layout not verified).
// IsActive is true when state == kMissionInProgress (3).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

enum eMissionState {
    kMissionInProgress = 3,
};

struct cSPMission {
    char pad[0x84];
    int mState;  // 0x84 retail (evidence: 0x00c44c70 / 0x00c44c80)

    int GetState() const;     // 0x00c44c70
    bool IsActive() const;    // 0x00c44c80
};

// @ 0x00c44c70
int cSPMission::GetState() const
{
    return mState;
}

// @ 0x00c44c80
bool cSPMission::IsActive() const
{
    return mState == kMissionInProgress;
}
