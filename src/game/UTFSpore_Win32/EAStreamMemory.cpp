// src/game/UTFSpore_Win32/EAStreamMemory.cpp -- migrated from slice(s) s0093b9e0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAStreamMemory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/MemoryStream.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/IO/IStream.h"
#include "EA/IO/SharedPointer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);          // 0x011e0744
extern "C" void  EASTL_deallocate(void* p);                                  // 0x00f47380
extern "C" void  ZoneObject_delete(void* p);                                  // 0x00926060
extern "C" void* AllocNamed(size_t n, void* alloc, int flags);               // 0x00925fe0
extern "C" void* DefaultAllocator();                                         // 0x00925cb0
extern "C" unsigned __cdecl strlen(const char*);
extern "C" unsigned __cdecl wcslen(const wchar_t*);
extern void* g_vtbl_bg6;       // 0x013effb8 (first base vtable)
extern void* g_vtbl_hkref;     // 0x013ef094 (second base vtable)
extern void* g_vtbl_bg;        // 0x0143eb74 (BackgroundLoading vtable, +0)
extern void* g_vtbl_bg2;       // 0x0143eb70 (BackgroundLoading vtable, +4)
extern void* g_vtbl_gfar;      // 0x013f3a68 (base vtable)
extern void* g_vtbl_gfar_b;    // 0x0143eb78 (GraphicsFactoryAsyncRequest vtable)
#include <intrin.h>
#include <new>
#pragma intrinsic(strlen)
#pragma intrinsic(wcslen)

// ---- items of slice s0093b9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
typedef unsigned int size_type;
extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);          // 0x011e0744
extern "C" void  EASTL_deallocate(void* p);                                  // 0x00f47380
extern "C" void  ZoneObject_delete(void* p);                                  // 0x00926060
extern "C" void* AllocNamed(size_t n, void* alloc, int flags);               // 0x00925fe0
extern "C" void* DefaultAllocator();                                         // 0x00925cb0
namespace EA {
namespace IO {
class SharedPointer_s0093_b9e0 { public:
    // +4 is a second base subobject (hkReferencedObject): its own vptr then a refcount.
    struct SharedRef {
        void* vtable;            // +0 (SharedPointer +4)
        long  mnRefCount;        // +4 (SharedPointer +8)
    };
    void*     vtable;            // +0
    SharedRef base2;             // +4
    void*     mpAllocator;       // +0c
    long      field_10;          // +10
    unsigned char field_14;      // +14
    SharedPointer_s0093_b9e0(void* pData, unsigned char freeData, void* alloc);
    SharedPointer_s0093_b9e0* Init(void* pData, unsigned nSize);                        // 0x0093bca0
    SharedPointer_s0093_b9e0* InitWithAlloc(void* pData, void* alloc, unsigned nSize);  // 0x0093bcf0
    void* Destroy(unsigned char flags);                                      // 0x0093bd90
};
}
}
namespace EA {
namespace IO {
inline void SharedRelease(SharedPointer_s0093_b9e0* p)
{
    if (p != 0) {
        SharedPointer_s0093_b9e0::SharedRef* r = &p->base2;
        long remaining = _InterlockedDecrement(&r->mnRefCount);
        if (remaining == 0) {
            _InterlockedExchange(&r->mnRefCount, 1);
            if (r != 0) {
                // The second base's vtable slot 0 is its Release/delete hook; `this` is the
                // base subobject (p + 4), not the vptr value (hybrid crash at 0x93bd97).
                typedef void (__thiscall *Fn)(void*, int);
                Fn fn = *(Fn*)r->vtable;
                fn(r, 1);
            }
        }
    }
}
}
}
namespace EA {
namespace IO {
class IStream_s0093_b9e0 {
public:
    virtual ~IStream_s0093_b9e0() {}
    virtual int AddRef();
    virtual int Release();
    virtual uint32 GetType() const;
    virtual int GetAccessFlags() const;
    virtual int GetState() const;
    virtual bool Close();
    virtual size_type GetSize() const;
    virtual bool SetSize(size_type size);
    virtual int GetPosition(int type) const;
    virtual bool SetPosition(int distance, int type);
    virtual int GetAvailable() const;
    virtual int Read(void* pData, size_t nSize);
    virtual bool Flush();
    virtual int Write(const void* pData, size_t nSize);
};
}
}
namespace EA {
namespace IO {
class MemoryStream_s0093_b9e0 : public IStream_s0093_b9e0 {
public:
    MemoryStream_s0093_b9e0(void* pData, size_type nSize, unsigned char copy, int a, void* alloc, int unused);  // 0x0093c2c0 (EA::IO::MemoryStream::MemoryStream_s0093_b9e0)
    ~MemoryStream_s0093_b9e0();  // 0x0093c2c0 (EA::IO::MemoryStream::MemoryStream_s0093_b9e0)

