// src/game/UTFSpore_Win32/DatabasePackedFile.cpp -- migrated from slice(s) s008daff0, s008da140, s008d91e0, s008d7220, s006bb1c0, s008d81d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DatabasePackedFile.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/IO/FileStream.h"
#include "EA/ResourceMan/PFHoleTable.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/IO/IStream.h"
#include "EA/ResourceMan/PFRecordInfo.h"
#include "EA/ResourceMan/PFIndex.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Thread/Mutex.h"
#include "EA/ResourceMan/PFDatabaseHeader.h"
#include "EA/ResourceMan/PFIndexModifiable.h"
#include "EA/ResourceMan/PFRecordRead.h"
#include "EA/ResourceMan/PFRecordWrite.h"
#include "EA/CompressionRefpack.h"
#include "EA/ResourceMan/Manager.h"
#include "EA/COM/IUnknown32.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memset_pf(void* dst, int val, unsigned n);   // 0x11e073e
extern "C" void* __cdecl memcpy_pf(void* dst, const void* src, unsigned n); // 0x11e0744
extern "C" int   __cdecl FindEmbeddedPackageHeader(const wchar_t* path);    // 0x8dd510
namespace EA { namespace Thread { extern const unsigned int kTimeoutNone; } }  // 0x1436788
extern char g_ReadHeaderRecordGuard;      // 0x1667a90

// ---- items of slice s006bb1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Mutex { void Lock(const char* name); void Unlock(); };
struct MutexOwner { char pad[0x478]; Mutex mMutex; void LockOrUnlock(bool lock); };
// ---- items of slice s006bb1c0 end

