// src/game/UTFSpore_Win32/t2ksc.cpp -- migrated from slice(s) s008c9000, s008c7c40, s008c6e80 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/t2ksc.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern int*        gOutlineRows;                    // param_1 reload

// ---- items of slice s008c6e80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* tsiAlloc;
struct T2KReader;
void tsi_DeAllocMem(tsiAlloc a, void* p);           // 0x008D1440
struct T2KNode {
    int x;                                          // 0x000 (halved for the bbox)
    int y;                                          // 0x004
    T2KNode* mpNext;                                // 0x008
};
struct T2KOutline {
    uint32_t pad_00[0x40/4];                        // 0x000..0x040
    int      a_40;                                  // 0x040
    int      b_44;                                  // 0x044
    int      c_48;                                  // 0x048
    int      d_4c;                                  // 0x04c
};
extern T2KOutline* gOutlineOut;                     // ebx in ComputeOutlineBBox
extern int*        gOutlineRows;                    // param_1 reload
struct T2KReader {
    uint32_t  pad_000[0x214/4];                     // 0x000..0x214
    uint32_t  ringCapacity;                         // 0x214
    uint32_t  ringStart;                            // 0x218
    uint32_t  readCursor;                           // 0x21c
    uint32_t  pad_220[3];                           // 0x220..0x22c
    int       mpErrorContext;                       // 0x22c
    uint8_t   pad_230[0x217c - 0x230];              // 0x230..0x217c
    T2KNode*  m_inlineNodes[0x20];                  // 0x217c inline node table (32 entries)
    T2KNode** mppNodes;                             // 0x21fc node table pointer
    int       mnNodeCount2;                         // 0x2200
    int       mnNodeCount;                          // 0x2204
    uint8_t   pad_2208[0x2234 - 0x2208];            // 0x2208..0x2234
    tsiAlloc  mpAllocator;                          // 0x2234

    void FreeAllNodes();                            // 0x008C7960
    void AllocFreeNodes(int count);                 // 0x008C77D0
    void ComputeScanBBox();                         // 0x008C79C0
};
void __fastcall ComputeOutlineBBox(int* rows, int pass);    // 0x008C7BE0
// ---- items of slice s008c6e80 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern T2KOutline* gOutlineOut;                     // ebx in ComputeOutlineBBox

// ---- items of slice s008c7c40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* AllocFreeNodes(void);          /* 0x008c77d0 */
extern int   util_FixDiv(int a, int b);     /* 0x008d16d0 */
extern int   util_FixMul(int a, int b);     /* 0x008d1590 */
/* T2K / Font Fusion rasterizer edge builders (drawLine & cubic/conic flattening). */

typedef unsigned char  uchar;
typedef unsigned int   uint;
typedef struct RasNode {
    int             x;
    struct RasNode* next;
} RasNode;
typedef struct Ras {
    int       lastX;              /* 0x000 */
    int       lastY;              /* 0x004 */
    uchar     pad_008[0x050 - 0x008];
    int       clip;               /* 0x050 */
    uchar     pad_054[0x0d4 - 0x054];
    RasNode** bucketA;            /* 0x0d4 */
    uchar     pad_0d8[0x164 - 0x0d8];
    RasNode** bucketB;            /* 0x164 */
    uchar     pad_168[0x174 - 0x168];
    RasNode*  freeCur;            /* 0x174 */
    RasNode*  freeEnd;            /* 0x178 */
    uchar     pad_17c[0x2208 - 0x17c];
    int       deviationLimit;     /* 0x2208 */
    uchar     pad_220c[0x2211 - 0x220c];
    uchar     enabled;            /* 0x2211 */
    uchar     pad_2212[0x221c - 0x2212];
    short*    xCoords;            /* 0x221c */
    short*    yCoords;            /* 0x2220 */
    short     numPoints;          /* 0x2224 */
    int*      flagsA;             /* 0x2228 */
    int*      flagsB;             /* 0x222c */
    char*     onCurve;            /* 0x2230 */
} Ras;
void draw3rdDegreeBezierInner(Ras* ras, int maxDev, int x0, int y0, int x1, int y1,
                              int x2, int y2, int x3, int y3);
#define NEW_NODE(node)                                                  \
    do {                                                                \
        (node) = ras->freeCur;                                          \
        if (ras->freeEnd <= (node)) (node) = (RasNode*)AllocFreeNodes();\
        ras->freeCur = ras->freeCur + 1;                                \
    } while (0)
