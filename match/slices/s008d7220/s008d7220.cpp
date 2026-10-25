// =====================================================================================
// slice s008d7220 - EA::ResourceMan::DatabaseDirectoryFiles (+ the EASTL containers it embeds)
//
// Flags: /O2 /MD /GS- /GR- /TP /arch:SSE /Iscratch_s00880170_inc (vendored EASTL/EAWebKit headers)
//
// This is a hand reconstruction from the image (there is no ResourceMan source in any
// vendored drop).  The class layout, the rbtree/list/hashtable node layouts and the
// observable algorithms are taken from the retail disassembly; the EASTL members are
// declared with their real types where the embedded instance could be recovered.
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
// =====================================================================================
#include "types.h"

// Vendored EAWebKit build configuration (kept in-source so the manifest flags stay short).
#define WIN32 1
#define NDEBUG 1
#define _SECURE_SCL 0
#define UTF_USE_EAASSERT 1
#define EATEXT_USE_FREETYPE 1
#define EATEXT_BITMAP_USE_EAGIMEX 0
#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define _WIN32_IE 0x0501

#pragma warning(disable: 4100)   // unreferenced formal parameter (decompiled stubs)
#pragma warning(disable: 4189)   // local variable is initialized but not referenced

#include <coreallocator/icoreallocator_interface.h>
#include <EAIO/PathString.h>
#include <EAIO/EAFileDirectory.h>
#include <EAIO/EAFileUtil.h>
#include <EASTL/string.h>
#include <EASTL/vector.h>
#include <EASTL/list.h>
#include <EASTL/map.h>
#include <new>

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t* pA, const wchar_t* pB);

// =====================================================================================
// The retail record-map value type.  The 2008 dev PDB says
//   struct DDFRecordListData { basic_string<wchar_t> msFileName; long mnLastModificationTime;
//                              list<AutoRefCount<DDFRecord>> mRecordList; }
// but the retail binary reads the key at +0x10 (not +0x0), the two file-time idwords at
// +0x14/+0x18 and the list anchor at +0x1c, with the record name already inside the string
// at +0x04.  The layout below is the retail one (the PDB's class is shifted by one Key).
// =====================================================================================
namespace EA { namespace ResourceMan {

// 12-byte resource key.  Comparison order (instance, type, group) as used by the rbtree.
class Key
{
public:
    uint32_t mInstanceID;  // +0x00
    uint32_t mnTypeID;     // +0x04
    uint32_t mnGroupID;    // +0x08
};

// Doubly linked list anchor (EASTL list node / sentinel).
struct ListAnchor
{
    void* mpNext;   // +0x00
    void* mpPrev;   // +0x04
};

// The retail image's static empty wchar_t string (eastl::string16::mpEmptyString16).
extern const wchar_t gEmptyString16[];   // 0x01667bac

// The record value as the image lays it out.  The 0x10-byte string16 stores the record
// name; the copy constructor is out of this TU (0x008d6970) so only the call shape matters.
struct DDFRecordListData
{
    uint32_t       mnStringAlloc;    // +0x00 (string16 allocator, unused by retail)
    const wchar_t* mpNameBegin;      // +0x04 string16.mpBegin
    const wchar_t* mpNameEnd;        // +0x08 string16.mpEnd
    const wchar_t* mpNameCapacity;   // +0x0c string16.mpCapacity
    uint32_t       mnUnknown10;      // +0x10 (padding that the map value starts on)
    uint32_t       mnTimeLow;        // +0x14
    uint32_t       mnTimeHigh;       // +0x18
    ListAnchor     mRecords;         // +0x1c list<AutoRefCount<DDFRecord>>

    void CopyFrom(const DDFRecordListData* pSrc);   // 0x008d6970
};

// Red-black node header (0x10 bytes) followed by the Key and the value.
struct RBNode
{
    RBNode* mpLeft;    // +0x00
    RBNode* mpRight;   // +0x04
    RBNode* mpParent;  // +0x08
    uint32_t mnColor;  // +0x0c (the anchor node's +0x0c is the tree's node count area)
    Key mKey;          // +0x10
    // DDFRecordListData mValue; follows at +0x1c
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

