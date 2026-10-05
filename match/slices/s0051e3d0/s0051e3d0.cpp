// Slice 6: nSPSkinner PaintSystem destructor plus DeviceRestore and cPaintSystem::Shutdown.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

void DefaultRefCounted_Release(void* p);   // 0x0040????  (DefaultRefCounted::Release)
void FUN_00402420(void* p);                // 0x00402420
void SP_cJob_GetStatus(void* job);         // 0x00690120
void FUN_00526a40();                       // 0x00526a40
void FUN_004e1bf0();                       // 0x004e1bf0
void FUN_00525e10(void* p);                // 0x00525e10
void* EA_alloc(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0

extern void* g_vtblF1c74;                // 0x013f1c74
extern void* g_vtblF1c70;                // 0x013f1c70
extern void* g_vtblSimCreatureAbility;   // 0x013ef094
extern void* g_vtblSkinnerPaintSystem;   // 0x013eb394

inline void VCall1(void* p)
{
    (*(void(__thiscall**)(void*))(((void**)*(void**)p)[1]))(p);
}

struct PaintSystem2 {
    void dtor();
};

// @ 0x0051e3d0 PaintSystem dtor (full member teardown)
void PaintSystem2::dtor()
{
    *(void**)this = &g_vtblF1c74;
    *(void**)((char*)this + 4) = &g_vtblF1c70;
    if (*(void**)((char*)this + 0x104) != 0)
        DefaultRefCounted_Release(*(void**)((char*)this + 0x104));
    if (*(void**)((char*)this + 0x100) != 0)
        FUN_00402420(*(void**)((char*)this + 0x100));
    if (*(void**)((char*)this + 0xfc) != 0)
        SP_cJob_GetStatus(*(void**)((char*)this + 0xfc));
    if (*(void**)((char*)this + 0xf8) != 0)
        SP_cJob_GetStatus(*(void**)((char*)this + 0xf8));
    if (*(void**)((char*)this + 0xf4) != 0)
        VCall1(*(void**)((char*)this + 0xf4));
    if (*(void**)((char*)this + 0xf0) != 0)
        VCall1(*(void**)((char*)this + 0xf0));
    for (uint32_t i = *(uint32_t*)((char*)this + 0x94); i < *(uint32_t*)((char*)this + 0x98); i += 8) {
    }
    FUN_00526a40();
    FUN_004e1bf0();
    FUN_00525e10(this);
    if (*(void**)((char*)this + 0x1c) != 0)
        DefaultRefCounted_Release(*(void**)((char*)this + 0x1c));
    if (*(void**)((char*)this + 0x18) != 0)
        DefaultRefCounted_Release(*(void**)((char*)this + 0x18));
    if (*(void**)((char*)this + 0x14) != 0)
        VCall1(*(void**)((char*)this + 0x14));
    if (*(void**)((char*)this + 0x10) != 0)
        DefaultRefCounted_Release(*(void**)((char*)this + 0x10));
    if (*(void**)((char*)this + 0x0c) != 0)
        DefaultRefCounted_Release(*(void**)((char*)this + 0x0c));
    *(void**)((char*)this + 4) = &g_vtblSimCreatureAbility;
    *(void**)this = &g_vtblSkinnerPaintSystem;
}

// @ 0x0051e5b0 `anonymous namespace'::DeviceRestore -- PARTIAL skeleton (1723-byte /Od body)
void FUN_0051e5b0(void* self) { (void)self; }

// @ 0x0051ec70 nSPSkinner::cPaintSystem::Shutdown -- PARTIAL skeleton (1083-byte /Od body)
void FUN_0051ec70(void* self) { (void)self; }
