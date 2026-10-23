// Slice s00b09570 -- SPGonzago / SP::cFruitManager cluster.
// Retail member offsets are read from the disassembly; the dev PDB layout differs,
// so objects are modelled locally with role-named members at retail offsets.
//
// Modelled classes:
//   Fv16      header 0x18 + 16 x u32   (0x58)   small fixed vector
//   Fv512     header 0x18 + 512 x u32  (0x818)  large fixed vector
//   Scatter   4 floats + 12 dwords + 1 dword + 3 Fv16 + 2 floats + 3 Fv512  (0x19a0)
//   ScatterE  8-byte prefix + Scatter   (0x19a8)
//   Mgr       manager singleton (only touched offsets are named)
//   TreeData  0x80-byte tree element
//   Pairs     pointer vector used by 00b0a0c0

typedef unsigned int u32;
typedef unsigned __int64 u64;

// ---------------------------------------------------------- indirect this-call
typedef void  (__thiscall *F0v)(void *);
typedef void *(__thiscall *F0p)(void *);
typedef void  (__thiscall *F1i)(void *, int);
typedef void  (__thiscall *F1p)(void *, void *);
typedef void  (__thiscall *F1u)(void *, u32);

static inline void *VS(void *o, int off) { return *(void **)((char *)(*(void **)o) + off); }
static inline void *vc_p(void *o, int off) { return ((F0p)VS(o, off))(o); }
static inline void  vc_v(void *o, int off) { ((F0v)VS(o, off))(o); }
static inline void  vc_vu(void *o, int off, u32 a) { ((F1u)VS(o, off))(o, a); }

// ---------------------------------------------------------------- fixed vectors
// mpBegin/mpEnd/mpCap point into mBuf; mCount carries the logical size.

struct Fv16 {
    u32 *mpBegin;   // +0x00
    u32 *mpEnd;     // +0x04
    u32 *mpCap;     // +0x08
    u32  mPad0c;    // +0x0c
    u32  mPad10;    // +0x10
    u32  mCount;    // +0x14
    u32  mBuf[16];  // +0x18
    Fv16() { mpBegin = mBuf; mpEnd = mBuf; mpCap = mBuf + 16; mCount = 0; }
    Fv16(const Fv16 &src);             // 0x01011cc0 (out-of-line)
    Fv16 &operator=(const Fv16 &src);  // 0x01011cc0 (out-of-line)
};

struct Fv512 {
    u32 *mpBegin;   // +0x00
    u32 *mpEnd;     // +0x04
    u32 *mpCap;     // +0x08
    u32  mPad0c;    // +0x0c
    u32  mPad10;    // +0x10
    u32  mCount;    // +0x14
    u32  mBuf[512]; // +0x18
    Fv512() { mpBegin = mBuf; mpEnd = mBuf; mpCap = mBuf + 512; mCount = 0; }
    Fv512(const Fv512 &src);             // 0x00b07050 (out-of-line)
    Fv512 &operator=(const Fv512 &src);  // 0x00b07050 (out-of-line)
};

// ------------------------------------------------------------- scatter object

struct Scatter {
    float mX;         // +0x0000
    float mY;         // +0x0004
    float mZ;         // +0x0008
    float mSpread;    // +0x000c
    u32   mPad10;     // +0x0010
    u32   mPad14;     // +0x0014
    u32   mPad18;     // +0x0018
    u32   mPad1c;     // +0x001c
    u32   mPad20;     // +0x0020
    u32   mPad24;     // +0x0024
    u32   mPad28;     // +0x0028
    u32   mPad2c;     // +0x002c
    u32   mPad30;     // +0x0030
    u32   mPad34;     // +0x0034
    u32   mPad38;     // +0x0038
    u32   mPad3c;     // +0x003c
    u32   mFlag40;    // +0x0040
    Fv16  mSmall0;    // +0x0044
    Fv16  mSmall1;    // +0x009c
    Fv16  mSmall2;    // +0x00f4
    float mTimerA;    // +0x014c
    float mTimerB;    // +0x0150
    u32   mPad154;    // +0x0154
    Fv512 mBig0;      // +0x0158
    Fv512 mBig1;      // +0x0970
    Fv512 mBig2;      // +0x1188
    Scatter(const Scatter &src);            // ctor
    Scatter &AssignFrom(const Scatter &src); // assign
    char F09740(u32 param_2);               // 0x00b09740
};

