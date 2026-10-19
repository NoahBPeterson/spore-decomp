// src/game/UTFSpore_Win32/EAStreamAdapter.cpp -- migrated from slice(s) s0093a9d0, s00939a60 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAStreamAdapter.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned short _byteswap_ushort(unsigned short);
extern "C" unsigned long  _byteswap_ulong(unsigned long);
extern "C" uint64_t ByteSwap64(uint32_t lo, uint32_t hi);   // 0x008de020
extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(_byteswap_ushort, _byteswap_ulong)
#pragma intrinsic(__rdtsc)

// ---- items of slice s00939a60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned long  _byteswap_ulong(unsigned long);
extern "C" uint64_t ByteSwap64(uint32_t lo, uint32_t hi);   // 0x008de020
class IOStream {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual int  v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void* v24(int);
    virtual void v28(int, int);
    virtual unsigned v2c();
    virtual int  v30(void* buf, int n);
    virtual void v34();
    virtual bool v38(void* buf, int n);
};
// ---- items of slice s00939a60 end

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
bool ReadInt32(IStream_s0093_a9d0* pStream, int* pOut, int count, int endian);  // 0x0093a780
}
}
namespace EA {
namespace IO {
bool ReadBytes(IStream_s0093_a9d0* pStream, void* pOut, int count);             // 0x0093a6c0
}
}
// ---- items of slice s0093a9d0 end

// @ 0x0093a780
bool ReadInt32(IOStream* s, uint32_t* buf, int count, int bigEndian)
{
    if (bigEndian != 1)
        s->v10();
    if (s->v14())
        return false;
    bool ok = false;
    if (s->v30(buf, count * 4) == count * 4) {
        if (bigEndian != 1) {
            while (count--) {
                *buf = _byteswap_ulong(*buf);
                ++buf;
            }
        }
        ok = true;
    }
    return ok;
}

// @ 0x0093a800
bool ReadUInt64(IOStream* s, uint64_t* buf, int count, int bigEndian)
{
    if (bigEndian != 1)
        s->v10();
    if (s->v14())
        return false;
    bool ok = false;
    if (s->v30(buf, count * 8) == count * 8) {
        if (bigEndian != 1) {
            while (count--) {
                uint32_t* p = (uint32_t*)buf;
                *(uint64_t*)buf = ByteSwap64(p[0], p[1]);
                ++buf;
            }
        }
        ok = true;
    }
    return ok;
}

// @ 0x0093a890
bool HasRoom(IOStream* s, int a, int b)
{
    return (unsigned)(a * b) <= s->v2c();
}

// @ 0x0093a8b0
unsigned ReadLine(IOStream* s, char* buf)
{
    if (s->v14())
        return 0;
    int n = 0;
    unsigned len = 0;
    void* alloc = 0;
    if (buf == 0)
        alloc = s->v24(0);
    char ch = 0;
    if (s->v30(&ch, 1) == 1) {
        do {
            ++n;
            if (ch == '\r' || ch == '\n') {
                char ch2 = ch;
                int r = 1;
                if (ch == '\r')
                    r = s->v30(&ch2, 1);
                if (r == 1 && ch2 != '\n')
                    s->v28(-1, 1);
                goto done;
            }
            if (buf != 0 && len < 0xffffffffu)
                *buf++ = ch;
            ++len;
        } while (s->v30(&ch, 1) == 1);
        if (n != 0)
            goto done;
    }
    len = 0xfffffffe;
done:
    if (buf == 0) {
        s->v28((int)alloc, 0);
        return len;
    }
    *buf = 0;
    return len;
}

// @ 0x0093a9a0
bool StreamWrite(IOStream* s, int a, int b)
{
    if (s->v14())
        return false;
    return s->v38((void*)a, b);
}

// @ 0x0093a9d0
namespace EA { namespace IO {
bool WriteUint16(IStream_s0093_a9d0* pStream, const uint16_t* pData, uint32 count, int endian)
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
}}  // namespace EA::IO

// @ 0x0093aa70
namespace EA { namespace IO {
bool WriteUint32(IStream_s0093_a9d0* pStream, const uint32* pData, uint32 count, int endian)
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
}}  // namespace EA::IO

// @ 0x0093acd0
namespace EA { namespace IO {
int ReadString(IStream_s0093_a9d0* pStream, char* pOut, int maxCount, int endian)
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
}}  // namespace EA::IO
