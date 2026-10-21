// Slice s008e0eb0 (0x8e0eb0..0x8e1aea) - EA::ResourceMan::Manager: the key-name / typename
// hash maps, the type-factory map erase helpers, the InternalDatabaseList vector helpers,
// SetKeyName/ForgetKeyName/SetTypename/ResetTypename, Shutdown and RegisterFactory.
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE

#include <string.h>
#include <new>

typedef unsigned int   uint32;
typedef int            int32;
typedef unsigned char  uint8;
typedef unsigned short uint16;

namespace EA {

namespace Thread {
// thiscall; the callee pops its arguments.
class Mutex { public:
    char mData[0x30];
    void Lock(const char* pName);   // 0x009221B0
    int  Unlock();                  // 0x00922270
};
}  // namespace Thread

// A plain EA allocator interface: +0x08 Allocate, +0x0c Free.
struct Alloc {
    virtual void* s0();
    virtual void* s1();
    virtual void* Allocate(uint32 nSize, int a, const char* pName);   // +0x08
    virtual void  Free(void* p, uint32 nSize);                        // +0x0c
};

namespace ResourceMan {

class Key { public:
    uint32 mInstance;   // +0x00
    uint32 mType;       // +0x04
    uint32 mGroup;      // +0x08
};

// eastl::basic_string<wchar_t> (3-pointer representation).
struct WString {
    void* mpBegin;  // +0x00
    void* mpEnd;    // +0x04
    void* mpCap;    // +0x08

    WString* assign(const void* pBegin, const void* pEnd);   // 0x00423650
};

// An AutoRefCount<T> payload (pointer + user field), an 8-byte vector element.
struct AutoRefObj {
    void* mpObject;     // +0x00
    int   mField;       // +0x04
};

// A vector of AutoRefObj (5-pointer eastl vector of 8-byte elements).
struct AutoRefVec {
    AutoRefObj* mpBegin;      // +0x00
    AutoRefObj* mpEnd;        // +0x04
    AutoRefObj* mpCap;        // +0x08
    void*       mpAllocator;  // +0x0c
    const char* mpName;       // +0x10

    void*       allocateStorage(int n, void* pAllocPair);                  // 0x008DEF20
    AutoRefObj* insertGrow(AutoRefObj* pPos, const AutoRefObj* pSrc);      // 0x008E1070
    AutoRefObj* insertAt(AutoRefObj* pPos, const AutoRefObj* pSrc);        // 0x008E12C0
    AutoRefObj* pushBack(AutoRefObj* pPos, const AutoRefObj* pSrc);        // 0x008E1690
    void        clearRange(AutoRefObj* pFirst, AutoRefObj* pLast);         // 0x008E1200
};

// Shared header of every node-based eastl::hashtable instantiation in this slice.
struct HashTable {
    uint32 mUnk0;               // +0x00
    void** mpBucketArray;       // +0x04
    uint32 mnBucketCount;       // +0x08
    uint32 mnElementCount;      // +0x0c
    uint32 mRehash[3];          // +0x10
    Alloc* mpAllocator;         // +0x1c
    const char* mpName;         // +0x20

    void** findKey(void** ppOut, const void* pKey);        // 0x008DB3D0
    void** findU32(void** ppOut, const uint32* pKey);      // 0x00A3B2C0
    int    eraseKey(const uint32* pKey);                    // 0x008E0630
    void*  refKey(uint32 nKey);                             // 0x008E0E10
    void*  insertNode20(void* pOut, void* pKey, void* p3);  // 0x008E0390
    void   eraseNode20(void* pOut, const void* pKey);       // 0x008E0FE0
    void   eraseNode1c(void* pOut, const void* pKey);       // 0x008E0F50
    WString* KeyNameOperatorIndex(Key* pKey);               // 0x008E0EB0 (hash_map::operator[])

