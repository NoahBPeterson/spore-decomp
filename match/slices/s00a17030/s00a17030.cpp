// Slice s00a17030 -- audio system dispatch helper.
#include "types.h"

struct VObj { void** vt; };
typedef void* (__thiscall *FnVp1)(void*, void*);

void* __cdecl GetSystemAT();   // 0x00a206f0  EA::Audio::GetSystemAT

struct CAudioDispatch {
    void* __thiscall Dispatch(bool flag);
};

// @ 0x00a17030
void* __thiscall CAudioDispatch::Dispatch(bool flag) {
    void* sys = GetSystemAT();
    VObj* obj = (VObj*)sys;
    if (flag)
        return ((FnVp1)obj->vt[0x19c / 4])(sys, this);
    return ((FnVp1)obj->vt[0x1a0 / 4])(sys, this);
}
