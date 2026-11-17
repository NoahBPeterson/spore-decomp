// Cast (0x00c551b0): return this for interface 0x03470928, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c551b0 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c551b0 : Base_c551b0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c551b0
void* Object_c551b0::Cast(uint32_t typeID) const
{
    if (typeID != 0x03470928)
        return Base_c551b0::Cast(typeID);
    return (void*)this;
}
