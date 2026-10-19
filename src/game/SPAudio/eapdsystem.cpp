// src/game/SPAudio/eapdsystem.cpp -- migrated from slice(s) s00a68140 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdsystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include <intrin.h>

// ---- items of slice s00a68140 begin (TODO(rewrite): local stubs, replace by canonical classes)
class EapdSystem {
public:
    void  Destroy();                       // 0xa68dd0
    void* ScalarDtor(int flag);            // @ 0xa68e80
};
class IntrusiveList {
public:
    void Remove(void* p);                  // 0xa68280
};
class Outer310 {
public:
    char pad[0x31c];
    IntrusiveList mList;                   // +0x31c
    void RemoveEntry(int p);               // @ 0xa68410
};
// ---- items of slice s00a68140 end

// @ 0x00a68410
void Outer310::RemoveEntry(int p)
{
    if (p)
        mList.Remove(&p);
}

// @ 0x00a68e80
void* EapdSystem::ScalarDtor(int flag)
{
    Destroy();
    return this;
}
