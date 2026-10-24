// Slice s008d81d0 (0x8d81d0..0x8d91d7) - Resource::DatabasePackedFile packed-file helpers.
//
// Spore-specific code. Layout follows the retail DBFP object (vptr pair + refcount, then the
// packed-file state, the memory/base fields at +0x264..+0x26c, the two mutexes, index, and the
// record multimap / hole tables). Offsets confirmed against the disassembly.
// Callees outside this slice are declared as thiscall members with the right arity so the
// generated call sites have no trailing 'add esp'.
//
// Functions (VA, name):
//   008d81d0  DatabasePackedFile::Lock
//   008d8200  DatabasePackedFile::CreateRecordWrite
//   008d8250  DatabasePackedFile::CreateRecordWriteData
//   008d82a0  DatabasePackedFile::CreateRecordReadCopy
//   008d82e0  DatabasePackedFile::CreateRecordRead
//   008d8320  DatabasePackedFile::ReadHeaders
//   008d8360  DatabasePackedFile::CreateIndex
//   008d8390  DatabasePackedFile::DestroyIndex
//   008d83b0  DatabasePackedFile::MakeIndexModifiable
//   008d84a0  DatabasePackedFile::AllocSpace
//   008d84d0  DatabasePackedFile::FreeSpace
//   008d8530  DatabasePackedFile::SetHoleTable
//   008d8570  DatabasePackedFile::ShouldCompress
//   008d85a0  DatabasePackedFile::Attach
//   008d8650  DatabasePackedFile::Dispose
//   008d86c0  DatabasePackedFile::SetStream
//   008d8710  DatabasePackedFile::GetKeyList
//   008d8770  DatabasePackedFile::GetKeyListSortedByPosition
//   008d87c0  DatabasePackedFile::Verify
//   008d8820  DatabasePackedFile::Decompress
//   008d8890  DatabasePackedFile::SetPosition
//   008d88d0  DatabasePackedFile::ReadBytes
//   008d8930  DatabasePackedFile::GetSize
//   008d8950  DatabasePackedFile::Reset
//   008d8980  DatabasePackedFile::Open
//   008d8b30  DatabasePackedFile::Sync
//   008d8b70  DatabasePackedFile::DeleteRecord
//   008d8c50  DatabasePackedFile::ReadHeaderRecord
//   008d8e20  DatabasePackedFile::WriteEmptyHeaderRecord
//   008d8ee0  DatabasePackedFile::WriteHeaderRecord
//   008d9000  DatabasePackedFile::VerifyIndexRecordIntegrity
//   008d9050  DatabasePackedFile::ReadAt
//   008d90e0  DatabasePackedFile::ReadRecordRaw
//   008d9170  DatabasePackedFile::ReadRecordSpan

#include "types.h"

struct IAlloc {
    virtual void a0();
    virtual void a1();
    virtual void* Alloc(unsigned size, const char* name, unsigned flags);
    virtual void Free(void* p, unsigned size);
};

struct Key { uint32_t inst, type, group; };

struct IdxEntry { int pos, size, usize; short flags; char compressed; };

struct IStream {
    virtual void s0();                              // +0x00
    virtual int AddRef();                           // +0x04
    virtual int Release();                          // +0x08
    virtual void s3();                              // +0x0c
    virtual int GetAccessFlags();                   // +0x10
    virtual int GetState();                         // +0x14 (-2 sentinel)
    virtual bool Close();                           // +0x18
    virtual int GetSize();                          // +0x1c
    virtual void SetSize(int n);                    // +0x20
    virtual void s9();                              // +0x24
    virtual bool SetPosition(int pos, int origin);  // +0x28
    virtual void s11();                             // +0x2c
    virtual int Read(void* buf, int size);          // +0x30
    virtual void s13();                             // +0x34
    virtual bool ReadRaw(void* buf, int size);      // +0x38
};

