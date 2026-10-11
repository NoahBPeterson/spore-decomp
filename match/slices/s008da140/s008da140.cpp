// Slice s008da140 (0x8da140..0x8db000) - Resource::DatabasePackedFile packing helpers.
//
// Spore-specific code contiguous with slice s008d81d0. Layout follows the retail DBFP object
// (see s008d81d0.cpp). The odd anonymous helpers (sort / heap / rbtree) are EASTL template
// instantiations emitted without PDB names; they are reproduced here verbatim as free functions.
//
// Functions (VA, name):
//   008da140  DatabasePackedFile::CompactDatabaseInternal
//   008da3d0  DatabasePackedFile::OpenRecord
//   008da750  DatabasePackedFile::ReadIndexRecord
//   008da8b0  DatabasePackedFile::CompactDatabase
//   008da920  DatabasePackedFile::DeleteRecordWrite
//   008daba0  DatabasePackedFile::Flush
//   008dac90  Hashtable::DoFreeNodes
//   008dace0  FUN_008dace0 (insertion sort)
//   008dad30  FUN_008dad30 (unguarded insertion sort)
//   008dad80  FUN_008dad80 (promote heap)
//   008dadd0  FUN_008dadd0 (adjust heap)
//   008dae40  HoleSet::GetTotalSize
//   008dae70  HoleSet::Erase
//   008daf40  PFIndexModifiable::GetDataEnd
//   008dafa0  PFIndexModifiable::GetTotalDiskSize

#include "types.h"

// ---------------------------------------------------------------------------
// external callees / data (direct calls only; targets are masked as REL32)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl operator_delete__(void* p);                              // 0xf47380
extern "C" void* __cdecl RBTreeIncrement(void* node);                             // 0x921580
extern "C" void* __cdecl RBTreeErase(void* node, void* header);                   // 0x921880
extern "C" void* __cdecl memset_pf(void* dst, int val, unsigned n);               // 0x11e073e
extern "C" void* __cdecl ICoreAllocator_Alloc_Named(unsigned size, void* alloc, const char* name); // 0x925fe0
extern "C" int   __cdecl FindEmbeddedPackageHeader(const wchar_t* path);          // 0x8dd510
extern const int kTimeoutNone[];                                                  // 0x1436788

// ---------------------------------------------------------------------------
// shared small types
// ---------------------------------------------------------------------------
// Node whose sort key lives at +0xc (EASTL sort/heap instantiations).
struct SortNode { char d[0xc]; unsigned key; };

// hash-table node used by the modifiable index (key/value pair lives inline).
struct HashNode {
    char      d0[0xc];     // +0x00
    int       mnPosition;  // +0x0c
    int       mnSize;      // +0x10
    char      d1[8];       // +0x14
    HashNode* mpNext;      // +0x1c
};

struct IAlloc {
    virtual void a0();
    virtual void a1();
    virtual void* Alloc(unsigned size, const char* name, unsigned flags);
    virtual void Free(void* p, unsigned size);
};

// allocator vtable as used by the BmpGlyphMetrics hashtable (free at +0xc).
struct HashAlloc {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void Free(void* p, unsigned n);   // +0x0c
    virtual void a4();
};

struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
};
struct AutoRef { void* p; };                 // AutoRefCount<IStream>
struct FileStream { void* vt; char d[0x224]; };
struct PFHeaderField { uint32_t f[10]; };

struct Mutex {
    char d[0x30];
    int Lock(const void* timeout);   // 0x9221b0
    int Unlock();                    // 0x922270
};

struct IStream {
    virtual void s0();
    virtual int  AddRef();                           // +0x04
    virtual int  Release();                          // +0x08
    virtual void s3();
    virtual int  GetAccessFlags();                   // +0x10
    virtual int  GetState();                         // +0x14
    virtual bool Close();                            // +0x18
    virtual int  GetSize();                          // +0x1c
    virtual void SetSize(int n);                     // +0x20
    virtual void s9();                               // +0x24
    virtual bool SetPosition(int pos, int origin);   // +0x28
    virtual void s11();                              // +0x2c
    virtual int  Read(void* buf, int size);          // +0x30
    virtual bool Flush();                            // +0x34
    virtual bool ReadRaw(void* buf, int size);       // +0x38
};

