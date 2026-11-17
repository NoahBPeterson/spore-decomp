// Cast (0x00c56c50): return this for interface 0x035ed8f0, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c56c50 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c56c50 : Base_c56c50 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c56c50
void* Object_c56c50::Cast(uint32_t typeID) const
{
    if (typeID != 0x035ed8f0)
        return Base_c56c50::Cast(typeID);
    return (void*)this;
}
