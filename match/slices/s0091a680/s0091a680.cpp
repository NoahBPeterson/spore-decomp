// EA::Callstack source/database lookup internals: EASTL list and hash-map instantiations plus
// the dbghelp stack walk. 0x0091a680..0x0091b5d0.
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
#include <intrin.h>

// ---- external helpers (masked relocations) ---------------------------------
extern "C" void* __cdecl operator_new(size_t nSize, const char* pName, int nFlags, int nAlign,
                                      const char* pFile, int nLine);    // 0x00f473a0
extern "C" void  operator_delete_array(void* pBlock);                   // 0x00f47380
extern "C" void* __cdecl memset(void* pDst, int nValue, size_t nLen);
extern "C" wchar_t* __cdecl wcscpy(wchar_t* pDst, const wchar_t* pSrc);

extern const char gEastlAllocatorFile[];    // 0x013ebb38 "…/EASTL/allocator.h"
extern const float gOne;                    // 0x01485720 (_HK_REAL_ONE)
extern const float gTwo;                    // 0x01470f1c (2.0f)
extern const wchar_t gEmptyString16[];      // 0x01667bac
extern const void* gWideTokenTable;         // 0x01667b34

extern "C" __declspec(dllimport) void* __stdcall GetCurrentProcess();
extern "C" __declspec(dllimport) void* __stdcall GetCurrentThread();

// ---- EASTL string block ----------------------------------------------------
struct cWString {
    uint16_t* mpBegin;                  // +0x00
    uint16_t* mpCapacityEnd;            // +0x04
    uint16_t* mpEnd;                    // +0x08
    uint16_t* mpSSOBuffer;              // +0x0c
    void Assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
};

// ---- database lookup list --------------------------------------------------
struct cLookupNode {
    cLookupNode* mpNext;                // +0x00
    cLookupNode* mpPrev;                // +0x04
    void* mpValue;                      // +0x08
};

struct cStrNode {
    cStrNode* mpNext;                   // +0x00
    cStrNode* mpPrev;                   // +0x04
    cWString mString;                   // +0x08
};

struct cStrList {
    cStrNode* mpListNext;               // +0x00 (sentinel head)
    cStrNode* mpListPrev;               // +0x04
    void DoClear();                     // 0x0091a750
};

// ---- address-rep hash entry ------------------------------------------------
struct cEntryFlags {
    union {
        struct {
            int      mKind   : 4;       // +0x40, bits 0..3
            int      mInfo   : 12;      // +0x40, bits 4..15
            uint32_t mUnused : 16;      // +0x42
        };
        struct {
            uint16_t mPadLow;           // +0x40
            uint16_t mExtra;            // +0x42
        };
    };
};

struct cAddressRepEntry {
    cWString mBlocks[4];                // +0x00..0x3f
    cEntryFlags mFlags;                 // +0x40
};

struct cHashNode {
    const void* mpKey;                  // +0x00
    cAddressRepEntry mValue;            // +0x04
    cHashNode* mpNext;                  // +0x48
    cHashNode(const void* const& pKey, const cAddressRepEntry& value);   // 0x0091a6d0
    void CopyFrom(const cHashNode* pSource);                            // 0x0091a620
};

// EASTL prime_rehash_policy (floats at +0x10 of the map)
struct cRehashPolicy {
    void DoRebuild(uint32_t* pOut, uint32_t nBucketCount, uint32_t nElements, int bFlag); // 0x00921440
};

struct IAddressRepLookup {
    virtual void v00(int bDelete);                          // +0x00
    virtual bool v04(const void* pDatabase, void* pArg);    // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0C(void* pArg1, void* pArg2);             // +0x0c
};

