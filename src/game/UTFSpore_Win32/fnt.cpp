// src/game/UTFSpore_Win32/fnt.cpp -- migrated from slice(s) s008adac0, s008abc50 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/fnt.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int util_FixMul(int a, int b);                     // 0x008d1590
extern "C" int util_FixDiv(int a, int b);                     // 0x008d16d0
extern "C" int util_ShortFracMul(int a, int b);               // 0x008d1670
extern "C" int util_EuclidianDistance(int a, int b);          // 0x008d17d0
extern "C" void __cdecl longjmp(int* buf, int val);
extern "C" unsigned int fnt_RoundToGrid(int d, int a, int b);              // 0x008ac040
extern "C" unsigned int fnt_RoundToHalfGrid(int d, int a, int b);          // 0x008ac070
extern "C" unsigned int FUN_008ac010(int d, int a, int b);                 // 0x008ac010extern "C" int FUN_008ac360(int d, int a, int b);                          // 0x008ac360
extern "C" int FUN_008ac0b0(void* st, int d, int a);                       // 0x008ac0b0
extern "C" int FUN_008ac100(void* st, int d, int a);                       // 0x008ac100
extern "C" int __cdecl setjmp3(void* jb, int arg);                         // 0x011e0cac

// ---- items of slice s008abc50 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint32;
struct tsiMemObject;
extern "C" int util_FixMul(int a, int b);                     // 0x008d1590
extern "C" int util_FixDiv(int a, int b);                     // 0x008d16d0
extern "C" int util_ShortFracMul(int a, int b);               // 0x008d1670
extern "C" int util_EuclidianDistance(int a, int b);          // 0x008d17d0
extern "C" void __cdecl longjmp(int* buf, int val);
struct blueZone_tag { int minPix; int maxPix; int refPix; };
struct stemSnap_tag { int minPix; int maxPix; int refPix; };
struct FFT1HintClass {                  // size 0x378
    tsiMemObject* mem;                  // +0x000
    int xPixelsPerEm;                   // +0x004
    int yPixelsPerEm;                   // +0x008
    int xScale;                         // +0x00c
    int yScale;                         // +0x010
    int xpos;                           // +0x014
    int ypos;                           // +0x018
    int upem;                           // +0x01c
    blueZone_tag pBlueZones[14];        // +0x020
    int bluevalues[14];                 // +0x0c8
    int numBlueValues;                  // +0x100
    int BlueFuzz;                       // +0x104
    int BlueScale;                      // +0x108
    int BlueShift;                      // +0x10c
    int BlueShiftPix;                   // +0x110
    stemSnap_tag pSnapV[12];            // +0x114
    stemSnap_tag pSnapH[12];            // +0x1a4
    int snapHWVals[12];                 // +0x234
    int snapVWVals[12];                 // +0x264
    int numSnapV;                       // +0x294
    int numSnapH;                       // +0x298
    int numSnapVZones;                  // +0x29c
    int numSnapHZones;                  // +0x2a0
    int StdHW;                          // +0x2a4
    int StdVW;                          // +0x2a8
    short numHintSets;                  // +0x2ac
    short* hintmarkers_x_ptr;           // +0x2b0
    short  hintmarkers_x_ml;            // +0x2b4
    short  num_hintmarkers_x;           // +0x2b6
    short* hintmarkers_y_ptr;           // +0x2b8
    short  hintmarkers_y_ml;            // +0x2bc
    short  num_hintmarkers_y;           // +0x2be
    short* xgcount_ptr;                 // +0x2c0
    short  xgcount_ml;                  // +0x2c4
    short  num_xgcount;                 // +0x2c6
    short* ygcount_ptr;                 // +0x2c8
    short  ygcount_ml;                  // +0x2cc
    short  num_ygcount;                 // +0x2ce
    short* xbgcount_ptr;                // +0x2d0
    short  xbgcount_ml;                 // +0x2d4
    short  numxbgcount;                 // +0x2d6
    short* ybgcount_ptr;                // +0x2d8
    short  ybgcount_ml;                 // +0x2dc
    short  numybgcount;                 // +0x2de
    short* xOrus_ptr;                   // +0x2e0
    short  xOrus_num_ml;                // +0x2e4
    short  numxOrus;                    // +0x2e6
    short* yOrus_ptr;                   // +0x2e8
    short  yOrus_num_ml;                // +0x2ec
    short  numyOrus;                    // +0x2ee
    short* nxIntOrus_ptr;               // +0x2f0
    short  xInt_num_ml;                 // +0x2f4
    short  numxIntOrus;                 // +0x2f6
    short* nyIntOrus_ptr;               // +0x2f8
    short  yInt_num_ml;                 // +0x2fc
    short  numyIntOrus;                 // +0x2fe
    void*  x_hints;                     // +0x300  (hints_t*)
    void*  y_hints;                     // +0x304  (hints_t*)
    void*  x_strokes;                   // +0x308  (extraStroke_t*)
    void*  y_strokes;                   // +0x30c  (extraStroke_t*)
    short num_x_hint_sets_ml;           // +0x310
    short num_y_hint_sets_ml;           // +0x312
    void*  x_edges;                     // +0x314  (extraEdge_t*)
    void*  y_edges;                     // +0x318
    int onepix;                         // +0x31c
    int pixrnd;                         // +0x320
    int pixfix;                         // +0x324
    int suppressOvershoots;             // +0x328
    short* extraXStrokeOrus_ptr;        // +0x32c
    short  extraXStrokeOrus_ml;         // +0x330
    short  numextraXStroke;             // +0x332
    short* extraYStrokeOrus_ptr;        // +0x334
    short  extraYStrokeOrus_ml;         // +0x338
    short  numextraYStroke;             // +0x33a
    short* extraXStrokeGlyphCount_ptr;  // +0x33c
    short  extraXStrokeGlyphCount_ml;   // +0x340
    short  numextraXStrokeGlyphCount;   // +0x342
    short* extraYStrokeGlyphCount_ptr;  // +0x344
    short  extraYStrokeGlyphCount_ml;   // +0x348
    short  numextraYStrokeGlyphCount;   // +0x34a
    short num_tcb;                      // +0x34c
    short numextraXEdge;                // +0x34e
    short numextraYEdge;                // +0x350
    short extraEdgeX_ml;                // +0x352
    short extraEdgeY_ml;                // +0x354
    short* extraXEdgeThresh_ptr;        // +0x358
    short* extraYEdgeThresh_ptr;        // +0x35c
    short* extraXEdgeDelta_ptr;         // +0x360
    short* extraYEdgeDelta_ptr;         // +0x364
    short* extraXEdgeIndex_ptr;         // +0x368
    short* extraYEdgeIndex_ptr;         // +0x36c
    short* extraXEdgeGlyphCount_ptr;    // +0x370
    short* extraYEdgeGlyphCount_ptr;    // +0x374
};
extern "C" unsigned int fnt_RoundToGrid(int d, int a, int b);              // 0x008ac040
extern "C" unsigned int fnt_RoundToHalfGrid(int d, int a, int b);          // 0x008ac070
extern "C" unsigned int FUN_008ac010(int d, int a, int b);                 // 0x008ac010extern "C" int FUN_008ac360(int d, int a, int b);                          // 0x008ac360
extern "C" int FUN_008ac0b0(void* st, int d, int a);                       // 0x008ac0b0
extern "C" int FUN_008ac100(void* st, int d, int a);                       // 0x008ac100
struct TM_State {                       // shared prefix, size >= 0x24
    int   curve[3];                     // +0x00 (three 4-byte values)
    int*  cx;                           // +0x0c  x coordinate array pointer
    int*  cy;                           // +0x10  y coordinate array pointer
    short opFlags;                      // +0x14
    short pad16;
    int   vec1;                         // +0x18
    int   scale;                        // +0x1c
    int*  sBase;                        // +0x20  operand stack base (grows down)
};
struct T1Exec {                         // full charstring decode context, size 0x60
    TM_State s;                         // +0x00
    void*    fp;                        // +0x24  function pointers block / free list
    int      pad28;                     // +0x28
    int      pad2c;                     // +0x2c  == param_5 (interp or no-interp)
    int      pad30;                     // +0x30
    int      pad34;                     // +0x34
    char     opbuf[0x1c];               // +0x38  the 28-byte T1 opcode buffer
    /* +0x38: [0x38] v[0]  [0x3c] vector[0]  [0x40] vector[1]  [0x44] op1
       +0x48: [0x48] op2    [0x4c] op3       [0x50] interp */
};
extern "C" int __cdecl setjmp3(void* jb, int arg);                         // 0x011e0cac
static inline int SnapProjScale(unsigned short c)
{
    if ((unsigned short)(c + 0x3ff) <= 0x7fe) {
        int t = ((short)c >= 0) ? 1 : 0;
        return ((t - 1) & 0xffff8000) + 0x4000;
    }
    return c;
}
struct T1Decode {
    uint32 ip;          // +0x00
    int    op;          // +0x04
    void*  m0;          // +0x08
    void*  m1;          // +0x0c
    void*  m2;          // +0x10
    short  xx;          // +0x14
    short  xy;          // +0x16
    short  yx;          // +0x18
    short  yy;          // +0x1a
    short  tx;          // +0x1c
    short  ty;          // +0x1e
    int*   sptr;        // +0x20
    void*  ctx;         // +0x24
    char*  env;         // +0x28
    void*  interp;      // +0x2c
    int    z30;         // +0x30
    int    z34;         // +0x34
    int    z38;         // +0x38
    short  mode;        // +0x3c
    short  pad3e;
    short  projScale;   // +0x40
    short  pad42;
    void*  movePoint;   // +0x44
    void*  project;     // +0x48
    void*  dualProject; // +0x4c
    void*  loop;        // +0x50
    void*  cvtEntry;    // +0x54
    void*  singleWidth; // +0x58
};
// ---- items of slice s008abc50 end

