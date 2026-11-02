// src/game/UTFSpore_Win32/t2ksbit.cpp -- migrated from slice(s) s008c6e80, s008c63a0, s008c4f40, s008c4030, s008c3120 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/t2ksbit.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>

// ---- items of slice s008c3120 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short ushort;
void  __cdecl tsi_DeAllocMem(int heap, void* p);                    // 0x008d1440
int   __cdecl Tell_InputStream(void* stream);                       // 0x008cc5b0
int   __cdecl ReadInt32(void* stream);                              // 0x008cc0f0
short __cdecl ReadInt16(void* stream);                              // 0x008cc190
void  __cdecl Seek_InputStream(void* stream, int pos);              // 0x008cc580
// ---- items of slice s008c3120 end

// ---- items of slice s008c4030 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
struct T2K_Stream
{
	u8*  block;        // +0x000
	int  readFn;       // +0x004
	u8*  clientData;   // +0x008
	u8   tmp;          // +0x00c
	u8   pad[0x20c - 0x0d];
	u32  size;         // +0x214
	u32  offset;       // +0x218
	u32  pos;          // +0x21c
	u8   pad2[0x22c - 0x220];
	u32  error;        // +0x22c
};
extern "C" void* tsi_AllocMem(void* mem, u32 size);         // 0x008d1260
extern "C" void  PrimeT2KInputStream(T2K_Stream* s);        // 0x008cc0b0
extern "C" void  tsi_Error(u32 err, u32 code);              // 0x008d10c0
struct EBSC
{
	void* mem;        // +0x00
	u32   unk04;      // +0x04
	u32   tag;        // +0x08  the 0x20000|N id
	u32   count;      // +0x0c
	u8*   data;       // +0x10  the count-record table (0x1c bytes each)
};
struct T2K_Metrics
{
	u16 height;    // [0]
	u16 width;     // [1]
	short bearingX;// [2]
	short bearingY;// [3]
	u16 advance;   // [4]
	short italicX; // [5]
	short italicY; // [6]
	u16 flags;     // [7]
};
__forceinline u8 ReadByte(T2K_Stream* s)
{
	if (s->block == 0) {
		u32 pos = s->pos;
		s->pos = pos + 1;
		int r = ((int(__cdecl*)(u8*, u8*, u32, u32))s->readFn)(s->clientData, &s->tmp, pos, 1);
		if (r < 0) {
			tsi_Error(s->error, 0x2728);
			return 0;
		}
		return s->tmp;
	}
	if (s->readFn == 0) {
		u8 b = s->block[s->pos];
		s->pos = s->pos + 1;
		return b;
	}
	if (s->size < (s->pos - s->offset) + 1)
		PrimeT2KInputStream(s);
	u8 b = s->block[(s->pos - s->offset)];
	s->pos = s->pos + 1;
	return b;
}
// ---- items of slice s008c4030 end

