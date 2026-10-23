// s008c3120 -- T2K thumbnail/CLUT pixel writers and CLUT-table helpers.
// Rebuilt from the shipped PE.  The writer functions operate on a large
// engine object addressed through fixed offsets; those offsets are kept as
// literals.  In the original binary the object pointer is threaded through
// ESI by a private convention; here it is modelled as an explicit parameter.

typedef unsigned char  byte;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef byte* (__cdecl *AllocFn)(int, int);

// ---------------------------------------------------------------------------
// engine helpers used by this module
// ---------------------------------------------------------------------------
void* __cdecl tsi_AllocMem(int heap, int size);                     // 0x008d1260
void  __cdecl tsi_DeAllocMem(int heap, void* p);                    // 0x008d1440
void  __cdecl FF_GetColorTable(void);                               // 0x008c20c0
int   __cdecl Tell_InputStream(void* stream);                       // 0x008cc5b0
int   __cdecl ReadInt32(void* stream);                              // 0x008cc0f0
short __cdecl ReadInt16(void* stream);                              // 0x008cc190
void  __cdecl Seek_InputStream(void* stream, int pos);              // 0x008cc580

// The colour-ramp tables live in .rdata; DAT_01435764 is the base ramp and
// DAT_0143579c is the alternate ramp selected for the third channel.
extern "C" const byte DAT_01435764[];                               // 0x01435764
extern "C" const byte DAT_0143579c[];                               // 0x0143579c

// ---------------------------------------------------------------------------
// FUN_008c3120 -- write the 8-bit-CLUT gray output
// @ 0x008c3120
void FUN_008c3120(int self)
{
	int   colorTable = *(int*)(self + 0x110);
	int   rowPitch   = *(int*)(self + 0x114);
	int   width      = *(int*)(self + 0x10c);
	int   nTriples   = (width + 6) / 3;
	int   tripleLen  = nTriples * 3;
	int   padOffset  = (tripleLen - width - 4) * 0x20;
	int   height;

	*(int*)(self + 0xe4) -= 0x80;

	height = (*(int*)(self + 0xe4) + 1 + padOffset) / 3;
	*(int*)(self + 0x100) = (padOffset - 0x7f + *(int*)(self + 0x100)) / 3;
	*(int*)(self + 0xd8) = (*(int*)(self + 0xd8) + 1) / 3;
	*(int*)(self + 0xec) = (*(int*)(self + 0xec) + 1) / 3;
	*(int*)(self + 0xf4) = (*(int*)(self + 0xf4) + 1) / 3;

	uint base = (*(int*)(self + 0xd0) + 1) / 3 + 0x8000;

	byte* tmp = 0;
	*(int*)(self + 0xe4) = height;
	*(uint*)(self + 0xd0) = base & 0xffff0000;

	if (height >> 6 >= 0 && (int)(base >> 16) <= (height >> 6) + nTriples)
		*(int*)(self + 0xe4) = height - 0x40;

	*(int*)(self + 0x114) = nTriples;
	*(int*)(self + 0x10c) = nTriples;

	int allocSize;
	if (*(int*)(self + 0x118) == 0)
		allocSize = 0;
	else
		allocSize = nTriples * colorTable;

	int owned = 0;
	byte* pixels  = 0;
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
		if (tripleLen < 0x81)
			tmp = localTmp;
		else
			tmp = (byte*)tsi_AllocMem(*(int*)(self + 4), tripleLen);

		byte* src = (byte*)*(int*)(self + 0x118);
		FF_GetColorTable();

		if (colorTable > 0)
		{
			int   srcDelta = (int)src - (int)tmp;
			byte* rowSrc   = src + 1;
			byte* rowDst   = pixels;
			int   rows     = colorTable;
			do
			{
				int x = 0;
				tmp[0] = 0;
				tmp[1] = 0;
				tmp[2] = 0;
				if (width - 2 > 1)
				{
					int i = 1;
					do
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
						x = i;
					} while (i < width - 2);
					x = i;
				}
				else
				{
					x = 1;
				}
				(void)x;
				(void)srcDelta;
			} while (--rows != 0);
		}
	}
}

// ---------------------------------------------------------------------------
// FUN_008c3570 -- thin wrapper: install the object pointer and tail into 8c3120
// @ 0x008c3570
void FUN_008c3570(int self)
{
	FUN_008c3120(self);
}

// ---------------------------------------------------------------------------
// FUN_008c3580 -- write the gray output (block-scaled variant)
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

// ---------------------------------------------------------------------------
// FUN_008c39a0 -- write the external-version LCD output
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

// ---------------------------------------------------------------------------
// memForSubIndexTable -- parse a sub-index table and report its memory needs
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

// ---------------------------------------------------------------------------
// Delete_blocClass -- release the sub-tables owned by a bloc class
// @ 0x008c4000
void Delete_blocClass(int* p)
{
	if (p == 0)
		return;
	tsi_DeAllocMem(p[0], (void*)p[0xf]);
	tsi_DeAllocMem(p[0], (void*)p[0x14]);
	tsi_DeAllocMem(p[0], p);
}
