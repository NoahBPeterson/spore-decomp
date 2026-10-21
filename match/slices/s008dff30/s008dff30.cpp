// Slice s008dff30 (0x8dff30..0x8e0eaa) - EA::ResourceMan::Manager database /
// factory lists, the change-notification registration and the eastl hashtable
// node insert/erase/free helpers used by the manager's maps.
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

// A plain EA allocator interface: slot +0x04 AddRef-ish, +0x08 Allocate, +0x0c Free.
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
};

// eastl::basic_string<wchar_t>::assign(begin, end) - 0x00423650.
struct WStringAsgn {
    void assign(const void* pBegin, const void* pEnd);
};

// An AutoRefCount<Factory> payload (pointer + user field).
struct AutoRefObj {
    void* mpObject;     // +0x00
    int   mField;       // +0x04
};

// A vector of AutoRefObj (5-pointer eastl vector).
struct AutoRefVec {
    AutoRefObj* mpBegin;      // +0x00
    AutoRefObj* mpEnd;        // +0x04
    AutoRefObj* mpCap;        // +0x08
    void*       mpAllocator;  // +0x0c
    const char* mpName;       // +0x10

    void* allocateStorage(int n, void* pAllocPair);   // 0x008DEF20
};

// Shared header of every node-based eastl::hashtable instantiation in this slice.
struct HashTable {    uint32 mUnk0;               // +0x00
    void** mpBucketArray;       // +0x04
    uint32 mnBucketCount;       // +0x08
    uint32 mnElementCount;      // +0x0c
    uint32 mRehash[3];          // +0x10
    Alloc* mpAllocator;         // +0x1c
    const char* mpName;         // +0x20

    void** find(void** ppOut, const uint32* pKey);        // 0x00AEA1B0
    void** findString(void** ppOut, const uint32* pKey);  // 0x00A3B2C0
    void** findFixed(void** ppOut, const uint32* pKey);   // 0x00645ED0
    void** findKey(void** ppOut, const void* pKey);       // 0x008DB3D0
    void  doRehash(uint32 n);                             // 0x008DE740
    void  doRehash2(uint32 n);                            // 0x008DE5E0
    void  doRehash3(uint32 n);                            // 0x008DE690
    void  doRehashKey(uint32 n);                          // 0x00888500
    void  DoFreeNodes18(void** pBucketArray, uint32 n);   // 0x008E06D0
    void  DoFreeNodes20(void** pBucketArray, uint32 n);   // 0x008E0740

    void* insertNode3(void* pOut, void* pKey, void* p3);  // 0x008DFCD0
    void* insertNode18(void* pOut, void* pKey, void* p3); // 0x008E02B0
    void* insertNode20(void* pOut, void* pKey, void* p3); // 0x008E0390
    void* insertNode1c(void* pOut, void* pKey, void* p3); // 0x008E0550
    int   eraseKey(uint32* pKey);                         // 0x008E0630
    void* refKey(uint32 nKey);                            // 0x008E0E10
};

// The rehash policy object embedded at HashTable+0x10.
struct RehashPolicy {
    void evaluate(void* pOut, uint32 nBucketCount, uint32 nElementCount, int one);  // 0x00921440
};

// Result written by RehashPolicy::evaluate.
struct RehashResult {
    uint8  mbGrew;          // +0x00
    char   _pad01[3];
    uint32 mnBucketCount;   // +0x04
};

// A ResourceMan factory: reference-counted COM object with the slots this slice uses.
class Factory { public:
    virtual void Slot00();                                                       // +0x00
    virtual void AddRef();                                                       // +0x04
    virtual void Release();                                                      // +0x08
    virtual void Slot0C();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C(void* a, void* b, void* c, void* d);                     // +0x1c
    virtual void Slot20();
    virtual void Slot24();                                                       // +0x24
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30(void* a, void* b);                                       // +0x30
    virtual char Init(Key* pKey, void* pTypeParam, int a, int b, int c, int d);  // +0x34
    virtual void Slot38();
    virtual void Slot3C();
    virtual void Slot40();
    virtual char Slot44(int a, void* b, int c);                                  // +0x44
    virtual void Slot48();
    virtual void Slot4C();
    virtual void Slot50();
    virtual char Slot54(void* a, int b);                                         // +0x54
    virtual void* Slot58(Key* pKey);                                             // +0x58
};

// ---------------------------------------------------------------------------
// Intrusive circular list node / anchor (mpNext, mpPrev) plus collection nodes.
// ---------------------------------------------------------------------------
struct CNode {
    CNode* mpNext;   // +0x00
    CNode* mpPrev;   // +0x04
    void*  mpData;   // +0x08
};

