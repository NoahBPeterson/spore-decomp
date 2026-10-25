// ===========================================================================
// slice s00bab8a0 -- SPStarManager (SPStarSearch.obj) container / teardown
// cluster.  Reconstructed from work/SporeApp.analysis.bin.
//
//   0x00bab8a0  StarTree::FUN_00bab8a0        lower_bound + key compare -> range
//   0x00baba60  TreeNodes::FUN_00baba60       recursive node-list destroy
//   0x00babb70  StarVec::FUN_00babb70         vector insert(pos, n, value)
//   0x00babd30  FUN_00babd30                  introsort loop over 12-byte triples
//   0x00babe70  Manager::FUN_00babe70         destructor
//   0x00bac150  Manager::FUN_00bac150         per-grid-row release pass (clear)
//   0x00bac3a0  Manager::FUN_00bac3a0         per-grid-row release pass (teardown)
//   0x00bac620  Manager::FUN_00bac620         grow the +0xa0 vector from property ids
//   0x00bac7d0  Manager::FUN_00bac7d0         alloc + ctor + push_back into +0x3c vector
//
// Types/layouts follow the sibling slices s00bb5d80 / s00bb0ca0 / s00ba8830
// (this component is the star manager / SPStarSearch translation unit).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
// ===========================================================================

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#pragma warning(disable: 4100 4189 4244 4311 4312)

// ---- allocation -----------------------------------------------------------
void* EAAlloc(int nSize, const char* pName, int a, int b, const char* pFile, int nLine); // 0x00f473a0
void  EAFree(void* pMem);                                                                 // 0x00f47380

// ---- external callees -----------------------------------------------------
void* MemMove(void* pDst, const void* pSrc, u32 nBytes);                    // 0x011e0744
void  FillCompute(void* a, u32 n, void* c, const void* v);                  // 0x00b2ac90
void  UninitMoveN(void* a, void* b, void* c, void* d);                      // 0x00829110
void  MoveBackwardC(void* a, void* b, void* c);                             // 0x00ac97a0
void  FillRange(void* a, u32 n, void* c);                                     // 0x00ea0350
void* LowerBound4(void* pBegin, void* pEnd, const void* pValue, u8 flag);   // 0x00ba95f0
int   CompareKey8(u32 a0, u32 a1, u32 b0, u32 b1);                          // 0x005e9260
void* Partition12(void* pBegin, void* pEnd, const void* pPivot, void* pPred); // 0x00baa810
void  TriplesBaseSort(void* pBegin, void* pMid, void* pEnd, void* pPred);   // 0x00ba9810
void  Free5(void* a, void* b, void* c, void* d, void* e);                   // 0x00571db0
void* CopyImpl(void* pFirst, void* pLast, void* pResult);                   // 0x006782c0
void* MessageServer();                                                      // 0x006abf00
void* PropertyServer();                                                     // 0x0067de30
void* TheManager();                                                         // 0x0067dcd0

// thiscall sub-object / algorithm callees (ecx = the sub-object).
struct CalleeVec {
    void FUN_00ae6970();                                        // 0x00ae6970
    void FUN_00d0c930(void* a);                                 // 0x00d0c930
    void FUN_009a9600(void* a);                                 // 0x009a9600
    void FUN_006a4950(void* a, void* b);                        // 0x006a4950
    void FUN_00547e50(void* a, void* b);                        // 0x00547e50
    void FUN_00ba8340(void* a, void* b);                        // 0x00ba8340
    void FUN_01038250();                                        // 0x01038250
    void FUN_00b5b9a0();                                        // 0x00b5b9a0
    void FUN_004558a0(void* a, void* b);                        // 0x004558a0
    void FUN_00b96600(void* a, void* b);                        // 0x00b96600
};
struct AllocObj {
    void FUN_00c8b640();                                        // 0x00c8b640
};
#define SUB(o, off) ((CalleeVec*)((u8*)(o) + (off)))

