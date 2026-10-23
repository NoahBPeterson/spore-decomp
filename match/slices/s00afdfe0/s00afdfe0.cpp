// Slice s00afdfe0 -- the EA::Swarm surface-decal emission helpers in
// Swarm/SurfaceDecalManager.obj (SporeApp.exe 0x00afdfe0..0x00afef00).
//
// The four emitter members (00afdfe0 / 00afe3a0 / 00afe670 / 00afec00) share one shape: write a
// mode word at +0x24, rebuild the decal vector at +0x50, then append 0x18-byte DecalRec records.
// The other three helpers (00afed00 / 00afedf0 / 00afee20) push records and run the
// quicksort-style init used by that vector.  Member offsets are retail (from the disassembly,
// which is one build off the dev PDB):
//   +0x00/+0x04/+0x08  surface x/y/z        +0x0c surface radius
//   +0x10              last slice value written by 00afec00
//   +0x14..+0x1c       mUp   (surface normal, flag +0x28 clear)
//   +0x20..+0x28       mUpAlt
//   +0x24              mMode
//   +0x28              mUseAlt
//   +0x50              decal vector: {begin, end, capacityEnd} of 0x18-byte records
//
// Every external call is written as a member of a helper class so its __thiscall ABI matches.
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// ---------------------------------------------------------------- constant data
extern const float DAT_013ec4b8;      // 1e-08f guard added to the normal-length sum
extern const float DAT_01567354;      // emitter 1/2 density scale
extern const float DAT_01471064;      // 0.5f
extern const float DAT_01470f1c;      // emitter 3 spacing scale
extern const float DAT_0167aec4, DAT_0167aec8, DAT_0167aecc;   // surface origin x/y/z
extern const float DAT_0167aef4, DAT_0167aef8, DAT_0167aefc;   // default up x/y/z
extern const float DAT_0167af18, DAT_0167af1c, DAT_0167af20;   // alternative up x/y/z
extern char DAT_0167af30[];           // identity Matrix3 source for Matrix3::Assign

// ---------------------------------------------------------------- decal record / vector
struct DecalRec { u8 m_hdr; u8 m_pad0[3]; void* m_ptr; void* m_pad1; float m_x, m_y, m_z; };  // 0x18

