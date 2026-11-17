// Cast (0x00c5e7d0): return this for interface 0x03470926, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c5e7d0 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c5e7d0 : Base_c5e7d0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c5e7d0
void* Object_c5e7d0::Cast(uint32_t typeID) const
{
    if (typeID != 0x03470926)
        return Base_c5e7d0::Cast(typeID);
    return (void*)this;
}
