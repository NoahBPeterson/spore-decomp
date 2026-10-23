/* T2K / Font Fusion rasterizer edge builders (drawLine & cubic/conic flattening). */

typedef unsigned char  uchar;
typedef unsigned short ushort;
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

extern void* AllocFreeNodes(void);          /* 0x008c77d0 */
extern int   util_FixDiv(int a, int b);     /* 0x008d16d0 */
extern int   util_FixMul(int a, int b);     /* 0x008d1590 */

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

// @ 0x008c8600
void FUN_008c8600(Ras* ras, int param_2, int param_3, int param_4, int param_5,
                  int param_6, int param_7, int param_8, int param_9)
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

// @ 0x008c83b0
void draw3rdDegreeBezierInner(Ras* ras, int maxDev, int x0, int y0, int x1, int y1,
                              int x2, int y2, int x3, int y3)
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