    void** endIterator() { return mpBucketArray + mnBucketCount; }
};

// A ResourceMan factory: reference-counted COM object with the slots this slice uses.
class Factory { public:
    virtual void Slot00();                                                     // +0x00
    virtual void AddRef();                                                     // +0x04
    virtual void Release();                                                    // +0x08
    virtual int  Slot0C();                                                     // +0x0c
    virtual void Slot10();                                                     // +0x10
    virtual void Slot14();                                                     // +0x14
    virtual void Slot18();
    virtual void Slot1C(void* a, void* b, void* c, void* d);
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual uint32 Slot2C(uint32* pOut, uint32 nCount);                        // +0x2c
    virtual void Slot30(void* a, void* b);
    virtual char Slot34(Key* pKey, void* pTypeParam, int a, int b, int c, int d);
    virtual void Slot38();
    virtual void Slot3C();
    virtual void Slot40();
    virtual char Slot44(int a, void* b, int c);
    virtual void Slot48();
    virtual void Slot4C();
    virtual void Slot50();
    virtual char Slot54(void* a, int b);
    virtual void* Slot58(Key* pKey);
};

// A pair<AutoRefCount<Factory>,int> as stored in the per-type factory vectors.
struct FactorySlot {
    void* mpFactory;   // +0x00 (AutoRefCount<Factory>)
    int   mValue;      // +0x04
};

// Manager compressor array element.
struct Compressor {
    void** vftable;   // +0x00
};

// ---------------------------------------------------------------------------
// Manager
// ---------------------------------------------------------------------------
class Manager { public:
    void** vftable;                     // +0x00
    uint8  mbInitialized;               // +0x04
    char   _pad05[3];
    void*  mpAllocator;                 // +0x08
    uint8  _pad0c[0x20];                // +0x0c change-notification set
    void*  mDatabaseListHead;           // +0x2c
    HashTable mTypeToFactoriesMap;      // +0x30
    HashTable mTypeFactoryMap;          // +0x54
    HashTable mTypeToFactoryArrayMap;   // +0x78
    HashTable mTypenameMap;             // +0x9c
    uint8  _padC0[0x34];                // +0xc0
    HashTable mKeyNameMap;              // +0xf4
    Thread::Mutex mNameMutex;           // +0x118
    uint8  _pad148[0x20];               // +0x148
    Compressor* mpCompressorBegin;      // +0x168
    Compressor* mpCompressorEnd;        // +0x16c

    bool     SetKeyName(Key* pKey, const wchar_t* pName);        // 0x008E1480
    bool     ForgetKeyName(Key* pKey);                           // 0x008E14E0
    bool     SetTypename(uint32 nType, const wchar_t* pName);    // 0x008E1560
    bool     ResetTypename(uint32 nType, const wchar_t* pName);  // 0x008E1610
    int      Shutdown();                                         // 0x008E1700
    void     Fn8e1930(uint32 nKey, uint32* pIds, uint32 nCount); // 0x008E1930
    int      RegisterFactory(char bAdd, Factory* pFactory);      // 0x008E1A50
};

// The Manager::InternalDatabaseList sub-object: a Flush()-able list plus a Node* vector and a
// mutex.  Layout observed in the destructor.
struct InternalDatabaseList {
    uint8       _pad00[0x10];
    Thread::Mutex mMutex;        // +0x10
    uint8       _pad40[0x30];
    void**      mpVecBegin;      // +0x40
    void**      mpVecEnd;        // +0x44
    void**      mpVecCap;        // +0x48
    void*       mpVecAllocator;  // +0x4c
    uint8       _pad50[4];
    uint8       mHashBase[0x24]; // +0x54

    void Flush();               // 0x008E0840
    ~InternalDatabaseList();    // 0x008E1420
};

extern "C" void __cdecl Fn926640(void* p);   // 0x00926640 (hashtable dtor thunk)
extern "C" void __cdecl Fn922130(void* p);   // 0x00922130 (Thread::Mutex::~Mutex)

}  // namespace ResourceMan
}  // namespace EA

using namespace EA;
using namespace EA::ResourceMan;

