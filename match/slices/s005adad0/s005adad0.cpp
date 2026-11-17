// Cast (0x005adad0): return this when the type ID is one of 0x8665f54d, 0xee3f516e, 0xefdf6da5, else null.
#include "game/types.h"

struct Object_5adad0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005adad0
void* Object_5adad0::Cast(uint32_t typeID) const
{
    if (typeID == 0x8665f54d)
        return (void*)this;
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0xefdf6da5 ? (void*)this : 0;
}
