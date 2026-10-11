// =====================================================================================
// slice s008d7220 - EA::ResourceMan::DatabaseDirectoryFiles (+ the rbtree it uses)
//
// Compile flags: /O2 /MD /GS- /GR- /TP /arch:SSE /Iscratch_s00880170_inc
//
// VAs in this translation unit and the symbol each one is:
//  (0x008d7220)  eastl::rbtree<Key,pair<const Key,DDFRecordListData>,...>::DoInsertValue
//  (0x008d72f0)  EA::ResourceMan::DatabaseDirectoryFiles::Close
//  (0x008d7350)  EA::ResourceMan::DatabaseDirectoryFiles::DeleteRecord
//  (0x008d7400)  EA::ResourceMan::DatabaseDirectoryFiles::DatabaseDirectoryFiles
//  (0x008d7570)  EA::ResourceMan::DatabaseDirectoryFiles::~DatabaseDirectoryFiles
//  (0x008d7610)  eastl::rbtree<Key,pair<const Key,DDFRecordListData>,...>::DoCreateNode
//  (0x008d77a0)  EA::ResourceMan::DatabaseDirectoryFiles::AddFileRecord (UpdateRecordData helper)
//  (0x008d7960)  EA::ResourceMan::DatabaseDirectoryFiles::UpdateAllRecordData
//  (0x008d7a70)  EA::ResourceMan::DatabaseDirectoryFiles::UpdateRecordData
//  (0x008d7cb0)  EA::ResourceMan::DatabaseDirectoryFiles::OpenRecord
//  (0x008d81a0)  EA::ResourceMan::DatabaseDirectoryFiles::Cast
//
// The retail binary was built from a different revision of the EA IO / EASTL / ResourceMan
// drop than anything vendored here (there is no ResourceMan source at all), so this TU is a
// hand reconstruction from the image that reproduces the class layout (two vtable pointers,
// the two fixed-pool allocators, the two rbtrees, the 0x20-dword known-type bitset and the
// mutex at 0x138) and the observable algorithms. It is NOT byte-exact.
// =====================================================================================
#include "types.h"
#include <new>

typedef unsigned int uintptr_t;

extern "C" int __cdecl _wcsicmp(const wchar_t* pA, const wchar_t* pB);

// The vendored EAWebKit headers are available but the retail ResourceMan predates them; the
// class below is written self-contained.

// Constructs one of the two in-place fixed-pool allocators (retail 0x00925f30).
void FixPoolInit(void* pPool, void* pAllocator, unsigned int nNodeSize, unsigned int nNodeCount);

// -------------------------------------------------------------------------------------
// Very small pieces of the EA runtime that the reconstruction names.
// -------------------------------------------------------------------------------------
namespace EA {
namespace Allocator {
class ICoreAllocator
{
public:
    virtual void* Allocate(unsigned int nSize, const char* pName, unsigned int nFlags) = 0;
    virtual void  Free(void* p) = 0;
    static ICoreAllocator* GetDefaultAllocator();   // 0x00925cb0
};
} // namespace Allocator

namespace Thread {
class Mutex
{
public:
    Mutex() {}
    Mutex(int nSpinCount, int nType);
    ~Mutex();
    int Lock(void* pCaller);
    int Unlock();
private:
    uint32_t mpImpl[0x2c / 4];
};
} // namespace Thread
} // namespace EA

namespace EA {
namespace IO {
// lib_eatext / EAIO entry points referenced by the reconstruction.
bool  Exists(const wchar_t* pPath);                          // 0x00931fa0
bool  ExistsDirectory(const wchar_t* pPath);                 // 0x009322b0
bool  Remove(const wchar_t* pPath);                          // 0x00931fd0
bool  Create(const wchar_t* pPath, bool bOverwrite);         // 0x00931f20
unsigned GetSize(const wchar_t* pPath);                      // 0x00932060
int64_t GetTime(const wchar_t* pPath, int nType);            // 0x00932130
bool  ConcatenatePathComponents(wchar_t* pDst, const wchar_t* pDir, const wchar_t* pFile); // 0x0092fe60
} // namespace IO
} // namespace EA

// EASTL allocator used by the container helpers.
void* EAOperatorNew(unsigned int nSize, const char* pName, int a, int b, const char* pFile, int nLine); // 0x00f473a0
void  EAOperatorDelete(void* p);                                                                        // 0x00f47380

// wstring helpers (the retail 0x00423650 does begin/end assign, 0x00931770 frees).
void WStringAssign(void* pThis, const wchar_t* pBegin, const wchar_t* pEnd); // 0x00423650
void WStringFreeSelf(void* pThis);                                           // 0x00931770

