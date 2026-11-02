// src/game/UTFSpore_Win32/_at_00830000.cpp -- migrated from slice(s) s0083f140 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00830000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Stopwatch.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl Messaging_GetServer();

// ---- items of slice s0083f140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl Messaging_GetServer();
// ---- items of slice s0083f140 end

// @ 0x0083f580
int __cdecl FileMessageCallback(void*, void*, void*, void*, void* arg)
{
    int* server = (int*)Messaging_GetServer();
    if (server) {
        void* p = (arg == 0) ? 0 : (char*)arg + 4;
        return ((int(__thiscall*)(int*, int, int, int, void*))(*(void***)server)[6])(server, 0x6f41f272, 0, 0, p);
    }
    if (arg) {
        int P = *(int*)((char*)arg + 4);
        return ((int(__thiscall*)(int*, int, int))(*(void**)(P + 4)))((int*)((char*)arg + 4), 0x6f41f272, 0);
    }
    return 0;
}
