// slice s00591fa0 -- SP::cAppModeEditorBase::HandleMessage (6297 B, EA::Messaging::IHandlerRC).  Skeleton.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
namespace SP {
class cAppModeEditorBase {
public:
    char pad0[0x600];
    int HandleMessage(uint32_t messageID, int* args);   // 0x00591fa0
};
}
using namespace SP;
// @ 0x00591fa0 PARTIAL: 6297 B message dispatcher; skeleton returns 0.
int cAppModeEditorBase::HandleMessage(uint32_t messageID, int* args) { (void)messageID; (void)args; return 0; }
