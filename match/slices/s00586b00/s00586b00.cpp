// slice s00586b00 -- SP::cAppModeEditorBase::PrepareAppForNewModel / SetMode.  Both functions are
// large (1.9 KB) editor state transitions; only their signatures and headlines are modelled here.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

namespace SP {

class cSPEditorModel;
class cSPEditorAnimatedEventInfo;

class cAppModeEditorBase {
public:
    char pad0[0x600];
    void PrepareAppForNewModel(cSPEditorModel* model);   // 0x00586b00
    bool SetMode(int mode, char b);  // 0x00587270
};

}  // namespace SP

using namespace SP;

// @ 0x00586b00
// PARTIAL: rebuilds editor state for a newly loaded model (1889 B).  Skeleton only.
void cAppModeEditorBase::PrepareAppForNewModel(cSPEditorModel* model)
{
    (void)model;
    *(bool*)((char*)this + 0x472) = 0;
    *(void**)((char*)this + 0x380) = 0;
}

// @ 0x00587270
// PARTIAL: switches the editor mode (1959 B).  Skeleton preserves the early-out only.
bool cAppModeEditorBase::SetMode(int mode, char b)
{
    if (*(int*)((char*)this + 0x31c) == mode && b == 0)
        return false;
    return true;
}
