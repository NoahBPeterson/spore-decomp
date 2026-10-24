// Slice s00b85380 -- EA::Text::TileMap / Vertex3D vector / PaintSystem cluster.
//
// Modelled types:
//   Vertex3D  0x24-byte vertex (9 dwords; copied with fld/fstp or rep movsd)
//   Vertex2D  0x18-byte vertex / Vec20B  0x1c-byte element (Assign @0x473500)
//   Vec3f     0x0c-byte vector element (float3: swap/insert)
//   TileMap   the owning container (raw byte accessors at retail offsets)
//
// Retail member offsets are read from the disassembly; the dev PDB layout differs,
// so objects are modelled locally with role-named members at retail offsets.

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef int            i32s;

// eastl allocation header: the dword immediately before an allocated block
// says whether the allocator owns it (nonzero -> free with operator delete[]).
static inline bool BlockIsOurs(const void *p)
{
    return p != 0 && ((const u32 *)p)[-1] != 0;
}

// --------------------------------------------------------------- extern decls
extern "C" void *operator_new(u32 n, const char *pFile, int a, int b,
                              const char *pAlloc, int line);            // 0x00f473a0
#define OPERATOR_NEW(n) operator_new((n), "Simulator", 0, 0, (const char *)0x013ebb38, 0xd1)
extern "C" void  operator_delete_array(void *p);                        // 0x00f47380
extern "C" void *memcpy(void *d, const void *s, u32 n);                 // 0x011e0744
extern "C" void *memset(void *d, int c, u32 n);                         // 0x011e073e
extern "C" void *memmove(void *d, const void *s, u32 n);                // via [0x13cc480]
extern "C" void  FUN_00b83af0(void *out, const void *key);              // 0x00b83af0
extern "C" void  FUN_00b848f0(void *a, void *b, void *c);               // 0x00b848f0
extern "C" void  FUN_00b84e90(void *a, u32 b, void *c);                 // 0x00b84e90
extern "C" void *FUN_00b7f710(void *first, void *pos, void *dst);       // 0x00b7f710
extern "C" void  FUN_00b7f780(void *a, void *b, void *c, void *d, void *e); // 0x00b7f780
extern "C" void  FUN_00b7f800(void *a, void *b, void *c, void *d);      // 0x00b7f800
extern "C" void  FUN_00b7f6a0(void *a, void *b, void *c);               // 0x00b7f6a0
extern "C" void *FUN_00b7f8b0(void *a, void *b, void *c);               // 0x00b7f8b0
extern "C" void  FUN_00b7f3f0(void *a, void *b);                        // 0x00b7f3f0
extern "C" void  FUN_00b7f430(void *a, void *b);                        // 0x00b7f430
extern "C" void  FUN_00b85090(void *a, void *b, void *c);               // 0x00b85090
extern "C" void *FUN_00b83be0(u32 n, const void *first, const void *last); // 0x00b83be0
extern "C" void  FUN_00b7f510(u32 n);                                   // 0x00b7f510
extern "C" void  FUN_00b7f5c0(void *a, void *b, void *c, void *d, void *e); // 0x00b7f5c0
extern "C" void  FUN_00b7f800v();                                       // unused guard
extern "C" void  FUN_00b83a40(void *a, void *b, void *c, void *d, void *e, void *f, void *g); // 0x00b83a40
extern "C" u32   FUN_00921340(u32 n);                                   // 0x00921340
extern "C" u32   FUN_009213c0(u32 n);                                   // 0x009213c0
extern "C" void  FUN_00921260(void *a, u32 b, u32 c, u32 d, u32 e, u32 f); // 0x00921260
extern "C" void  FUN_720250_CopyVertex3D(const void *first, const void *last, void *dst); // 0x00720250

// Vec20B::operator= -- a 0x14-byte element assignment (thiscall(dst, src)).
// Modelled as a member so the compiler emits ecx = dst.
struct Vec20B {
    u32 m0; u32 m4; u32 m8; u32 mc; u32 m10;
    void Assign(const Vec20B &src);       // 0x00473500
};
#define Vec20BAssign(pDst, pSrc) ((pDst)->Assign(*(pSrc)))

// ------------------------------------------------- Vertex3D element (0x24)
struct Vertex3D {
    float x, y, z, w;   // +0x00..0x0c
    u32   m10;          // +0x10
    float m14, m18, m1c; // +0x14..0x1c
    u32   m20;          // +0x20
};

// ------------------------------------------------------------- function 1
// @ 0x00b85570
// In-place reversal of a {float3} array: swap [begin] and [end-0xc] moving in.
struct Vec3f { float x, y, z; };