/* Insert a node holding `value` into the sorted bucket list. */
#define INSERT_NODE(bucket, value)                                      \
    do {                                                                \
        cur = *(bucket);                                                \
        NEW_NODE(node);                                                 \
        (node)->x = (value);                                            \
        if (cur == 0 || (value) < cur->x) {                             \
            (node)->next = cur;                                         \
            *(bucket) = (node);                                         \
        }                                                               \
        else {                                                          \
            prev = cur->next;                                           \
            while (prev != 0 && prev->x <= (value)) {                   \
                cur  = prev;                                            \
                prev = prev->next;                                      \
            }                                                           \
            (node)->next = prev;                                        \
            cur->next = (node);                                         \
        }                                                               \
    } while (0)

// ---- items of slice s008c7c40 end
// ---- items of slice s008c7c40 end

// ---- items of slice s008c9000 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
#define T2K_SCAN_BITMAP 5
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
static __inline uint8 MixGrey(int a, int d)
{
    int wd = 63 - d;
    int wa = 63 - a;
    wd = (63 * 63 + 1) - wd * wd;
    wa = (63 * 63 + 1) - wa * wa;
    return (uint8)((a * wa + d * wd) / (wa + wd));
}
struct tsiMemObject {
    uint32_t pad00[0x18];           // +0x00
    tsiScanConv* currentScanConv;   // +0x60 scan converter owning the cached bitmap
    void* cachedBitmap;             // +0x64
    uint32_t pad18[0x0c];           // +0x68
    int scanConvKept;               // +0x98 scan converter was cached, do not free it
    int bitmapKept;                 // +0x9c bitmap was cached, do not free it
};
static __declspec(noinline) void FreeAllNodes(tsiScanConv* t)
{
    for (int i = 1; i <= t->freeMemBlockN; i++)
        tsi_DeAllocMem(t->mem, t->freeMemBlocks[i]);
    if (t->freeMemBlocks != t->freeMemBlocksBuffer)
        tsi_DeAllocMem(t->mem, t->freeMemBlocks);
    t->freeMemBlockMaxCount = 0;
}
// ---- items of slice s008c9000 end

// @ 0x008c77d0
void T2KReader::AllocFreeNodes(int count)
{
    (void)count;
}

// @ 0x008c7960
void T2KReader::FreeAllNodes()
{
    for (int i = 1; i <= mnNodeCount; ++i) {
        tsi_DeAllocMem(mpAllocator, mppNodes[i]);
    }
    if (mppNodes != m_inlineNodes) {
        tsi_DeAllocMem(mpAllocator, mppNodes);
    }
    mnNodeCount2 = 0;
}

// @ 0x008c79c0
void T2KReader::ComputeScanBBox()
{
}

// @ 0x008c7be0
void __fastcall ComputeOutlineBBox(int* rows, int pass)
{
    T2KOutline* out = gOutlineOut;
    for (int which = 0; which < 2; ++which) {
        int seed = *rows;
        int lo = seed;
        int hi = seed;
        for (int i = 1; i <= pass; ++i) {
            int v = rows[i];
            if (v > hi) {
                hi = v;
            } else if (v < lo) {
                lo = v;
            }
        }
        if (which == 0) {
            out->a_40 = lo;
            out->b_44 = hi;
            rows = gOutlineRows;
        } else {
            out->c_48 = lo;
            out->d_4c = hi;
        }
    }
}

