// src/game/UTFSpore_Win32/EAStreamfixedmemory.cpp -- migrated from slice(s) s0093b9e0, s0093a9d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAStreamfixedmemory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);   // 0x011e0744 (memcpy thunk)
#include <intrin.h>
#include "EA/IO/MemoryStream.h"
#include "EA/IO/SharedPointer.h"
#include <new>

// ---- items of slice s0093a9d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
typedef unsigned int size_type;
extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);   // 0x011e0744 (memcpy thunk)
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
    virtual int         Write(const void* pData, size_t nSize); // +38
};
}
}
namespace EA {
namespace IO {
class FixedMemoryStream : public IStream_s0093_a9d0 {
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
}
}
// ---- items of slice s0093a9d0 end

// ---- items of slice s0093b9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
// ---- items of slice s0093b9e0 end

// @ 0x0093b900
namespace EA { namespace IO {
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
}}  // namespace EA::IO

// @ 0x0093b920
namespace EA { namespace IO {
int FixedMemoryStream::GetPosition(int type) const
{
    switch (type) {
    case 0: return (int)mnPosition;
    case 2: return (int)mnPosition - (int)mnSize;
    default: return 0;
    }
}
}}  // namespace EA::IO

// @ 0x0093b950
namespace EA { namespace IO {
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
}}  // namespace EA::IO

// @ 0x0093b9a0
namespace EA { namespace IO {
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
}}  // namespace EA::IO

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
