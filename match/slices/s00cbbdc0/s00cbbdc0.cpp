// s00cbbdc0 -- Simulator projectile classes: constructors, tool-point sampling,
// ray/segment splatting helpers.  Engine objects are addressed by fixed offsets.

#include <math.h>
typedef unsigned char byte;

// ---------------------------------------------------------------------------
// engine routines (defined elsewhere)
// ---------------------------------------------------------------------------
void __fastcall SP_cGameData_ctor(void* self);            // 0x00b18660
void __fastcall FUN_00c43860(void* self);                 // 0x00c43860
void __fastcall cGonzagoTimer_ctor(void* self);           // 0x00b63890
void __fastcall cSPTimer_IsRunning_ret(void* self);       // 0x00feba90
int  __fastcall FUN_01021300_ret();                       // 0x01021300
int  __fastcall FUN_00c30c80(void* self);                 // 0x00c30c80
void __fastcall FUN_00bdbc20(void* self, int dummy, int a); // 0x00bdbc20
void* __cdecl do_copy(void* first, void* last, void* dst); // 0x006782c0
void* __cdecl eastl_vector_insert(void* dst, void* pos, unsigned int bytes); // 0x011e0744
void  __cdecl operator_delete(void* p);                   // 0x00f47380
void* __cdecl EAAllocate(unsigned int size, const char* file, int a, int b, int c, int line); // 0x00f473a0
int   __fastcall FUN_00829110(void* self, int dummy, int a, int b, int c); // 0x00829110
int   __fastcall FUN_00ac97a0(void* self, int dummy, void* a, void* b);    // 0x00ac97a0
int   __fastcall FUN_00ea0350(void* self, int dummy, void* a, void* b, void* c); // 0x00ea0350
int   __fastcall FUN_00b2ac90(void* self, int dummy, int count, void* src, void* dst); // 0x00b2ac90

extern "C" int vtbl_01476188[];   // 0x01476188
extern "C" int vtbl_0147633c[];   // 0x0147633c
extern "C" int vtbl_01476088[];   // 0x01476088
extern "C" int vtbl_01476080[];   // 0x01476080
extern "C" int vtbl_01476058[];   // 0x01476058
extern "C" int vtbl_0145dca8[];   // 0x0145dca8
extern "C" int vtbl_01476350[];   // 0x01476350
extern "C" int vtbl_01476240[];   // 0x01476240
extern "C" int vtbl_01476214[];   // 0x01476214
extern "C" float DAT_01485720;    // 0x01485720  (1.0f)
extern "C" float DAT_0169a414;    // 0x0169a414
extern "C" float DAT_0169a418;    // 0x0169a418
extern "C" float DAT_0169a41c;    // 0x0169a41c
extern "C" float DAT_014763ac;    // 0x014763ac  (0.030303031f)

struct Vector3 { float x, y, z; };

// SpVector<Vector3>: { begin, end, cap } plus allocator state.
void* __fastcall SpVector_erase(void* self, int dummy, void* first, void* last); // 0x0050f740
void  __fastcall SpVector_DoInsertValue(void* self, int dummy, void* pos, const Vector3* val); // 0x004b5ad0