struct ScatterE {
    u32     mKey;    // +0x0000
    u32     mPad04;  // +0x0004
    Scatter mBody;   // +0x0008
};

// ------------------------------------------------------------- tree element

struct TreeData {
    u32   mPad00;     // +0x00  (vtable in the original; never dereferenced here)
    u32   mPad04[3];  // +0x04
    float mPosX;      // +0x10
    float mPosY;      // +0x14
    float mPosZ;      // +0x18
    u32   mPad1c[11]; // +0x1c
    u32   mFruitLo;   // +0x48
    u32   mFruitHi;   // +0x4c
    u32   mSeedX;     // +0x50
    u32   mSeedY;     // +0x54
    u32   mSeedZ;     // +0x58
    u32   mPad5c[4];  // +0x5c
    float mCanopyR;   // +0x6c
    u32   mPad70[3];  // +0x70
    char  mSkip;      // +0x7c
    u32   mScore;     // +0x1c8
    TreeData();                      // ctor
    void  ReadFromIArchive(void *p); // vtable slot 5
};

// --------------------------------------------------------------- the manager

// Overlay used to read the two occupancy-mask words of a tree object at
// +0x48/+0x4c (which live inside the first Fv16 block of a Scatter).
struct TreeBits {
    u32 mPad00[0x12]; // +0x00
    u32 mMaskLo;      // +0x48
    u32 mMaskHi;      // +0x4c
    u32 mSeedX;       // +0x50
    u32 mSeedY;       // +0x54
    u32 mSeedZ;       // +0x58
};

struct Mgr {
    u32   mPad00[13];     // +0x0000
    float mSpawnX;        // +0x0034
    float mSpawnY;        // +0x0038
    float mSpawnZ;        // +0x003c
    u32   mPad40;         // +0x0040
    u32   mPad44[2];      // +0x0044
    u32   mSelA;          // +0x004c
    u32   mSelB;          // +0x0050
    u32   mSelC;          // +0x0054
    float mSoundX;        // +0x005c
    float mSoundY;        // +0x0060
    float mSoundZ;        // +0x0064
    u32   mPad68[15];     // +0x0068
    u32  *mpSpots;        // +0x00a4  array of 0x38-byte spots
    u32   mPadA8[61];     // +0x00a8
    u32  *mpIndexA;       // +0x019c
    u32   mPadA0[10];     // +0x01a0
    u32  *mpIndexB;       // +0x01c8
    u32   mPad1cc[22733]; // +0x01cc .. +0x164ff
    u32  *mpGrid;         // +0x16500  sphere-query grid
    u32   mPad16504[38];  // +0x16504 .. +0x1659b
    u32   mCount1659c;    // +0x1659c
    u32   mPad165a0[428573]; // +0x165a0 .. +0x1b8e13
    u32  *mpTreesBegin;   // +0x1b8e14
    u32  *mpTreesEnd;     // +0x1b8e18
    u32   mPad1b8e1c[1243]; // +0x1b8e1c .. +0x1ba187
    u32   mFlagsA;        // +0x1ba188
    u32   mFlagsB;        // +0x1ba18c
    Scatter *Place(u32 index, int *pOut);                          // 0x00b09830
    void  RemoveAllNouns();                                        // 0x00b09b00
    Scatter *PlaceIndexed(Scatter *pTree, u32 index, u32 param_3);  // 0x00b09b80
    void  UpdateFruit(int period);                                 // 0x00b09bf0
    char  SerializeMgr(u32 param_2);                               // 0x00b0a040
    void  QueryTrees(float *pPos, void **ppVec, u32 mask, float radius,
                     int sort, float *pSortPos, int needFruit);    // 0x00b0a0c0
};

// pointer-vector used by the sphere query
struct Pairs {
    int *mpBegin; // +0x00
    int *mpEnd;   // +0x04
    int *mpCap;   // +0x08
};

// the reader object used by 00b0a310
struct Stream {
    void *mpVtbl;          // +0x00
    Stream *GetOuter();    // vtable slot 8  (0x20)
    void   *GetIO();       // vtable slot 6  (0x18)
    void    EndRead();     // vtable slot 7  (0x1c)
    void    ReadTreeRefVector(void *pThis, void *pVec);  // 0x00b0a310
};

// -------------------------------------------------------------- extern decls

