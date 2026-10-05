// slice s00587a20 -- SP::cAppModeEditorBase::Deactivate (2891 B).  Large teardown; skeleton only.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

namespace SP {

class cAppModeEditorBase {
public:
    char pad0[0x600];
    void Deactivate();   // 0x00587a20
};

}  // namespace SP

using namespace SP;

// @ 0x00587a20
// PARTIAL: releases the editor's worlds/models and removes listeners (2891 B).  Skeleton only.
void cAppModeEditorBase::Deactivate()
{
    *(void**)((char*)this + 0x94) = 0;
    *(void**)((char*)this + 0x98) = 0;
    *(void**)((char*)this + 0x9c) = 0;
}