void Vec3f_ReverseSwap(Vec3f *pBegin, Vec3f *pEnd)
{
    Vec3f *pLo = pBegin;
    Vec3f *pHi = pEnd - 1;
    while (pLo < pHi) {
        float a = pLo->x;
        float b = pLo->y;
        float c = pLo->z;
        pLo->x = pHi->x;
        pLo->y = pHi->y;
        pLo->z = pHi->z;
        pHi->x = a;
        pHi->y = b;
        pHi->z = c;
        ++pLo;
        --pHi;
    }
}

// @ 0x00b85930
// Allocates `n` bytes (operator_new) then copies [src, src+bytes) into it.
void * __stdcall AllocAndCopy(u32 n, const void *pSrc, const void *pSrcEnd)
{
    void *pDst;
    if (n != 0)
        pDst = OPERATOR_NEW(n);
    else
        pDst = 0;
    memcpy(pDst, pSrc, (u32)((const char *)pSrcEnd - (const char *)pSrc));
    return pDst;
}

// @ 0x00b86350
// Forward copy of 0x1c-byte elements: {u32,u32,Vec20B}.
u32 *CopyVec20BForward(u32 *pFirst, u32 *pLast, u32 *pDst)
{
    u32 *pResult = pDst;
    if (pFirst != pLast) {
        do {
            pDst[0] = pFirst[0];
            pDst[1] = pFirst[1];
            Vec20BAssign((Vec20B *)(pDst + 2), (const Vec20B *)(pFirst + 2));
            pFirst += 7;
            pDst += 7;
        } while (pFirst != pLast);
        pResult = pDst;
    }
    return pResult;
}

// @ 0x00b86390
// Backward copy of 0x1c-byte elements.
u32 *CopyVec20BBackward(u32 *pFirst, u32 *pLast, u32 *pDst)
{
    u32 *pResult = pDst;
    if (pLast != pFirst) {
        do {
            pLast -= 7;
            pDst -= 7;
            pDst[0] = pLast[0];
            pDst[1] = pLast[1];
            Vec20BAssign((Vec20B *)(pDst + 2), (const Vec20B *)(pLast + 2));
            pResult = pDst;
        } while (pLast != pFirst);
    }
    return pResult;
}

// ---------------------------------------------------------------- vector types
// A 12-byte vector of Vector3 (0xc-byte float3) elements, with a 1-dword guard
// at +0xc used by the realloc path.
struct SpVector3 {
    Vec3f *mpBegin;   // +0x00
    Vec3f *mpEnd;     // +0x04
    Vec3f *mpCap;     // +0x08
    void  *mpGuard;   // +0x0c
    Vec3f *insert(Vec3f *pos, const Vec3f *pVal);   // 0x00b85d40
    void   DoInsertValue(Vec3f *pos, const Vec3f *pVal); // 0x004b5ad0
    Vec3f *end() const { return mpEnd; }
};

// @ 0x00b85d40
Vec3f *SpVector3::insert(Vec3f *pos, const Vec3f *pVal)
{
    u32 idx = (u32)(pos - mpBegin);
    Vec3f *pOld = mpEnd;
    if (pos == pOld && pOld != mpCap) {
        mpEnd = pOld + 1;
        if (pOld != 0) {
            pOld->x = pVal->x;
            pOld->y = pVal->y;
            pOld->z = pVal->z;
        }
    } else {
        DoInsertValue(pos, pVal);
    }
    return mpBegin + idx;
}

// ------------------------------------------------------ Vertex3D vector (0x24)
struct Vertex3DVec {
    Vertex3D *mpBegin;   // +0x00
    Vertex3D *mpEnd;     // +0x04
    Vertex3D *mpCap;     // +0x08
    void  *mpGuard;      // +0x0c
    void push_back(const Vertex3D *pVal);   // 0x00b85db0
    void GrowAndInsert(Vertex3D *pos, const Vertex3D *pVal); // 0x00b85380
    Vertex3D *CopyUninit(Vertex3D *pSrc, Vertex3D *pDst);    // 0x00b85500
    void InsertFillN(Vertex3D *pos, u32 n, const Vertex3D *pVal); // 0x00b85710
};

// @ 0x00b85500
// Copies [pSrc, mpEnd) into pDst (0x24-byte elements), advances mpEnd by the
// copied span (pSrc - pDst), and returns pDst.
Vertex3D *Vertex3DVec::CopyUninit(Vertex3D *pDst, Vertex3D *pSrc)
{
    Vertex3D *pEnd = mpEnd;
    Vertex3D *s = pSrc;
    Vertex3D *d = pDst;
    while (s != pEnd) {
        *d = *s;
        s += 1;
        d += 1;
    }
    mpEnd = mpEnd + (pDst - pSrc);
    return pDst;
}

