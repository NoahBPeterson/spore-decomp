// Cast (0x00b72300): return this for interface 0x03ed590d, otherwise ask the base class (Cast 0xb18460).
#include "game/types.h"

struct Base_b72300 {
    void* Cast(uint32_t typeID) const;   // 0x00b18460
};
struct Object_b72300 : Base_b72300 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00b72300
void* Object_b72300::Cast(uint32_t typeID) const
{
    if (typeID != 0x03ed590d)
        return Base_b72300::Cast(typeID);
    return (void*)this;
}
