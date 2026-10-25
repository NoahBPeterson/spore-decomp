// src/game/SPGonzago/SPAudioResourceCityMusic.cpp -- migrated from slice(s) s00eb1e80, s00eb0ea0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAudioResourceCityMusic.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Stopwatch.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedExchange(volatile long* pTarget, long nValue);
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s00eb0ea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
extern "C" long _InterlockedExchange(volatile long* pTarget, long nValue);
inline void* operator new(uint32_t, void* pPlace) { return pPlace; }
void* operator_new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                   const char* pFile, int32_t nLine);           // 0x00f473a0
bool WriteUint32(void* pStream, const uint32_t* pValue, uint32_t nCount,
                 int32_t nEndian);                              // 0x0093aa70
class cPropertyList {
public:
    __forceinline cPropertyList()
    {
        _InterlockedExchange(&mnRefCount, 0);
        mnField08 = 0;
        mnField0C = 0;
        mnField10 = 0;
    }
virtual void p00();
virtual void p04();
virtual void p08();
    virtual void* GetProperty(uint32_t nKey);                   // 0x00c
    virtual void* GetPropertyValue(uint32_t nKey, void** ppValue);  // 0x024

    volatile long mnRefCount;                                   // 0x004
    uint32_t mnField08;                                         // 0x008
    uint32_t mnField0C;                                         // 0x00c
    uint32_t mnField10;                                         // 0x010
};
class cResourceCityMusic : public cPropertyList {
public:
    cResourceCityMusic();

    uint32_t mnField14;                                         // 0x014
    uint32_t mnField18;                                         // 0x018
    uint32_t* mpData1CBegin;                                    // 0x01c
    uint32_t* mpData1CEnd;                                      // 0x020
    uint32_t* mpData1CCap;                                      // 0x024
    uint8_t  mPad028[0x08];                                     // 0x028
    uint32_t* mpData30Begin;                                    // 0x030
    uint32_t* mpData30End;                                      // 0x034
    uint32_t* mpData30Cap;                                      // 0x038
    uint8_t  mPad03C[0x08];                                     // 0x03c
    uint32_t* mpData44Begin;                                    // 0x044
    uint32_t* mpData44End;                                      // 0x048
    uint32_t* mpData44Cap;                                      // 0x04c
    uint8_t  mPad050[0x08];                                     // 0x050
    uint32_t* mpData58Begin;                                    // 0x058
    uint32_t* mpData58End;                                      // 0x05c
    uint32_t* mpData58Cap;                                      // 0x060
    uint8_t  mPad064[0x08];                                     // 0x064
};
class cWriter {
public:
virtual void w00();
virtual void w04();
virtual void w08();
virtual void w0c();
    virtual void w10();
    virtual void SetField08(void* pValue);                      // 0x014
    virtual void* GetStream();                                  // 0x018
};
class cFactoryCityMusic {
public:
virtual void f00();
virtual void f04();
virtual void f08();
virtual void f0c();
virtual void f10();
virtual void f14();
virtual void f18();
virtual void f1c();
    virtual void f20();
    virtual bool CreateAndWrite(void* pArg1, void* pResource, uint32_t nArg3,
                                uint32_t nArg4);                // 0x024

    bool WriteResource(cResourceCityMusic* pResource, cWriter* pWriter,
                       void* pUnusedA, void* pUnusedB);         // 0x00eb1c10
    bool CreateResource(void* pArg1, void** ppOut, uint32_t nArg3,
                        uint32_t nArg4);                        // 0x00eb1dc0
};
// ---- items of slice s00eb0ea0 end

// ---- items of slice s00eb1e80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __fastcall FUN_00eb0230(void* self, int dummy, int n);             // 0x00eb0230
extern "C" void  __fastcall FUN_00478930(void* self, int dummy, int n);             // 0x00478930 string grow
extern "C" void  __fastcall FUN_00530670(void* self, int dummy);                    // 0x00530670 ~string
int  FUN_0093a780(void* s, void* d, int n, int z);   // 0x0093a780 EA::IO::ReadInt32
int  FUN_0093a6c0(void* s, void* b, int n);          // 0x0093a6c0 read raw bytes
void FUN_0093a800(void* s, void* b, int n, int z);   // 0x0093a800
namespace SP {
class cGameCinematicsAppMode { public:
    char pad[0x100];
    bool OnKeyDown(int k, int v);                       // 0x00eb2370
    void HandleSimulationUpdate(float a, float b);      // 0x00eb23d0
    unsigned AsInterface(int id);                       // 0x00eb2440
    void DtorBody();                                    // 0x00eb2470
    bool Init(int* p);                                  // 0x00eb2520
    bool Shutdown();                                    // 0x00eb25d0
    unsigned HandleMessage(unsigned msg, unsigned a2);  // 0x00eb2600
    cGameCinematicsAppMode* CtorBody();                 // 0x00eb28e0
    bool Activate();                                    // 0x00eb2990
    void Deactivate();                                  // 0x00eb2c70
    bool ReadResource(void* a1, void* a2, int a3, int a4); // 0x00eb20d0
};
}
struct VectorI {
    float* begin;
    float* end;
    float* cap;
    void insert(float* pos, unsigned n, const float* val);   // 0x00eb1e80
    void resize(unsigned n);                                 // 0x00eb2070
};
struct String8 { char* mpBegin; char* mpEnd; char* mpCap; };
typedef void*  (__thiscall *FP0)(void*);
typedef void*  (__thiscall *FP1)(void*, int);
#define VT(o)         (*(void***)(o))
// ---- items of slice s00eb1e80 end

