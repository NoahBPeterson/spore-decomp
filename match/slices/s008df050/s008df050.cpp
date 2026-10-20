// Slice s008df050 (0x8df050..0x8dfef0) - EA::ResourceMan::Manager resource/factory
// lookup, the typenname<->type maps, and the change-notification rbtree insert helper.
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE
//
// Functions (VA, name):
//   008df050  AutoRefCount<Factory> range move-assign (backward)
//   008df0b0  Manager::GetResourceInternal
//   008df430  Manager::GetResource
//   008df460  Manager::GetResourceAsync
//   008df7a0  Manager::ReloadResource
//   008df940  Manager::GetPrivateResource
//   008df970  Manager::FindTextStyleType
//   008df9b0  Manager::FindResourceFactory
//   008dfb20  Manager::FindFactory
//   008dfba0  Manager::GetTypeFromTypename
//   008dfc60  Manager::GetTypenameFromType
//   008dfcd0  hashtable::insertNode (key = 3 dwords, hash = k0 ^ k2)
//   008dfde0  rbtree<ChangeNotificationInfo>::DoInsertValue
//   008dfed0  AutoRefVec::assign-from-range ctor helper

#include <string.h>
#include "types.h"

typedef unsigned int uint32;
typedef int          int32;
typedef unsigned char uint8;

namespace EA {

namespace Thread {
// thiscall; the callee pops its arguments.
struct Mutex {
    char mData[0x30];
    void Lock(const char* pName);   // 0x009221B0
    int  Unlock();                  // 0x00922270
};
}  // namespace Thread

// COM-style object: vtable slot +0x04 AddRef, +0x08 Release.
struct IRefCounted {
    virtual void Slot0();
    virtual void AddRef();          // +0x04
    virtual void Release();         // +0x08
};

namespace ResourceMan {

struct Key {
    uint32 mInstance;   // +0x00
    uint32 mType;       // +0x04
    uint32 mGroup;      // +0x08
};

// Shared header of every node-based eastl::hashtable<unsigned, ...> instantiation here.
// The find() bodies live in other translation units; only the shape matters.
struct HashTable {
    uint32 mUnk0;               // +0x00
    void** mpBucketArray;       // +0x04
    uint32 mnBucketCount;       // +0x08
    uint32 mnElementCount;      // +0x0c
    uint32 mRehash[3];          // +0x10
    void* mpAllocator;          // +0x1c
    const char* mpName;         // +0x20

    void** find(void** ppOut, const uint32* pKey);        // 0x00AEA1B0
    void** findFixed(void** ppOut, const uint32* pKey);   // 0x00645ED0
    void** findString(void** ppOut, const uint32* pKey);  // 0x00A3B2C0
    void doRehash(uint32 nBucketCount);                   // 0x008DE740
    void* insertNode3(void* pOut, void* pKey, void* p3);  // 0x008DFCD0
};

// The rehash policy object embedded at HashTable+0x10.
struct RehashPolicy {
    void evaluate(void* pOut, uint32 nBucketCount, uint32 nElementCount, int one);  // 0x00921440
};

// Result written by RehashPolicy::evaluate: a "grew" flag and the new bucket count.
struct RehashResult {
    uint8  mbGrew;          // +0x00
    char   _pad01[3];
    uint32 mnBucketCount;   // +0x04
};

struct CacheRes;

// A ResourceMan factory: reference-counted COM object with the slots this slice uses.
struct Factory {
    virtual void Slot00();                                                        // +0x00
    virtual void AddRef();                                                        // +0x04
    virtual void Release();                                                       // +0x08
    virtual void Slot0C();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C(void* a, void* b, void* c, void* d);                      // +0x1c
    virtual void Slot20();
    virtual void Slot24();                                                        // +0x24
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30();
    virtual char Init(Key* pKey, void* pTypeParam, int a, int b, int c, int d);   // +0x34
};

// An AutoRefCount<Factory>: pointer + user field, with *virtual* AddRef/Release
// (unlike the interlocked AutoRefObj variant used by the change-notification maps).
struct AutoRefFactory {
    Factory* mpObject;  // +0x00
    int      mField;    // +0x04
};

// eastl::hashtable node for maps keyed by one uint32 with a 4-byte payload.
struct HashNode4 {
    uint32 mKey;        // +0x00
    void*  mpValue;     // +0x04
    void*  mpNext;      // +0x08
};

// Fixed-capacity hashtable node with a 3-dword key, used by the 0x8dfcd0 insert.
struct HashNode12 {
    uint32 mKey0;       // +0x00
    uint32 mKey1;       // +0x04
    uint32 mKey2;       // +0x08
    void*  mpNext;      // +0x0c
};

// Node of the typename<->type map: wchar_t* name + next link at +0x14.
struct NameNode {
    uint32      mType;  // +0x00
    const wchar_t* mpName;  // +0x04
    char        pad08[0x0c];
    NameNode*   mpNext; // +0x14
};

// AutoRefCount<pair<Factory,int>> holder (8 bytes) used by the vector helpers.
struct AutoRefObj {
    void* mpObject;     // +0x00
    int   mField;       // +0x04
};

// A vector of AutoRefObj: begin/end/capacity/allocator/name at +0x10.
struct AutoRefVec {
    AutoRefObj* mpBegin;      // +0x00
    AutoRefObj* mpEnd;        // +0x04
    AutoRefObj* mpCapacity;   // +0x08
    void* mpAllocator;        // +0x0c
    void* mpName;             // +0x10

