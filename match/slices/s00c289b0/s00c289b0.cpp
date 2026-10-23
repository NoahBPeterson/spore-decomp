// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Slice s00c289b0: SPGonzago creature locomotion helpers (9 functions).
//
// Reconstructed from the retail disassembly of SporeApp.exe (image base 0x400000); raw 32-bit struct
// offsets are used instead of the generated SP headers.  The retail code uses SSE scalar arithmetic
// (movss/addss/mulss/subss/divss) for its float work, which cl15 never emits for plain float math (it
// always uses x87), so only the two float-free functions (00c296b0, 00c29940) can be byte-exact.
//
// Callees that are __thiscall are declared as members of a placeholder class (MSVC 2008 rejects
// __thiscall on free functions) and reached through a cast of the object pointer.
#include <math.h>
#include <xmmintrin.h>

struct Vec3_s00c289b0 { float x, y, z; };
struct Vec4_s00c289b0 { float x, y, z, w; };

// ---- virtual-call helpers (retail does `mov eax,[obj]; mov edx,[eax+slot]; call edx`) ------------
typedef void* (__thiscall *VtFnP)(void*);
typedef float (__thiscall *VtFnF)(void*);
typedef void  (__thiscall *VtFnV)(void*);
typedef void  (__thiscall *VtFnV1)(void*, void*);

static inline void* VtCall0(void* obj, int slot) { return ((VtFnP)(*(void***)obj)[slot / 4])(obj); }
static inline float VtCallF(void* obj, int slot) { return ((VtFnF)(*(void***)obj)[slot / 4])(obj); }
static inline void  VtCallV0(void* obj, int slot) { ((VtFnV)(*(void***)obj)[slot / 4])(obj); }
static inline void  VtCallV1(void* obj, int slot, void* a) { ((VtFnV1)(*(void***)obj)[slot / 4])(obj, a); }

// embedded creature body (self+0xc0): vtable +0x2c -> Vec3*, +0x74 -> float
static inline Vec3_s00c289b0* BodyPos(void* bodyObj) { return (Vec3_s00c289b0*)VtCall0(bodyObj, 0x2c); }
static inline float           BodyFlt(void* bodyObj) { return VtCallF(bodyObj, 0x74); }

// ---- layouts -------------------------------------------------------------------------------------
struct Timing_s00c289b0 { char _pad[0x10]; float step; };

struct Body_s00c289b0 {
	char           _pad000[0x14];
	Vec3_s00c289b0 pos;      // +0x14
	char           _pad020[0x50 - 0x20];
	Vec3_s00c289b0 vel;      // +0x50
	int            m5c;      // +0x5c
	char           _pad060[0x68 - 0x60];
	float          m68;      // +0x68
	float          m6c;      // +0x6c
};

struct Motion_s00c28b40 {
	Vec3_s00c289b0 v;        // +0x00
	char           _pad00c[0x10 - 0xc];
	float          step;     // +0x10
	void*          obj14;    // +0x14
};

struct PathRec_s00c290d0 { Vec3_s00c289b0 p; char _pad[0x3c - 12]; };
struct Path_s00c290d0 {
	PathRec_s00c290d0* begin;   // +0x00
	PathRec_s00c290d0* end;     // +0x04
	char               _pad008[0x14 - 8];
	Vec3_s00c289b0     base;    // +0x14
};

struct XformMsg_s00c289b0 {
	unsigned short m0;       // +0x00
	unsigned short mCount;   // +0x02
	Vec3_s00c289b0 pos;      // +0x04
	float          mScale;   // +0x10
	float          mRot[9];  // +0x14
	void Ctor();             // 0x00434040
};

// The transform-bearing effect; its vtable carries the message accessors at +0x18/+0x20.
struct Eff_s00c289b0 {
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14();
	virtual void SetXform(XformMsg_s00c289b0* m);   // +0x18
	virtual void v1c();                             // +0x1c
	virtual void GetXform(XformMsg_s00c289b0* m);   // +0x20
};

