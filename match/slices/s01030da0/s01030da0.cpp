// Cast (0x01030da0): return this for interface 0x114242e6, otherwise ask the base class (Cast 0xabe880).
#include "game/types.h"

struct Base_1030da0 {
    void* Cast(uint32_t typeID) const;   // 0x00abe880
};
struct Object_1030da0 : Base_1030da0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x01030da0
void* Object_1030da0::Cast(uint32_t typeID) const
{
    if (typeID != 0x114242e6)
        return Base_1030da0::Cast(typeID);
    return (void*)this;
}
