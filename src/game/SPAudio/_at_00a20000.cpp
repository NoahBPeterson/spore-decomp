// src/game/SPAudio/_at_00a20000.cpp -- migrated from slice(s) s00a20060 by tools/migrate/rewrite.py
// Object file: SPAudio/_at_00a20000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Thread/Mutex.h"
#include "EA/Audio/Playlist.h"
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/Sound.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) unsigned int _controlfp(unsigned int, unsigned int);

// ---- items of slice s00a20060 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) unsigned int _controlfp(unsigned int, unsigned int);
// ---- items of slice s00a20060 end

// @ 0x00a206c0
void __fastcall SetFp(const unsigned int* p)
{
    unsigned int v = *p;
    if ((v & 0x30000) != 0x10000)
        _controlfp(v, 0x30000);
}
