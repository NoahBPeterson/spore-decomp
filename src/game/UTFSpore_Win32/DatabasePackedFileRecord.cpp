// src/game/UTFSpore_Win32/DatabasePackedFileRecord.cpp -- migrated from slice(s) s008dc1a0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DatabasePackedFileRecord.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/PFRecordRead.h"
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/IO/FileStream.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/ResourceMan/Key.h"
#include "EA/IO/MemoryStream.h"
#include "EA/ResourceMan/PFIndexModifiable.h"
#include "EA/ResourceMan/PFRecordInfo.h"
#include "EA/ResourceMan/PFRecordWrite.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern "C" void* __cdecl ZoneObject_delete(void* p);                          // 0x926060
extern char vtbl_ZoneObject_PFRecordRead[];   // 0x13effa8
extern char vtbl_ZoneObject_PFRecordWrite[];  // 0x13effb8
extern char vtbl_PFRecordRead_base[];         // 0x140a2e0
extern char vtbl_IStream_default[];           // 0x13f3a68
extern char vtbl_PFRecordRead[];              // 0x1436900
extern char vtbl_PFRecordRead_IStream[];      // 0x14368c4
#include <string.h>
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedDecrement, _InterlockedExchange)

// ---- items of slice s008dc1a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint32;
typedef unsigned short uint16;
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern "C" void* __cdecl ZoneObject_delete(void* p);                          // 0x926060
struct Key { uint32 mInstance; uint32 mType; uint32 mGroup; };   // 0xc
struct IAllocator {
    virtual void a0();                          // +0x00
    virtual void a1();                          // +0x04
    virtual void* Alloc(unsigned size, const char* name, unsigned flags); // +0x08
    virtual void  Free(void* p, unsigned size);                           // +0x0c
    virtual void a4();                          // +0x10
};
struct PFRecordInfo { uint32 mf[4]; };          // 0x10
struct DatabasePackedFile {                     // 0x384
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual IAllocator* GetAllocator();         // +0x48
    bool ReadFileSpan(void* dst, unsigned offset, int size);            // 0x8d9050
    bool WriteFileSpan(const void* src, unsigned offset, int size);     // 0x8d90e0
    bool DecompressRecord(uint16 type, unsigned src, unsigned a, unsigned b, void* out); // 0x8d9320
};
struct PFRecordOwner {
virtual void o00();
virtual void o01();
virtual void o02();
virtual void o03();
virtual void o04();
virtual void o05();
virtual void o06();
virtual void o07();
virtual void o08();
virtual void o09();
virtual void o10();
virtual void o11();
virtual void o12();
virtual void o13();
virtual void o14();
    virtual bool OnStreamRelease(void* stream);  // +0x3c
};
struct MemoryStream {
virtual void r00();
virtual void r01();
virtual void r02();
virtual void r03();
virtual void r04();
virtual void r05();
virtual void r06();
virtual int r07();
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
extern char vtbl_ZoneObject_PFRecordRead[];   // 0x13effa8
extern char vtbl_ZoneObject_PFRecordWrite[];  // 0x13effb8
extern char vtbl_PFRecordRead_base[];         // 0x140a2e0
extern char vtbl_IStream_default[];           // 0x13f3a68
extern char vtbl_PFRecordRead[];              // 0x1436900
extern char vtbl_PFRecordRead_IStream[];      // 0x14368c4
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
// ---- items of slice s008dc1a0 end

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

// @ 0x008dca50
bool PFRecordReadIstream::IStreamAddRef()
{
    volatile long* p = (volatile long*)((char*)this + 0x6c);
    if (_InterlockedExchangeAdd(p, 0) == 0)
        return false;
    _InterlockedExchangeAdd(p, 1);
    return true;
}

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

// @ 0x008dcc50
bool PFRecordWrite::IStreamAddRef()
{
    volatile long* p = (volatile long*)(raw + 0x278);
    if (_InterlockedExchangeAdd(p, 0) == 0)
        return false;
    _InterlockedExchangeAdd(p, 1);
    return true;
}

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
