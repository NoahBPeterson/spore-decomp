#include "types.h"

// Slice s005e0930: SP verb-tray / editor widgets.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.

// ---------------------------------------------------------------------------------------------
// @ 0x005e0e50  (matched)
struct RefObj {
    virtual void v0();
    virtual void v1();
    virtual void Release();     // +0x08
    void Shutdown(int);
};
struct BaseB { virtual void vb(); void ShutdownBase(); };
struct CShut : BaseB {
    char pad[0x50];
    RefObj* m54;                // +0x54
    void Shutdown();
};
void CShut::Shutdown()
{
    ShutdownBase();
    if (m54) {
        m54->Shutdown(1);
        RefObj* p = m54;
        if (p) {
            m54 = 0;
            p->Release();
        }
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x005e0cf0  ctor (complete; see nonmatching.txt)
struct BaseA { BaseA(); virtual void v0(); };
struct IBaseB { virtual void vb(); };
struct VerbTray : BaseA, IBaseB {
    char pad08[0x4c];      // +0x08..+0x53
    uint32_t z54[12];      // +0x54..+0x83
    char pad84[0xc];       // +0x84..+0x8f
    float f90[6];          // +0x90..+0xa4
    VerbTray();
};
VerbTray::VerbTray()
{
    z54[0] = 0; z54[1] = 0; z54[2] = 0; z54[3] = 0; z54[4] = 0; z54[5] = 0;
    z54[6] = 0; z54[7] = 0; z54[8] = 0; z54[9] = 0; z54[10] = 0; z54[11] = 0;
    f90[0] = 0.0f; f90[1] = 0.0f; f90[2] = 0.0f;
    f90[3] = 0.0f; f90[4] = 0.0f; f90[5] = 0.0f;
}

// ---------------------------------------------------------------------------------------------
// Not reconstructed.  See partial.txt.

// @ 0x005e0930
void FUN_005e0930(void* self) { (void)self; }

// @ 0x005e0d80
void FUN_005e0d80(void* self) { (void)self; }

// @ 0x005e0e80
void FUN_005e0e80(void* self) { (void)self; }

// @ 0x005e1020
void FUN_005e1020(void* self) { (void)self; }

// @ 0x005e12c0
void FUN_005e12c0(void* self) { (void)self; }
