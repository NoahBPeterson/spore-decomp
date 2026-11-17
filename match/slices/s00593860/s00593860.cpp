// Cast (0x00593860): return this when the type ID is one of 0xee3f516e, 0x0179c807, 0x03a3aa3a, else null.
#include "game/types.h"

struct Object_593860 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00593860
void* Object_593860::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x0179c807)
        return (void*)this;
    return typeID == 0x03a3aa3a ? (void*)this : 0;
}
