// Slice s008dc1a0 (0x8dc1a0..0x8dcea0) - EA::ResourceMan packed-file record IO.
//
// These are the region methods of DatabasePackedFile*.obj: the modifiable index's hole
// bookkeeping, the PFRecordRead stream implementation (IStream sub-object embedded at
// +0x20), the PFRecordWrite stream implementation, and the record constructors.
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE
//
// Functions (VA, name):
//   008dc1a0  HoleSet::Insert
//   008dc2b0  PFIndexModifiable::ReserveRange
//   008dc350  PFRecordReadIstream::ForwardGetSize           (vtable thunk)
//   008dc370  PFRecordReadIstream::GetAccessFlags
//   008dc380  PFRecordReadIstream::GetSize(mode)
//   008dc3c0  PFRecordReadIstream::GetSize()
//   008dc3f0  PFRecordRead::ReadSpan
//   008dc510  PFRecordRead::EnsureLoaded
//   008dc5e0  PFRecordRead::GetBuffer
//   008dc600  PFRecordWrite::OpenTempFile
//   008dc740  PFRecordWrite::DeleteTempFile
//   008dc7b0  PFRecordWriteIstream::Close
//   008dc7e0  PFRecordWriteIstream::SetSize
//   008dc820  PFRecordWriteIstream::SetPosition
//   008dc860  PFRecordWriteIstream::Flush
//   008dc890  PFRecordWrite::WriteRecordToParent
//   008dca00  PFRecordRead::IStreamDestroy
//   008dca50  PFRecordRead::IStreamAddRef
//   008dca70  PFRecordRead::IStreamRelease
//   008dcab0  PFRecordReadIstream::SetPosition
//   008dcb70  PFRecordReadIstream::Read
//   008dcbf0  PFRecordWrite::IStreamDestroy
//   008dcc50  PFRecordWrite::IStreamAddRef
//   008dcc80  PFRecordRead::PFRecordRead(copy)
//   008dcd70  PFRecordRead::`scalar deleting destructor'
//   008dcdc0  PFRecordRead::PFRecordRead(info)
//   008dcea0  PFRecordWrite::PFRecordWrite

#include <string.h>
#include "types.h"

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;

// ---------------------------------------------------------------------------
// intrinsics
// ---------------------------------------------------------------------------
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedDecrement, _InterlockedExchange)

// ---------------------------------------------------------------------------
// external callees (real addresses in comments)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl memcpy_pf(void* dst, const void* src, unsigned n);   // 0x11e0744 (CRT memcpy)
extern "C" void* __cdecl RBTreeIncrement(void* node);                         // 0x921580
extern "C" void* __cdecl RBTreeDecrement(const void* node);                   // 0x9215c0
extern "C" int   __cdecl Sprintf16(wchar_t* buf, const wchar_t* fmt, ...);   // 0x9399c0
extern "C" char  __cdecl CreateTempFile(wchar_t* name, int a, const wchar_t* fmt, int b); // 0x932580
extern "C" char  __cdecl IO_File_Remove(const wchar_t* path);                // 0x931fd0
extern "C" void* __cdecl ZoneObject_delete(void* p);                          // 0x926060

// ---------------------------------------------------------------------------
// fixed layout helpers
// ---------------------------------------------------------------------------
struct Key { uint32 mInstance; uint32 mType; uint32 mGroup; };   // 0xc

struct IAllocator {
    virtual void a0();                          // +0x00
    virtual void a1();                          // +0x04
    virtual void* Alloc(unsigned size, const char* name, unsigned flags); // +0x08
    virtual void  Free(void* p, unsigned size);                           // +0x0c
    virtual void a4();                          // +0x10
};

// EASTL rbtree<Hole> used by HoleSet.  Node: right@+0 left@+4 parent@+8 color@+0xc
// key(mnPos)@+0x10 value(mnSize)@+0x14.  The tree lives at HoleSet+4 and its size
// counter is the rbtree's at tree+0x14 == HoleSet+0x18.
struct HoleTree {
    char d[0x1c];                               // full 0x1c, size counter at +0x14
    void Erase(void** ppOut, void* pNode);      // 0x8dae70 (defined in s008da140)
    int  GetTotalSize();                        // 0x8dae40 (defined in s008da140)
    void DoInsert(void** ppOut, void* pAfter, const int* pRange); // 0x8dbef0
};
struct HoleSet {
    int       mExtent;                          // +0x00 running extent
    HoleTree  mTree;                            // +0x04
    bool Insert(int pos, int size);             // 0x8dc1a0
    void Release(unsigned pos, int size);       // 0x8dc000 (defined in s008daff0)
    int  GetTotalSize() { return mTree.GetTotalSize(); }
};
typedef char chk_holeset[(sizeof(HoleSet) == 0x20) ? 1 : -1];

// record metadata blob handed to the info-constructor (+0x50..+0x5c mirror it).
struct PFRecordInfo { uint32 mf[4]; };          // 0x10

