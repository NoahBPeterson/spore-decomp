// slice s00599040 -- SP::cCollectableItems::LoadConfiguration and the SpaceInventory UI template
// helpers (layout class with cSPUIPropertyLayout base, cSPUILayout at +0xc, vptr field at +0xa8).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

namespace SP {

class cSPUILayout {
public:
    void* FindWindowByID(int id, int b);   // 0x008105b0
};

class cSpaceInventory {
public:
    char pad0[0xc];
    cSPUILayout mLayout;                    // +0x0c
    char pad10[0x78 - (0xc + sizeof(cSPUILayout))];
    float mFloats[4];                       // +0x78
    char pad88[0xa8 - 0x88];
    void* mpA8;                             // +0xa8
    char padAc[0x6d74 - 0xac];
    int mField6d74;                         // +0x6d74

    bool FUN_00599440(int a, int b, int c);           // 0x00599440
    __declspec(noinline) void LoadConfiguration(int a, int b);   // 0x00599040
    void FUN_00599460();                              // 0x00599460
    void* FUN_005994d0();                             // 0x005994d0
    void FUN_00599530();                              // 0x00599530
    void FUN_00599560();                              // 0x00599560
    void FUN_005995d0();                              // 0x005995d0
    void FUN_00599730(void* a, void* b);              // 0x00599730
    __declspec(noinline) void FUN_005997f0(int a, int b, int c, int d, int e); // 0x005997f0
    void FUN_00599be0(int a);                         // 0x00599be0
    void FUN_00599c10(int a);                         // 0x00599c10

    // external (not in this slice)
    void FUN_00828020(int a);
    void FUN_00828010(float f);
    void FUN_00828be0();
    void FUN_00827fc0(const wchar_t* s, int a);
    void SetMaxCargoAmount(int a);
};

}  // namespace SP

using namespace SP;

volatile int g_dummySideEffect;
#define SIDE_EFFECT() (g_dummySideEffect = 1)

// @ 0x00599440
bool cSpaceInventory::FUN_00599440(int a, int b, int c)
{
    mField6d74 = c;
    LoadConfiguration(a, b);
    return true;
}

// @ 0x00599530
void cSpaceInventory::FUN_00599530()
{
    FUN_00828020(1);
    void* p = mpA8;
    if (p) {
        void** vt = *(void***)p;
        ((void(__thiscall*)(void*, int, int))vt[0x7c / 4])(p, 1, 1);
    }
}

// @ 0x00599560
void cSpaceInventory::FUN_00599560()
{
    FUN_00828020(0);
    void* p = mpA8;
    if (p) {
        void** vt = *(void***)p;
        ((void(__thiscall*)(void*, int, int))vt[0x7c / 4])(p, 1, 0);
    }
}

// @ 0x00599be0
void cSpaceInventory::FUN_00599be0(int a)
{
    FUN_005997f0(a, 0xf865c777, 0x54d95160, 0x54d95161, 0x54d95162);
}

// @ 0x00599c10
void cSpaceInventory::FUN_00599c10(int a)
{
    FUN_005997f0(a, 0x449505af, 0xd4d959e0, 0xd4d959e1, 0xd4d959e2);
}

// @ 0x00599460
void cSpaceInventory::FUN_00599460()
{
    void* win = mLayout.FindWindowByID(0, 1);
    if (win) {
        void* x = ((void*(__thiscall*)(void*))(*(void***)win)[0x10 / 4])(win);
        if (x) {
            void* y = ((void*(__thiscall*)(void*))(*(void***)win)[0x10 / 4])(win);
            ((void(__thiscall*)(void*, void*))(*(void***)y)[0xdc / 4])(y, win);
        }
    }
    FUN_00828be0();
}

// @ 0x00599040
// PARTIAL: 1015 B configuration loader; skeleton only.
__declspec(noinline) void cSpaceInventory::LoadConfiguration(int a, int b) { (void)a; (void)b; SIDE_EFFECT(); }

// @ 0x005994d0
// PARTIAL: SpaceInventory ctor; skeleton only.
void* cSpaceInventory::FUN_005994d0() { return this; }

// @ 0x005995d0
// PARTIAL: 337 B initialise; skeleton only.
void cSpaceInventory::FUN_005995d0() {}

// @ 0x00599730
// PARTIAL: 188 B image-from-layout helper; skeleton only.
void cSpaceInventory::FUN_00599730(void* a, void* b) { (void)a; (void)b; }

// @ 0x005997f0
// PARTIAL: 952 B layout refresh; skeleton only.
__declspec(noinline) void cSpaceInventory::FUN_005997f0(int a, int b, int c, int d, int e) { (void)a; (void)b; (void)c; (void)d; (void)e; SIDE_EFFECT(); }
