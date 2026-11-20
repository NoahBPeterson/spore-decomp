// @ 0x00dd6da0
#include "game/types.h"

struct EventNode {
    EventNode* mpNodeLeft;
    EventNode* mpNodeRight;
    EventNode* mpNodeParent;
    unsigned mColor;
    unsigned mKey;
};

struct cSPUILayout {
    void Shutdown(unsigned flags); // 0x00811ad0
};
extern cSPUILayout* DAT_016a095c;
void ShutdownLayoutStack(); // 0x00dd5950

struct cSPUIEventLog {
    char pad000[0x30];
    EventNode* mpNodeRight;
    char pad034[8];
    unsigned mnSize;
    void remove_event(unsigned id); // 0x00dd6bc0
};

// The shutdown interface is the secondary base of cSPUIEventLog, at +4.
struct EventLogShutdownBase {
    char pad000[0x38];
    unsigned mnSize;
    void Shutdown();
};

void EventLogShutdownBase::Shutdown()
{
    cSPUIEventLog* log = reinterpret_cast<cSPUIEventLog*>(
        reinterpret_cast<char*>(this) - 4);
    if (mnSize != 0) {
        do {
            log->remove_event(log->mpNodeRight->mKey);
        } while (log->mnSize != 0);
    }
    if (DAT_016a095c != 0) {
        DAT_016a095c->Shutdown(1);
        DAT_016a095c = 0;
    }
    ShutdownLayoutStack();
}