// List header used by GetDatabaseList: an 8-byte (next/prev) anchor, the
// allocator used to build the nodes, and the allocation name.
struct AllocList {
    void*  mpNext;       // +0x00
    void*  mpPrev;       // +0x04
    Alloc* mpAllocator;  // +0x08
    const char* mpName;  // +0x0c
};

// ---------------------------------------------------------------------------
// Database list
// ---------------------------------------------------------------------------
struct DBNode {
    DBNode* mpNext;      // +0x00
    void*   mpDatabase;  // +0x04
};

struct DBList {
    DBNode* mpHead;             // +0x00
    char    _pad04[0x0c];
    Thread::Mutex mMutex;       // +0x10
    void*   mDeletedBegin;      // +0x40
    void*   mDeletedEnd;        // +0x44
    void*   mDeletedCap;        // +0x48

    void Add(void* pDatabase, int a);   // 0x008DE940
    void Erase(DBNode** ppNode);        // 0x008E07B0
    void Flush();                       // 0x008E0840
};

// ---------------------------------------------------------------------------
// Vectors used as manager method out-parameters
// ---------------------------------------------------------------------------
// eastl::vector<Key> (0xc-byte elements).
struct KeyVec {
    Key* mpBegin;   // +0x00
    Key* mpEnd;     // +0x04
    Key* mpCap;     // +0x08
    void DoInsertValue(Key* pPos, const Key* pSrc);   // 0x004E3E10
};

// eastl::vector<T*> (4-byte elements) - the "SimpleVector" family.
struct PtrVec {
    void** mpBegin;  // +0x00
    void** mpEnd;    // +0x04
    void** mpCap;    // +0x08
    void DoInsertValue(void** pPos, void* const* pSrc);   // 0x00A80DD0
};

// eastl::vector<Node*> used by InternalDatabaseList::mDeleted.
struct Vec8 {
    void** mpBegin;  // +0x00
    void** mpEnd;    // +0x04
    void** mpCap;    // +0x08
    void DoInsertValue(void** pPos, void* const* pSrc);   // 0x008891F0
};

// A vector of unsigned with a range-insert helper.
struct U32Vec {
    uint32* mpBegin;  // +0x00
    uint32* mpEnd;    // +0x04
    uint32* mpCap;    // +0x08
    void DoInsertValue(uint32* pPos, const uint32* pSrc);                         // 0x004558A0
    void DoInsertFromIterator(uint32* pPos, const uint32* pFirst, const uint32* pLast, uint32 a); // 0x0042B9E0
};

// A VecOwner: one extra pointer followed by an AutoRefVec.
struct VecOwner {
    void*      mpUnk0;   // +0x00
    AutoRefVec vec;      // +0x04
    VecOwner*  AssignRange(VecOwner* pSrc);          // 0x008DFED0
    VecOwner*  CopyFrom(void* p1, AutoRefVec* pSrc); // 0x008E0250
};

// ---------------------------------------------------------------------------
// eastl::rbtree<ChangeNotificationInfo, ...> - the manager's change set at
// Manager+0x0c.  Its methods take ecx = &rbtree (NOT &Manager).
// ---------------------------------------------------------------------------
namespace eastl_shim {

struct RbNodeBase {
    RbNodeBase* mpNodeRight;   // +0x00
    RbNodeBase* mpNodeLeft;    // +0x04
    RbNodeBase* mpNodeParent;  // +0x08
    uint32      mnColor;       // +0x0c
};

struct ChangeInfo {
    Key  mKey;        // +0x00
    int  mnPriority;  // +0x0c
};

struct ChangeNode {
    RbNodeBase base;    // +0x00
    ChangeInfo info;    // +0x10 (mKey at +0x10, priority at +0x1c)
};

struct ChangeSet {
    uint32      mUnk0;        // +0x00
    RbNodeBase  mAnchor;      // +0x04 (root = mAnchor.mpNodeParent at +0x0c)
    uint32      mnSize;       // +0x14
    void*       mpAllocator;  // +0x18
    const char* mpName;       // +0x1c

    void  LowerBound(void** ppOut, const uint32* pKey);   // 0x008DE450
    void  erase(void** ppOut, void* pIter);               // 0x008D93A0
    void* DoInsertValue(void* pOut, const void* pValue, void* pUnused);  // 0x008DFDE0
};

}  // namespace eastl_shim

// ---------------------------------------------------------------------------
// Manager
// ---------------------------------------------------------------------------
class Manager { public:
    void** vftable;                     // +0x00
    uint8  mbInitialized;               // +0x04
    char   _pad05[3];
    void*  mpAllocator;                 // +0x08
    eastl_shim::ChangeSet mChangeSet;   // +0x0c (0x20 bytes)
    DBList* mDatabaseList;              // +0x2c
    HashTable mTypeToFactoryMap;        // +0x30
    HashTable mTypeToFactoriesMap;      // +0x54
    HashTable mTextStyleMap;            // +0x78
    void*  mpCompressorBegin;           // +0x9c
    void*  mpCompressorEnd;             // +0xa0
    char   _padA4[0x0c];
    HashTable mTypenameMap;             // +0xb0
    char   _padD4[0x20];
    HashTable mKeyNameMap;              // +0xf4
    Thread::Mutex mNameMutex;           // +0x118
    Thread::Mutex mAsyncMutex;          // +0x148

