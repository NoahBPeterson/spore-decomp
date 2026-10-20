// slice s008d62f0 -- EA::ResourceMan::DatabaseDirectoryFiles (UTFSpore_Win32/DatabaseDirectoryFiles.obj)
// Object file: UTFSpore_Win32/DatabaseDirectoryFiles.obj.  Hand reconstruction from the image
// (retail class layout + observable algorithms); see symbols/slices/s008d62f0.txt.
// Flags: /O2 /MD /GS- /GR- /TP /arch:SSE

#include <new>
#include <string.h>

typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef int            ptrdiff_t;
typedef unsigned int   size_t;

namespace EA { namespace ResourceMan { struct RBNode; } }

// ---- external helpers (address in the comment) ----
extern "C" int __cdecl _wcsicmp(const wchar_t* pA, const wchar_t* pB);
extern "C" wchar_t* __cdecl wcsncpy(wchar_t* pDst, const wchar_t* pSrc, size_t n);
extern "C" unsigned long __cdecl strtoul(const char* pStr, char** ppEnd, int nBase);

void* EAAllocate(unsigned int nSize, const char* pName, int nA, int nB,
                 const char* pFile, int nLine);                          // 0x00f473a0
void  EAOperatorDelete(void* p);                                         // 0x00f47380
namespace EA { namespace ResourceMan { struct RBNode; } }

void* RBTreeIncrement(void* pNode);                                      // 0x00921580
void* RBTreeDecrement(void* pNode);                                      // 0x009215c0
void  RBTreeInsert(void* pNode, void* pParent, void* pAnchor, int nSide); // 0x009216a0
void  RBTreeErase(void* pNode, void* pAnchor);                           // 0x00921880
int   BasicStringCompare(const wchar_t* a0, const wchar_t* a1,
                         const wchar_t* b0, const wchar_t* b1);          // 0x005e9260
void  WStrAllocateSelf(void* pThis, unsigned int nCapacity);             // 0x00429760
void  WStrAssign(void* pThis, const wchar_t* pBegin, const wchar_t* pEnd);// 0x00423650
void  WStrFreeSelf(void* pThis);                                         // 0x00931770
void* WStringCtor(void* pDst, const void* pSrc);                         // 0x009337f0
void  ListBaseDoClear(void* pList);                                      // 0x0060c4a0
void  cWStringRangeInitialize(void* pThis, const wchar_t* pStr);         // 0x00579a90
void** RbTreeFind(void* pTree, void** ppOut, const void* pKey);          // 0x00a21dc0 (ret 8)
void** HoleFind(void* pTree, void** ppOut, const void* pKey);            // 0x00e5c780
void   HoleErase(void* pTree, void* pNode);                              // 0x008dae70 (HoleSet::Erase)
void   HoleInsert(void* pTree, void** ppOut, const void* pKey);          // 0x00a17a70
void   KeyVecPushBack(void* pVector, const void* pKey);                  // 0x004e3e10
void   WStrFormat(void* pString, const wchar_t* pFormat, ...);           // 0x0041e050

namespace EA { namespace Thread {
class Mutex_s008d_62f0
{
public:
    Mutex_s008d_62f0() {}
    Mutex_s008d_62f0(int nSpinCount, int nType);
    ~Mutex_s008d_62f0();
    int Lock(void* pCaller);   // 0x009221b0 (EA::Thread::Mutex::Lock)
    int Unlock();              // 0x00922270 (EA::Thread::Mutex::Unlock)
private:
    uint32_t mpImpl[0x2c / 4];
};
}}
namespace EA { namespace Allocator {
class ICoreAllocator_s008d_62f0
{
public:
    virtual void* Allocate(unsigned int nSize, const char* pName, unsigned int nFlags); // vtbl +0x08
    virtual void  Free(void* p, unsigned int nSize);                                    // vtbl +0x0c
    static ICoreAllocator_s008d_62f0* GetDefaultAllocator();   // 0x00925cb0
};
}}
namespace EA { namespace IO {
class FileStream_s008d_62f0
{
public:
    FileStream_s008d_62f0(const wchar_t* pPath);    // 0x00931e10
    ~FileStream_s008d_62f0();                       // 0x00931e70
    bool Open(unsigned int nMode, unsigned int nAccess, unsigned int nShare, unsigned int nFlags); // 0x009318f0
    bool Close();                                   // 0x00931a70
    void AddRef();                                  // 0x009317b0
};
class StreamBuffer_s008d_62f0
{
public:
    StreamBuffer_s008d_62f0(unsigned int nSize, unsigned int nFlags, FileStream_s008d_62f0* pStream); // 0x0093b530
    ~StreamBuffer_s008d_62f0();                     // 0x0093b5a0
};
unsigned ReadLine(StreamBuffer_s008d_62f0* pBuf, char* pLine, unsigned int nSize); // 0x0093a8b0
unsigned ConcatenatePathComponents(wchar_t* pDst, const wchar_t* pDir, const wchar_t* pFile); // 0x0092fe60
int      StripPathComponent(wchar_t* pPath, int nCount);  // 0x0092fee0
unsigned SplitDirectory(const wchar_t* pPath, wchar_t* pOut, unsigned int a, unsigned int b); // 0x009302b0
namespace File { bool Exists(const wchar_t* pPath); }     // 0x00931fa0
}}