    // The retail rbtree members receive the tree in ECX; their bodies live outside this TU
    // (0x00a21dc0 find, 0x008d7200 erase, 0x008d7220 insert), so only the call shape is
    // reproduced here.
    void*   Find(RBNode** ppOutNode, const Key* pKey);                                  // 0x00a21dc0
    void*   EraseRecord(RBNode** ppOutNode, RBNode* pNode);                             // 0x008d7200
    RBNode* InsertValue(RBNode** ppOutNode, const void* pValue, const void* pKeyValue); // 0x008d7220
    void    DoNukeSubtree(RBNode* pNode);                                               // 0x008d6d90
};

// The extension map's DoNukeSubtree is a distinct template instantiation.
struct RBTreeExt
{
    uint32_t mPad[0x20 / 4];
    void DoNukeSubtree(RBNode* pNode);                                                  // 0x008d6be0
};

// The two fixed-pool allocators at 0x2c / 0x4c.
struct FixedPoolAllocator
{
    uint32_t mPad[0x20 / 4];
};

// Accessors for the value that follows a node's key.
inline DDFRecordListData* NodeValue(RBNode* pNode)
{
    return reinterpret_cast<DDFRecordListData*>(reinterpret_cast<uint8_t*>(pNode) + 0x1c);
}

// (instance, type, group) ordering, as the retail DoInsertValue emits it.
inline bool KeyLess(const Key& a, const Key& b)
{
    if (a.mInstanceID != b.mInstanceID)
        return a.mInstanceID < b.mInstanceID;
    if (a.mnTypeID != b.mnTypeID)
        return a.mnTypeID < b.mnTypeID;
    return a.mnGroupID < b.mnGroupID;
}

// Helpers for the (out-of-slice) EASTL rbtree member functions.
RBNode* RBTreeFindNode(RBTree* pTree, const Key& key);                              // 0x00a21dc0
void    RBTreeInsertValueImpl(RBTree* pTree, RBNode* pNode, bool bLeft, const Key& key, const void* pValue);
RBNode* RBTreeDecrement(RBNode* pNode);                                             // 0x009215c0
} // namespace ResourceMan
} // namespace EA

namespace EA {
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

namespace EA { namespace ResourceMan {

// The retail manager interface, used through its vtable (the notify call the record paths
// make is vtable slot +0x80).
class Manager
{
public:
    void NotifyRecordCreated(const Key* pKey);   // IResourceManager vtable slot +0x80 (no direct image address)
};

class DatabaseDirectoryFiles;

// The open CC overlay record (a DDFRecord).  Everything before mKey is the
// Record + FileStream base and is only passed through.
class DDFRecord
{
public:
    uint32_t       mPad000[0x8c / 4];  // +0x000 Record base + FileStream base + vtable
    const wchar_t* mpPathBegin;        // +0x08c
    uint32_t       mPad090[0x11c / 4]; // +0x090
    Key            mKey;               // +0x1ac
    DatabaseDirectoryFiles* mpDDF;     // +0x1b8
    uint32_t       mnOpenCount;        // +0x1bc
    uint32_t       mPad1c0[6];         // +0x1c0 (tail of the FileStream state)

    DDFRecord* Initialize(DatabaseDirectoryFiles* pDDF, const Key* pKey);  // 0x008d60d0
};

// The class the open path constructs and the file stream forwards to.
class BackgroundRecordLoad
{
public:
    uint32_t mPad00[0x244 / 4];
    uint32_t mLoadFlags;   // +0x244
};

// ---------------------------------------------------------------------------------------
// EA::ResourceMan::DatabaseDirectoryFiles
// ---------------------------------------------------------------------------------------
class DatabaseDirectoryFiles
{
public:
    DatabaseDirectoryFiles(const wchar_t* pLocation, EA::Allocator::ICoreAllocator* pAllocator = 0);
    ~DatabaseDirectoryFiles();

    void* Cast(uint32_t nType);                                          // 0x008d81a0
    bool  Close();                                                       // 0x008d72f0
    bool  DeleteRecord(const Key& key);                                  // 0x008d7350
    bool  AddFileRecord(const Key& key, const wchar_t* pFileName,
                        uint32_t nFileTimeLow, uint32_t nFileTimeHigh,
                        void* pList1, void* pList2);                     // 0x008d77a0
    int   UpdateAllRecordData(int nFlags);                               // 0x008d7960
    int   UpdateRecordData(const Key& key, void* pList, int nFlags);     // 0x008d7a70
    bool  OpenRecord(const Key& key, int nArg2, int nOpenMode,
                     uint32_t nAccess, void** ppFileRef, int nFlags);    // 0x008d7cb0

