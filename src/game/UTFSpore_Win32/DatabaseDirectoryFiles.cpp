// src/game/UTFSpore_Win32/DatabaseDirectoryFiles.cpp -- migrated from slice(s) s008d62f0, s008d5340, s008d7220 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DatabaseDirectoryFiles.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
#include <new>
#include "EA/IO/FileStream.h"
#include "EA/Thread/Mutex.h"
#include <string.h>

// ---- items of slice s008d7220 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uintptr_t;
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
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

    void DoClear();   // 0x0060c4a0 (thiscall)
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

// ---- items of slice s008d5340 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t* s, wchar_t** pEnd, int radix);
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long* pAddend, long nValue);
extern "C" long __cdecl _InterlockedExchange(volatile long* pTarget, long nValue);
extern "C" long __cdecl _InterlockedDecrement(volatile long* pAddend);
extern void* gVtblResource;                                            // 0x013effa8
extern void* gVtbl140944c;                                             // 0x0140944c
extern void* gVtbl14366c8;                                             // 0x014366c8
extern void* gVtbl1436678;                                             // 0x01436678
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)
void EASTL_allocator_deallocate(void* p);                             // 0x00f47380 (operator delete[])
namespace eastl {
class allocator_s008d_5340 { public:};
}
namespace eastl {
int CompareI(const char* a, const char* b, unsigned n);               // 0x00606ea0 (cdecl)
}
namespace eastl {
template <class T> inline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }
}
namespace eastl {
extern char gEmptyString[];                                           // 0x01667bac
}
namespace eastl {
inline int CharStrlen(const char* p) { return (int)strlen(p); }
}
namespace eastl {
struct string {                                                       // eastl::basic_string<char>, 16 bytes
    typedef char T;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s008d_5340 mAllocator;

    string()
    {
        mpBegin = gEmptyString;
        mpEnd = gEmptyString;
        mpCapacity = gEmptyString + 1;
    }
    ~string()
    {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            EASTL_allocator_deallocate(mpBegin);
    }
    __forceinline int comparei(const T* p) const
    {
        const T* pBegin2 = p;
        const T* pEnd2 = p + CharStrlen(p);
        const int n1 = (int)(mpEnd - mpBegin);
        const int n2 = (int)(pEnd2 - pBegin2);
        const int nMin = min_alt(n1, n2);
        const int cmp = CompareI(mpBegin, pBegin2, (unsigned)nMin);
        return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
    }
    string& insert(int position, const T* p);                       // 0x0068cd40 (thiscall)
};
}
namespace eastl {
bool operator==(const string& a, const char* b);                      // 0x00555020 (cdecl)
}
void* RBTreeIncrement(void* pNode);                                   // 0x00921580
inline void** VtableOf(void* pObject) { return *reinterpret_cast<void***>(pObject); }
extern "C" char (*g_154c464)(void* pOut, void* pArg2, void* pArg3, unsigned int nGroupId, void* pArg5, int nArg6);
namespace EA {
namespace Thread {
class Mutex_s008d_5340 {
public:
    int Lock(void* pCaller);                                          // 0x009221b0
    int Unlock();                                                     // 0x00922270
private:
    unsigned int mImpl[0x2c / 4];                                     // 0x00
};
}
}
namespace EA {
namespace IO {
class FilePath {
public:
    FilePath(const wchar_t* pPath);                                   // 0x00930f60
    wchar_t* GetExtension();                                          // 0x00930c10
    unsigned int GetDirectory(wchar_t* pDirectory, unsigned int nLength);  // 0x00930c30
private:
    wchar_t mPath[520];                                               // +0x000
};
}
}
namespace EA {
namespace IO {
class FileStream_s008d_5340 {
public:
    void Construct(const char* pPath);                                // 0x00931da0 (in-place FileStream construction)
    ~FileStream_s008d_5340();                                                    // 0x00931e70
    void* mpVtbl;                                                     // +0x00
};
}
}
namespace EA {
namespace ResourceMan {
struct Key_s008d_5340 {
    unsigned int mnTypeID;        // +0x00
    unsigned int mnGroupID;       // +0x04
    unsigned int mnInstanceID;    // +0x08
};
}
}
namespace EA {
namespace ResourceMan {
struct String16_s008d_5340 {
    const wchar_t* mpBegin;       // +0x00
    const wchar_t* mpEnd;         // +0x04
    const wchar_t* mpCapacity;    // +0x08
};
}
}
namespace EA {
namespace ResourceMan {
struct RBNode_s008d_5340 {
    RBNode_s008d_5340* mpLeft;               // +0x00
    RBNode_s008d_5340* mpRight;              // +0x04
    RBNode_s008d_5340* mpParent;             // +0x08
    unsigned int mnColor;         // +0x0c
    // payload follows
};
}
}
namespace EA {
namespace ResourceMan {
struct RBTree_s008d_5340 {
    void* mpAllocator;            // +0x00
    RBNode_s008d_5340* mpAnchor;             // +0x04 self-referential header node
    RBNode_s008d_5340* mpBegin;              // +0x08 left-most node
    RBNode_s008d_5340* mpRoot;               // +0x0c
    unsigned int mnUnknown10;     // +0x10
    unsigned int mnCount;         // +0x14
    void* mpAllocIface;           // +0x18
    unsigned int mnAllocName;     // +0x1c
};
}
}
namespace EA {
namespace ResourceMan {
inline RBNode_s008d_5340* TreeAnchor(RBTree_s008d_5340* pTree) { return reinterpret_cast<RBNode_s008d_5340*>(reinterpret_cast<char*>(pTree) + 4); }
}
}
namespace EA {
namespace ResourceMan {
inline String16_s008d_5340* NodeExtKey(RBNode_s008d_5340* pNode) { return reinterpret_cast<String16_s008d_5340*>(reinterpret_cast<char*>(pNode) + 0x10); }
}
}
namespace EA {
namespace ResourceMan {
inline unsigned int* NodeExtValue(RBNode_s008d_5340* pNode) { return reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(pNode) + 0x20); }
}
}
namespace EA {
namespace ResourceMan {
struct RecordOpenResult {
    unsigned int mStatus;         // +0x00
    int          mHandle;         // +0x04
    unsigned int mGroupId;        // +0x08
};
}
}
namespace EA {
namespace ResourceMan {
typedef bool (__cdecl* FileNameToKeyFn)(void* pKey, void* pName, void* pContext, RecordOpenResult* pResult);
}
}
namespace EA {
namespace ResourceMan {
class DatabaseDirectoryFiles_s008d_5340 {
public:
    bool FUN_008d5d80();                                              // 0x008d5d80
    void* Cast(unsigned int nInterfaceId);                            // 0x008d5da0
    void SetMutexLocked(bool bLock);                                  // 0x008d5de0
    bool OpenRecord(void* pKey, void* pName, void* pContext, RecordOpenResult* pResult);  // 0x008d5e10
    bool OpenRecordFromPath(const wchar_t* pPath, void* pResult);     // 0x008d5ea0
    bool SetLocation(unsigned int nFlags, int nType);                 // 0x008d5fe0
    int  GetTypeByExtension(const wchar_t* pExtension);               // 0x008d61e0
    const wchar_t* GetExtensionByType(unsigned int nType);            // 0x008d6290

