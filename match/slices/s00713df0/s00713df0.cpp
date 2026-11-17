// Cast (0x00713df0): return this when the type ID is one of 0x03699ee9, 0xae9cb0fa, 0xee3f516e, else null.
#include "game/types.h"

struct Object_713df0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00713df0
void* Object_713df0::Cast(uint32_t typeID) const
{
    if (typeID == 0x03699ee9)
        return (void*)this;
    if (typeID == 0xae9cb0fa)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