    void* allocateStorage(int n, void* pAllocPair);   // 0x008DEF20
};

// ---------------------------------------------------------------------------
// eastl::rbtree<ChangeNotificationInfo, ...> — the manager's change-set tree at
// Manager+0x0c.  Its methods take ecx = &rbtree (NOT &Manager).
// ---------------------------------------------------------------------------
namespace eastl_shim {

struct RbNodeBase {
    RbNodeBase* mpNodeRight;   // +0x00
    RbNodeBase* mpNodeLeft;    // +0x04
    RbNodeBase* mpNodeParent;  // +0x08
    uint32      mnColor;       // +0x0c
};

// The payload carried by a change-set node: key + priority.
struct ChangeInfo {
    Key  mKey;        // +0x00
    int  mnPriority;  // +0x0c
};

struct ChangeNode {
    RbNodeBase base;    // +0x00
    ChangeInfo info;    // +0x10 (mKey at +0x10, priority at +0x1c)
};

struct ChangeSet {
    uint32 mUnk0;              // +0x00
    RbNodeBase mAnchor;        // +0x04  (root = mAnchor.mpNodeParent at +0x0c)
    uint32 mnSize;             // +0x14
    void* mpAllocator;         // +0x18
    const char* mpName;        // +0x1c

    void  DoInsertValueImpl(void* ppNode, void* pParent, const void* pValue, char bForceLeft);  // 0x008DEE90
    void* DoInsertValue(void* pOut, const void* pValue, void* pUnused);                          // 0x008DFDE0
};

RbNodeBase* __cdecl RBTreeDecrement(const RbNodeBase* pNode);   // 0x009215C0

// ChangeNotificationInfoCompare: priority descending, then key ascending.
inline bool ChangeLess(const ChangeInfo* lhs, const ChangeInfo* rhs)
{
    if (lhs->mnPriority != rhs->mnPriority)
        return rhs->mnPriority < lhs->mnPriority;
    if (lhs->mKey.mInstance != rhs->mKey.mInstance)
        return lhs->mKey.mInstance < rhs->mKey.mInstance;
    if (lhs->mKey.mType != rhs->mKey.mType)
        return lhs->mKey.mType < rhs->mKey.mType;
    return lhs->mKey.mGroup < rhs->mKey.mGroup;
}

}  // namespace eastl_shim

// ---------------------------------------------------------------------------
// Manager
// ---------------------------------------------------------------------------
struct Manager {
    void** vftable;                 // +0x00
    uint8  mbInitialized;           // +0x04
    char   _pad05[3];
    void*  mpAllocator;             // +0x08
    eastl_shim::ChangeSet mChangeSet;   // +0x0c (0x20 bytes)
    void*  mDatabaseList;           // +0x2c
    HashTable mTypeToFactoryMap;    // +0x30
    HashTable mTypeToFactoriesMap;  // +0x54
    HashTable mTextStyleMap;        // +0x78
    void*  mpCompressorBegin;       // +0x9c
    void*  mpCompressorEnd;         // +0xa0
    char   _padA4[0x0c];
    HashTable mTypenameMap;         // +0xb0
    char   _padD4[0x44];
    Thread::Mutex mNameMutex;       // +0x118
    Thread::Mutex mAsyncMutex;      // +0x148