// ---- items of slice s008adac0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct TTExecCtx;
void fnt_SH_Common(void* ctx, int* a, int* b);       // 0x008ad850
void __fastcall fnt_SHP_Common(void* unused, TTExecCtx* ctx, int distance); // 0x008ad950 (ctx in edx)
int  fnt_GetCVTScale(void* ctx);                     // 0x008ac370
void fnt_MovePoint(void* ctx, void* zone, int point, int distance); // 0x008ac1a0
int  util_MulDiv(int a, int b, int c);               // 0x008d1600
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
// ---- items of slice s008adac0 end

// @ 0x008abf90
void* fnt_SuperRound_Err(FFT1HintClass* h)
{
    longjmp((int*)((char*)h + 0x5c), 0x1101);
    return 0;
}

// @ 0x008abfe0
uint32 FUN_008abfe0(int unused, int d, int a)
{
    (void)unused;
    uint32 r;
    if (d >= 0) {
        r = (uint32)((a + d) & 0xffffffc0u);
    } else {
        r = (uint32)(0u - ((unsigned)(a - d) & 0xffffffc0u));
    }
    if ((int)(r ^ (uint32)d) < 0 && d != 0)
        r = 0;
    return r;
}

// @ 0x008ac010
uint32 FUN_008ac010(int unused, int d, int a)
{
    (void)unused;
    uint32 r;
    if (d >= 0)
        r = (uint32)((d + a + 0x3f) & 0xffffffc0u);
    else
        r = (uint32)(0u - ((unsigned)(0x3f + (a - d)) & 0xffffffc0u));
    if ((int)(r ^ (uint32)d) < 0 && d != 0)
        r = 0;
    return r;
}