// The creature object; also carries the placeholder declarations of its unnamed retail methods.
struct C_s00c289b0 {
	char     _pad000[0x110];
	unsigned m110;           // +0x110
	char     _pad114[0x137 - 0x114];
	char     m137;           // +0x137
	char     _pad138[0x2b0 - 0x138];
	int      m2b0;           // +0x2b0
	char     _pad2b4[0x330 - 0x2b4];
	unsigned m330;           // +0x330
	char     _pad334[0xb54 - 0x334];
	void*    mB54;           // +0xb54
	char     _padB58[0xb5e - 0xb58];
	char     mB5e;           // +0xb5e
	char     _padB5f[0xf90 - 0xb5f];
	char     mF90;           // +0xf90

	void  SetFlagPair(bool b, unsigned a, unsigned c);                               // 0x00c201a0
	void* GetEffect(unsigned id);                                                    // 0x00c14e70
	bool  Flag388();                                                                 // 0x00c0c0e0
	int   FnC0C2F0();                                                                // 0x00c0c2f0
	void* FnC0EE60();                                                                // 0x00c0ee60
	float* PathAverage(float* out, Path_s00c290d0* path, const float* inEAX);        // 0x00c290d0
};

// Planet model; placeholder declarations of its unnamed retail methods.
struct Pm_s00c289b0 {
	Vec3_s00c289b0* Transform(Vec3_s00c289b0* out, const Vec3_s00c289b0* in);       // 0x00b816f0
	Vec3_s00c289b0* TransformClamp(Vec3_s00c289b0* out, const Vec3_s00c289b0* in);  // 0x00b81630
	float GetWaterHeight();                                                          // 0x00b7e390
	float GetRadius();                                                               // 0x00b7e490
	void  BuildSurfaceOrientation(void* out, const void* pos, const void* dir);      // 0x00b7f250
	Vec3_s00c289b0* RotateTo(Vec3_s00c289b0* out, const Vec3_s00c289b0* in);        // 0x00b7ee70
	float HeightAt(const Vec3_s00c289b0* in);                                        // 0x00b7ecc0
};

struct Chunk_s00c296b0 { char _pad[0x100]; void Ctor(); };   // 0x00af4da0

// ---- plain retail callees / globals --------------------------------------------------------------
void*  __cdecl F_PlanetModel();                          // 0x00b3d350
void*  __cdecl F_GetTriggerMgr();                        // 0x00b3d4d0
void*  __cdecl F_b3d310();                               // 0x00b3d310
void*  __cdecl F_GetCurrentGameMode();                   // 0x00b5b800
Vec3_s00c289b0* __cdecl F_normalized_safe(Vec3_s00c289b0* out, const Vec3_s00c289b0* in);   // 0x00449c20

extern Vec3_s00c289b0 g_168dd78;   // 0x0168dd78
extern char DAT_018eb45e;          // 0x018eb45e
extern char DAT_01654c10;          // 0x01654c10

// =================================================================================================
// @ 0x00c289b0
// Advance a creature body's locomotion timer and, past two thresholds, refresh its surface position
// and velocity.  arg2 = self (creature), arg3 = body, arg4 = flag, arg5 = threshold.
void __cdecl f_00c289b0(Timing_s00c289b0* timing, C_s00c289b0* self, Body_s00c289b0* body, char flag, float thresh)
{
	if (thresh < body->m68 && (*(unsigned char*)((char*)self + 0x330) & 0xb) == 0)
	{
		body->m6c = 0.0f;
		return;
	}

	float t = timing->step + body->m6c;
	body->m6c = t;
	if (t > 0.25f)
	{
		if ((self->m110 & 0x1000) == 0)
		{
			Vec3_s00c289b0 tmp;
			body->pos = *((Pm_s00c289b0*)F_PlanetModel())->Transform(&tmp, &body->pos);
		}

		if (body->m6c > 2.0f)
		{
			if (flag == '\0' || body->m5c != 3)
			{
				self->m330 |= 1;
				return;
			}

			void* bodyObj = (char*)self + 0xc0;
			float s = BodyFlt(bodyObj);
			Vec3_s00c289b0 p;
			p.x = body->pos.x + s * body->vel.x;
			p.y = body->pos.y + s * body->vel.y;
			p.z = body->pos.z + s * body->vel.z;
			Vec3_s00c289b0* bp = BodyPos(bodyObj);
			p.x -= bp->x;
			p.y -= bp->y;
			p.z -= bp->z;
			Vec3_s00c289b0 tmp2;
			body->vel = *F_normalized_safe(&tmp2, &p);
			self->m330 &= 0xfffffff4;
		}
	}
}

