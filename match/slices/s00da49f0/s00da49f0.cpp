// Slice s00da49f0: SP::cSocialBand construction / copy / assignment, the cSocialBand entry-list
// move/copy helpers used by the band pool, and SP::SOCIAL_PROPOSE_Tick (the 9-state propose
// behaviour).  Reconstructed from the frozen gold6 disassembly.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <string.h>

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// shared refcounted pointer (the band keeps two of them).  Only the first two vtable slots are
// ever used: slot 0 = AddRef, slot 1 = Release.
// ---------------------------------------------------------------------------
struct RefCounted {
    void** mpVTable;                                                         // +0x00
    void AddRef()  { ((void(__thiscall*)(void*))mpVTable[0])(this); }
    void Release() { ((void(__thiscall*)(void*))mpVTable[1])(this); }
};

// ---------------------------------------------------------------------------
// cActionCircle (0x64 bytes): an embedded scripted action, at cSocialBand +0x178.
// ---------------------------------------------------------------------------
struct cActionCircle {
    uint8_t mData[0x64];                                                     // +0x00
    void* Init();                                                            // 0x00afba10
    cActionCircle* Assign(const cActionCircle* pSrc);                        // 0x00d5d4b0
    cActionCircle* CopyInit(const cActionCircle* pSrc);                      // 0x00c278e0
};

// ---------------------------------------------------------------------------
// the embedded EASTL-style vectors.  Only the three pointer lanes are driven through the external
// helpers, so each is modelled with its real size and named lanes.
// ---------------------------------------------------------------------------
struct VecA {                                                               // +0x064, size 0x14
    void* mpBegin;                                                           // +0x00
    void* mpEnd;                                                             // +0x04
    void* mpCap;                                                             // +0x08
    void* mpField70;                                                         // +0x70
    void* mpField74;                                                         // +0x74
    void* Assign(const VecA* pSrc);                                          // 0x01011cc0
    void  InitBuffer(int nCount, void* pSrcBuf);                             // 0x00b93c60
};

struct VecB {                                                               // +0x078, size 0x10
    void* mpBegin;                                                           // +0x00
    void* mpEnd;                                                             // +0x04
    void* mpCap;                                                             // +0x08
    void* mpField84;                                                         // +0x84
    void* Assign(const VecB* pSrc);                                          // 0x01011cc0
    void  InitBuffer(int nCount, void* pSrcBuf);                             // 0x00b93c60
};

struct VecC {                                                               // +0x08c, size 0x58
    void* mpBegin;                                                           // +0x8c
    void* mpEnd;                                                             // +0x90
    void* mpCap;                                                             // +0x94
    void* mpField98;                                                         // +0x98
    void* mpBufPtr;                                                          // +0x9c
    void* mpFieldA0;                                                         // +0xa0
    uint8_t mBuf[0x40];                                                      // +0xa4
    void* Erase(void* pFirst, void* pLast);                                  // 0x00e25bd0
    void* Assign(void* pFirst, void* pLast, void* pSrcAlloc);                // 0x00bdf600
};

struct VecD {                                                               // +0x0f4, size 0x5c
    void* mpBegin;                                                           // +0xf4
    void* mpEnd;                                                             // +0xf8
    void* mpCap;                                                             // +0xfc
    void* mpField100;                                                        // +0x100
    void* mpField104;                                                        // +0x104
    uint8_t mBuf[0x48];                                                      // +0x108
    void* InitFixed(int n);                                                  // 0x00da1d40
    void* Erase(void* pFirst, void* pLast);                                  // 0x009e0480
    void* Assign(void* pFirst, void* pLast, void* pSrcAlloc);                // 0x00da1250
};

struct VecE {                                                               // +0x150, size 0x28
    void* mpBegin;                                                           // +0x150
    void* mpEnd;                                                             // +0x154
    void* mpCap;                                                             // +0x158
    void* mpField15c;                                                        // +0x15c
    void* mpField160;                                                        // +0x160
    uint8_t mBuf[0x14];                                                      // +0x164
    void* InitFixed(int n);                                                  // 0x00da3b30
    void* Assign(void* pFirst, void* pLast, void* pDest);                    // 0x00da1e70
};

struct VecF {                                                               // +0x1e4, size 0x28
    void* mpBegin;                                                           // +0x1e4
    void* mpEnd;                                                             // +0x1e8
    void* mpCap;                                                             // +0x1ec
    void* mpField1f0;                                                        // +0x1f0
    void* mpBufPtr;                                                          // +0x1f4
    void* mpField1f8;                                                        // +0x1f8
    uint8_t mBuf[0x10];                                                      // +0x1fc
    void* Assign(void* pFirst, void* pLast, void* pDest);                    // 0x00da1f10
};

void FUN_00829110(void* pOut, void* pSrcBegin, void* pSrcEnd, void* pDest, void* pSrc); // 0x00829110