// ---- vtable helpers (thiscall dispatch through a member pointer) ----------
struct VtblObj { void C0(); void C1(void*); void C2(void*, void*); char R1(void*); };
typedef void  (VtblObj::*PMF0)();
typedef void  (VtblObj::*PMF1)(void*);
typedef void  (VtblObj::*PMF2)(void*, void*);
typedef char  (VtblObj::*PMFR1)(void*);
inline void VCall(void* pObj, u32 nOff)
{
    (((VtblObj*)pObj)->*(*(PMF0*)((u8*)*(void**)pObj + nOff)))();
}
inline void VCallObj(void* pObj, u32 nOff, void* pArg)
{
    (((VtblObj*)pObj)->*(*(PMF1*)((u8*)*(void**)pObj + nOff)))(pArg);
}
inline void VCallObj2(void* pObj, u32 nOff, void* a, void* b)
{
    (((VtblObj*)pObj)->*(*(PMF2*)((u8*)*(void**)pObj + nOff)))(a, b);
}
inline char VCallCharPtr(void* pObj, u32 nOff, void* pArg)
{
    return (((VtblObj*)pObj)->*(*(PMFR1*)((u8*)*(void**)pObj + nOff)))(pArg);
}
inline char VCallCharInt(void* pObj, u32 nOff, int a)
{
    return (((VtblObj*)pObj)->*(*(PMFR1*)((u8*)*(void**)pObj + nOff)))((void*)a);
}

// A 4-byte intrusive smart pointer: the payload's vtable has AddRef at +0 and
// Release at +4.
inline void RefAddRef(void* pPayload)
{
    if (pPayload) VCall(pPayload, 0x00);
}
inline void RefRelease(void* pPayload)
{
    if (pPayload) VCall(pPayload, 0x04);
}

// ---------------------------------------------------------------------------
// 0x00bab8a0 -- tree lower_bound + equal-key test, returning an iterator range
// ---------------------------------------------------------------------------
struct StarTree {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    u8    mGap08[0xc];  // +0x08
    u8    mFlag;        // +0x14
    void FUN_00bab8a0(void** pRange, const void* pKey);
};

// @ 0x00bab8a0
void StarTree::FUN_00bab8a0(void** pRange, const void* pKey)
{
    void* pNode = LowerBound4(mpBegin, mpEnd, pKey, mFlag);
    if (pNode != mpEnd &&
        CompareKey8(((const u32*)pKey)[0], ((const u32*)pKey)[1],
                    ((u32*)pNode)[0], ((u32*)pNode)[1]) >= 0) {
        pRange[0] = pNode;
        pRange[1] = (u8*)pNode + 0x10;
    } else {
        pRange[0] = pNode;
        pRange[1] = pNode;
    }
}

// ---------------------------------------------------------------------------
// 0x00baba60 -- recursive destroy of a sibling list of tree nodes; each node
// owns a child chain (+0x00), a next field (+0x04), a plain buffer (+0x30) and
// a vector of smart pointers (+0x14..+0x18).
// ---------------------------------------------------------------------------
struct TreeNode {
    TreeNode* mpChild;   // +0x00
    TreeNode* mpNext;    // +0x04
    u8        mGap08[0xc];
    void**    mpElemsBegin; // +0x14
    void**    mpElemsEnd;   // +0x18
    u8        mGap1c[0x14];
    void*     mpBuffer30;   // +0x30
};

struct TreeNodes {
    void FUN_00baba60(TreeNode* pNode);
};

// @ 0x00baba60
void TreeNodes::FUN_00baba60(TreeNode* pNode)
{
    while (pNode) {
        FUN_00baba60(pNode->mpChild);
        if (pNode->mpBuffer30)
            EAFree(pNode->mpBuffer30);
        TreeNode* pNext = pNode->mpNext;
        for (void** pp = pNode->mpElemsBegin; pp < pNode->mpElemsEnd; ++pp)
            if (*pp)
                VCall(*pp, 0x04);                    // Release
        if (pNode->mpElemsBegin && ((u32*)pNode->mpElemsBegin)[-1] != 0)
            EAFree(pNode->mpElemsBegin);
        EAFree(pNode);
        pNode = pNext;
    }
}

// ---------------------------------------------------------------------------
// Eastl-style vector of 4-byte smart pointers (0x14 bytes incl. allocator).
// ---------------------------------------------------------------------------
struct StarVec {
    void** mpBegin;     // +0x00
    void** mpEnd;       // +0x04
    void** mpCapacity;  // +0x08
    u32    mAlloc[2];   // +0x0c
    void FUN_00babb70(void* pPos, u32 n, const void* pValue);
};

