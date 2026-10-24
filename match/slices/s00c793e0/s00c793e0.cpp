// =============================================================================================
// SporeApp.exe slice s00c793e0  (batch gold6, worker 0)
//
// Nine routines hanging off the Simulator::cPlayer object whose state lists live at
//   +0x1184, +0x1198, +0x11ac   SPVector<unsigned int> member lists
//   +0x1214                     eastl::vector<pair<unsigned int, SP::cGonzagoTimer>>
//   +0x1228 rbtree, +0x698 / +0x111c hashtables, +0x38 / +0x113c / +0x11c0 lists
// plus the ban-mode pick-priority helper (00c79e20, SP::cCityInputStrategy).
// =============================================================================================
#include "types.h"

// ---------------------------------------------------------------------------------------------
// image data
// ---------------------------------------------------------------------------------------------
extern void* g_vtbl_01472d48;       // 0x01472d48  Simulator::cPlayer vtable (+0x00)
extern void* g_vtbl_01472d34;       // 0x01472d34  Simulator::cPlayer interface vtable (+0x04)
extern void* g_vtbl_01472d24;       // 0x01472d24  Simulator::cPlayer interface vtable (+0x34)
extern void* g_vtbl_013eb394;       // 0x013eb394  ??_7PaintSystem@@6B@ (+0x34, base dtor)
extern uint8_t g_gameModeEntry;     // 0x01654c02  game-mode table entry (DAT_01654c02)
extern wchar_t g_wstrEmpty[];       // 0x013f6254  shared empty wstring buffer
extern wchar_t g_wstrBool[];        // 0x013f58a0  L"bool"
extern char g_szSimulator[];        // 0x013f09b4  "Simulator"
extern char g_szAllocatorH[];       // 0x013ebb38  "...EASTL/allocator.h"

// ---------------------------------------------------------------------------------------------
// external routines
// ---------------------------------------------------------------------------------------------
void   __cdecl operator_delete_array(void* pBlock);             // 0x00f47380
void*  __cdecl operator_new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                            const char* pFile, int32_t nLine);  // 0x00f473a0
void*  __cdecl FUN_00c771e0(void* pLast, void* pEnd, void* pFirst);            // 0x00c771e0 eastl copy_impl::do_copy
void*  __cdecl FUN_00c75b60(void* pDst, uint32_t n, void* pValue, void* pPos); // 0x00c75b60 eastl uninitialized_fill_n
void*  __cdecl FUN_00c76740(void* pDst, void* pSrc, uint32_t nBytes);          // 0x00c76740 eastl uninitialized_move
void   __cdecl FUN_00b184c0();                                                 // 0x00b184c0 SP::cGameData::~cGameData
uint32_t __cdecl FUN_00c227e0();                                               // 0x00c227e0 get the ban-pick mode
void   __cdecl FUN_00c227d0(uint32_t nMode);                                   // 0x00c227d0 set the ban-pick mode
void*  __cdecl FUN_00b3d2a0(void* pAvatar);                                    // 0x00b3d2a0 SP::StarManager
void   __cdecl FUN_00ba5bc0(void* pEmpire, uint32_t nArg);                     // 0x00ba5bc0
void*  __cdecl SP_GetCurrentGameMode();                                         // 0x00b5b800
void*  __cdecl SP_NounManager();                                                // 0x00b3d300
void*  __cdecl SP_SpaceGameGet();                                               // 0x01002bd0
void*  __cdecl SP_MessageServer();                                              // 0x0067dcc0
uint32_t __cdecl SP_GetPlayerEmpireOrMinus1();                                  // 0x00b1f9d0
uint32_t __cdecl SP_GetPlayerEmpireID();                                        // 0x01021090

// eastl::basic_string<wchar_t> helpers
void*  __cdecl EA_ConvertToString16(void* pOut, const char* pStr, int32_t nLen);  // 0x0093c5a0
bool   __cdecl WriteTypedValue(void* pStream, int32_t nA, void* pElem, const wchar_t* pType);  // 0x0057c940

// ---------------------------------------------------------------------------------------------
// small shared types
// ---------------------------------------------------------------------------------------------
class cGonzagoTimer {
public:
    uint64_t mPad00[4];                         // +0x00, 0x20 bytes, 8-byte aligned
    ~cGonzagoTimer();                           // 0x00b638b0
};

