// slice s008acbf0 -- TrueType bytecode interpreter handlers (FreeType-derived).
// Every function takes the interpreter execution context as its first argument
// unless noted otherwise.  Field offsets are taken from the original machine
// code for this slice.

struct TTZone;
struct TTGraphicsState;
struct TTExecCtx;

typedef int (*TTRound3Fn)(TTExecCtx*, int, int);

// The rounding part of the graphics state begins at ctx->mGS+0x58.
struct TTRoundState {
    int        mField00;    // +0x00 (ctx->mGS + 0x58)
    char       mPad04[0x14];
    TTRound3Fn mRound;      // +0x18 (ctx->mGS + 0x70)
};

// A zone (stride 0x2c):
//   +0x00  mCurX   int*
//   +0x04  mCurY   int*
//   +0x08  mOrgX   int*
//   +0x0c  mOrgY   int*
//   +0x10  mOrusX  short*
//   +0x14  mOrusY  short*
//   +0x18  (unused)
//   +0x1c  mNumContours
//   +0x20  mContourStarts short*
//   +0x24  mContourEnds   short*
//   +0x28  mFlags         unsigned char*
struct TTZone {
    int*           mCurX;           // +0x00
    int*           mCurY;           // +0x04
    int*           mOrgX;           // +0x08
    int*           mOrgY;           // +0x0c
    short*         mOrusX;          // +0x10
    short*         mOrusY;          // +0x14
    int            mUnused18;       // +0x18
    short          mNumContours;    // +0x1c
    short*         mContourStarts;  // +0x20
    short*         mContourEnds;    // +0x24
    unsigned char* mFlags;          // +0x28
};

// Graphics state (base is ctx+0x28).
struct TTGraphicsState {
    char       mPad00[0x58];
    int        mField58;        // +0x58
    int        mField5c;        // +0x5c
    int        mField60;        // +0x60
    int        mField64;        // +0x64
    int        mField68;        // +0x68
    int        mField6c;        // +0x6c
    TTRound3Fn mRound3;         // +0x70
    int        mField74;        // +0x74
    int        mPeriod;         // +0x78
    short      mPeriodShort;    // +0x7c
    short      mPhase;          // +0x7e
    short      mThreshold;      // +0x80
    char       mPad82[0x06];
    short      mField88;        // +0x88
    char       mPad8a[0x0e];
    int (*mRound)(TTGraphicsState*, int); // +0x98
};

struct TTExecCtx {
    unsigned char*   mIP;       // +0x00
    unsigned short   mOpcode;   // +0x04
    char             mPad06[0x02];
    TTZone*          mZp0;      // +0x08
    TTZone*          mZp1;      // +0x0c
    TTZone*          mZp2;      // +0x10
    short            mVecX;     // +0x14
    short            mVecY;     // +0x16
    short            mSingleX;  // +0x18
    short            mSingleY;  // +0x1a
    char             mPad1c[0x04];
    int*             mStack;    // +0x20
    TTZone*          mZones;    // +0x24 (base of the zone array)
    TTGraphicsState* mGS;       // +0x28
    char             mPad2c[0x04];
    int              mRefPt;    // +0x30
    int              mZp0Idx;   // +0x34
    int              mZp1Idx;   // +0x38
    char             mPad3c[0x02];
    short            mRepeat;   // +0x3e
    short            mAaField;  // +0x40
    int (*mMoveFn)(TTExecCtx*, TTZone*, int, int); // +0x44
    int (*mProjFn)(TTExecCtx*, int, int);          // +0x48
    int (*mDualFn)(TTExecCtx*, int, int);          // +0x4c
    char             mPad50[0x04];
    int (*mReadFn)(TTExecCtx*, int);               // +0x54
};

