// Slice s01200010 -- 0x01200010, 2027 bytes (cdecl).
//
// Interpolates one animation track between two neighbouring keys A and B (Havok-style hkaAnimation sampling).
//   out   : 16-byte aligned destination vec4 array
//   keys  : { keyA, keyB } pointers; the key time sits `timeOffset` bytes into each key
//   t     : the sample time; the blend factor is u = (t - timeA) / (timeB - timeA)
//   fmt   : key format. fmt->mode == 0: the keys hold raw vec4 floats; otherwise the data is quantised and
//           decoded through the callbacks (+0x18 scalar, +0x20 quaternion) with strides at +4 / +8
//   info  : track info; byte +8 = has rotation, byte +9 = has translation/scale (and +0xc..+0x20 the
//           per-axis bias and scale used to expand the decoded translation)
//
// Rotation: a shortest-path slerp of the two quaternions. dot < 0 flips A; if the dot is above
// cos(kSlerpAngle) the pair is blended linearly (B-A or B+A, then +A) and renormalised with a rsqrtps
// plus two Newton steps; otherwise sin-weighted slerp using acos/fsin.
// Translation: raw mode lerps four floats; quantised mode decodes x/y/z one scalar at a time, lerps,
// scales and biases them and leaves out->w alone.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include <xmmintrin.h>
#include <math.h>

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

extern const float kZero;        // 0x01485378
extern const float kOne;         // 0x01485720
extern const float kHalf;        // 0x01471064
extern const float kMinusOne;    // 0x013eb1bc
extern const float kSlerpAngle;  // 0x0171e318

typedef void (__cdecl *DecodeFn)(float* dst, const void* src);

struct KeyFormat
{
	int mode;               // +0x00  0 = raw floats
	int componentStride;    // +0x04  distance between the scalars of one translation key
	int keyStride;          // +0x08  size of a quantised rotation key
	int pad0[3];            // +0x0c
	DecodeFn readScalar;    // +0x18
	int pad1;               // +0x1c
	DecodeFn readQuat;      // +0x20
};

struct TrackInfo
{
	int pad0[2];            // +0x00
	uint32_t flags;         // +0x08  byte 0: rotation, byte 1: translation
	float biasX, scaleX;    // +0x0c
	float biasY, scaleY;    // +0x14
	float biasZ, scaleZ;    // +0x1c
};

static __forceinline __m128 Splat(float f) { return _mm_set_ps1(f); }
#define SPLAT(v, i) _mm_shuffle_ps((v), (v), (i) * 0x55)

// ((x*x' + y*y') + z*z') + w*w', in every lane
static __forceinline __m128 Dot4(__m128 a, __m128 b)
{
	__m128 xy = _mm_add_ps(_mm_mul_ps(SPLAT(a, 0), SPLAT(b, 0)), _mm_mul_ps(SPLAT(a, 1), SPLAT(b, 1)));
	__m128 xyz = _mm_add_ps(xy, _mm_mul_ps(SPLAT(a, 2), SPLAT(b, 2)));
	return _mm_add_ps(xyz, _mm_mul_ps(SPLAT(a, 3), SPLAT(b, 3)));
}

// v * rsqrt(|v|^2) with two Newton-Raphson steps
static __forceinline __m128 Normalize4(__m128 v)
{
	__m128 sq = _mm_mul_ps(v, v);
	__m128 s = _mm_add_ps(sq, _mm_shuffle_ps(sq, sq, 0x0e));
	s = _mm_add_ps(s, _mm_shuffle_ps(s, s, 0x01));
	s = _mm_shuffle_ps(s, s, 0x00);
	const __m128 one = Splat(kOne);
	const __m128 half = Splat(kHalf);
	__m128 r = _mm_rsqrt_ps(s);
	r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(s, _mm_mul_ps(r, r))), _mm_mul_ps(r, half)));
	r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(s, _mm_mul_ps(r, r))), _mm_mul_ps(r, half)));
	return _mm_mul_ps(v, r);
}

