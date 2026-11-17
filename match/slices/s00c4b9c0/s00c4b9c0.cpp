// Cast (0x00c4b9c0): return this for interface 0x0437443d, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c4b9c0 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c4b9c0 : Base_c4b9c0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c4b9c0
void* Object_c4b9c0::Cast(uint32_t typeID) const
{
    if (typeID != 0x0437443d)
        return Base_c4b9c0::Cast(typeID);
    return (void*)this;
}
