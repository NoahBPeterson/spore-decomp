// Cast (0x00c5ecb0): return this for interface 0x0422227e, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c5ecb0 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c5ecb0 : Base_c5ecb0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c5ecb0
void* Object_c5ecb0::Cast(uint32_t typeID) const
{
    if (typeID != 0x0422227e)
        return Base_c5ecb0::Cast(typeID);
    return (void*)this;
}
