// Slice s008d91e0 (0x8d91e0..0x8da15c) - Resource::DatabasePackedFile / EA::ResourceMan packed-file code.
//
// Spore-specific code (no upstream OSS source). Layout follows the 2008 dev PDB class
// EA::ResourceMan::DatabasePackedFile; the retail offsets were confirmed against the asm
// (hole tables live at +0x33c / +0x35c, a float at +0x338, header dwords 0x308..0x32c).
// Callees outside this slice are declared as thiscall members with the right arity.
//
// Functions (VA, name):
//   008d91e0  DatabasePackedFile::CompressRecordData
//   008d9320  DatabasePackedFile::ReadCompressed
//   008d93a0  RecMap::erase
//   008d93e0  DatabasePackedFile::~DatabasePackedFile
//   008d94a0  DatabasePackedFile::CloseInternal
//   008d9560  DatabasePackedFile::GetOpenCount
//   008d95f0  DatabasePackedFile::WriteIndexRecord
//   008d9770  DatabasePackedFile::InitializeHoleTable
//   008d9850  DatabasePackedFile::TryCompress
//   008d98f0  RecMap::DoInsertValue
//   008d99c0  DatabasePackedFile::SetLocation
//   008d9a10  DatabasePackedFile::CloseRecord
//   008d9f20  RecMap::insert
//   008d9f80  DatabasePackedFile::DatabasePackedFile

#include "types.h"

struct IAlloc {
    virtual void a0();
    virtual void a1();
    virtual void* Alloc(unsigned size, const char* name, unsigned flags);
    virtual void Free(void* p, unsigned size);
};

struct Key { uint32_t inst, type, group; };

struct IdxEntry { int pos, size, usize; short flags; char compressed; };

// Stream-like object with the vtable slots the packed file uses.
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
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);

struct RbIter {
    RbNode* p;
    RbIter(RbNode* q) : p(q) {}
    RbIter(const RbIter& o) : p(o.p) {}
};

struct PFPair { Key key; Record* value; };

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

// eastl::multimap<Key, PFRecordBase*> at DatabasePackedFile+0x2e8
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
    __declspec(noinline) void DoInsertValue(RbNode** out, RbNode* parent, const PFPair* v, bool bForceToLeft);   // 0x8d98f0
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

struct Mutex {
    char d[0x30];
    Mutex(void*, bool);       // 0x9222a0
    ~Mutex();                 // 0x922130
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

struct Refpack {
    void* vt;
    int CompressData(const void* src, unsigned size, void* dst, unsigned dstSize, int level);   // 0x92c9f0
};
extern char vtbl_Refpack[];            // 0x140a0e8

IAlloc* GetDefaultAllocator();                                  // 0x925cb0

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
    Mutex mMutex;                       // +0x270
    Mutex mFileMutex;                   // +0x2a0
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
    Mutex& MutexM() { return mMutex; }
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

typedef char chk_sz[(sizeof(DatabasePackedFile) == 0x384) ? 1 : -1];

// @ 0x008d91e0
bool DatabasePackedFile::CompressRecordData(const void* src, unsigned size, void** ppOut, unsigned* pOutSize, uint16_t* pFlags)
{
    bool bAlloc = (*ppOut == 0);
    if (size - 1 <= 0x26259fe) {
        Refpack rp;
        rp.vt = vtbl_Refpack;
        *pFlags = 0xffff;
        unsigned n = rp.CompressData(src, size, 0, 0, 1);
        if (bAlloc && n) {
            *pOutSize = n;
            *ppOut = mpAllocator->Alloc(n, kStrPackedRecord, 0);
        }
        if (*ppOut) {
            n = rp.CompressData(src, size, *ppOut, *pOutSize, (size > 250000) + 1);
            *pOutSize = n;
            if (n != 0xffffffff)
                return true;
            *pOutSize = 0;
            if (bAlloc && *ppOut) {
                mpAllocator->Free(*ppOut, 0);
                *ppOut = 0;
            }
        }
        return false;
    }
    if (bAlloc) {
        *pOutSize = size;
        void* p = mpAllocator->Alloc(size, kStrPackedRecord, 0);
        *ppOut = p;
        memcpy(p, src, size);
        return true;
    }
    if (size <= *pOutSize) {
        *pOutSize = size;
        memcpy(*ppOut, src, size);
        return true;
    }
    *pOutSize = 0;
    return false;
}

// @ 0x008d9320
bool DatabasePackedFile::ReadCompressed(int a1, int pos, int size, int d, int e)
{
    bool r = false;
    if (pos != 0) {
        void* buf = mpAllocator->Alloc(size, kStrRaw, 0);
        if (buf) {
            if (ReadAt(buf, pos, size))
                r = Decompress(a1, buf, size, d, e);
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
bool DatabasePackedFile::CloseInternal(bool bFlush)
{
    bool r;
    if (mnAccessFlags != 0) {
        if (mnAccessFlags & 2) {
            r = Sync();
            if (bFlush && r) {
                typedef void (__thiscall *Fn)(DatabasePackedFile*);
                ((Fn)(*(void***)this)[0x24 / 4])(this);
            }
        } else {
            r = true;
        }
        if (mnMemorySize != 0) {
            m26c = 0;
            mnAccessFlags = 0;
        } else {
            mpMemoryLocation.p->Close();
            mnAccessFlags = 0;
        }
    } else {
        r = true;
    }
    if (mpMemoryLocation.p == (IStream*)&mFile)
        mpMemoryLocation = 0;
    {
        typedef void (__thiscall *Fn)(DatabasePackedFile*, Index*);
        ((Fn)(*(void***)this)[0x88 / 4])(this, mpIndex);
    }
    mpIndex = 0;
    HoleA().Reset(0);
    HoleB().Reset(0);
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
bool DatabasePackedFile::TryCompress(const void* src, unsigned size, void** ppOut, unsigned* pOutSize, uint16_t* pFlags)
{
    *ppOut = 0;
    *pOutSize = 0;
    if (CompressRecordData(src, size, ppOut, pOutSize, pFlags)) {
        float a = (float)*pOutSize;
        float b = (float)size;
        if (a / b < mfMinRatioToUseCompression)
            return true;
        if (*ppOut)
            mpAllocator->Free(*ppOut, 0);
        *ppOut = 0;
        *pOutSize = 0;
    }
    return false;
}

// @ 0x008d98f0
void RecMap::DoInsertValue(RbNode** out, RbNode* parent, const PFPair* v, bool bForceToLeft)
{
    int side = (bForceToLeft || parent == Anchor() || KeyLess(v->key, parent->key)) ? 0 : 1;
    RbNode* node = (RbNode*)mpAlloc->Alloc(0x20, 0, mnFlags);
    PFPair* pv = (PFPair*)&node->key;
    if (pv)
        *pv = *v;
    RBTreeInsert(node, parent, Anchor(), side);
    ++mnSize;
    *out = node;
}

// @ 0x008d99c0
bool DatabasePackedFile::SetLocation(const wchar_t* path)
{
    if (mnAccessFlags == 0) {
        mnMemorySize = 0;
        mnMemoryOffset = 0;
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
    Mutex& mtx = MutexM();
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