    // ---- retail layout (0x168 bytes, two vtable pointers) ----
    void*  mpVtbl0;                    // 0x000
    void*  mpVtbl1;                    // 0x004
    int    mnRefCount;                 // 0x008
    bool   mbInitialized;              // 0x00c
    unsigned char mPad0d[3];           // 0x00d

    void*  mpAllocator;                // 0x010
    bool   mbRequireDirectoryExists;   // 0x014
    bool   mbRecursive;                // 0x015
    unsigned char mPad16[2];           // 0x016

    unsigned int mnAccessFlags;        // 0x018
    String16_s008d_5340 msDirectory;              // 0x01c
    unsigned int mDirectoryAllocator;  // 0x028

    unsigned char mExtensionPool[0x20];// 0x02c
    unsigned char mRecordPool[0x20];   // 0x04c

    RBTree_s008d_5340 mExtensionToTypeMap;        // 0x06c
    RBTree_s008d_5340 mRecordDataMap;             // 0x08c

    unsigned int mDefaultGroupId;      // 0x0ac
    void*  mpManager;                  // 0x0b0
    FileNameToKeyFn mpFileNameToKeyConverter;  // 0x0b4

    unsigned int mKnownTypesBits[0x20];// 0x0b8

    EA::Thread::Mutex_s008d_5340 mMutex;          // 0x138
};
}
}
struct ListItemNode {
    ListItemNode* mpNext;         // +0x00
    ListItemNode* mpPrev;         // +0x04
    void* mpItem;                 // +0x08
};
struct ListOwner {
    unsigned char mPad00[0x18];
    ListItemNode mList;           // +0x18 (head/anchor node)
};
struct ListItemInterface {
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();      // +0x18
};
struct ListItemStatusInterface {
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual unsigned int v10();  // +0x10
};
class BackgroundRecordLoad {
public:
    void* Initialize(void* pOwner, const EA::ResourceMan::Key_s008d_5340* pKey);  // 0x008d60d0
    void* Destroy(unsigned int nFlags);                                // 0x008d6140
    bool  AddRef();                                                    // 0x008d5f70
    bool  Release();                                                   // 0x008d5fa0

