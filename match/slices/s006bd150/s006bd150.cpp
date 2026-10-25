// Slice s006bd150 — DatabasePackedFile compression/index/close/location helpers (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "../s006bc1b0/s006bc1b0.h"

// ---------------------------------------------------------------------------
// Slice-local object views and out-of-slice callees.  The shared stub header
// keeps several embedded sub-objects (open-record map, string16) as padding,
// so they get a named view here instead of raw-offset casts.
// ---------------------------------------------------------------------------
extern char vtbl_DBPF_140a138[];   // 0x0140a138
extern char vtbl_DBPF_140a124[];   // 0x0140a124
extern char vtbl_DBPF_1408500[];   // 0x01408500
extern char vtbl_DBPF_14084f0[];   // 0x014084f0
extern char vtbl_DBPF_13f1ab0[];   // 0x013f1ab0
extern char vtbl_DBPF_13eb938[];   // 0x013eb938
extern char vtbl_DBPF_13effb8[];   // 0x013effb8

extern wchar_t gEmptyString16[];     // 0x01667bac  eastl::gEmptyString16
extern wchar_t gEmptyString16End[];  // 0x01667bae
extern const float kRatio095;        // 0x0140a098  (0.95f, kCompressRatio)
extern const float kRatio015;        // 0x0140a094  (0.15f, kHoleRatio)

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

ICoreAllocator* GetDefaultAllocator();     // 0x00925cb0
void* __cdecl sub_11E073E(void* dst, int val, unsigned n);   // 0x011e073e (memset)
void  __cdecl EAFree(void* p);             // 0x00f47380

// First words of DatabasePackedFile: two vptrs and the base refcount at +0x08.
struct DBPFHead {
    void* mpVtbl0;     // 0x00
    void* mpVtbl4;     // 0x04
    long  mnRefCount;  // 0x08
};

// eastl::basic_string16 embedded at +0x20.
struct WString16 {
    wchar_t* mpBegin;     // 0x00
    wchar_t* mpEnd;       // 0x04
    wchar_t* mpCapacity;  // 0x08
    char     pad00c[4];
};

// Embedded FileStream / Mutex / PFHoleTable lifecycle entry points that the
// shared stub header does not declare.
struct FileStreamX {
    void Construct(const void* params);   // 0x00929220
    void AddRef();                        // 0x00928e10
    void Destroy();                       // 0x00929450
};
struct MutexX {
    void Construct(const void* params, bool b);   // 0x009222a0
    void Destroy();                               // 0x00922130
};
struct HoleTableX {
    void Destroy();                               // 0x006bef60
};

// eastl open-record multimap at DatabasePackedFile+0x4f0.
struct RecNode;

struct RecMap {
    uint32          mCompare;   // 0x00  (never initialised by the ctor)
    RecNode*        mRight;     // 0x04  (anchor.right, points back at the anchor)
    RecNode*        mLeft;      // 0x08  (anchor.left)
    RecNode*        mParent;    // 0x0c  (anchor.parent = tree root)
    uint32          mColor;     // 0x10  (anchor colour, stored as a whole dword)
    uint32          mnSize;     // 0x14
    ICoreAllocator* mpAlloc;    // 0x18
    uint32          mnFlags;    // 0x1c

    RecNode* Anchor() { return reinterpret_cast<RecNode*>(&mRight); }
    RecNode** Find(RecNode** out, const Key* key);   // 0x00a21dc0
    void DoFreeNodes(RecNode* root);                 // 0x008de4f0
};

struct RecNode {
    RecNode* mRight;    // 0x00
    RecNode* mLeft;     // 0x04
    RecNode* mParent;   // 0x08
    int      mnColor;   // 0x0c
    Key      mKey;      // 0x10
    void*    mpValue;   // 0x1c
};

// One persisted index entry (64-bit file position stored as two halves).
struct IdxEntry {
    uint32 posLo;       // 0x00
    uint32 posHi;       // 0x04
    uint32 size;        // 0x08
    uint32 usize;       // 0x0c
    uint16 flags;       // 0x10
    uint8  compressed;  // 0x12
    char   pad013;
};

