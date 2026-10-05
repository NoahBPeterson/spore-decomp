// slice s00585330 — editor input dispatch helpers + stubs.
#include "types.h"

struct cLocalInputState {
    void OnKeyDown(int a, int b);   // 0x00697a50
    void OnKeyUp(int a, int b);     // 0x00697a80
};

struct cAppModeEditorBase {
    char pad0[0x30];
    int mCurrentMouseDown;    // +0x30
    char pad34[0x7c - 0x34];
    void* mLightingWorld;     // +0x7c
    char pad80[0x31c - 0x80];
    int mQueuedAnim;          // +0x31c

    cLocalInputState* Input() { return (cLocalInputState*)((char*)this + 0xf8); }
    uint32_t SetModeModifiers();               // 0x005855b0
    void FUN_00585830(int a, int b);
    void FUN_00585860(int a, int b);
    bool OnKeyUp(uint32_t key, uint32_t mods);
};

// @ 0x00585830
void cAppModeEditorBase::FUN_00585830(int a, int b)
{
    Input()->OnKeyDown(a, b);
    SetModeModifiers();
}

// @ 0x00585860
void cAppModeEditorBase::FUN_00585860(int a, int b)
{
    Input()->OnKeyUp(a, b);
    SetModeModifiers();
}

// @ 0x00585890
bool cAppModeEditorBase::OnKeyUp(uint32_t key, uint32_t mods)
{
    Input()->OnKeyUp(key, mods);
    SetModeModifiers();
    if (mQueuedAnim == 2) {
        typedef void (__thiscall *Fn)(void*, uint32_t, uint32_t);
        Fn fn = *(Fn*)(*(char**)mLightingWorld + 0x20);
        fn(mLightingWorld, key, mods);
    }
    SetModeModifiers();
    if (key > 0xf) {
        if (key < 0x13)
            mCurrentMouseDown = mods;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// Not-yet-reconstructed functions (skeleton stubs; see partial.txt).
void FUN_00585330() {}   // 0x00585330  631 B
void FUN_005855b0() {}   // 0x005855b0  517 B
void FUN_005857c0() {}   // 0x005857c0  104 B
void FUN_005858f0() {}   // 0x005858f0  797 B
void FUN_00585c10() {}   // 0x00585c10  155 B
void FUN_00585d10() {}   // 0x00585d10  38 B