    char CheckCacheInternal(CacheRes* p1, void* p2, void** ppOut, char flag);  // 0x008DE9D0

    __declspec(noinline)
    char GetResourceInternal(char bFlag, Key* pKey, void* p3, int a4,
                             void* pFactory, void** ppRes, Key* pKeyOut);
    char GetResource(int a1, int a2, int a3, int a4, int a5, int a6);
    char GetPrivateResource(int a1, int a2, int a3, int a4, int a5, int a6);
    char GetResourceAsync(Key* pKey, void** ppOut, void* p3, int a4, void* a5,
                          void* pFactory, void* p7, Key* pKeyOut);
    char ReloadResource(Key* pKey, void* p2, int a4, void* pFactory, int* p5);

    int32 FindTextStyleType(int32 nType);
    void* FindResourceFactory(Key* pKey, Key* pOut, Factory* pFac);
    Factory* FindFactory(uint32 nType, int nFilter);
    uint32 GetTypeFromTypename(const wchar_t* pName);
    const wchar_t* GetTypenameFromType(uint32 nType);
};

// ---------------------------------------------------------------------------
// external helpers (bodies live in other translation units)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl EAAllocate(uint32 nSize, const char* pName, int a, int b,
                                    const char* pFile, int nLine);                                     // 0x00F473A0
extern "C" void* __cdecl MakeTypeParam(int a, int b, int c, int d);                                // 0x00C463D0
extern "C" void* __cdecl AutoRefAsPPTypeParam(void* pThis, int a, int b);                          // 0x00A16F40
extern "C" int   __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);                             // msvcr90

void* __cdecl Fn8de840(void** ppOut, AutoRefObj* first, AutoRefObj* last, AutoRefObj* dest,
                       void* pAlloc);   // 0x008DE840 (5-arg call site; allocator unused)
void* ChangeGetSource();                                                                       // 0x008D5D00

}  // namespace ResourceMan
}  // namespace EA

using namespace EA;
using namespace EA::ResourceMan;

// ===========================================================================
// @ 0x008DF050
// ===========================================================================
AutoRefFactory* AutoRefMoveBackward(AutoRefFactory* first, AutoRefFactory* last, AutoRefFactory* dest)
{
    if (last == first) return dest;
    do {
        Factory* pSrc = last[-1].mpObject;
        Factory* pOld = dest[-1].mpObject;
        --last;
        --dest;
        if (pSrc != pOld) {
            if (pSrc) pSrc->AddRef();
            dest->mpObject = pSrc;
            if (pOld) pOld->Release();
        }
        dest->mField = last->mField;
    } while (last != first);
    return dest;
}

