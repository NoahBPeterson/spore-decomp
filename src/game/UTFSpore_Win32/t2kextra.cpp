// src/game/UTFSpore_Win32/t2kextra.cpp -- migrated from slice(s) s008c3120, s008c2540 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/t2kextra.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void tsi_DeAllocMem(void* mem, void* p);        // 0x008d1440
extern "C" int util_EuclidianDistance(int x, int y);   // 0x008d17d0
extern "C" int util_FixDiv(int a, int b);              // 0x008d16d0
extern "C" int util_FixMul(int a, int b);              // 0x008d1590

// ---- items of slice s008c2540 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint8_t u8;
typedef uint32_t u32;
struct TVEffect {
    u8 isGrey;     // +0: 0 = source is a 1-bit bitmap
    u8 mode;       // +1
    u8 pad2[2];
    int dx;        // +4
    int dy;        // +8
    int r;         // +0xc
    int g;         // +0x10
    int b;         // +0x14
    int r2;        // +0x18
    int g2;        // +0x1c
    int b2;        // +0x20
};
extern "C" void tsi_DeAllocMem(void* mem, void* p);        // 0x008d1440
static inline u32 BitVal(const u8* row, int x, u32 on)
{
    return ((0x80 >> (x & 7)) & row[x >> 3]) ? on : 0;
}
typedef void* (*AllocCallback)(void* user, int size);
struct T2KMem {
    char pad0[0x64];
    void* m_cache;      // +0x64
    char pad68[0x34];
    int m_flag9c;       // +0x9c
};
struct T2KObj {
    char pad00[4];
    T2KMem* m_mem;      // +0x04
    char pad08[0x14];
    int m_flag1c;       // +0x1c
    void* m_allocUser;  // +0x20
    void* m_allocFn;    // +0x24
    char pad28[0x8];
    int m_owned;        // +0x30
    int m_allocated;    // +0x34
    char pad38[0x98];
    int m_fix0;         // +0xd0
    int m_fix1;         // +0xd4
    int m_fix2;         // +0xd8
    int m_fix3;         // +0xdc
    int m_light0;       // +0xe0
    char padE4[0x18];
    int m_light1;       // +0xfc
    char pad100[0xc];
    int m_width;        // +0x10c
    int m_height;       // +0x110
    int m_rowBytes;     // +0x114
    u8* m_src;          // +0x118
    u32* m_out;         // +0x11c
};
extern "C" int util_EuclidianDistance(int x, int y);   // 0x008d17d0
extern "C" int util_FixDiv(int a, int b);              // 0x008d16d0
extern "C" int util_FixMul(int a, int b);              // 0x008d1590
// ---- items of slice s008c2540 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_008c3120(int self);

typedef unsigned char  byte;
typedef unsigned int   uint;
typedef byte* (__cdecl *AllocFn)(int, int);
void* __cdecl tsi_AllocMem(int heap, int size);   // 0x008d1260
void  __cdecl FF_GetColorTable(void);                               // 0x008c20c0