// @ 0x008c7c40
void __fastcall drawLine(void* unused, Ras* ras, int param_3, int param_4, int param_5, int param_6)
{
    RasNode*  node;
    RasNode*  cur;
    RasNode*  prev;
    RasNode** local_1c;
    int       iVar3;
    int       uVar4;
    int       iVar5;
    int       value;
    uint      uVar8;
    int       iVar9;
    uchar     local_2d;
    int       local_2c;
    int       local_28;
    int       local_24;
    int       local_20;
    int       local_18;
    int       local_14;
    int       local_10;
    int       local_c;
    uchar     bVar7;

    local_18 = 0;
    local_20 = 0;
    local_28 = 0;
    local_24 = 0;
    local_2d = 0;
    if (ras->enabled != 0) {
        if (param_3 < param_5) {
            local_2c = param_5 - param_3;
            uVar8 = ((uint)param_3 + 0x1fU) & 0xffffffc0U;
            iVar9 = (int)uVar8 + 0x20;
            local_24 = param_3;
            local_20 = param_4;
            local_28 = param_5;
            local_18 = param_6;
            local_2d = 1;
            if ((((uchar)param_3 & 0x3f) == 0x20) && (ras->lastX < param_3)) {
                iVar9 = (int)uVar8 + 0x60;
            }
        }
        else {
            if (param_3 <= param_5) {
                local_28 = 0;
                goto LAB_008c7ec1;
            }
            local_2d = 0;
            local_2c = param_3 - param_5;
            iVar9 = (int)((((uint)param_5 + 0x1fU) & 0xffffffc0U)) + 0x20;
            local_24 = param_5;
            local_20 = param_6;
            local_28 = param_3;
            local_18 = param_4;
            if ((((uchar)param_3 & 0x3f) == 0x20) && (param_3 < ras->lastX)) {
                local_28 = param_3 - 1;
            }
        }
        if (iVar9 <= local_28) {
            local_1c = ras->bucketB + (iVar9 >> 6);
            iVar3 = local_18 - local_20;
            if ((ras->clip == 0) ||
                ((local_2c < 0xb504) && (iVar3 < 0xb504) && (-0xb504 < iVar3))) {
                local_14 = (iVar9 - local_24) * iVar3;
                do {
                    value = (local_14 / local_2c + local_20) * 2 | (int)local_2d;
                    INSERT_NODE(local_1c, value);
                    local_14 = local_14 + iVar3 * 0x40;
                    iVar9 = iVar9 + 0x40;
                    local_1c = local_1c + 1;
                } while (iVar9 <= local_28);
            }
            else {
                local_14 = iVar9 - local_24;
                do {
                    uVar4 = util_FixDiv(local_14, local_2c);
                    iVar5 = util_FixMul(iVar3, uVar4);
                    value = (iVar5 + local_20) * 2 | (int)local_2d;
                    INSERT_NODE(local_1c, value);
                    local_14 = local_14 + 0x40;
                    iVar9 = iVar9 + 0x40;
                    local_1c = local_1c + 1;
                } while (iVar9 <= local_28);
            }
        }
    }
LAB_008c7ec1:
    bVar7 = (uchar)param_4;
    if (param_4 < param_6) {
        uVar8 = ((uint)param_4 + 0x1fU) & 0xffffffc0U;
        local_2c = param_6 - param_4;
        iVar9 = (int)uVar8 + 0x20;
        local_2d = 1;
        if (((bVar7 & 0x3f) == 0x20) && (ras->lastY < param_4)) {
            iVar9 = (int)uVar8 + 0x60;
        }
        local_28 = param_5;
        local_24 = param_3;
        local_20 = param_4;
        local_18 = param_6;
        if (param_5 < param_3) goto LAB_008c7f5e;
        iVar3 = local_2c - 1;
    }
    else {
        if (param_6 < param_4) {
            local_2c = param_4 - param_6;
            iVar9 = (int)((((uint)param_6 + 0x1fU) & 0xffffffc0U)) + 0x20;
            local_2d = 0;
            local_18 = param_4;
            if (((bVar7 & 0x3f) == 0x20) && (param_4 < ras->lastY)) {
                local_18 = param_4 - 1;
            }
            local_28 = param_3;
            local_24 = param_5;
            local_20 = param_6;
            if (param_3 < param_5) {
                iVar3 = local_2c - 1;
                goto LAB_008c7f60;
            }
        }
        else {
            iVar9 = (int)((((uint)param_4 + 0x1fU) & 0xffffffc0U)) + 0x20;
            local_2c = 0;
        }
LAB_008c7f5e:
        iVar3 = 0;
    }
LAB_008c7f60:
    if (iVar9 <= local_18) {
        local_1c = ras->bucketA + (iVar9 >> 6);
        if (local_2c == 0) {
            if ((bVar7 & 0x3f) == 0x20) {
                if (param_3 == param_5) goto LAB_008c8201;
                local_2c = 0;
                do {
                    iVar9 = param_5;
                    if (local_2c == 0) {
                        if (param_3 < param_5) {
                            iVar9 = param_3;
                        }
                        uVar8 = 1;
                    }
                    else {
                        if (param_5 < param_3) {
                            iVar9 = param_3;
                        }
                        uVar8 = 0;
                    }
                    value = iVar9 * 2 | (int)uVar8;
                    INSERT_NODE(local_1c, value);
                    local_2c = local_2c + 1;
                } while (local_2c < 2);
            }
        }
        else {
            local_28 = local_28 - local_24;
            if ((ras->clip == 0) ||
                ((local_2c < 0xb504) && (local_28 < 0xb504) && (-0xb504 < local_28))) {
                local_10 = (iVar9 - local_20) * local_28;
                local_c = local_10 + iVar3;
                local_20 = iVar3 - local_10;
                do {
                    if (local_10 < 0) {
                        iVar3 = -(local_20 / local_2c);
                    }
                    else {
                        iVar3 = local_c / local_2c;
                    }
                    value = (local_24 + iVar3) * 2 | (int)local_2d;
                    INSERT_NODE(local_1c, value);
                    local_10 = local_10 + local_28 * 0x40;
                    local_20 = local_20 + local_28 * -0x40;
                    local_c = local_c + local_28 * 0x40;
                    iVar9 = iVar9 + 0x40;
                    local_1c = local_1c + 1;
                } while (iVar9 <= local_18);
            }
            else {
                local_10 = iVar9 - local_20;
                do {
                    uVar4 = util_FixDiv(local_10, local_2c);
                    iVar3 = util_FixMul(local_28, uVar4);
                    value = (iVar3 + local_24) * 2 | (int)local_2d;
                    INSERT_NODE(local_1c, value);
                    local_10 = local_10 + 0x40;
                    iVar9 = iVar9 + 0x40;
                    local_1c = local_1c + 1;
                } while (iVar9 <= local_18);
            }
        }
    }
    if (param_3 != param_5) {
        ras->lastX = param_3;
    }
LAB_008c8201:
    if (param_4 != param_6) {
        ras->lastY = param_4;
    }
}

