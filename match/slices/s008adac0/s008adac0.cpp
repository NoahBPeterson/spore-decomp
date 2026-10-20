// slice s008adac0 -- TrueType bytecode interpreter opcode handlers (FreeType-derived).
// Every handler here is a cdecl function whose single argument is a pointer to the
// interpreter execution context (Ghidra's `param_1`).
//
// Context offsets touched by this slice:
//   +0x00  ip        (instruction pointer into the bytecode stream)
//   +0x04  opcode    (word; also read as a bitfield: bit 0 = "in 3D/dual mode")
//   +0x08  zp0       (zone 0)
//   +0x0c  zp1       (zone 1)
//   +0x10  zp2       (original/unscaled zone)
//   +0x14  (word) dx / vector.x
//   +0x16  (word) dy / vector.y
//   +0x18  (word) single-width x
//   +0x1a  (word) single-width y
//   +0x20  stack     (top of operand stack; grows downward)
//   +0x24  zp2ref    (original-zone equality sentinel)
//   +0x28  gs        (graphics state)
//   +0x30  refPt     (point index of the reference point)
//   +0x34  zp0Idx    (current point of zone 0)
//   +0x38  zp1Idx    (current point of zone 1)
//   +0x3e  (word)      repeat counter consumed by the current handler
//   +0x40  (word)      computed "AA" / direction field
//   +0x44  move      fn(ctx, zone, point, distance)
//   +0x48  project   fn(ctx, dx, dy)
//   +0x4c  dual      fn(ctx, dx, dy)   (3D projection)
//   +0x54  read/round fn(ctx, value)
//   +0x98  round     fn(gs, distance)
//
// A zone is:
//   +0x00 .. +0x0c  org.x / org.y / cur.x / cur.y (int* per point)
//   +0x10  cur  (short*[2]: current x,y -- read as short arrays by fnt_MDRP)
//   +0x14  cur+8 (short y)
//   +0x18  org  (short*[2])
//   +0x1c  (short) end point + 1
//   +0x20  tags (byte*)
//   +0x24  contours (short*)
//
// The graphics state (+0x28):
//   +0x04  free-vector table (int*; [1] = the free x/y vector)
//   +0x08  cvt   (int*)
//   +0x0c  (word) single-width / point size
//   +0x0e  (word) loop value
//   +0x58  scan control
//   +0x64  scan control / +0x66 (word) scan type
//   +0x68  instruction control
//   +0x86  (word) minimum distance for AA
//   +0x8a  byte   in-instruction-control flag
//   +0xb6  byte   grayscale
//   +0xb7  byte   subpixel flags
//   +0xc0  AA vector table (short[4] per row: x, y, ...)
//   +0xc4  AA distance table (short*)
//   +0xc8  byte   backend-compatibility mode

struct TTExecCtx;

void fnt_SH_Common(void* ctx, int* a, int* b);       // 0x008ad850
void __fastcall fnt_SHP_Common(void* unused, TTExecCtx* ctx, int distance); // 0x008ad950 (ctx in edx)
int  fnt_GetCVTScale(void* ctx);                     // 0x008ac370
void fnt_MovePoint(void* ctx, void* zone, int point, int distance); // 0x008ac1a0
int  util_FixDiv(int a, int b);                      // 0x008d16d0
int  util_FixMul(int a, int b);                      // 0x008d1590
int  util_ShortFracMul(int a, int b);                // 0x008d1670
int  util_MulDiv(int a, int b, int c);               // 0x008d1600
int  util_EuclidianDistance(int a, int b);           // 0x008d17d0

struct TTGraphicsState {
    char           mPad00[0x04];
    int*           mFreeVec;    // +0x04
    int*           mCvt;        // +0x08
    unsigned short mSingleW;    // +0x0c
    unsigned short mLoopVal;    // +0x0e
    char           mPad10[0x48];
    unsigned int   mScanCtrl;   // +0x58
    char           mPad5c[0x08];
    unsigned short mScanCtrl2;  // +0x64 (word; the dword at +0x64 is updated by SCANCTRL)
    unsigned short mScanType;   // +0x66
    unsigned int   mInstrCtrl;  // +0x68
    char           mPad6c[0x1a];
    short          mMinDist;    // +0x86
    char           mPad88[0x02];
    unsigned char  mChanged;    // +0x8a
    char           mPad8b[0x0d];
    int (*mRoundFn)(void*, int); // +0x98
    char           mPad9c[0x1a];
    unsigned char  mGray;       // +0xb6
    unsigned char  mSubpixel;   // +0xb7
    char           mPadb8[0x08];
    short*         mAaVec;      // +0xc0
    short*         mAaDist;     // +0xc4
    unsigned char  mBackend;    // +0xc8
};

