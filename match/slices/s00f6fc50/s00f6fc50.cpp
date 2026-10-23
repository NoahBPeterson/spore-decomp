// Spore (SporeApp.exe) -- slice s00f6fc50: SP::cTerrainMap cube-face sampling helpers.
//
//   0x00F6FC50  sample the cube face under a direction and return the 32-bit terrain
//               height (masked by the low-res 16-bit map)
//   0x00F6FE50  boolean variant of the above
//   0x00F70080  interpolated 16-bit height (slope blend)
//   0x00F70250  boolean 16-bit height test
//   0x00F70440  total of two sub-object counts (__fastcall, no stack args)
//   0x00F70470  bilinear cube-image sample thresholded through FUN_00fb9e70
//   0x00F70660  effect-presence test (terrain height + SP::EffectsManager)
//   0x00F70870  count of sub-object + effect (__fastcall, no stack args)
//
// Names for the callees come from symbols/pdb_names.json
//  0x00f88650 -> SP::cTerrainMap<unsigned int>::GetFloat
//  0x00f8d620 -> SP::cTerrainMap<unsigned short>::GetFloat
//  0x00f8de70 -> SP::cCubeImage::SampleBilinear  (Claude-coined)
//  0x00fb9e70 -> FUN_00fb9e70 (glyph-atlas texel sample, returns double in st(0))
//  0x0067ddd0 -> SP::EffectsManager
//
// Self-contained TU: every type is modelled here so the compiler emits the same member
// offsets the original used.  `this+0xc` is the inner terrain object; the two sub-maps
// live at inner+8 (16-bit) and inner+0xc (32-bit); the cube image at inner+0x10.
#include "types.h"

#define NULL 0

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

// ---------------------------------------------------------------------------
// external callees (defined elsewhere in the binary)
// ---------------------------------------------------------------------------

// 0x00f88650  SP::cTerrainMap<unsigned int>::GetFloat(const float* uv)
struct cTerrainMapU32
{
	float GetFloat(const float* uv);
};

// 0x00f8d620  SP::cTerrainMap<unsigned short>::GetFloat(const float* uv)
struct cTerrainMapU16
{
	float GetFloat(const float* uv);
};

// 0x00f8de70  SP::cCubeImage::SampleBilinear(const float* uv)
struct cCubeImage
{
	float SampleBilinear(const float* uv);
};

// 0x00fb9e70  glyph-atlas texel sample; thiscall, returns double in st(0)
struct AtlasSampler
{
	double Sample(float v);
};

// ---------------------------------------------------------------------------
// SP::EffectsManager (0x0067ddd0) and the effect handle it vends
// ---------------------------------------------------------------------------
extern void* EffectsManager();   // 0x0067ddd0

// effect handle: vtable slots 0 (vt0), 4 (vt4), 0x10 (vt10), 0x20 (vt20)
struct IEffect
{
	virtual void  vt00();
	virtual void  vt04();
	virtual void  vt08();
	virtual void  vt0c();
	virtual int   vt10();
	virtual void  vt14();
	virtual void  vt18();
	virtual void  vt1c();
	virtual float vt20(void* p);
};

// the manager vtable slot used is 0x8c (35th slot): LookupByKey(int,int) -> IEffect*
typedef IEffect* (__thiscall *PFN_MgrLookup)(void* self, int key, int b);

// ---------------------------------------------------------------------------
// inner terrain object (this+0xc) and the outer owner
// ---------------------------------------------------------------------------
struct CubeInner
{
	char   _pad00[8];
	void*  mp08;                     // +0x08  cTerrainMap<unsigned short>*
	void*  mp0c;                     // +0x0c  cTerrainMap<unsigned int>*
	void*  mp10;                     // +0x10  cCubeImage*
	void*  mp14;                     // +0x14  other sub-object
	char   _pad18[0x38 - 0x18];
	float  m38;                      // +0x38
	float  m3c;                      // +0x3c
	float  m40;                      // +0x40
	float  m44;                      // +0x44
	float  m48;                      // +0x48
};

struct CubeOwner
{
	char        _pad00[0xc];
	CubeInner*  mpInner;             // +0x0c
	void*       mp10;                // +0x10

	float Sample32(const float* p);          // 0x00F6FC50
	float Test32(const float* p);            // 0x00F6FE50
	float Slope16(const float* p);           // 0x00F70080
	float Test16(const float* p);            // 0x00F70250
	int   CountSubs();                       // 0x00F70440
	float SampleImage(const float* p);       // 0x00F70470
	float TestEffect(const float* p);        // 0x00F70660
	int   CountSubsEffect();                 // 0x00F70870
};

// project a direction onto its dominant cube face; returns (u, v, face)
// (shared inline prefix of the six sampling functions)
struct CubeUV { float u; float v; int face; };

static __forceinline void ProjectToFace(const float* p, CubeUV* out)
{
	float vx = p[0];
	float vy = p[1];
	float vz = p[2];
	float ax = (float)fabs(vx);
	float ay = (float)fabs(vy);
	float az = (float)fabs(vz);

	if (az < ax || az < ay)
	{
		if (ay < ax)
		{
			out->u = (vy / vx + 1.0f) * 0.5f;
			out->v = (vz / ax + 1.0f) * 0.5f;
			out->face = 2;
			if (vx < 0.0f)
				out->face = 3;
		}
		else
		{
			out->u = (vz / vy + 1.0f) * 0.5f;
			out->v = (vx / ay + 1.0f) * 0.5f;
			out->face = 4;
			if (vy < 0.0f)
				out->face = 5;
		}
	}
	else
	{
		out->u = (vx / vz + 1.0f) * 0.5f;
		out->v = (vy / az + 1.0f) * 0.5f;
		out->face = 0;
		if (vz < 0.0f)
			out->face = 1;
	}
}