struct DatabasePackedFile {                     // 0x384
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17();
    virtual IAllocator* GetAllocator();         // +0x48
    bool ReadFileSpan(void* dst, unsigned offset, int size);            // 0x8d9050
    bool WriteFileSpan(const void* src, unsigned offset, int size);     // 0x8d90e0
    bool DecompressRecord(uint16 type, unsigned src, unsigned a, unsigned b, void* out); // 0x8d9320
};

// Owner (the record whose stream this is) exposes its release-handler through
// vtable slot 0x3c; it is invoked with the stream pointer as a stack argument.
struct PFRecordOwner {
    virtual void o00(); virtual void o01(); virtual void o02(); virtual void o03();
    virtual void o04(); virtual void o05(); virtual void o06(); virtual void o07();
    virtual void o08(); virtual void o09(); virtual void o10(); virtual void o11();
    virtual void o12(); virtual void o13(); virtual void o14();
    virtual bool OnStreamRelease(void* stream);  // +0x3c
};

// Read-side memory stream, embedded at PFRecordRead+0x2c.  vtable slots that the
// read path uses: GetSize(mode)@0x24, SetPosition@0x28, GetSize0@0x2c, Read@0x30.
struct MemoryStream {
    virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
    virtual void r04(); virtual void r05(); virtual void r06(); virtual int r07();
    virtual void r08();                              // +0x20
    virtual int  GetSize(int mode);                  // +0x24
    virtual bool SetPosition(int delta, int mode);   // +0x28
    virtual int  GetSize0();                         // +0x2c
    virtual int  Read(void* buf, int len);           // +0x30
    bool  SetData(void* data, unsigned size, unsigned a, unsigned b, void* alloc); // 0x93be30
    void* GetData();                            // 0x93ba70
    void  SetOption(int option, float value);   // 0x93bb40
    void  Construct(const char* name);          // 0x93bd50
    void  Destroy();                            // 0x93bde0
    int   Attach(void* a, unsigned b);          // 0x93bf70
};

// Write-side memory stream, embedded at PFRecordWrite+0x24.  Slots used by the
// write path: GetSize@0x1c, SetSize@0x20, SetPosition@0x28, Flush@0x2c, Read@0x30.
struct MemStreamW {
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04(); virtual void w05(); virtual void w06();
    virtual int  GetSize();                          // +0x1c
    virtual void SetSize(int n);                     // +0x20
    virtual void w09();                              // +0x24
    virtual void SetPosition(int delta, int mode);   // +0x28
    virtual void Flush();                            // +0x2c
    virtual int  Read(void* buf, int len);           // +0x30
    bool  SetData(void* data, unsigned size, unsigned a, unsigned b, void* alloc);
    void* GetData();
    void  SetOption(int option, float value);
    void  Construct(const char* name);
    void  Destroy();
    int   Attach(void* a, unsigned b);
};

struct FileStream {
    virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
    virtual int  IsOpen();                      // +0x10
    virtual void f05();                         // +0x14
    virtual bool Close();                       // +0x18
    virtual void f07();                         // +0x1c
    virtual bool f08(int n);                    // +0x20
    virtual int  f09();                         // +0x24
    virtual void f10(int a, int b);             // +0x28
    virtual void f11();                         // +0x2c
    virtual int  f12();                         // +0x30
    virtual void f13();                         // +0x34
    virtual bool f14();                         // +0x38
    virtual void f15();                         // +0x3c
    virtual void f16();                         // +0x40
    virtual int  GetPath(void* buf, int n);     // +0x44
    virtual void f18();                         // +0x48
    virtual bool Open(int mode, int a, int b, int c); // +0x4c
    void Construct(const char* path);           // 0x931da0
};

// ---------------------------------------------------------------------------
// PFRecordRead: vtbl@0 refcount@4 type@8 key@0xc/+0x10/+0x14 parent@0x18 flags@0x1c
//                istream-vtbl@0x20 readbuf@0x24 bufpos@0x28 memstream@0x2c
//                info@0x50..0x64 bytestate@0x68 stream-refcount@0x6c
// PFRecordWrite: istream-vtbl@0x20 memstream@0x24 filestream@0x48
//                tempopen@0x274 stream-refcount@0x278
// ---------------------------------------------------------------------------
struct PFRecordRead {
    char raw[0x70];
    void  EnsureLoaded();                        // 0x8dc510
    char  ReadSpan(void* dst, unsigned pos, unsigned len); // 0x8dc3f0
    void* GetBuffer();                           // 0x8dc5e0
    void  IStreamDestroy();                      // 0x8dca00
    PFRecordRead(const PFRecordRead& src, const Key& key, DatabasePackedFile* parent); // 0x8dcc80
    PFRecordRead(const PFRecordInfo& info, const Key& key, DatabasePackedFile* parent); // 0x8dcdc0
    void* operator new(unsigned n, void* p) { return p; }
    void* Destroy(unsigned flags);               // 0x8dcd70
};

