// src/game/cmn/ssys.cpp.cpp -- migrated from slice(s) s01132ad0 by tools/migrate/rewrite.py
// Object file: cmn/ssys.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void*   g_sysObj;                  // 0x016e61a8  Snd9 system object
extern void*   g_voice;                   // 0x016e6260  Snd9 service voice
extern int   __cdecl FUN_0112e720(int, int, void*, void*, void*);   // 0x0112e720
extern int   __cdecl FUN_011390a0(void);               // 0x011390a0
extern int   __cdecl FUN_01138cf0(void);               // 0x01138cf0
extern int   __cdecl FUN_0113eda0(void*);              // 0x0113eda0
extern void  __cdecl FUN_0113ee40(void*);              // 0x0113ee40
extern void  __cdecl SNDSYSI_init(void);               // 0x0113f060

// ---- items of slice s01132ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*   g_sysObj;                  // 0x016e61a8  Snd9 system object
extern void*   g_voice;                   // 0x016e6260  Snd9 service voice
extern int   __cdecl FUN_0112e720(int, int, void*, void*, void*);   // 0x0112e720
extern int   __cdecl FUN_011390a0(void);               // 0x011390a0
extern int   __cdecl FUN_01138cf0(void);               // 0x01138cf0
extern int   __cdecl FUN_0113eda0(void*);              // 0x0113eda0
extern void  __cdecl FUN_0113ee40(void*);              // 0x0113ee40
extern void  __cdecl SNDSYSI_init(void);               // 0x0113f060
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
struct VoiceCtorDesc
{
	int     f00;    // +0x00
	int     f04;    // +0x04
	int     f08;    // +0x08
	int     f0c;    // +0x0c
	uint8_t f10;    // +0x10
	uint8_t pad11[0xb];
	uint8_t f1c;    // +0x1c
};
// ---- items of slice s01132ad0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
int __cdecl Voice_CreateInstance(int code);  // 0x01133050 (stays in the slice: not this object's)

// @ 0x01133120
int __cdecl Snd9_System_Init(int param_1)
{
	int sys = (int)g_sysObj;
	if ((*(uint8_t*)0x016e7c1c) == 1)
		return 0;

	((SndSysObj*)sys)->Lock();
	int v = *(int*)(sys + 0xe0);
	((SndSysObj*)sys)->Unlock();

	char b;
	do
	{
		((SndSysObj*)sys)->Lock();
		b = (char)((SndSysObj*)sys)->FUN_0112c640(v);
		((SndSysObj*)sys)->Unlock();
	} while (b == 0);

	uint8_t dev[0x1c];
	int code = FUN_0113eda0(dev);
	int r = Voice_CreateInstance(code);
	if (r < 0)
		return Voice_CreateInstance(r);

	FUN_0113ee40(dev);
	SNDSYSI_init();
	((SndSysObj*)sys)->Lock();
	int u2 = ((SndSysObj*)sys)->FUN_0112cd60(FUN_011390a0());
	int u4 = ((SndSysObj*)sys)->FUN_0112cd60(FUN_01138cf0());

	if (param_1 == 0)
		param_1 = ((SndSysObj*)sys)->FUN_00ff35d0();

	VoiceCtorDesc d;
	d.f00 = 0;
	d.f04 = u2;
	d.f08 = 0;
	d.f0c = u4;
	d.f10 = 6;
	d.f1c = 6;

	Voice* voice = (Voice*)FUN_0112e720(0, 2, &d.f08, &d.f04, g_sysObj);
	g_voice = voice;
	*(const char**)((char*)voice + 0x14) = "Snd9 Service";

	int local3c = param_1;
	((SndSysObj*)d.f04)->FUN_0112ccc0(0, &local3c);
	((SndSysObj*)sys)->Unlock();
	return 0;
}