// ===========================================================================
// @ 0x008DF0B0
// ===========================================================================
__declspec(noinline)
char Manager::GetResourceInternal(char bFlag, Key* pKey, void* p3, int a4,
                                  void* pFactory, void** ppRes, Key* pKeyOut)
{
    typedef void*  (__thiscall* FnVf30)(void*, Key*, Key*, void*);
    typedef void*  (__thiscall* FnVf58)(void*, Key*);
    typedef void*  (__thiscall* FnVf48)(void*, uint32, uint32);
    typedef void   (__thiscall* FnVf6C)(void*, void*, int);
    typedef void*  (__thiscall* FnVf1C)(void*, void*, void*, void*, uint32);

    char result = 0;
    if (bFlag) {
        void* pCacheKey = pKeyOut ? (void*)pKeyOut : (void*)pKey;
        result = CheckCacheInternal((CacheRes*)pCacheKey, p3, 0, 0);
        if (result) return result;
    }
    Key key = *pKey;
    Factory* pFac = (Factory*)pFactory;
    Key* pOutKey = pKeyOut;
    if (!pFac) {
        if (!pKeyOut) {
            pFac = (Factory*)((FnVf30)(*(void***)this)[0x30 / 4])(this, pKey, &key, 0);
            pOutKey = pKey;
        } else {
            pFac = (Factory*)((FnVf58)(*(void***)this)[0x58 / 4])(this, &key);
        }
        if (!pFac) return result;
    }
    if (!p3) {
        if (!pOutKey) {
            if (!((FnVf30)(*(void***)this)[0x30 / 4])(this, pKey, &key, pFac)) return 0;
            if (!((FnVf48)(*(void***)this)[0x48 / 4])(this, key.mType, -1)) return 0;
            return 1;
        }
        if (a4 != 0 && !((FnVf48)(*(void***)this)[0x48 / 4])(this, pOutKey->mType, -1)) return result;
        return pFac->Init(&key, 0, 1, 6, 1, 0);
    }
    // p3 != 0: the resource is being fetched for real.
    Factory* pFound = 0;
    char bOk = 0;
    void* pRef = 0;
    if (pOutKey) {
        pFound = pFactory ? (Factory*)pFactory
                          : (Factory*)((FnVf48)(*(void***)this)[0x48 / 4])(this, key.mType, pOutKey->mType);
        if (!pFound) goto cleanup;
        bOk = pFac->Init(&key, MakeTypeParam(1, 3, 1, 0), 0, 0, 0, 0);
    } else {
        void* pNode;
        mTypeToFactoriesMap.find(&pNode, &pKey->mType);
        if (pNode == mTypeToFactoriesMap.mpBucketArray[mTypeToFactoriesMap.mnBucketCount]) {
            pFound = pFactory ? (Factory*)pFactory
                              : (Factory*)((FnVf48)(*(void***)this)[0x48 / 4])(this, key.mType, key.mType);
            if (!pFound) goto cleanup;
            bOk = pFac->Init(&key, MakeTypeParam(1, 3, 1, 0), 0, 0, 0, 0);
        } else {
            AutoRefObj* pBegin = *(AutoRefObj**)((uint32*)pNode + 1);
            AutoRefObj* pEnd = *(AutoRefObj**)((uint32*)pNode + 2);
            for (; pBegin != pEnd; ++pBegin) {
                uint32 nType = (uint32)pBegin->mpObject;
                pFound = pFactory ? (Factory*)pFactory
                                  : (Factory*)((FnVf48)(*(void***)this)[0x48 / 4])(this, nType, pKey->mType);
                if (!pFound) continue;
                if (pRef) { void* t = pRef; pRef = 0; ((IRefCounted*)t)->Release(); }
                bOk = pFac->Init(&key, MakeTypeParam(1, 3, 1, 0), 0, 0, 0, 0);
                if (bOk) break;
            }
        }
    }
    if (bOk) {
        void* pRes = pFound;
        ((IRefCounted*)pRes)->Slot0();
        if (result) {
            void* pOut2 = *ppRes;
            ((Factory*)pFound)->Slot1C(pOut2, p3, (void*)a4, (void*)pOutKey);
        }
    }
cleanup:
    if (pRef) ((IRefCounted*)pRef)->Release();
    return result;
}

// ===========================================================================
// @ 0x008DF430
// ===========================================================================
char Manager::GetResource(int a1, int a2, int a3, int a4, int a5, int a6)
{
    return GetResourceInternal(1, (Key*)a1, (void*)a2, a3, (void*)a4, (void**)a5, (Key*)a6);
}