extern "C" void  FUN_00b07140(void *pVec, void *pBegin, void *pEnd);
extern "C" Mgr  *FUN_00b3d440();
extern "C" void *FUN_00b08e90(void *pThis);
extern "C" void *FUN_00b04ba0(void *pThis, u32 a, u32 b);
extern "C" int   FUN_00b3d310();
extern "C" void  FUN_00b023d0(void *pThis, void *a, u32 b, u32 c);
extern "C" void *FUN_00b091d0(void *pThis);
extern "C" void *FUN_00b06cd0(void *pThis);
extern "C" void  FUN_00b065c0(void *pDst, void *pSrc);
extern "C" float FUN_00b00000f();
extern "C" void  FUN_00b06340(void *a, void *b, float x, float y, float z);
extern "C" void  FUN_00b060f0(void *pVec, u32 n);
extern "C" void  FUN_00b03680(TreeData *pDst, const TreeData *pSrc);
extern "C" void  FUN_00b07190(void *pVec, u32 where, const TreeData *pSrc);
extern "C" void  FUN_00b97280(void *pDst, u32 n, u32 *pOut);
extern "C" void  FUN_00b98ea0(void *p, u32 n);
extern "C" void  FUN_00b96600(void *pVec, u32 *pWhere);
extern "C" void  FUN_00d01790(void *pThis, u32 n);
extern "C" void  FUN_00b09340(Mgr *pThis, float f, int **ppEnd, u32 a, u32 b);
extern "C" void  SetSeed(u32 seed);
extern "C" double RandomDoubleUniform(void);
extern "C" u32    RandomUint32Uniform(u32 n);
extern "C" int    ReadInt32(void *pIO, u32 *pOut, u32 n, u32 z);
extern "C" int    FUN_00702760(void *pThis, float r, float *pPos, u32 n, void *pList);

extern "C" void *SP__NounManager(u32 h);
extern "C" void  SP__cGameNounManager__RemoveNoun(void *pThis, u32 h);
extern "C" void *EA__Audio__GetSystemAT();
extern "C" void  Start3dSoundByName(u32 id, void *pSys, float x, float y, float z);
extern "C" void *SP__App();
extern "C" void *SP__PlanetModel(void *pOut, const float *pIn);
extern "C" void *SP__cPlanetModel__DirectionToSurfacePosition(void *pThis, void *a, void *b);
extern "C" void  SP__cViewer__GetCameraLocationInfo(void *pThis, void *a, void *b, int c, int d);
extern "C" void *SP__cVarListSerializer__ctor(void *pThis, void *a, const char *s, u32 n);
extern "C" char  SP__cVarListSerializer__Serialize(void *pThis, u32 a);
extern "C" void *rw__math__fpu__QuaternionFromMatrix33(void *pOut, void *pIn, int n);
extern "C" void *cSPTransformOps__Assign(void *pThis, const void *pSrc);
extern "C" void *translateTransform(void *pOut, const char *pIn, const float *pVec);
extern "C" void  eastl__copy_backward(void *pFirst, void *pLast, void *pOut);
extern "C" void  FUN_00aea5d0(void *pPos, void **ppSrc);
extern "C" void  FUN_00c3f8b0(int a, int b);
extern "C" void  FUN_00b53940(void *pThis);
extern "C" void  FUN_00b5a260(void *pThis, int a);
extern "C" void  FUN_00b54200(void *pThis);
extern "C" void  FUN_00b54230(void *pThis, int a);

extern "C" void operator_delete_array(void *p);
extern "C" void memcpy(void *d, const void *s, u32 n);

// Out-of-line copy helpers (the container copy constructors 0x01011cc0 / 0x00b07050).
// These are really *assignments*: they read the destination's mpBegin/mpCap, so the
// destination header must already be initialised before the call.
typedef void (__thiscall *FAssign16)(Fv16 *, const Fv16 *);
typedef void (__thiscall *FAssign512)(Fv512 *, const Fv512 *);
static inline void CopyFv16Contents(Fv16 *pDst, const Fv16 *pSrc) {
    ((FAssign16)0x01011cc0)(pDst, pSrc);
}
static inline void CopyFv512Contents(Fv512 *pDst, const Fv512 *pSrc) {
    ((FAssign512)0x00b07050)(pDst, pSrc);
}