// ---- items of slice s008c4f40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef signed char    s8;
struct indexSubHeader          // 0x08
{
    u16 indexFormat;      // +0x00
    u16 imageFormat;      // +0x02
    u32 imageDataOffset;  // +0x04
};
struct indexSubTableArray      // 0x08
{
    u16 firstGlyphIndex;      // +0x00
    u16 lastGlyphIndex;       // +0x02
    indexSubHeader* indexSubTable; // +0x04
};
struct bigGlyphMetrics         // 0x10
{
    u16 height;        // +0x00
    u16 width;         // +0x02
    short horiBearingX;// +0x04
    short horiBearingY;// +0x06
    u16 horiAdvance;   // +0x08
    short vertBearingX;// +0x0a
    short vertBearingY;// +0x0c
    u16 vertAdvance;   // +0x0e
};
struct bitmapSizeTable         // 0x38
{
    u32  mem;                      // +0x00
    u32  indexSubTableArrayOffset; // +0x04
    u32  indexTableSize;           // +0x08
    u32  numberOfIndexSubTables;   // +0x0c
    u32  colorRef;                 // +0x10
    u8   hori[12];                 // +0x14
    u8   vert[12];                 // +0x20
    u16  startGlyphIndex;          // +0x2c
    u16  endGlyphIndex;            // +0x2e
    u8   ppemX;                    // +0x30
    u8   ppemY;                    // +0x31
    u8   bitDepth;                 // +0x32
    u8   flags;                    // +0x33
    indexSubTableArray* table;     // +0x34
};
struct blocClass               // 0x54
{
    u32 mem;                       // +0x00
    u32 startOffset;               // +0x04
    int fontIsSbitOnly;            // +0x08
    u32 requestedBitDepth;         // +0x0c
    u8  gInfo[0x34];               // +0x10  sbitGlypInfoData (unused here)
    u32 version;                   // +0x44
    u32 nTables;                   // +0x48
    bitmapSizeTable* table;        // +0x4c
    u8* cacheTables;               // +0x50
};
struct FontWideMetrics
{
    int   valid;  // +0x00
    short a;      // +0x04
    short b;      // +0x06
    short c;      // +0x08
    u16   d;      // +0x0a
    int   e;      // +0x0c
    int   f;      // +0x10
    short g;      // +0x14
    short h;      // +0x16
};
struct SbitSizeQuery          // 0x14
{
    u8  pad00[6];          // +0x00
    u16 glyphIndex;        // +0x06
    u16 ppemY;             // +0x08
    u16 substitutePpemX;   // +0x0a
    u16 substitutePpemY;   // +0x0c
};
struct SbitGlyphRecord
{
    u32  dataPtr;            // +0x00  bitmap data pointer (0 when absent)
    u16  glyphIndex;         // +0x04
    u8   pad06[8];           // +0x06
    u8   substituteBitDepth; // +0x0e
    u8   bitDepth;           // +0x0f
    u8   flags;              // +0x10
    u16  imageFormat;        // +0x12
    bigGlyphMetrics bigM;    // +0x14
};
struct codeOffsetPair
{
    u16 glyphCode; // +0x00
    u16 offset;    // +0x02
};
struct indexSubTable1            // index format 1 and 3, size 0x0c
{
    indexSubHeader header;       // +0x00
    u32* offsetArray;            // +0x08
};
struct indexSubTable2            // index format 2, size 0x1c
{
    indexSubHeader header;       // +0x00
    u32 imageSize;               // +0x08
    bigGlyphMetrics bigM;        // +0x0c
};
struct indexSubTable4            // index format 4, size 0x10
{
    indexSubHeader header;       // +0x00
    u32 numGlyphs;               // +0x08
    codeOffsetPair* glyphArray;  // +0x0c
};
struct indexSubTable5            // index format 5, size 0x24
{
    indexSubHeader header;       // +0x00
    u32 imageSize;               // +0x08
    bigGlyphMetrics bigM;        // +0x0c
    u32 numGlyphs;               // +0x1c
    u16* glyphArray;             // +0x20
};
namespace retail {
    int FindBitmapSizeTable(void* self, int xy, void* subtable, void* out); // 0x008c4dc0
}
__forceinline int ScaleMetric(int value, int num, int den)
{
    return (value * num + (den >> 1)) / den;
}
// ---- items of slice s008c4f40 end

// ---- items of slice s008c63a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int32_t int32;
struct bigGlyphMetrics_s008c_63a0 {
    uint16 height;         // +0x00
    uint16 width;          // +0x02
    int16  horiBearingX;   // +0x04
    int16  horiBearingY;   // +0x06
    uint16 horiAdvance;    // +0x08
    int16  vertBearingX;   // +0x0a
    int16  vertBearingY;   // +0x0c
    uint16 vertAdvance;    // +0x0e
};
struct SbitGlyphInfo {           // sbitGlypInfoData, 0x34
    uint32 dataOffset;           // +0x00
    uint16 glyphIndex;           // +0x04
    uint16 ppemX;                // +0x06
    uint16 ppemY;                // +0x08
    uint16 substitutePpemX;      // +0x0a
    uint16 substitutePpemY;      // +0x0c
    uint8  substituteBitDepth;   // +0x0e
    uint8  bitDepth;             // +0x0f
    uint8  flags;                // +0x10
    uint8  pad11;                // +0x11
    uint16 imageFormat;          // +0x12
    bigGlyphMetrics_s008c_63a0 bigM;        // +0x14
    int32  smallMetricsUsed;     // +0x24
    uint32 rowBytes;             // +0x28
    uint8* baseAddr;             // +0x2c
    uint32 bitmapSize;           // +0x30
};
// ---- items of slice s008c63a0 end