// Callees outside this slice.
void fnt_ComputeAndCheck_PF_Proj(void);                         // 0x008ac7a0 (ctx in eax)
void fnt_MovePoint(TTExecCtx*, TTZone*, int, int);              // 0x008ac1a0
int  fnt_Project(TTExecCtx*, int, int);                         // 0x008ac300
int  util_FixDiv(int, int);                                     // 0x008d16d0
int  util_FixMul(int, int);                                     // 0x008d1590
int  util_ShortFracMul(int, unsigned short);                    // 0x008d1670
int  fnt_RoundToGrid(TTExecCtx*, int, int);                     // 0x008ac040
int  fnt_RoundToHalfGrid(TTExecCtx*, int, int);                 // 0x008ac070
int  fnt_RoundToDoubleGrid(TTExecCtx*, int, int);               // 0x008abfb0
int  fnt_RoundOff(TTExecCtx*, int, int);                        // 0x008ac360
int  fnt_RoundUpToGrid(TTExecCtx*, int, int);                   // 0x008ac010
int  fnt_RoundDownToGrid(TTExecCtx*, int, int);                 // 0x008abfe0

// The original helper takes its context in EAX, not on the stack.
static TTExecCtx* fnt_CallComputeAndCheck(TTExecCtx* ctx)
{
    __asm {
        mov eax, ctx
        call fnt_ComputeAndCheck_PF_Proj
    }
}

// --------------------------------------------------------------------------- handlers

// @ 0x008acbf0
void fnt_WPV(TTExecCtx* c)
{
    c->mStack -= 1;
    c->mVecY = *(short*)c->mStack;
    c->mStack -= 1;
    c->mVecX = *(short*)c->mStack;
    TTExecCtx* r = fnt_CallComputeAndCheck(c);
    r->mMoveFn = (int (*)(TTExecCtx*, TTZone*, int, int))fnt_MovePoint;
    r->mProjFn = fnt_Project;
    r->mDualFn = fnt_Project;
}

// @ 0x008acc30
void fnt_WFV(TTExecCtx* c)
{
    c->mStack -= 1;
    c->mSingleY = *(short*)c->mStack;
    c->mStack -= 1;
    c->mSingleX = *(short*)c->mStack;
    TTExecCtx* r = fnt_CallComputeAndCheck(c);
    r->mMoveFn = (int (*)(TTExecCtx*, TTZone*, int, int))fnt_MovePoint;
}

// @ 0x008acc60
void fnt_GPV(TTExecCtx* c)
{
    *c->mStack++ = c->mVecX;
    *c->mStack++ = c->mVecY;
}

// @ 0x008acc90
void fnt_GFV(TTExecCtx* c)
{
    *c->mStack++ = c->mSingleX;
    *c->mStack++ = c->mSingleY;
}

// @ 0x008accc0
void fnt_SFVTPV(TTExecCtx* c)
{
    *(int*)&c->mSingleX = *(int*)&c->mVecX;
    c->mAaField = 0x4000;
    c->mMoveFn = (int (*)(TTExecCtx*, TTZone*, int, int))fnt_MovePoint;
}