// @ 0x00b85db0
void Vertex3DVec::push_back(const Vertex3D *pVal)
{
    Vertex3D *p = mpEnd;
    if (p < mpCap) {
        mpEnd = p + 1;
        if (p != 0) {
            p->x = pVal->x;
            p->y = pVal->y;
            p->z = pVal->z;
            p->w = pVal->w;
            p->m10 = pVal->m10;
            p->m14 = pVal->m14;
            p->m18 = pVal->m18;
            p->m1c = pVal->m1c;
            p->m20 = pVal->m20;
        }
        return;
    }
    GrowAndInsert(p, pVal);
}

// @ 0x00b85380
// Inserts one Vertex3D at `pos`; grows the buffer if full.
void Vertex3DVec::GrowAndInsert(Vertex3D *pos, const Vertex3D *pVal)
{
    Vertex3D *pEnd = mpEnd;
    if (pEnd != mpCap) {
        if (pVal >= pos && pVal < pEnd)
            pVal += 1;
        if (pEnd != 0) {
            pEnd->x = (pEnd - 1)->x;
            pEnd->y = (pEnd - 1)->y;
            pEnd->z = (pEnd - 1)->z;
            pEnd->w = (pEnd - 1)->w;
            pEnd->m10 = (pEnd - 1)->m10;
            pEnd->m14 = (pEnd - 1)->m14;
            pEnd->m18 = (pEnd - 1)->m18;
            pEnd->m1c = (pEnd - 1)->m1c;
            pEnd->m20 = (pEnd - 1)->m20;
        }
        for (Vertex3D *p = mpEnd - 1; p != pos; ) {
            p -= 1;
            p[1] = p[0];
        }
        *pos = *pVal;
        mpEnd += 1;
        return;
    }

    // grow: new capacity = max(2*size, 1)
    u32 size = (u32)(pEnd - mpBegin);
    u32 newCap = size * 2;
    if (newCap == 0)
        newCap = 1;
    void *pNew = 0;
    if (newCap != 0)
        pNew = OPERATOR_NEW(newCap * 0x24);

    Vertex3D *pMid = (Vertex3D *)FUN_00b7f710(mpBegin, pos, pNew);
    if (pMid != 0)
        *pMid = *pVal;
    Vertex3D *pNewEnd = (Vertex3D *)FUN_00b7f710(pos, mpEnd, pMid + 1);
    if (BlockIsOurs(mpBegin))
        operator_delete_array(mpBegin);
    mpEnd = pNewEnd;
    mpBegin = (Vertex3D *)pNew;
    mpCap = (Vertex3D *)pNew + newCap;
}

// assign(begin,end) for a 0x18-byte vertex vector.
struct Vertex2D { float x, y, z, w; u32 m10; u32 m14; };  // 0x18

struct Vertex2DVec {
    Vertex2D *mpBegin;   // +0x00
    Vertex2D *mpEnd;     // +0x04
    Vertex2D *mpCap;     // +0x08
    Vertex2D *Assign(const Vertex2DVec *pSrc);          // 0x00b855e0
    Vertex2D *ReallocAssign(u32 n, const Vertex2D *pSrc, const Vertex2D *pSrcEnd); // 0x00b83be0
};

// @ 0x00b855e0
Vertex2D *Vertex2DVec::Assign(const Vertex2DVec *pSrc)
{
    if (pSrc == this)
        return (Vertex2D *)this;
    Vertex2D *pFirst = pSrc->mpBegin;
    Vertex2D *pLast = pSrc->mpEnd;
    u32 n = (u32)(pLast - pFirst);
    u32 cap = (u32)(mpCap - mpBegin);
    if (n > cap) {
        Vertex2D *pNew = ReallocAssign(n, pFirst, pLast);
        if (BlockIsOurs(mpBegin))
            operator_delete_array(mpBegin);
        mpCap = pNew + n;
        mpBegin = pNew;
        mpEnd = pNew + n;
        return (Vertex2D *)this;
    }
    u32 size = (u32)(mpEnd - mpBegin);
    if (size < n) {
        FUN_720250_CopyVertex3D(pFirst, pFirst + size, mpBegin);
        FUN_00b7f5c0(&pLast, mpBegin + size, pLast, mpEnd, pLast);
        mpEnd = mpBegin + n;
        return (Vertex2D *)this;
    }
    FUN_720250_CopyVertex3D(pFirst, pLast, mpBegin);
    mpEnd = mpBegin + n;
    return (Vertex2D *)this;
}