// @ 0x00eb1c10
bool cFactoryCityMusic::WriteResource(cResourceCityMusic* pResource, cWriter* pWriter, void* pUnusedA, void* pUnusedB)
{
    pWriter->SetField08(&pResource->mnField08);

    cResourceCityMusic* pData;
    if (pResource != nullptr)
        pData = (cResourceCityMusic*)pResource->GetProperty(0x04f67fb5);
    else
        pData = nullptr;

    bool bOk = (pData != nullptr);
    if (bOk) {
        void* pStream = pWriter->GetStream();

        uint32_t nMagic = 0x20434d50;
        bOk &= WriteUint32(pStream, &nMagic, 1, 0);
        uint32_t nVersion = 1;
        bOk &= WriteUint32(pStream, &nVersion, 1, 0);
        bOk &= WriteUint32(pStream, &pData->mnField14, 1, 0);
        bOk &= WriteUint32(pStream, &pData->mnField18, 1, 0);

        uint32_t nCount = (uint32_t)(pData->mpData1CEnd - pData->mpData1CBegin);
        bOk &= WriteUint32(pStream, &nCount, 1, 0);
        bOk &= WriteUint32(pStream, pData->mpData1CBegin, nCount, 0);
        bOk &= WriteUint32(pStream, pData->mpData30Begin, nCount, 0);

        nCount = (uint32_t)(pData->mpData44End - pData->mpData44Begin);
        bOk &= WriteUint32(pStream, &nCount, 1, 0);
        bOk &= WriteUint32(pStream, pData->mpData44Begin, nCount, 0);

        nCount = (uint32_t)(pData->mpData58End - pData->mpData58Begin);
        bOk &= WriteUint32(pStream, &nCount, 1, 0);
        bOk &= WriteUint32(pStream, pData->mpData58Begin, nCount, 0);
    }

    return bOk;
}

// @ 0x00eb1dc0
bool cFactoryCityMusic::CreateResource(void* pArg1, void** ppOut, uint32_t nArg3, uint32_t nArg4)
{
    uint8_t* pMemory = (uint8_t*)operator_new(0x6c, "Audio", 0, 0, 0, 0);
    cResourceCityMusic* pResource = new (pMemory) cResourceCityMusic();

    if (pResource != nullptr)
        pResource->p00();

    if (pArg1 != nullptr) {
        if (!CreateAndWrite(pArg1, pResource, nArg3, nArg4)) {
            if (pResource != nullptr)
                pResource->p04();
            return false;
        }
    }

    *ppOut = pResource;
    return true;
}

// @ 0x00eb20d0
namespace SP {
bool cGameCinematicsAppMode::ReadResource(void* a1, void* a2, int a3, int a4)
{
    (void)a3; (void)a4;
    int* obj = (int*)a2;
    int* p = (int*)((FP0)VT(a1)[0x10 / 4])(a1);
    obj[2] = p[0];
    obj[3] = p[1];
    obj[4] = p[2];

    int* chunk = (int*)((FP1)VT(obj)[0xc / 4])(obj, 0x4f67fb5);
    if (chunk == 0) return false;
    bool ok = true;

    void* stream = (void*)((FP0)VT(a1)[0x18 / 4])(a1);
    int hdr = 0, ver = 0, cnt = 0;
    ok = ok && FUN_0093a780(stream, &hdr, 1, 0);
    ok = ok && FUN_0093a780(stream, &ver, 1, 0);
    if (!ok || hdr != 0x20434d50 || (unsigned)ver > 1u) return false;

    ok = ok && FUN_0093a780(stream, (char*)chunk + 0x14, 1, 0);
    ok = ok && FUN_0093a780(stream, (char*)chunk + 0x18, 1, 0);
    ok = ok && FUN_0093a780(stream, &cnt, 1, 0);
    if (ok) {
        FUN_00eb0230((char*)chunk + 0x1c, 0, cnt);
        ok = ok && FUN_0093a780(stream, *(void**)((char*)chunk + 0x1c), cnt, 0);
        ((VectorI*)((char*)chunk + 0x30))->resize((unsigned)cnt);
        ok = ok && FUN_0093a780(stream, *(void**)((char*)chunk + 0x30), cnt, 0);
    }
    ok = ok && FUN_0093a780(stream, &cnt, 1, 0);
    if (ok) {
        FUN_00eb0230((char*)chunk + 0x44, 0, cnt);
        ok = ok && FUN_0093a780(stream, *(void**)((char*)chunk + 0x44), cnt, 0);
    }
    ok = ok && FUN_0093a780(stream, &cnt, 1, 0);
    if (ok) {
        ((VectorI*)((char*)chunk + 0x58))->resize((unsigned)cnt);
        ok = ok && FUN_0093a780(stream, *(void**)((char*)chunk + 0x58), cnt, 0);
    }
    if (ok && ver == 0) {
        String8 str;
        str.mpBegin = (char*)0x1667bac;
        str.mpEnd   = (char*)0x1667bac;
        str.mpCap   = (char*)0x1667bad;
        ok = ok && FUN_0093a780(stream, &cnt, 1, 0);
        if (ok) {
            FUN_00478930(&str, 0, cnt);
            ok = ok && FUN_0093a6c0(stream, str.mpBegin, cnt + 1);
        }
        ok = ok && FUN_0093a780(stream, &cnt, 1, 0);
        if (ok) {
            FUN_00478930(&str, 0, cnt);
            ok = ok && FUN_0093a6c0(stream, str.mpBegin, cnt + 1);
        }
        ok = ok && FUN_0093a780(stream, &cnt, 1, 0);
        if (ok) {
            FUN_00478930(&str, 0, cnt);
            FUN_0093a6c0(stream, str.mpBegin, cnt + 1);
        }
        int tmp = 0;
        FUN_0093a800(stream, &tmp, 1, 0);
        FUN_00530670(&str, 0);
    }
    return ok;
}
}  // namespace SP