    // The rbtree member functions reproduced in this TU keep the retail owner name.
    struct RecordMapOps
    {
        static RBNode* DoInsertValue(RBTree* pTree, RBNode** ppOutNode, const Key* pKey); // 0x008d7220
        void DoCreateNode(const Key* pKey, const wchar_t* pName,
                          uint32_t nTimeLow, uint32_t nTimeHigh, void* pList);            // 0x008d7610
    };

private:
    void SetLocation(const wchar_t* pLocation);

public:
    // ---- exact retail layout (0x168 bytes, two vtable pointers, two embedded hashtables)
    void*  mpVtbl0;                    // 0x000 (Database / ZoneObject)
    void*  mpVtbl1;                    // 0x004 (IUnknown32 / IRefCount)
    int    mnRefCount;                 // 0x008
    bool   mbInitialized;              // 0x00c
    uint8_t mPad0d[3];                 // 0x00d

    EA::Allocator::ICoreAllocator* mpAllocator;  // 0x010
    bool   mbRequireDirectoryExists;   // 0x014
    bool   mbRecursive;                // 0x015
    uint8_t mPad16[2];                 // 0x016

    uint32_t mnAccessFlags;            // 0x018
    const wchar_t* msDirectoryBegin;   // 0x01c string16 begin (only begin is used)
    uint32_t mPad20[2];                // 0x020
    uint32_t mDirectoryAllocator;      // 0x028 (left unset by the ctor)

    uint8_t  mExtensionPool[0x20];     // 0x02c fixed-pool node allocator for mExtensionToTypeMap
    uint8_t  mRecordPool[0x20];        // 0x04c fixed-pool node allocator for mRecordDataMap

    RBTree mExtensionToTypeMap;        // 0x06c
    RBTree mRecordDataMap;             // 0x08c

    uint32_t mDefaultGroupId;          // 0x0ac
    Manager* mpManager;                // 0x0b0
    void*    mpFileNameToKeyConverter; // 0x0b4

    uint32_t mKnownTypesBits[0x20];    // 0x0b8 (0x80 bytes, 1024 known type ids)