// ---------------------------------------------------------------------------
// cSocialBand: 0x20c bytes.  It has no user-declared constructor, so the game constructs it in
// place with the plain Init / CopyInit / Assign members and cSocialBandEntry stays trivial.
// ---------------------------------------------------------------------------
struct cSocialBand {
    void** mpVTable;                                                         // +0x000
    void* mpField04;                                                         // +0x004
    RefCounted* mpField08;                                                   // +0x008
    RefCounted* mpField0c;                                                   // +0x00c
    uint32_t mField10;                                                       // +0x010 (Init leaves 0x10..0x30 untouched)
    uint32_t mField14;                                                       // +0x014
    uint32_t mField18;                                                       // +0x018
    uint32_t mField1c;                                                       // +0x01c
    uint32_t mField20;                                                       // +0x020
    uint32_t mField24;                                                       // +0x024
    uint32_t mField28;                                                       // +0x028
    uint32_t mField2c;                                                       // +0x02c
    uint32_t mField30;                                                       // +0x030
    float mField34;                                                          // +0x034
    float mField38;                                                          // +0x038
    float mField3c;                                                          // +0x03c
    float mField40;                                                          // +0x040
    uint32_t mField44;                                                       // +0x044
    uint32_t mField48;                                                       // +0x048
    float mField4c;                                                          // +0x04c
    uint8_t mField50;                                                        // +0x050
    uint8_t mField51;                                                        // +0x051
    uint8_t mField52;                                                        // +0x052
    uint8_t mPad53;                                                          // +0x053
    float mField54;                                                          // +0x054
    uint8_t mField58;                                                        // +0x058
    uint8_t mPad59[3];                                                       // +0x059
    float mField5c;                                                          // +0x05c
    uint32_t mField60;                                                       // +0x060
    VecA mVecA;                                                              // +0x064
    VecB mVecB;                                                              // +0x078
    uint32_t mField88;                                                       // +0x088
    VecC mVecC;                                                              // +0x08c
    RefCounted* mpFieldE4;                                                   // +0x0e4
    RefCounted* mpFieldE8;                                                   // +0x0e8
    uint32_t mFieldEc;                                                       // +0x0ec
    uint32_t mFieldF0;                                                       // +0x0f0
    VecD mVecD;                                                              // +0x0f4
    VecE mVecE;                                                              // +0x150
    cActionCircle mActionCircle;                                             // +0x178
    int32_t mField1dc;                                                       // +0x1dc
    uint32_t mField1e0;                                                      // +0x1e0
    VecF mVecF;                                                              // +0x1e4

    cSocialBand* Init();                                                     // 0x00da4f00 (default ctor)
    cSocialBand* CopyInit(const cSocialBand* pSrc);                          // 0x00da52e0 (copy ctor)
    cSocialBand* Assign(const cSocialBand* pSrc);                            // 0x00da5030 (operator=)
};

// vtable slot 0 of the band's vtable, invoked with a 0 tag: the pool's slot destructor.
inline void BandRelease(cSocialBand* pBand)
{
    ((void(__thiscall*)(void*, int))pBand->mpVTable[0])(pBand, 0);
}

// ---------------------------------------------------------------------------
// cSocialBandEntry (0x210 bytes): one pool slot, an ownership tag plus a cSocialBand.
// bit 31 of mSlotInfo set  => the slot is empty / owns nothing.
// bit 31 of mSlotInfo clear => the slot owns a live mBand.
// ---------------------------------------------------------------------------
struct cSocialBandEntry {
    union {
        uint32_t mSlotInfo;                                                  // +0x000 the whole word
        struct {
            uint32_t mSlotIndex : 31;                                        // bits 0..30
            uint32_t mIsEmpty   : 1;                                         // bit 31
        };
    };
    cSocialBand mBand;                                                       // +0x004
    cSocialBandEntry* Assign(const cSocialBandEntry& rhs);                   // 0x00da5550
};

void* FUN_00da55c0(cSocialBandEntry* pFirst, cSocialBandEntry* pLast, cSocialBandEntry* pDest); // 0x00da55c0
void  FUN_00da5620(cSocialBandEntry* pSrcBegin, cSocialBandEntry* pSrcEnd, cSocialBandEntry* pDestEnd); // 0x00da5620
void  FUN_00d9b7f0(cSocialBandEntry* pFirst, cSocialBandEntry* pLast, cSocialBandEntry* pDest);  // 0x00d9b7f0

void* EAAlloc(int nSize, const char* pTag, int n0, int n1, const char* pFile, int nLine); // 0x00f473a0
void  EAFree(void* p);                                                       // 0x00f47380

struct cSocialBandPool {
    cSocialBandEntry* mpBegin;                                               // +0x00
    cSocialBandEntry* mpEnd;                                                 // +0x04
    cSocialBandEntry* mpCap;                                                 // +0x08

    void Reserve(uint n);                                                    // 0x00da5660
    void Insert(cSocialBandEntry* pPos, cSocialBandEntry* pValue);           // 0x00da5720
    void DoInsertEntry();                                                    // 0x00da58a0
};