struct PFRecordWrite {
    char raw[0x27c];
    char  OpenTempFile();                        // 0x8dc600
    void  DeleteTempFile();                      // 0x8dc740
    char  WriteRecordToParent(void* data, unsigned size);  // 0x8dc890
    void  IStreamDestroy();                      // 0x8dcbf0
    bool  IStreamAddRef();                       // 0x8dcc50
    PFRecordWrite(unsigned access, unsigned size, const Key& key, DatabasePackedFile* parent); // 0x8dcea0
};

// IStream sub-object embedded at +0x20 of PFRecordRead.
struct PFRecordReadIstream {
    unsigned   GetAccessFlags();                 // 0x8dc370
    void       ForwardGetSize();                 // 0x8dc350
    int        GetSize(int mode);                // 0x8dc380
    int        GetSize0();                       // 0x8dc3c0
    bool       SetPosition(int delta, int mode); // 0x8dcab0
    int        Read(void* buf, int len);         // 0x8dcb70
    bool       IStreamAddRef();                   // 0x8dca50
    bool       IStreamRelease();                  // 0x8dca70
};

// IStream sub-object embedded at +0x20 of PFRecordWrite.
struct PFRecordWriteIstream {
    void Close();                                // 0x8dc7b0
    void SetSize(int n);                         // 0x8dc7e0
    void SetPosition(int a, int b);              // 0x8dc820
    void Flush();                                // 0x8dc860
};
// ===========================================================================
// 0x8dc1a0  HoleSet::Insert
// ===========================================================================
// @ 0x008dc1a0
bool HoleSet::Insert(int pos, int size)
{
    if (size == 0)
        return true;
    int end = pos + size;
    int extent = mExtent;
    if (end > extent) {
        if (pos < extent)
            return false;
        mExtent = end;
        if (pos > extent)
            Release(extent, pos - extent);
        return true;
    }
    // Find the first hole positioned strictly after `pos` (rbtree lower_bound).
    char* root = *(char**)((char*)&mTree + 0xc);
    char* at = (char*)&mTree + 4;
    while (root != 0) {
        if (pos < *(int*)(root + 0x10)) {
            at = root;
            root = *(char**)(root + 4);
        } else {
            root = *(char**)root;
        }
    }
    if (at == *(char**)((char*)&mTree + 8))
        return false;
    char* prev = (char*)RBTreeDecrement(at);
    int prevPos = *(int*)(prev + 0x10);
    int prevSize = *(int*)(prev + 0x14);
    void* out;
    mTree.Erase(&out, prev);
    int holeEnd = prevPos + prevSize;
    int range[2];
    if (prevPos < pos) {
        range[0] = prevPos;
        range[1] = pos - prevPos;
        mTree.DoInsert(&out, at, range);
    }
    if (end < holeEnd) {
        range[0] = end;
        range[1] = holeEnd - end;
        mTree.DoInsert(&out, at, range);
    }
    return true;
}

// ===========================================================================
// 0x8dc2b0  PFIndexModifiable::ReserveRange
// ===========================================================================
struct PFIndexModifiable {
    char d0[0x2c];                  // +0x00
    char** mpBucketArray;           // +0x2c
    int    mnBucketCount;           // +0x30
    bool ReserveRange(HoleSet* holes, unsigned pos, unsigned end);
};

// @ 0x008dc2b0
bool PFIndexModifiable::ReserveRange(HoleSet* holes, unsigned pos, unsigned end)
{
    char** pBucket = mpBucketArray;
    char* node = *pBucket;
    if (node == 0) {
        ++pBucket;
        while (*pBucket == 0)
            ++pBucket;
        node = *pBucket;
    }
    char* last = mpBucketArray[mnBucketCount];
    while (node != last) {
        unsigned holeSize = *(unsigned*)(node + 0x10);
        if (holeSize != 0) {
            unsigned holePos = *(unsigned*)(node + 0xc);
            if (holePos < pos || end <= holePos || end - holePos < holeSize)
                return false;
            if (!holes->Insert((int)holePos, (int)holeSize))
                return false;
        }
        node = *(char**)(node + 0x1c);
        while (node == 0) {
            ++pBucket;
            node = *pBucket;
        }
    }
    return true;
}

// ===========================================================================
// 0x8dc350  PFRecordReadIstream::ForwardGetSize
// ===========================================================================
// @ 0x008dc350
void PFRecordReadIstream::ForwardGetSize()
{
    char* obj = (char*)this - 0x20;
    void** vt = *(void***)obj;
    typedef void (__thiscall *F)(void*);
    ((F)vt[0x24 / 4])(obj);
}

// ===========================================================================
// 0x8dc370  PFRecordReadIstream::GetAccessFlags
// ===========================================================================
// @ 0x008dc370
unsigned PFRecordReadIstream::GetAccessFlags()
{
    return *(unsigned*)((char*)this - 4);
}

// ===========================================================================
// 0x8dc380  PFRecordReadIstream::GetSize(mode)
// ===========================================================================
// @ 0x008dc380
int PFRecordReadIstream::GetSize(int mode)
{
    char* self = (char*)this;
    unsigned char flags = *(unsigned char*)(self + 0x48);
    if (flags == 0) {
        if (mode == 0)
            return *(int*)(self + 0x40);
        if (mode == 1)
            return 0;
        if (mode == 2)
            return *(int*)(self + 0x40) - *(int*)(self + 0x44);
    }
    MemoryStream* ms = (MemoryStream*)(self + 0xc);
    return ms->GetSize(mode);
}

