// src/game/UTFSpore_Win32/EAStreamChild.cpp -- migrated from slice(s) s0093a9d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAStreamChild.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"
#include <intrin.h>

// ---- items of slice s0093a9d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
typedef unsigned int size_type;
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
class StreamChild : public IStream_s0093_a9d0 {
public:
    StreamChild(IStream_s0093_a9d0* pParent = 0, size_type nPosition = 0, size_type nSize = 0);
    ~StreamChild();

    bool Open(IStream_s0093_a9d0* pStreamParent, size_type nPosition, size_type nSize);

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
    IStream_s0093_a9d0*  mpStreamParent;    // +0c
    size_type mnPositionParent;  // +10
    size_type mnPosition;        // +14
    size_type mnSize;            // +18
};
}
}
// ---- items of slice s0093a9d0 end

// @ 0x0093b6a0
namespace EA { namespace IO {
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
}}  // namespace EA::IO

// @ 0x0093b6d0
namespace EA { namespace IO {
int StreamChild::GetState() const
{
    if (mpStreamParent != 0)
        return mpStreamParent->GetState();
    return 0;
}
}}  // namespace EA::IO

// @ 0x0093b6f0
namespace EA { namespace IO {
int StreamChild::GetPosition(int) const
{
    return (int)mnPosition;
}
}}  // namespace EA::IO

// @ 0x0093b700
namespace EA { namespace IO {
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
}}  // namespace EA::IO

// @ 0x0093b770
namespace EA { namespace IO {
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
}}  // namespace EA::IO
