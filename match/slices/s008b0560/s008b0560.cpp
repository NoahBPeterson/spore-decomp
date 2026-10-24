// Slice s008b0560 -- EA-UTF Type-2 (T2K) glyph container (module "EA-UTF", object t2k.obj).
//
// 008b0560 New_GlyphClassT2K       build a GlyphClass from a packed T2K charstring
// 008b0920 tsi_DecodeGlyphHeader    decode one glyph descriptor into the two coord sets
// 008b0f10 tsi_ReadGlyphCoord       read one coordinate using a 2-bit selector nibble
// 008b1040 tsi_ReadFlagNibbleHi     nibble reader, high nibble first (this in ecx)
// 008b1070 tsi_ReadFlagNibbleLo     nibble reader, low nibble first (this in edx)
// 008b10a0 tsi_FindCoordIndex       value lookup in one of the four coordinate arrays
// 008b1160 SkipExtraStreamItems     skip `n` byte-counted items of the input stream
// 008b12e0 New_pfrkernSubTable0Data build a PFR kern sub-table 0 from a packed blob
//
// The structs (GlyphClass, T2KPointSet, PFRKernSubTable, InputStream) are the ones
// recovered in the neighbouring slices s008af670 / s008b3ae0 / s008b14b0.
//
// Flags: /O2 /MD /Gy /TP
#include "types.h"

typedef uint8_t  uint8;
typedef int8_t   int8;
typedef uint16_t uint16;
typedef int16_t  int16;
typedef uint32_t uint32;
typedef int32_t  int32;

struct tsiMemObject;
struct InputStream;

extern "C" {
void*  tsi_FastAllocN(tsiMemObject* mem, int32 size, int32 tag);   // 0x008d14d0
void*  tsi_AllocMem(tsiMemObject* mem, int32 size);                // 0x008d1260
void*  tsi_ReAllocMem(tsiMemObject* mem, void* p, int32 size);     // 0x008d1330
void   tsi_Error(tsiMemObject* mem, int32 code);                   // 0x008d10c0
int16  ReadInt16(InputStream* in);                                 // 0x008cc190
uint32 ReadUnsignedNumber(InputStream* in);                        // 0x008cc670
void   PrimeT2KInputStream(InputStream* in);                       // 0x008cc0b0
uint32 Tell_InputStream(InputStream* in);                          // 0x008cc5b0
void   Seek_InputStream(InputStream* in, uint32 pos);              // 0x008cc580
uint32 ReadDeltaXYValue(InputStream* in, int16* dx, int16* dy);    // 0x008af670
}

typedef int (*PF_READ_TO_RAM)(void* id, uint8* dst, uint32 pos, uint32 n);

struct InputStream {
    uint8*         privateBase;   // 0x000
    PF_READ_TO_RAM readToRam;     // 0x004
    void*          nonRamID;      // 0x008
    uint8          tmp_ch;        // 0x00c  one-byte staging area for readToRam
    uint8          pad00d[0x210 - 0x00d];
    uint32         bytesLeft;     // 0x210
    uint32         cacheCount;    // 0x214
    uint32         posZero;       // 0x218
    uint32         pos;           // 0x21c
    uint32         maxPos;        // 0x220
    uint32         posZero2;      // 0x224
    int            ctorType;      // 0x228
    tsiMemObject*  mem;           // 0x22c
};