// @ 0x008c8220
void drawParabola(Ras* ras, int x0, int y0, int x1, int y1, int x2, int y2)
{
    int  frame[112];
    int* fp;
    int  iVar1;
    int  iVar2;
    int  iVar3;
    int  level;

    iVar1 = (x0 + x2 - 2 * x1) >> 2;
    if (iVar1 < 0) {
        iVar1 = -iVar1;
    }
    iVar2 = (y0 + y2 - 2 * y1) >> 2;
    if (iVar2 < 0) {
        iVar2 = -iVar2;
    }
    if (iVar1 < iVar2) {
        iVar1 = iVar2;
    }
    level = 0;
    while (ras->deviationLimit < iVar1) {
        level = level + 1;
        iVar1 = iVar1 >> 2;
    }
    fp = frame;
    for (;;) {
        while (0 < level) {
            level = level - 1;
            iVar1 = (x2 + 2 + x1 * 2 + x0) >> 2;
            fp[0] = iVar1;
            iVar3 = (y2 + 2 + y1 * 2 + y0) >> 2;
            fp[1] = iVar3;
            fp[2] = (x0 + 1 + x1) >> 1;
            fp[3] = (y0 + 1 + y1) >> 1;
            fp[4] = x0;
            fp[5] = y0;
            x1 = (x2 + 1 + x1) >> 1;
            fp[6] = level;
            fp = fp + 7;
            y1 = (y2 + 1 + y1) >> 1;
            y0 = iVar3;
            x0 = iVar1;
        }
        drawLine(ras->onCurve, ras, x2, y2, x0, y0);
        if (fp <= frame) break;
        level = fp[-1];
        y0 = fp[-2];
        x0 = fp[-3];
        y1 = fp[-4];
        x1 = fp[-5];
        y2 = fp[-6];
        fp = fp - 7;
        x2 = fp[0];
    }
}

