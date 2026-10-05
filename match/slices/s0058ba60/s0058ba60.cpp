// slice s0058ba60 -- SP::cAppModeEditorBase::OnMouseMoveUpdate (998 B).  Skeleton.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
namespace SP {
class cAppModeEditorBase {
public:
    char pad0[0x600];
    int OnMouseMoveUpdate(float x, float y, int a, int b);   // 0x0058ba60
};
}
using namespace SP;
// @ 0x0058ba60 PARTIAL: mouse-move update; skeleton returns 0.
int cAppModeEditorBase::OnMouseMoveUpdate(float x, float y, int a, int b) { (void)x; (void)y; (void)a; (void)b; return 0; }