// ---------------------------------------------------------------------------
// GlyphClass -- 0x78-byte layout shared with s008b4cc0 / s008b71c0.
// The fields at 0x08..0x12 and 0x44..0x50 are read with two different types by the
// simple-glyph path (as the flattened "glyph body") and by the composite/empty path
// (as two packed coord-set pointers), so they are spelled as raw dwords here.
// ---------------------------------------------------------------------------
struct GlyphClass {
    tsiMemObject* mem;            // 0x00
    uint16        w04;            // 0x04  T2K: point count
    uint16        pad06;
    uint32        w08;            // 0x08  T2K: number of contours (state: "has coords")
    uint32        d0c;            // 0x0c  composite record pointer (small glyphs)
    uint32        d10;            // 0x10  composite record end   (small glyphs)
    char          pad14[0x34 - 0x14];
    uint16        tag34;          // 0x34  glyph kind (3 for T2K glyphs)
    uint16        compFlag;       // 0x36  < 0 => composite
    uint16        contour;        // 0x38  current contour index
    uint16        pad3a;
    uint32        d3c;            // 0x3c  contour-offset table / composite record pointer
    uint32        d40;            // 0x40  contour-end table
    uint32        d44;            // 0x44  x array pointer
    uint32        d48;            // 0x48  y array pointer
    uint32        d4c;            // 0x4c  per-point tag array
    uint32        d50;            // 0x50  packed component blob
    uint32        d54;            // 0x54  end of the packed component blob
    uint32        d58;            // 0x58  decoded components
    uint32        d5c;            // 0x5c
    uint32        d60;            // 0x60  component capacity
    char          pad64[0x68 - 0x64];
    uint32        d68;            // 0x68  component count
    int16         cnt6c;          // 0x6c
    int16         cnt6e;          // 0x6e
    uint16        w70;            // 0x70  min x of the point set
    uint16        w72;            // 0x72  max y of the point set
    uint8         b74;            // 0x74
};