    void* mpVtbl;                          // +0x000
    volatile long mnBusy04;                // +0x004
    EA::IO::FileStream_s008d_5340 mStream;            // +0x008
    unsigned char mStreamTail[0x234 - 0x008 - sizeof(EA::IO::FileStream_s008d_5340)];
    EA::ResourceMan::Key_s008d_5340 mKey;             // +0x234
    void* mpOwner;                         // +0x240
    volatile long mnRefCount;              // +0x244
};
// ---- items of slice s008d5340 end

// ---- items of slice s008d62f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned long __cdecl strtoul(const char* pStr, char** ppEnd, int nBase);
typedef int            ptrdiff_t;
namespace EA {
namespace ResourceMan {
 struct RBNode_s008d_62f0; 
}
}
extern "C" wchar_t* __cdecl wcsncpy(wchar_t* pDst, const wchar_t* pSrc, size_t n);
void* EAAllocate(unsigned int nSize, const char* pName, int nA, int nB,
                 const char* pFile, int nLine);                          // 0x00f473a0
void  RBTreeInsert(void* pNode, void* pParent, void* pAnchor, int nSide); // 0x009216a0
void  RBTreeErase(void* pNode, void* pAnchor);                           // 0x00921880
int   BasicStringCompare(const wchar_t* a0, const wchar_t* a1,
                         const wchar_t* b0, const wchar_t* b1);          // 0x005e9260
void  WStrAllocateSelf(void* pThis, unsigned int nCapacity);             // 0x00429760
void  WStrAssign(void* pThis, const wchar_t* pBegin, const wchar_t* pEnd);// 0x00423650
void  WStrFreeSelf(void* pThis);                                         // 0x00931770
void  ListBaseDoClear(void* pList);                                      // 0x0060c4a0
void** RbTreeFind(void* pTree, void** ppOut, const void* pKey);          // 0x00a21dc0 (ret 8)
void** HoleFind(void* pTree, void** ppOut, const void* pKey);            // 0x00e5c780
void   HoleErase(void* pTree, void* pNode);                              // 0x008dae70 (HoleSet::Erase)
void   HoleInsert(void* pTree, void** ppOut, const void* pKey);          // 0x00a17a70
void   KeyVecPushBack(void* pVector, const void* pKey);                  // 0x004e3e10
void   WStrFormat(void* pString, const wchar_t* pFormat, ...);           // 0x0041e050
namespace EA {
namespace Thread {
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
}
}
namespace EA {
namespace Allocator {
class ICoreAllocator_s008d_62f0
{
public:
    virtual void  v00() = 0;
    virtual void  v04() = 0;
    virtual void* Allocate(unsigned int nSize, const char* pName, unsigned int nFlags); // vtbl +0x08
    virtual void  Free(void* p, unsigned int nSize);                                    // vtbl +0x0c
    static ICoreAllocator_s008d_62f0* GetDefaultAllocator();   // 0x00925cb0
};
}
}
namespace EA {
namespace IO {
class FileStream_s008d_62f0
{
public:
    FileStream_s008d_62f0(const wchar_t* pPath);    // 0x00931e10
    ~FileStream_s008d_62f0();                       // 0x00931e70
    bool Open(unsigned int nMode, unsigned int nAccess, unsigned int nShare, unsigned int nFlags); // 0x009318f0
    bool Close();                                   // 0x00931a70
    void AddRef();                                  // 0x009317b0
};
}
}
namespace EA {
namespace IO {
class StreamBuffer_s008d_62f0
{
public:
    StreamBuffer_s008d_62f0(unsigned int nSize, unsigned int nFlags, FileStream_s008d_62f0* pStream); // 0x0093b530
    ~StreamBuffer_s008d_62f0();                     // 0x0093b5a0
};
}
}
namespace EA {
namespace IO {
unsigned ReadLine(StreamBuffer_s008d_62f0* pBuf, char* pLine, unsigned int nSize); // 0x0093a8b0
}
}
namespace EA {
namespace IO {
unsigned ConcatenatePathComponents_s008d_62f0(wchar_t* pDst, const wchar_t* pDir, const wchar_t* pFile); // 0x0092fe60
}
}
namespace EA {
namespace IO {
int      StripPathComponent(wchar_t* pPath, int nCount);  // 0x0092fee0
}
}
namespace EA {
namespace IO {
unsigned SplitDirectory(const wchar_t* pPath, wchar_t* pOut, unsigned int a, unsigned int b); // 0x009302b0
}
}
namespace EA {
namespace IO {
namespace File {
 bool Exists(const wchar_t* pPath);   // 0x00931fa0
}
}
}
namespace EA {
namespace ResourceMan {
struct Key_s008d_62f0
{
    uint32_t mnTypeID;      // 0x00
    uint32_t mnGroupID;     // 0x04
    uint32_t mnInstanceID;  // 0x08
};
}
}
namespace EA {
namespace ResourceMan {
struct String16_s008d_62f0
{
    const wchar_t* mpBegin;     // +0x00
    const wchar_t* mpEnd;       // +0x04
    const wchar_t* mpCapacity;  // +0x08
};
}
}
namespace EA {
namespace ResourceMan {
struct DDFRecordListData_s008d_62f0
{
    String16_s008d_62f0   mName;         // +0x00
    uint32_t   mnUnknown0c;   // +0x0c
    uint32_t   mnValue10;     // +0x10
    uint32_t   mnValue14;     // +0x14
    ListAnchor mRecords;      // +0x18  list<AutoRefCount<DDFRecord>>
    DDFRecordListData_s008d_62f0* Construct(const DDFRecordListData_s008d_62f0* pSrc);  // 0x008d6970
};  // 0x20
// rbtree value_type: pair<const Key, DDFRecordListData> as retail lays it out (+0x10 aligned).
struct KeyPair_s008d_62f0
{
    Key_s008d_62f0                mKey;     // +0x00
    uint32_t                      mnPad;    // +0x0c
    DDFRecordListData_s008d_62f0  mValue;   // +0x10