// ---- items of slice s008d91e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned); // 0x011e0744
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern char vtbl_BakeSprites[];        // 0x13f1ab0
extern char vtbl_AppDPF0[];            // 0x1408500
extern char vtbl_AppDPF4[];            // 0x14084f0
extern char vtbl_DPF0[];               // 0x14367b0
extern char vtbl_DPF4[];               // 0x143679c
extern char vtbl_Base4[];              // 0x13eb938
extern char vtbl_Base0[];              // 0x13effb8
extern wchar_t kEmptyWString[];        // 0x1667bac
extern const char kStrRaw[];           // "Resource/Raw"
extern const char kStrPackedRecord[];  // 0x0140a10c "Resource/PackedRecord"
extern const char kStrRecordData[];    // "Resource/RecordData"
extern const char kBusy[];             // "BUSY"
extern const float kHoleRatio;         // 0x1436794 (0.15f)
extern const float kCompressRatio;     // 0x1436798 (0.95f)
#pragma intrinsic(_InterlockedExchange)
struct IAlloc {
    virtual void a0();
    virtual void a1();
    virtual void* Alloc(unsigned size, const char* name, unsigned flags);
    virtual void Free(void* p, unsigned size);
};
struct Key { uint32_t inst, type, group; };
struct IdxEntry { int pos, size, usize; short flags; char compressed; };
struct IStream {
    virtual void s0();
    virtual int AddRef();
    virtual int Release();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual bool Close();        // +0x18
    virtual int GetSize();       // +0x1c
    virtual void s8();
    virtual void s9();
    virtual bool SetPosition(int pos, int origin);   // +0x28
    virtual void s11();
    virtual int Read(void* buf, int size);           // +0x30
};
struct Record {
    virtual void r0();
    virtual void r1();
    virtual int Release();            // +8
    virtual void r3();
    virtual Key* GetKey();            // +0x10
    virtual void r5();
    virtual IStream* GetStream();     // +0x18
    virtual void r7();
    virtual void r8();
    virtual void r9();
    virtual void Detach();            // +0x28
    uint32_t pad4;                    // +4 (second vptr, unused here)
    int magic;                        // +8
    uint32_t pad[7];                  // up to +0x20
    IStream mStream;                  // embedded stream sub-object at +0x20 (vptr)
    bool WriteInternal(int pos, int size);   // 0x8dc890
};
struct Index {
    virtual void i0();
    virtual void i1();
    virtual void i2();
    virtual int GetSize();                                       // +0xc
    virtual void i4(); virtual void i5(); virtual void i6(); virtual void i7(); virtual void i8();
    virtual bool InsertHoles(void* holes, int n, int len);       // +0x24
    virtual void i10();
    virtual void SetEntry(const Key* k, const IdxEntry* e);      // +0x2c
    virtual bool GetEntry(const Key* k, IdxEntry* e);            // +0x30
    virtual void i13();
    virtual bool Serialize(void** ppBuf, int* pLen, int size, int flag);   // +0x38
};
struct RbNode {
    RbNode* right;
    RbNode* left;
    RbNode* parent;
    int color;
    Key key;
    Record* value;
};
RbNode* __cdecl RBTreeIncrement(RbNode*);
void __cdecl RBTreeErase(RbNode*, RbNode* anchor);
void __cdecl RBTreeInsert(RbNode* node, RbNode* parent, RbNode* anchor, int side);
struct RbIter {
    RbNode* p;
    RbIter(RbNode* q) : p(q) {}
    RbIter(const RbIter& o) : p(o.p) {}
};
struct PFPair { Key key; Record* value; };
inline bool KeyLess(const Key& a, const Key& b)
{
    if (a.inst != b.inst)
        return a.inst < b.inst;
    if (a.group != b.group)
        return a.group < b.group;
    return a.type < b.type;
}
struct RbAnchor {
    RbNode* right;
    RbNode* left;
    RbNode* parent;
    int color;
    RbAnchor() : left(0), parent(0), color(0) {}
};
struct RecMap {
    uint32_t cmp;
    RbAnchor mAnchor;
    int mnSize;
    IAlloc* mpAlloc;
    int mnFlags;
    RbNode* Anchor() { return (RbNode*)&mAnchor; }
    RbNode** find(RbNode** out, const Key* k);  // 0xa21dc0 (returns pointer to iterator)
    RbIter erase(RbIter it);                    // 0x8d93a0
    __declspec(noinline) RbNode** DoInsertValue(RbNode** out, RbNode* parent, const PFPair* v, bool bForceToLeft);   // 0x8d98f0
    RbNode** insert(RbNode** out, const PFPair* v, int unused);                             // 0x8d9f20
    void DoNuke(RbNode* root);                  // 0x8de4f0
    RecMap(IAlloc* a) : mpAlloc(a), mnFlags(0) {
        mAnchor.right = Anchor();
        mAnchor.left = Anchor();
        mAnchor.parent = 0;
        *(char*)&mAnchor.color = 0;
        mnSize = 0;
    }
    ~RecMap() { DoNuke(mAnchor.parent); }
};
struct Mutex_s008d_91e0 {
    char d[0x30];
    Mutex_s008d_91e0(void*, bool);       // 0x9222a0
    ~Mutex_s008d_91e0();                 // 0x922130
    int Lock(const void* timeout);   // 0x9221b0
    int Unlock();                    // 0x922270
};
extern const int kTimeoutNone[];    // 0x1436788
struct FileStream {
    virtual void f0();
    virtual int AddRef();
    char d[0x224];
    FileStream(int);          // 0x931da0
    ~FileStream();            // 0x931e70
};
struct HoleSet {
    char d[0x20];
    HoleSet();                       // 0x8db8c0
    ~HoleSet();                      // 0x8db390
    void Reset(int n);               // 0x8db3a0
    bool Insert(int pos, int size);  // 0x8dc1a0
    int Alloc(int size);             // 0x8dbf20
};
IAlloc* GetDefaultAllocator();                                  // 0x925cb0
struct DBase {
    void* volatile vt0;                 // +0
    void* volatile vt4;                 // +4
    volatile long mRefCount;            // +8
    DBase() {
        vt4 = vtbl_BakeSprites;
        vt0 = vtbl_AppDPF0;
        vt4 = vtbl_AppDPF4;
        _InterlockedExchange(&mRefCount, 0);
    }
    ~DBase() {
        vt4 = vtbl_Base4;
        vt0 = vtbl_Base0;
    }
};
struct DBase1 : DBase {
    DBase1() {
        vt0 = vtbl_DPF0;
        vt4 = vtbl_DPF4;
    }
};
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
    WString() : mpBegin(kEmptyWString), mpEnd(kEmptyWString), mpCapacity(kEmptyWString + 1) {}
    ~WString() {
        if (((int)((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
            operator delete[](mpBegin);
    }
    void assign(const wchar_t* b, const wchar_t* e);   // 0x423650
};
struct AutoRef {
    IStream* p;
    AutoRef() : p(0) {}
    ~AutoRef() { if (p) p->Release(); }
    void operator=(IStream* q) {
        IStream* old = p;
        if (old) {
            p = q;
            old->Release();
        }
    }
};
struct PFHeader {
    uint32_t f[10];
    PFHeader() {
        for (int i = 0; i < 10; ++i)
            f[i] = 0;
    }
};
struct HoleTable {
    int mExtent;
    float mRatio;
    HoleSet mHoles;
    HoleTable(int e, float r) : mExtent(e), mRatio(r) {}
};
struct DatabasePackedFile : DBase1 {
    bool mbInitialized;                 // +0xc
    IAlloc* mpAllocator;                // +0x10
    int mnAccessFlags;                  // +0x14
    int mnAutoOpenAccessFlags;          // +0x18
    bool mbEnableReadOnCorruptFiles;    // +0x1c
    bool mbEnableWriteOnCorruptFiles;   // +0x1d
    WString mPath;                      // +0x20
    FileStream mFile;                   // +0x30
    long mnFileStartingOffset;          // +0x258
    long mpStream;                      // +0x25c
    AutoRef mpMemoryLocation;           // +0x260
    unsigned mnMemorySize;              // +0x264
    long mnMemoryOffset;                // +0x268
    uint32_t m26c;                      // +0x26c
    Mutex_s008d_91e0 mMutex;                       // +0x270
    Mutex_s008d_91e0 mFileMutex;                   // +0x2a0
    Index* mpIndex;                     // +0x2d0
    bool mbIndexHasChanged;             // +0x2d4
    unsigned mnUserVersionMajor;        // +0x2d8
    unsigned mnUserVersionMinor;        // +0x2dc
    bool mbEnableCompression;           // +0x2e0
    float mfMinRatioToUseCompression;   // +0x2e4  (just before the map)
    RecMap mMap;                        // +0x2e8
    PFHeader mHeaderBlock;              // +0x308 (10 dwords)
    bool mbFlag330;                     // +0x330
    HoleTable mActive;                  // +0x334 (extent, ratio, holes at +0x33c)
    HoleSet mHoleB;                     // +0x35c
    bool mbHolesHaveChanged;            // +0x37c
    bool mbBusyCompacting;              // +0x37d
    uint32_t mpManager;                 // +0x380

    HoleSet& HoleA() { return mActive.mHoles; }
    HoleSet& HoleB() { return mHoleB; }
    Mutex_s008d_91e0& MutexM() { return mMutex; }
    unsigned& IdxPos() { return mHeaderBlock.f[7]; }

    // out-of-slice callees
    void Dispose();                                       // 0x8d8650
    bool Sync();                                          // 0x8d8b30
    bool FreeSpace(int pos, int size, int flag);          // 0x8d84d0
    bool AllocSpace(int* pOut, int size);                 // 0x8d84a0
    bool WriteRecordRaw(const void* buf, int pos, int size);   // 0x8d90e0
    bool ReadAt(void* dst, int pos, int size);            // 0x8d9050
    bool Decompress(int a, void* b, int c, int d, int e); // 0x8d8820

    // this slice
    bool CompressRecordData(const void* src, unsigned size, void** ppOut, unsigned* pOutSize, uint16_t* pFlags);
    bool ReadCompressed(int a1, int pos, int size, int d, int e);
    ~DatabasePackedFile();
    bool CloseInternal(bool bFlush);
    int GetOpenCount(const Key* key);
    bool WriteIndexRecord();
    void InitializeHoleTable();
    bool TryCompress(const void* src, unsigned size, void** ppOut, unsigned* pOutSize, uint16_t* pFlags);
    __declspec(noinline) bool SetLocation(const wchar_t* path);
    bool CloseRecord(Record* rec);
    DatabasePackedFile(const wchar_t* path, IAlloc* alloc);
};
    void memcpy(...); // 0x011e0744
// ---- items of slice s008d91e0 end


// ---- items of slice s008da140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl operator_delete__(void* p);                              // 0xf47380
extern "C" void* __cdecl RBTreeIncrement(void* node);                             // 0x921580
extern "C" void* __cdecl RBTreeErase(void* node, void* header);                   // 0x921880
extern bool FUN_008d84d0(int pos, int size, bool flag); // 0x8d84d0
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
struct SortNode { char d[0xc]; unsigned key; };
struct HashNode {
    char      d0[0xc];     // +0x00
    int       mnPosition;  // +0x0c
    int       mnSize;      // +0x10
    char      d1[8];       // +0x14
    HashNode* mpNext;      // +0x1c
};
struct HashAlloc {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void Free(void* p, unsigned n);   // +0x0c
    virtual void a4();
};
struct WString_s008d_a140 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
};
struct AutoRef_s008d_a140 { void* p; };                 // AutoRefCount<IStream>
struct FileStream_s008d_a140 { void* vt; char d[0x224]; };
struct PFHeaderField { uint32_t f[10]; };
struct Mutex_s008d_a140 {
    char d[0x30];
    int Lock(const void* timeout);   // 0x9221b0
    int Unlock();                    // 0x922270
};
struct Index_s008d_a140 {
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
struct RbNode_s008d_a140;
struct RbAnchor_s008d_a140 { RbNode_s008d_a140* right; RbNode_s008d_a140* left; RbNode_s008d_a140* parent; int color; };
struct RbNode_s008d_a140 { RbNode_s008d_a140* right; RbNode_s008d_a140* left; RbNode_s008d_a140* parent; int color; char key[0xc]; void* value; };
struct RecMap_s008d_a140 {
    uint32_t cmp;
    RbAnchor_s008d_a140 mAnchor;
    int mnSize;
    IAlloc* mpAlloc;
    int mnFlags;
    RbNode_s008d_a140* Anchor() { return (RbNode_s008d_a140*)&mAnchor; }
    RbNode_s008d_a140** find(RbNode_s008d_a140** out, const void* k);   // 0xa21dc0
    RecMap_s008d_a140() {}
};
struct HoleSet_s008d_a140 {
    int mField0;                       // +0
    char d[0x1c];                      // total 0x20
    int GetTotalSize();                // 0x8dae40
    void Erase(void** out, void* node); // 0x8dae70
    void FUN_008dc120(HoleSet_s008d_a140* other); // 0x8dc120
};
struct HoleTable_s008d_a140 {
    int mExtent;                       // +0x334
    float mRatio;                      // +0x338
    HoleSet_s008d_a140 mHoles;                    // +0x33c
};
struct DatabasePackedFile_s008d_a140 {            // 0x384
    void* volatile vt0;                // +0x00
    void* volatile vt4;                // +0x04
    volatile long mRefCount;           // +0x08
    bool mbInitialized;                // +0x0c
    IAlloc* mpAllocator;               // +0x10
    int mnAccessFlags;                 // +0x14
    int mnAutoOpenAccessFlags;         // +0x18
    bool mbEnableReadOnCorruptFiles;   // +0x1c
    bool mbEnableWriteOnCorruptFiles;  // +0x1d
    WString_s008d_a140 mPath;                     // +0x20
    FileStream_s008d_a140 mFile;                  // +0x30
    long mnFileStartingOffset;         // +0x258
    long mpStream;                     // +0x25c (IStream*)
    AutoRef_s008d_a140 mpMemoryLocation;          // +0x260
    char* mpMemoryBase;                // +0x264
    unsigned mnMemorySize;             // +0x268
    unsigned mnMemoryPosition;         // +0x26c
    Mutex_s008d_a140 mMutex;                      // +0x270
    Mutex_s008d_a140 mFileMutex;                  // +0x2a0
    Index_s008d_a140* mpIndex;                    // +0x2d0
    bool mbIndexHasChanged;            // +0x2d4
    unsigned mnUserVersionMajor;       // +0x2d8
    unsigned mnUserVersionMinor;       // +0x2dc
    bool mbEnableCompression;          // +0x2e0
    float mfMinRatioToUseCompression;  // +0x2e4
    RecMap_s008d_a140 mMap;                       // +0x2e8
    PFHeaderField mHeaderBlock;        // +0x308
    bool mbFlag330;                    // +0x330
    HoleTable_s008d_a140 mActive;                 // +0x334
    HoleSet_s008d_a140 mHoleB;                    // +0x35c
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
struct PFIndexModifiable {
    char d0[4];                 // +0x00
    void* mpAllocator;          // +0x04
    char d1[0x24];              // +0x08
    HashNode** mpBucketArray;   // +0x2c
    int mnBucketCount;          // +0x30
    int GetDataEnd();
    int GetTotalDiskSize();
};
struct BmpGlyphHash {
    char d[0x1c];              // +0x00
    HashAlloc* mpAlloc;        // +0x1c
    void DoFreeNodes(void** pBuckets, unsigned n);
};
typedef bool (__thiscall *TFb0)(void*);
typedef void (__thiscall *TFv0)(void*);
struct VecBuf {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    void* Init(int size, void* pFlag);   // 0x686430
};
typedef void* (__thiscall *TFp1p)(void*, void*);
typedef bool  (__thiscall *TFb3i)(void*, int, int, int);
typedef void  (__thiscall *TFv1i)(void*, int);
typedef void  (__thiscall *TFv1p)(void*, void*);
// ---- items of slice s008da140 end

// ---- items of slice s008daff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl operator_new(int size, const char* name, int a, int b,
                                      const char* file, int line);                      // 0xf473a0
extern "C" void* __cdecl RBTreeDecrement(void* node);                                   // 0x9215c0
extern "C" void* __cdecl RBTreeInsert(void* node, void* parent, void* header, int lazy); // 0x9216a0
extern "C" void* __cdecl DoNukeSubtree(void* node);                                     // 0x9a9600
extern "C" void  __cdecl FUN_00925f30();                                                // 0x925f30 (fixed-pool init)
extern "C" void  __cdecl FUN_00921440(void* self, void* out, unsigned n, unsigned load, int flag); // 0x921440
typedef void  (__thiscall* Fn921440)(void*, void*, unsigned, unsigned, int);
extern "C" void  __cdecl FUN_008de690(void* self, unsigned n);                          // 0x8de690
typedef void  (__thiscall* Fn8de690)(void*, unsigned);
extern "C" void  __cdecl FUN_008dac90(void* self, void* pArray, unsigned n);           // 0x8dac90 DoFreeNodes
typedef void  (__thiscall* Fn8dac90)(void*, void*, unsigned);
extern "C" void  __cdecl FUN_00925e60(void* self);                                       // 0x925e60
typedef void  (__thiscall* Fn925e60)(void*);
extern "C" void  __cdecl ZoneObject_delete(void* p);                                     // 0x926060
extern "C" void* __cdecl FUN_008dbc20(void* self, void* a, void* b, void* c, unsigned flags); // 0x8dbc20
typedef void* (__thiscall* Fn8dbc20)(void*, void*, void*, void*, unsigned);
extern "C" void  __cdecl FUN_008dbba0(void* a, void* b, void* c);                       // 0x8dbba0
extern "C" void  __cdecl FUN_008daeb0(int* a, int* b, int c);                           // 0x8daeb0
extern "C" void  __cdecl FUN_008daef0(int* a, int* b, int c);                           // 0x8daef0
extern "C" void  __cdecl FUN_008dadd0(int* arr, int a, int b, int c, int d, int e);     // 0x8dadd0
extern "C" void* __cdecl Vector_DoInsertValue(void* pos, const void* val);              // 0x4e3e10
struct RBTreeBase { void DoNukeSubtree(void* root); void* Erase(void* node); };
struct HTNode {                 // 0x20-byte hashtable node for mItemsMap
    unsigned  mInstance;        // +0x00  Key.mInstance
    unsigned  mType;            // +0x04  Key.mType
    unsigned  mGroup;           // +0x08  Key.mGroup
    unsigned  mnOffset;         // +0x0c  PFRecordInfo.mnPosition
    unsigned  mnSize;           // +0x10  PFRecordInfo.mnSize
    unsigned  mnSizeDecompressed; // +0x14
    unsigned short mnCompressionType; // +0x18
    unsigned char mbSaved;      // +0x1a
    char      d1b;              // +0x1b
    HTNode*   mpNext;           // +0x1c
};
struct HTIterator { void* mpNode; const void* mpKey; };   // 8-byte hashtable iterator
struct HT {                     // the hashtable object (embedded at PFIndexModifiable+0x28)
    char       d00[4];
    HTNode**   mpBucketArray;   // +0x04
    unsigned   mnBucketCount;   // +0x08
    unsigned   mnElementCount;  // +0x0c
    float      mfMaxLoadFactor; // +0x10
    float      mfGrowthFactor;  // +0x14
    unsigned   mnNextResize;    // +0x18
    void*      mpCoreAllocator; // +0x1c
    unsigned   mnFlags;         // +0x20

    void find(void* out, const void* key);                    // 0x8db3d0
    void* InsertUnique(void* out, const void* val, unsigned flags); // 0x8db450
    void* GetFileInfoRef(const void* key);                    // 0x8dbb10
    HTIterator* erase(HTIterator* out, HTNode* node, HTNode** bucket); // 0x88aa50
};
struct HoleNode {
    HoleNode* mpLeft;           // +0x00
    HoleNode* mpRight;          // +0x04
    HoleNode* mpParent;         // +0x08
    char      d0c[4];           // +0x0c
    unsigned  mnPos;            // +0x10
    unsigned  mnSize;           // +0x14
};
struct HoleSet_s008d_aff0 {                // EA::ResourceMan hole table (0x20 bytes)
    int        mExtent;         // +0x00
    char       d04[4];          // +0x04
    HoleNode*  mAnchor;         // +0x08 (past-the-end header)
    HoleNode*  mRoot;           // +0x0c
    HoleNode*  mTreeRoot;       // +0x10 (tree header parent == root)
    char       d14[4];          // +0x14
    int        mnSize;          // +0x18
    char       d1c[4];          // +0x1c

    HoleSet_s008d_aff0();                                        // 0x8db8c0
    void Reset(int extent);                           // 0x8db3a0
    HoleNode* AllocAt(int size);                      // 0x8dbf20
    void Release(unsigned pos, int size);             // 0x8dc000
    void MergeFrom(HoleSet_s008d_aff0* other);                   // 0x8dc120
};
class PFIndexModifiable_s008d_aff0 {
public:
    void**     vtbl;            // +0x00
    void*      mpAllocator;     // +0x04
    char       d08[0x20];       // +0x08..+0x27
    HT         mItemsMap;       // +0x28
    char       d4c[0x8];        // +0x4c..+0x53

    bool Write(void** ppBuf, unsigned* pSize, unsigned count, char flag); // 0x8daff0
    void SetIsSaved();                                   // 0x8db230
    bool CheckFilesInRange(unsigned a, unsigned b);      // 0x8db280
    bool CheckFilesInSizeRange(unsigned a, unsigned b);  // 0x8db310
    PFIndexModifiable_s008d_aff0(void* alloc);                      // 0x8db730
    void* _virtual_dtor(int flags);                      // 0x8db7b0
    void* GetFileInfo(const void* key);                  // 0x8db810
    bool RemoveFile(const void* key, void* out);         // 0x8db850
    bool Read(void* buf, unsigned a3, unsigned count, char flag); // 0x8db9b0
    int GetFiles(void* vec, void* filter);               // 0x8dbcf0
    unsigned GetAllFiles(int a2, unsigned a3, int a4, void* vec); // 0x8dbdb0
    void PutFileInfo(int a1, int* info);                 // 0x8dbeb0
};
struct RBTree {
    int* insertUnique(int* out, int* parent, int* value, char flag);   // 0x8db560
};
// ---- items of slice s008daff0 end

// @ 0x006bbdd0
bool EA::ResourceMan::DatabasePackedFile::Init()
{
    if (!mbInitialized) mbInitialized = true;
    return true;
}












// @ 0x006bbde0
void __cdecl FUN_006bbde0(void* self)
{ (void)self; }












// @ 0x006bbe50
void MutexOwner::LockOrUnlock(bool lock)
{
    if (lock) mMutex.Lock("App");
    else      mMutex.Unlock();
}












// @ 0x006bbe80
void __cdecl FUN_006bbe80(void* self)
{ (void)self; }












// @ 0x006bbf10
void __cdecl FUN_006bbf10(void* self)
{ (void)self; }












// @ 0x006bbfa0
void __cdecl FUN_006bbfa0(void* self)
{ (void)self; }












// @ 0x006bc020
void __cdecl FUN_006bc020(void* self)
{ (void)self; }












// @ 0x006bc0a0
void __cdecl FUN_006bc0a0(void* self)
{ (void)self; }












// @ 0x006bc0f0
void __cdecl FUN_006bc0f0(void* self)
{ (void)self; }












// @ 0x006bc130
void __cdecl FUN_006bc130(void* self)
{ (void)self; }












// @ 0x008d81a0
void * EA::ResourceMan::DatabasePackedFile::AsInterface(EA::COM::InterfaceId nType)
{
    if (nType == 0x0226a25b)
        return this;
    if (nType != 0xee3f516e)
        return 0;
    return (nType == 0xee3f516e) ? static_cast<EA::COM::IUnknown32 *>(this) : 0;
}











// @ 0x008d81d0
void EA::ResourceMan::DatabasePackedFile::Lock(bool b)
{
    if (b)
        mMutex.Lock(EA::Thread::kTimeoutNone);
    else
        mMutex.Unlock();
}



















// @ 0x008d8200
EA::ResourceMan::PFRecordBase * EA::ResourceMan::DatabasePackedFile::CreateRecord(int flag, unsigned int a, unsigned int b, EA::ResourceMan::Key const & c)
{
    if (flag & 2) {
        return new (mpAllocator, "Resource/PFRecordWrite") PFRecordWrite(a, b, c, this);
    }
    return 0;
}



















// @ 0x008d8250
EA::ResourceMan::PFRecordBase * EA::ResourceMan::DatabasePackedFile::CreateRecord(int flag, void * a, unsigned int b, EA::ResourceMan::Key const & c)
{
    if (flag & 2) {
        return new (mpAllocator, "Resource/PFRecordWrite") PFRecordWrite((unsigned char *)a, b, 1, c, this);
    }
    return 0;
}



















// @ 0x008d82a0
EA::ResourceMan::PFRecordBase * EA::ResourceMan::DatabasePackedFile::CreateRecord(int unused, EA::ResourceMan::PFRecordRead & a, EA::ResourceMan::Key const & b)
{
    return new (mpAllocator, "Resource/PFRecordRead") PFRecordRead(a, b, this);
}



















// @ 0x008d82e0
EA::ResourceMan::PFRecordBase * EA::ResourceMan::DatabasePackedFile::CreateRecord(int unused, EA::ResourceMan::PFRecordInfo & a, EA::ResourceMan::Key const & b)
{
    return new (mpAllocator, "Resource/PFRecordRead") PFRecordRead(a, b, this);
}



















// @ 0x008d8320
bool EA::ResourceMan::DatabasePackedFile::ReadHeaders()
{
    if (!ReadHeaderRecord()) {
        if (mpIndex == 0)
            mpIndex = CreateIndex(3);
        return false;
    }
    return ReadIndexRecord() ? true : false;
}



















// @ 0x008d8360
EA::ResourceMan::PFIndex * EA::ResourceMan::DatabasePackedFile::CreateIndex(int unused)
{
    return new (mpAllocator, "Resource/PFIndexModifiable") PFIndexModifiable(mpAllocator);
}



















// @ 0x008d8390
void EA::ResourceMan::DatabasePackedFile::DestroyIndex(EA::ResourceMan::PFIndex * idx)
{
    if (idx)
        delete idx;
}



















// @ 0x008d83b0
void EA::ResourceMan::DatabasePackedFile::MakeIndexModifiable()
{
    mMutex.Lock(EA::Thread::kTimeoutNone);
    if (mpIndex && mpIndex->IsModifiable()) {
        mMutex.Unlock();
        return;
    }
    {
        PFIndex* newIdx = CreateIndex(3);
        if (mpIndex) {
            int size = mpIndex->GetSize();
            if (size) {
                void * buf = 0;
                unsigned int len = 0;
                if (mpIndex->WriteToMemory(buf, len, size, 0)) {
                    newIdx->ReadFromMemory(buf, len, size, 0);
                    mpAllocator->Free(buf, 0);
                }
            }
            DestroyIndex(mpIndex);
        }
        mpIndex = newIdx;
        InitializeHoleTable();
    }
    mMutex.Unlock();
}



















// @ 0x008d84a0
bool EA::ResourceMan::DatabasePackedFile::AllocateSpace(long & pOut, unsigned int size)
{
    bool r = false;
    if (mnAccessFlags != 0 && (mnAccessFlags & 2)) {
        pOut = mActiveHoleTable.Allocate(size);
        r = true;
    }
    return r;
}



















// @ 0x008d84d0
bool EA::ResourceMan::DatabasePackedFile::FreeSpace(long pos, unsigned int size, bool flag)
{
    if (pos == 0 || size == 0)
        return true;
    if (mnHoleUsageFlags & 0x10) {
        if (flag) {
            mActiveHoleTable.Free(pos, size);
            mbHolesHaveChanged = true;
            return true;
        }
        mDelayedHoleTable.Free(pos, size);
        mbHolesHaveChanged = true;
        return true;
    }
    mActiveHoleTable.Free(pos, size);
    mbHolesHaveChanged = true;
    return true;
}



















// @ 0x008d8530
bool EA::ResourceMan::DatabasePackedFile::SetHoleUse(int extent, float ratio)
{
    mnHoleUsageFlags = extent;
    if (ratio >= 0.0f)
        mfHoleCompactionMinimumRatio = ratio;
    return true;
}



















// @ 0x008d8570
int EA::ResourceMan::DatabasePackedFile::ShouldRecordBeCompressed(EA::ResourceMan::Key const & unused, unsigned int size)
{
    if (mbEnableCompression && (unsigned)(size - 0x32) <= 0xf423ce)
        return 1;
    return 0;
}



















// @ 0x008d85a0
bool EA::ResourceMan::DatabasePackedFile::Attach(bool attach, EA::ResourceMan::Manager * mgr, bool arg3)
{
    bool r = false;
    if (attach) {
        EA::ResourceMan::Manager* old = mpManager;
        if (old != 0 && mgr != old)
            ((TFb3i)(*(void***)this)[0x44 / 4])(this, 0, (int)old, (int)*(uint32_t*)&arg3);
        if (mgr == 0)
            return r;
        if (arg3) {
            mpManager = mgr;
            r = true;
        } else {
            r = mgr->RegisterDatabase(1, this, 0);
        }
    } else {
        if (mgr != 0 && mgr != mpManager)
            return false;
        if (arg3) {
            mpManager = 0;
            r = true;
        } else {
            r = mpManager->RegisterDatabase(0, this, 0);
        }
    }
    return r;
}



















// @ 0x008d8650
bool EA::ResourceMan::DatabasePackedFile::Shutdown()
{
    if (mbInitialized) {
        if (mnAccessFlags != 0)
            Close();
        DestroyIndex(mpIndex);
        mpIndex = 0;
        if (mpStream.mpObject) {
            EA::IO::IStream* p = mpStream.mpObject;
            mpStream.mpObject = 0;
            p->Release();
        }
        mbInitialized = false;
    }
    return true;
}



















// @ 0x008d86c0
bool EA::ResourceMan::DatabasePackedFile::SetStream(EA::IO::IStream * s)
{
    if (mnAccessFlags != 0)
        return false;
    EA::IO::IStream* old = mpStream.mpObject;
    if (s != old) {
        if (s)
            s->AddRef();
        mpStream.mpObject = s;
        if (old)
            old->Release();
    }
    return true;
}



















// @ 0x008d8710
unsigned int EA::ResourceMan::DatabasePackedFile::GetKeyList(eastl::vector<EA::ResourceMan::Key, eastl::sp_vector_allocator> * a, EA::ResourceMan::KeyFilter * b)
{
    mMutex.Lock(EA::Thread::kTimeoutNone);
    if (mnAccessFlags != 0) {
        int r = mpIndex->GetKeyList(a, b);
        mMutex.Unlock();
        return r;
    }
    mMutex.Unlock();
    return 0;
}



















// @ 0x008d8770
unsigned int EA::ResourceMan::DatabasePackedFile::GetKeyListSortedByPosition(eastl::vector<EA::ResourceMan::Key, eastl::sp_vector_allocator> * a)
{
    mMutex.Lock(EA::Thread::kTimeoutNone);
    if (mnAccessFlags != 0) {
        int r = mpIndex->GetKeysSortedByPosition(a);
        mMutex.Unlock();
        return r;
    }
    mMutex.Unlock();
    return 0;
}



















// @ 0x008d87c0
bool EA::ResourceMan::DatabasePackedFile::Verify()
{
    mMutex.Lock(EA::Thread::kTimeoutNone);
    bool r = false;
    if (mOpenRecordMultiMap.mnSize == 0 && mnAccessFlags != 0) {
        int div = mActiveHoleTable.mExtent;
        int total = mActiveHoleTable.GetBytesFree();
        if ((float)total / (float)div > mfHoleCompactionMinimumRatio)
            r = true;
    }
    mMutex.Unlock();
    return r;
}



















// @ 0x008d8820
bool EA::ResourceMan::DatabasePackedFile::DecompressData(unsigned short unused, unsigned char const * buf, unsigned int size, unsigned int expectedSize, unsigned char * dest)
{
    bool r = false;
    EA::CompressionRefpack rp;
    if (rp.ValidateCompressedData(buf, size)) {
        int n = rp.DecompressData(buf, size, 0, 0, 1);
        if (n == expectedSize) {
            if (size == 0 || n == 0) {
                r = true;
            } else if (rp.DecompressData(buf, size, dest, expectedSize, 1) != 0) {
                r = true;
            }
        }
    }
    return r;
}



















// @ 0x008d8890
bool EA::ResourceMan::DatabasePackedFile::InternalSetPosition(long pos)
{
    if (mpMemoryLocation) {
        if ((unsigned)pos >= mnMemorySize)
            return false;
        mnMemoryOffset = pos;
        return true;
    }
    return mpStream.mpObject->SetPosition(pos, (EA::IO::PositionType)0);
}



















// @ 0x008d88d0
unsigned int EA::ResourceMan::DatabasePackedFile::InternalRead(void * dst, unsigned int size)
{
    if (mpMemoryLocation) {
        unsigned pos = mnMemoryOffset;
        unsigned limit = mnMemorySize;
        unsigned n = size;
        if (pos + n > limit)
            n = limit - pos;
        memcpy_pf(dst, (char*)(pos + (unsigned)mpMemoryLocation), n);
        mnMemoryOffset += n;
        return n;
    }
    return mpStream.mpObject->Read(dst, size);
}



















// @ 0x008d8930
unsigned int EA::ResourceMan::DatabasePackedFile::InternalGetSize()
{
    if (mpMemoryLocation)
        return mnMemorySize;
    return mpStream.mpObject->GetSize();
}



















// @ 0x008d8950
bool EA::ResourceMan::DatabasePackedFile::InternalClose()
{
    if (mpMemoryLocation) {
        mnMemoryOffset = 0;
        return true;
    }
    return mpStream.mpObject->Close();
}



















// @ 0x008d8980
bool EA::ResourceMan::DatabasePackedFile::Open(int access, int mode, bool autoOpen)
{
    if (mnAccessFlags != 0)
        return false;
    bool r = false;
    if (mpMemoryLocation) {
        if ((access & 3) == 1 && (mode == 3 || mode == 6) &&
            ReadHeaders()) {
            mnAccessFlags = access;
            return true;
        }
        return false;
    }
    if (autoOpen) {
        mnAutoOpenAccessFlags = access;
        return true;
    }
    if (!mbInitialized)
        return false;
    {
        EA::IO::IStream* s = mpStream.mpObject;
        int flags = (access & 2) ? 3 : 1;
        mnAccessFlags = flags;
        if (s) {
            if ((s->GetAccessFlags() & flags) != flags) {
                mnAccessFlags = 0;
                return false;
            }
        } else {
            if (access & 2) {
                if (mode == 6) mode = 4;
            } else {
                if (mode == 6) mode = 3;
            }
            (&mFile)->SetPath(mPath.mpBegin);
            if (!(&mFile)->Open(mnAccessFlags, mode, 1, 2)) {
                mnAccessFlags = 0;
                return false;
            }
            mpStream.mpObject = (EA::IO::IStream*)&mFile;
        }
        if (InternalGetSize() != 0) {
            r = ReadHeaders();
            if (r)
                return true;
            mpIndex->Clear();
            if (mbEnableWriteOnCorruptFiles && (mnAccessFlags & 2)) {
                r = WriteEmptyHeaderRecord();
                if (r) {
                    InitializeHoleTable();
                    mbIndexHasChanged = true;
                    return true;
                }
            }
        } else {
            if (!(mnAccessFlags & 2)) {
                r = false;
            } else {
                r = WriteEmptyHeaderRecord();
                if (r)
                    return true;
            }
        }
    }
    InternalClose();
    if (!r)
        mnAccessFlags = 0;
    return r;
}



















// @ 0x008d8b30
bool EA::ResourceMan::DatabasePackedFile::CloseOpenRecords()
{
    bool r = false;
    if (mnAccessFlags != 0) {
        while (mOpenRecordMultiMap.mnSize != 0) {
            eastl::rbtree_node<eastl::pair<EA::ResourceMan::Key const ,EA::ResourceMan::PFRecordBase *> >* n = (eastl::rbtree_node<eastl::pair<EA::ResourceMan::Key const ,EA::ResourceMan::PFRecordBase *> >*)mOpenRecordMultiMap.mAnchor.mpNodeLeft;
            CloseRecord(n->mValue.second);
        }
        r = true;
    }
    return r;
}



















// @ 0x008d8b70
bool EA::ResourceMan::DatabasePackedFile::DeleteRecord(EA::ResourceMan::Key const & key)
{
    mMutex.Lock(EA::Thread::kTimeoutNone);
    bool r = false;
    if ((mnAccessFlags & 2) && mnAccessFlags != 0) {
        if (mpIndex->FindRecord(key)) {
            if (mOpenRecordMultiMap.find(key) == mOpenRecordMultiMap.end()) {
                MakeIndexModifiable();
                PFRecordInfo e(0, 0, 0, 0, false);
                if (mpIndex->DeleteRecord(key, e)) {
                    FreeSpace(e.mnPosition, e.mnSize, e.mbCommitted == 0);
                    r = true;
                    mbIndexHasChanged = true;
                }
            }
        }
    }
    mMutex.Unlock();
    return r;
}



















// @ 0x008d8c50
bool EA::ResourceMan::DatabasePackedFile::ReadHeaderRecord()
{
    char buf[0x60];
    if (mpMemoryLocation) {
        if ((unsigned)mnFileStartingOffset >= mnMemorySize)
            return false;
        mnMemoryOffset = mnFileStartingOffset;
    } else {
        if (!mpStream.mpObject->SetPosition(mnFileStartingOffset, (EA::IO::PositionType)0))
            return false;
    }
    memset_pf(buf, 0, 0x60);
    if (InternalRead(buf, 0x60) != 0x60)
        return false;
    uint32_t* b = (uint32_t*)buf;
    mHeader.mnUserVersionMajor = b[3];
    mHeader.mnUserVersionMinor = b[4];
    mHeader.mnCreationTime = b[6];
    mHeader.mnUpdatedTime = b[7];
    mHeader.mnIndexRecordType = b[8];
    mHeader.mnIndexRecordPosition = b[16];
    if (mHeader.mnIndexRecordPosition == 0)
        mHeader.mnIndexRecordPosition = b[10];
    mHeader.mnIndexRecordEntryCount = b[9];
    mHeader.mnIndexRecordSize = b[11];
    if (VerifyHeaderRecordIntegrity((EA::ResourceMan::PFHeaderRecord *)buf))
        return true;
    mnFileStartingOffset = FindEmbeddedPackageHeader(mPath.mpBegin);
    if (mnFileStartingOffset == -1) {
        mnFileStartingOffset = 0;
        return false;
    }
    if (g_ReadHeaderRecordGuard)
        return false;
    g_ReadHeaderRecordGuard = 1;
    bool r = ReadHeaderRecord();
    g_ReadHeaderRecordGuard = 0;
    return r;
}



















// @ 0x008d8e20
bool EA::ResourceMan::DatabasePackedFile::WriteEmptyHeaderRecord()
{
    for (int i = 0; i < 10; ++i)
        ((uint32_t *)&mHeader)[i] = 0;
    mHeader.mnUserVersionMajor = mnUserVersionMajor;
    mHeader.mnUserVersionMinor = mnUserVersionMinor;
    for (int i = 2; i < 10; ++i)
        ((uint32_t *)&mHeader)[i] = 0;
    mbHeaderHasChanged = true;
    uint32_t r = (uint32_t)WriteHeaderRecord();
    if ((char)r != 0) {
        if (mpMemoryLocation)
            return r & 0xffffff00u;
        r = (uint32_t)mpStream.mpObject->SetSize(0x60);
    }
    return r;
}



















// @ 0x008d8ee0
bool EA::ResourceMan::DatabasePackedFile::WriteHeaderRecord()
{
    if (!(mnAccessFlags & 2))
        return false;
    if (mpMemoryLocation == 0) {
        if (mpStream.mpObject->GetState() == -2)
            return false;
    }
    if (!mbHeaderHasChanged)
        return true;
    if (!InternalSetPosition(mnFileStartingOffset))
        return false;
    char buf[0x60];
    memset_pf(buf, 0, 0x60);
    uint32_t* b = (uint32_t*)buf;
    b[0] = 0x46504244;
    b[1] = 3;
    b[2] = 0;
    b[3] = mnUserVersionMajor;
    b[4] = mnUserVersionMinor;
    b[8] = mHeader.mnIndexRecordType;
    b[9] = mHeader.mnIndexRecordEntryCount;
    b[10] = (mHeader.mnIndexRecordPosition & 0x80000000) ? 0 : mHeader.mnIndexRecordPosition;
    b[11] = mHeader.mnIndexRecordSize;
    b[15] = 3;
    b[16] = mHeader.mnIndexRecordPosition;
    b[17] = mHeader.mnIndexRecordEntryCount;
    b[19] = mHeader.mnIndexRecordPosition;
    if (mpMemoryLocation)
        return false;
    if (!mpStream.mpObject->Write((void const *)buf, 0x60))
        return false;
    mbHeaderHasChanged = false;
    return true;
}



















// @ 0x008d9000
bool EA::ResourceMan::DatabasePackedFile::VerifyIndexRecordIntegrity()
{
    int size;
    if (mpMemoryLocation)
        size = mnMemorySize;
    else
        size = mpStream.mpObject->GetSize();
    return mpIndex->Validate(0, size);
}



















// @ 0x008d9050
bool EA::ResourceMan::DatabasePackedFile::ReadFileSpan(void * dst, long pos, unsigned int size)
{
    mFileMutex.Lock(EA::Thread::kTimeoutNone);
    bool r;
    if (mnAccessFlags != 0) {
        int abs = mnFileStartingOffset + pos;
        if (mpMemoryLocation) {
            if ((unsigned)abs >= mnMemorySize)
                goto fail;
            mnMemoryOffset = abs;
        } else {
            if (!mpStream.mpObject->SetPosition(abs, (EA::IO::PositionType)0))
                goto fail;
        }
        r = InternalRead(dst, size) != -1;
        mFileMutex.Unlock();
        return r;
    }
fail:
    mFileMutex.Unlock();
    return false;
}



















// @ 0x008d90e0
bool EA::ResourceMan::DatabasePackedFile::WriteFileSpan(void const * dst, long pos, unsigned int size)
{
    mFileMutex.Lock(EA::Thread::kTimeoutNone);
    bool r;
    if (mnAccessFlags != 0 && (mnAccessFlags & 2)) {
        if (InternalSetPosition(mnFileStartingOffset + pos)) {
            if (mpMemoryLocation == 0)
                r = mpStream.mpObject->Write(dst, size);
            else
                r = false;
            mFileMutex.Unlock();
            return r;
        }
    }
    mFileMutex.Unlock();
    return false;
}



















// @ 0x008d9170
bool EA::ResourceMan::DatabasePackedFile::ReadRecordRaw(EA::ResourceMan::Key const & key, void * dst, unsigned int size)
{
    mMutex.Lock(EA::Thread::kTimeoutNone);
    if (mnAccessFlags != 0) {
        const PFRecordInfo* e = (const PFRecordInfo*)mpIndex->FindRecord(key);
        unsigned esize = e->mnSize;
        unsigned n = size;
        if (n > esize)
            n = esize;
        bool r = ReadFileSpan(dst, e->mnPosition, n);
        mMutex.Unlock();
        return r;
    }
    mMutex.Unlock();
    return false;
}










// @ 0x008d91e0
bool EA::ResourceMan::DatabasePackedFile::CompressData(void const * src, unsigned int size, void *& ppOut, unsigned int & pOutSize, unsigned short & pFlags)
{
    bool bAlloc = (ppOut == 0);
    if (size - 1 <= 0x26259fe) {
        EA::CompressionRefpack rp;
        pFlags = 0xffff;
        unsigned n = rp.CompressData(src, size, 0, 0, 1);
        if (bAlloc && n) {
            pOutSize = n;
            ppOut = mpAllocator->Alloc(n, kStrPackedRecord, 0);
        }
        if (ppOut) {
            n = rp.CompressData(src, size, ppOut, pOutSize, (size > 250000) + 1);
            pOutSize = n;
            if (n != 0xffffffff)
                return true;
            pOutSize = 0;
            if (bAlloc && ppOut) {
                mpAllocator->Free(ppOut, 0);
                ppOut = 0;
            }
        }
        return false;
    }
    if (bAlloc) {
        pOutSize = size;
        void* p = mpAllocator->Alloc(size, kStrPackedRecord, 0);
        ppOut = p;
        memcpy(p, src, size);
        return true;
    }
    if (size <= pOutSize) {
        pOutSize = size;
        memcpy(ppOut, src, size);
        return true;
    }
    pOutSize = 0;
    return false;
}

// @ 0x008d9320
bool EA::ResourceMan::DatabasePackedFile::DecompressRecord(unsigned short a1, unsigned int pos, unsigned int size, unsigned int d, unsigned char * e)
{
    bool r = false;
    if (pos != 0) {
        void* buf = mpAllocator->Alloc(size, kStrRaw, 0);
        if (buf) {
            if (WriteFileSpan(buf, pos, size))
                r = DecompressData(a1, (unsigned char const *)buf, size, d, e);
            mpAllocator->Free(buf, 0);
        }
    }
    return r;
}

// @ 0x008d93a0
RbIter RecMap::erase(RbIter it)
{
    RbNode* node = it.p;
    --mnSize;
    RbNode* next = RBTreeIncrement(node);
    RBTreeErase(node, Anchor());
    mpAlloc->Free(node, 0x20);
    return RbIter(next);
}

// @ 0x008d93e0
DatabasePackedFile::~DatabasePackedFile()
{
    vt0 = vtbl_DPF0;
    vt4 = vtbl_DPF4;
    Dispose();
}

// @ 0x008d94a0
bool EA::ResourceMan::DatabasePackedFile::CloseInternal(bool bFlush)
{
    bool r;
    if (mnAccessFlags != 0) {
        if (mnAccessFlags & 2) {
            r = CloseOpenRecords();
            if (bFlush && r) {
                Flush();
            }
        } else {
            r = true;
        }
        if (mpMemoryLocation != 0) {
            mnMemoryOffset = 0;
            mnAccessFlags = 0;
        } else {
            mpStream.mpObject->Close();
            mnAccessFlags = 0;
        }
    } else {
        r = true;
    }
    if (mpStream.mpObject == (EA::IO::IStream*)&mFile)
        mpStream = 0;
    {
        DestroyIndex(mpIndex);
    }
    mpIndex = 0;
    mActiveHoleTable.Reset(0);
    mDelayedHoleTable.Reset(0);
    return r;
}

// @ 0x008d9560
int DatabasePackedFile::GetOpenCount(const Key* key)
{
    if (!(mnAccessFlags & 2))
        return 0;
    MutexM().Lock(kTimeoutNone);
    int count = 0;
    if (mnAccessFlags != 0) {
        RbNode* tmp;
        RbNode* n = *mMap.find(&tmp, key);
        RbNode* end = mMap.Anchor();
        while (n != end && n->key.inst == key->inst && n->key.type == key->type && n->key.group == key->group) {
            ++count;
            n = RBTreeIncrement(n);
        }
    }
    MutexM().Unlock();
    return count;
}

// @ 0x008d95f0
bool DatabasePackedFile::WriteIndexRecord()
{
    bool ok = true;
    if (mnAccessFlags != 0 && (mnAccessFlags & 2) && mbIndexHasChanged) {
        int size = mpIndex->GetSize();
        void* buf = 0;
        int len = 0;
        if (!mpIndex->Serialize(&buf, &len, size, 1))
            return false;
        int oldSize = (int)mHeaderBlock.f[9];
        mbFlag330 = true;
        if (len == 0) {
            ok = FreeSpace(IdxPos(), oldSize, 0);
            mHeaderBlock.f[9] = 0;
            IdxPos() = 0;
            mHeaderBlock.f[8] = 0;
        } else {
            mHeaderBlock.f[8] = size;
            mHeaderBlock.f[9] = len;
            if (len != oldSize || (mActive.mExtent & 0x10)) {
                ok = FreeSpace(IdxPos(), oldSize, 0);
                if (!ok)
                    goto done;
                int pos = 0;
                IdxPos() = 0;
                ok = AllocSpace(&pos, mHeaderBlock.f[9]);
                IdxPos() = pos;
                if (!ok) {
                    mHeaderBlock.f[8] = 0;
                    IdxPos() = 0;
                    mHeaderBlock.f[9] = 0;
                    goto done;
                }
            }
            ok = WriteRecordRaw(buf, IdxPos(), len);
            if (!ok) {
                if (IdxPos() != 0) {
                    FreeSpace(IdxPos(), mHeaderBlock.f[9], 0);
                    mHeaderBlock.f[9] = 0;
                    IdxPos() = 0;
                    mHeaderBlock.f[8] = 0;
                }
            }
        }
        if (ok)
            mbIndexHasChanged = false;
done:
        mpAllocator->Free(buf, 0);
    }
    return ok;
}

// @ 0x008d9770
void DatabasePackedFile::InitializeHoleTable()
{
    int end = mnMemorySize ? mnMemoryOffset : mpMemoryLocation.p->GetSize();
    int n = end - mpStream;
    HoleA().Reset(n);
    HoleB().Reset(n);
    if (mActive.mExtent & 2) {
        HoleA().Reset(0);
        HoleA().Insert(0, 0x60);
        if (mActive.mExtent & 8) {
            WriteRecordRaw(kBusy, 0, 4);
            mbFlag330 = true;
            mbIndexHasChanged = true;
            return;
        }
        if (HoleA().Insert(IdxPos(), mHeaderBlock.f[9]) && mpIndex->InsertHoles(&HoleA(), 0x60, n))
            return;
        HoleA().Reset(n);
        HoleB().Reset(n);
        mActive.mExtent &= ~2;
    }
}

// @ 0x008d9850
bool EA::ResourceMan::DatabasePackedFile::ShouldRecordBeCompressed(unsigned char * src, unsigned int size, void *& ppOut, unsigned int & pOutSize, unsigned short & pFlags)
{
    ppOut = 0;
    pOutSize = 0;
    if (CompressData(src, size, ppOut, pOutSize, pFlags)) {
        float a = (float)pOutSize;
        float b = (float)size;
        if (a / b < mfMinRatioToUseCompression)
            return true;
        if (ppOut)
            mpAllocator->Free(ppOut, 0);
        ppOut = 0;
        pOutSize = 0;
    }
    return false;
}

// @ 0x008d98f0
RbNode** RecMap::DoInsertValue(RbNode** out, RbNode* parent, const PFPair* v, bool bForceToLeft)
{
    int side = (bForceToLeft || parent == Anchor() || KeyLess(v->key, parent->key)) ? 0 : 1;
    RbNode* node = (RbNode*)mpAlloc->Alloc(0x20, 0, mnFlags);
    PFPair* pv = (PFPair*)&node->key;
    if (pv)
        *pv = *v;
    RBTreeInsert(node, parent, Anchor(), side);
    ++mnSize;
    *out = node;
    return out;
}

// @ 0x008d99c0
bool EA::ResourceMan::DatabasePackedFile::SetLocation(wchar_t const * path)
{
    if (mnAccessFlags == 0) {
        mpMemoryLocation = 0;
        mnMemorySize = 0;
        const wchar_t* e = path;
        if (*e) {
            do {
                ++e;
            } while (*e);
        }
        mPath.assign(path, path + (e - path));
        return true;
    }
    return false;
}

// @ 0x008d9a10
bool DatabasePackedFile::CloseRecord(Record* rec)
{
    typedef void (__thiscall *VFn)(DatabasePackedFile*);
    if (!(mnAccessFlags & 2)) {
        rec->Detach();
        rec->Release();
        return true;
    }
    Key key = *rec->GetKey();
    Mutex_s008d_91e0& mtx = MutexM();
    mtx.Lock(kTimeoutNone);
    if (mnAccessFlags == 0) {
        mtx.Unlock();
        return false;
    }
    RecMap* map = &mMap;
    RbNode* end = map->Anchor();
    RbNode* tmpf;
    RbNode* it = *map->find(&tmpf, &key);
    while (it != end && it->key.inst == key.inst && it->key.type == key.type && it->key.group == key.group) {
        if (it->value == rec)
            goto found;
        it = RBTreeIncrement(it);
    }
    mtx.Unlock();
    return false;

found:
    if (rec->magic != 0x12e4a892) {
        rec->Detach();
        rec->Release();
        --map->mnSize;
        RBTreeIncrement(it);
        RBTreeErase(it, map->Anchor());
        map->mpAlloc->Free(it, 0x20);
        mtx.Unlock();
        return true;
    }
    if (!(mnAccessFlags & 2)) {
        mtx.Unlock();
        return false;
    }
    ((VFn)(*(void***)this)[0x8c / 4])(this);
    if (rec->GetStream()->GetSize() == 0) {
        IdxEntry e0;
        e0.pos = e0.size = e0.usize = 0;
        e0.flags = 0;
        e0.compressed = 0;
        if (mpIndex->GetEntry(&key, &e0))
            FreeSpace(e0.pos, e0.size, e0.compressed == 0);
        IdxEntry e1;
        e1.pos = e1.size = e1.usize = 0;
        e1.flags = 0;
        e1.compressed = 0;
        mpIndex->SetEntry(&key, &e1);
        mbIndexHasChanged = true;
        rec->Detach();
        rec->Release();
        RbIter tmp(it);
        map->erase(tmp);
        mtx.Unlock();
        return true;
    }
    mtx.Unlock();

    IStream* stream = &rec->mStream;
    int size = stream->GetSize();
    void* pCompressed = 0;
    unsigned cSize = 0;
    uint32_t cFlags = 0;
    if (mbEnableCompression && (unsigned)(size - 0x32) <= 0xf423ce) {
        char* buf = (char*)mpAllocator->Alloc(size + 0x10, kStrRecordData, 0);
        buf[size + 1] = 0;
        buf[size] = 0;
        if (stream->SetPosition(0, 0) && size == stream->Read(buf, size)) {
            if (!TryCompress(buf, size, &pCompressed, &cSize, (uint16_t*)&cFlags)) {
                pCompressed = 0;
                cFlags = 0;
            }
        }
        mpAllocator->Free(buf, 0);
    }
    int diskPos = 0;
    int storedSize = pCompressed ? (int)cSize : size;
    mtx.Lock(kTimeoutNone);
    bool bAlloc = false;
    if (mnAccessFlags != 0 && (mnAccessFlags & 2)) {
        diskPos = HoleA().Alloc(storedSize);
        bAlloc = true;
    }
    mtx.Unlock();
    IdxEntry newEntry;
    newEntry.pos = diskPos;
    newEntry.size = storedSize;
    newEntry.usize = size;
    newEntry.flags = (short)cFlags;
    newEntry.compressed = 0;
    bool result = false;
    if (bAlloc) {
        if (pCompressed) {
            result = WriteRecordRaw(pCompressed, diskPos, cSize);
            if (pCompressed)
                mpAllocator->Free(pCompressed, 0);
        } else {
            result = rec->WriteInternal(diskPos, size);
        }
    } else if (pCompressed) {
        mpAllocator->Free(pCompressed, 0);
    }
    bool bAdded = false;
    mtx.Lock(kTimeoutNone);
    if (result) {
        IdxEntry old;
        old.pos = old.size = old.usize = 0;
        old.flags = 0;
        old.compressed = 0;
        if (mpIndex->GetEntry(&key, &old))
            FreeSpace(old.pos, old.size, old.compressed == 0);
        mpIndex->SetEntry(&key, &newEntry);
        mbIndexHasChanged = true;
        bAdded = true;
    } else if (bAlloc) {
        FreeSpace(diskPos, storedSize, 1);
    }
    RbNode* it2 = *map->find(&tmpf, &key);
    while (it2 != end && it2->key.inst == key.inst && it2->key.type == key.type && it2->key.group == key.group) {
        if (it2->value == rec) {
            --map->mnSize;
            RBTreeIncrement(it2);
            RBTreeErase(it2, map->Anchor());
            map->mpAlloc->Free(it2, 0x20);
            rec->Detach();
            rec->Release();
            break;
        }
        it2 = RBTreeIncrement(it2);
    }
    mtx.Unlock();
    return bAdded;
}

// @ 0x008d9f20
RbNode** RecMap::insert(RbNode** out, const PFPair* v, int unused)
{
    RbNode* parent = Anchor();
    RbNode* n = mAnchor.parent;
    while (n) {
        parent = n;
        n = KeyLess(v->key, n->key) ? n->left : n->right;
    }
    DoInsertValue(out, parent, v, false);
    return out;
}

// @ 0x008d9f80
DatabasePackedFile::DatabasePackedFile(const wchar_t* path, IAlloc* alloc)
: mbInitialized(false),
      mpAllocator(alloc ? alloc : GetDefaultAllocator()),
      mnAccessFlags(0),
      mnAutoOpenAccessFlags(0),
      mbEnableReadOnCorruptFiles(false),
      mbEnableWriteOnCorruptFiles(true),
      mFile(0),
      mpStream(0),
      mnMemorySize(0),
      mnMemoryOffset(0),
      m26c(0),
      mMutex(0, true),
      mFileMutex(0, true),
      mfMinRatioToUseCompression(kCompressRatio),
      mpIndex(0),
      mbIndexHasChanged(false),
      mnUserVersionMajor(0),
      mnUserVersionMinor(0),
      mbEnableCompression(true),
      mMap(mpAllocator),
      mbFlag330(false),
      mActive(0x13, kHoleRatio),
      mbHolesHaveChanged(false),
      mbBusyCompacting(false),
      mpManager(0)
{
    mFile.AddRef();
    if (path)
        SetLocation(path);
}

// @ 0x008da140
bool DatabasePackedFile_s008d_a140::CompactDatabaseInternal()
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




// @ 0x008da3d0
bool DatabasePackedFile_s008d_a140::OpenRecord(void* pKey, unsigned access, unsigned reqFlags, unsigned mode, void* arg5, void* pOutRecord)
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




// @ 0x008da750
bool EA::ResourceMan::DatabasePackedFile::ReadIndexRecord()
{
    char cFlag = 0;
    if (mHeader.mnIndexRecordEntryCount == 0) {
        if (mpIndex == 0)
            mpIndex = CreateIndex(3);
        if (mpIndex->GetSize() == 0)
            InitializeHoleTable();
        return true;
    }
    unsigned nPos = (unsigned)mnFileStartingOffset + mHeader.mnIndexRecordPosition;
    if (((char *)mpMemoryLocation) == 0) {
        if (!mpStream.mpObject->SetPosition(nPos, (EA::IO::PositionType)0))
            return false;
    } else {
        if (mnMemorySize <= nPos)
            return false;
        mnMemoryOffset = nPos;
    }
    VecBuf buf;
    buf.Init((int)mHeader.mnIndexRecordSize, &cFlag);
    void* pBuf = buf.mpBegin;
    bool bResult = false;
    bool bCreated = false;
    if (!InternalRead(pBuf, mHeader.mnIndexRecordSize))
        goto cleanup;
    if (mpIndex == 0)
        mpIndex = CreateIndex(3);
    if (mpIndex != 0)
        bCreated = mpIndex->ReadFromMemory(pBuf, mHeader.mnIndexRecordSize, mHeader.mnIndexRecordEntryCount, 1);
    if (!VerifyIndexRecordIntegrity() && !mbEnableReadOnCorruptFiles) {
        bResult = false;
    } else if (bCreated) {
        InitializeHoleTable();
        mbIndexHasChanged = false;
        bResult = true;
    }
cleanup:
    if (pBuf != 0 && ((int*)pBuf)[-1] != 0)
        operator_delete__(pBuf);
    return bResult;
}




// @ 0x008da8b0
bool EA::ResourceMan::DatabasePackedFile::CompactDatabase()
{
    mMutex.Lock(EA::Thread::kTimeoutNone);
    mFileMutex.Lock(EA::Thread::kTimeoutNone);
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




// @ 0x008da920
char DatabasePackedFile_s008d_a140::FUN_008da920(void* param2)
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




// @ 0x008daba0
bool DatabasePackedFile_s008d_a140::Flush()
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




// @ 0x008dae40
int HoleSet_s008d_a140::GetTotalSize()
{
    int nSum = 0;
    for (void* p = *(void**)((char*)this + 0xc); p != (char*)this + 8; p = RBTreeIncrement(p))
        nSum += *(int*)((char*)p + 0x14);
    return nSum;
}




// @ 0x008dae70
void HoleSet_s008d_a140::Erase(void** ppOut, void* pNode)
{
    --*(int*)((char*)this + 0x14);
    void* pNext = RBTreeIncrement(pNode);
    RBTreeErase(pNode, (char*)this + 4);
    operator_delete__(pNode);
    *ppOut = pNext;
}




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



// @ 0x008daff0
bool PFIndexModifiable_s008d_aff0::Write(void** ppBuf, unsigned* pSize, unsigned count, char flag)
{
    bool bSameFirst = true;    // every record's key.mType equals the first record's
    bool bSameLast = true;     // every record's key.mGroup equals the last record's
    unsigned nFirstOffset = 0;
    unsigned nLastOffset = 0;

    HTNode** pb = mItemsMap.mpBucketArray;
    HTNode* p = *pb;
    if (p == 0) {
        ++pb;
        while (*pb == 0)
            ++pb;
        p = *pb;
    }
    if (mItemsMap.mnElementCount == 0) {
        bSameFirst = false;
        bSameLast = false;
    } else {
        nLastOffset = p->mGroup;
        nFirstOffset = p->mType;
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
    while (p != mItemsMap.mpBucketArray[mItemsMap.mnBucketCount]) {
        if (!bSameFirst || p->mType != nFirstOffset)
            bSameFirst = false;
        if (bSameLast && p->mGroup == nLastOffset)
            bSameLast = true;
        else
            bSameLast = false;
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
    int nElem = 0x20;
    *pSize = 4;
    if (bSameFirst) {
        *pSize = 8;
        nElem = 0x1c;
    }
    if (bSameLast) {
        *pSize += 4;
        nElem -= 4;
    }
    *pSize += 4;
    int nTotal = (int)*pSize + (nElem - 4) * (int)count;
    *pSize = (unsigned)nTotal;
    unsigned* pBuf = (unsigned*)((void* (__thiscall*)(void*, unsigned, const char*, int))
                                 (*(void***)mpAllocator)[8 / 4])(mpAllocator, (unsigned)nTotal, (const char*)0x140a1dc, 0);
    *ppBuf = pBuf;
    if (pBuf == 0)
        return false;

    unsigned* pOut = pBuf;
    int i = 1;
    *pOut = (-(unsigned)bSameLast & 2) | (bSameFirst ? 1u : 0u) | 4;
    if (bSameFirst) {
        pBuf[1] = nFirstOffset;
        i = 2;
    }
    if (bSameLast) {
        pBuf[i] = nLastOffset;
        ++i;
    }
    pBuf[i] = 0;
    pOut = pBuf + i + 1;

    HTNode** pb2 = mItemsMap.mpBucketArray;
    HTNode* q = *pb2;
    if (q == 0) {
        ++pb2;
        while (*pb2 == 0) ++pb2;
        q = *pb2;
    }
    HTNode* end = mItemsMap.mpBucketArray[mItemsMap.mnBucketCount];
    while (q != end) {
        if (!bSameFirst)
            *pOut++ = q->mType;
        if (!bSameLast)
            *pOut++ = q->mGroup;
        pOut[0] = q->mInstance;
        pOut[1] = q->mnOffset;
        pOut[2] = q->mnSize | 0x80000000;
        pOut[3] = q->mnSizeDecompressed;
        unsigned hi = (q->mbSaved == 0 && flag == 0) ? 0u : 0x10000u;
        pOut[4] = (unsigned)q->mnCompressionType | hi;
        pOut += 5;
        q = q->mpNext;
        while (q == 0) { ++pb2; q = *pb2; }
    }
    return true;
}


// @ 0x008db230
void PFIndexModifiable_s008d_aff0::SetIsSaved()
{
    HTNode** pb = mItemsMap.mpBucketArray;
    HTNode* p = *pb;
    if (p == 0) {
        ++pb;
        while (*pb == 0)
            ++pb;
        p = *pb;
    }
    while (p != mItemsMap.mpBucketArray[mItemsMap.mnBucketCount]) {
        p->mbSaved = 1;
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
}


// @ 0x008db280
bool PFIndexModifiable_s008d_aff0::CheckFilesInRange(unsigned a, unsigned b)
{
    HTNode** pb = mItemsMap.mpBucketArray;
    HTNode* p = *pb;
    if (p == 0) {
        ++pb;
        while (*pb == 0)
            ++pb;
        p = *pb;
    }
    HTNode* end = mItemsMap.mpBucketArray[mItemsMap.mnBucketCount];
    while (p != end) {
        if (p->mnSize != 0) {
            if ((unsigned)(p->mnOffset - a) >= (unsigned)(b - a))
                return false;
            if (p->mnSize > (unsigned)(b - p->mnOffset))
                return false;
        }
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
    return true;
}


// @ 0x008db310
bool PFIndexModifiable_s008d_aff0::CheckFilesInSizeRange(unsigned a, unsigned b)
{
    if (b == 0)
        return true;
    unsigned nEnd = a + b;
    HTNode** pb = mItemsMap.mpBucketArray;
    HTNode* p = *pb;
    if (p == 0) {
        ++pb;
        while (*pb == 0)
            ++pb;
        p = *pb;
    }
    HTNode* end = mItemsMap.mpBucketArray[mItemsMap.mnBucketCount];
    while (p != end) {
        if (p->mnSize != 0 && p->mnOffset < nEnd && a < p->mnOffset + p->mnSize)
            return false;
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
    return true;
}


// @ 0x008db3a0
void HoleSet_s008d_aff0::Reset(int extent)
{
    ((RBTreeBase*)((char*)this + 4))->DoNukeSubtree(*(void**)((char*)this + 0x10));
    char* b = (char*)this + 4;
    void* p = b + 4;
    *(void**)(b + 8) = p;
    *(void**)p = p;
    *(void**)(b + 0xc) = 0;
    *(char*)(b + 0x10) = 0;
    *(void**)(b + 0x14) = 0;
    mExtent = extent;
}


// @ 0x008db450
void* HT::InsertUnique(void* out, const void* val, unsigned flags)
{
    (void)flags;
    const unsigned* v = (const unsigned*)val;
    unsigned hash = v[0] ^ v[2];
    unsigned bucket = hash % mnBucketCount;
    HTNode* node = mpBucketArray[bucket];
    while (node != 0) {
        if (v[0] == node->mInstance &&
            v[1] == node->mType &&
            v[2] == node->mGroup) {
            *(void**)out = node;
            *((char*)out + 8) = 0;
            *(void**)((char*)out + 4) = &mpBucketArray[bucket];
            return out;
        }
        node = node->mpNext;
    }
    unsigned rehashInfo[2];
    ((Fn921440)FUN_00921440)((char*)this + 0x10, &rehashInfo[0], mnBucketCount, mnElementCount, 1);
    HTNode* n = (HTNode*)((void* (__thiscall*)(void*, int, unsigned, unsigned))
                          (*(void***)mpCoreAllocator)[8 / 4])(mpCoreAllocator, 0x20, 0, mnFlags);
    if (n != 0) {
        for (int k = 0; k < 7; ++k)
            ((unsigned*)n)[k] = v[k];
    }
    n->mpNext = 0;
    if (*(char*)&rehashInfo[0]) {
        bucket = hash % rehashInfo[1];
        ((Fn8de690)FUN_008de690)(this, rehashInfo[1]);
    }
    n->mpNext = mpBucketArray[bucket];
    mpBucketArray[bucket] = n;
    ++mnElementCount;
    *(void**)out = n;
    *((char*)out + 8) = 1;
    *(void**)((char*)out + 4) = &mpBucketArray[bucket];
    return out;
}


// @ 0x008db560
int* RBTree::insertUnique(int* out, int* parent, int* value, char flag)
{
    unsigned lazy = 0;
    if (flag == 0 && parent != (int*)((char*)this + 4) && *(int*)((char*)parent + 0x10) <= *value)
        lazy = 1;
    int node = (int)operator_new(
        0x18, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if ((int*)(node + 0x10) != 0) {
        *(int*)(node + 0x10) = *value;
        *(int*)(node + 0x14) = value[1];
    }
    RBTreeInsert((void*)node, (void*)parent, (void*)((char*)this + 4), (int)lazy);
    *(int*)((char*)this + 0x14) = *(int*)((char*)this + 0x14) + 1;
    *out = node;
    return out;
}


// @ 0x008db5e0
extern "C" void* FUN_008db5e0(int* lo, int* hi, int* pivot)
{
    for (;;) {
        int* a = lo;
        unsigned pv = *(unsigned*)((char*)pivot + 0xc);
        while (*(unsigned*)((char*)*a + 0xc) < pv)
            ++a;
        int* b = hi;
        unsigned bv = *(unsigned*)((char*)*(b - 1) + 0xc);
        while (pv < bv) {
            --b;
            bv = *(unsigned*)((char*)*(b - 1) + 0xc);
        }
        if (a >= b)
            return a;
        int t = *a;
        *a = *b;
        *b = t;
        ++a;
        lo = a;
    }
}


// @ 0x008db630
extern "C" void FUN_008db630(int* lo, int* mid, int* hi, int d)
{
    FUN_008daeb0(lo, mid, d);
    for (int* p = mid; p < hi; ++p) {
        int v = *p;
        if (*(unsigned*)((char*)v + 0xc) < *(unsigned*)((char*)*lo + 0xc)) {
            *p = *lo;
            FUN_008dadd0(lo, 0, (int)(mid - lo), 0, v, d);
        }
    }
    FUN_008daef0(lo, mid, d);
}


// @ 0x008db730
PFIndexModifiable_s008d_aff0::PFIndexModifiable_s008d_aff0(void* alloc)
{
    (void)alloc;
    vtbl = (void**)0x1436878;
    mpAllocator = alloc;
    ((void (__thiscall *)(void*, void*, unsigned, unsigned))0x925f30)((char*)this + 8, alloc, 0x80, 0x20);   // 0x925f30
    *(float*)((char*)this + 0x38) = *(float*)0x1485720;
    *(float*)((char*)this + 0x3c) = *(float*)0x1470f1c;
    *(void**)((char*)this + 0x44) = (char*)this + 8;
    *(unsigned*)((char*)this + 0x48) = 0;
    *(unsigned*)((char*)this + 0x34) = 0;
    *(unsigned*)((char*)this + 0x40) = 0;
    *(unsigned*)((char*)this + 0x30) = 1;
    *(void**)((char*)this + 0x2c) = (void*)0x154df28;
}


// @ 0x008db7b0
void* PFIndexModifiable_s008d_aff0::_virtual_dtor(int flags)
{
    ((Fn8dac90)FUN_008dac90)((char*)this + 0x28, *(void**)((char*)this + 0x2c),
                             *(unsigned*)((char*)this + 0x30));
    *(unsigned*)((char*)this + 0x34) = 0;
    unsigned n = *(unsigned*)((char*)this + 0x30);
    if (n > 1) {
        void* a = *(void**)((char*)this + 0x44);
        void* bucket = *(void**)((char*)this + 0x2c);
        unsigned sz = n * 4 + 4;
        ((void (__thiscall*)(void*, void*, unsigned))(((void**)(*(void**)a))[0xc / 4]))(a, bucket, sz);
    }
    ((Fn925e60)FUN_00925e60)((char*)this + 8);
    *(void**)this = (void*)0x13effb8;
    if (flags & 1)
        ZoneObject_delete(this);
    return this;
}


// @ 0x008db810
void* PFIndexModifiable_s008d_aff0::GetFileInfo(const void* key)
{
    HTNode* out[2];
    HT* ht = &mItemsMap;
    ht->find(&out[0], key);
    if (out[0] != ht->mpBucketArray[ht->mnBucketCount])
        return (char*)out[0] + 0xc;
    return 0;
}


// @ 0x008db850
bool PFIndexModifiable_s008d_aff0::RemoveFile(const void* key, void* out)
{
    HTNode* node[2];
    HT* ht = &mItemsMap;
    ht->find(&node[0], key);
    if (node[0] != ht->mpBucketArray[ht->mnBucketCount]) {
        *(unsigned*)((char*)out + 0x00) = *(unsigned*)((char*)node[0] + 0x0c);
        *(unsigned*)((char*)out + 0x04) = *(unsigned*)((char*)node[0] + 0x10);
        *(unsigned*)((char*)out + 0x08) = *(unsigned*)((char*)node[0] + 0x14);
        *(unsigned*)((char*)out + 0x0c) = *(unsigned*)((char*)node[0] + 0x18);
        HTIterator it;
        it.mpNode = node[0];
        it.mpKey = node[1];
        ht->erase(&it, (HTNode*)it.mpNode, (HTNode**)it.mpKey);
        return true;
    }
    return false;
}


// @ 0x008db8c0
HoleSet_s008d_aff0::HoleSet_s008d_aff0()
{
    mExtent = -1;
    char* p = (char*)this + 8;
    *(void**)(p + 4) = 0;
    *(void**)(p + 8) = 0;
    *(void**)(p + 0xc) = 0;
    *(void**)p = p;
    *(void**)((char*)this + 0xc) = p;
    *(void**)((char*)this + 0x10) = 0;
    *((char*)this + 0x14) = 0;
    *(void**)((char*)this + 0x18) = 0;
}


// @ 0x008db8f0
extern "C" void FUN_008db8f0(int* lo, int* hi, int depth, int d)
{
    while ((hi - lo) * 4 > 0x70 && depth > 0) {
        unsigned a = *(unsigned*)((char*)*lo + 0xc);
        unsigned b = *(unsigned*)((char*)*(hi - 1) + 0xc);
        int mid = (int)(hi - lo) / 2;
        unsigned c = *(unsigned*)((char*)lo[mid] + 0xc);
        int* piv;
        if (a < c) {
            if (c < b) piv = lo + mid;
            else if (a < b) piv = hi - 1;
            else piv = lo;
        } else {
            if (a < b) piv = lo;
            else if (c < b) piv = lo + mid;
            else piv = hi - 1;
        }
        int* split = (int*)FUN_008db5e0(lo, hi, (int*)piv);
        --depth;
        FUN_008db8f0(split, hi, depth, d);
        hi = split;
    }
    if (depth == 0)
        FUN_008db630(lo, hi, hi, d);
}


// @ 0x008db9b0
bool PFIndexModifiable_s008d_aff0::Read(void* buf, unsigned a3, unsigned count, char flag)
{
    (void)a3;
    unsigned* p = (unsigned*)buf;
    unsigned u = p[0];
    if (((u >> 2) & 1) == 0)
        return false;
    unsigned i = 1;
    unsigned firstOffset = 0xffffffff;
    if (u & 1) {
        firstOffset = p[1];
        i = 2;
    }
    unsigned pos = 0xffffffff;
    if ((u >> 1) & 1) {
        pos = p[i];
        ++i;
    }
    if (p[i] != 0)
        return false;
    if (count != 0) {
        unsigned* q = p + i + 1;
        unsigned sel = u;
        do {
            unsigned offset;
            if (sel & 1)
                offset = firstOffset;
            else { offset = *q; ++q; }
            if (((u >> 1) & 1) == 0) { pos = *q; ++q; }

            unsigned mi = q[0];
            unsigned f1 = q[1];
            unsigned f2 = q[2];
            unsigned f3 = q[3];
            q += 4;

            unsigned comp;
            if ((int)f2 < 0) {
                unsigned x = *q;
                ++q;
                f2 &= 0x7fffffff;
                comp = (x & 0xffff) | (((x >> 16) & 1) << 16);
            } else {
                comp = (f2 == f3) ? 0u : 0xffffu;
            }
            if (flag)
                comp = (comp & 0xffff) | 0x10000;

            unsigned val[7];
            val[0] = mi;
            val[1] = offset;
            val[2] = pos;
            val[3] = f1;
            val[4] = f2;
            val[5] = f3;
            val[6] = comp;
            void* out[3];
            mItemsMap.InsertUnique(&out[0], &val[0], 0);

            --count;
            if (count == 0)
                break;
            sel = u & 0xff;
        } while (true);
    }
    return true;
}


// @ 0x008dbb10
void* HT::GetFileInfoRef(const void* key)
{
    HTNode* out[3];
    out[0] = 0;
    out[1] = 0;
    find(&out[0], key);
    if (out[0] == mpBucketArray[mnBucketCount]) {
        const unsigned* k = (const unsigned*)key;
        // Retail builds the new record from an uninitialised stack dword and
        // keeps only its top byte in the compression field; mirror that read.
        volatile unsigned char junk[16];
        unsigned hi = ((unsigned)junk[15]) << 24;
        unsigned val[7];
        val[0] = k[0];
        val[1] = k[1];
        val[2] = k[2];
        val[3] = 0;
        val[4] = 0;
        val[5] = 0;
        val[6] = hi;
        InsertUnique(&out[0], &val[0], (unsigned)key & 0xffffff00u);
    }
    return (char*)out[0] + 0xc;
}


// @ 0x008dbcf0
int PFIndexModifiable_s008d_aff0::GetFiles(void* vec, void* filter)
{
    HTNode** pb = mItemsMap.mpBucketArray;
    HTNode* p = *pb;
    int n = 0;
    if (p == 0) {
        ++pb;
        while (*pb == 0) ++pb;
        p = *pb;
    }
    HTNode* end = mItemsMap.mpBucketArray[mItemsMap.mnBucketCount];
    while (p != end) {
        if (filter == 0 ||
            ((bool (__thiscall*)(void*, void*))(((void**)(*(void**)filter))[4 / 4]))(filter, p)) {
            if (vec != 0) {
                char* w = *(char**)((char*)vec + 4);
                if (w < *(char**)((char*)vec + 8)) {
                    *(char**)((char*)vec + 4) = w + 0xc;
                    if (w != 0) {
                        *(unsigned*)(w + 0) = *(unsigned*)((char*)p + 0x00);
                        *(unsigned*)(w + 4) = *(unsigned*)((char*)p + 0x04);
                        *(unsigned*)(w + 8) = *(unsigned*)((char*)p + 0x08);
                    }
                } else {
                    Vector_DoInsertValue(w, p);
                }
            }
            ++n;
        }
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
    return n;
}


// @ 0x008dbdb0
unsigned PFIndexModifiable_s008d_aff0::GetAllFiles(int a2, unsigned a3, int a4, void* vec)
{
    (void)a4;
    HTNode** big = (HTNode**)((void* (__thiscall*)(void*, unsigned, const char*, int))
                              (*(void***)mpAllocator)[8 / 4])(
        mpAllocator, mItemsMap.mnElementCount * 4, (const char*)0x140a248, 0);
    HTNode** pb = mItemsMap.mpBucketArray;
    HTNode* p = *pb;
    if (p == 0) {
        ++pb;
        while (*pb == 0) ++pb;
        p = *pb;
    }
    HTNode* end = mItemsMap.mpBucketArray[mItemsMap.mnBucketCount];
    HTNode** out = big;
    while (p != end) {
        *out++ = p;
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
    a3 &= 0xffffff00;
    FUN_008dbba0(big, (char*)big + a2 * 4, (void*)a3);
    for (HTNode** q = big; q < out; ++q) {
        char* w = *(char**)((char*)vec + 4);
        HTNode* v = *q;
        if (w < *(char**)((char*)vec + 8)) {
            *(char**)((char*)vec + 4) = w + 0xc;
            if (w != 0) {
                *(unsigned*)(w + 0) = *(unsigned*)((char*)v + 0x00);
                *(unsigned*)(w + 4) = *(unsigned*)((char*)v + 0x04);
                *(unsigned*)(w + 8) = *(unsigned*)((char*)v + 0x08);
            }
        } else {
            Vector_DoInsertValue(w, v);
        }
    }
    ((void (__thiscall*)(void*, void*, unsigned))(((void**)(*(void**)mpAllocator))[0xc / 4]))(
        mpAllocator, big, 0);
    return a3;
}


// @ 0x008dbeb0
void PFIndexModifiable_s008d_aff0::PutFileInfo(int a1, int* info)
{
    int c = info[2];
    int d = info[3];
    int a = info[0];
    int b = info[1];
    unsigned* out = (unsigned*)mItemsMap.GetFileInfoRef((const void*)a1);
    out[0] = a;
    out[1] = b;
    out[2] = c;
    out[3] = d;
}


// @ 0x008dbef0
// HoleTree::DoInsert - __thiscall (ecx = the tree header at HoleSet+4, ret 12). Forwards the
// header and the three arguments to FUN_008dbc20 with the 256-byte-aligned header value as the
// trailing flag, then returns its first argument (the out-parameter address).
struct HoleTreeDoInsertThunk {
    char d00[0x04];                                 // +0x00 tree header storage
    void* DoInsert(void** ppOut, void* pAfter, const int* pRange);   // 0x8dbef0
};

void* HoleTreeDoInsertThunk::DoInsert(void** ppOut, void* pAfter, const int* pRange)
{
    unsigned aligned = (unsigned)this & 0xffffff00u;
    ((Fn8dbc20)FUN_008dbc20)(this, ppOut, pAfter, (void*)pRange, aligned);
    return ppOut;
}


// @ 0x008dbf20
HoleNode* HoleSet_s008d_aff0::AllocAt(int size)
{
    HoleNode* anchor = (HoleNode*)((char*)this + 8);
    HoleNode* p = mRoot;
    HoleNode* best = anchor;
    unsigned bestSize = 0xffffffff;
    if (p != anchor) {
        do {
            unsigned holeSize = p->mnSize;
            if (holeSize >= (unsigned)size && holeSize < bestSize) {
                best = p;
                bestSize = holeSize;
                if (holeSize == (unsigned)size)
                    break;
            }
            p = (HoleNode*)RBTreeIncrement(p);
        } while (p != anchor);
        if (best != anchor) {
            unsigned pos = best->mnPos;
            unsigned holeSize = best->mnSize;
            HoleNode* next = (HoleNode*)RBTreeIncrement(best);
            --mnSize;
            RBTreeIncrement(best);
            RBTreeErase(best, (char*)this + 8);
            operator_delete__(best);
            unsigned rest = holeSize - (unsigned)size;
            if (rest != 0) {
                unsigned newPos = pos + (unsigned)size;
                unsigned pair[2];
                pair[0] = newPos;
                pair[1] = rest;
                unsigned aligned = newPos & 0xffffff00u;
                ((Fn8dbc20)FUN_008dbc20)((char*)this + 4, &aligned, next, &pair[0], aligned);
            }
            return (HoleNode*)pos;
        }
    }
    int old = mExtent;
    mExtent = old + size;
    return (HoleNode*)old;
}


// @ 0x008dc000
void HoleSet_s008d_aff0::Release(unsigned pos, int size)
{
    HoleNode* anchor = (HoleNode*)((char*)this + 8);
    HoleNode* p = mTreeRoot;
    HoleNode* slot = anchor;
    while (p != 0) {
        if ((int)p->mnPos < (int)pos) {
            p = p->mpLeft;
        } else {
            slot = p;
            p = p->mpRight;
        }
    }
    unsigned base = pos;
    int sz = size;
    if (slot != mRoot) {
        HoleNode* prev = (HoleNode*)RBTreeDecrement(slot);
        unsigned pp = prev->mnPos;
        unsigned ps = prev->mnSize;
        if (pp + ps == pos) {
            --mnSize;
            sz = ps + size;
            base = pp;
            RBTreeIncrement(prev);
            RBTreeErase(prev, (char*)this + 8);
            operator_delete__(prev);
        }
    }
    if (slot == anchor) {
        if (pos + size == (unsigned)mExtent) {
            mExtent -= size;
            return;
        }
    } else if (base + sz == slot->mnPos) {
        sz += slot->mnSize;
        HoleNode* next = (HoleNode*)RBTreeIncrement(slot);
        --mnSize;
        RBTreeIncrement(slot);
        RBTreeErase(slot, (char*)this + 8);
        operator_delete__(slot);
        slot = next;
    }
    unsigned pair[2];
    pair[0] = base;
    pair[1] = (unsigned)sz;
    unsigned aligned = pos & 0xffffff00u;
    ((Fn8dbc20)FUN_008dbc20)((char*)this + 4, &aligned, slot, &pair[0], aligned);
}


// @ 0x008dc120
void HoleSet_s008d_aff0::MergeFrom(HoleSet_s008d_aff0* other)
{
    HoleNode* anchor = (HoleNode*)((char*)other + 8);
    for (HoleNode* p = other->mRoot; p != anchor; p = (HoleNode*)RBTreeIncrement(p))
        Release(p->mnPos, p->mnSize);
    HoleNode* q = other->mTreeRoot;
    while (q != 0) {
        ((RBTreeBase*)((char*)other + 4))->DoNukeSubtree(*(void**)q);
        HoleNode* n = *(HoleNode**)((char*)q + 4);
        operator_delete__(q);
        q = n;
    }
    other->mTreeRoot = 0;
    *(char*)((char*)other + 0x14) = 0;
    *(void**)((char*)other + 0x18) = 0;
    *(void**)((char*)other + 0x0c) = anchor;
    *(void**)((char*)other + 0x08) = anchor;
}
