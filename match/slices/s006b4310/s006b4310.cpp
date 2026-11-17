// Cast (0x006b4310): return this when the type ID is one of 0xae9cb0fa, 0xee3f516e, 0x043dd21e, else null.
#include "game/types.h"

struct Object_6b4310 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x006b4310
void* Object_6b4310::Cast(uint32_t typeID) const
{
    if (typeID == 0xae9cb0fa)
        return (void*)this;
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x043dd21e ? (void*)this : 0;
}