// ---------------------------------------------------------------------------
// external helpers (bodies live in other translation units)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl EAAllocate(uint32 nSize, const char* pName, int a, int b,
                                    const char* pFile, int nLine);         // 0x00F473A0
extern "C" void  __cdecl EAOperatorDelete(void* p);                        // 0x00F47380
extern "C" AutoRefObj* __cdecl AutoRefMoveBackward(AutoRefObj* first, AutoRefObj* last,
                                                   AutoRefObj* dest);      // 0x008DF050
extern "C" void  __cdecl Fn8de840(AutoRefObj* first, AutoRefObj* last,
                                  AutoRefObj* dest, void* pAlloc);         // 0x008DE840
extern "C" AutoRefObj* __cdecl Fn8de890(AutoRefObj* first, AutoRefObj* last, void* dest); // 0x008DE890
extern "C" void  __cdecl Fn7e18d0(void* a, void* b, void* c);              // 0x007E18D0
extern "C" void  __cdecl Fn8dede0(void* a, void* b);                        // 0x008DEDE0
extern "C" void  __cdecl Fn7e1b00(FactorySlot* first, FactorySlot* last, FactorySlot* dest); // 0x007E1B00
extern "C" void  __cdecl Fn5f8700(void* pOut, void* pKey, void* pStr);      // 0x005F8700
extern "C" void  __cdecl Fn8decb0();                                       // 0x008DECB0
extern "C" bool  __cdecl Fn6ab760(void* pDst, const wchar_t* pSrc);         // 0x006AB760
extern "C" void  __cdecl ClearAutoRefVec(void* pVec, uint32 nBytes);        // 0x008E1200
extern "C" void  __cdecl NodeMapEraseAll(void* pMap);                       // 0x008E1930 parameter path
extern "C" void  __cdecl InsertU32Slot(void* pOut, uint32* pKey, uint32 flags); // 0x008DED00
extern "C" void  __cdecl Fn8e0250(void* pKey, void* pOut);                 // 0x008E0250
extern "C" void  __cdecl FreeString16IfHeap(void* pBegin, void* pEnd);      // inline-reproduced below

extern const wchar_t gEmptyString16[];   // 0x01667BAC

// A small helper matching WString's "free if heap" tail used at several call sites.
static void FreeWStringBuffer(void* pBegin, void* pEnd)
{
    uint32 nBytes = (reinterpret_cast<uint32>(pEnd) - reinterpret_cast<uint32>(pBegin)) & 0xfffffffeu;
    if (nBytes > 2 && pBegin != 0)
        EAOperatorDelete(pBegin);
}

// AutoRefObj copy-assign (0x008DEE30): store the pointer, bump its refcount, copy the value.
extern "C" AutoRefObj* __cdecl CopyAutoRefImpl(AutoRefObj* pDst, const AutoRefObj* pSrc); // 0x008DEE30
static void CopyAutoRef(AutoRefObj* pDst, const AutoRefObj* pSrc)
{
    (void)CopyAutoRefImpl(pDst, pSrc);
}

// Release one intrusive vector node (0x00DEE30-style free of the vector it heads).
static void FreeAutoRefVectorNode(uint8* pNode)
{
    uint8* pBegin = *reinterpret_cast<uint8**>(pNode + 4);
    if (pBegin != 0)
        (*(void (__thiscall**)(uint8*, uint32))((reinterpret_cast<uint8*>(*reinterpret_cast<void**>(pNode + 0xc)) + 0xc)))(
            pBegin, static_cast<uint32>(
                (*reinterpret_cast<uint8**>(pNode + 0xc) - pBegin) >> 3) * 8);
    (*(void (__thiscall**)(uint8*, uint32))((reinterpret_cast<uint8*>(*reinterpret_cast<void**>(pNode + 0x1c)) + 0xc)))(pNode, 0x1c);
}

