// Cast (0x00c56680): return this for interface 0x04f3bde8, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c56680 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c56680 : Base_c56680 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c56680
void* Object_c56680::Cast(uint32_t typeID) const
{
    if (typeID != 0x04f3bde8)
        return Base_c56680::Cast(typeID);
    return (void*)this;
}