// ===========================================================================
// 0x8dc3c0  PFRecordReadIstream::GetSize()
// ===========================================================================
// @ 0x008dc3c0
int PFRecordReadIstream::GetSize0()
{
    char* self = (char*)this;
    if (*(int*)(self - 4) == 0)
        return 0;
    unsigned char flags = *(unsigned char*)(self + 0x48);
    if ((flags & 2) == 0)
        return *(int*)(self + 0x44) - *(int*)(self + 0x40);
    return ((MemoryStream*)(self + 0xc))->GetSize0();
}

// ===========================================================================
// 0x008dcab0  PFRecordReadIstream::SetPosition
// ===========================================================================
// @ 0x008dcab0
bool PFRecordReadIstream::SetPosition(int delta, int mode)
{
    char* self = (char*)this;
    char* outer = self - 0x20;
    if (*(int*)(self - 4) == 0)
        return false;
    ((PFRecordRead*)outer)->EnsureLoaded();
    if (*(unsigned char*)(self + 0x48) != 0) {
        MemoryStream* ms = (MemoryStream*)(self + 0xc);
        return ms->SetPosition(delta, mode);
    }
    switch (mode) {
    case 0:                                   // seek from start
        if (delta < 0) {
            *(int*)(self + 0x40) = 0;
        } else if (delta > *(int*)(self + 0x44)) {
            *(int*)(self + 0x40) = *(int*)(self + 0x44);
        } else {
            *(int*)(self + 0x40) = delta;
        }
        return true;
    case 1:                                   // seek from current
        if (delta < 0 && -delta > *(int*)(self + 0x40)) {
            *(int*)(self + 0x40) = 0;
        } else if (delta > 0 && *(int*)(self + 0x40) + delta > *(int*)(self + 0x44)) {
            *(int*)(self + 0x40) = *(int*)(self + 0x44);
        } else {
            *(int*)(self + 0x40) += delta;
        }
        return true;
    case 2:                                   // seek from end
        if (delta >= 0) {
            *(int*)(self + 0x40) = *(int*)(self + 0x44);
        } else if (-delta > *(int*)(self + 0x44)) {
            *(int*)(self + 0x40) = 0;
        } else {
            *(int*)(self + 0x40) = *(int*)(self + 0x44) + delta;
        }
        return true;
    default:
        return true;
    }
}

// ===========================================================================
// 0x008dcb70  PFRecordReadIstream::Read
// ===========================================================================
// @ 0x008dcb70
int PFRecordReadIstream::Read(void* buf, int len)
{
    char* self = (char*)this;
    char* outer = self - 0x20;
    if (*(int*)(self - 4) == 0)
        return -1;
    ((PFRecordRead*)outer)->EnsureLoaded();
    if (*(unsigned char*)(self + 0x48) != 0) {
        MemoryStream* ms = (MemoryStream*)(self + 0xc);
        return ms->Read(buf, len);
    }
    int n = -1;
    if (*(int*)(self - 4) != 0) {
        unsigned pos = *(unsigned*)(self + 0x40);
        unsigned size = *(unsigned*)(self + 0x44);
        if (size < pos + (unsigned)len || pos + (unsigned)len < pos)
            n = (int)(size - pos);
        else
            n = len;
        if (n != 0) {
            if (!((PFRecordRead*)outer)->ReadSpan(buf, pos, (unsigned)n))
                n = 0;
        }
        *(int*)(self + 0x40) += n;
    }
    return n;
}

// ===========================================================================
// 0x008dca50  PFRecordReadIstream::IStreamAddRef
// ===========================================================================
// @ 0x008dca50
bool PFRecordReadIstream::IStreamAddRef()
{
    volatile long* p = (volatile long*)((char*)this + 0x6c);
    if (_InterlockedExchangeAdd(p, 0) == 0)
        return false;
    _InterlockedExchangeAdd(p, 1);
    return true;
}

// ===========================================================================
// 0x008dca70  PFRecordReadIstream::IStreamRelease
// ===========================================================================
// @ 0x008dca70
bool PFRecordReadIstream::IStreamRelease()
{
    char* self = (char*)this;
    volatile long* p = (volatile long*)(self + 0x6c);
    if (_InterlockedExchangeAdd(p, 0) == 0)
        return false;
    if (_InterlockedDecrement(p) != 0)
        return true;
    if (*(int*)(self + 0x1c) != 0)
        return ((PFRecordOwner*)(*(void**)(self + 0x18)))->OnStreamRelease(self);
    return true;
}

