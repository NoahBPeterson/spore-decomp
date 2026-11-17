// Cast (0x00d38850): return this when the type ID is one of 0xae9cb0fa, 0x0116d389, 0x012191ca, else null.
#include "game/types.h"

struct Object_d38850 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00d38850
void* Object_d38850::Cast(uint32_t typeID) const
{
    if (typeID == 0xae9cb0fa)
        return (void*)this;
    if (typeID == 0x0116d389)
        return (void*)this;
    return typeID == 0x012191ca ? (void*)this : 0;
}