struct Index {
    virtual void i0();                              // +0x00
    virtual bool IsModifiable();                    // +0x04
    virtual void i2();                              // +0x08
    virtual int GetSize();                          // +0x0c
    virtual void Op10();                            // +0x10
    virtual void i5();                              // +0x14
    virtual void i6();                              // +0x18
    virtual int GetKeyList(int a, int b);           // +0x1c
    virtual int GetKeyListSortedByPosition(int a);  // +0x20
    virtual void i9();                              // +0x24
    virtual void* Find(const Key* k);               // +0x28
    virtual void i11();                             // +0x2c
    virtual bool GetEntry(const Key* k, IdxEntry* e);// +0x30
    virtual void Op34(void* buf, int len, int size, int flag); // +0x34
    virtual bool Serialize(void** ppBuf, int* pLen, int size, int flag); // +0x38
    virtual void i15();                             // +0x3c
    virtual bool VerifyRange(int a, int b);         // +0x40
};

struct PFRecordWrite {
    void* Init(int a, int b, int c, void* owner);                 // 0x8dcea0
    void* InitData(int a, int b, int c, int d, void* owner);      // 0x8dd0d0
};
struct PFRecordRead {
    void* Init(int a, int b, void* owner);                        // 0x8dcc80
    void* Init2(int a, int b, void* owner);                       // 0x8dcdc0
};

struct PFIndexModifiable {
    void* Init(void* alloc);                                      // 0x8db730
};

struct HoleSet {
    int mField0;                       // +0
    char d[0x1c];
    HoleSet();
    ~HoleSet();
    void Reset(int n);                 // 0x8db3a0
    bool AddHole(int pos, int size);   // 0x8dc000
    int Alloc(int size);               // 0x8dbf20
    int GetTotalSize();                // 0x8dae40
};

struct RbNode {
    RbNode* right;
    RbNode* left;
    RbNode* parent;
    int color;
    Key key;
    void* value;                       // +0x1c
};

struct RbAnchor {
    RbNode* right;
    RbNode* left;
    RbNode* parent;
    int color;
};

struct RecMap {
    uint32_t cmp;
    RbAnchor mAnchor;
    int mnSize;
    IAlloc* mpAlloc;
    int mnFlags;
    RbNode* Anchor() { return (RbNode*)&mAnchor; }
    RbNode** find(RbNode** out, const Key* k);   // 0xa21dc0
    RecMap() {}
};

struct Mutex {
    char d[0x30];
    int Lock(const void* timeout);   // 0x9221b0
    int Unlock();                    // 0x922270
};

struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
};
struct AutoRef { IStream* p; };

struct FileStream {
    void* vt;              // +0x00
    char d[0x224];         // total 0x228
};

struct PFHeader {
    uint32_t f[10];
};

struct HoleTable {
    int mExtent;           // +0x334
    float mRatio;          // +0x338
    HoleSet mHoles;        // +0x33c
};

struct Refpack {
    void* vt;
    bool IsValidHeader(const void* buf, int size);                               // 0x92cad0
    int DecompressData(const void* buf, int size, void* dst, int dsize, int f);  // 0x92ca60
};

struct DBase {
    void* volatile vt0;    // +0
    void* volatile vt4;    // +4
    volatile long mRefCount; // +8
};
struct DBase1 : DBase {};

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