// ---- items of slice s008c6e80 begin (TODO(rewrite): local stubs, replace by canonical classes)
void FUN_008c75f0();                                        // 0x008C75F0
void FUN_008c6e80();                                        // 0x008C6E80
// ---- items of slice s008c6e80 end

// @ 0x008c3ec0
int memForSubIndexTable(void* stream)
{
	int size   = 0;
	int start  = Tell_InputStream(stream);
	ReadInt32(stream);
	ReadInt32(stream);
	int count  = ReadInt32(stream);
	ReadInt32(stream);

	Seek_InputStream(stream, start + 0x30);

	while (count > 0)
	{
		ushort lo   = (ushort)ReadInt16(stream);
		ushort hi   = (ushort)ReadInt16(stream);
		int    skip = ReadInt32(stream);
		Seek_InputStream(stream, start + skip);

		int type = ReadInt16(stream) - 1;
		switch (type)
		{
		case 0:
		case 2:
			size += 0x10 + (hi - lo) * 4;
			break;
		case 1:
			size += 0x1c;
			break;
		case 3:
			size += 0x10 + ((ReadInt32(stream) * 4 + 3) & ~3);
			break;
		case 4:
			size += 0x24 + ((ReadInt32(stream) * 2 + 3) & ~3);
			break;
		default:
			break;
		}

		Seek_InputStream(stream, start + 8);
		--count;
	}

	Seek_InputStream(stream, start);
	return size;
}

// @ 0x008c4000
void Delete_blocClass(int* p)
{
	if (p == 0)
		return;
	tsi_DeAllocMem(p[0], (void*)p[0xf]);
	tsi_DeAllocMem(p[0], (void*)p[0x14]);
	tsi_DeAllocMem(p[0], p);
}

// @ 0x008c4030
EBSC* FUN_008c4030(void* mem, T2K_Stream* s)
{
	int tag = ReadInt32(s);
	if ((u32)(tag - 0x20000) > 0xffff)
		return 0;

	EBSC* e = (EBSC*)tsi_AllocMem(mem, 0x14);
	e->mem = mem;
	e->tag = tag;

	int count = ReadInt32(s);
	e->count = count;
	e->data = (u8*)tsi_AllocMem(mem, count * 0x1c);

	for (int i = 0; i < count; ++i) {
		u8* rec = e->data + i * 0x1c;
		for (int j = 0; j < 0xc; ++j)
			rec[j] = ReadByte(s);
		for (int j = 0; j < 0xc; ++j)
			rec[0xc + j] = ReadByte(s);
		rec[0x18] = ReadByte(s);
		rec[0x19] = ReadByte(s);
		rec[0x1a] = ReadByte(s);
		rec[0x1b] = ReadByte(s);
	}
	return e;
}

// @ 0x008c44d0
void ReadBigMetrics(T2K_Stream* s, T2K_Metrics* m)
{
	m->height   = ReadByte(s);
	m->width    = ReadByte(s);
	m->bearingX = (signed char)ReadByte(s);
	m->bearingY = (signed char)ReadByte(s);
	m->advance  = ReadByte(s);
	m->italicX  = (signed char)ReadByte(s);
	m->italicY  = (signed char)ReadByte(s);
	m->flags    = ReadByte(s);
}

// @ 0x008c4a00
void ReadSmallMetrics(T2K_Stream* s, T2K_Metrics* m)
{
	m->height   = ReadByte(s);
	m->width    = ReadByte(s);
	m->bearingX = (signed char)ReadByte(s);
	m->bearingY = (signed char)ReadByte(s);
	m->advance  = ReadByte(s);
}

// @ 0x008c4d50
int __fastcall FintBestSubstitute(void* selfv, void* /*edx*/, int x, int y)
{
	char* self = (char*)selfv;
	int   best = 0x7fffffff;
	int   bestIdx = -1;
	int   count = *(int*)(self + 0x48);
	u8*   table = *(u8**)(self + 0x4c);

	if (count <= 0)
		return bestIdx;

	u8* p = table + 0x31;
	for (int i = 0; i < count; ++i) {
		int dx = (int)p[-1] - x;
		if (dx < 0)
			dx = -dx * 4;
		int dy = (int)p[0] - y;
		if (dy < 0)
			dy = -dy * 4;
		int d = dx + dy;
		if (d < best) {
			best = d;
			bestIdx = i;
		}
		p += 0x38;
	}
	return bestIdx;
}

