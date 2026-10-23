// Slice s00c09410 (gold5).
//
// Two large SP/CCM routines of the creature ("noun") layer:
//
//   00c09410  SP::GREET_AVATAR_Decide  -- __thiscall, ret 4.  Decides whether the
//             creature should greet the player avatar and, if so, kicks the agent
//             order manager / animation path.
//   00c099e0  the spawn/place-a-creature routine: builds a noun from a species
//             profile, hooks it to a herd, pushes it into the noun manager, then
//             orients it on the planet surface.
//
// The binary is a VC9 (cl 15.00) x86 build with the Spore CCM/SP headers missing
// here, so every structure is addressed through its raw byte offset and the
// callees are declared with their real addresses embedded in their names (which
// is what tools/difftest/resolve.py's hex-name rule keys on).
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// free functions (__cdecl / __stdcall)
// ---------------------------------------------------------------------------
extern "C" void* FUN_00b3d300();                 // SP::NounManager
extern "C" void* FUN_00b3d380();                 // SP::GameTimeManager
extern "C" void* FUN_00b3d260();                 // SP::BehaviorManager
extern "C" void* FUN_00b3d350();                 // SP::PlanetModel
extern "C" void* FUN_00b3d480();                 // cCityVisualizer accessor
extern "C" void* FUN_0067cb40();                 // SP::ObjectTemplateDB
extern "C" void* FUN_00b5b800();                 // SP::GetCurrentGameMode
extern "C" void* FUN_00401090();                 // GetSetting9
extern "C" void* FUN_0067cb30(int, void*);       // resource key lookup
extern "C" float   FUN_00d38a30(int, void*);     // creature tuning scalar
extern "C" float   FUN_00c02690(float*);         // vector length
extern "C" void*   FUN_00c04820(void*, void*, void*, void*);
extern "C" void*   FUN_00c06750(void*, void*, float, char, void*);
extern "C" void*   FUN_00c07320(void*, void*, void*);
extern "C" void*   FUN_00d995f0(float, double, void*, void*, void*, void*, void*, void*);
extern "C" void*   FUN_00aea5d0(void*, void*);   // eastl::vector<...>::push_back
extern "C" float   FUN_00572a10(float, float);   // RandomFloatRange
extern "C" void*   FUN_00c02710(float);
extern "C" float   FUN_00c033d0(void*);
extern "C" void*   FUN_0059aed0(float*, void*, void*);
extern "C" void*   FUN_00c035f0(void*);
extern "C" int     FUN_00c02790(void*);