static __forceinline __m128 Slerp(__m128 q0, __m128 q1, __m128 tv)
{
	__m128 dot = Dot4(q0, q1);
	if (kZero > _mm_cvtss_f32(dot))
	{
		q0 = _mm_mul_ps(q0, Splat(kMinusOne));
		dot = _mm_sub_ps(_mm_setzero_ps(), dot);
	}
	const float cosLimit = (float)cos((double)kSlerpAngle);
	if (_mm_cvtss_f32(dot) > cosLimit)
	{
		__m128 d;
		if (_mm_cvtss_f32(Dot4(q0, q1)) > kZero)
			d = _mm_mul_ps(_mm_sub_ps(q1, q0), tv);
		else
			d = _mm_mul_ps(_mm_add_ps(q1, q0), _mm_sub_ps(_mm_setzero_ps(), tv));
		return Normalize4(_mm_add_ps(d, q0));
	}
	const float angle = (float)acos((double)_mm_cvtss_f32(dot));
	const __m128 av = Splat(angle);
	const __m128 w0 = _mm_div_ps(Splat((float)sin((double)_mm_cvtss_f32(_mm_mul_ps(_mm_sub_ps(Splat(kOne), tv), av)))),
	                             Splat((float)sin((double)angle)));
	const __m128 w1 = _mm_div_ps(Splat((float)sin((double)_mm_cvtss_f32(_mm_mul_ps(tv, av)))),
	                             Splat((float)sin((double)angle)));
	return _mm_add_ps(_mm_mul_ps(q0, w0), _mm_mul_ps(q1, w1));
}

// @ 0x01200010
void SampleTrackKeys(float* out, const char* const* keys, int timeOffset, float t, const KeyFormat* fmt,
                     const TrackInfo* info)
{
	const char* a = keys[0];
	const char* b = keys[1];
	const uint32_t flags = info->flags;
	const float timeA = *(const float*)(a + timeOffset);
	const float u = (t - timeA) / (*(const float*)(b + timeOffset) - timeA);
	const __m128 uv = Splat(u);

	if (fmt->mode == 0)
	{
		if ((uint8_t)flags)
		{
			_mm_store_ps(out, Slerp(_mm_load_ps((const float*)a), _mm_load_ps((const float*)b), uv));
			a += 16;
			b += 16;
			out += 4;
		}
		if ((uint8_t)(flags >> 8))
		{
			const __m128 va = _mm_load_ps((const float*)a);
			const __m128 vb = _mm_load_ps((const float*)b);
			_mm_store_ps(out, _mm_add_ps(va, _mm_mul_ps(_mm_sub_ps(vb, va), uv)));
		}
		return;
	}

	if ((uint8_t)flags)
	{
		__declspec(align(16)) float q0[4];
		__declspec(align(16)) float q1[4];
		fmt->readQuat(q0, a);
		fmt->readQuat(q1, b);
		_mm_store_ps(out, Slerp(_mm_load_ps(q0), _mm_load_ps(q1), uv));
		a += fmt->keyStride;
		b += fmt->keyStride;
		out += 4;
	}
	if ((uint8_t)(flags >> 8))
	{
		float v;
		fmt->readScalar(&v, a);
		const float ax = v;
		fmt->readScalar(&v, a + fmt->componentStride);
		const float ay = v;
		fmt->readScalar(&v, a + fmt->componentStride + fmt->componentStride);
		const float az = v;
		fmt->readScalar(&v, b);
		const float bx = v;
		fmt->readScalar(&v, b + fmt->componentStride);
		const float by = v;
		fmt->readScalar(&v, b + fmt->componentStride + fmt->componentStride);
		const float bz = v;
		out[0] = info->scaleX * (ax + (bx - ax) * u) + info->biasX;
		out[1] = info->scaleY * (ay + (by - ay) * u) + info->biasY;
		out[2] = info->scaleZ * (az + (bz - az) * u) + info->biasZ;
	}
}

// ---------------------------------------------------------------------------------------------
// Small fixup helpers of the animation-track serializer (0x01200800 .. 0x01201070).
// Records dumped to disk keep object ids; the Init* entry points turn them back into pointers
// through the rw::core arena, and the rebase helpers fix up the self-relative members.