extern "C" void* __cdecl ICoreAllocator_Alloc_Named(unsigned size, void* alloc, const char* name); // 0x925fe0
extern "C" void* __cdecl memset_pf(void* dst, int val, unsigned n);   // 0x11e073e
extern "C" void* __cdecl memcpy_pf(void* dst, const void* src, unsigned n); // 0x11e0744
extern "C" int   __cdecl FindEmbeddedPackageHeader(const wchar_t* path);    // 0x8dd510
extern const int kTimeoutNone[];          // 0x1436788
extern char vtbl_Refpack[];               // 0x140a0e8
extern char g_ReadHeaderRecordGuard;      // 0x1667a90

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
    char* mpMemoryBase;                 // +0x264
    unsigned mnMemorySize;              // +0x268
    unsigned mnMemoryPosition;          // +0x26c
    Mutex mMutex;                       // +0x270
    Mutex mFileMutex;                   // +0x2a0
    Index* mpIndex;                     // +0x2d0
    bool mbIndexHasChanged;             // +0x2d4
    unsigned mnUserVersionMajor;        // +0x2d8
    unsigned mnUserVersionMinor;        // +0x2dc
    bool mbEnableCompression;           // +0x2e0
    float mfMinRatioToUseCompression;   // +0x2e4
    RecMap mMap;                        // +0x2e8
    PFHeader mHeaderBlock;              // +0x308
    bool mbFlag330;                     // +0x330
    HoleTable mActive;                  // +0x334
    HoleSet mHoleB;                     // +0x35c
    bool mbHolesHaveChanged;            // +0x37c
    bool mbBusyCompacting;              // +0x37d
    uint32_t mpManager;                 // +0x380

    HoleSet& HoleA() { return mActive.mHoles; }
    HoleSet& HoleB() { return mHoleB; }

    // this slice
    void Lock(bool b);
    void* CreateRecordWrite(int flag, int a, int b, int c);
    void* CreateRecordWriteData(int flag, int a, int b, int c);
    void* CreateRecordReadCopy(int unused, int a, int b);
    void* CreateRecordRead(int unused, int a, int b);
    bool ReadHeaders();
    void* CreateIndex(int unused);
    void DestroyIndex(Index* idx);
    void MakeIndexModifiable();
    bool AllocSpace(int* pOut, int size);
    bool FreeSpace(int pos, int size, bool flag);
    bool SetHoleTable(int extent, float ratio);
    int ShouldCompress(int unused, unsigned size);
    bool Attach(bool attach, uint32_t mgr, bool arg3);
    bool Dispose();
    bool SetStream(IStream* s);
    int GetKeyList(int a, int b);
    int GetKeyListSortedByPosition(int a);
    bool Verify();
    bool Decompress(int unused, const void* buf, int size, int expectedSize, void* dest);
    bool SetPosition(int pos);
    int ReadBytes(void* dst, int size);
    int GetSize();
    bool Reset();
    bool Open(int access, int mode, bool autoOpen);
    bool Sync();
    bool DeleteRecord(const Key* key);
    bool ReadHeaderRecord();
    bool WriteEmptyHeaderRecord();
    bool WriteHeaderRecord();
    bool VerifyIndexRecordIntegrity();
    bool ReadAt(void* dst, int pos, int size);
    bool ReadRecordRaw(void* dst, int pos, int size);
    bool ReadRecordSpan(const Key* key, void* dst, int size);
};

typedef char chk_sz[(sizeof(DatabasePackedFile) == 0x384) ? 1 : -1];

typedef void (__thiscall *TF0)(void*);
typedef int  (__thiscall *TFi0)(void*);
typedef char (__thiscall *TFc0)(void*);
typedef bool (__thiscall *TFb0)(void*);
typedef void (__thiscall *TF1)(void*, int);
typedef int  (__thiscall *TFi1)(void*, int);
typedef bool (__thiscall *TFb1)(void*, int);
typedef void (__thiscall *TF2)(void*, int, int);
typedef bool (__thiscall *TFb2)(void*, int, int);
typedef int  (__thiscall *TFi2)(void*, int, int);
typedef void (__thiscall *TF3)(void*, int, int, int);
typedef bool (__thiscall *TFb3)(void*, int, int, int);
typedef bool (__thiscall *TFb4)(void*, int, int, int, int);

// @ 0x008d81d0
void DatabasePackedFile::Lock(bool b)
{
    if (b)
        mMutex.Lock(kTimeoutNone);
    else
        mMutex.Unlock();
}

// @ 0x008d8200
void* DatabasePackedFile::CreateRecordWrite(int flag, int a, int b, int c)
{
    if (flag & 2) {
        PFRecordWrite* p = (PFRecordWrite*)ICoreAllocator_Alloc_Named(0x27c, mpAllocator, "Resource/PFRecordWrite");
        if (p)
            return p->Init(a, b, c, this);
    }
    return 0;
}

// @ 0x008d8250
void* DatabasePackedFile::CreateRecordWriteData(int flag, int a, int b, int c)
{
    if (flag & 2) {
        PFRecordWrite* p = (PFRecordWrite*)ICoreAllocator_Alloc_Named(0x27c, mpAllocator, "Resource/PFRecordWrite");
        if (p)
            return p->InitData(a, b, 1, c, this);
    }
    return 0;
}

// @ 0x008d82a0
void* DatabasePackedFile::CreateRecordReadCopy(int unused, int a, int b)
{
    PFRecordRead* p = (PFRecordRead*)ICoreAllocator_Alloc_Named(0x70, mpAllocator, "Resource/PFRecordRead");
    if (p)
        return p->Init(a, b, this);
    return 0;
}