// @ 0x008c21c0
extern "C" void T2K_CastRaysOfLightAndDarkness(unsigned* buf, int a2, int a3, int a4, int a5,
                                               unsigned* sel)
{
    unsigned colLo = (((*(unsigned*)((char*)(sel) + 0x18)) << 8 | (*(unsigned*)((char*)(sel) + 0x1c))) << 8) | (*(unsigned*)((char*)(sel) + 0x20));
    unsigned colHi = (((*(unsigned*)((char*)(sel) + 0x24)) << 8 | (*(unsigned*)((char*)(sel) + 0x28))) << 8) | (*(unsigned*)((char*)(sel) + 0x2c));
    int subFalse = 0;               // subtracted in the "both false" branch (orig [esp+0x38])
    int subTrue = 0;                // subtracted in the "both true" branch  (orig [esp+0x3c])
    unsigned colB = 0;              // colour mask held in [esp+0x14]
    unsigned colA = 0;              // colour mask held in [esp+0x18]
    if ((*(char*)((char*)(sel) + 1)) == 1) {
        subTrue = 0;
        subFalse = 1;
        colB = colLo;
        colA = colHi;
    } else if ((*(char*)((char*)(sel) + 1)) == 2) {
        subTrue = 1;
        subFalse = 0;
        colB = colHi;
        colA = colLo;
    }

    int i = 0;
    if (0 < a5) {
        do {
            unsigned v = buf[i];
            if (v != 0) {
                unsigned u = v << 0x18;
                if (u < 0x7f000000u)
                    u = u - 0x80000000u;
                buf[i] = u;
            }
            i++;
        } while (i < a5);
    }

    int span = a3;                  // local_28 = max(a2, a3)
    if (a3 < a2)
        span = a2;

    int pass = 0;                   // local_8
    do {
        int limit = a3;             // local_c: a3 on pass 0, a2 on pass 1
        int r = pass;
        if (pass != 0)
            limit = a2;
        for (; r < limit; r++) {
            int off;                    // orig [esp+0x1c]
            int col;                    // orig [esp+0x24]
            if (pass == 0) {
                off = 0;
                col = r;
            } else {
                col = 0;
                off = r;
            }
            int count = 0;              // orig [esp+0x10] (number of row pixels to walk)
            if (0 < span) {
                int n = 0;
                int c = col;
                do {
                    if (a2 <= (off - col) + c || a3 <= c)
                        break;
                    count++;
                    n++;
                    c++;
                } while (n < span);
            }
            int idx = 0;
            if (0 < count) {
                int base = 0;           // row offset at the start of the current run (orig [esp+0x44])
                int idxOff = 0;         // idx * a4 (orig [esp+0x30])
                int rowOff = col * a4;  // (col + idx) * a4 (orig [esp+0x48])
                bool prevIn = false;    // run currently open?
                int prevN = 0;          // first index of the current run
                bool prevVal = false;   // value at the run's previous sample
                int lastIdx = 0;        // last index seen in the current run
                do {
                    unsigned v = buf[rowOff + idx + off];
                    bool val = false;
                    int end;            // split point between the two colour spans
                    unsigned mask1 = 0; // colour mask for the first span  (orig [esp+0x20])
                    unsigned mask2 = 0; // colour mask for the second span (orig [esp+0x40])
                    if (prevIn) {
                        if (v < 0x80000000u) {
                            val = v != 0;
                        } else {
                            lastIdx = idx;
                            if (idx < count - 1)
                                goto next;
                            val = false;
                        }
                    } else if (v < 0x80000000u) {
                        prevVal = v != 0;
                        goto next;
                    } else {
                        prevIn = true;
                        base = idxOff;
                        prevN = idx;
                        lastIdx = idx;
                        if (idx < count - 1)
                            goto next;
                        val = false;
                    }
                    /* merge the run [prevN, lastIdx] using the two colours */
                    if ((int)prevVal < (int)val) {
                        mask1 = colA;
                    } else if ((int)val < (int)prevVal) {
                        mask1 = colB;
                    } else if (prevVal || val) {
                        mask1 = colB;
                        mask2 = colA;
                        end = (lastIdx + prevN) / 2 - subTrue;
                    } else {
                        mask1 = colA;
                        mask2 = colB;
                        end = (lastIdx + prevN) / 2 - subFalse;
                    }
                    if (prevN <= end) {
                        int p = prevN + off;
                        int q = col * a4 + base;  // base is the run's start row, not the current one
                        int k = (end - prevN) + 1;
                        do {
                            unsigned* slot = &buf[q + p];
                            q += a4;
                            p++;
                            k--;
                            *slot = (*slot - 0x80000000u) | mask1;
                        } while (k != 0);
                    }
                    end++;
                    if (end <= lastIdx) {
                        int p = end + off;
                        int q = (col + end) * a4;
                        int k = (lastIdx - end) + 1;
                        do {
                            unsigned* slot = &buf[q + p];
                            q += a4;
                            p++;
                            k--;
                            *slot = (*slot - 0x80000000u) | mask2;
                        } while (k != 0);
                    }
                    prevIn = false;
                    base = idxOff;
                    prevN = idx;
                    prevVal = val;
                next:
                    idxOff += a4;
                    rowOff += a4;
                    idx++;
                } while (idx < count);
            }
        }
        pass++;
        if (1 < pass) {
            i = 0;
            if (0 < a5) {
                do {
                    unsigned v = buf[i];
                    if (v != 0) {
                        unsigned hi = v >> 0x18;
                        if (0x7e < hi)
                            hi = 0x7e;
                        buf[i] = (hi * 0x40 + (hi & 0xffffffe0)) * 0x80000 | (v & 0xffffff);
                    }
                    i++;
                } while (i < a5);
            }
            return;
        }
    } while (1);
}

