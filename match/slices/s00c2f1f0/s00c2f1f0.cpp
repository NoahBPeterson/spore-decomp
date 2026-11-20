// @ 0x00c2f1f0
#include "game/types.h"

// Mission accessor with no surviving PDB name: the virtual at +0xc0 hands back
// the active mission id record, whose AddRef/Release are slots 0 and 1.  The
// id picked depends on whether that record is the one stored at +0xa4
// (0xbc = the id of the current mission, 0xb0 = the id of the other one).
//
// The two exits release the record separately; cl15 tail-merges the identical
// Release sequences into one call site, which is what puts `this` in edi and
// the record in esi as in retail (a single shared release tail is compiled
// with the roles swapped, 22 diff bytes).
class MissionSelectionAccessor {
public:
    unsigned int FUN_00c2f1f0();
};

unsigned int MissionSelectionAccessor::FUN_00c2f1f0()
{
    char* self = (char*)this;
    int* properties = (int*)((void* (__thiscall*)(void*))
        (*(void***)self)[0xc0 / 4])(self);
    if (properties != 0)
        ((void (__thiscall*)(void*))(*(void***)properties)[0 / 4])(properties);

    if (properties == *(int**)(self + 0xa4))
    {
        unsigned int result = *(unsigned int*)(self + 0xbc);
        if (properties != 0)
            ((void (__thiscall*)(void*))(*(void***)properties)[4 / 4])(properties);
        return result;
    }

    unsigned int result = *(unsigned int*)(self + 0xb0);
    if (properties != 0)
        ((void (__thiscall*)(void*))(*(void***)properties)[4 / 4])(properties);
    return result;
}