struct TTZone {
    int*   mOrgX;     // +0x00
    int*   mOrgY;     // +0x04
    int*   mCurX;     // +0x08
    int*   mCurY;     // +0x0c
    short* mCurS;     // +0x10 (current x,y as shorts: [0]=x [1]=y)
    short* mOrgS;     // +0x14 (original x,y as shorts)
    unsigned char* mFlags;     // +0x18 (per-point flag bytes: bit0 = on-curve)
    char   mPad1c[0x00];
};

struct TTExecCtx {
    unsigned char* mIP;          // +0x00
    unsigned short mOpcode;      // +0x04
    char           mPad06[0x02];
    TTZone*        mZp0;         // +0x08
    TTZone*        mZp1;         // +0x0c
    TTZone*        mZp2;         // +0x10
    short          mVecX;        // +0x14
    short          mVecY;        // +0x16
    short          mSingleX;     // +0x18
    short          mSingleY;     // +0x1a
    char           mPad1c[0x04];
    int*           mStack;       // +0x20
    TTZone*        mZp2Ref;      // +0x24
    TTGraphicsState* mGS;        // +0x28
    char           mPad2c[0x04];
    int            mRefPt;       // +0x30
    int            mZp0Idx;      // +0x34
    int            mZp1Idx;      // +0x38
    char           mPad3c[0x02];
    short          mRepeat;      // +0x3e
    short          mAaField;     // +0x40
    int (*mMoveFn)(void*, TTZone*, int, int);   // +0x44
    int (*mProjFn)(void*, int, int);            // +0x48
    int (*mDualFn)(void*, int, int);            // +0x4c
    int (*mReadFn)(void*, int);                 // +0x54
    char           mPad58[0x40];
    int (*mRoundFn)(void*, int);                // +0x98
};

#define GS(c)   ((c)->mGS)

static inline int  popInt(TTExecCtx* c) { c->mStack -= 1; return *c->mStack; }
static inline void pushInt(TTExecCtx* c, int v) { *c->mStack = v; c->mStack += 1; }

// --------------------------------------------------------------------------- handlers

// @ 0x008adac0
void fnt_SHE(TTExecCtx* c)
{
    int x = 0;
    fnt_SH_Common(c, &x, &x);
    c->mStack -= 1;
    int idx = *c->mStack;
    unsigned char* z = (unsigned char*)c->mZp2 + idx * 0x2c;
    int n = *(short*)(z + 0x1c);
    short* orgS = *(short**)(z + 0x24);
    short refY = orgS[n * 2 - 2];
    short refX = *(short*)*(void**)(z + 0x20);
    if ((int*)(z + 0) != &x)
        x = -1;
    (void)refX;
    (void)refY;
}

// @ 0x008adbe0
void fnt_SHPIX(TTExecCtx* c)
{
    int pix = popInt(c);
    int dx = 0;
    int dy = 0;
    if (c->mSingleX != 0)
        dx = util_ShortFracMul(pix, (unsigned short)c->mSingleX);
    if (c->mSingleY != 0)
        dy = util_ShortFracMul(pix, (unsigned short)c->mSingleY);
    (void)dy;
    fnt_SHP_Common((void*)0, c, dx);
}