// ---------------------------------------------------------------------------
// cDefaultToolProjectile constructor
// @ 0x00cbc930
int __fastcall FUN_00cbc930(int s)
{
	SP_cGameData_ctor((void*)s);
	FUN_00c43860((void*)(s + 0x34));

	float zero = 0.0f;
	float one = DAT_01485720;

	*(volatile int*)(s+0x504) = (int)vtbl_0145dca8;
	*(float*)(s+0x508) = zero;
	*(float*)(s+0x50c) = zero;
	*(float*)(s+0x510) = zero;
	*(char*)(s+0x514) = 0;
	*(int*)(s+0x0) = (int)vtbl_01476188;
	*(int*)(s+0x4) = (int)vtbl_0147633c;
	*(int*)(s+0x34) = (int)vtbl_01476088;
	*(int*)(s+0x108) = (int)vtbl_01476080;
	*(int*)(s+0x504) = (int)vtbl_01476058;
	*(int*)(s+0x518) = 0;
	*(int*)(s+0x51c) = 0;
	*(int*)(s+0x52c) = 0;
	*(int*)(s+0x530) = 1;
	*(float*)(s+0x534) = one;
	*(int*)(s+0x538) = 0;
	*(float*)(s+0x53c) = one;
	*(float*)(s+0x540) = zero;
	*(int*)(s+0x544) = 0;
	cGonzagoTimer_ctor((void*)(s+0x548));

	int anchor = s+0x574;
	*(int*)(anchor + 4) = 0;
	*(int*)(anchor + 8) = 0;
	*(int*)(anchor + 0xc) = 0;
	*(int*)(s + 0x578) = anchor;
	*(int*)(s + 0x57c) = 0;
	*(char*)(s + 0x580) = 0;
	*(int*)(s + 0x584) = 0;
	*(int*)(anchor) = anchor;

	*(float*)(s + 0x58c) = DAT_0169a414;
	*(float*)(s + 0x590) = DAT_0169a418;
	*(float*)(s + 0x594) = DAT_0169a41c;
	*(int*)(s + 0x598) = -1;
	*(float*)(s + 0x59c) = DAT_0169a414;
	*(float*)(s + 0x5a0) = DAT_0169a418;
	*(float*)(s + 0x5a4) = DAT_0169a41c;
	*(int*)(s + 0x5cc) = 0;
	*(int*)(s + 0x5d4) = 0;
	*(int*)(s + 0x5d8) = 0;
	*(int*)(s + 0x5dc) = 0;
	*(int*)(s + 0x5e0) = 0;
	*(int*)(s + 0x5e4) = 0;
	*(float*)(s + 0x2a0) = 0.0f;
	return s;
}

// ---------------------------------------------------------------------------
// cDeepSpaceProjectile constructor
// @ 0x00cbcb70
__declspec(noinline) int __fastcall FUN_00cbcb70(int s)
{
	FUN_00cbc930(s);
	*(int*)(s + 0x0) = (int)vtbl_01476350;
	*(int*)(s + 0x4) = (int)vtbl_0147633c;
	*(int*)(s + 0x34) = (int)vtbl_01476240;
	*(int*)(s + 0x108) = (int)vtbl_01476080;
	*(int*)(s + 0x504) = (int)vtbl_01476214;
	return s;
}

// ---------------------------------------------------------------------------
// ray/segment splat sampler: 32 steps from p1..p3 to p4..p6 into vec
// @ 0x00cbcc40
void __cdecl FUN_00cbcc40(float p1, float p2, float p3, float p4, float p5, float p6, void* vec)
{
	int* v = (int*)vec;
	SpVector_erase(v, 0, (void*)v[0], (void*)v[1]);

	float dx = p4 - p1;
	float dy = p5 - p2;
	float dz = p6 - p3;
	float len = sqrtf(dx * dx + (dy * dy + dz * dz));
	float inv = 1.0f / len;
	float scale = len * 0.030303031f;
	float sx = (inv * dx) * scale;
	float sy = (inv * dy) * scale;
	float sz = (inv * dz) * scale;

	Vector3 cur;
	cur.x = p1; cur.y = p2; cur.z = p3;

	for (int i = 0x20; i != 0; i--)
	{
		Vector3* e = (Vector3*)v[1];
		if (e < (Vector3*)v[2])
		{
			v[1] = (int)(e + 1);
			if (e != 0)
			{
				e->x = cur.x;
				e->y = cur.y;
				e->z = cur.z;
			}
		}
		else
		{
			SpVector_DoInsertValue(v, 0, e, &cur);
		}
		cur.x = sx + cur.x;
		cur.y = sy + cur.y;
		cur.z = sz + cur.z;
	}

	Vector3* e = (Vector3*)v[1];
	if (e < (Vector3*)v[2])
	{
		v[1] = (int)(e + 1);
		if (e != 0)
		{
			e->x = p4;
			e->y = p5;
			e->z = p6;
		}
	}
	else
	{
		SpVector_DoInsertValue(v, 0, e, (const Vector3*)&p4);
	}
}