// @ 0x008c4dc0
int FindBitmapSizeTable(void* selfv, int xy, void* subtable, void* out)
{
	char* self = (char*)selfv;
	int   x = (u16)xy;
	int   y = (u16)(xy >> 16);
	void* sub = subtable;
	short* res = (short*)out;

	int count = *(int*)(self + 0x48);
	int found = 0;

	res[3] = (short)x;   // +6
	res[4] = (short)y;   // +8
	res[5] = (short)x;   // +0xa
	res[6] = (short)y;   // +0xc

	for (;;) {
		if (count > 0) {
			u8* table = *(u8**)(self + 0x4c);
			int mask = *(int*)(self + 0xc);
			for (int i = 0; i < count; ++i) {
				u8* p = table + i * 0x38;
				if (mask != 0) {
					if (p[0x30] == x && p[0x31] == y && p[0x32] == mask) {
						found = (int)p;
						if (found != 0)
							return found;
						break;
					}
				} else {
					if (p[0x30] == x && p[0x31] == y) {
						found = (int)p;
						if (found != 0)
							return found;
						break;
					}
				}
			}
		}

		if (*(int*)(self + 0xc) != 0)
			return found;

		if (sub != 0) {
			char* s = (char*)sub;
			int n = *(int*)(s + 0xc);
			int i = 0;
			if (n > 0) {
				u8* q = *(u8**)(s + 0x10) + 0x19;
				while (q[-1] != x || q[0] != y) {
					++i;
					q += 0x1c;
					if (n <= i)
						goto fallback;
				}
				u8* qq = *(u8**)(s + 0x10) + i * 0x1c;
				res[5] = qq[0x1a];
				res[6] = qq[0x1b];
				y = (u8)res[6];
				x = (u8)res[5];
				sub = 0;
				continue;
			}
		}

	fallback:
		if (*(int*)(self + 8) != 0) {
			int idx = FintBestSubstitute(self, 0, x, y);
			if (idx >= 0) {
				u8* table = *(u8**)(self + 0x4c);
				u8* r = table + idx * 0x38;
				res[5] = r[0x30];
				res[6] = r[0x31];
				return (int)r;
			}
		}
		return found;
	}
}

// @ 0x008c4f40
void GetFontWideSbitMetrics(void* self, void* subtable, int yppem, int xppem, FontWideMetrics* hor, FontWideMetrics* ver)
{
    SbitSizeQuery siz;
    bitmapSizeTable* t = (bitmapSizeTable*)retail::FindBitmapSizeTable(self, xppem, subtable, &siz);
    if (t == 0) {
        hor->valid = 0;
        ver->valid = 0;
        return;
    }

    int subX = siz.substitutePpemX;   // +0x0a
    int subY = siz.substitutePpemY;   // +0x0c

    // ---- horizontal block (hori[0..4] = advance, bearingY, width, bearingX, row)
    hor->valid = 1;
    hor->a = (short)ScaleMetric((s8)t->hori[0], xppem, subY);
    hor->b = (short)ScaleMetric((s8)t->hori[1], xppem, subY);
    hor->c = 0;
    hor->d = (u16)ScaleMetric((u8)t->hori[2], yppem, subX);
    hor->f = ScaleMetric((s8)t->hori[3], yppem, subX);
    hor->e = ScaleMetric((s8)t->hori[4], xppem, subY);

    // Normalise the row/bit values: double both while they still fit in 16 bits.
    for (int i = 0; i < 16; ++i) {
        int e = hor->e;
        int f = hor->f;
        if (e >= 0x10000 || e <= -0x10000)
            break;
        if (f >= 0x10000 || f <= -0x10000)
            break;
        hor->e = e + e;
        hor->f = f + f;
    }

    // ---- vertical block (vert[0..4] = advance, bearingX, width, row, bearingY)
    ver->valid = 1;
    ver->a = (short)ScaleMetric((s8)t->vert[0], yppem, subX);
    ver->b = (short)ScaleMetric((s8)t->vert[1], yppem, subX);
    ver->c = 0;
    ver->d = (u16)ScaleMetric((u8)t->vert[2], xppem, subY);
    ver->f = ScaleMetric((s8)t->vert[4], yppem, subX);
    ver->e = ScaleMetric((s8)t->vert[3], xppem, subY);

    for (int i = 0; i < 16; ++i) {
        int e = ver->e;
        int f = ver->f;
        if (e >= 0x10000 || e <= -0x10000)
            break;
        if (f >= 0x10000 || f <= -0x10000)
            break;
        ver->e = e + e;
        ver->f = f + f;
    }

    // A negative "bearing" marker in hori[9] flips the vertical bearings.
    if (hor->b > 0 && (s8)t->hori[9] < 0) {
        hor->b = (short)-hor->b;
        ver->b = (short)-ver->b;
    }
}