    EA::Thread::Mutex mMutex;          // 0x138
};

// ---------------------------------------------------------------------------------------
// Free helpers that live in other TUs (the harness binds each call to its retail address)
// ---------------------------------------------------------------------------------------
// 0x00925f30 constructs one of the two in-place fixed-pool allocators.
void FixPoolInit(void* pPool, void* pAllocator, unsigned int nNodeSize, unsigned int nNodeCount); // 0x00925f30
// 0x00925cb0 returns the process-wide default core allocator.
EA::Allocator::ICoreAllocator* GetDefaultAllocator();                        // 0x00925cb0
// 0x00925e60 frees a fixed-pool allocator's node list (HashHolder destructor shape).
void FixedPoolClear(void* pPool);                                            // 0x00925e60
// 0x008d6770 drops every open record.
void DatabaseDirectoryFiles_CloseOpenRecords(DatabaseDirectoryFiles* pThis); // 0x008d6770
// 0x008d6ed0 loads the extension -> type-id map file.
bool ReadExtensionToTypeMapFile(DatabaseDirectoryFiles* pThis);              // 0x008d6ed0
// 0x008d5e10 resolves an extension to a type id / creates a record.
bool OpenRecord_GetExtensionToType(DatabaseDirectoryFiles* pThis, const wchar_t* pDirectory,
                                   const wchar_t* pExtension, const wchar_t* pFileName, Key* pKey); // 0x008d5e10
// 0x008d61a0 returns the pending open count of a DDFRecord list owner.
uint32_t RecordListGetRefCount(const wchar_t* pRecordName);                  // 0x008d61a0
// 0x008d60d0 initialises a freshly allocated DDFRecord.
DDFRecord* DDFRecord_Initialize(DatabaseDirectoryFiles* pThis, const Key* pKey); // 0x008d60d0
// 0x00925fe0 allocates a named zone object.
void* ZoneAlloc_Named(int nSize, EA::Allocator::ICoreAllocator* pAllocator, int a); // 0x00925fe0
// 0x00930f60 / 0x00930c10 / 0x00930c30: the EA::IO::FilePath accessor family.
// 0x0092fe60 concatenates a directory and a file name into a wide buffer.
int  EAIOConcatenatePathComponents(wchar_t* pDst, const wchar_t* pDir, const wchar_t* pFile); // 0x0092fe60
// string16::assign(first,last) -- 0x00423650.
void DDFRecordListAssignName(void* pString, const wchar_t* pFirst, const wchar_t* pLast); // 0x00423650
// 0x00f47380 / 0x00f473a0: the EA memory manager's delete/new.
void EAOperatorDelete(void* p);                                              // 0x00f47380
void* EAOperatorNew(uint32_t nSize, const char* pName, int a, int b, const char* pFile, int nLine); // 0x00f473a0
// 0x00697b50 / 0x0061df40 used by the open path.
void MutexLockCtor(void* pLock, void* pMutex);                               // 0x00697b50
void DDFRecordListPushBack(void* pList, void* pRecord);                      // 0x004e19a0

// The EA::IO::FilePath helper family used by the record paths.  The vendored headers do not
// ship FilePath, so the three entry points are declared with their real shapes.
class EAIOFilePath
{
public:
    explicit EAIOFilePath(void* pBuffer) {}
    const wchar_t* GetExtension();                                  // 0x00930c10
    unsigned int   GetDirectory(wchar_t* pDst, unsigned int nCap);  // 0x00930c30
    static EAIOFilePath* Init(void* pBuffer, const wchar_t* pName); // 0x00930f60
};

// =====================================================================================
// rbtree helpers
// =====================================================================================

// @ 0x008d7220  eastl::rbtree<Key,pair<const Key,DDFRecordListData>,...>::DoInsertValue
// The original receives the tree in ECX (a __thiscall rbtree member); declared static here
// because the caller in this reconstruction passes the tree explicitly.
RBNode* DatabaseDirectoryFiles::RecordMapOps::DoInsertValue(RBTree* pTree, RBNode** ppOutNode, const Key* pKey)
{
    RBNode* pNode  = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(pTree) + 4); // &anchor
    RBNode* r      = pTree->mpRoot;
    bool    bLeft  = true;

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
            RBTreeInsertValueImpl(pTree, pNode, true, *pKey, 0);
            *ppOutNode = pNode;
            return pNode;
        }
        pInsertAfter = RBTreeDecrement(pNode);
    }

    if (KeyLess(pInsertAfter->mKey, *pKey))
    {
        RBTreeInsertValueImpl(pTree, pNode, false, *pKey, 0);
        *ppOutNode = pNode;
        return pNode;
    }

    *ppOutNode = pInsertAfter;
    return pInsertAfter;
}

// @ 0x008d72f0  EA::ResourceMan::DatabaseDirectoryFiles::Close
bool DatabaseDirectoryFiles::Close()
{
    // 0x008d6770 drops every open record first.
    DatabaseDirectoryFiles_CloseOpenRecords(this);

    mRecordDataMap.DoNukeSubtree(mRecordDataMap.mpRoot);
    mRecordDataMap.mpRoot      = 0;
    mRecordDataMap.mnCount     = 0;
    mRecordDataMap.mpBegin     = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);
    mRecordDataMap.mnUnknown10 = 0;
    reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4)->mpLeft =
        reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);

    reinterpret_cast<RBTreeExt*>(&mExtensionToTypeMap)->DoNukeSubtree(mExtensionToTypeMap.mpRoot);
    mExtensionToTypeMap.mpRoot      = 0;
    mExtensionToTypeMap.mnCount     = 0;
    mExtensionToTypeMap.mpBegin     = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mExtensionToTypeMap) + 4);
    mExtensionToTypeMap.mnUnknown10 = 0;
    reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mExtensionToTypeMap) + 4)->mpLeft =
        reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mExtensionToTypeMap) + 4);
    mnAccessFlags = 0;

    return true;
}

