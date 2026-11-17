// Cast (0x00c75430): return this for interface 0x02c216ed, otherwise ask the base class (Cast 0xb18460).
#include "game/types.h"

struct Base_c75430 {
    void* Cast(uint32_t typeID) const;   // 0x00b18460
};
struct Object_c75430 : Base_c75430 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c75430
void* Object_c75430::Cast(uint32_t typeID) const
{
    if (typeID == 0x02c216ed)
        return (void*)this;
    return Base_c75430::Cast(typeID);
}
