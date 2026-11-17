// Cast (0x00ad6940): return this when the type ID is one of 0xee3f516e, 0x060b4546, else null.
#include "game/types.h"

struct Object_ad6940 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ad6940
void* Object_ad6940::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x060b4546 ? (void*)this : 0;
}
