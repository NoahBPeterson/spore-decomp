// Slice s006ac630 — resource-registration registry helpers (SporeApp.exe).
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// The global registry object (0x01603118) exposes Register/Unregister as __thiscall
// members; the free forms below are used where the original tail-calls without an ecx.
struct Registry {
    bool Register(void* key, void* obj);     // 0x006acc60
    bool Unregister(void* key, void* obj);   // 0x006ace70
};
extern Registry* sRegistry;   // 0x01603118

bool Registry_RegisterFree(void* key, void* obj);     // 0x006acc60 (cdecl tail-call form)
bool Registry_UnregisterFree(void* key, void* obj);   // 0x006ace70

// @ 0x006acfe0
bool FUN_006acfe0(uint32_t* a, char* b)
{
    *(uint32_t*)(b + 8)  = a[0];
    *(uint32_t*)(b + 0xc) = a[1];
    *(uint32_t*)(b + 0x10) = a[2];
    if (sRegistry)
        return sRegistry->Register(a, b);
    return false;
}

// @ 0x006ad010
bool FUN_006ad010(char* a)
{
    if (sRegistry)
        return sRegistry->Register(a + 8, a);
    return false;
}

// @ 0x006ad030
bool FUN_006ad030(char* a)
{
    if (sRegistry)
        return sRegistry->Unregister(a, 0);
    return false;
}

// @ 0x006ad050
bool FUN_006ad050(char* a)
{
    if (sRegistry)
        return sRegistry->Unregister(a + 8, a);
    return false;
}

// @ 0x006ad250
void __stdcall FUN_006ad250(char* a)
{
    Registry* r = sRegistry;
    if (r)
        r->Unregister(a + 8, a);
}

// @ 0x006ad590
bool FUN_006ad590(char* a, bool flag)
{
    if (flag)
        return Registry_RegisterFree(a + 8, a);
    return Registry_UnregisterFree(a + 8, a);
}

// ===========================================================================
// Remaining slice functions (partial)
// ===========================================================================

// @ 0x006ac630
// `anonymous namespace'::OnRegister
void OnRegister(void* msg)
{
    // TODO(partial): registration-callback handler (registry insert + fixed_vector push).
    (void)msg;
}

// @ 0x006ac6f0
void FUN_006ac6f0(void* self)
{
    // TODO(partial): vtable reset + Mutex dtor + vector free.
    (void)self;
}

// @ 0x006ac770
void* FUN_006ac770(void* self)
{
    // TODO(partial): vtable + inline fixed_vector init + Mutex ctor.
    return self;
}

// @ 0x006ac7d0
void* FUN_006ac7d0(void* self, void* a2)
{
    // TODO(partial): registry ctor.
    (void)a2;
    return self;
}

// @ 0x006ac840
void FUN_006ac840(void* self, void* a2)
{
    // TODO(partial): registry callback list setup.
    (void)self; (void)a2;
}

// @ 0x006ac8d0
void FUN_006ac8d0(void* self, void* a2, void* a3)
{
    // TODO(partial): registry insert path.
    (void)self; (void)a2; (void)a3;
}

// @ 0x006aca20
void FUN_006aca20(void* self, void* a2)
{
    // TODO(partial): registry erase/lookup helper.
    (void)self; (void)a2;
}

// @ 0x006acaa0
void FUN_006acaa0(void* self, void* a2, void* a3)
{
    // TODO(partial): registration callback vector manipulation.
    (void)self; (void)a2; (void)a3;
}

// @ 0x006acc60
bool FUN_006acc60(void* key, void* obj)
{
    // TODO(partial): sRegistry->Register(key,obj): find/add registration entry and push
    // the callback vector.
    (void)key; (void)obj;
    return false;
}

// @ 0x006ace70
bool FUN_006ace70(void* key, void* obj)
{
    // TODO(partial): sRegistry->Unregister(key,obj): erase registration entry.
    (void)key; (void)obj;
    return false;
}

// @ 0x006ad070
// SP::RemoveRegistrationCallback
void RemoveRegistrationCallback(void* key, void* callback)
{
    // TODO(partial): fixed-hashtable find + erase of one callback pointer.
    (void)key; (void)callback;
}

// @ 0x006ad0f0
void FUN_006ad0f0(void* self, void* a2)
{
    // TODO(partial): registry callback registration helper.
    (void)self; (void)a2;
}

// @ 0x006ad180
void FUN_006ad180(void* self, void* a2)
{
    // TODO(partial): registry teardown helper.
    (void)self; (void)a2;
}

// @ 0x006ad270
void FUN_006ad270(void* self, void* a2, void* a3)
{
    // TODO(partial): shader/resource registration path.
    (void)self; (void)a2; (void)a3;
}

// @ 0x006ad350
void FUN_006ad350(void* self, void* a2)
{
    // TODO(partial): registration list walk.
    (void)self; (void)a2;
}

// @ 0x006ad410
void FUN_006ad410(void* self, void* a2, void* a3)
{
    // TODO(partial): registration notify loop.
    (void)self; (void)a2; (void)a3;
}
