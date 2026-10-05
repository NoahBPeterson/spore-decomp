// Slice s005a33c0 -- SP::cSPEditorBlockAbilities-ish wrapper + 2 large UI functions.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16

struct Wrapper;

struct IVtObj {
    PV4                                 // 0x00..0x0c
    virtual IVtObj* GetObj();           // 0x10
    PV                                  // 0x14
    PV4                                 // 0x18..0x24
    virtual int Check();                // 0x28
    PV16                                // 0x2c..0x68
    PV4                                 // 0x6c..0x78
    virtual void SetFlag(int a, bool b); // 0x7c
    PV16                                // 0x80..0xbc
    PV8                                 // 0xc0..0xdc
    PV2                                 // 0xe0..0xe4
    virtual void DoE8(IVtObj* w);       // 0xe8
};

struct Wrapper {
    char    pad[0x10];
    IVtObj* mpObject;   // +0x10
    bool FUN_005a41e0();          // 0x005a41e0
    void FUN_005a4200(bool flag); // 0x005a4200
};

// ===========================================================================
// @ 0x005a41e0
bool Wrapper::FUN_005a41e0()
{
    if (mpObject)
        return (mpObject->Check() & 1) != 0;
    return false;
}

// ===========================================================================
// @ 0x005a4200
void Wrapper::FUN_005a4200(bool flag)
{
    if (mpObject) {
        mpObject->SetFlag(1, flag);
        if (flag) {
            if (mpObject->GetObj())
                mpObject->GetObj()->DoE8(mpObject);
        }
    }
}

// ===========================================================================
// @ 0x005a33c0
void FUN_005a33c0(void* self)
{
    (void)self;
}

// @ 0x005a3e10
void FUN_005a3e10(void* self)
{
    (void)self;
}