struct Arena
{
	int   ObjectToId(void* obj);     // 0x011e3c30 (thiscall, ret 4)
	void* IdToObject(int id);        // 0x011e2300 (thiscall, ret 4)
};

// Context carrying the arena pointer directly at +0x78 (and a relocation base at +0x7c).
struct ArenaCtx
{
	unsigned char pad00[0x78];
	Arena* mpArena;                  // +0x78
	int*   mpBase;                   // +0x7c
};

// Context carrying an arena-owning object at +0x1c; that object holds the arena at its +0x78.
struct ArenaHost
{
	unsigned char pad00[0x78];
	Arena* mpArena;                  // +0x78
};
struct WorldCtx
{
	unsigned char pad00[0x1c];
	ArenaHost* mpHost;               // +0x1c
};

// Contexts that only provide the relocation base.
struct Base20Ctx
{
	unsigned char pad00[0x20];
	int* mpBase;                     // +0x20
};

// Keyed object of the global registry.
struct RegObj
{
	int mKey;                        // +0x00
};
extern int    g_regCount;            // 0x015d09e0
extern RegObj* g_regList[];          // 0x015d09e8

// Three int members holding self-relative values.
struct Rel3
{
	int mV0;                         // +0x00
	int mV1;                         // +0x04
	int mV2;                         // +0x08
};

// Fixup record with four serialized object slots; mpFn is the sample/callback handler.
struct Fixup4
{
	void* mpLink;                    // +0x00
	void* mpFn;                      // +0x04
	void* mpData8;                   // +0x08
	void* mpDataC;                   // +0x0c
	void* mpData10;                  // +0x10
};

// Fixup record with an inline table of 8-byte id/aux entries.
struct FixupTable
{
	void* mpLink;                    // +0x00
	void* mpFn;                      // +0x04
	int*  mpEntries;                 // +0x08 (self-relative)
	void* mpDataC;                   // +0x0c
	void* mpData10;                  // +0x10
	unsigned int mCount;             // +0x14
};

int FUN_012010e0(int* a, int* b, int c, int* d);        // 0x012010e0
int FixupCallback(int arg, Fixup4* rec);                 // 0x01200f80
int SampleTrackPairs(FixupTable* rec, ArenaCtx* ctx);    // 0x01200ab0

// @ 0x01200800
RegObj* FindObjectByKey(int key)
{
	for (int i = 0; i < g_regCount; i++)
		if (g_regList[i]->mKey == key)
			return g_regList[i];
	return 0;
}

// @ 0x01200830
int SetFloatValue(float* dst, float v)
{
	*dst = v;
	return 1;
}

// @ 0x01200850
void CopyDword(unsigned int* dst, const unsigned int* src)
{
	*dst = *src;
}

struct __declspec(align(16)) AlignedVec4
{
	float x, y, z, w;
};

// @ 0x01200860
int CopyVec4(__m128* dst, const __m128* src)
{
	*dst = *src;
	return 1;
}

// @ 0x01200880
void CopyVec4Void(__m128* dst, const __m128* src)
{
	*dst = *src;
}

// @ 0x01200890
void Unbase3(Rel3* p, Base20Ctx* ctx)
{
	int d = (int)p - (int)ctx->mpBase;
	p->mV2 -= d;
	p->mV0 -= d;
	p->mV1 -= d;
}

// @ 0x012008b0
void Rebase3(Rel3* p, void* from)
{
	int d = (int)p - (int)from;
	p->mV2 += d;
	p->mV0 += d;
	p->mV1 += d;
}

// @ 0x012008d0
int Rebase3FromBase(Rel3* p, ArenaCtx* ctx)
{
	int d = (int)p - (int)ctx->mpBase;
	p->mV2 += d;
	p->mV0 += d;
	p->mV1 += d;
	return 1;
}

// @ 0x01200960
WorldCtx* FixupToIds(Fixup4* rec, WorldCtx* ctx)
{
	rec->mpLink = (void*)ctx->mpHost->mpArena->ObjectToId(rec->mpLink);
	rec->mpData8 = (void*)ctx->mpHost->mpArena->ObjectToId(rec->mpData8);
	rec->mpDataC = (void*)ctx->mpHost->mpArena->ObjectToId(rec->mpDataC);
	rec->mpData10 = (void*)ctx->mpHost->mpArena->ObjectToId(rec->mpData10);
	return ctx;
}

