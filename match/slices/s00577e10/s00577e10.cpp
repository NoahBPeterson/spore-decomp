// slice s00577e10
// Single 5788-byte editor function (SP::cAppModeEditorBase::UpdateBabyCreatures).
// It builds a large SSE/stack matrix from the animated-creature manager positions,
// samples the surrounding record grid and updates the baby-creature poses.
// The full body is not translated (see partial.txt): this is a compiling skeleton.
#include "types.h"

namespace SP {
class cAppModeEditorBase {
public:
    char pad[0x458];
    void UpdateBabyCreatures(int);      // 0x577e10
};
}

// @ 0x00577e10
void SP::cAppModeEditorBase::UpdateBabyCreatures(int)
{
}
