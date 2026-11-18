// Slice s00cd7100 - SporeApp 0x00cd7100
// SP::cTribeModeStrategy relationship-event notifier.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-

#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

// SP::cTribeModeStrategy, only the predicate this function calls.
struct cTribeModeStrategy {
    bool Has(int id);                       // 0x00cd6ef0
};

// The object a posted feedback event is delivered through.
struct cEventLog {
    void PostFeedbackEvent(u32 event, u32 category, int a, int b, int c, int d);  // 0x00dd8640
};

extern cTribeModeStrategy* gTribeModeStrategy_0169b2c8;   // 0x0169b2c8
cEventLog* EventLog_00b3d3e0();                           // 0x00b3d3e0

// @ 0x00cd7100
// Maps a relationship state (1..9) to its feedback-event id and posts it,
// unless the tribe-mode strategy has already handled that state.
void FUN_00cd7100(int relationship)
{
    u32 event;
    switch (relationship) {
    case 1: event = 0x1f530f73u; break;
    case 2: event = 0x87257c01u; break;
    case 3: event = 0xcbaf7ee2u; break;
    case 4: event = 0xd3a34498u; break;
    case 5: event = 0xbd7ce41eu; break;
    case 6: event = 0xeb39fbd9u; break;
    case 7: event = 0xa0d49e3au; break;
    case 8: event = 0x666686efu; break;
    case 9: event = 0x97ada627u; break;
    default:
        return;
    }

    if (!gTribeModeStrategy_0169b2c8->Has(relationship))
        EventLog_00b3d3e0()->PostFeedbackEvent(event, 0x182cd6ceu, 0, 0, 1, 0);
}