struct cAddressRepLookupSet {
    bool mbEnableAutoDatabaseFind;      // +0x00
    bool mbLookedForDBFiles;            // +0x01
    uint8_t mPad02[2];                  // +0x02
    cLookupNode mListHead;              // +0x04 (sentinel)
    cStrList mSourceDirList;            // +0x10 (sentinel)
    uint32_t mPad18;                    // +0x18
    uint32_t mnSourceCodeFailureCount;  // +0x1c
    uint32_t mnSourceContextLineCount;  // +0x20
    void PushBack(void* pValue);                                        // 0x0091a680
    int  GetSymbolInfoTypeFromDatabase(const void* pDatabase);          // 0x0091a200
    bool AddDatabaseFile(const void* pDatabase, void* pA, void* pB, int bFlag); // 0x0091a7a0
    void AutoDatabaseAdd();                                             // 0x0091a8a0
    int  GetAddressRepSource(cAddressRepEntry* pEntry, int* pLine);      // 0x0091a970
    uint32_t GetAddressRepFromSet(uint32_t nFlags, const void* pAddress,
                                  cAddressRepEntry* pEntry, int* pLine); // 0x0091a490
    uint32_t GetAddressRep(uint32_t nFlags, const void* pAddress,
                           cAddressRepEntry* pEntry, int* pLine);        // 0x0091ae20
    void Shutdown();                                                    // 0x0091a430
};

struct cAddressRepCache {
    uint32_t mField00;                  // +0x00
    cHashNode** mpBucketArray;          // +0x04
    uint32_t mnBucketCount;             // +0x08
    uint32_t mnElementCount;            // +0x0c
    float mfMaxLoadFactor;              // +0x10
    float mfGrowthFactor;               // +0x14
    uint32_t mField18;                  // +0x18
    uint8_t mPad1C[4];                  // +0x1c
    cAddressRepLookupSet mLookupSet;    // +0x20
    cAddressRepCache();                                                 // 0x0091b2f0
    ~cAddressRepCache();                                                // 0x0091b090
    cAddressRepEntry* operator[](const void* const& pKey);              // 0x0091af40
    void DoFreeNodes(cHashNode** ppBuckets, uint32_t nBucketCount);     // 0x0091aeb0
    void DoInsert(void** ppIter, const cHashNode* pSource, uint32_t bFlag); // 0x0091ad30
    void DoRehash(uint32_t nBucketCount);                               // 0x0091a380
    void SetAddressRep(int nIndex, const void* const& pKey, const char* pText,
                       int nLen, int nValue);                           // 0x0091b000
    uint32_t GetAddressRep(uint32_t nMask, const void* const& pKey, int* pRep,
                           int* pLine, char bBuild);                    // 0x0091b0f0
};

// string stub embedded in an AddressRep object (offsets 0x228 / 0x33c)
struct cStrStub {
    void AssignRange(const char* pBegin, const char* pEnd);   // 0x00942e50
    void Sprintf(const char* pFormat, ...);                   // 0x0091a730
};

// file stream stub
struct cFileStream {
    void Construct(const wchar_t* pPath);                     // 0x00931e10
    bool Open(uint32_t nMode, uint32_t a, uint32_t b, uint32_t c); // 0x009318f0
    int  GetSize();                                           // 0x00931b70
    uint32_t Read(void* pDst, uint32_t nLen);                 // 0x00931ce0
    bool Close();                                             // 0x00931a70
    void Destruct();                                          // 0x00931e70
};

// ---- external callees ------------------------------------------------------
extern "C" void FUN_00406540(void* pDst, void* pSrc, int nElemSize, int nCount, void* pCtor); // 0x00406540
void* FUN_006abeb0(int nSize);                                        // 0x006abeb0
void* __fastcall FUN_0091d480(void* pMem);                            // 0x0091d480
void* __fastcall FUN_0091c210(void* pMem);                            // 0x0091c210
void* __fastcall FUN_0091d7a0(void* pMem);                            // 0x0091d7a0
void* __fastcall FUN_00919510(void* pMem);                            // 0x00919510
void  FUN_00935d30(wchar_t* pBuffer);                                 // 0x00935d30
void  FUN_00930dd0(wchar_t* pPath, wchar_t** ppA, wchar_t** ppB,
                   wchar_t** ppC);                                    // 0x00930dd0
char  FUN_00931fa0(const wchar_t* pPath);                             // 0x00931fa0
void  FUN_0093cf60(wchar_t* pDst, int nMax, const char* pSrc, int nFlag); // 0x0093cf60
void* FUN_00921150(const wchar_t* pText, const wchar_t* pToken,
                   const void* pTable);                               // 0x00921150
