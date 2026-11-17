// Cast (0x009233b0): return this when the type ID is one of 0x0119adc5, 0x0e9f1ff0, 0xee3f516e, else null.
#include "game/types.h"

struct Object_9233b0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x009233b0
void* Object_9233b0::Cast(uint32_t typeID) const
{
    if (typeID == 0x0119adc5)
        return (void*)this;
    if (typeID == 0x0e9f1ff0)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