    int  Fn8dff30(CNode* pList, uint32 nKey);
    int  GetDatabaseList(AllocList* pList, int nFilter);
    int  Fn8e0140(CNode* pList);
    void GetNameFromKey(Key* pKey, void* pOut);
    int  Fn8e08c0(U32Vec* pOut, uint32 nKey);
    int  Fn8e0950(KeyVec* pOut, uint32 nKey);
    int  Fn8e0a30(KeyVec* pKeys, void* pArg, PtrVec* pFactories);
    int  Fn8e0c10(void* pUnused, KeyVec* pOut, uint32 nKey);
    char RegisterChangeNotification(void* pUnused, Key key, int nPriority);
    char RegisterDatabase(char bAdd, void* pDatabase, int a3);
};

}  // namespace ResourceMan
}  // namespace EA

using namespace EA;
using namespace EA::ResourceMan;

// ---------------------------------------------------------------------------
// external helpers (bodies live in other translation units)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl EAAllocate(uint32 nSize, const char* pName, int a, int b,
                                    const char* pFile, int nLine);        // 0x00F473A0
extern "C" void  __cdecl FnC77680(void* pOut, const void* pIn);           // 0x00C77680
extern "C" void* __cdecl Fn8de840(void** ppOut, AutoRefObj* first, AutoRefObj* last,
                                  AutoRefObj* dest, void* pAlloc);        // 0x008DE840

// Node constructors / helpers, modelled as members of a proxy struct so the
// thiscall ABI (ecx = the node, callee pops its stack arguments) is preserved.
struct NodeCtorProxy {
    void  ctor18(void* pKey);                                  // 0x00688700
    void  ctor20(void* pKey);                                  // 0x005F8390
};
struct MapPairProxy {
    void* makePair(uint32 nKey, WString* pStr);                // 0x00688760
};

// GetNameFromKey calls through a global cdecl function pointer in .rdata.
extern void (*g_DefaultCreateNameFromKey)(const void* p1, void* p2, void* p3, int a, int b); // 0x0154C468

static const char* const kEastlFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ---------------------------------------------------------------------------
// Intrusive list append used by several collectors.
// ---------------------------------------------------------------------------
static void IntrPushBack(CNode* pAnchor, CNode* pNode)
{
    pNode->mpNext = pAnchor;
    pNode->mpPrev = pAnchor->mpPrev;
    pAnchor->mpPrev->mpNext = pNode;
    pAnchor->mpPrev = pNode;
}

// ===========================================================================
// @ 0x008DFF30
// ===========================================================================
int Manager::Fn8dff30(CNode* pList, uint32 nKey)
{
    int nCount = 0;
    if (nKey == 0xffffffffu) {
        uint32* pSlot = (uint32*)mTypeToFactoryMap.mpBucketArray;
        uint32 node = *pSlot;
        if (node == 0) {
            do { ++pSlot; } while (*pSlot == 0);
            node = *pSlot;
        }
        uint32 end = (uint32)mTypeToFactoryMap.mpBucketArray[mTypeToFactoryMap.mnBucketCount];
        while (node != end) {
            uint32* pNode = (uint32*)node;
            AutoRefObj* pIt = (AutoRefObj*)pNode[1];
            AutoRefObj* pLast = (AutoRefObj*)pNode[2];
            while (pIt != pLast) {
                Factory* pFac = (Factory*)pIt->mpObject;
                ++nCount;
                CNode* pNew = (CNode*)EAAllocate(0xc, "EASTL", 0, 0, kEastlFile, 0xd1);
                if (pNew) pNew->mpData = pFac;
                IntrPushBack(pList, pNew);
                ++pIt;
            }
            node = pNode[6];
            if (node == 0) {
                do { ++pSlot; node = *pSlot; } while (node == 0);
            }
            pList = pList;
        }
    } else {
        void* it[2];
        HashTable* pMap = &mTypeToFactoryMap;
        pMap->find(it, &nKey);
        if (it[0] != pMap->mpBucketArray[pMap->mnBucketCount]) {
            uint32* pNode = (uint32*)it[0];
            AutoRefObj* pIt = (AutoRefObj*)pNode[1];
            AutoRefObj* pLast = (AutoRefObj*)pNode[2];
            for (; pIt != pLast; ++pIt) {
                Factory* pFac = (Factory*)pIt->mpObject;
                ++nCount;
                CNode* pNew = (CNode*)EAAllocate(0xc, "EASTL", 0, 0, kEastlFile, 0xd1);
                if (pNew) pNew->mpData = pFac;
                IntrPushBack(pList, pNew);
            }
        }
    }
    return nCount;
}

