// src/game/UTFSpore_Win32/DatabaseDirectoryFiles.cpp -- migrated from slice(s) s008d7220 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DatabaseDirectoryFiles.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int __cdecl _wcsicmp(const wchar_t* pA, const wchar_t* pB);
#include <new>

// ---- items of slice s008d7220 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uintptr_t;
extern "C" int __cdecl _wcsicmp(const wchar_t* pA, const wchar_t* pB);
void FixPoolInit(void* pPool, void* pAllocator, unsigned int nNodeSize, unsigned int nNodeCount);
namespace EA {
namespace Allocator {
class ICoreAllocator_s008d_7220
{
public:
    virtual void* Allocate(unsigned int nSize, const char* pName, unsigned int nFlags) = 0;
    virtual void  Free(void* p) = 0;
    static ICoreAllocator_s008d_7220* GetDefaultAllocator();   // 0x00925cb0
};  // namespace Allocator
}
}
namespace EA {
namespace Thread {
class Mutex_s008d_7220
{
public:
    Mutex_s008d_7220() {}
    Mutex_s008d_7220(int nSpinCount, int nType);
    ~Mutex_s008d_7220();
    int Lock(void* pCaller);  // 0x009221b0 (EA::Thread::Mutex::Lock)
    int Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
private:
    uint32_t mpImpl[0x2c / 4];
};  // namespace Thread
}
}
namespace EA {
namespace IO {
bool  ExistsDirectory(const wchar_t* pPath);                 // 0x009322b0
}
}
namespace EA {
namespace IO {
bool  Remove(const wchar_t* pPath);                          // 0x00931fd0
}
}
namespace EA {
namespace IO {
unsigned GetSize(const wchar_t* pPath);                      // 0x00932060
}
}
namespace EA {
namespace IO {
bool  ConcatenatePathComponents(wchar_t* pDst, const wchar_t* pDir, const wchar_t* pFile); // 0x0092fe60
}
}
void  EAOperatorDelete(void* p);                                                                        // 0x00f47380
void WStringFreeSelf(void* pThis);                                           // 0x00931770
namespace EA {
namespace ResourceMan {
struct Key_s008d_7220
{
    uint32_t mnTypeID;      // 0x00
    uint32_t mnGroupID;     // 0x04
    uint32_t mnInstanceID;  // 0x08
};
}
}
namespace EA {
namespace ResourceMan {
struct ListAnchor
{
    void* mpNext;   // 0x00
    void* mpPrev;   // 0x04
};
}
}
namespace EA {
namespace ResourceMan {
class  DatabaseDirectoryFiles;
}
}
namespace EA {
namespace ResourceMan {
struct DDFRecordListData
{
    uint32_t       mnUnknown00;      // +0x00
    const wchar_t* mpNameBegin;      // +0x04 string16.mpBegin
    const wchar_t* mpNameEnd;        // +0x08 string16.mpEnd
    const wchar_t* mpNameCapacity;   // +0x0c string16.mpCapacity
    uint32_t       mnUnknown10;      // +0x10
    uint32_t       mnTimeLow;        // +0x14
    uint32_t       mnTimeHigh;       // +0x18
    ListAnchor     mRecords;         // +0x1c list<AutoRefCount<DDFRecord>>
};
}
}
// The retail image's static empty wchar_t string, used as the default record name.
extern const wchar_t gRecordValueEmptyName[];   // 0x01667bac
namespace EA {
namespace ResourceMan {
// The record map's value as retail lays it out: the string16 name first, one more dword, the two
// file-time words and the record list anchor at +0x18.  Its copy constructor lives outside this TU.
struct RecordValue
{
    const wchar_t* mpNameBegin;     // +0x00
    const wchar_t* mpNameEnd;       // +0x04
    const wchar_t* mpNameCapacity;  // +0x08
    uint32_t       mnUnknown0c;     // +0x0c
    uint32_t       mnTimeHigh;      // +0x10
    uint32_t       mnTimeLow;       // +0x14
    ListAnchor     mRecords;        // +0x18