struct Index {
    virtual void i0();                               // +0x00
    virtual bool IsModifiable();                     // +0x04
    virtual void i2();                               // +0x08
    virtual int  GetSize();                          // +0x0c
    virtual int  Op10();                             // +0x10
    virtual void i5();                               // +0x14
    virtual void i6();                               // +0x18
    virtual int  GetKeyList(int a, int b);           // +0x1c
    virtual int  GetKeyListSortedByPosition(int a);  // +0x20
    virtual void i9();                               // +0x24
    virtual void* Find(const void* k);               // +0x28
    virtual void Op2C(void* a, void* b);             // +0x2c
    virtual bool GetEntry(const void* k, void* e);   // +0x30
    virtual void Op34(void* buf, int len, int size, int flag); // +0x34
    virtual bool Serialize(void** pp, int* pl, int size, int flag); // +0x38
    virtual void Op3C();                             // +0x3c
    virtual bool VerifyRange(int a, int b);          // +0x40
};

// --- fixed-key multimap anchor (mOpenRecordMultiMap @ +0x2e8) ---
struct RbNode;
struct RbAnchor { RbNode* right; RbNode* left; RbNode* parent; int color; };
struct RbNode { RbNode* right; RbNode* left; RbNode* parent; int color; char key[0xc]; void* value; };
struct RecMap {
    uint32_t cmp;
    RbAnchor mAnchor;
    int mnSize;
    IAlloc* mpAlloc;
    int mnFlags;
    RbNode* Anchor() { return (RbNode*)&mAnchor; }
    RbNode** find(RbNode** out, const void* k);   // 0xa21dc0
    RecMap() {}
};

struct HoleSet {
    int mField0;                       // +0
    char d[0x1c];                      // total 0x20
    int GetTotalSize();                // 0x8dae40
    void Erase(void** out, void* node); // 0x8dae70
    void FUN_008dc120(HoleSet* other); // 0x8dc120
};
struct HoleTable {
    int mExtent;                       // +0x334
    float mRatio;                      // +0x338
    HoleSet mHoles;                    // +0x33c
};

struct DatabasePackedFile {            // 0x384
    void* volatile vt0;                // +0x00
    void* volatile vt4;                // +0x04
    volatile long mRefCount;           // +0x08
    bool mbInitialized;                // +0x0c
    IAlloc* mpAllocator;               // +0x10
    int mnAccessFlags;                 // +0x14
    int mnAutoOpenAccessFlags;         // +0x18
    bool mbEnableReadOnCorruptFiles;   // +0x1c
    bool mbEnableWriteOnCorruptFiles;  // +0x1d
    WString mPath;                     // +0x20
    FileStream mFile;                  // +0x30
    long mnFileStartingOffset;         // +0x258
    long mpStream;                     // +0x25c (IStream*)
    AutoRef mpMemoryLocation;          // +0x260
    char* mpMemoryBase;                // +0x264
    unsigned mnMemorySize;             // +0x268
    unsigned mnMemoryPosition;         // +0x26c
    Mutex mMutex;                      // +0x270
    Mutex mFileMutex;                  // +0x2a0
    Index* mpIndex;                    // +0x2d0
    bool mbIndexHasChanged;            // +0x2d4
    unsigned mnUserVersionMajor;       // +0x2d8
    unsigned mnUserVersionMinor;       // +0x2dc
    bool mbEnableCompression;          // +0x2e0
    float mfMinRatioToUseCompression;  // +0x2e4
    RecMap mMap;                       // +0x2e8
    PFHeaderField mHeaderBlock;        // +0x308
    bool mbFlag330;                    // +0x330
    HoleTable mActive;                 // +0x334
    HoleSet mHoleB;                    // +0x35c
    bool mbHolesHaveChanged;           // +0x37c
    bool mbBusyCompacting;             // +0x37d
    uint32_t mpManager;                // +0x380

    // this slice
    bool CompactDatabaseInternal();
    bool CompactDatabase();
    bool ReadIndexRecord();
    bool OpenRecord(void* pKey, unsigned access, unsigned reqFlags, unsigned mode, void* arg5, void* pOutRecord);
    char FUN_008da920(void* param2);
    bool Flush();