// @ 0x008acce0
void fnt_ISECT(TTExecCtx* c)
{
    int* p = c->mStack;
    int b = p[-1];
    int a = p[-2];
    int d = p[-3];
    int e = p[-4];
    int contour = p[-5];
    c->mStack = p - 5;

    TTZone* z0 = c->mZp0;
    TTZone* z1 = c->mZp1;
    TTZone* z2 = c->mZp2;

    int x1 = z0->mCurX[a], y1 = z0->mCurY[a];
    int x2 = z0->mCurX[b], y2 = z0->mCurY[b];
    int x3 = z1->mCurX[d], y3 = z1->mCurY[d];
    int x4 = z1->mCurX[e], y4 = z1->mCurY[e];
    int dx1 = x2 - x1, dy1 = y2 - y1;
    int dx2 = x3 - x4, dy2 = y3 - y4;

    z2->mFlags[contour] |= 3;
    int* outX = z2->mCurX;
    int* outY = z2->mCurY;

    int xx, yy;
    if (dy1 == 0) {
        if (dx2 == 0) {
            outX[contour] = x3;
            outY[contour] = y1;
            return;
        }
        xx = y4 - y1;
        yy = -dy2;
    } else if (dx1 == 0) {
        if (dy2 == 0) {
            outX[contour] = x1;
            outY[contour] = y4;
            return;
        }
        xx = x4 - x1;
        yy = -dx2;
    } else {
        int adx = dx1 < 0 ? -dx1 : dx1;
        int ady = dy1 < 0 ? -dy1 : dy1;
        if (ady < adx) {
            int u = util_FixDiv(dy1, dx1);
            xx = (y4 - y1) - util_FixMul(x4 - x1, u);
            yy = util_FixMul(dx2, u) - dy2;
        } else {
            int u = util_FixDiv(dx1, dy1);
            xx = util_FixMul(y4 - y1, u) + (x1 - x4);
            yy = dx2 - util_FixMul(dy2, u);
        }
    }

    if (yy == 0) {
        outX[contour] = ((dx1 >> 1) + ((x3 - x4) >> 1) + x4 + x1) >> 1;
        outY[contour] = ((dy1 >> 1) + ((y3 - y4) >> 1) + y4 + y1) >> 1;
        return;
    }

    int ax = xx < 0 ? -xx : xx;
    int ay = yy < 0 ? -yy : yy;
    if (ay <= ax) {
        if (xx == 0) {
            outX[contour] = x4;
            outY[contour] = y4;
            return;
        }
        int u = util_FixDiv(yy, xx);
        outX[contour] = util_FixDiv(dx2, u) + x4;
        outY[contour] = util_FixDiv(dy2, u) + y4;
    } else {
        int u = util_FixDiv(xx, yy);
        outX[contour] = util_FixMul(dx2, u) + x4;
        outY[contour] = util_FixMul(dy2, u) + y4;
    }
}

// @ 0x008acf70
void fnt_SCVTCI(TTExecCtx* c)
{
    c->mStack -= 1;
    c->mGS->mField6c = *c->mStack;
}

// @ 0x008acf90
void fnt_SSWCI(TTExecCtx* c)
{
    c->mStack -= 1;
    c->mGS->mField58 = *c->mStack;
}

// @ 0x008acfb0
void fnt_SSW(TTExecCtx* c)
{
    c->mStack -= 1;
    c->mGS->mField5c = *c->mStack;
}

// @ 0x008acfd0
void fnt_SMD(TTExecCtx* c)
{
    c->mStack -= 1;
    TTGraphicsState* gs = c->mGS;
    gs->mField88 = *(short*)c->mStack;
    gs->mField60 = gs->mRound(gs, gs->mField88);
}

// @ 0x008ad000
void fnt_SRP(TTExecCtx* c)
{
    c->mStack -= 1;
    int v = *c->mStack;
    switch (*(unsigned*)&c->mOpcode) {
    case 0x10: c->mRefPt = v; break;
    case 0x11: c->mZp0Idx = v; break;
    case 0x12: c->mZp1Idx = v; break;
    case 0x17: c->mRepeat = (short)(v - 1); break;
    }
}

// @ 0x008ad060
void fnt_SZP(TTExecCtx* c)
{
    c->mStack -= 1;
    int idx = *c->mStack;
    TTZone* z = (TTZone*)((char*)c->mZones + idx * 0x2c);
    switch (*(unsigned*)&c->mOpcode) {
    case 0x13:
    case 0x16:
        *(TTZone* volatile*)((char*)c + 0x10) = z;
        *(TTZone* volatile*)((char*)c + 0x0c) = z;
        *(TTZone* volatile*)((char*)c + 0x08) = z;
        break;
    case 0x14:
        *(TTZone* volatile*)((char*)c + 0x0c) = z;
        break;
    case 0x15:
        *(TTZone* volatile*)((char*)c + 0x10) = z;
        break;
    }
}

// @ 0x008ad0b0
void fnt_SetRoundMode(TTExecCtx* c)
{
    TTRound3Fn* p = &c->mGS->mRound3;
    switch (*(unsigned*)&c->mOpcode) {
    case 0x18: *p = fnt_RoundToGrid; return;
    case 0x19: *p = fnt_RoundToHalfGrid; return;
    case 0x3d: *p = fnt_RoundToDoubleGrid; return;
    case 0x7a: *p = fnt_RoundOff; return;
    case 0x7c: *p = fnt_RoundUpToGrid; return;
    case 0x7d: *p = fnt_RoundDownToGrid; return;
    }
}

