// Slice s008c8920 -- T2K (Type 2000 font scaler) edge-list builders and the scan-converter
// constructor.  The image object is the tsiScanConv record (size 0x2238); the layout is the
// retail one (member offsets confirmed against the disassembly) and matches the declaration
// used by the neighbouring slices s008c6e80/s008c9000.
//
//   Make2ndDegreeEdgeList : walks the quadratic outline (startPoint/endPoint point into the
//                           point list; x/y hold 26.6 coords, onCurve flags the control
//                           points) and buckets the on-curve runs into the x/y scanline edge
//                           lists (drawLine) or adaptively subdivides the quadratics
//                           (drawParabola).
//   tsi_NewScanConv       : allocates a scan converter, fills its parameters, computes the
//                           outline bbox and the row/column edge-list bases, then dispatches
//                           to Make2ndDegreeEdgeList (degree != 3) or Make3rdDegreeEdgeList.
//   CountInterSections    : static helper (count in eax, list in ecx, hi in edx, lo on the
//                           stack) that counts list intersections in [lo-4, hi+4], stopping
//                           at 2.
//   IsStub                : static helper (y in eax, maxIndex in ecx) that reports whether a
//                           dropout candidate continues on neither neighbouring scanline.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef uint8_t  uint8;
typedef int32_t  int32;
typedef uint32_t uint32;

struct tsiMemObject;

// One entry of a scanline / column edge list: 2 * coordinate (26.6) + the curve-direction bit.
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

// Static helpers of this TU (register conventions as the original: see their definitions).
static int  CountInterSections(int count, T2KInterSectType* p, long lo, long hi);   // 0x008c8eb0
static int  IsStub(long y, long maxIndex, T2KInterSectType** edgeHead,
                   T2KInterSectType** otherEdgeHead, long x1, long x2, long minIndex); // 0x008c8f00

// The rasterizer entry points live in a neighbouring translation unit (slice s008c7c40).
// drawLine is entered with ecx = the (unused) onCurve base, edx = t and x0..y1 on the stack;
// the retail routine ends in a plain `ret`, so the caller must pop the four stack arguments.
// MSVC's __fastcall places ecx/edx correctly but has the callee pop them, hence the explicit
// `add esp, 16` after each call (an ABI detail no C declaration can express).
void __fastcall drawLine(void* unused, tsiScanConv* t, long x0, long y0, long x1, long y1); // 0x008c7c40

// 0x008c8220 drawParabola: the retail routine is a register-ABI fragment (P0x in eax, P0y
// in edx, P1y in ecx and only ras/x2/y2/x1 on the stack), so it cannot be called from a C
// declaration -- see match/slices/s008c7c40/nonmatching.txt.  Like the neighbouring slices we
// call it from a single __asm block, setting the register arguments exactly; the retail routine
// ends in a plain `ret`, so the caller pops the four stack arguments.
extern "C" void FUN_008c8220(void);              // drawParabola

// Quadratic segment P0 -> P1 -> P2.  The retail caller passes P0=(px0,py0), P1=(ctrlX,ctrlY)
// and P2=(lastX,lastY); the emitted chord orientation therefore matters (drawLine records its
// first point in ras->prevX0/prevY0).  Inline __asm (not a macro) keeps the statement
// separators the inline assembler needs.

void* tsi_FastAllocN(tsiMemObject* mem, int32 size, int32 tag);                      // 0x008d14d0
T2KInterSectType* tsi_AllocMem(tsiMemObject* mem, int32 size);                       // 0x008d1260
// 0x008c7be0 ComputeOutlineBBox: another register-ABI routine (eax = x row table, ebx = output
// record, stack: y row table, last point index).  Called from __asm like drawParabola.
extern "C" void FUN_008c7be0(void);                                                  // ComputeOutlineBBox
extern "C" void FUN_008c77d0(void);   // AllocFreeNodes: esi = t, no stack arguments
void Make3rdDegreeEdgeList(tsiScanConv* t);                                          // 0x008c8720

