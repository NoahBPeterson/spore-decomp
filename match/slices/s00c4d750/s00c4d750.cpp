// Cast (0x00c4d750): return this for interface 0x0462227e, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c4d750 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c4d750 : Base_c4d750 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c4d750
void* Object_c4d750::Cast(uint32_t typeID) const
{
    if (typeID != 0x0462227e)
        return Base_c4d750::Cast(typeID);
    return (void*)this;
}