    void CopyFrom(const RecordValue* pSrc);   // 0x008d6970
};
}
}
namespace EA {
namespace ResourceMan {
struct RBNode
{
    RBNode* mpLeft;    // 0x00
    RBNode* mpRight;   // 0x04
    RBNode* mpParent;  // 0x08
    uint32_t mnColor;  // 0x0c
    Key_s008d_7220 mKey;          // 0x10
    // DDFRecordListData mValue; follows, accessed through the raw node pointer
};
}
}
namespace EA {
namespace ResourceMan {
struct RBTree
{
    void*   mpAllocator;  // +0x00
    RBNode* mpAnchor;     // +0x04 self-referential header node
    RBNode* mpBegin;      // +0x08 left-most node
    RBNode* mpRoot;       // +0x0c
    uint32_t mnUnknown10; // +0x10
    uint32_t mnCount;     // +0x14
    uint32_t mPad18[2];   // +0x18

    void Find(RBNode** ppOut, const Key_s008d_7220* pKey);                    // 0x00a21dc0
    void EraseRecord(void* pArg, RBNode* pNode);                              // 0x008d7200
    void InsertValue(RBNode** ppOut, const void* pValue, const void* pKey);   // 0x008d7220
};
}
}
namespace EA {
namespace ResourceMan {
struct String16
{
    const wchar_t* mpBegin;     // +0x00
    const wchar_t* mpEnd;       // +0x04
    const wchar_t* mpCapacity;  // +0x08

    void assign(const wchar_t* pFirst, const wchar_t* pLast);   // 0x00423650
};
}
}
namespace EA {
namespace ResourceMan {
inline DDFRecordListData* NodeValue(RBNode* pNode)
{
    return reinterpret_cast<DDFRecordListData*>(reinterpret_cast<uint8_t*>(pNode) + 0x1c);
}
}
}
namespace EA {
namespace ResourceMan {
inline bool KeyLess(const Key_s008d_7220& a, const Key_s008d_7220& b)
{
    if (a.mnTypeID != b.mnTypeID)
        return a.mnTypeID < b.mnTypeID;
    if (a.mnInstanceID != b.mnInstanceID)
        return a.mnInstanceID < b.mnInstanceID;
    return a.mnGroupID < b.mnGroupID;
}
}
}
namespace EA {
namespace ResourceMan {
RBNode* RBTreeFindNode(RBTree* pTree, const Key_s008d_7220& key);                              // modelled on rbtree::find
}
}
namespace EA {
namespace ResourceMan {
void    RBTreeDoInsertValueImpl(RBTree* pTree, RBNode* pNode, bool bLeft, const Key_s008d_7220& key, const void* pValue);
}
}
namespace EA {
namespace ResourceMan {
void    RBTreeNukeSubtree(RBTree* pTree, RBNode* pNode);                            // 0x008d6d90 / 0x008d6be0
}
}
namespace EA {
namespace ResourceMan {
RBNode* RBTreeDecrement(RBNode* pNode);                                             // 0x009215c0
}
}
namespace EA {
namespace ResourceMan {
class DatabaseDirectoryFiles
{
public:
    // Virtual interface (vtable 0x01436700 / 0x01482d24 in retail).
    DatabaseDirectoryFiles(const wchar_t* pLocation, EA::Allocator::ICoreAllocator_s008d_7220* pAllocator = 0);
    ~DatabaseDirectoryFiles();

    void* Cast(uint32_t nType);                     // 0x008d81a0
    bool  Close();                                  // 0x008d72f0
    bool  DeleteRecord(const Key_s008d_7220& key);             // 0x008d7350

    // Internal helpers the UpdateRecordData / OpenRecord family call.
    bool  AddFileRecord(const Key_s008d_7220& key, const wchar_t* pFileName, int nHighTime,
                        int nLowTime, int* pOutProc);                 // 0x008d77a0
    int   UpdateAllRecordData(int nFlags);                            // 0x008d7960
    int   UpdateRecordData(const Key_s008d_7220& key, int nFileTime, int nFlags); // 0x008d7a70
    bool  OpenRecord(const Key_s008d_7220& key, int nArg2, uint32_t nArg3, int nArg4,
                     void** ppFileRef, int nArg6);                    // 0x008d7cb0

