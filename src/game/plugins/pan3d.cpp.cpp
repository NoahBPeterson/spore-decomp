// src/game/plugins/pan3d.cpp.cpp -- migrated from slice(s) s0114f870, s0114e990, s0113a8b0 by tools/migrate/rewrite.py
// Object file: plugins/pan3d.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern uint8_t g_vtbl_014bc0fc[];        // 0x14bc0fc  shared base vtable (PlugIn-kind)
extern uint8_t g_vtbl_014b81e4[];        // 0x14b81e4  Pan3D vtable
#include <string.h>
#include <math.h>
#include <xmmintrin.h>
#pragma function(memset)
#pragma function(memcpy)

// ---- items of slice s0113a8b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t g_vtbl_014bc0fc[];        // 0x14bc0fc  shared base vtable (PlugIn-kind)
extern uint8_t g_vtbl_014b81e4[];        // 0x14b81e4  Pan3D vtable
static inline uint8_t&  B(void* p, unsigned o) { return *(uint8_t*)((char*)p + o); }
static inline uint16_t& W16(void* p, unsigned o) { return *(uint16_t*)((char*)p + o); }
static inline uint32_t& W(void* p, unsigned o) { return *(uint32_t*)((char*)p + o); }
static inline float&    F(void* p, unsigned o) { return *(float*)((char*)p + o); }
static inline void*&    P(void* p, unsigned o) { return *(void**)((char*)p + o); }
struct Ctx {
    uint8_t b[0x800];

    // --- real (callee) members, never defined here ---
    void     FastFirReset();                       // 0x114e580  FastFirEngine::Reset
    float    FastFirApply(int, int, int, int);     // 0x114e390  FastFirEngine::Apply
    void     ReverbConfigure(int);                 // 0x113a7a0  ReverbIR1 filter setup
    void*    SysAlloc(uint32_t, const char*, int, int); // 0x112c820 System::Alloc
    void     SysFree(void*, int);                  // 0x112c850  System::Free
    bool     AddTimer(void*, void*, void*, const char*, int, int); // 0x112d8e0 TimerManager::AddTimer
    void     RemoveTimer(void*);                   // 0x112dad0  System::RemoveTimer
    void     InitSndPlayer1();                     // 0x112dbb0  PlugIn::Initialize<SndPlayer1>
    void     Init16();                             // 0x114f4f0  PlugIn::Initialize<Pan3D> (zero 16 bytes)
    float    VoiceDecayRate();                     // 0x112e440  Voice decay / sample rate

    // --- slice functions (defined below) ---
    void     FUN_0113aa50(int, uint32_t*);
    void     FUN_0113ac60(int, uint32_t*);
    void     FUN_0113ae30();
    void     FUN_0113af90();
    void     FUN_0113b290(int, uint32_t*);
    void     FUN_0113b330();
    void     FUN_0113b750(int, float, float);
    void     FUN_0113b810();
    void     FUN_0113b9d0();
};
// ---- items of slice s0113a8b0 end

// ---- items of slice s0114e990 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef float f32;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
struct AudioChannelBuffer {
    char  pad0[4];
    f32*  mpSamples;   // +0x04
    char  pad8[0x0E - 0x08];
    u16   muStride;    // +0x0E
};
struct AudioProcessContext {
    char  pad00000[0x30000];
    char  pad30000[0x0C];
    AudioChannelBuffer* mpSrcBuffer;  // +0x3000C
    AudioChannelBuffer* mpDstBuffer;  // +0x30010
    AudioChannelBuffer* mpAuxBuffer;  // +0x30014
    void* mpFormat;                   // +0x30018
    u32   muMixerCpuCycles;           // +0x3001C
    s32   mNumSamples;                // +0x30020
    f32   mfSampleRate;               // +0x30024
    f32   mfResampleGain;             // +0x30028
    u8    mbChannelCount;             // +0x3002C
};
struct PeakingIir2 {
    char pad0[0x21];
    u8   mbChannelCount;    // +0x21
    char pad22[0x28 - 0x22];
    f32  mfCutoffFreq;      // +0x28
    char pad2c[0x30 - 0x2C];
    f32  mfGain;            // +0x30
    char pad34[0x38 - 0x34];
    f32  mfQ;               // +0x38
    char pad3c[0x40 - 0x3C];
    f32  mState[6][4];      // +0x40 .. +0x9F
    s32  mbActive;          // +0xA0
    f32  mfA1;              // +0xA4
    f32  mfA2;              // +0xA8
    f32  mfB0;              // +0xAC
    f32  mfB1;              // +0xB0
    f32  mfB2;              // +0xB4
    f32  mfLastOmega;       // +0xB8
    f32  mfLastGain;        // +0xBC
    f32  mfLastQ;           // +0xC0