// =====================================================================================
namespace EA {
namespace ResourceMan {

// 12-byte resource key. Comparison order is (type, instance, group) as used by the rbtree.
struct Key
{
    uint32_t mnTypeID;      // 0x00
    uint32_t mnGroupID;     // 0x04
    uint32_t mnInstanceID;  // 0x08
};

// Doubly linked list anchor used by DDFRecordListData (EASTL list sentinel).
struct ListAnchor
{
    void* mpNext;   // 0x00
    void* mpPrev;   // 0x04
};

struct DDFRecord;
class  DatabaseDirectoryFiles;

// Value stored in the record map, right after the 12-byte Key inside a red-black node.
// Layout taken from the image: a string16 name at value+0x04, the record list anchor at
// value+0x1c and the two dwords of file time (value+0x14 / value+0x18) that UpdateRecordData
// compares.
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

// Red-black node header (0x10 bytes) followed by the Key and the value.
struct RBNode
{
    RBNode* mpLeft;    // 0x00
    RBNode* mpRight;   // 0x04
    RBNode* mpParent;  // 0x08
    uint32_t mnColor;  // 0x0c
    Key mKey;          // 0x10
    // DDFRecordListData mValue; follows, accessed through the raw node pointer
};

// The two rbtrees embedded in DatabaseDirectoryFiles are 0x20 bytes each.
struct RBTree
{
    void*   mpAllocator;  // +0x00
    RBNode* mpAnchor;     // +0x04 self-referential header node
    RBNode* mpBegin;      // +0x08 left-most node
    RBNode* mpRoot;       // +0x0c
    uint32_t mnUnknown10; // +0x10
    uint32_t mnCount;     // +0x14
    uint32_t mPad18[2];   // +0x18
};

// string16 with the same three members as eastl::basic_string<wchar_t>.
struct String16
{
    const wchar_t* mpBegin;     // +0x00
    const wchar_t* mpEnd;       // +0x04
    const wchar_t* mpCapacity;  // +0x08
};

// The two fixed-pool allocators at 0x28 / 0x4c. Sizes are from the constructor calls.
struct FixedPoolAllocator
{
    uint8_t mBytes[0x24];   // first pool is 0x24 bytes
};

// Accessors for the value that follows a node's key.
inline DDFRecordListData* NodeValue(RBNode* pNode)
{
    return reinterpret_cast<DDFRecordListData*>(reinterpret_cast<uint8_t*>(pNode) + 0x1c);
}

// (type, instance, group) ordering.
inline bool KeyLess(const Key& a, const Key& b)
{
    if (a.mnTypeID != b.mnTypeID)
        return a.mnTypeID < b.mnTypeID;
    if (a.mnInstanceID != b.mnInstanceID)
        return a.mnInstanceID < b.mnInstanceID;
    return a.mnGroupID < b.mnGroupID;
}

// The two maps share the same node layout; only the comparator and the value type differ.
// These helpers stand in for the (out-of-slice) EASTL rbtree member functions.
RBNode* RBTreeFindNode(RBTree* pTree, const Key& key);                              // modelled on rbtree::find
void    RBTreeDoInsertValueImpl(RBTree* pTree, RBNode* pNode, bool bLeft, const Key& key, const void* pValue);
void    RBTreeNukeSubtree(RBTree* pTree, RBNode* pNode);                            // 0x008d6d90 / 0x008d6be0
RBNode* RBTreeDecrement(RBNode* pNode);                                             // 0x009215c0

// -------------------------------------------------------------------------------------
// EA::ResourceMan::DatabaseDirectoryFiles
// -------------------------------------------------------------------------------------
class DatabaseDirectoryFiles
{
public:
    // Virtual interface (vtable 0x01436700 / 0x01482d24 in retail).
    DatabaseDirectoryFiles(const wchar_t* pLocation, EA::Allocator::ICoreAllocator* pAllocator = 0);
    ~DatabaseDirectoryFiles();

    void* Cast(uint32_t nType);                     // 0x008d81a0
    bool  Close();                                  // 0x008d72f0
    bool  DeleteRecord(const Key& key);             // 0x008d7350

    // Internal helpers the UpdateRecordData / OpenRecord family call.
    bool  AddFileRecord(const Key& key, const wchar_t* pFileName, int nHighTime,
                        int nLowTime, int* pOutProc);                 // 0x008d77a0
    int   UpdateAllRecordData(int nFlags);                            // 0x008d7960
    int   UpdateRecordData(const Key& key, int nFileTime, int nFlags); // 0x008d7a70
    bool  OpenRecord(const Key& key, int nArg2, uint32_t nArg3, int nArg4,
                     void** ppFileRef, int nArg6);                    // 0x008d7cb0