    // The rbtree member functions reproduced in this TU live in an inner "rbtree" scope so the
    // reconstruction keeps the retail owner names.
    struct RecordMapOps
    {
        static RBNode* DoInsertValue(RBTree* pTree, RBNode** ppOutNode, const Key_s008d_7220* pKey); // 0x008d7220
        // All three retail call sites ignore the result (the value left in EAX is the string
        // destructor's leftover), so the node-creation helper is void.
        void DoCreateNode(const Key_s008d_7220* pKey, const wchar_t* pName,
                          uint32_t nHighTime, uint32_t nLowTime,
                          ListAnchor* pList);                                // 0x008d7610
    };

private:
    void SetLocation(const wchar_t* pLocation);

public:
    // ---- exact retail layout (0x168 bytes, two vtable pointers) ----
    void*  mpVtbl0;                    // 0x000 (Database / ZoneObject)
    void*  mpVtbl1;                    // 0x004 (IUnknown32 / IRefCount)
    int    mnRefCount;                 // 0x008
    bool   mbInitialized;              // 0x00c
    uint8_t mPad0d[3];

    EA::Allocator::ICoreAllocator_s008d_7220* mpAllocator;  // 0x010
    bool   mbRequireDirectoryExists;   // 0x014
    bool   mbRecursive;                // 0x015
    uint8_t mPad16[2];

    uint32_t mnAccessFlags;            // 0x018
    String16 msDirectory;              // 0x01c
    uint32_t mDirectoryAllocator;      // 0x028 (left unset by the ctor)

    uint8_t  mExtensionPool[0x20];     // 0x02c fixed-pool node allocator for mExtensionToTypeMap
    uint8_t  mRecordPool[0x20];        // 0x04c fixed-pool node allocator for mRecordDataMap

    RBTree mExtensionToTypeMap;        // 0x06c  rbtree<string16,uint32>
    RBTree mRecordDataMap;             // 0x08c  rbtree<Key,DDFRecordListData>

    uint32_t mDefaultGroupId;          // 0x0ac
    void*    mpManager;                // 0x0b0  IResourceManager*
    void*    mpFileNameToKeyConverter; // 0x0b4

    uint32_t mKnownTypesBits[0x20];    // 0x0b8  (0x80 bytes, 1024 known type ids)

    EA::Thread::Mutex_s008d_7220 mMutex;          // 0x138
};
}
}
// ---- items of slice s008d7220 end

// @ 0x008d7220
namespace EA { namespace ResourceMan {
RBNode* DatabaseDirectoryFiles::RecordMapOps::DoInsertValue(RBTree* pTree, RBNode** ppOutNode, const Key_s008d_7220* pKey)
{
    RBNode*  pNode = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(pTree) + 4); // &anchor
    RBNode*  r     = pTree->mpRoot;
    bool     bLeft = true;

    if (r != 0)
    {
        do
        {
            pNode = r;
            bLeft = KeyLess(*pKey, r->mKey);
            r = bLeft ? r->mpLeft : r->mpRight;
        } while (r != 0);
    }

    RBNode* pInsertAfter = pNode;
    if (bLeft)
    {
        if (pNode == pTree->mpBegin)
        {
            RBTreeDoInsertValueImpl(pTree, pNode, true, *pKey, 0);
            *ppOutNode = pNode;
            return pNode;
        }
        pInsertAfter = RBTreeDecrement(pNode);
    }

    if (KeyLess(pInsertAfter->mKey, *pKey))
    {
        RBTreeDoInsertValueImpl(pTree, pNode, false, *pKey, 0);
        *ppOutNode = pNode;
        return pNode;
    }

    *ppOutNode = pInsertAfter;
    return pInsertAfter;
}
}}  // namespace EA::ResourceMan

// @ 0x008d72f0
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles::Close()
{
    // CloseOpenRecords() @ 0x008d6770 drops every open record first.
    extern void DatabaseDirectoryFiles_CloseOpenRecords(DatabaseDirectoryFiles* pThis);
    DatabaseDirectoryFiles_CloseOpenRecords(this);

    RBTreeNukeSubtree(&mRecordDataMap, mRecordDataMap.mpRoot);
    mRecordDataMap.mpBegin    = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);
    mRecordDataMap.mpRoot     = 0;
    mRecordDataMap.mnUnknown10 = 0;
    mRecordDataMap.mnCount    = 0;
    *reinterpret_cast<RBNode**>(&mRecordDataMap.mpAnchor) = mRecordDataMap.mpAnchor;

    RBTreeNukeSubtree(&mExtensionToTypeMap, mExtensionToTypeMap.mpRoot);
    mExtensionToTypeMap.mpBegin    = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mExtensionToTypeMap) + 4);
    mExtensionToTypeMap.mpRoot     = 0;
    mExtensionToTypeMap.mnUnknown10 = 0;
    mExtensionToTypeMap.mnCount    = 0;
    mnAccessFlags = 0;
    *reinterpret_cast<RBNode**>(&mExtensionToTypeMap.mpAnchor) = mExtensionToTypeMap.mpAnchor;

    return true;
}
}}  // namespace EA::ResourceMan

