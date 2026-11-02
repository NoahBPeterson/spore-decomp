// src/game/UTFSpore_Win32/EAStreamAdapter.cpp -- migrated from slice(s) s00c562b0, s0093a9d0, s00939a60 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAStreamAdapter.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"
#include <intrin.h>
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cCity.h"
#include "SP/cCivData.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanet.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPGenericPressureEvent.h"
#include "SP/cSPMission.h"
#include "SP/cSPMissionHappinessEvent.h"
#include "SP/cTerrainSphere.h"

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned short _byteswap_ushort(unsigned short);
extern "C" unsigned long  _byteswap_ulong(unsigned long);
extern "C" uint64_t ByteSwap64(uint32_t lo, uint32_t hi);   // 0x008de020
extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(_byteswap_ushort, _byteswap_ulong)
#pragma intrinsic(__rdtsc)

// ---- items of slice s00939a60 begin (TODO(rewrite): local stubs, replace by canonical classes)
class IOStream {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual int  v14();
    virtual void v18();
    virtual unsigned v1c();
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
    virtual bool        Write(const void* pData, size_t nSize); // +38
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

// ---- items of slice s00c562b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
}
namespace SP {
template <class B> struct VPad<0, B> : B {};
}
namespace SP {
struct IEmpty {};
}
namespace SP {
struct cStarRecordRef;
}
namespace SP {
struct cPlanet_s00c5_62b0;
}
namespace SP {
struct cCivData_s00c5_62b0;
}
namespace SP {
struct cCity_s00c5_62b0;
}
namespace SP {
template <class T> class AutoRefCount {
public:
    T* mpObject;                                       // +0x00

    void operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* pOld = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pOld)
                pOld->Release();
        }
    }
    T* operator->() const { return mpObject; }
};
}
namespace SP {
struct tCivDataList {                                  // vector of civ data records
    cCivData_s00c5_62b0** mpBegin;                                // +0x00
    cCivData_s00c5_62b0** mpEnd;                                  // +0x04
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
}
namespace SP {
class cStarRecordRef {
public:
    uint8_t       pad000[0x15c];
    tCivDataList  mCivDataList;                        // +0x15c
    bool    FUN_00b8e040(uint32_t key);                // 0x00b8e040 loyalty booster present
    int32_t FUN_00b8de30();                            // 0x00b8de30 star record handle
    bool    FUN_00b8d970();                            // 0x00b8d970
    int32_t FUN_00b8dab0();                            // 0x00b8dab0
    void*   GetCommContext(void* pData);               // 0x00ce6950
    int32_t GetNumItemGroups();                        // 0x00c710c0
    void*   GetItemGroup(int32_t index);               // 0x00c71030
};
}
namespace SP {
struct ICPlanetVtbl : VPad<47, IEmpty> {
    virtual void AddRef();                             // +0xbc
    virtual void Release();                            // +0xc0
};
}
namespace SP {
class cPlanet_s00c5_62b0 : public ICPlanetVtbl {
public:
    uint8_t         pad004[0xd0];
    void*           mpSerializedState;                 // +0x0d4
    uint8_t         pad0d8[0x64];
    cStarRecordRef* mpStarRecord;                      // +0x13c
    uint8_t         pad140[0x78];
    uint8_t         mPendingEventCount;                // +0x1b8
    void FUN_00c71430(int32_t a, int32_t b);           // 0x00c71430
    int32_t FUN_00c710c0();                            // 0x00c710c0 item group count
    void* FUN_00c71030(int32_t index);                 // 0x00c71030 item group by index
};
}
namespace SP {
struct tCityList {                                     // cCivData::GetCities result
    cCity_s00c5_62b0** mpBegin;                                   // +0x00
    cCity_s00c5_62b0** mpEnd;                                     // +0x04
    int32_t size() const { return (int32_t)(mpEnd - mpBegin); }
};
}
namespace SP {
class cCivData_s00c5_62b0 {
public:
    tCityList* GetCities();                            // 0x005c65e0
};
}
namespace SP {
class cCity_s00c5_62b0 {
public:
    uint8_t pad00[0x30];
    float   mHappiness;                                // +0x30
};
}
namespace SP {
struct IArchiveWriter : VPad<6, IEmpty> {
    virtual void* GetStream();                                     // +0x18
};
}
namespace SP {
struct IArchiver0 : VPad<6, IEmpty> {
    virtual void* GetStream();                                     // +0x18
    virtual void* EndRead();                                       // +0x1c
};
}
namespace SP {
struct IArchiver : IArchiver0 {
    virtual IArchiveWriter* GetWriter();                           // +0x20
    virtual void* ReadItem(uint32_t typeID, void* pItem, int32_t flag);   // +0x24
    virtual void* SerializeItem(uint32_t typeID, void* pItem, int32_t flag); // +0x28
    virtual void* SerializeObject(void* pObject);                  // +0x2c
};
}
namespace SP {
bool __cdecl EA_WriteUint32(void* pStream, const uint32_t* pValue, int32_t count,
                            int32_t flag);                 // 0x0093aa70
}
namespace SP {
struct tItemInfo {                                     // 0xc-byte "requested"/"delivered" record
    AutoRefCount<cPlanet_s00c5_62b0> mpPlanet;                    // +0x00
    int32_t               mRequested;                  // +0x04
    int32_t               mDelivered;                  // +0x08
};
}
// ---- items of slice s00c562b0 end

// @ 0x0093a6c0
bool WriteExact(IOStream* s, void* buf, int n)
{
    if (s->v14())
        return false;
    bool b = s->v30(buf, n) == n;
    return b;
}

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
    bool ok;
    if (endian == 1) {
        ok = pStream->Write(pData, count * 2);
    } else {
        ok = true;
        while (count != 0) {
            uint16_t v = *pData;
            count--;
            pData++;
            uint32 tmp = _byteswap_ushort(v);
            if (!pStream->Write(&tmp, 2)) {
                ok = false;
                break;
            }
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

// @ 0x0093ab10
namespace EA { namespace IO {
bool WriteUint64(IStream_s0093_a9d0* pStream, const uint64_t* pData, uint32 count, int endian)
{
    if (endian != 1)
        pStream->GetAccessFlags();
    if (pStream->GetState() != 0)
        return false;
    bool ok;
    if (endian == 1) {
        ok = pStream->Write(pData, count * 8);
    } else {
        ok = true;
        while (count != 0) {
            uint64_t v = *pData;
            count--;
            uint64_t tmp = ByteSwap64((uint32)v, (uint32)(v >> 32));
            pData++;
            if (!pStream->Write(&tmp, 8)) {
                ok = false;
                break;
            }
        }
    }
    return ok;
}
}}  // namespace EA::IO

// @ 0x0093abd0
namespace EA { namespace IO {
bool WriteString(IStream_s0093_a9d0* pStream, const char* pStr, int count, int mode)
{
    if (pStream->GetState() != 0)
        return false;

    bool bResult(true);

    if (count == -1) {
        count = 0;
        const char* pCurrent = pStr;
        while (*pCurrent++)
            ++count;
    }

    if (count)
        bResult = pStream->Write(pStr, count);

    if (bResult) {
        if (mode == 1) {
            if (!count || ((pStr[count - 1] != '\n') && (pStr[count - 1] != '\r')))
                mode = 2;
        }
        if (mode == 3) {
            const char terminator[2] = { '\r', '\n' };
            bResult = pStream->Write(terminator, sizeof(terminator));
        } else if (mode == 2) {
            const char terminator[1] = { '\n' };
            bResult = pStream->Write(terminator, sizeof(terminator));
        }
    }
    return bResult;
}
}}  // namespace EA::IO

// @ 0x0093ac80
namespace EA { namespace IO {
bool ReadBool(IStream_s0093_a9d0* pStream, bool* pOut)
{
    if (pStream->GetState() != 0)
        return false;
    if (pStream->Read(pOut, 1) == 1) {
        *pOut = (*pOut != 0);
        return true;
    }
    return false;
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
    if (EA::IO::ReadInt32(pStream, &len, 1, endian)) {
        bool ok;
        if (pOut == 0) {
            ok = pStream->SetPosition(pStream->GetPosition(0) - 4, 0);
        } else if ((uint32)len <= (uint32)(maxCount - 1)) {
            ok = ReadBytes(pStream, pOut, len);
            pOut[len] = 0;
        } else {
            ok = ReadBytes(pStream, pOut, maxCount);
            pOut[maxCount - 1] = 0;
            if (!ok)
                return -1;
            ok = pStream->SetPosition(pStream->GetPosition(0) + (len - maxCount), 0);
        }
        if (ok)
            return len;
    }
    return -1;
}
}}  // namespace EA::IO

// @ 0x0093adb0
namespace EA { namespace IO {
bool WriteCString(IStream_s0093_a9d0* pStream, const char* pStr, int count, int endian)
{
    if (endian != 1)
        pStream->GetAccessFlags();
    if (pStream->GetState() != 0)
        return false;
    if (count == -1) {
        count = 0;
        const char* pCurrent = pStr;
        while (*pCurrent != 0) {
            pCurrent++;
            count++;
        }
    }
    uint32 len = count;
    bool ok = WriteUint32(pStream, &len, 1, endian);
    if (ok && count != 0)
        ok = pStream->Write(pStr, count);
    return ok;
}
}}  // namespace EA::IO

// @ 0x00c56e60
namespace SP {
IArchiver& operator<<(IArchiver& archiver, const tItemInfo& item)
{
    void* pStream = archiver.GetWriter()->GetStream();
    uint32_t value = (uint32_t)item.mRequested;
    EA_WriteUint32(pStream, &value, 1, 0);
    pStream = archiver.GetWriter()->GetStream();
    value = (uint32_t)item.mDelivered;
    EA_WriteUint32(pStream, &value, 1, 0);
    archiver.SerializeObject(item.mpPlanet.mpObject ? &item.mpPlanet.mpObject->mpSerializedState : 0);
    return archiver;
}
}  // namespace SP