// ---------------------------------------------------------------------------
// __thiscall methods (declared on a dummy type; the mangled name embeds the
// address so resolve.py's hex-name rule maps them back to the real callees).
// ---------------------------------------------------------------------------
struct M
{
	void* FUN_00b1fdb0();                      // 0xb1fdb0 cGameNounManager::GetAvatar
	void* FUN_00b20c60(int);                   // 0xb20c60 cGameNounManager::CreateNoun
	void  FUN_00b1fd50(void*);                 // 0xb1fd50 NounMgr::SetAvatar
	void  FUN_00b225d0(void*);                 // 0xb225d0 cGameNounManager::RemoveNoun
	void* FUN_00bca0c0(int, int, int, int);    // 0xbca0c0 cAgentOrderManager::FindSlot
	void* FUN_00ad20e0(void*, void*);          // 0xad20e0 cCityVisualizer::findVignetteEntry
	void  FUN_00c6b440(void*);                 // 0xc6b440 cHerd::OnAnimalRemoved
	void* FUN_004df420();                      // 0x4df420 GetAvatarProfile
	void* FUN_004e01b0();                      // 0x4e01b0
	void* FUN_004e0050(int, int);              // 0x4e0050 GetSpeciesArchetype
	void  FUN_004df3e0(void*);                 // 0x4df3e0 SetAvatarProfile
	void  FUN_00c0c180(void*);                 // 0xc0c180 C::SetE84
	char  FUN_00c037c0(void*, void*, int);     // 0xc037c0 C::attach
	char  FUN_00c0c0e0();                      // 0xc0c0e0 C::Flag388
	void  FUN_0060d860(void*, void*);          // 0x60d860 UpdateProperty
	void  FUN_00c0d9b0();                      // 0xc0d9b0 C::apply
	void* FUN_00c0c1a0();                      // 0xc0c1a0 C::getActiveOrder
	void  FUN_00c0fb80(int, int);              // 0xc0fb80 CAN::fb80
	void* FUN_00c0bbe0();                      // 0xc0bbe0
	void* FUN_00c042e0();                      // 0xc042e0
	void  FUN_00f924e0(float);                 // 0xf924e0
	void* FUN_00c05e80();                      // 0xc05e80
	void  FUN_00c05ea0();                      // 0xc05ea0
	void  FUN_00c06bf0(void*);                 // 0xc06bf0 vector::erase
	void* FUN_00c072f0(void*);                 // 0xc072f0 vector::push_back
	float FUN_00c0e4f0();                      // 0xc0e4f0 CCM::e4f0
	float FUN_00c0c010();                      // 0xc0c010 C::GetA
	float FUN_00c0c040();                      // 0xc0c040 C::GetB
	char  FUN_00c0c130();                      // 0xc0c130 C::isValid
	char  FUN_00c0d560(void*, float, float);   // 0xc0d560 C::proximity
	int   FUN_00c0c140();                      // 0xc0c140 C::CallFind13
	float FUN_004d3d70(int);                   // 0x4d3d70 TuningObj::GetBound
	int   FUN_00bc96a0(int, int);              // 0xbc96a0 cSPCreatureBase::Play
	void  FUN_00bc97f0(int, int, float, void*); // 0xbc97f0 cSPCreatureBase::queue
	void* FUN_00bc9980(float);                 // 0xbc9980 cSPCreatureBase::emit
	void  FUN_00b7f250(void*, void*, void*);   // 0xb7f250 BuildSurfaceOrientation2
	long long FUN_00b316c0();                  // 0xb316c0 GameTimeManager::now
};

// ---------------------------------------------------------------------------
// inline virtual dispatch helpers (the vtable slot is a byte offset)
// ---------------------------------------------------------------------------
typedef void  (__thiscall *VF0)(void*);
typedef void* (__thiscall *VP0)(void*);
typedef float (__thiscall *VFl0)(void*);
typedef int   (__thiscall *VI0)(void*);
typedef void  (__thiscall *VF1)(void*, void*);
typedef void* (__thiscall *VP1)(void*, void*);
typedef void  (__thiscall *VF2)(void*, void*, void*);

static inline void  vv0(void* p, int off) { (*(VF0*)(*(char**)p + off))(p); }
static inline void* vp0(void* p, int off) { return (*(VP0*)(*(char**)p + off))(p); }
static inline float vf0(void* p, int off) { return (*(VFl0*)(*(char**)p + off))(p); }
static inline int   vi0(void* p, int off) { return (*(VI0*)(*(char**)p + off))(p); }
static inline void  vv1(void* p, int off, void* a) { (*(VF1*)(*(char**)p + off))(p, a); }
static inline void* vp1(void* p, int off, void* a) { return (*(VP1*)(*(char**)p + off))(p, a); }
static inline void  vv2(void* p, int off, void* a, void* b) { (*(VF2*)(*(char**)p + off))(p, a, b); }

// ---------------------------------------------------------------------------
// .rdata constants / globals
// ---------------------------------------------------------------------------
extern float g_0145cff0;   // 0x0145cff0
extern float g_01469e34;   // 0x01469e34
extern float g_01473c70;   // 0x01473c70
extern float g_01486110;   // 0x01486110
extern float g_013f9428;   // 0x013f9428
extern float g_015d96b8;   // 0x015d96b8
extern float g_01687a54;   // 0x01687a54
extern float g_01687a58;   // 0x01687a58
extern float g_01471064;   // 0x01471064
extern float g_01488874;   // 0x01488874
extern float g_01571278;   // 0x01571278
extern float g_0157127c;   // 0x0157127c
extern float g_01571280;   // 0x01571280
extern float g_01571284;   // 0x01571284
extern float g_01571288;   // 0x01571288
extern float g_0157128c;   // 0x0157128c
extern float g_01571290;   // 0x01571290

// ===========================================================================
// 00c09410  SP::GREET_AVATAR_Decide
// ===========================================================================
struct CCM
{
	void FUN_00c09410(int param_2);
};

