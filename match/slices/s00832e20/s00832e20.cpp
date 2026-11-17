// Cast (0x00832e20): return this for interface 0x0664cdf0, otherwise ask the base class (Cast 0x963490).
#include "game/types.h"

struct Base_832e20 {
    void* Cast(uint32_t typeID) const;   // 0x00963490
};
struct Object_832e20 : Base_832e20 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00832e20
void* Object_832e20::Cast(uint32_t typeID) const
{
    if (typeID != 0x0664cdf0)
        return Base_832e20::Cast(typeID);
    return (void*)this;
}