// ===========================================================================
// 0x00da4f00 — cSocialBand default construction
// ===========================================================================
// @ 0x00da4f00
cSocialBand* cSocialBand::Init()
{
    mpVTable = (void**)0x0147c1e0;
    mpField04 = 0;
    mpField08 = 0;
    mpField0c = 0;
    mField34 = 0.0f;
    mField38 = 0.0f;
    mField3c = 0.0f;
    mField40 = 0.0f;
    mField44 = 0;
    mField48 = 0;
    mField4c = 0.0f;
    mField50 = 0;
    mField51 = 0;
    mField52 = 0;
    mField54 = 0.0f;
    mField58 = 0;
    mField5c = 0.0f;
    mField60 = 0;
    mVecA.mpBegin = 0;
    mVecA.mpEnd = 0;
    mVecA.mpCap = 0;
    mVecB.mpBegin = 0;
    mVecB.mpEnd = 0;
    mVecB.mpCap = 0;

    uint8_t* pBufC = mVecC.mBuf;
    mVecC.mpBufPtr = pBufC;
    mVecC.mpEnd = pBufC;
    mVecC.mpBegin = pBufC;
    mVecC.mpCap = pBufC + 0x40;

    mpFieldE4 = 0;
    mpFieldE8 = 0;
    mFieldF0 = 0;

    uint8_t* pBufD = mVecD.mBuf;
    mVecD.mpEnd = pBufD;
    mVecD.mpBegin = pBufD;
    mVecD.mpCap = pBufD + 0x48;
    mVecD.InitFixed(6);

    uint8_t* pBufE = mVecE.mBuf;
    mVecE.mpEnd = pBufE;
    mVecE.mpBegin = pBufE;
    mVecE.mpCap = pBufE + 0x14;
    mVecE.InitFixed(5);

    mActionCircle.Init();

    mField1e0 = 0;
    mField1dc = -1;
    uint8_t* pBufF = mVecF.mBuf;
    mVecF.mpBufPtr = pBufF;
    mVecF.mpEnd = pBufF;
    mVecF.mpBegin = pBufF;
    mVecF.mpCap = pBufF + 0x10;

    return this;
}

// ===========================================================================
// 0x00da52e0 — cSocialBand copy construction
// ===========================================================================
// @ 0x00da52e0
cSocialBand* cSocialBand::CopyInit(const cSocialBand* pSrc)
{
    mpVTable = (void**)0x0147c1e0;
    mpField04 = pSrc->mpField04;
    mpField08 = pSrc->mpField08;
    if (mpField08)
        mpField08->AddRef();
    mpField0c = pSrc->mpField0c;
    if (mpField0c)
        mpField0c->AddRef();

    mField10 = pSrc->mField10;
    mField14 = pSrc->mField14;
    mField18 = pSrc->mField18;
    mField1c = pSrc->mField1c;
    mField20 = pSrc->mField20;
    mField24 = pSrc->mField24;
    mField28 = pSrc->mField28;
    mField2c = pSrc->mField2c;
    mField30 = pSrc->mField30;
    mField34 = pSrc->mField34;
    mField38 = pSrc->mField38;
    mField3c = pSrc->mField3c;
    mField40 = pSrc->mField40;
    mField44 = pSrc->mField44;
    mField48 = pSrc->mField48;
    mField4c = pSrc->mField4c;
    mField50 = pSrc->mField50;
    mField51 = pSrc->mField51;
    mField52 = pSrc->mField52;
    mField54 = pSrc->mField54;
    mField58 = pSrc->mField58;
    mField5c = pSrc->mField5c;
    mField60 = pSrc->mField60;

    int nA = (int)((uint8_t*)pSrc->mVecA.mpEnd - (uint8_t*)pSrc->mVecA.mpBegin) / 4;
    mVecA.InitBuffer(nA, (void*)&pSrc->mVecA.mpField70);
    void* pEndA = 0;
    FUN_00829110(&pEndA, pSrc->mVecA.mpBegin, pSrc->mVecA.mpEnd, mVecA.mpBegin, (void*)pSrc);
    mVecA.mpEnd = pEndA;

    int nB = (int)((uint8_t*)pSrc->mVecB.mpEnd - (uint8_t*)pSrc->mVecB.mpBegin) / 4;
    mVecB.InitBuffer(nB, (void*)&pSrc->mVecB.mpField84);
    void* pEndB = 0;
    FUN_00829110(&pEndB, pSrc->mVecB.mpBegin, pSrc->mVecB.mpEnd, mVecB.mpBegin, (void*)pSrc);
    mVecB.mpEnd = pEndB;

    uint8_t* pBufC = mVecC.mBuf;
    mVecC.mpBufPtr = pBufC;
    mVecC.mpEnd = pBufC;
    mVecC.mpBegin = pBufC;
    mVecC.mpCap = pBufC + 0x40;
    mVecC.Assign(pSrc->mVecC.mpBegin, pSrc->mVecC.mpEnd, (void*)pSrc);

    mpFieldE4 = pSrc->mpFieldE4;
    if (mpFieldE4)
        mpFieldE4->AddRef();
    mpFieldE8 = pSrc->mpFieldE8;
    if (mpFieldE8)
        mpFieldE8->AddRef();
    mFieldEc = pSrc->mFieldEc;
    mFieldF0 = pSrc->mFieldF0;

    uint8_t* pBufD = mVecD.mBuf;
    mVecD.mpEnd = pBufD;
    mVecD.mpBegin = pBufD;
    mVecD.mpCap = pBufD + 0x48;
    mVecD.Assign(pSrc->mVecD.mpBegin, pSrc->mVecD.mpEnd, (void*)pSrc);

    uint8_t* pBufE = mVecE.mBuf;
    mVecE.mpEnd = pBufE;
    mVecE.mpBegin = pBufE;
    mVecE.mpCap = pBufE + 0x14;
    mVecE.Assign(pSrc->mVecE.mpBegin, pSrc->mVecE.mpEnd, (void*)pSrc);

    mActionCircle.CopyInit(&pSrc->mActionCircle);

    mField1dc = pSrc->mField1dc;
    mField1e0 = pSrc->mField1e0;

    uint8_t* pBufF = mVecF.mBuf;
    mVecF.mpBufPtr = pBufF;
    mVecF.mpEnd = pBufF;
    mVecF.mpBegin = pBufF;
    mVecF.mpCap = pBufF + 0x10;
    mVecF.Assign(pSrc->mVecF.mpBegin, pSrc->mVecF.mpEnd, (void*)pSrc);

    return this;
}