// TileMap lookup: the container holds a vector of 4-byte keys at +0x34/+0x38 and
// a parallel array of 0x14-byte elements at +0x0c.
struct TileMapLookup {
    u8   mPad00[0x0c];
    Vec20B *mpData;   // +0x0c
    u8   mPad10[0x24];
    u32 *mpKeys;      // +0x34
    u32 *mpKeysEnd;   // +0x38
    char LookupAssign(u32 key, Vec20B *pOut);   // 0x00b859c0
};

// @ 0x00b859c0
char TileMapLookup::LookupAssign(u32 key, Vec20B *pOut)
{
    int n = (int)(mpKeysEnd - mpKeys);
    for (int i = 0; i < n; ++i) {
        if (mpKeys[i] == key) {
            Vec20BAssign(pOut, &mpData[i]);
            return 1;
        }
    }
    return 0;
}

// ------------------------------------------------ TileMap (PaintSystem) type
// A PaintSystem/TileMap object. Only the members touched by this slice are
// named; the rest are pad bytes at their retail offsets.

// The fixed-block pool embedded at PaintSystem::mPool (+0xf4).
struct FixedPool {
    u32   mPad00;         // +0x00
    void *mpBegin;        // +0x04  (+0xf8 in the object)
    u32   mCount;         // +0x08  (+0xfc)
    u32   mSize;          // +0x0c  (+0x100)
    u8    mPad10[0x0c];   // +0x10..0x1b
    void *mpFree;         // +0x1c  (+0x110) free-list head
    u8    mPad20[0x04];   // +0x20..0x23
    void *mpLow;          // +0x24  (+0x118) allocator range start
    void *mpHigh;         // +0x28  (+0x11c) allocator range end
    u8    mPad2c[0x04];   // +0x2c..0x2f
    void *mpSentinel;     // +0x30  (+0x124)
};

struct PaintSystem {
    void *mpVtbl;         // +0x00 (cListenerBase vtable)
    void *mpSubVtbl;      // +0x04 (cGonzagoSubsystem vtable)
    void *mpSubVtbl08;    // +0x08
    u32  *mpVec0c;        // +0x0c
    u8    mPad10[0x10];   // +0x10..0x1f
    void *mpField20;      // +0x20
    u8    mPad24[0x14];   // +0x24..0x37
    u32  *mpBits38;       // +0x38 bitvector begin
    u8    mPad3c[0x04];   // +0x3c
    u32  *mpBits40;       // +0x40 bitvector end
    u8    mPad44[0x0c];   // +0x44..0x4f
    u32  *mpVec50;        // +0x50
    u8    mPad54[0x10];   // +0x54..0x63
    u32  *mpVec64;        // +0x64
    u8    mPad68[0x18];   // +0x68..0x7f
    u32  *mpVec80;        // +0x80
    u8    mPad84[0x10];   // +0x84..0x93
    u32  *mpVec94;        // +0x94
    u8    mPad98[0x14];   // +0x98..0xab
    u32  *mpVecAc;        // +0xac
    u8    mPadB0[0x10];   // +0xb0..0xbf
    u32  *mpVecC0;        // +0xc0
    u8    mPadC4[0x10];   // +0xc4..0xd3
    u32  *mpVecD4;        // +0xd4
    u32  *mpVecD8;        // +0xd8
    u8    mPadDc[0x18];   // +0xdc..0xf3
    FixedPool mPool;      // +0xf4

    void Dtor();                             // 0x00b85a30
};

extern "C" void SP__cGonzagoSubsystem__dtor(void *p);      // 0x00b5b9a0
extern "C" void SP__cGonzagoSubsystem__ctor(void *p);      // 0x00b5b960
extern "C" void FUN_00b7f430(void *a, void *b);            // 0x00b7f430
extern "C" void FUN_00b7f3f0(void *a, void *b);            // 0x00b7f3f0

// eastl fixed-pool / free-list helpers are thiscall: ecx = the container.
typedef void (__thiscall *PoolFreeNodesFn)(void *self, void *begin, void *count);
typedef void (__thiscall *PoolFreeVecFn)(void *self, void *begin, void *end);
// cGonzagoSubsystem ctor/dtor are thiscall: ecx = the embedded subsystem.
typedef void (__thiscall *SubsystemDtorFn)(void *self);
typedef void (__thiscall *SubsystemCtorFn)(void *self);

