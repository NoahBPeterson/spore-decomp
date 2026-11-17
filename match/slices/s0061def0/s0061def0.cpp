// Cast (0x0061def0): return this when the type ID is one of 0x060419ef, 0xae9cb0fa, 0xee3f516e, else null.
#include "game/types.h"

struct Object_61def0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0061def0
void* Object_61def0::Cast(uint32_t typeID) const
{
    if (typeID == 0x060419ef)
        return (void*)this;
    if (typeID == 0xae9cb0fa)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