// @ 0x008adc30
void fnt_IP(TTExecCtx* c)
{
    TTZone* zp1 = c->mZp1;
    TTZone* zp2 = c->mZp2;
    TTZone* zp0 = c->mZp0;
    int zp0Idx = c->mZp0Idx;
    int idx = c->mZp1Idx;
    int scale = 0x10000;
    int d1 = c->mProjFn(c, zp1->mOrgX[idx] - zp0->mOrgX[zp0Idx],
                           zp1->mOrgY[idx] - zp0->mOrgY[zp0Idx]);
    int d2 = c->mDualFn(c, zp1->mCurX[idx] - zp0->mCurX[zp0Idx],
                           zp1->mCurY[idx] - zp0->mCurY[zp0Idx]);
    if (d2 != 0)
        scale = util_FixDiv(d1, d2);
    short rep = c->mRepeat;
    if (rep < 0) {
        c->mRepeat = 0;
        return;
    }
    do {
        c->mStack -= 1;
        int p = *c->mStack;
        int dd = c->mDualFn(c, zp2->mCurX[p] - zp0->mCurX[zp0Idx],
                               zp2->mCurY[p] - zp0->mCurY[zp0Idx]);
        int moved = util_FixMul(dd, scale);
        int orig = c->mProjFn(c, zp2->mOrgX[p] - zp0->mOrgX[zp0Idx],
                                 zp2->mOrgY[p] - zp0->mOrgY[zp0Idx]);
        c->mMoveFn(c, zp2, p, moved - orig);
        rep--;
    } while (rep >= 0);
    c->mRepeat = 0;
}

// @ 0x008add80
void fnt_MSIRP(TTExecCtx* c)
{
    int dist = popInt(c);
    TTZone* zp0 = c->mZp0;
    int refPt = c->mRefPt;
    TTZone* zp1 = c->mZp1;
    int p = popInt(c);
    if (zp1 == c->mZp2Ref) {
        int a = util_ShortFracMul(dist, c->mVecX);
        zp1->mCurX[p] = a + zp0->mCurX[refPt];
        int b = util_ShortFracMul(dist, c->mVecY);
        zp1->mCurY[p] = b + zp0->mCurY[refPt];
        zp1->mOrgX[p] = zp1->mCurX[p];
        zp1->mOrgY[p] = zp1->mCurY[p];
    }
    int d = c->mProjFn(c, zp1->mCurX[p] - zp0->mCurX[refPt],
                          zp1->mCurY[p] - zp0->mCurY[refPt]);
    c->mMoveFn(c, zp1, p, dist - d);
    c->mZp0Idx = refPt;
    c->mZp1Idx = p;
    if (c->mOpcode & 1)
        c->mRefPt = p;
}

// @ 0x008ade50
void fnt_IUP(TTExecCtx* c)
{
    TTZone* zp0 = c->mZp0;
    TTZone* zp1 = c->mZp1;
    int k = c->mRefPt;
    int baseY = zp0->mOrgX[k];
    int baseX = zp0->mOrgY[k];
    int reps = c->mRepeat;
    if (reps < 0) {
        c->mRepeat = 0;
        return;
    }
    do {
        c->mStack -= 1;
        int p = *c->mStack;
        int d = c->mProjFn(c, zp1->mOrgX[p] - baseY, zp1->mOrgY[p] - baseX);
        c->mMoveFn(c, zp1, p, -d);
        reps--;
    } while (reps >= 0);
    c->mRepeat = 0;
}

// @ 0x008aded0
void fnt_SHP(TTExecCtx* c)
{
    int k1 = popInt(c);
    int k2 = popInt(c);
    TTZone* zp0 = c->mZp0;
    TTZone* zp1 = c->mZp1;
    int d = c->mProjFn(c, zp0->mCurX[k1] - zp1->mCurX[k2],
                          zp0->mCurY[k1] - zp1->mCurY[k2]);
    int half = d >> 1;
    c->mMoveFn(c, zp0, k2, half);
    c->mMoveFn(c, zp1, k1, half - d);
}

// @ 0x008adf40
void fnt_MDAP0(TTExecCtx* c)
{
    c->mStack -= 1;
    GS(c)->mMinDist = *(short*)c->mStack;
}

// @ 0x008adf60
void fnt_FLIPPT(TTExecCtx* c)
{
    unsigned char* const flags = c->mZp0->mFlags;
    int* p = c->mStack;
    for (short n = c->mRepeat; n >= 0; n--) {
        p -= 1;
        flags[*p] ^= 1;
    }
    c->mRepeat = 0;
    c->mStack = p;
}

// @ 0x008adfa0
void fnt_FLIPRGON(TTExecCtx* c)
{
    int* p = c->mStack;
    int hi = p[-1];
    p -= 1;
    int lo = p[-1];
    p -= 1;
    unsigned char* const flags = c->mZp0->mFlags;
    for (short i = (short)(hi - lo); i >= 0; i--)
        flags[lo++] |= 1;
    c->mStack = p;
}

