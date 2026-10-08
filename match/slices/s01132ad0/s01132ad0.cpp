// RenderWare 4 core audio: Snd9 / SNDSTRM stream layer (slice s01132ad0).
// Built with VC .NET 2003 (cl 13.10) + /GL /LTCG, so most of these functions cannot be byte-exact
// from a single-object compile; the source below is the complete behaviour-equivalent reconstruction.
// Flags: /vc71 /O2 /MD /Gy /TP
#include "types.h"

struct SNDSTREAMSTATE;
struct SndTrack;
typedef void (__cdecl *SndTimerFn)(void);

// ---------------------------------------------------------------------------
// Globals (retail addresses)
// ---------------------------------------------------------------------------
extern uint8_t g_sysInit;                 // 0x016e7c1c  Snd9 system initialised (==1)
extern uint8_t g_numStreams;              // 0x016e7bfe  number of stream slots
extern int8_t  g_numTimers;               // 0x016e7c1d  number of timer callbacks
extern int16_t g_numTracks;               // 0x016e7c20  number of tracks
extern int     g_frame;                   // 0x016e7c24  frame counter
extern SndTimerFn g_timers[];             // 0x016e7c28  timer callbacks
extern void*   g_parseFn;                 // 0x016e7c74  install-once parse callback
extern SNDSTREAMSTATE* g_streamStates[];  // 0x016e61e0  array of stream-state pointers
extern SndTrack g_tracks[];               // 0x016e7c78  track array
extern int*    g_voiceList;               // 0x016e6268  head of active-voice list
extern void*   g_sysObj;                  // 0x016e61a8  Snd9 system object
extern void*   g_voice;                   // 0x016e6260  Snd9 service voice
extern int     g_numChannels;             // 0x015bfe38  output channel count
extern int     g_key;                     // 0x015ba628  resource key compared by parsedata

extern const float kChanDefault;          // 0x014a7db0
extern const int8_t g_chanMap[];          // 0x014a7dee  channel remap table

// ---------------------------------------------------------------------------
// Low-level helpers / cross-slice callees
// ---------------------------------------------------------------------------
extern int   __cdecl FUN_0113f1c0(int);                // 0x0113f1c0
extern int   __cdecl FUN_01141190(void*);              // 0x01141190
extern int   __cdecl FUN_011411a0(void*, void*);       // 0x011411a0
extern int   __cdecl FUN_0113f1d0(void*, void*, void*, void*, int); // 0x0113f1d0
extern void  __cdecl FUN_0113f750(int);                // 0x0113f750
extern int   __cdecl FUN_011e7910(int, int, int, int, int, int);    // 0x011e7910
extern void  __cdecl FUN_01141690(void*);              // 0x01141690
extern int   __cdecl FUN_01141740(int, int);           // 0x01141740
extern void  __cdecl SNDSTRM_purge(int);               // 0x01132660
extern int   __cdecl FUN_01141200(void*);              // 0x01141200
extern int   __cdecl FUN_011411d0(void*, void*);       // 0x011411d0
extern int   __cdecl FUN_01141270(int);                // 0x01141270
extern int   __cdecl FUN_01132300(int);                // 0x01132300
extern int   __cdecl FUN_01141150(int);                // 0x01141150
extern void  __cdecl FUN_0113fec0(int);                // 0x0113fec0
extern int   __cdecl FUN_0113fba0(void*, int);         // 0x0113fba0
extern void  __cdecl FUN_011433b0(int);                // 0x011433b0
extern void  __cdecl FUN_01140890(int);                // 0x01140890
extern void  __cdecl FUN_011432a0(int);                // 0x011432a0
extern void  __cdecl FUN_01143210(int);                // 0x01143210
extern int   __cdecl FUN_0112e720(int, int, void*, void*, void*);   // 0x0112e720
extern int   __cdecl FUN_0113f720(int);                // 0x0113f720
extern int   __cdecl FUN_011390a0(void);               // 0x011390a0
extern int   __cdecl FUN_01138cf0(void);               // 0x01138cf0
extern int   __cdecl FUN_0113eda0(void*);              // 0x0113eda0
extern void  __cdecl FUN_0113ee40(void*);              // 0x0113ee40
extern void  __cdecl SNDSYSI_init(void);               // 0x0113f060
extern void  __cdecl SNDSTRMI_releasecallback(void);   // 0x01132370
extern void  __cdecl FUN_011323a0(void);               // 0x011323a0
extern void  __cdecl SNDSTRMI_parsechunk(void);        // 0x011328c0
extern void* __cdecl SNDMEMI_alloc(void*, int);        // 0x0113ec90
extern void  __cdecl FUN_01133450(void);               // 0x01133450
extern void  __cdecl FUN_01133460(void);               // 0x01133460
extern void  __cdecl SNDSTRMI_Destroy(int);            // 0x01132a10

