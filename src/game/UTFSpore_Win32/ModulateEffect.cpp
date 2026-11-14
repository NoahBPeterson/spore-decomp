// src/game/UTFSpore_Win32/ModulateEffect.cpp

#include "game/types.h"

// unnamed retail callees (address in the comment)
void* GetDefaultAllocator();                                     // 0x009512c0
void* AllocObject(int size, int align, const char* name, void* allocator);  // 0x009512d0
uint32_t WinColor_Lerp(uint32_t a, uint32_t b, float t);         // 0x007f5eb0

namespace EA {
namespace UTFWinControls {

// Interface reached only through its SetColor slot; the leading slots are
// padding so the call lands on vtable +0x5c (slot 23).
#define VTABLE_SLOT(name) virtual void name();
#define VTABLE_SLOTS_4(a, b, c, d) VTABLE_SLOT(a) VTABLE_SLOT(b) VTABLE_SLOT(c) VTABLE_SLOT(d)

struct IColorTarget {
    VTABLE_SLOTS_4(Unused00, Unused01, Unused02, Unused03)  // vtable +0x00..0x0c
    VTABLE_SLOTS_4(Unused04, Unused05, Unused06, Unused07)  // vtable +0x10..0x1c
    VTABLE_SLOTS_4(Unused08, Unused09, Unused10, Unused11)  // vtable +0x20..0x2c
    VTABLE_SLOTS_4(Unused12, Unused13, Unused14, Unused15)  // vtable +0x30..0x3c
    VTABLE_SLOTS_4(Unused16, Unused17, Unused18, Unused19)  // vtable +0x40..0x4c
    VTABLE_SLOT(Unused20)                                   // vtable +0x50
    VTABLE_SLOT(Unused21)                                   // vtable +0x54
    VTABLE_SLOT(Unused22)                                   // vtable +0x58
    virtual void SetColor(uint32_t c);                      // vtable +0x5c
};

#undef VTABLE_SLOT
#undef VTABLE_SLOTS_4

struct PairHolder {
    void* m000;
    int m004;
    int m008;
    void Get(uint32_t* a, uint32_t* b);
};

struct ModulateEffect {
    void* m00;                     // +0x00
    void* m04;                     // +0x04
    void* m08;                     // +0x08
    void* m0c;                     // +0x0c
    char  pad10[0x50];             // +0x10..0x5f
    void* volatile m60;            // +0x60
    volatile int m64;              // +0x64
    volatile int m68;              // +0x68
    void Ctor();                   // 0x00963db0
    void Update(IColorTarget* target, float t);
};

struct BasicFactory_ModulateEffect {
    void* CreateInstance(void* ctx, void* allocator);
};

// @ 0x00980120
void ModulateEffect::Update(IColorTarget* target, float t)
{
    target->SetColor(WinColor_Lerp((uint32_t)m64, (uint32_t)m68, t));
}

// @ 0x00980150
void PairHolder::Get(uint32_t* a, uint32_t* b)
{
    *a = (uint32_t)m004;
    *b = (uint32_t)m008;
}

// @ 0x009802b0
void* BasicFactory_ModulateEffect::CreateInstance(void* ctx, void* allocator)
{
    if (!allocator)
        allocator = GetDefaultAllocator();
    ModulateEffect* p = (ModulateEffect*)AllocObject(
        0x70, 8, "UTFWin/EA::UTFWinControls::ModulateEffect", allocator);
    if (p) {
        p->Ctor();
        p->m60 = (void*)0x14426a0;
        p->m64 = -1;
        p->m68 = -1;
        p->m00 = (void*)0x1443d90;
        p->m04 = (void*)0x1443d74;
        p->m0c = (void*)0x1443d38;
        p->m60 = (void*)0x1443e5c;
        return p;
    }
    return 0;
}

}  // namespace UTFWinControls
}  // namespace EA
