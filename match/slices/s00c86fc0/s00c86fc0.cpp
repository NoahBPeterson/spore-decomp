// Cast (0x00c86fc0): return this for interface 0xb075dec5, otherwise ask the base class (Cast 0xb18460).
#include "game/types.h"

struct Base_c86fc0 {
    void* Cast(uint32_t typeID) const;   // 0x00b18460
};
struct Object_c86fc0 : Base_c86fc0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c86fc0
void* Object_c86fc0::Cast(uint32_t typeID) const
{
    if (typeID == 0xb075dec5)
        return (void*)this;
    return Base_c86fc0::Cast(typeID);
}
