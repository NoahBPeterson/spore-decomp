// Cast (0x00c61c30): return this for interface 0x0463327e, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c61c30 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c61c30 : Base_c61c30 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c61c30
void* Object_c61c30::Cast(uint32_t typeID) const
{
    if (typeID != 0x0463327e)
        return Base_c61c30::Cast(typeID);
    return (void*)this;
}
