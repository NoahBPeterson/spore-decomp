// Slice s008c9000 -- T2K (Type 2000 font scaler) scan converter: MakeBits (0x008c9000, 2669 bytes).
//
// Turns the edge lists collected by the scan converter (one sorted intersection list per
// scanline in yEdgeHead[], and, for dropout control and grey scale, one per column in
// xEdgeHead[]) into a bitmap:
//   * computes the bitmap box from the scan bbox (optionally widened by one pixel on the
//     left/bottom for synthetic emboldening), allocates and clears the bitmap (through the
//     caller's cache callback, else tsi_FastAllocN);
//   * grey scale (greyScaleLevel > 0): accumulates the horizontal coverage of every span with
//     non-zero winding into the 0..126 cells, then folds the vertical coverage in, mixing
//     partial values with a weighted blend; finally expands to 0..255 or remaps the levels;
//   * mono: fills every span between pixel centres, then does x and y dropout control
//     (optionally ignoring stubs, IsStub) and records whether dropouts were added.
//
// Names: function and tsiScanConv members are dev-PDB names (pdb_candidates: MakeBits,
// IsStub, CountInterSections, ComputeScanBBox); parameter and local names are Claude-coined.
// IsStub and CountInterSections are static helpers with cl's register convention for
// same-TU statics (IsStub: y in eax, maxIndex in ecx); they are defined here so the call
// sites get that convention. Only MakeBits is claimed by this slice.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE  (cmovl in the y-dropout clamp)
#include "types.h"

typedef uint8_t uint8;
typedef int32_t int32;

struct tsiMemObject;

struct T2KInterSectType {          // size 0x8
    long coordinate25Dot6_flag1;   // 2 * coordinate (26.6) + direction flag
    T2KInterSectType* next;
};

struct tsiScanConv {               // size 0x2238 (dev PDB)
    long prevX0;                   // +0x0
    long prevY0;                   // +0x4
    long left;                     // +0x8
    long right;                    // +0xc
    long top;                      // +0x10
    long bottom;                   // +0x14
    long fTop26Dot6;               // +0x18
    long fLeft26Dot6;              // +0x1c
    long rowBytes;                 // +0x20
    unsigned char* baseAddr;       // +0x24
    int internal_baseAddr;         // +0x28
    int scanBBoxIsComputed;        // +0x2c
    long xminSC;                   // +0x30
    long xmaxSC;                   // +0x34
    long yminSC;                   // +0x38
    long ymaxSC;                   // +0x3c
    long outlineXMin;              // +0x40
    long outlineXMax;              // +0x44
    long outlineYMin;              // +0x48
    long outlineYMax;              // +0x4c
    int couldOverflowIntegerMath;  // +0x50
    T2KInterSectType* yBaseBuffer[32];      // +0x54
    T2KInterSectType** yEdgeHead;  // +0xd4
    T2KInterSectType** yBase;      // +0xd8
    long minYIndex;                // +0xdc
    long maxYIndex;                // +0xe0
    T2KInterSectType* xBaseBuffer[32];      // +0xe4
    T2KInterSectType** xEdgeHead;  // +0x164
    T2KInterSectType** xBase;      // +0x168
    long minXIndex;                // +0x16c
    long maxXIndex;                // +0x170
    T2KInterSectType* free;        // +0x174
    T2KInterSectType* freeEnd;     // +0x178
    T2KInterSectType firstMemBlockBuffer[1024];   // +0x17c
    T2KInterSectType* freeMemBlocksBuffer[32];    // +0x217c
    T2KInterSectType** freeMemBlocks;       // +0x21fc
    long freeMemBlockMaxCount;     // +0x2200
    long freeMemBlockN;            // +0x2204
    long maxError;                 // +0x2208
    unsigned char greyScaleLevel;  // +0x220c
    char xDropOutControl;          // +0x220d
    char yDropOutControl;          // +0x220e
    char includeStubs;             // +0x220f
    char smartDropout;             // +0x2210
    char doXEdges;                 // +0x2211
    int weDidXDropouts;            // +0x2214
    int weDidYDropouts;            // +0x2218
    short* startPoint;             // +0x221c
    short* endPoint;               // +0x2220
    short numberOfContours;        // +0x2224
    long* x;                       // +0x2228
    long* y;                       // +0x222c
    char* onCurve;                 // +0x2230
    tsiMemObject* mem;             // +0x2234
};

