// Cast (0x00c4afd0): return this for interface 0x0463329e, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c4afd0 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c4afd0 : Base_c4afd0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c4afd0
void* Object_c4afd0::Cast(uint32_t typeID) const
{
    if (typeID != 0x0463329e)
        return Base_c4afd0::Cast(typeID);
    return (void*)this;
}