// @ 0x008d82e0
void* DatabasePackedFile::CreateRecordRead(int unused, int a, int b)
{
    PFRecordRead* p = (PFRecordRead*)ICoreAllocator_Alloc_Named(0x70, mpAllocator, "Resource/PFRecordRead");
    if (p)
        return p->Init2(a, b, this);
    return 0;
}

// @ 0x008d8320
bool DatabasePackedFile::ReadHeaders()
{
    if (!((TFc0)(*(void***)this)[0x68 / 4])(this)) {
        if (mpIndex == 0)
            mpIndex = (Index*)((TFi1)(*(void***)this)[0x84 / 4])(this, 3);
        return false;
    }
    return ((TFc0)(*(void***)this)[0x78 / 4])(this);
}

// @ 0x008d8360
void* DatabasePackedFile::CreateIndex(int unused)
{
    PFIndexModifiable* p = (PFIndexModifiable*)ICoreAllocator_Alloc_Named(0x4c, mpAllocator, "Resource/PFIndexModifiable");
    if (p)
        return p->Init(mpAllocator);
    return 0;
}

// @ 0x008d8390
void DatabasePackedFile::DestroyIndex(Index* idx)
{
    if (idx)
        ((TF1)(*(void***)idx)[0])(idx, 1);
}

// @ 0x008d83b0
void DatabasePackedFile::MakeIndexModifiable()
{
    mMutex.Lock(kTimeoutNone);
    if (mpIndex && mpIndex->IsModifiable()) {
        mMutex.Unlock();
        return;
    }
    {
        Index* newIdx = (Index*)((TFi1)(*(void***)this)[0x84 / 4])(this, 3);
        if (mpIndex) {
            int size = mpIndex->GetSize();
            if (size) {
                void* buf = 0;
                int len = 0;
                if (mpIndex->Serialize(&buf, &len, size, 0)) {
                    newIdx->Op34(buf, len, size, 0);
                    mpAllocator->Free(buf, 0);
                }
            }
            ((TF1)(*(void***)this)[0x88 / 4])(this, (int)mpIndex);
        }
        mpIndex = newIdx;
        ((TF0)(*(void***)this)[0x90 / 4])(this);
    }
    mMutex.Unlock();
}

// @ 0x008d84a0
bool DatabasePackedFile::AllocSpace(int* pOut, int size)
{
    bool r = false;
    if (mnAccessFlags != 0 && (mnAccessFlags & 2)) {
        *pOut = mActive.mHoles.Alloc(size);
        r = true;
    }
    return r;
}

// @ 0x008d84d0
bool DatabasePackedFile::FreeSpace(int pos, int size, bool flag)
{
    if (pos == 0 || size == 0)
        return true;
    if (mActive.mExtent & 0x10) {
        if (flag) {
            mActive.mHoles.AddHole(pos, size);
            mbHolesHaveChanged = true;
            return true;
        }
        mHoleB.AddHole(pos, size);
        mbHolesHaveChanged = true;
        return true;
    }
    mActive.mHoles.AddHole(pos, size);
    mbHolesHaveChanged = true;
    return true;
}

// @ 0x008d8530
bool DatabasePackedFile::SetHoleTable(int extent, float ratio)
{
    mActive.mExtent = extent;
    if (ratio >= 0.0f)
        mActive.mRatio = ratio;
    return true;
}

// @ 0x008d8570
int DatabasePackedFile::ShouldCompress(int unused, unsigned size)
{
    if (mbEnableCompression && (unsigned)(size - 0x32) <= 0xf423ce)
        return 1;
    return 0;
}

// @ 0x008d85a0
bool DatabasePackedFile::Attach(bool attach, uint32_t mgr, bool arg3)
{
    bool r = false;
    if (attach) {
        uint32_t old = mpManager;
        if (old != 0 && mgr != old)
            ((TF3)(*(void***)this)[0x44 / 4])(this, 0, (int)old, (int)*(uint32_t*)&arg3);
        if (mgr == 0)
            return r;
        if (arg3) {
            mpManager = mgr;
            r = true;
        } else {
            r = ((TFb3)(*(void***)mgr)[0x50 / 4])((void*)mgr, 1, (int)this, 0);
        }
    } else {
        if (mgr != 0 && mgr != mpManager)
            return false;
        if (arg3) {
            mpManager = 0;
            r = true;
        } else {
            r = ((TFb3)(*(void***)mpManager)[0x50 / 4])((void*)mpManager, 0, (int)this, 0);
        }
    }
    return r;
}