// ===========================================================================
// @ 0x008DF460
// ===========================================================================
char Manager::GetResourceAsync(Key* pKey, void** ppOut, void* p3, int a4, void* a5,
                               void* pFactory, void* p7, Key* pKeyOut)
{
    typedef void*  (__thiscall* FnVf30)(void*, Key*, Key*, void*);
    typedef void*  (__thiscall* FnVf58)(void*, Key*);
    typedef void*  (__thiscall* FnVf48)(void*, uint32, uint32);
    typedef char   (__thiscall* FnVf34)(void*, Key*, void*, int, int, int, int);
    typedef char   (__thiscall* FnVf10)(void*, void*, void*, void*, void*, void*, int);

    void* pCache = 0;
    void* pCacheKey = pKeyOut ? (void*)pKeyOut : (void*)pKey;
    char result = CheckCacheInternal((CacheRes*)pCacheKey, p3, &pCache, 0);
    if (result) {
        if (!ppOut) return result;
        *ppOut = pCache;
        return result;
    }
    Key key = *pKey;
    Factory* pFac = (Factory*)pFactory;
    Key* pOutKey = pKeyOut;
    if (!pFac) {
        if (!pKeyOut) {
            pFac = (Factory*)((FnVf30)(*(void***)this)[0x30 / 4])(this, pKey, &key, 0);
            pOutKey = pKey;
        } else {
            pFac = (Factory*)((FnVf58)(*(void***)this)[0x58 / 4])(this, &key);
        }
        if (!pFac) goto cleanup;
    }
    if (!a4) {
        if (!pOutKey) {
            if (!((FnVf30)(*(void***)this)[0x30 / 4])(this, pKey, &key, pFac)) { result = 0; goto cleanup; }
            result = ((FnVf48)(*(void***)this)[0x48 / 4])(this, key.mType, -1) != 0;
            goto cleanup;
        }
        if (!a5 && !((FnVf48)(*(void***)this)[0x48 / 4])(this, pOutKey->mType, -1)) goto cleanup;
        result = pFac->Init(&key, 0, 1, 6, 1, 0);
        goto cleanup;
    }
    {
        mAsyncMutex.Lock((const char*)0x1436AB8);
        void* pLookup = pKeyOut ? (void*)pKeyOut : (void*)&key;
        result = CheckCacheInternal((CacheRes*)pLookup, p3, 0, 1);
        if (!result) {
            char bOk = 0;
            if (!pKeyOut) {
                void* pNode;
                mTypeToFactoriesMap.find(&pNode, &pKey->mType);
                if (pNode == mTypeToFactoriesMap.mpBucketArray[mTypeToFactoriesMap.mnBucketCount]) {
                    if (a5 || (a5 = ((FnVf48)(*(void***)this)[0x48 / 4])(this, key.mType, key.mType), a5 != 0)) {
                        void* pTypeParam = MakeTypeParam(1, 3, 1, 0);
                        bOk = ((FnVf34)(*(void***)pFac)[0x34 / 4])(pFac, &key, pTypeParam, 0, 0, 0, 0);
                    }
                } else {
                    AutoRefObj* pBegin = *(AutoRefObj**)((uint32*)pNode + 1);
                    AutoRefObj* pEnd = *(AutoRefObj**)((uint32*)pNode + 2);
                    for (; pBegin != pEnd; ++pBegin) {
                        uint32 nType = (uint32)pBegin->mpObject;
                        if (a5 || (a5 = ((FnVf48)(*(void***)this)[0x48 / 4])(this, nType, pKey->mType), a5 != 0)) {
                            void* pTypeParam = MakeTypeParam(1, 3, 1, 0);
                            bOk = ((FnVf34)(*(void***)pFac)[0x34 / 4])(pFac, &key, pTypeParam, 0, 0, 0, 0);
                            if (bOk) break;
                        }
                    }
                }
            } else {
                if (!a5 && (a5 = ((FnVf48)(*(void***)this)[0x48 / 4])(this, pOutKey->mType, -1), a5 == 0))
                    goto unlock;
                void* pTypeParam = MakeTypeParam(1, 3, 1, 0);
                bOk = ((FnVf34)(*(void***)pFac)[0x34 / 4])(pFac, &key, pTypeParam, 0, 0, 0, 0);
            }
            if (bOk) {
                void* pSrc = ChangeGetSource();
                if (pSrc == 0) {
                    result = 0;
                } else {
                    result = ((FnVf10)(*(void***)pSrc)[0x10 / 4])(pSrc, (void*)a5, p3, (void*)a4, p7, pKeyOut, 1) ? 1 : 0;
                }
            }
        }
    unlock:
        mAsyncMutex.Unlock();
    }
cleanup:
    if (pCache) ((IRefCounted*)pCache)->Release();
    return result;
}