// ===========================================================================
// 0x8dc3f0  PFRecordRead::ReadSpan
// ===========================================================================
// @ 0x008dc3f0
char PFRecordRead::ReadSpan(void* dst, unsigned pos, unsigned len)
{
    unsigned bufPos = *(unsigned*)(raw + 0x28);
    if (bufPos <= pos && pos < bufPos + 0x200) {
        unsigned avail = 0x200 - (pos - bufPos);
        char* src = (char*)*(void**)(raw + 0x24) + (pos - bufPos);
        if (len <= avail) {
            memcpy_pf(dst, src, len);
            return 1;
        }
        memcpy_pf(dst, src, avail);
        dst = (char*)dst + avail;
        pos += avail;
        len -= avail;
    }
    if (len < 0x200 && pos + len < *(unsigned*)(raw + 0x64)) {
        *(unsigned*)(raw + 0x28) = 0xffffffff;
        if (*(void**)(raw + 0x24) == 0) {
            IAllocator* alloc = ((DatabasePackedFile*)*(void**)(raw + 0x18))->GetAllocator();
            *(void**)(raw + 0x24) = alloc->Alloc(0x200, "Resource/PFReadBuffer", 0);
        }
        if (*(void**)(raw + 0x24) != 0) {
            unsigned n = 0x200;
            if (*(unsigned*)(raw + 0x64) < pos + 0x200)
                n = *(unsigned*)(raw + 0x64) - pos;
            if (((DatabasePackedFile*)*(void**)(raw + 0x18))->ReadFileSpan(
                    *(void**)(raw + 0x24), *(unsigned*)(raw + 0x50) + pos, (int)n)) {
                *(unsigned*)(raw + 0x28) = pos;
                memcpy_pf(dst, *(void**)(raw + 0x24), len);
                return 1;
            }
            return 0;
        }
    }
    return ((DatabasePackedFile*)*(void**)(raw + 0x18))->ReadFileSpan(
               dst, *(unsigned*)(raw + 0x50) + pos, (int)len) ? 1 : 0;
}

// ===========================================================================
// 0x8dc510  PFRecordRead::EnsureLoaded
// ===========================================================================
// @ 0x008dc510
void PFRecordRead::EnsureLoaded()
{
    unsigned char flags = *(unsigned char*)(raw + 0x68);
    if (flags == 0 || flags == 3)
        return;
    DatabasePackedFile* parent = (DatabasePackedFile*)*(void**)(raw + 0x18);
    IAllocator* alloc = parent->GetAllocator();
    if (*(uint16*)(raw + 0x5c) != 0) {
        void* p = alloc->Alloc(*(unsigned*)(raw + 0x64), "Resource/RecordData", 0);
        if (p == 0)
            goto loaded;
        if (!parent->DecompressRecord(*(uint16*)(raw + 0x5c), *(unsigned*)(raw + 0x50),
                                      *(unsigned*)(raw + 0x54), *(unsigned*)(raw + 0x58), p)) {
            alloc->Free(p, 0);
            goto loaded;
        }
        ((MemoryStream*)(raw + 0x2c))->SetData(p, *(unsigned*)(raw + 0x64), 1, 1, alloc);
    } else {
        void* p = alloc->Alloc(*(unsigned*)(raw + 0x64), "Resource/RecordData", 0);
        if (p == 0)
            goto loaded;
        if (!parent->ReadFileSpan(p, *(unsigned*)(raw + 0x50), *(int*)(raw + 0x64))) {
            *(unsigned char*)(raw + 0x68) = 0;
            return;
        }
        ((MemoryStream*)(raw + 0x2c))->SetData(p, *(unsigned*)(raw + 0x64), 1, 1, alloc);
    }
loaded:
    *(unsigned char*)(raw + 0x68) |= 2;
}

// ===========================================================================
// 0x8dc5e0  PFRecordRead::GetBuffer
// ===========================================================================
// @ 0x008dc5e0
void* PFRecordRead::GetBuffer()
{
    EnsureLoaded();
    unsigned char flags = *(unsigned char*)(raw + 0x68);
    if (flags == 3)
        return *(void**)(raw + 0x30);
    return 0;
}

// ===========================================================================
// 0x8dc600  PFRecordWrite::OpenTempFile
// ===========================================================================
// @ 0x008dc600
char PFRecordWrite::OpenTempFile()
{
    wchar_t name[20];
    const wchar_t* fmt = L"Record_%08x_%08x";
    memcpy_pf(name, fmt, sizeof(L"Record_%08x_%08x"));
    Sprintf16(name, fmt, *(unsigned*)(raw + 0x10), *(unsigned*)(raw + 0xc));
    wchar_t path[260];
    if (!CreateTempFile(path, 0, name, 0))
        return 0;
    FileStream* fs = (FileStream*)(raw + 0x48);
    fs->GetPath(path, 0x104);
    if (!fs->Open(3, 4, 1, 0))
        return 0;
    fs->f08(0);
    return 1;
}

// ===========================================================================
// 0x8dc740  PFRecordWrite::DeleteTempFile
// ===========================================================================
// @ 0x008dc740
void PFRecordWrite::DeleteTempFile()
{
    FileStream* fs = (FileStream*)(raw + 0x48);
    if (fs->IsOpen()) {
        fs->Close();
        wchar_t path[260];
        fs->GetPath(path, 0x104);
        IO_File_Remove(path);
    }
}

