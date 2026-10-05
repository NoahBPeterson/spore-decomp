// slice s00588570 -- SP::cAppModeEditorBase::OnMouseDown (5989 B).  Huge input handler; skeleton.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

namespace SP {

class cAppModeEditorBase {
public:
    char pad0[0x600];
    bool OnMouseDown(int x, int y, int button, int flags);   // 0x00588570
};

}  // namespace SP

using namespace SP;

// @ 0x00588570
// PARTIAL: editor mouse-down handling (5989 B).  Skeleton returns unhandled.
bool cAppModeEditorBase::OnMouseDown(int x, int y, int button, int flags)
{
    (void)x; (void)y; (void)button; (void)flags;
    return false;
}