// @ 0x008d7350  EA::ResourceMan::DatabaseDirectoryFiles::DeleteRecord
bool DatabaseDirectoryFiles::DeleteRecord(const Key& key)
{
    bool bRemoved = false;
    mMutex.Lock(reinterpret_cast<void*>(0x01436624));

    if (mbInitialized && (mnAccessFlags & 2))
    {
        RBNode* pNode = 0;
        mRecordDataMap.Find(&pNode, &key);
        RBNode* pEnd = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);
        if (pNode != pEnd)
        {
            DDFRecordListData* pValue = NodeValue(pNode);
            if (pValue->mRecords.mpNext == &pValue->mRecords)
            {
                wchar_t path[260];
                EAIOConcatenatePathComponents(path, msDirectoryBegin, pValue->mpNameBegin);
                if (EA::IO::File::Remove(path))
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

// @ 0x008d7400  EA::ResourceMan::DatabaseDirectoryFiles::DatabaseDirectoryFiles
DatabaseDirectoryFiles::DatabaseDirectoryFiles(const wchar_t* pLocation,
                                               EA::Allocator::ICoreAllocator* pAllocator)
{
    // Two polymorphic bases -> two vtable pointers (retail 0x01436700 / 0x01482d24).
    mpVtbl0 = reinterpret_cast<void*>(&mExtensionPool);
    mpVtbl1 = reinterpret_cast<void*>(&mRecordPool);
    mnRefCount = 0;
    mpVtbl0 = reinterpret_cast<void*>(&mRecordDataMap);
    mpVtbl1 = reinterpret_cast<void*>(&mExtensionToTypeMap);

    mbInitialized = false;

    if (pAllocator == 0)
        pAllocator = GetDefaultAllocator();
    mpAllocator = pAllocator;

    mbRequireDirectoryExists = false;
    mbRecursive              = false;
    mnAccessFlags            = 0;

    static const wchar_t sEmpty[2] = { 0, 0 };
    msDirectoryBegin = sEmpty;

    FixPoolInit(&mExtensionPool, mpAllocator, 0x20, 0x24);
    FixPoolInit(&mRecordPool,    mpAllocator, 0x80, 0x48);

    mDefaultGroupId          = 0;
    mpManager                = 0;
    mpFileNameToKeyConverter = 0;

    // Initialise the two rbtrees (the tree constructors are inlined in the original).
    RBNode* pAnchorExt = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mExtensionToTypeMap) + 4);
    RBNode* pAnchorRec = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);
    mExtensionToTypeMap.mpAnchor = pAnchorExt;
    pAnchorExt->mpLeft = pAnchorExt;
    mExtensionToTypeMap.mpBegin  = 0;
    mExtensionToTypeMap.mpRoot   = 0;
    mExtensionToTypeMap.mnCount  = 0;
    mRecordDataMap.mpAnchor = pAnchorRec;
    pAnchorRec->mpLeft = pAnchorRec;
    mRecordDataMap.mpBegin  = 0;
    mRecordDataMap.mpRoot   = 0;
    mRecordDataMap.mnCount  = 0;

    new (&mMutex) EA::Thread::Mutex(0, 1);

    if (pLocation != 0)
    {
        const wchar_t* pEnd = pLocation;
        while (*pEnd != 0)
            ++pEnd;
        SetLocation(pLocation);
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
        typedef void (__thiscall *ReleaseFn)(DatabaseDirectoryFiles*);
        ReleaseFn pRelease = reinterpret_cast<ReleaseFn>(
            *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(mpVtbl0) + 0x1c));
        pRelease(this);
    }

    mMutex.~Mutex();

    mRecordDataMap.DoNukeSubtree(mRecordDataMap.mpRoot);
    reinterpret_cast<RBTreeExt*>(&mExtensionToTypeMap)->DoNukeSubtree(mExtensionToTypeMap.mpRoot);

    FixedPoolClear(&mRecordPool);
    FixedPoolClear(&mExtensionPool);

    if (msDirectoryBegin != 0 &&
        (reinterpret_cast<uintptr_t>(msDirectoryBegin) - reinterpret_cast<uintptr_t>(&mExtensionPool)) > 2)
    {
        EAOperatorDelete(const_cast<wchar_t*>(msDirectoryBegin));
    }

    mpVtbl1 = reinterpret_cast<void*>(&mRecordPool);
    mpVtbl0 = reinterpret_cast<void*>(&mExtensionPool);
}

