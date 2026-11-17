// Cast (0x00bd61a0): return this for interface 0x038cfb68, otherwise ask the base class (Cast 0xb18460).
#include "game/types.h"

struct Base_bd61a0 {
    void* Cast(uint32_t typeID) const;   // 0x00b18460
};
struct Object_bd61a0 : Base_bd61a0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00bd61a0
void* Object_bd61a0::Cast(uint32_t typeID) const
{
    if (typeID == 0x038cfb68)
        return (void*)this;
    return Base_bd61a0::Cast(typeID);
}