    bool SetData(void* pData, size_type nSize, unsigned char copy, unsigned char freeData, void* alloc);  // 0x0093be30 (EA::IO::MemoryStream::SetData)
    bool Clear();  // 0x0093c320 (EA::IO::MemoryStream::Clear)
    bool Grow(size_type size);  // 0x0093c000 (EA::IO::MemoryStream::Grow)
    bool WriteBuffer(const void* pData, size_type nSize);  // 0x0093c150 (EA::IO::MemoryStream::WriteBuffer)
    int  ReadBuffer(void* pData, size_type nSize);  // 0x0093bbf0 (EA::IO::MemoryStream::ReadBuffer)
    bool SetSizeEx(size_type size);  // 0x0093c130 (EA::IO::MemoryStream::SetSizeEx)
    virtual bool SetSize(size_type size);  // 0x0093c370 (EA::IO::MemoryStream::SetSize)
    virtual bool SetPosition(int distance, int type);  // 0x0093c0c0 (EA::IO::MemoryStream::SetPosition)
    virtual int  Write(const void* pData, size_t nSize);

    SharedPointer_s0093_b9e0* mpSharedPointer;  // +04
    int            mnRefCount;       // +08
    size_type      mnSize;           // +0c
    size_type      mnCapacity;       // +10
    size_type      mnPosition;       // +14
    bool           mbResizeEnabled;  // +18
    bool           mbLocked;         // +19
    float          mfResizeFactor;   // +1c
    int            mnResizeIncrement;// +20
};
}
}
namespace EA {
namespace IO {
class GraphicsFactoryAsyncRequest {
public:
    GraphicsFactoryAsyncRequest();
    GraphicsFactoryAsyncRequest(void* pData, void* nSize, int unused);

    float GetProperty(int index);
    void  SetProperty(int index, float value);
    bool  Attach(void* pData, size_type nSize);

    void*          mpVtbl;           // +00
    SharedPointer_s0093_b9e0* mpData;           // +04
    int            mnField08;        // +08
    size_type      mnSize;           // +0c
    size_type      mnCapacity;       // +10
    size_type      mnPosition;       // +14
    bool           mbFlag18;         // +18
    bool           mbFlag19;         // +19
    float          mfFactor;         // +1c
    int            mnIncrement;      // +20
};
}
}
struct ICoreAllocator_s0093_b9e0 {
    virtual void v0();
    virtual void v1();
    virtual void* Alloc(void* pData, unsigned nSize, int flags);  // slot 2
    virtual void  Free(void* pData, int flags);                   // slot 3
};
extern void* g_vtbl_bg6;       // 0x013effb8 (first base vtable)
extern void* g_vtbl_hkref;     // 0x013ef094 (second base vtable)
extern void* g_vtbl_bg;        // 0x0143eb74 (BackgroundLoading vtable, +0)
extern void* g_vtbl_bg2;       // 0x0143eb70 (BackgroundLoading vtable, +4)
void* g_vtbl_bg = 0;           // stand-in storage: the real vtable lives in another object file
extern void* g_vtbl_gfar;      // 0x013f3a68 (base vtable)
extern void* g_vtbl_gfar_b;    // 0x0143eb78 (GraphicsFactoryAsyncRequest vtable)
// ---- items of slice s0093b9e0 end