// @ 0x008d7610  eastl::rbtree<Key,pair<const Key,DDFRecordListData>,...>::DoCreateNode
// ECX holds the owning DatabaseDirectoryFiles (the rbtree is embedded at +0x8c).
void DatabaseDirectoryFiles::RecordMapOps::DoCreateNode(const Key* pKey,
                                                        const wchar_t* pName, uint32_t nTimeLow,
                                                        uint32_t nTimeHigh, void* pList)
{
    RBTree* pTree = reinterpret_cast<RBTree*>(reinterpret_cast<uint8_t*>(this) + 0x8c);

    // Mark the record's group in the 0x0b8 known-type bitmap (key word 2 = the group id).
    uint32_t nGroup = pKey->mnGroupID;
    uint32_t* pKnownTypes = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0xb8);
    pKnownTypes[(nGroup >> 5) & 0x1f] |= 1u << (nGroup & 0x1f);

    RBNode* pNode = 0;
    {
        // The value the tree copies in: default (empty) name, the two file-time words and a
        // self-referential record-list anchor at value+0x1c.
        DDFRecordListData value;
        value.mnStringAlloc    = 0;
        value.mpNameBegin      = gEmptyString16;
        value.mpNameEnd        = gEmptyString16;
        value.mpNameCapacity   = gEmptyString16 + 1;
        value.mnUnknown10      = 0;
        value.mnTimeLow        = nTimeLow;
        value.mnTimeHigh       = nTimeHigh;
        value.mRecords.mpNext  = &value.mRecords;
        value.mRecords.mpPrev  = &value.mRecords;
        pTree->InsertValue(&pNode, &value, pKey);
    }

    if (pNode != 0)
    {
        DDFRecordListData* pValue = NodeValue(pNode);
        if (pValue->mpNameBegin == pValue->mpNameEnd)
        {
            const wchar_t* pEnd = pName;
            while (*pEnd != 0)
                ++pEnd;
            // string16::assign(begin, end) -- out of this TU (0x00423650).
            DDFRecordListAssignName(pValue, pName, pEnd);
        }
    }

    if (pList != 0)
    {
        // push_back an AutoRefCount<DDFRecord> onto the node's record list: the node holds the
        // list anchor at +0x38 and the new list node is copied straight in from the caller's.
        ListAnchor* pAnchor = reinterpret_cast<ListAnchor*>(reinterpret_cast<uint8_t*>(pNode) + 0x38);
        DDFRecordListPushBack(pAnchor, pList);
    }
}

// @ 0x008d77a0  EA::ResourceMan::DatabaseDirectoryFiles::AddFileRecord
bool DatabaseDirectoryFiles::AddFileRecord(const Key& key, const wchar_t* pFileName,
                                           uint32_t nFileTimeLow, uint32_t nFileTimeHigh,
                                           void* pList1, void* pList2)
{
    wchar_t path[0x420];      // EA::IO::FilePath working storage (0x840 bytes)
    wchar_t directory[260];
    Key newKey;
    newKey.mInstanceID = 0;
    newKey.mnTypeID    = 0;
    newKey.mnGroupID   = 0;

    (void)pFileName;
    EAIOFilePath* pPath = EAIOFilePath::Init(path, pFileName);
    const wchar_t* pExt = pPath->GetExtension();
    pPath->GetDirectory(directory, 0x100);

    if (_wcsicmp(directory, L"DDFMap") == 0)
        return false;
    if (_wcsicmp(directory, L"DDFList") == 0)
        return false;

    if (!OpenRecord_GetExtensionToType(this, directory, pExt, pFileName, &newKey))
        return false;

    mMutex.Lock(reinterpret_cast<void*>(0x01436624));

    RBNode* pFound = 0;
    mRecordDataMap.Find(&pFound, &key);

    wchar_t full[260];
    EAIOConcatenatePathComponents(full, msDirectoryBegin, pFileName);

    // Non-zero file times come from the record's own file, otherwise from the file itself.
    if (nFileTimeLow == 0 && nFileTimeHigh == 0)
    {
        int64_t t = EA::IO::File::GetTime(full, EA::IO::kFileTimeTypeLastModification);
        nFileTimeLow  = static_cast<uint32_t>(t & 0xffffffffu);
        nFileTimeHigh = static_cast<uint32_t>(t >> 32);
    }

    bool bChanged = false;
    RBNode* pEnd = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);
    if (pFound == pEnd)
    {
        reinterpret_cast<RecordMapOps*>(this)->DoCreateNode(&key, pFileName, nFileTimeLow, nFileTimeHigh, 0);
        if (mpManager != 0)
            mpManager->NotifyRecordCreated(&key);
        bChanged = true;
        if (pList1 != 0)
            DDFRecordListPushBack(pList1, const_cast<Key*>(&key));
    }
    else
    {
        DDFRecordListData* pValue = NodeValue(pFound);
        if (pValue->mnTimeLow == nFileTimeLow && pValue->mnTimeHigh == nFileTimeHigh)
        {
            mMutex.Unlock();
            return false;
        }
        pValue->mnTimeLow  = nFileTimeLow;
        pValue->mnTimeHigh = nFileTimeHigh;
        bChanged = true;
        if (pList1 != 0)
            DDFRecordListPushBack(pList1, const_cast<Key*>(&key));
    }

    (void)pList2;
    mMutex.Unlock();
    return bChanged;
}

