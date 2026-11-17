// Cast (0x00c7e5b0): return this for interface 0x03572e6c, otherwise ask the base class (Cast 0xb18460).
#include "game/types.h"

struct Base_c7e5b0 {
    void* Cast(uint32_t typeID) const;   // 0x00b18460
};
struct Object_c7e5b0 : Base_c7e5b0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c7e5b0
void* Object_c7e5b0::Cast(uint32_t typeID) const
{
    if (typeID == 0x03572e6c)
        return (void*)this;
    return Base_c7e5b0::Cast(typeID);
}