// ---------------------------------------------------------------------------
// 0x00F6FC50
// ---------------------------------------------------------------------------
// @ 0x00f6fc50
float CubeOwner::Sample32(const float* p)
{
	CubeInner* in = mpInner;
	if (in->mp08 == NULL || in->mp0c == NULL)
		return 0.0f;

	float f1 = in->m38;
	float f2 = in->m3c;
	float f3 = in->m38;
	float f4 = in->m48;

	CubeUV uv;
	ProjectToFace(p, &uv);

	float r1 = ((cTerrainMapU32*)in->mp0c)->GetFloat(&uv.u);
	if (f4 <= r1 * f1)
	{
		float r2 = ((cTerrainMapU16*)in->mp08)->GetFloat(&uv.u);
		if (f2 * f3 < r2 * f1)
			return r1;
	}
	return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00F6FE50
// ---------------------------------------------------------------------------
// @ 0x00f6fe50
float CubeOwner::Test32(const float* p)
{
	CubeInner* in = mpInner;
	if (in->mp08 == NULL || in->mp0c == NULL)
		return 0.0f;

	float f1 = in->m38;
	float f2 = in->m3c;
	float f3 = in->m38;
	float f4 = in->m48;

	CubeUV uv;
	ProjectToFace(p, &uv);

	float r1 = ((cTerrainMapU32*)in->mp0c)->GetFloat(&uv.u);
	if (f4 <= r1 * f1)
	{
		float r2 = ((cTerrainMapU16*)in->mp08)->GetFloat(&uv.u);
		if (f2 * f3 < r2 * f1)
			return 1.0f;
		return 0.0f;
	}
	return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00F70080
// ---------------------------------------------------------------------------
// @ 0x00f70080
float CubeOwner::Slope16(const float* p)
{
	CubeInner* in = mpInner;
	if (in->mp08 == NULL)
		return 0.0f;

	float f1 = in->m38;
	float f2 = in->m3c;
	float f3 = in->m38;

	CubeUV uv;
	ProjectToFace(p, &uv);

	float r = ((cTerrainMapU16*)in->mp08)->GetFloat(&uv.u);
	float hi = f2 * f3;
	if (hi <= r * f1)
		return 0.0f;
	return (hi - r * f1) / (hi + f1);
}

// ---------------------------------------------------------------------------
// 0x00F70250
// ---------------------------------------------------------------------------
// @ 0x00f70250
float CubeOwner::Test16(const float* p)
{
	CubeInner* in = mpInner;
	if (in->mp08 == NULL)
		return 0.0f;

	float f1 = in->m38;
	float f2 = in->m3c;
	float f3 = in->m38;

	CubeUV uv;
	ProjectToFace(p, &uv);

	float r = ((cTerrainMapU16*)in->mp08)->GetFloat(&uv.u);
	if (f2 * f3 > r * f1)
		return 1.0f;
	return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00F70440
// ---------------------------------------------------------------------------
// @ 0x00f70440
int CubeOwner::CountSubs()
{
	CubeInner* in = mpInner;
	void* p1 = in->mp08;
	void* p2 = in->mp14;
	int a;
	if (p1)
		a = *(int*)((char*)p1 + 0xc);
	else
		a = 0;
	int b;
	if (p2)
		b = *(int*)((char*)p2 + 0xc);
	else
		b = 0;
	return a + b;
}

// ---------------------------------------------------------------------------
// 0x00F70470
// ---------------------------------------------------------------------------
// @ 0x00f70470
float CubeOwner::SampleImage(const float* p)
{
	CubeInner* in = mpInner;
	if (in->mp10 == NULL)
		return 0.0f;

	CubeUV uv;
	ProjectToFace(p, &uv);

	float r = ((cCubeImage*)in->mp10)->SampleBilinear(&uv.u);
	double v = ((AtlasSampler*)mp10)->Sample(r);
	if (v < 0.05)
		return 0.0f;
	return 1.0f;
}
// ---------------------------------------------------------------------------
// 0x00F70660
// ---------------------------------------------------------------------------
// @ 0x00f70660
float CubeOwner::TestEffect(const float* p)
{
	CubeUV uv;
	ProjectToFace(p, &uv);

	CubeInner* in = mpInner;
	if (in->mp08 != NULL)
	{
		float thr = (in->m44 + in->m3c) * in->m38;
		float r = ((cTerrainMapU16*)in->mp08)->GetFloat(&uv.u);
		if (r * in->m38 <= thr)
			return 0.0f;
	}

	void* mgr = EffectsManager();
	IEffect* obj = ((PFN_MgrLookup)(*(void***)mgr)[0x8c / 4])(mgr, 0x107ae878, 0);
	if (obj != NULL)
	{
		obj->vt00();
		if (obj->vt20((void*)p) != 0.0f)
		{
			obj->vt04();
			return 1.0f;
		}
		obj->vt04();
	}
	return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00F70870
// ---------------------------------------------------------------------------
// @ 0x00f70870
int CubeOwner::CountSubsEffect()
{
	CubeInner* in = mpInner;
	void* a = in->mp08;

	void* mgr = EffectsManager();
	IEffect* obj = ((PFN_MgrLookup)(*(void***)mgr)[0x8c / 4])(mgr, 0x107ae878, 0);
	if (obj != NULL)
		obj->vt00();

	int x;
	if (a)
		x = *(int*)((char*)a + 0xc);
	else
		x = 0;
	int y;
	if (obj)
		y = obj->vt10();
	else
		y = 0;
	x = x + y;
	if (obj)
		obj->vt04();
	return x;
}
