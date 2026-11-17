// Cast (0x00992da0): return this for interface 0x04d044f3, otherwise ask the base class (Cast 0x95f960).
#include "game/types.h"

struct Base_992da0 {
    void* Cast(uint32_t typeID) const;   // 0x0095f960
};
struct Object_992da0 : Base_992da0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00992da0
void* Object_992da0::Cast(uint32_t typeID) const
{
    if (typeID != 0x04d044f3)
        return Base_992da0::Cast(typeID);
    return (void*)this;
}