// @ 0x008c5320
int FindGlyph_blocClass(blocClass* self, void* subtable, int yppem, u16 code, void* unused, SbitGlyphRecord* info, int xppem)
{
    bitmapSizeTable* t = (bitmapSizeTable*)retail::FindBitmapSizeTable(self, xppem, subtable, info);

    u32 data = 0;
    u16 imageFormat = 0;
    u8  bitDepth = 0;

    if (t == 0)
        goto done;
    if (code < t->startGlyphIndex || code > t->endGlyphIndex)
        goto done;

    {
        int nSub = (int)t->numberOfIndexSubTables;
        if (nSub <= 0)
            goto done;

        indexSubTableArray* arr = t->table;
        int i = 0;
        while (i < nSub) {
            if (code >= arr[i].firstGlyphIndex && code <= arr[i].lastGlyphIndex)
                break;
            ++i;
        }
        if (i >= nSub)
            goto done;

        {
            indexSubTableArray* sub = &arr[i];
            indexSubHeader* hdr = sub->indexSubTable;

            bitDepth = t->bitDepth;
            info->substituteBitDepth = t->bitDepth;
            info->bitDepth = t->bitDepth;
            info->flags = t->flags;
            imageFormat = hdr->imageFormat;

            int fmt = (int)hdr->indexFormat - 1;
            if ((u32)fmt > 4)
                goto done;

            switch (fmt) {
            case 0:   // index format 1
            case 2:   // index format 3 (same arm as 1)
            {
                indexSubTable1* h1 = (indexSubTable1*)hdr;
                data = h1->offsetArray[(u32)code - sub->firstGlyphIndex];
                break;
            }
            case 1:   // index format 2
            {
                indexSubTable2* h2 = (indexSubTable2*)hdr;
                data = ((u32)code - sub->firstGlyphIndex) * h2->imageSize
                       + hdr->imageDataOffset;
                info->bigM = h2->bigM;
                break;
            }
            case 3:   // index format 4 (code/offset pairs)
            {
                indexSubTable4* h4 = (indexSubTable4*)hdr;
                int numGlyphs = (int)h4->numGlyphs;
                codeOffsetPair* pairs = h4->glyphArray;
                int lo = 0;
                while (lo < numGlyphs) {
                    if (pairs[lo].glyphCode == code) {
                        data = (u32)pairs[lo].offset + hdr->imageDataOffset;
                        break;
                    }
                    ++lo;
                }
                break;
            }
            case 4:   // index format 5 (sparse glyph index)
            {
                indexSubTable5* h5 = (indexSubTable5*)hdr;
                int numGlyphs = (int)h5->numGlyphs;
                u16* glyphs = h5->glyphArray;
                int lo = 0;
                while (lo < numGlyphs) {
                    if (glyphs[lo] == code) {
                        data = (u32)lo * h5->imageSize + hdr->imageDataOffset;
                        break;
                    }
                    ++lo;
                }
                break;
            }
            }
        }
    }

done:
    info->dataPtr = data;
    info->glyphIndex = code;
    info->imageFormat = imageFormat;
    (void)bitDepth;
    (void)yppem;
    (void)unused;
    (void)xppem;
    return data != 0 ? 1 : 0;
}