// PFIndexModifiable virtual view (slots up to GetEntry/SetEntry).
struct PFIndexVtbl {
    virtual void i00();
    virtual void i04();
    virtual void i08();
    virtual void i0c();
    virtual void i10();
    virtual void i14();
    virtual void i18();
    virtual void i1c();
    virtual void i20();
    virtual void i24();
    virtual void i28();
    virtual void SetEntry(const Key* key, const IdxEntry* entry);   // +0x2c
    virtual bool GetEntry(const Key* key, IdxEntry* entry);         // +0x30
};

// IStream and Record sub-objects used by CloseRecord.
struct IStreamX {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual int  GetSize();                         // +0x1c
    virtual void s20();
    virtual void s24();
    virtual bool SetPosition(int pos, int origin);  // +0x28
    virtual void s2c();
    virtual int  Read(void* buf, int size);         // +0x30
};

struct Record {
    virtual void r00();              // +0x00
    virtual void r04();              // +0x04
    virtual int  Release();          // +0x08
    virtual void r0c();              // +0x0c
    virtual Key* GetKey();           // +0x10
    virtual void r14();              // +0x14
    virtual IStreamX* GetStream();   // +0x18
    virtual void r1c();              // +0x1c
    virtual void r20();              // +0x20
    virtual void r24();              // +0x24
    virtual void Detach();           // +0x28
    char pad04[4];                   // +0x04
    int  mnMagic;                    // +0x08
    char pad0c[0x14];                // +0x0c .. +0x1f
    IStreamX mStream;                // +0x20
    // Chunked write of this record's stream at a raw file span (0x6c05a0).
    bool DoRead(uint32 posLo, uint32 posHi, uint32 n);   // 0x006c05a0
};

inline void* AllocBlock(ICoreAllocator* alloc, uint32 n, const char* name, uint32 flags)
{
    return ((void*(__thiscall*)(ICoreAllocator*, uint32, const char*, uint32))
            (*(void***)alloc)[8 / 4])(alloc, n, name, flags);
}

inline void FreeBlock(ICoreAllocator* alloc, void* p, uint32 n)
{
    ((void(__thiscall*)(ICoreAllocator*, void*, uint32))(*(void***)alloc)[0xc / 4])(alloc, p, n);
}

// @ 0x006bd150
bool DatabasePackedFile::FUN_006bd150(void* src, uint32 n, void** ppMem, uint32* pSize, uint16* pFlags)
{
    bool bWasNull = (*ppMem == 0);
    CompressionRefpack refpack;
    if (n - 1 < 39999999) {
        *pFlags = 0xffff;
        uint32 r = refpack.FUN_0092c9f0(src, n, 0, 0, 1);
        if (bWasNull && r != 0) {
            *pSize = r;
            *ppMem = ((void*(__thiscall*)(void*, uint32, const char*, int))(*(void***)mpAllocator)[8 / 4])
                (mpAllocator, r, "Resource/PackedRecord", 0);
        }
        if (*ppMem != 0) {
            uint32 r2 = refpack.FUN_0092c9f0(src, n, *ppMem, *pSize, (n > 250000) + 1);
            *pSize = r2;
            if (r2 != 0xffffffff)
                return true;
            *pSize = 0;
            if (bWasNull && *ppMem != 0) {
                ((void(__thiscall*)(void*, void*, int))(*(void***)mpAllocator)[0xc / 4])
                    (mpAllocator, *ppMem, 0);
                *ppMem = 0;
            }
        }
        return false;
    }
    if (bWasNull) {
        *pSize = n;
        void* mem = ((void*(__thiscall*)(void*, uint32, const char*, int))(*(void***)mpAllocator)[8 / 4])
            (mpAllocator, n, "Resource/PackedRecord", 0);
        *ppMem = mem;
        sub_11E0744(mem, src, n);
        return true;
    }
    if (*pSize < n) {
        *pSize = 0;
        return false;
    }
    *pSize = n;
    sub_11E0744(*ppMem, src, n);
    return true;
}