// __thiscall entry points for the manager helpers (this in ecx).
typedef int FTC_dummy;
extern "C" void *__fastcall FUN_00b03320(Mgr *p, int dummy, u32 a, u32 b, u32 c);
extern "C" u32   __fastcall FUN_00b058f0(Mgr *p, int dummy);
static inline void *FUN_00b03320_tc(Mgr *p, u32 a, u32 b, u32 c) {
    return FUN_00b03320(p, 0, a, b, c);
}
static inline u32 FUN_00b058f0_tc(Mgr *p) { return FUN_00b058f0(p, 0); }

// ------------------------------------------------------------------ functions

// @ 0x00b09570
Scatter::Scatter(const Scatter &src)
{
    mX = src.mX;
    mY = src.mY;
    mZ = src.mZ;
    mSpread = src.mSpread;
    mPad10 = src.mPad10;
    mPad14 = src.mPad14;
    mPad18 = src.mPad18;
    mPad1c = src.mPad1c;
    mPad20 = src.mPad20;
    mPad24 = src.mPad24;
    mPad28 = src.mPad28;
    mPad2c = src.mPad2c;
    mPad30 = src.mPad30;
    mPad34 = src.mPad34;
    mPad38 = src.mPad38;
    mPad3c = src.mPad3c;
    mFlag40 = src.mFlag40;
    Fv16 *p0 = &mSmall0;
    p0->mpBegin = p0->mBuf;
    p0->mpEnd = p0->mBuf;
    p0->mpCap = p0->mBuf + 16;
    p0->mCount = 0;
    CopyFv16Contents(p0, &src.mSmall0);
    Fv16 *p1 = &mSmall1;
    p1->mpBegin = p1->mBuf;
    p1->mpEnd = p1->mBuf;
    p1->mpCap = p1->mBuf + 16;
    p1->mCount = 0;
    CopyFv16Contents(p1, &src.mSmall1);
    Fv16 *p2 = &mSmall2;
    p2->mpBegin = p2->mBuf;
    p2->mpEnd = p2->mBuf;
    p2->mpCap = p2->mBuf + 16;
    p2->mCount = 0;
    CopyFv16Contents(p2, &src.mSmall2);
    mTimerA = src.mTimerA;
    mTimerB = src.mTimerB;
    Fv512 *b0 = &mBig0;
    b0->mpBegin = b0->mBuf;
    b0->mpEnd = b0->mBuf;
    b0->mpCap = b0->mBuf + 512;
    b0->mCount = 0;
    CopyFv512Contents(b0, &src.mBig0);
    Fv512 *b1 = &mBig1;
    b1->mpBegin = b1->mBuf;
    b1->mpEnd = b1->mBuf;
    b1->mpCap = b1->mBuf + 512;
    b1->mCount = 0;
    CopyFv512Contents(b1, &src.mBig1);
    Fv512 *b2 = &mBig2;
    b2->mpBegin = b2->mBuf;
    b2->mpEnd = b2->mBuf;
    b2->mpCap = b2->mBuf + 512;
    b2->mCount = 0;
    CopyFv512Contents(b2, &src.mBig2);
}

// @ 0x00b09740
char Scatter::F09740(u32 param_2)
{
    char buf[0xa14];
    SP__cVarListSerializer__ctor(buf, this, (const char *)0x01567428, 0x1a80d26);
    char ok = SP__cVarListSerializer__Serialize(buf, param_2);
    if (ok != 0) {
        if (mBig0.mpBegin != mBig0.mpEnd) {
            FUN_00b065c0(&mBig0, &mSmall0);
            FUN_00b07140(&mBig0, mBig0.mpBegin, mBig0.mpEnd);
        }
        if (mBig1.mpBegin != mBig1.mpEnd) {
            FUN_00b065c0(&mBig1, &mSmall1);
            FUN_00b07140(&mBig1, mBig1.mpBegin, mBig1.mpEnd);
        }
        if (mBig2.mpBegin != mBig2.mpEnd) {
            FUN_00b065c0(&mBig2, &mSmall2);
            FUN_00b07140(&mBig2, mBig2.mpBegin, mBig2.mpEnd);
        }
        return ok;
    }
    return 0;
}

