// eastl algorithm / container internals shared by the star manager and the
// feedback-event code (gold6 worker 36, slice s00ba9810).

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short wchar_t16;

// ---- allocation / globals --------------------------------------------------
void* operator_new(uint32_t nSize, const char* pName, int a, int b, const char* pFile, int nLine); // 0x00f473a0
void operator_delete_array(void* pMem);                                  // 0x00f47380
void* OfflineAlloc(int nSize, const char* pName, int a, int b, int c, int d); // 0x00f473a0

extern const wchar_t16 gEmptyString16[];                                // 0x01667bac
extern uint8_t gbTypeCheckEnabled;                                       // 0x015d8b58
extern const wchar_t16 gTypeName[];                                      // 0x013f36bc  L"type"
extern const wchar_t16 gDbReadInitiated[];                               // 0x0145fc38  L"dbreadinitiated"
extern const wchar_t16 gDbReadCompleted[];                               // 0x0145fc18  L"dbreadcompleted"
extern const wchar_t16 gUnknownString[];                                 // 0x013f6254

extern const char gSimulatorName[];                                      // 0x013f09b4  "Simulator"
extern const char gAllocatorFile[];                                      // 0x013ebb38  EASTL/allocator.h
extern const char gMemoryStreamName[];                                   // 0x01465758  "App/memorystream"

// ---- shared shapes ---------------------------------------------------------
struct cSortTriple {                                                    // 12-byte sort / run key
    float mX;                                                           // +0x00
    float mY;                                                           // +0x04
    float mZ;                                                           // +0x08
};

struct cRunInfo {                                                       // 16-byte typesetter run
    float mX;                                                           // +0x00
    float mY;                                                           // +0x04
    float mZ;                                                           // +0x08
    uint32_t mExtra;                                                    // +0x0c
};

struct cIntVector {                                                     // eastl::vector<int>
    int* mpBegin;                                                       // +0x00
    int* mpEnd;                                                         // +0x04
    int* mpCapacityEnd;                                                 // +0x08
};

struct cIntVectorElement {                                              // 0x14-byte element
    cIntVector mVector;                                                 // +0x00
    uint32_t mExtra0;                                                   // +0x0c
    uint32_t mExtra1;                                                   // +0x10
};

struct cRbNodeBase {                                                    // eastl rbtree node header
    void* mpLeft;                                                       // +0x00
    void* mpRight;                                                      // +0x04
    void* mpParent;                                                     // +0x08
    uint32_t mnColor;                                                   // +0x0c
};

struct cFeedbackTree {                                                  // eastl::rbtree<uint32,...>
    void* mpAnchor;                                                     // +0x00
    cRbNodeBase mHead;                                                  // +0x04
    uint32_t mnSize;                                                    // +0x14
    void Find(void* pOut, uint32_t nKey);                               // 0x00e5c780
    int EraseKey(uint32_t nKey);                                        // 0x00baa110
};

struct cFeedbackNode {                                                  // tree node with value
    cRbNodeBase mBase;                                                  // +0x00
    uint32_t mnKey;                                                     // +0x10
    void* mpValue;                                                      // +0x14
};

void FUN_00ba8550(void* pBegin, void* pMiddle, void* pPred);            // 0x00ba8550
void FUN_00ba85c0(void* pBegin, void* pMiddle, void* pPred);            // 0x00ba85c0
void FUN_00ba7a80(void* pBegin, int a, int nCount, int b, cSortTriple value, void* pPred); // 0x00ba7a80
void FUN_00829110(void* pOut, const int* pFirst, const int* pLast, int* pDest,
                  const void* pSource);                                 // 0x00829110
void* RBTreeIncrement(void* pNode);                                     // 0x00921580
void RBTreeErase(void* pNode, void* pHead);                             // 0x00921880
bool FUN_00ac8050(void* pVisitor, int nFlags, void* pValue);            // 0x00ac8050
const cSortTriple* FUN_00bb9b80(void* pObject);                         // 0x00bb9b80
int FUN_00bb9ae0(void* pObject);                                        // 0x00bb9ae0
int GetAvatar(void* pNoun);                                             // 0x00b1fdb0
const cSortTriple* GetUFOKey(void* pEmpire);                            // 0x00c326b0
bool EmpireHasKey(void* pEmpire, const cSortTriple* pKey);              // 0x00c328c0