// @ 0x008d7350
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles::DeleteRecord(const Key_s008d_7220& key)
{
    bool bRemoved = false;
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    if (mbInitialized && (mnAccessFlags & 2))
    {
        RBNode* pNode = 0;
        mRecordDataMap.Find(&pNode, &key);
        RBNode* pEnd  = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);
        if (pNode != pEnd)
        {
            DDFRecordListData* pValue = NodeValue(pNode);
            if (pValue->mRecords.mpNext == &pValue->mRecords)
            {
                wchar_t path[260];
                EA::IO::ConcatenatePathComponents(path, msDirectory.mpBegin, pValue->mpNameBegin);
                if (EA::IO::Remove(path))
                {
                    mRecordDataMap.EraseRecord(&pNode, pNode);
                    bRemoved = true;
                }
            }
        }
    }

    mMutex.Unlock();
    return bRemoved;
}
}}  // namespace EA::ResourceMan

// @ 0x008d7400
namespace EA { namespace ResourceMan {
DatabaseDirectoryFiles::DatabaseDirectoryFiles(const wchar_t* pLocation, EA::Allocator::ICoreAllocator_s008d_7220* pAllocator)
{
    // Two polymorphic bases -> two vtable pointers.
    mpVtbl0 = reinterpret_cast<void*>(&mExtensionPool);
    mpVtbl1 = reinterpret_cast<void*>(&mRecordPool);
    mnRefCount = 0;
    mpVtbl0 = reinterpret_cast<void*>(&mRecordDataMap);
    mpVtbl1 = reinterpret_cast<void*>(&mExtensionToTypeMap);

    mbInitialized = false;

    if (pAllocator == 0)
        pAllocator = EA::Allocator::ICoreAllocator_s008d_7220::GetDefaultAllocator();
    mpAllocator = pAllocator;

    mbRequireDirectoryExists = false;
    mbRecursive              = false;
    mnAccessFlags            = 0;

    static const wchar_t sEmpty[2] = { 0, 0 };
    msDirectory.mpBegin    = sEmpty;
    msDirectory.mpEnd      = sEmpty;
    msDirectory.mpCapacity = sEmpty + 1;

    FixPoolInit(&mExtensionPool, mpAllocator, 0x20, 0x24);
    FixPoolInit(&mRecordPool,    mpAllocator, 0x80, 0x48);

    mDefaultGroupId          = 0;
    mpManager                = 0;
    mpFileNameToKeyConverter = 0;

    // Initialise the two rbtrees (empty: anchor node self-referential, begin == &anchor).
    RBNode* pAnchorExt = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mExtensionToTypeMap) + 4);
    RBNode* pAnchorRec = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);
    pAnchorExt->mpLeft = pAnchorExt;
    pAnchorRec->mpLeft = pAnchorRec;
    mExtensionToTypeMap.mpAnchor = pAnchorExt;
    mExtensionToTypeMap.mpBegin  = pAnchorExt;
    mExtensionToTypeMap.mpRoot   = 0;
    mExtensionToTypeMap.mnCount  = 0;
    mRecordDataMap.mpAnchor = pAnchorRec;
    mRecordDataMap.mpBegin  = pAnchorRec;
    mRecordDataMap.mpRoot   = 0;
    mRecordDataMap.mnCount  = 0;

    // retail constructs the mutex at 0x138 in place:
    new (&mMutex) EA::Thread::Mutex_s008d_7220(0, 1);

    if (pLocation != 0)
    {
        const wchar_t* pEnd = pLocation;
        while (*pEnd != 0)
            ++pEnd;
        msDirectory.assign(pLocation, pEnd);
        WStringFreeSelf(&msDirectory);
    }

    for (int i = 0; i < 0x20; ++i)
        mKnownTypesBits[i] = 0;
}
}}  // namespace EA::ResourceMan

