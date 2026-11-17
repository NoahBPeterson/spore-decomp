// Cast (0x00c51e90): return this for interface 0x02afd27e, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c51e90 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c51e90 : Base_c51e90 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c51e90
void* Object_c51e90::Cast(uint32_t typeID) const
{
    if (typeID != 0x02afd27e)
        return Base_c51e90::Cast(typeID);
    return (void*)this;
}