// ---------------------------------------------------------------------------
// @ 0x008b0560
// ---------------------------------------------------------------------------
extern "C" GlyphClass* New_GlyphClassT2K(tsiMemObject* mem, InputStream* in, uint32 a3,
                                         int16 lsb, int16 adv, int16 tsb, int16 adv2)
{
    GlyphClass* g = (GlyphClass*)tsi_FastAllocN(mem, 0x78, 0);
    g->mem = mem;
    g->d68 = 0;
    g->d3c = 0;
    g->d58 = 0;
    g->d54 = 0;
    g->d50 = 0;
    g->d0c = 0;
    g->d10 = 0;
    g->tag34 = 3;
    g->w04 = 0;
    g->w08 = 0;

    int16 contourDelta = ReadInt16(in);
    g->compFlag = contourDelta;
    g->cnt6c = 0;
    g->cnt6e = 0;
    g->w70 = 0;
    g->w72 = 0;
    g->d5c = 0;
    g->d68 = 0;
    g->d60 = 0;

    uint32 nAll = 0;        // points already in the arrays (also the phantom index)
    uint32 limit;           // packed-blob capacity (composite) or nPts (simple)

    if (contourDelta < 0) {
        // ---- composite glyph: the point deltas are packed back to front ----
        g->d60 = 0x400;
        int16* buf = (int16*)tsi_AllocMem(mem, 0x800);
        uint16 f;
        do {
            if ((int)g->d60 <= (int)nAll + 10) {
                g->d60 = g->d60 / 2 + g->d60;
                buf = (int16*)tsi_ReAllocMem(mem, buf, g->d60 * 2);
            }
            f = (uint16)ReadInt16(in);
            buf[nAll] = (int16)f;
            nAll++;
            buf[nAll] = ReadInt16(in);
            nAll++;
            if (f & 1)
                buf[nAll++] = ReadInt16(in);
            buf[nAll++] = ReadInt16(in);
            if (f & 8) {
                buf[nAll++] = ReadInt16(in);
            } else if (f & 0x40) {
                buf[nAll++] = ReadInt16(in);
            } else if (f & 0x80) {
                buf[nAll++] = ReadInt16(in);
                buf[nAll++] = ReadInt16(in);
                buf[nAll++] = ReadInt16(in);
            }
            if (f & 0x20)
                continue;
            break;
        } while (true);

        limit = 0;
        g->d68 = 0;
        uint32 m = (uint32)tsi_FastAllocN(mem, 0x34, 1);
        g->d50 = m;
        g->d54 = m + 0x10;
        g->d3c = m + 0x10;
        g->d44 = m + 0x20;
        g->d48 = m + 0x28;
        g->d4c = m + 0x30;
        g->d58 = (uint32)buf;
        g->d5c = nAll;
    } else if (contourDelta > 0) {
        // ---- simple glyph: cumulative contour ends ----
        int total = 0;
        int16* tbl;
        if (contourDelta <= 8) {
            g->d3c = (uint32)((char*)g + 0x44);
            tbl = (int16*)((char*)g + 0x50);
        } else {
            tbl = (int16*)tsi_AllocMem(mem, contourDelta * 4);
            g->d3c = (uint32)tbl;
            tbl = (int16*)((char*)tbl + contourDelta * 2);
        }
        int16* pEnd = tbl;
        for (int i = 0; i < contourDelta; i++) {
            *(int16*)((char*)g->d3c + i * 2) = (int16)total;
            total = (int16)(pEnd[i] + total);
            pEnd[i] = (int16)(total + 1);
            total++;
        }
        int nPts = total;
        int stride = nPts + 4;
        limit = (uint32)nPts;
        g->d68 = 0;
        char* m = (char*)tsi_FastAllocN(mem, stride * 0xd, 1);
        g->d50 = (uint32)m;
        g->d54 = (uint32)(m + stride * 4);
        g->d3c = (uint32)(m + stride * 4);
        g->d44 = (uint32)(m + stride * 8);
        g->d48 = (uint32)(m + stride * 0xa);
        g->d4c = (uint32)(m + stride * 0xc);
        g->w04 = g->compFlag;
        g->w08 = g->compFlag;
        int16 minX = 0x7fff;
        int16 maxY = (int16)0x8001;
        int16* pX = (int16*)g->d44;
        int16* pY = (int16*)g->d48;
        int16* pT = (int16*)g->d4c;
        int xAcc = 0;
        int yAcc = 0;
        for (int i = 0; i < nPts; i++) {
            int16 dx, dy;
            uint8 t = (uint8)ReadDeltaXYValue(in, &dx, &dy);
            xAcc += dx;
            yAcc += dy;
            pT[i] = t;
            if ((int16)xAcc < minX)
                minX = (int16)xAcc;
            if ((int16)yAcc > maxY)
                maxY = (int16)yAcc;
            pX[i] = (int16)xAcc;
            pY[i] = (int16)yAcc;
        }
        g->w70 = (uint16)minX;
        g->w72 = (uint16)maxY;
    } else {
        // ---- empty glyph ----
        limit = 0;
        g->d3c = 0;
        g->w08 = 0;
    }

    if (contourDelta <= 0) {
        // composite / empty: the four phantom points live in the packed blob
        uint32 m = g->d50;
        uint32 e = g->d54;
        int16* pp = (int16*)(m + 4);
        pp[0] = (int16)(g->w70 - lsb);
        pp[1] = (int16)(pp[0] + adv);
        int mid = ((int)pp[0] + (int)pp[1]) >> 1;
        *(int16*)(m + 2) = 0;
        *(int16*)(m + 4 + 4) = (int16)(g->w72 + tsb);
        *(int16*)(e) = (int16)(g->w72 + tsb - adv2);
        *(int16*)(e + 2) = (int16)mid;
        *(int16*)(e + 4) = (int16)mid;
        g->contour = (uint16)nAll;
        return g;
    }

    // simple glyph: the four phantom points follow the real points
    int16* pX = (int16*)(g->d44 + nAll * 2);
    int16* pY = (int16*)(g->d48 + nAll * 2);
    char*  pT = (char*)g->d4c + nAll * 2;
    *(int16*)(g->d58 + nAll * 2) = 0;
    pX[1] = (int16)(g->w70 - lsb);
    pT[2] = 0;
    int16 v = pX[1];
    pX[2] = (int16)(v + adv);
    pT[4] = (int16)(g->w72 + tsb);
    int mid = ((int)v + (int)pX[2]) >> 1;
    pT[6] = (int16)(pT[4] - adv2);
    pT[8] = (int16)mid;
    pT[10] = (int16)mid;
    g->contour = (uint16)limit;
    g->d54 = g->d58;
    return g;
}

// ===========================================================================
// @ 0x008b0920
// FUN_008b0920: expand one glyph descriptor into the x/y coordinate sets.
// Plain __cdecl with four stack arguments (the module's glyph builder at
// 0x008b3ae0 calls it as FUN_008b0920(pfr, flags, &cur, &pts)).
// ===========================================================================
struct T2KPointSet {
    uint16  nx;                   // 0x00
    int16   xs[0x40];             // 0x02
    uint16  ny;                   // 0x82
    int16   ys[0x40];             // 0x84
    int16   curX;                 // 0x104
    int16   curY;                 // 0x106
    uint16  out1;                 // 0x108  written as ushort, read as the u16 at 0x82
    uint16  out0;                 // 0x10a  written as ushort, read as the u16 at 0x84
    uint8*  outCursor;            // 0x10c
};

