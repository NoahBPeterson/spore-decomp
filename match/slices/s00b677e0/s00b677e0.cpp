// s00b677e0 -- Spore label helpers: colour / size / population of the object a label refers to.
// Rebuilt from the shipped PE.  The engine identifies classes by 32-bit type hashes; those are kept
// as literals here because the original spelling is not recoverable.
//
// Module flags: /O2 /MD /Gy /TP

#include <xmmintrin.h>
#include <math.h>

struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct Obj;

struct Vtbl
{
	void* s00;                                        // 0x000
	void* s04;                                        // 0x004
	void  (__thiscall* m08)(Obj*);                    // 0x008  release
	void* (__thiscall* query)(Obj*, int);             // 0x00c  interface cast
	void* s10;                                        // 0x010
	void* s14;                                        // 0x014
	void* s18;                                        // 0x018
	void* s1c;                                        // 0x01c
	int   (__thiscall* m20)(Obj*);                    // 0x020  class id
	void* s24;                                        // 0x024
	void* s28;                                        // 0x028
	float*(__thiscall* m2c)(Obj*);                    // 0x02c  world position
	void* (__thiscall* m30)(Obj*);                    // 0x030
	void* s34;                                        // 0x034
	int   (__thiscall* type)(Obj*);                   // 0x038  type hash
	void* s3c;                                        // 0x03c
	void* s40;                                        // 0x040
	void* s44;                                        // 0x044
	void* s48;                                        // 0x048
	int   (__thiscall* m4c)(Obj*);                    // 0x04c  owner id
	void* s50;                                        // 0x050
	void* s54;                                        // 0x054
	int   (__thiscall* m58)(Obj*);                    // 0x058
	void* (__thiscall* m5c)(Obj*);                    // 0x05c
	void* s60;                                        // 0x060
	void* s64;                                        // 0x064
	float*(__thiscall* m68)(Obj*);                    // 0x068
	void* s6c;                                        // 0x06c
	void* s70;                                        // 0x070
	void* s74;                                        // 0x074
	void* s78;                                        // 0x078
	void* s7c;                                        // 0x07c
	void* s80;                                        // 0x080
	void* (__thiscall* m84)(Obj*);                    // 0x084
	void* s88;                                        // 0x088
	void* s8c;                                        // 0x08c
	void* s90;                                        // 0x090
	void* s94;                                        // 0x094
	void* s98;                                        // 0x098
	void* s9c;                                        // 0x09c
	void* sa0;                                        // 0x0a0
	void* sa4;                                        // 0x0a4
	void* sa8;                                        // 0x0a8
	void* sac;                                        // 0x0ac
	void* sb0;                                        // 0x0b0
	void* sb4;                                        // 0x0b4
	void* sb8;                                        // 0x0b8
	void* sbc;                                        // 0x0bc
	void* sc0;                                        // 0x0c0
	void* sc4;                                        // 0x0c4
	void* sc8;                                        // 0x0c8
	void* scc;                                        // 0x0cc
	char  (__thiscall* md0)(Obj*);                    // 0x0d0
	void* sd4;                                        // 0x0d4
	void* sd8;                                        // 0x0d8
	void* sdc;                                        // 0x0dc
	float*(__thiscall* me0)(Obj*);                    // 0x0e0
	void* se4;                                        // 0x0e4
	void* se8;                                        // 0x0e8
	void* sec;                                        // 0x0ec
	void* sf0;                                        // 0x0f0
	void* sf4;                                        // 0x0f4
	void* sf8;                                        // 0x0f8
	void* sfc;                                        // 0x0fc
	void* s100;                                       // 0x100
	void* s104;                                       // 0x104
	void  (__thiscall* m108)(Obj*, void*);            // 0x108
};

struct Obj
{
	Vtbl* vt;                                         // 0x000
};