    // contiguous helpers
    bool ReadBytes(void* dst, int size);              // 0x8d88d0
    bool Verify();                                    // 0x8d87c0
    bool WriteEmpty1(int a, int b, int c);            // vf
};

typedef char chk_sz[(sizeof(DatabasePackedFile) == 0x384) ? 1 : -1];

// external helpers used by the complex functions (declared only)
extern bool FUN_008d84a0(void* pOut, int size);       // 0x8d84a0
extern bool FUN_008d84d0(int pos, int size, bool flag); // 0x8d84d0
extern void FUN_00686430(void* vecbuf, int size, void* flag); // 0x686430

// ===========================================================================
// 0x8da8b0  DatabasePackedFile::CompactDatabase
// ===========================================================================
// @ 0x008da8b0
bool DatabasePackedFile::CompactDatabase()
{
    mMutex.Lock(kTimeoutNone);
    mFileMutex.Lock(kTimeoutNone);
    bool bResult = false;
    if (mnAccessFlags != 0 && !mbBusyCompacting) {
        mbBusyCompacting = true;
        bResult = CompactDatabaseInternal();
        mbBusyCompacting = false;
    }
    mFileMutex.Unlock();
    mMutex.Unlock();
    return bResult;
}

// ===========================================================================
// 0x8dae40  HoleSet::GetTotalSize
// ===========================================================================
// @ 0x008dae40
int HoleSet::GetTotalSize()
{
    int nSum = 0;
    for (void* p = *(void**)((char*)this + 0xc); p != (char*)this + 8; p = RBTreeIncrement(p))
        nSum += *(int*)((char*)p + 0x14);
    return nSum;
}

// ===========================================================================
// 0x8dae70  HoleSet::Erase
// ===========================================================================
// @ 0x008dae70
void HoleSet::Erase(void** ppOut, void* pNode)
{
    --*(int*)((char*)this + 0x14);
    void* pNext = RBTreeIncrement(pNode);
    RBTreeErase(pNode, (char*)this + 4);
    operator_delete__(pNode);
    *ppOut = pNext;
}

// ===========================================================================
// 0x8daf40  PFIndexModifiable::GetDataEnd
// ===========================================================================
struct PFIndexModifiable {
    char d0[4];                 // +0x00
    void* mpAllocator;          // +0x04
    char d1[0x24];              // +0x08
    HashNode** mpBucketArray;   // +0x2c
    int mnBucketCount;          // +0x30
    int GetDataEnd();
    int GetTotalDiskSize();
};

// @ 0x008daf40
int PFIndexModifiable::GetDataEnd()
{
    HashNode** pBucket = mpBucketArray;
    HashNode* pNode = *pBucket;
    unsigned nEnd = 0;
    if (pNode == 0) {
        ++pBucket;
        while (*pBucket == 0)
            ++pBucket;
        pNode = *pBucket;
    }
    HashNode* pLast = mpBucketArray[mnBucketCount];
    while (pNode != pLast) {
        unsigned n = (unsigned)pNode->mnSize + (unsigned)pNode->mnPosition;
        pNode = pNode->mpNext;
        nEnd = nEnd < n ? n : nEnd;
        while (pNode == 0) {
            ++pBucket;
            pNode = *pBucket;
        }
    }
    return (int)nEnd;
}

// ===========================================================================
// 0x8dafa0  PFIndexModifiable::GetTotalDiskSize
// ===========================================================================
// @ 0x008dafa0
int PFIndexModifiable::GetTotalDiskSize()
{
    HashNode** pBucket = mpBucketArray;
    HashNode* pNode = *pBucket;
    int nTotal = 0;
    if (pNode == 0) {
        ++pBucket;
        while (*pBucket == 0)
            ++pBucket;
        pNode = *pBucket;
    }
    HashNode* pLast = mpBucketArray[mnBucketCount];
    while (pNode != pLast) {
        nTotal += pNode->mnSize;
        pNode = pNode->mpNext;
        while (pNode == 0) {
            ++pBucket;
            pNode = *pBucket;
        }
    }
    return nTotal;
}