// @ 0x008ac040
uint32 fnt_RoundToGrid(int unused, int d, int a)
{
    (void)unused;
    uint32 r;
    if (d >= 0)
        r = (uint32)((d + a + 0x20) & 0xffffffc0u);
    else
        r = (uint32)(0u - ((unsigned)(0x20 + (a - d)) & 0xffffffc0u));
    if ((int)(r ^ (uint32)d) < 0 && d != 0)
        r = 0;
    return r;
}

// @ 0x008ac070
uint32 fnt_RoundToHalfGrid(int unused, int d, int a)
{
    (void)unused;
    uint32 r;
    if (d >= 0)
        r = (uint32)(((a + d) & 0xffffffc0u) + 0x20);
    else
        r = (uint32)(0xffffffe0u - ((unsigned)(a - d) & 0xffffffc0u));
    if ((int)(r ^ (uint32)d) < 0 && d != 0)
        r = (uint32)((((int)(d <= 0) - 1) & 0x40) + 0xFFFFFFE0u);
    return r;
}

// @ 0x008ac0b0
int FUN_008ac0b0(void* st, int d, int a)
{
    int* p  = *(int**)((char*)st + 0x28);
    int  c8 = *(int*)((char*)p + 0x80) - *(short*)((char*)p + 0x7e);
    int  m  = *(int*)((char*)p + 0x74);
    int  e  = *(short*)((char*)p + 0x7e);
    int  r;
    if (d >= 0) {
        r = ((unsigned)(c8 + d + a) & (unsigned)m) + e;
    } else {
        r = 0u - (((unsigned)(c8 - d + a) & (unsigned)m) + e);
    }
    if ((r ^ d) < 0 && d != 0)
        r = (e < 1) ? (d <= 0 ? e : -e) : e;
    return r;
}