// Release every factory vector in a type->factories map node list.
static void ClearFactoryMap(HashTable* pMap)
{
    for (void** pBucket = pMap->mpBucketArray; pBucket != pMap->endIterator(); ++pBucket)
    {
        for (uint8* pNode = reinterpret_cast<uint8*>(*pBucket); pNode != 0;
             pNode = *reinterpret_cast<uint8**>(pNode + 0x18))
        {
            FactorySlot* pSlots = *reinterpret_cast<FactorySlot**>(pNode + 4);
            FactorySlot* pEnd   = *reinterpret_cast<FactorySlot**>(pNode + 8);
            for (; pSlots != pEnd; ++pSlots)
            {
                if (pSlots->mpFactory != 0)
                    (*(void (__thiscall**)(void*))((reinterpret_cast<uint8*>(*reinterpret_cast<void**>(pSlots->mpFactory)) + 8)))(pSlots->mpFactory);
            }
        }
    }
}

// Walk the change-notification list, releasing each still-live entry.
static void FreeChangeList(void* pHead)
{
    for (uint8* p = reinterpret_cast<uint8*>(pHead); p != 0; p = *reinterpret_cast<uint8**>(p))
    {
        uint8* pObj = *reinterpret_cast<uint8**>(p + 4);
        int bLive = (*(int (__thiscall**)(uint8*))((reinterpret_cast<uint8*>(*reinterpret_cast<void**>(pObj)) + 0x10)))(pObj);
        if (bLive != 0)
            (*(void (__thiscall**)(uint8*))((reinterpret_cast<uint8*>(*reinterpret_cast<void**>(pObj)) + 8)))(pObj);
    }
}

// ===========================================================================
// @ 0x008E0EB0
// ===========================================================================
WString* HashTable::KeyNameOperatorIndex(Key* pKey)
{
    void* pFound = 0;
    findKey(&pFound, pKey);

    if (pFound != *endIterator())
        return reinterpret_cast<WString*>(reinterpret_cast<uint8*>(pFound) + 0xc);

    // Not present: build the node's pair from an empty string and insert it.
    uint8 pair[0x14];
    WString empty;
    empty.mpBegin = const_cast<wchar_t*>(gEmptyString16);
    empty.mpEnd   = const_cast<wchar_t*>(gEmptyString16);
    empty.mpCap   = const_cast<wchar_t*>(gEmptyString16 + 1);
    Fn5f8700(pair, pKey, &empty);

    uint8 out[0xc];
    insertNode20(out, pair, 0);

    void* pBegin = *reinterpret_cast<void**>(&pair[0x00]);
    void* pEnd   = *reinterpret_cast<void**>(&pair[0x08]);
    FreeWStringBuffer(pBegin, pEnd);

    return reinterpret_cast<WString*>(reinterpret_cast<uint8*>(*reinterpret_cast<void**>(out)) + 0xc);
}

// ===========================================================================
// @ 0x008E0F50
// ===========================================================================
void HashTable::eraseNode1c(void* pOut, const void* pKey)
{
    uint8* pNode = *reinterpret_cast<uint8**>(const_cast<void*>(pKey));
    uint8* pNext = *reinterpret_cast<uint8**>(pNode + 0x14);

    *reinterpret_cast<void**>(pOut) = pNext;
    *reinterpret_cast<uint8**>(reinterpret_cast<uint8*>(pOut) + 4) =
        *reinterpret_cast<uint8**>(const_cast<void*>(pKey));

    if (pNext == 0)
    {
        uint8** pSlot = reinterpret_cast<uint8**>(reinterpret_cast<uint8*>(pOut) + 4);
        do
        {
            *pSlot = *pSlot + 4;
            pNext = **reinterpret_cast<uint8***>(pSlot);
        }
        while (pNext == 0);
        *reinterpret_cast<void**>(pOut) = pNext;
    }

    // Unlink pNode from its bucket chain (single-link, +0x14 next).
    uint8* pBucket = *reinterpret_cast<uint8**>(*reinterpret_cast<uint8**>(const_cast<void*>(pKey)));
    if (pBucket == pNode)
    {
        *reinterpret_cast<uint8**>(*reinterpret_cast<uint8**>(const_cast<void*>(pKey))) =
            *reinterpret_cast<uint8**>(pNode + 0x14);
    }
    else
    {
        uint8* pPrev = pBucket;
        uint8* pCur = *reinterpret_cast<uint8**>(pPrev + 0x14);
        while (pCur != pNode)
        {
            pPrev = pCur;
            pCur = *reinterpret_cast<uint8**>(pPrev + 0x14);
        }
        *reinterpret_cast<uint8**>(pPrev + 0x14) = *reinterpret_cast<uint8**>(pCur + 0x14);
    }

    // Free the node's string, then the node.
    void* pStrBegin = *reinterpret_cast<void**>(pNode + 4);
    void* pStrEnd   = *reinterpret_cast<void**>(pNode + 0xc);
    FreeWStringBuffer(pStrBegin, pStrEnd);
    --mnElementCount;
    mpAllocator->Free(pNode, 0x1c);
}

