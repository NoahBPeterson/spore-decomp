// s00fd36c0 -- bitstream reader / audio frame decoder helpers.
// Rebuilt from the shipped PE.  The module works on a large decoder object whose
// fields are addressed by fixed offsets; those offsets are kept as literals.

struct Decoder;

// ---------------------------------------------------------------------------------------------------------
// bit reader used by this module (external helpers)
// ---------------------------------------------------------------------------------------------------------
int   __cdecl FUN_00fcef00(int* state, int code);      // 0x00fcef00
int   __cdecl FUN_00fcef80(int* state);                // 0x00fcef80
int   __cdecl FUN_00fcefe0(int* state, int n);         // 0x00fcefe0
int   __cdecl FUN_00fcf130(int* state, int code);      // 0x00fcf130
int   __fastcall FUN_00fd2d00(int* s);                 // 0x00fd2d00
void  __cdecl FUN_00fd2d60(int p, int* table);         // 0x00fd2d60
void  __cdecl FUN_00fd3210(int p, unsigned char mode); // 0x00fd3210
void  __cdecl FUN_00fd30a0(int p);                     // 0x00fd30a0
void  __cdecl FUN_00fd3550(int p);                     // 0x00fd3550
void  __cdecl FUN_00fd34c0(int p);                     // 0x00fd34c0
void  __cdecl FUN_00fd0120(int p, int a, int b);       // 0x00fd0120
void  __cdecl FUN_00fd4170(int p);                     // 0x00fd4170
void  __cdecl FUN_00fd4340(int p, unsigned char mode); // 0x00fd4340
void  __cdecl FUN_00fd3e90(int p);                     // 0x00fd3e90
int   __cdecl FUN_00fd4090(int p);                     // 0x00fd4090
void* __cdecl operator_new_arr(void* p, int a, unsigned int size); // 0x011e073e