void  FUN_00920f00(wchar_t* pText);                                   // 0x00920f00
void* FUN_00920c60(const wchar_t* pText, const void* pTable);         // 0x00920c60
char* FUN_0093d0b0(char* pBegin, char* pEnd, char** ppNext);          // 0x0093d0b0
void  FUN_0091a380(cAddressRepCache* pMap, uint32_t nBucketCount);     // 0x0091a380
void  FUN_00ce0bf0(void** ppIter, const void* const& pKey);           // 0x00ce0bf0
void  __fastcall FUN_0091a4f0(cAddressRepEntry* pEntry);              // 0x0091a4f0
void  FUN_00401930(cAddressRepEntry* pDst, int nSize, int nCount,
                   void* pCtor);                                      // 0x00401930
void  __fastcall FUN_00919a60(cAddressRepEntry* pEntry);              // 0x00919a60
void  __fastcall FUN_0091b350(void* pDbgHelp);                        // 0x0091b350

// ===========================================================================
// @ 0x0091a680 : append a database object to the lookup list
// ===========================================================================
void cAddressRepLookupSet::PushBack(void* pValue)
{
    cLookupNode* pHead = &mListHead;
    cLookupNode* pNode = (cLookupNode*)operator_new(0x0c, "EASTL", 0, 0, gEastlAllocatorFile, 0xd1);
    if (&pNode->mpValue) pNode->mpValue = pValue;
    pNode->mpNext = pHead;
    pNode->mpPrev = pHead->mpPrev;
    pHead->mpPrev->mpNext = pNode;
    pHead->mpPrev = pNode;
}

// @ 0x0091a6d0 : node copy-construction from a key and an entry
cHashNode::cHashNode(const void* const& pKey, const cAddressRepEntry& value)
{
    mpKey = pKey;
    FUN_00406540((void*)&mValue.mBlocks[0], (void*)&value.mBlocks[0], 0x10, 4,
                 (void*)0x57cb10);
    mValue.mFlags.mKind = value.mFlags.mKind;
    mValue.mFlags.mInfo = value.mFlags.mInfo;
    mValue.mFlags.mExtra = value.mFlags.mExtra;
}

// @ 0x0091a750 : destroy every node of a string list
void cStrList::DoClear()
{
    cStrNode* pHead = (cStrNode*)this;
    cStrNode* pNode = mpListNext;
    if (pNode == pHead) return;
    do {
        cStrNode* pCur = pNode;
        int nBytes = (int)((char*)pCur->mString.mpEnd - (char*)pCur->mString.mpBegin);
        pNode = pCur->mpNext;
        nBytes &= ~1;
        if (nBytes > 2 && pCur->mString.mpBegin) operator_delete_array(pCur->mString.mpBegin);
        operator_delete_array(pCur);
    } while (pNode != pHead);
}

// @ 0x0091a7a0 : load one symbol database file
bool cAddressRepLookupSet::AddDatabaseFile(const void* pDatabase, void* pA, void* pB, int bFlag)
{
    int nType = GetSymbolInfoTypeFromDatabase(pDatabase);
    if (nType == 0) return false;

    IAddressRepLookup* pRepo;
    switch (nType - 1) {
    case 0: {
        void* pMem = FUN_006abeb0(0x90);
        pRepo = pMem ? (IAddressRepLookup*)FUN_0091d480(pMem) : 0;
        break;
    }
    case 1: {
        void* pMem = FUN_006abeb0(0x58);
        pRepo = pMem ? (IAddressRepLookup*)FUN_0091c210(pMem) : 0;
        break;
    }
    case 2:
    case 3: {
        void* pMem = FUN_006abeb0(0x10);
        pRepo = pMem ? (IAddressRepLookup*)FUN_0091d7a0(pMem) : 0;
        break;
    }
    case 4: {
        void* pMem = FUN_006abeb0(0x2e8);
        pRepo = pMem ? (IAddressRepLookup*)FUN_00919510(pMem) : 0;
        break;
    }
    default:
        return false;
    }
    if (!pRepo) return false;

    pRepo->v0C(pA, pB);
    if (!pRepo->v04(pDatabase, pA)) {
        pRepo->v00(1);
        return false;
    }
    PushBack(pRepo);
    return true;
}

