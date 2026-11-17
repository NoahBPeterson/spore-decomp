// Cast (0x00d79ff0): return this for interface 0x0181957b, otherwise ask the base class (Cast 0xabe880).
#include "game/types.h"

struct Base_d79ff0 {
    void* Cast(uint32_t typeID) const;   // 0x00abe880
};
struct Object_d79ff0 : Base_d79ff0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00d79ff0
void* Object_d79ff0::Cast(uint32_t typeID) const
{
    if (typeID != 0x0181957b)
        return Base_d79ff0::Cast(typeID);
    return (void*)this;
}