    void CalculateFilterCoefficients(f32 omega, f32 gain, f32 q);  // 0x0114ee60
    int  Process(AudioProcessContext* ctx);                        // 0x0114ef10
};
// ---- items of slice s0114e990 end

// ---- items of slice s0114f870 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
extern "C" void __cdecl FUN_01134260(void* dst, void* src, float scale, unsigned int n);
extern "C" void __cdecl FUN_01160300(void* dst, int src, float a, float b, unsigned int n);
extern "C" void __cdecl FUN_011600e0(void* dst, int src, float a, float b, unsigned int n);
extern "C" double __cdecl iat_floor(double);
#pragma intrinsic(fabs)
struct IirSlot
{
	void Iir2Filter(void* a, int b, void* c);
};
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
// ---- items of slice s0114f870 end

// @ 0x0113ad10
void FUN_0113ad10(uint8_t* p, int param_2)
{
    if (p != 0) {
        P(p, 0) = g_vtbl_014bc0fc;
        uint8_t* e = p + 0x40;
        int i = 5;
        do {
            ((Ctx*)e)->Init16();
            e += 0x10;
        } while (--i >= 0);
    }
    if (param_2 != 0)
        W(p, 0xc) = (uint32_t)(p + param_2);
}

// @ 0x0113b060
bool FUN_0113b060(uint8_t* p, uint8_t* params)
{
    if (p != 0) {
        P(p, 0) = g_vtbl_014b81e4;
        ((Ctx*)(p + 0x30))->Init16();
    }
    uint8_t* ebp = p + 0x28;
    W(p, 0xc) = (uint32_t)ebp;
    if (params == 0) {
        F(p, 0x58) = 1.0f;
        W(p, 0x9c) = 0;
    } else {
        F(p, 0x58) = F(params, 0);
        W(p, 0x9c) = (uint32_t)(int)F(params, 4);
    }

    unsigned int aligned = ((unsigned int)p + 0xcf) & ~7u;
    uint32_t u3 = (uint32_t)(aligned - (unsigned int)p);
    W16(p, 0xc0) = (uint16_t)u3;
    memset((void*)((unsigned int)(uint16_t)u3 + (unsigned int)p), 0, 0x6c);

    uint32_t aligned2 = (uint32_t)((aligned + 0x73) & ~7u);
    W16(p, 0xc2) = (uint16_t)(aligned2 - (uint32_t)(unsigned int)p);
    memset((void*)((unsigned int)(uint16_t)(aligned2 - (uint32_t)(unsigned int)p) + (unsigned int)p), 0,
           W(p, 0x9c) * 0x50);

    float rate = F((uint8_t*)P(p, 4), 0xc0);
    F(p, 0x54) = rate;
    int delay = (int)(rate * F(p, 0x58));
    int n = ((delay + 0xff) & ~0xff) + 0x100;
    uint32_t size = (uint32_t)n * 4 + 0x122c;
    W(p, 0xa8) = (uint32_t)n;
    void* dst = ((Ctx*)P(p, 4))->SysAlloc(size,
        "rw::audio::core::Pan3D::Delay line, internal buffer and DSPSettingsLocal", 0x80, 0);
    W(p, 0x8c) = (uint32_t)dst;
    memset(dst, 0, size);

    uint32_t u = ((uint32_t)(unsigned int)dst + 0x7f) & ~(uint32_t)0x7f;
    W(p, 0x94) = u;
    W(p, 0x90) = (u + 0x100f) & ~(uint32_t)0xf;
    W(p, 0x98) = (W(p, 0x90) + W(p, 0xa8) * 4 + 0xf) & ~(uint32_t)0xf;

    F(p, 0x84) = 1.0f;
    F(ebp, 0) = 1.0f;
    W(p, 0xb0) = 0;
    W(p, 0xa0) = 0;
    B(p, 0xc6) = 0;
    F(p, 0x5c) = 1.0f;
    W(p, 0xa4) = 0;
    B(p, 0xc5) = 0;
    F(p, 0x6c) = 0.0f;
    F(p, 0x70) = 0.0f;
    W(p, 0xbc) = 0;
    W(p, 0x7c) = 0;
    W(p, 0x80) = 0;
    F(p, 0x60) = 0.0f;
    F(p, 0x64) = 0.0f;
    F(p, 0x68) = 0.0f;

    uint32_t n32 = W(p, 0xa8);
    float fn = (float)n32;
    if ((int)n32 < 0)
        fn += 4294967296.0f;
    uint8_t* voice = (uint8_t*)P(p, 8);
    F(voice, 0x28) = fn - F(p, 0x18) + F(voice, 0x28);
    F(p, 0x18) = fn;
    return true;
}

