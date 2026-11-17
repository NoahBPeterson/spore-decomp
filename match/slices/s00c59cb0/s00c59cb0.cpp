// Cast (0x00c59cb0): return this for interface 0x0422227c, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c59cb0 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c59cb0 : Base_c59cb0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c59cb0
void* Object_c59cb0::Cast(uint32_t typeID) const
{
    if (typeID != 0x0422227c)
        return Base_c59cb0::Cast(typeID);
    return (void*)this;
}