namespace EA { namespace ResourceMan {

struct Key_s008d_62f0
{
    uint32_t mnTypeID;      // 0x00
    uint32_t mnGroupID;     // 0x04
    uint32_t mnInstanceID;  // 0x08
};

struct ListAnchor
{
    void* mpNext;   // 0x00
    void* mpPrev;   // 0x04
};

struct String16
{
    const wchar_t* mpBegin;     // +0x00
    const wchar_t* mpEnd;       // +0x04
    const wchar_t* mpCapacity;  // +0x08
};

// The value stored in the Key rbtree (offset +0x10 of the tree node when reached through the
// pair; the node itself only stores this part).
struct DDFRecordListData
{
    String16   mName;         // +0x00
    uint32_t   mnUnknown0c;   // +0x0c
    uint32_t   mnValue10;     // +0x10
    uint32_t   mnValue14;     // +0x14
    ListAnchor mRecords;      // +0x18  list<AutoRefCount<DDFRecord>>
};  // 0x20

struct RBNode
{
    RBNode* mpLeft;    // 0x00
    RBNode* mpRight;   // 0x04
    RBNode* mpParent;  // 0x08
    uint32_t mnColor;  // 0x0c
    // payload follows
};

struct RBTree
{
    void*   mpAllocator;  // +0x00
    RBNode* mpAnchor;     // +0x04 self-referential header node
    RBNode* mpBegin;      // +0x08 left-most node
    RBNode* mpRoot;       // +0x0c
    uint32_t mnUnknown10; // +0x10
    uint32_t mnCount;     // +0x14
    void*   mpAllocIface; // +0x18 ICoreAllocator*
    uint32_t mnAllocName; // +0x1c
};

// list<AutoRefCount<DDFRecord>> node (extends the anchor so the head/tail node is the anchor)
class DDFRecord;
struct ListRefNode : ListAnchor
{
    DDFRecord*   mpRef;     // +0x08
};

// pair<string16,uint32> as stored in a node of the extension tree (node+0x10).
struct ExtPair
{
    String16 mKey;       // +0x00
    uint32_t mnValue;    // +0x10
    ExtPair* Construct(const String16& key, const uint32_t& value);
};

inline RBNode* Anchor(RBTree* pTree) { return reinterpret_cast<RBNode*>(reinterpret_cast<uint8_t*>(pTree) + 4); }
inline String16* NodeExtKey(RBNode* pNode) { return reinterpret_cast<String16*>(reinterpret_cast<uint8_t*>(pNode) + 0x10); }
inline uint32_t* NodeExtValue(RBNode* pNode) { return reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(pNode) + 0x20); }
inline DDFRecordListData* NodeValue(RBNode* pNode) { return reinterpret_cast<DDFRecordListData*>(reinterpret_cast<uint8_t*>(pNode) + 0x20); }
inline const Key_s008d_62f0* NodeKey(RBNode* pNode) { return reinterpret_cast<const Key_s008d_62f0*>(reinterpret_cast<uint8_t*>(pNode) + 0x10); }
inline Key_s008d_62f0* NodeKeyMutable(RBNode* pNode) { return reinterpret_cast<Key_s008d_62f0*>(reinterpret_cast<uint8_t*>(pNode) + 0x10); }

inline void FreeString16(String16* pStr)
{
    uint32_t nBytes = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(pStr->mpCapacity) -
                                            reinterpret_cast<uintptr_t>(pStr->mpBegin));
    nBytes &= 0xfffffffeu;
    if (nBytes > 2 && pStr->mpBegin != 0)
        EAOperatorDelete(const_cast<wchar_t*>(pStr->mpBegin));
}

inline void FreeTreeNode(RBTree* pTree, RBNode* pNode, unsigned int nSize)
{
    EA::Allocator::ICoreAllocator_s008d_62f0* pAlloc =
        reinterpret_cast<EA::Allocator::ICoreAllocator_s008d_62f0*>(pTree->mpAllocIface);
    pAlloc->Free(pNode, nSize);
}