// eastl::pair<unsigned int, SP::cGonzagoTimer> - element of the +0x1214 list, 0x28 bytes wide
struct tPair28 {
    uint32_t      mKey;                         // +0x00
    cGonzagoTimer mTimer;                       // +0x08
};

// eastl::vector<pair<unsigned int, cGonzagoTimer>> (three pointers)
class tPairVec {
public:
    tPair28* mpBegin;                           // +0x00
    tPair28* mpEnd;                             // +0x04
    tPair28* mpCap;                             // +0x08
    tPair28* erase(tPair28* pFirst, tPair28* pLast);    // 0x00c798a0
};

// SPVector<unsigned int>
class tUintVec {
public:
    uint32_t* mpBegin;                          // +0x00
    uint32_t* mpEnd;                            // +0x04
    uint32_t* mpCap;                            // +0x08
    uint32_t  mnAlloc;                          // +0x0c
    uint32_t* insert(uint32_t* pPos, uint32_t n, const uint32_t& rValue);  // 0x00c79900
    void      DoInsertValue(uint32_t* pPos, const uint32_t& rValue);       // 0x004558a0
};

// eastl::vector<EA::AutoRefCount<T>> - element is one refcounted pointer
struct tAutoRef {
    void* mpObj;                                // +0x00
};

class tRefVec {
public:
    tAutoRef* mpBegin;                          // +0x00
    tAutoRef* mpEnd;                            // +0x04
    tAutoRef* mpCap;                            // +0x08
    void insert(tAutoRef* pPos, uint32_t n, tAutoRef* pValue);    // 0x00c795f0
};

// a reference counted object we only ever touch through slots 0x00 / 0x04
class cRefObj {
public:
    virtual int AddRef();                       // +0x00
    virtual int Release();                      // +0x04
};

// the object reached through cPlayerInner::mn70 (cSPGameDataUFO-ish)
class cPlayerInner {
public:
    void** mpVtbl00;                            // +0x00
    uint8_t mPad04[0x70 - 0x04];
    uint32_t mn70;                              // +0x70  the handle stored in the state lists
    int  FUN_00bb9ae0();                        // 0x00bb9ae0
    bool FUN_00bb9bd0();                        // 0x00bb9bd0
    bool FUN_00bb9c00();                        // 0x00bb9c00
    void FUN_00bb9bb0(uint32_t nArg);           // 0x00bb9bb0
    void FUN_00bb9be0(uint32_t nArg);           // 0x00bb9be0
    void FUN_00bb9b00(uint32_t nA, uint32_t nB); // 0x00bb9b00
    void* GetAvatar();                          // 0x00b1fdb0 SP::cGameNounManager::GetAvatar
    int  AddRef();                              // 0x00801920
};

class cStarManager {
public:
    void* GetEmpireByID();                      // 0x00ba9370
};

class cEmpire {
public:
    uint8_t mPad00[0x84];                       // +0x00
    uint32_t mn84;                              // +0x84
    void FUN_00c322f0(uint32_t nArg);           // 0x00c322f0
    void FUN_00c313a0(uint32_t nArg);           // 0x00c313a0
};

class cMessageServer {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14(uint32_t nKey, uint32_t nA, uint32_t nB);   // +0x14
};

class cNounMgr {
public:
    void** mpVtbl00;                            // +0x00
    void* GetPlayerTribe();                     // 0x00bfc5f0
};

class cTribe {
public:
    void** mpVtbl00;                            // +0x00
    void FUN_00fe5430(uint32_t nA, uint32_t nB); // 0x00fe5430
};

// one 20-byte ban-mode entry inside cPlayer's +0x113c table
class cBanModeEntry {
public:
    void FUN_00db5b30(void* pVec);              // 0x00db5b30
};

// the serialisation stream used by 00c793e0
class cSerialStream {
public:
    virtual void v00(const wchar_t* pName);     // +0x00
    virtual void v04(const wchar_t* pName);     // +0x04
};

// eastl::basic_string<wchar_t, eastl::allocator>
class tWString {
public:
    wchar_t* mpBegin;                           // +0x00
    wchar_t* mpEnd;                             // +0x04
    wchar_t* mpCap;                             // +0x08
    void RangeInitialize(uint32_t nCount);                      // 0x00579a90
    tWString() : mpBegin(0), mpEnd(0), mpCap(0) {}              // inlined by cl
    tWString(const tWString& rOther);                           // 0x0056e2d0
    ~tWString() {
        if (mpCap - mpBegin > 1 && mpBegin != 0)
            operator_delete_array(mpBegin);
    }
};

