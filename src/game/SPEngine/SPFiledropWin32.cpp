// src/game/SPEngine/SPFiledropWin32.cpp -- migrated from slice(s) s006bb1c0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPFiledropWin32.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void __stdcall ReleaseStgMedium(void*);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long*);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long*);

// ---- items of slice s006bb1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void __stdcall ReleaseStgMedium(void*);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long*);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long*);
void __cdecl FUN_00688dd0(void*);
struct RefObj { void** vtbl; long mRefCount; };
// ---- items of slice s006bb1c0 end

// @ 0x006bb7b0
bool __cdecl FUN_006bb7b0(const void* a, const void* b)
{ (void)a; (void)b; return false; }

// @ 0x006bb830
void __cdecl FUN_006bb830(void* self)
{ (void)self; }

// @ 0x006bb890
long __stdcall FUN_006bb890(long* p)
{
    return InterlockedIncrement(p + 1);
}

// @ 0x006bb8b0
long __stdcall FUN_006bb8b0(RefObj* p)
{
    long n = InterlockedDecrement(&p->mRefCount);
    if (n == 0) {
        if (p) ((void(__thiscall*)(RefObj*, int))p->vtbl[7])(p, 1);
        n = 0;
    }
    return n;
}

// @ 0x006bb8e0
void __cdecl FUN_006bb8e0(void* self)
{ (void)self; }

// @ 0x006bb9b0
void __cdecl FUN_006bb9b0(void* self)
{ (void)self; }

// @ 0x006bba40
int __stdcall FUN_006bba40(void* p)
{
    char* c = (char*)p;
    if (c[0xc]) {
        FUN_00688dd0(c + 0x24);
        ReleaseStgMedium(c + 0x24);
        c[0xc] = 0;
    }
    return 0;
}

// @ 0x006bba70
void __cdecl FUN_006bba70(void* self)
{ (void)self; }
