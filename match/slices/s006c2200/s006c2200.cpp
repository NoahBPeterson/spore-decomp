// Cast (0x006c2200): return this for interface 0x2f4e681b, otherwise ask the base class (Cast 0x6abe20).
#include "game/types.h"

struct Base_6c2200 {
    void* Cast(uint32_t typeID) const;   // 0x006abe20
};
struct Object_6c2200 : Base_6c2200 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x006c2200
void* Object_6c2200::Cast(uint32_t typeID) const
{
    if (typeID == 0x2f4e681b)
        return (void*)this;
    return Base_6c2200::Cast(typeID);
}