// @ 0x008d8650
bool DatabasePackedFile::Dispose()
{
    if (mbInitialized) {
        if (mnAccessFlags != 0)
            ((TF0)(*(void***)this)[0x1c / 4])(this);
        ((TF1)(*(void***)this)[0x88 / 4])(this, (int)mpIndex);
        mpIndex = 0;
        if (mpMemoryLocation.p) {
            IStream* p = mpMemoryLocation.p;
            mpMemoryLocation.p = 0;
            p->Release();
        }
        mbInitialized = false;
    }
    return true;
}

// @ 0x008d86c0
bool DatabasePackedFile::SetStream(IStream* s)
{
    if (mnAccessFlags != 0)
        return false;
    IStream* old = mpMemoryLocation.p;
    if (s != old) {
        if (s)
            s->AddRef();
        mpMemoryLocation.p = s;
        if (old)
            old->Release();
    }
    return true;
}

// @ 0x008d8710
int DatabasePackedFile::GetKeyList(int a, int b)
{
    mMutex.Lock(kTimeoutNone);
    if (mnAccessFlags != 0) {
        int r = mpIndex->GetKeyList(a, b);
        mMutex.Unlock();
        return r;
    }
    mMutex.Unlock();
    return 0;
}

// @ 0x008d8770
int DatabasePackedFile::GetKeyListSortedByPosition(int a)
{
    mMutex.Lock(kTimeoutNone);
    if (mnAccessFlags != 0) {
        int r = mpIndex->GetKeyListSortedByPosition(a);
        mMutex.Unlock();
        return r;
    }
    mMutex.Unlock();
    return 0;
}

// @ 0x008d87c0
bool DatabasePackedFile::Verify()
{
    mMutex.Lock(kTimeoutNone);
    bool r = false;
    if (mMap.mnSize == 0 && mnAccessFlags != 0) {
        int div = mActive.mHoles.mField0;
        int total = mActive.mHoles.GetTotalSize();
        if ((float)total / (float)div > mActive.mRatio)
            r = true;
    }
    mMutex.Unlock();
    return r;
}