    void Construct(const KeyPair_s008d_62f0& src)
    {
        mKey = src.mKey;
        mValue.Construct(&src.mValue);
    }
    // The rbtree builds the key/value pair's first three words in place before running the value copy.
    void ConstructKey(const KeyPair_s008d_62f0& src) { mKey = src.mKey; }
};
}
}
namespace EA {
namespace ResourceMan {
struct RBNode_s008d_62f0
{
    RBNode_s008d_62f0* mpLeft;    // 0x00
    RBNode_s008d_62f0* mpRight;   // 0x04
    RBNode_s008d_62f0* mpParent;  // 0x08
    uint32_t mnColor;  // 0x0c
    // payload follows
};
}
}
namespace EA {
namespace ResourceMan {
// rbtree iterator: a class (not a bare pointer) so the compiler returns it through a hidden out-parameter,
// exactly as the retail erase wrapper does.
struct RBNodeIter_s008d_62f0
{
    RBNode_s008d_62f0* mpNode;
    RBNodeIter_s008d_62f0() : mpNode(0) {}
    explicit RBNodeIter_s008d_62f0(RBNode_s008d_62f0* p) : mpNode(p) {}
    RBNodeIter_s008d_62f0(const RBNodeIter_s008d_62f0& o) : mpNode(o.mpNode) {}
    RBNodeIter_s008d_62f0& operator=(const RBNodeIter_s008d_62f0& o) { mpNode = o.mpNode; return *this; }
};
}
}
namespace EA {
namespace ResourceMan {
struct RBTree_s008d_62f0
{
    void*   mpAllocator;  // +0x00
    RBNode_s008d_62f0* mpAnchor;     // +0x04 self-referential header node
    RBNode_s008d_62f0* mpBegin;      // +0x08 left-most node
    RBNode_s008d_62f0* mpRoot;       // +0x0c
    uint32_t mnUnknown10; // +0x10
    uint32_t mnCount;     // +0x14
    void*   mpAllocIface; // +0x18 ICoreAllocator*
    uint32_t mnAllocName; // +0x1c