// ===========================================================================
// @ 0x008DF7A0
// ===========================================================================
char Manager::ReloadResource(Key* pKey, void* p2, int a4, void* pFactory, int* p5)
{
    typedef void*  (__thiscall* FnVf58)(void*, Key*);
    typedef void*  (__thiscall* FnVf48)(void*, uint32, uint32);
    typedef char   (__thiscall* FnVf34)(void*, Key*, void**, int, int, int, int);
    typedef char   (__thiscall* FnVf24)(void*, void*, void*, int, void*);
    typedef void   (__thiscall* FnVf24v)(void*);

    char bInit = 0;
    char bFound = 0;
    void* pRef = 0;
    void* pOwner = p5;
    if (!pFactory)
        pFactory = (void*)((FnVf58)(*(void***)this)[0x58 / 4])(this, pKey);

    void* it[2];
    mTypeToFactoriesMap.find(it, &pKey->mType);
    if (it[0] == mTypeToFactoriesMap.mpBucketArray[mTypeToFactoriesMap.mnBucketCount]) {
        if (!pOwner) {
            pOwner = (void*)((FnVf48)(*(void***)this)[0x48 / 4])(this, pKey->mType,
                                                                  *(uint32*)((char*)p2 + 0xc));
            if (!pOwner) goto cleanup;
        }
        if (pRef) { void* t = pRef; pRef = 0; ((IRefCounted*)t)->Release(); }
        bInit = ((FnVf34)(*(void***)pFactory)[0x34 / 4])(pFactory, pKey, &pRef, 1, 3, 1, 0);
    } else {
        Key key = *pKey;
        uint32* pEnd = *(uint32**)((char*)it[0] + 8);
        for (uint32* pCur = *(uint32**)((char*)it[0] + 4); pCur != pEnd; ++pCur) {
            key.mType = *pCur;
            void* pFound = pOwner;
            if (!pOwner) {
                pFound = (void*)((FnVf48)(*(void***)this)[0x48 / 4])(this, key.mType,
                                                                      *(uint32*)((char*)p2 + 0xc));
                if (!pFound) continue;
            }
            if (pRef) { void* t = pRef; pRef = 0; ((IRefCounted*)t)->Release(); }
            bInit = ((FnVf34)(*(void***)pFactory)[0x34 / 4])(pFactory, &key, &pRef, 1, 3, 1, 0);
            if (bInit) { pOwner = pFound; break; }
        }
    }
    if (pOwner && bInit) {
        bFound = ((FnVf24)(*(void***)pOwner)[0x24 / 4])(pOwner, pRef, p2, a4,
                                                        (void*)*(uint32*)((char*)p2 + 0xc));
        ((FnVf24v)(*(void***)pRef)[0x24 / 4])(pRef);
    }
cleanup:
    if (pRef) ((IRefCounted*)pRef)->Release();
    return bFound;
}

// ===========================================================================
// @ 0x008DF940
// ===========================================================================
char Manager::GetPrivateResource(int a1, int a2, int a3, int a4, int a5, int a6)
{
    return GetResourceInternal(0, (Key*)a1, (void*)a2, a3, (void*)a4, (void**)a5, (Key*)a6);
}

// ===========================================================================
// @ 0x008DF970
// ===========================================================================
int32 Manager::FindTextStyleType(int32 nType)
{
    HashTable* pMap = &mTextStyleMap;
    void* it[2];
    int32 result = nType;
    void** ppNode = pMap->findFixed(it, (const uint32*)&nType);
    if (*ppNode != pMap->mpBucketArray[pMap->mnBucketCount])
        result = *(int32*)((char*)*ppNode + 4);
    return result;
}