// ---------------------------------------------------------------------------------------------------------
// data tables
// ---------------------------------------------------------------------------------------------------------
extern "C"
{
	extern const int DAT_01492328[16];                // 0x01492328
	extern const int DAT_01492368[16];                // 0x01492368
	extern const unsigned short DAT_01492540[];       // 0x01492540
	extern const short DAT_01492542[];                // 0x01492542
	extern const unsigned char DAT_01492544[];        // 0x01492544
	extern const int DAT_01492600[];                  // 0x01492600
	extern const unsigned char DAT_01492708[];        // 0x01492708
	extern const int DAT_01492ac8[20];                // 0x01492ac8
	extern const unsigned char DAT_01492b19[];        // 0x01492b19
	extern const unsigned char DAT_01492b1a[];        // 0x01492b1a
	extern const unsigned char DAT_01492b21[];        // 0x01492b21
	extern const unsigned short DAT_01492b48;         // 0x01492b48
	extern const unsigned short DAT_01492b5c;         // 0x01492b5c
	extern const unsigned short DAT_01492b60;         // 0x01492b60
	extern const unsigned int DAT_01492b3c;           // 0x01492b3c
	extern const unsigned int DAT_01492b40;           // 0x01492b40
	extern const unsigned int DAT_01492b44;           // 0x01492b44
	extern const unsigned int DAT_01492b4c;           // 0x01492b4c
	extern const unsigned int DAT_01492b50;           // 0x01492b50
	extern const unsigned int DAT_01492b54;           // 0x01492b54
	extern const unsigned int DAT_01492b58;           // 0x01492b58
	extern int** DAT_016d9404;                        // 0x016d9404
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00fd4520 -- read a 32-bit big-endian value into a bitstream record
// @ 0x00fd4520
void FUN_00fd4520(int* out, unsigned char* p)
{
	out[0] = (int)p;
	out[1] = (((((p[0] << 8) + p[1]) << 8) + p[2]) << 8) + p[3];
	out[2] = 0x20;
	out[3] = 4;
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00fd4560 -- consume n bits from the big-endian bitstream
// @ 0x00fd4560
unsigned int FUN_00fd4560(int* s, unsigned int n)
{
	unsigned int pos = s[3];
	unsigned char* data = (unsigned char*)s[0];
	unsigned int cnt = s[2];
	unsigned int buf = s[1];
	unsigned int hi;

	data += pos;
	hi = 0;
	if (cnt < n)
	{
		n -= cnt;
		hi = (buf >> (32 - cnt)) << n;
		buf = ((((data[0] << 8) + data[1]) << 8) + data[2]) << 8;
		buf += data[3];
		pos += 4;
		cnt = 0x20;
	}
	s[1] = buf << n;
	s[2] = cnt - n;
	s[3] = pos;
	return (buf >> (32 - n)) | hi;
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00fd4090 -- scale factor of one subband (0 when unset)
// @ 0x00fd4090
int FUN_00fd4090(int p)
{
	int* s = (int*)(p + 0x10c);
	int  k;

	if (FUN_00fcef00(s, 0xcd) == 0)
		return 0;

	k = 1 - 2 * FUN_00fcef80(s);
	if (FUN_00fcef00(s, 0xab) == 0)
		return k << (3 - FUN_00fcef00(s, 0x53));
	if (FUN_00fcef00(s, 0xc7) == 0)
	{
		if (FUN_00fcef00(s, 0x8c) != 0)
			return k * 0xc;
		if (FUN_00fcef00(s, 0x7d) != 0)
			return k * 0x10;
		if (FUN_00fcef00(s, 0x68) != 0)
			return k * 0x14;
		return k * 0x18;
	}
	return FUN_00fcefe0(s, 7) * k * 4;
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00fd4170 -- read the scale-factor band tables and adjust them
// @ 0x00fd4170
void FUN_00fd4170(int p)
{
	int local = 0;
	unsigned char* dst = (unsigned char*)(p + 0x37cd);

	do
	{
		if (FUN_00fcef00((int*)(p + 0x10c), 0xae) != 0)
		{
			unsigned int v = 0;
			int i;
			for (i = 3; i >= 0; i--)
				v |= (unsigned int)FUN_00fcef80((int*)(p + 0x10c)) << i;
			int rec = (local + v) * 0x14;
			dst[-1]  = DAT_01492708[rec + 0x0];
			dst[-0xb] = DAT_01492708[rec + 0x1];
			dst[0]   = DAT_01492708[rec + 0x2];
			dst[-0xa] = DAT_01492708[rec + 0x3];
			dst[1]   = DAT_01492708[rec + 0x4];
			dst[-9]  = DAT_01492708[rec + 0x5];
			dst[2]   = DAT_01492708[rec + 0x6];
			dst[-8]  = DAT_01492708[rec + 0x7];
			dst[3]   = DAT_01492708[rec + 0x8];
			dst[-7]  = DAT_01492708[rec + 0x9];
			dst[4]   = DAT_01492708[rec + 0xa];
			dst[-6]  = DAT_01492708[rec + 0xb];
			dst[5]   = DAT_01492708[rec + 0xc];
			dst[-5]  = DAT_01492708[rec + 0xd];
			dst[6]   = DAT_01492708[rec + 0xe];
			dst[-4]  = DAT_01492708[rec + 0xf];
			dst[7]   = DAT_01492708[rec + 0x10];
			dst[-3]  = DAT_01492708[rec + 0x11];
			dst[8]   = DAT_01492708[rec + 0x12];
			dst[-2]  = DAT_01492708[rec + 0x13];
		}

		if (FUN_00fcef00((int*)(p + 0x10c), 0xfe) != 0)
		{
			int i;
			for (i = 0; i < 10; i++)
			{
				int v = FUN_00fd4090(p) + dst[i - 1];
				if (v < 0)
					v = 0;
				else if (v > 0xff)
					v = 0xff;
				dst[i - 1] = (unsigned char)v;

				v = FUN_00fd4090(p) + dst[i - 0xb];
				if (v < 0)
					v = 0;
				else if (v > 0xff)
					v = 0xff;
				dst[i - 0xb] = (unsigned char)v;
			}
		}
		local += 0x10;
		dst += 0x14;
	} while (local < 0x30);

	FUN_00fd3e90(p);
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00fd4340 -- read the Huffman/code-length tables from the bitstream
// @ 0x00fd4340
void FUN_00fd4340(int p, unsigned char mode)
{
	int* s = (int*)(p + 0x10c);
	int i = 0;
	const unsigned char* t = DAT_01492b19;

	(void)mode;

	do
	{
		if (FUN_00fcef00(s, t[-1]) != 0)
		{
			unsigned int v = 0;
			int k;
			for (k = 6; k >= 0; k--)
				v |= (unsigned int)FUN_00fcef80(s) << k;
			unsigned char c = (unsigned char)(v * 2);
			*(unsigned char*)(i + 0x37a2 + p) = c;
			if (c == 0)
				*(unsigned char*)(i + 0x37a2 + p) = 1;
		}
		if (FUN_00fcef00(s, t[0]) != 0)
		{
			unsigned int v = 0;
			int k;
			for (k = 6; k >= 0; k--)
				v |= (unsigned int)FUN_00fcef80(s) << k;
			unsigned char c = (unsigned char)(v * 2);
			*(unsigned char*)(i + 0x37a0 + p) = c;
			if (c == 0)
				*(unsigned char*)(i + 0x37a0 + p) = 1;
		}
		t += 0x11;
		i++;
	} while ((int)t < 0x1492b3b);

	{
		unsigned char* d = (unsigned char*)(p + 0x37a4);
		const unsigned char* base = DAT_01492b1a;
		do
		{
			int j = 0;
			const unsigned char* src = base;
			do
			{
				if (FUN_00fcef00(s, *src) != 0)
				{
					unsigned int v = 0;
					int k;
					for (k = 6; k >= 0; k--)
						v |= (unsigned int)FUN_00fcef80(s) << k;
					unsigned char c = (unsigned char)(v * 2);
					d[j] = c;
					if (c == 0)
						d[j] = 1;
				}
				j++;
				src++;
			} while (j < 7);
			d += 7;
			base += 0x11;
		} while ((int)base < 0x1492b3c);
	}

	{
		unsigned char* d = (unsigned char*)(p + 0x37b2);
		const unsigned char* base = DAT_01492b21;
		do
		{
			int j = 0;
			const unsigned char* src = base;
			do
			{
				if (FUN_00fcef00(s, *src) != 0)
				{
					unsigned int v = 0;
					int k;
					for (k = 6; k >= 0; k--)
						v |= (unsigned int)FUN_00fcef80(s) << k;
					unsigned char c = (unsigned char)(v * 2);
					d[j] = c;
					if (c == 0)
						d[j] = 1;
				}
				j++;
				src++;
			} while (j < 8);
			d += 8;
			base += 0x11;
		} while ((int)base < 0x1492b43);
	}
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00fd3e90 -- normalise the decoded band energies into the scale tables
// @ 0x00fd3e90
void FUN_00fd3e90(int p)
{
	unsigned char* pbVar5 = (unsigned char*)(p + 0x37cc);
	unsigned char* pcVar3 = (unsigned char*)(p + 0x383b);
	int local_4c = 0;
	int local_48 = -10;

	do
	{
		unsigned char* local_50 = pbVar5 + 0x46;
		unsigned char* pbVar4 = pbVar5;
		int local_40 = 3;

		do
		{
			int local_28[10];
			int iVar6 = 0;
			int i;

			for (i = 0; i < 10; i++)
			{
				if (local_4c == i)
					local_28[i] = 0;
				else
					local_28[i] = pbVar4[local_48 + i] * 100;
				iVar6 += local_28[i];
			}

			*local_50 = (unsigned char)(255 - (pbVar5[0] * 255) / (pbVar5[-10] + pbVar5[0] + 1));

			int iVar1 = local_28[0] + local_28[2] + local_28[3] + local_28[4];
			pcVar3[-1] = (unsigned char)(iVar1 * 255 / (iVar6 + 1)) + 1;
			pcVar3[0]  = (unsigned char)((local_28[0] + local_28[2]) * 255 / (iVar1 + 1)) + 1;

			int iVar1b = local_28[5] + local_28[6] + local_28[8] + local_28[9];
			pcVar3[1] = (unsigned char)((local_28[1] + local_28[7]) * 255 /
			                            (iVar1b + local_28[1] + local_28[7] + 1)) + 1;
			pcVar3[2] = (unsigned char)(local_28[0] * 255 / (local_28[2] + local_28[0] + 1)) + 1;
			pcVar3[3] = (unsigned char)(local_28[3] * 255 / (local_28[4] + local_28[3] + 1)) + 1;
			pcVar3[4] = (unsigned char)(local_28[1] * 255 / (local_28[1] + local_28[7] + 1)) + 1;
			pcVar3[5] = (unsigned char)((local_28[6] + local_28[5]) * 255 / (iVar1b + 1)) + 1;
			pcVar3[6] = (unsigned char)(local_28[5] * 255 / (local_28[6] + local_28[5] + 1)) + 1;
			pcVar3[7] = (unsigned char)(local_28[8] * 255 / (local_28[9] + local_28[8] + 1)) + 1;

			pbVar4 += 0x14;
			local_50 += 0xa;
			pcVar3 += 0x5a;
		} while (--local_40 != 0);

		local_48--;
		local_4c++;
		pbVar5++;
		pcVar3 += 9;
	} while (-0x14 < local_48);
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00fd3c10 -- start a frame: reset the tables and prepare the band map
// @ 0x00fd3c10
void FUN_00fd3c10(int p)
{
	int iVar1 = *(int*)(p + 0x1a8);
	int iVar2 = *(int*)(p + 0x1ac);
	int i, j;

	DAT_016d9404 = (int**)&p;

	if (*(char*)(p + 0x3b62) == 0)
	{
		for (i = 0; i < 0x14; i++)
			((int*)(p + 0x37c2))[i] = DAT_01492ac8[i];

		*(unsigned short*)(p + 0x37a2) = DAT_01492b5c;
		*(unsigned int*)(p + 0x37a4)   = DAT_01492b3c;
		*(unsigned int*)(p + 0x37a8)   = DAT_01492b40;
		*(unsigned int*)(p + 0x37ac)   = DAT_01492b44;
		*(unsigned short*)(p + 0x37b0) = DAT_01492b48;
		*(unsigned short*)(p + 0x37a0) = DAT_01492b60;
		*(unsigned int*)(p + 0x37b2)   = DAT_01492b4c;
		*(unsigned int*)(p + 0x37b6)   = DAT_01492b50;
		*(unsigned int*)(p + 0x37ba)   = DAT_01492b54;
		*(unsigned int*)(p + 0x37be)   = DAT_01492b58;

		operator_new_arr(*(void**)(p + 0x350), 1, *(unsigned int*)(p + 0x1a4));

		const int* tbl = (*(int*)(p + 0x160) == 1) ? DAT_01492368 : DAT_01492328;
		for (i = 0; i < 0x10; i++)
			((int*)(p + 0x2a8))[i] = tbl[i];
		FUN_00fd2d60(p, (int*)(p + 0x2a8));
	}
	else
	{
		FUN_00fd4170(p);
		FUN_00fd4340(p, *(unsigned char*)(p + 0x3b62));
		*(int*)(p + 0x1a0) = 0;
	}

	FUN_00fd3210(p, *(unsigned char*)(p + 0x3b62));

	for (i = 0; i < 0x10; i++)
	{
		unsigned char* src = *(unsigned char**)(*(int*)(p + 0xf4) + 0xc);
		unsigned char* dst = (unsigned char*)(p + 0x1e8 + i * 4);
		dst[0] = src[dst[0x40] * 4];
		dst[1] = src[dst[0x41] * 4];
		dst[2] = src[dst[0x42] * 4];
		dst[3] = src[dst[0x43] * 4];
	}

	if (*(int*)(p + 0x238c) != 0)
		FUN_00fd30a0(p);

	if (*(int*)(p + 0x160) == 1)
	{
		unsigned int v = 0;
		for (i = 7; i >= 0; i--)
			v |= (unsigned int)FUN_00fcef80((int*)(p + 0x10c)) << i;
		*(unsigned int*)(p + 0x330) = v & 0xff;
	}

	FUN_00fd3550(p);
	operator_new_arr(*(void**)(p + 4), 0, 0x300);

	*(int*)(p + 0x3790) = 0;
	*(int*)(p + 0x3794) = 0;
	*(int*)(p + 0x3798) = 0;
	*(int*)(p + 0x379c) = 0;

	int n1 = iVar1 - 3;
	if (3 < n1)
	{
		int n2 = iVar2 - 3;
		for (i = 3; i < n1; i++)
		{
			FUN_00fd34c0(p);
			for (j = 3; j < n2; j++)
				FUN_00fd0120(p, i, j);
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
// FUN_00fd36c0 -- decode one band of quantised coefficients
// @ 0x00fd36c0
unsigned char FUN_00fd36c0(int p, short* out, int p3, unsigned char* p4, unsigned char* p5)
{
	int stream = *(int*)(*(int*)(p + 0xf4) + 0xc);
	unsigned char* b11 = (unsigned char*)(p + 0x39a2 + p3 * 0xb);
	int idx = p3 * 3 + *p4 + *p5;
	int* s = (int*)(p + 0x124);
	unsigned char* rec = (unsigned char*)(p + 0x3b44 + idx * 5);
	unsigned char bVar3;
	unsigned char pos;
	int i;
	unsigned int val;
	int code;
	int sign;

	if (FUN_00fcf130(s, rec[0]) == 0)
	{
		bVar3 = 0;
		*p5 = 0;
		*p4 = 0;
	}
	else
	{
		*p5 = 1;
		*p4 = 1;
		if (FUN_00fcf130(s, rec[2]) == 0)
		{
			bVar3 = 1;
			sign = FUN_00fd2d00(s);
			*out = (short)((-sign ^ 1) + sign);
		}
		else
		{
			bVar3 = 2;
			if (FUN_00fcf130(s, rec[3]) == 0)
			{
				if (FUN_00fcf130(s, rec[4]) == 0)
					val = 2;
				else
					val = FUN_00fcf130(s, b11[5]) + 3;
				sign = FUN_00fd2d00(s);
				*out = (short)((-sign ^ val) + sign);
				goto LAB_loop;
			}

			if (FUN_00fcf130(s, b11[6]) == 0)
				code = FUN_00fcf130(s, b11[7]) + 5;
			else if (FUN_00fcf130(s, b11[8]) == 0)
				code = FUN_00fcf130(s, b11[9]) + 7;
			else
				code = FUN_00fcf130(s, b11[10]) + 9;

			code *= 0x10;
			val = DAT_01492540[code];
			i = DAT_01492542[code];
			do
			{
				val += (unsigned int)FUN_00fcf130(s, DAT_01492544[code + i]) << i;
				i--;
			} while (i >= 0);
			sign = FUN_00fd2d00(s);
			*out = (short)((-sign ^ val) + sign);
		}
	}

LAB_loop:
	pos = 1;
	do
	{
		unsigned char bVar16 = pos;
		unsigned char* e = (unsigned char*)((DAT_01492600[pos] + bVar3 * 6) * 0xb + p + 0x39b8 + p3 * 0xc6);

		if ((bVar16 < 2 || bVar3 != 0) && FUN_00fcf130(s, e[0]) == 0)
		{
			if (FUN_00fcf130(s, e[1]) == 0)
			{
				pos = (unsigned char)(bVar16 + 1);
				break;
			}

			unsigned char* q = (unsigned char*)(p + 0x334 + (bVar16 > 5 ? 0xe : 0));
			bVar3 = 0;
			if (FUN_00fcf130(s, q[0]) == 0)
			{
				if (FUN_00fcf130(s, q[1]) == 0)
					pos = (unsigned char)(bVar16 + FUN_00fcf130(s, q[2]) + 1);
				else
					pos = (unsigned char)(bVar16 + FUN_00fcf130(s, q[3]) + 3);
			}
			else if (FUN_00fcf130(s, q[4]) == 0)
			{
				if (FUN_00fcf130(s, q[5]) == 0)
					pos = (unsigned char)(bVar16 + FUN_00fcf130(s, q[6]) + 5);
				else
					pos = (unsigned char)(bVar16 + FUN_00fcf130(s, q[7]) + 7);
			}
			else
			{
				val = (unsigned int)FUN_00fcf130(s, q[8]);
				val += (unsigned int)FUN_00fcf130(s, q[9]) * 2;
				val += (unsigned int)FUN_00fcf130(s, q[10]) * 4;
				val += (unsigned int)FUN_00fcf130(s, q[11]) * 8;
				val += (unsigned int)FUN_00fcf130(s, q[12]) * 16;
				val += (unsigned int)FUN_00fcf130(s, q[13]) * 32;
				pos = (unsigned char)(bVar16 + val + 9);
			}
		}
		else
		{
			if (FUN_00fcf130(s, e[2]) == 0)
			{
				int a = *(int*)(p + 0x128);
				int b = *(int*)(p + 0x12c);
				int c = *(int*)(p + 0x130);
				int half = (a + 1) >> 1;
				unsigned int thr = (unsigned int)half << 0x18;
				int bit = (b >= (int)thr) ? 1 : 0;

				bVar3 = 1;
				if (b == (int)thr)
					a = half;
				else
				{
					a -= half;
					b -= thr;
				}
				b += b;
				a += a;
				if (--c == 0)
				{
					b |= *(unsigned char*)(*(int*)(p + 0x138) + *(int*)(p + 0x134));
					*(int*)(p + 0x134) += 1;
					c = 8;
				}
				*(int*)(p + 0x130) = c;
				*(int*)(p + 0x12c) = b;
				*(int*)(p + 0x128) = a;
				out[*(int*)(stream + *(unsigned char*)(p + 0x228 + pos) * 4)] = (short)(1 - 2 * bit);
			}
			else
			{
				bVar3 = 2;
				if (FUN_00fcf130(s, e[6]) == 0)
					code = FUN_00fcf130(s, e[7]) + 5;
				else if (FUN_00fcf130(s, e[8]) == 0)
					code = FUN_00fcf130(s, e[9]) + 7;
				else
					code = FUN_00fcf130(s, e[10]) + 9;

				code *= 0x10;
				val = DAT_01492540[code];
				i = DAT_01492542[code];
				do
				{
					val += (unsigned int)FUN_00fcf130(s, DAT_01492544[code + i]) << i;
					i--;
				} while (i >= 0);
				sign = FUN_00fd2d00(s);
				out[*(int*)(stream + *(unsigned char*)(p + 0x228 + pos) * 4)] = (short)((-sign ^ val) + sign);
			}
			pos = (unsigned char)(bVar16 + 1);
		}
	} while (pos < 0x40);

	return *(unsigned char*)(p + 0x268 + (unsigned char)(pos - 1));
}
