// src/game/cmn/decoderregistry.cpp.cpp -- migrated from slice(s) s01133a80 by tools/migrate/rewrite.py
// Object file: cmn/decoderregistry.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_sys;                        // 0x016e61a8  rw::audio::core::System
extern int   __cdecl FUN_01143420(int, int, int, int*, void*);       // 0x01143420
extern void* __cdecl FUN_01143430(int, int, int, int, int, void*);   // 0x01143430

// ---- items of slice s01133a80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_sys;                        // 0x016e61a8  rw::audio::core::System
class System
{
public:
	void* Alloc(int size, const char* name, int align, int flags);   // 0x0112c820
	void  Free(void* p, int flags);                                  // 0x0112c850
};
extern int   __cdecl FUN_01143420(int, int, int, int*, void*);       // 0x01143420
extern void* __cdecl FUN_01143430(int, int, int, int, int, void*);   // 0x01143430
// ---- items of slice s01133a80 end

// @ 0x01133fc0
void* __cdecl FUN_01133fc0(int* desc, int param_2, int param_3, System* param_4)
{
	int iStack_8 = ((int (__cdecl*)(int, int**))desc[0])(param_2, &desc);
	int iStack_4 = param_3 * 0x14;
	int16_t sVar1 = *(int16_t*)((char*)desc + 0x18);
	int iVar7 = ((iStack_8 + 7) & ~7) + iStack_4;
	int bVar = (sVar1 != 0);
	int* puVar4 = desc;
	int puStack_c = 0;
	if (sVar1 != 0)
	{
		int iVar3 = FUN_01143420(param_2, 2, sVar1, &puStack_c, param_4);
		iVar7 = (iVar7 + ((puStack_c - 1) & ~(puStack_c - 1))) + iVar3;
		puVar4 = (puStack_c < (int)desc) ? desc : (int*)puStack_c;
	}
	int iVar3 = iVar7;
	if (iVar7 == 0)
		iVar3 = 0x34;
	int* p = (int*)((System*)g_sys)->Alloc(iVar3, 0, (int)puVar4, 0);
	if (p != 0)
	{
		*p = 0x014a7e54;
		p[3] = desc[2];
		p[4] = 0;
		*(char*)((char*)p + 0x2e) = (char)param_2;
		p[1] = (int)param_4;
		char ok = ((char (__cdecl*)(int*))desc[1])(p);
		if (ok != 0)
		{
			p[2] = (int)p;
			p[5] = desc[3];
			p[6] = desc[5];
			p[8] = iVar7;
			unsigned uVar8 = ((int)p + iStack_8 + 7) & ~7;
			*(char*)((char*)p + 0x32) = (char)param_3;
			*(uint16_t*)((char*)p + 0x2c) = 0;
			p[7] = 0;
			*(char*)((char*)p + 0x2f) = 0;
			*(char*)((char*)p + 0x30) = 0;
			*(char*)((char*)p + 0x31) = 0;
			*(char*)((char*)p + 0x33) = (char)bVar;
			p[9] = uVar8 - (int)p;
			if ((char)bVar == 0)
			{
			lab:
				int i = 0;
				int* q = (int*)(p[9] + (int)p);
				if (*(char*)((char*)p + 0x32) != 0)
				{
					do
					{
						*q = 0;
						q[3] = 0;
						i++;
						q += 5;
					} while (i < (int)(unsigned)*(uint8_t*)((char*)p + 0x32));
				}
				return p;
			}
			FUN_01143420(param_2, 2, *(int16_t*)((char*)desc + 0x18), &param_3, param_4);
			uVar8 = (uVar8 + (param_3 - 1) + iStack_4) & ~(param_3 - 1);
			p[10] = (uVar8 - (int)p) & 0xffff;
			void* storage = ((System*)g_sys)->Alloc(
				*(uint16_t*)((char*)desc + 0x18) * param_2 * 4, "Decoder block storage", 0x80, 0);
			p[4] = (int)storage;
			if (storage != 0)
			{
				FUN_01143430(param_2, 2, *(int16_t*)((char*)desc + 0x18), uVar8, (int)storage, param_4);
				goto lab;
			}
		}
		if (p[3] != 0)
			((void (__cdecl*)(int*))p[3])(p);
		if (p[4] != 0)
			((System*)g_sys)->Free((void*)p[4], 0);
		((System*)g_sys)->Free(p, 0);
	}
	return 0;
}
