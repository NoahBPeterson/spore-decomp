// Slice s006755c0: SP save/load subjects, uint32 hash maps (eastl::hashtable),
// property lookups, and Pollen response helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

typedef unsigned int uint32_t;
void* operator new(unsigned int, void*);

void EAFree(void* p);                                                            // 0x00F47380
void* EAAllocate(unsigned int n, const char* name, int a, int b, const char* file, int line); // 0x00F473A0

// Names handed to the EA allocator by every container in this slice.
static const char* const kpEditorAllocName = (const char*)0x013EB430;   // ?kEditorAllocName@@3QBDB
static const char* const kpEastlAllocatorFile = (const char*)0x013EBB38; // ".../EASTL/allocator.h"

// Result of eastl::hashtable::DoInsertValue.
struct HashInsertResult {
    void* mpNode;     // +0x00
    void* mpBucket;   // +0x04
    char  mbInserted; // +0x08
};
// Result of eastl::prime_rehash_policy::get_next_bucket_count.
struct RehashResult {
    char     mbNeedsRehash;  // +0x00
    uint32_t mnNewCount;     // +0x04
};
struct PrimeRehashPolicy {
    // (out, nBucketCount, nElementCount, nMinBuckets) - out is the first stack slot.
    void GetNextBucketCount(RehashResult* pOut, uint32_t nBucketCount, uint32_t nElemCount,
                            int nMinBuckets);           // 0x00921440
};

// ---------------------------------------------------------------------------
// eastl::hashtable<uint32_t,uint32_t,eastl::allocator,...> (0x20 bytes)
// ---------------------------------------------------------------------------
extern void* gpEmptyBucketArray[2];   // 0x0154DF28

struct UIntHashTable {
    char     mPad00[4];       // +0x00  use_first/equal_to/hash/mod_range_hashing
    void**   mpBucketArray;   // +0x04
    uint32_t mnBucketCount;   // +0x08
    uint32_t mnElementCount;  // +0x0c
    float    mfMaxLoadFactor; // +0x10
    float    mfGrowthFactor;  // +0x14
    uint32_t mnNextResize;    // +0x18
    char     mAllocator[4];   // +0x1c

    void DoFreeNodes(void** pNodeArray, uint32_t n);   // 0x006B6570
    void rehash(uint32_t nNewBucketCount);             // 0x00675650
    // Returns pResult (the original leaves it in eax) - 0x006758A0
    HashInsertResult* DoInsertValue(HashInsertResult* pResult, const uint32_t* pKey, bool bHint);

    // eastl::hashtable default construction (the allocator member is left as-is).
    void init()
    {
        mfMaxLoadFactor = 1.0f;
        mfGrowthFactor  = 2.0f;
        mnElementCount  = 0;
        mnNextResize    = 0;
        mnBucketCount   = 1;
        mpBucketArray   = &gpEmptyBucketArray[0];
    }

    void reset()
    {
        mnBucketCount  = 1;
        mpBucketArray  = &gpEmptyBucketArray[0];
        mnElementCount = 0;
        mnNextResize   = 0;
    }
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    ~UIntHashTable()
    {
        clear();
        if (mnBucketCount > 1)
            EAFree(mpBucketArray);
    }
};

// @ 0x00675770
void __fastcall FUN_00675770(UIntHashTable* pThis)
{
    pThis->clear();
}

// Four consecutive 0x20-byte uint hash maps (offsets 0x00,0x20,0x40,0x60).
struct FourHashMaps {
    UIntHashTable m0;   // +0x00
    UIntHashTable m1;   // +0x20
    UIntHashTable m2;   // +0x40
    UIntHashTable m3;   // +0x60
    ~FourHashMaps();
};

// @ 0x00675CC0
FourHashMaps::~FourHashMaps() {}

// ---------------------------------------------------------------------------
// Save/load subject used by 0x6755C0.
// ---------------------------------------------------------------------------
struct ISaveStream;

struct SaveSubject {
    char  mPad00[0x24];
    char  mFlag24;      // +0x24
    char  mPad25[3];

    char FUN_006754D0();                    // 0x006754D0 (bool)
    char FUN_00675440(ISaveStream* p);      // 0x00675440 (bool)
    int  FUN_006755C0(ISaveStream* p);
};