// @ 0x008d8820
bool DatabasePackedFile::Decompress(int unused, const void* buf, int size, int expectedSize, void* dest)
{
    Refpack rp;
    bool r = false;
    rp.vt = vtbl_Refpack;
    if (rp.IsValidHeader(buf, size)) {
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
bool DatabasePackedFile::SetPosition(int pos)
{
    if (mpMemoryBase) {
        if ((unsigned)pos >= mnMemorySize)
            return false;
        mnMemoryPosition = pos;
        return true;
    }
    return mpMemoryLocation.p->SetPosition(pos, 0);
}

// @ 0x008d88d0
int DatabasePackedFile::ReadBytes(void* dst, int size)
{
    if (mpMemoryBase) {
        unsigned pos = mnMemoryPosition;
        unsigned limit = mnMemorySize;
        unsigned n = size;
        if (pos + n > limit)
            n = limit - pos;
        memcpy_pf(dst, (char*)(pos + (unsigned)mpMemoryBase), n);
        mnMemoryPosition += n;
        return n;
    }
    return mpMemoryLocation.p->Read(dst, size);
}

// @ 0x008d8930
int DatabasePackedFile::GetSize()
{
    if (mpMemoryBase)
        return mnMemorySize;
    return mpMemoryLocation.p->GetSize();
}

// @ 0x008d8950
bool DatabasePackedFile::Reset()
{
    if (mpMemoryBase) {
        mnMemoryPosition = 0;
        return true;
    }
    return mpMemoryLocation.p->Close();
}

// @ 0x008d8980
bool DatabasePackedFile::Open(int access, int mode, bool autoOpen)
{
    if (mnAccessFlags != 0)
        return false;
    bool r = false;
    if (mpMemoryBase) {
        if ((access & 3) == 1 && (mode == 3 || mode == 6) &&
            ((TFb0)(*(void***)this)[0x64 / 4])(this)) {
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
        IStream* s = mpMemoryLocation.p;
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
            ((TF1)(*(void***)&mFile)[0x3c / 4])(&mFile, (int)mPath.mpBegin);
            if (!((TFb4)(*(void***)&mFile)[0x4c / 4])(&mFile, mnAccessFlags, mode, 1, 2)) {
                mnAccessFlags = 0;
                return false;
            }
            mpMemoryLocation.p = (IStream*)&mFile;
        }
        if (GetSize() != 0) {
            r = ((TFb0)(*(void***)this)[0x64 / 4])(this);
            if (r)
                return true;
            mpIndex->Op10();
            if (mbEnableWriteOnCorruptFiles && (mnAccessFlags & 2)) {
                r = ((TFb0)(*(void***)this)[0x6c / 4])(this);
                if (r) {
                    ((TF0)(*(void***)this)[0x90 / 4])(this);
                    mbIndexHasChanged = true;
                    return true;
                }
            }
        } else {
            if (!(mnAccessFlags & 2)) {
                r = false;
            } else {
                r = ((TFb0)(*(void***)this)[0x6c / 4])(this);
                if (r)
                    return true;
            }
        }
    }
    Reset();
    if (!r)
        mnAccessFlags = 0;
    return r;
}

// @ 0x008d8b30
bool DatabasePackedFile::Sync()
{
    bool r = false;
    if (mnAccessFlags != 0) {
        while (mMap.mnSize != 0) {
            RbNode* n = mMap.mAnchor.left;
            ((TF1)(*(void***)this)[0x3c / 4])(this, (int)n->value);
        }
        r = true;
    }
    return r;
}

// @ 0x008d8b70
bool DatabasePackedFile::DeleteRecord(const Key* key)
{
    mMutex.Lock(kTimeoutNone);
    bool r = false;
    if ((mnAccessFlags & 2) && mnAccessFlags != 0) {
        if (mpIndex->Find(key)) {
            RbNode* tmp;
            RbNode** it = mMap.find(&tmp, key);
            if (*it == mMap.Anchor()) {
                ((TF0)(*(void***)this)[0x8c / 4])(this);
                IdxEntry e;
                e.pos = 0; e.size = 0; e.usize = 0; e.flags = 0; e.compressed = 0;
                if (mpIndex->GetEntry(key, &e)) {
                    FreeSpace(e.pos, e.size, e.compressed == 0);
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
bool DatabasePackedFile::ReadHeaderRecord()
{
    char buf[0x60];
    if (mpMemoryBase) {
        if ((unsigned)mpStream >= mnMemorySize)
            return false;
        mnMemoryPosition = mpStream;
    } else {
        if (!mpMemoryLocation.p->SetPosition(mpStream, 0))
            return false;
    }
    memset_pf(buf, 0, 0x60);
    if (ReadBytes(buf, 0x60) != 0x60)
        return false;
    uint32_t* b = (uint32_t*)buf;
    mHeaderBlock.f[0] = b[3];
    mHeaderBlock.f[1] = b[4];
    mHeaderBlock.f[2] = b[6];
    mHeaderBlock.f[3] = 0;
    mHeaderBlock.f[4] = b[7];
    mHeaderBlock.f[5] = 0;
    mHeaderBlock.f[6] = b[8];
    mHeaderBlock.f[7] = b[16];
    if (mHeaderBlock.f[7] == 0)
        mHeaderBlock.f[7] = b[10];
    mHeaderBlock.f[8] = b[9];
    mHeaderBlock.f[9] = b[11];
    if (((TFb1)(*(void***)this)[0x74 / 4])(this, (int)buf))
        return true;
    mpStream = FindEmbeddedPackageHeader(mPath.mpBegin);
    if (mpStream == -1) {
        mpStream = 0;
        return false;
    }
    if (g_ReadHeaderRecordGuard)
        return false;
    g_ReadHeaderRecordGuard = 1;
    bool r = ((TFb0)(*(void***)this)[0x68 / 4])(this);
    g_ReadHeaderRecordGuard = 0;
    return r;
}

// @ 0x008d8e20
bool DatabasePackedFile::WriteEmptyHeaderRecord()
{
    for (int i = 0; i < 10; ++i)
        mHeaderBlock.f[i] = 0;
    mHeaderBlock.f[0] = mnUserVersionMajor;
    mHeaderBlock.f[1] = mnUserVersionMinor;
    for (int i = 2; i < 10; ++i)
        mHeaderBlock.f[i] = 0;
    mbFlag330 = true;
    bool r = ((TFb0)(*(void***)this)[0x70 / 4])(this);
    if (r) {
        if (mpMemoryBase)
            return false;
        r = ((TFb1)(*(void***)mpMemoryLocation.p)[0x20 / 4])(mpMemoryLocation.p, 0x60);
    }
    return r;
}

// @ 0x008d8ee0
bool DatabasePackedFile::WriteHeaderRecord()
{
    if (!(mnAccessFlags & 2))
        return false;
    if (mpMemoryBase == 0) {
        if (((TFi0)(*(void***)mpMemoryLocation.p)[0x14 / 4])(mpMemoryLocation.p) == -2)
            return false;
    }
    if (!mbFlag330)
        return true;
    if (!SetPosition(mpStream))
        return false;
    char buf[0x60];
    memset_pf(buf, 0, 0x60);
    uint32_t* b = (uint32_t*)buf;
    b[0] = 0x46504244;
    b[1] = 3;
    b[2] = 0;
    b[3] = mnUserVersionMajor;
    b[4] = mnUserVersionMinor;
    b[8] = mHeaderBlock.f[6];
    b[9] = mHeaderBlock.f[8];
    b[10] = (mHeaderBlock.f[7] & 0x80000000) ? 0 : mHeaderBlock.f[7];
    b[11] = mHeaderBlock.f[9];
    b[15] = 3;
    b[16] = mHeaderBlock.f[7];
    b[17] = mHeaderBlock.f[8];
    b[19] = mHeaderBlock.f[7];
    if (mpMemoryBase)
        return false;
    if (!((TFb2)(*(void***)mpMemoryLocation.p)[0x38 / 4])(mpMemoryLocation.p, (int)buf, 0x60))
        return false;
    mbFlag330 = false;
    return true;
}

// @ 0x008d9000
bool DatabasePackedFile::VerifyIndexRecordIntegrity()
{
    int size;
    if (mpMemoryBase)
        size = mnMemorySize;
    else
        size = mpMemoryLocation.p->GetSize();
    return mpIndex->VerifyRange(0, size);
}

// @ 0x008d9050
bool DatabasePackedFile::ReadAt(void* dst, int pos, int size)
{
    mFileMutex.Lock(kTimeoutNone);
    bool r;
    if (mnAccessFlags != 0) {
        int abs = mpStream + pos;
        if (mpMemoryBase) {
            if ((unsigned)abs >= mnMemorySize)
                goto fail;
            mnMemoryPosition = abs;
        } else {
            if (!mpMemoryLocation.p->SetPosition(abs, 0))
                goto fail;
        }
        r = ReadBytes(dst, size) != -1;
        mFileMutex.Unlock();
        return r;
    }
fail:
    mFileMutex.Unlock();
    return false;
}

// @ 0x008d90e0
bool DatabasePackedFile::ReadRecordRaw(void* dst, int pos, int size)
{
    mFileMutex.Lock(kTimeoutNone);
    bool r;
    if (mnAccessFlags != 0 && (mnAccessFlags & 2)) {
        if (SetPosition(mpStream + pos)) {
            if (mpMemoryBase == 0)
                r = mpMemoryLocation.p->ReadRaw(dst, size);
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
bool DatabasePackedFile::ReadRecordSpan(const Key* key, void* dst, int size)
{
    mMutex.Lock(kTimeoutNone);
    if (mnAccessFlags != 0) {
        const IdxEntry* e = (const IdxEntry*)mpIndex->Find(key);
        unsigned esize = e->size;
        unsigned n = size;
        if (n > esize)
            n = esize;
        bool r = ReadAt(dst, e->pos, n);
        mMutex.Unlock();
        return r;
    }
    mMutex.Unlock();
    return false;
}