extern "C" void FUN_008b0920(GlyphClass* g, uint8 flags, uint8** cursor, T2KPointSet* pts)
{
    uint8* cur = *cursor;
    if (g->w08 == 0) {
        // ---------------- header of a composite sub-glyph ----------------
        uint32 nx, ny;
        switch (flags & 3) {
        case 0:
            nx = 0;
            ny = 0;
            break;
        case 1: {
            uint8 b = *cur;
            nx = b & 0xf;
            ny = b >> 4;
            cur++;
            break;
        }
        case 2: {
            uint8 b = *cur++;
            nx = b;
            ny = *cur++;
            break;
        }
        default: {
            uint8 b = *cur++;
            nx = b;
            ny = *cur++;
            break;
        }
        }

        int16 nX = (int16)nx;
        int16 nY = (int16)ny;
        int iX = 0;
        int iY = 0;
        int32 acc = 0;
        uint8 pairByte = 0;
        int left = 0;
        int16 lastIn = 0;
        int tableFlag = flags & 1;    // picks the nX or the nY table
        int guard = 0;
        do {
            if (iX < nX) {
                lastIn = iX;
                iX++;
                if (lastIn == 0) {
                    pairByte = g->cnt6e;
                    acc = 0;
                    tableFlag = flags & 1;
                } else {
                    goto both;
                }
            } else {
                if (iY >= nY)
                    break;
                lastIn = iY;
                iY++;
                if (lastIn == 0) {
                    pairByte = g->cnt6c;
                    acc = 0;
                    tableFlag = flags & 1;
                } else {
                both:
                    (void)guard;
                    if ((flags & 0x40) == 0) {
                        pairByte = 0;
                    } else if (left != 0) {
                        pairByte >>= 1;
                        left--;
                    } else if (tableFlag != 0) {
                        pairByte = *cur >> 4;
                        left = 3;
                        tableFlag = 1;
                    } else {
                        pairByte = *cur++ & 0xf;
                        left = 3;
                        tableFlag = 0;
                    }
                }
            }
            // the pair byte can yield up to four 2-bit fields; each field selects
            // the encoding of one coordinate delta
            for (int k = 0; k < 4; k++) {
                if (k != 0)
                    pairByte >>= 1;
                int16 v;
                if (k == 0) {
                    if ((pairByte & 1) == 0) {
                        if (left & 1) {
                            if (tableFlag) {
                                uint8 b0 = *cur++;
                                v = (int16)((int16)(int8)b0 * 0x100 + *cur);
                                cur++;
                            } else {
                                uint8 b0 = *cur;
                                uint8 b1 = cur[1];
                                cur += 2;
                                v = (int16)((int16)(int8)(b0 << 4) * 0x10 + (b1 >> 4));
                                tableFlag = 0;
                            }
                        } else {
                            int8 b0 = (int8)*cur++;
                            v = (int16)((int16)b0 * 0x10 + (*cur >> 4));
                        }
                    } else if (left & 2) {
                        if (tableFlag) {
                            uint8 b0 = *cur;
                            cur++;
                            uint8 b1 = *cur++;
                            v = (int16)((int16)(int8)(b0 << 4) * 0x100 + (b1 << 4) + (*cur >> 4));
                        } else {
                            int8 b0 = (int8)*cur++;
                            v = (int16)((int16)b0 * 0x100 + *cur++);
                        }
                    } else if (tableFlag) {
                        uint8 b0 = *cur++;
                        v = (int16)((int16)(int8)b0 * 0x100 + *cur++);
                    } else {
                        uint8 b0 = *cur++;
                        v = (int16)((int16)(int8)(b0 << 4) * 0x10 + (*cur >> 4));
                        tableFlag = 1;
                    }
                } else {
                    // succeeding fields always accumulate into the same coordinate
                    if (iX < nX) {
                        if (pairByte & 1) {
                            v = (int16)(*cur * 0x100 + cur[1]);
                            cur += 2;
                        } else {
                            v = (int16)((int16)(int8)*cur + acc);
                            cur++;
                        }
                        acc += v;
                        pts->xs[iX] = (int16)acc;
                        iX++;
                    } else {
                        if (pairByte & 1) {
                            v = (int16)(*cur * 0x100 + cur[1]);
                            cur += 2;
                        } else {
                            v = (int16)((int16)(int8)*cur + acc);
                            cur++;
                        }
                        acc += v;
                        pts->ys[iY] = (int16)acc;
                        iY++;
                    }
                }
                if (iX >= nX && iY >= nY)
                    break;
            }
            guard += 4;
        } while (iX + iY < nX + nY);

        pts->out1 = (uint16)nx;
        pts->out0 = (uint16)ny;
        pts->outCursor = cur;
        return;
    }

    // ---------------- header of a real glyph ----------------
    // The original stores the two counters in the two halfwords of a word local:
    // the second is written first (high half at [esp+0x18]) and the first second
    // (low half at [esp+0x1c]).
    uint16 nX = 0;
    uint16 nY = 0;
    uint16 state = 0;
    uint8 extended = 0;
    switch (flags & 3) {
    case 0:
        break;
    case 1: {
        uint8 b = *cur;
        nX = b & 0xf;
        nY = b >> 4;
        cur++;
        break;
    }
    case 2: {
        uint8 b = *cur++;
        nX = b;
        nY = *cur++;
        break;
    }
    default: {
        extended = 1;
        uint8 b = *cur++;
        nX = b;
        nY = *cur++;
        break;
    }
    }

    int iX = 0;
    int iY = 0;
    int16* dst = pts->xs;
    uint32 acc = 0;
    int left = 0;
    uint8 pairByte = 0;
    for (;;) {
        int sel;
        if (iX < (int16)nX) {
            sel = iX;
            iX++;
            if (sel != 0) {
                if (flags & 0x40) {
                    if (left != 0) {
                        pairByte >>= 1;
                        left--;
                    } else if (extended != 0) {
                        pairByte = *cur++ & 0xf;
                        left = 3;
                        extended = 0;
                    } else {
                        pairByte = *cur >> 4;
                        left = 3;
                        extended = 1;
                    }
                } else {
                    pairByte = 0;
                }
            } else {
                dst = pts->xs;
                pairByte = (flags >> 4) & 1;
            }
        } else if (iY < (int16)nY) {
            sel = iY;
            iY++;
            if (sel != 0) {
                if (flags & 0x40) {
                    if (left != 0) {
                        pairByte >>= 1;
                        left--;
                    } else if (extended != 0) {
                        pairByte = *cur++ & 0xf;
                        left = 3;
                        extended = 0;
                    } else {
                        pairByte = *cur >> 4;
                        left = 3;
                        extended = 1;
                    }
                } else {
                    pairByte = 0;
                }
            } else {
                dst = pts->ys;
                pairByte = (flags >> 5) & 1;
            }
        } else {
            break;
        }
        int16 v;
        if ((pairByte & 1) == 0) {
            if (extended) {
                uint8 b0 = *cur++;
                v = (int16)((int16)(int8)(b0 << 4) * 0x10 + (*cur >> 4));
            } else {
                v = (int16)*cur++;
            }
        } else if (nY & 2) {
            if (extended) {
                uint8 b0 = *cur;
                uint8 b1 = cur[1];
                cur += 2;
                v = (int16)((int16)(int8)(b0 << 4) * 0x100 + b1 * 0x10 + (*cur >> 4));
            } else {
                int8 b0 = (int8)*cur++;
                v = (int16)((int16)b0 * 0x100 + *cur++);
            }
        } else if (extended) {
            uint8 b0 = *cur;
            uint8 b1 = cur[1];
            cur += 2;
            v = (int16)((int16)(int8)(b0 << 4) * 0x10 + b1);
            extended = 0;
        } else {
            uint8 b0 = *cur;
            uint8 b1 = cur[1];
            cur += 1;
            v = (int16)((int16)(int8)(b0 << 4) * 0x10 + (b1 >> 4));
            extended = 1;
        }
        acc += (uint16)v;
        dst[sel] = (int16)acc;
    }

    if (flags & 4) {
        int i = (int16)(nY - 1);
        for (; i >= 0; i--)
            pts->ys[i + 1] = pts->ys[i];
        nY++;
    }
    if (nY & 1) {
        int i = (int16)nY;
        nY++;
        pts->ys[i + 1] = pts->ys[i];
    }
    (void)state;
    pts->out1 = nX;
    pts->out0 = nY;
    pts->outCursor = cur;
}