// @ 0x006755C0
int SaveSubject::FUN_006755C0(ISaveStream* p)
{
    char cVar1 = FUN_006754D0();
    uint32_t local = (mFlag24 != 0);
    (*(void(__thiscall**)(ISaveStream*, uint32_t*, int))(*(void***)p + 0x38 / 4))(p, &local, 4);
    char cVar2 = FUN_00675440(p);
    if ((cVar2 != 0) && (cVar1 != 0))
        return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// Global object pointer teardown.
// ---------------------------------------------------------------------------
struct GlobalObject {
    virtual void v0(int);
    virtual void v1(int);
    void FUN_006753A0();          // 0x006753A0
};
extern GlobalObject* g_pGlobalObject;            // 0x015FC250

// @ 0x00675620
void FUN_00675620()
{
    if (g_pGlobalObject) {
        g_pGlobalObject->FUN_006753A0();
        if (g_pGlobalObject) {
            g_pGlobalObject->v0(1);
        }
    }
}

// ---------------------------------------------------------------------------
// Property queries.
// ---------------------------------------------------------------------------
struct PropertyList {
    virtual void v0();
    virtual void Release();                                          // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, struct Property** out);    // +0x24
};
struct Property {
    char mPad00[0x12];
    uint16_t mType;   // +0x12
    char* GetBool();  // 0x0041E920
};
struct PropertyManager_ {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0A();
    virtual void GetPropertyListEx(uint32_t a, uint32_t b, PropertyList** out);  // +0x2C
};
PropertyManager_* __stdcall PropertyManager();   // 0x0067DE30

// @ 0x00675700
bool __stdcall FUN_00675700(uint32_t a)   // retail returns with `ret 4`
{
    PropertyList* props = 0;
    PropertyManager_* pm = PropertyManager();
    pm->GetPropertyListEx(a, 0x5befd27, &props);
    char result = 0;
    if (props) {
        Property* prop = 0;
        if (props->GetProperty(0x5bef2cd, &prop) && prop->mType == 1) {
            result = *prop->GetBool();
        }
        props->Release();
    }
    return result;
}

// ---------------------------------------------------------------------------
// Property writer / stream interfaces (slot order from the retail call sites).
// ---------------------------------------------------------------------------
struct IPropStream {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05();
    virtual void* GetStream();                                 // +0x18
};

struct IPropWriter {
    virtual bool Begin(const wchar_t* pName);                  // +0x00
    virtual bool End(const wchar_t* pName);                    // +0x04
    virtual bool Attr(const wchar_t* pName, const wchar_t* pValue);  // +0x08
    virtual bool Text(const wchar_t* pText);                   // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void NextEntry();                                  // +0x1c
    virtual IPropStream* GetWriter();                          // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual bool ReadProp(void* pData, int nSize);             // +0x38
};

// ---- external callees -----------------------------------------------------
void      __cdecl EA_IO_WriteUint32(void* pStream, const void* pValue, int nCount, int nFlags);  // 0x0093AA70
void      __cdecl EA_IO_ReadInt32(void* pStream, void* pValue, int nCount, int nFlags);          // 0x0093A780
uint32_t* __cdecl LowerBoundU32(uint32_t* pFirst, uint32_t* pLast, const uint32_t* pValue,
                                unsigned char bFlag);                                            // 0x00555A20
struct Elem16;
Elem16*   __cdecl UninitialisedCopy16(Elem16* pFirst, Elem16* pLast, Elem16* pDest);             // 0x00C7EA30
void      __cdecl CopyBackward16(Elem16* pFirst, Elem16* pLast, Elem16* pDest);                  // 0x00EDBA80

// ---------------------------------------------------------------------------
// eastl::vector<...>::DoInsertValue over 0x10-byte elements.
// ---------------------------------------------------------------------------
struct Elem16 {
    uint32_t m0;   // +0x00
    uint32_t m4;   // +0x04
    uint32_t m8;   // +0x08
    uint32_t mC;   // +0x0c
};
struct Elem16Vec {
    Elem16* mpBegin;   // +0x00
    Elem16* mpEnd;     // +0x04
    Elem16* mpCap;     // +0x08
    Elem16* insert(Elem16* pPos, const Elem16* pValue);            // 0x00676370
    void    DoInsertValue(Elem16* pPos, const Elem16* pValue);     // 0x00675B90
};

// ---------------------------------------------------------------------------
// eastl::vector<uint32_t> (save-area id lists).
// ---------------------------------------------------------------------------
struct U32Vec {
    uint32_t* mpBegin;   // +0x00
    uint32_t* mpEnd;     // +0x04
    uint32_t* mpCap;     // +0x08
    void DoInsertValue(uint32_t* pPos, const uint32_t* pValue);   // 0x005481D0
};

// ---------------------------------------------------------------------------
// Sorted uint32 list held at +0x24 of a save/load subject.
// ---------------------------------------------------------------------------
struct SortedU32List {
    char       mPad00[0x24];
    uint32_t*  mpBegin;     // +0x24
    uint32_t*  mpEnd;       // +0x28
    char       mPad2c[0x0c];
    char       mbSorted;    // +0x38 (true: the list is kept sorted)
};
struct SortedListOwner {
    char            mPad00[0x08];
    SortedU32List*  mpList;   // +0x08
};

// ---------------------------------------------------------------------------
// eastl::basic_string<wchar_t, eastl::allocator> and its EA conversions.
// ---------------------------------------------------------------------------
extern wchar_t gEmptyString16[];       // 0x01667BAC  eastl::gEmptyString16
struct TWString {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08
    int      mAlloc;    // +0x0c
    TWString* Clone(const TWString* pOther);          // 0x0056E2D0 (copy ctor)
    void      RangeInitialize(const wchar_t* pFirst); // 0x00579A90
    // eastl::basic_string destructor: release everything but the shared empty buffer.
    void Release()
    {
        if ((unsigned)((char*)mpCap - (char*)mpBegin) > 2 && mpBegin != 0)
            EAFree(mpBegin);
    }
};
TWString* __cdecl ConvertToString16W(TWString* pOut, const char* pSrc, int nLen);          // 0x0093C5A0
TWString* __cdecl ConvertToString16FromW(TWString* pOut, const TWString* pSrc);             // 0x0093C6D0
void      __cdecl TypedValueToString16(TWString* pOut, const void* pValue);                 // 0x00694F00
extern wchar_t gEmptyEntryName[];      // 0x014011D0
extern char    g_bWriteTypeAttribute;  // 0x015D8B51

// 0x00694F00 formats `pValue` as text; every caller in this slice then streams it.
bool __cdecl FUN_00675990(IPropWriter* pWriter, const char* pText, const void* pValue,
                          const wchar_t* pType);

// ---------------------------------------------------------------------------
// 0x00675790 : serialize a uint32 -> uint32 hash table.
//   uint32 count; { uint32 key; } * count
// ---------------------------------------------------------------------------
// @ 0x00675790
void __cdecl FUN_00675790(IPropWriter* pWriter, UIntHashTable* pMap)
{
    uint32_t nCount = pMap->mnElementCount;
    EA_IO_WriteUint32(pWriter->GetWriter()->GetStream(), &nCount, 1, 0);

    uint32_t** ppBuckets = (uint32_t**)pMap->mpBucketArray;
    uint32_t*  pNode     = ppBuckets[0];
    uint32_t** ppScan    = ppBuckets;
    if (pNode == 0) {
        do { ++ppScan; } while (*ppScan == 0);
        pNode = (uint32_t*)*ppScan;
    }
    uint32_t* pEnd = (uint32_t*)ppBuckets[pMap->mnBucketCount];
    while (pNode != pEnd) {
        EA_IO_WriteUint32(pWriter->GetWriter()->GetStream(), pNode, 1, 0);
        pWriter->NextEntry();
        pNode = (uint32_t*)pNode[1];
        if (pNode == 0) {
            do { ++ppScan; } while (*ppScan == 0);
            pNode = (uint32_t*)*ppScan;
        }
    }
    pWriter->NextEntry();
}

// ---------------------------------------------------------------------------
// 0x006758A0 : eastl::hashtable<uint32_t,uint32_t>::DoInsertValue
// ---------------------------------------------------------------------------
// @ 0x006758A0
HashInsertResult* UIntHashTable::DoInsertValue(HashInsertResult* pResult, const uint32_t* pKey,
                                               bool)
{
    uint32_t nKey         = *pKey;
    uint32_t nBucketCount = mnBucketCount;
    uint32_t nIndex       = nKey % nBucketCount;
    uint32_t** ppBucket   = (uint32_t**)mpBucketArray + nIndex;
    uint32_t* pNode       = *ppBucket;
    while (pNode != 0) {
        if (pNode[0] == nKey) {
            pResult->mpNode     = pNode;
            pResult->mpBucket   = ppBucket;
            pResult->mbInserted = 0;
            return pResult;    // the original leaves the insert result in eax
        }
        pNode = (uint32_t*)pNode[1];
    }

    RehashResult rehashResult;
    ((PrimeRehashPolicy*)(void*)((char*)this + 0x10))->GetNextBucketCount(&rehashResult, nBucketCount, mnElementCount, 1);

    uint32_t* pNew = (uint32_t*)EAAllocate(8, kpEditorAllocName, 0, 0, kpEastlAllocatorFile, 0xd1);
    if (pNew != 0)
        pNew[0] = nKey;
    pNew[1] = 0;

    if (rehashResult.mbNeedsRehash != 0) {
        nIndex = nKey % rehashResult.mnNewCount;
        rehash(rehashResult.mnNewCount);
    }

    uint32_t** ppBase = (uint32_t**)mpBucketArray;
    pNew[1]           = (uint32_t)ppBase[nIndex];
    ppBase[nIndex]    = pNew;
    ++mnElementCount;

    pResult->mpNode     = pNew;
    pResult->mpBucket   = &ppBase[nIndex];
    pResult->mbInserted = 1;
    return pResult;
}

// ---------------------------------------------------------------------------
// 0x00675990 : stream one typed value as a property entry.
//   Begin(value text or type) [Attr(L"type", type)] Text(text) End(...)
// ---------------------------------------------------------------------------
// @ 0x00675990
bool __cdecl FUN_00675990(IPropWriter* pWriter, const char* pText, const void* pValue,
                          const wchar_t* pType)
{
    TWString strValue;                                  // formatted value
    strValue.mpBegin = gEmptyString16;                  // the retail empty-string triple: the capacity
    strValue.mpEnd   = gEmptyString16;                  //   sentinel sits one *byte* past the buffer
    strValue.mpCap   = (wchar_t*)((char*)gEmptyString16 + 1);
    strValue.mAlloc  = 0;
    TypedValueToString16(&strValue, pValue);
    if (strValue.mpBegin == strValue.mpEnd) {
        strValue.Release();
        return true;
    }

    // Entry name: widen the caller's text into a temporary, then copy-construct the real string.
    TWString strTemp;
    if (pText != 0) {
        ConvertToString16W(&strTemp, pText, -1);
    } else {
        strTemp.mpBegin = gEmptyString16;
        strTemp.mpEnd   = gEmptyString16;
        strTemp.mpCap   = gEmptyString16 + 1;
        strTemp.mAlloc  = 0;
    }
    TWString strName;
    strName.Clone(&strTemp);
    strTemp.Release();

    TWString strText;                                   // entry text: the formatted value
    ConvertToString16FromW(&strText, &strValue);

    // Every writer call is folded back to 0/1, like the original's explicit setne/xor pairs.
    bool bResult;
    if (strName.mpBegin == strName.mpEnd) {
        bResult = pWriter->Begin(pType) != 0;
    } else {
        bResult = pWriter->Begin(strName.mpBegin) != 0;
        if (bResult && g_bWriteTypeAttribute != 0)
            bResult = pWriter->Attr(L"type", pType) != 0;
    }
    if (bResult)
        bResult = pWriter->Text(strText.mpBegin) != 0;
    if (bResult)
        bResult = pWriter->End((strName.mpBegin == strName.mpEnd) ? pType : strName.mpBegin) != 0;

    strText.Release();
    strName.Release();
    strValue.Release();
    return bResult;
}

// ---------------------------------------------------------------------------
// 0x00675B90 : eastl::vector<T>::DoInsertValue for 0x10-byte elements.
// ---------------------------------------------------------------------------
// @ 0x00675B90
void Elem16Vec::DoInsertValue(Elem16* pPos, const Elem16* pValue)
{
    if (mpEnd != mpCap) {
        Elem16*       pLast = mpEnd;
        const Elem16* pSrc  = pValue;
        if ((unsigned)pSrc >= (unsigned)pPos && (unsigned)pSrc < (unsigned)mpEnd)
            ++pSrc;
        if (pLast != 0)
            *pLast = *(mpEnd - 1);
        CopyBackward16(pPos, mpEnd - 1, mpEnd);
        *pPos = *pSrc;
        ++mpEnd;
        return;
    }

    unsigned nSize = (unsigned)(mpEnd - mpBegin);
    unsigned nNewSize = (nSize != 0) ? nSize * 2 : 1;
    Elem16*  pNewBegin = 0;
    if (nNewSize != 0)
        pNewBegin = (Elem16*)EAAllocate(nNewSize * 0x10, kpEditorAllocName, 0, 0,
                                        kpEastlAllocatorFile, 0xd1);

    Elem16* pMid = UninitialisedCopy16(mpBegin, pPos, pNewBegin);
    if (pMid != 0)
        *pMid = *pValue;
    Elem16* pNewEnd = UninitialisedCopy16(pPos, mpEnd, pMid + 1);

    if (mpBegin != 0)
        EAFree(mpBegin);
    mpEnd   = pNewEnd;
    mpCap   = pNewBegin + nNewSize;
    mpBegin = pNewBegin;
}

// ---------------------------------------------------------------------------
// 0x00675D70 : constructor of the 0xbc-byte save/load subject (four hash maps
// at +0x3c).
// ---------------------------------------------------------------------------
struct SubjectA {
    void*        mpVtbl0;    // +0x00
    void*        mpVtbl1;    // +0x04
    uint32_t     mu08;       // +0x08
    uint32_t     mu0c;       // +0x0c  block freed with EAFree
    uint32_t     mu10;       // +0x10
    uint32_t     mu14;       // +0x14
    uint32_t     mu18;       // +0x18  untouched by the constructor
    uint32_t     mu1c;       // +0x1c
    uint32_t     mu20;       // +0x20
    uint32_t     mu24;       // +0x24  block freed with EAFree
    uint32_t     mu28;       // +0x28
    uint32_t     mu2c;       // +0x2c
    uint32_t     mu30;       // +0x30  untouched by the constructor
    uint32_t     mu34;       // +0x34
    uint32_t     mu38;       // +0x38
    FourHashMaps mMaps;      // +0x3c
    SubjectA* Ctor();        // 0x00675D70
};

// @ 0x00675D70
SubjectA* __fastcall FUN_00675d70(SubjectA* pThis)
{
    // The IEventModifier base constructor installs its own vtable first; it is then
    // replaced by the derived table below.
    *(void* volatile*)&pThis->mpVtbl1 = (void*)0x013EF094;    // SP::Audio::IEventModifier vtable
    pThis->mu08    = 0;
    pThis->mpVtbl0 = (void*)0x01401178;
    pThis->mpVtbl1 = (void*)0x01401174;
    pThis->mu0c    = 0;
    pThis->mu10    = 0;
    pThis->mu14    = 0;
    pThis->mu24    = 0;
    pThis->mu28    = 0;
    pThis->mu2c    = 0;
    pThis->mMaps.m0.init();
    pThis->mMaps.m1.init();
    pThis->mMaps.m2.init();
    pThis->mMaps.m3.init();
    return pThis;
}

// ---------------------------------------------------------------------------
// 0x00675E80 : does the subject's sorted id list contain `nKey`?
// ---------------------------------------------------------------------------
// @ 0x00675E80
bool __fastcall FUN_00675e80(SortedListOwner* pThis, int, uint32_t nKey)
{
    SortedU32List* pList = pThis->mpList;
    uint32_t*      pLast = pList->mpEnd;
    uint32_t*      pFound = LowerBoundU32(pList->mpBegin, pLast, &nKey, (unsigned char)pList->mbSorted);
    if (pFound == pLast || nKey < *pFound)
        pFound = pLast;
    return pFound != pLast;
}

// ---------------------------------------------------------------------------
// 0x00675ED0 : load the subject's payload from the "Simulator" save area.
// ---------------------------------------------------------------------------
struct cObjectDatabase {
    virtual void v0();   // +0x00
    virtual void v1();   // +0x04
};
struct SaveAreaHolder {                                  // Holder in the save-area code
    uint32_t mu00;   // +0x00
    uint32_t mu04;   // +0x04
    uint32_t mu08;   // +0x08
    uint32_t mu0c;   // +0x0c
    bool     Bind(cObjectDatabase* pDatabase, void* pKey);   // 0x0069E090
    bool     Reset();                                       // 0x0069D480
};
struct SaveAreaScope {                                   // 0x0069E040 / 0x0069D400
    uint32_t       mu00;      // +0x00
    uint32_t       mu04;      // +0x04
    SaveAreaHolder mHolder;   // +0x08
    SaveAreaScope* Init();    // 0x0069E040
    void           Destroy(); // 0x0069D400
};
struct LoadableSubject {
    virtual void* v00();  virtual void* v04();  virtual void* v08();  virtual void* v0c();
    virtual void* v10();  virtual char  LoadFrom(SaveAreaHolder* pHolder);   // +0x14
};
struct SaveSession {
    char         mPad00[0x08];
    LoadableSubject* mpSubject;   // +0x08
};
void*     __cdecl SP_GetSaveArea(void* pKey);                    // 0x006B1F90
void*     __cdecl ZoneObjectNew(unsigned nSize, const char* pName,
                                int a, int b, int c, int d);     // 0x00926020
cObjectDatabase* __cdecl ObjectDatabaseCtor(cObjectDatabase* pThis, void* pArea);  // 0x0069FA60
extern char gSaveAreaDatabaseKey;   // 0x01529498

// @ 0x00675ED0
char __fastcall FUN_00675ed0(SaveSession* pThis)
{
    void* pArea = SP_GetSaveArea((void*)0x011AC19C);
    cObjectDatabase* pDatabase =
        (cObjectDatabase*)ZoneObjectNew(0x24, "Simulator", 0, 0, 0, 0);
    if (pDatabase != 0) {
        ObjectDatabaseCtor(pDatabase, pArea);
        pDatabase->v0();
    }

    SaveAreaScope scope;
    scope.Init();
    if (!scope.mHolder.Bind(pDatabase, &gSaveAreaDatabaseKey)) {
        scope.Destroy();
        if (pDatabase != 0)
            pDatabase->v1();
        return 0;
    }

    char bLoaded = pThis->mpSubject->LoadFrom(&scope.mHolder);
    if (bLoaded == 0) {
        SubjectA* pNew = 0;
        void* pRaw = ZoneObjectNew(0xbc, "Simulator", 0, 0, 0, 0);
        if (pRaw != 0)
            pNew = FUN_00675d70((SubjectA*)pRaw);
        LoadableSubject* pOld = pThis->mpSubject;
        if ((LoadableSubject*)pNew != pOld) {
            if (pNew != 0)
                ((LoadableSubject*)pNew)->v00();
            pThis->mpSubject = (LoadableSubject*)pNew;
            if (pOld != 0)
                pOld->v04();
        }
    }

    scope.mHolder.Reset();
    scope.Destroy();
    if (pDatabase != 0)
        pDatabase->v1();
    return bLoaded;
}

// ---------------------------------------------------------------------------
// 0x00675FF0 : stream a uint32 id list as a property entry.
// ---------------------------------------------------------------------------
// @ 0x00675FF0
bool __cdecl FUN_00675ff0(IPropWriter* pWriter, const char* pName, U32Vec* pVec)
{
    bool bResult = true;
    if (pVec->mpBegin == pVec->mpEnd)
        return bResult;

    // Name: widen into a temporary, then copy-construct the string the entry is written with.
    TWString strTemp;
    if (pName != 0) {
        ConvertToString16W(&strTemp, pName, -1);
    } else {
        strTemp.mpBegin = 0;
        strTemp.mpEnd   = 0;
        strTemp.mpCap   = 0;
        strTemp.mAlloc  = 0;
        strTemp.RangeInitialize(0);
    }
    TWString strName;
    strName.Clone(&strTemp);
    strTemp.Release();
    const wchar_t* pName16 = (strName.mpBegin != strName.mpEnd) ? strName.mpBegin : gEmptyEntryName;

    pWriter->Begin(pName16);
    for (uint32_t* p = pVec->mpBegin; p != pVec->mpEnd; ++p) {
        if (bResult)
            bResult = FUN_00675990(pWriter, 0, p, L"uint32_t");
    }
    pWriter->End(pName16);
    strName.Release();
    return bResult;
}

// ---------------------------------------------------------------------------
// 0x00676140 : read a uint32 -> uint32 hash table back in.
// ---------------------------------------------------------------------------
// @ 0x00676140
void __cdecl FUN_00676140(IPropWriter* pWriter, UIntHashTable* pMap)
{
    pMap->clear();

    uint32_t nCount = 0;
    EA_IO_ReadInt32(pWriter->GetWriter()->GetStream(), &nCount, 1, 0);
    for (uint32_t i = 0; i < nCount; ++i) {
        uint32_t nValue = 0;
        EA_IO_ReadInt32(pWriter->GetWriter()->GetStream(), &nValue, 1, 0);
        pWriter->NextEntry();
        HashInsertResult result;
        pMap->DoInsertValue(&result, &nValue, false);
    }
    pWriter->NextEntry();
}

// ---------------------------------------------------------------------------
// 0x006761F0 : stream a uint32 -> uint32 hash table as a property entry.
// ---------------------------------------------------------------------------
// @ 0x006761F0
bool __cdecl FUN_006761f0(IPropWriter* pWriter, const char* pName, UIntHashTable* pMap)
{
    bool bResult = true;
    if (pMap->mnElementCount == 0)
        return bResult;

    TWString strTemp;
    if (pName != 0) {
        ConvertToString16W(&strTemp, pName, -1);
    } else {
        strTemp.mpBegin = 0;
        strTemp.mpEnd   = 0;
        strTemp.mpCap   = 0;
        strTemp.mAlloc  = 0;
        strTemp.RangeInitialize(0);
    }
    TWString strName;
    strName.Clone(&strTemp);
    strTemp.Release();
    const wchar_t* pName16 = (strName.mpBegin != strName.mpEnd) ? strName.mpBegin : gEmptyEntryName;

    pWriter->Begin(pName16);

    uint32_t** ppBuckets = (uint32_t**)pMap->mpBucketArray;
    uint32_t*  pNode     = ppBuckets[0];
    uint32_t** ppScan    = ppBuckets;
    if (pNode == 0) {
        do { ++ppScan; } while (*ppScan == 0);
        pNode = (uint32_t*)*ppScan;
    }
    uint32_t* pEnd = (uint32_t*)ppBuckets[pMap->mnBucketCount];
    while (pNode != pEnd) {
        if (bResult)
            bResult = FUN_00675990(pWriter, 0, pNode, L"uint32_t");
        pNode = (uint32_t*)pNode[1];
        if (pNode == 0) {
            do { ++ppScan; } while (*ppScan == 0);
            pNode = (uint32_t*)*ppScan;
        }
    }

    pWriter->End(pName16);
    strName.Release();
    return bResult;
}

// ---------------------------------------------------------------------------
// 0x00676370 : eastl::vector<pair<wchar_t const*, ...>>::insert
// ---------------------------------------------------------------------------
// @ 0x00676370
Elem16* Elem16Vec::insert(Elem16* pPos, const Elem16* pValue)
{
    int nIndex = (int)(pPos - mpBegin);
    if (pPos == mpEnd && mpEnd != mpCap) {
        Elem16* pNew = mpEnd;
        mpEnd = pNew + 1;
        if (pNew != 0)
            *pNew = *pValue;
    } else {
        DoInsertValue(pPos, pValue);
    }
    return mpBegin + nIndex;
}

// ---------------------------------------------------------------------------
// 0x006763E0 : constructor of the 0xac-byte save/load subject (four hash maps
// at +0x28).
// ---------------------------------------------------------------------------
struct VObject {
    virtual void v0();   // +0x00
    virtual void v1();   // +0x04
    virtual void v2();   // +0x08
};
struct SubjectB {
    void*        mpVtbl;  // +0x00
    VObject*     mp04;    // +0x04
    VObject*     mp08;    // +0x08
    void*        mp0c;    // +0x0c  block freed with EAFree
    uint32_t     mu10;    // +0x10
    uint32_t     mu14;    // +0x14
    uint32_t     mu18;    // +0x18  untouched by the constructor
    uint32_t     mu1c;    // +0x1c
    uint32_t     mu20;    // +0x20
    char         mb24;    // +0x24
    char         mPad25[3];
    FourHashMaps mMaps;   // +0x28
};

// @ 0x006763E0
SubjectB* __fastcall FUN_006763e0(SubjectB* pThis)
{
    pThis->mpVtbl = (void*)0x0140116C;
    pThis->mp04   = 0;
    pThis->mp08   = 0;
    pThis->mp0c   = 0;
    pThis->mu10   = 0;
    pThis->mu14   = 0;
    pThis->mb24   = 0;
    pThis->mMaps.m0.init();
    pThis->mMaps.m1.init();
    pThis->mMaps.m2.init();
    pThis->mMaps.m3.init();
    return pThis;
}

// ---------------------------------------------------------------------------
// 0x00676490 : deleting destructor for SubjectB.
// ---------------------------------------------------------------------------
// @ 0x00676490
void* __fastcall FUN_00676490(SubjectB* pThis, int, int nFlags)
{
    pThis->mpVtbl = (void*)0x0140116C;
    pThis->mMaps.~FourHashMaps();
    if (pThis->mp0c != 0)
        EAFree(pThis->mp0c);
    if (pThis->mp08 != 0)
        pThis->mp08->v1();
    if (pThis->mp04 != 0)
        pThis->mp04->v2();
    pThis->mpVtbl = (void*)0x013EB394;
    if ((nFlags & 1) != 0)
        EAFree(pThis);
    return pThis;
}

// ---------------------------------------------------------------------------
// 0x006764F0 : deleting destructor for SubjectA.
// ---------------------------------------------------------------------------
// @ 0x006764F0
void* __fastcall FUN_006764f0(SubjectA* pThis, int, int nFlags)
{
    pThis->mMaps.~FourHashMaps();
    if (pThis->mu24 != 0)
        EAFree((void*)pThis->mu24);
    if (pThis->mu0c != 0)
        EAFree((void*)pThis->mu0c);
    pThis->mpVtbl1 = (void*)0x013EF094;
    pThis->mpVtbl0 = (void*)0x013EB938;
    if ((nFlags & 1) != 0)
        EAFree(pThis);
    return pThis;
}

// ---------------------------------------------------------------------------
// 0x00676540 : read a sorted uint32 list back in.
// ---------------------------------------------------------------------------
// @ 0x00676540
void __cdecl FUN_00676540(IPropWriter* pWriter, U32Vec* pVec)
{
    pVec->mpEnd = pVec->mpBegin;

    uint32_t nCount = 0;
    EA_IO_ReadInt32(pWriter->GetWriter()->GetStream(), &nCount, 1, 0);
    for (uint32_t i = 0; i < nCount; ++i) {
        uint32_t nValue = 0;
        EA_IO_ReadInt32(pWriter->GetWriter()->GetStream(), &nValue, 1, 0);
        pWriter->NextEntry();

        // eastl::lower_bound over the sorted list.
        uint32_t* pInsert = pVec->mpBegin;
        int       nLen    = (int)(pVec->mpEnd - pInsert);
        while (nLen > 0) {
            int nHalf = nLen >> 1;
            uint32_t* pMid = pInsert + nHalf;
            if (*pMid < nValue) {
                pInsert = pMid + 1;
                nLen -= nHalf + 1;
            } else {
                nLen = nHalf;
            }
        }
        if (pInsert == pVec->mpEnd) {
            if (pVec->mpEnd == pVec->mpCap) {
                pVec->DoInsertValue(pInsert, &nValue);
            } else {
                *pVec->mpEnd = nValue;
                ++pVec->mpEnd;
            }
        } else if (nValue < *pInsert) {
            pVec->DoInsertValue(pInsert, &nValue);
        }
    }
    pWriter->NextEntry();
}