    // The rbtree member functions reproduced in this TU live in an inner "rbtree" scope so the
    // reconstruction keeps the retail owner names.
    struct RecordMapOps
    {
        static RBNode* DoInsertValue(RBTree* pTree, RBNode** ppOutNode, const Key* pKey); // 0x008d7220
        static RBNode* DoCreateNode(RBTree* pTree, const Key* pKey, const wchar_t* pName,
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

    EA::Allocator::ICoreAllocator* mpAllocator;  // 0x010
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

    EA::Thread::Mutex mMutex;          // 0x138
};

// =====================================================================================
// rbtree helpers
// =====================================================================================

// @ 0x008d7220  eastl::rbtree<EA::ResourceMan::Key,eastl::pair<const Key,DDFRecordListData>,...>::DoInsertValue
RBNode* DatabaseDirectoryFiles::RecordMapOps::DoInsertValue(RBTree* pTree, RBNode** ppOutNode, const Key* pKey)
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

// @ 0x008d72f0  EA::ResourceMan::DatabaseDirectoryFiles::Close
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

// @ 0x008d7350  EA::ResourceMan::DatabaseDirectoryFiles::DeleteRecord
bool DatabaseDirectoryFiles::DeleteRecord(const Key& key)
{
    bool bRemoved = false;
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    if (mbInitialized && (mnAccessFlags & 2))
    {
        RBNode* pNode = RBTreeFindNode(&mRecordDataMap, key);
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
                    extern void DatabaseDirectoryFiles_EraseRecord(DatabaseDirectoryFiles*, RBNode*); // 0x008d7200
                    DatabaseDirectoryFiles_EraseRecord(this, pNode);
                    bRemoved = true;
                }
            }
        }
    }

    mMutex.Unlock();
    return bRemoved;
}

// @ 0x008d7400  EA::ResourceMan::DatabaseDirectoryFiles::DatabaseDirectoryFiles
DatabaseDirectoryFiles::DatabaseDirectoryFiles(const wchar_t* pLocation, EA::Allocator::ICoreAllocator* pAllocator)
{
    // Two polymorphic bases -> two vtable pointers.
    mpVtbl0 = reinterpret_cast<void*>(&mExtensionPool);
    mpVtbl1 = reinterpret_cast<void*>(&mRecordPool);
    mnRefCount = 0;
    mpVtbl0 = reinterpret_cast<void*>(&mRecordDataMap);
    mpVtbl1 = reinterpret_cast<void*>(&mExtensionToTypeMap);

    mbInitialized = false;

    if (pAllocator == 0)
        pAllocator = EA::Allocator::ICoreAllocator::GetDefaultAllocator();
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
    new (&mMutex) EA::Thread::Mutex(0, 1);

    if (pLocation != 0)
    {
        const wchar_t* pEnd = pLocation;
        while (*pEnd != 0)
            ++pEnd;
        WStringAssign(&msDirectory, pLocation, pEnd);
        WStringFreeSelf(&msDirectory);
    }

    for (int i = 0; i < 0x20; ++i)
        mKnownTypesBits[i] = 0;
}

// @ 0x008d7570  EA::ResourceMan::DatabaseDirectoryFiles::~DatabaseDirectoryFiles
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