class SndSysObj
{
public:
	void Lock(void);                 // 0x0112c600
	void Unlock(void);               // 0x0112c620
	bool FUN_0112c640(int);          // 0x0112c640
	int  FUN_0112ce00(void);         // 0x0112ce00
	int  FUN_0112cd60(int);          // 0x0112cd60
	int  FUN_00ff35d0(void);         // 0x00ff35d0
	void FUN_0112ccc0(int, void*);   // 0x0112ccc0  __thiscall, ret 8
};

class Voice
{
public:
	void Release(void);              // 0x0112e950
};

class RwStream
{
public:
	int QueueFile(int, int, int, void*, int);   // 0x011e69d0
	int QueueMem(int, int, void*, int);         // 0x011e6aa0
	int FUN_011e6c70(void);                     // 0x011e6c70
	int FUN_011e6bf0(void);                     // 0x011e6bf0
};

// ---------------------------------------------------------------------------
// Track / stream-state layouts (retail offsets, read off the disassembly)
// ---------------------------------------------------------------------------
struct SNDCHANNEL
{
	float   m_start;      // +0x00
	uint8_t m_flag;       // +0x04
	uint8_t m_index;      // +0x05
	uint8_t m_pad06[2];   // +0x06
	float   m_volume;     // +0x08
	int     m_link;       // +0x0c
	int     m_link2;      // +0x10
	uint8_t m_pad14[0xc]; // +0x14
	float   m_active;     // +0x20
}; // 0x24

struct SNDSTREAMSTATE
{
	int      m_stream;        // +0x00
	int      m_handle;        // +0x04
	int      m_08;            // +0x08
	int      m_result;        // +0x0c
	int      m_position;      // +0x10
	uint8_t  m_pad14;         // +0x14
	uint8_t  m_owned;         // +0x15
	uint8_t  m_16;            // +0x16
	uint8_t  m_pad17[0x98-0x17]; // +0x17
	int      m_98;            // +0x98
	uint8_t  m_pad9c[0xe8-0x9c]; // +0x9c
	int      m_key[4];        // +0xe8
	float*   m_channelBuf;    // +0xf8
	uint8_t  m_padfc[0x114-0xfc]; // +0xfc
	uint8_t  m_list114[0xc];  // +0x114
	uint8_t  m_list120[8];    // +0x120
	int      m_128;           // +0x128
	uint8_t  m_pad12c[4];     // +0x12c
	SNDCHANNEL m_channels[6]; // +0x130
	float    m_mixBuf[1];     // +0x208
};

struct SndTrack
{
	int      m_index;         // +0x00
	uint16_t m_entries[15];   // +0x04
	uint8_t  m_pad22;         // +0x22
	uint8_t  m_count;         // +0x23
	uint8_t  m_pad24[0x0c];   // +0x24
	float    m_volStart;      // +0x30
	float    m_volMax;        // +0x34
	float    m_volAcc;        // +0x38
	int      m_step;          // +0x3c
	int      m_stepBase;      // +0x40
	int      m_countdown;     // +0x44
	float    m_volTarget;     // +0x48
	uint8_t  m_pad4c[2];      // +0x4c
	uint8_t  m_4e;            // +0x4e
	uint8_t  m_4f;            // +0x4f
	uint8_t  m_50;            // +0x50
	uint8_t  m_pad51[0x10];   // +0x51
	uint8_t  m_60;            // +0x60
	uint8_t  m_61;            // +0x61
	uint8_t  m_pad62[6];      // +0x62
	uint8_t  m_68;            // +0x68
	uint8_t  m_69;            // +0x69
	uint8_t  m_pad6a[2];      // +0x6a
	void*    m_table;         // +0x6c
	int      m_70;            // +0x70
	int      m_74;            // +0x74
	int      m_78;            // +0x78
	uint8_t  m_pad7c[2];      // +0x7c
	uint16_t m_7e;            // +0x7e
	uint8_t  m_pad80[4];      // +0x80
}; // 0x84

