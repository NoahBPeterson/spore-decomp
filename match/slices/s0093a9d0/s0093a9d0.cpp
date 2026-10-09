// Spore retail 0093a9d0..0093b9a0 -- EA::IO stream helpers, StreamBuffer, StreamChild,
// FixedMemoryStream.  Layouts from the Spore-ModAPI IO headers (community RE of the
// closer 2017 Steam build); field offsets confirmed against the retail disassembly.

#include "types.h"
#include <intrin.h>

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned int size_type;

extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);   // 0x011e0744 (memcpy thunk)

namespace EA {
namespace Text {
int ConvertEncoding(const wchar_t* src, size_t srcCount, int srcEnc,
                    char* dst, int* dstLen, int dstEnc);              // 0x0093c950
int ConvertEncoding(const char* src, size_t srcCount, int srcEnc,
                    char* dst, int* dstLen, int dstEnc);
}

namespace IO {

// ---- allocator used by the stream buffers -----------------------------------
struct CoreAllocator;
extern CoreAllocator* gpCoreAllocator;                                // 0x016c8b44
struct CoreAllocator {
    void* Alloc(size_type size, int a, int b, int c, int d, int e);
    void* Realloc(void* p, size_type size);
    void  Free(void* p);
};

// ---- IStream ----------------------------------------------------------------
class IStream {
public:
    virtual             ~IStream() {}                 // +00 dtor
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
    virtual int         Write(const void* pData, size_t nSize); // +38
};

// ---- StreamBuffer -----------------------------------------------------------
class StreamBuffer : public IStream {
public:
    StreamBuffer(size_type nReadBufferSize = -2, size_type nWriteBufferSize = -2, IStream* pStream = 0);
    ~StreamBuffer();

    IStream* GetStream() const { return mpStream; }
    bool SetStream(IStream* pStream);
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
    virtual int       Write(const void* pData, size_t nSize);

    bool FillWriteBuffer(const char* pData, size_type nSize);
    bool FlushWriteBuffer();

    IStream*  mpStream;                   // +04
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

// ---- StreamChild ------------------------------------------------------------
class StreamChild : public IStream {
public:
    StreamChild(IStream* pParent = 0, size_type nPosition = 0, size_type nSize = 0);
    ~StreamChild();

    bool Open(IStream* pStreamParent, size_type nPosition, size_type nSize);

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
    virtual int       Write(const void* pData, size_t nSize);

    int       mnRefCount;        // +04
    int       mnAccessFlags;     // +08
    IStream*  mpStreamParent;    // +0c
    size_type mnPositionParent;  // +10
    size_type mnPosition;        // +14
    size_type mnSize;            // +18
};

// ---- FixedMemoryStream ------------------------------------------------------
class FixedMemoryStream : public IStream {
public:
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
    virtual int       Write(const void* pData, size_t nSize);

    bool SetData(const void* pData, size_type nSize);