// ===========================================================================
// @ 0x008DF9B0
// ===========================================================================
void* Manager::FindResourceFactory(Key* pKey, Key* pOut, Factory* pFac)
{
    typedef char  (__thiscall* FnVf34)(void*, Key*, int, int, int, int, int);
    typedef void* (__thiscall* FnVf58)(void*, Key*);

    HashTable* pMap = &mTypeToFactoriesMap;
    void* it[2];
    pMap->find(it, &pKey->mType);
    void* pNode = it[0];
    if (pNode == pMap->mpBucketArray[pMap->mnBucketCount]) {
        if (!pFac) {
            pFac = (Factory*)((FnVf58)(*(void***)this)[0x58 / 4])(this, pKey);
        } else if (!((FnVf34)(*(void***)pFac)[0x34 / 4])(pFac, pKey, 0, 1, 6, 1, 0)) {
            return 0;
        }
        if (pFac && pOut) *pOut = *pKey;
        return pFac;
    }
    Key key = *pKey;
    if (!pFac) {
        int* pEntry = *(int**)((char*)this + 0x2c);
        if (!pEntry) return 0;
        do {
            uint32* pEnd = *(uint32**)((char*)pNode + 8);
            pFac = (Factory*)pEntry[1];
            for (uint32* pCur = *(uint32**)((char*)pNode + 4); pCur != pEnd; ++pCur) {
                key.mType = *pCur;
                if (((FnVf34)(*(void***)pFac)[0x34 / 4])(pFac, &key, 0, 1, 6, 1, 0)) goto found;
            }
            pEntry = (int*)*pEntry;
        } while (pEntry);
        return 0;
    }
    {
        uint32* pEnd = *(uint32**)((char*)pNode + 8);
        for (uint32* pCur = *(uint32**)((char*)pNode + 4); pCur != pEnd; ++pCur) {
            key.mType = *pCur;
            if (((FnVf34)(*(void***)pFac)[0x34 / 4])(pFac, &key, 0, 1, 6, 1, 0)) goto found;
        }
    }
    return 0;
found:
    if (pOut) *pOut = key;
    return pFac;
}

// ===========================================================================
// @ 0x008DFB20
// ===========================================================================
Factory* Manager::FindFactory(uint32 nType, int nFilter)
{
    typedef char (__thiscall* FnVf30)(void*, uint32, int);

    HashTable* pMap = &mTypeToFactoryMap;
    void* it[2];
    void** ppNode = pMap->find(it, &nType);
    void* pNode = *ppNode;
    int filter = nFilter;
    if (nType == (uint32)filter) filter = -1;
    if (pNode == pMap->mpBucketArray[pMap->mnBucketCount]) return 0;
    AutoRefObj* pBegin = *(AutoRefObj**)((uint32*)pNode + 1);
    AutoRefObj* pEnd = *(AutoRefObj**)((uint32*)pNode + 2);
    for (; pBegin != pEnd; ++pBegin) {
        Factory* pFac = (Factory*)pBegin->mpObject;
        if (filter == -1 || ((FnVf30)(*(void***)pFac)[0x30 / 4])(pFac, nType, filter)) return pFac;
    }
    return 0;
}

// ===========================================================================
// @ 0x008DFBA0
// ===========================================================================
uint32 Manager::GetTypeFromTypename(const wchar_t* pName)
{
    Thread::Mutex* pMutex = &mNameMutex;
    pMutex->Lock((const char*)0x1436AB8);
    NameNode** ppBucket = (NameNode**)mTypenameMap.mpBucketArray;
    NameNode* pNode = *ppBucket;
    if (!pNode) {
        do { ++ppBucket; } while (*ppBucket == 0);
        pNode = *ppBucket;
    }
    while (pNode != (NameNode*)mTypenameMap.mpBucketArray[mTypenameMap.mnBucketCount]) {
        if (_wcsicmp(pNode->mpName, pName) == 0) {
            uint32 result = pNode->mType;
            pMutex->Unlock();
            return result;
        }
        pNode = pNode->mpNext;
        if (!pNode) {
            do { ++ppBucket; pNode = *ppBucket; } while (!pNode);
        }
    }
    pMutex->Unlock();
    return 0xffffffff;
}

// ===========================================================================
// @ 0x008DFC60
// ===========================================================================
const wchar_t* Manager::GetTypenameFromType(uint32 nType)
{
    Thread::Mutex* pMutex = &mNameMutex;
    pMutex->Lock((const char*)0x1436AB8);
    HashTable* pMap = &mTypenameMap;
    void* it[2];
    void** ppNode = pMap->findString(it, &nType);
    void* pNode = it[0];
    if (pNode != pMap->mpBucketArray[pMap->mnBucketCount]) {
        const wchar_t* pResult = (const wchar_t*)((void**)pNode)[1];
        pMutex->Unlock();
        return pResult;
    }
    pMutex->Unlock();
    return 0;
}