// @ 0x0114ee60
void PeakingIir2::CalculateFilterCoefficients(f32 omega, f32 gain, f32 q)
{
    const f32 c = cosf(omega);
    const f32 s = sinf(omega);

    const f32 sOver2Q = s / (q * 2.0f);
    const f32 A = sqrtf(gain);
    const f32 alpha = sOver2Q / A;
    const f32 k = 1.0f / (alpha + 1.0f);
    const f32 v13 = A * sOver2Q;

    mfA1 = k * (c * -2.0f);
    mfA2 = (1.0f - alpha) * k;
    mfB0 = (1.0f + v13) * k;
    mfB1 = k * (c * -2.0f);
    mfB2 = (1.0f - v13) * k;
}

// @ 0x0114f100
void __fastcall Iir2Filter(f32* state, int /*edx*/, f32* dst, f32* src, const f32* coef)
{
    const f32 a1 = coef[0];
    const f32 a2 = coef[1];
    const f32 b0 = coef[2];
    const f32 b1 = coef[3];
    const f32 b2 = coef[4];

    f32 x1 = state[0];
    f32 x2 = state[1];
    f32 y1 = state[2];
    f32 y2 = state[3];

    const f32* end = src + 0x100;
    while (src < end)
    {
        const f32 x0 = src[0];
        const f32 x1n = src[1];
        const f32 y0 = (x0 * b0 + x1 * b1 + x2 * b2 + 1e-18f) - y1 * a1 - y2 * a2;

        const f32 x2n = src[2];
        const f32 y1o = (x1n * b0 + x0 * b1 + x1 * b2 + 1e-18f) - y0 * a1 - y1 * a2;

        const f32 x3 = src[3];
        const f32 x4 = src[4];
        const f32 x5 = src[5];
        const f32 y2o = (x2n * b0 + x1n * b1 + x0 * b2 + 1e-18f) - y1o * a1 - y0 * a2;
        const f32 y3 = (x3 * b0 + x2n * b1 + x1n * b2 + 1e-18f) - y2o * a1 - y1o * a2;
        const f32 y4 = (x4 * b0 + x3 * b1 + x2n * b2 + 1e-18f) - y3 * a1 - y2o * a2;
        const f32 y5 = (x5 * b0 + x4 * b1 + x3 * b2 + 1e-18f) - y4 * a1 - y3 * a2;

        const f32 x6 = src[6];
        const f32 y6 = (x6 * b0 + x5 * b1 + x4 * b2 + 1e-18f) - y5 * a1 - y4 * a2;

        const f32 x7 = src[7];
        const f32 y7 = (x7 * b0 + x6 * b1 + x5 * b2 + 1e-18f) - y6 * a1 - y5 * a2;

        dst[0] = y0;
        dst[1] = y1o;
        dst[2] = y2o;
        dst[3] = y3;
        dst[4] = y4;
        dst[5] = y5;
        dst[6] = y6;
        dst[7] = y7;

        x1 = x7;
        x2 = x6;
        y1 = y7;
        y2 = y6;

        src += 8;
        dst += 8;
    }

    state[0] = x1;
    state[1] = x2;
    state[2] = y1;
    state[3] = y2;
}

// @ 0x0114f4f0
__declspec(noinline) void __fastcall ClearIirState(f32* state, int /*edx*/)
{
    state[0] = 0.0f;
    state[1] = 0.0f;
    state[2] = 0.0f;
    state[3] = 0.0f;
}

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
