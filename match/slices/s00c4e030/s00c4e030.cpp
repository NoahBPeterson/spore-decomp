// Cast (0x00c4e030): return this for interface 0x02ba2a01, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c4e030 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c4e030 : Base_c4e030 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c4e030
void* Object_c4e030::Cast(uint32_t typeID) const
{
    if (typeID != 0x02ba2a01)
        return Base_c4e030::Cast(typeID);
    return (void*)this;
}