// @ 0x008c63a0
static __declspec(noinline) void MergeBits(SbitGlyphInfo* dst, SbitGlyphInfo* src, uint8 bitPos, uint8 rowOffset, uint8 mode)
{
    uint8* dstBase = dst->baseAddr;
    uint8* srcBase = src->baseAddr;
    int dstRowBytes = dst->rowBytes;
    int srcRowBytes = src->rowBytes;
    int dstWidth = dst->bigM.width;
    int srcWidth = src->bigM.width;

    if (dstBase == 0 || srcBase == 0)
        return;

    uint8* dstEnd = dstBase + dst->bigM.height * dstRowBytes;
    uint8* dstRow = dstBase + rowOffset * dstRowBytes;

    if (mode == 0) {
        int rows = src->bigM.height;
        if (rows <= 0)
            return;
        int startBit = bitPos;
        do {
            int bit = startBit;
            int x = 0;
            if (srcWidth > 0) {
                int acc = 0;
                do {
                    if (bit >= dstWidth)
                        break;
                    if ((x & 7) == 0)
                        acc = srcBase[x >> 3];
                    acc += acc;
                    if (acc & 0x100)
                        dstRow[bit >> 3] |= (uint8)(0x80 >> (bit & 7));
                    x++;
                    bit++;
                } while (x < srcWidth);
            }
            dstRow += dstRowBytes;
            srcBase += srcRowBytes;
            if (dstRow >= dstEnd)
                return;
            rows--;
        } while (rows > 0);
    } else {
        int rows = src->bigM.height;
        if (rows <= 0)
            return;
        int startBit = bitPos;
        uint8* s = srcBase - startBit;
        do {
            int x = 0;
            int p = startBit;
            if (srcWidth > 0) {
                do {
                    if (p >= dstWidth)
                        break;
                    uint8 v = s[p];
                    if (v != 0 && v > dstRow[p])
                        dstRow[p] = v;
                    x++;
                    p++;
                } while (x < srcWidth);
            }
            srcBase += srcRowBytes;
            s = srcBase - startBit;
            dstRow += dstRowBytes;
            if (dstRow >= dstEnd)
                return;
            rows--;
        } while (rows > 0);
    }
}

// @ 0x008c6500
static __declspec(noinline) void CopyRows(uint8* src, int srcRowBytes, uint8* dst, int oldSize, int newSize)
{
    int n = oldSize * newSize;
    int pos = oldSize >> 1;
    int step = newSize;
    uint8* s = src;
    uint8* d = dst;

    if (pos >= n)
        return;

    if (newSize > oldSize) {
        do {
            while (step < pos) {
                step += newSize;
                s += srcRowBytes;
            }
            if (srcRowBytes > 0) {
                for (int i = 0; i < srcRowBytes; i++)
                    d[i] = s[i];
            }
            pos += oldSize;
            d += srcRowBytes;
        } while (pos < n);
    } else {
        do {
            while (step < pos) {
                step += newSize;
                s += srcRowBytes;
            }
            if (srcRowBytes > 0) {
                for (int i = 0; i < srcRowBytes; i++)
                    d[i] = s[i];
            }
            pos += oldSize;
            d += srcRowBytes;
        } while (pos < n);
    }
}

// @ 0x008c65d0
static __declspec(noinline) void PackRows(int width, uint8* dst, int rows, uint8* src, int step, int srcRowBytes, int dstRowBytes, uint8 mode)
{
    for (int r = 0; r < rows; r++) {
        int x;
        if (mode == 0) {
            uint8 cur = *src;
            uint8 acc = 0;
            int bit = 0;
            int avail = width;
            int pos = step >> 1;
            for (x = 0; x < width; x++) {
                while (avail < pos) {
                    bit++;
                    avail += width;
                    cur += cur;
                    if ((bit & 7) == 0)
                        cur = src[bit >> 3];
                }
                if (cur & 0x80)
                    acc |= (uint8)(0x80 >> (x & 7));
                if ((x & 7) == 7) {
                    dst[x >> 3] = acc;
                    acc = 0;
                }
                pos += step;
            }
            if ((x & 7) != 0)
                dst[(x - 1) >> 3] = acc;
        } else {
            int srcRow = 0;
            int avail = width;
            int pos = step >> 1;
            for (x = 0; x < width; x++) {
                if (avail < pos) {
                    do {
                        srcRow++;
                        avail += width;
                    } while (avail < pos);
                }
                dst[x] = src[srcRow];
                pos += step;
            }
        }
        src += srcRowBytes;
        dst += dstRowBytes;
    }
}

// @ 0x008c6e80
void FUN_008c6e80()
{
}

// @ 0x008c75f0
void FUN_008c75f0()
{
}