// ===========================================================================
// 0x8dc7b0  PFRecordWriteIstream::Close
// ===========================================================================
// @ 0x008dc7b0
void PFRecordWriteIstream::Close()
{
    FileStream* fs = (FileStream*)((char*)this + 0x28);
    if (fs->IsOpen())
        fs->f07();
    else
        ((MemStreamW*)((char*)this + 4))->GetSize();
}

// ===========================================================================
// 0x8dc7e0  PFRecordWriteIstream::SetSize
// ===========================================================================
// @ 0x008dc7e0
void PFRecordWriteIstream::SetSize(int n)
{
    FileStream* fs = (FileStream*)((char*)this + 0x28);
    if (fs->IsOpen())
        fs->f08(n);
    else
        ((MemStreamW*)((char*)this + 4))->SetSize(n);
}

// ===========================================================================
// 0x008dc820  PFRecordWriteIstream::SetPosition
// ===========================================================================
// @ 0x008dc820
void PFRecordWriteIstream::SetPosition(int a, int b)
{
    FileStream* fs = (FileStream*)((char*)this + 0x28);
    if (fs->IsOpen())
        fs->f10(a, b);
    else
        ((MemStreamW*)((char*)this + 4))->SetPosition(a, b);
}

// ===========================================================================
// 0x008dc860  PFRecordWriteIstream::Flush
// ===========================================================================
// @ 0x008dc860
void PFRecordWriteIstream::Flush()
{
    FileStream* fs = (FileStream*)((char*)this + 0x28);
    if (fs->IsOpen())
        fs->f11();
    else
        ((MemStreamW*)((char*)this + 4))->Flush();
}

// ===========================================================================
// 0x008dc890  PFRecordWrite::WriteRecordToParent
// ===========================================================================
// @ 0x008dc890
char PFRecordWrite::WriteRecordToParent(void* data, unsigned size)
{
    char ok = 0;
    if (*(int*)(raw + 0x1c) == 0)
        return 0;
    FileStream* fs = (FileStream*)(raw + 0x48);
    if (!fs->IsOpen()) {
        // Memory-stream path: clamp to the buffered size and copy straight through.
        MemStreamW* ms = (MemStreamW*)(raw + 0x24);
        int have = ms->GetSize();
        unsigned n = (unsigned)have < size ? (unsigned)have : size;
        ((DatabasePackedFile*)*(void**)(raw + 0x18))->WriteFileSpan(ms->GetData(), (unsigned)data, (int)n);
        return ok;
    }
    IAllocator* alloc = ((DatabasePackedFile*)*(void**)(raw + 0x18))->GetAllocator();
    void* buf = alloc->Alloc(0x4000, "Resource/RecordData", 0);
    if (buf == 0)
        return ok;
    unsigned done = 0;
    unsigned todo = (unsigned)fs->f09();
    ok = 1;
    fs->f10(0, 0);
    while (done < size && ok) {
        unsigned chunk = size - done;
        if (chunk > 0x4000)
            chunk = 0x4000;
        int got = fs->f12();
        ok = 0;
        if ((unsigned)got == chunk) {
            ok = ((DatabasePackedFile*)*(void**)(raw + 0x18))->WriteFileSpan(
                     buf, *(unsigned*)(raw + 0x50) + done, (int)chunk) ? 1 : 0;
            done += chunk;
        }
        (void)todo;
    }
    alloc->Free(buf, 0);
    fs->f10(0, 0);
    return ok;
}

// ===========================================================================
// 0x008dca00  PFRecordRead::IStreamDestroy
// ===========================================================================
// @ 0x008dca00
void PFRecordRead::IStreamDestroy()
{
    if (*(void**)(raw + 0x24) != 0) {
        DatabasePackedFile* parent = (DatabasePackedFile*)*(void**)(raw + 0x18);
        if (parent != 0)
            parent->GetAllocator()->Free(*(void**)(raw + 0x24), 0);
        *(void**)(raw + 0x24) = 0;
        *(unsigned*)(raw + 0x28) = 0xffffffff;
    }
    *(void**)(raw + 0x1c) = 0;
    *(void**)(raw + 0x18) = 0;
    _InterlockedExchange((volatile long*)(raw + 0x6c), 0);
}

// ===========================================================================
// 0x008dcbf0  PFRecordWrite::IStreamDestroy
// ===========================================================================
// @ 0x008dcbf0
void PFRecordWrite::IStreamDestroy()
{
    *(void**)(raw + 0x1c) = 0;
    *(void**)(raw + 0x18) = 0;
    *(unsigned char*)(raw + 0x274) = 0;
    _InterlockedExchange((volatile long*)(raw + 0x278), 0);
    DeleteTempFile();
}

// ===========================================================================
// 0x008dcc50  PFRecordWrite::IStreamAddRef
// ===========================================================================
// @ 0x008dcc50
bool PFRecordWrite::IStreamAddRef()
{
    volatile long* p = (volatile long*)(raw + 0x278);
    if (_InterlockedExchangeAdd(p, 0) == 0)
        return false;
    _InterlockedExchangeAdd(p, 1);
    return true;
}