// @ 0x008adfe0
void fnt_FLIPRGOFF(TTExecCtx* c)
{
    int* p = c->mStack;
    int hi = p[-1];
    p -= 1;
    int lo = p[-1];
    p -= 1;
    unsigned char* const flags = c->mZp0->mFlags;
    for (short i = (short)(hi - lo); i >= 0; i--)
        flags[lo++] &= 0xfe;
    c->mStack = p;
}

// @ 0x008ae020
void fnt_SCANCTRL(TTExecCtx* c)
{
    c->mStack -= 1;
    unsigned* const sc = (unsigned*)((char*)GS(c) + 0x64);
    *sc = (*sc & 0xffff0000) | (unsigned)*c->mStack;
}

// @ 0x008ae040
void fnt_INSTCTRL(TTExecCtx* c)
{
    c->mStack -= 1;
    unsigned v = (unsigned)*c->mStack;
    if (v > 7)
        return;
    switch (v) {
    case 0: GS(c)->mScanType = 5; return;
    case 1: GS(c)->mScanType = 1; return;
    case 2:
    case 3:
    case 6:
    case 7: GS(c)->mScanType = 0; return;
    case 4: GS(c)->mScanType = 7; return;
    case 5: GS(c)->mScanType = 3; return;
    }
}

// @ 0x008ae0b0
void fnt_SCFS(TTExecCtx* c)
{
    c->mStack -= 1;
    unsigned sel = (unsigned)*c->mStack;
    c->mStack -= 1;
    unsigned val = (unsigned)*c->mStack;
    if (GS(c)->mBackend == 0)
        return;
    if (sel == 1) {
        GS(c)->mInstrCtrl ^= (GS(c)->mInstrCtrl ^ val) & 1;
        return;
    }
    if (sel == 2)
        GS(c)->mInstrCtrl ^= (GS(c)->mInstrCtrl ^ val) & 2;
}

// @ 0x008ae100
void fnt_AA(TTExecCtx* c)
{
    TTGraphicsState* g = GS(c);
    short saveX = c->mVecX;
    short saveY = c->mVecY;
    short saveAa = c->mAaField;
    c->mStack -= 1;
    int p = *c->mStack;
    int k = c->mRefPt * 4;
    int vx = c->mZp1->mCurX[p] - *(int*)(k + (char*)c->mZp0->mCurX);
    int vy = c->mZp1->mCurY[p] - *(int*)(k + (char*)c->mZp0->mCurY);
    bool negY = vy < 0;
    if (negY) vy = -vy;
    bool negX = vx < 0;
    if (negX) vx = -vx;
    bool swapped = vx < vy;
    if (swapped) { int t = vx; vx = vy; vy = t; }

    int a = vx << 10;
    int b = vy << 10;
    int len = util_EuclidianDistance(b, a);
    if (len != 0) {
        b = util_FixDiv(b, len);
        a = util_FixDiv(a, len);
    }
    short* vecTable = g->mAaVec;
    short* distTable = g->mAaDist;
    int best = 0x280;
    int bestIdx = -1;
    for (short i = 0; i < 0x14; i++) {
        short dy = *distTable++;
        if (dy >= best)
            break;
        c->mVecX = *vecTable;
        short yy = vecTable[2];
        c->mVecY = yy;
        vecTable += 4;
        int dx = (int)c->mVecX - (short)((a + 1) >> 2);
        if (dx < 0) dx = -dx;
        int e = (int)yy - (short)((b + 1) >> 2);
        if (e < 0) e = -e;
        int score = (dx < e) ? ((dx >> 1) + e) : ((e >> 1) + dx);
        if (score < 0xc9107b8) {
            int s = util_ShortFracMul(vy, yy) + util_ShortFracMul(vx, c->mVecX);
            if (s < 0) s = -s;
            int d = ((g->mMinDist * s) >> 6) + (int)dy;
            if (d < best) {
                best = d;
                bestIdx = i;
            }
        }
    }
    int move = 0;
    if (bestIdx >= 0) {
        c->mVecX = g->mAaVec[bestIdx * 4];
        c->mVecY = g->mAaVec[bestIdx * 4 + 2];
        if (swapped) { short t = c->mVecX; c->mVecX = c->mVecY; c->mVecY = t; }
        if (negX) c->mVecX = -c->mVecX;
        if (negY) c->mVecY = -c->mVecY;
        short s = (short)(((int)c->mSingleY * c->mVecY + 0x2000) >> 14)
                + (short)(((int)c->mSingleX * c->mVecX + 0x2000) >> 14);
        unsigned u = (unsigned)(s + 0x3ff);
        if (u <= 0x7fe)
            s = (short)(((s >= 0) ? 0x4000 : 0x4000 - 0x8000));
        c->mAaField = s;
        move = util_ShortFracMul(c->mZp1->mCurX[p] - c->mZp0->mCurX[p], c->mVecX)
             + util_ShortFracMul(c->mZp1->mCurY[p] - c->mZp0->mCurY[p], c->mVecY);
    }
    fnt_MovePoint(c, c->mZp1, p, move);
    c->mVecX = saveX;
    c->mVecY = saveY;
    c->mAaField = saveAa;
}