// @ 0x0093bc40
namespace EA { namespace IO {
SharedPointer_s0093_b9e0::SharedPointer_s0093_b9e0(void* pData, unsigned char freeData, void* alloc)
{
    vtable = (void*)&g_vtbl_bg6;
    base2.vtable = (void*)&g_vtbl_hkref;
    _InterlockedExchange(&base2.mnRefCount, 0);
    vtable = (void*)&g_vtbl_bg;
    base2.vtable = (void*)&g_vtbl_bg2;
    if (alloc == 0)
        alloc = DefaultAllocator();
    mpAllocator = alloc;
    field_10 = (long)pData;
    field_14 = freeData;
}
}}  // namespace EA::IO

// @ 0x0093bca0
EA::IO::SharedPointer_s0093_b9e0* EA::IO::SharedPointer_s0093_b9e0::Init(void* pData, unsigned nSize)
{
    vtable = (void*)&g_vtbl_bg6;
    base2.vtable = (void*)&g_vtbl_hkref;
    _InterlockedExchange(&base2.mnRefCount, 0);
    vtable = (void*)&g_vtbl_bg;
    base2.vtable = (void*)&g_vtbl_bg2;
    mpAllocator = DefaultAllocator();
    field_10 = (long)((ICoreAllocator_s0093_b9e0*)mpAllocator)->Alloc(pData, nSize, 0);
    field_14 = 1;
    return this;
}

// @ 0x0093bcf0
EA::IO::SharedPointer_s0093_b9e0* EA::IO::SharedPointer_s0093_b9e0::InitWithAlloc(void* pData, void* alloc, unsigned nSize)
{
    vtable = (void*)&g_vtbl_bg6;
    base2.vtable = (void*)&g_vtbl_hkref;
    _InterlockedExchange(&base2.mnRefCount, 0);
    vtable = (void*)&g_vtbl_bg;
    base2.vtable = (void*)&g_vtbl_bg2;
    if (alloc == 0)
        alloc = DefaultAllocator();
    mpAllocator = alloc;
    field_10 = (long)((ICoreAllocator_s0093_b9e0*)alloc)->Alloc(pData, nSize, 0);
    field_14 = 1;
    return this;
}

// @ 0x0093bd50
void* __fastcall FUN_0093bd50(void* self, int unused, int unused2)
{
    EA::IO::GraphicsFactoryAsyncRequest* p = (EA::IO::GraphicsFactoryAsyncRequest*)self;
    p->mpVtbl = (void*)&g_vtbl_gfar_b;
    p->mpData = 0;
    p->mnField08 = 0;
    p->mnSize = 0;
    p->mnCapacity = 0;
    p->mnPosition = 0;
    p->mbFlag18 = false;
    p->mbFlag19 = false;
    p->mfFactor = 1.5f;
    p->mnIncrement = 0;
    return self;
}

// @ 0x0093bd90
void* EA::IO::SharedPointer_s0093_b9e0::Destroy(unsigned char flags)
{
    vtable = (void*)&g_vtbl_bg;
    base2.vtable = (void*)&g_vtbl_bg2;
    if (field_14 != 0)
        ((ICoreAllocator_s0093_b9e0*)mpAllocator)->Free((void*)field_10, 0);
    base2.vtable = (void*)&g_vtbl_hkref;
    vtable = (void*)&g_vtbl_bg6;
    if (flags & 1)
        ZoneObject_delete(this);
    return this;
}

// @ 0x0093bde0
void __fastcall FUN_0093bde0(EA::IO::GraphicsFactoryAsyncRequest* self)
{
    self->mpVtbl = (void*)&g_vtbl_gfar_b;
    EA::IO::SharedRelease(self->mpData);
    self->mpVtbl = (void*)&g_vtbl_gfar;
}