// @ 0x00c09410 FUN_00c09410
void CCM::FUN_00c09410(int param_2)
{
	char* self = (char*)this;
	if (*(int*)(*(int*)(self + 0xb4c)) == 0)
		return;

	void* nounMgr = FUN_00b3d300();
	int* avatar = (int*)((M*)nounMgr)->FUN_00b1fdb0();

	int bVar6 = 0;
	int bVar7 = 0;
	int* piVar18 = 0;
	char cVar8 = 0;

	if (*(char*)(self + 0xb5e) == 0 && avatar != 0)
	{
		float fVar20 = FUN_00d38a30(1, this);
		float fVar21 = FUN_00d38a30(2, this);
		float fVar22 = ((M*)this)->FUN_00c0e4f0() * fVar21;
		float fVar23 = ((M*)this)->FUN_00c0c010();
		void* piVar1 = self + 0xc0;
		float cosVal = (float)cos(fVar23 * 0.008726646f);

		float outv[4];
		vv1(piVar1, 0x5c, outv);
		float* pfVar12 = (float*)vp0(piVar1, 0x2c);
		float fThis74 = vf0(piVar1, 0x74);
		piVar18 = (int*)(int)fThis74;

		float* pfVar13 = (float*)vp0((char*)avatar + 0xc0, 0x2c);
		float fDx = pfVar13[0] - pfVar12[0];
		float fDy = pfVar13[1] - pfVar12[1];
		float fDz = pfVar13[2] - pfVar12[2];
		float fLen = FUN_00c02690(&fDx);
		float fAv74 = vf0((char*)avatar + 0xc0, 0x74);

		float fGap = fLen - (fAv74 + fThis74);
		float fStack_10 = 0.0f;
		if (0.0f <= fGap)
			fStack_10 = fGap;

		float fDot = outv[0] * fDx + outv[1] * fDy + outv[2] * fDz;

		cVar8 = ((M*)avatar)->FUN_00c0c130();
		if (cVar8 != 0 || fVar22 < fStack_10 || fDot < cosVal)
			cVar8 = 0;
		else
			cVar8 = 1;

		char cVar9 = ((M*)this)->FUN_00c0d560(avatar, fVar20, fStack_10);

		if (cVar8 == 0 && cVar9 == 0)
		{
			cVar8 = (char)vi0(piVar1, 0x58);
			if (cVar8 == 0 && (cVar8 = (char)vi0(self, 0xd0)) == 0 &&
				(cVar8 = ((M*)avatar)->FUN_00c0c130()) != 0)
			{
				float fVar2 = (float)avatar[0x400];
				float fB = ((M*)this)->FUN_00c0c040();
				int bVar5;
				if (fVar2 <= 1.5258789e-05f || (fB * fVar20 + fVar2) <= fStack_10)
					bVar5 = 0;
				else
					bVar5 = 1;
				int bVar4;
				if (fVar22 < fStack_10 || fDot < cosVal)
					bVar4 = 0;
				else
					bVar4 = 1;
				int iVar14 = ((M*)avatar)->FUN_00c0c140();
				if ((bVar5 || bVar4) && iVar14 != -1)
				{
					iVar14 = (int)vp1(avatar, 0xb4, (void*)iVar14);
					if (iVar14 != 0 &&
						(bVar5 || (bVar4 && fStack_10 < *(float*)(iVar14 + 0xa8))))
					{
						bVar7 = 1;
						piVar18 = avatar;
						bVar6 = 0;
						if (bVar4)
						{
							int t = ((*(unsigned*)((char*)avatar + 0xb58)) >> 9) & 1;
							float fBound = ((M*)(void*)iVar14)->FUN_004d3d70(t);
							if (fStack_10 < fBound)
								bVar6 = 1;
						}
					}
				}
			}
		}
		else
		{
			char* cnt = self + 0x1034;
			if (*(int*)(self + 0x103c) != *(int*)(self + 0x104c))
			{
				int iVar14 = (int)((M*)cnt)->FUN_00c05e80();
				if (*(int*)(iVar14 + 0x10) == (int)avatar)
					((M*)cnt)->FUN_00c05ea0();
			}
			void* vEnd = *(void**)(self + 0x1128);
			void* uVar16 = FUN_00c04820(*(void**)(self + 0x1124), vEnd,
										 (void*)FUN_00c02790, vEnd);
			((M*)(self + 0x1124))->FUN_00c06bf0(uVar16);
			void* res67 = FUN_00c06750(cnt, avatar, fStack_10, cVar8, 0);
			((M*)(self + 0x1124))->FUN_00c072f0(&res67);
			FUN_00c07320(*(void**)(self + 0x1124), *(void**)(self + 0x1128),
						 (void*)param_2);
			bVar6 = 1;
			((M*)(void*)(*(int*)(self + 0xb4c) + 8))->FUN_00bc97f0(0x4000000, 0,
																	0x40a00000f, avatar);
			piVar18 = avatar;
		}
	}

	// LAB_00c097f2
	if (avatar != 0)
	{
		void* creature = (void*)(*(int*)(self + 0xb4c) + 8);
		int iVar14 = ((M*)creature)->FUN_00bc96a0(0x4000000, 0);
		if (iVar14 == 0)
			*(char*)(self + 0xfb9) = 1;
		if (bVar6)
		{
			if (piVar18 != 0 && ((M*)piVar18)->FUN_00c0c130() != 0)
				((M*)creature)->FUN_00bc97f0(0, 8, 0x41200000f, piVar18);
			*(int*)(self + 0x101c) = 1;
		}
		else if (bVar7)
		{
			if (piVar18 != 0 && ((M*)piVar18)->FUN_00c0c130() != 0)
				((M*)creature)->FUN_00bc97f0(0x100, 0, 0x41200000f, piVar18);
			*(int*)(self + 0x101c) = 2;
		}
		else
		{
			*(int*)(self + 0x101c) = 0;
		}
	}

	// LAB_00c098a5
	{
		int iVar14 = *(int*)(self + 0xeac);
		unsigned uVar19 = ((unsigned)*(int*)(self + 0xb58) >> 8 & 1)
			| ((((*(unsigned*)(self + 0x110) & 0x100) != 0x100) ? 0xffffe000u : 0u) + 0x2000u)
			| *(unsigned*)(*(int*)(self + 0xb4c) + 0x5fc);
		if (iVar14 == 0)
			uVar19 |= 0x40000u;
		else if (iVar14 == 1)
			uVar19 |= 0x80000u;
		else if (iVar14 == 2)
			uVar19 |= 0x100000u;

		void* agentOrderMgr = *(void**)(self + 0xb48);
		int slot1 = (int)((M*)agentOrderMgr)->FUN_00bca0c0(1, 1, 0, 0);
		int slot2 = (int)((M*)agentOrderMgr)->FUN_00bca0c0(2, 1, 0, 0);
		void* creature = (void*)(*(int*)(self + 0xb4c) + 8);
		void* uVar16 = ((M*)creature)->FUN_00bc9980((float)param_2);
		void* gtMgr = FUN_00b3d380();
		long long uVar25 = ((M*)gtMgr)->FUN_00b316c0();
		double dTime = (double)(uVar25 & 0x7fffffffffffffffLL) * 0.0010000000474974513;
		int* puVar3 = *(int**)(self + 0xb4c);
		FUN_00d995f0((float)param_2, dTime, (void*)puVar3[0], self,
					 (void*)(puVar3 + 0x74), (void*)puVar3[0x17a],
					 (void*)(uVar19
							 | (slot1 != -1 ? 0x2000000u : 0u)
							 | (slot2 != -1 ? 0x4000000u : 0u)),
					 uVar16);
	}
}