    void DoInsertValueImpl(RBNode_s008d_62f0** ppOutNode, RBNode_s008d_62f0* pPosition,
                           const void* pKey, bool bLeft);   // 0x008d6e20
    RBNodeIter_s008d_62f0 Erase(RBNodeIter_s008d_62f0 it);              // 0x008d6d20
    RBNodeIter_s008d_62f0 EraseIterator(RBNodeIter_s008d_62f0 it);      // 0x008d7200
};
}
}
namespace EA {
namespace ResourceMan {
class DDFRecord;
}
}
namespace EA {
namespace ResourceMan {
struct ListRefNode : ListAnchor
{
    DDFRecord*   mpRef;     // +0x08
};
}
}
namespace EA {
namespace ResourceMan {
struct ExtPair
{
    String16_s008d_62f0 mKey;       // +0x00
    uint32_t mnValue;    // +0x10
    ExtPair* Construct(const String16_s008d_62f0& key, const uint32_t& value);
};
}
}
namespace EA {
namespace ResourceMan {
inline RBNode_s008d_62f0* Anchor(RBTree_s008d_62f0* pTree) { return reinterpret_cast<RBNode_s008d_62f0*>(reinterpret_cast<uint8_t*>(pTree) + 4); }
}
}
namespace EA {
namespace ResourceMan {
inline String16_s008d_62f0* NodeExtKey_s008d_62f0(RBNode_s008d_62f0* pNode) { return reinterpret_cast<String16_s008d_62f0*>(reinterpret_cast<uint8_t*>(pNode) + 0x10); }
}
}
namespace EA {
namespace ResourceMan {
inline uint32_t* NodeExtValue_s008d_62f0(RBNode_s008d_62f0* pNode) { return reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(pNode) + 0x20); }
}
}
namespace EA {
namespace ResourceMan {
inline DDFRecordListData_s008d_62f0* NodeValue_s008d_62f0(RBNode_s008d_62f0* pNode) { return reinterpret_cast<DDFRecordListData_s008d_62f0*>(reinterpret_cast<uint8_t*>(pNode) + 0x20); }
}
}
namespace EA {
namespace ResourceMan {
inline const Key_s008d_62f0* NodeKey(RBNode_s008d_62f0* pNode) { return reinterpret_cast<const Key_s008d_62f0*>(reinterpret_cast<uint8_t*>(pNode) + 0x10); }
}
}
namespace EA {
namespace ResourceMan {
inline bool KeyLess_s008d_62f0(const Key_s008d_62f0& a, const Key_s008d_62f0& b)
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
inline void FreeString16(String16_s008d_62f0* pStr)
{
    int nBytes = static_cast<int>(reinterpret_cast<uintptr_t>(pStr->mpCapacity) -
                                  reinterpret_cast<uintptr_t>(pStr->mpBegin));
    nBytes &= 0xfffffffeu;
    if (nBytes > 2 && pStr->mpBegin != 0)
        EAOperatorDelete(const_cast<wchar_t*>(pStr->mpBegin));
}
}
}
namespace EA {
namespace ResourceMan {
inline void FreeTreeNode(RBTree_s008d_62f0* pTree, RBNode_s008d_62f0* pNode, unsigned int nSize)
{
    EA::Allocator::ICoreAllocator_s008d_62f0* pAlloc =
        reinterpret_cast<EA::Allocator::ICoreAllocator_s008d_62f0*>(pTree->mpAllocIface);
    pAlloc->Free(pNode, nSize);
}
}
}
namespace EA {
namespace ResourceMan {
inline RBNode_s008d_62f0* AllocTreeNode(RBTree_s008d_62f0* pTree, unsigned int nSize)
{
    EA::Allocator::ICoreAllocator_s008d_62f0* pAlloc =
        reinterpret_cast<EA::Allocator::ICoreAllocator_s008d_62f0*>(pTree->mpAllocIface);
    return reinterpret_cast<RBNode_s008d_62f0*>(pAlloc->Allocate(nSize, 0, pTree->mnAllocName));
}
}
}
namespace EA {
namespace ResourceMan {
void ExtTreeDoNukeSubtree(RBTree_s008d_62f0* pTree, RBNode_s008d_62f0* pNode);                 // 0x008d6be0
}
}
namespace EA {
namespace ResourceMan {
void KeyTreeDoNukeSubtree(RBTree_s008d_62f0* pTree, RBNode_s008d_62f0* pNode);                 // 0x008d6d90
}
}
namespace EA {
namespace ResourceMan {
void ListRefAppend(ListAnchor* pList, ListRefNode* pFirst, ListRefNode* pLast, bool bUnused); // 0x008d65e0
}
}
namespace EA {
namespace ResourceMan {
void ExtTreeDoInsertValueImpl(RBTree_s008d_62f0* pTree, RBNode_s008d_62f0* pPosition, const String16_s008d_62f0* pKey, bool bLeft); // 0x008d6830
}
}
namespace EA {
namespace ResourceMan {

}
}
namespace EA {
namespace ResourceMan {
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
}
}
namespace EA {
namespace ResourceMan {
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
}
}
namespace EA {
namespace ResourceMan {
class Manager_s008d_62f0;
}
}
namespace EA {
namespace ResourceMan {
class DatabaseDirectoryFiles_s008d_62f0
{
public:
    bool SetManager(bool bAttach, Manager_s008d_62f0* pManager, void* pContext);        // 0x008d62f0
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
    String16_s008d_62f0 msDirectory;              // 0x01c
    uint32_t mDirectoryAllocator;      // 0x028

    uint8_t  mExtensionPool[0x20];     // 0x02c
    uint8_t  mRecordPool[0x20];        // 0x04c

    RBTree_s008d_62f0 mExtensionToTypeMap;        // 0x06c
    RBTree_s008d_62f0 mRecordDataMap;             // 0x08c

    uint32_t mDefaultGroupId;          // 0x0ac
    Manager_s008d_62f0* mpManager;                // 0x0b0
    void*    mpFileNameToKeyConverter; // 0x0b4

    uint32_t mKnownTypesBits[0x20];    // 0x0b8