// @ 0x008ae420
void fnt_svtca_lo(TTExecCtx* c)
{
    int* out = c->mStack;
    unsigned char* in = c->mIP;
    for (short n = (short)(c->mOpcode - 0xb0); n >= 0; n--) {
        *out = *in;
        out++;
        in++;
    }
    c->mStack = out;
    c->mIP = in;
}

// @ 0x008ae460
void fnt_a0b0(TTExecCtx* c)
{
    unsigned char* in = c->mIP;
    int n = (unsigned short)*in;
    unsigned char* next = in + 1;
    int* out = c->mStack;
    c->mIP = next;
    n -= 1;
    if ((short)n >= 0) {
        do {
            *out = *next;
            out++;
            next++;
            n--;
        } while ((short)n >= 0);
    }
    c->mIP = next;
    c->mStack = out;
}

// @ 0x008ae4a0
void fnt_a0b8(TTExecCtx* c)
{
    int n = (short)(c->mOpcode - 0xb8);
    int* out = c->mStack;
    unsigned char* in = c->mIP;
    for (; n >= 0; n--) {
        unsigned short v = (unsigned short)(((unsigned short)in[0] << 8) + in[1]);
        *out = (short)v;
        out++;
        in += 2;
    }
    c->mIP = in;
    c->mStack = out;
}

// @ 0x008ae4f0
void fnt_a0b8b(TTExecCtx* c)
{
    unsigned char* in = c->mIP;
    int n = (unsigned short)*in;
    unsigned char* next = in + 1;
    int* out = c->mStack;
    c->mIP = next;
    n -= 1;
    if ((short)n >= 0) {
        do {
            unsigned short v = (unsigned short)(((unsigned short)next[0] << 8) + next[1]);
            *out = (short)v;
            out++;
            next += 2;
            n--;
        } while ((short)n >= 0);
    }
    c->mStack = out;
    c->mIP = next;
}

// @ 0x008ae540
void fnt_MD1(TTExecCtx* c)
{
    int v = popInt(c);
    int idx = popInt(c);
    GS(c)->mFreeVec[idx] = v;
}

// @ 0x008ae560
void fnt_MD0(TTExecCtx* c)
{
    c->mStack -= 1;
    int* p = c->mStack;
    *p = GS(c)->mFreeVec[*p];
    c->mStack += 1;
}

// @ 0x008ae580
void fnt_WCVT(TTExecCtx* c)
{
    int scale = fnt_GetCVTScale(c);
    int v = popInt(c);
    int idx = popInt(c);
    if (scale != 0x10000 && scale != 0)
        v = util_FixDiv(v, scale);
    GS(c)->mCvt[idx] = v;
}

// @ 0x008ae5d0
void fnt_RS(TTExecCtx* c)
{
    int arg = popInt(c);
    int idx = popInt(c);
    TTGraphicsState* g = GS(c);
    g->mCvt[idx] = g->mRoundFn(g, arg);
}

// @ 0x008ae600
void fnt_ROUND(TTExecCtx* c)
{
    c->mStack -= 1;
    int* p = c->mStack;
    *p = c->mReadFn(c, *p);
    c->mStack += 1;
}

// @ 0x008ae630
void fnt_GC(TTExecCtx* c)
{
    c->mStack -= 1;
    int idx = *c->mStack;
    TTZone* z = c->mZp2;
    int v;
    if (c->mOpcode & 1)
        v = c->mDualFn(c, z->mCurX[idx], z->mCurY[idx]);
    else
        v = c->mProjFn(c, z->mOrgX[idx], z->mOrgY[idx]);
    *c->mStack = v;
    c->mStack += 1;
}

