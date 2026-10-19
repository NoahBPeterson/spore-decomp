// src/game/cmn/voice.cpp.cpp -- migrated from slice(s) s01132ad0, s0112dca0 by tools/migrate/rewrite.py
// Object file: cmn/voice.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/Voice.h"
#include "rw/audio/core/DecoderRegistry.h"
#include "rw/audio/core/ListDNode.h"
#include "rw/audio/core/PlugIn.h"
#include "rw/audio/core/System.h"

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace rw { namespace audio { namespace core { int FUN_0112e700(int param); }}}  // 0x0112e700 (stays in the slice: not this object's)

// @ 0x0112e950
void rw::audio::core::Voice::Release()
{
    System* s = *(System**)((int)this + 0x10);
    char* cmd = s->mpCommandBuffer + s->mCommandIndex;
    s->mCommandIndex += 8;
    *(void**)cmd = (void*)&FUN_0112e700;
    *(void**)(cmd + 4) = this;
}

// @ 0x01133050
int __cdecl Voice_CreateInstance(int code)
{
	switch (code)
	{
	case 0:
		return 0;
	case 0xffffffed:
		return -1;
	case 0xffffffee:
		return -7;
	case 0xfffffff1:
		return -8;
	case 0xfffffff2:
		return -4;
	case 0xfffffff6:
		return -9;
	case 0xfffffff7:
		return -2;
	case 0xfffffff8:
		return -10;
	case 0xfffffff9:
		return -11;
	case 0xfffffffa:
		return -2;
	default:
		return -6;
	}
}