// thiscall helpers, modelled as methods so the compiler emits the right convention
struct NounMgr
{
	void* Func_b25f40(int id);                        // 0x00b25f40  noun by id
	void* Func_bfc5f0();                              // 0x00bfc5f0  player tribe
	int   Func_b1f9d0();                              // 0x00b1f9d0  player empire or -1
};
struct StarMgr
{
	void* Func_ba9370(int id);                        // 0x00ba9370  empire by id
};
struct RelMgr
{
	char  Func_d01b50(int owner, int player);         // 0x00d01b50  at war
	int   Func_d00a70(int owner, int player, int f);  // 0x00d00a70  relation code
};
struct TribeObj
{
	int GetMaxPopulation();                           // 0x00c8eae0
	int GetAdultPopulation();                         // 0x00c8f370
};
struct EmpireObj
{
	Vec3 GetColor();                                  // 0x00c32cd0  (sret)
};
struct PropObj
{
	float Func_bfc490();                              // 0x00bfc490  float property
};
struct ObjBce5c0
{
	void* Func_bce5c0();                              // 0x00bce5c0
};
struct ObjC9d9e0
{
	void* Func_c9d9e0();                              // 0x00c9d9e0
};
struct ObjC04750
{
	void* Func_c04750();                              // 0x00c04750
};
struct ObjC37710
{
	void* Func_c37710();                              // 0x00c37710
};
struct CitizenObj
{
	char  Func_c232c0();                              // 0x00c232c0  is tribe member
	void* Func_c22f50();                              // 0x00c22f50  tribe
	void* Func_c23e40();                              // 0x00c23e40  city
};
struct PlacementObj
{
	void* Func_ba3f90(void* a, void* b, int c);       // 0x00ba3f90
};
struct SpeciesMgr
{
	void* Func_4e0050(int a, int b);                  // 0x004e0050  archetype
};
struct LayoutObj
{
	void Func_811ad0(int flag);                       // 0x00811ad0  shutdown
};
struct LabelMgr
{
	void* Func_b721d0(int* entry);                    // 0x00b721d0  find entry
};

// cdecl / no-argument engine entry points
void* __cdecl SP_GetCurrentGameMode();                // 0x00b5b800
void* __cdecl SP_NounManager();                       // 0x00b3d300
void* __cdecl SP_StarManager();                       // 0x00b3d2a0
void* __cdecl SP_RelationshipManager();               // 0x00b3d2c0
void* __cdecl SP_App();                               // 0x0067dd10
int   __cdecl FUN_01021090();                         // 0x01021090  player empire id
void* __cdecl FUN_00b3d4c0();                         // 0x00b3d4c0
void* __cdecl FUN_00401090();                         // 0x00401090  species manager
void* __cdecl FUN_00cd40b0();                         // 0x00cd40b0  tribe-mode strategy
void  __cdecl FUN_00805ea0(Vec4* area);               // 0x00805ea0  main window area
void* __cdecl FUN_00811ad0(void* p, int f);           // 0x00811ad0

void* __cdecl FUN_00eec990(void*);                    // 0x00eec990
void* __cdecl FUN_00b6f0c0(int);                      // 0x00b6f0c0
void* __cdecl FUN_00b676c0(void*);                    // 0x00b676c0
void* __cdecl FUN_00b676e0(void*);                    // 0x00b676e0
void* __cdecl FUN_00b18700(void*);                    // 0x00b18700
char  __cdecl FUN_00b18760(void*);                    // 0x00b18760
void* __cdecl FUN_00c0c380(void*);                    // 0x00c0c380
void* __cdecl FUN_00ac80d0(void*, int);               // 0x00ac80d0
void* __cdecl FUN_00ac8960(void*);                    // 0x00ac8960
void* __cdecl FUN_00ac86d0(void*);                    // 0x00ac86d0
void* __cdecl FUN_00b1fc00(void*);                    // 0x00b1fc00
int   __cdecl FUN_00b677a0(void*);                    // 0x00b677a0
int   __cdecl FUN_00c00ad0(int);                      // 0x00c00ad0
void* __cdecl FUN_00b67700(void*);                    // 0x00b67700
char  __cdecl FUN_00c88e30(void*);                    // 0x00c88e30