// @ 0x012009c0
void FixupToPointers(Fixup4* rec, int unknown, ArenaCtx* ctx)
{
	rec->mpLink = ctx->mpArena->IdToObject((int)rec->mpLink);
	rec->mpData8 = ctx->mpArena->IdToObject((int)rec->mpData8);
	rec->mpDataC = ctx->mpArena->IdToObject((int)rec->mpDataC);
	rec->mpData10 = ctx->mpArena->IdToObject((int)rec->mpData10);
}

// @ 0x01200a10
int InitFixup4(Fixup4* rec, ArenaCtx* ctx)
{
	rec->mpFn = (void*)FixupCallback;
	rec->mpLink = ctx->mpArena->IdToObject((int)rec->mpLink);
	rec->mpData8 = ctx->mpArena->IdToObject((int)rec->mpData8);
	rec->mpDataC = ctx->mpArena->IdToObject((int)rec->mpDataC);
	rec->mpData10 = ctx->mpArena->IdToObject((int)rec->mpData10);
	return 1;
}

// @ 0x01200ee0
int InitFixupTable(FixupTable* rec, ArenaCtx* ctx)
{
	rec->mpFn = (void*)SampleTrackPairs;
	rec->mpLink = ctx->mpArena->IdToObject((int)rec->mpLink);
	rec->mpData10 = ctx->mpArena->IdToObject((int)rec->mpData10);
	rec->mpEntries = (int*)((char*)rec->mpEntries + ((char*)rec - (char*)ctx->mpBase));
	int** entries = (int**)rec->mpEntries;
	for (unsigned int i = 0; i < rec->mCount; i++)
		entries[i * 2] = (int*)ctx->mpArena->IdToObject((int)entries[i * 2]);
	rec->mpDataC = ctx->mpArena->IdToObject((int)rec->mpDataC);
	return 1;
}

// @ 0x01200f80
int FixupCallback(int arg, Fixup4* rec)
{
	if (!arg)
		arg = (int)rec->mpData8;
	return FUN_012010e0((int*)rec->mpData10, (int*)rec->mpDataC, (int)rec->mpLink, (int*)arg);
}

// @ 0x01200fb0
void RebaseOneReversed(int* p, Base20Ctx* ctx)
{
	if (p != ctx->mpBase)
	{
		*p = *p - (int)p;
		*p = (int)ctx->mpBase + *p;
	}
}

// @ 0x01200fd0
void RebaseDeltaFrom(int* p, int* from)
{
	if (p != from)
		*p += (int)p - (int)from;
}

// @ 0x01200ff0
int RebaseDeltaFromBase(int* p, ArenaCtx* ctx)
{
	if (p != ctx->mpBase)
		*p += (int)p - (int)ctx->mpBase;
	return 1;
}

// @ 0x01201050
void RebaseToBase20(int* p, Base20Ctx* ctx)
{
	int d = (int)ctx->mpBase - (int)p;
	*p = *p + d;
}

// @ 0x01201070
void RebaseTranslated(int* p, int* from)
{
	int d = (int)p - (int)from;
	*p += d;
}

// @ 0x01200940
// Fixup wrapper destructor: releases the wrapped object through its secondary operator table and
// then runs the recorded callback slot.
struct RelVt
{
	void* s00;                       // +0x00
	void* s04;                       // +0x04
	void* s08;                       // +0x08
	void (__thiscall* s0c)(void*);   // +0x0c
};
struct RelObj
{
	void*         pad00;             // +0x00
	RelVt*        mpVt;              // +0x04
	unsigned char pad08[0x18 - 8];
	int           mRefs;             // +0x18
};
struct FixupHolder
{
	RelObj* mpObj;                                   // +0x00
	void (__cdecl* mpFn)(int, FixupHolder*);         // +0x04
	void Finish();
};

void FixupHolder::Finish()
{
	RelObj* obj = mpObj;
	int refs = obj->mRefs;
	if (!refs)
		obj->mpVt->s0c(obj);
	mpFn(0, this);
}