// ===========================================================================
// @ 0x008E0FE0
// ===========================================================================
void HashTable::eraseNode20(void* pOut, const void* pKey)
{
    uint8* pNode = *reinterpret_cast<uint8**>(const_cast<void*>(pKey));
    uint8* pNext = *reinterpret_cast<uint8**>(pNode + 0x18);

    *reinterpret_cast<void**>(pOut) = pNext;
    *reinterpret_cast<uint8**>(reinterpret_cast<uint8*>(pOut) + 4) =
        *reinterpret_cast<uint8**>(const_cast<void*>(pKey));

    if (pNext == 0)
    {
        uint8** pSlot = reinterpret_cast<uint8**>(reinterpret_cast<uint8*>(pOut) + 4);
        do
        {
            *pSlot = *pSlot + 4;
            pNext = **reinterpret_cast<uint8***>(pSlot);
        }
        while (pNext == 0);
        *reinterpret_cast<void**>(pOut) = pNext;
    }

    uint8* pBucket = *reinterpret_cast<uint8**>(*reinterpret_cast<uint8**>(const_cast<void*>(pKey)));
    if (pBucket == pNode)
    {
        *reinterpret_cast<uint8**>(*reinterpret_cast<uint8**>(const_cast<void*>(pKey))) =
            *reinterpret_cast<uint8**>(pNode + 0x18);
    }
    else
    {
        uint8* pPrev = pBucket;
        uint8* pCur = *reinterpret_cast<uint8**>(pPrev + 0x18);
        while (pCur != pNode)
        {
            pPrev = pCur;
            pCur = *reinterpret_cast<uint8**>(pPrev + 0x18);
        }
        *reinterpret_cast<uint8**>(pPrev + 0x18) = *reinterpret_cast<uint8**>(pCur + 0x18);
    }

    void* pStrBegin = *reinterpret_cast<void**>(pNode + 8);
    void* pStrEnd   = *reinterpret_cast<void**>(pNode + 0x10);
    FreeWStringBuffer(pStrBegin, pStrEnd);
    --mnElementCount;
    mpAllocator->Free(pNode, 0x20);
}

