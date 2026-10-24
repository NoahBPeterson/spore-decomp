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
void* EraseToEnd(void* pBegin, void* pEnd, void* pValue);                   // 0x006782c0
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
struct VecRows { void* mpBegin; void* mpEnd; void* mpCap; u32 mAlloc[2]; };   // 0x14
struct Ctr12   { void* mpA; void* mpB; void* mpC; void* mpD; };                // 0x10

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
    void*   mpBufA0;        // +0x0a0
    u8      mGapA4[0x10];   // +0x0a4
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
    void*   mp148;          // +0x148
    void*   mp14c;          // +0x14c
    Ctr12   mCtr150;        // +0x150
    Ctr12   mCtr16c;        // +0x16c
    u8      mGap17c[0x08];  // +0x17c
    void*   mp184;          // +0x184
    u8      mGap188[0x08];  // +0x188
    void*   mp190;          // +0x190
    Ctr12   mCtr194;        // +0x194  (only +0x1a0/+0x1a4 used)
    u8      mGap1a8[0x34];  // +0x1a8
    void*   mp1dc;          // +0x1dc
    u8      mGap1e0[0x04];  // +0x1e0  (sub-object starts here)
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
    if (mpBufA0 && ((u32*)mpBufA0)[-1] != 0)
        EAFree(mpBufA0);

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

// ---------------------------------------------------------------------------
// Release helper shared by the two grid passes: destroy [pNewEnd, pOldEnd)
// of a smart-pointer vector and publish the new end.
// ---------------------------------------------------------------------------
static void ReleaseTail(void** pNewEnd, void** pOldEnd)
{
    for (void** pp = pNewEnd; pp < pOldEnd; ++pp)
        if (*pp)
            VCall(*pp, 0x04);
}

// @ 0x00bac150
void Manager::FUN_00bac150()
{
    u32 nRows = (u32)((u8*)mpGridEnd - (u8*)mpGrid) / 0x14;
    for (u32 i = 0; i < nRows; ++i) {
        u8* pRow = (u8*)mpGrid + i * 0x14;          // row: vector of element ptrs
        void** pElem = *(void***)pRow;
        u32 nElems = (u32)((u8*)((void**)pRow)[1] - (u8*)pElem) / 4;
        for (u32 j = 0; j < nElems; ++j) {
            u8* pObj = (u8*)((void**)pElem)[j];
            void** pB84 = (void**)(pObj + 0x84);
            void** pE84 = (void**)(pObj + 0x88);
            void** pNew = (void**)EraseToEnd(pB84, pE84, pE84);
            ReleaseTail(pNew, pE84);
            *pE84 = pNew;

            void** pB98 = (void**)(pObj + 0x98);
            void** pE98 = (void**)(pObj + 0x9c);
            void** pNew2 = (void**)EraseToEnd(pB98, pE98, pE98);
            ReleaseTail(pNew2, pE98);
            *pE98 = pNew2;
        }
    }

    void* pSrv = MessageServer();
    u8 local[0x10];
    *(u32*)&local[0x0] = 0x13eb428;
    *(u32*)&local[0x4] = 0x5220cb8;
    *(void**)&local[0x8] = this;
    VCallObj(pSrv, 0x28, local);

    if (mp224) {
        void* pTemp[3] = { 0, 0, 0 };
        VCallObj2(mp224, 0x30, 0, pTemp);           // fill a temp list
        void** pB = (void**)pTemp[0];
        void** pE = (void**)pTemp[1];
        u32 n = (u32)((u8*)pE - (u8*)pB) / 0xc;
        for (u32 k = 0; k < n; ++k)
            VCallObj(mp224, 0x40, (u8*)pB + k * 0xc);
        VCall(mp224, 0x24);
        if (pTemp[0] && ((u32*)pTemp[0])[-1] != 0)
            EAFree(pTemp[0]);
    }
}

