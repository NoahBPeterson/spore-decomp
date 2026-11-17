// Cast (0x010777f0): return this when the type ID is one of 0xee3f516e, 0x05f5ea41, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_10777f0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x010777f0
void* Object_10777f0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x05f5ea41)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
