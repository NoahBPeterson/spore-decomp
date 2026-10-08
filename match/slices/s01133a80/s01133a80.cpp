// RenderWare 4 core audio: Collection, DecoderRegistry and PCM/EaLayer3 decoders (slice s01133a80).
// Built with VC .NET 2003 (cl 13.10) + /GL /LTCG; single-object compiles cannot match most callers.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------------------
// Globals / helpers
// ---------------------------------------------------------------------------
extern void* g_sys;                        // 0x016e61a8  rw::audio::core::System
extern uint32_t g_singleton[4];            // 0x016e6270  singleton scratch
extern const float kPcmScale;              // 0x0148f474  3.0517578e-05f (1/32768)
extern const float g_14a7e88[][2];         // 0x014a7e88
extern const float g_14a7ea8[];            // 0x014a7ea8

class System
{
public:
	void* Alloc(int size, const char* name, int align, int flags);   // 0x0112c820
	void  Free(void* p, int flags);                                  // 0x0112c850
};

class SndSub
{
public:
	void Init(void);   // 0x0112da90
};

extern int   __cdecl FUN_01143420(int, int, int, int*, void*);       // 0x01143420
extern void* __cdecl FUN_01143430(int, int, int, int, int, void*);   // 0x01143430

// ---------------------------------------------------------------------------
// List node / block / collection layouts (retail offsets)
// ---------------------------------------------------------------------------
struct CollNode
{
	CollNode* pnext;    // +0x0
	CollNode* pprev;    // +0x4
	int       data;     // +0x8
}; // 0xc

struct CollBlock
{
	CollBlock* pnext;   // +0x0
	int        count;   // +0x4
}; // 0x8, followed by `count` CollNodes

struct Collection
{
	CollBlock* mBlockHead;   // +0x0
	CollBlock* mBlockTail;   // +0x4
	int        mBlockCount;  // +0x8
	CollNode*  mFreeHead;    // +0xc
	CollNode*  mUsedHead;    // +0x10
	int        mSize;        // +0x14
	int        mCapacity;    // +0x18

	void      FUN_01133a80(CollNode* n);       // 0x01133a80
	bool      FUN_01133ad0(int add);           // 0x01133ad0
	bool      FUN_01133bd0(void* userdata);    // 0x01133bd0
	void      FUN_01133c30(int* slot);         // 0x01133c30
};

struct HeadList
{
	int* phead;   // +0x0
	int* ptail;   // +0x4
	int  count;   // +0x8

	int  FUN_01133ed0(int key);     // 0x01133ed0
	int* FUN_01133f00(int* entry);  // 0x01133f00
};

struct BitReader
{
	uint8_t  pad0[0x20];
	uint8_t* ptr;      // +0x20
	uint8_t  pad24[8];
	uint32_t buf;      // +0x2c
	int      bits;     // +0x30

	unsigned FUN_01134a60(int n);   // 0x01134a60
};

// ---------------------------------------------------------------------------
// @ 0x01133a80  Collection: move a used node to the free list
// ---------------------------------------------------------------------------
void Collection::FUN_01133a80(CollNode* n)
{
	Collection* c = this;
	if (n == c->mUsedHead)
		c->mUsedHead = n->pnext;
	if (n->pprev != 0)
		n->pprev->pnext = n->pnext;
	if (n->pnext != 0)
		n->pnext->pprev = n->pprev;
	n->pnext = c->mFreeHead;
	n->pprev = 0;
	if (c->mFreeHead != 0)
		c->mFreeHead->pprev = n;
	c->mFreeHead = n;
	c->mSize--;
}

// ---------------------------------------------------------------------------
// @ 0x01133ad0  rw::audio::core::Collection::AddCapacity
// ---------------------------------------------------------------------------
bool Collection::FUN_01133ad0(int add)
{
	Collection* c = this;
	int count = c->mCapacity + add;
	CollBlock* blk = (CollBlock*)((System*)g_sys)->Alloc(
		count * 0xc + 8, "rw::audio::core::Collection: NodeBlock", 0x10, 0);
	if (blk == 0)
		return true;
	blk->count = count;
	blk->pnext = 0;
	if (c->mBlockHead == 0)
		c->mBlockHead = blk;
	else
		c->mBlockTail->pnext = blk;
	c->mBlockCount++;
	c->mBlockTail = blk;

	CollNode* n = (CollNode*)((char*)blk + 8);
	for (int i = 0; i < count; i++)
	{
		n->data = 0;
		n->pnext = c->mFreeHead;
		n->pprev = 0;
		if (c->mFreeHead != 0)
			c->mFreeHead->pprev = n;
		c->mFreeHead = n;
		n++;
	}
	c->mCapacity += count;
	return false;
}