inline RBNode* AllocTreeNode(RBTree* pTree, unsigned int nSize)
{
    EA::Allocator::ICoreAllocator_s008d_62f0* pAlloc =
        reinterpret_cast<EA::Allocator::ICoreAllocator_s008d_62f0*>(pTree->mpAllocIface);
    return reinterpret_cast<RBNode*>(pAlloc->Allocate(nSize, 0, pTree->mnAllocName));
}

}}  // namespace EA::ResourceMan

namespace EA { namespace ResourceMan {
void ExtTreeDoNukeSubtree(RBTree* pTree, RBNode* pNode);                 // 0x008d6be0
void KeyTreeDoNukeSubtree(RBTree* pTree, RBNode* pNode);                 // 0x008d6d90
void ListRefAppend(ListAnchor* pList, ListRefNode* pFirst, ListRefNode* pLast, bool bUnused); // 0x008d65e0
void ExtTreeDoInsertValueImpl(RBTree* pTree, RBNode* pPosition, const String16* pKey, bool bLeft); // 0x008d6830
void KeyTreeDoInsertValueImpl(RBTree* pTree, RBNode* pPosition, const void* pKey, bool bLeft);      // 0x008d6e20
RBNode* KeyTreeErase(RBTree* pTree, RBNode* pNode);                      // 0x008d6d20
}}

namespace EA { namespace ResourceMan {

class DDFRecord;

// The object the record list's AutoRefCount<DDFRecord> points at.
class IRecordStream
{
public:
    virtual void v00();                  // +0x00
    virtual void v04();                  // +0x04
    virtual void v08();                  // +0x08
    virtual void v0c();                  // +0x0c
    virtual int  GetFlags();             // +0x10
    virtual void v14();                  // +0x14
    virtual void v18();                  // +0x18
    virtual void v1c();                  // +0x1c
    virtual void v20();                  // +0x20
    virtual void v24();                  // +0x24
    virtual void v28();                  // +0x28
    virtual void v2c();                  // +0x2c
    virtual void v30();                  // +0x30
    virtual void Close();                // +0x34
};

class DDFRecord
{
public:
    virtual void  v00();                                 // +0x00
    virtual void  AddRef();                              // +0x04
    virtual void  Release();                             // +0x08
    virtual void  v0c();                                 // +0x0c
    virtual const Key_s008d_62f0* GetKey();              // +0x10
    virtual void  v14();                                 // +0x14
    virtual IRecordStream* GetStream();                  // +0x18
    virtual void  v1c();                                 // +0x1c

    EA::IO::FileStream_s008d_62f0 mStream;               // +0x08
    uint32_t mnPad;                                      // ...
    uint32_t mnOpenFlag;                                 // +0x244 (atomics)
};

// ---- the class itself (retail layout, 0x168 bytes) ----
class Manager;

class DatabaseDirectoryFiles
{
public:
    bool SetManager(bool bAttach, Manager* pManager, void* pContext);        // 0x008d62f0
    bool CloseUnreferencedRecords();                                         // 0x008d6410
    int  GetRecordCount(const Key_s008d_62f0& key);                          // 0x008d64a0
    bool GetRecordName(const Key_s008d_62f0& key, wchar_t* pName);           // 0x008d6510
    bool SetLocation(const wchar_t* pLocation);                              // 0x008d6650
    bool RemoveRecord(DDFRecord* pRecord);                                   // 0x008d66a0
    void CloseOpenRecords();                                                 // 0x008d6770
    int  GetKeyList(void* pKeyVector, void* pFilter);                        // 0x008d6b20
    bool AddExtensionMapping(const wchar_t* pExtension, uint32_t nValue);     // 0x008d6c40
    bool ReadExtensionToTypeMapFile();                                       // 0x008d6ed0

    // ---- retail layout (0x168 bytes, two vtable pointers) ----
    void*  mpVtbl0;                    // 0x000
    void*  mpVtbl1;                    // 0x004
    int    mnRefCount;                 // 0x008
    bool   mbInitialized;              // 0x00c
    uint8_t mPad0d[3];

    EA::Allocator::ICoreAllocator_s008d_62f0* mpAllocator;  // 0x010
    bool   mbRequireDirectoryExists;   // 0x014
    bool   mbRecursive;                // 0x015
    uint8_t mPad16[2];

    uint32_t mnAccessFlags;            // 0x018
    String16 msDirectory;              // 0x01c
    uint32_t mDirectoryAllocator;      // 0x028

    uint8_t  mExtensionPool[0x20];     // 0x02c
    uint8_t  mRecordPool[0x20];        // 0x04c

    RBTree mExtensionToTypeMap;        // 0x06c
    RBTree mRecordDataMap;             // 0x08c

    uint32_t mDefaultGroupId;          // 0x0ac
    Manager* mpManager;                // 0x0b0
    void*    mpFileNameToKeyConverter; // 0x0b4

