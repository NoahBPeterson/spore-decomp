// Cast (0x00c61fa0): return this for interface 0x02aeefff, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c61fa0 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c61fa0 : Base_c61fa0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c61fa0
void* Object_c61fa0::Cast(uint32_t typeID) const
{
    if (typeID != 0x02aeefff)
        return Base_c61fa0::Cast(typeID);
    return (void*)this;
}