// ===========================================================================
// @ 0x008E00B0
// ===========================================================================
int Manager::GetDatabaseList(AllocList* pList, int nFilter)
{
    int nCount = 0;
    for (DBNode* pNode = mDatabaseList->mpHead; pNode; pNode = pNode->mpNext) {
        void* pDB = pNode->mpDatabase;
        if (nFilter != 0) {
            typedef char (__thiscall* FnVf34)(void*, int, int, int, int, int, int);
            if (!((FnVf34)(*(void***)pDB)[0x34 / 4])(pDB, nFilter, 0, 1, 6, 1, 0))
                continue;
        }
        ++nCount;
        if (!pList) continue;
        CNode* pNew = (CNode*)pList->mpAllocator->Allocate(0xc, 0, pList->mpName);
        if (pNew) pNew->mpData = pDB;
        IntrPushBack((CNode*)pList, pNew);
    }
    return nCount;
}

// ===========================================================================
// @ 0x008E0140
// ===========================================================================
int Manager::Fn8e0140(CNode* pList)
{
    int nCount = 0;
    for (uint32* pIt = (uint32*)mpCompressorBegin; pIt != (uint32*)mpCompressorEnd; pIt += 2) {
        Factory* pFac = (Factory*)*pIt;
        ++nCount;
        if (pList) {
            CNode* pNew = (CNode*)EAAllocate(0xc, "EASTL", 0, 0, kEastlFile, 0xd1);
            if (pNew) pNew->mpData = pFac;
            IntrPushBack(pList, pNew);
        }
    }
    return nCount;
}

// ===========================================================================
// @ 0x008E01C0
// ===========================================================================
void Manager::GetNameFromKey(Key* pKey, void* pOut)
{
    Thread::Mutex* pMutex = &mNameMutex;
    pMutex->Lock((const char*)0x1436AB8);
    HashTable* pMap = &mKeyNameMap;
    void* it[2];
    pMap->findKey(it, pKey);
    if (it[0] == pMap->mpBucketArray[pMap->mnBucketCount]) {
        g_DefaultCreateNameFromKey(pKey, pOut, this, 0, 0);
        pMutex->Unlock();
        return;
    }
    char* pSrc = (char*)it[0] + 0xc;
    if (pSrc != (char*)pOut) {
        ((WStringAsgn*)pOut)->assign(*(void**)pSrc, *((void**)pSrc + 1));
    }
    pMutex->Unlock();
}

// ===========================================================================
// @ 0x008E0250
// ===========================================================================
VecOwner* VecOwner::CopyFrom(void* p1, AutoRefVec* pSrc)
{
    mpUnk0 = *(void**)p1;
    vec.allocateStorage((int)(pSrc->mpEnd - pSrc->mpBegin), (char*)pSrc + 0xc);
    Fn8de840((void**)&p1, pSrc->mpBegin, pSrc->mpEnd, vec.mpBegin, p1);
    vec.mpEnd = (AutoRefObj*)p1;
    return this;
}

// ===========================================================================
// @ 0x008E02B0
// ===========================================================================
void* HashTable::insertNode18(void* pOut, void* pKey, void* p3)
{
    (void)p3;
    uint32 nKey = *(uint32*)pKey;
    uint32 idx = nKey % mnBucketCount;
    char* pSlot = (char*)mpBucketArray + idx * 4;
    uint32 node = *(uint32*)pSlot;
    while (node) {
        if (nKey == *(uint32*)node) break;
        node = *(uint32*)(node + 0x14);
    }
    if (node == 0) {
        RehashResult pol;
        ((RehashPolicy*)((char*)this + 0x10))->evaluate(&pol, mnBucketCount, mnElementCount, 1);
        void* pNew = mpAllocator->Allocate(0x18, 0, mpName);
        if (pNew) ((NodeCtorProxy*)pNew)->ctor18(pKey);
        *(void**)((char*)pNew + 0x14) = 0;
        if (pol.mbGrew) {
            idx = nKey % pol.mnBucketCount;
            doRehash2(pol.mnBucketCount);
        }
        *(void**)((char*)pNew + 0x14) = mpBucketArray[idx];
        mpBucketArray[idx] = pNew;
        ++mnElementCount;
        *(void**)pOut = pNew;
        *((void**)pOut + 1) = &mpBucketArray[idx];
        *((uint8*)pOut + 8) = 1;
        return pOut;
    }
    *(void**)pOut = (void*)node;
    *((void**)pOut + 1) = pSlot;
    *((uint8*)pOut + 8) = 0;
    return pOut;
}

