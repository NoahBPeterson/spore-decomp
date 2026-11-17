// Cast (0x00edfe80): return this for interface 0x015a2cf2, else null.
#include "game/types.h"

struct Object_edfe80 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00edfe80
void* Object_edfe80::Cast(uint32_t typeID) const
{
    return typeID == 0x015a2cf2 ? (void*)this : 0;
}
