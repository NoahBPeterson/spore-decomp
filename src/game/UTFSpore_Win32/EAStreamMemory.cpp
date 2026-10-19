// src/game/UTFSpore_Win32/EAStreamMemory.cpp -- migrated from slice(s) s0093b9e0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAStreamMemory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/MemoryStream.h"
#include "EA/IO/IStream.h"
#include "EA/IO/SharedPointer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);          // 0x011e0744
extern "C" void  EASTL_deallocate(void* p);                                  // 0x00f47380
extern "C" void* AllocNamed(size_t n, void* alloc, int flags);               // 0x00925fe0
extern "C" void* DefaultAllocator();                                         // 0x00925cb0
extern void* g_vtbl_bgloading;
extern void* g_vtbl_bgloading_a;
extern void* g_vtbl_bgloading_b;
extern void* g_vtbl_gfar;   // 0x013f3a68 (equiv t3)
#include <intrin.h>
#include <new>

// ---- items of slice s0093b9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
typedef unsigned int size_type;
extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);          // 0x011e0744
extern "C" void  EASTL_deallocate(void* p);                                  // 0x00f47380
extern "C" void* AllocNamed(size_t n, void* alloc, int flags);               // 0x00925fe0
extern "C" void* DefaultAllocator();                                         // 0x00925cb0
namespace EA {
namespace IO {
struct SharedPointer_s0093_b9e0 {
    void* vtable;            // +0
    void* vtable2;           // +4
    long  mnRefCount;        // +8
    void* mpAllocator;       // +0c
    long  field_10;          // +10
    unsigned char field_14;  // +14
    SharedPointer_s0093_b9e0(void* pData, void* alloc, unsigned char freeData);
};
}
}
namespace EA {
namespace IO {
inline void SharedRelease(SharedPointer_s0093_b9e0* p)
{
    if (p != 0) {
        if (_InterlockedDecrement(&p->mnRefCount) == 0) {
            _InterlockedExchange(&p->mnRefCount, 1);
            if (p->vtable2 != 0) {
                // +4 is the second base's vptr (multiple inheritance): the original calls slot 0
                // of that vtable with this = p + 4 (the base subobject), not with the vptr value
                // (hybrid crash at 0x93bd97, 2026-10-12: a dtor ran on the vtable as `this`).
                typedef void (__thiscall *Fn)(void*, int);
                (*(Fn*)p->vtable2)((char*)p + 4, 1);
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
    MemoryStream_s0093_b9e0(void* pData, size_type nSize, unsigned char copy, int a, void* alloc);
    ~MemoryStream_s0093_b9e0();

    bool SetData(void* pData, size_type nSize, unsigned char copy, void* a, void* b, void* alloc);  // 0x0093be30 (EA::IO::MemoryStream::SetData)
    bool Clear();
    bool Grow(size_type size);
    int  WriteBuffer(const void* pData, size_type nSize);
    int  ReadBuffer(void* pData, size_type nSize);
    bool SetSizeEx(size_type size);
    virtual bool SetSize(size_type size);
    virtual bool SetPosition(int distance, int type);
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
    GraphicsFactoryAsyncRequest(void* pData, void* nSize);

    float GetProperty(int index);
    void  SetProperty(int index, float value);
    int   Attach(void* pData, size_type nSize);

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
extern void* g_vtbl_bgloading;
extern void* g_vtbl_bgloading_a;
extern void* g_vtbl_bgloading_b;
extern void* g_vtbl_gfar;   // 0x013f3a68 (equiv t3)
// ---- items of slice s0093b9e0 end

// @ 0x0093bc40
namespace EA { namespace IO {
SharedPointer_s0093_b9e0::SharedPointer_s0093_b9e0(void* pData, void* alloc, unsigned char freeData)
{
    vtable = 0;
    vtable2 = 0;
    mnRefCount = 0;
    mpAllocator = alloc;
    field_14 = freeData;
    field_10 = (long)pData;
    if (mpAllocator == 0)
        mpAllocator = (void*)&DefaultAllocator;
}
}}  // namespace EA::IO

// @ 0x0093bca0
void* FUN_0093bca0(void* self, void* pData, size_type nSize, void* a)
{
    *(void**)self = (void*)&g_vtbl_bgloading;
    ((long*)self)[1] = 0;
    ((long*)self)[2] = 0;
    ((long*)self)[3] = (long)&DefaultAllocator;
    void* r = ((void*(__thiscall*)(void*, void*, void*, void*, int))((void**)DefaultAllocator())[2])(DefaultAllocator(), pData, a, 0, 0);
    ((long*)self)[4] = (long)r;
    *((char*)self + 0x14) = 1;
    return self;
}

// @ 0x0093bcf0
void** FUN_0093bcf0(void** self, void* pData, void* allocArg, void* a)
{
    *self = (void*)&g_vtbl_bgloading;
    self[1] = 0;
    self[2] = 0;
    self[3] = allocArg ? allocArg : (void*)&DefaultAllocator;
    void* r = ((void*(__thiscall*)(void*, void*, void*, int))((void**)self[3])[2])(self[3], pData, a, 0);
    self[4] = r;
    *((char*)self + 0x14) = 1;
    return self;
}

// @ 0x0093bd50
void __fastcall FUN_0093bd50(void* self, int unused)
{
    *(void**)self = (void*)&g_vtbl_gfar;
    ((long*)self)[1] = 0;
    ((long*)self)[2] = 0;
    ((long*)self)[3] = 0;
    ((long*)self)[4] = 0;
    ((long*)self)[5] = 0;
    *((char*)self + 0x18) = 0;
    *((char*)self + 0x19) = 0;
    *(float*)((char*)self + 0x1c) = 1.5f;
    ((long*)self)[8] = 0;
}

// @ 0x0093bd90
void* FUN_0093bd90(void* self, unsigned char flags)
{
    *(void**)self = (void*)&g_vtbl_bgloading_a;
    ((long*)self)[1] = (long)&g_vtbl_bgloading_b;
    if (*((char*)self + 0x14) != 0) {
        void* alloc = ((void**)self)[3];
        void* data = ((void**)self)[4];
        (*(void(__thiscall*)(void*, void*, int))((void**)alloc)[3])(alloc, data, 0);
    }
    *(void**)self = (void*)&g_vtbl_bgloading;
    if (flags & 1)
        EASTL_deallocate(self);
    return self;
}

// @ 0x0093bde0
void __fastcall FUN_0093bde0(void* self)
{
    *(void**)self = (void*)&g_vtbl_gfar;
    EA::IO::SharedPointer_s0093_b9e0* p = (EA::IO::SharedPointer_s0093_b9e0*)((void**)self)[1];
    if (p != 0)
        EA::IO::SharedRelease(p);
    *(void**)self = (void*)&g_vtbl_gfar;
}

// @ 0x0093be30
bool __thiscall EA::IO::MemoryStream_s0093_b9e0::SetData(void* pData, size_type nSize, unsigned char copy, void* a, void* b, void* alloc)
{
    bool result = false;
    if (pData == 0 && nSize == 0) {
        SharedRelease(mpSharedPointer);
        mpSharedPointer = 0;
    } else {
        if (alloc == 0)
            alloc = (void*)&DefaultAllocator;
        void* data = pData;
        if (copy == 0)
            data = ((void*(__thiscall*)(void*, size_type, int, int))((void**)alloc)[2])(alloc, nSize, 0, 0);
        if (data == 0)
            goto done;
        SharedRelease(mpSharedPointer);
        {
            SharedPointer_s0093_b9e0* sp = (SharedPointer_s0093_b9e0*)AllocNamed(0x18, alloc, 0);
            if (sp != 0)
                sp = new ((void*)sp) SharedPointer_s0093_b9e0(data, alloc, 0);
            mpSharedPointer = sp;
            if (sp == 0)
                goto done;
            _InterlockedIncrement(&sp->mnRefCount);
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
int __thiscall EA::IO::GraphicsFactoryAsyncRequest::Attach(void* pData, size_type nSize)
{
    if (mpData != (EA::IO::SharedPointer_s0093_b9e0*)pData) {
        if (pData != 0)
            _InterlockedIncrement(&((EA::IO::SharedPointer_s0093_b9e0*)pData)->mnRefCount);
        EA::IO::SharedRelease(mpData);
        mpData = (EA::IO::SharedPointer_s0093_b9e0*)pData;
    }
    if (mpData == 0) {
        mnSize = 0;
        mnCapacity = 0;
    } else {
        mnSize = nSize;
        mnCapacity = nSize;
    }
    mnPosition = 0;
    return mpData != 0;
}

// @ 0x0093c000
bool __thiscall EA::IO::MemoryStream_s0093_b9e0::Grow(size_type nSize)
{
    void* alloc = (void*)&DefaultAllocator;
    if (mpSharedPointer != 0 && mpSharedPointer->mpAllocator != 0)
        alloc = mpSharedPointer->mpAllocator;
    SharedPointer_s0093_b9e0* sp = 0;
    if (nSize != 0) {
        sp = (SharedPointer_s0093_b9e0*)AllocNamed(0x18, alloc, 0);
        if (sp == 0)
            return false;
        sp = new ((void*)sp) SharedPointer_s0093_b9e0((void*)nSize, alloc, 0);
        if (sp == 0)
            return false;
        _InterlockedIncrement(&sp->mnRefCount);
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
int __thiscall EA::IO::MemoryStream_s0093_b9e0::WriteBuffer(const void* pData, size_type nSize)
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
        size_type need = (size_type)((float)cap * mfResizeFactor + (float)mnResizeIncrement);
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
EA::IO::GraphicsFactoryAsyncRequest::GraphicsFactoryAsyncRequest(void* pData, void* nSize)
{
    *(void**)this = (void*)&g_vtbl_gfar;
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
EA::IO::MemoryStream_s0093_b9e0::MemoryStream_s0093_b9e0(void* pData, size_type nSize, unsigned char copy, int a, void* alloc)
{
    *(void**)this = (void*)&g_vtbl_gfar;
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
        SetData(pData, nSize, copy, (void*)a, alloc, alloc);
}
