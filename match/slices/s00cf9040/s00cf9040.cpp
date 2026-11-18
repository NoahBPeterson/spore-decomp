// @ 0x00cf9040
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "game/types.h"

namespace SP {
class cCivilization;
class cSPUIEventLog {
public:
    uint32_t PostFeedbackEvent(uint32_t eventID, uint32_t groupID,
                              const void* position, const void* color,
                              int mode, int playerID); // 0x00dd8640
};
cSPUIEventLog* __cdecl EventLog(); // 0x00b3d3e0
}

class cCivRefTable {
public:
    SP::cCivilization* SetField10(SP::cCivilization* civilization); // 0x00cfe790
};
extern cCivRefTable* g_civRefTable; // 0x0169d3c8

namespace SP {
class cCivModeStrategy {
public:
    uint32_t PostFeedbackEvent(cCivilization* civilization,
                              uint32_t eventID, uint32_t groupID,
                              const void* position, const void* color,
                              int mode, int playerID);
};

uint32_t cCivModeStrategy::PostFeedbackEvent(cCivilization* civilization,
    uint32_t eventID, uint32_t groupID, const void* position,
    const void* color, int mode, int playerID)
{
    cCivRefTable* table = g_civRefTable;
    cCivilization* saved = table->SetField10(civilization);
    uint32_t result = EventLog()->PostFeedbackEvent(eventID, groupID,
                                                  position, color, mode, playerID);
    table->SetField10(saved);
    return result;
}
}
