// Spore (SporeApp.exe) -- slice s0114f870: terrain-lighting biquad-filter / trig-scatter family.
//
//   0x0114F870  fixed-point (16.16) linear interpolation of a terrain column into a
//               biquad state machine (256 samples)
//   0x0114F9D0  span resampler: floor()ed start/end indices feeding an eastl vector insert
//   0x0114FAB0  per-frame driver: ring buffer fill + filter + Iir2Filter + terrain blend
//   0x0114FE20  scaled copy of one terrain row into six filter taps
//   0x0114FF00  biquad low-pass coefficient setup (tan)
//   0x0114FFD0  biquad coefficient setup with resonance (tan + sqrt)
//   0x01150100  octant lookup of (cos,sin) weights
//   0x011501F0  octant lookup with level split + min correction
//
// Self-contained TU: the owner is modelled with the member offsets the original used.
#include "types.h"
#include <math.h>

#define NULL 0

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

// ---------------------------------------------------------------------------
// external callees (defined elsewhere in the binary)
// ---------------------------------------------------------------------------

// 0x01134260  dst[i] = src[i] * scale   (scaled copy; SSE when 16-byte aligned)
extern "C" void __cdecl FUN_01134260(void* dst, void* src, float scale, unsigned int n);

// 0x01160300  terrain blend helper (dst, src, a, b, n)
extern "C" void __cdecl FUN_01160300(void* dst, int src, float a, float b, unsigned int n);

// 0x011600e0  terrain blend helper (dst, src, a, b, n)
extern "C" void __cdecl FUN_011600e0(void* dst, int src, float a, float b, unsigned int n);

// 0x011e0906  ?iat_floor@@YANN@Z
extern "C" double __cdecl iat_floor(double);

// 0x011e0744  eastl::vector<bool,...>::DoInsertValue(vector, position, value)
extern "C" void __cdecl eastl_insert(void* vec, void* pos, int value);

// 0x0114f100  Iir2Filter; lives in a sub-object at owner+0x30
struct IirSlot
{
	void Iir2Filter(void* a, int b, void* c);
};

// ---------------------------------------------------------------------------
// owner
// ---------------------------------------------------------------------------
struct cLightFilter
{
	char           _pad00[0x28];
	float          m28;            // +0x28  source scale
	char           _pad2c[0x30 - 0x2c];
	char           m30[0x10];      // +0x30  Iir2Filter state
	char           m40[0x1c];      // +0x40  Iir2Filter arg
	float          m5c;            // +0x5c
	char           _pad60[0x90 - 0x60];
	int            m90;            // +0x90  ring buffer base
	int            m94;            // +0x94  scratch buffer base
	char           _pad98[0xa0 - 0x98];
	unsigned int   ma0;            // +0xa0  column count
	char           _pada4[0xa8 - 0xa4];
	unsigned int   ma8;            // +0xa8  ring size
	char           _padac[0xb0 - 0xac];
	unsigned int   mb0;            // +0xb0  ring write index
	char           _padb4[0xb8 - 0xb4];
	unsigned int   mb8;            // +0xb8  countdown
	char           _padbc[0xc0 - 0xbc];
	unsigned short mc0;            // +0xc0  offset to sub-object A
	unsigned short mc2;            // +0xc2  offset to sub-object B

	void F870(int param_1, float* param_2, float* param_3, float param_4, float* param_5); // 0x0114f870
	void F9D0(int a, float b, float c, void* vec, void* vec2);                            // 0x0114f9d0
	void FAB0(int param_2, int param_3);                                                   // 0x0114fab0
	void FE20(int param_2, int param_3);                                                   // 0x0114fe20
	void F900(void* param_1, float param_2);                                               // 0x0114ff00
	void FFD0(float* param_1, float param_2, float param_3);                               // 0x0114ffd0
	void F100(float param_1, float param_2, float* param_3);                               // 0x01150100
	void F1F0(float param_1, float param_2, float param_3, float param_4, float* param_5);  // 0x011501f0
};

