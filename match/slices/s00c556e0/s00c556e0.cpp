// Cast (0x00c556e0): return this for interface 0x0422227d, otherwise ask the base class (Cast 0xc59cb0).
#include "game/types.h"

struct Base_c556e0 {
    void* Cast(uint32_t typeID) const;   // 0x00c59cb0
};
struct Object_c556e0 : Base_c556e0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c556e0
void* Object_c556e0::Cast(uint32_t typeID) const
{
    if (typeID != 0x0422227d)
        return Base_c556e0::Cast(typeID);
    return (void*)this;
}