    EA::Thread::Mutex_s008d_62f0 mMutex;  // 0x138

    void SetSource(void* pArg0, Manager_s008d_62f0* pOld, void* pContext);  // vtable +0x44
};
}
}
namespace EA {
namespace ResourceMan {
struct HoleSet_s008d_62f0
{
    uint8_t mPad000[0x444];
    RBTree_s008d_62f0  mMap;        // 0x444
};
}
}

// ---- items of slice s008d62f0 end

// @ 0x008d5da0
namespace EA { namespace ResourceMan {
void* DatabaseDirectoryFiles_s008d_5340::Cast(unsigned int nInterfaceId)
{
    if (nInterfaceId == 0x0226a1de)
        return reinterpret_cast<char*>(this) - 4;
    if (nInterfaceId != 0xee3f516e)
        return 0;
    char* pBlock = reinterpret_cast<char*>(this) - 4;   // 4 (the subobject size) is the null pointer here
    return pBlock ? static_cast<void*>(this) : 0;
}
}}  // namespace EA::ResourceMan

// @ 0x008d5de0
namespace EA { namespace ResourceMan {
void DatabaseDirectoryFiles_s008d_5340::SetMutexLocked(bool bLock)
{
    if (bLock)
        mMutex.Lock(reinterpret_cast<void*>(0x01436624));
    else
        mMutex.Unlock();
}
}}  // namespace EA::ResourceMan

// @ 0x008d5e10
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles_s008d_5340::OpenRecord(void* pKey, void* pName, void* pContext, RecordOpenResult* pResult)
{
    if (mpFileNameToKeyConverter) {
        pResult->mGroupId = mDefaultGroupId;
        return mpFileNameToKeyConverter(pKey, pName, pContext, pResult);
    }
    if (!g_154c464(pResult, pContext, 0, mDefaultGroupId, 0, 0))
        return false;
    int nHandle = reinterpret_cast<int (__thiscall*)(void*, void*)>(VtableOf(this)[0x5c / 4])(this, pName);
    if (nHandle != -1)
        pResult->mHandle = nHandle;
    return true;
}
}}  // namespace EA::ResourceMan

// @ 0x008d5ea0
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles_s008d_5340::OpenRecordFromPath(const wchar_t* pPath, void* pResult)
{
    EA::IO::FilePath filePath(pPath);
    wchar_t* pExtension = filePath.GetExtension();
    wchar_t sDirectory[0x104];
    filePath.GetDirectory(sDirectory, 0x100);
    return OpenRecord(sDirectory, pExtension, const_cast<wchar_t*>(pPath), static_cast<RecordOpenResult*>(pResult));
}
}}  // namespace EA::ResourceMan

// @ 0x008d60d0
void* BackgroundRecordLoad::Initialize(void* pOwner, const EA::ResourceMan::Key_s008d_5340* pKey)
{
    mpVtbl = &gVtblResource;
    _InterlockedExchange(&mnBusy04, 0);
    mpVtbl = &gVtbl140944c;
    mStream.Construct(0);
    mpVtbl = &gVtbl14366c8;
    mStream.mpVtbl = &gVtbl1436678;
    mKey = *pKey;
    mpOwner = pOwner;
    _InterlockedExchange(&mnRefCount, 0);
    return this;
}

// @ 0x008d61a0
unsigned int __stdcall FUN_008d61a0(ListOwner* pOwner)
{
    unsigned int nFlags = 0;
    ListItemNode* pEnd = &pOwner->mList;
    for (ListItemNode* pNode = pOwner->mList.mpNext; pNode != pEnd; pNode = pNode->mpNext) {
        void* pStatus = static_cast<ListItemInterface*>(pNode->mpItem)->v18();
        nFlags |= static_cast<ListItemStatusInterface*>(pStatus)->v10();
    }
    return nFlags;
}

// @ 0x008d61e0
namespace EA { namespace ResourceMan {
int DatabaseDirectoryFiles_s008d_5340::GetTypeByExtension(const wchar_t* pExtension)
{
    mMutex.Lock(reinterpret_cast<void*>(0x01436624));
    if (*pExtension == L'.')
        ++pExtension;

    RBNode_s008d_5340* pEnd = TreeAnchor(&mExtensionToTypeMap);
    for (RBNode_s008d_5340* pNode = mExtensionToTypeMap.mpBegin; pNode != pEnd;
         pNode = static_cast<RBNode_s008d_5340*>(RBTreeIncrement(pNode))) {
        if (_wcsicmp(NodeExtKey(pNode)->mpBegin, pExtension) == 0) {
            int nType = static_cast<int>(*NodeExtValue(pNode));
            mMutex.Unlock();
            return nType;
        }
    }

    wchar_t* pEndChars;
    unsigned long nType = wcstoul(pExtension, &pEndChars, 16);
    if (*pEndChars != 0) {
        mMutex.Unlock();
        return -1;
    }
    mMutex.Unlock();
    return static_cast<int>(nType);
}
}}  // namespace EA::ResourceMan