// @ 0x0091a8a0 : look for the sibling .map/.pdb files of the running module
void cAddressRepLookupSet::AutoDatabaseAdd()
{
    if (mbLookedForDBFiles) return;
    mbLookedForDBFiles = true;

    wchar_t aPath[0x104];
    const wchar_t* pA = 0;
    const wchar_t* pB = 0;
    wchar_t* pName = 0;

    FUN_00935d30(aPath);
    FUN_00930dd0(aPath, (wchar_t**)&pB, (wchar_t**)&pA, &pName);
    wcscpy(pName, L".map");
    if (FUN_00931fa0(aPath)) AddDatabaseFile(aPath, 0, 0, 1);
    wcscpy(pName, L".pdb");
    if (FUN_00931fa0(aPath)) AddDatabaseFile(aPath, 0, 0, 1);
}

// @ 0x0091a970 : build the source-code representation of one address
int cAddressRepLookupSet::GetAddressRepSource(cAddressRepEntry* pEntry, int* pLine)
{
    int nResult = 0;
    if (mnSourceCodeFailureCount >= 0x40) {
        mnSourceCodeFailureCount++;
        return 0;
    }
    cStrStub* pOut = (cStrStub*)((char*)pEntry + 0x228);

    wchar_t aPath[0x104];
    FUN_0093cf60(aPath, 0x104, *(const char**)pEntry, -1);
    aPath[0x103] = 0;
    bool bFound = FUN_00931fa0(aPath) != 0;
    if (!bFound) {
        const wchar_t* pEnd = aPath;
        while (*pEnd) ++pEnd;
        wchar_t aTemp[0x108];
        cStrNode* pDir = mSourceDirList.mpListNext;
        do {
            if (pDir == (cStrNode*)&mSourceDirList) break;
            const wchar_t* pCur = aPath;
            while (pCur != pEnd) {
                aTemp[0] = 0;
                FUN_00921150(aTemp, pCur, gWideTokenTable);
                FUN_00920f00(aTemp);
                if (FUN_00931fa0(aTemp)) {
                    bFound = true;
                    wcscpy(aPath, aTemp);
                    aPath[0x103] = 0;
                    break;
                }
                pCur = (const wchar_t*)FUN_00920c60(pCur, gWideTokenTable);
            }
            pDir = pDir->mpNext;
        } while (!bFound);
    }

    cFileStream stream;
    stream.Construct(aPath);
    if (stream.Open(1, 6, 1, 0)) {
        int nSize = stream.GetSize();
        char* pText;
        char* pTextEnd;
        if ((uint32_t)(nSize + 1) > 1) {
            pText = (char*)operator_new(nSize + 1, "EASTL", 0, 0, gEastlAllocatorFile, 0xd1);
            pTextEnd = pText + nSize + 1;
        } else {
            pText = (char*)gEmptyString16;
            pTextEnd = (char*)gEmptyString16 + 1;
        }
        memset(pText, 0, nSize);
        pText[nSize] = 0;
        stream.Read(pText, nSize);
        stream.Close();

        int nLine = *pLine;
        int nHalf = (int)(mnSourceContextLineCount >> 1);
        int nFirst = nLine - nHalf;
        int nLast = nLine + nHalf;
        char* pCur = pText;
        for (int nIndex = 1; pCur < pTextEnd && nIndex <= nLast; nIndex++) {
            char* pNext;
            char* pLineStart = FUN_0093d0b0(pCur, pTextEnd, &pNext);
            if (nIndex >= nFirst) {
                *pLineStart = 0;
                if (nIndex == nLine)
                    pOut->AssignRange("> => ", "> => " + 5);
                else
                    pOut->AssignRange(">    ", ">    " + 5);
                pOut->AssignRange(pCur, pNext);
                pOut->AssignRange("\r\n", "\r\n" + 2);
                nResult = 4;
                nFirst = nLine - nHalf;
            }
            pCur = pNext;
        }
        if (pTextEnd - pText > 1 && pText) operator_delete_array(pText);
    }
    stream.Destruct();
    if (nResult == 0) {
        mnSourceCodeFailureCount++;
        return 0;
    }
    return nResult;
}

