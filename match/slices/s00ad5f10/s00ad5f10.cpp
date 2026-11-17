// Cast (0x00ad5f10): return this when the type ID is one of 0xee3f516e, 0x0448444b, else null.
#include "game/types.h"

struct Object_ad5f10 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ad5f10
void* Object_ad5f10::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x0448444b ? (void*)this : 0;
}