// ===========================================================================
// 00c099e0  spawn / place a creature noun
// ===========================================================================
// @ 0x00c099e0 FUN_00c099e0
extern "C" int* FUN_00c099e0(int a1, int* profile, int a3, int a4,
							 int flagA, int flagB)
{
	char* p2 = (char*)profile;
	int* piVar4 = (int*)FUN_0067cb40();
	int* piVar12 = (int*)(p2 + 0x504);
	vv2(piVar4, 0x58, piVar12, (void*)1);

	int useFallback = 1;
	if (flagB != 0)
	{
		int* p = (int*)((M*)FUN_00b3d480())->FUN_00ad20e0(profile, (void*)piVar12);
		if (p != 0 && vp0(p, 0x20) == (void*)0x18eb45e)
		{
			piVar4 = p;
			useFallback = 0;
		}
	}
	if (useFallback)
	{
		void* nounMgr = FUN_00b3d300();
		int* p = (int*)((M*)nounMgr)->FUN_00b20c60(0x18eb45e);
		if (p == 0)
			piVar4 = 0;
		else
			piVar4 = (int*)vp1(p, 0xc, (void*)0xd0036e08);
	}

	*(int*)((char*)piVar4 + 0xb34) = (int)piVar12;
	if (*(int*)((char*)piVar4 + 0x1674) != 0)
		((M*)(void*)*(int*)((char*)piVar4 + 0x1674))->FUN_00c6b440(piVar4);
	{
		int* piVar13 = (int*)*(int*)((char*)piVar4 + 0x1674);
		if (piVar12 != piVar13)
		{
			if (piVar12 != 0)
				vv0(piVar12, 0);
			*(int*)((char*)piVar4 + 0x1674) = (int)piVar12;
			if (piVar13 != 0)
				vv0(piVar13, 4);
		}
	}

	int iVar7 = (int)((M*)FUN_00401090())->FUN_004df420();
	if (piVar12 != 0)
	{
		void* uVar8;
		if (profile == (int*)iVar7)
			uVar8 = ((M*)FUN_00401090())->FUN_004e01b0();
		else
			uVar8 = ((M*)FUN_00401090())->FUN_004e0050(*(int*)(p2 + 0x58c),
													   *(int*)(p2 + 0x5f4));
		((M*)piVar4)->FUN_00c0c180(uVar8);
	}
	if (flagA != 0)
	{
		((M*)FUN_00b3d300())->FUN_00b1fd50(piVar4);
		void* setting = FUN_00401090();
		if (profile != (int*)iVar7)
			((M*)setting)->FUN_004df3e0(profile);
	}

	char cVar3 = ((M*)piVar4)->FUN_00c037c0(profile, (void*)flagA, 0);
	if (cVar3 == 0)
	{
		((M*)FUN_00b3d300())->FUN_00b225d0(piVar4);
		return 0;
	}

	cVar3 = ((M*)piVar4)->FUN_00c0c0e0();
	if (cVar3 != 0)
	{
		*(float*)((char*)piVar4 + 0x2a8) = g_015d96b8;
		int gm = (int)FUN_00b5b800();
		int key = 0;
		if (gm == 0x1654c01)
			key = 0xf3ff72ef;
		else if ((gm = (int)FUN_00b5b800()) == 0x1654c02)
			key = 0x4f84bd4;
		if (key != 0)
		{
			void* pm = FUN_0067cb30(key, profile);
			((M*)pm)->FUN_0060d860((void*)key, profile);
		}
	}

	// LAB_00c09b8c
	((M*)piVar4)->FUN_00c0d9b0();
	if (piVar12 != 0)
	{
		int iVar14 = (int)((M*)piVar4)->FUN_00c0c1a0();
		if (iVar14 == 0)
		{
			int* q = *(int**)((char*)piVar4 + 0xb20);
			iVar14 = (int)FUN_00c02710((*(float*)((char*)q + 0x5b0)
										+ *(float*)((char*)q + 0x56c)) * 0.1f);
		}
		else
		{
			iVar14 = *(int*)(iVar14 + 0x330);
		}
		*(int*)((char*)piVar4 + 0xb88) = iVar14;

		int* pv = piVar4;
		vv0(piVar4, 0);
		int* puVar10 = *(int**)(p2 + 0x548);
		int* piVar13;
		if (puVar10 < *(int**)(p2 + 0x54c))
		{
			*(int**)(p2 + 0x548) = puVar10 + 1;
			piVar13 = piVar4;
			if (puVar10 != 0)
			{
				*puVar10 = (int)piVar4;
				vv0(piVar4, 0);
			}
		}
		else
		{
			FUN_00aea5d0(puVar10, &pv);
			piVar13 = pv;
		}
		if (piVar13 != 0)
			vv0(piVar13, 4);
	}

	if (flagA == 0)
	{
		vv1((char*)piVar4 + 0x5a8, 0x2c, (void*)1);
		float fVar1 = *(float*)((char*)piVar4 + 0x5e0);
		float fVar14 = FUN_00572a10(g_01687a54, g_01687a58);
		((M*)((char*)piVar4 + 0x5a8))->FUN_00f924e0(fVar14 * fVar1);
		if (piVar12 != 0 && *(int*)(p2 + 0x660) != 1 &&
			(int)FUN_00b5b800() != 0x1654c10)
		{
			int uVar8 = (int)((M*)piVar4)->FUN_00c0c1a0();
			float fVar14b = FUN_00c033d0((void*)uVar8);
			int iVar9;
			if (*(int*)(p2 + 0x5f8) < 1 || *(char*)(p2 + 0x588) != 0)
			{
				iVar9 = 0;
			}
			else
			{
				float fStack_2c = (float)*(int*)(p2 + 0x5f8) * fVar14b;
				iVar9 = (int)fStack_2c;
				if ((float)iVar9 < fStack_2c)
					iVar9 = iVar9 + 1;
			}
			if (0 < iVar9)
			{
				int iVar7b = 0;
				for (int* it = *(int**)(p2 + 0x544); it != *(int**)(p2 + 0x548); ++it)
				{
					if (*it != 0 && (*(unsigned char*)(*it + 0xb58) & 1) != 0)
						iVar7b = iVar7b + 1;
				}
				*(int*)((char*)piVar4 + 0xb58) |= (unsigned)(iVar7b < iVar9);
			}
		}
	}
	else
	{
		vv1((char*)piVar4 + 0x5a8, 0x2c, 0);
	}

	vv1((char*)piVar4 + 0xc0, 0x38, (void*)a1);

	float fAngle = g_01571278 * g_01471064;
	float s1 = (float)sin(fAngle);
	float f38 = g_0157127c * s1;
	float f3c = g_01571280 * s1;
	float f40 = s1 * g_01571284;
	float f44 = (float)cos(fAngle);

	float s2 = (float)sin(fAngle);
	float co = (float)cos(fAngle);
	float x0 = s2 * g_01571288;
	float x1 = s2 * g_0157128c;
	float x2 = s2 * g_01571290;
	float f20 = x2 * f3c - x1 * f40;
	float f24 = x0 * f40 - x2 * f38;
	float f28 = x1 * f38 - x0 * f3c;
	float f1c = co;

	float m10 = co * f38;
	float m14 = co * f3c;
	float m18 = co * f40;
	float r0 = f44 * x0 + m10 + f20;
	float r1 = x1 * f44 + m14 + f24;
	float r2 = x2 * f44 + m18 + f28;
	float r3 = f1c * f44 - (x2 * f40 + x0 * f38 + x1 * f3c);

	float q[4];
	q[0] = r0;
	q[1] = r1;
	q[2] = r2;
	q[3] = r3;

	float fStack_24 = f44;
	float w[4];
	void* puVar10 = FUN_0059aed0(q, (void*)a1, w);

	float uStack_3c = ((float*)puVar10)[0];
	float uStack_38 = ((float*)puVar10)[1];
	float uStack_34 = ((float*)puVar10)[2];
	void* planetModel = FUN_00b3d350();
	float auStack_20[6];
	((M*)planetModel)->FUN_00b7f250(auStack_20, (void*)a1, &uStack_3c);
	vv1((char*)piVar4 + 0xc0, 0x3c, auStack_20);

	((M*)piVar4)->FUN_00c0fb80(a1, (int)&fStack_24);
	((M*)piVar4)->FUN_00c0bbe0();
	((M*)piVar4)->FUN_00c042e0();
	vv0(piVar4, 0x54);
	*(int*)((char*)piVar4 + 0x2b0) = 0;
	void* behaviorMgr = FUN_00b3d260();
	vv1(behaviorMgr, 0x38, (char*)piVar4 + 0x58);

	if (flagA != 0)
	{
		*(char*)((char*)piVar4 + 0xbd) = 0;
		int iVar = *(int*)((char*)piVar4 + 0xb54);
		if (iVar != 0)
			*(int*)(iVar + 0x54) = 2;
	}
	FUN_00c035f0(piVar4);
	return piVar4;
}