// ---------------------------------------------------------------------------------------------------------
// data
// ---------------------------------------------------------------------------------------------------------
extern "C"
{
	extern const float DAT_01687910[3];               // 0x01687910
	extern const float DAT_0168791c[3];               // 0x0168791c
	extern const float DAT_01687928[3];               // 0x01687928
	extern const float DAT_01687934[3];               // 0x01687934
	extern const float DAT_0156b008[3];               // 0x0156b008
	extern float DAT_0168794c;                        // 0x0168794c
	extern float DAT_01687950;                        // 0x01687950
	extern float DAT_01687954;                        // 0x01687954
	extern int   DAT_01687958;                        // 0x01687958
	extern float DAT_01687940;                        // 0x01687940
	extern float DAT_01687944;                        // 0x01687944
	extern float DAT_01687948;                        // 0x01687948
	extern const float DAT_01485720;                  // 0x01485720  1.0
	extern const float DAT_013f6b64;                  // 0x013f6b64
	extern const float DAT_01464988;                  // 0x01464988
	extern const float DAT_013ec488;                  // 0x013ec488  -0.5
	extern const float DAT_01471064;                  // 0x01471064  0.5
	extern const float DAT_013eb1bc;                  // 0x013eb1bc  -1.0
	extern char DAT_01654c02;                         // 0x01654c02
	extern char DAT_01654c05;                         // 0x01654c05
	extern char DAT_01654c10;                         // 0x01654c10
	extern void* g_pLabelMgr;                         // 0x01687348
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00b677e0 -- colour of the object a label points at
// @ 0x00b677e0
Vec3 FUN_00b677e0(Obj* o)
{
	Vec3 out;

	if (SP_GetCurrentGameMode() == &DAT_01654c10)
	{
		switch ((int)FUN_00eec990(o))
		{
		case 2:
			out.x = DAT_01687910[0]; out.y = DAT_01687910[1]; out.z = DAT_01687910[2];
			return out;
		case 3:
			out.x = DAT_0168791c[0]; out.y = DAT_0168791c[1]; out.z = DAT_0168791c[2];
			return out;
		case 4:
			out.x = DAT_01687928[0]; out.y = DAT_01687928[1]; out.z = DAT_01687928[2];
			return out;
		case 5:
			out.x = DAT_01687934[0]; out.y = DAT_01687934[1]; out.z = DAT_01687934[2];
			return out;
		default:
			out.x = DAT_0156b008[0]; out.y = DAT_0156b008[1]; out.z = DAT_0156b008[2];
			return out;
		}
	}

	switch (o->vt->type(o))
	{
	case 0x436f315:
	case 0xee9b2232:
	case 0x137e8e0:
	case 0x1a55e4d:
	case 0xff10521:
	case 0x70704db:
	case 0xecade42:
	case 0x1007ae63:
		{
			void* v = ((NounMgr*)SP_NounManager())->Func_b25f40(o->vt->m4c(o));
			if (v != 0)
				return *(Vec3*)((char*)v + 0xc4);
		}
		break;

	case 0x116d858:
		{
			void* v = ((ObjC9d9e0*)FUN_00b18700(o))->Func_c9d9e0();
			if (v != 0)
				return *(Vec3*)((char*)FUN_00b6f0c0(*(int*)((char*)v + 0x234)));
		}
		break;

	case 0xb033b403:
		{
			int id = o->vt->m4c(o);
			EmpireObj* e = (EmpireObj*)((StarMgr*)SP_StarManager())->Func_ba9370(id);
			if (e != 0)
				return e->GetColor();
		}
		break;

	case 0xd0036e08:
		if (FUN_00b18760(o) != 0)
		{
			if ((DAT_01687958 & 1) == 0)
			{
				DAT_01687958 |= 1;
				DAT_0168794c = DAT_01485720;
				DAT_01687950 = DAT_013f6b64;
				DAT_01687954 = DAT_01464988;
			}
			out.x = DAT_0168794c; out.y = DAT_01687950; out.z = DAT_01687954;
			return out;
		}
		break;

	case 0xee02c7:
		{
			Obj* p = (Obj*)FUN_00b676e0(o);
			if (p != 0)
			{
				Obj* q = (Obj*)p->vt->m5c(p);
				if (q != 0)
					return *(Vec3*)((char*)FUN_00b6f0c0(*(int*)((char*)q + 0x234)));
			}
		}
		break;

	case 0x629baec:
		{
			void* v = (void*)*(int*)((char*)FUN_00b676c0(o) + 0x10c);
			if (v != 0)
				return *(Vec3*)((char*)FUN_00b6f0c0(*(int*)((char*)v + 0x234)));
		}
		break;

	case 0x4f176642:
		{
			Obj* p = (Obj*)FUN_00c0c380(o);
			return *(Vec3*)p->vt->me0(p);
		}

	case 0x4f396a66:
		{
			void* v = FUN_00ac80d0(o, 0x18c6d19);
			if (v != 0)
				return *(Vec3*)((char*)FUN_00b6f0c0(*(int*)((char*)v + 0x234)));
		}
		break;

	default:
		break;
	}

	out.x = DAT_0156b008[0]; out.y = DAT_0156b008[1]; out.z = DAT_0156b008[2];
	return out;
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00b67b90 -- rounded size property (building / creature size) of an object
// @ 0x00b67b90
int FUN_00b67b90(Obj* o)
{
	void* p = o != 0 ? o->vt->query(o, 0x13f94d4) : 0;

	switch (o->vt->type(o))
	{
	case 0x436f315:
	case 0x116d858:
	case 0xb033b403:
	case 0xd0036e08:
	case 0xee02c7:
	case 0x137e8e0:
	case 0x1a55e4d:
	case 0xff10521:
	case 0x4e3faaf:
	case 0x70704db:
	case 0xecade42:
	case 0x1007ae63:
	case 0x4f176642:
		{
			float f = *(float*)((char*)p + 0x38);
			int n = _mm_cvtss_si32(_mm_set_ss(f));
			if ((float)n < f)
				n++;
			return n;
		}
	case 0xee9b2232:
		return 0;
	case 0x1b92b27:
		return 0;
	default:
		return 0;
	}
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00b67c70 -- label kind (0..17) of an object
// @ 0x00b67c70
int FUN_00b67c70(Obj* o)
{
	switch (o->vt->type(o))
	{
	case 0x436f315:
		return 9;
	case 0x116d858:
		{
			Obj* p = (Obj*)o->vt->query(o, 0x116d858);
			if (p != 0 && p->vt->m58(p) == 10)
				return 0x11;
			return 2;
		}
	case 0xee9b2232:
		return 7;
	case 0xb033b403:
		return 0xb;
	case 0xd0036e08:
		return 0xc;
	case 0xee02c7:
		return 4;
	case 0x137e8e0:
		return 6;
	case 0x1a55e4d:
		return 9;
	case 0x1b92b27:
		return 0xe;
	case 0xff10521:
		return 9;
	case 0x4e3faaf:
		return 10;
	case 0x70704db:
		return 9;
	case 0xecade42:
		return 9;
	case 0x1007ae63:
		return 8;
	case 0x4f176642:
		return 3;
	case 0x4f396a66:
		return 5;
	case 0x629baec:
		return 0xd;
	default:
		{
			int h = FUN_00b677a0(o);
			if (h == (int)0xcf56099a || h == 0x6031c03a)
				return 0x10;
			return 0x11;
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00b67dc0 -- project a world position to screen.  The original passes the source vector in ESI and
// the destination Vec2 in EDI (whole-program register calling convention), so the C form below is a
// semantic reconstruction only.
// @ 0x00b67dc0
struct AppVtbl
{
	char pad[0x58];
	void* (__thiscall* m58)(void*);                   // 0x058
};

struct App
{
	AppVtbl* vt;
	void Transform(Vec2* out, const Vec3* in);        // 0x007c4180
};

bool FUN_00b67dc0(const Vec3* in, Vec2* out)
{
	App* app = (App*)SP_App();
	float* m = (float*)app->vt->m58(app);
	float x = in->x, y = in->y, z = in->z;

	float w = DAT_01687948 * (m[0x68 / 4] * z + m[0x48 / 4] * x + m[0x58 / 4] * y + m[0x78 / 4])
	        + DAT_01687940 * (m[0x60 / 4] * z + m[0x50 / 4] * y + m[0x40 / 4] * x + m[0x70 / 4])
	        + DAT_01687944 * (m[0x64 / 4] * z + m[0x44 / 4] * x + m[0x54 / 4] * y + m[0x74 / 4]);

	if (w < 0.0f)
		return false;

	Vec2 p;
	app->Transform(&p, in);
	*out = p;

	return p.x <= DAT_01485720 && p.x >= DAT_013eb1bc &&
	       p.y <= DAT_01485720 && p.y >= DAT_013eb1bc;
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00b67ef0 -- screen-space anchor of a label, in normalised window coordinates
// @ 0x00b67ef0
bool FUN_00b67ef0(Obj* o, Vec2* out, Vec2* out2)
{
	float def[6] = { DAT_013ec488, DAT_013ec488, 0.0f,
	                 DAT_01471064, DAT_01471064, DAT_01485720 };
	float* pos;

	if ((*(unsigned int*)((char*)o + 0x50) & 0x10) == 0 ||
	    (*(unsigned int*)((char*)o + 0x50) & 0x20) != 0)
		pos = o->vt->m68(o);
	else
		pos = def;

	float h = pos[5];
	float* v = o->vt->m2c(o);
	float x = v[0], y = v[1], z = v[2];
	float inv = 1.0f / sqrtf(x * x + y * y + z * z);

	Vec3 p;
	p.x = x + (inv * x) * h;
	p.y = y + (inv * y) * h;
	p.z = z + (inv * z) * h;

	Vec2 s;
	bool ok = FUN_00b67dc0(&p, &s);

	FUN_00805ea0((Vec4*)def);

	float fx = ((s.x + DAT_01485720) * def[2]) * DAT_01471064;
	float fy = ((DAT_01485720 - s.y) * def[3]) * DAT_01471064;

	out->x = fx;
	out->y = fy;
	if (out2 != 0)
	{
		out2->x = fx;
		out2->y = fy;
	}

	return FUN_00c88e30(o) == 0 && ok;
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00b68090 -- ownership relation code (0 = own, 2..6 = relationship)
// @ 0x00b68090
int FUN_00b68090(Obj* o)
{
	switch (o->vt->type(o))
	{
	case 0xee9b2232:
	case 0x901f1362:
	case 0xb033b403:
	case 0x4f396a66:
		break;
	default:
		return 0;
	}

	int player;
	if (SP_GetCurrentGameMode() == &DAT_01654c02)
	{
		Obj* t = (Obj*)((NounMgr*)SP_NounManager())->Func_bfc5f0();
		player = t->vt->m4c(t);
	}
	else if (SP_GetCurrentGameMode() == &DAT_01654c05)
	{
		player = FUN_01021090();
	}
	else
	{
		player = ((NounMgr*)SP_NounManager())->Func_b1f9d0();
	}

	int owner = o->vt->m4c(o);
	if (player == owner)
		return 0;
	if (owner == -1)
		return 5;

	Obj* c = (Obj*)o->vt->query(o, 0xb033b403);
	if (c != 0 && ((ObjC37710*)c)->Func_c37710() != 0)
	{
		if (!((RelMgr*)SP_RelationshipManager())->Func_d01b50(owner, player))
		{
			void* v = FUN_00b67700(((ObjC37710*)c)->Func_c37710());
			if (v != 0 && *(char*)((char*)v + 0x21c) != 0)
				return 5;
		}
	}

	switch (((RelMgr*)SP_RelationshipManager())->Func_d00a70(owner, player, 1))
	{
	case 0:
		return 5;
	case 1:
		return 2;
	case 2:
		return 3;
	case 3:
		return 4;
	case 4:
		return 6;
	}
	return 0;
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00b681d0 -- max population cap of the object's tribe (first matching tier)
// @ 0x00b681d0
int FUN_00b681d0(Obj* o)
{
	void* tribe = 0;

	if (o != 0)
	{
		if (o->vt->m20(o) == 0x18c6d19)
		{
			tribe = o;
		}
		else
		{
			Obj* p = (Obj*)o->vt->query(o, 0xee02c7);
			if (p != 0)
				tribe = p->vt->m5c(p);
		}
	}

	if (tribe == 0)
		return 0;

	int max = ((TribeObj*)tribe)->GetMaxPopulation();
	for (int i = 0; i < 7; i++)
	{
		int v = FUN_00c00ad0(i);
		if (v >= max)
			return v;
	}
	return ((TribeObj*)tribe)->GetMaxPopulation();
}


// ---------------------------------------------------------------------------------------------------------
// FUN_00b68250 -- adult population of the object's tribe
// @ 0x00b68250
int FUN_00b68250(Obj* o)
{
	if (o != 0)
	{
		if (o->vt->m20(o) == 0x18c6d19)
		{
			TribeObj* t = (TribeObj*)o;
			return t->GetAdultPopulation();
		}

		Obj* p = (Obj*)o->vt->query(o, 0xee02c7);
		if (p == 0)
			return 0;
		TribeObj* t = (TribeObj*)p->vt->m5c(p);
		if (t == 0)
			return 0;
		return t->GetAdultPopulation();
	}
	return 0;
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00b682a0 -- player-owner of the object (tribe / city / empire), used to colour labels
// @ 0x00b682a0
int FUN_00b682a0(Obj* o)
{
	switch (o->vt->type(o))
	{
	case 0x436f315:
		{
			void* v = ((ObjBce5c0*)o->vt->query(o, 0x436f315))->Func_bce5c0();
			if (v == 0)
				return 0;
			return FUN_00b68090((Obj*)v);
		}
	case 0x116d858:
		{
			void* v = ((ObjC9d9e0*)o->vt->query(o, 0x116d858))->Func_c9d9e0();
			if (v == 0)
				return 0;
			return FUN_00b68090((Obj*)v);
		}
	case 0xee9b2232:
		{
			void* v = FUN_00ac86d0(o);
			if (v == 0)
				return 0;
			return FUN_00b68090((Obj*)v);
		}
	case 0xb033b403:
		return FUN_00b68090(o);

	case 0xd0036e08:
		{
			Obj* c = (Obj*)FUN_00ac8960(o);
			char* v = (char*)((ObjC04750*)c)->Func_c04750();
			if (v != 0 && *(int*)(v + 0x4ac) == 3 && *(char*)(v + 0x4c8) == 0)
				return 0;
			if ((*(unsigned int*)((char*)c + 0xb58) >> 8) & 1)
				return 6;
			if (((*(unsigned int*)((char*)c + 0xb58) >> 4) & 1) && c->vt->md0(c))
				return 7;
			return (int)((PlacementObj*)FUN_00b3d4c0())->Func_ba3f90((char*)c + 0xb28, c, 0);
		}

	case 0xee02c7:
		{
			Obj* p = (Obj*)FUN_00b676e0(o);
			Obj* v = (Obj*)p->vt->m5c(p);
			if (v == 0)
				return 0;
			return FUN_00b68090(v);
		}

	case 0x137e8e0:
		{
			Obj* p = (Obj*)o->vt->query(o, 0x137e8e0);
			if (SP_GetCurrentGameMode() == &DAT_01654c10)
				return 0;
			void* v = ((NounMgr*)SP_NounManager())->Func_b25f40(p->vt->m4c(p));
			if (v == 0)
				return 0;
			return FUN_00b68090((Obj*)v);
		}

	case 0x1b92b27:
		{
			char* x = (char*)FUN_00b1fc00(o);
			if (x == 0)
				return 0;
			if (*(int*)(x + 0x128) == 0)
				return 0;
			if ((*(unsigned char*)(x + 0x124) & 1) == 0)
				return 0;
			int base = *(int*)(*(int*)(x + 0x128) + 0xa4) + 0x504;
			int v = (int)((PlacementObj*)FUN_00b3d4c0())->Func_ba3f90((void*)base, 0, 0);
			if (v == 0)
			{
				char* s = (char*)*(int*)(x + 0x128);
				void* a = ((SpeciesMgr*)FUN_00401090())->Func_4e0050(
					*(int*)(s + 0x88), *(int*)(s + 0xf0));
				if (a != 0)
					v = *(int*)((char*)a + 0x390);
			}
			return v;
		}

	case 0x1a55e4d:
	case 0xff10521:
	case 0xecade42:
	case 0x1007ae63:
		{
			Obj* p = (Obj*)o->vt->query(o, 0xe9cb8ba);
			void* v = p->vt->m84(p);
			if (v == 0)
				return 0;
			return FUN_00b68090((Obj*)v);
		}

	case 0x4e3faaf:
	case 0x70704db:
		return 0;

	case 0x4f176642:
		{
			CitizenObj* p = (CitizenObj*)o->vt->query(o, 0x4f176642);
			if (p->Func_c232c0())
			{
				void* t = p->Func_c22f50();
				if (t == 0)
					return 0;
				return FUN_00b68090((Obj*)t);
			}
			void* c = p->Func_c23e40();
			if (c == 0)
				return 0;
			return FUN_00b68090((Obj*)c);
		}

	case 0x4f396a66:
		{
			void* t = FUN_00ac80d0(o, 0x18c6d19);
			if (t == 0)
				return 0;
			return FUN_00b68090((Obj*)t);
		}

	case 0x629baec:
		{
			Obj* p = (Obj*)o->vt->query(o, 0x629baec);
			return FUN_00b68090((Obj*)p->vt->m30(p));
		}

	default:
		return 0;
	}
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00b685e0 -- vertical label offset of an object
// @ 0x00b685e0
float FUN_00b685e0(Obj* o)
{
	switch (o->vt->type(o))
	{
	case 0x116d858:
	case 0xb033b403:
	case 0xd0036e08:
	case 0xee02c7:
	case 0x1a55e4d:
	case 0x137e8e0:
	case 0xecade42:
	case 0x4e3faaf:
	case 0x436f315:
	case 0x70704db:
	case 0x4f176642:
	case 0xff10521:
	case 0x1007ae63:
		{
			Obj* p = (Obj*)o->vt->query(o, 0x13f94d4);
			return ((PropObj*)p)->Func_bfc490();
		}
	case 0x2a8fe3c:
		return 0.0f;
	case 0xee9b2232:
		return 0.0f;
	case 0x175cdc9:
		return 0.0f;
	case 0x1b92b27:
		return 0.0f;
	case 0x3a25119:
		return 0.0f;
	default:
		return 0.0f;
	}
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00b686a0 -- close the label UI of an object; the original receives its argument in EAX
// (whole-program register calling convention), approximated here as an ordinary parameter.
// @ 0x00b686a0
void FUN_00b686a0(int* entry)
{
	int* e = (int*)((LabelMgr*)g_pLabelMgr)->Func_b721d0(entry);
	if (e == 0 || e[0x50 / 4] == 0)
		return;

	if (SP_GetCurrentGameMode() == &DAT_01654c02)
	{
		Obj* o = (Obj*)e[1];
		if (o->vt->type(o) == 0xee02c7)
		{
			char* s = (char*)FUN_00cd40b0();
			if (s != 0)
				s += 4;
			else
				s = 0;
			Obj* c = (Obj*)e[0xac / 4];
			c->vt->m108(c, s);
		}
	}

	((LayoutObj*)e[0x50 / 4])->Func_811ad0(1);

	Obj* p = (Obj*)e[0x50 / 4];
	if (p != 0)
	{
		e[0x50 / 4] = 0;
		p->vt->m08(p);
	}
}
