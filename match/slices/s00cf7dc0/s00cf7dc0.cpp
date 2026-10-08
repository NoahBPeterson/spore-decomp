// Slice s00cf7dc0: FUN_00cf86d0 (VA 00cf86d0, 381 bytes, thiscall, plain ret).
//
// Tears down the per-mode sim hand-off when the owner's flag at +0xe0 is set:
//   ticker = SimTicker();
//   if (mbPending) {
//       cSimSingleton::Get()->FUN_00dcc2c0();          // thiscall, no args
//       ticker->Slot54(cSimSingleton::Get());
//       cSimMode200::Get()->Slot20();                   // virtual, no args
//       ticker->Slot54(cSimMode200::Get());
//       ticker->Slot54(cSimMode64::Get());
//       cSimMode64::Get()->FUN_00ae6570();              // thiscall, no args
//       mbPending = false;
//   }
// Each singleton is created lazily with the "Simulator/SimSingleton" tag, so every
// Get() re-reads its global exactly as the original does.
//
// Flags: default /O2 /MD /Gy /TP.
#include "types.h"
#pragma warning(disable : 4291)

#define VPAD4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);

struct cSimTicker {                            // SimTicker() returns this (0x00b3d330)
    VPAD4(a) VPAD4(b) VPAD4(c) VPAD4(d) VPAD4(e)
    virtual void s50();
    virtual void Slot54(void* p);              // +0x54
};
cSimTicker* SimTicker();                       // 0x00b3d330

struct cSimSingleton {                         // 0x58 bytes, ctor 0x00dc7d70
    uint32_t mData[0x58 / 4];
    cSimSingleton();                           // 0x00dc7d70
    void FUN_00dcc2c0();                       // 0x00dcc2c0 (thiscall, no args)
    static cSimSingleton* sInstance;           // 0x01699ab8
    static cSimSingleton* Get()
    {
        if (!sInstance)
            sInstance = new ("Simulator/SimSingleton", 0, 0, 0, 0) cSimSingleton();
        return sInstance;
    }
};

struct cSimMode200 {                           // 0xc8 bytes, polymorphic, ctor 0x00ae5c30
    VPAD4(a) VPAD4(b)
    virtual void Slot20();                     // +0x20
    uint32_t mData[(0xc8 - 4) / 4];
    cSimMode200();                             // 0x00ae5c30
    static cSimMode200* sInstance;             // 0x0167a60c
    static cSimMode200* Get()
    {
        if (!sInstance)
            sInstance = new ("Simulator/SimSingleton", 0, 0, 0, 0) cSimMode200();
        return sInstance;
    }
};

struct cSimMode64 {                            // 0x40 bytes, polymorphic, ctor 0x00ae6a70
    virtual void v0();
    uint32_t mData[(0x40 - 4) / 4];
    cSimMode64();                              // 0x00ae6a70
    void FUN_00ae6570();                       // 0x00ae6570 (thiscall, no args)
    static cSimMode64* sInstance;              // 0x0167a690
    static cSimMode64* Get()
    {
        if (!sInstance)
            sInstance = new ("Simulator/SimSingleton", 0, 0, 0, 0) cSimMode64();
        return sInstance;
    }
};

struct cSimModeOwner {
    uint32_t pad00[0xe0 / 4];
    bool mbPending;                            // +0xe0
    void FUN_00cf86d0();                       // 0x00cf86d0
};

void cSimModeOwner::FUN_00cf86d0()
{
    cSimTicker* ticker = SimTicker();
    if (mbPending) {
        cSimSingleton::Get()->FUN_00dcc2c0();
        ticker->Slot54(cSimSingleton::Get());
        cSimMode200::Get()->Slot20();
        ticker->Slot54(cSimMode200::Get());
        ticker->Slot54(cSimMode64::Get());
        cSimMode64::Get()->FUN_00ae6570();
        mbPending = false;
    }
}
