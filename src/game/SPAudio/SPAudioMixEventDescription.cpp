// src/game/SPAudio/SPAudioMixEventDescription.cpp -- migrated from slice(s) s00a3cbb0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioMixEventDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"

// unnamed retail callees and globals (address in the comment)
extern char  PTR_FUN_01453930[];            // ICommand vtable for the mixevent inline command
extern char  PTR_FUN_01453918[];            // NotifyAttack command vtable

// ---- items of slice s00a3cbb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int, const char*, int, int, int, int);
void* operator new(unsigned int, const char*, int, int, const char*, int);
inline void* operator new(unsigned int, void* p) { return p; }
extern char  PTR_FUN_01453930[];            // ICommand vtable for the mixevent inline command
extern char  PTR_FUN_01453918[];            // NotifyAttack command vtable
namespace EA {
namespace ArgScript {
void cCommandBase_ctor(void* p);
}
}
void MixEventAddCommands(int* mgr);   // 0xa3cce0
inline char* VT(int obj) { return *(char**)obj; }
// ---- items of slice s00a3cbb0 end

// @ 0x00a3cce0
void MixEventAddCommands(int* mgr)
{
    void* c1 = ::operator new(0x10, "ArgScript/MixEventInline", 0, 0, 0, 0);
    if (c1) {
        EA::ArgScript::cCommandBase_ctor(c1);
        *(void**)c1 = (void*)PTR_FUN_01453930;
    }
    (*(void(__thiscall**)(int*, const char*, void*))(VT((int)mgr) + 0x18))(mgr, "mixevent", c1);
    void* c2 = ::operator new(0xc, "Swarm", 0, 0, 0, 0);
    if (c2) {
        EA::ArgScript::cCommandBase_ctor(c2);
        *(void**)c2 = (void*)PTR_FUN_01453918;
    }
    (*(void(__thiscall**)(int*, const char*, void*))(VT((int)mgr) + 0x14))(mgr, "mixevent", c2);
}
