// Cast (0x00c41d00): return this for interface 0x0116dd1b, otherwise ask the base class (Cast 0xc884f0).
#include "game/types.h"

struct Base_c41d00 {
    void* Cast(uint32_t typeID) const;   // 0x00c884f0
};
struct Object_c41d00 : Base_c41d00 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c41d00
void* Object_c41d00::Cast(uint32_t typeID) const
{
    if (typeID != 0x0116dd1b)
        return Base_c41d00::Cast(typeID);
    return (void*)this;
}
