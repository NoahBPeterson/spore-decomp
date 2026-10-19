// src/game/UTFSpore_Win32/EAStreamEncoding.cpp -- migrated from slice(s) s0093a9d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAStreamEncoding.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"
#include <intrin.h>

// ---- items of slice s0093a9d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
typedef unsigned int size_type;
namespace EA {
namespace Text {
int ConvertEncoding(const wchar_t* src, size_t srcCount, int srcEnc,
                    char* dst, int* dstLen, int dstEnc);              // 0x0093c950
}
}
namespace EA {
namespace Text {
int ConvertEncoding(const char* src, size_t srcCount, int srcEnc,
                    char* dst, int* dstLen, int dstEnc);
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
    virtual int         Write(const void* pData, size_t nSize); // +38
};
}
}
// ---- items of slice s0093a9d0 end

// @ 0x0093b820
namespace EA { namespace IO {
bool WriteEncoded(IStream_s0093_a9d0* pStream, const wchar_t* pSrc, size_t count, int encoding)
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
}}  // namespace EA::IO
