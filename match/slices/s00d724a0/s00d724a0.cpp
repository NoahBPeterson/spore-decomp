// Cast (0x00d724a0): return this for interface 0x0018195d, otherwise ask the base class (Cast 0xd79ff0).
#include "game/types.h"

struct Base_d724a0 {
    void* Cast(uint32_t typeID) const;   // 0x00d79ff0
};
struct Object_d724a0 : Base_d724a0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00d724a0
void* Object_d724a0::Cast(uint32_t typeID) const
{
    if (typeID != 0x0018195d)
        return Base_d724a0::Cast(typeID);
    return (void*)this;
}