// ---- 0x00ba9810 ------------------------------------------------------------
// finalisation step of a quick sort over 12-byte elements: every element of
// [middle, end) that sorts before the pivot is swapped forward and re-inserted
// @ 0x00ba9810
void SortTriples_Finalize(cSortTriple* pBegin, cSortTriple* pMiddle, cSortTriple* pEnd,
                          char (*pPred)(const cSortTriple*, const cSortTriple*))
{
    FUN_00ba8550(pBegin, pMiddle, (void*)pPred);
    for (cSortTriple* pCur = pMiddle; pCur < pEnd; pCur++) {
        if (pPred(pCur, pBegin)) {
            cSortTriple saved = *pCur;
            *pCur = *pBegin;
            *pBegin = saved;
            FUN_00ba7a80(pBegin, 0, (int)(pMiddle - pBegin), 0, saved, (void*)pPred);
        }
    }
    FUN_00ba85c0(pBegin, pMiddle, (void*)pPred);
}

// ---- 0x00ba98b0 ------------------------------------------------------------
// copy a range of 0x14-byte integer-vector elements into storage the caller
// already allocated, advancing the iterator slot past every element
// @ 0x00ba98b0
cIntVectorElement** CopyIntVectorRange(cIntVectorElement** ppIter, const cIntVectorElement* pFirst,
                                       const cIntVectorElement* pLast, int nUnused,
                                       const void* pSource)
{
    *ppIter = (cIntVectorElement*)pSource;
    for (; pFirst != pLast; pFirst++) {
        cIntVector* pDest = (cIntVector*)*ppIter;
        if (pDest) {
            int nCount = (int)((char*)pFirst->mVector.mpEnd - (char*)pFirst->mVector.mpBegin) >> 2;
            int* pData;
            if (nCount != 0) {
                pData = (int*)operator_new((uint32_t)(nCount * 4), gSimulatorName, 0, 0,
                                           gAllocatorFile, 0xd1);
            } else {
                pData = 0;
            }
            int* pNewEnd;
            pDest->mpBegin = pData;
            pDest->mpEnd = pData;
            pDest->mpCapacityEnd = pData + nCount;
            FUN_00829110(&pNewEnd, pFirst->mVector.mpBegin, pFirst->mVector.mpEnd, pData, pSource);
            pDest->mpEnd = pNewEnd;
        }
        *ppIter = (cIntVectorElement*)((char*)*ppIter + 0x14);
    }
    return ppIter;
}

// ---- 0x00ba9960 ------------------------------------------------------------
// default-construct nCount 0x14-byte elements, each copied from *pSource
// @ 0x00ba9960
void ConstructIntVectorRange(cIntVectorElement* pDest, uint32_t nCount,
                             const cIntVectorElement* pSource)
{
    if (nCount <= 0) return;
    do {
        if (pDest) {
            int nCount2 = (int)((char*)pSource->mVector.mpEnd - (char*)pSource->mVector.mpBegin) >> 2;
            int* pData;
            if (nCount2 != 0) {
                pData = (int*)operator_new((uint32_t)(nCount2 * 4), gSimulatorName, 0, 0,
                                           gAllocatorFile, 0xd1);
            } else {
                pData = 0;
            }
            int* pNewEnd;
            pDest->mVector.mpBegin = pData;
            pDest->mVector.mpEnd = pData;
            pDest->mVector.mpCapacityEnd = pData + nCount2;
            FUN_00829110(&pNewEnd, pSource->mVector.mpBegin, pSource->mVector.mpEnd, pData,
                         pSource);
            pDest->mVector.mpEnd = pNewEnd;
        }
        --nCount;
        pDest = (cIntVectorElement*)((char*)pDest + 0x14);
    } while (nCount > 0);
}

// ---- wide-string / IO externals -------------------------------------------
struct cWideString {
    wchar_t16* mpBegin;                                                 // +0x00
    wchar_t16* mpEnd;                                                   // +0x04
    wchar_t16* mpCapacityEnd;                                           // +0x08

    cWideString();                                                      // empty ctor
    cWideString(const cWideString& other);                              // 0x0056e2d0
    void RangeInitialize(const wchar_t16* pStr);                        // 0x00579a90
    void assign(const wchar_t16* pFirst, const wchar_t16* pLast);       // 0x00423650
};