// ===========================================================================
// @ 0x008DFCD0
// ===========================================================================
void* HashTable::insertNode3(void* pOut, void* pKey, void* p3)
{
    (void)p3;
    HashNode12* pK = (HashNode12*)pKey;
    uint32 hash = pK->mKey0 ^ pK->mKey2;
    uint32 idx = hash % mnBucketCount;
    HashNode12* pNode = (HashNode12*)mpBucketArray[idx];
    while (pNode) {
        if (pK->mKey0 == pNode->mKey0 && pK->mKey1 == pNode->mKey1 && pK->mKey2 == pNode->mKey2) {
            *(void**)pOut = pNode;
            *((void**)pOut + 1) = &mpBucketArray[idx];
            *((uint8*)pOut + 8) = 0;
            return pOut;
        }
        pNode = (HashNode12*)pNode->mpNext;
    }
    RehashResult pol;
    ((RehashPolicy*)((char*)this + 0x10))->evaluate(&pol, mnBucketCount, mnElementCount, 1);
    HashNode12* pNew = (HashNode12*)EAAllocate(0x10, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (pNew) {
        pNew->mKey0 = pK->mKey0;
        pNew->mKey1 = pK->mKey1;
        pNew->mKey2 = pK->mKey2;
    }
    pNew->mpNext = 0;
    if (pol.mbGrew) {
        idx = hash % pol.mnBucketCount;
        doRehash(pol.mnBucketCount);
    }
    pNew->mpNext = mpBucketArray[idx];
    mpBucketArray[idx] = pNew;
    ++mnElementCount;
    *(void**)pOut = pNew;
    *((void**)pOut + 1) = &mpBucketArray[idx];
    *((uint8*)pOut + 8) = 1;
    return pOut;
}

// ===========================================================================
// @ 0x008DFDE0
// ===========================================================================
void* eastl_shim::ChangeSet::DoInsertValue(void* pOut, const void* pValue, void* pUnused)
{
    (void)pUnused;
    const ChangeInfo* pVal = (const ChangeInfo*)pValue;
    ChangeSet* pSet = this;
    RbNodeBase* pParent = &pSet->mAnchor;
    char bLess = 1;
    RbNodeBase* pIter = pSet->mAnchor.mpNodeParent;
    if (pIter) {
        do {
            pParent = pIter;
            bLess = ChangeLess(pVal, &((ChangeNode*)pIter)->info);
            pIter = bLess ? pIter->mpNodeLeft : pIter->mpNodeRight;
        } while (pIter);
    }
    RbNodeBase* pNext = pParent;
    if (bLess) {
        if (pParent == pSet->mAnchor.mpNodeLeft) {
            void* pNode = (void*)pValue;
            pSet->DoInsertValueImpl(&pNode, pParent, pValue, 0);
            *(void**)pOut = pNode;
            *((uint8*)pOut + 4) = 1;
            return pOut;
        }
        pNext = RBTreeDecrement(pParent);
    }
    if (ChangeLess(&((ChangeNode*)pNext)->info, pVal)) {
        void* pNode = (void*)pValue;
        pSet->DoInsertValueImpl(&pNode, pParent, pValue, 0);
        *(void**)pOut = pNode;
        *((uint8*)pOut + 4) = 1;
        return pOut;
    }
    *(void**)pOut = pNext;
    *((uint8*)pOut + 4) = 0;
    return pOut;
}

// ===========================================================================
// @ 0x008DFED0
// ===========================================================================
// A vector owner: an extra 4-byte field followed by an AutoRefVec whose
// mpBegin/mpEnd are the vector's *used* range.
struct VecOwner {
    void*      mpUnk0;   // +0x00
    AutoRefVec vec;      // +0x04
    VecOwner*  AssignRange(VecOwner* pSrc);   // 0x008DFED0
};

VecOwner* VecOwner::AssignRange(VecOwner* pSrc)
{
    mpUnk0 = pSrc->mpUnk0;
    vec.allocateStorage(((char*)pSrc->vec.mpEnd - (char*)pSrc->vec.mpBegin) >> 3,
                        (char*)pSrc + 0x10);
    Fn8de840((void**)&pSrc, pSrc->vec.mpBegin, pSrc->vec.mpEnd, vec.mpBegin, pSrc);
    vec.mpEnd = (AutoRefObj*)pSrc;
    return this;
}