// @ 0x008c8920
void Make2ndDegreeEdgeList(tsiScanConv* t)
{
    long* xArr = t->x;
    long* yArr = t->y;
    char* onCurve = t->onCurve;
    long contour = 0;

    for (;;) {
        if ((long)t->numberOfContours <= contour)
            return;

        long start = t->startPoint[contour];
        long end = t->endPoint[contour];
        long cur;
        long last;
        long lastX, lastY;
        long ctrlX, ctrlY;
        long x1, y1;

        if (onCurve[start] == 0) {
            // The contour starts on an off-curve control point: seed the walk with the
            // last point (or the start/end midpoint when that one is off-curve too).
            ctrlX = xArr[start];
            ctrlY = yArr[start];
            lastX = xArr[end];
            lastY = yArr[end];
            if (onCurve[end] == 0) {
                lastX = (ctrlX + 1 + lastX) >> 1;
                lastY = (ctrlY + 1 + lastY) >> 1;
                if ((lastX & 0x3f) == 0x20) {
                    lastX = lastX - 1;
                    xArr[start] = ctrlX - 1;
                    xArr[end] = xArr[end] - 1;
                }
                if ((lastY & 0x3f) == 0x20) {
                    yArr[start] = yArr[start] - 1;
                    yArr[end] = yArr[end] - 1;
                    lastY = lastY - 1;
                }
            } else {
                if ((lastX & 0x3f) == 0x20) {
                    lastX = lastX - 1;
                    xArr[end] = lastX;
                }
                if ((lastY & 0x3f) == 0x20) {
                    yArr[end] = lastY - 1;
                    lastY = lastY - 1;
                }
            }
            last = end;
            cur = start;
        } else {
            // The contour starts on-curve: nudge coincident/rounded start points so the
            // first edge does not collapse.
            lastX = xArr[start];
            lastY = yArr[start];
            ctrlX = 0;
            ctrlY = 0;
            cur = -1;
            if ((lastX & 0x3f) == 0x20) {
                long v = xArr[end];
                t->prevX0 = v;
                if (onCurve[end] == 0) {
                    lastX = lastX - 1;
                    xArr[start] = lastX;
                } else if (v == lastX) {
                    if (end != start && onCurve[end - 1] != 0)
                        t->prevX0 = xArr[end - 1];
                    if (t->prevX0 == lastX) {
                        lastX = lastX - 1;
                        xArr[start] = lastX;
                    }
                }
            }
            last = start;
            if ((lastY & 0x3f) == 0x20) {
                long v = yArr[end];
                t->prevY0 = v;
                if (onCurve[end] == 0) {
                    yArr[start] = lastY - 1;
                    lastY = lastY - 1;
                } else if (v == lastY) {
                    if (end != start && onCurve[end - 1] != 0)
                        t->prevY0 = yArr[end - 1];
                    if (t->prevY0 == lastY) {
                        yArr[start] = lastY - 1;
                        lastY = lastY - 1;
                    }
                }
            }
        }

        if (cur < 0)
            goto lineLoop;

    quadLoop:
        for (;;) {
            long idx = cur + 1;
            if (idx > end)
                idx = start;
            x1 = xArr[idx];
            y1 = yArr[idx];
            if (onCurve[idx] != 0) {
                // On-curve end point: one quadratic from the last point through ctrl.
                __asm {
                    push ctrlX
                    mov  ecx, ctrlY
                    push lastY
                    mov  edx, t
                    push lastX
                    push t
                    mov  edx, y1
                    mov  eax, x1
                    call FUN_008c8220
                    add  esp, 16
                }
                lastX = x1;
                lastY = y1;
                last = idx;
                if (idx == start)
                    goto nextContour;
                goto lineLoop;
            }
            // Next point is a control point too: draw to the start/next midpoint and
            // keep subdividing the quadratic.
            long midX = (x1 + ctrlX + 1) >> 1;
            long midY = (y1 + ctrlY + 1) >> 1;
            __asm {
                push ctrlX
                mov  ecx, ctrlY
                push lastY
                mov  edx, t
                push lastX
                push t
                mov  edx, midY
                mov  eax, midX
                call FUN_008c8220
                add  esp, 16
            }
            if (idx == start)
                goto nextContour;
            ctrlX = x1;
            ctrlY = y1;
            last = cur;
            lastX = midX;
            lastY = midY;
            cur = idx;
        }

    lineLoop:
        for (;;) {
            long idx = last + 1;
            if (idx > end)
                idx = start;
            x1 = xArr[idx];
            y1 = yArr[idx];
            ctrlX = x1;
            ctrlY = y1;
            if (onCurve[idx] == 0) {
                // Control point: switch to the quadratic walk (unless the contour wrapped).
                if (idx == start)
                    goto nextContour;
                cur = idx;
                goto quadLoop;
            }
            drawLine(t->onCurve, t, lastX, lastY, x1, y1);
            __asm { add esp, 16 }           // retail drawLine returns with a plain ret
            lastX = x1;
            lastY = y1;
            last = idx;
            if (idx == start)
                goto nextContour;
        }

    nextContour:
        ++contour;
    }
}

