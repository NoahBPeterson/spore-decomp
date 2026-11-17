// Cast (0x00835280): return this for interface 0x03796ce5, otherwise ask the base class (Cast 0x950eb0).
#include "game/types.h"

struct Base_835280 {
    void* Cast(uint32_t typeID) const;   // 0x00950eb0
};
struct Object_835280 : Base_835280 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00835280
void* Object_835280::Cast(uint32_t typeID) const
{
    if (typeID != 0x03796ce5)
        return Base_835280::Cast(typeID);
    return (void*)this;
}