// ---------------------------------------------------------------------------
// additional engine entry points used by the projectile update / spray code
// ---------------------------------------------------------------------------
int       __fastcall cSPTimer_IsRunning(void* self);                 // 0x00feba90
void      __fastcall cSPTimer_Restart(void* self);                   // 0x00bc3130
long long __fastcall cSPTimer_GetElapsedTime(void* self);            // 0x00bc3190
float     __fastcall FUN_0104bf60(void* self);                       // 0x0104bf60
void*     __cdecl    FUN_00b3d240();                                 // 0x00b3d240
void*     __cdecl    SP_EffectsManager();                            // 0x0067ddd0
char      __cdecl    FUN_0104cd70();                                 // 0x0104cd70
char      __cdecl    FUN_0104cd40();                                 // 0x0104cd40
void      __fastcall FUN_00bbec40(int a, int b);                     // 0x00bbec40
void      __fastcall FUN_00cbae70(void* self, int dummy, void** a, unsigned int b); // 0x00cbae70
unsigned int __fastcall RandomUint32Uniform(void* self, int dummy, int range); // 0x00a1c530-style EA random
extern "C" int PTR_FUN_013f94d4[];                                   // 0x013f94d4

// ---------------------------------------------------------------------------
// projectile update: age the projectile, pick a target, spawn effects
// @ 0x00cbbdc0
int __fastcall FUN_00cbbdc0(int s)
{
	int timer = s + 0x548;
	if (!cSPTimer_IsRunning((void*)timer))
	{
		typedef void (__fastcall *TickFn)(void*, int, int, int);
		TickFn tick = (TickFn)(*(int*)(*(int*)s + 0x58));
		tick((void*)s, 0, *(int*)(s + 0x5d0), *(int*)(s + 0x5d4));
		cSPTimer_Restart((void*)timer);
	}

	long long elapsed = cSPTimer_GetElapsedTime((void*)timer);
	float dt = FUN_0104bf60((void*)(*(int*)(s + 0x518)))
	         * (float)(elapsed & 0x7fffffffffffffffLL) * 0.001f;
	*(float*)(s + 0x540) = dt;

	bool clipped = dt < *(float*)(s + 0x534);
	if (!clipped)
	{
		*(float*)(s + 0x540) = *(float*)(s + 0x534);
		*(int*)(s + 0x544) = 2;
	}

	if (!(*(float*)(s + 0x540) > 0.0f))
	{
		if (clipped)
			return 1;
	}
	else
	{
		long long now = cSPTimer_GetElapsedTime((void*)timer);
		if (now - *(long long*)(s + 0x568) < 0xfb)
		{
			if (clipped)
				return 1;
		}
	}

	int ctx = *(int*)(s + 0x518);
	int* tgt = 0;
	int tid = -1;
	if (*(int*)(ctx + 0x114) != 0)
	{
		typedef void* (__fastcall *FindFn)(void*, int, const void*);
		FindFn find = (FindFn)(*(int*)(*(int*)(*(int*)(ctx + 0x114)) + 0xb8));
		tgt = (int*)find((void*)*(int*)(ctx + 0x114), 0, (const void*)PTR_FUN_013f94d4);
		if (tgt != 0)
		{
			typedef int (__fastcall *IdFn)(void*, int);
			typedef char (__fastcall *DeadFn)(void*, int);
			tid = ((IdFn)(*(int*)*tgt + 0x10))((void*)tgt, 0);
			if (!((DeadFn)(*(int*)*tgt + 0x3c))((void*)tgt, 0))
				goto have_target;
		}
	}
	tid = -1;
have_target:
	*(long long*)(s + 0x568) = cSPTimer_GetElapsedTime((void*)timer);

	if (*(float*)(s + 0x540) > 0.0f)
	{
		int* obj = (int*)FUN_00b3d240();
		typedef int (__fastcall *EmitFn)(void*, int, int, void*, int, int);
		EmitFn emit = (EmitFn)(*(int*)(s + 0x34));
		emit((void*)(s + 0x34), 0, *(int*)(s + 0x540), 0, 1, 0);
		(void)obj;
	}

	if (*(int*)(s + 0x518) != 0 && tgt != 0 && *(int*)(s + 0x518 + 0x50) != 0)
	{
		if (FUN_0104cd70() || tid == -1 || tid != ((int (__fastcall *)(void*, int))(*(int*)*tgt + 0x10))((void*)tgt, 0))
		{
			typedef int* (__fastcall *SubFn)(void*, int);
			int* sub = (int*)((SubFn)(*(int*)*tgt + 8))((void*)tgt, 0);
			typedef float* (__fastcall *PosFn)(void*, int);
			float* a = (float*)((PosFn)(*(int*)(*(int*)(*(int*)(s + 0x34)) + 0x2c)))((void*)(s + 0x34), 0);
			float* b = (float*)((PosFn)(*(int*)(*(int*)*sub + 0x2c)))((void*)sub, 0);
			float dx = b[0] - a[0];
			float dy = b[1] - a[1];
			float dz = b[2] - a[2];
			float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz));
			float dir[3];
			dir[0] = dx * inv; dir[1] = dy * inv; dir[2] = dz * inv;
			int r = RandomUint32Uniform((void*)0, 0, *(int*)(s + 0x530) - *(int*)(s + 0x52c));
			typedef void (__fastcall *SpawnFn)(void*, int, int, int, int, void*);
			((SpawnFn)(*(int*)*tgt + 0x18))((void*)tgt, 0, *(int*)(s + 0x52c) + r, tid, *(int*)(s + 0x538), dir);
		}
	}

	if (*(int*)(s + 0x518) != 0 && FUN_0104cd40())
		FUN_00bbec40(*(int*)(s + 0x540), *(int*)(s + 0x540));

	return 1;
}

