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

namespace EA { namespace Text {
int ConvertEncoding(const void* src, size_t srcCount, int srcEnc, void* dst, int* dstLen, int dstEnc); // 0x0093c950
int GetCharacterSize(int encoding);
}}

namespace EA { namespace IO {

struct SharedPointer {
    void* vtable;            // +0
    void* vtable2;           // +4
    long  mnRefCount;        // +8
    void* mpAllocator;       // +0c
    long  field_10;          // +10
    unsigned char field_14;  // +14
    SharedPointer(void* pData, void* alloc, unsigned char freeData);
};

inline void SharedRelease(SharedPointer* p)
{
    if (p != 0) {
        if (_InterlockedDecrement(&p->mnRefCount) == 0) {
            _InterlockedExchange(&p->mnRefCount, 1);
            if (p->vtable2 != 0) {
                typedef void (__thiscall *Fn)(void*, int);
                (*(Fn*)p->vtable2)(p->vtable2, 1);
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
    MemoryStream(void* pData, size_type nSize, unsigned char copy, int a, void* alloc);
    ~MemoryStream();

    bool SetData(void* pData, size_type nSize, unsigned char copy, void* a, void* b, void* alloc);
    bool Clear();
    bool Grow(size_type size);
    int  WriteBuffer(const void* pData, size_type nSize);
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
    GraphicsFactoryAsyncRequest(void* pData, void* nSize);

    float GetProperty(int index);
    void  SetProperty(int index, float value);
    int   Attach(void* pData, size_type nSize);

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
    int   WriteBuffer(const void* pData, size_type nSize);
    char* mpData;         // +04
    int   mnField08;      // +08
    size_type mnSize;     // +0c
    size_type mnCapacity; // +10
    size_type mnPosition; // +14
};

extern void* g_vtbl_memorystream;

// @ 0x0093b9e0
int __thiscall memorystream::WriteBuffer(const void* pData, size_type nSize)
{
    if (nSize == 0)
        return 1;
    size_type pos = mnPosition;
    size_type end = pos + nSize;
    size_type take = nSize;
    if (end > mnCapacity)
        take = mnSize - pos;
    else if (end > mnSize)
        mnSize = end;
    MemCpyThunk(mpData + pos, pData, take);
    mnPosition += take;
    return take == nSize;
}

// @ 0x0093ba40
memorystream* memorystream_Ctor(memorystream* self, char* pData, size_type nSize)
{
    self->mpData = pData;
    *(void**)self = (void*)&g_vtbl_memorystream;
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
        if (value != 0.0f) { mbFlag19 = 1; return; }
        mbFlag19 = 0;
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

namespace EA { namespace IO {

// @ 0x0093bc40
SharedPointer::SharedPointer(void* pData, void* alloc, unsigned char freeData)
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

} } // EA::IO

extern void* g_vtbl_bgloading;
extern void* g_vtbl_bgloading_a;
extern void* g_vtbl_bgloading_b;
extern void* g_vtbl_gfar;

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
    EA::IO::SharedPointer* p = (EA::IO::SharedPointer*)((void**)self)[1];
    if (p != 0)
        EA::IO::SharedRelease(p);
    *(void**)self = (void*)&g_vtbl_gfar;
}

// @ 0x0093be30
bool __thiscall EA::IO::MemoryStream::SetData(void* pData, size_type nSize, unsigned char copy, void* a, void* b, void* alloc)
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
            SharedPointer* sp = (SharedPointer*)AllocNamed(0x18, alloc, 0);
            if (sp != 0)
                sp = new ((void*)sp) SharedPointer(data, alloc, 0);
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
    if (mpData != (EA::IO::SharedPointer*)pData) {
        if (pData != 0)
            _InterlockedIncrement(&((EA::IO::SharedPointer*)pData)->mnRefCount);
        EA::IO::SharedRelease(mpData);
        mpData = (EA::IO::SharedPointer*)pData;
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
bool __thiscall EA::IO::MemoryStream::Grow(size_type nSize)
{
    void* alloc = (void*)&DefaultAllocator;
    if (mpSharedPointer != 0 && mpSharedPointer->mpAllocator != 0)
        alloc = mpSharedPointer->mpAllocator;
    SharedPointer* sp = 0;
    if (nSize != 0) {
        sp = (SharedPointer*)AllocNamed(0x18, alloc, 0);
        if (sp == 0)
            return false;
        sp = new ((void*)sp) SharedPointer((void*)nSize, alloc, 0);
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
int __thiscall EA::IO::MemoryStream::WriteBuffer(const void* pData, size_type nSize)
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
    EA::IO::SharedPointer* p = (EA::IO::SharedPointer*)((void**)self)[1];
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
EA::IO::MemoryStream::MemoryStream(void* pData, size_type nSize, unsigned char copy, int a, void* alloc)
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
int FUN_0093c420(int a, int b) { return b; }

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
};

// @ 0x0093c440
void ConvertToString8Impl(void* outp, const wchar_t* src, unsigned count)
{
    EAString* out = (EAString*)outp;
    if (count == 0xffffffff) {
        const wchar_t* p = src;
        while (*p) p++;
        count = (unsigned)(p - src);
    }
    char buf[512];
    int len = 0x200;
    unsigned n = (unsigned)EA::Text::ConvertEncoding(src, count, 0x10, buf, &len, 8);
    if (count > n) {
        // did not fit: redo with an exact-size buffer
        char* heap = (char*)EASTL_allocate(count * 4, 0, 0, 0, 0, 0);
        len = count * 4;
        EA::Text::ConvertEncoding(src, count, 0x10, heap, &len, 8);
        out->mpBegin = 0; out->mpEnd = 0; out->mpCap = 0;
        char* data = (char*)EASTL_allocate((size_t)len + 1, 0, 0, 0, 0, 0);
        MemCpyThunk(data, heap, len);
        data[len] = 0;
        out->mpBegin = data; out->mpEnd = data + len; out->mpCap = data + len + 1;
        EASTL_deallocate(heap);
        return;
    }
    out->mpBegin = 0; out->mpEnd = 0; out->mpCap = 0;
    char* data = (char*)EASTL_allocate((size_t)len + 1, 0, 0, 0, 0, 0);
    MemCpyThunk(data, buf, len);
    data[len] = 0;
    out->mpBegin = data; out->mpEnd = data + len; out->mpCap = data + len + 1;
}

// @ 0x0093c570
void* ConvertToString8(void* out, const int* range)
{
    ConvertToString8Impl(out, (const wchar_t*)range[0], (unsigned)((range[1] - range[0]) >> 1));
    return out;
}

// @ 0x0093c5a0
void ConvertToString16Impl(void* outp, const char* src, unsigned count)
{
    EAString* out = (EAString*)outp;
    if (count == 0xffffffff) {
        const char* p = src;
        while (*p) p++;
        count = (unsigned)(p - src);
    }
    wchar_t buf[512];
    int len = 0x200;
    unsigned n = (unsigned)EA::Text::ConvertEncoding(src, count, 8, buf, &len, 0x10);
    if (count <= n) {
        out->mpBegin = 0; out->mpEnd = 0; out->mpCap = 0;
        wchar_t* data = (wchar_t*)EASTL_allocate(((size_t)len + 1) * 2, 0, 0, 0, 0, 0);
        MemCpyThunk(data, buf, (size_t)len * 2);
        data[len] = 0;
        out->mpBegin = data; out->mpEnd = data + len; out->mpCap = data + len + 1;
        return;
    }
    wchar_t* heap = (wchar_t*)EASTL_allocate(((size_t)count * 2), 0, 0, 0, 0, 0);
    len = count * 2;
    EA::Text::ConvertEncoding(src, count, 8, heap, &len, 0x10);
    out->mpBegin = 0; out->mpEnd = 0; out->mpCap = 0;
    wchar_t* data = (wchar_t*)EASTL_allocate(((size_t)len + 1) * 2, 0, 0, 0, 0, 0);
    MemCpyThunk(data, heap, (size_t)len * 2);
    data[len] = 0;
    out->mpBegin = data; out->mpEnd = data + len; out->mpCap = data + len + 1;
    EASTL_deallocate(heap);
}

// @ 0x0093c6d0
void* ConvertToString16(void* out, const int* range)
{
    ConvertToString16Impl(out, (const char*)range[0], (unsigned)(range[1] - range[0]));
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
        if (p[0] == 0xfe && p[1] == 0xff)
            return 0x4b1;
        if (p[0] == 0xff && p[1] == 0xfe)
            return 0x4b0;
        if (count > 2 && p[0] == 0xef && p[1] == 0xbb && p[2] == 0xbf)
            return 8;
        unsigned zeroEven = 0, zeroOdd = 0, ascii = 0, lead = 0, cont = 0;
        for (unsigned i = 0; i < count; ++i) {
            unsigned char c = p[i];
            if (c == 0) {
                if ((i & 1) == 0) cont++; else lead++;
            } else if (c < 0x80) {
                ascii++;
            } else if (c > 0xc1 && c < 0xf0) {
                zeroEven++;
            }
        }
        if (ascii == count)
            return 8;
        if (count >> 2 < lead) {
            if ((count >> 3 < cont) && (count >> 3 < zeroEven))
                return (p[0] == 0) + 0x4b2;
            return (zeroEven < cont) + 0x4b0;
        }
        if (zeroEven < count >> 2)
            result = 0x4b0;
    }
    return result;
}

// @ 0x0093c850
int ConvertEncoding_via_UTF16(const void* src, int srcLen, int srcEnc, void* dst, int* dstLen, int dstEnc)
{
    unsigned bufSize = (unsigned)srcLen * 2 + 4;
    void* small = 0;
    void* buf;
    if (bufSize < 0x201) {
        static unsigned char stackBuf[0x400];
        buf = stackBuf;
    } else {
        buf = EASTL_allocate(bufSize, "EATextEncoding/LargeStringBuffer/char[]", 0, 0, 0, 0);
        small = buf;
    }
    unsigned local = bufSize;
    int n = EA::Text::ConvertEncoding(src, srcLen, srcEnc, buf, (int*)&local, 0x10);
    if (n == srcLen) {
        int r = EA::Text::ConvertEncoding(buf, local, 0x10, dst, dstLen, dstEnc);
        if ((unsigned)r == local) {
            EASTL_deallocate(small);
            return srcLen;
        }
    }
    EASTL_deallocate(small);
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
