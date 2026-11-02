// src/game/UTFSpore_Win32/EAStreamBuffer.cpp -- migrated from slice(s) s0093a9d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAStreamBuffer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);   // 0x011e0744 (memcpy thunk)
#include <intrin.h>

// ---- items of slice s0093a9d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
typedef unsigned int size_type;
extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);   // 0x011e0744 (memcpy thunk)
namespace EA {
namespace IO {
struct CoreAllocator;
}
}
namespace EA {
namespace IO {
extern CoreAllocator* gpCoreAllocator;                                // 0x016c8b44
}
}
namespace EA {
namespace IO {
struct CoreAllocator {
    void* Alloc(size_type size, int a, int b, int c, int d, int e);   // 0x009289f0 (equiv t2)
    void* Realloc(void* p, size_type size);
    void  Free(void* p);
};
}
}
namespace EA {
namespace IO {
class IStream_s0093_a9d0 {
public:
    virtual             ~IStream_s0093_a9d0() {}                 // +00 dtor
    virtual int         AddRef();                    // +04
    virtual int         Release();                   // +08
    virtual uint32      GetType() const;             // +0c
    virtual int         GetAccessFlags() const;      // +10
    virtual int         GetState() const;            // +14
    virtual bool        Close();                     // +18
    virtual size_type   GetSize() const;             // +1c
    virtual bool        SetSize(size_type size);      // +20
    virtual int         GetPosition(int type) const; // +24
    virtual bool        SetPosition(int distance, int type); // +28
    virtual int         GetAvailable() const;        // +2c
    virtual int         Read(void* pData, size_t nSize);     // +30
    virtual bool        Flush();                     // +34
    virtual bool        Write(const void* pData, size_t nSize); // +38
};
}
}
namespace EA {
namespace IO {
class StreamBuffer : public IStream_s0093_a9d0 {
public:
    StreamBuffer(size_type nReadBufferSize = -2, size_type nWriteBufferSize = -2, IStream_s0093_a9d0* pStream = 0);
    ~StreamBuffer();

    IStream_s0093_a9d0* GetStream() const { return mpStream; }
    bool SetStream(IStream_s0093_a9d0* pStream);
    void GetBufferSizes(size_type& read, size_type& write) const { read = mnReadBufferSize; write = mnWriteBufferSize; }
    bool SetBufferSizes(size_type nReadBufferSize, size_type nWriteBufferSize);

    virtual int       AddRef();
    virtual int       Release();
    virtual uint32    GetType() const;
    virtual int       GetAccessFlags() const;
    virtual int       GetState() const;
    virtual bool      Close();
    virtual size_type GetSize() const;
    virtual bool      SetSize(size_type size);
    virtual int       GetPosition(int type) const;
    virtual bool      SetPosition(int distance, int type);
    virtual int       GetAvailable() const;
    virtual int       Read(void* pData, size_t nSize);
    virtual bool      Flush();
    virtual bool      Write(const void* pData, size_t nSize);

    bool FillWriteBuffer(const char* pData, size_type nSize);
    __declspec(noinline) bool FlushWriteBuffer();

    IStream_s0093_a9d0*  mpStream;                   // +04
    int       mnRefCount;                 // +08
    size_type mnPositionExternal;         // +0c
    size_type mnPositionInternal;         // +10
    char*     mpReadBuffer;               // +14
    size_type mnReadBufferSize;           // +18
    size_type mnReadBufferStartPosition;  // +1c
    size_type mnReadBufferUsed;           // +20
    char*     mpWriteBuffer;              // +24
    size_type mnWriteBufferSize;          // +28
    size_type mnWriteBufferStartPosition; // +2c
    size_type mnWriteBufferUsed;          // +30
};
}
}
// ---- items of slice s0093a9d0 end

// @ 0x0093ae40
namespace EA { namespace IO {
int StreamBuffer::GetAccessFlags() const
{
    if (mpStream != 0)
        return mpStream->GetAccessFlags();
    return 0;
}
}}  // namespace EA::IO

// @ 0x0093ae60
namespace EA { namespace IO {
int StreamBuffer::GetState() const
{
    if (mpStream != 0)
        return mpStream->GetState();
    return 0;
}
}}  // namespace EA::IO

