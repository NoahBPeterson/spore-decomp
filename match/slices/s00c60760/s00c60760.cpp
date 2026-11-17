// Cast (0x00c60760): return this for interface 0x035988ee, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c60760 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c60760 : Base_c60760 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c60760
void* Object_c60760::Cast(uint32_t typeID) const
{
    if (typeID != 0x035988ee)
        return Base_c60760::Cast(typeID);
    return (void*)this;
}