// ===========================================================================
// 0x00da5030 — cSocialBand assignment
// ===========================================================================
// @ 0x00da5030
cSocialBand* cSocialBand::Assign(const cSocialBand* pSrc)
{
    mpField04 = pSrc->mpField04;

    if (mpField08 != pSrc->mpField08) {
        if (pSrc->mpField08)
            pSrc->mpField08->AddRef();
        RefCounted* pOld = mpField08;
        mpField08 = pSrc->mpField08;
        if (pOld)
            pOld->Release();
    }
    if (mpField0c != pSrc->mpField0c) {
        if (pSrc->mpField0c)
            pSrc->mpField0c->AddRef();
        RefCounted* pOld = mpField0c;
        mpField0c = pSrc->mpField0c;
        if (pOld)
            pOld->Release();
    }

    mField10 = pSrc->mField10;
    mField14 = pSrc->mField14;
    mField18 = pSrc->mField18;
    mField1c = pSrc->mField1c;
    mField20 = pSrc->mField20;
    mField24 = pSrc->mField24;
    mField28 = pSrc->mField28;
    mField2c = pSrc->mField2c;
    mField30 = pSrc->mField30;
    mField34 = pSrc->mField34;
    mField38 = pSrc->mField38;
    mField3c = pSrc->mField3c;
    mField40 = pSrc->mField40;
    mField44 = pSrc->mField44;
    mField48 = pSrc->mField48;
    mField4c = pSrc->mField4c;
    mField50 = pSrc->mField50;
    mField51 = pSrc->mField51;
    mField52 = pSrc->mField52;
    mField54 = pSrc->mField54;
    mField58 = pSrc->mField58;
    mField5c = pSrc->mField5c;
    mField60 = pSrc->mField60;

    mVecA.Assign(&pSrc->mVecA);
    mVecB.Assign(&pSrc->mVecB);

    if (&mVecC != &pSrc->mVecC) {
        mVecC.Erase(mVecC.mpBegin, mVecC.mpEnd);
        mVecC.Assign(pSrc->mVecC.mpBegin, pSrc->mVecC.mpEnd, (void*)pSrc);
    }

    if (mpFieldE4 != pSrc->mpFieldE4) {
        if (pSrc->mpFieldE4)
            pSrc->mpFieldE4->AddRef();
        RefCounted* pOld = mpFieldE4;
        mpFieldE4 = pSrc->mpFieldE4;
        if (pOld)
            pOld->Release();
    }
    if (mpFieldE8 != pSrc->mpFieldE8) {
        if (pSrc->mpFieldE8)
            pSrc->mpFieldE8->AddRef();
        RefCounted* pOld = mpFieldE8;
        mpFieldE8 = pSrc->mpFieldE8;
        if (pOld)
            pOld->Release();
    }
    mFieldEc = pSrc->mFieldEc;
    mFieldF0 = pSrc->mFieldF0;

    if (&mVecD != &pSrc->mVecD) {
        mVecD.Erase(mVecD.mpBegin, mVecD.mpEnd);
        mVecD.Assign(pSrc->mVecD.mpBegin, pSrc->mVecD.mpEnd, (void*)pSrc);
    }
    if (&mVecE != &pSrc->mVecE) {
        memcpy(mVecE.mpBegin, mVecE.mpEnd, 0);
        mVecE.mpEnd = (uint8_t*)mVecE.mpEnd + ((int)((uint8_t*)mVecE.mpEnd - (uint8_t*)mVecE.mpBegin) >> 2) * -4;
        mVecE.Assign(pSrc->mVecE.mpBegin, pSrc->mVecE.mpEnd, mVecE.mpBegin);
    }

    mActionCircle.Assign(&pSrc->mActionCircle);

    mField1dc = pSrc->mField1dc;
    mField1e0 = pSrc->mField1e0;

    if (&mVecF != &pSrc->mVecF) {
        memcpy(mVecF.mpBegin, mVecF.mpEnd, 0);
        mVecF.mpEnd = (uint8_t*)mVecF.mpEnd + ((int)((uint8_t*)mVecF.mpEnd - (uint8_t*)mVecF.mpBegin) >> 2) * -4;
        mVecF.Assign(pSrc->mVecF.mpBegin, pSrc->mVecF.mpEnd, mVecF.mpBegin);
    }

    return this;
}