void ParseCommandLine(cWideString* pOut, const char* pCommandLine);     // 0x00694bf0
cWideString* ConvertToString16(cWideString* pOut, const char* pText, int nLength);  // 0x0093c5a0
cWideString* ConvertToString16(cWideString* pOut, const cWideString* pText);        // 0x0093c6d0
cWideString* PathJoin(cWideString* pOut, const cWideString* pBase,
                      const wchar_t16* pName);                          // 0x0057cba0
bool FileExists(const wchar_t16* pPath);                                // 0x00931fa0

struct ISaveStream;

struct IGameSave {                                                      // save-area object
    virtual char v00(uint32_t nId);
    virtual char v04(uint32_t nId);
    virtual char v08(const wchar_t16* pTypeName, void* pArg);
    virtual char v0C(const wchar_t16* pName);
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual ISaveStream* v24();
    virtual const wchar_t16* v28();
};
IGameSave* GetSaveArea(uint32_t nId);                                   // 0x006b1f90

// @ 0x00ba99f0 : does the save hold a "type" entry for this command line / file?
bool SaveAreaHasType(IGameSave* pSave, const char* pCommandLine, const char* pFileName, void* pArg)
{
    cWideString cmdLine;
    ParseCommandLine(&cmdLine, pCommandLine);
    if (cmdLine.mpBegin == cmdLine.mpEnd) return true;

    cWideString fileName;
    if (pFileName) {
        ConvertToString16(&fileName, pFileName, -1);
    } else {
        fileName.mpBegin = (wchar_t16*)gEmptyString16;
        fileName.mpEnd = (wchar_t16*)gEmptyString16;
        fileName.mpCapacityEnd = (wchar_t16*)gEmptyString16 + 1;
    }
    cWideString name(fileName);
    delete[] fileName.mpBegin;

    cWideString typedName;
    ConvertToString16(&typedName, &cmdLine);

    bool bMatch;
    if (typedName.mpBegin == typedName.mpEnd) {
        bMatch = pSave->v00((uint32_t)name.mpBegin);
        if (!bMatch) return false;
    } else {
        bMatch = pSave->v00((uint32_t)typedName.mpBegin);
        if (gbTypeCheckEnabled) {
            if (bMatch) {
                bMatch = pSave->v08(gTypeName, pArg);
                if (!bMatch) return false;
            } else {
                return false;
            }
        }
        if (!bMatch) return false;
        bMatch = pSave->v0C(typedName.mpBegin);
        if (!bMatch) return false;
    }
    delete[] typedName.mpBegin;
    delete[] name.mpBegin;
    return pSave->v04((uint32_t)name.mpBegin);
}

// @ 0x00ba9bc0 : StarManager - are the dbread marker files present in the save?
bool StarManager_HasDatabaseFile()
{
    cWideString namesA;
    cWideString namesB;
    namesA.RangeInitialize(GetSaveArea(0x4729a47)->v28());
    namesB.RangeInitialize(GetSaveArea(0x4729a47)->v28());

    cWideString joined;
    cWideString* pResult = PathJoin(&joined, &namesA, gDbReadInitiated);
    if (pResult != &namesA) namesA.assign(pResult->mpBegin, pResult->mpEnd);
    delete[] joined.mpBegin;

    pResult = PathJoin(&joined, &namesB, gDbReadCompleted);
    if (pResult != &namesB) namesB.assign(pResult->mpBegin, pResult->mpEnd);
    delete[] joined.mpBegin;

    if (!FileExists(namesA.mpBegin)) {
        delete[] namesB.mpBegin;
        delete[] namesA.mpBegin;
        return true;
    }
    bool bHasCompleted = FileExists(namesB.mpBegin);
    delete[] namesB.mpBegin;
    delete[] namesA.mpBegin;
    return bHasCompleted;
}

// ---- 0x00ba9d60 -----------------------------------------------------------
struct ISaveStream {                                                    // save-area reader
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual char v18(int a, int b, int c);
    virtual int  v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual int  v30(void* pDst, int nMax);
    virtual char v34(const char* pName, int a, int b, int c, void* pOut, int nUnused);
    virtual void v38();
    virtual void v3C(void* pArg);
};

struct IPackedDatabase {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual char v18(int a, int b, int c);
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30(void* pDst, int nMax);
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50(void* pStream);
    virtual void v54();
};

struct cMemoryStream {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28(int a, int b);
    void SetData(const void* pData, int nSize);                          // 0x0093b8e0
};
cMemoryStream* ConstructMemoryStream(uint32_t nSize);                    // 0x0093ba40
IPackedDatabase* ConstructDatabasePackedFile(int a, int b);              // 0x008d9f80