// ===========================================================================
// @ 0x008b0f10
// tsi_ReadGlyphCoord: read one coordinate from the cursor with the encoding given
// by bits 0-1 of `sel`, then the next coordinate with bits 2-3.
// ===========================================================================
extern "C" void tsi_ReadGlyphCoord(uint8** cursor, uint8 sel, T2KPointSet* pts,
                                   int16* outA, int16* outB)
{
    uint8* cur = *cursor;
    switch (sel & 3) {
    case 0:
        *outA = pts->xs[*cur];
        cur++;
        break;
    case 1:
        *outA = (int16)(*cur * 0x100 + cur[1]);
        cur += 2;
        break;
    case 2:
        *outA = (int16)((int16)(int8)*cur + pts->curX);
        cur++;
        break;
    case 3:
        *outA = pts->curX;
        break;
    }
    pts->curX = *outA;

    switch ((sel >> 2) & 3) {
    case 0:
        *outB = pts->ys[*cur];
        pts->curY = *outB;
        cur++;
        break;
    case 1:
        *outB = (int16)(*cur * 0x100 + cur[1]);
        pts->curY = *outB;
        cur += 2;
        break;
    case 2:
        *outB = (int16)((int16)(int8)*cur + pts->curY);
        pts->curY = *outB;
        cur++;
        break;
    case 3:
        *outB = pts->curY;
        pts->curY = *outB;
        break;
    }
    *cursor = cur;
}