// =================================================================================================
// @ 0x00c28b40
// Per-frame creature surface/velocity update (returns false once the creature is in the "done" state).
bool __cdecl f_00c28b40(Motion_s00c28b40* p1, C_s00c289b0* self, Vec3_s00c289b0* dir3, char param4)
{
	bool bVar3 = false;
	Pm_s00c289b0* pm = (Pm_s00c289b0*)F_PlanetModel();
	Vec3_s00c289b0* pfVar7 = BodyPos((char*)self + 0xc0);
	int iVar8 = self->FnC0C2F0();

	float* q = (float*)VtCall0(p1->obj14, 0x68);
	float fVar17 = q[0x14 / 4];
	float fVar1 = q[8 / 4];

	if (self->mB5e == 0 && (self->m110 & 0x1000) != 0)
	{
		bool c = self->Flag388();
		self->m2b0 = c ? 0 : 3;
		*(char*)(*(int*)((char*)self->mB54 + 0x17c) + 0x168c) = self->m137;
		return true;
	}

	if (self->m137 != 0)
		self->m2b0 = 0;

	if ((self->m110 & 0x1000) == 0)
	{
		int st = *(int*)((char*)F_GetTriggerMgr() + 0x2c);
		bool skip = (st == 1 || st == 2) || (iVar8 < 2 && self->mF90 == 0);
		if (skip)
		{
			if (param4 != 0)
				return !bVar3;
		}
		else
		{
			if (param4 != 0)
				return !bVar3;

			float len = sqrtf(pfVar7->x * pfVar7->x + pfVar7->y * pfVar7->y + pfVar7->z * pfVar7->z);
			float wh = pm->GetWaterHeight();
			float dist2 = 0.0f;
			float diff = len - wh;

			if (self->Flag388())
			{
				void* t = self->FnC0EE60();
				if (t)
				{
					void* a = VtCall0(t, 0x08);
					Vec3_s00c289b0* b = BodyPos(a);
					dist2 = sqrtf((b->y - pfVar7->y) * (b->y - pfVar7->y) +
					              ((b->z - pfVar7->z) * (b->z - pfVar7->z) +
					               (b->x - pfVar7->x) * (b->x - pfVar7->x)));
				}
			}

			void* g = F_b3d310();
			float f16 = (*(int*)((char*)g + 0x20) == 0) ? 1.0f : 10.0f;

			if (diff > f16 + dist2 + (fVar17 - fVar1))
			{
				float stp = p1->step;
				Vec3_s00c289b0 tmp;
				pm->RotateTo(&tmp, pfVar7);
				bool bVar2 = (dir3->y * tmp.y + dir3->z * tmp.z) + tmp.x * dir3->x > 0.3f;

				Vec3_s00c289b0 p;
				p.x = pfVar7->x + p1->v.x * stp;
				p.y = pfVar7->y + p1->v.y * stp;
				p.z = pfVar7->z + p1->v.z * stp;

				void* sph = *(void**)((char*)pm + 0x24);
				void* hit = VtCall0(sph, 0x0c);
				float lim = *(float*)((char*)hit + 0x4c);
				if (!(lim > 45.0f))
					lim = 45.0f;

				float fv = pm->HeightAt(&p);
				char* cls = (char*)VtCall0(self, 0x20);

				if (cls == &DAT_018eb45e)
				{
					if (fv > lim + 13.0f)
					{
						bVar3 = true;
						if (F_GetCurrentGameMode() != &DAT_01654c10)
							VtCallV0(p1->obj14, 0xec);
						p1->v.x = tmp.x * -30.0f;
						p1->v.y = tmp.y * -30.0f;
						p1->v.z = tmp.z * -30.0f;
					}
					else if (bVar2)
					{
						if (fv > lim + 10.0f)
						{
							bVar3 = true;
							if (F_GetCurrentGameMode() != &DAT_01654c10)
								VtCallV0(p1->obj14, 0xec);
							p1->v.x = 0.0f;
							p1->v.y = 0.0f;
							p1->v.z = 0.0f;
						}
						else if (lim < fv)
						{
							float sc = 1.0f - (fv - lim) / lim;
							p1->v.x *= sc;
							p1->v.y *= sc;
							p1->v.z *= sc;
						}
					}
				}
				else if (bVar2)
				{
					float sc;
					if (fv > lim + 13.0f)      sc = 0.1f;
					else if (fv > lim + 10.0f) sc = 0.25f;
					else if (fv > lim)         sc = 0.5f;
					else                       sc = -1.0f;
					if (sc >= 0.0f)
					{
						p1->v.x *= sc;
						p1->v.y *= sc;
						p1->v.z *= sc;
					}
				}
			}
		}
	}
	else
	{
		if (param4 != 0)
			return !bVar3;
	}

	if (self->m137 != 0)
	{
		if (p1->v.x != g_168dd78.x || p1->v.y != g_168dd78.y || p1->v.z != g_168dd78.z)
		{
			float stp = p1->step;
			Vec3_s00c289b0 d;
			d.x = pfVar7->x + p1->v.x * stp;
			d.y = pfVar7->y + p1->v.y * stp;
			d.z = pfVar7->z + p1->v.z * stp;

			Vec3_s00c289b0 rt;
			Vec3_s00c289b0* r = pm->Transform(&rt, &d);
			Vec3_s00c289b0 dv;
			dv.x = r->x - pfVar7->x;
			dv.y = r->y - pfVar7->y;
			dv.z = r->z - pfVar7->z;

			Vec3_s00c289b0 nn;
			F_normalized_safe(&nn, &dv);

			float L = sqrtf(p1->v.x * p1->v.x + (p1->v.y * p1->v.y + p1->v.z * p1->v.z));
			p1->v.x = nn.x * L;
			p1->v.y = nn.y * L;
			p1->v.z = nn.z * L;
		}
	}
	return !bVar3;
}