struct IResourceKeyVisitor {
    virtual void v00(const wchar_t16* pName);
    virtual void v04(const wchar_t16* pName);
};

// @ 0x00ba9d60 : read the packed address-rep database out of the save area
bool LoadDatabaseFromSave(IGameSave* pSave, uint32_t nVerbose)
{
    cSortTriple key;
    key.mX = 1.0f;
    key.mY = 1.0f;
    key.mZ = 1.0f;

    if (!pSave->v08(gEmptyString16, (void*)nVerbose)) return false;

    ISaveStream* pStream = (ISaveStream*)pSave->v24();
    uint32_t nSize = (uint32_t)pStream->v1C();
    void* pBuffer = OfflineAlloc((int)nSize, gSimulatorName, 0, 0, 0, 0);
    uint32_t nRead = 0;
    pStream->v30(&nRead, 1);
    pStream->v30(pBuffer, pStream->v1C());

    cMemoryStream* pMemory = ConstructMemoryStream(0x18);
    if (pMemory) pMemory->v04();
    pMemory->SetData(pBuffer, pStream->v1C());
    pMemory->v28(0, 0);

    IPackedDatabase* pDatabase = ConstructDatabasePackedFile(0, 0);
    if (pDatabase) pDatabase->v04();
    pDatabase->v50(pMemory);
    pDatabase->v04();
    if (!pDatabase->v18(1, 6, 0)) {
        bool bResult = false;
        pDatabase->v08();
        return bResult;
    }
    cIntVectorElement* pFound = 0;
    pDatabase->v30(&pFound, 0);
    pDatabase->v1C();
    delete[] (int*)pFound;
    pDatabase->v08();
    return true;
}

// ---- 0x00ba9f80 -----------------------------------------------------------
struct cStarPickState {
    uint8_t mPad000[0xf0];                                              // +0x000
    void** mpObjects;                                                   // +0x0f0
    void** mpObjectsEnd;                                                // +0x0f4
    uint8_t mPad0F8[0x150 - 0xf8];                                      // +0x0f8
    cFeedbackTree mEmpiresByKey;                                        // +0x150
    bool HasKey(const cSortTriple* pKey);                               // 0x00ba9f80
};

// @ 0x00ba9f80 : is this run key used by any star-manager entry or empire?
bool cStarPickState::HasKey(const cSortTriple* pKey)
{
    uint32_t nCount = (uint32_t)((char*)mpObjectsEnd - (char*)mpObjects) >> 2;
    for (uint32_t i = 0; i < nCount; i++) {
        void* pObject = mpObjects[i];
        const cSortTriple* pObjectKey = FUN_00bb9b80(pObject);
        if (pKey->mX == pObjectKey->mX && pKey->mY == pObjectKey->mY &&
            pKey->mZ == pObjectKey->mZ) {
            return true;
        }
        if (FUN_00bb9ae0(pObject) != 5) continue;
        uint32_t nAvatarKey = (uint32_t)GetAvatar(pObject);
        if ((int)nAvatarKey >= 0) continue;
        if (nAvatarKey == 0xffffffff) continue;
        mEmpiresByKey.Find(&nAvatarKey, nAvatarKey);
        cFeedbackNode* pNode = (cFeedbackNode*)nAvatarKey;
        if (pNode == (cFeedbackNode*)&mEmpiresByKey.mHead) continue;
        void* pEmpire = pNode->mpValue;
        if (!pEmpire) continue;
        const cSortTriple* pUFOKey = GetUFOKey(pEmpire);
        if (pKey->mX == pUFOKey->mX && pKey->mY == pUFOKey->mY && pKey->mZ == pUFOKey->mZ)
            return true;
        if (EmpireHasKey(pEmpire, pKey)) return true;
    }
    return false;
}

// ---- 0x00baa110 -----------------------------------------------------------
// @ 0x00baa110 : erase one key (and its ref-counted value) from a feedback map
int cFeedbackTree::EraseKey(uint32_t nKey)
{
    Find(&nKey, nKey);
    void* pNode = (void*)nKey;
    if (pNode != (void*)&mHead) {
        --mnSize;
        RBTreeIncrement(pNode);
        RBTreeErase(pNode, &mHead);
        void* pValue = ((cFeedbackNode*)pNode)->mpValue;
        if (pValue) {
            typedef void (__thiscall *release_fn)(void*);
            void** pVtable = *(void***)pValue;
            ((release_fn)pVtable[1])(pValue);
        }
        delete[] (cFeedbackNode*)pNode;
        return true;
    }
    return false;
}