// @ 0x0093ae80
namespace EA { namespace IO {
size_type StreamBuffer::GetSize() const
{
    if (mpStream != 0) {
        size_type size = mpStream->GetSize();
        if (size == (size_type)-1)
            return size;
        if (mnWriteBufferUsed != 0 && size < mnPositionExternal)
            return mnPositionExternal;
        return size;
    }
    return (size_type)-1;
}
}}  // namespace EA::IO

// @ 0x0093aeb0
namespace EA { namespace IO {
int StreamBuffer::GetPosition(int type) const
{
    if (mpStream != 0) {
        switch (type) {
        case 0: return mnPositionExternal;
        case 2: return mnPositionExternal - GetSize();
        default: return 0;
        }
    }
    return -1;
}
}}  // namespace EA::IO

// @ 0x0093aef0
namespace EA { namespace IO {
int StreamBuffer::GetAvailable() const
{
    return GetSize() - mnPositionExternal;
}
}}  // namespace EA::IO

// @ 0x0093af00
namespace EA { namespace IO {
bool StreamBuffer::FlushWriteBuffer()
{
    if (mnWriteBufferUsed != 0) {
        if (mpStream->Write(mpWriteBuffer, mnWriteBufferUsed) == 0) {
            size_type pos = mpStream->GetPosition(0);
            mnPositionInternal = pos;
            mnWriteBufferStartPosition = pos;
            mnWriteBufferUsed = 0;
            return false;
        }
        mnPositionInternal += mnWriteBufferUsed;
        mnWriteBufferStartPosition = mnPositionInternal;
        mnWriteBufferUsed = 0;
    }
    return true;
}
}}  // namespace EA::IO

// @ 0x0093af60
namespace EA { namespace IO {
bool StreamBuffer::SetBufferSizes(size_type readSize, size_type writeSize)
{
    if (readSize == -1)
        readSize = 2000;
    readSize &= 0xfffffffe;
    if (readSize - 1 < 3)
        readSize = 4;
    else if (readSize > 16000000)
        readSize = 16000000;
    if (readSize < mnReadBufferSize) {
        mnReadBufferStartPosition = 0;
        mnReadBufferUsed = 0;
    }
    char* oldRead = mpReadBuffer;
    char* newRead = oldRead == 0 ? (char*)gpCoreAllocator->Alloc(readSize, 0, 0, 0, 0, 0)
                                 : (char*)gpCoreAllocator->Realloc(oldRead, readSize);
    mpReadBuffer = newRead;
    if (newRead == 0)
        mpReadBuffer = oldRead;
    else
        mnReadBufferSize = readSize;

    if (writeSize == -1)
        writeSize = 2000;
    writeSize &= 0xfffffffe;
    if (writeSize - 1 < 3)
        writeSize = 4;
    else if (writeSize > 16000000)
        writeSize = 16000000;
    if (writeSize < mnWriteBufferSize)
        FlushWriteBuffer();
    char* oldWrite = mpWriteBuffer;
    char* newWrite = oldWrite == 0 ? (char*)gpCoreAllocator->Alloc(writeSize, 0, 0, 0, 0, 0)
                                   : (char*)gpCoreAllocator->Realloc(oldWrite, writeSize);
    mpWriteBuffer = newWrite;
    if (newWrite != 0)
        mnWriteBufferSize = writeSize;
    else
        mpWriteBuffer = oldWrite;
    return true;
}
}}  // namespace EA::IO

// @ 0x0093b050
namespace EA { namespace IO {
bool StreamBuffer::SetSize(size_type size)
{
    bool ok = false;
    if (mpStream != 0) {
        mnReadBufferStartPosition = 0;
        mnReadBufferUsed = 0;
        FlushWriteBuffer();
        ok = mpStream->SetSize(size);
        size_type pos = mpStream->GetPosition(0);
        mnPositionExternal = pos;
        mnPositionInternal = pos;
    }
    return ok;
}
}}  // namespace EA::IO

// @ 0x0093b0a0
namespace EA { namespace IO {
bool StreamBuffer::SetPosition(int distance, int type)
{
    bool ok = false;
    if (mpStream != 0) {
        int base = distance;
        int newPos;
        if (type == 1)
            newPos = base + mnPositionExternal;
        else if (type == 2)
            newPos = base + GetSize();
        else
            newPos = base;

        if (mnReadBufferUsed == 0 || newPos < 0) {
            if (newPos != (size_type)mnPositionExternal) {
                FlushWriteBuffer();
                if (mpStream->SetPosition(newPos, 0)) {
                    mnPositionInternal = newPos;
                    mnPositionExternal = newPos;
                    ok = true;
                } else {
                    newPos = mpStream->GetPosition(0);
                    mnPositionInternal = newPos;
                    mnPositionExternal = newPos;
                }
            } else {
                ok = true;
            }
        } else {
            mnPositionExternal = newPos;
            ok = true;
        }
    }
    return ok;
}
}}  // namespace EA::IO