// ---------------------------------------------------------------------------------------------
// container members of cPlayer (each is a thiscall anchor for the free helpers)
// ---------------------------------------------------------------------------------------------
class cPool38 {                                 // cPlayer+0x38, pool freed by 0x00a42fe0
public:
    uint8_t   mPad00[4];
    uint32_t* mpPool;                           // +0x04 (cPlayer+0x03c)
    uint32_t  mnCount;                          // +0x08 (cPlayer+0x040)
    uint32_t  mnNext;                           // +0x0c (cPlayer+0x044)
    uint8_t   mPad10[8];
    uint32_t* mpFreeHead;                       // +0x18 (cPlayer+0x054)
    uint8_t   mPad1c[8];
    uint32_t* mpPoolBegin;                      // +0x24 (cPlayer+0x05c)
    uint32_t* mpPoolEnd;                        // +0x28 (cPlayer+0x060)
    uint8_t   mPad2c[4];
    uint32_t* mpStatic;                         // +0x30 (cPlayer+0x068)
    void FUN_00a42fe0(void* pPool, uint32_t nCount);   // 0x00a42fe0
};

class cHash69c {                                // cPlayer+0x698, eastl hashtable
public:
    uint8_t   mPad00[4];
    uint32_t* mpBuckets;                        // +0x04 (cPlayer+0x69c)
    uint32_t  mnCount;                          // +0x08 (cPlayer+0x6a0)
    uint32_t  mnNext;                           // +0x0c (cPlayer+0x6a4)
    uint8_t   mPad10[8];
    uint32_t* mpFreeHead;                       // +0x18 (cPlayer+0x6b4)
    uint8_t   mPad1c[8];
    uint32_t* mpPoolBegin;                      // +0x24 (cPlayer+0x6bc)
    uint32_t* mpPoolEnd;                        // +0x28 (cPlayer+0x6c0)
    uint8_t   mPad2c[4];
    uint32_t* mpStatic;                         // +0x30 (cPlayer+0x6c8)
    void DoFreeNodes(uint32_t* pBuckets, uint32_t nCount);   // 0x00a1b6c0
};

class cHash1120 {                               // cPlayer+0x111c, eastl hashtable
public:
    uint8_t   mPad00[4];
    uint32_t* mpBuckets;                        // +0x04 (cPlayer+0x1120)
    uint32_t  mnCount;                          // +0x08 (cPlayer+0x1124)
    uint32_t  mnNext;                           // +0x0c (cPlayer+0x1128)
    void DoFreeNodes(uint32_t* pBuckets, uint32_t nCount);   // 0x006b6570
};

class cBanModeArray {                           // cPlayer+0x113c, 20-byte ban-mode entries
public:
    void*   mpBegin;                            // +0x00 (cPlayer+0x113c)
    void*   mpEnd;                              // +0x04 (cPlayer+0x1140)
    void FUN_00c77ab0(void* pBegin, void* pEnd);   // 0x00c77ab0
};

class cList11c0 {                               // cPlayer+0x11c0, pointer list
public:
    void* mpBegin;                              // +0x00 (cPlayer+0x11c0)
    void* mpEnd;                                // +0x04 (cPlayer+0x11c4)
    void FUN_00c781e0(void* pBegin, void* pEnd);   // 0x00c781e0
};

class cList11f8 {                               // cPlayer+0x11f8, container with a +0x0c head
public:
    uint8_t mPad00[0x0c];
    void*   mpHead;                             // +0x0c (cPlayer+0x1204)
    void FUN_00c77b10(void* pHead);             // 0x00c77b10
};

class cRbTree1228 {                             // cPlayer+0x1228, eastl rbtree
public:
    uint32_t  mUnk00;                           // +0x00
    void*     mpEndNode;                        // +0x04
    void*     mpEndNodeSelf;                    // +0x08
    void*     mpRoot;                           // +0x0c (cPlayer+0x1234)
    uint32_t  mb10;                             // +0x10
    uint32_t  mn14;                             // +0x14
    void DoNukeSubtree(void* pRoot);            // 0x009a9600
};