// @ 0x00b85a30
void PaintSystem::Dtor()
{
    mpVtbl      = (void *)0x014654e0;
    mpSubVtbl   = (void *)0x01465490;
    mpSubVtbl08 = (void *)0x01465488;

    ((PoolFreeNodesFn)0x00b7f430)(&mPool, mPool.mpBegin, (void *)mPool.mCount);
    mPool.mSize = 0;
    u32   count = mPool.mCount;
    void *first = mPool.mpBegin;
    if (count > 1 && first != mPool.mpSentinel) {
        if (first < mPool.mpLow || mPool.mpHigh <= first)
            operator_delete_array(first);
        else {
            *(u32 *)first = (u32)mPool.mpFree;
            mPool.mpFree = first;
        }
    }

    ((PoolFreeVecFn)0x00b7f3f0)(&mpVecD4, mpVecD4, mpVecD8);
    if (BlockIsOurs(mpVecD4))
        operator_delete_array(mpVecD4);
    if (BlockIsOurs(mpVecC0))
        operator_delete_array(mpVecC0);
    if (BlockIsOurs(mpVecAc))
        operator_delete_array(mpVecAc);
    if (BlockIsOurs(mpVec94))
        operator_delete_array(mpVec94);
    if (BlockIsOurs(mpVec80))
        operator_delete_array(mpVec80);
    if (BlockIsOurs(mpVec64))
        operator_delete_array(mpVec64);
    if (BlockIsOurs(mpVec50))
        operator_delete_array(mpVec50);

    u32 n = ((u32)mpBits40 - (u32)mpBits38) & 0xfffffffe;
    if ((int)n > 2 && mpBits38 != 0)
        operator_delete_array(mpBits38);

    if (mpField20 != 0)
        ((void (__thiscall *)(void *))((void **)*(void **)mpField20)[1])(mpField20);

    ((SubsystemDtorFn)0x00b5b9a0)(&mpSubVtbl);
    mpVtbl = (void *)0x013eb394;
}

// Stack-local eastl fixed_pool_base built by InitPool.
struct FixedPoolBase {
    u32  m0;            // +0x00
    u32  m4;            // +0x04
    void *mpBegin;      // +0x08
    void *mpEnd;        // +0x0c
    u32  mElemSize;     // +0x10
    void *mpOwner;      // +0x14
};

// eastl helpers used by InitPool are all thiscall (ecx = the container).
typedef void (__thiscall *FixedPoolInitFn)(void *self, void *pBegin, u32 nBytes, u32 nElem, u32 nAlign, u32 nFlags);
typedef void (__thiscall *PoolInitNodesFn)(void *self, u32 nCount,
                                           void *a, void *pB1, void *pB2, void *b, void *pB3, void *pPool);
typedef u32  (__thiscall *PoolSizeFn)(void *self, u32 nCount);
typedef void (__thiscall *PoolGrowFn)(void *self, u32 nCount);

// Flat fixed-pool object embedded at PaintSystem+0xf4.
// Laid out by PaintSystemPool::InitPool (retail offsets +0x08..+0x12838).
struct PaintSystemPool {
    u8   mPad00[0x08];      // +0x00..0x07
    u32  mSize;             // +0x08
    u32  mCount;            // +0x0c
    u32  mBoundHigh;        // +0x10 (10000.0f)
    u32  mBoundLow;         // +0x14 (2.0f)
    u32  mField18;          // +0x18
    u8   mPad1c[0x18];      // +0x1c..0x33
    u8   mField34[0x04];    // +0x34
    u8   mPad38[0x800];     // +0x38..0x837
    u8   mNodes[0x12000];   // +0x838 fixed-block pool
    u8   mTail[0x04];       // +0x12838

    void *InitPool(void *a, void *b);   // 0x00b85bc0 (thiscall)
};

// @ 0x00b85bc0
// Initialises the PaintSystem's fixed pool and node bookkeeping.
void *PaintSystemPool::InitPool(void *a, void *b)
{
    FixedPoolBase fixedPool;
    fixedPool.m0 = 0;
    ((FixedPoolInitFn)0x00921260)(&fixedPool, mNodes, 0x12000, 0x24, 4, 0);

    fixedPool.mpBegin   = mNodes;
    fixedPool.mpEnd     = mNodes + 0x12000;
    fixedPool.mElemSize = 0x24;
    fixedPool.mpOwner   = (u8 *)this + 0x34;

    u32 nNodes = FUN_00921340(0x200);
    ((PoolInitNodesFn)0x00b83a40)(this, nNodes, a, &b, &b, b, &b, &fixedPool);

    mBoundHigh = *(const u32 *)0x013f0620;   // 10000.0f
    mBoundLow  = *(const u32 *)0x01470f1c;   // 2.0f
    mField18   = 0;
    fixedPool.mpBegin = 0;                   // +0x08 cleared before the size query
    u32 need = ((PoolSizeFn)0x009213c0)(&fixedPool, mCount);
    if (need > mSize)
        ((PoolGrowFn)0x00b7f510)(this, need);
    return this;
}

// TileMap header (only +0x04/+0x08 are touched by IndexLookup).
struct TileMapIndex {
    u8      mPad00[0x04];   // +0x00
    void  **mpTable;        // +0x04 indexed record table
    u32     mIndex;         // +0x08