// @ 0x008ad190
void fnt_SetRoundValues(TTExecCtx* c, unsigned int selector, int absolute)
{
    TTGraphicsState* gs = c->mGS;
    unsigned int periodSel = selector & 0xc0;

    if (absolute) {
        if (periodSel == 0) {
            gs->mPeriodShort = 0x20;
            gs->mField74 = -0x20;
        } else if (periodSel == 0x40) {
            gs->mPeriodShort = 0x40;
            gs->mField74 = -0x40;
        } else if (periodSel == 0x80) {
            gs->mPeriodShort = 0x80;
            gs->mField74 = -0x80;
        } else {
            gs->mPeriodShort = 999;
            gs->mField74 = -999;
        }
    } else {
        gs->mPeriod = 0x2d413ccd;
        if (periodSel == 0)
            gs->mPeriod = 0x16a09e66;
        else if (periodSel == 0x80)
            gs->mPeriod = 0x5a82799a;
        else if (periodSel != 0x40)
            gs->mPeriod = 999;
        gs->mPeriodShort = (short)(char)((unsigned)(gs->mPeriod + 0x800000) >> 24);
    }

    switch (selector & 0x30) {
    case 0:
        gs->mPhase = 0;
        break;
    case 0x10: {
        int v = gs->mPeriodShort + 2;
        gs->mPhase = (short)(v >> 2);
        break;
    }
    case 0x20:
        gs->mPhase = (short)((gs->mPeriodShort + 1) >> 1);
        break;
    case 0x30: {
        int v = gs->mPeriodShort * 3 + 2;
        gs->mPhase = (short)(v >> 2);
        break;
    }
    }

    if ((selector & 0x0f) == 0)
        gs->mThreshold = (short)(gs->mPeriodShort - 1);
    else
        gs->mThreshold = (short)((((int)(selector & 0x0f) - 4) * gs->mPeriodShort + 4) >> 3);
}

// @ 0x008ad2f0
int fnt_ContourTailDelta(TTExecCtx* c)
{
    TTZone* z = c->mZones + 1;
    int* org = z->mOrgX;
    int n = z->mNumContours;
    short* ends = z->mContourEnds;
    int p = ends[n - 1];
    int delta = org[p + 2] - org[p + 1];
    p++;
    *c->mStack = delta;
    c->mStack += 1;
    return p;
}

// @ 0x008ad320
void fnt_DUP(TTExecCtx* c)
{
    *c->mStack = c->mStack[-1];
    c->mStack += 1;
}

// @ 0x008ad340
void fnt_CLEAR(TTExecCtx* c)
{
    c->mStack = *(int**)c->mGS;
}

// @ 0x008ad350
void fnt_SWAP(TTExecCtx* c)
{
    c->mStack -= 1;
    int a = *c->mStack;
    c->mStack -= 1;
    int b = *c->mStack;
    c->mStack[0] = a;
    c->mStack += 1;
    *c->mStack = b;
    c->mStack += 1;
}

// @ 0x008ad380
void fnt_DEPTH(TTExecCtx* c)
{
    *c->mStack = (int)(c->mStack - *(int**)c->mGS);
    c->mStack += 1;
}

// @ 0x008ad3a0
void fnt_CINDEX(TTExecCtx* c)
{
    c->mStack -= 1;
    int* p = c->mStack;
    p[0] = p[-p[0]];
    c->mStack += 1;
}

// @ 0x008ad3c0
void fnt_MINDEX(TTExecCtx* c)
{
    int* p = c->mStack - 1;
    int n = p[0];
    int* q = p - n;
    int v = *q;
    if (n != 0) {
        do {
            *q = q[1];
            q++;
            n--;
        } while (n != 0);
        p--;
    }
    *p = v;
    c->mStack = p + 1;
}