// =================================================================================================
// @ 0x00c290d0
// Weighted-average of a smoothed path (records of 0x3c bytes) minus the creature's surface point.
// NB: the retail function receives a pointer in EAX at entry (custom/LTCG register ABI); it is modelled
// here as a trailing argument.  Recorded as nonmatching.
float* C_s00c289b0::PathAverage(float* out, Path_s00c290d0* path, const float* inEAX)
{
	out[0] = inEAX[0];
	out[1] = inEAX[1];
	out[2] = inEAX[2];
	if (path->begin == path->end)
		return out;

	int* piVar4 = *(int**)(*(int*)((char*)this + 0xb54) + 0x17c);
	float fVar10 = *(float*)(*piVar4 + 0x370) * (float)piVar4[0x1c];
	Vec3_s00c289b0* pfVar5 = BodyPos((char*)this + 0xc0);

	Vec3_s00c289b0* pb = &path->base;
	float d0 = pfVar5->x - pb->x;
	float d1 = pfVar5->y - pb->y;
	float d2 = pfVar5->z - pb->z;
	float fVar11 = sqrtf(d0 * d0 + (d1 * d1 + d2 * d2));
	float fVar13 = 0.0f;
	if (fVar11 <= fVar10)
	{
		if (fVar10 * 0.2f <= fVar11)
		{
			if (fVar11 <= fVar10 * 0.8f)
				fVar13 = 1.0f;
			else
				fVar13 = (fVar10 - fVar11) / (fVar10 - fVar10 * 0.8f);
		}
		else
		{
			fVar13 = fVar11 / (fVar10 * 0.2f);
		}
		fVar13 = ((3.0f - fVar13 * 2.0f) * fVar13) * fVar13;
	}

	PathRec_s00c290d0* pfVar6 = path->begin;
	PathRec_s00c290d0* pfVar7 = path->begin;
	PathRec_s00c290d0* end = path->end;
	float fVar18 = pb->x * fVar13;
	float fVar17 = pb->y * fVar13;
	float fVar12 = pb->z * fVar13;
	if (pfVar6 != end)
	{
		unsigned uVar9 = 0;
		do
		{
			float e0 = pfVar7->p.x - pfVar6->p.x;
			float e1 = pfVar7->p.y - pfVar6->p.y;
			float e2 = pfVar7->p.z - pfVar6->p.z;
			fVar11 = sqrtf(e0 * e0 + (e1 * e1 + e2 * e2)) + fVar11;
			if (fVar11 > fVar10)
				break;
			float w = 0.0f;
			if (fVar11 <= fVar10)
			{
				if (fVar10 * 0.2f <= fVar11)
				{
					if (fVar11 <= fVar10 * 0.8f)
						w = 1.0f;
					else
						w = (fVar10 - fVar11) / (fVar10 - fVar10 * 0.8f);
				}
				else
				{
					w = fVar11 / (fVar10 * 0.2f);
				}
				w = ((3.0f - w * 2.0f) * w) * w;
			}
			fVar13 = w + fVar13;
			fVar18 = pfVar7->p.x * w + fVar18;
			fVar17 = pfVar7->p.y * w + fVar17;
			fVar12 = pfVar7->p.z * w + fVar12;
			pfVar6 = pfVar7;
			pfVar7++;
			uVar9++;
		} while (uVar9 < (unsigned)(path->end - path->begin));
	}

	if (fVar13 > 1e-06f)
	{
		fVar13 = 1.0f / fVar13;
		out[0] = fVar18 * fVar13 - pfVar5->x;
		out[1] = fVar17 * fVar13 - pfVar5->y;
		out[2] = fVar12 * fVar13 - pfVar5->z;
	}
	return out;
}