// ===========================================================================
// @ 0x008E1070
// ===========================================================================
AutoRefObj* AutoRefVec::insertGrow(AutoRefObj* pPos, const AutoRefObj* pSrc)
{
    if (mpEnd != mpCap)
    {
        // There is room: shift the tail right by one and copy-assign into the slot.
        AutoRefObj* pOldEnd = mpEnd;
        if (*reinterpret_cast<void* const*>(&pPos) > mpEnd)
            pPos = mpEnd;
        if (pOldEnd != 0)
        {
            pOldEnd->mpObject = pOldEnd[-1].mpObject;
            if (pOldEnd->mpObject != 0)
                (*(void (__thiscall**)(void*))((reinterpret_cast<uint8*>(*reinterpret_cast<void**>(pOldEnd->mpObject)) + 4)))(pOldEnd->mpObject);
            pOldEnd->mField = pOldEnd[-1].mField;
        }
        AutoRefMoveBackward(mpBegin, mpEnd - 1, mpEnd);
        CopyAutoRef(pPos, pSrc);
        ++mpEnd;
        return pPos;
    }

    // No room: allocate a doubled buffer, splice the old range, copy, splice back.
    int nCount = static_cast<int>(mpEnd - mpBegin);
    int nNew = nCount > 0 ? nCount * 2 : 1;
    AutoRefObj* pNew = nNew != 0
        ? reinterpret_cast<AutoRefObj*>(allocateStorage(nNew, &mpAllocator))
        : 0;
    AutoRefObj* pMid = Fn8de890(mpBegin, pPos, pNew);
    Fn7e18d0(pPos, mpEnd, pNew);
    if (pMid != 0)
        CopyAutoRef(pMid, pSrc);
    Fn8de890(pPos, mpEnd, pMid + 1);
    Fn7e18d0(pPos, mpEnd, pMid + 1);
    return pMid;
}

// ===========================================================================
// @ 0x008E1200
// ===========================================================================
void AutoRefVec::clearRange(AutoRefObj* pFirst, AutoRefObj* pLast)
{
    uint32 n = static_cast<uint32>(pLast - pFirst);
    for (uint32 i = 0; i < n; ++i)
    {
        void* pEntry = pFirst[i].mpObject;
        if (pEntry == 0)
            continue;
        // Each entry heads an intrusive list of vector-holding nodes.
        uint8* pNode = reinterpret_cast<uint8*>(pEntry);
        while (pNode != 0)
        {
            uint8* pBegin = *reinterpret_cast<uint8**>(pNode + 4);
            uint8* pEnd   = *reinterpret_cast<uint8**>(pNode + 8);
            uint8* pNext  = *reinterpret_cast<uint8**>(pNode + 0x18);
            for (uint8* p = pBegin; p < pEnd; p += 8)
            {
                void* pObj = *reinterpret_cast<void**>(p);
                if (pObj != 0)
                    (*(void (__thiscall**)(void*))((reinterpret_cast<uint8*>(*reinterpret_cast<void**>(pObj)) + 8)))(pObj);
            }
            FreeAutoRefVectorNode(pNode);
            pNode = pNext;
        }
    }
}

// ===========================================================================
// @ 0x008E12C0
// ===========================================================================
AutoRefObj* AutoRefVec::insertAt(AutoRefObj* pPos, const AutoRefObj* pSrc)
{
    if (mpEnd == mpCap)
        return insertGrow(pPos, pSrc);

    AutoRefObj* pOldEnd = mpEnd;
    if (pOldEnd != 0)
    {
        pOldEnd->mpObject = pOldEnd[-1].mpObject;
        if (pOldEnd->mpObject != 0)
            (*(void (__thiscall**)(void*))((reinterpret_cast<uint8*>(*reinterpret_cast<void**>(pOldEnd->mpObject)) + 4)))(pOldEnd->mpObject);
        pOldEnd->mField = pOldEnd[-1].mField;
    }
    AutoRefMoveBackward(mpBegin, mpEnd - 1, mpEnd);
    CopyAutoRef(pPos, pSrc);
    ++mpEnd;
    return pPos;
}

// ===========================================================================
// @ 0x008E1420
// ===========================================================================
InternalDatabaseList::~InternalDatabaseList()
{
    Flush();

    while (mpVecBegin != mpVecEnd)
        mpVecEnd = reinterpret_cast<void**>(reinterpret_cast<uint8*>(mpVecEnd) - 4);

    Fn926640(mHashBase);

    if (mpVecBegin != 0)
        (*(void (__thiscall**)(void*, uint32))((reinterpret_cast<uint8*>(*reinterpret_cast<void**>(mpVecAllocator)) + 0xc)))(
            mpVecBegin, static_cast<uint32>(reinterpret_cast<uint8*>(mpVecCap) - reinterpret_cast<uint8*>(mpVecBegin)));

    Fn922130(&mMutex);
}