    void *IndexLookup(void *pKey);   // 0x00b85ca0 (thiscall)
};

// The 0x18-byte lookup key built for the insert helper.
struct TileMapKey {
    u32 m0;                 // +0x00
    u32 m4;                 // +0x04
    u32 m8;                 // +0x08
    u32 mC;                 // +0x0c
    u32 m10;                // +0x10
    u32 m14;                // +0x14
};

// TileMap hash-map helpers are thiscall (ecx = the TileMap).
typedef void (__thiscall *MapFindFn)(void *self, void *pOut, const void *pKey);
typedef void (__thiscall *MapInsertFn)(void *self, void *pRec, const void *pKey, void *pArg);

// One 0x34-byte scratch buffer: the find helper fills it, then the insert key
// is built overlapping its tail (exactly as the retail compiler laid it out).
struct LookupBuffer {
    u32        mRec[5];     // +0x00..0x13 located/inserted record
    TileMapKey key;         // +0x14..0x2b (overlaps the buffer tail)
    u32        mTail0;      // +0x2c
    u32        mTail1;      // +0x30
};

// @ 0x00b85ca0
// TileMap::operator[](key): finds or creates the 0x14-byte record at +0xc.
void *TileMapIndex::IndexLookup(void *pKey)
{
    LookupBuffer buf;
    ((MapFindFn)0x00b83af0)(this, &buf, pKey);
    if (buf.mRec[0] == (u32)mpTable[mIndex]) {
        const u32 *pIn = (const u32 *)pKey;
        buf.key.m0  = pIn[0];
        buf.key.m4  = pIn[1];
        buf.key.m8  = pIn[2];
        buf.mTail0  = buf.mRec[3];
        buf.mTail1  = buf.mRec[4];
        buf.key.mC  = buf.mRec[0];
        buf.key.m10 = buf.mRec[1];
        buf.key.m14 = buf.mRec[2];
        ((MapInsertFn)0x00b848f0)(this, &buf, &buf.key, (void *)((u32)pKey & 0xffffff00));
    }
    return (u8 *)buf.mRec[0] + 0xc;
}

// @ 0x00b85e10
// Fills the (already-allocated) vector with `n` default-constructed 0x14-byte
// elements, then sets begin/end/cap.
struct Vec20BElem { u32 m[5]; void Construct(void *pDefault); };  // 0x00b84ba0
struct SpVector20B {
    u32 *mpBegin;   // +0x00
    u32 *mpEnd;     // +0x04
    u32 *mpCap;     // +0x08
    void *AssignN(u32 n, u32 unused);       // 0x00b85e10
};

void *SpVector20B::AssignN(u32 n, u32 unused)
{
    u8 *pBuf;
    if (n != 0)
        pBuf = (u8 *)OPERATOR_NEW(n * 0x14);
    else
        pBuf = 0;
    u32 bytes = n * 0x14;
    Vec20BElem defaultValue;
    defaultValue.m[0] = 0;
    defaultValue.m[1] = 0;
    defaultValue.m[2] = 0;
    mpBegin = (u32 *)pBuf;
    mpEnd = (u32 *)pBuf;
    mpCap = (u32 *)(pBuf + bytes);
    u8 *pIt = pBuf;
    while (n > 0) {
        if (pIt != 0)
            ((Vec20BElem *)pIt)->Construct(&defaultValue);
        --n;
        pIt += 0x14;
    }
    mpEnd = (u32 *)((u8 *)mpBegin + bytes);
    return this;
}

extern "C" void FUN_00b84ba0(void *p);   // 0x00b84ba0

// @ 0x00b85f30
// resize(n) for a 0x18-byte vertex vector: fills new slots with the default value.
void Vertex2DVec_Resize(void *pThis, u32 n)
{
    Vertex2DVec *p = (Vertex2DVec *)pThis;
    u32 size = (u32)(p->mpEnd - p->mpBegin);
    if (size < n) {
        FUN_00b84e90(p->mpEnd, n - size, 0);
        return;
    }
    FUN_720250_CopyVertex3D(p->mpEnd, p->mpEnd, p->mpBegin + n);
    p->mpEnd = p->mpEnd + (p->mpEnd - (p->mpBegin + n));
}

extern "C" void FUN_00b84e90(void *a, u32 b, void *c);   // 0x00b84e90

// @ 0x00b85fb0
// Copy-constructs a byte vector from another byte vector.
struct ByteVec {
    u8 *mpBegin;   // +0x00
    u8 *mpEnd;     // +0x04
    u8 *mpCap;     // +0x08
    void *CopyCtor(const ByteVec *pSrc);   // 0x00b85fb0
    void *AssignFrom(const ByteVec *pSrc); // 0x00b86010
    void *InsertFill(u8 *pos, u32 n, const u8 *pVal);  // 0x00b860d0
};