// ---- 0x00baa2b0 -----------------------------------------------------------
// @ 0x00baa2b0 : offer every stored run to a visitor, under one display name
bool FeedbackTree_VisitRuns(IResourceKeyVisitor* pVisitor, const char* pName,
                            cFeedbackTree* pTree)
{
    bool bResult = true;
    if (pTree->mnSize == 0) return bResult;

    cWideString name;
    if (pName) {
        ConvertToString16(&name, pName, -1);
    } else {
        name.mpBegin = 0;
        name.mpEnd = 0;
        name.mpCapacityEnd = 0;
        name.RangeInitialize(0);
    }
    cWideString displayName(name);
    delete[] name.mpBegin;

    const wchar_t16* pDisplay = displayName.mpBegin;
    if (displayName.mpBegin == displayName.mpEnd) pDisplay = gUnknownString;
    pVisitor->v00(pDisplay);

    for (cFeedbackNode* pNode = (cFeedbackNode*)pTree->mHead.mpRight;
         pNode != (cFeedbackNode*)&pTree->mHead;
         pNode = (cFeedbackNode*)RBTreeIncrement(pNode)) {
        if (bResult) bResult = FUN_00ac8050(pVisitor, 0, &pNode->mpValue);
    }

    pDisplay = displayName.mpBegin;
    if (displayName.mpBegin == displayName.mpEnd) pDisplay = gUnknownString;
    pVisitor->v04(pDisplay);
    delete[] displayName.mpBegin;
    return bResult;
}

// ---- 0x00baa410 -----------------------------------------------------------
void* FUN_00ba7920(void* pFirst, const void* pMiddle, void* pDest);      // 0x00ba7920
void FUN_00edba80(void* pDest, const void* pFirst, const void* pLast);  // 0x00edba80

struct cRunInfoVector {
    cRunInfo* mpBegin;                                                  // +0x00
    cRunInfo* mpEnd;                                                    // +0x04
    cRunInfo* mpCapacityEnd;                                            // +0x08
    void Insert(cRunInfo* pPosition, const cRunInfo* pValue);           // 0x00baa410
};

// @ 0x00baa410 : insert one 16-byte run at pPosition
void cRunInfoVector::Insert(cRunInfo* pPosition, const cRunInfo* pValue)
{
    cRunInfo* pEnd = mpEnd;
    if (pEnd != mpCapacityEnd) {
        if (pValue >= pPosition && pValue < pEnd)
            pValue = (const cRunInfo*)((const char*)pValue + 0x10);
        if (pEnd) *pEnd = *(pEnd - 1);
        FUN_00edba80(pPosition, mpEnd - 1, mpEnd);
        *pPosition = *pValue;
        mpEnd++;
        return;
    }
    int nCapacity = (int)((char*)pEnd - (char*)mpBegin) >> 4;
    if (nCapacity == 0) {
        nCapacity = 1;
    } else {
        nCapacity *= 2;
    }
    cRunInfo* pNew;
    if (nCapacity == 0) {
        pNew = 0;
    } else {
        pNew = (cRunInfo*)operator_new((uint32_t)(nCapacity * 0x10), gSimulatorName, 0, 0,
                                       gAllocatorFile, 0xd1);
    }
    cRunInfo* pSlot = (cRunInfo*)FUN_00ba7920(mpBegin, pPosition, pNew);
    if (pSlot) *pSlot = *pValue;
    cRunInfo* pNewEnd = (cRunInfo*)FUN_00ba7920(pPosition, mpEnd, pSlot + 1);
    delete[] (int*)mpBegin;
    mpEnd = pNewEnd;
    mpCapacityEnd = (cRunInfo*)((char*)pNew + (uint32_t)nCapacity * 0x10);
    mpBegin = pNew;
}

// ---- 0x00baa530 -----------------------------------------------------------
void* FUN_00ba7960(void* pFirst, const void* pMiddle, void* pDest);      // 0x00ba7960

struct cTripleVector {
    cSortTriple* mpBegin;                                               // +0x00
    cSortTriple* mpEnd;                                                 // +0x04
    cSortTriple* mpCapacityEnd;                                         // +0x08
    void Insert(cSortTriple* pPosition, const cSortTriple* pValue);     // 0x00baa530
};