// ---------------------------------------------------------------------------
// 0x0114F870
// ---------------------------------------------------------------------------
// @ 0x0114f870
void cLightFilter::F870(int param_1, float* param_2, float* param_3, float param_4, float* param_5)
{
	unsigned int uVar1 = (unsigned int)(long long)((1.0f - param_4) * 65536.0f);
	unsigned int local = (unsigned int)(long long)(*param_3 * 65536.0f);
	int n = 0x100;
	do
	{
		*param_3 += param_4;
		float f3 = (float)(local & 0xffff) * 1.5258e-05f;
		float f4 = (1.0f - f3) * *(float*)(param_1 + (local >> 16) * 4) + *(float*)(param_1 + 4 + (local >> 16) * 4) * f3;
		float fr = ((((param_5[1] * param_5[8] + param_5[0] * param_5[7]) + f4 * param_5[6]) + 1e-18f) - param_5[4] * param_5[2]) - param_5[3] * param_5[5];
		param_5[1] = param_5[0];
		param_5[3] = param_5[2];
		param_5[0] = f4;
		param_5[2] = fr;
		n--;
		*param_2 = fr;
		param_2++;
		local += uVar1;
	} while (n != 0);
}

// ---------------------------------------------------------------------------
// 0x0114F9D0
// ---------------------------------------------------------------------------
// @ 0x0114f9d0
void cLightFilter::F9D0(int a, float b, float c, void* vec, void* vec2)
{
	float t = (float)a - b;
	int i1 = (int)floor((double)t);
	int i2 = (int)floor((double)(t - c * 256.0f + 256.0f)) + 1;
	if (i1 < 0)
	{
		if (i2 <= 0)
			goto L3;
		eastl_insert(vec, (char*)m90 + (ma8 + i1) * 4, -i1 * 4);
		eastl_insert((char*)vec - i1 * 4, (void*)m90, i2 * 4 + 4);
		return;
	}
	if (i2 > 0)
		goto L4;
L3:
	i1 += ma8;
	i2 += ma8;
L4:
	eastl_insert(vec, (char*)m90 + i1 * 4, (i2 - i1) * 4 + 4);
	(void)vec2;
}

// ---------------------------------------------------------------------------
// 0x0114FAB0
// ---------------------------------------------------------------------------
// @ 0x0114fab0
void cLightFilter::FAB0(int param_2, int param_3)
{
	int iVar2 = m94;
	float f28 = m28;
	int iVar4 = (int)mc0 + (int)this;
	while (mb0 >= ma8)
		mb0 = mb0 - ma8;
	int local_44[16];
	int local_4c = iVar2;
	local_44[0] = (int)mb0 - 0x100;
	FUN_01134260((void*)((int)m90 + (int)mb0 * 4), *(void**)(param_3 + 4), f28, 0x100);
	mb0 = mb0 + 0x100;
	F9D0(local_44[0], *(float*)(iVar4 + 0x64), *(float*)(iVar4 + 0x68), (void*)(iVar2 + 0x800), local_44);
	float l48 = *(float*)(iVar4 + 0x64);
	double dVar6 = iat_floor((double)l48);
	float local_50 = l48 - (float)dVar6;
	F870(iVar2 + 0x800, (float*)iVar2, &local_50, *(float*)(iVar4 + 0x68), (float*)iVar4);
	dVar6 = iat_floor((double)*(float*)(iVar4 + 0x64));
	*(float*)(iVar4 + 0x64) = (float)dVar6 + local_50;
	((IirSlot*)((char*)this + 0x30))->Iir2Filter((void*)(iVar2 + 0x400), iVar2, (char*)this + 0x40);

	float* pf = (float*)(iVar4 + 0x4c);
	int n = 0;
	do
	{
		FUN_01160300((void*)(*(int*)(param_2 + 4) + (unsigned short)*(unsigned short*)(param_2 + 0xe) * n * 4),
			local_4c, *pf, pf[-5], 0x100);
		n++;
		*pf = pf[-5] * 256.0f + *pf;
		pf++;
	} while (n < 5);

	mb8 = mb8 - 1;
	if (mb8 == 0)
	{
		*(float*)(iVar4 + 0x38) = 0.0f;
		*(float*)(iVar4 + 0x3c) = 0.0f;
		*(float*)(iVar4 + 0x40) = 0.0f;
		*(float*)(iVar4 + 0x44) = 0.0f;
		*(float*)(iVar4 + 0x48) = 0.0f;
	}

	int cnt = 0;
	if (ma0 != 0)
	{
		float* p5 = (float*)((int)mc2 + (int)this + 0x4c);
		do
		{
			if (256.0f <= *p5)
			{
				*p5 = *p5 - 256.0f;
			}
			else
			{
				*p5 = 0.0f;
				p5[-1] = 0.0f;
			}
			F9D0(local_44[0], p5[-2], p5[-1], (void*)(local_4c + 0x800), local_44);
			float l50 = p5[-2];
			double dd = iat_floor((double)l50);
			l50 = l50 - (float)dd;
			F870(local_4c + 0x800, (float*)local_4c, &l50, p5[-1], p5 - 0x13);
			dd = iat_floor((double)p5[-2]);
			p5[-2] = (float)dd + l50;
			FUN_011600e0((void*)(*(int*)(param_2 + 4) + (unsigned short)*(unsigned short*)(p5 - 4) * (unsigned short)*(unsigned short*)(param_2 + 0xe) * 4),
				local_4c + 0x400, p5[-6], p5[-8], 0x100);
			p5[-6] = p5[-8] * 256.0f + p5[-6];
			p5[-8] = 0.0f;
			FUN_011600e0((void*)(*(int*)(param_2 + 4) + (unsigned short)*(unsigned short*)((int)p5 - 0xe) * (unsigned short)*(unsigned short*)(param_2 + 0xe) * 4),
				local_4c + 0x400, p5[-5], p5[-7], 0x100);
			p5[-5] = p5[-7] * 256.0f + p5[-5];
			p5[-7] = 0.0f;
			cnt++;
			p5 = p5 + 0x14;
		} while (cnt < (int)ma0);
	}

	if (256.0f <= m5c)
		m5c = m5c - 256.0f;
}

