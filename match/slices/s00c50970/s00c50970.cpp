// Cast (0x00c50970): return this for interface 0x032a12f0, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c50970 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c50970 : Base_c50970 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c50970
void* Object_c50970::Cast(uint32_t typeID) const
{
    if (typeID != 0x032a12f0)
        return Base_c50970::Cast(typeID);
    return (void*)this;
}