// ===========================================================================
// @ 0x008E0390
// ===========================================================================
void* HashTable::insertNode20(void* pOut, void* pKey, void* p3)
{
    (void)p3;
    uint32* pK = (uint32*)pKey;
    uint32 hash = pK[0] ^ pK[2];
    uint32 idx = hash % mnBucketCount;
    char* pSlot = (char*)mpBucketArray + idx * 4;
    uint32 node = *(uint32*)pSlot;
    uint32* pNode = (uint32*)node;
    while (node) {
        if (pK[0] == pNode[0] && pK[1] == pNode[1] && pK[2] == pNode[2]) break;
        node = pNode[7];
        pNode = (uint32*)node;
    }
    if (node == 0) {
        RehashResult pol;
        ((RehashPolicy*)((char*)this + 0x10))->evaluate(&pol, mnBucketCount, mnElementCount, 1);
        void* pNew = mpAllocator->Allocate(0x20, 0, mpName);
        if (pNew) ((NodeCtorProxy*)pNew)->ctor20(pKey);
        *(void**)((char*)pNew + 0x1c) = 0;
        if (pol.mbGrew) {
            idx = hash % pol.mnBucketCount;
            doRehash3(pol.mnBucketCount);
        } else {
            idx = hash % mnBucketCount;
        }
        *(void**)((char*)pNew + 0x1c) = mpBucketArray[idx];
        mpBucketArray[idx] = pNew;
        ++mnElementCount;
        *(void**)pOut = pNew;
        *((void**)pOut + 1) = &mpBucketArray[idx];
        *((uint8*)pOut + 8) = 1;
        return pOut;
    }
    *(void**)pOut = (void*)node;
    *((void**)pOut + 1) = pSlot;
    *((uint8*)pOut + 8) = 0;
    return pOut;
}

// ===========================================================================
// @ 0x008E04A0
// ===========================================================================
char Manager::RegisterChangeNotification(void* pUnused, Key key, int nPriority)
{
    (void)pUnused;
    if (key.mInstance == 0) return 0;
    eastl_shim::ChangeInfo info;
    memcpy(&info, &key, 0xc);
    info.mnPriority = nPriority;

    void* pIter;
    mChangeSet.LowerBound(&pIter, (const uint32*)&info);
    void* pEnd = (char*)this + 0x10;
    if ((char)nPriority == 0) {
        if (pIter == pEnd) return 0;
        mChangeSet.erase(&pIter, pIter);
        return 1;
    }
    if (pIter != pEnd) return 0;
    mChangeSet.DoInsertValue(0, &info, 0);
    return 1;
}

// ===========================================================================
// @ 0x008E0550
// ===========================================================================
void* HashTable::insertNode1c(void* pOut, void* pKey, void* p3)
{
    (void)p3;
    uint32 nKey = *(uint32*)pKey;
    uint32 idx = nKey % mnBucketCount;
    char* pSlot = (char*)mpBucketArray + idx * 4;
    uint32 node = *(uint32*)pSlot;
    while (node) {
        if (nKey == *(uint32*)node) break;
        node = *(uint32*)(node + 0x18);
    }
    if (node == 0) {
        RehashResult pol;
        ((RehashPolicy*)((char*)this + 0x10))->evaluate(&pol, mnBucketCount, mnElementCount, 1);
        void* pNew = mpAllocator->Allocate(0x1c, 0, mpName);
        if (pNew) ((VecOwner*)pNew)->AssignRange((VecOwner*)pKey);
        *(void**)((char*)pNew + 0x18) = 0;
        if (pol.mbGrew) {
            idx = nKey % pol.mnBucketCount;
            doRehashKey(pol.mnBucketCount);
        }
        *(void**)((char*)pNew + 0x18) = mpBucketArray[idx];
        mpBucketArray[idx] = pNew;
        ++mnElementCount;
        *(void**)pOut = pNew;
        *((void**)pOut + 1) = &mpBucketArray[idx];
        *((uint8*)pOut + 8) = 1;
        return pOut;
    }
    *(void**)pOut = (void*)node;
    *((void**)pOut + 1) = pSlot;
    *((uint8*)pOut + 8) = 0;
    return pOut;
}

// ===========================================================================
// @ 0x008E0630
// ===========================================================================
int HashTable::eraseKey(uint32* pKey)
{
    int nBefore = mnElementCount;
    uint32 idx = *pKey % mnBucketCount;
    char* pSlot = (char*)mpBucketArray + idx * 4;
    if (*(uint32*)pSlot != 0) {
        uint32 node;
        do {
            node = *(uint32*)pSlot;
            if (*pKey == *(uint32*)node) break;
            pSlot = (char*)node + 0x18;
        } while (*(uint32*)pSlot != 0);
        while (*(uint32*)pSlot != 0) {
            node = *(uint32*)pSlot;
            if (*pKey != *(uint32*)node) break;
            *(uint32*)pSlot = *(uint32*)(node + 0x18);
            uint32* pBegin = *(uint32**)(node + 4);
            if (pBegin) {
                Alloc* pAlloc = *(Alloc**)(node + 0x10);
                uint32 nBytes = ((*(uint32**)(node + 0xc) - pBegin) >> 2) * 4;
                pAlloc->Free(pBegin, nBytes);
            }
            mpAllocator->Free((void*)node, 0x1c);
            --mnElementCount;
        }
    }
    return nBefore - mnElementCount;
}

