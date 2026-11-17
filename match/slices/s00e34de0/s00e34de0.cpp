// Cast (0x00e34de0): return this for interface 0xae9cb0fa, otherwise ask the base class (Cast 0x801300).
#include "game/types.h"

struct Base_e34de0 {
    void* Cast(uint32_t typeID) const;   // 0x00801300
};
struct Object_e34de0 : Base_e34de0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00e34de0
void* Object_e34de0::Cast(uint32_t typeID) const
{
    if (typeID != 0xae9cb0fa)
        return Base_e34de0::Cast(typeID);
    return (void*)this;
}