// @ 0x008c2c80
void T2K_CreateBorderedCharacter(T2KObj* t, TVEffect* fx)
{
    int g = fx->g;
    int r = fx->r;
    int r2 = fx->r2;
    u32 b2 = (u32)fx->b2;
    u8 isGrey = fx->isGrey;
    int b = fx->b;
    int width = t->m_width;
    int dy = fx->dy;
    u32 g2 = (u32)fx->g2;
    int dx = fx->dx;
    int rowBytes = t->m_rowBytes;
    u8* src = t->m_src;
    int dx2 = dx * 2;
    int height = t->m_height;
    int dy2 = dy * 2;
    int outW = width + dx2;
    int outH = dy2 + height;
    if (height == 0)
        outH = 0;

    if (t->m_fix0 != 0) {
        if (t->m_flag1c == 0) {
            int span = dx2 > dy2 ? dx2 : dy2;
            int dist = util_EuclidianDistance(t->m_fix2, t->m_fix3);
            int scale = util_FixDiv(span * 0x10000 + dist, dist);
            t->m_fix0 = util_FixMul(scale, t->m_fix0);
            t->m_fix1 = util_FixMul(scale, t->m_fix1);
            t->m_fix2 = util_FixMul(scale, t->m_fix2);
            t->m_fix3 = util_FixMul(scale, t->m_fix3);
        } else {
            t->m_fix2 += dx * 0x20000;
            t->m_fix0 += dx * 0x20000;
        }
    }

    t->m_light0 += dy * 0x40;
    t->m_light1 += dy * 0x40;
    t->m_rowBytes = outW * 4;
    t->m_height = outH;
    t->m_width = outW;

    int total = src == 0 ? 0 : outW * outH;
    t->m_allocated = 0;
    u32* out;
    if (t->m_allocFn == 0 ||
        (out = (u32*)((AllocCallback)t->m_allocFn)(t->m_allocUser, total * 4)) == 0) {
        out = (u32*)tsi_AllocMem((int)t->m_mem, total * 4);
        t->m_allocated = 1;
    }
    t->m_out = out;

    if (total != 0) {
        for (int i = 0; i < total; i++)
            out[i] = 0;

        u32* scan = out + outW * dy * 2;
        if (height > 0) {
            int rows = height;
            do {
                int x = 0;
                if (width > 0) {
                    do {
                        u32 v = isGrey ? src[x] : BitVal(src, x, 0x7e);
                        if (v != 0) {
                            u32 s = (v >> 5) + v * 2;
                            for (int i = dy2; i > 0; i--) {
                                if (*scan < s) *scan = s;
                                scan -= outW;
                            }
                            for (int i = dx2; i > 0; i--) {
                                if (*scan < s) *scan = s;
                                scan++;
                            }
                            for (int i = dy2; i > 0; i--) {
                                if (*scan < s) *scan = s;
                                scan += outW;
                            }
                            for (int i = dx2; i > 0; i--) {
                                if (*scan < s) *scan = s;
                                scan--;
                            }
                        }
                        x++;
                        scan++;
                    } while (x < width);
                }
                src += rowBytes;
                scan += outW - width;
                rows--;
            } while (rows != 0);
        }

        for (int i = 0; i < total; i++)
            out[i] = (out[i] << 24) | ((((u32)r2 << 8) | g2) << 8) | b2;

        u32* dest = out + outW * dy + dx;
        if (height > 0) {
            int rows = height;
            do {
                int x = 0;
                if (width > 0) {
                    do {
                        u32 v = isGrey ? src[x] : BitVal(src, x, 0x7e);
                        if (v != 0) {
                            int k = (v >> 5) + 1 + (int)v * 2;
                            u32 px = *dest;
                            unsigned a = (px >> 24) & 0xff;
                            a = a + (a >> 7);
                            *dest = ((((u32)(r - r2) * k) & 0xffffff00u) + (u32)r2 * 0x100) * 0x100 |
                                    ((((u32)(g - (int)g2) * k) & 0xffffff00u) + g2 * 0x100) |
                                    (((((0x100 - a) * (u32)k) >> 8) - 1 + a) * 0x1000000) |
                                    ((((u32)(b - (int)b2) * k) >> 8) + b2);
                        }
                        x++;
                        dest++;
                    } while (x < width);
                }
                src += rowBytes;
                dest += outW - width;
                rows--;
            } while (rows != 0);
        }
    }

    if (t->m_out != 0 && t->m_owned != 0) {
        T2KMem* mem = t->m_mem;
        if (t->m_out == (u32*)mem->m_cache)
            mem->m_flag9c = 1;
        else
            tsi_DeAllocMem(mem, t->m_out);
        t->m_out = 0;
    }
}