// @ 0x00b09830
Scatter *Mgr::Place(u32 index, int *pOut)
{
    Scatter *pEntry = 0;
    Mgr *pMan = this;
    if (*(char *)&pOut != 0) {
        pMan = FUN_00b3d440();
        Scatter *pNew = (Scatter *)FUN_00b08e90(pMan);
        if (pNew == 0)
            goto done;
        vc_v(pNew, 0);
        pOut = (int *)pNew;
        pMan = FUN_00b3d440();
        u32 *pEnd = pMan->mpTreesBegin;
        if (pEnd < pMan->mpTreesEnd) {
            pMan->mpTreesBegin = pEnd + 1;
            pEntry = pNew;
            if (pEnd != 0) {
                *pEnd = (u32)pNew;
                vc_v(pNew, 0);
            }
        } else {
            FUN_00aea5d0(pEnd, (void **)&pOut);
            pEntry = (Scatter *)pOut;
        }
        vc_v(pEntry, 0x5c);
        if (*(int *)((char *)pEntry + 0x16c) != 1)
            *(int *)((char *)pEntry + 0x16c) = 1;
        {
            float mat[3];
            translateTransform(mat, (const char *)(pMan->mpSpots + index * 0xe),
                               &this->mSpawnX);
            char *pTr = (char *)pEntry + 0x34;
            ((F1p)VS(pTr, 0x38))(pTr, &mat[1]);
            float q[4];
            rw__math__fpu__QuaternionFromMatrix33(q, mat, 0);
            ((F1p)VS(pTr, 0x3c))(pTr, q);
            ((char *)pEntry)[0xa9] = 1;
            ((char *)pEntry)[0xab] = 0;
            ((char *)pEntry)[0xa4] = 1;
            ((char *)pEntry)[0xa3] = 1;
            FUN_00b53940(pTr);
            FUN_00b3d310();
            FUN_00b5a260(pTr, 0);
            FUN_00b54200(pTr);
            FUN_00b54230(pTr, 0);
            int *pQ = (int *)vc_p(pTr, 0x98);
            if (pQ[0] != (int)0x4f15bfb5 || pQ[1] != (int)0x00b1b104 || pQ[2] != 0)
                vc_vu(pTr, 0x94, 0x0156741c);
            u32 *pF = (u32 *)vc_p(pTr, 0xac);
            if (pF != 0) {
                pF[1] |= 1;
                ((F1i)VS(pF, 0x16c))(pF, 1);
                cSPTransformOps__Assign(pF + 2, mat);
                FUN_00c3f8b0(1, 0);
                *(int *)((char *)pEntry + 0x158) = (int)this->mSelB;
                *(int *)((char *)pEntry + 0x15c) = (int)this->mSelA;
                *(int *)((char *)pEntry + 0x160) = (int)this->mSelC;
                *(int *)((char *)pEntry + 0x150) = -1;
            }
        }
    }
done:
    {
        u32 selA = this->mSelA;
        u32 selC = this->mSelC;
        u32 selB = this->mSelB;
        pMan = FUN_00b3d440();
        int *pVec = (int *)FUN_00b04ba0(pMan, selA, selB);
        if (pVec != 0 && selC < (u32)((pVec[1] - *pVec) >> 2)) {
            int pObj = *(int *)(*pVec + selC * 4);
            if (pObj != 0) {
                u64 mask = 1ULL << index;
                *(u32 *)(pObj + 0x48) &= ~(u32)mask;
                *(u32 *)(pObj + 0x4c) &= ~(u32)(mask >> 32);
            }
        }
    }
    {
        u32 spot = this->mpIndexA[index];
        u32 arg = this->mpIndexB ? this->mpIndexB[0] : 0;
        pMan = FUN_00b3d440();
        FUN_00b023d0(pMan, (void *)spot, arg, 0);
    }
    {
        void *pSys = EA__Audio__GetSystemAT();
        void *pSnd;
        if (pSys == 0)
            pSnd = 0;
        else
            pSnd = vc_p(pSys, 0x20);
        Start3dSoundByName(0xbd19551a, pSnd, this->mSoundX, this->mSoundY, this->mSoundZ);
    }
    if (pEntry != 0)
        vc_v(pEntry, 4);
    return pEntry;
}

