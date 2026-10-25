// Spore retail 0093b9e0..0093c920 -- App::memorystream, EA::IO::MemoryStream,
// GraphicsFactoryAsyncRequest and EA::Text helpers (retail layout confirmed by disasm).

#include "types.h"
#include <intrin.h>
#include <new>

typedef unsigned int uint32;
typedef unsigned int size_type;

extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);          // 0x011e0744
extern "C" void  EASTL_deallocate(void* p);                                  // 0x00f47380
extern "C" void* EASTL_allocate(size_t n, const char*, int, int, int, int);  // 0x00f473a0
extern "C" void* AllocNamed(size_t n, void* alloc, int flags);               // 0x00925fe0
extern "C" void* DefaultAllocator();                                         // 0x00925cb0
extern "C" int   fputs(const char*, void*);
extern "C" void* __iob_func();
extern "C" unsigned __cdecl strlen(const char*);
extern "C" unsigned __cdecl wcslen(const wchar_t*);
#pragma intrinsic(strlen)
#pragma intrinsic(wcslen)

namespace EA { namespace Text {
int ConvertEncoding(const void* src, size_t srcCount, int srcEnc, void* dst, int* dstLen, int dstEnc); // 0x0093c950
int GetCharacterSize(int encoding);
}}

namespace EA { namespace IO {

class SharedPointer { public:
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
    SharedPointer(void* pData, unsigned char freeData, void* alloc);
    SharedPointer* Init(void* pData, unsigned nSize);                        // 0x0093bca0
    SharedPointer* InitWithAlloc(void* pData, void* alloc, unsigned nSize);  // 0x0093bcf0
    void* Destroy(unsigned char flags);                                      // 0x0093bd90
};

inline void SharedRelease(SharedPointer* p)
{
    if (p != 0) {
        SharedPointer::SharedRef* r = &p->base2;
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

class IStream {
public:
    virtual ~IStream() {}
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

class MemoryStream : public IStream {
public:
    MemoryStream(void* pData, size_type nSize, unsigned char copy, int a, void* alloc, int unused);
    ~MemoryStream();

    bool SetData(void* pData, size_type nSize, unsigned char copy, unsigned char freeData, void* alloc);
    bool Clear();
    bool Grow(size_type size);
    bool WriteBuffer(const void* pData, size_type nSize);
    int  ReadBuffer(void* pData, size_type nSize);
    bool SetSizeEx(size_type size);
    virtual bool SetSize(size_type size);
    virtual bool SetPosition(int distance, int type);
    virtual int  Write(const void* pData, size_t nSize);

    SharedPointer* mpSharedPointer;  // +04
    int            mnRefCount;       // +08
    size_type      mnSize;           // +0c
    size_type      mnCapacity;       // +10
    size_type      mnPosition;       // +14
    bool           mbResizeEnabled;  // +18
    bool           mbLocked;         // +19
    float          mfResizeFactor;   // +1c
    int            mnResizeIncrement;// +20
};

class GraphicsFactoryAsyncRequest {
public:
    GraphicsFactoryAsyncRequest();
    GraphicsFactoryAsyncRequest(void* pData, void* nSize, int unused);

    float GetProperty(int index);
    void  SetProperty(int index, float value);
    bool  Attach(void* pData, size_type nSize);

    void*          mpVtbl;           // +00
    SharedPointer* mpData;           // +04
    int            mnField08;        // +08
    size_type      mnSize;           // +0c
    size_type      mnCapacity;       // +10
    size_type      mnPosition;       // +14
    bool           mbFlag18;         // +18
    bool           mbFlag19;         // +19
    float          mfFactor;         // +1c
    int            mnIncrement;      // +20
};

} } // EA::IO

// =============================================================================
// App::memorystream
// =============================================================================
class memorystream {
public:
    bool  WriteBuffer(const void* pData, size_type nSize);
    memorystream* Init(char* pData, size_type nSize);
    void* mpVtbl;         // +00
    char* mpData;         // +04
    int   mnField08;      // +08
    size_type mnSize;     // +0c
    size_type mnCapacity; // +10
    size_type mnPosition; // +14
};

extern void* g_vtbl_memorystream;

// @ 0x0093b9e0
bool __thiscall memorystream::WriteBuffer(const void* pData, size_type nSize)
{
    if (nSize > 0) {
        size_type pos = mnPosition;
        size_type end = pos + nSize;
        size_type take = nSize;
        if (end > mnCapacity) {
            take = mnSize - pos;
        } else if (mnSize < end) {
            mnSize = end;
        }
        MemCpyThunk(mpData + pos, pData, take);
        mnPosition += take;
        return take == nSize;
    }
    return true;
}

// @ 0x0093ba40
memorystream* memorystream::Init(char* pData, size_type nSize)
{
    memorystream* self = this;
    self->mpData = pData;
    self->mpVtbl = (void*)&g_vtbl_memorystream;
    self->mnField08 = 0;
    self->mnSize = nSize;
    self->mnCapacity = nSize;
    self->mnPosition = 0;
    return self;
}

// @ 0x0093ba90
int __fastcall FUN_0093ba90(char* self)
{
    return (*(char*)(self + 0x19) == 0) * 2 + 1;
}

// @ 0x0093bab0
float __thiscall EA::IO::GraphicsFactoryAsyncRequest::GetProperty(int index)
{
    switch (index) {
    case 1: return mbFlag18 ? 1.0f : 0.0f;
    case 2: return mfFactor;
    case 3: return (float)mnIncrement;
    case 4: return mbFlag19 ? 1.0f : 0.0f;
    default: return 0.0f;
    }
}

// @ 0x0093bb40
void __thiscall EA::IO::GraphicsFactoryAsyncRequest::SetProperty(int index, float value)
{
    switch (index) {
    case 1:
        mbFlag18 = (value != 0.0f);
        return;
    case 2:
        if (value < 1.0f) value = 1.0f;
        mfFactor = value;
        return;
    case 3:
        if (value < 0.0f) value = 0.0f;
        mnIncrement = (int)value;
        return;
    case 4:
        mbFlag19 = (value != 0.0f);
        return;
    default:
        return;
    }
}

// @ 0x0093bbf0
int __thiscall EA::IO::MemoryStream::ReadBuffer(void* pData, size_type nSize)
{
    if (nSize != 0) {
        size_type avail = mnSize - mnPosition;
        if (avail != 0) {
            if (avail < nSize)
                nSize = avail;
            MemCpyThunk(pData, (char*)mpSharedPointer->field_10 + mnPosition, nSize);
            mnPosition += nSize;
            return nSize;
        }
    }
    return 0;
}

struct ICoreAllocator {
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
extern const float g_1_5f;     // 0x01485548

namespace EA { namespace IO {

// @ 0x0093bc40
SharedPointer::SharedPointer(void* pData, unsigned char freeData, void* alloc)
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

} } // EA::IO

// @ 0x0093bca0
EA::IO::SharedPointer* EA::IO::SharedPointer::Init(void* pData, unsigned nSize)
{
    vtable = (void*)&g_vtbl_bg6;
    base2.vtable = (void*)&g_vtbl_hkref;
    _InterlockedExchange(&base2.mnRefCount, 0);
    vtable = (void*)&g_vtbl_bg;
    base2.vtable = (void*)&g_vtbl_bg2;
    mpAllocator = DefaultAllocator();
    field_10 = (long)((ICoreAllocator*)mpAllocator)->Alloc(pData, nSize, 0);
    field_14 = 1;
    return this;
}

// @ 0x0093bcf0
EA::IO::SharedPointer* EA::IO::SharedPointer::InitWithAlloc(void* pData, void* alloc, unsigned nSize)
{
    vtable = (void*)&g_vtbl_bg6;
    base2.vtable = (void*)&g_vtbl_hkref;
    _InterlockedExchange(&base2.mnRefCount, 0);
    vtable = (void*)&g_vtbl_bg;
    base2.vtable = (void*)&g_vtbl_bg2;
    if (alloc == 0)
        alloc = DefaultAllocator();
    mpAllocator = alloc;
    field_10 = (long)((ICoreAllocator*)alloc)->Alloc(pData, nSize, 0);
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
void* EA::IO::SharedPointer::Destroy(unsigned char flags)
{
    vtable = (void*)&g_vtbl_bg;
    base2.vtable = (void*)&g_vtbl_bg2;
    if (field_14 != 0)
        ((ICoreAllocator*)mpAllocator)->Free((void*)field_10, 0);
    base2.vtable = (void*)&g_vtbl_hkref;
    vtable = (void*)&g_vtbl_bg6;
    if (flags & 1)
        EASTL_deallocate(this);
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
bool __thiscall EA::IO::MemoryStream::SetData(void* pData, size_type nSize, unsigned char copy, unsigned char freeData, void* alloc)
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
            SharedPointer* sp = (SharedPointer*)AllocNamed(0x18, alloc, 0);
            if (sp != 0)
                sp = new ((void*)sp) SharedPointer(data, freeData, alloc);
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
    if (mpData != (EA::IO::SharedPointer*)pData) {
        if (pData != 0)
            _InterlockedIncrement(&((EA::IO::SharedPointer*)pData)->base2.mnRefCount);
        EA::IO::SharedRelease(mpData);
        mpData = (EA::IO::SharedPointer*)pData;
    }
    EA::IO::SharedPointer* p = mpData;
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
bool __thiscall EA::IO::MemoryStream::Grow(size_type nSize)
{
    void* alloc;
    if (mpSharedPointer != 0 && mpSharedPointer->mpAllocator != 0)
        alloc = mpSharedPointer->mpAllocator;
    else
        alloc = DefaultAllocator();
    SharedPointer* sp = 0;
    if (nSize != 0) {
        sp = (SharedPointer*)AllocNamed(0x18, alloc, 0);
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
bool __thiscall EA::IO::MemoryStream::SetPosition(int distance, int type)
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
bool __thiscall EA::IO::MemoryStream::SetSizeEx(size_type size)
{
    if (size > mnCapacity)
        return Grow(size);
    return false;
}

// @ 0x0093c150
bool __thiscall EA::IO::MemoryStream::WriteBuffer(const void* pData, size_type nSize)
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
    EA::IO::SharedPointer* p = (EA::IO::SharedPointer*)((void**)self)[1];
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
EA::IO::MemoryStream::MemoryStream(void* pData, size_type nSize, unsigned char copy, int a, void* alloc, int unused)
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

// @ 0x0093c320
bool __thiscall EA::IO::MemoryStream::Clear()
{
    SharedRelease(mpSharedPointer);
    mpSharedPointer = 0;
    mnCapacity = 0;
    mnSize = 0;
    mnPosition = 0;
    return true;
}

// @ 0x0093c370
bool __thiscall EA::IO::MemoryStream::SetSize(size_type size)
{
    if (mbLocked)
        return false;
    bool result = true;
    if (size != mnSize) {
        if (!mbResizeEnabled) {
            result = false;
        } else if (size < mnSize) {
            mnSize = size;
            if (size < mnPosition) {
                mnPosition = size;
                return result;
            }
        } else {
            bool ok = Grow(size);
            result = false;
            if (ok) {
                mnSize = size;
                return ok;
            }
        }
    }
    return result;
}

// @ 0x0093c3f0
int __fastcall FUN_0093c3f0(void** self)
{
    if ((int)(long)self[1] > 1) {
        int n = (int)(long)self[1] - 1;
        self[1] = (void*)(long)n;
        return n;
    }
    typedef void (__thiscall *Fn)(void*, int);
    (*(Fn*)self[0])(self, 1);
    return 0;
}

// @ 0x0093c420
int __stdcall FUN_0093c420(int a, int b) { return b; }

// @ 0x0093c430
extern void* g_vtbl_c430;
void* __fastcall FUN_0093c430(void** self)
{
    *self = (void*)&g_vtbl_c430;
    self[1] = 0;
    return self;
}

// =============================================================================
// EA::Text
// =============================================================================
namespace EA {

struct EAString {
    void* mpBegin;   // +0
    void* mpEnd;     // +4
    void* mpCap;     // +8
    void RangeInitialize(unsigned n);   // 0x00475ab0
    void AllocateSelf(unsigned n);      // 0x00429760
};

// @ 0x0093c440
EAString* ConvertToString8Impl(EAString* out, const wchar_t* src, unsigned count)
{
    if (count == 0xffffffff)
        count = wcslen(src);
    char buf[512];
    int len = 0x200;
    unsigned n = (unsigned)EA::Text::ConvertEncoding(src, count, 0x10, buf, &len, 8);
    if (n >= count) {
        char* bufEnd = buf + len;
        out->mpBegin = 0; out->mpEnd = 0; out->mpCap = 0;
        out->RangeInitialize((unsigned)(bufEnd - buf) + 1);
        char* data = (char*)out->mpBegin;
        MemCpyThunk(data, buf, (unsigned)(bufEnd - buf));
        out->mpEnd = data + (bufEnd - buf);
        *(char*)out->mpEnd = 0;
        return out;
    }
    len = count * 4;
    char* tmp = new char[len];
    EA::Text::ConvertEncoding(src, count, 0x10, tmp, &len, 8);
    char* tmpEnd = tmp + len;
    out->mpBegin = 0; out->mpEnd = 0; out->mpCap = 0;
    out->RangeInitialize((unsigned)(tmpEnd - tmp) + 1);
    char* data = (char*)out->mpBegin;
    MemCpyThunk(data, tmp, (unsigned)(tmpEnd - tmp));
    out->mpEnd = data + (tmpEnd - tmp);
    *(char*)out->mpEnd = 0;
    EASTL_deallocate(tmp);
    return out;
}

// @ 0x0093c570
void* ConvertToString8(void* out, const int* range)
{
    ConvertToString8Impl((EAString*)out, (const wchar_t*)range[0], (unsigned)((range[1] - range[0]) >> 1));
    return out;
}

static __forceinline void AssignW(EAString* o, const wchar_t* pBegin, const wchar_t* pEnd)
{
    o->mpBegin = 0; o->mpEnd = 0; o->mpCap = 0;
    o->AllocateSelf((unsigned)(pEnd - pBegin) + 1);
    wchar_t* data = (wchar_t*)o->mpBegin;
    MemCpyThunk(data, pBegin, (unsigned)(pEnd - pBegin) * 2);
    char* end = (char*)(data + (pEnd - pBegin));
    o->mpEnd = end;
    *(wchar_t*)end = 0;
}

// @ 0x0093c5a0
EAString* ConvertToString16Impl(EAString* out, const char* src, unsigned count)
{
    if (count == 0xffffffff)
        count = strlen(src);
    wchar_t buf[512];
    int len = 0x200;
    unsigned n = (unsigned)EA::Text::ConvertEncoding(src, count, 8, buf, &len, 0x10);
    if (n >= count) {
        AssignW(out, buf, buf + len);
        return out;
    }
    len = count;
    wchar_t* tmp = new wchar_t[count];
    EA::Text::ConvertEncoding(src, count, 8, tmp, &len, 0x10);
    AssignW(out, tmp, tmp + len);
    EASTL_deallocate(tmp);
    return out;
}

// @ 0x0093c6d0
void* ConvertToString16(void* out, const int* range)
{
    ConvertToString16Impl((EAString*)out, (const char*)range[0], (unsigned)(range[1] - range[0]));
    return out;
}

// @ 0x0093c6f0
void FUN_0093c6f0(const char* s)
{
    if (s != 0)
        fputs(s, (char*)__iob_func() + 0x20);
}

namespace Text {

// @ 0x0093c710
int Strlen32(const int* p)
{
    int n = -1;
    int v;
    do {
        v = *p;
        n++;
        p++;
    } while (v != 0);
    return n;
}

// @ 0x0093c730
int DetectEncoding(const unsigned char* p, unsigned count)
{
    int result = 8;
    if (count > 1) {
        if (count >= 2) {
            if (p[0] == 0xfe && p[1] == 0xff)
                return 0x4b1;
            if (p[0] == 0xff && p[1] == 0xfe)
                return 0x4b0;
            if (count >= 3 && p[0] == 0xef && p[1] == 0xbb && p[2] == 0xbf)
                return 8;
        }
        unsigned zeroOdd = 0, zeroTotal = 0, zeroEven = 0, ascii = 0, mb = 0;
        for (unsigned i = 0; i < count; ++i) {
            unsigned char c = p[i];
            if (c == 0) {
                zeroTotal++;
                if (i & 1) zeroOdd++; else zeroEven++;
            } else if (c <= 0x7f) {
                ascii++;
            } else if (c >= 0xc2) {
                if (c < 0xf0)
                    mb++;
            }
        }
        if (ascii == count)
            return 8;
        if (zeroTotal > (count >> 2)) {
            if ((zeroEven > (count >> 3)) && (zeroOdd > (count >> 3)))
                result = (p[0] == 0) + 0x4b2;
            else
                result = (zeroOdd < zeroEven) + 0x4b0;
        } else if (mb < (count >> 2)) {
            result = 0x4b0;
        }
    }
    return result;
}

// @ 0x0093c850
int ConvertEncoding_via_UTF16(const void* src, int srcLen, int srcEnc, void* dst, int* dstLen, int dstEnc)
{
    unsigned len = (unsigned)srcLen * 2 + 4;
    unsigned char stackBuf[0x200];
    unsigned char* buf;
    unsigned char* heap;
    if (len <= 0x200) {
        heap = 0;
        buf = stackBuf;
    } else {
        heap = (unsigned char*)EASTL_allocate(len, "EATextEncoding/LargeStringBuffer/char[]", 0, 0, 0, 0);
        buf = heap;
    }
    int n = EA::Text::ConvertEncoding(src, srcLen, srcEnc, buf, (int*)&len, 0x10);
    if (n == srcLen) {
        int r = EA::Text::ConvertEncoding(buf, len, 0x10, dst, dstLen, dstEnc);
        if ((unsigned)r == len) {
            EASTL_deallocate(heap);
            return srcLen;
        }
    }
    EASTL_deallocate(heap);
    *dstLen = 0;
    return 0;
}

// @ 0x0093c920
int GetCharacterSize(int encoding)
{
    if (encoding < 0x21) {
        if (encoding == 0x20)
            return 4;
        if (encoding == 0x10)
            return 2;
    } else if (encoding > 0x4af && encoding < 0x4b2) {
        return 2;
    }
    return 1;
}

} } // EA::Text
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