// ===========================================================================
// 0x00da5550 — cSocialBandEntry assignment
// ===========================================================================
// @ 0x00da5550
cSocialBandEntry* cSocialBandEntry::Assign(const cSocialBandEntry& rhs)
{
    if (!rhs.mIsEmpty) {
        if (mIsEmpty) {
            if (&mBand)
                mBand.CopyInit(&rhs.mBand);
        } else {
            mBand.Assign(&rhs.mBand);
        }
    } else {
        if (!mIsEmpty)
            BandRelease(&mBand);
    }
    mSlotInfo = rhs.mSlotInfo;
    return this;
}

// ===========================================================================
// 0x00da55c0 — copy a range of entries into uninitialised storage, returns the new end
// ===========================================================================
// @ 0x00da55c0
void* FUN_00da55c0(cSocialBandEntry* pFirst, cSocialBandEntry* pLast, cSocialBandEntry* pDest)
{
    while (pFirst != pLast) {
        if (pDest) {
            pDest->mSlotInfo = pFirst->mSlotInfo;
            if (!pFirst->mIsEmpty)
                pDest->mBand.CopyInit(&pFirst->mBand);
        }
        pFirst = (cSocialBandEntry*)((uint8_t*)pFirst + 0x210);
        pDest = (cSocialBandEntry*)((uint8_t*)pDest + 0x210);
    }
    return pDest;
}