// @ 0x00b09b00
void Mgr::RemoveAllNouns()
{
    u32 *pIt = mpTreesBegin;
    if (pIt != mpTreesEnd) {
        do {
            u32 h = *pIt;
            void *pNM = SP__NounManager(h);
            SP__cGameNounManager__RemoveNoun(pNM, h);
            if (pIt + 1 < mpTreesEnd)
                eastl__copy_backward(pIt + 1, mpTreesEnd, pIt);
            mpTreesEnd--;
            u32 last = *mpTreesEnd;
            if (last != 0)
                ((F0v)VS((void *)last, 4))((void *)last);
        } while (pIt != mpTreesEnd);
    }
    mFlagsB &= 0xffffffef;
    mCount1659c = 0;
    FUN_00b06cd0(this);
}

// @ 0x00b09b80  (this = Mgr, pTree = the group object, index = bit index)
Scatter *Mgr::PlaceIndexed(Scatter *pTreeRaw, u32 index, u32 param_3)
{
    u64 mask = 1ULL << index;
    const TreeBits *pBits = (const TreeBits *)pTreeRaw;
    if ((((u32)mask & pBits->mMaskLo) | ((u32)(mask >> 32) & pBits->mMaskHi)) == 0)
        return 0;
    Mgr *pSub = (Mgr *)FUN_00b03320_tc(this, pBits->mSeedZ,
                                       pBits->mSeedX,
                                       pBits->mSeedY);
    Scatter *pFound = (Scatter *)0;
    if (pSub != 0) {
        u32 cnt = FUN_00b058f0_tc(pSub);
        if (index < cnt)
            pFound = pSub->Place(index, (int *)param_3);
    }
    return pFound;
}

