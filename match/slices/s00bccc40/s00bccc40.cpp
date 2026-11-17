// Cast (0x00bccc40): return this for interface 0x01a55e4d, otherwise ask the base class (Cast 0xbcc500).
#include "game/types.h"

struct Base_bccc40 {
    void* Cast(uint32_t typeID) const;   // 0x00bcc500
};
struct Object_bccc40 : Base_bccc40 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00bccc40
void* Object_bccc40::Cast(uint32_t typeID) const
{
    if (typeID == 0x01a55e4d)
        return (void*)this;
    return Base_bccc40::Cast(typeID);
}
