// Cast (0x00e21790): return this for interface 0x03deb129, otherwise ask the base class (Cast 0x950eb0).
#include "game/types.h"

struct Base_e21790 {
    void* Cast(uint32_t typeID) const;   // 0x00950eb0
};
struct Object_e21790 : Base_e21790 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00e21790
void* Object_e21790::Cast(uint32_t typeID) const
{
    if (typeID == 0x03deb129)
        return (void*)this;
    return Base_e21790::Cast(typeID);
}
