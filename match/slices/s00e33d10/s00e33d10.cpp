// Cast (0x00e33d10): return this when the type ID is one of 0x2f009dd0, 0x31e56741, 0xee3f516e, else null.
#include "game/types.h"

struct Object_e33d10 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00e33d10
void* Object_e33d10::Cast(uint32_t typeID) const
{
    if (typeID == 0x2f009dd0)
        return (void*)this;
    if (typeID == 0x31e56741)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
