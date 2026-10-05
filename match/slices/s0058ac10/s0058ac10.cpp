// slice s0058ac10 -- SP::cAppModeEditorBase::OnKeyDown / OnMouseUp.  Large input handlers; skeletons.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
namespace SP {
class cAppModeEditorBase {
public:
    char pad0[0x600];
    int OnKeyDown(int* a, uint32_t b);                    // 0x0058ac10
    int OnMouseUp(int x, int y, int button, int flags); // 0x0058b650
};
}
using namespace SP;
// @ 0x0058ac10 PARTIAL: 2620 B key handler; skeleton returns unhandled.
int cAppModeEditorBase::OnKeyDown(int* a, uint32_t b) { (void)a; (void)b; return 0; }
// @ 0x0058b650 PARTIAL: 1029 B mouse-up handler; skeleton returns unhandled.
int cAppModeEditorBase::OnMouseUp(int x, int y, int button, int flags) { (void)x; (void)y; (void)button; (void)flags; return 0; }