// ---------------------------------------------------------------------------
// @ 0x01133b60  get first used node
// ---------------------------------------------------------------------------
int __fastcall FUN_01133b60(int p)
{
	if (*(int*)(p + 0x10) != 0)
		return *(int*)(p + 0x10);
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01133b70  free every node block
// ---------------------------------------------------------------------------
void __fastcall FUN_01133b70(int* c)
{
	int* blk = (int*)*c;
	if (blk != 0)
	{
		int next = *blk;
		*c = next;
		if (next == 0)
			c[1] = 0;
		c[2] = c[2] - 1;
		while (blk != 0)
		{
			((System*)g_sys)->Free(blk, 0);
			blk = (int*)*c;
			if (blk == 0)
				break;
			next = *blk;
			*c = next;
			if (next == 0)
				c[1] = 0;
			c[2] = c[2] - 1;
		}
	}
	c[3] = 0;
	c[4] = 0;
	c[0] = 0;
	c[1] = 0;
	c[2] = 0;
	c[5] = 0;
	c[6] = 0;
}

// ---------------------------------------------------------------------------
// @ 0x01133bd0  allocate a node from the free list into the used list
// ---------------------------------------------------------------------------
bool Collection::FUN_01133bd0(void* userdata)
{
	Collection* c = this;
	bool r = false;
	if (c->mFreeHead == 0)
	{
		r = FUN_01133ad0(c->mSize + 1);
		if (r)
			return r;
	}
	CollNode* n = c->mFreeHead;
	if (n != 0)
	{
		c->mFreeHead = n->pnext;
		if (c->mFreeHead != 0)
			c->mFreeHead->pprev = 0;
	}
	*(void**)((char*)n + 8) = userdata;
	*(void**)userdata = n;
	n->pnext = c->mUsedHead;
	n->pprev = 0;
	if (c->mUsedHead != 0)
		c->mUsedHead->pprev = n;
	c->mUsedHead = n;
	c->mSize++;
	return r;
}

// ---------------------------------------------------------------------------
// @ 0x01133c30  release a node given a pointer-to-slot
// ---------------------------------------------------------------------------
void Collection::FUN_01133c30(int* slot)
{
	Collection* c = this;
	CollNode* n = (CollNode*)*slot;
	*slot = 0;
	n->data = 0;
	if (n == c->mUsedHead)
		c->mUsedHead = n->pnext;
	if (n->pprev != 0)
		n->pprev->pnext = n->pnext;
	if (n->pnext != 0)
		n->pnext->pprev = n->pprev;
	n->pnext = c->mFreeHead;
	n->pprev = 0;
	if (c->mFreeHead != 0)
		c->mFreeHead->pprev = n;
	c->mFreeHead = n;
	c->mSize--;
}

// ---------------------------------------------------------------------------
// @ 0x01133c90  shrink: release fully-used blocks
// ---------------------------------------------------------------------------
bool __fastcall FUN_01133c90(Collection* c)
{
	CollBlock* blk = c->mBlockHead;
	bool r = false;
	if (blk != 0 && blk->pnext != 0 && blk->count <= c->mCapacity - c->mSize)
	{
		int i = 0;
		CollNode* n = (CollNode*)((char*)blk + 8);
		CollNode* start = n;
		if (blk->count > 0)
		{
			for (;;)
			{
				if (*(int*)((char*)n + 8) == 0)   // n[1].data == 0 => free?
				{
					if (n == c->mFreeHead)
						c->mFreeHead = n->pnext;
					if (n->pprev != 0)
						n->pprev->pnext = n->pnext;
					if (n->pnext != 0)
						n->pnext->pprev = n->pprev;
				}
				i++;
				n = (CollNode*)((char*)n + 0xc);
				if (i >= blk->count)
					break;
			}
		}
		int local4 = 0;
		if (blk->count > 0)
		{
			do
			{
				CollNode* p = *(CollNode**)((char*)start + 8); // start[1].pnext (userdata slot)
				if (p != 0)
				{
					CollNode* q = p->pnext;
					p->pnext = 0;
					q->data = 0;
					if (q == c->mUsedHead)
						c->mUsedHead = q->pnext;
					if (q->pprev != 0)
						q->pprev->pnext = q->pnext;
					if (q->pnext != 0)
						q->pnext->pprev = q->pprev;
					q->pnext = c->mFreeHead;
					q->pprev = 0;
					if (c->mFreeHead != 0)
						c->mFreeHead->pprev = q;
					c->mFreeHead = q;
					c->mSize--;
					if (start == c->mFreeHead)
						c->mFreeHead = start->pnext;
					if (start->pprev != 0)
						start->pprev->pnext = start->pnext;
					if (start->pnext != 0)
						start->pnext->pprev = start->pprev;
					if (c->mFreeHead == 0)
					{
						if ((char)c->FUN_01133ad0(c->mSize + 1) != 0)
							goto next;
					}
					{
						CollNode* f = c->mFreeHead;
						if (f != 0)
						{
							c->mFreeHead = f->pnext;
							if (c->mFreeHead != 0)
								c->mFreeHead->pprev = 0;
						}
						*(CollNode**)((char*)f + 8) = p;
						p->pnext = f;
						f->pnext = c->mUsedHead;
						f->pprev = 0;
						if (c->mUsedHead != 0)
							c->mUsedHead->pprev = f;
						c->mUsedHead = f;
						c->mSize++;
					}
				}
			next:
				local4++;
				start = (CollNode*)((char*)start + 0xc);
			} while (local4 < blk->count);
		}
		if (c->mBlockHead != 0)
		{
			c->mBlockHead = c->mBlockHead->pnext;
			if (c->mBlockHead == 0)
				c->mBlockTail = 0;
			c->mBlockCount--;
		}
		c->mCapacity -= blk->count;
		((System*)g_sys)->Free(blk, 0);
		r = 1;
	}
	return r;
}

// ---------------------------------------------------------------------------
// @ 0x01133e30  free every used node back to the free list
// ---------------------------------------------------------------------------
void __fastcall FUN_01133e30(Collection* c)
{
	while (c->mUsedHead != 0)
	{
		CollNode* n = c->mUsedHead;
		CollNode* inner = (CollNode*)n->data;
		if (inner != 0)
		{
			n = inner->pnext;
			inner->pnext = 0;
			n->data = 0;
			n = c->mUsedHead;
		}
		if (n == c->mUsedHead)
			c->mUsedHead = n->pnext;
		if (n->pprev != 0)
			n->pprev->pnext = n->pnext;
		if (n->pnext != 0)
			n->pnext->pprev = n->pprev;
		n->pnext = c->mFreeHead;
		n->pprev = 0;
		if (c->mFreeHead != 0)
			c->mFreeHead->pprev = n;
		c->mFreeHead = n;
		c->mSize--;
	}
}

// ---------------------------------------------------------------------------
// @ 0x01133ea0
// ---------------------------------------------------------------------------
void __fastcall FUN_01133ea0(int p)
{
	((System*)*(void**)(p + 0xc))->Free((void*)p, 0);
}

// ---------------------------------------------------------------------------
// @ 0x01133ed0  find node whose +0x14 field equals key
// ---------------------------------------------------------------------------
int HeadList::FUN_01133ed0(int key)
{
	int* list = (int*)this;
	int p = *list;
	while (p != 0)
	{
		int base = p - 0x10;
		int next = *(int*)p;
		if (*(int*)(base + 0x14) == key)
			return base;
		p = next;
	}
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01133f00  find-or-insert node
// ---------------------------------------------------------------------------
int* HeadList::FUN_01133f00(int* entry)
{
	int* list = (int*)this;
	int* p = (int*)*list;
	if (p != 0)
	{
		int* q = p;
		int* next;
		do
		{
			next = (int*)*q;
			if (q[1] == entry[5])
				return q - 4;
			q = next;
		} while (next != 0);
	}
	int* slot = entry + 4;
	*slot = (int)p;
	if (list[1] == 0)
		list[1] = (int)slot;
	list[2] = list[2] + 1;
	*list = (int)slot;
	return entry;
}

// ---------------------------------------------------------------------------
// @ 0x01133f40  destructor-like: notify, free storage, free self
// ---------------------------------------------------------------------------
void __fastcall FUN_01133f40(int p)
{
	void (*notify)(int) = *(void (**)(int))(p + 0xc);
	if (notify != 0)
		notify(p);
	if (*(int*)(p + 0x10) != 0)
		((System*)g_sys)->Free(*(void**)(p + 0x10), 0);
	((System*)g_sys)->Free((void*)p, 0);
}

// ---------------------------------------------------------------------------
// @ 0x01133f80  allocate a 0x10-byte object owned by sys
// ---------------------------------------------------------------------------
void* __cdecl FUN_01133f80(System* sys)
{
	void* p = sys->Alloc(0x10, 0, 0x10, 0);
	if (p != 0)
	{
		*(int*)((char*)p + 0) = 0;
		*(int*)((char*)p + 4) = 0;
		*(int*)((char*)p + 8) = 0;
		*(System**)((char*)p + 0xc) = sys;
		return p;
	}
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01133fc0  rw::audio::core::DecoderRegistry::DecoderFactory
// ---------------------------------------------------------------------------
void* __cdecl FUN_01133fc0(int* desc, int param_2, int param_3, System* param_4)
{
	int iStack_8 = ((int (__cdecl*)(int, int**))desc[0])(param_2, &desc);
	int iStack_4 = param_3 * 0x14;
	int16_t sVar1 = *(int16_t*)((char*)desc + 0x18);
	int iVar7 = ((iStack_8 + 7) & ~7) + iStack_4;
	int bVar = (sVar1 != 0);
	int* puVar4 = desc;
	int puStack_c = 0;
	if (sVar1 != 0)
	{
		int iVar3 = FUN_01143420(param_2, 2, sVar1, &puStack_c, param_4);
		iVar7 = (iVar7 + ((puStack_c - 1) & ~(puStack_c - 1))) + iVar3;
		puVar4 = (puStack_c < (int)desc) ? desc : (int*)puStack_c;
	}
	int iVar3 = iVar7;
	if (iVar7 == 0)
		iVar3 = 0x34;
	int* p = (int*)((System*)g_sys)->Alloc(iVar3, 0, (int)puVar4, 0);
	if (p != 0)
	{
		*p = 0x014a7e54;
		p[3] = desc[2];
		p[4] = 0;
		*(char*)((char*)p + 0x2e) = (char)param_2;
		p[1] = (int)param_4;
		char ok = ((char (__cdecl*)(int*))desc[1])(p);
		if (ok != 0)
		{
			p[2] = (int)p;
			p[5] = desc[3];
			p[6] = desc[5];
			p[8] = iVar7;
			unsigned uVar8 = ((int)p + iStack_8 + 7) & ~7;
			*(char*)((char*)p + 0x32) = (char)param_3;
			*(uint16_t*)((char*)p + 0x2c) = 0;
			p[7] = 0;
			*(char*)((char*)p + 0x2f) = 0;
			*(char*)((char*)p + 0x30) = 0;
			*(char*)((char*)p + 0x31) = 0;
			*(char*)((char*)p + 0x33) = (char)bVar;
			p[9] = uVar8 - (int)p;
			if ((char)bVar == 0)
			{
			lab:
				int i = 0;
				int* q = (int*)(p[9] + (int)p);
				if (*(char*)((char*)p + 0x32) != 0)
				{
					do
					{
						*q = 0;
						q[3] = 0;
						i++;
						q += 5;
					} while (i < (int)(unsigned)*(uint8_t*)((char*)p + 0x32));
				}
				return p;
			}
			FUN_01143420(param_2, 2, *(int16_t*)((char*)desc + 0x18), &param_3, param_4);
			uVar8 = (uVar8 + (param_3 - 1) + iStack_4) & ~(param_3 - 1);
			p[10] = (uVar8 - (int)p) & 0xffff;
			void* storage = ((System*)g_sys)->Alloc(
				*(uint16_t*)((char*)desc + 0x18) * param_2 * 4, "Decoder block storage", 0x80, 0);
			p[4] = (int)storage;
			if (storage != 0)
			{
				FUN_01143430(param_2, 2, *(int16_t*)((char*)desc + 0x18), uVar8, (int)storage, param_4);
				goto lab;
			}
		}
		if (p[3] != 0)
			((void (__cdecl*)(int*))p[3])(p);
		if (p[4] != 0)
			((System*)g_sys)->Free((void*)p[4], 0);
		((System*)g_sys)->Free(p, 0);
	}
	return 0;
}

// ---------------------------------------------------------------------------
// @ 0x011341c0
// ---------------------------------------------------------------------------
void* __fastcall FUN_011341c0(int* p)
{
	p[4] = 0;
	p[0x17] = 0;
	((SndSub*)((char*)p + 0x60))->Init();
	g_singleton[0] = 0;
	g_singleton[1] = 0;
	g_singleton[2] = 0;
	g_singleton[3] = 0;
	*p = (int)g_singleton;
	return p;
}

// ---------------------------------------------------------------------------
// @ 0x01134200  dst[i] = src[i] * scale
// ---------------------------------------------------------------------------
void __cdecl FUN_01134200(float* dst, float* src, float scale, int count)
{
	float* end = dst + count;
	do
	{
		for (int k = 0; k < 16; k++)
			dst[k] = src[k] * scale;
		src += 16;
		dst += 16;
	} while (dst != end);
}

// ---------------------------------------------------------------------------
// @ 0x01134260
// ---------------------------------------------------------------------------
void __cdecl FUN_01134260(float* dst, float* src, float scale, uint32_t count)
{
	if (((((uint32_t)dst | (uint32_t)src) & 0xf) == 0) && ((count & 0xf) == 0))
	{
		FUN_01134200(dst, src, scale, count);
	}
	else
	{
		float* end = dst + count;
		if (dst < end)
		{
			int diff = (int)src - (int)dst;
			do
			{
				*dst = *(float*)(diff + (int)dst) * scale;
				dst = dst + 1;
			} while (dst < end);
		}
	}
	volatile int barrier = 0;
	(void)barrier;
}

// ---------------------------------------------------------------------------
// @ 0x011342c0  dst[i] += src[i] * scale
// ---------------------------------------------------------------------------
void __cdecl FUN_011342c0(float* dst, float* src, float scale, uint32_t count)
{
	if (((((uint32_t)dst | (uint32_t)src) & 0xf) == 0) && ((count & 0xf) == 0))
	{
		float* end = dst + count;
		do
		{
			for (int k = 0; k < 16; k++)
				dst[k] = src[k] * scale + dst[k];
			src += 16;
			dst += 16;
		} while (dst != end);
		return;
	}
	float* end = dst + count;
	if (dst < end)
	{
		int diff = (int)src - (int)dst;
		do
		{
			*dst = *(float*)(diff + (int)dst) * scale + *dst;
			dst = dst + 1;
		} while (dst < end);
	}
}

// ---------------------------------------------------------------------------
// @ 0x01134380  Xas1 decoder create event
// ---------------------------------------------------------------------------
bool __cdecl FUN_01134380(int p)
{
	*(int*)(p + 0x38) = 0;
	*(int*)(p + 0x34) = 0;
	return true;
}

// ---------------------------------------------------------------------------
// @ 0x011343b0  Xas1 decode block
// ---------------------------------------------------------------------------
int __cdecl FUN_011343b0(int c, int param_2)
{
	if (*(int*)(c + 0x38) < 1)
	{
		int* blk = (int*)(*(int*)(c + 0x24) + (uint32_t)*(uint8_t*)(c + 0x30) * 0x14 + c);
		if (blk[3] == 0)
		{
			blk = 0;
		}
		else
		{
			(*(uint8_t*)(c + 0x30))++;
			if (*(uint8_t*)(c + 0x32) <= *(uint8_t*)(c + 0x30))
				*(uint8_t*)(c + 0x30) = 0;
		}
		if (*(char*)((char*)blk + 0x10) == 0)
		{
			*(int*)(c + 0x38) = 0;
			*(int*)(c + 0x34) = 0;
		}
		*(int*)(c + 0x34) = blk[0];
		*(int*)(c + 0x38) = blk[3];
	}

	uint32_t nch = (uint32_t)*(uint8_t*)(c + 0x2e);
	for (uint32_t ch = 0; ch < nch; ch++)
	{
		int iVar11 = *(int*)(c + 0x34);
		float* pf = (float*)(*(int*)(param_2 + 4) + *(uint16_t*)(param_2 + 0xe) * ch * 4);
		uint32_t uVar9 = (uint32_t)*(uint8_t*)(iVar11 + ch * 2);
		uint32_t uVar10 = uVar9 & 0xf;
		float fVar1 = g_14a7e88[uVar10][0];
		float fVar2 = g_14a7e88[uVar10][1];
		int iVar7 = iVar11 + nch * 2;
		pf[0] = (float)(int)(*(int8_t*)(iVar11 + 1 + ch * 2) * 0x100 + (uVar9 & 0xf0)) * kPcmScale;
		uVar9 = (uint32_t)*(uint8_t*)(iVar7 + ch * 2);
		float fVar3 = g_14a7ea8[uVar9 & 0xf];
		pf[1] = (float)(int)(*(int8_t*)(iVar7 + 1 + ch * 2) * 0x100 + (uVar9 & 0xf0)) * kPcmScale;
		pf += 2;
		uint8_t* pb = (uint8_t*)(iVar7 + nch * 2 + ch);
		for (int i = 3; i != 0; i--)
		{
			uint8_t b = *pb;
			pf[0] = (float)(int)((uint32_t)(b >> 4) << 0x1c) * fVar3 + pf[-2] * fVar2 + pf[-1] * fVar1;
			pf[1] = (pf[-1] * fVar2 + pf[0] * fVar1) + (float)(int)((uint32_t)b << 0x1c) * fVar3;
			b = pb[nch];
			pf[2] = (float)(int)((uint32_t)(b >> 4) << 0x1c) * fVar3 + pf[0] * fVar2 + pf[1] * fVar1;
			pf[3] = (pf[1] * fVar2 + pf[2] * fVar1) + (float)(int)((uint32_t)b << 0x1c) * fVar3;
			b = pb[nch * 2];
			pb += nch * 3;
			pf[4] = (float)(int)((uint32_t)(b >> 4) << 0x1c) * fVar3 + pf[2] * fVar2 + pf[3] * fVar1;
			pf[5] = (pf[3] * fVar2 + pf[4] * fVar1) + (float)(int)((uint32_t)b << 0x1c) * fVar3;
			b = *pb;
			pf[6] = (float)(int)((uint32_t)(b >> 4) << 0x1c) * fVar3 + pf[4] * fVar2 + pf[5] * fVar1;
			pf[7] = (pf[5] * fVar2 + pf[6] * fVar1) + (float)(int)((uint32_t)b << 0x1c) * fVar3;
			b = pb[nch];
			pb += nch * 2;
			pf[8] = (float)(int)((uint32_t)(b >> 4) << 0x1c) * fVar3 + pf[6] * fVar2 + pf[7] * fVar1;
			pf[9] = (pf[7] * fVar2 + pf[8] * fVar1) + (float)(int)((uint32_t)b << 0x1c) * fVar3;
			pf += 10;
		}
	}
	*(int*)(c + 0x38) -= 0x20;
	*(int*)(c + 0x34) += nch * 0x13;
	return 0x20;
}

// ---------------------------------------------------------------------------
// @ 0x01134700  Pcm16Big decoder create event
// ---------------------------------------------------------------------------
bool __cdecl FUN_01134700(int p)
{
	*(int*)(p + 0x34) = 0;
	*(int*)(p + 0x38) = 0;
	return true;
}

// ---------------------------------------------------------------------------
// @ 0x01134740  big-endian 16-bit samples -> float
// ---------------------------------------------------------------------------
void __cdecl FUN_01134740(int a, int b, uint16_t* s, float* out, int stride)
{
	if (a >= b)
		return;
	for (int i = a; i < b; i++)
	{
		uint16_t v = *s;
		v = (uint16_t)((v >> 8) | (v << 8));
		out[i] = (float)(int)(int16_t)v * kPcmScale;
		s += stride;
	}
}

// ---------------------------------------------------------------------------
// @ 0x01134880  unrolled big-endian 16-bit -> float
// ---------------------------------------------------------------------------
void __cdecl FUN_01134880(int count, uint16_t* s, float* out, int stride)
{
	uint16_t* s0 = s;
	float* o0 = out;
	int i = count;
	for (; i >= 8; i -= 8)
	{
		out[0] = (float)(int)(int16_t)(uint16_t)((s[0] >> 8) | (s[0] << 8)) * kPcmScale;
		out[1] = (float)(int)(int16_t)(uint16_t)((s[stride] >> 8) | (s[stride] << 8)) * kPcmScale;
		out[2] = (float)(int)(int16_t)(uint16_t)((s[stride * 2] >> 8) | (s[stride * 2] << 8)) * kPcmScale;
		out[3] = (float)(int)(int16_t)(uint16_t)((s[stride * 3] >> 8) | (s[stride * 3] << 8)) * kPcmScale;
		out[4] = (float)(int)(int16_t)(uint16_t)((s[stride * 4] >> 8) | (s[stride * 4] << 8)) * kPcmScale;
		out[5] = (float)(int)(int16_t)(uint16_t)((s[stride * 5] >> 8) | (s[stride * 5] << 8)) * kPcmScale;
		out[6] = (float)(int)(int16_t)(uint16_t)((s[stride * 6] >> 8) | (s[stride * 6] << 8)) * kPcmScale;
		out[7] = (float)(int)(int16_t)(uint16_t)((s[stride * 7] >> 8) | (s[stride * 7] << 8)) * kPcmScale;
		s += stride * 8;
		out += 8;
	}
	FUN_01134740(count - i, count, s0 + (count - i) * stride, o0, stride);
}

// ---------------------------------------------------------------------------
// @ 0x011349a0  Pcm16Big decode block
// ---------------------------------------------------------------------------
void __cdecl FUN_011349a0(int c, int param_2, int param_3)
{
	if (*(int*)(c + 0x38) < 1)
	{
		int* blk = (int*)(*(int*)(c + 0x24) + (uint32_t)*(uint8_t*)(c + 0x30) * 0x14 + c);
		if (blk[3] == 0)
		{
			blk = 0;
		}
		else
		{
			(*(uint8_t*)(c + 0x30))++;
			if (*(uint8_t*)(c + 0x32) <= *(uint8_t*)(c + 0x30))
				*(uint8_t*)(c + 0x30) = 0;
		}
		if (*(char*)((char*)blk + 0x10) == 0)
		{
			*(int*)(c + 0x34) = 0;
			*(int*)(c + 0x38) = 0;
		}
		*(int*)(c + 0x34) = blk[0];
		int len = blk[3];
		*(int*)(c + 0x38) = len;
		if (blk[2] != 0)
		{
			*(int*)(c + 0x38) = len - blk[2];
			*(int*)(c + 0x34) += (uint32_t)*(uint8_t*)(c + 0x2e) * blk[2] * 2;
		}
	}
	uint32_t nch = *(uint8_t*)(c + 0x2e);
	for (uint32_t ch = 0; ch < nch; ch++)
		FUN_01134880(param_3, (uint16_t*)(*(int*)(c + 0x34) + ch * 2),
		             (float*)(*(int*)(param_2 + 4) + *(uint16_t*)(param_2 + 0xe) * ch * 4), nch);
	*(int*)(c + 0x38) -= param_3;
	*(int*)(c + 0x34) += nch * param_3 * 2;
}

// ---------------------------------------------------------------------------
// @ 0x01134a60  read param_2 bits from the bit reader
// ---------------------------------------------------------------------------
unsigned BitReader::FUN_01134a60(int n)
{
	int r = (int)this;
	while (*(int*)(r + 0x30) < n)
	{
		uint8_t b = **(uint8_t**)(r + 0x20);
		int cnt = *(int*)(r + 0x30) + 8;
		*(int*)(r + 0x20) = *(int*)(r + 0x20) + 1;
		*(uint32_t*)(r + 0x2c) |= (uint32_t)b << (0x18 - (char)*(int*)(r + 0x30) & 0x1f);
		*(int*)(r + 0x30) = cnt;
	}
	uint32_t v = *(uint32_t*)(r + 0x2c);
	*(int*)(r + 0x30) = *(int*)(r + 0x30) - n;
	*(uint32_t*)(r + 0x2c) = v << ((uint8_t)n & 0x1f);
	return v >> ((0x20 - (uint8_t)n) & 0x1f);
}

// ---------------------------------------------------------------------------
// @ 0x01134ae0
// ---------------------------------------------------------------------------
void __cdecl FUN_01134ae0(int* p)
{
	void (__stdcall* f)(int) = *(void (__stdcall**)(int))(*p + 4);
	f(0);
	volatile int barrier = 0;
	(void)barrier;
}