// @ 0x006bd300
void DatabasePackedFile::FUN_006bd300()
{
    DBPFHead* head = reinterpret_cast<DBPFHead*>(this);
    head->mpVtbl0 = vtbl_DBPF_140a138;
    head->mpVtbl4 = vtbl_DBPF_140a124;

    if (mbInitialized) {
        if (mnAccessFlags != 0)
            ((char(__thiscall*)(void*, int))(*(void***)this)[0x1c / 4])(this, 1);
        ((void(__thiscall*)(void*, PFIndexModifiable*))(*(void***)this)[0x80 / 4])(this, mpIndex);
        mpIndex = 0;
        mbInitialized = false;
    }

    reinterpret_cast<HoleTableX*>(&mHoleTable1)->Destroy();
    reinterpret_cast<HoleTableX*>(&mHoleTable0)->Destroy();

    RecMap* map = reinterpret_cast<RecMap*>(&field_4f0[0]);
    map->DoFreeNodes(map->mParent);

    reinterpret_cast<MutexX*>(&mReadWriteMutex)->Destroy();
    reinterpret_cast<MutexX*>(&mIndexMutex)->Destroy();
    reinterpret_cast<FileStreamX*>(&mFile)->Destroy();

    // The string16 teardown measures the allocated span (capacity - begin) and
    // frees the buffer unless it is the two-byte empty-string sentinel.
    WString16* str = reinterpret_cast<WString16*>(mFilePath);
    int nBytes = (int)((char*)str->mpCapacity - (char*)str->mpBegin);
    nBytes &= ~1;
    if (nBytes > 2 && str->mpBegin != 0)
        EAFree(str->mpBegin);

    head->mpVtbl4 = vtbl_DBPF_13eb938;
    head->mpVtbl0 = vtbl_DBPF_13effb8;
}

// @ 0x006bd430
char DatabasePackedFile::FUN_006bd430(char p2)
{
    char bl;
    if (mnAccessFlags == 0) {
        bl = 1;
        goto done;
    }
    if ((mnAccessFlags & 2) == 0) {
        bl = 1;
    } else {
        bl = (char)FUN_006bcd30();
        if (p2 != 0 && bl != 0) {
            ((void(__thiscall*)(void*))(*(void***)this)[0x24 / 4])(this);
            mFile.FUN_00929290();
            mnAccessFlags = 0;
            goto done;
        }
    }
    mFile.FUN_00929290();
    mnAccessFlags = 0;
done:
    ((void(__thiscall*)(void*, void*))(*(void***)this)[0x80 / 4])(this, mpIndex);
    mpIndex = 0;
    mHoleTable0.FUN_006bef70(0, 0);
    mHoleTable1.FUN_006bef70(0, 0);
    return bl;
}

// @ 0x006bd4d0
int DatabasePackedFile::FUN_006bd4d0(Key* key)
{
    EA::Thread::AutoLock lock(mIndexMutex, &g_mutexParam);
    int count = 0;
    if (mnAccessFlags != 0) {
        void* out = 0;
        void** it = ((RBTreeHead*)((char*)this + 0x4f0))->find(&out, key);
        char* end = (char*)this + 0x4f4;
        for (char* n = *(char**)it;
             n != end && *(uint32*)(n + 0x10) == key->type &&
             *(uint32*)(n + 0x14) == key->group && *(uint32*)(n + 0x18) == key->instance;
             n = (char*)RBTreeIncrement(n)) {
            count++;
        }
    }
    return count;
}

// @ 0x006bd580
bool DatabasePackedFile::FUN_006bd580(uint32 p2, int p3, void** p4, uint32* p5, uint32 p6)
{
    *p4 = 0;
    *p5 = 0;
    if (!FUN_006bd150((void*)p2, (uint32)p3, p4, p5, (uint16*)p6))
        return false;
    float a = (float)*p5;
    float b = (float)(uint32)p3;
    if (a / b < field_4ec)
        return true;
    if (*p4 != 0)
        ((void(__thiscall*)(void*, void*, int))(*(void***)mpAllocator)[0xc / 4])(mpAllocator, *p4, 0);
    *p4 = 0;
    *p5 = 0;
    return false;
}

// @ 0x006bd650
bool DatabasePackedFile::SetLocation(const wchar_t* p)
{
    if (mnAccessFlags == 0) {
        const wchar_t* end = p;
        while (*end)
            ++end;
        ((WStringAssign*)((char*)this + 0x20))->assign(p, p + (end - p));
        return true;
    }
    return false;
}