// @ 0x008d7570
namespace EA { namespace ResourceMan {
DatabaseDirectoryFiles::~DatabaseDirectoryFiles()
{
    mpVtbl0 = reinterpret_cast<void*>(&mRecordDataMap);
    mpVtbl1 = reinterpret_cast<void*>(&mExtensionToTypeMap);

    if (mnAccessFlags != 0)
        Close();

    if (mbInitialized)
    {
        mbInitialized = false;
        // Release the directory handle through the vtable slot at +0x1c.
        typedef void (*ReleaseFn)(DatabaseDirectoryFiles*);
        ReleaseFn pRelease = *reinterpret_cast<ReleaseFn*>(reinterpret_cast<uint8_t*>(mpVtbl0) + 0x1c);
        if (pRelease)
            pRelease(this);
    }

    mMutex.~Mutex_s008d_7220();

    RBTreeNukeSubtree(&mRecordDataMap, mRecordDataMap.mpRoot);
    RBTreeNukeSubtree(&mExtensionToTypeMap, mExtensionToTypeMap.mpRoot);

    if (msDirectory.mpBegin != 0 &&
        (reinterpret_cast<uintptr_t>(msDirectory.mpCapacity) - reinterpret_cast<uintptr_t>(msDirectory.mpBegin)) > 2)
    {
        EAOperatorDelete(const_cast<wchar_t*>(msDirectory.mpBegin));
    }

    mpVtbl1 = reinterpret_cast<void*>(&mRecordPool);
    mpVtbl0 = reinterpret_cast<void*>(&mExtensionPool);
}
}}  // namespace EA::ResourceMan

// @ 0x008d7610
namespace EA { namespace ResourceMan {
void DatabaseDirectoryFiles::RecordMapOps::DoCreateNode(const Key_s008d_7220* pKey, const wchar_t* pName, uint32_t nHighTime, uint32_t nLowTime, ListAnchor* pList)
{
    // ECX holds the owning DatabaseDirectoryFiles; the record map is embedded at +0x8c.
    RBTree* pTree = reinterpret_cast<RBTree*>(reinterpret_cast<uint8_t*>(this) + 0x8c);

    // Mark the record's group in the 0xb8 hash bitmap (key word 1 = the group id).
    uint32_t  nGroup = pKey->mnGroupID;
    uint32_t* pHash  = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0xb8);
    pHash[(nGroup >> 5) & 0x1f] |= 1u << (nGroup & 0x1f);

    // The retail builds a pair<const Key,DDFRecordListData> on the stack and inserts it through the
    // rbtree (ECX = tree). The insert writes its iterator (the new node) followed by a bool into the
    // out slot; the third argument re-uses the dead pKey argument slot, whose low byte was zeroed.
    struct InsertResult { RBNode* pNode; uint32_t bInserted; };
    InsertResult result;
    result.pNode    = 0;
    result.bInserted = 0;
    {
        // Retail pair: the 12-byte key is followed by four bytes of padding, so the value starts
        // at +0x10 (the node keeps the same layout after its 0x10 header).
        struct Pair { Key_s008d_7220 first; uint32_t mnPadKey; DDFRecordListData second; } pair;
        pair.first   = *pKey;
        pair.mnPadKey = 0;

        // Retail copies a default (empty-named) record value into the pair's value slot.
        RecordValue raw;
        raw.mpNameBegin     = gRecordValueEmptyName;
        raw.mpNameEnd       = gRecordValueEmptyName;
        raw.mpNameCapacity  = gRecordValueEmptyName + 2;
        raw.mnUnknown0c     = 0;
        raw.mnTimeHigh      = nHighTime;
        raw.mnTimeLow       = nLowTime;
        raw.mRecords.mpNext = &raw.mRecords;
        raw.mRecords.mpPrev = &raw.mRecords;
        reinterpret_cast<RecordValue*>(&pair.second)->CopyFrom(&raw);

        pTree->InsertValue(&result.pNode, &pair,
                           reinterpret_cast<const void*>(reinterpret_cast<uintptr_t>(pKey) & ~(uintptr_t)0xFF));
    }
    RBNode* pNode = result.pNode;

    if (pNode != 0)
    {
        DDFRecordListData* pValue = NodeValue(pNode);
        if (pValue->mpNameBegin == pValue->mpNameEnd)
        {
            const wchar_t* pEnd = pName;
            while (*pEnd != 0)
                ++pEnd;
            reinterpret_cast<String16*>(&pValue->mpNameBegin)->assign(pName, pEnd);
        }
    }

