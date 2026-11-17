// Cast (0x00b8da90): return this for interface 0x03e434e1, otherwise ask the base class (Cast 0x6abe20).
#include "game/types.h"

struct Base_b8da90 {
    void* Cast(uint32_t typeID) const;   // 0x006abe20
};
struct Object_b8da90 : Base_b8da90 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00b8da90
void* Object_b8da90::Cast(uint32_t typeID) const
{
    if (typeID == 0x03e434e1)
        return (void*)this;
    return Base_b8da90::Cast(typeID);
}
