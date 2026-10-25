// Slice s00e352c0: Spore engine routines (paused sub-object wake helpers).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

// vtable-slot fetcher: every engine object here is reached through its vtable.
static inline void* vfn(void* obj, unsigned off) { return ((void**)*(void***)obj)[off / 4]; }

// The paused sub-object, stored at owner+0x10 and owner+0x18.
struct PauseState {
    char    pad00[0x44];
    char    mbWakeNeeded;  // +0x44  non-zero: the state has work pending
    char    pad45[0x48 - 0x45];
    int32_t mHandle48;     // +0x48  pending flush handle (0x00828100 reads it)
};

// Target of 0x00bdc4a0 (1 stack argument, this in ecx).
struct CastTarget {
    void FUN_00bdc4a0(int enable);   // 0x00bdc4a0 resume the cast object
};

// Owner the entry point runs on (this in ecx).
struct PauseOwner {
    char        pad00[0x10];
    PauseState* mpState;        // +0x10  state woken by 0x00e352c0
    char        pad14[0x18 - 0x14];
    PauseState* mpState18;      // +0x18  state forwarded by 0x00e35350
    char        pad1c[0x20 - 0x1c];
    char        mbUnpaused;     // +0x20  set to 0 once the object has resumed
};

extern "C" void* __fastcall FUN_00828100(PauseState* self);   // 0x00828100 flush pending handle
extern "C" void* __fastcall FUN_00b25c30(void* self);         // 0x00b25c30 cast helper
extern "C" void* __cdecl    FUN_00b3d300();                   // 0x00b3d300 object getter
extern "C" char  __fastcall FUN_00cf0e10(void* self);         // 0x00cf0e10 paused query
extern "C" void* __cdecl    FUN_00cf74c0();                   // 0x00cf74c0 selector getter
extern "C" void* __fastcall FUN_00cf74f0(void* self);         // 0x00cf74f0 +0xe8 handle
extern "C" void  __fastcall FUN_00e2a6c0(PauseState* self);   // 0x00e2a6c0 sibling wake
extern "C" void  __fastcall FUN_00e352c0(PauseOwner* self);   // this function

// ===========================================================================
// @ 0x00e352c0  wake a sub-object that has work pending: flush its pending
// handle, resume it through its own release slots, and clear the owner's
// "unpaused" byte once the selector reports it is running again.  __fastcall
// with this in ecx only.
// ===========================================================================
void __fastcall FUN_00e352c0(PauseOwner* self)
{
    if (self->mpState->mbWakeNeeded != 0) {
        void* flushed = FUN_00828100(self->mpState);
        ((void (__thiscall*)(void*, int, int))vfn(flushed, 0x7c))(flushed, 1, 0);
        ((void (__thiscall*)(PauseState*))vfn(self->mpState, 0x24))(self->mpState);

        if (self->mbUnpaused != 0) {
            void* selector = FUN_00cf74c0();
            void* handle = FUN_00cf74f0(selector);
            if (FUN_00cf0e10(handle) == 0) {
                self->mbUnpaused = 0;

                void* object = FUN_00b3d300();
                void* cast = FUN_00b25c30(object);
                if (cast != 0)
                    ((CastTarget*)cast)->FUN_00bdc4a0(1);
            }
        }
    }
}

// ===========================================================================
// @ 0x00e35350  tail stub: wake the owner's +0x10 state, then forward the
// +0x18 state to the sibling wake helper.
// ===========================================================================
void __fastcall FUN_00e35350(PauseOwner* self)
{
    FUN_00e352c0(self);
    FUN_00e2a6c0(self->mpState18);
}