// @ 0x008ad400
void fnt_ROLL(TTExecCtx* c)
{
    int* q = c->mStack;
    int a = *--q;
    int b = *--q;
    *q = a;
    int d = *--q;
    *q = b;
    q[2] = d;
}

// @ 0x008ad430
void fnt_MDAP(TTExecCtx* c)
{
    TTZone* z = c->mZp0;
    TTRoundState* rs = (TTRoundState*)((char*)c->mGS + 0x58);
    c->mStack -= 1;
    int p = *c->mStack;
    c->mZp0Idx = p;
    c->mRefPt = p;
    if (c->mOpcode & 1) {
        int v = c->mProjFn(c, z->mCurX[p], z->mCurY[p]);
        int r = rs->mRound(c, v, 0);
        c->mMoveFn(c, z, p, r - v);
    } else {
        c->mMoveFn(c, z, p, 0);
    }
}

// @ 0x008ad4b0
void fnt_MIAP(TTExecCtx* c)
{
    TTRoundState* gs = (TTRoundState*)((char*)c->mGS + 0x58);
    TTZone* z = c->mZp0;
    c->mStack -= 1;
    int dist = c->mReadFn(c, *c->mStack);
    c->mStack -= 1;
    int p = *c->mStack;
    c->mZp0Idx = p;
    c->mRefPt = p;

    if (z == c->mZones) {
        z->mOrgX[p] = util_ShortFracMul(dist, (unsigned short)c->mVecX);
        z->mCurX[p] = z->mOrgX[p];
        z->mOrgY[p] = util_ShortFracMul(dist, (unsigned short)c->mVecY);
        z->mCurY[p] = z->mOrgY[p];
    }

    int v = c->mProjFn(c, z->mCurX[p], z->mCurY[p]);
    if (c->mOpcode & 1) {
        int d = dist - v;
        if (d < 0)
            d = -d;
        dist = (d > gs->mField00) ? v : dist;
        dist = gs->mRound(c, dist, 0);
    }
    c->mMoveFn(c, z, p, dist - v);
}

// @ 0x008ad590
void fnt_IUP(TTExecCtx* c)
{
    TTZone* z = c->mZp2;
    unsigned char* flags = z->mFlags;
    int* cur;
    int* org;
    short* orus;
    unsigned char mask;
    unsigned char otherMask;
    if (c->mOpcode & 1) {
        cur = z->mCurX;
        org = z->mOrgX;
        orus = z->mOrusX;
        mask = 1;
        otherMask = 1;
    } else {
        cur = z->mCurY;
        org = z->mOrgY;
        orus = z->mOrusY;
        mask = 2;
        otherMask = 2;
    }
    (void)otherMask;

    for (int ci = 0; ci < z->mNumContours; ci++) {
        int first = z->mContourStarts[ci];
        int last = z->mContourEnds[ci];
        int p = first;
        if ((flags[p] & mask) == 0) {
            while (p <= last && (flags[p] & mask) == 0)
                p++;
            if (p > last)
                continue;
        }
        int start = p;
        int next = start;
        for (;;) {
            int prev = next;
            next = (prev == last) ? first : prev + 1;
            if (next == start)
                break;
            while ((flags[next] & mask) == 0)
                next = (next == last) ? first : next + 1;

            int base, other;
            if (orus[prev] < orus[next]) {
                base = prev;
                other = next;
            } else {
                base = next;
                other = prev;
            }
            int curB = cur[base];
            int orgB = org[base];
            int curO = cur[other];
            int orgO = org[other];
            int dcur = curB - orgB;
            int dorg = curO - orgO;
            int dorus = orus[other] - orus[base];

            if (dorus == 0) {
                int q = prev;
                for (;;) {
                    q = (q == last) ? first : q + 1;
                    if (q == next)
                        break;
                    cur[q] += dcur;
                }
            } else {
                int dcur1 = curO - curB;
                if (dorus < 0x8000 && dcur1 < 0x8000) {
                    int q = prev;
                    for (;;) {
                        q = (q == last) ? first : q + 1;
                        if (q == next)
                            break;
                        int v = org[q];
                        if (orgB < v) {
                            if (orgO <= v)
                                v += dorg;
                            else
                                v = (((orus[q] - orus[base]) * dcur1 + (dorus >> 1)) / dorus) + curB;
                        } else {
                            if (orgO <= v)
                                v += dorg;
                            else
                                v += dcur;
                        }
                        cur[q] = v;
                    }
                } else {
                    int factor = 0;
                    int haveFactor = 0;
                    int q = prev;
                    for (;;) {
                        q = (q == last) ? first : q + 1;
                        if (q == next)
                            break;
                        int v = org[q];
                        if (orgB < v) {
                            if (v < orgO) {
                                if (!haveFactor) {
                                    factor = util_FixDiv(dcur1, dorus);
                                    haveFactor = 1;
                                }
                                v = util_FixMul(orus[q] - orus[base], factor) + curB;
                            } else {
                                v += dorg;
                            }
                        } else {
                            v += dcur;
                        }
                        cur[q] = v;
                    }
                }
            }
            if (next == start)
                break;
        }
    }
}

