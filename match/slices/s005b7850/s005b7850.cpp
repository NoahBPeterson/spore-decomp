// Cast (0x005b7850): return this when the type ID is one of 0xbb46d99a, 0xee3f516e, 0xefdf6da5, else null.
#include "game/types.h"

struct Object_5b7850 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005b7850
void* Object_5b7850::Cast(uint32_t typeID) const
{
    if (typeID == 0xbb46d99a)
        return (void*)this;
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0xefdf6da5 ? (void*)this : 0;
}