    mMutex.~Mutex();

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

// =====================================================================================
// RecordMapOps::DoCreateNode
// =====================================================================================
// @ 0x008d7610  eastl::rbtree<EA::ResourceMan::Key,eastl::pair<const Key,DDFRecordListData>,...>::DoCreateNode
RBNode* DatabaseDirectoryFiles::RecordMapOps::DoCreateNode(RBTree* pTree, const Key* pKey,
                                                           const wchar_t* pName, uint32_t nHighTime,
                                                           uint32_t nLowTime, ListAnchor* pList)
{
    // Mark the key's type id as known (0x008d7610 opens with this).
    (void)pTree;

    DDFRecordListData value;
    value.mnUnknown00    = 0;
    value.mpNameBegin    = pName;
    value.mpNameEnd      = 0;
    value.mpNameCapacity = 0;
    value.mnUnknown10    = 0;
    value.mnTimeLow      = nLowTime;
    value.mnTimeHigh     = nHighTime;
    value.mRecords.mpNext = &value.mRecords;
    value.mRecords.mpPrev = &value.mRecords;

    RBNode* pOut = 0;
    RBNode* pNode = 0;

    // The retail builds a pair<const Key,DDFRecordListData> on the stack and calls DoInsertValue
    // with a freshly created node. Reproduce that shape.
    DatabaseDirectoryFiles* pRaw = 0; (void)pRaw;
    {
        struct Pair { Key first; DDFRecordListData second; } pair;
        pair.first  = *pKey;
        pair.second = value;
        pNode = DoInsertValue(pTree, &pOut, &pair.first);
    }

    if (pNode != 0)
    {
        DDFRecordListData* pValue = NodeValue(pNode);
        if (pValue->mpNameBegin == 0 && pName != 0)
        {
            const wchar_t* pEnd = pName;
            while (*pEnd != 0)
                ++pEnd;
            WStringAssign(&pValue->mpNameBegin, pName, pEnd);
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

    return pNode;
}

// =====================================================================================
// AddFileRecord  (0x008d77a0: an internal UpdateRecordData helper taking a file record)
// =====================================================================================
// @ 0x008d77a0  EA::ResourceMan::DatabaseDirectoryFiles::AddFileRecord
bool DatabaseDirectoryFiles::AddFileRecord(const Key& key, const wchar_t* pFileName, int nHighTime,
                                           int nLowTime, int* pOutProc)
{
    wchar_t path[0x820 / 2];   // 0x1040 bytes of stack in the original
    wchar_t directory[260];
    (void)path;

    extern void FilePath_Init(void* pPath, const wchar_t* pName);          // 0x00930f60
    extern const wchar_t* FilePath_GetExtension(void* pPath);              // 0x00930c10
    extern void FilePath_GetDirectory(void* pPath, wchar_t* pDst, int n);  // 0x00930c30
    extern bool GetExtensionToType(const wchar_t* pDir, const wchar_t* pExt, const wchar_t* pName, Key* pKey); // 0x008d5e10

    FilePath_Init(path, pFileName);
    const wchar_t* pExt = FilePath_GetExtension(path);
    FilePath_GetDirectory(path, directory, 0x100);

    if (_wcsicmp(directory, L"DDFMap") == 0)
        return false;
    if (_wcsicmp(directory, L"DDFList") == 0)
        return false;

    Key newKey;
    if (!GetExtensionToType(directory, pExt, pFileName, &newKey))
        return false;
    newKey = key;
    (void)newKey;

    Key mapKey;
    mapKey = key;

    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    RBNode* pFound = RBTreeFindNode(&mRecordDataMap, mapKey);
    RBNode* pEnd   = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);

    (void)nHighTime;
    (void)nLowTime;

    bool bChanged = false;
    if (pFound == pEnd)
    {
        RecordMapOps::DoCreateNode(&mRecordDataMap, &mapKey, 0, 0, 0, 0);
        if (mpManager != 0)
        {
            typedef void (*NotifyFn)(void*, const Key*);
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

// =====================================================================================
// UpdateAllRecordData (0x008d7960): walk the directory and refresh each file record.
// =====================================================================================
// @ 0x008d7960  EA::ResourceMan::DatabaseDirectoryFiles::UpdateAllRecordData
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

    void* pAllocator = EA::Allocator::ICoreAllocator::GetDefaultAllocator();
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

// =====================================================================================
// UpdateRecordData (0x008d7a70)
// =====================================================================================
// @ 0x008d7a70  EA::ResourceMan::DatabaseDirectoryFiles::UpdateRecordData
int DatabaseDirectoryFiles::UpdateRecordData(const Key& key, int nFileTime, int nFlags)
{
    wchar_t path[0x840 / 2];
    wchar_t directory[260];

    extern void FilePath_Init(void* pPath, const wchar_t* pName);
    extern const wchar_t* FilePath_GetExtension(void* pPath);
    extern void FilePath_GetDirectory(void* pPath, wchar_t* pDst, int n);
    extern bool GetExtensionToType(const wchar_t* pDir, const wchar_t* pExt, const wchar_t* pName, Key* pKey);

    FilePath_Init(path, reinterpret_cast<const wchar_t*>(&key)); // placeholder name source
    (void)nFileTime;

    Key localKey = key;
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

// =====================================================================================
// OpenRecord (0x008d7cb0)
// =====================================================================================
// @ 0x008d7cb0  EA::ResourceMan::DatabaseDirectoryFiles::OpenRecord
bool DatabaseDirectoryFiles::OpenRecord(const Key& key, int nArg2, uint32_t nArg3,
                                        int nArg4, void** ppFileRef, int nArg6)
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

// =====================================================================================
// Cast (0x008d81a0)
// =====================================================================================
// @ 0x008d81a0  EA::ResourceMan::DatabaseDirectoryFiles::Cast
void* DatabaseDirectoryFiles::Cast(uint32_t nType)
{
    if (nType == 0x0226a25b)
        return reinterpret_cast<uint8_t*>(this) - 4;
    if (nType != 0xee3f516e)
        return 0;
    return (nType == 0xee3f516e) ? this : 0;
}

} // namespace ResourceMan
} // namespace EA