// @ 0x008c8c30
tsiScanConv* tsi_NewScanConv(tsiMemObject* mem, short parm2, short* parm3, short* parm4,
                             long* parm5, long* parm6, char* parm7, char greyScaleLevel,
                             char xDropOut, char yDropOut, char includeStubs, int parm12,
                             char parm13, int parm14, int parm15)
{
    tsiScanConv* t = (tsiScanConv*)tsi_FastAllocN(mem, 0x2238, 4);
    t->smartDropout = parm12 != 0;
    t->mem = mem;
    t->includeStubs = parm13 != 0;
    if (parm13 == 0 && (yDropOut != 0 || includeStubs != 0)) {
        includeStubs = 1;
        yDropOut = 1;
    }
    t->greyScaleLevel = greyScaleLevel;
    if (parm15 == 0)
        t->maxError = (greyScaleLevel != 0) ? 4 : 2;
    else
        t->maxError = 2;
    if (t->maxError < parm14)
        t->maxError = parm14;
    if (0x10 < t->maxError)
        t->maxError = 0x10;
    t->xDropOutControl = yDropOut;
    t->yDropOutControl = includeStubs;
    if (parm15 != 0) {
        t->doXEdges = 1;
    } else {
        t->doXEdges = (includeStubs != 0 || greyScaleLevel != 0) ? 1 : 0;
    }
    t->numberOfContours = parm2;
    t->startPoint = parm3;
    t->weDidXDropouts = 0;
    t->weDidYDropouts = 0;
    t->scanBBoxIsComputed = 0;
    t->endPoint = parm4;
    t->x = parm5;
    t->y = parm6;
    t->onCurve = parm7;
    {
        long lastPoint = parm4[parm2 - 1];
        __asm {
            push ebx
            push lastPoint
            push parm6
            mov  eax, parm5
            mov  ebx, t
            call FUN_008c7be0
            add  esp, 8
            pop  ebx
        }
    }
    {
        long diffY = t->outlineXMax - t->outlineXMin;
        t->couldOverflowIntegerMath = 0;
        if (diffY >= 0xb504 || t->outlineYMax - t->outlineYMin >= 0xb504)
            t->couldOverflowIntegerMath = 1;
    }
    {
        int pass = 0;
        long hi = t->outlineXMax;
        long lo = t->outlineXMin;
        for (;;) {
            hi = (hi + 0x40) >> 6;
            lo = (lo - 0x40) >> 6;
            long n = (hi - lo) + 1;
            if (pass == 0 && t->doXEdges == 0) {
                t->xBase = 0;
                t->minXIndex = lo;
                t->maxXIndex = hi;
                t->xEdgeHead = 0;
            } else {
                T2KInterSectType** base;
                if (n <= 0x20)
                    base = (pass == 0) ? t->xBaseBuffer : t->yBaseBuffer;
                else
                    base = (T2KInterSectType**)tsi_AllocMem(t->mem, n * 4);
                for (long k = 0; k < n; k++)
                    base[k] = 0;
                if (pass == 0) {
                    t->xBase = base;
                    t->xEdgeHead = &base[-lo];
                    t->minXIndex = lo;
                    t->maxXIndex = hi;
                } else {
                    t->yBase = base;
                    t->yEdgeHead = &base[-lo];
                    t->minYIndex = lo;
                    t->maxYIndex = hi;
                }
            }
            ++pass;
            if (pass > 1) {
                t->freeMemBlockMaxCount = 0;
                __asm {
                    push esi
                    mov  esi, t
                    call FUN_008c77d0
                    pop  esi
                }
                t->baseAddr = 0;
                if (parm13 != 3)
                    Make2ndDegreeEdgeList(t);
                else
                    Make3rdDegreeEdgeList(t);
                return t;
            }
            // Both passes always reload the second (y) bounds after the first one.
            if (pass == 1) {
                hi = t->outlineYMax;
                lo = t->outlineYMin;
            }
        }
    }
}

// Counts the intersections of list p within [lo-4, hi+4] (stops at 2).
// @ 0x008c8eb0
static int CountInterSections(int count, T2KInterSectType* p, long lo, long hi)
{
    if (p != 0) {
        T2KInterSectType* q = p->next;
        lo -= 4;
        hi += 4;
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

// Keeps the static helpers above (cl drops unreferenced statics); the original callers are in
// MakeBits, which is another translation unit here.
int KeepEdgeHelpers(tsiScanConv* t, long lo, long hi, long x1, long x2, long y, long maxIndex,
                    long minIndex)
{
    t->yBase[0] = (T2KInterSectType*)0;
    return IsStub(y, maxIndex, t->yEdgeHead, t->xEdgeHead, x1, x2, minIndex)
         + CountInterSections(0, t->yEdgeHead[0], lo, hi);
}

// @ 0x008c8f00
static int IsStub(long y, long maxIndex, T2KInterSectType** edgeHead,
                  T2KInterSectType** otherEdgeHead, long x1, long x2, long minIndex)
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
