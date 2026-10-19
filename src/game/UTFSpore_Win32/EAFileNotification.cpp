// src/game/UTFSpore_Win32/EAFileNotification.cpp -- migrated from slice(s) s01300280 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAFileNotification.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int atexit(void (__cdecl*)());
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(const char* name);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void* module, const char* name);
extern void FUN_013c0f40(void);

// ---- items of slice s01300280 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int atexit(void (__cdecl*)());
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(const char* name);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void* module, const char* name);
extern void FUN_013c0f40(void);
// ---- items of slice s01300280 end

// @ 0x01300280
void init_1668f1c()
{
    void* h = LoadLibraryA("kernel32.dll");
    *(void**)0x1668f1c = h;
    if (h != 0) {
        *(void**)0x1668f20 = GetProcAddress(h, "ReadDirectoryChangesW");
        atexit(&FUN_013c0f40);
    } else {
        *(void**)0x1668f20 = 0;
        atexit(&FUN_013c0f40);
    }
}