// ===========================================================================
// @ 0x008b1040
// Nibble reader, high nibble first.  The object is passed in ECX.
// ===========================================================================
struct NibSrcTC {
    uint8* cur;                    // 0x00
    uint16 half;                   // 0x04
    uint8 ReadHi();                // 0x008b1040
};

uint8 NibSrcTC::ReadHi()
{
    if (half == 0) {
        half = 1;
        return *cur >> 4;
    }
    half = 0;
    uint8 v = (uint8)(*cur & 0xf);
    cur = cur + 1;
    return v;
}

// ===========================================================================
// @ 0x008b1070
// Nibble reader, low nibble first.  The object arrives in EDX in the original
// (a TU-local static register convention); modelled as a static with a dead
// first argument (EAX) so the object lands in EDX.
// ===========================================================================
static int8 ReadNibbleLo(int dummy, NibSrcTC* s)
{
    (void)dummy;
    if (s->half == 0) {
        uint8* p = s->cur;
        uint8 v = *p;
        s->cur = p + 1;
        return (int8)v;
    }
    uint8 b0 = *s->cur;
    uint8* p = s->cur + 1;
    s->cur = p;
    int b1 = *p;
    b0 <<= 4;
    return (int8)((b1 >> 4) + b0);
}
extern "C" int8 ReadNibbleLo_(NibSrcTC* s) { return ReadNibbleLo(7, s); }

// ===========================================================================
// @ 0x008b10a0
// tsi_FindCoordIndex: pick a coordinate from the x or y table.
//   pts    arrives in EAX
//   dirHint arrives in ECX (a signed direction / search hint; 0 = derive it)
//   useY   is the stack argument (0 = x table, non-zero = y table)
// The original is a TU-local static (register convention); modelled as a static
// with a stand-in caller.
// ===========================================================================
static int FindCoordIndex(T2KPointSet* pts, int dirHint, int16 useY)
{
    int16* arr;
    int    count;
    int    ref;
    int    acc;
    if (useY == 0) {
        arr   = pts->xs;
        count = (uint16)pts->nx;
        ref   = (uint16)pts->out1;
        acc   = (uint16)pts->curX;
    } else {
        arr   = pts->ys;
        count = (uint16)pts->ny;
        ref   = (uint16)pts->out0;
        acc   = (uint16)pts->curY;
    }

    int dir = (int16)dirHint;
    if (dir == 0) {
        if ((int16)acc > (int16)ref)
            dir = 1;
        else if ((int16)acc < (int16)ref)
            dir = -1;
        else
            return acc;
    }

    if (dir > 0) {
        for (int i = 0; i < (int16)count; i++) {
            if (arr[i] > (int16)acc) {
                int idx = i + dir - 1;
                if (idx >= (int16)count)
                    idx = count - 1;
                return arr[idx];
            }
        }
        return acc;
    }

    for (int i = (int16)count - 1; i >= 0; i--) {
        if (arr[i] < (int16)acc) {
            int idx = i + dir + 1;
            if (idx < 0)
                idx = 0;
            return arr[idx];
        }
    }
    return acc;
}
extern "C" int FindCoordIndex_(T2KPointSet* pts, int dirHint, int16 useY)
{
    return FindCoordIndex(pts, dirHint, useY);
}