// ===========================================================================
// 0x00da5660 — cSocialBandPool::Reserve
// ===========================================================================
// @ 0x00da5660
void cSocialBandPool::Reserve(uint n)
{
    int nCount = (int)((uint8_t*)mpCap - (uint8_t*)mpBegin) / 0x210;
    if ((uint)nCount < n) {
        cSocialBandEntry* pNew = 0;
        if (n != 0)
            pNew = (cSocialBandEntry*)EAAlloc((int)(n * 0x210), "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        cSocialBandEntry* pOldBegin = mpBegin;
        cSocialBandEntry* pOldEnd = mpEnd;
        FUN_00da55c0(pOldBegin, pOldEnd, pNew);
        FUN_00d9b7f0(pOldBegin, pOldEnd, pNew);
        if (mpBegin)
            EAFree(mpBegin);
        int nOld = (int)((uint8_t*)pOldEnd - (uint8_t*)pOldBegin) / 0x210;
        mpBegin = pNew;
        mpEnd = (cSocialBandEntry*)((uint8_t*)pNew + nOld * 0x210);
        mpCap = (cSocialBandEntry*)((uint8_t*)pNew + n * 0x210);
    }
}

// ===========================================================================
// 0x00da5720 — cSocialBandPool::Insert(pos, value)
// ===========================================================================
// @ 0x00da5720
void cSocialBandPool::Insert(cSocialBandEntry* pPos, cSocialBandEntry* pValue)
{
    cSocialBandEntry* pEnd = mpEnd;
    if (pEnd != mpCap) {
        cSocialBandEntry* pSrc = pValue;
        if (!(pValue < pPos) && !(pValue >= pEnd))
            pSrc = (cSocialBandEntry*)((uint8_t*)pValue + 0x210);

        if (pEnd) {
            cSocialBandEntry* pPrev = (cSocialBandEntry*)((uint8_t*)pEnd - 0x210);
            pEnd->mSlotInfo = pPrev->mSlotInfo;
            if (!pPrev->mIsEmpty)
                pEnd->mBand.CopyInit(&pPrev->mBand);
        }

        FUN_00da5620(pPos, (cSocialBandEntry*)((uint8_t*)pEnd - 0x210), pEnd);
        pPos->Assign(*pSrc);
        mpEnd = (cSocialBandEntry*)((uint8_t*)pEnd + 0x210);
        return;
    }

    int nCount = (int)((uint8_t*)mpEnd - (uint8_t*)mpBegin) / 0x210;
    int nNew;
    if (nCount == 0)
        nNew = 1;
    else
        nNew = nCount * 2;

    cSocialBandEntry* pNew = 0;
    if (nNew != 0)
        pNew = (cSocialBandEntry*)EAAlloc(nNew * 0x210, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);

    cSocialBandEntry* pOldBegin = mpBegin;
    cSocialBandEntry* pOldEnd = mpEnd;
    cSocialBandEntry* pDest = (cSocialBandEntry*)FUN_00da55c0(pOldBegin, pOldEnd, pNew);
    FUN_00d9b7f0(pOldBegin, pOldEnd, pNew);
    if (pDest) {
        pDest->mSlotInfo = pValue->mSlotInfo;
        if (!pValue->mIsEmpty)
            pDest->mBand.CopyInit(&pValue->mBand);
    }

    cSocialBandEntry* pNewEnd = (cSocialBandEntry*)FUN_00da55c0(pOldEnd, pPos,
        (cSocialBandEntry*)((uint8_t*)pDest + 0x210));
    FUN_00d9b7f0(pOldEnd, pPos, (cSocialBandEntry*)((uint8_t*)pDest + 0x210));
    if (mpBegin)
        EAFree(mpBegin);
    mpBegin = pNew;
    mpEnd = pNewEnd;
    mpCap = (cSocialBandEntry*)((uint8_t*)pNew + nNew * 0x210);
}

// ===========================================================================
// 0x00da58a0 — cSocialBandPool::DoInsertEntry (append a default/free slot)
// ===========================================================================
// @ 0x00da58a0
void cSocialBandPool::DoInsertEntry()
{
    cSocialBandEntry temp;
    cSocialBandEntry* p = mpEnd;
    if (p < mpCap) {
        mpEnd = (cSocialBandEntry*)((uint8_t*)p + 0x210);
        if (p)
            p->mSlotInfo = 0x80000000u;
        return;
    }
    temp.mSlotInfo = 0x80000000u;
    Insert(p, &temp);
    if (!temp.mIsEmpty)
        BandRelease(&temp.mBand);
}

// ===========================================================================
// SP::SOCIAL_PROPOSE_Tick — the brain's social-propose state machine.
// ===========================================================================
struct cTuningObj {
    uint8_t mPad00[8];                                                       // +0x00
    int32_t mField08;                                                        // +0x08
    uint8_t mPad0c[4];                                                       // +0x0c
    int32_t mField10;                                                        // +0x10
    uint8_t mPad14[0x28];                                                    // +0x14
    float mField3c;                                                          // +0x3c
    uint32_t GetAt(uint i);                                                  // 0x004d3cd0
};

struct cSPCreatureBase;

struct StubField {
    bool FUN_00e31a90();                                                     // 0x00e31a90
};

struct cLocomotiveObject {
    uint8_t mData[0x40];                                                     // +0x00
    bool IsNearGoal();                                                       // 0x00c42e20
};

struct cSocialProgressValues {
    float mField00;                                                          // +0x00
    uint8_t mPad04[4];                                                       // +0x04
    int32_t mField08;                                                        // +0x08
    uint8_t mField0c;                                                        // +0x0c
    uint8_t mField0d;                                                        // +0x0d
    uint8_t mPad0e[2];                                                       // +0x0e
    int32_t mField10;                                                        // +0x10
    uint8_t mPad14[0x0c];                                                    // +0x14

    void Update(float dt, int32_t a, cSPCreatureBase* pCreature, cSPCreatureBase* pTarget); // 0x00d9ba60
    bool FUN_00d9b010();                                                     // 0x00d9b010
    void FUN_00d9b040(int32_t v);                                            // 0x00d9b040
    void FUN_00d9b090(float v, int32_t anim);                                // 0x00d9b090
};

struct SocialProposeMemoryBlock {
    uint8_t mPad00[4];                                                       // +0x00
    cSPCreatureBase* mpField04;                                              // +0x04
    int32_t mField08;                                                        // +0x08
    int32_t mField0c;                                                        // +0x0c
    int32_t mField10;                                                        // +0x10
    int32_t mField14;                                                        // +0x14
    cSocialProgressValues mProgress;                                         // +0x18
    StubField* mpField38;                                                    // +0x38
    int32_t mField3c;                                                        // +0x3c
    uint8_t mField40;                                                        // +0x40
    uint8_t mPad41[3];                                                       // +0x41
    float mField44;                                                          // +0x44
    float mField48;                                                          // +0x48
    int32_t mField4c;                                                        // +0x4c
    int32_t mField50;                                                        // +0x50
    int32_t mField54;                                                        // +0x54
    uint32_t mField58;                                                       // +0x58

    int32_t RewardPlayer(cSPCreatureBase* pCreature, cSPCreatureBase* pTarget);  // 0x00d9bc70
    void FUN_00d9b230(cSPCreatureBase* pCreature, void* pBlock, int32_t anim);   // 0x00d9b230
    void FUN_00d9b110(cSPCreatureBase* pCreature);                               // 0x00d9b110
    int32_t SocialRespond_Activate(cSPCreatureBase* pCreature, int32_t prev);     // 0x00da3b90
};

struct cSocialProposeBrain {
    uint8_t mPad000[0x1a4];                                                  // +0x00
    SocialProposeMemoryBlock mPropose;                                       // +0x1a4
    bool ShouldSkip();                                                       // 0x00a75010
};

struct BehaviorStimuli {
    void* Play(int flags, int a);                                            // 0x00bc96a0
    void  ClearAll(int flags, int a);                                        // 0x00bc98f0
};

struct cSPCreatureBase {
    void** mpVTable;                                                         // +0x000
    uint8_t mPad004[0xc0 - 4];                                               // +0x004
    cLocomotiveObject mLoco;                                                 // +0x0c0
    uint8_t mPad100[0xb4c - 0x100];                                          // +0x100
    void* mpFieldb4c;                                                        // +0xb4c
    uint8_t mPadb50[0xb5c - 0xb50];                                          // +0xb50
    uint8_t mFieldb5c;                                                       // +0xb5c
    uint8_t mPadb5d[0x1020 - 0xb5d];                                         // +0xb5d
    void** mpField1020;                                                      // +0x1020

    int32_t PlayAnimation(int32_t anim, int a, int b);                       // 0x00c12190
    int32_t InterruptAnimation(int32_t anim, int a, int b);                  // 0x00c12310
    bool    AnimationFinished(int32_t h);                                    // 0x00c12400
    void*   GetTargetAsCreature();                                           // 0x00c0ee70
    bool    CCM_e0c0(int32_t id);                                            // 0x00c0e0c0
};

struct SocialProposeState {
    int32_t mState;                                                          // +0x00
    int32_t mAnimHandle;                                                     // +0x04
    uint8_t mFlag8;                                                          // +0x08
    uint8_t mPad9[3];                                                        // +0x09
    int32_t mField0c;                                                        // +0x0c
};

int32_t FUN_00d99470(cSPCreatureBase* p);                                    // 0x00d99470

// @ 0x00da49f0
uint SP_SOCIAL_PROPOSE_Tick(cSPCreatureBase* pCreature, int, int, int, int,
                            SocialProposeState* pState, int, float dt)
{
    void* pBrain = *(void**)((uint8_t*)pCreature + 0xb4c);
    cSocialProposeBrain* pB = (cSocialProposeBrain*)(*(void**)((uint8_t*)pBrain + 0x600));
    (void)pBrain;
    SocialProposeMemoryBlock* pMem = &pB->mPropose;

    if (pB->ShouldSkip())
        return 0;

    if (pState->mFlag8 != 0) {
        if (FUN_00d99470(pMem->mpField04) == 0)
            return 0;
        cSPCreatureBase* pTgt = (cSPCreatureBase*)pMem->mpField04->GetTargetAsCreature();
        if (pTgt != pCreature)
            return 0;
        if (*(int32_t*)((uint8_t*)pMem->mpField04->mpFieldb4c + 0x1d8) != (int32_t)0x941bd4bf)
            return 0;
        pMem->mProgress.Update(dt, pMem->mField3c, pCreature, pMem->mpField04);
        if (pMem->mpField38->FUN_00e31a90() && pState->mState != 8) {
            int32_t anim = pMem->RewardPlayer(pCreature, pMem->mpField04);
            if (anim != -1) {
                pState->mAnimHandle = pCreature->PlayAnimation(anim, 1, -1);
                pMem->FUN_00d9b230(pCreature, (void*)pB, anim);
            }
            pState->mState = 8;
        }
    }

    if ((uint)pState->mState > 8)
        return 1;

    switch (pState->mState) {
    case 0: {
        if (pCreature->mLoco.IsNearGoal()) {
            if (pState->mFlag8 != 0) {
                if (pMem->mField50 > 0) {
                    pMem->mField48 = 10.0f;                              // [0x01582f28] = 10.0f
                    pState->mAnimHandle = pCreature->InterruptAnimation(0x61e0673, -1, 0);
                    pState->mState = 2;
                } else {
                    pState->mState = 4;
                }
            } else {
                if (pState->mField0c != -1 && pMem->mField4c < pMem->mField50) {
                    pCreature->mFieldb5c = 1;
                    pMem->mField4c++;
                    pState->mState = 5;
                } else {
                    pCreature->mFieldb5c = 1;
                }
            }
        }
        if (pState->mFlag8 == 0)
            pState->mField0c = pMem->SocialRespond_Activate(pCreature, pState->mField0c);
        return 1;
    }
    case 1:
        return 1;
    case 2:
        pMem->mField48 = pMem->mField48 - dt;
        if (pCreature->AnimationFinished(pState->mAnimHandle)) {
            pCreature->PlayAnimation(0x61e0674, 1, -1);
            pState->mState = 3;
        }
        return 1;
    case 3:
        pMem->mField48 = pMem->mField48 - dt;
        if (!(0.0f > pMem->mField48) && pMem->mField4c != pMem->mField50)
            return 1;
        pMem->mProgress.mField00 = (float)(uint)(pMem->mField4c + 1) * pMem->mProgress.mField00;
        pMem->mField58 |= 0x20;
        pMem->mField54 = pMem->mField4c;
        pState->mState = 4;
        return 1;
    case 4: {
        if ((uint)pMem->mField0c < (uint)pMem->mField08) {
            void* pElem = pCreature->mpField1020[pMem->mField0c];
            void** pVtbl = pCreature->mpVTable;
            cTuningObj* pTune = (cTuningObj*)((void*(__thiscall*)(void*, void*))pVtbl[0xb4 / 4])(pCreature, pElem);
            uint32_t v = pTune->GetAt(0);
            pState->mAnimHandle = pCreature->InterruptAnimation((int32_t)v, -1, 0);
            pMem->mProgress.FUN_00d9b090((float)(uint)(pMem->mField54 + 1) * pTune->mField3c, pState->mAnimHandle);
            pMem->mField10 = pTune->mField08;
            pMem->mField14 = pTune->mField10;
            pState->mState = 6;
            pMem->mField58 &= 0xfffffff0u;
            pMem->mField40 = 1;
            pMem->FUN_00d9b230(pCreature, (void*)pB, (int32_t)v);
            return 1;
        }
        if (pMem->mProgress.FUN_00d9b010())
            return 1;
        pMem->mProgress.FUN_00d9b040(1);
        pState->mAnimHandle = pCreature->PlayAnimation(0x53685d8f, 1, -1);
        pMem->FUN_00d9b230(pCreature, (void*)pB, 0x53685d8f);
        pState->mState = 8;
        return 1;
    }
    case 5: {
        BehaviorStimuli* pStim = (BehaviorStimuli*)((uint8_t*)*(void**)((uint8_t*)pCreature + 0xb4c) + 8);
        void* pR = pStim->Play(0x10000000, 0);
        if (pR && *(int32_t*)((uint8_t*)pR + 0xc) == 3)
            pCreature->InterruptAnimation(*(int32_t*)((uint8_t*)pR + 0x10), -1, 0);
        pStim->ClearAll(0x10000000, 0);
        return 1;
    }
    case 6: {
        uint32_t flags = pMem->mField58;
        if (!(flags & 2)) {
            if (flags & 1) {
                pMem->mField44 = pMem->mField44 - dt;
                if (pMem->mField44 <= 0.0f)
                    return 0;
            }
        }
        if (!(flags & 1)) {
            if (pCreature->AnimationFinished(pState->mAnimHandle)) {
                pMem->mField58 |= 1;
                pState->mAnimHandle = pCreature->PlayAnimation(0x61e0675, 1, -1);
                pMem->FUN_00d9b230(pCreature, (void*)pB, 0x61e0675);
                if (!(pMem->mField58 & 2))
                    pMem->mField44 = 10.0f;                              // [0x01582f20] = 10.0f
            }
        }
        flags = pMem->mField58;
        if ((flags & 1) && !(flags & 2)) {
            if (!pMem->mProgress.FUN_00d9b010()
                && pMem->mProgress.mField0d == 0
                && pMem->mProgress.mField0c == 0) {
                pMem->mProgress.mField08 = pMem->mProgress.mField10;
                pMem->mProgress.mField0c = 1;
            }
        }
        if (pMem->mProgress.mField0d != 0) {
            if (!pCreature->CCM_e0c0(0x61e0670)) {
                pState->mAnimHandle = pCreature->PlayAnimation(0x61e0670, 1, -1);
                pMem->FUN_00d9b230(pCreature, (void*)pB, 0x61e0670);
            }
        }
        pMem->FUN_00d9b110(pCreature);
        flags = pMem->mField58;
        if (!(flags & 1))
            return 1;
        if (!(flags & 4))
            return 1;
        if (pMem->mProgress.FUN_00d9b010())
            return 1;
        pMem->mField0c++;
        if (pMem->mField58 & 8) {
            pState->mState = 4;
            return 1;
        }
        pState->mAnimHandle = pCreature->PlayAnimation(0x68d8f9c, 1, -1);
        pState->mState = 7;
        pMem->FUN_00d9b230(pCreature, (void*)pB, 0x68d8f9c);
        return 1;
    }
    case 7:
        if (pCreature->AnimationFinished(pState->mAnimHandle)) {
            pState->mAnimHandle = 0;
            pState->mState = 4;
        }
        return 1;
    default:
        if (pCreature->AnimationFinished(pState->mAnimHandle))
            return 0;
        return 1;
    }
}