    if (pList != 0)
    {
        // push_back an AutoRefCount<DDFRecord> onto the node's record list.
        void* pRecord = *reinterpret_cast<void**>(pList);
        if (pRecord != 0)
        {
            typedef void (*AddRefFn)(void*);
            AddRefFn pAddRef = *reinterpret_cast<AddRefFn*>(*reinterpret_cast<uint8_t**>(pRecord) + 4);
            if (pAddRef)
                pAddRef(pRecord);
        }
        (void)pRecord;
    }
}
}}  // namespace EA::ResourceMan

// @ 0x008d77a0
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles::AddFileRecord(const Key_s008d_7220& key, const wchar_t* pFileName, int nHighTime, int nLowTime, int* pOutProc)
{
    wchar_t path[0x820 / 2];   // 0x1040 bytes of stack in the original
    wchar_t directory[260];
    (void)path;

    extern void FilePath_Init(void* pPath, const wchar_t* pName);          // 0x00930f60
    extern const wchar_t* FilePath_GetExtension(void* pPath);              // 0x00930c10
    extern void FilePath_GetDirectory(void* pPath, wchar_t* pDst, int n);  // 0x00930c30
    extern bool GetExtensionToType(const wchar_t* pDir, const wchar_t* pExt, const wchar_t* pName, Key_s008d_7220* pKey); // 0x008d5e10

    FilePath_Init(path, pFileName);
    const wchar_t* pExt = FilePath_GetExtension(path);
    FilePath_GetDirectory(path, directory, 0x100);

    if (_wcsicmp(directory, L"DDFMap") == 0)
        return false;
    if (_wcsicmp(directory, L"DDFList") == 0)
        return false;

    Key_s008d_7220 newKey;
    if (!GetExtensionToType(directory, pExt, pFileName, &newKey))
        return false;
    newKey = key;
    (void)newKey;

    Key_s008d_7220 mapKey;
    mapKey = key;

    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    RBNode* pFound = RBTreeFindNode(&mRecordDataMap, mapKey);
    RBNode* pEnd   = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);

    (void)nHighTime;
    (void)nLowTime;

    bool bChanged = false;
    if (pFound == pEnd)
    {
        reinterpret_cast<RecordMapOps*>(this)->DoCreateNode(&mapKey, 0, 0, 0, 0);
        if (mpManager != 0)
        {
            typedef void (*NotifyFn)(void*, const Key_s008d_7220*);
            NotifyFn pNotify = *reinterpret_cast<NotifyFn*>(*reinterpret_cast<uint8_t**>(mpManager) + 0x80);
            if (pNotify)
                pNotify(mpManager, &mapKey);
        }
    }
    else
    {
        if (nHighTime != 0 || nLowTime != 0)
        {
            DDFRecordListData* pValue = NodeValue(pFound);
            if (pValue->mnTimeHigh == static_cast<uint32_t>(nHighTime) &&
                pValue->mnTimeLow  == static_cast<uint32_t>(nLowTime))
            {
                mMutex.Unlock();
                return false;
            }
            pValue->mnTimeHigh = static_cast<uint32_t>(nHighTime);
            pValue->mnTimeLow  = static_cast<uint32_t>(nLowTime);
        }
    }

    bChanged = true;
    if (pOutProc != 0)
        *pOutProc = 1;

    mMutex.Unlock();
    return bChanged;
}
}}  // namespace EA::ResourceMan

// @ 0x008d7960
namespace EA { namespace ResourceMan {
int DatabaseDirectoryFiles::UpdateAllRecordData(int nFlags)
{
    int nUpdated = 0;

    if (!mbInitialized)
        return 0;
    if (!EA::IO::ExistsDirectory(msDirectory.mpBegin))
        return 0;

    extern void ReadExtensionToTypeMapFile(DatabaseDirectoryFiles* pThis);   // 0x008d6ed0
    ReadExtensionToTypeMapFile(this);

    // DirectoryIterator over msDirectory; for each entry call AddFileRecord.
    struct DirEntry { uint8_t mBytes[0x30]; };
    struct DirIter  { uint8_t mBytes[0x30]; };

    void* pAllocator = EA::Allocator::ICoreAllocator_s008d_7220::GetDefaultAllocator();
    (void)pAllocator;

    extern void DirectoryIterator_Ctor(void* pIter, void* pAlloc);        // 0x005f9680
    extern void DirectoryIterator_Dtor(void* pIter);                      // 0x005f96c0
    extern bool DirectoryIterator_Read(void* pIter, const wchar_t* pDir, DirEntry* pEntry, int a, int b, int c, int d); // 0x0092ef40
    extern bool DirectoryIterator_ReadRecursive(void* pIter, const wchar_t* pDir, DirEntry* pEntry, int a, int b, int c, int d, int e); // 0x0092f220

    DirIter iter;
    DirectoryIterator_Ctor(&iter, &pAllocator);

    DirEntry entry;
    if (!mbRecursive)
        DirectoryIterator_Read(&iter, msDirectory.mpBegin, &entry, 0, 2, 0x100000, 1);
    else
        DirectoryIterator_ReadRecursive(&iter, msDirectory.mpBegin, &entry, 0, 2, 1, 0, 0x100000);

    (void)nUpdated;
    DirectoryIterator_Dtor(&iter);
    return nUpdated;
}
}}  // namespace EA::ResourceMan

