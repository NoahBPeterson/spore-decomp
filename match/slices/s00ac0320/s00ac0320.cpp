// Cast (0x00ac0320): return this for interface 0x102a041a, else null.
#include "game/types.h"

struct Object_ac0320 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ac0320
void* Object_ac0320::Cast(uint32_t typeID) const
{
    return typeID == 0x102a041a ? (void*)this : 0;
}
