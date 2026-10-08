// RenderWare 4 core audio: EaLayer3 / TimeStretch / SubMix decoders (slice s011369e0).
// Built with VC .NET 2003 (cl 13.10) + /GL /LTCG. Most functions call out heavily, so single-object
// compiles cannot match them; the bodies are the behaviour-equivalent reconstruction.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------------------
// Globals and helpers
// ---------------------------------------------------------------------------
extern int* g_timerListHead;   // 0x016e6288
extern int* g_timerListTail;   // 0x016e628c

class Sys
{
public:
	void* Alloc(int size, const char* name, int align, int flags);   // 0x0112c820
	void  Free(void* p, int flags);                                  // 0x0112c850
	void  RemoveTimer(void* handle);                                 // 0x0112dad0
	void  AddSub(void* a, void* b, void* cb, void* ctx, void* c, int d, int e);  // 0x0112d8e0
};

class TimerMgr
{
public:
	char AddTimer(void* handle, void* fn, void* self, const char* name, int a, int b); // 0x0112d8e0
};

class PlugIn
{
public:
	void Initialize(void);   // 0x0112dbb0
};

struct DecoderThunk
{
	void FUN_01137420(int, int);        // 0x01137420
	void FUN_01137450(int);             // 0x01137450
	void FUN_011376d0(int, int);        // 0x011376d0
	void FUN_011377f0(int, int, int);   // 0x011377f0
	int  FUN_011378a0(uint8_t);         // 0x011378a0
	int  FUN_011379f0(uint32_t*);       // 0x011379f0
	void FUN_01137060(int, int);        // 0x01137060
};

// extern "C" helpers
extern void  __cdecl FUN_01148cb0(void);                  // 0x01148cb0
extern void  __cdecl FUN_01148a00(int);                   // 0x01148a00
extern int   __cdecl FUN_01136460(void*);                 // 0x01136460
extern void  __cdecl FUN_01136980(int, int);              // 0x01136980
extern int   __cdecl FUN_01148e80(void);                  // 0x01148e80
extern void  __cdecl FUN_01148fd0(void*);                 // 0x01148fd0
extern void  __cdecl FUN_01148e30(void);                  // 0x01148e30
extern void  __cdecl FUN_01148eb0(int, int, int);         // 0x01148eb0
extern int   __cdecl FUN_01149490(int, int*);             // 0x01149490
extern void  __cdecl FUN_01148da0(float*, float, int);    // 0x01148da0 ScaleSamples
extern void  __cdecl memcpy_thunk(void*, const void*, unsigned);   // 0x011e0744
extern int   __cdecl FUN_0114a4a0(int);                   // 0x0114a4a0
extern void  __cdecl FUN_0114c880(int*, int, int);        // 0x0114c880
extern void* __cdecl operator_new_arr(void*, int, int);   // 0x011e073e
extern int   __cdecl FUN_011e7c70(int);                   // 0x011e7c70
extern int   __cdecl FUN_00a10ef0(int);                   // 0x00a10ef0 (bit reader; this=int,int)
extern void  __cdecl FUN_0112dae0(int, int, int);         // 0x0112dae0 PlugInDescFixup
extern void* __cdecl EALayer3Core_ctor(void*, int);       // 0x01149f70

static Sys* sys_of(int p) { return (Sys*)*(int*)(p + 4); }

static int Cvtss2si(float f)
{
	int r;
	__asm { cvtss2si eax, f }
	__asm { mov r, eax }
	return r;
}