// @ 0x0093be30
bool __thiscall EA::IO::MemoryStream_s0093_b9e0::SetData(void* pData, size_type nSize, unsigned char copy, unsigned char freeData, void* alloc)
{
    bool result = false;
    if (pData == 0 && nSize == 0) {
        SharedRelease(mpSharedPointer);
        mpSharedPointer = 0;
    } else {
        if (alloc == 0)
            alloc = DefaultAllocator();
        void* data = pData;
        if (copy == 0)
            data = ((void*(__thiscall*)(void*, size_type, int, int))((void**)alloc)[2])(alloc, nSize, 0, 0);
        if (data == 0)
            goto done;
        SharedRelease(mpSharedPointer);
        {
            SharedPointer_s0093_b9e0* sp = (SharedPointer_s0093_b9e0*)AllocNamed(0x18, alloc, 0);
            if (sp != 0)
                sp = new ((void*)sp) SharedPointer_s0093_b9e0(data, freeData, alloc);
            mpSharedPointer = sp;
            if (sp == 0)
                goto done;
            _InterlockedIncrement(&sp->base2.mnRefCount);
            if (pData != 0 && nSize != 0 && copy == 0)
                MemCpyThunk(data, pData, nSize);
        }
    }
    result = true;
done:
    if (mpSharedPointer == 0) {
        mnCapacity = 0;
        mnPosition = 0;
        mnSize = 0;
    } else {
        mnCapacity = nSize;
        mnPosition = 0;
        mnSize = nSize;
    }
    return result;
}

// @ 0x0093bf70
bool __thiscall EA::IO::GraphicsFactoryAsyncRequest::Attach(void* pData, size_type nSize)
{
    if (mpData != (EA::IO::SharedPointer_s0093_b9e0*)pData) {
        if (pData != 0)
            _InterlockedIncrement(&((EA::IO::SharedPointer_s0093_b9e0*)pData)->base2.mnRefCount);
        EA::IO::SharedRelease(mpData);
        mpData = (EA::IO::SharedPointer_s0093_b9e0*)pData;
    }
    EA::IO::SharedPointer_s0093_b9e0* p = mpData;
    if (p != 0) {
        mnSize = nSize;
        mnCapacity = nSize;
    } else {
        mnSize = 0;
        mnCapacity = 0;
    }
    mnPosition = 0;
    return p != 0;
}

// @ 0x0093c000
bool __thiscall EA::IO::MemoryStream_s0093_b9e0::Grow(size_type nSize)
{
    void* alloc;
    if (mpSharedPointer != 0 && mpSharedPointer->mpAllocator != 0)
        alloc = mpSharedPointer->mpAllocator;
    else
        alloc = DefaultAllocator();
    SharedPointer_s0093_b9e0* sp = 0;
    if (nSize != 0) {
        sp = (SharedPointer_s0093_b9e0*)AllocNamed(0x18, alloc, 0);
        if (sp == 0)
            return false;
        sp->InitWithAlloc(0, alloc, nSize);
        if (sp == 0)
            return false;
        _InterlockedIncrement(&sp->base2.mnRefCount);
    }
    if (mpSharedPointer != 0) {
        if (sp != 0) {
            size_type copy = mnCapacity;
            if (nSize < mnCapacity)
                copy = nSize;
            MemCpyThunk((void*)sp->field_10, (void*)mpSharedPointer->field_10, copy);
        }
        SharedRelease(mpSharedPointer);
    }
    mpSharedPointer = sp;
    mnCapacity = nSize;
    return true;
}