// ---------------------------------------------------------------------------
// vtable addresses referenced by the constructors (raw retail vtables)
// ---------------------------------------------------------------------------
extern char vtbl_ZoneObject_PFRecordRead[];   // 0x13effa8
extern char vtbl_ZoneObject_PFRecordWrite[];  // 0x13effb8
extern char vtbl_PFRecordRead_base[];         // 0x140a2e0
extern char vtbl_IStream_default[];           // 0x13f3a68
extern char vtbl_PFRecordRead[];              // 0x1436900
extern char vtbl_PFRecordRead_IStream[];      // 0x14368c4
extern char vtbl_Resource_PFRecordRead[];     // (base ctor tag)
extern char vtbl_PFRecordWrite[];             // 0x1436968
extern char vtbl_PFRecordWrite_IStream[];     // 0x143692c

// Shared stream-interface bootstrap for PFRecordRead: init istream vtable, buffer
// cursor, embedded MemoryStream, and the stream refcount.
static void InitReadStream(PFRecordRead* self)
{
    *(void**)(self->raw + 0x20) = vtbl_IStream_default;
    *(void**)(self->raw + 0x20) = vtbl_PFRecordRead_IStream;
    *(void**)(self->raw + 0x24) = 0;
    *(unsigned*)(self->raw + 0x28) = 0xffffffff;
    *(void**)self->raw = vtbl_PFRecordRead;
    MemoryStream* ms = (MemoryStream*)(self->raw + 0x2c);
    ms->Construct("ResourceMan/PFRecordRead");
    *(void**)(self->raw + 0x6c) = (void*)1;
    ms->r01();   // AddRef the embedded stream
}

// ===========================================================================
// 0x008dcc80  PFRecordRead::PFRecordRead(const PFRecordRead&, const Key&, DatabasePackedFile*)
// ===========================================================================
// @ 0x008dcc80
PFRecordRead::PFRecordRead(const PFRecordRead& src, const Key& key, DatabasePackedFile* parent)
{
    *(void**)raw = vtbl_ZoneObject_PFRecordRead;
    _InterlockedExchange((volatile long*)(raw + 4), 0);
    *(void**)raw = vtbl_PFRecordRead_base;
    *(unsigned*)(raw + 8) = 0x12e4a891;                 // kPFRecordTypeRead
    *(uint32*)(raw + 0xc) = key.mInstance;
    *(uint32*)(raw + 0x10) = key.mType;
    *(uint32*)(raw + 0x14) = key.mGroup;
    *(void**)(raw + 0x18) = parent;
    *(unsigned*)(raw + 0x1c) = 1;
    *(void**)(raw + 0x20) = vtbl_IStream_default;
    InitReadStream(this);
    (void)src;
    *(unsigned*)(raw + 0x50) = *(unsigned*)(src.raw + 0x50);
    *(unsigned*)(raw + 0x54) = *(unsigned*)(src.raw + 0x54);
    *(unsigned*)(raw + 0x58) = *(unsigned*)(src.raw + 0x58);
    *(unsigned*)(raw + 0x5c) = *(unsigned*)(src.raw + 0x5c);
    *(unsigned*)(raw + 0x60) = 0;
    *(unsigned*)(raw + 0x64) = *(unsigned*)(src.raw + 0x64);
    *(unsigned char*)(raw + 0x68) = *(unsigned char*)(src.raw + 0x68);
    _InterlockedExchange((volatile long*)(raw + 0x6c), 1);
    MemoryStream* ms = (MemoryStream*)(raw + 0x2c);
    if ((*(unsigned char*)(raw + 0x68) & 2) != 0) {
        int shared = ((MemoryStream*)(src.raw + 0x2c))->r07();
        ms->Attach(*(void**)(src.raw + 0x30), (unsigned)shared);
        ms->SetPosition(0, 0);
    }
}

// ===========================================================================
// 0x008dcd70  PFRecordRead::`scalar deleting destructor'
// ===========================================================================
// @ 0x008dcd70
void* PFRecordRead::Destroy(unsigned flags)
{
    *(void**)raw = vtbl_PFRecordRead;
    *(void**)(raw + 0x20) = vtbl_PFRecordRead_IStream;
    if (*(int*)(raw + 0x1c) != 0) {
        PFRecordOwner* owner = (PFRecordOwner*)*(void**)(raw + 0x18);
        owner->OnStreamRelease(this);
    }
    ((MemoryStream*)(raw + 0x2c))->Destroy();
    *(void**)(raw + 0x20) = vtbl_IStream_default;
    *(void**)raw = vtbl_ZoneObject_PFRecordWrite;
    if (flags & 1)
        ZoneObject_delete(this);
    return this;
}