typedef void* (*FF_GetCacheMemoryPtr)(void* theCache, long size);

void* tsi_FastAllocN(tsiMemObject* mem, int32 size, int32 tag);   // 0x008d14d0
void ComputeScanBBox(tsiScanConv* t);                              // 0x008c79c0
extern "C" void* memset(void* dst, int c, unsigned int n);         // 0x011e073e

#define T2K_SCAN_BITMAP 5

// Counts the intersections of list p within [lo-4, hi+4] (stops at 2). @ 0x008c8eb0
static int CountInterSections(int count, T2KInterSectType* p, long lo, long hi)
{
    if (p != 0) {
        T2KInterSectType* q = p->next;
        hi += 4;
        lo -= 4;
        do {
            long a = p->coordinate25Dot6_flag1 >> 1;
            long b = q->coordinate25Dot6_flag1 >> 1;
            if (a > hi)
                break;
            if (a >= lo && ++count >= 2)
                break;
            if (b > hi)
                break;
            if (b >= lo && ++count >= 2)
                break;
            p = q->next;
            if (p == 0)
                break;
            q = p->next;
        } while (q != 0);
    }
    return count;
}

// A dropout candidate is a stub if the outline does not continue on both sides of the
// scanline (line y, columns x1..x2) on the neighbouring scanline above or below. @ 0x008c8f00
static int IsStub(long y, long maxIndex, T2KInterSectType** edgeHead, T2KInterSectType** otherEdgeHead,
                  long x1, long x2, long minIndex)
{
    long yUp = y + 1;
    long yDown = y - 1;
    long yC = (y << 6) + 32;
    int count;

    if (((yUp >= maxIndex) ? 1 : 0) < maxIndex) {
        count = CountInterSections(0, edgeHead[yUp], (x1 << 6) + 32, (x2 << 6) + 32);
        if (count >= 2)
            goto below;
    } else {
        count = 0;
    }
    count = CountInterSections(count, otherEdgeHead[x1], yC, (yUp << 6) + 32);
    if (count >= 2)
        goto below;
    count = CountInterSections(count, otherEdgeHead[x2], yC, (yUp << 6) + 32);
    if (count >= 2)
        goto below;
    return 1;

below:
    if (yDown < minIndex) {
        count = 0;
    } else {
        count = CountInterSections(0, edgeHead[yDown], (x1 << 6) + 32, (x2 << 6) + 32);
        if (count >= 2)
            return 0;
    }
    count = CountInterSections(count, otherEdgeHead[x1], (yDown << 6) + 32, yC);
    if (count >= 2)
        return 0;
    count = CountInterSections(count, otherEdgeHead[x2], (yDown << 6) + 32, yC);
    if (count >= 2)
        return 0;
    return 1;
}

// Weighted mix of two grey levels (0..63 coverage, stored doubled).
static __inline uint8 MixGrey(int a, int d)
{
    int wd = 63 - d;
    int wa = 63 - a;
    wd = (63 * 63 + 1) - wd * wd;
    wa = (63 * 63 + 1) - wa * wa;
    return (uint8)((a * wa + d * wd) / (wa + wd));
}