    uint32_t mKnownTypesBits[0x20];    // 0x0b8

    EA::Thread::Mutex_s008d_62f0 mMutex;  // 0x138

    void SetSource(void* pArg0, Manager* pOld, void* pContext);  // vtable +0x44
};

}}  // namespace EA::ResourceMan

namespace EA { namespace ResourceMan {

// @ 0x008d62f0
bool DatabaseDirectoryFiles::SetManager(bool bAttach, Manager* pManager, void* pContext)
{
    if (bAttach)
    {
        Manager* pOld = mpManager;
        if (pOld != 0 && pManager != pOld)
            SetSource(0, pOld, pContext);

        if (pManager == 0)
            return false;

        if (pContext == 0)
        {
            typedef bool (__thiscall *SetManagerFn)(Manager*, int, DatabaseDirectoryFiles*, void*);
            SetManagerFn pfn = *reinterpret_cast<SetManagerFn*>(*reinterpret_cast<uint8_t**>(pManager) + 0x50);
            return pfn(pManager, 1, this, 0);
        }

        mpManager = pManager;

        RBNode* pEnd = Anchor(&mRecordDataMap);
        for (RBNode* pNode = mRecordDataMap.mpBegin; pNode != pEnd; pNode = reinterpret_cast<RBNode*>(RBTreeIncrement(pNode)))
        {
            typedef void (__thiscall *AddRecursiveFn)(Manager*, const Key_s008d_62f0*, const wchar_t*);
            AddRecursiveFn pfn = *reinterpret_cast<AddRecursiveFn*>(*reinterpret_cast<uint8_t**>(mpManager) + 0x80);
            pfn(mpManager, NodeKey(pNode), NodeValue(pNode)->mName.mpBegin);
        }
        return true;
    }

    if (pManager != 0 && pManager != mpManager)
        return false;

    if (pContext != 0)
    {
        mpManager = 0;
        return true;
    }

    typedef bool (__thiscall *SetManagerFn)(Manager*, int, DatabaseDirectoryFiles*, void*);
    SetManagerFn pfn = *reinterpret_cast<SetManagerFn*>(*reinterpret_cast<uint8_t**>(mpManager) + 0x50);
    return pfn(mpManager, 0, this, 0);
}

// @ 0x008d6410
bool DatabaseDirectoryFiles::CloseUnreferencedRecords()
{
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    RBNode* pEnd = Anchor(&mRecordDataMap);
    for (RBNode* pNode = mRecordDataMap.mpBegin; pNode != pEnd; pNode = reinterpret_cast<RBNode*>(RBTreeIncrement(pNode)))
    {
        ListAnchor* pList = &NodeValue(pNode)->mRecords;
        int nCount = 0;
        for (void* p = pList->mpNext; p != pList; p = *reinterpret_cast<void**>(p))
            ++nCount;

        if (nCount == 1)
        {
            DDFRecord* pRecord = *reinterpret_cast<DDFRecord**>(reinterpret_cast<uint8_t*>(pList->mpNext) + 8);
            IRecordStream* pStream = pRecord->GetStream();
            if (pStream->GetFlags() & 2)
                pStream->Close();
        }
    }

    mMutex.Unlock();
    return true;
}

// @ 0x008d64a0
int DatabaseDirectoryFiles::GetRecordCount(const Key_s008d_62f0& key)
{
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    RBNode* pNode = 0;
    RbTreeFind(&mRecordDataMap, reinterpret_cast<void**>(&pNode), &key);

    if (pNode == Anchor(&mRecordDataMap))
    {
        mMutex.Unlock();
        return 0;
    }

    ListAnchor* pList = &NodeValue(pNode)->mRecords;
    int nCount = 0;
    for (void* p = pList->mpNext; p != pList; p = *reinterpret_cast<void**>(p))
        ++nCount;

    mMutex.Unlock();
    return nCount;
}

// @ 0x008d6510
bool DatabaseDirectoryFiles::GetRecordName(const Key_s008d_62f0& key, wchar_t* pName)
{
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    RBNode* pNode = 0;
    RbTreeFind(&mRecordDataMap, reinterpret_cast<void**>(&pNode), &key);

    if (pNode == Anchor(&mRecordDataMap))
    {
        mMutex.Unlock();
        return false;
    }

    if (pName != 0)
    {
        const wchar_t* pSrc = NodeValue(pNode)->mName.mpBegin;
        wchar_t c;
        do
        {
            c = *pSrc++;
            *pName++ = c;
        } while (c != 0);
    }

    mMutex.Unlock();
    return true;
}

// @ 0x008d6580
ExtPair* ExtPair::Construct(const String16& key, const uint32_t& value)
{
    mKey.mpBegin    = 0;
    mKey.mpEnd      = 0;
    mKey.mpCapacity = 0;

    ptrdiff_t nChars = key.mpEnd - key.mpBegin;
    WStrAllocateSelf(&mKey, static_cast<unsigned int>(nChars + 1));

    wchar_t* pDst = const_cast<wchar_t*>(mKey.mpBegin);
    memcpy(pDst, key.mpBegin, static_cast<size_t>(nChars) * sizeof(wchar_t));
    pDst[nChars] = 0;
    mKey.mpEnd = pDst + nChars;

    mnValue = value;
    return this;
}

// @ 0x008d65e0
void ListRefAppend(ListAnchor* pList, ListRefNode* pFirst, ListRefNode* pLast, bool bUnused)
{
    (void)bUnused;
    for (ListRefNode* p = pFirst; p != pLast; p = reinterpret_cast<ListRefNode*>(p->mpNext))
    {
        ListRefNode* pNew = reinterpret_cast<ListRefNode*>(
            EAAllocate(0xc, "EASTL", 0, 0,
                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                       0xd1));

        if (pNew != 0)
        {
            pNew->mpRef = p->mpRef;
            if (pNew->mpRef != 0)
                pNew->mpRef->AddRef();
        }

        pNew->mpNext = pList;
        pNew->mpPrev = pList->mpPrev;
        reinterpret_cast<ListRefNode*>(pList->mpPrev)->mpNext = pNew;
        pList->mpPrev = pNew;
    }
}

// @ 0x008d6650
bool DatabaseDirectoryFiles::SetLocation(const wchar_t* pLocation)
{
    if (mnAccessFlags == 0)
    {
        const wchar_t* pEnd = pLocation;
        while (*pEnd != 0)
            ++pEnd;
        WStrAssign(&msDirectory, pLocation, pEnd);
        WStrFreeSelf(&msDirectory);
    }
    return mnAccessFlags == 0;
}

// @ 0x008d66a0
bool DatabaseDirectoryFiles::RemoveRecord(DDFRecord* pRecord)
{
    bool bRemoved = false;
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    RBNode* pNode = 0;
    RbTreeFind(&mRecordDataMap, reinterpret_cast<void**>(&pNode), pRecord->GetKey());

    if (pNode != Anchor(&mRecordDataMap))
    {
        ListAnchor* pList = &NodeValue(pNode)->mRecords;
        ListRefNode* pFirst = reinterpret_cast<ListRefNode*>(pList->mpNext);
        ListRefNode* pHead  = reinterpret_cast<ListRefNode*>(pList);
        for (ListRefNode* p = pFirst; p != pHead; p = reinterpret_cast<ListRefNode*>(p->mpNext))
        {
            if (p->mpRef == pRecord)
            {
                pRecord->AddRef();

                ListRefNode* pDel = p;
                reinterpret_cast<ListRefNode*>(pDel->mpPrev)->mpNext = pDel->mpNext;
                reinterpret_cast<ListRefNode*>(pDel->mpNext)->mpPrev = pDel->mpPrev;

                if (pDel->mpRef != 0)
                    pDel->mpRef->Release();
                EAOperatorDelete(pDel);
                bRemoved = true;
                break;
            }
        }
    }

    mMutex.Unlock();

    if (bRemoved)
    {
        pRecord->mnOpenFlag = 0;
        pRecord->mStream.Close();
        pRecord->Release();
        return true;
    }
    return false;
}

// @ 0x008d6770
void DatabaseDirectoryFiles::CloseOpenRecords()
{
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    RBNode* pEnd = Anchor(&mRecordDataMap);
    for (RBNode* pNode = mRecordDataMap.mpBegin; pNode != pEnd; pNode = reinterpret_cast<RBNode*>(RBTreeIncrement(pNode)))
    {
        ListAnchor* pList = &NodeValue(pNode)->mRecords;
        if (pList->mpNext == pList)
            continue;

        for (ListRefNode* p = reinterpret_cast<ListRefNode*>(pList->mpNext);
             p != reinterpret_cast<ListRefNode*>(pList); p = reinterpret_cast<ListRefNode*>(p->mpNext))
        {
            DDFRecord* pRecord = p->mpRef;
            uint32_t nOpen = pRecord->mnOpenFlag;
            if (nOpen != 0)
            {
                pRecord->mnOpenFlag = 0;
                pRecord->mStream.Close();
            }
        }

        ListRefNode* p = reinterpret_cast<ListRefNode*>(pList->mpNext);
        while (p != reinterpret_cast<ListRefNode*>(pList))
        {
            ListRefNode* pNext = reinterpret_cast<ListRefNode*>(p->mpNext);
            if (p->mpRef != 0)
                p->mpRef->Release();
            EAOperatorDelete(p);
            p = pNext;
        }
        pList->mpNext = pList;
        pList->mpPrev = pList;
    }

    mMutex.Unlock();
}

// @ 0x008d6830
void ExtTreeDoInsertValueImpl(RBTree* pTree, RBNode* pPosition, const String16* pKey, bool bLeft)
{
    bool bInsertLeft = false;
    if (!bLeft && pPosition != Anchor(pTree))
    {
        const String16* pPosKey = NodeExtKey(pPosition);
        if (BasicStringCompare(pKey->mpBegin, pKey->mpEnd, pPosKey->mpBegin, pPosKey->mpEnd) >= 0)
            bInsertLeft = true;
    }

    RBNode* pNode = AllocTreeNode(pTree, 0x24);
    if (pNode != 0)
        reinterpret_cast<ExtPair*>(reinterpret_cast<uint8_t*>(pNode) + 0x10)->Construct(*pKey, *NodeExtValue(pNode));

    RBTreeInsert(pNode, pPosition, Anchor(pTree), bInsertLeft ? 1 : 0);
    ++pTree->mnCount;
}

// @ 0x008d68c0
struct HoleSet_s008d_62f0
{
    uint8_t mPad000[0x444];
    RBTree  mMap;        // 0x444
};

bool HoleSetInsertRemove(HoleSet_s008d_62f0* pThis, void* pEntry, bool bAdd)
{
    uint32_t nCountBefore = pThis->mMap.mnCount;

    if (pEntry != 0)
    {
        RBNode* pNode = 0;
        HoleFind(&pThis->mMap, reinterpret_cast<void**>(&pNode), pEntry);

        if (!bAdd)
        {
            if (pNode != Anchor(&pThis->mMap))
            {
                HoleErase(&pThis->mMap, pNode);
                typedef void (__thiscall *ReleaseFn)(void*);
                ReleaseFn pfn = *reinterpret_cast<ReleaseFn*>(*reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(pEntry) + 4) + 4);
                pfn(reinterpret_cast<uint8_t*>(pEntry) + 4);
            }
        }
        else if (pNode == Anchor(&pThis->mMap))
        {
            typedef void (__thiscall *AddRefFn)(void*);
            AddRefFn pfn = *reinterpret_cast<AddRefFn*>(*reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(pEntry) + 4));
            pfn(reinterpret_cast<uint8_t*>(pEntry) + 4);
            HoleInsert(&pThis->mMap, reinterpret_cast<void**>(&pNode), pEntry);
        }
    }