// @ 0x0091ad30 : insert one node into the hash map
void cAddressRepCache::DoInsert(void** ppIter, const cHashNode* pSource, uint32_t bFlag)
{
    uint32_t nKey = (uint32_t)ppIter[0];
    uint32_t nSlot = nKey % mnBucketCount;
    cHashNode** ppSlot = &mpBucketArray[nSlot];
    cHashNode* pNode = *ppSlot;
    while (pNode) {
        if (pNode->mpKey == ppIter[0]) {
            ppIter[0] = pNode;
            *((uint8_t*)ppIter + 8) = 0;
            ppIter[1] = ppSlot;
            return;
        }
        pNode = pNode->mpNext;
    }

    uint32_t aRebuild[2];
    ((cRehashPolicy*)&mfMaxLoadFactor)->DoRebuild(aRebuild, mnBucketCount, mnElementCount, 1);
    cHashNode* pNew = (cHashNode*)operator_new(0x4c, "EASTL", 0, 0, gEastlAllocatorFile, 0xd1);
    if (pNew) pNew->CopyFrom(pSource);
    pNew->mpNext = 0;
    (void)bFlag;
    if (*(uint8_t*)aRebuild) {
        uint32_t nBucketCount = aRebuild[1];
        nSlot = nKey % nBucketCount;
        DoRehash(nBucketCount);
    }
    pNew->mpNext = mpBucketArray[nSlot];
    mpBucketArray[nSlot] = pNew;
    mnElementCount++;
    ppIter[0] = pNew;
    ppIter[1] = &mpBucketArray[nSlot];
    *((uint8_t*)ppIter + 8) = 1;
}

// @ 0x0091ae20 : set-level address-rep lookup
uint32_t cAddressRepLookupSet::GetAddressRep(uint32_t nFlags, const void* pAddress,
                                             cAddressRepEntry* pEntry, int* pLine)
{
    if (nFlags & 2) nFlags |= 1;
    if (mListHead.mpNext == &mListHead && mbEnableAutoDatabaseFind && !mbLookedForDBFiles)
        AutoDatabaseAdd();

    uint32_t nResult = GetAddressRepFromSet(nFlags, pAddress, pEntry, pLine);
    if (nFlags & 8) {
        ((cStrStub*)((char*)pEntry + 0x33c))->Sprintf("0x%08x", (uint32_t)pAddress);
        nResult |= 8;
    }
    if ((nFlags & 4) && pEntry->mBlocks[0].mpBegin != pEntry->mBlocks[0].mpCapacityEnd)
        nResult |= (uint32_t)GetAddressRepSource(pEntry, pLine);
    return nResult;
}

// @ 0x0091aeb0 : free all hash-map nodes
void cAddressRepCache::DoFreeNodes(cHashNode** ppBuckets, uint32_t nBucketCount)
{
    for (uint32_t i = 0; i < nBucketCount; i++) {
        cHashNode* pNode = ppBuckets[i];
        while (pNode) {
            cHashNode* pNext = pNode->mpNext;
            cWString* pBlock = &pNode->mValue.mBlocks[4];
            int k = 3;
            do {
                cWString* s = pBlock - 1;
                int nBytes = (int)((char*)s->mpEnd - (char*)s->mpBegin);
                if (nBytes > 1 && s->mpBegin) operator_delete_array(s->mpBegin);
                --pBlock;
                --k;
            } while (k >= 0);
            operator_delete_array(pNode);
            pNode = pNext;
        }
        ppBuckets[i] = 0;
    }
}

// @ 0x0091af40 : hash_map::operator[]
cAddressRepEntry* cAddressRepCache::operator[](const void* const& pKey)
{
    void* aIter[3];
    FUN_00ce0bf0(aIter, pKey);
    if (aIter[0] != (void*)mpBucketArray[mnBucketCount]) {
        cAddressRepEntry value;
        for (int i = 0; i < 4; i++) {
            value.mBlocks[i].mpBegin = (uint16_t*)gEmptyString16;
            value.mBlocks[i].mpCapacityEnd = (uint16_t*)gEmptyString16;
            value.mBlocks[i].mpEnd = (uint16_t*)gEmptyString16;
            value.mBlocks[i].mpSSOBuffer = (uint16_t*)((const char*)gEmptyString16 + 1);
        }
        value.mFlags.mKind = 0;
        value.mFlags.mInfo = 0;
        value.mFlags.mExtra = 0;

        cHashNode node(pKey, value);
        *((uint8_t*)aIter + 8) = 0;
        DoInsert(aIter, &node, *((uint8_t*)aIter + 8));
        FUN_0091a4f0(&node.mValue);
        FUN_0091a4f0(&value);
    }
    return (cAddressRepEntry*)((uint8_t*)aIter[0] + 4);
}

