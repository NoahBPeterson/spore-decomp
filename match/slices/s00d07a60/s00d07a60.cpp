// Cast (0x00d07a60): return this for interface 0x06568b6c, otherwise ask the base class (Cast 0x801300).
#include "game/types.h"

struct Base_d07a60 {
    void* Cast(uint32_t typeID) const;   // 0x00801300
};
struct Object_d07a60 : Base_d07a60 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00d07a60
void* Object_d07a60::Cast(uint32_t typeID) const
{
    if (typeID != 0x06568b6c)
        return Base_d07a60::Cast(typeID);
    return (void*)this;
}
