// Cast (0x00d546b0): return this for interface 0x0240cb66, otherwise ask the base class (Cast 0xabe880).
#include "game/types.h"

struct Base_d546b0 {
    void* Cast(uint32_t typeID) const;   // 0x00abe880
};
struct Object_d546b0 : Base_d546b0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00d546b0
void* Object_d546b0::Cast(uint32_t typeID) const
{
    if (typeID != 0x0240cb66)
        return Base_d546b0::Cast(typeID);
    return (void*)this;
}
