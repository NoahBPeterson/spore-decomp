// Cast (0x00c625f0): return this for interface 0x02aeeeee, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c625f0 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c625f0 : Base_c625f0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c625f0
void* Object_c625f0::Cast(uint32_t typeID) const
{
    if (typeID != 0x02aeeeee)
        return Base_c625f0::Cast(typeID);
    return (void*)this;
}
