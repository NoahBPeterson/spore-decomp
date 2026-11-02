// src/game/UTFSpore_Win32/ModulateEffect.cpp -- migrated from slice(s) s0097f390 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ModulateEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWin/IWindow.h"

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned __cdecl wcslen(const wchar_t*);
#pragma intrinsic(wcslen)

// ---- items of slice s0097f390 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP
void* GetDefaultAllocator();                                     // 0x009512c0
void* AllocObject(int size, int align, const char* name, void* allocator);  // 0x009512d0
uint32_t WinColor_Lerp(uint32_t a, uint32_t b, float t);         // 0x007f5eb0
namespace EA {
namespace UTFWinControls {
struct IColorTarget {
    VP4 VP4 VP4 VP4 VP4                               // 0x00..0x4c
    VP VP VP                                          // 0x50..0x58
    virtual void SetColor(uint32_t c);                 // 0x5c
};
}
}
namespace EA {
namespace UTFWinControls {
struct PairHolder {
    void* m000;
    int m004;
    int m008;
    void Get(uint32_t* a, uint32_t* b);
};
}
}
namespace EA {
namespace UTFWinControls {
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
}
}
namespace EA {
namespace UTFWinControls {
struct BasicFactory_ModulateEffect {
    void* CreateInstance(void* ctx, void* allocator);
};
}
}
// ---- items of slice s0097f390 end

// @ 0x00980120
namespace EA { namespace UTFWinControls {
void ModulateEffect::Update(IColorTarget* target, float t)
{
    target->SetColor(WinColor_Lerp((uint32_t)m64, (uint32_t)m68, t));
}
}}  // namespace EA::UTFWinControls

// @ 0x00980150
namespace EA { namespace UTFWinControls {
void PairHolder::Get(uint32_t* a, uint32_t* b)
{
    *a = (uint32_t)m004;
    *b = (uint32_t)m008;
}
}}  // namespace EA::UTFWinControls

// @ 0x009802b0
namespace EA { namespace UTFWinControls {
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
}}  // namespace EA::UTFWinControls
