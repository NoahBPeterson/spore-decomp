// Slice s00951d10 -- UTFSpore_Win32 EA framework global pointer setter.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

void* g_166ae74;                               // 0x0166ae74

// @ 0x00951d10
void __cdecl FUN_00951d10(void* p)
{
    void* old = g_166ae74;

    if (p != old) {
        if (p != 0)
            ((void (__thiscall*)(void*))(*(void***)p)[0])(p);
        g_166ae74 = p;
        if (old != 0)
            ((void (__thiscall*)(void*))(*(void***)old)[1])(old);
    }
}