// ---------------------------------------------------------------------------
// @ 0x01132ad0  SNDSTRMI_parsedata (QueueFile/QueueMem parse callback)
// ---------------------------------------------------------------------------
int __cdecl SNDSTRMI_parsedata(int* hdr, uint32_t size, uint32_t a3, void* a4,
                               char (__cdecl *cb)(int*, int), int cbArg, uint32_t* out)
{
	if (size < 8)
		return 0;
	if (cb != 0 && cb(hdr, cbArg) == 0)
		return 0;
	uint32_t n = (uint32_t)hdr[1];
	if (size < n)
		return 0;
	*out = n;
	return (int)(hdr[0] == g_key) + 1;
}

// ---------------------------------------------------------------------------
// @ 0x01132b50  SNDSTRMI_destroyall
// ---------------------------------------------------------------------------
int __cdecl SNDSTRMI_destroyall(void)
{
	int i = 0;
	if ((*(uint8_t*)0x016e7bfe) != 0)
	{
		do
		{
			SNDSTRMI_Destroy(i);
			i++;
		} while (i < (int)(uint32_t)(*(uint8_t*)0x016e7bfe));
	}
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01132b80  SNDSTRMI_create
// ---------------------------------------------------------------------------
int __cdecl SNDSTRMI_create(char* key, int numTracks, int a3, SNDSTREAMSTATE* state,
                            int size, void* streamPtr, int flag, int a8)
{
	if ((*(uint8_t*)0x016e7c1c) == 0)
		return -10;
	FUN_01133450();

	int idx = 0;
	if (g_numStreams != 0)
	{
		do
		{
			if (g_streamStates[idx] == 0)
			{
				int base = g_numChannels * 4 + 0x208;
				char* region = (char*)state + base;
				char* trackArea = region + numTracks * 0x28;
				int avail = FUN_0113f1c0(a3);

				SNDMEMI_alloc(state, 0x208);
				FUN_01141190(state->m_list114);
				FUN_01141190(state->m_list120);

				for (int i = 0; i < numTracks; i++)
					FUN_011411a0(state->m_list120, region + i * 0x28);

				int res = FUN_0113f1d0((void*)&SNDSTRMI_releasecallback, (void*)&FUN_011323a0,
				                       state, trackArea, FUN_0113f1c0(a3));
				state->m_result = res;
				if (res < 0)
				{
					FUN_01133460();
					return res;
				}

				if (flag == 0)
				{
					unsigned align = (unsigned)(avail + (int)trackArea) & 0xf;
					if (align != 0)
						avail += 0x10 - align;
					int h = FUN_011e7910(numTracks + 2, avail + (int)trackArea,
					                     (size - base) - numTracks * 0x28 - avail, a8, 0, 0);
					state->m_handle = h;
					if (h == 0)
					{
						FUN_0113f750(state->m_result);
						FUN_01133460();
						return -9;
					}
					state->m_owned = 0;
				}
				else
				{
					state->m_handle = (int)streamPtr;
					state->m_owned = 1;
				}

				state->m_position = 0;
				state->m_08 = -1;
				state->m_key[0] = ((int*)key)[0];
				state->m_key[1] = ((int*)key)[1];
				state->m_key[2] = ((int*)key)[2];
				state->m_key[3] = ((int*)key)[3];
				state->m_channelBuf = state->m_mixBuf;

				for (int i = 0; i < g_numChannels; i++)
					state->m_channelBuf[i] = (float)(int)*(int8_t*)&state->m_key[1] * 0.007874016f;

				float vol = (float)(int)*(int8_t*)key * 0.007874016f;
				for (int i = 0; i < 6; i++)
				{
					SNDCHANNEL* ch = &state->m_channels[i];
					ch->m_start = kChanDefault;
					ch->m_flag = 0;
					ch->m_index = (uint8_t)i;
					ch->m_volume = vol;
				}
				state->m_16 = 1;

				int active = 0;
				for (int i = 0; i < (int)(uint32_t)g_numStreams; i++)
					if (g_streamStates[i] != 0)
						active++;
				if (active == 0)
				{
					FUN_01141690((void*)&SNDSTRMI_parsechunk);
					g_parseFn = (void*)&SNDSTRMI_destroyall;
				}

				g_streamStates[idx] = state;
				if (flag == 0)
				{
					int t = ((RwStream*)state->m_handle)->FUN_011e6c70();
					FUN_01141740(idx, t / 3);
				}
				state->m_98 = 0;
				SNDSTRM_purge(idx);
				FUN_01133460();
				return idx;
			}
			idx++;
		} while (idx < (int)(uint32_t)g_numStreams);
	}

	FUN_01133460();
	return -9;
}

// ---------------------------------------------------------------------------
// @ 0x01132e70  SNDSTRMI_queue
// ---------------------------------------------------------------------------
int __cdecl SNDSTRMI_queue(uint32_t id, int a2, int a3, int a4, int a5)
{
	if ((*(uint8_t*)0x016e7c1c) == 0)
		return -10;
	FUN_01133450();

	if ((int)(uint32_t)g_numStreams <= (int)id || (int)id < 0)
	{
		FUN_01133460();
		return -8;
	}
	SNDSTREAMSTATE* st = g_streamStates[id];
	if (st == 0)
	{
		FUN_01133460();
		return -8;
	}
	if (st->m_128 == 0)
	{
		FUN_01133460();
		return -13;
	}

	if (a5 == 0)
	{
		st->m_stream = ((RwStream*)st->m_handle)->QueueFile(a2, a3, a3 >> 31,
		                                                   (void*)&SNDSTRMI_parsedata, 0);
	}
	else if (a5 == 1)
	{
		st->m_stream = ((RwStream*)st->m_handle)->QueueMem(a2, a3, (void*)&SNDSTRMI_parsedata, 0);
	}
	else
	{
		st->m_stream = a3;
	}

	if (st->m_stream == 0)
	{
		FUN_01133460();
		return -1;
	}

	int node = FUN_01141200(st->m_list120);
	SNDMEMI_alloc((void*)node, 0x28);
	FUN_011411d0(st->m_list114, (void*)node);
	*(int*)(node + 8) = st->m_stream;
	st->m_position += 0x100;
	if (st->m_position < 0)
		st->m_position = 0;
	*(uint32_t*)(node + 0xc) = (uint32_t)st->m_position | id;
	*(int*)(node + 0x20) = a2;
	int r = *(int*)(node + 0xc);
	FUN_01133460();
	return r;
}

// ---------------------------------------------------------------------------
// @ 0x01132f90
// ---------------------------------------------------------------------------
void __cdecl FUN_01132f90(int a, int b, int c)
{
	SNDSTRMI_queue(a, b, 0, c, 2);
}

// ---------------------------------------------------------------------------
// @ 0x01132fb0
// ---------------------------------------------------------------------------
int __cdecl FUN_01132fb0(int p1, int p2, int p3, int p4, int p5, int p6)
{
	return SNDSTRMI_create((char*)p2, p3, p4, (SNDSTREAMSTATE*)p5, p6, (void*)p1, 1, 0);
}

// ---------------------------------------------------------------------------
// @ 0x01132fe0
// ---------------------------------------------------------------------------
int __cdecl FUN_01132fe0(uint8_t* p)
{
	*(uint16_t*)(p + 8) = 0x1000;
	*(uint16_t*)(p + 0xc) = 0xffff;
	*(uint16_t*)(p + 0xa) = 0x1000;
	p[2] = 0x7f;
	p[0] = 0x7f;
	p[3] = 0x7f;
	p[1] = 0x3c;
	*(uint16_t*)(p + 0xe) = 0;
	p[4] = 0;
	*(uint16_t*)(p + 6) = 0;
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01133020
// ---------------------------------------------------------------------------
int __cdecl FUN_01133020(int a, int b)
{
	int t = g_numChannels + (a * 5 + 0x41) * 2;
	return FUN_0113f1c0(b) + t * 4;
}

// ---------------------------------------------------------------------------
// @ 0x01133050  rw::audio::core::Voice::CreateInstance
// ---------------------------------------------------------------------------
int __cdecl Voice_CreateInstance(int code)
{
	switch (code)
	{
	case 0:
		return 0;
	case 0xffffffed:
		return -1;
	case 0xffffffee:
		return -7;
	case 0xfffffff1:
		return -8;
	case 0xfffffff2:
		return -4;
	case 0xfffffff6:
		return -9;
	case 0xfffffff7:
		return -2;
	case 0xfffffff8:
		return -10;
	case 0xfffffff9:
		return -11;
	case 0xfffffffa:
		return -2;
	default:
		return -6;
	}
}

// ---------------------------------------------------------------------------
// @ 0x011330e0
// ---------------------------------------------------------------------------
bool __cdecl FUN_011330e0(void)
{
	return (*(uint8_t*)0x016e7c1c) == 1;
}

// ---------------------------------------------------------------------------
// @ 0x011330f0
// ---------------------------------------------------------------------------
int __cdecl FUN_011330f0(void)
{
	SndSysObj* sys = (SndSysObj*)g_sysObj;
	sys->Lock();
	((Voice*)g_voice)->Release();
	sys->Unlock();
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01133120  Snd9::System::Init
// ---------------------------------------------------------------------------
struct VoiceCtorDesc
{
	int     f00;    // +0x00
	int     f04;    // +0x04
	int     f08;    // +0x08
	int     f0c;    // +0x0c
	uint8_t f10;    // +0x10
	uint8_t pad11[0xb];
	uint8_t f1c;    // +0x1c
};

int __cdecl Snd9_System_Init(int param_1)
{
	int sys = (int)g_sysObj;
	if ((*(uint8_t*)0x016e7c1c) == 1)
		return 0;

	((SndSysObj*)sys)->Lock();
	int v = *(int*)(sys + 0xe0);
	((SndSysObj*)sys)->Unlock();

	char b;
	do
	{
		((SndSysObj*)sys)->Lock();
		b = (char)((SndSysObj*)sys)->FUN_0112c640(v);
		((SndSysObj*)sys)->Unlock();
	} while (b == 0);

	uint8_t dev[0x1c];
	int code = FUN_0113eda0(dev);
	int r = Voice_CreateInstance(code);
	if (r < 0)
		return Voice_CreateInstance(r);

	FUN_0113ee40(dev);
	SNDSYSI_init();
	((SndSysObj*)sys)->Lock();
	int u2 = ((SndSysObj*)sys)->FUN_0112cd60(FUN_011390a0());
	int u4 = ((SndSysObj*)sys)->FUN_0112cd60(FUN_01138cf0());

	if (param_1 == 0)
		param_1 = ((SndSysObj*)sys)->FUN_00ff35d0();

	VoiceCtorDesc d;
	d.f00 = 0;
	d.f04 = u2;
	d.f08 = 0;
	d.f0c = u4;
	d.f10 = 6;
	d.f1c = 6;

	Voice* voice = (Voice*)FUN_0112e720(0, 2, &d.f08, &d.f04, g_sysObj);
	g_voice = voice;
	*(const char**)((char*)voice + 0x14) = "Snd9 Service";

	int local3c = param_1;
	((SndSysObj*)d.f04)->FUN_0112ccc0(0, &local3c);
	((SndSysObj*)sys)->Unlock();
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01133250
// ---------------------------------------------------------------------------
void __cdecl FUN_01133250(void)
{
	*(void**)0x016e80c4 = (void*)0x01141f90;   // SFILTER_unpackealayer3init
	*(void**)0x016e80c8 = (void*)0x01141c30;   // SFILTER_unpackealayer3linit
	*(void**)0x016e80cc = (void*)0x01141990;   // SFILTER_unpackealayer3pinit
	*(int*)0x016e810c = 0x20;
	*(int*)0x016e8110 = 0x34;
	*(int*)0x016e8114 = 0x38;
}

// ---------------------------------------------------------------------------
// @ 0x01133290
// ---------------------------------------------------------------------------
void __cdecl FUN_01133290(void)
{
	int* p = g_voiceList;
	while (p != 0)
	{
		int* next = (int*)p[0];
		((void (__cdecl*)(int))p[2])(p[3]);
		p = next;
	}
}

// ---------------------------------------------------------------------------
// @ 0x011332c0  per-frame track update
// ---------------------------------------------------------------------------
void __cdecl FUN_011332c0(void)
{
	g_frame++;
	for (int i = 0; i < (int)g_numTimers; i++)
		g_timers[i]();

	if (g_numTracks <= 0)
		return;

	int off = 0;
	for (int i = 0; i < (int)g_numTracks; i++)
	{
		SndTrack* t = (SndTrack*)((char*)g_tracks + off);
		if (t->m_69 == 1)
		{
			if (t->m_index >= 0 && t->m_78 != 0)
			{
				t->m_68++;
				if (t->m_4f <= (uint8_t)t->m_68)
					t->m_68 = 0;
				t->m_7e = 0;
				FUN_011433b0(i);
				FUN_01140890(i);
			}

			bool changed = false;
			if (t->m_74 != 0)
			{
				t->m_50++;
				changed = true;
				if (t->m_4e <= (uint8_t)t->m_50)
					t->m_50 = 0;
			}

			float fv = t->m_volStart;
			if (fv != 0.0f)
			{
				float acc = t->m_volAcc + fv;
				float maxv = t->m_volMax;
				changed = true;
				t->m_volAcc = acc;
				bool done;
				if (fv >= 0.0f)
					done = !(acc < maxv);
				else
					done = !(maxv < acc);
				if (done)
				{
					t->m_volStart = 0.0f;
					t->m_volAcc = maxv;
				}
				if (t->m_volAcc < 0.0f)
				{
					FUN_011432a0(t->m_index);
					off += 0x84;
					continue;
				}
			}

			t->m_countdown--;
			if (t->m_step != 0)
			{
				t->m_stepBase += t->m_step;
				changed = true;
			}
			if (t->m_countdown == 0)
			{
				t->m_61++;
				if ((int8_t)t->m_60 <= (int8_t)t->m_61)
				{
					FUN_011432a0(t->m_index);
					off += 0x84;
					continue;
				}
				int cv = *(int*)((char*)t->m_table + t->m_61 * 8);
				t->m_countdown = cv;
				if (cv < 0)
					t->m_countdown = 0x7fffffff;
				t->m_step = (*(int*)((char*)t->m_table + t->m_61 * 8 + 4) * 0x10000 - t->m_stepBase)
				            / t->m_countdown;
			}

			if (changed)
			{
				FUN_01143210(i);
				FUN_0113fec0(i);
			}
		}
		off += 0x84;
	}
}

// ---------------------------------------------------------------------------
// @ 0x01133470
// ---------------------------------------------------------------------------
int __cdecl FUN_01133470(uint32_t id, int* out)
{
	out[0] = 0;
	out[1] = 0;
	out[2] = 0;
	out[3] = 0;
	if ((*(uint8_t*)0x016e7c1c) == 0)
		return -10;
	if ((int)id < 0)
		return -8;

	int a = FUN_01132300(id & 0xff);
	if (a == 0)
		return -8;

	int b = FUN_01141270(id);
	if (b == 0)
	{
		out[0] = 3;
		return 0;
	}
	if (*(char*)(b + 0x24) == 0)
	{
		out[0] = 0;
		return 0;
	}

	uint16_t sr;
	if (*(int*)(a + 0x114) == b)
	{
		out[0] = 2;
		sr = *(uint16_t*)(a + 0x18);
	}
	else
	{
		out[0] = 1;
		sr = *(uint16_t*)(a + 0x1c);
	}

	float rate = 1000.0f / (float)(int)sr;
	out[1] = (int)((float)(uint32_t)*(int*)(b + 0x14) * rate);
	out[2] = (int)((float)(uint32_t)(*(int*)(b + 0x18) - *(int*)(b + 0x14)) * rate);
	out[3] = (int)((float)(uint32_t)*(int*)(b + 0x1c) * rate);
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x011335a0
// ---------------------------------------------------------------------------
int __cdecl FUN_011335a0(int id, int* out)
{
	out[2] = 0;
	out[1] = 0;
	out[0] = 0;
	if ((*(uint8_t*)0x016e7c1c) == 0)
		return -10;

	int a = FUN_01132300(id);
	if (a == 0)
		return -8;

	int v = *(int*)(a + 0x11c);
	out[0] = v;
	if (v == 0)
		return 0;
	out[1] = *(int*)(*(int*)(a + 0x114) + 0xc);
	if (*(short*)(a + 0x18) == 0)
		return 0;

	uint32_t q = (uint32_t)(FUN_0113f720(*(int*)(a + 0xc)) * 1000) / (uint32_t)*(uint16_t*)(a + 0x18);
	out[2] = q;
	if (q == 0)
	{
		int c = FUN_01141270(out[1]);
		if (*(int*)(c + 0x10) != 0)
		{
			uint32_t m = (uint32_t)((RwStream*)*(int*)(a + 4))->FUN_011e6bf0();
			if (m > 0x3d0900)
				m = 0x3d0900;
			out[2] = (int)((m * 1000) / *(uint32_t*)(c + 0x10));
		}
	}
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01133660  Channel::Set (LTCG register ABI in the original: val in xmm0, this in edx)
// ---------------------------------------------------------------------------
void FUN_01133660(float val, SNDCHANNEL* ch)
{
	ch->m_volume = val;
	if (ch->m_active != 0.0f)
	{
		if (&ch->m_link == g_voiceList)
			g_voiceList = *(int**)g_voiceList;
		if (ch->m_link2 != 0)
			*(int*)ch->m_link2 = ch->m_link;
		if (ch->m_link != 0)
			*(int*)(ch->m_link + 4) = ch->m_link2;
		ch->m_active = 0.0f;
	}
}

// ---------------------------------------------------------------------------
// @ 0x011336b0
// ---------------------------------------------------------------------------
int __cdecl FUN_011336b0(int id, int param_2, float param_3)
{
	if ((*(uint8_t*)0x016e7c1c) == 0)
		return -10;

	int st = FUN_01132300(id);
	if (st == 0)
		return -8;

	if (param_2 == -1)
	{
		for (int i = 0; i < 6; i++)
		{
			SNDCHANNEL* ch = (SNDCHANNEL*)((char*)st + 0x130 + i * 0x24);
			ch->m_volume = param_3;
			if (ch->m_active != 0.0f)
			{
				if (&ch->m_link == g_voiceList)
					g_voiceList = *(int**)g_voiceList;
				if (ch->m_link2 != 0)
					*(int*)ch->m_link2 = ch->m_link;
				if (ch->m_link != 0)
					*(int*)(ch->m_link + 4) = ch->m_link2;
				ch->m_active = 0.0f;
			}
		}
	}
	else
	{
		FUN_01133660(param_3, (SNDCHANNEL*)((char*)st + 0x130 + param_2 * 0x24));
	}

	int idx = FUN_01141150(*(int*)(st + 8));
	if (idx >= 0)
	{
		int base = idx * 0x84;
		if (param_2 == -1)
		{
			SndTrack* t = (SndTrack*)((char*)g_tracks + base);
			for (int i = 0; i < (int)t->m_count; i++)
			{
				int16_t s = (int16_t)t->m_entries[i];
				SndTrack* c = (SndTrack*)((char*)g_tracks + s * 0x84);
				if (c->m_volAcc != param_3)
				{
					c->m_volAcc = param_3;
					c->m_volTarget = param_3;
					FUN_0113fec0(s);
				}
			}
		}
		else
		{
			SndTrack* t = (SndTrack*)((char*)g_tracks + base);
			int8_t k = g_chanMap[(uint32_t)t->m_count * 6 + param_2];
			if (k != -128)
			{
				int16_t s = (int16_t)t->m_entries[(uint8_t)k];
				SndTrack* c = (SndTrack*)((char*)g_tracks + s * 0x84);
				float old = c->m_volAcc;
				c->m_volStart = 0.0f;
				if (old != param_3)
				{
					c->m_volAcc = param_3;
					c->m_volTarget = param_3;
					FUN_0113fec0(s);
				}
			}
		}
	}
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x011339d0
// ---------------------------------------------------------------------------
int __cdecl FUN_011339d0(int id, int n)
{
	if ((*(uint8_t*)0x016e7c1c) == 0)
		return -10;
	int st = FUN_01132300(id);
	if (st == 0)
		return -8;
	if (n > 0x4000)
		n = 0x4000;
	*(uint16_t*)(st + 0xf0) = (uint16_t)n;
	FUN_0113fba0(*(void**)(st + 8), n);
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01133a20
// ---------------------------------------------------------------------------
int __cdecl FUN_01133a20(int id, int16_t v)
{
	if ((*(uint8_t*)0x016e7c1c) == 0)
		return -10;
	FUN_01133450();
	int p = FUN_01141270(id);
	int r = -8;
	if (p != 0)
	{
		*(int*)(p + 0x20) = (int)v;
		r = 0;
	}
	FUN_01133460();
	return r;
}

// ---------------------------------------------------------------------------
// @ 0x01133a60
// ---------------------------------------------------------------------------
void __stdcall FUN_01133a60(int*& p)
{
	int* v = p;
	p = 0;
	*(int*)((char*)v + 8) = 0;
}