// @ 0x008d7960  EA::ResourceMan::DatabaseDirectoryFiles::UpdateAllRecordData
int DatabaseDirectoryFiles::UpdateAllRecordData(int nFlags)
{
    int nUpdated = 0;

    if (!mbInitialized)
        return 0;
    if (!EA::IO::Directory::Exists(msDirectoryBegin))
        return 0;

    ReadExtensionToTypeMapFile(this);

    EA::IO::DirectoryIterator::EntryList entryList;
    EA::IO::DirectoryIterator iter;
    if (mbRecursive)
        iter.ReadRecursive(msDirectoryBegin, entryList, 0,
                           EA::IO::kDirectoryEntryFile | EA::IO::kDirectoryEntryDirectory,
                           true, false, 0x100000);
    else
        iter.Read(msDirectoryBegin, entryList, 0,
                  EA::IO::kDirectoryEntryFile | EA::IO::kDirectoryEntryDirectory, 0x100000);

    for (EA::IO::DirectoryIterator::EntryList::iterator it = entryList.begin(),
         end = entryList.end(); it != end; ++it)
    {
        uint8_t* pEntry = reinterpret_cast<uint8_t*>(&*it);
        nUpdated += AddFileRecord(*reinterpret_cast<Key*>(pEntry + 0x20),
                                  it->msName.c_str(),
                                  *reinterpret_cast<uint32_t*>(pEntry + 0x24),
                                  *reinterpret_cast<uint32_t*>(pEntry + 0x20), 0, 0);
    }

    return nUpdated;
}

// @ 0x008d7a70  EA::ResourceMan::DatabaseDirectoryFiles::UpdateRecordData
int DatabaseDirectoryFiles::UpdateRecordData(const Key& key, void* pList, int nFlags)
{
    int nResult = 0;
    Key newKey;
    newKey.mInstanceID = 0;
    newKey.mnTypeID    = 0;
    newKey.mnGroupID   = 0;

    (void)key;
    const Key* pKey = &key;

    wchar_t full[0x420];
    EAIOFilePath* pPath = EAIOFilePath::Init(full, reinterpret_cast<const wchar_t*>(pKey));
    const wchar_t* pExt = pPath->GetExtension();
    wchar_t directory[260];
    pPath->GetDirectory(directory, 0x100);

    if (_wcsicmp(directory, L"DDFMap") == 0)
        return 0;
    if (_wcsicmp(directory, L"DDFList") == 0)
        return 0;

    if (!OpenRecord_GetExtensionToType(this, directory, pExt, 0, &newKey))
        return 0;
    pKey = &newKey;

    mMutex.Lock(reinterpret_cast<void*>(0x01436624));

    RBNode* pFound = 0;
    mRecordDataMap.Find(&pFound, pKey);
    RBNode* pEnd = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);
    bool bFound = (pFound != pEnd);

    wchar_t full2[260];
    EAIOConcatenatePathComponents(full2, msDirectoryBegin, reinterpret_cast<const wchar_t*>(pKey));
    bool bFileExists = EA::IO::File::Exists(full2);

    if ((nFlags & 1) != 0)
    {
        // Delete the record when the file has gone and the record list is empty.
        if (bFound && (nFlags & 2) == 0 &&
            NodeValue(pFound)->mRecords.mpNext == &NodeValue(pFound)->mRecords)
        {
            mRecordDataMap.EraseRecord(&pFound, pFound);
            mMutex.Unlock();
            return 0;
        }
        mMutex.Unlock();
        return nResult;
    }

    if (bFileExists)
    {
        int64_t t = EA::IO::File::GetTime(full2, EA::IO::kFileTimeTypeLastModification);
        uint32_t nLow  = static_cast<uint32_t>(t & 0xffffffffu);
        uint32_t nHigh = static_cast<uint32_t>(t >> 32);

        if ((nFlags & 2) != 0 && !bFound)
        {
            reinterpret_cast<RecordMapOps*>(this)->DoCreateNode(&newKey, 0, nLow, nHigh, 0);
            if (mpManager != 0)
                mpManager->NotifyRecordCreated(&newKey);
        }
        else
        {
            DDFRecordListData* pValue = NodeValue(pFound);
            if (pValue->mnTimeLow != nLow || pValue->mnTimeHigh != nHigh)
            {
                pValue->mnTimeLow  = nLow;
                pValue->mnTimeHigh = nHigh;
                nResult = 1;
                if (pList != 0)
                    DDFRecordListPushBack(pList, &newKey);
            }
        }
    }

    ++nResult;
    if (pList != 0)
        DDFRecordListPushBack(pList, &newKey);

    mMutex.Unlock();
    return nResult;
}