    return nCountBefore != pThis->mMap.mnCount;
}

DDFRecordListData* DDFRecordListDataConstruct(DDFRecordListData* pThis, const DDFRecordListData* pSrc);

// @ 0x008d6970
DDFRecordListData* DDFRecordListDataConstruct(DDFRecordListData* pThis, const DDFRecordListData* pSrc)
{
    pThis->mName.mpBegin    = 0;
    pThis->mName.mpEnd      = 0;
    pThis->mName.mpCapacity = 0;

    ptrdiff_t nChars = pSrc->mName.mpEnd - pSrc->mName.mpBegin;
    WStrAllocateSelf(&pThis->mName, static_cast<unsigned int>(nChars + 1));

    wchar_t* pDst = const_cast<wchar_t*>(pThis->mName.mpBegin);
    memcpy(pDst, pSrc->mName.mpBegin, static_cast<size_t>(nChars) * sizeof(wchar_t));
    pDst[nChars] = 0;
    pThis->mName.mpEnd = pDst + nChars;

    pThis->mnValue10 = pSrc->mnValue10;
    pThis->mnValue14 = pSrc->mnValue14;

    ListAnchor* pList = &pThis->mRecords;
    pList->mpNext = pList;
    pList->mpPrev = pList;
    ListRefAppend(pList,
                  reinterpret_cast<ListRefNode*>(const_cast<void*>(pSrc->mRecords.mpNext)),
                  reinterpret_cast<ListRefNode*>(const_cast<ListAnchor*>(&pSrc->mRecords)),
                  false);

    return pThis;
}