    void*     mpData;      // +04
    int       mnRefCount;  // +08
    size_type mnSize;      // +0c
    size_type mnCapacity;  // +10
    size_type mnPosition;  // +14
};

// ==== free helpers ===========================================================

// @ 0x0093a9d0
bool WriteUint16(IStream* pStream, const uint16_t* pData, uint32 count, int endian)
{
    if (endian != 1)
        pStream->GetAccessFlags();
    if (pStream->GetState() != 0)
        return false;
    if (endian == 1)
        return pStream->Write(pData, count * 2) != 0;
    bool ok = true;
    if (count != 0) {
        for (;;) {
            uint16_t v = *pData;
            pData++;
            count--;
            uint32 tmp = _byteswap_ushort(v);
            if (!pStream->Write(&tmp, 2)) {
                ok = false;
                break;
            }
            if (count == 0)
                return true;
        }
    }
    return ok;
}

// @ 0x0093aa70
bool WriteUint32(IStream* pStream, const uint32* pData, uint32 count, int endian)
{
    if (endian != 1)
        pStream->GetAccessFlags();
    if (pStream->GetState() != 0)
        return false;
    if (endian == 1)
        return pStream->Write(pData, count * 4) != 0;
    bool ok = true;
    if (count != 0) {
        for (;;) {
            uint32 v = *pData;
            pData++;
            count--;
            uint32 tmp = _byteswap_ulong(v);
            if (!pStream->Write(&tmp, 4)) {
                ok = false;
                break;
            }
            if (count == 0)
                return true;
        }
    }
    return ok;
}

// @ 0x0093ab10
bool WriteUint64(IStream* pStream, const uint64_t* pData, uint32 count, int endian)
{
    if (endian != 1)
        pStream->GetAccessFlags();
    if (pStream->GetState() != 0)
        return false;
    if (endian == 1)
        return pStream->Write(pData, count * 8) != 0;
    bool ok = true;
    if (count != 0) {
        for (;;) {
            uint64_t v = *pData;
            pData++;
            count--;
            uint64_t tmp = ((uint64_t)_byteswap_ulong((uint32)v) << 32) | _byteswap_ulong((uint32)(v >> 32));
            if (!pStream->Write(&tmp, 8)) {
                ok = false;
                break;
            }
            if (count == 0)
                return true;
        }
    }
    return ok;
}

bool ReadInt32(IStream* pStream, int* pOut, int count, int endian);  // 0x0093a780
bool ReadBytes(IStream* pStream, void* pOut, int count);             // 0x0093a6c0

// @ 0x0093abd0
bool WriteString(IStream* pStream, const char* pStr, int count, int mode)
{
    if (pStream->GetState() != 0)
        return false;
    if (count == -1) {
        count = 0;
        if (*pStr == 0)
            goto done;
        const char* p = pStr;
        do {
            p++;
            count++;
        } while (*p != 0);
    }
    if (count != 0 && !pStream->Write(pStr, count))
        return false;
done:
    if (mode == 1) {
        if (count != 0) {
            if (pStr[count - 1] == '\n')
                return true;
            if (pStr[count - 1] == '\r')
                return true;
        }
    } else if (mode == 3) {
        uint16 crlf = 0x0a0d;
        return pStream->Write(&crlf, 2) != 0;
    } else if (mode != 2) {
        return true;
    }
    char lf = 10;
    return pStream->Write(&lf, 1) != 0;
}

// @ 0x0093ac80
bool ReadBool(IStream* pStream, bool* pOut)
{
    if (pStream->GetState() != 0)
        return false;
    if (pStream->Read(pOut, 1) == 1) {
        *pOut = (*pOut != 0);
        return true;
    }
    return false;
}

// @ 0x0093acd0
int ReadString(IStream* pStream, char* pOut, int maxCount, int endian)
{
    if (endian != 1)
        pStream->GetAccessFlags();
    if (pStream->GetState() != 0)
        return 0;
    int len = 0;
    if (!EA::IO::ReadInt32(pStream, &len, 1, endian))
        return -1;
    if (pOut != 0) {
        if ((uint32)(maxCount - 1) < (uint32)len) {
            if (!ReadBytes(pStream, pOut, maxCount))
                return -1;
            pOut[maxCount - 1] = 0;
            pStream->SetPosition(pStream->GetPosition(0), 0);
        } else {
            if (!ReadBytes(pStream, pOut, len))
                return -1;
            pOut[len] = 0;
        }
    } else {
        pStream->SetPosition(pStream->GetPosition(0) + (len + 3u & 0xfffffffc), 0);
    }
    return (int)len;
}

// @ 0x0093adb0
bool WriteCString(IStream* pStream, const char* pStr, int count, int endian)
{
    if (endian != 1)
        pStream->GetAccessFlags();
    if (pStream->GetState() != 0)
        return false;
    if (count == -1) {
        count = 0;
        while (pStr[count] != 0)
            count++;
    }
    uint32 len = count;
    bool ok = WriteUint32(pStream, &len, 1, endian);
    if (ok && count != 0)
        ok = pStream->Write(pStr, count) != 0;
    return ok;
}

} // namespace IO
} // namespace EA

// =============================================================================
// StreamBuffer
// =============================================================================
namespace EA {
namespace IO {

// @ 0x0093ae40
int StreamBuffer::GetAccessFlags() const
{
    if (mpStream != 0)
        return mpStream->GetAccessFlags();
    return 0;
}

// @ 0x0093ae60
int StreamBuffer::GetState() const
{
    if (mpStream != 0)
        return mpStream->GetState();
    return 0;
}

// @ 0x0093ae80
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

// @ 0x0093aeb0
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

// @ 0x0093aef0
int StreamBuffer::GetAvailable() const
{
    return GetSize() - mnPositionExternal;
}

// @ 0x0093af00
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

// @ 0x0093af60
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

// @ 0x0093b050
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

// @ 0x0093b0a0
bool StreamBuffer::SetPosition(int distance, int type)
{
    if (mpStream == 0)
        return false;
    int newPos;
    if (type == 1)
        newPos = distance + mnPositionExternal;
    else if (type == 2) {
        newPos = distance + GetPosition(2);
    } else
        newPos = distance;

    if (mnReadBufferUsed == 0 || newPos < 0) {
        if (newPos != (size_type)mnPositionExternal) {
            FlushWriteBuffer();
            if (!mpStream->SetPosition(newPos, 0)) {
                size_type pos = mpStream->GetPosition(0);
                mnPositionInternal = pos;
                mnPositionExternal = pos;
                return false;
            }
            mnPositionInternal = newPos;
            mnPositionExternal = newPos;
        }
    } else {
        mnPositionExternal = newPos;
    }
    return true;
}

// @ 0x0093b140
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

// @ 0x0093b300
bool StreamBuffer::Flush()
{
    if (mpStream != 0)
        return FlushWriteBuffer();
    return false;
}

// @ 0x0093b310
bool StreamBuffer::FillWriteBuffer(const char* pData, size_type nSize)
{
    bool result = true;
    if (nSize != 0) {
        size_type used = mnWriteBufferUsed;
        if (used == 0)
            mnWriteBufferStartPosition = mnPositionInternal;
        if ((size_type)(used + nSize) <= mnWriteBufferSize) {
            MemCpyThunk(mpWriteBuffer + used, pData, nSize);
            mnWriteBufferUsed += nSize;
        } else {
            while (result) {
                size_type take = mnWriteBufferSize - mnWriteBufferUsed;
                if ((size_type)nSize < take)
                    take = nSize;
                if (take != 0) {
                    MemCpyThunk(mpWriteBuffer + mnWriteBufferUsed, pData, take);
                    mnWriteBufferUsed += take;
                    pData += take;
                    nSize -= take;
                }
                if (mnWriteBufferUsed == mnWriteBufferSize)
                    result = FlushWriteBuffer();
                if (nSize == 0)
                    break;
            }
        }
    }
    return result;
}

// @ 0x0093b3c0
bool StreamBuffer::SetStream(IStream* pStream)
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

// @ 0x0093b450
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

// @ 0x0093b490
int StreamBuffer::Write(const void* pData, size_t nSize)
{
    if (mpStream == 0)
        return 0;
    if (mnReadBufferUsed != 0) {
        mnReadBufferStartPosition = 0;
        mnReadBufferUsed = 0;
        if (mnPositionExternal != mnPositionInternal)
            mpStream->SetPosition(mnPositionExternal, 0);
    }
    if (mnWriteBufferSize != 0) {
        int r = FillWriteBuffer((const char*)pData, nSize) ? 1 : 0;
        mnPositionExternal += nSize;
        return r;
    }
    bool ok = mpStream->Write(pData, nSize) != 0;
    if (ok) {
        mnPositionInternal += nSize;
        mnPositionExternal = mnPositionInternal;
        return 1;
    }
    size_type pos = mpStream->GetPosition(0);
    mnPositionInternal = pos;
    mnPositionExternal = pos;
    return 0;
}

// @ 0x0093b530
StreamBuffer::StreamBuffer(size_type nReadBufferSize, size_type nWriteBufferSize, IStream* pStream)
    : mpStream(0), mnRefCount(0), mnPositionExternal(0), mnPositionInternal(0),
      mpReadBuffer(0), mnReadBufferSize(0), mnReadBufferStartPosition(0), mnReadBufferUsed(0),
      mpWriteBuffer(0), mnWriteBufferSize(0), mnWriteBufferStartPosition(0), mnWriteBufferUsed(0)
{
    if (nReadBufferSize != -2 && nWriteBufferSize != -2)
        SetBufferSizes(nReadBufferSize, nWriteBufferSize);
    if (pStream != 0)
        SetStream(pStream);
}

// @ 0x0093b5a0
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

// =============================================================================
// StreamChild
// =============================================================================

// @ 0x0093b630
bool StreamChild::Open(IStream* pParent, size_type nPosition, size_type nSize)
{
    if (mnAccessFlags == 0 && pParent != 0) {
        int flags = pParent->GetAccessFlags();
        if ((flags & 1) != 0) {
            size_type size = pParent->GetSize();
            size_type end = nPosition + nSize;
            if (nPosition < size && end <= size && end >= nPosition) {
                mpStreamParent = pParent;
                mnAccessFlags = 1;
                mnPositionParent = nPosition;
                mnPosition = 0;
                mnSize = nSize;
                return true;
            }
        }
    }
    return false;
}

// @ 0x0093b6a0
bool StreamChild::Close()
{
    if (mnAccessFlags != 0) {
        mnAccessFlags = 0;
        mpStreamParent = 0;
        mnPositionParent = 0;
        mnPosition = 0;
        mnSize = 0;
    }
    return true;
}

// @ 0x0093b6d0
int StreamChild::GetState() const
{
    if (mpStreamParent != 0)
        return mpStreamParent->GetState();
    return 0;
}

// @ 0x0093b6f0
int StreamChild::GetPosition(int) const
{
    return (int)mnPosition;
}

// @ 0x0093b700
bool StreamChild::SetPosition(int distance, int type)
{
    if (mnAccessFlags == 0)
        return false;
    if (type == 0) {
        if (distance >= (int)mnSize)
            return false;
        mnPosition = distance;
        return true;
    }
    if (type == 1) {
        return mpStreamParent->SetPosition(distance + mnPositionParent + mnPosition, 0) != 0;
    }
    if (type == 2) {
        return mpStreamParent->SetPosition(distance + mnPositionParent + mnSize, 0) != 0;
    }
    return false;
}

// @ 0x0093b770
int StreamChild::Read(void* pData, size_t nSize)
{
    if (mnAccessFlags != 0) {
        if (!mpStreamParent->SetPosition(mnPositionParent + mnPosition, 0))
            return -1;
        int avail = GetAvailable();
        int take = (int)nSize;
        if (avail < take)
            take = avail;
        int n = mpStreamParent->Read(pData, take);
        if (n == take) {
            mnPosition += take;
            return take;
        }
    }
    return -1;
}

// @ 0x0093b7d0
StreamChild::StreamChild(IStream* pParent, size_type nPosition, size_type nSize)
{
    mnRefCount = 0;
    mnAccessFlags = 0;
    mpStreamParent = 0;
    mnPositionParent = 0;
    mnPosition = 0;
    mnSize = 0;
    if (pParent != 0)
        Open(pParent, nPosition, nSize);
}

// @ 0x0093b820
bool WriteEncoded(IStream* pStream, const wchar_t* pSrc, size_t count, int encoding)
{
    char buf[256];
    for (;;) {
        if (count == 0)
            return true;
        int len = 0x100;
        int n = Text::ConvertEncoding(pSrc, count, 0x10, buf, &len, encoding);
        count -= n;
        pSrc += n;
        if (!pStream->Write(buf, len))
            return false;
    }
}

// =============================================================================
// FixedMemoryStream
// =============================================================================

// @ 0x0093b8b0
int FixedMemoryStream::Release()
{
    if (mnRefCount > 1) {
        int n = mnRefCount - 1;
        mnRefCount = n;
        return n;
    }
    delete this;
    return 0;
}

// @ 0x0093b8e0
bool FixedMemoryStream::SetData(const void* pData, size_type nSize)
{
    mpData = (void*)pData;
    mnCapacity = nSize;
    mnSize = nSize;
    mnPosition = 0;
    return true;
}

// @ 0x0093b900
bool FixedMemoryStream::SetSize(size_type size)
{
    if (size <= mnCapacity) {
        mnSize = size;
        if (mnPosition > size)
            mnPosition = size;
        return true;
    }
    return false;
}

// @ 0x0093b920
int FixedMemoryStream::GetPosition(int type) const
{
    switch (type) {
    case 0: return (int)mnPosition;
    case 2: return (int)mnPosition - (int)mnSize;
    default: return 0;
    }
}

// @ 0x0093b950
bool FixedMemoryStream::SetPosition(int distance, int type)
{
    if (type == 0) {
        mnPosition = distance;
    } else if (type == 1) {
        mnPosition += distance;
    } else if (type == 2) {
        mnPosition = distance + mnSize;
    }
    if ((int)mnPosition > (int)mnSize) {
        mnPosition = mnSize;
        return false;
    }
    return true;
}

// @ 0x0093b9a0
int FixedMemoryStream::Read(void* pData, size_t nSize)
{
    if ((size_type)nSize > 0) {
        size_type avail = mnSize - mnPosition;
        if (avail != 0) {
            if (avail < (size_type)nSize)
                nSize = avail;
            MemCpyThunk(pData, (char*)mpData + mnPosition, nSize);
            mnPosition += nSize;
            return (int)nSize;
        }
    }
    return 0;
}

} // namespace IO
} // namespace EA
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