// =================================================================================================
// @ 0x00c293f0
// Build a surface orientation from obj's position toward dir (falls back to obj->vtbl[0x30] when the
// direction is degenerate).  Returns out.
Vec4_s00c289b0* __cdecl f_00c293f0(Vec4_s00c289b0* out, void* obj, const Vec3_s00c289b0* dir)
{
	if (dir->x * dir->x + dir->y * dir->y + dir->z * dir->z > 0.0f)
	{
		Vec3_s00c289b0* p = (Vec3_s00c289b0*)VtCall0(obj, 0x2c);
		Vec3_s00c289b0 d;
		d.x = dir->x - p->x;
		d.y = dir->y - p->y;
		d.z = dir->z - p->z;
		float len = sqrtf(d.z * d.z + d.y * d.y + d.x * d.x);
		if (len > 1.52587890625e-05f)
		{
			float inv = 1.0f / len;
			Vec3_s00c289b0 n;
			n.x = d.x * inv;
			n.y = d.y * inv;
			n.z = d.z * inv;
			((Pm_s00c289b0*)F_PlanetModel())->BuildSurfaceOrientation(out, p, &n);
			return out;
		}
	}
	Vec4_s00c289b0* src = (Vec4_s00c289b0*)VtCall0(obj, 0x30);
	out->x = src->x;
	out->y = src->y;
	out->z = src->z;
	out->w = src->w;
	return out;
}

// =================================================================================================
// @ 0x00c29530
// Analytic ground-clearance solve (x87): project p1 onto the planet surface, distance of p1 above that
// surface versus p1's own radius, then a quadratic in the slope radius.
float __cdecl f_00c29530(Vec3_s00c289b0* p1, Vec3_s00c289b0* p2, float param3)
{
	Vec3_s00c289b0 tmp;
	Vec3_s00c289b0* surf = ((Pm_s00c289b0*)F_PlanetModel())->TransformClamp(&tmp, p1);
	float fVar2 = sqrtf(p1->x * p1->x + (p1->y * p1->y + p1->z * p1->z)) -
	              sqrtf(surf->x * surf->x + (surf->y * surf->y + surf->z * surf->z));
	if (!(0.0f < fVar2))
		return 0.0f;

	float R = -((Pm_s00c289b0*)F_PlanetModel())->GetRadius();
	float inv = 1.0f / sqrtf((p1->x * p1->x + (p1->y * p1->y + p1->z * p1->z)) + 1e-08f);
	float n0 = p1->x * inv;
	float n1 = inv * p1->y;
	float n2 = inv * p1->z;
	float A = (p2->z * n2 + p2->y * n1) + p2->x * n0;
	float P = fVar2;
	if (0.0f < A)
	{
		P = ((A / R) * A) * 0.5f + fVar2;
		A = 0.0f;
	}
	if (0.0f < param3)
		R = R - param3;
	return (sqrtf(P * R + P * R + A * A) + A) / R;
}