// @ 0x008ac100
int FUN_008ac100(void* st, int d, int a)
{
    int* p  = *(int**)((char*)st + 0x28);
    int  c8 = *(int*)((char*)p + 0x80) - *(short*)((char*)p + 0x7e);
    int  u  = *(int*)((char*)p + 0x74) >> 14;
    int  e  = *(short*)((char*)p + 0x7e);
    int  r;
    if (d >= 0)
        r = util_FixMul(util_FixDiv(c8 + d + a, u) & 0xffffffc0, u) + e;
    else
        r = -(util_FixMul(util_FixDiv(c8 - d + a, u) & 0xffffffc0, u) + e);
    if ((r ^ d) < 0 && d != 0)
        r = (e < 1) ? (d <= 0 ? e : -e) : e;
    return r;
}

// @ 0x008ac1a0
char* fnt_MovePoint(void* st, int idx, int delta, int flag)
{
    int   v0 = *(unsigned short*)((char*)st + 0x18);
    int   v1 = *(unsigned short*)((char*)st + 0x1a);
    short dy = *(short*)((char*)st + 0x40);
    void** sp    = (void**)st;
    int*   cx    = (int*)sp[0];
    int*   cy    = (int*)sp[1];
    char*  marks = (char*)sp[10];
    char*  r     = 0;

    if (dy == 0x4000) {
        if (v0 != 0) {
            cx[idx] += util_ShortFracMul(delta, v0);
            r = marks + idx;
            *r |= 1;
        }
        if (v1 != 0) {
            cy[idx] += util_ShortFracMul(delta, v1);
            r = marks + idx;
            *r |= 2;
            return r;
        }
    } else {
        if (v0 != 0) {
            cx[idx] += (util_FixMul(delta, util_FixDiv((short)v0 << 4, (int)dy)) + 4) >> 4;
            r = marks + idx;
            *r |= 1;
        }
        if (v1 != 0) {
            cy[idx] += (util_FixMul(delta, util_FixDiv((short)v1 << 4, (int)dy)) + 4) >> 4;
            r = marks + idx;
            *r |= 2;
            return r;
        }
    }
    return r;
}

// @ 0x008ac2a0
int* FUN_008ac2a0(int unused, void** st, int idx, int delta)
{
    int*  p = (int*)*st + idx;
    int*  m;
    (void)unused;
    *p += delta;
    m = (int*)st[10];
    *((char*)m + idx) |= 1;
    return (int*)((char*)m + idx);
}

// @ 0x008ac2d0
int* FUN_008ac2d0(int unused, void** st, int idx, int delta)
{
    int*  p = (int*)st[1] + idx;
    int*  m;
    (void)unused;
    *p += delta;
    m = (int*)st[10];
    *((char*)m + idx) |= 2;
    return (int*)((char*)m + idx);
}

// @ 0x008ac300
int fnt_Project(void* st, int x, int y)
{
    return util_ShortFracMul(x, *(unsigned short*)((char*)st + 0x14)) +
           util_ShortFracMul(y, *(unsigned short*)((char*)st + 0x16));
}