// ===========================================================================
// @ 0x008E1480
// ===========================================================================
bool Manager::SetKeyName(Key* pKey, const wchar_t* pName)
{
    mNameMutex.Lock(reinterpret_cast<const char*>(0x1436AB8));
    WString* pStr = mKeyNameMap.KeyNameOperatorIndex(pKey);
    const char* pBegin = reinterpret_cast<const char*>(pName);
    const char* pScan  = pBegin;
    while (*reinterpret_cast<const wchar_t*>(pScan) != 0)
        pScan += 2;
    pStr->assign(pName, pBegin + ((pScan - pBegin) >> 1) * 2);
    mNameMutex.Unlock();
    return true;
}

// ===========================================================================
// @ 0x008E14E0
// ===========================================================================
bool Manager::ForgetKeyName(Key* pKey)
{
    mNameMutex.Lock(reinterpret_cast<const char*>(0x1436AB8));

    void* pFound = 0;
    mKeyNameMap.findKey(&pFound, pKey);

    bool bFound = (pFound != *mKeyNameMap.endIterator());
    if (bFound)
        mKeyNameMap.eraseNode20(&pFound, pKey);

    mNameMutex.Unlock();
    return bFound;
}

// ===========================================================================
// @ 0x008E1560
// ===========================================================================
bool Manager::SetTypename(uint32 nType, const wchar_t* pName)
{
    mNameMutex.Lock(reinterpret_cast<const char*>(0x1436AB8));

    void* pFound = 0;
    mTypenameMap.findU32(&pFound, &nType);

    if (pFound == *mTypenameMap.endIterator())
    {
        WString* pStr = reinterpret_cast<WString*>(mTypenameMap.refKey(nType));
        const wchar_t* pEnd = pName;
        while (*pEnd != 0)
            ++pEnd;
        pStr->assign(pName, pEnd);
        mNameMutex.Unlock();
        return true;
    }

    bool bOk = Fn6ab760(reinterpret_cast<uint8*>(pFound) + 4, pName);
    mNameMutex.Unlock();
    return bOk;
}

// ===========================================================================
// @ 0x008E1610
// ===========================================================================
bool Manager::ResetTypename(uint32 nType, const wchar_t* pName)
{
    mNameMutex.Lock(reinterpret_cast<const char*>(0x1436AB8));

    void* pFound = 0;
    mTypenameMap.findU32(&pFound, &nType);

    if (pFound != *mTypenameMap.endIterator())
    {
        mTypenameMap.eraseNode1c(&pFound, &nType);
        mNameMutex.Unlock();
        return true;
    }

    WString* pStr = reinterpret_cast<WString*>(mTypenameMap.refKey(nType));
    const wchar_t* pEnd = pName;
    while (*pEnd != 0)
        ++pEnd;
    pStr->assign(pName, pEnd);
    mNameMutex.Unlock();
    return false;
}

// ===========================================================================
// @ 0x008E1690
// ===========================================================================
AutoRefObj* AutoRefVec::pushBack(AutoRefObj* pPos, const AutoRefObj* pSrc)
{
    if (pPos == mpEnd && mpEnd != mpCap)
    {
        AutoRefObj* pSlot = mpEnd;
        mpEnd = pSlot + 1;
        if (pSlot != 0)
        {
            pSlot->mpObject = pSrc->mpObject;
            if (pSlot->mpObject != 0)
                (*(void (__thiscall**)(void*))((reinterpret_cast<uint8*>(*reinterpret_cast<void**>(pSlot->mpObject)) + 4)))(pSlot->mpObject);
            pSlot->mField = pSrc->mField;
        }
        return mpBegin + (pPos - mpBegin);
    }
    insertAt(pPos, pSrc);
    return mpBegin + (pPos - mpBegin);
}