// @ 0x008ad850
TTZone* fnt_SH_Common(TTExecCtx* c, int* dx, int* dy, int* point)
{
    TTZone* z;
    int idx;
    if (c->mOpcode & 1) {
        idx = c->mZp0Idx;
        z = c->mZp0;
    } else {
        idx = c->mZp1Idx;
        z = c->mZp1;
    }

    int d = c->mProjFn(c, z->mOrgX[idx] - z->mCurX[idx],
                          z->mOrgY[idx] - z->mCurY[idx]);
    if (c->mAaField != 0x4000) {
        if (c->mSingleX != 0) {
            int f = util_FixDiv((int)c->mSingleX << 4, c->mAaField);
            *dx = (util_FixMul(d, f) + 4) >> 4;
        }
        if (c->mSingleY != 0) {
            int f = util_FixDiv((int)c->mSingleY << 4, c->mAaField);
            *dy = (util_FixMul(d, f) + 4) >> 4;
        }
    } else {
        if (c->mSingleX != 0)
            *dx = util_ShortFracMul(d, (unsigned short)c->mSingleX);
        if (c->mSingleY != 0)
            *dy = util_ShortFracMul(d, (unsigned short)c->mSingleY);
    }
    *point = idx;
    return z;
}

// @ 0x008ad950
void fnt_SHP_Common(TTExecCtx* c, int dy, int dx)
{
    TTZone* z = c->mZp2;
    short reps = c->mRepeat;
    if (reps < 0) {
        c->mRepeat = 0;
        return;
    }
    do {
        c->mStack -= 1;
        int p = *c->mStack;
        if (c->mSingleX != 0) {
            z->mCurX[p] += dx;
            z->mFlags[p] |= 1;
        }
        if (c->mSingleY != 0) {
            z->mCurY[p] += dy;
            z->mFlags[p] |= 2;
        }
        reps--;
    } while (reps >= 0);
    c->mRepeat = 0;
}

// @ 0x008ad9c0
void fnt_SHP(TTExecCtx* c)
{
    int dx, dy, point;
    fnt_SH_Common(c, &dx, &dy, &point);
    fnt_SHP_Common(c, dy, dx);
}

// @ 0x008ada00
void fnt_SHC(TTExecCtx* c)
{
    int dx, dy, point;
    TTZone* z = fnt_SH_Common(c, &dx, &dy, &point);
    TTZone* zp2 = c->mZp2;
    int dxv = c->mSingleX ? dx : 0;
    int dyv = c->mSingleY ? dy : 0;

    c->mStack -= 1;
    int ci = *c->mStack;
    if (ci < zp2->mNumContours) {
        int p = zp2->mContourStarts[ci];
        int last = zp2->mContourEnds[ci];
        while (p <= last) {
            if (p != point || z != zp2) {
                if (dxv != 0) {
                    zp2->mCurX[p] += dxv;
                    zp2->mFlags[p] |= 1;
                }
                if (dyv != 0) {
                    zp2->mCurY[p] += dyv;
                    zp2->mFlags[p] |= 2;
                }
            }
            p++;
        }
    }
}