// ===========================================================================
// @ 0x008E06D0
// ===========================================================================
void HashTable::DoFreeNodes18(void** pBucketArray, uint32 nCount)
{
    for (uint32 i = 0; i < nCount; ++i) {
        char* p = (char*)pBucketArray[i];
        while (p) {
            char* pNode = p;
            void* pBegin = *(void**)(pNode + 4);
            uint32 nEnd = *(uint32*)(pNode + 0xc);
            p = *(char**)(pNode + 0x14);
            int nBytes = (int)(nEnd - (uint32)pBegin) & (int)0xfffffffeu;
            if (nBytes > 2 && pBegin)
                operator delete(pBegin);
            mpAllocator->Free(pNode, 0x18);
        }
        pBucketArray[i] = 0;
    }
}

// ===========================================================================
// @ 0x008E0740
// ===========================================================================
void HashTable::DoFreeNodes20(void** pBucketArray, uint32 nCount)
{
    for (uint32 i = 0; i < nCount; ++i) {
        char* p = (char*)pBucketArray[i];
        while (p) {
            char* pNode = p;
            void* pBegin = *(void**)(pNode + 0xc);
            uint32 nEnd = *(uint32*)(pNode + 0x14);
            p = *(char**)(pNode + 0x1c);
            int nBytes = (int)(nEnd - (uint32)pBegin) & (int)0xfffffffeu;
            if (nBytes > 2 && pBegin)
                operator delete(pBegin);
            mpAllocator->Free(pNode, 0x20);
        }
        pBucketArray[i] = 0;
    }
}

// ===========================================================================
// @ 0x008E07B0
// ===========================================================================
void DBList::Erase(DBNode** ppNode)
{
    Thread::Mutex* pMutex = &mMutex;
    pMutex->Lock((const char*)0x1436AB8);
    DBNode* pNode = mpHead;
    DBNode** ppPrev = &mpHead;
    if (pNode) {
        while (pNode != *ppNode) {
            ppPrev = &pNode->mpNext;
            pNode = pNode->mpNext;
            if (!pNode) { pMutex->Unlock(); return; }
        }
        *ppPrev = pNode->mpNext;
        void** pEnd = (void**)mDeletedEnd;
        if (pEnd < (void**)mDeletedCap) {
            mDeletedEnd = pEnd + 1;
            if (pEnd) *pEnd = pNode;
        } else {
            void* pItem = pNode;
            ((Vec8*)&mDeletedBegin)->DoInsertValue(pEnd, &pItem);
        }
        void* pDB = pNode->mpDatabase;
        void** pVt = *(void***)((char*)pDB + 4);
        ((void (__thiscall*)(void*))pVt[1])((char*)pDB + 4);
    }
    pMutex->Unlock();
}

// ===========================================================================
// @ 0x008E0840
// ===========================================================================
void DBList::Flush()
{
    Thread::Mutex* pMutex = &mMutex;
    pMutex->Lock((const char*)0x1436AB8);
    DBNode* pNode = mpHead;
    DBNode** ppPrev = &mpHead;
    if (pNode) {
        do {
            DBNode* pNext = pNode->mpNext;
            *ppPrev = 0;
            void** pEnd = (void**)mDeletedEnd;
            if (pEnd < (void**)mDeletedCap) {
                mDeletedEnd = pEnd + 1;
                if (pEnd) *pEnd = pNode;
            } else {
                void* pItem = pNode;
                ((Vec8*)&mDeletedBegin)->DoInsertValue(pEnd, &pItem);
            }
            void* pDB = pNode->mpDatabase;
            void** pVt = *(void***)((char*)pDB + 4);
            ((void (__thiscall*)(void*))pVt[1])((char*)pDB + 4);
            ppPrev = &pNode->mpNext;
            pNode = pNext;
        } while (pNode);
    }
    pMutex->Unlock();
}