// @ 0x008c83b0
void draw3rdDegreeBezierInner(Ras* ras, int maxDev, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
{
    int  frame[144];
    int* fp;
    int  iVar3;
    int  iVar4;
    int  iVar5;
    int  iVar6;
    int  iVar7;
    int  iVar9;
    int  level;

    iVar3 = ((x1 - x0) - x2 + x3) * 3 + 4 >> 3;
    if (iVar3 < 0) iVar3 = -iVar3;
    if (maxDev < iVar3) maxDev = iVar3;
    iVar3 = ((y1 - y0) - y2 + y3) * 3 + 4 >> 3;
    if (iVar3 < 0) iVar3 = -iVar3;
    if (maxDev < iVar3) maxDev = iVar3;
    level = 0;
    while (ras->deviationLimit < maxDev) {
        level = level + 1;
        maxDev = maxDev >> 2;
    }
    fp = frame;
    for (;;) {
        while (0 < level) {
            iVar6 = x1 + x2 + 1 >> 1;
            iVar5 = x0 + 1 + x3 >> 1;
            iVar3 = x0 + (x1 + x2) * 3 + 4 + x3 >> 3;
            fp[0] = iVar3;
            level = level - 1;
            iVar4 = y0 + (y1 + y2) * 3 + 4 + y3 >> 3;
            fp[1] = iVar4;
            fp[2] = iVar5 + 1 + iVar6 >> 1;
            iVar9 = y2 + 1 + y3 >> 1;
            iVar7 = y1 + y2 + 1 >> 1;
            fp[3] = iVar9 + 1 + iVar7 >> 1;
            fp[4] = iVar5;
            fp[5] = iVar9;
            fp[6] = x3;
            fp[7] = y3;
            fp[8] = level;
            x1 = x0 + 1 + x1 >> 1;
            y1 = y0 + 1 + y1 >> 1;
            x2 = iVar6 + 1 + x1 >> 1;
            fp = fp + 9;
            y2 = y1 + 1 + iVar7 >> 1;
            x3 = iVar3;
            y3 = iVar4;
        }
        drawLine(ras->onCurve, ras, x0, y0, x3, y3);
        if (fp <= frame) break;
        level = fp[-1];
        y3 = fp[-2];
        y2 = fp[-4];
        y1 = fp[-6];
        x1 = fp[-7];
        x2 = fp[-5];
        y0 = fp[-8];
        fp = fp - 9;
        x0 = fp[0];
        x3 = fp[6];
    }
}

// @ 0x008c8600
void FUN_008c8600(Ras* ras, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9)
{
    int maxDev;
    int dev1;
    int dev3;
    int d1;
    int d2;
    int iVar1;
    int iVar2;
    int iVar3;

    d1 = (param_4 - param_2 - param_8 + param_6) * 3 + 4 >> 3;
    if (d1 < 0) d1 = -d1;
    d2 = (param_5 - param_3 - param_9 + param_7) * 3 + 4 >> 3;
    if (d2 < 0) d2 = -d2;
    maxDev = ((d1 < d2 ? d2 : d1) + 2) >> 2;

    dev1 = (param_2 + (param_4 + param_6) * 3 + 4 + param_8) >> 3;
    dev3 = (param_3 + (param_5 + param_7) * 3 + 4 + param_9) >> 3;

    iVar1 = (param_3 + 1 + param_5) >> 1;
    iVar3 = (param_5 + param_7 + 1) >> 1;
    iVar2 = ((param_4 + param_6 + 1) >> 1) + ((param_2 + param_4 + 1) >> 1) + 1;

    draw3rdDegreeBezierInner(ras, maxDev,
                             param_2, param_3,
                             (param_2 + 1 + param_4) >> 1, iVar1,
                             iVar2 >> 1,
                             (iVar1 + 1 + iVar3) >> 1,
                             dev1, dev3);

    iVar1 = (param_7 + 1 + param_9) >> 1;
    draw3rdDegreeBezierInner(ras, maxDev,
                             dev1, dev3,
                             ((param_4 + ((param_6 + param_8 + 1) >> 1)) + 1) >> 1,
                             iVar1 + 1 + iVar3 >> 1,
                             (param_6 + param_8 + 1) >> 1,
                             (param_7 + param_9 + 1) >> 1,
                             param_8, param_9);
}

// @ 0x008c8720
void Make3rdDegreeEdgeList(Ras* ras)
{
    int*  iVar2;
    int*  iVar3;
    char* iVar4;
    int   iVar5;
    int   iVar6;
    int   iVar7;
    int   iVar8;
    int   iVar9;
    int   iVar10;
    int   iVar11;
    int   iVar12;
    int   iVar13;
    int   iVar14;
    int   iVar15;
    int   local_8;
    char  cVar1;

    iVar2 = ras->flagsA;
    iVar3 = ras->flagsB;
    iVar4 = ras->onCurve;
    local_8 = 0;
    if (0 < (int)ras->numPoints) {
        do {
            iVar13 = (int)ras->xCoords[local_8];
            iVar11 = (int)ras->yCoords[local_8];
            iVar15 = (iVar11 - iVar13) + 1;
            cVar1 = *(char*)(iVar13 + iVar4);
            iVar10 = iVar13;
            iVar7 = iVar11;
            while (iVar14 = iVar10, cVar1 == '\0') {
                iVar10 = iVar14 + 1;
                iVar7 = iVar14;
                cVar1 = *(char*)(iVar14 + 1 + iVar4);
            }
            iVar10 = *(int*)(iVar2 + iVar14 * 4);
            iVar5 = *(int*)(iVar3 + iVar14 * 4);
            if (((uchar)iVar10 & 0x3f) == 0x20) {
                iVar6 = *(int*)(iVar2 + iVar7 * 4);
                ras->lastX = iVar6;
                if (*(char*)(iVar7 + iVar4) == '\0') {
LAB_008c87ec:
                    iVar10 = iVar10 + -1;
                    *(int*)(iVar2 + iVar14 * 4) = iVar10;
                }
                else if (iVar6 == iVar10) {
                    if ((iVar7 != iVar13) && (*(char*)(iVar7 + -1 + iVar4) != '\0')) {
                        ras->lastX = *(int*)(iVar2 + -4 + iVar7 * 4);
                    }
                    if (ras->lastX == iVar10) goto LAB_008c87ec;
                }
            }
            if (((uchar)iVar5 & 0x3f) == 0x20) {
                iVar6 = *(int*)(iVar3 + iVar7 * 4);
                ras->lastY = iVar6;
                if (*(char*)(iVar7 + iVar4) == '\0') {
LAB_008c8839:
                    *(int*)(iVar3 + iVar14 * 4) = iVar5 + -1;
                    iVar5 = iVar5 + -1;
                }
                else if (iVar6 == iVar5) {
                    if ((iVar7 != iVar13) && (*(char*)(iVar7 + -1 + iVar4) != '\0')) {
                        ras->lastY = *(int*)(iVar3 + -4 + iVar7 * 4);
                    }
                    if (ras->lastY == iVar5) goto LAB_008c8839;
                }
            }
            while (0 < iVar15) {
                iVar14 = iVar14 + 1;
                if (iVar11 < iVar14) {
                    iVar14 = iVar13;
                }
                iVar7 = *(int*)(iVar2 + iVar14 * 4);
                iVar6 = *(int*)(iVar3 + iVar14 * 4);
                if (*(char*)(iVar14 + iVar4) == '\0') {
                    iVar12 = iVar14 + 1;
                    if (iVar11 < iVar14 + 1) {
                        iVar12 = iVar13;
                    }
                    iVar14 = iVar12 + 1;
                    if (iVar11 < iVar12 + 1) {
                        iVar14 = iVar13;
                    }
                    iVar8 = *(int*)(iVar3 + iVar14 * 4);
                    iVar9 = *(int*)(iVar2 + iVar14 * 4);
                    FUN_008c8600(ras, iVar10, iVar5, iVar7, iVar6,
                                 *(int*)(iVar2 + iVar12 * 4),
                                 *(int*)(iVar3 + iVar12 * 4), iVar9, iVar8);
                    iVar15 = iVar15 + -3;
                    iVar10 = iVar9;
                    iVar5 = iVar8;
                }
                else {
                    drawLine(iVar4, ras, iVar10, iVar5, iVar7, iVar6);
                    iVar15 = iVar15 + -1;
                    iVar10 = iVar7;
                    iVar5 = iVar6;
                }
            }
            local_8 = local_8 + 1;
        } while (local_8 < (int)ras->numPoints);
    }
}

// @ 0x008c9000
void MakeBits(tsiScanConv* t, char xWeightIsOne, char omitBitMap, FF_GetCacheMemoryPtr funcptr, void* theCache, int bitRange255, uint8* remapBits, int emboldenDir)
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

// @ 0x008c9a70
void tsi_DeleteScanConv(tsiScanConv* t)
{
    if (t == 0)
        return;
    if (t->baseAddr != 0) {
        if ((void*)t->baseAddr == t->mem->cachedBitmap)
            t->mem->bitmapKept = 1;
        else
            tsi_DeAllocMem(t->mem, t->baseAddr);
    }
    FreeAllNodes(t);
    if (t->xBase != t->xBaseBuffer)
        tsi_DeAllocMem(t->mem, t->xBase);
    if (t->yBase != t->yBaseBuffer)
        tsi_DeAllocMem(t->mem, t->yBase);
    tsiMemObject* mem = t->mem;
    if (t == mem->currentScanConv)
        mem->scanConvKept = 1;
    else
        tsi_DeAllocMem(mem, t);
}