// @ 0x008ae690
void fnt_MD(TTExecCtx* c)
{
    int v = popInt(c);
    int idx = popInt(c);
    TTZone* z = c->mZp2;
    int d = c->mProjFn(c, z->mOrgX[idx], z->mOrgY[idx]);
    c->mMoveFn(c, z, idx, v - d);
    if (z == c->mZp2Ref) {
        z->mCurX[idx] = z->mOrgX[idx];
        z->mCurY[idx] = z->mOrgY[idx];
    }
}

// @ 0x008ae6f0
void fnt_MDRP(TTExecCtx* c)
{
    int k = popInt(c);
    int idx = popInt(c);
    TTZone* zp0 = c->mZp0;
    TTZone* zp1 = c->mZp1;
    int d;
    if ((c->mOpcode - 1) & 1) {
        d = c->mDualFn(c, (int)zp0->mOrgS[idx * 2] - (int)zp1->mOrgS[k * 2],
                          (int)zp0->mOrgS[idx * 2 + 1] - (int)zp1->mOrgS[k * 2 + 1]);
        d = GS(c)->mRoundFn(GS(c), d);
    } else {
        d = c->mProjFn(c, zp0->mOrgX[idx] - zp1->mOrgX[k],
                          zp0->mOrgY[idx] - zp1->mOrgY[k]);
    }
    pushInt(c, d);
}

// @ 0x008ae7a0
void fnt_MPPEM(TTExecCtx* c)
{
    TTGraphicsState* g = GS(c);
    int w = g->mSingleW;
    if (g->mGray == 0)
        w = ((util_FixMul(w * 2, fnt_GetCVTScale(c)) + 1) >> 1) & 0xffff;
    pushInt(c, w);
}

// @ 0x008ae7f0
void fnt_MPS(TTExecCtx* c)
{
    pushInt(c, GS(c)->mLoopVal);
}

// @ 0x008ae810
void fnt_GETINFO(TTExecCtx* c)
{
    c->mStack -= 1;
    unsigned char* slot = (unsigned char*)c->mStack;
    unsigned v = *(unsigned*)slot;
    unsigned r = (v & 1) != 0;
    if ((v & 2) != 0 && (GS(c)->mSubpixel & 1) != 0)
        r |= 0x100;
    if ((v & 4) != 0 && (GS(c)->mSubpixel & 2) != 0)
        r |= 0x200;
    *(unsigned*)slot = r;
    c->mStack += 1;
}

// @ 0x008ae860
void fnt_INSTRCTRL_ON(TTExecCtx* c)
{
    GS(c)->mChanged = 1;
}

// @ 0x008ae870
void fnt_INSTRCTRL_OFF(TTExecCtx* c)
{
    GS(c)->mChanged = 0;
}

// @ 0x008ae880
void fnt_POP_NOOP(TTExecCtx* c)
{
    c->mStack -= 1;
}

// @ 0x008ae890
void fnt_Arithmetic(TTExecCtx* c)
{
    int* st = c->mStack;
    int b = st[-1];
    int a = st[-2];
    unsigned op = (unsigned)(c->mOpcode - 0x50);
    st -= 2;
    if (op > 0x3c) {
        c->mStack = st;
        return;
    }
    int r;
    switch (op) {
    case 0x00: r = a <  b; break;
    case 0x01: r = a <= b; break;
    case 0x02: r = a >  b; break;
    case 0x03: r = a >= b; break;
    case 0x04: r = a == b; break;
    case 0x05: r = a != b; break;
    case 0x06: r = (a != 0) && (b != 0); break;
    case 0x07: r = (a != 0) || (b != 0); break;
    case 0x08: r = a + b; break;
    case 0x09: r = a - b; break;
    case 0x0a: r = util_MulDiv(a, b, 0); break;
    case 0x0b: r = (a << 6) / b; break;
    case 0x0c: r = (a < b) ? b : a; break;
    case 0x0d: r = (a > b) ? b : a; break;
    case 0x0e: r = util_MulDiv(a, b, 1); break;
    case 0x0f: r = util_MulDiv(a, b, 2); break;
    default:   r = util_MulDiv(a, b, 3); break;
    }
    st[0] = r;
    c->mStack = st + 1;
}
