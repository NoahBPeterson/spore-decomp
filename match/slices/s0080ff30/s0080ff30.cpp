// Cast (0x0080ff30): return this for interface 0x05adf5fb, otherwise ask the base class (Cast 0x6abe20).
#include "game/types.h"

struct Base_80ff30 {
    void* Cast(uint32_t typeID) const;   // 0x006abe20
};
struct Object_80ff30 : Base_80ff30 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0080ff30
void* Object_80ff30::Cast(uint32_t typeID) const
{
    if (typeID == 0x05adf5fb)
        return (void*)this;
    return Base_80ff30::Cast(typeID);
}