// @ 0x006bd690
bool DatabasePackedFile::FUN_006bd690(void* p2)
{
    Record* rec = static_cast<Record*>(p2);
    Key key = *rec->GetKey();

    RecMap* map = reinterpret_cast<RecMap*>(&field_4f0[0]);
    RecNode* end = map->Anchor();

    {
        EA::Thread::AutoLock lock(mIndexMutex, &g_mutexParam);
        if (mnAccessFlags == 0)
            return false;

        RecNode* found;
        RecNode* it = static_cast<RecNode*>(*map->Find(&found, &key));
        for (;;) {
            if (it == end)
                return false;
            if (it->mKey.type != key.type)
                return false;
            if (it->mKey.group != key.group)
                return false;
            if (it->mKey.instance != key.instance)
                return false;
            if (it->mpValue == rec)
                break;
            it = static_cast<RecNode*>(RBTreeIncrement(it));
        }

        if (rec->mnMagic != 0x6492fe5) {
            rec->Detach();
            rec->Release();
            --map->mnSize;
            RBTreeIncrement(it);
            RBTreeErase(it, map->Anchor());
            FreeBlock(map->mpAlloc, it, 0x20);
            return true;
        }

        if ((mnAccessFlags & 2) == 0)
            return false;

        ((void(__thiscall*)(void*))(*(void***)this)[0x84 / 4])(this);

        if (rec->GetStream()->GetSize() == 0) {
            PFIndexVtbl* idx = reinterpret_cast<PFIndexVtbl*>(mpIndex);

            IdxEntry old;
            old.posLo = 0;
            old.posHi = 0;
            old.size = 0;
            old.usize = 0;
            old.flags = 0;
            old.compressed = 0;
            if (idx->GetEntry(&key, &old))
                FUN_006bc310(old.posLo, old.posHi, old.size, 0, old.compressed == 0);

            IdxEntry empty;
            empty.posLo = 0;
            empty.posHi = 0;
            empty.size = 0;
            empty.usize = 0;
            empty.flags = 0;
            empty.compressed = 0;
            idx->SetEntry(&key, &empty);
            field_4dc = true;

            rec->Detach();
            rec->Release();
            --map->mnSize;
            RBTreeIncrement(it);
            RBTreeErase(it, map->Anchor());
            FreeBlock(map->mpAlloc, it, 0x20);
            return true;
        }
    }

    IStreamX* stream = &rec->mStream;
    int size = stream->GetSize();
    void* pCompressed = 0;
    uint32 cSize = 0;
    uint32 cFlags = 0;
    if (field_4e8 && (uint32)(size - 0x32) <= 0xf423ce) {
        char* buf = (char*)AllocBlock(mpAllocator, (uint32)(size + 0x10), "Resource/RecordData", 0);
        buf[size + 1] = 0;
        buf[size] = 0;
        if (stream->SetPosition(0, 0) && size == stream->Read(buf, size)) {
            if (!FUN_006bd580((uint32)buf, size, &pCompressed, &cSize, (uint32)&cFlags)) {
                pCompressed = 0;
                cFlags = 0;
            }
        }
        FreeBlock(mpAllocator, buf, 0);
    }

    int64_t diskPos = 0;
    uint32 storedSize = (pCompressed != 0) ? cSize : (uint32)size;
    bool bAlloc = false;
    {
        EA::Thread::AutoLock lock(mIndexMutex, &g_mutexParam);
        if (mnAccessFlags != 0 && (mnAccessFlags & 2) != 0) {
            diskPos = mHoleTable0.FUN_006bfc50(storedSize, 0);
            bAlloc = true;
        }
    }

    IdxEntry newEntry;
    newEntry.posLo = (uint32)diskPos;
    newEntry.posHi = (uint32)(diskPos >> 32);
    newEntry.size = storedSize;
    newEntry.usize = (uint32)size;
    newEntry.flags = (uint16)cFlags;
    newEntry.compressed = 0;

    bool result = false;
    if (bAlloc) {
        if (pCompressed != 0)
            result = FUN_006bcb50((uint32)pCompressed, newEntry.posLo, newEntry.posHi, cSize);
        else
            result = rec->DoRead(newEntry.posLo, newEntry.posHi, (uint32)size);
    }
    if (pCompressed != 0)
        FreeBlock(mpAllocator, pCompressed, 0);

    bool bAdded = false;
    {
        EA::Thread::AutoLock lock(mIndexMutex, &g_mutexParam);
        if (result) {
            PFIndexVtbl* idx = reinterpret_cast<PFIndexVtbl*>(mpIndex);

            IdxEntry old;
            old.posLo = 0;
            old.posHi = 0;
            old.size = 0;
            old.usize = 0;
            old.flags = 0;
            old.compressed = 0;
            if (idx->GetEntry(&key, &old))
                FUN_006bc310(old.posLo, old.posHi, old.size, 0, old.compressed == 0);

            idx->SetEntry(&key, &newEntry);
            field_4dc = true;
            bAdded = true;
        } else if (bAlloc) {
            if (diskPos != 0) {
                if (storedSize != 0) {
                    mHoleTable0.FUN_006bfda0((uint32)diskPos, (uint32)(diskPos >> 32), storedSize, 0);
                    field_5a0 = true;
                }
            }
        }

        RecNode* found2;
        RecNode* it2 = static_cast<RecNode*>(*map->Find(&found2, &key));
        for (;;) {
            if (it2 == end)
                break;
            if (it2->mKey.type != key.type)
                break;
            if (it2->mKey.group != key.group)
                break;
            if (it2->mKey.instance != key.instance)
                break;
            if (it2->mpValue == rec) {
                --map->mnSize;
                RBTreeIncrement(it2);
                RBTreeErase(it2, map->Anchor());
                FreeBlock(map->mpAlloc, it2, 0x20);
                rec->Detach();
                rec->Release();
                break;
            }
            it2 = static_cast<RecNode*>(RBTreeIncrement(it2));
        }
    }

    return bAdded;
}