// @ 0x008ac330
int fnt_OldProject(void* st, int x, int y)
{
    return util_ShortFracMul(x, *(unsigned short*)((char*)st + 0x1c)) +
           util_ShortFracMul(y, *(unsigned short*)((char*)st + 0x1e));
}

// @ 0x008ac370
static int fnt_GetCVTScale(T1Exec* s)
{
    int  cx = *(unsigned short*)((char*)s + 0x14);
    int* p  = *(int**)((char*)s + 0x28);
    int  cy = *(unsigned short*)((char*)s + 0x16);
    int  a, b;

    if (cy == 0)
        return *(int*)((char*)p + 0xb8);
    if (cx == 0)
        return *(int*)((char*)p + 0xbc);
    a = util_ShortFracMul(*(int*)((char*)p + 0xbc), (cy * cy + 0x2000) >> 14);
    b = util_ShortFracMul(*(int*)((char*)p + 0xb8), (cx * cx + 0x2000) >> 14);
    return b + a;
}

// @ 0x008ac3e0
int FUN_008ac3e0(T1Exec* s, int idx)
{
    return *(int*)(*(int*)(*(int*)((char*)s + 0x28) + 8) + idx * 4);
}

// @ 0x008ac400
int fnt_GetCVTEntrySlow(T1Exec* s, int idx)
{
    int v = *(int*)(*(int*)(*(int*)((char*)s + 0x28) + 8) + idx * 4);
    return (util_FixMul(v * 2, fnt_GetCVTScale(s)) + 1) >> 1;
}

// @ 0x008ac430
int FUN_008ac430(T1Exec* s)
{
    return *(int*)(*(int*)((char*)s + 0x28) + 0x60);
}

// @ 0x008ac440
int fnt_GetSingleWidthSlow(T1Exec* s)
{
    return util_FixMul(*(int*)(*(int*)((char*)s + 0x28) + 0x60), fnt_GetCVTScale(s));
}

// @ 0x008ac460
int* fnt_ChangeCvt(T1Exec* s, int idx, int delta)
{
    int* p;
    if (*(char*)(*(int*)((char*)s + 0x28) + 0xb6) == 0) {
        int sc = fnt_GetCVTScale(s);
        if (sc != 0x10000 && sc != 0) {
            p = (int*)(*(int*)(*(int*)((char*)s + 0x28) + 8) + idx * 4);
            *p += (util_FixDiv(delta * 2, sc) + 1) >> 1;
            return p;
        }
    }
    p = (int*)(*(int*)(*(int*)((char*)s + 0x28) + 8) + idx * 4);
    *p += delta;
    return p;
}

// @ 0x008ac4c0
void fnt_InterpChars(uint32* st, uint32 ip, uint32 end)
{
    if (st[0xb] != 0) {
        uint32 prev = *st;
        int    tbl  = *(int*)(st[10] + 0x8c);
        *st = ip;
        while ((uint32)*st < end) {
            void* f = *(void**)(st[10] + 0x70);
            short mode;
            if (f == (void*)0x8ac040)
                mode = 1;
            else if (f == (void*)0x8ac070)
                mode = 0;
            else if (f == (void*)0x8abfb0)
                mode = 2;
            else if (f == (void*)0x8abfe0)
                mode = 3;
            else if (f == (void*)0x8ac010)
                mode = 4;
            else if (f == (void*)0x8ac360)
                mode = 5;
            else if (f == (void*)0x8ac0b0)
                mode = 6;
            else if (f == (void*)0x8ac100)
                mode = 7;
            else
                mode = (short)-1;
            *(short*)((char*)st + 0x3c) = mode;
            ((void (__cdecl*)(void*))st[0xb])(st);
            if (st[0xb] == 0)
                break;
            unsigned int op = *(unsigned char*)*st;
            st[1] = op;
            void* h = *(void**)(tbl + op * 4);
            *st += 1;
            ((void (__cdecl*)(void*))h)(st);
        }
        *st = prev;
    }
}