// @ 0x00bac3a0
void Manager::FUN_00bac3a0()
{
    if (mp224) {
        void* pTemp[3] = { 0, 0, 0 };
        VCallObj(mp224, 0x24, pTemp);
        void* pHead = pTemp[0];
        while (pHead) {
            void* pNext = *(void**)((u8*)pHead + 8);
            void* pMgr = TheManager();
            VCallObj(pMgr, 0x20, *(void**)((u8*)pHead + 0xc));
            (void)pNext;
            void* pN = pTemp[0];
            if (pN) {
                ((void**)pN)[1] = 0;                // hmm: unlink
            }
            if (pHead) EAFree(pHead);
            pTemp[0] = pTemp[1];
            pHead = pTemp[0];
        }
        VCall(mp224, 0x24);
    }

    u32 nRows = (u32)((u8*)mpGridEnd - (u8*)mpGrid) / 0x14;
    for (u32 i = 0; i < nRows; ++i) {
        u8* pRow = (u8*)mpGrid + i * 0x14;
        void** pElem = *(void***)pRow;
        u32 nElems = (u32)((u8*)((void**)pRow)[1] - (u8*)pElem) / 4;
        for (u32 j = 0; j < nElems; ++j) {
            u8* pObj = (u8*)((void**)pElem)[j];
            void** pB84 = (void**)(pObj + 0x84);
            void** pE84 = (void**)(pObj + 0x88);
            void** pNew = (void**)EraseToEnd(pB84, pE84, pE84);
            ReleaseTail(pNew, pE84);
            *pE84 = pNew;

            void** pB98 = (void**)(pObj + 0x98);
            void** pE98 = (void**)(pObj + 0x9c);
            void** pNew2 = (void**)EraseToEnd(pB98, pE98, pE98);
            ReleaseTail(pNew2, pE98);
            *pE98 = pNew2;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00bac620 -- enumerate the property-id list returned by the property server
// and grow the +0xa0 vector with one element per id.
// ---------------------------------------------------------------------------
struct SmallCtr { void* mpBegin; void* mpEnd; void* mpCap; };   // 0x0c

// @ 0x00bac620
void Manager::FUN_00bac620(int)
{
    if (mpBufA0 != *(void**)((u8*)this + 0xa4))
        return;                                     // only when the vector is empty

    u32 nIds;
    {
        void* pList[2];
        void* pSrv = PropertyServer();
        void (*pGet)(void*, u32, void*) = (void (*)(void*, u32, void*))(*(void**)((u8*)*(void**)pSrv + 0x48));
        pGet(pSrv, 0xe38475d9, pList);
        nIds = (u32)((u8*)pList[1] - (u8*)pList[0]) / 4;

        for (u32 i = 0; i < nIds; ++i) {
            void* pObj = 0;
            void* pSrv2 = PropertyServer();
            char ok = ((char (*)(void*, u32, u32, void*))(*(void**)((u8*)*(void**)pSrv2 + 0x2c)))
                          (pSrv2, 0xe38475d9, ((u32*)pList[0])[i], &pObj);
            if (!ok)
                continue;

            u8 b0 = 0, b1 = 0;
            if (pObj) {
                void* pVal = 0;
                if (((char (*)(void*, u32, void*))(*(void**)((u8*)*(void**)pObj + 0x24)))(pObj, 0xea288a88, &pVal)) {
                    if (pVal && *(u16*)((u8*)pVal + 0x12) == 1) {
                        void* pD = pVal;
                        if (*(u8*)((u8*)pVal + 0x10) & 0x30)
                            pD = *(void**)pVal;
                        b0 = *(u8*)pD;
                    }
                }
                void* pVal2 = 0;
                if (((char (*)(void*, u32, void*))(*(void**)((u8*)*(void**)pObj + 0x24)))(pObj, 0xb57908c6, &pVal2)) {
                    if (pVal2 && *(u16*)((u8*)pVal2 + 0x12) == 1) {
                        void* pD = pVal2;
                        if (*(u8*)((u8*)pVal2 + 0x10) & 0x30)
                            pD = *(void**)pVal2;
                        b1 = *(u8*)pD;
                    }
                }
            }

            // push_back into the +0xa0 vector.
            {
                void** pEnd = *(void***)((u8*)this + 0xa4);
                void** pCap = *(void***)((u8*)this + 0xa8);
                if (pEnd < pCap) {
                    *pEnd = pObj;
                    *(void***)((u8*)this + 0xa4) = pEnd + 1;
                } else {
                    void* tmp = pObj;
                    SUB(this, 0xa0)->FUN_004558a0(pEnd, &tmp);
                }
            }
        }
    }
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