// =================================================================================================
// @ 0x00c296b0
// Sub-object array constructor: 8 chunks of 0x100 bytes (ctor 0xaf4da0) then 8 zero dwords at +0x800.
struct C_s00c296b0
{
	char m_storage[0x800];
	int  m_zero[8];           // +0x800 .. +0x81f
	C_s00c296b0* Init();
};

C_s00c296b0* C_s00c296b0::Init()
{
	Chunk_s00c296b0* p = (Chunk_s00c296b0*)m_storage;
	for (int i = 7; i >= 0; i--)
	{
		p->Ctor();
		p++;
	}
	m_zero[0] = 0;
	m_zero[1] = 0;
	m_zero[2] = 0;
	m_zero[3] = 0;
	m_zero[4] = 0;
	m_zero[5] = 0;
	m_zero[6] = 0;
	m_zero[7] = 0;
	return this;
}

// =================================================================================================
// @ 0x00c297d0
// -dot(a - c, b - d) / |b - d|^2  (0 when |b-d|^2 < 2^-16).
float __cdecl f_00c297d0(const Vec3_s00c289b0* a, const Vec3_s00c289b0* b, const Vec3_s00c289b0* c, const Vec3_s00c289b0* d)
{
	float dz = b->z - d->z;
	float dx = b->x - d->x;
	float dy = b->y - d->y;
	float len2 = (dx * dx + dz * dz) + dy * dy;
	if (len2 < 1.52587890625e-05f)
		return 0.0f;
	// x87, evaluated as ((a.x-c.x)*dx + (a.z-c.z)*dz) + (a.y-c.y)*dy
	return (-1.0f / len2) * (((a->x - c->x) * dx + (a->z - c->z) * dz) + (a->y - c->y) * dy);
}

// =================================================================================================
// @ 0x00c29880
// |(p1 + p2*s) - (p3 + p4*s)|
float __cdecl f_00c29880(const Vec3_s00c289b0* p1, const Vec3_s00c289b0* p2, const Vec3_s00c289b0* p3, const Vec3_s00c289b0* p4, float s)
{
	float fVar1 = (p1->z + p2->z * s) - (p3->z + p4->z * s);
	float fVar2 = (p1->y + p2->y * s) - (p3->y + p4->y * s);
	float fVar3 = (p1->x + p2->x * s) - (p3->x + p4->x * s);
	return sqrtf(fVar3 * fVar3 + (fVar2 * fVar2 + fVar1 * fVar1));
}

// =================================================================================================
// @ 0x00c29940
// Toggle a creature flag and, when set, copy the body scale into the creature's effect transform.
// Retail passes the creature on the stack (cdecl), not in ecx -- that dead argument slot is what the
// bool argument of SetFlagPair is marshalled through.
void __cdecl f_00c29940(C_s00c289b0* self)
{
	bool b = (self->m110 & 0x1000) == 0x1000;
	self->SetFlagPair(b, 0x2775920e, 0x48021ef);
	if (b && self->mF90 != 0)
	{
		Eff_s00c289b0* e = (Eff_s00c289b0*)self->GetEffect(0x48021ef);
		if (e)
		{
			XformMsg_s00c289b0 x;
			x.Ctor();
			e->GetXform(&x);
			x.mScale = BodyFlt((char*)self + 0xc0);
			x.mCount++;
			e->SetXform(&x);
		}
	}
}