// @ 0x0091b000 : store one representation field of one address
void cAddressRepCache::SetAddressRep(int nIndex, const void* const& pKey, const char* pText,
                                     int nLen, int nValue)
{
    cAddressRepEntry* pEntry = (*this)[pKey];
    uint32_t nKind = pEntry->mFlags.mKind;
    nKind = (nKind | (1 << (nIndex & 0x1f)));
    pEntry->mFlags.mKind = nKind;
    if (nIndex == 1) {
        pEntry->mFlags.mInfo = nValue;
    } else if (nIndex == 0) {
        pEntry->mFlags.mExtra = (uint16_t)nValue;
    }
    if (nLen < 0) {
        const char* pEnd = pText;
        while (*pEnd) ++pEnd;
        nLen = (int)(pEnd - pText);
    }
    ((cWString*)((char*)pEntry + (nIndex << 4)))->Assign(pText, pText + nLen);
}

// @ 0x0091b090 : address-rep cache destructor
cAddressRepCache::~cAddressRepCache()
{
    mLookupSet.Shutdown();
    mLookupSet.mSourceDirList.DoClear();
    cLookupNode* pNode = mLookupSet.mListHead.mpNext;
    while (pNode != &mLookupSet.mListHead) {
        cLookupNode* pNext = pNode->mpNext;
        operator_delete_array(pNode);
        pNode = pNext;
    }
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) operator_delete_array(mpBucketArray);
}

// @ 0x0091b0f0 : cache-level address-rep lookup
uint32_t cAddressRepCache::GetAddressRep(uint32_t nMask, const void* const& pKey, int* pRep,
                                         int* pLine, char bBuild)
{
    cAddressRepEntry* pEntry = (*this)[pKey];
    if (bBuild && ((pEntry->mFlags.mKind & nMask) != nMask)) {
        cAddressRepEntry aTemp[4];
        FUN_00401930(&aTemp[0], 0x114, 4, (void*)0x00919a60);
        mLookupSet.GetAddressRep(nMask, pKey, aTemp, pLine);
        for (uint32_t nIndex = 0, nBit = 1; nIndex < 4; nIndex++, nBit <<= 1) {
            if (nMask & nBit) {
                cWString* s = &aTemp[nIndex].mBlocks[0];
                if (s->mpBegin != s->mpCapacityEnd)
                    SetAddressRep((int)nIndex, pKey, (const char*)s->mpBegin,
                                  (int)((char*)s->mpCapacityEnd - (char*)s->mpBegin),
                                  *(int*)&aTemp[nIndex].mFlags);
            }
        }
        for (int k = 3; k >= 0; k--) {
            cWString* s = &aTemp[k].mBlocks[0];
            int nBytes = (int)((char*)s->mpEnd - (char*)s->mpBegin);
            if (nBytes > 1 && s->mpBegin) operator_delete_array(s->mpBegin);
        }
    }

    uint32_t nResult = 0;
    uint32_t nHave = pEntry->mFlags.mKind & nMask;
    if (!(nHave & 1) || pEntry->mBlocks[0].mpBegin == pEntry->mBlocks[0].mpEnd) {
        pRep[0] = 0;
        pLine[0] = 0;
    } else {
        pRep[0] = (int)pEntry->mBlocks[0].mpBegin;
        pLine[0] = (int)pEntry->mFlags.mExtra;
        nResult = 1;
    }
    if (!(nHave & 2) || pEntry->mBlocks[1].mpBegin == pEntry->mBlocks[1].mpEnd) {
        pRep[1] = 0;
        pLine[1] = 0;
    } else {
        pRep[1] = (int)pEntry->mBlocks[1].mpBegin;
        pLine[1] = pEntry->mFlags.mInfo;
        nResult |= 2;
    }
    if (!(nHave & 4) || pEntry->mBlocks[2].mpBegin == pEntry->mBlocks[2].mpEnd) {
        pRep[2] = 0;
    } else {
        pRep[2] = (int)pEntry->mBlocks[2].mpBegin;
        nResult |= 4;
    }
    pLine[2] = 0;
    if ((nHave & 8) && pEntry->mBlocks[3].mpBegin != pEntry->mBlocks[3].mpEnd) {
        pRep[3] = (int)pEntry->mBlocks[3].mpBegin;
        pLine[3] = 0;
        return nResult | 8;
    }
    pRep[3] = 0;
    pLine[3] = 0;
    return nResult;
}

