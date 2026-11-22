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

// ---- items of slice s01132ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*   g_sysObj;                  // 0x016e61a8  Snd9 system object
extern void*   g_voice;                   // 0x016e6260  Snd9 service voice
class SndSysObj
{
public:
	void Lock(void);                 // 0x0112c600
	void Unlock(void);               // 0x0112c620
	bool FUN_0112c640(int);          // 0x0112c640
	int  FUN_0112ce00(void);         // 0x0112ce00
	int  FUN_0112cd60(int);          // 0x0112cd60
	int  FUN_00ff35d0(void);         // 0x00ff35d0
	void FUN_0112ccc0(int, void*);   // 0x0112ccc0  __thiscall, ret 8
};
class Voice
{
public:
	void Release(void);              // 0x0112e950
};
// ---- items of slice s01132ad0 end

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

// @ 0x011330f0
int __cdecl FUN_011330f0(void)
{
	SndSysObj* sys = (SndSysObj*)g_sysObj;
	sys->Lock();
	((Voice*)g_voice)->Release();
	sys->Unlock();
	return 0;
}