// @ 0x0093c0c0
bool __thiscall EA::IO::MemoryStream_s0093_b9e0::SetPosition(int distance, int type)
{
    size_type oldPos = mnPosition;
    if (type == 0) {
        mnPosition = distance;
    } else if (type == 1) {
        mnPosition = oldPos + distance;
    } else if (type == 2) {
        mnPosition = mnSize + distance;
    }
    if (mnPosition > mnSize) {
        if (!mbResizeEnabled) {
            mnPosition = mnSize;
            return false;
        }
        if (!Grow(mnPosition)) {
            mnPosition = oldPos;
            return false;
        }
    }
    return true;
}

// @ 0x0093c130
bool __thiscall EA::IO::MemoryStream_s0093_b9e0::SetSizeEx(size_type size)
{
    if (size > mnCapacity)
        return Grow(size);
    return false;
}

// @ 0x0093c150
bool __thiscall EA::IO::MemoryStream_s0093_b9e0::WriteBuffer(const void* pData, size_type nSize)
{
    if (mbLocked)
        return false;
    if (nSize == 0)
        return true;
    size_type cap = mnCapacity;
    size_type end = mnPosition + nSize;
    size_type take = nSize;
    if (end > cap) {
        if (!mbResizeEnabled) {
            take = mnSize - mnPosition;
            goto copy;
        }
        float want = (float)cap * mfResizeFactor + (float)mnResizeIncrement;
        // The retail object was built without SSE: its float->unsigned conversion is an x87 fistp,
        // i.e. round-to-nearest, not the truncation a C++ cast performs here.
        size_type need = (size_type)(want < 0.0f ? want - 0.5f : want + 0.5f);
        if (need < end)
            need = end;
        if (!Grow(need))
            return false;
    } else if (end > mnSize) {
        mnSize = end;
    }
copy:
    MemCpyThunk((char*)mpSharedPointer->field_10 + mnPosition, pData, take);
    mnPosition += take;
    return take == nSize;
}

// @ 0x0093c210
void* FUN_0093c210(void* self, unsigned char flags)
{
    *(void**)self = (void*)&g_vtbl_gfar;
    EA::IO::SharedPointer_s0093_b9e0* p = (EA::IO::SharedPointer_s0093_b9e0*)((void**)self)[1];
    if (p != 0)
        EA::IO::SharedRelease(p);
    *(void**)self = (void*)&g_vtbl_gfar;
    if (flags & 1)
        EASTL_deallocate(self);
    return self;
}

// @ 0x0093c270
EA::IO::GraphicsFactoryAsyncRequest::GraphicsFactoryAsyncRequest(void* pData, void* nSize, int unused)
{
    *(void**)this = (void*)&g_vtbl_gfar_b;
    mpData = 0;
    mnField08 = 0;
    mnSize = 0;
    mnCapacity = 0;
    mnPosition = 0;
    mbFlag18 = false;
    mbFlag19 = false;
    mfFactor = 1.5f;
    mnIncrement = 0;
    if (pData != 0 && nSize != 0)
        Attach(pData, (size_type)nSize);
}

// @ 0x0093c2c0
EA::IO::MemoryStream_s0093_b9e0::MemoryStream_s0093_b9e0(void* pData, size_type nSize, unsigned char copy, int a, void* alloc, int unused)
{
    mpSharedPointer = 0;
    mnRefCount = 0;
    mnSize = 0;
    mnCapacity = 0;
    mnPosition = 0;
    mbResizeEnabled = false;
    mbLocked = false;
    mfResizeFactor = 1.5f;
    mnResizeIncrement = 0;
    if (pData != 0 && nSize != 0)
        SetData(pData, nSize, copy, (unsigned char)a, alloc);
}

// @ 0x0093c370
bool __thiscall EA::IO::MemoryStream_s0093_b9e0::SetSize(size_type size)
{
    if (mbLocked)
        return false;
    bool result = true;
    if (size != mnSize) {
        if (mbResizeEnabled) {
            if (size < mnSize) {
                mnSize = size;
                if (mnPosition > size)
                    mnPosition = size;
            } else {
                result = Grow(size);
                if (result)
                    mnSize = size;
            }
        } else
            result = false;
    }
    return result;
}