// @ 0x008c3120
struct T2KWriter {
    char pad00[4];
    int  m_mem;         // +0x4
    char pad08[0x18];
    int  m_allocUser;   // +0x20
    AllocFn m_allocFn;  // +0x24
    char pad28[0xa8];
    int  m_f0;          // +0xd0
    int  m_f1;          // +0xd4
    int  m_f2;          // +0xd8
    int  m_f3;          // +0xdc
    char padE0[4];
    int  m_f4;          // +0xe4
    char padE8[4];
    int  m_f5;          // +0xec
    char padF0[4];
    int  m_f6;          // +0xf4
    char padF8[8];
    int  m_f7;          // +0x100
    char pad104[8];
    int  m_f8;          // +0x10c
    int  m_f9;          // +0x110
    int  m_f10;         // +0x114
    void* m_src;        // +0x118
};

// @ 0x008c3120
void FUN_008c3120(int self_)
{
	T2KWriter* self = (T2KWriter*)self_;
	int   colorTable = self->m_f9;
	int   rowPitch   = self->m_f10;
	int   width      = self->m_f8;
	int   nTriples   = (width + 6) / 3;
	int   tripleLen  = nTriples * 3;
	int   padOffset  = (tripleLen - width - 4) * 0x20;
	int   height;

	self->m_f4 -= 0x80;

	height = (self->m_f4 + 1 + padOffset) / 3;
	self->m_f7 = (padOffset - 0x7f + self->m_f7) / 3;
	self->m_f2 = (self->m_f2 + 1) / 3;
	self->m_f5 = (self->m_f5 + 1) / 3;
	self->m_f6 = (self->m_f6 + 1) / 3;

	uint base = (self->m_f0 + 1) / 3 + 0x8000;

	byte* tmp = 0;
	self->m_f4 = height;
	*(uint*)&self->m_f0 = base & 0xffff0000;

	if (height >> 6 >= 0 && (int)(base >> 16) <= (height >> 6) + nTriples)
		self->m_f4 = height - 0x40;

	self->m_f10 = nTriples;
	self->m_f8 = nTriples;
	(void)rowPitch;

	int allocSize;
	if ((int)self->m_src == 0)
		allocSize = 0;
	else
		allocSize = nTriples * colorTable;

	int owned = 0;
	byte* pixels  = 0;
	AllocFn allocator = self->m_allocFn;
	if (allocator != 0)
		pixels = allocator(self->m_allocUser, allocSize);
	if (pixels == 0)
	{
		pixels = (byte*)tsi_AllocMem(self->m_mem, allocSize);
		owned = 1;
	}

	if (allocSize != 0)
	{
		byte localTmp[128];
		if (tripleLen < 0x81)
			tmp = localTmp;
		else
			tmp = (byte*)tsi_AllocMem(self->m_mem, tripleLen);

		byte* src = (byte*)(int)self->m_src;
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
	(void)owned;
}

// @ 0x008c3570
void FUN_008c3570(int self)
{
	FUN_008c3120(self);
}