// ---------------------------------------------------------------------------------------------
// Simulator::cPlayer - the object owning the state lists (only touched members are named)
// ---------------------------------------------------------------------------------------------
class cPlayer {
public:
    void* mpVtbl00;                             // +0x0000
    void* mpVtbl04;                             // +0x0004
    uint8_t mPad08[0x34 - 0x08];
    void* mpVtbl34;                             // +0x0034
    cPool38 mPool38;                            // +0x0038 .. +0x006b
    uint8_t mPad6c[0x698 - 0x6c];
    cHash69c mHash69c;                          // +0x0698 .. +0x06cb
    uint8_t mPad6cc[0x10e8 - 0x6cc];
    void* mpRef10e8;                            // +0x10e8
    uint8_t mPad10ec[0x111c - 0x10ec];
    cHash1120 mHash1120;                        // +0x111c .. +0x112b
    uint8_t mPad112c[0x113c - 0x112c];
    cBanModeArray mBanModeTable;                // +0x113c .. +0x1143
    uint8_t mPad1144[0x1184 - 0x1144];
    tUintVec mVec1184;                          // +0x1184 .. +0x1193
    uint8_t mPad1194[0x1198 - 0x1194];
    tUintVec mVec1198;                          // +0x1198 .. +0x11a7
    uint8_t mPad11a8[0x11ac - 0x11a8];
    tUintVec mVec11ac;                          // +0x11ac .. +0x11bb
    uint8_t mPad11bc[0x11c0 - 0x11bc];
    cList11c0 mList11c0;                        // +0x11c0 .. +0x11c7
    uint8_t mPad11c8[0x11d8 - 0x11c8];
    void* mpBlock11d8;                          // +0x11d8
    uint8_t mPad11dc[0x11f4 - 0x11dc];
    void* mpRef11f4;                            // +0x11f4
    cList11f8 mList11f8;                        // +0x11f8 .. +0x1207
    uint8_t mPad1208[0x1214 - 0x1208];
    tPair28* mpPairBegin1214;                   // +0x1214
    tPair28* mpPairEnd1218;                     // +0x1218
    uint8_t mPad121c[0x1228 - 0x121c];
    cRbTree1228 mRbTree;                        // +0x1228 .. +0x123f
    uint8_t mPad1240c[0x1258 - 0x1240];
    cGonzagoTimer mTimer1258;                   // +0x1258
    uint8_t mPad1278[0x129c - 0x1278];
    void* mpBlock129c;                          // +0x129c
    uint8_t mPad12a0[0x12ac - 0x12a0];
    void* mpBlock12ac;                          // +0x12ac

    bool  FUN_00c772c0(uint32_t nKey);                          // 0x00c772c0
    void  FUN_00c754e0(cPlayerInner* pObj);                     // 0x00c754e0
    void  FUN_00c79f20(cPlayerInner* pObj);                     // 0x00c79f20
    void  FUN_00c79fa0(cPlayerInner* pObj);                     // 0x00c79fa0
    void  FUN_00c7a160(cPlayerInner* pObj);                     // 0x00c7a160
    void  SetBanModePickPriorities(uint32_t nMode, tUintVec* pVec);  // 0x00c79e20
    void  FUN_00c79b60();                                       // 0x00c79b60  destructor body
};

// ---------------------------------------------------------------------------------------------
// 0x00c798a0 - eastl::vector<pair<unsigned, cGonzagoTimer>>::erase(first, last)
// ---------------------------------------------------------------------------------------------
// @ 0x00c798a0 tPairVec::erase
tPair28* tPairVec::erase(tPair28* pFirst, tPair28* pLast)
{
    tPair28* pNewEnd = (tPair28*)FUN_00c771e0(pLast, mpEnd, pFirst);
    tPair28* pEnd = mpEnd;
    while (pNewEnd < pEnd) {
        pNewEnd->mTimer.~cGonzagoTimer();
        ++pNewEnd;
    }
    mpEnd -= pLast - pFirst;
    return pFirst;
}

