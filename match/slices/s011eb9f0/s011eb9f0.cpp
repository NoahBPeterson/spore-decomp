// Slice s011eb9f0 -- RenderWare 4 core: release the four handles produced by 011eb980.
// Split out of s011eaf70 because this row is built with the VC .NET 2003 compiler (/vc71):
// cl 13.10 keeps `add esp,4` right after the indirect call, cl 15 schedules `inc esi` into it.
// Flags: /vc71 /O2 /MD /Gy /TP.
#include "types.h"

extern "C" void* g_rwFreeFn;                               // 0x016f4aec  rw::core::stdc free callback

// @ 0x11eb9f0
void __stdcall FUN_011eb9f0(unsigned int* handles)
{
	for (unsigned int i = 0; i < 4; ++i)
		((void (__cdecl*)(unsigned int))g_rwFreeFn)(handles[i]);
}
