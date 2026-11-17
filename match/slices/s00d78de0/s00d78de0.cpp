// Cast (0x00d78de0): return this for interface 0x109b40e4, otherwise ask the base class (Cast 0xd79ff0).
#include "game/types.h"

struct Base_d78de0 {
    void* Cast(uint32_t typeID) const;   // 0x00d79ff0
};
struct Object_d78de0 : Base_d78de0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00d78de0
void* Object_d78de0::Cast(uint32_t typeID) const
{
    if (typeID != 0x109b40e4)
        return Base_d78de0::Cast(typeID);
    return (void*)this;
}
