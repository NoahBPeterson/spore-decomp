// Cast (0x00c4ebb0): return this for interface 0x02f9998c, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c4ebb0 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c4ebb0 : Base_c4ebb0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c4ebb0
void* Object_c4ebb0::Cast(uint32_t typeID) const
{
    if (typeID != 0x02f9998c)
        return Base_c4ebb0::Cast(typeID);
    return (void*)this;
}