// ---------------------------------------------------------------------------
// @ 0x011369e0  rw::audio::core::EaLayer3DecBase::DecodeGranule
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_011369e0(int param_1, int param_2)
{
	if (*(int*)(param_1 + 0x2f24) < 1)
	{
		int* blk = (int*)(*(int*)(param_1 + 0x24) + (uint32_t)*(uint8_t*)(param_1 + 0x30) * 0x14 + param_1);
		if (blk[3] == 0)
			blk = 0;
		else
		{
			(*(uint8_t*)(param_1 + 0x30))++;
			if (*(uint8_t*)(param_1 + 0x32) <= *(uint8_t*)(param_1 + 0x30))
				*(uint8_t*)(param_1 + 0x30) = 0;
		}
		if (*(char*)((char*)blk + 0x10) == 0)
			FUN_01148cb0();
		int v = blk[0];
		*(int*)(param_1 + 0x2f20) = v;
		*(int*)(param_1 + 0x2f24) = blk[3];
		FUN_01136980(v, 0);
	}
	else
	{
		FUN_01148a00(*(int*)(param_1 + 0x2f20));
	}
	int r = FUN_01136460((void*)(param_1 + 0x310));
	if (r < 0)
		return 0;
	uint32_t nch = *(uint8_t*)(param_1 + 0x2e);
	for (uint32_t ch = 0; ch < nch; ch++)
	{
		void* dst = (void*)(*(int*)(param_2 + 4) + *(uint16_t*)(param_2 + 0xe) * ch * 4);
		memcpy_thunk(dst, (void*)(param_1 + 0x310 + *(uint16_t*)(param_1 + 0x48) * ch * 4),
		             (uint32_t)*(uint16_t*)(param_1 + 0x48) * 4);
		FUN_01148da0((float*)dst, 0.000030517578125f, *(uint16_t*)(param_1 + 0x48));
	}
	*(int*)(param_1 + 0x2f24) -= (uint32_t)*(uint16_t*)(param_1 + 0x48);
	*(int*)(param_1 + 0x2f20) += *(int*)(param_1 + 0x44) + 4;
	return (uint32_t)*(uint16_t*)(param_1 + 0x48);
}

// ---------------------------------------------------------------------------
// @ 0x01136b10
// ---------------------------------------------------------------------------
int __cdecl FUN_01136b10(int param_1)
{
	int u = (param_1 + 0x47) & ~7;
	*(int*)(param_1 + 0x3c) = 0;
	*(int*)(param_1 + 0x38) = 0;
	*(int*)(param_1 + 0x34) = u;
	int r = 0;
	if (u != 0)
		r = FUN_01148e80();
	*(int*)(param_1 + 0x34) = r;
	return 1;
}

// ---------------------------------------------------------------------------
// @ 0x01136b40
// ---------------------------------------------------------------------------
void __cdecl FUN_01136b40(int param_1)
{
	FUN_01148fd0((void*)*(int*)(param_1 + 0x34));
}

// ---------------------------------------------------------------------------
// @ 0x01136b50  rw::audio::core::EaLayer3Dec::DecodeEvent
// ---------------------------------------------------------------------------
void __cdecl FUN_01136b50(int param_1, int param_2)
{
	if (*(int*)(param_1 + 0x3c) < 1)
	{
		int* blk = (int*)(*(int*)(param_1 + 0x24) + (uint32_t)*(uint8_t*)(param_1 + 0x30) * 0x14 + param_1);
		if (blk[3] == 0)
			blk = 0;
		else
		{
			(*(uint8_t*)(param_1 + 0x30))++;
			if (*(uint8_t*)(param_1 + 0x32) <= *(uint8_t*)(param_1 + 0x30))
				*(uint8_t*)(param_1 + 0x30) = 0;
		}
		if (*(char*)((char*)blk + 0x10) == 0)
		{
			*(int*)(param_1 + 0x3c) = 0;
			*(int*)(param_1 + 0x38) = 0;
			FUN_01148e30();
		}
		int v = blk[0];
		*(int*)(param_1 + 0x38) = v;
		int len = blk[3];
		*(int*)(param_1 + 0x3c) = len;
		FUN_01148eb0(v, len, *(uint8_t*)(param_1 + 0x2e));
	}
	int consumed;
	int n;
	do
	{
		consumed = FUN_01149490(param_2, &n);
		uint32_t nch = *(uint8_t*)(param_1 + 0x2e);
		for (uint32_t ch = 0; ch < nch; ch++)
			FUN_01148da0((float*)(*(int*)(param_2 + 4) + *(uint16_t*)(param_2 + 0xe) * ch * 4),
			             0.000030517578125f, n);
		*(int*)(param_1 + 0x38) += consumed;
	} while (n < 1);
	*(int*)(param_1 + 0x3c) -= n;
}

// ---------------------------------------------------------------------------
// @ 0x01136c60
// ---------------------------------------------------------------------------
void __cdecl FUN_01136c60(int param_1)
{
	int* arr = (int*)*(int*)(param_1 + 0x3c);
	if (arr[0] != 0)
	{
		for (int i = 0; i < *(int*)(param_1 + 0x48); i++)
			((void (__cdecl*)(int))**(int**)(*(int*)(param_1 + 0x3c) + i * 4))(0);
		sys_of(param_1)->Free((void*)arr[0], 0);
	}
}