// @ 0x008d69f0
void ExtTreeDoInsertValue(RBTree* pTree, RBNode** ppOutNode, bool* pbInserted, const String16* pKey)
{
    RBNode* pNode   = Anchor(pTree);
    RBNode* pParent = 0;
    bool    bLeft   = true;

    if (pTree->mpRoot != 0)
    {
        pParent = pTree->mpRoot;
        do
        {
            pNode = pParent;
            const String16* pNodeKey = NodeExtKey(pNode);
            int nCmp = BasicStringCompare(pKey->mpBegin, pKey->mpEnd,
                                          pNodeKey->mpBegin, pNodeKey->mpEnd);
            bLeft   = nCmp < 0;
            pParent = bLeft ? pNode->mpLeft : pNode->mpRight;
        } while (pParent != 0);
    }

    if (bLeft)
    {
        if (pNode == pTree->mpBegin)
        {
            ExtTreeDoInsertValueImpl(pTree, pNode, pKey, false);
            *ppOutNode  = 0;
            *pbInserted = true;
            return;
        }
        pNode = reinterpret_cast<RBNode*>(RBTreeDecrement(pNode));
    }

    const String16* pNodeKey = NodeExtKey(pNode);
    if (BasicStringCompare(pNodeKey->mpBegin, pNodeKey->mpEnd, pKey->mpBegin, pKey->mpEnd) < 0)
    {
        ExtTreeDoInsertValueImpl(pTree, pNode, pKey, false);
        *ppOutNode  = 0;
        *pbInserted = true;
        return;
    }

    *ppOutNode  = pNode;
    *pbInserted = false;
}