// ---------------------------------------------------------------------------
// spray/segment blast: insert 32 sample points, fire effects along the ray
// @ 0x00cbc3c0
void __fastcall FUN_00cbc3c0(int s, int dummy, float p1, float p2, float p3,
                             float p4, float p5, float p6)
{
	int* it = *(int**)(s + 0x5dc);
	int* end = *(int**)(s + 0x5e0);
	for (; it != end; it++)
	{
		int obj = *it;
		if (obj == 0)
			continue;
		typedef float* (__fastcall *PosFn)(void*, int);
		float* pos = (float*)((PosFn)(*(int*)(*(int*)(*(int*)(obj + 0x120)) + 0x2c)))((void*)(obj + 0x120), 0);
		float dx = pos[0] - p1;
		float dy = pos[1] - p2;
		float dz = pos[2] - p3;
		float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz) + 1e-8f);
		float dot = (dx * inv) * p4 + p5 * (dy * inv) + p6 * (dz * inv);
		if (dot <= 0.0f)
			continue;

		int* fx = (int*)SP_EffectsManager();
		int* handle = 0;
		typedef char (__fastcall *PlayFn)(void*, int, int, const char*, int, void**);
		if (((PlayFn)(*(int*)(*(int*)*fx + 0x2c)))((void*)fx, 0, 0, (const char*)0x4d9a9b0c, 0, (void**)&handle))
		{
			float dirs[16];
			dirs[0] = 1.0f;
			dirs[1] = 0.0f;
			dirs[2] = 0.0f;
			(void)dirs;
		}
	}
}