// @ 0x008ac5c0
void fnt_NoInterpChars(uint32* st, uint32 ip, uint32 end)
{
    uint32 prev = *st;
    int    tbl  = *(int*)(st[10] + 0x8c);
    *st = ip;
    while ((uint32)*st < end) {
        unsigned int op = *(unsigned char*)*st;
        st[1] = op;
        void* h = *(void**)(tbl + op * 4);
        *st += 1;
        ((void (__cdecl*)(void*))h)(st);
    }
    *st = prev;
}

// @ 0x008ac600
int fnt_Execute(void* ctx, uint32 ip, uint32 end, char* env, void* interp)
{
    T1Decode d;
    int      cblock[16];
    int      rc;
    void*    t;

    d.z38 = 0;
    d.z34 = 0;
    d.z30 = 0;
    t = *(char*)(env + 0xc8) == 0 ? (char*)ctx + 0x2c : ctx;

    d.m0 = t;
    d.m1 = t;
    d.m2 = t;
    d.ctx = t;
    d.env = env;
    d.xx = 0x4000;
    d.xy = 0;
    d.yx = 0x4000;
    d.yy = 0;
    d.tx = 0x4000;
    d.ty = 0;
    d.project = (void*)0x8ac360;
    d.dualProject = (void*)0x8ac360;
    d.projScale = 0x4000;
    d.movePoint = (void*)0x8ac2a0;
    d.pad42 = 0;
    d.cvtEntry = (void*)0x8ac3e0;
    d.singleWidth = (void*)0x8ac430;

    if (*(unsigned char*)(env + 0xc9) != 1) {
        if (*(unsigned short*)(env + 0x0c) < 2)
            return 0;
        if (*(unsigned char*)(env + 0xb6) == 0) {
            d.cvtEntry = (void*)0x8ac400;
            d.singleWidth = (void*)0x8ac440;
            if (util_FixMul(*(int*)(env + 0x10), *(int*)(env + 0xb8)) < 0x10001)
                return 0;
            if (util_FixMul(*(int*)(env + 0x10), *(int*)(env + 0xbc)) < 0x10001)
                return 0;
        }
        if (*(unsigned char*)(env + 0xc8) == 0 &&
            *(short*)(env + 0x88) != 0) {
            int (*fn)(void*, int) = *(int (**)(void*, int))(env + 0x98);
            *(int*)(env + 0x60) = fn(env, *(short*)(env + 0x88));
        }
    }

    rc = setjmp3(cblock, 0);
    if (rc == 0) {
        *(unsigned short*)(env + 0xca) = 0;
        *(int*)(env + 0xc0) = 0x1432238;
        *(int*)(env + 0xc4) = 0x14322d8;
        d.interp = interp;
        d.loop = interp != 0 ? (void*)0x8ac4c0 : (void*)0x8ac5c0;
        ((void (__cdecl*)(void*, uint32, uint32))d.loop)(&d, ip, end);
        return 0;
    }
    return rc;
}

// @ 0x008ac7a0
static void fnt_ComputeAndCheck_PF_Proj(void* s)
{
    int a = *(short*)((char*)s + 0x1a) * *(short*)((char*)s + 0x16) + 0x2000;
    int b = *(short*)((char*)s + 0x18) * *(short*)((char*)s + 0x14) + 0x2000;
    unsigned short c = (unsigned short)((a >> 14) + (b >> 14));
    if ((unsigned short)(c + 0x3ff) <= 0x7fe)
        c = (unsigned short)SnapProjScale(c);
    *(short*)((char*)s + 0x40) = c;
}

// @ 0x008ac800
void FUN_008ac800(void* s)
{
    *(short*)((char*)s + 0x14) = 0;
    *(short*)((char*)s + 0x18) = 0;
    *(short*)((char*)s + 0x16) = 0x4000;
    *(int*)((char*)s + 0x48) = 0x10cca50;
    *(int*)((char*)s + 0x4c) = 0x10cca50;
    *(short*)((char*)s + 0x1a) = 0x4000;
    *(int*)((char*)s + 0x44) = 0x8ac2d0;
    *(short*)((char*)s + 0x40) = 0x4000;
}