// ===========================================================================
// 0x8dac90  Hashtable::DoFreeNodes
// ===========================================================================
struct BmpGlyphHash {
    char d[0x1c];              // +0x00
    HashAlloc* mpAlloc;        // +0x1c
    void DoFreeNodes(void** pBuckets, unsigned n);
};

// @ 0x008dac90
void BmpGlyphHash::DoFreeNodes(void** pBuckets, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        HashNode* pNode = (HashNode*)pBuckets[i];
        while (pNode) {
            HashNode* p = pNode;
            pNode = p->mpNext;
            mpAlloc->Free(p, 0x20);
        }
        pBuckets[i] = 0;
    }
}

// ===========================================================================
// 0x8dace0  insertion sort (value at +0xc)
// ===========================================================================
// @ 0x008dace0
void FUN_008dace0(SortNode** p1, SortNode** p2)
{
    SortNode** i = p1;
    if (p1 != p2) {
        while (i = i + 1, i != p2) {
            SortNode* key = *i;
            SortNode** j = i;
            while (j != p1 && key->key < j[-1]->key) {
                *j = j[-1];
                j = j - 1;
            }
            *j = key;
        }
    }
}

// ===========================================================================
// 0x8dad30  unguarded insertion sort (guarded by element before p1)
// ===========================================================================
// @ 0x008dad30
void FUN_008dad30(SortNode** p1, SortNode** p2)
{
    for (; p1 != p2; p1 = p1 + 1) {
        SortNode** j = p1;
        SortNode* prev = p1[-1];
        SortNode** k = p1 - 1;
        SortNode* key = *p1;
        if (key->key < prev->key) {
            do {
                *j = prev;
                j = k;
                prev = j[-1];
                k = j - 1;
            } while (key->key < prev->key);
        }
        *j = key;
    }
}

// ===========================================================================
// 0x8dad80  promote heap (sift up)
// ===========================================================================
// @ 0x008dad80
void FUN_008dad80(SortNode** array, int topIndex, int holeIndex, SortNode* value, int extra)
{
    int parent = (holeIndex - 1) >> 1;
    if (holeIndex <= topIndex) {
        array[holeIndex] = value;
        return;
    }
    do {
        SortNode* p = array[parent];
        if (p->key >= value->key)
            break;
        array[holeIndex] = p;
        holeIndex = parent;
        parent = (parent - 1) >> 1;
    } while (holeIndex > topIndex);
    array[holeIndex] = value;
    (void)extra;
}

// ===========================================================================
// 0x8dadd0  adjust heap (sift down, then promote)
// ===========================================================================
// @ 0x008dadd0
void FUN_008dadd0(SortNode** array, int topIndex, int length, int holeIndex, SortNode* value, int extra)
{
    int child = holeIndex * 2 + 2;
    if (child < length) {
        do {
            SortNode* right = array[child];
            if (right->key < array[child - 1]->key)
                --child;
            array[holeIndex] = array[child];
            holeIndex = child;
            child = child * 2 + 2;
        } while (child < length);
    }
    if (child == length) {
        array[holeIndex] = array[child - 1];
        holeIndex = child - 1;
    }
    FUN_008dad80(array, topIndex, holeIndex, value, extra);
}

// ===========================================================================
// 0x8daba0  DatabasePackedFile::Flush
// ===========================================================================
typedef bool (__thiscall *TFb0)(void*);
typedef void (__thiscall *TFv0)(void*);
typedef int  (__thiscall *TFi1)(void*, int);