void *ByteVec::CopyCtor(const ByteVec *pSrc)
{
    u32 bytes = (u32)(pSrc->mpEnd - pSrc->mpBegin);
    u8 *pBuf;
    if (bytes != 0)
        pBuf = (u8 *)OPERATOR_NEW(bytes);
    else
        pBuf = 0;
    mpBegin = pBuf;
    mpEnd = pBuf;
    mpCap = pBuf + bytes;
    u32 n = (u32)(pSrc->mpEnd - pSrc->mpBegin);
    u8 *pDst = (u8 *)memcpy(pBuf, pSrc->mpBegin, n);
    mpEnd = pDst + n;
    return this;
}

// @ 0x00b86010
// Byte-vector operator= (assign from another byte vector).
void *ByteVec::AssignFrom(const ByteVec *pSrc)
{
    if (pSrc == this)
        return this;
    u32 n = (u32)(pSrc->mpEnd - pSrc->mpBegin);
    u32 cap = (u32)(mpCap - mpBegin);
    if (n > cap) {
        u8 *pNew = (u8 *)AllocAndCopy(n, pSrc->mpBegin, pSrc->mpEnd);
        if (BlockIsOurs(mpBegin))
            operator_delete_array(mpBegin);
        mpBegin = pNew;
        mpCap = pNew + n;
        mpEnd = mpBegin + n;
        return this;
    }
    u32 size = (u32)(mpEnd - mpBegin);
    if (n > size) {
        memcpy(mpBegin, pSrc->mpBegin, size);
        u8 *pSrc2 = pSrc->mpBegin + (mpEnd - mpBegin);
        memcpy(mpEnd, pSrc2, (u32)(pSrc->mpEnd - pSrc2));
        mpEnd = mpBegin + n;
        return this;
    }
    memcpy(mpBegin, pSrc->mpBegin, n);
    mpEnd = mpBegin + n;
    return this;
}