// ===========================================================================
// @ 0x008E1700
// ===========================================================================
int Manager::Shutdown()
{
    if (mbInitialized == 0)
        return 1;

    Compressor* pFirst = mpCompressorBegin;
    Compressor* pLast  = mpCompressorEnd;
    mbInitialized = 0;

    for (Compressor* p = pFirst; p != pLast; ++p)
    {
        int* pRefCount = reinterpret_cast<int*>(reinterpret_cast<uint8*>(p->vftable) + 4);   // +0x04
        if (*pRefCount == 1)
            (*(void (__thiscall**)(void*))(reinterpret_cast<uint8*>(*p->vftable) + 8))(p);
    }

    Fn8dede0(Fn8de890(reinterpret_cast<AutoRefObj*>(pFirst), reinterpret_cast<AutoRefObj*>(pLast), 0), mpCompressorEnd);
    mpCompressorEnd = pFirst;

    // Empty the type->factories map freeing the per-type factory vectors.
    ClearFactoryMap(&mTypeToFactoriesMap);
    ClearAutoRefVec(&mTypeToFactoriesMap, 0);

    FreeChangeList(mDatabaseListHead);
    return 1;
}

// ===========================================================================
// @ 0x008E1930
// ===========================================================================
void Manager::Fn8e1930(uint32 nKey, uint32* pIds, uint32 nCount)
{
    mTypeFactoryMap.eraseKey(&nKey);

    for (uint32 i = 0; i < nCount; ++i)
    {
        uint32 key = pIds[i];
        uint32 slot = 0;
        InsertU32Slot(&slot, &key, 0);
    }
}

// ===========================================================================
// @ 0x008E1A50
// ===========================================================================
int Manager::RegisterFactory(char bAdd, Factory* pFactory)
{
    if (pFactory == 0)
        return 0;

    if (bAdd == 0)
    {
        // Remove pFactory from every type's factory vector.
        for (void** pBucket = mTypeToFactoriesMap.mpBucketArray;
             pBucket != mTypeToFactoriesMap.endIterator(); ++pBucket)
        {
            for (uint8* pNode = reinterpret_cast<uint8*>(*pBucket); pNode != 0;
                 pNode = *reinterpret_cast<uint8**>(pNode + 0x18))
            {
                FactorySlot* pSlots = *reinterpret_cast<FactorySlot**>(pNode + 4);
                FactorySlot* pEnd   = *reinterpret_cast<FactorySlot**>(pNode + 8);
                while (pSlots != pEnd)
                {
                    if (pSlots->mpFactory == pFactory)
                    {
                        if (pSlots->mpFactory != 0)
                            (*(void (__thiscall**)(void*))((reinterpret_cast<uint8*>(*reinterpret_cast<void**>(pSlots->mpFactory)) + 8)))(pSlots->mpFactory);
                        Fn7e1b00(pSlots + 1, pEnd, pSlots);
                        --pEnd;
                        if (pEnd->mpFactory != 0)
                            (*(void (__thiscall**)(void*))((reinterpret_cast<uint8*>(*reinterpret_cast<void**>(pEnd->mpFactory)) + 8)))(pEnd->mpFactory);
                        *reinterpret_cast<FactorySlot**>(pNode + 8) = pEnd;
                    }
                    else
                    {
                        ++pSlots;
                    }
                }
            }
        }
        return 1;
    }

    // Add: register each of the factory's type ids in the type->factories map.
    pFactory->Slot10();
    uint32 n = pFactory->Slot2C(0, 0);
    uint32* pIds = 0;
    if (n != 1)
        pIds = reinterpret_cast<uint32*>(EAAllocate(n * 4, "Resource/Temp TypeId Array", 0, 0, 0, 0));
    pFactory->Slot2C(pIds, n);

    for (uint32 i = 0; i < n; ++i)
    {
        void* pEntry = 0;
        mTypeToFactoriesMap.findU32(&pEntry, &pIds[i]);
        if (pEntry == *mTypeToFactoriesMap.endIterator())
        {
            uint8 vec[0x14];
            Fn8decb0();
            (void)vec;
            Fn8e0250(&pIds[i], vec);
        }
    }
    (void)pIds;
    return 1;
}