// @ 0x00b09bf0
void Mgr::UpdateFruit(int period)
{
    float dt = (float)period * 0.001f;
    if ((*(u32 *)0x0167bbe4 & 1) == 0) {
        *(u32 *)0x0167bbe4 |= 1;
        SetSeed(0xffffffff);
    }
    char buf[0x100];
    int *pAnchors[3] = { (int *)buf, (int *)buf, (int *)buf + 0x40 };
    int *pBegin = (int *)buf;
    int *pEnd = pBegin;
    (void)pAnchors;
    if ((mFlagsB >> 3 & 1) != 0 || (mFlagsB >> 5 & 1) != 0) {
        int *pApp = (int *)SP__App();
        int *pV = (int *)vc_p(pApp, 0x50);
        void *pViewer = vc_p(pV, 0x1c);
        float loc[3] = { *(float *)0x0167af5c, *(float *)0x0167af60, *(float *)0x0167af64 };
        float dir[3] = { *(float *)0x0167af5c, *(float *)0x0167af60, *(float *)0x0167af64 };
        if (pViewer != 0) {
            SP__cViewer__GetCameraLocationInfo(pViewer, loc, dir, 0, 0);
            void *pPM = SP__PlanetModel(dir, loc);
            SP__cPlanetModel__DirectionToSurfacePosition(pPM, dir, loc);
            FUN_00b09340(this, 200.0f, &pBegin, 0, 0);
            pEnd = pAnchors[1];
        }
    }
    int n = (int)((char *)pEnd - (char *)pBegin) >> 2;
    if ((mFlagsB >> 5 & 1) != 0 && n > 0) {
        for (int i = 0; i < n; i++) {
            int e = pBegin[i];
            float v = *(float *)(e + 0x150) - dt;
            *(float *)(e + 0x150) = v;
            if (v < 0.0f) {
                SetSeed(0xffffffff);
                float f = (float)(RandomDoubleUniform() * 2.0 - 1.0);
                if (f > 1.0f) f = 1.0f;
                if (f < -1.0f) f = -1.0f;
                *(float *)(e + 0x150) = f + *(float *)0x015673a0;
                int *pVec = (RandomDoubleUniform() >= 0.5) ? (int *)(e + 0xf4)
                                                           : (int *)(e + 0x9c);
                if (*pVec != pVec[1]) {
                    int cnt = (pVec[1] - *pVec) >> 2;
                    int left = cnt;
                    int t;
                    u32 lo = 0;
                    u32 hi = 0;
                    for (;;) {
                        if (left == 0)
                            goto nextA;
                        left--;
                        u32 r = RandomUint32Uniform((u32)cnt);
                        t = *(int *)(*pVec + r * 4);
                        lo = *(u32 *)(t + 0x48);
                        hi = *(u32 *)(t + 0x4c);
                        if (hi > lo)
                            break;
                    }
                    u32 x = (lo + 1) & ~lo;
                    int b;
                    if (x == 0) {
                        b = 0x20;
                    } else {
                        b = 1;
                        u32 u = x;
                        if ((u & 0xffff) == 0) { b = 0x11; u >>= 16; }
                        if ((unsigned char)u == 0) { b += 8; u >>= 8; }
                        if ((u & 0xf) == 0) { b += 4; u >>= 4; }
                        if ((u & 3) == 0) { b += 2; u >>= 2; }
                        b -= (int)(u & 1);
                    }
                    u64 m = 1ULL << b;
                    *(u32 *)(t + 0x48) = (u32)m | lo;
                    *(u32 *)(t + 0x4c) = (u32)(m >> 32) | hi;
                    Mgr *pSub;
                    do {
                        pSub = (Mgr *)FUN_00b03320_tc(this, *(u32 *)(t + 0x58),
                                                      *(u32 *)(t + 0x50),
                                                      *(u32 *)(t + 0x54));
                    } while (pSub == 0);
                    {
                        u32 spot = pSub->mpIndexA[b];
                        u32 arg = pSub->mpIndexB[0];
                        Mgr *pM2 = FUN_00b3d440();
                        FUN_00b023d0(pM2, (void *)spot, arg, 0x3f800000);
                    }
                }
            }
        nextA:;
        }
    }
    if ((mFlagsB >> 3 & 1) != 0 && n > 0) {
        for (int i = 0; i < n; i++) {
            int e = pBegin[i];
            float v = *(float *)(e + 0x14c) - dt;
            *(float *)(e + 0x14c) = v;
            if (v < 0.0f) {
                SetSeed(0xffffffff);
                *(float *)(e + 0x14c) = FUN_00b00000f();
                int *pVec = (RandomDoubleUniform() >= 0.5) ? (int *)(e + 0xf4)
                                                           : (int *)(e + 0x9c);
                int cnt = (pVec[1] - *pVec) >> 2;
                int left = cnt;
                int t;
                for (;;) {
                    if (left == 0)
                        goto nextB;
                    left--;
                    u32 r = RandomUint32Uniform((u32)cnt);
                    t = *(int *)(*pVec + r * 4);
                    if (*(u32 *)(t + 0x48) != 0)
                        break;
                }
                {
                    u32 lo = *(u32 *)(t + 0x48);
                    int b;
                    if (lo == 0) {
                        b = 0x20;
                    } else {
                        b = 1;
                        u32 u = lo;
                        if ((u & 0xffff) == 0) { b = 0x11; u >>= 16; }
                        if ((unsigned char)u == 0) { b += 8; u >>= 8; }
                        if ((u & 0xf) == 0) { b += 4; u >>= 4; }
                        if ((u & 3) == 0) { b += 2; u >>= 2; }
                        b -= (int)(u & 1);
                    }
                    PlaceIndexed((Scatter *)t, (u32)b, 1);
                }
            }
        nextB:;
        }
    }
    if (pBegin != 0 && pBegin[-1] != 0)
        operator_delete_array(pBegin);
}

// @ 0x00b0a040
char Mgr::SerializeMgr(u32 param_2)
{
    char buf[0xa14];
    void *pOuter = (char *)this - 4;
    SP__cVarListSerializer__ctor(buf, pOuter, (const char *)0x01567a80, 0x1a80d26);
    char ok = SP__cVarListSerializer__Serialize(buf, param_2);
    mFlagsA &= 0xfffffffd;
    mFlagsB = 0x1388;
    if ((mFlagsA & 0x10) != 0) {
        FUN_00b091d0(pOuter);
        return ok;
    }
    FUN_00b06cd0(pOuter);
    return ok;
}