// ---------------------------------------------------------------------------
// @ 0x01136ca0
// ---------------------------------------------------------------------------
int __cdecl FUN_01136ca0(int param_1, int* param_2)
{
	*param_2 = 0x10;
	return ((uint32_t)(param_1 + 1) >> 1) * 4 + 0x58;
}

// ---------------------------------------------------------------------------
// @ 0x01136cc0  rw::audio::core::EaLayer3DecBase::CreateInstance
// ---------------------------------------------------------------------------
int __cdecl FUN_01136cc0(int param_1, uint8_t param_2)
{
	*(uint8_t*)(param_1 + 0x54) = param_2;
	*(uint32_t*)(param_1 + 0x44) = (uint32_t)*(uint8_t*)(param_1 + 0x2e);
	*(uint32_t*)(param_1 + 0x48) = (*(uint8_t*)(param_1 + 0x2e) + 1) / 2;
	*(int*)(param_1 + 0x40) = 0;
	*(int*)(param_1 + 0x38) = 0;
	*(int*)(param_1 + 0x3c) = param_1 + 0x58;
	int total = 0;
	for (int i = 0; i < *(int*)(param_1 + 0x48); i++)
		total += 0x2e0;
	int base = (int)sys_of(param_1)->Alloc(total, "EALayer3Core Instances", 0x10, 0);
	for (int i = 0; i < *(int*)(param_1 + 0x48); i++)
	{
		int half = (i != *(int*)(param_1 + 0x44) / 2);
		int slot = *(int*)(param_1 + 0x3c) + i * 4;
		uint32_t p = (uint32_t)(base + 0xf) & ~0xf;
		*(uint32_t*)slot = p;
		base = p + 0x2e0;
		operator_new_arr((void*)p, 0, 0x2e0);
		void* core = (void*)*(int*)slot;
		void* r = core ? EALayer3Core_ctor(core, half + 1) : 0;
		*(int*)slot = (int)r;
		*(int*)(*(int*)slot + 0x2dc) = *(int*)(param_1 + 4);
	}
	*(int*)(param_1 + 0x50) = 0;
	*(uint8_t*)(param_1 + 0x55) = 0;
	*(int*)(param_1 + 0x4c) = 0x451;
	return 1;
}

// ---------------------------------------------------------------------------
// @ 0x01136de0
// ---------------------------------------------------------------------------
void __cdecl FUN_01136de0(int param_1)
{
	FUN_01136cc0(param_1, 2);
}