// @ 0x006bdc50
void* DatabasePackedFile::FUN_006bdc50(const wchar_t* p2, int p3)
{
    DBPFHead* head = reinterpret_cast<DBPFHead*>(this);
    head->mpVtbl4 = vtbl_DBPF_13f1ab0;
    head->mpVtbl0 = vtbl_DBPF_1408500;
    head->mpVtbl4 = vtbl_DBPF_14084f0;
    _InterlockedExchange(&head->mnRefCount, 0);
    head->mpVtbl0 = vtbl_DBPF_140a138;
    head->mpVtbl4 = vtbl_DBPF_140a124;

    mbInitialized = false;
    if (p3 == 0)
        mpAllocator = GetDefaultAllocator();
    else
        mpAllocator = reinterpret_cast<ICoreAllocator*>(p3);
    mnAccessFlags = 0;
    mnAutoOpenAccessFlags = 0;
    mbEnableReadOnCorruptFiles = false;
    mbEnableWriteOnCorruptFiles = true;

    WString16* str = reinterpret_cast<WString16*>(mFilePath);
    str->mpBegin = gEmptyString16;
    str->mpEnd = gEmptyString16;
    str->mpCapacity = gEmptyString16End;

    reinterpret_cast<FileStreamX*>(&mFile)->Construct(0);
    reinterpret_cast<MutexX*>(&mIndexMutex)->Construct(0, true);
    reinterpret_cast<MutexX*>(&mReadWriteMutex)->Construct(0, true);

    mpIndex = 0;
    field_4dc = false;
    field_4e0 = 0;
    field_4e4 = 0;
    field_4e8 = true;
    field_4ec = kRatio095;

    RecMap* map = reinterpret_cast<RecMap*>(&field_4f0[0]);
    map->mLeft = 0;
    map->mParent = 0;
    map->mColor = 0;
    map->mpAlloc = mpAllocator;
    map->mnFlags = 0;
    map->mRight = map->Anchor();
    map->mLeft = map->Anchor();
    map->mParent = 0;
    map->mColor = 0;
    map->mnSize = 0;

    sub_11E073E(&field_510[0], 0, 0x30);

    field_540 = false;
    field_544 = 0x12;
    field_548 = kRatio015;

    mHoleTable0.FUN_006bf5a0();
    mHoleTable1.FUN_006bf5a0();

    field_5a0 = false;
    pad05a1[0] = 0;   // +0x5a1
    field_5a4 = 0;

    reinterpret_cast<FileStreamX*>(&mFile)->AddRef();

    if (p2 != 0 && mnAccessFlags == 0) {
        const wchar_t* end = p2;
        while (*end)
            ++end;
        reinterpret_cast<WStringAssign*>(mFilePath)->assign(p2, end);
    }

    return this;
}
