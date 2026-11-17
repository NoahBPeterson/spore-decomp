// Cast (0x00c561c0): return this for interface 0x0317afcb, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c561c0 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c561c0 : Base_c561c0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c561c0
void* Object_c561c0::Cast(uint32_t typeID) const
{
    if (typeID != 0x0317afcb)
        return Base_c561c0::Cast(typeID);
    return (void*)this;
}