// ===========================================================================
// @ 0x008b1160
// SkipExtraStreamItems: read a count byte, then skip that many byte-counted items.
// ===========================================================================
static __forceinline uint8 ReadByteRaw(InputStream* in)
{
    if (in->privateBase == 0) {
        uint32 pos = in->pos;
        in->pos = pos + 1;
        if (in->readToRam(in->nonRamID, &in->tmp_ch, pos, 1) < 0) {
            tsi_Error(in->mem, 0x2728);
            return 0;
        }
        return in->tmp_ch;
    }
    if (in->readToRam == 0) {
        uint8 b = in->privateBase[in->pos];
        in->pos = in->pos + 1;
        return b;
    }
    if (in->cacheCount < (in->pos - in->posZero) + 1)
        PrimeT2KInputStream(in);
    uint8 b = in->privateBase[in->pos - in->posZero];
    in->pos = in->pos + 1;
    return b;
}

static void SkipExtraStreamItems(InputStream* in)
{
    int16 n = (int16)ReadByteRaw(in);
    while (n > 0) {
        uint8 len = ReadByteRaw(in);
        Seek_InputStream(in, Tell_InputStream(in) + len + 1);
        n--;
    }
}
extern "C" void SkipExtraStreamItems_(InputStream* in) { SkipExtraStreamItems(in); }

// ===========================================================================
// @ 0x008b12e0
// New_pfrkernSubTable0Data: build sub-table 0 (char code -> kern array) of a PFR
// kern table from its packed blob.  `data` arrives in EAX (register helper).
// ===========================================================================
struct PFRKernSubTable {
    tsiMemObject* mem;            // 0x00
    uint16        count;          // 0x04
    uint16        f06;            // 0x06
    uint16        f08;            // 0x08
    uint16        f0a;            // 0x0a
    uint32*       entries;        // 0x0c  count * 8 bytes of packed entries
};

extern "C" PFRKernSubTable* New_pfrkernSubTable0Data(uint8* data, tsiMemObject* mem, uint16 firstChar)
{
    PFRKernSubTable* kt = (PFRKernSubTable*)tsi_AllocMem(mem, 0x10);
    uint8* p;
    uint16 count = 0;
    uint16 entryIdx = 0;
    uint16 next;

    p = data;
    do {
        p += (int16)firstChar;
        count = (uint16)(count + *p);
        next = *(uint16*)(p + 1);
        p += 3;
        firstChar = next;
    } while (next == 4);

    kt->mem = mem;
    kt->count = count;
    kt->entries = (uint32*)tsi_AllocMem(mem, count * 8);

    do {
        uint8 nb = p[0];
        uint16 groupStart = entryIdx;
        uint16 groupEnd = (uint16)(groupStart + nb);
        uint8 pack = p[3];
        kt->f06 = 0;
        kt->f08 = 0;
        kt->f0a = 0;
        p += 4;
        for (; groupStart < groupEnd; entryIdx++, groupStart++) {
            uint16 v1, v2;
            if ((pack & 1) == 0) {
                v1 = (uint16)(p[0] * 0x100 + p[1]);
                p += 2;
                v2 = (uint16)(p[0] * 0x100 + p[1]);
                p += 2;
            } else {
                v1 = (uint16)(p[0] * 0x100 + p[1]);
                v2 = (uint16)(p[2] * 0x100 + p[3]);
                p += 4;
            }
            kt->entries[entryIdx] = ((uint32)v1 << 16) | v2;
        }
        next = *(uint16*)(p + 1);
        p += 2;
    } while (next == 4);
    return kt;
}
