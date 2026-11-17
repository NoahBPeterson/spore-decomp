// Cast (0x00ac7770): return this for interface 0x4ffd23cd, else null.
#include "game/types.h"

struct Object_ac7770 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ac7770
void* Object_ac7770::Cast(uint32_t typeID) const
{
    return typeID == 0x4ffd23cd ? (void*)this : 0;
}
