// src/game/SPGonzago/SPTribeHut.cpp -- migrated from slice(s) s01355f90, s005718f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeHut.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include <string.h>
#include <math.h>
#include <intrin.h>

// ---- items of slice s005718f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
namespace EA {
namespace Audio {
struct SystemAT {
    PV8 PV4 PV2
    virtual void BeginMessage(uint32_t id);                 // +0x38
    virtual void SetFloat(uint32_t id, float v);            // +0x3c
    virtual void SetInt(uint32_t id, uint32_t v);           // +0x40
    virtual void pv41();
    virtual void pv42();
    virtual void SetString(uint32_t id, const char* s, uint32_t len);   // +0x4c
    virtual void pv44();
    virtual void pv45();
    virtual void SendMessage();                             // +0x58
};
}
}
namespace EA {
namespace Audio {
SystemAT* __cdecl GetSystemAT();
}
}
// ---- items of slice s005718f0 end

// ---- items of slice s01355f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void E209_1_24();   // 0x00aca090
extern void E209_1_28();   // 0x00bca960
extern void E209_1_2C();   // 0x00c2e4e0
extern void E209_1_30();   // 0x00692fb0
extern void E209_1_34();   // 0x00b6f550
extern void E209_1_38();   // 0x00ac8050
extern void E209_2_24();   // 0x00ae3430
extern void E209_2_28();   // 0x00ae3450
extern void E209_2_2C();   // 0x00693150
extern void E209_2_30();   // 0x00695080
extern void E209_3_24();   // 0x00ae3430
extern void E209_3_28();   // 0x00ae3450
extern void E209_3_2C();   // 0x00693150
extern void E209_3_30();   // 0x00695080
extern void E209_4_24();   // 0x00ae3430
extern void E209_4_28();   // 0x00ae3450
extern void E209_4_2C();   // 0x00693150
extern void E209_4_30();   // 0x00695080
extern void E209_5_24();   // 0x00ae3430
extern void E209_5_28();   // 0x00ae3450
extern void E209_5_2C();   // 0x00693150
extern void E209_5_30();   // 0x00695080
extern void E209_F34();    // 0x00b1fbf0
extern void E209_F38();    // 0x00ae5720
extern void E209_6_24();   // 0x00bd0cb0
extern void E209_6_28();   // 0x00bca960
extern void E209_6_2C();   // 0x00c2e4e0
extern void E209_6_30();   // 0x00692fb0
extern void E209_6_34();   // 0x00b6f550
extern void E209_6_38();   // 0x00ac8050
typedef unsigned int   u32;
struct PropDesc {
    const char* mName;    // +0x00
    u32 mHash;            // +0x04
    u32 mType;            // +0x08
    u32 mPad0C;           // +0x0c
    u32 mPad10;           // +0x10
    u32 mPad14;           // +0x14
    u32 mZero18;          // +0x18
    u32 mZero1C;          // +0x1c
    void* mDefault;       // +0x20
    void* mFn24;          // +0x24
    void* mFn28;          // +0x28
    void* mFn2C;          // +0x2c
    void* mFn30;          // +0x30
    void* mFn34;          // +0x34
    void* mFn38;          // +0x38
};
// ---- items of slice s01355f90 end

// @ 0x00571f80
void __cdecl Start3dSoundByName(uint32_t soundId, uint32_t objectId, float x, float y, float z)
{
    EA::Audio::SystemAT* sys = EA::Audio::GetSystemAT();
    if (sys) {
        sys->BeginMessage(0x3475365);
        sys->SetInt(0x3475381, soundId);
        sys->SetInt(0x3475385, objectId);
        sys->SetFloat(0x3475391, x);
        sys->SetFloat(0x3475395, y);
        sys->SetFloat(0x3475398, z);
        sys->SendMessage();
    }
}

// @ 0x01356230
void FUN_01356230(void)
{
    PropDesc d;

    d.mName = (const char*)0x145a45c;
    d.mHash = 0x33e0b60;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_1_24;
    d.mFn28 = (void*)E209_1_28;
    d.mFn2C = (void*)E209_1_2C;
    d.mFn30 = (void*)E209_1_30;
    d.mFn34 = (void*)E209_1_34;
    d.mFn38 = (void*)E209_1_38;
    d.mType = 0x230;
    *(PropDesc*)0x157c3d0 = d;

    d.mName = (const char*)0x14745ac;
    d.mHash = 0x33e0b61;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_2_24;
    d.mFn28 = (void*)E209_2_28;
    d.mFn2C = (void*)E209_2_2C;
    d.mFn30 = (void*)E209_2_30;
    d.mFn34 = (void*)E209_F34;
    d.mFn38 = (void*)E209_F38;
    d.mType = 0x20c;
    *(PropDesc*)0x157c40c = d;

    d.mName = (const char*)0x1474598;
    d.mHash = 0x33e0b62;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_3_24;
    d.mFn28 = (void*)E209_3_28;
    d.mFn2C = (void*)E209_3_2C;
    d.mFn30 = (void*)E209_3_30;
    d.mFn34 = (void*)E209_F34;
    d.mFn38 = (void*)E209_F38;
    d.mType = 0x200;
    *(PropDesc*)0x157c448 = d;

    d.mName = (const char*)0x1474584;
    d.mHash = 0x33e0b63;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_4_24;
    d.mFn28 = (void*)E209_4_28;
    d.mFn2C = (void*)E209_4_2C;
    d.mFn30 = (void*)E209_4_30;
    d.mFn34 = (void*)E209_F34;
    d.mFn38 = (void*)E209_F38;
    d.mType = 0x1e8;
    *(PropDesc*)0x157c484 = d;

    d.mName = (const char*)0x1474570;
    d.mHash = 0x33e0b64;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_5_24;
    d.mFn28 = (void*)E209_5_28;
    d.mFn2C = (void*)E209_5_2C;
    d.mFn30 = (void*)E209_5_30;
    d.mFn34 = (void*)E209_F34;
    d.mFn38 = (void*)E209_F38;
    d.mType = 0x1f4;
    *(PropDesc*)0x157c4c0 = d;

    d.mName = (const char*)0x1467dac;
    d.mHash = 0x5651e69;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_6_24;
    d.mFn28 = (void*)E209_6_28;
    d.mFn2C = (void*)E209_6_2C;
    d.mFn30 = (void*)E209_6_30;
    d.mFn34 = (void*)E209_6_34;
    d.mFn38 = (void*)E209_6_38;
    d.mType = 0x234;
    *(PropDesc*)0x157c4fc = d;
}
