// Cast (0x00622fc0): return this for interface 0x0536c778, otherwise ask the base class (Cast 0x992da0).
#include "game/types.h"

struct Base_622fc0 {
    void* Cast(uint32_t typeID) const;   // 0x00992da0
};
struct Object_622fc0 : Base_622fc0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00622fc0
void* Object_622fc0::Cast(uint32_t typeID) const
{
    if (typeID != 0x0536c778)
        return Base_622fc0::Cast(typeID);
    return (void*)this;
}
