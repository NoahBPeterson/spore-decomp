// Cast (0x006b6510): return this for interface 0x030410fc, otherwise ask the base class (Cast 0x6abe20).
#include "game/types.h"

struct Base_6b6510 {
    void* Cast(uint32_t typeID) const;   // 0x006abe20
};
struct Object_6b6510 : Base_6b6510 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x006b6510
void* Object_6b6510::Cast(uint32_t typeID) const
{
    if (typeID == 0x030410fc)
        return (void*)this;
    return Base_6b6510::Cast(typeID);
}