// @ 0x008ac840
void FUN_008ac840(void* s)
{
    *(short*)((char*)s + 0x14) = 0x4000;
    *(short*)((char*)s + 0x16) = 0;
    *(short*)((char*)s + 0x18) = 0x4000;
    *(int*)((char*)s + 0x48) = 0x8ac360;
    *(int*)((char*)s + 0x4c) = 0x8ac360;
    *(short*)((char*)s + 0x1a) = 0;
    *(int*)((char*)s + 0x44) = 0x8ac2a0;
    *(short*)((char*)s + 0x40) = 0x4000;
}

// @ 0x008ac880
void fnt_SPVTCA(void* s)
{
    if (*(unsigned char*)((char*)s + 4) & 1) {
        *(short*)((char*)s + 0x14) = 0x4000;
        *(short*)((char*)s + 0x16) = 0;
        *(int*)((char*)s + 0x48) = 0x8ac360;
        *(short*)((char*)s + 0x40) = *(short*)((char*)s + 0x18);
    } else {
        *(short*)((char*)s + 0x14) = 0;
        *(short*)((char*)s + 0x16) = 0x4000;
        *(int*)((char*)s + 0x48) = 0x10cca50;
        *(short*)((char*)s + 0x40) = *(short*)((char*)s + 0x1a);
    }
    unsigned short c = *(unsigned short*)((char*)s + 0x40);
    if ((unsigned short)(c + 0x3ff) <= 0x7fe)
        *(short*)((char*)s + 0x40) = (short)SnapProjScale(c);
    *(int*)((char*)s + 0x44) = 0x8ac1a0;
    *(int*)((char*)s + 0x4c) = *(int*)((char*)s + 0x48);
}

// @ 0x008ac900
void fnt_SFVTCA(void* s)
{
    if (*(unsigned char*)((char*)s + 4) & 1) {
        *(short*)((char*)s + 0x18) = 0x4000;
        *(short*)((char*)s + 0x1a) = 0;
        *(short*)((char*)s + 0x40) = *(short*)((char*)s + 0x14);
    } else {
        *(short*)((char*)s + 0x18) = 0;
        *(short*)((char*)s + 0x1a) = 0x4000;
        *(short*)((char*)s + 0x40) = *(short*)((char*)s + 0x16);
    }
    unsigned short c = *(unsigned short*)((char*)s + 0x40);
    if ((unsigned short)(c + 0x3ff) <= 0x7fe)
        *(short*)((char*)s + 0x40) = (short)SnapProjScale(c);
    *(int*)((char*)s + 0x44) = 0x8ac1a0;
}

// @ 0x008ac970
void fnt_SPVTL(void* s)
{
    int**  sp = (int**)((char*)s + 0x20);
    int    i2, i1, dx, dy, dist;
    int**  m1 = (int**)*(int**)((char*)s + 0x0c);
    int**  m2 = (int**)*(int**)((char*)s + 0x10);

    *sp = (int*)((char*)*sp - 4);
    i2  = **sp;
    *sp = (int*)((char*)*sp - 4);
    i1  = **sp;
    dx = (*(int*)((char*)*m1 + i1 * 4) - *(int*)((char*)*m2 + i2 * 4)) << 10;
    dy = (*(int*)((char*)m1[1] + i1 * 4) - *(int*)((char*)m2[1] + i2 * 4)) << 10;
    dist = util_EuclidianDistance(dx, dy);
    if (dist != 0) {
        dx = util_FixDiv(dx, dist);
        dy = util_FixDiv(dy, dist);
    }
    *(short*)((char*)s + 0x14) = (short)((dx + 1) >> 2);
    *(short*)((char*)s + 0x16) = (short)((dy + 1) >> 2);
    if (*(unsigned char*)((char*)s + 4) & 1) {
        short y0 = *(short*)((char*)s + 0x16);
        short x0 = *(short*)((char*)s + 0x14);
        *(short*)((char*)s + 0x16) = x0;
        *(short*)((char*)s + 0x14) = (short)-y0;
    }
    fnt_ComputeAndCheck_PF_Proj(s);
    *(int*)((char*)s + 0x44) = 0x8ac1a0;
    *(int*)((char*)s + 0x48) = 0x8ac300;
    *(int*)((char*)s + 0x4c) = 0x8ac300;
}