// ---------------------------------------------------------------------------------------------
// 0x00c79f20 - drop pObj's handle from the +0x1198 list unless it is marked hidden
// ---------------------------------------------------------------------------------------------
// @ 0x00c79f20 cPlayer::FUN_00c79f20
void cPlayer::FUN_00c79f20(cPlayerInner* pObj)
{
    if (pObj == 0)
        return;
    if (pObj->FUN_00bb9c00())
        return;
    pObj->FUN_00bb9be0(1);
    if (!pObj->FUN_00bb9bd0()) {
        tUintVec* pVec = &mVec1198;
        uint32_t v = pObj->mn70;
        if (pVec->mpEnd < pVec->mpCap) {
            uint32_t* p = pVec->mpEnd;
            pVec->mpEnd = p + 1;
            if (p != 0) {
                *p = v;
                FUN_00c754e0(pObj);
                return;
            }
        } else {
            pVec->DoInsertValue(pVec->mpEnd, v);
        }
    }
    FUN_00c754e0(pObj);
}

// ---------------------------------------------------------------------------------------------
// 0x00c7a160 - AddRef pObj; if its handle is not already in the +0x11ac list, append it
// ---------------------------------------------------------------------------------------------
// @ 0x00c7a160 cPlayer::FUN_00c7a160
void cPlayer::FUN_00c7a160(cPlayerInner* pObj)
{
    if (pObj == 0)
        return;
    if (pObj->AddRef() != 2)
        return;

    tUintVec* pVec = &mVec11ac;
    uint32_t* p = pVec->mpBegin;
    uint32_t* pEnd = pVec->mpEnd;
    uint32_t v = pObj->mn70;
    while (p != pEnd && *p != v)
        ++p;
    if (p == pEnd) {
        if (pVec->mpEnd < pVec->mpCap) {
            uint32_t* q = pVec->mpEnd;
            pVec->mpEnd = q + 1;
            if (q != 0) {
                *q = v;
                pObj->FUN_00bb9b00(0x10000, 1);
                return;
            }
        } else {
            pVec->DoInsertValue(pVec->mpEnd, v);
        }
    }
    pObj->FUN_00bb9b00(0x10000, 1);
}

