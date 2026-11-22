// src/game/UTFSpore_Win32/_at_008c0000.cpp -- migrated from slice(s) s008caba0, s008cb7f0, s008c3120 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_008c0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s008c3120 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  byte;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef byte* (__cdecl *AllocFn)(int, int);
extern "C" void* __cdecl tsi_AllocMem(int heap, int size);                     // 0x008d1260
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

// ---- items of slice s008caba0 begin (TODO(rewrite): local stubs, replace by canonical classes)
/* Slice s008caba0 -- T2K / Font Fusion (module "EA-UTF"): glyph stroking + hint application.
 *
 * COMPILE AS C: "/O2 /MD /Gy /TC /GS-"   (T2K is C, like s008bb550 / s008bdb70 / s008be260).
 * The retail binary was built with LTCG, so several of these routines take arguments in
 * caller-saved registers rather than on the stack; they are written here with those values as
 * ordinary leading/extra parameters and cannot be byte-exact from a single /O2 TU (see
 * nonmatching.txt).
 *
 * 008caba0 glyph_StrokeCtr            stroke one contour of a glyph (source glyph arrives in EDI)
 * 008cae30 ApplyHintsToStrokeGlyph    snap the x then y coordinates to the pixel grid (5th arg in EAX)
 * 008cb070 ff_glyph_StrokeGlyph       stroke a whole glyph into a freshly allocated GlyphClass
 * 008cb1b0 ff_Read2Numbers            bit-packed 2-number stream decoder
 * 008cb2e0 ff_Read4Numbers            bit-packed 4-number stream decoder
 * 008cb450 ReadLowUnsignedNumber      0xf0-prefixed 4-bits-per-byte variable-length number
 * 008cb520 AllocatePointSpaceIfNeeded grow the point arrays and copy the old points (glyph in ECX, count in EAX)
 * 008cb5e0 GetGlyphStream             open a sub-stream over one glyph's data (font in ESI)
 * 008cb6b0 Read_PreferredMappingTable decode the "preferred mapping" cmap sub-table
 * 008cb790 MapCodeToGlyph             binary search of a decoded mapping table
 */

typedef unsigned char uint8_s008c_aba0;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;
typedef int int32_s008c_aba0;
typedef struct tsiMemObject_s008c_aba0 {
    uint8_s008c_aba0 pad00[0x54];
    void* base54;           // +0x54
    uint8_s008c_aba0 pad58[0x8c - 0x58];
    int32_s008c_aba0 flag8c;           // +0x8c
} tsiMemObject_s008c_aba0;
typedef int (*PF_READ_TO_RAM)(void* id, uint8_s008c_aba0* dest, int32_s008c_aba0 offset, int32_s008c_aba0 numBytes);
typedef struct InputStream {
    uint8_s008c_aba0* privateBase;            // +0x000
    PF_READ_TO_RAM ReadToRamFunc;  // +0x004
    void* nonRamID;                // +0x008
    uint8_s008c_aba0 tmp_ch[0x208];           // +0x00c
    uint32 cacheCount;             // +0x214
    uint32 posZero;                // +0x218
    uint32 pos;                    // +0x21c
    uint32 pad220[3];              // +0x220
    tsiMemObject_s008c_aba0* mem;             // +0x22c
} InputStream;
typedef struct MappingTable {
    tsiMemObject_s008c_aba0* mem;   // +0x00
    uint32 version;      // +0x04
    int32_s008c_aba0 count;         // +0x08
    uint16 field0c;      // +0x0c
    uint16 field0e;      // +0x0e
    uint16* keys;        // +0x10
    uint16* values;      // +0x14
} MappingTable;
extern "C" int32_s008c_aba0 ReadInt32(InputStream* in);                                     // 0x008cc0f0
extern "C" int16 ReadInt16(InputStream* in);                                     // 0x008cc190
// ---- items of slice s008caba0 end

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

// @ 0x008cb6b0
// T2K is C (the slice compiles /TC), so the definition keeps C linkage: manifest symbol _FUN_008cb6b0.
extern "C" MappingTable* FUN_008cb6b0(tsiMemObject_s008c_aba0* mem, InputStream* in)
{
    int n = 0;
    MappingTable* t = 0;
    uint32 version = ReadInt32(in);
    int i;
    if (version - 0x10000 <= 0xffff) {
        t = (MappingTable*)tsi_AllocMem((int)mem, 0x18);
        t->mem = mem;
        t->version = version;
        n = ReadInt32(in);
        t->count = n;
        t->keys = (uint16*)tsi_AllocMem((int)mem, n * 4);
        t->values = t->keys + n;
        t->field0c = ReadInt16(in);
        t->field0e = ReadInt16(in);
        for (i = 0; i < n; i++)
            t->keys[i] = ReadInt16(in);
        for (i = 0; i < n; i++)
            t->values[i] = ReadInt16(in);
    }
    t->field0c = (uint16)(t->field0c << 3);
    for (i = 0; i < n; i++)
        t->values[i] = (uint16)(t->values[i] << 3);
    return t;
}

// @ 0x008cb790
// T2K is C (the slice compiles /TC), so the definition keeps C linkage: manifest symbol _FUN_008cb790.
extern "C" uint16 FUN_008cb790(MappingTable* t, uint16 code)
{
    uint16 def = t->field0c;
    int lo = 0;
    int hi = t->count - 1;
    do {
        int mid = (hi + lo) >> 1;
        uint16 v = t->keys[mid];
        if (code > v) {
            lo = mid + 1;
        } else if (code >= v) {
            def = t->values[mid];
            break;
        } else {
            hi = mid - 1;
        }
    } while (hi >= lo);
    return def;
}

// @ 0x008cc020
void Delete_T2KMemHeader(T2KMemHeader* h)
{
    if (h != 0)
        tsi_DeAllocMem(h->mem, h);
}