// @ 0x008c9000
void MakeBits(tsiScanConv* t, char xWeightIsOne, char omitBitMap, FF_GetCacheMemoryPtr funcptr,
              void* theCache, int bitRange255, uint8* remapBits, int emboldenDir)
{
    unsigned char greyScaleLevel = t->greyScaleLevel;
    long xmin, xmax, ymin, ymax;
    long left, right, top, bottom, width, height, rowBytes, N;
    long xmid, ymid;
    long y, x;
    uint8* baseAddr;

    if (t->scanBBoxIsComputed == 0)
        ComputeScanBBox(t);

    xmin = t->xminSC;
    if (emboldenDir == 1)
        xmin -= 64;
    xmax = t->xmaxSC;
    ymin = t->yminSC;
    ymax = t->ymaxSC;
    if (emboldenDir == 2)
        ymin -= 64;
    xmid = (xmax + xmin) >> 1;
    ymid = (ymax + ymin) >> 1;

    t->fTop26Dot6 = ymax + 64;
    t->fLeft26Dot6 = xmin;
    t->right = right = (xmax + 64) >> 6;
    t->left = left = xmin >> 6;
    t->top = top = ymin >> 6;
    t->bottom = bottom = (ymax + 64) >> 6;
    width = right - left;
    height = bottom - top;
    if (greyScaleLevel == 0)
        rowBytes = (width + 7) / 8;
    else
        rowBytes = width;
    t->rowBytes = rowBytes;
    t->baseAddr = 0;
    t->internal_baseAddr = 0;
    if (omitBitMap)
        return;

    N = rowBytes * height;
    baseAddr = 0;
    if (funcptr != 0)
        baseAddr = (uint8*)funcptr(theCache, N);
    if (funcptr == 0 || baseAddr == 0) {
        baseAddr = (uint8*)tsi_FastAllocN(t->mem, N, T2K_SCAN_BITMAP);
        t->internal_baseAddr = 1;
    }
    t->baseAddr = baseAddr;
    {
        long i, n4 = N >> 2;
        long* lp = (long*)baseAddr;
        for (i = 0; i < n4; i++)
            lp[i] = 0;
        for (i <<= 2; i < N; i++)
            baseAddr[i] = 0;
    }

    if (t->minYIndex <= t->maxYIndex && t->maxYIndex >= bottom)
        t->maxYIndex = bottom - 1;

    if (greyScaleLevel > 0) {
        long heightM1 = height - 1;
        uint8* rowPtr = baseAddr + (heightM1 - t->minYIndex + top) * rowBytes - left;

        // horizontal coverage
        for (y = t->minYIndex; y <= t->maxYIndex; y++, rowPtr -= rowBytes) {
            T2KInterSectType* p = t->yEdgeHead[y];
            if (p == 0)
                continue;
            T2KInterSectType* q = p->next;
            int winding = 0;
            for (;;) {
                long c1 = p->coordinate25Dot6_flag1;
                long c2 = q->coordinate25Dot6_flag1;
                winding += ((c2 & 1) + (c1 & 1)) * 2 - 2;
                while (winding != 0) {
                    q = q->next;
                    c2 = q->coordinate25Dot6_flag1;
                    winding += (c2 & 1) * 2 - 1;
                }
                long x1 = c1 >> 1;
                long x2 = c2 >> 1;
                long ix1 = x1 >> 6;
                long ix2 = x2 >> 6;
                if (ix1 == ix2) {
                    rowPtr[ix1] += (uint8)(((x2 & 63) - (x1 & 63)) * 2);
                } else {
                    rowPtr[ix1] += (uint8)((63 - (x1 & 63)) * 2);
                    ix1++;
                    if (ix1 < ix2 && ((long)(rowPtr + ix1) & 1)) {
                        rowPtr[ix1] = 126;
                        ix1++;
                    }
                    for (; ix1 < ix2; ix1 += 2)
                        *(unsigned short*)(rowPtr + ix1) = 0x7e7e;
                    rowPtr[ix2] = (uint8)((x2 & 63) * 2);
                }
                p = q->next;
                if (p == 0)
                    break;
                q = p->next;
                if (q == 0)
                    break;
            }
        }

        // vertical coverage
        long col = t->minXIndex - left;
        for (x = t->minXIndex; x <= t->maxXIndex; x++, col++) {
            T2KInterSectType* p = t->xEdgeHead[x];
            uint8* pending = 0;
            uint8 acc = 0;
            if (p == 0)
                continue;
            T2KInterSectType* q = p->next;
            int winding = 0;
            for (;;) {
                long c1 = p->coordinate25Dot6_flag1;
                long c2 = q->coordinate25Dot6_flag1;
                winding += ((c2 & 1) + (c1 & 1)) * 2 - 2;
                while (winding != 0) {
                    q = q->next;
                    c2 = q->coordinate25Dot6_flag1;
                    winding += (c2 & 1) * 2 - 1;
                }
                long y1 = c1 >> 1;
                long y2 = c2 >> 1;
                long iy1 = y1 >> 6;
                long iy2 = y2 >> 6;
                long off = (heightM1 - iy1 + top) * rowBytes + col;
                if (pending != 0 && pending != baseAddr + off) {
                    *pending = MixGrey(*pending, acc);
                    acc = 0;
                }
                if (iy1 == iy2) {
                    acc += (uint8)(((y2 & 63) - (y1 & 63)) * 2);
                    pending = baseAddr + off;
                } else {
                    acc += (uint8)((63 - (y1 & 63)) * 2);
                    baseAddr[off] = MixGrey(baseAddr[off], acc);
                    pending = baseAddr + (heightM1 - iy2 + top) * rowBytes + col;
                    acc = (uint8)((y2 & 63) * 2);
                }
                p = q->next;
                if (p == 0)
                    break;
                q = p->next;
                if (q == 0)
                    break;
            }
            if (pending != 0)
                *pending = MixGrey(*pending, acc);
        }

        if (bitRange255) {
            for (long i = 0; i < N; i++)
                baseAddr[i] = (uint8)((baseAddr[i] << 1) + (baseAddr[i] >> 5));
        } else if (remapBits != 0) {
            for (long i = 0; i < N; i++)
                baseAddr[i] = remapBits[baseAddr[i]];
        }
        return;
    }

    // mono fill
    {
        uint8* rowPtr = baseAddr + (height - t->maxYIndex + top - 1) * rowBytes;
        for (y = t->maxYIndex; y >= t->minYIndex; y--, rowPtr += rowBytes) {
            T2KInterSectType* p = t->yEdgeHead[y];
            if (p == 0)
                continue;
            T2KInterSectType* q = p->next;
            int winding = 0;
            for (;;) {
                long c1 = p->coordinate25Dot6_flag1;
                long c2 = q->coordinate25Dot6_flag1;
                winding += ((c2 & 1) + (c1 & 1)) * 2 - 2;
                while (winding != 0) {
                    q = q->next;
                    c2 = q->coordinate25Dot6_flag1;
                    winding += (c2 & 1) * 2 - 1;
                }
                long ix1 = (c1 + 62) >> 7;
                long ix2 = (c2 + 64) >> 7;
                if (ix1 < ix2) {
                    ix1 -= left;
                    ix2 += -1 - left;
                    long b1 = ix1 >> 3;
                    long b2 = ix2 >> 3;
                    uint8 mask = (uint8)(0xff >> (ix1 & 7));
                    if (b1 == b2) {
                        rowPtr[b1] |= mask & (uint8)(0xff80 >> (ix2 & 7));
                    } else {
                        rowPtr[b1] |= mask;
                        b1++;
                        if (b1 < b2 && ((long)(rowPtr + b1) & 1)) {
                            rowPtr[b1] = 0xff;
                            b1++;
                        }
                        for (; b1 < b2; b1 += 2)
                            *(unsigned short*)(rowPtr + b1) = 0xffff;
                        rowPtr[b2] = (uint8)(0xff80 >> (ix2 & 7));
                    }
                }
                p = q->next;
                if (p == 0)
                    break;
                q = p->next;
                if (q == 0)
                    break;
            }
        }
    }

    // x dropout control: horizontal spans narrower than a pixel that set no pixel
    if (t->xDropOutControl) {
        int weDidDropouts = 0;
        long rowOff = (height - t->minYIndex + top - 1) * rowBytes;
        long rowStep = -rowBytes;
        for (y = t->minYIndex; y <= t->maxYIndex; y++, rowOff += rowStep) {
            T2KInterSectType* p = t->yEdgeHead[y];
            T2KInterSectType* q;
            if (p == 0 || (q = p->next) == 0)
                continue;
            int winding = 0;
            for (;;) {
                long c1 = p->coordinate25Dot6_flag1;
                long c2 = q->coordinate25Dot6_flag1;
                winding += ((c2 & 1) + (c1 & 1)) * 2 - 2;
                while (winding != 0) {
                    q = q->next;
                    c2 = q->coordinate25Dot6_flag1;
                    winding += (c2 & 1) * 2 - 1;
                }
                long x2 = c2 >> 1;
                long x1 = c1 >> 1;
                if (x2 - x1 < 64) {
                    long i1 = ((x2 + x1 - 64) >> 7) - left;
                    long i2 = i1 + 1;
                    if (i1 < 0)
                        i1 = 0;
                    if (i2 >= width)
                        i2 = width - 1;
                    if (!(baseAddr[(i1 >> 3) + rowOff] & (0x80 >> (i1 & 7))) &&
                        !(baseAddr[(i2 >> 3) + rowOff] & (0x80 >> (i2 & 7)))) {
                        long xa = c1 >> 1;
                        long xb = q->coordinate25Dot6_flag1 >> 1;
                        if (!t->includeStubs &&
                            IsStub(y, bottom, t->yEdgeHead, t->xEdgeHead, (xa - 32) >> 6, (xb + 32) >> 6, top))
                            goto nextX;
                        if (t->smartDropout) {
                            if (xa > xmid)
                                xa = (xa + xb - 2) >> 1;
                            else
                                xa = (xa + xb + 1) >> 1;
                        }
                        xa = (xa >> 6) - left;
                        baseAddr[(xa >> 3) + rowOff] |= (uint8)(0x80 >> (xa & 7));
                        weDidDropouts = 1;
                    }
                }
            nextX:
                p = q->next;
                if (p == 0)
                    break;
                q = p->next;
                if (q == 0)
                    break;
            }
        }
        t->weDidXDropouts |= weDidDropouts;
    }

    // y dropout control: vertical spans shorter than a pixel that set no pixel
    if (t->yDropOutControl) {
        int weDidDropouts = 0;
        long col = t->minXIndex - left;
        for (x = t->minXIndex; x <= t->maxXIndex; x++, col++) {
            T2KInterSectType* p = t->xEdgeHead[x];
            T2KInterSectType* q;
            if (p == 0 || (q = p->next) == 0)
                continue;
            int winding = 0;
            for (;;) {
                long c1 = p->coordinate25Dot6_flag1;
                long c2 = q->coordinate25Dot6_flag1;
                winding += ((c2 & 1) + (c1 & 1)) * 2 - 2;
                while (winding != 0) {
                    q = q->next;
                    c2 = q->coordinate25Dot6_flag1;
                    winding += (c2 & 1) * 2 - 1;
                }
                long y2 = c2 >> 1;
                long y1 = c1 >> 1;
                if (y2 - y1 < 64) {
                    long i1 = (y2 + y1 - 64) >> 7;
                    long i2 = i1 + 1;
                    if (i1 < top)
                        i1 = top;
                    if (i2 >= bottom)
                        i2 = bottom - 1;
                    uint8 bit = (uint8)(0x80 >> (col & 7));
                    if (!(baseAddr[(height - i1 + top - 1) * rowBytes + (col >> 3)] & bit) &&
                        !(baseAddr[(height - i2 + top - 1) * rowBytes + (col >> 3)] & bit)) {
                        long yb = q->coordinate25Dot6_flag1 >> 1;
                        long ya = c1 >> 1;
                        if (!t->includeStubs &&
                            IsStub(x, right, t->xEdgeHead, t->yEdgeHead, (ya - 32) >> 6, (yb + 32) >> 6, left))
                            goto nextY;
                        if (t->smartDropout) {
                            if (ya > ymid)
                                ya = (ya + yb - 2) >> 1;
                            else
                                ya = (ya + yb + 1) >> 1;
                        }
                        baseAddr[(height - (ya >> 6) + top - 1) * rowBytes + (col >> 3)] |= bit;
                        weDidDropouts = 1;
                    }
                }
            nextY:
                p = q->next;
                if (p == 0)
                    break;
                q = p->next;
                if (q == 0)
                    break;
            }
        }
        t->weDidYDropouts |= weDidDropouts;
    }
}