// @ 0x0093b140
namespace EA { namespace IO {
int StreamBuffer::Read(void* pData, size_t nSize)
{
    if (mpStream == 0)
        return -1;
    if (nSize == 0)
        return 0;
    if (mnWriteBufferUsed != 0)
        FlushWriteBuffer();
    if (mnReadBufferSize == 0) {
        int n = mpStream->Read(pData, nSize);
        if (n == -1) {
            size_type pos = mpStream->GetPosition(0);
            mnPositionInternal = pos;
            mnPositionExternal = pos;
            return -1;
        }
        mnPositionInternal += nSize;
        mnPositionExternal = mnPositionInternal;
        return n;
    }

    char* pDst = (char*)pData;
    size_t remaining = nSize;
    bool ok = true;
    if (mnPositionExternal >= mnReadBufferStartPosition &&
        mnPositionExternal < mnReadBufferStartPosition + mnReadBufferUsed) {
        size_type avail = mnReadBufferUsed - (mnPositionExternal - mnReadBufferStartPosition);
        size_type take = (size_type)nSize;
        if (avail < take)
            take = avail;
        MemCpyThunk(pDst, mpReadBuffer + (mnPositionExternal - mnReadBufferStartPosition), take);
        pDst += take;
        remaining -= take;
        mnPositionExternal += take;
    }
    while (remaining != 0) {
        mnReadBufferStartPosition = 0;
        mnReadBufferUsed = 0;
        if (mnPositionInternal != mnPositionExternal)
            ok = mpStream->SetPosition(mnPositionExternal, 0) != 0;
        if (!ok)
            break;
        mnPositionInternal = mnPositionExternal;
        size_type read;
        if ((size_type)(mnReadBufferSize * 2) < (size_type)remaining) {
            read = mpStream->Read(pDst, remaining);
            if (read != -1) {
                mnPositionInternal += read;
                mnPositionExternal += read;
                remaining -= read;
            }
            goto done;
        }
        read = mpStream->Read(mpReadBuffer, mnReadBufferSize);
        if (read == -1) {
            mnReadBufferStartPosition = 0;
            mnReadBufferUsed = 0;
            ok = false;
        } else {
            mnReadBufferStartPosition = mnPositionInternal;
            mnReadBufferUsed = read;
            mnPositionInternal += read;
            ok = true;
        }
        if (!ok || mnReadBufferUsed == 0)
            break;
        size_type take = (size_type)remaining;
        if (mnReadBufferUsed < take)
            take = mnReadBufferUsed;
        MemCpyThunk(pDst, mpReadBuffer, take);
        mnPositionExternal += take;
        remaining -= take;
        pDst += take;
        if (remaining == 0)
            return (int)nSize;
    }
done:
    return (int)(nSize - remaining);
}
}}  // namespace EA::IO

// @ 0x0093b300
namespace EA { namespace IO {
bool StreamBuffer::Flush()
{
    if (mpStream != 0)
        return FlushWriteBuffer();
    return false;
}
}}  // namespace EA::IO

// @ 0x0093b310
namespace EA { namespace IO {
bool StreamBuffer::FillWriteBuffer(const char* pData, size_type nSize)
{
    bool bReturnValue = true;
    if (nSize > 0) {
        if (mnWriteBufferUsed == 0)
            mnWriteBufferStartPosition = mnPositionInternal;
        if ((mnWriteBufferUsed + nSize) <= mnWriteBufferSize) {
            MemCpyThunk(mpWriteBuffer + mnWriteBufferUsed, pData, (size_t)nSize);
            mnWriteBufferUsed += nSize;
        } else {
            while (nSize && bReturnValue) {
                const size_type nSizeToBuffer =
                    (mnWriteBufferSize - mnWriteBufferUsed < nSize)
                        ? (mnWriteBufferSize - mnWriteBufferUsed) : nSize;
                if (nSizeToBuffer) {
                    MemCpyThunk(mpWriteBuffer + mnWriteBufferUsed, pData, (size_t)nSizeToBuffer);
                    mnWriteBufferUsed += nSizeToBuffer;
                    pData += nSizeToBuffer;
                    nSize -= nSizeToBuffer;
                }
                if (mnWriteBufferUsed == mnWriteBufferSize)
                    bReturnValue = FlushWriteBuffer();
            }
        }
    }
    return bReturnValue;
}
}}  // namespace EA::IO