// @ 0x008daba0
bool DatabasePackedFile::Flush()
{
    bool bResult = true;
    mMutex.Lock(kTimeoutNone);
    mFileMutex.Lock(kTimeoutNone);
    if (mnAccessFlags != 0 && (mnAccessFlags & 2) != 0
        && (mbIndexHasChanged || mbHolesHaveChanged || mbFlag330)) {
        if ((mActive.mExtent & 1) != 0 && Verify())
            CompactDatabase();
        bResult = ((TFb0)(*(void***)this)[0x7c / 4])(this);
        if (bResult) {
            bResult = ((TFb0)(*(void***)this)[0x70 / 4])(this);
            if (bResult) {
                if (mpMemoryBase != 0) {
                    bResult = true;
                } else {
                    bResult = ((TFb0)(*(void***)mpMemoryLocation.p)[0x34 / 4])(mpMemoryLocation.p);
                    if (!bResult)
                        goto done;
                }
                mActive.mHoles.FUN_008dc120(&mHoleB);
                ((TFv0)(*(void***)mpIndex)[0x3c / 4])(mpIndex);
            }
        }
    }
done:
    mFileMutex.Unlock();
    mMutex.Unlock();
    return bResult;
}

// ---------------------------------------------------------------------------
// helpers shared by the record-level functions below
// ---------------------------------------------------------------------------
struct VecBuf {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    void* Init(int size, void* pFlag);   // 0x686430
};

typedef int   (__thiscall *TFi0)(void*);
typedef void* (__thiscall *TFp1i)(void*, int);
typedef void* (__thiscall *TFp1p)(void*, void*);
typedef bool  (__thiscall *TFb2i)(void*, unsigned, int);
typedef bool  (__thiscall *TFb4i)(void*, void*, unsigned, unsigned, int);
typedef bool  (__thiscall *TFb3i)(void*, int, int, int);
typedef void  (__thiscall *TFv1i)(void*, int);

// external helpers of the complex functions (addresses masked; semantics approximated)
extern "C" void* __cdecl ZoneObject_operator_new(unsigned size, void* alloc, const char* name);
extern "C" void* __cdecl DatabasePackedFile_ctor(void* mem, int a, void* alloc);
extern "C" void  __cdecl FUN_00930f60();
extern "C" void  __cdecl FUN_00572590();
extern "C" char  __cdecl FUN_00932580(void* buf, void* a);
extern "C" char  __cdecl FUN_00931ff0(void* buf, void* path, int a);
extern "C" char  __cdecl IO_File_Exists(void* buf);
extern "C" void  __cdecl IO_File_Remove();
extern "C" int   __cdecl CopyDatabaseRecords(void* db, void* src, int a, int b);
extern "C" char  __cdecl ReadRecordRaw(void* p0, void* p1, void* p2, void* p3);
typedef void  (__thiscall *TFv1p)(void*, void*);

// ===========================================================================
// 0x8da750  DatabasePackedFile::ReadIndexRecord
// ===========================================================================
// @ 0x008da750
bool DatabasePackedFile::ReadIndexRecord()
{
    char cFlag = 0;
    if (mHeaderBlock.f[8] == 0) {
        if (mpIndex == 0)
            mpIndex = (Index*)((TFp1i)(*(void***)this)[0x84 / 4])(this, 3);
        if (((TFi0)(*(void***)mpIndex)[0x0c / 4])(mpIndex) == 0)
            ((TFv0)(*(void***)this)[0x90 / 4])(this);
        return true;
    }
    unsigned nPos = (unsigned)mpStream + mHeaderBlock.f[7];
    if (mpMemoryBase == 0) {
        if (!((TFb2i)(*(void***)mpMemoryLocation.p)[0x28 / 4])(mpMemoryLocation.p, nPos, 0))
            return false;
    } else {
        if (mnMemorySize <= nPos)
            return false;
        mnMemoryPosition = nPos;
    }
    VecBuf buf;
    buf.Init((int)mHeaderBlock.f[9], &cFlag);
    void* pBuf = buf.mpBegin;
    bool bResult = false;
    bool bCreated = false;
    if (!ReadBytes(pBuf, (int)mHeaderBlock.f[9]))
        goto cleanup;
    if (mpIndex == 0)
        mpIndex = (Index*)((TFp1i)(*(void***)this)[0x84 / 4])(this, 3);
    if (mpIndex != 0)
        bCreated = ((TFb4i)(*(void***)mpIndex)[0x34 / 4])(mpIndex, pBuf, mHeaderBlock.f[9], mHeaderBlock.f[8], 1);
    if (!((TFb0)(*(void***)this)[0x80 / 4])(this) && !mbEnableReadOnCorruptFiles) {
        bResult = false;
    } else if (bCreated) {
        ((TFv0)(*(void***)this)[0x90 / 4])(this);
        mbIndexHasChanged = false;
        bResult = true;
    }
cleanup:
    if (pBuf != 0 && ((int*)pBuf)[-1] != 0)
        operator_delete__(pBuf);
    return bResult;
}

