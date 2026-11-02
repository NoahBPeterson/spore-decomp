// src/game/UTFSpore_Win32/_at_008c0000.cpp -- migrated from slice(s) s008cb7f0, s008c3120 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_008c0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s008c3120 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  byte;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef byte* (__cdecl *AllocFn)(int, int);
void* __cdecl tsi_AllocMem(int heap, int size);                     // 0x008d1260
void  __cdecl FF_GetColorTable(void);                               // 0x008c20c0
// ---- items of slice s008c3120 end

// ---- items of slice s008cb7f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint8_t uint8;
typedef int16_t int16;
typedef int32_t int32;
struct tsiMemObject {
    uint8 pad00[0x54];
    void* base54;           // +0x54
    void* stream58;         // +0x58 (stream that owns +0x90)
    uint8 pad5c[0x8c - 0x5c];
    int32 flag8c;           // +0x8c
    int32 flag90;           // +0x90
};
extern "C" void tsi_DeAllocMem(tsiMemObject* mem, void* p);                                     // 0x008d1440
struct T2KMemHeader {                   // 0x14 bytes
    tsiMemObject* mem;                  // +0x00
    int16 flags04;                      // +0x04
    int16 flags06;                      // +0x06
    int16 value08;                      // +0x08
    int16 value0a;                      // +0x0a
    int16 value0c;                      // +0x0c
    int16 value0e;                      // +0x0e
    int16 value10;                      // +0x10
    int16 pad12;                        // +0x12
};
extern "C" void Delete_T2KMemHeader(T2KMemHeader* h);                                            // 0x008cc020
// ---- items of slice s008cb7f0 end

// @ 0x008c3580
void FUN_008c3580(int self)
{
	int width     = *(int*)(self + 0x10c);
	int colorTbl  = *(int*)(self + 0x110);
	int nTriples  = (width + 6) / 3;
	int tripleLen = nTriples * 3;

	*(int*)(self + 0xe4) = (*(int*)(self + 0xe4) - 0x7f) / 3;
	*(int*)(self + 0x100) = (*(int*)(self + 0x100) - 0x7f) / 3;
	*(int*)(self + 0x114) = nTriples;
	*(int*)(self + 0x10c) = nTriples;

	int allocSize = *(int*)(self + 0x118) == 0 ? 0 : nTriples * colorTbl;

	int owned = 0;
	byte* pixels = 0;
	AllocFn allocator = *(AllocFn*)(self + 0x24);
	if (allocator != 0)
		pixels = allocator(*(int*)(self + 0x20), allocSize);
	if (pixels == 0)
	{
		pixels = (byte*)tsi_AllocMem(*(int*)(self + 4), allocSize);
		owned = 1;
	}

	if (allocSize != 0)
	{
		byte localTmp[128];
		byte* tmp;
		if (tripleLen <= 0x80)
			tmp = localTmp;
		else
			tmp = (byte*)tsi_AllocMem(*(int*)(self + 4), tripleLen);

		byte* src = (byte*)*(int*)(self + 0x118);
		FF_GetColorTable();

		if (colorTbl > 0)
		{
			int   delta = (int)src - (int)tmp;
			byte* rowSrc = src + 1;
			byte* rowDst = pixels;
			int   rows = colorTbl;
			do
			{
				tmp[0] = 0;
				tmp[1] = 0;
				tmp[2] = 0;
				int i = 1;
				while (i < width - 2)
				{
					uint lo = rowSrc[i - 1];
					if ((uint)rowSrc[i] < lo)
						lo = rowSrc[i];
					uint hi = rowSrc[i + 1];
					if (hi < lo)
						lo = hi;
					if (lo > 10)
					{
						int  v = lo * 0x186 + 0xc;
						char c = (char)(v >> 0xc);
						tmp[i + 2] = c;
						tmp[i + 3] = c;
						tmp[i + 4] = c;
						int d = (c * 5 + (c >> 1) * 2);
						rowSrc[i - 1] -= (char)d;
						rowSrc[i]     -= (char)d;
						rowSrc[i + 1] -= (char)d;
					}
					else
					{
						tmp[i + 2] = 0;
						tmp[i + 3] = 0;
						tmp[i + 4] = 0;
					}
					i += 3;
				}
				(void)delta;
				(void)rowDst;
			} while (--rows != 0);
		}
		(void)owned;
	}
}

// @ 0x008c39a0
void FUN_008c39a0(int self, ushort mode)
{
	int width     = *(int*)(self + 0x10c);
	int colorTbl  = *(int*)(self + 0x110);
	int nTriples  = (colorTbl + 6) / 3;
	int tripleLen = nTriples * 3;

	*(uint*)(self + 0xe0) =
		(*(int*)(self + 0xe0) - colorTbl * 0x40 - 0x7f) / 3 - 0x20 + nTriples * 0x40 & 0xffffffc0;
	*(uint*)(self + 0xfc) =
		(*(int*)(self + 0xfc) - colorTbl * 0x40 - 0x7f) / 3 - 0x20 + nTriples * 0x40 & 0xffffffc0;

	int widthOut = width;
	if (colorTbl == 0 && width == 0)
	{
		nTriples = 0;
		widthOut = 1;
	}
	*(int*)(self + 0x114) = widthOut;
	*(int*)(self + 0x110) = nTriples;
	*(int*)(self + 0x10c) = widthOut;

	int allocSize = *(int*)(self + 0x118) == 0 ? 0 : widthOut * nTriples;

	int owned = 0;
	byte* pixels = 0;
	AllocFn allocator = *(AllocFn*)(self + 0x24);
	if (allocator != 0)
		pixels = allocator(*(int*)(self + 0x20), allocSize);
	if (pixels == 0)
	{
		pixels = (byte*)tsi_AllocMem(*(int*)(self + 4), allocSize);
		owned = 1;
	}

	if (allocSize != 0)
	{
		byte localTmp[128];
		byte* tmp;
		if (tripleLen < 0x81)
			tmp = localTmp;
		else
			tmp = (byte*)tsi_AllocMem(*(int*)(self + 4), tripleLen);

		byte* src = (byte*)*(int*)(self + 0x118);
		FF_GetColorTable();

		if (widthOut > 0)
		{
			int   delta = (int)src - (int)tmp;
			byte* rowSrc = src + 1;
			byte* rowDst = pixels;
			int   rows = widthOut;
			do
			{
				tmp[0] = 0;
				tmp[1] = 0;
				tmp[2] = 0;
				int i = 1;
				while (i < nTriples - 2)
				{
					uint lo = rowSrc[i - 1];
					if ((uint)rowSrc[i] < lo)
						lo = rowSrc[i];
					uint hi = rowSrc[i + 1];
					if (hi < lo)
						lo = hi;
					if (lo < 0xb)
					{
						tmp[i + 2] = 0;
						tmp[i + 3] = 0;
						tmp[i + 4] = 0;
					}
					else
					{
						int  v = lo * 0x186 + 0xc;
						char c = (char)(v >> 0xc);
						tmp[i + 2] = c;
						tmp[i + 3] = c;
						tmp[i + 4] = c;
						c = (char)(v >> 0xd) + c * '\n';
						rowSrc[i - 1] -= c;
						rowSrc[i]     -= c;
						rowSrc[i + 1] -= c;
					}
					i += 3;
				}
				(void)delta;
				(void)rowDst;
			} while (--rows != 0);
		}
		(void)owned;
	}
	(void)mode;
}

// @ 0x008cc020
void Delete_T2KMemHeader(T2KMemHeader* h)
{
    if (h != 0)
        tsi_DeAllocMem(h->mem, h);
}