// ===========================================================================
// 0x008dcdc0  PFRecordRead::PFRecordRead(const PFRecordInfo&, const Key&, DatabasePackedFile*)
// ===========================================================================
// @ 0x008dcdc0
PFRecordRead::PFRecordRead(const PFRecordInfo& info, const Key& key, DatabasePackedFile* parent)
{
    *(void**)raw = vtbl_ZoneObject_PFRecordRead;
    _InterlockedExchange((volatile long*)(raw + 4), 0);
    *(void**)raw = vtbl_PFRecordRead_base;
    *(unsigned*)(raw + 8) = 0x12e4a891;                 // kPFRecordTypeRead
    *(uint32*)(raw + 0xc) = key.mInstance;
    *(uint32*)(raw + 0x10) = key.mType;
    *(uint32*)(raw + 0x14) = key.mGroup;
    *(void**)(raw + 0x18) = parent;
    *(unsigned*)(raw + 0x1c) = 1;
    *(void**)(raw + 0x20) = vtbl_IStream_default;
    InitReadStream(this);
    *(unsigned*)(raw + 0x50) = info.mf[0];
    *(unsigned*)(raw + 0x54) = info.mf[1];
    *(unsigned*)(raw + 0x58) = info.mf[2];
    *(unsigned*)(raw + 0x5c) = info.mf[3];
    *(unsigned*)(raw + 0x60) = 0;
    *(unsigned*)(raw + 0x64) = 0;
    *(unsigned char*)(raw + 0x68) = 0;
    _InterlockedExchange((volatile long*)(raw + 0x6c), 1);
    if (*(uint16*)(raw + 0x5c) != 0) {
        *(unsigned*)(raw + 0x64) = *(unsigned*)(raw + 0x58);
        *(unsigned char*)(raw + 0x68) = 1;
        return;
    }
    *(unsigned*)(raw + 0x64) = *(unsigned*)(raw + 0x54);
    if (*(unsigned*)(raw + 0x64) <= 0x200)
        *(unsigned char*)(raw + 0x68) = 1;
}

// ===========================================================================
// 0x008dcea0  PFRecordWrite::PFRecordWrite(unsigned, unsigned, const Key&, DatabasePackedFile*)
// ===========================================================================
// @ 0x008dcea0
PFRecordWrite::PFRecordWrite(unsigned access, unsigned size, const Key& key, DatabasePackedFile* parent)
{
    *(void**)raw = vtbl_ZoneObject_PFRecordRead;
    _InterlockedExchange((volatile long*)(raw + 4), 0);
    *(void**)raw = vtbl_PFRecordRead_base;
    *(unsigned*)(raw + 8) = 0x12e4a892;                 // kPFRecordTypeWrite
    *(uint32*)(raw + 0xc) = key.mInstance;
    *(uint32*)(raw + 0x10) = key.mType;
    *(uint32*)(raw + 0x14) = key.mGroup;
    *(void**)(raw + 0x18) = parent;
    *(unsigned*)(raw + 0x1c) = 3;
    *(void**)(raw + 0x20) = vtbl_IStream_default;
    *(void**)raw = vtbl_PFRecordWrite;
    *(void**)(raw + 0x20) = vtbl_PFRecordWrite_IStream;
    MemStreamW* ms = (MemStreamW*)(raw + 0x24);
    ms->Construct("ResourceMan/PFRecordWrite");
    FileStream* fs = (FileStream*)(raw + 0x48);
    fs->Construct(0);
    *(unsigned char*)(raw + 0x274) = 0;
    _InterlockedExchange((volatile long*)(raw + 0x278), 1);
    ms->w01();
    fs->f01();
    ms->SetOption(1, 1.0f);
    ms->SetOption(2, 1.5f);
    ms->SetOption(3, 1024.0f);
    if (size == 0)
        return;
    if (size <= 0x1e8480 || *(unsigned char*)(raw + 0x274) != 0)
        goto tail;
    *(unsigned char*)(raw + 0x274) = 1;
    if (!OpenTempFile())
        goto tail;
    {
        IAllocator* alloc = ((DatabasePackedFile*)*(void**)(raw + 0x18))->GetAllocator();
        void* buf = alloc->Alloc(0x4000, "Resource/Raw", 0);
        if (buf == 0)
            goto deltemp;
        unsigned done = 0;
        char ok = 1;
        while (done < size && ok) {
            unsigned chunk = size - done;
            if (chunk > 0x4000)
                chunk = 0x4000;
            ok = ((DatabasePackedFile*)*(void**)(raw + 0x18))->ReadFileSpan(
                     buf, done, (int)chunk) ? 1 : 0;
            if (ok) {
                ok = fs->f14() ? 1 : 0;
                done += chunk;
            }
        }
        if (ok)
            fs->f10(0, 0);
        alloc->Free(buf, 0);
        if (ok)
            return;
    }
deltemp:
    DeleteTempFile();
tail:
    {
        IAllocator* alloc = ((DatabasePackedFile*)*(void**)(raw + 0x18))->GetAllocator();
        if (ms->SetData(0, size, 0, 1, alloc))
            ((DatabasePackedFile*)*(void**)(raw + 0x18))->WriteFileSpan(ms->GetData(), 0, (int)size);
    }
    (void)access;
}