// ===========================================================================
// 0x8da3d0  DatabasePackedFile::OpenRecord
// ===========================================================================
// Reconstructed from the retail disassembly. The Ghidra calling convention for this body is
// garbled; the real prototype is (key, access, reqFlags, mode, arg5, outRecordInfo), ret 0x18.
// @ 0x008da3d0
bool DatabasePackedFile::OpenRecord(void* pKey, unsigned access, unsigned reqFlags, unsigned mode,
                                    void* arg5, void* pOutRecord)
{
    void* pRecord = 0;
    if ((access & 3) == 0)
        goto done;
    {
        bool bLocked = false;
        if (mnAccessFlags == 0) {
            mMutex.Lock(kTimeoutNone);
            bLocked = true;
        }
        if (mnAccessFlags == 0)
            goto unlock_false;
        if ((mnAccessFlags & 2) != 0 && !bLocked) {
            bLocked = true;
            mMutex.Lock(kTimeoutNone);
        }
        {
            void* pInfo = ((TFp1p)(*(void***)mpIndex)[0x28 / 4])(mpIndex, pKey);
            bool bFound = pInfo != 0;
            if (bFound && pOutRecord != 0) {
                ((unsigned*)pOutRecord)[0] = *(unsigned*)((char*)pInfo + 0x00);
                ((unsigned*)pOutRecord)[1] = *(unsigned*)((char*)pInfo + 0x04);
                ((unsigned*)pOutRecord)[2] = *(unsigned*)((char*)pInfo + 0x08);
                ((unsigned*)pOutRecord)[3] = *(unsigned short*)((char*)pInfo + 0x0c);
            }
            if (reqFlags == 0) {
                if (bLocked)
                    mMutex.Unlock();
                return bFound;
            }
            unsigned want = mode;
            if (mode == 6)
                want = (((access & 2) != 0) ? 1u : 0u) + 3;
            bool bReadOnly;
            if (bFound) {
                bReadOnly = (want == 1);
            } else {
                if (want == 3)
                    goto unlock_false;
                bReadOnly = (want == 5);
            }
            if (bReadOnly || ((mnAccessFlags & access) != access))
                goto unlock_false;
            if (want == 2 || want == 5)
                reqFlags |= 0x100;
            if (bFound) {
                if ((access & 2) == 0 || reqFlags == 0) {
                    unsigned recFlags = *(unsigned*)((char*)pInfo + 0x08);
                    if (recFlags != 0 && arg5 != 0 && ((unsigned)arg5 & 1) == 0)
                        goto unlock_false;
                }
                if ((access & 2) == 0) {
                    if ((mnAccessFlags & 2) == 0)
                        pRecord = ((TFp1p)(*(void***)this)[0x2c / 4])(this, pInfo);
                    else
                        pRecord = ((TFp1p)(*(void***)this)[0x2c / 4])(this, pInfo);
                    goto have_record;
                }
            } else {
                pRecord = ((TFp1p)(*(void***)this)[0x2c / 4])(this, pInfo);
                if (pRecord != 0) {
                    ((TFv0)(*(void***)this)[0x30 / 4])(this);
                    ((TFv0)(*(void***)this)[0x34 / 4])(this);
                }
                goto have_record;
            }
        }
unlock_false:
        if (bLocked)
            mMutex.Unlock();
        return false;
    }
have_record:
    if (pRecord != 0)
        ((TFv0)(*(void***)pRecord)[0x04 / 4])(pRecord);
done:
    if (pOutRecord != 0)
        *(void**)pOutRecord = pRecord;
    return pRecord != 0;
}