// @ 0x00b860d0
// eastl::vector<byte>::insert(pos, n, value): grows if needed, shifts the tail
// right by n, then fills the n slots at `pos` with `value`.
void *ByteVec::InsertFill(u8 *pos, u32 n, const u8 *pVal)
{
    u32 cap = (u32)(mpCap - mpEnd);
    if (n > cap) {
        u32 size = (u32)(mpEnd - mpBegin);
        u32 newCap = size * 2;
        if (size == 0)
            newCap = 1;
        u32 need = size + n;
        if (need > newCap)
            newCap = need;
        u8 *pNew;
        if (newCap == 0)
            pNew = 0;
        else
            pNew = (u8 *)OPERATOR_NEW(newCap);
        u32 headBytes = (u32)(pos - mpBegin);
        u8 *pMid = (u8 *)memcpy(pNew, mpBegin, headBytes) + headBytes;
        u8 value = *pVal;
        if (n != 0)
            memset(pMid, value, n);
        u32 tailBytes = (u32)(mpEnd - pos);
        u8 *pNewEnd = (u8 *)memcpy(pMid + n, pos, tailBytes) + tailBytes;
        if (BlockIsOurs(mpBegin))
            operator_delete_array(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCap = pNew + newCap;
        return this;
    }
    if (n != 0) {
        u8 value = *pVal;
        u8 *pOldEnd = mpEnd;
        u32 tailBytes = (u32)(mpEnd - pos);
        if (tailBytes <= n) {
            u32 fillNew = n - tailBytes;
            if (fillNew != 0)
                memset(mpEnd, value, fillNew);
            mpEnd += fillNew;
            memcpy(mpEnd, pos, (u32)(pOldEnd - pos));
            mpEnd += (u32)(pOldEnd - pos);
            memset(pos, value, (u32)(pOldEnd - pos));
            return this;
        }
        u8 *pSrc = mpEnd - n;
        memcpy(mpEnd, pSrc, (u32)(mpEnd - pSrc));
        mpEnd += n;
        memmove(pSrc + (u32)(pos - mpBegin) - (u32)(pSrc - mpBegin), pos, (u32)(pSrc - pos));
        memset(pos, value, n);
    }
    return this;
}

// @ 0x00b85710
// eastl::vector<Vertex3D>::insert(pos, n, value): grows if needed, shifts the
// tail right by n, then fills the n slots at `pos` with `*pVal`.
void Vertex3DVec::InsertFillN(Vertex3D *pos, u32 n, const Vertex3D *pVal)
{
    u32 capCount = (u32)(mpCap - mpEnd);
    if (n > capCount) {
        u32 size = (u32)(mpEnd - mpBegin);
        u32 newCap = size * 2;
        if (size == 0)
            newCap = 1;
        u32 need = size + n;
        if (need > newCap)
            newCap = need;
        Vertex3D *pNew;
        if (newCap == 0)
            pNew = 0;
        else
            pNew = (Vertex3D *)OPERATOR_NEW(newCap * 0x24);
        Vertex3D *pMid = (Vertex3D *)FUN_00b7f8b0(mpBegin, pos, pNew);
        FUN_00b7f800(pMid, (void *)n, (void *)pVal, pos);
        Vertex3D *pNewEnd = (Vertex3D *)FUN_00b7f8b0(pos, mpEnd, pMid + n);
        if (BlockIsOurs(mpBegin))
            operator_delete_array(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCap = pNew + newCap;
        return;
    }
    if (n != 0) {
        Vertex3D value = *pVal;
        Vertex3D *pOldEnd = mpEnd;
        u32 tailCount = (u32)(pOldEnd - pos);
        if (n < tailCount) {
            Vertex3D *pSplit = pOldEnd - n;
            FUN_00b7f780((void *)&pVal, pSplit, pOldEnd, pOldEnd, pOldEnd);
            mpEnd = mpEnd + n;
            FUN_00b85090(pos, pSplit, pOldEnd);
            FUN_00b7f6a0(pos, pos + n, &value);
            return;
        }
        u32 fillNew = n - tailCount;
        FUN_00b7f800(pOldEnd, (void *)fillNew, &value, pos);
        mpEnd = mpEnd + fillNew;
        FUN_00b7f780((void *)&pos, pos, pOldEnd, mpEnd, pos);
        mpEnd = mpEnd + tailCount;
        FUN_00b7f6a0(pos, pOldEnd, &value);
    }
}

// ---------------------------------------------------------------- listener ctor
// @ 0x00b863e0
// Constructs a cGonzago listener / PaintSystem object.

struct cGonzagoListener {
    u32 m00;                    // +0x00 vtable (cListenerBase)
    u32 mSubVtbl;               // +0x04 cGonzagoSubsystem vtable
    u32 mSubVtbl08;             // +0x08
    u8  mSysRest[0x14];         // +0x0c..0x1f
    u32 m20, m24;               // +0x20,+0x24
    float m28;                  // +0x28
    u32 m2c, m30, m34;          // +0x2c..0x34
    u32 m38, m3c;               // +0x38,+0x3c (wstring begin/end)
    u32 m40;                    // +0x40 (wstring cap)
    u8  m48;                    // +0x48
    u32 m4c, m50, m54, m58;     // +0x4c..0x58
    u32 m64, m68, m6c;          // +0x64..0x6c
    u8  m78;                    // +0x78
    u32 m7c, m80, m84, m88;     // +0x7c..0x88
    u32 m94, m98, m9c;          // +0x94..0x9c
    u32 mac, mb0, mb4;          // +0xac..0xb4
    u32 mc0, mc4, mc8;          // +0xc0..0xc8
    u32 md4, md8, mdc;          // +0xd4..0xdc
    u32 mec;                    // +0xec
    u8  mf0;                    // +0xf0
    u8  mpPool[4];              // +0xf4 fixed pool (thiscall member target)

    cGonzagoListener *Ctor();   // 0x00b863e0 (returns this)
};

cGonzagoListener *cGonzagoListener::Ctor()
{
    m00 = 0x013eb384u;
    ((SubsystemCtorFn)0x00b5b960)(&mSubVtbl);
    m00 = 0x014654e0u;
    mSubVtbl   = 0x01465490u;
    mSubVtbl08 = 0x01465488u;

    m20 = 0;
    m24 = 0;
    m28 = *(float *)0x013eb1bc;
    m2c = 0;
    m30 = 0;
    m34 = 0;
    m40 = 0x01667baeu;
    m38 = 0x01667bacu;
    m3c = 0x01667bacu;
    m48 = 0;
    m4c = 0;
    m50 = 0;
    m54 = 0;
    m58 = 0;
    m64 = 0;
    m68 = 0;
    m6c = 0;
    m78 = 0;
    m7c = 0;
    m80 = 0;
    m84 = 0;
    m88 = 0;
    m94 = 0;
    m98 = 0;
    m9c = 0;
    mac = 0;
    mb0 = 0;
    mb4 = 0;
    mc0 = 0;
    mc4 = 0;
    mc8 = 0;
    md4 = 0;
    md8 = 0;
    mdc = 0;
    mf0 = 0;
    mec = 0xffffffffu;
    u32 tmp = 0;
    ((PaintSystemPool *)mpPool)->InitPool(&tmp, &tmp);
    return this;
}