// ---------------------------------------------------------------- external helpers
extern "C" void* EAAllocate(u32 size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
extern "C" void* g_PlanetModel();                                                     // 0x00b3d350
extern "C" float* Func_afa510(float* out, const float* uv, float radius);             // 0x00afa510
extern "C" float* SquareToCircle(float* out, float u, float v);                       // 0x00a7c630

// EA::Random::RandomLinearCongruential
struct RandomLCG { u32 __thiscall RandomUint32Uniform(u32 range); };                  // 0x00a68fb0
extern RandomLCG g_sMathRandom;                                                       // 0x01601760

// the array primitives shared by the quad-set and decal vectors
struct ArrayVT
{
	void  __thiscall clear(void* a, void* b);          // 0x00afc0d0
	void* __thiscall pushBack(void* value);            // 0x00afc030
	void  __thiscall reserve(int n);                   // 0x00afbe80
	void  __thiscall constructAt(void* zero);          // 0x00afc150
	void  __thiscall eraseOne(void* key);              // 0x00afc4b0
	void  __thiscall removeByKey(void* key);           // 0x00afb130
	void* __thiscall find(void* out, const void* key); // 0x00afb0d0
	void  __thiscall assignMatrix(const void* src);    // 0x0041cb40
	void  __thiscall eraseRange(void* first, void* last, int n, float x, float y, float z);  // 0x00afc500
};
extern "C" void Func_afc500();   // 0x00afc500  quicksort pass setup
extern "C" void Func_afb230();   // 0x00afb230  partition
extern "C" void Func_afb340();   // 0x00afb340  partition (upper half)
struct Matrix3 { float m[9]; };
struct Sampler { float m_t; float m_u; u32 m_lo; u32 m_hi; };   // 0x10 bytes

// rng wrapper used by the scatter loops: rng.spin() advances and re-seeds.
struct ScatterRng { float m_v; float m_w; u32 m_i; u32 m_j; };

// =====================================================================================
// @ 0x00afdfe0  emitter mode 3: green-theorem radial ring
void __fastcall FUN_00afdfe0(void* selfv, float root)
{
	char* self = (char*)selfv;
	float* f = (float*)self;
	ArrayVT* decals = (ArrayVT*)(self + 0x50);

	*(u32*)(self + 0x24) = 3;
	decals->clear(*(void**)(self + 0x54), *(void**)(self + 0x50));

	if (g_PlanetModel() == 0)
		return;

	char alt = *(char*)(self + 0x28);

	// origin
	float ox, oy, oz;
	if (alt) { ox = DAT_0167aec4; oy = DAT_0167aec8; oz = DAT_0167aecc; }
	else     { ox = f[5];         oy = f[6];         oz = f[7];         }

	// frame row 0 (at +0x14/+0x18/+0x1c)
	float a0, a1, a2;
	if (alt) {
		a0 = DAT_0167af18; a1 = DAT_0167af1c; a2 = DAT_0167af20;
	} else {
		float e0 = f[5], e1 = f[6], e2 = f[7];
		float inv = 1.0f / sqrtf(e0 * e0 + e1 * e1 + e2 * e2 + DAT_013ec4b8);
		a0 = e0 * inv; a1 = e1 * inv; a2 = e2 * inv;
	}

	// unit up (at +0x44/+0x48/+0x4c)
	float u0 = DAT_0167aef4, u1 = DAT_0167aef8, u2 = DAT_0167aefc;

	// surface row used by the sweep at +0x1c/+0x20/+0x24
	float s0 = f[0], s1 = f[1], s2 = f[2];
	float rad = f[3];

	// radial field at +0x2c/+0x30/+0x34
	float r0 = s1 * a2 - s2 * a1;
	float r1 = s2 * a0 - s0 * a2;
	float r2 = s0 * a1 - s1 * a0;

	// second row = up x (surface row) at +0x2c/+0x30/+0x34 (reused slots)
	float b0 = u1 * r2 - u2 * r1;
	float b1 = u2 * r0 - u0 * r2;
	float b2 = u0 * r1 - u1 * r0;

	// direction row at +0x6c/+0x70/+0x74, built again from the local frame
	float d0 = b1 * r2 - b2 * r1;
	float d1 = b2 * r0 - b0 * r2;
	float d2 = b0 * r1 - b1 * r0;

	// sample count: (rad*rad * K) / (K*root*root) * 0.5
	float num = rad * rad;
	num *= DAT_01567354;
	float den = DAT_01567354 * root;
	den *= root;
	float ratio = num / den;
	ratio *= DAT_01471064;
	int count = (int)ratio;
	if (count <= 0)
		return;

	ScatterRng rng;
	rng.m_v = 0.0f;
	rng.m_w = u0;
	rng.m_i = 0;
	rng.m_j = 0;

	u32 seed = g_sMathRandom.RandomUint32Uniform(0x2ee0);
	(void)seed;

	float start0 = ox - a0 * d0;
	float start1 = oy - a1 * d1;
	float start2 = oz - a2 * d2;

	do {
		float k = (float)count;
		float p0 = start0 + r0 * k * DAT_01471064;
		float p1 = start1 + r1 * k * DAT_01471064;
		float p2 = start2 + r2 * k * DAT_01471064;

		float c0 = d0 * k * DAT_01471064;
		float c1 = d1 * k * DAT_01471064;
		float c2 = d2 * k * DAT_01471064;
		(void)c0; (void)c1; (void)c2;

		float uv[2];
		SquareToCircle(uv, 0.0f, 0.0f);

		float q0 = uv[0] * (rad - root);
		float q1 = uv[1] * (rad - root);

		// rotated into the local frame, then offset by the origin
		float w0 = (q0 * b0 + q1 * d0) + ox;
		float w1 = (q0 * b1 + q1 * d1) + oy;
		float w2 = (q0 * b2 + q1 * d2) + oz;

		if (*(char*)(self + 0x28) == 0) {
			float tmp[3];
			Func_afa510(tmp, &p0, rad);
			w0 = tmp[0]; w1 = tmp[1]; w2 = tmp[2];
		}

		DecalRec rec;
		rec.m_hdr = 0;
		rec.m_ptr = 0;
		rec.m_pad1 = 0;
		rec.m_x = w0; rec.m_y = w1; rec.m_z = w2;

		void* end = *(void**)(self + 0x54);
		if (end < *(void**)(self + 0x58)) {
			*(void**)(self + 0x54) = (char*)end + 0x18;
			if (end) *(DecalRec*)end = rec;
		} else {
			decals->constructAt(&rec);
			if (rec.m_ptr) {
				void** vt = *(void***)rec.m_ptr;
				((void(__thiscall*)(void*))vt[1])(rec.m_ptr);
			}
		}

		(void)p0; (void)p1; (void)p2;
		(void)w0; (void)w1; (void)w2;
		(void)rng;
	} while (--count != 0);
}

// =====================================================================================
// @ 0x00afe3a0  emitter mode 4: straight sweep along the emission direction
void __fastcall FUN_00afe3a0(void* selfv, float spacing)
{
	char* self = (char*)selfv;
	float* f = (float*)self;
	ArrayVT* decals = (ArrayVT*)(self + 0x50);

	*(u32*)(self + 0x24) = 4;
	if (g_PlanetModel() == 0)
		return;

	char alt = *(char*)(self + 0x28);

	float ox, oy, oz;
	if (alt) { ox = DAT_0167aec4; oy = DAT_0167aec8; oz = DAT_0167aecc; }
	else     { ox = f[5];         oy = f[6];         oz = f[7];         }

	float a0, a1, a2;
	if (alt) {
		a0 = DAT_0167af18; a1 = DAT_0167af1c; a2 = DAT_0167af20;
	} else {
		float e0 = f[5], e1 = f[6], e2 = f[7];
		float inv = 1.0f / sqrtf(e0 * e0 + e1 * e1 + e2 * e2 + DAT_013ec4b8);
		a0 = e0 * inv; a1 = e1 * inv; a2 = e2 * inv;
	}

	float s0 = f[0], s1 = f[1], s2 = f[2];
	float rad = f[3];

	float r0 = s1 * a2 - s2 * a1;
	float r1 = s2 * a0 - s0 * a2;
	float r2 = s0 * a1 - s1 * a0;

	// step size doubles when the emission direction is the surface normal:
	// (r0,r1,r2)*spacing*2 with the radius-derived direction when alt, else from the row
	float k = rad / spacing;
	int count = (int)k;

	float step0 = r0 * spacing * 2.0f;
	float step1 = r1 * spacing * 2.0f;
	float step2 = r2 * spacing * 2.0f;

	float cnt = (float)count * 0.5f;
	float p0 = ox - step0 * cnt;
	float p1 = oy - step1 * cnt;
	float p2 = oz - step2 * cnt;

	decals->clear(*(void**)(self + 0x54), *(void**)(self + 0x50));

	if (count <= 0)
		return;

	do {
		if (alt) {
			DecalRec rec;
			rec.m_hdr = 0; rec.m_ptr = 0; rec.m_pad1 = 0;
			rec.m_x = p0; rec.m_y = p1; rec.m_z = p2;
			void* end = *(void**)(self + 0x54);
			if (end < *(void**)(self + 0x58)) {
				*(void**)(self + 0x54) = (char*)end + 0x18;
				if (end) *(DecalRec*)end = rec;
			} else {
				decals->constructAt(&rec);
				if (rec.m_ptr) { void** vt = *(void***)rec.m_ptr; ((void(__thiscall*)(void*))vt[1])(rec.m_ptr); }
			}
		} else {
			float tmp[3];
			Func_afa510(tmp, &p0, rad);
			DecalRec rec;
			rec.m_hdr = 0; rec.m_ptr = 0; rec.m_pad1 = 0;
			rec.m_x = tmp[0]; rec.m_y = tmp[1]; rec.m_z = tmp[2];
			void* end = *(void**)(self + 0x54);
			if (end < *(void**)(self + 0x58)) {
				*(void**)(self + 0x54) = (char*)end + 0x18;
				if (end) *(DecalRec*)end = rec;
			} else {
				decals->constructAt(&rec);
				if (rec.m_ptr) { void** vt = *(void***)rec.m_ptr; ((void(__thiscall*)(void*))vt[1])(rec.m_ptr); }
			}
		}
		p0 += step0; p1 += step1; p2 += step2;
	} while (--count != 0);
}

// append a DecalRec (0,0,0,xyz) to the vector at self+0x50.  Shared inline body of the emitters.
static void decalAppend(char* self, float x, float y, float z)
{
	ArrayVT* vec = (ArrayVT*)(self + 0x50);
	DecalRec tmp;
	tmp.m_hdr  = 0;
	tmp.m_ptr  = 0;
	tmp.m_pad1 = 0;
	tmp.m_x = x; tmp.m_y = y; tmp.m_z = z;

	DecalRec* end = *(DecalRec**)(self + 0x54);
	if (end < *(DecalRec**)(self + 0x58)) {
		*(DecalRec**)(self + 0x54) = end + 1;
		if (end) *end = tmp;
	} else {
		vec->constructAt(&tmp);
		if (tmp.m_ptr) {
			void** vt = *(void***)tmp.m_ptr;
			((void(__thiscall*)(void*))vt[1])(tmp.m_ptr);
		}
	}
}

// =====================================================================================
// @ 0x00afe670  emitter mode 5: grid of decals at `spacing`
void __fastcall FUN_00afe670(void* selfv, void* sel, float spacing)
{
	char* self = (char*)selfv;
	float* f = (float*)self;
	(void)sel;

	*(u32*)(self + 0x24) = 5;

	// surface point
	const float* org = (*(char*)(self + 0x28)) ? &DAT_0167aec4 : f + 5;
	float ox = org[0], oy = org[1], oz = org[2];

	// axis: normalized surface normal, or the alternative up vector
	float a0, a1, a2;
	if (*(char*)(self + 0x28)) {
		a0 = DAT_0167af18; a1 = DAT_0167af1c; a2 = DAT_0167af20;
	} else {
		float e0 = f[5], e1 = f[6], e2 = f[7];
		float inv = 1.0f / sqrtf(e0 * e0 + e1 * e1 + e2 * e2 + DAT_013ec4b8);
		a0 = e0 * inv; a1 = e1 * inv; a2 = e2 * inv;
	}

	float s0 = f[0], s1 = f[1], s2 = f[2];
	float rad = f[3];

	if (!(*(char*)(self + 0x28))) {
		// grid axis is the unit surface normal (computed above, kept in a0/a1/a2)
	}
	float n0 = a0, n1 = a1, n2 = a2;   // unit axis for the grid offsets

	// clear the decal vector and drop the surface point at the origin
	ArrayVT* vec = (ArrayVT*)(self + 0x50);
	vec->clear(*(void**)(self + 0x54), *(void**)(self + 0x50));
	decalAppend(self, ox, oy, oz);

	// step = 2 * spacing
	float step = spacing;
	step *= 2.0f;
	step = spacing * 2.0f;

	float p0 = DAT_01470f1c * spacing;
	float rowScale = p0 * p0;
	rowScale += rowScale;              // 2 * (k*spacing)^2
	rowScale = sqrtf(rowScale);
	// rows = (int)(radius / rowScale) + 1
	int rows = (int)(rad / rowScale) + 1;

	// surface-direction basis at this step
	float c0 = s0 * step;
	float c1 = s1 * step;
	float c2 = s2 * step;

	// grid-direction basis at this step: normal x surface, scaled
	float g0 = (n1 * s2 - n2 * s1) * step;
	float g1 = (n2 * s0 - n0 * s2) * step;
	float g2 = (n0 * s1 - n1 * s0) * step;

	int outer = 1;
	for (; outer < rows; ++outer) {
		float kf = (float)outer;
		// start point of this ring
		float q0 = (ox - g0 * kf) + c0 * kf;
		float q1 = (oy - g1 * kf) + c1 * kf;
		float q2 = (oz - g2 * kf) + c2 * kf;

		int inner = 2 * outer;
		float t0 = q0, t1 = q1, t2 = q2;

		// right edge
		for (int i = inner; i > 0; --i) {
			decalAppend(self, t0, t1, t2);
			t0 += g0; t1 += g1; t2 += g2;
		}
		// top edge
		for (int i = inner; i > 0; --i) {
			decalAppend(self, t0, t1, t2);
			t0 -= c0; t1 -= c1; t2 -= c2;
		}
		// left edge
		for (int i = inner; i > 0; --i) {
			decalAppend(self, t0, t1, t2);
			t0 -= g0; t1 -= g1; t2 -= g2;
		}
		// bottom edge
		for (int i = inner; i > 0; --i) {
			decalAppend(self, t0, t1, t2);
			t0 += c0; t1 += c1; t2 += c2;
		}
	}
}

// =====================================================================================
// @ 0x00afec00  emitter mode 6: copy decals from a vector at `first`
void __fastcall FUN_00afec00(void* selfv, void* /*edx*/, int** sel, float scale)
{
	char* self = (char*)selfv;
	ArrayVT* vec = (ArrayVT*)(self + 0x50);

	*(u32*)(self + 0x24) = 6;
	vec->clear(*(void**)(self + 0x50), *(void**)(self + 0x54));
	*(float*)(self + 0x10) = scale;

	int* first = sel[0];
	int* last  = sel[1];
	if (first == last)
		return;

	int count = (int)((char*)last - (char*)first) / 0xc;
	vec->reserve(count);

	if (count > 0) {
		for (int i = 0; i < count; ++i) {
			const float* p = (const float*)((char*)first + i * 0xc);
			decalAppend(self, p[0], p[1], p[2]);
		}
	}
}

// =====================================================================================
// @ 0x00afed00  push one decal from the geometry at ecx+0x38
void __fastcall FUN_00afed00(void* selfv, void* /*edx*/, void* geom)
{
	char* self = (char*)selfv;
	ArrayVT* vec = (ArrayVT*)(self + 0x50);
	void* ref = geom;

	if (ref) {
		void** vt = *(void***)ref;
		((void(__thiscall*)(void*))vt[0xbc / 4])(ref);   // addRef
	}
	vec->pushBack(&ref);
	if (ref) {
		void** vt = *(void***)ref;
		((void(__thiscall*)(void*))vt[0xc0 / 4])(ref);   // release
	}

	// build the 7-dword record: {0, origin.xyz, origin.xyz}
	float rec[7];
	rec[0] = 0.0f;
	rec[1] = DAT_0167aec4; rec[2] = DAT_0167aec8; rec[3] = DAT_0167aecc;
	rec[4] = DAT_0167aec4; rec[5] = DAT_0167aec8; rec[6] = DAT_0167aecc;

	void* at = vec->pushBack(rec);
	void* dst = at;
	for (int i = 0; i < 7; ++i)
		((u32*)dst)[i] = ((u32*)rec)[i];

	*(u32*)((char*)geom + 0x1a4) = *(u32*)(self + 0x174);
}

// =====================================================================================
// @ 0x00afedf0  remove one decal by key
// free call: ecx is left at `self`, args are (self, &key)
extern "C" void Func_afc4b0(void* self, void* key);   // 0x00afc4b0

void __fastcall FUN_00afedf0(void* selfv, void* /*edx*/, void* key)
{
	char* self = (char*)selfv;

	Func_afc4b0(self, &key);
	((ArrayVT*)(self + 0x38))->removeByKey(&key);
	*(u32*)((char*)key + 0x1a4) = 0;
}

// =====================================================================================
// @ 0x00afee20  insertion-sort init over the decal vector
struct SortCtx { float m_a; float m_b; float m_c; u32 m_d; };
typedef void (__cdecl *SortFn)(char*, char*, int, SortCtx);

void FUN_00afee20(char* first, char* last, SortCtx ctx)
{
	if (first == last)
		return;

	int n = (int)(last - first) >> 2;
	int passes = 0;
	for (int t = n; t != 0; t >>= 1)
		++passes;

	((SortFn)Func_afc500)(first, last, passes * 2 - 2, ctx);

	if (n > 0x1c) {
		((SortFn)Func_afb230)(first, first + 0x70, 0, ctx);
		((SortFn)Func_afb340)(first + 0x70, last, 0, ctx);
	} else {
		((SortFn)Func_afb230)(first, last, 0, ctx);
	}
}
