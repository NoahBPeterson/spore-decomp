// Cast (0x00ad7270): return this for interface 0x050b7169, otherwise ask the base class (Cast 0xc884f0).
#include "game/types.h"

struct Base_ad7270 {
    void* Cast(uint32_t typeID) const;   // 0x00c884f0
};
struct Object_ad7270 : Base_ad7270 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ad7270
void* Object_ad7270::Cast(uint32_t typeID) const
{
    if (typeID == 0x050b7169)
        return (void*)this;
    return Base_ad7270::Cast(typeID);
}