// @ 0x00babb70
// eastl::vector<T>::insert(position, n, value).  Out-of-line algorithm helpers
// are the same ones the sibling slices use.
void StarVec::FUN_00babb70(void* pPos, u32 n, const void* pValue)
{
    if (n == 0)
        return;
    u32 nFree = (u32)((u8*)mpCapacity - (u8*)mpEnd) / 4;
    if (n > nFree) {
        u32 nOld   = (u32)((u8*)mpEnd - (u8*)mpBegin) / 4;
        u32 nNewCap = nOld > 0 ? nOld * 2 : 1;
        if (nOld + n > nNewCap)
            nNewCap = nOld + n;
        void** pNew = 0;
        if (nNewCap)
            pNew = (void**)EAAlloc(nNewCap * 4, "Simulator", 0, 0,
                        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        u32 nPrefix = (u32)((u8*)pPos - (u8*)mpBegin);
        void** pMid = (void**)((u8*)MemMove(pNew, mpBegin, nPrefix) + nPrefix);
        FillCompute(pMid, n, (void*)((u8*)pMid + n * 4), pValue);
        void** pTail = (void**)((u8*)pMid + n * 4);
        void** pNewEnd = (void**)((u8*)MemMove(pTail, pPos, (u8*)mpEnd - (u8*)pPos) + ((u8*)mpEnd - (u8*)pPos));
        if (mpBegin && ((u32*)mpBegin)[-1] != 0)
            EAFree(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + nNewCap;
        return;
    }

    // enough room: hold one reference to the value, then shift the tail.
    void* pVal = *(void**)pValue;
    RefAddRef(pVal);
    u32 nTail = (u32)((u8*)mpEnd - (u8*)pPos) / 4;
    if (n >= nTail) {
        void** pOldEnd = mpEnd;
        u32 nInit = n - nTail;
        FillCompute(pOldEnd, nInit, (void*)((u8*)pOldEnd + nInit * 4), (void*)&pVal);
        mpEnd = (void**)((u8*)mpEnd + nInit * 4);
        void** pNewEnd = (void**)((u8*)mpEnd + nTail * 4);
        FillRange(pPos, nTail, (void*)&pVal);
        mpEnd = pNewEnd;
    } else {
        void** pOldEnd = mpEnd;
        void** pShift = mpEnd - n;
        UninitMoveN(pShift, mpEnd, pOldEnd, 0);
        mpEnd = (void**)((u8*)mpEnd + n * 4);
        MoveBackwardC(pShift, pPos, pOldEnd);
        FillRange(pPos, n, (void*)&pVal);
    }
    RefRelease(pVal);
}

// ---------------------------------------------------------------------------
// 0x00babd30 -- introsort-style loop over 12-byte {float,float,uint} triples.
// ---------------------------------------------------------------------------
typedef char (*SortPred12)(const void*, const void*);

// @ 0x00babd30
void FUN_00babd30(void* pBegin, void* pEnd, int nDepth, SortPred12 pPred)
{
    int nCount = (int)(((u8*)pEnd - (u8*)pBegin) / 0xc);
    for (;;) {
        if (nCount <= 0x1c)
            break;
        if (nDepth <= 0)
            break;
        u8* pMid = (u8*)pBegin + (nCount / 2) * 0xc;
        u8  pivot[0xc];
        if (pPred(pBegin, pMid)) {
            if (pPred(pMid, (u8*)pEnd - 0xc))
                *(u32*)&pivot[0] = ((u32*)pMid)[0], *(u32*)&pivot[4] = ((u32*)pMid)[1], *(u32*)&pivot[8] = ((u32*)pMid)[2];
            else if (pPred(pBegin, (u8*)pEnd - 0xc))
                *(u32*)&pivot[0] = ((u32*)pEnd)[-3], *(u32*)&pivot[4] = ((u32*)pEnd)[-2], *(u32*)&pivot[8] = ((u32*)pEnd)[-1];
            else
                *(u32*)&pivot[0] = ((u32*)pBegin)[0], *(u32*)&pivot[4] = ((u32*)pBegin)[1], *(u32*)&pivot[8] = ((u32*)pBegin)[2];
        } else {
            if (pPred(pBegin, (u8*)pEnd - 0xc))
                *(u32*)&pivot[0] = ((u32*)pBegin)[0], *(u32*)&pivot[4] = ((u32*)pBegin)[1], *(u32*)&pivot[8] = ((u32*)pBegin)[2];
            else if (pPred(pMid, (u8*)pEnd - 0xc))
                *(u32*)&pivot[0] = ((u32*)pEnd)[-3], *(u32*)&pivot[4] = ((u32*)pEnd)[-2], *(u32*)&pivot[8] = ((u32*)pEnd)[-1];
            else
                *(u32*)&pivot[0] = ((u32*)pMid)[0], *(u32*)&pivot[4] = ((u32*)pMid)[1], *(u32*)&pivot[8] = ((u32*)pMid)[2];
        }
        void* pCut = Partition12(pBegin, pEnd, pivot, (void*)pPred);
        FUN_00babd30(pBegin, pCut, nDepth - 1, pPred);
        pBegin = pCut;
        nCount = (int)(((u8*)pEnd - (u8*)pCut) / 0xc);
    }
    if (nDepth == 0)
        TriplesBaseSort(pBegin, pEnd, pEnd, (void*)pPred);
}

// ---------------------------------------------------------------------------
// The star-manager.  Only the fields the teardown passes touch are named.
// ---------------------------------------------------------------------------
struct VecRows { void** mpBegin; void** mpEnd; void** mpCap; u32 mAlloc[2]; }; // 0x14
struct Ctr12   { void* mpA; void* mpB; void* mpC; void* mpD; };                // 0x10

// ---- vectors --------------------------------------------------------------
// SPVector<AutoRefCount<T>>: erase(first,last) inlined as a CopyImpl call over
// [last, end), a Release of every element from the copied position to the old
// end, then "end -= last - first".
struct RefVec {
    void** pBegin;      // +0x00
    void** pEnd;        // +0x04
    void** pCap;        // +0x08
    void Clear()
    {
        void** pB = pBegin;
        void** pE = pEnd;
        u32    n  = (u32)(pE - pB);
        void** pNew = (void**)CopyImpl(pE, pE, pB);
        for (void** p = pNew; p < pE; ++p)
            if (*p)
                VCall(*p, 0x04);            // Release
        pEnd -= n;
    }
};

// SPVector<unsigned int>: POD elements, so erase() only copies and rewinds.
struct U32Vec {
    u32* pBegin;        // +0x00
    u32* pEnd;          // +0x04
    u32* pCap;          // +0x08
    void DoInsertValue(u32* pPos, const u32& value);   // 0x004558a0
    void Clear()
    {
        u32* pB = pBegin;
        u32* pE = pEnd;
        u32  n  = (u32)(pE - pB);
        MemMove(pB, pE, (u32)(pEnd - pE) * 4);   // copy [last,end) == empty
        pEnd -= n;
    }
};

// One grid cell: two smart-pointer vectors at +0x84 and +0x98.
struct GridElem {
    u8     mGap00[0x84];   // +0x00
    RefVec mVec84;         // +0x84
    u8     mGap90[0x08];   // +0x90
    RefVec mVec98;         // +0x98
};

// ---- message-server event plumbing ---------------------------------------
struct EventKey {          // listener/event key passed to the message server
    void* mpVtbl;          // +0x00  (0x013eb428)
    u32   mTag;            // +0x04  (0x05220cb8)
};

struct EventNode {         // intrusive circular-list node
    EventNode* pNext;      // +0x00
    EventNode* pPrev;      // +0x04
    void*      pValue;     // +0x08
};

struct MsgServer {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20();
    virtual void Query(void* pList, void* pEvent);   // +0x24
    virtual void Fire(void* pEvent);                 // +0x28
};

struct PendingVec {        // vector of 12-byte pending entries
    void* pBegin;          // +0x00
    void* pEnd;            // +0x04
    void* pCap;            // +0x08
};

struct PendingSource {     // the object at Manager::mp224
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20();
    virtual void Finish();                           // +0x24
    virtual void s28(); virtual void s2c();
    virtual void Collect(PendingVec* pOut, int nFlag);   // +0x30
    virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void Visit(void* pEntry);                // +0x40
};

struct GlobalMgr {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void Dispatch(void* pValue, int a, void* pSrc, int b, int c);  // +0x20
};

struct PropertyRef {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20();
    virtual char Read(u32 key, void** pOut);         // +0x24
};

struct PropertyMgr {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20();
    virtual void s24();                               // +0x24
    virtual void s28();
    virtual char Resolve(u32 id, u32 key, void** pOut);   // +0x2c
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44();
    virtual void Query(u32 key, void** pOut);        // +0x48
};

struct Manager {
    void*   mpVtbl;         // +0x000
    void*   mpVtbl4;        // +0x004
    u8      mGap08[0x14];   // +0x008
    void*   mpVtbl1c;       // +0x01c
    Ctr12   mCtr20;         // +0x020
    u8      mGap30[0x0c];   // +0x030
    void*   mpBuf3c;        // +0x03c
    u8      mGap40[0x10];   // +0x040
    void*   mpBuf50;        // +0x050
    u8      mGap54[0x18];   // +0x054
    void*   mp6c;           // +0x06c
    void*   mp70;           // +0x070
    void*   mp74;           // +0x074
    u8      mGap78[0x28];   // +0x078
    U32Vec  mIdsA0;         // +0x0a0
    u8      mGapAc[0x08];   // +0x0ac
    void*   mpB4;           // +0x0b4
    void*   mpB8;           // +0x0b8
    void*   mpBc;           // +0x0bc
    void*   mpC0;           // +0x0c0
    void*   mpC4;           // +0x0c4
    void**  mpGrid;         // +0x0c8  rows, stride 0x14
    void**  mpGridEnd;      // +0x0cc
    u8      mGapD0[0x0c];   // +0x0d0
    VecRows mRowsDc;        // +0x0dc
    VecRows mRowsF0;        // +0x0f0
    VecRows mRows104;       // +0x104
    VecRows mRows118;       // +0x118
    Ctr12   mCtr12c;        // +0x12c
    u8      mGap13c[0x0c];  // +0x13c
    void*   mp148;          // +0x148
    void*   mp14c;          // +0x14c
    Ctr12   mCtr150;        // +0x150
    u8      mGap160[0x0c];  // +0x160
    Ctr12   mCtr16c;        // +0x16c
    u8      mGap17c[0x08];  // +0x17c
    void*   mp184;          // +0x184
    u8      mGap188[0x08];  // +0x188
    void*   mp190;          // +0x190
    Ctr12   mCtr194;        // +0x194  (only +0x1a0/+0x1a4 used)
    u8      mGap1a4[0x04];  // +0x1a4
    u8      mGap1a8[0x34];  // +0x1a8
    void*   mp1dc;          // +0x1dc
    u8      mSub1e0[0x24];  // +0x1e0..+0x203
    void*   mp204;          // +0x204
    void*   mp208;          // +0x208
    void*   mp20c;          // +0x20c
    u8      mGap210[0x10];  // +0x210
    void*   mp220;          // +0x220
    void*   mp224;          // +0x224
    void*   mp228;          // +0x228

    void FUN_00babe70();
    void FUN_00bac150();
    void FUN_00bac3a0();
    void FUN_00bac620(int v);
    void* FUN_00bac7d0();
};

// @ 0x00babe70
void Manager::FUN_00babe70()
{
    mpVtbl   = (void*)0x1466058;
    mpVtbl4  = (void*)0x1466050;
    mpVtbl1c = (void*)0x1466040;

    if (mp228) VCall((u8*)mp228 + 4, 0x04);
    if (mp224) VCall((u8*)mp224 + 4, 0x04);
    if (mp220) VCall(mp220, 0x04);
    if (mp204) VCall((u8*)mp204 + 8, 0x0c);

    SUB(this, 0x208)->FUN_006a4950(mp208, mp20c);
    if (mp208 && ((u32*)mp208)[-1] != 0)
        EAFree(mp208);

    SUB(this, 0x1e0)->FUN_01038250();

    if (mp1dc) VCall(mp1dc, 0x04);
    if (mCtr194.mpA) VCall(mCtr194.mpA, 0x04);
    if (mCtr194.mpB) VCall(mCtr194.mpB, 0x04);

    SUB(this, 0x184)->FUN_009a9600(mp190);

    SUB(this, 0x16c)->FUN_00547e50(mCtr16c.mpA, mCtr16c.mpB);
    if (mCtr16c.mpA)
        EAFree(mCtr16c.mpA);

    SUB(this, 0x150)->FUN_00d0c930(mCtr150.mpD);
    if (mp14c) VCall(mp14c, 0x04);
    if (mp148) VCall(mp148, 0x04);

    SUB(this, 0x12c)->FUN_00d0c930(mCtr12c.mpD);

    SUB(this, 0x118)->FUN_00ae6970();
    SUB(this, 0x104)->FUN_00ae6970();
    SUB(this, 0xf0)->FUN_00ae6970();
    SUB(this, 0xdc)->FUN_00ae6970();

    SUB(this, 0xc8)->FUN_00ba8340(mpGrid, mpGridEnd);
    if (mpGrid && ((u32*)mpGrid)[-1] != 0)
        EAFree(mpGrid);

    if (mpB4) {
        Free5(mpB4, mpB8, mpBc, mpC0, mpC4);
        mpB4 = 0;
    }
    if (mIdsA0.pBegin && ((u32*)mIdsA0.pBegin)[-1] != 0)
        EAFree(mIdsA0.pBegin);

    if (((u32)((u8*)mp74 - (u8*)mp6c) & 0xfffffffe) > 2 && mp6c)
        EAFree(mp6c);
    if (mpBuf50 && ((u32*)mpBuf50)[-1] != 0)
        EAFree(mpBuf50);
    if (mpBuf3c && ((u32*)mpBuf3c)[-1] != 0)
        EAFree(mpBuf3c);

    SUB(this, 0x20)->FUN_009a9600(mCtr20.mpD);
    mpVtbl1c = (void*)0x13eb394;
    SUB(this, 0)->FUN_00b5b9a0();
}

// @ 0x00bac150
void Manager::FUN_00bac150()
{
    EventKey event;
    event.mpVtbl = (void*)0x13eb428;
    event.mTag   = 0x5220cb8;

    u32 rowOffset = 0;
    for (u32 i = 0; i < (u32)((int)((u8*)mpGridEnd - (u8*)mpGrid) / 0x14); ++i) {
        VecRows* pRow = (VecRows*)((u8*)mpGrid + rowOffset);
        for (u32 j = 0; j < (u32)(pRow->mpEnd - pRow->mpBegin); ++j) {
            GridElem* pElem = (GridElem*)pRow->mpBegin[j];
            pElem->mVec84.Clear();
            pElem->mVec98.Clear();
        }
        rowOffset += 0x14;
    }

    ((MsgServer*)MessageServer())->Fire(&event);

    if (mp224) {
        PendingVec pending;
        pending.pBegin = 0;
        pending.pEnd   = 0;
        pending.pCap   = 0;
        ((PendingSource*)mp224)->Collect(&pending, 0);
        for (int k = 0; k < (int)((u8*)pending.pEnd - (u8*)pending.pBegin) / 0xc; ++k)
            ((PendingSource*)mp224)->Visit((u8*)pending.pBegin + k * 0xc);
        ((PendingSource*)mp224)->Finish();
        if (pending.pBegin && ((u32*)pending.pBegin)[-1] != 0)
            EAFree(pending.pBegin);
    }
}

// @ 0x00bac3a0
void Manager::FUN_00bac3a0()
{
    EventKey event;
    event.mpVtbl = (void*)0x13eb428;
    event.mTag   = 0x5220cb8;

    EventNode list;
    list.pNext = &list;
    list.pPrev = &list;

    ((MsgServer*)MessageServer())->Query(&list, &event);

    while (list.pNext != &list) {
        EventNode* pNode = list.pNext;
        ((GlobalMgr*)TheManager())->Dispatch(pNode->pValue, 0, mp224, 0, 0);
        pNode->pPrev->pNext = pNode->pNext;
        pNode->pNext->pPrev = pNode->pPrev;
        if (pNode->pValue)
            VCall(pNode->pValue, 0x04);             // Release
        EAFree(pNode);
    }

    ((PendingSource*)mp224)->Finish();

    u32 rowOffset = 0;
    for (u32 i = 0; i < (u32)((int)((u8*)mpGridEnd - (u8*)mpGrid) / 0x14); ++i) {
        VecRows* pRow = (VecRows*)((u8*)mpGrid + rowOffset);
        for (u32 j = 0; j < (u32)(pRow->mpEnd - pRow->mpBegin); ++j) {
            GridElem* pElem = (GridElem*)pRow->mpBegin[j];
            pElem->mVec84.Clear();
            pElem->mVec98.Clear();
        }
        rowOffset += 0x14;
    }

    ((MsgServer*)MessageServer())->Fire(&event);

    ((PendingSource*)mp224)->Finish();

    EventNode* pNode = list.pNext;
    while (pNode != &list) {
        EventNode* pNext = pNode->pNext;
        if (pNode->pValue)
            VCall(pNode->pValue, 0x04);             // Release
        EAFree(pNode);
        pNode = pNext;
    }
}

// ---------------------------------------------------------------------------
// 0x00bac620 -- enumerate the property-id list returned by the property server
// and grow the +0xa0 vector with one element per id.
// ---------------------------------------------------------------------------
// @ 0x00bac620
void Manager::FUN_00bac620(int nType)
{
    U32Vec& ids = mIdsA0;

    if (ids.pBegin != ids.pEnd)
        return;                                     // only when the vector is empty

    ids.Clear();

    U32Vec props;
    props.pBegin = 0;
    props.pEnd   = 0;
    props.pCap   = 0;

    ((PropertyMgr*)PropertyServer())->Query(0xe38475d9, (void**)&props);

    for (u32 i = 0; i < (u32)(props.pEnd - props.pBegin); ++i) {
        u8  b0 = 0;
        u8  b1;
        void* pRef = 0;

        char ok = ((PropertyMgr*)PropertyServer())->Resolve(props.pBegin[i], 0xe38475d9, &pRef);
        if (ok && pRef) {
            void* pVal;
            if (((PropertyRef*)pRef)->Read(0xea288a88, &pVal)
                && *(u16*)((u8*)pVal + 0x12) == 1) {
                void* pD = pVal;
                if (*(u8*)((u8*)pVal + 0x10) & 0x30)
                    pD = *(void**)pVal;
                b0 = *(u8*)pD;
            }
            void* pVal2;
            if (((PropertyRef*)pRef)->Read(0xb57908c6, &pVal2)
                && *(u16*)((u8*)pVal2 + 0x12) == 1) {
                void* pD = pVal2;
                if (*(u8*)((u8*)pVal2 + 0x10) & 0x30)
                    pD = *(void**)pVal2;
                b1 = *(u8*)pD;
            }
        }

        if (!ok || (b1 == (u8)nType && b0 == 0)) {
            if (ids.pEnd < ids.pCap) {
                u32* pSlot = ids.pEnd;
                ids.pEnd = pSlot + 1;
                if (pSlot)
                    *pSlot = props.pBegin[i];
            } else {
                ids.DoInsertValue(ids.pEnd, props.pBegin[i]);
            }
        }

        if (pRef)
            VCall(pRef, 0x04);                      // Release
    }

    if (props.pBegin && ((u32*)props.pBegin)[-1] != 0)
        EAFree(props.pBegin);
}

// @ 0x00bac7d0
void* Manager::FUN_00bac7d0()
{
    void* pObj = EAAlloc(0x50, "Simulator/cStar", 0, 0, 0, 0);
    if (pObj)
        ((AllocObj*)pObj)->FUN_00c8b640();
    else
        pObj = 0;

    u8* pVec = (u8*)this + 0x3c;
    void** pEnd = *(void***)(pVec + 4);
    if (pEnd < *(void***)(pVec + 8)) {
        *(void***)(pVec + 4) = pEnd + 1;
        if (pEnd)
            *pEnd = pObj;
    } else {
        void* tmp = pObj;
        SUB(pVec, 0)->FUN_00b96600(pEnd, &tmp);
    }
    return pObj;
}