// ---------------------------------------------------------------------------
// 0x0114FE20
// ---------------------------------------------------------------------------
// @ 0x0114fe20
void cLightFilter::FE20(int param_2, int param_3)
{
	float v = m28 * 0.707f;
	void* src = *(void**)(param_3 + 4);
	int base = *(int*)(param_2 + 4);
	unsigned int s = *(unsigned short*)(param_2 + 0xe);
	FUN_01134260((void*)base, src, v, 0x100);
	FUN_01134260((void*)(base + s * 4), src, v, 0x100);
	FUN_01134260((void*)(base + s * 8), src, 0.0f, 0x100);
	FUN_01134260((void*)(base + s * 12), src, 0.0f, 0x100);
	FUN_01134260((void*)(base + s * 16), src, 0.0f, 0x100);
	FUN_01134260((void*)(base + s * 20), src, 0.0f, 0x100);
}

// ---------------------------------------------------------------------------
// 0x0114FF00
// ---------------------------------------------------------------------------
// @ 0x0114ff00
void cLightFilter::F900(void* param_1, float param_2)
{
	float* p = (float*)param_1;
	if (param_2 < 0.001f)
	{
		p[6] = 0.0f;
		p[7] = 0.0f;
		p[8] = 0.0f;
		p[4] = 0.0f;
		p[5] = 0.0f;
		return;
	}
	float t = tanf(param_2 * 3.1415927f);
	float t2 = t * t;
	float d = 1.0f / ((t * 1.414f + t2) + 1.0f);
	p[6] = d * t2;
	p[8] = d * t2;
	p[7] = (d * t2) * 2.0f;
	p[4] = ((t2 - 1.0f) * d) * 2.0f;
	p[5] = ((1.0f - t * 1.414f) + t2) * d;
}