// @ 0x008aca20
void fnt_SDPVTL(void* s)
{
    int**  sp = (int**)((char*)s + 0x20);
    int    i2, i1, dx, dy, dist;
    int**  m1 = (int**)*(int**)((char*)s + 0x0c);
    int**  m2 = (int**)*(int**)((char*)s + 0x10);
    int    ax, ay;

    *sp = (int*)((char*)*sp - 4);
    i2  = **sp;
    *sp = (int*)((char*)*sp - 4);
    i1  = **sp;
    dx = (*(int*)((char*)*m1 + i1 * 4) - *(int*)((char*)*m2 + i2 * 4)) << 10;
    dy = (*(int*)((char*)m1[1] + i1 * 4) - *(int*)((char*)m2[1] + i2 * 4)) << 10;
    dist = util_EuclidianDistance(dx, dy);
    if (dist != 0) {
        dx = util_FixDiv(dx, dist);
        dy = util_FixDiv(dy, dist);
    }
    *(short*)((char*)s + 0x14) = (short)((dx + 1) >> 2);
    *(short*)((char*)s + 0x16) = (short)((dy + 1) >> 2);

    ax = (*(int*)((char*)m1[2] + i1 * 4) - *(int*)((char*)m2[2] + i2 * 4)) << 10;
    ay = (*(int*)((char*)m1[3] + i1 * 4) - *(int*)((char*)m2[3] + i2 * 4)) << 10;
    dist = util_EuclidianDistance(ax, ay);
    if (dist != 0) {
        ax = util_FixDiv(ax, dist);
        ay = util_FixDiv(ay, dist);
    }
    *(short*)((char*)s + 0x1c) = (short)((ax + 1) >> 2);
    *(short*)((char*)s + 0x1e) = (short)((ay + 1) >> 2);

    if (*(unsigned char*)((char*)s + 4) & 1) {
        short x0 = *(short*)((char*)s + 0x14);
        short y0 = *(short*)((char*)s + 0x16);
        short x1 = *(short*)((char*)s + 0x1c);
        short y1 = *(short*)((char*)s + 0x1e);
        *(short*)((char*)s + 0x14) = (short)-y0;
        *(short*)((char*)s + 0x16) = x0;
        *(short*)((char*)s + 0x1c) = (short)-y1;
        *(short*)((char*)s + 0x1e) = x1;
    }
    fnt_ComputeAndCheck_PF_Proj(s);
    *(int*)((char*)s + 0x44) = 0x8ac1a0;
    *(int*)((char*)s + 0x48) = 0x8ac300;
    *(int*)((char*)s + 0x4c) = 0x8ac330;
}

// @ 0x008acb50
void fnt_SFVTL(void* s)
{
    int**  sp = (int**)((char*)s + 0x20);
    int    i2, i1, dx, dy, dist;
    int**  m1 = (int**)*(int**)((char*)s + 0x0c);
    int**  m2 = (int**)*(int**)((char*)s + 0x10);

    *sp = (int*)((char*)*sp - 4);
    i2  = **sp;
    *sp = (int*)((char*)*sp - 4);
    i1  = **sp;
    dx = (*(int*)((char*)*m1 + i1 * 4) - *(int*)((char*)*m2 + i2 * 4)) << 10;
    dy = (*(int*)((char*)m1[1] + i1 * 4) - *(int*)((char*)m2[1] + i2 * 4)) << 10;
    dist = util_EuclidianDistance(dx, dy);
    if (dist != 0) {
        dx = util_FixDiv(dx, dist);
        dy = util_FixDiv(dy, dist);
    }
    *(short*)((char*)s + 0x18) = (short)((dx + 1) >> 2);
    *(short*)((char*)s + 0x1a) = (short)((dy + 1) >> 2);
    if (*(unsigned char*)((char*)s + 4) & 1) {
        short y0 = *(short*)((char*)s + 0x1a);
        short x0 = *(short*)((char*)s + 0x18);
        *(short*)((char*)s + 0x1a) = x0;
        *(short*)((char*)s + 0x18) = (short)-y0;
    }
    fnt_ComputeAndCheck_PF_Proj(s);
    *(int*)((char*)s + 0x44) = 0x8ac1a0;
}

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
