// Cast (0x0099a9b0): return this when the type ID is one of 0xafc46457, 0xee3f516e, else null.
#include "game/types.h"

struct Object_99a9b0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0099a9b0
void* Object_99a9b0::Cast(uint32_t typeID) const
{
    if (typeID == 0xafc46457)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