// ===========================================================================
// 0x8da920  DatabasePackedFile helper (delete/replace record)
// ===========================================================================
// @ 0x008da920
char DatabasePackedFile::FUN_008da920(void* param2)
{
    mMutex.Lock(kTimeoutNone);
    if ((mnAccessFlags & 2) == 0 || mnAccessFlags == 0) {
        mMutex.Unlock();
        return 0;
    }
    void* pFound = ((TFp1p)(*(void***)mpIndex)[0x28 / 4])(mpIndex, param2);
    if (pFound == 0) {
        mMutex.Unlock();
        return 0;
    }
    char cResult = 0;
    void* pRec = ((TFp1p)(*(void***)this)[0x60 / 4])(this, param2);
    bool bAlloc = false;
    if (pRec != 0)
        bAlloc = true;
    mMutex.Unlock();
    if (bAlloc) {
        char cWritten = ReadRecordRaw(this, pRec, 0, 0);
        (void)cWritten;
    }
    mMutex.Lock(kTimeoutNone);
    mMutex.Unlock();
    return cResult;
}

// ===========================================================================
// 0x8da140  DatabasePackedFile::CompactDatabaseInternal
// ===========================================================================
// @ 0x008da140
bool DatabasePackedFile::CompactDatabaseInternal()
{
    mActive.mHoles.FUN_008dc120(&mHoleB);
    if ((mnAccessFlags & 2) == 0)
        return false;
    if (mMap.mnSize != 0)
        return false;
    if (((TFb0)(*(void***)mpIndex)[0x08 / 4])(mpIndex)) {
        if (mnMemorySize == 0)
            ((TFv0)(*(void***)mpMemoryLocation.p)[0x20 / 4])(mpMemoryLocation.p);
        mHeaderBlock.f[8] = 0;
        mHeaderBlock.f[7] = 0;
        mHeaderBlock.f[9] = 0;
        mbFlag330 = true;
        ((TFv0)(*(void***)this)[0x90 / 4])(this);
        ((TFv0)(*(void***)this)[0x24 / 4])(this);
        return true;
    }
    char cResult = 0;
    char szPath[520];
    void* pFilePath = 0;
    FUN_00930f60();
    (void)pFilePath;
    FUN_00572590();
    if (FUN_00932580(szPath, 0) != 0) {
        void* pNew = ZoneObject_operator_new(0x388, mpAllocator, "Resource/DatabasePackedFile");
        void* pDb = 0;
        if (pNew != 0)
            pDb = DatabasePackedFile_ctor(pNew, 0, mpAllocator);
        bool bOk = false;
        if (pDb != 0 && ((TFb0)(*(void***)pDb)[0x04 / 4])(pDb)) {
            ((TFv1p)(*(void***)pDb)[0x2c / 4])(pDb, szPath);
            if (((TFb3i)(*(void***)pDb)[0x18 / 4])(pDb, 3, 6, 0)) {
                *(int*)((char*)pDb + 0x334) = 2;
                ((TFv1i)(*(void***)pDb)[0x14 / 4])(pDb, 1);
                FUN_008d84d0(0, 0, true);
                ((TFv1i)(*(void***)pDb)[0x14 / 4])(pDb, 0);
                bOk = CopyDatabaseRecords(pDb, this, 0, 0) != -1;
                ((TFv0)(*(void***)pDb)[0x1c / 4])(pDb);
            }
            ((TFv0)(*(void***)pDb)[0x08 / 4])(pDb);
        }
        if (pDb != 0)
            ((TFv1i)(*(void***)pDb)[0x00 / 4])(pDb, 1);
        if (bOk) {
            unsigned nExtent = (unsigned)mActive.mExtent;
            int nAccess = mnAccessFlags;
            mActive.mExtent = (int)(nExtent & 0xfffffffe);
            if (((TFb0)(*(void***)this)[0x1c / 4])(this)) {
                if (FUN_00931ff0(szPath, mPath.mpBegin, 1) == 0) {
                    ((TFb3i)(*(void***)this)[0x18 / 4])(this, nAccess, 6, 0);
                    cResult = 0;
                } else {
                    cResult = (char)((TFb3i)(*(void***)this)[0x18 / 4])(this, nAccess, 6, 0);
                }
            }
            mActive.mExtent = (int)nExtent;
        }
        if (IO_File_Exists(szPath) != 0)
            IO_File_Remove();
    }
    return cResult != 0;
}