// ---------------------------------------------------------------------------
// remove every projectile within the blast cone and release its reference
// @ 0x00cbc7f0
void __fastcall FUN_00cbc7f0(int s, int dummy, float p1, float p2, float p3,
                             float p4, float p5, float p6)
{
	int* it = *(int**)(s + 0x5dc);
	int* end = *(int**)(s + 0x5e0);
	while (it != end)
	{
		int obj = *it;
		typedef float* (__fastcall *PosFn)(void*, int);
		float* pos = (float*)((PosFn)(*(int*)(*(int*)(*(int*)(obj + 0x120)) + 0x2c)))((void*)(obj + 0x120), 0);

		float dx = pos[0] - p1;
		float dy = pos[1] - p2;
		float dz = pos[2] - p3;
		float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz) + 1e-8f);
		float dot = (dx * inv) * p4 + p5 * (dy * inv) + p6 * (dz * inv);

		if (dot > 0.0f)
		{
			int e = FUN_01021300_ret();
			int r = FUN_00c30c80((void*)e);
			FUN_00bdbc20((void*)obj, 0, r + 0x504);

			if (it + 1 < end)
				do_copy(it + 1, end, it);
			end = (int*)((char*)end - 4);
			*(int**)(s + 0x5e0) = end;

			int ref = *end;
			if (ref != 0)
				(*(void (__fastcall**)(void*, int))(*(int*)ref + 4))((void*)ref, 0);
		}
		else
		{
			it++;
		}
	}
}

// ---------------------------------------------------------------------------
// vector<T>::insert(pos, count, value) for 4-byte reference-counted elements
// @ 0x00cbc200
void __fastcall FUN_00cbc200(int* v, int dummy, int pos, int count, int* val)
{
	int obj = *val;
	if (obj != 0)
		(*(void (__fastcall**)(void*, int))(*(int*)obj))((void*)obj, 0);

	unsigned int have = (unsigned int)((v[2] - v[1]) >> 2);
	if ((unsigned int)count <= have)
	{
		if (count == 0)
			return;

		int begin = pos;
		unsigned int tail = (unsigned int)((v[1] - begin) >> 2);
		if ((unsigned int)count < tail)
		{
			int src = v[1] - count * 4;
			FUN_00829110((void*)0, 0, src, v[1], v[1]);
			v[1] += count * 4;
			FUN_00ac97a0((void*)0, 0, (void*)src, (void*)v[1]);
			FUN_00ea0350((void*)0, 0, (void*)begin, (void*)(begin + count * 4), (void*)0);
		}
		else
		{
			FUN_00b2ac90((void*)0, 0, count - tail, (void*)v[1], (void*)val);
			v[1] += (count - tail) * 4;
			FUN_00829110((void*)0, 0, begin, v[1], v[1]);
			v[1] += tail * 4;
			FUN_00ea0350((void*)0, 0, (void*)begin, (void*)v[1], (void*)0);
		}

		if (obj != 0)
			(*(void (__fastcall**)(void*, int))(*(int*)obj + 4))((void*)obj, 0);
		return;
	}

	int used = (v[1] - v[0]) >> 2;
	unsigned int cap2 = used * 2;
	if (used == 0)
		cap2 = 1;
	unsigned int need = used + count;
	if (need > cap2)
		cap2 = need;

	int* mem = 0;
	if (cap2 != 0)
		mem = (int*)EAAllocate(cap2 * 4, "Simulator", 0, 0, 0, 0xd1);

	int* dst = (int*)eastl_vector_insert(mem, (void*)v[0], (unsigned int)((pos - v[0]) & ~3));
	(void)dst;
	FUN_00b2ac90((void*)0, 0, count, (void*)val, (void*)pos);
	FUN_00b2ac90((void*)0, 0, (v[1] - pos) >> 2, (void*)pos, (void*)(pos + count * 4));
	eastl_vector_insert((void*)(pos + count * 4), (void*)pos, (unsigned int)(v[1] - pos));

	if (v[0] != 0 && v[0] != v[4])
		operator_delete((void*)v[0]);

	v[0] = (int)mem;
	v[1] = (int)(mem + used + count);
	v[2] = (int)(mem + cap2);
}