// @ 0x0091b2f0 : address-rep cache constructor
cAddressRepCache::cAddressRepCache()
    : mfMaxLoadFactor(gOne)
    , mfGrowthFactor(gTwo)
{
    mpBucketArray = (cHashNode**)0x0154df28;
    mnElementCount = 0;
    mField18 = 0;
    mnBucketCount = 1;
    mLookupSet.mbEnableAutoDatabaseFind = true;
    mLookupSet.mbLookedForDBFiles = false;
    mLookupSet.mListHead.mpNext = &mLookupSet.mListHead;
    mLookupSet.mListHead.mpPrev = &mLookupSet.mListHead;
    mLookupSet.mSourceDirList.mpListNext = (cStrNode*)&mLookupSet.mSourceDirList;
    mLookupSet.mSourceDirList.mpListPrev = (cStrNode*)&mLookupSet.mSourceDirList;
    mLookupSet.mnSourceCodeFailureCount = 0;
    mLookupSet.mnSourceContextLineCount = 8;
}

// ---------------------------------------------------------------------------
// @ 0x0091b3d0 : dbghelp stack walk
// ---------------------------------------------------------------------------
struct cContext {
    uint32_t mContextFlags;                 // +0x000
    uint8_t  mRest[0x2cc - 4];              // +0x004
};

struct cAddress64 {
    void*    mpOffset;                      // +0x00
    uint32_t mPad04;                        // +0x04
    uint32_t mnMode;                        // +0x08
    uint32_t mPad0C;                        // +0x0c
};

struct cStackFrame {
    cAddress64 mAddrPC;                     // +0x00
    uint32_t   mPad10[2];                   // +0x10
    cAddress64 mAddrStack;                  // +0x18
    cAddress64 mAddrFrame;                  // +0x24
    uint8_t    mRest[0xa4 - 0x30];          // +0x30
};

typedef int (__stdcall* StackWalk64Fn)(uint32_t nMachine, void* hProcess, void* hThread,
                                       cStackFrame* pFrame, cContext* pContext, void* pReadMemory,
                                       void* pFunctionTable, void* pGetModuleBase,
                                       void* pTranslate);
extern StackWalk64Fn gStackWalk64;          // 0x01667b50
extern void* gReadMemoryRoutine;            // 0x01667b54
extern void* gFunctionTableRoutine;         // 0x01667b58
extern uint32_t gDbgHelpInitState;          // 0x01667b40

// @ 0x0091b3d0
uint32_t GetCallstack(void** pOut, uint32_t nMaxFrames, const void** pContext)
{
    uint32_t nFrames = 0;
    if (gDbgHelpInitState == 0) FUN_0091b350(&gDbgHelpInitState);
    if (gStackWalk64 == 0) {
        pOut[0] = 0;
        return 0;
    }

    cContext context;
    memset(&context, 0, 0x2cc);
    context.mContextFlags = 0x10001;

    void* pPC;
    void* pStack;
    void* pFramePtr;
    if (pContext) {
        pPC = (void*)pContext[0];
        pStack = (void*)pContext[1];
        pFramePtr = (void*)pContext[2];
    } else {
        pPC = _ReturnAddress();
        pStack = _AddressOfReturnAddress();
        pFramePtr = (void*)((char*)_AddressOfReturnAddress() + sizeof(void*));
    }

    cStackFrame frame;
    memset(&frame, 0, 0xa4);
    frame.mAddrPC.mpOffset = pPC;
    frame.mAddrPC.mnMode = 3;
    frame.mAddrStack.mpOffset = pStack;
    frame.mAddrStack.mnMode = 3;
    frame.mAddrFrame.mpOffset = pFramePtr;
    frame.mAddrFrame.mnMode = 3;

    void* hProcess = GetCurrentProcess();
    void* hThread = GetCurrentThread();
    int nSkip = 0;
    while (nFrames < nMaxFrames - 1) {
        if (!gStackWalk64(0x14c, hProcess, hThread, &frame, &context, 0, gReadMemoryRoutine,
                          gFunctionTableRoutine, 0))
            break;
        if (frame.mAddrStack.mpOffset == 0) break;
        if (pContext != 0 || nSkip > 0) pOut[nFrames++] = frame.mAddrPC.mpOffset;
        ++nSkip;
    }
    pOut[nFrames] = 0;
    return nFrames;
}