// @ 0x0093b3c0
namespace EA { namespace IO {
bool StreamBuffer::SetStream(IStream_s0093_a9d0* pStream)
{
    bool result = true;
    if (pStream != mpStream) {
        if (mpStream != 0) {
            FlushWriteBuffer();
            mnReadBufferStartPosition = 0;
            mnReadBufferUsed = 0;
            mnWriteBufferStartPosition = 0;
            mnWriteBufferUsed = 0;
            mnPositionExternal = 0;
            mnPositionInternal = 0;
        }
        if (pStream != 0) {
            pStream->AddRef();
            if (pStream->GetAccessFlags() == 0) {
                result = false;
            } else {
                size_type pos = pStream->GetPosition(0);
                mnPositionExternal = pos;
                mnPositionInternal = pos;
            }
        }
        if (mpStream != 0)
            mpStream->Release();
        mpStream = pStream;
        return result;
    }
    return true;
}
}}  // namespace EA::IO

// @ 0x0093b450
namespace EA { namespace IO {
bool StreamBuffer::Close()
{
    if (mpStream == 0)
        return false;
    FlushWriteBuffer();
    mnReadBufferStartPosition = 0;
    mnReadBufferUsed = 0;
    mnWriteBufferStartPosition = 0;
    mnWriteBufferUsed = 0;
    mnPositionExternal = 0;
    mnPositionInternal = 0;
    return mpStream->Close();
}
}}  // namespace EA::IO

// @ 0x0093b490
namespace EA { namespace IO {
bool StreamBuffer::Write(const void* pData, size_t nSize)
{
    if (mpStream == 0)
        return false;
    if (mnReadBufferUsed != 0) {
        mnReadBufferStartPosition = 0;
        mnReadBufferUsed = 0;
        if (mnPositionExternal != mnPositionInternal)
            mpStream->SetPosition(mnPositionExternal, 0);
    }
    if (mnWriteBufferSize != 0) {
        bool r = FillWriteBuffer((const char*)pData, nSize);
        mnPositionExternal += nSize;
        return r;
    }
    bool ok = mpStream->Write(pData, nSize);
    if (ok) {
        mnPositionInternal += nSize;
        mnPositionExternal = mnPositionInternal;
        return true;
    }
    size_type pos = mpStream->GetPosition(0);
    mnPositionInternal = pos;
    mnPositionExternal = pos;
    return false;
}
}}  // namespace EA::IO

// @ 0x0093b530
namespace EA { namespace IO {
StreamBuffer::StreamBuffer(size_type nReadBufferSize, size_type nWriteBufferSize, IStream_s0093_a9d0* pStream)
: mpStream(0), mnRefCount(0), mnPositionExternal(0), mnPositionInternal(0),
      mpReadBuffer(0), mnReadBufferSize(0), mnReadBufferStartPosition(0), mnReadBufferUsed(0),
      mpWriteBuffer(0), mnWriteBufferSize(0), mnWriteBufferStartPosition(0), mnWriteBufferUsed(0)
{
    if (nReadBufferSize != -2 && nWriteBufferSize != -2)
        SetBufferSizes(nReadBufferSize, nWriteBufferSize);
    if (pStream != 0)
        SetStream(pStream);
}
}}  // namespace EA::IO

// @ 0x0093b5a0
namespace EA { namespace IO {
StreamBuffer::~StreamBuffer()
{
    if (mpStream != 0) {
        FlushWriteBuffer();
        mnReadBufferStartPosition = 0;
        mnReadBufferUsed = 0;
        mnWriteBufferStartPosition = 0;
        mnWriteBufferUsed = 0;
        mnPositionExternal = 0;
        mnPositionInternal = 0;
        if (mpStream != 0)
            mpStream->Release();
        mpStream = 0;
    }
    if (mpReadBuffer != 0)
        gpCoreAllocator->Free(mpReadBuffer);
    if (mpWriteBuffer != 0)
        gpCoreAllocator->Free(mpWriteBuffer);
}
}}  // namespace EA::IO