// ---------------------------------------------------------------------------
// @ 0x01136e10
// ---------------------------------------------------------------------------
void __fastcall FUN_01136e10(int param_1)
{
	float* p = (float*)(param_1 + 0x40);
	for (int i = 0x12; i != 0; i--)
	{
		*p = 0.0f;
		p += 2;
	}
	*(float*)(param_1 + 0xe8) = 0.0f;
	*(float*)(param_1 + 0x118) = 0.0f;
	*(float*)(param_1 + 0x130) = 0.0f;
	*(float*)(param_1 + 0xec) = 0.0f;
	*(float*)(param_1 + 0x11c) = 0.0f;
	*(float*)(param_1 + 0x134) = 0.0f;
	*(float*)(param_1 + 0xf0) = 0.0f;
	*(float*)(param_1 + 0x120) = 0.0f;
	*(float*)(param_1 + 0x138) = 0.0f;
	*(float*)(param_1 + 0xf4) = 0.0f;
	*(float*)(param_1 + 0x124) = 0.0f;
	*(float*)(param_1 + 0x13c) = 0.0f;
	*(float*)(param_1 + 0xf8) = 0.0f;
	*(float*)(param_1 + 0x128) = 0.0f;
	*(float*)(param_1 + 0x140) = 0.0f;
	*(float*)(param_1 + 0xfc) = 0.0f;
	*(float*)(param_1 + 0x12c) = 0.0f;
	*(float*)(param_1 + 0x144) = 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x01136ec0
// ---------------------------------------------------------------------------
void __fastcall FUN_01136ec0(int param_1)
{
	if (*(char*)(param_1 + 0x14d) == 1)
		sys_of(param_1)->RemoveTimer((void*)(param_1 + 0x24));
}

// ---------------------------------------------------------------------------
// @ 0x01136ee0
// ---------------------------------------------------------------------------
void __cdecl FUN_01136ee0(int param_1)
{
	if (*(int16_t*)(param_1 + 0x148) == 0)
		*(int16_t*)(param_1 + 0x148) =
			(int16_t)Cvtss2si(*(float*)(*(int*)(param_1 + 4) + 0xc0) * 0.01f);
	if (*(char*)(param_1 + 0x14c) != 0)
	{
		*(uint8_t*)(param_1 + 0x14c) = 0;
		return;
	}
	for (int off = 0x40; off <= 0x98; off += 8)
		*(float*)(param_1 + off) = 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x01136f80
// ---------------------------------------------------------------------------
int __fastcall FUN_01136f80(int param_1)
{
	FUN_01136e10(*(int*)(param_1 + 4));
	return 8;
}

// ---------------------------------------------------------------------------
// @ 0x01136fa0
// ---------------------------------------------------------------------------
int __cdecl FUN_01136fa0(int* param_1)
{
	if (param_1 != 0)
	{
		*param_1 = 0x014a7f54;
		((PlugIn*)((char*)param_1 + 0x24))->Initialize();
	}
	param_1[3] = (int)(param_1 + 0x10);
	*(uint8_t*)((char*)param_1 + 0x14d) = 0;
	*(int16_t*)((char*)param_1 + 0x148) =
		(int16_t)(*(float*)(param_1[1] + 0xc0) * 0.01f);
	for (int off = 0; off < 0x90; off += 8)
		*(float*)((char*)param_1 + 0x40 + off) = 0.0f;
	*(uint8_t*)((char*)param_1 + 0x14c) = 0;
	FUN_01136e10((int)param_1);
	*(int16_t*)((char*)param_1 + 0x14a) = 0;
	for (int i = 0; i < 6; i++)
		FUN_0114a4a0(i);
	char ok = ((TimerMgr*)(param_1[1] + 0x60))->AddTimer((void*)((char*)param_1 + 0x24),
	                                                      (void*)&FUN_01136ee0, param_1, "VuMeter", 1, 1);
	if (ok != 0)
		return 0;
	*(uint8_t*)((char*)param_1 + 0x14d) = 1;
	return 1;
}

// ---------------------------------------------------------------------------
// @ 0x01137060
// ---------------------------------------------------------------------------
void DecoderThunk::FUN_01137060(int, int)
{
	int param_1 = (int)this;
	int iVar1 = *(int*)(param_1 + 4);
	int* p = (int*)(*(int*)(iVar1 + 0x20) + *(int*)(iVar1 + 0xb4));
	*(int*)(iVar1 + 0xb4) += 8;
	p[0] = (int)&FUN_01136f80;
	p[1] = param_1;
}

// ---------------------------------------------------------------------------
// @ 0x011370d0
// ---------------------------------------------------------------------------
bool __cdecl FUN_011370d0(int* param_1)
{
	if (param_1 != 0)
		*param_1 = 0x014bc0fc;
	return true;
}
// ---------------------------------------------------------------------------
// @ 0x011370f0
// ---------------------------------------------------------------------------
int* __cdecl FUN_011370f0(void)
{
	*(int*)0x015bae30 = 0x015bae48;
	FUN_0112dae0((int)0x015bae10, 0, 0);
	return (int*)0x015bae48;
}

// ---------------------------------------------------------------------------
// @ 0x01137130
// ---------------------------------------------------------------------------
void __fastcall FUN_01137130(int param_1)
{
	if (*(int*)(param_1 + 0x30) != 0)
	{
		sys_of(param_1)->Free(*(void**)(param_1 + 0x30), 0);
		*(int*)(param_1 + 0x30) = 0;
	}
}

// ---------------------------------------------------------------------------
// @ 0x01137150
// ---------------------------------------------------------------------------
int __cdecl FUN_01137150(int param_1)
{
	return (uint32_t)*(uint8_t*)(param_1 + 8) * 0x1c + 0x80;
}

// ---------------------------------------------------------------------------
// @ 0x01137170  rw::audio::core::TimeStretch::CreateInstance
// ---------------------------------------------------------------------------
int __cdecl FUN_01137170(int* param_1, float* param_2)
{
	if (param_1 != 0)
		*param_1 = 0x014a8150;
	param_1[3] = (int)(param_1 + 0xe);
	float scale;
	int mode;
	int count;
	if (param_2 == 0)
	{
		scale = 9.0f;
		mode = 0;
		count = 0x10;
	}
	else
	{
		scale = param_2[0];
		mode = (int)param_2[1];
		count = (int)param_2[2];
	}
	uint32_t rate = (uint32_t)((*(float*)(param_1[1] + 0xc0) * scale) * 0.001f);
	uint32_t rounded = rate & ~7;
	if ((rate & 7) > 4)
		rounded += 8;
	uint32_t strideFloats = rounded * 4;
	uint32_t strideBytes = (strideFloats + 0xf) & ~0xf;
	uint32_t stride2 = (rounded * 0xc + 0xf) & ~0xf;
	uint16_t tail = (uint16_t)(((uint16_t)((int)param_1 + 0x87) & 0xfff8) - (uint16_t)(int)param_1);
	*(uint16_t*)((char*)param_1 + 0x7e) = tail;
	param_1[0x1e] = strideBytes;
	param_1[0x14] = rounded * 3;
	param_1[0x1d] = stride2;
	uint32_t nch = *(uint8_t*)((char*)param_1 + 0x21);
	int total = 0;
	for (uint32_t i = nch; i != 0; i--)
		total += strideBytes * 2 + stride2;
	if (mode == 1)
		total += strideBytes * 2;
	int base = (int)sys_of((int)param_1)->Alloc(total, "rw::audio::core::TimeStretch - Samples Buffers", 0x10, 0);
	param_1[0xc] = base;
	if (nch != 0)
	{
		int* pi5 = (int*)((int)param_1 + tail + 8);
		int* pi7 = (int*)((int)param_1 + tail + 0xc);
		for (uint32_t i = 0; i < nch; i++)
		{
			uint32_t a = (base + 0xf) & ~0xf;
			pi5[-1] = a;
			base = a + strideBytes;
			*pi5 = base;
			base += strideBytes;
			*pi7 = base;
			base += stride2;
			pi5 += 7;
			pi7 += 7;
		}
	}
	if (mode == 1)
	{
		uint32_t a = (base + 0xf) & ~0xf;
		param_1[10] = a;
		param_1[0xb] = a + strideBytes;
	}
	param_1[0xe] = 0x3f800000;
	param_1[0x13] = rounded;
	param_1[0x11] = 0x3f800000;
	param_1[0x16] = nch;
	*(float*)(param_1 + 0x12) = scale;
	param_1[0x15] = count;
	param_1[0x10] = mode;
	param_1[9] = 0;
	param_1[0x17] = 0;
	*(uint8_t*)((char*)param_1 + 0x7c) = 0;
	param_1[0x1c] = 0;
	param_1[0x1b] = 0;
	if (nch != 0)
	{
		char* p = (char*)param_1 + tail + 0x18;
		for (uint32_t i = nch; i != 0; i--)
		{
			*(float*)(p - 0x18) = 0.0f;
			*(int*)(p - 4) = 0;
			*(int*)p = 0;
			p += 0x1c;
		}
	}
	return 1;
}

// ---------------------------------------------------------------------------
// @ 0x011373c0
// ---------------------------------------------------------------------------
int* __cdecl FUN_011373c0(void)
{
	int* p = g_timerListHead;
	if (p == 0)
		return 0;
	int* r = (int*)((char*)p - 0x2c);
	g_timerListHead = (int*)*p;
	return r;
}

// ---------------------------------------------------------------------------
// @ 0x011373e0
// ---------------------------------------------------------------------------
int __cdecl FUN_011373e0(int param_1)
{
	int iVar2 = *(int*)(param_1 + 4);
	int* p = (int*)(iVar2 + 0x2c);
	*p = (int)g_timerListTail;
	*(int*)(iVar2 + 0x30) = 0;
	if (g_timerListTail != 0)
		*(int*)((char*)g_timerListTail + 4) = (int)p;
	g_timerListTail = p;
	*(uint8_t*)(iVar2 + 0x8e) = 1;
	return 8;
}

// ---------------------------------------------------------------------------
// @ 0x01137420
// ---------------------------------------------------------------------------
void DecoderThunk::FUN_01137420(int, int param_3)
{
	int* param_1 = (int*)this;
	param_1[3] = param_3;
	param_1[2] = *(int*)(param_3 + 0x24);
	*(uint8_t*)(param_1 + 4) = *(uint8_t*)(param_3 + 0x21);
	*param_1 = *(int*)(param_3 + 0x28);
	param_1[1] = 0;
	if (*(int*)(param_3 + 0x28) != 0)
		*(int*)(*(int*)(param_3 + 0x28) + 4) = (int)param_1;
	*(int*)(param_3 + 0x28) = (int)param_1;
}

// ---------------------------------------------------------------------------
// @ 0x01137450
// ---------------------------------------------------------------------------
void DecoderThunk::FUN_01137450(int param_2)
{
	int* param_1 = (int*)this;
	int iVar2 = param_1[3];
	if (iVar2 == 0)
		return;
	if (param_1 == *(int**)(iVar2 + 0x28))
		*(int*)(iVar2 + 0x28) = **(int**)(iVar2 + 0x28);
	if (param_1[1] != 0)
		*(int*)param_1[1] = *param_1;
	if (*param_1 != 0)
		*(int*)(*param_1 + 4) = param_1[1];
	if (param_2 != 0)
	{
		*(uint8_t*)(param_1[3] + 0x8f) = 1;
		int n = *(uint8_t*)(param_1[3] + 0x21);
		int off = 0x34;
		for (int i = 0; i < n; i++)
		{
			*(float*)(param_1[3] + off) += *(float*)(param_2 - 0x34 + off);
			off += 4;
		}
	}
	param_1[3] = 0;
	param_1[2] = 0;
	*(uint8_t*)(param_1 + 4) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x011374e0
// ---------------------------------------------------------------------------
int __fastcall FUN_011374e0(int param_1)
{
	(*(int16_t*)(*(int*)(param_1 + 0xc) + 0x8c))++;
	return *(int*)(param_1 + 8);
}

// ---------------------------------------------------------------------------
// @ 0x011374f0
// ---------------------------------------------------------------------------
void __fastcall FUN_011374f0(int param_1)
{
	int* n = *(int**)(param_1 + 0x28);
	while (n != 0)
	{
		int iVar2 = n[3];
		if (iVar2 != 0)
		{
			if (n == *(int**)(iVar2 + 0x28))
				*(int*)(iVar2 + 0x28) = **(int**)(iVar2 + 0x28);
			if (n[1] != 0)
				*(int*)n[1] = *n;
			if (*n != 0)
				*(int*)(*n + 4) = n[1];
			n[3] = 0;
			n[2] = 0;
			*(uint8_t*)(n + 4) = 0;
		}
		n = *(int**)(param_1 + 0x28);
	}
	if (*(char*)(param_1 + 0x8e) != 0)
	{
		int* p = (int*)(param_1 + 0x2c);
		if (p == g_timerListTail)
			g_timerListTail = (int*)*p;
		if (*(int**)(param_1 + 0x30) != 0)
			**(int**)(param_1 + 0x30) = *p;
		if (*p != 0)
			*(int*)(*p + 4) = *(int*)(param_1 + 0x30);
	}
	if (*(int*)(param_1 + 0x24) != 0)
		sys_of(param_1)->Free(*(void**)(param_1 + 0x24), 0);
}

// ---------------------------------------------------------------------------
// @ 0x01137590  rw::audio::core::SubMix::CreateInstance
// ---------------------------------------------------------------------------
int __cdecl FUN_01137590(int* param_1, int* param_2)
{
	if (param_1 != 0)
	{
		*param_1 = 0x014ab18c;
		param_1[10] = 0;
	}
	*(uint8_t*)((char*)param_1 + 0x8e) = 0;
	if (param_2 == 0)
		*(uint8_t*)(param_1 + 0x13) = 0;
	else
	{
		char* src = (char*)*param_2;
		char* dst = (char*)(param_1 + 0x13);
		char c;
		do
		{
			c = *src;
			*dst = c;
			src++;
			dst++;
		} while (c != 0);
	}
	uint32_t size = (uint32_t)*(uint8_t*)((char*)param_1 + 0x21) << 10;
	*(uint16_t*)(param_1 + 0x23) = 0;
	void* buf = sys_of((int)param_1)->Alloc(size, "rw::audio::core::SubMix::mpSubMixBuffer", 0x80, 0);
	param_1[9] = (int)buf;
	if (buf == 0)
		return 0;
	operator_new_arr(buf, 0, size);
	int iVar2 = param_1[1];
	int* p = (int*)(*(int*)(iVar2 + 0x20) + *(int*)(iVar2 + 0xb4));
	*(int*)(iVar2 + 0xb4) += 8;
	p[1] = (int)param_1;
	p[0] = (int)&FUN_011373e0;
	*(uint8_t*)((char*)param_1 + 0x8f) = 0;
	for (int i = 0xd; i <= 0x12; i++)
		param_1[i] = 0;
	return 1;
}

// ---------------------------------------------------------------------------
// @ 0x011376a0
// ---------------------------------------------------------------------------
int __stdcall FUN_011376a0(uint8_t param_1)
{
	if (param_1 != 4 && param_1 != 0)
		return 1;
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x011376d0
// ---------------------------------------------------------------------------
void DecoderThunk::FUN_011376d0(int param_2, int param_3)
{
	int param_1 = (int)this;
	int iVar7 = param_2 * 0x50 + *(int*)(param_1 + 0x58);
	int iVar6 = param_2 * 0x30 + (uint32_t)*(uint16_t*)(param_1 + 0x1c4) + param_1;
	int local = param_3;
	FUN_00a10ef0(4);
	uint8_t b = (uint8_t)FUN_00a10ef0(4);
	*(uint8_t*)(iVar7 + 0x48) = b;
	int c = FUN_00a10ef0(6);
	*(char*)(iVar6 + 0x2b) = (char)c + 1;
	int n = FUN_00a10ef0(0x12);
	*(float*)(iVar6 + 0x10) = (float)(uint32_t)n;
	uint8_t d = (uint8_t)FUN_00a10ef0(2);
	*(uint8_t*)(iVar7 + 0x49) = d;
	char e = (char)FUN_00a10ef0(1);
	*(int*)(iVar6 + 0x14) = FUN_00a10ef0(0x1d);
	if (e == 0)
		*(int*)(iVar6 + 0x18) = -1;
	else
		*(int*)(iVar6 + 0x18) = FUN_00a10ef0(0x20);
	if (*(char*)(iVar7 + 0x49) == 2)
		*(int*)(iVar7 + 0x10) = FUN_00a10ef0(0x20);
	if (e != 0)
	{
		if (*(char*)(iVar7 + 0x49) == 1 ||
		    (*(char*)(iVar7 + 0x49) == 2 && *(int*)(iVar7 + 0x10) <= *(int*)(iVar6 + 0x18)))
			*(int*)(iVar7 + 0xc) = FUN_00a10ef0(0x20);
		else
			*(int*)(iVar7 + 0xc) = 0;
	}
	*(int*)(iVar7 + 8) = param_3;
}

// ---------------------------------------------------------------------------
// @ 0x011377f0
// ---------------------------------------------------------------------------
void DecoderThunk::FUN_011377f0(int param_2, int param_3, int param_4)
{
	int param_1 = (int)this;
	int iVar1 = param_2 * 0x50 + *(int*)(param_1 + 0x58);
	int iVar2 = param_2 * 0x30 + (uint32_t)*(uint16_t*)(param_1 + 0x1c4) + param_1;
	if (param_4 > 0 && param_3 != 0)
	{
		int loc[6];
		char b;
		FUN_0114c880(loc, param_3, param_4);
		*(int*)(iVar2 + 0x20) = loc[3];
		*(int*)(iVar2 + 0x24) = loc[2];
		*(int*)(iVar1 + 0x3c) = loc[1];
		*(int*)(iVar1 + 0x40) = loc[0];
		*(int*)(iVar1 + 0x38) = loc[4];
		*(int*)(iVar1 + 0x44) = loc[5];
		*(uint8_t*)(iVar1 + 0x4c) = b;
		*(int*)(iVar2 + 0x1c) = 0;
		*(int*)(iVar1 + 0x14) = *(int*)(iVar2 + 0x24);
		return;
	}
	*(int*)(iVar2 + 0x20) = 0;
	*(int*)(iVar1 + 0x3c) = 0;
	*(int*)(iVar1 + 0x40) = 0;
	*(int*)(iVar1 + 0x38) = 0;
	*(uint8_t*)(iVar1 + 0x4c) = 1;
	*(int*)(iVar2 + 0x1c) = 0;
	*(int*)(iVar2 + 0x24) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x011378a0
// ---------------------------------------------------------------------------
int DecoderThunk::FUN_011378a0(uint8_t param_2)
{
	int param_1 = (int)this;
	int iVar2 = *(int*)(param_1 + 0x24) + (uint32_t)param_2 * 0x14 + param_1;
	int iVar1 = *(int*)(iVar2 + 0xc);
	if (iVar1 == 0)
		return 0;
	if (param_2 == *(uint8_t*)(param_1 + 0x31))
		return iVar1 - *(int*)(param_1 + 0x1c);
	return iVar1 - *(int*)(iVar2 + 8);
}

// ---------------------------------------------------------------------------
// @ 0x01137910
// ---------------------------------------------------------------------------
int __cdecl FUN_01137910(int* param_1)
{
	int iVar1;
	if (*param_1 == 0)
		iVar1 = 1;
	else
		iVar1 = Cvtss2si(*(float*)*param_1);
	return (((uint32_t)*(uint8_t*)(param_1 + 2) * 4 + 0x1d7) & ~7) + iVar1 * 0x30;
}

// ---------------------------------------------------------------------------
// @ 0x01137950
// ---------------------------------------------------------------------------
void __fastcall FUN_01137950(int param_1)
{
	char* pc = (char*)(param_1 + 0x69);
	for (int count = 0x14; count != 0; count--)
	{
		if (*pc == 2)
		{
			int iVar3 = *(int*)((uint32_t)(uint8_t)pc[1] * 0x30 + 8 +
			                    (uint32_t)*(uint16_t*)(param_1 + 0x1c4) + param_1);
			int iVar2 = *(int*)(iVar3 + 0x24) + (uint32_t)(uint8_t)pc[-1] * 0x14;
			int iVar4 = *(int*)(iVar2 + 0xc + iVar3);
			if (iVar4 != 0)
			{
				int base;
				if (pc[-1] == *(uint8_t*)(iVar3 + 0x31))
					base = *(int*)(iVar3 + 0x1c);
				else
					base = *(int*)(iVar2 + iVar3 + 8);
				if (iVar4 != base)
					goto next;
			}
			*pc = 0;
			if (*(int*)(pc - 0xd) != 0)
			{
				int* pi = (int*)((uint32_t)(uint8_t)pc[1] * 0x50 + *(int*)(param_1 + 0x58) + 0x18);
				*pi -= *(int*)(*(int*)(pc - 0xd) + 4);
				if (*(int*)(pc - 9) != 0)
					FUN_011e7c70(*(int*)(pc - 0xd));
				*(int*)(pc - 0xd) = 0;
			}
		}
	next:
		pc += 0x10;
	}
}

// ---------------------------------------------------------------------------
// @ 0x011379f0
// ---------------------------------------------------------------------------
int DecoderThunk::FUN_011379f0(uint32_t* param_2)
{
	int param_1 = (int)this;
	if (*(char*)((uint32_t)*(uint8_t*)(param_1 + 0x1cd) * 0x10 + 0x69 + param_1) == 0)
	{
		*param_2 = (uint32_t)*(uint8_t*)(param_1 + 0x1cd);
		uint8_t b = *(uint8_t*)(param_1 + 0x1cd) + 1;
		*(uint8_t*)(param_1 + 0x1cd) = (b == 0x14) - 1 & b;
		return 1;
	}
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01137a30
// ---------------------------------------------------------------------------
int __cdecl FUN_01137a30(int param_1)
{
	int iVar1 = *(int*)(param_1 + 4);
	uint32_t u = 0;
	if (*(uint8_t*)(iVar1 + 0x1ca) != 0)
	{
		char* pc = (char*)(*(uint16_t*)(iVar1 + 0x1c4) + 0x2a + iVar1);
		do
		{
			if (*(float*)(pc - 0x1e) == *(float*)(param_1 + 0x10) && *pc != 4 && *pc != 0)
			{
				if (*(double*)(pc - 0x2a) <= *(double*)(*(int*)(iVar1 + 4) + 8))
					return 0x18;
				*(double*)(pc - 0x2a) = *(double*)(param_1 + 8);
				return 0x18;
			}
			u++;
			pc += 0x30;
		} while (u < *(uint8_t*)(iVar1 + 0x1ca));
	}
	return 0x18;
}
