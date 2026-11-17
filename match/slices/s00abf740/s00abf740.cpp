// Cast (0x00abf740): return this for interface 0x011c0ba3, else null.
#include "game/types.h"

struct Object_abf740 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00abf740
void* Object_abf740::Cast(uint32_t typeID) const
{
    return typeID == 0x011c0ba3 ? (void*)this : 0;
}