// ===========================================================================
// @ 0x008E08C0
// ===========================================================================
int Manager::Fn8e08c0(U32Vec* pOut, uint32 nKey)
{
    HashTable* pMap = &mTypeToFactoriesMap;
    void* it[2];
    pMap->find(it, &nKey);
    if (it[0] != pMap->mpBucketArray[pMap->mnBucketCount]) {
        uint32* pNode = (uint32*)it[0];
        pOut->DoInsertFromIterator(pOut->mpEnd, *(uint32**)((char*)pNode + 4),
                                   *(uint32**)((char*)pNode + 8), nKey);
        return (int)((*(uint32**)((char*)pNode + 8) - *(uint32**)((char*)pNode + 4)) >> 2);
    }
    void** pEnd = (void**)pOut->mpEnd;
    if ((uint32*)pEnd < pOut->mpCap) {
        pOut->mpEnd = (uint32*)(pEnd + 1);
        if (pEnd) *(uint32*)pEnd = nKey;
    } else {
        pOut->DoInsertValue((uint32*)pEnd, &nKey);
    }
    return 1;
}

// ===========================================================================
// @ 0x008E0950
// ===========================================================================
int Manager::Fn8e0950(KeyVec* pOut, uint32 nKey)
{
    CNode anchor;
    anchor.mpNext = &anchor;
    anchor.mpPrev = &anchor;

    for (uint32* pIt = (uint32*)mpCompressorBegin; pIt != (uint32*)mpCompressorEnd; pIt += 2) {
        void* pObj = (void*)*pIt;
        typedef void (__thiscall* FnVf24)(void*, CNode*, void*);
        ((FnVf24)(*(void***)pObj)[0x24 / 4])(pObj, &anchor, (void*)nKey);
    }

    int nCount = 0;
    for (CNode* pNode = anchor.mpNext; pNode != &anchor; pNode = pNode->mpNext) {
        Key* pKey = (Key*)((char*)pNode->mpData + 8);
        Key* pEnd = pOut->mpEnd;
        if (pEnd < pOut->mpCap) {
            pOut->mpEnd = pEnd + 1;
            if (pEnd) { pEnd->mInstance = pKey->mInstance; pEnd->mType = pKey->mType; pEnd->mGroup = pKey->mGroup; }
        } else {
            pOut->DoInsertValue(pEnd, pKey);
        }
        ++nCount;
    }

    CNode* pNode = anchor.mpNext;
    while (pNode != &anchor) {
        CNode* pNext = pNode->mpNext;
        if (pNode->mpData) {
            void* pObj = pNode->mpData;
            void** pVt = *(void***)pObj;
            ((void (__thiscall*)(void*))pVt[1])(pObj);
        }
        operator delete(pNode);
        pNode = pNext;
    }
    return nCount;
}

// ===========================================================================
// @ 0x008E0A30
// ===========================================================================
int Manager::Fn8e0a30(KeyVec* pKeys, void* pArg, PtrVec* pFactories)
{
    HashTable tbl;
    tbl.mUnk0 = 0;
    char* pRaw = (char*)&tbl;
    memset(pRaw, 0, 0xc);
    tbl.mpName = 0;

    KeyVec local;
    local.mpBegin = local.mpEnd = local.mpCap = 0;
    int nCount = 0;

    for (DBNode* pNode = mDatabaseList->mpHead; pNode; pNode = pNode->mpNext) {
        void* pDB = pNode->mpDatabase;
        typedef void (__thiscall* FnVf30)(void*, KeyVec*, void*);
        ((FnVf30)(*(void***)pDB)[0x30 / 4])(pDB, &local, pArg);

        int nElems = (int)((local.mpEnd - local.mpBegin) / 3);
        for (int i = 0; i < nElems; ++i) {
            Key* pElem = &local.mpBegin[i];
            int kind;
            FnC77680(&kind, pElem);
            if (kind == 1) {
                if (pKeys) {
                    Key* pEnd = pKeys->mpEnd;
                    if (pEnd < pKeys->mpCap) {
                        pKeys->mpEnd = pEnd + 1;
                        if (pEnd) { pEnd->mInstance = pElem->mInstance; pEnd->mType = pElem->mType; pEnd->mGroup = pElem->mGroup; }
                    } else {
                        pKeys->DoInsertValue(pEnd, pElem);
                    }
                }
                if (pFactories) {
                    void** pEnd = pFactories->mpEnd;
                    if (pEnd < pFactories->mpCap) {
                        pFactories->mpEnd = pEnd + 1;
                        if (pEnd) *pEnd = pDB;
                    } else {
                        void* pVal = pDB;
                        pFactories->DoInsertValue(pEnd, &pVal);
                    }
                }
                void* out[3];
                tbl.insertNode3(out, pElem, 0);
                ++nCount;
            }
        }
        local.mpEnd = local.mpBegin;
    }
    if (local.mpBegin && *(int32*)((char*)local.mpBegin - 4) != 0) {
        operator delete(local.mpBegin);
    }
    return nCount;
}