// ---------------------------------------------------------------------------------------------
// 0x00c79fa0 - player refresh: empire resync, then move the handle between the +0x1198 and
//              +0x1184 lists
// ---------------------------------------------------------------------------------------------
// @ 0x00c79fa0 cPlayer::FUN_00c79fa0
void cPlayer::FUN_00c79fa0(cPlayerInner* pObj)
{
    if (pObj == 0)
        return;
    uint32_t v = pObj->mn70;

    if (pObj->FUN_00bb9ae0() == 5) {
        void* pAvatar = pObj->GetAvatar();
        if (pAvatar != (void*)SP_GetPlayerEmpireID()) {
            void* pAvatar2 = pObj->GetAvatar();
            cStarManager* pSM = (cStarManager*)FUN_00b3d2a0(pAvatar2);
            cEmpire* pEmpire = (cEmpire*)pSM->GetEmpireByID();
            if (pEmpire != 0 && !FUN_00c772c0(0x5f1f0ca))
                pEmpire->FUN_00c313a0(1);
        }
    }

    if (pObj->FUN_00bb9bd0())
        return;

    if (pObj->FUN_00bb9c00()) {
        for (uint32_t* p = mVec1198.mpBegin; p != mVec1198.mpEnd; ++p) {
            if (*p == v) {
                *p = mVec1198.mpEnd[-1];
                mVec1198.mpEnd -= 1;
                break;
            }
        }
    }

    if (mVec1184.mpEnd < mVec1184.mpCap) {
        uint32_t* q = mVec1184.mpEnd;
        mVec1184.mpEnd = q + 1;
        if (q != 0)
            *q = v;
    } else {
        mVec1184.DoInsertValue(mVec1184.mpEnd, v);
    }

    pObj->FUN_00bb9bb0(1);
    pObj->FUN_00bb9be0(1);

    if (pObj->FUN_00bb9ae0() == 5) {
        void* pAvatar = pObj->GetAvatar();
        cStarManager* pSM = (cStarManager*)FUN_00b3d2a0(pAvatar);
        cEmpire* pEmpire = (cEmpire*)pSM->GetEmpireByID();
        if (pEmpire != 0)
            pEmpire->FUN_00c322f0(0);
    }

    if (SP_SpaceGameGet() != 0) {
        cNounMgr* pSG = (cNounMgr*)SP_SpaceGameGet();
        if (pSG->GetPlayerTribe() != 0) {
            cNounMgr* pSG2 = (cNounMgr*)SP_SpaceGameGet();
            cTribe* pTribe = (cTribe*)pSG2->GetPlayerTribe();
            pTribe->FUN_00fe5430(2, 1);
        }
    }

    if ((uint32_t)(pObj->AddRef() - 1) <= 2) {
        cMessageServer* pMS = (cMessageServer*)SP_MessageServer();
        pMS->v14(0xf46092d8, 0, 0);
    }

    if (pObj->FUN_00bb9ae0() == 5) {
        void* pAvatar = pObj->GetAvatar();
        cStarManager* pSM = (cStarManager*)FUN_00b3d2a0(pAvatar);
        cEmpire* pEmpire = (cEmpire*)pSM->GetEmpireByID();
        if (pEmpire != 0) {
            uint32_t n84 = pEmpire->mn84;
            SP_NounManager();
            uint32_t nCur = SP_GetPlayerEmpireOrMinus1();
            if (n84 != nCur)
                FUN_00ba5bc0(pEmpire, 0);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c79e20 - SP::cCityInputStrategy::SetBanModePickPriorities
// ---------------------------------------------------------------------------------------------
// @ 0x00c79e20 cPlayer::SetBanModePickPriorities
void cPlayer::SetBanModePickPriorities(uint32_t nMode, tUintVec* pVec)
{
    if (nMode >= 10)
        return;

    cBanModeEntry* pEntry = (cBanModeEntry*)((uint8_t*)mBanModeTable.mpBegin + nMode * 20);
    pEntry->FUN_00db5b30(pVec);

    uint32_t* pBegin = pVec->mpBegin;
    uint32_t* pEnd = pVec->mpEnd;

    if (SP_GetCurrentGameMode() == (void*)&g_gameModeEntry) {
        cNounMgr* pNM = (cNounMgr*)SP_NounManager();
        cTribe* pTribe = (cTribe*)pNM->GetPlayerTribe();
        if (pTribe != 0) {
            tUintVec* pList = ((tUintVec*(__thiscall*)(void*))pTribe->mpVtbl00[0x90 / 4])(pTribe);
            for (uint32_t* p = pList->mpBegin; p != pList->mpEnd; ++p) {
                void* pObj = (void*)*p;
                if (pObj != 0) {
                    void** pVtbl = *(void***)pObj;
                    if (((uint32_t(__thiscall*)(void*, uint32_t))pVtbl[0x0c / 4])(pObj, 0x4f176642) != 0
                        && FUN_00c227e0() == nMode)
                        FUN_00c227d0(0xffffffff);
                }
            }
        }
    }

    for (uint32_t* p = pBegin; p != pEnd; ++p) {
        void* pObj = (void*)*p;
        if (pObj != 0) {
            void** pVtbl = *(void***)pObj;
            if (((uint32_t(__thiscall*)(void*, uint32_t))pVtbl[0xb8 / 4])(pObj, 0x4f176642) != 0)
                FUN_00c227d0(nMode);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c793e0 - serialise a bool array: write the element type name, each element, then close
// ---------------------------------------------------------------------------------------------
// @ 0x00c793e0 FUN_00c793e0
uint8_t FUN_00c793e0(cSerialStream* pStream, const char* pName, tUintVec* pVec)
{
    uint8_t nOk = 1;
    if (pVec->mpBegin == pVec->mpEnd)
        return nOk;

    tWString wTemp;
    if (pName == 0)
        wTemp.RangeInitialize(0);
    else
        EA_ConvertToString16(&wTemp, pName, -1);

    tWString wName(wTemp);

    const wchar_t* pszOpen = (wName.mpBegin == wName.mpEnd) ? g_wstrEmpty : wName.mpBegin;
    pStream->v00(pszOpen);

    for (uint32_t* p = pVec->mpBegin; p != pVec->mpEnd; p += 2)
        nOk = nOk && (WriteTypedValue(pStream, 0, p + 1, g_wstrBool) != 0);

    const wchar_t* pszClose = (wName.mpBegin == wName.mpEnd) ? g_wstrEmpty : wName.mpBegin;
    pStream->v04(pszClose);

    return nOk;
}

// ---------------------------------------------------------------------------------------------
// 0x00c79900 - eastl::vector<unsigned int>::insert(pos, n, value)
// ---------------------------------------------------------------------------------------------
// @ 0x00c79900 tUintVec::insert
uint32_t* tUintVec::insert(uint32_t* pPos, uint32_t n, const uint32_t& rValue)
{
    if ((uint32_t)(mpCap - mpEnd) < n) {
        uint32_t nOld  = (uint32_t)(mpEnd - mpBegin);
        uint32_t nGrow = nOld * 2;
        if (nOld == 0)
            nGrow = 1;
        uint32_t nCap = nOld + n;
        if (nCap < nGrow)
            nCap = nGrow;

        uint32_t* pNew = (nCap == 0)
            ? 0
            : (uint32_t*)operator_new(nCap * 4, g_szSimulator, 0, 0, g_szAllocatorH, 0xd1);

        uint32_t nPrefix = (uint32_t)((uint8_t*)pPos - (uint8_t*)mpBegin);
        uint32_t* pMid = (uint32_t*)FUN_00c76740(pNew, mpBegin, nPrefix);
        uint32_t* pFill = (uint32_t*)((uint8_t*)pMid + nPrefix);

        uint32_t v = rValue;
        for (uint32_t i = 0; i < n; ++i)
            pFill[i] = v;

        uint32_t nTail = (uint32_t)((uint8_t*)mpEnd - (uint8_t*)pPos);
        uint32_t* pNewEnd = (uint32_t*)FUN_00c76740((uint8_t*)pFill + n * 4, pPos, nTail);

        if (mpBegin != 0 && *((int32_t*)mpBegin - 1) != 0)
            operator_delete_array(mpBegin);

        mpBegin = pNew;
        mpEnd   = pNewEnd;
        mpCap   = (uint32_t*)((uint8_t*)pNew + nCap * 4);
    } else if (n != 0) {
        uint32_t nTail = (uint32_t)(mpEnd - pPos);
        uint32_t v = rValue;
        if (n < nTail) {
            FUN_00c75b60(pPos, n, &v, (uint8_t*)mpEnd - n * 4);
        } else {
            for (uint32_t i = nTail; i > 0; --i)
                pPos[n - nTail + i - 1] = pPos[i - 1];
            for (uint32_t i = 0; i < n - nTail; ++i)
                pPos[i] = v;
        }
        mpEnd += n;
    }
    return pPos;
}

// ---------------------------------------------------------------------------------------------
// 0x00c795f0 - eastl::vector<EA::AutoRefCount<T>>::insert(pos, n, value)
// ---------------------------------------------------------------------------------------------
// @ 0x00c795f0 tRefVec::insert
void tRefVec::insert(tAutoRef* pPos, uint32_t n, tAutoRef* pValue)
{
    if ((uint32_t)(mpCap - mpEnd) < n) {
        uint32_t nOld  = (uint32_t)(mpEnd - mpBegin);
        uint32_t nGrow = nOld * 2;
        if (nOld == 0)
            nGrow = 1;
        uint32_t nCap = nOld + n;
        if (nCap < nGrow)
            nCap = nGrow;

        tAutoRef* pNew = (nCap == 0)
            ? 0
            : (tAutoRef*)operator_new(nCap * 4, g_szSimulator, 0, 0, g_szAllocatorH, 0xd1);

        uint32_t nPrefix = (uint32_t)((uint8_t*)pPos - (uint8_t*)mpBegin);
        tAutoRef* pMid = (tAutoRef*)FUN_00c76740(pNew, mpBegin, nPrefix);
        tAutoRef* pFill = (tAutoRef*)((uint8_t*)pMid + nPrefix);
        FUN_00c75b60(pFill, n, pValue, pPos);

        uint32_t nTail = (uint32_t)((uint8_t*)mpEnd - (uint8_t*)pPos);
        tAutoRef* pNewEnd = (tAutoRef*)FUN_00c76740((uint8_t*)pFill + n * 4, pPos, nTail);

        if (mpBegin != 0 && *((int32_t*)mpBegin - 1) != 0)
            operator_delete_array(mpBegin);

        mpBegin = pNew;
        mpEnd   = pNewEnd;
        mpCap   = (tAutoRef*)((uint8_t*)pNew + nCap * 4);
    } else if (n != 0) {
        void* pObj = pValue->mpObj;
        if (pObj != 0)
            ((cRefObj*)pObj)->AddRef();

        uint32_t nRest = (uint32_t)(mpEnd - pPos);
        if (n < nRest) {
            for (uint32_t i = nRest; i > n; --i)
                pPos[i + n - 1] = pPos[i - 1];
            for (uint32_t i = 0; i < n; ++i)
                pPos[i] = *pValue;
        } else {
            for (uint32_t i = nRest; i < n; ++i)
                pPos[i] = *pValue;
        }
        mpEnd += n;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c79b60 - Simulator::cPlayer destructor body (base dtor tail-called at the end)
// ---------------------------------------------------------------------------------------------
// @ 0x00c79b60 cPlayer::FUN_00c79b60
void cPlayer::FUN_00c79b60()
{
    mpVtbl00 = (void*)&g_vtbl_01472d48;
    mpVtbl04 = (void*)&g_vtbl_01472d34;
    mpVtbl34 = (void*)&g_vtbl_01472d24;

    if (mpRef11f4 != 0) {
        void* p = mpRef11f4;
        mpRef11f4 = 0;
        ((cRefObj*)p)->Release();
    }
    if (mpBlock129c != 0 && mpBlock129c != mpBlock12ac)
        operator_delete_array(mpBlock129c);

    mTimer1258.~cGonzagoTimer();
    mRbTree.DoNukeSubtree(mRbTree.mpRoot);

    for (uint32_t i = (uint32_t)mpPairBegin1214; i < (uint32_t)mpPairEnd1218; i += 0x28)
        ((cGonzagoTimer*)(i + 8))->~cGonzagoTimer();
    if (mpPairBegin1214 != 0 && *((int32_t*)mpPairBegin1214 - 1) != 0)
        operator_delete_array(mpPairBegin1214);

    mList11f8.FUN_00c77b10(mList11f8.mpHead);
    if (mpRef11f4 != 0)
        ((cRefObj*)mpRef11f4)->Release();

    if (mpBlock11d8 != 0)
        operator_delete_array(mpBlock11d8);
    mList11c0.FUN_00c781e0(mList11c0.mpBegin, mList11c0.mpEnd);
    if (mList11c0.mpBegin != 0)
        operator_delete_array(mList11c0.mpBegin);

    if (mVec11ac.mpBegin != 0 && *((int32_t*)mVec11ac.mpBegin - 1) != 0)
        operator_delete_array(mVec11ac.mpBegin);
    if (mVec1198.mpBegin != 0 && *((int32_t*)mVec1198.mpBegin - 1) != 0)
        operator_delete_array(mVec1198.mpBegin);
    if (mVec1184.mpBegin != 0 && *((int32_t*)mVec1184.mpBegin - 1) != 0)
        operator_delete_array(mVec1184.mpBegin);

    mBanModeTable.FUN_00c77ab0(mBanModeTable.mpBegin, mBanModeTable.mpEnd);
    if (mBanModeTable.mpBegin != 0 && *((int32_t*)mBanModeTable.mpBegin - 1) != 0)
        operator_delete_array(mBanModeTable.mpBegin);

    mHash1120.DoFreeNodes(mHash1120.mpBuckets, mHash1120.mnCount);
    mHash1120.mnNext = 0;
    if (mHash1120.mnCount > 1)
        operator_delete_array(mHash1120.mpBuckets);
    if (mpRef10e8 != 0)
        ((cRefObj*)mpRef10e8)->Release();

    mHash69c.DoFreeNodes(mHash69c.mpBuckets, mHash69c.mnCount);
    {
        uint32_t* p = mHash69c.mpBuckets;
        mHash69c.mnNext = 0;
        if (mHash69c.mnCount > 1 && p != mHash69c.mpStatic) {
            if (p < mHash69c.mpPoolBegin || mHash69c.mpPoolEnd <= p) {
                operator_delete_array(p);
            } else {
                *p = (uint32_t)mHash69c.mpFreeHead;
                mHash69c.mpFreeHead = p;
            }
        }
    }

    mPool38.FUN_00a42fe0(mPool38.mpPool, mPool38.mnCount);
    {
        uint32_t* p = mPool38.mpPool;
        mPool38.mnNext = 0;
        if (mPool38.mnCount > 1 && p != mPool38.mpStatic) {
            if (mPool38.mpPoolBegin <= p && p < mPool38.mpPoolEnd) {
                *p = (uint32_t)mPool38.mpFreeHead;
                mPool38.mpFreeHead = p;
                mpVtbl34 = (void*)&g_vtbl_013eb394;
                return;
            }
            operator_delete_array(p);
        }
    }
    mpVtbl34 = (void*)&g_vtbl_013eb394;
}