// ---------------------------------------------------------------------------
// 0x0114FFD0
// ---------------------------------------------------------------------------
// @ 0x0114ffd0
void cLightFilter::FFD0(float* p, float param_2, float param_3)
{
	if (param_3 < 0.001f && -0.001f < param_3)
	{
		p[2] = 1.0f;
		p[3] = 0.0f;
		p[4] = 0.0f;
		p[0] = 0.0f;
		p[1] = 0.0f;
		return;
	}
	param_3 = param_3 + 1.0f;
	float t = tanf(param_2 * 3.1415927f);
	float t2 = t * t;
	float t14 = t * 1.414f;
	float d = 1.0f / ((t14 + t2) + 1.0f);
	float f7 = t2 * param_3;
	float f2 = sqrtf(param_3 + param_3) * t;
	p[2] = ((f2 + f7) + 1.0f) * d;
	p[3] = ((f7 - 1.0f) * d) * 2.0f;
	p[4] = ((1.0f - f2) + f7) * d;
	p[0] = ((t2 - 1.0f) * d) * 2.0f;
	p[1] = ((1.0f - t14) + t2) * d;
}

// ---------------------------------------------------------------------------
// 0x01150100
// ---------------------------------------------------------------------------
// @ 0x01150100
void cLightFilter::F100(float param_1, float param_2, float* param_3)
{
	float a = (360.0f - param_1) * 0.017453292f;
	if (3.1415927f < a)
		a = a - 6.2831855f;
	float ang = -2.3561945f - a;
	unsigned char i1 = 4;
	unsigned char i2 = 3;
	if (-2.3561945f >= a)
	{
		ang = -2.3561945f - a;
		i1 = 4;
		i2 = 3;
	}
	else if (-0.7853982f >= a)
	{
		ang = -0.7853982f - a;
		i1 = 2;
		i2 = 4;
	}
	else if (0.7853982f >= a)
	{
		ang = 0.7853982f - a;
		i1 = 0;
		i2 = 2;
	}
	else if (2.3561945f >= a)
	{
		ang = 2.3561945f - a;
		i1 = 3;
		i2 = 0;
	}
	else if (a > 2.3561945f)
	{
		ang = -2.3561945f - a;
		i1 = 4;
		i2 = 3;
	}
	param_3[0] = (float)i1 + (float)fabs(cosf(ang)) * param_2;
	param_3[1] = (float)fabs(sinf(ang)) * param_2 + (float)i2;
}

// ---------------------------------------------------------------------------
// 0x011501F0
// ---------------------------------------------------------------------------
// @ 0x011501f0
void cLightFilter::F1F0(float param_1, float param_2, float param_3, float param_4, float* param_5)
{
	float a = (360.0f - param_2) * 0.017453292f;
	if (3.1415927f < a)
		a = a - 6.2831855f;
	unsigned char b1 = 3;
	int i2 = 4;
	unsigned int u3 = 3;
	float ang = -2.3561945f - a;
	if (-2.3561945f < a)
	{
		if (a <= -0.7853982f)
		{
			ang = -0.7853982f - a;
			b1 = 4;
			i2 = 1;
		}
		else if (a <= 0.7853982f)
		{
			ang = 0.7853982f - a;
			b1 = 1;
			i2 = 0;
		}
		else if (a <= 2.3561945f)
		{
			ang = 2.3561945f - a;
			b1 = 2;
			i2 = 3;
			u3 = 0;
			goto LAB;
		}
		else
		{
			b1 = 3;
			i2 = 4;
		}
	}
	u3 = b1;
LAB:
	float f7;
	float f8;
	if (param_1 <= 1.0f)
	{
		f7 = (param_1 + 1.0f) * 0.5f;
		f8 = (1.0f - param_1) * 0.5f;
	}
	else
	{
		f7 = 1.0f;
		f8 = 0.0f;
	}
	float p7 = f7 * param_3;
	float p8 = f8 * param_3;
	float ca = cosf(ang);
	float sa = sinf(ang);
	param_5[i2] = ca * p7;
	param_5[u3] = sa * p7;
	param_5[4 - i2] = ca * p8;
	param_5[4 - u3] = sa * p8;
	if (param_4 <= 1e-10f || b1 != 1)
	{
		param_5[2] = 0.0f;
	}
	else
	{
		float x = param_5[0];
		float y = param_5[1];
		float m = (x < y) ? x : y;
		m = m * param_4;
		float cc = cosf(a);
		param_5[0] = x - m;
		param_5[1] = y - m;
		param_5[2] = (cc * m) * 1.414f;
	}
	float tmp = param_5[1];
	param_5[1] = param_5[2];
	param_5[2] = tmp;
}
