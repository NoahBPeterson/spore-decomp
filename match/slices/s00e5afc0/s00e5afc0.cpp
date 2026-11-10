#include "types.h"
struct Inner { char pad[0x10]; unsigned mAt10; };
struct Mgr {
    char pad0[0x411c]; unsigned mAt411c;
    char pad1[0x5190 - 0x4120]; Inner* mpAt5190;
};
extern Mgr* g_16b3c04;
struct Obj { unsigned mKey; char pad[0xfc-4]; unsigned mFieldFc; };

// @ 0x00e5afc0
bool FUN_00e5afc0(Obj* o)
{
    unsigned key = o->mKey;
    Mgr* m = g_16b3c04;
    if (key == m->mAt411c)
        return false;
    return o->mFieldFc == m->mpAt5190->mAt10;
}