// @ 0x00b0a0c0
void Mgr::QueryTrees(float *pPos, void **ppVec, u32 mask, float radius,
                     int sort, float *pSortPos, int needFruit)
{
    if (*(u32 *)((char *)mpGrid + 0x24) == *(u32 *)((char *)mpGrid + 0x28))
        return;
    {
        float org[3];
        void *pPM = SP__PlanetModel(org, pPos);
        SP__cPlanetModel__DirectionToSurfacePosition(pPM, org, pPos);
        int *pList = 0;
        int found = 0;
        FUN_00b97280(&pList, 0x100, (u32 *)&found);
        int n = FUN_00702760(mpGrid, radius, org, 0x100, (void *)pList);
        FUN_00b98ea0((void *)n, 0);
        Pairs *pVec = (Pairs *)ppVec;
        memcpy(pVec->mpBegin, pVec->mpEnd, 0);
        pVec->mpEnd += (int)(((char *)pVec->mpEnd - (char *)pVec->mpBegin) >> 2) * -4;
        FUN_00d01790(ppVec, (u32)n);
        for (int i = 0; i < n; i++) {
            int e = pList[i];
            if (*(char *)(e + 0x7c) != 0)
                continue;
            u32 kind;
            u32 key = *(u32 *)(e + 0x58);
            if (key == 0x29c388a) kind = 2;
            else if (key == 0x3a8be428) kind = 1;
            else kind = (-(u32)(key != 0x6d60a1cc) & 0xfffffffd) + 4;
            if ((mask & kind) == 0)
                continue;
            if (needFruit != 0 && *(int *)(e + 0x48) == 0)
                continue;
            float dz = pPos[2] - *(float *)(e + 0x18);
            float dy = pPos[1] - *(float *)(e + 0x14);
            float dx = pPos[0] - *(float *)(e + 0x10);
            float r = *(float *)(e + 0x6c) + radius;
            if (dx * dx + dy * dy + dz * dz >= r * r)
                continue;
            if (pVec->mpEnd < pVec->mpCap) {
                int *pSlot = pVec->mpEnd;
                pVec->mpEnd = pSlot + 1;
                if (pSlot != 0)
                    *pSlot = e;
            } else {
                FUN_00b96600(ppVec, (u32 *)&e);
            }
        }
        if (sort != 0 && ((char *)pVec->mpEnd - (char *)pVec->mpBegin) >> 2 > 1) {
            float *p = (pSortPos != 0) ? pSortPos : org;
            FUN_00b06340(pVec->mpBegin, pVec->mpEnd, p[0], p[1], p[2]);
        }
        if (pList != 0 && pList[-1] != 0)
            operator_delete_array(pList);
    }
}

// @ 0x00b0a310
void Stream::ReadTreeRefVector(void *pThis, void *pVecRaw)
{
    char *pVec = (char *)pVecRaw;
    FUN_00b07140(pVec, *(void **)(pVec + 0), *(void **)(pVec + 4));
    u32 count = 0;
    Stream *pS = (Stream *)pThis;
    Stream *pO = pS->GetOuter();
    void *pIO = pO->GetIO();
    ReadInt32(pIO, &count, 1, 0);
    FUN_00b060f0(pVec, count);
    for (u32 i = 0; i < count; i++) {
        TreeData tmp;
        ((F1p)VS(&tmp, 0x14))(&tmp, pThis);
        TreeData *pEnd = *(TreeData **)(pVec + 4);
        if (pEnd < *(TreeData **)(pVec + 8)) {
            *(TreeData **)(pVec + 4) = pEnd + 1;
            if (pEnd != 0)
                FUN_00b03680(pEnd, &tmp);
        } else {
            FUN_00b07190(pVec, (u32)pEnd, &tmp);
        }
        *(int *)&tmp = 0x145c678;
        *(int *)((char *)&tmp + 4) = 0x145c668;
        int *pX = *(int **)((char *)&tmp + 0x6c);
        if (pX != 0)
            ((F0v)VS(pX, 4))((void *)pX);
    }
    pS->EndRead();
}

// @ 0x00b0a3f0
Scatter &Scatter::AssignFrom(const Scatter &src)
{
    mX = src.mX;
    mY = src.mY;
    mZ = src.mZ;
    mSpread = src.mSpread;
    mFlag40 = src.mFlag40;
    mSmall0 = src.mSmall0;
    mSmall1 = src.mSmall1;
    mSmall2 = src.mSmall2;
    mTimerA = src.mTimerA;
    mTimerB = src.mTimerB;
    mBig0 = src.mBig0;
    mBig1 = src.mBig1;
    mBig2 = src.mBig2;
    return *this;
}

// @ 0x00b0a530
ScatterE *CopyBackwardScatterE(const ScatterE *pFirst, ScatterE *pLast, ScatterE *pOut)
{
    if (pLast != pFirst) {
        do {
            pLast--;
            pOut--;
            pOut->mKey = pLast->mKey;
            pOut->mBody.AssignFrom(pLast->mBody);
        } while (pLast != pFirst);
    }
    return pOut;
}