// @ 0x008d6b20
int DatabaseDirectoryFiles::GetKeyList(void* pKeyVector, void* pFilter)
{
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    int nCount = 0;
    RBNode* pEnd = Anchor(&mRecordDataMap);
    for (RBNode* pNode = mRecordDataMap.mpBegin; pNode != pEnd; pNode = reinterpret_cast<RBNode*>(RBTreeIncrement(pNode)))
    {
        const Key_s008d_62f0* pKey = NodeKey(pNode);

        bool bAccept = true;
        if (pFilter != 0)
        {
            typedef bool (__thiscall *FilterFn)(void*, const Key_s008d_62f0*);
            FilterFn pfn = *reinterpret_cast<FilterFn*>(*reinterpret_cast<uint8_t**>(pFilter) + 4);
            bAccept = pfn(pFilter, pKey);
        }

        if (bAccept)
        {
            if (pKeyVector != 0)
                KeyVecPushBack(pKeyVector, pKey);
            ++nCount;
        }
    }

    mMutex.Unlock();
    return nCount;
}

// @ 0x008d6be0
void ExtTreeDoNukeSubtree(RBTree* pTree, RBNode* pNode)
{
    while (pNode != 0)
    {
        ExtTreeDoNukeSubtree(pTree, pNode->mpLeft);
        RBNode* pRight = pNode->mpRight;
        FreeString16(NodeExtKey(pNode));
        FreeTreeNode(pTree, pNode, 0x24);
        pNode = pRight;
    }
}

// @ 0x008d6c40
bool DatabaseDirectoryFiles::AddExtensionMapping(const wchar_t* pExtension, uint32_t nValue)
{
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    if (*pExtension == L'.')
        ++pExtension;

    if (*pExtension == 0)
    {
        mMutex.Unlock();
        return false;
    }

    String16 key;
    cWStringRangeInitialize(&key, pExtension);

    ExtPair pair;
    pair.Construct(key, nValue);

    RBNode* pOut = 0;
    bool bInserted = false;
    ExtTreeDoInsertValue(&mExtensionToTypeMap, &pOut, &bInserted, &pair.mKey);

    FreeString16(&pair.mKey);
    FreeString16(&key);

    mMutex.Unlock();
    return true;
}

// @ 0x008d6d20
RBNode* KeyTreeErase(RBTree* pTree, RBNode* pNode)
{
    --pTree->mnCount;
    RBNode* pNext = reinterpret_cast<RBNode*>(RBTreeIncrement(pNode));
    RBTreeErase(pNode, Anchor(pTree));
    ListBaseDoClear(&NodeValue(pNode)->mRecords);
    FreeString16(&NodeValue(pNode)->mName);
    FreeTreeNode(pTree, pNode, 0x48);
    return pNext;
}

// @ 0x008d6d90
void KeyTreeDoNukeSubtree(RBTree* pTree, RBNode* pNode)
{
    while (pNode != 0)
    {
        KeyTreeDoNukeSubtree(pTree, pNode->mpLeft);
        RBNode* pRight = pNode->mpRight;

        DDFRecordListData* pValue = NodeValue(pNode);
        ListAnchor* pList = &pValue->mRecords;
        ListRefNode* p = reinterpret_cast<ListRefNode*>(pList->mpNext);
        while (p != reinterpret_cast<ListRefNode*>(pList))
        {
            ListRefNode* pNext = reinterpret_cast<ListRefNode*>(p->mpNext);
            if (p->mpRef != 0)
                p->mpRef->Release();
            EAOperatorDelete(p);
            p = pNext;
        }

        FreeString16(&pValue->mName);
        FreeTreeNode(pTree, pNode, 0x48);
        pNode = pRight;
    }
}