// @ 0x00baa530 : insert one 12-byte element at pPosition
void cTripleVector::Insert(cSortTriple* pPosition, const cSortTriple* pValue)
{
    cSortTriple* pEnd = mpEnd;
    if (pEnd != mpCapacityEnd) {
        if (pPosition <= pValue && pValue < pEnd)
            pValue = (const cSortTriple*)((const char*)pValue + 0xc);
        if (pEnd) *pEnd = *(pEnd - 1);
        for (cSortTriple* pCur = mpEnd - 1; pCur != pPosition; pCur--)
            pCur[0] = pCur[-1];
        *pPosition = *pValue;
        mpEnd++;
        return;
    }
    int nCapacity = (int)((char*)pEnd - (char*)mpBegin) / 0xc;
    if (nCapacity == 0) {
        nCapacity = 1;
    } else {
        nCapacity *= 2;
    }
    cSortTriple* pNew;
    if (nCapacity == 0) {
        pNew = 0;
    } else {
        pNew = (cSortTriple*)operator_new((uint32_t)(nCapacity * 0xc), gSimulatorName, 0, 0,
                                          gAllocatorFile, 0xd1);
    }
    cSortTriple* pSlot = (cSortTriple*)FUN_00ba7960(mpBegin, pPosition, pNew);
    if (pSlot) *pSlot = *pValue;
    cSortTriple* pNewEnd = (cSortTriple*)FUN_00ba7960(pPosition, mpEnd, pSlot + 1);
    delete[] (int*)mpBegin;
    mpBegin = pNew;
    mpEnd = pNewEnd;
    mpCapacityEnd = (cSortTriple*)((char*)pNew + (uint32_t)nCapacity * 0xc);
}

// ---- 0x00baa730 -----------------------------------------------------------
void* FUN_00ba96e0(void* pBegin, void* pEnd);                           // 0x00ba96e0
void FUN_00ba9740(void* pBegin, void* pMiddle, void* pEnd, void* pPred); // 0x00ba9740

struct ISortKey {
    virtual void v00(void* pArg);
    uint8_t mPad04[0x24];                                               // +0x04
    int mnKey;                                                          // +0x28
};

// @ 0x00baa730 : quick sort over pointer runs with a median-of-three pivot
void SortKeyChain(ISortKey** pBegin, ISortKey** pEnd, int nDepth, void* pArg)
{
    for (;;) {
        if ((int)(((uint32_t)pEnd - (uint32_t)pBegin) & ~3u) <= 0x70 || nDepth < 1) {
            if (nDepth == 0) FUN_00ba9740(pBegin, pEnd, pEnd, pArg);
            return;
        }
        ISortKey** pMid = pBegin + ((pEnd - pBegin) >> 1);
        ISortKey* pFirst = *pBegin;
        ISortKey* pMiddle = *pMid;
        ISortKey* pLast = *(pEnd - 1);
        ISortKey** pPivot;
        if (pFirst->mnKey < pMiddle->mnKey) {
            if (pLast->mnKey <= pMiddle->mnKey) {
                if (pFirst->mnKey < pLast->mnKey) pPivot = pEnd - 1;
                else pPivot = pBegin;
            } else {
                pPivot = pMid;
            }
        } else {
            if (pLast->mnKey <= pFirst->mnKey) {
                if (pMiddle->mnKey < pLast->mnKey) pPivot = pEnd - 1;
                else pPivot = pMid;
            } else {
                pPivot = pBegin;
            }
        }
        ISortKey* pItem = *pPivot;
        if (pItem) pItem->v00(pArg);
        ISortKey** pSplit = (ISortKey**)FUN_00ba96e0(pBegin, pEnd);
        nDepth--;
        SortKeyChain(pSplit, pEnd, nDepth, pArg);
        pEnd = pSplit;
    }
}

// ---- 0x00baa810 -----------------------------------------------------------
// @ 0x00baa810 : partition 12-byte elements around the given predicate
cSortTriple* PartitionTriples(cSortTriple* pFirst, cSortTriple* pLast, cSortTriple value,
                              char (*pPredicate)(const cSortTriple*, const cSortTriple*))
{
    for (;;) {
        while (pPredicate(pFirst, &value)) ++pFirst;
        --pLast;
        while (pPredicate(&value, pLast)) --pLast;
        if (pFirst >= pLast) return pFirst;
        cSortTriple saved = *pFirst;
        *pFirst = *pLast;
        *pLast = saved;
        ++pFirst;
    }
}
