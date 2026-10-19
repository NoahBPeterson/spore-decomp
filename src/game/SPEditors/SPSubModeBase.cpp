// src/game/SPEditors/SPSubModeBase.cpp -- migrated from slice(s) s0063aa90 by tools/migrate/rewrite.py
// Object file: SPEditors/SPSubModeBase.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPlayModeSubModeBase.h"
#include "EA/Stopwatch.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cSPPlayMode.h"
#include "SP/cSPPlayModeSubModeAction.h"
#include "SP/cSPPlayModeSubModeDance.h"
#include "SP/cSPPlayModeSubModeMovie.h"
#include "SP/cSPPlayModeUI.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "SP/SubModeParams_t.h"

// @ 0x0063b270
void SP::cSPPlayModeSubModeBase::Init(SP::SubModeParams_t * params)
{
    mSubModeParams = (SP::SubModeParams_t*)params;
    mPlayMode = *(SP::cSPPlayMode**)((char*)params + 0x24);
}