// @ 0x008d7a70
namespace EA { namespace ResourceMan {
int DatabaseDirectoryFiles::UpdateRecordData(const Key_s008d_7220& key, int nFileTime, int nFlags)
{
    wchar_t path[0x840 / 2];
    wchar_t directory[260];

    extern void FilePath_Init(void* pPath, const wchar_t* pName);
    extern const wchar_t* FilePath_GetExtension(void* pPath);
    extern void FilePath_GetDirectory(void* pPath, wchar_t* pDst, int n);
    extern bool GetExtensionToType(const wchar_t* pDir, const wchar_t* pExt, const wchar_t* pName, Key_s008d_7220* pKey);

    FilePath_Init(path, reinterpret_cast<const wchar_t*>(&key)); // placeholder name source
    (void)nFileTime;

    Key_s008d_7220 localKey = key;
    if (_wcsicmp(directory, L"DDFMap") == 0)
        return 0;
    if (_wcsicmp(directory, L"DDFList") == 0)
        return 0;

    int nResult = 0;
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));
    RBNode* pNode = RBTreeFindNode(&mRecordDataMap, localKey);
    mMutex.Unlock();
    (void)pNode;
    (void)nFlags;
    return nResult;
}
}}  // namespace EA::ResourceMan

// @ 0x008d7cb0
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles::OpenRecord(const Key_s008d_7220& key, int nArg2, uint32_t nArg3, int nArg4, void** ppFileRef, int nArg6)
{
    if (!mbInitialized)
        return false;

    // The image only tests the known-type bitset when the second argument is zero, and it indexes
    // the bitset by the key's second dword (offset 4), not by the type id.
    if (nArg2 == 0)
    {
        uint32_t v = key.mnGroupID;                 // key + 4
        uint32_t nBit = 1u << (v & 0x1f);
        uint32_t nIdx = (v >> 5) & 0x1f;
        if ((mKnownTypesBits[nIdx] & nBit) == 0)
            return false;
    }

    mMutex.Lock(reinterpret_cast<void*>(0x1436624));
    RBNode* pNode = RBTreeFindNode(&mRecordDataMap, key);
    RBNode* pEnd  = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);
    bool bFound = (pNode != pEnd);

    if (nArg2 == 0 && ppFileRef == 0)
    {
        mMutex.Unlock();
        return bFound;
    }

    wchar_t name[0x100];
    name[0] = 0;
    if (bFound)
    {
        DDFRecordListData* pValue = NodeValue(pNode);
        const wchar_t* pName = pValue->mpNameBegin;
        wchar_t* pDst = name;
        if (pName)
        {
            while ((*pDst++ = *pName++) != 0)
                ;
        }
    }
    mMutex.Unlock();

    if (bFound && ppFileRef != 0)
    {
        wchar_t full[0x200];
        EA::IO::ConcatenatePathComponents(full, msDirectory.mpBegin, name);
        ppFileRef[3] = 0;
        ppFileRef[0] = 0;
        unsigned nSize = EA::IO::GetSize(full);
        ppFileRef[1] = reinterpret_cast<void*>(static_cast<uintptr_t>(nSize));
        ppFileRef[2] = reinterpret_cast<void*>(static_cast<uintptr_t>(nSize));
    }

    (void)nArg3;
    (void)nArg4;
    (void)nArg6;
    return bFound;
}
}}  // namespace EA::ResourceMan