// @ 0x008d6e20
void KeyTreeDoInsertValueImpl(RBTree* pTree, RBNode* pPosition, const void* pKey, bool bLeft)
{
    (void)bLeft;
    (void)pPosition;
    (void)pKey;
    (void)pTree;
}

// @ 0x008d6ed0
bool DatabaseDirectoryFiles::ReadExtensionToTypeMapFile()
{
    if (!mbInitialized)
        return false;

    wchar_t directory[0x104];
    wcsncpy(directory, msDirectory.mpBegin, 0x104);
    directory[0x103] = 0;

    wchar_t path[0x104];
    wchar_t parent[0x104];
    for (;;)
    {
        EA::IO::ConcatenatePathComponents(path, directory, L"DDFMap.txt");
        if (EA::IO::File::Exists(path))
            break;
        EA::IO::StripPathComponent(path, 8);
        if (EA::IO::SplitDirectory(path, parent, 2, 4) != 2)
            return false;
    }

    bool bResult = false;
    {
        EA::IO::FileStream_s008d_62f0 stream(path);
        if (stream.Open(1, 6, 1, 0))
        {
            mMutex.Lock(reinterpret_cast<void*>(0x1436624));
            stream.AddRef();
            {
                EA::IO::StreamBuffer_s008d_62f0 buffer(0x400, 0, &stream);

                char line[0x100];
                bool bMapCleared = false;
                unsigned int nLen = EA::IO::ReadLine(&buffer, line, 0x100);

                for (; nLen < 0xfffffffe; nLen = EA::IO::ReadLine(&buffer, line, 0x100))
                {
                    if (nLen >= 0xc && line[0] == '0' && (line[1] == 'x' || line[1] == 'X'))
                    {
                        line[0x16] = 0;
                        uint32_t nTypeId = static_cast<uint32_t>(strtoul(&line[6], 0, 16));

                        wchar_t ext[0x20];
                        unsigned int i = 0;
                        for (; i < 0x1f; ++i)
                        {
                            char c = line[0xb + i];
                            if (c == 0 || c <= ' ')
                                break;
                            ext[i] = static_cast<wchar_t>(c);
                        }
                        ext[i] = 0;

                        if (!bMapCleared)
                        {
                            ExtTreeDoNukeSubtree(&mExtensionToTypeMap, mExtensionToTypeMap.mpRoot);
                            RBNode* pAnchor = Anchor(&mExtensionToTypeMap);
                            pAnchor->mpLeft = pAnchor;
                            mExtensionToTypeMap.mpBegin = pAnchor;
                            mExtensionToTypeMap.mpRoot = 0;
                            mExtensionToTypeMap.mnUnknown10 = 0;
                            mExtensionToTypeMap.mnCount = 0;
                            bMapCleared = true;
                        }

                        AddExtensionMapping(ext, nTypeId);
                    }
                    else if (nLen >= 5 && line[0] == 'g')
                    {
                        if (line[2] == '0' && (line[3] == 'x' || line[3] == 'X'))
                        {
                            mDefaultGroupId = static_cast<uint32_t>(strtoul(&line[8], 0, 16));
                        }
                        else
                        {
                            char* p = &line[2];
                            while (*p != 0 && *p != ' ' && *p != '\t' && *p != '/' && *p != '#')
                                ++p;
                            *p = 0;

                            String16 name;
                            name.mpBegin    = L"";
                            name.mpEnd      = L"";
                            name.mpCapacity = L"" + 2;
                            WStrFormat(&name, L"%hs!", &line[2]);

                            uint32_t nValue = 0;
                            if (mpFileNameToKeyConverter != 0)
                            {
                                typedef void (__stdcall *ConvertFn)(const wchar_t*, int, const wchar_t*, uint32_t*);
                                ConvertFn pfn = reinterpret_cast<ConvertFn>(mpFileNameToKeyConverter);
                                pfn(name.mpBegin, 0, name.mpBegin, &nValue);
                            }
                            else
                            {
                                typedef void (__stdcall *DefaultConvertFn)(uint32_t*, const wchar_t*, int, int, int, int);
                                DefaultConvertFn pfn = *reinterpret_cast<DefaultConvertFn*>(0x154c464);
                                pfn(&nValue, name.mpBegin, 0, 0, 0, 0);
                            }

                            mDefaultGroupId = nValue;
                            FreeString16(&name);
                        }
                    }
                }

                bResult = true;
            }  // ~StreamBuffer
            mMutex.Unlock();
        }
    }  // ~FileStream

    return bResult;
}

// @ 0x008d7200
RBNode* RecordMapEraseIterator(RBTree* pTree, RBNode* pNode)
{
    return KeyTreeErase(pTree, pNode);
}

}}  // namespace EA::ResourceMan
