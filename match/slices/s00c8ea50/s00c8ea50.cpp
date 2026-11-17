// Cast (0x00c8ea50): return this for interface 0x024270c8, otherwise ask the base class (Cast 0xcb3760).
#include "game/types.h"

struct Base_c8ea50 {
    void* Cast(uint32_t typeID) const;   // 0x00cb3760
};
struct Object_c8ea50 : Base_c8ea50 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c8ea50
void* Object_c8ea50::Cast(uint32_t typeID) const
{
    if (typeID == 0x024270c8)
        return (void*)this;
    return Base_c8ea50::Cast(typeID);
}