// ===========================================================================
// @ 0x008E0C10
// ===========================================================================
int Manager::Fn8e0c10(void* pUnused, KeyVec* pOut, uint32 nKey)
{
    (void)pUnused;
    int nCount = 0;
    if ((char)nKey == 0) {
        for (DBNode* pNode = mDatabaseList->mpHead; pNode; pNode = pNode->mpNext) {
            void* pDB = pNode->mpDatabase;
            typedef int (__thiscall* FnVf30)(void*, KeyVec*, void*);
            nCount += ((FnVf30)(*(void***)pDB)[0x30 / 4])(pDB, pOut, (void*)nKey);
        }
        return nCount;
    }

    CNode anchor;
    anchor.mpNext = &anchor;
    anchor.mpPrev = &anchor;

    for (uint32* pIt = (uint32*)mpCompressorBegin; pIt != (uint32*)mpCompressorEnd; pIt += 2) {
        void* pObj = (void*)*pIt;
        typedef void (__thiscall* FnVf24)(void*, CNode*, void*);
        ((FnVf24)(*(void***)pObj)[0x24 / 4])(pObj, &anchor, (void*)nKey);
    }

    for (CNode* pNode = anchor.mpNext; pNode != &anchor; pNode = pNode->mpNext) {
        Key* pKey = (Key*)((char*)pNode->mpData + 8);
        Key* pEnd = pOut->mpEnd;
        if (pEnd < pOut->mpCap) {
            pOut->mpEnd = pEnd + 1;
            if (pEnd) { pEnd->mInstance = pKey->mInstance; pEnd->mType = pKey->mType; pEnd->mGroup = pKey->mGroup; }
        } else {
            pOut->DoInsertValue(pEnd, pKey);
        }
        ++nCount;
    }

    CNode* pNode = anchor.mpNext;
    while (pNode != &anchor) {
        CNode* pNext = pNode->mpNext;
        if (pNode->mpData) {
            void* pObj = pNode->mpData;
            void** pVt = *(void***)pObj;
            ((void (__thiscall*)(void*))pVt[1])(pObj);
        }
        operator delete(pNode);
        pNode = pNext;
    }
    return nCount;
}

// ===========================================================================
// @ 0x008E0D30
// ===========================================================================
char Manager::RegisterDatabase(char bAdd, void* pDatabase, int a3)
{
    if (bAdd) {
        typedef char (__thiscall* FnVf54)(void*, void*, int);
        if (((FnVf54)(*(void***)this)[0x54 / 4])(this, pDatabase, 0))
            return 0;
        mDatabaseList->Add(pDatabase, a3);
        ((Factory*)pDatabase)->AddRef();
        typedef char (__thiscall* FnVf44)(void*, int, void*, int);
        return ((FnVf44)(*(void***)pDatabase)[0x44 / 4])(pDatabase, 1, this, 1);
    }
    for (DBNode* pNode = mDatabaseList->mpHead; pNode; pNode = pNode->mpNext) {
        if (pNode->mpDatabase != pDatabase) continue;
        void* pFound = pNode->mpDatabase;
        void* pSub = (char*)pFound + 4;
        typedef void (__thiscall* FnVf0)(void*);
        ((FnVf0)(*(void***)pSub)[0])(pSub);
        mDatabaseList->Erase(&pNode);
        typedef char (__thiscall* FnVf44)(void*, int, void*, int);
        char bOk = ((FnVf44)(*(void***)pFound)[0x44 / 4])(pFound, 0, this, 1);
        typedef int (__thiscall* FnVf10)(void*);
        if (((FnVf10)(*(void***)pFound)[0x10 / 4])(pFound) == 1) {
            ((FnVf0)(*(void***)pFound)[0x08 / 4])(pFound);
        }
        ((FnVf0)(*(void***)pSub)[1])(pSub);
        return bOk;
    }
    return 0;
}

// ===========================================================================
// @ 0x008E0E10
// ===========================================================================
void* HashTable::refKey(uint32 nKey)
{
    void* it[2];
    findString(it, (const uint32*)nKey);
    if (it[0] != mpBucketArray[mnBucketCount])
        return (char*)it[0] + 4;

    WString tmp;
    tmp.mpBegin = (void*)0x1667BAC;
    tmp.mpEnd = (void*)0x1667BAC;
    tmp.mpCap = (void*)0x1667BAE;
    char pairBuf[0x14];
    void* pPair = ((MapPairProxy*)pairBuf)->makePair(nKey, &tmp);
    void* out;
    insertNode18(&out, pPair, (void*)0);
    void* pResult = (char*)out + 4;

    void* pBegin = *(void**)((char*)pairBuf + 4);
    uint32 nBytes = (*(uint32*)((char*)pairBuf + 0xc)) - (uint32)pBegin;
    nBytes &= 0xfffffffeu;
    if (nBytes > 2 && pBegin)
        operator delete(pBegin);
    return pResult;
}