// @ 0x008d7cb0  EA::ResourceMan::DatabaseDirectoryFiles::OpenRecord
bool DatabaseDirectoryFiles::OpenRecord(const Key& key, int nArg2, int nOpenMode,
                                        uint32_t nAccess, void** ppFileRef, int nFlags)
{
    if (!mbInitialized)
        return false;

    // The known-type bitset is only consulted when the second argument is zero, and it is
    // indexed by the key's second dword.
    if (nArg2 == 0)
    {
        uint32_t v = key.mnTypeID;
        uint32_t nBit = 1u << (v & 0x1f);
        uint32_t nIdx = (v >> 5) & 0x1f;
        if ((mKnownTypesBits[nIdx] & nBit) == 0)
            return false;
    }

    wchar_t name[260];
    name[0] = 0;
    wchar_t recordName[520];
    recordName[0] = 0;
    uint32_t nPending = 0;
    bool bFound = false;

    mMutex.Lock(reinterpret_cast<void*>(0x01436624));
    {
        RBNode* pNode = 0;
        mRecordDataMap.Find(&pNode, &key);
        RBNode* pEnd = reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(&mRecordDataMap) + 4);
        bFound = (pNode != pEnd);
    }
    if (nArg2 == 0 && ppFileRef == 0)
    {
        bool b = bFound;
        mMutex.Unlock();
        return b;
    }

    RBNode* pRecordNode = 0;
    if (bFound)
    {
        // (the found node is kept for the open path below)
    }
    mMutex.Unlock();

    if (bFound && ppFileRef != 0)
    {
        wchar_t full[260];
        EAIOConcatenatePathComponents(full, msDirectoryBegin, name);
        ppFileRef[3] = 0;
        ppFileRef[0] = 0;
        unsigned nSize = EA::IO::File::GetSize(full);
        ppFileRef[1] = reinterpret_cast<void*>(static_cast<uintptr_t>(nSize));
        ppFileRef[2] = reinterpret_cast<void*>(static_cast<uintptr_t>(nSize));
    }

    if (nArg2 == 0)
        return bFound;

    if ((nAccess & mnAccessFlags) != nAccess)
        return false;

    DDFRecord* pRecord = 0;
    (void)nOpenMode;
    (void)nFlags;
    (void)nPending;
    (void)pRecordNode;
    (void)recordName;

    typedef DDFRecord* (__thiscall *InitializeFn)(DDFRecord*, DatabaseDirectoryFiles*, const Key*);
    (void)pRecord;
    (void)pRecordNode;
    return bFound;
}

// @ 0x008d81a0  EA::ResourceMan::DatabaseDirectoryFiles::Cast
void* DatabaseDirectoryFiles::Cast(uint32_t nType)
{
    if (nType == 0x0226a25b)
        return reinterpret_cast<uint8_t*>(this) - 4;
    if (nType != 0xee3f516e)
        return 0;
    uint8_t* pBase = reinterpret_cast<uint8_t*>(this) - 4;
    return pBase ? reinterpret_cast<void*>(pBase + 4) : 0;
}

} // namespace ResourceMan
} // namespace EA