// @ 0x008d6580
namespace EA { namespace ResourceMan {
ExtPair* ExtPair::Construct(const String16_s008d_62f0& key, const uint32_t& value)
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
}}  // namespace EA::ResourceMan

// @ 0x008d65e0
namespace EA { namespace ResourceMan {
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
}}  // namespace EA::ResourceMan

// @ 0x008d6650
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles_s008d_62f0::SetLocation(const wchar_t* pLocation)
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
}}  // namespace EA::ResourceMan

// @ 0x008d66a0
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles_s008d_62f0::RemoveRecord(DDFRecord* pRecord)
{
    bool bRemoved = false;
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    RBNode_s008d_62f0* pNode = 0;
    RbTreeFind(&mRecordDataMap, reinterpret_cast<void**>(&pNode), pRecord->GetKey());

    if (pNode != Anchor(&mRecordDataMap))
    {
        ListAnchor* pList = &NodeValue_s008d_62f0(pNode)->mRecords;
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
}}  // namespace EA::ResourceMan

// @ 0x008d6770
namespace EA { namespace ResourceMan {
void DatabaseDirectoryFiles_s008d_62f0::CloseOpenRecords()
{
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    RBNode_s008d_62f0* pEnd = Anchor(&mRecordDataMap);
    for (RBNode_s008d_62f0* pNode = mRecordDataMap.mpBegin; pNode != pEnd; pNode = reinterpret_cast<RBNode_s008d_62f0*>(RBTreeIncrement(pNode)))
    {
        ListAnchor* pList = &NodeValue_s008d_62f0(pNode)->mRecords;
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
}}  // namespace EA::ResourceMan

// @ 0x008d6830
namespace EA { namespace ResourceMan {
void ExtTreeDoInsertValueImpl(RBTree_s008d_62f0* pTree, RBNode_s008d_62f0* pPosition, const String16_s008d_62f0* pKey, bool bLeft)
{
    bool bInsertLeft = false;
    if (!bLeft && pPosition != Anchor(pTree))
    {
        const String16_s008d_62f0* pPosKey = NodeExtKey_s008d_62f0(pPosition);
        if (BasicStringCompare(pKey->mpBegin, pKey->mpEnd, pPosKey->mpBegin, pPosKey->mpEnd) >= 0)
            bInsertLeft = true;
    }

    RBNode_s008d_62f0* pNode = AllocTreeNode(pTree, 0x24);
    if (pNode != 0)
        reinterpret_cast<ExtPair*>(reinterpret_cast<uint8_t*>(pNode) + 0x10)->Construct(*pKey, *NodeExtValue_s008d_62f0(pNode));

    RBTreeInsert(pNode, pPosition, Anchor(pTree), bInsertLeft ? 1 : 0);
    ++pTree->mnCount;
}
}}  // namespace EA::ResourceMan

// @ 0x008d68c0
namespace EA { namespace ResourceMan {
bool HoleSetInsertRemove(HoleSet_s008d_62f0* pThis, void* pEntry, bool bAdd)
{
    uint32_t nCountBefore = pThis->mMap.mnCount;

    if (pEntry != 0)
    {
        RBNode_s008d_62f0* pNode = 0;
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
}}  // namespace EA::ResourceMan

// @ 0x008d6970
namespace EA { namespace ResourceMan {
DDFRecordListData_s008d_62f0* DDFRecordListData_s008d_62f0::Construct(const DDFRecordListData_s008d_62f0* pSrc)
{
    mName.mpBegin    = 0;
    mName.mpEnd      = 0;
    mName.mpCapacity = 0;

    ptrdiff_t nChars = pSrc->mName.mpEnd - pSrc->mName.mpBegin;
    WStrAllocateSelf(&mName, static_cast<unsigned int>(nChars + 1));

    wchar_t* pDst = const_cast<wchar_t*>(mName.mpBegin);
    memcpy(pDst, pSrc->mName.mpBegin, static_cast<size_t>(nChars) * sizeof(wchar_t));
    pDst[nChars] = 0;
    mName.mpEnd = pDst + nChars;

    mnValue10 = pSrc->mnValue10;
    mnValue14 = pSrc->mnValue14;

    ListAnchor* pList = &mRecords;
    pList->mpNext = pList;
    pList->mpPrev = pList;
    ListRefAppend(pList,
                  reinterpret_cast<ListRefNode*>(const_cast<void*>(pSrc->mRecords.mpNext)),
                  reinterpret_cast<ListRefNode*>(const_cast<ListAnchor*>(&pSrc->mRecords)),
                  false);

    return this;
}
}}  // namespace EA::ResourceMan

// @ 0x008d6b20
namespace EA { namespace ResourceMan {
int DatabaseDirectoryFiles_s008d_62f0::GetKeyList(void* pKeyVector, void* pFilter)
{
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    int nCount = 0;
    RBNode_s008d_62f0* pEnd = Anchor(&mRecordDataMap);
    for (RBNode_s008d_62f0* pNode = mRecordDataMap.mpBegin; pNode != pEnd; pNode = reinterpret_cast<RBNode_s008d_62f0*>(RBTreeIncrement(pNode)))
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
}}  // namespace EA::ResourceMan

// @ 0x008d6be0
namespace EA { namespace ResourceMan {
void ExtTreeDoNukeSubtree(RBTree_s008d_62f0* pTree, RBNode_s008d_62f0* pNode)
{
    while (pNode != 0)
    {
        ExtTreeDoNukeSubtree(pTree, pNode->mpLeft);
        RBNode_s008d_62f0* pRight = pNode->mpRight;
        FreeString16(NodeExtKey_s008d_62f0(pNode));
        FreeTreeNode(pTree, pNode, 0x24);
        pNode = pRight;
    }
}
}}  // namespace EA::ResourceMan

// @ 0x008d6d20
namespace EA { namespace ResourceMan {
RBNodeIter_s008d_62f0 RBTree_s008d_62f0::Erase(RBNodeIter_s008d_62f0 it)
{
    RBNode_s008d_62f0* pNode = it.mpNode;
    --mnCount;
    it.mpNode = reinterpret_cast<RBNode_s008d_62f0*>(RBTreeIncrement(pNode));
    RBTreeErase(pNode, Anchor(this));
    NodeValue_s008d_62f0(pNode)->mRecords.DoClear();
    FreeString16(&NodeValue_s008d_62f0(pNode)->mName);
    FreeTreeNode(this, pNode, 0x48);
    return it;
}
}}  // namespace EA::ResourceMan

// @ 0x008d6d90
namespace EA { namespace ResourceMan {
void KeyTreeDoNukeSubtree(RBTree_s008d_62f0* pTree, RBNode_s008d_62f0* pNode)
{
    while (pNode != 0)
    {
        KeyTreeDoNukeSubtree(pTree, pNode->mpLeft);
        RBNode_s008d_62f0* pRight = pNode->mpRight;

        DDFRecordListData_s008d_62f0* pValue = NodeValue_s008d_62f0(pNode);
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
}}  // namespace EA::ResourceMan

// @ 0x008d6e20
// Reconstructed from the retail listing.  The shape is complete; the remaining residue is cl 15's choice of
// esi/edi for this/new-node (retail: esi=this, edi=node) and the scheduling of the insertion-side store.
namespace EA { namespace ResourceMan {
void RBTree_s008d_62f0::DoInsertValueImpl(RBNode_s008d_62f0** ppOutNode, RBNode_s008d_62f0* pPosition,
                                          const void* pKey, bool bLeft)
{
    int nSide;
    if (!bLeft && pPosition != Anchor(this))
    {
        const KeyPair_s008d_62f0* pNew = reinterpret_cast<const KeyPair_s008d_62f0*>(pKey);
        nSide = 1;
        if (KeyLess_s008d_62f0(pNew->mKey, *NodeKey(pPosition)))
            nSide = 0;
    }
    else
    {
        nSide = 0;
    }

    RBNode_s008d_62f0* pNode = AllocTreeNode(this, 0x48);
    if (pNode != 0)
        reinterpret_cast<KeyPair_s008d_62f0*>(reinterpret_cast<uint8_t*>(pNode) + 0x10)->Construct(
            *reinterpret_cast<const KeyPair_s008d_62f0*>(pKey));

    RBTreeInsert(pNode, pPosition, Anchor(this), nSide);
    ++mnCount;
    *ppOutNode = pNode;
}
}}  // namespace EA::ResourceMan

// @ 0x008d6ed0
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles_s008d_62f0::ReadExtensionToTypeMapFile()
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
        EA::IO::ConcatenatePathComponents_s008d_62f0(path, directory, L"DDFMap.txt");
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
                            RBNode_s008d_62f0* pAnchor = Anchor(&mExtensionToTypeMap);
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

                            String16_s008d_62f0 name;
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
}}  // namespace EA::ResourceMan

// @ 0x008d7200
namespace EA { namespace ResourceMan {
RBNodeIter_s008d_62f0 RBTree_s008d_62f0::EraseIterator(RBNodeIter_s008d_62f0 it)
{
    return Erase(it);
}
}}  // namespace EA::ResourceMan

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
