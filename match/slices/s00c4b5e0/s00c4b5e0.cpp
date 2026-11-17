// Cast (0x00c4b5e0): return this for interface 0x03470927, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c4b5e0 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c4b5e0 : Base_c4b5e0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c4b5e0
void* Object_c4b5e0::Cast(uint32_t typeID) const
{
    if (typeID != 0x03470927)
        return Base_c4b5e0::Cast(typeID);
    return (void*)this;
}
