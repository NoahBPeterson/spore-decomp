// Slice s008c4030 -- Adobe T2K (Type2K) font-stream readers from psread.c, linked into
// SporeApp.exe.  These decode the embedded EA/postscript font descriptors:
//
//   008c4030  New_ebscClass        read the bitmap/substitute metrics table (indexed by 0x1c)
//   008c44d0  ReadBigMetrics       read 8 display-metric bytes into a short[8]
//   008c4a00  ReadSmallMetrics     read 5 display-metric bytes into a short[5]
//   008c4d50  FintBestSubstitute   nearest (x,y) match in the substitute table (ret int)
//   008c4dc0  FindBitmapSizeTable  look up a size entry, falling back to the substitute table
//
// Every byte is pulled through one inlined T2K_INPUT_STREAM "read one byte" sequence that has
// three arms: a direct buffer pointer, an indirect (block/fn) copy, or a refill via
// PrimeT2KInputStream.  T2K_INPUT_STREAM retail offsets:
//   +0x000  block            (non-zero -> use the fn arm; zero -> memory arm)
//   +0x004  readFn           (T2K_READ_FUNC)
//   +0x008  clientData
//   +0x00c  tmp              (1-byte scratch the fn arm fills)
//   +0x214  size             +0x218 offset   +0x21c pos   +0x22c error
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed char    s8;

// ---------------------------------------------------------------- the T2K input stream
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

// ---------------------------------------------------------------- external helpers
extern "C" int   ReadInt32(T2K_Stream* s);                  // 0x008cc0f0  big-endian 32-bit
extern "C" void* tsi_AllocMem(void* mem, u32 size);         // 0x008d1260
extern "C" void  PrimeT2KInputStream(T2K_Stream* s);        // 0x008cc0b0
extern "C" void  tsi_Error(u32 err, u32 code);              // 0x008d10c0

// A structural copy of the entry struct returned by New_ebscClass (0x14 bytes).
struct EBSC
{
	void* mem;        // +0x00
	u32   unk04;      // +0x04
	u32   tag;        // +0x08  the 0x20000|N id
	u32   count;      // +0x0c
	u8*   data;       // +0x10  the count-record table (0x1c bytes each)
};

// A display-metrics block (glyph bounding box + advance + bearing).
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

// One record of the bitmap-size / substitute table (0x38 bytes).
struct SizeEntry
{
	u32  unk00[0x30 / 4];
	u8   x;        // +0x30
	u8   y;        // +0x31
	u8   z;        // +0x32
	u8   pad[0x38 - 0x33];
};

// ---------------------------------------------------------------- the inlined byte reader
// One byte from the stream; the original inlines this everywhere, so keep it __forceinline.
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

// =====================================================================================
// @ 0x008c4030  New_ebscClass
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

// =====================================================================================
// @ 0x008c44d0  ReadBigMetrics
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

// =====================================================================================
// @ 0x008c4a00  ReadSmallMetrics
void ReadSmallMetrics(T2K_Stream* s, T2K_Metrics* m)
{
	m->height   = ReadByte(s);
	m->width    = ReadByte(s);
	m->bearingX = (signed char)ReadByte(s);
	m->bearingY = (signed char)ReadByte(s);
	m->advance  = ReadByte(s);
}

// =====================================================================================
// @ 0x008c4d50  FintBestSubstitute
// retail ABI: self in ecx, x,y on the stack, caller cleans (ret); modelled as fastcall + dummy.
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

// =====================================================================================
// @ 0x008c4dc0  FindBitmapSizeTable
// x arrives in eax, y in ecx (retail register ABI); subtable ptr and out are stack args.
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
