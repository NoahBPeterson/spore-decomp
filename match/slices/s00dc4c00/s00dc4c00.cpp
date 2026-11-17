// Cast (0x00dc4c00): return this for interface 0x02e98ab4, otherwise ask the base class (Cast 0xb18460).
#include "game/types.h"

struct Base_dc4c00 {
    void* Cast(uint32_t typeID) const;   // 0x00b18460
};
struct Object_dc4c00 : Base_dc4c00 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00dc4c00
void* Object_dc4c00::Cast(uint32_t typeID) const
{
    if (typeID == 0x02e98ab4)
        return (void*)this;
    return Base_dc4c00::Cast(typeID);
}
